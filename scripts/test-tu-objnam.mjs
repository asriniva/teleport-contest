import './pure-js-probes/deny-wasm.mjs';
import {createProbe,createReference,loadFixture,fixtureImports} from './pure-js-fixtures/load.mjs';
import {DataView as FixtureDataView} from './native-test-backend.mjs';
// Actual unchanged EmC OBJNAM versus the imported JS translation.
// Foreign gameplay dependencies are controlled C functions, not C naming policy.
import assert from './native-test-assert.mjs';
import fs from 'node:fs';
import {resolve} from 'node:path';
import {pathToFileURL} from 'node:url';
import * as core from '../js/ported/objnam.js';
import {callObjnam,objnamState,createObjnamEnvironment} from '../js/nethack/bindings/objnam.js';
import {C,R,T,withCEnvironment} from '../js/c-runtime/context.js';
const custom=process.env.TELEPORT_OBJNAM_PROBE_DIR,dir=resolve(custom??'.cache/tu-probes');
const path=k=>pathToFileURL(resolve(dir,(custom?'':'objnam-')+k+'.mjs'));
const {default:referenceFactory}=await loadFixture("objnam",path('reference'));
const {default:hybridFactory}=await loadFixture("objnam",path('hybrid'));
const reference=await referenceFactory();
function text(m,p){p=Number(p);if(!p)return null;let end=p;while(m.HEAPU8[end])end++;return Buffer.from(m.HEAPU8.slice(p,end)).toString('latin1');}
const raw={};for(let i=0;i<reference._probe_layout_count();i++)raw[text(reference,reference._probe_layout_name(i))]=reference._probe_layout_value(i);
const L={};for(const[k,v]of Object.entries(raw))L[k]=raw['constwidth_'+k]===8n?(raw['constsigned_'+k]?BigInt.asIntN(64,v):BigInt.asUintN(64,v)):Number(BigInt.asIntN(64,v));
const contexts=new WeakMap(),lastServices=new WeakMap();
const runtime={objnam(s,n,...a){
 lastServices.set(s.moduleKey,s);const cfg=contexts.get(s.moduleKey);
 if(!cfg)return callObjnam(s,L,n,...a);
 const label=cfg.depth?'nested':cfg.label;cfg.depth++;
 const current=new Proxy(s,{get(t,k,r){
  const value=Reflect.get(t,k,r);
  if(k==='strlen'||k==='Strlen_')return(...args)=>{cfg.events.push(label);return value(...args);};
  return value;
 }});
 try{return callObjnam(current,cfg.layout??L,n,...a);}finally{cfg.depth--;}
},objnamState(s){lastServices.set(s.moduleKey,s);return objnamState(s);}};
const hybrid=await hybridFactory({nethackPorted:runtime});const modules=[reference,hybrid];
const names=['strprepend','nextobuf','releaseobuf','maybereleaseobuf','obj_typename','simple_typename','safe_typename','obj_is_pname','distant_name','fruitname','fruit_from_indx','fruit_from_name','reorder_fruit','xcalled','xname','xname_flags','minimal_xname','mshot_xname','the_unique_obj','the_unique_pm','add_erosion_words','erosion_matters','doname_base','doname','doname_with_price','doname_vague_quan','not_fully_identified','corpse_xname','cxname','cxname_singular','killer_xname','short_oname','singular','just_an','an','An','the','The','aobjnam','yobjnam','Yobjnam2','Tobjnam','Doname2','paydoname','yname','Yname2','ysimple_name','Ysimple_name2','simpleonames','ansimpleoname','thesimpleoname','actualoname','bare_artifactname','otense','vtense','singplur_lookup','singplur_compound','makeplural','makesingular','ch_ksound','badman','wishymatch','rnd_otyp_by_wpnskill','rnd_otyp_by_namedesc','shiny_obj','set_wallprop_from_str','wizterrainwish','dbterrainmesg','readobjnam_init','readobjnam_preparse','readobjnam_parse_charges','readobjnam_postparse1','readobjnam_postparse2','readobjnam_postparse3','readobjnam','rnd_class','Japanese_item_name','armor_simple_name','suit_simple_name','cloak_simple_name','helm_simple_name','gloves_simple_name','boots_simple_name','shield_simple_name','shirt_simple_name','mimic_obj_name','safe_qbuf'];
assert.equal(names.length,87);for(const name of names)assert.equal(typeof core[name],'function',name);
for(let i=0;i<hybrid._probe_layout_count();i++){const key=text(hybrid,hybrid._probe_layout_name(i));assert.equal(hybrid._probe_layout_value(i),raw[key],key);}
const stack=modules.map(m=>m._probe_stack()),seen=new Set();let comparisons=0,context='';
function write(m,i,s){const p=Number(m._probe_buffer(i));m.HEAPU8.fill(0,p,p+4096);m.HEAPU8.set(Buffer.from(s+'\0','latin1'),p);return BigInt(p);}
function reset(){for(const m of modules)m._probe_reset();}
function both(fn){for(let i=0;i<modules.length;i++)fn(modules[i],i);}
function run(name,args=()=>[],label=''){
 context=name+' '+label;const id=names.indexOf(name);assert.notEqual(id,-1);seen.add(name);
 const values=modules.map((m,i)=>{const a=args(m,i).map(x=>BigInt(x??0));while(a.length<8)a.push(0n);try{m._probe_invoke(id,...a);}catch(error){console.error('OBJNAM failing entry',context,'module',i,'args',a.map(String));throw error;}return [text(m,m._probe_result()),text(m,m._probe_trace()),text(m,m._probe_snapshot()),Array.from({length:4},(_,j)=>new FixtureDataView(m.HEAPU8.buffer).getInt32(Number(m._probe_ints())+j*4,true)),Array.from({length:4},(_,j)=>text(m,m._probe_buffer(j)))];});
 assert.deepEqual(values[1],values[0],context);for(let i=0;i<modules.length;i++)assert.equal(modules[i]._probe_stack(),stack[i],context+' stack');assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);comparisons++;return values[0][0];
}
// Every source grammar transformation is exercised against the same libc bytes.
const words=['','apple','orange','The Eye of the Aethiopica','a newt','an erinys','the invisible erinys','they','you','pair of boots','child','cubus','homunculus','Cyclops','djinni','erinys','foot','fungus','goose','knife','candelabrum','louse','mouse','mumak','nemesis','ovum','ox','passerby','vortex','serum','staff','tooth','fish','piranha','craft','aircraft','hovercraft','slice','mongoose','box','fox','church','dish','lotus','tengu','hezrou','wumpus','manes','nurse','axe','clove','nerve','leaf','life','wolf','dwarf','human','shaman','woman','German','Roman','Ottoman','chessman','Ahriman','specimen','dolmen','batman','staff of fire','lump of royal jelly','gloves of power','boots called bar','potato','tomato','matzo','matzoh','alga','baluchitherium','monarch','stomach','psych','tech','myth','ninja','samurai','ki-rin','Nazgul','Bordeaux','mouthful of gold','the red dragon','3 knives'];
for(const word of words){for(const fn of ['makeplural','makesingular','an','An','the','The']){reset();run(fn,m=>[write(m,0,word)],word);}for(const verb of ['are','have','hit','carry','go','wash','watch']){reset();run('vtense',m=>[write(m,0,word),write(m,1,verb)],word+' '+verb);}}
reset();assert.equal(run('makeplural',m=>[write(m,0,'child')]),'children');reset();assert.equal(run('makesingular',m=>[write(m,0,'children')]),'child');reset();assert.equal(run('an',m=>[write(m,0,'apple')]),'an apple');
// Buffer pool wraps, releases interior addresses, and never aliases Modules.
reset();let first=modules.map(()=>0n);for(let i=0;i<25;i++){run('nextobuf');both((m,j)=>{const p=m._probe_return();if(i===0)first[j]=p;if(i===12||i===24)assert.equal(p,first[j]);});}
run('releaseobuf',m=>[m._probe_return()+80n]);run('nextobuf');run('maybereleaseobuf',m=>[m._probe_return()+255n]);run('nextobuf');
reset();run('strprepend',m=>{const p=write(m,0,'x'.repeat(80)+'sword');return[p+80n,write(m,1,'long ')];});
for(let typ=0;typ<Number(L.NUM_OBJECTS);typ++)for(const fn of ['obj_typename','simple_typename','safe_typename']){reset();run(fn,()=>[typ],String(typ));}
for(const typ of [-1,Number(L.NUM_OBJECTS),9999]){reset();run('safe_typename',()=>[typ],String(typ));}
console.log('OBJNAM initial',comparisons,'exact comparisons; next object/parser cases pending');
// All object-class formatting uses actual configured objects/monsters tables.
const objectFns=['xname','xname_flags','minimal_xname','mshot_xname','obj_is_pname','the_unique_obj','erosion_matters','doname_base','doname','doname_with_price','doname_vague_quan','not_fully_identified','corpse_xname','cxname','cxname_singular','killer_xname','Doname2','yname','Yname2','ysimple_name','Ysimple_name2','simpleonames','ansimpleoname','thesimpleoname','actualoname','bare_artifactname','armor_simple_name','suit_simple_name','cloak_simple_name','helm_simple_name','gloves_simple_name','boots_simple_name','shield_simple_name','shirt_simple_name'];
for(let typ=0;typ<Number(L.NUM_OBJECTS);typ++){
 reset();both(m=>m._probe_item(0,typ,1n,0));
 for(const fn of ['xname','simpleonames','doname'])run(fn,m=>[m._probe_obj(0)],'otyp '+typ);
}
for(const typ of [L.LONG_SWORD,L.ARROW,L.POT_WATER,L.WAN_WISHING,L.RIN_INCREASE_DAMAGE,L.CORPSE,L.EGG,L.SLIME_MOLD,L.TIN,L.STATUE,L.HEAVY_IRON_BALL,L.LEATHER_GLOVES,L.BOOTS,L.T_SHIRT,L.SPE_NOVEL].filter(x=>x!==undefined)){
 for(const bits of [0,3,7,15,23,63,127,255,4095]){
  reset();both(m=>{m._probe_item(0,typ,3n,2);m._probe_bits(0,bits);});
  for(const fn of objectFns){
   const args=m=>fn==='corpse_xname'?[m._probe_obj(0),write(m,0,'cursed partly eaten'),0]:fn==='doname_base'?[m._probe_obj(0),0]:fn==='xname_flags'?[m._probe_obj(0),0]:[m._probe_obj(0)];
   run(fn,args,typ+' bits '+bits);
  }
 }
}
// Large long quantities retain all low bits through C casts and formatting.
for(const quantity of [1n,2n,9007199254740993n,9223372036854775807n]){
 reset();both(m=>{m._probe_item(0,L.LONG_SWORD,quantity,3);m._probe_bits(0,7);});run('doname',m=>[m._probe_obj(0)],'quan '+quantity);
}
// Naming aliases, exact callback identities, shortened copies and restoration.
for(const length of [3,11,12,40,200]){
 reset();both(m=>{m._probe_bits(0,7);m._probe_name(0,0,write(m,5,'named '+ 'N'.repeat(length)));m._probe_name(0,1,write(m,6,'called '+ 'U'.repeat(length)));});
 run('xcalled',m=>[write(m,0,''),80,write(m,1,'of '),write(m,2,'a name')]);
 for(const fn of ['xname','minimal_xname','killer_xname','doname'])run(fn,m=>[m._probe_obj(0)],'longname '+length);
 for(const limit of [8,20,80,255])run('short_oname',m=>[m._probe_obj(0),m._probe_callback(0),m._probe_callback(3),limit],'limit '+limit);
 for(const callback of [0,1,2,3,4]){
  run('distant_name',m=>[m._probe_obj(0),m._probe_callback(callback)],'callback '+callback);
  run('singular',m=>[m._probe_obj(0),m._probe_callback(callback)],'callback '+callback);
 }
 // The original aobjnam/Tobjnam verb append is unbounded; a deliberately
 // saturated 200-byte name is tested by the bounded formatters, not passed
 // to that undefined-overflow combination (the C reference itself traps).
 if(length<=40){
 run('aobjnam',m=>[m._probe_obj(0),write(m,1,'hit')],'length '+length);
 run('yobjnam',m=>[m._probe_obj(0),write(m,1,'hit')]);
 run('Yobjnam2',m=>[m._probe_obj(0),write(m,1,'hit')]);
 run('Tobjnam',m=>[m._probe_obj(0),write(m,1,'hit')]);
 }
 run('otense',m=>[m._probe_obj(0),write(m,1,'carry')]);
 run('paydoname',m=>[m._probe_obj(0)]);
 for(const prefixLen of [0,20,100,250,280])run('safe_qbuf',m=>[write(m,0,''),write(m,1,'P'.repeat(prefixLen)),write(m,2,'?'),m._probe_obj(0),m._probe_callback(0),m._probe_callback(3),write(m,3,'item')],'prefix '+prefixLen);
 run('safe_qbuf',m=>{const p=write(m,0,'Already ');return[p,p,write(m,1,'?'),m._probe_obj(0),m._probe_callback(0),m._probe_callback(3),write(m,3,'item')];},'aliased prefix');
}
for(const word of words){reset();run('ch_ksound',m=>[write(m,0,word)]);run('badman',m=>[write(m,0,word),0]);run('badman',m=>[write(m,0,word),1]);run('singplur_compound',m=>[write(m,0,word)]);run('singplur_lookup',m=>{const p=write(m,0,word);return[p,p+BigInt(word.length),1,m._probe_alt()];});}
for(const [a,b]of [['pick-axe','pick axe'],['potion of water','water'],['speed boots','boots of speed'],['aluminium','aluminum'],['dwarven cloak','dwarvish cloak'],['foo','bar']])for(const invert of [0,1]){reset();run('wishymatch',m=>[write(m,0,a),write(m,1,b),invert],a+' / '+b);}
// Fruit list traversal/output cells and list reordering retain actual aliases.
reset();both(m=>{m._probe_fruit(0,7,write(m,3,'slice of pizza'),1);m._probe_fruit(1,3,write(m,4,'pear'),2);m._probe_fruit(2,12,write(m,5,'apple'),-1);});
for(const juice of [0,1])run('fruitname',()=>[juice]);
for(const id of [0,3,7,12,99])run('fruit_from_indx',()=>[id]);
for(const name of ['pear','pears','slice of pizza','slice of pizzas','apple','apples','no fruit'])for(const exact of [0,1])run('fruit_from_name',m=>[write(m,0,name),exact,m._probe_ints()],name);
run('reorder_fruit',()=>[1]);run('reorder_fruit',()=>[0]);
console.log('OBJNAM object/grammar',comparisons,'exact comparisons; unentered:',names.filter(n=>!seen.has(n)).join(','));
reset();both(m=>{m._probe_item(0,L.LONG_SWORD,1n,0);m._probe_bits(0,7);});assert.equal(run('xname',m=>[m._probe_obj(0)]),'long sword');
for(const pm of [L.PM_NEWT,L.PM_HUMAN,L.PM_MEDUSA,L.PM_HIGH_CLERIC,L.PM_LONG_WORM_TAIL].filter(x=>x!==undefined)){reset();run('the_unique_pm',m=>[m._probe_pm(pm)],String(pm));}
for(const level of [0,1,2,3]){reset();both(m=>{m._probe_scalar(8,BigInt(level));m._probe_scalar(9,BigInt(level));});run('add_erosion_words',m=>[m._probe_obj(0),write(m,0,'')],String(level));}
for(const adjective of ['apple','uranium','unicorn','one-eyed creature','honor','X-ray','European','the Eye']){reset();run('just_an',m=>[write(m,0,''),write(m,1,adjective)]);}
for(const start of [L.ARROW,L.LONG_SWORD,L.SHORT_SWORD])for(const end of [start,start+3]){reset();both(m=>m._probe_option(0,1));run('rnd_class',()=>[start,end],start+'..'+end);}
for(const skill of [L.P_DAGGER,L.P_POLEARMS,L.P_BOW,-127]){reset();both(m=>m._probe_option(0,1));run('rnd_otyp_by_wpnskill',()=>[skill]);}
for(const desc of ['shiny','sword','blank','healing','gray stone','nonexistent']){reset();both(m=>m._probe_option(0,1));run('rnd_otyp_by_namedesc',m=>[write(m,0,desc),0,0],desc);}
for(const cls of [0,L.ARMOR_CLASS,L.RING_CLASS]){reset();both(m=>m._probe_option(0,1));run('shiny_obj',()=>[cls]);}
for(const typ of [L.LONG_SWORD,L.SHORT_SWORD,L.WOODEN_HARP,L.POT_BOOZE]){reset();run('Japanese_item_name',m=>[typ,write(m,0,'fallback')]);}
for(const typ of [L.STRANGE_OBJECT,L.GOLD_PIECE,L.LONG_SWORD]){reset();both(m=>m._probe_scalar(14,BigInt(typ)));run('mimic_obj_name',m=>[m._probe_mon(0)]);}
// Persistent named artifacts use the forward nameit path; original records are
// restored by the copy-based formatters, including bytes not listed in snapshots.
reset();both(m=>{m._probe_bits(0,7);m._probe_scalar(6,BigInt(L.ART_STING));m._probe_name(0,0,write(m,5,'Sting'));m._probe_scalar(12,1n);});
assert.equal(run('obj_is_pname',m=>[m._probe_obj(0)]),'1');run('xname',m=>[m._probe_obj(0)]);run('doname',m=>[m._probe_obj(0)]);run('killer_xname',m=>[m._probe_obj(0)]);
// A valid poisoned-padding object verifies the original full struct save/restore,
// rather than only the selected semantic fields in the comparison snapshot.
reset();both(m=>m._probe_poison(0));
const objectBytes=modules.map(m=>{const p=Number(m._probe_obj(0));return m.HEAPU8.slice(p,p+L.struct_obj_size);});
run('killer_xname',m=>[m._probe_obj(0)],'full object copy including native padding');
for(let i=0;i<modules.length;i++){const p=Number(modules[i]._probe_obj(0));assert.deepEqual(modules[i].HEAPU8.slice(p,p+L.struct_obj_size),objectBytes[i],'Original object bytes restored '+i);}
const wishes=['nothing','nil','none','','blessed','a long sword','2 long swords','blessed +3 long sword','uncursed rustproof very rusty long sword','greased poisoned arrow','a pair of leather gloves','2 pairs of low boots','potion of healing','holy water','unholy water','clear potion','scroll labeled ZELGO MER','blank scroll','blank spellbook','wand of wishing (0:3)','wand of light (2:-1)','ring of protection','3 gold pieces','gold piece','tin of spinach','empty tin','tin of newt meat','newt corpse','historic statue of a newt','partly eaten food ration','glob','2 gray ooze globs','glob of black pudding','orange','slice of pizza','3 blessed slices of pizza','gray dragon scale mail','silver saber','pickax','camera','lembas','tee shirt','Accuracy','boots of speed','speed boots','amulet of poison resistance','Book of the Dead','bell of opening','candelabrum of invocation','Amulet of Yendor','real Amulet of Yendor','fake Amulet of Yendor','long sword named Blade','potion called foo','polearm','hammer','shiny','this does not exist'];
for(const wish of wishes)for(const wizard of [0,1]){
 reset();both(m=>{m._probe_scalar(0,BigInt(wizard));m._probe_option(0,1);m._probe_fruit(0,7,write(m,6,'slice of pizza'),-1);});
 run('readobjnam',m=>[write(m,0,wish),m._probe_obj(6)],'wish '+wish+' wizard '+wizard);
}
reset();both(m=>m._probe_option(0,1));run('readobjnam',m=>[0,m._probe_obj(6)],'NULL random request');
// Each parser stage also receives its original addressable record directly.
for(const phrase of ['a blessed +3 long sword','2 pairs of low boots','wand of light (2:7)','potion called foo','glob of gray ooze','silver saber','untrapped unlocked box']){
 reset();both(m=>{m._probe_scalar(0,1n);m._probe_option(0,1);});
 run('readobjnam_init',m=>[write(m,0,phrase),m._probe_data()],phrase);
 const pre=run('readobjnam_preparse',m=>[m._probe_data()],phrase);
 // Private helpers are called only along an original valid caller edge: an
 // already resolved wish must not be fed back into the next parser stage.
 if(pre==='0'){
  run('readobjnam_parse_charges',m=>[m._probe_data()],phrase);
  let code=run('readobjnam_postparse1',m=>[m._probe_data()],phrase);
  if(code==='0')code=run('readobjnam_postparse2',m=>[m._probe_data()],phrase);
  if(code==='0'||code==='1')run('readobjnam_postparse3',m=>[m._probe_data()],phrase);
 }
}
for(const phrase of ['undiggable wall','nonpasswall wall','unphaseable nondiggable wall','ordinary wall']){reset();run('set_wallprop_from_str',m=>[write(m,0,phrase)]);}
for(const phrase of ['fountain','magic fountain','throne','sink','pool','lava','ice','tree','grave','altar','lawful altar','door','locked door','wall','secret door','corridor','pit','bear trap']){
 reset();both(m=>m._probe_scalar(0,1n));run('readobjnam_init',m=>[write(m,0,phrase),m._probe_data()]);run('wizterrainwish',m=>[m._probe_data()],phrase);
}
reset();run('dbterrainmesg',m=>[write(m,0,'wall'),10,8]);
console.log('OBJNAM parser progress',comparisons,'exact comparisons; unentered:',names.filter(n=>!seen.has(n)).join(','));
// Changing same-Module dependency contexts remain live through the environment
// cache, including a nested native callback and restoration after an exception.
reset();const cfg={depth:0,label:'first',events:[]};contexts.set(hybrid,cfg);
run('an',m=>[write(m,0,'apple')],'first override');cfg.label='second';run('an',m=>[write(m,0,'orange')],'second override');
assert.ok(cfg.events.includes('first'));assert.ok(cfg.events.includes('second'));
reset();cfg.events=[];cfg.label='outer';both(m=>{m._probe_item(0,L.LONG_SWORD,3n,0);m._probe_bits(0,0);m._probe_option(240,4);m._probe_option(241,4);});
const sizes=modules.map(m=>m.HEAPU8.buffer.byteLength);run('xname',m=>[m._probe_obj(0)],'nested dependency context + real growth');
assert.ok(cfg.events.includes('nested'),'Native callback actually reentered the source formatter');
assert.ok(cfg.events.slice(cfg.events.lastIndexOf('nested')+1).includes('outer'),'Outer dependency context restored after native reentry');
for(let i=0;i<modules.length;i++)assert.ok(modules[i].HEAPU8.buffer.byteLength>sizes[i],'Actual heap growth '+i);
contexts.delete(hybrid);
const services=lastServices.get(hybrid),sentinel={rectState:{marker:'R'},trackState:{marker:'T'}},savedStack=hybrid._probe_stack();
const throwing=new Proxy(services,{get(t,k,r){if(k==='strlen'||k==='Strlen_')return()=>{throw Error('OBJNAM dependency exception witness');};return Reflect.get(t,k,r);}});
withCEnvironment(sentinel,()=>{
 assert.throws(()=>callObjnam(throwing,L,'an',write(hybrid,0,'apple')),/OBJNAM dependency exception witness/);
 assert.equal(C,sentinel);assert.equal(R,sentinel.rectState);assert.equal(T,sentinel.trackState);
});
assert.equal(hybrid._probe_stack(),savedStack);assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);
reset();assert.equal(run('an',m=>[write(m,0,'apple')],'normal services restored after exception'),'an apple');
// Cache identity includes external immutable layout identity; direct constructor
// calls themselves remain fresh and do not publish their result as the cache.
let layoutReads=0;const otherLayout={...L};Object.defineProperty(otherLayout,'BUFSZ',{enumerable:true,get(){layoutReads++;return L.BUFSZ;}});
callObjnam(services,otherLayout,'an',write(hybrid,0,'apple'));const firstReads=layoutReads;assert.ok(firstReads>0);
callObjnam(services,otherLayout,'an',write(hybrid,0,'orange'));assert.equal(layoutReads,firstReads,'Same external layout identity reuses validated environment');
assert.notEqual(createObjnamEnvironment(services,L,objnamState(services)),createObjnamEnvironment(services,L,objnamState(services)),'Direct constructor remains fresh');
// A failed constructor is never published. Retry uses the original native
// helpers on another actual Module, and source static state never crosses it.
const second=await hybridFactory({nethackPorted:runtime});second._probe_reset();const s2=lastServices.get(second);let fail=true;
const failed=new Proxy(s2,{get(t,k,r){const value=Reflect.get(t,k,r);if(k==='literal')return(...a)=>{if(fail){fail=false;throw Error('OBJNAM constructor failure witness');}return value(...a);};return value;}});
const secondStack=second._probe_stack();assert.throws(()=>callObjnam(failed,L,'an',write(second,0,'apple')),/OBJNAM constructor failure witness/);
assert.equal(second._probe_stack(),secondStack);assert.equal(C,undefined);
assert.equal(text(second,callObjnam(s2,L,'an',write(second,0,'apple'))),'an apple','Successful constructor retry');
const secondIndex=objnamState(s2).obufidx;callObjnam(services,L,'an',write(hybrid,0,'orange'));assert.equal(objnamState(s2).obufidx,secondIndex,'Independent Module buffer index');
const secondPool=Number(second._probe_pool()),primaryPool=Number(hybrid._probe_pool());second.HEAPU8[secondPool]=37;hybrid.HEAPU8[primaryPool]=91;assert.equal(second.HEAPU8[secondPool],37,'Independent actual native storage');
// Run a real comparison pair on the second Module after its independent cache
// construction and a second native C-to-JS reentry/growth event.
modules[1]=second;stack[1]=second._probe_stack();reset();both(m=>{m._probe_item(0,L.LONG_SWORD,3n,0);m._probe_bits(0,0);m._probe_option(240,4);m._probe_option(241,4);});
const beforeSecond=second.HEAPU8.buffer.byteLength;run('xname',m=>[m._probe_obj(0)],'second actual Module native reentry/growth');assert.ok(second.HEAPU8.buffer.byteLength>beforeSecond);
for(const fn of ['makeplural','doname','safe_typename']){reset();run(fn,m=>fn==='makeplural'?[write(m,0,'children')]:fn==='doname'?[m._probe_obj(0)]:[L.LONG_SWORD],'second Module');}
modules[1]=hybrid;stack[1]=hybrid._probe_stack();
assert.deepEqual(names.filter(n=>!seen.has(n)),[],'All 87 original functions entered');
console.log(`OBJNAM: ${comparisons} exact EmC comparisons; all 87 functions, original catalogues/grammar/wishes, native callback identity/reentry, actual growth, changing cached service contexts, constructor retry, two Modules and C/R/T/stack restoration pass.`);
