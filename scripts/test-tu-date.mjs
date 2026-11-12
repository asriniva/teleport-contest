import './pure-js-probes/deny-wasm.mjs';
import { DataView, assertStackRestored, allocationMetric, assertMemoryGrowth, memoryCheckpoint, referenceBackend, referenceLabel } from './native-test-backend.mjs';
const referenceFactory = referenceBackend('date', emscriptenReferenceFactory);
import assert from './native-test-assert.mjs';
import { readFileSync } from 'node:fs';
import { spawnSync } from 'node:child_process';
import { fileURLToPath } from 'node:url';
import emscriptenReferenceFactory from '../.cache/tu-probes/date-reference.mjs';
import createPureJsProbe from './pure-js-probes/date.mjs';
import { C, R, T } from '../js/c-runtime/context.js';

if (!process.argv.includes('--worker')) {
    for (const zone of ['UTC', 'America/New_York', 'America/Los_Angeles', 'Asia/Kolkata', 'Europe/Berlin']) {
        const result = spawnSync(process.execPath, [fileURLToPath(import.meta.url), '--worker'], {
            env: { ...process.env, TZ: zone }, encoding: 'utf8', timeout: 30000,
        });
        assert.equal(result.status, 0, `${zone}: ${result.error || result.stderr || result.stdout}`);
        process.stdout.write(result.stdout);
    }
} else {
    const layouts = JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json', import.meta.url)));
    const layout = layouts.date;
    const modules = [await referenceFactory(), await createPureJsProbe(layouts)];
    let comparisons = 0;
    const initialStack = modules.map(module => module._probe_stack());
    function scope() {
        assert.equal(C, undefined); assert.equal(R, undefined); assert.equal(T, undefined);
        modules.forEach((module, i) => assertStackRestored(module, initialStack[i]));
    }
    function bytes(module, pointer) {
        if (!pointer) return null;
        let end = Number(pointer);
        while (module.HEAPU8[end]) end++;
        return Buffer.from(module.HEAPU8.slice(Number(pointer), end));
    }
    function text(module, pointer) { return bytes(module, pointer)?.toString() ?? null; }
    function allocate(module, value) {
        if (value === null) return 0;
        const data = Buffer.isBuffer(value) ? value : Buffer.from(value);
        const pointer = module._malloc(BigInt(data.length + 1));
        module.HEAPU8.set(data, Number(pointer));
        module.HEAPU8[Number(pointer) + data.length] = 0;
        return pointer;
    }
    function descriptors(module) {
        return Object.fromEntries(Array.from({ length: module._probe_field_count() }, (_, i) => [
            text(module, module._probe_field_name(i)), {
                offset: Number(module._probe_field_offset(i)), size: Number(module._probe_field_size(i)),
                kind: ['pointer', 'ulong'][module._probe_field_kind(i)],
            },
        ]));
    }
    modules.forEach(module => {
        assert.equal(Number(module._probe_context_size()), layout.size);
        assert.deepEqual(descriptors(module), layout.fields);
        assert.equal(module._probe_long_size(), 8); assert.equal(module._probe_time_size(), 8);
        assert.equal(Number(module._probe_version_size()), 3 * module._probe_long_size());
        for (const name of ['incarnation', 'feature_set', 'entity_count']) {
            assert.deepEqual(layout.versionFields[name], {
                offset: Number(module['_probe_offset_' + name]()), size: module._probe_long_size(), kind: 'ulong',
            });
        }
        assert.equal(module._probe_int_size(), layouts.calendar.intSize);
        assert.equal(module._probe_bufsz(), layout.BUFSZ);
        assert.equal(text(module, module._probe_build_date_time()), layout.strings.BUILD_DATE_TIME);
        for (const name of ['sha', 'branch', 'prefix']) assert.equal(text(module, module['_probe_git_' + name]()), layout.strings['NETHACK_GIT_' + name.toUpperCase()]);
    });
    function snapshot(module) {
        const base = Number(module._probe_pointer());
        const view = new DataView(module.HEAPU8.buffer);
        const fields = Object.fromEntries(Object.entries(layout.fields).map(([name, field]) => {
            const value = view.getBigUint64(base + field.offset, true);
            return [name, field.kind === 'pointer' ? bytes(module, value)?.toString('hex') ?? null : value];
        }));
        return { fields, trace: bytes(module, module._probe_trace()).toString('hex') };
    }
    function state() {
        const results = modules.map(snapshot);
        assert.deepEqual(results[1], results[0]); scope(); comparisons++;
        return results[0];
    }
    function env(name, value) {
        modules.forEach(module => {
            const key = allocate(module, name), data = allocate(module, value);
            assert.equal(module._probe_env(BigInt(key), BigInt(data)), 0);
            module._free(key); if (data) module._free(data);
        });
        return state();
    }
    function inputs(values, helper = 'fixture-version') {
        modules.forEach(module => {
            const pointer = allocate(module, helper);
            module._probe_inputs(...values, BigInt(pointer)); module._free(pointer);
        });
        return state();
    }
    function populate(values, helper, realDate) {
        inputs(values, helper);
        modules.forEach(module => module._probe_populate());
        const result = state();
        assert.equal(result.fields.version_number, values[0]);
        assert.equal(result.fields.version_features, values[1]);
        assert.equal(result.fields.version_sanity1, values[2]);
        assert.equal(result.fields.ignored_features, values[3]);
        const date = realDate === null ? 'May  2 2026 12:00:00' : layout.strings.BUILD_DATE_TIME;
        assert.equal(result.fields.build_date, Buffer.from(date).toString('hex'));
        const raw = Buffer.isBuffer(helper) ? helper : Buffer.from(helper);
        assert.equal(result.fields.version_string, Buffer.concat([Buffer.from('v.'), raw]).subarray(0, layout.BUFSZ - 1).toString('hex'));
        assert.equal(result.trace, Buffer.from(`ignored;version:.;id:${layout.BUFSZ}:${date};banner:${layout.BUFSZ}:${date};`).toString('hex'));
        for (const name of ['sha', 'branch', 'prefix']) {
            const configured = layout.strings['NETHACK_GIT_' + name.toUpperCase()];
            assert.equal(result.fields['git_' + name], configured === null ? null : Buffer.from(configured).toString('hex'));
        }
        comparisons++;
        return result;
    }
    function release() {
        modules.forEach(module => module._probe_release());
        return state();
    }
    const initial = state();
    assert.equal(initial.fields.build_time, 554476737n);
    assert.deepEqual(release(), initial, 'Static defaults must not be freed before first population');
    assert.deepEqual(release(), initial);
    env('TZ', process.env.TZ);
    const cases = [
        [0n, 0n, 0n, 0n], [1n, 2n, 3n, 4n],
        [(1n << 53n) - 1n, 1n << 53n, (1n << 53n) + 1n, (1n << 53n) + 3n],
        [1n << 63n, (1n << 64n) - 1n, (1n << 63n) + 1n, (1n << 64n) - 2n],
    ];
    const helperStrings = ['', 'fixture-version', 'x'.repeat(layout.BUFSZ - 1), Buffer.from([0xff, 0x80, 0xc3, 0xa9])];
    for (const realDate of [null, '', '1', 'false']) {
        env('NETHACK_REAL_BUILD_DATE', realDate);
        for (const values of cases) for (const helper of helperStrings) {
            const populated = populate(values, helper, realDate);
            assert.deepEqual(populate(values, helper, realDate), populated, 'Repeated population has identical visible state');
            const freed = release();
            for (const name of ['build_date', 'version_string', 'version_id', 'copyright_banner_c']) assert.equal(freed.fields[name], null);
            assert.deepEqual(release(), freed, 'Repeated free is harmless');
        }
    }
    env('NETHACK_REAL_BUILD_DATE', null);
    const oldBuffers = modules.map(module => memoryCheckpoint(module));
    modules.forEach(module => module._malloc(40n * 1024n * 1024n));
    modules.forEach((module, i) => assertMemoryGrowth(module, oldBuffers[i]));
    state(); populate(cases[3], 'after growth', null); release();
    const independent = await createPureJsProbe(layouts);
    const before = state();
    assert.deepEqual(snapshot(independent).fields, initial.fields, 'Separate game starts with static defaults');
    const pointer = allocate(independent, 'independent');
    independent._probe_inputs(1n, 2n, 3n, 4n, BigInt(pointer)); independent._free(pointer);
    independent._probe_populate(); independent._probe_release();
    assert.deepEqual(state(), before); scope(); comparisons++;
    console.log(`DATE (${process.env.TZ}): ${comparisons} ${referenceLabel}/pure-JS layout, build metadata, version, lifecycle and stack comparisons checked.`);
}
