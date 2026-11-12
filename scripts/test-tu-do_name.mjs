// Exact original EmC versus imported JS; foreign naming/UI dependencies controlled.
import assert from './native-test-assert.mjs';
import {resolve} from 'node:path';import{pathToFileURL}from'node:url';
import * as data from '../js/ported/do_name.js';import{callDoName,initializeDoName}from'../js/nethack/bindings/do_name.js';import{C,R,T}from'../js/c-runtime/context.js';
const dir=resolve(process.env.TELEPORT_DO_NAME_PROBE_DIR??'.cache/tu-probes');const path=k=>pathToFileURL(resolve(dir,(process.env.TELEPORT_DO_NAME_PROBE_DIR?'':'do_name-')+k+'.mjs'));
const{default:rf}=await import(path('reference')),{default:hf}=await import(path('hybrid'));const reference=await rf();
function text(m,p){p=Number(p);if(!p)return null;let e=p;while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.slice(p,e)).toString('latin1');}
const L={strings:{}};for(let i=0;i<reference._probe_layout_count();i++)L[text(reference,reference._probe_layout_name(i))]=Number(reference._probe_layout_value(i));for(let i=0;i<reference._probe_string_count();i++)L.strings[text(reference,reference._probe_string_name(i))]=text(reference,reference._probe_string_value(i));
const runtime={initializeDoName,do_name:(services,name,...args)=>callDoName(new Proxy(services,{get(target,key,receiver){if(['rectState','trackState'].includes(key))return target[key];if(!Reflect.has(target,key))throw Error('Missing DO_NAME service '+String(key));return Reflect.get(target,key,receiver);}}),L,name,...args)};
const modules=[reference,await hf({nethackPorted:runtime})],stacks=modules.map(m=>m._probe_stack());let comparisons=0,context='';
for(let i=0;i<6;i++){assert.equal(modules[1]._probe_startup_bogon(i),reference._probe_startup_bogon(i),'Native constructor observes original bogon byte '+i);comparisons++;}

