// Configured original-C versus JS caller policy, separate from game/capture encoding.
import assert from 'node:assert/strict';
import {readFile,writeFile,mkdir} from 'node:fs/promises';
import {writeFileSync} from 'node:fs';
import {resolve} from 'node:path';
import {pathToFileURL} from 'node:url';
import {spawnSync} from 'node:child_process';
import {C,withCEnvironment} from '../js/ported/c-runtime.js';
import * as core from '../js/ported/termcap.js';
import {callTermcap,createTermcapEnvironment} from '../js/ported/termcap-runtime.js';
import {checkTermcapSource} from '../nethack-c/wasm/tu-fragments/termcap-source-check.mjs';
const dir=resolve(process.env.TERMCAP_PROBE_DIR??'.cache/termcap-author');
const schema=JSON.parse(await readFile('nethack-c/wasm/tu-fragments/termcap-schema.json','utf8'));
const helpers='canonical reset clear_trace option override pointer trace error stack last_output_pointer layout_count layout_name layout_value callback_pointer invoke_callback constant'.split(' ');
if(process.argv.includes('--build')){
 await mkdir(dir,{recursive:true});checkTermcapSource();
 const defines=JSON.parse(await readFile('nethack-c/wasm/compile-defines.json','utf8'));
 const exported=helpers.map(n=>'_probe_'+n).concat(['global','read','write','address'].map(n=>'_teleport_termcap_'+n),schema.functions.map(f=>'_probe_call_'+f.name));
 const base=['-O2','-sMEMORY64=1','-sMODULARIZE=1','-sENVIRONMENT=node','-sALLOW_MEMORY_GROWTH=1','-sSTACK_SIZE=4194304','-sSUPPORT_LONGJMP=emscripten','--no-entry','-sEXPORTED_RUNTIME_METHODS=HEAPU8,FS,ENV','-sEXPORTED_FUNCTIONS='+JSON.stringify(exported),...defines.map(s=>'-D'+s),'-I'+resolve('.cache/wasm64-build/tree/include'),'-I'+resolve('.cache/ncurses-wasm64-build/include'),'-I'+resolve('scripts'),'-include',resolve('nethack-c/wasm/native-terminal.h'),'-fmacro-prefix-map='+resolve('scripts')+'/../.cache/wasm64-build/tree/win/tty/=../win/tty/',...'getenv putchar fflush free tgetent tgetnum tgetflag tgetstr tputs'.split(' ').map(n=>'-Wl,--wrap='+n),resolve('scripts/tu-termcap-probe.c'),resolve('.cache/ncurses-wasm64-build/lib/libtinfo.a')];
 for(const mode of ['reference','hybrid']){const args=[...base,...(mode==='hybrid'?['-DHYBRID_TERMCAP=1','--js-library',resolve('nethack-c/wasm/tu-libraries/termcap.js')]:[]),'-o',resolve(dir,'termcap-'+mode+'.mjs')];const p=spawnSync(resolve('.cache/emsdk/upstream/emscripten/emcc'),args,{encoding:'utf8',maxBuffer:32*1024*1024});await writeFile(resolve(dir,'build-'+mode+'-'+Date.now()+'.log'),JSON.stringify({args,status:p.status})+'\n'+p.stdout+p.stderr);if(p.status!==0)throw Error('TERMCAP '+mode+' compile failed; private raw build log preserved');}
}
const wasm=await readFile(resolve(dir,'termcap-hybrid.wasm'));
const imports=WebAssembly.Module.imports(new WebAssembly.Module(wasm)).filter(v=>v.kind==='function').map(v=>v.name);
for(const f of schema.functions)assert.ok(imports.includes(f.static?'teleport_termcap_test_'+f.name:f.name),'actual JS policy import '+f.name);
assert.ok(imports.includes('teleport_termcap_callback_tty_decgraphics_termcap_fixup'));
const factories=await Promise.all(['reference','hybrid'].map(async mode=>(await import(pathToFileURL(resolve(dir,'termcap-'+mode+'.mjs')).href)).default));
const entry=await readFile('nethack-c/wasm/terminfo/x/xterm-256color');
const text=(m,p)=>{let at=Number(p),end=at;assert.ok(at>=0&&at<m.HEAPU8.length);while(end<m.HEAPU8.length&&m.HEAPU8[end])end++;assert.ok(end<m.HEAPU8.length,'C NUL terminator');return Buffer.from(m.HEAPU8.subarray(at,end)).toString('latin1');};
const layout=m=>{const out={};for(let i=0;i<m._probe_layout_count();i++)out[text(m,m._probe_layout_name(i))]=m._probe_layout_value(i);return out;};
const moduleOptions=(environment={})=>({noInitialRun:true,print:()=>{},printErr:()=>{},preRun:[m=>{Object.assign(m.ENV,{TERM:'xterm-256color',TERMINFO:'/nethack/terminfo',NETHACK_NO_DELAY:'1',NOMUX_MARKERS:'1',LINES:'24',COLUMNS:'80',HOME:'/home/player',LANG:'C',LC_ALL:'C',...environment});m.FS.mkdirTree('/nethack/terminfo/x');m.FS.writeFile('/nethack/terminfo/x/xterm-256color',entry);}]});
const reference=await factories[0](moduleOptions()),L=layout(reference),servicesByModule=new WeakMap(),calls=new Map();
const runtime={termcap(services,name,...args){servicesByModule.set(services.moduleKey,services);calls.set(name,(calls.get(name)??0)+1);return callTermcap(services,L,name,...args);}};
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
function state(m){const out=[],dv=new DataView(m.HEAPU8.buffer);
 const scalar=(d,v,path,ctype)=>{if(d.p!==undefined){const canonical=m._probe_canonical(v);out.push([path,canonical===0xffffffffffffffffn?'foreign:'+((ctype??'').includes('char')||charPointers.has(path)?text(m,v):'opaque'):canonical.toString()]);if((ctype??'').includes('char')||charPointers.has(path))out.push([path+'.text',v?text(m,v):null]);}else if(d.f)out.push([path,v===0n?0:v===m._probe_callback_pointer(0)?'xputc':v===m._probe_callback_pointer(1)?'decgraphics':v===m._probe_callback_pointer(2)?'utf8graphics':'unknown']);else out.push([path,v.toString()]);};
 const value=(d,at,path,ctype='')=>{if(d.s){for(const f of schema.schema[d.s].fields){const v=read(m,d.s,at,f.name);if(f.d.s||f.d.a)value(f.d,v,path+'.'+f.name,f.ctype);else scalar(f.d,v,path+'.'+f.name,f.ctype);}return;}if(d.a){const child=d.a.length===1?d.e:{a:d.a.slice(1),e:d.e};for(let i=0;i<d.a[0];i++)value(child,at+BigInt(i*width(child)),path+'['+i+']',ctype);return;}const bytes=width(d);let v=0n;for(let i=0;i<bytes;i++)v|=BigInt(dv.getUint8(Number(at)+i))<<BigInt(8*i);scalar(d,v,path,ctype);};
 for(const g of globals)value(g.d,global(m,g.name),g.name,charPointers.has(g.name)||g.name==='hilites'?'char *':'');
 value({s:'DisplayDesc'},pointer(m,2),'display');for(let i=0;i<8;i++)out.push(['int'+i,dv.getInt32(Number(pointer(m,1,i)),true)]);return out;
}
function evidence(extra={}){writeFileSync(resolve(dir,'failure-'+Date.now()+'.json'),JSON.stringify({active,...extra,reference:{trace:text(reference,reference._probe_trace()),error:reference._probe_error(),state:state(reference)},hybrid:{trace:text(hybrid,hybrid._probe_trace()),error:hybrid._probe_error(),state:state(hybrid)}},(_,v)=>typeof v==='bigint'?v.toString():v,2)+'\n');}
const stacks=modules.map(m=>m._probe_stack());
function compare(){const actual=state(hybrid),expected=state(reference);const first=actual.findIndex((v,i)=>JSON.stringify(v)!==JSON.stringify(expected[i]));assert.equal(first,-1,'TERMCAP state '+active+' mismatch '+JSON.stringify([actual[first],expected[first]]));assert.equal(text(hybrid,hybrid._probe_trace()),text(reference,reference._probe_trace()),'TERMCAP trace '+active);assert.equal(hybrid._probe_error(),reference._probe_error());comparisons+=3;for(let i=0;i<2;i++){assert.equal(modules[i]._probe_stack(),stacks[i]);comparisons++;}assert.equal(C,undefined);comparisons++;}
function reset(label){active=label;cases++;both('reset');}
function input(value,index=0){for(const m of modules){const bytes=Buffer.from(value+'\0','latin1');assert.ok(bytes.length<=8192);m.HEAPU8.set(bytes,Number(pointer(m,0,index)));}}
function action(name,...args){if(process.env.TERMCAP_VERBOSE)console.log(active,name);invoked.add(name);const f=schema.functions.find(f=>f.name===name),ret=f.type.qualType.split('(')[0].trim();const actual=modules.map(m=>m['_probe_call_'+name](...args.map(a=>BigInt(typeof a==='function'?a(m):a))));const normalized=actual.map((v,i)=>ret.includes('*')?v?text(modules[i],v):null:BigInt.asIntN(64,v).toString());try{assert.deepEqual(normalized[1],normalized[0],name+' return');compare();}catch(error){evidence({name,actual,normalized});throw error;}return actual;}
// Source initialization happens through a real original entry, not a test-only
// write into C const data or a surrogate reference static-buffer helper.
reset('first real entry initializes JS source storage');action('nomux_end_attr');
reset('pinned terminal startup');action('term_startup',m=>pointer(m,1),m=>pointer(m,1,1));
const argMap={term_startup:[m=>pointer(m,1),m=>pointer(m,1,1)],tty_number_pad:[1],nocmov:[3,2],cmov:[4,5],xputc:[65],nomux_emit_marker:[m=>pointer(m,0)],nomux_clear_to_eol:[0,0],nomux_putch:[65],nomux_set_attr:[Number(L.ATR_BOLD)],nomux_set_fg:[Number(L.CLR_RED)],nomux_sgr_fg:[9],nomux_raw_putch:[65],nomux_raw_emit:[m=>pointer(m,0),1],nomux_get_cursor:[m=>pointer(m,1),m=>pointer(m,1,1)],xputs:[m=>pointer(m,0)],s_atr2str:[Number(L.ATR_BOLD)],e_atr2str:[Number(L.ATR_BOLD)],term_attr_fixup:[63],term_start_attr:[Number(L.ATR_BOLD)],term_end_attr:[Number(L.ATR_BOLD)],term_start_color:[Number(L.CLR_RED)],term_start_bgcolor:[5],term_curs_set:[0],emit24bit:[0x123456],emit256:[123],term_start_extracolor:[0x123456,123]};
const filter=process.env.TERMCAP_FILTER?new RegExp(process.env.TERMCAP_FILTER):null;
for(const f of schema.functions){if(filter&&!filter.test(f.name)||f.name==='term_startup'||f.name==='term_shutdown'||f.name==='kill_hilite')continue;reset('initial '+f.name);input(f.name==='nomux_emit_marker'?'input':'sample');assert.ok(!f.parameters.length||Object.hasOwn(argMap,f.name),'explicit valid '+f.name);action(f.name,...(argMap[f.name]??[]));}
reset('shutdown original allocation lifecycle');action('term_shutdown');
reset('already shut down highlight cleanup');action('kill_hilite');
console.log(`termcap: ${cases} cases, ${comparisons} EmC/JS state/trace/result/stack checks, ${invoked.size}/56 routines; native host and game pending`);
await writeFile(resolve(dir,'summary.json'),JSON.stringify({status:'pass',oracle:'unchanged configured original C and actual configured ncurses6.5 libtinfo; controlled foreign terminal transport',nativeHost:'pending',game:'pending',captureEncoder:'unchanged and outside this private fixture',cases,comparisons,functions:invoked.size,policyImports:schema.functions.length,calls:Object.fromEntries(calls)},null,2)+'\n');
