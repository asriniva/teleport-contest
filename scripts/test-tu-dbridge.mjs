import assert from 'node:assert/strict';
import {readFileSync} from 'node:fs';
import refFactory from '../.cache/tu-probes/dbridge-reference.mjs';
import hybridFactory from '../.cache/tu-probes/dbridge-hybrid.mjs';
import {createPortedRuntime} from '../js/ported/wasm-runtime.js';
import {C,R,T} from '../js/ported/c-runtime.js';
const layouts=JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url))),L=layouts.dbridge,runtime=createPortedRuntime(layouts),modules=[await refFactory(),await hybridFactory({nethackPorted:runtime})],stacks=modules.map(m=>m._probe_stack());let comparisons=0;
const text=(m,p)=>{p=Number(p);let e=p;while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.slice(p,e)).toString('latin1');};
const snap=m=>({state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace()),rng:m._probe_rng_state()>>>0,count:m._probe_rng_count()});
function check(){assert.deepEqual(snap(modules[1]),snap(modules[0]));assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);modules.forEach((m,i)=>assert.equal(m._probe_stack(),stacks[i]));comparisons++;}
function call(name,...args){if(name==='set_monster')args[2]=BigInt(args[2]);if(name==='hero')args[1]=BigInt(args[1]);if(name==='prop')args[2]=BigInt(args[2]);const r=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(r[1],r[0],name+':'+args);comparisons++;check();return r[0];}
const reset=(s=1)=>call('reset',s),opt=(k,v)=>call('option',k,v),mon=(i,k,v)=>call('set_monster',i,k,v),hero=(k,v)=>call('hero',k,v),prop=(p,k,v)=>call('prop',p,k,v),terrain=(x,y,k,v)=>call('terrain',x,y,k,v),entity=(i,k,x=10,y=10)=>call('entity',i,k,x,y),act=(op,a=0,b=0,c=0,d=0)=>Number(call('action',op,a,b,c,d));
const trace=()=>text(modules[0],modules[0]._probe_trace()),state=()=>text(modules[0],modules[0]._probe_snapshot());
function rng(values){modules.forEach(m=>{new Int32Array(m.HEAPU8.buffer,Number(m._probe_rng_pointer()),values.length).set(values);m._probe_rng_length(values.length);});check();}
function verb(s){modules.forEach(m=>m.HEAPU8.set(Buffer.from(s+'\0'),Number(m._probe_pointer(5,0))));check();}
function bridge(dir=L.DB_NORTH,open=0,under=0){const [dx,dy]=directions.get(dir);terrain(10,10,0,under===L.DB_LAVA?L.LAVAPOOL:L.MOAT);terrain(10+dx,10+dy,0,L.HWALL);assert.equal(act(11,10,10,dir,open),1);terrain(10,10,1,dir|under);return[10+dx,10+dy];}
function coordinates(){const m=modules[0],v=new DataView(m.HEAPU8.buffer),p=Number(m._probe_pointer(3,0));return[v.getInt16(p,true),v.getInt16(p+2,true)];}
reset();for(const m of modules)for(let i=0;i<m._probe_layout_count();i++){const k=text(m,m._probe_layout_name(i)),v=m._probe_layout_value(i);assert.equal(typeof L[k]==='string'?BigInt.asUintN(64,v).toString():Number(BigInt.asIntN(64,v)),L[k],k);}
const required=['COLNO','ROWNO','ROOM','STONE','HWALL','DOOR','DBWALL','DRAWBRIDGE_UP','DRAWBRIDGE_DOWN','WATER','POOL','MOAT','LAVAPOOL','LAVAWALL','ICE','DB_NORTH','DB_SOUTH','DB_EAST','DB_WEST','DB_MOAT','DB_LAVA','DB_ICE','DB_UNDER','PM_HUMAN','PM_GHOST','PM_LONG_WORM','PM_LONG_WORM_TAIL','PM_GIANT_BAT','PM_GIANT_EEL','PM_XORN','PM_FIRE_ELEMENTAL','PM_FLOATING_EYE','WWALKING','SWIMMING','LEVITATION','FLYING','PASSES_WALLS','CONFUSION','STUNNED','FUMBLING','HALLUC','DEAF','BOULDER','DROWNING','BURNING','CRUSHING'];
for(const k of required)assert.ok(Number.isSafeInteger(L[k]),k);
const directions=new Map([[L.DB_NORTH,[0,-1]],[L.DB_SOUTH,[0,1]],[L.DB_EAST,[1,0]],[L.DB_WEST,[-1,0]]]);

