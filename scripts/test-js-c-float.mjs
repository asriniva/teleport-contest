// Actual macOS snprintf default plus explicit configured-musl alternate oracle.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import { fileURLToPath, pathToFileURL } from 'node:url';
import { spawnSync } from 'node:child_process';
import { CMemory } from '../js/c-runtime/heap.js';
import { createCStdlib } from '../js/c-runtime/stdlib.js';
const root = fileURLToPath(new URL('../', import.meta.url));
if(Number(process.versions.node.split('.')[0])<24){const result=spawnSync(path.join(root,'.cache/emsdk/node/24.19.0_64bit/bin/node'),[fileURLToPath(import.meta.url)],{stdio:'inherit'});process.exit(result.status??1);}
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
}
#ifdef PROBE_MAIN
int main(void){unsigned long long bits;char format[2048],encodedFormat[4096];int size,star,width,precision;
 while(scanf("%llx %4095s %d %d %d %d",&bits,encodedFormat,&size,&star,&width,&precision)==6){
 int len=strlen(encodedFormat)/2;for(int i=0;i<len;i++){unsigned byte;sscanf(encodedFormat+2*i,"%2x",&byte);format[i]=byte;}format[len]=0;
 int result=probe(bits,format,size,star,width,precision);printf("%d:",result);
 for(int i=0;i<size+16;i++)printf("%02x",output[i]);puts("");}return 0;}
#endif
`);
const build = spawnSync(path.join(root, '.cache/emsdk/upstream/emscripten/emcc'), [
  '-O2', '-sMEMORY64=1', source, '--no-entry', '-sMODULARIZE=1', '-sEXPORT_ES6=1', '-sENVIRONMENT=node',
  '-sEXPORTED_FUNCTIONS=_probe,_probe_output,_malloc,_free', '-sEXPORTED_RUNTIME_METHODS=HEAPU8', '-o', modulePath,
], { encoding: 'utf8', timeout: 60000 });
assert.equal(build.status, 0, build.error || build.stderr);
const factory = (await import(pathToFileURL(modulePath))).default;
const reference = await factory(), memory = new CMemory(), libc = createCStdlib(memory), musl = createCStdlib(memory,{floatPolicy:'musl'});
const numberBits = new DataView(new ArrayBuffer(8));
const asBits = number => { numberBits.setFloat64(0, number, true); return numberBits.getBigUint64(0, true); };
const corpus=[];let cases=0;
function compare(bits,format,size=1024,width=null,precision=null){corpus.push({bits,format,size,width,precision});}
const values = [0, -0, 1, -1, 1.5, 2.5, 9.999999999999999, 1e-4, 1e-5, 1e20, 1e300,
  Number.MAX_VALUE, Number.MIN_VALUE, Infinity, -Infinity].map(asBits);
values.push(0x7ff8000000000000n, 0xfff8000000000000n, 0x7ff0000000000001n, 0x41fc4c57c6afc5ecn);
for (const bits of values) for (const code of ['a','A','e','E','f','F','g','G'])
  for (const flags of ['%', '%+020.6', '%-#20.0', '% .12', '%#.14']) compare(bits, flags + code);
for (const code of ['a','e','f','g']) for (const width of [-32, 0, 32]) for (const precision of [-1, 0, 6, 12, 50])
  for (const size of [0,1,2,8,128]) compare(asBits(-1.23456789012345), '%#0*.*' + code, size, width, precision);
let seed = 0x2a7e49b1;
const random = () => { seed ^= seed << 13; seed ^= seed >>> 17; seed ^= seed << 5; return seed >>> 0; };
for (let i = 0; i < 10000; i++) {
  const bits = BigInt(random()) << 32n | BigInt(random());
  const code = ['a','A','e','E','f','F','g','G'][random() % 8];
  compare(bits, '%' + ['','+','#','-',' ','0'][random() % 6] + '40.' + [0,1,6,11,12,13,17,50,99][random() % 9] + code, [0,1,16,1024][random() % 4]);
}
// All first-discarded/next-discarded nibble combinations at every rounded
// hex precision: specifically exercises Apple's unusual halfway rule.
for(let precision=0;precision<13;precision++)for(let nibble=0;nibble<16;nibble++)for(let next=0;next<16;next++){
 const shift=BigInt(48-precision*4),fraction=shift>=0n?BigInt(nibble)<<shift:0n;
 const rest=shift>=4n?BigInt(next)<<(shift-4n):0n;
 compare(0x3ff0000000000000n|fraction|rest,'%+.'+precision+'a');
}
const nativePath=path.join(work,'probe-native');
const compiler=process.env.CC||path.join(root,'.cache/wasm64-build/host-cc');
const hostBuild=spawnSync(compiler,['-O2','-DPROBE_MAIN',source,'-o',nativePath],{encoding:'utf8',timeout:60000});assert.equal(hostBuild.status,0,hostBuild.error||hostBuild.stderr);
const host=spawnSync(nativePath,[],{input:corpus.map(c=>[c.bits.toString(16),Buffer.from(c.format).toString('hex'),c.size,Number(c.width!==null),c.width??0,c.precision??0].join(' ')).join('\n')+'\n',encoding:'utf8',maxBuffer:100000000,timeout:60000});assert.equal(host.status,0,host.error||host.stderr);
const nativeLines=host.stdout.trimEnd().split('\n');assert.equal(nativeLines.length,corpus.length);const differences=[];
for(let i=0;i<corpus.length;i++){
 const {bits,format,size,width,precision}=corpus[i];numberBits.setBigUint64(0,bits,true);const number=numberBits.getFloat64(0,true),nativeResult=nativeLines[i].split(':'),nativeBytes=Buffer.from(nativeResult[1],'hex');
 const encoded=Buffer.from(format+'\0'),nativeFormat=reference._malloc(BigInt(encoded.length));reference.HEAPU8.set(encoded,Number(nativeFormat));
 try{
 const wasmResult=reference._probe(bits,BigInt(nativeFormat),size,Number(width!==null),width??0,precision??0),wasmOutput=Number(reference._probe_output()),wasmBytes=reference.HEAPU8.slice(wasmOutput,wasmOutput+size+16);
 for(const [api,expected,bytes,policy]of[[libc,Number(nativeResult[0]),nativeBytes,'darwin'],[musl,wasmResult,wasmBytes,'musl']])memory.withScope(scope=>{
 const guard=scope.alloc(size+16),destination=guard+8;memory.HEAPU8.fill(0xa5,guard,guard+size+16);
 const result=api.snprintf(size?destination:0,size,format,...(width===null?[number]:[width,precision,number]));
 assert.equal(result,expected,policy+' '+format+'/'+bits.toString(16));assert.deepEqual(memory.readBytes(guard,size+16),new Uint8Array(bytes),policy+' '+format+'/'+bits.toString(16));
 });
 if(wasmResult!==Number(nativeResult[0])||!Buffer.from(wasmBytes).equals(nativeBytes))differences.push({bits:bits.toString(16),format,size,width,precision,native:nativeResult[1],configured:Buffer.from(wasmBytes).toString('hex')});
 }finally{reference._free(nativeFormat);}cases++;
}
fs.writeFileSync(path.join(work,'platform-differences.json'),JSON.stringify(differences,null,2)+'\n');
assert.throws(() => libc.format('%Lf', 1), /Long-double/);
console.log(`PASS: ${cases} actual macOS C snprintf comparisons and ${cases} explicit configured-musl comparisons; ${differences.length} measured platform differences. IEEE extremes/subnormals/NaNs, decimal/hex, all discarded-nibble pairs, flags/stars, truncation and guards.`);
