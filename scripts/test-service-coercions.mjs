// Every fixed-coercion catalog is checked against C types AND wrapper ASTs.
import fs from 'node:fs';import assert from 'node:assert/strict';import {parse} from 'acorn';
import {splitCParameters,parseCPrototype} from '../js/c-runtime/prototypes.js';import {validateServiceCoercions} from '../js/nethack/service-coercions.js';
const publicTypes=JSON.parse(fs.readFileSync('js/nethack/public-functions.json')).functions;
const canonical={pointer:'pointer',text:'text',integer:'int',int:'int',byte:'char',char:'char',coord:'short',short:'short',long:'long',size:'size',uint:'uint'};
const converters=Object.fromEntries(Object.keys(canonical).map(k=>[k,v=>v]));
const allCatalogs=fs.readdirSync('js/nethack').filter(n=>n.endsWith('.json')).map(file=>({file,data:JSON.parse(fs.readFileSync('js/nethack/'+file))}));
const catalogs=allCatalogs.filter(({data})=>Object.values(data.calls??{}).some(r=>Array.isArray(r.coercions)));
let rows=0,argumentsChecked=0,negativeControls=0;const counts={};
for(const {file,data}of catalogs){
 validateServiceCoercions(file,data.calls,publicTypes,converters);
 const source='nethack-c/wasm/tu-libraries/'+file.replace(/(?:-services)?-abi\.json$/,'')+'.js',ast=parse(fs.readFileSync(source,'utf8'),{ecmaVersion:'latest',sourceType:'script'}),properties=[];
 function visit(n){if(!n||typeof n!=='object')return;if(n.type==='Property'&&n.value?.type==='ArrowFunctionExpression')properties.push(n);for(const value of Object.values(n))if(Array.isArray(value))value.forEach(visit);else if(value&&typeof value==='object')visit(value);}visit(ast);
 counts[file]=Object.keys(data.calls).length;
 for(const [name,row]of Object.entries(data.calls)){
  const unwrap=n=>n.type==='CallExpression'&&n.callee.name==='Number'&&n.arguments.length===1?unwrap(n.arguments[0]):n;
  const candidates=properties.filter(p=>(p.key.name??p.key.value)===name&&unwrap(p.value.body)?.callee?.name==='_'+row.target);
  assert.equal(candidates.length,1,file+'.'+name+' has exactly one original wrapper');
  const fn=candidates[0].value,call=unwrap(fn.body),params=fn.params.map(n=>{assert.equal(n.type,'Identifier');return n.name;});
  assert.equal(call.arguments.length,parseCPrototype(publicTypes[row.target]).parameters.length,file+'.'+name+' C target arity');
  const sourceConversions=call.arguments.map(n=>{
   let kind,arg;
   if(n.type==='CallExpression'&&n.arguments.length===1&&n.arguments[0].type==='Identifier'){kind=n.callee.name==='Number'?'int':canonical[n.callee.name]??({ptr:'pointer',narrow:'short',BigInt:'long'})[n.callee.name];arg=n.arguments[0].name;}
   else if(n.type==='BinaryExpression'&&n.right.value===0&&['|','>>>'].includes(n.operator)){kind=n.operator==='|'?'int':'uint';arg=n.left.type==='Identifier'?n.left.name:n.left.type==='CallExpression'&&n.left.callee.name==='Number'?n.left.arguments[0].name:undefined;}
   else if(n.type==='Identifier'){kind='int';arg=n.name;}
   assert.ok(kind&&params.includes(arg),file+'.'+name+' source conversion '+JSON.stringify(n));return [kind,params.indexOf(arg)];
  });
  const actual=row.coercions.map((entry,i)=>Array.isArray(entry)?[canonical[entry[0]],entry[1]]:[canonical[entry],i]);
  assert.deepEqual(actual,sourceConversions,file+'.'+name+' every converter and source argument order');rows++;argumentsChecked+=actual.length;
  if(actual.length){
   for(const bad of [[],row.coercions.slice(0,-1),...['unknown','constructor','toString'].map(kind=>row.coercions.map((v,i)=>i?v:Array.isArray(v)?[kind,v[1]]:kind))]){assert.throws(()=>validateServiceCoercions(file,{[name]:{...row,coercions:bad}},publicTypes,converters),/Invalid .* service metadata/);negativeControls++;}
   assert.throws(()=>validateServiceCoercions(file,{[name]:{...row,coercions:row.coercions.map((v,i)=>i?v:['pointer',actual.length])}},publicTypes,converters),/invalid source argument/);negativeControls++;
  }
 }
}
assert.equal(catalogs.length,4);assert.equal(rows,337);
let otherArgumentSchemas=0,variadicSchemas=0,sdkDeclarations=0;
const sdk=fs.readFileSync('nethack-c/wasm/tu-mail-support.inc','utf8');
for(const {file,data}of allCatalogs)for(const [name,row]of Object.entries(data.calls??{})){
 if(!Array.isArray(row.arguments))continue;otherArgumentSchemas++;
 const proto=row.prototype??publicTypes[row.target];let params;
 if(proto)params=parseCPrototype(proto).parameters;
 else{assert.ok(file==='mail-abi.json'&&['stat','getpwuid'].includes(row.target),'Unresolved service declaration '+file+'.'+name);const match=new RegExp('teleport_mail_'+row.target+'\\(([^)]*)\\)').exec(sdk);assert.ok(match);params=splitCParameters(match[1]);sdkDeclarations++;}
 const required=params.indexOf('...');if(required>=0){assert.ok(row.arguments.length>=required,file+'.'+name+' fixed variadic prefix');variadicSchemas++;}else assert.equal(row.arguments.length,params.length,file+'.'+name+' every fixed argument');
 assert.ok(row.arguments.every(kind=>typeof kind==='string'&&kind.length),file+'.'+name+' nonempty argument conversion');
}
assert.equal(otherArgumentSchemas,490);assert.equal(variadicSchemas,27);assert.equal(sdkDeclarations,2);
const evidence={passed:true,catalogs:counts,rows,argumentsChecked,negativeControls,otherArgumentSchemas,variadicSchemas,sdkDeclarations,scope:'Every fixed-coercion catalog: each target C signature, original wrapper converter and source argument order. Empty/truncated/unknown/out-of-range metadata fails before gameplay. This is static wiring coverage, not execution of every game policy.'};
fs.mkdirSync('.cache/service-coercions',{recursive:true});fs.writeFileSync('.cache/service-coercions/audit.json',JSON.stringify(evidence,null,2)+'\n');console.log(JSON.stringify(evidence));
