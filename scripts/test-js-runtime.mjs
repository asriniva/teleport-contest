// Native original-C comparisons for translated functions on JS-owned memory.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import { fileURLToPath } from 'node:url';
import { spawnSync } from 'node:child_process';
import { createJsRuntime, JS_RUNTIME_LAYOUTS, CPanic } from '../js/nethack/runtime.js';
import { CMemory } from '../js/c-runtime/heap.js';
import { C_ERRNO } from '../js/c-runtime/stdlib.js';
import { C, R, T, withCEnvironment } from '../js/c-runtime/context.js';

const root = fileURLToPath(new URL('../', import.meta.url));
// A separate worktree may borrow prepared reference sources read-only.
const reference = process.env.STANDALONE_REFERENCE_ROOT || root;
const scratch = path.join(root, '.cache/js-dependency-runtime');
fs.mkdirSync(scratch, { recursive: true });
const oracle = path.join(scratch, 'original-c-runtime');
const compiler = process.env.CC || path.join(reference, '.cache/wasm64-build/host-cc');
const sources = ['strutil', 'alloc', 'isaac64', 'nhmd4'].map(name => path.join(reference, 'nethack-c/upstream/src', name + '.c'));
const built = spawnSync(compiler, ['-O2', '-DNOPANICTRACE', '-Dmalloc=js_probe_malloc', '-Drealloc=js_probe_realloc',
    '-I' + path.join(reference, '.cache/wasm64-build/tree/include'),
    path.join(root, 'scripts/js-runtime-probe.c'), ...sources, '-o', oracle], { encoding: 'utf8' });
assert.equal(built.status, 0, built.error?.message || built.stderr);
const runtime = createJsRuntime({ initialBytes: 1024, maximumBytes: 2 * 1024 * 1024 });
const { memory, libc } = runtime;
const commands = [], expected = [];
const hex = bytes => Buffer.from(bytes).toString('hex');
const token = input => hex(typeof input === 'string' ? CMemory.byteString(input) : input) || '-';
function add(command, output) { commands.push(command); expected.push(output); }
function clean() { assert.equal(C, undefined); assert.equal(R, undefined); assert.equal(T, undefined); }
const layout = JS_RUNTIME_LAYOUTS.strutil;
add('L', [layout.size, layout.len, layout.str, layout.buf, layout.bufSize, layout.largestInt,
    JS_RUNTIME_LAYOUTS.isaac64.size, JS_RUNTIME_LAYOUTS.nhmd4.size].join(','));

let random = 0x13579bdf;
function next() { random ^= random << 13; random ^= random >>> 17; random ^= random << 5; return random >>> 0; }
function noise(n) { return Uint8Array.from({ length: n }, () => next() & 255); }
const patterns = ['', '*', '?', 'a*b', '**a?*', '[a]', 'A*B', '\\*', '\xff*'];
const texts = ['', 'a', 'Ab', 'a\nb', '[a]', '\xff', '\x80', 'abc\0ignored'];
for (let i = 0; i < 500; i++) {
    patterns.push(Array.from({ length: next() % 9 }, () => 'aAbB*?'[next() % 6]).join(''));
    texts.push(Array.from({ length: next() % 13 }, () => 'aAbB \n'[next() % 6]).join(''));
}
for (let i = 0; i < patterns.length; i++) for (const ci of [0, 1]) {
    const pattern = patterns[i], text = texts[i % texts.length];
    const result = memory.withScope(scope => runtime.strutil(ci ? 'pmatchi' : 'pmatch', scope.cstring(pattern), scope.cstring(text)));
    add(`P ${ci} ${token(pattern)} ${token(text)}`, String(result)); clean();
}
const buffer = runtime.createStrbuf();
function bufferState() {
    return [buffer.len, buffer.str === 0 ? 0 : buffer.str === buffer.buf ? 1 : 2,
        buffer.str ? hex(memory.readBytes(buffer.str, memory.strlen(buffer.str))) : ''].join(',');
}
for (const input of ['', 'a\nb\n', 'x'.repeat(255), 'q'.repeat(1024), '\xff\x80', '\0ignored', 'z'.repeat(15000)]) {
    memory.withScope(scope => runtime.strutil('strbuf_append', buffer, scope.cstring(input)));
    add('A ' + token(input), bufferState());
    runtime.strutil('strbuf_nl_to_crlf', buffer); add('N', bufferState());
    clean();
}
for (const capacity of [1, 30000, 10, 50000]) {
    runtime.strutil('strbuf_reserve', buffer, capacity); add('R ' + capacity, bufferState());
}
runtime.strutil('strbuf_empty', buffer); add('E', bufferState());
memory.withScope(scope => runtime.strutil('strbuf_append', buffer, scope.cstring('after free')));
add('A ' + token('after free'), bufferState());
runtime.strutil('strbuf_empty', buffer); add('E', bufferState());

