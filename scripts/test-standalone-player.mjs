// Real process stdin/stdout and durable-file boundary, compared with sealed C.
import fs from 'node:fs';
import path from 'node:path';
import assert from 'node:assert/strict';
import crypto from 'node:crypto';
import {spawnSync} from 'node:child_process';
const out=path.resolve('.cache/standalone-player-checks'),reference=path.resolve('.cache/full-original-c-v1'),save='/nethack/save/0Ada.Z',sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex');
fs.mkdirSync(out,{recursive:true});const files=['scripts/test-standalone-player.mjs','scripts/play-standalone.mjs','js/standalone/program.js','js/standalone/environment.js','js/c-runtime/stdio.js','js/c-runtime/vfs.js'],before=Object.fromEntries(files.map(p=>[p,sha(p)]));
const[{runFullOriginalC},{worldGraph}]=await Promise.all([import('./full-original-c-run.mjs'),import('./restoration-world-graph.mjs')]);
let checks=0;const eq=(a,b,n)=>{assert.deepEqual(a,b,n);checks++;},profile={seed:1,timezone:'UTC',datetime:'20260102030405',clockEpoch:1767323045,options:'OPTIONS=!news\n'},args=['-u','Ada-male-lawful','-p','Archeologist','-r','human'];
const rc=path.join(out,'nethackrc');fs.writeFileSync(rc,profile.options);
function launch(name,keys,initial){
 const state=path.join(out,name+'.json');if(initial)fs.writeFileSync(state,JSON.stringify({version:1,state:{files:{[save]:initial},deleted:[]}}));else if(fs.existsSync(state))fs.unlinkSync(state);
 const result=spawnSync(process.execPath,['scripts/play-standalone.mjs','--assets',reference+'/assets','--state',state,'--seed','1','--rc',rc,'--fixed-time','2026-01-02T03:04:05Z','--',...args],{input:Buffer.from(keys),env:{...process.env,USER:'root',LOGNAME:'root',TZ:'UTC'},encoding:null,maxBuffer:64*1024*1024});
 fs.writeFileSync(path.join(out,name+'.stdout'),result.stdout??'');fs.writeFileSync(path.join(out,name+'.stderr'),result.stderr??'');eq(result.status,0,name+' genuine process exit '+String(result.stderr));eq(result.signal,null,name+' no process signal');const persisted=JSON.parse(fs.readFileSync(state));eq(persisted.version,1,name+' durable state version');assert.ok(persisted.state.files[save],name+' actual nonempty source save');checks++;return{stdout:result.stdout.toString('base64'),stderr:result.stderr.toString('base64'),save:persisted.state.files[save],state};
}
const c=await runFullOriginalC(reference,{...profile,argv:args,keys:'  nSy'});eq(c.status,{kind:'exited',code:0},'native source initial save exits');const j=launch('initial','  nSy');eq(j.stdout,c.stdout,'fresh terminal launcher exact C stdout');eq(j.stderr,c.stderr,'fresh terminal launcher exact C stderr');
const streams={c:c.files[save].bytes,js:j.save},cases=[];
for(const[source,bytes]of Object.entries(streams)){
 const native=await runFullOriginalC(reference,{...profile,argv:args,keys:'Sy',files:{[save]:{bytes}}});eq(native.status,{kind:'exited',code:0},source+' native restore/resave normal exit');
 const terminal=launch(source+'-restore','Sy',bytes);eq(terminal.stdout,native.stdout,source+' fresh CLI restore/resave exact C stdout');eq(terminal.stderr,native.stderr,source+' fresh CLI restore/resave exact C stderr');
 let expectedRuntime,actualRuntime;
 const expected=await runFullOriginalC(reference,{...profile,argv:args,keys:'',files:{[save]:native.files[save]},observeRuntime:r=>expectedRuntime=r});
 const roundtrip=await runFullOriginalC(reference,{...profile,argv:args,keys:'',files:{[save]:{bytes:terminal.save}},observeRuntime:r=>actualRuntime=r});eq(roundtrip.status,{kind:'input-exhausted'},source+' CLI resave loads in fresh C');eq(roundtrip.state.moves,'1',source+' source turn survives durable file round trip');for(const k of ['status','consumed','snapshots','state','rngLog','displayRngLog','stdout','stderr','frames'])eq(roundtrip[k],expected[k],source+' complete fresh C observation of durable resaves '+k);eq(worldGraph(actualRuntime),worldGraph(expectedRuntime),source+' complete live restored world identity graph');cases.push({source,input:source==='c'?'original-C stream':'CLI-produced stream',nativeRestoreAndResave:true,cliRestoreAndResave:true,cliResaveLoadsInC:true});
}
for(const[p,h]of Object.entries(before))eq(sha(p),h,'stable player input '+p);
const evidence={complete:true,fullGameAccepted:false,checks,sourceSha256:before,cases,productionWasmForbidden:true,limits:'Real Node process byte input/output and atomic durable file state, initial source save plus fresh C/CLI cross-consumers and C load of both CLI resaves. No synthetic source state, frame cleanup or raw-save masking. Interactive OS terminal-mode behavior is outside this pipe-based check; the engine recording suites remain separate.'};fs.writeFileSync(path.join(out,'evidence.json'),JSON.stringify(evidence,null,2));console.log('PASS '+JSON.stringify(evidence));
