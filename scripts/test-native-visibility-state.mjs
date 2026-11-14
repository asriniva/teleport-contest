// Actual game visibility state, byte aliases and callback growth safety.
import assert from 'node:assert/strict';
import {runStandaloneProgram} from './run-standalone-program.mjs';
import {nativeStateFor} from '../js/nethack/native/state-bridge.js';
import fs from 'node:fs';
import {createStandaloneEnvironment} from '../js/nethack/environment.js';
import {enableVision} from '../js/nethack/vision.js';
import {CMemory} from '../js/c-runtime/heap.js';
let runtime,checks=0;const eq=(a,b,label)=>{assert.deepEqual(a,b,label);checks++;};
const result=runStandaloneProgram('.cache/full-original-c-v1/assets',{seed:1,keys:'  nl.',options:'OPTIONS=!news\n',observeRuntime:r=>{runtime=r;}});
eq(result.status.kind,'input-exhausted','actual gameplay reaches next input');
const env=runtime.environment,owner=nativeStateFor(env),ws=owner.visibilityState,{memory,ctypes}=env;
eq(memory.stableBuffer,true,'game uses a resizable JavaScript buffer');eq(Boolean(ws),true,'actual game owns native visibility');
const rows=ws.arrays.get('could_see');eq(rows.length,2,'two source buffers');
for(const plane of rows)for(const row of plane){eq(row instanceof Uint8Array,true,'native typed row');eq(row.length,80,'source row extent');}
const gv=env.requireGlobal('gv'),slot=ctypes.fieldAddress('struct instance_globals_v',gv,'viz_array');
const table=ws.rows(owner.nativeArena.pointer(slot));eq(Array.isArray(table),true,'native row references');
owner.enter();try{
 const row=table[0],before=row[1],oldLength=memory.buffer.byteLength,buffer=memory.buffer;
 for(const value of [0,255,257,-1]){ws.write(0,1,value);eq(ws.read(0,1),value&255,'byte narrowing');eq(memory.view.getUint8(row.address+1),value&255,'writes alias original bytes');}
 owner.boundary(()=>{memory.grow(oldLength+1);memory.view.setUint8(row.address+1,73);});
 eq(memory.buffer,buffer,'growth preserves buffer identity');eq(memory.buffer.byteLength>oldLength,true,'real growth occurred');eq(row[1],73,'held local row sees callback growth and byte mutation');row[1]=91;eq(memory.view.getUint8(row.address+1),91,'held row still writes live bytes');
 const other=rows.find(plane=>plane[0].address!==row.address)[0];const pointerAt=table.address,oldPointer=owner.nativeArena.pointer(pointerAt);
 owner.boundary(()=>owner.nativeArena.storePointer(pointerAt,other));eq(ws.rows(table)[0],other,'callback pointer rewrite refreshes native row table');
 owner.boundary(()=>owner.nativeArena.storePointer(pointerAt,oldPointer));eq(ws.rows(table)[0].address,row.address,'restored row reference');
 const previousActive=owner.nativeArena.pointer(slot),otherTable=ws.arrays.get('cs_rows1').address===previousActive?ws.arrays.get('cs_rows0'):ws.arrays.get('cs_rows1');
 owner.boundary(()=>owner.nativeArena.storePointer(slot,otherTable));eq(ws.read(0,1),ws.rows(otherTable)[0][1],'external active buffer switch');
 owner.boundary(()=>owner.nativeArena.storePointer(slot,previousActive));eq(ws.read(0,1),row[1],'active buffer restored after callback');
 const scalar=ws.element(row,1);eq(scalar.value,91,'native scalar reference reads row');ws.advance(scalar,1).value=259;eq(row[2],3,'advanced scalar narrows byte');row[1]=before;
 for(const name of ['cs_rmin0','cs_rmax0','colbump']){const values=ws.arrays.get(name),old=values[0];values[0]=-32769;eq(values[0],32767,'signed coordinate width '+name);eq(ws.coords(values),values,'stable coordinate identity '+name);values[0]=old;}
}finally{owner.leave();}
// Traverse the actual registered visibility callback path, including growth
// while recursive native scan locals still hold typed row references.
const visit=(grow)=>{const coordinates=[];let grew=false;const callback=env.functionPointer('visibility-growth-'+grow,'viip',(x,y,arg)=>{eq(owner.depth,0,'foreign visibility callback boundary');eq(arg,0,'opaque callback argument');coordinates.push([x,y]);if(grow&&!grew){const bytes=memory.buffer.byteLength;eq(memory.grow(bytes+1),true,'callback increases real game memory');eq(memory.buffer.byteLength>bytes,true,'callback capacity increased');grew=true;}});env.services.do_clear_area(owner.nativeRecords.record('struct you',env.requireGlobal('u')).ux,owner.nativeRecords.record('struct you',env.requireGlobal('u')).uy,4,callback,0);return coordinates;};
eq(visit(true),visit(false),'actual callback traversal order survives memory growth');
const legacy=new CMemory({initialBytes:64,maximumBytes:1024}),old=legacy.buffer;legacy.grow(128);eq(legacy.stableBuffer,false,'generic runtime keeps replacement mode');eq(legacy.buffer!==old,true,'generic buffer replacement remains');
const fallback=createStandaloneEnvironment({resizable:false}),layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json'));
fallback.enableDecl(layouts.decl);const compatibility=enableVision(fallback,layouts).context;
eq(compatibility.nativeVisibilityState,undefined,'replacement mode uses original descriptor adapter');
fallback.call('vision','vision_init');compatibility.viz_clear[0][1]=77;const held=compatibility.viz_clear[0];fallback.memory.grow(fallback.memory.buffer.byteLength+1);eq(held[1],77,'legacy descriptor row survives replacement growth');
console.log('PASS native visibility state '+checks+' checks: actual gameplay, direct rows, byte aliases, external pointer mutation and callback growth');
