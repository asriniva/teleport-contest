// Native differential mode collects assertion failures so later existing cases
// still execute. Every failure remains recorded and makes the process fail.
import {AsyncLocalStorage} from 'node:async_hooks';
import strictAssert from 'node:assert/strict';
import { writeFileSync } from 'node:fs';
const native = process.env.TELEPORT_NATIVE_TESTS === '1';
const failures = [];
const expectedFailure=new AsyncLocalStorage();
let assertions = 0, failureCount=0;
let completed = false;
process.once('beforeExit', () => { completed = true; });
function value(v) {
    if (typeof v === 'bigint') return `${v}n`;
    if (Buffer.isBuffer(v) || ArrayBuffer.isView(v)) return { bytes: v.byteLength, sample: Array.from(v).slice(0, 80) };
    if (typeof v === 'string' && v.length > 300) return v.slice(0, 300) + `… (${v.length} chars)`;
    return v;
}
function invoke(fn, args) {
    if(expectedFailure.getStore())return fn(...args);
    assertions++;
    try { return fn(...args); }
    catch (error) {
        if (!(error instanceof strictAssert.AssertionError)) throw error;
        const record = { message: error.message.slice(0, 1500), operator: error.operator, actual: value(error.actual), expected: value(error.expected), stack: error.stack?.split('\n').filter(line=>/^\s+at /.test(line)).slice(0,8).join('\n') };
        failureCount++;if(failures.length<100)failures.push(record);
        if (failureCount <= 3) console.error(`C REFERENCE DIFFERENCE ${failureCount}: ${record.message}`);
    }
}
const collecting = new Proxy((...args) => invoke(strictAssert, args), {
    get(target, key) {
        const property = strictAssert[key];
        if(['throws','rejects'].includes(key))return (...args)=>{if(typeof args[0]==='function'){const callback=args[0];args[0]=()=>expectedFailure.run(true,callback);}return invoke(property,args);};
        return typeof property === 'function' && key !== 'AssertionError' ? (...args) => invoke(property, args) : property;
    },
});
if (native) process.once('exit', () => {
    const file = new URL(`../.cache/native-assertions-${process.pid}.json`, import.meta.url);
    writeFileSync(file, JSON.stringify({ test: process.argv[1], runId: process.env.TELEPORT_NATIVE_RUN_ID, pid: process.pid, nativeInstances: globalThis.__nativeTestInstances || 0, isolatedCInstances: globalThis.__isolatedCReferenceInstances || 0, completed, assertions, failures: failureCount, sampledDetails: Math.min(failureCount,100), details: failures }, (key, v) => value(v), 2) + '\n');
    console.error(`Native assertions: ${assertions} checked, ${failureCount} failed.`);
    if (failureCount) process.exitCode = 1;
});
export default native ? collecting : strictAssert;
