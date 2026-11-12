// Controlled configured memory64 comparison; native/game/public equivalence pending.
import assert from 'node:assert/strict';
import {readFileSync,writeFileSync} from 'node:fs';
import {pathToFileURL} from 'node:url';
import {resolve} from 'node:path';
const probeDir=resolve(process.env.MKLEV_PROBE_DIR??'.cache/mklev-first-pass');
const {default:refFactory}=await import(pathToFileURL(resolve(probeDir,'mklev-reference.mjs')));
const {default:hybridFactory}=await import(pathToFileURL(resolve(probeDir,'mklev-hybrid.mjs')));
const {callMklev}=await import(process.env.MKLEV_RUNTIME??'../js/nethack/bindings/mklev.js');
const schema=JSON.parse(readFileSync(new URL('../nethack-c/wasm/tu-fragments/mklev-schema.json',import.meta.url))),metadata=JSON.parse(readFileSync(new URL('../nethack-c/wasm/tu-fragments/mklev-source-metadata.json',import.meta.url))),functions=metadata.functions,names=functions.map(f=>f.name),kinds=Object.keys(schema.schema),covered=new Set();
const ref=await refFactory(),hybrid=await hybridFactory();hybrid.nethackPorted={mklev:callMklev};const mods=[ref,hybrid];
const testConstants=["ALTAR", "DOOR", "FILL_NORMAL", "HWALL", "MOAT", "OROOM", "POOL", "ROOM", "SDOOR", "STONE", "TELEP_TRAP", "WATER", "all_themes", "most_themes", "tut_themes"];
const L=Object.fromEntries(schema.layoutKeys.map((n,i)=>[n,Number(ref._teleport_mklev_layout(i))]));
testConstants.forEach((n,i)=>{assert.equal(ref._probe_constant(i),hybrid._probe_constant(i));L[n]=ref._probe_constant(i);});
for(let i=0;i<schema.layoutKeys.length;i++)assert.equal(ref._teleport_mklev_layout(i),hybrid._teleport_mklev_layout(i));
const addr=(m,p,k,f)=>Number(m._teleport_mklev_address(kinds.indexOf(k),BigInt(p),schema.schema[k].fields.findIndex(x=>x.name===f)));
const get=(m,p,k,f)=>m._teleport_mklev_read(kinds.indexOf(k),BigInt(p),schema.schema[k].fields.findIndex(x=>x.name===f));
const set=(m,p,k,f,v)=>m._teleport_mklev_write(kinds.indexOf(k),BigInt(p),schema.schema[k].fields.findIndex(x=>x.name===f),BigInt.asUintN(64,BigInt(v)));
const global=(m,n)=>Number(m._teleport_mklev_global(schema.globals.findIndex(g=>g.name===n)));
const field=(m,n,k,f)=>addr(m,global(m,n),k,f),ptr=(m,i)=>Number(m._probe_pointer(i));
const setter=fn=>mods.forEach(fn),reset=()=>setter(m=>m._probe_reset()),fill=t=>setter(m=>{for(let x=0;x<80;x++)for(let y=0;y<21;y++)m._probe_map(x,y,t,0);}),map=(x,y,t,b=0)=>setter(m=>m._probe_map(x,y,t,b)),option=(i,v)=>setter(m=>m._probe_option(i,v)),seed=n=>setter(m=>m._probe_seed(n));
const room=(m,i=0)=>field(m,'svr','instance_globals_saved_r','rooms')+i*L['size:struct mkroom'];
const regions=m=>[
 ...schema.globals.map((g,i)=>({name:g.name,p:global(m,g.name),size:Number(m._probe_global_size(i))})),
 ...[[0,'coord',4],[1,'level',4],[2,'text',256],[3,'gang',256],[4,'objpool',Number(m._probe_region_size(0))],[5,'monpool',Number(m._probe_region_size(1))],[6,'trappool',Number(m._probe_region_size(2))],[7,'branch',Number(m._probe_region_size(3))],[8,'speciallevel',Number(m._probe_region_size(4))],[9,'luastates',256],[10,'scratch',8192],[11,'vizrows',1680],[12,'vizptrs',168]].map(([i,name,size])=>({name,p:ptr(m,i),size})),
 ...Array.from({length:6},(_,i)=>({name:'nativeIdentity'+i,p:Number(m._probe_identity(i)),size:i<4?['cmd_before','level_enter','level_leave','end_turn'][i].length+1:1})),
 ...Array.from({length:m._probe_count(3)},(_,i)=>({name:'allocation'+i,p:Number(m._probe_alloc_pointer(i)),size:Number(m._probe_alloc_size(i))}))
];
const pointerID=(m,v)=>{v=Number(v);if(!v)return'0';const r=regions(m).find(r=>r.p&&v>=r.p&&v<r.p+r.size);return r?r.name+'+'+(v-r.p):'UNKNOWN:'+v;};
const bare=t=>t.replace(/\b(?:const|volatile)\b/g,'').trim().replace(/\s+/g,' '),record=t=>kinds.find(k=>bare(schema.schema[k].ctype)===bare(t));
const size=t=>{t=bare(t);const a=t.match(/^(.*?)((?:\[\d+\])+)$/);if(a)return [...a[2].matchAll(/\[(\d+)\]/g)].reduce((n,x)=>n*Number(x[1]),size(a[1]));return t.includes('*')?8:L['size:'+t]??({'int':4,'unsigned int':4,'short':2,'unsigned short':2,'char':1,'signed char':1,'unsigned char':1,'long':8,'unsigned long':8}[t]);};
// Canonicalize only selected compiler-typed pointer fields, preserving every
// scalar, padding, unknown pointer, and unselected byte unchanged.
function raw(m,p,n,t,extra=[]){const bytes=m.HEAPU8.slice(p,p+n),pointers=[],slots=new Set();const slot=(at,path)=>{if(slots.has(at))return;slots.add(at);const v=new DataView(m.HEAPU8.buffer).getBigUint64(at,true);pointers.push([path,pointerID(m,v)]);bytes.fill(0,at-p,at-p+8);};
 const walk=(at,type,path)=>{type=bare(type);const ar=type.match(/^(.*?)((?:\[\d*\])+)$/);if(ar){const dims=[...ar[2].matchAll(/\[(\d*)\]/g)].map(x=>x[1]?Number(x[1]):Math.floor(n/size(ar[1]))),count=dims.reduce((a,b)=>a*b,1),step=size(ar[1]);if(ar[1].includes('*')||record(ar[1]))for(let i=0;i<count;i++)walk(at+i*step,ar[1],path+'['+i+']');return;}if(type.includes('*')){slot(at,path);return;}const k=record(type);if(k)for(const f of schema.schema[k].fields)if(!f.bit&&(f.canonical.includes('*')||f.canonical.includes('[')||record(f.canonical)))walk(addr(m,at,k,f.name),f.canonical,path+'.'+f.name);};
 walk(p,t,'');for(const [offset,label]of extra)slot(p+offset,label);return{bytes:Buffer.from(bytes).toString('hex'),pointers};}
