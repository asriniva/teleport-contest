import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import { fileURLToPath, pathToFileURL } from 'node:url';
import { spawnSync } from 'node:child_process';
import vm from 'node:vm';
import { CVFS, VFSError, VFS_ERRNO, O_RDONLY, O_WRONLY, O_RDWR, O_CREAT, O_EXCL,
  O_TRUNC, O_APPEND, O_DIRECTORY } from '../js/services/c-vfs.js';

const root = fileURLToPath(new URL('../', import.meta.url));
const work = path.join(root, '.cache/js-dependency-vfs');
fs.mkdirSync(work, { recursive: true });
const nativeRoot = path.join(work, 'native-root');
fs.rmSync(nativeRoot, { recursive: true, force: true }); fs.mkdirSync(nativeRoot);
function command(executable, args, options = {}) {
  const result = spawnSync(executable, args, { encoding: 'utf8', timeout: 60000, maxBuffer: 16 * 1024 * 1024, ...options });
  assert.equal(result.status, 0, `${executable}: ${result.error || result.stderr || result.status}`);
  return result.stdout;
}
const compiler = process.env.CC || path.join(root, '.cache/wasm64-build/host-cc');
const source = path.join(root, 'scripts/test-js-vfs.c'), native = path.join(work, 'native-vfs');
command(compiler, ['-O2', '-std=gnu17', source, '-o', native]);
const bytes = text => Uint8Array.from(Buffer.from(text, 'hex'));
const commands = [
  'MK save', 'MK bones', 'MK save', 'MK missing/child', 'OPEN missing 0',
  'OPEN save/a 578', 'WRITE 3 h4100ff8042 -', 'SEEK 3 0 0', 'READ 3 9 -', 'FSTAT 3',
  'READ 3 9 -', 'WRITE 3 h5a 2', 'SEEK 3 0 1', 'SEEK 3 -1 2', 'READ 3 9 -',
  'SEEK 3 10 0', 'WRITE 3 h58 -', 'STAT save/a', 'SEEK 3 0 0', 'READ 3 20 -',
  'OPEN save/a 0', 'SAME 3 4', 'WRITE 4 h58 -', 'READ 99 1 -', 'SEEK 3 -1 0',
  'SEEK 3 0 3', 'OPEN save/a 193', 'OPEN save 1', 'OPEN save/a 65536',
  'CLOSE 4', 'OPEN save 0', 'READ 4 1 -', 'CLOSE 4', 'UNLINK save',
  'OPEN save/write-only 577', 'READ 4 1 -', 'CLOSE 4', 'UNLINK save/write-only',
  'UNLINK save/a', 'STAT save/a', 'FSTAT 3', 'SEEK 3 0 0', 'READ 3 20 -',
  'OPEN save/a 578', 'SAME 3 4', 'WRITE 4 h6e6577 -', 'READ 3 20 0',
  'RENAME save/a bones/payload', 'STAT save/a', 'STAT bones/payload',
  'OPEN bones/destination 578', 'WRITE 5 h6f6c64 -', 'RENAME bones/payload bones/destination',
  'SAME 4 5', 'SEEK 5 0 0', 'READ 5 10 -', 'OPEN bones/destination 0',
  'SAME 4 6', 'READ 6 10 -', 'CLOSE 6', 'CLOSE 5', 'CLOSE 4', 'CLOSE 3',
  'OPEN bones/destination 1089', 'WRITE 3 h21 -', 'SEEK 3 0 0', 'WRITE 3 h3f -',
  'CLOSE 3', 'OPEN bones/destination 0', 'READ 3 20 -', 'CLOSE 3',
  'OPEN bones/destination 577', 'CLOSE 3', 'STAT bones/destination',
  'MK empty', 'MK empty/sub', 'RMDIR empty', 'RENAME empty/sub save/sub', 'RMDIR empty',
  'MK dest', 'RENAME save/sub dest', 'STAT dest', 'RENAME dest bones/destination',
  'RENAME bones/destination dest', 'UNLINK bones/destination', 'RMDIR dest',
  'LS .', 'LS save', 'LS bones/destination', 'CD save', 'PWD', 'MK inner', 'CD ./inner/..',
  'PWD', 'CD ..', 'PWD', 'STAT ./save//inner/../.', 'STAT missing/../save',
  'RENAME save save/inner/child', 'CD bones/destination', 'RMDIR no-such-file',
];
let seed = 0xa1726d41;
const random = n => { seed ^= seed << 13; seed ^= seed >>> 17; seed ^= seed << 5; return (seed >>> 0) % n; };
for (let i = 0; i < 400; ++i) {
  const file = 'f' + random(10), fd = 3 + random(8);
  switch (random(10)) {
    case 0: commands.push(`OPEN ${file} ${[0, 1, 2, 577, 578, 1089, 193][random(7)]}`); break;
    case 1: commands.push(`WRITE ${fd} h${Buffer.from(Array.from({ length: random(20) }, () => random(256))).toString('hex')} -`); break;
    case 2: commands.push(`READ ${fd} ${random(20)} -`); break;
    case 3: commands.push(`SEEK ${fd} ${random(30) - 3} ${random(4)}`); break;
    case 4: commands.push(`CLOSE ${fd}`); break;
    case 5: commands.push(`UNLINK ${file}`); break;
    case 6: commands.push(`RENAME ${file} f${random(10)}`); break;
    case 7: commands.push(`STAT ${file}`); break;
    case 8: commands.push(`FSTAT ${fd}`); break;
    default: commands.push('LS .');
  }
}
function execute(api, line) {
  const [op, a, b, c] = line.split(' ');
  try {
    let result = 0;
    switch (op) {
      case 'MK': api.mkdir(a); break;
      case 'OPEN': result = api.open(a, Number(b)); break;
      case 'CLOSE': api.close(Number(a)); break;
      case 'UNLINK': api.unlink(a); break;
      case 'RENAME': api.rename(a, b); break;
      case 'RMDIR': api.rmdir(a); break;
      case 'CD': api.chdir(a); break;
      case 'PWD': return 'OK ' + api.cwd();
      case 'SEEK': result = api.lseek(Number(a), Number(b), Number(c)); break;
      case 'READ': {
        const data = new Uint8Array(Number(b));
        const count = api.read(Number(a), data, 0, data.length, c === '-' ? undefined : Number(c));
        return `OK ${count} ${Buffer.from(data.subarray(0, count)).toString('hex')}`;
      }
      case 'WRITE': {
        const data = bytes(b.slice(1));
        result = api.write(Number(a), data, 0, data.length, c === '-' ? undefined : Number(c)); break;
      }
      case 'STAT': case 'FSTAT': {
        const st = op === 'STAT' ? api.stat(a) : api.fstat(Number(a));
        return `OK ${api.isDir(st.mode) ? 'dir' : 'file'} ${st.size}`;
      }
      case 'SAME': return 'OK ' + Number(api.fstat(Number(a)).ino === api.fstat(Number(b)).ino);
      case 'LS': return 'OK ' + api.readdir(a).sort().join(',');
      default: throw Error('Unknown test operation');
    }
    return 'OK ' + result;
  } catch (error) { if (error instanceof VFSError) return 'ERR ' + error.code; throw error; }
}
const core = new CVFS();
const expected = commands.map(line => execute(core, line));
const actual = command(native, [nativeRoot], { input: commands.join('\n') + '\n' }).split('\n').slice(0, -1);
assert.equal(actual.length, expected.length);
let nativeHostDifferences = 0;
for (let i = 0; i < actual.length; ++i) {
  // macOS returns EPERM for unlink(directory); Linux and the configured MEMFS
  // return EISDIR. Preserve the target behavior, and assert both sides rather
  // than silently treating these symbolic errors as universally equivalent.
  if (process.platform === 'darwin' && commands[i] === 'UNLINK save') {
    assert.equal(actual[i], 'ERR EPERM'); assert.equal(expected[i], 'ERR EISDIR'); ++nativeHostDifferences;
  } else assert.equal(expected[i], actual[i], `native ${i}: ${commands[i]}`);
}

