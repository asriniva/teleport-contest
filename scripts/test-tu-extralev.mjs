import { DataView, Int32Array, assertStackRestored, allocationMetric, assertMemoryGrowth, memoryCheckpoint, referenceBackend, referenceLabel } from './native-test-backend.mjs';
const referenceFactory = referenceBackend('extralev', emscriptenReferenceFactory);
import assert from './native-test-assert.mjs';
import { readFileSync } from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/extralev-reference.mjs';
import hybridFactory from '../.cache/tu-probes/extralev-hybrid.mjs';
import { createPortedRuntime } from '../js/ported/wasm-runtime.js';
import { C, R, T } from '../js/ported/c-runtime.js';

const layouts = JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json', import.meta.url)));
const layout = layouts.extralev;
const modules = [await referenceFactory(), await hybridFactory({ nethackPorted: createPortedRuntime(layouts) })];
const stacks = modules.map(module => module._probe_stack());
let comparisons = 0;
function scope() {
    assert.equal(C, undefined); assert.equal(R, undefined); assert.equal(T, undefined);
    modules.forEach((module, i) => assertStackRestored(module, stacks[i]));
}
function bytes(module, pointer) {
    let end = Number(pointer); while (module.HEAPU8[end]) end++;
    return Buffer.from(module.HEAPU8.slice(Number(pointer), end));
}
function block(module, pointer, length) { return Buffer.from(module.HEAPU8.slice(Number(pointer), Number(pointer) + length)); }
function snapshot(module) {
    return { grid: block(module, module._probe_grid_pointer(), 9 * layout.rogueSize),
        terrain: block(module, module._probe_terrain_pointer(), layout.COLNO * layout.ROWNO * layout.terrainSize),
        rooms: block(module, module._probe_rooms_pointer(), layout.roomSize * layout.roomCount),
        smeq: block(module, module._probe_smeq_pointer(), layout.smeqSize * layout.smeqCount),
        nroom: module._probe_nroom(), rng: module._probe_rng_count(), randomState: module._probe_rng_state() >>> 0,
        ghostSleep: module._probe_ghost_sleep(), renamedSleep: module._probe_renamed_sleep(),
        objects: Array.from({ length: module._probe_object_count() }, (_, i) => ({ type: module._probe_object_type(i), quantity: module._probe_object_quantity(i),
            weight: module._probe_object_weight(i) >>> 0, spe: module._probe_object_spe(i), cursed: module._probe_object_cursed(i),
            known: module._probe_object_known(i), proof: module._probe_object_proof(i) })),
        trace: bytes(module, module._probe_trace()).toString('hex') };
}
function state() { const values = modules.map(snapshot); assert.deepEqual(values[1], values[0]); scope(); comparisons++; return values[0]; }
function call(name, ...args) {
    const result = modules.map(module => module['_probe_' + name](...args));
    assert.deepEqual(result[1], result[0], `${name}(${args})`); state(); comparisons++; return result[0];
}
function rng(values) {
    modules.forEach(module => {
        new Int32Array(module.HEAPU8.buffer, Number(module._probe_rng_pointer()), values.length).set(values);
        module._probe_rng_length(values.length);
    }); state();
}
function field(x, y, name) {
    const module = modules[0], address = Number(module._probe_grid_pointer()) + (x * 3 + y) * layout.rogueSize + layout['r_' + name];
    const size = layout['r_' + name + '_size'];
    return new DataView(module.HEAPU8.buffer)['getInt' + size * 8](address, true);
}
function trace() { return Buffer.from(state().trace, 'hex').toString(); }
modules.forEach(module => {
    assert.equal(Number(module._probe_context_size()), layout.rogueSize);
    for (let i = 0; i < module._probe_layout_count(); i++) {
        const key = bytes(module, module._probe_layout_name(i)).toString(); assert.equal(Number(module._probe_layout_value(i)), layout[key], key);
    }
});
for (const seed of [0, 1, 2, 3, 9, 42, 1234, 65535, 2147483647, 2147483648, 4294967295]) {
    call('reset', seed); call('make');
    assert.ok(state().nroom >= 1 && state().nroom <= 9);
    let real = 0;
    for (let x = 0; x < 3; x++) for (let y = 0; y < 3; y++) { real += field(x, y, 'real') ? 1 : 0; assert.equal(field(x, y, 'doortable'), 0); }
    assert.equal(state().nroom, real);
    assert.ok(!trace().includes('impossible:'), 'Valid room callbacks provide all expected walls');
    call('clear'); call('make');
}
call('reset', 5); rng(Array(180).fill(0)); call('make'); assert.ok(state().nroom > 0, 'All-dummy rolls still force real rooms');
for (const start of [[0, 0], [1, 1], [2, 2]]) {
    call('reset', 42); call('walk', ...start);
    const seen = new Set([start.join(',')]), queue = [start];
    for (let i = 0; i < queue.length; i++) {
        const [x, y] = queue[i], doors = field(x, y, 'doortable');
        for (const [bit, dx, dy, opposite] of [[1, 0, -1, 2], [2, 0, 1, 1], [4, -1, 0, 8], [8, 1, 0, 4]]) if (doors & bit) {
            const nx = x + dx, ny = y + dy; assert.ok(nx >= 0 && nx < 3 && ny >= 0 && ny < 3);
            assert.ok(field(nx, ny, 'doortable') & opposite, 'Each grid connection is reciprocal');
            const key = `${nx},${ny}`; if (!seen.has(key)) { seen.add(key); queue.push([nx, ny]); }
        }
    }
    assert.equal(seen.size, 9, 'The generated passage graph connects all nine cells');
}
for (const args of [[3, 3, 20, 14, 1], [3, 14, 20, 3, 1], [20, 3, 3, 14, 0], [3, 3, 20, 14, 0], [7, 7, 7, 7, 1]]) {
    call('reset', 10); call('join', ...args);
}
// Real/dummy endpoint combinations in both legal corridor directions.
for (const direction of [2, 8]) for (const firstReal of [0, 1]) for (const secondReal of [0, 1]) {
    call('reset', 17);
    const dest = direction === 2 ? [0, 1] : [1, 0];
    call('cell', 0, 0, firstReal, 2, 2, 4, 2, 0, direction);
    call('cell', ...dest, secondReal, 2, 2, 4, 2, 1, direction === 2 ? 1 : 4);
    if (firstReal) call('room', 0, 3, 2, 6, 3);
    if (secondReal) call('room', 1, 1 + 26 * dest[0] + 2, 7 * dest[1] + 2, 1 + 26 * dest[0] + 5, 7 * dest[1] + 3);
    call('clear'); call('corridor', 0, 0, direction);
    assert.ok(!trace().includes('impossible:'));
}
for (const direction of [0, 1, 3, 4, 16]) { call('reset', 1); call('corridor', 0, 0, direction); assert.ok(trace().includes(`corridor in direction ${direction}?`)); }
for (const direction of [2, 8]) {
    call('reset', 1); call('cell', 2, 2, 0, 2, 2, 4, 2, 0, direction); call('corridor', 2, 2, direction);
    assert.ok(trace().includes('going nowhere?'));
}
call('reset', 1); rng([0]); call('corr', 5, 6); assert.equal(call('typ', 5, 6), layout.SCORR);
rng([1]); call('corr', 5, 6); assert.equal(call('typ', 5, 6), layout.CORR);
// corr changes only typ, preserving glyph and all packed wall/door/light
// flags even when every surrounding storage byte is nonzero.
const preserved = modules.map(module => {
    const cell = Number(module._probe_terrain_pointer()) + (5 * layout.ROWNO + 6) * layout.terrainSize;
    module.HEAPU8.fill(0xa5, cell, cell + layout.terrainSize);
    return cell;
});
rng([1]); call('corr', 5, 6);
modules.forEach((module, i) => {
    const raw = module.HEAPU8.slice(preserved[i], preserved[i] + layout.terrainSize);
    raw.forEach((value, offset) => {
        if (offset < layout.terrainType || offset >= layout.terrainType + layout.terrainTypeSize) assert.equal(value, 0xa5);
    });
});
// A different disabled RNG call site must retain the old caller annotation.
call('options', 0, 0, 0); call('clear'); rng([1]); call('join', 3, 3, 8, 5, 1);
assert.ok(trace().includes(':corr;'), 'Disabled join/corr logging retains the prior corr caller');

