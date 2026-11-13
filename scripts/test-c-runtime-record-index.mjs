// Differential contracts against the immutable prototype-factory predecessor.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import {execFileSync} from 'node:child_process';
import {pathToFileURL, fileURLToPath} from 'node:url';
import path from 'node:path';
const root=process.cwd(),base='7732c2a2d8e09c38fd3215f2173490c424e8e9aa';
function relocate(source){for(const file of ['adapter-memory.js','records.js'])source=source.replaceAll("'./"+file+"'",JSON.stringify(pathToFileURL(path.join(root,'js/c-runtime',file)).href));return source;}
const load=source=>import('data:text/javascript;base64,'+Buffer.from(relocate(source)).toString('base64'));
const baseline=await load(execFileSync('git',['show',base+':js/c-runtime/adapter-factories.js'],{encoding:'utf8'}));
const candidate=await import('../js/c-runtime/adapter-factories.js');
const outcome=fn=>{try{return{value:fn()};}catch(e){return{error:e.name,message:e.message};}};
function run(mod){
 const trace=[],observations=[],cache=new Map(),types=new Map(),ids=new WeakMap();let serial=0,revision=1,view,reenter=false;
 const layout={get RSize(){trace.push('size');if(reenter){reenter=false;observations.push(view('R',64).field);}return{valueOf(){trace.push('size coerce');return revision===2?16:8;}};}};
 const address=v=>{trace.push(['address',typeof v]);return Number(v?.address??v);};
 const init=(name,at)=>{trace.push(['init',String(name),at]);return{get field(){trace.push(['field',this.address,revision]);return this.address+revision;},set field(v){trace.push(['write',this.address,v]);revision=Number(v);},method(){return this.address;}};};
 view=mod.createPrototypeDescriptorFactory({address,cache,recordTypes:types,layout,errorPrefix:'missing '},init);
 const normalized=v=>{if(v&&typeof v==='object'){if(!ids.has(v))ids.set(v,++serial);return{id:ids.get(v),address:v.address,keys:Object.keys(v)};}return typeof v==='function'?{name:v.name,length:v.length}:v;};
 const get=(v,k)=>{const r=outcome(()=>v[k]);return r.error?r:{value:normalized(r.value)};};
 const first=view('R',64);observations.push(normalized(first),normalized(view('R',64)),normalized(view('R',0)));
 for(const key of ['field','method','0','00','01','1','2','09','10','00100','9007199254740993','999999999999999999999999999999999999999999','-1','+1','1e2','1.0',' 1','1 ','1\n','\n1','١','９','missing','address','kind',Symbol.iterator])observations.push([String(key),get(first,key)]);
 revision=2;observations.push(get(first,'1'));reenter=true;observations.push(get(first,'2'));
 first.field=9;observations.push(get(first,'field'));first.address=80;observations.push(get(first,'0'),get(first,'field'));
 // Private own numeric shadowing and handler-object reflection are outside
 // the accessor transport equivalence contract; test public indexed reads above.
 const custom=Object.create(Object.getPrototypeOf(first));Object.defineProperty(custom,'extra',{get(){trace.push('extra');return this.address+5;}});Object.setPrototypeOf(first,custom);observations.push(get(first,'extra'));
 observations.push(outcome(()=>{first.missing=4;}));cache.clear();observations.push(normalized(view('R',64)));
 types.clear();observations.push(normalized(view('R',96)));
 const pointer={get address(){trace.push('pointer.address');return 120;}};observations.push(normalized(view('R',pointer)));
 const name={ [Symbol.toPrimitive](hint){trace.push('name '+hint);return'R';}};observations.push(normalized(view(name,128)),get(view(name,128),'1'));
 return{trace,observations};
}
const expected=run(baseline),actual=run(candidate);assert.deepEqual(actual,expected);const result={baseCommit:base,events:actual.trace.length,observations:actual.observations.length,scope:'Actual prototype factory provider/reflection/index/identity/error/reentry comparisons under ordinary RegExp/Map intrinsics; no native or game acceptance.'};fs.mkdirSync(path.join(root,'.cache'),{recursive:true});fs.writeFileSync(path.join(root,'.cache/record-index-contracts.json'),JSON.stringify(result,null,2)+'\n');console.log(result);
