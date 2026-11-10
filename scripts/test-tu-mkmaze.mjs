// Controlled configured memory64 comparison; no native/game/public equivalence claim.
import assert from 'node:assert/strict';
import {readFileSync,writeFileSync} from 'node:fs';
import {pathToFileURL} from 'node:url';
import {resolve} from 'node:path';
const probeDir=resolve(process.env.MKMAZE_PROBE_DIR??'.cache/mkmaze-first-pass');
const {default:refFactory}=await import(pathToFileURL(resolve(probeDir,'mkmaze-reference.mjs')));
const {default:hybridFactory}=await import(pathToFileURL(resolve(probeDir,'mkmaze-hybrid.mjs')));
const {callMkmaze}=await import(process.env.MKMAZE_RUNTIME??'../js/ported/mkmaze-runtime.js');
const schema=JSON.parse(readFileSync(new URL('../nethack-c/wasm/tu-fragments/mkmaze-schema.json',import.meta.url))),functions=JSON.parse(readFileSync(new URL('../nethack-c/wasm/tu-fragments/mkmaze-source-metadata.json',import.meta.url))).functions,names=functions.map(f=>f.name),kinds=Object.keys(schema.schema),covered=new Set();
const ref=await refFactory(),hybrid=await hybridFactory();hybrid.nethackPorted={mkmaze:callMkmaze};const mods=[ref,hybrid];
const layout=Object.fromEntries(schema.layoutKeys.map((n,i)=>[n,Number(ref._teleport_mkmaze_layout(i))]));
for(let i=0;i<schema.layoutKeys.length;i++)assert.equal(ref._teleport_mkmaze_layout(i),hybrid._teleport_mkmaze_layout(i));
const L=layout;
const addr=(m,p,k,f)=>Number(m._teleport_mkmaze_address(kinds.indexOf(k),BigInt(p),schema.schema[k].fields.findIndex(x=>x.name===f)));
const get=(m,p,k,f)=>m._teleport_mkmaze_read(kinds.indexOf(k),BigInt(p),schema.schema[k].fields.findIndex(x=>x.name===f));
const set=(m,p,k,f,v)=>m._teleport_mkmaze_write(kinds.indexOf(k),BigInt(p),schema.schema[k].fields.findIndex(x=>x.name===f),BigInt.asUintN(64,BigInt(v)));
const global=(m,n)=>Number(m._teleport_mkmaze_global(schema.globals.findIndex(g=>g.name===n)));
const field=(m,n,k,f)=>addr(m,global(m,n),k,f);
const ptr=(m,i)=>Number(m._probe_pointer(i));
const reset=()=>mods.forEach(m=>m._probe_reset());
const fill=typ=>mods.forEach(m=>{for(let x=0;x<80;x++)for(let y=0;y<21;y++)m._probe_map(x,y,typ,0);});
const map=(x,y,t,b=0)=>mods.forEach(m=>m._probe_map(x,y,t,b));
const option=(i,v)=>mods.forEach(m=>m._probe_option(i,v));
const seed=n=>mods.forEach(m=>m._probe_seed(n));
const setter=fn=>mods.forEach(fn);
const knownRegions=m=>[
 ...schema.globals.map((g,i)=>({name:g.name,p:Number(m._teleport_mkmaze_global(i)),size:L['size:'+g.canonical]??(g.canonical.includes('*')?8:g.name==='mons'?L['size:struct permonst']*384:g.name==='objects'?L['size:struct objclass']*482:0)})),
 ...[[0,'coord',4],[1,'level',4],[2,'text',256],[3,'gang',256],[4,'objpool',L['size:struct obj']*512],[5,'monpool',L['size:struct monst']*256],[6,'trappool',L['size:struct trap']*128],[7,'serial',65536],[8,'exclusion',L['size:struct exclusion_zone']],[9,'nhfile',L['size:struct nh_file']],[10,'gas',L['size:NhRegion']],[11,'scratch',4096]].map(([i,name,size])=>({name,p:ptr(m,i),size})),
 ...Array.from({length:m._probe_count(3)},(_,i)=>({name:'allocation'+i,p:Number(m._probe_alloc_pointer(i)),size:Number(m._probe_alloc_size(i))}))
];
// Only explicit compiler-typed pointer slots are canonicalized. Unknown pointers
// and every unselected/scalar/padding byte remain raw and must match.
const pointerID=(m,v)=>{v=Number(v);if(!v)return '0';const r=knownRegions(m).find(r=>r.p&&v>=r.p&&v<r.p+r.size);return r?r.name+'+'+(v-r.p):'UNKNOWN:'+v;};
const rawRecord=(m,p,type)=>{const bytes=m.HEAPU8.slice(p,p+L['size:struct '+type]),pointers=[];schema.schema[type].fields.forEach(f=>{if(f.canonical.includes('*')&&!f.canonical.includes('[')){const at=addr(m,p,type,f.name),v=get(m,p,type,f.name);pointers.push([f.name,pointerID(m,v)]);bytes.fill(0,at-p,at-p+8);}});for(const [kind,which,name]of type==='obj'?[[0,0,'nobj'],[0,1,'v.nexthere']]:type==='monst'?[[1,0,'minvent']]:[]){if(pointers.some(([n])=>n===name))continue;const offset=Number(m._probe_pointer_offset(kind,which)),v=new DataView(m.HEAPU8.buffer).getBigUint64(p+offset,true);pointers.push([name,pointerID(m,v)]);bytes.fill(0,offset,offset+8);}return{bytes:Buffer.from(bytes).toString('hex'),pointers};};
const selectedState=m=>{const out={};const walk=(p,k,path)=>{for(const f of schema.schema[k].fields){const t=f.canonical,child=Object.keys(schema.schema).find(n=>schema.schema[n].ctype===t)||(t.startsWith('struct ')?t.slice(7):t.startsWith('union ')?t.slice(6):null);if(t.includes('['))continue;if(t.includes('*'))out[path+'.'+f.name]=pointerID(m,get(m,p,k,f.name));else if(child&&schema.schema[child])walk(addr(m,p,k,f.name),child,path+'.'+f.name);else if(!t.startsWith('struct ')&&!t.startsWith('union '))out[path+'.'+f.name]=get(m,p,k,f.name).toString();}};for(const g of schema.globals){if(g.canonical.includes('[')||g.canonical.includes('*'))continue;const k=Object.keys(schema.schema).find(n=>schema.schema[n].ctype===g.canonical);if(k)walk(global(m,g.name),k,g.name);}return out;};
const snapshot=m=>({selectedState:selectedState(m),grid:Buffer.from(m.HEAPU8.slice(Number(m._probe_grid()),Number(m._probe_grid())+80*21*8)).toString('hex'),coord:Buffer.from(m.HEAPU8.slice(ptr(m,0),ptr(m,0)+4)).toString('hex'),draws:m._probe_draws(),error:m._probe_error(),objects:Array.from({length:m._probe_count(0)},(_,i)=>rawRecord(m,ptr(m,4)+i*L['size:struct obj'],'obj')),monsters:Array.from({length:m._probe_count(1)},(_,i)=>rawRecord(m,ptr(m,5)+i*L['size:struct monst'],'monst')),traps:Array.from({length:m._probe_count(2)},(_,i)=>rawRecord(m,ptr(m,6)+i*L['size:struct trap'],'trap')),bubbles:Array.from({length:m._probe_count(3)},(_,i)=>{const p=Number(m._probe_alloc_pointer(i)),size=Number(m._probe_alloc_size(i));return !p?null:size===L['size:struct bubble']?rawRecord(m,p,'bubble'):null;}),serial:Buffer.from(m.HEAPU8.slice(ptr(m,7),ptr(m,7)+m._probe_serial_length())).toString('hex'),trace:m.UTF8ToString(Number(m._probe_trace()))});
let checks=0;
function compare(label){try{assert.deepEqual(snapshot(hybrid),snapshot(ref),label);checks++;}catch(e){writeFileSync(new URL('../.cache/mkmaze-first-pass/mismatch.json',import.meta.url),JSON.stringify({label,ref:snapshot(ref),hybrid:snapshot(hybrid)},null,2));throw e;}}
function action(name,args=[]){covered.add(name);const outputSlots=[];const result=mods.map((m,i)=>{const a=typeof args==='function'?args(m,i):args;if(name==='get_level_extends')outputSlots[i]=a.slice(0,4).map(Number);const stack=m.stackSave();try{return m._probe_action(names.indexOf(name),...Array.from({length:10},(_,j)=>BigInt(a[j]??0)));}finally{assert.equal(m.stackSave(),stack,name+' stack restored');}});assert.equal(result[0],result[1],name+' result');if(outputSlots.length){const cells=mods.map((m,i)=>outputSlots[i].map(at=>Buffer.from(m.HEAPU8.slice(at,at+2)).toString('hex')));assert.deepEqual(cells[0],cells[1],name+' ALL four native coordxy output cells (8 bytes)');}compare(name);return result;}
reset();fill(L.STONE);action('iswall',[0,0]);action('iswall_or_stone',[0,0]);action('is_solid',[0,0]);
for(const typ of [L.STONE,L.SDOOR,L.STAIRS,L.ICE,L.FOUNTAIN,L.SINK,L.LAVAPOOL]){map(4,5,typ);action('set_levltyp',[4,5,L.AIR]);action('set_levltyp_lit',[4,5,L.ROOM,-1]);}
for(let n=1;n<=16;n++){reset();seed(n);setter(m=>set(m,addr(m,field(m,'svl','instance_globals_saved_l','level'),'dlevel_t','flags'),'levelflags','corrmaze',n%2));action('create_maze',[n%5+1,(n*3)%5+1,n%2]);action('mazexy',m=>[ptr(m,0)]);action('bound_digging');action('wallification',[1,0,79,20]);}
console.log('PASS initial MKMAZE',checks,'checks',covered.size,'functions');
reset();fill(L.STONE);setter(m=>{const p=Number(m._probe_scratch());new Int32Array(m.HEAPU8.buffer,p,9).set([1,1,1,1,0,1,1,1,1]);});
action('extend_spine',m=>[Number(m._probe_scratch()),1,0,1]);
action('okay',[4,4,2]);action('maze0xy',m=>[ptr(m,0)]);action('maze_inbounds',[3,3]);
for(let n=0;n<8;n++){reset();for(let x=0;x<80;x++)for(let y=0;y<21;y++)map(x,y,[L.STONE,L.HWALL,L.VWALL,L.ROOM,L.SDOOR,L.WATER,L.IRONBARS][(x*17+y*11+n)%7],(x+y)%4);action('wall_cleanup',[1,0,79,20]);action('fix_wall_spines',[1,0,79,20]);}
reset();fill(L.STONE);action('walkfrom',[3,3,L.CORR]);action('maze_remove_deadends',[L.CORR]);action('get_level_extends',m=>{const p=Number(m._probe_scratch());return[p,p+2,p+4,p+6];});
reset();fill(L.ROOM);action('is_exclusion_zone',[L.LR_TELE,5,5]);setter(m=>m._probe_exclusion(L.LR_TELE,3,3,8,8));action('is_exclusion_zone',[L.LR_DOWNTELE,5,5]);action('is_exclusion_zone',[L.LR_PORTAL,5,5]);action('bad_location',[5,5,3,3,8,8]);
for(const type of [L.LR_TELE,L.LR_UPTELE,L.LR_DOWNTELE,L.LR_PORTAL,L.LR_UPSTAIR,L.LR_DOWNSTAIR,L.LR_BRANCH]){reset();fill(L.ROOM);action('put_lregion_here',m=>[5,5,0,0,0,0,type,1,ptr(m,1)]);action('place_lregion',m=>[4,4,9,9,0,0,0,0,type,ptr(m,1)]);}
reset();fill(L.STONE);action('place_lregion',m=>[3,3,5,5,0,0,0,0,L.LR_TELE,ptr(m,1)]);
for(const type of [L.LR_BRANCH,L.LR_PORTAL,L.LR_UPSTAIR,L.LR_DOWNSTAIR,L.LR_TELE,L.LR_UPTELE,L.LR_DOWNTELE]){reset();fill(L.ROOM);setter(m=>m._probe_region(type,6,7));action('fixup_special');}
reset();fill(L.ROOM);for(let x=8;x<=70;x++)for(let y=3;y<=17;y++)map(x,y,L.HWALL,8<<2);action('baalz_fixup');
reset();fill(L.ROOM);setter(m=>{m._probe_attach(2,5,5);}); // replaced below with explicit native string contents
setter(m=>{const p=ptr(m,2);m.stringToUTF8('minetn-1',p,256);});action('check_ransacked',m=>[ptr(m,2)]);
action('migrate_orc',m=>[ptr(m,5),1]);action('migrate_orc',m=>[ptr(m,5),0x1000000000000001n]);action('shiny_orc_stuff',m=>[ptr(m,5)]);action('migr_booty_item',m=>[L.SLIME_MOLD,ptr(m,2)]);action('stolen_booty');
reset();fill(L.ROOM);action('pick_vibrasquare_location');action('populate_maze');
for(let n=20;n<24;n++){reset();seed(n);setter(m=>m.stringToUTF8('',ptr(m,2),256));action('makemaz',m=>[ptr(m,2)]);}
// Actual nested Snprintf RNG paths retain closing-line recorder attribution.
for(const mode of [0,1,2]){reset();option(6,1);if(mode===2)option(0,1);setter(m=>{m._probe_special(5);m.stringToUTF8(mode===0?'test':'',ptr(m,2),256);if(mode){const dungeons=field(m,'svd','instance_globals_saved_d','dungeons');m.stringToUTF8('test',addr(m,dungeons,'dungeon','proto'),20);}});action('makemaz',m=>[ptr(m,2)]);}
reset();fill(L.LAVAPOOL);action('fumaroles');action('mkportal',[5,5,0,4]);
for(const air of [0,1]){
 reset();fill(air?L.AIR:L.WATER);setter(m=>{m._probe_plane(air);m._probe_attach(3,40,10);});action('setup_waterlevel');action('set_wportal');
 const first=m=>Number(get(m,global(m,'svb'),'instance_globals_saved_b','bbubbles'));
 setter(m=>{const p=first(m),x=Number(BigInt.asIntN(16,get(m,p,'bubble','x'))),y=Number(BigInt.asIntN(16,get(m,p,'bubble','y')));m._probe_attach(1,x,y);m._probe_attach(2,x,y);m._probe_attach(0,x,y);});
 for(let n=0;n<5;n++){action('movebubbles');setter(m=>m._probe_hero(40,10,n%3-1,(n+1)%3-1));action('maybe_adjust_hero_bubble');action('water_friction');}
 action('mv_bubble',m=>[first(m),-5,8,0]);action('mk_bubble',[10,10,5]);
 action('save_waterlevel',m=>[m._probe_nhfile(2)]);action('unsetup_waterlevel');setter(m=>m._probe_rewind());action('restore_waterlevel',m=>[m._probe_nhfile(0)]);action('save_waterlevel',m=>[m._probe_nhfile(4)]);
}
assert.equal(covered.size,44,[...names.filter(n=>!covered.has(n))].join(','));
console.log('PASS baseline MKMAZE',checks,'state/RNG/full-trace comparisons; all',covered.size,'configured functions; full 80x21 maps and controlled serializer bytes.');

