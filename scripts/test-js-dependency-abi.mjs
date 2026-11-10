// Exercise the experimental JS services through actual wasm64 C imports.
// Run build-js-dependency-game.py first; nothing writes active build outputs.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import { fileURLToPath, pathToFileURL } from 'node:url';
import { spawnSync } from 'node:child_process';

const root = fileURLToPath(new URL('../', import.meta.url));
const regexEnabled = process.argv.includes('--regex');
const buildArgument = process.argv.indexOf('--build-dir');
const build = buildArgument >= 0 ? path.resolve(process.argv[buildArgument + 1])
    : path.join(root, regexEnabled ? '.cache/js-dependency-game-regex' : '.cache/js-dependency-game');
const work = path.join(build, 'abi-tests');
const snapshot = path.join(build, 'snapshot');
const sdk = process.env.EMSDK || path.join(root, '.cache/emsdk');
assert.ok(fs.existsSync(path.join(snapshot, 'nethack-c/wasm/dependency-library.js')), 'Run scripts/build-js-dependency-game.py first');
fs.mkdirSync(work, { recursive: true });
const environment = { ...process.env, EMSDK: sdk,
    TELEPORT_JS_REGEX: regexEnabled ? '1' : '0',
    PATH: path.join(sdk, 'node/24.19.0_64bit/bin') + path.delimiter + process.env.PATH };
