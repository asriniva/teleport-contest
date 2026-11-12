// Development-only check of required factory arguments in the real dispatcher.
// Spread arguments and runtime value types remain outside this static contract.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import {resolve, dirname} from 'node:path';
import {fileURLToPath, pathToFileURL} from 'node:url';
const root = resolve(dirname(fileURLToPath(import.meta.url)), '..');
const sdk = resolve(process.env.EMSDK ?? resolve(root, '.cache/emsdk'));
const {parse} = await import(pathToFileURL(resolve(sdk, 'upstream/emscripten/node_modules/acorn/dist/acorn.mjs')));
function check(source, factories) {
    let checked = 0;
    function visit(node) {
        if (!node || typeof node !== 'object') return;
        if (node.type === 'CallExpression' && node.callee.type === 'Identifier'
            && factories.has(node.callee.name) && !node.arguments.some(arg => arg.type === 'SpreadElement')) {
            const required = factories.get(node.callee.name);
            assert.ok(node.arguments.length >= required,
                `${node.callee.name} requires ${required} arguments; central dispatcher supplies ${node.arguments.length}`);
            checked++;
        }
        for (const value of Object.values(node)) {
            if (Array.isArray(value)) value.forEach(visit);
            else if (value && typeof value === 'object') visit(value);
        }
    }
    visit(parse(source, {ecmaVersion:'latest', sourceType:'module'}));
    return checked;
}
const fixture = new Map([['createFixtureEnvironment', 3]]);
assert.equal(check('createFixtureEnvironment(services, layout, core);', fixture), 1);
assert.throws(() => check('createFixtureEnvironment(services, layout);', fixture), /requires 3 arguments/);
assert.equal(check('createFixtureEnvironment(...args);', fixture), 0);
const sourcePath = resolve(root, 'js/backends/emscripten/runtime.js');
const source = fs.readFileSync(sourcePath, 'utf8');
const ast = parse(source, {ecmaVersion:'latest', sourceType:'module'});
const factories = new Map();
for (const node of ast.body) {
    if (node.type !== 'ImportDeclaration') continue;
    const names = node.specifiers.filter(spec => spec.type === 'ImportSpecifier' && /^(create|initialize)[A-Z]/.test(spec.local.name));
    if (!names.length) continue;
    const imported = await import(new URL(node.source.value, pathToFileURL(sourcePath)));
    for (const spec of names) {
        const fn = imported[spec.imported.name];
        assert.equal(typeof fn, 'function', spec.local.name);
        let required = fn.length;
        // Production unixtty receives its optional va_list through the argument
        // packet; its fourth explicit pointer is used by isolated/native callers.
        if (spec.local.name === 'createUnixttyEnvironment') {
            assert.equal(fn.length, 4);
            assert.ok(fn.toString().includes('vaPointer ?? packet?.nativeVaList'));
            required = 3;
        }
        factories.set(spec.local.name, required);
    }
}
console.log(`Central factory argument contract passed: ${check(source, factories)} calls; missing-namespace negative fixture rejected.`);
