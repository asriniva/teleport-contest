// End-to-end checks for the process timezone, seasonal independence and
// macOS-visible behavior. Session answers never enter the engine input.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import { spawnSync } from 'node:child_process';
import { fileURLToPath } from 'node:url';
import { normalizeSession } from '../frozen/session_loader.mjs';
import { runSegment } from '../js/jsmain.js';
import { InMemoryStorage } from '../js/storage.js';
import { decodeScreen } from '../frozen/screen-decode.mjs';

const root = fileURLToPath(new URL('../', import.meta.url));
function inputFor(name, count) {
    const session = normalizeSession(JSON.parse(fs.readFileSync(new URL(`../sessions/${name}.session.json`, import.meta.url))));
    const { seed, datetime, nethackrc, moves } = session.segments[0];
    return { seed, datetime, nethackrc, moves: moves.slice(0, count), storage: new InMemoryStorage() };
}
const expectedShops = { 'America/New_York': 'Ermenak', 'America/Los_Angeles': 'Alaca', UTC: 'Akhalataki' };
function loadSession(name) {
    return normalizeSession(JSON.parse(fs.readFileSync(new URL(`../sessions/${name}.session.json`, import.meta.url))));
}
function segmentInput(segment, storage, count = segment.moves.length) {
    const { seed, datetime, nethackrc, moves } = segment;
    return { seed, datetime, nethackrc, moves: moves.slice(0, count), storage };
}

