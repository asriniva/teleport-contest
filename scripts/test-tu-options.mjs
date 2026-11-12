import assert from './native-test-assert.mjs';
import {referenceBackend,assertStackRestored,memoryCheckpoint,assertMemoryGrowth} from './native-test-backend.mjs';
import {readFileSync,writeFileSync} from 'node:fs';
import {callOptions} from '../js/nethack/bindings/options.js';
import {C,R,T,withCEnvironment} from '../js/c-runtime/context.js';
import {createRegexAbi} from '../js/c-runtime/regex-abi.js';
if(process.env.TELEPORT_NATIVE_TESTS!=='0')throw Error('OPTIONS has no native reference fixture; set TELEPORT_NATIVE_TESTS=0 only for explicit Emscripten diagnostics.');
const own=process.env.TELEPORT_OPTIONS_AUTHOR==='1',base=own?'../.cache/options-author/':'../.cache/tu-probes/';
const referenceFactory=(await import(base+(own?'reference.mjs':'options-reference.mjs'))).default;
const hybridFactory=(await import(base+(own?'hybrid.mjs':'options-hybrid.mjs'))).default;
const S=JSON.parse(readFileSync(new URL('../nethack-c/wasm/tu-fragments/options-schema.json',import.meta.url)));
const provide=createRegexAbi(),servicesByModule=new Map();
const ported={callOptions(s,n,...a){servicesByModule.set(s.moduleKey,s);return callOptions(s,undefined,n,...a);},nativeRegex:(s,n,...a)=>provide(s)[n](...a)};
const reference=await referenceBackend('options',referenceFactory)({nethackPorted:ported});
let lastAction='startup';process.on('uncaughtExceptionMonitor',()=>writeFileSync(new URL('../.cache/options-author/last-action.txt',import.meta.url),lastAction));
let modules=[reference,await hybridFactory({nethackPorted:ported})],comparisons=0;
const text=(m,p)=>{p=Number(p);let z=p;while(m.HEAPU8[z])z++;return Buffer.from(m.HEAPU8.slice(p,z)).toString('latin1');};
const nullable=(m,p)=>p?text(m,p):null;
const L=Object.fromEntries(S.layoutKeys.map((n,i)=>{let v=BigInt.asIntN(64,reference._probe_layout(i));return[n,Number.isSafeInteger(Number(v))?Number(v):v];}));
if(own)writeFileSync(new URL('../.cache/options-author/layout.json',import.meta.url),JSON.stringify(L,(_,v)=>typeof v==='bigint'?String(v):v,2));
const kinds=Object.keys(S.schema),ki=n=>{const i=kinds.indexOf(n);assert.ok(i>=0,'native record '+n);return i;},fi=(k,f)=>{const i=S.schema[k]?.fields.findIndex(x=>x.name===f);assert.ok(i>=0,'native field '+k+'.'+f);return i;},st=n=>S.statics.findIndex(x=>x.name===n),gi=n=>S.globals.findIndex(x=>x.name===n),buf=(m,i)=>m._probe_buffer(i),bits=v=>BigInt.asUintN(64,v);
const field=(m,k,p,f)=>bits(m._probe_read(ki(k),BigInt(p),fi(k,f))),write=(m,k,p,f,v)=>m._probe_write(ki(k),BigInt(p),fi(k,f),BigInt(v));
const address=(m,k,p,f)=>Number(m._probe_address(ki(k),BigInt(p),fi(k,f))),global=(m,n)=>Number(m._probe_global(gi(n)));
const retType=n=>S.functionTypes[n].split('(')[0].trim(),pointerReturn=n=>retType(n).includes('*');
const stacks=modules.map(m=>m._probe_stack()),exercised=new Set();
const tokenMaps=modules.map(m=>new Map(S.functionAddresses.map((n,i)=>[bits(m._probe_function_token(i)),n])));
function input(i,s){for(const m of modules){m.HEAPU8.fill(0,Number(buf(m,i)),Number(buf(m,i))+8192);m.HEAPU8.set(Buffer.from(s+'\0','latin1'),Number(buf(m,i)));}}
function token(m,p){return tokenMaps[modules.indexOf(m)]?.get(bits(p))??(p?'foreign-function':null);}
function size(t){if(t==='menu_cmd_t'||t==='struct menu_cmd_t')return L['size:menu_cmd_t'];const a=t.match(/^(.*?)\[(\d+)\](.*)$/);if(a)return +a[2]*size(a[1]+a[3]);if(t.includes('*'))return 8;if(t.startsWith('enum '))return 4;return ({char:1,'signed char':1,'unsigned char':1,short:2,'unsigned short':2,int:4,'unsigned int':4,long:8,'unsigned long':8,'long long':8,'unsigned long long':8})[t]??L['size:'+t];}
function scalar(m,p,t){const d=new DataView(m.HEAPU8.buffer);if(t.includes('*'))return d.getBigUint64(p,true);const n=size(t);return n===8?d.getBigUint64(p,true):BigInt(d['getUint'+(8*n)](p,true));}
const skipGlobals=new Set(['cg','nul_glyphinfo','aligns','genders','races','roles','vanqorders','known_handling','def_warnsyms','def_oc_syms','hexdd','disclosure_options']);
function projection(m,staticsOnly=false){
 const seen=new Map();
 function value(t,p,depth=0){
  if(t==='menu_cmd_t')t='struct menu_cmd_t';
  const a=t.match(/^(.*?)\[(\d+)\](.*)$/);if(a){const b=a[1]+a[3],n=+a[2],z=size(b);assert.ok(z,t);return Array.from({length:n},(_,i)=>value(b,p+i*z,depth));}
  if(t.includes('[]'))return 'foreign-unsized-array';
  if(!t.includes('*')&&(t.startsWith('struct ')||t.startsWith('union '))){const k=t.replace(/^(?:struct|union) /,''),rec=S.schema[k];if(!rec)return 'foreign-record';return Object.fromEntries(rec.fields.map(f=>{const v=field(m,k,p,f.name),t=f.canonical;if(t.includes('[')||!t.includes('*')&&/^(struct|union) /.test(t))return[f.name,value(t,address(m,k,p,f.name),depth)];return[f.name,t.includes('*')?pointer(t,v,depth):String(v)];}));}
  const v=scalar(m,p,t);return t.includes('*')?pointer(t,v,depth):String(v);
 }
 function pointer(t,v,depth){if(!v)return null;if(t.includes('(*'))return token(m,v);if(/^(?:const )?char\s*\*$/.test(t))return text(m,v);if(t.startsWith('struct ')){const k=t.match(/^struct (\w+)/)?.[1];if(S.schema[k]&&depth<160){const key=k+':'+v;if(seen.has(key))return {alias:seen.get(key)};seen.set(key,seen.size);return value('struct '+k,Number(v),depth+1);}}return 'nonnull';}
 if(staticsOnly)return Object.fromEntries(S.statics.filter(g=>!g.name.includes('.')).map(g=>[g.name,value(g.type,Number(m._probe_data(st(g.name))))]));
 return Object.fromEntries(S.globals.filter(g=>!skipGlobals.has(g.name)).map(g=>[g.name,value(g.canonical,global(m,g.name))]));
}
function check(){const pair=modules.map(m=>({state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace()),globals:projection(m)}));try{assert.deepEqual(pair[1],pair[0]);}catch(e){writeFileSync(new URL('../.cache/options-author/difference.json',import.meta.url),JSON.stringify(pair));throw e;}modules.forEach((m,i)=>assertStackRestored(m,stacks[i],m._probe_stack()));comparisons++;}
function act(n,args=[]){lastAction=n;exercised.add(n);const i=S.names.indexOf(n);assert.ok(i>=0,n);const values=modules.map((m,mi)=>m._probe_call(i,...Array.from({length:6},(_,j)=>BigInt(typeof args[j]==='function'?args[j](m,mi):args[j]??0))));if(pointerReturn(n)){assert.equal(nullable(modules[1],values[1]),nullable(modules[0],values[0]),n);}else assert.equal(values[1],values[0],n);comparisons++;check();return pointerReturn(n)?nullable(modules[0],values[0]):BigInt.asIntN(64,values[0]);}
const reset=()=>{modules.forEach(m=>m._probe_reset());check();};
const clear=()=>modules.forEach(m=>m._probe_clear());
const freed=m=>Number(/^free:(\d+);/.exec(text(m,m._probe_snapshot()))[1]);
function table(which){const pair=modules.map(m=>{const p=Number(m._probe_data(which));return Array.from({length:218},(_,i)=>{const a=p+i*L['size:struct allopt_t'];return Object.fromEntries(S.schema.allopt_t.fields.map(f=>{const v=field(m,'allopt_t',a,f.name);if(f.name==='optfn')return[f.name,token(m,v)];if(f.name==='addr')return[f.name,v?{value:m.HEAPU8[Number(v)],alias:Array.from({length:i},(_,j)=>field(m,'allopt_t',p+j*L['size:struct allopt_t'],'addr')).findIndex(q=>q===v)}:null];if(f.canonical.includes('*'))return[f.name,nullable(m,v)];return[f.name,String(v)];}));});});assert.deepEqual(pair[1],pair[0]);comparisons+=218;return pair[0];}
// Enter an actual original function before observing private lazily packed source data.
input(0,'foo:bar');input(1,'foo');assert.equal(act('match_optname',[m=>buf(m,0),m=>buf(m,1),3,1]),1n);
assert.deepEqual(projection(modules[1],true),projection(reference,true),'all 36 native file-static initializers, every field and string');comparisons+=36;
table(0);for(const m of modules)assert.ok(m.HEAPU8.slice(Number(m._probe_data(1)),Number(m._probe_data(1))+218*L['size:struct allopt_t']).every(x=>x===0),'live allopt remains zero before its explicit initializer');comparisons++;
reset();assert.match(text(reference,reference._probe_catalogue()),/^1:1:strange object:human:Archeologist$/,'real object/monster/role catalogues initialized');assert.equal(text(modules[1],modules[1]._probe_catalogue()),text(reference,reference._probe_catalogue()));comparisons++;
for(const m of modules){for(const n of ['assure_syscf_file','read_config_file'])m._probe_return(Object.keys(S.dependencies).indexOf(n),1n);}
act('initoptions_init');assert.match(text(reference,reference._probe_catalogue()),/^1:1:slime mold:human:Archeologist$/,'original OPTIONS initialization assigns its own fruit name index');comparisons++;
const rows=table(1),rowIndex=n=>rows.findIndex(r=>r.name===n),byHandler=n=>rows.findIndex(r=>r.optfn===n);
for(const which of [0,1])for(let row=0;row<218;row++){const values=modules.map(m=>m.HEAPU8.slice(Number(m._probe_table_bytes(which,row)),Number(m._probe_table_bytes(which,row))+L['size:struct allopt_t']));assert.deepEqual(values[1],values[0],'full scalar bytes/padding '+which+':'+row);comparisons++;}
clear();act('allopt_array_init');assert.equal(text(reference,reference._probe_trace()),'','repeat initialization is inert');
// Every configured option handler is called directly with its real table index.
for(const n of S.names.filter(n=>/^(?:optfn_|pfxfn_)/.test(n))){let index=byHandler(n);if(index<0)index=0;for(const req of [1,4,5]){input(0,'');input(1,'');clear();act(n,[index,req,0,m=>buf(m,0),m=>buf(m,1)]);assert.deepEqual(modules[1].HEAPU8.slice(Number(buf(modules[1],0)),Number(buf(modules[1],0))+8192),modules[0].HEAPU8.slice(Number(buf(modules[0],0)),Number(buf(modules[0],0))+8192),n+' output/guard bytes');comparisons++;}}
console.log('OPTIONS initial',comparisons,'comparisons;',exercised.size,'/224 functions');
// Original menu handlers retain their own cancellation and cleanup paths.
for(const n of S.names.filter(n=>n.startsWith('handler_'))){reset();modules.forEach(m=>m._probe_menu(0,-1));const option=n==='handler_align_misc'?'align_message':n==='handler_symset'?'symset':n.slice(8);act(n,[Math.max(0,rowIndex(option))]);}
// Boolean rows use their actual live native address cells, including aliases.
for(let i=0;i<217;i++)if(rows[i].optfn==='optfn_boolean'&&rows[i].addr){for(const negated of [0,1]){input(0,rows[i].name);input(1,'');clear();act('optfn_boolean',[i,2,negated,m=>buf(m,0),m=>buf(m,1)]);}}
for(const [s,min,allow]of [['autopickup',3,0],['AutoPickup',3,0],['autopickup:off',3,1],['auto',5,0],['!autopickup',3,0],['',0,1]]){input(0,s);input(1,'autopickup');clear();act('match_optname',[m=>buf(m,0),m=>buf(m,1),min,allow]);}
for(const s of ['autopickup','!autopickup','autopickup:true','autopickup:off','autopickup:xyz','noautopickup','not_an_option','male','female','no!autopickup','!fruit:pear','!fruit','fruit:pear','number_pad:2','number_pad:-1','paranoid_confirmation:all','paranoid_confirmation:none','paranoid_confirmation:!quit attack','menu_objsyms:2','runmode:walk','pickup_burden:stressed','sortloot:full','packorder:$)[%?+!=/(*`0_','statushilites:9007199254740993','statushilites:-1','role:Wizard','race:elf','gender:female','alignment:chaotic','font_map:mono','font_map:serif','font_size_map:15','windowcolors:menu white/black','menuinvertmode:2','effects:1','playmode:normal','versinfo:all']){reset();input(0,s);clear();act('parseoptions',[m=>buf(m,0),1,1]);}
// Source-owned one-function helpers, with valid writable native buffers.
reset();
for(const n of ['check_misc_menu_command','petname_optfn','shared_menu_optfn','spcfn_misc_menu_cmd']){input(0,'catname:Mittens');input(1,'Mittens');clear();if(n==='check_misc_menu_command')act(n,[m=>buf(m,0),m=>buf(m,1)]);else act(n,[Math.max(0,rowIndex(n==='petname_optfn'?'catname':'menu_next_page')),4,0,m=>buf(m,0),m=>buf(m,1)]);}
for(const i of [-1,0,1,2,3,4,217])act('opt2roleopt',[i]);
for(const n of ['saveoptstr','getoptstr','unsaveoptstr']){input(0,'Wizard');clear();act(n,n==='saveoptstr'?[rowIndex('role'),m=>buf(m,0)]:[rowIndex('role'),L.builtin_opt??1]);}
act('freeroleoptvals');
for(const s of ['foo','foo:','foo=bar','foo:one=two','foo=one:two']){input(0,s);clear();act('string_for_opt',[m=>buf(m,0),0]);act('string_for_opt',[m=>buf(m,0),1]);input(1,'foo');act('string_for_env_opt',[m=>buf(m,1),m=>buf(m,0),0]);}
input(0,'feature');act('bad_negation',[m=>buf(m,0),1]);act('determine_ambiguities');
for(const s of ['foo','foo:bar','foo=bar']){input(0,s);act('length_without_val',[m=>buf(m,0),s.length]);}
act('reset_duplicate_opt_detection');for(const i of [rowIndex('autopickup'),rowIndex('autopickup'),rowIndex('fruit')]){act('duplicate_opt_detection',[i]);act('complain_about_duplicate',[i]);}
input(0,'dummy');act('rejectoption',[m=>buf(m,0)]);input(0,'TELEPORT_OPTIONS_MISSING');assert.equal(act('nh_getenv',[m=>buf(m,0)]),null);
for(const n of [-1,0,1,2,5,256]){input(0,'');input(1,'one\ttwo\nthree');act('nmcpy',[m=>buf(m,0),m=>buf(m,1),n]);}
for(const s of ['plain','\\n','\\t','\\033','\\x41','\\mA','^A','\\123','\\999','\\x80','\\\\','\\q','^?','\\M-x']){input(0,s);input(1,'');act('escapes',[m=>buf(m,0),m=>buf(m,1)]);assert.deepEqual(modules[1].HEAPU8.slice(Number(buf(modules[1],1)),Number(buf(modules[1],1))+8192),modules[0].HEAPU8.slice(Number(buf(modules[0],1)),Number(buf(modules[0],1))+8192));comparisons++;}
for(const s of ['', 'a','<enter>','<esc>','^A','M-a','\\x41','27','999','<space>','<tab>','<delete>',String.fromCharCode(0xe9)]){input(0,s);act('txt2key',[m=>buf(m,0)]);}
for(const n of [0,1,2,3,4,5,255])act('set_menuobjsyms_flags',[n]);
for(const s of ['$)[%?+!=/(*`0_','$','$$','?+invalid','']){input(0,s);act('change_inv_order',[m=>buf(m,0)]);}
for(const s of ['warnings:123456','warnings:\\x80','warnings:','warnings:abcdefghijkl']){input(0,s);input(1,'warnings');act('warning_opts',[m=>buf(m,0),m=>buf(m,1)]);}
for(const m of modules)m.HEAPU8.set([65,66,67,68,69,70],Number(buf(m,0)));act('assign_warnings',[m=>buf(m,0)]);
for(const s of ['suppress_alert:3.7.0','suppress_alert:0.0.0','suppress_alert:bad']){input(0,s);input(1,'suppress_alert');act('feature_alert_opts',[m=>buf(m,0),m=>buf(m,1)]);}
for(const s of ['a:apply','M-a:annotate','mouse1:apply','bad','^A:apply','a:unknown']){input(0,s);act('parsebindings',[m=>buf(m,0)]);}
for(const n of ['reset_needed_visuals','count_cond','count_apes'])act(n);
input(0,'x');act('oc_to_str',[m=>buf(m,0),m=>buf(m,1)]);
for(const ch of [0,27,32,65,127,128,255]){act('illegal_menu_cmd_key',[ch]);act('get_menu_cmd_key',[ch]);act('map_menu_cmd',[ch]);}
act('add_menu_cmd_alias',[65,66]);act('get_menu_cmd_key',[66]);act('map_menu_cmd',[65]);
for(const flags of [0,1,2,3,0xffffffff]){input(0,'');act('collect_menu_keys',[m=>buf(m,0),flags,1]);}
reset();for(const n of ['ask_do_tutorial','doset_simple_menu','doset_simple','doset','query_msgtype','handle_add_list_remove']){modules.forEach(m=>{m._probe_menu(-1,0);m._probe_menu(0,-1);});input(0,'pattern');act(n,n==='handle_add_list_remove'?[m=>buf(m,0),0]:[]);}
input(0,'name');input(1,'value');act('doset_add_menu',[3,m=>buf(m,0),m=>buf(m,1),1,0]);
for(const list of [0,1])act('show_menu_controls',[3,list]);
for(const i of [0,1,2,3]){for(const m of modules)m.HEAPU8[Number(buf(m,0))]=i&1;act('term_for_boolean',[i,m=>buf(m,0)]);}
input(0,'autopickup');act('toggle_bool_option',[m=>buf(m,0)]);act('dotogglepickup');
for(const s of ['A',"'b'",'\\x41','\\033',"'\\n'",'',' ','\\x80',"'\\\\'",'bad']){input(0,s);act('sym_val',[m=>buf(m,0)]);}
for(const n of ['get_option_value'])for(const name of ['autopickup','fruit','role','not-an-option']){input(0,name);act(n,[m=>buf(m,0),0]);}
act('longest_option_name',[0,7]);input(0,'autopickup');act('set_option_mod_status',[m=>buf(m,0),4]);
for(const mask of [0n,1n,1n<<31n,1n<<63n,0xffffffffffffffffn])for(const n of ['set_wc_option_mod_status','set_wc2_option_mod_status'])act(n,[mask,4]);
for(const name of ['color','font_map','petattr','windowborders','not-an-option']){input(0,name);for(const n of ['is_wc_option','wc_supported','is_wc2_option','wc2_supported'])act(n,[m=>buf(m,0)]);}
for(const [type,name]of [[1,'mono'],[2,'serif'],[3,'fixed'],[4,'roman'],[5,'sans']]){input(0,name);act('wc_set_font_name',[type,m=>buf(m,0)]);input(0,name+'2');act('wc_set_font_name',[type,m=>buf(m,0)]);}
for(const s of ['menu white/black','message red/blue text yellow/green','unknown white/black','menu white','menu /black','menu white/black menu red/blue']){input(0,s);act('wc_set_window_colors',[m=>buf(m,0)]);}act('options_free_window_colors');
for(const n of ['heed_all_options','disregard_all_options'])act(n);for(const i of [-1,0,216,217])for(const n of ['heed_this_option','disregard_this_option'])act(n,[i]);
input(0,'row');for(const m of modules){m.HEAPU8[Number(buf(m,1))]=1;}act('enhance_menu_text',[m=>buf(m,0),256,0,m=>buf(m,1),m=>m._probe_data(1)]);
reset();act('set_playmode');
for(const s of ['apples','pears','apples']){input(0,s);act('fruitadd',[m=>buf(m,0),0]);}
for(const s of ['hello','world','']){input(0,s);act('next_opt',[3,m=>buf(m,0)]);}
console.log('OPTIONS expanded',comparisons,'comparisons;',exercised.size,'/224 functions; remaining',S.names.filter(n=>!exercised.has(n)));
// The original list owners use the configured regex ABI in both modules.
reset();
for(const typ of [-1,0,1,2,3,4,99])act('msgtype2name',[typ]);
assert.equal(act('test_regex_pattern',[0,0]),0n);
for(const pattern of ['^hello$','a.*b','[','']){input(0,pattern);clear();act('test_regex_pattern',[m=>buf(m,0),0]);}
for(const [typ,pattern]of [[1,'^hello$'],[2,'world'],[3,'repeat']]){input(0,pattern);assert.equal(act('msgtype_add',[typ,m=>buf(m,0)]),1n);}
assert.equal(act('msgtype_count'),3n);
for(const msg of ['hello','world','repeat','other'])for(const norep of [0,1]){input(0,msg);act('msgtype_type',[m=>buf(m,0),norep]);}
act('hide_unhide_msgtypes',[1,(1<<1)|(1<<3)]);input(0,'hello');assert.equal(act('msgtype_type',[m=>buf(m,0),0]),-1n);
act('hide_unhide_msgtypes',[0,0x7fffffff]);act('free_one_msgtype',[1]);assert.equal(act('msgtype_count'),2n);
for(const line of ['show "visible"','hide "hidden"','norep "again"','bogus "x"','hide','stop "["']){input(0,line);act('msgtype_parse_add',[m=>buf(m,0)]);}
for(const n of ['all_options_msgtypes','all_options_conds','all_options_menucolors']){act(n,[m=>m._probe_stringbuf()]);assert.equal(text(modules[1],modules[1]._probe_stringbuf_text()),text(reference,reference._probe_stringbuf_text()));comparisons++;}
const messageNodes=act('msgtype_count'),messageFreeBefore=freed(reference);act('msgtype_free');assert.equal(freed(reference)-messageFreeBefore,Number(messageNodes)*3,'pattern, regex structure and list node really freed');comparisons++;assert.equal(act('msgtype_count'),0n);
for(const mapping of ['"<gold"','">junk" # comment','"plain"','bad','"["','"x" trailing']){input(0,mapping);act('add_autopickup_exception',[m=>buf(m,0)]);}
assert.equal(act('count_apes'),3n);act('all_options_apes',[m=>m._probe_stringbuf()]);assert.equal(text(modules[1],modules[1]._probe_stringbuf_text()),text(reference,reference._probe_stringbuf_text()));comparisons++;
act('remove_autopickup_exception',[m=>field(m,'instance_globals_a',global(m,'ga'),'apelist')]);assert.equal(act('count_apes'),2n);const apeFreeBefore=freed(reference);act('free_autopickup_exceptions');assert.equal(freed(reference)-apeFreeBefore,6,'both native-owned autopickup nodes completely freed');comparisons++;assert.equal(act('count_apes'),0n);
// The char** result is real native storage and can point inside the input.
for(const [name,value,neg]of [['role','Wizard',0],['race','elf',0],['gender','female',0],['alignment','chaotic',0],['role','!cav !mon',0],['role','sam !val',0],['role','tour',1]]){reset();input(0,name);input(1,name+':'+value);for(const m of modules)new DataView(m.HEAPU8.buffer).setBigUint64(Number(buf(m,2)),0n,true);act('parse_role_opt',[rowIndex(name),neg,m=>buf(m,0),m=>buf(m,1),m=>buf(m,2)]);const out=modules.map(m=>nullable(m,new DataView(m.HEAPU8.buffer).getBigUint64(Number(buf(m,2)),true)));assert.equal(out[1],out[0]);comparisons++;act('get_cnf_role_opt',[rowIndex(name)]);act('freeroleoptvals');}
reset();act('can_set_perm_invent');act('option_help');
for(const m of modules)for(const n of ['assure_syscf_file','read_config_file'])m._probe_return(Object.keys(S.dependencies).indexOf(n),1n);
act('initoptions_init');act('initoptions_finish');assert.match(text(reference,reference._probe_catalogue()),/^1:1:fruit:human:Archeologist$/);comparisons++;
act('initoptions');act('all_options_strbuf',[m=>m._probe_stringbuf()]);assert.equal(text(modules[1],modules[1]._probe_stringbuf_text()),text(reference,reference._probe_stringbuf_text()));comparisons++;
console.log('OPTIONS all entries',comparisons,'comparisons;',exercised.size,'/224 functions; remaining',S.names.filter(n=>!exercised.has(n)));
// Real menu callbacks drive each source retry rather than simulating the loop.
const queueMenus=values=>modules.forEach(m=>{m._probe_menu(-1,0);values.forEach((v,i)=>m._probe_menu(i,v));});
const queueInputs=values=>{modules.forEach(m=>m._probe_input(-1,0n));values.forEach((s,i)=>{input(10,s);modules.forEach(m=>m._probe_input(i,buf(m,10)));});};
reset();queueMenus([...Array(24).fill(1),4]);queueInputs(Array.from({length:24},(_,i)=>'<owned'+i));act('handler_autopickup_exception');assert.equal(act('count_apes'),24n);assert.equal((text(reference,reference._probe_trace()).match(/What new autopickup/g)||[]).length,24);comparisons++;
queueMenus([2,0,4]);act('handler_autopickup_exception');assert.match(text(reference,reference._probe_trace()),/List of autopickup exceptions/);comparisons++;act('free_autopickup_exceptions');
reset();queueMenus([1,4]);queueInputs(['\x1b']);for(const m of modules){write(m,'instance_flags',global(m,'iflags'),'use_menu_color',1);write(m,'instance_flags',global(m,'iflags'),'perm_invent',1);}act('handler_menu_colors');assert.match(text(reference,reference._probe_trace()),/What new menucolor pattern/);assert.match(text(reference,reference._probe_trace()),/dep:update_inventory/,'ESC follows original shared cleanup');comparisons++;
reset();queueMenus([1,4]);queueInputs(['valid']);for(const m of modules)m._probe_return(Object.keys(S.dependencies).indexOf('query_color'),-1n);act('handler_menu_colors');assert.match(text(reference,reference._probe_trace()),/dep:query_color/);comparisons++;
reset();queueMenus([1,2,4]);queueInputs(['^menu_owned$']);act('handler_msgtype');assert.equal(act('msgtype_count'),1n);queueMenus([3,1,4]);act('handler_msgtype');assert.equal(act('msgtype_count'),0n);
reset();queueMenus([-1,-1]);act('doset_simple_menu');assert.equal((text(reference,reference._probe_trace()).match(/select:/g)||[]).length,1,'cancel is distinct from help');comparisons++;
reset();queueMenus([219,-1]);act('doset');assert.equal((text(reference,reference._probe_trace()).match(/select:/g)||[]).length,2,'source help edge reruns full options');comparisons++;
// Native callbacks can grow actual Wasm memory and reenter the same module.
reset();const beforeGrowth=modules.map(memoryCheckpoint);modules.forEach(m=>{m._probe_option(250,1n);m._probe_option(252,1n);});act('show_menu_controls',[3,1]);modules.forEach((m,i)=>assertMemoryGrowth(m,beforeGrowth[i]));assert.match(text(reference,reference._probe_trace()),/nested:/);comparisons++;
// A call-local service override must be restored after nested calls and throws.
const hm=modules[1],services=servicesByModule.get(hm),env=callOptions(services,undefined,'environment');
let outerCalls=0,innerCalls=0;
const outer=Object.create(services),inner=Object.create(services);outer.strlen=()=>10n;inner.strlen=()=>17n;outer.strncmpi=(...args)=>{outerCalls++;assert.equal(callOptions(inner,undefined,'match_optname',Number(buf(hm,0)),Number(buf(hm,1)),3,0),1);assert.equal(env.strlen(Number(buf(hm,0))),10n,'nested call restores outer facade');return services.strncmpi(...args);};inner.strncmpi=(...args)=>{innerCalls++;return services.strncmpi(...args);};
input(0,'autopickup');input(1,'autopickup');assert.equal(callOptions(outer,undefined,'match_optname',Number(buf(hm,0)),Number(buf(hm,1)),3,0),1);assert.ok(outerCalls>0&&innerCalls>0);comparisons++;
const throwing=Object.create(services);throwing.strlen=()=>12345n;throwing.strncmpi=()=>{throw Error('OPTIONS facade witness');};const sp=hm._probe_stack();assert.throws(()=>callOptions(throwing,undefined,'match_optname',Number(buf(hm,0)),Number(buf(hm,1)),3,0),/facade witness/);assert.equal(hm._probe_stack(),sp);assert.equal(env.strlen(Number(buf(hm,0))),10n,'throw restores plain facade');assert.equal(callOptions(services,undefined,'match_optname',Number(buf(hm,0)),Number(buf(hm,1)),3,0),1);comparisons++;
// A second actual JS module shares the dispatcher but owns independent backing.
const primarySnapshot=projection(hm),other=await hybridFactory({nethackPorted:ported});other.HEAPU8.set(Buffer.from('foo\0'),Number(other._probe_buffer(0)));other.HEAPU8.set(Buffer.from('foo\0'),Number(other._probe_buffer(1)));assert.equal(other._probe_call(S.names.indexOf('match_optname'),other._probe_buffer(0),other._probe_buffer(1),3n,0n,0n,0n),1n);other._probe_reset();other.HEAPU8.set(Buffer.from('autopickup\0'),Number(other._probe_buffer(0)));other._probe_call(S.names.indexOf('parseoptions'),other._probe_buffer(0),1n,1n,0n,0n,0n);assert.equal(new DataView(other.HEAPU8.buffer).getInt8(address(other,'flag',global(other,'flags'),'pickup')),1);assert.deepEqual(projection(hm),primarySnapshot);comparisons++;
assert.equal(exercised.size,224);console.log('OPTIONS private',comparisons,'exact comparisons; all224 functions, native callbacks/retries/growth and shared-dispatcher module isolation.');
// A negative menu item ID is not a negative selection count.
reset();queueMenus([-1,-1]);modules.forEach(m=>m._probe_option(254,1n));act('doset_simple_menu');assert.equal((text(reference,reference._probe_trace()).match(/select:/g)||[]).length,2);assert.equal(field(reference,'instance_globals_s',global(reference,'gs'),'simple_options_help'),1n);comparisons++;
// Pointer-valued menu selections retain actual ownership identity.
reset();for(const s of ['"one"','"two"']){input(0,s);act('add_autopickup_exception',[m=>buf(m,0)]);}queueMenus([3,1,4]);modules.forEach(m=>m._probe_option(253,1n));act('handler_autopickup_exception');assert.equal(act('count_apes'),1n);assert.match(text(reference,reference._probe_trace()),/ape0:/);comparisons++;act('free_autopickup_exceptions');
// Condition strings come from a scripted native producer; OPTIONS owns wrapping.
reset();const conditions=['cond_one_12345678901234567890','','!cond_two_12345678901234567890','cond_three_12345678901234567890'];queueInputs(conditions);modules.forEach(m=>m._probe_option(249,BigInt(conditions.length)));act('all_options_conds',[m=>m._probe_stringbuf()]);const condText=text(reference,reference._probe_stringbuf_text());assert.equal(condText,'OPTIONS=cond_one_12345678901234567890,!cond_two_12345678901234567890,\\\n        cond_three_12345678901234567890\n');assert.equal(text(modules[1],modules[1]._probe_stringbuf_text()),condText);comparisons++;
console.log('OPTIONS extended',comparisons,'exact comparisons.');
// Native lookup results are scripted; fruitadd itself owns every list update.
reset();input(0,'owned-fruit');assert.equal(act('fruitadd',[m=>buf(m,0),0]),1n);
const fruitHead=m=>field(m,'instance_globals_f',global(m,'gf'),'ffruit');
for(const m of modules)m._probe_return(Object.keys(S.dependencies).indexOf('fruit_from_name'),fruitHead(m));
input(0,'owned-fruit');assert.equal(act('fruitadd',[m=>buf(m,0),0]),1n,'existing native node takes original nonew edge');
for(const m of modules){const a=address(m,'instance_globals_saved_p',global(m,'svp'),'pl_fruit');m.HEAPU8.set(Buffer.from('replacement\0'),a);}
assert.equal(act('fruitadd',[m=>address(m,'instance_globals_saved_p',global(m,'svp'),'pl_fruit'),fruitHead]),1n,'replace preserves original node ID');
assert.equal(field(reference,'context_info',address(reference,'instance_globals_saved_c',global(reference,'svc'),'context'),'current_fruit'),1n);comparisons++;
for(const m of modules){m._probe_return(Object.keys(S.dependencies).indexOf('fruit_from_name'),0n);m._probe_option(247,1n);m._probe_option(248,127n);}
input(0,'overflow-fruit');clear();const chosenFruit=act('fruitadd',[m=>buf(m,0),0]);assert.ok(chosenFruit>=1n&&chosenFruit<=127n);assert.match(text(reference,reference._probe_trace()),/rng:options\.c:fruitadd:8273:127:/);comparisons++;
input(0,'fruit');input(1,'');act('optfn_fruit',[rowIndex('fruit'),2,1,m=>buf(m,0),m=>buf(m,1)]);assert.equal(text(reference,address(reference,'instance_globals_saved_p',global(reference,'svp'),'pl_fruit')),'slime mold','negated fruit reaches goodfruit common tail');comparisons++;
console.log('OPTIONS complete proof',comparisons,'exact comparisons, all224 original functions.');
// A failed first constructor must not publish a partially packed environment.
let rejectInitial=true;const rejecting={nativeRegex:ported.nativeRegex,callOptions(s,n,...a){if(rejectInitial){rejectInitial=false;const temporary=Object.create(s);temporary.literal=()=>{throw Error('OPTIONS initial packing witness');};return callOptions(temporary,undefined,n,...a);}return callOptions(s,undefined,n,...a);}};
const retryModule=await hybridFactory({nethackPorted:rejecting});for(const i of [0,1])retryModule.HEAPU8.set(Buffer.from('foo\0'),Number(retryModule._probe_buffer(i)));const callRetry=()=>retryModule._probe_call(S.names.indexOf('match_optname'),retryModule._probe_buffer(0),retryModule._probe_buffer(1),3n,0n,0n,0n);assert.throws(callRetry,/initial packing witness/);assert.equal(callRetry(),1n);assert.equal(text(retryModule,field(retryModule,'allopt_t',retryModule._probe_data(0),'name')),'windowtype');assert.ok(retryModule.HEAPU8.slice(Number(retryModule._probe_data(1)),Number(retryModule._probe_data(1))+218*L['size:struct allopt_t']).every(v=>v===0));comparisons++;
console.log('OPTIONS final',comparisons,'exact comparisons; original C oracle, all224 entries and guarded callback/data lifetimes.');
// Actual native menucolor records feed OPTIONS' list and reverse serialization.
reset();input(8,'first-color');input(9,'second-color');const nativeColors=modules.map(m=>{const bytes=L['size:struct menucoloring'],nodes=[m._malloc(bytes),m._malloc(bytes)];for(const n of nodes)m.HEAPU8.fill(0,Number(n),Number(n)+bytes);nodes.forEach((n,i)=>{write(m,'menucoloring',n,'origstr',buf(m,8+i));write(m,'menucoloring',n,'color',i+1);write(m,'menucoloring',n,'attr',0);write(m,'menucoloring',n,'next',i?0:nodes[1]);});write(m,'instance_globals_m',global(m,'gm'),'menu_colorings',nodes[0]);m._probe_return(Object.keys(S.dependencies).indexOf('count_menucolors'),2n);return nodes;});
act('all_options_menucolors',[m=>m._probe_stringbuf()]);const colorConfig=text(reference,reference._probe_stringbuf_text());assert.equal(text(modules[1],modules[1]._probe_stringbuf_text()),colorConfig);assert.ok(colorConfig.indexOf('second-color')<colorConfig.indexOf('first-color'),'source reverses the actual native linked list');comparisons++;
queueMenus([2,0,4]);clear();act('handler_menu_colors');assert.match(text(reference,reference._probe_trace()),/"first-color"/);assert.match(text(reference,reference._probe_trace()),/"second-color"/);comparisons++;
modules.forEach((m,i)=>{write(m,'instance_globals_m',global(m,'gm'),'menu_colorings',0);nativeColors[i].forEach(n=>m._free(n));});check();
console.log('OPTIONS final checked',comparisons,'exact comparisons; all224 configured functions.');
// Static and interior returned pointers retain the original native aliasing.
reset();input(0,'autopickup');act('get_option_value',[m=>buf(m,0),0]);const optionBuffers=modules.map(m=>m._probe_result());input(0,'fruit');act('get_option_value',[m=>buf(m,0),0]);modules.forEach((m,i)=>assert.equal(m._probe_result(),optionBuffers[i],'same original retbuf across option handlers'));comparisons++;
input(0,'foo:bar');act('string_for_opt',[m=>buf(m,0),0]);modules.forEach(m=>assert.equal(m._probe_result(),buf(m,0)+4n,'interior pointer is not a duplicated string'));comparisons++;
input(0,'foo');act('string_for_opt',[m=>buf(m,0),0]);modules.forEach(m=>assert.equal(m._probe_result(),m._probe_data(st('empty_optstr')),'empty result is the original non-NULL static object'));comparisons++;
for(const m of modules){const base=address(m,'instance_flags',global(m,'iflags'),'wcolors');for(const[name,member]of [['fgp','fg'],['bgp','bg']])for(let i=0;i<4;i++){const p=new DataView(m.HEAPU8.buffer).getBigUint64(Number(m._probe_data(st(name)))+i*8,true);assert.equal(p,BigInt(address(m,'windowcolors_struct',base+L[['wcolor_menu','wcolor_message','wcolor_status','wcolor_text'][i]]*L['size:struct windowcolors_struct'],member)),'native '+name+' pointer cell '+i);comparisons++;}}
console.log('OPTIONS frozen candidate',comparisons,'exact comparisons; 224 functions and original aliases.');
// The original header's logging-disabled branch calls rnd without attribution.
reset();modules.forEach(m=>{m._probe_option(240,1n);m._probe_option(247,1n);m._probe_option(248,127n);});input(0,'unlogged-overflow');clear();const unloggedFruit=act('fruitadd',[m=>buf(m,0),0]);assert.ok(unloggedFruit>=1n&&unloggedFruit<=127n);assert.match(text(reference,reference._probe_trace()),/rng:::0:127:/);comparisons++;
console.log('OPTIONS final acceptance',comparisons,'exact comparisons; all224 original entries.');
