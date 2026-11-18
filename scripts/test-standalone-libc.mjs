import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import {spawnSync} from 'node:child_process';
import {createStandaloneEnvironment} from '../js/nethack/environment.js';
import {createStandaloneProgram} from '../js/nethack/program.js';
import {C_ERRNO} from '../js/c-runtime/stdlib.js';
import {VFSError,VFS_ERRNO} from '../js/c-runtime/vfs.js';
const root=process.env.STANDALONE_REFERENCE_ROOT;if(!root)throw new Error('Missing STANDALONE_REFERENCE_ROOT');
const scratch=path.resolve('.cache/standalone-libc');fs.mkdirSync(scratch,{recursive:true});
// musl's atomic header supplies this mathematical trailing-zero operation.
// Override only that header for a host-native build of the unchanged sort body.
fs.writeFileSync(path.join(scratch,'atomic.h'),'#include <limits.h>\nstatic inline int a_ctz_l(unsigned long x){return x?__builtin_ctzl(x):CHAR_BIT*sizeof(x);}\n');
const built=spawnSync(process.env.CC||root+'/.cache/wasm64-build/host-cc',['-O2','-I'+scratch,'-Dweak_alias(x,y)=','-Ddifftime=standalone_probe_difftime',
    root+'/.cache/emsdk/upstream/emscripten/system/lib/libc/musl/src/stdlib/qsort.c',
    root+'/.cache/emsdk/upstream/emscripten/system/lib/libc/musl/src/time/difftime.c',
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

const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json'));
const {environment:game,stdio:gameStdio}=createStandaloneProgram({layouts,readKey(){throw Error('Unexpected input');}});
const discoverySort=game.enableDiscoveries(layouts).services.qsort;
const discoveryRows=Array.from({length:64},(_,i)=>game.services.literal(
    (i%2===0?'* ':'  ')+String.fromCharCode(97+i%3).repeat(2)+' '+(i%4<2?'x':'X')));
const discoveryPointers=game.memory.calloc(discoveryRows.length,8);
discoveryRows.forEach((pointer,i)=>game.memory.view.setBigUint64(discoveryPointers+i*8,BigInt(pointer),true));
discoverySort(discoveryPointers,discoveryRows.length,8);
assert.deepEqual(Array.from({length:discoveryRows.length},(_,i)=>Number(
    game.memory.view.getBigUint64(discoveryPointers+i*8,true))),
    [0,1,2].flatMap(group=>discoveryRows.filter((_,i)=>i%3===group)));

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
const signedInputs=['9223372036854775807!', '9223372036854775808!', '18446744073709551616!',
    '-9223372036854775808!', '-9223372036854775809!', '0x8000000000000000!', '-0x8000000000000001!'];
const signedOracle=spawnSync(path.join(scratch,'probe'),['signed-scans',...signedInputs],{encoding:'utf8'});
assert.equal(signedOracle.status,0,signedOracle.stderr);
const signedExpected=signedOracle.stdout.trim().split('\n');
const stream=runtime.enableStdio();
const scanPath=memory.cstring('/signed-scan');
const scanFormat='%li%n';
const scannedLong=assigned=>[assigned,memory.view.getBigInt64(out,true),memory.view.getInt32(end,true),
    Number(runtime.libc.errno===C_ERRNO.ERANGE)].join(',');
for (const [i,input] of signedInputs.entries()) {
    runtime.libc.errno=0;
    assert.equal(scannedLong(s.sscanf(input,scanFormat,out,end)),signedExpected[i],input);
    runtime.filesystem.writeFile('/signed-scan',input);
    const file=stream.fopen(scanPath,'r');
    assert.ok(file);
    runtime.libc.errno=0;
    assert.equal(scannedLong(stream.fscanf(file,scanFormat,out,end)),signedExpected[i],input);
    assert.equal(stream.fgetc(file),33);
    assert.equal(stream.fclose(file),0);
}
const edgeActual=[];
const plainPath='screen-path-plain',markedPath='\uFEFF'+plainPath;
game.filesystem.writeFile('/'+plainPath,'A');
game.filesystem.writeFile('/'+markedPath,'B');
game.libc.errno=0;
const trailingFile=gameStdio.fopen(plainPath+'/','r');
edgeActual.push([Number(Boolean(trailingFile)),Number(game.libc.errno===VFS_ERRNO.ENOTDIR)].join(' '));
const markedFile=gameStdio.fopen(game.memory.cstring(new TextEncoder().encode(markedPath)),'r');
assert.ok(markedFile);
edgeActual.push(String(gameStdio.fgetc(markedFile)));
assert.equal(gameStdio.fclose(markedFile),0);
const strerror=game.resolve('strerror');
for (const code of [0,VFS_ERRNO.EIO,VFS_ERRNO.EMFILE,VFS_ERRNO.ENAMETOOLONG,VFS_ERRNO.ENOMEM,
    VFS_ERRNO.ENOTSUP,59,C_ERRNO.ERANGE,VFS_ERRNO.ESPIPE])
    edgeActual.push(game.memory.readString(Number(strerror(code))));
game.libc.errno=VFS_ERRNO.ENOTSUP;
game.resolve('perror')(game.services.literal('test'));
gameStdio.fflush(gameStdio.stderr);
assert.equal(new TextDecoder().decode(gameStdio.captured(2)),'test: Operation not supported\n');
memory.view.setInt32(out,88,true);
memory.view.setInt32(end,-1,true);
let edgeResult=s.sscanf('0xg','%i%n',out,end);
edgeActual.push([edgeResult,memory.view.getInt32(out,true),memory.view.getInt32(end,true)].join(' '));
runtime.libc.errno=0;
edgeResult=s.sscanf('+','%d%n',out,end);
edgeActual.push([edgeResult,Number(runtime.libc.errno!==0)].join(' '));
memory.memset(out,88,2);
memory.view.setInt32(end,-1,true);
edgeResult=s.sscanf('a','%2c%n',out,end);
edgeActual.push([edgeResult,memory.HEAPU8[out],memory.HEAPU8[out+1],memory.view.getInt32(end,true)].join(' '));
if (process.platform==='darwin') {
    const edgeOracle=spawnSync(path.join(scratch,'probe'),['screen-edges',scratch],{encoding:'utf8'});
    assert.equal(edgeOracle.status,0,edgeOracle.stderr);
    assert.deepEqual(edgeActual,edgeOracle.stdout.trim().split('\n'));
}
runtime.filesystem.writeFile('/signed-scan','0xg');
const hexFile=stream.fopen(scanPath,'r');
assert.ok(hexFile);
assert.equal(stream.fscanf(hexFile,'%i',out),1);
assert.equal(memory.view.getInt32(out,true),0);
assert.equal(stream.fgetc(hexFile),120);
assert.equal(stream.fgetc(hexFile),103);
assert.equal(stream.fclose(hexFile),0);
assert.equal(s.strcasecmp('\xc0','\xe0'),-32);assert.equal(s.strcasecmp('AbC','aBc'),0);
const comparisonText = memory.cstring('The lance');
assert.equal(s.strncmp(comparisonText, 'The ', 4n), 0);
assert.equal(s.strcmp('The lance\0suffix', BigInt(comparisonText)), 0);
assert.equal(s.strncmp('a\0suffix', 'a\0different', 20), 0);
assert.equal(s.strcmp('\xff', '\x80'), 127);
assert.equal(s.strncmp(0, 0, 0), 0);
const copyOracle=spawnSync(path.join(scratch,'probe'),['bytes'],{encoding:'utf8'});assert.equal(copyOracle.status,0,copyOracle.stderr);
const copyOut=memory.malloc(16);
for (const source of [s.literal('ab'), 'ab', 'ab\0ignored']) {
    const copyActual=[];
    for (const n of [0,1,2,3,7,16]) {
        memory.memset(copyOut,0xa5,16);
        const result=s.strncpy(copyOut,source,BigInt(n));
        copyActual.push([n,Number(result===copyOut),Buffer.from(memory.readBytes(copyOut,16)).toString('hex')].join(':'));
    }
    assert.deepEqual(copyActual,copyOracle.stdout.trim().split('\n'),'C size_t64 bounded copying and zero padding');
}
memory.writeString(copyOut,'ab');
assert.equal(s.strncat(copyOut,'cd\0ignored',8),copyOut);
assert.equal(memory.readString(copyOut),'abcd');
assert.equal(s.strncat(copyOut,'efgh',2),copyOut);
assert.equal(memory.readString(copyOut),'abcdef');
const creatOracle=spawnSync(path.join(scratch,'probe'),['creat',path.join(scratch,'creat-native.bin')],{encoding:'utf8'});assert.equal(creatOracle.status,0,creatOracle.stderr);
const files=createStandaloneEnvironment(),io=files.enableStdio(),payload=files.memory.cstring('abc');let fd=io.creat('/creat',0o640);assert.ok(fd>=3);assert.equal(io.write(fd,payload,3),3);assert.equal(io.close(fd),0);
fd=io.creat('/creat',0o600);const stat=files.filesystem.fstat(fd),badRead=io.read(fd,payload,1),creatActual=[[Number(fd>=0),stat.size,(stat.mode&0o777).toString(8),Number(badRead===-1&&files.libc.errno===new VFSError('EBADF').errno)].join(',')];assert.equal(io.close(fd),0);
const absent=io.creat('/creat.missing/file',0o600);creatActual.push([absent,Number(files.libc.errno===new VFSError('ENOENT').errno)].join(','));assert.deepEqual(creatActual,creatOracle.stdout.trim().split('\n'),'C creat truncation, permissions, write-only descriptor and missing-parent failure');
const timeEdges=[-(1n<<63n),-(1n<<63n)+1n,-(1n<<53n)-1n,-(1n<<53n),-1000000n,-1n,0n,1n,1000000n,(1n<<53n)-1n,1n<<53n,(1n<<53n)+1n,(1n<<63n)-2n,(1n<<63n)-1n];
// Only defined signed time_t differences are claimed; overflowing subtraction
// is undefined in the pinned C body and is outside this acceptance.
const timePairs=timeEdges.flatMap(end=>timeEdges.filter(start=>end-start>=-(1n<<63n)&&end-start<(1n<<63n)).map(start=>[end,start]));
const timeOracle=spawnSync(path.join(scratch,'probe'),['difftime'],{input:timePairs.map(pair=>pair.join(' ')).join('\n')+'\n',encoding:'utf8'});assert.equal(timeOracle.status,0,timeOracle.stderr);
const differences=timeOracle.stdout.trim().split('\n').map(Number);assert.equal(differences.length,timePairs.length);
for(const[i,[end,start]]of timePairs.entries())assert.equal(s.difftime(end,start),differences[i],'Pinned musl difftime subtraction before conversion '+end+':'+start);
console.log(`PASS: ${cases.length} exact original-musl qsort output/comparator traces, stable NetHack sorting, hacklib utilities bounded scanner contracts and6 C size_t64 strncpy cases plus C creat file contracts and${timePairs.length} pinned-musl difftime cases.`);
