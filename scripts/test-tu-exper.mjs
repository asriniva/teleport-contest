import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import referenceFactory from '../.cache/tu-probes/exper-reference.mjs';
import hybridFactory from '../.cache/tu-probes/exper-hybrid.mjs';
import { createPortedRuntime } from '../js/ported/wasm-runtime.js';
import { C, R, T } from '../js/ported/c-runtime.js';

const layouts = JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json', import.meta.url)));
const layout = layouts.exper;
const modules = [await referenceFactory(), await hybridFactory({ nethackPorted: createPortedRuntime(layouts) })];
const stacks = modules.map(module => module._probe_stack());
let comparisons = 0;
function scope() {
    assert.equal(C, undefined); assert.equal(R, undefined); assert.equal(T, undefined);
    modules.forEach((module, i) => assert.equal(module._probe_stack(), stacks[i]));
}
function bytes(module, pointer) {
    let end = Number(pointer); while (module.HEAPU8[end]) end++;
    return Buffer.from(module.HEAPU8.slice(Number(pointer), end));
}
function allocate(module, value) {
    if (value === null) return 0;
    const data = Buffer.isBuffer(value) ? value : Buffer.from(value), pointer = module._malloc(BigInt(data.length + 1));
    module.HEAPU8.set(data, Number(pointer)); module.HEAPU8[Number(pointer) + data.length] = 0; return pointer;
}
function snapshot(module) {
    return { states: Array.from({ length: 5 }, (_, i) => {
        const pointer = Number(module._probe_snapshot_pointer(i)), size = Number(module._probe_snapshot_size(i));
        return Buffer.from(module.HEAPU8.slice(pointer, pointer + size));
    }), rng: module._probe_rng_count(), randomState: module._probe_rng_state() >>> 0, achievements: module._probe_achievements(),
    trace: bytes(module, module._probe_trace()).toString('hex'), assertion: bytes(module, module._probe_assertion()).toString('hex') };
}
function state() { const values = modules.map(snapshot); assert.deepEqual(values[1], values[0]); scope(); comparisons++; return values[0]; }
function call(name, ...args) {
    const result = modules.map(module => module['_probe_' + name](...args));
    assert.deepEqual(result[1], result[0], `${name}(${args})`); state(); comparisons++; return result[0];
}
function reset(seed = 1) { call('reset', seed); }
function rng(values) {
    modules.forEach(module => { new Int32Array(module.HEAPU8.buffer, Number(module._probe_rng_pointer()), values.length).set(values); module._probe_rng_length(values.length); }); state();
}
function hero(level = 1, xp = 0n, score = 0n, poly = 0, maximum = level, peak = level) { call('hero', level, maximum, peak, xp, score, poly); }
function textCall(name, text, ...args) {
    const results = modules.map(module => {
        const pointer = allocate(module, text), result = module['_probe_' + name](BigInt(pointer), ...args);
        if (pointer) module._free(pointer); return result;
    }); assert.deepEqual(results[1], results[0]); state(); comparisons++; return results[0];
}
function readHero(name, index) {
    const module = modules[0], pointer = Number(module._probe_snapshot_pointer(0));
    if (index !== undefined) return new DataView(module.HEAPU8.buffer).getInt16(pointer + layout['hero_' + name] + 2 * index, true);
    const size = layout['hero_' + name + '_size'], address = pointer + layout['hero_' + name];
    return new DataView(module.HEAPU8.buffer)[`get${size === 8 ? 'Big' : ''}Int${size * 8}`](address, true);
}
function trace() { return Buffer.from(state().trace, 'hex').toString(); }
reset();
modules.forEach(module => {
    for (let i = 0; i < module._probe_layout_count(); i++) {
        const key = bytes(module, module._probe_layout_name(i)).toString(), actual = module._probe_layout_value(i);
        if (key === 'LONG_MAX') assert.equal(BigInt(actual), BigInt(layout[key])); else assert.equal(Number(actual), layout[key], key);
    }
});
for (const level of [-2147483648, -1, 0, 1, 2, 8, 9, 10, 11, 18, 19, 20, 21, 30, 100, 2147483647]) call('threshold', level);
const roles = ['PM_ARCHEOLOGIST', 'PM_CLERIC', 'PM_WIZARD', 'PM_HEALER', 'PM_KNIGHT', 'PM_BARBARIAN', 'PM_VALKYRIE'];
for (const role of roles) for (const energy of [-100, -5, -3, -1, 0, 1, 3, 5, 100]) {
    reset(); call('role', layout[role], 10, 0, 1, 2, 1, 3, 2, 4); call('energy_modifier', energy);
}
for (const level of [0, 1, 9, 10, 29, 30]) for (const role of roles) for (const roll of [0, 99]) {
    reset(); hero(level); call('role', layout[role], 10, 0, 5, 3, -20, 3, 2, 4); call('role', layout[role], 10, 1, 7, 2, 1, 3, 3, 5); rng([roll, roll]);
    assert.ok(call('power') >= 1);
}
for (const maximum of [-10000, -200, -1, 0, 199, 200, 599, 600, 26000, 26200, 26400, 26800, 2147483647]) {
    reset(); hero(30); call('health', 50, 100, 0, maximum, 0, 0, 0);
    call('role', layout.PM_WIZARD, 10, 0, 0, 0, 300, 1, 300, 1); rng([0]); call('power');
}
reset(); hero(0); call('role', layout.PM_ARCHEOLOGIST, 10, 0, 32767, 0, 1, 3, 2, 4); call('role', layout.PM_ARCHEOLOGIST, 10, 1, 32767, 0, 1, 3, 2, 4);
assert.equal(call('power'), 65534); assert.equal(readHero('ueninc', 0), -2, 'Saved increment uses signed xint16 storage');
reset(); hero(1); call('option', 1, -3); call('role', layout.PM_HEALER, 10, 0, 0, 0, -3, 20, 0, 20); rng([0]); call('power');