// Formal narrowing, signed/unsigned 64-bit object quantity, all error frames.
reset();fill(L.ROOM);action('set_levltyp',[65540,65541,257]);action('set_levltyp_lit',[-65532,-65531,0x101,-257]);
setter(m=>{m._probe_quantity(0x20000000000001n);m.stringToUTF8('wide gang',ptr(m,2),256);});action('migr_booty_item',m=>[L.SLIME_MOLD,ptr(m,2)]);
reset();action('fix_wall_spines',[-1,0,80,21]);action('okay',[3,3,9]);
// A scalar equal to a native address is preserved verbatim, never normalized.
reset();setter(m=>m._probe_attach(1,5,5));
const scalarSnapshots=mods.map(m=>{const p=ptr(m,4);set(m,p,'obj','quan',BigInt(p));const snap=rawRecord(m,p,'obj'),at=addr(m,p,'obj','quan')-p;assert.equal(snap.bytes.slice(at*2,(at+8)*2),Buffer.from(m.HEAPU8.slice(p+at,p+at+8)).toString('hex'));assert.ok(!snap.pointers.some(([name])=>name==='quan'));return snap;});
set(hybrid,ptr(hybrid,4),'obj','quan',BigInt(ptr(hybrid,4))+8n);assert.throws(()=>assert.deepEqual(rawRecord(hybrid,ptr(hybrid,4),'obj'),scalarSnapshots[0]));
// Independent Module, real growth in a dependency, and C→JS cross-Module reentry.
const third=await hybridFactory();third._probe_reset();ref._probe_reset();let reentered=false;
third.nethackPorted={mkmaze(services,name,...args){const original=services.rn2;services.rn2=n=>{if(name==='create_maze'&&!reentered){reentered=true;const prior=hybrid.stackSave();hybrid._probe_action(names.indexOf('iswall'),0n,0n,0n,0n,0n,0n,0n,0n,0n,0n);assert.equal(hybrid.stackSave(),prior);const old=third.HEAPU8.buffer;third._malloc(50000000n);assert.notEqual(third.HEAPU8.buffer,old);}return original(n);};return callMkmaze(services,name,...args);}};
for(const m of [ref,third]){m._probe_seed(137);const sp=m.stackSave();m._probe_action(names.indexOf('create_maze'),1n,1n,1n,0n,0n,0n,0n,0n,0n,0n);assert.equal(m.stackSave(),sp);}
assert.ok(reentered);assert.deepEqual(snapshot(third),snapshot(ref),'new Module with real growth and cross-Module reentry');
console.log('PASS MKMAZE final',checks,'comparisons; 44 functions, exact map/RNG/full traces, 64-bit/narrowing, typed-pointer scalar witness, real growth/reentry/Module isolation and stack restoration. Native/full-game/public pending.');

// Asymmetric map extents force both struct rm* += ROWNO scans to reach
// a distant column. Compare every native output byte, then all packed rm bytes.
reset();fill(L.STONE);for(let x=20;x<=25;x++)for(let y=8;y<=12;y++)map(x,y,L.ROOM);for(let x=50;x<=60;x++)for(let y=3;y<=17;y++)map(x,y,L.ROOM);
action('get_level_extends',m=>{const p=Number(m._probe_scratch());return[p,p+2,p+4,p+6];});
for(const m of mods){const p=Number(m._probe_scratch());assert.deepEqual([...new Int16Array(m.HEAPU8.buffer,p,4)],[19,2,61,18]);assert.equal(Buffer.from(m.HEAPU8.slice(p,p+8)).toString('hex'),'130002003d001200');}
action('bound_digging');console.log('PASS expanded proposed MKMAZE',checks,'comparisons including ALL8 native extent output bytes and asymmetric bound-map regression');
