import assert from 'node:assert/strict';
import {readFileSync,writeFileSync} from 'node:fs';
import {pathToFileURL} from 'node:url';
import path from 'node:path';
const arg=process.argv.indexOf('--out');if(arg<0)throw Error('--out required');const out=path.resolve(process.argv[arg+1]);
const reference=(await import(pathToFileURL(out+'/reference-full.mjs'))).default;
const hybrid=(await import(pathToFileURL(out+'/hybrid-full.mjs'))).default;
import {createSfctoolHelpers} from '../js/ported-utilities/sfctool-helpers.js';
const names=JSON.parse(readFileSync(new URL('../nethack-c/wasm/utilities/sfctool/helper-functions.json',import.meta.url)));
const all=[],observed=new Set();let checks=0,cases=0;
for(const factory of [reference,hybrid]) {
    let helpers;
    const m=await factory({print(){},printErr(){}});
    helpers=createSfctoolHelpers(m);m.utilityInvoke=(name,args)=>helpers.invoke(name,args);
    all.push({m,h:helpers,mon:Number(m._utility_root(0)),obj:Number(m._utility_root(1))});
}
function str(x,s){const bytes=x.m.lengthBytesUTF8(s)+1,p=Number(x.m._malloc(BigInt(bytes)));x.m.stringToUTF8(s,p,bytes);return p;}
function call(name,...args){observed.add(name);const results=all.map(x=>x.m._utility_call(names.indexOf(name),...Array.from({length:4},(_,i)=>BigInt(typeof args[i]==='function'?args[i](x):args[i]??0))));return results;}
function normalized(x){const {m,h,mon,obj}=x;const count=m._utility_log(0,0),pointers=Array.from({length:count},(_,i)=>Number(m._utility_allocation(i+1)));const id=p=>p? pointers.lastIndexOf(Number(p))+1:0;
 const mx=h.record(mon,'monst').mextra,ox=h.record(obj,'obj').oextra;
 const nested=(base,fields)=>base?fields.map(f=>id(base[f]?.address??base[f])):0;
 return{freeCalls:m._utility_log(4,0),mail:ox&&ox.omailcmd?m.UTF8ToString(ox.omailcmd):null,allocations:Array.from({length:count},(_,i)=>m._utility_log(2,i+1)),frees:Array.from({length:m._utility_log(1,0)},(_,i)=>m._utility_log(3,i+1)),mextra:id(mx?.address),oextra:id(ox?.address),monfields:nested(mx,['mgivenname','egd','epri','eshk','emin','edog','ebones']),objfields:nested(ox,['oname','omonst','omailcmd']),mcorpsenm:mx?mx.mcorpsenm:0,omid:ox?ox.omid:0,flags:Array.from({length:5},(_,i)=>m._utility_monflag_get(BigInt(mon),i)),bill:mx?.eshk?id(mx.eshk.bill_p):0};}
