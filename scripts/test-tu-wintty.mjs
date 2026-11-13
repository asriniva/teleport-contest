import {nativeFixtureServices} from './native-pet-combat-fixture.mjs';
const nativeExecution=process.env.NATIVE_WINTTY_FIXTURE==='1',nativeServices=new WeakMap();
function ttyServices(s){if(!nativeExecution)return s;let local=nativeServices.get(s);if(!local){local=nativeFixtureServices(s,{}).services;Object.setPrototypeOf(local,Object.getPrototypeOf(s));Object.defineProperties(local,Object.getOwnPropertyDescriptors(s));nativeServices.set(s,local);}return local;}
import './pure-js-probes/deny-wasm.mjs';
import {createProbe,createReference,loadFixture,fixtureImports} from './pure-js-fixtures/load.mjs';
import {DataView as FixtureDataView,Int32Array as FixtureInt32Array} from './native-test-backend.mjs';
// Actual configured WINTTY C versus imported JS; real termcap/ncurses chain.
import assert from './native-test-assert.mjs';
import fs from 'node:fs';
import {resolve}from'node:path';
import {pathToFileURL}from'node:url';
import * as core from '../js/ported/wintty.js';
import {callWintty,initializeWintty,winttyState,createWinttyEnvironment}from'../js/nethack/bindings/wintty.js';
// Original C reference is available through the isolated reference process.
const privateDir=process.env.TELEPORT_WINTTY_PROBE_DIR,dir=resolve(privateDir??'.cache/tu-probes');
const file=mode=>pathToFileURL(resolve(dir,(privateDir?'':'wintty-')+mode+'.mjs'));
const {default:referenceFactory}=await loadFixture("wintty",file('reference'));
const {default:hybridFactory}=await loadFixture("wintty",file('hybrid'));
const output=[[],[]],moduleRefs=[],stdinQueues=[[],[]];
function emitted(i,c){const m=moduleRefs[i];if(!m){output[i].push([c]);return;}const p=Number(m._probe_display()),d=new FixtureDataView(m.HEAPU8.buffer),cx=p?d.getInt16(p+L.offset_struct_DisplayDesc_curx,true):0,cy=p?d.getInt16(p+L.offset_struct_DisplayDesc_cury,true):0,s=Number(m._probe_shadow());const cell=x=>cy>=0&&cy<24&&x>=0&&x<80?d.getUint32(s+(cy*80+x)*4,true):0;output[i].push([c,cx,cy,cell(cx),cell(cx-1),p?d.getInt32(p+L.offset_struct_DisplayDesc_attrs,true):0]);}