for (const input of ['', '0', '  -17tail', '+0x1f!', '0777x', '0x', '+', '9223372036854775807',
    '9223372036854775808', '-9223372036854775808', '-9223372036854775809',
    '18446744073709551615', '18446744073709551616', '-18446744073709551615', 'zZ', '9'.repeat(100)]) {
    for (const base of [0, 2, 8, 10, 16, 36]) for (const unsigned of [0, 1]) {
        const output = memory.withScope(scope => {
            const p = scope.cstring(input), end = scope.alloc(8); libc.errno = 0;
            const value = (unsigned ? libc.strtoull : libc.strtoll)(p, end, base);
            const error = libc.errno === C_ERRNO.EINVAL ? 'EINVAL' : libc.errno === C_ERRNO.ERANGE ? 'ERANGE' : libc.errno === 0 ? '0' : 'OTHER';
            return [value.toString(), Number(memory.view.getBigUint64(end, true)) - p, error].join(',');
        });
        add(`T ${base} ${unsigned} ${token(input)}`, output);
    }
}
for (const value of [-2147483648, -12345, -1, 0, 1, 9, 12345, 2147483647]) {
    const formatted = libc.format('%+08d|%#x|%#o|%.0d|%8.4d', value, value, value, 0, value);
    add('F ' + value, token(formatted));
}
for (let kind = 0; kind < 4; kind++) {
    const limited = createJsRuntime({ initialBytes: 256, maximumBytes: 512 });
    let message;
    try {
        if (kind === 0) limited.alloc('alloc', 1025);
        else if (kind === 1) limited.alloc('re_alloc', limited.alloc('alloc', 8), 1025);
        else limited.alloc(kind === 2 ? 'FITSint_' : 'FITSuint_', kind === 2 ? 2147483648n : 4294967296n, 'runtime-test.c', 12);
        assert.fail('Expected original allocation/cast panic');
    } catch (error) { assert.ok(error instanceof CPanic); message = error.message; }
    add('O ' + kind, token(message)); clean();
}
for (const length of [0, 1, 55, 56, 57, 63, 64, 65, 127, 128, 2048]) {
    const input = noise(length);
    for (const chunk of [1, 3, 64, 67]) {
        const digest = runtime.createMD4();
        for (let at = 0; at < input.length; at += chunk) digest.update(input.subarray(at, at + chunk));
        const output = digest.final();
        add(`D ${token(input)} ${chunk}`, hex(output) + ',' + hex(memory.readBytes(digest.address, JS_RUNTIME_LAYOUTS.nhmd4.size)));
        memory.free(digest.address);
    }
}
for (const length of [0, 1, 255, 256, 2048, 2050]) {
    const seed = noise(length), generator = runtime.createIsaac(seed);
    const values = Array.from({ length: 1000 }, () => generator.next().toString());
    add(`I ${token(seed)} 1000`, values.join(',') + ';' + hex(memory.readBytes(generator.address, JS_RUNTIME_LAYOUTS.isaac64.size)));
    memory.free(generator.address);
}
const native = spawnSync(oracle, [], { input: commands.join('\n') + '\n', encoding: 'utf8',
    maxBuffer: 16 * 1024 * 1024, timeout: 30000 });
