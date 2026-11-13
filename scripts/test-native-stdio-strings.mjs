// The unchanged configured C fwrite/FILE machinery is the byte-write oracle.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import {resolve} from 'node:path';
import {pathToFileURL} from 'node:url';
import {createStandaloneEnvironment} from '../js/nethack/environment.js';
import {CMemory} from '../js/c-runtime/heap.js';
const directory=resolve(process.env.STANDALONE_SDK_ORACLE??'../teleport-contest/.cache/standalone-sdk-boundary-v5');
const {default:factory}=await import(pathToFileURL(directory+'/reference.mjs')),c=await factory();
let checks=0,cases=0;
const eq=(a,b,label)=>{assert.deepEqual(a,b,label);checks++;};
const literal=text=>{const bytes=CMemory.byteString(text+'\0'),p=c._malloc(BigInt(bytes.length));c.HEAPU8.set(bytes,Number(p));return BigInt(p);};
for(const mode of [0,1,2])for(const size of [0,8,9,16,1024]){
 const e=createStandaloneEnvironment(),io=e.enableStdio(),name='/native-text-'+cases++,path=literal(name),access=literal('w+'),cf=BigInt(c._fopen(path,access)),jf=io.fopen(name,'w+'),cp=BigInt(c._malloc(BigInt(Math.max(size,1)))),jp=e.memory.malloc(Math.max(size,1));
 c.HEAPU8.fill(0xa5,Number(cp),Number(cp)+Math.max(size,1));e.memory.memset(jp,0xa5,Math.max(size,1));
 eq(io.setvbuf(jf,size?jp:0,mode,size),c._setvbuf(cf,size?cp:0n,mode,BigInt(size)),'setvbuf');
 function compare(label){for(const method of ['__fbufsize','__fpending','ftell','feof','ferror'])eq(Number(io[method](jf)),Number(c['_'+method](cf)),label+' '+method);eq([...e.filesystem.readFile(name)],[...c.FS.readFile(name)],label+' file bytes');if(size)eq([...e.memory.readBytes(jp,size)],[...c.HEAPU8.slice(Number(cp),Number(cp)+size)],label+' caller buffer');}
 for(const value of ['', 'x','first\nsecond\ntail','\0after','prefix\0after','\xe9\xff\n','z'.repeat(1025),'\n','tail']){
  const bytes=CMemory.byteString(value),zero=bytes.indexOf(0),n=zero<0?bytes.length:zero,p=BigInt(c._malloc(BigInt(Math.max(1,bytes.length))));c.HEAPU8.set(bytes,Number(p));
  c._sdk_errno(137);e.libc.errno=137;
  const expected=Number(c._fwrite(p,1n,BigInt(n),cf)),actual=io.fputs(value,jf);eq(actual,expected===n?0:-1,'native string return');eq(e.libc.errno,c._sdk_errno(-1),'native string errno');compare('string '+JSON.stringify(value.slice(0,18)));c._free(p);
 }
 // A defined update-stream transition positions after buffered input/pushback.
 eq(io.fflush(jf),c._fflush(cf),'flush');eq(io.fseek(jf,0,0),c._fseek(cf,0n,0),'seek');
 for(let i=0;i<3;i++)eq(io.fgetc(jf),c._fgetc(cf),'read before write');eq(io.ungetc(88,jf),c._ungetc(88,cf),'pushback');eq(io.fseek(jf,0,1),c._fseek(cf,0n,1),'position after pushback');
 const suffix=literal('replacement');eq(io.fputs('replacement',jf),Number(c._fwrite(suffix,1n,11n,cf))===11?0:-1,'write after pushback');compare('after pushback');
 eq(io.fflush(jf),c._fflush(cf),'final flush');compare('flushed');eq(io.fclose(jf),c._fclose(cf),'close');
 c._free(path);c._free(access);c._free(cp);c._free(suffix);e.memory.free(jp);
}
// Read-only, append and closed-descriptor errors use the same original C FILEs.
for(const accessMode of ['r','a+'])for(const mode of [0,1,2]){
 const e=createStandaloneEnvironment(),io=e.enableStdio(),name='/native-errors-'+cases++,seed=CMemory.byteString('seed\n');e.filesystem.writeFile(name,seed);c.FS.writeFile(name,seed);
 const path=literal(name),access=literal(accessMode),cf=BigInt(c._fopen(path,access)),jf=io.fopen(name,accessMode);eq(io.setvbuf(jf,0,mode,0),c._setvbuf(cf,0n,mode,0n),'error setvbuf');
 const input=literal('append\n');c._sdk_errno(137);e.libc.errno=137;const n=Number(c._fwrite(input,1n,7n,cf));eq(io.fputs('append\n',jf),n===7?0:-1,'read-only/append return');eq(io.ferror(jf),c._ferror(cf),'read-only/append error');eq(e.libc.errno,c._sdk_errno(-1),'read-only/append errno');eq(Number(io.ftell(jf)),Number(c._ftell(cf)),'read-only/append offset');eq(io.fflush(jf),c._fflush(cf),'read-only/append flush');eq([...e.filesystem.readFile(name)],[...c.FS.readFile(name)],'read-only/append bytes');eq(io.fclose(jf),c._fclose(cf),'error close');c._free(path);c._free(access);c._free(input);
}
{
 const e=createStandaloneEnvironment(),io=e.enableStdio(),name='/native-closed-fd',path=literal(name),access=literal('w+'),cf=BigInt(c._fopen(path,access)),jf=io.fopen(name,'w+'),input=literal('closed');cases++;
 eq(io.setvbuf(jf,0,2,0),c._setvbuf(cf,0n,2,0n),'closed-fd buffer');eq(io.close(io.fileno(jf)),c._close(c._fileno(cf)),'close descriptor');c._sdk_errno(137);e.libc.errno=137;const n=Number(c._fwrite(input,1n,6n,cf));eq(io.fputs('closed',jf),n===6?0:-1,'closed-fd return');eq(io.ferror(jf),c._ferror(cf),'closed-fd error');eq(e.libc.errno,c._sdk_errno(-1),'closed-fd errno');eq(io.fclose(jf),c._fclose(cf),'closed-fd fclose');c._free(path);c._free(access);c._free(input);
}
// Named reopen replaces FILE append flags; unnamed reopen keeps them.
{
 const e=createStandaloneEnvironment(),io=e.enableStdio(),name='/native-reopen-append',path=literal(name),appendMode=literal('a+'),writeMode=literal('w+'),cf=BigInt(c._fopen(path,appendMode)),jf=io.fopen(name,'a+'),text=literal('data');cases++;
 eq(io.fputs('data',jf),Number(c._fwrite(text,1n,4n,cf))===4?0:-1,'append data');eq(io.fflush(jf),c._fflush(cf),'append flush');eq(io.fseek(jf,0,0),c._fseek(cf,0n,0),'append rewind');
 eq(io.fputs('data',jf),Number(c._fwrite(text,1n,4n,cf))===4?0:-1,'append after rewind');eq(Number(io.ftell(jf)),Number(c._ftell(cf)),'pending append seeks end');eq(io.fflush(jf),c._fflush(cf),'append second flush');
 eq(Boolean(io.freopen(name,'w+',jf)),Boolean(c._freopen(path,writeMode,cf)),'named reopen');eq(io.fputs('data',jf),Number(c._fwrite(text,1n,4n,cf))===4?0:-1,'reopened data');eq(io.fflush(jf),c._fflush(cf),'reopened flush');eq(io.fseek(jf,0,0),c._fseek(cf,0n,0),'reopened rewind');
 eq(Boolean(io.freopen(0,'a+',jf)),Boolean(c._freopen(0n,appendMode,cf)),'unnamed reopen');eq(io.fputs('data',jf),Number(c._fwrite(text,1n,4n,cf))===4?0:-1,'unnamed data');eq(Number(io.ftell(jf)),Number(c._ftell(cf)),'unnamed FILE flags retained');eq(io.fflush(jf),c._fflush(cf),'unnamed flush');eq([...e.filesystem.readFile(name)],[...c.FS.readFile(name)],'reopened file bytes');eq(io.fclose(jf),c._fclose(cf),'reopened close');c._free(path);c._free(appendMode);c._free(writeMode);c._free(text);
}
// Empty/encoding/error contracts and malloc-free native byte paths.
for(const buffered of [false,true]){
 let inputGrowth=0;const queue=[0,255,65,10],chunks=[],e=createStandaloneEnvironment(),io=e.enableStdio({readStdin:n=>{if(!inputGrowth++){assert.ok(e.memory.grow(e.memory.buffer.byteLength+1));}return Uint8Array.from(queue.splice(0,n));},stdout:bytes=>chunks.push([...bytes])});
 if(!buffered)io.setvbuf(io.stdin,0,2,0);io.setvbuf(io.stdout,0,2,0);
 if(buffered)eq(io.getchar(),0,'buffered warmup');
 const original=e.memory.malloc;let allocations=0;e.memory.malloc=function(...args){allocations++;return original.apply(this,args);};
 try{if(!buffered)eq(io.getchar(),0,'unbuffered zero');for(const byte of [255,65,10])eq(io.getchar(),byte,'native read');eq(io.getchar(),-1,'native EOF');eq(io.feof(io.stdin),1,'EOF flag');eq(io.ungetc(7,io.stdin),7,'unget after EOF');eq(io.getchar(),7,'native pushback');eq(io.putchar(255),255,'native output byte');eq(io.puts('line'),10,'native puts');eq(io.printf('%s:%d\n','count',42),9,'native formatted output');eq(allocations,0,'no C heap scratch allocations');eq(chunks.flat(),[255,...CMemory.byteString('line\ncount:42\n')],'native captured bytes');}
 finally{e.memory.malloc=original;}
 assert.throws(()=>io.fputs('prefix\0\u0100',io.stdout),/explicit UTF-8/);checks++;
 const old=e.memory.buffer;io.fputs('x',io.stdout);e.memory.grow(old.byteLength+1);assert.notEqual(e.memory.buffer,old);io.fputs('y\n',io.stdout);checks++;
}
const report={passed:true,cases,checks,originalCByteWrites:true,encodingAndNul:true,bufferAliases:true,inputPushbackAndEof:true,mallocFreeNativeBytes:true};
fs.mkdirSync('.cache/native-stdio-strings',{recursive:true});fs.writeFileSync('.cache/native-stdio-strings/evidence.json',JSON.stringify(report,null,2)+'\n');console.log(JSON.stringify(report));