const options=i=>({stdin:()=>stdinQueues[i].shift()??null,stdout:c=>emitted(i,c),print:s=>output[i].push(s),printErr:s=>output[i].push('ERR:'+s),preRun:[m=>{m.ENV.TERM='xterm-256color';m.ENV.TERMINFO='/terminfo';m.ENV.NOMUX_MARKERS='1';m.ENV.HOME='/';}]});
const reference=await referenceFactory(options(0));moduleRefs[0]=reference;
function text(m,p){p=Number(p);if(!p)return null;let end=p;while(m.HEAPU8[end])end++;return Buffer.from(m.HEAPU8.slice(p,end)).toString('latin1');}
const raw={};for(let i=0;i<reference._probe_layout_count();i++)raw[text(reference,reference._probe_layout_name(i))]=reference._probe_layout_value(i);
const L={};for(const[k,v]of Object.entries(raw))L[k]=raw['constwidth_'+k]===8n?(raw['constsigned_'+k]?BigInt.asIntN(64,v):BigInt.asUintN(64,v)):Number(BigInt.asIntN(64,v));
for(const[,name]of fs.readFileSync(new URL(import.meta.url),'utf8').matchAll(/\bL\.([A-Z][A-Z_0-9]*)/g))assert.notEqual(L[name],undefined,'Actual compiler constant '+name);
const services=new WeakMap();
const runtime={wintty(s,n,...a){s=ttyServices(s);services.set(s.moduleKey,s);return callWintty(s,L,n,...a);},initializeWintty(s){s=ttyServices(s);services.set(s.moduleKey,s);return initializeWintty(s,L);},winttyState};
const hybrid=await hybridFactory({...options(1),nethackPorted:runtime});moduleRefs[1]=hybrid;
const modules=[reference,hybrid],names=["bail","winch_handler","resize_tty","newclipping","new_status_window","tty_init_nhwindows","tty_preference_update","tty_player_selection","tty_askname","tty_get_nh_event","getret","tty_suspend_nhwindows","tty_resume_nhwindows","tty_exit_nhwindows","tty_create_nhwindow","erase_menu_or_text","free_window_info","tty_clear_nhwindow","toggle_menu_curr","dmore","set_item_state","set_all_on_page","unset_all_on_page","invert_all_on_page","invert_all","toggle_menu_attr","process_menu_window","process_text_window","tty_display_nhwindow","tty_dismiss_nhwindow","tty_destroy_nhwindow","erase_tty_screen","tty_curs","compress_str","tty_putstr","tty_display_file","tty_start_menu","tty_add_menu","reverse","tty_end_menu","tty_select_menu","tty_message_menu","tty_ctrl_nhwindow","tty_update_inventory","tty_mark_synch","tty_wait_synch","docorner","end_glyphout","g_putch","g_pututf8","setclipped","tty_cliparound","tty_print_glyph","tty_raw_print","tty_raw_print_bold","tty_nhgetch","tty_nh_poskey","win_tty_init","tty_putmixed","tty_status_init","tty_status_enablefield","tty_status_update","make_things_fit","check_fields","tty_putstatusfield","set_condition_length","shrink_enc","shrink_dlvl","check_windowdata","condcolor","condattr","render_status"];
let comparisons=0;const seen=new Set();
function both(fn){modules.forEach(fn);}
function write(m,slot,s){const p=Number(m._probe_buffer(slot));m.HEAPU8.fill(0,p,p+8192);m.HEAPU8.set(Buffer.from(s+'\0','latin1'),p);return BigInt(p);}
// Only this compiler-typed selection pointer is canonicalized. No byte scanning.
function selectionRegion(m,raw,count){
 assert.equal(typeof raw,'bigint');
 if(raw===0n)return {kind:'null',raw:0n,count};
 const matches=[];
 for(let id=1,n=m._probe_alloc_count();id<=n;id++){
  if(!m._probe_alloc_live(id))continue;
  const base=m._probe_alloc_base(id),size=BigInt(m._probe_alloc_size(id));
  assert.equal(typeof base,'bigint');
  if(raw>=base&&raw<base+size)matches.push({id,base,size});
 }
 if(matches.length!==1)return {kind:'unknown',raw,count,matches:matches.length};
 const region=matches[0],offset=raw-region.base;
 assert.ok(Number.isInteger(count)&&count>0,'Positive selected pointer has positive exact int count');
 assert.ok(offset+BigInt(count)*BigInt(L.struct_mi_size)<=region.size,'Selected pointer extent remains inside its actual LIVE allocation');
 return {kind:'known',allocation:region.id,offset,count};
}
function selectionOutput(m){
 const d=new FixtureDataView(m.HEAPU8.buffer),raw=d.getBigUint64(Number(m._probe_ints()),true),count=Number(BigInt.asIntN(32,m._probe_return()));
 assert.equal(raw!==0n,count>0,'Actual selection output NULL iff no selected records');
 const region=selectionRegion(m,raw,count);
 assert.notEqual(region.kind,'unknown','Selected pointer must have a unique LIVE allocation; raw64='+raw.toString());
 return region;
}
// Separate observation-contract witness. Native result/count and all165 actual
// comparisons stay unchanged. Both temporary pointers are restored in finally.
function selectionObservationContract(){
 const stride=BigInt(L.struct_mi_size);
 assert.equal(stride,24n,'Actual compiler menu_item stride');
 const expected=modules.map(m=>{
  const base=new FixtureDataView(m.HEAPU8.buffer).getBigUint64(Number(m._probe_ints()),true);
  const originalCount=Number(BigInt.asIntN(32,m._probe_return()));
  assert.ok(originalCount>=2,'STOP: offset witness needs a genuine LIVE multi-item selection');
  const first=selectionRegion(m,base,1),second=selectionRegion(m,base+stride,1);
  assert.equal(first.kind,'known');assert.equal(second.kind,'known');
  assert.equal(first.allocation,second.allocation);assert.equal(first.offset,0n);assert.equal(second.offset,stride);
  assert.equal(selectionRegion(m,0xfedcba9876543210n,1).raw,0xfedcba9876543210n,'Unknown raw64 remains exact before address conversion');
  return first;
 });
 assert.deepEqual(expected[1],expected[0],'Native paired region identities agree for observation contract');
 const observed=modules.map((m,i)=>{
  const out=Number(m._probe_ints()),d=new FixtureDataView(m.HEAPU8.buffer),base=d.getBigUint64(out,true);
  const observedToken=base; // loader-only known-pointer controls anchor
  d.setBigUint64(out,observedToken,true);
  try{return selectionRegion(m,new FixtureDataView(m.HEAPU8.buffer).getBigUint64(out,true),1);}
  finally{new FixtureDataView(m.HEAPU8.buffer).setBigUint64(out,base,true);assert.equal(new FixtureDataView(m.HEAPU8.buffer).getBigUint64(out,true),base,'Observation contract restores the original owned pointer');}
 });
 assert.deepEqual(observed[1],expected[0],'Known LIVE allocation identity and exact offset observation contract');
 console.log('PASS separate known LIVE region/count/offset observation contract; raw64 and finally restoration');
}
function run(name,args=()=>[],label=''){
 seen.add(name);const snapshots=modules.map((m,i)=>{const a=args(m,i).map(v=>BigInt(v??0));while(a.length<9)a.push(0n);try{m._probe_invoke(names.indexOf(name),...a);}catch(e){console.error(name,label,'module',i);throw e;}return{text:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace()),error:m._probe_error(),shadow:Buffer.from(m.HEAPU8.slice(Number(m._probe_shadow()),Number(m._probe_shadow())+24*80*4)).toString('hex'),ints:(()=>{const p=Number(m._probe_ints()),d=new FixtureDataView(m.HEAPU8.buffer),values=Array.from(new FixtureInt32Array(m.HEAPU8.buffer,p,16));if(name==='tty_select_menu'){values.splice(0,2,selectionOutput(m));}return values;})(),output:output[i]};});assert.deepEqual(snapshots[1],snapshots[0],name+' '+label);for(const m of modules)assert.equal(m._probe_error(),name==='bail'?1:0,'Defined native caller path '+name+' '+label);comparisons++;return modules.map(m=>m._probe_return());
}
both(m=>m._probe_reset());
// The startup catalogue is observable before the first original function.
function catalogue(m,p){p=Number(p);const d=new FixtureDataView(m.HEAPU8.buffer),bytes=m.HEAPU8.slice(p,p+L.struct_window_procs_size);const values={};for(const[name,t]of Object.entries(core.tty_procs_initial)){const at=Number(L['offset_struct_window_procs_'+name]);if(name==='name'){values.name=text(m,d.getBigUint64(p+at,true));bytes.fill(0,at,at+8);}else if(name.startsWith('win_')){const kind=m._probe_callback_kind(d.getBigUint64(p+at,true));assert.ok(kind>=0,'Actual native callback identity '+name);values[name]=kind;bytes.fill(0,at,at+8);}}return{values,bytes:Buffer.from(bytes).toString('hex')};}
assert.deepEqual(catalogue(hybrid,hybrid._probe_startup_catalogue()),catalogue(reference,reference._probe_startup_catalogue()),'Optimized native constructor sees full JS catalogue before first source call');
assert.equal(catalogue(hybrid,hybrid._probe_startup_catalogue()).values.name,'tty');
// Actual original C private catalogues are read through their real storage;
// compare every row rather than deriving expected values from JS alone.
for(const [index,table]of [[25,core.twolineorder_initial],[26,core.threelineorder_initial]]){
 const readOrder=m=>{const d=new FixtureDataView(m.HEAPU8.buffer),p=Number(m._probe_storage(index));return Array.from({length:57},(_,i)=>d.getInt32(p+4*i,true));};
 const native=readOrder(reference);assert.deepEqual(readOrder(hybrid),native,'All original status-order cells '+index);
 assert.deepEqual(native,table.flat().map(v=>typeof v==='string'?Number(L[v]):v),'Readable JS status selectors resolve to actual C catalogue');
}
const enc=m=>{const p=Number(m._probe_storage(24)),d=new FixtureDataView(m.HEAPU8.buffer);return Array.from({length:18},(_,i)=>text(m,d.getBigUint64(p+8*i,true)));};
assert.deepEqual(enc(hybrid),enc(reference));assert.deepEqual(enc(reference),core.encvals_initial.flat());
const cmds=m=>Array.from(m.HEAPU8.slice(Number(m._probe_storage(16)),Number(m._probe_storage(16))+12));
assert.deepEqual(cmds(hybrid),cmds(reference));assert.deepEqual(cmds(reference),core.default_menu_cmds_initial.map(v=>typeof v==='string'?Number(L[v])&255:v));
assert.equal(text(reference,reference._probe_storage(7)),core.defmorestr_initial);assert.equal(text(hybrid,hybrid._probe_storage(7)),core.defmorestr_initial);

