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
const wizard=process.argv.includes('--wizard');
const scratch=path.join(build,wizard?'wizard-tests':process.argv.includes('--all-levels')?'all-level-tests':'level-tests');fs.mkdirSync(scratch,{recursive:true});
const wizardCases={
 'lua-os-probe.lua':`assert(type(os)=='table' and type(debug)=='table' and io==nil and package==nil)
local keys={} for k in pairs(os) do keys[#keys+1]=k end table.sort(keys)
assert(table.concat(keys,',')=='clock,date,difftime,remove,rename,time')
assert(os.date('!%F %T',951827696)=='2000-02-29 12:34:56')
local t=os.date('!*t',0); assert(t.year==1970 and t.month==1 and t.day==1)
assert(os.difftime(99,12)==87 and type(os.clock())=='number')
assert(os.rename('lua-probe-input','lua-probe-renamed'));assert(os.remove('lua-probe-renamed'))
assert(os.rename('lua-os-marker','lua-os-passed'))`,
 'lua-debug-probe.lua':`assert(type(collectgarbage)=='function' and type(load)=='function' and type(loadfile)=='function' and type(dofile)=='function')
assert(debug.debug==nil and debug.gethook==nil and debug.sethook==nil)
local function f() local x=17; return debug.getinfo(1,'S').what,x end
local what,x=f();assert(what=='Lua' and x==17)
local x=23;local function capture()return x end
local name,v=debug.getupvalue(capture,1);assert(name=='x' and v==23)
assert(debug.setupvalue(capture,1,29)=='x' and capture()==29)
local once=false; local f=assert(load(function()if once then return nil end once=true return 'return 37' end,'reader','t'));assert(f()==37)
assert(loadfile('lua-reader-fixture.lua')()==41 and dofile('lua-reader-fixture.lua')==41)
collectgarbage('collect');assert(type(collectgarbage('count'))=='number')
assert(os.rename('lua-debug-marker','lua-debug-passed'))`,
};
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
            FS.mkdirTree('/nethack');for (const [name,bytes] of Object.entries(input.luaProbeFiles || {})) FS.writeFile('/nethack/'+name,bytes);
            const originalRead = FS.read;
            FS.read = function(stream, ...args) {
                const count = originalRead.call(this, stream, ...args);
                if (count > 0 && stream.path?.endsWith('.lua')) luaReads.push(stream.path);
                return count;
            };`);
 adapter=adapter.replace('getScreens: () => screens,','getLuaFileReads: () => luaReads, getScreens: () => screens,');
 adapter=adapter.replace('getLuaFileReads: () => luaReads,','getLuaProbeFiles: () => Object.fromEntries(Object.keys(input.luaProbeExpected || {}).map(name => [name,module.FS.analyzePath("/nethack/"+name).exists])), getLuaFileReads: () => luaReads,');
 const filename=path.join(scratch,backend+'-adapter.mjs');fs.writeFileSync(filename,adapter);
 factories[backend]=(await import(pathToFileURL(filename))).runWasmSegment;
}
let files=process.argv.includes('--probe')?['castle.lua']:['minetn-1.lua','minetn-2.lua','minetn-3.lua','minetn-4.lua','minetn-5.lua','minetn-6.lua','minetn-7.lua','minend-1.lua','minend-2.lua','minend-3.lua','soko1-1.lua','soko1-2.lua','soko2-1.lua','soko2-2.lua','soko3-1.lua','soko3-2.lua','soko4-1.lua','soko4-2.lua','oracle.lua','bigrm-1.lua','bigrm-2.lua','medusa-1.lua','medusa-2.lua','medusa-3.lua','medusa-4.lua','castle.lua','valley.lua','asmodeus.lua','baalz.lua','juiblex.lua','orcus.lua','wizard1.lua','wizard2.lua','wizard3.lua','sanctum.lua','earth.lua','air.lua','fire.lua','water.lua','astral.lua','Tou-strt.lua','Tou-loca.lua','Tou-goal.lua'];
if(process.argv.includes('--all-levels'))files=fs.readdirSync(path.join(build,'snapshot/prepared/dat')).filter(name=>name.endsWith('.lua')&&!['quest.lua','nhcore.lua','nhlib.lua','dungeon.lua','themerms.lua'].includes(name)).sort();
if(wizard)files=Object.keys(wizardCases);
else for(const file of files)assert.ok(fs.existsSync(path.join(build,'snapshot/prepared/dat',file)),file+' must be an original embedded level');
const options='OPTIONS=name:LuaProbe,role:Tourist,race:human,gender:female,align:neutral\nOPTIONS=!autopickup,!legacy,!tutorial,!splash_screen,pettype:none\nOPTIONS=pushweapon,showexp,time,color,suppress_alert:3.3.1\nOPTIONS=symset:DECgraphics\n';
const seeds=process.argv.includes('--probe')?[8000]:[8000,17,4294967295];
const report=[];
for(const seed of seeds)for(let start=0;start<files.length;start+=6) {
 const group=files.slice(start,start+6);
 const moves=group.map(file=>(wizard?'#wizloadlua\n':'#wizloaddes\n')+file+'\n'+' '.repeat(12)+'\x1b').join('')+':';
 const input={seed,datetime:'20260401090000',nethackrc:options,moves};
 if(wizard){input.luaProbeFiles={...wizardCases,'lua-reader-fixture.lua':'return 41','lua-probe-input':'payload','lua-os-marker':'ok','lua-debug-marker':'ok'};input.luaProbeExpected={'lua-os-passed':true,'lua-debug-passed':true,'lua-probe-input':false,'lua-probe-renamed':false};}
 const results={};
 for(const backend of ['base-game','game']) {
  const game=await factories[backend]({...input,storage:new InMemoryStorage()});
  results[backend]={screens:game.getScreens(),cursors:game.getCursors(),rng:game.getRngLog(),animations:game.getAnimationFramesByStep(),luaReads:game.getLuaFileReads()};
  if(wizard)assert.deepEqual(game.getLuaProbeFiles(),input.luaProbeExpected,backend+': wizard scripts must reach their success markers');
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
console.log(`PASS: ${report.length} ${wizard?'wizard OS/debug script':'original special-level'} groups through actual C NetHack callbacks, ${seeds.length} seeds; all RNG/screens/cursors/animations match compiled Lua.`);
