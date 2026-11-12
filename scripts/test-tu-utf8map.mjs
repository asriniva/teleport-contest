import { DataView, assertStackRestored, allocationMetric, assertMemoryGrowth, memoryCheckpoint, referenceBackend, referenceLabel } from './native-test-backend.mjs';
const referenceFactory = referenceBackend('utf8map', emscriptenReferenceFactory);
import assert from './native-test-assert.mjs';
import { readFileSync } from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/utf8map-reference.mjs';
import hybridFactory from '../.cache/tu-probes/utf8map-hybrid.mjs';
import { createPortedRuntime } from '../js/backends/emscripten/runtime.js';
import { C, R, T } from '../js/c-runtime/context.js';

const layouts = JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json', import.meta.url)));
const layout = layouts.utf8map;
const modules = [await referenceFactory(), await hybridFactory({ nethackPorted: createPortedRuntime(layouts) })];
const stacks = modules.map(module => module._probe_stack());
const tracked = new Set([0, 1, 2, 3, 7, layout.MAX_GLYPH - 1]);
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
function allocate(module, value) {
    if (value === null) return 0;
    const data = Buffer.isBuffer(value) ? value : Buffer.from(value);
    const pointer = module._malloc(BigInt(data.length + 1));
    module.HEAPU8.set(data, Number(pointer)); module.HEAPU8[Number(pointer) + data.length] = 0;
    return pointer;
}
modules.forEach(module => {
    assert.equal(Number(module._probe_context_size()), layout.GlyphMapSize);
    for (let i = 0; i < module._probe_layout_count(); i++) {
        const key = bytes(module, module._probe_layout_name(i)).toString();
        assert.equal(Number(module._probe_layout_value(i)), layout[key], key);
    }
});
function details(module, which) {
    const result = [], seen = new Set();
    let pointer = module._probe_custom_head(which);
    while (pointer) {
        assert.ok(!seen.has(pointer)); seen.add(pointer);
        result.push({ pointer, glyph: module._probe_detail_glyph(BigInt(pointer)), code: module._probe_detail_code(BigInt(pointer)) >>> 0,
            text: bytes(module, module._probe_detail_text(BigInt(pointer)))?.toString('hex') ?? null });
        pointer = module._probe_detail_next(BigInt(pointer));
    }
    assert.equal(Number(module._probe_custom_end(which)), result.length ? Number(result.at(-1).pointer) : 0, 'Tail aliases the actual last node');
    return result;
}
function snapshot(module) {
    return {
        maps: [...tracked].map(index => ({ index, present: Boolean(module._probe_map_u(index)), code: module._probe_map_code(index) >>> 0,
            text: bytes(module, module._probe_map_text(index))?.toString('hex') ?? null })),
        gbuf: module._probe_gbuf_count(),
        custom: Array.from({ length: layout.NUM_GRAPHICS }, (_, which) => ({
            name: bytes(module, module._probe_custom_name(which))?.toString('hex') ?? null,
            count: module._probe_custom_count(which), type: module._probe_custom_type(which),
            details: details(module, which).map(({ pointer, ...data }) => data),
        })),
        trace: bytes(module, module._probe_trace()).toString('hex'),
    };
}
function state() {
    const result = modules.map(snapshot);
    assert.deepEqual(result[1], result[0]); scope(); comparisons++;
    return result[0];
}
function call(name, ...args) {
    modules.forEach(module => module._probe_clear_trace());
    const result = modules.map(module => module['_probe_' + name](...args));
    assert.deepEqual(result[1], result[0]); state(); comparisons++;
    return result[0];
}
function set(index, code, text) {
    if (index >= 0) tracked.add(index);
    const result = modules.map(module => {
        module._probe_clear_trace();
        const pointer = allocate(module, text);
        const status = module._probe_set(index, code, BigInt(pointer));
        if (pointer) module._free(pointer);
        return status;
    });
    assert.equal(result[1], result[0]); state(); comparisons++;
    return result[0];
}
for (const value of [null, '', 'U+', 'u+', 'U+0', 'u+0041', 'U+10FFFF', 'U+abcdef0', 'U+ABCDEF01',
    'U+123456789', 'U+00000001', 'U+41junk', 'U+1 2', 'U+g', 'U+0x41', 'u-1234', ' U+41', Buffer.from([0xff, 0x80])]) {
    const result = modules.map(module => {
        const pointer = allocate(module, value); const number = module._probe_unicode(BigInt(pointer));
        if (pointer) module._free(pointer); return number;
    });
    assert.equal(result[1], result[0]); scope(); comparisons++;
}
// set_map_u's C declaration marks pointer arguments nonnull; do not pass
// null despite its defensive source check, which Clang can optimize away.
assert.equal(set(1, 0, 'ignored'), 0);
for (const index of [0, 1, 2, 7, layout.MAX_GLYPH - 1]) {
    assert.equal(set(index, 0x2603 + index, Buffer.from([0xff, 0x80, 65 + index % 26])), 1);
    const old = modules.map(module => module._probe_map_u(index));
    assert.equal(set(index, 0xffffffff, ''), 1);
    modules.forEach((module, i) => assert.equal(module._probe_map_u(index), old[i], 'Representation struct reused on replacement'));
    const before = state(); assert.equal(set(index, 0, 'ignored'), 0); assert.deepEqual(state().maps, before.maps);
}
set(1, 0x2603, Buffer.from([0xe2, 0x98, 0x83]));
set(2, 0x41, '');
call('fallback', 1, 65); call('fallback', 2, 66); call('fallback', 3, 0xfe);
function mixed(input, capacity, flagPointer = true, inPlace = false) {
    const result = modules.map(module => {
        module._probe_clear_trace();
        const raw = input === null ? Buffer.alloc(0) : Buffer.isBuffer(input) ? input : Buffer.from(input);
        const length = Math.max(capacity, raw.length + 1, 1) + 32;
        const allocation = module._malloc(BigInt(length));
        module.HEAPU8.fill(0xa5, Number(allocation), Number(allocation) + length);
        const out = Number(allocation) + 8;
        let source = 0;
        if (inPlace) { module.HEAPU8.set(raw, out); module.HEAPU8[out + raw.length] = 0; source = out; }
        else source = allocate(module, input);
        const flags = module._malloc(4n); new DataView(module.HEAPU8.buffer).setInt32(Number(flags), 12345, true);
        const returned = module._probe_mixed(BigInt(out), BigInt(capacity), BigInt(source), flagPointer ? BigInt(flags) : 0n);
        assert.equal(Number(returned), out, 'mixed_to_utf8 returns the original buffer');
        assert.ok(module.HEAPU8.slice(Number(allocation), out).every(value => value === 0xa5));
        assert.ok(module.HEAPU8.slice(out + Math.max(capacity, inPlace ? raw.length + 1 : 1), Number(allocation) + length).every(value => value === 0xa5));
        const result = { output: bytes(module, BigInt(out)).toString('hex'), flags: new DataView(module.HEAPU8.buffer).getInt32(Number(flags), true),
            trace: bytes(module, module._probe_trace()).toString('hex') };
        if (!inPlace && source) module._free(source);
        module._free(flags); module._free(allocation);
        return result;
    });
    assert.deepEqual(result[1], result[0]); state(); comparisons++;
    return result[0];
}
const strings = [null, '', 'plain bytes', '\\', '\\\\', '\\x', '\\G', '\\GABCD0001', '\\GABCD0002', '\\GABCD0003',
    'before\\GABCD0001after', '\\GABCD0001\\GABCD0003', '\\GABCD0003\\GABCD0001', '\\GFFFF0001', '\\GABCDzzzz',
    '\\GABCD0001\\', '\\\\GABCD0001', Buffer.from([0xff, 0x80, 0xc3, 0xa9])];
