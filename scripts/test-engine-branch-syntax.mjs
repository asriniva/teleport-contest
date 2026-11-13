import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import {parse} from '../.cache/emsdk/upstream/emscripten/node_modules/acorn/dist/acorn.mjs';
import {isEngine} from './branch-coverage/loader.mjs';
import {instrument} from './branch-coverage/instrument.mjs';
let modules=0,sites=0;
function walk(directory){
 for(const entry of fs.readdirSync(directory,{withFileTypes:true})){
  const file=path.posix.join(directory,entry.name);
  if(entry.isDirectory())walk(file);
  else if(isEngine(file)){
   const source=fs.readFileSync(file,'utf8'),transformed=instrument(source,file);
   try{parse(transformed.code,{ecmaVersion:'latest',sourceType:'module'});}catch(error){throw Error(file+': '+error.message,{cause:error});}
   assert.equal(new Set(transformed.sites.map(site=>site.key)).size,transformed.sites.length,file+' stable site keys');
   assert.equal(fs.readFileSync(file,'utf8'),source,file+' original source untouched');
   modules++;sites+=transformed.sites.length;
  }
 }
}
walk('js');
assert.ok(modules>0);
console.log('PASS: '+modules+' transformed engine modules parse, with '+sites+' unique decision/function sites and original sources unchanged.');