run('tty_init_nhwindows',m=>[m._probe_ints(),0]);
assert.equal(reference._probe_error(),0,'Native actual termcap/ncurses startup succeeds');assert.equal(hybrid._probe_error(),0,'Hybrid actual termcap/ncurses startup succeeds');
run('tty_get_nh_event');run('tty_mark_synch');run('tty_wait_synch');
const ids={};
function create(type,role){const values=run('tty_create_nhwindow',()=>[type]);assert.equal(values[1],values[0],'Native window allocation returns same logical slot');if(role!==undefined)modules.forEach((m,i)=>m._probe_set(role,values[i]));return Number(values[0]);}
ids.message=create(L.NHW_MESSAGE,13);ids.map=create(L.NHW_MAP,12);ids.menu=create(L.NHW_MENU);ids.text=create(L.NHW_TEXT);
run('tty_status_init');both(m=>m._probe_set(2,1n));
both(m=>m.FS.writeFile('/fixture.txt','File heading\n\tTabbed line\n'));
run('tty_display_file',m=>[write(m,0,'/fixture.txt'),1]);
run('tty_display_file',m=>[write(m,0,'/missing-fixture'),0]);
// Native allocation grows memory and reenters through the original imported
// synchronisation function while source window pointers are live.
const beforeGrowth=modules.map(m=>m.HEAPU8.buffer);
both(m=>{m._probe_option(1000,6);m._probe_option(1001,6);});
const growthWindow=create(L.NHW_TEXT);
modules.forEach((m,i)=>assert.notEqual(m.HEAPU8.buffer,beforeGrowth[i],'Actual native allocation grew Module memory'));
assert.match(text(reference,reference._probe_trace()),/growth;.*nested;/,'Native allocation callback reentered original synchronisation');
both(m=>{m._probe_option(1000,0);m._probe_option(1001,0);});
run('tty_putstr',m=>[growthWindow,L.ATR_NONE,write(m,0,'After actual growth')]);
run('tty_destroy_nhwindow',()=>[growthWindow]);
run('tty_raw_print',m=>[write(m,0,'Original raw output')]);
run('tty_raw_print_bold',m=>[write(m,0,'Bold output')]);
run('g_putch',()=>[65]);run('g_putch',()=>[0xe1]);
run('g_pututf8',m=>[write(m,0,'UTF8 bytes')]);
both(m=>m._probe_input(write(m,0,'a')));run('tty_nhgetch');
stdinQueues.forEach(q=>q.push(90));both(m=>m._probe_set(3,1n));
run('tty_nhgetch',()=>[],'nested real native read from stdin');assert.equal(reference._probe_return(),90n,'Nested native read returns queued byte');
both(m=>m._probe_set(3,0n));
both(m=>m._probe_set(0,1n));run('tty_nhgetch',()=>[],'hangup short circuit');assert.equal(reference._probe_return(),27n);both(m=>m._probe_set(0,0n));
both(m=>{m._probe_set(1,1n);m._probe_option(9,81);});run('tty_nhgetch',()=>[],'configured fuzzer input');assert.equal(reference._probe_return(),81n);both(m=>m._probe_set(1,0n));

