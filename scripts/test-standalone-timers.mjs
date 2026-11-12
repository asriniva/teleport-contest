import {layoutSourceSha} from './nethack-layout.mjs';
// Original C TIMEOUT/HACK/MKOBJ versus unchanged source functions on CMemory.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import crypto from 'node:crypto';
import {pathToFileURL} from 'node:url';
import {createStandaloneEnvironment} from '../js/nethack/environment.js';
import {C,R,T} from '../js/c-runtime/context.js';
const directory=path.resolve(process.env.STANDALONE_TIMERS_ORACLE||'.cache/standalone-timers');
const receipt=JSON.parse(fs.readFileSync(path.join(directory,'receipt.json')));
const sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex');
for(const [p,h]of Object.entries(receipt.sourceSha256))assert.equal(layoutSourceSha(p,h),h,'Changed C input '+p);
for(const [p,h]of Object.entries(receipt.artifactSha256))assert.equal(sha(path.join(directory,p)),h,'Changed C artifact '+p);
const {default:factory}=await import(pathToFileURL(path.join(directory,'reference.mjs')));
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),L={...layouts.mkobj,...layouts.timeout},M=layouts.mkobj;
const metadata=JSON.parse(fs.readFileSync('js/nethack/records.json')).records;
let comparisons=0;
for(const seed of [1n,0x12345678n,0xffffffffffffffffn]){
 const env=createStandaloneEnvironment({initialBytes:1024,maximumBytes:64*1024*1024,environment:{NETHACK_RNGLOG:'/rng.log'}}),errors=[],ref=await factory({printErr:line=>errors.push(line)});
 env.enableStdio();env.enableDecl(layouts.decl);env.enableDrawing(layouts.drawing);env.enableObjects(layouts.objects);env.call('objects','objects_globals_init');env.enableMonst(layouts.monst);env.call('monst','monst_globals_init');env.enableSerialization(layouts);env.enableRnd(layouts.rnd,{seed});env.call('rnd','rng_log_init');env.enableAddressPort('dungeon',{only:['ledger_no','maxledgerno']});env.enableObjectState(layouts);env.call('object-state','init_objects');env.enableObjectRecords(layouts);env.services.svc.context.ident=2;env.services.svc.context.current_fruit=19;env.enableItemInventory(layouts);env.enableTimers(layouts);
 ref._probe_init(seed);ref._probe_item_prepare();ref._probe_action(0,0,0,0);
 const {memory,ctypes}=env,js=[],native=[],args=Array.from({length:4},()=>memory.calloc(1,8));
 const root=ctypes.locate('struct instance_globals_t',env.requireGlobal('gt'),'timer_base').at;
 const id=ctypes.locate('struct instance_globals_saved_t',env.requireGlobal('svt'),'timer_id').at;
 const moves=ctypes.locate('struct instance_globals_saved_m',env.requireGlobal('svm'),'moves').at;
 const info=[metadata.fe.size,metadata.fe.alignment,...['next','timeout','tid','kind','func_index','arg'].map(k=>metadata.fe.fields[k].offset),ctypes.size('union any')];
 info.forEach((value,i)=>assert.equal(BigInt(value),ref._probe_timer_layout(i),'timer ABI '+i));
 const token=(bits,list)=>{bits=BigInt.asUintN(64,BigInt(bits));const index=list.findIndex(p=>p&&BigInt(p)===bits);return index>=0?'object:'+index:'bits:'+bits.toString(16);};
 const readNative=(type,p,key,method)=>new DataView(ref.HEAPU8.buffer)[method](Number(p)+metadata[type].fields[key].offset,true);
 function snapshot(m,list,start){
  const dv=new DataView(m.HEAPU8.buffer),rows=[];let p=Number(dv.getBigUint64(start,true)),seen=new Set();
  while(p){assert.ok(!seen.has(p),'cyclic timer queue');seen.add(p);const bytes=Buffer.from(m.HEAPU8.slice(p,p+metadata.fe.size));
   const next=Number(bytes.readBigUInt64LE(metadata.fe.fields.next.offset)),arg=bytes.readBigUInt64LE(metadata.fe.fields.arg.offset);
   bytes.writeBigUInt64LE(next?1n:0n,metadata.fe.fields.next.offset);bytes.writeBigUInt64LE(0n,metadata.fe.fields.arg.offset);
   rows.push({bytes,arg:token(arg,list)});p=next;
  }
  return rows;
 }
 function diagnostic(){let p=Number(ref._probe_diagnostics()),end=p;while(ref.HEAPU8[end])end++;return Buffer.from(ref.HEAPU8.slice(p,end)).toString('latin1');}
 function check(label){
  assert.deepEqual(snapshot(memory,js,root),snapshot(ref,native,Number(ref._probe_timer_global(0))),label+' queue');
  assert.equal(memory.view.getBigUint64(id,true),new DataView(ref.HEAPU8.buffer).getBigUint64(Number(ref._probe_timer_global(1)),true),label+' id');
  for(let i=0;i<js.length;i++)if(js[i])assert.deepEqual(memory.readBytes(js[i],metadata.obj.size),ref.HEAPU8.slice(Number(native[i]),Number(native[i])+metadata.obj.size),label+' object '+i);
  assert.equal(env.diagnostics.join(''),diagnostic(),label+' diagnostics');assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);comparisons++;
 }
 function create(i,type,init=0){js[i]=env.call('mkobj','mksobj',type,init,0);native[i]=BigInt(ref._probe_item_create(i,type,init,0));check('create '+type);}
 function argument(index,bits,nativeBits=bits){memory.view.setBigUint64(args[index],BigInt.asUintN(64,BigInt(bits)),true);new DataView(ref.HEAPU8.buffer).setBigUint64(Number(ref._probe_timer_arg(index)),BigInt.asUintN(64,BigInt(nativeBits)),true);}
 function op(name,{when=0n,kind=L.TIMER_OBJECT,fn=L.ROT_CORPSE,arg=0,a=0,b=1}={}){
  const codes={start_timer:0,stop_timer:1,peek_timer:2,obj_stop_timers:3,obj_move_timers:4,obj_split_timers:5,obj_has_timer:6,run_timers:7,attach_egg_hatch_timeout:8,attach_fig_transform_timeout:9,kill_egg:10};
  const expected=ref._probe_timer_op(codes[name],BigInt(when),kind,fn,arg,a,b);
  const parameters={start_timer:[when,kind,fn,args[arg]],stop_timer:[fn,args[arg]],peek_timer:[fn,args[arg]],obj_stop_timers:[js[a]],obj_move_timers:[js[a],js[b]],obj_split_timers:[js[a],js[b]],obj_has_timer:[js[a],fn],run_timers:[],attach_egg_hatch_timeout:[js[a],when],attach_fig_transform_timeout:[js[a]],kill_egg:[js[a]]};
  const actual=env.call('timers',name,...parameters[name]);
  if(['start_timer','stop_timer','peek_timer','obj_has_timer'].includes(name))assert.equal(BigInt(actual),expected,name+' return');
  check(name);return actual;
 }
 for(let i=0;i<3;i++)create(i,M.EGG);
 argument(0,js[0],native[0]);argument(1,js[1],native[1]);argument(2,js[2],native[2]);
 memory.view.setBigInt64(moves,200n,true);new DataView(ref.HEAPU8.buffer).setBigInt64(Number(ref._probe_timer_global(2)),200n,true);
 // Sorted insertion, duplicate refusal, per-type/argument selection and
 // stable state after reallocating the JS heap with live timer views.
 for(const [when,fn]of [[9n,L.ROT_CORPSE],[2n,L.REVIVE_MON],[9n,L.ZOMBIFY_MON]])op('start_timer',{when,fn});
 op('start_timer',{when:19n,fn:L.ROT_CORPSE});op('peek_timer');op('obj_has_timer');
 const node=Number(memory.view.getBigUint64(root,true)),cnode=new DataView(ref.HEAPU8.buffer).getBigUint64(Number(ref._probe_timer_global(0)),true);
 for(const bit of [0,1,2,3,255]){ctypes.setField('struct fe',node,'needs_fixup','unsigned int',bit);assert.equal(ctypes.getField('struct fe',node,'needs_fixup','unsigned int'),ref._probe_timer_fixup(cnode,bit));check('measured bitfield');}
 ctypes.setField('struct fe',node,'needs_fixup','unsigned int',0);ref._probe_timer_fixup(cnode,0);
 const prior=memory.buffer,growth=memory.malloc(memory.buffer.byteLength+16*1024*1024);assert.ok(growth);memory.free(growth);assert.notEqual(memory.buffer,prior);check('growth');
 op('obj_move_timers');op('obj_split_timers',{a:1,b:2});op('obj_stop_timers',{a:1});op('obj_stop_timers',{a:2});
 // A C union may carry opaque 64-bit data rather than a dereferenceable
 // address; pointer comparisons must preserve all bits, including bit 63.
 argument(3,0xf123456789abcdefn);
 op('start_timer',{kind:L.TIMER_GLOBAL,arg:3,when:99n});op('start_timer',{kind:L.TIMER_GLOBAL,arg:3,when:100n});op('peek_timer',{arg:3});op('stop_timer',{arg:3});
 // Repeat queue operations against original C, never using expected outputs
 // from the implementation. Cleanup-bearing burn events are a later group.
 let random=0x31415926;
 const next=()=>{random^=random<<13;random^=random>>>17;random^=random<<5;return random>>>0;};
 const fns=[L.ROT_ORGANIC,L.ROT_CORPSE,L.REVIVE_MON,L.ZOMBIFY_MON,L.HATCH_EGG,L.FIG_TRANSFORM,L.SHRINK_GLOB];
 for(let i=0;i<400;i++){const a=next()%3,fn=fns[next()%fns.length];switch(next()%5){case 0:op('start_timer',{arg:a,fn,when:BigInt(1+next()%500)});break;case 1:op('stop_timer',{arg:a,fn});break;case 2:op('peek_timer',{arg:a,fn});break;case 3:op('obj_stop_timers',{a});break;case 4:op('obj_has_timer',{a,fn});break;}}
 for(let a=0;a<3;a++)op('obj_stop_timers',{a});
 // Real attach policies and a real elapsed sterile-egg callback, not a
 // success callback substituted for hatching or monster creation.
 op('attach_egg_hatch_timeout',{a:0});op('kill_egg',{a:0});op('attach_fig_transform_timeout',{a:1});op('obj_stop_timers',{a:1});
 op('attach_egg_hatch_timeout',{a:0,when:2n});memory.view.setBigInt64(moves,202n,true);new DataView(ref.HEAPU8.buffer).setBigInt64(Number(ref._probe_timer_global(2)),202n,true);
 op('run_timers');
 // Timer IDs are unsigned source storage even though a source cast passes
 // through long; original raw record bytes remain exact at wraparound.
 memory.view.setBigUint64(id,0xffffffffffffffffn,true);new DataView(ref.HEAPU8.buffer).setBigUint64(Number(ref._probe_timer_global(1)),0xffffffffffffffffn,true);
 op('start_timer',{when:3n,fn:L.ROT_ORGANIC});op('start_timer',{when:3n,fn:L.REVIVE_MON});op('obj_stop_timers');
 // Four previously missing special constructors now create their real timers.
 for(const type of [M.GLOB_OF_GRAY_OOZE,M.GLOB_OF_BROWN_PUDDING,M.GLOB_OF_GREEN_SLIME,M.GLOB_OF_BLACK_PUDDING]){
  create(3,type,1);op('obj_stop_timers',{a:3});env.call('mkobj','dealloc_obj_real',js[3]);ref._probe_item_action(3,3,0);js[3]=native[3]=0;check('glob cleanup');
 }
 // Shared union storage matches the original obj_to_any lifetime/alias ABI.
 const p0=env.services.obj_to_any(js[0]),p1=env.services.obj_to_any(js[1]);assert.equal(p0.address,p1.address);assert.equal(p0.a_obj.address,js[1]);comparisons++;
 assert.equal(Buffer.from(env.filesystem.readFile('/rng.log')).toString('latin1'),Buffer.from(ref.FS.readFile('/rng.log')).toString('latin1'),'RNG log/continuation');comparisons++;
 for(let i=0;i<3;i++){env.call('mkobj','dealloc_obj_real',js[i]);ref._probe_item_action(3,i,0);js[i]=native[i]=0;}
 assert.equal(memory.view.getBigUint64(root,true),0n);check('final queue empty');
}
console.log(`PASS: ${comparisons} original-C timer/any/object comparisons, queue ordering/duplicates/move/split/stop/attach/sterile expiry, opaque uint64 bits, ID wrap, growth and four glob constructors. Other event/world owners remain explicit dependencies.`);
