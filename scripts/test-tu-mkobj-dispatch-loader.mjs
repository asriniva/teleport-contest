// Redirect only the frozen suite's dispatcher hook; preserve every oracle check.
import assert from 'node:assert/strict';
import {readFile} from 'node:fs/promises';

const target=new URL('./test-tu-mkobj.mjs',import.meta.url).href;
const dispatcher=new URL('../js/ported/mkobj-dispatch.js',import.meta.url).href;
const environment=new URL('../js/c-runtime/context.js',import.meta.url).href;
const witness=new URL('./test-tu-mkobj-dispatch-witness.mjs',import.meta.url).href;

export async function load(url,context,nextLoad) {
    if(url!==target)return nextLoad(url,context);
    let source=await readFile(new URL(url),'utf8');
    const hooks=source.split('\n').filter(line=>line.startsWith('const runtime={mkobj('));
    assert.equal(hooks.length,1,'one original MKOBJ fixture dispatcher');
    assert.ok(hooks[0].includes('createMkobjEnvironment(services,L,core)'));
    const hook=`const seen=new WeakMap(),nativeOverrides=new WeakMap();
const runtime={mkobj(services,name,...args){const extra=nativeOverrides.get(services.moduleKey);if(extra)services=Object.assign(Object.create(services),extra);seen.set(services.moduleKey,services);envs.set(services.moduleKey,getMkobjEnvironment(services,L));return callMkobj(services,L,name,...args);}};`;
    source=source.replace(hooks[0],hook);
    const end='assert.equal(called.size,99);';
    assert.equal(source.split(end).length,2);
    source=source.replace(end,'await verifyMkobjDispatch({hybrid,reference,hf,runtime,schema,L,envs,seen,nativeOverrides,pool,index,field,C,R,T,callMkobj,getMkobjEnvironment});\n'+end);
    source='import {callMkobj,getMkobjEnvironment} from '+JSON.stringify(dispatcher)+';\n'
        +'import {R,T} from '+JSON.stringify(environment)+';\n'
        +'import {verifyMkobjDispatch} from '+JSON.stringify(witness)+';\n'+source;
    return {format:'module',source,shortCircuit:true};
}
