// Resolve catalog dependencies against the actual fully assembled production
// program. Resolution checks wiring; this deliberately does not run game bodies.
import fs from 'node:fs';
import assert from 'node:assert/strict';
import {createStandaloneProgram} from '../js/nethack/program.js';
import {parseCPrototype} from '../js/c-runtime/prototypes.js';
import * as terminal from '../js/ported/termcap.js';
const read=file=>JSON.parse(fs.readFileSync(file,'utf8'));
const layouts=read('js/wasm/tu-layouts.json'),publicFunctions=read('js/nethack/public-functions.json').functions;
const {environment:env}=createStandaloneProgram({layouts,readKey(){throw Error('Wiring census must not run gameplay');}});
const symbols=new Set();
function walk(value){
 if(!value||typeof value!=='object')return;
 if(value.dependencies)for(const [name,row]of Object.entries(value.dependencies)){
  const prototype=typeof row==='string'?row:row?.type??row?.prototype;
  if(Object.hasOwn(publicFunctions,name)&&typeof prototype==='string'){
   parseCPrototype(prototype);symbols.add(name);
  }
 }
 for(const child of Object.values(value))walk(child);
}
for(const file of fs.readdirSync('js/nethack').filter(file=>file.endsWith('-abi.json')||file==='address-ports.json'))walk(read('js/nethack/'+file));
const missing=[];
for(const name of symbols){
 try{assert.equal(typeof env.resolve(name),'function');}
 catch(error){if(typeof env.services[name]!=='function')missing.push({name,message:error.message});}
}
assert.deepEqual(missing,[],'Unresolved production catalog dependencies');
const terminalNames=read('js/nethack/terminal-metadata.json').functions;
for(const name of terminalNames)assert.equal(typeof terminal[name],'function','Missing terminal policy '+name);
const recipes=read('js/nethack/lua-api.json').functions;
for(const [name,recipe]of Object.entries(recipes)){
 assert.ok(Object.hasOwn(publicFunctions,name),'Lua recipe without public prototype '+name);
 const prototype=parseCPrototype(publicFunctions[name]);
 assert.equal(env.ctypes.abiType(recipe.return),env.ctypes.abiType(prototype.result),'Lua return representation '+name);
 for(const argument of recipe.arguments)assert.ok(argument.index===null||Number.isInteger(argument.index)&&argument.index>=0&&argument.index<prototype.parameters.length,'Lua argument index '+name);
}
console.log(JSON.stringify({passed:true,registeredModules:Object.keys(env.status()).length,dependencySymbols:symbols.size,terminalFunctions:terminalNames.length,luaRecipes:Object.keys(recipes).length,scope:'Actual production assembly and symbol resolution; terminal policy presence and Lua recipe prototype/index checks. No claim of branch execution or callback behavior coverage.'}));
