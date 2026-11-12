import assert from './native-test-assert.mjs';
import {DataView,assertStackRestored,memoryCheckpoint,assertMemoryGrowth,referenceBackend,referenceLabel} from './native-test-backend.mjs';
import {readFileSync,writeFileSync} from 'node:fs';
import {callMthrowu} from '../js/nethack/bindings/mthrowu.js';
import * as core from '../js/ported/mthrowu.js';
import {C,R,T} from '../js/c-runtime/context.js';
const own=process.env.TELEPORT_MTHROWU_AUTHOR==='1';
const ref=(await import(own?'../.cache/mthrowu-author/reference.mjs':'../.cache/tu-probes/mthrowu-reference.mjs')).default,hyb=(await import(own?'../.cache/mthrowu-author/hybrid.mjs':'../.cache/tu-probes/mthrowu-hybrid.mjs')).default;
let reference=await referenceBackend('mthrowu',ref)();
function text(m,p){p=Number(p);if(!p)return null;let end=p;while(m.HEAPU8[end])end++;return Buffer.from(m.HEAPU8.slice(p,end)).toString('latin1');}
const measured={};for(let i=0;i<reference._probe_layout_count();i++)measured[text(reference,reference._probe_layout_name(i))]=Number(BigInt.asIntN(64,reference._probe_layout_value(i)));
const L=own?measured:JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url))).mthrowu;if(own)writeFileSync(new URL('../.cache/mthrowu-author/layout.json',import.meta.url),JSON.stringify(L,null,2));
for(const key of ["ACID_RES", "ACID_VENOM", "AD_ACID", "AD_FIRE", "AD_MAGM", "AD_SLEE", "AKLYS", "ARROW", "ART_MJOLLNIR", "BLINDED", "BLINDING_VENOM", "BOULDER", "BOW", "BRK_BY_HERO", "BRK_MELEE", "CONFUSION", "CREAM_PIE", "CROSSBOW_BOLT", "DAGGER", "DOOR", "D_CLOSED", "EGG", "ELVEN_ARROW", "ELVEN_BOW", "FIRST_GLASS_GEM", "FIRST_REAL_GEM", "FUMBLING", "GEM_CLASS", "HALLUC", "HALLUC_RES", "IRONBARS", "LAVAWALL", "LEATHER_GLOVES", "NUMMONS", "NUM_OBJECTS", "OBJ_FLOOR", "PM_COCKATRICE", "PM_HUMAN", "PM_WHITE_UNICORN", "PM_XORN", "POT_ACID", "ROCK", "ROOM", "STONE", "STRANGE_OBJECT", "STUNNED", "WAR_HAMMER", "WATER", "obj_owornmask"])assert.ok(Object.hasOwn(L,key),'missing native layout key: '+key);
const ported={callMthrowu:(services,name,...args)=>callMthrowu(services,L,name,...args)},modules=[reference,await hyb({nethackPorted:ported})],stacks=modules.map(m=>m._probe_stack());let comparisons=0;
const dependencies={};for(let i=0;i<reference._probe_dep_count();i++)dependencies[text(reference,reference._probe_dep_name(i))]=i;
const snapshot=m=>({state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace()),frees:m._probe_frees()});
function check(){assert.deepEqual(snapshot(modules[1]),snapshot(modules[0]));assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);modules.forEach((m,i)=>assertStackRestored(m,stacks[i]));comparisons++;}
function call(name,...args){const out=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(out[1],out[0],name+':'+args);comparisons++;check();return out[0];}
const reset=()=>call('reset'),act=(op,a=0,b=0,c=0,d=0,e=0,f=0,g=0)=>Number(call('action',op,a,b,c,d,e,f,g)),opt=(n,v)=>{assert.ok(Number.isInteger(dependencies[n]),n);call('option',dependencies[n],BigInt(v));},object=(i,f,v)=>call('object',i,f,BigInt(v)),mon=(i,f,v)=>call('set_monster',i,f,BigInt(v)),hero=(f,v)=>call('hero',f,BigInt(v)),prop=(n,f,v)=>call('property',n,f,BigInt(v)),attach=(i,m,w=0)=>call('attach',i,m,w),out=(slot,i)=>call('output',slot,i),position=(i,x,y)=>call('position',i,x,y),terrain=(x,y,t,f=0)=>call('terrain',x,y,t,f),trace=()=>text(reference,reference._probe_trace()),vision=(x,y,b)=>call('vision',x,y,b);
function rolls(...values){for(const m of modules)for(const n of values)m._probe_roll(n);}
const fields=prefix=>text(reference,reference._probe_snapshot()).split(';').find(s=>s.startsWith(prefix+':'))?.split(':');
const obj=i=>fields('o'+i),monster=i=>fields('m'+i);
reset();for(const[k,v]of Object.entries(measured))assert.equal(L[k],v,k);for(const key of ['PM_HUMAN','DAGGER','ARROW','AKLYS','W_WEP','NUM_OBJECTS','NUMMONS','IN_SIGHT','COULD_SEE'])assert.ok(Number.isSafeInteger(L[key]),key);
// Every readonly row is checked against the actual original private C array.
for(const[table,rows]of [[0,core.breathwep],[1,core.hallublasts]])for(let i=0;i<rows.length;i++){assert.equal(text(reference,reference._probe_table(table,i)),rows[i]);comparisons++;}assert.equal(core.breathwep.length,10);assert.equal(core.hallublasts.length,96);
for(let i=0;i<core.hallublasts.length;i++){reset();rolls(i);act(0);assert.ok(trace().includes('hallu:'+core.hallublasts[i]));assert.ok(trace().includes('mthrowu.c:54:rnd_hallublast'));}
for(const ad of [-5,0,L.AD_MAGM,L.AD_FIRE,L.AD_SLEE,L.AD_ACID,31]){reset();act(13,ad);prop(L.HALLUC,0,1);rolls(3);act(13,ad);assert.ok(trace().includes(core.hallublasts[3]));prop(L.HALLUC_RES,1,1);act(13,ad);}
// Launcher, ammunition, races and quantity limits, across the actual monster catalogue.
for(let pm=0;pm<L.NUMMONS;pm++){reset();mon(0,0,pm);object(0,0,L.ELVEN_ARROW);object(0,1,20);object(1,0,L.ELVEN_BOW);object(1,2,8);attach(0,0);attach(1,0,1);rolls(2);act(1,0);act(4,0,0,1);assert.ok(Number(obj(0)[4])===20);}
for(const ammo of [L.DAGGER,L.ARROW,L.ELVEN_ARROW,L.CROSSBOW_BOLT,L.ROCK])for(const qty of [1n,2n,100n,(1n<<53n)+1n]){reset();object(0,0,ammo);object(0,1,qty);object(1,0,L.ELVEN_BOW);attach(0,0);attach(1,0,1);rolls(3);const n=act(4,0,0,1);assert.ok(n>=1&&BigInt(n)<=qty);mon(0,3,1);assert.equal(act(4,0,0,1),1);}
reset();object(0,1,10);object(1,0,L.BOW);attach(0,0);attach(1,0,1);assert.equal(act(1,0),0);object(0,0,L.ARROW);assert.equal(act(1,0),1);
// Named/unnamed, singular/plural, hit/miss and real obj** replacement on potion use.
for(const named of [0,1])for(const hit of [0,1])for(const qty of [1n,2n]){reset();object(0,1,qty);out(0,0);rolls(hit?0:19);assert.equal(act(2,10,7,0,named),hit);assert.ok(trace().includes(hit?'hit':'miss'));}
reset();rolls(0);assert.equal(act(2,10,7,-1,1),1);assert.ok(trace().includes('the named object'));
for(const type of [L.ACID_VENOM,L.ROCK,L.POT_ACID]){reset();object(0,0,type);out(0,0);if(type===L.ACID_VENOM)prop(L.ACID_RES,1,1);if(type===L.ROCK)mon(-1,0,L.PM_XORN);rolls(0);act(2,10,9,0,0);if(type===L.POT_ACID){assert.equal(fields('ptr0')[1],'-1');assert.equal(obj(0),undefined);assert.equal(reference._probe_frees(),1);}}
// Ground/migration/consumption ownership and true frees, including C boolean narrowing.
for(const type of [L.DAGGER,L.CREAM_PIE,L.EGG,L.BLINDING_VENOM])for(const hit of [0,1]){reset();object(0,0,type);attach(0,0);const gone=act(3,0,hit,5,5);if(type===L.CREAM_PIE||type===L.BLINDING_VENOM||(type===L.EGG&&hit)){assert.equal(gone,1);assert.equal(obj(0),undefined);}else{assert.equal(gone,0);assert.equal(Number(obj(0)[7]),L.OBJ_FLOOR);}}
reset();opt('should_mulch_missile',-128);assert.equal(act(3,0,1,5,5),1);assert.equal(reference._probe_frees(),1);
for(const dependency of ['ship_object','flooreffects']){reset();if(dependency==='ship_object')opt('down_gate',0);opt(dependency,1);act(3,0,0,5,5);assert.ok(trace().includes(dependency+':'));}
// Monster hit/miss, poison, petrification, blindness and source -1 rolling behavior.
for(const hit of [0,1])for(const range of [-1,0,3]){reset();call('bhit',15,10);rolls(hit?0:19);const stopped=act(6,0,0,range,1);if(hit){assert.equal(monster(0)[3],'93');assert.equal(stopped,range===-1?0:1);}else if(range===0)assert.equal(stopped,1);}
for(const type of [L.ARROW,L.EGG,L.CREAM_PIE,L.ACID_VENOM]){reset();object(0,0,type);object(0,9,L.PM_COCKATRICE);object(0,6,1);opt('can_blnd',1);opt('dmgval',type===L.CREAM_PIE?0:7);call('bhit',15,10);rolls(0,29,4,24);act(6,0,0,0,1);if(type===L.CREAM_PIE){assert.equal(monster(0)[9],'0');assert.equal(monster(0)[8],'25');}if(type===L.EGG)assert.ok(trace().includes('petrify:'));}
// Real source extraction/splitting and projectile travel, with both flight checks.
for(const qty of [1n,3n])for(const blocked of [0,1,2]){reset();object(0,1,qty);attach(0,0,1);if(blocked===1)terrain(14,10,L.STONE);if(blocked===2)terrain(13,10,L.DOOR,L.D_CLOSED);rolls(1,1,1,1,1,1);act(9,0,15,10,-1,0,4,0);assert.ok(trace().includes('extract:'));if(qty>1n)assert.equal(obj(0)[4],'2');if(blocked===1)assert.ok(trace().includes('place:'));}
reset();object(0,1,1);object(0,3,1);attach(0,0,1);rolls(0,1,1);act(9,0,15,10,-1,0,5,0);assert.ok(trace().includes('misfire')||trace().includes('slip'));
reset();object(0,0,L.POT_ACID);attach(0,0);terrain(13,10,L.IRONBARS);opt('breaks',1);rolls(0);act(9,0,15,10,-1,0,4,0);assert.equal(obj(0),undefined);assert.equal(reference._probe_frees(),1);assert.ok(trace().includes('dissolve_bars:'));
// Successful/failed catches, intrinsic-only confusion/stun and role bonuses.
for(const property of [null,L.CONFUSION,L.STUNNED,L.FUMBLING,L.BLINDED])for(const external of [0,1]){reset();opt('freehand',1);opt('acurr',18);if(property!==null)prop(property,external,1);rolls(0);const caught=act(8,0);const blocks=property!==null&&(property===L.CONFUSION||property===L.STUNNED?external===0:true);assert.equal(caught,blocks?0:1);}
for(const gem of [L.FIRST_REAL_GEM,L.FIRST_GLASS_GEM,L.ROCK]){reset();mon(-1,0,L.PM_WHITE_UNICORN);object(0,0,gem);object(0,13,L.GEM_CLASS);const caught=act(7,0,0);assert.equal(caught,gem===L.ROCK?0:1);}
// Returning weapons: persistent source timer, exact raw64 worn masks and damage cell.
for(const tethered of [0,1])for(const outcome of [0,1,2]){reset();object(0,0,tethered?L.AKLYS:L.WAR_HAMMER);if(!tethered)object(0,10,L.ART_MJOLLNIR);object(0,11,1n<<63n);call('bhit',12,10);if(outcome===2)mon(0,3,1);rolls(outcome?1:0,1,1,2);act(10,0,0,tethered);if(outcome===1){assert.equal(Number(monster(0)[15]),tethered?0:-1);if(tethered){const p=Number(reference._probe_pointer(0,0));assert.ok(new DataView(reference.HEAPU8.buffer).getBigUint64(p+L.obj_owornmask,true)&(1n<<63n));}}}
reset();hero(5,2000);call('bhit',12,10);rolls(1,1,1,1,1,1);act(10,0,0,1);const first=trace().match(/Projectile return/g)?.length??0;hero(5,2200);act(10,0,1,1);assert.equal(trace().match(/Projectile return/g)?.length??0,first);hero(5,2601);act(10,0,2,1);assert.ok((trace().match(/Projectile return/g)?.length??0)>first);
// Inventory consumption and hero-versus-monster list identity.
for(const qty of [1n,2n,(1n<<53n)+7n]){reset();object(0,1,qty);attach(0,0);assert.equal(act(25,0,L.DAGGER),0);act(16,0,0);if(qty===1n)assert.equal(obj(0),undefined);else assert.equal(BigInt(obj(0)[4]),qty-1n);}
reset();attach(0,-1);assert.equal(act(25,-1,L.DAGGER),0);reset();attach(0,0);act(15,0,0);assert.equal(reference._probe_frees(),1);
// Line geometry, boulders, callback traversal and actual typed C callback invocation.
for(const [ax,ay,bx,by]of [[10,10,15,10],[10,10,10,15],[10,10,15,15],[10,10,13,15],[10,10,10,10],[1,1,9,1],[2,2,8,2]])for(const handling of [0,1,2]){reset();act(22,ax,ay,bx,by,handling);opt('clear_path',0);for(let x=1;x<20;x++)vision(x,10,0);act(22,ax,ay,bx,by,handling);call('option',498,12n);call('option',497,10n);act(21,ax,ay,bx,by);}
for(const typ of [L.ROOM,L.STONE,L.DOOR,L.WATER,L.LAVAWALL]){reset();terrain(12,10,typ,L.D_CLOSED);act(20,12,10);act(22,10,10,15,10,1);}
reset();assert.equal(act(24,0),1);mon(0,12,15);mon(0,13,10);assert.equal(act(24,0),0);mon(0,12,10);mon(0,13,10);act(23,-1,0);
// All native object records classify through the original bars switch.
for(let type=0;type<L.NUM_OBJECTS;type++){reset();object(0,0,type);object(0,9,L.PM_HUMAN);out(0,0);act(27,0,10,10,11,10,0,-1);}
for(const raw of [0,1,127,128,255,256,-1,-128,2147483647,-2147483648]){reset();object(0,0,L.ARROW);out(0,0);assert.equal(act(27,0,10,10,11,10,raw,-1),(raw<<24)>>24);}
for(const type of [L.DAGGER,L.BOULDER,L.LEATHER_GLOVES,L.POT_ACID]){reset();object(0,0,type);out(0,0);act(26,0,10,10,11,10,L.BRK_BY_HERO|L.BRK_MELEE);assert.ok(trace().includes('bars')||trace().includes('Whang')||trace().includes('Flapp')||trace().includes('Clonk'));}
reset();object(0,0,L.POT_ACID);out(0,0);opt('hero_breaks',1);act(26,0,10,10,11,10,L.BRK_BY_HERO);assert.equal(fields('ptr0')[1],'-1');assert.ok(trace().includes('dissolve_bars:'));
// Full public attack dispatch: actual ownership and source target/counter cleanup.
for(const operation of [5,11,17]){reset();object(0,1,4);object(0,0,L.ARROW);object(1,0,L.BOW);attach(0,0);attach(1,0,1);position(1,10,10);rolls(2,1,1,1,1,1,1,1,1,1);if(operation===5){call('bhit',10,10);act(22,10,10,15,10,1);act(5,0,0,1);}else if(operation===11)act(11,0,1);else act(17,0);assert.equal(fields('global')[17],[0,0,L.STRANGE_OBJECT,0].join(','));}
for(const op of [12,14,18,19])for(const canceled of [0,1]){reset();call('attack',0,L.AD_FIRE,3);mon(0,7,canceled);position(1,10,10);rolls(1,0,4,5,6);if(op===12||op===18)call('attack',0,L.AD_ACID,3);act(op,0,0,op===12||op===14?1:0);if(canceled)assert.ok(trace().includes('cough')||trace().includes('rattle'));else if(op===14||op===19)assert.ok(trace().includes('dobuzz:'),'op='+op+' canceled='+canceled+' '+trace());}
reset();call('option',500,1n);object(0,1,4);rolls(1);act(4,0,0,-1);assert.ok(!trace().includes('mthrowu.c:'));
// Fresh instances force genuine growth at native C callbacks while original JS is active.
for(const name of ['xname','obj_extract_self','place_object','dmgval','select_rwep']){reset();reference=await referenceBackend('mthrowu',ref)();modules[0]=reference;modules[1]=await hyb({nethackPorted:ported});stacks.splice(0,stacks.length,...modules.map(m=>m._probe_stack()));reset();const before=modules.map(memoryCheckpoint);call('callback',dependencies[name],dependencies[name]);object(0,1,2);attach(0,0,1);rolls(1,1,1,1,1);if(name==='xname'){act(22,10,10,15,10,1);act(5,0,0,-1);}else if(name==='dmgval'){call('bhit',15,10);rolls(0);act(6,0,0,0,1);}else if(name==='select_rwep')act(17,0);else act(9,0,15,10,-1,0,3,0);assert.ok(trace().includes('grow:'),name+': '+trace());assert.ok(trace().includes('reenter:'),name+': '+trace());modules.forEach((m,i)=>assertMemoryGrowth(m,before[i]));}
// One dispatcher, two actual Modules; the second runs source functions and owns state.
reset();call('bhit',12,10);hero(5,100000);rolls(1,1);act(10,0,0,1);const primary=snapshot(modules[1]),other=await hyb({nethackPorted:ported});other._probe_reset();other._probe_bhit(12,10);other._probe_roll(1);other._probe_roll(1);other._probe_action(10,0,0,1,0,0,0,0);assert.ok(text(other,other._probe_trace()).includes('Projectile return'));assert.deepEqual(snapshot(modules[1]),primary);check();
console.log('MTHROWU: '+comparisons+' '+referenceLabel+'/hybrid tables, projectile ownership, combat state, callbacks and isolation comparisons passed.');
