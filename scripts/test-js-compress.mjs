// Standalone JS .Z differential tests. Native programs are test oracles only.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import { fileURLToPath } from 'node:url';
import { spawnSync } from 'node:child_process';
import { compressUnixZ, decompressUnixZ } from '../js/services/unix-compress.js';

const root = fileURLToPath(new URL('../', import.meta.url));
const work = path.join(root, '.cache/js-dependency-compression');
fs.mkdirSync(work, { recursive: true });
function command(executable, args, expected = [0]) {
    const result = spawnSync(executable, args, { encoding: 'utf8', timeout: 60000 });
    assert.ok(expected.includes(result.status), `${executable}: ${result.error || result.stderr || result.status}`);
    return result;
}
const oracle = path.join(work, 'compress-oracle');
// Pin libc buffer sizes to the current Emscripten service, even on hosts whose
// native BUFSIZ differs: ncompress's ratio checkpoints depend on batching.
command(process.env.CC || 'cc', ['-O2', '-std=gnu17', '-DIBUFSIZ=1024', '-DOBUFSIZ=1024',
    path.join(root, 'nethack-c/wasm/compress-service.c'),
    path.join(root, 'scripts/compress-probe.c'), '-o', oracle]);
let comparisons = 0;
function equal(actual, expected, context) {
    assert.ok(Buffer.from(actual).equals(Buffer.from(expected)),
        `${context}: ${actual.length} actual bytes, ${expected.length} expected bytes`);
    ++comparisons;
}
function reference(input, unpack = false) {
    const plain = path.join(work, 'oracle-plain'), packed = plain + '.Z';
    fs.writeFileSync(unpack ? packed : plain, input);
    const status = command(oracle, [unpack ? '1' : '0', plain, packed], [0, 1, 2]).status;
    return { status, bytes: fs.readFileSync(unpack ? plain : packed) };
}
function inspectCodes(input) {
    // Independent format walk counts CLEAR and width transitions; the content
    // comparison below separately checks every expanded dictionary string.
    let bits = 9, next = input[2] & 0x80 ? 257 : 256, maximum = 511;
    let offset = 24, base = 24, first = true, clears = 0;
    const widths = new Set([bits]), maxBits = input[2] & 31, limit = 1 << maxBits;
    const align = () => { offset += (bits * 8 - (offset - base) % (bits * 8)) % (bits * 8); base = offset; };
    while (true) {
        if (next > maximum) { align(); ++bits; widths.add(bits); maximum = bits === maxBits ? limit : (1 << bits) - 1; }
        if (offset + bits > input.length * 8) break;
        let code = 0;
        for (let i = 0; i < bits; ++i) code |= ((input[(offset + i) >> 3] >> ((offset + i) & 7)) & 1) << i;
        offset += bits;
        if (first) { first = false; continue; }
        if (code === 256 && (input[2] & 0x80)) { ++clears; align(); bits = 9; next = 256; maximum = 511; continue; }
        if (next < limit) ++next;
    }
    return { clears, widths };
}
let random = 0x12345678;
const noise = Buffer.from(Array.from({ length: 1200000 }, () => {
    random ^= random << 13; random ^= random >>> 17; random ^= random << 5;
    return random & 255;
}));
const fixtures = [
    Buffer.alloc(0), Buffer.from('x'), Buffer.from('xy'), Buffer.from('xxx'),
    Buffer.from('NetHack save and bones data\0'.repeat(20000)),
    Buffer.from(Array.from({ length: 300000 }, (_, i) => i & 255)),
    Buffer.concat([Buffer.alloc(400000, 65), noise, Buffer.alloc(400000, 66)]),
    noise.subarray(0, 30000), noise,
    ...[255, 256, 257, 1023, 1024, 1025, 2048, 4096, 8192, 65536].map(n => noise.subarray(0, n)),
];
let clearCount = 0;
const widths = new Set();
for (const [index, original] of fixtures.entries()) {
    const js = compressUnixZ(original), c = reference(original);
    assert.equal(js.status, c.status, `Encode status fixture ${index}`);
    equal(js.bytes, c.bytes, `Byte-exact pinned ncompress encoding fixture ${index}`);
    assert.equal(js.status, js.bytes.length >= original.length ? 2 : 0);
    const stats = inspectCodes(js.bytes);
    clearCount += stats.clears;
    for (const width of stats.widths) widths.add(width);
    if (original.length > 0) {
        const unpacked = decompressUnixZ(js.bytes);
        assert.equal(unpacked.status, 0, `JS round-trip fixture ${index}: ${unpacked.error}`);
        equal(unpacked.bytes, original, `JS round-trip fixture ${index}`);
    } else {
        assert.equal(decompressUnixZ(js.bytes).status, 1, 'Match service rejection of header-only empty .Z');
    }
    // Both directions with the OS implementation; compressed byte identity is
    // required against pinned ncompress above, not against another encoder.
    const jsFile = path.join(work, `js-${index}.Z`);
    fs.writeFileSync(jsFile, js.bytes);
    command('/usr/bin/uncompress', ['-f', jsFile]);
    equal(fs.readFileSync(jsFile.slice(0, -2)), original, `OS decode fixture ${index}`);
    if (original.length > 0) {
        for (let bits = 9; bits <= 16; ++bits) {
            const nativeFile = path.join(work, 'native');
            fs.writeFileSync(nativeFile, original);
            command('/usr/bin/compress', ['-f', '-b', String(bits), nativeFile]);
            const native = fs.readFileSync(nativeFile + '.Z');
            const decoded = decompressUnixZ(native), cDecoded = reference(native, true);
            assert.equal(decoded.status, cDecoded.status, `Native ${bits}-bit status fixture ${index}: ${decoded.error}`);
            equal(decoded.bytes, original, `OS ${bits}-bit decode fixture ${index}`);
            equal(cDecoded.bytes, original, `Pinned ncompress ${bits}-bit decode fixture ${index}`);
        }
    }
}
assert.ok(clearCount > 0, 'Adaptive dictionary resets are exercised');
assert.deepEqual([...widths].sort((a, b) => a - b), [9, 10, 11, 12, 13, 14, 15, 16]);

