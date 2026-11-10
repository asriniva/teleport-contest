// Actual configured memory64 C vs imported JS; controlled world/window only.
import assert from 'node:assert/strict';
import{readFileSync,writeFileSync}from'node:fs';
import refFactory from'../.cache/display-first-pass/display-reference.mjs';
import hybridFactory from'../.cache/display-first-pass/display-hybrid.mjs';
const{callDisplay,initializeDisplay}=await import(process.env.DISPLAY_RUNTIME??'../js/ported/display-runtime.js');
const schema=JSON.parse(readFileSync(new URL('../nethack-c/wasm/tu-fragments/display-schema.json',import.meta.url))),functions=JSON.parse(readFileSync(new URL('../nethack-c/wasm/tu-fragments/display-source-metadata.json',import.meta.url))).functions,names=functions.map(f=>f.name),kinds=Object.keys(schema.schema),covered=new Set();

const output=[[],[]],ref=await refFactory({print:s=>output[0].push(['out',s]),printErr:s=>output[0].push(['err',s])}),hybrid=await hybridFactory({nethackPorted:{display:callDisplay,initializeDisplay:process.env.DISPLAY_STARTUP_NEGATIVE?()=>{}:initializeDisplay},print:s=>output[1].push(['out',s]),printErr:s=>output[1].push(['err',s])});const mods=[ref,hybrid];
const L=Object.fromEntries(schema.layoutKeys.map((k,i)=>[k,Number(ref._teleport_display_layout(i))]));
for(let i=0;i<schema.layoutKeys.length;i++)assert.equal(ref._teleport_display_layout(i),hybrid._teleport_display_layout(i));
const global=(m,n)=>Number(m._teleport_display_global(schema.globals.findIndex(g=>g.name===n))),ptr=(m,i)=>Number(m._probe_pointer(i));
const fieldIndex=(k,f)=>schema.schema[k].fields.findIndex(x=>x.name===f);
const addr=(m,p,k,f)=>Number(m._teleport_display_address(kinds.indexOf(k),BigInt(p),fieldIndex(k,f)));
const get=(m,p,k,f)=>m._teleport_display_read(kinds.indexOf(k),BigInt(p),fieldIndex(k,f));
const set=(m,p,k,f,v)=>m._teleport_display_write(kinds.indexOf(k),BigInt(p),fieldIndex(k,f),BigInt.asUintN(64,BigInt(v)));
const root=(m,n,k,f)=>addr(m,global(m,n),k,f),text=(m,s,p=ptr(m,0)+32768)=>(m.stringToUTF8(s,p,4096),p);
const setter=fn=>mods.forEach(fn),option=(i,v)=>setter(m=>m._probe_option(i,v)),seed=n=>setter(m=>m._probe_seed(n));
const typeKey=t=>kinds.find(k=>schema.schema[k].ctype.replace(/\b(?:const|volatile)\b/g,'').trim()===t)??(schema.schema[t.replace(/^(?:struct|union) /,'')]?t.replace(/^(?:struct|union) /,''):null);
const sizeOf=t=>{const a=t.match(/^(.*?)\[(\d+)\](.*)$/);if(a)return+a[2]*sizeOf(a[1]+a[3]);if(t.includes('*'))return 8;if(/^(?:unsigned |signed )?char$/.test(t))return 1;if(/^(?:unsigned )?short$/.test(t))return 2;if(/^(?:unsigned )?(?:int|enum \w+)$/.test(t))return 4;if(/^(?:unsigned )?long(?: long)?$/.test(t))return 8;return L['size:'+t]??L['size:'+schema.schema[typeKey(t)]?.ctype];};
const regionNames=['scratch','monsters','objlist','traps','engravings','regions','stairs','vision','visionrows','detailtext','glyph_events'];
const knownRegions=m=>[...schema.globals.filter(g=>g.name!=='stderr').map(g=>({name:g.name,p:global(m,g.name),size:Number(m._probe_global_size(schema.globals.indexOf(g)))})),...regionNames.map((name,i)=>({name,p:ptr(m,i),size:Number(m._probe_region_size(i))})),...schema.statics.filter(x=>!x.public&&x.owner===null).map(x=>({name:x.name,p:Number(m._probe_private(schema.statics.indexOf(x))),size:Number(m._probe_private_size(schema.statics.indexOf(x)))})),...schema.statics.filter(x=>x.public).map(x=>({name:x.name,p:Number(m._teleport_display_storage(schema.statics.indexOf(x))),size:Number(m._probe_public_size(schema.statics.indexOf(x)))})),...Array.from({length:m._probe_count()},(_,i)=>({name:'allocation'+i,p:Number(m._probe_alloc_pointer(i)),size:Number(m._probe_alloc_size(i)),live:Boolean(m._probe_alloc_live(i))}))];
// Read unknown pointer values as uint64 before conversion; only typed selected
// pointers into known exact regions are canonicalized. Unknown bytes stay raw.
const pointerID=(m,value)=>{const v=BigInt(value);if(v===0n)return'0';const r=knownRegions(m).find(r=>v>=BigInt(r.p)&&v<BigInt(r.p+r.size));return r?r.name+'+'+(v-BigInt(r.p)):'UNKNOWN:'+v;};
let scratchTypes=[];const returnedTypes=new Map(mods.map(m=>[m,[]]));
// Freed allocation bytes belong to the native allocator after their lifetime.
// Compare every live allocation byte; retain exact allocation lifetime metadata.
const rawRegions=m=>{
 const rs=knownRegions(m),regions=rs.filter(r=>r.live!==false&&!['cg','shield_static','defsyms','def_warnsyms','windowprocs'].includes(r.name)).map(r=>({...r,bytes:m.HEAPU8.slice(r.p,r.p+r.size),pointers:[]}));const visited=new Set();
 const pointerLayouts=new Map();
 const offsets=t=>{if(pointerLayouts.has(t))return pointerLayouts.get(t);let result=[];const a=t.match(/^(.*?)\[(\d+)\](.*)$/);if(a){const e=a[1]+a[3],pattern=offsets(e),step=sizeOf(e);if(step&&pattern.length)for(let i=0;i<+a[2];i++)for(const[o,ft]of pattern)result.push([i*step+o,ft]);}
  else if(t.includes('*'))result=[[0,t]];
  else if(!t.startsWith('union ')){const key=typeKey(t);if(key)for(const f of schema.schema[key].fields){if(f.bit)continue;const pattern=offsets(f.canonical);if(pattern.length){const base=ptr(m,0),off=addr(m,base,key,f.name)-base;for(const[o,ft]of pattern)result.push([off+o,ft]);}}}
  pointerLayouts.set(t,result);return result;};
 const visit=(at,t)=>{if(visited.has(at+':'+t))return;visited.add(at+':'+t);const dv=new DataView(m.HEAPU8.buffer);for(const[off,ft]of offsets(t)){const p=at+off,v=dv.getBigUint64(p,true),id=pointerID(m,v),r=regions.find(r=>p>=r.p&&p+8<=r.p+r.size);if(r&&!id.startsWith('UNKNOWN:')){r.pointers.push([p-r.p,id]);r.bytes.fill(0,p-r.p,p-r.p+8);}if(v&&v<=BigInt(Number.MAX_SAFE_INTEGER)){const pointee=ft.replace(/\s*\*\s*$/,'').trim(),key=typeKey(pointee);if(key&&rs.some(r=>v>=BigInt(r.p)&&v+BigInt(sizeOf(pointee)??0)<=BigInt(r.p+r.size)))visit(Number(v),pointee);}}};

 for(const g of schema.globals)if(!['windowprocs','cg','shield_static','defsyms','def_warnsyms'].includes(g.name))visit(global(m,g.name),g.canonical);
 for(const [offset,t]of scratchTypes)visit(ptr(m,0)+offset,t);
 for(const [at,t]of (returnedTypes.get(m)??[]))if(knownRegions(m).some(r=>at>=r.p&&at+sizeOf(t)<=r.p+r.size))visit(at,t);
 for(const row of schema.statics)if(row.public||row.owner===null)visit(Number(row.public?m._teleport_display_storage(schema.statics.indexOf(row)):m._probe_private(schema.statics.indexOf(row))),row.type);
 for(let i=0;i<m._probe_count();i++)if(m._probe_alloc_live(i)&&Number(m._probe_alloc_size(i))===sizeOf('struct tmp_glyph'))visit(Number(m._probe_alloc_pointer(i)),'struct tmp_glyph');
 for(let i=0;i<m._probe_glyph_events();i++){visit(ptr(m,10)+i*96,'struct glyphinfo');visit(ptr(m,10)+i*96+48,'struct glyphinfo');}
 for(const [i,t,count]of [[1,'struct monst',8],[2,'struct obj',8],[3,'struct trap',8],[4,'struct engr',8],[5,'NhRegion',8],[6,'struct stairway',8]]){const n=sizeOf(t);if(n)for(let j=0;j<count;j++)visit(ptr(m,i)+j*n,t);}
 visit(ptr(m,8),'unsigned char *[21]');
 return regions.map(r=>({name:r.name,bytes:Buffer.from(r.bytes).toString('hex'),pointers:r.pointers.sort((a,b)=>a[0]-b[0])}));
};
const snapshot=m=>({regions:rawRegions(m),trace:m.UTF8ToString(Number(m._probe_trace())),draws:m._probe_draws(),error:m._probe_error(),errno:m._probe_errno(),glyphEvents:m._probe_glyph_events(),allocationLive:Array.from({length:m._probe_count()},(_,i)=>m._probe_alloc_live(i))});
let checks=0,deferred=false;
function reset(){setter(m=>m._probe_reset());scratchTypes=[];returnedTypes.forEach(a=>a.length=0);output.forEach(a=>a.length=0);}
function compare(label){const a=snapshot(ref),b=snapshot(hybrid);try{assert.deepEqual(b,a,label);assert.deepEqual(output[1],output[0],label+' native stdout/stderr');checks++;}catch(e){writeFileSync(new URL('../.cache/display-first-pass/mismatch.json',import.meta.url),JSON.stringify({label,ref:a,hybrid:b},null,2));throw e;}}
function action(name,args=[]){covered.add(name);const results=mods.map((m,i)=>{const a=typeof args==='function'?args(m,i):args,sp=m.stackSave();try{const result=m._probe_action(names.indexOf(name),...Array.from({length:10},(_,j)=>BigInt(a[j]??0)));const rt=functions[names.indexOf(name)].type.qualType.split('(')[0];const returnedRecord=rt.replace(/\bconst\b/g,'').replace(/\s*\*\s*$/,'').trim();if(result&&rt.includes('*')&&typeKey(returnedRecord)&&result<=BigInt(Number.MAX_SAFE_INTEGER))returnedTypes.get(m).push([Number(result),returnedRecord]);return rt.includes('*')?(rt.includes('char')?(result?m.UTF8ToString(Number(result)):null):pointerID(m,result)):result;}finally{assert.equal(m.stackSave(),sp,name+' native stack cleanup');}});assert.equal(results[0],results[1],name+' result');if(!deferred)compare(name);return results;}

