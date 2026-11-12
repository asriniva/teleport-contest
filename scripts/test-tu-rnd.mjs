import './pure-js-probes/deny-wasm.mjs';
import { BigUint64Array, DataView, Int32Array, assertStackRestored, allocationMetric, assertMemoryGrowth, memoryCheckpoint, referenceBackend, referenceLabel } from './native-test-backend.mjs';
const referenceFactory = referenceBackend('rnd', emscriptenReferenceFactory);
import assert from './native-test-assert.mjs';
import { readFileSync } from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/rnd-reference.mjs';
import createPureJsProbe from './pure-js-probes/rnd.mjs';
import { C, R, T } from '../js/c-runtime/context.js';

const layouts = JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json', import.meta.url)));
const layout = layouts.rnd;
const implementation = await createPureJsProbe(layouts);
const runtime = implementation;
const modules = [await referenceFactory(), implementation];
// This read-only entry establishes lazy function-identity storage without
// drawing, seeding or changing any logger field.
assert.equal(modules[1]._probe_enabled(), modules[0]._probe_enabled());
const stacks = modules.map(module => module._probe_stack());
const files = [new Set(), new Set()], paths = new Set();
let callerStorage = [[], []], comparisons = 0;
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
function context(module, pointer) {
    const base = Number(pointer), view = new DataView(module.HEAPU8.buffer);
    return { n: view.getUint32(base + layout.n, true),
        r: Array.from(new BigUint64Array(module.HEAPU8.buffer, base + layout.r, layout.ISAAC64_SZ)),
        m: Array.from(new BigUint64Array(module.HEAPU8.buffer, base + layout.m, layout.ISAAC64_SZ)),
        a: view.getBigUint64(base + layout.a, true), b: view.getBigUint64(base + layout.b, true), c: view.getBigUint64(base + layout.c, true) };
}
function logPointer(index) { return index ? runtime.rndState.rng_logfile : modules[0]._probe_log_pointer(); }
function snapshot(index) {
    const module = modules[index];
    const js = index ? runtime.rndState : null;
    const log = logPointer(index); if (log) files[index].add(BigInt(log));
    return {
        rng: [0, 1].map(which => {
            const state = js ? js.rnglist[which].rng_state : context(module, module._probe_state(which));
            return { init: js ? js.rnglist[which].init : module._probe_state_init(which),
                state: { n: state.n, r: Array.from(state.r), m: Array.from(state.m), a: state.a, b: state.b, c: state.c } };
        }),
        logger: { open: Boolean(log), disp: js ? js.rng_log_disp : module._probe_log_disp(), count: module._probe_count(),
            file: bytes(module, js ? js.rng_caller_file : module._probe_caller_file())?.toString('hex') ?? null,
            line: js ? js.rng_caller_line : module._probe_caller_line(),
            function: bytes(module, js ? js.rng_caller_func : module._probe_caller_function())?.toString('hex') ?? null },
        seedCalls: module._probe_seed_calls(), seedValue: module._probe_seed_value(),
        diagnostic: bytes(module, module._probe_diagnostic()).toString('hex'),
        panic: bytes(module, module._probe_panic_message()).toString('hex'),
    };
}
function state() {
    const results = [snapshot(0), snapshot(1)];
    assert.deepEqual(results[1], results[0]); scope(); comparisons++;
    return results[0];
}
function call(name, ...args) {
    const results = modules.map(module => module['_probe_' + name](...args));
    assert.deepEqual(results[1], results[0], `${name}(${args})`); state(); comparisons++;
    return results[0];
}
function env(name, value) {
    modules.forEach(module => {
        const n = allocate(module, name), v = allocate(module, value);
        assert.equal(module._probe_env(BigInt(n), BigInt(v)), 0);
        module._free(n); if (v) module._free(v);
    }); state();
}
function caller(file, line, func) {
    modules.forEach((module, i) => {
        const f = allocate(module, file), fn = allocate(module, func);
        module._probe_caller(BigInt(f), line, BigInt(fn));
        callerStorage[i].forEach(pointer => { if (pointer) module._free(pointer); });
        callerStorage[i] = [f, fn];
    }); state();
}
function logs() {
    modules.forEach((module, i) => files[i].forEach(file => assert.equal(module._probe_flush(file), 0)));
    for (const path of paths) {
        const results = modules.map(module => {
            try { return Buffer.from(module.FS.readFile(path)); } catch (error) { if (error.code === 'ENOENT' || error.errno === 44) return null; throw error; }
        });
        assert.deepEqual(results[1], results[0], path); comparisons++;
    }
    scope();
}
modules.forEach(module => {
    for (let i = 0; i < module._probe_layout_count(); i++) {
        const key = bytes(module, module._probe_layout_name(i)).toString();
        assert.equal(Number(module._probe_layout_value(i)), layout[key]);
    }
});
state();
env('NETHACK_RNGLOG', null); env('NETHACK_RNGLOG_DISP', null); call('log_init'); assert.equal(call('enabled'), 0);
const beforeBad = state(); assert.equal(call('init', 1n, 2), -1);
assert.deepEqual(state().rng, beforeBad.rng);
assert.equal(Buffer.from(state().panic, 'hex').toString(), 'Bad rng function passed to init_isaac64().');
for (const seed of [0n, 1n, (1n << 53n) + 1n, 1n << 63n, (1n << 64n) - 1n]) {
    call('init', seed, 0); call('init', BigInt.asUintN(64, seed ^ 0x123456789abcdefn), 1);
    const before = state(); call('display', 100); call('rnd_display', 10);
    assert.deepEqual(state().rng[0], before.rng[0], 'Display draws leave core state unchanged');
    const display = state().rng[1];
    for (const x of [1, 2, 3, 7, 15, 16, 999, 2147483647]) { call('rn2', x); call('rnd', x); }
    assert.deepEqual(state().rng[1], display, 'Core draws leave display state unchanged');
}
if (layout.DEVELOPMENT) {
    for (const name of ['rn2', 'rnd', 'rnl']) for (const x of [0, -1, -2147483648]) {
        const before = state(); call(name, x); assert.deepEqual(state().rng, before.rng);
        assert.notEqual(state().diagnostic, '');
    }
    for (const args of [[-1, 6], [1, 0], [0, -1]]) { const before = state(); call('dice', ...args); assert.deepEqual(state().rng, before.rng); }
}
for (const luck of [-13, -10, -4, -2, -1, 0, 1, 2, 4, 10, 13]) {
    for (const more of [-3, 0, 3]) {
        call('hero', luck, more, 10);
        for (const x of [1, 2, 15, 16, 500]) call('rnl', x);
    }
}
for (const level of [1, 14, 15, 17, 30]) {
    call('hero', 0, 0, level);
    for (const x of [1, 2, 4, 50]) call('rne', x);
    for (const x of [1, 25, 1000]) call('rnz', x);
}
for (const args of [[0, 0], [0, 6], [1, 1], [3, 6], [100, 20]]) call('dice', ...args);
call('seed', (1n << 64n) - 2n, 3n);
const beforeWeak = state(); call('reseed', 0, 0); call('reseed', 2, 0);
assert.deepEqual(state().rng, beforeWeak.rng); assert.equal(state().seedCalls, 0);
call('init_random', 0); call('reseed', 1, 1); assert.equal(state().seedCalls, 2);
const beforeInvalid = state().rng; assert.equal(call('init_random', 2), -1); assert.deepEqual(state().rng, beforeInvalid);

