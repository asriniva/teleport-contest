import assert from 'node:assert/strict';
import fs from 'node:fs';
import {pathToFileURL} from 'node:url';
import {createStandaloneEnvironment} from '../js/nethack/environment.js';
const env=createStandaloneEnvironment({initialBytes:1024,maximumBytes:64*1024*1024});
const {memory,filesystem,services}=env,io=env.enableStdio({stdin:Uint8Array.of(65,0,66)});
const p=memory.calloc(1,128),f=io.fopen('/binary','w+');assert.ok(f);
memory.HEAPU8.set([0,255,65,10,66],p);assert.equal(io.fwrite(p,1,5,f),5);assert.equal(io.ftell(f),5n);
assert.equal(io.fseek(f,0,0),0);assert.equal(io.fgetc(f),0);assert.equal(io.ungetc(17,f),17);assert.equal(io.ftell(f),0n);assert.equal(io.fgetc(f),17);
assert.equal(io.fread(p+16,1,10,f),4);assert.equal(io.feof(f),1);assert.deepEqual([...memory.readBytes(p+16,4)],[255,65,10,66]);
io.rewind(f);assert.equal(io.feof(f),0);assert.equal(io.fgets(p+32,128-32,f),p+32);assert.deepEqual([...memory.readBytes(p+32,4)],[0,255,65,10]);
assert.equal(io.fclose(f),0);assert.equal(io.fclose(f),-1);assert.equal(env.libc.errno,8);
assert.equal(io.fopen('/absent','r'),0);assert.equal(env.libc.errno,44);
assert.equal(io.fgetc(io.stdin),65);assert.equal(io.fgetc(io.stdin),0);assert.equal(io.fgetc(io.stdin),66);assert.equal(io.fgetc(io.stdin),-1);
assert.equal(io.fprintf(io.stdout,'%s %d','hello',17),8);assert.equal(io.captured(1).length,0);assert.equal(io.fflush(io.stdout),0);assert.equal(Buffer.from(io.captured(1)).toString(),'hello 17');
const lua=env.enableLua(),a=lua.api,L=a.luaL_newstate();assert.ok(L);
function execute(source,results=1) {
    assert.equal(a.luaL_loadstring(L,source),0);
    assert.equal(a.lua_pcallk(L,0,results,0,0n,0n),0);
}
execute('return 6*7');assert.equal(a.lua_tointegerx(L,-1,0),42n);a.lua_settop(L,0);
const fn=env.functions.functionPointer(state=>{const n=a.luaL_checkinteger(state,1);a.lua_pushinteger(state,n+1n);return 1;},'ip');
a.lua_pushcclosure(L,fn,0);a.lua_setglobal(L,'increment');
execute('return increment(41)');assert.equal(a.lua_tointegerx(L,-1,0),42n);a.lua_settop(L,0);
let continued=false;
const error=env.functions.functionPointer(state=>{a.lua_pushstring(state,'deliberate');a.lua_error(state);continued=true;return 0;},'ip');
a.lua_pushcclosure(L,error,0);a.lua_setglobal(L,'fail');
assert.equal(a.luaL_loadstring(L,'return fail()'),0);assert.equal(a.lua_pcallk(L,0,1,0,0n,0n),2);assert.equal(continued,false);
assert.match(memory.readString(a.lua_tolstring(L,-1,0)),/deliberate/);a.lua_settop(L,0);
a.luaopen_os(L);a.lua_setglobal(L,'os');execute('return os.date("!%Y-%m-%d",0)');assert.equal(memory.readString(a.lua_tolstring(L,-1,0)),'1970-01-01');a.lua_settop(L,0);
filesystem.writeFile('/rename-me',Uint8Array.of(1,2,3));execute('return os.rename("/rename-me","/renamed")');assert.equal(a.lua_toboolean(L,-1),1);assert.deepEqual([...filesystem.readFile('/renamed')],[1,2,3]);a.lua_settop(L,0);
const user=a.lua_newuserdatauv(L,24,2);memory.view.setBigInt64(user,123n,true);memory.malloc(4*1024*1024);assert.equal(memory.view.getBigInt64(user,true),123n);
a.lua_close(L);
assert.equal(services.heap().buffer,memory.buffer);
if(process.env.STANDALONE_REFERENCE_ROOT) {
    const root=process.env.STANDALONE_REFERENCE_ROOT,L=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')).rnd;
    const {default:factory}=await import(pathToFileURL(root+'/.cache/tu-probes/rnd-reference.mjs')),ref=await factory();
    const state=env.enableRnd(L,{seed:12345n,displaySeed:54321n,luck:()=>0,level:()=>1});
    ref._probe_init(12345n,0);ref._probe_init(54321n,1);ref._probe_hero(0,0,1);
    const names={rn2:'rn2',display:'rn2_on_display_rng',rnd:'rnd',rnd_display:'rnd_on_display_rng',rnl:'rnl',rne:'rne',rnz:'rnz'};
    for(let i=0;i<200;i++)for(const [probe,name]of Object.entries(names))assert.equal(env.call('rnd',name,1+i%97),ref['_probe_'+probe](1+i%97));
    for(let i=0;i<100;i++)assert.equal(env.call('rnd','d',i%9,6),ref._probe_dice(i%9,6));
    env.setEnvironment('NETHACK_RNGLOG','/rng.log');env.setEnvironment('NETHACK_RNGLOG_DISP','1');env.call('rnd','rng_log_init');
    env.call('rnd','rn2',17);env.call('rnd','rn2_on_display_rng',19);assert.match(Buffer.from(filesystem.readFile('/rng.log')).toString(),/~drn2\(19\)/);
    io.fclose(state.state.rng_logfile);
}
console.log('PASS: binary stdio/EOF/seek/pushback/errors, standalone Lua bytecode, C API callbacks/error unwinding, OS/date/files, userdata growth and configured RNG comparisons.');
