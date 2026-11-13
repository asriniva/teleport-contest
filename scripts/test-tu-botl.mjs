import {nativeFixtureServices} from './native-pet-combat-fixture.mjs';
import {createStatusFieldPlans} from '../js/nethack/status.js';
import {pathToFileURL} from 'node:url';
import {resolve as resolvePath} from 'node:path';
const nativeExecution=process.env.NATIVE_BOTL_FIXTURE==='1',nativeServices=new WeakMap();
function statusServices(s){if(!nativeExecution)return s;let local=nativeServices.get(s);if(!local){local=nativeFixtureServices(s,{}).services;local.nativeFieldPlans=createStatusFieldPlans(s.moduleKey.environment);nativeServices.set(s,local);}return local;}
import './pure-js-probes/deny-wasm.mjs';
import {createProbe,createReference,loadFixture,fixtureImports} from './pure-js-fixtures/load.mjs';
import {DataView as FixtureDataView} from './native-test-backend.mjs';
import assert from './native-test-assert.mjs';
import {referenceBackend,assertStackRestored} from './native-test-backend.mjs';
import {readFileSync,writeFileSync} from 'node:fs';
import {callBotl,botlSchema,botlGlobals} from '../js/nethack/bindings/botl.js';
import * as data from '../js/ported/botl-data.js';
import {memoryCheckpoint,assertMemoryGrowth} from './native-test-backend.mjs';
import {C,R,T,withCEnvironment} from '../js/c-runtime/context.js';
// Original C reference is available through the isolated reference process.
const own=process.env.TELEPORT_BOTL_AUTHOR==='1';
const referenceFactory=(await loadFixture("botl",process.env.BOTL_PROBE_DIR?pathToFileURL(resolvePath(process.env.BOTL_PROBE_DIR,'reference.mjs')):own?'../.cache/botl-author/reference.mjs':'../.cache/tu-probes/botl-reference.mjs')).default;
const hybridFactory=(await loadFixture("botl",process.env.BOTL_PROBE_DIR?pathToFileURL(resolvePath(process.env.BOTL_PROBE_DIR,'hybrid.mjs')):own?'../.cache/botl-author/hybrid.mjs':'../.cache/tu-probes/botl-hybrid.mjs')).default;
const text=(m,p)=>{p=Number(p);let end=p;while(m.HEAPU8[end])end++;return Buffer.from(m.HEAPU8.slice(p,end)).toString('latin1');};
const reference=await referenceBackend('botl',referenceFactory)();
const measured={};for(let i=0;i<reference._probe_layout_count();i++){const raw=BigInt.asIntN(64,reference._probe_layout_value(i));measured[text(reference,reference._probe_layout_name(i))]=Number.isSafeInteger(Number(raw))?Number(raw):String(raw);}
const L=own?measured:JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url))).botl;
if(own)writeFileSync(new URL('../.cache/botl-author/layout.json',import.meta.url),JSON.stringify(L,null,2));
for(const m of readFileSync(new URL('./test-tu-botl.mjs',import.meta.url),'utf8').matchAll(/\bL\.([A-Z]\w*)/g))assert.ok(Object.hasOwn(L,m[1]),'compiled fixture value '+m[1]);
const servicesByModule=new Map();const ported={callBotl(s,n,...a){s=statusServices(s);servicesByModule.set(s.moduleKey,s);return callBotl(s,L,n,...a);}};
let modules=[reference,await hybridFactory({nethackPorted:ported})],stacks=modules.map(m=>m._probe_stack()),comparisons=0,expectedScope;
const names=Array.from({length:76},(_,i)=>text(reference,reference._probe_function_name(i))),exercised=new Set();
const snapshot=m=>m.isolatedCReference?m.observe('const text='+text.toString()+';return {state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace())};',{}):({state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace())});
function check(){const pair=modules.map(snapshot);if(pair[0].state!==pair[1].state||pair[0].trace!==pair[1].trace)writeFileSync(new URL('../.cache/botl-author/difference.json',import.meta.url),JSON.stringify(pair,null,2));assert.deepEqual(pair[1],pair[0]);modules.forEach((m,i)=>assertStackRestored(m,stacks[i],m._probe_stack()));assert.equal(C,expectedScope);assert.equal(R,expectedScope?.rectState);assert.equal(T,expectedScope?.trackState);comparisons++;}
function call(n,...a){const pair=modules.map(m=>m['_probe_'+n](...a));assert.deepEqual(pair[1],pair[0],n);comparisons++;return pair[0];}
function act(n,...a){const op=names.indexOf(n);assert.ok(op>=0,n);exercised.add(n);const result=call('action',op,...Array.from({length:6},(_,i)=>BigInt(a[i]??0)));check();return result;}
const reset=()=>{call('reset');check();},hero=(k,v)=>call('hero',k,BigInt(v)),stat=(i,k,v)=>call('stat',i,k,BigInt(v));
function input(i,s){for(const m of modules){const p=m._malloc(BigInt(Buffer.byteLength(s,'latin1')+1));m.HEAPU8.set(Buffer.from(s+'\0','latin1'),Number(p));m._probe_text(i,BigInt(p));m._free(BigInt(p));}comparisons++;}
const result=()=>{const pair=modules.map(m=>text(m,m._probe_result_text()));assert.equal(pair[1],pair[0]);comparisons++;return pair[0];};
const sourceCore=readFileSync(new URL('../js/ported/botl.js',import.meta.url),'utf8').replace(/"(?:\\.|[^"\\])*"|'(?:\\.|[^'\\])*'|\/\*[\s\S]*?\*\//g,'');const externals=new Set([...sourceCore.matchAll(/\bC\.(\w+)/g)].map(m=>m[1]));const fullEnvironment=callBotl(servicesByModule.get(modules[1]),L,'environment');assert.deepEqual([...externals].filter(n=>!(n in fullEnvironment)),[],'all source-used ABI/header bindings exist');comparisons++;
for(const m of modules)assert.equal(m._probe_startup(),1,'foreign C sees initialized readonly tables before any BOTL function');
assert.equal(text(modules[1],modules[1]._probe_public_tables()),text(reference,reference._probe_public_tables()));comparisons++;
const resolve=v=>v?.constant?L[v.constant]:v?.operator?(v.operator==='-'?-resolve(v.value):v.operator==='|'?BigInt(resolve(v.left))|BigInt(resolve(v.right)):resolve(v.left)+resolve(v.right)):v;
for(const [ti,n]of ['initblstats','condition_aliases','fieldids_alias'].entries()){
 const rows=data[n+'_initial'];assert.equal(reference._probe_private_count(ti),rows.length);
 for(let i=0;i<rows.length;i++){const row=rows[i];if(ti===0){for(const [j,key]of ['fldname','fldfmt'].entries())assert.equal(text(reference,reference._probe_private_text(ti,i,j)),row[key]||'');for(const [j,key]of ['anytype','valwidth','idxmax','fld','percent_matters'].entries())assert.equal(reference._probe_private_number(ti,i,j),BigInt(resolve(row[key])));}else{assert.equal(text(reference,reference._probe_private_text(ti,i,0)),row[ti===1?'id':'fieldname']||'');assert.equal(reference._probe_private_number(ti,i,0),BigInt(resolve(row[ti===1?'bitmask':'fldid'])));}comparisons++;}
}
function publicPointers(m){const points=[];for(const name of ['enc_stat','terrain_descr']){const gi=botlGlobals.findIndex(g=>g.name===name),g=botlGlobals[gi],p=Number(m._probe_global(gi));for(let i=0;i<g.d.a[0];i++)points.push(new FixtureDataView(m.HEAPU8.buffer).getBigUint64(p+8*i,true));}
 for(const name of ['conditions','condtests']){const gi=botlGlobals.findIndex(g=>g.name===name),g=botlGlobals[gi],kind=g.d.e.s,k=Object.keys(botlSchema).indexOf(kind),p=Number(m._probe_global(gi));for(let i=0;i<g.d.a[0];i++){for(const [j,f]of botlSchema[kind].fields.entries())if(f.d.q||f.d.p!==undefined)points.push(m._probe_read(k,BigInt(p+i*L[kind+'Size']),j));else if(f.d.a&&f.d.e.q){const base=Number(m._probe_read(k,BigInt(p+i*L[kind+'Size']),j));for(let z=0;z<f.d.a[0];z++)points.push(new FixtureDataView(m.HEAPU8.buffer).getBigUint64(base+8*z,true));}}}
 return {strings:points.map(p=>p?text(m,p):null),aliases:points.map(p=>points.map(q=>p===q))};}
