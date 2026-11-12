// Original configured NetHack wrapper versus unchanged JS translation using
// JS-owned memory and regex. The memory64 reference is development-only.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import { fileURLToPath, pathToFileURL } from 'node:url';
import { createHash } from 'node:crypto';
import { createJsRuntime, JS_RUNTIME_LAYOUTS } from '../js/nethack/runtime.js';
import { C, R, T } from '../js/c-runtime/context.js';

const root = fileURLToPath(new URL('../', import.meta.url));
const {referenceBackend}=await import('./native-test-backend.mjs');
const native=await referenceBackend('posixregex')();
const runtime = createJsRuntime({ initialBytes: 512 });
const { memory } = runtime;
const metadata = JSON.parse(fs.readFileSync(path.join(root, 'js/wasm/tu-layouts.json'))).posixregex;
const layout = JS_RUNTIME_LAYOUTS.posixregex;
for (const [field, value] of Object.entries({ size: layout.size, re: layout.re, err: layout.err,
    regexSize: layout.regexSize, BUFSZ: layout.bufferSize })) assert.equal(value, metadata[field], field);
let comparisons = 0;
const nativeString = pointer => {
    let end = Number(pointer);
    while (native.HEAPU8[end]) end++;
    return Buffer.from(native.HEAPU8.slice(Number(pointer), end)).toString('latin1');
};
function input(value, callback) {
    if (value === null) return callback(0, 0n);
    const bytes = typeof value === 'string' ? Buffer.from(value, 'latin1') : value;
    const pointer = BigInt(native._malloc(BigInt(bytes.length + 1)));
    native.HEAPU8.set(bytes, Number(pointer)); native.HEAPU8[Number(pointer) + bytes.length] = 0;
    try { return memory.withScope(scope => callback(scope.cstring(Uint8Array.from(bytes)), pointer)); }
    finally { native._free(pointer); }
}
function equal(a, b, label) {
    assert.equal(a, b, label); comparisons++;
    assert.equal(C, undefined); assert.equal(R, undefined); assert.equal(T, undefined);
}
function error(re, pointer) {
    return memory.withScope(scope => {
        const destination = scope.alloc(layout.bufferSize + 16), buffer = destination + 8;
        const reference = native._malloc(BigInt(layout.bufferSize + 16)), target = Number(reference) + 8;
        memory.HEAPU8.fill(0xa5, destination, destination + layout.bufferSize + 16);
        native.HEAPU8.fill(0xa5, Number(reference), Number(reference) + layout.bufferSize + 16);
        try {
            equal(runtime.posixregex('regex_error_desc', re, buffer), buffer, 'Caller-owned error buffer');
            equal(native._probe_error(pointer, BigInt(target)), BigInt(target), 'Native error buffer');
            assert.deepEqual(memory.readBytes(destination, layout.bufferSize + 16),
                Uint8Array.from(native.HEAPU8.slice(Number(reference), Number(reference) + layout.bufferSize + 16)));
            comparisons++;
            return [memory.readString(buffer), nativeString(BigInt(target))];
        } finally { native._free(reference); }
    });
}
equal(input('a', (s, c) => runtime.posixregex('regex_compile', s, 0)), 0, 'NULL regex compile');
equal(runtime.posixregex('regex_match', 0, 0), native._probe_match(0n, 0n), 'NULL regex match');
assert.deepEqual(error(0, 0n), ['no regexp', 'no regexp']);
const patterns = ['', 'a', '^a$', 'a|b', '(ab)+', '[a-z]+', '[[:digit:]]{2,4}',
    '.', 'a.*b', 'a?b*', '(a)\\1', '\\bword\\b', 'a{0}', 'a{2,3}', '[^x]',
    '^[[:space:]]*$', '[', '(', '*a', 'a{', 'a{3,2}', '[z-a]', 'a\\',
    '[[:nope:]]', 'a{999999999999}', Buffer.from([65, 0, 91]), Buffer.from([0xff, 0x80])];
const texts = [null, '', 'a', 'b', 'A', 'aa', 'abab', 'word', 'wordy', '12',
    '12345', 'a\nb', ' ', '\n', Buffer.from([0xff, 0x80]), Buffer.from([65, 0, 66])];
const initial = memory.live.size;
for (const pattern of patterns) {
    const address = runtime.posixregex('regex_init'), re = runtime.regexContext(address);
    const pointer = native._probe_init();
    assert.ok(address && pointer);
    const status = input(pattern, (s, c) => {
        const result = runtime.posixregex('regex_compile', s, re);
        equal(result, native._probe_compile(c, pointer), 'Compile result');
        equal(re.err, native._probe_err(pointer), 'Compile status');
        return result;
    });
    const [jsDescription, cDescription] = error(re, pointer);
    equal(jsDescription, cDescription, 'Compile description');
    if (status) for (const text of texts) {
        input(text, (s, c) => {
            equal(runtime.posixregex('regex_match', s, re), native._probe_match(c, pointer), 'Match result');
            equal(re.err, native._probe_err(pointer), 'Match preserves nonmatch error');
        });
    }
    // All views remain live across ordinary ArrayBuffer growth.
    const large = memory.malloc(50000);
    equal(re.err, native._probe_err(pointer), 'Live error field after growth');
    memory.free(large);
    runtime.posixregex('regex_free', re); native._probe_free(pointer);
}
assert.equal(memory.live.size, initial, 'Wrapper allocation leak');
const second = createJsRuntime();
const re = runtime.regexContext(runtime.posixregex('regex_init'));
memory.withScope(scope => runtime.posixregex('regex_compile', scope.cstring('a'), re));
assert.throws(() => second.services.regexec(re.re, second.memory.cstring('a'), 0, 0, 0), /successfully compiled/);
runtime.posixregex('regex_free', re);
console.log(`PASS: ${comparisons} configured original-C regex-wrapper comparisons on JS-owned memory; layout/error-buffer guards, growth, cleanup, NULL inputs and instance isolation.`);
