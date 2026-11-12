import {layoutSourceSha} from './nethack-layout.mjs';
// Compare real SDK libc calls with standalone device boundaries on real fds.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import crypto from 'node:crypto';
import {pathToFileURL} from 'node:url';
import {createStandaloneEnvironment} from '../js/nethack/environment.js';
import {createTerminalDevices} from '../js/nethack/unix-terminal.js';
import {connectUnixPlatformSyscalls} from '../js/nethack/unix-platform-syscalls.js';
import abi from '../js/nethack/unix-platform-abi.json' with {type:'json'};
const directory=path.resolve(process.env.STANDALONE_TERMINAL_ERRNO_ORACLE||'.cache/standalone-terminal-errno-v1');
const receipt=JSON.parse(fs.readFileSync(path.join(directory,'receipt.json'))),sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex');
for(const [p,h]of Object.entries(receipt.sourceSha256))assert.equal(layoutSourceSha(p,h),h,'Changed SDK reference input '+p);
for(const [p,h]of Object.entries(receipt.artifactSha256))assert.equal(sha(path.join(directory,p)),h,'Changed SDK reference artifact '+p);
const {default:factory}=await import(pathToFileURL(path.join(directory,'reference.mjs'))),ref=await factory();
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),env=createStandaloneEnvironment();env.enableStdio();
connectUnixPlatformSyscalls(env,env.ctypes);const device=createTerminalDevices(env,layouts),size=ref._probe_terminal_size(2),out=env.memory.malloc(size);
assert.equal(size,128);assert.equal(ref._probe_terminal_constant(0),abi.errno.ENOTTY);assert.equal(ref._probe_terminal_constant(1),abi.errno.EBADF);assert.equal(ref._probe_terminal_constant(2),abi.errno.EINVAL);
const winsize=ref._probe_terminal_constant(3),actions=[-1,...[4,5,6].map(i=>ref._probe_terminal_constant(i)),3];
const descriptors=[['stdin',0,0],['stdout',1,1],['stderr',2,2]];
for(const name of ['regular','closed']){env.filesystem.writeFile('/'+name,Uint8Array.of(1,2,3));ref.FS.writeFile('/'+name,Uint8Array.of(1,2,3));}
env.filesystem.mkdir('/directory');ref.FS.mkdir('/directory');
for(const name of ['regular','directory','closed']){
 const j=env.services.open('/'+name,0),c=ref.FS.open('/'+name,'r').fd;assert.ok(j>=3&&c>=3,'Real descriptor '+name);
 if(name==='closed'){assert.equal(env.services.close(j),0);ref.FS.close(ref.FS.getStream(c));}
 descriptors.push([name,j,c]);
}
descriptors.push(['negative',-1,-1],['invalid',9999,9999]);
let comparisons=4,cases=0;
const calls=[[0,0],[1,0],[3,0],...actions.map(action=>[2,action])];
for(const fill of [0,0xa5,0xff])for(const sentinel of [0,73,abi.errno.ENOTTY])for(const [label,jfd,cfd]of descriptors)for(const [op,action]of calls){
 const cp=Number(ref._probe_terminal_buffer(fill));env.memory.memset(out,fill,size);env.libc.errno=sentinel;ref._probe_terminal_errno(sentinel);
 const expected=ref._probe_terminal_op(op,cfd,action);
 const actual=op===0?env.services.isatty(jfd):op===1?device.tcgetattr(jfd,out):op===2?device.tcsetattr(jfd,action,out):device.ioctl(jfd,winsize,out);
 const description=`${label} op=${op} action=${action} fill=${fill} errno=${sentinel}`;
 assert.equal(actual,expected,description+' result');
 assert.equal(env.libc.errno,ref._probe_terminal_errno(sentinel),description+' errno');
 assert.deepEqual(env.memory.readBytes(out,size),ref.HEAPU8.slice(cp,cp+size),description+' full output/input buffer and untouched bytes');
 comparisons+=3;cases++;
}
for(const [name,j,c]of descriptors)if(['regular','directory'].includes(name)){env.services.close(j);ref.FS.close(ref.FS.getStream(c));}
console.log(`PASS: ${comparisons} original-SDK terminal comparisons across ${cases} calls: isatty/tcgetattr/tcsetattr/TIOCGWINSZ, real regular/directory/closed/invalid/stdtty descriptors, sentinel errno and complete buffers.`);
