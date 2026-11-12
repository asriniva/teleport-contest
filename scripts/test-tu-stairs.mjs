import './pure-js-probes/deny-wasm.mjs';
import { DataView, assertStackRestored, allocationMetric, assertMemoryGrowth, memoryCheckpoint, referenceBackend, referenceLabel } from './native-test-backend.mjs';
const referenceFactory = referenceBackend('stairs', emscriptenReferenceFactory);
import assert from './native-test-assert.mjs';
import { readFileSync } from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/stairs-reference.mjs';
import createPureJsProbe from './pure-js-probes/stairs.mjs';
import { C, R, T } from '../js/c-runtime/context.js';

const layouts = JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json', import.meta.url)));
const layout = layouts.stairs;
const modules = [await referenceFactory(), await createPureJsProbe(layouts)];
let comparisons = 0;
function scope() { assert.equal(C, undefined); assert.equal(R, undefined); assert.equal(T, undefined); }
function cstring(module, pointer) {
    let end = Number(pointer);
    while (module.HEAPU8[end]) end++;
    return Buffer.from(module.HEAPU8.slice(Number(pointer), end)).toString();
}
function read(module, pointer, offset, size, signed = true) {
    return new DataView(module.HEAPU8.buffer)[`get${size === 8 ? 'Big' : ''}${signed ? 'Int' : 'Uint'}${size * 8}`](Number(pointer) + offset, true);
}
function nodes(module) {
    const result = [], seen = new Set();
    let pointer = module._probe_head();
    while (pointer) {
        assert.ok(!seen.has(pointer), 'List must have no cycle'); seen.add(pointer);
        result.push(pointer);
        pointer = read(module, pointer, layout.next, 8, false);
    }
    return result;
}
function state() {
    const states = modules.map(module => ({
        nodes: nodes(module).map(pointer => ({
            x: read(module, pointer, layout.sx, layout.coordxySize),
            y: read(module, pointer, layout.sy, layout.coordxySize),
            dnum: read(module, pointer, layout.tolev + layout.dnum, layout.levelFieldSize),
            dlevel: read(module, pointer, layout.tolev + layout.dlevel, layout.levelFieldSize),
            up: read(module, pointer, layout.up, layout.boolSize, Boolean(layout.boolSigned)),
            ladder: read(module, pointer, layout.isladder, layout.boolSize, Boolean(layout.boolSigned)),
            traversed: read(module, pointer, layout.u_traversed, layout.boolSize, Boolean(layout.boolSigned)),
        })),
        trace: cstring(module, module._probe_trace()),
    }));
    assert.deepEqual(states[1], states[0]); scope(); comparisons++;
    return states[0];
}
function call(name, ...args) {
    const results = modules.map(module => module['_probe_' + name](...args));
    state(); return results;
}
function scalar(name, ...args) {
    const results = call(name, ...args);
    assert.equal(results[1], results[0]); comparisons++;
    return results[0];
}
function pointer(name, ...args) {
    const results = call(name, ...args);
    const indices = results.map((result, i) => result ? nodes(modules[i]).indexOf(result) : -1);
    assert.equal(indices[1], indices[0]);
    if (results[0]) assert.ok(indices[0] >= 0, 'Return must alias an actual C list node');
    comparisons++; return indices[0];
}
function mark(index, value) {
    modules.forEach(module => {
        const pointer = nodes(module)[index];
        new DataView(module.HEAPU8.buffer)[`setUint${layout.boolSize * 8}`](Number(pointer) + layout.u_traversed, value, true);
    });
    state();
}
function describe(index, singular) {
    const results = modules.map(module => module._probe_describe(nodes(module)[index], singular));
    results.forEach((result, i) => assert.equal(result, modules[i]._probe_description_buffer(), 'Description returns caller buffer'));
    const texts = results.map((result, i) => cstring(modules[i], result));
    assert.equal(texts[1], texts[0]); state(); comparisons++;
    return texts[0];
}
function known(index) {
    const results = modules.map(module => module._probe_known(index < 0 ? 0n : nodes(module)[index]));
    assert.equal(results[1], results[0]); state(); comparisons++;
    return results[0];
}
function queries(x, y, dnum, dlevel) {
    pointer('at', x, y); pointer('find', dnum, dlevel);
    for (const flag of [0, 1, 2, -1, 255, 256]) {
        pointer('find_from', dnum, dlevel, flag);
        pointer('find_dir', flag); pointer('find_special_dir', flag);
        for (const other of [0, 1, 2, 255, 256]) pointer('find_type_dir', flag, other);
    }
    for (const fn of ['on', 'ladder', 'on_up', 'on_down']) scalar(fn, x, y);
}
call('init'); call('hero', 0, 5, 0);
assert.equal(known(-1), 0);
queries(5, 6, 0, 2);
call('up'); call('down'); call('special', 256);
assert.equal(state().trace, 'random:0;random:1;random:256;');
// Front insertion and duplicate coordinates/destinations must return the most
// recent matching node, including equality against noncanonical boolean bytes.
for (const entry of [
    [10, 11, 1, 0, 0, 6], [12, 13, 0, 1, 1, 3],
    [10, 11, 2, 255, 1, 3], [32767, -32768, 256, -1, 2, 7],
    [-1, 0, -1, 2, 3, 1],
]) {
    call('add', ...entry);
    queries(entry[0], entry[1], entry[4], entry[5]);
    queries(79, 20, 4, 99);
}
assert.equal(pointer('at', 10, 11), 2);
assert.equal(pointer('find', 1, 3), 2);
for (const flag of [0, 1, 2, -1, 255, 256, 257]) {
    call('hero', 0, 5, 0); call('special', flag);
}
call('hero', 0, 5, 0); call('up'); call('down');
for (let i = 0; i < nodes(modules[0]).length; i++) {
    for (const traversed of [0, 1, 2, 255]) {
        mark(i, traversed); known(i);
        describe(i, 0); describe(i, 1); describe(i, 256);
    }
}
// Mutating a returned node changes subsequent C lookups immediately.
const aliases = modules.map(module => module._probe_at(10, 11));
modules.forEach((module, i) => {
    new DataView(module.HEAPU8.buffer)[`setInt${layout.coordxySize * 8}`](Number(aliases[i]) + layout.sx, 61, true);
});
state(); assert.equal(pointer('at', 61, 11), 2);
call('free'); assert.equal(state().nodes.length, 0); call('free');

