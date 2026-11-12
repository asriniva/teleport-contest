// Publish a completed subsystem receipt only from a fully successful real run.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import crypto from 'node:crypto';
import {migrationFiles,qualifiedHistorical} from './qualification.mjs';
const reportFile=process.argv[2];assert.ok(reportFile,'Pass the completed results.json path');
const reportFiles=process.argv.slice(2),inputs=reportFiles.map(file=>({file,bytes:fs.readFileSync(file)}));
const original=JSON.parse(inputs[0].bytes);assert.equal(original.registrySuites,138);assert.equal(original.selectedSuites,138);assert.equal(original.results.length,138);
const attempts=inputs.map(({file,bytes})=>({file,report:JSON.parse(bytes)}));
const rows=new Map(original.results.map(row=>[row.name,row]));
for(const {report:retry}of attempts.slice(1)){
 assert.equal(retry.recorderRun,false);
 for(const row of retry.results){assert.ok(rows.has(row.name));rows.set(row.name,row);}
}
const results=[...rows.values()];
for(const row of results){assert.equal(row.passed,true,row.name);assert.equal(row.completed,true,row.name);assert.equal(row.exitStatus,0,row.name);assert.ok(row.assertions>0,row.name);assert.equal(row.assertionFailures,0,row.name);assert.equal(row.implementation,'pure-javascript');}
assert.equal(results.length,138);assert.equal(new Set(results.map(r=>r.name)).size,138);
const report={...original,results,passed:138,failed:0,completed:138,assertionFailures:0,assertions:results.reduce((n,r)=>n+r.assertions,0),subsystemCohortPassed:true,validationMode:inputs.length===1?'single-full-cohort':'full-cohort-with-targeted-reruns',runReceipts:inputs.map(({file,bytes},i)=>({report:file,sha256:crypto.createHash('sha256').update(bytes).digest('hex'),runId:attempts[i].report.runId,selectedSuites:attempts[i].report.selectedSuites,passed:attempts[i].report.passed,failed:attempts[i].report.failed})),supersededAttempts:attempts.flatMap(({file,report:attempt})=>attempt.results.filter(row=>!row.passed&&rows.get(row.name)!==row).map(row=>({...row,attemptReport:file})))};
assert.equal(report.implementationCounts.pureJavaScript,138);assert.equal(report.implementationCounts.mixedEngineDiagnostics,0);assert.equal(report.recorderRun,false);
const bytes=inputs[0].bytes;
assert.deepEqual(report.results.find(r=>r.name==='botl').nodeArguments,['--jitless']);
const sha=b=>crypto.createHash('sha256').update(b).digest('hex'),digest=file=>sha(fs.readFileSync(file));
const relative=file=>path.relative(process.cwd(),path.resolve(file));
const sourceSha256={};
for(const file of migrationFiles)if(fs.existsSync(file))sourceSha256[file]=digest(file);
for(const row of report.results)sourceSha256['scripts/test-tu-'+row.name+'.mjs']=digest('scripts/test-tu-'+row.name+'.mjs');
for(const dir of ['scripts/pure-js-probes','scripts/pure-js-fixtures'])for(const name of fs.readdirSync(dir))if(/\.(?:mjs|py)$/.test(name))sourceSha256[dir+'/'+name]=digest(dir+'/'+name);
for(const file of ['scripts/test-native-existing.mjs','scripts/native-test-backend.mjs','scripts/native-test-assert.mjs','scripts/test-pure-js-tu.sh','scripts/build-pure-js-probes.py'])sourceSha256[file]=digest(file);
for(const file of Object.keys(JSON.parse(fs.readFileSync('docs/runtime-environment/pure-js-source-changes.json')).files))qualifiedHistorical(file);
const migration=JSON.parse(fs.readFileSync('docs/runtime-environment/pure-js-test-migration.json'));
let generated=0,handwritten=0;const fixtures={};
for(const suite of migration.suites){
 if(suite.fixture==='handwritten-js-setup'){handwritten++;continue;}
 const file='.cache/pure-js-fixtures/'+suite.name+'/manifest.json',manifest=JSON.parse(fs.readFileSync(file));generated++;
 assert.deepEqual(manifest.gameTranslationUnitsCompiled,[]);assert.equal(manifest.runtimeWasmRequired,false);
 assert.equal(manifest.builderSha256,digest('scripts/pure-js-fixtures/build.py'));
 for(const [p,h]of Object.entries(manifest.sourceSha256)){assert.equal(digest(p),h,p);assert.ok(!(p.endsWith('.c')&&(p.startsWith('nethack-c/upstream/')||p.startsWith('.cache/wasm64-build/tree/'))),'Engine/library C compiled into IUT: '+p);}
 for(const [p,h]of Object.entries(manifest.outputSha256))assert.equal(digest(path.dirname(file)+'/'+p),h,p);
 fixtures[suite.name]={manifest:file,sha256:digest(file)};
}
assert.equal(generated,120);assert.equal(handwritten,18);
const extras=[
 ['wasmIsolation','isolation-final.log','Pure-JS probe isolation:'],
 ['bindingContracts','bindings-final.log','672 total contracts'],
 ['sharedRuntimeContracts','c-runtime-final.log','PASS: shared typed records'],
 ['dependencySuite','dependencies-final.log','61 production dependency modules'],
 ['lexicalScope','lexical-final.log','Lexical scope check passed: 138'],
 ['sourceStructure','structure-final.log','nhlsel: original function inventory/order/parameters and all block comments preserved'],
 ['standaloneScope','standalone-scope-final3.log','"forbiddenDependencies":[]'],
 ['runtimeManifest','manifest-final.log','PASS:'],
 ['generatedSelection','nhlsel-generated-final.log','640 original-C/shared-JS scenarios'],
 ['selectionNegativeControl','nhlsel-negative-final.log','PASS: injected coordinate error rejected'],
 ['dispatcherWitness','mkobj-witness-final.log','MKOBJ dispatcher witnesses PASS'],
 ['sourceQualificationNegativeControls','qualification-controls-final.log','PASS: exact source qualification'],
 ['luaIO','lua-io-final.log','comparisons passed'],
 ['allocationSourceControls','allocation-source-controls.log','PASS 25 synthetic'],
 ['allocationLayeredAuditControls','allocation-audit-controls.log','PASS 77 real layered'],
 ['postDefaultControls','post-default-controls-final.log','PASS post-default qualification'],
 ['currentAuditGuards','audit-guards-final.log','PASS 9 synthetic'],
 ['referenceCacheControls','reference-cache-controls.log','PASS: original-C getter caching'],
].map(([name,log,marker])=>{const file='.cache/pure-js-fixtures/'+log,text=fs.readFileSync(file,'utf8');assert.ok(text.includes(marker),'Missing completed extra check: '+name);return{name,status:'passed',log:file,sha256:digest(file)};});
const referenceBuildsFile='.cache/pure-js-fixtures/reference-builds.json',referenceBuilds=JSON.parse(fs.readFileSync(referenceBuildsFile));
for(const name of ['cmd','options','uhitm','termcap','wintty'])for(const group of ['inputs','outputs'])for(const [file,hash]of Object.entries(referenceBuilds[name][group]))assert.equal(digest(file),hash,name+': '+file);
const integrationFile='.cache/pure-js-fixtures/main-integration-changes.json';
const mainIntegration=fs.existsSync(integrationFile)?JSON.parse(fs.readFileSync(integrationFile)):undefined;
const result={...report,mainIntegration,suites:138,failures:0,completeMigration:true,recorderRun:false,pureJsReadinessEstablished:false,completedAt:new Date().toISOString(),node:process.version,report:relative(reportFile),reportSha256:sha(bytes),fixtureCounts:{handwrittenJavaScript:handwritten,loweredFixtureAndAbiOnly:generated},fixtureManifests:fixtures,referenceBuilds:{receipt:referenceBuildsFile,sha256:digest(referenceBuildsFile)},sourceSha256,extraChecks:extras,results:report.results.map(row=>({...row,log:relative(row.log)})),limitations:['Controlled subsystem corpus; complete game readiness remains unproven.','The 44 recorder sessions were not run.','BOTL uses --jitless for its large lowered test fixture; production JIT performance is not qualified.','Existing upstream NHLSEL unary-alias use-after-free remains outside the defined-behavior corpus.']};
fs.writeFileSync('docs/runtime-environment/pure-js-test-validation.json',JSON.stringify(result,null,2)+'\n');
console.log('Recorded 138/138 successful pure-JS subsystem suites, '+report.assertions+' assertions; recorder not run.');
