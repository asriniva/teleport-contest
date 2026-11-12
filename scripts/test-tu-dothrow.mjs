import './pure-js-probes/deny-wasm.mjs';
import {createProbe,createReference,loadFixture,fixtureImports} from './pure-js-fixtures/load.mjs';
import {DataView as FixtureDataView} from './native-test-backend.mjs';
// Controlled configured memory64 comparison; native/game/public equivalence pending.
import assert from './native-test-assert.mjs';
import {readFileSync,writeFileSync} from 'node:fs';
import {pathToFileURL} from 'node:url';
import {resolve} from 'node:path';
const probeDir=resolve(process.env.DOTHROW_PROBE_DIR??'.cache/dothrow-first-pass');
const {default:refFactory}=await loadFixture("dothrow",pathToFileURL(resolve(probeDir,'dothrow-reference.mjs')));
const {default:hybridFactory}=await loadFixture("dothrow",pathToFileURL(resolve(probeDir,'dothrow-hybrid.mjs')));
const {callDothrow}=await loadFixture("dothrow",process.env.DOTHROW_RUNTIME??'../js/nethack/bindings/dothrow.js');
const schema=JSON.parse(readFileSync(new URL('../nethack-c/wasm/tu-fragments/dothrow-schema.json',import.meta.url))),metadata=JSON.parse(readFileSync(new URL('../nethack-c/wasm/tu-fragments/dothrow-source-metadata.json',import.meta.url))),functions=metadata.functions,names=functions.map(f=>f.name),kinds=Object.keys(schema.schema),covered=new Set();
const ref=await refFactory(),hybrid=await hybridFactory();hybrid.nethackPorted={dothrow:callDothrow};const mods=[ref,hybrid];
const testConstants=metadata.fixtureConstants;
const L=Object.fromEntries(schema.layoutKeys.map((n,i)=>[n,Number(ref._teleport_dothrow_layout(i))]));
testConstants.forEach((n,i)=>{assert.equal(ref._probe_constant(i),hybrid._probe_constant(i));L[n]=Number(ref._probe_constant(i));});
for(let i=0;i<schema.layoutKeys.length;i++)assert.equal(ref._teleport_dothrow_layout(i),hybrid._teleport_dothrow_layout(i));
const addr=(m,p,k,f)=>Number(m._teleport_dothrow_address(kinds.indexOf(k),BigInt(p),schema.schema[k].fields.findIndex(x=>x.name===f)));
const get=(m,p,k,f)=>m._teleport_dothrow_read(kinds.indexOf(k),BigInt(p),schema.schema[k].fields.findIndex(x=>x.name===f));
const set=(m,p,k,f,v)=>m._teleport_dothrow_write(kinds.indexOf(k),BigInt(p),schema.schema[k].fields.findIndex(x=>x.name===f),BigInt.asUintN(64,BigInt(v)));
const global=(m,n)=>Number(m._teleport_dothrow_global(schema.globals.findIndex(g=>g.name===n)));
const field=(m,n,k,f)=>addr(m,global(m,n),k,f),ptr=(m,i)=>Number(m._probe_pointer(i));
const setter=fn=>mods.forEach(fn),reset=()=>setter(m=>m._probe_reset()),fill=t=>setter(m=>{for(let x=0;x<80;x++)for(let y=0;y<21;y++)m._probe_map(x,y,t,0);}),map=(x,y,t,b=0)=>setter(m=>m._probe_map(x,y,t,b)),option=(i,v)=>setter(m=>m._probe_option(i,v)),seed=n=>setter(m=>m._probe_seed(n));
const obj=(m,i=0)=>ptr(m,4)+i*L['size:struct obj'],mon=(m,i=0)=>ptr(m,5)+i*L['size:struct monst'];
const regions=m=>[
 ...schema.globals.map((g,i)=>({name:g.name,p:global(m,g.name),size:Number(m._probe_global_size(i))})),
 ...[[0,'coord0',4],[1,'coord1',4],[2,'text',256],[3,'name',256],[4,'objpool',512*L['size:struct obj']],[5,'monpool',128*L['size:struct monst']],[6,'trappool',64*L['size:struct trap']],[7,'eshk',L['size:struct eshk']],[8,'mextra',L['size:struct mextra']],[9,'returning',L['size:struct throw_and_return_weapon']],[10,'scratch',8192],[11,'scalar',4],[12,'pronoun',16]].map(([i,name,size])=>({name,p:ptr(m,i),size})),
 ...schema.literals.map((text,i)=>({name:'sourceLiteral'+i,p:m.teleportDothrowLiteralCache?m.teleportDothrowLiteralCache.strings.get(text)??0:Number(m._probe_source_literal(i)),size:Buffer.byteLength(text)+1})),
 ...Array.from({length:9},(_,i)=>({name:'nativeIdentity'+i,p:Number(m._probe_identity(i)),size:1})),
 ...Array.from({length:m._probe_count(3)},(_,i)=>({name:'allocation'+i,p:Number(m._probe_alloc_pointer(i)),size:Number(m._probe_alloc_size(i))}))
];
const pointerID=(m,v)=>{const bits=BigInt(v);if(!bits)return'0';if(bits>BigInt(Number.MAX_SAFE_INTEGER)||bits<0n)return'UNKNOWN:'+bits;v=Number(bits);const list=regions(m),r=list.find(r=>r.p===v)??list.find(r=>r.p&&v>=r.p&&v<r.p+r.size);return r?r.name+'+'+(v-r.p):'UNKNOWN:'+v;};
const bare=t=>t.replace(/\b(?:const|volatile)\b/g,'').trim().replace(/\s+/g,' '),record=t=>kinds.find(k=>bare(schema.schema[k].ctype)===bare(t));
const size=t=>{t=bare(t);const a=t.match(/^(.*?)((?:\[\d+\])+)$/);if(a)return [...a[2].matchAll(/\[(\d+)\]/g)].reduce((n,x)=>n*Number(x[1]),size(a[1]));return t.includes('*')?8:L['size:'+t]??({'int':4,'unsigned int':4,'short':2,'unsigned short':2,'char':1,'signed char':1,'unsigned char':1,'long':8,'unsigned long':8}[t]);};
// Canonicalize only selected compiler-typed pointer fields, preserving every
// scalar, padding, unknown pointer, and unselected byte unchanged.
function raw(m,p,n,t,extra=[]){const bytes=m.HEAPU8.slice(p,p+n),pointers=[],slots=new Set();const slot=(at,path)=>{if(slots.has(at))return;slots.add(at);const v=new FixtureDataView(m.HEAPU8.buffer).getBigUint64(at,true);const id=pointerID(m,v);pointers.push([path,id]);if(!id.startsWith('UNKNOWN:'))bytes.fill(0,at-p,at-p+8);};
 const walk=(at,type,path)=>{type=bare(type);const ar=type.match(/^(.*?)((?:\[\d*\])+)$/);if(ar){const dims=[...ar[2].matchAll(/\[(\d*)\]/g)].map(x=>x[1]?Number(x[1]):Math.floor(n/size(ar[1]))),count=dims.reduce((a,b)=>a*b,1),step=size(ar[1]);if(ar[1].includes('*')||record(ar[1]))for(let i=0;i<count;i++)walk(at+i*step,ar[1],path+'['+i+']');return;}if(type.includes('*')){slot(at,path);return;}const k=record(type);if(k)for(const f of schema.schema[k].fields)if(!f.bit&&(f.canonical.includes('*')||f.canonical.includes('[')||record(f.canonical)))walk(addr(m,at,k,f.name),f.canonical,path+'.'+f.name);};
 walk(p,t,'');for(const [offset,label]of extra)slot(p+offset,label);return{bytes:Buffer.from(bytes).toString('hex'),pointers};}
