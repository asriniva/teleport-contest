if(process.env.TELEPORT_NATIVE_TESTS!=='0')throw Error('SP_LEV has no native reference fixture; Emscripten results cannot be labeled native.');
import assert from 'node:assert/strict';
import{readFile}from'node:fs/promises';import{resolve}from'node:path';import{pathToFileURL}from'node:url';
import{C}from'../js/ported/c-runtime.js';
const core=await import(pathToFileURL(resolve(process.env.SP_LEV_CORE??'js/ported/sp_lev.js')).href);
import{createSpLevEnvironment,initializeSpLev,callSpLev}from'../js/ported/sp_lev-runtime.js';
const dir=resolve(process.env.SP_LEV_PROBE_DIR??'.cache/sp-lev-first-pass'),schema=JSON.parse(await readFile(new URL('../nethack-c/wasm/tu-fragments/sp_lev-schema.json',import.meta.url),'utf8'));
const factory=async mode=>(await import(pathToFileURL(resolve(dir,'sp_lev-'+mode+'.mjs')).href)).default;
const reference=await(await factory('reference'))();
function text(m,p){p=Number(p);if(!p)return null;let e=p;while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.slice(p,e)).toString('utf8');}
function layout(m){const out={};for(let i=0;i<m._probe_layout_count();i++)out[text(m,m._probe_layout_name(i))]=Number(BigInt.asIntN(64,m._probe_layout_value(i)));return out;}
const L=layout(reference),envs=new WeakMap(),rawServices=new WeakMap(),ops=Object.keys(schema.functionTypes),index=n=>ops.indexOf(n);
const runtime={initializeSpLev(s){rawServices.set(s.moduleKey,s);envs.set(s.moduleKey,initializeSpLev(s,L,core));},sp_lev(s,name,...args){rawServices.set(s.moduleKey,s);return callSpLev(s,L,core,name,...args);}};
const hybrid=await(await factory('hybrid'))({nethackPorted:runtime}),modules=[reference,hybrid];
function manual(m){let next=0;const cache=new Map();return{moduleKey:m,heap:()=>m.HEAPU8,global:i=>Number(m._teleport_sp_lev_global(i)),read:(k,a,f)=>m._teleport_sp_lev_read(k,BigInt(a),f),write:(k,a,f,v)=>m._teleport_sp_lev_write(k,BigInt(a),f,v),address:(k,a,f)=>Number(m._teleport_sp_lev_address(k,BigInt(a),f)),literal:s=>{if(cache.has(s))return cache.get(s);const at=Number(m._teleport_sp_lev_literal_storage())+next,n=m.lengthBytesUTF8(s)+1;next+=n;assert.ok(next<=schema.literalBytes);m.stringToUTF8(s,at,n);cache.set(s,at);return at;},functionPointers:Object.fromEntries(Object.keys(schema.functionPointers).map((n,i)=>[n,()=>m._probe_function(i)])),copyRecord:(to,from,n)=>Number(m._teleport_sp_lev_copy(BigInt(to),BigInt(from),BigInt(n))),stackAlloc:n=>Number(m.stackAlloc(n)),stackSave:()=>m.stackSave(),stackRestore:v=>m.stackRestore(v)};}
envs.set(reference,createSpLevEnvironment(manual(reference),L,core));
const pool=(m,k=0,i=0)=>Number(m._probe_pool(k,i));const each=fn=>modules.forEach(m=>fn(m,envs.get(m)));
function field(m,at,k,f,v){const x=envs.get(m).field(at,k,f);if(v!==undefined)x.value=v;return x.value;}
function cell(m,at,t,v){const x=envs.get(m).cell(at,t);if(v!==undefined)x.value=v;return x.value;}
function input(m,s,offset=0){const at=pool(m,0,offset);m.stringToUTF8(s,at,8192-offset);return at;}
function option(k,v){each(m=>m._probe_option(k,BigInt(v)));}
const kinds=new Map(Object.entries(schema.schema).map(([k,v])=>[v.ctype,k]));
function array(t){const dims=[...t.matchAll(/\[(\d+)\]/g)].map(m=>+m[1]);return dims.length?{base:t.replace(/\[\d+\]/g,''),dims}:null;}
function sub(a){return a.dims.length===1?a.base:a.base.includes('(*)')?a.base.replace('(*)','(*'+a.dims.slice(1).map(n=>'['+n+']').join('')+')'):a.base+a.dims.slice(1).map(n=>'['+n+']').join('');}
function size(t){const a=array(t);return a?size(a.base)*a.dims.reduce((x,y)=>x*y,1):t.includes('*')?8:L['size:'+t]??({char:1,'signed char':1,'unsigned char':1,short:2,'unsigned short':2,int:4,'unsigned int':4,long:8,'unsigned long':8,'long long':8,'unsigned long long':8})[t];}
const pools=[[0,'char',32768],[1,'monster',8],[2,'object',8],[3,'struct obj',32],[4,'struct monst',16],[5,'struct mkroom',8],[6,'struct nhcoord',16],[7,'long long',16],[8,'void *',16],[9,'corridor',8],[10,'struct mapfragment',8],[11,'region',8],[12,'lev_init',4],[13,'spltrap',4],[14,'struct _room',4],[15,'room_door',4],[16,'altar',4],[17,'lev_region',4],[18,'terrain',4],[19,'unpacked_coord',4]];
const stringRanges=new WeakMap(modules.map(m=>[m,Array.from({length:m._probe_string_count()},(_,i)=>{const p=BigInt(m._probe_string(i));return[p,p+BigInt(m._probe_string_capacity(i))];})]));
function identity(m,value){const bits=BigInt.asUintN(64,BigInt(value));if(!bits)return{known:true,identity:0};if(bits>BigInt(Number.MAX_SAFE_INTEGER))return{known:false,identity:['raw',bits.toString()]};const p=Number(bits);if(bits===m._probe_lua())return{known:true,identity:['LuaState']};for(const[k,t,n]of pools){const a=pool(m,k),length=size(t)*n;if(length&&p>=a&&p<a+length)return{known:true,identity:['pool',k,p-a]};}for(let i=0;i<m._probe_block_count();i++){const a=Number(m._probe_block(i)),n=Number(m._probe_block_size(i));if(p>=a&&p<a+n)return{known:true,identity:['allocation',i,p-a]};}for(const g of schema.globals){if(g.canonical.endsWith('[]'))continue;const a=envs.get(m)[g.name],n=size(g.canonical);if(n&&p>=a&&p<a+n)return{known:true,identity:[g.name,p-a]};}for(let i=0;i<Object.keys(schema.data).length;i++){const a=Number(m._probe_data(i)),n=size(Object.values(schema.data)[i].type);if(n&&p>=a&&p<a+n)return{known:true,identity:['data',i,p-a]};}for(let i=0;i<Object.keys(schema.functionPointers).length;i++)if(bits===m._probe_function(i))return{known:true,identity:['function',i]};return{known:false,identity:['raw',bits.toString()]};}
function observed(m,at,t){const bits=new DataView(m.HEAPU8.buffer).getBigUint64(at,true),id=identity(m,bits);if(t==='char *'&&bits&&bits<=BigInt(Number.MAX_SAFE_INTEGER)){const a=BigInt(m._teleport_sp_lev_literal_storage()),r=[...stringRanges.get(m),[a,a+BigInt(schema.literalBytes)],[BigInt(pool(m)),BigInt(pool(m))+32768n]].find(([lo,hi])=>bits>=lo&&bits<hi);if(r){const p=Number(bits);let end=p;while(end<Number(r[1])&&m.HEAPU8[end])end++;if(end<Number(r[1]))return{known:true,identity:['string',Buffer.from(m.HEAPU8.slice(p,end)).toString('utf8')]};}}return id;}
function typed(m,at,t){const a=array(t);if(a){const s=sub(a);return Array.from({length:a.dims[0]},(_,i)=>typed(m,at+i*size(s),s));}if(t.includes('*'))return observed(m,at,t).identity;const k=kinds.get(t);if(k){const out={};for(const f of schema.schema[k].fields){const v=envs.get(m).field(at,k,f.name);out[f.name]=f.bit?v.value.toString():typed(m,v.address,f.canonical);}return out;}if(!size(t))throw Error('observer type '+t);return Buffer.from(m.HEAPU8.slice(at,at+size(t))).toString('hex');}
function rawRecord(m,at,k){const n=size(schema.schema[k].ctype),bytes=Buffer.from(m.HEAPU8.slice(at,at+n)),pointers={};function visit(p,t,path){const a=array(t);if(a){const s=sub(a);for(let i=0;i<a.dims[0];i++)visit(p+i*size(s),s,path+'['+i+']');return;}if(t.includes('*')){const v=observed(m,p,t);pointers[path]=v.identity;if(v.known)bytes.fill(0,p-at,p-at+8);return;}const r=kinds.get(t);if(r)for(const f of schema.schema[r].fields)if(!f.bit&&(f.canonical.includes('*')||kinds.has(f.canonical)||array(f.canonical))){if(r==='str_or_len'&&f.name==='len')continue;visit(envs.get(m).field(p,r,f.name).address,f.canonical,path+'.'+f.name);}}visit(at,schema.schema[k].ctype,k);return{bytes:bytes.toString('hex'),pointers};}
let active='',comparisons=0;const called=new Set(),stacks=modules.map(m=>m._probe_stack());
function selectionBytes(m,at,n){const bytes=Buffer.from(m.HEAPU8.slice(at,at+n)),offset=Number(m._probe_selection_map_offset()),v=observed(m,at+offset,'char *');if(v.known)bytes.fill(0,offset,offset+8);return{bytes:bytes.toString('hex'),map:v.identity};}
function snapshot(m){const e=envs.get(m),out={};for(const g of schema.globals){if(g.canonical.endsWith('[]')||['mons','objects','obj_descr','def_monsyms','defsyms'].includes(g.name))continue;const k=kinds.get(g.canonical);out[g.name]=k?rawRecord(m,e[g.name],k):typed(m,e[g.name],g.canonical);}for(const[k,t,n]of pools){if(k===0)continue;const kind=kinds.get(t);out['pool'+k]=Array.from({length:n},(_,i)=>kind?rawRecord(m,pool(m,k,i),kind):typed(m,pool(m,k,i),t));}out.allocations=Array.from({length:m._probe_block_count()},(_,i)=>{const at=Number(m._probe_block(i)),n=Number(m._probe_block_size(i)),live=m._probe_block_live(i),kind=m._probe_block_kind(i);let k=({2:'obj',3:'monst',4:'mapfragment',5:'sp_coder'})[kind];if(at===field(m,e.gc,'instance_globals_c','coder'))k='sp_coder';return{n,live,kind:kind===5?0:kind,bytes:!live?null:kind===1?selectionBytes(m,at,n):k?rawRecord(m,at,k):Buffer.from(m.HEAPU8.slice(at,at+n)).toString('hex')};});return out;}
function compare(){assert.equal(text(hybrid,hybrid._probe_trace()),text(reference,reference._probe_trace()),active+' trace');comparisons++;assert.deepEqual(snapshot(hybrid),snapshot(reference),active+' state');comparisons++;modules.forEach((m,i)=>{assert.equal(m._probe_stack(),stacks[i],active+' stack');comparisons++;});assert.equal(C,undefined);}
function reset(){active='reset';each(m=>m._probe_reset());compare();}
function action(name,args=()=>[]){active=name;called.add(name);if(process.env.SP_LEV_TRACE_ACTIONS)console.error(name);assert.ok(index(name)>=0,name);const values=modules.map(m=>{const a=typeof args==='function'?args(m):args;return m._probe_action(index(name),...a.map(BigInt),...Array(8-a.length).fill(0n));});const t=schema.sourceReturns[name];if(name==='get_unpacked_coord')assert.deepEqual(typed(hybrid,Number(values[1]),'unpacked_coord'),typed(reference,Number(values[0]),'unpacked_coord'));else if(t==='char *')assert.equal(text(hybrid,values[1]),text(reference,values[0]),name+' result');else if(t.includes('*'))assert.deepEqual(identity(hybrid,values[1]).identity,identity(reference,values[0]).identity,name+' result');else assert.equal(values[1],values[0],name+' result');comparisons++;compare();return values;}
function lua(source){active='Lua '+source;const codes=modules.map(m=>m._probe_lua_prepare(BigInt(input(m,source))));assert.equal(codes[1],codes[0],active+' status');comparisons++;assert.equal(hybrid._probe_lua_top(),reference._probe_lua_top());for(let i=1;i<=reference._probe_lua_top();i++){assert.equal(hybrid._probe_lua_type(i),reference._probe_lua_type(i));if(reference._probe_lua_type(i)===3)assert.equal(hybrid._probe_lua_int(i),reference._probe_lua_int(i));else if(reference._probe_lua_type(i)===4)assert.equal(text(hybrid,hybrid._probe_lua_text(i)),text(reference,reference._probe_lua_text(i)));}compare();return codes[0];}
reset();action('reset_xystart_size');
for(const loc of [0n,11n|(10n<<16n),-1n,0x20000000000001n])for(const h of [0,1,7,65535]){reset();action('get_unpacked_coord',[loc,h]);}
for(const a of [-1,0,1,7,10,15,16,127,32767])for(const b of [0,1,10,16]){reset();action('match_maptyps',[a,b]);}
for(const name of ['rnddoor','rndtrap','random_wdir','noncoalignment','sp_amask_to_amask','flip_encoded_dir_bits']){reset();action(name,name==='flip_encoded_dir_bits'?[3,15]:[1]);}
for(const name of ['solidify_map','map_cleanup','remove_boundary_syms','link_doors_rooms','spo_end_moninvent','spo_pop_container','update_croom']){reset();action(name);}
for(const name of ['lvlfill_maze_grid','lvlfill_solid','lvlfill_swamp','set_wall_property','wallify_map','flip_visuals','flip_level','flip_level_rnd']){reset();action(name,name==='lvlfill_maze_grid'?[2,2,10,10,16]:name==='lvlfill_solid'?[16,1]:name==='lvlfill_swamp'?[16,0,1]:name==='set_wall_property'?[2,2,10,10,1]:name==='wallify_map'?[2,2,10,10]:name==='flip_visuals'?[3,1,0,79,20]:[0,0]);}
reset();lua('return type(des),type(des.map),type(selection),type(selection.new)');
reset();lua('des.message("fixture message"); return 123');
reset();lua('des.level_flags("noflip","noteleport"); return 1');

