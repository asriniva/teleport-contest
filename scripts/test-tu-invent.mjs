import assert from 'node:assert/strict';
import {readFile} from 'node:fs/promises';
import {resolve,dirname,join} from 'node:path';
import {fileURLToPath,pathToFileURL} from 'node:url';
if(process.env.TELEPORT_NATIVE_TESTS!=='0')throw Error('INVENT has no native reference fixture; Emscripten results cannot be labeled native.');
const root=resolve(dirname(fileURLToPath(import.meta.url)),'..'),dir=resolve(process.env.INVENT_PROBE_DIR??join(root,'.cache/invent-first-pass'));
const {callInvent,createInventEnvironment}=await import(pathToFileURL(resolve(process.env.INVENT_RUNTIME_PATH??join(root,'js/ported/invent-runtime.js'))).href);
const schema=JSON.parse(await readFile(join(root,'nethack-c/wasm/tu-fragments/invent-schema.json'),'utf8'));const inventory={names:schema.names,functions:Object.fromEntries(Object.entries(schema.functionParameters).map(([name,args])=>[name,{args}]))};
const factories=await Promise.all(['reference','hybrid'].map(async mode=>(await import(pathToFileURL(join(dir,`invent-${mode}.mjs`)).href)).default));
const factoryServices=new Map();
const checkedInvent=(services,name,...args)=>{let seen=factoryServices.get(services.moduleKey);if(!seen)factoryServices.set(services.moduleKey,seen=new Set());seen.add(services);const frame=services.stackSave();try{return callInvent(services,name,...args);}finally{assert.equal(services.stackSave(),frame,'INVENT bridge restores own source frames before external cleanup');}};
const mods=[await factories[0](),await factories[1]({nethackPorted:{invent:checkedInvent}})];
const decode=(m,p)=>{const b=BigInt(p);assert.ok(b>0n&&b<BigInt(m.HEAPU8.length),'declared string fits memory');let a=Number(b),e=a;while(e<m.HEAPU8.length&&m.HEAPU8[e])e++;assert.ok(e<m.HEAPU8.length);return new TextDecoder().decode(m.HEAPU8.subarray(a,e));};
const constant=n=>{const i=schema.layoutKeys.indexOf(n);assert.ok(i>=0,n);return Number(mods[0]._probe_layout(i));};
const kinds=Object.keys(schema.schema),kind=n=>{const k=kinds.indexOf(n);assert.ok(k>=0,n);return k;};
const fields=n=>schema.schema[n].fields,fi=(n,f)=>{const i=fields(n).findIndex(v=>v.name===f);assert.ok(i>=0,n+'.'+f);return i;};
const ptr=(m,k,i=0)=>m._probe_record(k,i),global=(m,n)=>{const i=schema.globals.findIndex(g=>g.name===n);assert.ok(i>=0,n);return m._probe_global(i);};
const address=(m,at,n,f)=>m._probe_address(kind(n),at,fi(n,f));
const record=(m,at,n,f,v)=>m._probe_write(kind(n),at,fi(n,f),BigInt.asUintN(64,BigInt(v)));
const get=(m,at,n,f)=>m._probe_read(kind(n),at,fi(n,f));
const pathinfo=(m,path)=>{const[g,...tail]=path.split('.');let at=global(m,g),type=schema.globals.find(x=>x.name===g).canonical;for(let i=0;i<tail.length-1;i++){const n=type.replace(/^(struct|union) /,''),f=tail[i];at=address(m,at,n,f);type=fields(n)[fi(n,f)].canonical;}return {at,n:type.replace(/^(struct|union) /,''),f:tail.at(-1)};};
const field=(m,path,v)=>{const{at,n,f}=pathinfo(m,path);record(m,at,n,f,v);};
const fieldAddress=(m,path)=>{if(!path.includes('.'))return global(m,path);const{at,n,f}=pathinfo(m,path);return address(m,at,n,f);};
const put=(m,p,s)=>m.HEAPU8.set(new TextEncoder().encode(s+'\0'),Number(p)),buffer=(m,s,i=0)=>put(m,m._probe_buffer(i),s),option=(m,k,v=1)=>m._probe_option(k,BigInt(v));
const write64=(m,p,v)=>new DataView(m.HEAPU8.buffer).setBigUint64(Number(p),BigInt.asUintN(64,BigInt(v)),true);
const call=(m,n,args=[])=>{const i=inventory.names.indexOf(n);assert.ok(i>=0,n);const p=m._malloc(96n);try{for(let j=0;j<12;j++)write64(m,BigInt(p)+BigInt(j*8),args[j]??0);return m._probe_call(i,BigInt(p));}finally{m._free(p);}};
const callback=(m,k=0)=>m._probe_callback(k),func=(m,n)=>m._probe_function(schema.functionAddresses.indexOf(n));
const trace=m=>decode(m,m._probe_trace()),snapshot=m=>decode(m,m._probe_snapshot());
const objid=(m,v)=>{const raw=BigInt(v);if(!raw)return 'NULL';if(raw===global(m,'hands_obj'))return 'HANDS';for(let i=0;i<16;i++)if(raw===ptr(m,0,i))return 'obj'+i;throw Error('unclassified returned object '+raw);};
const strret=new Set(['loot_xname','currency','getobj_hands_txt','safeq_xprname','safeq_shortxprname','xprname','dfeature_at','let_to_name','cinv_doname','cinv_ansimpleoname']);
const objret=new Set(['merge_choice','addinv_core0','addinv','addinv_before','addinv_nomerge','hold_another_object','sobj_at','nxtobj','carrying','carrying_stoning_corpse','u_carried_gloves','o_on','g_at','getobj','find_unpaid','display_minventory']);
const lootResult=(m,p)=>{const out=[];if(!p)return null;for(let i=0;i<32;i++){const at=BigInt(p)+BigInt(i*24),o=get(m,at,'sortloot_item','obj');out.push([objid(m,o),...['indx','orderclass','subclass','disco','inuse'].map(f=>String(get(m,at,'sortloot_item',f)))]);if(!o)return out;}throw Error('unterminated Loot');};
const result=(m,n,v)=>strret.has(n)?v?decode(m,v):null:objret.has(n)?objid(m,v):n==='sortloot'?lootResult(m,v):String(v);
let checks=0;const invoked=new Set(),equal=(a,b,label)=>{assert.deepEqual(b,a,label);checks++;};
const defaults={
inuse_classify:m=>[ptr(m,3),ptr(m,0)],loot_classify:m=>[ptr(m,3),ptr(m,0)],loot_xname:m=>[ptr(m,0)],invletter_value:()=>[97],sortloot_cmp:m=>[ptr(m,3),ptr(m,3,1)],sortloot:m=>[ptr(m,2),0,0,0],unsortloot:m=>[ptr(m,4)],assigninvlet:m=>[ptr(m,0)],merge_choice:m=>[0,ptr(m,0)],merged:m=>[ptr(m,2),ptr(m,2,1)],addinv_core0:m=>[ptr(m,0),0,0],addinv_before:m=>[ptr(m,0),0],hold_another_object:m=>[ptr(m,0),m._probe_buffer(1),m._probe_buffer(0),m._probe_buffer(0)],consume_obj_charge:m=>[ptr(m,0),0],delallobj:()=>[12,10],delobj_core:m=>[ptr(m,0),0],sobj_at:()=>[34,12,10],nxtobj:m=>[ptr(m,0),constant('WEAPON_CLASS'),0],carrying:()=>[34],currency:()=>[1n],o_on:m=>[1,ptr(m,0)],obj_here:m=>[ptr(m,0),12,10],g_at:()=>[12,10],compactify:m=>[m._probe_buffer(0)],taking_off:m=>[m._probe_buffer(0)],mime_action:m=>[m._probe_buffer(0)],getobj_hands_txt:m=>[m._probe_buffer(0),m._probe_buffer(1)],getobj:m=>[m._probe_buffer(0),callback(m),0],silly_thing:m=>[m._probe_buffer(0),ptr(m,0)],ggetobj:m=>[m._probe_buffer(0),callback(m,2),0,0,ptr(m,4)],askchain:m=>[ptr(m,2),0,1,callback(m,2),0,0,m._probe_buffer(0)],prinv:m=>[m._probe_buffer(0),ptr(m,0),0n],xprname:m=>[ptr(m,0),0,97,1,0n,0n],dispinv_with_action:m=>[0,0,0],find_unpaid:m=>[0,ptr(m,2)],display_pickinv:m=>[0,0,0,0,0,ptr(m,4)],display_inventory:()=>[0,0],display_used_invlets:()=>[0],count_unidentified:()=>[0],count_unpaid:()=>[0],count_buc:()=>[0,0,0],tally_BUCX:m=>[0,0,...Array.from({length:6},(_,i)=>ptr(m,4,i))],count_contents:m=>[ptr(m,0),0,0,0,0],dounpaid:()=>[0,0,0],dfeature_at:m=>[12,10,m._probe_buffer(0)],look_here:()=>[0,0],will_feel_cockatrice:m=>[ptr(m,0),0],feel_cockatrice:m=>[ptr(m,0),0],mergable:m=>[ptr(m,0),ptr(m,0,1)],noarmor:()=>[0],useupf:m=>[ptr(m,0),1n],let_to_name:()=>[constant('WEAPON_CLASS'),0,0],check_invent_gold:m=>[m._probe_buffer(0)],invdisp_nothing:m=>[m._probe_buffer(0),m._probe_buffer(1)],display_minventory:m=>[ptr(m,1),0,0],display_binventory:()=>[12,10,0],prepare_perminvent:()=>[17],perm_invent_toggled:()=>[1]};
for(const n of ['menu_identify','identify_pack'])defaults[n]=()=>[0,0];
const argsFor=(m,n)=>defaults[n]?.(m)??(inventory.functions[n].args.length?[ptr(m,0)]:[]);
const setupBase=(m,n)=>{buffer(m,'drop');buffer(m,'%s',1);record(m,ptr(m,3),'sortloot_item','obj',ptr(m,0));record(m,ptr(m,3,1),'sortloot_item','obj',ptr(m,0,1));write64(m,ptr(m,2),ptr(m,0));write64(m,ptr(m,2,1),ptr(m,0,1));if(['useup','useupall','freeinv','freeinv_core','doorganize_core','adjust_split'].includes(n)){m._probe_chain(-1,0,0);record(m,ptr(m,0),'obj','where',3);}if(n==='sortloot')write64(m,ptr(m,2),0);if(n==='doorganize_core')option(m,9,27);};
const run=(label,n,setup=()=>{},args=m=>argsFor(m,n),expectedError=null)=>{const outputs=mods.map(m=>{m._probe_reset();setupBase(m,n);setup(m);const a=args(m),sp=m.stackSave();let v=0n,error=null;try{v=call(m,n,a);}catch(e){error=e.message;if(process.env.INVENT_DEBUG)console.error(e.stack);}finally{m.stackRestore(sp);}invoked.add(n);return{result:error?null:result(m,n,v),error,trace:trace(m),state:snapshot(m),loot:['inuse_classify','loot_classify'].includes(n)?lootResult(m,ptr(m,3)):null,buffers:[0,1].map(i=>decode(m,m._probe_buffer(i)))};});equal(outputs[0],outputs[1],label+' '+n);if(expectedError){assert.match(outputs[0].error??'',expectedError);checks++;}else if(outputs[0].error)throw Error(label+' '+n+' failed in actual original reference: '+outputs[0].error);return outputs[0];};
for(const n of inventory.names){if(process.env.INVENT_ONE&&process.env.INVENT_ONE!==n)continue;run('configured valid body',n);}
const chain=(m,count=4)=>{for(let i=0;i<count;i++){record(m,ptr(m,0,i),'obj','where',3);m._probe_chain(i,i+1<count?i+1:-1,0);}m._probe_chain(-1,count?0:-1,0);};
const objset=(m,i,values)=>{for(const[k,v]of Object.entries(values))record(m,ptr(m,0,i),'obj',k,v);};
const catalogueSize=482;
for(let i=0;i<catalogueSize;i++)run('real catalogue classify '+i,'loot_classify',m=>{record(m,ptr(m,0),'obj','otyp',i);const stride=constant('size:struct objclass');const at=global(m,'objects')+BigInt(i*stride);record(m,ptr(m,0),'obj','oclass',m._probe_class(i));record(m,ptr(m,0),'obj','dknown',i%2);record(m,ptr(m,0),'obj','known',(i>>1)%2);});
for(const mask of [0n,1n,2n,4n,8n,16n,32n,64n,256n,512n,1024n,65536n,131072n,262144n,524288n,0x100000000n,-1n,-9223372036854775808n])for(const handed of [0,1,2])run('inuse width '+mask+'/'+handed,'inuse_classify',m=>{objset(m,0,{owornmask:mask});field(m,'u.uhandedness',handed);});
for(const mode of [0,1,2,3,4,5,8,9,15,255,0xffffffff])for(const bynext of [0,1])for(const filter of [0,1])run('real deterministic sort '+mode+'/'+bynext+'/'+filter,'sortloot',m=>{chain(m,8);for(let i=0;i<8;i++){objset(m,i,{invlet:[36,97,90,35,65,122,98,66][i],owornmask:BigInt([0,256,65536,64,16,512,0,0][i]),bknown:i%2,blessed:(i>>1)%2,cursed:(i>>2)%2,spe:i-4});if(bynext){const union=address(m,ptr(m,0,i),'obj','v');record(m,union,'vptrs','v_nexthere',i<7?ptr(m,0,i+1):0);}}option(m,41,filter);},m=>[ptr(m,2),mode,bynext,filter?callback(m,1):0]);
for(const c of [-128,-1,0,35,36,64,65,90,91,96,97,122,123,127,128,255,256])run('char invlet '+c,'invletter_value',()=>{},()=>[c]);
for(const name of ['compactify','taking_off','mime_action','getobj_hands_txt'])for(const text of ['', 'abc', 'abcdef', 'abczABCD', 'abcdeghijklz', 'take off', 'remove', 'put on', 'drop', 'rub or apply', 'throw or fire', 'use or wield'])run('text '+text,name,m=>buffer(m,text));
for(const amount of [-9223372036854775808n,-9007199254740997n,-1n,0n,1n,2n,9007199254740997n,9223372036854775807n])for(const halluc of [0,1])for(const blocked of [0,1])for(const logged of [0,1])run('currency exact '+amount+'/'+halluc+'/'+blocked+'/'+logged,'currency',m=>{m._probe_property(constant('HALLUC'),BigInt(halluc),0n);m._probe_property(constant('HALLUC_RES'),BigInt(blocked),0n);option(m,12,logged);},()=>[amount]);
for(const name of ['count_unidentified','count_unpaid','count_buc','count_contents','find_unpaid','u_have_novel','u_carried_gloves','carrying','is_worn','is_inuse','this_type_only','worn_wield_only','tool_being_used','any_obj_ok','adjust_ok','adjust_gold_ok'])for(const state of [0,1,2,3,7,15])run('nonempty chain '+state,name,m=>{chain(m);for(let i=0;i<4;i++)objset(m,i,{known:state&1,dknown:(state>>1)&1,bknown:(state>>2)&1,rknown:(state>>3)&1,unpaid:i%2,blessed:i===1,cursed:i===2,quan:BigInt(i+1),owornmask:BigInt(i%2?256:0)});},m=>name==='count_unidentified'||name==='count_unpaid'?[ptr(m,0)]:name==='count_buc'?[ptr(m,0),state%4,0]:name==='count_contents'?[ptr(m,0),1,1,1,0]:name==='find_unpaid'?[ptr(m,0),ptr(m,2,3)]:argsFor(m,name));
for(const quantity of [1n,2n,0x100000001n,0x20000000000001n,9223372036854775806n])for(const countQuantity of [0,1])run('count_contents LP64 '+quantity+'/'+countQuantity,'count_contents',m=>{m._probe_chain(0,1,1);objset(m,1,{quan:quantity,where:2});},m=>[ptr(m,0),1,countQuantity,1,0]);
for(const age of [-9007199254740997n,-3n,0n,9007199254740997n])for(const count of [1n,2n,3n])run('merged signed64 age '+age+'/'+count,'merged',m=>{objset(m,0,{quan:count,age});objset(m,1,{quan:1n,age:age+1n});});
for(const type of [1,2,3,5,8,10,17])for(const unpaid of [0,1])for(const showsym of [0,1])run('class description '+type+'/'+unpaid+'/'+showsym,'let_to_name',()=>{},()=>[type,unpaid,showsym]);
for(const cost of [-9007199254740997n,0n,1n,0x100000001n,9007199254740997n])for(const quan of [0n,1n,0x100000001n,9007199254740997n])for(const letter of [0,36,97,255])run('formatted fullwidth '+cost+'/'+quan+'/'+letter,'xprname',m=>objset(m,0,{quan:9007199254740997n}),m=>[ptr(m,0),0,letter,1,cost,quan]);
for(const n of ['reorder_invent','reassign','assigninvlet','check_invent_gold','learn_unseen_invent','identify_pack','ggetobj','askchain','display_inventory','display_pickinv','display_used_invlets','reroll_menu','dotypeinv','doorganize_core'])for(const mode of [0,1,2])run('nonempty behavior '+mode,n,m=>{chain(m,4);for(let i=0;i<4;i++)objset(m,i,{invlet:[100,65,99,98][i],spe:i,quan:BigInt(i+1),known:i%2,dknown:i%2});field(m,'flags.sortpack',mode===1);field(m,'flags.sortloot',mode===2?105:102);option(m,9,27);option(m,40,constant('GETOBJ_SUGGEST'));option(m,42,1);},n==='askchain'?m=>[ptr(m,2),0,1,callback(m,2),0,2,m._probe_buffer(0)]:n==='getobj'?m=>[m._probe_buffer(0),callback(m),0]:m=>argsFor(m,n));
for(const n of ['getobj','display_inventory'])for(const queued of [97,98,35,45,90])for(const count of [0n,1n,2n,0x100000001n])run('native command queue '+queued+'/'+count,n,m=>{chain(m,3);objset(m,0,{quan:0x20000000000001n});option(m,40,constant('GETOBJ_SUGGEST'));if(count)m._probe_queue(constant('CMDQ_INT'),count);m._probe_queue(constant('CMDQ_KEY'),BigInt(queued));},m=>n==='getobj'?[m._probe_buffer(0),callback(m),1]:[0,1]);
for(const n of ['display_pickinv','display_inventory','display_used_invlets','reroll_menu'])for(const halluc of [0,1])for(const sel of [-1,0,1])run('native menu/display RNG '+halluc+'/'+sel,n,m=>{chain(m,3);field(m,'flags.sortpack',1);field(m,'iflags.force_invmenu',1);m._probe_property(constant('HALLUC'),BigInt(halluc),0n);option(m,14,sel);m.HEAPU8[Number(ptr(m,5))]=97;write64(m,ptr(m,5)+8n,0x20000000000001n);},m=>n==='display_pickinv'?[0,0,0,0,1,ptr(m,4)]:argsFor(m,n));
for(const invmode of [1,2,3,7,8,15,0x7fffffff])for(const mask of [0n,1n,0x100000001n,0x20000000000001n,-1n])run('foreign full48 mutable padding '+invmode+'/'+mask,'prepare_perminvent',m=>{field(m,'iflags.perminv_mode',0);call(m,'prepare_perminvent',[17]);m._probe_clear();m._probe_foreign(mask,0xa5);field(m,'iflags.perminv_mode',invmode);});
for(const returned of [0,1])for(const flags of [0n,1n,2n,4n,8n,0x100000000n])run('perminvent returned live alias '+returned+'/'+flags,'sync_perminvent',m=>{field(m,'iflags.perm_invent',1);field(m,'iflags.perminv_mode',1);option(m,4,returned);option(m,5,!returned);field(m,'program_state.beyond_savefile_load',1);const at=address(m,ptr(m,6),'win_request_info_t','tocore');record(m,at,'to_core','tocore_flags',flags);record(m,at,'to_core','maxslot',52);});
for(const n of ['loot_xname','sortloot','askchain','display_pickinv','xprname','display_minventory','prepare_perminvent','update_inventory'])for(const opt of [30,32])run('callback growth/reentry '+opt,n,m=>{chain(m,3);option(m,opt);option(m,42,1);field(m,'program_state.in_moveloop',1);field(m,'iflags.perminv_mode',7);},m=>argsFor(m,n));


