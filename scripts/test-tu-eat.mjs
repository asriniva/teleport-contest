import {nativeFixtureServices} from './native-pet-combat-fixture.mjs';
const nativeExecution=process.env.NATIVE_EAT_FIXTURE==='1',nativeServices=new WeakMap();
function eatingServices(s){if(!nativeExecution)return s;let local=nativeServices.get(s);if(!local){local=nativeFixtureServices(s,{}).services;nativeServices.set(s,local);}return local;}
import './pure-js-probes/deny-wasm.mjs';
import {referenceLabelFor as fixtureReferenceLabelFor} from './native-test-backend.mjs';
const fixtureReferenceLabel=fixtureReferenceLabelFor("eat");
import {createProbe,createReference,loadFixture,fixtureImports} from './pure-js-fixtures/load.mjs';
import {DataView as FixtureDataView,Int32Array as FixtureInt32Array} from './native-test-backend.mjs';
import{DataView,Int32Array,referenceBackend,assertStackRestored,assertMemoryGrowth}from'./native-test-backend.mjs';
import assert from './native-test-assert.mjs';import{readFileSync}from'node:fs';import{resolve}from'node:path';import{pathToFileURL}from'node:url';const{callEat,initializeEat}=await loadFixture("eat",process.env.TELEPORT_EAT_RUNTIME||'../js/nethack/bindings/eat.js');import*as core from'../js/ported/eat.js';import{C,R,T}from'../js/c-runtime/context.js';
const author=process.env.TELEPORT_EAT_PROBES,dir=author?pathToFileURL(resolve(author)+'/'):new URL('../.cache/tu-probes/',import.meta.url),rf=(await loadFixture("eat",new URL('eat-reference.mjs',dir))).default,hf=(await loadFixture("eat",new URL('eat-hybrid.mjs',dir))).default,ref=await referenceBackend('eat',rf)();
function text(m,p){if(!p)return null;let q=Number(p),e=q;while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.slice(q,e)).toString();}
const L={size:Number(ref._probe_context_size())};for(let i=0;i<ref._probe_layout_count();i++){const k=text(ref,ref._probe_layout_name(i)),v=ref._probe_layout_value(i);L[k]=/^(M1_|M2_|W_)/.test(k)?BigInt.asUintN(64,v).toString():Number(BigInt.asIntN(64,v));}
if(!author)assert.deepEqual(L,JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url))).eat);
const runtime={eat:(s,n,...args)=>callEat(eatingServices(s),L,n,...args),initializeEat:s=>initializeEat(eatingServices(s),L)},mods=[ref,await hf({nethackPorted:runtime})],stacks=mods.map(m=>m._probe_stack());
const names=["is_edible", "init_uhunger", "eatmdone", "eatmupdate", "food_xname", "choke", "recalc_wt", "reset_eat", "obj_nutrition", "adj_victual_nutrition", "touchfood", "food_disappears", "food_substitution", "do_reset_eat", "temp_resist", "eating_dangerous_corpse", "eatfood", "done_eating", "eating_conducts", "eat_brains", "maybe_cannibal", "cprefx", "fix_petrification", "intrinsic_possible", "should_givit", "temp_givit", "givit", "eye_of_newt_buzz", "cpostfx", "corpse_intrinsic", "violated_vegetarian", "costly_tin", "tin_variety_txt", "tin_details", "set_tin_variety", "tin_variety", "use_up_tin", "consume_tin", "opentin", "start_tin", "Hear_again", "rottenfood", "eatcorpse", "start_eating", "eating_glob", "garlic_breath", "fprefx", "bounded_increase", "accessory_has_effect", "eataccessory", "eatspecial", "foodword", "fpostfx", "edibility_prompts", "doeat_nonfood", "doeat", "tinopen_ok", "use_tin_opener", "bite", "gethungry", "morehungry", "lesshungry", "unfaint", "is_fainted", "reset_faint", "newuhs", "eat_ok", "offer_ok", "tin_ok", "floorfood", "vomit", "eaten_stat", "consume_oeaten", "maybe_finished_meal", "cant_finish_meal", "Popeye", "Finish_digestion"],returns=["Mgender", "Monnam", "Resists_Elem", "Ring_gone", "Tobjnam", "abs", "acurrstr", "addinv_nomerge", "adjalign", "adjattrib", "altar_wrath", "an", "ansimpleoname", "attacktype", "attacktype_fordmg", "attrcurse", "b_trapped", "body_part", "bot", "can_reach_floor", "canseemon", "cantvomit", "carrying", "change_luck", "change_sex", "check_capacity", "corpse_xname", "costly_alteration", "costly_spot", "curs_on_u", "debugcore", "defended", "delayed_killer", "deltrap", "dismount_steed", "dmgtype", "doname", "done", "dopotion", "dropx", "dropy", "dupstr", "encumber_msg", "end_running", "eos", "exercise", "explode", "fall_asleep", "feel_cockatrice", "fingers_or_gloves", "float_up", "fmt_ptr", "freeinv", "g_at", "gainstr", "hcolor", "heal_legs", "incr_itimeout", "inv_cnt", "is_flammable", "is_ice", "is_pool_or_lava", "is_rottable", "killer_xname", "losehp", "make_blinded", "make_confused", "make_deaf", "make_glib", "make_hallucinated", "make_sick", "make_slimed", "make_stoned", "make_stunned", "make_vomiting", "makeplural", "melt_ice", "mksobj", "mon_nam", "mondied", "monflee", "monstone", "more_experienced", "near_capacity", "newexplevel", "newsym", "nomul", "o_unleash", "obj_extract_self", "obj_here", "obj_is_pname", "obj_stop_timers", "objdescr_is", "observe_object", "olfaction", "otense", "outrumor", "paranoid_query", "peek_at_iced_corpse_age", "pluslvl", "pm_to_cham", "pmname", "poison_strdmg", "poly_when_stoned", "polymon", "polyself", "rehumanize", "remove_worn_item", "rescham", "reset_utrap", "retouch_equipment", "revive_corpse", "rndmonnam", "rounddiv", "sa_victual", "same_race", "see_monsters", "self_invis_message", "selftouch", "sellobj_state", "set_bknown", "set_itimeout", "set_mimic_blocking", "set_ulycn", "setuhpmax", "splitobj", "stackobj", "still_chewing", "stop_occupation", "strcat", "strlen", "strncmpi", "surface", "t_at", "the", "the_unique_pm", "tinnable", "toggle_displacement", "touch_artifact", "trycall", "uasmon_maxStr", "ubreatheu", "undiscovered_artifact", "unmul", "unpunish", "uqwepgone", "useup", "useupall", "useupf", "uswapwepgone", "uwepgone", "vault_gd_watching", "weight", "welded", "were_beastie", "wield_tool", "will_feel_cockatrice", "xname", "yn_function", "yobjnam", "you_unwere"],schema={"mon": ["struct monst", {"data": "ptr:pm", "m_ap_type": "Uint8", "mappearance": "Uint32", "mextra": "ptr:mextra", "mhp": "Int32", "mtame": "Int8", "mx": "Int16", "my": "Int16"}], "you": ["struct you", {"acurr": "nested:attribs", "aexe": "nested:attribs", "amax": "nested:attribs", "atemp": "nested:attribs", "mh": "Int32", "mhmax": "Int32", "ualign": "nested:align", "ublessed": "Int32", "uconduct": "nested:conduct", "ucreamed": "Uint32", "udaminc": "Int8", "uen": "Int32", "uenmax": "Int32", "uenpeak": "Int32", "uhave": "nested:have", "uhitinc": "Int8", "uhp": "Int32", "uhpmax": "Int32", "uhs": "Uint32", "uhunger": "Int32", "ulycn": "Int32", "umonnum": "Int32", "umonster": "Int32", "uprops": "array:prop:69", "uroleplay": "nested:roleplay", "usteed": "ptr:mon", "ustuck": "ptr:mon", "utrap": "Uint32", "utraptype": "Uint32", "ux": "Int16", "uy": "Int16", "uz": "nested:level"}], "prop": ["struct prop", {"blocked": "BigInt64", "extrinsic": "BigInt64", "intrinsic": "BigInt64"}], "obj": ["struct obj", {"age": "BigInt64", "cobj": "ptr:obj", "corpsenm": "Int32", "invlet": "Int8", "nexthere": "ptr:obj", "nobj": "ptr:obj", "o_id": "Uint32", "oartifact": "Int8", "oclass": "Int8", "oeaten": "Uint32", "otyp": "Int16", "owornmask": "BigInt64", "owt": "Uint32", "ox": "Int16", "oy": "Int16", "quan": "BigInt64", "spe": "Int8", "timed": "Int16", "where": "Int8"}], "colors": ["struct c_color_names", {"c_green": "ptr:raw"}], "iflags": ["struct instance_flags", {"debug_hunger": "Int8", "last_msg": "Int32", "menu_requested": "Int8", "override_ID": "Int32"}], "strings": ["struct c_common_strings", {"c_You_can_move_again": "ptr:raw", "c_something": "ptr:raw", "c_vision_clears": "ptr:raw"}], "conduct": ["struct u_conduct", {"food": "BigInt64", "literate": "BigInt64", "polyselfs": "BigInt64", "unvegan": "BigInt64", "unvegetarian": "BigInt64"}], "flags": ["struct flag", {"acoustics": "Int8", "female": "Int8", "paranoia_bits": "Uint32", "verbose": "Int8"}], "topology": ["struct dgn_topology", {"d_air_level": "nested:level", "d_astral_level": "nested:level", "d_water_level": "nested:level"}], "gv": ["struct instance_globals_v", {"vision_full_recalc": "Int8", "viz_array": "ptr:raw"}], "svm": ["struct instance_globals_saved_m", {"moves": "BigInt64"}], "role": ["struct Role", {"mnum": "Int16", "name": "nested:rolename"}], "cls": ["struct objclass", {"oc_delay": "Int8", "oc_nutrition": "Uint16", "oc_oprop": "Uint8", "oc_skill": "Int8"}], "pm": ["struct permonst", {"cnutrit": "Uint16", "cwt": "Uint32", "geno": "Uint16", "mattk": "array:attack:6", "mconveys": "Uint8", "mflags1": "BigUint64", "mflags2": "BigUint64", "mflags3": "Uint16", "mlet": "Int8", "mlevel": "Int8", "mmove": "Int8", "msize": "Uint8", "pmidx": "Int32", "pmnames": "array:ptr:raw:3"}], "vital": ["struct mvitals", {}], "gp": ["struct instance_globals_p", {}], "gm": ["struct instance_globals_m", {"multi": "BigInt64", "multi_reason": "ptr:raw"}], "attribs": ["struct attribs", {"a": "array:Int8:6"}], "level": ["struct d_level", {"dlevel": "Int16", "dnum": "Int16"}], "rm": ["struct rm", {"typ": "Int8"}], "svl": ["struct instance_globals_saved_l", {"level": "nested:dlevel"}], "descr": ["struct objdescr", {"oc_descr": "ptr:raw"}], "skill": ["struct skills", {}], "roleplay": ["struct u_roleplay", {"deaf": "Int8"}], "gn": ["struct instance_globals_n", {"nomovemsg": "ptr:raw"}], "svc": ["struct instance_globals_saved_c", {"context": "nested:context"}], "gender": ["struct Gender", {"he": "ptr:raw", "him": "ptr:raw"}], "stair": ["struct stairway", {}], "align": ["struct align", {"type": "Int8"}], "context": ["struct context_info", {"current_fruit": "Int32", "digging": "nested:dig", "tin": "nested:tin", "victual": "nested:victual"}], "gy": ["struct instance_globals_y", {"youmonst": "nested:mon"}], "gu": ["struct instance_globals_u", {"urace": "nested:race", "urole": "nested:role"}], "svd": ["struct instance_globals_saved_d", {"dungeon_topology": "nested:topology"}], "cg": ["struct const_globals", {}], "have": ["struct u_have", {}], "disp": ["struct display_hints", {"botl": "Int8"}], "race": ["struct Race", {"attrmax": "array:Int16:6", "attrmin": "array:Int16:6", "mnum": "Int16", "noun": "ptr:raw", "selfmask": "Int16"}], "gi": ["struct instance_globals_i", {"invent": "ptr:obj"}], "attack": ["struct attack", {"aatyp": "Uint8", "adtyp": "Uint8", "damd": "Uint8", "damn": "Uint8"}], "coord": ["struct nhcoord", {"x": "Int16", "y": "Int16"}], "killer": ["struct kinfo", {"format": "Int32", "name": "array:Int8:256"}], "victual": ["struct victual_info", {"nmod": "Int32", "o_id": "Uint32", "piece": "ptr:obj", "reqtime": "Int32", "usedtime": "Int32"}], "tin": ["struct tin_info", {"o_id": "Uint32", "reqtime": "Int32", "tin": "ptr:obj", "usedtime": "Int32"}], "ge": ["struct instance_globals_e", {"eatmbuf": "ptr:raw"}], "ga": ["struct instance_globals_a", {"afternmv": "callback"}], "go": ["struct instance_globals_o", {"occupation": "callback"}], "gc": ["struct instance_globals_c", {"corpsenm_digested": "Int16"}], "gf": ["struct instance_globals_f", {"force_save_hs": "Int8"}], "svk": ["struct instance_globals_saved_k", {"killer": "nested:killer"}], "edog": ["struct edog", {"hungrytime": "BigInt64"}], "mextra": ["struct mextra", {"edog": "ptr:edog"}], "dig": ["struct dig_info", {"chew": "Int8", "level": "nested:level", "pos": "nested:coord"}], "rolename": ["struct RoleName", {"m": "ptr:raw"}], "dlevel": ["__typeof__(svl.level)", {"locations": "array:rm:80,21", "monlist": "ptr:mon", "monsters": "array:ptr:mon:80,21", "objects": "array:ptr:obj:80,21"}]},bits={"mon": ["isminion", "mconf"], "you": ["mfemale", "uedibility", "uinvulnerable", "usick_type", "uswallow"], "prop": [], "obj": ["bknown", "blessed", "cknown", "cursed", "dknown", "globby", "in_use", "known", "no_charge", "oeroded", "oerodeproof", "otrapped", "rknown", "unpaid"], "colors": [], "iflags": [], "strings": [], "conduct": [], "flags": [], "topology": [], "gv": [], "svm": [], "role": [], "cls": ["oc_charged", "oc_material", "oc_unique"], "pm": [], "vital": [], "gp": [], "gm": [], "attribs": [], "level": [], "rm": ["flags"], "svl": [], "descr": [], "skill": [], "roleplay": [], "gn": [], "svc": [], "gender": [], "stair": [], "align": [], "context": [], "gy": [], "gu": [], "svd": [], "cg": [], "have": ["amulet"], "disp": [], "race": [], "gi": [], "attack": [], "coord": [], "killer": [], "victual": ["canchoke", "doreset", "eating", "fullwarn"], "tin": [], "ge": [], "ga": [], "go": [], "gc": [], "gf": [], "svk": [], "edog": [], "mextra": [], "dig": [], "rolename": [], "dlevel": []};
let count=0;const reached=new Set(),value=k=>{const v=typeof L[k]==='string'?Number(BigInt(L[k])):L[k];assert.ok(Number.isSafeInteger(v),'required compiler constant '+k);return v;},raw=(m,p,n)=>Buffer.from(m.HEAPU8.slice(Number(p),Number(p)+n));
function bytes(m,p,type){const b=raw(m,p,L[type+'Size']);function mask(t,base=0){for(const[f,kind]of Object.entries(schema[t][1])){const off=base+L[t+'_'+f];if(kind.startsWith('ptr:')||kind==='callback')b.fill(0,off,off+8);else if(kind.startsWith('nested:'))mask(kind.slice(7),off);}}mask(type);return b;}
const setReturn=(m,n,v)=>{const i=returns.indexOf(n);assert.notEqual(i,-1,n);m._probe_return(i,BigInt(v));},setup=fn=>mods.forEach(fn),ob=(m,i,n,v)=>m._probe_obj_bit(i,bits.obj.indexOf(n),v);
function reset(seed=19){setup(m=>{m._probe_reset(seed);m._probe_new_mon(value('PM_HUMAN'),11,10);m._probe_new_mon(value('PM_GHOST'),12,10);m._probe_new_obj(value('FOOD_RATION'),value('OBJ_INVENT'));m._probe_new_obj(value('CORPSE'),value('OBJ_INVENT'));m._probe_obj(1,4,BigInt(value('PM_HUMAN')));m._probe_new_obj(value('TIN'),value('OBJ_INVENT'));m._probe_obj(2,4,BigInt(value('PM_HUMAN')));m._probe_new_obj(value('RIN_ADORNMENT'),value('OBJ_INVENT'));m._probe_weight(0,20);m._probe_victual(0,0n);m._probe_victual(2,5n);m._probe_victual(3,-20n);m._probe_eaten(0,400);m._probe_tin(0,2n);m._probe_tin(2,5n);});}
function snapshot(m){const state={};for(const[k,type]of [[0,'you'],[7,'gm'],[8,'disp'],[9,'svc'],[10,'mon'],[11,'gu'],[12,'gn']])state[type]=bytes(m,m._probe_pointer(k,0),type);state.mon=Array.from({length:m._probe_count(0)},(_,i)=>bytes(m,m._probe_pointer(1,i),'mon'));state.obj=Array.from({length:m._probe_count(1)},(_,i)=>bytes(m,m._probe_pointer(2,i),'obj'));for(const[k,type]of [[0,'ge'],[1,'ga'],[2,'go'],[3,'gc'],[4,'gf'],[5,'svk']])state[type]=bytes(m,m._probe_more_pointer(k),type);Object.assign(state,{ctx:[0,1,2].map(i=>m._probe_context(i)),cells:raw(m,m._probe_pointer(5,0),64),trace:text(m,m._probe_trace()),result:text(m,m._probe_result_string()),rng:m._probe_rng_count(),rngstate:m._probe_rng_state(),frees:m._probe_free_count(),callbacks:[m._probe_callback_identity(0),m._probe_callback_identity(1)],mimic:text(m,m._probe_mimic_text()),nomove:text(m,m._probe_nomove_text())});return state;}
function action(name,a=0,b=0,c=0,d=0){reached.add(name);const op=names.indexOf(name),before={C,R,T},result=mods.map(m=>m._probe_action(op,BigInt(a),BigInt(b),BigInt(c),BigInt(d)));assert.deepEqual(result[1],result[0],name+' result '+[a,b,c,d]);assert.deepEqual(snapshot(mods[1]),snapshot(mods[0]),name+' state '+[a,b,c,d]);mods.forEach((m,i)=>assertStackRestored(m,stacks[i],name));assert.equal(C,before.C);assert.equal(R,before.R);assert.equal(T,before.T);count+=2;return result[0];}
function rolls(values){setup(m=>{new FixtureInt32Array(m.HEAPU8.buffer,Number(m._probe_rng_pointer()),values.length).set(values);m._probe_rng_length(values.length);});}
for(let i=0;i<7;i++){assert.equal(core.hu_stat[i],text(ref,ref._probe_table(0,i)));assert.equal(text(mods[1],mods[1]._probe_table(0,i)),core.hu_stat[i]);count+=2;}for(let i=0;i<22;i++){assert.equal(core.foodwords[i],text(ref,ref._probe_table(2,i)));count++;}for(let i=0;i<16;i++){assert.deepEqual(core.tintxts[i],{txt:text(ref,ref._probe_table(1,i)),nut:Number(ref._probe_tin_row(i,0)),fodder:Number(ref._probe_tin_row(i,1)),greasy:Number(ref._probe_tin_row(i,2))});count++;}
reset();action("is_edible",0,0,0,0);
reset();action("init_uhunger",0,0,0,0);
reset();action("eatmdone",0,0,0,0);
reset();action("eatmupdate",0,0,0,0);
reset();action("food_xname",0,0,0,0);
reset();setup(m=>m._probe_hunger(value('SATIATED'),2000));action("choke",0,0,0,0);
reset();action("recalc_wt",0,0,0,0);
reset();action("reset_eat",0,0,0,0);
reset();action("obj_nutrition",0,0,0,0);
reset();action("adj_victual_nutrition",0,0,0,0);
reset();action("touchfood",0,0,0,0);
reset();action("food_disappears",0,0,0,0);
reset();action("food_substitution",0,1,0,0);
reset();action("do_reset_eat",0,0,0,0);
reset();action("temp_resist",value("FIRE_RES"),0,0,0);
reset();action("eating_dangerous_corpse",value("STONE_RES"),0,0,0);
reset();action("eatfood",0,0,0,0);
reset();action("done_eating",0,0,0,0);
reset();action("eating_conducts",value("PM_HUMAN"),0,0,0);
reset();action("eat_brains",0,1,0,0);
reset();action("maybe_cannibal",value("PM_HUMAN"),0,0,0);
reset();action("cprefx",value("PM_HUMAN"),0,0,0);
reset();action("fix_petrification",0,0,0,0);
reset();action("intrinsic_possible",value("FIRE_RES"),value("PM_HUMAN"),0,0);
reset();action("should_givit",value("FIRE_RES"),value("PM_HUMAN"),0,0);
reset();action("temp_givit",value("FIRE_RES"),value("PM_HUMAN"),0,0);
reset();action("givit",value("FIRE_RES"),value("PM_HUMAN"),0,0);
reset();action("eye_of_newt_buzz",0,0,0,0);
reset();action("cpostfx",value("PM_HUMAN"),0,0,0);
reset();action("corpse_intrinsic",value("PM_HUMAN"),0,0,0);
reset();action("violated_vegetarian",0,0,0,0);
reset();action("costly_tin",0,0,0,0);
reset();action("tin_variety_txt",0,0,0,0);
reset();action("tin_details",2,value("PM_HUMAN"),0,0);
reset();action("set_tin_variety",2,1,0,0);
reset();action("tin_variety",2,0,0,0);
reset();action("use_up_tin",2,0,0,0);
reset();action("consume_tin",0,0,0,0);
reset();action("opentin",0,0,0,0);
reset();setup(m=>ob(m,2,'blessed',1));action("start_tin",2,0,0,0);
reset();action("Hear_again",0,0,0,0);
reset();action("rottenfood",0,0,0,0);
reset();setup(m=>m._probe_obj(1,4,BigInt(value('PM_LIZARD'))));action("eatcorpse",1,0,0,0);
reset();action("start_eating",0,0,0,0);
reset();action("eating_glob",0,0,0,0);
reset();action("garlic_breath",0,0,0,0);
reset();action("fprefx",0,0,0,0);
reset();action("bounded_increase",5,1,value("RIN_ADORNMENT"),0);
reset();action("accessory_has_effect",3,0,0,0);
reset();action("eataccessory",3,0,0,0);
reset();action("eatspecial",0,0,0,0);
reset();action("foodword",0,0,0,0);
reset();action("fpostfx",0,0,0,0);
reset();action("edibility_prompts",0,0,0,0);
reset();action("doeat_nonfood",0,0,0,0);
reset();setup(m=>m._probe_option(11,-1));action("doeat",0,0,0,0);
reset();action("tinopen_ok",0,0,0,0);
reset();setup(m=>m._probe_option(11,-1));action("use_tin_opener",0,0,0,0);
reset();action("bite",0,0,0,0);
reset();action("gethungry",0,0,0,0);
reset();action("morehungry",0,0,0,0);
reset();action("lesshungry",0,0,0,0);
reset();action("unfaint",0,0,0,0);
reset();action("is_fainted",0,0,0,0);
reset();action("reset_faint",0,0,0,0);
reset();action("newuhs",0,0,0,0);
reset();action("eat_ok",0,0,0,0);
reset();action("offer_ok",1,0,0,0);
reset();action("tin_ok",1,0,0,0);
reset();action("floorfood",0,0,0,0);
reset();action("vomit",0,0,0,0);
reset();action("eaten_stat",10,0,0,0);
reset();action("consume_oeaten",0,1,0,0);
reset();action("maybe_finished_meal",0,0,0,0);
reset();action("cant_finish_meal",1,0,0,0);
reset();action("Popeye",0,0,0,0);
reset();action("Finish_digestion",0,0,0,0);