// Full typed allocation payloads and exact source map-fragment ownership.
for(const source of ['...\n...\n...','12...\n...\n...','..\n..','x']){reset();const values=action('mapfrag_fromstr',m=>[input(m,source)]);if(values[0]){action('mapfrag_canmatch',m=>[values[modules.indexOf(m)]]);if(source.includes('...')){action('mapfrag_get',m=>[values[modules.indexOf(m)],1,1]);action('mapfrag_match',m=>[values[modules.indexOf(m)],10,10]);}each(m=>cell(m,pool(m,8),'struct mapfragment *',values[modules.indexOf(m)]));action('mapfrag_free',m=>[pool(m,8)]);}}
reset();action('mapfrag_error',[0]);
// Real out-reference writes through native short cells and packed long inputs.
for(const name of ['get_room_loc','get_free_room_loc','get_location','get_location_coord','cvt_to_abscoord','cvt_to_relcoord']){reset();each(m=>{cell(m,pool(m,6),'short',2);cell(m,pool(m,6)+2,'short',3);});action(name,m=>{const x=pool(m,6),y=x+2,r=pool(m,5);return name==='get_room_loc'?[x,y,r]:name==='get_free_room_loc'?[x,y,r,2n|(3n<<16n)]:name==='get_location'?[x,y,1,r]:name==='get_location_coord'?[x,y,1,r,2n|(3n<<16n)]:[x,y];});}
for(const name of ['is_ok_location','pm_good_location','m_bad_boulder_spot','pm_to_humidity','shared_with_room','maybe_add_door','good_stair_loc','floodfillchk_match_under','floodfillchk_match_accessible']){reset();action(name,m=>{const e=envs.get(m);return name==='pm_to_humidity'?[e.mons+L['size:struct permonst']*0]:name==='pm_good_location'?[10,10,e.mons]:name==='shared_with_room'||name==='maybe_add_door'?[10,10,pool(m,5)]:[10,10,1];});}
for(const name of ['create_des_coder','sp_level_coder_init','l_register_des','l_push_wid_hei_table','l_push_mkroom_table','get_trapname_bytype','get_traptype_byname','get_mkroom_name','set_floodfillchk_match_under']){reset();action(name,m=>name==='l_register_des'?[m._probe_lua()]:name==='l_push_wid_hei_table'?[m._probe_lua(),3,4]:name==='l_push_mkroom_table'?[m._probe_lua(),pool(m,5)]:name==='get_traptype_byname'?[input(m,'arrow')]:name==='get_trapname_bytype'?[1]:[0]);}
// Prepared real Lua values feed direct original helper boundaries.
const tables={get_table_align:'{align="chaos"}',get_table_monclass:'{class="@"}',get_table_buc:'{buc="cursed"}',get_table_objclass:'{class="%"}',get_table_objtype:'{id="fixture"}',get_table_montype:'{id="human"}',get_table_xy_or_coord:'{coord={11,10}}',get_table_int_or_random:'{amount=9007199254741001}',get_table_roomtype_opt:'{kind="ordinary"}',get_table_traptype_opt:'{kind="arrow"}',get_table_region:'{region={2,3,10,11}}',get_coord:'{11,10}',get_table_intarray_entry:'{9007199254741001,17}',get_table_coords_or_region:'{region={2,3,10,11}}',l_get_lregion:'{region={2,3,10,11},exclude={3,4,5,6}}'};
for(const[name,value]of Object.entries(tables)){reset();lua('return '+value);action(name,m=>{const l=m._probe_lua(),p=pool(m,7),s=input(m,name==='get_table_int_or_random'?'amount':name==='get_table_region'?'region':'kind');switch(name){case'get_table_montype':return[l,p];case'get_table_xy_or_coord':return[l,p,p+8];case'get_table_int_or_random':return[l,s,19];case'get_table_roomtype_opt':case'get_table_traptype_opt':return[l,s,0];case'get_table_region':return[l,s,p,p+8,p+16,p+24,0];case'get_coord':return[l,1,p,p+8];case'get_table_intarray_entry':return[l,1,1];case'get_table_coords_or_region':return[l,p,p+2,p+4,p+6];case'l_get_lregion':return[l,pool(m,17)];default:return[l];}});}



