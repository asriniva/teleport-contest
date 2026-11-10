// Native .Z interoperability and repeated in-process wasm64 codec calls.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import { fileURLToPath, pathToFileURL } from 'node:url';
import { spawnSync } from 'node:child_process';

const root = fileURLToPath(new URL('../', import.meta.url));
const work = path.join(root, '.cache/compression-tests');
const sdk = process.env.EMSDK || path.join(root, '.cache/emsdk');
fs.mkdirSync(work, { recursive: true });
function command(executable, args, expected = [0]) {
    const result = spawnSync(executable, args, { encoding: 'utf8', timeout: 60000 });
    assert.ok(expected.includes(result.status), `${executable}: ${result.error || result.stderr || result.status}`);
    return result;
}
const service = path.join(root, 'nethack-c/wasm/compress-service.c');
const probe = path.join(root, 'scripts/compress-probe.c');
const wasm = path.join(work, 'codec.mjs');
command(path.join(sdk, 'upstream/emscripten/emcc'), ['-O2', '-std=gnu17', '-sMEMORY64=1',
    '-sMODULARIZE=1', '-sENVIRONMENT=node', '-sALLOW_MEMORY_GROWTH=1',
    '-sEXPORTED_FUNCTIONS=_codec_run', '-sEXPORTED_RUNTIME_METHODS=FS', '--no-entry',
    service, probe, '-o', wasm]);
const createCodec = (await import(pathToFileURL(wasm))).default;
const codec = await createCodec({ printErr: () => {} });
const remove = file => { try { codec.FS.unlink(file); } catch { /* absent */ } };
function encode(bytes) {
    remove('/plain.Z'); codec.FS.writeFile('/plain', bytes);
    const status = codec._codec_run(0);
    return { status, bytes: codec.FS.readFile('/plain.Z') };
}
function decode(bytes) {
    remove('/plain'); codec.FS.writeFile('/plain.Z', bytes);
    const status = codec._codec_run(1);
    return { status, bytes: codec.FS.readFile('/plain') };
}
let random = 0x12345678;
const noise = Buffer.from(Array.from({ length: 600000 }, () => {
    random ^= random << 13; random ^= random >>> 17; random ^= random << 5;
    return random & 255;
}));
const fixtures = [
    Buffer.from('NetHack save and bones data\0'.repeat(20000)),
    Buffer.from(Array.from({ length: 300000 }, (_, i) => i & 255)),
    Buffer.concat([Buffer.alloc(400000, 65), noise, Buffer.alloc(400000, 66)]),
    noise.subarray(0, 30000),
];
for (const [index, original] of fixtures.entries()) {
    const packed = encode(original);
    assert.equal(packed.status, packed.bytes.length >= original.length ? 2 : 0);
    assert.deepEqual(Array.from(packed.bytes.subarray(0, 3)), [0x1f, 0x9d, 0x90]);
    const nativePath = path.join(work, `wasm-${index}.Z`);
    fs.writeFileSync(nativePath, packed.bytes);
    command('/usr/bin/uncompress', ['-f', nativePath]);
    assert.deepEqual(fs.readFileSync(nativePath.slice(0, -2)), original, 'Native must decode Wasm output');
    for (const bits of [9, 12, 16]) {
        const input = path.join(work, `native-${index}-${bits}`);
        fs.writeFileSync(input, original);
        command('/usr/bin/compress', ['-f', '-b', String(bits), input]);
        const nativePacked = fs.readFileSync(input + '.Z');
        const unpacked = decode(nativePacked);
        assert.equal(unpacked.status, 0);
        assert.deepEqual(Buffer.from(unpacked.bytes), original, `Decode native ${bits}-bit stream`);
    }
    const roundTrip = decode(encode(original).bytes);
    assert.equal(roundTrip.status, 0);
    assert.deepEqual(Buffer.from(roundTrip.bytes), original);
}
for (const bytes of [Buffer.alloc(0), Buffer.from('x'), noise.subarray(0, 200)]) {
    const file = path.join(work, 'no-shrink');
    fs.writeFileSync(file, bytes); fs.rmSync(file + '.Z', { force: true });
    const nativeStatus = command('/usr/bin/compress', [file], [0, 2]).status;
    assert.equal(encode(bytes).status, nativeStatus, 'Non-shrinking status agrees with native');
}
for (const invalid of [[], [0x1f], [0x1f, 0x9d, 0x90],
    [0x1f, 0x9d, 0x91, 0, 0], [0x1f, 0x9d, 0x88, 0, 0], [0x1f, 0x9d, 0x90, 0xff, 0xff]]) {
    assert.notEqual(decode(Uint8Array.from(invalid)).status, 0, 'Malformed input must fail locally');
}
remove('/plain'); assert.notEqual(codec._codec_run(0), 0, 'Missing input reports failure');
remove('/plain.Z'); codec.FS.mkdir('/plain.Z'); codec.FS.writeFile('/plain', fixtures[0]);
assert.notEqual(codec._codec_run(0), 0, 'Unwritable output reports failure');
codec.FS.rmdir('/plain.Z');
assert.equal(decode(encode(fixtures[0]).bytes).status, 0, 'Codec recovers after errors without terminating the module');
console.log('PASS: wasm64 .Z/native interoperability at 9/12/16 bits, binary/dictionary-reset data, repeated calls, no-shrink status, malformed streams and I/O failure recovery.');
