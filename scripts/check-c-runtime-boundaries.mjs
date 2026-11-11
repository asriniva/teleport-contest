// Validate the runtime's real module graph and reject application/host coupling.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import {pathToFileURL} from 'node:url';
const root=process.cwd(),reference=process.env.STANDALONE_REFERENCE_ROOT??path.resolve('../teleport-contest');
const {parse}=await import(pathToFileURL(reference+'/.cache/emsdk/upstream/emscripten/node_modules/acorn/dist/acorn.mjs'));
const visited=new Set();
function visitFile(file) {
    file=path.resolve(file);if(visited.has(file))return;visited.add(file);
    const relative=path.relative(root,file);
    assert.ok(relative.startsWith('js/c-runtime/')||relative.startsWith('js/services/'),'Application dependency in C runtime: '+relative);
    if(file.endsWith('.json'))return;
    const ast=parse(fs.readFileSync(file,'utf8'),{ecmaVersion:'latest',sourceType:'module'});
    function visit(node) {
        if(!node||typeof node!=='object')return;
        if(['ImportDeclaration','ExportNamedDeclaration','ExportAllDeclaration','ImportExpression'].includes(node.type)&&node.source) {
            assert.equal(typeof node.source.value,'string','Dynamic runtime import');
            assert.ok(node.source.value.startsWith('.'),'Host runtime import');
            visitFile(path.resolve(path.dirname(file),node.source.value));
        }
        if(node.type==='Identifier')assert.ok(!['WebAssembly','process','require','fetch','Worker','WebSocket','XMLHttpRequest'].includes(node.name),'Host capability in runtime: '+node.name);
        for(const [key,value]of Object.entries(node)){if(['start','end'].includes(key))continue;if(Array.isArray(value))value.forEach(visit);else if(value&&typeof value==='object')visit(value);}
    }
    visit(ast);
}
visitFile(path.resolve('js/c-runtime/index.js'));
// Every core implementation must be covered, not merely currently used exports.
for(const file of fs.readdirSync('js/c-runtime').filter(file=>file.endsWith('.js')))visitFile(path.resolve('js/c-runtime',file));
const measured=JSON.parse(fs.readFileSync('js/standalone/scanf-abi.json'));
const profile=JSON.parse(fs.readFileSync('js/c-runtime/libc-profile.json'));
for(const key of ['EINVAL','ERANGE','longBytes','pointerBytes','EOF'])assert.equal(profile[key],measured[key]);
console.log('PASS: '+visited.size+' runtime/dependency files; no game modules, host imports, Wasm or network capabilities; configured libc profile matches measured declarations.');
