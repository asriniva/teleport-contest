import { Int32Array, assertStackRestored, allocationMetric, assertMemoryGrowth, memoryCheckpoint, referenceBackend, referenceLabel } from './native-test-backend.mjs';
const referenceFactory = referenceBackend('mplayer', emscriptenReferenceFactory);
import assert from './native-test-assert.mjs';
import { readFileSync } from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/mplayer-reference.mjs';
import hybridFactory from '../.cache/tu-probes/mplayer-hybrid.mjs';
import { createPortedRuntime } from '../js/backends/emscripten/runtime.js';
import { C, R, T } from '../js/c-runtime/context.js';

const layouts = JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json', import.meta.url)));
const layout = layouts.mplayer;
const modules = [await referenceFactory(), await hybridFactory({ nethackPorted: createPortedRuntime(layouts) })];
const stacks = modules.map(module => module._probe_stack());
let comparisons = 0;
function scope() {
    assert.equal(C, undefined); assert.equal(R, undefined); assert.equal(T, undefined);
    modules.forEach((module, i) => assertStackRestored(module, stacks[i]));
}
function bytes(module, pointer) {
    if (!pointer) return null;
    let end = Number(pointer); while (module.HEAPU8[end]) end++;
    return Buffer.from(module.HEAPU8.slice(Number(pointer), end));
}
function allocate(module, value) {
    const data = Buffer.isBuffer(value) ? value : Buffer.from(value), pointer = module._malloc(BigInt(data.length + 1));
    module.HEAPU8.set(data, Number(pointer)); module.HEAPU8[Number(pointer) + data.length] = 0; return pointer;
}
function snapshot(module) {
    return { monsters: Array.from({ length: module._probe_monster_count() }, (_, i) => ({
        pm: module._probe_mon_pm(i), female: module._probe_mon_female(i), peaceful: module._probe_mon_peaceful(i),
        level: module._probe_mon_level(i), hp: module._probe_mon_hp(i), hpmax: module._probe_mon_hpmax(i), malign: module._probe_mon_malign(i),
        name: bytes(module, module._probe_mon_name(i))?.toString('hex') ?? null,
    })), objects: Array.from({ length: module._probe_object_count() }, (_, i) => ({
        fields: Array.from({ length: 11 }, (_, field) => module._probe_object_field(i, field)), quantity: module._probe_object_quantity(i),
    })), rng: module._probe_rng_count(), randomState: module._probe_rng_state() >>> 0,
        result: module._probe_result(), name: bytes(module, module._probe_name_result()).toString('hex'),
        good: module._probe_good_calls(), copy: module._probe_fake_copy(), trace: bytes(module, module._probe_trace()).toString('hex') };
}
function state() { const values = modules.map(snapshot); assert.deepEqual(values[1], values[0]); scope(); comparisons++; return values[0]; }
function call(name, ...args) {
    const results = modules.map(module => module['_probe_' + name](...args));
    assert.deepEqual(results[1], results[0], `${name}(${args})`); state(); comparisons++; return results[0];
}
function rng(values) {
    modules.forEach(module => {
        new Int32Array(module.HEAPU8.buffer, Number(module._probe_rng_pointer()), values.length).set(values); module._probe_rng_length(values.length);
    }); state();
}
function existing(pm, name, named = 1) {
    modules.forEach(module => {
        const pointer = allocate(module, name); module._probe_existing(pm, BigInt(pointer), named); module._free(pointer);
    }); state();
}
function dev() {
    const result = modules.map(module => {
        const pointer = module._probe_dev(); return { present: Boolean(pointer), text: bytes(module, pointer)?.toString('hex') ?? null };
    }); assert.deepEqual(result[1], result[0]); state(); comparisons++; return result[0];
}
function trace() { return Buffer.from(state().trace, 'hex').toString(); }
call('reset', 1);
modules.forEach(module => {
    assert.equal(Number(module._probe_context_size()), layout.monsterSize);
    for (let i = 0; i < module._probe_layout_count(); i++) {
        const key = bytes(module, module._probe_layout_name(i)).toString(); assert.equal(Number(module._probe_layout_value(i)), layout[key], key);
    }
});
// A developer name comes from C static storage. Its address must remain
// stable while other literals are materialized and after linear-memory growth.
call('reset', 1); rng([0]);
const literalPointers = modules.map(module => module._probe_dev());
const literalBytes = modules.map((module, i) => bytes(module, literalPointers[i]));
state();
function verifyLiteral() {
    call('reset', 1); rng([0]);
    modules.forEach((module, i) => {
        assert.equal(module._probe_dev(), literalPointers[i]);
        assert.deepEqual(bytes(module, literalPointers[i]), literalBytes[i]);
    });
    state(); comparisons++;
}
const selectedNames = [];
for (let i = 0; i < 58; i++) {
    call('reset', i); rng([i]); selectedNames.push(dev()); assert.equal(state().rng, 1);
}
assert.ok(selectedNames.every(name => name.present), 'Even the empty developer name is a nonnull C string');
assert.deepEqual(selectedNames[57], { present: true, text: '' });
verifyLiteral();
for (const [index, name, named, player] of [[0, 'Alex the Test', 1, true], [13, 'Patric the Test', 1, true],
    [14, 'Pat the Test', 1, true], [57, '', 0, true], [57, '', 1, true], [0, 'Alex the Test', 1, false]]) {
    call('reset', 1); existing(player ? layout.PM_ARCHEOLOGIST : layout.PM_ARCHEOLOGIST - 1, name, named); rng(Array(100).fill(index));
    const selected = dev();
    const collision = player && (index === 0 || index === 13 || index === 57);
    assert.equal(selected.present, !collision); assert.equal(state().rng, collision ? 100 : 1);
}
for (const pm of [layout.PM_ARCHEOLOGIST, layout.PM_VALKYRIE]) for (const index of [0, 6, 57]) for (const femaleRoll of [0, 1]) {
    call('reset', 1); rng([index, femaleRoll]); call('name', pm, 17);
    assert.ok(Buffer.from(state().name, 'hex').toString().endsWith(' the Rank17'));
}
call('reset', 1); existing(layout.PM_ARCHEOLOGIST, '', 0); rng(Array(100).fill(57)); call('name', layout.PM_ARCHEOLOGIST, 3);
assert.equal(Buffer.from(state().name, 'hex').toString(), 'Adam the Rank3');
call('reset', 1); existing(layout.PM_ARCHEOLOGIST, '', 0); rng(Array(100).fill(57)); call('name', layout.PM_VALKYRIE, 3);
assert.equal(Buffer.from(state().name, 'hex').toString(), 'Eve the Rank3');
for (const sequence of [Array(20).fill(0), Array(20).fill(1), [1, 1, 1, 0, 2], [1, 1, 1, 1, 0, 3], [0, 0, 0, 0, 2]]) {
    call('reset', 1); rng(sequence); call('armor', layout.STRANGE_OBJECT); assert.equal(state().objects.length, 0);
    call('armor', layout.PLATE_MAIL); const armor = state().objects[0];
    assert.equal(armor.fields[2], 0); assert.equal(armor.fields[3], 0); assert.equal(armor.fields[10], 0);
}
const roles = ['PM_ARCHEOLOGIST', 'PM_BARBARIAN', 'PM_CAVE_DWELLER', 'PM_HEALER', 'PM_KNIGHT', 'PM_MONK', 'PM_CLERIC', 'PM_RANGER', 'PM_ROGUE', 'PM_SAMURAI', 'PM_TOURIST', 'PM_VALKYRIE', 'PM_WIZARD'];
const observed = new Set();
for (const role of roles) for (let seed = 0; seed < 12; seed++) for (const endgame of [0, 1]) for (const special of [0, 1]) {
    call('reset', seed); call('option', 1, endgame); call('option', 2, seed); call('option', 3, seed % 3); call('option', 4, seed % 2); call('option', 6, seed % 2);
    call('make', layout[role], 10, 11, special); const result = state();
    assert.ok(result.result >= 0); const mon = result.monsters[result.result];
    assert.equal(mon.pm, layout[role]); assert.equal(mon.peaceful, 0); assert.equal(mon.hp, mon.hpmax); assert.equal(mon.malign, -7);
    assert.ok(mon.level >= (endgame && special ? 15 : 1) && mon.level <= (endgame && special ? 30 : 16));
    result.objects.forEach(object => observed.add(object.fields[0]));
    if (endgame && special) assert.ok(result.objects.some(object => object.fields[0] === layout.FAKE_AMULET_OF_YENDOR));
}
for (const fail of [0, 1]) for (const occupied of [0, 1]) {
    call('reset', 42); call('option', 0, fail); if (occupied) call('occupied', 10, 11);
    call('make', layout.PM_ARCHEOLOGIST, 10, 11, 1); assert.equal(state().result < 0, Boolean(fail));
    assert.equal(trace().includes('rloc:'), Boolean(occupied));
}
call('reset', 1); call('make', layout.PM_ARCHEOLOGIST - 1, 10, 11, 1); assert.equal(state().result, -1); assert.equal(state().rng, 0);
for (const failures of [-1, 0, 1, 50, 51, 52]) {
    call('reset', 123); call('option', 5, failures); call('create', 1, 0);
    assert.equal(state().copy, 1, 'The full cg.zeromonst representation was copied before set_mon_data');
    assert.equal(state().good, failures < 0 || failures >= 51 ? 52 : failures + 1);
    assert.equal(state().monsters.length, failures < 0 || failures >= 51 ? 0 : 1);
}
call('reset', 1); call('create', 0, 1); assert.equal(state().rng, 0);
call('reset', 123); call('option', 1, 1); call('option', 6, 1); call('create', 5, 1);
assert.equal(state().copy, 1);
for (const peaceful of [0, 1]) for (const sameRole of [0, 1]) for (const copied of [0, 1]) for (const roll of [0, 1, 2]) {
    call('reset', 1); existing(layout.PM_ARCHEOLOGIST, 'Player', 1); call('role', sameRole ? layout.PM_ARCHEOLOGIST : layout.PM_KNIGHT); rng([roll]); call('clear');
    call('talk', 0, peaceful, copied);
    if (peaceful) assert.equal(state().rng, 0);
    else {
        assert.equal(state().rng, 1);
        const text = trace();
        assert.equal(text.includes('The low-life') || text.includes('Fight, scum') || text.includes('Here is what'), !sameRole || Boolean(copied), 'Role message choice uses permonst pointer identity');
    }
}
// Disabled logging at a new site preserves its old caller annotation.
call('reset', 1); rng([0]); dev(); existing(layout.PM_ARCHEOLOGIST, 'Player', 1); call('option', 10, 0); call('clear'); rng([0]); call('talk', 0, 0, 0);
assert.ok(trace().includes(':dev_name;'));
const oldBuffers = modules.map(module => memoryCheckpoint(module));
modules.forEach(module => module._malloc(40n * 1024n * 1024n));
modules.forEach((module, i) => assertMemoryGrowth(module, oldBuffers[i]));
verifyLiteral();
call('reset', 99); call('option', 1, 1); call('option', 6, 1); call('make', layout.PM_WIZARD, 10, 11, 1); call('create', 2, 0);
const independent = await hybridFactory({ nethackPorted: createPortedRuntime(layouts) });
const before = state(); independent._probe_reset(2); independent._probe_make(layout.PM_KNIGHT, 10, 11, 0); independent._probe_create(1, 0);
assert.deepEqual(state(), before); scope(); comparisons++;
console.log(`MPLAYER: ${comparisons} ${referenceLabel}/hybrid developer-name, role-equipment, temporary-copy, retry, talk-identity and RNG-site comparisons checked.`);
