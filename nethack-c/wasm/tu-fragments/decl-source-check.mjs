// Guard the actual prepared profile, active expanded bodies/literals and typed source data.
import {readFileSync} from 'node:fs';
import {resolve} from 'node:path';
import {createHash} from 'node:crypto';
import {spawnSync} from 'node:child_process';
import {declInitializers} from '../../../js/ported/decl.js';
const hash=s=>createHash('sha256').update(s).digest('hex');
export function checkDeclSource(root=process.cwd(),{preprocess=true}={}){
 const read=p=>readFileSync(resolve(root,p),'utf8'),source=read('.cache/wasm64-build/tree/src/decl.c'),schema=JSON.parse(read('nethack-c/wasm/tu-fragments/decl-schema.json'));
 for(const [label,text]of [['prepared',source],['upstream',read('nethack-c/upstream/src/decl.c')]])if(hash(text)!==schema.source.sha256)throw Error('Review changed DECL '+label+' source');
 const core=read('js/ported/decl.js'),runtime=read('js/ported/decl-runtime.js'),storage=read('nethack-c/wasm/tu-fragments/decl-storage.c');
 const functions=[...core.matchAll(/^export function (\w+)\(([^)]*)\)/gm)];
 if(functions.map(m=>m[1]).join(',')!=='program_state_init,decl_globals_init,sa_victual'||functions.map(m=>m[2]).join('|')!=='||context_victual')throw Error('Review changed DECL original function/formal bindings');
 const comments=source.match(/\/\*[\s\S]*?\*\//g)??[];for(const c of comments)if(!core.includes(c))throw Error('Missing original DECL comment '+c.slice(0,80));
 if(Object.keys(declInitializers).join(',')!==schema.globals.map(g=>g.name).join(','))throw Error('Review changed DECL data definition order');
 if(hash(JSON.stringify(declInitializers))!=='b57a4a6d4e57d774bda077845fe1be9299c147c09f226efb4ce0f4d30f99a294')throw Error('Review changed DECL source initializer values');
 const copyPairs=[...source.matchAll(/^\s*((?:g[a-z]|sv[a-z]|program_state)) = ((?:g_init_[a-z]|init_sv[a-z]|init_program_state));/gm)].map(m=>m[1]+','+m[2]);
 const jsPairs=[...core.matchAll(/C\.copy\(C\.(\w+), C\.(\w+)\);/g)].map(m=>m[1]+','+m[2]);
 if(copyPairs.join('|')!==jsPairs.join('|')||copyPairs.length!==47)throw Error('Review changed DECL whole structure assignment order');
 const zeroNames=[...source.matchAll(/^\s*ZERO\((\w+)\);/gm)].map(m=>m[1]),jsZeros=[...core.matchAll(/ZERO\(C\.cell\("(\w+)"\)\);/g)].map(m=>m[1]);
 if(zeroNames.join(',')!==jsZeros.join(',')||zeroNames.length!==7)throw Error('Review changed DECL exact ZERO targets');
 if([...core.matchAll(/^    MAGICCHECK\(C\.g_init_[a-z], "g_init_[a-z]"\);/gm)].length!==26||!core.includes('C.gs.subrooms = C.svr.rooms[C.MAXNROFROOMS + 1]')||!core.includes('C.gv.valuables[0].list = C.gg.gems;'))throw Error('Review changed DECL checks or native pointer construction');
 if((storage.match(/unsigned char teleport_decl_backing_\w+\[\d+\] __attribute__\(\(aligned\(\d+\)\)\);/g)??[]).length!==152||/\bconstructor\b|=\s*\{|\.havestate|"cmd_before"/.test(storage))throw Error('Review DECL zero-only native storage');
 if(!runtime.includes('Object.preventExtensions(result)')||!runtime.includes('services.heap().copyWithin'))throw Error('Review DECL typed view/copy transport');
 let bitfields=0;
 if(preprocess){
  const defines=JSON.parse(read('nethack-c/wasm/compile-defines.json')),compiler=resolve(root,'.cache/emsdk/upstream/emscripten/emcc');
  const base=['-O2','-g','-sMEMORY64=1',...defines.map(x=>'-D'+x),'-I../include','-I'+resolve(root,'.cache/ncurses-wasm64-build/include'),'-include',resolve(root,'nethack-c/wasm/native-terminal.h')];
  const run=args=>{const result=spawnSync(compiler,[...base,...args,'decl.c'],{cwd:resolve(root,'.cache/wasm64-build/tree/src'),encoding:'utf8',maxBuffer:32*1024*1024});if(result.status!==0)throw Error('DECL actual configured compiler guard failed: '+result.stderr);return result.stdout;};
  const cpp=run(['-E']),owned=[];let owner=null;for(const line of cpp.split('\n').slice(0,-1)){const m=/^# \d+ "([^"]+)"/.exec(line);if(m){owner=m[1];continue;}if(owner==='decl.c')owned.push(line);}
  const body=owned.join('\n')+'\n';if(hash(body)!==schema.source.configuredBody.sha256)throw Error('Review changed DECL active body, expanded macro or branch');
  if(JSON.stringify(body.match(/"(?:\\.|[^"\\])*"/g)??[])!==JSON.stringify(schema.source.configuredBody.activeStringTokens))throw Error('Review changed DECL active literals');
  const macros=new Map([...run(['-E','-dM']).matchAll(/^#define (\w+)(\([^\n ]*\))? ?(.*)$/gm)].map(m=>[m[1],{params:m[2]??null,body:m[3]}]));
  for(const [name,fact]of Object.entries(schema.source.branchFacts)){const actual=macros.get(name)??null;if(JSON.stringify(actual)!==JSON.stringify(fact))throw Error('Review changed DECL configured macro '+name);}
  if(!macros.has('PANICTRACE')||!body.includes('ARGV0')||!macros.has('STATUS_HILITES')||macros.has('CHANGE_COLOR')||macros.has('DLB'))throw Error('Review changed DECL actual configured selection');
  const layouts=run(['-Xclang','-fdump-record-layouts-complete','-fsyntax-only']).split('*** Dumping AST Record Layout').flatMap(block=>{
   const size=/\[sizeof=(\d+), align=(\d+)\]/.exec(block),name=/^\s*0 \| (.+)$/m.exec(block);if(!size||!name)return [];
   const fields=[...block.matchAll(/^\s*(\d+)(?::(\d+)-(\d+))? \|   (\S.*)$/gm)].map(m=>({name:/\b(\w+)\s*$/.exec(m[4])[1],offset:Number(m[1]),bitOffset:m[2]===undefined?null:Number(m[2]),bits:m[3]===undefined?null:Number(m[3])-Number(m[2])+1}));
   return [{name:name[1],size:Number(size[1]),alignment:Number(size[2]),fields}];
  });
  for(const [name,s]of Object.entries(schema.schema)){
   const expected=s.fields.map(({name,offset,bitOffset,bits})=>({name,offset,bitOffset,bits}));bitfields+=expected.filter(f=>f.bits!==null).length;
   const candidates=layouts.filter(l=>l.name===s.ctype||(l.name.includes('(unnamed at ')&&l.size===s.size&&l.alignment===s.alignment&&l.fields.map(f=>f.name).join(',')===expected.map(f=>f.name).join(',')));
   if(!candidates.some(l=>l.size===s.size&&l.alignment===s.alignment&&JSON.stringify(l.fields)===JSON.stringify(expected)))throw Error('Review changed DECL actual record/bitfield layout '+name);
  }
 }
 return {functions:3,originalComments:comments.length,globals:152,staticTemplates:49,storageBytes:353008,records:Object.keys(schema.schema).length,fields:Object.values(schema.schema).reduce((n,s)=>n+s.fields.length,0),bitfields,sourceSha256:schema.source.sha256,configuredBodySha256:schema.source.configuredBody.sha256,initializerSha256:hash(JSON.stringify(declInitializers))};
}
