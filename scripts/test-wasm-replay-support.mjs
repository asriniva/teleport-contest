import assert from 'node:assert/strict';
import { decodeScreen } from '../frozen/screen-decode.mjs';
import { encodeRecorderScreen, shouldPersistGameFile, recordingClockEpoch } from '../js/wasm-replay-support.js';
import { recordingProfile, profileSysconf } from '../js/recording-profile.js';

const encoded = encodeRecorderScreen('\x1b[7mName          Level\x1b[27m\n\n');
const grid = decodeScreen(encoded);
assert.equal(grid[0][0].attr, 1, 'Heading letters retain inverse video');
assert.equal(grid[0][4].attr, 0, 'Recorder cursor-forward skips leave plain cells');
assert.equal(grid[0][14].ch, 'L');
assert.equal(grid[0][14].attr, 1);
assert.equal(encodeRecorderScreen('a    b\n\n'), 'a    b', 'Short spaces stay literal');
assert.equal(encodeRecorderScreen('a     b\n\n'), 'a\x1b[5Cb');
for (const path of ['/nethack/bonD0.3', '/nethack/bonM0.1', '/nethack/bonD0.3.gz', '/nethack/save/0Player']) {
    assert.ok(shouldPersistGameFile(path), `Keep persistent game state ${path}`);
}
for (const path of ['/nethack/0Player.0', '/nethack/0Player.3']) {
    assert.ok(!shouldPersistGameFile(path), `Discard transient process file ${path}`);
}
const previous = process.env.TELEPORT_RECORDING_EPOCH;
try {
    process.env.TELEPORT_RECORDING_EPOCH = '1768478400';
    assert.equal(recordingClockEpoch(), '1768478400');
    process.env.TELEPORT_RECORDING_EPOCH = 'not-a-timestamp';
    assert.throws(recordingClockEpoch, /valid Unix seconds/);
} finally {
    if (previous === undefined) delete process.env.TELEPORT_RECORDING_EPOCH;
    else process.env.TELEPORT_RECORDING_EPOCH = previous;
}
console.log('PASS: recorder encoding keeps heading styles while skipping long spaces; bones retained and temporary files discarded; recording clock validated.');
const originalHome = process.env.TELEPORT_RECORDING_HOME;
try {
    process.env.TELEPORT_RECORDING_HOME = '/test-profile/';
    assert.equal(recordingProfile().home, '/test-profile');
    for (const invalid of ['relative', '////', '/test/../elsewhere', '/test\nWIZARDS=*']) {
        process.env.TELEPORT_RECORDING_HOME = invalid;
        assert.throws(recordingProfile, /Recording HOME|Invalid recording profile/);
    }
} finally {
    if (originalHome === undefined) delete process.env.TELEPORT_RECORDING_HOME;
    else process.env.TELEPORT_RECORDING_HOME = originalHome;
}
const configured = profileSysconf('WIZARDS=root games\nSUPPORT=old\nEXPLORERS=*', { wizards: '*', support: '' });
assert.ok(configured.includes('WIZARDS=*'));
assert.ok(configured.includes('EXPLORERS=*'));
assert.ok(!configured.includes('SUPPORT='), 'No-support profile omits the setting entirely');
console.log('PASS: configurable recording HOME/sysconf, unrelated settings retained, and invalid profile values rejected.');