const extras=(m,k,n)=>Array.from({length:n},(_,i)=>[Number(m._probe_pointer_offset(k,i)),'nativePointer'+i]);
function snapshot(m){return{globals:schema.globals.map((g,i)=>raw(m,global(m,g.name),Number(m._probe_global_size(i)),g.canonical)),coords:[0,1].map(i=>raw(m,ptr(m,i),4,'struct nhcoord')),scalar:Buffer.from(m.HEAPU8.slice(ptr(m,11),ptr(m,11)+4)).toString('hex'),objects:Array.from({length:m._probe_count(0)},(_,i)=>raw(m,obj(m,i),L['size:struct obj'],'struct obj',extras(m,0,4))),monsters:Array.from({length:m._probe_count(1)},(_,i)=>raw(m,mon(m,i),L['size:struct monst'],'struct monst',extras(m,1,5))),traps:Array.from({length:m._probe_count(2)},(_,i)=>raw(m,ptr(m,6)+i*L['size:struct trap'],L['size:struct trap'],'struct trap',extras(m,2,1))),shop:raw(m,ptr(m,7),L['size:struct eshk'],'struct eshk'),mextra:raw(m,ptr(m,8),L['size:struct mextra'],'struct mextra'),allocations:Array.from({length:m._probe_count(3)},(_,i)=>{const p=Number(m._probe_alloc_pointer(i)),n=Number(m._probe_alloc_size(i));return!p?null:raw(m,p,n,'unsigned char[]');}),queue:Array.from({length:m._probe_queue_count()},(_,i)=>m._probe_queue_identity(i)),errno:m._probe_errno(),error:m._probe_error(),draws:m._probe_draws(),trace:m.UTF8ToString(Number(m._probe_trace()))};}
let checks=0;
function compare(label){try{assert.deepEqual(snapshot(hybrid),snapshot(ref),label);checks++;}catch(e){writeFileSync(new URL('../.cache/dothrow-first-pass/mismatch.json',import.meta.url),JSON.stringify({label,ref:snapshot(ref),hybrid:snapshot(hybrid)},null,2));throw e;}}
function action(name,args=[]){covered.add(name);const rt=functions[names.indexOf(name)].type.qualType.split('(')[0];const result=mods.map((m,i)=>{const a=typeof args==='function'?args(m,i):args,sp=m.stackSave();try{const v=m._probe_action(names.indexOf(name),...Array.from({length:10},(_,j)=>BigInt(a[j]??0)));return rt.includes('*')&&v!==-999n?pointerID(m,v):v;}catch(e){console.error('ACTION ERROR',name,e);throw e;}finally{assert.equal(m.stackSave(),sp,name+' stack');}});assert.equal(result[0],result[1],name+' result');compare(name);return result;}
reset();action('multishot_class_bonus',m=>[L.PM_RANGER,obj(m),0]);
for(const role of [L.PM_CAVE_DWELLER,L.PM_MONK,L.PM_RANGER,L.PM_ROGUE,L.PM_NINJA,L.PM_SAMURAI])for(const skill of [L.P_DAGGER,-L.P_SLING,-L.P_SHURIKEN,-L.P_DART,L.P_SPEAR]){setter(m=>set(m,global(m,'objects')+L.ARROW*L['size:struct objclass'],'objclass','oc_subtyp',skill));action('multishot_class_bonus',m=>[role,obj(m),obj(m,1)]);}
// Arbitrary native path predicate, all octants, tie slopes, early stop and zero.
for(const dx of[-6,-3,0,3,6])for(const dy of[-6,-3,0,3,6])for(const stop of[0,2]){reset();option(20,stop);setter(m=>{m._probe_coord(0,40,10);m._probe_coord(1,40+dx,10+dy);});action('walk_path',m=>[ptr(m,0),ptr(m,1),m._probe_identity(0),ptr(m,11)]);}
reset();action('ok_to_throw',m=>[ptr(m,11)]);action('throw_ok',[0]);action('throw_ok',m=>[obj(m)]);
for(const mode of[0,1,3,4,5]){reset();option(mode,1);action('dothrow');}
for(let n=1;n<=4;n++){reset();seed(n);action('dothrow');reset();seed(n);action('dofire');}
reset();action('autoquiver');action('find_launcher',m=>[obj(m)]);action('endmultishot',[1]);
for(const dir of[[1,0],[-1,0],[0,1],[0,-1],[1,1],[-1,-1]]){reset();action('hurtle',[...dir,3,1]);reset();action('mhurtle',m=>[mon(m),...dir,3]);}
reset();action('hurtle_jump',m=>[ptr(m,11),41,10]);action('hurtle_step',m=>[ptr(m,11),42,10]);action('mhurtle_step',m=>[mon(m),46,10]);action('will_hurtle',m=>[mon(m),47,10]);
for(const typ of[L.ROOM,L.STONE,L.DOOR,L.POOL,L.MOAT,L.LAVAPOOL]){reset();map(41,10,typ,L.D_CLOSED<<2);action('hurtle_step',m=>[ptr(m,11),41,10]);}
reset();action('check_shop_obj',m=>[obj(m),45,10,0]);option(9,1);action('check_shop_obj',m=>[obj(m),45,10,1]);
for(const typ of[L.ARROW,L.DAGGER,L.BOOMERANG,L.AKLYS,L.GOLD_PIECE,L.CREAM_PIE,L.EGG,L.POT_WATER,L.BOULDER]){reset();setter(m=>set(m,obj(m),'obj','otyp',typ));action('harmless_missile',m=>[obj(m)]);action('throwing_weapon',m=>[obj(m)]);action('should_mulch_missile',m=>[obj(m)]);}
reset();action('hitfloor',m=>[obj(m),1]);reset();setter(m=>set(m,obj(m),'obj','quan',1));action('toss_up',m=>[obj(m),1]);
reset();action('sho_obj_return_to_u',m=>{const p=field(m,'gb','instance_globals_b','bhitpos');set(m,p,'nhcoord','x',45);set(m,p,'nhcoord','y',10);return[obj(m)];});action('throwit_return',[1]);
reset();setter(m=>set(m,global(m,'u'),'you','ustuck',mon(m)));action('swallowit',m=>[obj(m)]);
for(const replacement of[0,1,2]){reset();option(29,replacement);action('throwit',m=>[obj(m),0,0,0]);}
for(const dz of[-1,1]){reset();setter(m=>set(m,global(m,'u'),'you','dz',dz));action('throwit',m=>[obj(m),0,0,0]);}
reset();action('return_throw_to_inv',m=>[obj(m),L.W_WEP,1,obj(m,1)]);action('omon_adj',m=>[mon(m),obj(m),1]);action('tmiss',m=>[obj(m),mon(m),1]);
for(let n=1;n<=6;n++){reset();seed(n);action('throwit_mon_hit',m=>[obj(m),mon(m)]);reset();seed(n);action('thitmonst',m=>[mon(m),obj(m)]);}
for(const buddy of[0,1])for(const known of[0,1])for(const material of[L.GEMSTONE,L.GLASS]){reset();setter(m=>{set(m,obj(m),'obj','otyp',L.DIAMOND);set(m,obj(m),'obj','oclass',L.GEM_CLASS);set(m,obj(m),'obj','dknown',known);const p=global(m,'objects')+L.DIAMOND*L['size:struct objclass'];set(m,p,'objclass','oc_material',material);set(m,p,'objclass','oc_name_known',known);set(m,field(m,'u','you','ualign'),'align','type',buddy);});action('gem_accept',m=>[mon(m),obj(m)]);}
for(const typ of[L.MIRROR,L.POT_WATER,L.POT_OIL,L.EGG,L.EXPENSIVE_CAMERA,L.BOULDER,L.STATUE]){reset();setter(m=>{set(m,obj(m),'obj','otyp',typ);set(m,obj(m),'obj','oclass',typ===L.POT_WATER||typ===L.POT_OIL?L.POTION_CLASS:L.TOOL_CLASS);});action('breaktest',m=>[obj(m)]);action('breakmsg',m=>[obj(m),1]);action('hero_breaks',m=>[obj(m),40,10,L.BRK_KNOWN2NOTBREAK]);action('hero_breaks',m=>[obj(m),40,10,L.BRK_FROM_INV|L.BRK_KNOWN2BREAK]);reset();setter(m=>set(m,obj(m),'obj','otyp',typ));action('breaks',m=>[obj(m),40,10]);reset();setter(m=>set(m,obj(m),'obj','otyp',typ));action('breakobj',m=>[obj(m),40,10,1,0]);}
reset();action('release_camera_demon',m=>[obj(m),43,10]);reset();setter(m=>{set(m,obj(m),'obj','otyp',L.GOLD_PIECE);set(m,obj(m),'obj','oclass',L.COIN_CLASS);});action('throw_gold',m=>[obj(m)]);

