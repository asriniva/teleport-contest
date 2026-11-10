import {spawnSync} from 'node:child_process';
import {mkdirSync,writeFileSync} from 'node:fs';
import {Session} from 'node:inspector';
import assert from 'node:assert/strict';
import {resolve} from 'node:path';
import {pathToFileURL} from 'node:url';
import {writeFile,readFile} from 'node:fs/promises';
import {createWasmLuaRuntime} from '../js/services/wasm-lua-runtime.js';
import {createLuaBytecodeVM} from '../js/services/lua-bytecode-vm.js';
import {callNhlua} from '../js/ported/nhlua-runtime.js';
import {nhluaSchema as schema} from '../js/ported/nhlua.js';
import {C} from '../js/ported/c-runtime.js';
const session=new Session();session.connect();const post=(method,params={})=>new Promise((ok,no)=>session.post(method,params,(e,r)=>e?no(e):ok(r)));await post('Profiler.enable');await post('Profiler.startPreciseCoverage',{callCount:true,detailed:true});
const invoked=new Set();
const directory=resolve('.cache/nhlua-author');
const backend=process.argv.includes('--backend=js')?'js':'c',suffix=backend==='js'?'-js':'';
if(process.argv.includes('--build')){
 const defines=JSON.parse(await readFile('nethack-c/wasm/compile-defines.json','utf8'));
 const exports=[...schema.functions.map(f=>'probe_call_'+f.name),...['callback','allocator','hook','warning','table_int'].map(n=>'probe_consumer_'+n),...['trace','clear_trace','option','stack','alloc','free','lua','lua_load','lua_run','lua_text','lua_integer','lua_type','lua_top','lua_settop','lua_string','lua_integer_push','lua_boolean','lua_table','lua_field','lua_global','lua_close','setup','grow','core','core_state','world','data','function_name','chains','snapshot','mutate','callback_pointer','loglua','userdata','nudfield','lua_boolean_value','lua_number','lua_isinteger'].map(n=>'probe_'+n)];
 mkdirSync(directory,{recursive:true});
 writeFileSync(resolve(directory,'probe-library.js'),"addToLibrary({probe_js_reentry__sig:'v',probe_js_reentry:function(){Module.nhluaProbeReentry();},probe_js_fatal__deps:['$UTF8ToString'],probe_js_fatal__sig:'vp',probe_js_fatal:function(message){throw new Error('fixture-fatal:'+UTF8ToString(Number(message)));}});\n");
 for(const mode of ['reference','hybrid']){
  const args=['-O2','-g','-fno-lto','-sMEMORY64=1','-sMODULARIZE=1','-sENVIRONMENT=node','-sALLOW_MEMORY_GROWTH=1','-sEXPORTED_RUNTIME_METHODS=HEAPU8,FS','--no-entry',...defines.map(v=>'-D'+v),'-I'+resolve('.cache/wasm64-build/tree/include'),'-I'+resolve('.cache/ncurses-wasm64-build/include'),'-I'+resolve('scripts'),'-I'+resolve('.cache/wasm64-build/tree/lib/lua-5.4.8/src'),'-I'+resolve('nethack-c/wasm/tu-fragments'),'-include',resolve('nethack-c/wasm/native-terminal.h'),'-fmacro-prefix-map='+process.cwd()+'/scripts/../.cache/wasm64-build/tree/src/=',resolve('scripts/tu-nhlua-probe.c'),resolve('scripts/tu-nhlua-probe-consumer.c'),'--js-library',resolve(directory,'probe-library.js'),'-sEXPORTED_FUNCTIONS='+JSON.stringify(exports.map(n=>'_'+n))];
  if(backend==='js')args.push(resolve('nethack-c/wasm/lua-bridge.c'),'--js-library',resolve('nethack-c/wasm/lua-library.js'));else args.push(resolve('.cache/wasm64-build/liblua-wasm64.a'));
  if(mode==='hybrid')args.push('-DHYBRID_NHLUA=1','--js-library',resolve('nethack-c/wasm/tu-libraries/nhlua.js'));
  args.push('-o',resolve(directory,'probe-'+mode+suffix+'.mjs'));
  const command=resolve('.cache/emsdk/upstream/emscripten/emcc');
  const result=spawnSync(command,args,{encoding:'utf8',maxBuffer:16*1024*1024});
  writeFileSync(resolve(directory,'final-build-'+mode+suffix+'.json'),JSON.stringify({command,args},null,2)+'\n');
  writeFileSync(resolve(directory,'final-build-'+mode+suffix+'.log'),result.stdout+result.stderr);
  assert.equal(result.status,0,result.stderr);
 }
}
const rf=(await import(pathToFileURL(resolve(directory,'probe-reference'+suffix+'.mjs')))).default,hf=(await import(pathToFileURL(resolve(directory,'probe-hybrid'+suffix+'.mjs')))).default;
const options=()=>({nethackLua:backend==='js'?createWasmLuaRuntime({vmFactory:createLuaBytecodeVM}):undefined});
const runtime={nhlua:(services,name,...args)=>{invoked.add(name);return callNhlua(services,name,...args);}};
const reference=await rf(options());
const hybrid=await hf({...options(),nethackPorted:runtime});
const modules=[reference,hybrid];modules.forEach(m=>m._probe_setup());
for(const file of ['nhlib.lua','nhcore.lua']){const bytes=await readFile('.cache/wasm64-build/tree/dat/'+file);for(const m of modules)m.FS.writeFile(file,bytes);}
const text=(m,p)=>{p=Number(p);let end=p;while(m.HEAPU8[end])end++;return Buffer.from(m.HEAPU8.subarray(p,end)).toString('latin1');};
const string=(m,s)=>{const bytes=Buffer.from(s,'latin1'),at=m._probe_alloc(BigInt(bytes.length+1));m.HEAPU8.set(bytes,Number(at));return at;};
let cases=0,checks=0,label='';const evidence=[];
function compare(values){try{assert.deepEqual(values[1],values[0],label);checks++;evidence.push({label,values});assert.equal(C,undefined);checks++;}catch(error){writeFile(resolve(directory,'failure-'+cases+'.json'),JSON.stringify({label,values},(_,v)=>typeof v==='bigint'?v.toString()+'n':v,2));throw error;}}
function call(name,...args){label=name;invoked.add(name);cases++;const values=modules.map(m=>m['_probe_call_'+name](...args.map(a=>typeof a==='function'?a(m):a)));const ret=schema.functions.find(f=>f.name===name).returnType;compare(values.map((v,i)=>ret.includes('*')?(ret.includes('char')?text(modules[i],v):Boolean(v)):v));compare(modules.map(m=>text(m,m._probe_trace())));return values;}
function stack(m,L){const out=[];for(let i=1;i<=m._probe_lua_top(L);i++){const type=m._probe_lua_type(L,i);out.push(type===3?['number',m._probe_lua_isinteger(L,i)?m._probe_lua_integer(L,i).toString():m._probe_lua_number(L,i)]:type===1?['boolean',m._probe_lua_boolean_value(L,i)]:type===4?['string',text(m,m._probe_lua_text(L,i))]:[type]);}return out;}
function dataImage(m,at,type){
 const v=new DataView(m.HEAPU8.buffer);at=Number(at);
 if(typeof type==='string'){const method={i8:'getInt8',u8:'getUint8',i16:'getInt16',u16:'getUint16',i32:'getInt32',u32:'getUint32',i64:'getBigInt64',u64:'getBigUint64'}[type];return v[method](at,true);}
 if(type.pointer){const p=v.getBigUint64(at,true);if(!p)return null;return type.pointer==='function'?text(m,m._probe_function_name(p)):type.pointer==='char'?text(m,p):'non-null';}
 if(type.record)return Object.fromEntries(schema.records[type.record].fields.map(f=>[f.name,dataImage(m,at+f.offset,f.type)]));
 const element=type.array.length===1?type.of:{array:type.array.slice(1),of:type.of};
 const size=t=>typeof t==='string'?Number(t.slice(1))/8:t.pointer?8:t.record?schema.records[t.record].size:t.array.reduce((n,d)=>n*d,size(t.of));
 return Array.from({length:type.array[0]},(_,i)=>dataImage(m,at+i*size(element),element));
}
// A rejected transport layout must neither publish metadata nor execute source policy.
let rejectLayout=true;
const retryModule=await hf({...options(),nethackPorted:{nhlua:(services,name,...args)=>{
 if(rejectLayout)return callNhlua({...services,layout:{...services.layout,pointerSize:4}},name,...args);
 return callNhlua(services,name,...args);
}}});
assert.throws(()=>retryModule._probe_call_splev_chr2typ(46),/NHLUA ABI pointerSize/);checks++;
assert.equal(retryModule.teleportNhluaTransport.layout,undefined);checks++;
assert.equal(C,undefined);checks++;
rejectLayout=false;
assert.equal(retryModule._probe_call_splev_chr2typ(46),schema.constants.ROOM);checks++;
assert.equal(Object.isFrozen(retryModule.teleportNhluaTransport.layout),true);checks++;
cases++;evidence.push({label:'rejected ABI metadata remains unpublished; genuine retry succeeds',checks:5});
call('splev_chr2typ',46);
assert.notEqual(retryModule.teleportNhluaTransport.layout,hybrid.teleportNhluaTransport.layout);checks++;
assert.equal(Object.isFrozen(hybrid.teleportNhluaTransport.layout),true);checks++;
for(const [index,[name,data]]of Object.entries(schema.data).filter(([,d])=>!d.staticLocal).entries()){
 label='complete native static image '+name;cases++;compare(modules.map(m=>dataImage(m,m._probe_data(index),data.type)));
}

