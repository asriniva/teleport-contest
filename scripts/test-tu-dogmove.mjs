import './pure-js-probes/deny-wasm.mjs';
import {referenceLabelFor as fixtureReferenceLabelFor} from './native-test-backend.mjs';
const fixtureReferenceLabel=fixtureReferenceLabelFor("dogmove");
import {createProbe,createReference,loadFixture,fixtureImports} from './pure-js-fixtures/load.mjs';
import assert from './native-test-assert.mjs';
import {resolve} from 'node:path';
import {pathToFileURL} from 'node:url';
import {readFile} from 'node:fs/promises';
import {referenceBackend,memoryCheckpoint,assertMemoryGrowth,assertStackRestored} from './native-test-backend.mjs';
import {withCEnvironment,C} from '../js/c-runtime/context.js';
import {createDogmoveEnvironment} from '../js/nethack/bindings/dogmove.js';
import * as core from '../js/ported/dogmove.js';
import {createNativePetMovement} from '../js/nethack/native/dogmove.js';
import nativeAbi from '../js/nethack/dogmove-abi.json' with {type:'json'};
import {nativeFixtureServices,nativeFixtureCall} from './native-pet-combat-fixture.mjs';
const nativeExecution=process.env.NATIVE_PET_COMBAT_FIXTURE==='1',nativeContexts=new WeakMap();
const dir=resolve(process.env.DOGMOVE_PROBE_DIR??'.cache/tu-probes'),factory=async mode=>(await loadFixture("dogmove",pathToFileURL(resolve(dir,'dogmove-'+mode+'.mjs')).href)).default;
const referenceFactory=await factory('reference'),hybridFactory=await factory('hybrid'),reference=await referenceBackend('dogmove',referenceFactory)();
function text(m,p){p=Number(p);let end=p;while(m.HEAPU8[end])end++;return Buffer.from(m.HEAPU8.slice(p,end)).toString('latin1');}
function readLayout(m){const l={};for(let i=0;i<m._probe_layout_count();i++)l[text(m,m._probe_layout_name(i))]=Number(m._probe_layout_value(i));return l;}
const L=readLayout(reference),environments=new WeakMap();
const types={droppables:['monst'],cursed_object_at:['int','int'],dog_nutrition:['monst','obj'],dog_eat:['monst','obj','int','int','int'],dog_starve:['monst'],dog_hunger:['monst','edog'],dog_invent:['monst','edog','int'],dog_goal:['monst','edog','int','int','int'],find_targ:['monst','int','int','int'],find_friends:['monst','monst','int'],score_targ:['monst','monst'],best_target:['monst','int'],pet_ranged_attk:['monst','int'],dog_move:['monst','int'],could_reach_item:['monst','int','int'],can_reach_location:['monst','int','int','int','int'],wantdoor:['int','int','int'],finish_meating:['monst'],mnum_leashable:['int'],quickmimic:['monst']};
const runtime={dogmove(services,name,...args){if(nativeExecution){let entry=nativeContexts.get(services.moduleKey);if(!entry){const connected=nativeFixtureServices(services,nativeAbi.schemas),namespace={...core},env=createDogmoveEnvironment(connected.services,L,namespace),native=createNativePetMovement(env);Object.assign(namespace,native);entry={...connected,env,native};nativeContexts.set(services.moduleKey,entry);environments.set(services.moduleKey,env);}const result=nativeFixtureCall(entry.owner,entry.services,entry.native[name],...args.map((v,i)=>types[name][i]==='int'?Number(v):entry.env.view(types[name][i],v)));return ['droppables','find_targ','best_target'].includes(name)?result?.address??0:result;}let env=environments.get(services.moduleKey);if(!env){env=createDogmoveEnvironment(services,L,core);environments.set(services.moduleKey,env);}const saved=services.stackSave();try{const result=withCEnvironment(env,core[name],...args.map((v,i)=>types[name][i]==='int'?Number(v):env.view(types[name][i],v)));return ['droppables','find_targ','best_target'].includes(name)?result?.address??0:result;}finally{services.stackRestore(saved);}}};
const hybrid=await hybridFactory({nethackPorted:runtime}),modules=[reference,hybrid],stacks=modules.map(m=>m._probe_stack());assert.deepEqual(readLayout(hybrid),L);let comparisons=0,active='';
const both=(method,...args)=>modules.map(m=>m['_probe_'+method](...args));
function equalBytes(actual,expected,label){if(actual!==expected){const at=Array.from(expected).findIndex((c,i)=>c!==actual[i]);throw Error('DOGMOVE '+label+' differs at '+at+' in '+active+' after '+comparisons+' checks\nactual '+actual.slice(Math.max(0,at-80),at+200)+'\nexpected '+expected.slice(Math.max(0,at-80),at+200));}}
function compare(){const values=modules.map(m=>({state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace())}));equalBytes(values[1].state,values[0].state,'state');equalBytes(values[1].trace,values[0].trace,'trace');comparisons+=2;modules.forEach((m,i)=>{assertStackRestored(m,stacks[i]);comparisons++;});assert.equal(C,undefined);}
function reset(){both('reset');compare();}
function action(op,...args){active='action '+op+' '+args.join(',');args=[...args,...Array(5-args.length).fill(0)];const v=both('action',op,...args);assert.equal(v[1],v[0],active);comparisons++;compare();return v;}
function option(i,v){both('option',i,v);}
const schema=JSON.parse(await readFile(resolve('nethack-c/wasm/tu-fragments/dogmove-schema.json'),'utf8')),kinds=Object.keys(schema.schema),globals=schema.globals;
function global(m,name){return m._teleport_dogmove_global(globals.findIndex(g=>g.name===name));}
function pointer(m,k,i=0){return m._probe_pointer(k,i);}
function field(m,type,at,name,value){m._teleport_dogmove_write(kinds.indexOf(type),at,schema.schema[type].fields.findIndex(f=>f.name===name),BigInt.asUintN(64,BigInt(value)));}
function get(m,type,at,name){return m._teleport_dogmove_read(kinds.indexOf(type),at,schema.schema[type].fields.findIndex(f=>f.name===name));}
function pfield(type,k,i,name,value){for(const m of modules)field(m,type,pointer(m,k,i),name,typeof value==='function'?value(m):value);}
function gfield(g,name,value){const type=globals.find(x=>x.name===g).d.s;for(const m of modules)field(m,type,global(m,g),name,typeof value==='function'?value(m):value);}
function nested(m,g,path){let type=globals.find(x=>x.name===g).d.s,at=global(m,g);for(const f of path){at=get(m,type,at,f);const d=schema.schema[type].fields.find(x=>x.name===f).d;type=d.s??d.p;}return{type,at};}
function nfield(g,path,name,value){for(const m of modules){const {type,at}=nested(m,g,path);field(m,type,at,name,typeof value==='function'?value(m):value);}}
function vision(mask){for(let y=0;y<L.ROWNO;y++)for(let x=0;x<L.COLNO;x++)both('vision',x,y,mask);}
function inv(...indices){pfield('monst',0,0,'minvent',m=>indices.length?pointer(m,1,indices[0]):0);for(let i=0;i<indices.length;i++)pfield('obj',1,indices[i],'nobj',m=>i+1<indices.length?pointer(m,1,indices[i+1]):0);}
// Invoke every original function, including native pointer, signed64, callback returns.
for(const [op,args]of [[0,[0]],[1,[10,10]],[2,[0,0]],[3,[0,0,10,10,0]],[4,[0]],[5,[0,1]],[6,[0,1]],[7,[0,1,0,100,0]],[8,[0,1,0,7]],[9,[0,1,15]],[10,[0,1]],[11,[0,0]],[12,[0,0]],[13,[0,0]],[14,[0,10,10]],[15,[0,10,10,13,10]],[16,[10,10]],[17,[0]],[18,[L.PM_LITTLE_DOG]],[19,[0]]]){reset();action(op,...args);}
// Every source qm row is compared with the real compiled private C table.
reset();action(0,0);const env=environments.get(hybrid);for(let i=0;i<9;i++)for(const [f,key]of ['mndx','mlet','mappearance','m_ap_type'].entries()){assert.equal(env.qm[i][key],reference._probe_qm(i,f));comparisons++;}const np=Number(reference._probe_nofetch());assert.deepEqual(Array.from(hybrid.HEAPU8.slice(env.nofetch,env.nofetch+4)),Array.from(reference.HEAPU8.slice(np,np+4)));comparisons++;
// Tool/weapon/artifact/cursed preferences, including duplicate replacement returns.
for(const typ of ['PICK_AXE','DWARVISH_MATTOCK','UNICORN_HORN','SKELETON_KEY','LOCK_PICK','CREDIT_CARD'])for(const artifact of [0,1])for(const wield of [0,1]){reset();pfield('obj',1,0,'otyp',L[typ]);pfield('obj',1,1,'otyp',L[typ]);pfield('obj',1,0,'oartifact',artifact);pfield('obj',1,1,'oartifact',1-artifact);inv(0,1);if(wield)pfield('monst',0,0,'mw',m=>pointer(m,1,0));action(0,0);}
for(const flags of [L.M1_ANIMAL,L.M1_MINDLESS,L.M1_TUNNEL|L.M1_NEEDPICK,L.M1_NOHANDS,L.M1_NOHEAD]){reset();pfield('permonst',4,L.PM_LITTLE_DOG,'mflags1',BigInt(flags));inv(0,1);pfield('obj',1,0,'otyp',L.PICK_AXE);action(0,0);}
// Full exact C-width nutrition for sizes, corpses, partly eaten objects and gold.
for(const size of [L.MZ_TINY,L.MZ_SMALL,L.MZ_MEDIUM,L.MZ_LARGE,L.MZ_HUGE,L.MZ_GIGANTIC])for(const eaten of [0,1]){reset();pfield('permonst',4,L.PM_LITTLE_DOG,'msize',size);pfield('obj',1,0,'oeaten',eaten);option(10,2);action(2,0,0);pfield('obj',1,0,'otyp',L.CORPSE);pfield('obj',1,0,'corpsenm',L.PM_LITTLE_DOG);action(2,0,0);}
for(const quantity of [0n,1n,19n,20n,1999n,2000n,4294967295n,9007199254740997n,9223372036854775807n]){reset();pfield('obj',1,0,'oclass',L.COIN_CLASS);pfield('obj',1,0,'quan',quantity);action(2,0,0);}
for(const weight of [0,19,20,0xffffffff]){reset();pfield('obj',1,0,'oclass',L.TOOL_CLASS);pfield('obj',1,0,'owt',weight);action(2,0,0);}
// Hunger transitions use the original long64 move clock; starvation messages vary.
for(const hungryDelta of [-1000n,-751n,-501n,-500n,-1n,1000n])for(const penalty of [0,10]){reset();pfield('edog',2,0,'hungrytime',9007199254740997n+hungryDelta);pfield('edog',2,0,'mhpmax_penalty',penalty);action(5,0,1);}
for(const see of [0,1])for(const leash of [0,1]){reset();if(see)vision(L.IN_SIGHT|L.COULD_SEE);pfield('monst',0,0,'mleashed',leash);action(4,0);}
// Eat reward, split ownership, visibility, rustproofing, shop-price64 and jelly paths.
for(const devour of [0,1])for(const unpaid of [0,1])for(const visible of [0,1]){reset();if(visible)vision(L.IN_SIGHT|L.COULD_SEE);option(5,visible);option(6,visible);pfield('obj',1,0,'quan',2n);pfield('obj',1,0,'unpaid',unpaid);pfield('obj',1,0,'invlet',97);pfield('edog',2,0,'mhpmax_penalty',10);pfield('monst',0,0,'mflee',1);pfield('monst',0,0,'mfleetim',9);action(3,0,0,9,10,devour);}
for(const bee of [-1,0,1]){reset();pfield('monst',0,0,'data',m=>pointer(m,4,L.PM_KILLER_BEE));pfield('obj',1,0,'otyp',L.LUMP_OF_ROYAL_JELLY);option(11,bee);action(3,0,0,10,10,0);}
reset();pfield('monst',0,0,'data',m=>pointer(m,4,L.PM_RUST_MONSTER));pfield('obj',1,0,'oerodeproof',1);pfield('obj',1,0,'unpaid',1);option(5,1);gfield('flags','verbose',1);action(3,0,0,10,10,0);
// Original RNG caller sites, drop/pick/eat decisions and object handoff order.
for(const carried of [0,1])for(const food of [L.DOGFOOD,L.ACCFOOD,L.APPORT])for(const seed of [0,1,2,7,15,31]){reset();option(29,1);option(28,seed);option(8,food);if(carried)inv(0);else both('map',1,10,10,0);action(6,0,4);}
// Reachability walks real terrain, water/lava/boulder and wall/door constraints.
for(const [pool,lava,boulder]of [[0,0,0],[1,0,0],[0,1,0],[0,0,1]])for(const swimmer of [0,1]){reset();option(1,pool);option(2,lava);option(3,boulder);pfield('permonst',4,L.PM_LITTLE_DOG,'mflags1',swimmer?BigInt(L.M1_SWIM):0n);action(14,0,12,10);action(15,0,10,10,12,10);}
// Header doormask aliases the live flags bits: closed/locked doors block a path.
// A column satisfying the native IS_OBSTRUCTED(typ < POOL) macro prevents detours.
for(const mask of [0,L.D_CLOSED,L.D_LOCKED,L.D_CLOSED|L.D_LOCKED]){
    reset();
    for(const m of modules){
        const base=nested(m,'svl',['level','locations']).at;
        for(let y=0;y<L.ROWNO;y++){
            const at=base+BigInt((11*L.ROWNO+y)*L.rmSize);
            field(m,'rm',at,'typ',y===10?L.DOOR:L.POOL-1);
            field(m,'rm',at,'flags',y===10?mask:0);
        }
    }
    const result=action(15,0,10,10,12,10);
    assert.equal(Number(result[0]),mask?0:1,'Native doorway reachability');comparisons++;
}
// Target/score/friend scans preserve long return arithmetic and creature identities.
for(const passive of [0,1])for(const peaceful of [0,1])for(const confused of [0,1]){reset();option(29,1);pfield('monst',0,1,'mx',14);pfield('monst',0,1,'mtame',0);pfield('monst',0,1,'mpeaceful',peaceful);pfield('monst',0,1,'m_lev',8);pfield('monst',0,0,'m_lev',7);pfield('monst',0,0,'mconf',confused);if(passive){for(const m of modules){const at=get(m,'permonst',pointer(m,4,L.PM_LITTLE_DOG),'mattk');field(m,'attack',at,'aatyp',L.AT_NONE);}}both('map',0,14,10,1);action(8,0,1,0,7);action(10,0,1);action(11,0,0);action(12,0,1);}
// Position candidates use native mfndpos stack records and original labeled joins.
for(const cnt of [0,1,2,3])for(const after of [0,1])for(const leashed of [0,1]){reset();option(29,1);option(17,cnt);pfield('monst',0,0,'mleashed',leashed);both('map',0,10,10,0);action(13,0,after);}
// Every qm source row can affect actual mimic state; visual feedback and leash paths.
for(const seen of [0,1])for(const leashed of [0,1])for(const times of [1,2,5]){reset();option(29,1);option(5,seen);option(20,1);if(seen)vision(L.IN_SIGHT|L.COULD_SEE);pfield('monst',0,0,'mleashed',leashed);pfield('monst',0,0,'meating',times);action(19,0);action(17,0);}
// Co-aligned priests/minions and positive scoring exercise original long promotion.
for(const alignment of [L.A_NONE,-1,0,1])for(const priest of [0,1]){reset();pfield('monst',0,0,'mux',40);pfield('monst',0,1,'mx',14);pfield('monst',0,1,'mtame',0);pfield('monst',0,1,'mpeaceful',1);pfield('monst',0,0,priest?'ispriest':'isminion',1);pfield('monst',0,1,priest?'ispriest':'isminion',1);pfield('mextra',3,0,priest?'epri':'emin',m=>pointer(m,priest?6:7,0));pfield('mextra',3,1,priest?'epri':'emin',m=>pointer(m,priest?6:7,1));pfield(priest?'epri':'emin',priest?6:7,0,priest?'shralign':'min_align',alignment);pfield(priest?'epri':'emin',priest?6:7,1,priest?'shralign':'min_align',alignment);action(10,0,1);}
for(const vampire of [0,1])for(const level of [1,8,30]){reset();option(29,1);pfield('monst',0,0,'mux',40);pfield('monst',0,1,'mx',14);pfield('monst',0,1,'mtame',0);pfield('monst',0,1,'m_lev',level);pfield('monst',0,1,'mhp',99);if(vampire){pfield('monst',0,0,'cham',L.PM_VAMPIRE);pfield('permonst',4,L.PM_VAMPIRE,'mlevel',14);}both('map',0,14,10,1);action(10,0,1);action(11,0,0);action(12,0,1);}
// Callback locals, same-TU reentry and goal tracking retain native alias visibility.
reset();option(32,1);pfield('monst',0,1,'meating',5);pfield('monst',0,1,'m_ap_type',L.M_AP_MONSTER);action(7,0,1,0,100,0);
reset();const refDistance=reference._probe_clear_area(10,10,500);let jsDistance=500;const e=environments.get(hybrid);withCEnvironment(e,()=>e.do_clear_area(10,10,9,nativeExecution?nativeContexts.get(hybrid).native.wantdoor:core.wantdoor,e.reference('int',()=>jsDistance,v=>jsDistance=v)));assert.equal(jsDistance,refDistance);comparisons++;compare();
// Candidate food and backtracking exercise the original forward/loop joins.
for(const cursed of [0,1])for(const seed of [1,8,99]){reset();option(28,seed);option(29,1);option(17,1);option(5,1);both('map',0,10,10,0);both('map',1,11,10,0);pfield('obj',1,0,'ox',11);pfield('obj',1,0,'cursed',cursed);action(13,0,0);}
reset();option(17,3);option(29,1);for(const m of modules){const at=get(m,'monst',pointer(m,0),'mtrack');field(m,'nhcoord',at,'x',11);field(m,'nhcoord',at,'y',10);}action(13,0,0);
reset();pfield('monst',0,0,'mleashed',1);option(21,1);action(13,0,0);
// Pet/target and reverse attacks preserve C status-bit tests and early returns.
for(const [status,response]of [[L.M_ATTK_HIT,0],[L.M_ATTK_HIT,L.M_ATTK_DEF_DIED],[L.M_ATTK_AGR_DIED,0],[L.M_ATTK_DEF_DIED,0]])for(const after of [0,1]){reset();option(29,1);option(17,1);option(18,L.ALLOW_M);option(15,status);option(33,response);pfield('monst',0,0,'m_lev',10);pfield('monst',0,1,'m_lev',1);pfield('monst',0,1,'mtame',0);both('map',0,11,10,1);action(13,0,after);}
for(const result of [0,L.M_ATTK_DEF_DIED]){reset();option(17,1);option(18,L.ALLOW_MDISP);option(19,1);option(34,result);both('map',0,11,10,1);action(13,0,0);}
// Source hunger/property/trap/steed/minion paths retain signed64 clocks and identity.
for(const minion of [0,1]){reset();gfield('u','usteed',minion?0:m=>pointer(m,0));if(minion){pfield('monst',0,0,'isminion',1);pfield('mextra',3,0,'edog',0);}for(const m of modules){const at=get(m,'you',global(m,'u'),'uprops');field(m,'prop',at+BigInt(L.CONFLICT*L.propSize),'intrinsic',1n);}option(26,0);action(13,0,0);}
for(const cls of [L.BALL_CLASS,L.CHAIN_CLASS,L.ROCK_CLASS]){reset();both('map',1,10,10,0);pfield('obj',1,0,'oclass',cls);action(6,0,4);}
for(const mnum of [L.PM_LONG_WORM,-1,L.HIGH_PM+1]){reset();action(18,mnum);}
// Existing scalar fields never become pointer identities by coincidental value.
reset();const coincident=BigInt(pointer(reference,0));pfield('edog',2,0,'hungrytime',coincident);action(5,0,1);
reset();pfield('edog',2,0,'hungrytime',coincident);field(hybrid,'edog',pointer(hybrid,2),'hungrytime',coincident+1n);assert.throws(()=>compare(),/DOGMOVE state differs/);comparisons++;
// A caller callback mutates the bound BEFORE evaluation, and grows the memory.
reset();inv(0);option(29,1);option(30,1);option(31,1);const checkpoints=modules.map(memoryCheckpoint);action(6,0,4);modules.forEach((m,i)=>assertMemoryGrowth(m,checkpoints[i]));comparisons+=2;
// Independent Modules retain distinct canonical records and private dummy storage.
const hybrid2=await hybridFactory({nethackPorted:runtime});hybrid2._probe_reset();hybrid2._probe_action(0,0,0,0,0,0);const e1=environments.get(hybrid),e2=environments.get(hybrid2);assert.notEqual(e1.dummy,e2.dummy);assert.notEqual(e1.view('monst',pointer(hybrid,0)),e2.view('monst',pointer(hybrid2,0)));comparisons+=2;
console.log(`dogmove: ${comparisons} ${fixtureReferenceLabel}/JS raw-state, trace, pointer, long64, callback and stack comparisons; all 20 configured functions invoked, controlled world dependencies`);

if(nativeExecution)console.log('Native DOGMOVE state/execution matrix PASS');
