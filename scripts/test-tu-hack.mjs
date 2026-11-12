// Controlled configured original-C versus JS policy. Native-host/game gates are separate.
import assert from 'node:assert/strict';
import {readFile,writeFile,mkdir} from 'node:fs/promises';
import {writeFileSync} from 'node:fs';
import {resolve} from 'node:path';
import {spawnSync} from 'node:child_process';
import {pathToFileURL} from 'node:url';
import {checkHackSource} from '../nethack-c/wasm/tu-fragments/hack-source-check.mjs';
import {C,withCEnvironment} from '../js/c-runtime/context.js';
import {createHackEnvironment,callHack} from '../js/nethack/bindings/hack.js';
import * as core from '../js/ported/hack.js';

if(process.env.TELEPORT_NATIVE_TESTS!=='0')throw Error('HACK has no native reference fixture; set TELEPORT_NATIVE_TESTS=0 only for the explicit Emscripten diagnostic.');
const dir=resolve(process.env.HACK_PROBE_DIR??'.cache/hack-author');
const schema=JSON.parse(await readFile('nethack-c/wasm/tu-fragments/hack-schema.json','utf8'));
if(process.argv.includes('--build')) {
 await mkdir(dir,{recursive:true});checkHackSource();
 const source=await readFile('.cache/wasm64-build/tree/src/hacklib.c','utf8');
 assert.equal(source.split('/*=').length,2,'original prepared deterministic qsort boundary');
 const sort=resolve(dir,'sort-dependency.c');await writeFile(sort,source.split('/*=')[0]);
 const exports=['probe_option_name','probe_reset','probe_option','probe_pointer','probe_canonical','probe_trace','probe_stack','probe_error','probe_layout_count','probe_layout_name','probe_layout_value','probe_pointer_equal','probe_test_constant','probe_callback_pointer','probe_invoke_comparator','probe_foreign_callback','probe_set_afternmv','probe_place_object','probe_room','teleport_hack_global','teleport_hack_read','teleport_hack_write','teleport_hack_address',...schema.functions.map(f=>'probe_call_'+f.name)];
 const defines=JSON.parse(await readFile('nethack-c/wasm/compile-defines.json','utf8'));
 const base=['-O2','-sMEMORY64=1','-sMODULARIZE=1','-sENVIRONMENT=node','-sALLOW_MEMORY_GROWTH=1','-sSTACK_SIZE=4194304','-sSUPPORT_LONGJMP=emscripten','--no-entry','-sEXPORTED_RUNTIME_METHODS=HEAPU8','-sEXPORTED_FUNCTIONS='+JSON.stringify(exports.map(s=>'_'+s)),...defines.map(s=>'-D'+s),'-I'+resolve('.cache/wasm64-build/tree/include'),'-I'+resolve('.cache/ncurses-wasm64-build/include'),'-I'+resolve('scripts'),'-include',resolve('nethack-c/wasm/native-terminal.h'),'-fmacro-prefix-map='+resolve('scripts')+'/../.cache/wasm64-build/tree/src/=',resolve('scripts/tu-hack-probe.c'),sort];
 for(const mode of ['reference','hybrid']) {
  const args=[...base,...(mode==='hybrid'?['-DHYBRID_HACK=1','--js-library',resolve('nethack-c/wasm/tu-libraries/hack.js')]:[]),'-o',resolve(dir,'hack-'+mode+'.mjs')];
  const r=spawnSync(resolve('.cache/emsdk/upstream/emscripten/emcc'),args,{encoding:'utf8',maxBuffer:32*1024*1024});
  await writeFile(resolve(dir,'build-'+mode+'-'+Date.now()+'.log'),JSON.stringify({args,status:r.status})+'\n'+r.stdout+r.stderr);
  if(r.status!==0)throw Error('HACK '+mode+' build failed; see private build log');
 }
}
const imports=new Set(WebAssembly.Module.imports(new WebAssembly.Module(await readFile(resolve(dir,'hack-hybrid.wasm')))).filter(e=>e.kind==='function').map(e=>e.name));
for(const f of schema.functions)assert.ok(imports.has(f.static?'teleport_hack_test_'+f.name:f.name),'JS policy import '+f.name);
for(const name of ['notice_mons_cmp','cmp_weights'])assert.ok(imports.has('teleport_hack_callback_'+name),'dedicated production comparator '+name);
const factories=await Promise.all(['reference','hybrid'].map(async mode=>(await import(pathToFileURL(resolve(dir,'hack-'+mode+'.mjs')).href)).default));
const text=(m,p)=>{let i=Number(p),end=i;assert.ok(i>=0&&i<m.HEAPU8.length,'C string address');while(end<m.HEAPU8.length&&m.HEAPU8[end])end++;assert.ok(end<m.HEAPU8.length,'terminated C string');return Buffer.from(m.HEAPU8.slice(i,end)).toString('latin1');};
function layout(m){const out={};for(let i=0;i<m._probe_layout_count();i++)out[text(m,m._probe_layout_name(i))]=m._probe_layout_value(i);return out;}
const reference=await factories[0](),L=Object.freeze(layout(reference)),environments=new WeakMap(),servicesByModule=new WeakMap(),callbackCalls=new Map();
const runtime={hack(services,name,...args){callbackCalls.set(name,(callbackCalls.get(name)??0)+1);servicesByModule.set(services.moduleKey,services);if(!environments.has(services.moduleKey))environments.set(services.moduleKey,createHackEnvironment(services,L,core));return callHack(services,L,name,...args);}};
const hybrid=await factories[1]({nethackPorted:runtime}),modules=[reference,hybrid];assert.deepEqual(layout(hybrid),L);
const fixtureConstants=['PM_HUMAN','DO_MOVE','TEST_MOVE','TEST_TRAV','TEST_TRAP','ALTAR','NO_KILLER_PREFIX','ROOM','ROWNO','COLNO','OBJ_FLOOR','ARROW_TRAP'];
const N=k=>{if(L[k]!==undefined)return Number(BigInt.asIntN(64,L[k]));const i=fixtureConstants.indexOf(k);assert.notEqual(i,-1,'native fixture constant '+k);return reference._probe_test_constant(i);};
const options={};for(let i=0;;i++){const p=reference._probe_option_name(i);if(!p)break;options[text(reference,p)]=i;}
const kinds=Object.keys(schema.schema),globals=schema.globals,stacks=modules.map(m=>m._probe_stack());
let cases=0,comparisons=0,active='',anyMember='a_long';const invoked=new Set(),observedRng=new Set();
const both=(n,...args)=>modules.map(m=>m['_probe_'+n](...args));
const ptr=(m,k,i=0)=>m._probe_pointer(k,i);
const global=(m,n)=>{const i=globals.findIndex(g=>g.name===n);assert.notEqual(i,-1,n);return m._teleport_hack_global(i);};
function field(kind,name){const i=schema.schema[kind].fields.findIndex(f=>f.name===name);assert.notEqual(i,-1,kind+'.'+name);return i;}
function write(m,kind,at,name,v){m._teleport_hack_write(kinds.indexOf(kind),at,field(kind,name),BigInt.asUintN(64,BigInt(v)));}
function read(m,kind,at,name){return m._teleport_hack_read(kinds.indexOf(kind),at,field(kind,name));}
function nested(m,g,path){let d=globals.find(x=>x.name===g).d,at=global(m,g);for(const name of path){const f=schema.schema[d.s].fields[field(d.s,name)];at=read(m,d.s,at,name);d=f.d;}return{d,at};}
function gfield(g,n,v){for(const m of modules)write(m,globals.find(x=>x.name===g).d.s,global(m,g),n,typeof v==='function'?v(m):v);}
function nfield(g,path,n,v){for(const m of modules){const x=nested(m,g,path);write(m,x.d.s,x.at,n,typeof v==='function'?v(m):v);}}
function pfield(kind,k,i,n,v){for(const m of modules)write(m,kind,ptr(m,k,i),n,typeof v==='function'?v(m):v);}
function option(n,v){const i=typeof n==='number'?n:options[n];assert.notEqual(i,undefined,n);both('option',i,v);}
function input(s){for(const m of modules)m.HEAPU8.set(Buffer.from(s+'\0','latin1'),Number(ptr(m,5)));}
function gbytes(g,name,bytes){const kind=globals.find(x=>x.name===g).d.s,d=schema.schema[kind].fields[field(kind,name)].d;assert.equal(d.a.length,1);assert.ok(bytes.length<d.a[0]);for(const m of modules){const at=Number(read(m,kind,global(m,g),name));m.HEAPU8.fill(0,at,at+d.a[0]);m.HEAPU8.set(bytes,at);}}
function location(m,x,y){return nested(m,'svl',['level','locations']).at+BigInt((x*N('ROWNO')+y)*N('rmSize'));}
function terrain(x,y,typ,flags=0){for(const m of modules){const at=location(m,x,y);write(m,'rm',at,'typ',typ);write(m,'rm',at,'flags',flags);}}
function trapAt(type,x,y){option('t_at',1);pfield('trap',4,0,'ttyp',type);pfield('trap',4,0,'tx',x);pfield('trap',4,0,'ty',y);}
function property(p,member,v){for(const m of modules){const at=read(m,'you',global(m,'u'),'uprops')+BigInt(N(p)*N('propSize'));write(m,'prop',at,member,v);}}
const width=d=>d.row?8:d.t?Number(d.t.slice(1))/8:d.p!==undefined||d.f?8:d.s?N(d.s+'Size'):d.a.reduce((a,b)=>a*b,1)*width(d.e);
function state(m){const out=[],dv=new DataView(m.HEAPU8.buffer);
 const scalar=(d,v,ct,path)=>{let value;if(d.p!==undefined||d.row){if(/^(?:const )?char \*(?:const)?$/.test(ct))value=v?text(m,v):null;else value=m._probe_canonical(v).toString();}else if(d.f)value=v?1:0;else value=v.toString();out.push([path,value]);};
 const value=(d,at,ct='',path='')=>{if(d.s){for(const [i,f]of schema.schema[d.s].fields.entries()){if(d.s==='any'&&f.name!==anyMember)continue;const v=m._teleport_hack_read(kinds.indexOf(d.s),at,i);if(f.d.s||f.d.a)value(f.d,v,f.ctype,path+'.'+f.name);else scalar(f.d,v,f.ctype,path+'.'+f.name);}if(d.s==='any'&&anyMember==='a_uint')out.push([path+'.upper32',read(m,'any',at,'a_long')>>32n]);return;}
  if(d.a){const child=d.a.length===1?d.e:{a:d.a.slice(1),e:d.e};for(let i=0;i<d.a[0];i++)value(child,at+BigInt(i*width(child)),ct.replace(/\[\d*\]/g,''),path+'['+i+']');return;}
  const bytes=width(d);let v=0n;for(let i=0;i<bytes;i++)v|=BigInt(dv.getUint8(Number(at)+i))<<BigInt(i*8);scalar(d,v,ct,path);};
 for(const g of globals)value(g.d,global(m,g.name),g.ctype??'',g.name);
 for(const [kind,k,count]of [['monst',0,8],['obj',1,16],['trap',4,4],['d_level',7,1],['engr',14,2],['weight_table_entry',17,2]])if(schema.schema[kind])for(let i=0;i<count;i++)value({s:kind},ptr(m,k,i),'',kind+i);
 for(let i=0;i<8;i++){out.push(['long'+i,dv.getBigInt64(Number(ptr(m,8,i)),true).toString()],['short'+i,dv.getInt16(Number(ptr(m,9,i)),true)],['int'+i,dv.getInt32(Number(ptr(m,10,i)),true)],['objref'+i,m._probe_canonical(dv.getBigUint64(Number(ptr(m,11,i)),true)).toString()]);}
 out.push(['input',text(m,ptr(m,5))]);return out;
}
function evidence(extra={}){const data={active,...extra,reference:{trace:text(reference,reference._probe_trace()),error:reference._probe_error(),state:state(reference)},hybrid:{trace:text(hybrid,hybrid._probe_trace()),error:hybrid._probe_error(),state:state(hybrid)}};writeFileSync(resolve(dir,'failure-'+Date.now()+'.json'),JSON.stringify(data,(_,v)=>typeof v==='bigint'?v.toString():v,2)+'\n');}
function compare(){const actual=state(hybrid),expected=state(reference);const first=actual.findIndex((v,i)=>JSON.stringify(v,(_,x)=>typeof x==='bigint'?x.toString():x)!==JSON.stringify(expected[i],(_,x)=>typeof x==='bigint'?x.toString():x));assert.equal(first,-1,'HACK state '+active+' first mismatch '+JSON.stringify([actual[first],expected[first]],(_,x)=>typeof x==='bigint'?x.toString():x));const trace=text(reference,reference._probe_trace());assert.equal(text(hybrid,hybrid._probe_trace()),trace,'HACK trace '+active);for(const match of trace.matchAll(/site:hack\.c:(\d+):/g))observedRng.add(Number(match[1]));comparisons+=2;for(let i=0;i<2;i++){assert.equal(modules[i]._probe_stack(),stacks[i],'restored C stack '+active);comparisons++;}assert.equal(C,undefined);comparisons++;}
function reset(label){active=label;anyMember='a_long';cases++;both('reset');}
function action(name,...args){if(process.env.HACK_VERBOSE)console.log(active,name);invoked.add(name);const member=({uint_to_any:'a_uint',long_to_any:'a_long',monst_to_any:'a_monst',obj_to_any:'a_obj'})[name];anyMember=member??anyMember;const f=schema.functions.find(f=>f.name===name),ret=f.type.qualType.split('(')[0].trim();const resolved=modules.map(m=>args.map(a=>typeof a==='function'?a(m):a));const values=modules.map((m,i)=>m['_probe_call_'+name](...resolved[i]));const normalized=values.map((v,i)=>/char\s*\*/.test(ret)?v?text(modules[i],v):null:ret.includes('*')?modules[i]._probe_canonical(v):v);try{assert.deepEqual(normalized[1],normalized[0],name+' result '+active);assert.equal(hybrid._probe_error(),reference._probe_error(),'native error '+active);comparisons+=2;if(member)for(let i=0;i<2;i++){const m=modules[i],at=read(m,'instance_globals_t',global(m,'gt'),'tmp_anything'),raw=new DataView(m.HEAPU8.buffer).getBigUint64(Number(at),true),expected=BigInt.asUintN(member==='a_uint'?32:64,BigInt(resolved[i][0]));assert.equal(raw,expected,'exact own-Module 8-byte anything representation');assert.equal(values[i],at,'shared gt.tmp_anything return identity');comparisons+=2;}compare();}catch(error){evidence({name,values,normalized});throw error;}return values;}
const obj=m=>ptr(m,1),mon=m=>ptr(m,0),human=m=>ptr(m,2,N('PM_HUMAN')),str=m=>ptr(m,5),x=m=>ptr(m,9),y=m=>ptr(m,9,1);
const argMap={uint_to_any:[0xfedcba98],long_to_any:[-0x123456789abcdefn],monst_to_any:[mon],obj_to_any:[obj],revive_nasty:[21,10,str],could_move_onto_boulder:[21,10],dopush:[21,10,22,10,obj,0],cannot_push_msg:[obj,21,10],cannot_push:[obj,21,10],rock_disappear_msg:[obj],moverock_done:[21,10],moverock_core:[21,10],still_chewing:[21,10],movobj:[obj,21,10],may_dig:[21,10],may_passwall:[21,10],bad_rock:[human,21,10],cant_squeeze_thru:[m=>ptr(m,6)],invocation_pos:[21,10],test_move:[20,10,1,0,N('DO_MOVE')],findtravelpath:[2],is_valid_travelpt:[21,10],trapmove:[21,10,0n],notice_mon:[mon],notice_mons_cmp:[m=>ptr(m,12),m=>ptr(m,12,1)],notice_all_mons:[1],impact_disturbs_zombies:[obj,1],disturb_buried_zombies:[21,10],u_locomotion:[str],u_simple_floortyp:[21,10],handle_tip:[0],swim_move_danger:[21,10],domove_bump_mon:[mon,0],domove_attackmon_at:[mon,21,10,m=>ptr(m,10)],domove_fight_ironbars:[21,10],domove_fight_web:[21,10],domove_swap_with_pet:[mon,21,10],domove_fight_empty:[21,10],water_turbulence:[x,y],impaired_movement:[x,y],avoid_moving_on_trap:[21,10,1],avoid_moving_on_liquid:[21,10,1],avoid_running_into_trap_or_liquid:[21,10],avoid_trap_andor_region:[21,10],move_out_of_bounds:[21,10],escape_from_sticky_mon:[21,10],maybe_smudge_engr:[20,10,21,10],set_uinwater:[0],pooleffects:[1],spoteffects:[1],monstinroom:[human,0],furniture_present:[N('ALTAR'),0],in_rooms:[20,10,0],in_town:[20,10],move_update:[0],check_special_room:[0],doorless_door:[21,10],crawl_destination:[21,10],end_running:[1],nomul:[0],unmul:[str],showdamage:[3],losehp:[1,str,N('NO_KILLER_PREFIX')],calc_capacity:[0],check_capacity:[str],cmp_weights:[m=>ptr(m,17),m=>ptr(m,17,1)],inv_cnt:[1],money_cnt:[obj],spot_checks:[21,10,N('ROOM')],rounddiv:[5n,2]};
const filter=process.env.HACK_FILTER?new RegExp(process.env.HACK_FILTER):null;
for(const f of schema.functions){if(filter&&!filter.test(f.name))continue;reset('initial '+f.name);assert.ok(!f.parameters.length||Object.hasOwn(argMap,f.name),'explicit valid argument fixture '+f.name);action(f.name,...(argMap[f.name]??[]));}

