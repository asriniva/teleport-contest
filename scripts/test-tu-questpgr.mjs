import {DataView,Int32Array,referenceBackend,referenceLabel,assertStackRestored,assertMemoryGrowth} from './native-test-backend.mjs';
import assert from './native-test-assert.mjs';
import {readFileSync} from 'node:fs';
import {resolve} from 'node:path';
import {pathToFileURL} from 'node:url';
import {callQuestpgr} from '../js/ported/questpgr-runtime.js';
import {C,R,T} from '../js/ported/c-runtime.js';
const author=process.env.TELEPORT_QUESTPGR_PROBES;
const dir=author?pathToFileURL(resolve(author)+'/'):new URL('../.cache/tu-probes/',import.meta.url);
const referenceFactory=(await import(new URL('questpgr-reference.mjs',dir))).default,hybridFactory=(await import(new URL('questpgr-hybrid.mjs',dir))).default;
const ref=await referenceBackend('questpgr',referenceFactory)();
function text(m,p){let end=Number(p);while(m.HEAPU8[end])end++;return Buffer.from(m.HEAPU8.slice(Number(p),end)).toString();}
const L={size:Number(ref._probe_context_size())};for(let i=0;i<ref._probe_layout_count();i++){const k=text(ref,ref._probe_layout_name(i)),v=ref._probe_layout_value(i);L[k]=['NON_PM','A_CHAOTIC'].includes(k)?Number(BigInt.asIntN(64,v)):k==='M2_PNAME'?BigInt.asUintN(64,v).toString():Number(v);}
if(!author){const recorded=JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url))).questpgr;assert.deepEqual(L,recorded);}
for(const key of ['BUFSZ','CVT_BUF_SIZE','roleSize','objSize','monSize','pmSize','genderSize','MS_LEADER','MS_NEMESIS','MS_GUARDIAN','NON_PM','G_GENOD'])assert.ok(Number.isSafeInteger(L[key]),key);
const runtime={questpgr:(services,name,...args)=>callQuestpgr(services,L,name,...args)};
const modules=[ref,await hybridFactory({nethackPorted:runtime})],stacks=modules.map(m=>m._probe_stack());let comparisons=0;
function bytes(m,p,n){return Buffer.from(m.HEAPU8.slice(Number(p),Number(p)+n));}
function snapshot(m){return {output:text(m,m._probe_pointer(1,0)),cvt:bytes(m,m._probe_pointer(2,0),L.CVT_BUF_SIZE),name:bytes(m,m._probe_pointer(3,0),L.CVT_BUF_SIZE),trace:text(m,m._probe_trace()),rng:[m._probe_rng_count(),m._probe_rng_state()>>>0],message:!!m._probe_pointer(6,0),free:m._probe_free_count()};}
function state(){assert.deepEqual(snapshot(modules[1]),snapshot(modules[0]));assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);modules.forEach((m,i)=>assertStackRestored(m,stacks[i]));comparisons++;}
function call(fn,...args){const result=modules.map(m=>m['_probe_'+fn](...args));assert.deepEqual(result[1],result[0],fn+'('+args+')');state();comparisons++;return result[0];}
function string(fn,value){modules.forEach(m=>{const b=Buffer.from(value),p=m._malloc(BigInt(b.length+1));m.HEAPU8.set(b,Number(p));m.HEAPU8[Number(p)+b.length]=0;m['_probe_'+fn](BigInt(p));m._free(BigInt(p));});state();}
const input=value=>string('input',value),source=value=>string('source',value),reset=(seed=42)=>call('reset',seed),act=(op,a=0,b=0,c=0)=>call('action',op,a,b,c);
function rolls(values){modules.forEach(m=>{new Int32Array(m.HEAPU8.buffer,Number(m._probe_rng_pointer()),values.length).set(values);m._probe_rng_length(values.length);});state();}
// All original function entries, role names, articles and exact substitutions.
reset();for(const typ of [0,L.MS_LEADER,L.MS_NEMESIS,L.MS_GUARDIAN,999])act(0,typ);for(const op of [1,2,6,7,8])act(op);
for(const female of [0,1,-1,127])for(const level of [1,14,30]){reset();call('hero',0,BigInt(female));call('hero',1,BigInt(level));for(const ch of 'pcrRsSlioOn gGHaAdDCNLxZ%?'.replaceAll(' ',''))act(11,ch.charCodeAt(0));}
for(const gender of [0,1,2,3])for(const artifact of [0,1])for(const who of 'dlno?')for(const pronoun of 'hHiIjJ?'){reset();call('option',2,artifact);call('gender',gender,gender,gender);act(11,'o'.charCodeAt(0));act(10,who.charCodeAt(0),pronoun.charCodeAt(0));}
for(const props of [[0n,0n,0n],[1n,0n,0n],[0n,1n,0n],[1n,1n,1n],[-1n,0n,0n]]){reset();for(let i=0;i<3;i++)call('hero',4+i,props[i]);act(11,120);}
for(const s of ['', 'plain words','%p %c %r %R %s %S %l %i %o %O %n %g %G %H %a %A %d %D %C %N %L %x %Z %% %?', '%oA %oa %oC %op %oP %os %oS %ot', '%dh %dH %di %dI %dj %dJ %lh %ni %oj','%ph %pi %pj %p?', '%','tail\nnext','tail\rnext']){reset();input(s);act(12);act(13);act(14,L.NHW_TEXT);}
// Artifact location precedence, recursively nested objects and dead monster chains.
for(let chain=0;chain<6;chain++)for(const dead of [0,1]){reset();call('object',0,0,-1,1);call('object',1,0,-1,2);call('object',2,L.ART_ORB_OF_DETECTION,-1,-1);call('chain',chain,0);call('dead',chain===3?1:0,dead?0:10);act(3,2);act(4,0);act(4,-1);for(const mask of [0,1<<L.OBJ_INVENT,1<<L.OBJ_FLOOR,1<<L.OBJ_MINVENT,1<<L.OBJ_MIGRATING,1<<L.OBJ_BURIED,0xffffffff])act(5,mask);}
for(const wish of [0,1,-1,256]){reset();call('hero',7,BigInt(wish));for(const common of [0,1,128,255])act(15,common);input('hello');act(17);}
const scenarios=[
"questtext={common={hello={text='Hello %p'}},Arc={hello={text='Greetings %p'}}}",
"questtext={common={hello={text='Common %p'}}}",
"questtext={common={hello={text='Line one\\nLine two %l'}}}",
"questtext={common={hello={text='A text window',output='text',synopsis='Recap %p'}}}",
"questtext={common={hello={text='A menu window',output='menu'}}}",
"questtext={common={hello={text='Explicit pline',output='pline'}}}",
"questtext={common={hello={text='Explicit default',output='default'}}}",
"questtext={common={hello={text='Explicit window',output='window'}}}",
"questtext={common={hello={text=function() return 'Computed %p' end}}}",
"questtext={common={hello={'first %p','second %p','third %p'}}}",
"questtext={common={hello={'only'}}}",
"questtext={common={hello={}}}",
"questtext={common={hello={text='"+'x'.repeat(L.BUFSZ+5)+"'}}}",
"questtext={common={other={text='Fallback %p'}},msg_fallbacks={hello='other'}}",
"questtext={common={},msg_fallbacks={hello='missing'}}",
"questtext={common={},msg_fallbacks={}}",
"questtext={common=3}","questtext=3",
];
for(const s of scenarios)for(const show of [0,1]){reset();source(s);input('hello');rolls([0,1,2]);act(16,0,show,0);act(17);act(18);}
// Raw results are independent allocated strings, freed by the original caller.
for(const s of ["questtext={common={hello={text='Raw %p'}}}","questtext={common={hello={text=function() return 'Function raw' end}}}"]){reset();source(s);input('hello');act(16,0,1,1);}
for(const fail of [0,1]){reset();call('option',fail,1);input('hello');act(16,0,1,0);act(16,0,0,0);}
for(const phrase of ['noxious fumes','poisonous gas','toxic\nfumes','fumes before noxious','toxic light','gas only']){reset();source('questtext={Arc={killed_nemesis={text='+JSON.stringify(phrase)+'}}}');act(9);}
for(const pm1 of [L.PM_GIANT_ANT,L.NON_PM])for(const pm2 of [L.PM_SOLDIER,L.NON_PM])for(const r of [[0,0],[1,0],[1,1],[0,1]]){reset();call('hero',8,BigInt(pm1));call('hero',9,BigInt(pm2));rolls(r);act(19);}
for(const flags of [0,L.G_GENOD]){reset();call('hero',10,BigInt(flags));rolls([1,1]);act(19);reset();call('hero',11,BigInt(flags));rolls([0,1]);act(19);}
reset();string('level_message','Arrive %p\nAt %H');act(20);act(20);
// Nested real C window callback invokes the same Lua-backed pager while outer locals live.
for(const body of ["text='Outer %p'","text='Outer one\\nOuter two'"]){reset();source("questtext={common={hello={"+body+"},nested={text='Nested %l'}}}");call('option',5,1);input('hello');act(17);}
// Native Lua allocation grows memory while JS buffers and role views are live.
reset();call('option',4,1);input('hello');const before=modules.map(m=>m.HEAPU8.buffer);act(17);modules.forEach((m,i)=>assertMemoryGrowth(m,before[i]));
console.log('QUESTPGR '+comparisons+' comparisons passed ('+referenceLabel+' vs JavaScript; actual Lua5.4.8, controlled qtext/world).');
