import './pure-js-probes/deny-wasm.mjs';
import {referenceLabelFor as fixtureReferenceLabelFor} from './native-test-backend.mjs';
const fixtureReferenceLabel=fixtureReferenceLabelFor("vision");
import {createProbe,createReference,loadFixture,fixtureImports} from './pure-js-fixtures/load.mjs';
import assert from './native-test-assert.mjs';
import {assertStackRestored,memoryCheckpoint,assertMemoryGrowth,referenceBackend} from './native-test-backend.mjs';
import {readFileSync,writeFileSync} from 'node:fs';
import {callVision,initializeVision,createVisionEnvironment} from '../js/nethack/bindings/vision.js';
import * as core from '../js/ported/vision.js';
import {C,R,T} from '../js/c-runtime/context.js';
const own=process.env.TELEPORT_VISION_AUTHOR==='1';
const ref=(await loadFixture("vision",own?'../.cache/vision-author/reference.mjs':'../.cache/tu-probes/vision-reference.mjs')).default;
const hyb=(await loadFixture("vision",own?'../.cache/vision-author/hybrid.mjs':'../.cache/tu-probes/vision-hybrid.mjs')).default;
const text=(m,p)=>{p=Number(p);let e=p;while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.slice(p,e)).toString('latin1');};
let reference=await referenceBackend('vision',ref)();const measured={};for(let i=0;i<reference._probe_layout_count();i++)measured[text(reference,reference._probe_layout_name(i))]=Number(BigInt.asIntN(64,reference._probe_layout_value(i)));
const L=own?measured:JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url))).vision;
if(own)writeFileSync(new URL('../.cache/vision-author/layout.json',import.meta.url),JSON.stringify(L,null,2));
for(const source of [readFileSync(new URL('./test-tu-vision.mjs',import.meta.url),'utf8'),readFileSync(new URL('../js/nethack/bindings/vision.js',import.meta.url),'utf8')])for(const m of source.matchAll(/\b(?:L|layout)\.([A-Z][A-Z_0-9]*|[a-z]\w*Size)\b/g))assert.ok(Object.hasOwn(L,m[1]),'compiled layout '+m[1]);
const externals=new Set([...readFileSync(new URL('../js/ported/vision.js',import.meta.url),'utf8').replace(/\/\*[\s\S]*?\*\/|"(?:\\.|[^"\\])*"/g,'').matchAll(/\bC\.(\w+)/g)].map(m=>m[1]));
const checked=new WeakSet();function validate(s){if(checked.has(s.moduleKey))return;const e=createVisionEnvironment(s,L);for(const k of externals)assert.notEqual(e[k],undefined,'native/header binding '+k);checked.add(s.moduleKey);}
const ported={initializeVision(s){validate(s);return initializeVision(s,L);},callVision(s,n,...a){validate(s);return callVision(s,L,n,...a);}};
let modules=[reference,await hyb({nethackPorted:ported})],stacks=modules.map(m=>m._probe_stack()),comparisons=0;
const snapshot=m=>({state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace())});
function check(){const a=modules.map(snapshot);if(a[0].state!==a[1].state||a[0].trace!==a[1].trace){writeFileSync(new URL('../.cache/vision-author/actual.json',import.meta.url),JSON.stringify(a[1]));writeFileSync(new URL('../.cache/vision-author/expected.json',import.meta.url),JSON.stringify(a[0]));}assert.deepEqual(a[1],a[0]);modules.forEach((m,i)=>assertStackRestored(m,stacks[i],m._probe_stack()));assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);comparisons++;}
function call(n,...a){const v=modules.map(m=>m['_probe_'+n](...a));assert.deepEqual(v[1],v[0],n);comparisons++;return v[0];}
const act=(op,a=0,b=0,c=0,d=0,e=0)=>{const r=call('action',op,a,b,c,d,e);check();return r;};
const reset=()=>{call('reset');check();},init=()=>{reset();act(0);act(1);},tile=(...a)=>call('tile',...a),hero=(k,v)=>call('hero',k,BigInt(v)),option=(...a)=>call('option',...a),prop=(n,f,v)=>call('property',n,f,BigInt(v)),monster=(i,k,v)=>call('set_monster',i,k,BigInt(v)),trace=()=>text(reference,reference._probe_trace()),value=(k,x=0,y=0)=>call('value',k,x,y);
for(const[k,v]of Object.entries(measured))assert.equal(L[k],v,k);
// Real optimized C foreign readers observe both JS catalogues BEFORE any source function.
for(const[table,name]of ['circle_data','circle_start'].entries()){assert.equal(core[name].length,table?16:137);for(let i=0;i<core[name].length;i++)assert.equal(call('foreign_circle',table,i),core[name][i]);}
assert.equal(call('startup_circle',0),16);assert.equal(call('startup_circle',1),120);
assert.equal(core.circle_data[136],16);assert.equal(core.circle_start[15],120);
reset();act(0);act(13);assert.equal(value(0,40,10),0);act(1);assert.equal(value(1,40,10),1);assert.equal(value(1,0,10),0);assert.equal(act(2,0,10),0n);assert.equal(act(2,40,10),0n);
// Full helper maps and boundary merges: every point on multiple rows toggles both ways.
for(const y of [0,1,10,20])for(const x of [0,1,2,39,40,78,79]){tile(x,y,0,L.STONE);act(5,x,y);assert.equal(value(1,x,y),0);tile(x,y,0,L.ROOM);act(6,x,y);assert.equal(value(1,x,y),1);act(12,y,x);assert.equal(value(1,x,y),0);act(11,y,x);assert.equal(value(1,x,y),1);}
// Every external obstruction class, packed doors, boulder chains and invisible mimics.
for(const type of [L.STONE,L.TREE,L.CLOUD,L.WATER,L.LAVAWALL,L.ROOM,L.DOOR]){init();tile(10,10,0,type);assert.equal(act(3,10,10),BigInt(type===L.ROOM||type===L.DOOR?0:1));}
for(const door of [0,L.D_CLOSED,L.D_LOCKED,L.D_TRAPPED]){init();tile(10,10,0,L.DOOR);tile(10,10,4,door);assert.equal(act(3,10,10),door?1n:0n);act(7,10,10);assert.equal(value(1,10,10),door?0:1);}
init();call('object',0,10,10,L.BOULDER);assert.equal(act(3,10,10),1n);
for(const invisible of [0,1])for(const see of [0,1]){init();monster(0,0,10);monster(0,1,10);monster(0,2,invisible);monster(0,3,L.M_AP_OBJECT);monster(0,4,L.BOULDER);monster(0,7,1);prop(L.SEE_INVIS,0,see);assert.equal(act(3,10,10),!invisible||see?1n:0n);}
init();option(0,1);option(2,10);option(3,10);assert.equal(act(3,10,10),2n);reset();act(0);hero(12,1);option(12,1);act(1);act(3,11,10);assert.ok(trace().includes('debug:seethru:0;'));
// Bresenham macro quadrants, equal endpoints and deterministic irregular obstacles.
for(let seed=1;seed<=8;seed++){init();for(let x=1;x<L.COLNO;x++)for(let y=0;y<L.ROWNO;y++)if((x*31+y*17+seed*13)%19<4)tile(x,y,0,L.STONE);act(1);for(let i=0;i<100;i++){const x1=1+(i*17+seed)%79,y1=(i*13+seed)%21,x2=1+(i*29+seed*7)%79,y2=(i*11+seed*3)%21;act(8,x1,y1,x2,y2);if(i%11===0)assert.equal(act(8,x1,y1,x1,y1),1n);}}
init();assert.equal(act(8,10,10,12,10),1n);tile(11,10,0,L.STONE);act(5,11,10);assert.equal(act(8,10,10,12,10),0n);
// Full source recalc: ordinary, refresh, blind/blocked, swallowed, pits and ranges.
for(const control of [0,1,2])for(const blind of [0,1])for(const lit of [0,1]){init();for(let x=1;x<80;x++)for(let y=0;y<21;y++)tile(x,y,1,lit);prop(L.BLINDED,0,blind);act(4,control);assert.equal(value(0,40,10)&L.IN_SIGHT,blind||control===2?0:L.IN_SIGHT);assert.ok(trace().includes('notice:1;'));}
for(const [key,v]of [[4,1],[9,1],[10,1],[11,1]]){init();hero(key,v);act(4,0);}
for(const radius of [-1,0,1,3,15])for(const night of [0,1,4,15]){init();hero(3,radius);hero(2,night);act(4,0);}
init();prop(L.BLINDED,0,1);prop(L.BLINDED,2,1);act(4,0);assert.equal(value(0,40,10)&L.IN_SIGHT,L.IN_SIGHT);
init();hero(6,2);hero(7,L.TT_PIT);act(4,0);assert.equal(value(0,41,11),L.IN_SIGHT|L.COULD_SEE);assert.equal(value(0,42,10),0);
init();hero(5,1);for(let x=39;x<=41;x++)for(let y=9;y<=11;y++)tile(x,y,0,L.WATER);act(4,0);assert.equal(value(0,41,11),L.IN_SIGHT|L.COULD_SEE);
// Old light memory and one-sided door darkness reach the shared not-in-sight tail.
init();tile(43,10,0,L.DOOR);tile(43,10,4,L.D_CLOSED);tile(43,10,1,1);tile(42,10,1,0);tile(43,10,2,1);act(1);act(4,0);assert.equal(value(0,43,10)&L.IN_SIGHT,0);tile(42,10,1,1);act(4,0);assert.equal(value(0,43,10)&L.IN_SIGHT,L.IN_SIGHT);
init();tile(45,10,2,1);act(4,0);assert.equal(value(7,45,10),0);
for(const lit of [0,1]){init();call('room',36,44,7,13,lit);tile(40,10,5,L.ROOMOFFSET);hero(13,1);act(10);act(4,0);assert.equal(value(0,44,12)&L.COULD_SEE,L.COULD_SEE);}
// Native pointer-to-pointer outputs, including legal aliased min/max output cells.
init();act(9,0);act(9,1);
// All radii execute recursive sides with and without an actual native callback.
for(let r=1;r<=15;r++){init();for(let x=25;x<55;x++)if(x%3)tile(x,8,0,L.STONE);act(1);act(14,10,40,r,0);act(14,10,40,r,1,0xfedcba98);assert.ok(trace().includes('visit:40:10:4275878552;'));}
init();act(14,65546,65576,3,0);act(15,11,40,41,0);act(16,11,39,40,0);
for(const center of [0,1])for(const detect of [0,1]){init();option(9,detect);hero(14,1);act(4,0);act(17,center?40:30,10,4,123);assert.ok(trace().includes('visit:'));}
// Opaque callback payloads are passed through untouched, never dereferenced.
for(const token of [0n,(1n<<53n)+1n,0xa5abcdef12345678n,(1n<<64n)-1n])for(const op of [14,17]){init();option(14,1);call('payload',token);if(op===14)act(14,10,40,2,1);else act(17,30,10,2,0);assert.ok(trace().includes(':'+token+';'));}
// Visibility explanations retain independent native classification calls and all bits.
for(let bits=0;bits<32;bits++){init();option(4,bits&1);option(5,bits&2);option(6,bits&4);option(7,bits&8);monster(0,2,bits&16);hero(3,4);prop(L.DETECT_MONSTERS,0,1);prop(L.WARN_OF_MON,0,1);hero(18,L.PM_HUMAN);act(4,0);const seen=act(18,0);assert.equal(Number(seen)&L.MONSEEN_DETECT,L.MONSEEN_DETECT);assert.equal(Number(seen)&L.MONSEEN_WARNMON,L.MONSEEN_WARNMON);}
for(const raw of [0,1,128,255,256,257,-128,-256]){init();option(4,raw);monster(0,2,1);const result=act(18,0);assert.equal(Number(result)&L.MONSEEN_SEEINVIS,(raw<<24>>24)?L.MONSEEN_SEEINVIS:0);}
init();monster(0,5,1);option(8,1);option(5,1);assert.equal(Number(act(18,0))&L.MONSEEN_NORMAL,L.MONSEEN_NORMAL);
// Actual 48MiB growth and native C->JS reentry occur inside the original loops.
for(const callback of [0,1,5]){reference=await referenceBackend('vision',ref)();modules=[reference,await hyb({nethackPorted:ported})];stacks=modules.map(m=>m._probe_stack());init();const before=modules.map(memoryCheckpoint);option(10,callback||1);option(11,callback||1);if(callback)act(14,10,40,6,1,123);else act(4,0);assert.ok(trace().includes('growth;reentry:'));modules.forEach((m,i)=>assertMemoryGrowth(m,before[i]));}
init();act(4,0);const primary=snapshot(modules[1]);const other=await hyb({nethackPorted:ported});other._probe_reset();other._probe_action(0,0,0,0,0,0);other._probe_action(1,0,0,0,0,0);other._probe_tile(20,10,0,L.STONE);other._probe_action(5,20,10,0,0,0);assert.equal(other._probe_value(1,20,10),0);assert.equal(modules[1]._probe_value(1,20,10),1);assert.deepEqual(snapshot(modules[1]),primary);check();
console.log('VISION: '+comparisons+' '+fixtureReferenceLabel+'/pure-JS full maps, paths, bounds, lighting, callbacks, native aliases, growth and isolation comparisons passed.');
