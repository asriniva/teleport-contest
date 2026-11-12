// Development-only check: dependency services execute without a Wasm or Node host.
// Native interoperability is tested separately by each dependency's oracle tests.
import assert from 'node:assert/strict';
import fs from 'node:fs/promises';
import path from 'node:path';
import { spawnSync } from 'node:child_process';
import { fileURLToPath, pathToFileURL } from 'node:url';
import vm from 'node:vm';

if (typeof vm.SourceTextModule !== 'function') {
    const result = spawnSync(process.execPath,
        ['--experimental-vm-modules', fileURLToPath(import.meta.url)],
        { stdio: 'inherit', timeout: 30000 });
    if (result.error) throw result.error;
    process.exit(result.status ?? 1);
}

const root = fileURLToPath(new URL('../', import.meta.url));
const owners = ['c-runtime','ported','nethack','lua','platform','libraries'].map(name => path.join(root,'js',name)+path.sep);
const forbidden = ['WebAssembly', 'process', 'require', 'Buffer', 'fetch',
    'XMLHttpRequest', 'Worker', 'SharedWorker'];
const context = vm.createContext({ TextEncoder, TextDecoder, atob, btoa }, {
    name: 'standalone-dependency-services',
    codeGeneration: { strings: false, wasm: false },
});
for (const name of forbidden) {
    Object.defineProperty(context, name, { value: undefined, writable: false,
        configurable: false });
}
const modules = new Map();
const pendingModules = new Map();
async function load(url) {
    const identifier = url.href;
    if (pendingModules.has(identifier)) return pendingModules.get(identifier);
    const pending = createModule(url);
    pendingModules.set(identifier, pending);
    return pending;
}
async function createModule(url) {
    const identifier = url.href;
    const filename = fileURLToPath(url);
    if(filename===path.join(root,'js/isaac64.js'))assert.deepEqual(await fs.readFile(filename),await fs.readFile(path.join(root,'frozen/isaac64.js')),'Canonical frozen ISAAC bytes');
    assert.ok(owners.some(owner=>filename.startsWith(owner))||filename===path.join(root,'js/isaac64.js'),
        `Production import escapes explicit dependency owners: ${identifier}`);
    const module = new vm.SourceTextModule(await fs.readFile(filename, 'utf8'), {
        context, identifier,
        importModuleDynamically: () => { throw new Error('Runtime imports forbidden'); },
    });
    modules.set(identifier, module);
    return module;
}
async function evaluate(module) {
    // Let the VM linker handle cycles. Manually linking child modules while a
    // parent graph is linking races on shared dependencies and rejects valid
    // cycles such as Lua table/value modules.
    if (module.status === 'unlinked') await module.link((specifier, referencing) => {
        assert.ok(specifier.startsWith('./') || specifier.startsWith('../'),
            `Production dependency imports a host/package module: ${specifier}`);
        return load(new URL(specifier, referencing.identifier));
    });
    await module.evaluate({ timeout: 5000 });
}

const compress = await load(pathToFileURL(path.join(root, 'js/libraries/compress/unix-z.js')));
const terminfo = await load(pathToFileURL(path.join(root, 'js/libraries/terminfo/index.js')));
const regex = await load(pathToFileURL(path.join(root, 'js/libraries/regex/posix.js')));
const runtime = await load(pathToFileURL(path.join(root, 'js/nethack/runtime.js')));
const lua = await load(pathToFileURL(path.join(root, 'js/lua/lua.js')));
const bytecode = await load(pathToFileURL(path.join(root, 'js/lua/bytecode-vm.js')));
const timezone = await load(pathToFileURL(path.join(root, 'js/platform/timezone/info.js')));
const luaOS = await load(pathToFileURL(path.join(root, 'js/lua/os-library.js')));
const luaOSServices = await load(pathToFileURL(path.join(root, 'js/lua/os-abi.js')));
const luaABI = await load(pathToFileURL(path.join(root, 'js/lua/abi.js')));
const gameFiles = await load(pathToFileURL(path.join(root, 'js/nethack/game-files.js')));
await evaluate(compress);
await evaluate(terminfo);
await evaluate(regex);
await evaluate(runtime);
await evaluate(lua);
await evaluate(bytecode);
await evaluate(timezone);
await evaluate(luaOS);
await evaluate(luaOSServices);
await evaluate(luaABI);
await evaluate(gameFiles);
context.codec = compress.namespace;
context.terminalServices = terminfo.namespace;
context.regexServices = regex.namespace;
context.runtimeServices = runtime.namespace;
context.luaServices = lua.namespace;
context.bytecodeServices = bytecode.namespace;
context.timezoneServices = timezone.namespace;
context.luaOSLibrary = luaOS.namespace;
context.luaOSServices = luaOSServices.namespace;
context.luaABI = luaABI.namespace;
context.gameFiles = gameFiles.namespace;

