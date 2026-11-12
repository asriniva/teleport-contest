import './pure-js-probes/deny-wasm.mjs';
import {createProbe,createReference,loadFixture,fixtureImports} from './pure-js-fixtures/load.mjs';
import {BigUint64Array as FixtureBigUint64Array,DataView as FixtureDataView,Uint8Array as FixtureUint8Array} from './native-test-backend.mjs';
import assert from './native-test-assert.mjs';
import {readFile,writeFile} from 'node:fs/promises';
import {resolve,dirname,join} from 'node:path';
import {fileURLToPath,pathToFileURL} from 'node:url';
// No native fixture exists. Reject the default/native request before importing factories.
// Original C reference is available through the isolated reference process.
const root=resolve(dirname(fileURLToPath(import.meta.url)),'..'),dir=resolve(process.env.UNIXMAIN_PROBE_DIR??join(root,'.cache/unixmain-first-pass'));
const {callUnixmain,createUnixmainEnvironment}=await loadFixture("unixmain",pathToFileURL(resolve(process.env.UNIXMAIN_RUNTIME_PATH??join(root,'js/nethack/bindings/unixmain.js'))).href);
const schema=JSON.parse(await readFile(join(root,'nethack-c/wasm/tu-fragments/unixmain-schema.json'),'utf8'));
const factories=await Promise.all(['reference','hybrid'].map(async mode=>(await loadFixture("unixmain",pathToFileURL(join(dir,`unixmain-${mode}.mjs`)).href)).default));
let latestServices;const checked=(services,n,...args)=>{latestServices=services;const sp=services.stackSave();try{return callUnixmain(services,n,...args);}finally{assert.equal(services.stackSave(),sp,'source stack frames restored: '+n);}};
const create=async i=>{const prints=[],exits=[],m=await factories[i]({thisProgram:'nethack',onExit:s=>exits.push(s),print:s=>prints.push(s),printErr:s=>prints.push(s),nethackPorted:{unixmain:checked},preRun:[m=>{Object.assign(m.ENV,{USER:'Tester',LOGNAME:'Logger',NETHACKDIR:'/nethack',NETHACK_SEED:'123'});} ]});m.output=prints;m.exits=exits;for(const p of ['/nethack','/nethack/alt','/nethack/save','/usr/games/lib/nethackdir'])m.FS.mkdirTree(p);m.FS.writeFile('/nethack/save/test.sav','saved');return m;};
const mods=await Promise.all([create(0),create(1)]);
const decode=(m,p)=>{p=BigInt(p);assert.ok(p>0n&&p<BigInt(m.HEAPU8.length));let at=Number(p),end=at;while(end<m.HEAPU8.length&&m.HEAPU8[end])end++;assert.ok(end<m.HEAPU8.length);return new TextDecoder().decode(m.HEAPU8.subarray(at,end));};
const put=(m,p,s)=>m.HEAPU8.set(new TextEncoder().encode(s+'\0'),Number(p));
const buffer=(m,s,i=0)=>{const p=m._probe_buffer(i);put(m,p,s);return p;};
const env=(m,k,v)=>{buffer(m,k,60);if(v!==null)buffer(m,v,61);m._probe_env(BigInt(m._probe_buffer(60)),v===null?0n:BigInt(m._probe_buffer(61)));const actual=m._probe_getenv(BigInt(m._probe_buffer(60)));assert.equal(actual?decode(m,actual):null,v,'actual C getenv matches configured environment '+k);checks++;};
const option=(m,k,v=1)=>m._probe_option(k,BigInt(v));
const write64=(m,p,v)=>new FixtureDataView(m.HEAPU8.buffer).setBigUint64(Number(p),BigInt.asUintN(64,BigInt(v)),true);
const kinds=Object.keys(schema.schema),kind=n=>{const k=kinds.indexOf(n);assert.ok(k>=0,n);return k;},fi=(n,f)=>{const k=schema.schema[n].fields.findIndex(x=>x.name===f);assert.ok(k>=0,n+'.'+f);return k;};
const global=(m,n)=>{const i=schema.globals.findIndex(g=>g.name===n);assert.ok(i>=0,n);return m._probe_global(i);};
const pathinfo=(m,path)=>{const[g,...tail]=path.split('.');let at=global(m,g),type=schema.globals.find(x=>x.name===g).canonical;for(const f of tail.slice(0,-1)){const n=type.replace(/^(struct|union) /,'');at=m._probe_address(kind(n),at,fi(n,f));type=schema.schema[n].fields[fi(n,f)].canonical;}return{at,n:type.replace(/^(struct|union) /,''),f:tail.at(-1)};};
const field=(m,path,v)=>{const{at,n,f}=pathinfo(m,path);m._probe_write(kind(n),at,fi(n,f),BigInt.asUintN(64,BigInt(v)));};
const fieldAddress=(m,path)=>{if(!path.includes('.'))return global(m,path);const{at,n,f}=pathinfo(m,path);return m._probe_address(kind(n),at,fi(n,f));};
const argv=(m,args,which=0)=>{for(let i=0;i<args.length;i++){buffer(m,args[i],20+which*20+i);m._probe_arg(which,i,20+which*20+i);}m._probe_arg(which,args.length,-1);const at=m._probe_argv(which),dv=new FixtureDataView(m.HEAPU8.buffer);assert.equal(dv.getBigUint64(Number(at)+args.length*8,true),0n,'argv[argc] is NULL');for(let i=0;i<args.length;i++)assert.notEqual(dv.getBigUint64(Number(at)+i*8,true),0n,'argc excludes terminating NULL');checks++;return at;};
const call=(m,n,a=[])=>{const i=schema.names.indexOf(n);assert.ok(i>=0,n);const p=m._malloc(32n);try{for(let j=0;j<4;j++)write64(m,BigInt(p)+BigInt(j*8),a[j]??0);return m._probe_call(i,BigInt(p));}finally{m._free(p);}};
const trace=m=>decode(m,m._probe_trace()),snapshot=m=>decode(m,m._probe_snapshot());
let checks=0;const invoked=new Set(),cases=[];const equal=(a,b,s)=>{assert.deepEqual(b,a,s);checks++;};
const passwd=(m,p)=>{const out={};for(let i=0;i<schema.schema.passwd.fields.length;i++){const f=schema.schema.passwd.fields[i],v=BigInt.asUintN(64,m._probe_read(kind('passwd'),p,i));out[f.name]=f.canonical.includes('*')?v?decode(m,v):null:String(v);}return out;};
const observe=(m,n,v)=>({result:n==='get_unix_pw'?passwd(m,v):n==='get_login_name'?decode(m,v):String(v),trace:trace(m),state:n==='main'?decode(m,m._probe_finished()):snapshot(m),buffers:[0,1].map(i=>decode(m,m._probe_buffer(i))),uuid:Array.from(m.HEAPU8.subarray(Number(fieldAddress(m,'svn.nhuuid')),Number(fieldAddress(m,'svn.nhuuid'))+37)),cwd:m.FS.cwd(),actions:Array.from({length:m._probe_actions()},(_,i)=>{const p=m._probe_action(i),raw=Array.from(m.HEAPU8.subarray(Number(p),Number(p)+152)),ptr=new FixtureDataView(m.HEAPU8.buffer).getBigUint64(Number(p),true),handler=m._probe_handler(ptr);assert.ok(handler>=0);raw.fill(0,0,8);return{handler,raw};})});
const run=(label,n,setup=()=>{},args=()=>[],errorExpected=null)=>{const out=mods.map(m=>{m._probe_reset();m.FS.chdir('/');m.output.length=0;setup(m);const sp=m.stackSave();let v=0n,error=null;try{v=call(m,n,args(m));}catch(e){error=e.message;if(process.env.UNIXMAIN_DEBUG)console.error(e.stack);}finally{m.stackRestore(sp);}return{...observe(m,n,v),error,output:m.output};});equal(out[0],out[1],label);if(errorExpected){assert.match(out[0].error??'',errorExpected,label);checks++;}else assert.equal(out[0].error,null,label);invoked.add(n);cases.push({label,function:n,observation:out[0]});return out[0];};
run('options no args','process_options',()=>{},m=>[1,argv(m,['nethack'])]);
run('directory actual MEMFS','chdirx',m=>buffer(m,'/nethack'),m=>[m._probe_buffer(0),1]);
run('name from environment','whoami');
run('full zeroed native signal records','sethanguphandler',()=>{},m=>[m._probe_function(1)]);
for(const [n,p] of [['authorize_wizard_mode','wizards'],['authorize_explore_mode','explorers']])for(const s of ['','root','root other','other','*anything'])run(n+'/'+s,n,m=>field(m,'sysopt.'+p,buffer(m,s)));
run('message normal explore','wd_message',m=>field(m,'flags.explore',1));
for(const s of ['','path','path/','/','abc def'])run('append '+s,'append_slash',m=>buffer(m,s),m=>[m._probe_buffer(0)]);
for(const s of ['','root',' root ','root\tother','other root','rooter','other','*suffix','\nroot\r','ROOT'])run('allowed user '+JSON.stringify(s),'check_user_string',m=>buffer(m,s),m=>[m._probe_buffer(0)]);
run('virtual account exact native fields','get_unix_pw');run('stable login buffer','get_login_name');run('explicit seed','sys_random_seed');
run('configured empty uuid getter','get_nhuuid',m=>put(m,fieldAddress(m,'svn.nhuuid'),'existing'));run('full uuid clear','free_nhuuid',m=>m.HEAPU8.fill(0x7f,Number(fieldAddress(m,'svn.nhuuid')),Number(fieldAddress(m,'svn.nhuuid'))+37));
// Preserve source option spelling, argument stepping, errors, and sysconf precedence.
for(const args of [['-D'],['-X'],['-D','-X'],['-X','-D'],['-debug'],['--debug'],['-dfoo'],['-DECgraphics'],['-IBMgraphics'],['-news'],['-no-news'],['-n'],['-uAda'],['-u','Ada'],['-u'],['-pWizard'],['-p','Wizard'],['-rElf'],['-r','Elf'],['-p'],['-r'],['-@'],['-loglua'],['-loganything'],['--'],['--x'],['--x=y'],['--u=Ada'],['-z'],['12'],['garbage'],['-u','X'.repeat(80)],['-p','Wizard','-r','Elf','-u','Ada','-@'],['-unknown'],['-no-graphics']])run('option argv '+JSON.stringify(args),'process_options',()=>{},m=>[args.length+1,argv(m,['nethack',...args])]);
for(const max of [0,1,7,2147483647])for(const lock of [0,3,2147483647])run('max players '+max+'/'+lock,'process_options',m=>{field(m,'sysopt.maxplayers',max);field(m,'gl.locknum',lock);},m=>[1,argv(m,['nethack'])]);
for(const [user,log,name] of [['Ada-Lovelace','fallback',''],['','Logger',''],['','', ''],['Override','Log','Kept'],['X'.repeat(80),'Log','']])run('whoami '+user+'/'+log+'/'+name,'whoami',m=>{env(m,'USER',user);env(m,'LOGNAME',log);put(m,fieldAddress(m,'svp.plname'),name);});
for(const name of ['', 'root','Root','Named'])for(const allow of ['*','Named',' root\tNamed\nother','NamedSuffix'])run('plname authorization '+name+'/'+allow,'check_user_string',m=>{field(m,'sysopt.check_plname',1);put(m,fieldAddress(m,'svp.plname'),name);buffer(m,allow);},m=>[m._probe_buffer(0)]);
for(const wiz of [0,1])for(const exp of [0,1])for(const list of ['', 'root', 'root other'])run('wd mode '+wiz+'/'+exp+'/'+list,'wd_message',m=>{field(m,'flags.debug',1);field(m,'flags.explore',1);field(m,'iflags.wiz_error_flag',wiz);field(m,'iflags.explore_error_flag',exp);field(m,'iflags.deferred_X',1);field(m,'sysopt.wizards',buffer(m,list));});
for(const raw of [0n,1n])run('raw signal constant '+raw,'sethanguphandler',()=>{},()=>[raw]);
for(const value of ['','0','-1','18446744073709551615','18446744073709551616','9007199254740993','  +12tail','0xff','garbage'])run('strtoul exact '+JSON.stringify(value),'sys_random_seed',m=>{env(m,'NETHACK_SEED',value);m.HEAPU8[Number(global(m,'has_strong_rngseed'))]=1;});
for(const bytes of [[],[0x12],[1,2,3,4,5,6,7],[1,2,3,4,5,6,7,0x80],[0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff]])run('actual entropy file '+bytes.join('/'),'sys_random_seed',m=>{env(m,'NETHACK_SEED',null);try{m.FS.unlink('/dev/random');}catch{}m.FS.writeFile('/dev/random',new FixtureUint8Array(bytes));});
for(const pid of [0,1,4,42,-1,-2147483648,2147483647])for(const time of [-9223372036854775808n,9007199254740993n,9223372036854775807n])run('fallback seed '+pid+'/'+time,'sys_random_seed',m=>{env(m,'NETHACK_SEED',null);try{m.FS.unlink('/dev/random');}catch{}option(m,70,pid);option(m,71,time);});
for(const n of ['whoami','process_options','sethanguphandler','wd_message','sys_random_seed'])for(const mode of [30,32])run('growth/native reentry '+n+'/'+mode,n,m=>{option(m,mode);field(m,'iflags.wiz_error_flag',1);field(m,'sysopt.wizards',buffer(m,'root other'));env(m,'USER','Ada');env(m,'NETHACK_SEED',null);try{m.FS.unlink('/dev/random');}catch{}},m=>n==='process_options'?[2,argv(m,['nethack','-D'])]:n==='sethanguphandler'?[m._probe_function(1)]:[]);
for(const n of ['whoami','process_options','sethanguphandler','wd_message','sys_random_seed'])run('native callback throw cleanup '+n,n,m=>{option(m,31);field(m,'iflags.wiz_error_flag',1);field(m,'sysopt.wizards',buffer(m,'root other'));env(m,'USER','Ada');env(m,'NETHACK_SEED',null);try{m.FS.unlink('/dev/random');}catch{}},m=>n==='process_options'?[2,argv(m,['nethack','-D'])]:n==='sethanguphandler'?[m._probe_function(1)]:[],/UNIXMAIN controlled callback/);
run('missing directory preserves error path','chdirx',m=>buffer(m,'/does-not-exist'),m=>[m._probe_buffer(0),1],/UNIXMAIN controlled callback/);
// The independent O2 consumer observes writable source-private data through real C fields.
const accountObservations=mods.map(m=>{m._probe_reset();const p=call(m,'get_unix_pw'),name=m._probe_passwd_string(p,0);assert.equal(decode(m,name),'root');assert.equal(m._probe_passwd_uid(p),0n);assert.equal(m._probe_passwd_gid(p),0n);const before=passwd(m,p);m._probe_passwd_set(p,buffer(m,'Mutable virtual user',2),0xffffffff,0x80000000);assert.equal(call(m,'get_unix_pw'),p,'stable private account address');const login=call(m,'get_login_name');assert.equal(decode(m,login),'Mutable virtual user');const again=call(m,'get_login_name');assert.equal(again,login,'stable source static char buffer');const out={before,after:passwd(m,p),login:decode(m,login),uid:String(m._probe_passwd_uid(p)),gid:String(m._probe_passwd_gid(p))};m._probe_passwd_set(p,name,0,0);checks+=7;return out;});equal(accountObservations[0],accountObservations[1],'independent native consumer + private alias mutation');
call(mods[1],'get_login_name');const base=latestServices,cenv=createUnixmainEnvironment(base),m=mods[1];
for(const raw of [0x20000000000000n,0x20000000000001n,0x20000000000003n,0xffffffffffffffffn]){const at=fieldAddress(m,'sysopt.wizards');field(m,'sysopt.wizards',raw);const observed=cenv.field(global(m,'sysopt'),'sysopt_s','wizards').value;assert.equal(BigInt(observed),raw);assert.equal(BigInt.asUintN(64,m._probe_read(kind('sysopt_s'),global(m,'sysopt'),fi('sysopt_s','wizards'))),raw);const bytes=Array.from(m.HEAPU8.subarray(Number(at),Number(at)+8));assert.deepEqual(bytes,Array.from(new FixtureUint8Array(new FixtureBigUint64Array([raw]).buffer)));assert.throws(()=>cenv.cell(observed,'char').value,/unsafe pointer dereference/);checks+=4;}
assert.equal(Number(0x20000000000000n),Number(0x20000000000001n));assert.throws(()=>cenv.ptr(Number(0x20000000000001n)),/inexact Number pointer/);checks+=2;
m._probe_reset();const seen=[];let entered=false;
const B=Object.assign(Object.create(base),{nh_getenv:()=>{seen.push('B');return m._probe_buffer(0);}});
const A=Object.assign(Object.create(base),{nh_getenv:()=>{seen.push('A');if(!entered){entered=true;callUnixmain(B,'whoami');put(m,fieldAddress(m,'svp.plname'),'');return 0;}return m._probe_buffer(0);}});
callUnixmain(A,'whoami');assert.deepEqual(seen,['A','B','A'],'nested calls use current services then restore caller services');checks++;
const bad=Object.assign(Object.create(base),{nh_getenv:()=>{throw Error('scoped service throw');}});put(m,fieldAddress(m,'svp.plname'),'');assert.throws(()=>callUnixmain(bad,'whoami'),/scoped service throw/);put(m,fieldAddress(m,'svp.plname'),'');assert.doesNotThrow(()=>callUnixmain(base,'whoami'));checks+=2;
const other=await create(1);other._probe_reset();const otherPw=call(other,'get_unix_pw'),originalPw=call(m,'get_unix_pw');m._probe_passwd_set(originalPw,buffer(m,'only first Module',2),23,45);assert.equal(decode(other,other._probe_passwd_string(otherPw,0)),'root');assert.equal(other._probe_passwd_uid(otherPw),0n);checks+=2;
// Repeated source frames and native callbacks must not accumulate stack storage.
for(let i=0;i<64;i++){m._probe_reset();const sp=m.stackSave();call(m,'sethanguphandler',[m._probe_function(1)]);assert.equal(m.stackSave(),sp);checks++;}
const mainCase=async(label,setup=()=>{},args=[])=>{const out=[];for(let i=0;i<2;i++){const m=await create(i);m._probe_reset();setup(m);let result,error=null;const sp=m.stackSave();try{result=m.callMain([...args]);}catch(e){error={name:e.name,message:e.message,status:e.status};if(process.env.UNIXMAIN_DEBUG)console.error(e.stack);}finally{m.stackRestore(sp);}assert.equal(result,0,'callMain catches ExitStatus and returns status0');assert.deepEqual(m.exits,[0],'real exit invokes onExit with status0');checks+=2;out.push({...observe(m,'main',result??0),error,output:m.output,exits:m.exits});}equal(out[0],out[1],label);assert.equal(out[0].error,null,label);assert.match(out[0].state,/alias:1\/1;/,'original argv0 aliases survive replacement argv');checks++;invoked.add('main');cases.push({label,function:'main',observation:out[0]});return out[0];};
await mainCase('real callMain new game');
for(const [label,setup,args] of [
 ['explicit user debug options',()=>{},['-u','Ada-Lovelace','-D']],
 ['startup argc argv dir cells',m=>{option(m,1);argv(m,['alternate','-u','Changed','-X'],1);},['-u','Original']],
 ['resume success',m=>{option(m,3);option(m,4);field(m,'iflags.news',1);field(m,'program_state.in_self_recover',1);},[]],
 ['resume raw output keep file',m=>{option(m,3);option(m,4);option(m,5,121);field(m,'flags.explore',1);field(m,'ge.early_raw_messages',1);},[]],
 ['resume delete file',m=>{option(m,3);option(m,4);field(m,'flags.debug',1);},[]],
 ['recover failure new game',m=>{option(m,3);field(m,'iflags.news',1);},[]],
 ['empty initial name then selection restore retry',m=>{env(m,'USER','');env(m,'LOGNAME','');option(m,11);option(m,2);buffer(m,'',12);},[]],
 ['selection rename restore retry',m=>{option(m,11);option(m,12);option(m,3,0);},[]],
 ['panic save prompt',m=>option(m,6),[]],
 ['callback memory growth',m=>option(m,30),[]],
 ['callback source reentry',m=>option(m,32),[]],
 ['wizard message precedence',m=>{field(m,'iflags.wiz_error_flag',1);field(m,'sysopt.wizards',buffer(m,'root other'));},[]],
])await mainCase('real callMain '+label,setup,args);
// Direct entry throws the SDK ExitStatus; callMain above catches the same status.
const directExit=[];
for(let i=0;i<2;i++){const module=await create(i);module._probe_reset();const args=argv(module,['nethack','-u','Direct']);const sp=module.stackSave();let caught;try{module._main(3,BigInt(args));}catch(e){caught=e;}finally{module.stackRestore(sp);}assert.equal(caught?.name,'ExitStatus');assert.equal(caught?.status,0);assert.deepEqual(module.exits,[0]);checks+=3;directExit.push({name:caught.name,status:caught.status,trace:trace(module),state:decode(module,module._probe_finished())});}
equal(directExit[0],directExit[1],'actual entry ExitStatus contract');
const scalarAddress=BigInt(mods[0]._probe_buffer(0));const scalar=run('seed scalar equals memory address bits','sys_random_seed',module=>{env(module,'NETHACK_SEED',null);try{module.FS.unlink('/dev/random');}catch{}option(module,70,0);option(module,71,scalarAddress);});assert.equal(scalar.result,String(scalarAddress));checks++;
call(mods[1],'get_login_name');for(let i=0;i<2;i++){assert.equal(BigInt(latestServices.functionAddress(i)),BigInt(mods[1]._probe_function(i)));checks++;}
assert.equal(BigInt(latestServices.teleport_native_signal(3,1)),1n,'function-pointer return preserves SIG_IGN exactly');checks++;
for(const {label,observation:o} of cases){
 if(label.startsWith('strtoul exact ')){const v=JSON.parse(label.slice(14)),expected={'':0n,'0':0n,'-1':-1n,'18446744073709551615':-1n,'18446744073709551616':-1n,'9007199254740993':9007199254740993n,'  +12tail':12n,'0xff':0n,'garbage':0n};assert.equal(o.result,String(expected[v]));assert.equal(o.trace,'');assert.match(o.state,/strong:1;/);checks+=3;}
 if(label.startsWith('actual entropy file ')){const text=label.slice(20),bytes=text?text.split('/').map(Number):[];let value=0n;bytes.forEach((x,i)=>value|=BigInt(x)<<BigInt(i*8));assert.equal(o.result,String(BigInt.asIntN(64,value)));assert.equal(o.trace,'getpid:42;');assert.match(o.state,/strong:1;/);checks+=3;}
 if(label.startsWith('fallback seed ')){const[pid,time]=label.slice(14).split('/').map(BigInt);let factor=BigInt.asUintN(64,pid);if(factor&&(factor&3n)===0n)factor--;const expected=BigInt.asIntN(64,time*(factor||1n));assert.equal(o.result,String(expected));assert.equal(o.trace,`getpid:${pid};paniclog:sys_random_seed/falling back to weak seed;getnow:${time};`);assert.match(o.state,/strong:0;/);checks+=3;}
 if(label==='whoami /Logger/')assert.match(o.state,/name:Logger\/0;/);
}
assert.equal(invoked.size,15);checks++;
if(process.env.UNIXMAIN_EVIDENCE_PATH)await writeFile(resolve(process.env.UNIXMAIN_EVIDENCE_PATH),JSON.stringify({checks,functions:[...invoked],cases},null,2)+'\n');
console.log(JSON.stringify({checks,functions:invoked.size,backend:'actual O2-g memory64 original sys/unix/unixmain.c vs JS',native:false},null,2));
