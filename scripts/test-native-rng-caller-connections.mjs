// Compare the entire unchanged game glue after normalizing the explicit caller
// value transport change. The environment's separately tested logger assembly
// is checked at caller sites only. No baseline execution/profiling is performed.
import fs from 'node:fs';import {execFileSync} from 'node:child_process';import assert from 'node:assert/strict';import {parse} from 'acorn';
const base=process.argv[2]??'9bf16acf47b5cec0d1b8dfbf3c2515cea0d6d86d',paths=[...fs.readdirSync('js/nethack').filter(n=>n.endsWith('.js')).map(n=>'js/nethack/'+n),...['dog','worn','steed'].map(n=>'js/nethack/native/'+n+'-graph.js')];
const options={ecmaVersion:'latest',sourceType:'module'};let files=0,sites=0,wholeGlueAstFiles=0;
const isOld=n=>n.type==='CallExpression'&&n.callee.type==='MemberExpression'&&!n.callee.computed&&n.callee.property.name==='rng_log_set_caller'&&(['services','S'].includes(n.callee.object.name)||n.callee.object.type==='MemberExpression'&&n.callee.object.object.name==='environment'&&n.callee.object.property.name==='services');
const arg=n=>n.type==='CallExpression'&&n.arguments.length===1&&(n.callee.type==='Identifier'&&['text','cptr'].includes(n.callee.name)||n.callee.type==='MemberExpression'&&!n.callee.computed&&n.callee.property.name==='literal')?n.arguments[0]:n;
function clean(n){if(Array.isArray(n))return n.filter(x=>!(x?.type==='ImportDeclaration'&&x.specifiers.some(s=>s.local.name==='recordNativeRngCaller'))).map(clean);if(!n||typeof n!=='object')return n;if(isOld(n))n={...n,callee:{type:'Identifier',name:'recordNativeRngCaller'},arguments:[n.callee.object,arg(n.arguments[0]),n.arguments[1],arg(n.arguments[2])]};return Object.fromEntries(Object.entries(n).filter(([k])=>!['start','end','raw'].includes(k)).map(([k,v])=>[k,clean(v)]));}
function calls(node,predicate,out=[]){if(!node||typeof node!=='object')return out;if(predicate(node))out.push(node);for(const value of Object.values(node))if(Array.isArray(value))value.forEach(n=>calls(n,predicate,out));else if(value&&typeof value==='object')calls(value,predicate,out);return out;}
for(const path of paths){if(path==='js/nethack/native/rng-output.js')continue;let text;try{text=execFileSync('git',['show',base+':'+path],{encoding:'utf8',stdio:['ignore','pipe','ignore']});}catch{continue;}
 const old=parse(text,options),before=calls(old,isOld);if(!before.length)continue;
 const current=parse(fs.readFileSync(path,'utf8'),options),after=calls(current,n=>n.type==='CallExpression'&&n.callee.name==='recordNativeRngCaller');assert.equal(after.length,before.length,path+' all sites connected');
 assert.deepEqual(clean(after),clean(before),path+' caller expressions/order');
 if(path!=='js/nethack/environment.js'){assert.deepEqual(clean(current),clean(old),path+' whole glue policy AST');wholeGlueAstFiles++;}
 files++;sites+=before.length;
}
assert.equal(files,65);assert.equal(sites,76);assert.equal(wholeGlueAstFiles,64);console.log(JSON.stringify({passed:true,base,files,sites,wholeGlueAstFiles,environmentCallerSitesOnly:true}));