// Terrain queries preserve every under-mask and reject only the boundaries guarded by the original source.
for(const type of [L.ROOM,L.STONE,L.DOOR,L.DBWALL,L.DRAWBRIDGE_UP,L.DRAWBRIDGE_DOWN,L.WATER,L.POOL,L.MOAT,L.LAVAPOOL,L.LAVAWALL,L.ICE])for(const mask of [0,L.DB_MOAT,L.DB_LAVA,L.DB_ICE,255,-1]){reset();terrain(10,10,0,type);terrain(10,10,1,mask);for(let op=0;op<9;op++)act(op,10,10);}
for(const [x,y]of [[-1,10],[0,10],[L.COLNO,10],[10,-1],[10,L.ROWNO]]){reset();for(const op of [0,1,2,3,4,5,7])assert.equal(act(op,x,y),op===7?-1:0);}
for(let mask=-4;mask<32;mask++){reset();act(6,mask);}
reset();terrain(10,10,0,L.MOAT);assert.equal(act(5,10,10),1);hero(7,1);assert.equal(act(5,10,10),0);assert.equal(act(1,10,10),1);
for(const [dir,[dx,dy]]of directions)for(const flag of [-1,0,1,256,257]){reset();const [wx,wy]=bridge(dir,flag);assert.equal(act(7,wx,wy),dir);assert.equal(act(9,wx,wy),1);assert.deepEqual(coordinates(),[10,10]);act(10,10,10);assert.deepEqual(coordinates(),[wx,wy]);for(const alias of [0,1]){opt(14,alias);act(9,10,10);act(10,10,10);}}
reset();assert.equal(act(11,10,10,L.DB_NORTH,1),0);terrain(9,10,0,L.HWALL);act(11,10,10,999,0);assert.ok(trace().includes('bad direction'));

// Entity setup uses the actual native occupant records, including tail data and clearing stale coordinates.
reset();entity(0,-1,20,20);assert.equal(act(12,20,20),-1);hero(0,10);hero(1,10);act(15,0,10,10);assert.equal(act(12,10,10),0);act(16,0);assert.ok(state().includes('out:you;'));verb('are ready');act(17,0,1);assert.ok(state().includes('out:You are ready;'));
for(const species of [L.PM_HUMAN,L.PM_LONG_WORM,L.PM_GHOST])for(const tail of [0,1]){reset();mon(0,0,species);mon(0,3,tail);mon(0,1,10);mon(0,2,10);act(13,0,0,11,10);const wanted=tail?L.PM_LONG_WORM_TAIL:species;assert.ok(state().includes(`;e:0:${wanted}:11:10`));act(16,0);verb('are');act(17,0,1);assert.ok(state().includes('out:Fixture monster is;'));const ptr=modules.map(m=>m._probe_pointer(4,0));verb('have');act(17,0,1);modules.forEach((m,i)=>assert.equal(m._probe_pointer(4,0),ptr[i]));act(17,0,0);assert.ok(state().includes('out:Fixture monster;'));verb('');act(17,0,1);assert.ok(state().includes('out:Fixture monster;'));act(13,0,-1,10,10);assert.ok(state().includes(';e:-1:-1:0:0'));}

