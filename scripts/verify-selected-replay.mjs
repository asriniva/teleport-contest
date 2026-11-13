// Strict postprocessing for complete selected sessions; never runs the game.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import {pathToFileURL} from 'node:url';
import {compareAnimationCursors} from './score-standalone.mjs';

const [sourceArgument, runArgument] = process.argv.slice(2);
assert.ok(sourceArgument && runArgument, 'Usage: node verify-selected-replay.mjs SOURCE RUN');
const source = path.resolve(sourceArgument), run = path.resolve(runArgument);
const load = file => JSON.parse(fs.readFileSync(path.join(run, file)));
const before = load('pre-run-manifest.json'), after = load('post-run-integrity.json');
assert.equal(after.exitCode, 0);
assert.deepEqual(after.changed, []);
assert.ok(before.normalEntry && !before.jsMainOverlay && !before.assetOverride && !before.layoutOverride);
const text = fs.readFileSync(path.join(run, 'results.stdout.log'), 'utf8');
assert.ok(text.includes('__RESULTS_JSON__'));
const bundle = JSON.parse(text.slice(text.lastIndexOf('__RESULTS_JSON__') + '__RESULTS_JSON__'.length));
assert.deepEqual(bundle.results.map(row => row.session).sort(), [...before.selectedSessions].sort());
const {normalizeSession} = await import(pathToFileURL(path.join(source, 'frozen/session_loader.mjs')));
const telemetry = fs.readdirSync(path.join(run, 'stats')).filter(file => file.endsWith('.json'))
    .map(file => JSON.parse(fs.readFileSync(path.join(run, 'stats', file))));
let segments = 0, animations = 0;
for (const result of bundle.results) {
    assert.equal(result.passed, true, result.session + ': ' + result.error);
    for (const metric of ['rngCalls', 'screens', 'cursors', 'animFrames'])
        assert.equal(result.metrics[metric].matched, result.metrics[metric].total, result.session + ': ' + metric);
    const expected = normalizeSession(JSON.parse(fs.readFileSync(path.join(source, 'sessions', result.session)))).segments;
    const actual = telemetry.filter(row => row.session === result.session).sort((a, b) => a.segment - b.segment);
    assert.equal(actual.length, expected.length);
    for (let i = 0; i < expected.length; i++) {
        const segment = expected[i], observed = actual[i], steps = segment.steps;
        const frameCounts = steps.map(step => (step.animation_frames ?? []).length);
        const cursorCoverage = compareAnimationCursors(steps.map(step => (step.animation_frames ?? []).map(frame => frame.cursor)), observed.animationCursors);
        assert.equal(cursorCoverage.status, 'matched');
        const counts = {segment: i, inputKeys: segment.moves.length, consumedKeys: segment.moves.length,
            rngCalls: steps.reduce((n, step) => n + (step.rng ?? []).filter(value => typeof value === 'string' && /^(?:rn2|rnd|rn1|rnl|rne|rnz|d)\(/.test(value)).length, 0),
            screens: steps.filter(step => step.screen).length, cursors: steps.filter(step => step.screen).length,
            animationSteps: steps.length, animationTotal: frameCounts.reduce((a, b) => a + b, 0),
            pendingAnimationFrames: 0, forbiddenAttempts: 0};
        for (const [key, value] of Object.entries(counts)) assert.equal(observed[key], value, result.session + ': ' + key);
        assert.deepEqual(observed.animationFrames, frameCounts);
        assert.ok(observed.storage?.get > 0 && observed.storage?.set > 0);
        assert.ok(!observed.error);
        animations += cursorCoverage.matched;
        segments++;
    }
}
assert.equal(telemetry.length, segments);
const summary = {complete: true, strictAllMetricsPassed: bundle.results.length,
    segments, animationCursorTriplesMatched: animations, timings: bundle.results.map(row => ({session: row.session, ...row.time}))};
fs.writeFileSync(path.join(run, 'selected-summary.json'), JSON.stringify(summary, null, 2) + '\n');
console.log(JSON.stringify(summary));
