// Actual configured-source/body/literal guards, independent of game selection.
import assert from 'node:assert/strict';
import {readFileSync} from 'node:fs';
import {resolve} from 'node:path';
import {createHash} from 'node:crypto';
import {spawnSync} from 'node:child_process';
import {nhluaSchema} from '../../../js/ported/nhlua.js';
const digest=v=>createHash('sha256').update(v).digest('hex');
const comments=s=>s.match(/\/\*[\s\S]*?\*\//g)??[];
export function checkNhluaSource({preprocess=true}={}) {
    const root=process.cwd(),prefix='nethack-c/wasm/tu-fragments/';
    const schema=JSON.parse(readFileSync(prefix+'nhlua-schema.json','utf8'));
    assert.deepEqual(nhluaSchema,schema,'NHLUA source data/schema export');
    const source=readFileSync('.cache/wasm64-build/tree/src/nhlua.c','utf8');
    const upstream=readFileSync('nethack-c/upstream/src/nhlua.c','utf8');
    assert.equal(digest(source),schema.source,'Prepared NHLUA source changed');
    assert.equal(digest(upstream),'cf161f30beb1147102cb9a137997acea715bdec9d7b16dc44082518d5ec257e1','Pristine NHLUA source changed');
    const core=readFileSync('js/ported/nhlua.js','utf8');
    const functions=[...core.matchAll(/export function (\w+)\(([^)]*)\)/g)];
    assert.deepEqual(functions.map(m=>({name:m[1],parameters:m[2].split(',').map(v=>v.trim()).filter(Boolean)})),schema.functions.map(f=>({name:f.name,parameters:f.parameters.map(p=>p.name)})),'Original function names/order/formals');
    assert.equal(functions.length,94);
    // The inherited seed patch replaced one pristine comment. Preserve it as
    // history without mixing it into the exact configured286-comment sequence.
    const historical=comments(upstream).filter(comment=>!comments(source).includes(comment));
    assert.equal(historical.length,1,'Exact pristine-only inherited comment inventory');
    assert(historical[0].includes('XXX Note that math.random'));
    const appendix="\n// Historical pristine comment replaced by inherited 001-deterministic-runtime.patch.\n// Retained outside the configured source bodies; seeded prepared policy above is authoritative.\n"+historical[0]+'\n';
    assert(core.endsWith(appendix),'Exact historical pristine-comment appendix');
    const configuredCore=core.slice(0,-appendix.length);
    assert.equal(digest(configuredCore),'478ce9cbbddfd0a9bcdab88d6d38eeccd90597ac16b5a3199ffc48933cbcdbee','Frozen policy/data before additive historical comment');
    assert.deepEqual(comments(configuredCore),comments(source),'Original configured block-comment order/multiplicity');
    const own=new Set(schema.functions.map(f=>f.name));
    assert(!schema.callSites.some(s=>own.has(s.name)),'No native NHLUA policy fallback through foreign-call sites');
    assert.equal(Object.keys(schema.data).length,27);
    assert.equal((core.match(/C\.setjmpBooleanScope\(/g)??[]).length,1,'One approved localized native jump continuation');
    assert(!readFileSync(prefix+'nhlua-support.c','utf8').includes('src/nhlua.c'),'Native support must not include source policy');
    if (preprocess) {
        const defines=JSON.parse(readFileSync('nethack-c/wasm/compile-defines.json','utf8'));
        const args=['-O2','-g','-I../include',...defines.map(x=>'-D'+x),'-sMEMORY64=1','-I'+resolve('.cache/ncurses-wasm64-build/include'),'-include',resolve('nethack-c/wasm/native-terminal.h'),'-E','nhlua.c'];
        const cpp=spawnSync(resolve('.cache/emsdk/upstream/emscripten/emcc'),args,{cwd:resolve('.cache/wasm64-build/tree/src'),encoding:'utf8',maxBuffer:32*1024*1024});
        assert.equal(cpp.status,0,cpp.stderr);
        let owner;const body=[];
        for(const line of cpp.stdout.replace(/\n$/,'').split(/\n/)){const marker=/^# \d+ "([^"]+)"/.exec(line);if(marker){owner=marker[1];continue;}if(owner==='nhlua.c')body.push(line);}
        const active=body.join('\n')+'\n';
        assert.equal(digest(active),schema.profile.bodySha256,'Actual active NHLUA branch bodies/macros changed');
        assert.deepEqual(active.match(/"(?:\\.|[^"\\])*"/g)??[],schema.profile.stringTokens,'Actual active NHLUA strings changed');
    }
    return {functions:94,comments:comments(source).length,dataObjects:27,source:schema.source,configuredBodiesChecked:preprocess};
}
if (process.argv[1]?.endsWith('nhlua-source-check.mjs')) console.log(JSON.stringify(checkNhluaSource()));
