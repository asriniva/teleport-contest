// Native REGION policies on actual source-initialized worlds, against all-C.
import fs from 'node:fs';import assert from 'node:assert/strict';import crypto from 'node:crypto';import {parse} from 'acorn';
import {runFullOriginalC} from './full-original-c-run.mjs';import {runStandaloneProgram} from './run-standalone-program.mjs';
import {worldGraph} from './restoration-world-graph.mjs';import {elementalRegions} from './elemental-region-world.mjs';import {encodeRecorderScreen} from '../js/wasm-replay-support.js';
import {nativeStateFor} from '../js/nethack/native/state-bridge.js';import {nativeSpatialFor} from '../js/nethack/native/spatial-state.js';import {C,R,T} from '../js/c-runtime/context.js';
let checks=0,actions=0;const equal=(a,b,label)=>{assert.deepEqual(a,b,label);checks++;},same=(a,b,label)=>{assert.strictEqual(a,b,label);checks++;};
const clean=n=>Array.isArray(n)?n.map(clean):n&&typeof n==='object'?Object.fromEntries(Object.entries(n).filter(([k])=>!['start','end','raw'].includes(k)).map(([k,v])=>[k,clean(v)])):n;
const old=parse(fs.readFileSync('js/ported/region.js','utf8'),{ecmaVersion:'latest',sourceType:'module'}),next=parse(fs.readFileSync('js/nethack/native/region.js','utf8'),{ecmaVersion:'latest',sourceType:'module'});
const expected=old.body.filter(n=>n.type!=='ImportDeclaration').map(n=>n.type==='ExportNamedDeclaration'?n.declaration:n);equal(clean(next.body[0].declaration.body.body.slice(0,-1)),clean(expected),'entire source policy and callback/RNG ordering');
const dir='.cache/full-original-c-v1',layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),L=layouts.region,records=JSON.parse(fs.readFileSync('js/nethack/records.json')).records,input={seed:1,timezone:'UTC',options:'OPTIONS=!news\n',keys:'  n'};
let module,env,program;const cOutput=[],cKeys=[],jKeys=[];
const c=await runFullOriginalC(dir,{...input,observeRuntime:r=>{module=r.module;const tty=module.FS.getStream(1).tty,put=tty.ops.put_char;tty.ops={...tty.ops,put_char(t,ch){if(ch!==null)cOutput.push(ch);return put(t,ch);}};}});
const j=runStandaloneProgram(dir+'/assets',{...input,observeRuntime:r=>{env=r.environment;program=r.program;}});
for(const k of ['status','state','snapshots','rngLog','displayRngLog','stdout','stderr'])equal(j[k],c[k],'actual main '+k);
const root={},text=(heap,p)=>{p=Number(p);if(!p)return null;let end=p;while(heap[end])end++;return Buffer.from(heap.slice(p,end)).toString('latin1');};for(let i=0;i<module._full_global_count();i++)root[text(module.HEAPU8,module._full_global_name(i))]=Number(module._full_global_address(i));
function pure(fn){const names=['WebAssembly','fetch','XMLHttpRequest','WebSocket','Worker'],saved=names.map(k=>Object.getOwnPropertyDescriptor(globalThis,k)),deny=()=>{throw Error('Forbidden production Wasm/network in REGION');};for(const k of names)Object.defineProperty(globalThis,k,{configurable:true,value:k==='WebAssembly'?new Proxy({},{get:deny}):deny});try{return fn();}finally{names.forEach((k,i)=>saved[i]?Object.defineProperty(globalThis,k,saved[i]):delete globalThis[k]);equal([C,R,T],[undefined,undefined,undefined],'no leaked C scope');}}
const S=new Proxy(env.services,{get:(o,k)=>{const value=Reflect.get(o,k);return typeof value==='function'?(...a)=>pure(()=>value(...a)):value;}}),owner=nativeStateFor(env),context=env.enableRegion(layouts).context;
for(const [name,fn]of Object.entries(env.start('region-reset').namespace))equal(fn.nativeDirect,true,'actual native REGION entry '+name);
same(context.u,owner.nativeRecords.record('struct you',env.requireGlobal('u')),'canonical hero identity');
module.teleportReadKey=()=>{assert.ok(cKeys.length<256);cKeys.push(32);return 32;};const entry=env.start('terminal-key-input'),prior=entry.namespace.teleport_getch,key=()=>{assert.ok(jKeys.length<256);jKeys.push(32);return 32;};Object.assign(key,prior);entry.namespace.teleport_getch=key;
const jv=()=>env.memory.view,cv=()=>new DataView(module.HEAPU8.buffer),field=(r,k)=>records[r].fields[k].offset;
const optional=(read,p)=>{try{return Buffer.from(read(p)).toString();}catch(e){if(p==='/rng-display.log')return null;throw e;}};
function compare(label){
 equal(elementalRegions({environment:env}),elementalRegions({module}),label+' all region bytes/rectangles/ordered monster IDs');equal(worldGraph({environment:env}),worldGraph({module}),label+' complete reachable world');
 for(const p of ['/rng.log','/rng-display.log'])equal(optional(p=>env.filesystem.readFile(p),p),optional(p=>module.FS.readFile(p),p),label+' ordered '+p);
 const rng=env.state('rnd').rnglist.map(({rng_state:s})=>{const l=layouts.rnd,b=Buffer.alloc(l.size);b.writeBigUInt64LE(BigInt(s.n),l.n);for(const k of ['r','m'])for(let i=0;i<256;i++)b.writeBigUInt64LE(s[k][i],l[k]+i*8);for(const k of ['a','b','c'])b.writeBigUInt64LE(s[k],l[k]);return b;});equal(rng,[0,1].map(i=>{const p=Number(module._full_rng_state(i));return Buffer.from(module.HEAPU8.slice(p,p+layouts.rnd.size));}),label+' full ISAAC states');
 const viz=(heap,base)=>{const v=new DataView(heap.buffer),p=Number(v.getBigUint64(base+L.gv_viz_array,true));return Array.from({length:L.ROWNO},(_,y)=>{const row=Number(v.getBigUint64(p+y*8,true));return Buffer.from(heap.slice(row,row+L.COLNO));});};equal(viz(env.memory.HEAPU8,env.requireGlobal('gv')),viz(module.HEAPU8,root.gv),label+' native visibility bytes');actions++;
}
function call(name,ja=[],ca=ja,{returns=true}={}){const a=S[name](...ja),b=module['_'+name](...ca);if(returns)equal(a,b,name+' return');compare(name);return a;}
compare('initial');
const x=context.u.ux,y=context.u.uy;
// Many overlapping zero-damage clouds exercise capacity growth, native rectangle
// insertion and swapping/removal while keeping hero survival out of the fixture.
for(let i=0;i<13;i++){
 const size=[1,4,12,24][i%4],a=S.create_gas_cloud(x,y,size,0),b=module._create_gas_cloud(x,y,size,0);compare('cloud '+i);
 same(context.region(a),context.region(a),'stable native region identity');
 const seen=S.visible_region_at(x,y),cseen=module._visible_region_at(x,y);equal(Boolean(seen),Boolean(cseen),'visible source query');
 if(seen)same(seen,nativeSpatialFor(env,layouts).regions.visible_region_at(x,y),'queries and mutations share one identity');
}
// The selection-based scroll/tool path calls the real SELVAR owner and then
// enters the same native region graph used by ordinary movement and effects.
const selection=S.selection_new(),cselection=module._selection_new();
for(const [dx,dy]of [[0,0],[1,0],[0,1]]){S.selection_setpoint(x+dx,y+dy,selection,1);module._selection_setpoint(x+dx,y+dy,cselection,1);}
S.create_gas_cloud_selection(selection,0);module._create_gas_cloud_selection(cselection,0);S.selection_free(selection,1);module._selection_free(cselection,1);compare('actual SELVAR to native cloud connection');
// Exercise hero and actor membership before and after movement, including
// capacity growth in each region's native monster-ID array.
const sourceMonster=context.svl.level.monlist;
call('in_out_region',[1,0]);call('in_out_region',[x,y]);
const cfirst=Number(cv().getBigUint64(root.svl+field('instance_globals_saved_l','level')+field('dlevel_t','monlist'),true)),cdata=Number(cv().getBigUint64(cfirst+field('monst','data'),true)),cbase=cdata-cv().getInt32(cdata+field('permonst','pmidx'),true)*L.permonstSize;
const species=env.requireGlobal('mons')+L.PM_FOG_CLOUD*L.permonstSize,cspecies=cbase+L.PM_FOG_CLOUD*L.permonstSize;
const actors=[];
for(let i=0;i<L.MONST_INC+2;i++){
 const mon=S.makemon(species,0,0,0),cmon=module._makemon(BigInt(cspecies),0,0,0);assert.ok(mon&&cmon,'real actor creation');compare('source actor '+i);
 call('m_in_out_region',[mon,x,y],[cmon,x,y]);actors.push([mon,cmon]);
}
assert.ok(context.gr.regions.some(r=>r.max_monst>L.MONST_INC),'actual monster-ID capacity grows past first allocation');checks++;
for(const [mon,cmon]of actors)call('update_monster_region',[mon],[cmon],{returns:false});
call('update_player_regions',[],[],{returns:false});
// Actual nonempty region bytes cross the save/restore boundary. Pointer fields
// are serialized by source routines, not by a test-only projection of native data.
const size=layouts.sfbase.nhfileSize,file=env.memory.calloc(1,size),cfile=Number(module._malloc(BigInt(size))),filename='/native-region-checkpoint',jfd=S.open(filename,578,0o600),cfd=module.FS.open(filename,'w+',0o600).fd;
module.HEAPU8.fill(0,cfile,cfile+size);
for(const [v,p,fd]of [[jv(),file,jfd],[cv(),cfile,cfd]]){for(const [key,value]of [['fd',fd],['mode',layouts.sfbase.WRITING|L.FREEING],['fnidx',layouts.sfbase.historical]])v.setInt32(p+field('nh_file',key),value,true);v.setInt8(p+field('nh_file','structlevel'),1);}
call('save_regions',[file],[BigInt(cfile)],{returns:false});S.bflush(jfd);module._bflush(cfd);equal(Buffer.from(env.filesystem.readFile(filename)),Buffer.from(module.FS.readFile(filename)),'all actual region checkpoint bytes without pointer normalization');
S.lseek(jfd,0,0);module.FS.llseek(module.FS.getStream(cfd),0,0);jv().setInt32(file+field('nh_file','mode'),0,true);cv().setInt32(cfile+field('nh_file','mode'),0,true);
call('rest_regions',[file,0],[BigInt(cfile),0],{returns:false});S.bclose(jfd);module._bclose(cfd);env.memory.free(file);module._free(BigInt(cfile));
const before=env.memory.buffer,grow=env.memory.malloc(env.memory.buffer.byteLength+16*1024*1024);env.memory.free(grow);assert.notEqual(env.memory.buffer,before);compare('live native regions after heap growth');
for(let i=0;i<20;i++)call('run_regions',[],[],{returns:false});
call('clear_regions',[],[],{returns:false});
// Real poison damage connects region callbacks to the current monster list and
// death policies. A one-cell cloud targets the actual source-created actor.
const monster=sourceMonster;assert.ok(monster);const id=monster.m_id,initialHp=monster.mhp,initialBlind=monster.mblinded,position=[monster.mx,monster.my];S.create_gas_cloud(...position,1,3);module._create_gas_cloud(...position,1,3);compare('actual poison cloud');
for(let i=0;i<8;i++)call('run_regions',[],[],{returns:false});
const live=()=>{const out=[];for(let m=context.svl.level.monlist;m;m=m.nmon)out.push({id:m.m_id,hp:m.mhp});return out;};assert.ok(!live().some(m=>m.id===id&&m.hp===initialHp)||monster.mblinded!==initialBlind||monster.mhp<1,'actual callback reaches monster state');
call('clear_regions',[],[],{returns:false});
S.tty_nhbell();module._tty_nhbell();equal(Buffer.from(program.stdio.captured(1)),Buffer.from(cOutput),'all actual terminal bytes');equal(program.terminal.frames,c.frames.map(({screen,cursor,animation})=>({screen:encodeRecorderScreen(screen),cursor:[...cursor,1],animation})),'all source recorder frames');equal(jKeys,cKeys,'More input order');
const sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex'),result={passed:true,checks,actions,nativeEntries:Object.keys(env.start('region-reset').namespace).length,policyFunctions:expected.filter(n=>n.type==='FunctionDeclaration').length,referenceReceiptSha256:sha(dir+'/receipt.json'),scope:'Actual full-main C/JS worlds; native region/actor identity, hero/monster movement membership and real actor creation, overlapping and selection-created cloud/rectangle/member array growth and heap growth, callback expiry/removal and real monster poison effects; complete region/world/visibility bytes, ordered RNG/state and terminal/frame equivalence. Actual nonempty save/release/restore bytes and state also verified; ghost-ID restoration and other advanced branches require separate acceptance.'};fs.writeFileSync('.cache/native-region-evidence.json',JSON.stringify(result,null,2)+'\n');console.log(JSON.stringify(result));
