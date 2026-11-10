import { DataView, Uint8Array, assertStackRestored, allocationMetric, assertMemoryGrowth, memoryCheckpoint, referenceBackend, referenceLabel } from './native-test-backend.mjs';
const referenceFactory = referenceBackend('nhmd4', emscriptenReferenceFactory);
import assert from './native-test-assert.mjs';
import { readFileSync } from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/nhmd4-reference.mjs';
import hybridFactory from '../.cache/tu-probes/nhmd4-hybrid.mjs';
import { createPortedRuntime } from '../js/ported/wasm-runtime.js';

const layouts = JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json', import.meta.url)));
const layout = layouts.nhmd4;
const modules = [await referenceFactory(), await hybridFactory({ nethackPorted: createPortedRuntime(layouts) })];
let comparisons = 0;
function contexts() {
    return modules.map(module => {
        const pointer = module._malloc(BigInt(layout.size));
        // init intentionally leaves buffer/block alone, so compare nonzero initial storage.
        module.HEAPU8.fill(0xa5, Number(pointer), Number(pointer) + layout.size);
        module._probe_init(BigInt(pointer));
        return pointer;
    });
}
function state(pointers) {
    const values = modules.map((module, i) => Buffer.from(module.HEAPU8.slice(Number(pointers[i]), Number(pointers[i]) + layout.size)));
    assert.deepEqual(values[1], values[0]);
    comparisons++;
}
function update(pointers, data) {
    for (const [i, module] of modules.entries()) {
        // Deliberately unaligned data pointer: the C source supports unaligned input.
        const allocation = module._malloc(BigInt(data.length + 1));
        const pointer = BigInt(allocation) + 1n;
        module.HEAPU8.set(data, Number(pointer));
        module._probe_update(BigInt(pointers[i]), pointer, BigInt(data.length));
        module._free(allocation);
    }
    state(pointers);
}
function final(pointers, expected) {
    const digests = modules.map((module, i) => {
        const pointer = module._malloc(16n);
        module._probe_final(BigInt(pointers[i]), BigInt(pointer));
        const result = Buffer.from(module.HEAPU8.slice(Number(pointer), Number(pointer) + 16)).toString('hex');
        module._free(pointer);
        assert.ok(module.HEAPU8.subarray(Number(pointers[i]), Number(pointers[i]) + layout.size).every(byte => byte === 0));
        return result;
    });
    assert.equal(digests[1], digests[0]);
    if (expected) assert.equal(digests[1], expected);
    state(pointers);
    comparisons++;
    return digests[1];
}
function release(pointers) {
    modules.forEach((module, i) => module._free(pointers[i]));
}
const vectors = [
    ['', '31d6cfe0d16ae931b73c59d7e0c089c0'],
    ['a', 'bde52cb31de33e46245e05fbdbd6fb24'],
    ['abc', 'a448017aaf21d8525fc10ae87aa6729d'],
    ['message digest', 'd9130a8164549fe818874806e1c7014b'],
    ['abcdefghijklmnopqrstuvwxyz', 'd79e1c308aa5bbcdeea8ed63df412da9'],
    ['ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789', '043f8582f241db351ce627e153e7f0e4'],
    ['1234567890'.repeat(8), 'e33b4ddc9c38f2199c3e7b164fcc0536'],
    ['a'.repeat(1000000), 'bbce80cc6bb65e5c6745e30d4eeca9a4'],
];
for (const [text, expected] of vectors) {
    for (const chunkSize of [1, 7, 55, 56, 63, 64, 65, 127, 4096]) {
        if (text.length > 1000 && chunkSize < 4096) continue;
        const pointers = contexts(), data = Buffer.from(text);
        state(pointers);
        update(pointers, new Uint8Array());
        for (let j = 0; j < data.length; j += chunkSize) update(pointers, data.subarray(j, j + chunkSize));
        final(pointers, expected);
        release(pointers);
    }
}
for (const length of [0, 1, 54, 55, 56, 57, 63, 64, 65, 119, 120, 127, 128, 129, 1023, 4097]) {
    const data = Uint8Array.from({ length }, (_, i) => (i * 173 + length) & 255);
    let expected;
    for (const chunks of [[length || 1], [1, 0, 63, 5, 64, 17], [55, 1, 8, 129]]) {
        const pointers = contexts();
        for (let offset = 0, j = 0; offset < length; j++) {
            const amount = Math.min(chunks[j % chunks.length], length - offset);
            update(pointers, data.subarray(offset, offset + amount));
            offset += amount;
        }
        expected = final(pointers, expected);
        release(pointers);
    }
}
// Exercise counter carry without constructing a half-gigabyte input, and preserve
// complete C state across copies, independent contexts, and Wasm memory growth.
const pointers = contexts(), copies = contexts(), independent = contexts();
update(pointers, Uint8Array.from({ length: 61 }, (_, i) => i));
update(independent, Uint8Array.of(9, 8, 7));
for (const [i, module] of modules.entries()) {
    const view = new DataView(module.HEAPU8.buffer);
    view.setUint32(Number(pointers[i]) + layout.lo, 0x1ffffffd, true);
    view.setUint32(Number(pointers[i]) + layout.hi, 0xffffffff, true);
    module.HEAPU8.copyWithin(Number(copies[i]), Number(pointers[i]), Number(pointers[i]) + layout.size);
    const previous = memoryCheckpoint(module);
    module._malloc(40n * 1024n * 1024n);
    assertMemoryGrowth(module, previous);
}
update(pointers, Uint8Array.of(1, 2, 3, 4));
update(independent, Uint8Array.of(5, 6));
update(copies, Uint8Array.of(1, 2, 3, 4));
const digest = final(pointers);
final(copies, digest);
final(independent);
console.log(`NHMD4: ${comparisons} ${referenceLabel}/hybrid state and digest comparisons checked, including RFC vectors.`);
