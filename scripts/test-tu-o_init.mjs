import './pure-js-probes/deny-wasm.mjs';
import { DataView, Int32Array, assertStackRestored, allocationMetric, assertMemoryGrowth, memoryCheckpoint, referenceBackend, referenceLabel } from './native-test-backend.mjs';
const referenceFactory = referenceBackend('o_init', emscriptenReferenceFactory);
import assert from './native-test-assert.mjs';
import {readFileSync} from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/o_init-reference.mjs';
import createGeneratedProbe from './pure-js-fixtures/runtime.mjs';
const hybridFactory=options=>createGeneratedProbe('o_init',options);
import {createPortedRuntime} from '../js/backends/emscripten/runtime.js';
import {C,R,T} from '../js/c-runtime/context.js';
import * as core from '../js/ported/o_init.js';
const layouts=JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url)));
const L=layouts.o_init,runtime=createPortedRuntime(layouts);
const modules=[await referenceFactory(),await hybridFactory({nethackPorted:runtime})];
const stacks=modules.map(m=>m._probe_stack());let comparisons=0;
function text(m,p){if(!p)return null;p=Number(p);let e=p;while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.slice(p,e)).toString('latin1');}
function normalizedIO(m){const b=Buffer.from(m.HEAPU8.slice(Number(m._probe_pointer(3,0)),Number(m._probe_pointer(3,0))+m._probe_io_length()));const records=(L.MAXOCLASSES+2)*L.baseElementSize+L.NUM_OBJECTS*L.discoElementSize;for(let i=0;i<L.NUM_OBJECTS;i++){const p=records+i*L.objectClassSize+L.cls_oc_uname;if(p+8<=b.length)b.writeBigUInt64LE(b.readBigUInt64LE(p)?1n:0n,p);}return b;}
function snapshot(m){return {state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace()),rng:m._probe_rng_state()>>>0,count:m._probe_rng_count(),io:normalizedIO(m),position:m._probe_io_position(-1)};}
function check(){assert.deepEqual(snapshot(modules[1]),snapshot(modules[0]));assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);modules.forEach((m,i)=>assertStackRestored(m, stacks[i]));comparisons++;}
function call(name,...args){const idx={record:2,object:1,hero:1,prop:2}[name];if(idx!==undefined)args[idx]=BigInt(args[idx]);const out=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(out[1],out[0],`${name}:${args}`);comparisons++;check();return out[0];}
function reset(s=1){call('reset',s);}
function act(op,a=0,b=0,c=0,d=0){return call('action',op,a,b,c,d);}
function rec(row,field,v){call('record',row,field,v);}
function value(row,field){const out=modules.map(m=>m._probe_row_value(row,field));assert.equal(out[1],out[0]);comparisons++;return Number(out[0]);}
function hero(k,v){call('hero',k,v);}
function opt(k,v){call('option',k,v);}
function obj(k,v){call('object',k,v);}
function prop(p,k,v){call('prop',p,k,v);}
function trace(){return text(modules[0],modules[0]._probe_trace());}
function output(){return text(modules[0],modules[0]._probe_pointer(2,0));}
function fields(prefix,m=modules[0]){return text(m,m._probe_snapshot()).split(';').find(x=>x.startsWith(prefix+':')).split(':').slice(1);}
function rng(values){modules.forEach(m=>{new Int32Array(m.HEAPU8.buffer,Number(m._probe_rng_pointer()),values.length).set(values);m._probe_rng_length(values.length);});check();}
function stringCall(name,leading,s){modules.forEach(m=>{if(s===null)m['_probe_'+name](leading,0n);else{const b=Buffer.from(s+'\0','latin1'),p=Number(m._malloc(BigInt(b.length)));m.HEAPU8.set(b,p);m['_probe_'+name](leading,BigInt(p));m._free(p);}});check();}
function input(k,s){stringCall('input',k,s);}
function uname(type,s){stringCall('set_uname',type,s);}
function sorted(i,s){stringCall('sorted',i,s);}
function setup(s=1){reset(s);act(3);}
function readArray(m,kind,n,size,signed=true){const base=Number(m._probe_pointer(kind,0)),v=new DataView(m.HEAPU8.buffer);return Array.from({length:n},(_,i)=>v['get'+(signed?'Int':'Uint')+size*8](base+i*size,true));}
function bases(){return readArray(modules[0],4,L.MAXOCLASSES+2,L.baseElementSize);}
function disco(){return readArray(modules[0],5,L.NUM_OBJECTS,L.discoElementSize);}
function totals(){return readArray(modules[0],6,L.MAXOCLASSES,L.probTotalElementSize);}
function known(type,encountered=1){rec(type,3,0);rec(type,4,0);act(12,type,1,encountered,1);}
reset();
for(const m of modules)for(let i=0;i<m._probe_layout_count();i++){const k=text(m,m._probe_layout_name(i)),v=m._probe_layout_value(i);assert.equal(typeof L[k]==='string'?BigInt.asUintN(64,v).toString():Number(BigInt.asIntN(64,v)),L[k],k);}
const required=['NUM_OBJECTS','MAXOCLASSES','FIRST_OBJECT','BUFSZ','AMULET_OF_YENDOR','BELL_OF_OPENING','SPE_BOOK_OF_THE_DEAD','CANDELABRUM_OF_INVOCATION','POTION_CLASS','GEM_CLASS','VENOM_CLASS','AMULET_CLASS','SPBOOK_CLASS','ILLOBJ_CLASS','TURQUOISE','AQUAMARINE','FLUORITE','SAPPHIRE','DIAMOND','EMERALD','LAST_REAL_GEM','POT_WATER','POT_HEALING','POT_EXTRA_HEALING','SCR_IDENTIFY','SPE_FORCE_BOLT','SPEED_BOOTS','HELMET','LEATHER_GLOVES','CLOAK_OF_PROTECTION','SLIME_MOLD','MAGIC_HARP','WOODEN_HARP','PM_SAMURAI','PM_HUMAN','STRANGE_OBJECT','HALLUC','HALLUC_RES','MENU_TRADITIONAL','MENU_COMBINATION','MENU_PARTIAL','MENU_FULL','ECMD_OK','WRITING','READING','COUNTING','FREEING'];
for(const k of required)assert.ok(Number.isSafeInteger(L[k]),k);

