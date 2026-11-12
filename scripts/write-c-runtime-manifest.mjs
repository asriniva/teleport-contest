// Bind this cleanup's source closure without rewriting historical oracle pins.
import {migrationFiles,qualifiedHistorical} from './pure-js-fixtures/qualification.mjs';
import fs from 'node:fs';
import {currentSourcePath} from './services-layout-audit.mjs';
import crypto from 'node:crypto';
const roots=['js/c-runtime','js/nethack'];
const wrappers=['address-ports','c-types','functions','libc','memory-services','record-views'];
const paths=[...roots.flatMap(root=>fs.readdirSync(root).filter(file=>/\.(js|json)$/.test(file)).map(file=>root+'/'+file)),
    ...wrappers.map(name=>'js/standalone/'+name+'.js'),
    'js/standalone/environment.js','js/standalone/object-state.js',
    ...fs.readdirSync('js/standalone').filter(file=>file.endsWith('.json')).map(file=>'js/standalone/'+file),
    'nethack-c/wasm/tu-ports.json','nethack-c/wasm/tu-fragments/unixunix-reviewed-makefile.py',
    ...JSON.parse(fs.readFileSync('docs/runtime-environment/c-runtime-helper-extraction.json')).files.map(row=>currentSourcePath(row.file)),
    'docs/runtime-environment/c-runtime-helper-extraction.json','docs/runtime-environment/c-runtime-shim-pruning.json','docs/runtime-environment/c-runtime-provenance-update.json',
    'scripts/extract-c-runtime-helpers.mjs','scripts/c-runtime-compiled-input.mjs','scripts/test-tu-topl.mjs','scripts/prune-c-runtime-shims.mjs','scripts/update-c-runtime-provenance.py','scripts/test-c-runtime-makefile-provenance.py','scripts/test-c-runtime-adapter-memory.mjs','scripts/check-c-runtime-extraction.mjs',
    'scripts/export-standalone-scanf-abi.py','scripts/export-standalone-were-abi.py',
    'scripts/write-c-runtime-manifest.mjs','scripts/check-c-runtime-boundaries.mjs','scripts/check-c-runtime-relocation.mjs','scripts/check-standalone-special-interactions.mjs','docs/runtime-environment/authorized-port-corrections.json',
    'scripts/test-c-runtime-memory.mjs','scripts/test-c-runtime-contracts.mjs','scripts/test-standalone.mjs','scripts/test-standalone-scanf.mjs','scripts/check-standalone-scope.mjs',
    ...['test-js-game-files','test-js-runtime-regex','test-js-time','test-js-runtime'].map(name=>'scripts/'+name+'.mjs'),
    ...['heap','stdlib','time','vfs','float-format'].map(name=>'js/c-runtime/'+name+'.js')];
