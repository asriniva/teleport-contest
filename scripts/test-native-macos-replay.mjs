// Replay fresh outputs of scripts/record-session.mjs from a native macOS C build.
// Use the same clock, timezone, and HOME in both runs for environment-sensitive cases.
import assert from 'node:assert/strict';
import {readFileSync} from 'node:fs';
import {basename} from 'node:path';
import {runSegment} from '../js/standalone-recorder-adapter.js';

const rngCall = /^(?:rn2|rnd|rn1|rnl|rne|rnz|d)\(/;

function compare(actual, expected, label) {
    assert.equal(actual.length, expected.length, label + ' count');
    for (let index = 0; index < expected.length; index++) {
        assert.deepEqual(actual[index], expected[index], label + ' at ' + index);
    }
}

const files = process.argv.slice(2);
assert.ok(files.length, 'Pass one or more .session.json files captured by the native C recorder');
for (const path of files) {
    const {version, segments} = JSON.parse(readFileSync(path, 'utf8'));
    assert.equal(version, 5, path);
    assert.ok(segments.length > 0, path + ' has no recorded segments');
    const data = new Map();
    const storage = {
        getItem: key => data.get(key) ?? null,
        setItem: (key, value) => data.set(key, String(value)),
        removeItem: key => data.delete(key),
        get length() { return data.size; },
        key: index => [...data.keys()][index] ?? null,
    };
    for (const [index, segment] of segments.entries()) {
        const label = basename(path) + ' segment ' + (index + 1);
        assert.ok(segment.steps.length > 0, label + ' has no native input boundaries');
        const game = await runSegment({...segment, storage}, {preservePublishedSaveCursor: false});
        const nativeRng = segment.steps.flatMap(step => step.rng ?? []).filter(call => rngCall.test(call));
        const jsRng = game.getRngLog().filter(call => rngCall.test(call));
        const value = call => call.replace(/\s*@\s.*$/, '').trim();
        compare(jsRng.map(value), nativeRng.map(value), label + ' ordered RNG');
        compare(game.getScreens(), segment.steps.map(step => step.screen), label + ' screens');
        compare(game.getCursors(), segment.steps.map(step => step.cursor), label + ' cursors');
        compare(game.getAnimationFramesByStep(), segment.steps.map(step => step.animation_frames ?? []), label + ' animations');
    }
    console.log('PASS: ' + basename(path));
}
