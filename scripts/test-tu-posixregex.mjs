import { assertStackRestored, allocationMetric, assertMemoryGrowth, memoryCheckpoint, referenceBackend, referenceLabel } from './native-test-backend.mjs';
const referenceFactory = referenceBackend('posixregex', emscriptenReferenceFactory);
import assert from './native-test-assert.mjs';
import { readFileSync } from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/posixregex-reference.mjs';
import hybridFactory from '../.cache/tu-probes/posixregex-hybrid.mjs';
import { createPortedRuntime } from '../js/ported/wasm-runtime.js';
import { C, R, T } from '../js/ported/c-runtime.js';

const layouts = JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json', import.meta.url)));
const layout = layouts.posixregex;
const modules = [await referenceFactory(), await hybridFactory({ nethackPorted: createPortedRuntime(layouts) })];
const stacks = modules.map(module => module._probe_stack());
let comparisons = 0;
function scope() {
    assert.equal(C, undefined); assert.equal(R, undefined); assert.equal(T, undefined);
    modules.forEach((module, i) => assertStackRestored(module, stacks[i]));
}
function bytes(module, pointer) {
    let end = Number(pointer);
    while (module.HEAPU8[end]) end++;
    return Buffer.from(module.HEAPU8.slice(Number(pointer), end));
}
function allocate(module, value) {
    if (value === null) return 0;
    const data = Buffer.isBuffer(value) ? value : Buffer.from(value);
    const pointer = module._malloc(BigInt(data.length + 1));
    module.HEAPU8.set(data, Number(pointer)); module.HEAPU8[Number(pointer) + data.length] = 0;
    return pointer;
}
modules.forEach(module => {
    assert.equal(Number(module._probe_context_size()), layout.NhregexSize);
    for (let i = 0; i < module._probe_layout_count(); i++) {
        const key = bytes(module, module._probe_layout_name(i)).toString();
        assert.equal(Number(module._probe_layout_value(i)), layout[key], key);
    }
    // Initialization must have happened before any nhregex API invocation.
    assert.equal(bytes(module, module._probe_identifier()).toString(), 'posixregex');
});
function init() {
    const result = modules.map(module => module._probe_init());
    result.forEach(pointer => assert.notEqual(Number(pointer), 0)); scope(); comparisons++;
    return result;
}
function compile(pattern, regexes) {
    const result = modules.map((module, i) => {
        const pointer = allocate(module, pattern);
        const status = module._probe_compile(BigInt(pointer), BigInt(regexes[i]));
        module._free(pointer);
        return { status, err: regexes[i] ? module._probe_err(BigInt(regexes[i])) : null };
    });
    assert.deepEqual(result[1], result[0]); scope(); comparisons++;
    return result[0];
}
function match(text, regexes) {
    const result = modules.map((module, i) => {
        const pointer = allocate(module, text);
        const status = module._probe_match(BigInt(pointer), BigInt(regexes[i]));
        if (pointer) module._free(pointer);
        return { status, err: regexes[i] ? module._probe_err(BigInt(regexes[i])) : null };
    });
    assert.deepEqual(result[1], result[0]); scope(); comparisons++;
    return result[0];
}
function error(regexes, keep = false) {
    const allocations = modules.map(module => module._malloc(BigInt(layout.BUFSZ + 16)));
    const results = modules.map((module, i) => {
        const base = Number(allocations[i]), buffer = base + 8;
        module.HEAPU8.fill(0xa5, base, base + layout.BUFSZ + 16);
        const result = module._probe_error(BigInt(regexes[i]), BigInt(buffer));
        assert.equal(Number(result), buffer, 'Error description returns the caller buffer');
        assert.ok(module.HEAPU8.slice(base, buffer).every(value => value === 0xa5));
        assert.ok(module.HEAPU8.slice(buffer + layout.BUFSZ, buffer + layout.BUFSZ + 8).every(value => value === 0xa5));
        return { text: bytes(module, BigInt(buffer)).toString('hex'), raw: Buffer.from(module.HEAPU8.slice(buffer, buffer + layout.BUFSZ)) };
    });
    assert.deepEqual(results[1], results[0]); scope(); comparisons++;
    if (!keep) modules.forEach((module, i) => module._free(allocations[i]));
    return { result: results[0], allocations: keep ? allocations : null };
}
function free(regexes) {
    modules.forEach((module, i) => module._probe_free(BigInt(regexes[i]))); scope(); comparisons++;
}
assert.equal(compile('valid', [0, 0]).status, 0);
assert.equal(match('text', [0, 0]).status, 0);
assert.equal(match(null, [0, 0]).status, 0);
assert.equal(Buffer.from(error([0, 0]).result.text, 'hex').toString(), 'no regexp');
const patterns = ['', 'a', '^a$', 'a|b', '(ab)+', '[a-z]+', '[[:digit:]]{2,4}', '.', 'a.*b', 'a?b*',
    '(a)\\1', '\\(foo\\)', '\\bword\\b', 'a{0}', 'a{2,3}', '[^x]', '^[[:space:]]*$',
    '[', '(', '*a', 'a{', 'a{3,2}', '[z-a]', 'a\\', '[[:nope:]]', 'a{999999999999}',
    Buffer.from([65, 0, 91]), Buffer.from([0xff, 0x80]), 'é', '^.$', '(a|aa)*b'];
