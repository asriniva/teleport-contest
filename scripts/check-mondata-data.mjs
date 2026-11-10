#!/usr/bin/env node
// Development-only exact projection of function-local C data, not game logic.
import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import { dirname, join, resolve } from 'node:path';
import { fileURLToPath, pathToFileURL } from 'node:url';

const root = resolve(dirname(fileURLToPath(import.meta.url)), '..');
const sdk = resolve(process.env.EMSDK ?? join(root, '.cache/emsdk'));
const { parse } = await import(pathToFileURL(join(sdk,
    'upstream/emscripten/node_modules/acorn/dist/acorn.mjs')).href);
const owners = { names: 'name_to_monplus', falsematch: 'name_to_monclass',
    truematch: 'name_to_monclass', rnd_breath_typ: 'get_atkdam_type' };
const records = new Set(['names', 'truematch']);

function originalArrays(source) {
    // Keep quoted text intact while removing comments, including comment-like
    // characters inside string literals. These four initializers have no CPP.
    const clean = source.replace(/\/\*[\s\S]*?\*\/|\/\/[^\n]*|"(?:\\.|[^"\\])*"/g,
        token => token.startsWith('/*') || token.startsWith('//') ? '' : token);
    const arrays = {};
    for (const name of Object.keys(owners)) {
        const pattern = new RegExp('\\b' + name + '\\s*\\[[^\\]]*\\]\\s*=\\s*\\{', 'g');
        const matches = [...clean.matchAll(pattern)];
        assert.equal(matches.length, 1, 'Expected exactly one original ' + name);
        const start = matches[0].index + matches[0][0].lastIndexOf('{');
        const tokens = [...clean.slice(start).matchAll(/"(?:\\.|[^"\\])*"|[A-Za-z_]\w*|\d+|[^\s]/g)]
            .map(match => match[0]);
        let index = 0;
        function value() {
            const token = tokens[index++];
            if (token === '{') {
                const result = [];
                while (tokens[index] !== '}') {
                    result.push(value());
                    if (tokens[index] === ',') index++;
                    else assert.equal(tokens[index], '}', 'Unexpected C initializer token');
                }
                index++;
                return result;
            }
            if (token === '-') {
                const next = value();
                assert.ok(['number', 'symbol'].includes(next[0]));
                return [next[0], next[0] === 'number' ? -next[1] : '-' + next[1]];
            }
            if (token.startsWith('"')) return ['string', JSON.parse(token)];
            if (/^\d+$/.test(token)) return ['number', Number(token)];
            assert.match(token, /^[A-Za-z_]\w*$/);
            return ['symbol', token];
        }
        arrays[name] = value();
    }
    return arrays;
}

function javascriptArrays(source) {
    const ast = parse(source, { ecmaVersion: 'latest', sourceType: 'module' });
    const arrays = {}, declarations = {};
    function value(node) {
        assert.ok(node, 'Sparse data arrays are not permitted');
        if (node.type === 'ArrayExpression') return node.elements.map(value);
        if (node.type === 'Literal') {
            assert.ok(['string', 'number'].includes(typeof node.value));
            return [typeof node.value, node.value];
        }
        if (node.type === 'MemberExpression') {
            assert.equal(node.computed, false);
            assert.equal(node.object.type, 'Identifier');
            assert.equal(node.object.name, 'C');
            assert.equal(node.property.type, 'Identifier');
            return ['symbol', node.property.name];
        }
        if (node.type === 'UnaryExpression' && node.operator === '-') {
            const item = value(node.argument);
            assert.ok(['number', 'symbol'].includes(item[0]));
            return [item[0], item[0] === 'number' ? -item[1] : '-' + item[1]];
        }
        if (node.type === 'ObjectExpression') {
            const fields = node.properties.map(property => {
                assert.equal(property.type, 'Property');
                assert.equal(property.computed, false);
                assert.equal(property.method, false);
                assert.equal(property.kind, 'init');
                assert.equal(property.key.type, 'Identifier');
                return property.key.name;
            });
            assert.deepEqual(fields, ['name', 'pm_val', 'genderhint']);
            return node.properties.map(property => value(property.value));
        }
        assert.fail('Unexpected local data expression: ' + node.type);
    }
    function visit(node, owner) {
        if (!node || typeof node !== 'object') return;
        if (Array.isArray(node)) { for (const child of node) visit(child, owner); return; }
        if (/Function/.test(node.type ?? '')) owner = node.id?.name ?? '<anonymous>';
        if (node.type === 'VariableDeclarator' && node.id.type === 'Identifier'
            && Object.hasOwn(owners, node.id.name)) {
            const name = node.id.name;
            assert.ok(!Object.hasOwn(arrays, name), 'Duplicate local array ' + name);
            assert.equal(owner, owners[name], name + ' moved out of its original function');
            assert.equal(node.init?.type, 'ArrayExpression', name + ' must remain literal data');
            if (records.has(name)) for (const row of node.init.elements)
                assert.equal(row?.type, 'ObjectExpression', name + ' must retain named fields');
            arrays[name] = value(node.init);
            declarations[name] = node;
        }
        for (const [key, child] of Object.entries(node))
            if (!['start', 'end', 'loc'].includes(key)) visit(child, owner);
    }
    visit(ast, undefined);
    assert.deepEqual(Object.keys(arrays).sort(), Object.keys(owners).sort());
    return { arrays, declarations };
}

const original = originalArrays(readFileSync(join(root,
    '.cache/wasm64-build/tree/src/mondata.c'), 'utf8'));
const javascript = readFileSync(join(root, 'js/ported/mondata.js'), 'utf8');
const projection = javascriptArrays(javascript);
assert.deepEqual(projection.arrays, original, 'Original local mondata tables changed');

// Exercise the checker against an altered row, an omitted declaration and a
// moved scope using in-memory text only. These are checker tests, not game data.
const row = projection.declarations.names.init.elements[0].properties[0].value;
const changed = javascript.slice(0, row.start) + JSON.stringify(row.value + '!')
    + javascript.slice(row.end);
assert.throws(() => assert.deepEqual(javascriptArrays(changed).arrays, original));
const declaration = projection.declarations.falsematch;
assert.throws(() => javascriptArrays(javascript.slice(0, declaration.start)
    + 'unrelated' + javascript.slice(declaration.start + 'falsematch'.length)));
assert.throws(() => javascriptArrays(javascript.replace('function name_to_monplus(',
    'function moved_name_to_monplus(')));
console.log('MONDATA local data projection passed: ' + Object.entries(original)
    .map(([name, values]) => name + '=' + values.length).join(', ')
    + '; 3 checker mutation tests passed.');
