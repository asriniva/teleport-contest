// Actual configured memory64 C vs imported JS; controlled world/Lua/serializer only.
import assert from 'node:assert/strict';
import{readFileSync,writeFileSync}from'node:fs';
import refFactory from'../.cache/dungeon-first-pass/dungeon-reference.mjs';
import hybridFactory from'../.cache/dungeon-first-pass/dungeon-hybrid.mjs';
import{callDungeon}from'../js/ported/dungeon-runtime.js';
const schema=JSON.parse(readFileSync(new URL('../nethack-c/wasm/tu-fragments/dungeon-schema.json',import.meta.url))),functions=JSON.parse(readFileSync(new URL('../nethack-c/wasm/tu-fragments/dungeon-source-metadata.json',import.meta.url))).functions,names=functions.map(f=>f.name),kinds=Object.keys(schema.schema),covered=new Set();
const serializerTypes=JSON.parse(readFileSync(new URL('../.cache/dungeon-first-pass/serializer-types.json',import.meta.url)));
const output=[[],[]],ref=await refFactory({print:s=>output[0].push(['out',s]),printErr:s=>output[0].push(['err',s])}),hybrid=await hybridFactory({print:s=>output[1].push(['out',s]),printErr:s=>output[1].push(['err',s])});hybrid.nethackPorted={dungeon:callDungeon};const mods=[ref,hybrid];
const L=Object.fromEntries(schema.layoutKeys.map((k,i)=>[k,Number(ref._teleport_dungeon_layout(i))]));
for(let i=0;i<schema.layoutKeys.length;i++)assert.equal(ref._teleport_dungeon_layout(i),hybrid._teleport_dungeon_layout(i));
const global=(m,n)=>Number(m._teleport_dungeon_global(schema.globals.findIndex(g=>g.name===n))),ptr=(m,i)=>Number(m._probe_pointer(i));
const fieldIndex=(k,f)=>schema.schema[k].fields.findIndex(x=>x.name===f);
const addr=(m,p,k,f)=>Number(m._teleport_dungeon_address(kinds.indexOf(k),BigInt(p),fieldIndex(k,f)));
const get=(m,p,k,f)=>m._teleport_dungeon_read(kinds.indexOf(k),BigInt(p),fieldIndex(k,f));
const set=(m,p,k,f,v)=>m._teleport_dungeon_write(kinds.indexOf(k),BigInt(p),fieldIndex(k,f),BigInt.asUintN(64,BigInt(v)));
const root=(m,n,k,f)=>addr(m,global(m,n),k,f),text=(m,s,p=ptr(m,1))=>(m.stringToUTF8(s,p,4096),p);
const setter=fn=>mods.forEach(fn),option=(i,v)=>setter(m=>m._probe_option(i,v)),seed=n=>setter(m=>m._probe_seed(n));
const typeKey=t=>kinds.find(k=>schema.schema[k].ctype.replace(/\b(?:const|volatile)\b/g,'').trim()===t)??(schema.schema[t.replace(/^(?:struct|union) /,'')]?t.replace(/^(?:struct|union) /,''):null);
const sizeOf=t=>{const a=t.match(/^(.*?)\[(\d+)\](.*)$/);if(a)return+a[2]*sizeOf(a[1]+a[3]);if(t.includes('*'))return 8;if(/^(?:unsigned |signed )?char$/.test(t))return 1;if(/^(?:unsigned )?short$/.test(t))return 2;if(/^(?:unsigned )?(?:int|enum \w+)$/.test(t))return 4;if(/^(?:unsigned )?long(?: long)?$/.test(t))return 8;return L['size:'+t]??L['size:'+schema.schema[typeKey(t)]?.ctype];};
const regionNames=['scratch','text','levels','lua','serializer','nhfile','stairs','graves','monsters','species','input'];
const knownRegions=m=>[...schema.globals.filter(g=>g.name!=='stderr').map(g=>({name:g.name,p:global(m,g.name),size:Number(m._probe_global_size(schema.globals.indexOf(g)))})),...regionNames.map((name,i)=>({name,p:ptr(m,i),size:Number(m._probe_region_size(i))})),...Array.from({length:m._probe_count()},(_,i)=>({name:'allocation'+i,p:Number(m._probe_alloc_pointer(i)),size:Number(m._probe_alloc_size(i)),live:Boolean(m._probe_alloc_live(i))}))];
// Read unknown pointer values as uint64 before conversion; only typed selected
// pointers into known exact regions are canonicalized. Unknown bytes stay raw.
const pointerID=(m,value)=>{const v=BigInt(value);if(v===0n)return'0';const r=knownRegions(m).find(r=>v>=BigInt(r.p)&&v<BigInt(r.p+r.size));return r?r.name+'+'+(v-BigInt(r.p)):'UNKNOWN:'+v;};
let scratchTypes=[];const returnedTypes=new Map(mods.map(m=>[m,[]]));
// Freed allocation bytes belong to the native allocator after their lifetime.
// Compare every live allocation byte; retain exact allocation lifetime metadata.
const rawRegions=m=>{
 const rs=knownRegions(m),regions=rs.filter(r=>r.live!==false&&!['cg','nul_glyphinfo','shtypes','vowels','windowprocs'].includes(r.name)).map(r=>({...r,bytes:m.HEAPU8.slice(r.p,r.p+r.size),pointers:[]}));const visited=new Set();
 const visit=(at,t)=>{if(t.startsWith('union '))return;const a=t.match(/^(.*?)\[(\d+)\](.*)$/);if(a){const e=a[1]+a[3],step=sizeOf(e);if(!step)return;for(let i=0;i<+a[2];i++)visit(at+i*step,e);return;}
  if(t.includes('*')){const v=new DataView(m.HEAPU8.buffer).getBigUint64(at,true),id=pointerID(m,v),r=regions.find(r=>at>=r.p&&at+8<=r.p+r.size);if(r&&!id.startsWith('UNKNOWN:')){r.pointers.push([at-r.p,id]);r.bytes.fill(0,at-r.p,at-r.p+8);}if(v&&v<=BigInt(Number.MAX_SAFE_INTEGER)){const pointee=t.replace(/\s*\*\s*$/,'').trim(),key=typeKey(pointee);if(key&&rs.some(r=>v>=BigInt(r.p)&&v+BigInt(sizeOf(pointee)??0)<=BigInt(r.p+r.size)))visit(Number(v),pointee);}return;}
  const key=typeKey(t);if(!key||visited.has(at+':'+key))return;visited.add(at+':'+key);for(const f of schema.schema[key].fields){if(f.bit)continue;const ft=f.canonical;if(ft.includes('*')||ft.includes('[')||typeKey(ft))visit(addr(m,at,key,f.name),ft);}
 };
 for(const g of schema.globals)if(!['stderr','windowprocs','cg','nul_glyphinfo','shtypes','vowels'].includes(g.name))visit(global(m,g.name),g.canonical);
 for(const [offset,t]of scratchTypes)visit(ptr(m,0)+offset,t);
 for(const [at,t]of (returnedTypes.get(m)??[]))if(knownRegions(m).some(r=>at>=r.p&&at+sizeOf(t)<=r.p+r.size))visit(at,t);
 for(let i=0;i<m._probe_event_count();i++){const t=serializerTypes[m._probe_event_type(i)],start=Number(m._probe_event_at(i)),extent=Number(m._probe_event_size(i)),step=sizeOf(t);if(step)for(let off=0;off<extent;off+=step)visit(ptr(m,4)+start+off,t);}
 // Levels/stairs/graves/monster/species arrays are explicit compiler-typed regions.
 for(const [i,t,count]of [[2,'struct d_level',8],[6,'struct stairway',8],[7,'struct cemetery',8],[8,'struct monst',8],[9,'struct permonst',8]]){const n=sizeOf(t);if(n)for(let j=0;j<count;j++)visit(ptr(m,i)+j*n,t);}
 return regions.map(r=>({name:r.name,bytes:Buffer.from(r.bytes).toString('hex'),pointers:r.pointers.sort((a,b)=>a[0]-b[0])}));
};
const snapshot=m=>({regions:rawRegions(m),trace:m.UTF8ToString(Number(m._probe_trace())),draws:m._probe_draws(),error:m._probe_error(),errno:m._probe_errno(),luaTop:m._probe_luatop(),serialLength:Number(m._probe_serial_length()),allocationLive:Array.from({length:m._probe_count()},(_,i)=>m._probe_alloc_live(i))});
let checks=0;
function reset(){setter(m=>m._probe_reset());scratchTypes=[];returnedTypes.forEach(a=>a.length=0);output.forEach(a=>a.length=0);}
function compare(label){const a=snapshot(ref),b=snapshot(hybrid);try{assert.deepEqual(b,a,label);assert.deepEqual(output[1],output[0],label+' native stdout/stderr');checks++;}catch(e){writeFileSync(new URL('../.cache/dungeon-first-pass/mismatch.json',import.meta.url),JSON.stringify({label,ref:a,hybrid:b},null,2));throw e;}}
function action(name,args=[]){covered.add(name);const results=mods.map((m,i)=>{const a=typeof args==='function'?args(m,i):args,sp=m.stackSave();try{const result=m._probe_action(names.indexOf(name),...Array.from({length:10},(_,j)=>BigInt(a[j]??0)));const rt=functions[names.indexOf(name)].type.qualType.split('(')[0];const returnedRecord=rt.replace(/\bconst\b/g,'').replace(/\s*\*\s*$/,'').trim();if(result&&rt.includes('*')&&typeKey(returnedRecord)&&result<=BigInt(Number.MAX_SAFE_INTEGER))returnedTypes.get(m).push([Number(result),returnedRecord]);return rt.includes('*')?(rt.includes('char')?(result?m.UTF8ToString(Number(result)):null):pointerID(m,result)):result;}finally{assert.equal(m.stackSave(),sp,name+' native stack cleanup');}});assert.equal(results[0],results[1],name+' result');compare(name);return results;}
reset();action('dumpit');
for(const name of ['dunlev','dunlevs_in_dungeon','ledger_no','depth','Is_special','Is_branchlev','builds_up','Is_botlevel','Can_dig_down','Can_fall_thru','has_ceiling','avoid_ceiling','In_quest','In_mines','In_V_tower','On_W_tower_level','In_hell','single_level_branch','Invocation_lev','chr_u_on_lvl'])action(name,m=>[ptr(m,2)]);
for(const name of ['deepest_lev_reached','maxledgerno','level_difficulty','earth_sense','init_castle_tune'])action(name);
action('on_level',m=>[ptr(m,2),ptr(m,2)+4]);for(const n of [1,20,21,40,41,60]){action('ledger_to_dnum',[n]);action('ledger_to_dlev',[n]);}
action('get_level',m=>[ptr(m,2)+12,15]);action('assign_level',m=>[ptr(m,2)+16,ptr(m,2)]);for(const n of [-5,0,5])action('assign_rnd_level',m=>[ptr(m,2)+20,ptr(m,2),n]);for(const n of [0,20,100])action('induced_align',[n]);
for(const n of ['Can_rise_up','In_W_tower'])action(n,m=>[40,10,ptr(m,2)]);for(const n of ['ceiling','surface','update_lastseentyp','update_mapseen_for'])action(n,[40,10]);
for(const n of ['find_hell','unreachable_level'])action(n,m=>[ptr(m,2),0]);
for(const n of ['dname_to_dnum','find_level','dungeon_branch','at_dgn_entrance','lev_by_name','find_mapseen_by_str'])action(n,m=>[text(m,'Dungeon 0')]);
for(const n of ['next_level','prev_level','goto_hell']){reset();action(n,[0,0]);}
reset();action('u_on_newpos',[42,11]);action('u_on_newpos',[-1,11]);action('u_on_rndspot',[1]);
for(const n of [-1,0,1,2,3,4])action('br_string',[n]);for(const n of [0,1,2,5])action('seen_string',m=>[n,text(m,'fountain')]);for(const n of [0,1,2,3])action('shop_string',[n]);for(const n of [-1,0,1,4,8])action('endgamelevelname',m=>[ptr(m,1),n]);
console.log('PASS DUNGEON draft',checks,'comparisons',covered.size,'configured entry points; remaining fixture cases in development');
const PD=0,MAP=4096,OUT=5000,STAT=6000,SL=8192,BR=12288,MS=16384,CHOICE=20480;
const rec=(m,off)=>ptr(m,0)+off;
const scalar=(m,off,t,v)=>{const p=rec(m,off),dv=new DataView(m.HEAPU8.buffer);if(t===8)dv.setBigInt64(p,BigInt(v),true);else if(t===4)dv.setInt32(p,v,true);else if(t===2)dv.setInt16(p,v,true);else dv.setInt8(p,v);};
const ownedString=(m,value)=>{const n=Buffer.byteLength(value)+1,p=Number(m._probe_alloc(n));m.stringToUTF8(value,p,n);return p;};
function protoSetup(){scratchTypes=[[PD,'struct proto_dungeon'],[SL,'struct s_level'],[SL+sizeOf('struct s_level'),'struct s_level'],[BR,'struct branch'],[MS,'struct mapseen'],[CHOICE,'struct lchoice']];setter(m=>{
 const p=rec(m,PD);set(m,p,'proto_dungeon','n_levs',2);set(m,p,'proto_dungeon','n_brs',1);
 for(let i=0;i<2;i++){const td=addr(m,p,'proto_dungeon','tmpdungeon')+i*sizeOf('struct tmpdungeon');set(m,td,'tmpdungeon','name',ownedString(m,'Dungeon '+i));set(m,td,'tmpdungeon','protoname',ownedString(m,'fixture'));set(m,td,'tmpdungeon','branches',i?0:1);const lv=rec(m,SL)+i*sizeOf('struct s_level'),tl=addr(m,p,'proto_dungeon','tmplevel')+i*sizeOf('struct tmplevel');set(m,tl,'tmplevel','name',ownedString(m,i?'castle':'oracle'));set(m,tl,'tmplevel','chain',-1);set(m,tl,'tmplevel','chance',100);const couple=addr(m,tl,'tmplevel','lev');set(m,couple,'couple','base',5+i*3);set(m,couple,'couple','rand',3);const dl=addr(m,lv,'s_level','dlevel');set(m,dl,'d_level','dnum',0);set(m,dl,'d_level','dlevel',5+i*3);m.stringToUTF8(i?'castle':'oracle',addr(m,lv,'s_level','proto'),15);new DataView(m.HEAPU8.buffer).setBigUint64(addr(m,p,'proto_dungeon','final_lev')+i*8,BigInt(lv),true);}
});}
function branchProto(){protoSetup();setter(m=>{const p=rec(m,PD),b=addr(m,p,'proto_dungeon','tmpbranch');set(m,b,'tmpbranch','name',ownedString(m,'Dungeon 1'));set(m,b,'tmpbranch','chain',-1);set(m,b,'tmpbranch','type',0);const lev=addr(m,b,'tmpbranch','lev');set(m,lev,'couple','base',5);set(m,lev,'couple','rand',3);});}
reset();branchProto();for(const n of ['find_branch','parent_dnum','parent_dlevel'])action(n,m=>[text(m,'Dungeon 1'),rec(m,PD)]);
for(const base of [1,-2])for(const rand of [-1,0,3])action('level_range',m=>[0,base,rand,-1,rec(m,PD),rec(m,OUT)]);
for(const t of [0,1,2,3,99]){setter(m=>set(m,addr(m,rec(m,PD),'proto_dungeon','tmpbranch'),'tmpbranch','type',t));action('correct_branch_type',m=>[addr(m,rec(m,PD),'proto_dungeon','tmpbranch')]);}
reset();branchProto();action('add_branch',m=>[1,2,rec(m,PD)]);action('init_dungeon_set_depth',m=>[rec(m,PD),1]);
reset();branchProto();action('possible_places',m=>[0,rec(m,MAP),rec(m,PD)]);action('pick_level',m=>[rec(m,MAP),0]);action('place_level',m=>[0,rec(m,PD)]);action('init_level',m=>[0,0,rec(m,PD)]);
for(const entry of [-40,-2,0,2,80]){setter(m=>set(m,addr(m,rec(m,PD),'proto_dungeon','tmpdungeon'),'tmpdungeon','entry_lev',entry));action('init_dungeon_set_entry',m=>[rec(m,PD),0]);}
reset();protoSetup();action('add_level',m=>[rec(m,SL)]);action('fixup_level_locations');action('unplaced_floater',m=>[root(m,'svd','instance_globals_saved_d','dungeons')]);
reset();scratchTypes=[[BR,'struct branch']];setter(m=>{const b=rec(m,BR),e1=addr(m,b,'branch','end1'),e2=addr(m,b,'branch','end2');set(m,e1,'d_level','dlevel',5);set(m,e2,'d_level','dnum',1);set(m,e2,'d_level','dlevel',2);});action('insert_branch',m=>[rec(m,BR),0]);action('insert_branch',m=>[rec(m,BR),1]);action('br_string2',m=>[rec(m,BR)]);
reset();branchProto();action('free_proto_dungeon',m=>[rec(m,PD)]);
// Real native callback pointer results: positive and null stair branches.
for(const present of [0,1])for(const name of ['next_level','prev_level']){reset();option(15,present);setter(m=>{const p=ptr(m,6),lev=addr(m,p,'stairway','tolev');set(m,lev,'d_level','dnum',1);set(m,lev,'d_level','dlevel',7);});action(name,[1]);}
for(const present of [0,1]){reset();option(16,1);option(15,present);action('u_on_rndspot',[1]);}
for(const flags of [0,1,2]){reset();option(5,flags);setter(m=>m._probe_lua(2,1));action('get_dgn_flags',m=>[ptr(m,3)]);setter(m=>m._probe_lua(2,1));option(7,flags);action('get_dgn_align',m=>[ptr(m,3)]);}
reset();scratchTypes=[[PD,'struct proto_dungeon']];setter(m=>m._probe_lua(3,1));action('init_dungeon_levels',m=>[ptr(m,3),rec(m,PD),0]);option(4,1);setter(m=>m._probe_lua(4,1));action('init_dungeon_branches',m=>[ptr(m,3),rec(m,PD),0]);
reset();scratchTypes=[[PD,'struct proto_dungeon']];option(28,1);setter(m=>m._probe_lua(2,1));action('init_dungeon_dungeons',m=>[ptr(m,3),rec(m,PD),0]);
for(const failure of [1,2]){reset();option(failure,1);action('init_dungeons');}
reset();option(28,1);action('init_dungeons');
console.log('PASS DUNGEON placement/Lua draft',checks,'comparisons',covered.size,'configured entry points');
reset();scratchTypes=[[CHOICE,'struct lchoice']];action('tport_menu',m=>[7,text(m,'Test level'),rec(m,CHOICE),ptr(m,2),0]);action('print_branch',m=>[7,0,1,20,0,rec(m,CHOICE)]);action('print_dungeon',m=>[0,rec(m,OUT),rec(m,OUT+2)]);
function currentMapseen(m){return Number(get(m,global(m,'svm'),'instance_globals_saved_m','mapseenchn'));}
reset();action('init_mapseen',m=>[ptr(m,2)]);action('init_mapseen',m=>[ptr(m,2)+4]);action('init_mapseen',m=>[ptr(m,2)]);action('find_mapseen',m=>[ptr(m,2)]);action('interest_mapseen',m=>[currentMapseen(m)]);action('get_annotation',m=>[ptr(m,2)]);action('query_annotation',m=>[ptr(m,2)]);action('find_mapseen_by_str',m=>[text(m,'annotation')]);action('print_level_annotation');action('donamelevel');action('query_annotation',m=>[ptr(m,2)+4]);
for(const n of ['print_mapseen','tunesuffix'])action(n,m=>n==='print_mapseen'?[7,currentMapseen(m),0,0,1]:[currentMapseen(m),ptr(m,1),256]);
action('overview_stats',m=>[7,text(m,'%s: %ld objects, %ld bytes'),rec(m,STAT),rec(m,STAT+8)]);
for(const typ of [L.FOUNTAIN,L.SINK,L.ALTAR,L.THRONE,L.GRAVE,L.TREE,L.POOL,L.LAVAPOOL,L.ICE]){setter(m=>m._probe_map(12,8,typ,255));for(let i=0;i<5;i++)action('count_feat_lastseentyp',m=>[currentMapseen(m),12,8]);}
action('recalc_mapseen');action('room_discovered',[0]);action('mapseen_temple',m=>[ptr(m,8)]);action('recbranch_mapseen',m=>[ptr(m,2),ptr(m,2)+4]);
scalar(ref,OUT,4,-1);scalar(hybrid,OUT,4,-1);action('traverse_mapseenchn',m=>[0,7,1,0,rec(m,OUT)]);action('show_overview',[0,0]);action('dooverview');action('remdun_mapseen',[1]);action('rm_mapseen',[3]);
reset();action('init_mapseen',m=>[ptr(m,2)]);action('query_annotation',m=>[ptr(m,2)]);action('save_mapseen',m=>[ptr(m,5),currentMapseen(m)]);setter(m=>m._probe_serial_rewind());action('load_mapseen',m=>[ptr(m,5)]);
reset();action('init_mapseen',m=>[ptr(m,2)]);action('save_dungeon',m=>[ptr(m,5),1,0]);setter(m=>m._probe_serial_rewind());action('restore_dungeon',m=>[ptr(m,5)]);
reset();action('save_exclusions',m=>[ptr(m,5)]);setter(m=>m._probe_serial_rewind());action('load_exclusions',m=>[ptr(m,5)]);action('free_exclusions');
console.log('PASS DUNGEON baseline',checks,'comparisons',covered.size,'functions; missing:',names.filter(n=>!covered.has(n)));
assert.equal(covered.size,110,'all actual configured entry points exercised');
// Positive/null attack-pointer result paths use native struct attack storage.
for(const present of [0,1]){reset();option(18,present);setter(m=>{set(m,global(m,'u'),'you','uswallow',1);set(m,global(m,'u'),'you','ustuck',ptr(m,8));set(m,ptr(m,9),'permonst','mflags1',262144n);});action('surface',[40,10]);}
// Shop/priest predicates see genuine native monst pointers and native room ids.
for(const temple of [0,1])for(const present of [0,1]){reset();action('init_mapseen',m=>[ptr(m,2)]);option(temple?25:23,present);option(temple?26:24,1);setter(m=>{const rooms=addr(m,global(m,'u'),'you','urooms');m.HEAPU8[rooms]=3;m.HEAPU8[rooms+1]=0;set(m,root(m,'svr','instance_globals_saved_r','rooms'),'mkroom','rtype',temple?L.TEMPLE:L.SHOPBASE);});action('recalc_mapseen');}
// Full 184-byte cemetery aggregate clone includes every scalar/padding byte.
reset();action('init_mapseen',m=>[ptr(m,2)]);setter(m=>{const p=ptr(m,7),n=sizeOf('struct cemetery');m.HEAPU8.fill(0xA5,p,p+2*n);for(let i=0;i<2;i++){const g=p+i*n;set(m,g,'cemetery','next',i?0:p+n);set(m,g,'cemetery','frpx',40+i);set(m,g,'cemetery','frpy',10);set(m,g,'cemetery','bonesknown',0);m.stringToUTF8('fixture hero '+i,addr(m,g,'cemetery','who'),49);m.stringToUTF8('fixture fate',addr(m,g,'cemetery','how'),101);}set(m,root(m,'svl','instance_globals_saved_l','level'),'dlevel_t','bonesinfo',p);});action('recalc_mapseen');action('save_mapseen',m=>[ptr(m,5),currentMapseen(m)]);setter(m=>m._probe_serial_rewind());action('load_mapseen',m=>[ptr(m,5)]);
// Wide native long accumulation; no safe-integer conversion of source integers.
setter(m=>{scalar(m,STAT,8,0x20000000000001n);scalar(m,STAT+8,8,0x40000000000003n);});action('overview_stats',m=>[7,text(m,'%s: %ld %ld'),rec(m,STAT),rec(m,STAT+8)]);
// Raw scalar/address and unknown typed pointer64 witnesses in observed live data.
const beforeWitness=mods.map(snapshot);setter(m=>scalar(m,STAT,8,BigInt(ptr(m,0))));const a0=snapshot(ref),b0=snapshot(hybrid);assert.notEqual(ptr(ref,0),ptr(hybrid,0),'distinct native scalar address witnesses');assert.throws(()=>assert.deepEqual(b0,a0));reset();scratchTypes=[[MS,'struct mapseen']];setter(m=>set(m,rec(m,MS),'mapseen','next',0x20000000000001n));const exact=snapshot(ref);assert.equal(new DataView(ref.HEAPU8.buffer).getBigUint64(addr(ref,rec(ref,MS),'mapseen','next'),true),0x20000000000001n);assert.deepEqual(snapshot(hybrid),exact);set(hybrid,rec(hybrid,MS),'mapseen','next',0x20000000000002n);assert.throws(()=>assert.deepEqual(snapshot(hybrid),exact));
reset();action('u_on_newpos',[65578,-65525]);reset();option(0,1);action('dumpit');
console.log('PASS DUNGEON extended',checks,'comparisons; positive/null typed native returns, cemetery fullcopy/save bytes, wide long/raw scalar/unknownpointer64 witnesses, narrowing/debug native output.');
// Success and exhausted backtracking: each recursive map[33] has native lifetime.
for(const [count,width]of [[3,2],[6,8],[8,10]]){
 reset();scratchTypes=[[PD,'struct proto_dungeon']];setter(m=>{const p=rec(m,PD);set(m,p,'proto_dungeon','n_levs',count);for(let i=0;i<count;i++){const t=addr(m,p,'proto_dungeon','tmplevel')+i*sizeOf('struct tmplevel');set(m,t,'tmplevel','name',ownedString(m,'level'+i));set(m,t,'tmplevel','chance',100);set(m,t,'tmplevel','chain',-1);const c=addr(m,t,'tmplevel','lev');set(m,c,'couple','base',1);set(m,c,'couple','rand',width);}});
 for(let i=0;i<count;i++)action('init_level',m=>[0,i,rec(m,PD)]);const answer=action('place_level',m=>[0,rec(m,PD)]);assert.equal(answer[0],count>width?0n:1n);
}
// Positive exclusion chain, exact coordinate buffers and original LIFO restore.
reset();setter(m=>{const p=Number(m._probe_alloc(sizeOf('struct exclusion_zone'))),q=Number(m._probe_alloc(sizeOf('struct exclusion_zone')));for(const [i,at]of[p,q].entries()){set(m,at,'exclusion_zone','next',i?0:q);set(m,at,'exclusion_zone','zonetype',i+1);for(const[f,v]of Object.entries({lx:3+i,ly:4,hx:12,hy:9}))set(m,at,'exclusion_zone',f,v);}set(m,global(m,'sve'),'instance_globals_saved_e','exclusion_zones',p);set(m,ptr(m,5),'nh_file','mode',2);});action('save_exclusions',m=>[ptr(m,5)]);action('free_exclusions');setter(m=>m._probe_serial_rewind());action('load_exclusions',m=>[ptr(m,5)]);action('free_exclusions');
// Independent Modules, real growth in a true native dependency boundary,
// actual native C -> imported JS reentry and persistent per-Module branch ids.
const fresh=await refFactory(),third=await hybridFactory();for(const m of[fresh,third]){m._probe_reset();returnedTypes.set(m,[]);}let reentered=false;
third.nethackPorted={dungeon(services,name,...args){const original=services.rn2;services.rn2=n=>{if(!reentered){reentered=true;const old=third.HEAPU8.buffer;third._probe_growth();assert.notEqual(third.HEAPU8.buffer,old);const sp=hybrid.stackSave();hybrid._probe_action(names.indexOf('dunlev'),BigInt(ptr(hybrid,2)),0n,0n,0n,0n,0n,0n,0n,0n,0n);assert.equal(hybrid.stackSave(),sp);}return original(n);};return callDungeon(services,name,...args);}};
for(const m of[fresh,third])m._probe_action(names.indexOf('init_castle_tune'),0n,0n,0n,0n,0n,0n,0n,0n,0n,0n);assert.ok(reentered);scratchTypes=[];assert.deepEqual(snapshot(third),snapshot(fresh),'independent Module/growth/native reentry');
for(const m of[fresh,third]){const pd=rec(m,PD);set(m,pd,'proto_dungeon','n_brs',1);const t=addr(m,pd,'proto_dungeon','tmpdungeon'),b=addr(m,pd,'proto_dungeon','tmpbranch');set(m,t,'tmpdungeon','name',ownedString(m,'Dungeon 0'));set(m,t,'tmpdungeon','branches',1);set(m,t+sizeOf('struct tmpdungeon'),'tmpdungeon','name',ownedString(m,'Dungeon 1'));set(m,b,'tmpbranch','name',ownedString(m,'Dungeon 1'));set(m,b,'tmpbranch','chain',-1);set(m,addr(m,b,'tmpbranch','lev'),'couple','base',5);}
scratchTypes=[[PD,'struct proto_dungeon']];for(let i=0;i<2;i++){for(const m of[fresh,third]){const sp=m.stackSave();m._probe_action(names.indexOf('add_branch'),1n,2n,BigInt(rec(m,PD)),0n,0n,0n,0n,0n,0n,0n);assert.equal(m.stackSave(),sp);const b=Number(get(m,global(m,'svb'),'instance_globals_saved_b','branches'));assert.equal(get(m,b,'branch','id'),BigInt(i));}assert.deepEqual(snapshot(third),snapshot(fresh),'persistent branch id and native ownership');}
console.log('PASS DUNGEON final',checks,'comparisons; all110 configured functions, recursive success/exhaustion, packed maps/serializer bytes, actual typed pointer families,64bit/narrowing,Module ids/growth/native reentry/stack cleanup. Controlled Lua/world only; native/full-game/public pending.');
// Positive const catalogue pointers and null annotation/name fallbacks exercise
// the source's local extern shtypes[] contract, beyond the untended-shop branch.
reset();for(const[offset,expected]of[[0,'store'],[1,'armor'],[2,'scroll shop'],[4,'shop?']])assert.equal(action('shop_string',[L.SHOPBASE+offset])[0],expected);
console.log('PASS DUNGEON FINAL',checks,'comparisons; all110 configured functions with positive/null catalogue pointers; controlled memory64 C-vs-imported-JS only.');
// The native variadic function-pointer selection has two real targets:
// x=0 is inside allocation bounds but invalid as a hero map location.
reset();action('u_on_newpos',[0,10]);
console.log('PASS DUNGEON FINAL COMPLETE',checks,'comparisons; all110 functions and both native panic/impossible dispatch targets.');
// Actual raw-header member alias seam: SURFACE_AT's drawbridgemask is rm.flags.
for(const mask of[0,1,7,31]){reset();setter(m=>{m._probe_map(40,10,L.DRAWBRIDGE_UP,255);set(m,Number(m._probe_grid())+(40*21+10)*sizeOf('struct rm'),'rm','flags',mask);});action('surface',[40,10]);for(const m of mods)assert.ok(m.UTF8ToString(Number(m._probe_trace())).includes('db_under_typ('+mask+')'),'actual alias sends original native flag mask');}
console.log('PASS DUNGEON FROZEN',checks,'comparisons; all110, original raw alias masks, pointer families, recursively placed topology/Lua/serializer ownership, wide and Module/growth/reentry/stack checks. No native/full-game/public claim.');
