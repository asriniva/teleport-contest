// Development evidence capture: resolve literal local module dependencies.
// Nonliteral imports and runtime file access require explicit artifact seeds.
import fs from 'node:fs';
import path from 'node:path';
import {fileURLToPath, pathToFileURL} from 'node:url';
const project = path.resolve(path.dirname(fileURLToPath(import.meta.url)), '..');
const args = process.argv.slice(2);
function option(name, fallback) {
    const i = args.indexOf(name);
    return i < 0 ? fallback : args[i + 1];
}
const root = path.resolve(option('--root', project));
const sdk = path.resolve(process.env.EMSDK ?? path.join(project, '.cache/emsdk'));
const {parse} = await import(pathToFileURL(path.join(sdk, 'upstream/emscripten/node_modules/acorn/dist/acorn.mjs')));
const seeds = ['js/jsmain.js', 'js/wasm-adapter.js', 'js/backends/emscripten/runtime.js',
    'js/wasm/nethack.mjs', 'scripts/test-wasm.mjs'];
const seen = new Set(), nonliteral = [];
function collect(relative) {
    if (seen.has(relative)) return;
    const filename = path.resolve(root, relative);
    if (!filename.startsWith(root + path.sep)) throw new Error(`Dependency escapes root: ${relative}`);
    if (!fs.statSync(filename).isFile()) throw new Error(`Missing module ${relative}`);
    seen.add(relative);
    if (!/\.[cm]?js$/.test(relative)) return;
    const ast = parse(fs.readFileSync(filename, 'utf8'), {ecmaVersion:'latest', sourceType:'module'});
    function visit(node) {
        if (!node || typeof node !== 'object') return;
        let source;
        if (['ImportDeclaration', 'ExportNamedDeclaration', 'ExportAllDeclaration'].includes(node.type)) source = node.source;
        if (node.type === 'ImportExpression') {
            source = node.source;
            if (source.type !== 'Literal') nonliteral.push({file:relative, offset:node.start});
        }
        if (source?.type === 'Literal' && typeof source.value === 'string' && source.value.startsWith('.')) {
            const url = new URL(source.value, pathToFileURL(filename));
            collect(path.relative(root, fileURLToPath(url)));
        }
        for (const value of Object.values(node)) {
            if (Array.isArray(value)) value.forEach(visit);
            else if (value && typeof value === 'object') visit(value);
        }
    }
    visit(ast);
}
seeds.forEach(collect);
const result = {seeds, files:[...seen].sort(), nonliteralImports:nonliteral,
    limitation:'Literal local module dependencies only; runtime artifacts and nonliteral imports require explicit seeds.'};
const output = option('--output', null);
if (output) fs.writeFileSync(output, JSON.stringify(result, null, 2) + '\n');
console.log(`Resolved ${seen.size} local module files; ${nonliteral.length} nonliteral import expressions reported.`);
