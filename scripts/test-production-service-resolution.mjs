// Resolve literal adapter dependencies in the actual assembled program. Deferred
// symbols must be resolved, not mistaken for missing published functions.
import './pure-js-probes/deny-wasm.mjs';
import fs from 'node:fs';
import assert from 'node:assert/strict';
import {parse} from '../.cache/emsdk/upstream/emscripten/node_modules/acorn/dist/acorn.mjs';
import {createStandaloneProgram} from '../js/nethack/program.js';
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json'));
const {environment:env}=createStandaloneProgram({layouts,readKey(){throw Error('Unexpected input');}});
const exclusions=new Map([
 ['messages.js:waitpid','External message-handler parent process; process provider remains a separate obligation.'],
 ['messages.js:execv','External message-handler child process; process provider remains a separate obligation.'],
 ['report.js:readlink','Guarded optional provider; the actual CVFS fallback implements errors for regular files.'],
]);
const rows=[],missing=[],used=new Set();
function walk(node,visit){if(!node||typeof node!=='object')return;if(Array.isArray(node)){for(const value of node)walk(value,visit);return;}if(!node.type)return;visit(node);for(const [key,value]of Object.entries(node))if(!['loc','start','end'].includes(key))walk(value,visit);}
for(const name of fs.readdirSync('js/nethack').filter(n=>n.endsWith('.js')).sort()){
 const file='js/nethack/'+name,source=fs.readFileSync(file,'utf8');
 if(!/\b(?:environment|env)\.resolve\b/.test(source))continue;
 walk(parse(source,{ecmaVersion:'latest',sourceType:'module',locations:true}),node=>{
  if(node.type!=='CallExpression')return;
  const callee=node.callee,lookup=callee.type==='Identifier'&&callee.name==='resolve'||callee.type==='MemberExpression'&&!callee.computed&&['environment','env'].includes(callee.object.name)&&callee.property.name==='resolve';
  if(!lookup||node.arguments[0]?.type!=='Literal'||typeof node.arguments[0].value!=='string')return;
  const symbol=node.arguments[0].value,key=name+':'+symbol,row={file,line:node.loc.start.line,symbol};
  if(exclusions.has(key)){used.add(key);rows.push({...row,excluded:exclusions.get(key)});return;}
  try{assert.equal(typeof env.services[symbol]==='function'?typeof env.services[symbol]:typeof env.resolve(symbol),'function');rows.push(row);}
  catch(error){missing.push({...row,error:error.message});}
 });
}
assert.deepEqual([...used].sort(),[...exclusions.keys()].sort(),'every exclusion still has a reviewed call site');
fs.mkdirSync('.cache/production-service-resolution',{recursive:true});
fs.writeFileSync('.cache/production-service-resolution/evidence.json',JSON.stringify({rows,missing,scope:'Literal resolve calls in top-level NetHack adapters against the assembled program, including deferred symbols. Dynamic names, optional process providers and path reachability are separate obligations.'},null,2)+'\n');
assert.deepEqual(missing,[],'production adapter dependencies must resolve');
// You1 is a configured header macro, not a linkable public C symbol. Test
// percent-bearing strings to reject an accidental format-string expansion.
const messages=env.start('messages'),you=messages.namespace.You,seen=[];
try{
 messages.namespace.You=(format,value)=>{seen.push([env.memory.readString(format),env.memory.readString(value)]);};
 for(const value of ['', 'shudder for a moment.', '100% %s %n'])env.start('world-position').environment.You1(env.services.literal(value));
 assert.deepEqual(seen,[['%s',''],['%s','shudder for a moment.'],['%s','100% %s %n']]);
}finally{messages.namespace.You=you;}
console.log('PASS '+rows.length+' literal production service lookups, including deferred symbols; '+used.size+' explicit optional-provider obligations.');
