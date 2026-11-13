// Reproduce specialization from the immutable pre-change display source.
// Usage: node scripts/specialize-display-fields.mjs /path/to/acorn.mjs
import fs from 'node:fs';
import {execFileSync} from 'node:child_process';
import {pathToFileURL} from 'node:url';
const {parse}=await import(pathToFileURL(process.argv[2]));
const source=execFileSync('git',['show','f58b27e:js/ported/display.js'],{encoding:'utf8'});
const schema=JSON.parse(fs.readFileSync('nethack-c/wasm/tu-fragments/display-schema.json'));
const ast=parse(source,{ecmaVersion:'latest',sourceType:'module'}),edits=[],fields=new Map();
function walk(node,parent){
 if(!node||typeof node!=='object')return;
 if(node.type==='MemberExpression'&&!node.computed&&['value','address'].includes(node.property.name)){
  const call=node.object;
  if(call.type==='CallExpression'&&call.callee.type==='MemberExpression'&&call.callee.object.name==='C'&&call.callee.property.name==='field'&&call.arguments.length===3){
   const [at,kind,field]=call.arguments;
   const declaration=schema.schema[kind.value]?.fields.find(f=>f.name===field.value);
   const written=(parent?.type==='AssignmentExpression'&&parent.left===node)||(parent?.type==='UpdateExpression');
   if(declaration&&!declaration.bit&&!written){
    const op=node.property.name==='address'?'address':'read',name=`display_${op}_${kind.value}_${field.value}`;
    fields.set(name,{name,kind:kind.value,field:field.value,canonical:declaration.canonical,op});
    edits.push({start:node.start,end:at.start,text:`C.${name}(`},{start:at.end,end:node.end,text:')'});
   }
  }
 }
 for(const [key,value]of Object.entries(node))if(key!=='start'&&key!=='end'){
  if(Array.isArray(value))for(const child of value)walk(child,node);else if(value&&typeof value==='object')walk(value,node);
 }
}
walk(ast);
let output=source;
for(const edit of edits.sort((a,b)=>b.start-a.start))output=output.slice(0,edit.start)+edit.text+output.slice(edit.end);
parse(output,{ecmaVersion:'latest',sourceType:'module'});
const manifest=JSON.stringify([...fields.values()],null,2)+'\n';
if(process.argv.includes('--check')){
 if(fs.readFileSync('js/ported/display.js','utf8')!==output||fs.readFileSync('js/nethack/display-direct-fields.json','utf8')!==manifest)throw Error('DISPLAY specialization differs from the pinned source transformation');
}else{
 fs.writeFileSync('js/ported/display.js',output);
 fs.writeFileSync('js/nethack/display-direct-fields.json',manifest);
}
console.log(JSON.stringify({specializedAccesses:edits.length/2,fieldOperations:fields.size}));
