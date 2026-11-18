import assert from 'node:assert/strict';
import {readFileSync} from 'node:fs';
import layouts from '../js/wasm/tu-layouts.json' with {type:'json'};
import {createStandaloneEnvironment} from '../js/nethack/environment.js';
import {runSegment} from '../js/standalone-recorder-adapter.js';
import {decodeScreen} from '../frozen/screen-decode.mjs';

const fixture = JSON.parse(readFileSync(new URL(
    '../sessions/seed0007-rogue-snake-swamp.session.json', import.meta.url
), 'utf8')).segments[0];
const ready = 'Septor\rynr"moy   n';
assert.ok(fixture.moves.startsWith(ready));
const idle = await runSegment({...fixture, moves: ready});
const enhance = await runSegment({...fixture, moves: ready + '\u00e5'});
assert.equal(enhance.getScreens().length, idle.getScreens().length + 1);
assert.match(decodeScreen(enhance.getScreens().at(-1))[0].map(cell => cell.ch).join(''), /Current skills:/);
assert.deepEqual(enhance.getRngLog(), idle.getRngLog());

const env = createStandaloneEnvironment({environment: {NOMUX_MARKERS: '1'}});
env.enableStdio();
env.enableDecl(layouts.decl);
env.enableHacklib(layouts.hacklib);
env.enableDependencies();
const terminal = env.enableTerminal(layouts.termcap, {preservePublishedSaveCursor: true});
const {memory, services} = env;
const call = (name, ...args) => env.call('termcap', name, ...args);
const raw = line => call('nomux_raw_emit', services.literal(line), 0);

raw('Saving...');
call('nomux_reset_raw_mode');
call('nomux_capture_write_input_boundary');
const saving = terminal.frames.at(-1);
assert.match(saving.screen, /Saving/);
assert.deepEqual(saving.cursor, [0, 1, 1]);
raw('No  Points');
call('nomux_capture_write_input_boundary');
const score = terminal.frames.at(-1);
assert.match(score.screen, /No {1,2}(?:\x1b\[\d+C)?Points/);
assert.doesNotMatch(score.screen, /Saving/);
assert.deepEqual(score.cursor, [0, 1, 1]);

const cells = memory.HEAPU8.subarray(terminal.global('nomux_buf'), terminal.global('nomux_buf') + 24 * 80 * 4);
for (let cell = 0; cell < 24 * 80; cell++) {
    cells.set(cell % 2 ? [65, 1, 7, 1] : [66, 2, 0, 0], cell * 4);
}
const rawGlobals = ['nomux_raw_active', 'nomux_raw_row', 'nomux_raw_col'];
const rawState = () => rawGlobals.map(name => memory.view.getInt32(terminal.global(name), true));
const before = rawState();
const pointer = call('nomux_capture_screen');
assert.ok(memory.readString(pointer).length > 24 * 256);
assert.deepEqual(rawState(), before);
console.log('PASS: one-byte M-e, preserved save cursor, fresh score screen, dense capture capacity');