function command(program, args, expected = [0]) {
    const result = spawnSync(program, args, { encoding: 'utf8', env: environment, timeout: 60000 });
    assert.ok(expected.includes(result.status), `${program}: ${result.error || result.stderr || result.status}`);
    return result;
}
const source = `
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef TEST_JS_REGEX
#include <regex.h>
#endif
extern int tgetent(char *, const char *);
extern int tgetflag(const char *);
extern int tgetnum(const char *);
extern char *tgetstr(const char *, char **);
extern char *tparm(const char *, ...);
extern char *tgoto(const char *, int, int);
extern int tputs(const char *, int, int (*)(int));
extern int teleport_compress_file(const char *, const char *, int);
extern short ospeed;
static char emitted[200];
static int position;
static int byte(int c) { emitted[position++] = (char)c; return c; }
static int nested, allocation_worked;
static int reentrant_byte(int c) {
  byte(c);
  if (!nested) {
    nested = 1;
    tputs("inner", 1, byte);
    volatile char *large = malloc(32 * 1024 * 1024);
    if (large) { large[0] = 5; large[32 * 1024 * 1024 - 1] = 7; allocation_worked = 1; free((void *)large); }
  }
  return -1; /* ncurses ignores callback return values. */
}
int codec_run(int unpack) { return teleport_compress_file("/plain", "/plain.Z", unpack); }
int terminfo_run(void) {
  char area[1000], *next = area, *format, *copy;
  if (tgetent(NULL, "xterm-256color") != 1) return 1;
  if (tgetnum("co") != 132 || tgetnum("li") != 50 || tgetnum("Co") != 256) return 2;
  if (tgetflag("os") != 0 || tgetnum("zz") != -1 || tgetstr("zz", NULL)) return 3;
  format = tgetstr("cm", NULL);
  if (!format || tgetstr("cm", NULL) != format) return 4;
  copy = tgetstr("cm", &next);
  if (copy != area || strcmp(copy, format) || next != area + strlen(format) + 1) return 5;
  if (strcmp(tgoto(format, 3, 2), "\\033[3;4H")) return 6;
  if (strcmp(tparm("%p1%03d", 7), "007")) return 7;
  if (strcmp(tparm("%p1%p2%+%d", 2147483647L, 1L), "-2147483648")) return 8;
  if (strcmp(tparm("%p1%d/%p2%d", -37L, 5L), "-37/5")) return 9;
  if (strcmp(tparm(tgetstr("AF",NULL), 255), "\\033[38;5;255m")) return 10;
  if (strcmp(tparm(tgetstr("AF",NULL), 9), "\\033[91m")) return 11;
  if (strcmp(tgetstr("me",NULL), "\\033[0m")) return 12;
  position=0; memset(emitted,0,sizeof emitted);
  if (tputs("A$<1>B\\200",1,byte) || position != 3 || memcmp(emitted,"AB\\200",3)) return 13;
  if (tputs(NULL,1,byte) != -1) return 14;
  /* Preserve the configured wasm64 ncurses intptr_t varargs behavior. Four
     int arguments occupy two8-byte slots: consumed numeric cells are -37,17.
     This deliberately tests a historical caller/library ABI mismatch. */
  if (strcmp(tparm("%p1%d/%p2%d", -37, 5, 17, 19), "-37/17")) return 15;
  if (strcmp(tparm(tgetstr("Ic",NULL), 15L, 1000L, 0L, 500L), "\\033]4;15;rgb:FF/00/7F\\033\\\\")) return 16;
  position=0; nested=0; allocation_worked=0; memset(emitted,0,sizeof emitted);
  if (tputs("outer",1,reentrant_byte) || strcmp(emitted,"oinneruter") || !allocation_worked) return 17;
  ospeed=0;
  return 0;
}
int main(void) { return 0; }
#ifdef TEST_JS_REGEX
const char *regex_case(int index) {
  static const struct { const char *pattern, *text; int flags; } corpus[] = {
    {"", "anything", 0}, {"[", "a", 0}, {"(a", "a", 0}, {"a{3,2}", "aa", 0},
    {"^scroll of (identify|enchant weapon)$", "scroll of identify", 0},
    {"potion.*healing", "a potion of extra healing", 0},
    {"[[:digit:]]+", "level42", 0}, {"^orc$", "orc", REG_NOTBOL},
    {"^orc$", "orc", REG_NOTEOL}, {"a{2,4}", "aaa", 0},
    {"\\\\<orc\\\\>", "an orc corpse", 0}, {"(a)\\\\1", "a1", 0},
    {"[\\200-\\377]", "\\200", 0}, {"^a$", "aa", 0},
    {"[[:madeup:]]", "x", 0}, {"a\\\\", "x", 0},
  };
  static char output[400];
  if (index < 0 || index >= (int)(sizeof corpus/sizeof corpus[0])) return NULL;
  regex_t re = {0}; char error[128], truncated[4];
  int code = regcomp(&re, corpus[index].pattern, REG_EXTENDED|REG_NOSUB);
  int matched = code ? -1 : regexec(&re, corpus[index].text, 0, NULL, corpus[index].flags);
  size_t length = regerror(code, &re, error, sizeof error);
  size_t short_length = regerror(code, &re, truncated, sizeof truncated);
  size_t zero_length = regerror(code, &re, NULL, 0);
  snprintf(output, sizeof output, "%d:%d:%zu:%s:%zu:%s:%zu", code, matched, length, error, short_length, truncated, zero_length);
  if (!code) regfree(&re);
  return output;
}
#endif
`;
const probeC = path.join(work, 'probe.c'), probeJS = path.join(work, 'probe.mjs');
fs.writeFileSync(probeC, source);
command(path.join(sdk, 'upstream/emscripten/emcc'), ['-O2', '-std=gnu17', '-sMEMORY64=1',
    ...(regexEnabled ? ['-DTELEPORT_JS_REGEX=1', '-DTEST_JS_REGEX=1'] : []),
    '-sMODULARIZE=1', '-sEXPORT_ES6=1', '-sENVIRONMENT=node', '-sALLOW_MEMORY_GROWTH=1',
    '-sEXPORTED_FUNCTIONS=_terminfo_run,_codec_run' + (regexEnabled ? ',_regex_case' : ''),
    '-sEXPORTED_RUNTIME_METHODS=FS,ENV,UTF8ToString',
    '--js-library', path.join(snapshot, 'nethack-c/wasm/dependency-library.js'),
    path.join(snapshot, 'nethack-c/wasm/dependency-bridge.c'), probeC, '-o', probeJS]);
