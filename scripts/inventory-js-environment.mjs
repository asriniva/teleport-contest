// Planning inventory, not a proof of runtime coverage or transitive closure.
import fs from 'node:fs';
import path from 'node:path';
import crypto from 'node:crypto';
import {fileURLToPath, pathToFileURL} from 'node:url';
const root = path.resolve(fileURLToPath(new URL('../', import.meta.url)));
const sdk = process.env.EMSDK || path.join(root, '.cache/emsdk');
const {parse} = await import(pathToFileURL(path.join(sdk, 'upstream/emscripten/node_modules/acorn/dist/acorn.mjs')));
const output = process.argv[2];
if (!output) throw new Error('Usage: inventory-js-environment.mjs OUTPUT.json');
const hashes = {};
const read = relative => {
    const bytes = fs.readFileSync(path.join(root, relative));
    hashes[relative] = crypto.createHash('sha256').update(bytes).digest('hex');
    return bytes.toString('utf8');
};
function inspect(relative) {
    const ast = parse(read(relative), {ecmaVersion:'latest', sourceType:'module', locations:true});
    const accesses = {C:new Set(), R:new Set(), T:new Set(), services:new Set()};
    const computed = [], imports = [], exports = [], factories = [];
    function visit(node) {
        if (!node || typeof node !== 'object') return;
        if (node.type === 'ImportDeclaration') imports.push(node.source.value);
        if (node.type === 'ExportNamedDeclaration') {
            if (node.declaration?.id) exports.push(node.declaration.id.name);
            for (const item of node.specifiers || []) exports.push(item.exported.name);
        }
        if (node.type === 'FunctionDeclaration' && /^(create|initialize|call)/.test(node.id?.name || ''))
            factories.push(node.id.name);
        if (node.type === 'MemberExpression' && node.object.type === 'Identifier' && accesses[node.object.name]) {
            const field = !node.computed ? node.property.name : node.property.type === 'Literal' ? node.property.value : null;
            if (field !== null) accesses[node.object.name].add(String(field));
            else computed.push({object:node.object.name, line:node.loc.start.line});
        }
        for (const [key, value] of Object.entries(node)) {
            if (['loc','start','end'].includes(key)) continue;
            if (Array.isArray(value)) value.forEach(visit);
            else if (value && typeof value === 'object') visit(value);
        }
    }
    visit(ast);
    return {file:relative, accesses:Object.fromEntries(Object.entries(accesses).map(([k,v])=>[k,[...v].sort()])), computed, imports, exports, factories};
}
const registry = JSON.parse(read('nethack-c/wasm/tu-ports.json'));
const modules = registry.map(port => {
    const adapter = `js/nethack/bindings/${port.name}.js`;
    return {name:port.name, source:port.source, canonicalInGame:port.name==='isaac64',
        startup:port.startup || null, policy:inspect(port.javascript),
        adapter:fs.existsSync(path.join(root,adapter)) ? inspect(adapter) : null};
});
// Include all bridge files: several registry rows use differently named adapters,
// and early ports are adapted directly in wasm-runtime.js.
const runtimeFiles = fs.readdirSync(path.join(root,'js/nethack/bindings'))
    .filter(name=>name.endsWith('.js')).sort().map(name=>inspect('js/nethack/bindings/'+name));
const serviceFrequency = {};
for (const module of modules) for (const key of module.adapter?.accesses.services || [])
    serviceFrequency[key] = (serviceFrequency[key] || 0) + 1;
const result = {
    scope:'Committed registry game ports; standalone utility profiles are a separate follow-up.',
    limitation:'AST member accesses are requirements candidates, not missing-feature counts. No alias resolution, call graph, macro expansion, branch execution or transitive closure is inferred. Runtime files and dynamic accesses require manual review. Constants, game functions, storage and libc are mixed in C accesses. Adapter filename matches are conventional only.',
    registryEntries:modules.length,
    canonicalIsaac:'Game delegates to frozen js/isaac64.js; registry source translation is historical and must not count as new PRNG work.',
    foundation:['js/nethack/runtime.js','js/c-runtime/heap.js','js/c-runtime/stdlib.js','js/c-runtime/vfs.js'].map(inspect),
    modules, runtimeFiles, serviceFrequency, hashes,
};
fs.writeFileSync(path.resolve(output), JSON.stringify(result,null,2)+'\n');
console.log(JSON.stringify({registryEntries:modules.length,runtimeFiles:runtimeFiles.length,hashedInputs:Object.keys(hashes).length,output:path.resolve(output)}));
