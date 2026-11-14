// Upgrade game glue caller metadata; source RNG policy and foreign ABIs stay put.
import fs from 'node:fs';
import assert from 'node:assert/strict';
import {parse} from 'acorn';
const rows=[];
const paths=[...fs.readdirSync('js/nethack').filter(n=>n.endsWith('.js')).map(n=>'js/nethack/'+n),...['dog','worn','steed'].map(n=>'js/nethack/native/'+n+'-graph.js')];
for(const path of paths){
 const source=fs.readFileSync(path,'utf8'),ast=parse(source,{ecmaVersion:'latest',sourceType:'module'}),edits=[];
 const nativeArg=node=>{
  if(node.type==='CallExpression'&&node.arguments.length===1&&(node.callee.type==='Identifier'&&['text','cptr'].includes(node.callee.name)||node.callee.type==='MemberExpression'&&!node.callee.computed&&node.callee.property.name==='literal'))node=node.arguments[0];
  return source.slice(node.start,node.end);
 };
 function visit(node){
  if(!node||typeof node!=='object')return;
  if(node.type==='CallExpression'&&node.callee.type==='MemberExpression'&&!node.callee.computed&&node.callee.property.name==='rng_log_set_caller'&&(['services','S'].includes(node.callee.object.name)||node.callee.object.type==='MemberExpression'&&node.callee.object.object.name==='environment'&&node.callee.object.property.name==='services')){
   assert.equal(node.arguments.length,3,path+' caller arity');const [file,line,caller]=node.arguments;
   edits.push([node.start,node.end,'recordNativeRngCaller('+source.slice(node.callee.object.start,node.callee.object.end)+','+nativeArg(file)+','+source.slice(line.start,line.end)+','+nativeArg(caller)+')']);return;
  }
  for(const value of Object.values(node))if(Array.isArray(value))value.forEach(visit);else if(value&&typeof value==='object')visit(value);
 }
 visit(ast);if(!edits.length)continue;
 let output=source;for(const [start,end,text]of edits.sort((a,b)=>b[0]-a[0]))output=output.slice(0,start)+text+output.slice(end);
 if(!source.includes("import {recordNativeRngCaller}"))output="import {recordNativeRngCaller} from '"+(path.includes("/native/")?"./rng-output.js":"./native/rng-output.js")+"';\n"+output;
 parse(output,{ecmaVersion:'latest',sourceType:'module'});fs.writeFileSync(path,output);rows.push({path,sites:edits.length});
}
console.log(JSON.stringify({files:rows.length,sites:rows.reduce((n,r)=>n+r.sites,0),rows}));
