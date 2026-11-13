// The wall flag shares a prefix with equipment masks, but has a different C
// type. Exercise the production context, not a substitute fixture provider.
import './pure-js-probes/deny-wasm.mjs';
import fs from 'node:fs';import assert from 'node:assert/strict';
import {createStandaloneProgram} from '../js/nethack/program.js';
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json'));
const {environment:env}=createStandaloneProgram({layouts,readKey(){throw Error('Unexpected input');}});
const context=env.enableMonsterLifecycle(layouts).context;
const declaration=fs.readFileSync('nethack-c/upstream/include/rm.h','utf8').match(/^#define W_NONDIGGABLE (0x[0-9a-f]+)$/m);
assert.ok(declaration,'review changed native wall-flag declaration');
assert.equal(typeof context.W_NONDIGGABLE,'number','native int wall flag must not use the equipment-mask BigInt projection');
assert.equal(context.W_NONDIGGABLE,Number(declaration[1]));
const equipment=Object.keys(layouts.mon).filter(name=>name.startsWith('W_')&&name!=='W_NONDIGGABLE');
assert.equal(equipment.length,7,'review the configured mask cohort');
for(const name of equipment){
 assert.equal(typeof context[name],'bigint',name+' retains its full native mask width');
 assert.equal(context[name],BigInt(layouts.mon[name]));
}
assert.equal(0x08&context.W_NONDIGGABLE,8,'actual packed wall bit operation');
assert.equal(0x04&context.W_NONDIGGABLE,0,'unrelated wall bit');
console.log('PASS: original integer wall constant and full-width equipment masks in the assembled pure-JS MON context; Wasm/network unavailable.');