const publics=schema.statics.filter(x=>x.public);
assert.equal(ref._probe_startup_calls(),7);assert.equal(hybrid._probe_startup_calls(),7);
const startup=m=>m.HEAPU8.slice(Number(m._probe_startup()),Number(m._probe_startup())+Number(m._probe_startup_size()));
assert.deepEqual(startup(hybrid),startup(ref),'all seven public full native byte objects before first display body');
assert.equal(Number(ref._probe_startup_size()),308125);
console.log('PASS DISPLAY eager optimized extern constructor: all7/full308125bytes before first body');
reset();
const scalar=(m,off,t,v)=>{const p=ptr(m,0)+off,dv=new DataView(m.HEAPU8.buffer);if(t===8)dv.setBigInt64(p,BigInt(v),true);else if(t===4)dv.setInt32(p,v,true);else if(t===2)dv.setInt16(p,v,true);else dv.setInt8(p,v);};
const rec=(m,off)=>ptr(m,0)+off;
const C=Object.fromEntries(schema.layoutKeys.map(k=>[k,L[k]]));
for(const [,name,n]of readFileSync(new URL('../.cache/display-first-pass/macros.txt',import.meta.url),'utf8').matchAll(/^#define (DISP_\w+) \((-?\d+)\)$/gm))C[name]=+n;
for(const name of ['tp_sensemon','sensemon','mon_warning','mon_visible','see_with_infrared','canseemon','knowninvisible','is_safemon','warning_of','mon_overrides_region','mimic_light_blocking'])action(name,m=>name==='mon_overrides_region'?[ptr(m,1),35,10]:[ptr(m,1)]);
for(const name of ['magic_map_background','map_background','map_invisible','unmap_invisible','unmap_object','feel_newsym','feel_location','newsym','newsym_force','set_mimic_blocking','see_nearby_objects','back_to_glyph'])action(name,[40,10]);
action('map_trap',m=>[ptr(m,3),0]);action('map_engraving',m=>[ptr(m,4)]);action('map_object',m=>[ptr(m,2),0]);action('map_location',[40,10,0]);action('show_mon_or_warn',[40,10,0]);action('display_monster',m=>[40,10,ptr(m,1),1,0]);action('display_warning',m=>[ptr(m,1)]);
for(const name of ['suppress_map_output','see_monsters','see_objects','see_traps','curs_on_u','doredraw','docrt','reglyph_darkroom','clear_glyph_buffer','cls','set_wall_state'])action(name);
action('docrt_flags',[0]);action('redraw_map',[0]);action('show_glyph',[40,10,C.GLYPH_CMAP_A_OFF]);action('row_refresh',[38,42,10]);action('flush_screen',[0]);
setter(m=>set(m,global(m,'u'),'you','ustuck',ptr(m,1)));for(const name of ['swallowed','under_water','under_ground'])action(name,[1]);
action('shieldeff',[40,10]);action('tether_glyph',[1,1]);action('flash_glyph_at',[40,10,C.GLYPH_CMAP_A_OFF,1]);
action('tmp_at',[C.DISP_BEAM,C.GLYPH_CMAP_A_OFF]);action('tmp_at',[40,10]);action('tmp_at',[C.DISP_END,0]);
action('get_bkglyph_and_framecolor',m=>[40,10,rec(m,512),rec(m,516)]);action('swallow_to_glyph',[0,C.S_sw_tl]);action('zapdir_to_glyph',[1,0,0]);action('glyph_at',[40,10]);
scratchTypes=[[0,'struct glyphinfo']];action('map_glyphinfo',m=>[40,10,C.GLYPH_CMAP_A_OFF,0,rec(m,0)]);action('cmap_to_roguecolor',[0]);action('reset_glyphmap',[0]);
action('check_pos',[40,10,0]);action('set_twall',[40,10,39,10,41,10,40,11]);action('set_wall',[40,10,0]);action('set_corn',[40,10,39,10,41,10,40,11]);action('set_crosswall',[40,10]);action('xy_set_wall_state',[40,10]);
action('set_seenv',m=>[Number(m._probe_grid())+(41*21+11)*8,40,10,41,11]);action('unset_seenv',m=>[Number(m._probe_grid())+(41*21+11)*8,40,10,41,11]);action('t_warn',m=>[Number(m._probe_grid())+(40*21+10)*8]);action('wall_angle',m=>[Number(m._probe_grid())+(40*21+10)*8]);action('fn_cmap_to_glyph',[0]);
console.log('DISPLAY draft',checks,covered.size,'missing',names.filter(n=>!covered.has(n)));
// Optimized native ABI copy: all 4 coordinate bytes survive a callback which
// mutates the original caller storage after the native callee receives coord.
for(const [x,y]of [[-32768,32767],[0,0],[40,10],[12345,-23456]]){
 reset();scratchTypes=[[512,'char *']];setter(m=>{scalar(m,128,2,x);scalar(m,130,2,y);m._probe_coord(BigInt(rec(m,128)));});
 const before=mods.map(m=>m.HEAPU8.slice(rec(m,128),rec(m,132)));
 ref._probe_coord_call(BigInt(rec(ref,128)));hybrid._teleport_display_dep_do_screen_description(BigInt(rec(hybrid,128)),0,0,BigInt(rec(hybrid,1024)),BigInt(rec(hybrid,512)),0n);
 assert.deepEqual(before[0],before[1]);assert.equal(ref.UTF8ToString(Number(ref._probe_trace())),hybrid.UTF8ToString(Number(hybrid._probe_trace())));
 assert.match(ref.UTF8ToString(Number(ref._probe_trace())),new RegExp('coord-after:'+x+','+y));compare('native coord by-value '+x+','+y);
}
// Eager initialization occurs once, including native mutable public storage.
setter(m=>m._probe_wallcolor(2,19));action('fn_cmap_to_glyph',[0]);
for(const m of mods){const at=Number(m._teleport_display_storage(schema.statics.findIndex(s=>s.name==='wallcolors')));assert.equal(new DataView(m.HEAPU8.buffer).getInt32(at+8,true),19);}

// Exhaust all byte seenv vectors and eight packed wall modes across original
// wall families. Native result, full packed map and accumulated diagnostics
// are compared; batching only avoids repeated large identical heap snapshots.
for(const typ of ['VWALL','HWALL','TLCORNER','TRCORNER','BLCORNER','BRCORNER','CROSSWALL','TUWALL','TDWALL','TLWALL','TRWALL']){
 reset();deferred=true;
 for(let mode=0;mode<8;mode++)for(let seen=0;seen<256;seen++){
  setter(m=>{m._probe_map(40,10,C[typ],seen);const p=Number(m._probe_grid())+(40*21+10)*8;set(m,p,'rm','flags',mode);set(m,p,'rm','horizontal',mode&1);});
  action('wall_angle',m=>[Number(m._probe_grid())+(40*21+10)*8]);
 }
 deferred=false;compare('wall_angle all256 vectors/8 modes '+typ);
}
// All public map rows and packed glyph buffer bytes after real source resets.
for(const color of [0,1])for(const rogue of [0,1]){
 reset();option(13,color?0:1);setter(m=>{set(m,global(m,'iflags'),'instance_flags','wc_color',color);if(rogue){const d=addr(m,global(m,'svd'),'instance_globals_saved_d','dungeon_topology'),l=addr(m,d,'dgn_topology','d_rogue_level');set(m,l,'d_level','dlevel',3);}});
 action('reset_glyphmap',[0]);action('clear_glyph_buffer');
 setter(m=>{const z=addr(m,global(m,'u'),'you','uz0');set(m,z,'d_level','dlevel',3);});action('redraw_map',[1]);
}
// Actual typed native pointer-return positive/null paths.
for(const present of [0,1]){
 reset();for(const i of [3,4,5,8,11])option(i,present);option(9,1);option(12,present);
 setter(m=>{set(m,ptr(m,3),'trap','tx',40);set(m,ptr(m,3),'trap','ty',10);set(m,ptr(m,3),'trap','ttyp',1);set(m,ptr(m,4),'engr','engr_x',40);set(m,ptr(m,4),'engr','engr_y',10);set(m,ptr(m,5),'NhRegion','visible',1);});
 action('map_location',[40,10,1]);action('feel_location',[40,10]);action('newsym',[40,10]);setter(m=>{m._probe_map(40,10,C.STAIRS,255);m.HEAPU8.fill(3,ptr(m,7),ptr(m,7)+1680);});action('back_to_glyph',[40,10]);
}

console.log('PASS DISPLAY first extended',checks,'comparisons: all71, optimized constructor7/full308125, native coord4byte copy/caller mutation, full9624glyphmap/full80x21buf,22528wall inputs (normal mode ranges and defined diagnostic/fallback separately documented)');
const property=(m,n,v)=>{const p=addr(m,global(m,'u'),'you','uprops')+C[n]*sizeOf('struct prop');set(m,p,'prop','intrinsic',v);};
const visible=()=>setter(m=>m.HEAPU8.fill(3,ptr(m,7),ptr(m,7)+1680));
// Native display RNG is distinct from the primary game RNG; every actual
// source macro expansion stays inline. Positive hallucination paths vary
// object kinds, gender, mimics, detection and worm tails.
for(const hallucinating of [0,1]){
 reset();visible();setter(m=>{property(m,'HALLUC',hallucinating);set(m,root(m,'svl','instance_globals_saved_l','level'),'dlevel_t','monlist',ptr(m,1));});
 deferred=true;
 for(const kind of [1,C.STATUE,C.CORPSE,C.BOULDER]){setter(m=>set(m,ptr(m,2),'obj','otyp',kind));action('map_object',m=>[ptr(m,2),1]);}
 for(const sex of [0,1])for(const mimic of [0,C.M_AP_FURNITURE,C.M_AP_OBJECT,C.M_AP_MONSTER])for(const sight of [1,2])for(const tail of [0,1]){
  setter(m=>{const p=ptr(m,1);set(m,p,'monst','female',sex);set(m,p,'monst','m_ap_type',mimic);set(m,p,'monst','mappearance',mimic===C.M_AP_FURNITURE?C.S_room:mimic===C.M_AP_OBJECT?C.STATUE:1);});
  action('display_monster',m=>[35,10,ptr(m,1),sight,tail]);
 }
 setter(m=>{set(m,ptr(m,1),'monst','m_ap_type',0);set(m,ptr(m,1),'monst','m_lev',20);property(m,'WARNING',1);});action('display_warning',m=>[ptr(m,1)]);
 setter(m=>{const level=root(m,'svl','instance_globals_saved_l','level'),grid=addr(m,level,'dlevel_t','monsters');new DataView(m.HEAPU8.buffer).setBigUint64(grid+(35*21+10)*8,BigInt(ptr(m,1)),true);});
 action('newsym',[35,10]);setter(m=>set(m,global(m,'u'),'you','ustuck',ptr(m,1)));action('swallowed',[1]);
 for(const loc of [C.S_sw_tl,C.S_sw_br])action('swallow_to_glyph',[1,loc]);
 deferred=false;compare('positive display RNG/mimics '+hallucinating);if(hallucinating)assert.ok(ref._probe_draws()>30);
}
// True source-owned function pointer goes through native iter_mons into JS.
reset();option(10,2);setter(m=>{for(let i=0;i<2;i++){const p=ptr(m,1)+i*sizeOf('struct monst');set(m,p,'monst','m_ap_type',C.M_AP_FURNITURE);set(m,p,'monst','mappearance',C.S_hcdoor);}});action('set_mimic_blocking');assert.match(ref.UTF8ToString(Number(ref._probe_trace())),/iter_mons\(native-source-callback\)/);
// Nested source-owned temporary display stack, all styles, dynamic ownership,
// capacity bound, changing glyph, tether backtracking and final free.
reset();visible();deferred=true;
for(const style of [C.DISP_BEAM,C.DISP_ALL,C.DISP_TETHER,C.DISP_FLASH,C.DISP_ALWAYS]){
 action('tmp_at',[style,C.GLYPH_CMAP_A_OFF]);action('tmp_at',[35,10]);action('tmp_at',[36,10]);
 action('tmp_at',[C.DISP_ALWAYS,C.GLYPH_CMAP_A_OFF]);action('tmp_at',[37,10]);action('tmp_at',[C.DISP_CHANGE,C.GLYPH_MON_MALE_OFF]);action('tmp_at',[C.DISP_END,0]);
 action('tmp_at',[C.DISP_END,style===C.DISP_TETHER?-1:0]);
}
action('tmp_at',[C.DISP_ALL,C.GLYPH_CMAP_A_OFF]);for(let i=0;i<162;i++)action('tmp_at',[1+i%79,Math.floor(i/79)]);action('tmp_at',[C.DISP_FREEMEM,0]);
deferred=false;compare('temporary glyph styles/nesting160bound/ownership');assert.ok(ref._probe_count()>=5);for(let i=0;i<ref._probe_count();i++)assert.equal(ref._probe_alloc_live(i),0);
// Full aggregate copies preserve user unicode pointer aliases and padding.
reset();setter(m=>{const row=Number(m._teleport_display_storage(schema.statics.findIndex(s=>s.name==='glyphmap')))+C.GLYPH_CMAP_A_OFF*32;m.HEAPU8.fill(0xA5,row,row+32);set(m,row,'glyph_map_entry','u',rec(m,6000));const sym=addr(m,row,'glyph_map_entry','sym');set(m,sym,'classic_representation','symidx',0);m.HEAPU8.fill(0x5A,rec(m,0),rec(m,48));});scratchTypes=[[0,'struct glyphinfo']];action('map_glyphinfo',m=>[35,10,C.GLYPH_CMAP_A_OFF,0,rec(m,0)]);for(const m of mods)assert.equal(new DataView(m.HEAPU8.buffer).getUint32(rec(m,8),true),0x5A5A5A5A,'map_glyphinfo leaves framecolor untouched');
action('show_glyph',[35,10,C.GLYPH_CMAP_A_OFF]);action('flush_screen',[1]);
// Accessibility's actual source caller reaches native by-value coord wrapper.
reset();action('clear_glyph_buffer');setter(m=>set(m,global(m,'a11y'),'accessibility_data','glyph_updates',1));action('show_glyph',[37,9,C.GLYPH_CMAP_A_OFF]);assert.match(ref.UTF8ToString(Number(ref._probe_trace())),/coord-before:37,9/);
// Explicit original diagnostics and guarded coordinate fallback, not UB.
reset();for(const pos of [[0,10],[-1,10],[80,10]])action('newsym',pos);action('glyph_at',[-1,21]);action('swallow_to_glyph',[0,0]);action('zapdir_to_glyph',[1,0,99]);action('show_glyph',[80,10,C.GLYPH_MON_MALE_OFF]);
// Native long values stay exact beyond JavaScript's safe integer range.
reset();setter(m=>{set(m,global(m,'svm'),'instance_globals_saved_m','moves',0x20000000000001n);set(m,global(m,'gg'),'instance_globals_g','glyph_reset_timestamp',0x40000000000003n);set(m,global(m,'gg'),'instance_globals_g','glyphmap_perlevel_flags',0x40000000000001n);});action('reset_glyphmap',[1]);
// Normalization witnesses: unknown selected pointer64 remains raw; an ordinary
// scalar numerically equal to a native address must never be normalized.
reset();scratchTypes=[[0,'struct glyphinfo']];setter(m=>set(m,addr(m,rec(m,0),'glyphinfo','gm'),'glyph_map_entry','u',0x20000000000001n));assert.deepEqual(snapshot(ref),snapshot(hybrid));set(hybrid,addr(hybrid,rec(hybrid,0),'glyphinfo','gm'),'glyph_map_entry','u',0x20000000000002n);assert.throws(()=>assert.deepEqual(snapshot(hybrid),snapshot(ref)));reset();setter(m=>scalar(m,6000,8,BigInt(ptr(m,0))));assert.notEqual(ptr(ref,0),ptr(hybrid,0));assert.throws(()=>assert.deepEqual(snapshot(hybrid),snapshot(ref)));reset();
console.log('PASS DISPLAY extended',checks,'comparisons; positive display RNG, actual native callback identity, all temporary styles/capacity/nesting/free, full aggregate48/32byte copies/framecolor/padding/unicode aliases, source by-value caller, exact64bit/raw pointer/scalar witnesses.');
// Native print callback reenters actual source functions while foreground is
// persistent native gbuf storage and background is a live local aggregate.
reset();action('clear_glyph_buffer');option(14,1);action('show_glyph',[39,10,C.GLYPH_CMAP_A_OFF]);action('flush_screen',[1]);assert.match(ref.UTF8ToString(Number(ref._probe_trace())),/window.native-reentry-borrowed/);
// Function-qualified persistent coordinate/delay statics remain distinct.
reset();setter(m=>set(m,global(m,'u'),'you','ustuck',ptr(m,1)));for(const n of ['swallowed','under_water','under_ground']){action(n,[1]);if(n!=='swallowed')action(n,[2]);setter(m=>{set(m,global(m,'u'),'you','ux',42);set(m,global(m,'u'),'you','uy',12);});action(n,[0]);}
// Independent factory instances: all7 ctor bytes again, native heap growth,
// native C -> imported JS reentry and outer/inner stack cleanup.
const fresh=await refFactory();let third,grown=false,reentered=false,initializations=0;
third=await hybridFactory({nethackPorted:{initializeDisplay(services){initializations++;return initializeDisplay(services);},display(services,name,...args){const native=services.rn2_on_display_rng;services.rn2_on_display_rng=n=>{if(!grown){grown=true;const old=third.HEAPU8.buffer;third._probe_growth();assert.notEqual(third.HEAPU8.buffer,old);const sp=third.stackSave();third._probe_action(names.indexOf('fn_cmap_to_glyph'),BigInt(C.S_room),0n,0n,0n,0n,0n,0n,0n,0n,0n);assert.equal(third.stackSave(),sp);reentered=true;}return native(n);};return callDisplay(services,name,...args);}}});
assert.equal(initializations,1);assert.deepEqual(startup(third),startup(fresh));for(const m of[fresh,third]){returnedTypes.set(m,[]);m._probe_reset();property(m,'HALLUC',1);}
scratchTypes=[];
for(const m of[fresh,third]){const sp=m.stackSave();m._probe_action(names.indexOf('map_object'),BigInt(ptr(m,2)),1n,0n,0n,0n,0n,0n,0n,0n,0n);assert.equal(m.stackSave(),sp);}
assert.ok(grown&&reentered);assert.deepEqual(snapshot(third),snapshot(fresh),'fresh Modules/growth/native source reentry');checks++;
// Stable done_hup exits at the original early suppression check. Releasing
// that condition permits output; no artificial asynchronous branch witness.
for(const m of[fresh,third]){set(m,global(m,'program_state'),'sinfo','done_hup',1);m._probe_action(names.indexOf('flush_screen'),0n,0n,0n,0n,0n,0n,0n,0n,0n,0n);set(m,global(m,'program_state'),'sinfo','done_hup',0);m._probe_action(names.indexOf('show_glyph'),38n,10n,BigInt(C.GLYPH_CMAP_A_OFF),0n,0n,0n,0n,0n,0n,0n);m._probe_action(names.indexOf('flush_screen'),1n,0n,0n,0n,0n,0n,0n,0n,0n,0n);assert.ok(m._probe_glyph_events()>0);}
assert.deepEqual(snapshot(third),snapshot(fresh),'actual stable hangup suppression then normal output');checks++;
assert.equal(covered.size,71);
console.log('PASS DISPLAY FINAL',checks,'top-level state/result comparisons; all71 configured functions,22528 additional wall result checks, native constructor all7/full308125bytes before first body in independent Modules, typed coord-by-value, display RNG/native source callback, full9624 maps/80x21buffer/48byte window records, temporary ownership,64bit/raw witnesses,growth/reentry/stack cleanup. Controlled world/window dependency models only; native/full-game/public pending.');
