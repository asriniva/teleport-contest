// Live C record transport contracts. Game parity is checked separately.
import assert from 'node:assert/strict';
import {createPrototypeDescriptorFactory} from '../js/c-runtime/adapter-factories.js';

function runtime() {
    let bytes = new Uint8Array(128), bias = 0;
    const types = new Map(), cache = new Map();
    const view = createPrototypeDescriptorFactory({
        address: Number, cache, recordTypes: types, layout: {pairSize: 8},
        errorPrefix: 'Unknown test record field ',
    }, () => {
        const prototype = {};
        Object.defineProperties(prototype, {
            first: {get() {return new DataView(bytes.buffer).getInt32(this.address, true) + bias;},
                    set(value) {new DataView(bytes.buffer).setInt32(this.address, value - bias, true);}},
            second: {get() {return new DataView(bytes.buffer).getInt32(this.address + 4, true);},
                     set(value) {new DataView(bytes.buffer).setInt32(this.address + 4, value, true);}},
            alias: {get() {return this.first;}, set(value) {this.first = value;}},
        });
        return prototype;
    });
    return {view, grow() {const next = new Uint8Array(1024); next.set(bytes); bytes = next;},
            replaceProvider() {bias = 3;}, raw: () => new DataView(bytes.buffer)};
}

for (let round = 0; round < 2; round++) {
    const first = runtime(), other = runtime(), record = first.view('pair', 16);
    assert.equal(record, first.view('pair', 16));
    assert.notEqual(record, other.view('pair', 16));
    assert.deepEqual(Object.keys(record), ['address', 'kind']);
    assert.equal(record.kind, 'pair');
    assert.equal(record[0], record);
    assert.equal(record['01'], record[1]);
    assert.equal(record[1].address, 24);
    record.first = -123;
    record.second = 456;
    record[1].alias = 789;
    assert.equal(first.raw().getInt32(16, true), -123);
    assert.equal(first.raw().getInt32(24, true), 789);
    assert.equal(record.alias, -123);
    first.raw().setInt32(16, 42, true);
    assert.equal(record.first, 42);
    first.grow();
    record.alias = 91;
    assert.equal(first.raw().getInt32(16, true), 91);
    assert.equal(record.second, 456);
    first.replaceProvider();
    assert.equal(record.first, 94);
    record.first = 100;
    assert.equal(first.raw().getInt32(16, true), 97);
    assert.equal(other.view('pair', 16).first, 0);
    assert.equal('missing' in record, false);
    assert.equal(record[Symbol.toPrimitive], undefined);
    assert.equal(record.toString(), '[object Object]');
    assert.equal(Object.prototype.hasOwnProperty.call(record, 'first'), false);
    for (const key of ['missing', '-1', '1.5']) {
        assert.throws(() => record[key], /Unknown test record field pair\./);
        assert.throws(() => {record[key] = 1;}, /Unknown test record field pair\./);
    }
    assert.throws(() => {record[2] = record;}, /Unknown test record field/);
    Object.defineProperty(record, 'user', {value: 9, writable: true});
    assert.equal(record.user, 9);
    record.user = 10;
    assert.equal(record.user, 10);
}
console.log('PASS: record identity, live fields/aliases, pointer indexing, growth, provider replacement, isolation and strict unknown-field contracts.');
