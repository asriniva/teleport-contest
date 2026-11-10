import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import { spawnSync } from 'node:child_process';
import { fileURLToPath } from 'node:url';
import referenceFactory from '../.cache/tu-probes/calendar-reference.mjs';
import hybridFactory from '../.cache/tu-probes/calendar-hybrid.mjs';
import { createPortedRuntime } from '../js/ported/wasm-runtime.js';
import { C, R, T } from '../js/ported/c-runtime.js';

if (!process.argv.includes('--worker')) {
    for (const zone of ['America/New_York', 'America/Los_Angeles', 'UTC', 'Asia/Kolkata', 'Europe/Berlin']) {
        const result = spawnSync(process.execPath, [fileURLToPath(import.meta.url), '--worker'], {
            env: { ...process.env, TZ: zone }, encoding: 'utf8', timeout: 30000,
        });
        assert.equal(result.status, 0, `${zone}: ${result.error || result.stderr || result.stdout}`);
        process.stdout.write(result.stdout);
    }
} else {
    const layouts = JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json', import.meta.url)));
    assert.equal(layouts.calendar.longSize, 8);
    assert.equal(layouts.calendar.timeSize, 8);
    const NativeDate = globalThis.Date;
    let clock = NativeDate.parse('2026-01-15T12:00:00Z');
    globalThis.Date = class extends NativeDate {
        constructor(...args) { super(...(args.length ? args : [clock])); }
        static now() { return clock; }
    };
    try {
        const modules = [await referenceFactory(), await hybridFactory({ nethackPorted: createPortedRuntime(layouts) })];
        const initialStack = modules.map(module => module._probe_stack());
        let comparisons = 0;
        function cstring(module, pointer) {
            let end = Number(pointer);
            while (module.HEAPU8[end]) end++;
            return Buffer.from(module.HEAPU8.slice(Number(pointer), end)).toString();
        }
        function scope() {
            assert.equal(C, undefined); assert.equal(R, undefined); assert.equal(T, undefined);
            modules.forEach((module, i) => assert.equal(module._probe_stack(), initialStack[i], 'C stack must be restored'));
        }
        function allocate(module, text) {
            if (text === null) return 0;
            const bytes = typeof text === 'string' ? Buffer.from(text) : text;
            const pointer = module._malloc(BigInt(bytes.length + 1));
            module.HEAPU8.set(bytes, Number(pointer));
            module.HEAPU8[Number(pointer) + bytes.length] = 0;
            return pointer;
        }
        function setEnv(name, value) {
            for (const module of modules) {
                const key = allocate(module, name), text = allocate(module, value);
                assert.equal(module._probe_set_env(BigInt(key), BigInt(text)), 0);
                module._free(key); if (text) module._free(text);
            }
        }
        function compare(name, ...args) {
            const values = modules.map(module => module['_probe_' + name](...args));
            assert.equal(values[1], values[0], `${name}(${args})`);
            comparisons++; scope(); return values[1];
        }
        function parse(text) {
            const values = modules.map(module => {
                const pointer = allocate(module, text);
                const value = module._probe_parse(BigInt(pointer));
                if (pointer) module._free(pointer);
                return value;
            });
            assert.equal(values[1], values[0], `parse(${text})`);
            comparisons++; scope(); return values[1];
        }
        const datePointers = [];
        function format(date) {
            const pointers = modules.map(module => module._probe_format(date));
            if (!datePointers.length) datePointers.push(...pointers);
            else pointers.forEach((pointer, i) => assert.equal(pointer, datePointers[i], 'datestr address must remain stable'));
            const values = modules.map((module, i) => cstring(module, pointers[i]));
            assert.equal(values[1], values[0], `format(${date})`);
            comparisons++; scope(); return values[1];
        }
        const dates = [0n, 1n, -1n, -2208988800n, -62167219200n, 946684800n,
            1709210096n, 1741503600n, 1762061400n, 1777723200n, 4102444800n,
            253402300800n, 1n << 40n, -(1n << 40n)];
        const strings = [null, '', 'x', '2000011009000', '200001100900000',
            '20000110090000', '20260115120000', '20260715120000', '20260308023000',
            '20261101013000', '20240229010203', '20230229010203', '19691231235959',
            '19700101000000', '00000101000000', '99991231235959', '20001332009999',
            'abcdefghijklmn', ' 0260101120000', Uint8Array.from({ length: 14 }, () => 255)];
        for (const now of ['2026-01-15T12:00:00Z', '2026-07-15T12:00:00Z']) {
            clock = NativeDate.parse(now);
            for (const epoch of [null, '1777723200', '1768478400', '0', '-1', 'junk', ' 1777723200 trailing']) {
                setEnv('NETHACK_RECORDING_EPOCH', epoch);
                for (const fixed of [null, '', '20260115120000', '20260715120000', 'invalid', 'x'.repeat(129)]) {
                    setEnv('NETHACK_FIXED_DATETIME', fixed);
                    for (const name of ['now', 'year', 'moon', 'friday', 'night', 'midnight']) compare(name);
                    compare('date', 0n); compare('time', 0n); format(0n);
                }
                setEnv('NETHACK_FIXED_DATETIME', null);
                for (const date of dates) {
                    compare('date', date); compare('time', date);
                    parse(format(date));
                }
                for (const text of strings) parse(text);
            }
        }
        // Explicitly preserve the C parser's -1 sentinel conversion in UTC.
        if (process.env.TZ === 'UTC') {
            setEnv('NETHACK_RECORDING_EPOCH', '0');
            assert.equal(parse('19691231235959'), 0n);
        }
        // Datestr survives both stack restoration and memory growth.
        const old = modules.map(module => module.HEAPU8.buffer);
        const before = format(1777723200n);
        modules.forEach(module => module._malloc(40n * 1024n * 1024n));
        modules.forEach((module, i) => {
            assert.notEqual(module.HEAPU8.buffer, old[i]);
            assert.equal(cstring(module, datePointers[i]), before);
        });
        format(1n); parse('20261101013000'); scope();
        const independent = await hybridFactory({ nethackPorted: createPortedRuntime(layouts) });
        const kept = cstring(modules[1], datePointers[1]);
        independent._probe_format(946684800n);
        assert.equal(cstring(modules[1], datePointers[1]), kept);
        console.log(`CALENDAR ${process.env.TZ}: ${comparisons} effective-C/hybrid clock, parsing and calendar comparisons passed.`);
    } finally { globalThis.Date = NativeDate; }
}
