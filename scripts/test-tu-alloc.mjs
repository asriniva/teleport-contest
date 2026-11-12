import { assertStackRestored, allocationMetric, assertMemoryGrowth, memoryCheckpoint, referenceBackend, referenceLabel } from './native-test-backend.mjs';
const referenceFactory = referenceBackend('alloc', emscriptenReferenceFactory);
import assert from './native-test-assert.mjs';
import { readFileSync } from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/alloc-reference.mjs';
import hybridFactory from '../.cache/tu-probes/alloc-hybrid.mjs';
import { createPortedRuntime } from '../js/backends/emscripten/runtime.js';
import { C, R, T, withCEnvironment } from '../js/c-runtime/context.js';

const layouts = JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json', import.meta.url)));
const modules = [await referenceFactory(), await hybridFactory({ nethackPorted: createPortedRuntime(layouts) })];
let comparisons = 0;
const stacks = modules.map(module => module._probe_stack());
function scope() {
    assert.equal(C, undefined); assert.equal(R, undefined); assert.equal(T, undefined);
    modules.forEach((module, i) => assertStackRestored(module, stacks[i], 'Normal and longjmp exits restore C stack'));
}
function cbytes(module, pointer) {
    let end = Number(pointer);
    while (module.HEAPU8[end]) end++;
    return Buffer.from(module.HEAPU8.slice(Number(pointer), end));
}
function allocateText(module, value) {
    const data = Buffer.isBuffer(value) ? value : Buffer.from(value);
    const pointer = module._malloc(BigInt(data.length + 1));
    module.HEAPU8.set(data, Number(pointer)); module.HEAPU8[Number(pointer) + data.length] = 0;
    return pointer;
}
function observed(module, status) {
    return {
        status, pointer: Boolean(module._probe_result()),
        signed: module._probe_signed_result(), unsigned: module._probe_unsigned_result() >>> 0,
        malloc: module._probe_malloc_calls(), realloc: module._probe_realloc_calls(),
        requested: BigInt(module._probe_requested()), panic: cbytes(module, module._probe_panic_message()).toString('latin1'),
    };
}
function operation(callback) {
    const values = modules.map((module, i) => observed(module, callback(module, i)));
    assert.deepEqual(values[1], values[0]); scope(); comparisons++;
    return values[0];
}
function pointers() { return modules.map(module => module._probe_result()); }
function free(values) { modules.forEach((module, i) => { if (values[i]) module._free(Number(values[i])); }); }
function aligned(length) {
    let value = BigInt(length >>> 0);
    if (value === 0n || value % 8n) value += 8n - value % 8n;
    return BigInt.asUintN(32, value);
}
modules.forEach(module => {
    assert.equal(module._probe_long_size(), 8); assert.equal(module._probe_int_size(), 4);
    assert.equal(module._probe_lua_integer_size(), 8); assert.equal(module._probe_ull_size(), 8);
    assert.equal(module._probe_monitor_heap(), 0);
    assert.equal(module._probe_ptrbuf_count(), 4); assert.equal(module._probe_ptrbuf_size(), 32);
});
for (const length of [0, 1, 2, 7, 8, 9, 15, 16, 17, 31, 32, 33, 63, 64, 65, 255, 256, 257, 4095, 4096, 4097]) {
    const value = operation(module => module._probe_alloc(length, 0));
    assert.equal(value.status, 0); assert.equal(value.pointer, true);
    assert.equal(value.malloc, 1); assert.equal(value.realloc, 0); assert.equal(value.requested, aligned(length));
    const allocated = pointers();
    modules.forEach((module, i) => { assert.equal(Number(allocated[i]) % 8, 0); module.HEAPU8.fill(0xa5, Number(allocated[i]), Number(allocated[i]) + Number(value.requested)); });
    free(allocated);
    const failure = operation(module => module._probe_alloc(length, 1));
    assert.equal(failure.status, -1); assert.equal(failure.pointer, false);
    assert.equal(failure.panic, `Memory allocation failure; cannot get ${aligned(length)} bytes`);
}
// uint32 rounding itself wraps; test huge requests only with injected failure.
for (const length of [2147483647, 2147483648, 4294967287, 4294967288, 4294967289, 4294967294, 4294967295]) {
    const result = operation(module => module._probe_alloc(length, 1));
    assert.equal(result.status, -1); assert.equal(result.requested, aligned(length));
    assert.equal(result.panic, `Memory allocation failure; cannot get ${aligned(length)} bytes`);
}
for (const initial of [0, 1, 7, 8, 17, 255, 4097]) {
    operation(module => module._probe_alloc(initial, 0));
    let current = pointers(), used = Number(aligned(initial));
    modules.forEach((module, i) => {
        for (let j = 0; j < used; j++) module.HEAPU8[Number(current[i]) + j] = (j * 13 + 7) & 255;
    });
    for (const length of [used + 100, 8, 0, 513, 17]) {
        const oldData = modules.map((module, i) => Buffer.from(module.HEAPU8.slice(Number(current[i]), Number(current[i]) + used)));
        const result = operation((module, i) => module._probe_realloc(BigInt(current[i]), length, 0));
        assert.equal(result.status, 0); assert.equal(result.pointer, true); assert.equal(result.realloc, 1);
        assert.equal(result.requested, aligned(length));
        current = pointers();
        const nextUsed = Number(aligned(length)), preserved = Math.min(used, nextUsed);
        modules.forEach((module, i) => {
            assert.deepEqual(Buffer.from(module.HEAPU8.slice(Number(current[i]), Number(current[i]) + preserved)), oldData[i].subarray(0, preserved));
            for (let j = 0; j < nextUsed; j++) module.HEAPU8[Number(current[i]) + j] = (j * 13 + 7) & 255;
        });
        used = nextUsed;
    }
    for (const length of [0, 1, 16, 999, 4294967288, 4294967289, 4294967295]) {
        const before = modules.map((module, i) => Buffer.from(module.HEAPU8.slice(Number(current[i]), Number(current[i]) + used)));
        const result = operation((module, i) => module._probe_realloc(BigInt(current[i]), length, 1));
        assert.equal(result.requested, aligned(length)); assert.equal(result.pointer, false);
        assert.equal(result.status, aligned(length) ? -1 : 0);
        assert.equal(result.panic, aligned(length) ? `Memory allocation failure; cannot extend to ${aligned(length)} bytes` : '');
        modules.forEach((module, i) => assert.deepEqual(Buffer.from(module.HEAPU8.slice(Number(current[i]), Number(current[i]) + used)), before[i], 'Failed realloc leaves old storage intact'));
    }
    free(current);
}
operation(module => module._probe_realloc(0n, 13, 0)); free(pointers());

