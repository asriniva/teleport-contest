// Independently re-expand the original configured catalogues. No game runtime
// or oracle output is used to generate the authoritative checked-in JS data.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import {execFileSync} from 'node:child_process';
import {fileURLToPath} from 'node:url';
import path from 'node:path';
import * as core from '../js/ported/earlyarg.js';
const root=fileURLToPath(new URL('../',import.meta.url));
const sdk=process.env.EMSDK||path.join(root,'.cache/emsdk');
const defines=JSON.parse(fs.readFileSync(path.join(root,'nethack-c/wasm/compile-defines.json'))).map(x=>'-D'+x);
const source=execFileSync(path.join(sdk,'upstream/emscripten/emcc'),['-E','-P',...defines,'-sMEMORY64=1','-I'+path.join(root,'.cache/wasm64-build/tree/include'),'-I'+path.join(root,'.cache/ncurses-wasm64-build/include'),path.join(root,'nethack-c/upstream/src/earlyarg.c')],{encoding:'utf8',maxBuffer:32*1024*1024});
const names=['monsdump','objdump','defsym_cmap_dump','defsym_mon_syms_dump','defsym_mon_defchars_dump','objclass_defchars_dump','objclass_classes_dump','objclass_syms_dump','arti_enum_dump','mcastu_enum_dump'];
function literal(value){
 // C octal character escapes are absent in JSON; handle the finite source form
 // directly rather than evaluating preprocessed C as JavaScript.
 const body=value.slice(1,-1);
 if(!body.startsWith('\\'))return body.charCodeAt(0);
 if(/^\\[0-7]{1,3}$/.test(body))return parseInt(body.slice(1),8);
 const escapes={'\\n':10,'\\t':9,'\\r':13,'\\b':8,'\\f':12,'\\v':11,'\\\\':92,"\\'":39,'\\"':34};
 if(body in escapes)return escapes[body];
 if(/^\\x[0-9a-f]+$/i.test(body))return parseInt(body.slice(2),16);
 throw new Error('Review changed catalogue character literal: '+value);
}
let count=0;
for(const name of names){
 const match=new RegExp('\\b'+name+'\\s*\\[\\]\\s*=\\s*\\{').exec(source);assert.ok(match,name);
 let at=match.index+match[0].length,depth=1,quote=null,escaped=false,start,rows=[];
 for(;depth;at++){
  const ch=source[at];
  if(quote){if(escaped)escaped=false;else if(ch==='\\')escaped=true;else if(ch===quote)quote=null;}
  else if(ch==='"'||ch==="'")quote=ch;
  else if(ch==='{'){if(depth===1)start=at+1;depth++;}
  else if(ch==='}'){depth--;if(depth===1)rows.push(source.slice(start,at));}
 }
 const expected=rows.map(row=>{
  const comma=row.indexOf(',');let val=row.slice(0,comma).trim();
  const nm=Array.from(row.slice(comma+1).matchAll(/"(?:[^"\\]|\\.)*"/g),m=>JSON.parse(m[0])).join('');
  if(val.startsWith("'"))val=literal(val);else if(/^-?\d+$/.test(val))val=Number(val);else assert.match(val,/^\w+$/);
  return {val,nm};
 });
 assert.deepEqual(core[name],expected,name);count+=expected.length;
}
console.log(`EARLYARG: ${count} source-expanded rows in ${names.length} authoritative JS catalogues match.`);
