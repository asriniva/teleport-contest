import assert from 'node:assert/strict';
import {createNativeTerminal} from '../js/platform/darwin/terminal.js';
import abi from '../js/platform/darwin/terminal-abi.json' with {type:'json'};
import createWire from '../.cache/tu-probes/unixtty-reference.mjs';
import {referenceBackend} from './native-test-backend.mjs';
const {native:n,wire:w,nativeConstants:nc,wireConstants:wc}=abi;
function layout(module){const actual={};for(let i=0;i<module._probe_layout_count();i++){
    let at=Number(module._probe_layout_name(i)),end=at;while(module.HEAPU8[end])end++;
    const key=Buffer.from(module.HEAPU8.slice(at,end)).toString();actual[key]=Number(module._probe_layout_value(i));
}return actual;}
const sdk=await createWire(),native=await referenceBackend('unixtty')();
assert.deepEqual({size:Number(sdk._probe_context_size()),...layout(sdk)},w,'Recorded SDK transport ABI matches the actual compiler');
assert.deepEqual(layout(native),n,'Native ABI matches host C, independently of the compatibility header');
const call=createNativeTerminal();let heap=new Uint8Array(2048),stack=1024,status=0,events=[];
const wire=new Uint8Array(w.termioSize),wv=new DataView(wire.buffer);
wv.setUint32(w.c_lflag,wc.ECHO|wc.ICANON,true);wv.setUint32(w.c_iflag,wc.ISTRIP,true);
wv.setUint32(w.c_cflag,wc.CS7,true);wv.setUint32(w.c_oflag,wc.TAB3|wc.ONLCR,true);
wv.setUint32(w.termioSize-8,w.B9600,true);wv.setUint32(w.termioSize-4,w.B9600,true);
wire[w.c_cc+wc.VERASE]=127;
const services={moduleKey:{},heap:()=>heap,stackSave:()=>stack,stackRestore:s=>{stack=s;},
    stackAlloc:n=>{const p=stack;stack+=n+8;return p;},
    tcgetattr(fd,p){events.push(['get',fd]);if(!status){
        // I/O may replace the memory backing store before it returns.
        const grown=new Uint8Array(4096);grown.set(heap);heap=grown;heap.set(wire,p);
    }return status;},
    tcsetattr(fd,action,p){events.push(['set',fd,action]);if(!status)wire.set(heap.slice(p,p+w.termioSize));return status;},
    signal(sig,handler){events.push(['signal',sig,handler]);return events.length===1?0n:BigInt(abi.wireIgnore);},
    kill(pid,sig){events.push(['kill',pid,sig]);return -1;},
    fpathconf(fd,key){events.push(['pathconf',fd,key]);return 255n;},
    ioctl(fd,request,args){events.push(['ioctl',fd,request,args]);return -1;},
};
heap.fill(0xa5,64,64+n.termioSize);
assert.equal(call(services,'tcgetattr',0,64),0);assert.equal(stack,1024);
let view=new DataView(heap.buffer);
assert.equal(view.getBigUint64(64+n.c_lflag,true),BigInt(nc.ECHO|nc.ICANON));
assert.equal(view.getBigUint64(64+n.c_iflag,true),BigInt(nc.ISTRIP));
assert.equal(view.getBigUint64(64+n.c_cflag,true),BigInt(nc.CS7));
assert.equal(view.getBigUint64(64+n.c_oflag,true),BigInt(nc.TAB3|nc.ONLCR));
assert.equal(heap[64+n.c_cc+nc.VERASE],127);
assert.equal(call(services,'cfgetospeed',64),BigInt(n.B9600));
view.setBigUint64(64+n.c_lflag,1n<<60n,true);heap[64+n.c_cc+nc.VDSUSP]=42;
assert.equal(call(services,'tcsetattr',0,n.TCSADRAIN,64),0);assert.equal(stack,1024);
assert.equal(wv.getUint32(w.c_lflag,true)&(wc.ECHO|wc.ICANON),0);
assert.equal(call(services,'tcgetattr',0,64),0);view=new DataView(heap.buffer);
assert.equal(view.getBigUint64(64+n.c_lflag,true),1n<<60n,'Native-only bits survive transport round trips');
assert.equal(heap[64+n.c_cc+nc.VDSUSP],42,'Native-only control character survives transport round trips');
const before=heap.slice(64,64+n.termioSize);status=-1;
assert.equal(call(services,'tcgetattr',0,64),-1);assert.deepEqual(heap.slice(64,64+n.termioSize),before);
assert.equal(call(services,'tcsetattr',0,n.TCSADRAIN,64),-1);
events=[];assert.equal(call(services,'signal',18,1n),0n);
assert.equal(call(services,'signal',18,1n),1n);
assert.deepEqual(events,[['signal',20,BigInt(abi.wireIgnore)],['signal',20,BigInt(abi.wireIgnore)]]);
assert.equal(call(services,'kill',0,18),-1);assert.deepEqual(events.at(-1),['kill',0,20]);
assert.equal(call(services,'fpathconf',0,n._PC_VDISABLE),255n);
assert.deepEqual(events.at(-1),['pathconf',0,w._PC_VDISABLE]);
assert.equal(call(services,'ioctl',0,0x40087468n,200),-1);
assert.deepEqual(events.at(-1),['ioctl',0,0x5413,200]);
assert.equal(stack,1024);
console.log('Native terminal transport: flags, speeds, controls, memory replacement, error preservation, signal identities and ioctl request ABI passed.');
