import './pure-js-probes/deny-wasm.mjs';
import { DataView, assertStackRestored, allocationMetric, assertMemoryGrowth, memoryCheckpoint, referenceBackend, referenceLabel } from './native-test-backend.mjs';
const referenceFactory = referenceBackend('isaac64', emscriptenReferenceFactory);
import assert from './native-test-assert.mjs';
import { readFileSync } from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/isaac64-reference.mjs';
import createPureJsProbe from './pure-js-probes/crypto.mjs';

const layouts = JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json', import.meta.url)));
const reference = await referenceFactory();
const hybrid = await createPureJsProbe('isaac64', layouts);
const modules = [reference, hybrid];
const size = layouts.isaac64.size;
const unsigned = value => BigInt.asUintN(64, value);
let comparisons = 0;
function contexts() {
    return modules.map(module => {
        const pointer = module._malloc(BigInt(size));
        module.HEAPU8.fill(0, Number(pointer), Number(pointer) + size);
        return pointer;
    });
}
function equalState(pointers) {
    const states = modules.map((module, i) => Buffer.from(module.HEAPU8.slice(
        Number(pointers[i]), Number(pointers[i]) + size)));
    assert.deepEqual(states[1], states[0]);
    comparisons++;
}
function seed(pointers, length, reseed = false) {
    for (const [i, module] of modules.entries()) {
        const pointer = module._malloc(2100n);
        for (let j = 0; j < 2100; j++) module.HEAPU8[Number(pointer) + j] = (j * 73 + length * 19) & 255;
        module[reseed ? '_probe_reseed' : '_probe_init'](BigInt(pointers[i]), BigInt(pointer), length);
        module._free(pointer);
    }
    equalState(pointers);
}
function draw(pointers, count, bound) {
    for (let j = 0; j < count; j++) {
        const values = modules.map((module, i) => unsigned(bound === undefined
            ? module._probe_next(BigInt(pointers[i])) : module._probe_bounded(BigInt(pointers[i]), bound)));
        assert.equal(values[1], values[0]);
        comparisons++;
        if (j % 256 === 0) equalState(pointers);
    }
    equalState(pointers);
}
for (const length of [-1, 0, 1, 7, 8, 9, 31, 2047, 2048, 2100]) {
    const pointers = contexts();
    seed(pointers, length);
    draw(pointers, 777);
    for (const nextLength of [0, 9, 2048]) {
        seed(pointers, nextLength, true);
        draw(pointers, 271);
    }
    for (const bound of [1n, 2n, 3n, 65537n, 1n << 32n, (1n << 63n) + 1n, (1n << 64n) - 1n]) {
        draw(pointers, 300, bound);
    }
    modules.forEach((module, i) => module._free(pointers[i]));
}
const original = contexts(), other = contexts(), copy = contexts();
seed(original, 17);
seed(other, 39);
draw(original, 19);
for (const [i, module] of modules.entries()) {
    module.HEAPU8.copyWithin(Number(copy[i]), Number(original[i]), Number(original[i]) + size);
}
draw(copy, 600);
draw(other, 600);
draw(original, 600);
equalState(copy);
modules.forEach((module, i) => assert.deepEqual(
    module.HEAPU8.slice(Number(copy[i]), Number(copy[i]) + size),
    module.HEAPU8.slice(Number(original[i]), Number(original[i]) + size)));
// Force an update with the 64-bit counter wrapping, then grow memory between calls.
for (const [i, module] of modules.entries()) {
    const view = new DataView(module.HEAPU8.buffer);
    view.setUint32(Number(original[i]) + layouts.isaac64.n, 0, true);
    for (const field of ['a', 'b', 'c']) view.setBigUint64(Number(original[i]) + layouts.isaac64[field], (1n << 64n) - 1n, true);
    const oldBuffer = memoryCheckpoint(module);
    module._malloc(40n * 1024n * 1024n);
    assertMemoryGrowth(module, oldBuffer);
}
draw(original, 700);
console.log(`ISAAC64: ${comparisons} ${referenceLabel} versus pure-JS output/state comparisons checked.`);
