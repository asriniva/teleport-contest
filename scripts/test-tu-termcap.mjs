import {nativeFixtureServices} from './native-pet-combat-fixture.mjs';
const nativeExecution=process.env.NATIVE_TERMCAP_FIXTURE==='1',nativeServices=new WeakMap();
import './pure-js-probes/deny-wasm.mjs';
import {createProbe,createReference,loadFixture,fixtureImports} from './pure-js-fixtures/load.mjs';
import {DataView as FixtureDataView} from './native-test-backend.mjs';
// Original C reference is available through the isolated reference process.
// Configured original-C versus JS caller policy, separate from game/capture encoding.
import assert from './native-test-assert.mjs';
import {readFile,writeFile,mkdir} from 'node:fs/promises';
import {writeFileSync} from 'node:fs';
import {resolve} from 'node:path';
import {pathToFileURL} from 'node:url';
import {spawnSync} from 'node:child_process';
import {C,withCEnvironment} from '../js/c-runtime/context.js';
import * as core from '../js/ported/termcap.js';
import {callTermcap,createTermcapEnvironment} from '../js/nethack/bindings/termcap.js';
import {createLibraryBindings} from '../js/c-runtime/library-bindings.js';
import {checkTermcapSource} from '../nethack-c/wasm/tu-fragments/termcap-source-check.mjs';
const callbackOnly=process.argv.includes('--callback-only');
const jsDependencies=process.argv.includes('--js-dependencies'),unwrapped=process.argv.includes('--unwrapped')||jsDependencies,prefix=callbackOnly?'termcap-callback-':jsDependencies?'termcap-js-dependencies-':unwrapped?'termcap-unwrapped-':'termcap-';
const dir=resolve(process.env.TERMCAP_PROBE_DIR??'.cache/tu-probes');
const schema=JSON.parse(await readFile('nethack-c/wasm/tu-fragments/termcap-schema.json','utf8'));
const helpers='canonical reset clear_trace option override pointer trace error stack last_output_pointer layout_count layout_name layout_value callback_pointer invoke_callback expected_callback constant'.split(' ');
if(process.argv.includes('--build')){
 await mkdir(dir,{recursive:true});checkTermcapSource();
 const defines=JSON.parse(await readFile('nethack-c/wasm/compile-defines.json','utf8'));
 let exported=helpers.map(n=>'_probe_'+n).concat(['global','read','write','address'].map(n=>'_teleport_termcap_'+n),schema.functions.map(f=>'_probe_call_'+f.name),'getenv putchar fflush free tgetent tgetnum tgetflag tgetstr tputs'.split(' ').map(n=>'___wrap_'+n));
 if(callbackOnly)exported=helpers.map(n=>'_probe_'+n).concat(['global','read','write','address'].map(n=>'_teleport_termcap_'+n),'_probe_call_term_start_screen');
 const base=['-O2','-sMEMORY64=1','-sMODULARIZE=1','-sENVIRONMENT=node','-sALLOW_MEMORY_GROWTH=1','-sSTACK_SIZE=4194304','-sSUPPORT_LONGJMP=emscripten','--no-entry','-sEXPORTED_RUNTIME_METHODS=HEAPU8,FS,ENV','-sEXPORTED_FUNCTIONS='+JSON.stringify(exported),...defines.map(s=>'-D'+s),'-I'+resolve('.cache/wasm64-build/tree/include'),'-I'+resolve('.cache/ncurses-wasm64-build/include'),'-I'+resolve('scripts'),'-include',resolve('nethack-c/wasm/native-terminal.h'),'-fmacro-prefix-map='+resolve('scripts')+'/../.cache/wasm64-build/tree/win/tty/=../win/tty/',...((unwrapped||callbackOnly)?['-DTERMCAP_UNWRAPPED=1']:'getenv putchar fflush free tgetent tgetnum tgetflag tgetstr tputs'.split(' ').map(n=>'-Wl,--wrap='+n)),resolve('scripts/tu-termcap-probe.c'),resolve('.cache/ncurses-wasm64-build/lib/libtinfo.a')];
 if(jsDependencies){base.splice(base.indexOf(resolve('.cache/ncurses-wasm64-build/lib/libtinfo.a')),1);base.push(resolve('nethack-c/wasm/dependency-bridge.c'),'--js-library',resolve('nethack-c/wasm/dependency-library.js'));}
 for(const mode of ['reference','hybrid']){const args=[...base,...(mode==='hybrid'?['-DHYBRID_TERMCAP=1','--js-library',resolve('nethack-c/wasm/tu-libraries/termcap.js')]:[]),'-o',resolve(dir,prefix+mode+'.mjs')];const p=spawnSync(resolve('.cache/emsdk/upstream/emscripten/emcc'),args,{encoding:'utf8',maxBuffer:32*1024*1024});await writeFile(resolve(dir,'build-'+mode+'-'+Date.now()+'.log'),JSON.stringify({args,status:p.status})+'\n'+p.stdout+p.stderr);if(p.status!==0)throw Error('TERMCAP '+mode+' compile failed; private raw build log preserved');}
}
const wasm=await readFile(resolve(dir,prefix+'hybrid.wasm'));
const imports=(await fixtureImports("termcap")).filter(v=>v.kind==='function').map(v=>v.name);
if(!callbackOnly)for(const f of schema.functions)assert.ok(imports.includes(f.static?'teleport_termcap_test_'+f.name:f.name),'actual JS policy import '+f.name);
assert.ok(imports.includes('teleport_termcap_callback_tty_decgraphics_termcap_fixup'));
const factories=await Promise.all(['reference','hybrid'].map(async mode=>(await loadFixture("termcap",pathToFileURL(resolve(dir,prefix+mode+'.mjs')).href)).default));
const entry=await readFile('nethack-c/wasm/terminfo/x/xterm-256color');
const text=(m,p)=>{let at=Number(p),end=at;assert.ok(at>=0&&at<m.HEAPU8.length);while(end<m.HEAPU8.length&&m.HEAPU8[end])end++;assert.ok(end<m.HEAPU8.length,'C NUL terminator');return Buffer.from(m.HEAPU8.subarray(at,end)).toString('latin1');};
const layout=m=>{const out={};for(let i=0;i<m._probe_layout_count();i++)out[text(m,m._probe_layout_name(i))]=m._probe_layout_value(i);return out;};
const moduleOptions=(environment={})=>{const output=[];return {probeOutput:output,...(jsDependencies?{nethackDependencies:createLibraryBindings()}:{}),noInitialRun:true,print:v=>output.push(['out',v]),printErr:v=>output.push(['err',v]),preRun:[m=>{Object.assign(m.ENV,{TERM:'xterm-256color',TERMINFO:'/nethack/terminfo',NETHACK_NO_DELAY:'1',NOMUX_MARKERS:'1',LINES:'24',COLUMNS:'80',HOME:'/home/player',LANG:'C',LC_ALL:'C',...environment});m.FS.mkdirTree('/nethack/terminfo/x');m.FS.writeFile('/nethack/terminfo/x/xterm-256color',entry);}]};};
const reference=await factories[0](moduleOptions()),L=layout(reference),servicesByModule=new WeakMap(),calls=new Map();
// wasm-ld --wrap instruments C relocations, while JS-library closures retain
// the raw exports. This private provider sends both callers through the SAME
// real C instrumentation. The production library and source remain unchanged.
function observeServices(services){const m=services.moduleKey,p=v=>BigInt(v?.address??v??0),str=v=>typeof v==='string'?BigInt(services.literal(v)):p(v),ptr=v=>v<=BigInt(Number.MAX_SAFE_INTEGER)?Number(v):v;return Object.assign(Object.create(services),{
 getenv:v=>ptr(m.___wrap_getenv(str(v))),putchar:v=>m.___wrap_putchar(Number(v)|0),fflush:v=>m.___wrap_fflush(p(v)),free:v=>m.___wrap_free(p(v)),
 tgetent:(b,n)=>m.___wrap_tgetent(str(b),str(n)),tgetnum:n=>m.___wrap_tgetnum(str(n)),tgetflag:n=>m.___wrap_tgetflag(str(n)),tgetstr:(n,a)=>ptr(m.___wrap_tgetstr(str(n),p(a))),tputs:(v,n,c)=>m.___wrap_tputs(str(v),Number(n)|0,p(c)),
});}
const runtime={termcap(services,name,...args){if(nativeExecution){let local=nativeServices.get(services);if(!local){local=nativeFixtureServices(services,{}).services;local.nativeTypes=services.moduleKey.environment.ctypes;nativeServices.set(services,local);}services=local;}servicesByModule.set(services.moduleKey,services);calls.set(name,(calls.get(name)??0)+1);return callTermcap(unwrapped||callbackOnly?services:observeServices(services),L,name,...args);}};
const hybrid=await factories[1]({...moduleOptions(),nethackPorted:runtime}),modules=[reference,hybrid];assert.deepEqual(layout(hybrid),L);
let cases=0,comparisons=0,active='';const invoked=new Set(),names=Object.keys(schema.schema),globals=schema.globals;
const both=(name,...args)=>modules.map(m=>m['_probe_'+name](...args));
const pointer=(m,kind,index=0)=>m._probe_pointer(kind,index);
const global=(m,name)=>{const i=globals.findIndex(g=>g.name===name);assert.notEqual(i,-1,name);return m._teleport_termcap_global(i);};
const field=(kind,name)=>{const i=schema.schema[kind].fields.findIndex(f=>f.name===name);assert.notEqual(i,-1,kind+'.'+name);return i;};
const read=(m,kind,p,name)=>m._teleport_termcap_read(names.indexOf(kind),p,field(kind,name));
const write=(m,kind,p,name,value)=>m._teleport_termcap_write(names.indexOf(kind),p,field(kind,name),BigInt.asUintN(64,BigInt(value)));
const width=d=>d.t?Number(d.t.slice(1))/8:d.p!==undefined||d.f?8:d.s?Number(L[d.s+'Size']):d.a.reduce((a,b)=>a*b,1)*width(d.e);
// In this guarded configured schema, every opaque root pointer except stdout
// is one of the original char* capabilities. ttyDisplay has a record target.
const charPointers=new Set(globals.filter(g=>g.d.p===''&&g.name!=='stdout').map(g=>g.name));
function state(m){const out=[],dv=new FixtureDataView(m.HEAPU8.buffer);
 const scalar=(d,v,path,ctype)=>{if(d.p!==undefined){const canonical=m._probe_canonical(v);out.push([path,canonical===0xffffffffffffffffn?'foreign:'+((ctype??'').includes('char')||charPointers.has(path)?text(m,v):'opaque'):canonical.toString()]);if((ctype??'').includes('char')||charPointers.has(path))out.push([path+'.text',v?(canonical!==0xffffffffffffffffn&&(canonical>>63n)?'<freed native allocation>':text(m,v)):null]);}else if(d.f)out.push([path,v===0n?0:v===m._probe_callback_pointer(0)?'xputc':v===m._probe_callback_pointer(1)?'decgraphics':v===m._probe_callback_pointer(2)?'utf8graphics':'unknown']);else out.push([path,v.toString()]);};
 const value=(d,at,path,ctype='')=>{if(d.s){for(const f of schema.schema[d.s].fields){const v=read(m,d.s,at,f.name);if(f.d.s||f.d.a)value(f.d,v,path+'.'+f.name,f.ctype);else scalar(f.d,v,path+'.'+f.name,f.ctype);}return;}if(d.a){const child=d.a.length===1?d.e:{a:d.a.slice(1),e:d.e};for(let i=0;i<d.a[0];i++)value(child,at+BigInt(i*width(child)),path+'['+i+']',ctype);return;}const bytes=width(d);let v=0n;for(let i=0;i<bytes;i++)v|=BigInt(dv.getUint8(Number(at)+i))<<BigInt(8*i);scalar(d,v,path,ctype);};
 for(const g of globals)value(g.d,global(m,g.name),g.name,charPointers.has(g.name)||g.name==='hilites'?'char *':'');
 value({s:'DisplayDesc'},pointer(m,2),'display');for(let i=0;i<8;i++)out.push(['int'+i,dv.getInt32(Number(pointer(m,1,i)),true)]);return out;
}
function evidence(extra={}){writeFileSync(resolve(dir,'failure-'+Date.now()+'.json'),JSON.stringify({active,...extra,reference:{trace:text(reference,reference._probe_trace()),error:reference._probe_error(),state:state(reference)},hybrid:{trace:text(hybrid,hybrid._probe_trace()),error:hybrid._probe_error(),state:state(hybrid)}},(_,v)=>typeof v==='bigint'?v.toString():v,2)+'\n');}
const stacks=modules.map(m=>m._probe_stack());
function compare(){const actual=state(hybrid),expected=state(reference);const first=actual.findIndex((v,i)=>JSON.stringify(v)!==JSON.stringify(expected[i]));assert.equal(first,-1,'TERMCAP state '+active+' mismatch '+JSON.stringify([actual[first],expected[first]]));assert.equal(text(hybrid,hybrid._probe_trace()),text(reference,reference._probe_trace()),'TERMCAP trace '+active);assert.equal(hybrid._probe_error(),reference._probe_error());assert.deepEqual(hybrid.probeOutput,reference.probeOutput,'actual stdio output '+active);comparisons+=4;for(let i=0;i<2;i++){assert.equal(modules[i]._probe_stack(),stacks[i]);comparisons++;}assert.equal(C,undefined);comparisons++;}
function reset(label){active=label;cases++;both('reset');}
function input(value,index=0){for(const m of modules){const bytes=Buffer.from(value+'\0','latin1');assert.ok(bytes.length<=8192);m.HEAPU8.set(bytes,Number(pointer(m,0,index)));}}
function action(name,...args){if(process.env.TERMCAP_VERBOSE)console.log(active,name);invoked.add(name);const f=schema.functions.find(f=>f.name===name),ret=f.type.qualType.split('(')[0].trim();const actual=modules.map(m=>m['_probe_call_'+name](...args.map(a=>BigInt(typeof a==='function'?a(m):a))));const normalized=actual.map((v,i)=>ret.includes('*')?v?text(modules[i],v):null:BigInt.asIntN(64,v).toString());try{assert.deepEqual(normalized[1],normalized[0],name+' return');compare();}catch(error){evidence({name,actual,normalized});throw error;}return actual;}

