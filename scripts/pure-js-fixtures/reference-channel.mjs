// Synchronous binary RPC used only by the separately isolated original-C reference.
import fs from 'node:fs';
import {serialize,deserialize} from 'node:v8';
const pause=new Int32Array(new SharedArrayBuffer(4));
export function channel(input,output){
 function read(n){const bytes=Buffer.alloc(n);let at=0;const deadline=Date.now()+120000;while(at<n){try{const got=fs.readSync(input,bytes,at,n-at);if(!got)throw Error('C reference channel closed');at+=got;}catch(e){if(e.code!=='EAGAIN')throw e;if(Date.now()>deadline)throw Error('C reference response timed out');Atomics.wait(pause,0,0,0.05);}}return bytes;}
 function write(bytes){let at=0;while(at<bytes.length){try{at+=fs.writeSync(output,bytes,at,bytes.length-at);}catch(e){if(e.code!=='EAGAIN')throw e;Atomics.wait(pause,0,0,0.05);}}}
 return {receive(){return deserialize(read(read(4).readUInt32LE()));},send(value){const bytes=serialize(value),header=Buffer.alloc(4);header.writeUInt32LE(bytes.length);write(header);write(bytes);}};
}