// The exact source-typed pointer slots are observed as BigUint64 before Number.
const raw64=v=>{const b=new Uint8Array(8);new DataView(b.buffer).setBigUint64(0,BigInt.asUintN(64,v),true);return Array.from(b);};
for(const m of mods){const known=ptr(m,0);const observe=p=>{const at=m._probe_observe(p,known),dv=new DataView(m.HEAPU8.buffer),po=m._probe_offset(0),so=m._probe_offset(1),bo=m._probe_offset(2),bits=dv.getBigUint64(Number(at)+po,true);return{pointer:bits===0n?{kind:'null'}:bits===known?{kind:'known',id:'object'}:{kind:'unknown',decimal:String(bits),bytes:Array.from(m.HEAPU8.subarray(Number(at)+po,Number(at)+po+8))},scalar:dv.getBigInt64(Number(at)+so,true),scalarBytes:Array.from(m.HEAPU8.subarray(Number(at)+so,Number(at)+so+8)),padding:Array.from(m.HEAPU8.subarray(Number(at)+bo,Number(at)+bo+8))};};const a=0x20000000000000n,b=a+1n,one=observe(a),two=observe(b);equal(Number(a),Number(b),'unknown pointer witness collides under Number');equal(one.pointer,{kind:'unknown',decimal:String(a),bytes:raw64(a)},'first exact unknown pointer');equal(two.pointer,{kind:'unknown',decimal:String(b),bytes:raw64(b)},'second exact unknown pointer');assert.notDeepEqual(one.pointer,two.pointer);checks++;equal(two.scalar,known,'address-shaped scalar stays full signed64');equal(two.scalarBytes,raw64(known),'address-shaped scalar bytes stay raw');equal(two.padding,Array(8).fill(0xa5),'padding stays raw');}
for(const name of ['loot_xname','display_pickinv','askchain','xprname','update_inventory'])run('controlled callback throw',name,m=>{chain(m,3);option(m,31);option(m,42,1);field(m,'program_state.in_moveloop',1);},m=>argsFor(m,name),/INVENT controlled callback/);
const getMenu=run('getobj redo_menu live input and full64 out-count','getobj',m=>{chain(m,3);objset(m,0,{quan:0x20000000000001n});option(m,9,63);option(m,40,constant('GETOBJ_SUGGEST'));option(m,14,1);option(m,43,1);for(const[i,c]of [42,63,97].entries()){m.HEAPU8[Number(ptr(m,5,i))]=c;write64(m,ptr(m,5,i)+8n,2n);}},m=>[m._probe_buffer(0),callback(m),1]);
assert.equal(getMenu.result,'obj15','getobj menu count must split selected native stack');assert.equal((getMenu.trace.match(/select:/g)??[]).length,3,'redo_menu must perform all three selections');checks+=2;
for(const name of ['doorganize_core'])for(const letter of [27,36,65,90,98])run('organize exact goto cleanup '+letter,name,m=>{chain(m,3);option(m,9,letter);},m=>argsFor(m,name));
for(const m of mods){m._probe_reset();buffer(m,'first');const p=call(m,'xprname',[0,m._probe_buffer(0),97,0,0n,0n]);buffer(m,'second');const q=call(m,'xprname',[0,m._probe_buffer(0),98,0,0n,0n]);equal(p,q,'source static li address remains stable');assert.match(decode(m,p),/second/);checks++;
 field(m,'iflags.perminv_mode',1);call(m,'prepare_perminvent',[17]);const one=m._probe_held();field(m,'iflags.perminv_mode',2);call(m,'prepare_perminvent',[17]);equal(m._probe_held(),one,'private wri_info address stays native and stable across full copies');}
