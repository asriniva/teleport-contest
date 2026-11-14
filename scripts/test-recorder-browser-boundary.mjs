// Exercise production replay without process or access to Node host modules.
import fs from 'node:fs';
import assert from 'node:assert/strict';
import {registerHooks} from 'node:module';
const session=JSON.parse(fs.readFileSync('sessions/seed0013-friday13-save-then-fullmoon-restore.session.json'));
const segments=session.segments??[session];
const originalProcess=globalThis.process;
const hook=registerHooks({resolve(specifier,context,next){assert.ok(!specifier.startsWith('node:'),'browser path imported '+specifier);return next(specifier,context);}});
const files=new Map(),storage={getItem:k=>files.get(k)??null,setItem:(k,v)=>files.set(k,String(v)),removeItem:k=>files.delete(k),get length(){return files.size},key:i=>[...files.keys()][i]??null};
let checks=0;
try{
 delete globalThis.process;
 const {runSegment}=await import('../js/standalone-recorder-adapter.js');
 for(const segment of segments){
  const result=await runSegment({...segment,storage});
  assert.deepEqual(result.getScreens(),segment.steps.map(step=>step.screen));checks++;
  assert.deepEqual(result.getCursors(),segment.steps.map(step=>step.cursor));checks++;
  assert.deepEqual(result.getRngLog(),segment.steps.flatMap(step=>step.rng??[]));checks++;
 }
 assert.ok(files.has('vfs:/teleport-standalone-state.json'));checks++;
}finally{globalThis.process=originalProcess;hook.deregister();}
console.log(JSON.stringify({passed:true,segments:segments.length,checks,nodeImportsAllowed:false,processAvailable:false}));
