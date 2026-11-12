// Original EmC TU versus imported JS, with explicitly controlled foreign world/UI.
import assert from './native-test-assert.mjs';
import {readFileSync} from 'node:fs';
import {resolve} from 'node:path';
import {pathToFileURL} from 'node:url';
import {callEngrave} from '../js/nethack/bindings/engrave.js';
import * as data from '../js/ported/engrave.js';
import {C,R,T} from '../js/c-runtime/context.js';
const dir=resolve(process.env.TELEPORT_ENGRAVE_PROBE_DIR??'.cache/tu-probes');
const path=kind=>pathToFileURL(resolve(dir,(process.env.TELEPORT_ENGRAVE_PROBE_DIR?'':'engrave-')+kind+'.mjs'));
const {default:rf}=await import(path('reference')),{default:hf}=await import(path('hybrid'));
const reference=await rf();
function text(m,ptr){let p=Number(ptr);if(!p)return null;let e=p;while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.slice(p,e)).toString('latin1');}
const L={};for(let i=0;i<reference._probe_layout_count();i++)L[text(reference,reference._probe_layout_name(i))]=Number(reference._probe_layout_value(i));
for(let i=0;i<reference._probe_string_count();i++)L[text(reference,reference._probe_string_name(i))]=text(reference,reference._probe_string_value(i));
for(const m of readFileSync(new URL(import.meta.url),'utf8').matchAll(/L\.([A-Z][A-Z_0-9]+)\b/g))assert.ok(m[1]in L,'Missing fixture constant '+m[1]);
const runtime={engrave:(services,name,...args)=>callEngrave(new Proxy(services,{get(target,key,receiver){if(['rectState','trackState'].includes(key))return target[key];if(!Reflect.has(target,key))throw Error('Missing ENGRAVE environment key '+String(key));return Reflect.get(target,key,receiver);}}),L,name,...args)};
const modules=[reference,await hf({nethackPorted:runtime})],stacks=modules.map(m=>m._probe_stack());let comparisons=0,context='';
function snapshot(m){return{state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace()),output:text(m,m._probe_output())};}
function check(){assert.deepEqual(snapshot(modules[1]),snapshot(reference),context);for(let i=0;i<2;i++)assert.equal(modules[i]._probe_stack(),stacks[i]);assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);comparisons++;}
function call(name,...args){const v=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(v[1],v[0],context+':'+name);check();return v[0];}
function string(m,value,fn){if(value===null)return fn(0n);const bytes=Buffer.from(value,'latin1'),ptr=m._malloc(BigInt(bytes.length+1));try{m.HEAPU8.set(bytes,Number(ptr));m.HEAPU8[Number(ptr)+bytes.length]=0;return fn(BigInt(ptr));}finally{m._free(ptr);}}
function input(value){for(const m of modules)string(m,value,p=>m._probe_input(p));check();}
function make(value='Elbereth',type=L.DUST,x=10,y=10,original=null,time=0n){for(const m of modules)string(m,value,s=>string(m,original,p=>m._probe_make(x,y,s,p,BigInt(time),type)));check();}
const reset=()=>call('reset'),opt=(key,value)=>call('option',key,value),act=(op,a=0,b=0,c=0,d=0n)=>call('action',op,a,b,c,BigInt(d)),trace=()=>snapshot(reference).trace,state=()=>snapshot(reference).state;
for(const m of modules)for(let i=0;i<m._probe_layout_count();i++)assert.equal(Number(m._probe_layout_value(i)),L[text(m,m._probe_layout_name(i))]);
assert.equal(reference._probe_table_count(0),data.rubouts.length);assert.equal(reference._probe_table_count(1),data.blind_writing.length);
for(const[row,r]of data.rubouts.entries()){assert.equal(reference._probe_table_value(0,row,0),r.wipefrom);assert.equal(text(reference,reference._probe_table_text(row)),r.wipeto);}
for(const[row,r]of data.blind_writing.entries()){assert.equal(r.length,reference._probe_table_width());for(let col=0;col<21;col++)assert.equal(reference._probe_table_value(1,row,col),r[col]);}
// Exact byte rubouts including unsigned seed wrap and leading/trailing spaces.
for(const value of ['', '  ', 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789', "?.,'`-|_:=+*@", 'An engraving!', '\x7f\xffABC  '])for(const seed of [0n,1n,2n,255n,65535n,4294967295n])for(const count of [0,1,5,30]){context=JSON.stringify({value,seed:String(seed),count});reset();input(value);opt(0,1);act(1,count,0,0,seed);}
for(const seed of [1,2,7,42])for(const noRumor of [0,1]){reset();call('seed',seed);opt(21,noRumor);opt(0,1);act(0);act(33);}
// Material/type/string/list lifetime; remembered and pristine text may differ.
for(const type of [L.DUST,L.ENGRAVE,L.BURN,L.MARK,L.ENGR_BLOOD,L.HEADSTONE,0])for(const value of ['Elbereth','a short inscription.','  leading words!','X']){reset();make(value,type,10,10,'original inscription!',9007199254740993n);act(4,10,10);input(value);act(5,10,10,1);act(8);act(9,10,10);act(26);act(22);act(32);act(31);act(21);act(11,10,10);assert.match(state(),/^g:/);}
reset();make('x'.repeat(L.BUFSZ+20),L.ENGRAVE);act(9,10,10);assert.match(trace(),/You:read/);
reset();make('one',L.DUST,10,10);make('two',L.MARK,11,10);make('three',L.BURN,12,10);opt(24,1);act(26);act(27,1);act(27,1);act(27,0);
// Type protection, erosion and exact unsigned16 count narrowing at direct calls.
for(const type of [L.DUST,L.ENGRAVE,L.BURN,L.HEADSTONE])for(const magical of [0,1])for(const count of [0,1,5,65536]){reset();make('  ABCDEFGH  ',type);opt(0,1);act(7,10,10,count,BigInt(magical));}
reset();make('immutable',L.DUST);call('engr_bit',0,1,1);act(6,10);assert.match(state(),/immutable/);
reset();make('ABCDE',L.DUST);act(6,65536);assert.match(state(),/ABCDE/);assert.match(state(),/rng:0;/);
// Hero/terrain/property macros with original native dependencies and level guards.
for(const pm of [L.PM_HUMAN,L.PM_AIR_ELEMENTAL,L.PM_GHOUL,L.PM_GIANT_SPIDER])for(const flying of [0,1])for(const lev of [0,1]){reset();call('hero',pm,0,0,0,L.P_BASIC);call('prop',L.FLYING,BigInt(flying),0n,0n);call('prop',L.LEVITATION,BigInt(lev),0n,0n);act(2,1);act(3,0,1,0);act(14);}
for(const skill of [0,L.P_BASIC]){reset();call('hero',L.PM_HUMAN,0,0,1,skill);act(2,1);}
for(const typ of [L.ROOM,L.ALTAR,L.GRAVE,L.FOUNTAIN,L.AIR,L.CLOUD,L.STONE]){reset();call('terrain',10,10,typ,0);act(14);}
for(const slot of [0,1,2])for(const typ of [L.DAGGER,L.MAGIC_MARKER,L.TOWEL,L.WAN_FIRE,L.DIAMOND,L.PLATE_MAIL]){context=JSON.stringify({slot,typ});reset();call('item',slot,typ,1,1n,0);call('equipment',0,0);call('equipment',1,1);opt(5,1);act(12);act(13,slot);}
// Private context and every wand effect retain buffers/flags and live field writes.
const wands=[L.WAN_LIGHT,L.WAN_SECRET_DOOR_DETECTION,L.WAN_STASIS,L.WAN_CREATE_MONSTER,L.WAN_WISHING,L.WAN_ENLIGHTENMENT,L.WAN_STRIKING,L.WAN_SLOW_MONSTER,L.WAN_SPEED_MONSTER,L.WAN_POLYMORPH,L.WAN_NOTHING,L.WAN_UNDEAD_TURNING,L.WAN_OPENING,L.WAN_LOCKING,L.WAN_PROBING,L.WAN_MAGIC_MISSILE,L.WAN_SLEEP,L.WAN_DEATH,L.WAN_COLD,L.WAN_CANCELLATION,L.WAN_MAKE_INVISIBLE,L.WAN_TELEPORTATION,L.WAN_DIGGING,L.WAN_FIRE,L.WAN_LIGHTNING];
for(const wand of wands)for(const blind of [0,1]){context=JSON.stringify({wand,blind});reset();make('old writing',L.BURN);call('prop',L.BLINDED,BigInt(blind),0n,0n);act(15);call('item',0,wand,1,1n,0);call('context',0,0n);act(16);act(17);}
for(const type of [0,L.DUST,L.ENGRAVE,L.BURN,L.MARK,L.HEADSTONE,L.ENGR_BLOOD])for(const adding of [0,1])for(const frost of [0,1]){reset();act(15);call('context',2,BigInt(type));call('context',4,BigInt(adding));call('context',5,BigInt(frost));act(18);}
for(const typ of [L.DAGGER,L.ATHAME,L.MAGIC_MARKER,L.TOWEL,L.DIAMOND,L.PLATE_MAIL,L.LOW_BOOTS,L.FOOD_RATION,L.SCR_BLANK_PAPER,L.BOULDER,L.BLINDING_VENOM]){reset();act(15);call('item',0,typ,2,1n,0);call('context',0,0n);act(17);}
// Entire command: cancel/escape, add/overwrite, finger/marker/blade/wand.
for(const selected of [-1,-2,0])for(const value of ['', '\x1b','x','Elbereth','Hello world!']){reset();input(value);opt(1,selected);act(19);for(let turn=0;turn<12;turn++)if(act(34)===0n)break;}
for(const typ of [L.DAGGER,L.ATHAME,L.MAGIC_MARKER,L.TOWEL,L.WAN_FIRE,L.WAN_COLD,L.WAN_LIGHTNING])for(const answer of [110,121,113]){reset();make('existing',L.DUST);input('new words');call('item',0,typ,3,1n,0);call('global',3,0n);opt(1,0);opt(3,answer);act(19);for(let turn=0;turn<30;turn++)if(act(34)===0n)break;}
// Interruption, real inventory ownership and marker exhaustion under occupation.
for(const spe of [1,2,10]){reset();call('item',0,L.MAGIC_MARKER,spe,1n,0);opt(1,0);input('This is a long written message');act(19);for(let turn=0;turn<8;turn++)if(act(34)===0n)break;}
// Save/restore actual nodes + leading-space pointer adjustments; stats output alias.
for(const mode of [L.WRITING,L.WRITING|L.FREEING,L.COUNTING|L.FREEING]){reset();make('  one',L.DUST,10,10);make('second',L.ENGRAVE,11,11);act(24,mode);if(!(mode&L.FREEING))act(24,L.FREEING);call('global',0,1234567890123n);act(25);act(26);assert.match(state(),/1234567890123/);}
// Native writes through record/text aliases and actual header debug semantics.
reset();make('saved text',L.ENGRAVE,10,10,null,9007199254740993n);opt(25,1);opt(26,1);act(24,L.WRITING);assert.match(state(),/9007199254740996/);assert.match(state(),/!aved text/);
reset();make('time alias',L.DUST,10,10,null,1152921504606846979n);opt(27,1);act(26);assert.match(state(),/e0:10,10,1,33,11,1,/);
reset();make('no erosion',L.DUST);call('global',4,27n);opt(16,1);act(7,10,10,0,0n);if(L.config_DEBUG){assert.match(trace(),/asked to erode 0 characters/);assert.match(state(),/g:100,0,0,0,27,/);}
reset();call('item',0,L.WAN_FIRE,1,1n,0);opt(1,0);opt(28,1);act(19);assert.match(trace(),/more_experienced:0:10;/);
// Defined early exits retain cleanup/return and avoid installing occupations.
for(const typ of [L.ALTAR,L.GRAVE]){reset();call('terrain',10,10,typ,0);act(19);}
reset();call('item',0,L.BLINDFOLD,1,1n,0);call('equipment',2,0);opt(1,0);act(19);
reset();call('prop',L.LEVITATION,1n,0n,0n);act(19);call('level',1,2,4);call('level',0,2,4);act(2,1);assert.equal(act(2,1),1n);
// Grave creation/relocation/sanity checks through original list and terrain code.
for(const supplied of [0,1]){reset();input('Rest here.');act(29,10,10,supplied);act(30,10,10);act(23);act(28);}
for(const stage of [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16]){
 reset();const before=modules.map(m=>m.HEAPU8.byteLength);opt(30,stage);opt(31,stage);
 if(stage===1){make('text',L.DUST);act(9,10,10);}else if(stage===2){make('text',L.ENGRAVE);act(9,10,10);}else if(stage===3){act(10,10,10,L.ENGRAVE);}else if(stage===4){make('text',L.DUST);opt(3,121);act(19);}else if(stage===8){call('item',0,L.DAGGER,0,3n,0);opt(1,0);act(19);act(34);}else if(stage===9){call('item',0,L.WAN_LIGHTNING,1,1n,0);opt(1,0);act(19);}else if(stage===10){act(0);}else if(stage===11){act(29,10,10,1);}else if(stage===12){call('item',0,L.WAN_NOTHING,-1,1n,0);opt(4,0);opt(1,0);act(19);}else if(stage===13){make('text',L.DUST);act(27);}else if(stage>=14){make('text',L.DUST);act(24,L.WRITING|L.FREEING);act(25);}else act(19);
 assert.match(trace(),/nested:/,'reentry stage '+stage);assert.match(trace(),new RegExp('grow:'+stage+';'));modules.forEach((m,i)=>assert.ok(m.HEAPU8.byteLength>before[i],'actual growth '+stage));
}
const other=await hf({nethackPorted:runtime});other._probe_reset();other._probe_action(10,10,10,L.DUST,0n);assert.notEqual(text(other,other._probe_snapshot()),state());assert.equal(C,undefined);
console.log(`ENGRAVE first-pass EmC: ${comparisons} exact comparisons passed; 34 original functions; native parity pending.`);
