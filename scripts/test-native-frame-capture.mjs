import fs from 'node:fs';import assert from 'node:assert/strict';
import {CMemory} from '../js/c-runtime/heap.js';import {createCStdlib} from '../js/c-runtime/stdlib.js';
import {createNativeTermcap} from '../js/nethack/native/termcap.js';
import {serializeNativeFrame,createNativeFrameCapture} from '../js/nethack/native/frame-capture.js';
import {encodeRecorderScreen} from '../js/wasm-replay-support.js';
let checks=0,formats=0,frames=0;const memory=new CMemory({initialBytes:262144,maximumBytes:1048576}),base=memory.calloc(1,7680),out=memory.malloc(160000),libc=createCStdlib(memory);
const views=()=>({bytes:new Uint8Array(memory.buffer,base,7680),signed:new Int8Array(memory.buffer,base,7680),heap8:memory.HEAP8});
const C={nomux_out:out,nomuxScreenViews:views,int:v=>Number(v)|0,charPointer:Number,sprintf:(...args)=>{formats++;return libc.sprintf(...args);}};
const source=createNativeTermcap(C);
function compare(label){frames++;const native=serializeNativeFrame(views().bytes),pointer=source.nomux_capture_screen(),original=memory.readString(pointer);assert.equal(native,original,label+' exact C byte serialization');checks++;assert.equal(encodeRecorderScreen(native),encodeRecorderScreen(original),label+' recording codec');checks++;}
compare('all zero');
const fill=()=>{const b=views().bytes;for(let i=0;i<1920;i++){b[i*4]=32;b[i*4+1]=7;b[i*4+2]=b[i*4+3]=0;}};
fill();compare('all default spaces');
for(const field of [0,1,2,3]){fill();const b=views().bytes;for(let i=0;i<1920;i++){b[i*4]=65+i%26;b[i*4+field]=i%256;}compare('all byte values in cell field '+field);}
// Exhaustive adjacent attribute pairs cover every low-bit SGR transition,
// including high bits which only affect the source end-of-line reset.
for(let group=0;group<69;group++){fill();const b=views().bytes;for(let i=0;i<1920;i++){const n=group*1920+i;b[i*4]=(n%5===0)?32:65;b[i*4+1]=n%17;const pair=Math.floor(n/2)%65536;b[i*4+2]=(i%2)?pair>>>8:pair&255;b[i*4+3]=n%3===0?1:0;}compare('attribute transition group '+group);}
let seed=0x12345678;const random=()=>seed=(Math.imul(seed,1664525)+1013904223)>>>0;
for(let sample=0;sample<8;sample++){const b=views().bytes;for(let i=0;i<b.length;i++)b[i]=random()>>>24;compare('deterministic mixed frame '+sample);}
const old=memory.buffer;memory.grow(old.byteLength+1);assert.notEqual(memory.buffer,old);checks++;compare('replacement backing buffer');
const events=[],captured=[];let kind='input';fill();views().bytes[0]=88;
const context={NULL:0,nomuxScreenViews:()=>{events.push('snapshot');return views();},fflush:()=>{events.push('flush');kind='anim';views().bytes[0]=89;}},namespace={nomux_get_cursor:(x,y)=>{events.push('cursor');x.value=17;y.value=9;}},services={nativeMarkerKind:()=>{events.push('kind');return kind;},nativeFrameCapture:(...args)=>{events.push('sink');captured.push(args);}};
const expected=serializeNativeFrame(views().bytes),capture=createNativeFrameCapture(context,namespace,services);capture(123);
assert.deepEqual(events,['snapshot','cursor','flush','kind','sink']);checks++;assert.deepEqual(captured[0],[expected,17,9,true]);checks++;
assert.throws(()=>serializeNativeFrame(new Uint8Array(7)),/dimensions/);checks++;
const evidence={passed:true,checks,frames,sourceFormattingCalls:formats,scope:'Exact original serializer body (separately AST verified) versus native serializer: all cell-byte values, default/trailing cells, color/attribute/DEC transitions, deterministic dense frames, control/high bytes, buffer replacement, unchanged codec, snapshot/cursor/flush/classification/sink order and native cursor values. Fixtures modify only component shadow cells, not gameplay/RNG state. Full original-C gameplay and recordings are separate.'};
fs.mkdirSync('.cache/native-frame-capture',{recursive:true});fs.writeFileSync('.cache/native-frame-capture/evidence.json',JSON.stringify(evidence,null,2));console.log(JSON.stringify(evidence));
