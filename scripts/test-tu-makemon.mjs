// Actual configured original MAKEMON versus JS; dungeon/world callbacks controlled.
import assert from './native-test-assert.mjs';
import {readFileSync,writeFileSync} from 'node:fs';
import {resolve} from 'node:path';
import {pathToFileURL} from 'node:url';
import {callMakemon} from '../js/nethack/bindings/makemon.js';
import * as core from '../js/ported/makemon.js';
import {C,R,T} from '../js/c-runtime/context.js';
if(process.env.TELEPORT_NATIVE_TESTS==='1')throw Error('MAKEMON native-host gate pending; original configured EmC first-pass only.');
const dir=resolve(process.env.TELEPORT_MAKEMON_PROBE_DIR??'.cache/makemon-author');
const {default:rf}=await import(pathToFileURL(resolve(dir,'reference.mjs'))),{default:hf}=await import(pathToFileURL(resolve(dir,'hybrid.mjs')));
const reference=await rf(),L={};
const text=(m,p)=>{let i=Number(p);if(!i)return null;let e=i;while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.subarray(i,e)).toString('latin1');};
for(let i=0;i<reference._probe_layout_count();i++)L[text(reference,reference._probe_layout_name(i))]=Number(reference._probe_layout_value(i));
const entered=new Set();const runtime={makemon:(services,name,...args)=>{entered.add(name);return callMakemon(services,L,name,...args);}};
const modules=[reference,await hf({nethackPorted:runtime})],stacks=modules.map(m=>m._probe_stack());let comparisons=0,context='initial';
const snapshot=m=>({state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace())});
function check(){const actual=snapshot(modules[1]),expected=snapshot(reference);if(actual.state!==expected.state||actual.trace!==expected.trace){writeFileSync(resolve(dir,'failure-'+Date.now()+'.json'),JSON.stringify({context,actual,expected},null,2));for(const k of ['state','trace'])if(actual[k]!==expected[k]){let i=0;while(actual[k][i]===expected[k][i])i++;console.error(context,k,'first difference',i,'actual',actual[k].slice(i,i+160),'expected',expected[k].slice(i,i+160));}}assert.ok(actual.state===expected.state&&actual.trace===expected.trace,context);for(let i=0;i<2;i++)assert.equal(modules[i]._probe_stack(),stacks[i],context+':stack');assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);comparisons++;}
function call(name,...args){const out=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(out[1],out[0],context+':'+name);check();return out[0];}
const reset=()=>call('reset'),opt=(n,v)=>call('option',n,v),g=(n,v)=>call('global',n,BigInt(v)),act=(op,a=0,b=0,c=0,n=0n)=>call('action',op,a,b,c,BigInt(n)),mon=(pm,lev=5,hp=20,flags=0,i=0)=>call('monster_setup',i,pm,lev,hp,flags);
for(const m of modules)for(let i=0;i<m._probe_layout_count();i++)assert.equal(Number(m._probe_layout_value(i)),L[text(m,m._probe_layout_name(i))]);
// Direct original entrypoint reachability; this is not branch-completeness evidence.
for(let op=0;op<41;op++){context='entry:'+op;reset();let a=L.PM_HUMAN,b=0,c=0,n=0n;if([2,13,39,40].includes(op))a=1;if(op===3){a=L.ORCISH_ARROW;b=7;}if(op===5)n=9007199254740993n;if(op===7){a=11;b=10;}if(op===8){b=1;}if(op===14){b=12;c=10;n=BigInt(L.NO_MINVENT|L.MM_NOGRP);}if(op===17){a=1;b=L.PM_HUMAN;c=1;}if(op===24){b=L.PM_ORC;}if([27,28,29].includes(op)){a=L.S_ORC;b=0;c=L.A_NONE;}if(op===32)a=L.DAGGER;if(op===33)a=L.PM_IRON_GOLEM;if(op===39){a=L.BAG_OF_TRICKS;b=0;}if(op===40)a=2;act(op,a,b,c,n);}
// Actual monster table supplies every configured species/type and class field.
for(let pm=L.LOW_PM;pm<L.NUMMONS;pm++){context='species:'+pm;reset();mon(pm);for(const op of[0,1,9,10,16,18,20,23,30,33,34,35])act(op,pm);}
for(const seed of[1,2,7,42])for(const pm of[L.PM_HUMAN,L.PM_ELF,L.PM_ORC,L.PM_WATCHMAN,L.PM_SOLDIER,L.PM_CAPTAIN,L.PM_ANGEL,L.PM_PIT_FIEND,L.PM_DWARF,L.PM_ETTIN,L.PM_NAZGUL,L.PM_KOBOLD,L.PM_PLAINS_CENTAUR,L.PM_MINOTAUR]){context='inventory:'+pm+':'+seed;reset();call('seed',seed);mon(pm,15);act(4);act(6);}
for(const amount of[0n,1n,2147483651n,9007199254740993n]){context='money:'+amount;reset();act(5,0,0,0,amount);}
for(const pm of[L.PM_ERINYS,L.PM_NAZGUL,L.PM_WIZARD_OF_YENDOR,L.PM_HIGH_CLERIC,L.PM_HUMAN])for(const born of[0,2,3,8,9,119,120,254,255])for(const flags of[0,L.G_GENOD,L.G_EXTINCT]){context='propagate:'+pm+':'+born+':'+flags;reset();call('vital',pm,born,0,flags);act(8,pm,1,0);act(18,pm);}
for(const pm of[L.PM_STRAW_GOLEM,L.PM_RED_DRAGON,L.PM_DEATH,L.PM_KILLER_BEE,L.PM_HUMAN])for(const lev of[0,1,5,49,127]){context='hp:'+pm+':'+lev;reset();mon(pm,lev,1);act(9);act(10,pm);}
for(const alignment of[L.A_CHAOTIC,L.A_NEUTRAL,L.A_LAWFUL,L.A_NONE])for(const record of[-20,-15,-1,0,20]){context='peace:'+alignment+':'+record;reset();g(3,alignment);g(4,record);for(const pm of[L.PM_HUMAN,L.PM_ANGEL,L.PM_ERINYS,L.PM_ORC,L.PM_KOBOLD]){mon(pm);act(34,pm);act(35);}}
for(const cls of[L.S_ORC,L.S_DEMON,L.S_LICH,L.S_GOLEM,L.S_HUMAN,0,L.MAXMCLASSES])for(const seed of[1,7,42]){context='class:'+cls+':'+seed;reset();call('seed',seed);act(25);act(27,cls);act(28,cls,L.G_IGNORE,L.A_CHAOTIC);act(29,cls);}
for(const pm of[L.PM_HUMAN,L.PM_ORC,L.PM_GIANT_SPIDER,L.PM_LARGE_MIMIC,L.PM_LONG_WORM,L.PM_WIZARD_OF_YENDOR,L.PM_ANGEL])for(const flags of[L.NO_MINVENT|L.MM_NOGRP,L.NO_MM_FLAGS,L.MM_ANGRY|L.MM_FEMALE|L.MM_NOGRP]){context='create:'+pm+':'+flags;reset();act(14,pm,12,10,BigInt(flags));}
for(const typ of[L.ROOM,L.DOOR,L.HWALL,L.CORR,L.POOL,L.LAVAPOOL]){context='mimic:'+typ;reset();mon(L.PM_LARGE_MIMIC);call('square',10,10,typ,0);act(38);}
for(const grow of[0,1])for(const pm of[L.PM_KILLER_BEE,L.PM_LITTLE_DOG,L.PM_KITTEN,L.PM_HUMAN,L.PM_STRAW_GOLEM]){context='grow:'+pm+':'+grow;reset();mon(pm,1,8);act(31,grow);}
for(const aliases of[0,1]){context='callback-growth-reentry:'+aliases;reset();opt(90,1);opt(91,aliases);mon(L.PM_ANGEL,20);act(4);act(6);act(14,L.PM_HUMAN,12,10,BigInt(L.MM_NOGRP|L.NO_MINVENT));}
// Real elemental-level predicates, survival rejection and home-elemental HP.
for(const plane of[1,2,3,4,5])for(const pm of[L.PM_AIR_ELEMENTAL,L.PM_FIRE_ELEMENTAL,L.PM_EARTH_ELEMENTAL,L.PM_WATER_ELEMENTAL,L.PM_RED_DRAGON,L.PM_HUMAN,L.PM_GHOST,L.PM_FLOATING_EYE]){context='planes:'+plane+':'+pm;reset();call('planes');g(0,8);g(1,plane);mon(pm);act(0,pm);act(1,pm);act(10,pm);act(20,pm);}
// Defined unsigned field wrap and bitfield assignment results stay native.
for(const level of[0,49,50,127,254,255]){context='grow-width:'+level;reset();mon(L.PM_LITTLE_DOG,level,20);opt(12,L.PM_DOG);act(31,0);}
for(const worm of[0,1,31,32,63,64]){context='worm-bit-width:'+worm;reset();opt(15,worm);act(14,L.PM_LONG_WORM,12,10,BigInt(L.MM_NOGRP|L.NO_MINVENT));}
// Header ifdebug preserves last_msg through an observing/mutating UI callback.
context='debug-header-origin';reset();g(8,1);opt(11,1);opt(95,1);call('vital',L.PM_GOBLIN,L.MAXMONNO-1,0,0);act(8,L.PM_GOBLIN,1,0);call('vital',L.PM_GOBLIN,0,0,L.G_EXTINCT);act(14,L.PM_GOBLIN,12,10,BigInt(L.NO_MINVENT|L.MM_NOGRP));
// Growth naming/error messages preserve callback evaluation and typed varargs.
for(const visible of[0,1])for(const genocide of[0,1]){context='grow-message:'+visible+':'+genocide;reset();mon(L.PM_LITTLE_DOG,4,20,2);opt(12,L.PM_DOG);opt(16,visible);call('vital',L.PM_DOG,0,0,genocide?L.G_GENOD:0);act(31,0);}
// Both forward success exits and the exhausted search keep one original shared tail.
for(const blind of[0,1])for(const valid of[0,1]){context='fallback:'+blind+':'+valid;reset();g(21,blind);opt(5,valid?79:80);opt(6,20);act(13,1,L.GP_CHECKSCARY);}
// Original mimic shared-tail selection, exact shop classes and native object aliases.
for(const roomType of[L.OROOM,L.ZOO,L.VAULT,L.DELPHI,L.TEMPLE,L.SHOPBASE,L.FODDERSHOP])for(const seed of[1,2,7,42,314159])for(const shop of[-L.CORPSE,L.RANDOM_CLASS,L.MAXOCLASSES+1,L.WEAPON_CLASS]){context='mimic-room:'+roomType+':'+seed+':'+shop;reset();call('seed',seed);mon(L.PM_LARGE_MIMIC);call('room',0,roomType);call('square',10,10,L.ROOM,L.ROOMOFFSET);opt(14,shop);opt(28,1);g(1,20);act(38);}
for(const type of[L.STATUE,L.CORPSE,L.EGG,L.TIN,L.SLIME_MOLD,L.BOULDER]){context='mimic-map-object:'+type;reset();mon(L.PM_LARGE_MIMIC);call('map_object',10,10,type);act(38);call('map_object',10,10,L.BOULDER);act(38);}
for(const algn of[L.AM_NONE,L.AM_CHAOTIC,L.AM_NEUTRAL,L.AM_LAWFUL]){context='align-cache:'+algn;reset();opt(8,1);g(10,algn);g(9,1000+algn);act(19,L.PM_HUMAN);act(19,L.PM_ANGEL);opt(8,0);g(10,L.AM_NONE);act(19,L.PM_ANGEL);g(9,2000+algn);act(19,L.PM_ANGEL);}
for(const seen of[0,1])for(const charge of[0,1,3]){context='bag-output:'+seen+':'+charge;reset();opt(16,seen);act(39,L.BAG_OF_TRICKS,charge,7,1n);}
context='controlled-C-unwind';reset();opt(93,1);mon(L.PM_ANGEL,20);assert.equal(act(4),-999n);opt(93,0);act(33,L.PM_IRON_GOLEM);
context='callback-write-alias';reset();opt(90,1);opt(91,1);opt(92,1);mon(L.PM_ANGEL,20);act(4);act(6);
// A second pair has independent TU arrays/caches/literal storage and live memories.
const isolatedReference=await rf(),isolatedHybrid=await hf({nethackPorted:runtime});
for(const m of[isolatedReference,isolatedHybrid]){m._probe_reset();m._probe_seed(314159);m._probe_action(25,0,0,0,0n);m._probe_action(27,L.S_ORC,0,0,0n);}
assert.deepEqual(snapshot(isolatedHybrid),snapshot(isolatedReference),'independent Module state');assert.equal(C,undefined);comparisons++;
const expected=Object.entries(core).filter(([,v])=>typeof v==='function').map(([k])=>k).sort();assert.deepEqual([...entered].sort(),expected,'all configured entrypoints imported/reached');
writeFileSync(resolve(dir,'summary.json'),JSON.stringify({status:'PASS',comparisons,entered:[...entered].sort(),reference:'actual configured original memory64 C',scope:'41 entrypoints reached; controlled foreign world; not all branches; native-host/production/public pending'},null,2));
console.log(`MAKEMON PASS ${comparisons} original C/hybrid comparisons; ${entered.size} configured entrypoints reached.`);
