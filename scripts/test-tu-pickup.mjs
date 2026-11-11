// Actual configured original C versus imported source JS in a controlled world.
import assert from 'node:assert/strict';
import {readFileSync,writeFileSync} from 'node:fs';
if(process.env.TELEPORT_NATIVE_TESTS!=='0')throw Error('PICKUP has no native reference fixture; set TELEPORT_NATIVE_TESTS=0 only for the explicit Emscripten diagnostic.');
const probeDir=process.env.PICKUP_PROBE_DIR;
const probeURL=name=>probeDir?new URL(name,new URL((probeDir.endsWith('/')?probeDir:probeDir+'/'),new URL('../',import.meta.url))):new URL('../.cache/pickup-first-pass/'+name.replace(/^pickup-fixture-/,'fixture-'),import.meta.url);
const {default:refFactory}=await import(probeURL('pickup-reference.mjs'));
const {default:hybridFactory}=await import(probeURL('pickup-hybrid.mjs'));
const {callPickup}=await import(process.env.PICKUP_RUNTIME??'../js/ported/pickup-runtime.js');
const read=p=>JSON.parse(readFileSync(new URL(p,import.meta.url)));
const schema=read('../nethack-c/wasm/tu-fragments/pickup-schema.json'),functions=read('../nethack-c/wasm/tu-fragments/pickup-source-metadata.json').functions,names=functions.map(f=>f.name),kinds=Object.keys(schema.schema),covered=new Set();
const regionNames=JSON.parse(readFileSync(probeURL('pickup-fixture-regions.json'))),constants=JSON.parse(readFileSync(probeURL('pickup-fixture-constants.json')));
const output=[[],[]],ref=await refFactory({print:s=>output[0].push(['out',s]),printErr:s=>output[0].push(['err',s])}),hybrid=await hybridFactory({nethackPorted:{pickup:callPickup},print:s=>output[1].push(['out',s]),printErr:s=>output[1].push(['err',s])}),mods=[ref,hybrid];
const L=Object.fromEntries(schema.layoutKeys.map((k,i)=>[k,Number(ref._teleport_pickup_layout(i))]));for(let i=0;i<schema.layoutKeys.length;i++)assert.equal(hybrid._teleport_pickup_layout(i),ref._teleport_pickup_layout(i));
const K=Object.fromEntries(constants.map((n,i)=>[n,Number(ref._probe_constant(i))]));
const global=(m,n)=>Number(m._teleport_pickup_global(schema.globals.findIndex(g=>g.name===n))),ptr=(m,i)=>Number(m._probe_pointer(i));
const fi=(k,f)=>{const i=schema.schema[k]?.fields.findIndex(x=>x.name===f);assert.ok(i>=0,k+'.'+f);return i;};
const addr=(m,p,k,f)=>Number(m._teleport_pickup_address(kinds.indexOf(k),BigInt(p),fi(k,f)));
const get=(m,p,k,f)=>m._teleport_pickup_read(kinds.indexOf(k),BigInt(p),fi(k,f));
const set=(m,p,k,f,v)=>m._teleport_pickup_write(kinds.indexOf(k),BigInt(p),fi(k,f),BigInt.asUintN(64,BigInt(v)));
const root=(m,n,k,f)=>addr(m,global(m,n),k,f),setter=fn=>mods.forEach(fn),option=(i,v)=>setter(m=>m._probe_option(i,v)),seed=n=>setter(m=>m._probe_seed(n));
const obj=(m,i=0)=>ptr(m,1)+i*112,scratch=(m,n=0)=>ptr(m,0)+n,text=(m,s,p=scratch(m,32768))=>(m.stringToUTF8(s,p,256),p),input=s=>setter(m=>m._probe_input(BigInt(text(m,s)))),answer=c=>setter(m=>m._probe_answer(typeof c==='string'?c.charCodeAt(0):c)),identity=(m,n)=>Number(m._probe_identity([...schema.ownedFunctionPointers,...schema.nativeFunctionPointers].indexOf(n)));
const cell=(m,p,v)=>new DataView(m.HEAPU8.buffer).setBigUint64(p,BigInt.asUintN(64,BigInt(v)),true);
const typeKey=t=>kinds.find(k=>schema.schema[k].ctype.replace(/\b(?:const|volatile)\b/g,'').trim()===t)??(schema.schema[t.replace(/^(?:struct|union) /,'')]?t.replace(/^(?:struct|union) /,''):null);
const sizeOf=t=>{const a=t.match(/^(.*?)\[(\d+)\](.*)$/);if(a)return+a[2]*sizeOf(a[1]+a[3]);if(t.includes('*'))return 8;if(/^(?:unsigned |signed )?char$/.test(t))return 1;if(/^(?:unsigned )?short$/.test(t))return 2;if(/^(?:unsigned )?(?:int|enum \w+)$/.test(t))return 4;if(/^(?:unsigned )?long(?: long)?$/.test(t))return 8;return L['size:'+t]??L['size:'+schema.schema[typeKey(t)]?.ctype];};
const literalRegions=m=>schema.literals.map((s,i)=>({name:'sourceLiteral'+i,p:m===ref?Number(m._probe_literal(i)):m.teleportPickupLiteralCache?.strings.get(s)??-1,size:Buffer.byteLength(s)+1})).filter(r=>r.p>=0);
const knownRegions=m=>[...schema.globals.map((g,i)=>({name:g.name,p:global(m,g.name),size:Number(m._probe_global_size(i))})),...regionNames.map((name,i)=>({name,p:ptr(m,i),size:Number(m._probe_region_size(i))})),...Array.from({length:m._probe_borrow_count()},(_,i)=>({name:'borrowedObject'+i,p:Number(m._probe_borrow_pointer(i)),size:1,borrowed:true})),...Array.from({length:m._probe_count()},(_,i)=>({name:'allocation'+i,p:Number(m._probe_alloc_pointer(i)),size:Number(m._probe_alloc_size(i)),live:Boolean(m._probe_alloc_live(i)),kind:m._probe_alloc_kind(i)}))];
// Unknown pointers stay raw64. Only compiler-typed fields into exact known regions
// are canonicalized. Scalar bytes, padding and unselected union bytes stay raw.
const pointerID=(m,value)=>{const v=BigInt(value);if(!v)return'0';const r=[...knownRegions(m),...literalRegions(m)].find(r=>v>=BigInt(r.p)&&v<BigInt(r.p+r.size));return r?r.name+'+'+(v-BigInt(r.p)):'UNKNOWN:'+v;};
let scratchTypes=[];
function rawRegions(m){
 const rs=knownRegions(m),pointerRegions=[...rs,...literalRegions(m)],idFor=v=>{if(!v)return'0';const r=pointerRegions.find(r=>v>=BigInt(r.p)&&v<BigInt(r.p+r.size));return r?r.name+'+'+(v-BigInt(r.p)):'UNKNOWN:'+v;},regions=rs.filter(r=>!r.borrowed&&r.live!==false&&!['windowprocs','cg','nul_glyphinfo'].includes(r.name)).map(r=>({...r,bytes:m.HEAPU8.slice(r.p,r.p+r.size),pointers:[]})),visited=new Set();
 const pointer=(at,t)=>{const v=new DataView(m.HEAPU8.buffer).getBigUint64(at,true),id=idFor(v),r=regions.find(r=>at>=r.p&&at+8<=r.p+r.size);if(r&&!id.startsWith('UNKNOWN:')){r.pointers.push([at-r.p,id]);r.bytes.fill(0,at-r.p,at-r.p+8);}return v;};
 const visit=(at,t)=>{if(t.startsWith('union '))return;const a=t.match(/^(.*?)\[(\d+)\](.*)$/);if(a){const e=a[1]+a[3],step=sizeOf(e);if(step)for(let i=0;i<+a[2];i++)visit(at+i*step,e);return;}if(t.includes('*')){pointer(at,t);return;}const key=typeKey(t);if(!key||visited.has(at+':'+key))return;visited.add(at+':'+key);for(const f of schema.schema[key].fields)if(!f.bit&&(f.canonical.includes('*')||f.canonical.includes('[')||typeKey(f.canonical)))visit(addr(m,at,key,f.name),f.canonical);
  if(key==='obj'){const where=Number(get(m,at,key,'where'));if([K.OBJ_FLOOR,K.OBJ_CONTAINED,K.OBJ_MINVENT].includes(where))pointer(addr(m,at,key,'v'),'struct obj *');}
 };
 for(const g of schema.globals)if(!['windowprocs','cg','nul_glyphinfo','ynaqchars','ynNaqchars','ynqchars','genders'].includes(g.name))visit(global(m,g.name),g.canonical);
 for(let i=0;i<3;i++)visit(global(m,'genders')+i*sizeOf('struct Gender'),'struct Gender');
 for(const [region,t,n]of [[1,'struct obj',256],[2,'struct monst',32],[3,'struct trap',8],[4,'struct autopickup_exception',8],[5,'struct mextra',1],[6,'struct eshk',1]])if(sizeOf(t))for(let i=0;i<n;i++)visit(ptr(m,region)+i*sizeOf(t),t);
 for(let i=0;i<32;i++)pointer(ptr(m,2)+i*sizeOf('struct monst')+Number(m._probe_extra_offset(0)),'struct mextra *');pointer(ptr(m,5)+Number(m._probe_extra_offset(1)),'struct eshk *');
 for(const [offset,t]of scratchTypes)visit(scratch(m,offset),t);
 for(const r of rs.filter(r=>r.live)){const t=r.kind===1?'struct sortloot_item':r.kind===2||r.kind===3?'struct mi':null;if(t)for(let at=r.p;at<r.p+r.size;at+=sizeOf(t)){visit(at,t);if(r.kind===2)pointer(at,'struct obj *');}}
 for(let i=0;i<m._probe_event_count();i++){const at=ptr(m,13)+i*56;visit(at,'struct glyphinfo');if(m._probe_event_kind(i))pointer(at+48,'struct obj *');}
 for(let i=0;i<m._probe_borrow_count();i++)if(m._probe_borrow_kind(i)===2)visit(ptr(m,14)+i*112,'struct obj');
 return regions.map(r=>({name:r.name,bytes:Buffer.from(r.bytes).toString('hex'),pointers:r.pointers.sort((a,b)=>a[0]-b[0])}));
}
const snapshot=m=>({prefixes:schema.statics.slice(0,4).map((s,i)=>{const p=Number(m._probe_prefix(i));return Buffer.from(m.HEAPU8.slice(p,p+Number(s.type.match(/\[(\d+)\]/)[1]))).toString('hex');}),regions:rawRegions(m),trace:m.UTF8ToString(Number(m._probe_trace())),draws:m._probe_draws(),error:m._probe_error(),errno:m._probe_errno(),allocations:Array.from({length:m._probe_count()},(_,i)=>[Number(m._probe_alloc_size(i)),m._probe_alloc_live(i),m._probe_alloc_kind(i)]),queue:Array.from({length:m._probe_queue_count()},(_,i)=>m._probe_queue_identity(i))});
const observedRng=new Set();let displayDraws=0;
let checks=0;function reset(){setter(m=>m._probe_reset());scratchTypes=[];output.forEach(a=>a.length=0);}
function compare(label){const a=snapshot(ref),b=snapshot(hybrid);try{assert.deepEqual(b,a,label);assert.deepEqual(output[1],output[0],label+' output');checks++;}catch(e){writeFileSync(new URL('../.cache/pickup-first-pass/mismatch.json',import.meta.url),JSON.stringify({label,ref:a,hybrid:b},null,2));e.message=label+' comparison failed; full snapshots in .cache/pickup-first-pass/mismatch.json';throw e;}}
function action(name,args=[]){covered.add(name);const rt=functions[names.indexOf(name)].type.qualType.split('(')[0],results=mods.map((m,i)=>{const a=typeof args==='function'?args(m,i):args,sp=m.stackSave();try{const result=m._probe_action(names.indexOf(name),...Array.from({length:10},(_,j)=>BigInt(a[j]??0)));return rt.includes('*')?(rt.includes('char')?(result?m.UTF8ToString(Number(result)):null):pointerID(m,result)):result;}catch(e){console.error('PICKUP unexpected boundary exception',name,i,a,e);throw e;}finally{assert.equal(m.stackSave(),sp,name+' stack cleanup');}});assert.equal(results[1],results[0],name+' result');compare(name);const trace=ref.UTF8ToString(Number(ref._probe_trace()));for(const x of trace.matchAll(/\[pickup\.c:(\d+):([^\]]+)\]/g))observedRng.add(x[2]+':'+x[1]);displayDraws+=Array.from(trace.matchAll(/display_rng\[/g)).length;return results;}
function objectMenus(){option(50,1);setter(m=>{for(let i=0;i<32;i++)m._probe_choice(i,-1,1,1);});}
function setType(m,p,typ){set(m,p,'obj','otyp',typ);set(m,p,'obj','oclass',get(m,global(m,'objects')+typ*sizeOf('struct objclass'),'objclass','oc_class'));}
function current(){setter(m=>{m._probe_floor(BigInt(obj(m,1)));set(m,global(m,'gc'),'instance_globals_c','current_container',obj(m,1));});}
function contained(){current();setter(m=>{set(m,obj(m,1),'obj','cobj',obj(m));set(m,obj(m),'obj','where',K.OBJ_CONTAINED);cell(m,addr(m,obj(m),'obj','v'),obj(m,1));set(m,global(m,'gi'),'instance_globals_i','invent',0);});}
reset();compare('initial native controlled world');
for(const name of ['allow_all','all_but_uchain','allow_category','is_worn_by_type','n_or_more','u_safe_from_fatal_corpse','fatal_corpse_mistake','rider_corpse_revival','check_autopickup_exceptions','autopick_testobj','reset_justpicked','count_justpicked','find_justpicked','mbag_explodes','stash_ok','tip_ok']){reset();current();action(name,m=>[obj(m),0]);}
for(const name of ['force_decor','deferred_decor','describe_decor','check_here','encumber_msg','u_handsy','is_boh_item_gone','choose_tip_container_menu','doloot','doloot_core','reverse_loot','dotip']){reset();if(name==='choose_tip_container_menu')objectMenus();action(name,[0]);}
reset();action('add_valid_menu_class',[K.WEAPON_CLASS]);action('menu_class_present',[K.WEAPON_CLASS]);action('allow_category',m=>[obj(m)]);
for(const name of ['simple_look','collect_obj_classes','query_classes']){reset();input('a');action(name,m=>name==='simple_look'?[obj(m),0]:name==='collect_obj_classes'?[scratch(m),obj(m),0,identity(m,'allow_all'),scratch(m,128)]:[scratch(m),scratch(m,128),scratch(m,129),text(m,'pick up'),obj(m),0,scratch(m,132)]);}
for(const name of ['pickup','container_at','able_to_loot','mon_beside']){reset();action(name,name==='pickup'?[0]:[40,10,1]);}
reset();scratchTypes=[[0,'struct mi *']];action('autopick',m=>[obj(m),0,scratch(m)]);scratchTypes=[[0,'struct mi *']];compare('autopick output pointer');
for(const name of ['query_objlist','query_category','count_categories']){reset();if(name==='query_objlist')objectMenus();scratchTypes=[[0,'struct mi *']];action(name,m=>name==='query_objlist'?[text(m,'choose'),addr(m,global(m,'gi'),'instance_globals_i','invent'),0,scratch(m),K.PICK_ANY,identity(m,'allow_all')]:name==='query_category'?[text(m,'choose'),obj(m),K.ALL_TYPES,scratch(m),K.PICK_ANY]:[obj(m),K.ALL_TYPES]);}
reset();action('delta_cwt',m=>[obj(m,1),obj(m)]);action('carry_count',m=>[obj(m),0,2,0,scratch(m),scratch(m,4)]);setter(m=>cell(m,scratch(m,8),2));action('lift_object',m=>[obj(m),0,scratch(m,8),0]);
for(const name of ['pickup_object','pick_obj','pickup_prinv']){reset();setter(m=>m._probe_floor(BigInt(obj(m))));action(name,m=>name==='pickup_prinv'?[obj(m),2,text(m,'test')]:[obj(m),2,0]);}
reset();current();setter(m=>cell(m,scratch(m),obj(m,1)));scratchTypes=[[0,'struct obj *']];answer('q');action('do_loot_cont',m=>[scratch(m),0,1]);
reset();action('loot_mon',m=>[ptr(m,2),scratch(m),scratch(m,8)]);
for(const name of ['ck_bag','in_container','container_gone','traditional_loot','menu_loot','in_or_out_menu']){reset();current();if(name==='menu_loot')objectMenus();answer('q');action(name,m=>name==='container_gone'?[identity(m,'in_container')]:name==='in_or_out_menu'?[text(m,'container'),obj(m,1),1,1,1,1]:name==='traditional_loot'?[1]:name==='menu_loot'?[0,1]:[obj(m)]);}
for(const name of ['out_container','removed_from_icebox','mbag_item_gone','boh_loss','do_boh_explosion']){reset();contained();if(name==='do_boh_explosion'||name==='boh_loss')setter(m=>{setType(m,obj(m,1),K.BAG_OF_HOLDING);set(m,obj(m,1),'obj','cursed',1);});action(name,m=>name==='mbag_item_gone'?[0,obj(m),1]:name==='boh_loss'?[obj(m,1),1]:name==='do_boh_explosion'?[obj(m,1),0]:[obj(m)]);}
reset();contained();setter(m=>{setType(m,obj(m,1),K.LARGE_BOX);set(m,obj(m,1),'obj','spe',1);setType(m,obj(m),K.CORPSE);set(m,obj(m),'obj','oclass',K.FOOD_CLASS);set(m,obj(m),'obj','corpsenm',K.PM_HOUSECAT);});action('observe_quantum_cat',m=>[obj(m,1),1,1]);
reset();action('explain_container_prompt',[1]);reset();current();setter(m=>cell(m,scratch(m),obj(m,1)));scratchTypes=[[0,'struct obj *']];answer('q');action('use_container',m=>[scratch(m),0,0]);
for(const name of ['tipcontainer','tipcontainer_gettarget','tipcontainer_checks']){reset();current();setter(m=>set(m,global(m,'gc'),'instance_globals_c','current_container',0));if(name==='tipcontainer_gettarget'||name==='tipcontainer')objectMenus();action(name,m=>[obj(m,1),name==='tipcontainer_gettarget'?scratch(m):0,0]);}
assert.equal(covered.size,66,'all configured functions');console.log('PASS PICKUP draft',checks,'top-level comparisons;',covered.size,'configured functions; extended proofs pending.');
// Native C filter callback reentry uses new call services while an outer source
// body still holds its environment. The callback also proves exception cleanup.
reset();action('add_valid_menu_class',[K.WEAPON_CLASS]);
const serviceEvents=[];let armed=true,nestedSeen=0,phase='outer',savedServices;
const overlay=(services,label)=>Object.assign(Object.create(services),Object.fromEntries(['read','write','address','heap'].map(key=>[key,(...a)=>{serviceEvents.push([label,phase,key]);return services[key](...a);}])));
hybrid.nethackPorted.pickup=(services,name,...args)=>{
 savedServices=services;
 if(name==='collect_obj_classes'){
  const outer=overlay(services,'outer');
  const indirect=outer.indirect5;outer.indirect5=(...a)=>{const old=hybrid.HEAPU8.buffer;hybrid._probe_growth();assert.notEqual(hybrid.HEAPU8.buffer,old,'growth at real native filter boundary');return indirect(...a);};
  return callPickup(outer,name,...args);
 }
 if(name==='allow_category'&&armed){
  armed=false;nestedSeen++;phase='nested';const nested=overlay(services,'nested'),sp=hybrid.stackSave(),result=callPickup(nested,name,...args);assert.equal(result,1,'positive actual native filter');assert.equal(hybrid.stackSave(),sp);
  const sentinel=new Error('controlled nested service exception');assert.throws(()=>callPickup(Object.assign(Object.create(nested),{read(){throw sentinel;}}),name,...args),e=>e===sentinel);assert.equal(hybrid.stackSave(),sp,'nested exception stack restore');
  phase='resumed';return result;
 }
 return callPickup(services,name,...args);
};
action('collect_obj_classes',m=>[scratch(m),obj(m),0,identity(m,'allow_category'),scratch(m,128)]);assert.equal(nestedSeen,1);assert.ok(serviceEvents.some(([l,p,k])=>l==='nested'&&p==='nested'&&k==='read'));assert.ok(serviceEvents.some(([l,p,k])=>l==='nested'&&p==='nested'&&k==='address'),'nested native address services');for(const key of ['read','heap'])assert.ok(serviceEvents.some(([l,p,k])=>l==='outer'&&p==='resumed'&&k===key),'outer '+key+' restored after native callback/exception');
hybrid.nethackPorted.pickup=callPickup;action('allow_category',m=>[obj(m)]);
let laterReads=0;hybrid.nethackPorted.pickup=(services,name,...args)=>callPickup(Object.assign(Object.create(services),{read(...a){laterReads++;return services.read(...a);}}),name,...args);action('allow_category',m=>[obj(m)]);assert.ok(laterReads>0,'later new services');hybrid.nethackPorted.pickup=callPickup;
const freshRef=await refFactory(),freshHybrid=await hybridFactory({nethackPorted:{pickup:callPickup}});for(const m of[freshRef,freshHybrid]){m._probe_reset();const sp=m.stackSave();assert.equal(m._probe_action(names.indexOf('menu_class_present'),BigInt(K.WEAPON_CLASS),0n,0n,0n,0n,0n,0n,0n,0n,0n),0n);assert.equal(m.stackSave(),sp);}assert.deepEqual(snapshot(freshHybrid),snapshot(freshRef),'fresh Module private state');
console.log('PASS PICKUP adapter native positive callback/new services/outer restoration/exception/later plain/new services/fresh Module/growth/stack cleanup.');
// Persistent filter state, duplicate insertion, combinations and actual native
// callbacks see positive and negative object predicates.
for(const code of [K.WEAPON_CLASS,66,85,67,88,117,80]){
 reset();action('add_valid_menu_class',[code]);action('add_valid_menu_class',[code]);action('menu_class_present',[code]);
 for(const variant of [0,1]){setter(m=>{set(m,obj(m),'obj','blessed',variant);set(m,obj(m),'obj','bknown',variant);set(m,obj(m),'obj','unpaid',variant);set(m,obj(m),'obj','pickup_prev',variant);set(m,obj(m),'obj','owornmask',variant?K.W_WEP:0);});action('allow_category',m=>[obj(m)]);action('is_worn_by_type',m=>[obj(m)]);}
 action('add_valid_menu_class',[0]);action('menu_class_present',[code]);
}
// Source retry joins keep addressable out-cells and state alive across native UI.
reset();setter(m=>{const p=Number(m._probe_newobj(K.GOLD_PIECE));m._probe_inventory(BigInt(p));});for(const s of ['i',':','a'])input(s);action('query_classes',m=>[scratch(m),scratch(m,128),scratch(m,129),text(m,'pick up'),obj(m,2),0,scratch(m,132)]);
for(const s of ['m','u','BU','/a','\x1b']){reset();input(s);action('query_classes',m=>[scratch(m),scratch(m,128),scratch(m,129),text(m,'take out'),obj(m),0,scratch(m,132)]);}
// Actual nonempty three-element Loot24/menu24 arrays, real owned callback IDs,
// positive/cancel menu returns and the direct single-item allocation path.
for(const flags of [0,K.INVORDER_SORT,K.BY_NEXTHERE,K.AUTOSELECT_SINGLE]){
 reset();objectMenus();setter(m=>{for(const type of [K.GOLD_PIECE,K.CORPSE]){const p=Number(m._probe_newobj(type));if(flags&K.BY_NEXTHERE)m._probe_floor(BigInt(p));else m._probe_inventory(BigInt(p));}if(flags&K.BY_NEXTHERE)m._probe_floor(BigInt(obj(m)));m._probe_choice(0,1,2,1);});scratchTypes=[[0,'struct mi *']];action('query_objlist',m=>[text(m,'pick several'),flags&K.BY_NEXTHERE?addr(m,addr(m,global(m,'svl'),'instance_globals_saved_l','level'),'dlevel_t','objects')+(40*21+10)*8:addr(m,global(m,'gi'),'instance_globals_i','invent'),flags,scratch(m),K.PICK_ANY,identity(m,'allow_all')]);
}
for(const qflags of [K.ALL_TYPES,K.BUC_BLESSED|K.BUC_CURSED|K.BUC_UNCURSED|K.BUC_UNKNOWN,K.UNPAID_TYPES|K.BILLED_TYPES,K.JUSTPICKED]){reset();setter(m=>{set(m,obj(m),'obj','pickup_prev',1);set(m,obj(m),'obj','unpaid',1);m._probe_choice(0,0,3,0);});scratchTypes=[[0,'struct mi *']];action('query_category',m=>[text(m,'categories'),obj(m),qflags,scratch(m),K.PICK_ANY]);}
// Floor list traversal uses nexthere, while the object list owns nobj links.
reset();setter(m=>{m._probe_floor(BigInt(obj(m)));const p=Number(m._probe_newobj(K.GOLD_PIECE));m._probe_floor(BigInt(p));set(m,p,'obj','pickup_prev',1);});action('check_here',[1]);action('collect_obj_classes',m=>[scratch(m),obj(m,2),1,identity(m,'all_but_uchain'),scratch(m,128)]);scratchTypes=[[0,'struct mi *']];action('autopick',m=>[obj(m,2),K.BY_NEXTHERE,scratch(m)]);
// Finite recursive bags, all original chance thresholds including depth clamp.
for(const depth of [0,1,3,7,9]){reset();setter(m=>{setType(m,obj(m),K.BAG_OF_HOLDING);set(m,obj(m),'obj','spe',1);});action('mbag_explodes',m=>[obj(m),depth]);}
reset();contained();setter(m=>{setType(m,obj(m),K.SACK);const p=Number(m._probe_newobj(K.WAN_CANCELLATION));set(m,p,'obj','spe',1);set(m,p,'obj','where',K.OBJ_CONTAINED);cell(m,addr(m,p,'obj','v'),obj(m));set(m,obj(m),'obj','cobj',p);});action('mbag_explodes',m=>[obj(m,1),0]);
for(const randomSeed of [1,2,4,9,17]){reset();contained();setter(m=>{setType(m,obj(m,1),K.BAG_OF_HOLDING);set(m,obj(m,1),'obj','cursed',1);});seed(randomSeed);action('boh_loss',m=>[obj(m,1),0]);}
// Native container extraction/insertion/merge aliases and icebox timers preserve
// object ownership and the source's saved-next traversal before destruction.
for(const merge of [0,1]){reset();contained();if(merge)setter(m=>{const p=m._probe_newobj(K.DAGGER);m._probe_inventory(p);});option(29,merge);action('out_container',m=>[obj(m)]);}
for(const age of [12n,0x20000000000001n]){reset();contained();setter(m=>{setType(m,obj(m,1),K.ICE_BOX);setType(m,obj(m),K.CORPSE);set(m,obj(m),'obj','oclass',K.FOOD_CLASS);set(m,obj(m),'obj','corpsenm',K.PM_HOUSECAT);set(m,obj(m),'obj','age',age);set(m,obj(m),'obj','oeroded2',1);set(m,global(m,'svm'),'instance_globals_saved_m','moves',age+1000n);});action('removed_from_icebox',m=>[obj(m)]);}
// A real current_container precedes every carried() read in in_container.
reset();current();setter(m=>setType(m,obj(m),K.WAN_CANCELLATION));setter(m=>{set(m,obj(m),'obj','spe',1);setType(m,obj(m,1),K.BAG_OF_HOLDING);});action('in_container',m=>[obj(m)]);
// Wide source long and raw pointer/scalar observation witnesses. Unknown
// pointer words are never converted to Number or searched as arbitrary bytes.
reset();setter(m=>{set(m,obj(m),'obj','quan',0x20000000000001n);set(m,global(m,'gv'),'instance_globals_v','val_for_n_or_more',0x20000000000000n);});action('n_or_more',m=>[obj(m)]);
reset();setter(m=>set(m,obj(m),'obj','cobj',0x20000000000001n));assert.deepEqual(snapshot(hybrid),snapshot(ref),'raw unknown typed pointer64 equal');set(hybrid,obj(hybrid),'obj','cobj',0x20000000000002n);assert.throws(()=>assert.deepEqual(snapshot(hybrid),snapshot(ref)),assert.AssertionError);
reset();setter(m=>set(m,obj(m),'obj','quan',BigInt(obj(m))));assert.notEqual(obj(ref),obj(hybrid));assert.throws(()=>assert.deepEqual(snapshot(hybrid),snapshot(ref)),assert.AssertionError,'scalar equal to a native address remains raw');
reset();console.log('PASS PICKUP extended',checks,'top-level comparisons; source retry/filter/menu arrays/recursive bags/container ownership/icebox/wide64/raw witnesses. Controlled native world and UI only.');
// The source's pickup goto joins: automatic menu tail, traditional count,
// menu-on-demand transfer, cancellation, and the ordinary menu/count paths.
for(const [what,style,response]of [[1,K.MENU_FULL,'a'],[-2,K.MENU_TRADITIONAL,'a'],[0,K.MENU_TRADITIONAL,'m'],[0,K.MENU_TRADITIONAL,'\x1b'],[0,K.MENU_TRADITIONAL,'A'],[0,K.MENU_FULL,'a'],[-2,K.MENU_FULL,'a']]){
 reset();objectMenus();setter(m=>{m._probe_floor(BigInt(obj(m)));set(m,global(m,'flags'),'flag','pickup',1);set(m,global(m,'flags'),'flag','menu_style',style);if(what>=0){const p=m._probe_newobj(K.GOLD_PIECE);m._probe_floor(p);}m._probe_choice(0,0,2,1);});input(response);answer('q');action('pickup',[what]);
}
// Source borrowed fake-hero aggregate in its valid look-only caller context: native
// callback copies the initialized112-byte object while its source lifetime holds.
for(const attack of [0,1]){
 reset();objectMenus();option(50,2);option(20,attack);setter(m=>{set(m,global(m,'u'),'you','uswallow',1);set(m,global(m,'u'),'you','ustuck',ptr(m,2));const extra=Number(m._probe_newobj(K.GOLD_PIECE));set(m,obj(m),'obj','nobj',extra);for(const p of [obj(m),extra]){set(m,p,'obj','where',K.OBJ_MINVENT);cell(m,addr(m,p,'obj','v'),ptr(m,2));}set(m,global(m,'gi'),'instance_globals_i','invent',0);set(m,ptr(m,2),'monst','minvent',obj(m));m._probe_choice(0,-1,3,1);});scratchTypes=[[0,'struct mi *']];action('query_objlist',m=>[text(m,'swallowed inventory'),addr(m,ptr(m,2),'monst','minvent'),K.INCLUDE_HERO|K.INVORDER_SORT,scratch(m),K.PICK_NONE,identity(m,'allow_all')]);
}
// Hallucinated object/monster glyph paths consume actual display RNG calls.
reset();objectMenus();option(20,1);option(50,2);setter(m=>{set(m,addr(m,global(m,'u'),'you','uprops')+L.HALLUC*sizeOf('struct prop'),'prop','intrinsic',100);set(m,global(m,'u'),'you','uswallow',1);set(m,global(m,'u'),'you','ustuck',ptr(m,2));set(m,ptr(m,2),'monst','minvent',obj(m));set(m,obj(m),'obj','where',K.OBJ_MINVENT);cell(m,addr(m,obj(m),'obj','v'),ptr(m,2));set(m,global(m,'gi'),'instance_globals_i','invent',0);});scratchTypes=[[0,'struct mi *']];action('query_objlist',m=>[text(m,'hallucinated inventory'),addr(m,ptr(m,2),'monst','minvent'),K.INCLUDE_HERO,scratch(m),K.PICK_NONE,identity(m,'allow_all')]);
// Exact native callback identities persist in the real fixture command queue.
reset();current();option(35,1);setter(m=>{set(m,obj(m,1),'obj','olocked',1);set(m,global(m,'flags'),'flag','autounlock',K.AUTOUNLOCK_FORCE);cell(m,scratch(m),obj(m,1));});scratchTypes=[[0,'struct obj *']];action('do_loot_cont',m=>[scratch(m),1,1]);assert.equal(ref._probe_queue_count(),1);assert.equal(ref._probe_queue_identity(0),[...schema.ownedFunctionPointers,...schema.nativeFunctionPointers].indexOf('doforce'));const qr=mods.map(m=>m._probe_queue_run(0));assert.equal(qr[1],qr[0]);compare('queued real native doforce identity/lifetime');
// Positive true-native saddle removal ownership, native RNG and caller outrefs.
reset();option(23,1);setter(m=>{setType(m,obj(m,1),K.SADDLE);set(m,obj(m,1),'obj','where',K.OBJ_MINVENT);cell(m,addr(m,obj(m,1),'obj','v'),ptr(m,2));set(m,ptr(m,2),'monst','minvent',obj(m,1));});answer('y');action('loot_mon',m=>[ptr(m,2),scratch(m),scratch(m,8)]);
// Positive native askchain callbacks both ways; source saves next before unlink.
for(const putIn of [0,1]){reset();if(putIn)current();else contained();input('a');action('traditional_loot',[putIn]);}
// User help/look retry then cleanup join, plus native getobj positive/null stash.
for(const command of ['q','n','s'])for(const cancel of [0,1]){reset();current();option(31,cancel);setter(m=>cell(m,scratch(m),obj(m,1)));scratchTypes=[[0,'struct obj *']];answer('?');answer(':');answer(command);action('use_container',m=>[scratch(m),0,1]);}
// Actual bag bite and quantum alive/dead native positive/null branches.
reset();current();setter(m=>{setType(m,obj(m,1),K.BAG_OF_TRICKS);cell(m,scratch(m),obj(m,1));});scratchTypes=[[0,'struct obj *']];action('do_loot_cont',m=>[scratch(m),1,1]);
for(const randomSeed of [1,2])for(const makeFailure of [0,1]){reset();contained();seed(randomSeed);option(21,makeFailure);setter(m=>{setType(m,obj(m,1),K.LARGE_BOX);set(m,obj(m,1),'obj','spe',1);setType(m,obj(m),K.CORPSE);set(m,obj(m),'obj','oclass',K.FOOD_CLASS);set(m,obj(m),'obj','corpsenm',K.PM_HOUSECAT);});action('observe_quantum_cat',m=>[obj(m,1),1,1]);}
console.log('PASS PICKUP branch suite',checks,'top-level comparisons; goto transfers/native borrowed aggregate/menu padding/queued identities/UI callbacks/saddle/quantum/display RNG.');
// Remaining source RNG origins: reverse looting with real gold/throne state,
// confused-loot fallthrough, and source-to-target magic bag destruction.
for(const randomSeed of [1,2,3,4,5])for(const throne of [0,1]){reset();seed(randomSeed);setter(m=>{const p=Number(m._probe_newobj(K.GOLD_PIECE));set(m,p,'obj','quan',123);m._probe_inventory(BigInt(p));set(m,Number(m._probe_grid())+(40*21+10)*sizeOf('struct rm'),'rm','typ',throne?K.THRONE:K.ROOM);});action('reverse_loot');}
for(const randomSeed of [1,2,3,4,5,6]){reset();seed(randomSeed);setter(m=>set(m,addr(m,global(m,'u'),'you','uprops')+L.CONFUSION*sizeOf('struct prop'),'prop','intrinsic',100));action('doloot_core');}
reset();contained();objectMenus();setter(m=>{set(m,global(m,'gc'),'instance_globals_c','current_container',0);setType(m,obj(m),K.WAN_CANCELLATION);set(m,obj(m),'obj','spe',1);const p=Number(m._probe_newobj(K.BAG_OF_HOLDING));m._probe_inventory(BigInt(p));m._probe_choice(0,1,1,1);});action('tipcontainer',m=>[obj(m,1)]);
const expectedRng=['do_loot_cont:2155','doloot_core:2203','doloot_core:2205','reverse_loot:2357','reverse_loot:2361','reverse_loot:2371','reverse_loot:2418','loot_mon:2467','mbag_explodes:2497','is_boh_item_gone:2512','in_container:2692','observe_quantum_cat:2832','tipcontainer:3803'];
assert.deepEqual([...observedRng].sort(),expectedRng.sort(),'all13 actual primary source RNG origin lines');assert.ok(displayDraws>0,'positive native display RNG');
console.log('PASS PICKUP RNG',checks,'top-level comparisons; all13 primary origins and native display draws observed.');
// Native long64 menu counts retain precision before the source's count clamps.
reset();objectMenus();setter(m=>{set(m,obj(m),'obj','quan',0x20000000000009n);m._probe_choice(0,0,1,1);m._probe_choicewide(0,0x20000000000003n);});scratchTypes=[[0,'struct mi *']];action('query_objlist',m=>[text(m,'wide native count'),addr(m,global(m,'gi'),'instance_globals_i','invent'),0,scratch(m),K.PICK_ANY,identity(m,'allow_all')]);for(const m of mods){const p=Number(new DataView(m.HEAPU8.buffer).getBigUint64(scratch(m),true));assert.equal(get(m,p,'mi','count'),0x20000000000003n);assert.equal(Buffer.from(m.HEAPU8.slice(p+20,p+24)).toString('hex'),'e5e5e5e5','all4 native menu padding bytes remain raw');}
// The private costly static persists across calls until an explicit recompute.
reset();setter(m=>m._probe_floor(BigInt(obj(m))));option(4,1);assert.equal(action('autopick_testobj',m=>[obj(m),1])[0],0n);option(4,0);assert.equal(action('autopick_testobj',m=>[obj(m),0])[0],0n);assert.equal(action('autopick_testobj',m=>[obj(m),1])[0],1n);
// Positive/null external regex-chain returns use genuine typed native links.
for(const match of [0,1]){reset();option(25,match);setter(m=>{set(m,global(m,'ga'),'instance_globals_a','apelist',ptr(m,4));set(m,ptr(m,4),'autopickup_exception','regex',ptr(m,0));set(m,ptr(m,4),'autopickup_exception','grab',0);});action('check_autopickup_exceptions',m=>[obj(m)]);action('autopick_testobj',m=>[obj(m),1]);}
// Exercise every immutable load-prefix array through its real native formatter.
for(const burden of [1,2,3,4]){reset();option(5,burden);action('pickup_prinv',m=>[obj(m),3,text(m,'lifting')]);action('encumber_msg');option(5,0);action('encumber_msg');}
for(const abc of [0,1])for(const selected of [0,3,6]){reset();setter(m=>{set(m,global(m,'flags'),'flag','lootabc',abc);m._probe_choice(0,selected,1,0);});action('in_or_out_menu',m=>[text(m,'choice'),obj(m,1),1,1,0,1]);}
// Positive genuine species-identity branches, with a native polymorph success
// instead of pretending an unhandled production death is a full-game proof.
for(const remote of [0,1]){reset();option(17,1);setter(m=>{setType(m,obj(m),K.CORPSE);set(m,obj(m),'obj','corpsenm',K.PM_COCKATRICE);});action('fatal_corpse_mistake',m=>[obj(m),remote]);}
for(const revival of [0,1]){reset();option(18,revival);setter(m=>{setType(m,obj(m),K.CORPSE);set(m,obj(m),'obj','corpsenm',K.PM_DEATH);});action('rider_corpse_revival',m=>[obj(m),0]);}
// Narrowing occurs at original typed native boundaries before map indexing.
reset();current();action('container_at',[65576,-65526,1]);action('able_to_loot',[65576,-65526,1]);
assert.equal(covered.size,66);console.log('PASS PICKUP FINAL',checks,'top-level comparisons; all66 original configured functions/all13 primary RNG origins/native display draws; controlled native dependency/UI/ownership world only. Native-host/full-game/public pending.');
// Legal swallowed-monster pickup may select a worn item; original source
// rejects it and copies the later selected menu_item over that24-byte slot.
reset();objectMenus();setter(m=>{const p=Number(m._probe_newobj(K.GOLD_PIECE));set(m,obj(m),'obj','nobj',p);for(const at of [obj(m),p]){set(m,at,'obj','where',K.OBJ_MINVENT);cell(m,addr(m,at,'obj','v'),ptr(m,2));}set(m,obj(m),'obj','owornmask',K.W_WEP);set(m,global(m,'gi'),'instance_globals_i','invent',0);set(m,ptr(m,2),'monst','minvent',obj(m));set(m,global(m,'u'),'you','uswallow',1);set(m,global(m,'u'),'you','ustuck',ptr(m,2));m._probe_choice(0,0,3,1);m._probe_choice2(0,1,2);});scratchTypes=[[0,'struct mi *']];assert.equal(action('query_objlist',m=>[text(m,'engulfer inventory'),addr(m,ptr(m,2),'monst','minvent'),0,scratch(m),K.PICK_ANY,identity(m,'allow_all')])[0],1n);for(const m of mods){const p=Number(new DataView(m.HEAPU8.buffer).getBigUint64(scratch(m),true));assert.equal(get(m,p,'mi','itemflags'),0xA1B2C3D5n);assert.equal(Buffer.from(m.HEAPU8.slice(p+20,p+24)).toString('hex'),'e6e6e6e6','all4 compaction padding bytes copied');}
for(const traits of [0,1])for(const ice of [0,1]){reset();contained();option(19,traits);setter(m=>{setType(m,obj(m),K.CORPSE);set(m,obj(m),'obj','corpsenm',ice?K.PM_ICE_TROLL:K.PM_HUMAN);set(m,obj(m),'obj','age',10);set(m,ptr(m,2),'monst','data',global(m,'mons')+(ice?K.PM_ICE_TROLL:K.PM_HUMAN)*sizeOf('struct permonst'));});action('removed_from_icebox',m=>[obj(m)]);}
console.log('PASS PICKUP VALID-CONTEXT FINAL',checks,'comparisons; fake-hero look-only and real worn-item24-byte compaction; positive/null attack and stored-monster fields.');
reset();assert.equal(L.GETOBJ_EXCLUDE,-3,'signed native header constant remains exact');assert.equal(action('stash_ok',[0])[0],-3n);assert.equal(action('tip_ok',[0])[0],-3n);
console.log('PASS PICKUP FROZEN-CANDIDATE',checks,'top-level comparisons; all66 actual functions,13 primary RNG origins,typed negative header constants and valid caller contexts.');