// All catalogue rows with representative original dietary classifications.
for(const species of ['PM_HUMAN','PM_RUST_MONSTER','PM_GHOUL','PM_GELATINOUS_CUBE','PM_FIRE_ELEMENTAL']){
 reset();setup(m=>m._probe_hero(0,BigInt(value(species))));
 for(let typ=0;typ<value('NUM_OBJECTS');typ++){
  setup(m=>m._probe_obj(0,0,BigInt(typ)));action('is_edible',0);
 }
}
for(const species of ['PM_HUMAN','PM_ELF','PM_ORC','PM_DWARF'])for(const typ of ['LEMBAS_WAFER','CRAM_RATION']){
 reset();setup(m=>{m._probe_hero(0,BigInt(value(species)));m._probe_obj(0,0,BigInt(value(typ)));});action('adj_victual_nutrition');action('obj_nutrition',0);action('fprefx',0);
}
for(const typ of ['FOOD_RATION','CORPSE','TIN','RIN_ADORNMENT'])for(const blessed of [0,1])for(const cursed of [0,1])for(const known of [0,1]){
 reset();setup(m=>{m._probe_obj(0,0,BigInt(value(typ)));ob(m,0,'blessed',blessed);ob(m,0,'cursed',cursed);ob(m,0,'known',known);});
 for(const n of ['foodword','eat_ok','offer_ok','tin_ok','tinopen_ok','food_xname'])action(n,0);
}
for(const old of [-100,-20,-1,0,1,5,10,19,20,40,100,20000])for(const inc of [-3,-1,0,1,3,100]){reset();action('bounded_increase',old,inc,value('RIN_ADORNMENT'));}
for(const species of ['PM_HUMAN','PM_ELF','PM_RUST_MONSTER','PM_FIRE_ELEMENTAL','PM_GHOST'])for(let prop=1;prop<=value('LAST_PROP');prop++){reset();action('intrinsic_possible',prop,value(species));}
for(const hunger of [-100,-1,0,1,49,50,51,149,150,151,299,300,301,900,999,1000,1001,1999])for(const incr of [0,1]){reset();setup(m=>m._probe_hunger(value('NOT_HUNGRY'),hunger));action('newuhs',incr);}

