import fs from 'node:fs';
import assert from 'node:assert/strict';
const file=process.argv[2],module=new WebAssembly.Module(fs.readFileSync(file));
const imports=WebAssembly.Module.imports(module),allowed=new Set(['teleport_getch','teleport_capture','port_insert_pastebuf']);
for(const row of imports){assert.ok(!row.name.startsWith('teleport_')||allowed.has(row.name),'Unexpected custom dependency import '+row.name);assert.ok(!/nethackPorted|nethackLua|nethackDependencies/.test(row.name),'JS algorithm dispatch '+row.name);}
const js=fs.readFileSync(file.replace(/\.wasm$/,'.mjs'),'utf8');
assert.ok(!/Module\[['"]nethack(?:Ported|Lua|Dependencies)['"]\]/.test(js),'Reference must not call JS game/dependency algorithms');
const exports=new Set(WebAssembly.Module.exports(module).map(r=>r.name));
for(const name of ['full_global_count','full_global_address','full_moves','full_rng_state'])assert.ok(exports.has(name),'Missing actual source observer '+name);
console.log('PASS: strict full-C imports; '+imports.length+' SDK/I/O imports, '+exports.size+' actual compiled exports.');
