import './pure-js-probes/deny-wasm.mjs';
import {createProbe,createReference,loadFixture,fixtureImports} from './pure-js-fixtures/load.mjs';
// First-pass configured Emscripten-C differential gate. Native macOS coverage
// and actual production mixed-link promotion are separate, still pending.
import assert from './native-test-assert.mjs';
import { pathToFileURL } from 'node:url';
import { resolve } from 'node:path';
import * as explode from '../js/ported/explode.js';
import { createExplodeEnvironment } from '../js/nethack/bindings/explode.js';
import { withCEnvironment, C } from '../js/c-runtime/context.js';
const probeDirectory=resolve(process.env.TELEPORT_EXPLODE_PROBE_DIR??'.cache/tu-probes');
const referenceFactory=(await loadFixture("explode",pathToFileURL(resolve(probeDirectory,'explode-reference.mjs')))).default;
const hybridFactory=(await loadFixture("explode",pathToFileURL(resolve(probeDirectory,'explode-hybrid.mjs')))).default;
const text=(m,value)=>{const p=Number(value);let e=p;while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.subarray(p,e)).toString('latin1');};
const layout=m=>Object.fromEntries(Array.from({length:m._probe_layout_count()},(_,i)=>[text(m,m._probe_layout_name(i)),Number(m._probe_layout_value(i))]));
const reference=await referenceFactory();let L=layout(reference),environments=new WeakMap();
const runtime={explode(services,name,...args){let env=environments.get(services.moduleKey);if(!env){env=createExplodeEnvironment(services,L);environments.set(services.moduleKey,env);}
    if(name==='explosionmask')args[0]=env.monster(args[0]);
    if(name==='scatter')args[4]=env.object(args[4]);
    if(name==='explode_oil')args[0]=env.object(args[0]);
    if(name==='mon_explodes'){args[0]=env.monster(args[0]);args[1]=env.attack(args[1]);}
    return withCEnvironment(env,explode[name],...args);
}};
const hybrid=await hybridFactory({nethackPorted:runtime}),modules=[reference,hybrid],stacks=modules.map(m=>m._probe_stack());
assert.deepEqual(layout(hybrid),L);
const snapshots=()=>modules.map(m=>({state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace())}));
let comparisons=1,scenario='initial';
function check(){const [a,b]=snapshots();assert.deepEqual(b,a,scenario);assert.equal(C,undefined);modules.forEach((m,i)=>assert.equal(m._probe_stack(),stacks[i]));comparisons++;}
function call(name,...args){if(name==='option'||name==='prop')args[1]=BigInt(args[1]);const result=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(result[1],result[0],scenario+':'+name+':'+args);comparisons++;check();return result[0];}
const reset=(seed=1)=>call('reset',seed),opt=(k,v)=>call('option',k,v),prop=(p,v=1)=>call('prop',p,v),act=(op,a=0,b=0,c=0,d=0,e=0,f=0)=>call('action',op,a,b,c,d,e,f);
const trace=()=>text(reference,reference._probe_trace());
function visible(value=1){for(let x=9;x<=12;x++)for(let y=9;y<=11;y++)call('cell',x,y,L.ROOM,value);}
// Every display-type input, including diagnosed unsupported damage types.
for(let type=-2;type<=45;type++){scenario='display type '+type;reset();act(6,type);}
// Shield selection for hero/monster, every admitted damage family and invalid
// input; wand death-field semantics remain distinct from disintegration.
for(const damage of [L.AD_PHYS,L.AD_MAGM,L.AD_FIRE,L.AD_COLD,L.AD_DISN,L.AD_ELEC,L.AD_DRST,L.AD_ACID,255])for(const hero of [0,1])for(const wand of [0,1])for(const resistant of [0,1]){
 scenario=`shield ${damage}/${hero}/${wand}/${resistant}`;reset();opt(0,resistant?0x7fffffff:0);opt(1,resistant);for(const p of[L.ANTIMAGIC,L.FIRE_RES,L.COLD_RES,L.DISINT_RES,L.SHOCK_RES,L.POISON_RES,L.ACID_RES])prop(p,resistant);if(resistant)opt(116,L.M2_DEMON);act(0,hero,damage,wand?L.WAND_CLASS:L.SCROLL_CLASS);
}
for(const digest of [0,1])for(const damage of [L.AD_PHYS,L.AD_FIRE,L.AD_COLD,L.AD_DISN,L.AD_ELEC,L.AD_DRST,L.AD_ACID])for(const wand of [0,1]){scenario='engulfer message';reset();opt(4,digest);act(1,damage,wand?L.WAND_CLASS:L.SCROLL_CLASS);}
// Explosion targeting, visibility, shield animation, inventory/floor order,
// damage/resistance and kill attribution are compared through full traces.
for(const type of [0,1,2,4,5,6,7,L.PHYS_EXPL_TYPE])for(const damage of [0,17])for(const shown of [0,1])for(const monster of [0,1]){
 scenario=`blast ${type}/${damage}/${shown}/${monster}`;reset(13);visible(shown);opt(101,monster);opt(118,0);opt(102,1);act(2,10,10,type,damage,L.SCROLL_CLASS,L.EXPL_FIERY);
}
for(const type of [1,2,4])for(const moving of [0,1])for(const resist of [0,1])for(const half of [0,1]){scenario='damage and kill';reset();visible();opt(101,1);opt(105,5);opt(103,moving);opt(8,resist);opt(7,3);prop(L.HALF_PHDAM,half);prop(type===1?L.FIRE_RES:L.COLD_RES,resist);opt(0,resist?0x7fffffff:0);act(2,10,10,type,19,L.WAND_CLASS,L.EXPL_MAGICAL);}
for(const role of[L.PM_CLERIC,L.PM_MONK,L.PM_WIZARD,L.PM_HEALER,L.PM_KNIGHT]){scenario='wand role damage';reset();opt(118,0);opt(125,role);act(2,10,10,1,31,L.WAND_CLASS,L.EXPL_FIERY);}
for(const diluted of[0,1])for(const lit of[0,1]){scenario='oil extinguish/explosion';reset(37);opt(118,0);opt(109,diluted);opt(110,lit);act(5,10,10);assert.ok(trace().includes('endburn:1;'));}
for(const damage of[L.AD_PHYS,L.AD_FIRE,L.AD_COLD,L.AD_ELEC,255])for(const dice of[0,1,2])for(const dead of[0,1]){scenario='monster explosion';reset(21);opt(118,0);opt(111,damage);opt(112,dice===2?2:0);opt(113,dice?4:0);opt(105,dead?0:100);act(7);}
// Scatter uses the original quantity split, RNG sites, chain allocation, motion,
// object collision and placement algorithms. No C scatter implementation is
// present in the hybrid fixture.
for(const seed of[1,2,5,100])for(const quantity of[1,4])for(const force of[0,1,4])for(const individual of[0,1]){scenario='scatter movement';reset(seed);opt(118,0);opt(106,quantity);opt(107,L.ROCK);opt(108,40);act(8,10,10);act(3,10,10,force,0,individual);}
for(const fracture of[0,1])for(const type of[L.BOULDER,L.STATUE,L.EGG]){scenario='scatter destruction';reset(2);opt(118,0);opt(107,type);opt(13,1);act(8,10,10);act(3,10,10,3,fracture?L.MAY_FRACTURE:L.MAY_DESTROY,1);}