assert.deepEqual(publicPointers(modules[1]),publicPointers(reference),'all public string values, nulls and pointer alias clusters');comparisons++;
reset();
for(const n of ['get_strength_str','check_gold_symbol','do_statusline1','do_statusline2','rank','max_rank_sz','stat_update_time','exp_percentage','exp_percent_changing','stat_cap_indx','stat_hunger_indx']){act(n);if(['get_strength_str','do_statusline1','do_statusline2','rank'].includes(n))result();}
for(const n of ['xlev_to_rank','rank_to_xlev'])for(const i of [-100,0,1,2,3,5,9,14,18,22,26,30,100])act(n,i);
for(let level=1;level<=30;level++){act('rank_of',level,L.PM_HUMAN,level%2);result();}
// Actual Role catalogue traversal checks native pointer stride and all titles.
const roleKind=Object.keys(botlSchema).indexOf('Role'),nameKind=Object.keys(botlSchema).indexOf('RoleName'),roleFields=botlSchema.Role.fields,nameFields=botlSchema.RoleName.fields;
const roleBase=Number(reference._probe_global(botlGlobals.findIndex(g=>g.name==='roles'))),rf=n=>roleFields.findIndex(f=>f.name===n),nf=n=>nameFields.findIndex(f=>f.name===n);
let roleCount=0;for(;roleCount<100;roleCount++){const at=roleBase+roleCount*L.RoleSize,name=Number(reference._probe_read(roleKind,BigInt(at),rf('name'))),male=reference._probe_read(nameKind,BigInt(name),nf('m'));if(!male)break;const species=Number(BigInt.asIntN(16,reference._probe_read(roleKind,BigInt(at),rf('mnum'))));for(const level of [1,3,9,14,18,22,26,30])for(const gender of [0,1]){act('rank_of',level,species,gender);result();}const ranks=Number(reference._probe_read(roleKind,BigInt(at),rf('rank')));for(let r=0;r<9;r++)for(const gender of ['m','f']){const ptr=reference._probe_read(nameKind,BigInt(ranks+r*L.RoleNameSize),nf(gender));if(ptr){input(0,text(reference,ptr));act('title_to_mon',0,0,4);}}}assert.ok(roleCount>10&&roleCount<100);
for(const h of [0,1,2,3,4,5,6]){hero(20,h);act('stat_hunger_indx');}
for(let fld=0;fld<27;fld++){act('bl_idx_to_fldname',fld);const name=result();input(0,name);assert.equal(act('fldname_to_bl_indx',0),reference._probe_private_number(0,fld,3));}
for(const s of ['', 'normal','none','red','<50%','>100','<=50%','20%','>0','foo','==5']){input(0,s);act('noneoftheabove',0);act('is_ltgt_percentnumber',0);act('has_ltgt_percentnumber',0);}
for(const s of ['plain text','hit points','strength','carry-cap','not-a-field']){input(0,s);act('repad_with_dashes',0);act('fldname_to_bl_indx',0);}
for(const s of ['stone','slime','strngl','foodpois','termill','blind','deaf','stun','conf','hallu','lev','fly','ride','all','major troubles','bogus','']){input(0,s);act('match_str2conditionbitmask',0);act('str2conditionbitmask',0);}
for(const mask of [0n,1n,3n,(1n<<29n)-1n,1n<<63n]){act('conditionbitmask2str',mask);result();}
for(const encoded of [0,1,7,15,255,256,511,-1]){act('split_clridx',encoded,0,4);}
reset();stat(0,1,L.ANY_INT);stat(1,1,L.ANY_INT);for(const [v,max]of[[0,100],[1,3],[99,100],[-1,3],[200,100]]){stat(0,2,v);stat(1,2,max);act('compare_blstats',0,1);act('percentage',0,1);}

