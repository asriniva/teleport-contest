// Production native glyph values: widths, aliasing, lifetime and foreign windows.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import {runStandaloneProgram} from './run-standalone-program.mjs';
import {nativeStateFor} from '../js/nethack/native/state-bridge.js';
import {createNativeValueRecords} from '../js/nethack/native/value-records.js';
import {createNativeWindowCallbacks} from '../js/nethack/native/window-callbacks.js';
let e;runStandaloneProgram('.cache/full-original-c-v1/assets',{keys:'',observeRuntime:r=>e=r.environment});
const owner=nativeStateFor(e),t=e.transport,m=e.memory,views=owner.nativeRecords;
const values=createNativeValueRecords({...e,nativeRecords:views},t.stackAlloc);
let checks=0;const eq=(a,b)=>{assert.deepEqual(a,b);checks++;};
const mark=t.stackSave(),before=m.live.size,v=values.local('struct glyphinfo');
eq(m.live.size,before);eq(v.read('glyph'),0);
for(const n of [0n,1n,-1n,0x7fffffffffffffffn,-0x8000000000000000n,0x100000001n]){
 v.write('glyph',n);eq(v.read('glyph'),Number(BigInt.asIntN(32,n)));
 v.write('framecolor',n);eq(v.read('framecolor'),Number(BigInt.asUintN(32,n)));
 const gm=v.field('gm');gm.write('tileidx',n);eq(gm.read('tileidx'),Number(BigInt.asIntN(16,n)));
 gm.write('color256idx',n);eq(gm.read('color256idx'),Number(BigInt.asUintN(16,n)));
 gm.field('sym').write('color',n);eq(gm.field('sym').read('color'),Number(BigInt.asIntN(32,n)));
}
eq(m.live.size,before);
const frame=()=>v.field('framecolor').value;v.write('framecolor',123);eq(frame(),123);v.field('framecolor').value=456;eq(v.read('framecolor'),456);
const nested=t.stackSave(),at=v.address;eq(m.live.size,before+1);t.stackRestore(nested);
eq(v.address,at);const physical=views.record('struct glyphinfo',at);
physical.glyph=123;eq(v.read('glyph'),123);v.write('glyph',456);eq(physical.glyph,456);
const other=values.local('struct glyphinfo');values.copy(other,at,e.ctypes.size('struct glyphinfo'));eq(other.read('glyph'),456);
other.field('gm').field('sym').write('color',9);eq(other.field('gm').field('sym').read('color'),9);
values.copy(at,other,e.ctypes.size('struct glyphinfo'));eq(physical.gm.sym.color,9);
const unicode=views.record('struct unicode_representation',t.stackAlloc(16));unicode.utf32ch=0x2603;unicode.utf8str=t.stackAlloc(4);m.HEAPU8.set([0xe2,0x98,0x83,0],unicode.utf8str);other.field('gm').write('u',unicode);values.copy(v,other,e.ctypes.size('struct glyphinfo'));eq(v.field('gm').read('u'),unicode);eq(physical.gm.u,unicode);eq(physical.gm.u.utf32ch,0x2603);
assert.throws(()=>values.copy(other,v,1),/extent/);checks++;
assert.throws(()=>v.read('not_a_field'),/Unknown/);checks++;
const callbacks=createNativeWindowCallbacks(e,owner),signature='viiipp';let invoked=0;
// A real foreign function token must receive C addresses, never JS records.
const token=e.functions.functionPointer((win,x,y,fg,bg)=>{invoked++;eq([win,x,y],[1,2,3]);eq(typeof fg,'number');eq(views.record('struct glyphinfo',fg).glyph,456);views.record('struct glyphinfo',bg).glyph=789;},signature);
callbacks.invokeCaptured('win_print_glyph',signature,token,1,2,3,v,other);
eq(invoked,1);eq(other.read('glyph'),789);
const oldBuffer=m.HEAPU8.buffer;m.grow(m.HEAPU8.byteLength+65536);assert.notEqual(m.HEAPU8.buffer,oldBuffer);checks++;
eq(v.read('glyph'),456);eq(other.read('glyph'),789);
t.stackRestore(mark);eq(m.live.has(at),false);assert.throws(()=>v.read('glyph'),/Expired/);checks++;assert.throws(()=>other.address,/Expired/);checks++;
fs.mkdirSync('.cache/native-display-values',{recursive:true});fs.writeFileSync('.cache/native-display-values/values.json',JSON.stringify({checks,scope:'Source-initialized production runtime; exact integer widths including extreme BigInts, nested copies/aliasing, zero C allocations before address acquisition, declaring-frame deferred lifetime, foreign win_print_glyph token materialization and writeback, memory growth and expired references.'},null,2));
console.log('PASS native display values '+checks);