const extras=(m,k,n)=>Array.from({length:n},(_,i)=>[Number(m._probe_pointer_offset(k,i)),'nativePointer'+i]);
function snapshot(m){return{globals:schema.globals.map((g,i)=>raw(m,global(m,g.name),Number(m._probe_global_size(i)),g.canonical)),coord:raw(m,ptr(m,0),4,'struct nhcoord'),objects:Array.from({length:m._probe_count(0)},(_,i)=>raw(m,ptr(m,4)+i*L['size:struct obj'],L['size:struct obj'],'struct obj',extras(m,0,4))),monsters:Array.from({length:m._probe_count(1)},(_,i)=>raw(m,ptr(m,5)+i*L['size:struct monst'],L['size:struct monst'],'struct monst',extras(m,1,5))),traps:Array.from({length:m._probe_count(2)},(_,i)=>raw(m,ptr(m,6)+i*L['size:struct trap'],L['size:struct trap'],'struct trap',extras(m,2,1))),allocations:Array.from({length:m._probe_count(3)},(_,i)=>{const p=Number(m._probe_alloc_pointer(i)),n=Number(m._probe_alloc_size(i));return!p?null:raw(m,p,n,m._probe_alloc_kind(i)===1?'struct stairway':'unsigned char[]',m._probe_alloc_kind(i)===1?extras(m,3,1):[]);}),branch:raw(m,ptr(m,7),L['size:struct branch'],'struct branch'),vision:Buffer.from(m.HEAPU8.slice(ptr(m,11),ptr(m,11)+1680)).toString('hex'),error:m._probe_error(),draws:m._probe_draws(),trace:m.UTF8ToString(Number(m._probe_trace()))};}
let checks=0;
function compare(label){try{assert.deepEqual(snapshot(hybrid),snapshot(ref),label);checks++;}catch(e){writeFileSync(new URL('../.cache/mklev-first-pass/mismatch.json',import.meta.url),JSON.stringify({label,ref:snapshot(ref),hybrid:snapshot(hybrid)},null,2));throw e;}}
function action(name,args=[]){covered.add(name);const rt=functions[names.indexOf(name)].type.qualType.split('(')[0];const result=mods.map((m,i)=>{const a=typeof args==='function'?args(m,i):args,sp=m.stackSave();try{const v=m._probe_action(names.indexOf(name),...Array.from({length:10},(_,j)=>BigInt(a[j]??0)));return rt.includes('*')&&v!==-999n?pointerID(m,v):v;}finally{assert.equal(m.stackSave(),sp,name+' stack');}});assert.equal(result[0],result[1],name+' result');compare(name);return result;}
function rooms(){action('add_room',[4,3,9,7,1,L.OROOM,0]);action('add_room',[24,3,29,7,0,L.OROOM,0]);}
reset();action('mkroom_cmp',m=>[room(m),room(m)]);action('mkroom_cmp',m=>{set(m,room(m),'mkroom','lx',3);set(m,room(m,1),'mkroom','lx',7);return[room(m),room(m,1)];});
reset();rooms();action('topologize',m=>[room(m)]);action('topologize',m=>[room(m,1)]);
for(const dir of [0,2,4,6,9])action('finddpos',m=>[ptr(m,0),dir,room(m)]);
action('good_rm_wall_doorpos',m=>[3,4,2,room(m)]);setter(m=>m._probe_coord(3,4));action('finddpos_shift',m=>[ptr(m,0),ptr(m,0)+2,6,room(m)]);
action('cardinal_nextto_room',m=>[room(m),3,4]);action('do_room_or_subroom',m=>[room(m,2),45,3,49,7,1,L.OROOM,0,1]);action('sort_rooms');action('join',[0,1,0]);action('makecorridors');
action('alloc_doors');for(let i=0;i<20;i++)action('add_door',m=>[4+i%5,2,room(m,i%2)]);action('add_door',m=>[4,2,room(m)]);
for(const typ of [L.DOOR,L.SDOOR]){map(5,2,L.HWALL);action('dosdoor',m=>[5,2,room(m),typ]);}
action('bydoor',[5,3]);action('okdoor',[5,2]);action('maybe_sdoor',[50]);action('dodoor',m=>[6,2,room(m)]);
action('place_niche',m=>[room(m),ptr(m,10),ptr(m,10)+8,ptr(m,10)+10]);action('makeniche',[L.TELEP_TRAP]);action('make_niches');action('makevtele');
action('add_subroom',m=>[room(m),5,4,7,6,1,L.OROOM,0]);action('topologize',m=>[room(m)]);setter(m=>{set(m,room(m),'mkroom','needfill',L.FILL_NORMAL);set(m,Number(get(m,global(m,'gs'),'instance_globals_s','subrooms')),'mkroom','needfill',L.FILL_NORMAL);});action('fill_ordinary_room',m=>[room(m),1]);
action('count_level_features');action('chk_okdoor',[5,2]);action('mklev_sanity_check');action('clear_level_structures');
for(let n=1;n<9;n++){reset();seed(n);rooms();action('generate_stairs_room_good',m=>[room(m),n%4-1]);action('generate_stairs_find_room');action('generate_stairs');for(const name of ['mkfount','mksink','mkaltar','mkgrave'])action(name,m=>[room(m)]);action('find_okay_roompos',m=>[room(m,1),ptr(m,0)]);}
reset();fill(L.ROOM);rooms();action('pos_to_room',[5,4]);action('find_branch_room',m=>[ptr(m,0)]);action('place_branch',m=>[ptr(m,7),5,5]);action('occupied',[5,5]);
for(let n=1;n<=12;n++){reset();fill(L.ROOM);seed(n);rooms();action('traptype_rnd',[n%4]);action('traptype_roguelvl');setter(m=>m._probe_coord(6,5));action('mktrap',m=>[n,0,room(m),ptr(m,0)]);action('mktrap_victim',m=>[ptr(m,6)]);}
action('mktrap',[0,0,0,0]);action('mktrap',[0,0,0,0]);action('mkstairs',[6,6,0,0,0]);action('mkstairs',[0,0,1,0,0]);
for(const typ of [L.WATER,L.POOL,L.MOAT,L.STONE]){reset();fill(typ);seed(21);action('water_has_kelp',[5,5,3,7]);action('mineralize',[40,60,10,5,1]);}
reset();rooms();action('level_finalize_topology');
for(const loadfail of [0,1,2]){reset();option(8,loadfail===2);option(9,loadfail===1);setter(m=>{m.stringToUTF8('fixture.lua',addr(m,field(m,'svd','instance_globals_saved_d','dungeons'),'dungeon','themerms'),32);});action('makerooms');action('themerooms_post_level_generate');for(const group of [L.tut_themes,L.most_themes,L.all_themes])action('free_luathemes',[group]);}
for(let n=1;n<=5;n++){reset();seed(n);action('makelevel');}
reset();option(7,1);action('mklev');reset();seed(15);action('mklev');
reset();fill(L.HWALL);action('mkinvk_check_wall',[5,5]);action('mkinvpos',[5,5,0]);action('mkinvpos',[1,5,2]);action('mkinvpos',[-1,5,2]);reset();fill(L.HWALL);action('mkinvokearea');action('mk_knox_portal',[5,5]);

