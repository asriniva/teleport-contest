import { DataView, assertStackRestored, allocationMetric, assertMemoryGrowth, memoryCheckpoint, referenceBackend, referenceLabel } from './native-test-backend.mjs';
const referenceFactory = referenceBackend('track', emscriptenReferenceFactory);
import assert from './native-test-assert.mjs';
import { readFileSync } from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/track-reference.mjs';
import hybridFactory from '../.cache/tu-probes/track-hybrid.mjs';
import { createPortedRuntime } from '../js/ported/wasm-runtime.js';
import { C, R, T } from '../js/ported/c-runtime.js';

const layouts = JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json', import.meta.url)));
const layout = layouts.track;
const runtime = createPortedRuntime(layouts);
const modules = [await referenceFactory(), await hybridFactory({ nethackPorted: runtime })];
let comparisons = 0;
function scope() {
    assert.equal(C, undefined); assert.equal(R, undefined); assert.equal(T, undefined);
}
function cstring(module, pointer) {
    let end = Number(pointer);
    while (module.HEAPU8[end]) end++;
    return Buffer.from(module.HEAPU8.slice(Number(pointer), end)).toString();
}
function state() {
    const values = modules.map(module => {
        const pointer = Number(module._probe_data());
        return {
            count: module._probe_count(), point: module._probe_point(),
            coords: Buffer.from(module.HEAPU8.slice(pointer, pointer + layout.UTSZ * layout.coordSize)),
        };
    });
    assert.deepEqual(values[1], values[0]);
    scope(); comparisons++;
    return values[1];
}
function call(name, ...args) {
    const results = modules.map(module => module['_probe_' + name](...args));
    state(); return results;
}
function hero(x, y, left = -1, right = -1) { call('hero', x, y, left, right); call('set'); }
function query(x, y) {
    const pointers = call('get', x, y);
    const indices = pointers.map((pointer, i) => pointer ? (Number(pointer) - Number(modules[i]._probe_data())) / layout.coordSize : -1);
    assert.equal(indices[1], indices[0]);
    const has = call('has', x, y);
    assert.equal(has[1], has[0]);
    comparisons++;
    return indices[1];
}
function serialization() {
    const values = modules.map(module => {
        const pointer = Number(module._probe_stream()), length = Number(module._probe_stream_size());
        return { bytes: Buffer.from(module.HEAPU8.slice(pointer, pointer + length)), trace: cstring(module, module._probe_trace()) };
    });
    assert.deepEqual(values[1], values[0]);
    comparisons++;
    return values[1];
}
call('init');
assert.equal(query(0, 0), -1);
hero(10, 10);
assert.equal(query(10, 10), -1, 'Exact current location returns null');
assert.equal(query(11, 10), 0);
assert.equal(query(11, 11), 0, 'Chebyshev diagonal distance is one');
assert.equal(query(12, 10), -1);
for (const [left, right] of [[layout.RIN_STEALTH, -1], [-1, layout.RIN_STEALTH], [layout.RIN_STEALTH, layout.RIN_STEALTH]]) {
    const before = state();
    hero(30, 30, left, right);
    assert.deepEqual(state(), before, 'A stealth ring in either hand prevents tracking');
}
hero(20, 20, 0, 1); // non-stealth equipment does not suppress the trail
assert.equal(query(21, 20), 1);
hero(11, 10);
assert.equal(query(11, 10), -1, 'Most recent exact match suppresses an older adjacent point');

for (let i = 0; i < 453; i++) {
    hero(i % 80, (i * 7) % 21, i % 17 === 0 ? layout.RIN_STEALTH : -1, -1);
    query(i % 80, (i * 7 + 1) % 21);
    query(-1, -1);
}
assert.equal(state().count, layout.UTSZ);
// Returned C pointer remains mutable storage, not a detached JS coordinate.
call('init'); hero(8, 8);
const result = call('get', 9, 8);
modules.forEach((module, i) => new DataView(module.HEAPU8.buffer)['setInt' + layout.coordxySize * 8](Number(result[i]) + layout.x, 42, true));
state();
assert.equal(query(43, 8), 0);

for (const length of [0, 1, 99, 100, 101, 250]) {
    for (const mode of [0, layout.COUNTING, layout.WRITING, layout.FREEING, layout.WRITING | layout.FREEING, layout.COUNTING | layout.FREEING]) {
        call('init');
        for (let i = 0; i < length; i++) hero(i - 150, i * 3 - 100);
        const before = state();
        call('save', mode);
        const saved = serialization();
        const writing = Boolean(mode & (layout.COUNTING | layout.WRITING));
        assert.equal(saved.bytes.length, writing ? layout.intSize * 2 + before.count * layout.coordSize : 0);
        if (mode & layout.FREEING) {
            assert.equal(state().count, 0);
            assert.ok(state().coords.every(byte => byte === 0));
        } else assert.deepEqual(state(), before);
        if (writing) {
            call('init');
            const restored = call('rest');
            assert.equal(restored[1], restored[0]); assert.equal(restored[1], 0);
            assert.deepEqual(state(), before);
            const after = serialization();
            assert.deepEqual(after.bytes, saved.bytes);
            assert.equal(after.trace, saved.trace.replaceAll('out:', 'in:'));
        }
    }
}

// Original guard accepts exactly100, rejects >100, and does not reject negatives.
for (const [count, point] of [[101, 0], [0, 101], [100, 100], [0, 100], [-1, -1], [0, -1]]) {
    call('init');
    for (let i = 0; i < 100; i++) hero(i, i);
    call('save', layout.WRITING);
    call('corrupt_counts', count, point);
    const results = call('rest');
    assert.equal(results[1], results[0]);
    const error = count > 100 || point > 100;
    assert.equal(results[1], error ? -1 : 0);
    const messages = modules.map(module => cstring(module, module._probe_panic_message()));
    assert.equal(messages[1], messages[0]);
    assert.equal(messages[1], error ? 'rest_track: impossible pt counts' : '');
    scope();
}

call('init');
for (const [x, y] of [[-32768, -32768], [32767, 32767], [-1, 0], [80, 21]]) {
    hero(x, y); query(x, y);
}
const old = modules.map(module => memoryCheckpoint(module));
modules.forEach(module => module._malloc(40n * 1024n * 1024n));
modules.forEach((module, i) => assertMemoryGrowth(module, old[i]));
state(); hero(5, 5); query(6, 6);
call('save', layout.WRITING | layout.FREEING);
assert.deepEqual(call('rest'), [0, 0]);
serialization();

const independentRuntime = createPortedRuntime(layouts);
const independent = await hybridFactory({ nethackPorted: independentRuntime });
const before = state();
independent._probe_init(); independent._probe_hero(1, 2, -1, -1); independent._probe_set();
assert.equal(independentRuntime.trackState.utcnt, 1);
assert.deepEqual(state(), before);
scope();
console.log(`TRACK: ${comparisons} ${referenceLabel}/hybrid ring-buffer, pointer and serialization comparisons checked.`);
