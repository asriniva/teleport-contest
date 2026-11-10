#!/usr/bin/env node
// Development-only comparison with the original C equipment catalogue.
import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import { dirname, join, resolve } from 'node:path';
import { fileURLToPath, pathToFileURL } from 'node:url';
const root = resolve(dirname(fileURLToPath(import.meta.url)), '..');
const sdk = resolve(process.env.EMSDK ?? join(root, '.cache/emsdk'));
const { parse } = await import(pathToFileURL(join(sdk,
    'upstream/emscripten/node_modules/acorn/dist/acorn.mjs')).href);
const original = readFileSync(join(root, '.cache/wasm64-build/tree/src/worn.c'), 'utf8');
const clean = original.replace(/\/\*[\s\S]*?\*\/|\/\/[^\n]*|"(?:\\.|[^"\\])*"/g,
    token => token.startsWith('/*') || token.startsWith('//') ? '' : token);
const initializer = clean.match(/\bworn\[\]\s*=\s*\{([\s\S]*?)\n\};/);
assert.ok(initializer, 'Review original worn initializer');
const row = /\{\s*(W_\w+|0)\s*,\s*(&\w+|0)\s*,\s*("(?:\\.|[^"\\])*"|\(char\s*\*\)\s*0)\s*\}/g;
const expected = [...initializer[1].matchAll(row)].map(record => ({
    w_mask: record[1] === '0' ? 0 : record[1],
    w_obj: record[2] === '0' ? 0 : record[2].slice(1),
    w_what: record[3].startsWith('"') ? JSON.parse(record[3]) : 0,
}));
assert.equal(expected.length, 17, 'Review original equipment row count');
assert.match(initializer[1].replace(row, ''), /^[\s,]*$/, 'Review original equipment grammar');

function check(source) {
    const ast = parse(source, { ecmaVersion: 'latest', sourceType: 'module' });
    const declarations = ast.body.map(node => node.type === 'ExportNamedDeclaration' ? node.declaration : node)
        .filter(node => node?.type === 'VariableDeclaration')
        .flatMap(node => node.declarations).filter(node => node.id.name === 'worn');
    assert.equal(declarations.length, 1, 'Exactly one authoritative worn table');
    assert.equal(declarations[0].init?.type, 'ArrayExpression');
    const actual = declarations[0].init.elements.map(node => {
        assert.equal(node?.type, 'ObjectExpression');
        const result = {};
        for (const property of node.properties) {
            assert.equal(property.type, 'Property');
            assert.equal(property.kind, 'init');
            assert.ok(!property.computed && !property.method && !property.shorthand);
            const key = property.key.name ?? property.key.value;
            assert.ok(!Object.hasOwn(result, key), 'No duplicate equipment field');
            assert.equal(property.value.type, 'Literal', 'Keep symbolic selectors and labels as data');
            result[key] = property.value.value;
        }
        assert.deepEqual(Object.keys(result).sort(), ['w_mask', 'w_obj', 'w_what']);
        return result;
    });
    assert.deepEqual(actual, expected, 'Original worn masks, live-cell selectors, labels, order and sentinel');
}
const source = readFileSync(join(root, 'js/ported/worn.js'), 'utf8');
check(source);
assert.throws(() => check(source.replace('"W_ARM"', '"W_ARMC"').replace("'W_ARM'", "'W_ARMC'")), /Original worn/);
assert.throws(() => check(source.replace('"uarm"', '"uarmc"').replace("'uarm'", "'uarmc'")), /Original worn/);
assert.throws(() => check(source.replace(/export\s+const\s+worn\s*=/, 'export const wrong_worn =')), /authoritative worn/);
console.log('WORN source data: all17 equipment rows, source selectors/labels/sentinel and3 mutation checks passed');