// Native record pointer increments and dereferenced counter increments.
for(const secret of [0,1]){reset();option(0,secret);each(m=>{field(m,pool(m,6),'nhcoord','x',11);field(m,pool(m,6),'nhcoord','y',10);field(m,pool(m,6,1),'nhcoord','x',15);field(m,pool(m,6,1),'nhcoord','y',10);});action('dig_corridor',m=>[pool(m,6),pool(m,6,1),pool(m,7),0,L.CORR,L.ROOM]);assert.ok(cell(hybrid,pool(hybrid,7),'int')>0);comparisons++;}
for(const name of ['create_room','create_subroom','create_door','create_trap','create_monster','create_object','create_altar','search_door','create_corridor','fill_special_room','build_room','light_region','splev_initlev','flip_dbridge_horizontal','flip_dbridge_vertical','flip_vault_guard','sel_set_wall_property','sel_set_ter','sel_set_feature','sel_set_door','sel_set_lit','add_doors_to_room','levregion_add']){reset();if(name==='light_region')each(m=>field(m,pool(m,11),'region','rlit',1));if(name==='create_door')each(m=>field(m,pool(m,15),'room_door','wall',1));if(name==='build_room')each(m=>{for(const[f,v]of Object.entries({x:2,y:2,w:4,h:3,xalign:1,yalign:1}))field(m,pool(m,14),'_room',f,v);});action(name,m=>{const e=envs.get(m),map=e.field(e.field(e.svl,'instance_globals_saved_l','level').address,'dlevel_t','locations').address,rm=map+(10*21+10)*8;switch(name){case'create_room':return[10,5,4,3,1,1,0,1];case'create_subroom':return[pool(m,5),2,2,4,3,0,1];case'create_door':return[pool(m,15),pool(m,5)];case'create_trap':return[pool(m,13),0];case'create_monster':return[pool(m,1),0];case'create_object':return[pool(m,2),0];case'create_altar':return[pool(m,16),0];case'search_door':return[pool(m,5),pool(m,6),pool(m,6)+2,1,0];case'create_corridor':return[pool(m,9)];case'fill_special_room':case'add_doors_to_room':return[pool(m,5)];case'build_room':return[pool(m,14),pool(m,5)];case'light_region':return[pool(m,11)];case'splev_initlev':return[pool(m,12)];case'flip_dbridge_horizontal':case'flip_dbridge_vertical':return[rm];case'flip_vault_guard':return[0,pool(m,4),1,0,79,20];case'sel_set_wall_property':return[10,10,pool(m,7)];case'sel_set_ter':return[10,10,pool(m,18)];case'sel_set_feature':case'sel_set_door':case'sel_set_lit':return[10,10,pool(m,7)];case'levregion_add':return[pool(m,17)];}});}


