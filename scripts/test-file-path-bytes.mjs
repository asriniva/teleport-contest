import assert from 'node:assert/strict';
import {createStandaloneEnvironment} from '../js/nethack/environment.js';
import {O_CREAT, O_RDONLY, O_WRONLY, VFS_ERRNO} from '../js/c-runtime/vfs.js';

const env = createStandaloneEnvironment();
const io = env.enableStdio();
const utf8 = new TextEncoder();
const prefix = utf8.encode('/names/Ren');
const path = (...suffix) => env.memory.cstring(Uint8Array.from([...prefix, ...suffix]));
const replacement = '/names/Ren�';
env.filesystem.mkdir('/names');
env.filesystem.writeFile(replacement, 'original');
const bytes = env.filesystem.readFile(replacement).slice();

function fails(result, code) {
    assert.equal(result, -1);
    assert.equal(env.libc.errno, VFS_ERRNO[code]);
}

for (const invalid of [[0xc3], [0xf0, 0x9f, 0x8c], [0xed, 0xa0, 0x80], [0xff]]) {
    const bad = path(...invalid);
    fails(io.open(bad, O_RDONLY), 'ENOENT');
    fails(io.open(bad, O_WRONLY | O_CREAT), 'EILSEQ');
    fails(io.mkdir(bad, 0o700), 'EILSEQ');
    fails(io.unlink(bad), 'ENOENT');
    fails(io.rename(replacement, bad), 'EILSEQ');
    fails(io.open(path(...invalid, 0x2f, 0x61), O_WRONLY | O_CREAT), 'ENOENT');
}
assert.deepEqual(env.filesystem.readFile(replacement), bytes);
const fd = io.open(path(...utf8.encode('�')), O_RDONLY);
assert.ok(fd >= 0);
assert.equal(io.close(fd), 0);
