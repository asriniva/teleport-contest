import assert from 'node:assert/strict';
import {createRecordViews} from '../js/c-runtime/record-views.js';
import {withCEnvironment,C,R,T} from '../js/c-runtime/context.js';
import {setupMonsterData,layouts} from './monster-data-view-harness.mjs';
let checks=0;const eq=(a,b,label)=>{assert.deepEqual(a,b,label);checks++;};
const a=setupMonsterData(),b=setupMonsterData();a.entry.prepareArgs=a.baseline;
function call(name,left,right=left){
 const x=a.env.services[name](...left),y=b.env.services[name](...right);
 eq(x?.address??x,y?.address??y,name+' return/pointer');
 eq(a.env.memory.HEAPU8,b.env.memory.HEAPU8,name+' entire addressable memory');
 eq([...a.env.memory.live],[...b.env.memory.live],name+' allocation state');
 eq([C,R,T],[undefined,undefined,undefined],name+' restored scope');
 return y;
}
const own=b.mon,pm=b.species[0];
eq(b.optimized('set_mon_data',[own,pm]),[own,pm]);
assert.equal(b.optimized('set_mon_data',[own,pm])[0],own);checks++;
assert.equal(b.optimized('set_mon_data',[own,pm])[1],pm);checks++;
// Own views bypass record lookup; pointers, foreign views and wrong types keep it.
const originalRecord=b.env.ctypes.record;let descriptions=0;
b.env.ctypes.record=(...args)=>{descriptions++;return originalRecord(...args);};
b.optimized('set_mon_data',[own,pm]);eq(descriptions,0,'no description/cache lookup for own views');
b.optimized('set_mon_data',[own.address,pm.address]);assert.ok(descriptions>=2);checks++;
b.env.ctypes.record=originalRecord;
const foreign=createRecordViews(b.env).record('struct monst',own.address);
assert.equal(b.optimized('mon_learns_traps',[foreign,0])[0],own);checks++;
assert.equal(b.optimized('mon_learns_traps',[{address:own.address},0])[0],own);checks++;
assert.equal(b.optimized('mon_learns_traps',[pm,0])[0],b.views.record('struct monst',pm.address));checks++;
const old=own.address;own.address=pm.address;
assert.equal(b.optimized('mon_learns_traps',[own,0])[0],b.views.record('struct monst',pm.address));checks++;own.address=old;
eq(b.optimized('mon_learns_traps',[0,0])[0],0,'null');
assert.throws(()=>b.optimized('mon_learns_traps',[-1,0]),RangeError);checks++;
for(const grow of [false,true]){
 if(grow)for(const x of[a,b]){const old=x.env.memory.buffer;assert.ok(x.env.memory.grow(old.byteLength+1));assert.notEqual(x.env.memory.buffer,old);checks+=2;}
 for(const index of [0,1,5,20,50,100,200,300]){
  // Initial old/new species and movement are identical across the pair.
  for(const movement of [0,1,12,32767,-1]){
   a.mon.movement=movement;b.mon.movement=movement;
   call('set_mon_data',[a.mon,a.species[index]],[b.mon,b.species[index]]);
  }
  for(const type of [0,1,2,3,255,257,-1]){
   call('attacktype',[a.species[index],type],[b.species[index],type]);
   for(const damage of [layouts.mondata.AD_ANY,0,1,255])call('attacktype_fordmg',[a.species[index],type,damage],[b.species[index],type,damage]);
  }
 }
 for(const trap of [layouts.mondata.NO_TRAP,layouts.mondata.PIT,a.entry.environment.HOLE,layouts.mondata.ALL_TRAPS,layouts.mondata.NO_TRAP])call('mon_learns_traps',[a.mon,trap],[b.mon,trap]);
 // Exercise the hero movement branch, using each store's real live hero view.
 const ah=a.creation.environment.gy.youmonst,bh=b.creation.environment.gy.youmonst;
 for(const [i,j]of [[0,20],[20,1]]){
  ah.data=a.species[i];bh.data=b.species[i];a.creation.environment.u.umovement=12;b.creation.environment.u.umovement=12;
  call('set_mon_data',[ah,a.species[j]],[bh,b.species[j]]);
 }
}
for(const x of[a,b]){
 const biology=x.entry.environment,shortRef=biology.shortRef,sentinel={rectState:{},trackState:{}};
 biology.shortRef=()=>{throw Error('injected biology failure');};
 withCEnvironment(sentinel,()=>{assert.throws(()=>x.env.services.set_mon_data(x.mon,x.species[0]),/injected biology failure/);assert.equal(C,sentinel);assert.equal(R,sentinel.rectState);assert.equal(T,sentinel.trackState);checks+=4;});
 biology.shortRef=(...args)=>{x.env.services.attacktype(x.species[0],1);assert.equal(C,biology);checks++;return shortRef(...args);};
 x.env.services.set_mon_data(x.mon,x.species[0]);biology.shortRef=shortRef;
}
eq(a.env.memory.HEAPU8,b.env.memory.HEAPU8,'nested calls and exceptions');
console.log(JSON.stringify({status:'PASS',checks,baseline:'original monster-data prepareArgs',heapGrowth:true,fullHeapComparisons:true}));