const names=['nextmbuf','new_mgivenname','free_mgivenname','new_oname','free_oname','safe_oname','name_from_player','christen_monst','alreadynamed','do_mgivenname','do_oname','oname','objtyp_is_callable','name_ok','call_ok','docallcmd','docall_xname','docall','namefloorobj','rndghostname','x_monnam','l_monnam','mon_nam','noit_mon_nam','some_mon_nam','Monnam','noit_Monnam','Some_Monnam','noname_monnam','m_monnam','y_monnam','YMonnam','Adjmonnam','a_monnam','Amonnam','distant_monnam','mon_nam_too','monverbself','minimal_monnam','Mgender','pmname','mon_pmname','obj_pmname','bogusmon','rndmonnam','bogon_is_pname','roguename','hcolor','rndcolor','hliquid','coyotename','rndorcname','christen_orc','noveltitle','lookup_novel'];
const reached=new Set();function snapshot(m){return{state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace()),result:text(m,m._probe_result())};}function check(){assert.deepEqual(snapshot(modules[1]),snapshot(reference),context);modules.forEach((m,i)=>assert.equal(m._probe_stack(),stacks[i]));assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);comparisons++;}
function call(name,...args){const values=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(values[1],values[0],context+name);check();return values[0];}
const mon=i=>m=>m._probe_mon(i),obj=i=>m=>m._probe_obj(i),pm=i=>m=>m._probe_pm(i),buf=i=>m=>m._probe_buffer(i),box=(i,v)=>m=>m._probe_int(i,v);
const strings=new WeakMap();function str(value){return m=>{if(value===null)return 0n;let cache=strings.get(m);if(!cache)strings.set(m,cache=new Map());const b=Buffer.from(value,'latin1');let p=cache.get(value);if(!p){p=m._malloc(BigInt(Math.max(b.length+1,8192)));cache.set(value,p);}m.HEAPU8.set(b,Number(p));m.HEAPU8[Number(p)+b.length]=0;return BigInt(p);};}
function invoke(name,...args){context=name+' '+JSON.stringify(args.map(a=>typeof a==='bigint'?String(a):typeof a));reached.add(name);const pointers=modules.map(m=>m._probe_invoke(names.indexOf(name),...Array.from({length:5},(_,i)=>typeof args[i]==='function'?BigInt(args[i](m)):BigInt(args[i]??0))));if(['new_mgivenname','new_oname'].includes(name)&&Number(args[1])>0)for(const m of modules)m.HEAPU8[Number(m._probe_name(name==='new_oname'?1:0))]=0;check();return pointers;}
const reset=()=>call('reset'),opt=(k,v)=>call('option',k,v),input=s=>{for(const m of modules)m._probe_input(str(s)(m));check();},prop=(k,a=0n,b=0n,c=0n)=>call('property',k,BigInt(a),BigInt(b),BigInt(c)),field=(i,f,v,pm=-1)=>call('monset',i,pm,f,BigInt(v)),item=(typ,quan=1n,f=0,v=1)=>call('item',0,typ,BigInt(quan),f,v),trace=()=>snapshot(reference).trace,result=()=>snapshot(reference).result;
for(const m of modules)for(let i=0;i<m._probe_layout_count();i++)assert.equal(Number(m._probe_layout_value(i)),L[text(m,m._probe_layout_name(i))]);
for(const[t,key]of ['ghostnames','hcolors','hliquids','coynames','sir_Terry_novels'].entries()){assert.equal(reference._probe_table_count(t),data[key].length);for(const[i,s]of data[key].entries())assert.equal(text(reference,reference._probe_table_text(t,i)),s);}
reset();const rows=Array.from({length:7},()=>invoke('nextmbuf'));for(let k=0;k<2;k++)for(let i=0;i<2;i++)assert.equal(rows[k][i],rows[k+5][i]);
// Old returned pointers keep the original five-row overwrite behavior.
reset();const oldNames=[];for(let i=0;i<7;i++){invoke('christen_monst',mon(0),str('Fido'+i));oldNames.push(invoke('mon_nam',mon(0)));}for(let k=0;k<2;k++){assert.equal(oldNames[0][k],oldNames[5][k]);assert.equal(text(modules[k],oldNames[0][k]),'Fido5');assert.equal(text(modules[k],oldNames[1][k]),'Fido6');}
for(const value of ['', 'Alice', '  A long   name  ', 'X'.repeat(180)]){reset();invoke('christen_monst',mon(0),str(value));invoke('safe_oname',obj(0));invoke('oname',obj(0),str(value),0);invoke('safe_oname',obj(0));invoke('free_mgivenname',mon(0));invoke('free_oname',obj(0));}
reset();invoke('new_mgivenname',mon(0),32);invoke('free_mgivenname',mon(0));invoke('free_mgivenname',mon(0));invoke('new_oname',obj(0),32);invoke('free_oname',obj(0));invoke('new_mgivenname',mon(0),0);invoke('new_oname',obj(0),0);
for(const value of ['', '\x1b', '  Alice   Smith  ', 'X'.repeat(180)]){reset();input(value);invoke('name_from_player',buf(0),str('Prompt?'),0);assert.ok(result()==='[NULL]'||result().length<L.PL_PSIZ);}
for(const typ of [L.DAGGER,L.POT_WATER,L.AMULET_OF_YENDOR,L.FAKE_AMULET_OF_YENDOR,L.SPE_NOVEL,L.HEAVY_IRON_BALL,L.FIGURINE,L.TOWEL,L.TIN,L.STATUE])for(const known of [0,1]){reset();item(typ,3n,0,known);invoke('objtyp_is_callable',typ);invoke('name_ok',obj(0));invoke('call_ok',obj(0));invoke('docall_xname',obj(0));}
for(const value of ['Alice',' ','','\x1b'])for(const old of [0,1]){reset();item(L.POT_WATER);if(old){input('old');invoke('docall',obj(0));}input(value);invoke('docall',obj(0));}
for(const typ of [L.DAGGER,L.SPE_NOVEL,L.POT_WATER])for(const artifact of [0,1]){reset();item(typ,1n,12,artifact?L.ART_STING:0);input('New Name');invoke('do_oname',obj(0));}
for(const reject of [0,1]){reset();opt(10,1);opt(11,L.DAGGER);opt(12,reject);opt(14,1);input('Sting');invoke('do_oname',obj(0));}
for(const typ of [L.PM_HUMAN,L.PM_GHOST,L.PM_JUIBLEX,L.PM_SHOPKEEPER,L.PM_HIGH_CLERIC,L.PM_WIZARD_OF_YENDOR,L.PM_WIZARD])for(const gender of [0,1])for(const article of [L.ARTICLE_NONE,L.ARTICLE_THE,L.ARTICLE_A,L.ARTICLE_YOUR])for(const suppress of [0,L.EXACT_NAME,L.SUPPRESS_IT|L.AUGMENT_IT]){reset();field(0,0,gender,typ);invoke('x_monnam',mon(0),article,str('angry'),suppress,0);}
for(const bit of [1,2,3,4,5,6,7,8,9,10,11]){reset();field(0,bit,1);invoke('x_monnam',mon(0),L.ARTICLE_THE,0,0,1);}
for(const visible of [0,1])for(const augmented of [0,L.AUGMENT_IT])for(const hallucination of [0,1]){reset();opt(1,visible);prop(L.HALLUC,BigInt(hallucination));invoke('x_monnam',mon(0),L.ARTICLE_THE,0,augmented,0);}
for(const name of ['Fido','Killer the Student','Ghostly'])for(const typ of [L.PM_HUMAN,L.PM_GHOST,L.PM_WIZARD]){reset();field(0,0,0,typ);invoke('christen_monst',mon(0),str(name));invoke('x_monnam',mon(0),L.ARTICLE_THE,str('angry'),0,0);invoke('x_monnam',mon(0),L.ARTICLE_THE,0,0,1);}
for(const name of ['l_monnam','mon_nam','noit_mon_nam','some_mon_nam','Monnam','noit_Monnam','Some_Monnam','noname_monnam','m_monnam','y_monnam','YMonnam','Adjmonnam','a_monnam','Amonnam']){reset();invoke(name,mon(0),name==='Adjmonnam'?str('silly'):0);}
for(const same of [0,1])for(const gender of [0,1,2,3]){reset();opt(16,gender);invoke('mon_nam_too',mon(0),mon(same?0:1));invoke('monverbself',mon(0),str('Human'),'hit'&&str('hit'),str('with a stick'));}
for(const who of [-1,0,3]){reset();invoke('minimal_monnam',mon(who),1);invoke('Mgender',mon(who<0?0:who));}
reset();invoke('pmname',pm(L.PM_HUMAN),-1);invoke('pmname',pm(L.PM_HUMAN),0);invoke('mon_pmname',mon(0));
for(const typ of [L.CORPSE,L.STATUE,L.FIGURINE,L.DAGGER])for(const flags of [L.CORPSTAT_MALE,L.CORPSTAT_FEMALE,L.CORPSTAT_RANDOM]){reset();item(typ,1n,10,L.PM_ALIGNED_CLERIC);item(typ,1n,9,flags);invoke('obj_pmname',obj(0));}
for(const value of ['', '-Private Name','_Some Name','+Proper','|nonproper','=Other','unmarked']){reset();for(const m of modules)m._probe_random(str(value)(m));invoke('bogusmon',buf(0),buf(1));}
for(const code of [0,45,95,43,124,61,97,128,255,256,257,-129]){reset();invoke('bogon_is_pname',code);}
for(const seed of [1,2,7,42])for(const hallu of [0,1]){reset();call('seed',seed);opt(0,1);prop(L.HALLUC,BigInt(hallu));invoke('rndghostname');invoke('rndmonnam',buf(1));invoke('hcolor',str('blue'));invoke('hcolor',str(''));invoke('hcolor',0);invoke('rndcolor');invoke('hliquid',str('water'));invoke('hliquid',str(''));invoke('coyotename',mon(0),buf(0));invoke('rndorcname',buf(0));invoke('christen_orc',mon(0),str('gang'),str('friend'));}
for(const env of [0,1]){reset();opt(17,env);invoke('roguename');}
for(const idx of [-5,-1,0,4,40,41,100]){reset();invoke('noveltitle',box(0,idx));call('intvalue',0);}
for(const title of ['', 'Sorcery', 'Masquerade', 'The Color of Magic','The Amazing Maurice','Thud',...data.sir_Terry_novels]){reset();invoke('lookup_novel',str(title),box(0,-1));call('intvalue',0);}
for(const key of [109,105,111,102,100,97,113,0]){reset();call('global',7,key);invoke('docallcmd');}
for(const selected of [109,105,111,102,100,97,113]){reset();opt(21,1);opt(22,selected);invoke('docallcmd');}
for(const glyph of [L.GLYPH_OBJ_OFF,L.GLYPH_OBJ_OFF+L.FIRST_OBJECT-1,L.GLYPH_OBJ_PILETOP_OFF+L.FIRST_OBJECT-2,L.GLYPH_OBJ_PILETOP_OFF+L.FIRST_OBJECT-1,L.GLYPH_OBJ_PILETOP_OFF+L.FIRST_OBJECT,L.GLYPH_BODY_OFF,L.GLYPH_STATUE_FEM_OFF,L.GLYPH_SWALLOW_OFF]){reset();opt(6,12);opt(20,glyph);invoke('namefloorobj');}
for(const reject of [0,1]){reset();opt(8,reject?-1:0);invoke('do_mgivenname');invoke('namefloorobj');}
reset();invoke('alreadynamed',mon(0),str('human'),str('human'));
reset();field(0,3,1,L.PM_HIGH_CLERIC);call('global',11,5);invoke('distant_monnam',mon(0),L.ARTICLE_THE,buf(0));
for(const stage of [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17]){reset();opt(50,stage);opt(51,stage);const before=modules.map(m=>m.HEAPU8.byteLength);
 if(stage===1||stage===2||stage===7||stage===9){if(stage===2){opt(10,1);opt(11,L.DAGGER);opt(12,1);}input('Name');invoke('do_oname',obj(0));if(stage===1)invoke('alreadynamed',mon(0),str('human'),str('human'));}
 else if(stage===3){opt(6,12);opt(7,10);opt(20,L.GLYPH_OBJ_OFF);opt(23,-1);invoke('namefloorobj');}
 else if(stage===4){field(1,5,1,L.PM_SHOPKEEPER);opt(6,11);invoke('do_mgivenname');}
 else if(stage===5||stage===12){opt(14,1);invoke('oname',obj(0),str('Sting'),L.ONAME_VIA_NAMING);}
 else if(stage===6){invoke('christen_monst',mon(0),str('Fido'));}
 else if(stage===8){call('global',7,105);invoke('docallcmd');}
 else if(stage===10){invoke('bogusmon',buf(0),buf(1));}
 else if(stage===11){invoke('docall_xname',obj(0));}
 else if(stage===13){invoke('do_mgivenname');}
 else if(stage===14){field(0,3,1);invoke('x_monnam',mon(0),L.ARTICLE_THE,0,0,0);}
 else if(stage===15){field(0,7,1);invoke('christen_monst',mon(0),str('Fido'));}
 else if(stage===16){opt(21,0);invoke('docallcmd');}
 else if(stage===17){opt(6,12);opt(7,10);opt(20,L.GLYPH_OBJ_OFF);invoke('namefloorobj');}
 assert.match(trace(),/nested:/,'stage '+stage);assert.match(trace(),new RegExp('grow:'+stage+';'),'stage '+stage);modules.forEach((m,i)=>assert.ok(m.HEAPU8.byteLength>before[i],'growth '+stage));}
assert.deepEqual([...reached].sort(),names.slice().sort());
const other=await hf({nethackPorted:runtime});other._probe_reset();other._probe_invoke(names.indexOf('mon_nam'),other._probe_mon(0),0n,0n,0n,0n);assert.equal(text(other,other._probe_result()),'the human');assert.equal(C,undefined);
console.log(`DO_NAME first-pass EmC: ${comparisons} exact comparisons passed; all 55 functions; native/shared/public gates pending.`);