function shuffle(count) {
    const length = Math.max(count, 1), arrays = modules.map(module => module._malloc(BigInt(length * 4)));
    const original = Array.from({ length }, (_, i) => (i * 37) | 0);
    modules.forEach((module, i) => new Int32Array(module.HEAPU8.buffer, Number(arrays[i]), length).set(original));
    modules.forEach((module, i) => module._probe_shuffle(BigInt(arrays[i]), count));
    const results = modules.map((module, i) => Array.from(new Int32Array(module.HEAPU8.buffer, Number(arrays[i]), length)));
    assert.deepEqual(results[1], results[0]);
    assert.deepEqual([...results[0]].sort((a, b) => a - b), [...original].sort((a, b) => a - b));
    modules.forEach((module, i) => module._free(arrays[i])); state(); comparisons++;
}
for (const count of [-1, 0, 1, 2, 10, 257]) shuffle(count);

function logInit(path, display) {
    env('NETHACK_RNGLOG', path); env('NETHACK_RNGLOG_DISP', display); call('log_init');
    if (path && !path.includes('missing-directory')) paths.add(path);
}
function loggedDraws() { call('rn2', 17); call('rnd', 6); call('rnl', 15); call('dice', 3, 6); call('rne', 1); call('rnz', 25); call('display', 8); call('rnd_display', 9); logs(); }
logInit('', null); assert.equal(call('enabled'), 0);
logInit('/rnd-a.log', null); caller(null, 0, null); loggedDraws();
caller('fixture.c', 123, 'function'); loggedDraws();
caller('source:file.c', -11, null); logInit(null, '1'); loggedDraws();
caller(Buffer.from([0xff, 0x80, 0x3a]), 2147483647, Buffer.from([0xfe, 65])); logInit(null, '0x'); loggedDraws();
caller(null, -1, 'ignored-without-file'); logInit(null, 'false'); loggedDraws();
const oldCount = call('count'); logInit('/missing-directory/log', '1'); assert.equal(call('enabled'), 0); loggedDraws(); assert.equal(call('count'), oldCount);
logInit('/rnd-b.log', 'yes'); loggedDraws(); logInit('/rnd-b.log', '1'); loggedDraws();
caller('shuffle.c', 99, 'shuffle'); shuffle(50000); logs();
const oldBuffers = modules.map(module => memoryCheckpoint(module));
modules.forEach(module => module._malloc(40n * 1024n * 1024n));
modules.forEach((module, i) => assertMemoryGrowth(module, oldBuffers[i]));
state(); loggedDraws(); shuffle(1024); logs();
const independent = await createPureJsProbe(layouts);
const beforeIndependent = state();
independent._probe_init(42n, 0); independent._probe_init(99n, 1); independent._probe_rn2(12); independent._probe_display(12);
assert.deepEqual(state(), beforeIndependent); comparisons++;
// Original log reinitialization intentionally leaves old FILE handles open;
// close the fixture's collected handles after all behavioral comparisons.
modules.forEach((module, i) => {
    files[i].forEach(file => module._probe_close(file));
    callerStorage[i].forEach(pointer => { if (pointer) module._free(pointer); });
});
scope();
console.log(`RND: ${comparisons} ${referenceLabel}/pure-JS full-ISAAC-state, random-operation, seeding, shuffle and byte-exact log comparisons checked.`);