// Exercise each description branch, checking oracle text as well as expected
// high-level outcomes so that a shared fixture error is visible.
function descriptionCase(hero, stair, traversed, expected) {
    call('init'); call('hero', ...hero); call('add', ...stair); mark(0, traversed);
    const text = describe(0, 0);
    if (expected) assert.equal(text, expected);
    describe(0, 1); known(0);
}
descriptionCase([0, 7, 0], [1, 2, 0, 0, 0, 8], 0, 'stairs down');
descriptionCase([0, 7, 0], [1, 2, 1, 1, 0, 6], 1, 'ladder up to level 6');
descriptionCase([2, 7, 0], [1, 2, 0, 0, 2, 8], 1, 'stairs down to level 8');
descriptionCase([3, 1, 0], [1, 2, 0, 0, 3, 1], 1, 'stairs down to level 1');
descriptionCase([1, 7, 0], [1, 2, 0, 0, 1, 8], 1, 'stairs down to level 18');
descriptionCase([0, 7, 0], [1, 2, 0, 0, 1, 3], 1, 'branch stairs down to the Gnomish Mines');
descriptionCase([0, 7, 0], [1, 2, 0, 1, 3, 1], 1, 'branch ladder down to Fort Ludios');
descriptionCase([0, 1, 0], [1, 2, 1, 0, 4, 1], 1, 'stairs up out of the dungeon');
for (const plane of [1, 2, 3, 4]) {
    descriptionCase([0, 1, 1], [1, 2, 1, 0, 4, plane], 1, 'branch stairs up to the Elemental Planes');
}
descriptionCase([0, 1, 1], [1, 2, 1, 0, 4, 5], 1, 'branch stairs up to the end game');
descriptionCase([0, 1, 1], [1, 2, 0, 0, 4, 1], 1, 'branch stairs down to the End Game');
descriptionCase([0, 2, 1], [1, 2, 1, 0, 4, 1], 1, 'branch stairs up to the End Game');

// Placement fallback: direct direction, special opposite direction and random.
for (const entries of [[], [[21, 22, 1, 0, 1, 3]], [[23, 24, 0, 1, 1, 3]], [[25, 26, 2, 0, 0, 3]]]) {
    call('init'); call('hero', 0, 5, 0);
    entries.forEach(entry => call('add', ...entry));
    call('up'); call('down');
    for (const flag of [0, 1, 256, -1]) call('special', flag);
}

// Deterministic broad list/order search coverage, without dependence on RNG.
call('init'); call('hero', 0, 5, 0);
for (let i = 0; i < 120; i++) {
    const entry = [(i * 7) % 80, (i * 13) % 21, i % 3, i % 4, i % 5, i % 9 + 1];
    call('add', ...entry);
    if (i % 7 === 0) { queries(entry[0], entry[1], entry[4], entry[5]); mark(0, 1); describe(0, i % 2); }
}
const before = state();
const oldBuffers = modules.map(module => memoryCheckpoint(module));
modules.forEach(module => module._malloc(40n * 1024n * 1024n));
modules.forEach((module, i) => assertMemoryGrowth(module, oldBuffers[i]));
assert.deepEqual(state(), before);
queries(0, 0, 1, 3); describe(0, 1); call('add', 77, 19, 0, 1, 2, 5);
const independent = await createPureJsProbe(layouts);
const unchanged = state();
independent._probe_init(); independent._probe_hero(1, 1, 1); independent._probe_add(1, 1, 1, 1, 1, 2);
assert.equal(nodes(independent).length, 1);
independent._probe_free(); assert.deepEqual(state(), unchanged);
call('free'); assert.equal(state().nodes.length, 0); scope();
console.log(`STAIRS: ${comparisons} ${referenceLabel}/pure-JS list, pointer, placement and description comparisons checked.`);