for (const source of ['', 'abc', 'x'.repeat(4097), Buffer.from([0xff, 0x80, 0xc3, 0xa9]), Buffer.from([65, 0, 66, 67])]) {
    const input = modules.map(module => allocateText(module, source));
    const data = Buffer.isBuffer(source) ? source : Buffer.from(source);
    const end = data.indexOf(0), expected = end < 0 ? data : data.subarray(0, end);
    const result = operation((module, i) => module._probe_dup(BigInt(input[i]), 0));
    assert.equal(result.status, 0); assert.equal(result.requested, aligned(expected.length + 1));
    const copied = pointers();
    modules.forEach((module, i) => {
        assert.notEqual(Number(copied[i]), Number(input[i]));
        assert.deepEqual(cbytes(module, copied[i]), expected);
        module.HEAPU8[Number(input[i])] = 90;
        assert.deepEqual(cbytes(module, copied[i]), expected, 'dupstr owns separate storage');
        module.HEAPU8[Number(input[i])] = data[0] ?? 0;
    });
    free(copied);
    const failure = operation((module, i) => module._probe_dup(BigInt(input[i]), 1));
    assert.equal(failure.status, -1); free(input);
}
const files = modules.map(module => allocateText(module, 'source-file.c'));
for (const value of [-9223372036854775808n, -2147483649n, -2147483648n, -1n, 0n, 1n, 2147483647n, 2147483648n, 9223372036854775807n]) {
    const result = operation((module, i) => module._probe_signed(value, BigInt(files[i]), -123));
    const valid = value >= -2147483648n && value <= 2147483647n;
    assert.equal(result.status, valid ? 0 : -1);
    assert.equal(result.panic, valid ? '' : 'Overflow at source-file.c:-123');
    if (valid) assert.equal(result.signed, Number(value));
}
for (const value of [0n, 1n, 2147483647n, 2147483648n, 4294967295n, 4294967296n, 1n << 63n, (1n << 64n) - 1n]) {
    const result = operation((module, i) => module._probe_unsigned(value, BigInt(files[i]), 2147483647));
    const valid = value <= 4294967295n;
    assert.equal(result.status, valid ? 0 : -1);
    assert.equal(result.panic, valid ? '' : 'Overflow at source-file.c:2147483647');
    if (valid) assert.equal(result.unsigned, Number(value));
}
free(files);

