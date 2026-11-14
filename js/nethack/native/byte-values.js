// Native scratch bytes materialize only at a real byte consumer. Reservations
// keep ownership in the declaring frame even when an address is requested below it.
import {CMemory} from '../../c-runtime/heap.js';
export function createNativeByteValues(environment){
 const {transport:t,memory}=environment;
 return function nativeByteBuffer(size){
  size=Number(size);if(!Number.isSafeInteger(size)||size<0)throw RangeError('Native byte buffer extent');
  const reservation=t.stackAlloc.reserve(size);let at,data;
  const bounds=i=>{reservation.assertAlive();if(!Number.isSafeInteger(i)||i<0||i>=size)throw RangeError('Native byte buffer extent');};
  const bytes=()=>{reservation.assertAlive();return at===undefined?(data??=new Uint8Array(size)):memory.HEAPU8.subarray(at,at+size);};
  return {nativeBytes:true,get address(){reservation.assertAlive();if(at===undefined){at=reservation();if(data){memory.HEAPU8.set(data,at);data=undefined;}}return at;},
   store(i,v){bounds(i);v=t.char(v);bytes()[i]=v;return v;},
   load(i=0){bounds(i);const v=bytes()[i];return v<<24>>24;},
   cstringBytes(){const value=bytes(),n=value.indexOf(0);if(n<0)throw RangeError('Unterminated native C string');return value.slice(0,n+1);},
   copyCString(source){reservation.assertAlive();let value;
    if(source?.nativeBytes)value=source.cstringBytes();
    else if(typeof source==='string'){const raw=CMemory.byteString(source),n=raw.indexOf(0);value=new Uint8Array((n<0?raw.length:n)+1);value.set(n<0?raw:raw.subarray(0,n));}
    else{const p=environment.address(source),n=memory.strlen(p);value=memory.HEAPU8.subarray(p,p+n+1);}
    if(value.length>size)throw RangeError('Native C string exceeds buffer');bytes().set(value);return this;
   },
  };
 };
}
