import {readFileSync,writeFileSync} from 'node:fs';
import {resolve as resolveSdkPath} from 'node:path';import {pathToFileURL as sdkFileURL,fileURLToPath as sdkURLPath} from 'node:url';
const toplSourceRoot=sdkURLPath(new URL('../../../../../',import.meta.url));
const {parse}=await import(sdkFileURL(resolveSdkPath(process.env.EMSDK??resolveSdkPath(toplSourceRoot,'.cache/emsdk'),'upstream/emscripten/node_modules/acorn/dist/acorn.mjs')));
const file=process.argv[2],source=readFileSync(file,'utf8'),tokens=[],tree=parse(source,{ecmaVersion:'latest',sourceType:'module',onToken:tokens}),edits=[];
function walk(n){
 if(n.type==='BinaryExpression'&&n.operator==='/'){
  const op=tokens.find(t=>t.start>=n.left.end&&t.end<=n.right.start&&t.value==='/');if(!op)throw Error('Division operator missing');
  edits.push([n.start,n.start,'C.div('],[op.start,op.end,','],[n.end,n.end,')']);
 }
 for(const v of Object.values(n))if(Array.isArray(v)){for(const c of v)if(c?.type)walk(c);}else if(v?.type)walk(v);
}
walk(tree);let s=source;for(const[a,b,text]of edits.sort((a,b)=>b[0]-a[0]||b[1]-a[1]))s=s.slice(0,a)+text+s.slice(b);writeFileSync(file,s);console.log('TOPL integral division sites',edits.length/3);
