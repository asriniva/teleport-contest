// Test/build guard for the frozen configured MHITU source and header facts.
import {readFileSync}from 'node:fs';
import {resolve}from 'node:path';
import {createHash}from 'node:crypto';
import {spawnSync}from 'node:child_process';
const sha=bytes=>createHash('sha256').update(bytes).digest('hex');
export function checkMhituSource(root=process.cwd(),{preprocess=true}={}){
 const read=p=>readFileSync(resolve(root,p),'utf8'),original=read('nethack-c/upstream/src/mhitu.c'),prepared=read('.cache/wasm64-build/tree/src/mhitu.c');
 const expected='5e0fb2e24f51f8e8803e58e4016f126bbe3fdbff9dd2ddbdc73b9d1d20c024b3';
 for(const[label,source]of [['upstream',original],['prepared',prepared]])if(sha(source)!==expected)throw Error('Review changed MHITU '+label+' source');
 const core=read('js/ported/mhitu.js'),runtime=read('js/nethack/bindings/mhitu.js'),schema=JSON.parse(read('nethack-c/wasm/tu-fragments/mhitu-schema.json'));
 const names=["hitmsg", "missmu", "mswings_verb", "mswings", "mpoisons_subj", "u_slow_down", "wildmiss", "expels", "getmattk", "calc_mattacku_vars", "mtrapped_in_pit", "mattacku", "summonmu", "diseasemu", "u_slip_free", "magic_negation", "hitmu", "gulp_blnd_check", "gulpmu", "explmu", "gazemu", "mdamageu", "could_seduce", "doseduce", "mayberem", "assess_dmg", "mon_avoiding_this_attack", "ranged_attk_available", "passiveum", "cloneu"];const jsNames=[...core.matchAll(/^export function (\w+)\(([^)]*)\)/gm)];
 if(names.length!==30||jsNames.map(m=>m[1]).join(',')!==names.join(','))throw Error('Review changed MHITU function set/order');
 for(const m of jsNames){const signature=new RegExp('^'+m[1]+'\\(([^)]*)\\)','m').exec(original)[1].replace(/\/\*[\s\S]*?\*\//g,'');const params=signature.trim()==='void'?[]:signature.split(',').map(s=>/\b(\w+)\s*$/.exec(s.trim().replace(/\[\]/g,''))[1]);if(m[2].replaceAll(' ','')!==params.join(','))throw Error('Review changed MHITU formal bindings '+m[1]);}
 const comments=original.match(/\/\*[\s\S]*?\*\//g)??[];for(const comment of comments)if(!core.includes(comment))throw Error('Missing original MHITU comment '+comment.slice(0,80));
 // Check the actual shared implementation and the module's exact cache wiring.
 const factories=read('js/c-runtime/adapter-factories.js'),records=read('js/c-runtime/records.js');
 if(!runtime.includes("const view=CAdapter.createDescriptorViewFactory({services,schemas,address:addr,raw,cache,names,decode,")||!factories.includes("cacheKey:(name,at)=>name+':'+at")||!factories.includes('checked:false,trackDefinitions:false')||!records.includes("publish='early'")||!records.includes('if(cache?.has(key))return cache.get(key);')||!records.includes("if(cache&&publish==='early')cache.set(key,view);"))throw Error('Review MHITU shared canonical native record identity');
 if(preprocess){
  const defines=JSON.parse(read('nethack-c/wasm/compile-defines.json')),compiler=resolve(root,'.cache/emsdk/upstream/emscripten/emcc');
  const base=['-sMEMORY64=1',...defines.map(x=>'-D'+x),'-I'+resolve(root,'.cache/wasm64-build/tree/include'),'-I'+resolve(root,'.cache/ncurses-wasm64-build/include')];
  const run=args=>{const result=spawnSync(compiler,[...base,...args,'mhitu.c'],{cwd:resolve(root,'.cache/wasm64-build/tree/src'),encoding:'utf8',maxBuffer:32*1024*1024});if(result.status!==0)throw Error('MHITU configured preprocessing failed: '+result.stderr);return result.stdout;};
  const macros=new Map([...run(['-E','-dM']).matchAll(/^#define (\w+)(\([^\n ]*\))? ?(.*)$/gm)].map(m=>[m[1],{params:m[2]??null,body:m[3]}]));
  if(macros.has('PM_BEHOLDER'))throw Error('Review changed MHITU configured branches');
  for(const[name,m]of Object.entries(schema.headerMacros)){const actual=macros.get(name);if(actual?.body!==m.original||actual.params!==(m.params===null?null:'('+m.params.join(',')+')'))throw Error('Review changed MHITU header macro '+name);}
  for(const[name,alias]of Object.entries(schema.fieldAliases)){if(macros.get(name)?.body!==alias.original)throw Error('Review changed MHITU field alias '+name);}
  const cpp=run(['-E']);
  let owner=null;const owned=[];for(const line of cpp.split('\n').slice(0,-1)){const marker=/^# \d+ "([^"]+)"/.exec(line);if(marker){owner=marker[1];continue;}if(owner==='mhitu.c')owned.push(line);}
  const body=owned.join('\n')+'\n';if(sha(body)!==schema.configuredBodies.sha256)throw Error('Review changed MHITU active configured bodies/macros/literals');
  if(JSON.stringify(body.match(/"(?:\\.|[^"\\])*"/g)??[])!==JSON.stringify(schema.configuredBodies.activeStringTokens))throw Error('Review changed MHITU active string literals');
  if(/\branged_attk_assessed\s*\(/.test(body)||/case AD_SLEE:/.test(body))throw Error('Review changed MHITU inactive branch selection');
if(!cpp.includes('rng_log_set_caller("mhitu.c",'))throw Error('Review changed MHITU production filename spelling');
  for(const site of schema.rngSites)if(!cpp.includes('rng_log_set_caller("mhitu.c", '+site.line+', __func__)'))throw Error('Review changed MHITU RNG source line '+site.line);
 }
 return{functions:30,originalComments:comments.length,records:Object.keys(schema.schema).length,fields:Object.values(schema.schema).reduce((n,s)=>n+s.fields.length,0),globals:schema.globals.length,rngSites:schema.rngSites.length,headerMacros:Object.keys(schema.headerMacros).length,sourceSha256:expected};
}