// Build a separate wasm32 MEMFS oracle for Node22; no current game module or
// generated TU probes are modified. Files are exclusively under this scratch.
const sdk = path.join(root, '.cache/emsdk'), memfsModule = path.join(work, 'memfs-oracle.mjs');
command(path.join(sdk, 'upstream/emscripten/emcc'), ['-O1', source,
  '-sMODULARIZE=1', '-sEXPORT_ES6=1', '-sINVOKE_RUN=0', '-sFORCE_FILESYSTEM=1',
  '-sEXPORTED_RUNTIME_METHODS=FS', '-sENVIRONMENT=node', '-o', memfsModule],
{ env: { ...process.env, EM_CONFIG: path.join(sdk, '.emscripten') } });
const { default: factory } = await import(pathToFileURL(memfsModule));
const { FS } = await factory(); FS.mkdir('/review'); FS.chdir('/review');
const targetStreams = new Map();
const target = {
  mkdir: p => FS.mkdir(p), open(p, flags) { const stream = FS.open(p, flags); targetStreams.set(stream.fd, stream); return stream.fd; },
  close(fd) { const stream = targetStreams.get(fd); if (!stream) throw new FS.ErrnoError(8); FS.close(stream); targetStreams.delete(fd); },
  read(fd, ...args) { const stream = targetStreams.get(fd); if (!stream) throw new FS.ErrnoError(8); return FS.read(stream, ...args); },
  write(fd, ...args) { const stream = targetStreams.get(fd); if (!stream) throw new FS.ErrnoError(8); return FS.write(stream, ...args); },
  lseek(fd, ...args) { const stream = targetStreams.get(fd); if (!stream) throw new FS.ErrnoError(8); return FS.llseek(stream, ...args); },
  fstat: fd => FS.fstat(fd), stat: p => FS.stat(p), isDir: mode => FS.isDir(mode),
  readdir: p => FS.readdir(p), unlink: p => FS.unlink(p), rename: (a, b) => FS.rename(a, b),
  rmdir: p => FS.rmdir(p), chdir: p => FS.chdir(p), cwd: () => FS.cwd().slice('/review'.length) || '/',
};
const namesByErrno = new Map(Object.entries(VFS_ERRNO).map(([name, number]) => [number, name]));
const invokeTarget = line => {
  try { return execute(target, line); }
  catch (error) { if (Number.isInteger(error.errno)) return 'ERR ' + (namesByErrno.get(error.errno) || error.errno); throw error; }
};
for (let i = 0; i < commands.length; ++i)
  assert.equal(expected[i], invokeTarget(commands[i]), `MEMFS ${i}: ${commands[i]}`);

