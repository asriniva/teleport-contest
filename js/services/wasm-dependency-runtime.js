// Temporary memory/filesystem adapter for the experimental mixed game build.
// Algorithms are in the standalone byte/string services, which know no Wasm.
import { createTerminfo } from './terminfo.js';
import { compressUnixZ, decompressUnixZ } from './unix-compress.js';

export function createWasmDependencyRuntime() {
    const terminfo = createTerminfo();
    const capabilityPointers = new Map();
    const calls = { tgetent: 0, tgetflag: 0, tgetnum: 0, tgetstr: 0, tparm: 0, tgoto: 0, tputs: 0, compress: 0, decompress: 0 };
    let expansion = 0, expansionSize = 0;
    const string = (services, pointer) => {
        pointer = Number(pointer);
        if (!pointer) return null;
        const heap = services.heap();
        let value = '';
        for (; pointer < heap.length && heap[pointer]; ++pointer) value += String.fromCharCode(heap[pointer]);
        return value;
    };
    const writeString = (services, pointer, value) => {
        const heap = services.heap();
        for (let i = 0; i < value.length; ++i) heap[pointer + i] = value.charCodeAt(i) & 255;
        heap[pointer + value.length] = 0;
    };
    const result = (services, value) => {
        if (value === null) return 0;
        if (value.length + 1 > expansionSize) {
            if (expansion) services.free(expansion);
            expansionSize = Math.max(256, value.length + 1);
            expansion = services.malloc(expansionSize);
            if (!expansion) throw new Error('JS terminfo expansion allocation failed');
        }
        writeString(services, expansion, value);
        return expansion;
    };
    return {
        calls,
        tgetent(services, name) {
            ++calls.tgetent;
            const lines = Number(services.ENV.LINES), columns = Number(services.ENV.COLUMNS);
            terminfo.lines = Number.isFinite(lines) && lines > 0 ? lines : 24;
            terminfo.columns = Number.isFinite(columns) && columns > 0 ? columns : 80;
            return terminfo.tgetent(null, string(services, name));
        },
        tgetflag(services, id) { ++calls.tgetflag; return terminfo.tgetflag(string(services, id)); },
        tgetnum(services, id) { ++calls.tgetnum; return terminfo.tgetnum(string(services, id)); },
        tgetstr(services, id, area) {
            ++calls.tgetstr;
            const value = terminfo.tgetstr(string(services, id));
            if (value === null) return 0;
            if (Number(area)) {
                let view = new DataView(services.heap().buffer);
                const pointer = Number(view.getBigUint64(Number(area), true));
                if (pointer) {
                    writeString(services, pointer, value);
                    view = new DataView(services.heap().buffer);
                    view.setBigUint64(Number(area), BigInt(pointer + value.length + 1), true);
                    return pointer;
                }
            }
            if (!capabilityPointers.has(value)) {
                const pointer = services.malloc(value.length + 1);
                if (!pointer) throw new Error('JS terminfo capability allocation failed');
                writeString(services, pointer, value);
                capabilityPointers.set(value, pointer);
            }
            return capabilityPointers.get(value);
        },
        tparm(services, format, parameters) {
            ++calls.tparm;
            const view = new DataView(services.heap().buffer);
            const args = Array.from({ length: 9 }, (_, i) => Number(BigInt.asIntN(32,
                view.getBigInt64(Number(parameters) + i * 8, true))));
            return result(services, terminfo.tparm(string(services, format), ...args));
        },
        tgoto(services, format, column, row) {
            ++calls.tgoto;
            return result(services, terminfo.tgoto(string(services, format), column, row));
        },
        tputs(services, value, lines, callback) {
            ++calls.tputs;
            return terminfo.tputs(string(services, value), lines, byte => services.emit(callback, byte));
        },
        compressFile(services, filename, compressed, unpack) {
            ++calls[unpack ? 'decompress' : 'compress'];
            const plain = string(services, filename), packed = string(services, compressed);
            const source = unpack ? packed : plain, destination = unpack ? plain : packed;
            let input, output;
            try {
                // Preserve the existing service's open/read source before
                // destination creation; file cleanup/prompts remain in files.c.
                input = services.FS.open(source, 'r');
                output = services.FS.open(destination, 'w', 0o666);
                const size = services.FS.fstat(input.fd).size;
                const bytes = new Uint8Array(size);
                let position = 0;
                while (position < size) {
                    const count = services.FS.read(input, bytes, position, size - position, position);
                    if (!count) throw new Error('unexpected end of input');
                    position += count;
                }
                const encoded = unpack ? decompressUnixZ(bytes) : compressUnixZ(bytes);
                if (encoded.bytes.length && services.FS.write(output, encoded.bytes, 0, encoded.bytes.length, 0) !== encoded.bytes.length)
                    throw new Error('incomplete output write');
                return encoded.status;
            } catch (error) {
                services.printErr(`${source}: ${error.message || error}`);
                return 1;
            } finally {
                if (output) services.FS.close(output);
                if (input) services.FS.close(input);
            }
        },
    };
}
