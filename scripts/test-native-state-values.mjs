// Measured enum fields and arrays must retain byte aliases without generic I/O.
import assert from 'node:assert/strict';
import metadata from '../js/nethack/records.json' with {type:'json'};
import {createStandaloneEnvironment} from '../js/nethack/environment.js';
import {createNativeRecordViews} from '../js/nethack/native/record-views.js';
const environment=createStandaloneEnvironment({initialBytes:1024,maximumBytes:128*1024*1024});
const {memory,ctypes}=environment,views=createNativeRecordViews(environment);
let checks=0,fields=0;
const load=ctypes.load,store=ctypes.store;
const deny=()=>{throw Error('generic C scalar I/O reached');};
function nativeOnly(callback){ctypes.load=ctypes.store=deny;try{return callback();}finally{ctypes.load=load;ctypes.store=store;}}
for(const [type,definition]of Object.entries(metadata.records)){
 const enums=Object.entries(definition.fields).flatMap(([name,field])=>{
  if(field.bits!==undefined)return [];
  const declared=ctypes.canonical(field.ctype.replace(new RegExp('\\s+'+name+'$'),''));
  return declared.startsWith('enum ')&&!declared.includes('*')&&!declared.includes('[')?[{name,field,declared}]:[];
 });
 if(!enums.length)continue;
 const at=memory.calloc(1,definition.size),record=views.record(type,at);
 try{for(const {name,field,declared}of enums){
  fields++;const p=at+field.offset;
  for(const value of [-2147483649n,-1n,0n,1n,2147483647n,4294967295n,4294967299n,1n<<63n]){
   store(declared,p,value);const expected=load(declared,p);
   assert.equal(nativeOnly(()=>record[name]),expected,'C byte writes -> '+type+'.'+name);checks++;
   nativeOnly(()=>{record[name]=value;});assert.equal(load(declared,p),expected,'native writes -> C '+type+'.'+name);checks++;
  }
 }}finally{memory.free(at);}
}
assert.ok(fields>0,'actual compiler enum fields were exercised');
const scalarTypes=['signed char','unsigned char','short','unsigned short','int','unsigned int','long','unsigned long','enum monnums'];
for(const type of scalarTypes)for(const unaligned of [false,true]){
 const bytes=ctypes.size(type),allocation=memory.calloc(1,bytes*4+16),at=allocation+(unaligned?1:0),array=views.array(type,at,4);
 try{for(const value of [-1n,0n,1n,4294967299n,1n<<63n])for(let i=0;i<4;i++){
  store(type,at+i*bytes,value);const expected=load(type,at+i*bytes);
  assert.equal(nativeOnly(()=>array[i]),expected,'byte alias '+type);checks++;
  nativeOnly(()=>{array[i]=value;});assert.equal(load(type,at+i*bytes),expected,'native array '+type);checks++;
 }
 memory.grow(memory.buffer.byteLength+1);
 nativeOnly(()=>{array[0]=7;assert.equal(array[0],type==='long'||type==='unsigned long'?7n:7);});checks++;
 assert.throws(()=>nativeOnly(()=>{array[0]=NaN;}),RangeError);checks++;
 }finally{memory.free(allocation);}
}
const actorAt=memory.calloc(1,ctypes.size('struct monst')),actor=views.record('struct monst',actorAt);
const slots=memory.calloc(1,64),occupancy=views.array('struct monst *',slots,4),opaque=views.array('void *',slots+32,4);
try{nativeOnly(()=>{
 occupancy[1]=actor;assert.equal(occupancy[1],actor);checks++;
 occupancy[1]=0;assert.equal(occupancy[1],0);checks++;
 occupancy[2]=actorAt;assert.equal(occupancy[2],actor);checks++;
 opaque[0]=(1n<<63n)+1n;assert.equal(opaque[0],(1n<<63n)+1n);checks++;
 opaque[1]=-1n;assert.equal(opaque[1],(1n<<64n)-1n);checks++;
 memory.grow(memory.buffer.byteLength+1);
 assert.equal(occupancy[2],actor);opaque[2]=actor;assert.equal(opaque[2],actorAt);checks+=2;
 });
 assert.equal(load('struct monst *',slots+16),BigInt(actorAt));checks++;
 store('struct monst *',slots+16,0);assert.equal(nativeOnly(()=>occupancy[2]),0);checks++;
}finally{memory.free(actorAt);memory.free(slots);}
console.log(JSON.stringify({passed:true,checks,measuredEnumFields:fields,scalarTypes:scalarTypes.length,alignedAndUnaligned:true,growth:true,canonicalOccupancy:true,genericScalarIo:false}));
