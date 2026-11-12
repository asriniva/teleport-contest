// Compare the extracted persistence protocol on independent JS and real MEMFS.
import assert from 'node:assert/strict';
import { pathToFileURL, fileURLToPath } from 'node:url';
import { createJsRuntime } from '../js/nethack/runtime.js';
import { filesUnder, encodeFileBytes, decodeFileBytes, captureGameFiles,
    restoreGameFiles } from '../js/services/game-files.js';

const oraclePath = fileURLToPath(new URL('../.cache/js-dependency-vfs/memfs-oracle.mjs', import.meta.url));
const factory = (await import(pathToFileURL(oraclePath))).default;
const { FS: memfs } = await factory();
const runtime = createJsRuntime();
const independent = runtime.FS;
const bytes = count => Uint8Array.from({ length: count }, (_, i) => (i * 197 + (i >>> 8)) & 255);
const sameFiles = (left, right) => {
    assert.deepEqual(Object.keys(left).sort(), Object.keys(right).sort());
    for (const name of Object.keys(left)) assert.deepEqual(left[name], right[name], name);
};
const persist = path => !path.endsWith('/transient') && !path.endsWith('/lock');
const states = [];
for (const FS of [independent, memfs]) {
    FS.mkdirTree('/nethack/save');
    FS.writeFile('/nethack/asset', bytes(100));
    FS.writeFile('/nethack/deleted', bytes(7));
    FS.writeFile('/nethack/changed', bytes(300));
    const baseline = filesUnder(FS, '/nethack');
    FS.unlink('/nethack/deleted');
    FS.writeFile('/nethack/changed', bytes(301));
    FS.writeFile('/nethack/save/player.Z', bytes(1024 * 1024));
    FS.writeFile('/nethack/bonD0.1', bytes(25000));
    FS.writeFile('/nethack/empty', new Uint8Array());
    FS.writeFile('/nethack/transient', bytes(9));
    FS.writeFile('/nethack/lock', bytes(11));
    const state = captureGameFiles(FS, baseline, persist);
    assert.deepEqual(state.deleted, ['/nethack/deleted']);
    assert.deepEqual(Object.keys(state.files).sort(), [
        '/nethack/bonD0.1', '/nethack/changed', '/nethack/empty', '/nethack/save/player.Z',
    ]);
    assert.throws(() => captureGameFiles(FS, baseline), TypeError);
    // Baselines must remain independent of later filesystem writes.
    assert.equal(baseline['/nethack/changed'].length, 300);
    states.push({ state, baseline });
}
assert.deepEqual(states[0].state, states[1].state);
for (const state of states) {
    for (const serialized of [state.state, JSON.stringify(state.state)]) {
        const destination = createJsRuntime().FS;
        destination.mkdirTree('/nethack');
        for (const [path, contents] of Object.entries(state.baseline)) destination.writeFile(path, contents);
        restoreGameFiles(destination, serialized);
        const expected = { ...state.baseline };
        delete expected['/nethack/deleted'];
        for (const [path, text] of Object.entries(state.state.files)) expected[path] = decodeFileBytes(text);
        sameFiles(filesUnder(destination, '/nethack'), expected);
        // Repeated restoration, including an already absent deletion, is stable.
        restoreGameFiles(destination, serialized);
        sameFiles(filesUnder(destination, '/nethack'), expected);
    }
}
for (const length of [0, 1, 2, 3, 8191, 8192, 8193, 16385, 1024 * 1024]) {
    const original = bytes(length);
    assert.equal(encodeFileBytes(original), Buffer.from(original).toString('base64'));
    assert.deepEqual(decodeFileBytes(encodeFileBytes(original)), original);
}
assert.deepEqual(runtime.FS.readFile('/nethack/asset'), bytes(100));
assert.throws(() => createJsRuntime().FS.stat('/nethack/asset'), error => error.code === 'ENOENT');
console.log('PASS: JS-owned filesystem and actual MEMFS produce identical save/bones payloads; 1 MB binary, deletion, transient filtering, base64 boundaries, restoration and instance isolation.');
