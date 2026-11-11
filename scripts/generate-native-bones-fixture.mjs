// Complete reference process: inputs/observation only, no translated owners.
import fs from 'node:fs';import path from 'node:path';import crypto from 'node:crypto';import {pathToFileURL} from 'node:url';
const digest=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex');
async function runControlledOriginalC(directory,input={},controller){
 directory=path.resolve(directory);const receipt=JSON.parse(fs.readFileSync(path.join(directory,'receipt.json')));
 if(receipt.gameTranslationUnits!==140||receipt.luaTranslationUnits!==32||receipt.abortBoundaries.length||receipt.syntheticGameGlobals.length||receipt.portedTranslationUnits.length)throw new Error('Not a complete original-C reference');
 for(const [p,h]of Object.entries(receipt.sourceSha256))if(digest(p)!==h)throw new Error('Changed original-C reference input '+p);
 for(const [p,h]of Object.entries(receipt.artifactSha256))if(digest(path.join(directory,p))!==h)throw new Error('Changed original-C reference artifact '+p);
 const {default:factory}=await import(pathToFileURL(path.join(directory,'out/game.mjs')));
 const profile={NETHACKDIR:'/nethack',HACKDIR:'/nethack',HOME:'/home/player',USER:'root',LOGNAME:'root',MAIL:'/nethack/mailbox',TERM:'xterm-256color',TERMINFO:'/nethack/terminfo',LINES:'24',COLUMNS:'80',TZ:input.timezone??process.env.TZ??Intl.DateTimeFormat().resolvedOptions().timeZone,NETHACK_NO_DELAY:'1',NOMUX_MARKERS:'1',NETHACK_RAW_KEYS:'1',NETHACK_SEED:String(input.seed??1),NETHACK_FIXED_DATETIME:input.datetime??'20260102030405',NETHACK_RECORDING_EPOCH:String(input.clockEpoch??1777723200),NETHACK_RNGLOG:'/rng.log',NETHACK_RNGLOG_DISP:'/rng-display.log',...input.environment};
 let keys=input.keys??'';const argv=input.argv??['-u','Ada-male-lawful','-p','Archeologist','-r','human'];
 if(typeof keys!=='string'||!Array.isArray(argv)||argv.some(a=>typeof a!=='string'))throw new Error('Scenario needs literal keys and argv');
 const snapshots=[],frames=[],diagnostics=[],stdout=[],stderr=[],exhausted='unwind';let consumed=0,module,inputExhausted=false,status={kind:'not-started'};
 const savedNow=Date.now,savedTZ=process.env.TZ;process.env.TZ=profile.TZ;Date.now=()=>Number(profile.NETHACK_RECORDING_EPOCH)*1000;
 const stringAt=p=>{p=Number(p);let end=p;if(!p)return null;while(module.HEAPU8[end])end++;return Buffer.from(module.HEAPU8.slice(p,end)).toString('utf8');};
 function state(){return {moves:String(module._full_moves()),x:module._full_hero_x(),y:module._full_hero_y(),hp:module._full_hero_hp(),level:module._full_hero_level(),firstInventoryId:module._full_hero_inventory_id(),rng:[0,1].map(i=>{const p=Number(module._full_rng_state(i)),n=Number(module._full_rng_size());return Buffer.from(module.HEAPU8.slice(p,p+n)).toString('base64');})};}
 function filesUnder(directory,out={}){for(const name of module.FS.readdir(directory)){if(name==='.'||name==='..')continue;const p=directory.replace(/\/$/,'')+'/'+name,st=module.FS.stat(p);if(module.FS.isDir(st.mode))filesUnder(p,out);else if(module.FS.isFile(st.mode))out[p]={bytes:Buffer.from(module.FS.readFile(p)).toString('base64'),mode:st.mode,atime:st.atime.getTime(),mtime:st.mtime.getTime(),ctime:st.ctime.getTime()};}return out;}
 try{
  module=await factory({noInitialRun:true,thisProgram:input.programName??'nethack',print:s=>diagnostics.push(String(s)),printErr:s=>diagnostics.push(String(s)),
   teleportReadKey(){if(snapshots.length>=(input.maxInputBoundaries??100000))throw new Error('Scenario input-boundary limit');snapshots.push({keyIndex:consumed,frameIndex:frames.length,state:state()});if(consumed>=keys.length){const next=controller({module,frames,snapshots,consumed});if(typeof next!=='string'||next.length!==1){inputExhausted=true;throw exhausted;}keys+=next;}const code=keys.charCodeAt(consumed++);return code===13?10:code;},
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
  return {profile:receipt.profile,input:{programName:input.programName??'nethack',seed:input.seed??1,datetime:profile.NETHACK_FIXED_DATETIME,clockEpoch:profile.NETHACK_RECORDING_EPOCH,argv:[...argv],keys,options:input.options??'',environment:profile},status,consumed,snapshots,frames,stdout:Buffer.from(stdout).toString('base64'),stderr:Buffer.from(stderr).toString('base64'),diagnostics,globals,state:state(),rngLog:readLog('/rng.log'),displayRngLog:readLog('/rng-display.log'),files:filesUnder('/nethack',filesUnder(profile.HOME))};
 }finally{Date.now=savedNow;if(savedTZ===undefined)delete process.env.TZ;else process.env.TZ=savedTZ;}
}

// Controller observes actual native fields only; every action returns one normal
// keyboard character for the original main parser. It never invokes policy APIs
// or writes game memory, globals, timers, terrain or random state.
const records=JSON.parse(fs.readFileSync('js/standalone/records.json')).records;
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),L=layouts.monmove;
const directory=path.resolve(process.env.STANDALONE_FULL_C_REFERENCE??'.cache/full-original-c-v1');
const output=path.resolve(process.env.NATIVE_BONES_OUTPUT??'.cache/native-deeper-bones-sam3');fs.mkdirSync(output,{recursive:true});
const savedFile='/nethack/save/0Ada.Z',producerPath='.cache/standalone-program/initial-state-save-c.json';
const fresh=process.env.NATIVE_BONES_FRESH!=='0',seed=Number(process.env.NATIVE_BONES_SEED??3);
const targetDepth=Number(process.env.NATIVE_BONES_DEPTH??5);if(!Number.isInteger(targetDepth)||targetDepth<4||targetDepth>10)throw new Error('Ordinary target depth must be4..10');
const role=process.env.NATIVE_BONES_ROLE??'Samurai',valk=role==='Valkyrie';
const stairKeys='lk khhokkkkklklkkkkhhhhhhhhhhjhhhhhhhhhhjjjjjjjjjhhhjjhhhhkk>';
const producer=fresh?null:JSON.parse(fs.readFileSync(producerPath));
const input={seed,timezone:'UTC',options:'OPTIONS=!news\n',argv:['-u',valk?'Ada-female-neutral':'Ada-male-lawful','-p',role,'-r','human'],keys:fresh?'  n':stairKeys+' ',maxInputBoundaries:10000,...(producer?{files:{[savedFile]:producer.files[savedFile]}}:{})};
if(producer&&(role!=='Archeologist'||seed!==1))throw new Error('Restored native seed1 Archeologist is fixed; use fresh for other profiles');
const trace=[],pending=[],directions=[[-1,0,'h'],[0,1,'j'],[0,-1,'k'],[1,0,'l']];let globals,deepest=0,stuck=0,previousPosition;
const readString=(module,p)=>{p=Number(p);let end=p;while(module.HEAPU8[end])end++;return Buffer.from(module.HEAPU8.slice(p,end)).toString();};
function choose({module,frames,consumed}){
 if(!globals){globals={};for(let i=0;i<module._full_global_count();i++)globals[readString(module,module._full_global_name(i))]=Number(module._full_global_address(i));}
 const view=new DataView(module.HEAPU8.buffer),offset=(type,name)=>records[type].fields[name].offset;
 const field=(type,p,name,kind='i16')=>{const f=records[type].fields[name],at=p+f.offset;if(f.bits!==undefined){let value=0n;for(let i=0;i<Math.ceil((f.shift+f.bits)/8);i++)value|=BigInt(module.HEAPU8[at+i])<<BigInt(i*8);return Number(value>>BigInt(f.shift)&((1n<<BigInt(f.bits))-1n));}return kind==='ptr'?Number(view.getBigUint64(at,true)):kind==='i32'?view.getInt32(at,true):kind==='i8'?view.getInt8(at):view.getInt16(at,true);};
 const u=globals.u,x=field('you',u,'ux'),y=field('you',u,'uy'),uz=u+offset('you','uz'),dnum=field('d_level',uz,'dnum'),dlevel=field('d_level',uz,'dlevel'),hp=field('you',u,'uhp','i32'),moves=String(module._full_moves());
 if(dnum===0)deepest=Math.max(deepest,dlevel);
 trace.push({keyIndex:consumed,moves,dnum,dlevel,x,y,hp});
 if(consumed>9000||Number(moves)>6000)throw new Error('Ordinary native fixture input/turn bound');
 const screen=(frames.at(-1)?.screen??'').replace(/\x1b\[[0-?]*[ -/]*[@-~]/g,'');
 if(screen.includes('--More--')||screen.includes('(end)')||/\(\d+ of \d+\)/.test(screen))return ' ';
 if(hp<=0)return /\[[ynq]+\]/i.test(screen)?'n':' ';
 if(pending.length)return pending.shift();
 const position=[dnum,dlevel,x,y].join(':');stuck=position===previousPosition?stuck+1:0;previousPosition=position;if(stuck>180&&dlevel<targetDepth)throw new Error('Ordinary path stalled at '+position);
 if(deepest>=targetDepth){pending.push('.');return 'm';}
 const level=globals.svl+offset('instance_globals_saved_l','level'),locations=level+offset('dlevel_t','locations');
 const typ=(a,b)=>field('rm',locations+(a*L.ROWNO+b)*records.rm.size,'typ','i8');
 const flags=(a,b)=>field('rm',locations+(a*L.ROWNO+b)*records.rm.size,'flags');
 const traps=new Set();for(let p=field('instance_globals_f',globals.gf,'ftrap','ptr');p;p=field('trap',p,'ntrap','ptr'))traps.add(field('trap',p,'tx')+','+field('trap',p,'ty'));
 const blocked=new Set();for(let p=field('dlevel_t',level,'monlist','ptr');p;p=field('monst',p,'nmon','ptr'))if(field('monst',p,'mhp','i32')>0&&!field('monst',p,'mtame','i8'))blocked.add(field('monst',p,'mx')+','+field('monst',p,'my'));
 let target;for(let p=field('instance_globals_s',globals.gs,'stairs','ptr');p;p=field('stairway',p,'next','ptr')){const to=p+offset('stairway','tolev');if(!field('stairway',p,'up','i8')&&field('d_level',to,'dnum')===dnum&&field('d_level',to,'dlevel')>dlevel){target=[field('stairway',p,'sx'),field('stairway',p,'sy')];break;}}
 if(!target)throw new Error('No ordinary down staircase on '+position);
 if(x===target[0]&&y===target[1])return '>';
 function route(avoidMonsters,allowSecrets){const queue=[[x,y,[]]],seen=new Set([x+','+y]);for(let at=0;at<queue.length;at++){const[a,b,path]=queue[at];if(a===target[0]&&b===target[1])return path;for(const[dx,dy,key]of directions){const nx=a+dx,ny=b+dy,id=nx+','+ny;if(nx<1||nx>=L.COLNO||ny<0||ny>=L.ROWNO||seen.has(id)||traps.has(id)||(avoidMonsters&&blocked.has(id)))continue;const t=typ(nx,ny);if(t<L.DOOR&&!(allowSecrets&&(t===layouts.dig.SDOOR||t===layouts.dig.SCORR)))continue;seen.add(id);queue.push([nx,ny,[...path,[nx,ny,key]]]);}}return null;}
 const path=route(true,false)??route(false,false)??route(true,true)??route(false,true);
 if(!path?.length)throw new Error('No ordinary trap-avoiding route on '+position);
 const[nx,ny,key]=path[0],t=typ(nx,ny);
 if(t===layouts.dig.SDOOR||t===layouts.dig.SCORR)return 's';
 if(t===L.DOOR&&(flags(nx,ny)&L.D_LOCKED)){
  let pick;for(let p=field('instance_globals_i',globals.gi,'invent','ptr');p;p=field('obj',p,'nobj','ptr'))if(field('obj',p,'otyp')===layouts.dig.PICK_AXE){pick=String.fromCharCode(field('obj',p,'invlet','i8'));break;}
  if(pick){pending.push(pick,key);return 'a';}pending.push(key);return String.fromCharCode(4);
 }
 if(t===L.DOOR&&(flags(nx,ny)&L.D_CLOSED)){pending.push(key);return 'o';}
 return key;
}
const result=await runControlledOriginalC(directory,input,choose);
const literalInput={...input,keys:result.input.keys};delete literalInput.maxInputBoundaries;
fs.writeFileSync(output+'/input.json',JSON.stringify(literalInput,null,2)+'\n');fs.writeFileSync(output+'/result.json',JSON.stringify(result,null,2)+'\n');fs.writeFileSync(output+'/trace.json',JSON.stringify(trace,null,2)+'\n');
const bones=Object.keys(result.files).filter(name=>/\/bon[^/]*$/.test(name));
fs.copyFileSync('scripts/generate-native-bones-fixture.mjs',output+'/controller.mjs');
const receipt=JSON.parse(fs.readFileSync(directory+'/receipt.json'));
const evidence={nativeOnly:true,complete:result.status.kind==='exited'&&result.status.code===0&&deepest>=4&&bones.length>0,deepest,status:result.status,consumed:result.consumed,moves:result.state.moves,bones:bones.map(name=>({path:name,bytes:Buffer.from(result.files[name].bytes,'base64').length,sha256:crypto.createHash('sha256').update(Buffer.from(result.files[name].bytes,'base64')).digest('hex')})),profile:{seed,role,targetDepth,restored:Boolean(producer),timezone:'UTC',options:input.options},controllerSha256:digest('scripts/generate-native-bones-fixture.mjs'),referenceReceiptSha256:digest(directory+'/receipt.json'),producerSha256:producer?digest(producerPath):null,literalInputSha256:digest(output+'/input.json'),originalC:{gameTranslationUnits:receipt.gameTranslationUnits,luaTranslationUnits:receipt.luaTranslationUnits},limitation:'Native input generation only; generated literal input must replay through unmodified full-original-c-run before acceptance. No JS producer/consumer or bones graph acceptance.'};
fs.writeFileSync(output+'/evidence.json',JSON.stringify(evidence,null,2)+'\n');console.log(JSON.stringify(evidence,null,2));
