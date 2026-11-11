// Audit mechanical moves against the committed pre-cleanup source. This is a
// development check; no git/host dependency enters the production runtime.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import crypto from 'node:crypto';
import {execFileSync} from 'node:child_process';
import {pathToFileURL} from 'node:url';
const baseline='df33dd4',reference=process.env.STANDALONE_REFERENCE_ROOT;
if(!reference)throw new Error('Missing STANDALONE_REFERENCE_ROOT');
const {parse}=await import(pathToFileURL(reference+'/.cache/emsdk/upstream/emscripten/node_modules/acorn/dist/acorn.mjs'));
const old=file=>execFileSync('git',['show',baseline+':'+file],{encoding:'utf8'});
const read=file=>fs.readFileSync(file,'utf8');
const body=(source,name)=>{
    const ast=parse(source,{ecmaVersion:'latest',sourceType:'module'});
    for(const node of ast.body){const declaration=node.declaration??node;if(declaration.type==='FunctionDeclaration'&&declaration.id.name===name)return source.slice(declaration.body.start,declaration.body.end);}
    throw new Error('Missing factory '+name);
};
assert.equal(body(read('js/nethack/runtime.js'),'createJsRuntime'),body(old('js/ported/js-runtime.js'),'createJsRuntime'),'Changed NetHack runtime provider');
const moves=[['functions','createFunctions'],['bitfields','createBitfields'],['stdio','createStdio'],['qsort','muslQsort'],['scanf','scanFormatted'],['environment-inputs','createEnvironmentInputs']];
for(const [file,name]of moves)assert.equal(body(read('js/c-runtime/'+file+'.js'),name),body(old('js/standalone/'+file+'.js'),name),'Changed moved factory '+name);
assert.equal(body(read('js/c-runtime/libc.js'),'createStandaloneLibc'),body(old('js/standalone/libc.js'),'createStandaloneLibc').replace('        // Match the configured SDK single-process syscall profile.\n        getpid:()=>42,\n',''));
const oldTypes=body(old('js/standalone/c-types.js'),'createCTypes').replace(/    const aliases=.*;\n/,'');
assert.equal(body(read('js/c-runtime/types.js'),'createCTypes'),oldTypes,'Changed type engine beyond injected aliases');
for(const name of ['scanf-abi','were-abi']) {
    const before=JSON.parse(old('js/standalone/'+name+'.json')),after=JSON.parse(read('js/standalone/'+name+'.json'));
    delete before.sourceSha256;delete after.sourceSha256;
    assert.deepEqual(after,before,'Changed measured declarations beyond source relocation '+name);
}
// All translated policies and frozen inputs retain the established baseline.
const sha=file=>crypto.createHash('sha256').update(fs.readFileSync(file)).digest('hex');
const policies=JSON.parse(read('docs/runtime-environment/scope-baseline.json'));
for(const [file,expected]of Object.entries(policies.sha256))assert.equal(sha(file),expected,'Changed policy '+file);
for(const name of ['isaac64','terminal','storage'])assert.equal(read('js/'+name+'.js'),read('frozen/'+name+'.js'));
console.log('PASS: 9 relocated factory bodies mechanically preserved (platform getpid and typedef declarations explicitly separated); '+Object.keys(policies.sha256).length+' baseline inputs and 3 frozen files unchanged.');
