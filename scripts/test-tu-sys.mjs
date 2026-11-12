import { DataView, assertStackRestored, allocationMetric, assertMemoryGrowth, memoryCheckpoint, referenceBackend, referenceLabel } from './native-test-backend.mjs';
const referenceFactory = referenceBackend('sys', emscriptenReferenceFactory);
import assert from './native-test-assert.mjs';
import { readFileSync } from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/sys-reference.mjs';
import hybridFactory from '../.cache/tu-probes/sys-hybrid.mjs';
import { createPortedRuntime } from '../js/backends/emscripten/runtime.js';
import { C, R, T } from '../js/c-runtime/context.js';

const layouts = JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json', import.meta.url)));
const layout = layouts.sys;
const modules = [await referenceFactory(), await hybridFactory({ nethackPorted: createPortedRuntime(layouts) })];
let comparisons = 0;
function scope() { assert.equal(C, undefined); assert.equal(R, undefined); assert.equal(T, undefined); }
function bytes(module, pointer) {
    if (!pointer) return null;
    let end = Number(pointer);
    while (module.HEAPU8[end]) end++;
    return Buffer.from(module.HEAPU8.slice(Number(pointer), end));
}
function text(module, pointer) { return bytes(module, pointer)?.toString() ?? null; }
function integer(module, pointer, size, signed = true) {
    return new DataView(module.HEAPU8.buffer)[`get${size === 8 ? 'Big' : ''}${signed ? 'Int' : 'Uint'}${size * 8}`](Number(pointer), true);
}
function descriptors(module, prefix) {
    const result = {};
    for (let i = 0; i < module[`_probe_${prefix}field_count`](); i++) {
        result[text(module, module[`_probe_${prefix}field_name`](i))] = {
            offset: Number(module[`_probe_${prefix}field_offset`](i)),
            size: Number(module[`_probe_${prefix}field_size`](i)),
            kind: prefix ? 'pointer' : ['pointer', 'int', 'long', 'array'][module._probe_field_kind(i)],
        };
    }
    return result;
}
modules.forEach(module => {
    assert.equal(Number(module._probe_context_size()), layout.size);
    assert.deepEqual(descriptors(module, ''), layout.fields);
    assert.deepEqual(descriptors(module, 'gc_'), layout.gcFields);
});
function fields(module, base, descriptions) {
    return Object.fromEntries(Object.entries(descriptions).map(([name, field]) => {
        const pointer = Number(base) + field.offset;
        let value;
        switch (field.kind) {
        case 'pointer': {
            const target = integer(module, pointer, field.size, false);
            value = bytes(module, target)?.toString('hex') ?? null;
            break;
        }
        case 'array': {
            const intSize = module._probe_int_size();
            value = Array.from({ length: field.size / intSize }, (_, i) => integer(module, pointer + i * intSize, intSize));
            break;
        }
        default: value = integer(module, pointer, field.size); break;
        }
        return [name, value];
    }));
}
function snapshot(module) {
    return {
        sys: fields(module, module._probe_sys_pointer(), layout.fields),
        gc: fields(module, module._probe_gc_pointer(), layout.gcFields),
    };
}
function state() {
    const values = modules.map(snapshot);
    assert.deepEqual(values[1], values[0]); scope(); comparisons++;
    return values[0];
}
function call(name, ...args) {
    modules.forEach(module => module['_probe_' + name](...args));
    return state();
}
function environment(value) {
    modules.forEach(module => {
        if (value === null) { module._probe_env(0n); return; }
        const data = Buffer.isBuffer(value) ? value : Buffer.from(value);
        const pointer = module._malloc(BigInt(data.length + 1));
        module.HEAPU8.set(data, Number(pointer));
        module.HEAPU8[Number(pointer) + data.length] = 0;
        module._probe_env(BigInt(pointer)); module._free(pointer);
    });
    state();
}
function initExpected(value) {
    const result = call('init');
    assert.equal(result.sys.support, null);
    assert.equal(result.sys.recover, null);
    assert.equal(result.sys.env_dbgfl, value === null ? 0 : 1);
    if (value !== null) assert.equal(result.sys.debugfiles, Buffer.from(value).toString('hex'));
    else if (layout.constants.SYSCF || !layout.constants.DEBUGFILES_DEFINED) assert.equal(result.sys.debugfiles, null);
    else assert.equal(result.sys.debugfiles, Buffer.from(layout.strings.DEBUGFILES).toString('hex'));
    assert.equal(result.sys.saveformat[0], layout.constants.historical);
    assert.equal(result.sys.bonesformat[0], layout.constants.historical);
    assert.equal(result.sys.persmax, Math.max(layout.constants.PERSMAX, 1));
    assert.equal(result.sys.entrymax, Math.max(layout.constants.ENTRYMAX, 10));
    assert.equal(result.sys.pointsmin, Math.max(layout.constants.POINTSMIN, 1));
    assert.equal(result.sys.livelog, BigInt(layout.constants.LL_NONE));
    comparisons++;
    return result;
}
state();
environment(null); initExpected(null); call('release'); call('release');
const environments = [null, '', '*', 'foo.c bar.c', 'FOO.c foo.C', 'a'.repeat(8192), Buffer.from([0xff, 0x80, 0x20, 0xc3, 0xa9])];
for (let i = 0; i < environments.length; i++) {
    const value = environments[i];
    call('populate', i);
    const populated = state();
    for (const seduce of [0, 1, -1, 2, 2147483647, -2147483648]) {
        call('seduce', seduce);
        assert.deepEqual(state(), populated, 'sysopt_seduce_set is the original no-op');
    }
    environment(value);
    const initialized = initExpected(value);
    assert.equal(initialized.sys.saveformat[1], populated.sys.saveformat[1], 'One-time conversion setting is preserved');
    assert.equal(initialized.sys.bonesformat[1], populated.sys.bonesformat[1]);
    assert.deepEqual(initialized.gc, populated.gc, 'Initialization leaves crash identity intact');
    const repeated = initExpected(value);
    assert.deepEqual(repeated, initialized, 'Repeated initialization has identical field contents');
    const released = call('release');
    assert.equal(released.sys.debugfiles, null);
    assert.equal(released.sys.env_dbgfl, 0);
    for (const value of Object.values(released.gc)) assert.equal(value, null);
    assert.deepEqual(call('release'), released, 'Release is idempotent');
}
// Sequential environment changes exercise freeing and replacing an existing
// DEBUGFILES allocation, then the source's absent-environment path.
call('populate', 123);
for (const value of ['first.c', '', '*', null, 'second.c', null]) {
    environment(value); initExpected(value);
}
// Release populated fields directly, including fields initialization clears.
call('populate', 456);
const populated = state();
const released = call('release');
for (const [name, field] of Object.entries(layout.fields)) {
    if (field.kind === 'pointer' && name !== 'crashreporturl') assert.equal(released.sys[name], null, name);
    else if (name !== 'env_dbgfl') assert.deepEqual(released.sys[name], populated.sys[name], name);
}
assert.equal(released.sys.crashreporturl, populated.sys.crashreporturl, 'Original release leaves this pointer unchanged');

const oldBuffers = modules.map(module => memoryCheckpoint(module));
modules.forEach(module => module._malloc(40n * 1024n * 1024n));
modules.forEach((module, i) => assertMemoryGrowth(module, oldBuffers[i]));
state(); call('populate', 789); environment('after-growth.c'); initExpected('after-growth.c'); call('release');
const independent = await hybridFactory({ nethackPorted: createPortedRuntime(layouts) });
const before = state();
independent._probe_populate(987); independent._probe_init(); independent._probe_seduce(-1); independent._probe_release();
assert.deepEqual(state(), before); scope();
console.log(`SYS: ${comparisons} ${referenceLabel}/hybrid configured-field, environment, initialization and release comparisons checked.`);
