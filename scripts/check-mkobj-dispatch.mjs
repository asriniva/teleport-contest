// Guard ABI categories against the compiler-derived original source schema.
import assert from 'node:assert/strict';
import {readFile} from 'node:fs/promises';
import {wideArguments,pointerReturns} from '../js/ported/mkobj-dispatch-data.js';

const schema=JSON.parse(await readFile(new URL('../nethack-c/wasm/tu-fragments/mkobj-schema.json',import.meta.url),'utf8'));
const expected={};
for(const [name,parameters] of Object.entries(schema.sourceParameters)) {
    const wide={};
    parameters.forEach((parameter,index)=>{
        if(['long','unsigned long'].includes(parameter.canonical))wide[index]=parameter.canonical;
    });
    if(Object.keys(wide).length)expected[name]=wide;
}
assert.deepEqual(wideArguments,expected);
assert.deepEqual([...pointerReturns],Object.entries(schema.sourceReturns).filter(([,type])=>type.includes('*')).map(([name])=>name));
console.log('MKOBJ dispatcher ABI categories match all99 compiler-derived signatures.');