// Read the three file-static datasets from original native storage; compare all entries and null sentinel.
const m=modules[0];assert.equal(core.uniq_objs.length,m._probe_table_count(0));for(let i=0;i<core.uniq_objs.length;i++){const v=new DataView(m.HEAPU8.buffer).getInt16(Number(m._probe_table_pointer(0))+2*i,true);assert.equal(v,L[core.uniq_objs[i]]);comparisons++;}
const nativeOrder=text(m,m._probe_table_pointer(1));assert.equal(nativeOrder,core.disco_order_let);assert.equal(m._probe_table_count(1),nativeOrder.length+1);
assert.equal(core.disco_orders_descr.length,m._probe_table_count(2));for(let i=0;i<core.disco_orders_descr.length;i++){const ptr=new DataView(m.HEAPU8.buffer).getBigUint64(Number(m._probe_table_pointer(2))+i*L.pointerSize,true);assert.equal(text(m,ptr),core.disco_orders_descr[i]||null);comparisons++;}
// Function-local static arrays retain source order without instrumenting or replacing the original C algorithm.
const csource=readFileSync(new URL('../.cache/wasm64-build/tree/src/o_init.c',import.meta.url),'utf8');
const jsource=readFileSync(new URL('../js/ported/o_init.js',import.meta.url),'utf8');
for(const name of ['shuffle_classes','shuffle_types']){const c=csource.match(new RegExp(`static (?:char|short) ${name}\\[\\] = \\{([\\s\\S]*?)\\};`));const j=jsource.match(new RegExp(`const ${name} = \\[([\\s\\S]*?)\\];`));assert.ok(c,name+' C initializer');assert.ok(j,name+' JS initializer');const tokens=s=>s.replace(/\/\*[\s\S]*?\*\//g,'').match(/\b[A-Z][A-Z_0-9]+\b/g);assert.deepEqual(tokens(j[1]),tokens(c[1]));comparisons++;}

// Full native records, bases and class totals are compared after each initializer and shuffle.
for(const seed of [1,2,0x12345678,0xffffffff]){setup(seed);const b=bases();assert.equal(b[L.MAXOCLASSES],L.NUM_OBJECTS);assert.equal(b[L.MAXOCLASSES+1],L.NUM_OBJECTS);for(let c=0;c<L.MAXOCLASSES;c++){assert.ok(b[c]<=b[c+1]);let sum=0;for(let row=b[c];row<b[c+1];row++)sum=(sum+value(row,2))<<16>>16;assert.equal(totals()[c],sum);}act(6);act(4);}
setup();for(let type=0;type<L.NUM_OBJECTS;type++){act(5,type);const state=fields('state');assert.ok(Number(state[5])<=type&&Number(state[6])>=type);}
for(const lev of [-3,-1,0,2,3,26,27,50,200]){setup();opt(1,lev);opt(2,50);act(0,1);const b=bases();let sum=0;for(let i=b[L.GEM_CLASS];i<b[L.GEM_CLASS+1];i++)sum+=value(i,2);assert.equal(totals()[L.GEM_CLASS],sum);act(8);}
setup();act(0,0);
const gemTypes=[L.TURQUOISE,L.AQUAMARINE,L.FLUORITE,L.SAPPHIRE,L.DIAMOND,L.EMERALD];reset();const originalColors=gemTypes.map(t=>value(t,9));
for(const blueT of [0,1])for(const blueA of [0,1])for(const fluorite of [0,1,2,3]){setup();gemTypes.forEach((t,i)=>{rec(t,1,t);rec(t,9,originalColors[i]);});rng([blueT,blueA,fluorite]);act(1);assert.equal(value(L.TURQUOISE,1),blueT?L.SAPPHIRE:L.TURQUOISE);assert.equal(value(L.AQUAMARINE,1),blueA?L.SAPPHIRE:L.AQUAMARINE);assert.equal(value(L.FLUORITE,1),[L.FLUORITE,L.SAPPHIRE,L.DIAMOND,L.EMERALD][fluorite]);}
for(const material of [-1,0,1,256,257]){setup();const lo=bases()[L.POTION_CLASS];for(let i=0;i<2;i++){rec(lo+i,3,0);rec(lo+i,8,i+1);rec(lo+i,7,i);}const descriptions=[value(lo,1),value(lo+1,1)];rng([1,0]);act(2,lo,lo+1,material);assert.equal(value(lo,1),descriptions[1]);assert.equal(value(lo+1,1),descriptions[0]);assert.equal(value(lo,8),(material<<24>>24)?2:1);assert.equal(value(lo,7),1);}
setup();let lo=bases()[L.POTION_CLASS];rec(lo,3,1);rec(lo+1,3,1);const draws=modules[0]._probe_rng_count();act(2,lo,lo+1,1);assert.equal(modules[0]._probe_rng_count(),draws);act(2,lo+1,lo,1);
for(const p of [0,-1,32767]){setup();const b=bases();for(let i=b[L.VENOM_CLASS];i<b[L.VENOM_CLASS+1];i++)rec(i,2,p);act(4);for(let i=b[L.VENOM_CLASS];i<b[L.VENOM_CLASS+1];i++)assert.equal(value(i,2),1);assert.ok(trace().includes('probability total'));}

// Native description lookup sees the actual shuffled descriptor index and rejects generic null objects safely.
setup();obj(0,L.POT_HEALING);const descriptionIndex=value(L.POT_HEALING,1);const descriptorPointer=new DataView(modules[0].HEAPU8.buffer).getBigUint64(Number(modules[0]._probe_pointer(1,descriptionIndex))+L.descr_oc_descr,true);input(2,text(modules[0],descriptorPointer));assert.equal(act(7,0),1n);input(2,'wrong description');assert.equal(act(7,0),0n);act(7,-1);obj(0,L.STRANGE_OBJECT);act(7,0);

// Name allocations are genuinely freed once; typed object records preserve null versus empty names on restore.
for(const flags of [0,L.COUNTING,L.WRITING,L.FREEING,L.WRITING|L.FREEING]){setup();uname(L.POT_HEALING,'called\x80name');uname(L.SCR_IDENTIFY,'');call('nhfile',0,flags);act(9);assert.equal(modules[0]._probe_free_count(1),flags&L.FREEING?2:0);}
setup();uname(L.POT_HEALING,'user name\x80');uname(L.SCR_IDENTIFY,'');rec(L.POT_HEALING,14,-1n);call('nhfile',0,L.WRITING|L.FREEING);act(9);assert.equal(modules[0]._probe_free_count(1),2);const serialized=modules.map(x=>normalizedIO(x));call('nhfile',0,L.READING);act(10);modules.forEach((x,i)=>assert.deepEqual(normalizedIO(x),serialized[i]));assert.equal(modules[0]._probe_io_position(-1),modules[0]._probe_io_length());assert.ok(text(modules[0],modules[0]._probe_snapshot()).includes('user name\x80'));call('nhfile',0,L.FREEING);act(9);assert.equal(modules[0]._probe_free_count(1),4);

// Discovery insertion/deletion, role-specific names, hallucination and live game-loop side effects.
for(const mark of [-1,0,1,256,257])for(const encounter of [0,1]){setup();rec(L.POT_HEALING,3,0);rec(L.POT_HEALING,4,0);hero(6,1);act(12,L.POT_HEALING,mark,encounter,1);assert.equal(value(L.POT_HEALING,3),mark<<24>>24?1:0);assert.equal(value(L.POT_HEALING,4),encounter);act(12,L.POT_HEALING,mark,encounter,1);}
for(const property of [0,1,2]){setup();obj(0,L.POT_HEALING);rec(L.POT_HEALING,4,0);if(property)prop(L.HALLUC,0,1);if(property===2)prop(L.HALLUC_RES,0,1);act(11);assert.equal(value(L.POT_HEALING,4),property===1?0:1);}
setup();obj(0,L.STRANGE_OBJECT);act(11);act(12,L.STRANGE_OBJECT,1,1,1);
setup();hero(6,1);rec(L.DIAMOND,3,0);act(12,L.DIAMOND,1,0,1);assert.ok(trace().includes(`gem:${L.DIAMOND};`));assert.ok(trace().includes('inventory;'));
setup();hero(7,1);hero(6,1);rec(L.POT_HEALING,3,0);act(12,L.POT_HEALING,1,0,1);assert.ok(!trace().includes('inventory;'));
setup();for(const t of [L.POT_HEALING,L.POT_EXTRA_HEALING,L.POT_WATER]){rec(t,3,0);rec(t,4,0);act(12,t,0,1,0);}rec(L.POT_EXTRA_HEALING,4,0);act(13,L.POT_EXTRA_HEALING);assert.ok(!disco().includes(L.POT_EXTRA_HEALING));assert.ok(disco().includes(L.POT_WATER));
setup();rec(L.POT_HEALING,3,0);rec(L.POT_HEALING,4,0);act(13,L.POT_HEALING);assert.ok(trace().includes('named object not in disco'));
setup();hero(0,L.PM_SAMURAI);opt(3,L.POT_HEALING);rec(L.POT_HEALING,3,0);rec(L.POT_HEALING,4,0);act(12,L.POT_HEALING,0,0,0);assert.ok(disco().includes(L.POT_HEALING));assert.equal(act(14,L.POT_HEALING),1n);
for(const called of [false,true]){setup();rec(L.POT_HEALING,3,0);rec(L.POT_HEALING,4,0);if(called)uname(L.POT_HEALING,'custom');assert.equal(act(14,L.POT_HEALING),called?1n:0n);}

// The native comparator ignores exactly two prefix bytes; real deterministic sort calls through the JS trampoline.
for(const [a,b] of [['* Zebra','  apple'],['* apple','  APPLE'],['  \x80','* \xff'],['  a2','* a10']]){setup();input(2,a);input(3,b);act(15);}
for(const loot of [-1,0,1,256,257]){setup();const list=loot<<24>>24?['* 01010 Zebra','  01010 apple','* 01010 APPLE']:['* Zebra','  apple','* APPLE'];list.forEach((s,i)=>sorted(i,s));act(21,list.length,loot);assert.equal(modules[0]._probe_free_count(3),3);assert.equal(modules[0]._probe_free_count(4),2);assert.ok(trace().includes('qsort:3:8;'));assert.ok(trace().includes('compare:'));assert.deepEqual(fields('lines')[0].split(',').slice(0,3).map(Number),[0,0,0]);}
setup();act(21,0,0);
for(const type of [L.POT_HEALING,L.SLIME_MOLD,L.MAGIC_HARP])for(const knows of [0,1]){setup();rec(type,3,knows);obj(0,type);hero(9,127);opt(5,-2);opt(6,9);opt(8,1);act(16,type);assert.ok(trace().includes('loot-cookie:'+ '00'.repeat(L.lootSize)));}
for(const type of [L.POT_HEALING,L.MAGIC_HARP,L.WOODEN_HARP])for(const form of ['plain','called','parenthesized']){setup();hero(0,L.PM_SAMURAI);opt(3,type);input(0,form==='called'?'fixture called user':form==='parenthesized'?'fixture (actual)':'fixture');act(18,type);assert.ok(output().includes('['));}
for(const kind of ['short','long-plain','long-parenthesis']){setup();input(0,kind==='short'?'short name':kind==='long-plain'?'n'.repeat(L.BUFSZ-2):'n'.repeat(L.BUFSZ-20)+' (actual type)');input(1,'PREFIX ');opt(4,1);act(19,L.POT_HEALING);assert.ok(output().length<L.BUFSZ);if(kind==='long-parenthesis')assert.ok(output().includes(' (actual type)'));}
for(const known of [0,1])for(const type of [L.AMULET_OF_YENDOR,L.BELL_OF_OPENING,L.SPE_BOOK_OF_THE_DEAD,L.CANDELABRUM_OF_INVOCATION]){setup();rec(type,3,known);act(20,type);assert.ok(output().startsWith('  '));}
for(let c=1;c<L.MAXOCLASSES;c++){setup();act(23,c);assert.equal(output(),`class ${c}`);}

// Sort selection, all discovery output modes, class menus and naming transfer full native unions/pointer arrays.
for(const sort of ['o','s','c','a','x','\0'])for(const config of [-1,0,1,256,257]){if(sort==='\0'&&!(config<<24>>24))continue;setup();hero(1,sort.charCodeAt(0));act(26,config);assert.equal(output(),config<<24>>24?(sort==='x'?'o':sort==='\0'?'':sort):core.disco_orders_descr[core.disco_order_let.indexOf(sort)<0?0:core.disco_order_let.indexOf(sort)]);}
for(const count of [-1,0,1,2])for(const mode of [0,1,2]){setup();hero(1,111);opt(12,count);call('pick_input',0,111);call('pick_input',1,97);act(17,mode);if(count===2)assert.equal(fields('state')[0],'97');assert.equal(modules[0]._probe_free_count(2),count>0?1:0);}
for(const sort of ['o','s','c','a','x'])for(const unique of [0,1]){setup();hero(1,sort.charCodeAt(0));known(L.POT_HEALING);known(L.POT_EXTRA_HEALING,0);known(L.SCR_IDENTIFY);uname(L.POT_HEALING,'zebra');if(unique)known(L.BELL_OF_OPENING);opt(10,unique);act(22);assert.ok(trace().includes('display:19:1;'));if(sort==='s'||sort==='c'||sort==='a')assert.ok(trace().includes('qsort:'));}
setup();act(22);assert.ok(trace().includes("haven't discovered anything"));
for(const style of [L.MENU_TRADITIONAL,L.MENU_COMBINATION,L.MENU_PARTIAL,L.MENU_FULL])for(const choice of ['!', 'u','r','a','\0']){setup();known(L.POT_HEALING);known(L.BELL_OF_OPENING);hero(2,style);opt(10,1);opt(14,choice.charCodeAt(0));opt(12,choice==='\0'?0:1);call('pick_input',0,choice.charCodeAt(0));act(24);if(choice==='u'||choice==='r'){assert.ok(trace().includes('Unique items or relics'));assert.ok(trace().includes('Bell of Opening'));}}
for(const sort of ['o','s','a']){setup();known(L.POT_HEALING);known(L.POT_EXTRA_HEALING);hero(2,L.MENU_TRADITIONAL);hero(1,sort.charCodeAt(0));opt(14,33);act(24);assert.ok(trace().includes('Discovered Class'));}
setup();hero(2,L.MENU_FULL);act(24);assert.ok(trace().includes("haven't discovered any items"));
setup();known(L.BELL_OF_OPENING);hero(2,L.MENU_TRADITIONAL);hero(8,1);opt(14,97);opt(15,121);act(24);assert.ok(trace().includes('artifact-dump:'));
for(const kind of ['empty','uncallable','cancel','selected']){setup();if(kind!=='empty')known(L.POT_HEALING);if(kind==='uncallable')opt(9,0);opt(12,kind==='selected'?1:0);call('pick_input',0,L.POT_HEALING);act(25);if(kind==='selected')assert.ok(trace().includes('docall-object:'));}

// Delegated sort menus must preserve cancellation and apply an affirmative choice before output.
for(const operation of [22,24])for(const selected of [-1,1]){setup();known(L.POT_HEALING);hero(3,1);hero(2,L.MENU_TRADITIONAL);opt(12,selected);call('pick_input',0,97);opt(14,33);act(operation);assert.ok(trace().includes('Ordering of discoveries'));if(selected<0){assert.ok(!trace().includes('display:19:1;'));assert.equal(fields('state')[0],'111');}else{assert.equal(fields('state')[0],'97');assert.ok(trace().includes('display:19:1;'));}}
// The initializer diagnoses and repairs an actually pre-known object with an alternate description.
reset();hero(5,1);rec(L.POT_HEALING,3,1);act(3);assert.equal(value(L.POT_HEALING,3),0);assert.ok(trace().includes('name is pre-known despite alternate description'));

// Real heap growth and native reentry at dependency boundaries, including inside actual qsort comparisons.
for(const stage of [1,2,3,4,5,6,7,8,9,10,11,12,13]){setup();opt(30,stage);opt(31,stage);const before=modules.map(x=>allocationMetric(x));if(stage===1||stage===2){hero(6,1);rec(L.DIAMOND,3,0);act(12,L.DIAMOND,1,0,1);}else if(stage===3)act(18,L.POT_HEALING);else if(stage===4){input(1,'');act(19,L.POT_HEALING);}else if(stage===5)act(16,L.POT_HEALING);else if(stage===6||stage===7){sorted(0,'  zebra');sorted(1,'* apple');act(21,2,0);}else if(stage===8){known(L.POT_HEALING);act(22);}else if(stage===9||stage===10){opt(12,1);call('pick_input',0,111);act(17,1);}else if(stage===11){known(L.POT_HEALING);opt(12,1);call('pick_input',0,L.POT_HEALING);act(25);}else{uname(L.POT_HEALING,'growth');if(stage===12){call('nhfile',0,L.WRITING);act(9);}else{call('nhfile',0,L.WRITING|L.FREEING);act(9);call('nhfile',0,L.READING);act(10);}}assert.ok(trace().includes(`grew:${stage};`),`growth ${stage}`);assert.ok(trace().includes('nested-sort:'));modules.forEach((x,i)=>assert.ok(allocationMetric(x)>before[i]));}
reset();opt(0,0);act(3);assert.ok(trace().includes('@;'));
setup();known(L.POT_HEALING);const held=snapshot(modules[1]);const other=await hybridFactory({nethackPorted:runtime});other._probe_reset(77);other._probe_action(3,0,0,0,0);other._probe_record(L.POT_HEALING,3,0n);other._probe_action(12,L.POT_HEALING,1,1,1);assert.equal(other._probe_row_value(L.POT_HEALING,3),1n);other._probe_action(22,0,0,0,0);assert.deepEqual(snapshot(modules[1]),held);comparisons+=2;check();
console.log(`O_INIT ${referenceLabel}/pure-JS differential: ${comparisons} comparisons checked`);