reset();action('throw_obj',m=>[obj(m),1]);
// The 8-byte saved aggregate must survive native direction-prompt mutation.
reset();setter(m=>{const split=addr(m,field(m,'svc','instance_globals_saved_c','context'),'context_info','objsplit');set(m,split,'obj_split','parent_oid',1);set(m,split,'obj_split','child_oid',0x80000001);});option(0,1);option(47,1);action('throw_obj',m=>[obj(m),1]);assert.match(ref.UTF8ToString(Number(ref._probe_trace())),/split_context=1,2147483649/);
// Persistently queued native and owned callbacks execute after dofire returns.
reset();setter(m=>{new FixtureDataView(m.HEAPU8.buffer).setBigUint64(global(m,'uquiver'),BigInt(obj(m)),true);new FixtureDataView(m.HEAPU8.buffer).setBigUint64(global(m,'uswapwep'),BigInt(obj(m,1)),true);set(m,global(m,'iflags'),'instance_flags','fireassist',1);});action('dofire');assert.deepEqual(snapshot(ref).queue,[7,3]);
for(const index of[0,1]){const result=mods.map(m=>{const sp=m.stackSave();try{return m._probe_queue_run(index);}finally{assert.equal(m.stackSave(),sp,'queued callback stack');}});assert.equal(result[0],result[1]);compare('queued callback '+index);}
// Both predecessors enter the same petrify body, including destroyed obj==0.
for(const typ of[L.EGG,L.CORPSE]){reset();setter(m=>{set(m,obj(m),'obj','otyp',typ);set(m,obj(m),'obj','oclass',L.FOOD_CLASS);set(m,obj(m),'obj','quan',1);set(m,obj(m),'obj','corpsenm',L.PM_COCKATRICE);});option(35,typ===L.CORPSE);action('toss_up',m=>[obj(m),0]);assert.equal(ref._probe_error(),5);}
// Formal narrowing and full-width weapon/property/shop fields.
reset();action('hurtle_step',m=>[ptr(m,11),65577,-65526]);
for(const mask of[0x20000000000001n|BigInt(L.W_WEP),0x40000000000003n|BigInt(L.W_SWAPWEP)]){reset();setter(m=>{set(m,obj(m),'obj','owornmask',mask);set(m,obj(m),'obj','quan',0x20000000000001n);});action('return_throw_to_inv',m=>[obj(m),mask,257,obj(m,1)]);}
reset();setter(m=>{const prop=field(m,'u','you','uprops')+L.WWALKING*L['size:struct prop'];set(m,prop,'prop','extrinsic',0x20000000000000n);});action('hurtle_jump',m=>[ptr(m,11),41,10]);
reset();option(9,1);setter(m=>{set(m,obj(m),'obj','unpaid',1);set(m,global(m,'gh'),'instance_globals_h','hero_seq',0x40000000000003n);set(m,ptr(m,7),'eshk','break_seq',0x20000000000001n);});action('breakobj',m=>[obj(m),45,10,1,0]);
// Returning/tethered weapon and merge-to-replacement ownership paths.
for(const kind of[1,2])for(const merge of[0,1]){reset();option(28,kind);option(32,merge);setter(m=>{set(m,obj(m),'obj','otyp',L.AKLYS);set(m,obj(m),'obj','quan',1);new FixtureDataView(m.HEAPU8.buffer).setBigUint64(global(m,'uwep'),BigInt(obj(m)),true);set(m,obj(m),'obj','owornmask',L.W_WEP);});action('throwit',m=>[obj(m),0x20000000000000n|BigInt(L.W_WEP),1,obj(m,1)]);}

