#!/usr/bin/env node
// Development-only source projection; no game algorithms or runtime imports.
import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import { dirname, join, resolve } from 'node:path';
import { fileURLToPath, pathToFileURL } from 'node:url';
const root = resolve(dirname(fileURLToPath(import.meta.url)), '..');
const sdk = resolve(process.env.EMSDK ?? join(root, '.cache/emsdk'));
const { parse } = await import(pathToFileURL(join(sdk,
    'upstream/emscripten/node_modules/acorn/dist/acorn.mjs')).href);
const original = readFileSync(join(root, '.cache/wasm64-build/tree/src/hacklib.c'), 'utf8');
const clean = original.replace(/\/\*[\s\S]*?\*\/|\/\/[^\n]*|"(?:\\.|[^"\\])*"/g,
    token => token.startsWith('/*') || token.startsWith('//') ? '' : token);
const initializer = clean.match(/static\s+struct\s+datamodel_information\s+dm\[\]\s*=\s*\{([\s\S]*?)\n\};/);
assert.ok(initializer, 'Review original datamodel initializer');
const records = [...initializer[1].matchAll(/\{\s*\{([^{}]+)\}\s*,\s*("(?:\\.|[^"\\])*")\s*,\s*("(?:\\.|[^"\\])*")\s*\}/g)];
assert.equal(records.length, 5, 'Review original datamodel row count');
assert.match(initializer[1].replace(/\{\s*\{([^{}]+)\}\s*,\s*("(?:\\.|[^"\\])*")\s*,\s*("(?:\\.|[^"\\])*")\s*\}/g, ''), /^[\s,]*$/);
const sizes = { short: 'shortSize', int: 'intSize', long: 'longSize',
    'long long': 'longLongSize', genericptr_t: 'pointerSize' };
const expected = records.map((row, index) => ({
    sz: row[1].split(',').map(value => {
        value = value.trim();
        if (index) { assert.match(value, /^\d+$/); return Number(value); }
        const match = value.match(/^\(int\)\s*sizeof\(([^)]+)\)$/);
        assert.ok(match && sizes[match[1]], 'Review original sizeof expression: ' + value);
        return sizes[match[1]];
    }),
    datamodel: JSON.parse(row[2]), dmplatform: JSON.parse(row[3]),
}));
const vowel = clean.match(/static\s+const\s+char\s+vowel\[\]\s*=\s*("(?:\\.|[^"\\])*")\s*;/);
assert.ok(vowel, 'Review original function-local vowel initializer');

function check(source) {
    const ast = parse(source, { ecmaVersion: 'latest', sourceType: 'module' });
    const top = ast.body.map(node => node.type === 'ExportNamedDeclaration' ? node.declaration : node);
    const declarations = top.filter(node => node?.type === 'VariableDeclaration')
        .flatMap(node => node.declarations).filter(node => node.id.name === 'dm');
    assert.equal(declarations.length, 1, 'Exactly one top-level authoritative dm table');
    function literal(node) {
        if (node?.type === 'Literal') return node.value;
        assert.equal(node?.type, 'ArrayExpression', 'Data must remain direct literals');
        return node.elements.map(literal);
    }
    assert.equal(declarations[0].init?.type, 'ArrayExpression');
    const actual = declarations[0].init.elements.map(node => {
        assert.equal(node?.type, 'ObjectExpression');
        const result = {};
        for (const property of node.properties) {
            assert.equal(property.type, 'Property');
            assert.equal(property.kind, 'init');
            assert.ok(!property.computed && !property.method && !property.shorthand);
            const key = property.key.name ?? property.key.value;
            assert.ok(!Object.hasOwn(result, key), 'No duplicate datamodel field');
            result[key] = literal(property.value);
        }
        assert.deepEqual(Object.keys(result).sort(), ['datamodel', 'dmplatform', 'sz']);
        return result;
    });
    assert.deepEqual(actual, expected, 'Original sizeof selectors, row order, fields and strings');
    const owner = top.find(node => node?.type === 'FunctionDeclaration' && node.id.name === 'ing_suffix');
    assert.ok(owner);
    const locals = owner.body.body.filter(node => node.type === 'VariableDeclaration')
        .flatMap(node => node.declarations).filter(node => node.id.name === 'vowel');
    assert.equal(locals.length, 1, 'vowel must retain original enclosing function');
    let value = locals[0].init;
    if (value?.type === 'CallExpression') {
        assert.equal(value.callee.type, 'MemberExpression');
        assert.equal(value.callee.object.name, 'C');
        assert.equal(value.callee.property.name, 'charPointer');
        assert.equal(value.arguments.length, 1);
        value = value.arguments[0];
    }
    assert.equal(value?.type, 'Literal');
    assert.equal(value.value, JSON.parse(vowel[1]), 'Original local vowel byte sequence');
}
const source = readFileSync(join(root, 'js/ported/hacklib.js'), 'utf8');
check(source);
assert.throws(() => check(source.replace('ILP32LL64', 'wrong-model')), /Original sizeof selectors/);
assert.throws(() => check(source.replace(/export\s+const\s+dm\s*=/, 'export const wrong_dm =')), /authoritative dm/);
assert.throws(() => check(source.replace('aeiouwy', 'aeiou')), /vowel byte sequence/);
console.log('HACKLIB source data: all5 datamodel rows, local vowel scope/value and3 mutation checks passed');
