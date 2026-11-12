import { DataView, assertStackRestored, allocationMetric, assertMemoryGrowth, memoryCheckpoint, referenceBackend, referenceLabel } from './native-test-backend.mjs';
const referenceFactory = referenceBackend('strutil', emscriptenReferenceFactory);
import assert from './native-test-assert.mjs';
import { readFileSync } from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/strutil-reference.mjs';
import hybridFactory from '../.cache/tu-probes/strutil-hybrid.mjs';
import { createPortedRuntime } from '../js/backends/emscripten/runtime.js';
import { C } from '../js/c-runtime/context.js';

const layouts = JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json', import.meta.url)));
const layout = layouts.strutil;
const modules = [await referenceFactory(), await hybridFactory({ nethackPorted: createPortedRuntime(layouts) })];
let comparisons = 0;
const bytes = value => typeof value === 'string' ? Buffer.from(value) : value;
function strings(value) {
    const data = bytes(value);
    return modules.map(module => {
        const pointer = module._malloc(BigInt(data.length + 1));
        module.HEAPU8.set(data, Number(pointer));
        module.HEAPU8[Number(pointer) + data.length] = 0;
        return pointer;
    });
}
function release(pointers) {
    modules.forEach((module, i) => module._free(pointers[i]));
}
function contexts() {
    return modules.map(module => {
        const pointer = module._malloc(BigInt(layout.size));
        module.HEAPU8.fill(0xa5, Number(pointer), Number(pointer) + layout.size);
        module._probe_init(BigInt(pointer));
        return pointer;
    });
}
function cstring(module, pointer) {
    const start = Number(pointer);
    let end = start;
    while (module.HEAPU8[end]) end++;
    return Buffer.from(module.HEAPU8.slice(start, end));
}
function state(pointers) {
    const values = modules.map((module, i) => {
        const pointer = Number(pointers[i]), view = new DataView(module.HEAPU8.buffer);
        const string = Number(view.getBigUint64(pointer + layout.str, true));
        return {
            len: view.getInt32(pointer + layout.len, true),
            storage: !string ? 'null' : string === pointer + layout.buf ? 'inline' : 'allocated',
            content: string ? cstring(module, string) : null,
            inlineBytes: Buffer.from(module.HEAPU8.slice(pointer + layout.buf, pointer + layout.buf + layout.bufSize)),
            padding: Buffer.from(module.HEAPU8.slice(pointer + 4, pointer + layout.str)),
        };
    });
    assert.deepEqual(values[1], values[0]);
    comparisons++;
    assert.equal(C, undefined, 'ABI scope must be restored after every call');
    return values[1];
}
function call(pointers, name, argument) {
    modules.forEach((module, i) => module['_probe_' + name](BigInt(pointers[i]), argument));
    return state(pointers);
}
function append(pointers, value) {
    const input = strings(value);
    modules.forEach((module, i) => module._probe_append(BigInt(pointers[i]), BigInt(input[i])));
    release(input);
    return state(pointers);
}
// Probe every inline/capacity boundary, exact allocation policy, empty/reuse,
// trailing and repeated newlines, existing CRLF and all non-NUL byte values.
for (const length of [0, 1, 254, 255, 256, 257, 511, 512, 513, 4096]) {
    const pointers = contexts();
    state(pointers);
    call(pointers, 'crlf');
    for (const capacity of [0, 1, 255, 256, 257, 1024]) call(pointers, 'reserve', capacity);
    append(pointers, Uint8Array.from({ length }, (_, i) => i % 255 + 1));
    append(pointers, '\nlast\r\n\n');
    call(pointers, 'crlf');
    call(pointers, 'crlf');
    call(pointers, 'empty');
    call(pointers, 'empty');
    append(pointers, 'after-empty\n');
    call(pointers, 'crlf');
    call(pointers, 'empty');
    release(pointers);
}
for (const text of ['', '\n', '\n\n', 'start\n', '\nend', 'a\nb\nc', '\r\n', 'abc']) {
    const pointers = contexts();
    append(pointers, text);
    const result = call(pointers, 'crlf');
    assert.deepEqual(result.content, Buffer.from(text.replaceAll('\n', '\r\n')));
    call(pointers, 'empty');
    release(pointers);
}
// Independent buffers interleaved through reallocations and disposal.
const first = contexts(), second = contexts();
append(first, 'first');
append(second, 'second\n');
append(first, 'x'.repeat(300));
call(second, 'crlf');
call(first, 'empty');
assert.equal(state(second).content.toString(), 'second\r\n');
call(second, 'empty');
release(first); release(second);

