// Genuine ordinary-main starvation death: no forced source entries or skips.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import crypto from 'node:crypto';
import {builtinModules} from 'node:module';
const directory=path.resolve(process.env.STANDALONE_FULL_C_REFERENCE??'.cache/full-original-c-v1');
const customFixture=Boolean(process.env.STANDALONE_DEATH_FIXTURE),fixture=path.resolve(process.env.STANDALONE_DEATH_FIXTURE??path.join(directory,'scenarios/death.json')),input=JSON.parse(fs.readFileSync(fixture));
const out=path.resolve(process.env.STANDALONE_DEATH_OUTPUT??'.cache/standalone-death-program');fs.mkdirSync(out,{recursive:true});
const sha=file=>crypto.createHash('sha256').update(fs.readFileSync(file)).digest('hex');
// Snapshot before dynamically importing production modules: imports themselves
// must not race ahead of the source revision which the evidence identifies.
const root=process.cwd(),builtins=new Set(builtinModules),externalImports=new Set();
const entries=['scripts/test-standalone-death-program.mjs','scripts/run-standalone-program.mjs','scripts/full-original-c-run.mjs','scripts/restoration-world-graph.mjs','js/wasm-replay-support.js'];
function productionFiles(){
 const files=new Set();
 const visit=file=>{file=path.resolve(file);if(files.has(file))return;if(!fs.statSync(file).isFile())throw new Error('Expected source file '+file);files.add(file);
  if(!/\.m?js$/.test(file))return;
  const text=fs.readFileSync(file,'utf8'),specifiers=new Set();
  for(const pattern of [/(?:^|[;\n])\s*(?:import|export)\s*[\w${},*\s]+?\s*from\s*['"]([^'"]+)['"]/g,/(?:^|[;\n])\s*import\s*['"]([^'"]+)['"]/g,/\bimport\s*\(\s*['"]([^'"]+)['"]/g])for(const match of text.matchAll(pattern))specifiers.add(match[1]);
  for(const specifier of specifiers){if(specifier.startsWith('.'))visit(path.resolve(path.dirname(file),specifier));else{if(!specifier.startsWith('node:')&&!builtins.has(specifier))throw new Error('Unbound external module '+specifier+' in '+file);externalImports.add(specifier);}}
  // Include literal local data resources in addition to imported JSON modules.
  for(const match of text.matchAll(/new\s+URL\s*\(\s*['"](\.[^'"]+)['"]\s*,\s*import\.meta\.url/g)){const resource=path.resolve(path.dirname(file),match[1]);if(fs.existsSync(resource)&&fs.statSync(resource).isFile())visit(resource);}
 };
 for(const entry of entries)visit(path.join(root,entry));
 return [...files].sort();
}
function assetFiles(dir,files=[]){for(const name of fs.readdirSync(dir)){const file=path.join(dir,name),stat=fs.statSync(file);if(stat.isDirectory())assetFiles(file,files);else if(stat.isFile())files.push(file);}return files.sort();}
const snapshot=()=>({sourceSha256:Object.fromEntries(productionFiles().map(file=>[path.relative(root,file),sha(file)])),assetSha256:Object.fromEntries(assetFiles(directory+'/assets').map(file=>[path.relative(directory+'/assets',file),sha(file)])),referenceReceiptSha256:sha(directory+'/receipt.json'),fixtureSha256:sha(fixture)});
const startProvenance=snapshot(),sealedReceipt=JSON.parse(fs.readFileSync(directory+'/receipt.json'));
const sealedAssets=Object.fromEntries(Object.entries(sealedReceipt.sourceSha256).filter(([file])=>file.includes('/assets/')).map(([file,hash])=>[file.slice(file.lastIndexOf('/assets/')+8),hash]));
assert.deepEqual(startProvenance.assetSha256,sealedAssets,'provided JS asset tree matches sealed C embed inputs');
if(process.env.STANDALONE_DEATH_PROVENANCE_ONLY==='1'){console.log(JSON.stringify({profile:'provenance only; no game comparison',sourceFiles:Object.keys(startProvenance.sourceSha256).length,assetFiles:Object.keys(startProvenance.assetSha256).length,externalImports:[...externalImports].sort()}));process.exit(0);}
const [{runFullOriginalC},{runStandaloneProgram},{worldGraph},{encodeRecorderScreen}]=await Promise.all([import('./full-original-c-run.mjs'),import('./run-standalone-program.mjs'),import('./restoration-world-graph.mjs'),import('../js/wasm-replay-support.js')]);

let cr,jr,checks=0;
const equal=(a,b,label)=>{assert.deepEqual(a,b,label);checks++;};
const reference=await runFullOriginalC(directory,{...input,observeRuntime:r=>{cr=r;}});
const actual=runStandaloneProgram(directory+'/assets',{...input,observeRuntime:r=>{jr=r;}});
for(const[label,result]of [['c',reference],['js',actual]])fs.writeFileSync(path.join(out,'ordinary-death-'+label+'.json'),JSON.stringify(result,null,2)+'\n');
equal(reference.status,{kind:'exited',code:0},'original C ordinary death completes');
assert.ok(reference.state.hp<=0,'fixture reaches ordinary fatal damage');checks++;
equal(actual.status,reference.status,'JS ordinary death completes genuine normal main');
equal(actual.consumed,reference.consumed,'all ordinary death input consumption');
equal(actual.snapshots,reference.snapshots,'all input-boundary scalars and both complete ISAAC states');
equal(actual.state,reference.state,'ordinary death final state');
equal(actual.rngLog,reference.rngLog,'complete ordinary death core RNG log');
equal(actual.displayRngLog,reference.displayRngLog,'complete ordinary death display RNG log');
equal(actual.frames,reference.frames.map(({screen,cursor,animation})=>({screen:encodeRecorderScreen(screen),cursor:[...cursor,1],animation})),'all frozen frames/cursors/animation');
equal(actual.stdout,reference.stdout,'exact raw terminal output');
equal(actual.stderr,reference.stderr,'exact raw terminal errors');
equal(Object.keys(actual.files).sort(),Object.keys(reference.files).sort(),'file paths and source lock removal');
for(const name of ['/nethack/record','/nethack/logfile','/nethack/xlogfile']){
 assert.ok(reference.files[name],name+' original file exists');checks++;
 equal(actual.files[name].bytes,reference.files[name].bytes,'exact score/log file '+name);
}
// Nonempty bones serialization may free objects still referenced by process-exit
// equipment roots. Live restored bones graphs are checked by fresh consumers.
let worlds;
if(!customFixture){
 worlds={c:worldGraph(cr),js:worldGraph(jr)};
 for(const[name,graph]of Object.entries(worlds))fs.writeFileSync(path.join(out,'ordinary-death-'+name+'-world.json'),JSON.stringify(graph,null,2)+'\n');
 equal(worlds.js,worlds.c,'actual post-main named world records and canonical pointer graph');
}
const binaryPersistence=[];
for(const name of Object.keys(reference.files))if(/\/(?:bon[^/]*$|save\/)/.test(name))binaryPersistence.push({path:name,cBytes:Buffer.from(reference.files[name].bytes,'base64').length,jsBytes:Buffer.from(actual.files[name].bytes,'base64').length,byteIdentical:reference.files[name].bytes===actual.files[name].bytes,semanticEquivalenceAccepted:false});
if(process.env.STANDALONE_DEATH_EXPECT_BONES==='1'){assert.ok(binaryPersistence.some(row=>/\/bon[^/]*$/.test(row.path)),'ordinary death produces real bones');checks++;}
const receipt=JSON.parse(fs.readFileSync(path.join(directory,'receipt.json')));
const endProvenance=snapshot();equal(endProvenance,startProvenance,'production source closure, assets, reference receipt and fixture stable at start/end');
const evidence={complete:true,deathRecordingAccepted:true,deathKind:customFixture?'ordinary fixture death':'starvation while fainted',postMainWorldAccepted:!customFixture,postMainWorldLimitation:customFixture?'Post-cleanup pointers are outside this recording proof; no post-exit object/heap graph acceptance. Fresh bones consumers independently compare live restored graphs.':undefined,fullGameAccepted:false,checks,inputBoundaries:actual.snapshots.length,frames:actual.frames.length,rawTerminalBytes:Buffer.from(actual.stdout,'base64').length,moves:actual.state.moves,consumed:actual.consumed,worldCoverage:worlds?.js.coverage??null,binaryPersistence,reference:{receiptSha256:sha(path.join(directory,'receipt.json')),fixtureSha256:sha(fixture),upstream:receipt.upstream,profile:receipt.profile,buildEnvironment:receipt.buildEnvironment,gameTranslationUnits:receipt.gameTranslationUnits,luaTranslationUnits:receipt.luaTranslationUnits,verifiedSourceHashes:Object.keys(receipt.sourceSha256).length,verifiedArtifactHashes:Object.keys(receipt.artifactSha256).length},assemblyProvenanceStable:true,productionProvenance:startProvenance,nodeVersion:process.version,externalImports:[...externalImports].sort(),limitation:customFixture?'Only this literal ordinary-main death recording, score/log text and final scalar/two-RNG state are accepted. Post-exit object graph equivalence is outside this custom-fixture proof. Actual compressed bones/save files are inventoried, with semantic equivalence explicitly unaccepted until cross-fed fresh consumers are proved. Full progression, victory and other death variants remain separate requirements.':'Only this genuine depth1 starvation-while-fainted death, exact main recording, score/log text and selected canonical world graph are accepted. This zero-point fixture has an empty ranking file and creates no bones/save file. Combat-caused deaths, nonempty score ranking, victory/progression, other interactions, arbitrary private/heap state and binary bones/save semantics remain separate requirements.'};
fs.writeFileSync(path.join(out,'evidence.json'),JSON.stringify(evidence,null,2)+'\n');console.log('PASS '+JSON.stringify(evidence));
