#!/usr/bin/env node
// Development-only original-source check; no game/runtime lookup table.
import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import { dirname, join, resolve } from 'node:path';
import { fileURLToPath, pathToFileURL } from 'node:url';
const root = resolve(dirname(fileURLToPath(import.meta.url)), '..');
const sdk = resolve(process.env.EMSDK ?? join(root, '.cache/emsdk'));
const { parse } = await import(pathToFileURL(join(sdk,
    'upstream/emscripten/node_modules/acorn/dist/acorn.mjs')).href);
const original = readFileSync(join(root, '.cache/wasm64-build/tree/src/wield.c'), 'utf8');
const names = ['are_no_longer_twoweap', 'can_no_longer_twoweap'];
const expected = Object.fromEntries(names.map(name => {
    const match = original.match(new RegExp('\\b' + name + '\\[\\]\\s*=\\s*("(?:\\\\.|[^"\\\\])*")'));
    assert.ok(match, 'Review original message: ' + name);
    return [name, JSON.parse(match[1])];
}));
function check(source) {
    const ast = parse(source, { ecmaVersion: 'latest', sourceType: 'module' });
    const actual = {};
    for (const entry of ast.body) {
        const node = entry.type === 'ExportNamedDeclaration' ? entry.declaration : entry;
        if (node?.type !== 'VariableDeclaration') continue;
        for (const item of node.declarations) {
            if (!names.includes(item.id.name)) continue;
            assert.equal(node.kind, 'const', 'Readonly source messages');
            assert.ok(!Object.hasOwn(actual, item.id.name), 'Unique source message');
            assert.equal(item.init?.type, 'Literal', 'Direct source message literal');
            actual[item.id.name] = item.init.value;
        }
    }
    assert.deepEqual(actual, expected, 'Original wield messages');
}
const source = readFileSync(join(root, 'js/ported/wield.js'), 'utf8');
check(source);
assert.throws(() => check(source.replace(expected[names[0]], expected[names[0]] + '!')), /Original wield messages/);
assert.throws(() => check(source.replace(new RegExp('export\\s+const\\s+' + names[1]), 'export const missing_message')), /Original wield messages/);
console.log('WIELD source data: both original messages and two mutation checks passed');
