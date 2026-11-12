// Native oracle compiles the pinned musl regex sources, never host regcomp.
// Only test code depends on Node/fs/subprocesses; the production service does not.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import { fileURLToPath } from 'node:url';
import { pathToFileURL } from 'node:url';
import { spawnSync } from 'node:child_process';
import { createHash } from 'node:crypto';
import vm from 'node:vm';
import * as regex from '../js/libraries/regex/posix.js';

const root = fileURLToPath(new URL('../', import.meta.url));
const work = path.join(root, '.cache/js-dependency-regex');
fs.mkdirSync(work, { recursive: true });
const musl = path.join(root, '.cache/emsdk/upstream/emscripten/system/lib/libc/musl');
const sources = path.join(musl, 'src/regex');
// A portable copy of the actual musl ABI header avoids the host's regex_t and
// flag/error constants. Only its platform-specific alltypes include is replaced.
const header = fs.readFileSync(path.join(musl, 'include/regex.h'), 'utf8')
  .replace(/#include <features.h>[\s\S]*?#include <bits\/alltypes.h>/,
    '#include <stddef.h>\ntypedef int regoff_t;');
fs.writeFileSync(path.join(work, 'regex.h'), header);
fs.writeFileSync(path.join(work, 'locale_impl.h'), '#define LCTRANS_CUR(s) (s)\n');
const oracleSource = `
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <regex.h>
/* Match musl MB_CUR_MAX==1, not the host's different C-locale decoder. */
int nh_musl_mbtowc(wchar_t *out, const char *s, size_t n) {
    if (!s) return 0;
    if (!n) return -1;
    unsigned c = (unsigned char)*s;
    if (out) *out = c < 128 ? c : 0xdf00 | c;
    return c != 0;
}
/* musl accepts exactly these twelve class names. Host-only extensions are
   intentionally unavailable. Match characters are ASCII or surrogate bytes;
   host wide class results agree on this domain, independently of Unicode data. */
wctype_t nh_musl_wctype(const char *s) {
    const char *names[] = {"alnum","alpha","blank","cntrl","digit","graph",
      "lower","print","punct","space","upper","xdigit",NULL};
    for (int i=0; names[i]; ++i) if (!strcmp(s,names[i])) return wctype(s);
    return 0;
}
static unsigned char *unhex(char *s) {
    size_t n = strlen(s+1)/2;
    unsigned char *bytes = calloc(n+1,1);
    for (size_t i=0;i<n;++i) { unsigned c; sscanf(s+1+2*i,"%2x",&c); bytes[i]=c; }
    return bytes;
}
int main(void) {
    char *line=NULL; size_t capacity=0;
    while (getline(&line,&capacity,stdin)>0) {
        char *p=strtok(line," "), *t=strtok(NULL," ");
        char *f=strtok(NULL," "), *e=strtok(NULL," ");
        if (!p || !t || !f || !e) return 2;
        unsigned char *pattern=unhex(p), *text=unhex(t);
        regex_t re={0}; int status=regcomp(&re,(char *)pattern,atoi(f));
        int result=status ? -1 : regexec(&re,(char *)text,0,NULL,atoi(e));
        char error[128]; regerror(status,&re,error,sizeof error);
        printf("%d %d ",status,result);
        for (unsigned char *s=(unsigned char *)error;*s;++s) printf("%02x",*s);
        puts("");
        if (!status) regfree(&re);
        free(pattern); free(text);
    }
    free(line); return 0;
}
`;
// The shim calls the host wctype, while the musl parser calls the whitelist.
// Compile it separately, without the wctype rename, to avoid recursion.
fs.writeFileSync(path.join(work, 'oracle.c'), oracleSource);
const shimHeader = path.join(work, 'compat.h');
fs.writeFileSync(shimHeader, '#include <limits.h>\n#define hidden\n#undef RE_DUP_MAX\n#define RE_DUP_MAX 255\n#ifndef CHARCLASS_NAME_MAX\n#define CHARCLASS_NAME_MAX 14\n#endif\n');
function command(executable, args, options = {}) {
  const result = spawnSync(executable, args, { encoding: 'utf8', timeout: 60000, maxBuffer: 64 * 1024 * 1024, ...options });
  assert.equal(result.status, 0, `${executable}: ${result.error || result.stderr || result.status}`);
  return result.stdout;
}
const hostCC = path.join(root, '.cache/wasm64-build/host-cc');
const cltCC = '/Library/Developer/CommandLineTools/usr/bin/clang';
const compiler = process.env.CC || (fs.existsSync(hostCC) ? hostCC : process.platform === 'darwin' ? cltCC : 'cc');
const compilerArgs = !process.env.CC && compiler === cltCC
  ? ['-isysroot', '/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk'] : [];
