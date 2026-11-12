import { Int32Array, assertStackRestored, allocationMetric, assertMemoryGrowth, memoryCheckpoint, referenceBackend, referenceLabel } from './native-test-backend.mjs';
const referenceFactory = referenceBackend('were', emscriptenReferenceFactory);
import assert from './native-test-assert.mjs';
import { readFileSync } from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/were-reference.mjs';
import hybridFactory from '../.cache/tu-probes/were-hybrid.mjs';
import { createPortedRuntime } from '../js/backends/emscripten/runtime.js';
import { C, R, T } from '../js/c-runtime/context.js';

const layouts = JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json', import.meta.url)));
const layout = layouts.were;
const modules = [await referenceFactory(), await hybridFactory({ nethackPorted: createPortedRuntime(layouts) })];
const stacks = modules.map(module => module._probe_stack());
let comparisons = 0;
function scope() {
    assert.equal(C, undefined); assert.equal(R, undefined); assert.equal(T, undefined);
    modules.forEach((module, i) => assertStackRestored(module, stacks[i]));
}
function bytes(module, pointer) {
    let end = Number(pointer); while (module.HEAPU8[end]) end++;
    return Buffer.from(module.HEAPU8.slice(Number(pointer), end));
}
function snapshot(module) {
    return { mon: { pm: module._probe_mon_pm(), hp: module._probe_mon_hp(), sleep: module._probe_mon_sleep(), move: module._probe_mon_move(),
        frozen: module._probe_mon_frozen(), flee: module._probe_mon_flee() },
        current: module._probe_current(), lycan: module._probe_lycan(), timeout: module._probe_timeout(), changes: module._probe_changes(),
        rng: module._probe_rng_count(), visible: module._probe_visible(), genbuf: bytes(module, module._probe_genbuf()).toString('hex'),
        summoned: Array.from({ length: module._probe_summoned_count() }, (_, i) => ({ pm: module._probe_summoned_pm(i), tame: module._probe_summoned_tame(i) })),
        trace: bytes(module, module._probe_trace()).toString('hex') };
}
function state() { const values = modules.map(snapshot); assert.deepEqual(values[1], values[0]); scope(); comparisons++; return values[0]; }
function call(name, ...args) {
    const result = modules.map(module => module['_probe_' + name](...args));
    assert.deepEqual(result[1], result[0], `${name}(${args})`); state(); comparisons++; return result[0];
}
function reset() { call('reset'); }
function option(index, value) { call('option', index, value); }
function rng(values) {
    modules.forEach(module => {
        new Int32Array(module.HEAPU8.buffer, Number(module._probe_rng_pointer()), 512).fill(0);
        new Int32Array(module.HEAPU8.buffer, Number(module._probe_rng_pointer()), values.length).set(values);
        module._probe_rng_length(values.length);
    }); state();
}
function mon(pm, { hp = 50, max = 100, asleep = 0, move = 1, frozen = 0, peaceful = 0, female = 0 } = {}) {
    call('mon', pm, hp, max, asleep, move, frozen, peaceful, female);
}
function hero({ current = layout.PM_HUMAN_WEREWOLF, lycan = layout.PM_WEREWOLF, timeout = 0, multi = 0, moving = 0, paranoia = 0, moon = 0 } = {}) {
    call('hero', current, lycan, timeout, multi, moving, paranoia, moon);
}
function trace() { return Buffer.from(state().trace, 'hex').toString(); }
reset();
modules.forEach(module => {
    assert.equal(Number(module._probe_context_size()), layout.monsterSize);
    for (let i = 0; i < module._probe_layout_count(); i++) {
        const key = bytes(module, module._probe_layout_name(i)).toString(); assert.equal(Number(module._probe_layout_value(i)), layout[key], key);
    }
});
for (let pm = -1; pm < layout.NUMMONS + 2; pm++) { call('counter', pm); call('beastie', pm); }
const pairs = [[layout.PM_WEREWOLF, layout.PM_HUMAN_WEREWOLF], [layout.PM_WEREJACKAL, layout.PM_HUMAN_WEREJACKAL], [layout.PM_WERERAT, layout.PM_HUMAN_WERERAT]];
for (const [beast, human] of pairs) {
    assert.equal(call('counter', beast), human); assert.equal(call('counter', human), beast);
    for (const starting of [beast, human]) for (const protection of [0, 1, 2]) for (const night of [0, 1]) for (const full of [0, 1]) for (const roll of [0, 1]) {
        reset(); mon(starting); call('properties', protection); option(0, night); hero({ moon: full ? layout.FULL_MOON : 0 }); rng([roll]);
        call('change');
    }
}
// Full visibility/message and sleep/paralysis/healing permutations; native
// Mgender/pmname use actual monster names and bitfield state from do_name.c.
for (const [beast, human] of pairs) for (const pm of [beast, human]) {
    for (const see of [0, 1]) for (const hallucination of [0, 32, 32 | 64, 32 | 128]) {
        reset(); mon(pm, { hp: 1, asleep: 1, move: 0, frozen: 7, female: see });
        option(1, see); call('properties', hallucination); call('new');
        assert.equal(state().mon.sleep, 0); assert.equal(state().mon.move, 1); assert.equal(state().mon.frozen, 0);
    }
}
for (const senses of [0, 4, 8, 16]) {
    reset(); mon(layout.PM_HUMAN_WEREWOLF); call('properties', senses); rng([0]); call('change');
    assert.equal(trace().includes('hear:'), senses === 0);
}
for (const fields of [{ hp: 0 }, { hp: 99 }, { hp: 100 }, { frozen: 7 }, { move: 0 }, { asleep: 1 }]) {
    reset(); mon(layout.PM_WEREWOLF, fields); call('new');
}
// Negative healing amounts use C integer division toward zero, rather
// than floor: (100 - 110) / 4 is -2, and the native fixture applies it.
reset(); mon(layout.PM_WEREWOLF, { hp: 110, max: 100 }); call('new');
assert.equal(state().mon.hp, 108); assert.ok(trace().includes('heal:-2:0;'));
for (const pm of [layout.PM_WOLF, layout.PM_SEWER_RAT]) {
    reset(); mon(pm); rng([0]); call('clear');
    const before = state(); call('change');
    assert.deepEqual(state(), before, 'Initial non-were guard changes no state and invokes no callbacks or RNG');
}
for (const moving of [0, 1]) for (const peaceful of [0, 1]) for (const scary of [0, 1]) for (const near of [0, 1]) {
    reset(); mon(layout.PM_WEREWOLF, { peaceful }); hero({ moving }); option(2, scary); option(3, near); rng([8]); call('new');
    assert.equal(state().mon.flee, moving && !peaceful && scary && near ? 1 : 0);
}
reset(); mon(layout.PM_WOLF); call('new'); assert.ok(trace().includes('impossible:unknown lycanthrope'));
// Disabled logging leaves the previous caller context intact, while all RNG
// calls and gameplay results still occur through the native fixture.
reset(); mon(layout.PM_HUMAN_WEREWOLF); rng([0]); call('change');
mon(layout.PM_WEREWOLF); hero({ moving: 1 }); option(2, 1); option(3, 1); option(11, 0);
call('clear'); rng([0]); call('new');
assert.ok(trace().includes('rn2:9:0@were.c:') && trace().includes(':were_change;'),
    'Disabled new_were RNG retains the caller from the earlier were_change site');
