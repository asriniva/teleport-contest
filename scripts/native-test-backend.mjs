// Native host adapter for the EXISTING differential tests. Memory accesses use
// real C pointers through Node-API; no C behavior is supplied by this adapter.
import assert from 'node:assert/strict';
import caseAssert from './native-test-assert.mjs';
import { createHash } from 'node:crypto';
import { createRequire } from 'node:module';
import { copyFileSync, readFileSync, mkdirSync, unlinkSync, writeFileSync, openSync, closeSync } from 'node:fs';
import { fileURLToPath } from 'node:url';
import { createNativeHacklibFS } from './native-hacklib-fs.mjs';
const require = createRequire(import.meta.url);
const root = new URL('../', import.meta.url);
// Native C is authoritative. Wasm C is available only as an explicit diagnostic.
const nativeMode = process.env.TELEPORT_NATIVE_TESTS !== '0';
export const referenceLabel = nativeMode ? 'native-C' : 'Emscripten-C';
let sequence = 0;
const builtins = Object.fromEntries(['DataView', 'Int8Array', 'Uint8Array', 'Int16Array', 'Uint16Array', 'Int32Array', 'Uint32Array', 'Float32Array', 'Float64Array', 'BigInt64Array', 'BigUint64Array'].map(name => [name, globalThis[name]]));
const index = key => typeof key === 'string' && /^\d+$/.test(key) ? Number(key) : null;
function view(buffer, start = 0, length) {
    const api = buffer.nativeAPI;
    const methods = {};
    for (const kind of ['Int8','Uint8','Int16','Uint16','Int32','Uint32','Float32','Float64','BigInt64','BigUint64']) {
        const size = Number(kind.match(/\d+/)[0]) / 8;
        methods['get' + kind] = (offset, little = false) => {
            const bytes = api._read(BigInt(start + Number(offset)), BigInt(size));
            return new builtins.DataView(bytes.buffer, bytes.byteOffset, size)['get' + kind](0, little);
        };
        methods['set' + kind] = (offset, value, little = false) => {
            const bytes = Buffer.alloc(size);
            new builtins.DataView(bytes.buffer, bytes.byteOffset, size)['set' + kind](0, value, little);
            api._write(BigInt(start + Number(offset)), bytes);
        };
    }
    return methods;
}
function typed(name, buffer, start, length) {
    const original = builtins[name], size = original.BYTES_PER_ELEMENT;
    const data = view(buffer, start);
    const kind = name.replace('Array', '');
    const type = kind === 'BigInt64' ? 'BigInt64' : kind === 'BigUint64' ? 'BigUint64' : kind;
    const object = {
        length, byteLength: length * size, byteOffset: start, buffer,
        set(values, offset = 0) { Array.from(values).forEach((value, i) => data['set' + type]((i + offset) * size, value, true)); },
        fill(value, first = 0, last = length) { for (let i = first; i < last; i++) data['set' + type](i * size, value, true); return proxy; },
        slice(first = 0, last = length) { return original.from(Array.from(proxy).slice(first, last)); },
        subarray(first = 0, last = length) { return typed(name, buffer, start + first * size, last - first); },
        *[Symbol.iterator]() { for (let i = 0; i < length; i++) yield data['get' + type](i * size, true); },
    };
    const proxy = new Proxy(object, {
        get(target, key) { const i = index(key); return i === null ? target[key] : data['get' + type](i * size, true); },
        set(target, key, value) { const i = index(key); if (i === null) target[key] = value; else data['set' + type](i * size, value, true); return true; },
    });
    return proxy;
}
function constructor(name) {
    return new Proxy(builtins[name], { construct(target, args) {
        if (!args[0]?.nativeAPI) return Reflect.construct(target, args);
        if (name === 'DataView') return view(...args);
        return typed(name, ...args);
    } });
}
export const DataView = constructor('DataView');
export const Int8Array = constructor('Int8Array'), Uint8Array = constructor('Uint8Array');
export const Int16Array = constructor('Int16Array'), Uint16Array = constructor('Uint16Array');
export const Int32Array = constructor('Int32Array'), Uint32Array = constructor('Uint32Array');
export const Float32Array = constructor('Float32Array'), Float64Array = constructor('Float64Array');
export const BigInt64Array = constructor('BigInt64Array'), BigUint64Array = constructor('BigUint64Array');
export function assertStackRestored(module, before, message) {
    if (module.nativeC) assert.ok(module._stack_status() > 0n, message || 'Every native C call restores its caller stack');
    else assert.equal(module._probe_stack(), before, message);
}
export function memoryCheckpoint(module) {
    return module.nativeC ? { nativeAllocated: module._allocated() } : module.HEAPU8.buffer;
}
export function assertMemoryGrowth(module, before, message) {
    if (module.nativeC) caseAssert.ok(module._allocated() > before.nativeAllocated, message || 'The same allocation case must allocate native memory');
    else assert.notEqual(module.HEAPU8.buffer, before, message);
}
export function allocationMetric(module) {
    return module.nativeC ? Number(module._allocated()) : module.HEAPU8.byteLength;
}
export function referenceBackend(name, emscriptenFactory) {
    if (!nativeMode) {
        if (!emscriptenFactory) return undefined;
        return async (options = {}) => {
            // The golden build supplies these same JS dependency services to
            // remaining C callers. The original tested TU still executes in C.
            const {createPortedRuntime} = await import('../js/backends/emscripten/runtime.js');
            const layouts = JSON.parse(readFileSync(new URL('js/wasm/tu-layouts.json', root)));
            return emscriptenFactory({nethackPorted:createPortedRuntime(layouts), ...options});
        };
    }
    return async () => {
        // Loading a private library copy gives each factory call independent
        // NetHack globals, just as separate Wasm instances have independent state.
        const source = new URL(`.cache/tu-probes/native-oracles/${name}-native.node`, root);
        const manifest=JSON.parse(readFileSync(new URL(`.cache/tu-probes/native-oracles/${name}-full-native-build.json`,root)));
        for(const [path,expected] of Object.entries(manifest.hashes)) {
            const actual=createHash('sha256').update(readFileSync(path)).digest('hex');
            assert.equal(actual,expected,`${name}: native source changed; rebuild before testing (${path})`);
        }
        const instance = new URL(`.cache/tu-probes/native-oracles/${name}-instance-${process.pid}-${sequence++}.node`, root);
        copyFileSync(source, instance);
        const api = require(fileURLToPath(instance));
        globalThis.__nativeTestInstances = (globalThis.__nativeTestInstances || 0) + 1;
        const fsRoot = fileURLToPath(new URL(`.cache/native-fs/${process.pid}-${sequence}`, root));
        mkdirSync(fsRoot, { recursive: true });
        api._set_root(fsRoot);
        process.once('exit', () => { try { unlinkSync(instance); } catch {} });
        const signatures = JSON.parse(readFileSync(new URL(`.cache/tu-probes/native-oracles/${name}-signatures.json`, root)));
        const buffer = { nativeAPI: api };
        let cached = [];
        const heap = {
            buffer,
            slice(start, end) { return api._read(BigInt(start), BigInt(end - start)); },
            subarray(start, end) { return api._read(BigInt(start), BigInt(end - start)); },
            set(bytes, start = 0) { api._write(BigInt(start), Buffer.from(bytes)); cached = []; },
            fill(value, start, end) { api._write(BigInt(start), Buffer.alloc(end - start, value)); cached = []; return proxy; },
            copyWithin(target, start, end) { api._write(BigInt(target), api._read(BigInt(start), BigInt(end - start))); cached = []; return proxy; },
        };
        const proxy = new Proxy(heap, {
            get(target, key) {
                const address = index(key);
                if (address === null) return target[key];
                if (!address) throw new RangeError('Native address zero cannot be read; use the explicit NULL-output case check');
                const cachedBlock = cached.find(block => address >= block.start && address < block.start + block.bytes.length);
                return cachedBlock ? cachedBlock.bytes[address - cachedBlock.start] : api._read(BigInt(address), 1n)[0];
            },
            set(target, key, value) {
                const address = index(key);
                if (address === null) target[key] = value;
                else { api._write(BigInt(address), Buffer.from([value])); cached = []; }
                return true;
            },
        });
        const fsPath = path => fsRoot + '/' + path.replace(/^\/+/, '');
        const FS = {
            readFile: path => readFileSync(fsPath(path)),
            writeFile: (path, data) => writeFileSync(fsPath(path), data),
            open: (path, flags) => ({ fd: openSync(fsPath(path), flags) }),
            close: stream => closeSync(stream.fd),
            unlink: path => unlinkSync(fsPath(path)),
        };
        const module = { nativeC: true, HEAPU8: proxy, _allocated: api._allocated, _stack_status: api._stack_status, FS };
        if (name === 'hacklib') module.FS = createNativeHacklibFS(api, fsRoot);
        for (const key of Object.keys(api).filter(key => key.startsWith('_probe_') || key === '_malloc' || key === '_free')) {
            module[key] = (...args) => {
                cached = [];
                if (name === 'calendar') api._set_clock(BigInt(Math.trunc(Date.now() / 1000)));
                if (process.env.TELEPORT_NATIVE_TRACE === '1') console.error('NATIVE CALL', name, key, args.map(String).join(','));
                let result = api[key](...args.map(value => value ?? 0));
                const ret = signatures[key]?.return ?? '';
                // Match the exported Wasm wire representation, retaining the
                // actual C bit pattern (not treating unsigned values as pointers).
                if (typeof result === 'bigint' && !ret.includes('*') && !['uintptr_t'].includes(ret)) result = BigInt.asIntN(64, result);
                if (typeof result === 'number' && /^(unsigned int|uint32_t|uint32)$/.test(ret)) result |= 0;
                if (result && /^(?:const )?char \*$/.test(signatures[key]?.return ?? '') && /(?:trace|snapshot|name|message|diagnostic|description|format|identifier|genbuf)/.test(key)) {
                    cached.push({ start: Number(result), bytes: api._cstring(result) });
                }
                return result;
            };
        }
        return module;
    };
}
