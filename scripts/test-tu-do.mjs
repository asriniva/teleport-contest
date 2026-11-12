import assert from './native-test-assert.mjs';
import {referenceBackend,referenceLabel,assertStackRestored,memoryCheckpoint,assertMemoryGrowth} from './native-test-backend.mjs';
import {readFileSync,writeFileSync} from 'node:fs';
import {callDo,createDoEnvironment} from '../js/nethack/bindings/do.js';
import {C,R,T,withCEnvironment} from '../js/c-runtime/context.js';
const own=process.env.TELEPORT_DO_AUTHOR==='1';
const ref=(await import(own?'../.cache/do-author/reference.mjs':'../.cache/tu-probes/do-reference.mjs')).default;
const hyb=(await import(own?'../.cache/do-author/hybrid.mjs':'../.cache/tu-probes/do-hybrid.mjs')).default;
const text=(m,p)=>{p=Number(p);let e=p;while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.slice(p,e)).toString('latin1');};
let reference=await referenceBackend('do',ref)();const measured={};for(let i=0;i<reference._probe_layout_count();i++)measured[text(reference,reference._probe_layout_name(i))]=Number(BigInt.asIntN(64,reference._probe_layout_value(i)));
const L=own?measured:JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url))).do;
if(own)writeFileSync(new URL('../.cache/do-author/layout.json',import.meta.url),JSON.stringify(L,null,2));
for(const match of readFileSync(new URL('./test-tu-do.mjs',import.meta.url),'utf8').matchAll(/\bL\.([A-Z]\w*)/g))assert.ok(Object.hasOwn(L,match[1]),'compiled fixture constant '+match[1]);
const constant=n=>{assert.ok(Object.hasOwn(L,'lo_'+n),n);let v=BigInt(L['lo_'+n])+(BigInt(L['hi_'+n])<<32n);if(L['csigned_'+n])v=BigInt.asIntN(64,v);return L['csize_'+n]===8?v:Number(v);};
const source=readFileSync(new URL('../js/ported/do.js',import.meta.url),'utf8').replace(/\/\*[\s\S]*?\*\/|"(?:\\.|[^"\\])*"/g,'');
const externals=new Set([...source.matchAll(/\bC\.(\w+)/g)].map(m=>m[1]));const validated=new WeakSet();
function validate(s){if(validated.has(s.moduleKey))return;const e=createDoEnvironment(s,L);for(const k of externals)assert.ok(k in e,'native/header binding '+k);validated.add(s.moduleKey);}
const ported={callDo(s,n,...a){validate(s);return callDo(s,L,n,...a);}};
let modules=[reference,await hyb({nethackPorted:ported})],stacks=modules.map(m=>m._probe_stack()),comparisons=0;
const names=Array.from({length:44},(_,i)=>text(reference,reference._probe_function_name(i))),op=n=>{const i=names.indexOf(n);assert.ok(i>=0,n);return i;};
const deps=Object.fromEntries(Array.from({length:reference._probe_dep_count()},(_,i)=>[text(reference,reference._probe_dep_name(i)),i]));
const snapshot=m=>({state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace())});
function check(){const pair=modules.map(snapshot);if(pair[0].state!==pair[1].state||pair[0].trace!==pair[1].trace){writeFileSync(new URL('../.cache/do-author/actual.json',import.meta.url),JSON.stringify(pair[1],null,2));writeFileSync(new URL('../.cache/do-author/expected.json',import.meta.url),JSON.stringify(pair[0],null,2));}assert.deepEqual(pair[1],pair[0]);modules.forEach((m,i)=>assertStackRestored(m,stacks[i],m._probe_stack()));assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);comparisons++;}
function call(n,...a){const pair=modules.map(m=>m['_probe_'+n](...a));assert.deepEqual(pair[1],pair[0],n);comparisons++;return pair[0];}
const exercised=new Set();const act=(n,a=0,b=0,c=0,d=0)=>{exercised.add(n);const result=call('action',op(n),BigInt(a),BigInt(b),BigInt(c),BigInt(d));check();return result;};
const reset=(seed=1)=>{call('reset',seed);check();},hero=(k,v)=>call('hero',k,BigInt(v)),field=(i,k,v)=>call('objfield',i,k,BigInt(v)),item=(i,t,q=1,w=L.OBJ_INVENT)=>call('object',i,t,BigInt(q),w),prop=(k,f,v)=>call('property',k,f,BigInt(v));
const option=(n,v)=>{assert.ok(Object.hasOwn(deps,n),n);return call('option',deps[n],v);};
const rolls=(...v)=>{call('roll',-1,0);v.forEach((r,i)=>call('roll',i,r));};const trace=()=>text(reference,reference._probe_trace());
function input(which,value){for(const m of modules){const p=m._malloc(BigInt(value.length+1));m.HEAPU8.set(Buffer.from(value+'\0','latin1'),Number(p));m._probe_text(which,BigInt(p));m._free(p);}comparisons++;}
const state=()=>text(reference,reference._probe_snapshot());
for(const[k,v]of Object.entries(measured))assert.equal(L[k],v,k);
// All condition gates operate on native objects and real catalogue class fields.
reset();assert.equal(act('drop',-1),BigInt(L.ECMD_FAIL));act('obj_no_longer_held',-1);act('doddrop');act('danger_uprops');
for(const [mask,expect]of [[0n,1n],[constant('W_ARMOR'),0n],[constant('W_ACCESSORY'),0n],[constant('W_SADDLE'),0n],[1n<<63n,1n]]){reset();item(0,L.DAGGER);field(0,2,mask);assert.equal(act('canletgo',0),expect);}
reset();item(0,L.DAGGER);field(0,2,constant('W_ARMOR'));input(0,'\xffdrop');act('canletgo',0);assert.ok(trace().includes('ÿdrop'));
reset();item(0,L.LOADSTONE,7);field(0,0,1);assert.equal(act('canletgo',0),0n);assert.ok(trace().includes('cannot'));reset();item(0,L.LEASH);field(0,9,123);assert.equal(act('canletgo',0),0n);
for(const eq of [0,1,2]){reset();item(0,L.DAGGER,3);call('equipment',eq,0);assert.equal(act('drop',0),BigInt(L.ECMD_TIME));assert.ok(state().includes('o:0,'+L.DAGGER+','+L.OBJ_FLOOR+','));assert.ok(trace().includes('freeinv:0;'));assert.ok(trace().indexOf('place:0:10:10;')>trace().indexOf('freeinv:0;'));}
for(const n of ['dropx','dropy','dropz']){reset();item(0,L.APPLE,3,n==='dropx'?L.OBJ_INVENT:L.OBJ_FREE);act(n,0,1);assert.ok(trace().includes('place:0:10:10;'));}
reset();item(0,L.DAGGER);assert.equal(act('dodrop'),BigInt(L.ECMD_TIME));assert.ok(trace().includes('getobj:drop:'));assert.ok(trace().includes('resetoccupation;'));
reset();item(0,L.DAGGER);option('can_reach_floor',1);act('drop',0);assert.ok(trace().includes('hitfloor:0:1;'));reset();item(0,L.DAGGER);option('welded',1);call('equipment',0,0);assert.equal(act('drop',0),BigInt(L.ECMD_FAIL));
// Pool/lava thresholds and common deleted-with-boulder cleanup, including a trapped native monster.
for(const terrain of [L.POOL,L.MOAT,L.WATER,L.LAVAPOOL])for(const roll of [0,1,4,5,9]){reset();item(0,L.BOULDER,1,L.OBJ_FREE);call('tile',10,10,terrain,0);rolls(roll);act('boulder_hits_pool',0,10,10,0);assert.ok(trace().includes('dispose:0;'));}
for(const type of [L.PIT,L.SPIKED_PIT,L.HOLE,L.TRAPDOOR]){reset();item(0,L.BOULDER,1,L.OBJ_FREE);call('trap',0,10,10,type,1);act('flooreffects',0,10,10);assert.ok(trace().includes('useupf:0:1;'));assert.ok(trace().includes('delfloortrap:0;'));
 reset();item(0,L.BOULDER,1,L.OBJ_FREE);call('trap',0,10,10,type,1);call('set_monster',0,L.PM_HUMAN,10,10,100,1);act('flooreffects',0,10,10);}