const common = [...compilerArgs, '-O2', '-std=gnu17', '-I', work, '-I', sources, '-include', shimHeader,
  '-Dregcomp=nh_musl_regcomp', '-Dregexec=nh_musl_regexec',
  '-Dregerror=nh_musl_regerror', '-Dregfree=nh_musl_regfree'];
const objects = [];
for (const name of ['regcomp', 'regexec', 'regerror', 'tre-mem']) {
  const object = path.join(work, `${name}.o`); objects.push(object);
  command(compiler, [...common, '-Dmbtowc=nh_musl_mbtowc', '-Dwctype=nh_musl_wctype',
    '-c', path.join(sources, `${name}.c`), '-o', object]);
}
const oracle = path.join(work, 'musl-regex-oracle');
command(compiler, [...common, path.join(work, 'oracle.c'), ...objects, '-o', oracle]);

const bytes = value => typeof value === 'string' ? Buffer.from(value) : Buffer.from(value);
const hex = value => 'h' + bytes(value).toString('hex');
const patterns = [
  '', 'a', '^a$', 'a|b', '(ab)+', '[a-z]+', '[[:digit:]]{2,4}', '.', 'a.*b', 'a?b*',
  '(a)\\1', '\\(foo\\)', '\\bword\\b', 'a{0}', 'a{2,3}', '[^x]', '^[[:space:]]*$',
  '[', '(', '*a', 'a{', 'a{3,2}', '[z-a]', 'a\\', '[[:nope:]]', 'a{999999999999}',
  Buffer.from([65, 0, 91]), Buffer.from([0xff, 0x80]), 'é', '^.$', '(a|aa)*b',
  ')', 'a)', '(a))', '()', '(a|)', '(|a)', '|', '||', 'a||b', '^*', '$+',
  'a**', 'a++', 'a?+', 'a+?', 'a{2}*', 'a{2}{3}', 'a{,2}', 'a{2,}', 'a{255}',
  'a{256}', 'a{1,256}', 'a{2,1}', '{', '+', '?', 'a}', 'a{2', 'a{2,3', 'a{2,x}',
  '[]]', '[-a]', '[a-]', '[^]]', '[^]', '[a-z--@]', '[a-z-x]', '[--@]', '[a--]',
  '[a-[:alpha:]]', '[[:alpha:]-x]', '[[:alpha:]]', '[[:ascii:]]', '[[:word:]]',
  '[[:rune:]]', '[[:Alpha:]]', '[[:]]', '[[:alpha]', '[[.a.]]', '[[=a=]]',
  '[\\n]', '[\\]]', '[\\-a]', '[a-\\]', '[^^]', '[\n]',
  '\\t', '\\n', '\\r', '\\f', '\\a', '\\e', '\\v', '\\w', '\\W', '\\s', '\\S', '\\d', '\\D',
  '\\b', '\\B', '\\<', '\\>', '\\b!', '!\\b', '\\B!', '!\\B',
  '\\0', '\\1', '(a)\\1', '\\9', '\\10', '\\x', '\\x0', '\\x41', '\\x4142',
  '\\x{}', '\\x{41}', '\\x{00000041}', '\\x{000000041}', '\\x{110000}', '\\x{1100000}',
  '\\x{ffffffff}', '\\x{41', '\\x{gg}', '\\x{df80}', '\\x{dfff}', '\\x{80}', '\\x{e9}',
  '[^[:alpha:]]', '[^[:print:]]', '[[:cntrl:]]', '[[:punct:]]', '[[:blank:]]',
  'a^b', 'a$b', '(a|^)*b', '(^|a)b', '($|a)b', '(a?|b*){2,3}',
];
for (const cls of ['alnum', 'alpha', 'blank', 'cntrl', 'digit', 'graph', 'lower', 'print', 'punct', 'space', 'upper', 'xdigit']) {
  patterns.push(`^[[:${cls}:]]$`, `^[^[:${cls}:]]$`);
}
const texts = ['', 'a', 'b', 'A', 'aa', 'a1', 'abab', 'foo', '(foo)', 'word', 'wordy', '12', '12345',
  'a\nb', ' ', '\n', '\t', '\r', '\x07', '\x1b', '!', '!!', '_', 'é',
  Buffer.from([0xff, 0x80]), Buffer.from([65, 0, 66]), Buffer.from([0x80]), Buffer.from([0xff]),
  'abbbb', 'aaaaaab', 'abababab', '2', '\\', '-', ']', '^', '(', ')', '{', 'v', '1',
  ...Array.from({ length: 256 }, (_, i) => Buffer.from([i]))];
const cases = [];
for (const pattern of patterns) for (const text of texts) cases.push({ pattern, text, flags: 9, eflags: 0 });
for (const pattern of ['^a$', '^', '$', '\\b', '\\B', '^.*$', '(^|a)$'])
  for (const text of ['', 'a', 'aa', '\n']) for (let eflags = 0; eflags < 4; ++eflags)
    cases.push({ pattern, text, flags: 9, eflags });

