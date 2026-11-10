// Test/build guard for the frozen configured POLYSELF source and header facts.
import {readFileSync}from 'node:fs';
import {resolve}from 'node:path';
import {createHash}from 'node:crypto';
import {spawnSync}from 'node:child_process';
const sha=bytes=>createHash('sha256').update(bytes).digest('hex');
export function checkPolyselfSource(root=process.cwd(),{preprocess=true}={}){
 const read=p=>readFileSync(resolve(root,p),'utf8'),original=read('nethack-c/upstream/src/polyself.c'),prepared=read('.cache/wasm64-build/tree/src/polyself.c');
 const expected='2f2f3dc74c2cbdd122f7a1401bd3e4e77efbc37ff6c499371cb8e57c9e39a5c8';
 for(const[label,source]of [['upstream',original],['prepared',prepared]])if(sha(source)!==expected)throw Error('Review changed POLYSELF '+label+' source');
 const core=read('js/ported/polyself.js'),runtime=read('js/ported/polyself-runtime.js'),schema=JSON.parse(read('nethack-c/wasm/tu-fragments/polyself-schema.json'));
 const names=[...original.matchAll(/^(\w+)\([^;]*?\)\s*\{/gm)].map(m=>m[1]);const jsNames=[...core.matchAll(/^export function (\w+)\(([^)]*)\)/gm)];
 if(names.length!==34||jsNames.map(m=>m[1]).join(',')!==names.join(','))throw Error('Review changed POLYSELF function set/order');
 for(const m of jsNames){const signature=new RegExp('^'+m[1]+'\\(([^)]*)\\)','m').exec(original)[1].replace(/\/\*[\s\S]*?\*\//g,'');const params=signature.trim()==='void'?[]:signature.split(',').map(s=>/\b(\w+)\s*$/.exec(s.trim())[1]);if(m[2].replaceAll(' ','')!==params.join(','))throw Error('Review changed POLYSELF formal bindings '+m[1]);}
 const comments=original.match(/\/\*[\s\S]*?\*\//g)??[];for(const comment of comments)if(!core.includes(comment))throw Error('Missing original POLYSELF comment '+comment.slice(0,80));
 if(!runtime.includes("key=name+':'+at")||!runtime.includes('cache.set(key,result)'))throw Error('Review POLYSELF canonical native record identity');
 if(preprocess){
  const defines=JSON.parse(read('nethack-c/wasm/compile-defines.json')),compiler=resolve(root,'.cache/emsdk/upstream/emscripten/emcc');
  const base=['-sMEMORY64=1',...defines.map(x=>'-D'+x),'-I'+resolve(root,'.cache/wasm64-build/tree/include'),'-I'+resolve(root,'.cache/ncurses-wasm64-build/include')];
  const run=args=>{const result=spawnSync(compiler,[...base,...args,'polyself.c'],{cwd:resolve(root,'.cache/wasm64-build/tree/src'),encoding:'utf8',maxBuffer:32*1024*1024});if(result.status!==0)throw Error('POLYSELF configured preprocessing failed: '+result.stderr);return result.stdout;};
  const macros=new Map([...run(['-E','-dM']).matchAll(/^#define (\w+)(\([^\n ]*\))? ?(.*)$/gm)].map(m=>[m[1],{params:m[2]??null,body:m[3]}]));
  if(!macros.has('STATUS_HILITES')||macros.has('DUMB'))throw Error('Review changed POLYSELF configured branches');
  for(const[name,m]of Object.entries(schema.headerMacros)){const actual=macros.get(name);if(actual?.body!==m.original||actual.params!==(m.params===null?null:'('+m.params.join(',')+')'))throw Error('Review changed POLYSELF header macro '+name);}
  const cpp=run(['-E']);if(!cpp.includes('rng_log_set_caller("polyself.c",'))throw Error('Review changed POLYSELF production filename spelling');
  for(const site of schema.rngSites)if(!cpp.includes('rng_log_set_caller("polyself.c", '+site.line+', __func__)'))throw Error('Review changed POLYSELF RNG source line '+site.line);
 }
 return{functions:34,originalComments:comments.length,records:Object.keys(schema.schema).length,fields:Object.values(schema.schema).reduce((n,s)=>n+s.fields.length,0),globals:schema.globals.length,rngSites:schema.rngSites.length,headerMacros:Object.keys(schema.headerMacros).length,sourceSha256:expected};
}