vm.runInContext(`
    for (const name of ${JSON.stringify(forbidden)}) {
        if (globalThis[name] !== undefined) throw Error('Host global available: ' + name);
    }
    const original = new Uint8Array(16000);
    for (let i = 0; i < original.length; i++) original[i] = i % 31;
    const packed = codec.compressUnixZ(original);
    if (packed.status !== 0 || packed.bytes.length >= original.length)
        throw Error('Standalone compressor failed');
    const restored = codec.decompressUnixZ(packed.bytes);
    if (restored.status !== 0 || restored.bytes.length !== original.length)
        throw Error('Standalone decompressor failed');
    for (let i = 0; i < original.length; i++) {
        if (restored.bytes[i] !== original[i]) throw Error('Standalone byte mismatch');
    }
    const terminal = terminalServices.createTerminfo();
    if (terminal.tgetent(null, 'xterm-256color') !== 1)
        throw Error('Embedded terminal entry unavailable');
    if (terminal.tgetnum('co') !== 80 || terminal.tgetnum('li') !== 24)
        throw Error('Standalone terminal dimensions differ');
    if (terminal.tgoto(terminal.tgetstr('cm'), 3, 2) !== '\\x1b[3;4H')
        throw Error('Standalone cursor expansion differs');
    let emitted = '';
    const clear = terminal.tgetstr('cl');
    terminal.tputs(clear, 24, byte => { emitted += String.fromCharCode(byte); return byte; });
    if (emitted !== clear) throw Error('Standalone terminal output differs');
    if (terminal.tgetent(null, 'teleport-no-such-terminal') !== 0)
        throw Error('Unknown terminal silently accepted');
    const expression = regexServices.compilePosixRegex('^[[:digit:]]{2}$');
    if (expression.status !== 0 || regexServices.execPosixRegex(expression.handle, '12') !== 0
        || regexServices.execPosixRegex(expression.handle, 'abc') !== 1)
        throw Error('Standalone POSIX regex failed');
    regexServices.freePosixRegex(expression.handle);
    const state = runtimeServices.createJsRuntime({initialBytes: 512});
    const buffer = state.createStrbuf();
    state.memory.withScope(scope => state.strutil('strbuf_append', buffer, scope.cstring('independent')));
    if (state.memory.readString(buffer.str) !== 'independent') throw Error('JS-owned string state failed');
    const hash = state.createMD4(); hash.update(new Uint8Array([97,98,99]));
    if (Array.from(hash.final(), byte => byte.toString(16).padStart(2, '0')).join('')
        !== 'a448017aaf21d8525fc10ae87aa6729d') throw Error('JS-owned MD4 failed');
    state.FS.mkdirTree('/nethack/save');
    state.FS.writeFile('/nethack/save/player', original);
    const saved = gameFiles.captureGameFiles(state.FS, {}, () => true);
    const other = runtimeServices.createJsRuntime();
    gameFiles.restoreGameFiles(other.FS, JSON.stringify(saved));
    if (other.FS.readFile('/nethack/save/player').some((byte, i) => byte !== original[i]))
        throw Error('Independent persistence failed');
    state.setEnvironment('NETHACK_FIXED_DATETIME', '20000229123456');
    if (state.calendar('yyyymmdd', 0n) !== 20000229n)
        throw Error('JS-owned calendar failed');
    const wrapper = state.regexContext(state.posixregex('regex_init'));
    state.memory.withScope(scope => {
        if (state.posixregex('regex_compile', scope.cstring('^orc$'), wrapper) !== 1
            || state.posixregex('regex_match', scope.cstring('orc'), wrapper) !== 1)
            throw Error('Independent NetHack regex wrapper failed');
    });
    state.posixregex('regex_free', wrapper);
    const language = luaServices.createLua({seed: 0n});
    const values = language.execute('return (9223372036854775807 + 1), 6 * 7');
    if (values[0] !== -9223372036854775808n || values[1] !== 42n)
        throw Error('Standalone Lua integer execution failed');
    const compiled = bytecodeServices.createLuaBytecodeVM({baseMeta: true});
    const source = 'local function sum(n) local s=0;for i=1,n do s=s+i end return s end;return sum(9),string.pack("<I4",0x12345678)';
    const chunk = compiled.compile(source, '@standalone.lua');
    const bytes = compiled.dumpBinary(chunk);
    const result = compiled.call(compiled.loadBinary(bytes, '@reloaded.lua'));
    if (result[0] !== 45n || result[1] !== '\\x78\\x56\\x34\\x12')
        throw Error('Standalone Lua compile/dump/load/execute failed');
    if (state.libc.format('%a', 1.1) !== '0x1.199999999999ap+0')
        throw Error('Standalone C floating-point formatting failed');
    const historical = timezoneServices.lookupTimezone('America/New_York', -880000000n);
    if (historical.abbreviation !== 'EWT' || historical.offset !== -14400)
        throw Error('Standalone historical timezone data failed');
    const osHost = luaOSServices.createLuaOSServices({
        osTimezone: () => 'America/New_York', osTMLayout: () => 0,
        sortClock: () => 1000n, osClockRate: () => 1000n, sortTime: () => 0n,
        heap: () => { throw Error('Calendar unexpectedly uses C memory'); },
    });
    luaOSLibrary.openLuaOS(compiled, osHost);
    const dates = compiled.execute('return os.date("!%Y|%C|%G|%g",-62198755200),os.date("!%Y",67768036160140800),os.time({year=2000,month=2,day=29,hour=12})');
    if (dates[0] !== '-001|-0|-002|02' || dates[1] !== '2147485547' || dates[2] !== 951843600n)
        throw Error('Standalone native Lua calendar/strftime failed');
    if (typeof luaABI.createLuaAbi() !== 'object') throw Error('Lua ABI provider requires a host before binding');
`, context, { timeout: 5000 });

console.log(`PASS: ${modules.size} production dependency modules load and execute with host imports, dynamic loading, Wasm, network, and Node globals unavailable.`);
