/** Strict original-Lua source compiler allocation/cleanup differential.
 * Native source is pinned and production parsing/compiler operations generate
 * their own allocations. No expected allocation events are replayed. */
import assert from 'node:assert/strict';
import { createHash } from 'node:crypto';
import { readFileSync, writeFileSync, readdirSync, mkdirSync } from 'node:fs';
import { execFileSync } from 'node:child_process';
import { fileURLToPath } from 'node:url';
import { resolve } from 'node:path';
import { createLuaCState } from '../js/lua/lapi.js';
import { createLuaBytecodeVM } from '../js/lua/bytecode-vm.js';
import { compileLuaIncremental } from '../js/lua/incremental-parser.js';
const vmFactory=options=>{const vm=createLuaBytecodeVM(options);if(process.argv.includes('--incremental'))vm.compile=(source,name)=>{const {closure}=compileLuaIncremental(source,name,{observer:vm.heap.allocationObserver()});closure.upvalues[0].value=vm.globals;return closure;};return vm;};

const root = fileURLToPath(new URL('../', import.meta.url));
const scratch = resolve(root, '.cache/js-lua-debug/source-memory');
const lua = resolve(root, '.cache/js-dependency-lua/lua-5.4.8/src');
mkdirSync(scratch, { recursive: true });
assert.equal(createHash('sha256').update(readFileSync(resolve(root, '.cache/lua-5.4.8.tar.gz'))).digest('hex'), '4f18ddae154e793e46eeab727c59ef1c0c0c2b744e7b94219710d76f530629ae');
const oracle = resolve(scratch, 'oracle'), input = resolve(scratch, 'input.lua');
execFileSync(resolve(root, '.cache/wasm64-build/host-cc'), ['-O2', '-I' + lua, resolve(root, 'scripts/test-js-lua-source-memory.c'), ...readdirSync(lua).filter(n => n.endsWith('.c') && !['lua.c', 'luac.c'].includes(n)).sort().map(n => resolve(lua, n)), '-lm', '-o', oracle]);

