import assert from 'node:assert/strict';
import fs from 'node:fs';
import {pathToFileURL} from 'node:url';
import {createStandaloneEnvironment} from '../js/standalone/environment.js';
import {encodeRecorderScreen} from '../js/wasm-replay-support.js';
const root=process.env.STANDALONE_REFERENCE_ROOT;if(!root)throw new Error('Missing STANDALONE_REFERENCE_ROOT');
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),L=layouts.termcap;
const env=createStandaloneEnvironment({environment:{NOMUX_MARKERS:'1',TERM:'xterm-256color',LINES:'24',COLUMNS:'80'}});
env.enableStdio();env.enableDecl(layouts.decl);env.enableHacklib(layouts.hacklib);env.enableDependencies();
const terminal=env.enableTerminal(L),{memory,services}=env;
const entry=fs.readFileSync('nethack-c/wasm/terminfo/x/xterm-256color');
const {default:factory}=await import(pathToFileURL(root+'/.cache/termcap-author/termcap-reference.mjs'));
const ref=await factory({noInitialRun:true,print:()=>{},printErr:()=>{},preRun:[m=>{
    Object.assign(m.ENV,{NOMUX_MARKERS:'1',TERM:'xterm-256color',TERMINFO:'/nethack/terminfo',LINES:'24',COLUMNS:'80'});
    m.FS.mkdirTree('/nethack/terminfo/x');m.FS.writeFile('/nethack/terminfo/x/xterm-256color',entry);
}]});
const source=JSON.parse(fs.readFileSync('js/standalone/terminal-metadata.json'));
const global=name=>BigInt(ref._teleport_termcap_global(source.globals.findIndex(g=>g.name===name)));
const ctext=p=>{p=Number(p);let end=p;while(ref.HEAPU8[end])end++;return Buffer.from(ref.HEAPU8.slice(p,end)).toString('latin1');};
const display=env.allocateGlobal('fixture.display',L.DisplayDescSize);
memory.view.setBigUint64(terminal.global('ttyDisplay'),BigInt(display),true);
ref._probe_reset();const nativeDisplay=ref._probe_pointer(2,0);
function cursor(x,y){for(const [name,value]of [['curx',x],['cury',y]]){env.ctypes.setField('struct DisplayDesc',display,name,'short',value);const kind=Object.keys(source.schemas).indexOf('DisplayDesc'),field=source.schemas.DisplayDesc.fields.findIndex(f=>f.name===name);ref._teleport_termcap_write(kind,nativeDisplay,field,BigInt.asUintN(64,BigInt(value)));}}
function call(name,...args){env.call('termcap',name,...args);return ref['_probe_call_'+name](...args.map(BigInt));}
call('nomux_clear_screen');let checks=0;
for(let i=0;i<400;i++) {
    const x=i*17%80,y=i*7%24;cursor(x,y);
    call('nomux_set_fg',i%16);call('nomux_set_attr',i%8);call('nomux_putch',32+i%224);
    if(i%9===0)call('nomux_end_attr');
    const own=memory.readBytes(terminal.global('nomux_buf'),24*80*L.nomux_cellSize),at=Number(global('nomux_buf'));
    assert.deepEqual(own,ref.HEAPU8.slice(at,at+own.length));checks++;
}
// The inherited recorder has a fixed 6144-byte output buffer. A stress grid
// with an attribute/color transition at every scattered cell exceeds that C
// buffer. Retain all cell checks, then capture a bounded defined-input grid.
call('nomux_clear_screen');
for(let i=0;i<40;i++){cursor(i,3);call('nomux_set_fg',i%16);call('nomux_set_attr',i%8);call('nomux_putch',65+i%26);}
const actual=env.call('termcap','nomux_capture_screen'),expected=ref._probe_call_nomux_capture_screen();
assert.equal(memory.readString(actual),ctext(expected));
call('nomux_capture_write_input_boundary');
const trace=ctext(ref._probe_trace()),capture=[...trace.matchAll(/capture:(-?\d+):(-?\d+):([01]):([0-9a-f]*);/g)].at(-1);
assert.ok(capture);assert.deepEqual(terminal.frames.at(-1),{screen:encodeRecorderScreen(Buffer.from(capture[4],'hex').toString('latin1')),cursor:[Number(capture[1]),Number(capture[2]),1],animation:Boolean(Number(capture[3]))});
const name=memory.cstring('xterm-256color'),nativeName=ref._probe_pointer(0,0);ref.HEAPU8.set(Buffer.from('xterm-256color\0'),Number(nativeName));
assert.equal(services.tgetent(0,name),ref.___wrap_tgetent(0n,nativeName));
for(const cap of ['co','li','Co','pa','am','bs','cm','cl','ce','so','se','AF','AB','vi','ve']) {
    const p=memory.cstring(cap);ref.HEAPU8.set(Buffer.from(cap+'\0'),Number(nativeName));
    assert.equal(services.tgetnum(p),ref.___wrap_tgetnum(nativeName));assert.equal(services.tgetflag(p),ref.___wrap_tgetflag(nativeName));
    const own=services.tgetstr(p,0),expected=ref.___wrap_tgetstr(nativeName,0n);assert.equal(own?memory.readString(own):null,expected?ctext(expected):null);checks+=3;
}
console.log(`PASS: ${checks} original-C recorder-cell/capture and pinned terminfo comparisons on standalone JS memory; game window/input bindings remain separate.`);