// The formatter accepts opaque full-width pointer bit patterns without ever
// dereferencing them. Compare all bytes and the four-slot overwrite behavior.
const addresses = [0n, 1n, 0x12345678n, (1n << 53n) - 1n, (1n << 53n) + 1n, 1n << 63n, (1n << 64n) - 1n];
const formattedPointers = [[], []];
for (let i = 0; i < addresses.length * 4; i++) {
    const results = modules.map((module, m) => {
        const result = module._probe_format(addresses[i % addresses.length]);
        formattedPointers[m].push(result);
        if (i >= 4) assert.equal(result, formattedPointers[m][i - 4]);
        if (i > 0 && i < 4) assert.notEqual(result, formattedPointers[m][i - 1]);
        return cbytes(module, result);
    });
    assert.deepEqual(results[1], results[0]); scope(); comparisons++;
}
const oldBuffers = modules.map(module => memoryCheckpoint(module));
modules.forEach(module => module._malloc(40n * 1024n * 1024n));
modules.forEach((module, i) => assertMemoryGrowth(module, oldBuffers[i]));
operation(module => module._probe_alloc(128, 0)); free(pointers());
const after = modules.map(module => cbytes(module, module._probe_format(0xabcdefn)));
assert.deepEqual(after[1], after[0]); scope(); comparisons++;
const independent = await hybridFactory({ nethackPorted: createPortedRuntime(layouts) });
const oldText = cbytes(modules[1], formattedPointers[1].at(-1));
independent._probe_format(0x999n); independent._probe_format(0x888n);
assert.deepEqual(cbytes(modules[1], formattedPointers[1].at(-1)), oldText); scope(); comparisons++;
// An existing translated caller has an active dependency scope when it
// reenters C and then this translated allocator. Restore that outer scope on
// both ordinary return and the C panic/longjmp path.
const outer = { rectState: { sentinel: 'rect' }, trackState: { sentinel: 'track' } };
withCEnvironment(outer, () => {
    function restored() {
        assert.equal(C, outer); assert.equal(R, outer.rectState); assert.equal(T, outer.trackState);
        assert.equal(modules[1]._probe_stack(), stacks[1]); comparisons++;
    }
    assert.equal(modules[1]._probe_alloc(31, 0), 0);
    restored();
    const pointer = modules[1]._probe_result();
    modules[1]._free(Number(pointer));
    assert.equal(modules[1]._probe_alloc(31, 1), -1);
    assert.equal(cbytes(modules[1], modules[1]._probe_panic_message()).toString(), 'Memory allocation failure; cannot get 32 bytes');
    restored();
});
scope();
console.log(`ALLOC: ${comparisons} ${referenceLabel}/hybrid alignment, memory, failure, pointer-pool and integer-cast comparisons checked.`);
