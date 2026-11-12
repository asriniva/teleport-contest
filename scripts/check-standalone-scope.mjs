// Guard production closure, frozen inputs, unchanged ports and generated inputs.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import crypto from 'node:crypto';
import {pathToFileURL} from 'node:url';
const root=process.cwd(),reference=process.env.STANDALONE_REFERENCE_ROOT;
if(!reference)throw new Error('Missing STANDALONE_REFERENCE_ROOT');
const {parse}=await import(pathToFileURL(reference+'/.cache/emsdk/upstream/emscripten/node_modules/acorn/dist/acorn.mjs'));
const read=file=>fs.readFileSync(path.resolve(root,file));
const json=file=>JSON.parse(read(file));
const sha=file=>crypto.createHash('sha256').update(fs.readFileSync(file)).digest('hex');
const check=(file,expected)=>assert.equal(sha(path.resolve(root,file)),expected,'Bound source changed: '+file);
const baseline=json('docs/runtime-environment/scope-baseline.json');
const corrections=json('docs/runtime-environment/authorized-port-corrections.json').corrections;
assert.deepEqual(corrections.map(row=>row.file),['js/ported/vision.js'],'Only the explicitly approved correction is allowed');
for(const row of corrections){assert.equal(baseline.sha256[row.file],row.baselineSha256,'Original correction baseline retained');assert.ok(row.correctedSha256!==row.baselineSha256,'Correction is a real source change');}
const corrected=new Map(corrections.map(row=>[row.file,row.correctedSha256]));
for(const [file,hash]of Object.entries(baseline.sha256))check(file,corrected.get(file)??hash);
for(const name of ['isaac64','terminal','storage'])assert.deepEqual(read('js/'+name+'.js'),read('frozen/'+name+'.js'),'Frozen '+name);
for(const [file,hash]of Object.entries(json('js/standalone/hero-abi.json').sourceSha256))check(file,hash);
for(const [file,hash]of Object.entries(json('js/standalone/display-abi.json').sourceSha256))check(file,hash);
for(const name of ['ball-abi','wizcmds-abi','region-services-abi','detect-abi','bones-services-abi','light-abi','steal-abi','pager-target-abi','dokick-abi','mondata-abi','getpos-abi','makemon-private-abi','wizard-abi','mplayer-abi','minion-abi','dig-abi','explode-abi','spell-abi','rip-abi','special-interactions-abi','teleport-abi','read-abi','mcastu-abi','shknam-abi','apply-abi','lock-abi','scanf-abi','quest-abi','priest-abi','topten-abi','exper-abi','insight-abi','mthrowu-abi','uhitm-abi','vault-abi','color-attributes-abi','mhitm-abi','end-lifecycle-abi','mhitu-abi','dogmove-abi','were-abi','zap-abi','mail-abi','killer-state-abi','artifact-abi','callback-address-abi','restore-lifecycle-abi','potion-abi','eat-abi','timeout-abi','role-transport-abi','unix-platform-abi','hunger-data-abi','descriptions-abi','attribute-abi','worm-abi','report-abi','level-abi','public-functions','trap-abi','vision-abi','window-abi','options-abi','status-abi','hack-abi','persistence-transport-abi','turn-loop-abi','runtime-info-abi','messages-abi','terminal-messages-abi','save-lifecycle-abi','terminal-input-abi','do-lifecycle-abi','equipment-format-abi','quest-pager-abi','equipment-abi','armor-abi','pet-abi','monmove-abi','mon-abi','glyph-abi','command-abi','files-abi','configuration-abi','object-language-abi']){
 const data=json('js/standalone/'+name+'.json');
 for(const [file,hash]of Object.entries(data.sourceSha256))check(file,hash);
 for(const [file,hash]of Object.entries(data.referenceHeaderSha256??{}))assert.equal(sha(path.resolve(reference,file)),hash,'Public declaration header changed: '+file);
}
const records=json('js/standalone/records.json');
check('nethack-c/wasm/compile-defines.json',records.definesSha256);
check('nethack-c/wasm/tu-fragments/decl-schema.json',records.declSchemaSha256);
check('js/standalone/address-ports.json',records.addressMetadataSha256);
for(const [file,hash]of Object.entries(records.supportSourceSha256))check(file,hash);
for(const [file,hash]of Object.entries(records.localHeaderSha256))check(file,hash);
for(const [file,hash]of Object.entries(records.headerSha256))assert.equal(sha(path.resolve(reference,file)),hash,'Measured header changed: '+file);
for(const file of ['decl-storage.json','lua-api.json']){const data=json('js/standalone/'+file);check(data.source,data.sha256);}
for(const [file,hash]of Object.entries(json('js/standalone/terminal-metadata.json').sourceSha256))check(file,hash);
for(const [name,item]of Object.entries(json('js/standalone/address-ports.json').ports)){
    check(`js/ported/${name}-runtime.js`,item.sourceSha256);check(`nethack-c/wasm/tu-fragments/${name}-schema.json`,item.fragmentSha256);
}
const seen=new Set(),forbidden=[];
function collect(file) {
    file=path.resolve(root,file);assert.ok(file.startsWith(root+path.sep),'Production import escapes repository');
    if(seen.has(file))return;seen.add(file);
    if(file.endsWith('.json'))return;
    const ast=parse(fs.readFileSync(file,'utf8'),{ecmaVersion:'latest',sourceType:'module'});
    function visit(node){
        if(!node||typeof node!=='object')return;
        if(['ImportDeclaration','ExportAllDeclaration','ExportNamedDeclaration','ImportExpression'].includes(node.type)&&node.source){
            const source=node.source.value;
            assert.equal(typeof source,'string','Nonliteral standalone import');
            assert.ok(source.startsWith('.'),'Host import in '+file+': '+source);
            assert.ok(!source.endsWith('.wasm'),'Wasm import in '+file);
            collect(path.resolve(path.dirname(file),source));
        }
        if(node.type==='Identifier'&&node.name==='WebAssembly')forbidden.push(path.relative(root,file));
        if((node.type==='CallExpression'||node.type==='NewExpression')&&node.callee.type==='Identifier'&&['eval','Function','fetch','Worker','WebSocket','XMLHttpRequest'].includes(node.callee.name))forbidden.push(path.relative(root,file)+':'+node.callee.name);
        for(const [key,value]of Object.entries(node)){if(['start','end','loc'].includes(key))continue;if(Array.isArray(value))value.forEach(visit);else if(value&&typeof value==='object')visit(value);}
    }
    visit(ast);
}
collect('js/standalone/environment.js');collect('js/standalone/program.js');assert.deepEqual(forbidden,[],'Forbidden production dependency');
const result={baselineCommit:baseline.mainCommit,portPoliciesUnchanged:baseline.policyCount-corrections.length,authorizedPortCorrections:corrections.map(({file,reason})=>({file,reason})),frozenFilesUnchanged:3,productionFiles:seen.size,forbiddenDependencies:forbidden,
    limitation:'Static literal import closure and source/provenance checks; component execution and complete game acceptance are separate gates.'};
fs.mkdirSync('.cache/standalone-validation',{recursive:true});fs.writeFileSync('.cache/standalone-validation/scope.json',JSON.stringify(result,null,2)+'\n');
console.log('PASS: '+JSON.stringify(result));
