/** Native Lua reader call order, callback COUNT and source error differential. */
import assert from 'node:assert/strict';
import { readFileSync, writeFileSync, mkdirSync, readdirSync } from 'node:fs';
import { execFileSync } from 'node:child_process';
import { fileURLToPath } from 'node:url';
import { resolve } from 'node:path';
import { createLuaCState } from '../js/lua/lapi.js';
import { createLuaBytecodeVM } from '../js/lua/bytecode-vm.js';
import { LuaError, luaStringBytes } from '../js/lua/lobject.js';
const root=fileURLToPath(new URL('../',import.meta.url)),scratch=resolve(root,'.cache/js-lua-debug/reader'),lua=resolve(root,'.cache/js-dependency-lua/lua-5.4.8/src');mkdirSync(scratch,{recursive:true});
const oracle=resolve(scratch,'oracle'),input=resolve(scratch,'input.lua');
execFileSync(resolve(root,'.cache/wasm64-build/host-cc'),['-O2','-I'+lua,resolve(root,'scripts/test-js-lua-reader.c'),...readdirSync(lua).filter(n=>n.endsWith('.c')&&!['lua.c','luac.c'].includes(n)).sort().map(n=>resolve(lua,n)),'-lm','-o',oracle]);
function native(source,chunk,fail=null){writeFileSync(input,source,'latin1');return execFileSync(oracle,[input,String(chunk),...(fail===null?[]:[String(fail)])],{encoding:'utf8',maxBuffer:64*1024*1024}).trim().split('\n').map(JSON.parse);}
function js(source,chunk,fail=Infinity){
 const events=[],blocks=new Map();let id=0,bytes=0,attempts=0,L;
 const allocator=(_u,p,old,size)=>{if(p!==null)assert.equal(blocks.get(p)?.size,old);if(size&&++attempts>=fail){events.push({event:'refused',attempt:attempts,old,size,bytes});return null;}bytes+=size-(p===null?0:old);const q=size?p??{id:++id}:null;events.push({event:'alloc',id:p?.id??q?.id??0,old,size,bytes});blocks.delete(p);if(size)blocks.set(q,{size});return q;};
 const mark=(phase,status)=>events.push({phase,status,bytes,attempts});
 try{L=createLuaCState({vmFactory:createLuaBytecodeVM,memoryAllocator:allocator});}catch(e){assert.equal(e.status,4);mark('state',4);return events;}mark('state',0);
 let at=0,calls=0,status=0,error=null;const reader=()=>{events.push({event:'read',call:++calls,bytes:L.lua_gc(3)*1024+L.lua_gc(4)});if(at===source.length)return null;const next=source.slice(at,at+chunk);at+=next.length;return next;};
 try{L.push(L.vm.loadReader(reader,'@fixture.lua','bt'));}catch(e){if(!(e instanceof LuaError))throw e;status=e.status??3;L.push(e.value);L.vm.heap.shrinkThread(L.vm.currentThread);error=luaStringBytes(L.value(-1));}
 mark('load',status);if(error!==null)events.push({error:Buffer.from(error,'latin1').toString('hex')});L.lua_close();mark('close',0);assert.equal(bytes,0);assert.equal(blocks.size,0);return events;
}
function compare(name,source,chunk,{full=true,fail=null}={}){const expected=native(source,chunk,fail),actual=js(source,chunk,fail??Infinity);if(JSON.stringify(actual)!==JSON.stringify(expected))writeFileSync(resolve(scratch,'failure.json'),JSON.stringify({name,source,chunk,fail,native:expected,js:actual},null,2));if(full)assert.deepEqual(actual,expected,name+'/'+chunk+'/'+fail);else assert.deepEqual(actual.filter(e=>e.event==='read'||e.error||e.phase==='load'),expected.filter(e=>e.event==='read'||e.error||e.phase==='load'),name+'/'+chunk);return expected;}
const dat=resolve(root,'nethack-c/upstream/dat');let cases=0,reads=0;
for(const name of readdirSync(dat).filter(n=>n.endsWith('.lua')).sort())for(const chunk of [1,7,33]){const events=compare(name,readFileSync(resolve(dat,name),'latin1'),chunk);cases++;reads+=events.filter(e=>e.event==='read').length;}
console.log(`PASS: ${cases} native chunked reader source loads / ${reads} callbacks; exact callback COUNT plus complete allocator/free transcripts.`);
const invalid=[['unknown','@ trailing bytes'],['local','local = trailing bytes'],['return','return + trailing bytes'],['function','return function( trailing bytes'],['quote','return "unfinished'],['long','return [[unfinished'],['attribute','local x<bad> = 1'],['readonly','local x<const> = 1;x=2'],['goto','goto missing'],['label','::x:: ::x::'],['stack','return '+ '('.repeat(205)+'1'+')'.repeat(205)]];
if(!process.argv.includes('--valid-only'))for(const[name,source]of invalid)for(const chunk of [1,2,3,7,source.length])compare(name,source,chunk);
console.log(`PASS: ${process.argv.includes('--valid-only')?0:invalid.length*5} native invalid-source reader stop/error/cleanup traces.`);

const directed=[['empty',''],['local','local x=17;return x'],['closure','local function f(x)return x+1 end;return f(2)'],['long','local a="'+ 'x'.repeat(90)+'";return a'],...invalid];
let refusals=0;
if(!process.argv.includes('--valid-only'))for(const[name,source]of directed)for(const chunk of [1,7]){
 const success=compare(name,source,chunk),end=success.find(e=>e.phase==='load').attempts;
 for(let fail=56;fail<=end+1;fail++){compare(name,source,chunk,{fail});refusals++;}
}
console.log(`PASS: ${refusals} native chunked reader allocation refusal schedules; exact early stop, status, errors and full cleanup.`);

let binaries=0,binaryRefusals=0;
const luac=resolve(scratch,'luac'),compiled=resolve(scratch,'compiled.luac');
execFileSync(resolve(root,'.cache/wasm64-build/host-cc'),['-O2','-I'+lua,...readdirSync(lua).filter(n=>n.endsWith('.c')&&n!=='lua.c').sort().map(n=>resolve(lua,n)),'-lm','-o',luac]);
for(const[name,text]of [['return','return 17'],['closure','local x=17;return function()return x end'],['long','return "'+'x'.repeat(90)+'"']]){
 writeFileSync(input,text,'latin1');execFileSync(luac,['-o',compiled,input]);const bytes=readFileSync(compiled).toString('latin1');
 for(const chunk of [1,7,33]){const events=compare('binary/'+name,bytes,chunk);binaries++;if(!process.argv.includes('--valid-only'))for(let fail=56;fail<=events.find(e=>e.phase==='load').attempts+1;fail++){compare('binary/'+name,bytes,chunk,{fail});binaryRefusals++;}}
}
console.log(`PASS: ${binaries} native binary-reader full traces and ${binaryRefusals} binary allocation refusal schedules.`);

const whole=readFileSync(compiled).toString('latin1'),malformed=[];
for(const length of [1,2,3,4,5,6,7,10,12,13,14,15,20,23,24,30,31,32,33,35,40,50,whole.length-1])malformed.push(['prefix-'+length,whole.slice(0,length)]);
for(const offset of [1,4,5,6,12,13,14,15,23])malformed.push(['header-'+offset,whole.slice(0,offset)+String.fromCharCode(whole.charCodeAt(offset)^1)+whole.slice(offset+1)]);
for(const[name,source]of malformed)for(const chunk of [1,7,source.length])compare(name,source,chunk);
console.log(`PASS: ${malformed.length*3} native malformed-binary reader stop/error/cleanup traces.`);