for (const input of strings) for (const capacity of [0, 1, 2, 3, 4, 8, 16, 64]) {
    mixed(input, capacity); mixed(input, capacity, false);
}
for (const input of ['', 'plain', '\\\\', '\\GABCD0001', 'x\\GABCD0001y']) mixed(input, 64, true, true);
assert.equal(mixed('plain', 64).flags, 12345, 'Raw text leaves flags untouched');
assert.equal(mixed('\\GABCD0001', 64).flags, 1);
assert.equal(mixed('\\GABCD0003', 64).flags, 0);
call('null_text', 1); assert.equal(mixed('\\GABCD0001', 64).flags, 0);
for (const [x, y] of [[0, 0], [layout.COLNO - 1, layout.ROWNO - 1], [4, 3]]) call('gbuf', x, y, 7);
assert.equal(state().gbuf, 3); call('free'); assert.equal(state().gbuf, 0);
assert.ok(state().maps.every(map => !map.present)); call('free');

function custom(name, glyph, code, text, which) {
    const result = modules.map(module => {
        module._probe_clear_trace();
        const n = allocate(module, name), t = allocate(module, text);
        const result = module._probe_custom(BigInt(n), glyph, code, BigInt(t), which);
        module._free(n); if (t) module._free(t); return result;
    });
    assert.equal(result[1], result[0]); state(); comparisons++;
}
for (let which = 0; which < layout.NUM_GRAPHICS; which++) {
    custom('main', 10, 0x41, 'A', which);
    custom('main', 11, 0x2603, Buffer.from([0xff, 0x80]), which);
    const before = modules.map(module => details(module, which).map(entry => entry.pointer));
    custom('main', 10, 0x42, 'B', which);
    modules.forEach((module, i) => assert.deepEqual(details(module, which).map(entry => entry.pointer), before[i], 'Update reuses the existing detail node'));
    custom('main', 10, 0, null, which);
    assert.equal(state().custom[which].count, 2, 'Deleting representation keeps its detail node/count');
    custom('main', 12, 0, 'nonempty', which);
    custom('main', 13, 0x43, '', which);
    custom('other', 11, 0x44, 'D', which);
    assert.equal(state().custom[which].count, 5, 'Mismatched customization name appends rather than updates');
    for (let i = 0; i < 20; i++) custom('main', 100 + i, i % 2 ? 0 : 0x10000 + i, i % 2 ? null : `entry-${i}`, which);
}
set(7, 0x1234, 'before reset'); call('gbuf', 3, 4, 7);
call('reset', layout.PRIMARYSET, 0); assert.equal(state().gbuf, 0); assert.ok(state().maps.every(map => !map.present));
assert.equal(Buffer.from(state().trace, 'hex').toString(), `apply:${layout.PRIMARYSET}:${layout.do_custom_symbols}:live=0;`);
call('reset', layout.ROGUESET, 1);
assert.equal(state().maps.find(map => map.index === 7).text, Buffer.from('SNOW').toString('hex'), 'Nested customization callback can reenter set_map_u');
const oldBuffers = modules.map(module => memoryCheckpoint(module));
modules.forEach(module => module._malloc(40n * 1024n * 1024n));
modules.forEach((module, i) => assertMemoryGrowth(module, oldBuffers[i]));
state(); set(1, 0x41, 'after growth'); mixed('\\GABCD0001', 64); custom('main', 10, 0x99, 'grown', 0); call('reset', 0, 1);
const independent = await hybridFactory({ nethackPorted: createPortedRuntime(layouts) });
const before = state();
const pointer = allocate(independent, 'Independent'); independent._probe_set(1, 0x41, BigInt(pointer)); independent._free(pointer);
independent._probe_reset(0, 1); independent._probe_cleanup();
assert.deepEqual(state(), before); call('cleanup'); scope(); comparisons++;
console.log(`UTF8MAP: ${comparisons} ${referenceLabel}/hybrid parser, raw-byte, map, customization, callback and lifecycle comparisons checked.`);
