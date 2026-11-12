// Configured original-C versus imported JS; controlled foreign-world dependencies.
import assert from './native-test-assert.mjs';
import {resolve}from'node:path';import{pathToFileURL}from'node:url';
import{callSpell}from'../js/nethack/bindings/spell.js';import * as core from '../js/ported/spell.js';import{C,R,T}from'../js/c-runtime/context.js';
const dir=resolve(process.env.TELEPORT_SPELL_PROBE_DIR??'.cache/tu-probes'),path=k=>pathToFileURL(resolve(dir,(process.env.TELEPORT_SPELL_PROBE_DIR?'':'spell-')+k+'.mjs'));
const {default:rf}=await import(path('reference')),{default:hf}=await import(path('hybrid'));const reference=await rf();
function text(m,p){p=Number(p);if(!p)return null;let e=p;while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.slice(p,e)).toString('latin1');}
const L={};for(let i=0;i<reference._probe_layout_count();i++)L[text(reference,reference._probe_layout_name(i))]=Number(reference._probe_layout_value(i));
const runtime={spell:(services,name,...args)=>callSpell(new Proxy(services,{get(o,k,r){if(['rectState','trackState'].includes(k))return o[k];if(!Reflect.has(o,k))throw Error('Missing SPELL service '+String(k));return Reflect.get(o,k,r);}}),L,name,...args)};
const modules=[reference,await hf({nethackPorted:runtime})],stacks=modules.map(m=>m._probe_stack());let comparisons=0,context='';
const names=['spell_let_to_idx','cursed_book','confused_book','deadbook_pacify_undead','deadbook','book_cursed','learn','study_book','book_disappears','book_substitution','age_spells','rejectcasting','getspell','dowizcast','docast','spelltypemnemonic','spell_skilltype','skill_based_spellbook_id','propagate_chain_lightning','cast_chain_lightning','cast_protection','spell_backfire','spelleffects_check','spelleffects','spell_aim_step','can_center_spell_location','display_spell_target_positions','throwspell','tport_spell','losespells','spell_cmp','sortspells','spellsortmenu','dovspell','show_spells','dospellmenu','percent_success','spellretention','initialspell','known_spell','spell_idx','force_learn_spell','num_spells'],reached=new Set();
function snapshot(m){return{state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace()),result:text(m,m._probe_result()),chain:text(m,m._probe_chain_state())};}
function check(){assert.deepEqual(snapshot(modules[1]),snapshot(reference),context);modules.forEach((m,i)=>assert.equal(m._probe_stack(),stacks[i]));assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);comparisons++;}
function call(name,...args){const out=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(out[1],out[0],context+':'+name);check();return out[0];}
const obj=i=>m=>m._probe_obj(i),mon=i=>m=>m._probe_mon(i),buf=i=>m=>m._probe_buffer(i),cell=i=>m=>m._probe_int(i),chain=m=>m._probe_chain(),zap=m=>m._probe_zap();
const stringCache=new WeakMap();function str(t){return m=>{let cache=stringCache.get(m);if(!cache)stringCache.set(m,cache=new Map());let p=cache.get(t);const b=Buffer.from(t,'latin1');if(!p){p=m._malloc(BigInt(Math.max(8192,b.length+1)));cache.set(t,p);}m.HEAPU8.set(b,Number(p));m.HEAPU8[Number(p)+b.length]=0;return p;};}
function invoke(name,...args){context=name+' '+args.map(x=>typeof x==='function'?'pointer':String(x)).join(',');reached.add(name);const out=modules.map(m=>m._probe_invoke(names.indexOf(name),...Array.from({length:4},(_,i)=>typeof args[i]==='function'?BigInt(args[i](m)):BigInt.asUintN(64,BigInt(args[i]??0)))));check();return out;}
const reset=()=>call('reset'),opt=(k,v)=>call('option',k,v),field=(k,v)=>call('global',k,BigInt(v)),book=(i,id,lev=1,know=20000)=>call('spell',i,id,lev,know),item=(i,id,k=0,v=0)=>call('item',i,id,k,BigInt(v)),prop=(i,a=0n,b=0n,c=0n)=>call('property',i,BigInt(a),BigInt(b),BigInt(c)),trace=()=>snapshot(reference).trace,result=()=>snapshot(reference).result;
for(const m of modules)for(let i=0;i<m._probe_layout_count();i++)assert.equal(Number(m._probe_layout_value(i)),L[text(m,m._probe_layout_name(i))]);
assert.equal(reference._probe_table_count(),core.spl_sortchoices.length);core.spl_sortchoices.forEach((s,i)=>assert.equal(text(reference,reference._probe_table_text(i)),s));
for(const c of [-257,-128,-1,0,64,65,90,91,96,97,122,123,255,256,321]){reset();invoke('spell_let_to_idx',c);}
for(const id of [L.SPE_HEALING,L.SPE_MAGIC_MISSILE,L.SPE_CHAIN_LIGHTNING,L.SPE_BLANK_PAPER,L.SPE_BOOK_OF_THE_DEAD])for(const know of [0,1,2000,2001,20000,2147483647]){reset();book(0,id,3,know);invoke('num_spells');invoke('known_spell',id);invoke('spell_idx',id);invoke('spell_skilltype',id);invoke('force_learn_spell',id);invoke('age_spells');invoke('initialspell',obj(0));}
reset();for(let i=0;i<L.MAXSPELL;i++)book(i,L.SPE_HEALING,1,20000);item(0,L.SPE_MAGIC_MISSILE);invoke('initialspell',obj(0));invoke('force_learn_spell',L.SPE_MAGIC_MISSILE);assert.match(trace(),/Too many spells memorized/);invoke('num_spells');
for(const skill of [L.P_ATTACK_SPELL,L.P_HEALING_SPELL,L.P_DIVINATION_SPELL,L.P_ENCHANTMENT_SPELL,L.P_CLERIC_SPELL,L.P_ESCAPE_SPELL,L.P_MATTER_SPELL,-1]){reset();invoke('spelltypemnemonic',skill);}
for(const skill of [L.P_ISRESTRICTED,L.P_UNSKILLED,L.P_BASIC,L.P_SKILLED,L.P_EXPERT])for(const know of [-1,0,1,199,200,201,499,500,19999,20000,2147483647]){reset();book(0,L.SPE_HEALING,1,know);call('skill',L.P_HEALING_SPELL,skill);invoke('spellretention',0,buf(0));}
for(const seed of [1,2,3,5,8,13,21,34,55])for(const resistant of [0,1]){reset();call('seed',seed);opt(0,1);prop(L.POISON_RES,BigInt(resistant));prop(L.ANTIMAGIC,BigInt(resistant));item(0,L.SPE_CHAIN_LIGHTNING);invoke('cursed_book',obj(0));}
for(const seed of [1,2,3])for(const id of [L.SPE_HEALING,L.SPE_BOOK_OF_THE_DEAD]){reset();call('seed',seed);item(0,id);invoke('confused_book',obj(0));}
for(const bless of [-1,0,1])for(const invocation of [0,1])for(const primed of [0,1]){reset();item(0,L.SPE_BOOK_OF_THE_DEAD,bless<0?1:0,Math.abs(bless));opt(7,invocation);field(24,1);field(25,1);item(1,L.CANDELABRUM_OF_INVOCATION,5,primed?7:0);item(1,L.CANDELABRUM_OF_INVOCATION,6,1);item(2,L.BELL_OF_OPENING,7,99);call('link',1,2);field(27,1);invoke('deadbook',obj(0));}
reset();opt(7,1);item(0,L.SPE_BOOK_OF_THE_DEAD);item(1,L.CANDELABRUM_OF_INVOCATION,5,7);item(1,L.CANDELABRUM_OF_INVOCATION,6,1);item(2,L.BELL_OF_OPENING,7,9007199254740993n);field(28,9007199254740994n);call('link',1,2);field(27,1);field(24,1);field(25,1);invoke('deadbook',obj(0));assert.match(trace(),/mkinvokearea:/,'exact recent bell age above2^53');
for(const pm of [L.PM_HUMAN,L.PM_VAMPIRE,L.PM_MASTER_LICH]){reset();call('monset',0,pm,0,0);invoke('deadbook_pacify_undead',mon(0));}
for(const id of [L.SPE_HEALING,L.SPE_MAGIC_MISSILE,L.SPE_BLANK_PAPER,L.SPE_BOOK_OF_THE_DEAD,L.SPE_NOVEL])for(const blessed of [0,1])for(const confused of [0,1]){reset();item(0,id,0,blessed);prop(L.CONFUSION,BigInt(confused));invoke('study_book',obj(0));field(13,0);invoke('learn');invoke('book_cursed',obj(0));invoke('book_substitution',obj(0),obj(1));invoke('book_disappears',obj(1));}
for(const before of [0n,1n,9007199254740993n])for(const prior of [0,1]){reset();item(0,L.SPE_NOVEL);opt(6,1);field(34,before);field(35,prior);invoke('study_book',obj(0));assert.match(trace(),/read_tribute:/,'original novel branch');}
for(const answer of [110,121]){reset();item(0,L.SPE_HEALING);book(0,L.SPE_HEALING,1,20000);opt(19,answer);invoke('study_book',obj(0));assert.match(trace(),/yn_function:/,'original memory-refresh prompt');}
for(const other of [0,1]){reset();item(0,L.SPE_HEALING,0,1);invoke('study_book',obj(0));item(0,L.SPE_HEALING,1,1);if(other)field(36,1);call('clear');invoke('book_cursed',obj(0));if(other)assert.doesNotMatch(trace(),/stop_occupation:/);else assert.match(trace(),/stop_occupation:/,'live occupation identity');}
for(const old of [-1,0])for(const next of [-1,0,1]){reset();if(old===0)field(13,0);invoke('book_substitution',obj(old),obj(next));invoke('book_disappears',obj(next));}
for(const delay of [-128,-5,-1,0,1,127])for(const known of [0,1]){reset();item(0,L.SPE_HEALING,3,4);field(13,0);field(12,delay);if(known)book(0,L.SPE_HEALING);invoke('learn');}
for(const impaired of [L.STUNNED,L.CONFUSION]){reset();prop(impaired,1n);invoke('rejectcasting');}
for(const yes of [0,1]){reset();opt(2,yes);opt(3,yes);invoke('rejectcasting');}
for(const key of [0,27,97,98,42,63,122]){reset();book(0,L.SPE_HEALING);field(9,L.MENU_TRADITIONAL);opt(19,key);invoke('getspell',cell(0));}
for(const count of [0,2,26,27,L.MAXSPELL]){reset();for(let i=0;i<count;i++)book(i,L.SPE_DIG+i,1,20000);field(9,L.MENU_TRADITIONAL);opt(19,count<27?97+Math.max(0,count-1):65+count-27);invoke('getspell',cell(0));if(count)assert.equal(reference._probe_intvalue(0),count-1);}
for(const key of [97,98,65,27]){reset();book(0,L.SPE_HEALING);opt(24,1);opt(25,L.CMDQ_KEY);opt(26,key);invoke('getspell',cell(0));}
for(const force of [0,1]){reset();book(0,L.SPE_HEALING);opt(20,1);opt(22,force?L.SPE_HEALING:1);invoke(force?'dowizcast':'docast');}
reset();invoke('skill_based_spellbook_id');field(0,L.PM_MONK);invoke('skill_based_spellbook_id');
for(const mode of [0,1,2,3,4]){reset();book(0,L.SPE_HEALING);invoke('tport_spell',mode);invoke('tport_spell',mode===1?3:mode===2?4:0);}
for(const confused of [0,1])for(const seed of [1,2,7,42]){reset();for(let i=0;i<5;i++)book(i,L.SPE_DIG+i,i+1,20000);prop(L.CONFUSION,BigInt(confused));call('seed',seed);invoke('losespells');}
for(const sort of [0,1,2,3,4,5,6,7,8]){reset();for(let i=0;i<6;i++)book(i,L.SPE_DIG+5-i,i%3+1,20000);field(8,sort);invoke('sortspells');invoke('spell_cmp',cell(0),cell(1));}
reset();for(let i=0;i<6;i++)book(i,L.SPE_DIG+5-i,i%3+1,20000);field(8,1);invoke('sortspells');field(8,8);invoke('sortspells');assert.match(snapshot(reference).state,/sort:0;/,'retained sort commits copied records');
for(const tab of [0,1])for(const wiz of [0,1])for(const action of [-3,-2,-1,0]){reset();book(0,L.SPE_HEALING);book(1,L.SPE_MAGIC_MISSILE);field(10,tab);field(11,wiz);invoke('dospellmenu',str('Spells'),action,cell(0));}
reset();book(0,L.SPE_HEALING);book(1,L.SPE_MAGIC_MISSILE);opt(20,2);opt(60,2);opt(61,1);invoke('dovspell');assert.match(snapshot(reference).state,new RegExp('s0:'+L.SPE_MAGIC_MISSILE+','),'actual menu swap path');
reset();for(let i=0;i<3;i++)book(i,L.SPE_DIG+i);opt(20,1);opt(21,2);opt(22,2);opt(23,3);invoke('dospellmenu',str('Spells'),1,cell(0));assert.equal(reference._probe_intvalue(0),2,'skip native preselected entry');
for(const count of [0,1,2]){reset();book(0,L.SPE_HEALING);book(1,L.SPE_MAGIC_MISSILE);opt(20,count?1:0);opt(21,count);opt(22,2);opt(23,3);invoke('spellsortmenu');invoke('dovspell');invoke('show_spells');}
for(const level of [1,2,3,7,15,30])for(const skill of [L.P_UNSKILLED,L.P_BASIC,L.P_SKILLED,L.P_EXPERT])for(const stat of [3,10,18,25]){reset();field(1,level);opt(1,stat);book(0,L.SPE_HEALING,3,20000);call('skill',L.P_HEALING_SPELL,skill);invoke('percent_success',0);invoke('cast_protection');}
for(const role of [L.PM_WIZARD,L.PM_KNIGHT])for(const cloak of [0,1])for(const id of [L.SPE_HEALING,L.SPE_PROTECTION]){reset();field(0,role);field(15,3);field(16,-4);field(17,5);field(18,9);book(0,id,3,20000);for(const[i,typ,slot]of [[0,L.PLATE_MAIL,1],[1,L.ROBE,2],[2,L.LARGE_SHIELD,6],[3,L.HELMET,3],[4,L.GAUNTLETS_OF_POWER,4],[5,L.IRON_SHOES,5],[6,L.QUARTERSTAFF,0]]){item(i,typ);if(i!==1||cloak)call('equipment',slot,i);}opt(13,100);invoke('percent_success',0);}
for(const know of [0,1,100,500,1000,2000,20000])for(const energy of [0,4,5,20,200]){reset();book(0,L.SPE_HEALING,1,know);field(2,energy);invoke('spelleffects_check',0,cell(0),cell(1));}
for(const know of [0,20000])for(const energy of [0,200]){reset();book(0,L.SPE_HEALING,1,know);field(2,energy);invoke('spelleffects_check',0,cell(0),cell(0));}
reset();invoke('spelleffects_check',L.UNKNOWN_SPELL,cell(0),cell(1));
for(let id=L.SPE_DIG;id<L.SPE_BLANK_PAPER;id++){reset();book(0,id,Math.max(1,Number(1)),20000);invoke('spelleffects',id,1,1);}
for(const force of [-257,-1,0,1,256,257]){reset();book(0,L.SPE_HEALING,1,20000);invoke('spelleffects',L.SPE_HEALING,1,force);}
for(const seed of [1,2,7,42]){reset();call('seed',seed);book(0,L.SPE_HEALING,7,0);invoke('spell_backfire',0);}
for(const x of [0,1,10,11,21,79])for(const typ of [L.ROOM,L.STONE,L.DOOR,L.POOL]){reset();call('terrain',11,10,typ,L.D_CLOSED);invoke('spell_aim_step',0,x,10);invoke('can_center_spell_location',x,10);}
reset();for(const flag of [0,1,256,257])invoke('display_spell_target_positions',flag);opt(50,1);invoke('throwspell');
for(const dir of [0,1,7,255])for(const strength of [0,1,2,3]){reset();call('zapset',dir,10,10,strength,0);if(dir<8)invoke('propagate_chain_lightning',chain,zap);}
for(const tail of [99,100]){reset();call('zapset',0,10,10,3,tail);invoke('propagate_chain_lightning',chain,zap);}
reset();invoke('cast_chain_lightning');
// Production occupation uses a genuine native function pointer into the original JS body.
reset();item(0,L.SPE_HEALING,0,1);invoke('study_book',obj(0));field(12,0);call('occupation');assert.match(trace(),/occupation:studying:/);
// Every growth stage must reach its real native callback and reenter the JS TU.
for(let stage=1;stage<=16;stage++){
 reset();opt(80,stage);opt(81,stage);const before=modules.map(m=>m.HEAPU8.byteLength);
 if(stage===1)invoke('cursed_book',obj(0));
 else if(stage===2){item(0,L.SPE_NOVEL);opt(6,1);invoke('study_book',obj(0));}
 else if(stage===3)invoke('confused_book',obj(0));
 else if(stage===4){field(13,0);invoke('learn');}
 else if(stage===5)invoke('deadbook',obj(0));
 else if(stage===6){item(0,L.SPE_BOOK_OF_THE_DEAD,1,1);invoke('deadbook',obj(0));assert.match(trace(),/makemon:/);}
 else if(stage===7||stage===8||stage===11){if(stage===11)opt(30,1);invoke('spelleffects',L.SPE_HEALING,1,1);}
 else if(stage===9){book(0,L.SPE_HEALING);opt(20,1);invoke('dospellmenu',str('Spells'),-2,cell(0));}
 else if(stage===10){book(0,L.SPE_HEALING);opt(24,1);opt(25,L.CMDQ_KEY);opt(26,97);invoke('getspell',cell(0));}
 else if(stage===12){opt(32,2);invoke('cast_chain_lightning');assert.match(trace(),/zhitm:/);}
 else if(stage===13||stage===14)invoke('throwspell');
 else if(stage===15){item(0,L.SPE_BOOK_OF_THE_DEAD,0,1);call('monset',0,L.PM_MASTER_LICH,0,0);invoke('deadbook',obj(0));assert.match(trace(),/iter:0;/);}
 else if(stage===16){item(0,L.SPE_HEALING,0,1);invoke('study_book',obj(0));}
 assert.match(trace(),/nested:/,'native reentry stage '+stage);assert.match(trace(),new RegExp('grow:'+stage+';'),'native growth stage '+stage);modules.forEach((m,i)=>assert.ok(m.HEAPU8.byteLength>before[i],'actual growth stage '+stage));
}
// Interleave saved teleport records between two actual native/hybrid Module pairs.
const others=[await rf(),await hf({nethackPorted:runtime})];
for(const m of modules){m._probe_reset();m._probe_spell(0,L.SPE_TELEPORT_AWAY,3,1111);m._probe_invoke(names.indexOf('tport_spell'),1n,0n,0n,0n);}
for(const m of others){m._probe_reset();m._probe_spell(0,L.SPE_TELEPORT_AWAY,6,2222);m._probe_invoke(names.indexOf('tport_spell'),1n,0n,0n,0n);}
for(const m of modules)m._probe_invoke(names.indexOf('tport_spell'),3n,0n,0n,0n);
check();assert.match(snapshot(reference).state,/s0:\d+,3,1111,/);
for(const m of others)m._probe_invoke(names.indexOf('tport_spell'),3n,0n,0n,0n);
assert.deepEqual(snapshot(others[1]),snapshot(others[0]));assert.match(snapshot(others[0]).state,/s0:\d+,6,2222,/);
assert.deepEqual([...reached].sort(),names.slice().sort());
console.log(`SPELL first-pass EmC: ${comparisons} exact comparisons passed; all 43 original functions; native/shared/public pending.`);
