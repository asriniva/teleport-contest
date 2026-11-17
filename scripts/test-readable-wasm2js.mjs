// Developer-only comparison; the compiled reference is never a gameplay dependency.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import {pathToFileURL} from 'node:url';
import {createHash} from 'node:crypto';
const [referenceDirectory,runnerPath]=process.argv.slice(2);
if(!referenceDirectory||!runnerPath)throw Error('Usage: node scripts/test-readable-wasm2js.mjs ORIGINAL_C_REFERENCE WASM2JS_RUNNER');
const {runFullOriginalC:runCompiledJs}=await import(pathToFileURL(path.resolve(runnerPath)));
const artifacts=Object.fromEntries(['engine.mjs','host.mjs','adapter.mjs','signatures.json'].map(name=>{const file=path.join(path.dirname(runnerPath),name);return [name,createHash('sha256').update(fs.readFileSync(file)).digest('hex')];}));
import {runStandaloneProgram} from './run-standalone-program.mjs';
import {encodeRecorderScreen} from '../js/wasm-replay-support.js';
for(const name of ['fetch','XMLHttpRequest','WebSocket','Worker'])Object.defineProperty(globalThis,name,{configurable:true,value:()=>{throw Error('Network/workers forbidden in reference comparison');}});
const directory=referenceDirectory;
const options='OPTIONS=name:Archer,role:Ranger,race:human,gender:male,align:neutral\nOPTIONS=!autopickup,!autoquiver,!legacy,!tutorial,!splash_screen,pettype:none\n';
for(const keys of ['Q- f c\x1b','Q- f ?c\x1b','Q- f 2c h..........','Q- Qc\x1b']){
 const input={seed:101,timezone:'America/New_York',datetime:'20000110090000',argv:['-u','Archer'],options,keys};
 const saved=globalThis.WebAssembly;globalThis.WebAssembly=new Proxy({},{get(){throw Error('Runtime WebAssembly forbidden in JS reference comparison');}});
 let expected,actual;try{expected=await runCompiledJs(directory,input);actual=runStandaloneProgram(directory+'/assets',input);}finally{globalThis.WebAssembly=saved;}
 for(const key of ['status','consumed','state','stdout','stderr','rngLog','displayRngLog'])assert.deepEqual(actual[key],expected[key],key);
 assert.equal(actual.status.kind,'input-exhausted');assert.deepEqual(actual.frames,expected.frames.map(({screen,cursor,animation})=>({screen:encodeRecorderScreen(screen),cursor:[...cursor,1],animation})));
 console.log(JSON.stringify({passed:true,keys,status:actual.status,frames:actual.frames.length,moves:actual.state.moves,reference:'complete C engine compiled to JavaScript via wasm2js',runtimeWasmForbidden:true}));
}

console.log(JSON.stringify({referenceArtifacts:artifacts,scope:'Four authored scenarios, not complete gameplay coverage. Public recording equivalence is checked separately.'}));
