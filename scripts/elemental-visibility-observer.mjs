import {layoutSourceSha} from './nethack-layout.mjs';
// Read-only diagnostic: sealed original DWARF locations and measured shared fields.
import fs from 'node:fs';import path from 'node:path';import crypto from 'node:crypto';import assert from 'node:assert/strict';import{execFileSync}from'node:child_process';
const records=JSON.parse(fs.readFileSync(new URL('../js/nethack/records.json',import.meta.url))).records;
export function createElementalVisibilityObserver(directory){
 const wasm=path.resolve(directory,'out/game.wasm'),receipt=JSON.parse(fs.readFileSync(path.resolve(directory,'receipt.json'))),hash=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex'),tool=path.resolve('.cache/emsdk/upstream/bin/llvm-dwarfdump');assert.equal(layoutSourceSha(wasm,receipt.artifactSha256['out/game.wasm']),receipt.artifactSha256['out/game.wasm']);
 const types={viz_clear:'char[21][80]',could_see:'seenV[2][21][80]',viz_clear_rows:'char *[21]',cs_rows0:'seenV *[21]',cs_rows1:'seenV *[21]',circle_data:'const coordxy[137]',circle_start:'const coordxy[16]'},locations={};
 for(const[name,type]of Object.entries(types)){const output=execFileSync(tool,['--name='+name,wasm],{encoding:'utf8',stdio:['ignore','pipe','ignore']});assert.ok(output.includes('"'+type+'"'),name+' original native type');assert.match(output,/DW_AT_decl_file\s*\("[^"\n]*\/src\/vision\.c"\)/);const found=[...output.matchAll(/DW_AT_location\s*\(DW_OP_addr 0x([0-9a-f]+)\)/g)];assert.equal(found.length,1,name+' unique original static location');locations[name]=parseInt(found[0][1],16);}
 const metadata={wasmSha256:hash(wasm),dwarfToolSha256:hash(tool),locations,types};
 function observe(runtime){const module=runtime.module,e=runtime.environment,heap=module?.HEAPU8??e.memory.HEAPU8,view=new DataView(heap.buffer),p64=p=>Number(view.getBigUint64(p,true)),raw=(p,n)=>Buffer.from(heap.slice(p,p+n)).toString('hex'),nativeGlobals={};
  if(module){const str=p=>{p=Number(p);let q=p;while(heap[q])q++;return Buffer.from(heap.slice(p,q)).toString();};for(let i=0;i<module._full_global_count();i++)nativeGlobals[str(module._full_global_name(i))]=Number(module._full_global_address(i));}
  const global=n=>module?nativeGlobals[n]:e.requireGlobal(n),privateAt=n=>module?locations[n]:e.requireGlobal('vision.'+n),gv=global('gv'),field=n=>gv+records.instance_globals_v.fields[n].offset,rows=p=>p?Array.from({length:21},(_,y)=>raw(p64(p+8*y),80)):null,coords=p=>p?Array.from({length:21},(_,y)=>view.getInt16(p+2*y,true)):null;
  const clear=privateAt('viz_clear'),could=privateAt('could_see'),rowOffsets=(name,base)=>Array.from({length:21},(_,y)=>p64(privateAt(name)+8*y)-base);
  return{gv:{rows:rows(p64(field('viz_array'))),rmin:coords(p64(field('viz_rmin'))),rmax:coords(p64(field('viz_rmax'))),fullRecalc:view.getInt8(field('vision_full_recalc'))},vizClear:Array.from({length:21},(_,y)=>raw(clear+y*80,80)),couldSee:[0,1].map(i=>Array.from({length:21},(_,y)=>raw(could+i*21*80+y*80,80))),clearRowOffsets:rowOffsets('viz_clear_rows',clear),couldRowOffsets:[rowOffsets('cs_rows0',could),rowOffsets('cs_rows1',could)],circleData:raw(privateAt('circle_data'),137*2),circleStart:raw(privateAt('circle_start'),16*2)};
 }
 return{metadata,observe};
}