reset(); mon(layout.PM_HUMAN_WEREWOLF); call('set_changes', 9007199254740993n); rng([0]); call('change');
assert.equal(state().changes, 9007199254740994n, 'Long counter increments exactly beyond the JS number integer range');

const sequences = [[0], [1], [4], [0, 0, 0, 0, 0, 0], [4, 1, 0, 1, 0, 0, 0, 2, 0, 3]];
for (const [beast, human] of pairs) for (const pm of [beast, human, layout.PM_WOLF]) {
    for (const yours of [0, 1]) for (const protection of [0, 1, 2]) for (const sequence of sequences) {
        reset(); rng(sequence); call('properties', protection); option(8, sequence[0] % 3); option(9, sequence[0] % 2);
        const total = call('summon', pm, yours, sequence[0] % 2);
        assert.equal(total, state().summoned.length);
        assert.equal(state().visible, sequence[0] % 2 ? total : 0);
        if (yours) assert.ok(state().summoned.every(monster => monster.tame === 1));
    }
}
// Player transformation controls: property intrinsics/extrinsics, stunned or
// unaware query suppression, nearby-monster guard, and refusal/acceptance.
for (const mask of [0, 256, 512, 256 | 1024, 256 | 2048, 4096]) {
    for (const query of [0, 1]) for (const nearby of [0, 1]) for (const unaware of [0, 1, 2]) {
        reset(); hero({ multi: unaware ? -1 : 0, paranoia: query }); call('properties', mask); option(4, nearby); option(5, query);
        option(6, unaware === 1); option(7, unaware === 2); call('you');
    }
}
reset(); hero({ current: layout.PM_WEREWOLF }); call('you'); assert.equal(state().changes, 0n);
for (const current of [layout.PM_WEREWOLF, layout.PM_HUMAN_WEREWOLF, layout.PM_WOLF]) {
    for (const mask of [0, 256, 512, 1024 | 256, 2048, 4096]) for (const purify of [0, 1]) for (const query of [0, 1]) for (const nearby of [0, 1]) {
        reset(); hero({ current, timeout: query ? 0 : 77, paranoia: 1 }); call('properties', mask); option(4, nearby); option(5, query); rng([199]); call('unwere', purify);
        if (purify) assert.equal(state().lycan, -1);
    }
}
for (const pm of [-1, layout.PM_WEREWOLF, layout.PM_WERERAT]) { reset(); call('lycanthrope', pm); assert.equal(state().lycan, pm); assert.ok(trace().includes(`uasmon:${pm};`)); }
const oldBuffers = modules.map(module => memoryCheckpoint(module));
modules.forEach(module => module._malloc(40n * 1024n * 1024n));
modules.forEach((module, i) => assertMemoryGrowth(module, oldBuffers[i]));
reset(); mon(layout.PM_HUMAN_WEREWOLF, { asleep: 1, move: 0 }); rng([0]); call('change');
reset(); rng([4, 0, 1, 0, 0]); call('summon', layout.PM_WEREWOLF, 1, 1);
const independent = await hybridFactory({ nethackPorted: createPortedRuntime(layouts) });
const before = state(); independent._probe_reset(); independent._probe_change(); independent._probe_you();
assert.deepEqual(state(), before); scope(); comparisons++;
console.log(`WERE: ${comparisons} ${referenceLabel}/hybrid mapping, monster, player-property, summoning, callback and RNG-site comparisons checked.`);