// Positive native trap pointer and packed terrain alias paths.
for(const reply of [110,121,113]){reset();setup(m=>{m._probe_hero(0,BigInt(value('PM_RUST_MONSTER')));m._probe_option(36,1);m._probe_trap(value('BEAR_TRAP'),1);m._probe_option(10,reply);setReturn(m,'can_reach_floor',1);});setup(m=>{const p=m._malloc(4n);m.HEAPU8.set(Buffer.from('eat\0'),Number(p));m._probe_text(BigInt(p));m._free(BigInt(p));});action('floorfood',0,0);for(const name of ['eat_ok','offer_ok','tin_ok'])action(name,-1);}
for(const mask of [0,value('W_NONDIGGABLE')]){reset();setup(m=>{m._probe_hero(0,BigInt(value('PM_RUST_MONSTER')));m._probe_tile(10,10,value('IRONBARS'),3);m._probe_wall(mask);m._probe_option(10,110);setReturn(m,'can_reach_floor',1);const p=m._malloc(4n);m.HEAPU8.set(Buffer.from('eat\0'),Number(p));m._probe_text(BigInt(p));m._free(BigInt(p));});action('floorfood',0,0);for(const name of ['eat_ok','offer_ok','tin_ok'])action(name,-1);}

for(const rotten of [0,1]){reset();rolls(Array(100).fill(0));setup(m=>{ob(m,1,'oeroded',rotten);setReturn(m,'peek_at_iced_corpse_age',100);m._probe_victual(0,1n);});action('eatcorpse',1);action('edibility_prompts',1);}
// Addressable callbacks may grow memory and reenter an original EAT function.
for(const target of [1,20+returns.indexOf('xname')]){reset();setup(m=>{m._probe_option(120,target);m._probe_option(125,target);});const sizes=mods.map(m=>m.HEAPU8.length);action(target===1?'bounded_increase':'food_xname',...(target===1?[20,3,value('RIN_ADORNMENT')]:[0,0]));mods.forEach((m,i)=>assertMemoryGrowth(m,sizes[i],'EAT callback growth'));}