// The native union and formatter are exercised with actual compiled type tags.
for(const type of [L.ANY_INT,L.ANY_UINT,L.ANY_LONG,L.ANY_ULONG,L.ANY_MASK32])for(const value of [0n,1n,-1n,2147483647n,-2147483648n,9007199254740993n]){
 call('any',0,value);act('anything_to_s',0,0,type);result();input(1,String(value));act('s_to_anything',0,1,type);
 const raw=modules.map(m=>new FixtureDataView(m.HEAPU8.buffer).getBigUint64(Number(m._probe_pointer(2,0)),true));assert.equal(raw[1],raw[0]);comparisons++;
}
for(const inputText of ['hitpoints/<50%/red','strength/always/green','condition/blind/red','power/>20/blue','hitpoints/criticalhp/red','bogus/always/red','hitpoints/<bad/red','hitpoints/up/green','hitpoints/down/red','hitpoints/changed/yellow']){
 reset();input(0,inputText);act('parse_status_hl1',0,0);act('count_status_hilites');act('status_hilite_linestr_gather');act('status_hilite_linestr_countfield',L.BL_FLUSH);act('all_options_statushilites',0);act('status_hilites_viewall');act('status_hilite_linestr_done');act('clear_status_hilites');
}
reset();
for(const line of ['blind','conf','none','bogus']){input(0,line);act('parse_cond_option',0,0);act('parse_cond_option',1,0);}
for(const idx of [0,1,15,29]){input(0,'');act('opt_next_cond',idx,0);}
for(const line of ['stone+slime','blind&deaf','foo','a+b+c+d',''])for(const max of [0,1,2,16]){input(0,line);exercised.add('splitsubfields');const count=call('action',names.indexOf('splitsubfields'),0n,64n,BigInt(max),0n,0n,0n);const lists=modules.map(m=>{const cell=Number(m._probe_pointer(0,64)),dv=new FixtureDataView(m.HEAPU8.buffer),p=Number(dv.getBigUint64(cell,true));const entries=[];if(count>=0n){assert.ok(p>0);for(let i=0;i<Number(count);i++){const item=Number(dv.getBigUint64(p+8*i,true));entries.push([text(m,item),item-Number(m._probe_pointer(3,0))]);}}dv.setBigUint64(cell,0n,true);return entries;});assert.deepEqual(lists[1],lists[0]);comparisons++;check();}
for(const idx of [L.ATR_NONE,L.ATR_BOLD,L.ATR_INVERSE]){act('hlattr2attrname',idx,0,128);result();}
for(const n of ['reset_status_hilites','status_eval_next_unhilite','status_hilite_linestr_gather_conditions','init_blstats'])act(n);
// Cancellation traverses each real menu function without inventing menu policy.
for(const n of ['cond_menu','query_conditions','status_hilite_menu_choose_field','status_hilite_menu','status_hilites_viewall']){reset();act(n);}
for(const fld of [L.BL_HP,L.BL_TITLE,L.BL_CONDITION]){
 for(const n of ['status_hilite_menu_choose_behavior','status_hilite_menu_add','status_hilite_remove','status_hilite_menu_fld']){reset();act(n,fld);}
 reset();input(0,'hitpoints');act('status_hilite_menu_choose_updownboth',fld,0,1,1);
}
reset();input(0,'green');input(1,'red');input(2,'blue');act('is_fld_arrayvalues',0,0,0,3,0);act('query_arrayvalue',0,0,0,3);
reset();input(0,'Hero');act('title_to_mon',0,0,4);act('describe_level',0,1);act('weapon_status',0);result();act('armor_status',0);result();
act('bot_via_windowport');act('bot');act('timebot');

