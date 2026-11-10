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
    const build = JSON.parse(fs.readFileSync(new URL('../js/wasm/build.json', import.meta.url)));
    const dependencies = terminalSmoke.getDependencyDiagnostics();
    assert.equal(dependencies.backend, build.dependencyBackend || 'c', 'Diagnostics identify the compiled dependency backend');
    if (dependencies.backend === 'javascript') {
        for (const name of ['tgetent', 'tgetstr', 'tputs'])
            assert.ok(dependencies.calls[name] > 0, `Game actually invoked JS ${name}`);
        const wasm = new WebAssembly.Module(fs.readFileSync(new URL('../js/wasm/nethack.wasm', import.meta.url)));
        const imports = new Set(WebAssembly.Module.imports(wasm).map(item => item.name));
        for (const name of ['tgetent', 'tgetstr', 'tgetnum', 'tgetflag', 'tgoto',
            'teleport_js_tparm', 'teleport_js_tputs', 'teleport_compress_file'])
            assert.ok(imports.has(name), `Regular game imports JS dependency ${name}`);
        const symbols = fs.readFileSync(new URL('../js/wasm/nethack.mjs.symbols', import.meta.url), 'utf8')
            .split('\n').map(line => line.slice(line.indexOf(':') + 1));
        const regexBridgeImports = ['teleport_js_regcomp', 'teleport_js_regexec',
            'teleport_js_regerror', 'teleport_js_regfree'];
        if (build.regexTransport === 'ported-posixregex-direct-js') {
            assert.equal(build.regex, 'javascript-native-macos-compatible-ERE-C-locale');
            assert.ok(build.javascriptTranslationUnits.some(port => port.name === 'posixregex'),
                'Direct regex transport registers the original NetHack JS wrapper TU');
            for (const name of ['regex_init', 'regex_compile', 'regex_match', 'regex_error_desc', 'regex_free'])
                assert.ok(imports.has(name), `Game enters the JS NetHack wrapper ${name}`);
            for (const name of regexBridgeImports)
                assert.ok(!imports.has(name), `Direct regex transport prunes obsolete bridge ${name}`);
            for (const name of ['regcomp', 'regexec', 'regerror', 'regfree'])
                assert.ok(!symbols.includes(name), `Direct regex transport excludes compiled libc entry ${name}`);
        } else {
            assert.equal(build.regexTransport, 'wasm-libc-js-bridge', 'Build identifies its exact regex transport');
            for (const name of regexBridgeImports)
                assert.ok(imports.has(name), `Legacy libc transport imports JS dependency ${name}`);
        }
        assert.ok(!symbols.some(name => name.startsWith('tre_')), 'Regular game excludes compiled TRE algorithms');
        for (const name of ['ncompress_encode', 'ncompress_decode', 'setupterm', '_nc_read_entry', '_nc_tparm_analyze'])
            assert.ok(!symbols.includes(name), `Regular game excludes compiled dependency ${name}`);
    } else assert.equal(dependencies.calls, null, 'C reference mode must not claim JS dependency execution');
    assert.match(terminalSmoke.getScreens()[0], /\x0elqqqqqqk\x0f/,
        'Boundary screens must retain recorder shadow encoding without glyph conversion');

    // Real configuration and inventory screens verify both the selected
    // regex calls and their visible effect, independently of bridge names.
    const plainInventory = await runSegment(inputFor('seed8000-tourist-starter', 11));
    const coloredInput = inputFor('seed8000-tourist-starter', 11);
    coloredInput.nethackrc += '\nMENUCOLOR="gold (pieces|coins)$"=red&bold\n';
    const coloredInventory = await runSegment(coloredInput);
    if (build.regexTransport === 'ported-posixregex-direct-js') {
        const regex = coloredInventory.getDependencyDiagnostics().regex;
        assert.equal(regex.transport, build.regexTransport);
        assert.equal(regex.backend, build.regex);
        assert.ok(regex.calls.regcomp > 0, 'Actual game invokes the direct JS regex compiler');
        assert.ok(regex.calls.regexec > 0, 'Actual inventory invokes direct JS regex matching');
        if (coloredInventory.getDependencyDiagnostics().backend === 'javascript')
            assert.deepEqual(Object.fromEntries(Object.keys(regex.calls).map(name =>
                [name, coloredInventory.getDependencyDiagnostics().calls[name]])), regex.calls,
                'Flat diagnostics count the selected regex path');
    }
    const plainGrid = decodeScreen(plainInventory.getScreens()[11]);
    const coloredGrid = decodeScreen(coloredInventory.getScreens()[11]);
    const rowText = row => row.map(cell => cell.ch).join('');
    assert.deepEqual(coloredGrid.map(rowText), plainGrid.map(rowText),
        'A menu regex changes styling without changing game text');
    const goldRow = plainGrid.findIndex(row => rowText(row).includes('gold pieces'));
    assert.ok(goldRow >= 0, 'Actual inventory contains a gold-pieces entry');
    const goldColumn = rowText(plainGrid[goldRow]).indexOf('gold pieces');
    for (let column = goldColumn; column < goldColumn + 'gold pieces'.length; column++) {
        assert.equal(coloredGrid[goldRow][column].color, 1, 'ERE-selected gold entry is red');
        assert.equal(coloredGrid[goldRow][column].attr, 2, 'ERE-selected gold entry is bold');
        assert.notDeepEqual(coloredGrid[goldRow][column], plainGrid[goldRow][column],
            'The configured rule visibly changes the selected entry');
    }
    for (let row = 0; row < plainGrid.length; row++) if (row !== goldRow)
        assert.deepEqual(coloredGrid[row], plainGrid[row], 'Nonmatching inventory rows retain their styles');
    assert.deepEqual(coloredInventory.getRngLog(), plainInventory.getRngLog(),
        'Menu regex matching does not change gameplay RNG');
    console.log('Actual inventory ERE alternation selects red/bold gold text without gameplay changes.');

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
        const deathGame = await runSegment(segmentInput(bones.segments[0], storage));
        if (deathGame.getDependencyDiagnostics().backend === 'javascript')
            assert.ok(deathGame.getDependencyDiagnostics().calls.compress > 0, 'Game bones persistence uses JS compression');
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
