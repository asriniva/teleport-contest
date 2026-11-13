import assert from 'node:assert/strict';
import fs from 'node:fs';
import os from 'node:os';
import path from 'node:path';
import vm from 'node:vm';
import {gzipSync} from 'node:zlib';
import {instrument} from './branch-coverage/instrument.mjs';
import {createCollector} from './branch-coverage/collector.mjs';
import {report} from './branch-coverage/report.mjs';

// Synthetic negative controls for acceptance itself, independent of engine hits.
const directory=fs.mkdtempSync(path.join(os.tmpdir(),'nethack-branch-gate-'));
let checks=0;
function fixture(source,args){
 const file='js/ported/example.js',runtime=createCollector(),transformed=instrument(source,file);
 const run=vm.runInNewContext(transformed.code+';run',{__nethackBranchCoverage:runtime});
 for(const input of args)run(...input);
 const row=runtime.files.get(file);
 return {definitions:{version:1,files:{[file]:{sourceSha256:row.sourceSha256,sites:transformed.sites}}},raw:{version:1,test:'synthetic-acceptance-control',exitStatus:0,referenceProcess:false,files:{[file]:row}},file};
}
function evaluate(example){
 fs.writeFileSync(path.join(directory,'control.json.gz'),gzipSync(JSON.stringify(example.raw)));
 return report(example.definitions,directory);
}
try{
 const partial=fixture('function run(v){if(v)return 1;return 2;}',[[true]]);
 assert.equal(evaluate(partial).allBranchesCovered,false);checks++;
 const complete=fixture('function run(v){if(v)return 1;return 2;}',[[true],[false]]);
 assert.equal(evaluate(complete).allBranchesCovered,true);checks++;
 assert.equal(evaluate(complete).allCoverageProcessesPassed,true);checks++;
 assert.ok(evaluate(complete).files[complete.file].arms.every(arm=>arm.witness?.test==='synthetic-acceptance-control'));checks++;
 const failed=structuredClone(complete);failed.raw.exitStatus=1;
 assert.equal(evaluate(failed).allBranchesCovered,false);checks++;
 assert.equal(evaluate(failed).allCoverageProcessesPassed,false);checks++;
 assert.ok(evaluate(failed).files[failed.file].arms.every(arm=>arm.witness===null));checks++;
 const legacy=structuredClone(complete);delete legacy.raw.exitStatus;
 assert.equal(evaluate(legacy).allCoverageProcessesPassed,false);checks++;
 assert.ok(evaluate(legacy).files[legacy.file].arms.every(arm=>arm.witness===null));checks++;
 const testDrift=structuredClone(complete);testDrift.raw.testSourceChanged=true;
 assert.equal(evaluate(testDrift).allBranchesCovered,false);checks++;
 assert.equal(evaluate(testDrift).allCoverageProcessesPassed,false);checks++;
 const unloaded=structuredClone(complete);
 unloaded.definitions.files['js/ported/unloaded.js']=structuredClone(unloaded.definitions.files[unloaded.file]);
 assert.equal(evaluate(unloaded).allBranchesCovered,false);checks++;
 const constant=fixture('function run(){if(true)return 1;return 2;}',[[]]);
 assert.equal(evaluate(constant).summary.provenConstantArms,1);checks++;
 const contradicted=structuredClone(constant),decision=contradicted.definitions.files[contradicted.file].sites.find(s=>s.kind==='if');
 contradicted.raw.files[contradicted.file].counts[decision.id]=[1,1];
 assert.throws(()=>evaluate(contradicted),/proof contradicted/);checks++;
 const unsupported=fixture('function run(v){for(let {x=3}=v;false;){}return 1;}',[[{}],[{x:4}]]);
 const site=unsupported.definitions.files[unsupported.file].sites.find(s=>s.kind==='default-value');
 unsupported.raw.files[unsupported.file].counts[site.id]=[1,1];
 assert.equal(evaluate(unsupported).allBranchesCovered,false);checks++;
 assert.equal(evaluate(unsupported).summary.unmeasuredArms,1);checks++;
 const defaults=fixture('function run(v=3){return v;}',[[],[4]]);
 assert.equal(evaluate(defaults).allBranchesCovered,true);checks++;
 const onlyDefault=fixture('function run(v=3){return v;}',[[],[]]);
 assert.equal(evaluate(onlyDefault).allBranchesCovered,false);checks++;
 const aborted=fixture('function fail(){throw Error("parameter");}function f(a=2,b=fail()){return a+b;}function run(){try{f();}catch{}return f(3,4);}',[[]]);
 const abortedReport=evaluate(aborted),aDefault=abortedReport.files[aborted.file].arms.filter(s=>s.kind==='default-value'&&s.parameterEntryKey);
 assert.ok(aDefault.some(s=>s.arm===1&&s.count===0),'aborted default calls must not manufacture supplied-argument hits');checks++;
 const legacyDefaults=structuredClone(onlyDefault);delete legacyDefaults.raw.files[legacyDefaults.file].defaultTracking;
 assert.equal(evaluate(legacyDefaults).allBranchesCovered,false);checks++;
 const nestedInitializer=fixture('let b;function run(a=({b=3}={})){return a;}',[[7]]);
 const nestedSites=nestedInitializer.definitions.files[nestedInitializer.file].sites.filter(s=>s.kind==='default-value');
 assert.equal(nestedSites.filter(s=>s.parameterEntryKey).length,1,'defaults inside an initializer are not parameters');checks++;
 assert.equal(evaluate(nestedInitializer).allBranchesCovered,false);checks++;
 const local=fixture('function run(v){const {x=3}=v;return x;}',[[{}],[{x:4}]]);
 assert.equal(evaluate(local).allBranchesCovered,true);checks++;
 const localDefault=fixture('function run(v){const {x=3}=v;return x;}',[[{}],[{}]]);
 assert.equal(evaluate(localDefault).allBranchesCovered,false);checks++;
 const member=fixture('function run(v){v.x??=3;return v.x;}',[[{x:null}],[{x:4}]]);
 assert.equal(evaluate(member).allBranchesCovered,true);checks++;
 const enumeration=fixture('function run(v){let n=0;for(const k in v)n++;return n;}',[[{}],[{x:1}]]);
 assert.equal(evaluate(enumeration).allBranchesCovered,true);checks++;
 const nonempty=fixture('function run(v){let n=0;for(const k in v)n++;return n;}',[[{x:1}]]);
 assert.equal(evaluate(nonempty).allBranchesCovered,false);checks++;
 const enumerationError=fixture('function run(){try{for(const k in new Proxy({},{ownKeys(){throw Error("enumeration");}}))return k;}catch{}}',[[]]);
 const iteratorSite=enumerationError.definitions.files[enumerationError.file].sites.find(s=>s.kind==='iterator-loop');
 assert.ok(!enumerationError.raw.files[enumerationError.file].counts[iteratorSite.id]?.[1],'enumeration exceptions cannot count as empty iteration');checks++;
 const closed=fixture('function helper(sk){if(!sk)return 1;else{do{}while(sk);}}function run(){return helper(0);}',[[]]);
 assert.equal(evaluate(closed).allBranchesCovered,true);checks++;
 assert.equal(evaluate(closed).summary.provenClosedParameterArms,3);checks++;
 const contradictedClosed=structuredClone(closed),dead=contradictedClosed.definitions.files[closed.file].sites.find(s=>s.unreachableProof);
 contradictedClosed.raw.files[closed.file].counts[dead.id]=[1,0];
 assert.throws(()=>evaluate(contradictedClosed),/proof contradicted/);checks++;
 for(const [change,message]of [
  [x=>x.raw.referenceProcess=true,/Reference process included/],
  [x=>x.raw.files[x.file].sourceSha256='changed',/source drift/],
  [x=>x.raw.files[x.file].siteKeys=x.raw.files[x.file].siteKeys.map(()=> 'invalid:0:1'),/Unknown coverage site/],
  [x=>x.definitions.files={},/Uninventoried engine file/],
 ]){const example=structuredClone(complete);change(example);assert.throws(()=>evaluate(example),message);checks++;}
 console.log('PASS: '+checks+' coverage-gate controls reject gaps, unsupported constructs, reference contamination, source drift and unknown sites.');
}finally{fs.rmSync(directory,{recursive:true,force:true});}