assert.equal(covered.size,39,names.filter(n=>!covered.has(n)).join(','));console.log('PASS DOTHROW baseline',checks,'comparisons all39; controlled-world native/full-game/public pending.');

// Scalar address bits remain raw and reject intentional mismatch.
reset();setter(m=>set(m,obj(m),'obj','quan',BigInt(obj(m))));const witness=mods.map(m=>raw(m,obj(m),L['size:struct obj'],'struct obj',extras(m,0,4)));for(let i=0;i<2;i++){const m=mods[i],off=addr(m,obj(m),'obj','quan')-obj(m);assert.equal(witness[i].bytes.slice(off*2,(off+8)*2),Buffer.from(m.HEAPU8.slice(obj(m)+off,obj(m)+off+8)).toString('hex'));}set(hybrid,obj(hybrid),'obj','quan',BigInt(obj(hybrid))+8n);assert.throws(()=>assert.deepEqual(raw(hybrid,obj(hybrid),L['size:struct obj'],'struct obj',extras(hybrid,0,4)),witness[0]));

// Unknown typed pointers retain their exact raw bytes, including unsafe integers.
reset();const unknown=0x20000000000001n;for(const m of mods){const at=obj(m)+Number(m._probe_pointer_offset(0,0));new FixtureDataView(m.HEAPU8.buffer).setBigUint64(at,unknown,true);const r=raw(m,obj(m),L['size:struct obj'],'struct obj',extras(m,0,4)),off=at-obj(m);assert.equal(r.bytes.slice(off*2,(off+8)*2),Buffer.from(m.HEAPU8.slice(at,at+8)).toString('hex'));assert.ok(r.pointers.some(([name,id])=>id==='UNKNOWN:'+unknown));}const beforeUnknown=raw(ref,obj(ref),L['size:struct obj'],'struct obj',extras(ref,0,4));new FixtureDataView(hybrid.HEAPU8.buffer).setBigUint64(obj(hybrid)+Number(hybrid._probe_pointer_offset(0,0)),unknown+2n,true);assert.throws(()=>assert.deepEqual(raw(hybrid,obj(hybrid),L['size:struct obj'],'struct obj',extras(hybrid,0,4)),beforeUnknown));

