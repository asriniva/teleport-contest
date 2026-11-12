// Complete reference process: inputs/observation only, no translated owners.
import fs from 'node:fs';import path from 'node:path';import crypto from 'node:crypto';import {pathToFileURL} from 'node:url';
const digest=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex');
export async function runFullOriginalC(directory,input={}){
 directory=path.resolve(directory);const receipt=JSON.parse(fs.readFileSync(path.join(directory,'receipt.json')));
 if(receipt.gameTranslationUnits!==140||receipt.luaTranslationUnits!==32||receipt.abortBoundaries.length||receipt.syntheticGameGlobals.length||receipt.portedTranslationUnits.length)throw new Error('Not a complete original-C reference');
 for(const [p,h]of Object.entries(receipt.sourceSha256))if(digest(p)!==h)throw new Error('Changed original-C reference input '+p);
 for(const [p,h]of Object.entries(receipt.artifactSha256))if(digest(path.join(directory,p))!==h)throw new Error('Changed original-C reference artifact '+p);
 const {default:factory}=await import(pathToFileURL(path.join(directory,'out/game.mjs')));
 const profile={NETHACKDIR:'/nethack',HACKDIR:'/nethack',HOME:'/home/player',USER:'root',LOGNAME:'root',MAIL:'/nethack/mailbox',TERM:'xterm-256color',TERMINFO:'/nethack/terminfo',LINES:'24',COLUMNS:'80',TZ:input.timezone??process.env.TZ??Intl.DateTimeFormat().resolvedOptions().timeZone,NETHACK_NO_DELAY:'1',NOMUX_MARKERS:'1',NETHACK_RAW_KEYS:'1',NETHACK_SEED:String(input.seed??1),NETHACK_FIXED_DATETIME:input.datetime??'20260102030405',NETHACK_RECORDING_EPOCH:String(input.clockEpoch??1777723200),NETHACK_RNGLOG:'/rng.log',NETHACK_RNGLOG_DISP:'/rng-display.log',...input.environment};
 const keys=input.keys??'',argv=input.argv??['-u','Ada-male-lawful','-p','Archeologist','-r','human'];
 if(typeof keys!=='string'||!Array.isArray(argv)||argv.some(a=>typeof a!=='string'))throw new Error('Scenario needs literal keys and argv');
 const snapshots=[],frames=[],diagnostics=[],stdout=[],stderr=[],authoredKeys=[],exhausted='unwind';let consumed=0,module,inputExhausted=false,status={kind:'not-started'};
 const savedNow=Date.now,savedTZ=process.env.TZ;process.env.TZ=profile.TZ;Date.now=()=>Number(profile.NETHACK_RECORDING_EPOCH)*1000;
 const stringAt=p=>{p=Number(p);let end=p;if(!p)return null;while(module.HEAPU8[end])end++;return Buffer.from(module.HEAPU8.slice(p,end)).toString('utf8');};
 function state(){return {moves:String(module._full_moves()),x:module._full_hero_x(),y:module._full_hero_y(),hp:module._full_hero_hp(),level:module._full_hero_level(),firstInventoryId:module._full_hero_inventory_id(),rng:[0,1].map(i=>{const p=Number(module._full_rng_state(i)),n=Number(module._full_rng_size());return Buffer.from(module.HEAPU8.slice(p,p+n)).toString('base64');})};}
 function filesUnder(directory,out={}){for(const name of module.FS.readdir(directory)){if(name==='.'||name==='..')continue;const p=directory.replace(/\/$/,'')+'/'+name,st=module.FS.stat(p);if(module.FS.isDir(st.mode))filesUnder(p,out);else if(module.FS.isFile(st.mode))out[p]={bytes:Buffer.from(module.FS.readFile(p)).toString('base64'),mode:st.mode,atime:st.atime.getTime(),mtime:st.mtime.getTime(),ctime:st.ctime.getTime()};}return out;}
 try{
  module=await factory({noInitialRun:true,thisProgram:input.programName??'nethack',print:s=>diagnostics.push(String(s)),printErr:s=>diagnostics.push(String(s)),
   teleportReadKey(){if(snapshots.length>=(input.maxInputBoundaries??100000))throw new Error('Scenario input-boundary limit');snapshots.push({keyIndex:consumed,frameIndex:frames.length,state:state()});const code=typeof input.authorKey==='function'?input.authorKey({module,state:state(),frame:frames.at(-1),consumed}):consumed<keys.length?keys.charCodeAt(consumed):undefined;if(code===undefined){inputExhausted=true;throw exhausted;}if(!Number.isInteger(code)||code<0||code>65535)throw new TypeError('Original-C author must return a UTF-16 key code or undefined');authoredKeys.push(code);consumed++;return code===13?10:code;},
   teleportCapture(screen,x,y,animation){frames.push({keyIndex:consumed,screen,cursor:[x,y],animation:Boolean(animation)});},
   preRun:[m=>{Object.assign(m.ENV,profile);m.FS.mkdirTree(profile.HOME);m.FS.writeFile(profile.HOME+'/.nethackrc',input.options??'');}],
  });
  for(const fd of [1,2]){const tty=module.FS.getStream(fd).tty;if(!tty)throw new Error('Reference stdout/stderr must remain real TTY devices');const original=tty.ops.put_char;tty.ops={...tty.ops,put_char:(t,c)=>{if(c!==null)(fd===1?stdout:stderr).push(c);return original(t,c);}};}
  module.FS.mkdirTree('/nethack/save');module.FS.chdir('/nethack');
  for(const [p,row]of Object.entries(input.files??{})){if(!p.startsWith('/nethack/')&&!p.startsWith(profile.HOME+'/'))throw new Error('Scenario file outside game/home scope');module.FS.mkdirTree(path.posix.dirname(p));module.FS.writeFile(p,Buffer.from(row.bytes??row,'base64'));if(row.mode!==undefined)module.FS.chmod(p,row.mode);if(row.mtime!==undefined)module.FS.utime(p,row.atime??row.mtime,row.mtime);}
  input.observeRuntime?.({module});
  try{const result=module.callMain([...argv]);status=inputExhausted?{kind:'input-exhausted'}:{kind:'exited',code:result??0};}
  catch(e){if(e===exhausted)status={kind:'input-exhausted'};else if(e?.name==='ExitStatus')status={kind:'exited',code:e.status};else status={kind:'failed',message:String(e?.stack??e)};}
  const globals={};for(let i=0;i<module._full_global_count();i++){const name=stringAt(module._full_global_name(i));if((input.inspectGlobals??['u','flags','iflags','svc','svm','gl','svh','program_state']).includes(name)){const p=Number(module._full_global_address(i)),n=Number(module._full_global_size(i));globals[name]=Buffer.from(module.HEAPU8.slice(p,p+n)).toString('base64');}}
  const readLog=p=>{try{return Buffer.from(module.FS.readFile(p)).toString('utf8');}catch{return '';}};
  return {profile:receipt.profile,input:{programName:input.programName??'nethack',seed:input.seed??1,datetime:profile.NETHACK_FIXED_DATETIME,clockEpoch:profile.NETHACK_RECORDING_EPOCH,argv:[...argv],keys:typeof input.authorKey==='function'?authoredKeys.map(c=>String.fromCharCode(c)).join(''):keys,options:input.options??'',environment:profile},status,consumed,snapshots,frames,stdout:Buffer.from(stdout).toString('base64'),stderr:Buffer.from(stderr).toString('base64'),diagnostics,globals,state:state(),rngLog:readLog('/rng.log'),displayRngLog:readLog('/rng-display.log'),files:filesUnder('/nethack',filesUnder(profile.HOME))};
 }finally{Date.now=savedNow;if(savedTZ===undefined)delete process.env.TZ;else process.env.TZ=savedTZ;}
}
if(process.argv[1]&&path.resolve(process.argv[1])===path.resolve(new URL(import.meta.url).pathname)){
 const [directory,inputFile,outputFile]=process.argv.slice(2);if(!directory||!inputFile||!outputFile)throw new Error('Usage: node full-original-c-run.mjs REFERENCE INPUT.json OUTPUT.json');
 const result=await runFullOriginalC(directory,JSON.parse(fs.readFileSync(inputFile)));fs.writeFileSync(outputFile,JSON.stringify(result,null,2)+'\n');console.log(JSON.stringify({status:result.status,consumed:result.consumed,inputs:result.snapshots.length,frames:result.frames.length,moves:result.state.moves}));if(result.status.kind==='failed')process.exitCode=1;
}
