import assert from 'node:assert/strict';
import {writeFileSync} from 'node:fs';
import {pathToFileURL} from 'node:url';
import path from 'node:path';
const arg=process.argv.indexOf('--out');if(arg<0)throw Error('--out required');const out=path.resolve(process.argv[arg+1]);
const reference=(await import(pathToFileURL(out+'/reference-full.mjs'))).default;
const hybrid=(await import(pathToFileURL(out+'/hybrid-full.mjs'))).default;
import {createSfctool} from '../js/ported-utilities/sfctool-runtime.js';
import {C} from '../js/ported-utilities/sfctool-scope.js';
const expected='str=grow int=17 long=-9007199254740993 double=1.25 %\n';
function text(m,s){const n=m.lengthBytesUTF8(s)+1,p=Number(m._malloc(BigInt(n)));m.stringToUTF8(s,p,n);return p;}
const results=[];let checks=0;
for(const factory of[reference,hybrid]){
 const a=await factory({print(){},printErr(){}}),b=await factory({print(){},printErr(){}}),ha=createSfctool(a),hb=createSfctool(b);
 for(const[m,h]of[[a,ha],[b,hb]]){m.utilityInvoke=(name,args)=>h.invoke(name,args);m.utilityVararg=(...args)=>h.helper.vararg(...args);}
 hb.C.renidx=3;
 const second=text(b,'a.b/c'),before=a.HEAPU8.buffer.byteLength,secondBefore=b.HEAPU8.buffer.byteLength;
 let out='',nested=0,retained=0n;
 a.FS.createDevice('/','stdout',()=>null,value=>{
  if(!Number.isInteger(value))return;
  out+=String.fromCharCode(value);
  if(out.length===expected.length){
   retained=a._malloc(40n*1024n*1024n);
   b._utility_extra_call(0,BigInt(second),0);
   nested++;
  }
 });
 a._utility_streams();a._utility_extra_call(1,BigInt(text(a,'grow')),17);a._utility_flush();
 assert.equal(out,expected);assert.equal(nested,1);assert.ok(a.HEAPU8.buffer.byteLength>before);
 assert.equal(b.HEAPU8.buffer.byteLength,secondBefore);assert.equal(b.UTF8ToString(second),'a_b_c');
 assert.equal(ha.C.renidx,-1);assert.equal(hb.C.renidx,3);assert.equal(C,undefined);checks+=8;
 a._free(retained);
 results.push({stdout:out,nested,actualHeapGrowth:true,otherModuleHeapUnchanged:true,otherString:b.UTF8ToString(second),sourceScopeRestored:true});
}
assert.deepEqual(results[1],results[0]);checks++;
writeFileSync(path.join(out,'growth-reentry-results.json'),JSON.stringify({status:'PASS',checks,results,qualification:'Native stdio device callback grows on the final expected output byte, then invokes the actual source regularize function in a second Module. No mid-buffer SDK streaming-growth or post-exit resumption claim.'},null,2)+'\n');
console.log(JSON.stringify({status:'PASS',checks}));