function traceJS(source, fail = Infinity, limit = 0) {
  const events = [], blocks = new Map(); let id = 0, bytes = 0, attempts = 0, L;
  const allocator = (_ud, pointer, old, size) => {
    if (pointer !== null) assert.equal(blocks.get(pointer)?.size, old);
    if (size && (++attempts >= fail || L && limit && L.lua_gc(3) * 1024 + L.lua_gc(4) > limit)) {
      events.push({ event: 'refused', attempt: attempts, old, size, bytes }); return null;
    }
    bytes += size - (pointer === null ? 0 : old);
    const result = size ? pointer ?? { id: ++id } : null;
    events.push({ event: 'alloc', id: pointer?.id ?? result?.id ?? 0, old, size, bytes });
    blocks.delete(pointer); if (size) blocks.set(result, { size }); return result;
  };
  const mark = (phase, status) => events.push({ phase, status, bytes, attempts });
  try { L = createLuaCState({ vmFactory, memoryAllocator: allocator }); }
  catch (error) { assert.equal(error.status, 4); mark('state', 4); assert.equal(bytes, 0); assert.equal(blocks.size, 0); return events; }
  mark('state', 0);
  mark('load', L.luaL_loadbuffer(source, source.length, '@fixture.lua', 't'));
  L.lua_close(); mark('close', 0);
  assert.equal(bytes, 0); assert.equal(blocks.size, 0); return events;
}
const native = (source, option = null, quiet = false) => {
  writeFileSync(input, source);
  return execFileSync(oracle, [input, ...(option === null ? [] : [String(option)]), ...(quiet ? ['quiet'] : [])], { encoding: 'utf8' }).trim().split('\n').map(JSON.parse);
};
const phases = events => events.filter(e => e.phase);
function compare(name, source, option = null) {
  const expected = native(source, option), actual = traceJS(source, typeof option === 'number' ? option : Infinity, typeof option === 'string' ? Number(option.slice(6)) : 0);
  if (JSON.stringify(actual) !== JSON.stringify(expected)) writeFileSync(resolve(scratch, 'failure.json'), JSON.stringify({ name, option, native: expected, js: actual }, null, 2));
  assert.deepEqual(actual, expected, name + '/' + (option ?? 'success')); return expected;
}
const dat = resolve(root, 'nethack-c/upstream/dat');
let callbacks = 0, corpus = 0;
for (const name of readdirSync(dat).filter(n => n.endsWith('.lua')).sort()) {
  callbacks += compare(name, readFileSync(resolve(dat, name), 'latin1')).length; corpus++;
}
console.log(`PASS: ${corpus} original source scripts, complete native source-load/close allocator transcripts (${callbacks} callbacks).`);
const baseline = readFileSync(resolve(root, 'scripts/test-js-lua.mjs'), 'utf8');
const begin = baseline.indexOf('const core = [') + 13, end = baseline.indexOf('\n];', begin) + 2;
const language = Function('return ' + baseline.slice(begin, end))();
language.push(['backward-label', 'local x=0;::again::local y=x;x=x+1;if x<4 then goto again end;return x']);
for (const length of [28,29,30,31,60,61,62,63,124,125,126,127]) {
  language.push(['quoted-boundary-' + length, 'return "' + 'a'.repeat(length) + '"']);
  language.push(['hex-escape-boundary-' + length, 'return "' + 'a'.repeat(length) + '\\x41"']);
  language.push(['decimal-escape-boundary-' + length, 'return "' + 'a'.repeat(length) + '\\065"']);
  language.push(['unicode-escape-boundary-' + length, 'return "' + 'a'.repeat(length) + '\\u{1F600}"']);
}
language.push(['numeric-buffer', 'return ' + '0'.repeat(300) + '1']);
for (const equals of [0,14,15,30,31,62]) {
  const open = '[' + '='.repeat(equals) + '[', close = ']' + '='.repeat(equals) + ']';
  language.push(['long-delimiter-' + equals, 'return ' + open + 'a'.repeat(29) + close]);
  language.push(['long-comment-' + equals, '--' + open + '\nignored\n' + close + '\nreturn 1']);
}
for (const [name, source] of language) compare('language/' + name, source);
console.log(`PASS: ${language.length} additional language, lexer-buffer and control-flow source-load/close transcripts.`);
const directed = [
  ['empty', ''], ['local', 'local x=17;return x'], ['closure', 'local function f(x)return x+1 end;return f(2)'],
  ['table', 'local t={1,2};return t[1]'], ['branch', 'local x=1;if x<3 then local y=7;x=x+y else x=9 end;return x'],
  ['loop', 'local x=0;for i=1,3 do x=x+i end;return x'], ['while', 'local x=0;while x<3 do x=x+1 end;return x'],
  ['nested', 'local function f(x,...) local y=x+1;return function(z)return y+z end end'],
  ['long', 'local a="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";local b="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";return a,b'],
];
let refusals = 0, limits = 0;
for (const [name, source] of directed) {
  const events = compare(name, source), end = events.find(e => e.phase === 'load').attempts;
  for (let fail = 56; fail <= end + 1; fail++) { compare(name, source, fail); refusals++; }
  const thresholds = new Set([4986, 4987, 4988]);
  for (const e of events) if (e.size > 0) for (const offset of [-1, 0, 1]) thresholds.add(e.bytes + offset);
  for (const threshold of thresholds) {
    const expected = native(source, 'limit:' + threshold, true), actual = phases(traceJS(source, Infinity, threshold));
    assert.deepEqual(actual, expected, `${name}/COUNT:${threshold}`); limits++;
  }
}
console.log(`PASS: ${directed.length} directed sources, ${refusals} allocation refusal schedules and ${limits} native COUNT thresholds; exact callbacks, status, counts and cleanup.`);