run('win_tty_init',()=>[L.WININIT]);

const win=(m,name)=>m._probe_window(ids[name]);
both(m=>m._probe_option(3,1));run('tty_curs',()=>[ids.map,-1,-1],'source guarded positioning diagnostic');both(m=>m._probe_option(3,0));
run('tty_curs',()=>[ids.map,10,5]);
run('tty_putstr',m=>[ids.map,L.ATR_BOLD,write(m,0,'Map output')]);
run('tty_putstr',m=>[0,L.ATR_NONE,write(m,0,'Base text')]);
for(const message of ['message line','another message','wide '+('word '.repeat(20))])run('tty_putstr',m=>[ids.message,L.ATR_NONE,write(m,0,message)]);
run('getret');
run('tty_nh_poskey',m=>[m._probe_ints(),BigInt(Number(m._probe_ints())+2),BigInt(Number(m._probe_ints())+4)]);
for(const value of ['short','  '+('wide  spaces '.repeat(20))+'  ','line one\nline two']){const returns=run('compress_str',m=>[write(m,0,value)]);assert.equal(text(hybrid,returns[1]),text(reference,returns[0]));}
run('tty_putmixed',m=>[ids.message,L.ATR_NONE,write(m,0,'Mixed message')]);
run('tty_preference_update',m=>[write(m,0,'statuslines')]);
run('tty_preference_update',m=>[write(m,0,'unrelated')]);
both(m=>m._probe_option(6,1));run('tty_player_selection');
both(m=>m._probe_input(write(m,0,'Test\n')));run('tty_askname');
both(m=>m._probe_input(write(m,0,'Ab\bC\n')));run('tty_askname',()=>[],'prepared erase-key synchronization');assert.equal(text(reference,reference._probe_name()),'AC','Native name edit removes preceding byte');assert.equal(text(hybrid,hybrid._probe_name()),text(reference,reference._probe_name()));
run('tty_suspend_nhwindows',m=>[write(m,0,'Paused')]);run('tty_resume_nhwindows');
run('end_glyphout');run('setclipped');run('tty_cliparound',()=>[10,10]);run('newclipping',()=>[10,10]);
for(const [char,color,special,rgb,idx]of [[65,L.CLR_RED,0,0,0],[0xe1,L.NO_COLOR,L.MG_PET,0,0],[95,L.CLR_BLUE,L.MG_DETECT,0,0],[64,L.CLR_GREEN,L.MG_OBJPILE,0x00ff00,42]]){
 both(m=>{m._probe_set(5,1n);m._probe_graphics(L.H_DEC,256,1,1,1,0);});
 run('tty_print_glyph',m=>[ids.map,10,10,m._probe_glyph(0,char,color,special,rgb,idx,0n),m._probe_glyph(1,32,L.NO_COLOR,0,0,0,0n)]);
}
both(m=>m._probe_graphics(L.H_UTF8,16777216,1,1,1,0));run('tty_print_glyph',m=>[ids.map,11,10,m._probe_glyph(0,42,L.CLR_BLUE,0,0,0,write(m,0,'\xe2\x97\x86')),0]);
run('docorner',()=>[0,5,1]);
run('tty_ctrl_nhwindow',m=>[ids.map,0,m._probe_buffer(0)]);
run('tty_update_inventory',()=>[0]);
// Real source menu construction owns native nodes, strings, pages and selections.
function addItem(id,ordinal,group=0){return run('tty_add_menu',m=>{const p=Number(m._probe_buffer(2));new FixtureDataView(m.HEAPU8.buffer).setBigUint64(p,0xfedcba9876540000n+BigInt(ordinal),true);return[id,m._probe_glyph(0,64,L.NO_COLOR,0,0,0,0n),p,ordinal?97+(ordinal-1)%26:0,group,L.ATR_NONE,L.NO_COLOR,write(m,0,'Item '+ordinal),0];});}
const paged=create(L.NHW_MENU);
run('tty_start_menu',()=>[paged,0]);for(let i=1;i<=26;i++)addItem(paged,i);
run('tty_end_menu',m=>[paged,write(m,0,'Multiple pages')]);
const pages=new FixtureDataView(reference.HEAPU8.buffer).getBigInt64(Number(reference._probe_window(paged))+L.offset_struct_WinDesc_npages,true);
assert.ok(pages>1n,'Actual original menu builds multiple native page pointers');
both(m=>m._probe_input(write(m,0,'>.\n')));
run('tty_select_menu',m=>[paged,L.PICK_ANY,m._probe_ints()],'native multiple-page navigation');
assert.ok(Number(BigInt.asIntN(32,reference._probe_return()))>0,'Native page selection reaches a positive selected list');
selectionObservationContract();
const pageSelections=modules.map(m=>{const p=new FixtureDataView(m.HEAPU8.buffer).getBigUint64(Number(m._probe_ints()),true),n=Number(m._probe_return());const bytes=Buffer.from(m.HEAPU8.slice(Number(p),Number(p)+n*L.struct_mi_size)).toString('hex');m._probe_release(p);return bytes;});
assert.equal(pageSelections[1],pageSelections[0],'Full native selected records after page navigation');
// Clear the caller's now-dangling selection output before its unrelated reuse.
both(m=>m.HEAPU8.fill(0,Number(m._probe_ints()),Number(m._probe_ints())+8));
run('tty_destroy_nhwindow',()=>[paged]);