let boundaryComparisons = 0;
const boundary = [
  f => f.mkdir('.'), f => f.mkdir('a/.'), f => f.mkdir('a/..'),
  f => f.rmdir('a/.'), f => f.rmdir('a/..'), f => f.rmdir('.'), f => f.unlink('a/.'),
  f => f.rename('a/file', 'a'), f => f.rename('a', 'a/child'),
  f => f.mkdirTree('file'), f => f.mkdirTree('file/child'), f => f.mkdirTree('file/../newdir'),
  f => { f.mkdir('private', 0); f.writeFile('private/file', Uint8Array.of(1)); },
  f => { f.mkdir('private', 0); f.chdir('private'); },
  f => { f.writeFile('readonly', Uint8Array.of(1), { mode: 0o444 }); f.open('readonly', 'w'); },
  f => { f.writeFile('writeonly', Uint8Array.of(1), { mode: 0o222 }); f.open('writeonly', 'r'); },
  f => { f.writeFile('none', Uint8Array.of(1), { mode: 0 }); f.readFile('none'); },
  f => { const stream = f.open('none', 'w', 0); f.write(stream, Uint8Array.of(1), 0, 1); f.close(stream); },
  f => { f.mkdir('readonly', 0o555); f.mkdir('readonly/child'); },
  f => { f.writeFile('none', Uint8Array.of(1), { mode: 0 }); f.open('none', O_CREAT | O_EXCL | O_WRONLY); },
  f => { f.writeFile('unicode', 'é\0after'); assert.equal(f.readFile('unicode', { encoding: 'utf8' }), 'é'); },
  f => { f.writeFile('append', Uint8Array.of(1, 2)); const stream = f.open('append', 'a+');
    f.write(stream, Uint8Array.of(3), 0, 1, 0); assert.equal(stream.position, 2);
    assert.deepEqual(f.readFile('append'), Uint8Array.of(3, 2)); f.close(stream); },
];
const outcome = callback => {
  try { callback(); return 'OK'; }
  catch (error) { if (Number.isInteger(error.errno)) return 'ERR ' + namesByErrno.get(error.errno); throw error; }
};
for (let i = 0; i < boundary.length; ++i) {
  const isolated = new CVFS(); const directory = '/edge-' + i;
  FS.mkdir(directory); FS.chdir(directory);
  for (const f of [isolated.FS, FS]) {
    f.mkdir('a'); f.mkdir('b'); f.writeFile('file', Uint8Array.of(1)); f.writeFile('a/file', Uint8Array.of(2));
  }
  assert.equal(outcome(() => boundary[i](isolated.FS)), outcome(() => boundary[i](FS)), `MEMFS boundary ${i}`);
  ++boundaryComparisons;
}