for(let c=0;c<128;c++)call('splev_chr2typ',c);
for(let c=-2;c<55;c++)call('splev_typ2chr',c);
for(const value of ['.','#','|','A','x',''])call('check_mapchr',m=>string(m,value));
let states=modules.map(m=>m._probe_lua());
const state=m=>states[modules.indexOf(m)];
function clear(){modules.forEach(m=>{m._probe_lua_settop(state(m),0);m._probe_clear_trace();});}
function pushString(value){modules.forEach(m=>m._probe_lua_string(state(m),string(m,value)));}
function pushInteger(value){modules.forEach(m=>m._probe_lua_integer_push(state(m),BigInt(value)));}
function compareStack(){compare(modules.map(m=>stack(m,state(m))));}
function compareWorld(){compare(modules.map(m=>text(m,m._probe_snapshot())));}
clear();call('lcheck_param_table',state);compareStack();
clear();modules.forEach(m=>m._probe_lua_table(state(m)));
for(const [name,value]of [['nhl_add_table_entry_int',123456],['nhl_add_table_entry_char',65],['nhl_add_table_entry_bool',1]]){call(name,state,m=>string(m,name),name.endsWith('_int')?BigInt(value):value);modules.forEach(m=>m._probe_lua_field(state(m),1,string(m,name)));compareStack();modules.forEach(m=>m._probe_lua_settop(state(m),1));}
call('nhl_add_table_entry_str',state,m=>string(m,'str'),m=>string(m,'value'));call('get_table_str',state,m=>string(m,'str'));
call('nhl_add_table_entry_str',state,m=>string(m,'map'),m=>string(m,'.'));call('get_table_mapchr',state,m=>string(m,'map'));call('get_table_mapchr_opt',state,m=>string(m,'absent'),schema.constants.ROOM);
const optionsPointer=m=>{const at=m._probe_alloc(24n);const view=new DataView(m.HEAPU8.buffer);view.setBigUint64(Number(at),string(m,'one'),true);view.setBigUint64(Number(at)+8,string(m,'two'),true);return at;};call('get_table_option',state,m=>string(m,'absent'),m=>string(m,'two'),optionsPointer);
call('nhl_add_table_entry_region',state,m=>string(m,'region'),1,2,3,4);
call('get_table_int',state,m=>string(m,'nhl_add_table_entry_int'));compareStack();
call('get_table_int_opt',state,m=>string(m,'absent'),19);compareStack();
for(const value of [-4294967297n,-2147483649n,2147483648n,4294967297n,9223372036854775807n]){call('nhl_add_table_entry_int',state,m=>string(m,'wide'),value);call('get_table_int',state,m=>string(m,'wide'));}
for(const value of ['true','false','yes','no']){call('nhl_add_table_entry_str',state,m=>string(m,'bool'),m=>string(m,value));call('get_table_boolean',state,m=>string(m,'bool'));}
clear();call('init_nhc_data',state);compareStack();
clear();call('init_u_data',state);compareStack();
clear();call('nhlL_openlibs',state,2147483648);compareStack();
clear();
for(const [script,nresults]of [['return 7+8',1],['local s=0 for i=1,100 do s=s+i end return s',1]]){modules.forEach(m=>assert.equal(m._probe_lua_load(state(m),string(m,script)),0));call('nhl_pcall',state,0,nresults,m=>string(m,'fixture'));compareStack();clear();}
for(const script of ["error('fixture error')","return nil.no_such_field"]){modules.forEach(m=>m._probe_lua_load(state(m),string(m,script)));call('nhl_pcall',state,0,1,m=>string(m,'fixture'));compareStack();clear();}
for(const s of ['warning','@off','@on','fixture warning']){call('nhl_warn',0n,m=>string(m,s),0);}
modules.forEach((m,i)=>m._probe_lua_close(states[i]));
const configs=modules.map(m=>{const p=m._probe_alloc(16n);const v=new DataView(m.HEAPU8.buffer);v.setUint32(Number(p),2147483648,true);v.setUint32(Number(p)+4,1048576,true);return p;});
states=call('nhl_init',m=>configs[modules.indexOf(m)]);
assert(states.every(Boolean),'nhl_init source succeeds with actual nhlib.lua');
modules.forEach(m=>m._probe_core(state(m)));
clear();call('nhl_loadlua',state,m=>string(m,'nhcore.lua'));clear();
const coreStates=states;states=call('nhl_init',m=>configs[modules.indexOf(m)]);clear();
const callbackCases=[
 'return nhc.COLNO,nhc.ROWNO,u.ux,u.uy,u.dx,u.dy,u.dz,u.tx,u.ty,u.ulevel,u.ulevelmax,u.uhunger,u.nv_range,u.xray_range,u.umonster,u.umonnum,u.mh,u.mhmax,u.mtimedone,u.dnum,u.dlevel,u.uluck,u.uhp,u.uhpmax,u.uen,u.uenmax,u.moves,u.role,u.depth,u.uhave_amulet,u.invocation_level',
 "nh.pline('fixture %s');nh.verbalize('hello');nh.impossible('controlled');return nh.getlin('question')",
 "return nh.makeplural('cat'),nh.makesingular('cats'),nh.s_suffix('hero'),nh.ing_suffix('run'),nh.an('orb'),nh.eckey('help')",
 'return nh.rn2(11),nh.random(3,7),math.random(3,9),d(2,6)',
 "return nh.level_difficulty(),nh.is_genocided('vampire'),nh.debug_themerm(false)",
 "nh.parse_config('fruit:pear');return nh.get_config('fruit')",
 'return nh.dnum_name(0),nh.int_to_pmname(-1),nh.int_to_objname(-1),nh.int_to_pmname(0),nh.int_to_objname(0)',
 'return #nh.stairways()',
 'u.clear_inventory();u.giveobj(nil)',
 "nh.pushkey('abc');nh.doturn();nh.doturn(true);nh.flip_level(3)",
 'nh.debug_flags({mongen=false,hunger=false,overwrite_stairs=true,prevent_pline=true})',
 'nh.test({x=32769,y=-32770,name="Visitor"})',
 'local ok,err=pcall(nh.gettrap,3,4);return ok,err',
 'nh.deltrap(3,4)',
 "return nh.getmap(3,4).typ_name",
 "return nh.has_timer_at(3,4,'melt-ice'),nh.peek_timer_at({x=5,y=6},'melt-ice')",
 "nh.stop_timer_at(3,4,'melt-ice');nh.start_timer_at({x=3,y=4},'melt-ice',17)",
 "nh.text('fixture text');nh.text('fixture text',1)",
 "nh.menu('choose','a','one',{{key='a',text='first'},{key='b',text='second'}})",
 "return nh.variable('missing')",
 "nh.variable('number',123);return nh.variable('number')",
 "nh.variable('word','fixture');return nh.variable('word')",
 "nh.variable('boolean',true);return nh.variable('boolean')",
 "nh.variable('removed',nil);return nh.variable('removed')",
 "local ok,err=pcall(nh.rn2);return ok,err",
 "local ok,err=pcall(nh.int_to_pmname,'bad');return ok,err",
];
for(const script of callbackCases){
 clear();label=script;const loads=modules.map(m=>m._probe_lua_load(state(m),string(m,script)));compare(loads);
 const results=call('nhl_pcall',state,0,-1,m=>string(m,'callback-fixture'));compareStack();assert.equal(results[0],0,script+' succeeds');
}
function runScript(script){clear();const loads=modules.map(m=>m._probe_lua_load(state(m),string(m,script)));label=script;compare(loads);const results=call('nhl_pcall',state,0,-1,m=>string(m,'directed'));compareStack();assert.equal(results[0],0,script);}
for(const terrain of ['DOOR','ALTAR','THRONE','TREE','FOUNTAIN','SINK'])for(const bits of [0,1,2,4,8,16,31]){
 modules.forEach(m=>m._probe_world(schema.constants[terrain],bits,schema.constants.PIT));
 runScript("local x=nh.getmap(3,4);return x.typ,x.mapchr,x.horizontal,x.lit,x.waslit,x.flags.nodoor,x.flags.broken,x.flags.isopen,x.flags.closed,x.flags.locked,x.flags.trapped,x.flags.shrine,x.flags.looted,x.flags.swarm,x.flags.warned,x.flags.pudding,x.flags.dishwasher,x.flags.ring");
}
modules.forEach(m=>m._probe_option(5,1));
for(const trap of ['SQKY_BOARD','ROLLING_BOULDER_TRAP','PIT','SPIKED_PIT']){
 modules.forEach(m=>m._probe_world(schema.constants.ROOM,0,schema.constants[trap]));
 runScript('local t=nh.gettrap(3,4);return t.tx,t.ty,t.ttyp,t.ttyp_name,t.tseen,t.madeby_u,t.once,t.tnote,t.launchx,t.launchy,t.launch2x,t.launch2y,t.conjoined');
}
modules.forEach(m=>m._probe_option(10,2));runScript("return nh.menu('choose','a','one',{{key='a',text='first'},{key='b',text='second'}})");
modules.forEach(m=>m._probe_option(10,0));
const oldHeaps=modules.map(m=>m.HEAPU8.buffer);modules.forEach(m=>m._probe_option(20,1));runScript("nh.text('growth line one\\nline two');return u.ux,u.uy");modules.forEach((m,i)=>{assert.notEqual(m.HEAPU8.buffer,oldHeaps[i]);checks++;m._probe_option(20,0);});
for(const size of [0,1,255,256,511,1024,2049]){call('nhl_warn',0n,m=>string(m,'x'.repeat(size)),1);call('nhl_warn',0n,m=>string(m,'tail'),0);}
runScript("nh.gamestate();nh.gamestate(true);return u.ux,u.uy,u.moves");
modules.forEach(m=>m._probe_chains(2));runScript('local x=nh.stairways();return #x,x[1].x,x[1].y,x[1].up,x[1].ladder,x[2].dnum,x[2].dlevel');
modules.forEach(m=>m._probe_chains(0));compareWorld();runScript('nh.gamestate()');compareWorld();modules.forEach(m=>m._probe_mutate());compareWorld();runScript('nh.gamestate(true)');compareWorld();runScript('u.clear_inventory()');compareWorld();
modules.forEach(m=>m._probe_chains(1));runScript('nh.debug_flags({mongen=false})');compareWorld();

