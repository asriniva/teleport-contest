// Exercise the actual production owner, live ABI readers and native filtering.
import assert from 'node:assert/strict';import fs from 'node:fs';import {parse} from 'acorn';
import {createScalarAdapter,exactAddress} from '../js/c-runtime/adapter-factories.js';
import {runStandaloneProgram} from './run-standalone-program.mjs';
import {nativeStateFor} from '../js/nethack/native/state-bridge.js';
import {createNativePline} from '../js/nethack/native/pline.js';
import * as sourceOptions from '../js/ported/options.js';import {withCEnvironment} from '../js/c-runtime/context.js';
let runtime,checks=0;const eq=(a,b,label)=>{assert.deepEqual(a,b,label);checks++;};
const result=runStandaloneProgram('.cache/full-original-c-v1/assets',{keys:'  nl.Fyy ',options:'OPTIONS=!news\n',observeRuntime:r=>{runtime=r;}});eq(result.status.kind,'input-exhausted','actual walk, wait and attack');
const env=runtime.environment,{memory,ctypes,transport}=env,owner=nativeStateFor(env),layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),history=owner.messageHistory;
eq(Boolean(history),true,'actual game owns native history');
const messages=env.start('messages'),ctx=messages.environment;
// Source-owned free leaves the ring logically empty and retains its arena.
messages.namespace.dumplogfreemessages();eq(history.rows().every(x=>x===0),true,'source frees all messages');
const input=memory.malloc(layouts.pline.BIGBUFSZ),insert=line=>{memory.writeString(input,line);messages.namespace.dumplogmsg(input);};
const initialLive=memory.live.size,initialBytes=[...memory.live.values()].reduce((n,a)=>n+a.capacity,0);
let allocationsDuringHistory=0;const malloc=memory.malloc;memory.malloc=function(size){allocationsDuringHistory++;return malloc.call(this,size);};
try{for(let i=0;i<3*history.count;i++){
 const line='history '+i+' '+String.fromCharCode(0x80,0xff)+'x'.repeat(i%70);insert(line);
 const index=(ctx.gs.saved_pline_index+history.count-1)%history.count,pointer=memory.view.getBigUint64(history.pointerAt+index*8,true);
 eq(memory.readString(Number(pointer)),line,'original pointer slot sees native row');eq(history.rows()[index],Number(pointer),'native ring agrees with raw pointer');
 eq(memory.live.size,initialLive,'no C heap allocation while ring grows/reuses/wraps');
}
}finally{memory.malloc=malloc;}eq(allocationsDuringHistory,0,'zero actual C malloc calls during native ring updates');
eq([...memory.live.values()].reduce((n,a)=>n+a.capacity,0),initialBytes,'ring preserves byte allocation budget');
// Pointer-backed copies must not manufacture a JS string in the middle.
memory.writeString(input,'direct bytes');const oldReadString=memory.readString;let direct;
try{memory.readString=()=>{throw Error('unexpected history decode');};direct=history.copy(0,input);}finally{memory.readString=oldReadString;}
eq(memory.readString(direct),'direct bytes','native pointer copy avoids decoding');
for(const value of ['',String.fromCharCode(128,255),'embedded\0tail','x'.repeat(history.capacity-1)]){const p=history.copy(0,value);eq(memory.readString(p),value.split('\0')[0],'native JS string encoding');}
assert.throws(()=>history.copy(0,'bad\u0100'),/byte|Latin|character/i);checks++;
assert.throws(()=>history.copy(0,'ok\0bad\u0100'),/byte|Latin|character/i);checks++;
const index=ctx.gs.saved_pline_index;insert('Unknown command xyz');eq(ctx.gs.saved_pline_index,index,'unknown command excluded');
const long='oversize '+ 'z'.repeat(2*history.capacity);insert(long);eq(memory.live.size,initialLive+1,'oversize history owns real allocation');
const last=(ctx.gs.saved_pline_index+history.count-1)%history.count,at=Number(memory.view.getBigUint64(history.pointerAt+last*8,true));eq(memory.readString(at),long,'full direct oversized message retained');eq(memory.readString(Number(env.services.get_saved_pline(0))),long,'original report policy reads native history');
messages.namespace.dumplogfreemessages();eq(memory.live.size,initialLive,'source frees oversize storage');eq(history.rows().every(x=>x===0),true,'native and raw ring empty after release');
// Mixed provider storage and byte mutations remain visible at native entries.
const foreign=memory.cstring('foreign row');owner.boundary(()=>owner.nativeArena.storePointer(history.pointerAt,foreign));owner.enter();try{eq(history.rows()[0],foreign,'foreign pointer replacement');}finally{owner.leave();}
messages.namespace.dumplogfreemessages();eq(memory.live.has(foreign),false,'foreign row freed by original allocator');
insert('growth row');const buffer=memory.buffer,bytes=buffer.byteLength;owner.boundary(()=>memory.grow(bytes+1));eq(memory.buffer.byteLength>bytes,true,'real growth');eq(memory.buffer,buffer,'resizable arena stable');eq(memory.readString(history.rows()[0]),'growth row','history live after growth');
// Compare native filtering with the entire original OPTIONS function while the
// actual option owner supplies live records, regex identities and signed types.
const {env:sourceScalars}=createScalarAdapter({heap:()=>memory.HEAPU8},{},{schema:{},globals:[]},value=>exactAddress(value,'OPTIONS pointer exceeds exact address range',true),{profile:'declared-enum',errors:['','','']});
const options={nativeMessageFilter:owner.functions.get('msgtype_type')},oracleContext={ptr:value=>exactAddress(value,'OPTIONS pointer exceeds exact address range',true),i8:sourceScalars.i8,i32:sourceScalars.i32,gp:env.requireGlobal('gp'),regex_match:(...args)=>env.services.regex_match(...args),field:(at,type,key)=>({get value(){const field=ctypes.record(type).fields[key],scalar=field.ctype.replace(new RegExp('\\s+'+key+'$'),'');return ctypes.getField(type,at,key,scalar);}})},gp=owner.nativeRecords.record('struct instance_globals_p',env.requireGlobal('gp')),oldHead=gp.plinemsg_types,oldRegex=env.services.regex_match;
const allocations=[];let events=[];
try{
 const nodes=[-3,2,0].map((type,i)=>{const p=memory.calloc(1,ctypes.size('struct plinemsg_type'));allocations.push(p);const n=owner.nativeRecords.record('struct plinemsg_type',p);n.msgtype=type;n.regex=0;return n;});nodes.forEach((n,i)=>{n.next=nodes[i+1]??0;});gp.plinemsg_types=nodes[0];
 for(const matched of [-1,0,1,2])for(const norepeat of [-1,0,1,256,257]){
  const line=env.services.literal('filter target');let calls=0;
  env.services.regex_match=()=>{events.push(calls);return calls++===matched?1:0;};
  events=[];calls=0;const expected=withCEnvironment(oracleContext,sourceOptions.msgtype_type,line,norepeat),expectedEvents=[...events];
  events=[];calls=0;eq(options.nativeMessageFilter(line,norepeat),expected,'native source filter result');eq(events,expectedEvents,'ordered regex calls including negative types');
 }
 for(const value of [0,1,256,257,-256,NaN,Infinity]){
  const line=env.services.literal('provider result');env.services.regex_match=()=>value;
  eq(options.nativeMessageFilter(line,1),withCEnvironment(oracleContext,sourceOptions.msgtype_type,line,1),'foreign regex result remains unchanged '+value);
 }
 const line=env.services.literal('mutating provider');const compareMutation=fn=>{nodes[0].next=nodes[1];let calls=0;env.services.regex_match=()=>{calls++;nodes[0].next=0;return 0;};const result=fn();return [result,calls];};
 eq(compareMutation(()=>options.nativeMessageFilter(line,1)),compareMutation(()=>withCEnvironment(oracleContext,sourceOptions.msgtype_type,line,1)),'callback mutation precedes next link read');
 // Real compiler-compatible regex objects use the existing source provider.
 env.services.regex_match=oldRegex;const regex=env.services.regex_init();
 try{eq(env.services.regex_compile(env.services.literal('^ordered [0-9]+$'),regex),1,'actual regex compile');nodes[0].regex=regex;nodes[0].next=0;gp.plinemsg_types=nodes[0];
  for(const text of ['ordered 17','ordered x','unmatched','ordered 0'])for(const norepeat of [0,1]){const line=env.services.literal(text);eq(options.nativeMessageFilter(line,norepeat),withCEnvironment(oracleContext,sourceOptions.msgtype_type,line,norepeat),'actual source regex filter '+text);}
 }finally{env.services.regex_free(regex);nodes[0].regex=0;}
 gp.plinemsg_types=0;
 const observe=fn=>{try{return {value:fn()};}catch(error){return {error:[error.name,error.message]};}};
 for(const msg of [0,-1,0n,-1n,Number.MAX_SAFE_INTEGER,BigInt(Number.MAX_SAFE_INTEGER)+2n,null,undefined,NaN,Infinity,'18','invalid'])for(const flag of [-257,-1,0,1,256,257,1.75,NaN,undefined,null,4294967297,2n**80n+1n])eq(observe(()=>options.nativeMessageFilter(msg,flag)),observe(()=>withCEnvironment(oracleContext,sourceOptions.msgtype_type,msg,flag)),'public pointer/boolean value and error coercion');
 gp.plinemsg_types=0;env.services.regex_match=()=>{throw Error('empty filter must not inspect line or regex');};eq(options.nativeMessageFilter.nativeValuesEntry('native JS text',1),1,'empty native list accepts native string');
}finally{gp.plinemsg_types=oldHead;env.services.regex_match=oldRegex;for(const p of allocations)memory.free(p);}
// The complete native filter must invert to the original source AST.
const parseOptions={ecmaVersion:'latest',sourceType:'module'},original=parse(fs.readFileSync('js/ported/options.js','utf8'),parseOptions).body.find(n=>n.declaration?.id?.name==='msgtype_type').declaration,native=parse(fs.readFileSync('js/nethack/native/message-filter.js','utf8'),parseOptions).body[0].declaration.body.body[0];
const expression=text=>parse('const value='+text,parseOptions).body[0].declarations[0].init;let inversions=0;
function clean(node){if(Array.isArray(node))return node.map(clean);if(!node||typeof node!=='object')return node;
 if(node.type==='CallExpression'&&node.callee?.object?.name==='C'&&node.callee.property?.name==='messageTypes'){inversions++;return clean(expression('C.field(C.gp,"instance_globals_p","plinemsg_types").value'));}
 if(node.type==='MemberExpression'&&node.object?.name==='tmp'&&['regex','msgtype','next'].includes(node.property?.name)){inversions++;return clean(expression('C.field(tmp,"plinemsg_type",'+JSON.stringify(node.property.name)+').value'));}
 return Object.fromEntries(Object.entries(node).filter(([key])=>!['start','end','raw'].includes(key)).map(([key,value])=>[key,clean(value)]));
}
eq(clean(native),clean(original),'entire source filter policy AST after inverse field lowering');eq(inversions,4,'exactly four native field operations');
// An actual replaced window callback must leave native scope and invalidate
// cached pointer references before native code resumes.
const win=ctypes.fieldAddress('struct window_procs',env.requireGlobal('windowprocs'),'win_raw_print'),oldWindow=owner.nativeArena.pointer(win),external=memory.cstring('callback row');
const callback=env.functionPointer('native-history-window-alias','vp',()=>{eq(owner.depth,0,'foreign window callback runs outside native scope');owner.nativeArena.storePointer(history.pointerAt+8,external);});
owner.enter();try{history.rows();owner.nativeArena.storePointer(win,callback);env.nativeWindowCallbacks.invoke('win_raw_print','vp',input);eq(history.rows()[1],external,'window callback updates native history before return');eq(owner.depth,1,'native caller scope restored');}finally{owner.nativeArena.storePointer(win,oldWindow);owner.leave();}
const exceptional=memory.cstring('exception callback row'),throwing=env.functionPointer('native-history-window-exception','vp',()=>{eq(owner.depth,0,'throwing callback is outside native scope');owner.nativeArena.storePointer(history.pointerAt+16,exceptional);throw Error('expected foreign window failure');});
owner.enter();try{history.rows();owner.nativeArena.storePointer(win,throwing);assert.throws(()=>env.nativeWindowCallbacks.invoke('win_raw_print','vp',input),/expected foreign window failure/);checks++;eq(owner.depth,1,'exception restores native caller scope');eq(history.rows()[2],exceptional,'exception invalidates pointer reference cache');}finally{owner.nativeArena.storePointer(win,oldWindow);owner.leave();}
messages.namespace.dumplogfreemessages();memory.free(input);
// The chronicle stores the original text. The external log substitutes tabs
// and truncates only if a tab occurs within the substitution buffer.
const bufferSize=layouts.pline.BUFSZ;
const beforeBoundary='x'.repeat(bufferSize-2);
const beyondBoundary=beforeBoundary+'x\ttail';
const chronicle=[];
let externalLog;
const {livelog_printf}=createNativePline({
 BUFSZ:bufferSize,
 svm:{moves:7n},
 chronicle,
 formatChronicle:text=>text,
 messageText:text=>text.split('\0',1)[0],
 livelog_add:(flags,text)=>{externalLog={flags,text};},
});
for(const [input,expected] of [[beforeBoundary+'\ttail',beforeBoundary+'_'],[beyondBoundary,beyondBoundary],['a\tb\tc','a_b_c'],['x\0\t','x'],['y'.repeat(bufferSize*3),'y'.repeat(bufferSize*2-1)]]){
 livelog_printf(1n,input);
 eq(externalLog,{flags:1n,text:expected},'external log substitution preserves the legacy buffer limit');
 eq(chronicle.at(-1),{flags:1n,turn:7n,text:input.slice(0,bufferSize*2-1).split('\0',1)[0]},'chronicle stores the unsubstituted message');
}
console.log('PASS native message state '+checks+' checks: actual gameplay, ring reuse/wrap, zero normal history allocations, raw readers, overflow release, foreign rows, growth and ordered signed filtering');
