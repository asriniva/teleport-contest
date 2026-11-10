// Guard the actual configured original source, ABI, and retained JS policy.
import { readFileSync } from 'node:fs';
import { resolve } from 'node:path';
import { createHash } from 'node:crypto';
import { spawnSync } from 'node:child_process';
const sha=b=>createHash('sha256').update(b).digest('hex');
export function checkArtifactSource(root=process.cwd(),{preprocess=true}={}) {
 const read=p=>readFileSync(resolve(root,p),'utf8');
 const expected='f0cf8f78bb68f305394e3cd9ccb8080cb15c147582b7f5f55888f4acdfe10141';
 const original=read('nethack-c/upstream/src/artifact.c');
 for(const [name,s]of [['upstream',original],['prepared',read('.cache/wasm64-build/tree/src/artifact.c')]])if(sha(s)!==expected)throw Error('Review changed ARTIFACT '+name+' source');
 for(const path of ['nethack-c/upstream/include/artilist.h','.cache/wasm64-build/tree/include/artilist.h'])if(sha(read(path))!=='5375cf830dac26aefd5dbefe1ab5bd79a1f1988b770e7a4dee61b6453c1dd3d3')throw Error('Review changed ARTIFACT table source '+path);
 const core=read('js/ported/artifact.js'),schema=JSON.parse(read('nethack-c/wasm/tu-fragments/artifact-schema.json'));
 if(schema.preparedSha256!==expected)throw Error('Review changed ARTIFACT ABI source binding');
 const functions=[...core.matchAll(/^export function (\w+)\(([^)]*)\)/gm)].filter(m=>m[1]!=='initializeArtifactData');
 if(functions.length!==76||functions.map(m=>m[1]).join(',')!==schema.functions.map(f=>f.name).join(','))throw Error('Review changed ARTIFACT function set/order');
 for(let i=0;i<functions.length;i++) {
  const params=functions[i][2].replace(/\/\*[\s\S]*?\*\//g,'').replace(/\s+/g,'');
  if(params!==schema.functions[i].parameters.map(p=>p.name).join(','))throw Error('Review changed ARTIFACT formals '+functions[i][1]);
 }
 const comments=original.match(/\/\*[\s\S]*?\*\//g)??[];
 for(const c of comments)if(!core.includes(c))throw Error('Missing original ARTIFACT comment '+c.slice(0,70));
 if(preprocess) {
  const defines=JSON.parse(read('nethack-c/wasm/compile-defines.json'));
  const base=['-O2','-sMEMORY64=1',...defines.map(x=>'-D'+x),'-I'+resolve(root,'.cache/wasm64-build/tree/include'),'-I'+resolve(root,'.cache/ncurses-wasm64-build/include'),'-include',resolve(root,'nethack-c/wasm/native-terminal.h')];
  const run=args=>{const r=spawnSync(resolve(root,'.cache/emsdk/upstream/emscripten/emcc'),[...base,...args,'artifact.c'],{cwd:resolve(root,'.cache/wasm64-build/tree/src'),encoding:'utf8',maxBuffer:32*1024*1024});if(r.status!==0)throw Error('ARTIFACT configured preprocessing failed: '+r.stderr);return r.stdout;};
  const macros=new Map([...run(['-E','-dM']).matchAll(/^#define (\w+)(\([^\n ]*\))? ?(.*)$/gm)].map(m=>[m[1],{params:m[2]??null,body:m[3]}]));
  if(macros.has('SFCTOOL'))throw Error('Review changed ARTIFACT configured branches');
  if(!schema.headerMacros)throw Error('ARTIFACT ABI lacks configured macro provenance');
  for(const [name,m]of Object.entries(schema.headerMacros)) {
   const actual=macros.get(name);
   if(actual?.body!==m.original||actual.params!==(m.params===null?null:'('+m.params.join(',')+')'))throw Error('Review changed ARTIFACT header macro '+name);
  }
  const manual={SetVoice:'',SIZE:'(int)(sizeof(x) / sizeof(x[0]))',Maybe_Half_Phys:'((Half_physical_damage) ? (((dmg) + 1) / 2) : (dmg))'};
  for(const [name,body]of Object.entries(manual))if(macros.get(name)?.body!==body)throw Error('Review changed ARTIFACT manual macro '+name);
  const cpp=run(['-E']);
  const rng=[...cpp.matchAll(/rng_log_set_caller\("artifact\.c", (\d+), __func__\)/g)].map(m=>Number(m[1]));
  const sites=[...core.matchAll(/C\.rngCaller\((\d+),/g)].map(m=>Number(m[1]));
  if(rng.join(',')!==sites.join(','))throw Error('Review changed ARTIFACT RNG source sites/order');
  for(const [line,fn]of [[1197,'dump_artifact_info'],[1204,'dump_artifact_info']])if(!core.includes("C.nh_snprintf('"+fn+"', "+line+',')||!cpp.includes('nh_snprintf(__func__, '+line+','))throw Error('Review changed ARTIFACT snprintf context');
 }
 return {functions:76,staticFunctions:schema.functions.filter(f=>f.static).length,originalComments:comments.length,records:Object.keys(schema.schema).length,fields:Object.values(schema.schema).reduce((n,s)=>n+s.fields.length,0),globals:schema.globals.length,variadicShapes:Object.keys(schema.variadicABI).length,headerMacros:Object.keys(schema.headerMacros??{}).length,sourceSha256:expected};
}