if(callbackOnly){
 assert.deepEqual(imports.filter(n=>n.startsWith('teleport_termcap_test_')),[],'production closure has no private fixture aliases');
 reset('production source callback publication');action('term_start_screen');for(let which=0;which<3;which++){reset('production actual indirect callback '+which);for(const m of modules){assert.equal(m._probe_callback_pointer(which),m._probe_expected_callback(which));comparisons++;}both('invoke_callback',which,65);compare();}
 await writeFile(resolve(dir,'callback-summary.json'),JSON.stringify({status:'pass',cases,comparisons,policyImports:imports.filter(n=>schema.functions.some(f=>f.name===n)||n.startsWith('teleport_termcap_')),noPrivateTestImports:true,nativeHost:'pending',game:'pending'},null,2)+'\n');console.log('TERMCAP production callback closure: '+cases+' cases / '+comparisons+' checks; zero private test imports');process.exit(0);
}
// Source initialization happens through a real original entry, not a test-only
// write into C const data or a surrogate reference static-buffer helper.
reset('first real entry initializes JS source storage');action('nomux_end_attr');
reset('pinned terminal startup');action('term_startup',m=>pointer(m,1),m=>pointer(m,1,1));
const argMap={term_startup:[m=>pointer(m,1),m=>pointer(m,1,1)],tty_number_pad:[1],nocmov:[3,2],cmov:[4,5],xputc:[65],nomux_emit_marker:[m=>pointer(m,0)],nomux_clear_to_eol:[0,0],nomux_putch:[65],nomux_set_attr:[Number(L.ATR_BOLD)],nomux_set_fg:[Number(L.CLR_RED)],nomux_sgr_fg:[9],nomux_raw_putch:[65],nomux_raw_emit:[m=>pointer(m,0),1],nomux_get_cursor:[m=>pointer(m,1),m=>pointer(m,1,1)],xputs:[m=>pointer(m,0)],s_atr2str:[Number(L.ATR_BOLD)],e_atr2str:[Number(L.ATR_BOLD)],term_attr_fixup:[63],term_start_attr:[Number(L.ATR_BOLD)],term_end_attr:[Number(L.ATR_BOLD)],term_start_color:[Number(L.CLR_RED)],term_start_bgcolor:[5],term_curs_set:[0],emit24bit:[0x123456],emit256:[123],term_start_extracolor:[0x123456,123]};
const filter=process.env.TERMCAP_FILTER?new RegExp(process.env.TERMCAP_FILTER):null;
for(const f of schema.functions){if(filter&&!filter.test(f.name)||f.name==='term_startup'||f.name==='term_shutdown'||f.name==='kill_hilite')continue;reset('initial '+f.name);input(f.name==='nomux_emit_marker'?'input':'sample');assert.ok(!f.parameters.length||Object.hasOwn(argMap,f.name),'explicit valid '+f.name);action(f.name,...(argMap[f.name]??[]));}

