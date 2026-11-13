// Coverage is an explicit acceptance gate; reports never convert gaps into passes.
import {gzipSync} from 'node:zlib';
import fs from 'node:fs';import path from 'node:path';import {fileURLToPath} from 'node:url';import {spawn} from 'node:child_process';
import {inventory,report} from './branch-coverage/report.mjs';
const root=fileURLToPath(new URL('../',import.meta.url)),args=process.argv.slice(2),diagnostic=args.includes('--report-only'),selected=args.filter(a=>!a.startsWith('--'));
for(const argument of args)if(argument.startsWith('--')&&argument!=='--report-only')throw Error('Unknown branch-coverage option '+argument);
const registered=JSON.parse(fs.readFileSync(path.join(root,'nethack-c/wasm/tu-ports.json')));
for(const name of selected)if(!registered.some(port=>port.name===name))throw Error('Unknown subsystem '+name);
const runId=process.pid+'-'+Date.now(),directory=path.join(root,'.cache/engine-branch-coverage',runId),raw=path.join(directory,'raw');fs.mkdirSync(raw,{recursive:true});
const definitions=inventory(root);fs.writeFileSync(path.join(directory,'inventory.json.gz'),gzipSync(JSON.stringify(definitions)));
const env={...process.env,NETHACK_BRANCH_COVERAGE_DIR:raw,NETHACK_BRANCH_REFERENCE_OBSERVERS:'1',NODE_OPTIONS:[process.env.NODE_OPTIONS,'--import='+new URL('./branch-coverage/register.mjs',import.meta.url).href].filter(Boolean).join(' '),DEPENDENCY_TEST_NODE:process.execPath,DEPENDENCY_MEMORY64_NODE:process.execPath};
console.log('Engine branch coverage '+runId+'; '+Object.keys(definitions.files).length+' modules. Recorder excluded.');
const tests=[
 {name:'instrumentation-semantics',command:process.execPath,args:['scripts/test-engine-branch-instrumentation.mjs']},
 {name:'instrumentation-syntax',command:process.execPath,args:['scripts/test-engine-branch-syntax.mjs']},
 {name:'coverage-gate-controls',command:process.execPath,args:['scripts/test-engine-branch-gate.mjs']},
 {name:'closed-parameter-proofs',command:process.execPath,args:['scripts/test-engine-closed-parameters.mjs']},
 {name:'reference-observation-controls',command:process.execPath,args:['scripts/test-engine-reference-observers.mjs']},
 {name:'world-suite-selection-controls',command:process.execPath,args:['scripts/test-engine-world-suite-selection.mjs']},
 {name:'reference-runtime-source-controls',command:process.execPath,args:['scripts/test-engine-reference-runtime-successor.mjs']},
 {name:'test-source-inverse-controls',command:'python3',args:['scripts/test-engine-test-source-successors.py']},
 {name:'service-source-inverse-controls',command:'python3',args:['scripts/test-engine-service-source-successors.py']},
 {name:'production-service-resolution',command:process.execPath,args:['scripts/test-production-service-resolution.mjs']},
 {name:'mon-header-constants',command:process.execPath,args:['scripts/test-mon-header-constants.mjs']},
 {name:'production-abi-rejections',command:process.execPath,args:['scripts/test-engine-abi-rejections.mjs']},
 {name:'measured-callbacks',command:process.execPath,args:['scripts/check-engine-callbacks.mjs']},
 {name:'engulf-production-provider',command:process.execPath,args:['scripts/test-uhitm-delay-callback.mjs']},
 {name:'engulf-branch-matrix',command:process.execPath,args:['scripts/test-engulf-branch-matrix.mjs']},
 {name:'production-window-bindings',command:process.execPath,args:['scripts/test-production-window-bindings.mjs']},
 {name:'uhitm-branch-matrix',command:process.execPath,args:['scripts/test-uhitm-branch-matrix.mjs']},
 {name:'mhitm-branch-matrix',command:process.execPath,args:['scripts/test-mhitm-branch-matrix.mjs']},
 {name:'mhitu-branch-matrix',command:process.execPath,args:['scripts/test-mhitu-branch-matrix.mjs']},
 {name:'trap-branch-matrix',command:process.execPath,args:['scripts/test-trap-branch-matrix.mjs']},
 {name:'small-engine-branches',command:process.execPath,args:['scripts/test-small-engine-branches.mjs']},
 {name:'policy-branch-gaps',command:process.execPath,args:['scripts/test-policy-branch-gaps.mjs']},
 {name:'calendar-branch-gaps',command:process.execPath,args:['scripts/test-calendar-branch-gaps.mjs']},
 {name:'quest-inventory-branches',command:process.execPath,args:['scripts/test-quest-inventory-branches.mjs']},
 {name:'display-branch-matrix',command:process.execPath,args:['scripts/test-display-branch-matrix.mjs']},
 {name:'display-darkroom-branches',command:process.execPath,args:['scripts/test-display-darkroom-branches.mjs']},
 {name:'mon-position-branches',command:process.execPath,args:['scripts/test-mon-position-branches.mjs']},
 {name:'mon-position-production',command:process.execPath,args:['--import',fileURLToPath(new URL('./branch-coverage/reference-setup.mjs',import.meta.url)),'scripts/test-engine-mon-position-production.mjs']},
 ...[[],['--disintegration'],['--poison']].map(args=>({name:'fatal-production-'+(args[0]?.slice(2)??'death-ray'),command:process.execPath,args:['--import',fileURLToPath(new URL('./branch-coverage/reference-setup.mjs',import.meta.url)),'scripts/test-engine-fatal-zap-branches.mjs',...args]})),
 {name:'zap-branch-matrix',command:process.execPath,args:['scripts/test-zap-branch-matrix.mjs']},
 {name:'shop-pricing-branches',command:process.execPath,args:['scripts/test-shop-pricing-branches.mjs']},
 {name:'game-asset-branches',command:process.execPath,args:['scripts/test-game-assets-branches.mjs']},
 {name:'bundled-main-contract',command:process.execPath,args:['--import',fileURLToPath(new URL('./branch-coverage/reference-setup.mjs',import.meta.url)),'scripts/test-standalone-game-assets.mjs']},
 {name:'subsystems',command:process.execPath,args:['scripts/test-native-existing.mjs',...selected]}];
