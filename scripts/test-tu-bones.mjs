import './pure-js-probes/deny-wasm.mjs';
import {referenceLabelFor as fixtureReferenceLabelFor} from './native-test-backend.mjs';
const fixtureReferenceLabel=fixtureReferenceLabelFor("bones");
import {createProbe,createReference,loadFixture,fixtureImports} from './pure-js-fixtures/load.mjs';
import assert from './native-test-assert.mjs';
import {pathToFileURL} from 'node:url';
import {resolve} from 'node:path';
import {referenceBackend,memoryCheckpoint,assertMemoryGrowth,assertStackRestored} from './native-test-backend.mjs';
import {withCEnvironment,C} from '../js/c-runtime/context.js';
import {createBonesEnvironment} from '../js/nethack/bindings/bones.js';
import * as core from '../js/ported/bones.js';
const probeDir=resolve(process.env.BONES_PROBE_DIR??'.cache/tu-probes');
const factory=async mode=>(await loadFixture("bones",pathToFileURL(resolve(probeDir,'bones-'+mode+'.mjs')).href)).default;
// Scratch builds use the same names as shared probes after integration.
const importFactory=async mode=>{try{return await factory(mode);}catch(error){if(!process.env.BONES_PROBE_DIR)throw error;return (await loadFixture("bones",pathToFileURL(resolve(probeDir,mode+'.mjs')).href)).default;}};
const referenceFactory=await importFactory('reference'),hybridFactory=await importFactory('hybrid');
const reference=await referenceBackend('bones',referenceFactory)();
function text(m,p){p=Number(p);let end=p;while(m.HEAPU8[end])end++;return Buffer.from(m.HEAPU8.slice(p,end)).toString('latin1');}
function readLayout(m){const l={};for(let i=0;i<m._probe_layout_count();i++)l[text(m,m._probe_layout_name(i))]=Number(m._probe_layout_value(i));return l;}
const L=readLayout(reference),environments=new WeakMap();
const signatures={no_bones_level:['level'],goodfruit:['int'],resetobjs:['object','boolean'],sanitize_name:['pointer'],give_to_nearby_mon:['object','coordxy','coordxy'],drop_upon_death:['monster','object','coordxy','coordxy'],fixuporacle:['monster'],can_make_bones:[],remove_mon_from_bones:['monster'],savebones:['int','long','object'],getbones:[],bones_include_name:['pointer'],set_ghostly_objlist:['object'],fix_ghostly_obj:['object'],newebones:['monster'],free_ebones:['monster']};
const runtime={bones(services,name,...args){let env=environments.get(services.moduleKey);if(!env){env=createBonesEnvironment(services,L,core);environments.set(services.moduleKey,env);}const saved=services.stackSave();try{return withCEnvironment(env,core[name],...args.map((v,i)=>['object','monster','level'].includes(signatures[name][i])?env[signatures[name][i]](v):signatures[name][i]==='long'?BigInt.asIntN(64,v):Number(v)));}finally{services.stackRestore(saved);}}};
const hybrid=await hybridFactory({nethackPorted:runtime}),modules=[reference,hybrid],stacks=modules.map(m=>m._probe_stack());
assert.deepEqual(readLayout(hybrid),L);let comparisons=0;
function compare(){const snapshots=modules.map(m=>({state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace())}));assert.deepEqual(snapshots[1],snapshots[0]);comparisons+=2;modules.forEach((m,i)=>{assertStackRestored(m,stacks[i]);comparisons++;});assert.equal(C,undefined);}
const both=(name,...args)=>modules.map(m=>m['_probe_'+name](...args));
function reset(){both('reset');compare();}
function option(i,value){both('option',i,value);}
function field(kind,index,name,value){for(const m of modules){const p=m._probe_pointer(kind==='object'?0:kind==='monster'?1:kind==='fruit'?2:kind==='trap'?3:kind==='hero'?6:7,index);m._teleport_bones_write(L['kind_'+kind],p,L['field_'+kind+'_'+name],BigInt.asUintN(64,BigInt(value)));}}
function action(op,a=0,b=0){const values=both('action',op,a,b);assert.equal(values[1],values[0]);comparisons++;compare();return Number(values[0]);}
function input(bytes){for(const m of modules){const p=Number(m._probe_pointer(5,0));m.HEAPU8.set(bytes,p);m.HEAPU8[p+bytes.length]=0;}}
function string(value){input(Buffer.from(value,'latin1'));}
function output(){return modules.map(m=>text(m,m._probe_pointer(5,0)));}
// Exact time_t dependency transport, including dates past2038 and integers above
// Number's exact range. This checks the savebones ABI without claiming file I/O.
for(const when of [0n,2147483648n,-2147483649n,9007199254740997n]){reset();action(0);const expected=reference._probe_time_bridge(when);const actual=environments.get(hybrid).yyyymmddhhmmss(when);assert.equal(text(hybrid,actual),text(reference,expected));comparisons++;compare();}
// All nonzero byte values under tty/non-tty and eight-bit input modes.
for(const tty of [0,L.wp_tty])for(const eight of [0,1]){reset();option(21,tty);for(const m of modules)m._teleport_bones_write(L.kind_iflags,m._teleport_bones_global(2),L.field_iflags_wc_eight_bit_input,BigInt(eight));input(Uint8Array.from({length:255},(_,i)=>i+1));action(0);assert.equal(output()[1],output()[0]);comparisons++;}
for(const bytes of [[],[0],[1,0,255],[32,126,127,128,159,160,254,255]]){reset();input(bytes);action(0);assert.equal(output()[1],output()[0]);comparisons++;}
// Existing cemetery names must match the full name followed by a hyphen.
for(const name of ['Alice','Ali','Alice-','Bob','','A'.repeat(31)]){reset();for(const m of modules){const p=Number(m._probe_pointer(5,0));m.HEAPU8.set(Buffer.from('Alice-Wiz-Hum-Mal-Neu\0'),p);m._probe_cemetery(0,BigInt(p));m.HEAPU8.set(Buffer.from('Bob-Rog-Orc-Fem-Cha\0'),p);m._probe_cemetery(1,BigInt(p));}both('link',6,0,0);both('link',7,0,1);string(name);action(9);}
// Bone level and eligibility gates preserve branch order and RNG callbacks.
for(const which of [0,1,2,3,4,5,6,7,8,9,10,11,12]){reset();switch(which){case 1:for(const m of modules){const at=m._teleport_bones_read(L.kind_hero,m._probe_pointer(6,0),L.field_hero_uz);m._teleport_bones_write(L.kind_level,at,L.field_level_dlevel,0n);}break;case 2:option(0,0);break;case 3:option(0,99);break;case 4:option(2,1);option(19,0);break;case 5:option(20,0);break;case 6:option(3,1);break;case 7:option(4,1);break;case 8:option(5,1);option(6,4);break;case 9:field('hero',0,'uswallow',1);break;case 10:both('trap',0,L.MAGIC_PORTAL);both('link',4,0,0);break;case 11:option(7,0);break;case 12:for(const m of modules)m._teleport_bones_write(L.kind_flags,m._teleport_bones_global(1),L.field_flags_explore,1n);break;}action(1);}
for(const wizard of [0,1])for(const seed of [0,1,2,9,22,12345]){reset();option(22,seed);option(23,1);for(const m of modules)m._teleport_bones_write(L.kind_flags,m._teleport_bones_global(1),L.field_flags_debug,BigInt(wizard));action(1);}
for(const id of [0,1,2,4,5]){reset();action(3,id);}
// Nested chains, in-use deletion and all configured special-object rewrites.
const types=['SLIME_MOLD','SCR_MAIL','EGG','TIN','CORPSE','STATUE','AMULET_OF_YENDOR','CANDELABRUM_OF_INVOCATION','BELL_OF_OPENING','SPE_BOOK_OF_THE_DEAD','SPE_NOVEL'];
for(const type of types)for(const restore of [0,1]){reset();field('object',0,'otyp',L[type]);field('object',0,'spe',3);field('object',0,'corpsenm',L.PM_GHOST);field('object',0,'lamplit',1);for(const name of ['known','dknown','bknown','rknown','lknown','cknown','tknown','no_charge','nomerge'])field('object',0,name,1);both('known',L[type],1);both('name',0,1);both('omonst',0);both('pm',L.PM_GHOST,0n,L.G_UNIQ);option(10,1);both('link',0,0,1);both('link',2,0,2);field('object',1,'in_use',1);action(4,0,restore);}
for(const duplicate of [0,1])for(const quest of [0,1]){reset();field('object',0,'oartifact',1);both('name',0,1);option(8,duplicate);option(9,quest);action(4,0,1);}
// Partly eaten shop food exercises both addressable coord out parameters.
for(const location of [0,1])for(const inside of [0,1])for(const room of [0,1])for(const tended of [0,1]){reset();field('object',0,'oclass',L.FOOD_CLASS);field('object',0,'oeaten',9);field('object',0,'where',L.OBJ_FLOOR);option(11,location);option(12,inside);option(13,room);option(14,tended);action(4,0,1);}
for(const type of ['BOW','ELVEN_BOW','ORCISH_BOW','YUMI','BOOMERANG','EGG'])for(const left of [0,1]){reset();field('object',0,'otyp',L[type]);field('hero',0,'uhandedness',left);both('link',0,0,1);action(5,0);action(6,0);action(6,0);}
// Extension allocation/zeroing, repeat initialization and ownership cleanup.
function extension(m,index){const extra=m._teleport_bones_read(L.kind_monster,m._probe_pointer(1,index),L.field_monster_mextra);return Number(m._teleport_bones_read(L.kind_mextra,extra,L.field_mextra_ebones));}
for(let i=0;i<8;i++){reset();field('monster',i,'m_id',0xffffffffn-BigInt(i));action(7,i);const bytes=modules.map(m=>m.HEAPU8.slice(extension(m,i),extension(m,i)+L.ebonesSize));assert.deepEqual(Array.from(bytes[1]),Array.from(bytes[0]));comparisons++;for(const m of modules)m.HEAPU8[extension(m,i)+L.ebonesSize-1]=0xa5;action(7,i);assert.equal(hybrid.HEAPU8[extension(hybrid,i)+L.ebonesSize-1],0xa5);comparisons++;action(8,i);action(8,i);}
// A C dependency grows memory between JS stores/loads of addressable locals.
reset();field('object',0,'oclass',L.FOOD_CLASS);field('object',0,'oeaten',4);field('object',0,'where',L.OBJ_FLOOR);for(const i of [11,12,13,14,26])option(i,1);const checkpoints=modules.map(memoryCheckpoint);action(4,0,1);modules.forEach((m,i)=>assertMemoryGrowth(m,checkpoints[i]));comparisons+=2;
// Inventory list extraction, curse RNG and monster/container/floor destinations.
for(const monster of [-1,0])for(const container of [-1,3])for(const seed of [1,2,6,9,18]){reset();option(22,seed);option(23,1);field('hero',0,'twoweap',1);for(let i=0;i<3;i++){field('object',i,'otyp',i?L.EGG:L.SLIME_MOLD);field('object',i,'spe',1);field('object',i,'lamplit',1);field('object',i,'owornmask',0x8000000000000001n);}both('link',0,0,1);both('link',0,1,2);both('link',1,0,0);action(10,monster,container);}
console.log(`bones: ${comparisons} ${fixtureReferenceLabel}/JS state, trace, return and stack comparisons; focused 11/16-function harness, full save/getbones file paths not covered`);
