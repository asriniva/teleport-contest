import './pure-js-probes/deny-wasm.mjs';
import assert from 'node:assert/strict';
import fs from 'node:fs';
import {createProbe,createReference} from './pure-js-fixtures/load.mjs';
import {Int32Array as FixtureInt32Array,DataView as FixtureDataView} from './native-test-backend.mjs';
import {C,R,T,withCEnvironment} from '../js/c-runtime/context.js';
import {createMplayerEnvironment} from '../js/nethack/bindings/mplayer.js';
import {mk_mplayer} from '../js/ported/mplayer.js';
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json'));
const bytes=(m,p,n)=>{let at=Number(p),end=n===undefined?at:at+n;if(n===undefined)while(m.HEAPU8[end])end++;return Buffer.from(m.HEAPU8.slice(at,end));};
const text=(m,p)=>bytes(m,p).toString('latin1');
const scope=()=>{assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);};
function rolls(m,values){new FixtureInt32Array(m.HEAPU8.buffer,Number(m._probe_rng_pointer()),values.length).set(values);m._probe_rng_length(values.length);}
let comparisons=0,contracts=0;

const were=[await createReference('were'),await createProbe('were')],W=layouts.were;
function wereState(m){return{mon:[m._probe_mon_pm(),m._probe_mon_hp(),m._probe_mon_sleep(),m._probe_mon_move(),m._probe_mon_frozen(),m._probe_mon_flee()],current:m._probe_current(),lycan:m._probe_lycan(),timeout:m._probe_timeout(),changes:m._probe_changes(),rng:m._probe_rng_count(),visible:m._probe_visible(),genbuf:text(m,m._probe_genbuf()),summoned:Array.from({length:m._probe_summoned_count()},(_,i)=>[m._probe_summoned_pm(i),m._probe_summoned_tame(i)]),trace:text(m,m._probe_trace())};}
for(const human of [W.PM_HUMAN_WEREWOLF,W.PM_HUMAN_WEREJACKAL,W.PM_HUMAN_WERERAT])for(const protection of [1,2]){
 for(const m of were){m._probe_reset();m._probe_mon(human,50,100,0,1,0,0,0);m._probe_properties(protection);}
 const before=were.map(wereState),stacks=were.map(m=>m._probe_stack());were.forEach(m=>m._probe_new());
 const after=were.map(wereState);assert.deepEqual(after[1],after[0]);assert.deepEqual(after,before,'protected human-form were cannot change');
 assert.deepEqual(were.map(m=>m._probe_stack()),stacks);scope();comparisons++;
}
const forms=[W.PM_WEREWOLF,W.PM_HUMAN_WEREWOLF,W.PM_WEREJACKAL,W.PM_HUMAN_WEREJACKAL,W.PM_WERERAT,W.PM_HUMAN_WERERAT];
for(const form of forms)for(const yours of [0,1])for(const buffer of [0,1])for(const visible of [0,1])for(const failure of [0,2])for(const roll of [0,4]){
 for(const m of were){m._probe_reset();m._probe_option(8,failure);m._probe_option(9,visible);rolls(m,Array(16).fill(roll));}
 const stacks=were.map(m=>m._probe_stack()),results=were.map(m=>m._probe_summon(form,yours,buffer)),states=were.map(wereState);
 assert.equal(results[1],results[0]);assert.deepEqual(states[1],states[0]);
 const attempted=roll===0?1:5;assert.equal(results[0],attempted-(failure?Math.floor(attempted/failure):0),'independent creation/failure schedule');
 assert.equal(states[0].visible,visible?results[0]:0);assert.equal(states[0].summoned.length,results[0]);
 assert.ok(states[0].summoned.every(([,tame])=>tame===yours));assert.deepEqual(were.map(m=>m._probe_stack()),stacks);scope();comparisons++;
}