const auxiliary=await hf({...options(),nethackPorted:runtime});
for(const m of modules){m.nhluaProbeReentry=()=>{const previous=C;assert.equal(auxiliary._probe_call_splev_chr2typ(46),schema.constants.ROOM);assert.equal(C,previous);m._probe_call_nhl_warn(0n,string(m,'nested source warning'),0);assert.equal(C,previous);checks+=3;};m._probe_option(21,1);}
runScript("nh.text('outer callback line');return u.ux,u.uy");modules.forEach(m=>m._probe_option(21,0));
runScript("nh.callback('level_enter','fixture_callback');nh.callback('level_enter','fixture_callback',true)");
runScript("local ok,err=pcall(function()u.ux=17 end);return ok,err");
clear();
modules.forEach((m,i)=>{m._probe_lua_settop(coreStates[i],0);assert.equal(m._probe_lua_load(coreStates[i],string(m,'nh_lua_variables={single=7}')),0);assert.equal(m._probe_lua_run(coreStates[i],0),0);});
call('get_nh_lua_variables');call('save_luadata',0n);call('restore_luadata',0n);call('get_nh_lua_variables');
call('nhl_pushhooked_open_table',state);compareStack();
call('nhl_done',state);states=coreStates;call('l_nhcore_done');
call('get_lua_version');call('get_lua_version');
for(const file of ['nhlib.lua','missing.lua'])call('load_lua',m=>string(m,file),m=>configs[modules.indexOf(m)]);
call('l_nhcore_init');for(const n of [-1,0,1,2,3,4,7])call('l_nhcore_call',n);call('tutorial',0);states=modules.map(m=>m._probe_core_state());modules.forEach(m=>m._probe_chains(0));runScript('nh.gamestate()');compareWorld();call('free_tutorial');compareWorld();call('l_nhcore_done');



