import {runHistoricalCli as runPriorLayoutAudit} from './nethack-layout.mjs';
if(runPriorLayoutAudit(import.meta.url))process.exit(0);
// Audit mechanical moves against the committed pre-cleanup source. This is a
// development check; no git/host dependency enters the production runtime.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import {readBeforeLayout} from './services-layout-audit.mjs';
import crypto from 'node:crypto';
import {execFileSync} from 'node:child_process';
import {pathToFileURL} from 'node:url';
import {sdkRuntimeExtensionBaseline} from './check-sdk-runtime-extension.mjs';
const baseline='df33dd4',reference=process.env.STANDALONE_REFERENCE_ROOT;
if(!reference)throw new Error('Missing STANDALONE_REFERENCE_ROOT');
const {parse}=await import(pathToFileURL(reference+'/.cache/emsdk/upstream/emscripten/node_modules/acorn/dist/acorn.mjs'));
const old=file=>execFileSync('git',['show',baseline+':'+file],{encoding:'utf8'});
const read=file=>readBeforeLayout(file,'utf8');
const body=(source,name)=>{
    const ast=parse(source,{ecmaVersion:'latest',sourceType:'module'});
    for(const node of ast.body){const declaration=node.declaration??node;if(declaration.type==='FunctionDeclaration'&&declaration.id.name===name)return source.slice(declaration.body.start,declaration.body.end);}
    throw new Error('Missing factory '+name);
};
assert.equal(body(read('js/nethack/runtime.js'),'createJsRuntime'),body(old('js/ported/js-runtime.js'),'createJsRuntime'),'Changed NetHack runtime provider');
const moves=[['functions','createFunctions'],['bitfields','createBitfields'],['stdio','createStdio'],['qsort','muslQsort'],['scanf','scanFormatted'],['environment-inputs','createEnvironmentInputs']];
const sdkBaseline=sdkRuntimeExtensionBaseline();
for(const [file,name]of moves)assert.equal(body(file==='stdio'&&sdkBaseline!==null?sdkBaseline:read('js/c-runtime/'+file+'.js'),name),body(old('js/nethack/'+file+'.js'),name),'Changed moved factory '+name);
assert.equal(body(read('js/c-runtime/libc.js'),'createStandaloneLibc'),body(old('js/nethack/libc.js'),'createStandaloneLibc').replace('        // Match the configured SDK single-process syscall profile.\n        getpid:()=>42,\n',''));
const oldTypes=body(old('js/nethack/c-types.js'),'createCTypes').replace(/    const aliases=.*;\n/,'');
assert.equal(body(read('js/c-runtime/types.js'),'createCTypes'),oldTypes,'Changed type engine beyond injected aliases');
for(const name of ['scanf-abi','were-abi']) {
    const before=JSON.parse(old('js/nethack/'+name+'.json')),after=JSON.parse(read('js/nethack/'+name+'.json'));
    delete before.sourceSha256;delete after.sourceSha256;
    assert.deepEqual(after,before,'Changed measured declarations beyond source relocation '+name);
}
// All translated policies and frozen inputs retain the established baseline.
const sha=file=>crypto.createHash('sha256').update(readBeforeLayout(file)).digest('hex');
const policies=JSON.parse(read('docs/runtime-environment/scope-baseline.json'));
// Preserve main's explicitly approved VISION exception without refreshing the
// immutable policy baseline or accepting additional correction declarations.
// Only this fixed current-manifest declaration is needed here. The current
// manifest's complete hashes are independently checked by its writer/source gate.
const integrationBase=JSON.parse(fs.readFileSync('docs/runtime-environment/c-runtime-manifest.json','utf8')).integrationBaseCommit;
assert.equal(integrationBase,'8cf4880d8cf7fb9104635f068564a5de87523fe7','Changed runtime integration base');
const correctionFile='docs/runtime-environment/authorized-port-corrections.json';
assert.equal(read(correctionFile),execFileSync('git',['show',integrationBase+':'+correctionFile],{encoding:'utf8'}),'Changed main-approved correction declaration');
const {corrections}=JSON.parse(read(correctionFile));
assert.deepEqual(corrections.map(row=>row.file),['js/ported/vision.js']);
for(const row of corrections)assert.equal(policies.sha256[row.file],row.baselineSha256);
const corrected=new Map(corrections.map(row=>[row.file,row.correctedSha256]));
for(const [file,expected]of Object.entries(policies.sha256))assert.equal(sha(file),corrected.get(file)??expected,'Changed policy '+file);
for(const name of ['isaac64','terminal','storage'])assert.equal(read('js/'+name+'.js'),read('frozen/'+name+'.js'));
console.log('PASS: 9 original relocated factory bodies preserved through qualified historical projection; current stdio SDK feature delta separately bound when declared (platform getpid and typedef declarations explicitly separated); '+Object.keys(policies.sha256).length+' baseline inputs checked, including main\'s exact approved VISION correction; 3 frozen files unchanged.');