call('reset', 1); call('ghost'); assert.equal(state().objects.length, 0); assert.equal(state().rng, 0);
for (const fail of [0, 1]) for (const rename of [0, 1]) for (const sequence of [Array(32).fill(0), Array(32).fill(1), Array.from({ length: 32 }, (_, i) => i % 5)]) {
    call('reset', 3); call('room', 0, 3, 3, 8, 6); call('options', fail, rename, 1); call('clear'); rng(sequence); call('ghost');
    const result = state();
    if (fail) { assert.equal(result.objects.length, 0); assert.equal(result.ghostSleep, 0); }
    else {
        assert.equal(result.ghostSleep, 1); assert.equal(result.renamedSleep, rename ? 1 : 0);
        assert.ok(trace().includes('christen:Fixture Rogue:sleep=1;'));
        assert.ok(result.objects.some(object => object.type === layout.ARROW && object.quantity >= 25n && object.quantity <= 34n));
        assert.ok(result.objects.some(object => object.type === layout.BOW && object.spe === 1));
    }
}
// More seeds reach independently selected food/weapon/armor/amulet branches.
const encountered = new Set();
for (let seed = 0; seed < 80; seed++) {
    call('reset', seed); call('room', 0, 3, 3, 8, 6); call('clear'); call('ghost');
    state().objects.forEach(object => encountered.add(object.type));
}
for (const name of ['FOOD_RATION', 'MACE', 'TWO_HANDED_SWORD', 'BOW', 'ARROW', 'RING_MAIL', 'PLATE_MAIL', 'FAKE_AMULET_OF_YENDOR']) assert.ok(encountered.has(layout[name]), name);
const oldBuffers = modules.map(module => memoryCheckpoint(module));
modules.forEach(module => module._malloc(40n * 1024n * 1024n));
modules.forEach((module, i) => assertMemoryGrowth(module, oldBuffers[i]));
call('reset', 123); call('make'); call('ghost');
const independent = await hybridFactory({ nethackPorted: createPortedRuntime(layouts) });
const beforeIndependent = state(); independent._probe_reset(99); independent._probe_make(); independent._probe_ghost();
assert.deepEqual(state(), beforeIndependent); scope(); comparisons++;
console.log(`EXTRALEV: ${comparisons} ${referenceLabel}/hybrid full-grid, room, corridor, recursive-walk, ghost-object and RNG-site comparisons checked.`);
