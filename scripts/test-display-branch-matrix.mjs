// Reuse original C/JS full-state/pointer/trace assertions without copying them.
// Import executes the existing DISPLAY checks before these additional cases.
import './pure-js-probes/deny-wasm.mjs';
import assert from 'node:assert/strict';
import {reset,setter,seed,action,set,global,ptr,property,sizeOf,C,root,addr} from './test-tu-display.mjs';
const terrain=['STONE','ROOM','CORR','DOOR','SDOOR','SCORR','STAIRS','LADDER','FOUNTAIN','SINK','GRAVE','ALTAR','THRONE','TREE','IRONBARS','POOL','MOAT','LAVAPOOL','AIR','CLOUD','ICE'];
let cases=0;
for(const typ of terrain)for(let pattern=0;pattern<8;pattern++){
 assert.ok(Number.isInteger(C[typ]),typ);reset();seed(11+pattern);
 const a=pattern&1,b=(pattern>>1)&1,c=(pattern>>2)&1;
 // Six distinct nonzero linear forms over3 bits give every pair of Boolean
 // factors all four combinations: lit,waslit,blind,seenv,sight,memory.
 const lit=a,waslit=b,blind=c,seen=a^b,sight=a^c,memory=b^c,x=41,y=11;
 setter(m=>{
  m._probe_map(x,y,C[typ],seen?255:0);
  const cell=Number(m._probe_grid())+(x*21+y)*sizeOf('struct rm');
  set(m,cell,'rm','lit',lit);set(m,cell,'rm','waslit',waslit);
  property(m,'BLINDED',blind);
  const level=root(m,'svl','instance_globals_saved_l','level');
  set(m,addr(m,level,'dlevel_t','flags'),'levelflags','hero_memory',memory);
  m.HEAPU8[ptr(m,7)+y*80+x]=sight?3:0;
 });
 for(const [name,args]of [['map_background',[x,y]],['map_location',[x,y,sight]],['back_to_glyph',[x,y]],['newsym',[x,y]]])action(name,args);
 cases++;
}
assert.equal(cases,168);console.log('PASS:168 additional original-C/pure-JS DISPLAY terrain/visibility cases,672 full state/result/trace comparisons;21 terrain kinds and pairwise coverage of6 Boolean factors. Controlled world/window dependencies.');
