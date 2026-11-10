import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import referenceFactory from '../.cache/tu-probes/rect-reference.mjs';
import hybridFactory from '../.cache/tu-probes/rect-hybrid.mjs';
import { createPortedRuntime } from '../js/ported/wasm-runtime.js';
import { C, R } from '../js/ported/c-runtime.js';

const layouts = JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json', import.meta.url)));
const layout = layouts.rect;
const runtime = createPortedRuntime(layouts);
const modules = [await referenceFactory(), await hybridFactory({ nethackPorted: runtime })];
const fields = ['lx', 'ly', 'hx', 'hy'];
let comparisons = 0;
function cstring(module, pointer) {
    const start = Number(pointer);
    let end = start;
    while (module.HEAPU8[end]) end++;
    return Buffer.from(module.HEAPU8.slice(start, end)).toString();
}
function read(module, pointer) {
    if (!pointer) return null;
    const view = new DataView(module.HEAPU8.buffer);
    return fields.map(field => view['getInt' + layout.coordSize * 8](Number(pointer) + layout[field], true));
}
function bases() { return [Number(modules[0]._probe_data()), runtime.rectState.rect?.address || 0]; }
function state() {
    const counts = [modules[0]._probe_count(), runtime.rectState.rect_cnt];
    const capacities = [modules[0]._probe_capacity(), runtime.rectState.n_rects];
    assert.equal(counts[1], counts[0]);
    assert.equal(capacities[1], capacities[0]);
    const pointers = bases();
    assert.equal(Boolean(pointers[1]), Boolean(pointers[0]));
    const values = modules.map((module, i) => Array.from({ length: counts[i] }, (_, j) => read(module, pointers[i] + j * layout.size)));
    assert.deepEqual(values[1], values[0]);
    for (const name of ['rng_count', 'rng_bound', 'diagnostic_count']) assert.equal(modules[1]['_probe_' + name](), modules[0]['_probe_' + name]());
    for (const name of ['rng_caller', 'diagnostic_message']) {
        assert.equal(cstring(modules[1], modules[1]['_probe_' + name]()), cstring(modules[0], modules[0]['_probe_' + name]()));
    }
    assert.equal(C, undefined);
    assert.equal(R, undefined);
    comparisons++;
    return values[1];
}
function boxes(value) {
    return modules.map(module => {
        const pointer = module._malloc(BigInt(layout.size));
        const view = new DataView(module.HEAPU8.buffer);
        fields.forEach((field, j) => view['setInt' + layout.coordSize * 8](Number(pointer) + layout[field], value[j], true));
        return pointer;
    });
}
function release(pointers) { modules.forEach((module, i) => module._free(pointers[i])); }
function call(name, ...argumentsByModule) {
    const result = modules.map((module, i) => module['_probe_' + name](...argumentsByModule.map(args => args[i])));
    state();
    return result;
}
function useBox(name, value) {
    const pointers = boxes(value);
    const result = call(name, pointers.map(BigInt));
    release(pointers);
    return result;
}
function normalizePointers(pointers) {
    const base = bases();
    return pointers.map((pointer, i) => pointer ? (Number(pointer) - base[i]) / layout.size : -1);
}
function random() {
    const pointers = call('random');
    const indices = normalizePointers(pointers);
    assert.equal(indices[1], indices[0]);
    comparisons++;
    return pointers;
}

call('seed', [123, 123]);
random(); // empty state consumes no RNG
call('free');
call('free');
call('init');
assert.deepEqual(state(), [[0, 0, layout.COLNO - 1, layout.ROWNO - 1]]);
for (const box of [[0, 0, 79, 20], [1, 1, 2, 2], [-1, 0, 2, 2], [80, 20, 81, 21]]) {
    const results = useBox('get', box);
    const normalized = normalizePointers(results);
    assert.equal(normalized[1], normalized[0]);
    const indices = useBox('index', box);
    assert.equal(indices[1], indices[0]);
}
useBox('remove', [7, 7, 9, 9]); // not a precise match
useBox('add', [1, 1, 2, 2]); // contained rectangle is ignored
call('init'); // reuse allocation, reset list

// By-value struct arguments must stay snapshots when output aliases either input.
for (const [a, b] of [
    [[0, 0, 5, 5], [-2, 3, 9, 7]],
    [[-32768, -32768, 32767, 32767], [7, 8, 9, 10]],
    [[32767, -32768, -32768, 32767], [0, -1, 1, 2]],
]) {
    for (const alias of [-1, 0, 1]) {
        const first = boxes(a), second = boxes(b), output = alias === 0 ? first : alias === 1 ? second : boxes([0, 0, 0, 0]);
        call('bounds', first.map(BigInt), second.map(BigInt), output.map(BigInt));
        assert.deepEqual(read(modules[1], output[1]), read(modules[0], output[0]));
        comparisons++;
        release(first); release(second);
        if (alias < 0) release(output);
    }
}

// Overlap forces recursive intersections across multiple list members.
call('init');
useBox('remove', [0, 0, 79, 20]);
useBox('add', [0, 0, 50, 15]);
useBox('add', [20, 5, 79, 20]);
const cut = boxes([25, 7, 30, 10]);
call('split', bases().map(BigInt), cut.map(BigInt));
release(cut);

for (let trial = 0; trial < 70; trial++) {
    call('seed', [trial + 1, trial + 1]);
    call('init');
    for (let step = 0; step < 30 && runtime.rectState.rect_cnt; step++) {
        const selected = random();
        const [lx, ly, hx, hy] = read(modules[0], selected[0]);
        const x = lx + (trial * 7 + step * 3) % (hx - lx + 1);
        const y = ly + (trial * 3 + step * 5) % (hy - ly + 1);
        const remove = boxes([x, y, Math.min(hx, x + 2 + trial % 5), Math.min(hy, y + 1 + step % 3)]);
        call('split', selected.map(BigInt), remove.map(BigInt));
        release(remove);
    }
}

// Capacity diagnostic precedes duplicate/containment checks in the original.
call('init');
useBox('remove', [0, 0, 79, 20]);
for (let i = 0; i < runtime.rectState.n_rects; i++) useBox('add', [-1000 + i, -10, -1000 + i, -10]);
useBox('add', [-999, -10, -999, -10]);
assert.equal(modules[1]._probe_diagnostic_count(), 1);
assert.equal(cstring(modules[1], modules[1]._probe_diagnostic_message()), 'n_rects may be too small.');
for (let i = 0; i < 20; i++) random();

// Views/proxies created before growth must read the new buffer afterward.
const old = modules.map(module => module.HEAPU8.buffer);
modules.forEach(module => module._malloc(40n * 1024n * 1024n));
modules.forEach((module, i) => assert.notEqual(module.HEAPU8.buffer, old[i]));
state();
call('init');
random();
call('free');
random();

// A second game instance has independent statics even with interleaved calls.
const independentRuntime = createPortedRuntime(layouts);
const independent = await hybridFactory({ nethackPorted: independentRuntime });
modules[1]._probe_init();
independent._probe_init();
const before = { ...runtime.rectState.rect[0] };
independent._probe_free();
assert.equal(independentRuntime.rectState.rect_cnt, 0);
assert.equal(runtime.rectState.rect_cnt, 1);
assert.deepEqual({ ...runtime.rectState.rect[0] }, before);
modules[1]._probe_free();
assert.equal(C, undefined);
assert.equal(R, undefined);
console.log(`RECT: ${comparisons} original-C/hybrid geometry, state, pointer and RNG comparisons passed.`);
