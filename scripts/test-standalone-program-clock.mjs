// Original C MAIN clock fallback, without the fixed calendar-date override.
import fs from 'node:fs';import assert from 'node:assert/strict';import crypto from 'node:crypto';
import {elementalSourceSnapshot} from './elemental-source-provenance.mjs';
const directory='.cache/full-original-c-v1',out='.cache/standalone-program-clock';fs.mkdirSync(out,{recursive:true});const before=elementalSourceSnapshot(directory,['scripts/test-standalone-program-clock.mjs']);
const[{runFullOriginalC},{runStandaloneProgram},{encodeRecorderScreen}]=await Promise.all([import('./full-original-c-run.mjs'),import('./run-standalone-program.mjs'),import('../js/wasm-replay-support.js')]);
let checks=0;const eq=(a,b,n)=>{assert.deepEqual(a,b,n);checks++;},cases=[];
for(const[timezone,epoch]of [['UTC',1777723200],['UTC',1777723200.875],['America/New_York',1730611800]]){
 const input={seed:1,timezone,clockEpoch:epoch,options:'OPTIONS=!news\n',keys:'',environment:{NETHACK_FIXED_DATETIME:''}},native=[],actual=[];
 const c=await runFullOriginalC(directory,{...input,observeRuntime:({module:m})=>{const read=m.teleportReadKey;m.teleportReadKey=()=>{native.push({time:String(m._getnow()),year:m._getyear()});return read();};}});
 eq(native.length,1,'native real first input boundary');eq(native[0].time,String(Math.floor(epoch)),'native seconds fallback');
 if(process.env.PROGRAM_CLOCK_NATIVE_ONLY==='1'){cases.push({timezone,epoch,nativeOnly:true,clock:native[0]});continue;}
 const j=runStandaloneProgram(directory+'/assets',{...input,observeRuntime:({environment:e})=>{const group=e.start('terminal-key-input'),read=group.namespace.teleport_getch;group.namespace.teleport_getch=()=>{actual.push({time:String(e.resolve('getnow')()),year:e.resolve('getyear')()});return read();};}});
 eq(actual,native,'complete source clock observations');for(const k of ['status','consumed','snapshots','state','stdout','stderr','rngLog','displayRngLog'])eq(j[k],c[k],timezone+' entire MAIN observation '+k);eq(j.frames,c.frames.map(({screen,cursor,animation})=>({screen:encodeRecorderScreen(screen),cursor:[...cursor,1],animation})),'all real source frames');
 cases.push({timezone,epoch,clock:actual[0],frames:j.frames.length});
}
if(process.env.PROGRAM_CLOCK_NATIVE_ONLY==='1'){console.log('Native clock diagnostic '+JSON.stringify(cases));process.exit(0);}
eq(elementalSourceSnapshot(directory,['scripts/test-standalone-program-clock.mjs']),before,'all production/test/assets unchanged before imports and after execution');const evidence={complete:true,fullGameAccepted:false,checks,cases,productionProvenance:before,limitation:'Clock and complete genuine first-input MAIN observations for specified epochs/timezones, including fractional milliseconds and source fallback without NETHACK_FIXED_DATETIME. No game fields, RNG or date policy changed.'};fs.writeFileSync(out+'/evidence.json',JSON.stringify(evidence,null,2));console.log('PASS '+JSON.stringify({checks,cases}));
