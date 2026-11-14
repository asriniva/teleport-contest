// Reproduce the judge's real ship_object -> otransit_msg -> Strcpy path.
// Setup uses actual game functions on genuine independently initialized worlds.
import fs from 'node:fs';import assert from 'node:assert/strict';
import {runFullOriginalC} from './full-original-c-run.mjs';import {runStandaloneProgram} from './run-standalone-program.mjs';
import {enableDokick} from '../js/nethack/dokick.js';import {encodeRecorderScreen} from '../js/wasm-replay-support.js';import {worldGraph} from './restoration-world-graph.mjs';
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),records=JSON.parse(fs.readFileSync('js/nethack/records.json')).records,input={seed:1,timezone:'UTC',options:'OPTIONS=!news\n',keys:'  n'};let cr,jr,checks=0,transitCopies=0;
const cresult=await runFullOriginalC('.cache/full-original-c-v1',{...input,observeRuntime:r=>cr=r}),jresult=runStandaloneProgram('.cache/full-original-c-v1/assets',{...input,observeRuntime:r=>jr=r});
const eq=(a,b,label)=>{assert.deepEqual(a,b,label);checks++;};eq(jresult.status,cresult.status,'genuine MAIN startup');eq(jresult.state,cresult.state,'startup state and PRNG');
const c=cr.module,e=jr.environment,group=enableDokick(e,layouts),globals={},readCString=p=>{p=Number(p);let end=p;while(c.HEAPU8[end])end++;return Buffer.from(c.HEAPU8.subarray(p,end)).toString('latin1');};
for(let i=0;i<c._full_global_count();i++)globals[readCString(c._full_global_name(i))]=Number(c._full_global_address(i));
const coutput=[...Buffer.from(cresult.stdout,'base64')],tty=c.FS.getStream(1).tty,put=tty.ops.put_char;tty.ops={...tty.ops,put_char:(t,ch)=>{if(ch!==null)coutput.push(ch);return put(t,ch);}};
const cview=()=>new DataView(c.HEAPU8.buffer),pointer=at=>Number(cview().getBigUint64(at,true));
let stairs=pointer(globals.gs+records.instance_globals_s.fields.stairs.offset),target;
while(stairs){const f=records.stairway.fields;if(!cview().getInt8(stairs+f.up.offset)&&!cview().getInt8(stairs+f.isladder.offset)){target=[cview().getInt16(stairs+f.sx.offset,true),cview().getInt16(stairs+f.sy.offset,true)];break;}stairs=pointer(stairs+f.next.offset);}
assert.ok(target,'source generated a down staircase');const [x,y]=target;
const originalCopy=group.services.Strcpy;group.services.Strcpy=(...args)=>{transitCopies++;return originalCopy(...args);};
const readLog=(filesystem,path)=>{try{return {exists:true,text:Buffer.from(filesystem.readFile(path)).toString()};}catch(error){if(error.code==='ENOENT'||error.errno===44)return {exists:false};throw error;}};
function compare(label){eq(worldGraph(jr),worldGraph(cr),label+' complete world');for(const path of ['/rng.log','/rng-display.log'])eq(readLog(e.filesystem,path),readLog(c.FS,path),label+' ordered '+path);eq(Buffer.from(jr.program.stdio.captured(1)),Buffer.from(coutput),label+' exact terminal bytes');eq(jr.program.terminal.frames,cresult.frames.map(({screen,cursor,animation})=>({screen:encodeRecorderScreen(screen),cursor:[...cursor,1],animation})),label+' every frame/cursor/animation');}
c._teleds(x,y,0);e.services.teleds(x,y,0);c._vision_recalc(0);e.services.vision_recalc(0);compare('source teleport to staircase');
const visible=pointer(pointer(globals.gv+records.instance_globals_v.fields.viz_array.offset)+y*8);assert.ok(c.HEAPU8[visible+x]&layouts.vision.IN_SIGHT,'transit path is visible');
let shipped=0;
for(const type of [layouts.dokick.ROCK,layouts.dokick.CORPSE]){
 for(let i=0;i<8;i++){
  const co=c._mksobj(type,1,0),jo=e.services.mksobj(type,1,0);compare('source object creation '+type+'/'+i);
  const before=transitCopies,expected=c._ship_object(co,x,y,0),actual=e.services.ship_object(jo,x,y,0);eq(actual,expected,'actual source ship return');eq(transitCopies,before+1,'actual ship invokes otransit_msg Strcpy exactly once');compare('actual visible shipping '+type+'/'+i);
  if(actual){shipped++;break;}c._obfree(co,0n);e.services.obfree(jo,0);compare('source cleanup of retained object');
 }
}
assert.equal(shipped,2,'both ordinary object and corpse migrate through visible transit');
const evidence={passed:true,checks,transitCopies,shipped,stairs:target,scope:'Real original-C and JS MAIN worlds; source teleport, visibility, object creation, ship_object and cleanup. Both ordinary-object and corpse transit branches execute the actual Strcpy adapter. Complete ordered core/display RNG, world graph, raw terminal and frames match. This is a targeted reproduction, not every shipping/shop/trap branch.'};
fs.mkdirSync('.cache/service-coercions',{recursive:true});fs.writeFileSync('.cache/service-coercions/transit.json',JSON.stringify(evidence,null,2)+'\n');console.log(JSON.stringify(evidence));
