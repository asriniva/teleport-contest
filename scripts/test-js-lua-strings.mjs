// Independent native Lua5.4.8 comparisons for binary packing and formatting.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import { fileURLToPath, pathToFileURL } from 'node:url';
import { spawnSync } from 'node:child_process';
import { createLua } from '../js/services/lua/lua.js';
import { isLuaString, luaStringBytes } from '../js/services/lua/lobject.js';
const root = fileURLToPath(new URL('../', import.meta.url));
if (Number(process.versions.node.split('.')[0]) < 24) {
  const result = spawnSync(path.join(root, '.cache/emsdk/node/24.19.0_64bit/bin/node'), [fileURLToPath(import.meta.url)], { stdio: 'inherit' });
  process.exit(result.status ?? 1);
}
const work = path.join(root, '.cache/js-lua-strings'); fs.mkdirSync(work, { recursive: true });
function command(program, args, options = {}) {
  const result = spawnSync(program, args, { encoding: 'utf8', timeout: 60000, maxBuffer: 8 * 1024 * 1024, ...options });
  assert.equal(result.status, 0, `${program}: ${result.error || result.stderr || result.stdout}`);
  return result.stdout.trimEnd();
}
command('python3', ['-c', `import hashlib,tarfile,pathlib
p=pathlib.Path(${JSON.stringify(root)}); a=p/'.cache/lua-5.4.8.tar.gz'
assert hashlib.sha256(a.read_bytes()).hexdigest()=='4f18ddae154e793e46eeab727c59ef1c0c0c2b744e7b94219710d76f530629ae'
with tarfile.open(a) as t:t.extractall(p/'.cache/js-lua-strings',filter='data')`]);
const nativeSource = path.join(work, 'oracle.c');
fs.writeFileSync(nativeSource, `#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
static int evaluate(const char*input,int isfile) {
 lua_State*L=luaL_newstate();luaL_openlibs(L);
 if((isfile?luaL_loadfile(L,input):luaL_loadstring(L,input))||lua_pcall(L,0,LUA_MULTRET,0)) {fprintf(stderr,"%s",lua_tostring(L,-1));lua_close(L);return 2;}
 for(int i=1;i<=lua_gettop(L);i++)switch(lua_type(L,i)){
 case LUA_TNIL:puts("nil");break;
 case LUA_TBOOLEAN:printf("boolean:%d\\n",lua_toboolean(L,i));break;
 case LUA_TNUMBER:if(lua_isinteger(L,i))printf("integer:%lld\\n",(long long)lua_tointeger(L,i));
 else{double n=lua_tonumber(L,i);uint64_t b;memcpy(&b,&n,8);printf("float:%016llx\\n",(unsigned long long)b);}break;
 case LUA_TSTRING:{size_t z;const unsigned char*s=(const unsigned char*)lua_tolstring(L,i,&z);printf("string:");for(size_t k=0;k<z;k++)printf("%02x",s[k]);puts("");break;}
 default:printf("type:%s\\n",lua_typename(L,lua_type(L,i)));break;}
 lua_close(L);return 0;
}
int oracle_source(const char*input){return evaluate(input,0);}
int main(int argc,char**argv){return argc==2?evaluate(argv[1],1):3;}`);
const source = path.join(work, 'lua-5.4.8/src'), oracle = path.join(work, 'oracle');
command(path.join(root, '.cache/wasm64-build/host-cc'), ['-O2', '-I' + source, nativeSource,
  ...fs.readdirSync(source).filter(name => name.endsWith('.c') && name !== 'lua.c' && name !== 'luac.c').map(name => path.join(source, name)), '-lm', '-o', oracle]);
const wasmPath = path.join(work, 'oracle.mjs');
command(path.join(root, '.cache/emsdk/upstream/emscripten/emcc'), ['-O2', '-sMEMORY64=1', '-I' + source, nativeSource,
  ...fs.readdirSync(source).filter(name => name.endsWith('.c') && name !== 'lua.c' && name !== 'luac.c').map(name => path.join(source, name)),
  '-lm', '-sMODULARIZE=1', '-sEXPORT_ES6=1', '-sENVIRONMENT=node', '-sALLOW_MEMORY_GROWTH=1',
  '-sINVOKE_RUN=0', '-sEXPORTED_FUNCTIONS=_oracle_source,_malloc,_free', '-sEXPORTED_RUNTIME_METHODS=HEAPU8', '-o', wasmPath]);