// Native signatures are exercised by a separate no-LTO C caller.
for(const counter of [0,4294967,4294968,4294967294,4294967295]){
 const cs=modules.map(m=>{const at=m._probe_alloc(16n),v=new DataView(m.HEAPU8.buffer);v.setUint32(Number(at),2147483648,true);v.setUint32(Number(at)+4,1048576,true);v.setUint32(Number(at)+8,5000,true);return at;});
 states=call('nhlL_newstate',m=>cs[modules.indexOf(m)],m=>string(m,'stat-state'));
 modules.forEach(m=>{m._probe_clear_trace();m._probe_nudfield(state(m),0,counter);m._probe_loglua(1);});
 call('nhl_getmeminuse',state);
 compare(modules.map(m=>m._probe_consumer_callback(m._probe_callback_pointer(0),state(m))));compareStack();clear();
 if(counter===4294967295){modules.forEach(m=>m._probe_consumer_hook(m._probe_callback_pointer(2),state(m),0n));}
 for(const requested of [1n,16n,4096n,4294967297n]){
  const blocks=modules.map(m=>m._probe_consumer_allocator(m._probe_callback_pointer(1),m._probe_userdata(state(m)),0n,0n,requested));
  compare(blocks.map(Boolean));assert(blocks.every(Boolean));
  modules.forEach((m,i)=>assert.equal(m._probe_consumer_allocator(m._probe_callback_pointer(1),m._probe_userdata(state(m)),blocks[i],requested,0n),0n));checks+=2;
 }
 const used=modules.map(m=>m._probe_call_nhl_getmeminuse(state(m)));compare(used);
 const accepted=modules.map((m,i)=>{m._probe_nudfield(state(m),4,used[i]);return m._probe_consumer_allocator(m._probe_callback_pointer(1),m._probe_userdata(state(m)),0n,0n,32n);});compare(accepted.map(Boolean));assert(accepted.every(Boolean));
 const refused=modules.map((m,i)=>{m._probe_nudfield(state(m),4,used[i]-1);return m._probe_consumer_allocator(m._probe_callback_pointer(1),m._probe_userdata(state(m)),accepted[i],32n,64n);});compare(refused);assert(refused.every(p=>p===0n));
 modules.forEach((m,i)=>{assert.equal(m._probe_consumer_allocator(m._probe_callback_pointer(1),m._probe_userdata(state(m)),accepted[i],32n,0n),0n);m._probe_nudfield(state(m),4,1048576);});
 call('nhl_done',state);modules.forEach(m=>m._probe_loglua(0));
}
for(const m of modules){m._probe_clear_trace();m._probe_consumer_warning(m._probe_callback_pointer(3),0n,string(m,'typed warning '),1);m._probe_consumer_warning(m._probe_callback_pointer(3),0n,string(m,'end'),0);}compare(modules.map(m=>text(m,m._probe_trace())));

