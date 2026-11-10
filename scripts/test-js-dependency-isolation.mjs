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
const services = path.join(root, 'js/services');
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
async function load(url) {
    const identifier = url.href;
    if (modules.has(identifier)) return modules.get(identifier);
    const filename = fileURLToPath(url);
    assert.ok(filename.startsWith(services + path.sep),
        `Production import escapes dependency service directory: ${identifier}`);
    const module = new vm.SourceTextModule(await fs.readFile(filename, 'utf8'), {
        context, identifier,
        importModuleDynamically: () => { throw new Error('Runtime imports forbidden'); },
    });
    modules.set(identifier, module);
    await module.link((specifier, referencing) => {
        assert.ok(specifier.startsWith('./') || specifier.startsWith('../'),
            `Production dependency imports a host/package module: ${specifier}`);
        return load(new URL(specifier, referencing.identifier));
    });
    return module;
}

const compress = await load(pathToFileURL(path.join(services, 'unix-compress.js')));
const terminfo = await load(pathToFileURL(path.join(services, 'terminfo.js')));
await compress.evaluate({ timeout: 5000 });
await terminfo.evaluate({ timeout: 5000 });
context.codec = compress.namespace;
context.terminalServices = terminfo.namespace;

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
`, context, { timeout: 5000 });

console.log(`PASS: ${modules.size} production dependency modules load and execute with host imports, dynamic loading, Wasm, network, and Node globals unavailable.`);
