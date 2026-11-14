// Every source glyph maps to the same declared values as complete original C.
import assert from 'node:assert/strict';import fs from 'node:fs';
import {runFullOriginalC} from './full-original-c-run.mjs';
import {runStandaloneProgram} from './run-standalone-program.mjs';
import {initializeDisplay} from '../js/nethack/bindings/display.js';
import {nativeStateFor} from '../js/nethack/native/state-bridge.js';
let e,c;const input={keys:'',seed:1,timezone:'UTC',options:'OPTIONS=!news\n'};
const reference=await runFullOriginalC('.cache/full-original-c-v1',{...input,observeRuntime:r=>c=r.module});
const actual=runStandaloneProgram('.cache/full-original-c-v1/assets',{...input,observeRuntime:r=>e=r.environment});
for(const k of ['state','rngLog','displayRngLog','stdout','stderr'])assert.deepEqual(actual[k],reference[k],k);
const owner=nativeStateFor(e),display=initializeDisplay(e.start('display').environment),t=e.transport;
const mark=t.stackSave(),value=display.nativeLocalRecord('struct glyphinfo'),p=c._malloc(48n);
const readText=(heap,p)=>{p=Number(p);if(!p)return null;let end=p;while(heap[end])end++;return Buffer.from(heap.subarray(p,end)).toString('hex');};
const unicode=(heap,p)=>{p=Number(p?.address??p);if(!p)return null;const view=new DataView(heap.buffer);return [view.getUint32(p,true),readText(heap,view.getBigUint64(p+8,true))];};
const js=o=>[o.glyph,o.ttychar,o.framecolor,o.gm.glyphflags,o.gm.sym.color,o.gm.sym.symidx,o.gm.customcolor,o.gm.color256idx,o.gm.tileidx,unicode(e.memory.HEAPU8,o.gm.u)];
const original=()=>{const v=new DataView(c.HEAPU8.buffer),at=Number(p);return [v.getInt32(at,true),v.getInt32(at+4,true),v.getUint32(at+8,true),v.getUint32(at+16,true),v.getInt32(at+20,true),v.getInt32(at+24,true),v.getUint32(at+28,true),v.getUint16(at+32,true),v.getInt16(at+34,true),unicode(c.HEAPU8,v.getBigUint64(at+40,true))];};
const hero=owner.nativeRecords.record('struct you',e.requireGlobal('u'));
let checks=0;const before=e.memory.live.size;
for(const [x,y]of [[hero.ux,hero.uy],[0,0]])for(const flags of [0,1])for(let glyph=0;glyph<display.MAX_GLYPH;glyph++){
 value.write('framecolor',0x89abcdef);new DataView(c.HEAPU8.buffer).setUint32(Number(p)+8,0x89abcdef,true);
 display.nativeNamespace.map_glyphinfo(x,y,glyph,flags,value);c._map_glyphinfo(x,y,glyph,flags,BigInt(p));
 assert.deepEqual(js(value.object()),original(),'glyph '+glyph+' flags '+flags+' @ '+x+','+y);checks++;
}
assert.equal(e.memory.live.size,before,'mapping native values must not allocate C storage');
assert.ok(checks>10000);t.stackRestore(mark);c._free(p);
fs.mkdirSync('.cache/native-display-values',{recursive:true});fs.writeFileSync('.cache/native-display-values/glyphs.json',JSON.stringify({checks,glyphs:display.MAX_GLYPH,scope:'Every valid glyph, both NOOVERRIDE modes, hero and nonhero coordinates, source-initialized original C versus native DISPLAY mapping; all declared glyph fields, resolved Unicode pointer contents and preserved framecolor. No C storage allocated by native mapping. Other graphics configurations remain covered only where exercised by public recordings.'},null,2));console.log('PASS native glyphs '+checks);
