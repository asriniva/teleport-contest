// Fixed inline projections versus the existing proxy transport, on live memory.
import assert from 'node:assert/strict';
import {CMemory} from '../js/c-runtime/heap.js';
import {createArrayView} from '../js/c-runtime/records.js';

function fixture(fixed) {
    const memory = new CMemory({initialBytes: 16384, maximumBytes: 1024 * 1024});
    const base = memory.calloc(1, 24 * 80 * 4 + 640), cells = new Map(), rows = new Map();
    function cell(at) {
        if (!cells.has(at)) {
            const value = {address: at};
            for (const [index, name] of ['ch', 'fg', 'attr', 'decgfx'].entries())
                Object.defineProperty(value, name, {get: () => memory.view.getUint8(at + index),
                    set: value => memory.view.setUint8(at + index, value)});
            cells.set(at, value);
        }
        return cells.get(at);
    }
    function row(at) {
        if (!rows.has(at)) rows.set(at, createArrayView({address: at, byteLength: 320}, {
            checked: false, allowLeadingZeroes: true, propertyCount: fixed ? 80 : undefined, cacheReads: true,
            read: i => cell(at + i * 4), write: (i, value) => memory.memmove(at + i * 4, value.address, 4),
        }));
        return rows.get(at);
    }
    const grid = createArrayView({address: base, byteLength: 24 * 320}, {
        checked: false, allowLeadingZeroes: true, propertyCount: fixed ? 24 : undefined, cacheReads: true,
        read: i => row(base + i * 320), write: (i, value) => memory.memmove(base + i * 320, value.address, 320),
    });
    return {memory, base, grid};
}

const old = fixture(false), fixed = fixture(true);
for (const f of [old, fixed]) {
    const {grid, memory, base} = f;
    for (let row = 0; row < 24; row++) for (let col = 0; col < 80; col++) {
        const cell = grid[row][col];
        cell.ch = row * 17 + col;
        cell.fg = col % 16;
        cell.attr = row % 8;
        cell.decgfx = col % 2;
    }
    const held = grid[1][2];
    grid[1][2] = grid[0][3];
    assert.equal(held.ch, 3);
    assert.equal(grid['01']['02'], held);
    assert.equal(grid[24][0].address, base + 24 * 320);
    grid[24][0].ch = 99;
    assert.equal(memory.view.getUint8(base + 24 * 320), 99);
    const before = memory.buffer;
    memory.malloc(memory.buffer.byteLength + 64);
    assert.notEqual(memory.buffer, before);
    memory.view.setUint8(held.address, 128);
    assert.equal(held.ch, 128);
    held.ch = 255;
    assert.equal(grid[1][2].ch, 255);
    assert.deepEqual(Object.keys(grid), ['address', 'byteLength']);
    assert.equal(grid[-1], undefined);
    assert.equal(grid.toString(), '[object Object]');
    grid.label = 'live';
    assert.equal(grid.label, 'live');
    grid[0] = grid[1];
}
assert.deepEqual(fixed.memory.readBytes(fixed.base, 24 * 320 + 640), old.memory.readBytes(old.base, 24 * 320 + 640));

// Scalar loads and pointer slots are deliberately not cached.
for (const fixed of [false, true]) {
    let values = [1, 2, 3];
    const array = createArrayView({length: 3}, {propertyCount: fixed ? 3 : undefined,
        read: i => values[i], write: (i, value) => {values[i] = value;},
        onePast: i => Object.freeze({address: i * 8})});
    assert.equal(array[1], 2);
    values[1] = 19;
    assert.equal(array[1], 19);
    array[1] = 27;
    assert.equal(values[1], 27);
    assert.deepEqual(array[3], {address: 24});
    assert.throws(() => array[4], /bounds/);
    assert.throws(() => {array[3] = 4;}, /bounds/);
    assert.equal(array['01'], undefined);
}
assert.throws(() => createArrayView({}, {propertyCount: -1, read() {}}), /Unsupported fixed/);
console.log('PASS: fixed live grid equals proxy transport across 1,920 cells, aggregate copies, unusual pointer indices, growth and fresh scalar loads.');
