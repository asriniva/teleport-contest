// Original C cave generation against the actual production adapter, including
// ice cells. The TU fixture's C bitfield helpers cannot exercise this boundary.
import fs from 'node:fs';import assert from 'node:assert/strict';import crypto from 'node:crypto';
import {runFullOriginalC} from './full-original-c-run.mjs';
import {runStandaloneProgram} from './run-standalone-program.mjs';
import {worldGraph} from './restoration-world-graph.mjs';
const dir='.cache/full-original-c-v1',out='.cache/mkmap-ice-regression';fs.mkdirSync(out,{recursive:true});
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),L=layouts.mkmap;
let module,env,checks=0;const equal=(a,b,s)=>{assert.deepEqual(a,b,s);checks++;};
const input={seed:1,timezone:'UTC',options:'OPTIONS=!news\n',keys:'  n'};
const c=await runFullOriginalC(dir,{...input,observeRuntime:r=>{module=r.module;}});
const j=runStandaloneProgram(dir+'/assets',{...input,observeRuntime:r=>{env=r.environment;}});
for(const k of ['status','consumed','snapshots','state','rngLog','displayRngLog','stdout','stderr'])equal(j[k],c[k],'real game startup '+k);
const roots={};for(let i=0;i<module._full_global_count();i++){const at=Number(module._full_global_name(i));let end=at;while(module.HEAPU8[end])end++;roots[Buffer.from(module.HEAPU8.slice(at,end)).toString()]=Number(module._full_global_address(i));}
const terrain=()=>Buffer.from(env.memory.HEAPU8.slice(env.requireGlobal('svl')+L.levlOffset,env.requireGlobal('svl')+L.levlOffset+L.COLNO*L.ROWNO*L.terrainSize));
const referenceTerrain=()=>Buffer.from(module.HEAPU8.slice(roots.svl+L.levlOffset,roots.svl+L.levlOffset+L.COLNO*L.ROWNO*L.terrainSize));
const rng=()=>env.state('rnd').rnglist.map(({rng_state:s})=>{const l=layouts.rnd,b=Buffer.alloc(l.size);b.writeBigUInt64LE(BigInt(s.n),l.n);for(const k of ['r','m'])for(let i=0;i<256;i++)b.writeBigUInt64LE(s[k][i],l[k]+8*i);for(const k of ['a','b','c'])b.writeBigUInt64LE(s[k],l[k]);return b.toString('hex');});
const referenceRng=()=>[0,1].map(i=>{const p=Number(module._full_rng_state(i));return Buffer.from(module.HEAPU8.slice(p,p+Number(module._full_rng_size()))).toString('hex');});
const optionalLog=(path,read)=>{try{return Buffer.from(read(path));}catch(error){if(path==='/rng-display.log'&&(error.code==='ENOENT'||error.errno===44))return null;throw error;}};
const steps=[];let iceCases=0;
for(const [bg,fg]of [[L.STONE,L.ICE],[L.ICE,L.ROOM],[L.STONE,L.LAVAPOOL],[L.LAVAPOOL,L.ROOM]])for(const smoothed of [0,1])for(const joined of [0,1])for(const icedpools of [0,1]){
 const config={bg,fg,smoothed,joined,lit:-1,walled:0,icedpools},bytes=new Uint8Array(L.initSize),view=new DataView(bytes.buffer);
 for(const [key,value]of Object.entries(config))view['setInt'+L['init_'+key+'_size']*8](L['init_'+key],value,true);
 const cp=module._malloc(BigInt(L.initSize)),jp=env.memory.calloc(1,L.initSize);module.HEAPU8.set(bytes,Number(cp));env.memory.HEAPU8.set(bytes,jp);
 module._mkmap(BigInt(cp));env.resolve('mkmap')(jp);module._free(BigInt(cp));env.memory.free(jp);
 equal(terrain(),referenceTerrain(),'every terrain byte '+JSON.stringify(config));
 equal(worldGraph({environment:env}),worldGraph({module}),'complete world '+JSON.stringify(config));
 equal(rng(),referenceRng(),'both complete ISAAC states');
 for(const path of ['/rng.log','/rng-display.log'])equal(optionalLog(path,p=>env.filesystem.readFile(p)),optionalLog(path,p=>module.FS.readFile(p)),'ordered '+path);
 let count=0;for(let x=1;x<L.COLNO;x++)for(let y=0;y<L.ROWNO;y++){
  const p=env.requireGlobal('svl')+L.levlOffset+(x*L.ROWNO+y)*L.terrainSize;
  if(env.memory.view.getInt8(p+L.terrainType)===L.ICE){equal(env.ctypes.getField('rm',p,'icedpool','unsigned int'),icedpools?L.ICED_POOL:L.ICED_MOAT,'real ICE setter preserves header bits');count++;}
 }
 if(bg===L.ICE||fg===L.ICE){assert.ok(count>0,'regression really exercises ice');iceCases++;}
 steps.push({...config,iceCells:count});
}
const sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex');
const result={passed:true,checks,cases:steps.length,iceCases,steps,referenceReceiptSha256:sha(dir+'/receipt.json'),limits:'Component generation on source-initialized real C/JS worlds; all map bytes, world graph and complete ordered main/display RNG logs compared. Does not identify the unavailable leaderboard recording.'};
fs.writeFileSync(out+'/evidence.json',JSON.stringify(result,null,2)+'\n');console.log(JSON.stringify(result));
