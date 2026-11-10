import { assertStackRestored, allocationMetric, assertMemoryGrowth, memoryCheckpoint, referenceBackend, referenceLabel } from './native-test-backend.mjs';
const referenceFactory = referenceBackend('drawing', emscriptenReferenceFactory);
import assert from './native-test-assert.mjs';
import { readFileSync } from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/drawing-reference.mjs';
import hybridFactory from '../.cache/tu-probes/drawing-hybrid.mjs';
import { createPortedRuntime } from '../js/ported/wasm-runtime.js';
import { C, R, T } from '../js/ported/c-runtime.js';

const layouts = JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json', import.meta.url)));
const modules = [await referenceFactory(), await hybridFactory({ nethackPorted: createPortedRuntime(layouts) })];
const stacks = modules.map(module => module._probe_stack());
let comparisons = 0;
function scope() {
    assert.equal(C, undefined); assert.equal(R, undefined); assert.equal(T, undefined);
    modules.forEach((module, i) => assertStackRestored(module, stacks[i]));
}
function bytes(module, pointer) {
    if (!pointer) return null;
    let end = Number(pointer);
    while (module.HEAPU8[end]) end++;
    return Buffer.from(module.HEAPU8.slice(Number(pointer), end));
}
function metadata(module, kind) {
    return Object.fromEntries(Array.from({ length: module[`_probe_${kind}_count`]() }, (_, i) => [
        bytes(module, module[`_probe_${kind}_name`](i)).toString(), Number(module[`_probe_${kind}_value`](i)),
    ]));
}
assert.deepEqual(metadata(modules[1], 'layout'), metadata(modules[0], 'layout'));
assert.deepEqual(metadata(modules[1], 'constant'), metadata(modules[0], 'constant'));
assert.equal(modules[1]._probe_char_signed(), modules[0]._probe_char_signed());
function snapshot(module) {
    const aliases = new Map();
    function string(pointer) {
        if (!pointer) return { bytes: null, alias: -1 };
        const key = BigInt(pointer).toString();
        if (!aliases.has(key)) aliases.set(key, aliases.size);
        return { bytes: bytes(module, pointer).toString('hex'), alias: aliases.get(key) };
    }
    return Array.from({ length: 5 }, (_, table) => Array.from({ length: module._probe_table_count(table) }, (_, i) => ({
        symbol: module._probe_table_symbol(table, i),
        name: string(module._probe_table_name(table, i)),
        explanation: string(module._probe_table_explanation(table, i)),
        color: module._probe_table_color(table, i),
    })));
}
// No drawing lookup has been invoked. The authoritative JS data must already
// be materialized for C consumers during module startup, without lazy calls.
const initial = modules.map(snapshot);
assert.deepEqual(initial[1], initial[0]); scope(); comparisons++;
const tablePointers = modules.map(module => Array.from({ length: 5 }, (_, table) => module._probe_table_pointer(table)));
assert.ok(initial[0][0].length > 1 && initial[0][1].length > 1 && initial[0][2].length === 6);
assert.deepEqual(initial[0][0][0].name.bytes, '');
assert.deepEqual(initial[0][0][0].explanation.bytes, '');
assert.equal(initial[0][3].at(-1).symbol, 0);
assert.equal(initial[0][3].at(-1).explanation.bytes, null, 'The default symbol sentinel has a null explanation');

function lookup(name, value) {
    const result = modules.map(module => module['_probe_' + name](value));
    assert.equal(result[1], result[0], `${name}(${value})`); scope(); comparisons++;
    return result[0];
}
for (let byte = 0; byte <= 255; byte++) {
    for (const name of ['object', 'monclass', 'furniture']) {
        const actual = lookup(name, byte);
        assert.equal(lookup(name, byte - 256), actual, 'C char parameter truncation preserves the low byte');
        assert.equal(lookup(name, byte + 256), actual);
    }
}
for (const value of [-2147483648, -65537, -65536, -65535, -32769, -32768, -257, -256, -129, -128, -1,
    0, 1, 127, 128, 255, 256, 257, 32767, 32768, 65535, 65536, 65537, 2147483647]) {
    for (const name of ['object', 'monclass', 'furniture']) lookup(name, value);
}
// Every actual symbol maps to the first matching class; zero remains excluded
// by the original class loops which deliberately begin at element one.
for (const [name, table] of [['object', 0], ['monclass', 1]]) {
    const rows = initial[0][table];
    for (let i = 1; i < rows.length; i++) {
        const first = rows.findIndex((row, index) => index > 0 && row.symbol === rows[i].symbol);
        assert.equal(lookup(name, rows[i].symbol), first);
    }
    assert.equal(lookup(name, 0), rows.length);
}
modules.forEach((module, i) => {
    assert.deepEqual(snapshot(module), initial[i], 'Lookup calls leave every data element and alias unchanged');
    tablePointers[i].forEach((pointer, table) => assert.equal(module._probe_table_pointer(table), pointer));
});
comparisons++;
const oldBuffers = modules.map(module => memoryCheckpoint(module));
modules.forEach(module => module._malloc(40n * 1024n * 1024n));
modules.forEach((module, i) => assertMemoryGrowth(module, oldBuffers[i]));
modules.forEach((module, i) => assert.deepEqual(snapshot(module), initial[i]));
for (let byte = 0; byte <= 255; byte++) for (const name of ['object', 'monclass', 'furniture']) lookup(name, byte);
const independent = await hybridFactory({ nethackPorted: createPortedRuntime(layouts) });
assert.deepEqual(snapshot(independent), initial[0], 'A fresh module also initializes every table before any lookup');
independent._probe_object(65); independent._probe_monclass(64); independent._probe_furniture(60);
modules.forEach((module, i) => assert.deepEqual(snapshot(module), initial[i]));
scope(); comparisons++;
console.log(`DRAWING: ${comparisons} ${referenceLabel}/hybrid startup-table, string-alias, char-lookup and memory-growth comparisons checked.`);
