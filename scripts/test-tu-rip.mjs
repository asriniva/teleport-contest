import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import referenceFactory from '../.cache/tu-probes/rip-reference.mjs';
import hybridFactory from '../.cache/tu-probes/rip-hybrid.mjs';
import { createPortedRuntime } from '../js/ported/wasm-runtime.js';
import { C, R, T } from '../js/ported/c-runtime.js';

const layouts = JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json', import.meta.url)));
const layout = layouts.rip;
const modules = [await referenceFactory(), await hybridFactory({ nethackPorted: createPortedRuntime(layouts) })];
let comparisons = 0;
function scope() { assert.equal(C, undefined); assert.equal(R, undefined); assert.equal(T, undefined); }
function bytes(module, pointer) {
    let end = Number(pointer);
    while (module.HEAPU8[end]) end++;
    return Buffer.from(module.HEAPU8.slice(Number(pointer), end));
}
function text(module, value) {
    const data = Buffer.isBuffer(value) ? value : Buffer.from(value);
    const pointer = module._malloc(BigInt(data.length + 1));
    module.HEAPU8.set(data, Number(pointer));
    module.HEAPU8[Number(pointer) + data.length] = 0;
    return pointer;
}
function inputs(module, name, money, death, date) {
    const namePointer = text(module, name), deathPointer = text(module, death);
    module._probe_inputs(BigInt(namePointer), money, BigInt(deathPointer), date);
    module._free(namePointer); module._free(deathPointer);
}
function snapshot(module) {
    return {
        head: Number(module._probe_head()),
        killer: { how: module._probe_killer_how(), format: module._probe_killer_format(), calls: module._probe_killer_calls(), size: module._probe_killer_size() },
        date: { calls: module._probe_date_calls(), argument: module._probe_date_argument() },
        output: Array.from({ length: module._probe_line_count() }, (_, i) => ({
            window: module._probe_line_window(i), attribute: module._probe_line_attribute(i),
            dump: module._probe_line_dump(i), live: module._probe_line_live(i),
            bytes: bytes(module, module._probe_line_text(i)).toString('hex'),
        })),
    };
}
modules.forEach(module => {
    assert.equal(Number(module._probe_context_size()), layout.pointerSize);
    assert.equal(module._probe_bufsz(), layout.BUFSZ);
    assert.equal(module._probe_dumplog(), layout.DUMPLOG);
    assert.equal(module._probe_dedication(), layout.NH320_DEDICATION);
    assert.equal(module._probe_long_size(), 8);
    assert.equal(module._probe_time_size(), 8);
});
function run({ name = 'Player', money = 100n, death = 'killed by a newt', date = 20261109n, window = 1, how = 0, when = 1777723200n } = {}) {
    window |= 0; // C winid has no distinct negative zero.
    const results = modules.map(module => {
        inputs(module, name, money, death, date);
        const stack = module._probe_stack();
        module._probe_run(window, how, when);
        assert.equal(module._probe_stack(), stack, 'C/JS wrappers must restore the stack');
        return snapshot(module);
    });
    assert.deepEqual(results[1], results[0]); scope(); comparisons++;
    const result = results[0];
    assert.equal(result.head, 0, 'All tombstone lines and the pointer table are freed');
    assert.deepEqual(result.killer, { how, format: 0, calls: 1, size: layout.BUFSZ });
    assert.deepEqual(result.date, { calls: 1, argument: when });
    assert.equal(result.output.length, layout.DUMPLOG && window === 0 ? 17 : 18);
    result.output.forEach(line => { assert.equal(line.attribute, 0); assert.equal(line.live, 1); });
    assert.equal(result.output[0].dump, layout.DUMPLOG && window === 0 ? 1 : 0);
    assert.equal(Buffer.from(result.output[0].bytes, 'hex').toString(), layout.DUMPLOG && window === 0 ? 'Game over:' : '');
    for (const line of result.output.slice(1)) { assert.equal(line.window, window); assert.equal(line.dump, 0); }
    const rawName = Buffer.isBuffer(name) ? name : Buffer.from(name);
    const clippedName = rawName.subarray(0, Math.min(16, modules[0]._probe_plname_size() - 1));
    assert.ok(Buffer.from(result.output[7].bytes, 'hex').includes(clippedName), 'Name is clipped to sixteen bytes');
    const cash = money < 0n ? 0n : money > 999999999n ? 999999999n : money;
    assert.ok(Buffer.from(result.output[8].bytes, 'hex').includes(Buffer.from(`${cash} Au`)));
    const year = (date / 10000n) % 10000n;
    assert.ok(Buffer.from(result.output[13].bytes, 'hex').includes(Buffer.from(String(year).padStart(4))));
    comparisons++;
    return result;
}
run();
for (const name of ['', 'a', '123456789012345', '1234567890123456', '12345678901234567', 'x'.repeat(100), Buffer.from([0xff, 0x80, 0xc3, 0xa9, 0x41, 0x20])]) {
    run({ name });
}
for (const money of [-9223372036854775808n, -123n, -1n, 0n, 1n, 999999998n, 999999999n, 1000000000n, 9223372036854775807n]) {
    for (const window of [0, 1, -1, 12345]) run({ money, window });
}
for (const date of [-9223372036854775808n, -20261109n, -10000n, -1n, 0n, 10000n, 99991231n, 100001231n, 9223372036854775807n]) {
    run({ date, when: date });
}
const deathStrings = [
    '', 'a', '123456789012345', '1234567890123456', '12345678901234567',
    'one two three four five six seven eight nine ten eleven twelve',
    ' '.repeat(64), '              a b', 'a               b', 'a                b',
    '1234567890123456 word', '123456789012345  word', 'ends with space ',
    'a'.repeat(layout.BUFSZ - 1), ('ab '.repeat(layout.BUFSZ)).slice(0, layout.BUFSZ - 1),
    Buffer.from([0xff, 0x80, 0xc3, 0xa9, 0x20, 0xfe, 0x20, 0x41]),
];
for (const death of deathStrings) {
    for (const how of [-2147483648, -1, 0, 1, 99, 2147483647]) run({ death, how, window: how % 2 });
}
for (let i = 0; i < 100; i++) {
    const death = Array.from({ length: Math.min(layout.BUFSZ - 1, i * 3) }, (_, j) => (j + i) % 13 === 0 ? ' ' : String.fromCharCode(65 + (j % 26))).join('');
    run({ name: `Player ${i}`, money: BigInt(i) * 123456789n, death, date: BigInt(10000 * i + 101), window: i % 3, how: i, when: BigInt(-i) });
}
const oldBuffers = modules.map(module => module.HEAPU8.buffer);
modules.forEach(module => module._malloc(40n * 1024n * 1024n));
modules.forEach((module, i) => assert.notEqual(module.HEAPU8.buffer, oldBuffers[i]));
run({ name: 'After growth', death: 'killed after memory grew', window: 0 });
const independent = await hybridFactory({ nethackPorted: createPortedRuntime(layouts) });
const before = modules.map(snapshot);
inputs(independent, 'Independent', 42n, 'independent death', 19991231n);
independent._probe_run(3, 19, -123n);
assert.equal(Number(independent._probe_head()), 0);
assert.deepEqual(modules.map(snapshot), before); scope(); comparisons++;
console.log(`RIP: ${comparisons} original-C/hybrid byte-exact tombstone, callback, allocation and stack comparisons passed.`);