const players=[await createReference('mplayer'),await createProbe('mplayer')],M=layouts.mplayer;
function playerState(m){return{monsters:Array.from({length:m._probe_monster_count()},(_,i)=>[m._probe_mon_pm(i),m._probe_mon_female(i),m._probe_mon_peaceful(i),m._probe_mon_level(i),m._probe_mon_hp(i),m._probe_mon_hpmax(i),m._probe_mon_malign(i),text(m,m._probe_mon_name(i))]),objects:Array.from({length:m._probe_object_count()},(_,i)=>({fields:Array.from({length:11},(_,j)=>m._probe_object_field(i,j)),quantity:m._probe_object_quantity(i)})),rng:m._probe_rng_count(),randomState:m._probe_rng_state(),result:m._probe_result(),name:text(m,m._probe_name_result()),good:m._probe_good_calls(),copy:m._probe_fake_copy(),trace:text(m,m._probe_trace())};}
const roles=['PM_ARCHEOLOGIST','PM_BARBARIAN','PM_CAVE_DWELLER','PM_HEALER','PM_KNIGHT','PM_MONK','PM_CLERIC','PM_RANGER','PM_ROGUE','PM_SAMURAI','PM_TOURIST','PM_VALKYRIE','PM_WIZARD'];
for(const role of roles){
 for(const m of players){m._probe_reset(1);m._probe_option(1,1);rolls(m,Array(512).fill(0));}
 const stacks=players.map(m=>m._probe_stack());players.forEach(m=>m._probe_make(M[role],10,11,1));
 const states=players.map(playerState);assert.deepEqual(states[1],states[0]);
 assert.ok(states[0].objects.some(o=>o.fields[0]===M.LOADSTONE),'forced loadstone draw for '+role);
 assert.deepEqual(players.map(m=>m._probe_stack()),stacks);scope();comparisons++;
}
// A deliberately inconsistent predicate exercises the defensive default. This
// is a JS provider-failure contract, not a valid native is_mplayer result.
const faulty=await createProbe('mplayer',{nethackPorted:{mplayer(services,name,...args){
 assert.equal(name,'mk_mplayer');const env=createMplayerEnvironment(services,M);env.is_mplayer=()=>true;
 const result=withCEnvironment(env,mk_mplayer,env.permonst(args[0]),args[1],args[2],args[3]<<24>>24);
 return result?.address??result;
}}});
faulty._probe_reset(1);rolls(faulty,Array(512).fill(0));faulty._probe_make(M.PM_ARCHEOLOGIST-1,10,11,0);
assert.ok(text(faulty,faulty._probe_trace()).includes('bad mplayer monster'));assert.ok(faulty._probe_result()>=0);scope();contracts++;

const writing=[await createReference('write'),await createProbe('write')],L=layouts.write;
function writeState(m){return{storage:Array.from({length:4},(_,i)=>bytes(m,m._probe_snapshot_pointer(i),Number(m._probe_snapshot_size(i)))),scalars:Array.from({length:3},(_,i)=>m._probe_scalar(i)),literate:m._probe_literate(),random:m._probe_rng_state(),count:m._probe_rng_count(),knowledge:Array.from({length:L.NUM_OBJECTS},(_,i)=>[m._probe_known(i),m._probe_encountered(i)]),trace:text(m,m._probe_trace())};}
writing.forEach(m=>m._probe_reset(1));
const books=[];
for(let typ=L.MAXOCLASSES;typ<L.NUM_OBJECTS;typ++)if(writing[0]._probe_class(typ)===L.SPBOOK_CLASS&&![L.SPE_BLANK_PAPER,L.SPE_NOVEL,L.SPE_BOOK_OF_THE_DEAD].includes(typ)&&writing[0]._probe_name(typ))books.push(typ);
assert.ok(books.length>20);
for(const typ of books){
 const cost=writing[0]._probe_cost(typ,L.SPBOOK_CLASS),half=Math.trunc(cost/2);assert.ok(half>1&&half<127);
 for(const m of writing){
  m._probe_reset(1);m._probe_paper(L.SPE_BLANK_PAPER,1,1,0,0);m._probe_object(typ,1,1,0n);m._probe_input(BigInt(m._probe_name(typ)));m._probe_pen(half,1,0,0);rolls(m,Array(64).fill(half-1));
 }
 const stacks=writing.map(m=>m._probe_stack()),results=writing.map(m=>m._probe_write()),states=writing.map(writeState);
 assert.equal(results[1],results[0]);assert.equal(results[0],L.ECMD_TIME);assert.deepEqual(states[1],states[0]);
 assert.ok(states[0].trace.includes('spellbook is left unfinished and your writing fades.'));
 assert.deepEqual(states[0].scalars,[0,1,0],'unfinished spellbook remains; only new object freed');
 assert.equal(new FixtureDataView(writing[0].HEAPU8.buffer).getInt8(Number(writing[0]._probe_snapshot_pointer(0))+L.obj_spe),0);
 assert.deepEqual(writing.map(m=>m._probe_stack()),stacks);scope();comparisons++;
}
assert.equal(comparisons,211+books.length);assert.equal(contracts,1);
console.log('PASS: '+comparisons+' original-C/pure-JS WERE/MPLAYER/WRITE gap cases ('+books.length+' unfinished spellbooks), plus1 explicit provider-failure contract; complete fixture snapshots/traces, return values, stack/context restoration.');