assert.equal(native.status, 0, native.error?.message || native.stderr);
const actual = native.stdout.trimEnd().split('\n');
assert.equal(actual.length, expected.length);
for (let i = 0; i < expected.length; i++) assert.equal(actual[i], expected[i], `original C command ${i}: ${commands[i].slice(0, 100)}`);

// Allocation identities, aliases, failure and scopes are independent runtime
// contracts; absolute native malloc addresses are deliberately not compared.
const small = new CMemory({ initialBytes: 64, maximumBytes: 256 });
const a = small.malloc(24), b = small.malloc(24);
small.HEAPU8.fill(0xa5, a, a + 24);
const moved = small.realloc(a, 64);
assert.ok(moved); assert.ok(small.readBytes(moved, 24).every(x => x === 0xa5));
assert.equal(small.realloc(moved, 1000), 0);
assert.ok(small.readBytes(moved, 24).every(x => x === 0xa5));
small.free(b); small.free(moved); assert.throws(() => small.free(moved), RangeError);
const zero = small.calloc(4, 8); assert.ok(small.readBytes(zero, 32).every(x => x === 0));
small.free(zero); assert.equal(small.calloc(Number.MAX_SAFE_INTEGER, 8), 0);
const before = memory.live.size;
assert.throws(() => memory.withScope(scope => { scope.cstring('temporary'); throw Error('unwind'); }), /unwind/);
assert.equal(memory.live.size, before);
const other = createJsRuntime({ initialBytes: 512 });
assert.equal(runtime.services.allocState.ptrbufidx, 0);
const {referenceBackend}=await import('./native-test-backend.mjs');
const nativePointers=await referenceBackend('alloc')();
for (let i = 0; i < 7; i++) {
    const pointer = runtime.alloc('fmt_ptr', i);
    const expected=nativePointers._probe_format(BigInt(i));let end=Number(expected);
    while(nativePointers.HEAPU8[end])end++;
    assert.equal(memory.readString(pointer),Buffer.from(nativePointers.HEAPU8.slice(Number(expected),end)).toString('latin1'));
}
assert.equal(other.services.allocState.ptrbufidx, 0);
assert.throws(() => runtime.alloc('FITSint_', 2147483648n, 'runtime-test.c', 12), CPanic);
clean();
withCEnvironment(runtime.services, () => {
    const outer = C;
    other.alloc('dupstr', other.memory.cstring('independent'));
    assert.equal(C, outer);
}); clean();
assert.ok(memory.generation > 0, 'growth must occur while live buffer views exist');
assert.equal(libc.format('%f', 1.5), '1.500000');
assert.throws(() => libc.format('%Lf', 1.5), /Long-double formatting is not supported/);
const bounded = new CMemory({ initialBytes: 64, maximumBytes: 64 });
const boundedRuntime = (await import('../js/c-runtime/stdlib.js')).createCStdlib(bounded);
const unterminated = bounded.malloc(48);
bounded.HEAPU8.fill(65, unterminated, 64);
assert.equal(boundedRuntime.format('%.3s', unterminated), 'AAA');
assert.equal(boundedRuntime.format('%.0s', 100000), '');
memory.withScope(scope => {
    const input = scope.cstring('abc'); libc.errno = 73;
    assert.equal(libc.atoi(input), 0); assert.equal(libc.errno, 73);
    assert.equal(libc.atol(input), 0n); assert.equal(libc.errno, 73);
});
const reused = new CMemory({ initialBytes: 128 });
let retained;
reused.withScope(scope => { const temporary = scope.alloc(16); reused.free(temporary); retained = reused.malloc(16); });
assert.ok(reused.live.has(retained), 'scope cleanup must not free a reused allocation owned elsewhere');
console.log(`PASS: ${commands.length} original-C runtime comparisons; 6000 ISAAC values and full states, MD4 chunk/digest/cleared states, strbuf/wildcards, integer parsing and formatting.`);
console.log('PASS: JS-owned allocation/reallocation/growth/aliases/failure, scoped cleanup, nested instance isolation and restored C bindings; no Module or Wasm used by the service provider.');
