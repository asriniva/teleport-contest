import{parseArgs}from'node:util';import{resolve}from'node:path';import{pathToFileURL}from'node:url';
const cli=parseArgs({options:{out:{type:'string'}}});if(!cli.values.out)throw Error('--out required');
const outURL=pathToFileURL(resolve(cli.values.out)+'/');
const rf=(await import(new URL('reference.mjs',outURL))).default,hf=(await import(new URL('hybrid.mjs',outURL))).default;
import assert from'node:assert/strict';import{writeFileSync}from'node:fs';import{createUtility}from'../js/ported-utilities/random-runtime.mjs';import{C}from'../js/ported-utilities/random-scope.mjs';
let checks=0;const eq=(a,b,n)=>{assert.deepEqual(b,a,n);checks++;};
async function setup(factory){const m=await factory();let u;if(factory===hf){u=createUtility(m);m.utilityInvoke=(...a)=>u.invoke(...a);m.utilityScalar=i=>u.scalar(i);m.utilityPointer=i=>u.pointer(i);}const size=m._utility_long_size();assert.equal(size,8);checks++;return{m,u,size,buffers:[],text:p=>{p=Number(p);let e=p;while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.subarray(p,e)).toString();},view:()=>new DataView(m.HEAPU8.buffer)};}
const a=await setup(rf),b=await setup(hf);
function norm(x,p){p=BigInt(p);const base=BigInt(x.m._utility_storage());if(p>=base&&p<=base+BigInt(32*x.size))return['default',Number(p-base)];for(let i=0;i<x.buffers.length;i++){const q=x.buffers[i];if(p>=q.p&&p<=q.p+BigInt(q.bytes))return[i,Number(p-q.p)];}return['unknown',p.toString()];}
function snapshot(x){return{scalars:Array.from({length:3},(_,i)=>x.m._probe_scalar(i)),pointers:Array.from({length:4},(_,i)=>norm(x,x.m._probe_pointer(i))),initial:Buffer.from(x.m.HEAPU8.subarray(Number(x.m._utility_storage()),Number(x.m._utility_storage())+32*x.size)),buffers:x.buffers.map(q=>Buffer.from(x.m.HEAPU8.subarray(Number(q.p),Number(q.p)+q.bytes))),diags:x.m._probe_diag_count(),text:x.text(x.m._probe_diagnostic())};}
function compare(label){eq(snapshot(a),snapshot(b),label);assert.equal(C,undefined);checks++;}
function allocate(x,type){const degree=x.m._utility_degree(type);const bytes=(degree+1)*x.size+64;const p=BigInt(x.m._malloc(BigInt(bytes)));x.m.HEAPU8.fill(0xa7,Number(p),Number(p)+bytes);x.buffers.push({p,bytes});return p;}
compare('JS authoritative initial32 native long cells/pointer layout');
for(let i=0;i<130;i++){eq(a.m._random(),b.m._random(),'default random '+i);compare('default pointer wrap '+i);}
const sizes=[8,31,32,63,64,127,128,255,256,1024];
for(const n of sizes){const type=n<32?0:n<64?1:n<128?2:n<256?3:4;for(const seed of[0,1,2,0x7fffffff,0x80000000,0xffffffff]){const p=allocate(a,type),q=allocate(b,type);eq(norm(a,a.m._initstate(seed,p,n)),norm(b,b.m._initstate(seed,q,n)),'initstate old alias '+n+':'+seed);compare('initstate exact full cells/tails');for(let i=0;i<73;i++){const x=a.m._random(),y=b.m._random();eq(x,y,'configured generated value');assert.ok(x>=0n&&x<=0x7fffffffn);checks++;}compare('degree wrap and generated state');}}
for(const i of[0,5,12,30,59,1,0]){eq(norm(a,a.m._setstate(a.buffers[i].p)),norm(b,b.m._setstate(b.buffers[i].p)),'setstate old alias');compare('restored pointers');for(let j=0;j<17;j++)eq(a.m._random(),b.m._random(),'restored sequence');eq(norm(a,a.m._setstate(a.buffers[i].p)),norm(b,b.m._setstate(b.buffers[i].p)),'same-state alias safe');compare('same-state header');}
for(const n of[-8,0,7]){eq(a.m._initstate(123,0n,n),b.m._initstate(123,0n,n),'size rejection before NULL dereference');compare('size rejected diagnostic/current state header');}
for(const x of[a,b]){const p=allocate(x,4);x.view().setBigInt64(Number(p),-1n,true);x.m._setstate(p);}
compare('negative corrupt type diagnostic still valid physically allocated degree');for(let i=0;i<30;i++)eq(a.m._random(),b.m._random(),'source retained degree after corrupt type');compare('post diagnostic state');
// External native mutation of the currently active long cell is observed live.
for(const x of[a,b])x.view().setBigInt64(Number(x.m._probe_pointer(2)),123456789n,true);
eq(a.m._random(),b.m._random(),'external state-cell mutation');compare('external mutation fresh read');
const before=b.m.HEAPU8.buffer;const big=b.m._malloc(BigInt(b.m.HEAPU8.length*2));assert.notEqual(before,b.m.HEAPU8.buffer);b.m._free(big);checks++;eq(a.m._random(),b.m._random(),'fresh views after actual growth');compare('growth exact state');
const c=await setup(hf);eq(snapshot(await setup(rf)),snapshot(c),'independent Module defaults');c.m._srandom(9);compare('separate Module does not alter other Module');
for(const x of[a,b])for(const q of x.buffers)x.m._free(q.p);
writeFileSync(new URL('results.json',outURL),JSON.stringify({status:'PASS CURRENT EMC OBSERVATION',checks,ownedFunctions:4,seeds:6,selectorSizes:sizes,growth:true,initialStateCells:32,limits:'Signed long recurrence overflow is inherited C UB; exact current EmC output/state observations, not portable-C proof. Physically adequate compiler-sized long buffers; no undersized/misaligned/freed inputs or concurrent calls; normal game ISAAC unchanged.'},null,2)+'\n');console.log('PASS RANDOM all4 functions '+checks+' checks');