// Native morphology and player property combinations determine survival, automatic misses and chance thresholds.
for(const species of [L.PM_HUMAN,L.PM_GHOST,L.PM_GIANT_BAT,L.PM_GIANT_EEL,L.PM_XORN,L.PM_FIRE_ELEMENTAL,L.PM_FLOATING_EYE])for(const player of [0,1])for(const terrainType of [L.ROOM,L.MOAT,L.LAVAPOOL,L.DBWALL]){reset();if(player){hero(0,10);hero(1,10);hero(2,species);entity(0,4);}else{mon(0,0,species);entity(0,0);}terrain(10,10,0,terrainType);act(18,0,10,10);act(20,0);for(const roll of [0,2,4,7,9]){rng([roll]);act(21,0,0);rng([roll]);act(21,0,1);rng([roll]);act(22,0);}}
for(const property of [L.WWALKING,L.SWIMMING,L.LEVITATION,L.FLYING,L.PASSES_WALLS,L.CONFUSION,L.STUNNED,L.FUMBLING]){reset();hero(0,10);hero(1,10);entity(0,4);prop(property,0,1);terrain(10,10,0,L.MOAT);act(18,0,10,10);rng([0]);act(21,0,1);rng([0]);act(22,0);}
for(const immobile of [0,1,2,3]){reset();mon(0,0,L.PM_GIANT_BAT);if(immobile===1)mon(0,4,1);if(immobile===2)mon(0,5,0);if(immobile===3)mon(0,3,1);entity(0,0);rng([4]);act(21,0,0);rng([0]);assert.equal(act(22,0),immobile?0:1);}

// Awareness requires both a negative movement counter and actual unconscious/fainted state.
for(const mode of [0,1,2]){reset();hero(0,10);hero(1,10);hero(2,L.PM_GIANT_BAT);hero(4,-((1n<<53n)+3n));opt(4,mode===1);opt(5,mode===2);entity(0,4);rng([0]);assert.equal(act(21,0,0),mode?0:1);rng([0]);assert.equal(act(22,0),mode?0:1);assert.ok(trace().includes('unconscious;'));}
// Both native debug formatting shapes execute only while the original predicate is enabled.
reset();hero(0,10);hero(1,10);entity(0,4);opt(6,1);assert.equal(act(12,10,10),0);rng([0]);assert.equal(act(22,0),1);assert.ok(trace().includes('entitycnt = 0'));assert.ok(trace().includes('You try to jump (4 chances in 10)'));
for(const deaf of [0,1,2]){reset();bridge(L.DB_NORTH,0,L.DB_MOAT);opt(1,0);if(deaf===1)prop(L.DEAF,0,1);if(deaf===2)hero(8,1);call('add_monster',0,10,9);entity(0,0,10,9);rng([7,9]);act(23,0);assert.equal(trace().includes('You_hear:a crushing sound.'),deaf===0);assert.ok(trace().includes('xkilled:0:'));}

// Controlled death/lifesave boundaries keep real monster identity and clear all aliases of a dead worm.
for(const player of [0,1])for(const how of [L.DROWNING,L.BURNING,L.CRUSHING])for(const moving of [0,1])for(const lifesave of [0,1,2]){reset();hero(5,moving);opt(9,lifesave);if(player){hero(0,10);hero(1,10);entity(0,4);terrain(10,10,0,L.DBWALL);}else{call('add_monster',0,10,10);entity(0,0);entity(1,0,11,10);}hero(9,7);act(19,0,0,how);if(!player){assert.equal(trace().includes('monkilled:'),!!moving);assert.equal(trace().includes('xkilled:'),!moving);assert.ok(state().includes(';e:0:-1:'));}else assert.ok(trace().includes(how===L.DROWNING?'drown;':how===L.BURNING?'lava;':'done:'));}
reset();hero(0,10);hero(1,10);entity(0,4);terrain(10,10,0,L.DBWALL);act(19,0,0,L.CRUSHING);assert.ok(trace().includes('tele:14:14:'));assert.ok(state().includes(';e:4:'));

