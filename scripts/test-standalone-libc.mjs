import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import {spawnSync} from 'node:child_process';
import {createStandaloneEnvironment} from '../js/standalone/environment.js';
import {VFSError} from '../js/services/c-vfs.js';
const root=process.env.STANDALONE_REFERENCE_ROOT;if(!root)throw new Error('Missing STANDALONE_REFERENCE_ROOT');
const scratch=path.resolve('.cache/standalone-libc');fs.mkdirSync(scratch,{recursive:true});
// musl's atomic header supplies this mathematical trailing-zero operation.
// Override only that header for a host-native build of the unchanged sort body.
fs.writeFileSync(path.join(scratch,'atomic.h'),'#include <limits.h>\nstatic inline int a_ctz_l(unsigned long x){return x?__builtin_ctzl(x):CHAR_BIT*sizeof(x);}\n');
const built=spawnSync(process.env.CC||root+'/.cache/wasm64-build/host-cc',['-O2','-I'+scratch,'-Dweak_alias(x,y)=',
    root+'/.cache/emsdk/upstream/emscripten/system/lib/libc/musl/src/stdlib/qsort.c',
    'scripts/standalone-libc-probe.c','-o',path.join(scratch,'probe')],{encoding:'utf8'});
assert.equal(built.status,0,built.stderr);
const runtime=createStandaloneEnvironment(),{memory,services:s}=runtime;
let seed=1234;const next=()=>seed=(Math.imul(seed,1664525)+1013904223)>>>0;
const cases=[];
for(const n of [0,1,2,3,7,8,15,32,64,129,500])for(let k=0;k<12;k++)cases.push(Array.from({length:n},(_,i)=>k===0?i:k===1?n-i:k===2?1:(next()%23)-11));
const native=spawnSync(path.join(scratch,'probe'),[],{input:cases.map(v=>[v.length,...v].join(' ')).join('\n'),encoding:'utf8',maxBuffer:16*1024*1024});
assert.equal(native.status,0,native.stderr);const lines=native.stdout.trim().split('\n');assert.equal(lines.length,cases.length);
for(const [index,values]of cases.entries()) {
    const at=memory.malloc(Math.max(1,values.length)*4),trace=[];values.forEach((v,i)=>memory.view.setInt32(at+i*4,v,true));
    s.qsort(at,values.length,4,(a,b)=>{trace.push(`${(a-at)/4},${(b-at)/4};`);return Math.sign(memory.view.getInt32(a,true)-memory.view.getInt32(b,true));});
    const result=Array.from({length:values.length},(_,i)=>memory.view.getInt32(at+i*4,true));
    assert.equal(trace.join('')+'|'+result.map(v=>v+',').join(''),lines[index],`sort case ${index}`);memory.free(at);
}
runtime.enableHacklib(JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')).hacklib);
assert.equal(runtime.call('hacklib','sgn',-50),-1);
assert.equal(runtime.call('hacklib','distmin',1,1,7,4),6);
const str=memory.cstring('  alpha   beta  ');runtime.call('hacklib','mungspaces',str);assert.equal(memory.readString(str),'alpha beta');
const arr=memory.calloc(5,8),items=[[2,0],[1,1],[2,2],[0,3],[1,4]];
items.forEach(([key,id],i)=>{memory.view.setInt32(arr+i*8,key,true);memory.view.setInt32(arr+i*8+4,id,true);});
const cmp=runtime.functions.functionPointer((a,b)=>Math.sign(memory.view.getInt32(Number(a),true)-memory.view.getInt32(Number(b),true)),'ipp');
runtime.call('hacklib','nh_deterministic_qsort',arr,5n,8n,cmp);
assert.deepEqual(Array.from({length:5},(_,i)=>memory.view.getInt32(arr+i*8+4,true)),[3,1,4,0,2]);
const out=memory.calloc(1,64),other=memory.calloc(1,64),end=memory.calloc(1,8);
assert.equal(s.sscanf(' -17 0xff word!','%d %x %4s%n',out,other,other+8,end),3);
assert.equal(memory.view.getInt32(out,true),-17);assert.equal(memory.view.getInt32(other,true),255);assert.equal(memory.readString(other+8),'word');assert.equal(memory.view.getInt32(end,true),14);
assert.equal(s.sscanf('abc123','%3[a-z]%d',out,other),2);assert.equal(memory.readString(out),'abc');assert.equal(memory.view.getInt32(other,true),123);
assert.equal(s.sscanf('','%d',out),-1);assert.equal(s.sscanf('x','%d',out),0);
const scan=spawnSync(path.join(scratch,'probe'),['scan'],{encoding:'utf8'});assert.equal(scan.status,0,scan.stderr);
const actual=[];
let result=s.sscanf(' -17 0xff word!','%d %x %4s%n',out,other,other+8,end);
actual.push([result,memory.view.getInt32(out,true),memory.view.getUint32(other,true),memory.readString(other+8),memory.view.getInt32(end,true)].join(','));
result=s.sscanf('abc123','%3[a-z]%d%n',out,other,end);actual.push([result,memory.readString(out),memory.view.getInt32(other,true),memory.view.getInt32(end,true)].join(','));
result=s.sscanf('-9223372036854775808 18446744073709551615','%ld %lu',out,other);actual.push([result,memory.view.getBigInt64(out,true),memory.view.getBigUint64(other,true)].join(','));
memory.view.setInt32(out,19,true);actual.push([s.sscanf('','%d',out),memory.view.getInt32(out,true)].join(','));actual.push([s.sscanf('x','%d',out),memory.view.getInt32(out,true)].join(','));
assert.deepEqual(actual,scan.stdout.trim().split('\n'));
assert.equal(s.strcasecmp('\xc0','\xe0'),-32);assert.equal(s.strcasecmp('AbC','aBc'),0);
const copyOracle=spawnSync(path.join(scratch,'probe'),['bytes'],{encoding:'utf8'});assert.equal(copyOracle.status,0,copyOracle.stderr);
const copyOut=memory.malloc(16),copySource=s.literal('ab'),copyActual=[];
for(const n of [0,1,2,3,7,16]){memory.memset(copyOut,0xa5,16);const result=s.strncpy(copyOut,copySource,BigInt(n));copyActual.push([n,Number(result===copyOut),Buffer.from(memory.readBytes(copyOut,16)).toString('hex')].join(':'));}
assert.deepEqual(copyActual,copyOracle.stdout.trim().split('\n'),'C size_t64 bounded copying and zero padding');
const creatOracle=spawnSync(path.join(scratch,'probe'),['creat',path.join(scratch,'creat-native.bin')],{encoding:'utf8'});assert.equal(creatOracle.status,0,creatOracle.stderr);
const files=createStandaloneEnvironment(),io=files.enableStdio(),payload=files.memory.cstring('abc');let fd=io.creat('/creat',0o640);assert.ok(fd>=3);assert.equal(io.write(fd,payload,3),3);assert.equal(io.close(fd),0);
fd=io.creat('/creat',0o600);const stat=files.filesystem.fstat(fd),badRead=io.read(fd,payload,1),creatActual=[[Number(fd>=0),stat.size,(stat.mode&0o777).toString(8),Number(badRead===-1&&files.libc.errno===new VFSError('EBADF').errno)].join(',')];assert.equal(io.close(fd),0);
const absent=io.creat('/creat.missing/file',0o600);creatActual.push([absent,Number(files.libc.errno===new VFSError('ENOENT').errno)].join(','));assert.deepEqual(creatActual,creatOracle.stdout.trim().split('\n'),'C creat truncation, permissions, write-only descriptor and missing-parent failure');
console.log(`PASS: ${cases.length} exact original-musl qsort output/comparator traces, stable NetHack sorting, hacklib utilities bounded scanner contracts and6 C size_t64 strncpy cases plus C creat file contracts.`);