if(!filter||process.env.HACK_DIRECTED) {
 // Physical obstacles, actual flags/doormask alias and all four movement modes.
 for(const typ of ['ROOM','STONE','TREE','IRONBARS','DOOR','POOL','LAVAPOOL','ICE'])for(const diagonal of [0,1])for(const mode of ['DO_MOVE','TEST_MOVE','TEST_TRAV','TEST_TRAP']) {
  reset('movement '+typ+'/'+diagonal+'/'+mode);terrain(21,10+diagonal,N(typ),typ==='DOOR'?N('D_CLOSED'):0);gfield('flags','mention_walls',1);
  action('test_move',20,10,1,diagonal,N(mode));action('may_dig',21,10+diagonal);action('may_passwall',21,10+diagonal);
 }
 for(const mask of [0,N('D_NODOOR'),N('D_ISOPEN'),N('D_CLOSED'),N('D_LOCKED'),N('D_BROKEN')]) {
  reset('door alias '+mask);terrain(21,10,N('DOOR'),mask);action('doorless_door',21,10);action('crawl_destination',21,10);action('test_move',20,10,1,0,N('TEST_MOVE'));
 }
 for(const mode of [0,1,2])for(const target of [[21,10],[25,13],[20,10]]) {
  reset('travel '+mode+'/'+target.join(','));gfield('u','tx',target[0]);gfield('u','ty',target[1]);nfield('svc',['context'],'run',8);action('findtravelpath',mode);
 }
 reset('travel DEBUG body');gfield('u','tx',24);gfield('iflags','trav_debug',1);gfield('flags','runmode',N('RUN_CRAWL'));action('findtravelpath',2);
 // Seeded obstacle fields exercise the unchanged BFS ordering and guess pass
 // with fresh C-owned scratch arrays on repeatedly reused JS bindings.
 for(let seed=1;seed<=12;seed++)for(const mode of [0,1,2]) {
  reset('seeded travel '+seed+'/'+mode);
  let random=seed;const next=()=>random=(Math.imul(random,1664525)+1013904223)>>>0;
  for(let x=16;x<=28;x++)for(let y=6;y<=15;y++)if(x!==20||y!==10){const value=next()%8;terrain(x,y,N(value<2?'STONE':value===2?'DOOR':'ROOM'),value===2?N('D_CLOSED'):0);}
  gfield('u','tx',seed%2?28:16);gfield('u','ty',seed%3?15:6);
  nfield('svc',['context'],'run',8);action('findtravelpath',mode);
 }
 // All trapped-state switch arms, including shared wriggle-free label behavior.
 for(const trap of ['TT_BEARTRAP','TT_PIT','TT_WEB','TT_LAVA','TT_INFLOOR','TT_BURIEDBALL'])for(const turns of [1,3])for(const diagonal of [0,1]) {
  reset('trapped '+trap+'/'+turns+'/'+diagonal);gfield('u','utrap',turns);gfield('u','utraptype',N(trap));gfield('u','dy',diagonal);gfield('flags','verbose',1);action('trapmove',21,10+diagonal,0n);
 }
 // Native promotion/narrowing at function entry, exact signed long division and
 // original panic/recovery. No undefined INT64_MIN negation case is claimed.
 for(const x of [-9007199254740993n,-101n,-5n,-1n,0n,1n,5n,101n,9007199254740993n])for(const y of [-17,-2,2,17]) {reset('rounddiv '+x+'/'+y);action('rounddiv',x,y);}
 reset('coordxy formals narrow');action('test_move',65556,65546,65537,0,N('TEST_MOVE'));action('may_dig',65557,65546);
 reset('rounddiv panic recovery');action('rounddiv',5n,0);assert.equal(reference._probe_error(),1);comparisons++;action('rounddiv',7n,2);
 for(const coins of [0n,99n,101n,9007199254740993n]) {reset('money exact long '+coins);pfield('obj',1,0,'oclass',N('COIN_CLASS'));pfield('obj',1,0,'quan',coins);action('money_cnt',obj);gfield('gi','invent',obj);action('inv_weight');}
 // Pointer arithmetic into mkroom/rm arrays and stable five-byte static room
 // buffer. Compare its real bytes, lifetime and return offset after overwrite.
 for(const type of [0,N('SHOPBASE'),N('TEMPLE')]) {
  reset('room pointer walk '+type);for(const m of modules){const at=location(m,20,10);write(m,'rm',at,'roomno',N('SHARED_PLUS'));for(const [x,y,r]of [[19,9,0],[19,10,1],[20,9,2],[21,11,3]]){write(m,'rm',location(m,x,y),'roomno',N('ROOMOFFSET')+r);const rooms=nested(m,'svr',['rooms']).at;write(m,'mkroom',rooms+BigInt(r*N('mkroomSize')),'rtype',r%2?N('SHOPBASE')+1:N('TEMPLE'));}}
  const first=action('in_rooms',20,10,type),bases=modules.map((m,i)=>first[i]-(m._probe_canonical(first[i])&0xffffn));
  for(const m of modules)write(m,'rm',location(m,20,10),'roomno',N('ROOMOFFSET')+5);
  const second=action('in_rooms',20,10,0);
  for(let i=0;i<2;i++){assert.equal(second[i],bases[i]+3n,'same native static buffer base');comparisons++;}
  assert.deepEqual(hybrid.HEAPU8.slice(Number(bases[1]),Number(bases[1])+5),reference.HEAPU8.slice(Number(bases[0]),Number(bases[0])+5),'all five real static bytes after overwrite');assert.equal(text(hybrid,first[1]),text(reference,first[0]),'previous room pointer observes later writes');comparisons+=2;
 }
 // Actual C function-pointer indirection enters each dedicated JS comparator.
 for(const [name,index,kind]of [['notice_mons_cmp',27,12],['cmp_weights',90,17]]) {
  reset('native comparator '+name);const result=modules.map(m=>m._probe_invoke_comparator(index,ptr(m,kind),ptr(m,kind,1)));assert.equal(result[1],result[0]);comparisons++;compare();
  const env=environments.get(hybrid);assert.ok(env.pointerEqual(env.functionPointer(core[name]),hybrid._probe_callback_pointer(index)));comparisons++;
 }
 for(const grow of [0,1])for(const reenter of [0,1]) {
  reset('foreign afternmv '+grow+'/'+reenter);option(900,grow);option(904,reenter);both('set_afternmv',1);const before=hybrid.HEAPU8.buffer;action('unmul',str);if(grow){assert.notEqual(hybrid.HEAPU8.buffer,before);comparisons++;}
  reset('RNG growth reentry '+grow+'/'+reenter);gfield('u','utrap',3);gfield('u','utraptype',N('TT_BEARTRAP'));option(900,grow);option(902,reenter);action('trapmove',21,10,0n);
 }
 for(const after of [0,1]) {reset('Boots_on pointer equality '+after);both('set_afternmv',after);property('LEVITATION','extrinsic',BigInt(L.W_ARMF));action('weight_cap');}
 for(const cold of [0,1])for(const lev of [0,1])for(const resist of [0,1]) {
  reset('ice local alias '+cold+'/'+lev+'/'+resist);terrain(20,10,N('ICE'));property('COLD_RES','intrinsic',cold);property('LEVITATION','intrinsic',lev);option('Resists_Elem',resist);action('slippery_ice_fumbling');
 }
 // A real native grid/list dependency world lets successful pushes remove the
 // boulder from the source cell, rather than hiding source loops with stubs.
 for(const target of ['ROOM','STONE','DOOR','POOL'])for(const noPick of [0,1])for(const levitate of [0,1]) {
  reset('boulder '+target+'/'+noPick+'/'+levitate);pfield('obj',1,0,'otyp',N('BOULDER'));pfield('obj',1,0,'o_id',100);both('place_object',0,21,10);
  terrain(22,10,N(target),target==='DOOR'?N('D_CLOSED'):0);nfield('svc',['context'],'nopick',noPick);property('LEVITATION','intrinsic',levitate);action('moverock_core',21,10);
 }
 for(const close of [0,1]) {
  reset('buried ball native coord '+close);gfield('u','utrap',3);gfield('u','utraptype',N('TT_BURIEDBALL'));option('buried_ball',1);action('trapmove',close?21:23,10,0n);
 }
 // mkroom*++ must advance by the actual record size rather than one byte.
 for(const inside of [0,1])for(const subrooms of [0,1]) {
  reset('town room pointer stride '+inside+'/'+subrooms);nfield('svl',['level','flags'],'has_town',1);
  for(let i=0;i<2;i++)both('room',i,i?19:1,i?23:5,9,12,i?subrooms:0,0);
  action('in_town',inside?20:30,10);
 }
 for(const newlev of [0,1]) {
  reset('room string pointer increments '+newlev);const offset=N('ROOMOFFSET');gbytes('u','urooms',[offset,offset+1]);gbytes('u','ushops',[offset]);
  for(const m of modules){write(m,'rm',location(m,20,10),'roomno',N('SHARED_PLUS'));const rooms=nested(m,'svr',['rooms']).at;for(const [x,y,r]of [[19,9,1],[19,10,2],[20,9,3]]){write(m,'rm',location(m,x,y),'roomno',offset+r);write(m,'mkroom',rooms+BigInt(r*N('mkroomSize')),'rtype',r===1?0:N('SHOPBASE')+r);}}
  action('move_update',newlev);
 }
 for(const species of ['PM_HUMAN','PM_GRID_BUG'])for(const result of ['Trap_Effect_Finished','Trap_Caught_Mon','Trap_Moved_Mon','Trap_Killed_Mon']) {
  reset('pet pointer difference '+species+'/'+result);pfield('monst',0,0,'data',m=>ptr(m,2,N(species)));pfield('monst',0,0,'mx',21);pfield('monst',0,0,'my',11);option('mintrap',N(result));action('domove_swap_with_pet',mon,21,11);
 }
 for(const moveDuringCallback of [0,1]) {reset('recursive spoteffects '+moveDuringCallback);option(905,1);option(906,moveDuringCallback);action('spoteffects',1);action('spoteffects',1);}
 for(const left of [3,7,12,20]) {reset('source ice warning table '+left);terrain(20,10,N('ICE'));property('WARNING','intrinsic',1);option('spot_time_left',left);action('spoteffects',0);}
 for(const hp of [1,10])for(const count of [0,3,4,12]) {
  reset('static powers source order '+hp+'/'+count);gfield('u','uhp',hp);nfield('gu',['urole'],'mnum',N('PM_WIZARD'));gfield('svm','moves',1000);
  const powers=['TELEPORT','SEE_INVIS','POISON_RES','COLD_RES','SHOCK_RES','FIRE_RES','SLEEP_RES','DISINT_RES','TELEPORT_CONTROL','STEALTH','FAST','INVIS'];for(const p of powers.slice(0,count))property(p,'intrinsic',BigInt(L.INTRINSIC));action('maybe_wail');
 }
 reset('air level random branches');nfield('svd',['dungeon_topology','d_air_level'],'dnum',1);nfield('svd',['dungeon_topology','d_air_level'],'dlevel',3);for(let i=0;i<12;i++)action('air_turbulence');
 reset('confusion random movement');property('CONFUSION','intrinsic',1);for(let i=0;i<8;i++){action('u_maybe_impaired');action('impaired_movement',x,y);}
 for(const immobile of [0,1])for(const tame of [0,1]) {
  reset('sticky escape '+immobile+'/'+tame);gfield('u','ustuck',mon);pfield('monst',0,0,'mx',20);pfield('monst',0,0,'my',11);pfield('monst',0,0,'mcanmove',1-immobile);pfield('monst',0,0,'mtame',tame);action('escape_from_sticky_mon',21,10);
 }
 reset('engraving RNG sites');option('engr_at',1);action('maybe_smudge_engr',20,10,21,10);
 reset('displacer live boolean outparam');pfield('monst',0,0,'data',m=>ptr(m,2,N('PM_DISPLACER_BEAST')));pfield('monst',0,0,'mux',20);pfield('monst',0,0,'muy',10);pfield('monst',0,0,'mcanmove',1);for(let i=0;i<4;i++)action('domove_attackmon_at',mon,21,10,m=>ptr(m,10));
 reset('force fight web random site');trapAt(N('WEB'),21,10);pfield('trap',4,0,'tseen',1);nfield('svc',['context'],'forcefight',1);action('domove_fight_web',21,10);
 for(const typ of ['ROOM','STONE','DOOR']) {reset('force fight empty '+typ);terrain(21,10,N(typ));nfield('svc',['context'],'forcefight',1);action('domove_fight_empty',21,10);}
 reset('force fight map edge');nfield('svc',['context'],'forcefight',1);action('domove_fight_empty',-1,0);
 reset('levitation trap timeout reference');trapAt(N('ARROW_TRAP'),20,10);property('LEVITATION','intrinsic',1);action('spoteffects',1);
 reset('sink RNG before attribute offset');action('dosinkfall');
 reset('completed chewing hunger RNG');terrain(21,10,N('TREE'));for(let i=0;i<3;i++)action('still_chewing',21,10);
 reset('boulder landmine RNG');pfield('obj',1,0,'otyp',N('BOULDER'));both('place_object',0,21,10);trapAt(N('LANDMINE'),22,10);action('moverock_core',21,10);
 for(const half of [0,1]) {reset('sink floor weapon '+half);property('HALF_PHDAM','intrinsic',half);both('place_object',0,20,10);action('dosinkfall');}
 reset('hallucinated trap prompt RNG');gfield('flags','paranoia_bits',BigInt(L.PARANOID_TRAP));property('HALLUC','intrinsic',1);trapAt(N('ARROW_TRAP'),21,10);pfield('trap',4,0,'tseen',1);action('avoid_trap_andor_region',21,10);
 for(const ac of [-10,100])for(const half of [0,1]) {
  reset('piercer landing '+ac+'/'+half);gfield('u','uac',ac);property('HALF_PHDAM','intrinsic',half);pfield('permonst',2,N('PM_HUMAN'),'mlet',N('S_PIERCER'));for(const m of modules){const grid=nested(m,'svl',['level','monsters']).at;new DataView(m.HEAPU8.buffer).setBigUint64(Number(grid)+8*(20*N('ROWNO')+10),ptr(m,0),true);}action('spoteffects',1);
 }
 // Preserve the original comparison of zero-based roomno to raw roomno. The
 // outside monster cell deliberately carries zero to exercise that C branch.
 reset('zoo wakeup RNG');both('room',0,18,23,9,12,0,N('ZOO'));for(const m of modules){write(m,'rm',location(m,20,10),'roomno',N('ROOMOFFSET'));write(m,'rm',location(m,30,10),'roomno',0);}nfield('svl',['level'],'monlist',mon);pfield('monst',0,0,'msleeping',1);action('check_special_room',0);
 for(const flags of [0,N('W_NONDIGGABLE'),N('W_NONPASSWALL')]) {reset('wall_info live alias '+flags);terrain(21,10,N('STONE'),flags);action('may_dig',21,10);action('may_passwall',21,10);}
 for(const flags of [0,1,8,16]) {reset('drawbridgemask live alias '+flags);terrain(20,10,N('DRAWBRIDGE_UP'),flags);action('classify_terrain');}
 for(const looted of [0,1]) {reset('looted live alias '+looted);terrain(20,10,N('THRONE'),looted);action('pickup_checks');}
 reset('launch2 live union alias');pfield('obj',1,0,'otyp',N('BOULDER'));both('place_object',0,21,10);trapAt(N('ROLLING_BOULDER_TRAP'),22,10);
 for(const m of modules){const at=read(m,'vlaunchinfo',read(m,'trap',ptr(m,4),'vl'),'v_launch2');write(m,'nhcoord',at,'x',25);write(m,'nhcoord',at,'y',10);}action('moverock_core',21,10);
 reset('nonnull nexthere and next_boulder aliases');for(let i=0;i<2;i++){pfield('obj',1,i,'otyp',N('BOULDER'));pfield('obj',1,i,'corpsenm',i+7);both('place_object',i,21,10);}action('moverock_done',21,10);
 for(const weights of [[0xffffffff,2],[0x80000000,0x80000002]]) {
  reset('unsigned compound inventory '+weights.join('/'));gfield('gi','invent',obj);for(let i=0;i<2;i++){pfield('obj',1,i,'owt',weights[i]);pfield('obj',1,i,'nobj',i?0:m=>ptr(m,1,1));}action('inv_weight');action('near_capacity');
 }
 for(const run of [1,2,3,4,8])for(const shape of ['open','corridor','corner','closed-door'])for(const diagonal of [0,1]) {
  reset('lookaround labels '+run+'/'+shape+'/'+diagonal);nfield('svc',['context'],'run',run);gfield('u','dy',diagonal);gfield('u','last_str_turn',1);
  if(shape!=='open'){for(let x=19;x<=21;x++)for(let y=9;y<=11;y++)terrain(x,y,N('STONE'));terrain(20,10,N('CORR'));terrain(21,10,N('CORR'));if(shape==='corner')terrain(21,11,N('CORR'));if(shape==='closed-door')terrain(21,10,N('DOOR'),N('D_CLOSED'));}
  action('lookaround');
 }
 reset('throwing callback restores lexical environment and native frame');gfield('u','utrap',3);gfield('u','utraptype',N('TT_BEARTRAP'));
 const primary=servicesByModule.get(hybrid),failure=new Error('HACK private callback failure'),marker={privateHackOuterScope:true};
 const failing=Object.assign(Object.create(primary),{rngCaller(){throw failure;}});
 withCEnvironment(marker,()=>{assert.throws(()=>callHack(failing,L,'trapmove',21,10,0n),e=>e===failure);assert.equal(C,marker);comparisons+=2;});assert.equal(C,undefined);assert.equal(hybrid._probe_stack(),stacks[1]);comparisons+=2;
 reset('separate Module owns statics and native views');action('in_rooms',20,10,0);
 const env=environments.get(hybrid),saved={...env.state},hybrid2=await factories[1]({nethackPorted:runtime});hybrid2._probe_reset();hybrid2._probe_call_spoteffects(1);
 const env2=environments.get(hybrid2);assert.notEqual(env.state,env2.state);assert.notEqual(env.view('obj',ptr(hybrid,1)),env2.view('obj',ptr(hybrid2,1)));assert.notEqual(hybrid.HEAPU8.buffer,hybrid2.HEAPU8.buffer);assert.equal(env.state.spotterrain,saved.spotterrain);comparisons+=4;
 const opaque=0x20000000000001n;assert.equal(env.pointerEqual(opaque,opaque-1n),hybrid._probe_pointer_equal(opaque,opaque-1n));assert.equal(env.pointerDifference(opaque+L.permonstSize,opaque,'permonst'),1n);comparisons+=2;
 assert.throws(()=>createHackEnvironment(primary,{...L,pointerSize:4n},core),/changed HACK ABI/);assert.throws(()=>createHackEnvironment(primary,{...L,width_obj_otyp:4n},core),/field width/);comparisons+=2;
 assert.throws(()=>env.view('obj',ptr(hybrid,1)).invented_hack_field,/Unknown HACK/);assert.throws(()=>{env.view('obj',ptr(hybrid,1)).invented_hack_field=1;},/Unknown HACK/);comparisons+=2;
 // Guard mutations use private copies; original/prepared C and active files
 // remain byte-identical throughout these deliberate rejection witnesses.
 const guardRoot=resolve(dir,'guard-negative'),guardPaths=['nethack-c/upstream/src/hack.c','.cache/wasm64-build/tree/src/hack.c','js/ported/hack.js','nethack-c/wasm/tu-fragments/hack-schema.json'],originals=new Map();
 for(const p of guardPaths){const bytes=await readFile(p,'utf8');originals.set(p,bytes);await mkdir(resolve(guardRoot,p,'..'),{recursive:true});await writeFile(resolve(guardRoot,p),bytes);}
 checkHackSource(guardRoot,{preprocess:false,ast:false});
 for(const [p,change]of [[guardPaths[0],s=>'/* changed */'+s],[guardPaths[1],s=>'/* changed */'+s],[guardPaths[2],s=>s.replace('export function trapmove(','export function changed_trapmove(')],[guardPaths[2],s=>s.replace('uint_to_any(ui)','uint_to_any(changed)')],[guardPaths[2],s=>s.replace('TRAVP_VALID = 2','TRAVP_VALID = 3')],[guardPaths[2],s=>s.replace('C.state.unknown_obstacle = "an unknown obstacle"','C.state.unknown_obstacle = "changed"')],[guardPaths[2],s=>s.replace('C.TELEPORT,C.SEE_INVIS','C.SEE_INVIS,C.TELEPORT')],[guardPaths[2],s=>s.replace('/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */','')],[guardPaths[3],s=>s.replace(schema.preparedSha256,'0'.repeat(64))]]) {
  await writeFile(resolve(guardRoot,p),change(originals.get(p)));assert.throws(()=>checkHackSource(guardRoot,{preprocess:false,ast:false}),/Review changed|Missing original/);comparisons++;await writeFile(resolve(guardRoot,p),originals.get(p));
 }
}
if(!filter)assert.equal(invoked.size,95);
console.log(`hack: ${cases} cases, ${comparisons} EmC/JS state/trace/result/stack checks, ${invoked.size}/95 routines; native host and game pending`);
await writeFile(resolve(dir,'summary.json'),JSON.stringify({status:'pass',oracle:'configured Emscripten memory64 original source in a controlled foreign world',catalogues:'synthetic native tables; original objects.c/monst.c and real init_objects are not linked or executed',nativeHost:'pending',game:'pending',cases,comparisons,functions:invoked.size,jsPolicyImports:schema.functions.length,observedRngSites:[...observedRng].sort((a,b)=>a-b),nativeCallbackCalls:Object.fromEntries(callbackCalls)},null,2)+'\n');