// Real Lua callbacks execute through the registered original native identities.
const scripts=[
'des.level_init({style="solidfill",fg=".",lit=1})',
'des.monster({id="human",x=11,y=10,tail=false,group=false,adjacentok=true,ignorewater=true,countbirth=false})',
'des.object({id="fixture",x=11,y=10,quantity=3})',
'des.engraving({x=11,y=10,text="engraved",type="engrave"})',
'des.mineralize({goldprob=1,gemprob=2,kelppool=3,kelpmoat=4})',
'des.stair({dir="up",x=11,y=10})',
'des.ladder({dir="down",x=11,y=10})',
'des.grave({x=11,y=10,text="grave"})',
'des.altar({x=11,y=10,align="law",type="altar"})',
'des.trap({type="arrow",x=11,y=10})',
'des.gold({amount=17,x=11,y=10})',
'des.corridor({srcroom=-1,srcdoor=0,destroom=-1,destdoor=0})',
'des.random_corridors()',
'des.mazewalk({x=11,y=10,dir="east",stocked=false})',
'des.door({x=11,y=10,state="closed"})',
'des.feature({x=11,y=10,type="fountain"})',
'des.gas_cloud({x=11,y=10,damage=2,ttl=4})',
'des.terrain({x=11,y=10,typ=".",lit=1})',
'des.replace_terrain({region={2,2,8,8},fromterrain=".",toterrain="-",chance=100})',
'des.teleport_region({region={2,2,10,10},exclude={3,3,4,4},dir="up"})',
'des.levregion({region={2,2,10,10},exclude={3,3,4,4},type="stair-up"})',
'des.exclusion({region={2,2,10,10},type="monster-generation"})',
'des.region({region={2,2,10,10},lit=1,type="ordinary"})',
'des.drawbridge({x=11,y=10,dir="north",state="closed"})',
'des.wall_property({region={2,2,10,10},property="nondiggable"})',
'des.non_diggable(selection.area(2,2,10,10))',
'des.non_passwall(selection.area(2,2,10,10))',
'des.wallify({x1=2,y1=2,x2=10,y2=10})',
'des.map({x=10,y=8,map="...\\n...\\n...",lit=1})',
'des.room({x=10,y=5,w=4,h=3,type="ordinary",lit=1})',
'des.reset_level()',
'des.finalize_level()',
];
for(const script of scripts){reset();assert.equal(lua(script),0,script+' valid Lua caller');const match=/^des\.(\w+)\((.*)\)$/.exec(script),name='lspo_'+match[1];reset();assert.equal(lua('return '+match[2]),0);active=name;called.add(name);const status=modules.map(m=>m._probe_invoke_lua(index(name)));assert.equal(status[1],status[0],name+' protected status');assert.equal(status[0],0,name+' valid protected direct caller: '+text(reference,reference._probe_lua_text(-1)));comparisons+=2;compare();}
// Remaining native boundaries retain their actual formals and typed caller state.
for(const name of ['set_ok_location_func','find_montype','find_objtype','l_table_getset_feature_flag','nhl_abs_coord','l_create_stairway','set_wallprop_in_selection','load_special','maze1xy','fill_empty_maze','ensure_way_out','check_room']){reset();if(['l_table_getset_feature_flag','nhl_abs_coord','l_create_stairway'].includes(name))lua('return {x=11,y=10,dir="up",swarm=true}');if(name==='set_wallprop_in_selection')lua('return selection.area(2,2,8,8)');each(m=>{for(const[f,v]of Object.entries({x:10,y:8}))field(m,pool(m,6),'nhcoord',f,v);cell(m,pool(m,6,1),'short',3);cell(m,pool(m,6,1)+2,'short',3);});action(name,m=>{const p=pool(m,6),l=m._probe_lua();switch(name){case'set_ok_location_func':return[0];case'find_montype':return[l,input(m,'human'),pool(m,7)];case'find_objtype':return[l,input(m,'fixture'),0];case'l_table_getset_feature_flag':return[l,10,10,input(m,'swarm'),1];case'nhl_abs_coord':return[l];case'l_create_stairway':return[l,1];case'set_wallprop_in_selection':return[l,1];case'load_special':return[input(m,'fixture.lua')];case'maze1xy':return[p,1];case'check_room':return[p,p+4,p+2,p+6,0];default:return[];}});}
reset();lua('return selection.area(2,2,8,8)');action('generate_way_out_method',m=>[11,10,m._probe_selection()]);



