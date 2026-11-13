import {Session} from 'node:inspector';
import fs from 'node:fs';
const session=new Session();session.connect();
const parameters={samplingInterval:32768,includeObjectsCollectedByMajorGC:true,includeObjectsCollectedByMinorGC:true};
await new Promise((resolve,reject)=>session.post('HeapProfiler.startSampling',parameters,(error)=>error?reject(error):resolve()));
fs.writeFileSync(process.env.ALLOCATION_PROFILE_OUT+'/sampling.json',JSON.stringify({node:process.version,parameters,started:true,scope:'Diagnostic allocation sampling including collected objects; not a performance or deadline measurement.'},null,2)+'\n');
let stopped=false;
process.on('beforeExit',()=>{if(stopped)return;stopped=true;session.post('HeapProfiler.stopSampling',(error,result)=>{if(error){fs.writeFileSync(process.env.ALLOCATION_PROFILE_OUT+'/error.txt',String(error));process.exitCode=1;}else fs.writeFileSync(process.env.ALLOCATION_PROFILE_OUT+'/profile.json',JSON.stringify(result.profile));session.disconnect();});});
