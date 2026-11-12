// Focused dispatch regression, not full-game/native engulf equivalence.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import {createStandaloneProgram} from '../js/nethack/program.js';
import {withCEnvironment} from '../js/c-runtime/context.js';
import {start_engulf} from '../js/ported/uhitm.js';

const layouts=JSON.parse(fs.readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url)));
const records=JSON.parse(fs.readFileSync(new URL('../js/nethack/records.json',import.meta.url))).records;
const adapters=new URL('../js/nethack/',import.meta.url);
let measuredCallbacks=0;
for(const file of fs.readdirSync(adapters).filter(name=>name.endsWith('.js'))) {
    const source=fs.readFileSync(new URL(file,adapters),'utf8');
    for(const match of source.matchAll(/\bwindow\(['"](win_\w+)['"]/g)) {
        assert.ok(Object.hasOwn(records.window_procs.fields,match[1]),file+': unknown window callback '+match[1]);
        measuredCallbacks++;
    }
}
const {environment:env}=createStandaloneProgram({layouts,readKey(){throw Error('Unexpected input');}});
const owner=env.enableUhitm(layouts);
const at=env.ctypes.locate('struct window_procs',env.requireGlobal('windowprocs'),'win_delay_output').at;
const original=env.memory.view.getBigUint64(at,true);
const calls=[];
const install=label=>env.memory.view.setBigUint64(at,env.functions.functionPointer(()=>calls.push(label),'v'),true);
try {
    install('first');
    owner.services.nh_delay_output();
    install('second');
    owner.services.nh_delay_output();
    assert.deepEqual(calls,['first','second'],'dispatch reads the current active window callback');
    const messages=[];
    withCEnvironment({
        gy:{youmonst:{data:{}}},digests:()=>true,enfolds:()=>false,Invisible:true,
        You:(...args)=>messages.push(args),mon_nam:()=> 'target',
        nh_delay_output:owner.services.nh_delay_output,
    },()=>start_engulf({}));
    assert.deepEqual(calls,['first','second','second','second'],'original start_engulf dispatches both animation boundaries');
    assert.deepEqual(messages,[['%s %s%s!','swallow','target',' whole']]);
    console.log(`PASS: ${measuredCallbacks} literal window callback declarations, UHITM live callback replacement and both original start_engulf animation boundaries (synthetic dispatch regression).`);
} finally {
    env.memory.view.setBigUint64(at,original,true);
}
