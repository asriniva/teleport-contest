// Actual configured C snprintf, compared with ordinary-JS C-memory formatting.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import { fileURLToPath, pathToFileURL } from 'node:url';
import { spawnSync } from 'node:child_process';
import { CMemory } from '../js/services/c-memory.js';
import { createCStdlib } from '../js/services/c-stdlib.js';
const root = fileURLToPath(new URL('../', import.meta.url));
const work = path.join(root, '.cache/js-c-float'); fs.mkdirSync(work, { recursive: true });
const source = path.join(work, 'probe.c'), modulePath = path.join(work, 'probe.mjs');
fs.writeFileSync(source, `#include <stdio.h>
#include <stdint.h>
#include <string.h>
static unsigned char output[8192];
const unsigned char *probe_output(void){return output;}
int probe(uint64_t bits,const char*format,int size,int star,int width,int precision){
 union{uint64_t u;double d;}v={.u=bits};memset(output,0xa5,sizeof output);
 return star?snprintf((char*)output+8,size,format,width,precision,v.d):snprintf((char*)output+8,size,format,v.d);
}`);
const build = spawnSync(path.join(root, '.cache/emsdk/upstream/emscripten/emcc'), [
  '-O2', source, '--no-entry', '-sMODULARIZE=1', '-sEXPORT_ES6=1', '-sENVIRONMENT=node',
  '-sEXPORTED_FUNCTIONS=_probe,_probe_output,_malloc,_free', '-sEXPORTED_RUNTIME_METHODS=HEAPU8', '-o', modulePath,
], { encoding: 'utf8', timeout: 60000 });
assert.equal(build.status, 0, build.error || build.stderr);
const factory = (await import(pathToFileURL(modulePath))).default;
const reference = await factory(), memory = new CMemory(), libc = createCStdlib(memory);
const numberBits = new DataView(new ArrayBuffer(8));
const asBits = number => { numberBits.setFloat64(0, number, true); return numberBits.getBigUint64(0, true); };
let cases = 0;
function compare(bits, format, size = 1024, width = null, precision = null) {
  numberBits.setBigUint64(0, bits, true); const number = numberBits.getFloat64(0, true);
  const encoded = Buffer.from(format + '\0'), nativeFormat = reference._malloc(encoded.length);
  reference.HEAPU8.set(encoded, nativeFormat);
  try {
    const expected = reference._probe(bits, nativeFormat, size, Number(width !== null), width ?? 0, precision ?? 0);
    memory.withScope(scope => {
      const guard = scope.alloc(size + 16), destination = guard + 8;
      memory.HEAPU8.fill(0xa5, guard, guard + size + 16);
      const result = libc.snprintf(size ? destination : 0, size, format, ...(width === null ? [number] : [width, precision, number]));
      assert.equal(result, expected, format + '/' + bits.toString(16));
      const nativeOutput = reference._probe_output();
      assert.deepEqual(memory.readBytes(guard, size + 16), reference.HEAPU8.slice(nativeOutput, nativeOutput + size + 16), format + '/' + bits.toString(16));
    });
  } finally { reference._free(nativeFormat); }
  cases++;
}
const values = [0, -0, 1, -1, 1.5, 2.5, 9.999999999999999, 1e-4, 1e-5, 1e20, 1e300,
  Number.MAX_VALUE, Number.MIN_VALUE, Infinity, -Infinity].map(asBits);
values.push(0x7ff8000000000000n, 0xfff8000000000000n, 0x7ff0000000000001n, 0x41fc4c57c6afc5ecn);
for (const bits of values) for (const code of ['a','A','e','E','f','F','g','G'])
  for (const flags of ['%', '%+020.6', '%-#20.0', '% .12', '%#.14']) compare(bits, flags + code);
for (const code of ['a','e','f','g']) for (const width of [-32, 0, 32]) for (const precision of [-1, 0, 6, 12, 50])
  for (const size of [0,1,2,8,128]) compare(asBits(-1.23456789012345), '%#0*.*' + code, size, width, precision);
let seed = 0x2a7e49b1;
const random = () => { seed ^= seed << 13; seed ^= seed >>> 17; seed ^= seed << 5; return seed >>> 0; };
for (let i = 0; i < 1000; i++) {
  const bits = BigInt(random()) << 32n | BigInt(random());
  const code = ['a','A','e','E','f','F','g','G'][random() % 8];
  compare(bits, '%' + ['','+','#','-',' ','0'][random() % 6] + '40.' + [0,1,6,11,12,13,17,50,99][random() % 9] + code, [0,1,16,1024][random() % 4]);
}
assert.throws(() => libc.format('%Lf', 1), /Long-double/);
console.log(`PASS: ${cases} actual C snprintf comparisons; IEEE extremes/subnormals/NaNs, fixed/scientific/general/hex, musl precision12, flags/stars, capacity0/truncation and byte guards.`);