const lines = [], wasmFactory = (await import(pathToFileURL(wasmPath))).default;
const configured = await wasmFactory({ print: line => lines.push(line), printErr: line => { throw new Error(line); } });
function encoded(value) {
  if (value === null) return 'nil';
  if (typeof value === 'boolean') return 'boolean:' + Number(value);
  if (typeof value === 'bigint') return 'integer:' + value;
  if (isLuaString(value)) return 'string:' + Buffer.from(luaStringBytes(value), 'latin1').toString('hex');
  if (typeof value === 'number') { const bytes = new ArrayBuffer(8), view = new DataView(bytes); view.setFloat64(0, value); return 'float:' + view.getBigUint64(0).toString(16).padStart(16, '0'); }
  throw new Error('Unhandled result ' + typeof value);
}
let cases = 0, values = 0;
const platformDifferences = [];
function compare(source) {
  const input = path.join(work, 'input.lua'); fs.writeFileSync(input, source);
  const native = command(oracle, [input]);
  const bytes = Buffer.from(source + '\0'), pointer = configured._malloc(BigInt(bytes.length));
  configured.HEAPU8.set(bytes, Number(pointer)); lines.length = 0;
  try { assert.equal(configured._oracle_source(BigInt(pointer)), 0, source); }
  finally { configured._free(pointer); }
  const expected = lines.join('\n');
  if (native !== expected) {
    assert.ok(source.includes('string.format'), 'Unexpected native/configured difference: ' + source);
    platformDifferences.push({ source, native, configured: expected });
  }
  const vm = createLua({ baseError: true, baseMeta: true });
  const result = vm.execute(source, '@strings.lua');
  assert.equal(result.map(encoded).join('\n'), expected, source);
  cases++; values += result.length;
}
const literal = text => '"' + Array.from(text, c => '\\x' + c.charCodeAt(0).toString(16).padStart(2, '0')).join('') + '"';
const integer = n => n === -9223372036854775808n ? '(-9223372036854775807-1)' : String(n);
for (const order of ['<', '>', '=']) {
  for (let width = 1; width <= 16; width++) {
    for (const signed of [true, false]) {
      const format = order + (signed ? 'i' : 'I') + width;
      const limit = width >= 8 ? 9223372036854775807n : (1n << BigInt(width * 8 - Number(signed))) - 1n;
      const inputs = [0n, 1n, limit, ...(signed || width >= 8 ? [-1n, width >= 8 ? -9223372036854775808n : -(limit + 1n)] : [])];
      for (const value of inputs) compare(`local s=string.pack(${literal(format)},${integer(value)});return s,string.packsize(${literal(format)}),string.unpack(${literal(format)},s)`);
    }
  }
  for (const code of ['b','B','h','H','l','L','j','J','T','i','I'])
    compare(`local s=string.pack(${literal(order + code)},17);return s,string.unpack(${literal(order + code)},s),string.packsize(${literal(order + code)})`);
  for (const code of ['f', 'n', 'd']) for (const value of ['0.0', '-0.0', '1.5', '-2.25', '1e-300', '1e300', 'math.huge', '-math.huge'])
    compare(`local s=string.pack(${literal(order + code)},${value});return s,string.unpack(${literal(order + code)},s)`);
}
for (const format of ['!8bhlj', '!4bi4d', '<!8bXdI4', '>!16bXi16', '!1bi3I5', 'xc0xc7', 'c0', ' !8c3i2c3d', 'Xb', '!8bXj']) {
  compare(`return string.packsize(${literal(format)})`);
}
for (const format of ['<s1z', '>s2c8', 's16', '!8bzs2I4']) {
  const args = format.endsWith('I4') ? '7,"abc","a\\0b",17' : format.endsWith('z') ? '"a\\0b","xyz"' : format.endsWith('c8') ? '"xyz","a\\0b"' : '"a\\0b"';
  compare(`local s=string.pack(${literal(format)},${args});return s,string.unpack(${literal(format)},s)`);
}
for (const initial of [1, 2, 0, -1, -2, -1000, 4])
  compare(`local ok,a,b=pcall(string.unpack,"B","abc",${initial});return ok,ok and a or type(a),b`);
for (const format of ['i0','i17','!0','!17','c','q','X','Xc3','Xz','!8i3','!3i3','z','s1'])
  compare(`local ok,e=pcall(string.packsize,${literal(format)});return ok,ok and e or type(e)`);