// Valid boundary values and retained source branches; each mutation is applied
// to both actual native stores, never to a copied policy model.
function setGlobal(name,v){const g=globals.find(x=>x.name===name);assert.ok(g&&!g.d.s&&!g.d.a);for(const m of modules){const at=Number(global(m,name)),dv=new FixtureDataView(m.HEAPU8.buffer),n=typeof v==='function'?v(m):v;if(g.d.p!==undefined||g.d.f)dv.setBigUint64(at,BigInt(n),true);else dv['setUint'+(width(g.d)*8)](at,Number(n),true);}}
function setField(root,kind,name,v){for(const m of modules)write(m,kind,root(m),name,typeof v==='function'?v(m):v);}
const display=m=>pointer(m,2),iflags=m=>global(m,'iflags'),tc=m=>global(m,'tc_lcl_data');
if(!unwrapped){
for(const n of [-2147483648,-1,0,1,7,8,15,16,2147483647]){reset('SGR/color range '+n);action('nomux_sgr_fg',n);action('nomux_set_fg',n);}
for(const dark of [0,1]){setField(iflags,'instance_flags','wc2_darkgray',dark);reset('darkgray '+dark);action('nomux_set_fg',Number(L.CLR_BLACK));}setField(iflags,'instance_flags','wc2_darkgray',0);
for(const n of [0,1,2,3,4,5,6,7,31,-1]){reset('attributes '+n);action('s_atr2str',n);action('e_atr2str',n);action('term_start_attr',n);action('term_end_attr',n);}
for(const mask of [0,1,2,4,8,16,31,63,-1]){reset('attribute capability mask '+mask);action('term_attr_fixup',mask);}
setField(tc,'tc_lcl_data','tc_US',0);setGlobal('MB',0);setGlobal('MH',0);
for(const mask of [0,1,2,4,8,16,31,63,-1]){reset('missing attributes mask '+mask);action('term_attr_fixup',mask);action('s_atr2str',mask);action('e_atr2str',mask);}
for(const [row,col,ch]of [[0,0,32],[23,79,255],[-1,0,65],[24,0,66],[0,-1,67],[0,80,68],[2,3,31],[2,3,128]]){reset('shadow coordinates '+[row,col,ch]);setField(display,'DisplayDesc','cury',row);setField(display,'DisplayDesc','curx',col);action('nomux_putch',ch);}
for(const [row,col]of [[-1,0],[24,0],[0,-4],[23,79],[5,80]]){reset('clear eol '+[row,col]);action('nomux_clear_to_eol',row,col);}
reset('all cells defined and bounded serializer');action('nomux_clear_screen');
for(const m of modules){const start=global(m,'nomux_buf');for(let row=0;row<24;row++)for(let col=0;col<80;col++){const at=start+BigInt((row*80+col)*Number(L.nomux_cellSize));for(const[name,value]of [['ch',65+(row+col)%26],['fg',row%16],['attr',row%8],['decgfx',row%2]])write(m,'nomux_cell',at,name,value);}}
action('nomux_capture_screen');action('nomux_capture_write_screen');action('nomux_capture_write_input_boundary');
// Full C-owned screens vary signed character bytes, defaults, colors,
// attributes, DEC transitions and trailing blanks across reused live views.
for(let seed=1;seed<=8;seed++){
 reset('seeded full-screen capture '+seed);
 let random=seed;const next=()=>random=(Math.imul(random,1664525)+1013904223)>>>0;
 // C's inherited output buffer is only 24*256 bytes. Share styling within
 // 20-cell runs: even maximal transitions then fit without C overflow.
 let style;
 const cells=Array.from({length:24*80},(_,i)=>{if(i%20===0)style=next();const value=next();return [['ch',[0,32,65,127,128,255][value%6]],['fg',(style>>>8)%16],['attr',(style>>>16)%8],['decgfx',(style>>>24)%2]];});
 for(const m of modules){const start=global(m,'nomux_buf');for(let i=0;i<cells.length;i++)for(const[name,value]of cells[i])write(m,'nomux_cell',start+BigInt(i*Number(L.nomux_cellSize)),name,value);}
 action('nomux_capture_screen');action('nomux_capture_write_input_boundary');
}
reset('raw transitions newline clipping and non-ASCII bytes');action('nomux_enter_raw_mode');input('A\x1b\t\n'+String.fromCharCode(128,255)+'z');action('nomux_raw_emit',m=>pointer(m,0),1);for(const ch of [10,13,31,32,255])action('nomux_raw_putch',ch);action('nomux_raw_emit_eol');action('nomux_get_cursor',m=>pointer(m,1),m=>pointer(m,1,1));action('nomux_capture_screen');
for(const visibility of [0,0,1,1,2,-1]){reset('cached cursor visibility '+visibility);action('term_curs_set',visibility);}
for(const n of [-1n,0n,0xffffffn,0x123456789abcdefn,-0x8000000000000000n]){reset('RGB signed long '+n);action('emit24bit',n);}
for(const n of [-2147483648,-1,0,255,256,2147483647]){reset('indexed color int '+n);action('emit256',n);}
for(const count of [8,16,256]){setField(iflags,'instance_flags','colorcount',count);reset('extra color dispatch '+count);action('term_start_extracolor',0xffffffff,65535);}
// Observe real original static addresses via output, not the reference-only
// transport helper's unrelated backing. Different emit functions have distinct
// persistent buffers; successive invocations of each reuse its actual address.
reset('native static color buffer identities');action('emit24bit',0x123456);const rgb=modules.map(m=>m._probe_last_output_pointer());action('emit256',12);const indexed=modules.map(m=>m._probe_last_output_pointer());action('emit24bit',0x654321);for(let i=0;i<2;i++){assert.equal(modules[i]._probe_last_output_pointer(),rgb[i]);assert.notEqual(rgb[i],indexed[i]);comparisons+=2;}action('emit256',34);for(let i=0;i<2;i++){assert.equal(modules[i]._probe_last_output_pointer(),indexed[i]);comparisons++;}
reset('DEC fallback actual static buffers and indirect callback');
setField(m=>read(m,'instance_globals_t',global(m,'gt'),'tc_gbl_data'),'tc_gbl_data','tc_AS',0);
setField(m=>read(m,'instance_globals_t',global(m,'gt'),'tc_gbl_data'),'tc_gbl_data','tc_AE',0);setGlobal('KS',0);setGlobal('KE',0);
action('tty_decgraphics_termcap_fixup');const fallback=modules.map(m=>[read(m,'tc_gbl_data',read(m,'instance_globals_t',global(m,'gt'),'tc_gbl_data'),'tc_AS'),read(m,'tc_gbl_data',read(m,'instance_globals_t',global(m,'gt'),'tc_gbl_data'),'tc_AE')]);action('tty_decgraphics_termcap_fixup');for(let i=0;i<2;i++){assert.equal(read(modules[i],'tc_gbl_data',read(modules[i],'instance_globals_t',global(modules[i],'gt'),'tc_gbl_data'),'tc_AS'),fallback[i][0]);assert.equal(read(modules[i],'tc_gbl_data',read(modules[i],'instance_globals_t',global(modules[i],'gt'),'tc_gbl_data'),'tc_AE'),fallback[i][1]);assert.equal(text(modules[i],fallback[i][0]),'\x0e');assert.equal(text(modules[i],fallback[i][1]),'\x0f');comparisons+=4;}
reset('actual C indirect xputc callback');assert.deepEqual(both('invoke_callback',0,90),[90,90]);compare();for(const m of modules){assert.equal(m._probe_callback_pointer(0),m._probe_expected_callback(0));comparisons++;}

for(const which of [1,2]){reset('actual stored indirect graphics callback '+which);for(const m of modules){assert.equal(m._probe_callback_pointer(which),m._probe_expected_callback(which));comparisons++;}both('invoke_callback',which,0);compare();}
for(const [name,value]of [['nomux_seq',2147483647],['nomux_anim_id',2147483647]]){reset('native signed counter rollover '+name);setGlobal(name,value);action(name==='nomux_seq'?'nomux_capture_write_input_boundary':'nomux_capture_write_screen');}
for(const [x,y]of [[0,0],[3,0],[0,3],[3,3]]){reset('relative cursor '+[x,y]);setField(display,'DisplayDesc','curx',2);setField(display,'DisplayDesc','cury',2);action('nocmov',x,y);}
reset('cursor home fallback without UP/CM');setGlobal('UP',0);setField(tc,'tc_lcl_data','tc_CM',0);setField(display,'DisplayDesc','cury',3);action('nocmov',0,1);
reset('cursor newline fallback without CM/XD');setGlobal('XD',0);setField(display,'DisplayDesc','cury',0);action('nocmov',0,2);
for(const name of ['tmspc10','ti_map']){const g=globals.find(g=>g.name===name),size=width(g.d);assert.deepEqual(Buffer.from(hybrid.HEAPU8.subarray(Number(global(hybrid,name)),Number(global(hybrid,name))+size)),Buffer.from(reference.HEAPU8.subarray(Number(global(reference,name)),Number(global(reference,name))+size)));comparisons++;}

reset('native memory growth and callback reentry');both('option',0,1);both('option',1,1);const oldBuffers=modules.map(m=>m.HEAPU8.buffer);action('xputc',65);for(let i=0;i<2;i++){assert.notEqual(modules[i].HEAPU8.buffer,oldBuffers[i]);comparisons++;}action('nomux_capture_screen');

}
reset('shutdown original allocation lifecycle');action('term_shutdown');
reset('already shut down highlight cleanup');action('kill_hilite');

