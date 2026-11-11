// No invented passwd identity: use the actual default SDK failure in main.
import assert from 'node:assert/strict';import path from 'node:path';import fs from 'node:fs';
import{runFullOriginalC}from'./full-original-c-run.mjs';
import{runStandaloneProgram}from'./run-standalone-program.mjs';
import{encodeRecorderScreen}from'../js/wasm-replay-support.js';
const directory=path.resolve(process.env.STANDALONE_MAIL_ORACLE||'.cache/full-original-c-v1'),input={keys:'  n',options:'OPTIONS=!news\n',timezone:'UTC',environment:{MAIL:undefined}},cpaths=[],jpaths=[];let module,program;
const native=await runFullOriginalC(directory,{...input,observeRuntime:runtime=>{module=runtime.module;const stat=module.FS.stat.bind(module.FS);module.FS.stat=(p,...args)=>{cpaths.push(p);return stat(p,...args);};}});
const actual=runStandaloneProgram(path.join(directory,'assets'),{...input,observeRuntime:runtime=>{program=runtime.program;const filesystem=runtime.environment.filesystem,stat=filesystem.stat.bind(filesystem);filesystem.stat=(p,...args)=>{jpaths.push(p);return stat(p,...args);};}});

assert.equal(native.status.kind,'input-exhausted','Original main accepts actual SDK NULL passwd behavior');assert.equal(actual.status.kind,'input-exhausted','Pure JS main accepts identical no-MAIL profile: '+actual.status.message);
assert.equal(actual.consumed,native.consumed);assert.deepEqual(actual.state,native.state,'Full hero/RNG witness with MAIL unset');assert.deepEqual(actual.snapshots,native.snapshots,'Every real input boundary with MAIL unset');
assert.equal(actual.stdout,native.stdout,'Complete no-MAIL terminal');assert.equal(actual.stderr,native.stderr,'Complete no-MAIL stderr');assert.equal(actual.rngLog,native.rngLog);assert.equal(actual.displayRngLog,native.displayRngLog);
assert.deepEqual(actual.frames,native.frames.map(({screen,cursor,animation})=>({screen:encodeRecorderScreen(screen),cursor:[...cursor,1],animation})),'No-MAIL canonical recorder output');
const env=program.environment,mail=env.start('unix-platform-mail').environment,selected=env.memory.readString(mail.mailState.mailbox),expected=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')).mail.strings.MAILPATH;
assert.equal(selected,expected,'Unchanged MAIL selects the real bare MAILPATH after actual NULL passwd');
assert.ok(cpaths.includes(selected),'Original C performs stat on the exact selected fallback path');assert.ok(jpaths.includes(selected),'Original JS performs stat on the exact selected fallback path');
const contents=(filesystem,p)=>{try{return Buffer.from(filesystem.readFile(p));}catch(e){if(e.errno===44||e.code==='ENOENT')return null;throw e;}};
assert.deepEqual(contents(env.filesystem,selected),contents(module.FS,selected),'Actual selected mailbox contents/absence match');assert.equal(contents(env.filesystem,selected),null,'The default profile has no invented mailbox/user file');
console.log('PASS: 15 full-original-C no-MAIL/default-passwd main/path/content comparisons; source SDK returns NULL, without a virtual user.');