// Native obj** replacement is visible before the original else-if continues.
for(const result of [0,1]){reset();setup(m=>{m._probe_option(11,0);m._probe_option(30,result);m._probe_option(31,2);m._probe_obj(1,0,BigInt(value('CRAM_RATION')));m._probe_eaten(1,100);m._probe_option(120,3);m._probe_option(125,3);});action('doeat');}
// Native 64-bit intrinsic/extrinsic/blocked cells remain independent.
for(const mask of [0n,1n,0x10000000000000n,0x8000000000000000n,-1n])for(const field of [0,1,2]){reset();setup(m=>m._probe_property(value('FIRE_RES'),field,BigInt.asIntN(64,mask)));action('temp_resist',value('FIRE_RES'));}

for(const alias of [0,1]){reset();setup(m=>{const p=m._malloc(9n);m.HEAPU8.set(Buffer.from('mimic me\0'),Number(p));m._probe_mimic(BigInt(p),alias);m._free(BigInt(p));});action('eatmdone');assert.equal(mods[0]._probe_free_count(),1);count++;}
for(const token of [0n,0xa5123456789abcden])for(const slot of [0,1]){reset();setup(m=>m._probe_callback_set(slot,token));action('food_disappears',1);action('reset_faint');}
// A/B/A factories share the dispatcher but retain distinct module-owned statics.
const thirds=[await referenceBackend('eat',rf)(),await hf({nethackPorted:runtime})];for(const m of thirds){m._probe_reset(73);m._probe_hunger(value('FAINTED'),-1);m._probe_action(names.indexOf('newuhs'),0n,0n,0n,0n);}reset();action('is_fainted');assert.deepEqual(thirds.map(m=>m._probe_action(names.indexOf('is_fainted'),0n,0n,0n,0n)),[thirds[0]._probe_action(names.indexOf('is_fainted'),0n,0n,0n,0n),thirds[0]._probe_action(names.indexOf('is_fainted'),0n,0n,0n,0n)]);assert.deepEqual(snapshot(thirds[1]),snapshot(thirds[0]));count+=2;