const nudRecord=schema.records.nhl_user_data;
const nudOffset=name=>nudRecord.fields.find(f=>f.name===name).offset;
async function quotaCase(steps,perpcall,source,fatal){
 const ms=[await rf(options()),await hf({...options(),nethackPorted:runtime})];
 const observed=[];
 for(const m of ms){
  m._probe_setup();const config=m._probe_alloc(16n),dv=new DataView(m.HEAPU8.buffer),at=Number(config);
  for(const [offset,value]of [[0,2147483648],[4,1048576],[8,steps],[12,perpcall]])dv.setUint32(at+offset,value,true);
  const L=m._probe_call_nhlL_newstate(config,string(m,'quota-state'));
  const ud=Number(m._probe_userdata(L));assert(ud);
  assert.equal(m._probe_lua_load(L,string(m,source)),0);
  let status,message='';try{status=m._probe_call_nhl_pcall(L,0,1,string(m,'quota-case'));}catch(error){message=error.message;}
  const v=new DataView(m.HEAPU8.buffer);
  const result={status,message,trace:text(m,m._probe_trace()),steps:v.getUint32(ud+nudOffset('steps'),true),statctr:v.getUint32(ud+nudOffset('statctr'),true)};
  if(fatal){assert.equal(message,'fixture-fatal:Lua time exceeded 1:quota-case');assert.equal(status,undefined);if(m.teleportNhluaTransport)assert.equal(m.teleportNhluaTransport.continuations.size,0);/* Fatal callback chains are intentionally abandoned. No Lua API or close follows. */}
  else{assert.equal(message,'');assert.equal(status,0);result.value=m._probe_lua_integer(L,-1).toString();m._probe_call_nhl_done(L);}
  observed.push(result);
 }
 label='quota '+JSON.stringify({steps,perpcall,fatal});cases++;compare(observed);
}