const texts = [null, '', 'a', 'b', 'A', 'aa', 'abab', 'foo', '(foo)', 'word', 'wordy', '12', '12345', 'a\nb', ' ', '\n',
    'é', Buffer.from([0xff, 0x80]), Buffer.from([65, 0, 66])];
for (const pattern of patterns) {
    const regexes = init();
    const compiled = compile(pattern, regexes);
    const description = error(regexes);
    if (compiled.status) {
        assert.equal(Buffer.from(description.result.text, 'hex').toString(), 'no explanation');
        for (const text of texts) match(text, regexes);
        // A match or ordinary non-match does not reset a prior error value.
        for (const err of [layout.REG_NOMATCH, 12345, -1]) {
            modules.forEach((module, i) => module._probe_set_err(BigInt(regexes[i]), err));
            const before = modules.map((module, i) => module._probe_err(BigInt(regexes[i])));
            match('clearly no matching text', regexes);
            modules.forEach((module, i) => assert.equal(module._probe_err(BigInt(regexes[i])), before[i]));
            error(regexes);
        }
    } else assert.notEqual(description.result.text, '', 'Invalid pattern has a native engine explanation');
    const retained = error(regexes, true);
    free(regexes);
    modules.forEach((module, i) => {
        const buffer = Number(retained.allocations[i]) + 8;
        assert.deepEqual(Buffer.from(module.HEAPU8.slice(buffer, buffer + layout.BUFSZ)), retained.result.raw, 'Caller error buffer survives regex_free');
        module._free(retained.allocations[i]);
    });
}
// Deliberately choose an unmatching literal: REG_NOMATCH must preserve err.
const regexes = init(); assert.equal(compile('^literal$', regexes).status, 1);
modules.forEach((module, i) => module._probe_set_err(BigInt(regexes[i]), 73));
assert.deepEqual(match('different', regexes), { status: 0, err: 73 });
assert.deepEqual(match('literal', regexes), { status: 1, err: 73 });
const oldBuffers = modules.map(module => memoryCheckpoint(module));
modules.forEach(module => module._malloc(40n * 1024n * 1024n));
modules.forEach((module, i) => assertMemoryGrowth(module, oldBuffers[i]));
assert.deepEqual(match('literal', regexes), { status: 1, err: 73 });
error(regexes); free(regexes);
for (let i = 0; i < 50; i++) {
    const regexes = init(); compile(i % 2 ? '^repeat[[:digit:]]+$' : '[', regexes);
    if (i % 2) { assert.equal(match('repeat123', regexes).status, 1); assert.equal(match('repeatX', regexes).status, 0); }
    error(regexes); free(regexes);
}
const independent = await hybridFactory({ nethackPorted: createPortedRuntime(layouts) });
assert.equal(bytes(independent, independent._probe_identifier()).toString(), 'posixregex');
const independentRegex = independent._probe_init(), pattern = allocate(independent, '^independent$'), string = allocate(independent, 'independent');
assert.equal(independent._probe_compile(BigInt(pattern), BigInt(independentRegex)), 1);
assert.equal(independent._probe_match(BigInt(string), BigInt(independentRegex)), 1);
independent._probe_free(BigInt(independentRegex)); independent._free(pattern); independent._free(string);
scope(); comparisons++;
console.log(`POSIXREGEX: ${comparisons} ${referenceLabel}/hybrid native-engine, error-buffer, lifecycle and startup comparisons checked.`);