function state(label){assert.deepEqual(normalized(all[1]),normalized(all[0]),label);checks++;cases++;}
const mon=x=>x.mon,obj=x=>x.obj;
for (const s of ['','plain','/tmp/a','a/b\\c:d','a/b:c/d','ends/']) {
 const p=all.map(x=>str(x,s));const out=call('briefname',x=>p[all.indexOf(x)]);const offsets=out.map((v,i)=>Number(v)-p[i]);assert.equal(offsets[1],offsets[0]);checks++;
}
for(const v of [-99,-1,0,1,2,3,99]){const out=call('style_to_text',v).map((p,i)=>all[i].m.UTF8ToString(Number(p)));assert.equal(out[0],out[1]);checks++;}
assert.deepEqual(call('delete_savefile'),[0n,0n]);checks++;
for(const a of ['','a','AbC','abc=10','abc : yes','abc\t = hi',':x','xy'])for(const b of ['','abc','ABCD','xy'])for(const n of [0,1,2,3,8]){
 const as=all.map(x=>str(x,a)),bs=all.map(x=>str(x,b));const get=(p,x)=>p[all.indexOf(x)];const r=call('util_strncmpi',x=>get(as,x),x=>get(bs,x),n);assert.equal(r[1],r[0]);checks++;
 for(const v of [0,1]){const q=call('match_optname',x=>get(as,x),x=>get(bs,x),n,v);assert.equal(q[1],q[0]);checks++;}
 const l=call('length_without_val',x=>get(as,x),a.length);assert.equal(l[1],l[0]);checks++;
}
for(const s of ['', 'x', 'z'.repeat(128),'z'.repeat(129)]){
 for(const x of all)x.m.FS.createPath('/','env',true,true);
 // Actual libc getenv receives the actual Emscripten environment value.
 for(const x of all)x.m.ENV={SFCTOOL_TEST:s};
 const p=all.map(x=>str(x,'UNDEFINED_SFCTOOL_TEST'));
 assert.deepEqual(call('nh_getenv',x=>p[all.indexOf(x)]),[0n,0n]);checks++;
}
for(const value of ['', 'x', 'z'.repeat(128), 'z'.repeat(129)]){
 const env=all.map(x=>str(x,'SFCTOOL_REAL_ENV')),v=all.map(x=>str(x,value));
 for(const[i,x]of all.entries())assert.equal(x.m._utility_setenv(BigInt(env[i]),BigInt(v[i])),0);
 const pointers=call('nh_getenv',x=>env[all.indexOf(x)]);
 for(const[i,x]of all.entries()){if(value.length<=x.h.L[11]/2)assert.equal(x.m.UTF8ToString(Number(pointers[i])),value);else assert.equal(pointers[i],0n);checks++;}
}
call('new_mgivenname',mon,17);state('new name');call('new_mgivenname',mon,5);state('replace name');call('new_mgivenname',mon,0);state('zero name');call('free_mgivenname',mon);state('empty name free');
for(const [fresh,release,key,size]of [['newegd','free_egd','egd',4],['newepri','free_epri','epri',5],['neweshk','free_eshk','eshk',6],['newemin','free_emin','emin',7],['newedog','free_edog','edog',8],['newebones','free_ebones','ebones',9]]){
 call(fresh,mon);state(fresh);
 for(const x of all){const p=x.h.record(x.mon,'monst').mextra[key].address;x.m._utility_memory(1,BigInt(p),BigInt(x.h.L[size]));}
 call(fresh,mon);state(fresh+' reuse');
 for(const x of all){const p=x.h.record(x.mon,'monst').mextra[key].address;const bytes=Array.from(x.m.HEAPU8.slice(p,p+x.h.L[size]));assert.ok(bytes.every(c=>c===(key==='eshk'?0:0xa5)));checks++;}
 const flag=['egd','epri','eshk','emin','edog'].indexOf(key);
 if(flag>=0)for(const x of all)x.m._utility_monflag(BigInt(x.mon),flag,flag===4?7:1);
 call(release,mon);state(release);
 if(flag>=0)for(const x of all){assert.equal(x.m._utility_monflag_get(BigInt(x.mon),flag),0);checks++;}
 call(release,mon);state(release+' again');
}
call('new_oname',obj,12);state('new objname');call('new_oname',obj,4);state('replace objname');call('new_oname',obj,0);state('zero objname');call('free_oname',obj);state('empty objname');
call('newomid',obj);state('newomid');call('free_omid',obj);state('free_omid');
for(const s of ['hello','replaced','']){const p=all.map(x=>str(x,s));call('new_omailcmd',obj,x=>p[all.indexOf(x)]);state('mailcmd');}
call('free_omailcmd',obj);state('free mail');call('free_omailcmd',obj);state('free mail empty');
call('newomonst',obj);state('newomonst');call('newomonst',obj);state('newomonst reuse');
call('new_mgivenname',x=>x.h.record(x.obj,'obj').oextra.omonst.address,11);
call('newepri',x=>x.h.record(x.obj,'obj').oextra.omonst.address);
call('free_omonst',obj);state('free omonst');call('free_omonst',obj);state('free omonst empty');
call('newegd',mon);call('newepri',mon);call('neweshk',mon);call('newemin',mon);call('newedog',mon);call('newebones',mon);call('new_mgivenname',mon,9);state('all extras');call('dealloc_mextra',mon);state('dealloc all');call('dealloc_mextra',mon);state('dealloc all empty');
for(const [name,kind,bytes]of [['init_mextra','mextra',2],['init_oextra','oextra',3]]){const p=all.map(x=>Number(x.m._malloc(BigInt(x.h.L[bytes]))));for(const[i,x]of all.entries())x.m._utility_memory(1,BigInt(p[i]),BigInt(x.h.L[bytes]));call(name,x=>p[all.indexOf(x)]);const raw=all.map((x,i)=>Array.from(x.m.HEAPU8.slice(p[i],p[i]+x.h.L[bytes])));assert.deepEqual(raw[0],raw[1]);checks++;}
for(const name of ['newmextra','newoextra']){const p=call(name);assert.ok(p.every(Boolean));checks++;}
const m=all.map(x=>Number(x.m._utility_newmonst()));for(const[x,i]of all.map((x,i)=>[x,i]))x.m._utility_memory(0,BigInt(m[i]),BigInt(x.h.L[0]));call('dealloc_monst',x=>m[all.indexOf(x)]);state('dealloc monster');
assert.equal(observed.size,35);
const result={status:'PASS',checks,cases,helpers:observed.size,wholeTuComplete:false,configuredFunctions:50};writeFileSync(path.join(out,'full-helper-test-results.json'),JSON.stringify(result,null,2)+'\n');console.log(JSON.stringify(result));
