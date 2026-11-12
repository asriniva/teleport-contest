// Configured C/JS differential first-pass fixture; this is not native-host parity.
import assert from 'node:assert/strict';
import { readFile, writeFile, mkdir } from 'node:fs/promises';
import { resolve } from 'node:path';
import { spawnSync } from 'node:child_process';
import { checkWizcmdsSource } from '../nethack-c/wasm/tu-fragments/wizcmds-source-check.mjs';
import { pathToFileURL } from 'node:url';
import { C, withCEnvironment } from '../js/c-runtime/context.js';
import { createWizcmdsEnvironment, callWizcmds } from '../js/nethack/bindings/wizcmds.js';
import * as core from '../js/ported/wizcmds.js';
const dir=resolve(process.env.WIZCMDS_PROBE_DIR??'.cache/wizcmds-author');
const schema=JSON.parse(await readFile('nethack-c/wasm/tu-fragments/wizcmds-schema.json','utf8'));
if(process.argv.includes('--build')) {
 await mkdir(dir,{recursive:true});
 checkWizcmdsSource();
 const exports=['probe_option_name','probe_reset','probe_option','probe_pointer','probe_canonical','probe_trace','probe_stack','probe_layout_count','probe_layout_name','probe_layout_value','teleport_wizcmds_global','teleport_wizcmds_read','teleport_wizcmds_write','teleport_wizcmds_address',...schema.functions.map(f=>'probe_call_'+f.name)];
 const defines=JSON.parse(await readFile('nethack-c/wasm/compile-defines.json','utf8'));
 const base=['-O2','-sMEMORY64=1','-sMODULARIZE=1','-sENVIRONMENT=node','-sALLOW_MEMORY_GROWTH=1','--no-entry','-sEXPORTED_RUNTIME_METHODS=HEAPU8','-sEXPORTED_FUNCTIONS='+JSON.stringify(exports.map(s=>'_'+s)),...defines.map(s=>'-D'+s),'-I'+resolve('.cache/wasm64-build/tree/include'),'-I'+resolve('.cache/ncurses-wasm64-build/include'),'-I'+resolve('scripts'),'-fmacro-prefix-map='+resolve('scripts')+'/../.cache/wasm64-build/tree/src/=',resolve('scripts/tu-wizcmds-probe.c')];
 for(const mode of ['reference','hybrid']) {
  const args=[...base,...(mode==='hybrid'?['-DHYBRID_WIZCMDS=1','--js-library',resolve('nethack-c/wasm/tu-libraries/wizcmds.js')]:[]),'-o',resolve(dir,'wizcmds-'+mode+'.mjs')];
  const result=spawnSync(resolve('.cache/emsdk/upstream/emscripten/emcc'),args,{encoding:'utf8',maxBuffer:32*1024*1024});
  await writeFile(resolve(dir,'build-'+mode+'-'+Date.now()+'.log'),JSON.stringify({args,status:result.status})+'\n'+result.stdout+result.stderr);
  if(result.status!==0)throw Error('WIZCMDS '+mode+' build failed; see private build log');
 }
}
const importTable=WebAssembly.Module.imports(new WebAssembly.Module(await readFile(resolve(dir,'wizcmds-hybrid.wasm'))));
const importedNames=new Set(importTable.filter(e=>e.kind==='function').map(e=>e.name));
for(const f of schema.functions)assert.ok(importedNames.has(f.static?'teleport_wizcmds_test_'+f.name:f.name),'hybrid imports JS policy for '+f.name);
const factories=await Promise.all(['reference','hybrid'].map(async mode=>(await import(pathToFileURL(resolve(dir,'wizcmds-'+mode+'.mjs')).href)).default));
const text=(m,p)=>{let n=Number(p),end=n;while(m.HEAPU8[end])end++;return Buffer.from(m.HEAPU8.slice(n,end)).toString('latin1');};
function layout(m){const out={};for(let i=0;i<m._probe_layout_count();i++)out[text(m,m._probe_layout_name(i))]=m._probe_layout_value(i);return out;}
const reference=await factories[0](),L=layout(reference),servicesByModule=new WeakMap(),environments=new WeakMap();
const callbackCalls=new Map();
const runtime={wizcmds(services,name,...args){callbackCalls.set(name,(callbackCalls.get(name)??0)+1);servicesByModule.set(services.moduleKey,services);environments.set(services.moduleKey,createWizcmdsEnvironment(services,L,core));return callWizcmds(services,L,name,...args);}};
const hybrid=await factories[1]({nethackPorted:runtime}),modules=[reference,hybrid];
assert.deepEqual(layout(hybrid),L);
const N=k=>Number(BigInt.asIntN(64,L[k]));
const options={};for(let i=0;;i++){const p=reference._probe_option_name(i);if(!p)break;options[text(reference,p)]=i;}
const kinds=Object.keys(schema.schema),globals=schema.globals,stacks=modules.map(m=>m._probe_stack());
let cases=0,comparisons=0,active='';const invoked=new Set();
const both=(name,...args)=>modules.map(m=>m['_probe_'+name](...args));
const ptr=(m,k,i=0)=>m._probe_pointer(k,i);
const global=(m,n)=>m._teleport_wizcmds_global(globals.findIndex(g=>g.name===n));
function write(m,kind,at,name,v){const i=schema.schema[kind].fields.findIndex(f=>f.name===name);assert.notEqual(i,-1,kind+'.'+name);m._teleport_wizcmds_write(kinds.indexOf(kind),at,i,BigInt.asUintN(64,BigInt(v)));}
function read(m,kind,at,name){const i=schema.schema[kind].fields.findIndex(f=>f.name===name);assert.notEqual(i,-1,kind+'.'+name);return m._teleport_wizcmds_read(kinds.indexOf(kind),at,i);}
function nested(m,g,path){let d=globals.find(x=>x.name===g).d,at=global(m,g);for(const name of path){const f=schema.schema[d.s].fields.find(x=>x.name===name);assert.ok(f,g+'.'+path);at=read(m,d.s,at,name);d=f.d;}return{d,at};}
function gfield(g,n,v){for(const m of modules)write(m,globals.find(x=>x.name===g).d.s,global(m,g),n,typeof v==='function'?v(m):v);}
function nfield(g,path,n,v){for(const m of modules){const x=nested(m,g,path);write(m,x.d.s,x.at,n,typeof v==='function'?v(m):v);}}
function pfield(kind,k,i,n,v){for(const m of modules)write(m,kind,ptr(m,k,i),n,typeof v==='function'?v(m):v);}
function option(n,v){const i=typeof n==='number'?n:options[n];assert.notEqual(i,undefined,n);both('option',i,v);}
function input(s){for(const m of modules)m.HEAPU8.set(Buffer.from(s+'\0','latin1'),Number(ptr(m,5)));}
function property(p,member,v){for(const m of modules){const at=read(m,'you',global(m,'u'),'uprops')+BigInt(N(p)*N('propSize'));write(m,'prop',at,member,v);}}
const width=d=>d.t?Number(d.t.slice(1))/8:d.p!==undefined||d.f?8:d.s?N(d.s+'Size'):d.a.reduce((a,b)=>a*b,1)*width(d.e);
function state(m){const out=[];const dv=new DataView(m.HEAPU8.buffer);
 const value=(d,at,ct='')=>{if(d.s){for(const [i,f]of schema.schema[d.s].fields.entries()){const v=m._teleport_wizcmds_read(kinds.indexOf(d.s),at,i);if(f.d.s||f.d.a)value(f.d,v,f.ctype);else scalar(f.d,v,f.ctype);}return;}
  if(d.a){const child=d.a.length===1?d.e:{a:d.a.slice(1),e:d.e};let size=d.a[0];if(d.a[0]===N('MAX_GLYPH'))size=8;for(let i=0;i<size;i++)value(child,at+BigInt(i*width(child)),ct.replace(/\[\d*\]/g,''));return;}
  scalar(d,dv.getBigUint64(Number(at),true)&((1n<<BigInt(width(d)*8))-1n),ct);};
 const scalar=(d,v,ct)=>{if(d.p!==undefined){if(/^(?:const )?char \*(?:const)?$/.test(ct)){out.push(v?text(m,v):null);}else out.push(m._probe_canonical(v).toString());}
  else if(d.f)out.push(v?1:0);else out.push(v.toString());};
 for(const g of globals)value(g.d,global(m,g.name),['levltyp','known_handling'].includes(g.name)?'const char *':g.ctype??'');
 for(const [kind,k,count]of [['monst',0,8],['obj',1,16],['trap',4,4],['engr',7,4],['mextra',8,8],['oextra',9,16],['d_level',10,1],['mi',12,8],['damage',15,4],['kinfo',16,4],['cemetery',17,4]])for(let i=0;i<count;i++)value({s:kind},ptr(m,k,i));
 for(let i=0;i<8;i++)out.push(dv.getBigInt64(Number(ptr(m,11,i)),true).toString());
 return out;
}
function compare(){assert.deepEqual(state(hybrid),state(reference),'WIZCMDS state '+active);assert.equal(text(hybrid,hybrid._probe_trace()),text(reference,reference._probe_trace()),'WIZCMDS trace '+active);comparisons+=2;for(let i=0;i<2;i++){assert.equal(modules[i]._probe_stack(),stacks[i],'restored C stack');comparisons++;}assert.equal(C,undefined);}
function reset(label){active=label;cases++;both('reset');}
function action(name,...args){if(process.env.WIZCMDS_VERBOSE)console.log(active,name);invoked.add(name);const values=modules.map(m=>m['_probe_call_'+name](...args.map(a=>typeof a==='function'?a(m):a)));assert.equal(values[1],values[0],name+' result '+active);comparisons++;compare();return values;}
const initial=Object.keys(core).map(name=>[name]);
const argMap={makemap_unmakemon:[m=>ptr(m,0),0],size_obj:[m=>ptr(m,1)],count_obj:[m=>ptr(m,1),m=>ptr(m,11),m=>ptr(m,11,1),1,1],obj_chain:[7,m=>ptr(m,14),m=>ptr(m,1),1,m=>ptr(m,11),m=>ptr(m,11,1)],mon_invent_chain:[7,m=>ptr(m,14),m=>ptr(m,0),m=>ptr(m,11),m=>ptr(m,11,1)],contained_stats:[7,m=>ptr(m,14),m=>ptr(m,11),m=>ptr(m,11,1)],size_monst:[m=>ptr(m,0),1],mon_chain:[7,m=>ptr(m,14),m=>ptr(m,0),1,m=>ptr(m,11),m=>ptr(m,11,1)],misc_stats:[7,m=>ptr(m,11),m=>ptr(m,11,1)],list_migrating_mons:[m=>ptr(m,10)],migrsort_cmp:[m=>ptr(m,18),m=>ptr(m,18)],wizcustom_callback:[7,0,m=>ptr(m,14)]};
for(const [name]of initial){reset('initial '+name);if(name==='migrsort_cmp')for(const m of modules)new DataView(m.HEAPU8.buffer).setBigUint64(Number(ptr(m,18)),ptr(m,0),true);action(name,...(argMap[name]??[]));}
// Wizard-only routes, configured sandbox fields and dynamic command identities.
for(const name of ['wiz_wish','wiz_identify','wiz_makemap','wiz_map','wiz_genesis','wiz_where','wiz_detect','wiz_load_lua','wiz_load_splua','wiz_level_tele','wiz_custom','wiz_intrinsic']) {
 reset('wizard enabled '+name);gfield('flags','debug',1);input('fixture.lua');action(name);
}
for(const answer of [48,49,50,51,52,27]){reset('flip answer '+answer);gfield('flags','debug',1);option(205,answer);action('wiz_flip_level');}
for(const level of ['1','3','10','30','999','-5','10extra','  12  ','']){reset('levelchange '+level);input(level);action('wiz_level_change');}
// wmodes uses WINDOWPORT/wp_id; map_levltyp explicitly compares the name.
for(const [name,id]of [['tty',N('wp_tty')+1],['fixture',N('wp_tty')]]) {
 reset('window identity '+name+'/'+id);input(name);gfield('windowprocs','name',m=>ptr(m,5));gfield('windowprocs','wp_id',id);action('wiz_map_levltyp');action('wiz_show_wmodes');
}
reset('non-null special level and branch array pointer');option(214,1);for(const m of modules){const proto=read(m,'s_level',ptr(m,20),'proto');m.HEAPU8.set(Buffer.from('oracle-special\0','latin1'),Number(proto));const flags=read(m,'s_level',ptr(m,20),'flags');write(m,'d_flags',flags,'maze_like',1);write(m,'d_flags',flags,'town',1);const dungeons=nested(m,'svd',['dungeons']).at;const dname=read(m,'dungeon',dungeons+6n*BigInt(N('dungeonSize')),'dname');m.HEAPU8.set(Buffer.from('The laboratories\0','latin1'),Number(dname));}
for(const m of modules){const uz=read(m,'you',global(m,'u'),'uz');write(m,'d_level',uz,'dnum',6);}action('wiz_map_levltyp');
for(const value of [0,1,3]){reset('panic fuzzer '+value);gfield('iflags','debug_fuzzer',value);action('wiz_panic');}
for(const yes of [0,1])for(const answer of [110,121]){reset('fuzzer '+yes+'/'+answer);option('paranoid_query',yes);option(205,answer);action('wiz_fuzzer');}
// Cursor commands follow actual target, visibility, prefix and polymorph routes.
for(const command of ['wiz_kill','wiz_telekinesis','wiz_smell'])for(const target of ['hero','monster','none'])for(const prefix of [0,1]) {
 reset(command+' '+target+' prefix'+prefix);option(204,0);option(206,1);option('olfaction',1);option('canseemon',7);gfield('iflags','menu_requested',prefix);
 if(target!=='hero'){option(202,21);for(const m of modules){const level=nested(m,'svl',['level']);const at=read(m,'dlevel_t',level.at,'monsters');new DataView(m.HEAPU8.buffer).setBigUint64(Number(at)+((21*N('ROWNO')+10)*N('pointerSize')),target==='monster'?ptr(m,0):0n,true);}}
 action(command);
}
reset('sanity recovery fields');gfield('u','uswallow',1);gfield('u','uhp',100);gfield('u','uen',100);gfield('u','umonnum',N('PM_GRID_BUG'));gfield('u','mh',200);action('you_sanity_check');
reset('sanity recursion suppression');gfield('iflags','sanity_no_check',1);action('sanity_check');
reset('underwater vision exemption');gfield('u','uinwater',1);action('levl_sanity_check');
// Every object/monster extension and container recursion contributes exact sizes.
reset('object and monster extensions');
for(let i=0;i<3;i++){pfield('obj',1,i,'oextra',m=>ptr(m,9,i));pfield('oextra',9,i,'oname',m=>ptr(m,14,i));pfield('oextra',9,i,'omailcmd',m=>ptr(m,14,i+1));pfield('oextra',9,i,'omonst',m=>ptr(m,0,i));pfield('monst',0,i,'mextra',m=>ptr(m,8,i));pfield('mextra',8,i,'mgivenname',m=>ptr(m,14,i+2));}
pfield('obj',1,0,'nobj',m=>ptr(m,1,1));pfield('obj',1,0,'cobj',m=>ptr(m,1,2));pfield('obj',1,2,'cobj',m=>ptr(m,1,3));
action('count_obj',m=>ptr(m,1),m=>ptr(m,11),m=>ptr(m,11,1),1,1);
action('obj_chain',7,m=>ptr(m,14),m=>ptr(m,1),0,m=>ptr(m,11),m=>ptr(m,11,1));
pfield('monst',0,0,'minvent',m=>ptr(m,1));pfield('monst',0,0,'nmon',m=>ptr(m,0,1));nfield('svl',['level'],'monlist',m=>ptr(m,0));
action('mon_invent_chain',7,m=>ptr(m,14),m=>ptr(m,0),m=>ptr(m,11),m=>ptr(m,11,1));
action('contained_stats',7,m=>ptr(m,14),m=>ptr(m,11),m=>ptr(m,11,1));
for(const field of ['egd','epri','eshk','emin','edog','ebones'])pfield('mextra',8,0,field,m=>ptr(m,5));
pfield('monst',0,0,'wormno',3);option('size_wseg',123);action('size_monst',m=>ptr(m,0),1);action('size_monst',m=>ptr(m,0),0);
// Native qsort calls the imported JS comparator through the actual callback table.
for(const choice of [99,110,111,97,113,32]){
 reset('migration list '+choice);option(205,choice);
 for(let i=0;i<5;i++){pfield('monst',0,i,'nmon',i<4?m=>ptr(m,0,i+1):0);pfield('monst',0,i,'mux',i===0?1:i===1?1:3-(i%2));pfield('monst',0,i,'muy',i===0?3:i===1?4:9-i);pfield('monst',0,i,'m_id',i===4?0xffffffff:9-i);}
 gfield('gm','migrating_mons',m=>ptr(m,0));action('list_migrating_mons',m=>ptr(m,10));
}
// Configured DEBUG_MIGRATING_MONS creates or migrates existing monsters.
for(const count of ['0','1','3','-3','2000']){reset('debug migration count '+count);input(count);option(215,1);option(216,1);for(let i=0;i<3;i++)pfield('monst',0,i,'nmon',i<2?m=>ptr(m,0,i+1):0);nfield('svl',['level'],'monlist',m=>ptr(m,0));action('wiz_migrate_mons');}
// Exact snprintf function/line arguments and float32 arithmetic are visible.
reset('zero object class probability');for(let i=0;i<N('NUM_OBJECTS');i++)pfield('objclass',3,i,'oc_prob',0);action('wiz_objprobs');
reset('monster difficulty discrepancies');pfield('permonst',2,1,'difficulty',9);pfield('permonst',2,1,'mlevel',100);action('wiz_mon_diff');
reset('glyph customization globals');gfield('flags','debug',1);
// The menu path also reads known_handling; symbol-set indexing is explicit below.
for(const m of modules){const at=read(m,'instance_globals_s',global(m,'gs'),'symset');write(m,'symsetentry',at,'name',ptr(m,14));write(m,'symsetentry',at,'handling',1);}
option(212,1);pfield('glyph_map_entry',13,0,'customcolor',0x123456);action('wiz_custom');
reset('glyph unicode binary bytes');pfield('glyph_map_entry',13,0,'u',m=>ptr(m,19));pfield('unicode_representation',19,0,'utf32ch',0x1f600);pfield('unicode_representation',19,0,'utf8str',m=>ptr(m,5));input(String.fromCharCode(0xf0,0x9f,0x98,0x80));action('wizcustom_callback',7,0,m=>ptr(m,14));
// All timed-property switch arms (including the original goto feedback path).
for(const prop of ['BLINDED','DEAF','HALLUC','SICK','SLIMED','STONED','STUNNED','VOMITING','WARN_OF_MON','GLIB','CONFUSION','LEVITATION','FLYING','WWALKING','HALLUC_RES','FIRE_RES']){
 reset('intrinsic '+prop);gfield('flags','debug',1);option(207,1);option(208,N(prop));option(209,1);option(210,1);property(prop,'intrinsic',10n);action('wiz_intrinsic');
}
// Source statistics retain native-width counters beyond Number precision.
reset('all statistics');for(const name of ['engr_stats','light_stats','timer_stats','region_stats'])option(name,3);action('wiz_show_stats');
// Memory growth and nested same-TU callbacks must refresh views and restore scope.
reset('growth and same TU RNG reentry');gfield('flags','debug',1);option(207,1);option(208,N('SICK'));option(209,1);option(210,1);option(211,1);option(200,1);const oldBuffers=modules.map(m=>m.HEAPU8.buffer);action('wiz_intrinsic');for(let i=0;i<2;i++){assert.notEqual(modules[i].HEAPU8.buffer,oldBuffers[i]);comparisons++;}
// Prove a scalar equal to a native address is not normalized as a pointer.
reset('coincident scalar negative control');const coincident=ptr(reference,0);gfield('iflags','colorcount',coincident);write(hybrid,'instance_flags',global(hybrid,'iflags'),'colorcount',coincident+1n);assert.throws(compare,/WIZCMDS state/);comparisons++;
// Independent modules do not share native views or mutable dependency scope.
const hybrid2=await factories[1]({nethackPorted:runtime});hybrid2._probe_reset();hybrid2._probe_call_wiz_wish();
const primary=servicesByModule.get(hybrid),secondary=servicesByModule.get(hybrid2);assert.ok(primary&&secondary);comparisons++;
assert.notEqual(environments.get(hybrid).view('monst',ptr(hybrid,0)),environments.get(hybrid2).view('monst',ptr(hybrid2,0)));comparisons++;
reset('independent module callback reentry');
const marker={rectState:{sentinel:'R'},trackState:{sentinel:'T'}};
const nestedServices=new Proxy(primary,{get(o,key){if(key==='pline_pp')return (...args)=>{const previous=C;hybrid2._probe_call_wiz_show_nhuuid();assert.equal(C,previous);comparisons++;return o[key](...args);};return Reflect.get(o,key);}});
withCEnvironment(marker,()=>{callWizcmds(nestedServices,L,'wiz_wish');assert.equal(C,marker);comparisons++;});assert.equal(C,undefined);comparisons++;
// This boundary-only injected transport failure is not a claim of panic parity.
reset('transport error restores stack and scope');option('paranoid_query',1);
const failure=new Error('controlled transport failure');
const failingServices=new Proxy(primary,{get(o,key){return key==='panic_p'?()=>{throw failure;}:Reflect.get(o,key);}});
withCEnvironment(marker,()=>{assert.throws(()=>callWizcmds(failingServices,L,'wiz_panic'),e=>e===failure);assert.equal(C,marker);comparisons+=2;});assert.equal(hybrid._probe_stack(),stacks[1]);assert.equal(C,undefined);comparisons+=2;
assert.equal(invoked.size,48);assert.ok(callbackCalls.get('migrsort_cmp')>1,'native qsort reenters JS comparator');comparisons++;
console.log(`wizcmds: ${cases} cases, ${comparisons} EmC/JS state/trace/result/stack checks, ${invoked.size}/48 routines; native host pending`);
await writeFile(resolve(dir,'summary.json'),JSON.stringify({status:'pass',oracle:'configured Emscripten memory64 original source',nativeHost:'pending',cases,comparisons,functions:invoked.size,jsPolicyImports:schema.functions.length,nativeCallbackCalls:Object.fromEntries(callbackCalls)},null,2)+'\n');