let seed = 0x10ab975f;
const random = n => { seed ^= seed << 13; seed ^= seed >>> 17; seed ^= seed << 5; return (seed >>> 0) % n; };
const atoms = ['a', 'b', '.', '[a-c]', '[^ab]', '[[:digit:]]', '[[:space:]]', '\\w', '\\W', '\\b', '\\B', '^', '$', '\\1', '\\x41'];
function expression(depth = 0) {
  if (depth > 2 || random(3) === 0) return atoms[random(atoms.length)];
  const first = expression(depth + 1);
  switch (random(4)) {
    case 0: return '(' + first + '|' + expression(depth + 1) + ')';
    case 1: return '(' + first + ')' + ['*', '+', '?', '{0}', '{1,3}', '{2}'][random(6)];
    default: return first + expression(depth + 1);
  }
}
for (let i = 0; i < 1500; ++i) {
  let pattern = expression();
  if (random(6) === 0) pattern += ['[', '\\', '{3,1}', ')', '(', '|*'][random(6)];
  for (let j = 0; j < 12; ++j) {
    const text = Buffer.from(Array.from({ length: random(12) }, () => [97, 98, 99, 49, 32, 10, 33, 128, 255][random(9)]));
    cases.push({ pattern, text, flags: 9, eflags: random(4) });
  }
}
// Real NetHack user regex defaults and Lua syntax are not interchanged.
for (const pattern of ['^.*ring.*$', '.*(orc|goblin).*', '^[a-zA-Z ]+ potion$', '^[[:space:]]*#', '(a|aa)*b']) {
  for (const text of ['a ring of protection', 'an orc corpse', 'ruby potion', '  #comment', 'a'.repeat(2000), 'a'.repeat(2000) + 'b'])
    cases.push({ pattern, text, flags: 9, eflags: 0 });
}
// Raw byte-pattern fuzzing exercises parser/error precedence independently of
// the valid-expression generator, including C-locale non-ASCII and NUL bytes.
const patternBytes = [...Buffer.from('ab012[](){}*+?|^$\\-,:.x'), 0, 128, 255];
for (let i = 0; i < 2000; ++i) {
  const pattern = Buffer.from(Array.from({ length: random(20) }, () => patternBytes[random(patternBytes.length)]));
  for (const text of ['', 'a', 'ab1', '[]', Buffer.from([255, 128]), 'a\nb'])
    cases.push({ pattern, text, flags: 9, eflags: 0 });
}
const input = cases.map(test => `${hex(test.pattern)} ${hex(test.text)} ${test.flags} ${test.eflags}\n`).join('');
const output = command(oracle, [], { input }).trim().split('\n');
assert.equal(output.length, cases.length);
let comparisons = 0;
const cache = new Map();
for (let i = 0; i < cases.length; ++i) {
  const test = cases[i], [compile, execute, error] = output[i].split(' ');
  const key = hex(test.pattern);
  let js = cache.get(key);
  if (!js) { js = regex.compilePosixRegex(bytes(test.pattern)); cache.set(key, js); }
  const context = `pattern=${key} text=${hex(test.text)} flags=${test.eflags}`;
  assert.equal(js.status, Number(compile), `compile ${context}`);
  assert.equal(regex.posixRegexError(js.status), Buffer.from(error, 'hex').toString(), `error ${context}`);
  if (js.status === 0) assert.equal(regex.execPosixRegex(js.handle, bytes(test.text), test.eflags), Number(execute), `match ${context}`);
  ++comparisons;
}
let wasmComparisons = 0;
if (process.argv.includes('--wasm-cross-check')) {
  // Optional extra check against the actual existing Emscripten libc, without
  // C-locale shims. The current memory64 reference requires the SDK Node24;
  // default/native/production tests run on Node22. Its wrapper exposes eflags=0.
  const factory = (await import(pathToFileURL(process.env.POSIX_REGEX_WASM_ORACLE ?? path.join(root, '.cache/tu-probes/posixregex-reference.mjs')))).default;
  const {createPortedRuntime}=await import('../js/backends/emscripten/runtime.js');
  const layouts=JSON.parse(fs.readFileSync(path.join(root,'js/wasm/tu-layouts.json')));
  const reference = await factory({nethackPorted:createPortedRuntime(layouts)});
  const allocate = value => {
    const data = bytes(value), pointer = reference._malloc(BigInt(data.length + 1));
    reference.HEAPU8.set(data, Number(pointer)); reference.HEAPU8[Number(pointer) + data.length] = 0;
    return BigInt(pointer);
  };
  let previousKey = null, nativeHandle = null, nativeStatus = null;
  for (const test of cases) {
    if (test.eflags) continue;
    const key = hex(test.pattern), js = cache.get(key);
    if (key !== previousKey) {
      if (nativeHandle) reference._probe_free(nativeHandle);
      nativeHandle = reference._probe_init();
      const pointer = allocate(test.pattern);
      reference._probe_compile(pointer, nativeHandle);
      nativeStatus = reference._probe_err(nativeHandle);
      reference._free(pointer); previousKey = key;
    }
    assert.equal(js.status, nativeStatus, `Actual Emscripten compilation ${key}`);
    if (!nativeStatus) {
      const pointer = allocate(test.text);
      const result = reference._probe_match(pointer, nativeHandle);
      reference._free(pointer);
      assert.equal(regex.matchPosixRegex(js.handle, bytes(test.text)), !!result,
        `Actual Emscripten match ${key} ${hex(test.text)}`);
    }
    ++wasmComparisons;
  }
  if (nativeHandle) reference._probe_free(nativeHandle);
}
for (let code = -2; code < 20; ++code) {
  assert.equal(typeof regex.posixRegexError(code), 'string');
}
assert.equal(regex.posixRegexError(-1), 'Unknown error');
assert.equal(regex.posixRegexError(12345), 'Unknown error');
assert.throws(() => regex.compilePosixRegex('a', 0), /Only configured/);
assert.throws(() => regex.compilePosixRegex('a', 11), /Only configured/);
assert.throws(() => regex.compilePosixRegex('\u0100'), /encode Unicode/);
const first = regex.compilePosixRegex('^first$'), second = regex.compilePosixRegex('^second$');
assert.ok(regex.matchPosixRegex(first.handle, 'first'));
assert.ok(regex.matchPosixRegex(second.handle, 'second'));
assert.equal(regex.matchPosixRegex(first.handle, 'second'), false);
assert.equal(regex.freePosixRegex(first.handle), true);
assert.equal(regex.freePosixRegex(first.handle), false);
assert.equal(regex.execPosixRegex(first.handle, 'first'), regex.REG_BADPAT);
assert.ok(regex.matchPosixRegex(second.handle, 'second'));
const mutable = Uint8Array.from([97, 0, 91]);
const independent = regex.compilePosixRegex(mutable); mutable[0] = 98;
assert.ok(regex.matchPosixRegex(independent.handle, 'a\0b'));
assert.equal(regex.matchPosixRegex(independent.handle, 'b'), false);
for (let i = 0; i < 100; ++i) {
  const handle = regex.compilePosixRegex('^(a|b){1,3}$').handle;
  assert.ok(regex.matchPosixRegex(handle, 'aba')); regex.freePosixRegex(handle);
}
for (const result of cache.values()) if (result.handle) regex.freePosixRegex(result.handle);

