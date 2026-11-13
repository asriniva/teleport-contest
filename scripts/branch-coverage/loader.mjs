import fs from 'node:fs';import path from 'node:path';import {fileURLToPath} from 'node:url';
import {instrument} from './instrument.mjs';
const root=fileURLToPath(new URL('../../',import.meta.url));
const codec=new URL('../../js/wasm-replay-support.js',import.meta.url).href,observer='__nethackReferenceObserver';
export async function resolve(specifier,context,next){
 const result=await next(specifier,context);
 if(process.env.NETHACK_BRANCH_REFERENCE_OBSERVERS==='1'&&context.parentURL?.startsWith('file:')&&result.url===codec){
  const parent=path.relative(root,fileURLToPath(context.parentURL));
  if(parent.startsWith('scripts/')){const url=new URL(result.url);url.searchParams.set(observer,'1');return{...result,url:url.href};}
 }
 return result;
}
export function isEngine(file){return /^js\/(?:ported|nethack|c-runtime|lua|platform|libraries|ported-utilities)\/.+\.js$/.test(file)||['js/isaac64.js','js/terminal.js','js/storage.js','js/standalone-recorder-adapter.js','js/wasm-replay-support.js','js/recording-profile.js','js/jsmain.js'].includes(file);}
export async function load(url,context,next){
 if(url.startsWith(codec+'?')&&new URL(url).searchParams.get(observer)==='1'){
  // Test-script imports normalize reference observations. Production imports
  // keep the original module and contribute normal implementation coverage.
  return{format:'module',shortCircuit:true,source:`import * as original from ${JSON.stringify(codec)};
export * from ${JSON.stringify(codec)};
const wrap=fn=>new Proxy(fn,{apply(target,receiver,args){return globalThis.__nethackBranchCoverage.reference(()=>Reflect.apply(target,receiver,args));}});
export const encodeRecorderScreen=wrap(original.encodeRecorderScreen);
export const recordingClockEpoch=wrap(original.recordingClockEpoch);
export const shouldPersistGameFile=wrap(original.shouldPersistGameFile);
`};
 }
 const result=await next(url,context);
 if(result.format!=='module'||!url.startsWith('file:'))return result;
 const file=path.relative(root,fileURLToPath(url));if(!isEngine(file))return result;
 const source=typeof result.source==='string'?result.source:Buffer.from(result.source??fs.readFileSync(fileURLToPath(url))).toString();
 return {...result,source:instrument(source,file).code};
}