reset();act('status_initialize',1);
act('condopt',0,-1,0);for(let i=0;i<30;i++){act('condopt',i,1,1);act('condopt',i,1,0);}
for(let i=0;i<30;i++)for(const j of [0,15,29]){for(const m of modules){const dv=new FixtureDataView(m.HEAPU8.buffer),p=Number(m._probe_pointer(0,0));dv.setInt32(p,i,true);dv.setInt32(p+4,j,true);}act('cond_cmp',0,4);act('menualpha_cmp',0,4);}
reset();act('eval_notify_windowport_field',L.BL_TIME,0,0);act('evaluate_and_notify_windowport',0,0);
for(const type of [L.ANY_LONG,L.ANY_UINT,L.ANY_ULONG,L.ANY_MASK32]){stat(0,1,type);stat(1,1,type);stat(0,2,25);stat(1,2,100);act('compare_blstats',0,1);if(type!==L.ANY_MASK32)act('percentage',0,1);}
reset();for(const t of [0n,1n,9007199254740993n])act('hilite_reset_needed',0,t);
for(const fields of [['hitpoints','<50%','red'],['condition','blind','red'],['alignment','lawful','green'],['hunger','hungry','blue'],['power','always','green']]){reset();fields.forEach((v,i)=>input(i,v));act('parse_status_hl2',0,0);act('parse_condition',0,1);}
function setNative(kind,offset,name,value){const k=Object.keys(botlSchema).indexOf(kind),f=botlSchema[kind].fields.findIndex(f=>f.name===name);assert.ok(f>=0,name);for(const m of modules)m._probe_write(k,BigInt(m._probe_pointer(0,offset)),f,BigInt.asUintN(64,BigInt(value)));comparisons++;}
reset();setNative('hilite_s',128,'behavior',L.BL_TH_ALWAYS_HILITE);setNative('hilite_s',128,'anytype',L.ANY_INT);setNative('hilite_s',128,'coloridx',L.CLR_RED);setNative('hilite_s',128,'rel',L.EQ_VALUE);
act('status_hilite_add_threshold',L.BL_HP,128);assert.equal(act('count_status_hilites'),1n);act('status_hilite2str',128);result();
for(const hp of [0,4,5,10]){for(const m of modules)new FixtureDataView(m.HEAPU8.buffer).setInt32(Number(m._probe_pointer(0,0)),hp,true);act('get_hilite',0,L.BL_HP,0,0,50,8);}
input(0,'hitpoints/always/red');act('status_hilite_linestr_add',L.BL_HP,-1,0,0);assert.equal(act('status_hilite_linestr_countfield',L.BL_HP),1n);act('status_hilite_linestr_done');act('clear_status_hilites');
// Unsigned multiplication wraps at its original C width before division.
for(const [type,bits]of [[L.ANY_UINT,32],[L.ANY_ULONG,64]])for(const value of [1n,(1n<<BigInt(bits))-1n,(1n<<BigInt(bits-1))+1n])for(const max of [3n,100n]){reset();stat(0,1,type);stat(1,1,type);stat(0,2,BigInt.asIntN(64,value));stat(1,2,max);const quotient=BigInt.asIntN(32,BigInt.asUintN(bits,100n*value)/max);assert.equal(act('percentage',0,1),quotient===0n?1n:quotient);}
// Positive selections and each original retry label use native menu/input replies.
const depIndex=Object.fromEntries(Array.from({length:reference._probe_dep_count()},(_,i)=>[text(reference,reference._probe_dep_name(i)),i]));
const menu=(...values)=>{call('menu',-1,0);values.forEach((v,i)=>call('menu',i,v));};
function typedInput(...lines){for(const m of modules){m._probe_input(-1,0n);for(const [i,line]of lines.entries()){const p=m._malloc(BigInt(line.length+1));m.HEAPU8.set(Buffer.from(line+'\0','latin1'),Number(p));m._probe_input(i,BigInt(p));m._free(BigInt(p));}}comparisons++;}
reset();menu(L.BL_TH_ALWAYS_HILITE);assert.equal(act('status_hilite_menu_add',L.BL_HP),1n);assert.equal(act('count_status_hilites'),1n);
reset();menu(L.BL_TH_ALWAYS_HILITE,L.BL_TH_ALWAYS_HILITE);call('reply',depIndex.query_color,0,-1n);call('reply',depIndex.query_color,1,0n);assert.equal(act('status_hilite_menu_add',L.BL_HP),1n);assert.equal(act('count_status_hilites'),1n);
reset();menu(L.BL_TH_ALWAYS_HILITE);call('reply',depIndex.query_attr,0,-1n);call('reply',depIndex.query_attr,1,0n);assert.equal(act('status_hilite_menu_add',L.BL_HP),1n);
reset();menu(L.BL_TH_VAL_ABSOLUTE);typedInput('bad','<5');assert.equal(act('status_hilite_menu_add',L.BL_HP),1n);assert.ok(text(reference,reference._probe_trace()).includes('getlin:'));
reset();menu(L.BL_HP+1,-1,-1);assert.equal(act('status_hilite_menu_add',L.BL_FLUSH),0n);
reset();menu(L.BL_HP+1,-1,-1);act('status_hilite_menu');
// Per-call foreign overrides remain scoped across an actual native C -> JS
// reentry and an exception; the later ordinary import uses its fresh facade.
reset();const liveServices=servicesByModule.get(modules[1]),override=Object.create(liveServices);let nested=0,outerFormats=0;override.Sprintf=(...args)=>{outerFormats++;return liveServices.Sprintf(...args);};
override.acurr=()=>{nested++;assert.equal(modules[1]._probe_action(names.indexOf('stat_hunger_indx'),0n,0n,0n,0n,0n,0n),0n);return 17;};
const savedStack=modules[1]._probe_stack();const value=callBotl(override,L,'get_strength_str');assert.equal(text(modules[1],value.address??value),'17');assert.equal(nested,1);assert.equal(outerFormats,1);assertStackRestored(modules[1],savedStack,modules[1]._probe_stack());
const problem=new Error('controlled BOTL acurr failure'),failing=Object.create(liveServices);failing.acurr=()=>{throw problem;};assert.throws(()=>callBotl(failing,L,'get_strength_str'),e=>e===problem);assertStackRestored(modules[1],savedStack,modules[1]._probe_stack());assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);
act('get_strength_str');assert.equal(result(),'10');comparisons+=4;
// Real catalogue objects exercise nonempty weapon and armor descriptions.
for(const [typ,skill,expected]of [[L.AKLYS,0,'Aklys'],[L.TWO_HANDED_SWORD,0,'2H-Sword'],[L.LANCE,L.P_LANCE,'Value']]){reset();for(const m of modules)m._probe_object(0,typ);call('equipment',0,0);call('option',depIndex.weapon_type,BigInt(skill));act('weapon_status',0);assert.equal(result(),expected);}
reset();for(const [slot,typ,expected]of [[2,L.LEATHER_GLOVES,'Gloves'],[3,L.CLOAK_OF_PROTECTION,'Cloak+'],[4,L.LEATHER_ARMOR,'Suit'],[5,L.T_SHIRT,'Shirt'],[6,L.HELMET,'Value'],[7,L.LOW_BOOTS,'Boots'],[8,L.SMALL_SHIELD,'Shield']]){for(const m of modules)m._probe_object(slot,typ);call('equipment',slot,slot);act('armor_status',0);assert.equal(result(),expected);call('equipment',slot,-1);}
for(let slot=2;slot<=8;slot++)call('equipment',slot,slot);act('armor_status',0);assert.equal(result(),'GCAUHBS+');
for(let slot=2;slot<=8;slot++)call('equipment',slot,-1);for(const [slot,typ]of [[9,L.RIN_PROTECTION],[10,L.RIN_PROTECTION],[11,L.AMULET_OF_GUARDING]]){for(const m of modules)m._probe_object(slot,typ);call('equipment',slot,slot);act('armor_status',0);assert.equal(result(),'Naked+');call('equipment',slot,-1);}
reset();
// Native pointer variants and nullable/aliased scalar outputs retain live cells.
for(const type of [L.ANY_IPTR,L.ANY_UPTR,L.ANY_LPTR,L.ANY_ULPTR]){reset();for(const m of modules){const ptr=m._probe_pointer(0,128);new FixtureDataView(m.HEAPU8.buffer).setBigUint64(Number(ptr),0xa5a5a5a500000005n,true);m._probe_any(0,BigInt(ptr));}act('anything_to_s',0,0,type);result();input(1,'27');act('s_to_anything',0,1,type);}
for(const [a,b]of [[-1,-1],[-1,0],[0,-1],[0,0]])act('split_clridx',511,a,b);
input(0,'Ranger');for(const [a,b]of [[-1,-1],[-1,0],[0,-1],[0,0]])act('title_to_mon',0,a,b);
reset();act('get_strength_str');const savedPointers=modules.map(m=>m._probe_lastptr());for(let i=0;i<3;i++){act('do_statusline1');act('get_strength_str');modules.forEach((m,j)=>assert.equal(m._probe_lastptr(),savedPointers[j]));comparisons++;}
function globalPointer(global,field,row){const gi=botlGlobals.findIndex(g=>g.name===global),kind=botlGlobals[gi].d.s,ki=Object.keys(botlSchema).indexOf(kind),fi=botlSchema[kind].fields.findIndex(f=>f.name===field);assert.ok(fi>=0);for(const m of modules)m._probe_write(ki,BigInt(m._probe_global(gi)),fi,row<0?0n:BigInt(m._probe_pointer(3,row)));comparisons++;}
reset();for(let i=0;i<30;i++)act('condopt',i,1,0);hero(9,-9007199254740993n);input(0,'paralyzed by a monster');input(1,'frozen by a monster');globalPointer('gm','multi_reason',0);globalPointer('gn','nomovemsg',1);act('bot_via_windowport');act('bot_via_windowport');input(0,'something else at the same native address');act('bot_via_windowport');globalPointer('gm','multi_reason',1);act('bot_via_windowport');globalPointer('gm','multi_reason',-1);globalPointer('gn','nomovemsg',-1);act('bot_via_windowport');
// A long, legal menu session must reuse each automatic declaration's slot.
const spans=[];for(const count of [1,24]){reset();const choices=[];for(let i=0;i<count;i++)choices.push(L.BL_HP+1,-1);choices.push(-1);menu(...choices);call('clear');act('status_hilite_menu');spans.push(modules.map(m=>m._probe_stack_span()));}for(let i=0;i<2;i++)assert.equal(spans[1][i],spans[0][i],'bounded automatic frame in '+i);comparisons+=2;if(own)writeFileSync(new URL('../.cache/botl-author/stack-spans.json',import.meta.url),JSON.stringify(spans,(_,v)=>typeof v==='bigint'?String(v):v));
// The original explicit panic guard is caught only by this native fixture.
reset();const gbIndex=botlGlobals.findIndex(g=>g.name==='gb'),gbKind=botlGlobals[gbIndex].d.s,gbType=Object.keys(botlSchema).indexOf(gbKind),blinit=botlSchema[gbKind].fields.findIndex(f=>f.name==='blinit');for(const m of modules)m._probe_write(gbType,BigInt(m._probe_global(gbIndex)),blinit,0n);const panicOuter={rectState:{panic:1},trackState:{panic:2}};expectedScope=panicOuter;withCEnvironment(panicOuter,()=>assert.equal(act('bot_via_windowport'),-(1n<<63n)));expectedScope=undefined;for(const m of modules)m._probe_write(gbType,BigInt(m._probe_global(gbIndex)),blinit,1n);check();
// Fresh properties are observed through repeated real status updates.
for(const property of ['BLINDED','DEAF','CONFUSION','STUNNED','HALLUC','HALLUC_RES','LEVITATION','FLYING','FAST','STONED','SLIMED','SICK','STRANGLED'])if(Object.hasOwn(L,property)){
 reset();call('property',L[property],0,7n);act('bot_via_windowport');call('property',L[property],2,1n);act('bot_via_windowport');call('property',L[property],0,0n);act('bot_via_windowport');
}
reset();const before=modules.map(memoryCheckpoint);const dep=Object.fromEntries(Array.from({length:reference._probe_dep_count()},(_,i)=>[text(reference,reference._probe_dep_name(i)),i]));call('callback',dep.acurr,dep.acurr);const outer={rectState:{sentinel:1},trackState:{sentinel:2}};
expectedScope=outer;withCEnvironment(outer,()=>{act('do_statusline1');assert.equal(C,outer);assert.equal(R,outer.rectState);assert.equal(T,outer.trackState);});expectedScope=undefined;modules.forEach((m,i)=>assertMemoryGrowth(m,before[i]));comparisons++;
const primary=snapshot(modules[1]),saved=modules,oldStacks=stacks;modules=[await referenceFactory(),await hybridFactory({nethackPorted:ported})];stacks=modules.map(m=>m._probe_stack());reset();hero(0,17);act('rank');result();act('condopt',1,1,1);act('bot_via_windowport');assert.deepEqual(snapshot(saved[1]),primary,'second actual Module executes JS and preserves primary state');comparisons++;modules=saved;stacks=oldStacks;
act('status_finish');
assert.deepEqual(names.filter(n=>!exercised.has(n)),[],'every configured original BOTL function exercised');
console.log(`BOTL ${comparisons} comparisons PASS; all ${exercised.size}/76 functions exercised.`);
