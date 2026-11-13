import './pure-js-probes/deny-wasm.mjs';
import {createProbe,createReference,loadFixture,fixtureImports} from './pure-js-fixtures/load.mjs';
// Configured PLINE first-pass memory64 differential. Native and actual-game
// gates are separate and remain pending until the integrating owner runs them.
import assert from './native-test-assert.mjs';
import {resolve} from 'node:path';
import {pathToFileURL} from 'node:url';
import {createPlineBridge} from '../js/nethack/bindings/pline.js';
import {C} from '../js/c-runtime/context.js';
const directory=resolve(process.env.PLINE_PROBE_DIR??'.cache/tu-probes');
const referenceFactory=(await loadFixture("pline",pathToFileURL(resolve(directory,'pline-reference.mjs')))).default;
const hybridFactory=(await loadFixture("pline",pathToFileURL(resolve(directory,'pline-hybrid.mjs')))).default;
const text=(m,at)=>{at=Number(at);let end=at;while(m.HEAPU8[end])end++;return Buffer.from(m.HEAPU8.subarray(at,end)).toString('latin1');};
const layouts=m=>Object.fromEntries(Array.from({length:m._probe_layout_count()},(_,i)=>[text(m,m._probe_layout_name(i)),Number(m._probe_layout_value(i))]));
let comparisons=0,scenario='initial',sharedBridge;
async function pair(){const reference=await referenceFactory(),L=layouts(reference);const hybrid=await hybridFactory({nethackPorted:{pline:(sharedBridge??=createPlineBridge(L,{nativeExecution:process.env.NATIVE_PLINE_FIXTURE==='1'}))}});assert.deepEqual(layouts(hybrid),L);comparisons++;const modules=[reference,hybrid];modules.forEach(m=>m._probe_reset());return modules;}
let modules=await pair();
function compare(){const states=modules.map(m=>({state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace())}));assert.deepEqual(states[1],states[0],scenario);assert.equal(C,undefined);comparisons++;}
function call(name,...args){const stacks=modules.map(m=>m._probe_stack());const values=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(values[1],values[0]);modules.forEach((m,i)=>assert.equal(m._probe_stack(),stacks[i],scenario+' stack'));compare();}
function input(value,argument='C:\\path/to/source.c'){for(const m of modules){for(const [at,source]of[[m._probe_input(),value],[m._probe_argument(),argument]]){const bytes=typeof source==='string'?Buffer.from(source):source;m.HEAPU8.set(bytes,Number(at));m.HEAPU8[Number(at)+bytes.length]=0;}}}
const field=(key,value)=>call('field',key,value),option=(key,value)=>call('option',key,value),message=(fn,pattern=1)=>call('message',fn,pattern),direct=action=>call('direct',action);
// Every public variadic wrapper receives the real compiler-created packet,
// including mixed ints, 64-bit long beyond53 bits, float, and width/precision.
for(const fn of[0,1,2,3,4,5,6,7,8,9,10,11,12,13])for(const pattern of[0,1,2,3]){scenario=`wrapper ${fn}/${pattern}`;input('abcXYZ');message(fn,pattern);}
for(const fn of[14,15,16,17,18,19]){scenario='other public '+fn;input('public path');option(10,fn===17?12:2);option(11,14);message(fn);}
scenario='direct direction';option(10,8);direct(7);for(const value of[-32769,-1,0,32767,32768]){option(10,value);option(11,-value);direct(8);}
// Literal%s and no-substitution paths must preserve embedded '%' data.
for(const fn of[0,1,10]){scenario='embedded percent';input('100% literal %s');message(fn,1);}
for(const length of[0,1,249,250,251,252,253,254,255,256,257,258,260,300,1000,1270])for(const fn of[0,10]){scenario=`truncate ${fn}/${length}`;input('z'.repeat(Math.max(0,length-3))+'END'.slice(0,Math.min(length,3)));message(fn,1);}
for(const fn of[0,1,10]){scenario='raw non-ASCII bytes';input(Buffer.from([0x80,0xff,0xc3,0xa9,0x25,0x41]));message(fn,1);}
// Ring wrap, unknown-command exclusion and shrink/reuse/grow allocation paths.
scenario='history ring';for(let i=0;i<105;i++){input('history'+i+'x'.repeat(i%20));direct(0);}input('Unknown command abc');direct(0);direct(1);direct(1);
scenario='You buffer';for(const length of[2,12,3,80,70,200,1]){input('x'.repeat(length));message(1);}direct(2);direct(2);
for(const shown of[0,1])for(const hidden of[0,1])for(const msgtype of[0,1,2,3])for(const flags of[0,1,2,4,8,12,64,0xffffffff]){scenario=`suppression ${shown}/${hidden}/${msgtype}/${flags}`;field(0,shown);field(1,hidden);option(0,msgtype);option(10,flags);field(17,314159);input('same message');message(17);message(17);}
field(0,1);field(1,0);option(0,0);
for(const capabilities of[0n,0x4000n,0x8000n,0xc000n,(1n<<63n)|0xc000n]){scenario='unsigned64 window capabilities';call('caps',capabilities);option(10,12);input('capability attrs');message(17);}
for(const state of[2,3]){scenario='early return '+state;field(state,1);input('ignored');field(5,13);field(6,14);message(0);field(state,0);}
for(const fn of[14,15,16])for(const accessible of[0,1]){scenario='location '+fn+'/'+accessible;field(4,accessible);option(10,fn===14?8:1);option(11,19);input('located % message');message(fn);}
field(4,0);
for(const unaware of[0,1])for(const deaf of[0,1])for(const underwater of[0,1])for(const blind of[0,1])for(const acoustics of[0,1]){
 scenario='sense prefixes';field(9,unaware?-1:0);option(8,unaware);field(12,deaf);field(10,underwater);field(11,blind);field(8,acoustics);input('a sound');message(3);message(7);message(8);
}
field(9,0);field(12,0);field(11,0);field(10,0);field(8,1);
scenario='UI recursive message';option(5,1);input('outer UI');message(0);option(5,0);
scenario='vision recursive message';option(4,1);field(7,1);input('outer vision');message(0);option(4,0);
scenario='heap growth';const sizes=modules.map(m=>m.HEAPU8.byteLength);option(6,1);input('grow callback');message(0);modules.forEach((m,i)=>assert.ok(m.HEAPU8.byteLength>sizes[i]));
scenario='gamelog64';input('chronicle\tentry');direct(3);message(18);
for(const beyond of[0,1]){scenario='early raw double count';field(13,beyond);input('raw count');message(10);}
for(const sanity of[0,1])for(const saving of[0,1])for(const support of[0,1])for(const report of[0,1]){scenario='impossible feedback';field(15,sanity);field(14,saving);field(19,support);field(20,report);option(3,report);input('impossible detail');message(11,1);}
// The handler's use flag persists after fork failure. Fresh modules give each
// exit path its true initial private state without inventing reset behavior.
for(const fork of[41,-1]){modules=await pair();scenario='handler '+fork;field(18,1);option(1,fork);input('handler payload');message(0);message(10);message(0);}
modules=await pair();scenario='handler child failure';field(18,1);option(1,0);input('child payload');
const child=modules.map(m=>{assert.throws(()=>m._probe_message(0,1),/PLINE fixture exit 1/);return{state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace())};});assert.deepEqual(child[1],child[0]);assert.equal(C,undefined);comparisons++;
for(const fn of[0,1]){modules=await pair();scenario='format overflow panic';input('x'.repeat(1400));const states=modules.map(m=>{assert.throws(()=>m._probe_message(fn,1),/PLINE fixture exit 2/);return text(m,m._probe_trace());});assert.equal(states[1],states[0]);assert.equal(C,undefined);comparisons++;}
console.log(`PLINE: ${comparisons} configured original-C/pure-JS comparisons passed; ${process.env.NATIVE_PLINE_FIXTURE==='1'?'native source execution':'legacy execution'}; actual gameplay verified separately.`);