for(const seed of[1,2,3,4,5,6,7,8,19,37])for(const hit of[0,1,2]){scenario='scatter collisions and shop';reset(seed);opt(118,0);opt(107,hit===2?L.GOLD_PIECE:L.ROCK);opt(108,0);opt(5,hit===2);opt(101,1);opt(10,hit===1);opt(11,hit===2);opt(12,1);opt(124,3);act(8,9,10);act(3,9,10,6,L.MAY_HITMON|L.MAY_HITYOU,1);}
for(const swallowed of[0,1])for(const poly of[0,1])for(const immune of[0,1]){scenario='engulf/grab/invulnerability';reset(93);visible();opt(100,swallowed);opt(123,poly);prop(L.INVULNERABLE,immune);opt(101,1);act(2,10,10,1,27,L.SCROLL_CLASS,L.EXPL_FIERY);}
for(const olet of[L.TRAP_EXPLODE,L.MON_EXPLODE,L.WAND_CLASS,L.SCROLL_CLASS]){scenario='fatal naming';reset();opt(118,0);opt(104,1);act(2,10,10,olet===L.MON_EXPLODE?-1:1,29,olet,L.EXPL_FIERY);assert.ok(trace().includes('done:'));}
scenario='memory growth during inventory effects';reset();opt(118,0);opt(101,1);opt(15,1);act(2,10,10,1,9,L.SCROLL_CLASS,L.EXPL_FIERY);assert.ok(trace().includes('growth;'));
for(const damage of[65537,100000,2147483647,-2147483648]){scenario='32-bit noise multiplication';reset();opt(118,0);prop(L.INVULNERABLE);act(2,10,10,0,damage,L.SCROLL_CLASS,L.EXPL_FIERY);}

// C stores rm.typ's signed byte into local uchar typ before ZAP_POS. Preserve
// this defined conversion even for deliberately poisoned terrain bytes.
for(const terrainByte of[0x7f,0x80,0xff])for(const seed of[1,2,3,4,5,6,7,8]){scenario='unsigned terrain local';reset(seed);opt(118,0);opt(107,L.ROCK);opt(108,0);for(let x=8;x<=12;x++)for(let y=8;y<=12;y++)call('cell',x,y,terrainByte,0);act(8,10,10);act(3,10,10,2,0,1);}
// Bounds, empty chain and invalid blast type must remain diagnostic/no-op paths.
for(const [x,y] of[[0,0],[1,0],[79,20],[80,21]]){scenario='boundary';reset();opt(118,0);act(2,x,y,3,0,L.SCROLL_CLASS,L.EXPL_FIERY);act(3,10,10,1,0,0);}
console.log(`EXPLODE: ${comparisons} configured original-C/pure-JS comparisons passed; native and production promotion pending.`);