if(!unwrapped){
const override=(kind,id,value,bytes='')=>{assert.equal(id.length,2);input(bytes,1);both('override',kind,(id.charCodeAt(0)<<8)|id.charCodeAt(1),value);};
for(const spec of [
 {label:'unknown terminal',caps:[[3,'en',0]]},
 {label:'missing required backspace',caps:[[0,'le',0]]},
 {label:'overstrike refusal',caps:[[2,'os',1]]},
 {label:'no cursor addressing without fallback',caps:[[0,'cm',0],[0,'up',0],[0,'ho',0]]},
 {label:'no cursor addressing with home',caps:[[0,'cm',0]]},
 {label:'standout glitch and underlining',caps:[[1,'sg',2],[2,'ul',1]]},
 {label:'8 colors alias and ownership',caps:[[1,'Co',8]],dark:0},
 {label:'8 colors darkgray ownership',caps:[[1,'Co',8]],dark:1},
 {label:'16 colors darkgray ownership',caps:[[1,'Co',16]],dark:1},
 {label:'no color fallback',caps:[[1,'Co',0]]},
 {label:'missing foreground capabilities',caps:[[0,'AF',0],[0,'Sf',0]]},
 {label:'foreground alternate Sf',caps:[[0,'AF',0],[0,'Sf',1,'\x1b[3%p1%dm']]},
 {label:'missing cursor visibility',caps:[[0,'vi',0]]},
 {label:'numeric padding prefixes',caps:[[0,'so',1,'12\x1b[7m'],[0,'me',1,'15\x1b[0m']]},
 {label:'missing final clear screen',caps:[[0,'cl',0]]},
 ]){
 reset('startup '+spec.label);setField(iflags,'instance_flags','wc2_darkgray',spec.dark??0);for(const cap of spec.caps)override(...cap);action('term_startup',m=>pointer(m,1),m=>pointer(m,1,1));
 if(!reference._probe_error()){action('term_start_screen');action('term_end_screen');}
 // Reset clears only controls and trace; source shutdown performs its own real
 // cleanup. Keep the chosen color-count override active for 8-color ownership.
 both('clear_trace');action('term_shutdown');
}
// Real native memory/service objects exercise the dispatch cache, not a fake
// layout or policy model. Count actual constructor ABI reads through a Proxy.
{
 active='cache isolation override reentry exception and retry';cases++;
 const base=observeServices(servicesByModule.get(hybrid)),initial=C,saved=hybrid._probe_stack();
 let builds=0;const cacheLayout=new Proxy({...L},{get(o,k){if(k==='pointerSize')builds++;return o[k];}});
 callTermcap(base,cacheLayout,'nomux_end_attr');const firstBuildReads=builds;assert.ok(firstBuildReads>0);callTermcap(base,cacheLayout,'nomux_end_attr');assert.equal(builds,firstBuildReads);comparisons++;
 callTermcap(base,{...L},'nomux_end_attr');assert.equal(builds,firstBuildReads);comparisons++;
 const a=createTermcapEnvironment(base,L),b=createTermcapEnvironment(base,L);assert.notEqual(a,b);assert.equal(a.state,b.state);comparisons+=2;
 const bad={...L,pointerSize:4};assert.throws(()=>callTermcap(base,bad,'nomux_end_attr'),/ABI/);bad.pointerSize=8;callTermcap(base,bad,'nomux_end_attr');comparisons++;
 let order=[];const A=Object.assign(Object.create(base),{putchar:n=>{order.push('A'+n);if(n===65){callTermcap(B,cacheLayout,'xputc',66);assert.throws(()=>callTermcap(E,cacheLayout,'xputc',67),e=>e===sentinel);order.push('restored');}return n;}}),B=Object.assign(Object.create(base),{putchar:n=>(order.push('B'+n),n)}),sentinel=Error('real service failure'),E=Object.assign(Object.create(base),{putchar:()=>{throw sentinel;}});
 assert.equal(callTermcap(A,cacheLayout,'xputc',65),65);assert.equal(callTermcap(B,cacheLayout,'xputc',68),68);assert.deepEqual(order,['A65','B66','restored','B68']);comparisons+=3;assert.equal(builds,firstBuildReads);assert.equal(C,initial);assert.equal(hybrid._probe_stack(),saved);comparisons+=3;
 const before=state(reference);callTermcap(base,L,'nomux_set_fg',2);assert.deepEqual(state(reference),before);assert.equal(new FixtureDataView(hybrid.HEAPU8.buffer).getUint8(Number(global(hybrid,'nomux_fg_cur'))),2);comparisons+=2;
 for(const [field,value,pattern]of [['nomux_cellSize',8,/record size/],['width_nomux_cell_ch',2,/field width/],['longSize',4,/ABI/]])assert.throws(()=>createTermcapEnvironment(base,{...L,[field]:value}),pattern);comparisons+=3;
 assert.throws(()=>callTermcap(base,L,'not_a_source_function'),/Unknown/);assert.throws(()=>a.view('nomux_cell',global(hybrid,'nomux_buf')).unknown,/Unknown/);assert.throws(()=>a.view('nomux_cell',global(hybrid,'nomux_buf')).unknown=1,/Unknown/);comparisons+=3;
}


// Cold Modules exercise per-instance cached environment decisions. The
// reference remains original C and each pair receives the same real entry.
for(const environment of [
 {NOMUX_MARKERS:'0',NETHACK_NO_DELAY:'0'},
 {NOMUX_MARKERS:'',NETHACK_NO_DELAY:'',WEBHACK_NO_DELAY:'1'},
 {NOMUX_MARKERS:undefined,NETHACK_NO_DELAY:undefined,WEBHACK_NO_DELAY:'0'},
 {NOMUX_MARKERS:'1',NETHACK_NO_DELAY:'1'},
 {TERM:undefined},
 {LINES:'10',COLUMNS:'40',NOMUX_MARKERS:'1',NETHACK_NO_DELAY:'1'},
 ]){
 const cold=[await factories[0](moduleOptions(environment)),await factories[1]({...moduleOptions(environment),nethackPorted:runtime})],saved=cold.map(m=>m._probe_stack());
 const compareCold=()=>{assert.deepEqual(state(cold[1]),state(cold[0]),'cold actual native stores');assert.equal(text(cold[1],cold[1]._probe_trace()),text(cold[0],cold[0]._probe_trace()));assert.deepEqual(cold[1].probeOutput,cold[0].probeOutput);assert.equal(cold[1]._probe_error(),cold[0]._probe_error());assert.equal(C,undefined);cold.forEach((m,i)=>assert.equal(m._probe_stack(),saved[i]));comparisons+=7;};
 const run=(name,args=[])=>{active='cold '+JSON.stringify(environment)+' '+name;cases++;for(const m of cold){m._probe_reset();if(name==='term_startup'&&environment.COLUMNS==='40'){const t=read(m,'instance_globals_t',global(m,'gt'),'tc_gbl_data');write(m,'tc_gbl_data',t,'tc_CO',0);write(m,'tc_gbl_data',t,'tc_LI',0);}}const results=cold.map(m=>m['_probe_call_'+name](...args.map(a=>BigInt(typeof a==='function'?a(m):a))));assert.deepEqual(results.map(String),[String(results[0]),String(results[0])]);comparisons++;compareCold();};
 run('nomux_end_attr');run('term_startup',[m=>pointer(m,1),m=>pointer(m,1,1)]);if(cold[0]._probe_error()){run('term_shutdown');continue;}run('nomux_markers_enabled');run('tty_delay_output');
 for(const m of cold){const bytes=Buffer.from('NOMUX_MARKERS\0','latin1');m.HEAPU8.set(bytes,Number(pointer(m,0)));const at=m.___wrap_getenv(pointer(m,0));if(at)m.HEAPU8[Number(at)]=environment.NOMUX_MARKERS==='1'?48:49;}
 run('nomux_markers_enabled');run('nomux_capture_write_input_boundary');
 for(const m of cold){m.HEAPU8.set(Buffer.from('\0','latin1'),Number(pointer(m,0)));}
 run('nomux_raw_emit',[m=>pointer(m,0),1]);for(const m of cold)new FixtureDataView(m.HEAPU8.buffer).setBigUint64(Number(global(m,'ttyDisplay')),0n,true);run('nomux_raw_emit',[m=>pointer(m,0),1]);run('nomux_get_cursor',[m=>pointer(m,1),m=>pointer(m,1,1)]);run('term_shutdown');
}
// Failed construction/initialization must remain retryable and unpublished.
// Capture a genuine library service object without running a policy body.
{
 active='late publication initialization refusal and retry';cases++;let real;
 const m=await factories[1]({...moduleOptions(),nethackPorted:{termcap(s){real=s;return 0;}}});m._probe_call_nomux_end_attr();assert.ok(real);const top=m._probe_stack();let builds=0,failed=false;
 const retryLayout=new Proxy({...L},{get(o,k){if(k==='pointerSize')builds++;return o[k];}}),boom=Error('actual transport initialization failure'),service=Object.assign(Object.create(real),{staticBuffer(i){if(i===2&&!failed){failed=true;throw boom;}return real.staticBuffer(i);}});
 assert.throws(()=>callTermcap(service,retryLayout,'nomux_end_attr'),e=>e===boom);assert.equal(m._probe_stack(),top);assert.equal(C,undefined);const failedBuildReads=builds;assert.ok(failedBuildReads>0);comparisons+=4;
 callTermcap(service,retryLayout,'nomux_end_attr');callTermcap(service,retryLayout,'nomux_end_attr');assert.equal(builds,2*failedBuildReads);assert.equal(m._probe_stack(),top);assert.equal(new FixtureDataView(m.HEAPU8.buffer).getUint8(Number(global(m,'nomux_fg_cur'))),7);assert.equal(C,undefined);comparisons+=4;
 const a=createTermcapEnvironment(real,L),other=createTermcapEnvironment(servicesByModule.get(hybrid),L);assert.notEqual(a.state,other.state);a.state.cursor_vis=123;assert.notEqual(other.state.cursor_vis,123);comparisons+=2;
}
}
if(unwrapped){for(const m of modules)m.___wrap_fflush(pointer(m,3));compare();}
if(jsDependencies){for(const m of modules){const d=m.nethackDependencies;for(const k of ['tgetent','tgetstr','tgetnum','tparm','tgoto','tputs'])assert.ok(d.calls[k]>0,k+' real JS dependency exercised');}}
console.log(`termcap: ${cases} cases, ${comparisons} EmC/JS state/trace/result/stack checks, ${invoked.size}/56 routines; native host and game pending`);
await writeFile(resolve(dir,jsDependencies?'js-dependencies-summary.json':unwrapped?'unwrapped-summary.json':'summary.json'),JSON.stringify({status:'pass',oracle:jsDependencies?'unchanged configured original C caller versus JS caller, both using unchanged production JS terminfo runtime; no compiled libtinfo':'unchanged configured original C and actual configured ncurses6.5 libtinfo; controlled foreign terminal transport',nativeHost:'pending',game:'pending',captureEncoder:'unchanged and outside this private fixture',cases,comparisons,functions:invoked.size,policyImports:schema.functions.length,calls:Object.fromEntries(calls),dependencyCalls:jsDependencies?modules.map(m=>m.nethackDependencies.calls):null,provider:unwrapped?'unchanged production provider':'private typed routing through same real C observation wrappers'},null,2)+'\n');
