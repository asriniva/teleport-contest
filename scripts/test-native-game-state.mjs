import assert from 'node:assert/strict';
import fs from 'node:fs';
import {spawnSync} from 'node:child_process';
import {NativeGameState} from '../js/nethack/native/game-state.js';
import * as original from '../js/ported/monmove.js';
import {withCEnvironment} from '../js/c-runtime/context.js';
const generated=new URL('../js/nethack/native/monster-movement.js',import.meta.url);
const before=fs.readFileSync(generated,'utf8');
assert.equal(spawnSync('python3',['scripts/generate-native-monmove.py']).status,0);
assert.equal(fs.readFileSync(generated,'utf8'),before,'generator is reproducible');
let checks=0;
for(let i=0;i<200;i++) {
 const state=new NativeGameState(),events=[];
 const deps={MTSZ:4,MMOVE_NOTHING:0,MMOVE_DONE:1,MMOVE_DIED:2,Trap_Killed_Mon:3,Trap_Caught_Mon:4,NO_TRAP_FLAGS:0,
  IN_SIGHT:1,COULD_SEE:2,svm:{moves:BigInt(i)},regenerates:()=>i%3===0,
  healmon:(m,n)=>{m.mhp+=n;events.push('heal');},finish_meating:()=>events.push('finish'),
  mintrap:()=>i%2?3:4,newsym:(x,y)=>events.push([x,y]),IS_DOOR:t=>t===1,D_CLOSED:4,D_LOCKED:8,
  SURFACE_AT:(x,y)=>state.cells[x][y].typ,ACCESSIBLE:t=>t>0};
 const native=state.bindMovement(deps);
 const m=state.createMonster({mx:3,my:4,mhp:7,meating:i%4,mspec_used:i%5});
 const reference=structuredClone(m);
 const c={...deps,int:n=>Number(n)|0,coordxy:n=>Number(n)<<16>>16,char:n=>Number(n)<<24>>24,boolean:n=>Number(n)<<24>>24,bool:n=>n?1:0,
  intLocal:(value=0)=>({value}),coordxyLocal:(value=0)=>({value}),mfndposLocal:()=>({}),copyStruct:Object.assign,
  levl:state.cells};
 native.mon_regen(m,1);const trace=structuredClone(events);events.length=0;
 withCEnvironment(c,original.mon_regen,reference,1);
 assert.deepEqual(m,reference);assert.deepEqual(events,trace);checks+=2;
 native.mon_track_add(m,65535+i,-32769+i);withCEnvironment(c,original.mon_track_add,reference,65535+i,-32769+i);
 assert.deepEqual(m.mtrack,reference.mtrack);checks++;
 native.mon_track_clear(m);assert.ok(m.mtrack.every(p=>p.x===0&&p.y===0));checks++;
 m.mtrapped=1;reference.mtrapped=1;events.length=0;
 const result=native.m_move(m,0),moveTrace=structuredClone(events);events.length=0;
 assert.equal(result,withCEnvironment(c,original.m_move,reference,0));assert.deepEqual(events,moveTrace);checks+=2;
 state.cells[3][4].typ=1;state.cells[3][4].doormask=i%16;
 assert.equal(native.closed_door(3,4),withCEnvironment(c,original.closed_door,3,4));
 assert.equal(native.accessible(3,4),withCEnvironment(c,original.accessible,3,4));checks+=2;
 state.placeMonster(m,3,4);assert.equal(state.occupancy[3][4],m);
 state.moveMonster(m,4,5);assert.equal(state.occupancy[3][4],0);assert.equal(state.occupancy[4][5],m);checks+=3;
 assert.throws(()=>new NativeGameState().placeMonster(m,1,1),/Foreign/);checks++;
}
assert.ok(!before.includes('withCEnvironment'));assert.ok(!before.includes('C.callLocal('));
console.log(`PASS ${checks} native state and movement checks; full-turn recording parity not yet established`);
