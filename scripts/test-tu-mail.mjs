// First pass: actual EmC original C against imported JS with the same native
// dependency fixture. Native/macOS library differences remain a follow-up.
import assert from './native-test-assert.mjs';
import { resolve } from 'node:path';
import { pathToFileURL } from 'node:url';
import { callMail } from '../js/ported/mail-runtime.js';
import { C, R, T } from '../js/ported/c-runtime.js';
const directory = resolve(process.env.TELEPORT_MAIL_PROBE_DIR ?? '.cache/tu-probes');
const { default: referenceFactory } = await import(pathToFileURL(resolve(directory, process.env.TELEPORT_MAIL_PROBE_DIR ? 'reference.mjs' : 'mail-reference.mjs')));
const { default: hybridFactory } = await import(pathToFileURL(resolve(directory, process.env.TELEPORT_MAIL_PROBE_DIR ? 'hybrid.mjs' : 'mail-hybrid.mjs')));
const reference = await referenceFactory();
function text(m,p) { p=Number(p);if(!p)return null;let end=p;while(m.HEAPU8[end])end++;return Buffer.from(m.HEAPU8.slice(p,end)).toString('latin1'); }
const L={strings:{}};
for(let i=0;i<reference._probe_layout_count();i++)L[text(reference,reference._probe_layout_name(i))]=Number(reference._probe_layout_value(i));
for(let i=0;i<reference._probe_string_count();i++)L.strings[text(reference,reference._probe_string_name(i))]=text(reference,reference._probe_string_value(i));
const runtime={mail:(services,name,...args)=>callMail(services,L,name,...args)};
const modules=[reference,await hybridFactory({nethackPorted:runtime})];
const stacks=modules.map(m=>m._probe_stack());let comparisons=0;
function snapshot(m) { return { state:text(m,m._probe_snapshot()), trace:text(m,m._probe_trace()), stats:[3,4].map(i=>Array.from(m.HEAPU8.slice(Number(m._probe_pointer(i)),Number(m._probe_pointer(i))+L.statSize))) }; }
function check() { assert.deepEqual(snapshot(modules[1]),snapshot(modules[0]));assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);modules.forEach((m,i)=>assert.equal(m._probe_stack(),stacks[i]));comparisons++; }
function call(name,...args) { const result=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(result[1],result[0],name);check();return result[0]; }
function put(m,value) { if(value===null)return 0n;const bytes=Buffer.from(value,'latin1'),ptr=m._malloc(BigInt(bytes.length+1));m.HEAPU8.set(bytes,Number(ptr));m.HEAPU8[Number(ptr)+bytes.length]=0;return BigInt(ptr); }
function strings(name,values,...prefix) {modules.forEach(m=>{const pointers=values.map(value=>put(m,value));try{m['_probe_'+name](...prefix,...pointers);}finally{pointers.forEach(p=>{if(p)m._free(p);});}});check();}
function reset() {call('reset');}
function action(op,a=0,b=0) {return call('action',op,a,b);}
function trace() {return text(reference,reference._probe_trace());}
function state() {return text(reference,reference._probe_snapshot());}
function start() {call('stairs',0,5,5,1,-1);call('cell',5,5,20,3,-1);}
function info(typ=0,name=null,cmd=null) { // Source stores these pointers, so retain ownership through the call.
 const lists=modules.map(m=>['Hello fixture',name,cmd].map(value=>put(m,value)));
 modules.forEach((m,i)=>m._probe_info(typ,...lists[i]));
 return ()=>modules.forEach((m,i)=>lists[i].forEach(p=>{if(p)m._free(p);}));
}
// Every measured native layout is checked against the actual hybrid module.
for(const m of modules)for(let i=0;i<m._probe_layout_count();i++)assert.equal(Number(m._probe_layout_value(i)),L[text(m,m._probe_layout_name(i))]);
assert.equal(L.timeSize,8);assert.equal(L.stat_st_mtime_size,8);assert.equal(L.coord_x_size,2);
// Setup uses MAIL even if empty, otherwise the actual fixture uid/account name.
for(const mail of [null,'','/tmp/fixture mail','relative','\xffmail'])for(const debug of [0,1])for(const fail of [0,1]){
 reset();call('option',0,Number(mail!==null));if(mail!==null)strings('env',[mail],0);call('option',4,debug);call('option',2,fail);action(1);
 assert.match(trace(),mail===null?/uid;passwd:12345;/:/env:MAIL;/);if(debug)assert.match(trace(),/pline:mailbox=/);
 action(1);action(0);action(0);
}
reset();strings('env',['the_recorder_account'],2);action(1);assert.match(state(),/mail:\/usr\/mail\/the_recorder_account;/);
// Mutable native stat backing and signed64 fields remain live across checks.
for(const time of [0n,1n,9007199254740993n,-10n])for(const size of [0n,1n,9007199254740995n]){
 reset();call('option',0,1);call('stat',time,size);action(1);assert.match(state(),new RegExp('old:'+time+':'+size+';'));
 call('stat',time+1n,size);call('moves',100n);action(6);
}
reset();action(1);modules.forEach(m=>new DataView(m.HEAPU8.buffer).setBigInt64(Number(m._probe_pointer(3))+L.stat_st_mtime,9999n,true));call('stat',10000n,0n);action(6);assert.match(state(),/old:10000:0;/);
// Poll interval, swallowed/biff guards, stale and missing/empty mail cases.
for(const moves of [0n,49n,50n,51n,99n,100n,9007199254740993n])for(const biff of [0,1])for(const swallowed of [0,1]){
 reset();action(1);call('moves',moves);call('flags',biff,0);call('hero',10,10,swallowed,0);call('clear');action(6);
 if(moves<50n||!biff||swallowed)assert.equal(trace(),'');else assert.match(trace(),/stat:/);
}
reset();action(1);call('stat',2n,0n);action(6);assert.match(trace(),/stat:/);assert.doesNotMatch(trace(),/makemon:/);call('clear');call('moves',149n);action(6);assert.equal(trace(),'');call('moves',150n);action(6);assert.match(trace(),/stat:/);
reset();action(1);call('option',2,1);call('moves',100n);action(6);assert.match(state(),/new:0:0;/);
// Starting location: invisible/blind, telepathy, linked stairs, farthest row
// retry, no visible row, and enexto failure retain the original decisions.
for(const blind of [0n,1n])for(const telepathy of [0n,1n])for(const fail of [0,1]){
 reset();call('prop',L.BLINDED,blind,0n,0n);call('prop',L.TELEPAT,telepathy,0n,0n);call('option',7,fail);start();action(2);
}
reset();assert.equal(action(2),0);
reset();call('stairs',0,5,5,2,1);call('stairs',1,7,7,1,-1);call('cell',5,5,20,3,-1);call('cell',7,7,20,3,-1);assert.equal(action(2),1);assert.match(state(),/coord:7:7:/);
for(const mode of [0,1,2]){
 reset();call('row',2,2,30);call('row',15,3,60);for(const [x,y]of [[3,2],[31,2],[4,15],[61,15]])call('cell',x,y,20,mode,-1);action(2);
}
// Stop location selection includes equal-distance RNG, fallback and no result.
for(const origin of [[1,0],[70,20],[10,10],[9,10]])for(const fallback of [0,1])for(const fail of [0,1]){
 reset();call('coord',1,...origin);call('option',6,fallback);call('option',7,fail);call('option',5,1);action(3);
}
reset();call('coord',0,15,12);call('option',5,1);action(9);
// Movement, displacement and worm-segment restoration use real native grid
// cells. Same coordinates with a different monster identity remain distinct.
for(const deaf of [0,1])for(const displaced of [false,true])for(const worm of [false,true]){
 reset();call('hero',5,5,0,deaf);call('mon',0,2,5);call('cell',2,5,20,3,0);
 if(displaced){call('mon',1,...(worm?[20,15]:[3,5]));call('cell',3,5,20,3,1);}call('option',5,1);assert.equal(action(4,7,5),1);
}
for(const deaf of [0,1]){
 reset();call('hero',10,10,0,deaf);call('mon',0,3,3);call('mon',1,4,4);call('cell',3,3,20,3,0);call('cell',4,4,20,3,1);assert.equal(action(4,4,4),0);assert.match(trace(),deaf?/Never mind/:/too crowded/);
}
reset();call('mon',0,3,3);for(let x=2;x<=4;x++)for(let y=2;y<=4;y++)if(x!==3||y!==3)call('cell',x,y,0,0,-1);assert.equal(action(4,7,7),1);assert.match(state(),/mons:3:3,/);
// Delivery messages, optional naming/response bytes, failed daemon creation,
// source give_up/go_back paths, hearing changes and native object transfer.
for(const typ of [L.MSG_OTHER,L.MSG_MAIL,L.MSG_CALL])for(const deaf of [0,1])for(const names of [false,true])for(const fail of [0,1]){
 reset();start();call('hero',10,10,0,deaf);call('option',8,fail);const release=info(typ,names?'From Recorder':null,names?'REPLY':null);action(5);release();
 if(fail&&typ===L.MSG_OTHER)assert.match(trace(),/Hark!/);
 if(!fail&&typ!==L.MSG_OTHER)assert.match(trace(),/hold:1:Oops!/);
}
for(const occupied of [1,2]){
 reset();start();call('option',9,occupied);const done=info(occupied===1?L.MSG_OTHER:L.MSG_MAIL);action(5);done();
 if(occupied===1){assert.match(trace(),/too crowded/);assert.match(trace(),/Hark!/);}else assert.match(trace(),/gone:0:0;/);
}
reset();const release=info(L.MSG_OTHER);action(5);release();assert.match(trace(),/Hark!/);
reset();start();call('option',0,1);action(1);call('stat',2n,1n);action(6);assert.match(trace(),/I have some mail for you/);assert.match(trace(),/mksobj:/);
// Reading is controlled at the child/exec boundary: never launch a reader.
for(const reader of [null,'','/fixture/mail reader'])for(const child of [0,1])for(const fuzzer of [0,1]){
 reset();call('option',1,Number(reader!==null));if(reader!==null)strings('env',[reader],1);call('option',3,child);call('flags',1,fuzzer);const result=action(8);
 if(fuzzer)assert.equal(trace(),'');else if(child){assert.equal(result,-1);assert.match(trace(),/execl:.*:1:1;.*terminate:1;/);}else assert.match(trace(),/child:1;/);
}
// Native dependencies reenter JS and grow actual memory while source locals,
// stat output and grid pointers remain live. No cached DataView may survive.
for(const stage of [1,2,3,4,5,6,7,8,9,10,11,12,13,14]){
 reset();start();call('option',4,1);call('option',10,stage);call('option',11,stage);
 const before=modules.map(m=>m.HEAPU8.buffer.byteLength);const release=info(L.MSG_MAIL,'Fixture','REPLY');
 if(stage===7)call('prop',L.BLINDED,1n,0n,0n);
 if(stage<=5)action(1);else if(stage===11||stage===12){call('option',3,1);action(8);}else action(5);
 release();assert.match(trace(),new RegExp('reenter:'+stage+';'));assert.match(trace(),new RegExp('grow:'+stage+';'));
 modules.forEach((m,i)=>assert.ok(m.HEAPU8.buffer.byteLength>before[i]));
}
reset();start();call('option',12,6);const release2=info(L.MSG_MAIL);action(5);release2();assert.match(trace(),/deaf:1;/);
// One runtime, two actual Modules: mail/stat/free counters and pointer storage
// remain independent; operations on the second cannot mutate the first.
reset();call('option',0,1);action(1);const saved=snapshot(modules[1]);const independent=await hybridFactory({nethackPorted:runtime});independent._probe_reset();independent._probe_action(1,0,0);assert.deepEqual(snapshot(modules[1]),saved);
console.log(`MAIL: ${comparisons} Emscripten-C/hybrid state, stat bytes, movement, delivery, controlled reader, callbacks and growth comparisons checked.`);