// Exhaust every byte value for each attack and damage tag against native C.
for (const kind of ['attack', 'damage']) for (let value = 0; value < 256; value++) {
    reset(); call('attack', 0, kind === 'attack' ? value : 0, kind === 'damage' ? value : 0, 2, 3); call('experience', 1);
}
// Populate each slot progressively so later-slot offsets and the final attack
// are observed independently, rather than comparing only a first-slot attack.
reset();
let previousExperience = call('experience', 1);
for (let index = 0; index < layout.NATTK; index++) {
    call('attack', index, layout.AT_WEAP, layout.AD_DRLI, 1, 24);
    const experience = call('experience', 1);
    assert.ok(experience > previousExperience, `Attack slot ${index} contributes experience`);
    previousExperience = experience;
}
for (const level of [-1, 0, 1, 8, 9, 30, 127]) for (const armor of [-30, -1, 0, 2, 3, 10]) for (const speed of [0, layout.NORMAL_SPEED, layout.NORMAL_SPEED + 1, 3 * layout.NORMAL_SPEED / 2, 3 * layout.NORMAL_SPEED / 2 + 1, 255]) {
    reset(); call('option', 0, armor); call('victim', level, speed, 0, 1, 0, 0, 0); call('experience', 1);
}
for (const amphibious of [0, 1, 2, 4]) for (const dice of [[3, 7], [1, 23], [4, 6], [255, 255]]) {
    reset(); call('amphibious', amphibious); call('victim', 9, 30, layout.S_EEL, 1, 0, 0, 0); call('attack', 0, layout.AT_WEAP, layout.AD_WRAP, ...dice); call('experience', 1);
}
for (const revived of [0, 1]) for (const cloned of [0, 1]) for (const kills of [0, 1, 20, 21, 40, 41, 80, 81, 120, 121, 180, 181, 240, 241, 255, 1000]) {
    reset(); call('victim', 10, 20, 0, 1, revived, cloned, 0); call('experience', kills);
}
if (layout.MAIL_STRUCTURES) { reset(); call('victim', 30, 30, layout.S_EEL, 1, 0, 0, 1); assert.equal(call('experience', 1), 1); }
const LONG_MAX = BigInt(layout.LONG_MAX);
for (const role of [layout.PM_WIZARD, layout.PM_ARCHEOLOGIST]) for (const show of [0, 1]) for (const percent of [0, 1]) {
    for (const [xp, score, increment, extra] of [[0n, 0n, 0, 0], [10n, 900n, 50, 0], [100n, 1900n, -25, 1],
        [LONG_MAX - 2n, LONG_MAX - 2n, 10, 0], [0n, 100n, 536870912, 0], [0n, 100n, 1073741824, -1],
        [0n, 0n, -2147483648, 2147483647], [0n, 0n, 2147483647, 2147483647]]) {
        reset(); hero(5, xp, score); call('role', role, 10, 0, 1, 2, 1, 3, 2, 4); call('flags', show, show, 1, 0); call('option', 3, percent); call('more', increment, extra);
    }
}
for (const level of [1, 2, 10, 30]) for (const drainer of [null, 'life drain', '#levelchange']) for (const resistance of [0, 1]) for (const poly of [0, 1]) {
    reset(); hero(level, 999999n, 1000n, poly); call('increments', Math.max(level - 1, 1), 20, 12); call('option', 6, resistance); call('health', 5, 8, 3, 4, 30, 2, 3);
    assert.equal(textCall('lose', drainer, 0), 0);
}
for (const doneMode of [0, 1, 2]) { reset(); hero(1, 100n); call('option', 11, doneMode); textCall('killer', 'aliased killer'); assert.equal(textCall('lose', null, 1), 0); }
if (layout.ASSERT_ENABLED) for (const forced of [-1, layout.MAXULEV]) {
    reset(); hero(2); call('option', 7, forced); assert.equal(textCall('lose', null, 0), -1); assert.ok(Buffer.from(state().assertion, 'hex').toString().includes('losexp'));
}
for (const level of [1, 2, 3, 9, 10, 29, 30]) for (const incremental of [0, 1]) for (const poly of [0, 1]) for (const record of [0, 1]) {
    reset(); hero(level, LONG_MAX / 100n, 0n, poly, 30, 30); call('option', 8, record); call('plus', incremental);
}
reset(); hero(2); call('plus', 0); hero(2, 0n, 0n, 0, 3, 3); call('plus', 0); assert.ok(trace().includes('regained experience level'));
for (const level of [1, 9, 10, 19, 29, 30]) {
    const threshold = call('threshold', level);
    for (const experience of [threshold - 1n, threshold, threshold * 2n]) { reset(); hero(level, experience); call('new_level'); }
    for (const gaining of [0, 1]) for (const experience of [0n, threshold, LONG_MAX - 1n]) { reset(); hero(level, experience); rng([2147483647]); call('random_experience', gaining); }
}
// Different-site disabled logging retains the preceding newpw annotation.
reset(); rng([0]); call('power'); call('option', 10, 0); call('clear'); call('random_experience', 0); assert.ok(trace().includes(':newpw;'));
const oldBuffers = modules.map(module => module.HEAPU8.buffer);
modules.forEach(module => module._malloc(40n * 1024n * 1024n));
modules.forEach((module, i) => assert.notEqual(module.HEAPU8.buffer, oldBuffers[i]));
reset(); hero(5, 10000n, 0n, 1); call('plus', 1); textCall('lose', 'after-growth', 0);
const independent = await hybridFactory({ nethackPorted: createPortedRuntime(layouts) });
const before = state(); independent._probe_reset(99); independent._probe_plus(0); independent._probe_more(100, 1); independent._probe_new_level();
assert.deepEqual(state(), before); scope(); comparisons++;
console.log(`EXPER: ${comparisons} original-C/hybrid threshold, energy, attack-XP, score, level-change, assertion and RNG-site comparisons passed.`);