for(const failure of [1,2,3,10,55]){
 const result=[];
 for(const factory of [rf,hf]){
  const m=await factory({...options(),nethackPorted:runtime});m._probe_setup();m._probe_option(30,failure);const config=m._probe_alloc(16n),v=new DataView(m.HEAPU8.buffer);v.setUint32(Number(config),2147483648,true);v.setUint32(Number(config)+4,1048576,true);
  let pointer,message='';try{pointer=m._probe_call_nhlL_newstate(config,string(m,'allocation-refusal'));}catch(error){message=error.message;}
  assert.equal(pointer,undefined);assert.equal(message,'fixture-fatal:controlled re_alloc OOM');
  result.push({pointer,message,trace:text(m,m._probe_trace())});/* Failed construction/fatal panic is never followed by Lua calls. */
 }
 label='native nonreturning allocator panic '+failure;cases++;compare(result);
}

const panics=[];
for(const factory of [rf,hf]){
 const m=await factory({...options(),nethackPorted:runtime});m._probe_setup();const L=m._probe_lua();m._probe_lua_string(L,string(m,'explicit panic fixture'));let message;
 try{m._probe_consumer_callback(m._probe_callback_pointer(4),L);}catch(error){message=error.message;}
 assert.equal(message,'fixture-fatal:unprotected error in call to Lua API (explicit panic fixture)\n');
 panics.push({message,trace:text(m,m._probe_trace())});/* Fatal Module is intentionally abandoned. */
}
label='explicit panic callback';cases++;compare(panics);