const { createWasmDependencyRuntime } = await import(pathToFileURL(path.join(snapshot, 'js/services/wasm-dependency-runtime.js')));
const { compressUnixZ } = await import(pathToFileURL(path.join(snapshot, 'js/services/unix-compress.js')));
const createProbe = (await import(pathToFileURL(probeJS))).default;
const dependencies = createWasmDependencyRuntime({ regex: regexEnabled });
const errors = [];
const module = await createProbe({ noInitialRun: true, nethackDependencies: dependencies,
    printErr: text => errors.push(text), preRun: [instance => Object.assign(instance.ENV, { LINES: '50', COLUMNS: '132' })] });
assert.equal(module._terminfo_run(), 0, 'C ABI: dimensions, capability pointers/area, numeric varargs, RGB/colors and function callback');
// Run the identical C call-site probe against the configured ncurses library,
// including the deliberate int/long vararg packing test above. Native macOS
// LP64 varargs use a different calling convention and cannot verify this ABI.
const oracleJS = path.join(work, 'configured-oracle.mjs');
command(path.join(sdk, 'upstream/emscripten/emcc'), ['-O2', '-std=gnu17', '-sMEMORY64=1',
    ...(regexEnabled ? ['-DTEST_JS_REGEX=1'] : []),
    '-sMODULARIZE=1', '-sEXPORT_ES6=1', '-sENVIRONMENT=node', '-sALLOW_MEMORY_GROWTH=1',
    '-sEXPORTED_FUNCTIONS=_terminfo_run,_codec_run' + (regexEnabled ? ',_regex_case' : ''),
    '-sEXPORTED_RUNTIME_METHODS=FS,ENV,UTF8ToString',
    '--embed-file', path.join(root, 'nethack-c/wasm/terminfo') + '@/terminfo', probeC,
    path.join(root, '.cache/ncurses-wasm64-build/lib/libtinfo.a'),
    path.join(root, 'nethack-c/wasm/compress-service.c'), '-o', oracleJS]);
const createOracle = (await import(pathToFileURL(oracleJS))).default;
const oracle = await createOracle({ noInitialRun: true, printErr: text => errors.push(text),
    preRun: [instance => Object.assign(instance.ENV, { LINES: '50', COLUMNS: '132', TERMINFO: '/terminfo' })] });
assert.equal(oracle._terminfo_run(), 0, 'Identical probe verifies configured ncurses wasm64 ABI behavior');
let regexCases = 0;
if (regexEnabled) {
    for (let i = 0; ; ++i) {
        const expected = oracle._regex_case(i), actual = module._regex_case(i);
        if (!expected) { assert.equal(actual, 0n); break; }
        assert.equal(module.UTF8ToString(Number(actual)), oracle.UTF8ToString(Number(expected)),
            `Configured-musl corpus case ${i}: compile/exec/error/truncation/required length`);
        ++regexCases;
    }
}
const FS = module.FS;
const remove = file => { try { FS.unlink(file); } catch {} };
let random = 0x12345678;
const noise = Uint8Array.from({ length: 600000 }, () => { random ^= random << 13; random ^= random >>> 17; random ^= random << 5; return random & 255; });
const fixtures = [Uint8Array.from(Buffer.from('NetHack save and bones\0'.repeat(20000))),
    noise.subarray(0, 30000), new Uint8Array(0), Uint8Array.of(65),
    Uint8Array.from([...new Uint8Array(400000).fill(65), ...noise, ...new Uint8Array(400000).fill(66)])];
