import './pure-js-probes/deny-wasm.mjs';
import {referenceLabelFor as fixtureReferenceLabelFor} from './native-test-backend.mjs';
const fixtureReferenceLabel=fixtureReferenceLabelFor("potion");
import {createProbe,createReference,loadFixture,fixtureImports} from './pure-js-fixtures/load.mjs';
import {DataView as FixtureDataView,Int32Array as FixtureInt32Array} from './native-test-backend.mjs';
import {DataView,Int32Array,referenceBackend,assertStackRestored,assertMemoryGrowth} from './native-test-backend.mjs';
import assert from './native-test-assert.mjs';
import {readFileSync}from'node:fs';import {resolve}from'node:path';import {pathToFileURL}from'node:url';
import {callPotion,createPotionEnvironment}from'../js/nethack/bindings/potion.js';import * as core from'../js/ported/potion.js';import {C,R,T}from'../js/c-runtime/context.js';
const author=process.env.TELEPORT_POTION_PROBES,dir=author?pathToFileURL(resolve(author)+'/'):new URL('../.cache/tu-probes/',import.meta.url),referenceFactory=(await loadFixture("potion",new URL('potion-reference.mjs',dir))).default,hybridFactory=(await loadFixture("potion",new URL('potion-hybrid.mjs',dir))).default,ref=await referenceBackend('potion',referenceFactory)();
function text(m,p){if(!p)return null;let q=Number(p),end=q;while(m.HEAPU8[end])end++;return Buffer.from(m.HEAPU8.slice(q,end)).toString();}
const L={size:Number(ref._probe_context_size())};for(let i=0;i<ref._probe_layout_count();i++){const k=text(ref,ref._probe_layout_name(i)),v=ref._probe_layout_value(i);L[k]=/^(M1_|M2_|W_)/.test(k)?BigInt.asUintN(64,v).toString():Number(BigInt.asIntN(64,v));}
if(!author)assert.deepEqual(L,JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url))).potion);
const runtime={potion:(services,name,...args)=>callPotion(services,L,name,...args)},mods=[ref,await hybridFactory({nethackPorted:runtime})],stacks=mods.map(m=>m._probe_stack()),names=["itimeout", "itimeout_incr", "set_itimeout", "incr_itimeout", "make_confused", "make_stunned", "make_sick", "make_slimed", "make_stoned", "make_vomiting", "make_blinded", "toggle_blindness", "make_hallucinated", "make_deaf", "make_glib", "self_invis_message", "ghost_from_bottle", "drink_ok", "dodrink", "dopotion", "peffect_restore_ability", "peffect_hallucination", "peffect_water", "peffect_booze", "peffect_enlightenment", "peffect_invisibility", "peffect_see_invisible", "peffect_paralysis", "peffect_sleeping", "peffect_monster_detection", "peffect_object_detection", "peffect_sickness", "peffect_confusion", "peffect_gain_ability", "peffect_speed", "peffect_blindness", "peffect_gain_level", "peffect_healing", "peffect_extra_healing", "peffect_full_healing", "peffect_levitation", "peffect_gain_energy", "peffect_oil", "peffect_acid", "peffect_polymorph", "peffects", "healup", "strange_feeling", "bottlename", "H2Opotion_dip", "impact_arti_light", "potionhit", "potionbreathe", "mixtype", "dip_ok", "dip_hands_ok", "hold_potion", "dodip", "dip_into", "poof", "dip_potion_explosion", "potion_dip", "mongrantswish", "djinni_from_bottle", "split_mon", "speed_up"],returns=[
  "Can_rise_up",
  "Monnam",
  "Sting_effects",
  "The",
  "Tobjnam",
  "Yname2",
  "Yobjnam2",
  "a_monnam",
  "adjattrib",
  "aggravate",
  "alter_cost",
  "an",
  "aobjnam",
  "bhitm",
  "bless",
  "body_part",
  "burn_away_slime",
  "can_reach_floor",
  "canseemon",
  "ceiling",
  "check_unpaid",
  "clone_mon",
  "cloneu",
  "cmdq_peek",
  "costly_alteration",
  "curse",
  "cxname",
  "dealloc_killer",
  "dealloc_obj",
  "delayed_killer",
  "depth",
  "dipfountain",
  "dipsink",
  "dmgtype",
  "do_enlightenment_effect",
  "doname",
  "doup",
  "drinkfountain",
  "drinksink",
  "eatmupdate",
  "enlightenment",
  "erode_obj",
  "exercise",
  "explode",
  "explode_oil",
  "fall_asleep",
  "find_delayed_killer",
  "fingers_or_gloves",
  "fire_damage",
  "fix_petrification",
  "fixup_oil",
  "float_up",
  "float_vs_flight",
  "floating_above",
  "freeinv",
  "fruitname",
  "glyph_at",
  "goto_level",
  "hard_helmet",
  "hcolor",
  "heal_legs",
  "healmon",
  "hliquid",
  "hold_another_object",
  "in_rooms",
  "inaccessible_equipment",
  "killed",
  "learn_unseen_invent",
  "ledger_no",
  "losehp",
  "makemon",
  "makeplural",
  "makewish",
  "map_invisible",
  "mcureblindness",
  "mkobj",
  "mksobj",
  "mon_adjust_speed",
  "mon_hates_blessings",
  "mon_nam",
  "mon_set_minvis",
  "mongone",
  "monkilled",
  "monster_detect",
  "monstseesu",
  "monstunseesu",
  "more_experienced",
  "near_capacity",
  "new_were",
  "newsym",
  "newuhs",
  "nomul",
  "obfree",
  "obj_extract_self",
  "obj_resists",
  "obj_unpolyable",
  "objdescr_is",
  "object_detect",
  "observe_object",
  "otense",
  "paralyze_monst",
  "permapoisoned",
  "pluslvl",
  "poisontell",
  "poly_obj",
  "polyself",
  "prinv",
  "remove_worn_item",
  "resist",
  "rider_cant_reach",
  "rndexp",
  "rndmonnam",
  "see_monsters",
  "see_objects",
  "see_traps",
  "set_bc",
  "set_malign",
  "set_mimic_blocking",
  "set_ulycn",
  "shop_keeper",
  "simpleonames",
  "sleep_monst",
  "slept_monst",
  "splitobj",
  "spoteffects",
  "stagger",
  "stairway_at",
  "stolen_value",
  "subfrombill",
  "surface",
  "swallowed",
  "tamedog",
  "the",
  "thesimpleoname",
  "tmp_at",
  "trycall",
  "unfixable_trouble_count",
  "unmap_object",
  "update_inventory",
  "useup",
  "useupall",
  "vision_recalc",
  "vtense",
  "wake_nearto",
  "wakeup",
  "wash_hands",
  "water_damage",
  "waterbody_name",
  "which_armor",
  "x_monnam",
  "xname",
  "yname",
  "you_unwere",
  "you_were",
  "unbless",
  "uncurse",
  "uasmon_maxStr",
  "defended",
  "undiscovered_artifact",
  "Resists_Elem",
  "sensemon",
  "discover_object"
],bits={"mon": ["mblinded", "mcanmove", "mcansee", "mconf", "minvis", "mpeaceful", "msleeping"], "you": ["uinwater", "usick_type", "uswallow"], "prop": [], "obj": ["bknown", "blessed", "cursed", "dknown", "in_use", "lamplit", "oeroded", "oeroded2", "otrapped", "pickup_prev", "unpaid"], "colors": [], "iflags": [], "strings": [], "conduct": [], "flags": [], "topology": [], "gv": [], "svm": [], "role": [], "cls": ["oc_magic", "oc_material", "oc_name_known"], "pm": [], "vital": [], "gp": [], "gm": [], "attribs": [], "level": [], "rm": [], "svl": [], "descr": [], "skill": [], "roleplay": [], "gn": [], "svc": [], "gender": [], "stair": [], "align": [], "context": [], "gy": [], "gu": [], "svd": [], "cg": [], "have": ["amulet"], "disp": [], "race": [], "gi": [], "attack": [], "coord": [], "killer": [], "dlevel": []};let count=0;const reached=new Set();
const value=k=>{assert.ok(Number.isSafeInteger(L[k]),'required compiler constant '+k);return L[k];};
const raw=(m,p,n)=>Buffer.from(m.HEAPU8.slice(Number(p),Number(p)+n));
function bytes(m,p,n,offsets=[]){const b=raw(m,p,n);for(const off of offsets)b.fill(0,off,off+8);return b;}
const setReturn=(m,name,v)=>{const i=returns.indexOf(name);assert.notEqual(i,-1,'native scripted dependency '+name);m._probe_return(i,BigInt(v));};
const mb=(m,slot,key,v)=>{const i=bits.mon.indexOf(key);assert.notEqual(i,-1,key);m._probe_mon_bit(slot,i,v);},ob=(m,slot,key,v)=>{const i=bits.obj.indexOf(key);assert.notEqual(i,-1,key);m._probe_obj_bit(slot,i,v);};
function reset(seed=19){for(const m of mods){m._probe_reset(seed);m._probe_new_mon(value('PM_HUMAN'),11,10);m._probe_new_mon(value('PM_GHOST'),12,10);m._probe_new_obj(value('POT_HEALING'),value('OBJ_INVENT'));m._probe_new_obj(value('POT_WATER'),value('OBJ_INVENT'));m._probe_new_obj(value('LONG_SWORD'),value('OBJ_INVENT'));setReturn(m,'mksobj',1);setReturn(m,'mkobj',1);} }
function pointerField(m,p,offset){return new FixtureDataView(m.HEAPU8.buffer).getBigUint64(Number(p)+offset,true);}
function snapshot(m){const mon=[],obj=[];for(let i=0;i<m._probe_count(0);i++)mon.push(bytes(m,m._probe_pointer(1,i),L.monSize,[L.mon_data]));for(let i=0;i<m._probe_count(1);i++)obj.push(bytes(m,m._probe_pointer(2,i),L.objSize,[L.obj_nobj,L.obj_nexthere,L.obj_cobj]));const gm=m._probe_pointer(7,0),gn=m._probe_pointer(12,0);return{mon,obj,u:bytes(m,m._probe_pointer(0,0),L.youSize,[L.you_usteed,L.you_ustuck]),youmon:bytes(m,m._probe_pointer(10,0),L.monSize,[L.mon_data]),gp:raw(m,m._probe_pointer(6,0),L.gpSize),gm:bytes(m,gm,L.gmSize,[L.gm_multi_reason]),reason:text(m,pointerField(m,gm,L.gm_multi_reason)),gn:bytes(m,gn,L.gnSize,[L.gn_nomovemsg]),nomove:text(m,pointerField(m,gn,L.gn_nomovemsg)),disp:raw(m,m._probe_pointer(8,0),L.dispSize),map:raw(m,m._probe_pointer(3,0),L.COLNO*L.ROWNO*L.rmSize),vision:raw(m,m._probe_pointer(4,0),L.COLNO*L.ROWNO),cells:raw(m,m._probe_pointer(5,0),64),fake:raw(m,m._probe_pointer(14,0),L.objSize),scalar:Array.from({length:11},(_,i)=>m._probe_scalar(i)),result:text(m,m._probe_result_string()),trace:text(m,m._probe_trace()),rng:m._probe_rng_count(),rngstate:m._probe_rng_state()};}
function action(name,a=0n,b=0n,c=0n,d=0n){const op=names.indexOf(name);assert.notEqual(op,-1,name);reached.add(name);const before={C,R,T},result=mods.map(m=>m._probe_action(op,BigInt(a),BigInt(b),BigInt(c),BigInt(d)));assert.deepEqual(result[1],result[0],name+' result');assert.deepEqual(snapshot(mods[1]),snapshot(mods[0]),name+' state '+a+','+b+','+c+','+d);mods.forEach((m,i)=>assertStackRestored(m,stacks[i],name));assert.equal(C,before.C);assert.equal(R,before.R);assert.equal(T,before.T);count+=2;return result[0];}
function setup(fn){for(const m of mods)fn(m);}
function rolls(values){setup(m=>{new FixtureInt32Array(m.HEAPU8.buffer,Number(m._probe_rng_pointer()),values.length).set(values);m._probe_rng_length(values.length);});}
for(const k of ['PM_HUMAN','PM_GHOST','POT_HEALING','POT_WATER','LONG_SWORD','OBJ_INVENT','NUMMONS','NUM_OBJECTS','BLINDED','HALLUC','SICK','CONFUSION','STUNNED','DEAF','FAST'])value(k);
// Every original entrypoint, including private effects/selectors and native address-taken output cells.
for(const name of names){reset();let args=[0,0,0,0];if(name.startsWith('make_'))args=[1,0,0,0];if(name==='make_sick')args=[1,0,0,value('SICK_ALL')];if(['itimeout','itimeout_incr','set_itimeout','incr_itimeout','speed_up'].includes(name))args=[10,2,0,0];if(['potion_dip','mixtype','impact_arti_light','H2Opotion_dip'].includes(name))args=[0,1,0,0];if(name==='potionhit')args=[0,0,value('POTHIT_HERO_THROW'),0];if(name==='dip_potion_explosion')args=[0,1,0,0];if(name==='mongrantswish')setup(m=>m._probe_moncell(0));action(name,...args);}
// Signed64 timeout policy, overflow, low-byte booleans and full-width aliased native property references.
for(const n of [-9223372036854775808n,-1n,0n,1n,9007199254741013n,9223372036854775807n])for(const old of [0n,1n,0x1234567800000000n]){reset();setup(m=>m._probe_cells(0,old));action('itimeout',n);action('itimeout_incr',n,-17);action('set_itimeout',0,n);action('incr_itimeout',0,2147483649n);}
for(const name of ['make_confused','make_stunned','make_vomiting','make_blinded','make_hallucinated','make_deaf','make_glib','make_slimed','make_stoned'])for(const time of [0n,1n,23n,9007199254741000n])for(const talk of [0,1,128,256]){reset();setup(m=>{for(const key of ['CONFUSION','STUNNED','VOMITING','BLINDED','HALLUC','DEAF','GLIB','SLIMED','STONED'])m._probe_property(value(key),0,17n);});action(name,time,talk,0,0);}
// Native object catalogue and all potion classes, blessings and hallucinated text choice remain original source algorithms.
for(const name of names.filter(n=>n.startsWith('peffect_')))for(const bc of [-1,0,1])for(const poly of [0,1]){reset(31);setup(m=>{ob(m,0,bc<0?'cursed':'blessed',Math.abs(bc));if(poly)m._probe_hero(0,BigInt(value('PM_GHOST')));});action(name);}
for(let type=value('POT_GAIN_ABILITY');type<=value('POT_WATER');type++)for(const bc of [-1,0,1]){reset();setup(m=>{m._probe_obj(0,0,BigInt(type));ob(m,0,bc<0?'cursed':'blessed',Math.abs(bc));});action('peffects');action('drink_ok');action('dip_ok');action('dip_hands_ok');}
for(const blind of [0,1])for(const hallu of [0,1])for(const deaf of [0,1]){reset();setup(m=>{m._probe_property(value('BLINDED'),0,BigInt(blind));m._probe_property(value('HALLUC'),0,BigInt(hallu));m._probe_hero(13,BigInt(deaf));});action('bottlename');action('self_invis_message');action('toggle_blindness');}
// A wielded weapon evaluates EWarn_of_mon even when the warning mask is zero.
// Read the property index and slot masks from the actual compiled C metadata.
for(const mask of [0n,BigInt(L.W_WEP),BigInt(L.W_SADDLE),1n<<63n,BigInt(L.W_WEP)|(1n<<63n)])for(const blind of [0n,1n]){
 reset();setup(m=>{m._probe_equipment(0,2);m._probe_property(value('WARN_OF_MON'),1,mask);m._probe_property(value('BLINDED'),0,blind);});
 action('toggle_blindness');
 assert.ok(text(ref,ref._probe_trace()).includes('Sting_effects:')===Boolean(mask&BigInt(L.W_WEP)),'actual C warning slot selects Sting_effects');
 action('make_blinded',blind?0:10,0);
}
{
 const missing={...L};delete missing.WARN_OF_MON;
 let captured;
 const witness=await hybridFactory({nethackPorted:{potion(services){captured=services;return 0n;}}});
 witness._probe_action(names.indexOf('itimeout'),0n,0n,0n,0n);
 assert.throws(()=>createPotionEnvironment(captured,missing),/POTION property metadata WARN_OF_MON/,'missing metadata is rejected before short-circuited gameplay access');
}
// Real native linked object identities, water bless/curse function pointer and alias bits.
for(const type of ['LONG_SWORD','POT_HEALING','POT_WATER','POT_ACID','POT_OIL'])for(const potionBc of [-1,0,1])for(const targetBc of [-1,0,1]){reset();setup(m=>{m._probe_obj(0,0,BigInt(value('POT_WATER')));m._probe_obj(1,0,BigInt(value(type)));if(potionBc)ob(m,0,potionBc<0?'cursed':'blessed',1);if(targetBc)ob(m,1,targetBc<0?'cursed':'blessed',1);});action('H2Opotion_dip',0,1,1,0);action('mixtype',0,1);}
// Both cross-case shared tails, with the original Pestilence inversion and resistance short circuit.
for(const type of ['POT_HEALING','POT_EXTRA_HEALING','POT_FULL_HEALING','POT_GAIN_ABILITY','POT_RESTORE_ABILITY','POT_SICKNESS','POT_CONFUSION','POT_BLINDNESS','POT_WATER','POT_ACID','POT_POLYMORPH','POT_OIL'])for(const pest of [0,1])for(const bc of [-1,0,1]){reset(35);setup(m=>{m._probe_obj(0,0,BigInt(value(type)));if(pest)m._probe_mon(0,2,BigInt(value('PM_PESTILENCE')));if(bc)ob(m,0,bc<0?'cursed':'blessed',1);setReturn(m,'canseemon',1);});action('potionhit',0,0,value('POTHIT_HERO_THROW'));action('potionbreathe');}
for(const a of ['POT_HEALING','POT_EXTRA_HEALING','POT_FULL_HEALING','POT_GAIN_LEVEL','POT_GAIN_ENERGY','POT_SPEED','POT_SICKNESS','POT_BOOZE','POT_WATER','POT_ACID','UNICORN_HORN','AMETHYST'])for(const b of ['POT_HEALING','POT_SICKNESS','POT_BOOZE','POT_WATER']){reset();setup(m=>{m._probe_obj(0,0,BigInt(value(a)));m._probe_obj(1,0,BigInt(value(b)));});action('mixtype',0,1);}
for(const which of [0,1])for(const chance of [0,1,2,3,4]){reset(61);setup(m=>{m._probe_moncell(0);setReturn(m,'makemon',0);setReturn(m,'canseemon',1);m._probe_option(32,which);m._probe_hero(16,0n);});action('mongrantswish');rolls([chance,1,1,1]);action('djinni_from_bottle');}