for(const steps of [1000,2000,4000])await quotaCase(steps,0,'local s=0 for i=1,100000 do s=s+i end return s',true);
for(const perpcall of [1000,2000,4000])await quotaCase(0,perpcall,'local s=0 for i=1,100000 do s=s+i end return s',true);
await quotaCase(16000,0,'local s=0 for i=1,10 do s=s+i end return s',false);

const coverage=await post('Profiler.takePreciseCoverage');await post('Profiler.stopPreciseCoverage');session.disconnect();const bodies=coverage.result.filter(s=>s.url.endsWith('/js/ported/nhlua.js')).flatMap(s=>s.functions).filter(f=>schema.functions.some(s=>s.name===f.functionName)&&f.ranges[0].count>0).map(f=>f.functionName);
assert.deepEqual([...new Set(bodies)].sort(),schema.functions.map(f=>f.name).sort(),'Every configured original body executed');
const summary={evidence,bodyCoverage:[...new Set(bodies)],status:'PASS',cases,checks,functions:[...invoked],backend,scope:'Configured Emscripten original C versus JS source bodies; native host and whole-game integration pending'};
await writeFile(resolve(directory,'source-result-'+backend+'.json'),JSON.stringify(summary,(_,v)=>typeof v==='bigint'?v.toString()+'n':v,2)+'\n');
console.log(`NHLUA initial source ${cases} cases / ${checks} checks, ${new Set(bodies).size}/94 executed bodies, ${invoked.size} native entry names; ${backend==='js'?'frozen JS Lua':'compiled Lua'}, native host pending`);