// Helpers/facade, copy ownership, positional append quirks, normalization and
// save/bones persistence exercise boundaries outside the native trace protocol.
let time = 1000;
const vfs = new CVFS({ clock: () => time++ });
vfs.mkdirTree('/nethack/save'); vfs.mkdirTree('/nethack/bones'); vfs.chdir('/nethack');
const payload = Uint8Array.from({ length: 4097 }, (_, i) => i & 255);
vfs.writeFile('save/player.Z', payload); payload.fill(7);
const original = vfs.readFile('./save//../save/player.Z');
assert.equal(original[0], 0); assert.equal(original[255], 255);
original.fill(9); assert.equal(vfs.readFile('save/player.Z')[0], 0);
vfs.writeFile('bones/bones.01', Uint8Array.from([0, 255, 128, 10]));
vfs.writeFile('notes', 'é\0after');
assert.deepEqual(vfs.readFile('notes'), Uint8Array.from([195, 169, 0, 97, 102, 116, 101, 114]));
assert.equal(vfs.readFile('notes', { encoding: 'utf8' }), 'é');
const stream = vfs.FS.open('save/player.Z', 'r');
const read = new Uint8Array(4); assert.equal(vfs.FS.read(stream, read, 0, 4), 4);
assert.equal(stream.position, 4); assert.equal(vfs.FS.fstat(stream.fd).size, 4097);
vfs.FS.close(stream); assert.equal(stream.fd, null);
assert.throws(() => vfs.FS.close(stream), error => error.errno === VFS_ERRNO.EBADF);
assert.equal(new vfs.FS.ErrnoError(44).code, 'ENOENT');
const primitiveFd = vfs.open('notes'), stale = vfs.FS.getStream(primitiveFd);
vfs.close(primitiveFd); const reusedFd = vfs.open('notes'); assert.equal(reusedFd, primitiveFd);
assert.throws(() => vfs.FS.read(stale, read, 0, 1), error => error.code === 'EBADF');
assert.throws(() => stale.position, error => error.code === 'EBADF');
const wrapped = vfs.FS.getStream(reusedFd); assert.notEqual(wrapped, stale); vfs.FS.close(wrapped);
const appender = vfs.FS.open('notes', 'a+');
vfs.FS.write(appender, Uint8Array.of(88), 0, 1, 0);
assert.equal(appender.position, 8); assert.equal(vfs.readFile('notes')[0], 88); vfs.FS.close(appender);

