// Bind this cleanup's source closure without rewriting historical oracle pins.
import fs from 'node:fs';
import crypto from 'node:crypto';
const roots=['js/c-runtime','js/nethack'];
const wrappers=['address-ports','c-types','functions','libc','memory-services','record-views'];
const paths=[...roots.flatMap(root=>fs.readdirSync(root).filter(file=>/\.(js|json)$/.test(file)).map(file=>root+'/'+file)),
    ...wrappers.map(name=>'js/standalone/'+name+'.js'),
    'js/standalone/environment.js','js/standalone/object-state.js',
    ...fs.readdirSync('js/standalone').filter(file=>file.endsWith('.json')).map(file=>'js/standalone/'+file),
    'nethack-c/wasm/tu-ports.json','nethack-c/wasm/tu-fragments/unixunix-reviewed-makefile.py',
    ...JSON.parse(fs.readFileSync('docs/runtime-environment/c-runtime-helper-extraction.json')).files.map(row=>row.file),
    'docs/runtime-environment/c-runtime-helper-extraction.json','docs/runtime-environment/c-runtime-shim-pruning.json','docs/runtime-environment/c-runtime-provenance-update.json',
    'scripts/extract-c-runtime-helpers.mjs','scripts/c-runtime-compiled-input.mjs','scripts/test-tu-topl.mjs','scripts/prune-c-runtime-shims.mjs','scripts/update-c-runtime-provenance.py','scripts/test-c-runtime-makefile-provenance.py','scripts/test-c-runtime-adapter-memory.mjs','scripts/check-c-runtime-extraction.mjs',
    'scripts/export-standalone-scanf-abi.py','scripts/export-standalone-were-abi.py',
    'scripts/write-c-runtime-manifest.mjs','scripts/check-c-runtime-boundaries.mjs','scripts/check-c-runtime-relocation.mjs','scripts/check-standalone-special-interactions.mjs','docs/runtime-environment/authorized-port-corrections.json',
    'scripts/test-c-runtime-memory.mjs','scripts/test-c-runtime-contracts.mjs','scripts/test-standalone.mjs','scripts/test-standalone-scanf.mjs','scripts/check-standalone-scope.mjs',
    ...['test-js-game-files','test-js-runtime-regex','test-js-time','test-js-runtime'].map(name=>'scripts/'+name+'.mjs'),
    ...['c-memory','c-stdlib','c-time','c-vfs','c-float-format'].map(name=>'js/services/'+name+'.js')];
const sha256=Object.fromEntries([...new Set(paths)].sort().map(file=>[file,crypto.createHash('sha256').update(fs.readFileSync(file)).digest('hex')]));
const data={baselineCommit:'df33dd4',integrationBaseCommit:'8cf4880d8cf7fb9104635f068564a5de87523fe7',scope:'Common-runtime cleanup source closure; not game or native equivalence acceptance',sha256};
const file='docs/runtime-environment/c-runtime-manifest.json',text=JSON.stringify(data,null,2)+'\n';
if(process.argv.includes('--check')){
    if(fs.readFileSync(file,'utf8')!==text)throw new Error('Runtime cleanup source manifest differs; inspect actual changes before regenerating');
    console.log('PASS: '+Object.keys(sha256).length+' cleanup/runtime source hashes.');
}else{fs.writeFileSync(file,text);console.log('Bound '+Object.keys(sha256).length+' cleanup/runtime source hashes.');}