// Actual native getobj calls the original three selectors; successful quaff/dip paths retain their shared state.
for(const feature of ['ROOM','FOUNTAIN','SINK','POOL'])for(const yes of [110,121]){reset(11);setup(m=>{m._probe_option(11,0);m._probe_option(10,yes);m._probe_tile(10,10,value(feature),value('IN_SIGHT')|value('COULD_SEE'));});action('dodrink');action('dodip');action('dip_into');assert.ok(text(ref,ref._probe_trace()).includes('select:0:'));}
// Oil-only forward cleanup label and all source branch classes: real object table types, positive erosion/lamplit fields.
for(const obj of ['LONG_SWORD','UNICORN_HORN','OIL_LAMP','MAGIC_LAMP','TOWEL','CORPSE','AMETHYST'])for(const kind of ['POT_WATER','POT_OIL','POT_ACID','POT_POLYMORPH','POT_SICKNESS'])for(const bc of [-1,0,1]){reset(27);setup(m=>{m._probe_obj(0,0,BigInt(value(obj)));m._probe_obj(1,0,BigInt(value(kind)));if(bc)ob(m,1,bc<0?'cursed':'blessed',1);ob(m,0,'oeroded',1);ob(m,0,'oeroded2',1);});action('potion_dip',0,1);}
// Macro condition observes prior damage resistance; rn1 offset observes bless state after the native RNG callback.
for(const half of [0n,BigInt(value('FROMOUTSIDE'))]){reset(2);setup(m=>{m._probe_property(value('HALF_PHDAM'),0,half);m._probe_option(121,1);});rolls([1,2,3,4,5,6]);action('potionhit',-2,0,value('POTHIT_HERO_THROW'));assert.ok(text(ref,ref._probe_trace()).includes('fliphalf;'));}
reset(2);setup(m=>m._probe_option(122,1));rolls([7]);action('peffect_blindness');assert.ok(text(ref,ref._probe_trace()).includes('flipbless;'));
// C min reevaluates selected RHS, preserving both native RNG draws rather than caching the first.
reset(2);setup(m=>{ob(m,0,'blessed',1);m._probe_option(124,value('PM_GHOST'));m._probe_hero(6,100n);});rolls([14,1]);action('peffect_polymorph');assert.equal(ref._probe_rng_count(),2,'actual C min selected RHS twice');
// Exact signed64 property masks, low-byte Boolean arguments, timeout alias cells and full-monster clone branches.
for(const mask of [0x1000000000000000n,-9223372036854775808n,-1n]){reset();setup(m=>{m._probe_property(value('HALLUC_RES'),1,mask);m._probe_property(value('HALLUC'),0,17n);});action('make_hallucinated',0,1,mask);}
for(const who of [0,-2]){reset();setup(m=>{setReturn(m,'clone_mon',1);setReturn(m,'cloneu',1);setReturn(m,'canseemon',1);});action('split_mon',who,0);}
// Native mon** alias is cleared before the actual wish callback can inspect u.ustuck.
reset();setup(m=>{m._probe_option(32,1);m._probe_hero(16,0n);m._probe_option(123,20+returns.indexOf('tmp_at'));});action('mongrantswish');assert.ok(text(ref,ref._probe_trace()).includes('live_ustuck:-1;'));
// A native callback grows memory while the original effect retains live object/monster and native automatic buffers.
reset(15);const heapBefore=mods.map(m=>m.HEAPU8.buffer),stage=20+returns.indexOf('mon_set_minvis');setup(m=>{m._probe_obj(0,0,BigInt(value('POT_INVISIBILITY')));m._probe_option(120,stage);m._probe_option(125,stage);setReturn(m,'canseemon',1);});action('potionhit',0,0,value('POTHIT_HERO_THROW'));assert.ok(text(ref,ref._probe_trace()).includes('grow:'+stage+';'));assert.ok(text(ref,ref._probe_trace()).includes('reenter:'+stage+';'));mods.forEach((m,i)=>assertMemoryGrowth(m,heapBefore[i]));


// The original automatic object starts as the full native zeroobj, including all inactive fields and padding.
reset(3);setup(m=>{m._probe_obj(0,0,BigInt(value('UNICORN_HORN')));m._probe_obj(1,0,BigInt(value('POT_SICKNESS')));ob(m,1,'dknown',1);m._probe_class_known(value('POT_SICKNESS'),0);});action('potion_dip',0,1);assert.equal(ref._probe_scalar(10),1n,'actual native docall sees the automatic full-copy object');
// Separate actual Module state, selector identities and native buffers do not share the first environment.
const other=await hybridFactory({nethackPorted:runtime});mods.push(other);stacks.push(other._probe_stack());reset(7);setup(m=>{m._probe_option(11,0);m._probe_obj(0,0,BigInt(value('POT_CONFUSION')));});action('dodrink');assert.deepEqual(snapshot(other),snapshot(ref),'independent Module native state');count++;mods.pop();stacks.pop();

assert.equal(reached.size,names.length,'all66 original functions reached');
console.log('POTION '+count+' comparisons passed ('+fixtureReferenceLabel+' vs JavaScript; unchanged actual source/catalogues/heap, controlled foreign world, all66 original entrypoints).');