reset();item(0,L.BOULDER,1,L.OBJ_FREE);call('trap',0,10,10,L.PIT,1);call('set_monster',0,L.PM_HUMAN,10,10,100,1);hero(34,513);hero(35,514);act('flooreffects',0,10,10);assert.ok(state().includes('bhit:513,514;'));
for(const half of [0,1]){reset();item(0,L.BOULDER,1,L.OBJ_FREE);call('trap',0,10,10,L.PIT,1);hero(4,1);hero(5,L.TT_PIT);prop(L.HALF_PHDAM,0,half);call('option',506,half?2:1);rolls(14);act('flooreffects',0,10,10);assert.ok(trace().includes('losehp:'+(half?8:15)+':squished under a boulder:'));assert.equal((trace().match(/delfloortrap:0;/g)||[]).length,1);assert.equal((trace().match(/bury_objs:10:10;/g)||[]).length,1);}
reset();item(0,L.DAGGER,1,L.OBJ_FREE);assert.equal(act('flooreffects',0,10,10),0n);
for(const mode of [1,2]){reset();item(0,L.GLOB_OF_GREEN_SLIME,1,L.OBJ_FREE);item(1,L.GLOB_OF_GREEN_SLIME,1,L.OBJ_FLOOR);field(0,5,1);field(1,5,1);option('obj_nexto_xy',2);option('obj_meld',mode);assert.equal(act('flooreffects',0,10,10),mode===2?1n:0n);assert.ok(trace().includes('meld:0:1;'));assert.ok(state().includes('o:'+(mode===2?0:1)+':null;'));}
for(const bless of [-1,0,1])for(const blind of [0,1]){reset();item(0,L.DAGGER,1,L.OBJ_FREE);if(bless<0)field(0,0,1);if(bless>0)field(0,1,1);prop(L.BLINDED,0,blind);act('doaltarobj',0);}
reset();item(0,L.CRYSKNIFE);field(0,4,1);call('option',500,1);rolls(0);act('obj_no_longer_held',0);assert.ok(!trace().includes('caller:'));
reset();item(0,L.RIN_FREE_ACTION);act('trycall',0);reset();item(0,L.CORPSE);option('u_safe_from_fatal_corpse',1);assert.equal(act('better_not_try_to_drop_that',0),0n);for(const answer of [0,121]){reset();item(0,L.CORPSE);option('paranoid_ynq',answer);assert.equal(act('better_not_try_to_drop_that',0),answer===121?0n:1n);assert.ok(trace().includes('Drop the value corpse without value protection on?'));}
// Every sink transformation, successful relocation, and original 200-attempt failure cap.
for(let effect=0;effect<4;effect++){reset();call('tile',10,10,L.SINK,0);rolls(effect,1,1);act('polymorph_sink');assert.ok(trace().includes('newsym:'));}
reset();call('tile',10,10,L.SINK,0);rolls(2,2,1);act('polymorph_sink');assert.ok(state().includes('tile:10,10,'+L.ALTAR+',4,'));reset();call('tile',10,10,L.SINK,3);hero(33,1);rolls(0);act('polymorph_sink');assert.ok(state().includes('tile:10,10,'+L.FOUNTAIN+',1,0,'));reset();assert.equal(act('polymorph_sink'),0n);reset();call('tile',10,10,L.SINK,3);rolls(0);assert.equal(act('teleport_sink'),1n);assert.ok(trace().includes('terrain:2:1:'+L.SINK+';'));
reset();call('tile',10,10,L.SINK,0);call('tile',2,1,L.STONE,0);rolls(0);assert.equal(act('teleport_sink'),0n);assert.equal((trace().match(/rn2:/g)||[]).length,200);
const rings=['RIN_SEARCHING','RIN_SLOW_DIGESTION','RIN_LEVITATION','RIN_POISON_RESISTANCE','RIN_AGGRAVATE_MONSTER','RIN_SHOCK_RESISTANCE','RIN_CONFLICT','RIN_SUSTAIN_ABILITY','RIN_GAIN_STRENGTH','RIN_GAIN_CONSTITUTION','RIN_INCREASE_ACCURACY','RIN_INCREASE_DAMAGE','RIN_HUNGER','RIN_ADORNMENT','RIN_REGENERATION','RIN_INVISIBILITY','RIN_FREE_ACTION','RIN_SEE_INVISIBLE','RIN_STEALTH','RIN_FIRE_RESISTANCE','RIN_COLD_RESISTANCE','RIN_PROTECTION_FROM_SHAPE_CHAN','RIN_PROTECTION','RIN_WARNING','RIN_TELEPORTATION','RIN_TELEPORT_CONTROL','RIN_POLYMORPH','RIN_POLYMORPH_CONTROL'];
for(const ring of rings)for(const blind of [0,1]){reset();item(0,L[ring]);call('tile',10,10,L.SINK,0);prop(L.BLINDED,0,blind);rolls(1,1,1);act('dosinkring',0);if(ring==='RIN_SEARCHING'||ring==='RIN_SLOW_DIGESTION')assert.ok(trace().includes('place:0:10:10;'));else assert.ok(trace().includes('useup:0;'));}
// Held-container recursion and crysknife stochastic reversion preserve exact object fields.
for(const proof of [0,1])for(const roll of [0,1,9]){reset();item(0,L.CRYSKNIFE);field(0,4,proof);rolls(roll);act('obj_no_longer_held',0);assert.ok(state().includes('o:0,'+(!proof||roll===0?L.WORM_TOOTH:L.CRYSKNIFE)+','));}
reset();item(0,L.DAGGER);item(1,L.CRYSKNIFE,1,L.OBJ_CONTAINED);field(0,10,1);act('obj_no_longer_held',0);assert.ok(state().includes('o:1,'+L.WORM_TOOTH+','));
// Swallowed food policy receives controlled native digestion-classifier responses.
for(const typ of [L.DAGGER,L.MEAT_RING,L.CORPSE,L.GLOB_OF_GREEN_SLIME]){reset();item(0,typ,1,L.OBJ_FREE);hero(0,1);if(typ===L.GLOB_OF_GREEN_SLIME)field(0,5,1);option('dmgtype_fromattack',1);field(0,6,L.PM_WRAITH);const eaten=act('engulfer_digests_food',0);assert.equal(eaten,typ===L.DAGGER?0n:1n);if(typ!==L.DAGGER)assert.ok(trace().includes('delobj:0;'));}
reset();item(0,L.DAGGER,1,L.OBJ_FREE);hero(0,1);act('dropz',0,0);assert.ok(trace().includes('mpickobj:0:0;'));
// Menu cancellation and selection execute actual native callback pointers and allocated menu records.
reset();item(0,L.DAGGER,5);assert.equal(act('menudrop_split',0,2),BigInt(L.ECMD_TIME));assert.ok(trace().includes('split:0:2:1;'));
for(const n of ['menu_drop','doddrop']){reset();item(0,L.DAGGER,5);hero(13,L.MENU_FULL);option('query_category',-1);act(n,0);reset();item(0,L.DAGGER,5);hero(13,L.MENU_FULL);option('query_category',1);call('option',503,L.ALL_TYPES_SELECTED);option('query_objlist',1);call('option',504,2);assert.equal(act(n,0),BigInt(L.ECMD_TIME));assert.ok(trace().includes('split:0:2:'));assert.ok(trace().includes('place:'));}
reset();item(0,L.DAGGER);hero(13,L.MENU_FULL);option('query_category',0);assert.equal(act('menu_drop',0),BigInt(L.ECMD_OK));assert.ok(!trace().includes('query_objlist:'));
reset();item(0,L.DAGGER);hero(13,L.MENU_COMBINATION);option('ggetobj',L.ALL_FINISHED);assert.equal(act('menu_drop',0),BigInt(L.ECMD_TIME));assert.ok(!trace().includes('query_objlist:'));
reset();for(let i=0;i<30;i++)item(i,L.DAGGER);hero(0,1);hero(13,L.MENU_FULL);option('query_category',1);call('option',503,65);call('option',507,deps.freeinv+1);act('menu_drop',0);assert.equal((trace().match(/mpickobj:/g)||[]).length,30);assert.equal(call('stack_span'),0n);
reset();item(0,L.DAGGER);hero(13,L.MENU_TRADITIONAL);call('option',502,1);act('doddrop');assert.ok(trace().includes('ggetobj:drop:'));assert.ok(trace().includes('place:0:10:10;'));
for(const direction of ['up','down']){reset();input(0,direction);assert.equal(act('u_stuck_cannot_go'),0n);hero(1,0);assert.equal(act('u_stuck_cannot_go'),1n);assert.ok(trace().includes('cannot'));}
// Level entrypoints, insurance lifecycle and deferred-message ownership use native NHFILE storage.
reset();assert.equal(act('currentlevel_rewrite'),0n);assert.ok(trace().includes('controlled unavailable file'));
reset();option('create_levelfile',1);assert.equal(act('currentlevel_rewrite'),1n);act('save_currentstate');assert.ok(trace().includes('savestateinlock;'));
reset();hero(19,1);act('save_currentstate');assert.equal(state().match(/^hero:([^;]+)/)[1].split(',')[16],'1');reset();hero(19,1);call('option',505,1);option('create_levelfile',1);act('save_currentstate');assert.ok(trace().includes('bufon:7;'));assert.ok(trace().includes('savelev:'));assert.ok(trace().includes('closefile;'));
reset();act('u_collide_m',-1);assert.ok(trace().includes('level arrival collision: no monster?'));
reset();call('set_monster',0,L.PM_HUMAN,10,10,100,0);rolls(1);act('u_collide_m',0);assert.ok(trace().includes('mnexto:0:'));
reset();call('set_monster',0,L.PM_HUMAN,10,10,100,0);rolls(0);act('u_collide_m',0);assert.ok(state().startsWith('hero:11,11,'));
reset();act('dodown');act('doup');act('familiar_level_msg');act('hellish_smoke_mesg');hero(20,1);act('hellish_smoke_mesg');assert.ok(trace().includes('It is hot here.'));act('temperature_change_msg',-1);
reset();hero(25,0);act('goto_level',0,0,0,0);reset();act('goto_level',0,0,0,0);assert.ok(trace().includes('createfile:'));
reset();option('create_levelfile',1);act('goto_level',0,0,0,0);assert.ok(state().startsWith('hero:10,10,2,4,'));assert.ok(trace().includes('mklev;'));assert.ok(trace().includes('vision_reset;'));
for(const dest of [0,1])for(const stairs of [0,1])for(const falling of [0,1])for(const portal of [0,1]){reset();option('create_levelfile',1);act('goto_level',dest,stairs,falling,portal);assert.ok(trace().includes('obj_delivery:1;'));if(falling&&!stairs&&!portal)assert.ok(trace().includes('losehp:'));}
reset();item(0,L.DAGGER);field(0,17,1);field(0,7,(1n<<53n)+1n);rolls(0);prop(L.LEVITATION,1,constant('W_ARTI'));option('artifact_has_invprop',1);act('dodown');assert.ok(trace().includes('caller:do.c:1165:dodown;'));assert.equal(state().match(/o:0,([^;]+)/)[1].split(',')[7],String((1n<<53n)+101n));
reset();input(0,'before passage');input(1,'You materialize on a different level.');act('schedule_goto',0,0,0,0);assert.ok(state().includes('You materialize'));act('maybe_lvltport_feedback');assert.ok(trace().includes('You materialize on a different level.'));act('deferred_goto');
reset();act('final_level');assert.ok(trace().includes('create_mplayers:'));assert.ok(trace().includes('gain_guardian_angel;'));
// Corpse location, native revival outcomes, timer reuse and zombie transformation.
for(const where of [L.OBJ_INVENT,L.OBJ_FLOOR,L.OBJ_BURIED,L.OBJ_MINVENT]){reset();item(0,L.CORPSE,1,where);field(0,13,0);act('revive_corpse',0);reset();item(0,L.CORPSE,1,where);field(0,13,0);option('revive',1);assert.equal(act('revive_corpse',0),1n);assert.ok(trace().includes('dispose:0;'));}
reset();item(0,L.CORPSE,1,L.OBJ_FLOOR);act('revive_mon',0,0);assert.ok(trace().includes('start_timer:'));reset();item(0,L.CORPSE,1,L.OBJ_FLOOR);option('zombie_form',L.PM_HUMAN);act('zombify_mon',0,0);assert.ok(trace().includes('set_corpsenm:0:'));
// Safety flagcounter is a real writable native int, with increment and suppression semantics.
for(const timeout of [1n,128n,256n,(1n<<53n)+1n]){reset();prop(L.STONED,0,timeout);assert.equal(act('danger_uprops'),1n);}
reset();hero(14,1);option('monster_nearby',1);assert.equal(act('cmd_safety_prevention',0,0,0,0),1n);assert.ok(state().includes('cell:0,1;'));assert.equal(act('donull'),BigInt(L.ECMD_OK));reset();assert.equal(act('donull'),BigInt(L.ECMD_TIME));
for(const blind of [0,1,4,5,100]){reset();hero(17,blind);prop(L.BLINDED,0,blind);act('wipeoff');reset();hero(17,blind);prop(L.BLINDED,0,blind);act('dowipe');if(blind){assert.ok(trace().includes('occupation:'));call('occupation');check();}}
for(const side of [constant('LEFT_SIDE'),constant('RIGHT_SIDE'),constant('BOTH_SIDES')]){reset();act('set_wounded_legs',side,50);assert.ok(trace().includes('settimeout:50;'));act('legs_in_no_shape');act('heal_legs',0);assert.ok(state().includes('p:'+L.WOUNDED_LEGS+',0,0,0;'));}
assert.deepEqual([...exercised].sort(),names.slice().sort(),'all 44 original functions execute');
// Actual native growth and C->JS reentry within world callbacks observe fresh state.
reference=await referenceBackend('do',ref)();modules=[reference,await hyb({nethackPorted:ported})];stacks=modules.map(m=>m._probe_stack());reset();item(0,L.DAGGER);const before=modules.map(memoryCheckpoint);call('callback',deps.freeinv,deps.freeinv);act('drop',0);assert.ok(trace().includes('growth:'));assert.ok(trace().includes('reentry:'));modules.forEach((m,i)=>assertMemoryGrowth(m,before[i]));
const primary=snapshot(modules[1]),other=await hyb({nethackPorted:ported});const sentinelR={},sentinelT={},outer={rectState:sentinelR,trackState:sentinelT};withCEnvironment(outer,()=>{other._probe_reset(12);other._probe_callback(-1,deps.freeinv);other._probe_object(0,L.DAGGER,1n,L.OBJ_INVENT);assert.equal(other._probe_action(op('drop'),0n,0n,0n,0n),BigInt(L.ECMD_TIME));assert.ok(text(other,other._probe_trace()).includes('place:0:10:10;'));assert.equal(C,outer);assert.equal(R,sentinelR);assert.equal(T,sentinelT);});assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);assert.deepEqual(snapshot(modules[1]),primary);comparisons++;
console.log('DO '+referenceLabel+': '+comparisons.toLocaleString('en-US')+' comparisons passed; all 44 original functions.');
