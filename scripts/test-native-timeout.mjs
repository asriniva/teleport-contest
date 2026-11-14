// Actual production TIMEOUT/state/events against complete original C. Component
// actions start from genuine main initialization; no substitute game callbacks.
import fs from 'node:fs';import assert from 'node:assert/strict';import crypto from 'node:crypto';
import {parse} from 'acorn';
import {runFullOriginalC} from './full-original-c-run.mjs';
import {runStandaloneProgram} from './run-standalone-program.mjs';
import {worldGraph} from './restoration-world-graph.mjs';
import {encodeRecorderScreen} from '../js/wasm-replay-support.js';
import {C,R as runtimeRecords,T} from '../js/c-runtime/context.js';
import {nativeStateFor} from '../js/nethack/native/state-bridge.js';
const read=p=>JSON.parse(fs.readFileSync(p)),layouts=read('js/wasm/tu-layouts.json'),L={...layouts.mkobj,...layouts.timeout},M=layouts.mkobj,R=read('js/nethack/records.json').records;
let checks=0,actions=0;const equal=(a,b,label)=>{assert.deepEqual(a,b,label);checks++;};
function policy(node){
 if(Array.isArray(node))return node.map(policy);if(!node||typeof node!=='object')return node;
 if(node.type==='CallExpression'&&node.callee.type==='MemberExpression'&&node.callee.object.name==='C'&&node.callee.property.name==='callLocal')node={...node,callee:node.arguments[0],arguments:node.arguments.slice(1)};
 if(node.type==='ForStatement'&&node.test?.left?.object?.name==='upp'){
  const loop=parse('for (let propertyIndex = 0; propertyIndex < C.PROP_COUNT; propertyIndex++) { upp = C.u.uprops[propertyIndex]; }',{ecmaVersion:'latest'}).body[0];
  loop.body.body.push(node.body);node=loop;
 }
 if(node.type==='MemberExpression'&&node.object.name==='upp'&&node.property.name==='index')node={type:'Identifier',name:'propertyIndex'};
 return Object.fromEntries(Object.entries(node).filter(([k])=>!['start','end','raw'].includes(k)).map(([k,v])=>[k,policy(v)]));
}
const old=parse(fs.readFileSync('js/ported/timeout.js','utf8'),{ecmaVersion:'latest',sourceType:'module'}),next=parse(fs.readFileSync('js/nethack/native/timeout.js','utf8'),{ecmaVersion:'latest',sourceType:'module'});
const expected=old.body.filter(n=>n.type!=='ImportDeclaration').map(n=>n.type==='ExportNamedDeclaration'?n.declaration:n);
equal(policy(next.body[0].declaration.body.body.slice(0,-1)),policy(expected),'all policy statements and RNG ordering, with explicit native property iteration');
const dir='.cache/full-original-c-v1',input={seed:1,timezone:'UTC',options:'OPTIONS=!news\n',keys:'  n'};
let module,env,program;const cOutput=[],cKeys=[],jKeys=[];
const c=await runFullOriginalC(dir,{...input,observeRuntime:r=>{module=r.module;const tty=module.FS.getStream(1).tty,put=tty.ops.put_char;tty.ops={...tty.ops,put_char(t,ch){if(ch!==null)cOutput.push(ch);return put(t,ch);}};}});
const j=runStandaloneProgram(dir+'/assets',{...input,observeRuntime:r=>{env=r.environment;program=r.program;}});
for(const k of ['status','state','snapshots','rngLog','displayRngLog','stdout','stderr'])equal(j[k],c[k],'actual main '+k);
const root={};function text(heap,p){p=Number(p);if(!p)return null;let end=p;while(heap[end])end++;return Buffer.from(heap.slice(p,end)).toString('latin1');}
for(let i=0;i<module._full_global_count();i++)root[text(module.HEAPU8,module._full_global_name(i))]=Number(module._full_global_address(i));
const field=(type,name)=>R[type].fields[name].offset,cv=()=>new DataView(module.HEAPU8.buffer),jv=()=>env.memory.view;
function pure(fn){const names=['WebAssembly','fetch','XMLHttpRequest','WebSocket','Worker'],saved=names.map(k=>Object.getOwnPropertyDescriptor(globalThis,k)),deny=()=>{throw Error('Forbidden production Wasm/network in native TIMEOUT');};for(const k of names)Object.defineProperty(globalThis,k,{configurable:true,value:k==='WebAssembly'?new Proxy({},{get:deny}):deny});try{return fn();}finally{names.forEach((k,i)=>saved[i]?Object.defineProperty(globalThis,k,saved[i]):delete globalThis[k]);equal([C,runtimeRecords,T],[undefined,undefined,undefined],'native call leaves no C execution context');}}
const services=new Proxy(env.services,{get:(o,k)=>{const value=Reflect.get(o,k);return typeof value==='function'?(...args)=>pure(()=>value(...args)):value;}}),owner=nativeStateFor(env),timers=env.start('timers').environment,callbackIds=timers.timeout_funcs.map(r=>[r.f,r.cleanup]);
equal(timers.u,owner.nativeRecords.record('struct you',env.requireGlobal('u')),'canonical hero');
for(const name of Object.keys(env.start('timers').namespace))equal(env.start('timers').namespace[name].nativeDirect,true,'native gameplay entry '+name);
// Component messages may use the actual More input boundary after main stops.
module.teleportReadKey=()=>{assert.ok(cKeys.length<256);cKeys.push(32);return 32;};
const keyEntry=env.start('terminal-key-input'),oldKey=keyEntry.namespace.teleport_getch,newKey=()=>{assert.ok(jKeys.length<256);jKeys.push(32);return 32;};Object.assign(newKey,oldKey);keyEntry.namespace.teleport_getch=newKey;
const jroot=env.requireGlobal('gt')+field('instance_globals_t','timer_base'),croot=root.gt+field('instance_globals_t','timer_base');
const jmoves=env.requireGlobal('svm')+field('instance_globals_saved_m','moves'),cmoves=root.svm+field('instance_globals_saved_m','moves');
const jid=env.requireGlobal('svt')+field('instance_globals_saved_t','timer_id'),cid=root.svt+field('instance_globals_saved_t','timer_id');
const objects=[];
function queue(heap,at,isC){const v=new DataView(heap.buffer),seen=new Set(),out=[];let p=Number(v.getBigUint64(at,true));while(p){assert.ok(!seen.has(p),'acyclic queue');seen.add(p);const b=Buffer.from(heap.slice(p,p+R.fe.size)),next=Number(b.readBigUInt64LE(field('fe','next')));b.writeBigUInt64LE(next?1n:0n,field('fe','next'));const raw=b.readBigUInt64LE(field('fe','arg'));let argument=v.getInt16(p+field('fe','kind'),true)===L.TIMER_OBJECT?'object-id:'+v.getUint32(Number(raw)+field('obj','o_id'),true):'bits:'+raw.toString(16);const index=objects.findIndex(o=>BigInt(o[isC?'c':'j'])===raw);if(index>=0)argument='object:'+index;b.writeBigUInt64LE(0n,field('fe','arg'));out.push({bytes:b.toString('hex'),argument});p=next;}return out;}
const log=(read,p)=>{try{return Buffer.from(read(p)).toString();}catch(e){if(p==='/rng-display.log')return null;throw e;}};
function compare(label,{world=false}={}){
 equal(queue(env.memory.HEAPU8,jroot,false),queue(module.HEAPU8,croot,true),label+' ordered queue bytes/arguments');
 equal(jv().getBigUint64(jid,true),cv().getBigUint64(cid,true),label+' unsigned timer ID');
 for(const o of objects){const jb=Buffer.from(env.memory.HEAPU8.slice(o.j,o.j+R.obj.size)),cb=Buffer.from(module.HEAPU8.slice(o.c,o.c+R.obj.size));for(const b of [jb,cb])for(const name of ['nobj','v','cobj','oextra']){const f=R.obj.fields[name];if(f)b.writeBigUInt64LE(b.readBigUInt64LE(f.offset)?1n:0n,f.offset);}equal(jb,cb,label+' object '+o.id);}
 for(const p of ['/rng.log','/rng-display.log'])equal(log(p=>env.filesystem.readFile(p),p),log(p=>module.FS.readFile(p),p),label+' ordered '+p);
 const rng=env.state('rnd').rnglist.map(({rng_state:s})=>{const l=layouts.rnd,b=Buffer.alloc(l.size);b.writeBigUInt64LE(BigInt(s.n),l.n);for(const k of ['r','m'])for(let i=0;i<256;i++)b.writeBigUInt64LE(s[k][i],l[k]+i*8);for(const k of ['a','b','c'])b.writeBigUInt64LE(s[k],l[k]);return b;});
 equal(rng,[0,1].map(i=>{const p=Number(module._full_rng_state(i));return Buffer.from(module.HEAPU8.slice(p,p+layouts.rnd.size));}),label+' full ISAAC states');
 equal(timers.timeout_funcs.map(r=>[r.f,r.cleanup]),callbackIds,label+' unchanged callback IDs');
 if(world)equal(worldGraph({environment:env}),worldGraph({module}),label+' entire reachable world');actions++;
}
function call(name,ja=[],ca=ja,{world=false,returns=true}={}){const a=services[name](...ja),b=module['_'+name](...ca);if(returns)equal(typeof a==='bigint'?a:typeof b==='bigint'?BigInt(a):a,b,name+' return');compare(name,{world});return a;}
function create(type){const j=services.mksobj(type,0,0),c=Number(module._mksobj(type,0,0));const id=jv().getUint32(j+field('obj','o_id'),true);equal(id,cv().getUint32(c+field('obj','o_id'),true),'real object creation');const row={j,c,id};objects.push(row);compare('create');return row;}
const args=Array.from({length:4},()=>({j:env.memory.calloc(1,8),c:Number(module._malloc(8n))}));
function argument(index,jbits,cbits=jbits){jv().setBigUint64(args[index].j,BigInt.asUintN(64,BigInt(jbits)),true);cv().setBigUint64(args[index].c,BigInt.asUintN(64,BigInt(cbits)),true);}
function start(index,when,kind,fn){return call('start_timer',[when,kind,fn,args[index].j],[when,kind,fn,BigInt(args[index].c)]);}
function stop(index,fn){return call('stop_timer',[fn,args[index].j],[fn,BigInt(args[index].c)]);}
function peek(index,fn){return call('peek_timer',[fn,args[index].j],[fn,BigInt(args[index].c)]);}
compare('initial',{world:true});
for(let i=0;i<3;i++){const o=create(M.EGG);argument(i,o.j,o.c);}
const unionA=services.obj_to_any(objects[0].j),unionB=services.obj_to_any(objects[1].j),cuA=module._obj_to_any(BigInt(objects[0].c)),cuB=module._obj_to_any(BigInt(objects[1].c));equal(unionA,unionB,'stable shared union identity');equal(unionB.a_obj,owner.nativeRecords.record('struct obj',objects[1].j),'native shared union aliases the second actor item');equal(cuA,cuB,'original shared union identity');
for(const [when,fn]of [[9n,L.ROT_CORPSE],[2n,L.REVIVE_MON],[9n,L.ZOMBIFY_MON]])start(0,when,L.TIMER_OBJECT,fn);
peek(0,L.ROT_CORPSE);call('obj_move_timers',[objects[0].j,objects[1].j],[BigInt(objects[0].c),BigInt(objects[1].c)],{returns:false});call('obj_split_timers',[objects[1].j,objects[2].j],[BigInt(objects[1].c),BigInt(objects[2].c)],{returns:false});for(const o of objects.slice(0,3))call('obj_stop_timers',[o.j],[BigInt(o.c)],{returns:false});
argument(3,0xf123456789abcdefn);start(3,99n,L.TIMER_GLOBAL,L.ROT_CORPSE);peek(3,L.ROT_CORPSE);stop(3,L.ROT_CORPSE);
const fns=[L.ROT_ORGANIC,L.ROT_CORPSE,L.REVIVE_MON,L.ZOMBIFY_MON,L.HATCH_EGG,L.FIG_TRANSFORM,L.SHRINK_GLOB];let random=0x31415926;const nextRandom=()=>{random^=random<<13;random^=random>>>17;random^=random<<5;return random>>>0;};
for(let i=0;i<300;i++){const a=nextRandom()%3,fn=fns[nextRandom()%fns.length],o=objects[a];switch(nextRandom()%5){case 0:stop(a,fn);start(a,BigInt(1+nextRandom()%500),L.TIMER_OBJECT,fn);break;case 1:stop(a,fn);break;case 2:peek(a,fn);break;case 3:call('obj_stop_timers',[o.j],[BigInt(o.c)],{returns:false});break;case 4:call('obj_has_timer',[o.j,fn],[BigInt(o.c),fn]);break;}}
for(const o of objects)call('obj_stop_timers',[o.j],[BigInt(o.c)],{returns:false});
jv().setBigUint64(jid,0xffffffffffffffffn,true);cv().setBigUint64(cid,0xffffffffffffffffn,true);start(0,3n,L.TIMER_OBJECT,L.ROT_ORGANIC);start(0,3n,L.TIMER_OBJECT,L.REVIVE_MON);call('obj_stop_timers',[objects[0].j],[BigInt(objects[0].c)],{returns:false});
const previous=env.memory.buffer,growth=env.memory.malloc(env.memory.buffer.byteLength+16*1024*1024);env.memory.free(growth);assert.notEqual(env.memory.buffer,previous);compare('native views after actual heap growth');
call('attach_egg_hatch_timeout',[objects[0].j,2n],[BigInt(objects[0].c),2n],{returns:false});const when=jv().getBigInt64(jmoves,true)+2n;jv().setBigInt64(jmoves,when,true);cv().setBigInt64(cmoves,when,true);call('run_timers',[],[],{returns:false});
function prop(name,value,extrinsic=0n){for(const [v,p]of [[jv(),env.requireGlobal('u')],[cv(),root.u]]){const at=p+field('you','uprops')+L[name]*R.prop.size;v.setBigInt64(at+field('prop','intrinsic'),value,true);v.setBigInt64(at+field('prop','extrinsic'),extrinsic,true);}}
function step(label){const when=jv().getBigInt64(jmoves,true)+1n;jv().setBigInt64(jmoves,when,true);cv().setBigInt64(cmoves,when,true);call('nh_timeout',[],[],{returns:false,world:true});}
prop('FAST',5n);prop('FIRE_RES',4n);step('nonexpired');step('nonexpired2');
for(const name of ['FAST','FIRE_RES','CONFUSION','STUNNED','DEAF','BLINDED','HALLUC']){prop(name,1n);step(name+' expiry');}
prop('SLEEPY',1n);prop('SLEEP_RES',BigInt(L.FROMOUTSIDE));step('resisted sleep');prop('SLEEPY',0n);
// Real light/timer event expiry and cleanup. Both engines create and place the
// same oil objects; the actual original burn callback runs when due.
for(let i=0;i<2;i++){const o=create(L.POT_OIL);jv().setBigInt64(o.j+field('obj','age'),5n,true);cv().setBigInt64(o.c+field('obj','age'),5n,true);call('place_object',[o.j,services.u.ux,services.u.uy],[BigInt(o.c),services.u.ux,services.u.uy],{returns:false});call('begin_burn',[o.j,0],[BigInt(o.c),0],{returns:false,world:true});}
// Removed oil objects may be freed by real callbacks, so world traversal is the
// authoritative post-expiry comparison rather than dereferencing saved handles.
objects.splice(3);
for(let i=0;i<6;i++)step('burn expiry '+i);
const lamp=create(L.OIL_LAMP);jv().setBigInt64(lamp.j+field('obj','age'),160n,true);cv().setBigInt64(lamp.c+field('obj','age'),160n,true);call('place_object',[lamp.j,services.u.ux,services.u.uy],[BigInt(lamp.c),services.u.ux,services.u.uy],{returns:false});call('begin_burn',[lamp.j,0],[BigInt(lamp.c),0],{returns:false,world:true});step('lamp');call('end_burn',[lamp.j,1],[BigInt(lamp.c),1],{returns:false,world:true});
// Viable eggs connect native timer expiry to real placement, monster creation,
// visibility, naming and pet state. Require a new live actor, not merely expiry.
const monCount=()=>{let n=0;for(let m=timers.svl.level.monlist;m;m=m.nmon)n++;return n;};
for(const [species,yours]of [[L.PM_GIANT_ANT,0],[L.PM_BABY_GOLD_DRAGON,1]]){
 const egg=create(M.EGG);for(const [v,p]of [[jv(),egg.j],[cv(),egg.c]]){v.setInt32(p+field('obj','corpsenm'),species,true);v.setBigInt64(p+field('obj','quan'),1n,true);v.setInt8(p+field('obj','spe'),yours);}
 call('place_object',[egg.j,services.u.ux,services.u.uy],[BigInt(egg.c),services.u.ux,services.u.uy],{returns:false});call('attach_egg_hatch_timeout',[egg.j,1n],[BigInt(egg.c),1n],{returns:false});objects.pop();const before=monCount();step('real viable egg '+species);assert.ok(monCount()>before,'real hatch creates a live monster');checks++;
}
// Save/restore is the deliberate pointer-shaped boundary. Compare its actual
// bytes, normalizing only next links to their already observed queue identities.
argument(3,(12<<16)|8);start(3,100n,L.TIMER_LEVEL,L.MELT_ICE_AWAY);
const links=(heap,at)=>{const v=new DataView(heap.buffer),map=new Map([[0,0]]);let p=Number(v.getBigUint64(at,true));while(p){assert.ok(!map.has(p));map.set(p,map.size);p=Number(v.getBigUint64(p+field('fe','next'),true));}return map;};
for(const name of ['spot_time_expires','spot_time_left'])call(name,[12,8,L.MELT_ICE_AWAY]);
const jl=links(env.memory.HEAPU8,jroot),cl=links(module.HEAPU8,croot),size=layouts.sfbase.nhfileSize,file=env.memory.calloc(1,size),cfile=Number(module._malloc(BigInt(size))),filename='/native-timeout-checkpoint',jfd=services.open(filename,578,0o600),cfd=module.FS.open(filename,'w+',0o600).fd;
module.HEAPU8.fill(0,cfile,cfile+size);
for(const [v,p,fd]of [[jv(),file,jfd],[cv(),cfile,cfd]]){for(const [key,value]of [['fd',fd],['mode',layouts.sfbase.WRITING|L.FREEING],['fnidx',layouts.sfbase.historical]])v.setInt32(p+field('nh_file',key),value,true);v.setInt8(p+field('nh_file','structlevel'),1);}
call('save_timers',[file,L.RANGE_LEVEL],[BigInt(cfile),L.RANGE_LEVEL],{returns:false});services.bflush(jfd);module._bflush(cfd);
const normalizeFile=(data,map)=>{const b=Buffer.from(data),count=b.readInt32LE(0);equal(b.length,4+count*R.fe.size,'serialized queue length');for(let i=0;i<count;i++){const at=4+i*R.fe.size+field('fe','next'),p=Number(b.readBigUInt64LE(at));assert.ok(map.has(p),'serialized next was an observed source queue link');b.writeBigUInt64LE(BigInt(map.get(p)),at);}return b;};
equal(normalizeFile(env.filesystem.readFile(filename),jl),normalizeFile(module.FS.readFile(filename),cl),'complete actual serialized timer bytes');
services.lseek(jfd,0,0);module.FS.llseek(module.FS.getStream(cfd),0,0);jv().setInt32(file+field('nh_file','mode'),0,true);cv().setInt32(cfile+field('nh_file','mode'),0,true);
call('restore_timers',[file,L.RANGE_LEVEL,0n],[BigInt(cfile),L.RANGE_LEVEL,0n],{returns:false});call('relink_timers',[0],[0],{returns:false});call('spot_stop_timers',[12,8,L.MELT_ICE_AWAY],[12,8,L.MELT_ICE_AWAY],{returns:false,world:true});
services.bclose(jfd);module._bclose(cfd);env.memory.free(file);module._free(BigInt(cfile));
call('timer_sanity_check',[],[],{returns:false,world:true});call('do_storms',[],[],{returns:false,world:true});
const jp=env.memory.calloc(1,8),cp=Number(module._malloc(8n));
for(let i=-1;i<timers.propertynames.length+2;i++){const a=services.property_by_index(i,jp),b=module._property_by_index(i,BigInt(cp));equal(text(env.memory.HEAPU8,a),text(module.HEAPU8,b),'public property name '+i);equal(jv().getInt32(jp,true),cv().getInt32(cp,true),'public property index copyback '+i);}
const stats=env.memory.calloc(1,128),cstats=Number(module._malloc(128n)),bytes=env.memory.calloc(1,8),cbytes=Number(module._malloc(8n)),format='timer bytes %ld',cf=Number(module._malloc(BigInt(format.length+1)));module.HEAPU8.set(Buffer.from(format+'\0'),cf);
services.timer_stats(format,stats,jp,bytes);module._timer_stats(BigInt(cf),BigInt(cstats),BigInt(cp),BigInt(cbytes));equal([text(env.memory.HEAPU8,stats),jv().getBigInt64(jp,true),jv().getBigInt64(bytes,true)],[text(module.HEAPU8,cstats),cv().getBigInt64(cp,true),cv().getBigInt64(cbytes,true)],'real timer_stats formatting and count/size copyback');
for(const wake of [0,1]){call('fall_asleep',[-3,wake],[-3,wake],{returns:false,world:true});equal(jv().getBigInt64(env.requireGlobal('gm')+field('instance_globals_m','multi'),true),cv().getBigInt64(root.gm+field('instance_globals_m','multi'),true),'sleep multi lifetime');for(const [global,type,key]of [['gm','instance_globals_m','multi_reason'],['gn','instance_globals_n','nomovemsg']])equal(text(env.memory.HEAPU8,jv().getBigUint64(env.requireGlobal(global)+field(type,key),true)),text(module.HEAPU8,cv().getBigUint64(root[global]+field(type,key),true)),'sleep '+key);}
services.tty_nhbell();module._tty_nhbell();
equal(Buffer.from(program.stdio.captured(1)),Buffer.from(cOutput),'all actual terminal bytes');equal(program.terminal.frames,c.frames.map(({screen,cursor,animation})=>({screen:encodeRecorderScreen(screen),cursor:[...cursor,1],animation})),'all recorder frames');equal(jKeys,cKeys,'actual More input order');
const sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex');
const result={passed:true,checks,actions,policyFunctions:expected.filter(n=>n.type==='FunctionDeclaration').length,referenceReceiptSha256:sha(dir+'/receipt.json'),scope:'Original full-main worlds; native queue ordering/move/split/opaque union/ID wrap/growth and public property/spot/stats/sleep APIs, sterile and viable eggs with actual hostile/tame monster creation, native timed property scan and real POTION expiry, real burn/light expiry/cleanup, complete ordered RNG/state and terminal/frame equality. Actual nonempty timer save/release/restore/relink bytes and state checked. Fatal status and remaining foreign event branches need separate acceptance.'};
fs.writeFileSync('.cache/native-timeout-evidence.json',JSON.stringify(result,null,2)+'\n');console.log(JSON.stringify(result));