const snapshot = vfs.exportSnapshot(), restored = new CVFS(); restored.importSnapshot(snapshot);
assert.deepEqual(restored.exportSnapshot(), snapshot);
const backing = new Map(), storage = { getItem: key => backing.get(key) ?? null, setItem: (key, value) => backing.set(key, String(value)) };
vfs.saveToStorage(storage, 'test');
const segment = new CVFS({ storage, persistenceKey: 'test' }); assert.equal(segment.loadFromStorage(), true);
segment.unlink('/nethack/save/player.Z'); segment.writeFile('/nethack/bones/bones.02', Uint8Array.of(0, 128, 255)); segment.saveToStorage();
const next = new CVFS({ storage, persistenceKey: 'test' }); next.loadFromStorage();
assert.throws(() => next.stat('/nethack/save/player.Z'), error => error.code === 'ENOENT');
assert.deepEqual(next.readFile('/nethack/bones/bones.01'), Uint8Array.of(0, 255, 128, 10));
assert.deepEqual(next.readFile('/nethack/bones/bones.02'), Uint8Array.of(0, 128, 255));
assert.equal(new CVFS().loadFromStorage(storage, 'absent'), false);
assert.throws(() => next.saveToStorage({ setItem() { throw Object.assign(Error('full'), { name: 'QuotaExceededError' }); } }), error => error.code === 'ENOSPC');
assert.throws(() => next.loadFromStorage({ getItem() { throw Error('denied'); } }), error => error.code === 'EIO');
assert.throws(() => next.loadFromStorage({ getItem: () => 'bad json' }), error => error.code === 'EINVAL');
const before = next.exportSnapshot();
for (const invalid of [{}, { ...before, version: 2 }, { ...before, entries: [...before.entries, before.entries[0]] },
  { ...before, entries: [...before.entries, { path: '/escape/../x', type: 'file', mode: 438, atime: 0, mtime: 0, ctime: 0, base64: '' }] }]) {
  assert.throws(() => next.importSnapshot(invalid), VFSError); assert.deepEqual(next.exportSnapshot(), before);
}
const live = next.open('/nethack/bones/bones.01');
assert.throws(() => next.importSnapshot(before), error => error.code === 'EBUSY'); next.close(live);
const small = new CVFS({ maximumDescriptors: 1, maximumFileBytes: 4 });
const fd = small.open('/file', 'w+');
assert.throws(() => small.open('/file', 'r'), error => error.code === 'EMFILE');
small.write(fd, Uint8Array.of(1, 2, 3, 4));
assert.throws(() => small.write(fd, Uint8Array.of(5)), error => error.code === 'EFBIG');
small.lseek(fd, 100); assert.equal(small.write(fd, new Uint8Array(0)), 0);
small.close(fd); assert.deepEqual(small.readFile('/file'), Uint8Array.of(1, 2, 3, 4));
for (const operation of [() => small.open('/file', 4096), () => small.symlink('a', 'b'), () => small.chmod('/file', 0)])
  assert.throws(operation, error => error.code === 'ENOTSUP');
assert.equal(new CVFS().readdir('/').join(','), '.,..');
const large = new CVFS();
const savePayload = Uint8Array.from({ length: 1024 * 1024 }, (_, i) => i & 255);
large.writeFile('/save.Z', savePayload); large.saveToStorage(storage, 'large');
const largeRestored = new CVFS(); largeRestored.loadFromStorage(storage, 'large');
assert.deepEqual(largeRestored.readFile('/save.Z'), savePayload);
const unlinked = large.open('/save.Z'); large.unlink('/save.Z');
assert.equal(large.fstat(unlinked).size, savePayload.length);
assert.equal(large.exportSnapshot().entries.some(entry => entry.path === '/save.Z'), false);
large.close(unlinked);

const production = fs.readFileSync(path.join(root, 'js/services/c-vfs.js'), 'utf8');
const context = vm.createContext({ Uint8Array, TextEncoder, TextDecoder,
  WebAssembly: undefined, process: undefined, fetch: undefined, require: undefined, Buffer: undefined });
vm.runInContext(production.replace(/\bexport\s+/g, '') + `
  const isolated = new CVFS(); isolated.mkdirTree('/save');
  isolated.writeFile('/save/game', new Uint8Array([0,255,128]));
  if (isolated.readFile('/save/game')[1] !== 255) throw Error('host-free VFS failure');
`, context);
fs.writeFileSync(path.join(work, 'results.json'), JSON.stringify({ nativeComparisons: commands.length, nativeHostDifferences,
  memfsComparisons: commands.length, boundaryComparisons, seed: '0xa1726d41', scope: ['regular files', 'directories', 'numeric descriptors', 'MEMFS mode-bit checks', 'MEMFS facade', 'explicit snapshots/storage'],
  unsupported: ['chmod/chown/ACLs/user identities', 'symlinks', 'devices', 'sockets', 'locks', 'mounts', 'descriptor duplication'] }, null, 2) + '\n');
console.log(`PASS: ${commands.length} native named-errno and ${commands.length + boundaryComparisons} configured MEMFS comparisons; binary/hole/append/truncate/open-unlink/rename/fd behavior; mode bits, facade, 1MB snapshot persistence, deletion/bones, limits and host-free execution.`);
