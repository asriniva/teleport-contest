// First-pass configured Emscripten-C/JS differential; native/game/public pending.
import assert from 'node:assert/strict';
import {resolve} from 'node:path';
import {pathToFileURL} from 'node:url';
import * as core from '../js/ported/u_init.js';
import {createUInitBridge} from '../js/ported/u_init-runtime.js';
import {C} from '../js/ported/c-runtime.js';
const directory=resolve(process.env.U_INIT_PROBE_DIR??'.cache/tu-probes');
const referenceFactory=(await import(pathToFileURL(resolve(directory,'u_init-reference.mjs')))).default;
const hybridFactory=(await import(pathToFileURL(resolve(directory,'u_init-hybrid.mjs')))).default;
const text=(m,at)=>{at=Number(at);let end=at;while(m.HEAPU8[end])end++;return Buffer.from(m.HEAPU8.subarray(at,end)).toString('latin1');};
const layouts=m=>Object.fromEntries(Array.from({length:m._probe_layout_count()},(_,i)=>[text(m,m._probe_layout_name(i)),Number(m._probe_layout_value(i))]));
let comparisons=0,scenario='initial',bridge,modules,L,observe;
const dispatch=(services,name,...args)=>{const wrapped=observe?Object.assign(Object.create(services),{newhp(){observe(C);return services.newhp();}}):services;return bridge(wrapped,name,...args);};
async function pair(){const a=await referenceFactory();L=layouts(a);bridge??=createUInitBridge(L);const b=await hybridFactory({nethackPorted:{u_init:dispatch}});assert.deepEqual(layouts(b),L);comparisons++;modules=[a,b];reset();return modules;}
await pair();
function compare(){const states=modules.map(m=>({state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace())}));if(states[1].state!==states[0].state||states[1].trace!==states[0].trace){const a=states[0],b=states[1];for(const key of['state','trace'])if(a[key]!==b[key]){let p=0;while(a[key][p]===b[key][p]&&p<a[key].length)p++;console.error(scenario,key,'diff',p,JSON.stringify(a[key].slice(Math.max(0,p-90),p+250)),JSON.stringify(b[key].slice(Math.max(0,p-90),p+250)));}}assert.deepEqual(states[1],states[0],scenario);assert.equal(C,undefined);comparisons++;}
function call(name,...args){const saved=modules.map(m=>m._probe_stack()),values=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(values[1],values[0],scenario+' return');modules.forEach((m,i)=>assert.equal(m._probe_stack(),saved[i],scenario+' stack'));compare();return values[0];}
function reset(seed=1){modules.forEach(m=>m._probe_reset(seed));}
const invoke=(action,x=0,y=0)=>call('call',action,x,y),role=(r,race=0)=>call('role',r,race),option=(i,v)=>call('option',i,v),flags=(p=0,n=0,b=0,d=0)=>call('flags',p,n,b,d);
// An original routine initializes all private JS-owned data once per Module.
invoke(9);
const tables=Object.entries(core).filter(([,v])=>Array.isArray(v));assert.equal(tables.length,40);
for(let t=0;t<40;t++){
 const rows=modules[0]._probe_table_rows(t);assert.equal(modules[1]._probe_table_rows(t),rows);comparisons++;
 // Source order is retained in the generated metadata and data guard.
 const width=tables.find(([name])=>name===['Archeologist','Barbarian_0','Barbarian_1','Cave_man','Healer','Knight','Monk','Priest','Ranger','Rogue','Samurai','Tourist','Valkyrie','Wizard','Healing_book','Protection_book','Confuse_monster_book','Tinopener','Magicmarker','Lamp','Blindfold','Xtra_food','Leash','Towel','Wishing','Money','inv_subs','Skill_A','Skill_B','Skill_C','Skill_H','Skill_K','Skill_Mon','Skill_P','Skill_R','Skill_Ran','Skill_S','Skill_T','Skill_V','Skill_W'][t])[1][0].length;
 for(let row=0;row<rows;row++)for(let field=0;field<width;field++){assert.equal(modules[1]._probe_table_value(t,row,field),modules[0]._probe_table_value(t,row,field),`table${t}/${row}/${field}`);comparisons++;}
}
// Real complete object catalogue; all13 roles ×5 races ×3 deterministic RNG seeds.
for(let r=0;r<13;r++)for(let race=0;race<5;race++)for(const seed of[1,29,918273]){
 scenario=`full ${r}/${race}/${seed}`;reset(seed);role(r,race);invoke(0);invoke(1);invoke(2);invoke(1);invoke(2);
}
// Every role under pauper/nudist and discovery-starting-wish choices.
for(let r=0;r<13;r++)for(const [p,n,d]of[[1,0,0],[0,1,0],[1,1,1],[0,0,1]]){
 scenario=`conduct ${r}/${p}/${n}/${d}`;reset(r+33);role(r,r%5);flags(p,n,1,d);invoke(0);invoke(1);invoke(2);
}
// Every role/skill discipline, and source pauper skill-credit reset.
for(let r=0;r<13;r++){
 scenario='skills '+r;reset();role(r);invoke(9);
 for(const o of[L.SPE_FORCE_BOLT,L.SPE_HEALING,L.SPE_PROTECTION,L.SPE_POLYMORPH])invoke(10,o);
 flags(1);for(let skill=0;skill<L.P_NUM_SKILLS;skill++)call('skill',skill,skill%6,65535-skill);invoke(5);
}
// Birthday preserves the actual signed64 time_t bits, including values above53bits.
for(const clock of[0n,2147483648n,-2147483649n,9007199254740997n,-9007199254740997n,(1n<<63n)-1n,-(1n<<63n)]){
 scenario='clock '+clock;reset();call('clock',clock);flags(1,1,1);invoke(0);assert.ok(text(modules[0],modules[0]._probe_snapshot()).includes('birthday:'+clock+';'));
}
// Source struct copies must preserve64-bit roleplay counters and moves.
for(const value of[2147483648n,-2147483649n,9007199254740997n,-9007199254740997n,(1n<<63n)-1n,-(1n<<63n)]){
 scenario='roleplay/moves '+value;reset();call('long',0,value);call('long',1,value);call('long',2,value);
 observe=env=>{assert.equal(env.u.uroleplay.numbones,value);assert.equal(env.u.uroleplay.numrerolls,value);assert.equal(env.svm.moves,value);comparisons+=3;};invoke(0);observe=undefined;
}
// All equipment paths and magic-marker/charged-ring/container/poison adjustments.
const objects=[L.SMALL_SHIELD,L.HELMET,L.LEATHER_GLOVES,L.ROBE,L.CLOAK_OF_DISPLACEMENT,L.LEATHER_JACKET,L.ARROW,L.DAGGER,L.TIN_OPENER,L.FLINT,L.ROCK,L.SPE_HEALING,L.OIL_LAMP,L.SACK,L.MAGIC_MARKER,L.RIN_POLYMORPH_CONTROL,L.STATUE];
for(const typ of objects)for(const spe of[-128,-2,0,95,96,127])for(const bless of[0,1,2]){
 scenario=`object ${typ}/${spe}/${bless}`;reset(typ);call('object',typ,1,spe,1);call('align',spe%2?L.A_CHAOTIC:0);
 // Table class TOOL intentionally tests source stop behavior independently of object class.
 call('trop',0,typ,spe,L.TOOL_CLASS,3,6,bless);invoke(14);invoke(15);
}
// Explicit trquan, substitutions, no-inventory and filtered retry boundaries.
for(const [min,max]of[[0,0],[1,1],[3,9],[10,20]])for(const roll of[0,1,32767]){scenario='quantity';reset();call('trop',0,0,0,L.TOOL_CLASS,min,max,0);call('roll',roll);invoke(11);}
for(let race=0;race<5;race++)for(const typ of[L.DAGGER,L.SPEAR,L.SHORT_SWORD,L.BOW,L.ARROW,L.HELMET,L.SMALL_SHIELD,L.CRAM_RATION,L.LEMBAS_WAFER]){
 scenario='substitution';reset();role(0,race);call('object',typ,0,0,0);call('trop',0,0,0,L.TOOL_CLASS,1,1,0);option(7,1);invoke(13);
}
for(const banned of[L.WAN_WISHING,L.RIN_LEVITATION,L.POT_HALLUCINATION,L.POT_ACID,L.SCR_AMNESIA,L.SCR_FIRE,L.SCR_BLANK_PAPER,L.SPE_BLANK_PAPER,L.RIN_AGGRAVATE_MONSTER,L.RIN_HUNGER,L.WAN_NOTHING,L.SPE_NOVEL]){
 scenario='filter '+banned;reset();call('sequence',banned);call('sequence',L.PANCAKE);invoke(12,L.FOOD_CLASS);
}
scenario='1001 retry pancake';reset();for(let i=0;i<1001;i++)modules.forEach(m=>m._probe_sequence(L.WAN_WISHING));invoke(12,L.WAND_CLASS);
for(const [str,con,stuck]of[[0,0,0],[3,0,0],[0,4,0],[2,3,0],[0,0,1]]){scenario='carry';reset();option(0,str);option(1,con);option(2,stuck);invoke(6);}
// Coin quantities are full signed64 long, independently of number precision.
for(const money of[0n,1n,2147483648n,9007199254740997n,-9007199254740997n]){scenario='money '+money;reset();call('money',money);call('object',L.GOLD_PIECE,0,0,0);call('trop',0,L.GOLD_PIECE,0,L.COIN_CLASS,1,1,0);invoke(14);}
for(const kind of[8,9]){scenario=kind===8?'memory growth':'C reentry';reset();option(kind,1);const sizes=modules.map(m=>m.HEAPU8.byteLength);invoke(7,L.SACK,1);if(kind===8)modules.forEach((m,i)=>assert.ok(m.HEAPU8.byteLength>sizes[i]));}
// Controlled JS exception restores the dependency environment. An EM_JS throw
// bypasses the outer C probe frame epilogue, so its SP is not an equivalence check.
scenario='exception cleanup';reset();option(10,1);modules.forEach(m=>assert.throws(()=>m._probe_call(7,L.SACK,1),/U_INIT controlled panic/));assert.equal(C,undefined);compare();
// First original call reenters through a dependency after complete table materialization.
await pair();scenario='first-call C reentry';option(9,1);invoke(7,L.SACK,1);invoke(9);
// Source nudist continue advances without resetting its pending quantity.
scenario='nudist pending quantity';reset();flags(0,1);call('trop',0,L.LEATHER_JACKET,0,L.ARMOR_CLASS,3,3,0);call('trop',1,L.FOOD_RATION,0,L.FOOD_CLASS,1,1,0);call('trop',2,0,0,0,0,0,0);invoke(16);
// The public discovery pass follows the actual merged addinv return identity.
scenario='addinv merge identity';reset(777);role(12,1);option(11,1);invoke(1);invoke(2);invoke(1);invoke(2);
// Separate actual modules share one runtime bridge while private data stays local.
const old=modules;await pair();scenario='second Module';role(12,1);invoke(0);invoke(1);invoke(2);modules=old;reset(912);role(5,4);invoke(0);invoke(1);invoke(2);
console.log(`U_INIT: ${comparisons} configured Emscripten-C/JS comparisons passed; native/game/public gates pending.`);