// Evaluate production source with no importable host capabilities. Unlike
// merely checking import strings, this fails if startup attempts host access.
const production = fs.readFileSync(path.join(root, 'js/libraries/regex/posix.js'), 'utf8');
assert.equal(/\bimport(?:\s|\()/.test(production.replace(/\/\*[\s\S]*?\*\//g, '').replace(/\/\/[^\n]*/g, '')), false);
const context = vm.createContext({ Uint8Array, RegExp: undefined, WebAssembly: undefined,
  process: undefined, fetch: undefined, require: undefined, Buffer: undefined });
vm.runInContext(production.replace(/\bexport\s+/g, '') + `
  const isolated = compilePosixRegex('^[[:alpha:]]+\\\\b');
  if (isolated.status || !matchPosixRegex(isolated.handle, 'NetHack!')) throw Error('isolation failure');
  freePosixRegex(isolated.handle);
`, context);

// Persist input evidence only within this test's unique scratch directory.
fs.writeFileSync(path.join(work, 'results.json'), JSON.stringify({ comparisons, wasmComparisons,
  oracle: 'Pinned Emscripten musl regex C sources with renamed public symbols; C-locale byte decoder shim and identity error translation',
  configuredFlags: 9, captureOffsets: false, locales: ['C'],
  sourceFiles: Object.fromEntries(['regcomp.c', 'regexec.c', 'regerror.c', 'tre-mem.c', 'tre.h']
    .map(name => [name, createHash('sha256').update(fs.readFileSync(path.join(sources, name))).digest('hex')])),
  nativeOracleShims: ['musl regex.h ABI with portable size_t/regoff_t declarations',
    'C-locale musl byte-to-surrogate mbtowc', 'twelve-name musl wctype whitelist',
    'identity error-message translation', 'hidden visibility annotation removed', 'RE_DUP_MAX=255'],
  seed: '0x10ab975f' }, null, 2) + '\n');
console.log(`PASS: ${comparisons} native musl compile/error/match differentials; ${wasmComparisons} actual Emscripten cross-checks; byte/NUL/classes/extensions/counts/anchors; lifecycle and host-free execution.`);