function match(pattern, text, ci) {
    const patterns = strings(pattern), texts = strings(text);
    const values = modules.map((module, i) => module._probe_match(BigInt(patterns[i]), BigInt(texts[i]), ci));
    assert.equal(values[1], values[0], `${Buffer.from(bytes(pattern)).toString('hex')} / ${Buffer.from(bytes(text)).toString('hex')}, ci=${ci}`);
    comparisons++;
    release(patterns); release(texts);
}
const patterns = ['', '*', '?', '**', '*?', '?*', 'a', 'A', 'a*', '*b', 'a?b', '*a*b*', '**a**', 'file?.*', 'a*b?c', '?'.repeat(64)];
const texts = ['', 'a', 'A', 'b', 'ab', 'aab', 'aBc', 'abc', 'file1.txt', 'a'.repeat(64)];
for (const pattern of patterns) for (const text of texts) for (const ci of [0, 1]) match(pattern, text, ci);
// Exhaustive short words/patterns exercise recursive wildcard alternatives.
function words(alphabet, depth) {
    const result = [''];
    let level = [''];
    for (let i = 0; i < depth; i++) {
        level = level.flatMap(prefix => alphabet.map(c => prefix + c));
        result.push(...level);
    }
    return result;
}
for (const pattern of words(['a', 'B', '*', '?'], 3)) {
    for (const text of words(['a', 'b', 'B'], 3)) for (const ci of [0, 1]) match(pattern, text, ci);
}
for (let byte = 1; byte < 256; byte++) {
    match(Uint8Array.of(byte), Uint8Array.of(byte), 0);
    match(Uint8Array.of(byte), Uint8Array.of(byte), 1);
    match('?', Uint8Array.of(byte), 0);
    match('*', Uint8Array.of(byte), 1);
}
// Length guard must call the original panic with the same message. The probe's
// isolated panic uses setjmp/longjmp; production panic/exit is not replaced.
for (const length of [0, 1, 255, layout.largestInt - 1, layout.largestInt, layout.largestInt + 1]) {
    const pointers = strings('x'.repeat(length));
    const results = modules.map((module, i) => module._probe_guarded_strlen(BigInt(pointers[i])));
    assert.equal(results[1], results[0]);
    assert.equal(results[1], length < layout.largestInt ? length : -1);
    const messages = modules.map(module => cstring(module, module._probe_message()).toString());
    assert.equal(messages[1], messages[0]);
    assert.equal(messages[1], length < layout.largestInt ? '' : 'source-path.c:777 string too long');
    assert.equal(C, undefined);
    comparisons++;
    release(pointers);
}
// Force growth inside the C allocator called from JS, while the strbuf proxy
// already exists. C and JS must both continue using the new linear-memory views.
const growing = contexts();
append(growing, 'before-growth\n');
const previous = modules.map(module => memoryCheckpoint(module));
call(growing, 'reserve', 40 * 1024 * 1024);
modules.forEach((module, i) => assertMemoryGrowth(module, previous[i]));
append(growing, 'after-growth');
call(growing, 'crlf');
call(growing, 'empty');
release(growing);
console.log(`STRUTIL: ${comparisons} ${referenceLabel}/hybrid buffer, byte-pattern and fatal-length comparisons checked.`);
