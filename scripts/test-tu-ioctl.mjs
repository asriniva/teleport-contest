import { assertStackRestored, allocationMetric, assertMemoryGrowth, memoryCheckpoint, referenceBackend, referenceLabel } from './native-test-backend.mjs';
const referenceFactory = referenceBackend('ioctl', emscriptenReferenceFactory);
import assert from './native-test-assert.mjs';
import { readFileSync } from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/ioctl-reference.mjs';
import hybridFactory from '../.cache/tu-probes/ioctl-hybrid.mjs';
import { createPortedRuntime } from '../js/ported/wasm-runtime.js';
import { C, R, T } from '../js/ported/c-runtime.js';

const layouts = JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json', import.meta.url)));
const layout = layouts.ioctl;
const modules = [await referenceFactory(), await hybridFactory({ nethackPorted: createPortedRuntime(layouts) })];
const stacks = modules.map(module => module._probe_stack());
let shellerStorage = [0, 0], comparisons = 0;
function scope() {
    assert.equal(C, undefined); assert.equal(R, undefined); assert.equal(T, undefined);
    modules.forEach((module, i) => assertStackRestored(module, stacks[i]));
}
function bytes(module, pointer) {
    let end = Number(pointer);
    while (module.HEAPU8[end]) end++;
    return Buffer.from(module.HEAPU8.slice(Number(pointer), end));
}
function uint64(value) { return BigInt.asUintN(64, BigInt(value)); }
const signal = Object.fromEntries(['default', 'ignore', 'error'].map(name => {
    const values = modules.map(module => uint64(module['_probe_sig_' + name]()));
    assert.equal(values[1], values[0]); return [name, values[0]];
}));
modules.forEach(module => {
    assert.equal(Number(module._probe_context_size()), layout.termioSize);
    for (let i = 0; i < module._probe_layout_count(); i++) {
        const key = bytes(module, module._probe_layout_name(i)).toString();
        assert.equal(Number(module._probe_layout_value(i)), layout[key], key);
    }
});
function block(module, pointer) { return Buffer.from(module.HEAPU8.slice(Number(pointer), Number(pointer) + layout.termioSize)); }
function snapshot(module) {
    return {
        terminal: block(module, module._probe_termio_pointer()),
        input: block(module, module._probe_input_pointer()), output: block(module, module._probe_output_pointer()),
        trace: bytes(module, module._probe_trace()).toString('hex'), handler: uint64(module._probe_handler()),
    };
}
function state() {
    const values = modules.map(snapshot);
    assert.deepEqual(values[1], values[0]); scope(); comparisons++;
    return values[0];
}
function call(name, ...args) {
    const result = modules.map(module => module['_probe_' + name](...args));
    assert.deepEqual(result[1], result[0]); state(); comparisons++;
    return result[0];
}
function fill(which, seed) {
    modules.forEach(module => {
        const pointer = Number(module['_probe_' + which + '_pointer']());
        for (let i = 0; i < layout.termioSize; i++) module.HEAPU8[pointer + i] = (seed + i * 17) & 255;
    }); state();
}
function shellers(value) {
    modules.forEach((module, i) => {
        let pointer = 0;
        if (value !== null) {
            const data = Buffer.isBuffer(value) ? value : Buffer.from(value);
            pointer = module._malloc(BigInt(data.length + 1));
            module.HEAPU8.set(data, Number(pointer)); module.HEAPU8[Number(pointer) + data.length] = 0;
        }
        module._probe_shellers(BigInt(pointer));
        if (shellerStorage[i]) module._free(shellerStorage[i]);
        shellerStorage[i] = pointer;
    }); state();
}
function textTrace() { return Buffer.from(state().trace, 'hex').toString('latin1'); }
state();
for (const getStatus of [0, -1, 1]) for (const setStatus of [0, -1, 1]) {
    call('options', getStatus, setStatus, -1, 0, signal.default);
    fill('termio', 0xa0); fill('input', 0x31); fill('output', 0x82);
    const before = state();
    call('get');
    assert.deepEqual(state().terminal, getStatus === 0 ? before.input : before.terminal, 'Failed get leaves existing termio bytes intact');
    assert.equal(textTrace(), 'get:0;');
    call('set');
    assert.deepEqual(state().output, state().terminal, 'Set passes every termio byte regardless of syscall status');
    assert.equal(textTrace(), `get:0;set:0:${layout.TCSADRAIN};`);
    const windowsBefore = state(); call('windows');
    assert.deepEqual(state(), windowsBefore, 'The configured getwindowsz body is empty');
}
const denied = 'Norep:Suspend command not available.;';
// Exercise the native sizing branch with the same controlled ioctl dependency.
for(const status of [-1,0,1])for(const rows of [0,24])for(const columns of [0,80]){
    call('window_options',status,rows,columns);call('windows');
    assert.equal(call('dimensions',0),status===-1||!rows?12:rows);
    assert.equal(call('dimensions',1),status===-1||!columns?34:columns);
}
for (const value of [null, '', 'allowed-users', Buffer.from([0xff, 0x80, 0x41])]) {
    for (const auth of [0, 1]) {
        shellers(value); call('options', 0, 0, 0, auth, signal.default);
        assert.equal(call('suspend'), 0);
        const nonempty = value !== null && Buffer.from(value).length > 0;
        const checked = nonempty ? `check:${Buffer.from(value).toString('latin1')};` : '';
        if (!nonempty || !auth) {
            assert.equal(textTrace(), checked + denied); assert.equal(state().handler, signal.default);
        } else {
            assert.equal(textTrace(), checked + `signal:${layout.SIGTSTP}:${signal.ignore};suspend:<null>;signal:${layout.SIGTSTP}:${signal.default};kill:0:${layout.SIGTSTP};resume;`);
            assert.equal(state().handler, signal.default);
        }
    }
}
shellers('authorized');
for (const previous of [signal.default, signal.ignore, signal.error, (1n << 53n) + 1n, 1n << 63n, (1n << 64n) - 2n]) {
    for (const killStatus of [0, -1]) {
        call('options', 0, 0, killStatus, 1, previous);
        assert.equal(call('suspend'), 0);
        if (previous === signal.default) {
            assert.equal(textTrace(), `check:authorized;signal:${layout.SIGTSTP}:${signal.ignore};suspend:<null>;signal:${layout.SIGTSTP}:${signal.default};kill:0:${layout.SIGTSTP};resume;`);
            assert.equal(state().handler, signal.default);
        } else {
            assert.equal(textTrace(), `check:authorized;signal:${layout.SIGTSTP}:${signal.ignore};pline:I don't think your shell has job control.;`);
            assert.equal(state().handler, signal.ignore, 'Existing handler is replaced with SIG_IGN on the non-default branch');
        }
    }
}
const oldBuffers = modules.map(module => memoryCheckpoint(module));
modules.forEach(module => module._malloc(40n * 1024n * 1024n));
modules.forEach((module, i) => assertMemoryGrowth(module, oldBuffers[i]));
state(); fill('input', 0xf0); call('options', 0, 0, 0, 1, signal.default); call('get'); call('set'); call('suspend');
const independent = await hybridFactory({ nethackPorted: createPortedRuntime(layouts) });
const before = state();
independent._probe_options(0, 0, 0, 0, signal.default); independent._probe_get(); independent._probe_set(); independent._probe_suspend();
assert.deepEqual(state(), before); scope(); comparisons++;
modules.forEach((module, i) => { module._probe_shellers(0n); if (shellerStorage[i]) module._free(shellerStorage[i]); });
console.log(`IOCTL: ${comparisons} ${referenceLabel}/hybrid termios-byte, native-call-order, authorization and signal-handler comparisons checked.`);
