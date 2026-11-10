import { DataView, assertStackRestored, allocationMetric, assertMemoryGrowth, memoryCheckpoint, referenceBackend, referenceLabel } from './native-test-backend.mjs';
const referenceFactory = referenceBackend('unixtty', emscriptenReferenceFactory);
import assert from './native-test-assert.mjs';
import { readFileSync } from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/unixtty-reference.mjs';
import hybridFactory from '../.cache/tu-probes/unixtty-hybrid.mjs';
import { createPortedRuntime } from '../js/ported/wasm-runtime.js';
import { C, R, T } from '../js/ported/c-runtime.js';

const layouts = JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json', import.meta.url)));
const layout = layouts.unixtty;
const runtime = createPortedRuntime(layouts);
const modules = [await referenceFactory(), await hybridFactory({ nethackPorted: runtime })];
modules[1]._probe_fixup();
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
function allocate(module, value) {
    if (value === null) return 0;
    const data = Buffer.isBuffer(value) ? value : Buffer.from(value), pointer = module._malloc(BigInt(data.length + 1));
    module.HEAPU8.set(data, Number(pointer)); module.HEAPU8[Number(pointer) + data.length] = 0; return pointer;
}
function block(module, pointer) { return Buffer.from(module.HEAPU8.slice(Number(pointer), Number(pointer) + layout.termioSize)); }
function snapshot(module, index) {
    return { init: block(module, module._probe_init_pointer()), cur: block(module, module._probe_cur_pointer()),
        input: block(module, module._probe_input_pointer()), output: block(module, module._probe_output_pointer()),
        speed: module._probe_ospeed(), erase: module._probe_erase(), intr: module._probe_intr(), kill: module._probe_kill(),
        echo: module._probe_echo(), cbreak: module._probe_cbreak(), window: module._probe_window(),
        needed: index ? runtime.unixttyState.settty_needed : module._probe_needed(),
        trace: bytes(module, module._probe_trace()).toString('hex'), exit: module._probe_exit_status() };
}
function state() {
    const values = modules.map(snapshot); assert.deepEqual(values[1], values[0]); scope(); comparisons++; return values[0];
}
function call(name, ...args) {
    const result = modules.map(module => module['_probe_' + name](...args));
    assert.deepEqual(result[1], result[0], name); state(); comparisons++; return result[0];
}
function needed(value) { modules[0]._probe_set_needed(value); runtime.unixttyState.settty_needed = value; state(); }
function env(value) {
    modules.forEach(module => {
        const name = allocate(module, 'NOMUX_MARKERS'), val = allocate(module, value);
        assert.equal(module._probe_env(BigInt(name), BigInt(val)), 0); module._free(name); if (val) module._free(val);
    }); state();
}
function fill(which, seed) {
    modules.forEach(module => {
        const pointer = Number(module['_probe_' + which + '_pointer']());
        for (let i = 0; i < layout.termioSize; i++) module.HEAPU8[pointer + i] = (seed + i * 13) & 255;
    }); state();
}
function field(which, name, value) {
    modules.forEach(module => {
        const pointer = Number(module['_probe_' + which + '_pointer']()) + layout[name];
        const kind=layout.tcflagSize===8?'BigUint64':'Uint32';
        new DataView(module.HEAPU8.buffer)['set'+kind](pointer,layout.tcflagSize===8?BigInt(value):value,true);
    }); state();
}
function cc(which, index, value) {
    modules.forEach(module => { module.HEAPU8[Number(module['_probe_' + which + '_pointer']()) + layout.c_cc + index] = value; }); state();
}
function trace() { return Buffer.from(state().trace, 'hex').toString(); }
function set(text) {
    const result = modules.map(module => {
        const pointer = allocate(module, text); module._probe_set(BigInt(pointer)); if (pointer) module._free(pointer);
    }); assert.deepEqual(result[1], result[0]); state(); comparisons++;
}
modules.forEach(module => {
    assert.equal(Number(module._probe_context_size()), layout.termioSize);
    for (let i = 0; i < module._probe_layout_count(); i++) {
        const key = bytes(module, module._probe_layout_name(i)).toString(); assert.equal(Number(module._probe_layout_value(i)), layout[key], key);
    }
});
state();
const baudNames = ['B0', 'B50', 'B75', 'B110', 'B134', 'B150', 'B200', 'B300', 'B600', 'B1200', 'B1800', 'B2400', 'B4800', 'B9600', 'B19200', 'B38400'];
for (let i = 0; i < baudNames.length; i++) {
    env(null); call('options', 0, 0, layout[baudNames[i]], 0n, 1, 0);
    fill('input', i); field('input', 'c_oflag', 0); call('get');
    assert.equal(state().speed, i); assert.equal(state().needed, 1); assert.deepEqual(state().init, state().cur);
    assert.equal(trace(), 'get:0:init;speed:init;getioctls;');
}
for (const speed of [123456, 4294967295]) {
    call('options', 0, 0, speed, 0n, 1, 0); field('input', 'c_oflag', 0); call('get'); assert.equal(state().speed, 0);
}
for (const nomux of [null, '', '1']) for (const failure of [0, -1]) {
    env(nomux); call('options', failure, failure, layout.B9600, -1n, 1, 0);
    fill('input', 0xa5); fill('init', 0x42); field('input', 'c_oflag', layout.EXTABS);
    cc('input', layout.VERASE, 0xff); cc('input', layout.VKILL, 0x80); cc('input', layout.VINTR, 0xfe);
    call('get');
    const after = state();
    if (nomux !== null) {
        assert.equal(after.erase, 127); assert.equal(after.kill, 21); assert.equal(after.intr, 3);
    }
    assert.equal(trace().includes('perror:'), failure < 0 && nomux === null);
    const beforeSet = state(); set('reset message'); assert.equal(state().needed, 0);
    assert.ok(trace().includes('end;raw:reset message;'));
    assert.deepEqual(state().init, beforeSet.init, 'Restoring terminal leaves original structure intact');
}
// Exercise each ECHO/ICANON transition and C's byte-vs-long disable value
// comparisons. Repeated calls expose every fpathconf evaluation/order.
for (const lflag of [0, layout.ECHO, layout.ICANON, layout.ECHO | layout.ICANON]) {
    for (const disabled of [-1n, 0n, 255n, 513n]) {
        env(null); call('options', 0, 0, layout.B9600, disabled, 1, 0);
        fill('input', 0x71); field('input', 'c_oflag', 0); field('input', 'c_cflag', 0); call('get');
        field('cur', 'c_lflag', lflag); field('cur', 'c_iflag', layout.STRIPHI);
        cc('cur', layout.VINTR, 7); call('chars', -1, -1, -1);
        call('clear_trace'); call('fast'); assert.equal(state().echo, 0); assert.equal(state().cbreak, 1);
        call('fast'); call('on'); call('on'); call('off'); call('off'); call('on');
        field('init', 'c_cflag', layout.CS7); field('cur', 'c_iflag', layout.STRIPHI); call('fast');
    }
}
// Non-tty windows skip interrupt-changing and screen callbacks, retaining
// source behavior even when raw structures would otherwise require changes.
call('options', 0, 0, layout.B9600, 0n, 0, 0); call('chars', 1, 2, 3);
cc('cur', layout.VINTR, 7); call('clear_trace');
const beforeInterrupt = state(); call('on'); call('off');
assert.deepEqual(state(), beforeInterrupt);
set(null); assert.ok(!trace().includes('end;'));
call('clear_trace'); call('fast'); assert.ok(!trace().includes('start;'));
call('clear_trace'); const beforeFixup = state(); call('fixup'); assert.deepEqual(state(), beforeFixup);

