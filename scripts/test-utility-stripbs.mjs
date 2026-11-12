import assert from'node:assert/strict';import{resolve}from'node:path';import{pathToFileURL}from'node:url';import{writeFileSync,existsSync}from'node:fs';
import{C}from'../js/c-runtime/context.js';
assert.equal(process.argv.length,4,'Pass --out <actual fresh build directory>');assert.equal(process.argv[2],'--out');const w=resolve(process.argv[3]);assert.equal(existsSync(w+'/test-results.json'),false,'Refuse existing test result');
const {callStripbs}=await import(pathToFileURL(resolve(process.env.STRIPBS_RUNTIME??new URL('../js/ported-utilities/stripbs-runtime.js',import.meta.url).pathname)));
const reference=(await import(pathToFileURL(w+'/reference.mjs'))).default,hybrid=(await import(pathToFileURL(w+'/hybrid.mjs'))).default;
let comparisons=0,bodyCalls=0;const cases=[];const inputs=[[],[65],[65,66],[65,8,66],[65,66,8,67],[8],[8,8,8],[65,8,8,66],[0],[0,65,0,66],[65,0,8,66],[65,10,66,13,9],[255,128,254,127,8,255],Array.from({length:256},(_,i)=>i),Array.from({length:256},(_,i)=>255-i),Array.from({length:4096},(_,i)=>i%7===0?8:(i*37)%256)];
let seed=0x13579bdf;for(let j=0;j<16;j++){const a=[];for(let i=0;i<j*13;i++){seed^=seed<<13;seed^=seed>>>17;seed^=seed<<5;a.push(seed&255);}inputs.push(a);}
async function run(data,initialErrno,errorStream){
 const a=await reference(),b=await hybrid({stripbsPort:{main(s,argc,argv){bodyCalls++;return callStripbs(s,argc,argv);}}});
 for(const m of[a,b]){m.FS.writeFile('/input',Uint8Array.from(data));assert.equal(m._probe_prepare(errorStream?1:0,initialErrno),0);}
 const state=[a,b].map(m=>{const stack=m._probe_stack(),value=m._probe_run(),errno=m._probe_errno(),eof=m._probe_eof(),error=m._probe_error(),closed=m._probe_output_closed();assert.equal(m._probe_stack(),stack,'actual main stack restoration');comparisons++;return{value,errno,eof,error,closed,output:[...m.FS.readFile('/output')]};});
 assert.deepEqual(state[1],state[0],JSON.stringify({data,initialErrno,errorStream}));comparisons++;assert.equal(C,undefined);comparisons++;assert.equal(state[0].closed,1);comparisons++;
 const EOF=a._teleport_stripbs_metadata(0),failure=a._teleport_stripbs_metadata(1),success=a._teleport_stripbs_metadata(2);
 if(!errorStream){assert.equal(state[0].value,initialErrno===EOF?success:failure,'preserve original errno!=EOF return quirk');comparisons++;}else{assert.notEqual(state[0].error,0,'actual write-only stream read error');comparisons++;}
 cases.push({input:data.length<=16?data:{length:data.length},initialErrno,errorStream,...state[0],output:state[0].output.length<=16?state[0].output:{length:state[0].output.length}});
}
for(const bytes of inputs)for(const errno of[0,-1,123])await run(bytes,errno,false);
for(const bytes of[[],[65,8,255,0,66]])for(const errno of[0,-1,123])await run(bytes,errno,true);
const result={status:'PASS',comparisons,cases:cases.length,originalBodiesInvoked:1,bodyCalls,actualCResultCases:cases,qualification:'Original C main against imported JS main; real libc FILE streams on actual Emscripten MEMFS, fresh independent Modules per case. NativeMac/file-device parity and game scope are not claimed.'};
console.log(JSON.stringify({status:result.status,comparisons,cases:cases.length,originalBodiesInvoked:1,bodyCalls}));writeFileSync(w+'/test-results.json',JSON.stringify(result,null,2)+'\n');
