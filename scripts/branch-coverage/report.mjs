import {gzipSync,gunzipSync} from 'node:zlib';
import fs from 'node:fs';import path from 'node:path';import crypto from 'node:crypto';
import {instrument,version} from './instrument.mjs';import {isEngine} from './loader.mjs';
export function inventory(root=process.cwd()){
 const files={};function walk(dir){for(const row of fs.readdirSync(path.join(root,dir),{withFileTypes:true})){const p=path.posix.join(dir,row.name);if(row.isDirectory())walk(p);else if(isEngine(p)){const source=fs.readFileSync(path.join(root,p),'utf8');files[p]={sourceSha256:crypto.createHash('sha256').update(source).digest('hex'),sites:instrument(source,p).sites};}}}walk('js');return{version,files};
}
export function report(inventory,rawDirectory){
 const hits={},witnesses={},tests=new Set(),processes=[];
 for(const name of fs.readdirSync(rawDirectory).filter(n=>n.endsWith('.json.gz')).sort()){const raw=JSON.parse(gunzipSync(fs.readFileSync(path.join(rawDirectory,name))));if(raw.referenceProcess)throw Error('Reference process included');tests.add(raw.test);processes.push({record:name,test:raw.test,testSourceSha256:raw.testSourceSha256??null,testSourceChanged:raw.testSourceChanged??false,exitStatus:raw.exitStatus??null});if(raw.testSourceChanged||(raw.exitStatus!==undefined&&raw.exitStatus!==0))continue;
 const witness=raw.exitStatus===0?{record:name,test:raw.test,testArguments:raw.testArguments??null,testSourceSha256:raw.testSourceSha256??null}:null;
 const observe=(file,id,arm)=>{if(witness){const rows=witnesses[file]??=[];(rows[id]??=[])[arm]??=witness;}};
 for(const[file,row]of Object.entries(raw.files)){
  const definition=inventory.files[file];if(!definition)throw Error('Uninventoried engine file '+file);if(row.sourceSha256!==definition.sourceSha256)throw Error('Coverage source drift '+file);
  const indexes=new Map(definition.sites.map(s=>[s.key,s.id])),target=hits[file]??=[];for(const[oldId,arms]of row.counts.entries())if(arms){const i=indexes.get(row.siteKeys[oldId]);if(i===undefined)throw Error('Unknown coverage site '+file+':'+row.siteKeys[oldId]);for(const[a,n]of arms.entries())if(n){(target[i]??=[])[a]=(target[i]?.[a]??0)+n;observe(file,i,a);}}
  if(row.defaultTracking){
   const oldIndexes=new Map(row.siteKeys.map((key,id)=>[key,id]));
   for(const site of definition.sites)if(site.parameterEntryKey){
    // Each completed call reached this parameter. Defaults in calls which
    // later throw can only LOWER this bound; they cannot create false hits.
    const entered=row.counts[oldIndexes.get(site.parameterEntryKey)]?.[0]??0;
    const defaults=row.counts[oldIndexes.get(site.key)]?.[0]??0;
    const provided=Math.max(0,entered-defaults);
    if(provided){(target[site.id]??=[])[1]=(target[site.id]?.[1]??0)+provided;observe(file,site.id,1);}
   }
  }
  if(row.completions){
   const oldIndexes=new Map(row.siteKeys.map((key,id)=>[key,id]));
   for(const site of definition.sites)if(site.localCompletion){
    const oldId=oldIndexes.get(site.key),provided=Math.max(0,(row.completions[oldId]??0)-(row.counts[oldId]?.[0]??0));
    if(provided){(target[site.id]??=[])[1]=(target[site.id]?.[1]??0)+provided;observe(file,site.id,1);}
   }
  }
 }}
 const summary={files:Object.keys(inventory.files).length,tests:tests.size,reachableArms:0,coveredArms:0,uncoveredArms:0,provenConstantArms:0,provenClosedParameterArms:0,unmeasuredArms:0,functionEntries:0,enteredFunctions:0};const files={};
 for(const[file,definition]of Object.entries(inventory.files)){
  const rows=[];
  for(const site of definition.sites){if(site.kind==='function-entry'){summary.functionEntries++;if(hits[file]?.[site.id]?.[0])summary.enteredFunctions++;}
   for(const[arm,label]of site.arms.entries()){
    const count=hits[file]?.[site.id]?.[arm]??0,unreachable=site.unreachableProof||(site.constantArm!==undefined&&arm!==site.constantArm);
    let status;if(unreachable){if(count)throw Error('Constant-arm proof contradicted '+file+':'+site.line);if(site.unreachableProofKind==='closed-parameter'||site.constantProofKind==='closed-parameter'){summary.provenClosedParameterArms++;status='unreachable-closed-parameter';}else{summary.provenConstantArms++;status='unreachable-literal';}}
    else{summary.reachableArms++;if(!site.measured||site.measuredArms?.[arm]===false){summary.unmeasuredArms++;summary.uncoveredArms++;status='unmeasured';}else if(count){summary.coveredArms++;status='covered';}else{summary.uncoveredArms++;status='uncovered';}}
    rows.push({...site,arm,label,count,status,witness:witnesses[file]?.[site.id]?.[arm]??null});
   }
  }
  files[file]={sourceSha256:definition.sourceSha256,arms:rows};
 }
 return{version,summary,tests:[...tests].sort(),processes,allCoverageProcessesPassed:processes.length>0&&processes.every(p=>p.exitStatus===0&&!p.testSourceChanged),allBranchesCovered:summary.uncoveredArms===0,referenceProcessesExcluded:true,recorderRun:false,files,limitations:['Coverage measures execution, not correctness; assertions and original-C comparisons remain required.','Unsupported binding contexts, async iteration and super/private optional calls or logical assignments remain failing gaps if introduced.','Switch case-body entry includes fallthrough; implicit no-match has a separate outcome.','Unreachable proofs cover literal conditions and private closed-parameter predicates with validated call sites.','Legacy records without an exit status are diagnostic evidence and cannot establish passing-process acceptance.']};
}
if(process.argv[1]===new URL(import.meta.url).pathname){const[raw,out]=process.argv.slice(2);if(!raw||!out)throw Error('Usage: report.mjs RAW_DIRECTORY OUTPUT.json');const result=report(inventory(),raw);fs.writeFileSync(out,gzipSync(JSON.stringify(result)));console.log(JSON.stringify(result.summary));if(!result.allBranchesCovered||!result.allCoverageProcessesPassed)process.exitCode=1;}