run('tty_start_menu',()=>[ids.menu,0]);for(let i=1;i<=5;i++)addItem(ids.menu,i,i===1?48:71);run('tty_end_menu',m=>[ids.menu,write(m,0,'Choose an item')]);
const head=m=>m._probe_menu_item(ids.menu,0);
run('toggle_menu_curr',m=>[ids.menu,head(m),0,0,1,9007199254740993n]);
run('set_item_state',m=>[ids.menu,0,head(m)]);
run('toggle_menu_curr',m=>[ids.menu,head(m),0,0,0,0]);
run('set_all_on_page',m=>[ids.menu,head(m),0]);run('unset_all_on_page',m=>[ids.menu,head(m),0]);run('invert_all_on_page',m=>[ids.menu,head(m),0,0,-1]);run('invert_all',m=>[ids.menu,head(m),0,71,9007199254740993n]);
run('toggle_menu_attr',()=>[1,L.CLR_RED,L.ATR_BOLD]);run('toggle_menu_attr',()=>[0,L.CLR_RED,L.ATR_BOLD]);
run('unset_all_on_page',m=>[ids.menu,head(m),0]);
both(m=>m._probe_input(write(m,0,'0')));run('tty_select_menu',m=>[ids.menu,L.PICK_ONE,m._probe_ints()],'digit group goto');assert.equal(Number(BigInt.asIntN(32,reference._probe_return())),1,'Native digit group label selects its unique member');both(m=>{const p=new FixtureDataView(m.HEAPU8.buffer).getBigUint64(Number(m._probe_ints()),true);assert.equal(new FixtureDataView(m.HEAPU8.buffer).getBigUint64(Number(p),true),0xfedcba9876540001n,'Original whole anything identifier survives native selection');m._probe_release(p);});
for(const command of [String.fromCharCode(L.MENU_SELECT_ALL)+'\n',String.fromCharCode(L.MENU_INVERT_ALL)+'\n','a','\x1b']){
 both(m=>m._probe_input(write(m,0,command)));const counts=run('tty_select_menu',m=>[ids.menu,L.PICK_ANY,m._probe_ints()],JSON.stringify(command));assert.equal(counts[1],counts[0]);
 const selections=modules.map(m=>{const p=new FixtureDataView(m.HEAPU8.buffer).getBigUint64(Number(m._probe_ints()),true);const rows=[];for(let i=0;i<Number(BigInt.asIntN(32,m._probe_return()));i++)rows.push(Buffer.from(m.HEAPU8.slice(Number(p)+i*24,Number(p)+(i+1)*24)).toString('hex'));if(p)m._probe_release(p);return rows;});assert.deepEqual(selections[1],selections[0],'Full native menu selection records');
}
both(m=>m._probe_input(write(m,0,'\x1b')));run('process_menu_window',m=>[ids.menu,win(m,'menu')]);
run('dmore',m=>[win(m,'menu'),write(m,0,' ')])
run('tty_putstr',m=>[ids.text,L.ATR_BOLD,write(m,0,'Text window body')]);run('process_text_window',m=>[ids.text,win(m,'text')]);run('tty_display_nhwindow',()=>[ids.text,1]);run('tty_dismiss_nhwindow',()=>[ids.text]);run('erase_menu_or_text',m=>[ids.text,win(m,'text'),0]);
for(const how of [L.PICK_NONE,L.PICK_ONE]){both(m=>m._probe_input(write(m,0,' ')));run('tty_message_menu',m=>[120,how,write(m,0,'Message selection')]);}
run('tty_clear_nhwindow',()=>[ids.text]);
run('tty_status_init');
for(const fld of [L.BL_TITLE,L.BL_LEVELDESC,L.BL_GOLD,L.BL_HP,L.BL_HPMAX,L.BL_ENE,L.BL_ENEMAX,L.BL_AC,L.BL_CAP,L.BL_HUNGER,L.BL_CONDITION]){
 run('tty_status_enablefield',m=>[fld,write(m,0,'field '+fld),write(m,1,' %s'),1]);
 if(fld===L.BL_CONDITION){run('tty_status_update',m=>{const p=Number(m._probe_buffer(0));new FixtureDataView(m.HEAPU8.buffer).setBigInt64(p,BigInt(L.BL_MASK_BLIND)|BigInt(L.BL_MASK_CONF),true);m.HEAPU8.fill(0,p+32,p+32+8*32);return[fld,p,0,50,L.NO_COLOR,p+32];});}
 else run('tty_status_update',m=>[fld,write(m,0,fld===L.BL_TITLE?'Tester the Adventurer':fld===L.BL_LEVELDESC?'Dlvl:5    ':fld===L.BL_CAP?'Burdened':fld===L.BL_HP?'10':' 20 '),0,50,L.CLR_RED,0]);
}
run('check_windowdata');run('check_fields',m=>[0,m._probe_ints()]);run('make_things_fit',()=>[0]);run('set_condition_length');run('shrink_enc',()=>[1]);run('shrink_dlvl');
run('condcolor',m=>[L.BL_MASK_BLIND,m._probe_buffer(1)]);run('condattr',m=>[L.BL_MASK_BLIND,m._probe_buffer(1)]);
run('render_status');run('tty_putstatusfield',m=>[write(m,0,'status bytes'),1,0]);run('tty_status_update',()=>[L.BL_FLUSH,0,0,0,0,0]);
run('new_status_window');
both(m=>{m._probe_option(1,30);m._probe_option(2,100);});run('resize_tty');
assert.equal(hybrid._probe_callback_kind(services.get(hybrid).callbackPointer('winch_handler')),0,'Production signal trampoline has actual native callable identity');
run('winch_handler',()=>[L.SIGWINCH]);both(m=>m._probe_set(3,1n));both(m=>m._probe_signal(L.SIGWINCH));assert.deepEqual(text(hybrid,hybrid._probe_snapshot()),text(reference,reference._probe_snapshot()),'Actual native signal callback reentry');both(m=>m._probe_set(3,0n));
run('erase_tty_screen');
run('free_window_info',m=>[win(m,'text'),0]);run('tty_destroy_nhwindow',()=>[ids.text]);
// Reversing twice restores the same owned list before normal destruction.
for(let pass=0;pass<2;pass++){const values=run('reverse',m=>[head(m)]);modules.forEach((m,i)=>new FixtureDataView(m.HEAPU8.buffer).setBigUint64(Number(win(m,'menu'))+L.offset_struct_WinDesc_mlist,values[i],true));}
run('tty_destroy_nhwindow',()=>[ids.menu]);
run('tty_exit_nhwindows',m=>[write(m,0,'Finished')]);
// bail owns teardown; give it a new live terminal rather than exiting twice.
run('tty_init_nhwindows',m=>[m._probe_ints(),0]);
run('bail',m=>[write(m,0,'Exit path')]);assert.equal(reference._probe_error(),1,'Native noreturn termination path captured');
// Cached environments use the current call facade, restore it after native
// reentry/throws, and never publish a failed constructor for a layout identity.
const baseServices=services.get(hybrid),events=[];
let leakedOverride=0;baseServices.fflush=()=>{leakedOverride++;return 0;};
hybrid._probe_invoke(names.indexOf('tty_mark_synch'),...Array(9).fill(0n));
const nextFacade=services.get(hybrid);assert.notEqual(nextFacade,baseServices,'Every imported call gets a fresh services facade');
assert.equal(Object.getPrototypeOf(nextFacade),Object.getPrototypeOf(baseServices),'Only internal Module-bound dependency packet is reused');
assert.equal(leakedOverride,0,'A previous facade override cannot leak into later imported calls');delete baseServices.fflush;
const facade=overrides=>Object.assign(Object.create(baseServices),overrides);
let reenter=false;
const inner=facade({fflush:()=>{events.push('inner');return 0;}});
const outer=facade({fflush:()=>{events.push('outer');if(!reenter){reenter=true;callWintty(inner,L,'tty_mark_synch');if(nativeExecution)winttyState(baseServices).environments.get(L).environment.nativeNamespace.tty_mark_synch();else core.tty_mark_synch();}return 0;}});
const env=createWinttyEnvironment(baseServices,L,winttyState(baseServices));
const oldMask=env.tty_procs.wincap2;
hybrid._probe_mutate_catalogue(0,0xfedcba9876543210n);
assert.equal(env.tty_procs.wincap2,0xfedcba9876543210n,'External native catalogue mutation remains live in JS');
hybrid._probe_mutate_catalogue(0,oldMask);
assert.equal(env.tty_procs.wincap2,oldMask);
const more=write(hybrid,0,'Native!');hybrid._probe_more(more);
assert.equal(text(hybrid,env.defmorestr),'Native!','External C array mutation remains live in JS');
hybrid._probe_more(write(hybrid,0,core.defmorestr_initial));
const savedStack=hybrid._probe_stack();
callWintty(outer,L,'tty_mark_synch');assert.deepEqual(events,['outer','inner','outer'],'Nested source entry restores outer current services');
const marker=new Error('controlled native callback exception');
assert.throws(()=>callWintty(facade({fflush:()=>{throw marker;}}),L,'tty_mark_synch'),e=>e===marker);
let afterThrow=0;callWintty(facade({fflush:()=>{afterThrow++;return 0;}}),L,'tty_mark_synch');assert.equal(afterThrow,1);
assert.equal(hybrid._probe_stack(),savedStack,'Original source frames restored after reentry and exception');
const retryLayout={...L,width_struct_DisplayDesc_curx:99};
assert.throws(()=>callWintty(baseServices,retryLayout,'tty_get_nh_event'),/field width/);
retryLayout.width_struct_DisplayDesc_curx=L.width_struct_DisplayDesc_curx;
callWintty(baseServices,retryLayout,'tty_get_nh_event');
assert.notEqual(winttyState(baseServices).environments.get(L).environment,winttyState(baseServices).environments.get(retryLayout).environment,'Distinct immutable layout identities have separate validated environments');
// A fresh actual hybrid Module owns independent native catalogue/static backing.
const second=await hybridFactory({...options(1),stdout:()=>{},print:()=>{},printErr:()=>{},nethackPorted:runtime});
const secondServices=services.get(second);
assert.ok(secondServices);assert.notEqual(secondServices.moduleKey,baseServices.moduleKey);
assert.notEqual(winttyState(secondServices),winttyState(baseServices));
assert.deepEqual(catalogue(second,second._probe_startup_catalogue()),catalogue(reference,reference._probe_startup_catalogue()),'Second Module constructor independently receives original catalogue');
const firstCap=new FixtureDataView(hybrid.HEAPU8.buffer).getBigUint64(Number(hybrid._probe_live_catalogue())+L.offset_struct_window_procs_wincap2,true);
second._probe_mutate_catalogue(0,0xfedcba9876543210n);
assert.equal(new FixtureDataView(hybrid.HEAPU8.buffer).getBigUint64(Number(hybrid._probe_live_catalogue())+L.offset_struct_window_procs_wincap2,true),firstCap,'Native table mutation cannot cross Module memory');
assert.deepEqual(names.filter(n=>!seen.has(n)),[],'Every original configured function entered');
console.log(`WINTTY: ${comparisons} exact EmC comparisons, all72functions; actual ncurses/termcap, native constructor catalogue, stdio/cursor/shadow, menu ownership, status and signal callback pass.`);