// 200-attempt occupied positions and recursive subroom topology.
reset();rooms();for(let x=4;x<=9;x++)for(let y=3;y<=7;y++)map(x,y,L.ALTAR);action('find_okay_roompos',m=>[room(m),ptr(m,0)]);setter(m=>m._probe_coord(5,5));action('mktrap',m=>[1,0,room(m),0]);
reset();rooms();action('add_subroom',m=>[room(m),5,4,7,6,1,L.OROOM,0]);action('topologize',m=>[room(m)]);
// Actual two-predecessor fill_vault join with original effect block once.
let vaultChecks=0;for(const failfirst of[0,1,3])for(let n=31;n<=33;n++){reset();seed(n);option(11,10);option(14,failfirst);action('makelevel');vaultChecks+=ref.UTF8ToString(Number(ref._probe_trace())).split('check_room(').length-1;}assert.ok(vaultChecks>=4,'vault creation/check fallback cases reached');
// Multiple Lua states, tutorial/endgame release filters, and level-enter callback.
for(const group of[L.tut_themes,L.most_themes,L.all_themes]){reset();setter(m=>{const themes=field(m,'gl','instance_globals_l','luathemes');for(let i=0;i<4;i++)new DataView(m.HEAPU8.buffer).setBigUint64(themes+i*8,BigInt(ptr(m,9)+i*16),true);});action('free_luathemes',[group]);}
reset();setter(m=>{set(m,global(m,'gl'),'instance_globals_l','luacore',ptr(m,9));new DataView(m.HEAPU8.buffer).setInt32(global(m,'nhcb_counts')+4,1,true);});action('makelevel');assert.match(ref.UTF8ToString(Number(ref._probe_trace())),/lua_getglobal\(luastates\+0,nh_callback_run\)/);