// Native getobj invokes private owned throw_ok with growth and Module reentry.
const third=await hybridFactory();third._probe_reset();ref._probe_reset();let reentered=false,callbacks=0;
third.nethackPorted={dothrow(services,name,...args){if(name==='throw_ok'){callbacks++;if(!reentered){reentered=true;const sp=hybrid.stackSave();hybrid._probe_action(names.indexOf('multishot_class_bonus'),BigInt(L.PM_RANGER),BigInt(obj(hybrid)),0n,0n,0n,0n,0n,0n,0n,0n);assert.equal(hybrid.stackSave(),sp);const old=third.HEAPU8.buffer;third._probe_growth();assert.notEqual(third.HEAPU8.buffer,old);}}return callDothrow(services,name,...args);}};
for(const m of[ref,third]){const sp=m.stackSave();m._probe_action(names.indexOf('dothrow'),0n,0n,0n,0n,0n,0n,0n,0n,0n,0n);assert.equal(m.stackSave(),sp);}assert.ok(reentered&&callbacks>0);assert.deepEqual(snapshot(third),snapshot(ref),'native private callback with actual growth/cross-Module reentry');
console.log('PASS DOTHROW final',checks,'state/RNG/full-format/dependency/errno comparisons all39; native callback identities/queue/path/ownership/64bit/narrowing/petrify/stack/growth/reentry. Controlled catalogue/world; native/full-game/public pending.');
