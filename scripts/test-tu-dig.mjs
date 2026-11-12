import {DataView,Int32Array,referenceBackend,referenceLabel,assertStackRestored,assertMemoryGrowth} from './native-test-backend.mjs';
import assert from './native-test-assert.mjs';
import {readFileSync} from 'node:fs';import{resolve}from'node:path';import{pathToFileURL}from'node:url';
import{callDig}from'../js/nethack/bindings/dig.js';import * as core from '../js/ported/dig.js';import{C,R,T}from'../js/c-runtime/context.js';
const author=process.env.TELEPORT_DIG_PROBES,dir=author?pathToFileURL(resolve(author)+'/'):new URL('../.cache/tu-probes/',import.meta.url),referenceFactory=(await import(new URL('dig-reference.mjs',dir))).default,hybridFactory=(await import(new URL('dig-hybrid.mjs',dir))).default,ref=await referenceBackend('dig',referenceFactory)();
function text(m,p){if(!p)return null;let e=Number(p);while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.slice(Number(p),e)).toString();}
const L={size:Number(ref._probe_context_size())};for(let i=0;i<ref._probe_layout_count();i++){const k=text(ref,ref._probe_layout_name(i)),v=ref._probe_layout_value(i);L[k]=/^(M1_|M2_|W_)/.test(k)||['LEFT_SIDE','RIGHT_SIDE'].includes(k)?BigInt.asUintN(64,v).toString():Number(BigInt.asIntN(64,v));}
if(!author)assert.deepEqual(L,JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url))).dig);
const runtime={dig:(services,name,...args)=>callDig(services,L,name,...args)},modules=[ref,await hybridFactory({nethackPorted:runtime})],stacks=modules.map(m=>m._probe_stack()),names=["rm_waslit", "mkcavepos", "mkcavearea", "pick_can_reach", "dig_typ", "is_digging", "dig_check", "digcheck_fail_message", "dig", "furniture_handled", "holetime", "fillholetyp", "digactualhole", "liquid_flow", "dighole", "dig_up_grave", "use_pick_axe", "use_pick_axe2", "watchman_canseeu", "watch_dig", "mdig_tunnel", "draft_message", "zap_dig", "adj_pit_checks", "pit_flow", "buried_ball", "buried_ball_to_punishment", "buried_ball_to_freedom", "bury_an_obj", "bury_objs", "unearth_objs", "rot_organic", "rot_corpse", "wiz_debug_cmd_bury"],returnKeys=[
  "An",
  "Can_dig_down",
  "Is_botlevel",
  "Monnam",
  "On_ladder",
  "On_stairs",
  "Yobjnam2",
  "abon",
  "add_damage",
  "adjalign",
  "align_str",
  "altar_wrath",
  "altarmask_at",
  "an",
  "angry_guards",
  "angry_priest",
  "b_trapped",
  "body_part",
  "break_statue",
  "breaksink",
  "can_reach_floor",
  "cant_reach_floor",
  "cnv_trap_obj",
  "corpse_xname",
  "costly_spot",
  "count_wsegs",
  "currency",
  "cvt_sdoor_to_door",
  "dbon",
  "del_engr_at",
  "depth",
  "desecrate_altar",
  "dmgval",
  "do_attack",
  "does_block",
  "dogushforth",
  "dotrap",
  "dryup",
  "end_burn",
  "exercise",
  "expels",
  "explode",
  "feel_newsym",
  "feeltrap",
  "fire_damage",
  "fire_damage_chain",
  "flush_screen",
  "fracture_rock",
  "goto_level",
  "hard_helmet",
  "hideunder",
  "impact_drop",
  "in_town",
  "ledger_no",
  "make_angry_shk",
  "may_dig",
  "maybe_unhide_at",
  "mb_trapped",
  "mbodypart",
  "migrate_to_level",
  "minliquid",
  "mintrap",
  "mon_nam",
  "newsym",
  "o_unleash",
  "obj_ice_effects",
  "otense",
  "pay_for_damage",
  "pickup",
  "pooleffects",
  "recalc_block_point",
  "rloc",
  "seetrap",
  "shkname",
  "shopdig",
  "simpleonames",
  "spot_checks",
  "spoteffects",
  "stackobj",
  "stairway_at",
  "stolen_value",
  "stop_occupation",
  "switch_terrain",
  "teleport_pet",
  "the",
  "tmp_at",
  "u_wipe_engr",
  "uescaped_shaft",
  "unblock_point",
  "update_inventory",
  "uteetering_at_seen_pit",
  "wake_nearby",
  "water_damage_chain",
  "welded",
  "wield_tool",
  "xname",
  "yname",
  "yobjnam"
];let comparisons=0;
function bytes(m,p,n){return Buffer.from(m.HEAPU8.slice(Number(p),Number(p)+n));}
const hybridNullGuard=bytes(modules[1],0,64);
function snapshot(m){const objects=Array.from({length:m._probe_count(0)},(_,i)=>{const raw=bytes(m,m._probe_pointer(3,i),L.objSize);for(const k of ['nobj','nexthere','cobj','ocarry'])raw.fill(0,L['obj_'+k],L['obj_'+k]+8);return{raw,alive:m._probe_alive(i),links:[0,1,2].map(k=>m._probe_link(i,k)),timer:m._probe_timer(i)};}),monsters=Array.from({length:m._probe_count(2)},(_,i)=>{const raw=bytes(m,m._probe_pointer(4,i),L.monSize);for(const k of ['data','mw'])raw.fill(0,L['mon_'+k],L['mon_'+k]+8);return{raw,identity:[m._probe_mon_identity(i,0),m._probe_mon_identity(i,1)]};});return{trace:text(m,m._probe_trace()),msg:text(m,m._probe_message()),messageBytes:bytes(m,m._probe_pointer(9,0),L.BUFSZ),rng:[m._probe_rng_state()>>>0,m._probe_rng_count()],scalar:Array.from({length:18},(_,i)=>m._probe_scalar(i)),digging:bytes(m,m._probe_pointer(0,0),L.diggingSize),map:bytes(m,m._probe_pointer(1,0),L.COLNO*L.ROWNO*L.rmSize),vision:bytes(m,m._probe_pointer(8,0),L.COLNO*L.ROWNO),grid:text(m,m._probe_grid_state()),objects,monsters,free:m._probe_count(1)};}
function state(label='state'){assert.deepEqual(bytes(modules[1],0,64),hybridNullGuard,'hybrid NULL output guard');assert.deepEqual(snapshot(modules[1]),snapshot(modules[0]),label);assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);modules.forEach((m,i)=>assertStackRestored(m,stacks[i]));comparisons++;}
function call(fn,...args){if(process.env.TELEPORT_DIG_DEBUG)console.error(fn,...args);const out=modules.map(m=>m['_probe_'+fn](...args));assert.deepEqual(out[1],out[0],fn+' '+args);state(fn+' '+args);comparisons++;return out[0];}
const reset=(seed=42)=>call('reset',seed),option=(k,v)=>call('option',k,v),hero=(k,v)=>call('hero',k,BigInt(v)),context=(k,v)=>call('digging',k,BigInt(v)),obj=(slot,k,v)=>call('object',slot,k,BigInt(v)),result=(name,v)=>{assert.ok(returnKeys.includes(name),name);return call('return',returnKeys.indexOf(name),BigInt(v));},act=(name,a=0,b=0,c=0)=>{assert.ok(names.includes(name),name);return call('action',names.indexOf(name),a,b,c);},tile=(x,y,k,v)=>call('tile',x,y,k,v),property=(id,k,v)=>call('property',id,k,BigInt(v));
function rolls(values){modules.forEach(m=>{new Int32Array(m.HEAPU8.buffer,Number(m._probe_rng_pointer()),values.length).set(values);m._probe_rng_length(values.length);});state();}
function tool(type=L.PICK_AXE){const n=call('new',type,10,10);call('equipment',0,n);return n;}
for(const k of ['PICK_AXE','DWARVISH_MATTOCK','AXE','BATTLE_AXE','DAGGER','ROOM','STONE','POOL','MOAT','LAVAPOOL','ICE','PM_HUMAN','PM_WATCHMAN','PM_EARTH_ELEMENTAL','PM_XORN','PM_PURPLE_WORM','PIT','HOLE','SHOPBASE','NUMMONS'])assert.ok(Number.isSafeInteger(L[k]),k);
// Actual compiler fields, all original functions, static enum projection and pointer callbacks.
reset();assert.equal(act('is_digging'),0n);for(const kind of [0,1,2,3]){call('occupation',kind,0xa5a5a5a5a5a50001n);assert.equal(act('is_digging'),kind===1?1n:0n);}hero(24,65);call('occupation',1,0n);for(const effort of [-100,0,49,50,100,249,250,251,1000]){context(0,effort);act('holetime');}
for(const typ of [L.ROOM,L.CORR,L.STONE,L.TREE,L.DOOR,L.SDOOR,L.HWALL,L.LAVAWALL,L.WATER,L.FOUNTAIN,L.ALTAR])for(const type of [L.PICK_AXE,L.DWARVISH_MATTOCK,L.AXE,L.BATTLE_AXE,L.DAGGER]){reset();const n=tool(type);tile(11,10,0,typ);tile(11,10,1,L.D_CLOSED);act('dig_typ',n,11,10);}
for(const pit of [0,1])for(const see of [0,1])for(const mattock of [0,1])for(const adjacent of [0,1]){reset();const n=tool(mattock?L.DWARVISH_MATTOCK:L.PICK_AXE);call('trap',11,10,L.PIT,see,0);hero(5,pit);hero(6,L.TT_PIT);option(17,adjacent);act('pick_can_reach',n,11,10);}
for(const terrain of [L.STONE,L.ROOM,L.TREE,L.THRONE,L.ALTAR])for(const maker of [-2,-1,0])for(const can of [0,1]){reset();call('new_monster',L.PM_HUMAN,12,10);tile(10,10,0,terrain);result('Can_dig_down',can);act('dig_check',maker,10,10);}
for(const trap of [L.PIT,L.SPIKED_PIT,L.HOLE,L.TRAPDOOR,L.BEAR_TRAP,L.LANDMINE,L.MAGIC_PORTAL,L.VIBRATING_SQUARE]){reset();call('trap',10,10,trap,1,0);act('dig_check',-2,10,10);}
for(let code=L.DIGCHECK_FAILED;code<=L.DIGCHECK_FAIL_OBJ_POOL_OR_TRAP;code++){reset();tool();act('digcheck_fail_message',code,-2);}
// Liquid-neighborhood counts and source RNG short-circuit ordering including forced fill.
for(const typ of [L.POOL,L.MOAT,L.LAVAPOOL])for(let count=0;count<=9;count++)for(const force of [0,1]){reset(count+3);for(let i=0;i<count;i++)tile(9+Math.floor(i/3),9+i%3,0,typ);act('fillholetyp',10,10,force);}
for(const rock of [0,1])for(const waslit of [0,1]){reset();tile(10,10,0,L.CORR);tile(10,10,4,waslit);act('rm_waslit');act('mkcavearea',rock);}
for(const terrain of [L.ROOM,L.STONE,L.FOUNTAIN,L.SINK,L.DRAWBRIDGE_DOWN,L.DBWALL]){reset();tile(10,10,0,terrain);option(7,1);act('furniture_handled',10,10,1);}
// Occupation progress, stolen tool exits, fumbles, down-dig traps and exact cleanup branches.
reset();act('dig');for(const effort of [0,40,50,90,100,101,249,251])for(const down of [0,1]){reset(effort+1);tool();result('may_dig',1);result('Can_dig_down',1);context(0,effort);context(6,down);if(down){context(1,10);context(2,10);}else tile(11,10,0,L.STONE);act('dig');}
for(const which of [0,1,2])for(const welded of [0,1]){reset();tool();result('may_dig',1);result('welded',welded);property(L.FUMBLING,0,1);tile(11,10,0,L.STONE);rolls([0,which,4]);act('dig');}
for(const terrain of [L.STONE,L.TREE,L.HWALL,L.SDOOR,L.DOOR])for(const quiet of [0,1]){reset();tool();result('may_dig',1);context(0,120);context(9,quiet);tile(11,10,0,terrain);tile(11,10,1,L.D_CLOSED);act('dig');}
for(const bless of [-1,0,1]){reset();const n=tool();hero(8,9);hero(9,3);context(3,9);context(4,3);context(0,120);result('may_dig',1);tile(11,10,0,L.STONE);obj(n,bless<0?3:2,bless?1:0);rolls([0,0,0,0]);act('dig');}
for(const type of [L.HOLE,L.TRAPDOOR,L.PIT,L.LANDMINE,L.BEAR_TRAP])for(const trapped of [0,1]){reset();tool();result('Can_dig_down',1);context(0,90);context(6,1);context(1,10);call('trap',10,10,type,1,0);hero(5,trapped);rolls([0,6]);act('dig');}
// Real native callback identity from set_occupation and guard traversal.
reset();const n=tool();result('may_dig',1);tile(11,10,0,L.STONE);act('use_pick_axe2',n);assert.equal(ref._probe_scalar(8),1n);call('occupation_call');
for(const typ of [L.PM_HUMAN,L.PM_WATCHMAN,L.PM_WATCH_CAPTAIN])for(const see of [0,1])for(const peaceful of [0,1]){reset();call('new_monster',typ,12,10);call('mon_field',0,0,see);call('mon_field',0,1,peaceful);act('watchman_canseeu',0);result('in_town',1);tile(11,10,0,L.TREE);act('watch_dig',-1,11,10);act('watch_dig',-1,11,10);}
// Trap creation and source fall/flight/no-hole/furniture policies.
for(const type of [L.PIT,L.HOLE])for(const maker of [-2,-1,0])for(const fly of [0,1]){reset();call('new_monster',L.PM_HUMAN,10,10);option(52,type);result('Can_dig_down',1);property(L.FLYING,0,fly);act('digactualhole',10,10,maker);}
for(const terrain of [L.ROOM,L.STONE,L.THRONE,L.ALTAR,L.GRAVE,L.POOL,L.LAVAPOOL,L.DRAWBRIDGE_UP,L.DRAWBRIDGE_DOWN])for(const pit of [0,1]){reset();tool();tile(10,10,0,terrain);result('Can_dig_down',1);act('dighole',pit,1,0);}
for(const role of [L.PM_HUMAN,L.PM_ARCHEOLOGIST,L.PM_SAMURAI])for(let roll=0;roll<5;roll++){reset();hero(26,role);rolls([roll]);act('dig_up_grave',1);}
for(const terrain of [L.ROOM,L.POOL,L.MOAT,L.LAVAPOOL]){reset();option(54,1);hero(21,1);tile(11,10,0,terrain);call('new',L.CHEST,11,10);call('place',0,L.OBJ_FLOOR,11,10);call('trap',11,10,L.PIT,1,0);act('liquid_flow',11,10,terrain);}
// Tool directions, typed scratch strings and C macro property order.
for(const direction of [[0,0,0],[1,0,0],[0,0,1],[0,0,-1]])for(const typ of [L.PICK_AXE,L.AXE]){reset();const n=tool(typ);hero(2,direction[0]);hero(3,direction[1]);hero(4,direction[2]);option(12,direction[0]);option(13,direction[1]);option(14,direction[2]);act('use_pick_axe',n);act('use_pick_axe2',n);}
for(const t of [L.STONE,L.CORR,L.SCORR,L.HWALL,L.SDOOR,L.DOOR,L.TREE]){reset();call('new_monster',L.PM_HUMAN,11,10);tile(11,10,0,t);tile(11,10,1,L.D_CLOSED);act('mdig_tunnel',0);}
for(const halluc of [0,1])for(const alignment of [-1,0,1])for(const unexpected of [0,1]){reset();property(L.HALLUC,0,halluc);hero(10,alignment);act('draft_message',unexpected);}
for(const dir of [-1,0,1])for(const terrain of [L.ROOM,L.STONE,L.HWALL,L.TREE,L.DOOR]){reset();hero(4,dir);tile(11,10,0,terrain);tile(11,10,1,L.D_CLOSED);act('zap_dig');}
// Full trap copy survives deltrap clearing native conjoined fields before recursion.
reset();call('trap',10,10,L.PIT,1,1<<L.DIR_E);call('trap',11,10,L.PIT,1,1<<L.DIR_W);tile(9,10,0,L.MOAT);act('pit_flow',10,10,L.MOAT);
for(const [dir,dx,dy]of [[0,-1,0],[1,-1,-1],[2,0,-1],[3,1,-1],[4,1,0],[5,1,1],[6,0,1],[7,-1,1]]){reset();call('trap',10,10,L.PIT,1,1<<dir);call('trap',10+dx,10+dy,L.PIT,1,1<<((dir+4)%8));act('pit_flow',10,10,L.MOAT);}
for(const terrain of [L.ROOM,L.STONE,L.SCORR,L.TREE,L.IRONBARS,L.FOUNTAIN,L.SINK,L.THRONE,L.ALTAR,L.DOOR,L.LAVAPOOL]){reset();tile(10,10,0,terrain);act('adj_pit_checks');}reset();act('adj_pit_checks',1);
reset();tile(10,10,0,L.FOUNTAIN);act('adj_pit_checks');tile(10,10,0,L.ROOM);act('adj_pit_checks');assert.equal(text(ref,ref._probe_message()),'');
// Buried object lists, stable nearest-ball output and true object frees/timer state.
for(const type of [L.HEAVY_IRON_BALL,L.ROCK,L.BOULDER,L.CHEST,L.LEASH,L.CORPSE,L.POT_HEALING])for(const ice of [0,1]){reset();const n=call('new',type,10,10);call('place',n,L.OBJ_FLOOR,10,10);if(ice)tile(10,10,0,L.ICE);act('bury_an_obj',n,0);if(ref._probe_alive(n))act('unearth_objs',10,10);}
for(const mode of ['buried_ball','buried_ball_to_punishment','buried_ball_to_freedom']){reset();call('new',L.HEAVY_IRON_BALL,11,10);call('place',0,L.OBJ_BURIED,11,10);hero(5,12);hero(6,L.TT_BURIEDBALL);act(mode);}
reset();call('new',L.CHEST,10,10);call('place',0,L.OBJ_FLOOR,10,10);call('new',L.ROCK,10,10);call('place',1,L.OBJ_FLOOR,10,10);act('bury_objs',10,10);act('unearth_objs',10,10);act('wiz_debug_cmd_bury');
for(const corpse of [false,true])for(const where of [L.OBJ_FLOOR,L.OBJ_INVENT,L.OBJ_MINVENT,L.OBJ_MIGRATING,L.OBJ_BURIED]){reset();call('new',corpse?L.CORPSE:L.CHEST,10,10);call('place',0,where,10,10);if(where===L.OBJ_MINVENT){call('new_monster',L.PM_HUMAN,11,10);obj(0,17,0);call('mon_field',0,7,0);}obj(0,11,-9223372036854775808n);call('timeout',9007199254740993n);act(corpse?'rot_corpse':'rot_organic',0);}
reset();call('new',L.ROCK,10,10);call('place',0,L.OBJ_FLOOR,10,10);act('bury_an_obj',0,1);
// Addressable output aliases actual global cells rather than copied JS locals.
reset();call('new',L.HEAVY_IRON_BALL,11,10);call('place',0,L.OBJ_BURIED,11,10);context(1,10);context(2,10);option(55,1);act('buried_ball');assert.equal(new DataView(ref.HEAPU8.buffer).getInt16(Number(ref._probe_pointer(0,0))+L.digging_pos+L.coord_x,true),11);
reset();call('new',L.ROCK,10,10);call('place',0,L.OBJ_FLOOR,10,10);context(6,-128);act('bury_an_obj',0,2);assert.equal(new DataView(ref.HEAPU8.buffer).getInt8(Number(ref._probe_pointer(0,0))+L.digging_down),1);
// Donations/damage costs and source move comparisons retain exact signed64 values.
reset();call('new_monster',L.PM_HUMAN,15,10);option(5,0);option(6,1);result('costly_spot',1);result('stolen_value',9007199254740993n);for(let i=0;i<2;i++){call('new',L.CHEST,10,10);call('place',i,L.OBJ_FLOOR,10,10);}act('bury_objs',10,10);assert.ok(text(ref,ref._probe_trace()).includes('18014398509481986'));
for(const delta of [2n,3n]){reset();const n=tool();hero(18,1);hero(25,9007199254740993n+delta);context(5,9007199254740993n);context(1,10);context(2,10);tile(11,10,0,L.STONE);act('use_pick_axe2',n);}
reset();call('new',L.CHEST,10,10);call('place',0,L.OBJ_BURIED,10,10);call('new',L.APPLE,10,10);call('place',1,L.OBJ_CONTAINED,0,0);act('rot_organic',0);
// DEBUG arguments remain lazy, and actual source filename dig.c stays exact.
for(const debug of [0,1]){reset();option(1,debug);hero(20,123);call('new',L.CHEST,10,10);call('place',0,L.OBJ_FLOOR,10,10);act('bury_objs',10,10);assert.ok(text(ref,ref._probe_trace()).includes('debug:dig.c:1;'));}
// Memory grows inside real world callbacks while native room/coord/object views remain live.
for(const stage of [3,7]){reset();const n=tool();option(120,stage);const before=modules.map(m=>m.HEAPU8.buffer);if(stage===3){call('place',n,L.OBJ_FLOOR,10,10);act('bury_an_obj',n,0);}else{result('may_dig',1);context(0,120);tile(11,10,0,L.STONE);act('dig');}modules.forEach((m,i)=>assertMemoryGrowth(m,before[i]));}
const extra=await hybridFactory({nethackPorted:runtime});extra._probe_reset(7);assert.equal(extra._probe_count(0),0);state('module isolation');comparisons++;
console.log('DIG '+comparisons+' comparisons passed ('+referenceLabel+' vs JavaScript; controlled terrain/tool/world callbacks, actual native catalogues/allocator/helpers).');