for (const [index, original] of fixtures.entries()) {
    FS.writeFile('/plain', original);
    const expected = compressUnixZ(original);
    assert.equal(module._codec_run(0), expected.status, `Compression status fixture ${index}`);
    assert.deepEqual(FS.readFile('/plain.Z'), expected.bytes, `C-to-JS codec bytes fixture ${index}`);
    const packed = path.join(work, 'plain.Z');
    fs.writeFileSync(packed, expected.bytes);
    if (original.length) {
        command('/usr/bin/uncompress', ['-f', packed]);
        assert.deepEqual(fs.readFileSync(packed.slice(0, -2)), Buffer.from(original));
        assert.equal(module._codec_run(1), 0);
        assert.deepEqual(FS.readFile('/plain'), original);
    } else assert.equal(module._codec_run(1), 1, 'Existing service rejects header-only empty .Z');
}
remove('/plain'); FS.writeFile('/plain.Z', Uint8Array.of(7, 8, 9));
assert.equal(module._codec_run(0), 1, 'Missing source failure');
assert.deepEqual(FS.readFile('/plain.Z'), Uint8Array.of(7, 8, 9), 'Missing source does not truncate destination');
remove('/plain.Z'); FS.mkdir('/plain.Z'); FS.writeFile('/plain', fixtures[0]);
assert.equal(module._codec_run(0), 1, 'Destination directory failure');
FS.rmdir('/plain.Z'); FS.writeFile('/plain.Z', Uint8Array.of(0x1f, 0x9d, 0x90, 255, 255));
assert.equal(module._codec_run(1), 1, 'Corrupt input failure');
assert.equal(FS.readFile('/plain').length, 0, 'Destination opened/truncated before decode');
FS.writeFile('/plain', fixtures[0]);
assert.equal(module._codec_run(0), 0, 'Recovery after failure');
assert.equal(module._codec_run(1), 0);
assert.deepEqual(FS.readFile('/plain'), fixtures[0]);

// Import table proves executable game dependency entry points are JS imports;
// the symbol map excludes ncurses and codec algorithm implementations.
const gameBytes = fs.readFileSync(path.join(build, 'nethack.wasm'));
const imports = WebAssembly.Module.imports(new WebAssembly.Module(gameBytes)).map(item => item.name);
for (const name of ['tgetent', 'tgetstr', 'tgetnum', 'tgetflag', 'tgoto',
    imports.includes('teleport_js_tputs') ? 'teleport_js_tputs' : 'tputs', 'teleport_js_tparm', 'teleport_compress_file'])
    assert.ok(imports.includes(name), `Live game imports JS dependency ${name}`);
const symbols = fs.readFileSync(path.join(build, 'nethack.mjs.symbols'), 'utf8').split('\n').map(line => line.split(':').slice(1).join(':'));
for (const name of ['compress', 'decompress', 'ncompress_encode', 'ncompress_decode', 'setupterm', '_nc_read_entry', '_nc_tparm_analyze'])
    assert.ok(!symbols.includes(name), `Compiled dependency algorithm removed: ${name}`);
if (regexEnabled) {
    for (const name of ['regcomp', 'regexec', 'regerror', 'regfree'])
        assert.ok(imports.includes('teleport_js_' + name), `Live game imports JS ${name}`);
    assert.ok(!symbols.some(name => name.startsWith('tre_')), 'Compiled TRE algorithms removed');
    for (const name of ['regcomp', 'regexec', 'regerror', 'regfree']) assert.ok(dependencies.calls[name] > 0);
}
fs.writeFileSync(path.join(work, 'results.json'), JSON.stringify({ passed: true, calls: dependencies.calls,
    gameDependencyImports: imports.filter(name => /tget|tgoto|tputs|teleport_js_tparm|teleport_compress_file/.test(name)),
    diagnostics: errors, gameWasmBytes: gameBytes.length, regexCases }, null, 2) + '\n');
console.log(`PASS: wasm64 C/JS terminfo ABI, callback/area pointers and numeric varargs; JS codec/MEMFS/native interoperability, status0/1/2 and errors; removed compiled dependencies. Calls: ${JSON.stringify(dependencies.calls)}`);