const another=[await factories[0](),await factories[1]({nethackPorted:{invent:checkedInvent}})];
for(let i=0;i<2;i++){const a=mods[i],b=another[i];a._probe_reset();b._probe_reset();buffer(a,'Module A');buffer(b,'Module B');const p=call(a,'xprname',[0,a._probe_buffer(0),97,0,0n,0n]);call(b,'xprname',[0,b._probe_buffer(0),98,0,0n,0n]);assert.match(decode(a,p),/Module A/);checks++;}
assert.throws(()=>createInventEnvironment({layout:()=>9007199254740993n}),/layout exceeds exact scalar range/);checks++;


for(const quan of [1n,0x100000001n,9007199254740997n])for(const name of ['prinv','useupf'])run('remaining long formal '+quan,name,m=>objset(m,0,{quan:quan+1n}),m=>name==='prinv'?[m._probe_buffer(0),ptr(m,0),quan]:[ptr(m,0),quan]);
const lifetime=run('fixed native automatic identity over menu loop','display_pickinv',m=>{chain(m,16);field(m,'iflags.force_invmenu',1);option(m,36);},m=>[0,0,0,0,0,ptr(m,4)]);
assert.equal((lifetime.trace.match(/menu-stack:/g)??[]).length,16);assert.ok([...lifetime.trace.matchAll(/menu-stack:(-?\d+);/g)].every(m=>m[1]==='0'),'each iteration reuses its native automatic glyph_info');checks+=2;
const forcedCopy=run('independent optimized foreign48/padding witness','prepare_perminvent',m=>{field(m,'iflags.perminv_mode',0);call(m,'prepare_perminvent',[17]);m._probe_clear();m._probe_foreign(0x20000000000001n,0xa5);field(m,'iflags.perminv_mode',7);});
assert.match(forcedCopy.trace,/ctrl:17\//);const copied=forcedCopy.trace.match(/ctrl:[^:]+:([0-9a-f]{96});/)[1];assert.ok(copied.endsWith('a5'.repeat(8)),'full48 copy preserves foreign tail and padding');assert.ok(copied.startsWith('0100000000002000'),'signed64 flags retain independent lowbit');checks+=3;


for(const[i,name]of schema.functionAddresses.entries()){const outputs=mods.map(m=>{m._probe_reset();setupBase(m,name);const pointer=m._probe_function(i);assert.ok(pointer>0n,'native callable identity '+name);checks++;const value=m._probe_invoke(i),type=schema.functionTypes[name]??schema.dependencies[name].type;return{result:/^(const )?char \*/.test(type)?decode(m,value):String(value),trace:trace(m),state:snapshot(m)};});equal(outputs[0],outputs[1],'actual typed native function-pointer call '+name);}

console.log(JSON.stringify({backend:'Emscripten O2 memory64 original invent.c vs JS',checks,configuredFunctions:invoked.size,native:false,limits:'Controlled foreign game/naming/menu dependencies; real hacklib/strutil/catalogues/libc. Native/full-game/public pending.'},null,2));

// Added valid incoming/floor/inventory graphs exercise true merged() calls.
for(const m of mods){
 m._probe_reset();const typ=Number(get(m,ptr(m,0),'obj','otyp'));
 assert.equal(m._probe_class(typ),constant('WEAPON_CLASS'),'actual upstream object globals initializer supplies weapon class');
 const monster=get(m,ptr(m,1),'monst','data');
 assert.notEqual(get(m,monster,'permonst','mlet'),0n,'actual upstream monster globals initializer supplies human class');
}

const mergePair=(m,incoming=false)=>{
 objset(m,0,{where:incoming?0:3,quan:2,ox:12,oy:10,invlet:97});
 objset(m,1,{where:3,quan:3,ox:12,oy:10,invlet:98});
 assert.equal(call(m,'mergable',[ptr(m,0),ptr(m,0,1)]),1n,'actual original mergable must accept this native pair');
};
const addMerge=run('positive addressed incoming parameter inventory merge','addinv_core0',m=>{
 mergePair(m,true);m._probe_chain(-1,1,0);
},m=>[ptr(m,0),0,0]);
assert.equal(addMerge.result,'obj1');
for(const m of mods)assert.equal(get(m,ptr(m,0,1),'obj','quan'),5n,'merged quantity proves positive inventory branch');
const quiverMerge=run('positive global and formal pointer cells quiver merge','addinv_core0',m=>{
 mergePair(m,true);objset(m,2,{where:3,quan:7,invlet:99});m._probe_chain(-1,2,0);m._probe_chain(2,1,0);write64(m,global(m,'uquiver'),ptr(m,0,1));
},m=>[ptr(m,0),0,0]);
assert.equal(quiverMerge.result,'obj1');
for(const m of mods){assert.equal(get(m,ptr(m,0,1),'obj','quan'),5n);assert.equal(get(m,ptr(m,0,2),'obj','quan'),7n,'quiver preference must skip earlier eligible inventory stack');assert.equal(new DataView(m.HEAPU8.buffer).getBigUint64(Number(global(m,'uquiver')),true),ptr(m,0,1));}
const stackMerge=run('positive addressed floor-stack formal merge','stackobj',m=>{
 mergePair(m);objset(m,0,{where:1});objset(m,1,{where:1});
 const level=address(m,global(m,'svl'),'instance_globals_saved_l','level'),floor=address(m,level,'dlevel_t','objects');
 write64(m,floor+BigInt((12*21+10)*8),ptr(m,0));
 record(m,address(m,ptr(m,0),'obj','v'),'vptrs','v_nexthere',ptr(m,0,1));
},m=>[ptr(m,0)]);
for(const m of mods)assert.equal(get(m,ptr(m,0),'obj','quan'),5n,'floor survivor observes actual positive merge');
const organizeMerge=run('positive addressed organize formal updated survivor','doorganize_core',m=>{
 mergePair(m);m._probe_chain(-1,0,0);m._probe_chain(0,1,0);option(m,9,98);
},m=>[ptr(m,0)]);
for(const m of mods)assert.equal(get(m,ptr(m,0,1),'obj','quan'),5n,'organize target observes merge and caller formal replacement');
console.log('INVENT_ADDRESSED_FORMAL_POSITIVES '+JSON.stringify({added:4,checks,functions:119,source:'unchanged optimized Emscripten C vs cache-only corrected JS',native:false}));

for(const seen of factoryServices.values())assert.equal(seen.size,1,'INVENT factory reuses module-owned services');
