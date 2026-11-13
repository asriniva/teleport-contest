// Existing original-C/main-world comparisons, with no recorder drivers/corpus.
import fs from 'node:fs';import path from 'node:path';import crypto from 'node:crypto';import {spawn} from 'node:child_process';import {fileURLToPath} from 'node:url';
import {discoverProductionWorldSuites,expandProductionWorldSuites} from './branch-coverage/production-world-suites.mjs';
const root=fileURLToPath(new URL('../',import.meta.url));
const {suites:available,excluded}=discoverProductionWorldSuites(root),requested=process.argv.slice(2);
for(const name of requested)if(!available.includes(name))throw Error('Unknown or session-dependent suite '+name);
const suites=requested.length?[...new Set(requested)].sort():available;
const cases=expandProductionWorldSuites(suites);
if(!suites.length)throw Error('No production-world suites discovered');
const directory=path.join(root,'.cache/production-world-branches',process.pid+'-'+Date.now());fs.mkdirSync(directory,{recursive:true});
const sha=file=>crypto.createHash('sha256').update(fs.readFileSync(file)).digest('hex');
const env={...process.env,STANDALONE_REFERENCE_ROOT:process.env.STANDALONE_REFERENCE_ROOT??root,NETHACK_BRANCH_REFERENCE_OBSERVERS:'1',NODE_OPTIONS:[
 '--import='+new URL('./branch-coverage/reference-setup.mjs',import.meta.url).href,
 process.env.NODE_OPTIONS,
].filter(Boolean).join(' ')};
const results=[];let cursor=0;
const children=new Set();let stopping=false;
for(const signal of ['SIGTERM','SIGINT'])process.once(signal,()=>{stopping=true;process.exitCode=1;for(const child of children)child.kill('SIGTERM');});
console.log('Running '+cases.length+' original-C / production-JS cases from '+suites.length+' scripts; recorder excluded. Logs: '+directory);
async function worker(){while(!stopping&&cursor<cases.length){
 const {name,variant,args,environment={}}=cases[cursor++],label=name+(variant?':'+variant:''),file=path.join(root,'scripts',name),before=sha(file),log=path.join(directory,name+(variant?'-'+variant:'')+'.log'),output=fs.createWriteStream(log);
 console.log('RUN '+label);
 const status=await new Promise(resolve=>{
  const child=spawn(process.execPath,[file,...args],{cwd:root,env:{...env,...environment}});let timedOut=false;
  children.add(child);
  const timer=setTimeout(()=>{timedOut=true;child.kill('SIGTERM');},1200000);
  child.stdout.on('data',data=>output.write(data));child.stderr.on('data',data=>output.write(data));
  child.once('error',error=>{clearTimeout(timer);resolve({exitStatus:null,error:error.message});});
  child.once('close',(exitStatus,signal)=>{children.delete(child);clearTimeout(timer);resolve({exitStatus,signal,timedOut});});
 });
 await new Promise(resolve=>output.end(resolve));
 const result={name,variant,args,environment,...status,sourceSha256:before,sourceChanged:sha(file)!==before,log};result.passed=status.exitStatus===0&&!result.sourceChanged;
 results.push(result);console.log((result.passed?'PASS ':'FAIL ')+label);
 fs.writeFileSync(path.join(directory,'results.json'),JSON.stringify({recorderRun:false,fullCorpus:requested.length===0,suites,cases,excluded,results},null,2)+'\n');
}}
await Promise.all([worker(),worker()]);
console.log(JSON.stringify({suites:suites.length,cases:cases.length,passed:results.filter(r=>r.passed).length,failed:results.filter(r=>!r.passed).map(r=>({name:r.name,variant:r.variant})),directory,recorderRun:false}));
if(results.some(r=>!r.passed))process.exitCode=1;