for(const[name,source]of [['lspo_message','return "direct message"'],['lspo_level_flags','return "noflip","noteleport"']]){reset();lua(source);action(name,m=>[m._probe_lua()]);}
reset();action('set_door_orientation',[10,10]);reset();action('create_des_coder');action('spo_endroom',[0]);
// Two live rooms force the original224-byte mkroom pointer increment.
reset();each((m,e)=>{field(m,e.svn,'instance_globals_saved_n','nroom',2);const at=e.field(e.svr,'instance_globals_saved_r','rooms').address;for(let i=0;i<2;i++)for(const[f,v]of Object.entries({lx:5+i*20,hx:12+i*20,ly:4+i,hy:10+i}))field(m,at+i*L['size:struct mkroom'],'mkroom',f,v);field(m,at+2*L['size:struct mkroom'],'mkroom','hx',-1);});action('flip_level',[1,0]);

// Native aggregate-return callers copy the first16 bytes before the next static write.
reset();each(m=>m._probe_sret_sequence(11n|(10n<<16n),13n|(12n<<16n),7));compare();for(const m of modules){assert.deepEqual(rawRecord(m,pool(m,19),'unpacked_coord'),rawRecord(m,pool(m,19,2),'unpacked_coord'));assert.notDeepEqual(rawRecord(m,pool(m,19),'unpacked_coord'),rawRecord(m,pool(m,19,1),'unpacked_coord'));}comparisons+=4;
reset();option(3,1);option(4,1);action('rnddoor');assert.equal(field(hybrid,pool(hybrid,19,3),'unpacked_coord','x'),13);comparisons++;
// Current services forward per call and restore outer services even on a nested throw.
reset();const services=rawServices.get(hybrid),he=envs.get(hybrid),savedStack=hybrid._probe_stack(),first=callSpLev(services,L,core,'get_unpacked_coord',11n|(10n<<16n),7),firstBytes=first.slice();let outerCalls=0,nestedCalls=0;
const nested={...services,rn2:n=>{nestedCalls++;return services.rn2(n);}};
const outer={...services,rn2:n=>{outerCalls++;callSpLev(nested,L,core,'rnddoor');callSpLev(services,L,core,'get_unpacked_coord',13n|(12n<<16n),9);return services.rn2(n);}};
callSpLev(outer,L,core,'rnddoor');assert.equal(outerCalls,1);assert.equal(nestedCalls,1);assert.deepEqual(first,firstBytes);assert.equal(hybrid._probe_stack(),savedStack);assert.equal(C,undefined);comparisons+=5;
assert.throws(()=>callSpLev({...services,rn2:()=>{throw Error('SP_LEV scoped callback throw');}},L,core,'rnddoor'),/scoped callback throw/);assert.equal(hybrid._probe_stack(),savedStack);assert.equal(C,undefined);assert.doesNotThrow(()=>callSpLev(services,L,core,'rnddoor'));comparisons+=4;
const hybrid2=await(await factory('hybrid'))({nethackPorted:runtime});hybrid2._probe_reset();assert.notEqual(envs.get(hybrid2),he);const otherServices=rawServices.get(hybrid2);assert.notEqual(otherServices.moduleKey,services.moduleKey);callSpLev(otherServices,L,core,'get_unpacked_coord',17n|(18n<<16n),3);assert.deepEqual(first,firstBytes);comparisons+=3;

