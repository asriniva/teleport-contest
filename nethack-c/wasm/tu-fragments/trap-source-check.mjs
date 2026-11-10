// Actual configured-source/body/literal guards, independent of game selection.
import assert from 'node:assert/strict';
import {readFileSync} from 'node:fs';
import {resolve} from 'node:path';
import {createHash} from 'node:crypto';
import {spawnSync} from 'node:child_process';
import {trapSchema} from '../../../js/ported/trap.js';
const digest=v=>createHash('sha256').update(v).digest('hex');
const comments=s=>s.match(/\/\*[\s\S]*?\*\//g)??[];
export function checkTrapSource({preprocess=true}={}) {
    const root=process.cwd(),prefix='nethack-c/wasm/tu-fragments/';
    const schema=JSON.parse(readFileSync(prefix+'trap-schema.json','utf8'));
    assert.deepEqual(trapSchema,schema,'TRAP source data/schema export');
    const source=readFileSync('.cache/wasm64-build/tree/src/trap.c','utf8');
    const upstream=readFileSync('nethack-c/upstream/src/trap.c','utf8');
    assert.equal(digest(source),schema.source,'Prepared TRAP source changed');
    assert.equal(digest(upstream),'1f6af30bbd0b75a2e4c043098355c1f4eff2a841de27aecdc9f47343d4d5402c','Pristine TRAP source changed');
    const core=readFileSync('js/ported/trap.js','utf8');
    const functions=[...core.matchAll(/export function (\w+)\(([^)]*)\)/g)];
    assert.deepEqual(functions.map(m=>({name:m[1],parameters:m[2].split(',').map(v=>v.trim()).filter(Boolean)})),schema.functions.map(f=>({name:f.name,parameters:f.parameters.map(p=>p.name)})),'Original function names/order/formals');
    assert.equal(functions.length,124);assert.deepEqual(comments(core),comments(source),'Original block-comment order/multiplicity');
    const own=new Set(schema.functions.map(f=>f.name));
    assert(!schema.callSites.some(s=>own.has(s.name)),'No native TRAP policy fallback through foreign-call sites');
    assert.equal(Object.keys(schema.data).length,19);
    for(const label of ['uglovecheck','mglovecheck','roll'])assert(core.includes(label+'_dispatch: while (true)'),label+' native goto target');
    assert(core.includes('burn_stuff_scope: {'),'Native forward lava target');
    assert(!readFileSync(prefix+'trap-support.c','utf8').includes('src/trap.c'),'Native support must not include source policy');
    if (preprocess) {
        const defines=JSON.parse(readFileSync('nethack-c/wasm/compile-defines.json','utf8'));
        const args=['-O2','-g','-I../include',...defines.map(x=>'-D'+x),'-sMEMORY64=1','-I'+resolve('.cache/ncurses-wasm64-build/include'),'-include',resolve('nethack-c/wasm/native-terminal.h'),'-E','trap.c'];
        const cpp=spawnSync(resolve('.cache/emsdk/upstream/emscripten/emcc'),args,{cwd:resolve('.cache/wasm64-build/tree/src'),encoding:'utf8',maxBuffer:32*1024*1024});
        assert.equal(cpp.status,0,cpp.stderr);
        let owner;const body=[];
        for(const line of cpp.stdout.replace(/\n$/,'').split(/\n/)){const marker=/^# \d+ "([^"]+)"/.exec(line);if(marker){owner=marker[1];continue;}if(owner==='trap.c')body.push(line);}
        const active=body.join('\n')+'\n';
        assert.equal(digest(active),schema.profile.bodySha256,'Actual active TRAP branch bodies/macros changed');
        assert.deepEqual(active.match(/"(?:\\.|[^"\\])*"/g)??[],schema.profile.stringTokens,'Actual active TRAP strings changed');
    }
    return {functions:124,comments:comments(source).length,dataObjects:19,source:schema.source,configuredBodiesChecked:preprocess};
}
if (process.argv[1]?.endsWith('trap-source-check.mjs')) console.log(JSON.stringify(checkTrapSource()));