if (!process.argv.includes('--timezone-worker')) {
    const terminalSmoke = await runSegment(inputFor('seed8000-tourist-starter', 1));
    assert.equal(terminalSmoke.getTerminalDiagnostics().backend, 'shadow');
    assert.match(terminalSmoke.getScreens()[0], /\x0elqqqqqqk\x0f/,
        'Boundary screens must retain recorder shadow encoding without glyph conversion');

    for (const zone of Object.keys(expectedShops)) {
        const child = spawnSync(process.execPath, [fileURLToPath(import.meta.url), '--timezone-worker'], {
            cwd: root, env: { ...process.env, TZ: zone }, encoding: 'utf8', timeout: 30000,
        });
        assert.equal(child.status, 0, `${zone}: ${child.error || child.stderr || child.stdout}`);
        process.stdout.write(child.stdout);
    }
    {
        const segment = loadSession('seed0002-healer-reflection-drummer').segments[0];
        const menu = await runSegment(segmentInput(segment, new InMemoryStorage(), 585));
        assert.deepEqual(decodeScreen(menu.getScreens()[585]), decodeScreen(segment.steps[585].screen),
            'Actual spell heading must match the recording, including its skipped inverse spaces');
        const bones = loadSession('seed5006-tourist-stress-disaster');
        const storage = new InMemoryStorage();
        await runSegment(segmentInput(bones.segments[0], storage));
        const saved = JSON.parse(storage.getItem('vfs:/teleport-wasm64-state.json'));
        assert.ok(saved.files['/nethack/bonD0.3.Z'], 'Death segment must retain its successfully compressed bones file');
        assert.ok(!saved.files['/nethack/bonD0.3'], 'Successful compression removes the raw source');
        assert.ok(!Object.keys(saved.files).some(path => /^\/nethack\/\d[^/]*\.\d+$/.test(path)),
            'Transient level/lock files must stay excluded');
        const nextGame = await runSegment(segmentInput(bones.segments[1], storage, 5));
        assert.ok(nextGame.getScreens().some(screen => screen.includes('Get bones?')),
            'Next game must find the persisted bones instead of generating a fresh level');
        console.log('Recorded spell-heading cells and cross-segment bones restoration passed.');
    }
    const environment = loadSession('seed2200-wizard-quaff-zap-read').segments[0];
    const publicEnvironment = await runSegment(segmentInput(environment, new InMemoryStorage(), 216));
    assert.equal(publicEnvironment.getScreens()[158], environment.steps[158].screen,
        'Documented recording HOME must produce its natural help wrapping');
    assert.equal(publicEnvironment.getScreens()[216], environment.steps[216].screen,
        'Configured wildcard wizard list naturally omits named local contact text');
    const oldHome = process.env.TELEPORT_RECORDING_HOME;
    const oldWizards = process.env.TELEPORT_RECORDING_WIZARDS;
    const oldSupport = process.env.TELEPORT_RECORDING_SUPPORT;
    try {
        process.env.TELEPORT_RECORDING_HOME = '/profile-test';
        process.env.TELEPORT_RECORDING_WIZARDS = 'root games';
        process.env.TELEPORT_RECORDING_SUPPORT = 'ask the profile test operator';
        const custom = await runSegment(segmentInput(environment, new InMemoryStorage(), 216));
        assert.ok(custom.getScreens().some(screen => screen.includes('/profile-test/.nethackrc')),
            'Changing profile HOME changes actual config-file output');
        assert.ok(custom.getScreens().some(screen => screen.includes('To contact local support, ask the profile test operator')),
            'Support override is read by NetHack rather than filtered from snapshots');
    } finally {
        for (const [key, previous] of [['TELEPORT_RECORDING_HOME', oldHome],
            ['TELEPORT_RECORDING_WIZARDS', oldWizards], ['TELEPORT_RECORDING_SUPPORT', oldSupport]]) {
            if (previous === undefined) delete process.env[key]; else process.env[key] = previous;
        }
    }
    console.log('Recording-profile HOME wrapping, default contact text and independent overrides passed.');
    const apple = await runSegment(inputFor('seed0016-healer-newmoon-eat-zap', 7));
    assert.equal(apple.getScreens()[7].split('\n')[0], 'Delicious!  Must be a Macintosh!');
    const rogue = await runSegment(inputFor('seed0007-rogue-snake-swamp', 85));
    assert.match(rogue.getScreens()[32], /crash_email/);
    assert.match(rogue.getScreens()[84], /There is a jackal corpse here; eat it/);
    const version = await runSegment(inputFor('seed0106-priest-extcmd-sweep', 175));
    assert.match(version.getScreens()[175], /^MacOS NetHack/);
    assert.match(version.getScreens()[175], /mail\n\s*daemon/);
    console.log('macOS apple message, option layout, corpse prompt, version and mail features passed.');
} else {
    const NativeDate = globalThis.Date;
    let before;
    try {
        for (const now of ['2026-01-15T12:00:00Z', '2026-07-15T12:00:00Z']) {
            const fixedNow = NativeDate.parse(now);
            globalThis.Date = class extends NativeDate {
                constructor(...args) { super(...(args.length ? args : [fixedNow])); }
                static now() { return fixedNow; }
            };
            const game = await runSegment(inputFor('seed0002-healer-reflection-drummer', 340));
            const greeting = game.getScreens()[340].split('\n')[0];
            assert.match(greeting, new RegExp(`Welcome to ${expectedShops[process.env.TZ]}'s`));
            const actual = JSON.stringify([game.getScreens(), game.getRngLog()]);
            if (before) assert.equal(actual, before, `Replay depends on current season in ${process.env.TZ}`);
            before = actual;
            if (process.env.TZ === 'America/New_York') {
                const deaths = loadSession('seed0030-ten-diverse-deaths');
                for (const [segment, step, expected] of [[3, 277, 'Maganasipi'], [7, 149, 'Swidnica']]) {
                    const winter = await runSegment(segmentInput(deaths.segments[segment], new InMemoryStorage(), step));
                    assert.match(winter.getScreens()[step].split('\n')[0], new RegExp(`Welcome to ${expected}`),
                        'Winter replay must retain the historical recording-clock DST behavior');
                }
            }
        }
    } finally { globalThis.Date = NativeDate; }
    if (process.env.TZ === 'America/New_York') {
        const previousClock = process.env.TELEPORT_RECORDING_EPOCH;
        try {
            process.env.TELEPORT_RECORDING_EPOCH = String(NativeDate.parse('2026-01-15T12:00:00Z') / 1000);
            const segment = loadSession('seed0030-ten-diverse-deaths').segments[3];
            const standardTime = await runSegment(segmentInput(segment, new InMemoryStorage(), 277));
            assert.match(standardTime.getScreens()[277], /Welcome to Kopasker/,
                'Recording-clock override must select the winter DST flag through the same parser');
        } finally {
            if (previousClock === undefined) delete process.env.TELEPORT_RECORDING_EPOCH;
            else process.env.TELEPORT_RECORDING_EPOCH = previousClock;
        }
    }
    console.log(`${process.env.TZ}: correct shopkeeper; identical replay under winter and summer clocks.`);
}