reset();for(const name of ['ring of fixture','potion of fixture','scroll of fixture','spellbook of fixture','wand of fixture'])action('find_objtype',m=>[m._probe_lua(),input(m,name),0]);
assert.equal(L['size:sp_lev_objclasspfx'],16);assert.equal(L['size:sp_lev_corridor_end'],6);comparisons+=2;
// Unknown char* keeps all64 bits and raw bytes without string dereference.
reset();const unknownChar=0x20000000000001n;each(m=>new DataView(m.HEAPU8.buffer).setBigUint64(envs.get(m).field(pool(m,10),'mapfragment','data').address,unknownChar,true));assert.deepEqual(rawRecord(hybrid,pool(hybrid,10),'mapfragment'),rawRecord(reference,pool(reference,10),'mapfragment'));assert.deepEqual(rawRecord(hybrid,pool(hybrid,10),'mapfragment').pointers['mapfragment.data'],['raw',unknownChar.toString()]);new DataView(hybrid.HEAPU8.buffer).setBigUint64(envs.get(hybrid).field(pool(hybrid,10),'mapfragment','data').address,unknownChar+2n,true);assert.notDeepEqual(rawRecord(hybrid,pool(hybrid,10),'mapfragment'),rawRecord(reference,pool(reference,10),'mapfragment'));comparisons+=3;

