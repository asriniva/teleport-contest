import measured from '../js/nethack/records.json' with {type:'json'};
import assert from 'node:assert/strict';
import {createStandaloneEnvironment} from '../js/nethack/environment.js';
import {createNativeRecordViews} from '../js/nethack/native/record-views.js';
import {createRecordViews} from '../js/c-runtime/record-views.js';
import {fieldAliases} from '../js/nethack/declarations.js';
import {nativeStateFor} from '../js/nethack/native/state-bridge.js';
const env=createStandaloneEnvironment(),{memory,ctypes}=env;
const native=createNativeRecordViews(env),legacy=createRecordViews(env,fieldAliases),owner=nativeStateFor(env);
assert.equal(createNativeRecordViews(env),native,'all game adapters use one complete native record owner');
let checks=0,fields=0;
const types=process.env.NATIVE_RECORD_VIEW_ALL_TYPES==='1'?Object.keys(measured.records):['struct monst','struct you','struct prop','struct permonst','struct obj','struct rm','struct instance_globals_saved_c','struct window_procs'];
for(const type of types){
 const row=ctypes.record(type),at=memory.calloc(1,row.size),a=native.record(type,at),b=legacy.record(type,at);
 assert.equal(native.record(type,at),a);
 if(owner.sharedTypes.has(type))assert.equal(owner.records.get(type+':'+at),a);
 for(const[name,field]of Object.entries(row.fields)){
  const scalar=ctypes.canonical(field.ctype.replace(new RegExp('\\s+'+name+'$'),''));
  if(field.record||scalar.includes('[')||(!field.bits&&!scalar.includes('*')&&!/^(?:unsigned |signed )?(?:char|short|int|long|long long|float|double)$/.test(scalar)&&!scalar.startsWith('enum ')))continue;
  fields++;
  for(const value of [0,-1,65537,4294967297,2n**80n+1n,'17',undefined,NaN,Infinity,1.5]){
   memory.HEAPU8.fill(0xa5,at,at+row.size);const initial=memory.readBytes(at,row.size);
   let expectedError,actualError;
   try{b[name]=value;}catch(e){expectedError=e.constructor;}
   const expected=memory.readBytes(at,row.size);memory.HEAPU8.set(initial,at);
   try{a[name]=value;}catch(e){actualError=e.constructor;}
   assert.equal(actualError,expectedError,type+'.'+name+' '+String(value)+' coercion');
   assert.deepEqual(memory.readBytes(at,row.size),expected,type+'.'+name+' '+String(value)+' bytes');checks++;
   if(!actualError&&!scalar.includes('*')){assert.equal(a[name],b[name],type+'.'+name+' read');checks++;}
  }
 }
 memory.HEAPU8.fill(0,at,at+row.size);
}
const monAt=memory.calloc(1,ctypes.size('struct monst')),monster=native.record('struct monst',monAt);
const artifactAt=memory.calloc(1,ctypes.size('struct artifact')),artifact=native.record('struct artifact',artifactAt);
artifact.attk.aatyp=3;artifact.defn=artifact.attk;assert.equal(artifact.defn.aatyp,3);assert.equal(legacy.record('struct artifact',artifactAt).attk.aatyp,3);
monster.nmon=monster;assert.equal(monster.nmon,monster);
assert.equal([...monster.mtrack].length,monster.mtrack.length);
for(const point of monster.mtrack){point.x=1;point.y=2;}
for(let i=0;i<monster.mtrack.length;i++){assert.equal(monster.mtrack[i].x,1);assert.equal(monster.mtrack[i].y,2);}
const propAt=memory.calloc(69,ctypes.size('struct prop')),props=native.array('struct prop',propAt,69);
assert.equal(props,native.array('struct prop',propAt,69));assert.equal(props[1],native.record('struct prop',propAt+ctypes.size('struct prop')));
assert.equal(props[69].address,propAt+69*ctypes.size('struct prop'));assert.throws(()=>props[70],RangeError);
props[1].intrinsic=123n;props[2]=props[1];props[1].intrinsic=456n;assert.equal(props[2].intrinsic,123n);
const intsAt=memory.calloc(4,4),ints=native.array('int',intsAt,4);ints[1]=4294967297;assert.equal(ints[1],1);assert.equal(ints['01'],1);
assert.throws(()=>ints[4],RangeError);assert.throws(()=>native.array('int',0,4)[0],RangeError);
const before=memory.buffer;assert.equal(memory.grow(before.byteLength+1),true);assert.notEqual(memory.buffer,before);
assert.equal(props[1].intrinsic,456n);monster.mhp=42;assert.equal(legacy.record('struct monst',monAt).mhp,42);
assert.equal(native.advance(props[1],1),props[2]);
const pairAt=memory.calloc(2,ctypes.size('struct monst')),left=native.record('struct monst',pairAt),right=native.record('struct monst',pairAt+ctypes.size('struct monst'));
for(const field of ['mhp','mx','my','m_lev','mcan','mpeaceful']){
 const a=Object.getOwnPropertyDescriptor(left,field),b=Object.getOwnPropertyDescriptor(right,field);
 assert.ok(a.get===b.get,field+' getters are shared across real actor records');assert.ok(a.set===b.set,field+' setters are shared');
}
left.mhp=17;right.mhp=29;assert.equal(left.mhp,17);assert.equal(right.mhp,29);
const oldAddress=left.address;try{left.address=right.address;left.mhp=18;assert.equal(right.mhp,29);assert.equal(memory.view.getInt32(ctypes.fieldAddress('struct monst',oldAddress,'mhp'),true),18,'public address metadata never rebinds native storage');}finally{left.address=oldAddress;}
assert.equal(Object.getOwnPropertyDescriptor(left,'mhp').get.call(right),29,'a shared accessor reads its native receiver');
const coordAt=memory.calloc(1,ctypes.size('struct nhcoord')+1)+1,unaligned=native.record('struct nhcoord',coordAt);unaligned.x=-123;unaligned.y=321;assert.equal(memory.view.getInt16(coordAt,true),-123);assert.equal(unaligned.y,321);
const cellAt=memory.calloc(2,ctypes.size('struct rm')),cellA=native.record('struct rm',cellAt),cellB=native.record('struct rm',cellAt+ctypes.size('struct rm'));
assert.ok(Object.getOwnPropertyDescriptor(cellA,'lit').get===Object.getOwnPropertyDescriptor(cellB,'lit').get);cellA.lit=1;cellB.lit=0;assert.equal(cellA.lit,1);
const previousBytes=memory.buffer.byteLength;memory.grow(previousBytes+1);left.mhp=19;assert.equal(memory.view.getInt32(ctypes.fieldAddress('struct monst',left.address,'mhp'),true),19);assert.equal(unaligned.y,321);assert.equal(cellA.lit,1);
const second=createStandaloneEnvironment(),other=createNativeRecordViews(second),otherAt=second.memory.calloc(1,second.ctypes.size('struct monst'));
assert.notEqual(other.record('struct monst',otherAt),monster);
console.log(JSON.stringify({passed:true,recordTypes:types.length,fields,checks,canonicalIdentity:true,aliases:true,narrowing:true,arrays:true,growth:true,isolation:true,sharedScalarAndBitAccessors:true,fixedStorageAddress:true,unalignedRecords:true}));
