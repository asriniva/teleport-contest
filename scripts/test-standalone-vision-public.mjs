// Read-only queries through the canonical VISION context after genuine MAIN.
import fs from 'node:fs';import assert from 'node:assert/strict';import crypto from 'node:crypto';
import {runFullOriginalC} from './full-original-c-run.mjs';import {runStandaloneProgram} from './run-standalone-program.mjs';import {worldGraph} from './restoration-world-graph.mjs';import {encodeRecorderScreen} from '../js/wasm-replay-support.js';
const directory='.cache/full-original-c-v1',out='.cache/standalone-vision-public',R=JSON.parse(fs.readFileSync('js/standalone/records.json')).records,sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex');fs.mkdirSync(out,{recursive:true});let checks=0;
const eq=(a,b,n)=>{assert.deepEqual(a,b,n);checks++;},inputs=['scripts/test-standalone-vision-public.mjs','js/standalone/vision.js','js/standalone/vision-abi.json','js/ported/vision.js','js/nethack/bindings/vision.js','js/standalone/program.js','js/standalone/environment.js'];
const before=Object.fromEntries(inputs.map(p=>[p,sha(p)]));let module,environment;
const input={seed:1,timezone:'UTC',options:'OPTIONS=!news\n',keys:'  nm.'};
const c=await runFullOriginalC(directory,{...input,observeRuntime:r=>module=r.module});const j=runStandaloneProgram(directory+'/assets',{...input,observeRuntime:r=>environment=r.environment});
for(const k of ['status','consumed','snapshots','state','stdout','stderr','rngLog','displayRngLog'])eq(j[k],c[k],k+' whole MAIN observation');eq(j.frames,c.frames.map(({screen,cursor,animation})=>({screen:encodeRecorderScreen(screen),cursor:[...cursor,1],animation})),'all frozen MAIN frames');
let cells=0;for(let x=0;x<80;x++)for(let y=0;y<21;y++){eq(environment.resolve('get_viz_clear')(x,y),module._get_viz_clear(x,y),'native clear cell '+x+','+y);cells++;}
const heap=module.HEAPU8,v=new DataView(heap.buffer),globals=new Map();
for(let i=0;i<module._full_global_count();i++){const p=Number(module._full_global_name(i));let end=p;while(heap[end])end++;globals.set(Buffer.from(heap.slice(p,end)).toString(),Number(module._full_global_address(i)));}
const cg=worldGraph({module}),jg=worldGraph({environment});eq(jg,cg,'complete live world before read-only queries');
function list(view,svl){const result=new Map();let p=Number(view.getBigUint64(svl+R.instance_globals_saved_l.fields.level.offset+R.dlevel_t.fields.monlist.offset,true));while(p){const id=view.getUint32(p+R.monst.fields.m_id.offset,true);assert.ok(!result.has(id),'acyclic actual monster list');result.set(id,p);p=Number(view.getBigUint64(p+R.monst.fields.nmon.offset,true));}return result;}
const cm=list(v,globals.get('svl')),jm=list(environment.memory.view,environment.requireGlobal('svl'));eq([...jm.keys()],[...cm.keys()],'same live monsters');
for(const[id,p]of cm)eq(environment.resolve('howmonseen')(jm.get(id)),module._howmonseen(BigInt(p)),'native visibility mask for monster '+id);
eq(worldGraph({environment}),jg,'JS queries preserve live world');eq(worldGraph({module}),cg,'C queries preserve live world');
fs.writeFileSync(out+'/evidence.json',JSON.stringify({checks,cells,frames:j.frames.length,sourceSha256:before,limits:'Read-only get_viz_clear on every configured map cell and howmonseen for each actual live monster following real MAIN; special vision modes remain untested.'},null,2));
for(const[p,h]of Object.entries(before))eq(sha(p),h,'source stable '+p);
console.log('PASS '+JSON.stringify({checks,cells,frames:j.frames.length}));