// Expected Lua errors compare exact diagnostics separately from positive callbacks.
for(const script of ['des.non_diggable({2,2,10,10})','des.object({id="unknown-fixture-item",x=11,y=10})','des.gold({amount="broken",x=11,y=10})']){reset();assert.notEqual(lua(script),0,script+' expected real protected Lua error');assert.equal(lua('des.message("recovered after error")'),0);comparisons+=2;}
reset();assert.equal(lua('des.map({x=10,y=8,map="...\\n...\\n...",contents=function() des.message("nested map contents") end})'),0);comparisons++;

// Addressed formal cells carry actual pointer/int arguments through true callbacks.
for(const source of ['..\n..','...\nxxx\n...']){reset();const v=action('mapfrag_fromstr',m=>[input(m,source)]);each(m=>cell(m,pool(m,8),'struct mapfragment *',v[modules.indexOf(m)]));action('mapfrag_error',m=>[v[modules.indexOf(m)]]);for(const m of modules)assert.equal(BigInt(cell(m,pool(m,8),'struct mapfragment *')),v[modules.indexOf(m)]);comparisons+=2;}
for(const viaSelection of [0,1]){reset();each((m,e)=>{const map=e.field(e.field(e.svl,'instance_globals_saved_l','level').address,'dlevel_t','locations').address;field(m,map+(10*21+10)*8,'rm','typ',L.HWALL);});if(viaSelection){lua('return selection.area(2,2,12,12)');action('set_wallprop_in_selection',m=>[m._probe_lua(),2]);}else action('set_wall_property',[10,10,10,10,1]);}

