// Focused dispatch regression, not full-game/native engulf equivalence.
import './pure-js-probes/deny-wasm.mjs';
import assert from 'node:assert/strict';
import fs from 'node:fs';
import {createStandaloneProgram} from '../js/nethack/program.js';
import {withCEnvironment} from '../js/c-runtime/context.js';
import {start_engulf,end_engulf} from '../js/ported/uhitm.js';

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
    let combinations=0;
    for(const invisible of [false,true])for(const digest of [false,true])for(const enfold of [false,true]){
        const events=[],hero={mx:11,my:12,data:{}},target={mx:13,my:14};
        let delays=0;
        const second=()=>{delays++;events.push(['delay','second']);};
        const first=()=>{delays++;events.push(['delay','first']);env.memory.view.setBigUint64(at,env.functions.functionPointer(second,'v'),true);};
        env.memory.view.setBigUint64(at,env.functions.functionPointer(first,'v'),true);
        const displayRng=()=>{throw Error('Glyph conversion must receive, not invoke, the display RNG callback');};
        const context={gy:{youmonst:hero},u:{ux:11,uy:12},digests:data=>{assert.equal(data,hero.data);return digest;},enfolds:data=>{assert.equal(data,hero.data);return enfold;},Invisible:invisible,DISP_ALWAYS:-4,DISP_END:-5,rn2_on_display_rng:displayRng,
            map_location:(...a)=>events.push(['map',...a]),mon_to_glyph:(m,rng)=>{assert.equal(m,hero);assert.equal(rng,displayRng);return 99;},tmp_at:(...a)=>events.push(['tmp',...a]),You:(...a)=>events.push(['message',...a]),mon_nam:m=>{assert.equal(m,target);return 'target';},nh_delay_output:owner.services.nh_delay_output,newsym:(...a)=>events.push(['newsym',...a])};
        withCEnvironment(context,()=>{start_engulf(target);end_engulf();});
        const expected=[];
        if(!invisible)expected.push(['map',11,12,1],['tmp',-4,99],['tmp',13,14]);
        expected.push(['message','%s %s%s!',digest?'swallow':enfold?'enclose':'engulf','target',digest?' whole':''],['delay','first'],['delay','second']);
        if(!invisible)expected.push(['tmp',-5,0],['newsym',11,12]);
        assert.deepEqual(events,expected,'complete engulf ordering '+JSON.stringify({invisible,digest,enfold}));assert.equal(delays,2);combinations++;
    }
    assert.equal(combinations,8);
    console.log(`PASS: ${measuredCallbacks} literal window callback declarations, UHITM live callback replacement and both original start_engulf animation boundaries (synthetic dispatch regression); eight complete start/end branch combinations.`);
} finally {
    env.memory.view.setBigUint64(at,original,true);
}
