// Sweep real cmap glyphs and lighting across the entire controlled map; reuse
// the original full native/JS region, pointer, trace and ownership comparisons.
import './pure-js-probes/deny-wasm.mjs';
import assert from 'node:assert/strict';
import {reset,setter,action,set,global,ptr,sizeOf,C,root,addr} from './test-tu-display.mjs';
const glyphs=[C.GLYPH_CMAP_STONE_OFF,C.GLYPH_NOTHING_OFF,C.GLYPH_UNEXPLORED_OFF];
assert.ok(C.GLYPH_CMAP_B_OFF>C.GLYPH_CMAP_A_OFF);
for(let glyph=C.GLYPH_CMAP_A_OFF;glyph<C.GLYPH_CMAP_B_OFF;glyph++)glyphs.push(glyph);
assert.ok(glyphs.every(Number.isSafeInteger));
let cases=0;
for(const branch of ['main','mines','hell','knox','sokoban'])for(const dark of [0,1])for(const color of [0,1])for(const rogue of [0,1]){
 reset();
 setter(m=>{
  m._probe_option(1,Number(branch==='mines'));m._probe_option(2,Number(branch==='hell'));
  set(m,global(m,'flags'),'flag','dark_room',dark);set(m,global(m,'iflags'),'instance_flags','wc_color',color);
  const u=addr(m,global(m,'u'),'you','uz'),topology=addr(m,global(m,'svd'),'instance_globals_saved_d','dungeon_topology'),heroDungeon=branch==='knox'?9:branch==='sokoban'?11:7;
  set(m,u,'d_level','dnum',heroDungeon);set(m,u,'d_level','dlevel',3);
  for(const [name,number]of [['d_knox_level',9],['d_rogue_level',rogue?heroDungeon:10]]){
   const p=addr(m,topology,'dgn_topology',name);set(m,p,'d_level','dnum',number);set(m,p,'d_level','dlevel',3);
  }
  set(m,topology,'dgn_topology','d_sokoban_dnum',11);
  const grid=Number(m._probe_grid()),sight=ptr(m,7);
  let index=0;
  for(let x=1;x<80;x++)for(let y=0;y<21;y++,index++){
   const cell=grid+(x*21+y)*sizeOf('struct rm'),pattern=Math.floor(index/glyphs.length)&7;
   m._probe_map(x,y,index&1?C.ROOM:C.CORR,pattern&1?255:0);
   set(m,cell,'rm','glyph',glyphs[index%glyphs.length]);set(m,cell,'rm','lit',pattern&1);set(m,cell,'rm','waslit',(pattern>>1)&1);
   m.HEAPU8[sight+y*80+x]=pattern&4?3:0;
  }
 });
 action('reglyph_darkroom');
 setter(m=>set(m,global(m,'flags'),'flag','dark_room',1-dark));
 action('reglyph_darkroom');
 cases++;
}
assert.equal(cases,40);
console.log('PASS:40 original-C/pure-JS full-map darkroom cases,80 full comparisons; five dungeon contexts, dark/color/rogue toggles, '+glyphs.length+' valid remembered glyphs and distributed seen/lit/sight states across1659 cells. Controlled dependencies; no full-game claim.');
