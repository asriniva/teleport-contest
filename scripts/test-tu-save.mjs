import assert from './native-test-assert.mjs';
import {resolve} from 'node:path';
import {pathToFileURL} from 'node:url';
import {referenceBackend,referenceLabel,memoryCheckpoint,assertMemoryGrowth,assertStackRestored} from './native-test-backend.mjs';
import {withCEnvironment,C} from '../js/ported/c-runtime.js';
import {createSaveEnvironment} from '../js/ported/save-runtime.js';
import * as core from '../js/ported/save.js';
const dir=resolve(process.env.SAVE_PROBE_DIR??'.cache/tu-probes');
const factory=async mode=>(await import(pathToFileURL(resolve(dir,'save-'+mode+'.mjs')).href)).default;
const referenceFactory=await factory('reference'),hybridFactory=await factory('hybrid');
const reference=await referenceBackend('save',referenceFactory)();
function text(m,p){p=Number(p);let end=p;while(m.HEAPU8[end])end++;return Buffer.from(m.HEAPU8.slice(p,end)).toString('latin1');}
const signedLayoutValue=value=>Number(BigInt.asIntN(64,BigInt(value)));
function readLayout(m,unsignedCarrier=false){const l={};for(let i=0;i<m._probe_layout_count();i++){const value=m._probe_layout_value(i);l[text(m,m._probe_layout_name(i))]=signedLayoutValue(unsignedCarrier?BigInt.asUintN(64,BigInt(value)):value);}return l;}
const L=readLayout(reference),environments=new WeakMap();
const types={dosave:[],dosave0:[],save_gamelog:['nh_file'],savegamestate:['nh_file'],tricked_fileremoved:['nh_file','pointer'],savestateinlock:[],savelev:['nh_file','int'],savelev_core:['nh_file','int'],save_adjust_levelflags:[],savelevl:['nh_file'],save_bubbles:['nh_file','int'],savecemetery:['nh_file','cell:cemetery'],savedamage:['nh_file'],save_stairs:['nh_file'],save_bc:['nh_file'],saveobj:['nh_file','obj'],saveobjchn:['nh_file','cell:obj'],savemon:['nh_file','monst'],savemonchn:['nh_file','monst'],savetrapchn:['nh_file','trap'],savefruitchn:['nh_file'],savelevchn:['nh_file'],store_plname_in_file:['nh_file'],save_msghistory:['nh_file'],free_dungeons:[],freedynamicdata:[]};
const runtime={save(services,name,...args){let env=environments.get(services.moduleKey);if(!env){env=createSaveEnvironment(services,L);environments.set(services.moduleKey,env);}const saved=services.stackSave();try{return withCEnvironment(env,core[name],...args.map((v,i)=>types[name][i]?.startsWith('cell:')?env.pointerCell(types[name][i].slice(5),v):['int','pointer'].includes(types[name][i])?Number(v):env.view(types[name][i],v)));}finally{services.stackRestore(saved);}}};
const hybrid=await hybridFactory({nethackPorted:runtime}),modules=[reference,hybrid],stacks=modules.map(m=>m._probe_stack());assert.deepEqual(readLayout(hybrid),L);assert.deepEqual(readLayout(reference,true),L);assert.deepEqual(readLayout(hybrid,true),L);assert.equal(L.DISP_FREEMEM,reference._probe_disp_freemem());assert.equal(L.DISP_FREEMEM,hybrid._probe_disp_freemem());assert.ok(L.DISP_FREEMEM<0);let comparisons=5;
const both=(method,...args)=>modules.map(m=>m['_probe_'+method](...args));
function compare(){const values=modules.map(m=>({state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace())}));assert.equal(values[1].state,values[0].state);if(values[1].trace!==values[0].trace){const at=Array.from(values[0].trace).findIndex((c,i)=>c!==values[1].trace[i]);throw Error('SAVE trace differs at '+at+' after '+comparisons+' checks\nactual '+values[1].trace.slice(Math.max(0,at-80),at+200)+'\nexpected '+values[0].trace.slice(Math.max(0,at-80),at+200));}comparisons+=2;modules.forEach((m,i)=>{assertStackRestored(m,stacks[i]);comparisons++;});assert.equal(C,undefined);}
function reset(){both('reset');compare();}
function action(op,i=0){const v=both('action',op,i);assert.equal(v[1],v[0]);comparisons++;compare();}
function option(i,v){both('option',i,v);}
// Schema metadata is compiler-derived in the independent C support, never a copied
// SAVE algorithm. Field indices match the exact source-derived runtime descriptors.
const schema=JSON.parse(await (await import('node:fs/promises')).readFile(resolve('nethack-c/wasm/tu-fragments/save-schema.json'),'utf8'));
const kinds=Object.keys(schema.schema),globals=schema.globals;
function global(m,name){return m._teleport_save_global(globals.findIndex(g=>g.name===name));}
function pointer(m,k,i=0){return m._probe_pointer(k,i);}
function field(m,type,at,name,value){m._teleport_save_write(kinds.indexOf(type),at,schema.schema[type].fields.findIndex(f=>f.name===name),BigInt.asUintN(64,BigInt(value)));}
function get(m,type,at,name){return m._teleport_save_read(kinds.indexOf(type),at,schema.schema[type].fields.findIndex(f=>f.name===name));}
function setGlobal(name,value){for(const m of modules){const g=globals.find(x=>x.name===name);if(g.d.s)throw Error('field required');new DataView(m.HEAPU8.buffer).setBigUint64(Number(global(m,name)),BigInt.asUintN(64,BigInt(typeof value==='function'?value(m):value)),true);}}
function gfield(g,name,value){const type=globals.find(x=>x.name===g).d.s;for(const m of modules)field(m,type,global(m,g),name,typeof value==='function'?value(m):value);}
function pfield(type,k,i,name,value){for(const m of modules)field(m,type,pointer(m,k,i),name,typeof value==='function'?value(m):value);}
function nested(g,...fields){return m=>{let type=globals.find(x=>x.name===g).d.s,at=global(m,g);for(const f of fields){at=get(m,type,at,f);const d=schema.schema[type].fields.find(x=>x.name===f).d;type=d.s??d.p;}return {type,at};};}
function nfield(g,path,name,value){for(const m of modules){const {type,at}=nested(g,...path)(m);field(m,type,at,name,typeof value==='function'?value(m):value);}}
function mode(v){pfield('nh_file',0,0,'mode',v);}
function list(g,path,fieldName,kind,count,next,type){nfield(g,path,fieldName,m=>pointer(m,kind,0));for(let i=0;i<count;i++)pfield(type,kind,i,next,m=>i+1<count?pointer(m,kind,i+1):0);}
// Every configured body is invoked. Modes retain original bit masks and order.
for(const bits of [0,L.COUNTING,L.WRITING,L.FREEING,L.COUNTING|L.FREEING,L.WRITING|L.FREEING,L.COUNTING|L.WRITING|L.FREEING]){
 for(const op of [2,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23]){reset();mode(bits);action(op,7);}
}
for(const op of [0,1,3,4,5,6,7,8,24,25]){reset();if(op===6||op===7)mode(L.FREEING);action(op,7);}
// Both native coord arguments are observed at the actual cleanup dependency.
reset();action(25);for(const m of modules){assert.ok(text(m,m._probe_trace()).includes(`tmp_at:${L.DISP_FREEMEM}:0;`));comparisons++;}
// Lists and owned aliases are the same pointers reached through independent fields.
for(const bits of [L.COUNTING,L.WRITING,L.FREEING,L.WRITING|L.FREEING]){
 reset();mode(bits);list('gi',[],'invent',1,3,'nobj','obj');pfield('obj',1,0,'cobj',m=>pointer(m,1,4));
 for(const [ctx,f]of [['victual','piece'],['tin','tin'],['spbook','book']])nfield('svc',['context',ctx],f,m=>pointer(m,1,0));
 setGlobal('uball',m=>pointer(m,1,0));setGlobal('uchain',m=>pointer(m,1,1));pfield('obj',1,0,'owornmask',BigInt(L.W_BALL));pfield('obj',1,1,'owornmask',BigInt(L.W_CHAIN));action(16);
 reset();mode(bits);list('gm',[],'migrating_mons',2,3,'nmon','monst');pfield('monst',2,0,'minvent',m=>pointer(m,1,0));nfield('svc',['context','polearm'],'hitmon',m=>pointer(m,2,0));gfield('u','ustuck',m=>pointer(m,2,0));gfield('u','usteed',m=>pointer(m,2,1));action(18);
 for(const [op,g,path,f,k,next,t]of [[2,'gg',[],'gamelog',11,'next','gamelog_line'],[11,'svl',['level'],'bonesinfo',7,'next','cemetery'],[12,'svl',['level'],'damagelist',8,'next','damage'],[13,'gs',[],'stairs',9,'next','stairway'],[19,'gf',[],'ftrap',5,'ntrap','trap'],[20,'gf',[],'ffruit',6,'nextf','fruit'],[21,'svs',[],'sp_levchn',10,'next','s_level']]){reset();mode(bits);list(g,path,f,k,3,next,t);action(op);}
 reset();mode(bits);gfield('gl','looseball',m=>pointer(m,1,0));gfield('gl','loosechain',m=>pointer(m,1,1));action(14);
}
// Object extensions recurse into a monster and all configured monster extensions.
for(const extra of [0,1])for(const bits of [L.WRITING,L.WRITING|L.FREEING]){reset();mode(bits);if(extra){pfield('obj',1,0,'oextra',m=>pointer(m,3,0));pfield('oextra',3,0,'omonst',m=>pointer(m,2,0));pfield('monst',2,0,'mextra',m=>pointer(m,4,0));for(const [name,k]of [['edog',13],['egd',14],['epri',15],['eshk',16],['emin',17],['ebones',18]])pfield('mextra',4,0,name,m=>pointer(m,k,0));}action(15);}
for(const restoring of [0,L.REST_GSTATE])for(const sameDungeon of [0,1]){reset();gfield('program_state','restoring',restoring);list('gs',[],'stairs',9,2,'next','stairway');list('gf',[],'ftrap',5,2,'ntrap','trap');if(!sameDungeon){for(const m of modules){field(m,'d_level',get(m,'stairway',pointer(m,9,0),'tolev'),'dnum',3);field(m,'d_level',get(m,'trap',pointer(m,5,0),'dst'),'dnum',3);}}action(13);action(19);}
// Checkpoint pid refs, missing/open/create errors and normal pid-only truncation.
for(const checkpoint of [0,1])for(const opened of [0,1])for(const created of [0,1])for(const pid of [42,43]){reset();gfield('flags','ins_chkpt',checkpoint);gfield('gh','havestate',1);option(4,opened);option(5,created);option(6,pid);action(5);}
// Full save early failure paths restore notices/saving and temporary hero flags.
for(const worth of [0,1])for(const create of [0,1])for(const old of [0,1]){reset();gfield('program_state','something_worth_saving',worth);for(const m of modules){const at=get(m,'instance_globals_s',global(m,'gs'),'SAVEF');m.HEAPU8.set(Buffer.from('fixture-save\0'),Number(at));}gfield('iflags','save_uswallow',1);gfield('iflags','save_uinwater',1);gfield('iflags','save_uburied',1);gfield('iflags','window_inited',1);option(2,create);option(3,old);action(1);}
// Original signed-byte parameters narrow internal JS calls as C does.
reset();gfield('program_state','something_worth_saving',1);nfield('u',['uz'],'dlevel',128);option(2,1);for(const m of modules)m.HEAPU8.set(Buffer.from('fixture-save\0'),Number(get(m,'instance_globals_s',global(m,'gs'),'SAVEF')));action(1);
// Header provenance, >32bit/>2^53 time_t/long paths and original name/playmode slots.
for(const debug of [0,1])for(const female of [0,1])for(const alignment of [-1,0,1]){reset();gfield('flags','debug',debug);gfield('flags','female',female);nfield('u',['ualign'],'type',alignment);pfield('nh_file',0,0,'structlevel',1);action(22);}
reset();action(3);reset();option(25,1);action(23);
// Dependency writes local refs while growing memory or reentering another SAVE body.
for(const kind of ['growth','reentry','outref','mode','combined']){reset();list('gg',[],'gamelog',11,2,'next','gamelog_line');if(kind==='growth'||kind==='combined')option(26,1);if(kind==='reentry'||kind==='combined')option(27,1);if(kind==='outref'||kind==='combined')option(29,3);if(kind==='mode')option(28,L.WRITING|L.FREEING);const checkpoints=modules.map(memoryCheckpoint);action(2);if(kind==='growth'||kind==='combined'){modules.forEach((m,i)=>assertMemoryGrowth(m,checkpoints[i]));comparisons+=2;}}
// Scalar address coincidences stay exact; only typed pointers map to pool+offset.
function objectBytes(m){const part=text(m,m._probe_trace()).split(';').find(s=>s.startsWith('sfo_obj:obj:'));return Buffer.from(part.split(':')[3],'hex');}
function fieldOffset(m,name){return Number(m._teleport_save_address(kinds.indexOf('obj'),pointer(m,1),schema.schema.obj.fields.findIndex(f=>f.name===name)))-Number(pointer(m,1));}
reset();const coincident=BigInt(pointer(reference,1,2));pfield('obj',1,0,'owornmask',coincident);action(15);for(const m of modules){assert.equal(objectBytes(m).readBigUint64LE(fieldOffset(m,'owornmask')),coincident);comparisons++;}
// Intentionally different scalar inputs must fail the SAME unmodified comparison.
reset();pfield('obj',1,0,'owornmask',coincident);field(hybrid,'obj',pointer(hybrid,1),'owornmask',coincident+1n);assert.throws(()=>action(15),/SAVE trace differs/);comparisons++;
for(const unknown of [0n,0x123456n]){reset();pfield('obj',1,0,'nobj',unknown);action(15);for(const m of modules){assert.equal(objectBytes(m).readBigUint64LE(fieldOffset(m,'nobj')),unknown);comparisons++;}}
reset();pfield('obj',1,0,'nobj',0x123456n);field(hybrid,'obj',pointer(hybrid,1),'nobj',0x123457n);assert.throws(()=>action(15),/SAVE trace differs/);comparisons++;
// Aliases and interior offsets in known typed pointers remain distinguishable.
reset();for(const m of modules){field(m,'obj',pointer(m,1),'nobj',pointer(m,1,2));field(m,'obj',pointer(m,1),'oextra',pointer(m,3));field(m,'oextra',pointer(m,3),'oname',get(m,'oextra',pointer(m,3),'oname')+1n);}action(15);
// Independent Modules share neither typed view objects nor SAVE static sentinels.
const hybrid2=await hybridFactory({nethackPorted:runtime});hybrid2._probe_reset();hybrid2._probe_action(20,0);const e1=environments.get(hybrid),e2=environments.get(hybrid2);assert.notEqual(e1.zerofruit,e2.zerofruit);assert.notEqual(e1.view('obj',hybrid._probe_pointer(1,0)),e2.view('obj',hybrid2._probe_pointer(1,0)));e1.zerofruit.fid=919;assert.equal(e2.zerofruit.fid,0);comparisons+=3;
console.log(`save: ${comparisons} ${referenceLabel}/JS byte-stream, state, ownership, callback and stack comparisons; all 26 configured functions invoked, controlled dependency fixture`);
