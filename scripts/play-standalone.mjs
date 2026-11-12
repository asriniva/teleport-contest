#!/usr/bin/env node
// Node terminal/file boundary for the standalone JS engine. No Wasm loader.
import fs from 'node:fs';
import path from 'node:path';
import {fileURLToPath} from 'node:url';
const root=path.resolve(path.dirname(fileURLToPath(import.meta.url)),'..');
const options={assets:path.join(root,'.cache/full-original-c-v1/assets'),state:path.join(root,'.cache/standalone-player/files.json'),seed:'1',rc:null,fixedTime:null},argv=[];
for(let i=2;i<process.argv.length;i++){
 const key=process.argv[i];if(key==='--'){argv.push(...process.argv.slice(i+1));break;}
 if(key==='--help'){process.stdout.write('Usage: node scripts/play-standalone.mjs [--assets DIR] [--state FILE] [--seed INTEGER] [--rc FILE] [--fixed-time ISO] [-- NETHACK_ARGUMENTS...]\n\nPlay the standalone JavaScript engine in this terminal. Use the game’s save or quit command to exit. Saves, bones and scores are stored in --state. Seed defaults to1. Assets default to the prepared original-C data directory; its Wasm executable is never loaded.\n');process.exit(0);}
 if(!['--assets','--state','--seed','--rc','--fixed-time'].includes(key))throw Error('Unknown launcher option '+key+'; use -- before NetHack arguments');
 const value=process.argv[++i];if(value===undefined)throw Error('Missing value for '+key);options[key==='--fixed-time'?'fixedTime':key.slice(2)]=value;
}
options.seed=BigInt(options.seed).toString();
const epoch=options.fixedTime===null?null:Date.parse(options.fixedTime);if(epoch!==null&&!Number.isFinite(epoch))throw Error('Invalid --fixed-time ISO date');
const now=epoch===null?Date.now:()=>epoch,home='/home/player',profile={NETHACKDIR:'/nethack',HACKDIR:'/nethack',HOME:home,USER:process.env.USER??'player',LOGNAME:process.env.LOGNAME??process.env.USER??'player',MAIL:'/nethack/mailbox',TERM:'xterm-256color',TERMINFO:'/nethack/terminfo',LINES:'24',COLUMNS:'80',TZ:'UTC',NETHACK_NO_DELAY:'1',NOMUX_MARKERS:'1',NETHACK_RAW_KEYS:'1',NETHACK_SEED:options.seed};
process.env.TZ=profile.TZ;
if(epoch!==null){profile.NETHACK_FIXED_DATETIME=new Date(epoch).toISOString().replace(/[-:T]/g,'').slice(0,14);profile.NETHACK_RECORDING_EPOCH=String(Math.floor(epoch/1000));}
const assets={};
function loadAssets(directory,prefix='/nethack'){
 for(const row of fs.readdirSync(directory,{withFileTypes:true})){const name=path.join(directory,row.name),target=prefix+'/'+row.name;if(row.isDirectory())loadAssets(name,target);else if(row.isFile())assets[target]={bytes:new Uint8Array(fs.readFileSync(name)),mode:fs.statSync(name).mode&0o777};else throw Error('Unsupported game-data entry '+name);}
}
loadAssets(path.resolve(options.assets));
assets[home+'/.nethackrc']={bytes:new Uint8Array(options.rc?fs.readFileSync(path.resolve(options.rc)):[]),mode:0o600};
const statePath=path.resolve(options.state);let previous;
if(fs.existsSync(statePath)){
 previous=JSON.parse(fs.readFileSync(statePath,'utf8'));if(previous.version!==1||!previous.state||!previous.state.files||!Array.isArray(previous.state.deleted))throw Error('Unsupported standalone save-state format');
 for(const name of [...Object.keys(previous.state.files),...previous.state.deleted])if(!name.startsWith('/nethack/')||path.posix.normalize(name)!==name||name.includes('\0'))throw Error('Invalid virtual save path '+name);
}
function readBytes(count){const out=Buffer.alloc(count);let n;do{try{n=fs.readSync(0,out,0,count,null);break;}catch(error){if(error.code!=='EINTR')throw error;}}while(true);for(let i=0;i<n;i++)if(out[i]===13)out[i]=10;return new Uint8Array(out.buffer,out.byteOffset,n);}
function writeBytes(fd,bytes){let at=0;while(at<bytes.length){try{const n=fs.writeSync(fd,bytes,at,bytes.length-at);if(!n)throw Error('Terminal output closed');at+=n;}catch(error){if(error.code!=='EINTR')throw error;}}}
const forbidden=()=>{throw Error('The standalone player cannot use Wasm or network capabilities');},names=['WebAssembly','fetch','Worker','WebSocket','XMLHttpRequest'],saved=names.map(name=>Object.getOwnPropertyDescriptor(globalThis,name)),raw=Boolean(process.stdin.isTTY&&process.stdin.isRaw);let program,baseline,completed=false,code=1;
try{
 for(const name of names)Object.defineProperty(globalThis,name,{configurable:true,value:name==='WebAssembly'?new Proxy({},{get:forbidden}):forbidden});
 const[{createStandaloneProgram},{CExit}]=await Promise.all([import('../js/nethack/program.js'),import('../js/nethack/functions.js')]);
 const layouts=JSON.parse(fs.readFileSync(path.join(root,'js/wasm/tu-layouts.json')));
 program=createStandaloneProgram({layouts,assets,directories:[home,'/nethack/save'],runtime:{environment:profile,now,initialBytes:1024,maximumBytes:128*1024*1024},stdio:{readStdin:readBytes,stdout:bytes=>writeBytes(1,bytes),stderr:bytes=>writeBytes(2,bytes)},readKey(){const bytes=readBytes(1);if(!bytes.length)throw Error('Keyboard input closed before the game exited');return bytes[0];}});
 program.environment.filesystem.chdir('/nethack');baseline=program.environment.fileBaseline();if(previous)program.environment.restoreFiles(previous.state);
 if(process.stdin.isTTY)process.stdin.setRawMode(true);
 try{const result=program.run(argv,{programName:'nethack'});code=Number(result??0);completed=code===0;}catch(error){if(!(error instanceof CExit))throw error;code=error.status;completed=code===0;}
 if(completed){const state={version:1,state:program.environment.captureFiles(baseline)};fs.mkdirSync(path.dirname(statePath),{recursive:true});const temporary=statePath+'.tmp-'+process.pid;fs.writeFileSync(temporary,JSON.stringify(state)+'\n',{mode:0o600});fs.renameSync(temporary,statePath);}
}catch(error){process.stderr.write('\n'+String(error.stack??error)+'\n');code=1;}
finally{if(process.stdin.isTTY)process.stdin.setRawMode(raw);names.forEach((name,i)=>saved[i]?Object.defineProperty(globalThis,name,saved[i]):delete globalThis[name]);}
process.exitCode=code;