const formatted = ['fatal plain', 'typed -7 -9007199254740993 3.25 message %', 'chars Q 4294967295 abcdef', 'empty:'];
for (const window of [0, 1]) for (const restore of [0, 1]) for (const nested of [0, 1]) for (let variant = 0; variant < formatted.length; variant++) {
    env(null); call('options', 0, 0, layout.B9600, 0n, 1, nested); call('iflags', 0, 0, window); needed(restore);
    assert.equal(call('error', variant), -1); assert.equal(call('exit_status'), layout.EXIT_FAILURE);
    const text = trace();
    assert.ok(text.endsWith(`vprintf:${formatted[variant]};putchar:10;exit:${layout.EXIT_FAILURE};`));
    const cleanups = (text.match(/setioctls;/g) || []).length;
    assert.equal(cleanups, window && nested ? 1 : restore ? 1 : 0, 'Nested window cleanup prevents duplicate settty');
    assert.equal(text.startsWith('window-exit:<null>;'), Boolean(window));
}
const oldBuffers = modules.map(module => memoryCheckpoint(module));
modules.forEach(module => module._malloc(40n * 1024n * 1024n));
modules.forEach((module, i) => assertMemoryGrowth(module, oldBuffers[i]));
state(); call('options', 0, 0, layout.B38400, -1n, 1, 1); call('get'); call('fast'); call('off'); call('on'); set(null);
call('iflags', 0, 0, 1); needed(1); call('error', 1);
const independentRuntime = createPortedRuntime(layouts), independent = await hybridFactory({ nethackPorted: independentRuntime });
const beforeIndependent = state(); independent._probe_fixup(); independent._probe_options(0, 0, layout.B50, 0n, 1, 0);
independent._probe_get(); independent._probe_fast(); independent._probe_set(0n);
assert.deepEqual(state(), beforeIndependent); scope(); comparisons++;
console.log(`UNIXTTY: ${comparisons} ${referenceLabel}/hybrid terminal-byte, baud, control-flag, variadic-error and nested-cleanup comparisons checked.`);
