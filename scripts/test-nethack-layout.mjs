// Inspect the current checkout. Historical source receipts have their own audit.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import { fileURLToPath, pathToFileURL } from 'node:url';
import { parse } from 'acorn';

const ports = JSON.parse(fs.readFileSync('nethack-c/wasm/tu-ports.json', 'utf8'));
const generatedProbes = new Set(ports.flatMap(({ name }) => [
    `.cache/tu-probes/${name}-reference.mjs`, `.cache/tu-probes/${name}-hybrid.mjs`,
]));
const sdkParser = '.cache/emsdk/upstream/emscripten/node_modules/acorn/dist/acorn.mjs';
let modules = 0, imports = 0, unbuilt = 0;

function checkImport(file, specifier, dynamic) {
    if (typeof specifier !== 'string' || !specifier.startsWith('.')) return;
    const url = new URL(specifier, pathToFileURL(path.resolve(file)));
    const target = path.relative(process.cwd(), fileURLToPath(url)).split(path.sep).join('/');
    assert.ok(!target.startsWith('js/standalone/'), 'Obsolete module path in ' + file + ': ' + specifier);
    if (!fs.statSync(target, { throwIfNoEntry: false })?.isFile()) {
        const buildInput = file.startsWith('scripts/') && (target === sdkParser || generatedProbes.has(target));
        // These test runners are written into .cache by the test before it imports them.
        const testRunner = dynamic && file.startsWith('scripts/test-') && /^\.cache\/[^/]+-runner\.mjs$/.test(target);
        const wasmBridge = target === 'js/wasm/nethack.mjs'
            && (file === 'scripts/test-version-bridge.mjs' || file === 'js/wasm-adapter.js');
        assert.ok(buildInput || testRunner || wasmBridge, 'Unresolved import in ' + file + ': ' + specifier);
        unbuilt++;
        return;
    }
    imports++;
}

function checkModuleReferences(file, node) {
    if (node.type === 'ImportDeclaration' || node.type === 'ImportExpression'
        || node.type === 'ExportNamedDeclaration' || node.type === 'ExportAllDeclaration') {
        checkImport(file, node.source?.value, node.type === 'ImportExpression');
    }
    for (const child of Object.values(node)) {
        if (Array.isArray(child)) {
            for (const entry of child) if (entry?.type) checkModuleReferences(file, entry);
        } else if (child?.type) {
            checkModuleReferences(file, child);
        }
    }
}

function visit(directory) {
    for (const entry of fs.readdirSync(directory, { withFileTypes: true })) {
        const file = path.posix.join(directory, entry.name);
        if (entry.isDirectory()) {
            visit(file);
            continue;
        }
        if (!/\.(?:js|mjs)$/.test(file) || file === 'js/wasm/nethack.mjs') continue;
        const source = fs.readFileSync(file, 'utf8');
        let ast;
        try {
            ast = parse(source, { ecmaVersion: 'latest', sourceType: 'module' });
        } catch (error) {
            throw new Error(file + ': ' + error.message, { cause: error });
        }
        modules++;
        checkModuleReferences(file, ast);
        if (/^scripts\/test-(?:tu-|standalone-)/.test(file)) {
            assert.ok(!source.includes('runPriorLayoutAudit'), 'Runtime test uses historical modules: ' + file);
        }
        if (file.startsWith('js/')) {
            assert.ok(!source.includes('../standalone/'), 'Obsolete production import in ' + file);
        }
    }
}

visit('js');
visit('scripts');
assert.ok(!fs.existsSync('js/standalone'), 'Old production directory remains');
await import('./pure-js-probes/deny-wasm.mjs');
const { createStandaloneEnvironment } = await import('../js/nethack/environment.js');
const env = createStandaloneEnvironment();
assert.ok(env.memory && env.services);
console.log(`PASS current layout: ${modules} modules parsed, ${imports} relative imports resolved, ${unbuilt} references to absent optional build outputs. The environment initialized with Wasm denied.`);