for (const expression of [
  'string.pack("b",128)', 'string.pack("B",-1)', 'string.pack("I1",256)',
  'string.pack("i2",-32769)', 'string.pack("c2","abc")', 'string.pack("z","a\\0b")',
  'string.pack("s1",string.rep("x",256))', 'string.unpack("i4","a")',
  'string.unpack("z","abc")', 'string.unpack("s1","\\255abc")',
  'string.unpack("I9",string.rep("\\255",9))',
  'string.unpack("i9",string.rep("\\255",8).."\\0")',
]) compare(`local ok,e=pcall(function()return ${expression} end);return ok,type(e)`);
for (const code of ['d','i','u','o','x','X']) for (const format of ['%' + code, '%08' + code, '%-12.5' + code, '%.0' + code])
  for (const value of [0n, 1n, -1n, 127n, -9223372036854775808n, 9223372036854775807n])
    compare(`return string.format(${literal(format)},${integer(value)})`);
for (const format of ['%+d','% d','%#o','%#x','%#X','%#.0o','%#08x','%0008d','%-+08d'])
  for (const value of [0n, 1n, -17n]) compare(`return string.format(${literal(format)},${integer(value)})`);
for (const code of ['f','e','E','g','G','a','A']) {
  for (const value of ['0.0','-0.0','1.5','2.5','-3.5','0.125','1.2345678901234567','1e20','1e-20','1e300','1e-300','math.huge','-math.huge'])
    for (const prefix of ['%','%+.0','%#12.4','%020.6','%-12.8'])
      compare(`return string.format(${literal(prefix + code)},${value})`);
}
for (const value of ['"a\\0\\19\\255\\n\\r\\\"\\\\"','nil','true','false','17','(-9223372036854775807-1)','1.5','-0.0','math.huge','-math.huge','0/0'])
  compare(`return string.format("%q",${value})`);
for (const expression of ['string.format("%.s","abc")','string.format("%.0s","abc")',
  'string.format("%-5s",17)','string.format("%s","a\\0b")','string.format("%s",nil)',
  'string.format("%s",setmetatable({},{__tostring=function()return "custom" end}))',
  'string.format("%p %p %p",nil,17,true)','string.format("a\\0b%%c")']) compare('return ' + expression);
for (const format of ['%+u','%#d','%.1c','%0s','%1q','%100d','%.100f','%--#s','%n','%F','%','%..f'])
  compare(`local ok,e=pcall(string.format,${literal(format)},17);return ok,ok and e or type(e)`);
let seed = 0x1a2b3c4d;
const random = () => { seed ^= seed << 13; seed ^= seed >>> 17; seed ^= seed << 5; return seed >>> 0; };
const floating = bits => {
  const buffer = Buffer.alloc(8); buffer.writeBigUInt64LE(bits);
  return `string.unpack("<d",${literal(buffer.toString('latin1'))})`;
};
for (const bits of [1n, 0x8000000000000001n, 0xfffffffffffffn, 0x10000000000000n,
  0x7fefffffffffffffn, 0xffefffffffffffffn, 0x7ff8000000000000n, 0xfff8000000000000n,
  0x7ff0000000000001n])
  for (const code of ['a','A','f','e','g','q'])
    compare(`return string.format("%${code}",(${floating(bits)}))`);
for (let i = 0; i < 250; i++) {
  let bits = BigInt(random()) << 32n | BigInt(random());
  if ((bits >> 52n & 2047n) === 2047n) bits ^= 1n << 52n;
  const precision = [0,1,2,6,11,12,13,14,17,50,99][random() % 11];
  const code = ['a','A','e','E','f','g','G'][random() % 7];
  const flags = ['', '+', '#', ' ', '-'][random() % 5];
  compare(`return string.format(${literal('%' + flags + '20.' + precision + code)},(${floating(bits)}))`);
}
compare('local t=coroutine.create(function()end);local a=string.format("%p",t);return a~="(null)",a==string.format("%p",t),string.format("%p",coroutine.running())~="(null)"');
fs.writeFileSync(path.join(work, 'platform-differences.json'), JSON.stringify(platformDifferences, null, 2) + '\n');
console.log(`PASS: ${cases} configured Lua string cases / ${values} byte- and bit-identical values, each also executed natively; ${platformDifferences.length} measured host-format differences. Packing widths1–16, endianness, alignment, floats, strings, boundaries and rejected inputs.`);
