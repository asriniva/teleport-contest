import {gzipSync} from 'node:zlib';
import fs from 'node:fs';import path from 'node:path';import crypto from 'node:crypto';
const directory=process.env.NETHACK_BRANCH_COVERAGE_DIR;
if(!directory)throw Error('Missing NETHACK_BRANCH_COVERAGE_DIR');
const test=process.argv[1],testHash=()=>test&&fs.existsSync(test)?crypto.createHash('sha256').update(fs.readFileSync(test)).digest('hex'):null;
const testSourceSha256=testHash();
const testArguments=process.argv.slice(2);
const reference=process.argv[1]?.endsWith('/pure-js-fixtures/reference-worker.mjs');
const {createCollector}=await import('./collector.mjs');
const runtime=createCollector({enabled:!reference}),files=runtime.files;
Object.defineProperty(globalThis,'__nethackBranchCoverage',{value:runtime,configurable:true});
process.once('exit',exitStatus=>{
 if(reference||!files.size)return;fs.mkdirSync(directory,{recursive:true});
 const testSourceChanged=testHash()!==testSourceSha256;
 const result={version:1,pid:process.pid,test,testArguments,testSourceSha256,testSourceChanged,exitStatus,referenceProcess:false,referenceObserverExclusion:process.env.NETHACK_BRANCH_REFERENCE_OBSERVERS==='1',files:Object.fromEntries(files)};
 fs.writeFileSync(path.join(directory,process.pid+'-'+crypto.randomBytes(6).toString('hex')+'.json.gz'),gzipSync(JSON.stringify(result)));
});