// Constructed non-block 9-bit fixture; code 256 is an ordinary dictionary
// entry here, not CLEAR. Codes 65,66,256 decode to "ABAB".
const nonblock = Uint8Array.from([0x1f, 0x9d, 0x09, 65, 132, 0, 4]);
equal(decompressUnixZ(nonblock).bytes, Buffer.from('ABAB'), 'Non-block mode dictionary code 256');
equal(reference(nonblock, true).bytes, Buffer.from('ABAB'), 'Pinned non-block oracle');
const invalid = [[], [0x1f], [0x1f, 0x9d, 0x90], [0x1f, 0x9d, 0x90, 0],
    [0x1f, 0x9d, 0x91, 0, 0], [0x1f, 0x9d, 0x88, 0, 0],
    [0x1f, 0x9d, 0x90, 0xff, 0xff], [0x1f, 0x9d, 0x90, 65, 254, 3]];
for (const bytes of invalid) {
    const input = Uint8Array.from(bytes);
    assert.equal(reference(input, true).status, 1, 'Pinned oracle rejects selected malformed stream');
    assert.equal(decompressUnixZ(input).status, 1, 'JS rejects selected malformed stream');
    equal(decompressUnixZ(compressUnixZ(fixtures[4]).bytes).bytes, fixtures[4], 'Recovery after invalid stream');
}
assert.equal(compressUnixZ('x').status, 1);
assert.equal(decompressUnixZ(null).status, 1);
console.log(`PASS: ${comparisons} byte comparisons; byte-exact pinned ncompress encoding; native 9–16-bit decode; all widths and ${clearCount} CLEAR resets; binary/tiny/empty/no-shrink/error recovery.`);