// Actual catalogue food effects and every legal explicit tin variety.
for(let typ=0;typ<value('NUM_OBJECTS');typ++){
 reset();setup(m=>m._probe_obj(0,0,BigInt(typ)));const p=Number(mods[0]._probe_pointer(2,0));if(new FixtureDataView(mods[0].HEAPU8.buffer).getInt8(p+L.obj_oclass)!==value('FOOD_CLASS'))continue;
 action('fprefx',0);action('fpostfx',0);action('foodword',0);
}
for(let variety=-3;variety<17;variety++)for(const blessed of [0,1])for(const cursed of [0,1]){reset();setup(m=>{ob(m,2,'blessed',blessed);ob(m,2,'cursed',cursed);});action('set_tin_variety',2,variety);action('tin_variety',2,0);action('tin_details',2,value('PM_HUMAN'));}

for(const amount of [1,2,7,16,31])for(const eaten of [0,1,0x7fffffff,0x80000000,0xffffffff]){reset();setup(m=>m._probe_eaten(0,eaten));action('consume_oeaten',0,amount);}
for(const weight of [0x7fffffff,0x80000000,0xfffffffe]){reset();setup(m=>{m._probe_weight(1,weight);ob(m,1,'globby',1);setReturn(m,'peek_at_iced_corpse_age',100);});action('eatcorpse',1);}

for(const length of [3,100])for(const hallucinated of [0,1]){reset();setup(m=>{const message='M'.repeat(length),p=m._malloc(BigInt(length+1));m.HEAPU8.set(Buffer.from(message+'\0'),Number(p));m._probe_mimic(BigInt(p),1);m._free(BigInt(p));m._probe_hero(26,BigInt(value('M_AP_OBJECT')));m._probe_hero(27,BigInt(value(hallucinated?'GOLD_PIECE':'ORANGE')));m._probe_property(value('HALLUC'),0,BigInt(hallucinated));});action('eatmupdate');action('eatmdone');}

for(const row of core.tintxts.slice(0,-1))for(const suffix of [' eel',' EEL','X','']){reset();setup(m=>{const input=row.txt+suffix,p=m._malloc(BigInt(Buffer.byteLength(input)+1));m.HEAPU8.set(Buffer.from(input+'\0'),Number(p));m._probe_text(BigInt(p));m._free(BigInt(p));});action('tin_variety_txt');}
assert.equal(reached.size,77);console.log('EAT '+count+' original-C/JS comparisons passed ('+fixtureReferenceLabel+'); all77 functions and native-visible source tables exercised.');