// Wide native long fields participate in original age arithmetic and raw output.
reset();fill(L.ROOM);option(25,1);setter(m=>m._probe_coord(6,5));rooms();action('mktrap',m=>[1,0x100000000n,room(m),ptr(m,0)]);action('mktrap_victim',m=>[ptr(m,6)]);const wideObjectCount=ref._probe_count(0);assert.ok(wideObjectCount>0);assert.ok(Array.from({length:wideObjectCount},(_,i)=>BigInt.asIntN(64,get(ref,ptr(ref,4)+i*L['size:struct obj'],'obj','age'))).some(v=>v>0x20000000000000n));
// Configured makelevel selection arms, including Rogue source goto skip0.
for(const mode of['special','proto','fill','quest','hell','rogue']){reset();setter(m=>{const dun=field(m,'svd','instance_globals_saved_d','dungeons'),top=field(m,'svd','instance_globals_saved_d','dungeon_topology');if(mode==='special')m._probe_option(18,1);if(mode==='proto'||mode==='fill')m.stringToUTF8('fixture',addr(m,dun,'dungeon',mode==='proto'?'proto':'fill_lvl'),15);if(mode==='quest'){m._probe_option(2,1);m.stringToUTF8('Arc',ptr(m,2),256);set(m,field(m,'gu','instance_globals_u','urole'),'Role','filecode',ptr(m,2));}if(mode==='hell')m._probe_option(1,1);if(mode==='rogue'){const lev=addr(m,top,'dgn_topology','d_rogue_level');set(m,lev,'d_level','dnum',0);set(m,lev,'d_level','dlevel',3);}});action('makelevel');}
// Above-Oracle supply chest/static item arrays and same-line nested RNG sites.
reset();setter(m=>{const top=field(m,'svd','instance_globals_saved_d','dungeon_topology'),lev=addr(m,top,'dgn_topology','d_oracle_level');set(m,lev,'d_level','dnum',0);set(m,lev,'d_level','dlevel',15);});rooms();for(let n=41;n<=44;n++){seed(n);setter(m=>set(m,room(m),'mkroom','needfill',L.FILL_NORMAL));action('fill_ordinary_room',m=>[room(m),1]);}

