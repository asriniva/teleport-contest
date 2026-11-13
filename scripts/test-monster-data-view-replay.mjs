import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import {spawnSync} from 'node:child_process';
import {fileURLToPath} from 'node:url';
import {runStandaloneProgram} from './run-standalone-program.mjs';
const [mode,assets,out,loader]=process.argv.slice(2);
if(mode==='capture'){
 const results=[];
 for(const seed of[1,305419896])for(const keys of['  nled   ','  nm..........']){
  const result=runStandaloneProgram(assets,{seed,timezone:'UTC',options:'OPTIONS=!news\n',keys});
  assert.deepEqual(result.status,{kind:'input-exhausted'});
  results.push(result);
 }
 fs.writeFileSync(out,JSON.stringify(results));
}else{
 if(mode!=='compare'||!assets||!out||!loader)throw Error('Usage: test-monster-data-view-replay.mjs compare <assets> <output-directory> <baseline-loader>');
 fs.mkdirSync(out,{recursive:true});
 for(const name of['baseline','optimized']){
  const run=spawnSync(process.execPath,[...(name==='baseline'?['--import',path.resolve(loader)]:[]),fileURLToPath(import.meta.url),'capture',assets,path.join(out,name+'.json')],{encoding:'utf8'});
  assert.equal(run.status,0,run.stderr);
 }
 const before=JSON.parse(fs.readFileSync(path.join(out,'baseline.json'))),after=JSON.parse(fs.readFileSync(path.join(out,'optimized.json')));
 assert.deepEqual(after,before,'complete replay result before/after');
 console.log(JSON.stringify({status:'PASS',cases:after.length,frames:after.reduce((n,r)=>n+r.frames.length,0),inputBoundaries:after.reduce((n,r)=>n+r.snapshots.length,0),comparison:'entire result including recording frames, raw terminal, world globals, both RNG logs/images, files and process status'}));
}
