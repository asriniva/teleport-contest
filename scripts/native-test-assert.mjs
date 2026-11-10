// Native differential mode collects assertion failures so later existing cases
// still execute. Every failure remains recorded and makes the process fail.
import strictAssert from 'node:assert/strict';
import { writeFileSync } from 'node:fs';
const native = process.env.TELEPORT_NATIVE_TESTS === '1';
const failures = [];
let assertions = 0;
let completed = false;
process.once('beforeExit', () => { completed = true; });
function value(v) {
    if (typeof v === 'bigint') return `${v}n`;
    if (Buffer.isBuffer(v) || ArrayBuffer.isView(v)) return { bytes: v.byteLength, sample: Array.from(v).slice(0, 80) };
    if (typeof v === 'string' && v.length > 300) return v.slice(0, 300) + `… (${v.length} chars)`;
    return v;
}
function invoke(fn, args) {
    assertions++;
    try { return fn(...args); }
    catch (error) {
        if (!(error instanceof strictAssert.AssertionError)) throw error;
        const record = { message: error.message.slice(0, 1500), operator: error.operator, actual: value(error.actual), expected: value(error.expected), stack: error.stack?.split('\n').slice(0, 8).join('\n') };
        failures.push(record);
        if (failures.length <= 3) console.error(`NATIVE DIFFERENCE ${failures.length}: ${record.message}`);
    }
}
const collecting = new Proxy((...args) => invoke(strictAssert, args), {
    get(target, key) {
        const property = strictAssert[key];
        return typeof property === 'function' && key !== 'AssertionError' ? (...args) => invoke(property, args) : property;
    },
});
if (native) process.once('exit', () => {
    const file = new URL(`../.cache/native-assertions-${process.pid}.json`, import.meta.url);
    writeFileSync(file, JSON.stringify({ test: process.argv[1], runId: process.env.TELEPORT_NATIVE_RUN_ID, pid: process.pid, nativeInstances: globalThis.__nativeTestInstances || 0, completed, assertions, failures: failures.length, details: failures }, (key, v) => value(v), 2) + '\n');
    console.error(`Native assertions: ${assertions} checked, ${failures.length} failed.`);
    if (failures.length) process.exitCode = 1;
});
export default native ? collecting : strictAssert;
