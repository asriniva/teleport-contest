// Existing record-based policy versus direct typed views over identical storage.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import {execFileSync} from 'node:child_process';
import {CMemory} from '../js/c-runtime/heap.js';
import {createCTypes} from '../js/c-runtime/types.js';
import {createBitfields} from '../js/c-runtime/bitfields.js';
import {withCEnvironment} from '../js/c-runtime/context.js';
import {createTermcapEnvironment} from '../js/nethack/bindings/termcap.js';
import * as candidate from '../js/ported/termcap.js';
import metadata from '../js/nethack/records.json' with {type:'json'};
import layouts from '../js/wasm/tu-layouts.json' with {type:'json'};
const source=execFileSync('git',['show','f58b27e:js/ported/termcap.js'],{encoding:'utf8'}).replace("'../c-runtime/context.js'",JSON.stringify(new URL('../js/c-runtime/context.js',import.meta.url).href));
const baseline=await import('data:text/javascript;base64,'+Buffer.from(source).toString('base64'));
const schema=JSON.parse(fs.readFileSync(new URL('../nethack-c/wasm/tu-fragments/termcap-schema.json',import.meta.url))),kinds=Object.keys(schema.schema),L=layouts.termcap;
function fixture(policy){
 const memory=new CMemory({initialBytes:65536,maximumBytes:262144}),types=createCTypes(memory,metadata,createBitfields(memory,metadata));
 const width=d=>d.t?Number(d.t.slice(1))/8:d.p!==undefined||d.f?8:d.s?L[d.s+'Size']:d.a.reduce((a,b)=>a*b,1)*width(d.e);
 const globals=schema.globals.map(g=>memory.calloc(1,width(g.d)));
 let genericAccesses=0;
 const declaration=(k,i)=>[schema.schema[kinds[k]].ctype,schema.schema[kinds[k]].fields[i]];
 const services={moduleKey:{},heap:()=>memory.HEAPU8,global:i=>globals[i],stackSave:()=>0,stackRestore:()=>{},
 address:(k,p,i)=>{const[t,f]=declaration(k,i);return types.fieldAddress(t,p,f.name);},
 read:(k,p,i)=>{genericAccesses++;const[t,f]=declaration(k,i);return types.getField(t,p,f.name,f.ctype);},
 write:(k,p,i,v)=>{genericAccesses++;const[t,f]=declaration(k,i);return types.setField(t,p,f.name,f.ctype,v);}};
 const env=createTermcapEnvironment(services,L,policy),screen=globals[schema.globals.findIndex(g=>g.name==='nomux_buf')],trace=[];
 let formatHook=null;
 env.sprintf=(p,fmt,...args)=>{trace.push([p,fmt,...args]);formatHook?.();const text=fmt.replace('%d',String(args[0]));const bytes=Uint8Array.from(text,c=>c.charCodeAt(0));memory.HEAPU8.set(bytes,p);memory.HEAPU8[p+bytes.length]=0;return bytes.length;};
 const call=(name,...args)=>withCEnvironment(env,policy[name],...args);
 env.ttyDisplay=memory.calloc(1,L.DisplayDescSize);env.ttyDisplay.cury=1;env.ttyDisplay.curx=2;
 env.nomux_fg_cur=7;
 return {memory,env,screen,trace,call,hook:fn=>formatHook=fn,accesses:()=>genericAccesses};
}
let checks=0;
for(let seed=0;seed<9;seed++){
 const pair=[fixture(baseline),fixture(candidate)];
 function equal(label){assert.deepEqual(pair[1].memory.HEAPU8,pair[0].memory.HEAPU8,label+' heap');assert.deepEqual(pair[1].trace,pair[0].trace,label+' formatting');checks+=2;}
 const both=(name,...args)=>{for(const f of pair)f.call(name,...args);equal(name);};
 both('nomux_clear_screen');
 for(const ch of [32,65,127,128,255,256,0x7fffffff,-1])both('nomux_putch',ch);
 for(const [r,c]of [[-1,0],[24,0],[0,-10],[0,0],[23,79],[5,80]])both('nomux_clear_to_eol',r,c);
 for(const f of pair){
  for(let i=0;i<1920;i++){
   const n=i*4+f.screen,style=Math.floor(i/20)+seed;
   f.memory.HEAPU8.set([[0,32,65,127,128,255][(i+seed)%6],style%16,style%8,style%2],n);
  }
 }
 both('nomux_capture_screen');
 // Grow and mutate DEC mode during formatting, after character/style reads.
 for(const f of pair){let first=true;f.hook(()=>{if(!first)return;first=false;f.memory.grow(131072);f.memory.HEAPU8[f.screen+3]^=1;});}
 both('nomux_capture_screen');
 for(const f of pair){f.hook(null);f.env.nomux_raw_row=23;f.env.nomux_raw_col=78;}
 for(const ch of [65,255,10,66,31])both('nomux_raw_putch',ch);
 // Direct writes are immediately visible through retained legacy record views.
 const current=pair[1],held=current.env.nomux_buf[1][2];current.call('nomux_putch',90);assert.equal(held.ch,90);checks++;
 held.ch=-1;assert.equal(current.env.nomuxScreenViews().signed[(1*80+2)*4],-1);checks++;
 const views=current.env.nomuxScreenViews();assert.equal(current.env.nomuxScreenViews(),views);checks++;
 assert.equal(views.bytes.buffer,current.memory.buffer);checks++;
 const other=fixture(candidate);other.call('nomux_clear_screen');assert.equal(other.env.nomuxScreenViews().bytes[(1*80+2)*4],32);checks++;
}
console.log(JSON.stringify({passed:true,checks,seeds:9,scope:'Immutable previous policy differential: complete heap and formatting traces, signed bytes, clipping, alias visibility, cache identity, separate games and heap growth during capture formatting.'}));
