// C &&/|| are int0/1. Keep condition-only uses and exact short-circuit order.
import {readFileSync,writeFileSync} from 'node:fs';
import {resolve} from 'node:path';
import {pathToFileURL,fileURLToPath} from 'node:url';
const toplSourceRoot=fileURLToPath(new URL('../../../../../',import.meta.url));
const {parse}=await import(pathToFileURL(resolve(process.env.EMSDK??resolve(toplSourceRoot,'.cache/emsdk'),'upstream/emscripten/node_modules/acorn/dist/acorn.mjs')));
const file=process.argv[2],source=readFileSync(file,'utf8'),tree=parse(source,{ecmaVersion:'latest',sourceType:'module'}),ranges=[];
function visit(n,parent,key){
 if(n.type==='LogicalExpression'&&['&&','||'].includes(n.operator)&&parent?.type!=='LogicalExpression'){
  const truthOnly=((['IfStatement','WhileStatement','DoWhileStatement','ForStatement','ConditionalExpression'].includes(parent?.type))&&key==='test')||(parent?.type==='UnaryExpression'&&parent.operator==='!');
  if(!truthOnly)ranges.push([n.start,n.end]);
 }
 for(const[k,child]of Object.entries(n)){
  if(Array.isArray(child)){for(const c of child)if(c?.type)visit(c,n,k);}
  else if(child?.type)visit(child,n,k);
 }
}
visit(tree,null,null);let result=source;
const insertions=[];for(const[start,end]of ranges){insertions.push([start,'Number(Boolean('],[end,'))']);}
for(const[at,text]of insertions.sort((a,b)=>b[0]-a[0]))result=result.slice(0,at)+text+result.slice(at);
writeFileSync(file,result);console.log('TOPL stored/returned logical values canonicalized:',ranges.length);
