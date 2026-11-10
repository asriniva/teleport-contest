/** Private full-game C-Lua/JS-Lua differential: wizard-load original levels.
 * Only private adapter copies add -D and choose a snapshotted module factory.
 * No original source, script, recording, frozen harness or active build changes. */
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import { fileURLToPath, pathToFileURL } from 'node:url';

const root=fileURLToPath(new URL('../',import.meta.url));
const option=process.argv.indexOf('--build-dir');
const build=path.resolve(root, option<0?'.cache/js-lua-game-opcodes':process.argv[option+1]);
const scratch=path.join(build,'level-tests');fs.mkdirSync(scratch,{recursive:true});
const source=fs.readFileSync(path.join(build,'snapshot/js/wasm-adapter.js'),'utf8');
const {InMemoryStorage}=await import(pathToFileURL(path.join(build,'snapshot/js/storage.js')));
const factories={};
for(const backend of ['base-game','game']) {
 let adapter=source.replace(/from '(\.\.?\/[^']+)'/g,(_,specifier)=>'from '+JSON.stringify(pathToFileURL(path.resolve(build,'snapshot/js',specifier)).href));
 assert.equal(adapter.split("await import('./wasm/nethack.mjs')").length,2);
 adapter=adapter.replace("await import('./wasm/nethack.mjs')",'await import('+JSON.stringify(pathToFileURL(path.join(build,backend+'.mjs')).href)+')');
 assert.ok(adapter.includes("module.callMain(['-u', name])"));
 adapter=adapter.replace("module.callMain(['-u', name])","module.callMain(['-D', '-u', name])");
 adapter=adapter.replace('const screens = [], cursors = [], animations = [];','const screens = [], cursors = [], animations = []; const luaReads = [];');
 adapter=adapter.replace('const { FS, ENV } = instance;',`const { FS, ENV } = instance;
            const originalRead = FS.read;
            FS.read = function(stream, ...args) {
                const count = originalRead.call(this, stream, ...args);
                if (count > 0 && stream.path?.endsWith('.lua')) luaReads.push(stream.path);
                return count;
            };`);
 adapter=adapter.replace('getScreens: () => screens,','getLuaFileReads: () => luaReads, getScreens: () => screens,');
 const filename=path.join(scratch,backend+'-adapter.mjs');fs.writeFileSync(filename,adapter);
 factories[backend]=(await import(pathToFileURL(filename))).runWasmSegment;
}
const files=process.argv.includes('--probe')?['castle.lua']:['minetn-1.lua','minetn-2.lua','minetn-3.lua','minetn-4.lua','minetn-5.lua','minetn-6.lua','minetn-7.lua','minend-1.lua','minend-2.lua','minend-3.lua','soko1-1.lua','soko1-2.lua','soko2-1.lua','soko2-2.lua','soko3-1.lua','soko3-2.lua','soko4-1.lua','soko4-2.lua','oracle.lua','bigrm-1.lua','bigrm-2.lua','medusa-1.lua','medusa-2.lua','medusa-3.lua','medusa-4.lua','castle.lua','valley.lua','asmodeus.lua','baalz.lua','juiblex.lua','orcus.lua','wizard1.lua','wizard2.lua','wizard3.lua','sanctum.lua','earth.lua','air.lua','fire.lua','water.lua','astral.lua','Tou-strt.lua','Tou-loca.lua','Tou-goal.lua'];
for(const file of files)assert.ok(fs.existsSync(path.join(build,'snapshot/prepared/dat',file)),file+' must be an original embedded level');
const options='OPTIONS=name:LuaProbe,role:Tourist,race:human,gender:female,align:neutral\nOPTIONS=!autopickup,!legacy,!tutorial,!splash_screen,pettype:none\nOPTIONS=pushweapon,showexp,time,color,suppress_alert:3.3.1\nOPTIONS=symset:DECgraphics\n';
const seeds=process.argv.includes('--probe')?[8000]:[8000,17,4294967295];
const report=[];
for(const seed of seeds)for(let start=0;start<files.length;start+=6) {
 const group=files.slice(start,start+6);
 const moves=group.map(file=>'#wizloaddes\n'+file+'\n'+' '.repeat(12)+'\x1b').join('')+':';
 const input={seed,datetime:'20260401090000',nethackrc:options,moves};
 const results={};
 for(const backend of ['base-game','game']) {
  const game=await factories[backend]({...input,storage:new InMemoryStorage()});
  results[backend]={screens:game.getScreens(),cursors:game.getCursors(),rng:game.getRngLog(),animations:game.getAnimationFramesByStep(),luaReads:game.getLuaFileReads()};
 }
 const native=results['base-game'],js=results.game;
 fs.writeFileSync(path.join(scratch,`seed${seed}-group${start}-native.json`),JSON.stringify(native));
 fs.writeFileSync(path.join(scratch,`seed${seed}-group${start}-js.json`),JSON.stringify(js));
 for(const key of ['rng','screens','cursors','animations'])assert.deepEqual(js[key],native[key],`seed ${seed} levels ${group.join(',')} ${key}`);
 assert.deepEqual(js.luaReads,native.luaReads,'Both backends must actually read the same original scripts');
 for(const file of group)assert.ok(native.luaReads.some(filename=>filename.endsWith('/'+file)),`${file}: actual script bytes must be read`);
 const row={seed,files:group,screens:js.screens.length,rng:js.rng.length,animationFrames:js.animations.reduce((n,a)=>n+a.length,0)};
 report.push(row);console.log(JSON.stringify(row));
 fs.writeFileSync(path.join(scratch,'summary.json'),JSON.stringify({passed:report.length,groups:report},null,2)+'\n');
}
console.log(`PASS: ${report.length} original special-level groups through actual C NetHack callbacks, ${seeds.length} seeds; all RNG/screens/cursors/animations match compiled Lua.`);
