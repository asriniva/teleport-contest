// Bind this cleanup's source closure without rewriting historical oracle pins.
import fs from 'node:fs';
import crypto from 'node:crypto';
const roots=['js/c-runtime','js/nethack'];
const wrappers=['address-ports','bitfields','c-types','environment-inputs','functions','libc','memory-services','qsort','record-views','scanf','stdio'];
const paths=[...roots.flatMap(root=>fs.readdirSync(root).filter(file=>/\.(js|json)$/.test(file)).map(file=>root+'/'+file)),
    ...wrappers.map(name=>'js/standalone/'+name+'.js'),
    'js/standalone/environment.js','js/ported/js-runtime.js','js/standalone/scanf-abi.json','js/standalone/were-abi.json',
    'scripts/export-standalone-scanf-abi.py','scripts/export-standalone-were-abi.py',
    'scripts/write-c-runtime-manifest.mjs','scripts/check-c-runtime-boundaries.mjs','scripts/check-c-runtime-relocation.mjs',
    'scripts/test-c-runtime-memory.mjs','scripts/test-c-runtime-contracts.mjs','scripts/test-standalone.mjs',
    ...['c-memory','c-stdlib','c-time','c-vfs','c-float-format'].map(name=>'js/services/'+name+'.js')];
const sha256=Object.fromEntries([...new Set(paths)].sort().map(file=>[file,crypto.createHash('sha256').update(fs.readFileSync(file)).digest('hex')]));
const data={baselineCommit:'df33dd4',scope:'Common-runtime cleanup source closure; not game or native equivalence acceptance',sha256};
const file='docs/runtime-environment/c-runtime-manifest.json',text=JSON.stringify(data,null,2)+'\n';
if(process.argv.includes('--check')){
    if(fs.readFileSync(file,'utf8')!==text)throw new Error('Runtime cleanup source manifest differs; inspect actual changes before regenerating');
    console.log('PASS: '+Object.keys(sha256).length+' cleanup/runtime source hashes.');
}else{fs.writeFileSync(file,text);console.log('Bound '+Object.keys(sha256).length+' cleanup/runtime source hashes.');}
