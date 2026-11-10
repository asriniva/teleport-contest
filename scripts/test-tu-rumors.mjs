import { DataView, Int32Array, assertStackRestored, allocationMetric, assertMemoryGrowth, memoryCheckpoint, referenceBackend, referenceLabel } from './native-test-backend.mjs';
const referenceFactory = referenceBackend('rumors', emscriptenReferenceFactory);
import assert from './native-test-assert.mjs';
import {readFileSync} from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/rumors-reference.mjs';
import hybridFactory from '../.cache/tu-probes/rumors-hybrid.mjs';
import {createPortedRuntime} from '../js/ported/wasm-runtime.js';
import {C,R,T} from '../js/ported/c-runtime.js';
const layouts=JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url))),L=layouts.rumors,runtime=createPortedRuntime(layouts),modules=[await referenceFactory(),await hybridFactory({nethackPorted:runtime})],stacks=modules.map(m=>m._probe_stack());let comparisons=0;
function text(m,p){if(p===0n||p===0)return null;p=Number(p);let e=p;while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.slice(p,e)).toString('latin1');}
function caps(m){const counts=[0,1,2].map(f=>m._probe_cap_count(f)),p=m._probe_cap_pointer();return {counts,exists:p!==0n,names:p===0n?[]:Array.from({length:counts[2]},(_,i)=>text(m,m._probe_cap_name(i)))};}
function snapshot(m){return {state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace()),output:Buffer.from(m.HEAPU8.slice(Number(m._probe_output()),Number(m._probe_output())+Number(m._probe_output_size()))),saved:Buffer.from(m.HEAPU8.slice(Number(m._probe_saved_pointer()),Number(m._probe_saved_pointer())+Number(m._probe_saved_size()))),caps:caps(m),rng:m._probe_rng_state()>>>0,count:m._probe_rng_count()};}
function check(){assert.deepEqual(snapshot(modules[1]),snapshot(modules[0]));assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);modules.forEach((m,i)=>assertStackRestored(m, stacks[i]));comparisons++;}
const longs={hero:[1],prop:[2]};
function call(name,...args){args=args.map((v,i)=>longs[name]?.includes(i)?BigInt(v):v);const out=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(out[1],out[0],`${name}(${args})`);check();comparisons++;return out[0];}
function reset(seed=1){call('reset',seed);}
function rng(values){modules.forEach(m=>{new Int32Array(m.HEAPU8.buffer,Number(m._probe_rng_pointer()),values.length).set(values);m._probe_rng_length(values.length);});check();}
function file(id,data,encryptFrom=-1){const bytes=Buffer.from(data,'latin1');modules.forEach(m=>{const p=Number(m._malloc(BigInt(bytes.length+1)));m.HEAPU8.set(bytes,p);m.HEAPU8[p+bytes.length]=0;m._probe_file(id,BigInt(p),bytes.length,encryptFrom);m._free(p);});check();}
function act(op,a=0,b=0,start=0n,end=0n,pad=0,s=''){const out=modules.map(m=>{let p=0;if(s!==null){const bytes=Buffer.from(s+'\0','latin1');p=Number(m._malloc(BigInt(bytes.length)));m.HEAPU8.set(bytes,p);}try{return m._probe_action(op,a,b,BigInt(start),BigInt(end),pad,BigInt(p));}finally{if(p)m._free(p);}});assert.deepEqual(out[1],out[0],`action${op}`);check();comparisons++;return out[0];}
function output(){return text(modules[0],modules[0]._probe_output());}
function trace(){return text(modules[0],modules[0]._probe_trace());}
function fields(key){return text(modules[0],modules[0]._probe_snapshot()).split(';').find(s=>s.startsWith(key+':')).split(':').slice(1);}
function padded(s,n=L.MD_PAD_RUMORS){return s.padEnd(n,'_')+'\n';}
function rumors(t=['TRUE first','TRUE second'],f=['FALSE first','FALSE second']){const T=t.map(s=>padded(s)).join(''),F=f.map(s=>padded(s)).join(''),comment='# generated\n';let begin=0,header;for(let i=0;i<10;i++){header=`${t.length},${T.length},${begin.toString(16)};${f.length},${F.length},${(begin+T.length).toString(16)};0,0,${(begin+T.length+F.length).toString(16)}\n`;const next=comment.length+header.length;if(next===begin)break;begin=next;}return {data:comment+header+T+F,begin,tSize:T.length,fSize:F.length};}
function oracles(records=[['SPECIAL message','special second line'],['NORMAL first'],['NORMAL second','another normal line']]){let offset='# generated\n'.length+String(records.length).length+1+records.length*6;const offsets=[],bodies=[];for(const record of records){offsets.push(offset.toString(16).padStart(5,'0'));const body=record.map(s=>s+'\n').join('')+'---\n';bodies.push(body);offset+=body.length;}return {data:'# generated\n'+records.length+'\n'+offsets.join('\n')+'\n'+bodies.join(''),bodyLine:2+records.length};}
const bogus='# bogus\n'+['default bogus','BogonType___','_GeneralType___','|GroupType___','-PersonName___','+ManName___','=AnyPerson___','lowercase___','ZebraZilla___','___'].map(s=>s+'\n').join('');
function defaults(){const r=rumors(),o=oracles();file(0,r.data,2);file(1,o.data,o.bodyLine);file(2,bogus,1);file(3,'# engrave\nfirst__\nsecond__\nthird__\nlast__\n',1);file(4,'# epitaph\nfirst__\nsecond__\n',1);file(5,'# generic\nA___\nBBB___\nCCCC___\n',1);}
reset();for(const m of modules)for(let i=0;i<m._probe_layout_count();i++){const k=text(m,m._probe_layout_name(i)),raw=m._probe_layout_value(i);assert.equal(typeof L[k]==='string'?BigInt.asUintN(64,raw).toString():Number(BigInt.asIntN(64,raw)),L[k],k);}
for(const k of ['BUFSZ','MD_PAD_RUMORS','MD_PAD_BOGONS','BY_COOKIE','BY_PAPER','BY_ORACLE','WRITING','FREEING','COUNTING','ECMD_OK','ECMD_TIME','BLINDED'])assert.ok(Number.isSafeInteger(L[k]),k);
for(const s of ['', '\n','_', '____\n','foo','foo___','foo___\n','foo\n_','foo\r\n','\x80___\n']){reset();act(10,0,0,0n,0n,0,s);}
// Real native fgets/fseek/ftell selection, every byte offset and weighted lines.
reset();const lines=['A','BBB','CCCCCCCC'],body=lines.join('\n')+'\n';file(5,body,0);call('open',5);const frequencies=new Map();for(let pos=0;pos<body.length;pos++){rng([pos]);act(12,8192,0,0n,BigInt(body.length));frequencies.set(output(),(frequencies.get(output())||0)+1);}assert.deepEqual([...frequencies].sort(),[['A',9],['BBB',2],['CCCCCCCC',4]]);call('close');
for(const size of [0,1,2,5,256,8192])for(const end of [0n,15n]){reset();file(5,body,0);call('open',5);rng([0]);act(12,size,1,0n,end);call('position');call('close');}
reset();file(5,'',-1);call('open',5);act(12,256,0);assert.equal(output(),'');assert.equal(call('rng_count'),0);call('close');
reset();file(5,'L'.repeat(500)+'\n'+'R'.repeat(600)+'\n',0);call('open',5);rng([0]);act(12,8192,0);assert.equal(output(),'R'.repeat(600));assert.equal(call('free_count'),1);call('close');
reset();file(5,'L'.repeat(500)+'\n'+padded('SHORT'),0);call('open',5);rng(Array(10).fill(0));act(12,8192,0,0n,0n,L.MD_PAD_RUMORS);assert.equal(call('rng_count'),10);assert.equal(output(),'SHORT');call('close');
for(const pad of [0,L.MD_PAD_RUMORS,L.MD_PAD_BOGONS]){reset();defaults();rng([0]);act(2,5,1,0n,0n,pad);assert.ok(output().length);assert.match(trace(),/alternate:/);}
// Header parsing uses actual native sscanf and64bit output pointers.
for(const header of ['bad\n','1,0,20;1,60,40;0,0,80\n','1,60,fffffffffffffff0;1,60,8000000000000000;0,0,ffffffffffffffff\n']){reset();file(0,'# header\n'+header);call('open',0);act(11);call('close');}
for(const truth of [-2,-1,0,1,2])for(const choose of [0,1]){reset();defaults();rng([choose,0]);act(0,truth,0);if(truth===-2&&choose===0||truth===2&&choose===1)assert.equal(output(),'Oops...');}
reset();defaults();call('option',0,1);act(0,1,0);assert.equal(output(),'');call('option',0,0);act(0,1,0);assert.equal((trace().match(/open-fail:rumors/g)||[]).length,1);
reset();file(0,'# bad\nnot a header\n');act(0,1,0);assert.match(output(),/Error reading/);const opens=call('open_count');act(0,1,0);assert.equal(call('open_count'),opens);
for(const cookies of [0,48,49,50]){reset();const r=rumors(['TRUE'],['[cookie] Cookie clue','SAFE clue']);file(0,r.data,2);const values=[];for(let i=0;i<cookies;i++)values.push(0,L.MD_PAD_RUMORS+1);values.push(0,0);rng(values);act(0,-1,1);assert.equal(output(),'SAFE clue');assert.equal(trace().includes("Can't find non-cookie"),cookies>=49);}
reset();const allCookie=rumors(['TRUE'],['[cookie] only']);file(0,allCookie.data,2);rng(Array(102).fill(0));act(0,-1,1);assert.match(output(),/^\[cookie\]/);assert.equal(call('rng_count'),102);
reset();file(0,allCookie.data,2);rng([0,0]);act(0,-1,0);assert.equal(output(),'only');
for(const mklev of [0,1]){reset();defaults();call('hero',3,mklev);rng([0,0]);act(0,1,1);assert.equal(trace().includes('exercise:'),!mklev);}
// Rumor checking and auxiliary files traverse true/false boundaries and UI errors.
reset();defaults();act(1);assert.match(trace(),/T start=/);assert.match(trace(),/Bogus monsters:/);
for(const data of ['', 'not a comment\n','\n','#+\n','#+\n\n','#+\nfirst\n','#+\nfirst\nsecond\n','#+\nfirst\nsecond\nthird\n','#+\nfirst\nsecond\nthird\nfourth\n']){reset();file(3,data,1);act(14,3,0,0n,0n,0,'Engravings:');}
reset();defaults();call('option',7,1);act(14,3,0,0n,0n,0,'Engravings:');assert.match(trace(),/can't create temporary window/);
for(const fuzzer of [0,1]){reset();call('hero',4,7);call('hero',5,fuzzer);act(15,5);assert.equal(fields('hero')[6],'7');assert.match(trace(),new RegExp('impossible:'+(fuzzer?7:0)+':'));}
for(const mechanism of [L.BY_COOKIE,L.BY_PAPER,L.BY_ORACLE,99])for(const blind of [0,1])for(const fainted of [0,1]){reset();defaults();if(blind)call('prop',L.BLINDED,0,1);call('option',2,fainted);rng(Array(10).fill(0));act(3,1,mechanism);}
// Oracle offsets/consumption, special repeatability and save/restore ownership.
reset();defaults();rng([0]);act(6,1,0);assert.equal(Number(fields('oracle')[1]),3);assert.match(trace(),/SPECIAL message/);act(6,1,1);assert.equal(Number(fields('oracle')[1]),3);act(6,0,1);assert.equal(Number(fields('oracle')[1]),2);act(6,0,0);assert.equal(Number(fields('oracle')[1]),1);act(6,0,0);assert.equal(Number(fields('oracle')[1]),1);
for(const mode of [0,L.COUNTING,L.WRITING,L.FREEING,L.WRITING|L.FREEING]){reset();defaults();act(6,1,0);act(4,mode);if(mode&(L.COUNTING|L.WRITING))assert.equal(Number(call('saved_size')),4+3*8);if(mode&L.FREEING){assert.equal(fields('oracle')[1],'0');assert.equal(call('free_count'),1);}if(mode===(L.WRITING|L.FREEING)){call('restore_position',0);act(5);assert.equal(fields('oracle')[1],'3');assert.equal(fields('oracle')[0],'1');act(6,0,0);}}
reset();defaults();act(6,1,0);act(4,L.WRITING|L.FREEING);modules.forEach(m=>{const p=Number(m._probe_saved_pointer()),v=new DataView(m.HEAPU8.buffer);v.setBigUint64(p+4,(1n<<64n)-1n,true);v.setBigUint64(p+12,1n<<63n,true);v.setBigUint64(p+20,(1n<<53n)+1n,true);});call('restore_position',0);act(5);assert.match(fields('oracle')[2],/18446744073709551615,9223372036854775808,9007199254740993/);
for(const data of ['', '# header\n0\n','# header\nbad\n']){reset();file(1,data);act(6,0,0);assert.equal(fields('oracle')[1],'0');const n=call('open_count');act(6,0,0);assert.equal(call('open_count'),n);}
reset();defaults();call('option',0,2);act(6,0,0);call('option',0,0);const n=call('open_count');act(6,0,0);assert.equal(call('open_count'),n);
// Consultation UI/state/events and exactly native long64 wallet arithmetic.
for(const money of [0n,49n,50n,51n,999n,1000n,(1n<<53n)+1n])for(const minor of ['q','y','n'])for(const major of ['n','y']){reset();defaults();call('hero',9,money);call('hero',8,-((1n<<53n)+17n));call('option',3,minor.charCodeAt(0));call('option',4,major.charCodeAt(0));rng(Array(20).fill(0));const result=act(7,1);assert.equal(fields('hero')[4],'0');if(result===L.ECMD_TIME){assert.equal(fields('hero')[5],'1');assert.match(trace(),/pay:/);}}
reset();call('hero',8,-((1n<<53n)+17n));assert.equal(act(7,0),L.ECMD_OK);assert.equal(fields('hero')[4],'0');reset();call('hero',7,0);call('hero',9,100);assert.equal(act(7,1),L.ECMD_OK);
for(const doneMinor of [0,1])for(const doneMajor of [0,1]){reset();defaults();call('hero',1,doneMajor);call('hero',2,doneMinor);call('hero',9,10000);call('option',3,'y'.charCodeAt(0));rng(Array(10).fill(0));act(7,1);assert.equal(trace().includes('achievement:'),!(doneMinor||doneMajor));assert.equal(trace().includes('experience:'),!doneMinor);}
// Capital-name gathering: two passes, exact native ownership and full-word rules.
reset();defaults();for(const word of [null,'','archon','123Monster']){assert.equal(act(8,0,0,0n,0n,0,word),0);assert.equal(caps(modules[0]).exists,false);}
reset();defaults();act(16);let cap=caps(modules[0]);assert.ok(cap.counts[0]>0&&cap.counts[1]>0);assert.equal(cap.counts[2],cap.counts[0]+cap.counts[1]+1);assert.equal(cap.names.at(-1),null);assert.equal((trace().match(/seek:\d+:0:0:/g)||[]).length,2);assert.ok(cap.names.includes('BogonType'));assert.ok(!cap.names.includes('PersonName'));for(const word of cap.names.slice(0,-1)){for(const ending of ['', ' corpse',"'s corpse"]){assert.equal(act(8,0,0,0n,0n,0,word+ending),1);}assert.equal(act(8,0,0,0n,0n,0,word+'X'),0);}
let beforeFree=call('free_count');act(9);assert.equal(call('free_count')-beforeFree,cap.counts[1]+1);assert.equal(caps(modules[0]).exists,false);act(9);assert.equal(call('free_count')-beforeFree,cap.counts[1]+1);
reset();defaults();call('option',13,1);act(16);assert.ok(caps(modules[0]).counts[0]>=cap.counts[0]);beforeFree=call('free_count');const oldOwned=caps(modules[0]).counts[1]+1;act(16);assert.equal(call('free_count')-beforeFree,oldOwned);
reset();defaults();call('remove',2);act(16);assert.equal(caps(modules[0]).counts[1],0);act(9);assert.equal(call('free_count'),1);
reset();defaults();call('hero',6,1);call('option',10,1);act(16);assert.match(trace(),/Capitalized monster type names/);
// Real read callback grows memory; native exercise reenters another source path.
reset();defaults();call('option',11,1);call('option',12,1);rng([0,0]);const sizes=modules.map(m=>allocationMetric(m));act(0,1,1);assert.match(trace(),/nested-cap:1/);modules.forEach((m,i)=>assert.ok(allocationMetric(m)>sizes[i]));
// Shared runtime must key private CapMons ownership by actual native module.
reset();defaults();act(16);const referenceCaps=caps(modules[0]),other=await hybridFactory({nethackPorted:runtime});other._probe_reset(1);assert.equal(caps(other).exists,false);assert.deepEqual(caps(modules[1]),referenceCaps);other._probe_action(16,0,0,0n,0n,0,0n);assert.ok(caps(other).exists);assert.deepEqual(caps(modules[1]),referenceCaps);other._probe_action(9,0,0,0n,0n,0,0n);assert.deepEqual(caps(modules[1]),referenceCaps);check();
reset();call('option',1,0);defaults();rng([0,0]);act(0,1,1);const savedState=snapshot(modules[0]);modules[1]._probe_hero(0,7n);assert.deepEqual(snapshot(modules[0]),savedState);reset();
console.log(`RUMORS: ${comparisons} ${referenceLabel}/hybrid native-file, oracle, consultation, cache, ownership and RNG-site comparisons checked.`);
