// Configured original-C calendar versus JS-owned runtime, including DST policy.
// The memory64 oracle is test-only; production calendar/time imports no Wasm.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import { fileURLToPath, pathToFileURL } from 'node:url';
import { spawnSync } from 'node:child_process';
import { createHash } from 'node:crypto';
import { createJsRuntime } from '../js/ported/js-runtime.js';

const root = fileURLToPath(new URL('../', import.meta.url));
if (!process.argv.includes('--worker')) {
    for (const zone of ['America/New_York', 'America/Los_Angeles', 'UTC', 'Australia/Sydney', 'Pacific/Auckland']) {
        const result = spawnSync(process.execPath, [fileURLToPath(import.meta.url), '--worker'], {
            env: { ...process.env, TZ: zone }, encoding: 'utf8', timeout: 30000,
        });
        assert.equal(result.status, 0, `${zone}: ${result.error || result.stderr || result.stdout}`);
        process.stdout.write(result.stdout);
    }
    process.exit(0);
}
// getnow falls back to the current clock for a parsed -1/0 sentinel. Pin that
// clock for both providers, rather than comparing against the execution date.
const NativeDate = globalThis.Date;
globalThis.Date = class extends NativeDate {
    constructor(...args) { super(...(args.length ? args : [1777723200000])); }
    static now() { return 1777723200000; }
};
const {referenceBackend}=await import('./native-test-backend.mjs');
const reference=await referenceBackend('calendar')();
const runtime = createJsRuntime({ now: () => 1777723200n });
let comparisons = 0;
function nativeString(pointer) {
    pointer = Number(pointer);
    let end = pointer;
    while (reference.HEAPU8[end]) end++;
    return Buffer.from(reference.HEAPU8.subarray(pointer, end)).toString('latin1');
}
function nativeInput(value, callback) {
    const bytes = Buffer.from(value, 'latin1'), pointer = reference._malloc(BigInt(bytes.length + 1));
    reference.HEAPU8.set(bytes, Number(pointer)); reference.HEAPU8[Number(pointer) + bytes.length] = 0;
    try { return callback(BigInt(pointer)); } finally { reference._free(pointer); }
}
function setEnvironment(name, value) {
    runtime.setEnvironment(name, value);
    nativeInput(name, namePointer => value === null
        ? reference._probe_set_env(namePointer, 0n)
        : nativeInput(value, valuePointer => reference._probe_set_env(namePointer, valuePointer)));
}
function equal(js, c, label) { assert.equal(js, c, `${process.env.TZ}: ${label}`); comparisons++; }
const dates = ['20000110090000', '20260115090000', '20260715090000', '20260308013000',
    '20260308023000', '20261101013000', '20261101023000', '20260213000000', '20240229000102',
    '19000101000000', '19691231235959', '20380119031407', '20991231235959'];
for (const epoch of ['1777723200', '1768478400', '1784116800']) {
    setEnvironment('NETHACK_RECORDING_EPOCH', epoch);
    for (const date of dates) {
        setEnvironment('NETHACK_FIXED_DATETIME', date);
        equal(runtime.calendar('getnow'), reference._probe_now(), `now ${date}/${epoch}`);
        for (const [js, c] of [['getyear','year'], ['phase_of_the_moon','moon'],
            ['friday_13th','friday'], ['night','night'], ['midnight','midnight']])
            equal(runtime.calendar(js), reference['_probe_' + c](), `${js} ${date}/${epoch}`);
        for (const seconds of [0n, -1n, 1n, 951782462n, 2147483647n, 4102444799n]) {
            equal(runtime.calendar('yyyymmdd', seconds), reference._probe_date(seconds), 'yyyymmdd');
            equal(runtime.calendar('hhmmss', seconds), reference._probe_time(seconds), 'hhmmss');
            equal(runtime.memory.readString(runtime.calendar('yyyymmddhhmmss', seconds)),
                nativeString(reference._probe_format(seconds)), 'date text');
        }
    }
    for (const date of ['', 'x', '00000000000000', '99999999999999', '20260000000000',
        '20261340000000', '2026aa01000000', ...dates]) {
        const js = runtime.memory.withScope(scope => runtime.calendar('time_from_yyyymmddhhmmss', scope.cstring(date)));
        const c = nativeInput(date, pointer => reference._probe_parse(pointer));
        equal(js, c, 'parse ' + date);
    }
}
const before = runtime.memory.live.size;
for (let i = 0; i < 100; i++) runtime.calendar('getnow');
assert.equal(runtime.memory.live.size, before, 'calendar stack allocations leak');
console.log(`PASS: ${comparisons} configured-C/calendar/runtime comparisons in ${process.env.TZ}, including historical DST, normalization and temporary cleanup.`);
