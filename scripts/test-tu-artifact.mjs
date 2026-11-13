import {nativeFixtureServices} from './native-pet-combat-fixture.mjs';
import {createArtifactFieldPlans} from '../js/nethack/artifact.js';
const nativeExecution=process.env.NATIVE_ARTIFACT_FIXTURE==='1',nativeServices=new WeakMap();
function artifactServices(s){if(!nativeExecution)return s;let local=nativeServices.get(s);if(!local){local=nativeFixtureServices(s,{}).services;local.nativeFieldPlans=createArtifactFieldPlans(s.moduleKey.environment);nativeServices.set(s,local);}return local;}
import './pure-js-probes/deny-wasm.mjs';
import {createProbe,createReference,loadFixture,fixtureImports} from './pure-js-fixtures/load.mjs';
import {DataView as FixtureDataView} from './native-test-backend.mjs';
// Configured original-C/JS first pass; native-host and game parity remain separate.
import assert from './native-test-assert.mjs';
import {readFile,writeFile,mkdir} from 'node:fs/promises';
import {resolve} from 'node:path';
import {spawnSync} from 'node:child_process';
import {pathToFileURL} from 'node:url';
import {checkArtifactSource} from '../nethack-c/wasm/tu-fragments/artifact-source-check.mjs';
import {C,withCEnvironment} from '../js/c-runtime/context.js';
import {createArtifactEnvironment,callArtifact} from '../js/nethack/bindings/artifact.js';
import * as core from '../js/ported/artifact.js';
const dir=resolve(process.env.ARTIFACT_PROBE_DIR??'.cache/artifact-author');
const schema=JSON.parse(await readFile('nethack-c/wasm/tu-fragments/artifact-schema.json','utf8'));
if(process.argv.includes('--build')) {
 await mkdir(dir,{recursive:true});checkArtifactSource();
 const exports=['probe_option_name','probe_reset','probe_option','probe_pointer','probe_canonical','probe_trace','probe_stack','probe_save_rewind','probe_test_constant','probe_test_trap_glyph','probe_pointer_equal','probe_layout_count','probe_layout_name','probe_layout_value','teleport_artifact_global','teleport_artifact_read','teleport_artifact_write','teleport_artifact_address',...schema.functions.map(f=>'probe_call_'+f.name)];
 const defines=JSON.parse(await readFile('nethack-c/wasm/compile-defines.json','utf8'));
 const base=['-O2','-sMEMORY64=1','-sMODULARIZE=1','-sENVIRONMENT=node','-sALLOW_MEMORY_GROWTH=1','--no-entry','-sEXPORTED_RUNTIME_METHODS=HEAPU8','-sEXPORTED_FUNCTIONS='+JSON.stringify(exports.map(s=>'_'+s)),...defines.map(s=>'-D'+s),'-I'+resolve('.cache/wasm64-build/tree/include'),'-I'+resolve('.cache/ncurses-wasm64-build/include'),'-I'+resolve('scripts'),'-include',resolve('nethack-c/wasm/native-terminal.h'),'-fmacro-prefix-map='+resolve('scripts')+'/../.cache/wasm64-build/tree/src/=',resolve('scripts/tu-artifact-probe.c')];
 for(const mode of ['reference','hybrid']) {
  const args=[...base,...(mode==='hybrid'?['-DHYBRID_ARTIFACT=1','--js-library',resolve('nethack-c/wasm/tu-libraries/artifact.js')]:[]),'-o',resolve(dir,'artifact-'+mode+'.mjs')];
  const r=spawnSync(resolve('.cache/emsdk/upstream/emscripten/emcc'),args,{encoding:'utf8',maxBuffer:32*1024*1024});
  await writeFile(resolve(dir,'build-'+mode+'-'+Date.now()+'.log'),JSON.stringify({args,status:r.status})+'\n'+r.stdout+r.stderr);
  if(r.status!==0)throw Error('ARTIFACT '+mode+' build failed; see private build log');
 }
}
const imports=new Set((await fixtureImports("artifact")).filter(e=>e.kind==='function').map(e=>e.name));
for(const f of schema.functions)assert.ok(imports.has(f.static?'teleport_artifact_test_'+f.name:f.name),'JS policy import '+f.name);
const factories=await Promise.all(['reference','hybrid'].map(async mode=>(await loadFixture("artifact",pathToFileURL(resolve(dir,'artifact-'+mode+'.mjs')).href)).default));
const text=(m,p)=>{let i=Number(p),end=i;while(m.HEAPU8[end])end++;return Buffer.from(m.HEAPU8.slice(i,end)).toString('latin1');};
function layout(m){const out={};for(let i=0;i<m._probe_layout_count();i++)out[text(m,m._probe_layout_name(i))]=m._probe_layout_value(i);return out;}
const reference=await factories[0](),L=layout(reference),servicesByModule=new WeakMap(),environments=new WeakMap(),callbackCalls=new Map();
const runtime={artifact(services,name,...args){services=artifactServices(services);callbackCalls.set(name,(callbackCalls.get(name)??0)+1);servicesByModule.set(services.moduleKey,services);environments.set(services.moduleKey,createArtifactEnvironment(services,L,core));return callArtifact(services,L,name,...args);}};
const hybrid=await factories[1]({nethackPorted:runtime}),modules=[reference,hybrid];assert.deepEqual(layout(hybrid),L);
// Both copies capture their independently initialized original catalogue before reset.
hybrid._probe_call_artiname(0);
const testConstantNames=['ART_FIRE_BRAND','ART_FROST_BRAND','ART_MJOLLNIR','ART_MAGICBANE','CHEST','PM_HUMAN'];
const N=k=>{if(L[k]!==undefined)return Number(BigInt.asIntN(64,L[k]));const i=testConstantNames.indexOf(k);assert.notEqual(i,-1,'missing native fixture constant '+k);return reference._probe_test_constant(i);};
const options={};for(let i=0;;i++){const p=reference._probe_option_name(i);if(!p)break;options[text(reference,p)]=i;}
const kinds=Object.keys(schema.schema),globals=schema.globals,stacks=modules.map(m=>m._probe_stack());
let cases=0,comparisons=0,active='';const invoked=new Set();
const both=(n,...args)=>modules.map(m=>m['_probe_'+n](...args));
const ptr=(m,k,i=0)=>m._probe_pointer(k,i);
const global=(m,n)=>m._teleport_artifact_global(globals.findIndex(g=>g.name===n));
function write(m,kind,at,name,v){const i=schema.schema[kind].fields.findIndex(f=>f.name===name);assert.notEqual(i,-1,kind+'.'+name);m._teleport_artifact_write(kinds.indexOf(kind),at,i,BigInt.asUintN(64,BigInt(v)));}
function read(m,kind,at,name){const i=schema.schema[kind].fields.findIndex(f=>f.name===name);assert.notEqual(i,-1,kind+'.'+name);return m._teleport_artifact_read(kinds.indexOf(kind),at,i);}
function nested(m,g,path){let d=globals.find(x=>x.name===g).d,at=global(m,g);for(const name of path){const f=schema.schema[d.s].fields.find(x=>x.name===name);assert.ok(f,g+'.'+path);at=read(m,d.s,at,name);d=f.d;}return{d,at};}
function gfield(g,n,v){for(const m of modules)write(m,globals.find(x=>x.name===g).d.s,global(m,g),n,typeof v==='function'?v(m):v);}
function nfield(g,path,n,v){for(const m of modules){const x=nested(m,g,path);write(m,x.d.s,x.at,n,typeof v==='function'?v(m):v);}}
function pfield(kind,k,i,n,v){for(const m of modules)write(m,kind,ptr(m,k,i),n,typeof v==='function'?v(m):v);}
function option(n,v){const i=typeof n==='number'?n:options[n];assert.notEqual(i,undefined,n);both('option',i,v);}
function input(s){for(const m of modules)m.HEAPU8.set(Buffer.from(s+'\0','latin1'),Number(ptr(m,5)));}
function arti(m,i){return global(m,'artilist')+BigInt(i*N('artifactSize'));}
function afield(i,n,v){for(const m of modules)write(m,'artifact',arti(m,i),n,v);}
function attack(i,member,n,v){for(const m of modules)write(m,'attack',read(m,'artifact',arti(m,i),member),n,v);}
function gptr(name,v){for(const m of modules)new FixtureDataView(m.HEAPU8.buffer).setBigUint64(Number(global(m,name)),typeof v==='function'?v(m):BigInt(v),true);}
function location(m,x,y){return nested(m,'svl',['level','locations']).at+BigInt((x*N('ROWNO')+y)*N('rmSize'));}
function property(p,member,v){for(const m of modules){const at=read(m,'you',global(m,'u'),'uprops')+BigInt(N(p)*N('propSize'));write(m,'prop',at,member,v);}}
const width=d=>d.t?Number(d.t.slice(1))/8:d.p!==undefined||d.f?8:d.s?N(d.s+'Size'):d.a.reduce((a,b)=>a*b,1)*width(d.e);
function state(m){if(m.isolatedCReference)return m.observe('const {L,schema,testConstantNames}=context;const reference=m,globals=schema.globals,kinds=Object.keys(schema.schema),FixtureDataView=DataView;const text='+text.toString()+';const ptr='+ptr.toString()+';const global='+global.toString()+';const N='+N.toString()+';const width='+width.toString()+';'+state.toString()+';return state(m);',{L,schema,testConstantNames});const out=[],dv=new FixtureDataView(m.HEAPU8.buffer);
 const scalar=(d,v,ct)=>{if(d.p!==undefined){if(/^(?:const )?char \*(?:const)?$/.test(ct))out.push(v?text(m,v):null);else out.push(m._probe_canonical(v).toString());}else if(d.f)out.push(v?1:0);else out.push(v.toString());};
 const value=(d,at,ct='')=>{if(d.s){for(const [i,f]of schema.schema[d.s].fields.entries()){const v=m._teleport_artifact_read(kinds.indexOf(d.s),at,i);if(f.d.s||f.d.a)value(f.d,v,f.ctype);else scalar(f.d,v,f.ctype);}return;}
  if(d.a){const child=d.a.length===1?d.e:{a:d.a.slice(1),e:d.e};for(let i=0;i<d.a[0];i++)value(child,at+BigInt(i*width(child)),ct.replace(/\[\d*\]/g,''));return;}
  scalar(d,dv.getBigUint64(Number(at),true)&((1n<<BigInt(width(d)*8))-1n),ct);};
 for(const g of globals)value(g.d,global(m,g.name));
 for(const [kind,k,count]of [['monst',0,8],['obj',1,16],['trap',4,4],['d_level',7,1],['mi',12,8]])if(schema.schema[kind])for(let i=0;i<count;i++)value({s:kind},ptr(m,k,i));
 for(let i=0;i<8;i++){out.push(dv.getBigInt64(Number(ptr(m,8,i)),true).toString());out.push(dv.getInt16(Number(ptr(m,9,i)),true));out.push(dv.getInt32(Number(ptr(m,10,i)),true));out.push(m._probe_canonical(dv.getBigUint64(Number(ptr(m,11,i)),true)).toString());}
 out.push(text(m,ptr(m,5)));return out;
}
function compare(){assert.deepEqual(state(hybrid),state(reference),'ARTIFACT state '+active);assert.equal(text(hybrid,hybrid._probe_trace()),text(reference,reference._probe_trace()),'ARTIFACT trace '+active);comparisons+=2;for(let i=0;i<2;i++){assert.equal(modules[i]._probe_stack(),stacks[i],'restored C stack');comparisons++;}assert.equal(C,undefined);}
function reset(label){active=label;cases++;both('reset');}
function action(name,...args){if(process.env.ARTIFACT_VERBOSE)console.log(active,name);invoked.add(name);const f=schema.functions.find(f=>f.name===name),ret=f.type.qualType.split('(')[0].trim();const values=modules.map(m=>m['_probe_call_'+name](...args.map(a=>typeof a==='function'?a(m):a)));const normalized=values.map((v,i)=>/char\s*\*/.test(ret)?v?text(modules[i],v):null:ret.includes('*')?modules[i]._probe_canonical(v):v);assert.deepEqual(normalized[1],normalized[0],name+' result '+active);comparisons++;compare();return values;}
const argMap={save_artifacts:[0n],restore_artifacts:[0n],artiname:[1],mk_artifact:[m=>ptr(m,1),0,255,1],artifact_name:[m=>ptr(m,5),m=>ptr(m,9),0],restrict_name:[m=>ptr(m,1),m=>ptr(m,5)],exist_artifact:[N('LONG_SWORD'),m=>ptr(m,5)],artifact_exists:[m=>ptr(m,1),m=>ptr(m,5),1,N('ONAME_RANDOM')],found_artifact:[1],spec_ability:[m=>ptr(m,1),1n],attacks:[0,m=>ptr(m,1)],defends:[0,m=>ptr(m,1)],defends_when_carried:[0,m=>ptr(m,1)],protects:[m=>ptr(m,1),0],set_artifact_intrinsic:[m=>ptr(m,1),1,N('W_WEP')?BigInt(L.W_WEP):0n],touch_artifact:[m=>ptr(m,1),m=>ptr(m,6)],arti_immune:[m=>ptr(m,1),0],bane_applies:[m=>arti(m,1),m=>ptr(m,0)],spec_applies:[m=>arti(m,1),m=>ptr(m,0)],spec_abon:[m=>ptr(m,1),m=>ptr(m,0)],spec_dbon:[m=>ptr(m,1),m=>ptr(m,0),3],discover_artifact:[1],undiscovered_artifact:[1],disp_artifact_discoveries:[7],dump_artifact_info:[7],Mb_hit:[m=>ptr(m,6),m=>ptr(m,0),m=>ptr(m,1),m=>ptr(m,10),8,1,m=>ptr(m,5)],artifact_hit:[m=>ptr(m,6),m=>ptr(m,0),m=>ptr(m,1),m=>ptr(m,10),10],artifact_has_invprop:[m=>ptr(m,1),0],abil_to_adtyp:[m=>ptr(m,8)],abil_to_spfx:[m=>ptr(m,8)],what_gives:[m=>ptr(m,8)],glow_color:[1],glow_strength:[1],glow_verb:[1,1],Sting_effects:[1],retouch_object:[m=>ptr(m,11),0],untouchable:[m=>ptr(m,1),0],retouch_equipment:[0],count_surround_traps:[20,10],is_magic_key:[m=>ptr(m,6),m=>ptr(m,1)],has_magic_key:[m=>ptr(m,6)],is_art:[m=>ptr(m,1),1],artifact_origin:[m=>ptr(m,1),N('ONAME_RANDOM')]};
for(const f of schema.functions){reset('initial '+f.name);action(f.name,...(argMap[f.name]??(f.parameters.length?[m=>ptr(m,1)]:[])));}
// Original table names and secondary short outputs, including article and fuzzy paths.
for(let a=1;a<=33;a++) {
 const name=text(reference,read(reference,'artifact',arti(reference,a),'name'));
 for(const [label,value,fuzzy]of [['exact',name,0],['article','the '+name,0],['fuzzy',name.replace(/[ -]/g,''),1]]) {
  reset('name '+a+' '+label);input(value);const returned=action('artifact_name',m=>ptr(m,5),m=>ptr(m,9),fuzzy);if(label==='exact')for(let i=0;i<2;i++){assert.equal(returned[i],read(modules[i],'artifact',arti(modules[i],a),'name'));comparisons++;}
 }
 reset('artifact '+a+' intrinsics');pfield('obj',1,0,'oartifact',a);
 for(const m of modules)write(m,'obj',ptr(m,1),'otyp',read(m,'artifact',arti(m,a),'otyp'));
 action('set_artifact_intrinsic',m=>ptr(m,1),1,BigInt(L.W_ART));
 action('set_artifact_intrinsic',m=>ptr(m,1),0,BigInt(L.W_ART));
 action('set_artifact_intrinsic',m=>ptr(m,1),1,BigInt(L.W_WEP));
 action('set_artifact_intrinsic',m=>ptr(m,1),0,BigInt(L.W_WEP));
 action('spec_dbon',m=>ptr(m,1),m=>ptr(m,0),7);
 action('touch_artifact',m=>ptr(m,1),m=>ptr(m,6));
}
for(const flags of ['ONAME_WISH','ONAME_GIFT','ONAME_VIA_DIP','ONAME_VIA_NAMING','ONAME_LEVEL_DEF','ONAME_BONES','ONAME_RANDOM']) {
 reset('origin '+flags);pfield('obj',1,0,'oartifact',1);action('artifact_origin',m=>ptr(m,1),N(flags));action('find_artifact',m=>ptr(m,1));action('find_artifact',m=>ptr(m,1));
}
reset('discovery insertion order/save/restore');
for(const i of [4,2,4,33,1,8])action('discover_artifact',i);
action('disp_artifact_discoveries',7);action('dump_artifact_info',7);
action('save_artifacts',0n);both('save_rewind');action('init_artifacts');action('restore_artifacts',0n);
// Every basic attack, beheading and life-drain route, against hero and monster.
for(const a of ['ART_FIRE_BRAND','ART_FROST_BRAND','ART_MJOLLNIR','ART_MAGICBANE','ART_TSURUGI_OF_MURAMASA','ART_VORPAL_BLADE','ART_STORMBRINGER'])for(const defend of [0,1])for(const roll of [1,8,20]) {
 reset('hit '+a+' defend'+defend+' roll'+roll);pfield('obj',1,0,'oartifact',N(a));
 for(const m of modules)write(m,'obj',ptr(m,1),'otyp',read(m,'artifact',arti(m,N(a)),'otyp'));
 action('artifact_hit',m=>ptr(m,defend?0:6),m=>ptr(m,defend?6:0),m=>ptr(m,1),m=>ptr(m,10),roll);
}
for(const target of [0,1])for(const enchant of [-3,0,3,6])for(const roll of [1,3,6,8]) {
 reset('Magicbane '+target+'/'+enchant+'/'+roll);pfield('obj',1,0,'oartifact',N('ART_MAGICBANE'));pfield('obj',1,0,'spe',enchant);gfield('gs','spec_dbon_applies',1);input('fixture target');
 action('Mb_hit',m=>ptr(m,target?0:6),m=>ptr(m,target?6:0),m=>ptr(m,1),m=>ptr(m,10),roll,1,m=>ptr(m,5));
}
// Special-power switch plus cancellation, cooldown and invoked-property reversal.
for(const power of ['TAMING','HEALING','ENERGY_BOOST','UNTRAP','CHARGE_OBJ','LEV_TELE','CREATE_PORTAL','ENLIGHTENING','CREATE_AMMO','BANISH','FLING_POISON','SNOWSTORM','FIRESTORM','BLINDING_RAY','CONFLICT','LEVITATION','INVIS']) {
 reset('invoke '+power);afield(1,'inv_prop',N(power));pfield('obj',1,0,'oartifact',1);gfield('u','uhp',10);gfield('u','uen',10);action('arti_invoke',m=>ptr(m,1));
 action('arti_invoke',m=>ptr(m,1));
}
for(const choice of [0,1]) {
 reset('native getobj callback '+choice);option(244,choice);pfield('obj',1,0,'oartifact',1);action('doinvoke');
 reset('native charge callback '+choice);option(244,choice);action('invoke_charge_obj',m=>ptr(m,1));
}
reset('portal native menu outpointer');gfield('svn','n_dgns',3);
for(const m of modules){const at=nested(m,'svd',['dungeons']).at;for(let i=0;i<3;i++){const p=at+BigInt(i*N('dungeonSize'));write(m,'dungeon',p,'dunlev_ureached',3);write(m,'dungeon',p,'entry_lev',1);write(m,'dungeon',p,'depth_start',1);}}
option(246,1);action('invoke_create_portal',m=>ptr(m,1));
for(const hell of [0,1])for(const quest of [0,1]) {
 reset('banish live demon chain '+hell+'/'+quest);option('In_hell',hell);option('In_quest',quest);nfield('svl',['level'],'monlist',m=>ptr(m,0));
 for(let i=0;i<3;i++)pfield('monst',0,i,'nmon',i<2?m=>ptr(m,0,i+1):0);
 pfield('permonst',2,N('PM_HUMAN'),'mflags2',BigInt(L.M2_DEMON)|BigInt(L.M2_PRINCE));action('invoke_banish',m=>ptr(m,1));
}
for(const blessing of [-1,0,1])for(const direction of ['ray','vertical','self']) {
 reset('blinding '+blessing+'/'+direction);option('getdir',1);pfield('obj',1,0,'blessed',Number(blessing>0));pfield('obj',1,0,'cursed',Number(blessing<0));gfield('u','dx',direction==='ray'?1:0);gfield('u','dz',direction==='vertical'?1:0);action('invoke_blinding_ray',m=>ptr(m,1));
}
// Writable scalar references map exact live property addresses, not equal values.
for(const propertyName of ['FIRE_RES','COLD_RES','SHOCK_RES','ANTIMAGIC','DISINT_RES','POISON_RES','DRAIN_RES','SEARCHING','HALLUC_RES','TELEPAT','STEALTH','REGENERATION','TELEPORT_CONTROL','WARN_OF_MON','WARNING','ENERGY_REGENERATION','HALF_SPDAM','HALF_PHDAM','REFLECTING']) {
 reset('ability address '+propertyName);
 const address=m=>m._teleport_artifact_address(kinds.indexOf('prop'),read(m,'you',global(m,'u'),'uprops')+BigInt(N(propertyName)*N('propSize')),schema.schema.prop.fields.findIndex(f=>f.name==='extrinsic'));
 action('abil_to_adtyp',address);action('abil_to_spfx',address);action('what_gives',address);
}
reset('optional null artifact_name output');input('Excalibur');const nullBefore=modules.map(m=>m.HEAPU8.slice(0,32));action('artifact_name',m=>ptr(m,5),0n,0);for(let i=0;i<2;i++){assert.deepEqual(modules[i].HEAPU8.slice(0,32),nullBefore[i]);comparisons++;}
reset('stable overwritten glow buffer');const first=modules.map(m=>m._probe_call_glow_verb(1,0));const second=modules.map(m=>m._probe_call_glow_verb(13,1));for(let i=0;i<2;i++){assert.equal(first[i],second[i]);comparisons++;}assert.equal(text(hybrid,first[1]),text(reference,first[0]));comparisons++;compare();
// Silver touch damage, real obj** writes, removal/rescan and both drop policies.
for(const lose of [0,1])for(const held of [0,1])for(const half of [0,1]) {
 reset('retouch silver '+lose+'/'+held+'/'+half);option('hates_silver',1);
 pfield('obj',1,0,'otyp',N('RIN_INCREASE_DAMAGE'));pfield('obj',1,0,'oclass',N('RING_CLASS'));pfield('obj',1,0,'owornmask',BigInt(L.W_RINGL));
 pfield('objclass',3,N('RIN_INCREASE_DAMAGE'),'oc_material',N('SILVER'));
 if(held)gfield('gi','invent',m=>ptr(m,1));
 property('HALF_PHDAM','extrinsic',half?1n:0n);
 action('retouch_object',m=>ptr(m,11),lose);
}
for(const drop of [0,1,2]) {
 reset('equipment inventory and weapons '+drop);gfield('gi','invent',m=>ptr(m,1));pfield('obj',1,0,'nobj',m=>ptr(m,1,1));pfield('obj',1,1,'nobj',m=>ptr(m,1,2));gptr('uwep',m=>ptr(m,1));gptr('uswapwep',m=>ptr(m,1,1));gfield('u','twoweap',1);pfield('obj',1,0,'owornmask',BigInt(L.W_WEP));pfield('obj',1,1,'owornmask',BigInt(L.W_SWAPWEP));pfield('obj',1,2,'owornmask',BigInt(L.W_TOOL));action('retouch_equipment',drop);
}
for(const gloves of [0,1])for(const recursive of [0,1]) {
 reset('equipment removal lifecycle '+gloves+'/'+recursive);option('hates_silver',1);option(249,1);option(250,recursive);gfield('gi','invent',m=>ptr(m,1));pfield('obj',1,0,'otyp',N('RIN_INCREASE_DAMAGE'));pfield('objclass',3,N('RIN_INCREASE_DAMAGE'),'oc_material',N('SILVER'));pfield('obj',1,0,'owornmask',gloves?BigInt(L.W_ARMG):BigInt(L.W_RINGL));
 if(gloves)gptr('uarmg',m=>ptr(m,1));else{gptr('uleft',m=>ptr(m,1));gptr('uarmg',m=>ptr(m,1,1));pfield('obj',1,1,'cursed',1);}
 action('retouch_equipment',0);
}
for(const mode of ['hidden','shown','door','container']) {
 reset('surround traps '+mode);
 if(mode==='hidden'||mode==='shown')option('t_at',1);
 if(mode==='shown')option('glyph_at',reference._probe_test_trap_glyph());
 if(mode==='door')for(const m of modules){write(m,'rm',location(m,20,10),'typ',N('DOOR'));write(m,'rm',location(m,20,10),'flags',N('D_TRAPPED'));}
 if(mode==='container')for(const m of modules){write(m,'obj',ptr(m,1),'otyp',N('CHEST'));write(m,'obj',ptr(m,1),'otrapped',1);const objects=nested(m,'svl',['level','objects']).at;new FixtureDataView(m.HEAPU8.buffer).setBigUint64(Number(objects)+((20*N('ROWNO')+10)*8),ptr(m,1),true);}
 action('count_surround_traps',20,10);gptr('uwep',m=>ptr(m,1,1));pfield('obj',1,1,'oartifact',N('ART_MASTER_KEY_OF_THIEVERY'));action('mkot_trap_warn');action('mkot_trap_warn');
}
for(const blind of [0,1])for(const count of [-1,0,1,5,13]) {
 reset('Sting warning '+blind+'/'+count);gptr('uwep',m=>ptr(m,1));pfield('obj',1,0,'oartifact',N('ART_STING'));gfield('gw','warn_obj_cnt',5);property('BLINDED','intrinsic',blind?1n:0n);action('Sting_effects',count);
}
// Opaque wide pointer values are compared only; no outside-memory dereference.
for(const at of [(1n<<60n)+1n,(1n<<60n)+2n,0xfffffffffffffff8n]) {
 reset('wide opaque ability '+at);action('abil_to_adtyp',at);action('abil_to_spfx',at);
}
const env=environments.get(hybrid);
for(const [a,b]of [[(1n<<60n)+1n,(1n<<60n)+2n],[(1n<<60n)+1n,(1n<<60n)+1n]]){assert.equal(env.pointerEqual(a,b),reference._probe_pointer_equal(a,b));comparisons++;}
reset('growth with same-TU RNG logger reentry');option(240,1);option(242,1);pfield('obj',1,0,'oartifact',N('ART_MAGICBANE'));gfield('gs','spec_dbon_applies',1);input('fixture target');const buffers=modules.map(m=>m.HEAPU8.buffer);action('Mb_hit',m=>ptr(m,6),m=>ptr(m,0),m=>ptr(m,1),m=>ptr(m,10),1,1,m=>ptr(m,5));for(let i=0;i<2;i++){assert.notEqual(buffers[i],modules[i].HEAPU8.buffer);comparisons++;}
// A scalar equal to an address must remain a scalar in the comparison.
reset('coincident scalar negative control');const coincident=ptr(reference,0);gfield('u','uhp',coincident);write(hybrid,'you',global(hybrid,'u'),'uhp',coincident+1n);assert.throws(compare,/ARTIFACT state/);comparisons++;
const primary=servicesByModule.get(hybrid),marker={sentinel:'outer'};
const failure=new Error('controlled transport failure');
const failing=new Proxy(primary,{get(o,k){return k==='rn2'?()=>{throw failure;}:Reflect.get(o,k);}});
reset('transport error restores original C stack/scope');pfield('obj',1,0,'oartifact',N('ART_MAGICBANE'));
withCEnvironment(marker,()=>{assert.throws(()=>callArtifact(failing,L,'Mb_hit',ptr(hybrid,6),ptr(hybrid,0),ptr(hybrid,1),ptr(hybrid,10),1,1,ptr(hybrid,5)),e=>e===failure);assert.equal(C,marker);comparisons+=2;});assert.equal(C,undefined);assert.equal(hybrid._probe_stack(),stacks[1]);comparisons+=2;
// Native views, static table backing and mutable JS state are per Module.
const hybrid2=await factories[1]({nethackPorted:runtime});hybrid2._probe_call_artiname(0);hybrid2._probe_reset();hybrid2._probe_call_glow_verb(5,1);
const env2=environments.get(hybrid2);assert.notEqual(env.state,env2.state);assert.notEqual(env.view('obj',ptr(hybrid,1)),env2.view('obj',ptr(hybrid2,1)));comparisons+=2;
const originalCost=read(hybrid,'artifact',arti(hybrid,1),'cost');write(hybrid2,'artifact',arti(hybrid2,1),'cost',999999n);assert.equal(read(hybrid,'artifact',arti(hybrid,1),'cost'),originalCost);comparisons++;
assert.throws(()=>createArtifactEnvironment(primary,{...L,pointerSize:4n},core),/changed ARTIFACT ABI/);comparisons++;
assert.throws(()=>createArtifactEnvironment(primary,{...L,width_obj_otyp:4n},core),/field width/);comparisons++;
// Exercise refusal guards on private copies; original and active sources stay intact.
const guardRoot=resolve(dir,'guard-negative'),guardPaths=['nethack-c/upstream/src/artifact.c','.cache/wasm64-build/tree/src/artifact.c','nethack-c/upstream/include/artilist.h','.cache/wasm64-build/tree/include/artilist.h','js/ported/artifact.js','nethack-c/wasm/tu-fragments/artifact-schema.json'];
const guardOriginal=new Map();for(const p of guardPaths){const data=await readFile(p,'utf8');guardOriginal.set(p,data);await mkdir(resolve(guardRoot,p,'..'),{recursive:true});await writeFile(resolve(guardRoot,p),data);}
checkArtifactSource(guardRoot,{preprocess:false});
for(const [p,transform]of [[guardPaths[0],s=>'/* changed */'+s],[guardPaths[1],s=>'/* changed */'+s],[guardPaths[2],s=>'/* changed */'+s],[guardPaths[3],s=>'/* changed */'+s],[guardPaths[4],s=>s.replace('export function mk_artifact(','export function changed_mk_artifact(')],[guardPaths[4],s=>s.replace('/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */','')],[guardPaths[5],s=>s.replace(schema.preparedSha256,'0'.repeat(64))]]){await writeFile(resolve(guardRoot,p),transform(guardOriginal.get(p)));assert.throws(()=>checkArtifactSource(guardRoot,{preprocess:false}),/Review changed|Missing original/);comparisons++;await writeFile(resolve(guardRoot,p),guardOriginal.get(p));}
assert.equal(invoked.size,76);
console.log(`artifact: ${cases} cases, ${comparisons} EmC/JS state/trace/result/stack checks, ${invoked.size}/76 routines; native host pending`);
await writeFile(resolve(dir,'summary.json'),JSON.stringify({status:'pass',oracle:'configured Emscripten memory64 original source',nativeHost:'pending',nativeExecution,cases,comparisons,functions:invoked.size,jsPolicyImports:schema.functions.length,nativeCallbackCalls:Object.fromEntries(callbackCalls)},null,2)+'\n');