// Every transition removes real traps and floor references, updates events, and resets both entity records/killer.
for(const dir of directions.keys())for(const under of [L.DB_MOAT,L.DB_LAVA,L.DB_ICE,0])for(const operation of [25,26,27])for(const visible of [0,1]){reset();opt(13,visible?3:0);hero(6,1);const [wx,wy]=bridge(dir,operation===25?1:0,under);call('trap',0,10,10);call('trap',1,wx,wy);call('add_object',L.BOULDER,10,10);rng([2,0,1,1,0]);act(operation,10,10);assert.ok(trace().includes('deltrap:0;'));assert.ok(trace().includes('deltrap:1;'));assert.ok(state().includes('traps:0:0;'));assert.ok(state().includes(';e:-1:-1:0:0'));assert.ok(state().includes('kill:0:;'));if(operation!==25)assert.ok(state().includes('events:1:'));if(operation===27){assert.ok(trace().includes('scatter:'));assert.ok(state().includes('events:1:3;'));}}
for(const operation of [25,26,27]){reset();act(operation,10,10);assert.ok(!trace().includes('newsym:'));}
// Entity interactions force common relocation/recursive handling; bounded seeded trials compare the complete native world.
for(const species of [L.PM_HUMAN,L.PM_GHOST,L.PM_XORN,L.PM_GIANT_BAT])for(const other of [L.PM_HUMAN,L.PM_GHOST])for(const operation of [25,26,27])for(const seed of [1,2,3,17]){reset(seed);const [wx,wy]=bridge(L.DB_NORTH,operation===25?1:0,L.DB_MOAT);mon(0,0,species);mon(1,0,other);call('add_monster',0,10,10);call('add_monster',1,wx,wy);act(operation,10,10);}
reset();bridge(L.DB_NORTH,0,L.DB_MOAT);mon(0,0,L.PM_GHOST);call('add_monster',0,10,10);entity(0,0);act(23,0);assert.ok(trace().includes('passes through'));
reset();entity(0,0);entity(1,1);hero(9,5);act(24);assert.ok(state().includes('kill:0:;'));assert.equal(act(12,10,10),-1);

// Native callbacks reenter the real TU and grow linear memory; each typed field access must reacquire its view.
for(let stage=1;stage<=23;stage++){reset();opt(30,stage===22?0:stage);opt(31,stage===22?0:stage);const before=modules.map(m=>m.HEAPU8.byteLength);if(stage===1){entity(0,0);rng([7]);act(21,0,0);}else if(stage<=7){hero(0,10);hero(1,10);entity(0,4);terrain(10,10,0,L.DBWALL);if(stage===2)act(19,0,0,L.DROWNING);else if(stage===3)act(19,0,0,L.BURNING);else if(stage===7){call('add_monster',0,10,10);entity(0,0);act(19,0,0,L.CRUSHING);}else act(19,0,0,L.CRUSHING);}else if(stage===8||stage===9){bridge(L.DB_NORTH,0,L.DB_MOAT);call('add_monster',0,10,9);entity(0,0,10,9);rng([7,0]);act(23,0);}else if(stage===10){bridge(L.DB_NORTH,0,L.DB_MOAT);hero(0,10);hero(1,10);hero(2,L.PM_GHOST);entity(0,4);act(23,0);}else if(stage===11){bridge(L.DB_NORTH,0,L.DB_MOAT);mon(0,0,L.PM_GHOST);call('add_monster',0,10,10);rng([0]);act(27,10,10);}else{const [wx,wy]=bridge(L.DB_NORTH,stage===17?1:0,L.DB_MOAT);call('trap',0,10,10);call('trap',1,wx,wy);call('add_object',L.BOULDER,10,10);if(stage===22){opt(30,22);opt(31,22);}rng([1,0,0]);act(stage===17?25:stage<=18?26:27,10,10);}assert.ok(trace().includes(`grow:${stage};`),`growth${stage}`);assert.ok(trace().includes('nested:'));modules.forEach((m,i)=>assert.ok(m.HEAPU8.byteLength>before[i]));}
reset();opt(0,0);entity(0,0);rng([0]);act(22,0);assert.ok(trace().includes('@;'));
reset();bridge();const held=snap(modules[1]),other=await hybridFactory({nethackPorted:runtime});other._probe_reset(9);other._probe_terrain(10,9,0,L.HWALL);assert.equal(other._probe_action(11,10,10,L.DB_NORTH,0),1n);other._probe_action(26,10,10,0,0);assert.ok(text(other,other._probe_trace()).includes('unblock:'));assert.deepEqual(snap(modules[1]),held);comparisons+=2;check();
console.log(`DBRIDGE C/hybrid differential: ${comparisons} comparisons passed`);
