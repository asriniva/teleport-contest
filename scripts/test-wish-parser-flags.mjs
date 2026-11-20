import assert from 'node:assert/strict';
import {createStandaloneProgram} from '../js/nethack/program.js';
import {callObjnam} from '../js/nethack/bindings/objnam.js';
import layouts from '../js/wasm/tu-layouts.json' with {type: 'json'};

const {environment} = createStandaloneProgram({layouts, readKey() { throw Error('Unexpected prompt'); }});
const naming = environment.startModule('japanese-item-names').environment;
const layout = layouts.objnam;
const {memory, services} = environment;
const data = memory.calloc(1, layout.struct__readobjnam_data_size);
const flagAddress = data + layout.struct__readobjnam_data_flags;

for (const [text, expected] of [['looted sink', 1], ['grave', 0], ['disturbed grave', 1]]) {
    memory.view.setInt32(flagAddress, 99, true);
    callObjnam(naming, layout, 'readobjnam_init', services.literal(text), data);
    assert.equal(memory.view.getInt32(flagAddress, true), 0, 'clear flags when starting ' + text);
    callObjnam(naming, layout, 'readobjnam_preparse', data);
    assert.equal(memory.view.getInt32(flagAddress, true), expected, 'flags after parsing ' + text);
}