// Native pointer-cell and scalar observation controls never dereference unsafe64.
reset();const unknown=0x20000000000001n;
for(const m of modules){const at=envs.get(m).field(pool(m,3),'obj','nobj').address;new DataView(m.HEAPU8.buffer).setBigUint64(at,unknown,true);const got=rawRecord(m,pool(m,3),'obj');assert.deepEqual(got.pointers['obj.nobj'],['raw',unknown.toString()]);}
assert.deepEqual(rawRecord(hybrid,pool(hybrid,3),'obj'),rawRecord(reference,pool(reference,3),'obj'));
new DataView(hybrid.HEAPU8.buffer).setBigUint64(envs.get(hybrid).field(pool(hybrid,3),'obj','nobj').address,unknown+2n,true);
assert.notDeepEqual(rawRecord(hybrid,pool(hybrid,3),'obj'),rawRecord(reference,pool(reference,3),'obj'));assert.throws(()=>envs.get(hybrid).ptr(unknown));comparisons+=5;
reset();each(m=>field(m,pool(m,3),'obj','quan',BigInt(pool(reference,3))));assert.deepEqual(rawRecord(hybrid,pool(hybrid,3),'obj'),rawRecord(reference,pool(reference,3),'obj'));field(hybrid,pool(hybrid,3),'obj','quan',BigInt(pool(reference,3))+1n);assert.notDeepEqual(rawRecord(hybrid,pool(hybrid,3),'obj'),rawRecord(reference,pool(reference,3),'obj'));comparisons+=2;

if(process.env.SP_LEV_TRACE_ACTIONS)console.error('unreached',ops.filter(n=>!called.has(n)));
console.log('SP_LEV '+comparisons+' comparisons, '+called.size+'/142 direct entries; controlled world + real C Lua both modes; native/public pending');
