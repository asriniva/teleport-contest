// Combined original-C initialized constructors and inventory, with real owners.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import crypto from 'node:crypto';
import {pathToFileURL} from 'node:url';
import {createStandaloneEnvironment} from '../js/standalone/environment.js';
import {C,R,T} from '../js/c-runtime/context.js';
const directory=path.resolve(process.env.STANDALONE_ITEM_INVENTORY_ORACLE||'.cache/standalone-item-inventory');
const receipt=JSON.parse(fs.readFileSync(path.join(directory,'receipt.json')));
const sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex');
for(const [p,h]of Object.entries(receipt.sourceSha256))assert.equal(sha(p),h,'Changed C input '+p);
for(const [p,h]of Object.entries(receipt.artifactSha256))assert.equal(sha(path.join(directory,p)),h,'Changed C artifact '+p);
const {default:factory}=await import(pathToFileURL(path.join(directory,'reference.mjs')));
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),L=layouts.mkobj,O=layouts.o_init;
const records=JSON.parse(fs.readFileSync('js/standalone/records.json')).records;
// Explicit unfinished families. No catch-and-skip: any failure for a listed
// supported type fails the suite. These families are additional integration work.
const pendingNames=['AMULET_OF_YENDOR','CANDELABRUM_OF_INVOCATION','BELL_OF_OPENING','SPE_BOOK_OF_THE_DEAD','LARGE_BOX','CHEST','ICE_BOX','SACK','OILSKIN_SACK','BAG_OF_HOLDING','FIGURINE','CORPSE','EGG','TIN','STATUE','GLOB_OF_GRAY_OOZE','GLOB_OF_BROWN_PUDDING','GLOB_OF_GREEN_SLIME','GLOB_OF_BLACK_PUDDING','CANDY_BAR','SPE_NOVEL'];
const pending=new Set(pendingNames.map(name=>{const value=L[name]??O[name];assert.ok(Number.isInteger(value),name);return value;}));
let comparisons=0,constructors=0,callbacks=0;
for(const seed of [1n,0x12345678n,0xffffffffffffffffn]){
 const env=createStandaloneEnvironment({initialBytes:1024,maximumBytes:64*1024*1024,environment:{NETHACK_RNGLOG:'/rng.log'}}),referenceErrors=[],ref=await factory({printErr:line=>referenceErrors.push(line)});
 env.enableStdio();env.enableDecl(layouts.decl);env.enableDrawing(layouts.drawing);env.enableObjects(layouts.objects);env.call('objects','objects_globals_init');env.enableMonst(layouts.monst);env.call('monst','monst_globals_init');env.enableSerialization(layouts);env.enableRnd(layouts.rnd,{seed});env.call('rnd','rng_log_init');env.enableAddressPort('dungeon',{only:['ledger_no','maxledgerno']});env.enableObjectState(layouts);env.call('object-state','init_objects');env.enableObjectRecords(layouts);env.services.svc.context.ident=2;env.services.svc.context.current_fruit=19;env.enableItemInventory(layouts);
 ref._probe_init(seed);ref._probe_item_prepare();ref._probe_action(0,0,0,0);
 const {memory,ctypes}=env,js=[],native=[];let updates=0,growOnce=false;
 const update=env.functions.functionPointer(arg=>{assert.equal(arg,0);updates++;if(growOnce){const before=memory.buffer,p=memory.malloc(memory.buffer.byteLength+16*1024*1024);assert.ok(p);memory.free(p);assert.notEqual(memory.buffer,before);growOnce=false;}env.services.carrying(O.POT_HEALING);},'vi');
 ctypes.setField('struct window_procs',env.requireGlobal('windowprocs'),'win_update_inventory','void *',update);
 const nativeGet=(type,p,key,method)=>new DataView(ref.HEAPU8.buffer)[method](Number(p)+records[type].fields[key].offset,true);
 const token=(p,list)=>{p=Number(p);if(!p)return 0;const index=list.findIndex(q=>Number(q)===p);assert.ok(index>=0,'Unknown object identity '+p);return index+1;};
 function row(m,p,list){if(!p)return null;const bytes=Buffer.from(m.HEAPU8.slice(Number(p),Number(p)+records.obj.size));for(const key of ['nobj','v','cobj']){const at=records.obj.fields[key].offset;bytes.writeBigUInt64LE(BigInt(token(bytes.readBigUInt64LE(at),list)),at);}const extra=bytes.readBigUInt64LE(records.obj.fields.oextra.offset);assert.equal(extra,0n,'Unnamed ordinary profile must not hide extra ownership');return bytes;}
 function check(label){assert.deepEqual(js.map(p=>row(memory,p,js)),native.map(p=>row(ref,p,native)),label+' full object bytes');
  for(const [index,name,type,key]of [[0,'gi','instance_globals_i','invent'],[1,'go','instance_globals_o','objs_deleted']])assert.equal(token(ctypes.getField('struct '+type,env.requireGlobal(name),key,'void *'),js),token(nativeGet(type,ref._probe_item_global(index),key,'getBigUint64'),native),label+' root');
  assert.equal(env.services.gl.lastinvnr,nativeGet('instance_globals_l',ref._probe_item_global(2),'lastinvnr','getInt32'));
  assert.equal(env.services.svc.context.ident,nativeGet('context_info',Number(ref._probe_item_global(3))+records.instance_globals_saved_c.fields.context.offset,'ident','getUint32'));
  assert.equal(updates,ref._probe_item_updates());assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);comparisons++;
 }
 function create(i,type,init=1){assert.ok(!js[i]);js[i]=env.call('mkobj','mksobj',type,init,0);native[i]=BigInt(ref._probe_item_create(i,type,init,0));constructors++;check('mksobj '+type);}
 const actions={addinv:0,addinv_nomerge:1,freeinv:2,dealloc_obj_real:3,mergable:4,addinv_before:6,assigninvlet:9,reorder_invent:10};
 function call(name,i=0,j=0){const expected=ref._probe_item_action(actions[name],i,j);const args=name==='reorder_invent'?[]:name==='mergable'||name==='addinv_before'?[js[i],js[j]]:[js[i]];const actual=env.call(name==='dealloc_obj_real'?'mkobj':'invent',name,...args);if(['addinv','addinv_nomerge','addinv_before'].includes(name))assert.equal(token(actual,js),token(expected,native));if(name==='mergable')assert.equal(BigInt(actual),expected);if(name==='dealloc_obj_real'){assert.ok(!memory.live.has(js[i]));js[i]=native[i]=0;}check(name);return actual;}
 // Initialized and uninitialized ordinary constructors across the catalogue,
 // then real add/remove. This includes cursed/blessed/erosion RNG branches.
 for(let type=O.FIRST_OBJECT;type<O.NUM_OBJECTS;type++)if(!pending.has(type))for(const init of [0,1]){
  create(0,type,init);call('addinv');call('freeinv');call('dealloc_obj_real');
 }
 function field(global,type,key,value,method){ctypes.setField('struct '+type,env.requireGlobal(global),key,method==='setInt8'?'char':'int',value);const index={flags:4,program_state:6,iflags:7}[global];new DataView(ref.HEAPU8.buffer)[method](Number(ref._probe_item_global(index))+records[type].fields[key].offset,value,true);}
 // Active UI callback boundary, repeated letters, merging, no-merge and reentry.
 field('program_state','sinfo','in_moveloop',1,'setInt32');field('iflags','instance_flags','suppress_price',17,'setInt32');
 growOnce=true;ref._probe_item_force_growth();
 for(const fixed of [0,1]){
  field('flags','flag','invlet_constant',fixed,'setInt8');
  for(let i=0;i<55;i++){create(i,i%2?O.POT_HEALING:L.GOLD_PIECE,0);call('addinv_nomerge',i);}
  call('reorder_invent');
  for(let i=0;i<55;i++){call('freeinv',i);call('dealloc_obj_real',i);}
 }
 create(0,O.POT_HEALING,0);create(1,O.POT_HEALING,0);call('mergable',0,1);call('addinv',0);assert.equal(call('addinv',1),js[0]);
 // The merged-away allocation stays on the original deletion queue until
 // dobjsfree. Clear observer aliases before C frees it; never read freed C.
 const doomed=js[1];ref._probe_item_flush();env.call('mkobj','dobjsfree');assert.ok(!memory.live.has(doomed));js[1]=native[1]=0;check('deletion queue flush');
 call('freeinv',0);call('dealloc_obj_real',0);
 assert.equal(env.services.iflags.suppress_price,17);assert.equal(updates,ref._probe_item_updates());callbacks+=updates;
 assert.equal(env.diagnostics.join(''),(()=>{const p=Number(ref._probe_diagnostics());let end=p;while(ref.HEAPU8[end])end++;return Buffer.from(ref.HEAPU8.slice(p,end)).toString('latin1');})());
 assert.equal(Buffer.from(env.filesystem.readFile('/rng.log')).toString('latin1'),Buffer.from(ref.FS.readFile('/rng.log')).toString('latin1'),'exact RNG stream and caller logs');comparisons+=2;
 assert.ok(memory.generation>0);
 // Deliberately cross a declared unfinished boundary on both sides. The C
 // reference must abort and JS must report the missing owner; neither may
 // fabricate a successful timer or silently skip the constructor.
 assert.throws(()=>env.call('mkobj','mksobj',L.GLOB_OF_GRAY_OOZE,1,0),/Unresolved standalone function obj_to_any/);
 assert.throws(()=>ref._probe_item_create(0,L.GLOB_OF_GRAY_OOZE,1,0));
 assert.ok(referenceErrors.join('\n').includes('Unconnected C boundary: obj_to_any'));
 assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);comparisons+=2;
}
console.log(`PASS: ${comparisons} original-C item/inventory state comparisons, ${constructors} constructors, ${callbacks} real update callbacks; ${pendingNames.length} special-item families remain explicitly pending.`);