for(const file of ['scripts/check-sdk-runtime-extension.mjs','docs/runtime-environment/c-runtime-sdk-extension.json','docs/runtime-environment/c-runtime-sdk-extension.patch','docs/runtime-environment/sdk-boundary-evidence.json','docs/runtime-environment/c-runtime-metadata-successors.json','scripts/check-c-runtime-mkobj-address.py','scripts/test-c-runtime-mkobj-address-qualification.py','docs/runtime-environment/c-runtime-mkobj-address-extension.json','docs/runtime-environment/c-runtime-mkobj-address-extension.patch','docs/runtime-environment/mkobj-address-evidence.json'])if(fs.existsSync(file))paths.push(file);
// Exact later boundary corrections are qualified separately from historical cleanup.
for(const file of ['scripts/services-layout-audit.mjs','scripts/services_layout_audit.py','scripts/relocate-runtime-layout.py','scripts/services_layout_successors.py','scripts/test-services-layout-successors.py','docs/runtime-environment/services-layout-successors.json','docs/runtime-environment/recorder-boundary-correction-evidence.json'])if(fs.existsSync(file))paths.push(file);
const successorPatches='docs/runtime-environment/services-layout-successors';
if(fs.existsSync(successorPatches))for(const file of fs.readdirSync(successorPatches).filter(name=>name.endsWith('.patch')))paths.push(successorPatches+'/'+file);
for(const file of ['build-stairs-pager-native-queries.py','test-standalone-pager-arrow-native.mjs','test-standalone-pager-arrow-component.mjs','test-standalone-public-knight-stairs.mjs','test-standalone-knight-stairs-native-prefix.mjs'])paths.push('scripts/'+file);
const boundaryEvidence='docs/runtime-environment/recorder-boundary-evidence';
if(fs.existsSync(boundaryEvidence))for(const file of fs.readdirSync(boundaryEvidence).filter(name=>name.endsWith('.json')))paths.push(boundaryEvidence+'/'+file);
// A separate finite current feature proof precedes, and never replaces, the
// original cleanup and six-source native correction qualifications.
for(const file of ['scripts/post_default_successors.py','scripts/test-post-default-successors.py','scripts/test-current-audit-guards.py','docs/runtime-environment/post-default-source-successors.json','docs/runtime-environment/post-default-native-evidence.json'])if(fs.existsSync(file))paths.push(file);
const postDefaultPatches='docs/runtime-environment/post-default-source-successors';
if(fs.existsSync(postDefaultPatches))for(const file of fs.readdirSync(postDefaultPatches).filter(name=>name.endsWith('.patch')))paths.push(postDefaultPatches+'/'+file);
const postDefaultProof='docs/runtime-environment/post-default-native-evidence.json';
if(fs.existsSync(postDefaultProof))paths.push(...Object.keys(JSON.parse(fs.readFileSync(postDefaultProof)).rawProofs??{}));
// The MONMOVE correction has its own exact two-file proof, preserving earlier cohorts.
for(const file of ['scripts/monmove_source_successors.py','scripts/test-monmove-source-successors.py','scripts/test-standalone-monmove-private.mjs','scripts/standalone-monmove-private-probe.c','scripts/build-standalone-monmove-private.py','docs/runtime-environment/monmove-source-successors.json','docs/runtime-environment/monmove-native-evidence.json'])if(fs.existsSync(file))paths.push(file);
const monmovePatches='docs/runtime-environment/monmove-source-successors';
if(fs.existsSync(monmovePatches))for(const file of fs.readdirSync(monmovePatches).filter(name=>name.endsWith('.patch')))paths.push(monmovePatches+'/'+file);
const monmoveProof='docs/runtime-environment/monmove-native-evidence.json';
if(fs.existsSync(monmoveProof))paths.push(...Object.keys(JSON.parse(fs.readFileSync(monmoveProof)).rawProofs??{}));
// Shared window-header aliases have an independent exact native/source cohort.
for(const file of ['scripts/window_headers_source_successors.py','scripts/test-window-headers-source-successors.py','scripts/test-standalone-status-editor.mjs','scripts/fixtures/standalone-status-editor.json','docs/runtime-environment/window-headers-source-successors.json','docs/runtime-environment/window-headers-native-evidence.json'])if(fs.existsSync(file))paths.push(file);
const windowHeaderPatches='docs/runtime-environment/window-headers-source-successors';
if(fs.existsSync(windowHeaderPatches))for(const file of fs.readdirSync(windowHeaderPatches).filter(name=>name.endsWith('.patch')))paths.push(windowHeaderPatches+'/'+file);
const windowHeaderProof='docs/runtime-environment/window-headers-native-evidence.json';
if(fs.existsSync(windowHeaderProof))paths.push(...Object.keys(JSON.parse(fs.readFileSync(windowHeaderProof)).rawProofs??{}));
// Exact allocator/header qualification with independent native comparison evidence.
for(const file of ['scripts/allocation_cli_source_successors.py','scripts/test-allocation-cli-source-successors.py','scripts/test-allocation-cli-layered-audits.py','scripts/test-standalone-allocation-cli.mjs','docs/runtime-environment/allocation-cli-source-successors.json','docs/runtime-environment/allocation-cli-native-evidence.json'])if(fs.existsSync(file))paths.push(file);
const allocationCliPatches='docs/runtime-environment/allocation-cli-source-successors';
if(fs.existsSync(allocationCliPatches))for(const file of fs.readdirSync(allocationCliPatches).filter(name=>name.endsWith('.patch')))paths.push(allocationCliPatches+'/'+file);
const allocationCliProof='docs/runtime-environment/allocation-cli-native-evidence.json';
if(fs.existsSync(allocationCliProof))paths.push(...Object.keys(JSON.parse(fs.readFileSync(allocationCliProof)).rawProofs??{}));
// Exact natural SOUNDS callback integration proof.
paths.push('js/standalone/game-windows.js','scripts/sounds_source_successors.py','scripts/test-sounds-source-successors.py','scripts/test-standalone-sounds-main.mjs','scripts/author-standalone-ordinary-progression.mjs','scripts/fixtures/standalone-sounds-main.json','docs/runtime-environment/sounds-native-evidence.json','docs/runtime-environment/sounds-source-successors.json','docs/runtime-environment/sounds-source-successors/game-windows.patch',...Object.keys(JSON.parse(fs.readFileSync('docs/runtime-environment/sounds-native-evidence.json')).rawProofs));
// Exact type-access performance qualification, preserving measured ABI pins.
paths.push('scripts/type_access_source_successors.py','scripts/test-type-access-source-successors.py','docs/runtime-environment/type-access-native-evidence.json','docs/runtime-environment/type-access-source-successors.json','docs/runtime-environment/type-access-source-successors/types.js.patch','docs/runtime-environment/type-access-source-successors/record-views.js.patch',...Object.keys(JSON.parse(fs.readFileSync('docs/runtime-environment/type-access-native-evidence.json')).rawProofs));
// Exact buffered stdio byte-I/O performance qualification.
paths.push('scripts/pure-js-fixtures/qualification.mjs','scripts/stdio_byte_source_successors.py','scripts/test-stdio-byte-source-successors.py','scripts/test-standalone-stdio-byte-io.mjs','docs/runtime-environment/stdio-byte-native-evidence.json','docs/runtime-environment/stdio-byte-source-successors.json','docs/runtime-environment/stdio-byte-source-successors/stdio.js.patch',...Object.keys(JSON.parse(fs.readFileSync('docs/runtime-environment/stdio-byte-native-evidence.json')).rawProofs));
const sha256=Object.fromEntries([...new Set(paths)].sort().map(file=>[file,crypto.createHash('sha256').update(fs.readFileSync(file)).digest('hex')]));
const data={baselineCommit:'df33dd4',integrationBaseCommit:'8cf4880d8cf7fb9104635f068564a5de87523fe7',scope:'Common-runtime cleanup source closure; not game or native equivalence acceptance',sha256};
const file='docs/runtime-environment/c-runtime-manifest.json',text=JSON.stringify(data,null,2)+'\n';
if(process.argv.includes('--check')){
    const recorded=JSON.parse(fs.readFileSync(file));
    for(const [path,hash]of Object.entries(recorded.sha256)){if(sha256[path]!==hash)qualifiedHistorical(path,hash);}
    for(const path of Object.keys(sha256))if(!(path in recorded.sha256)){if(!migrationFiles.has(path))throw Error('Unreviewed new runtime source '+path);qualifiedHistorical(path);}
    console.log('PASS: '+Object.keys(sha256).length+' cleanup/runtime source hashes.');
}else{fs.writeFileSync(file,text);console.log('Bound '+Object.keys(sha256).length+' cleanup/runtime source hashes.');}