assert.equal(covered.size,57,names.filter(n=>!covered.has(n)).join(','));
console.log('PASS MKLEV',checks,'controlled state/RNG/full-trace comparisons; all 57 functions. Native/full-game/public pending.');

// Stable equal-key sorting invokes the actual native sorter and JS comparator.
reset();action('add_room',[24,3,29,7,1,L.OROOM,0]);action('add_room',[4,3,9,7,1,L.OROOM,0]);action('add_room',[24,12,29,16,0,L.OROOM,0]);
map(50,15,L.ROOM);setter(m=>{const grid=Number(m._probe_grid());set(m,grid+(50*21+15)*8,'rm','roomno',7);});action('sort_rooms');
// Narrowed formals, initialized sandbox, persistent statics, and error frames.
reset();action('add_room',[65540,65539,65545,65543,257,256,256]);action('generate_stairs_room_good',m=>[room(m),-0x100000001n]);action('generate_stairs');reset();action('generate_stairs');
reset();option(16,1);rooms();action('find_okay_roompos',m=>[room(m),ptr(m,0)]);option(16,0);map(4,3,L.ALTAR);action('find_okay_roompos',m=>[room(m),ptr(m,0)]);
// A scalar with native-address bits must remain raw and detect a mismatch.
reset();setter(m=>{m.HEAPU8.fill(0,ptr(m,4),ptr(m,4)+L['size:struct obj']);set(m,ptr(m,4),'obj','quan',BigInt(ptr(m,4)));});
const scalarSnapshots=mods.map(m=>raw(m,ptr(m,4),L['size:struct obj'],'struct obj',extras(m,0,4)));
for(let i=0;i<2;i++){const m=mods[i],at=addr(m,ptr(m,4),'obj','quan')-ptr(m,4);assert.equal(scalarSnapshots[i].bytes.slice(at*2,(at+8)*2),Buffer.from(m.HEAPU8.slice(ptr(m,4)+at,ptr(m,4)+at+8)).toString('hex'));}
set(hybrid,ptr(hybrid,4),'obj','quan',BigInt(ptr(hybrid,4))+8n);assert.throws(()=>assert.deepEqual(raw(hybrid,ptr(hybrid,4),L['size:struct obj'],'struct obj',extras(hybrid,0,4)),scalarSnapshots[0]));
// Fresh Module, C→JS owned comparator callback, real growth, cross-Module reentry.
const third=await hybridFactory();third._probe_reset();ref._probe_reset();let callbackCount=0,reentered=false;
third.nethackPorted={mklev(services,name,...args){if(name==='mkroom_cmp'){callbackCount++;if(!reentered){reentered=true;const prior=hybrid.stackSave();hybrid._probe_action(names.indexOf('mkroom_cmp'),BigInt(room(hybrid)),BigInt(room(hybrid)),0n,0n,0n,0n,0n,0n,0n,0n);assert.equal(hybrid.stackSave(),prior);const old=third.HEAPU8.buffer;third._probe_growth();assert.notEqual(third.HEAPU8.buffer,old);}}return callMklev(services,name,...args);}};
for(const m of[ref,third]){for(const x of[24,4,24])m._probe_action(names.indexOf('add_room'),BigInt(x),3n,BigInt(x+5),7n,1n,0n,0n,0n,0n,0n);const sp=m.stackSave();m._probe_action(names.indexOf('sort_rooms'),0n,0n,0n,0n,0n,0n,0n,0n,0n,0n);assert.equal(m.stackSave(),sp);}
assert.ok(reentered&&callbackCount>0);assert.deepEqual(snapshot(third),snapshot(ref),'native sort callback with real growth and cross-Module reentry');
console.log('PASS MKLEV final',checks,'state/RNG/full-trace comparisons; all57, raw scalars/padding with typed-pointer witness, real growth/reentry/Module isolation/stack cleanup. Controlled Lua/world only; native/full-game/public pending.');