if(!selected.length)tests.push({name:'dependency-contracts',command:'bash',args:['scripts/test-js-dependencies.sh']},{name:'production-cli-and-allocator',command:process.execPath,args:['scripts/test-standalone-allocation-cli.mjs']},{name:'native-assertion-contracts',command:process.execPath,args:['--import',fileURLToPath(new URL('./branch-coverage/reference-setup.mjs',import.meta.url)),'scripts/test-standalone-mon-assert.mjs']},{name:'production-worlds',command:process.execPath,args:['scripts/run-production-world-branches.mjs']});
const results=[];
for(const test of tests){
 console.log('RUN '+test.name);const log=path.join(directory,test.name+'.log'),output=fs.createWriteStream(log);
 const result=await new Promise(resolve=>{const child=spawn(test.command,test.args,{cwd:root,env});child.stdout.on('data',data=>output.write(data));child.stderr.on('data',data=>output.write(data));child.on('error',error=>resolve({exitStatus:null,error:error.message}));child.on('close',(exitStatus,signal)=>resolve({exitStatus,signal}));});
 await new Promise(resolve=>output.end(resolve));results.push({...test,...result,log,passed:result.exitStatus===0});console.log((result.exitStatus===0?'PASS ':'FAIL ')+test.name);
 // Preserve real failures while continuing independent corpus groups.
 fs.writeFileSync(path.join(directory,'execution.json'),JSON.stringify({runId,recorderRun:false,results},null,2)+'\n');
}
// Re-read the current inventory in case test-only instrumentation was improved
// during a diagnostic run. Source SHA checks still reject any engine changes.
const coverage=report(inventory(root),raw);coverage.execution={runId,results,selectedSubsystems:selected,fullCorpus:selected.length===0,allTestsPassed:results.every(r=>r.passed)};coverage.acceptancePassed=coverage.allBranchesCovered&&coverage.allCoverageProcessesPassed&&coverage.execution.allTestsPassed&&coverage.execution.fullCorpus;
fs.writeFileSync(path.join(directory,'report.json.gz'),gzipSync(JSON.stringify(coverage)));
fs.writeFileSync(path.join(root,'.cache/engine-branch-coverage/latest.json'),JSON.stringify({directory,report:path.join(directory,'report.json.gz'),summary:coverage.summary,acceptancePassed:coverage.acceptancePassed},null,2)+'\n');
console.log(JSON.stringify(coverage.summary));console.log('Report: '+path.join(directory,'report.json.gz'));
if(!coverage.acceptancePassed)console.log('NOT COMPLETE: uncovered/unmeasured branches or failed tests remain.');
if(!coverage.execution.allTestsPassed||(!coverage.acceptancePassed&&!diagnostic))process.exitCode=1;
if(diagnostic)console.log('Diagnostic report only; exit status does not establish branch acceptance.');
