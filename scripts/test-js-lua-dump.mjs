/** Original Lua5.4.8 dump writer block sequence and failure differential. */
import assert from 'node:assert/strict';
import { readFileSync, writeFileSync, readdirSync, mkdirSync } from 'node:fs';
import { execFileSync } from 'node:child_process';
import { fileURLToPath } from 'node:url';
import { resolve } from 'node:path';
import { compileLuaSource } from '../js/services/lua-source-compiler.js';
import { dumpLuaChunk } from '../js/services/lua-codegen.js';
const root = fileURLToPath(new URL('../', import.meta.url)), scratch = resolve(root, '.cache/js-lua-debug/dump');
const lua = resolve(root, '.cache/js-dependency-lua/lua-5.4.8/src'); mkdirSync(scratch, { recursive: true });
const source = resolve(scratch, 'oracle.c'), oracle = resolve(scratch, 'oracle'), input = resolve(scratch, 'input.lua');
writeFileSync(source, String.raw`
#include <stdio.h>
#include <stdlib.h>
#include "lua.h"
#include "lauxlib.h"
typedef struct {int calls,fail;} Writer;
static int writer(lua_State*L,const void*data,size_t n,void*ud){Writer*w=ud;w->calls++;printf("B:");for(size_t i=0;i<n;i++)printf("%02x",((const unsigned char*)data)[i]);puts("");return w->fail&&w->calls==w->fail?7:0;}
int main(int argc,char**argv){lua_State*L=luaL_newstate();if(luaL_loadfile(L,argv[1]))return 2;Writer w={0,argc>3?atoi(argv[3]):0};int status=lua_dump(L,writer,&w,argc>2?atoi(argv[2]):0);printf("S:%d\n",status);lua_close(L);return 0;}
`);
execFileSync(resolve(root, '.cache/wasm64-build/host-cc'), ['-O2', '-I' + lua, source, ...readdirSync(lua).filter(n => n.endsWith('.c') && !['lua.c', 'luac.c'].includes(n)).map(n => resolve(lua, n)), '-lm', '-o', oracle]);
const native = (text, strip, fail = 0) => { writeFileSync(input, text); return execFileSync(oracle, [input, String(+strip), String(fail)], { encoding: 'utf8' }).trim().split('\n'); };
function compare(text, name, strip, fail = 0) {
  const chunks = [], prototype = compileLuaSource(text, '@' + input);
  const result = dumpLuaChunk(prototype, { strip, onWrite: bytes => { chunks.push('B:' + Buffer.from(bytes).toString('hex')); return fail && chunks.length === fail ? 7 : 0; } });
  chunks.push('S:' + result.writerStatus); assert.deepEqual(chunks, native(text, strip, fail), name + '/' + strip + '/' + fail); return chunks.length - 1;
}
let cases = 0, writes = 0;
const dat = resolve(root, 'nethack-c/upstream/dat');
for (const name of readdirSync(dat).filter(n => n.endsWith('.lua'))) for (const strip of [false, true]) { writes += compare(readFileSync(resolve(dat, name), 'latin1'), name, strip); cases++; }
const directed = 'local function f(a,...)local t={a,...};return t end;return f(17,"long writer payload")';
const count = compare(directed, 'failure-baseline', false);
for (let fail = 1; fail <= count + 1; fail++) compare(directed, 'writer-refusal', false, fail);
console.log(`PASS: ${cases} native dump writer transcripts / ${writes} block writes, ${count + 1} writer refusal positions; unchanged binary bytes and native stop/status behavior.`);
