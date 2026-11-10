import assert from 'node:assert/strict';
import {readFile} from 'node:fs/promises';
import {resolve,dirname,join} from 'node:path';
import {fileURLToPath,pathToFileURL} from 'node:url';
import {createTeleportBridge} from '../js/ported/teleport-runtime.js';
if(process.env.TELEPORT_NATIVE_TESTS==='1')throw new Error('TELEPORT has no native reference fixture; Emscripten results cannot be labeled native.');
const root=resolve(dirname(fileURLToPath(import.meta.url)),'..'),dir=resolve(process.env.TELEPORT_PROBE_DIR??join(root,'.cache/teleport-first-pass'));
const meta=JSON.parse(await readFile(join(root,'nethack-c/wasm/tu-fragments/teleport-abi.json'),'utf8'));
const options=JSON.parse(await readFile(join(root,'nethack-c/wasm/tu-fragments/teleport-probe-options.json'),'utf8'));
const factories=await Promise.all(['reference','hybrid'].map(async mode=>(await import(pathToFileURL(join(dir,`teleport-${mode}.mjs`)).href)).default));
const decode=(m,p)=>{p=Number(p);let e=p;while(m.HEAPU8[e])e++;return new TextDecoder().decode(m.HEAPU8.subarray(p,e));};
const mods=await Promise.all(factories.map(f=>f()));
const layout={};for(let i=0;i<mods[0]._probe_layout_count();i++){const n=decode(mods[0],mods[0]._probe_layout_name(i));layout[n]=Number(mods[0]._probe_layout_value(i));assert.equal(mods[1]._probe_layout_value(i),mods[0]._probe_layout_value(i));assert.equal(decode(mods[1],mods[1]._probe_layout_name(i)),n);}
const bridge=createTeleportBridge(layout);mods[1].nethackPorted={teleport:bridge};
let checks=0;const invoked=new Set(),observedRngSites=new Set();
const ptr=(m,k,i=0)=>m._probe_pointer(k,i);
const field=(m,name,v)=>{const i=meta.globalfields.indexOf(name);assert.ok(i>=0,name);m._probe_field(i,BigInt(v));};
const record=(m,kind,name,i,v)=>{const k=['monster','permonst','object','trap','coord'][kind],f=meta.records[k][1].indexOf(name);assert.ok(f>=0,name);m._probe_record(kind,f,i,BigInt(v));};
const call=(m,name,args=[])=>m._probe_call(meta.names.indexOf(name),...Array.from({length:6},(_,i)=>BigInt(args[i]??0)));
const equal=(a,b,label)=>{assert.equal(b,a,label);checks++;};
function run(label,name,setup,args,n=0,seed=17){
 const got=mods.map(m=>{m._probe_reset(seed);setup?.(m);const before=m._probe_stack();let value=call(m,name,args?.(m)??[]);if(name==='stairway_find_forwiz'&&value!==0n){const id=[0,1,2,3].find(i=>ptr(m,7,i)===value);assert.notEqual(id,undefined,label+' known stair pointer');value=BigInt(id+1);}const after=m._probe_stack();assert.equal(after,before,label+' stack restored');return{value,trace:decode(m,m._probe_trace()),snapshot:decode(m,m._probe_snapshot(n))};});
 for(const m of got[0].trace.matchAll(/rng:teleport.c:(\d+):/g))observedRngSites.add(Number(m[1]));
 equal(got[0].value,got[1].value,label+' return');equal(got[0].trace,got[1].trace,label+' full trace');equal(got[0].snapshot,got[1].snapshot,label+' C world/coordinates');invoked.add(name);
}
const baseargs={
 m_blocks_teleporting:m=>[ptr(m,0)],noteleport_level:m=>[ptr(m,0)],goodpos_onscary:m=>[15,15,ptr(m,1)],goodpos:m=>[15,15,ptr(m,0),0],
 enexto:m=>[ptr(m,4),15,15,ptr(m,1)],enexto_gpflags:m=>[ptr(m,4),15,15,ptr(m,1),0],enexto_core:m=>[ptr(m,4),15,15,ptr(m,1),0],tele_jump_ok:()=>[10,10,15,15],teleok:()=>[15,15,0],teleds:()=>[15,15,2],collect_coords:m=>[ptr(m,5),40,10,3,0,0],safe_teleds:()=>[2],teleport_pet:m=>[ptr(m,0),0],scrolltele:m=>[ptr(m,2)],dotele:()=>[0],domagicportal:m=>[ptr(m,3)],tele_trap:m=>[ptr(m,3)],level_tele_trap:m=>[ptr(m,3),0],rloc_pos_ok:m=>[15,15,ptr(m,0)],rloc_to_core:m=>[ptr(m,0),15,15,4],rloc_to:m=>[ptr(m,0),15,15],rloc_to_flag:m=>[ptr(m,0),15,15,4],stairway_find_forwiz:()=>[0,1],rloc:m=>[ptr(m,0),0],control_mon_tele:m=>[ptr(m,0),ptr(m,4),0,0],mvault_tele:m=>[ptr(m,0)],tele_restrict:m=>[ptr(m,0)],mtele_trap:m=>[ptr(m,0),ptr(m,3),1],mlevel_tele_trap:m=>[ptr(m,0),ptr(m,3),0,1],rloco:m=>[ptr(m,2)],u_teleport_mon:m=>[ptr(m,0),1],
};
for(const name of meta.names)run('configured '+name,name,null,baseargs[name]);
const flags=[0,layout.CC_INCL_CENTER,layout.CC_UNSHUFFLED,layout.CC_RING_PAIRS,layout.CC_SKIP_MONS,layout.CC_SKIP_INACCS,layout.CC_INCL_CENTER|layout.CC_RING_PAIRS|layout.CC_SKIP_MONS|layout.CC_SKIP_INACCS,0xffffffff];
for(const [x,y] of [[1,0],[79,20],[40,10],[0,-1],[80,21],[-32768,32767],[32767,-32768]])for(const radius of [1,2,3,4])for(const flag of flags){
 run(`collect ${x}/${y}/${radius}/${flag}`,'collect_coords',m=>{m._probe_tile(2,0,layout.STONE,0);m._probe_tile(3,1,layout.DOOR,layout.D_CLOSED);},m=>[ptr(m,5),x,y,radius,flag,0],1659,31);
}
for(const flag of flags)for(const filtered of [false,true])run(`full map ${flag}/${filtered}`,'collect_coords',m=>{m._probe_tile(2,0,layout.STONE,0);},m=>[ptr(m,5),40,10,0,flag,filtered?ptr(m,6):0],1659,5481);
for(const opt of [31,34])run('filter growth/reentry '+opt,'collect_coords',m=>m._probe_option(opt,1n),m=>[ptr(m,5),40,10,4,layout.CC_RING_PAIRS,ptr(m,6)],1659);
for(const [x,y] of [[0,10],[80,10],[10,-1],[10,21],[40,10],[10,10],[15,15],[65551,65551]])for(const flag of [0,layout.GP_ALLOW_U,layout.GP_AVOID_MONPOS,layout.GP_CHECKSCARY,0xffffffff])for(const who of [0,8,-1])run(`goodpos ${x}/${y}/${flag}/${who}`,'goodpos',null,m=>[x,y,who<0?0:ptr(m,who),flag]);
for(const tile of [layout.STONE,layout.ROOM,layout.POOL,layout.LAVAPOOL,layout.DOOR,layout.ALTAR])for(const flag of [0,layout.MM_IGNOREWATER,layout.MM_IGNORELAVA,layout.GP_CHECKSCARY])for(const bits of [0n,BigInt(layout.M1_SWIM),BigInt(layout.M1_WALLWALK),BigInt(layout.M1_AMORPHOUS),0x8000000000000000n])run(`terrain ${tile}/${flag}/${bits}`,'goodpos',m=>{m._probe_tile(15,15,tile,layout.D_CLOSED);record(m,1,'mflags1',0,bits);},m=>[15,15,ptr(m,0),flag]);
for(const tile of [layout.POOL,layout.LAVAPOOL])for(const prop of [layout.LEVITATION,layout.FLYING,layout.SWIMMING,layout.FIRE_RES,layout.WWALKING])run(`hero terrain ${tile}/${prop}`,'goodpos',m=>{m._probe_tile(15,15,tile,0);m._probe_property(prop,0x2000000000000000n,0n,0n);},m=>[15,15,ptr(m,8),0]);
for(const when of [-9223372036854775808n,-9007199254740997n,0n,1n,9007199254740997n,9223372036854775807n])for(const moves of [-9007199254740997n,0n,9007199254740997n])run(`stasis ${when}/${moves}`,'noteleport_level',m=>{field(m,'svl.level.flags.stasis_until',when);field(m,'svm.moves',moves);},m=>[ptr(m,0)]);
for(const region of [[1,1,20,20,5,5,10,10],[0,0,0,0,0,0,0,0]])for(const start of [[6,6],[15,15]])for(const dest of [[6,6],[15,15],[0,-1]])run(`jump ${region}/${start}/${dest}`,'tele_jump_ok',m=>{m._probe_dest(0,...region);m._probe_dest(1,...region);},()=>[...start,...dest]);
for(const flag of [0,layout.GP_ALLOW_XY,layout.GP_ALLOW_XY|layout.GP_ALLOW_U,0xffffffff])for(const fill of [false,true])run(`enexto fallback ${flag}/${fill}`,'enexto_core',m=>{if(fill)for(let x=1;x<80;x++)for(let y=0;y<21;y++)m._probe_tile(x,y,layout.STONE,0);m._probe_option(50,1n);},m=>[ptr(m,4),40,10,0,flag]);
for(const mask of [0n,0x80000000n,0x8000000080000000n,0xffffffffffffffffn])for(const flag of [0,layout.RLOC_MSG,layout.RLOC_NOMSG])run(`rloc strategy ${mask}/${flag}`,'rloc_to_core',m=>{record(m,0,'mstrategy',0,mask);record(m,0,'mstate',0,-9007199254740997n);m._probe_option(31,1n);},m=>[ptr(m,0),15,15,flag]);
for(const mode of [-1,0,110,115,116,119])for(const high of [0n,9007199254740997n,-9007199254740997n])run(`wizard menu ${mode}/${high}`,'dotelecmd',m=>{m._probe_debug(1);field(m,'iflags.menu_requested',1);field(m,'HTeleportation',high);field(m,'ETeleportation',-high);m._probe_menu(mode);},null);
for(const text of ['\x1b','?','*','0','-1','-9','-10','5','12','invalid'])run(`controlled level ${JSON.stringify(text)}`,'level_tele',m=>{m._probe_debug(1);const at=m._malloc(BigInt(text.length+1));m.HEAPU8.set(new TextEncoder().encode(text+'\0'),Number(at));m._probe_input(BigInt(at));m._free(at);},null);
for(const type of [layout.TELEP_TRAP,layout.LEVEL_TELEP,layout.MAGIC_PORTAL,layout.HOLE,layout.TRAPDOOR])for(const once of [0,1])for(const name of ['tele_trap','level_tele_trap','mtele_trap','mlevel_tele_trap'])run(`trap ${name}/${type}/${once}`,name,m=>{m._probe_trap(0,type,40,10,15,15,once);m._probe_option(33,1n);},m=>name.startsWith('mlevel')?[ptr(m,0),ptr(m,3),0,1]:name.startsWith('mtele')?[ptr(m,0),ptr(m,3),1]:name==='level_tele_trap'?[ptr(m,3),layout.FORCETRAP]:[ptr(m,3)]);
for(const high of [9007199254740997n,-9007199254740997n,0x7fffffffffffffffn])for(const name of ['domagicportal','level_tele_trap'])run(`timeout ${name}/${high}`,name,m=>{field(m,'HStun',high);field(m,'HConfusion',high);m._probe_trap(0,layout.MAGIC_PORTAL,40,10,15,15,0);},m=>[ptr(m,3),0]);
for(const bits of [0n,BigInt(layout.M2_DEMON)|BigInt(layout.M2_LORD),BigInt(layout.M2_DEMON)|BigInt(layout.M2_PRINCE),0x8000000000000000n])run('C iterator private callback '+bits,'noteleport_level',m=>{m._probe_option(options.In_hell,1n);record(m,1,'mflags2',1,bits);},m=>[ptr(m,0)]);
for(const cursed of [0,1])for(const force of [0,1,128,256])for(const found of [0,1])run(`leash ${cursed}/${force}/${found}`,'teleport_pet',m=>{record(m,0,'mleashed',0,1);record(m,2,'cursed',0,cursed);m._probe_option(60,BigInt(found));},m=>[ptr(m,0),force]);
for(const drag of [0,1])for(const far of [false,true])run(`ball drag ${drag}/${far}`,'teleds',m=>{m._probe_link(2,0);m._probe_link(3,1);record(m,2,'where',0,layout.OBJ_FLOOR);m._probe_option(65,BigInt(drag));},()=>[far?30:41,10,layout.TELEDS_ALLOW_DRAG|layout.TELEDS_TELEPORT]);
for(const name of ['vault_tele','mvault_tele'])run('vault room '+name,name,m=>{m._probe_option(63,1n);m._probe_option(64,1n);},baseargs[name]);
for(const ladder of [0,1])for(const up of [0,1])run(`stair pointer ${ladder}/${up}`,'stairway_find_forwiz',m=>{m._probe_stair(0,8,8,0,0);m._probe_stair(1,9,9,1,1);m._probe_stair(2,10,10,0,1);m._probe_stair(3,11,11,1,0);m._probe_link(6,0);},()=>[ladder,up]);
run('Wizard rloc staircase','rloc',m=>{record(m,0,'iswiz',0,1);m._probe_stair(0,25,12,0,1);m._probe_link(6,0);},baseargs.rloc);
for(const flags of [0,layout.RLOC_ERR])for(const name of ['rloc','safe_teleds'])run(`exhausted world ${name}/${flags}`,name,m=>{for(let x=1;x<80;x++)for(let y=0;y<21;y++)m._probe_tile(x,y,layout.STONE,0);},m=>name==='rloc'?[ptr(m,0),flags]:[2]);
run('fuzzer dungeon selection','level_tele',m=>field(m,'iflags.debug_fuzzer',1),null);
for(const inputMenu of [0,1])run('wizard dungeon menu '+inputMenu,'level_tele',m=>{m._probe_debug(1);field(m,'iflags.menu_requested',inputMenu);m._probe_option(66,1n);const a=m._malloc(2);m.HEAPU8.set([63,0],Number(a));m._probe_input(BigInt(a));m._free(a);},null);
for(const via of [0,1])for(const answer of [0,-1])run(`controlled monster ${via}/${answer}`,'control_mon_tele',m=>{m._probe_debug(1);m._probe_option(40,15n);m._probe_option(41,15n);m._probe_option(42,BigInt(answer));},m=>[ptr(m,0),ptr(m,4),layout.RLOC_MSG,via]);
for(const blind of [0,1])run('monster visibility '+blind,'rloc_to_core',m=>{m._probe_vision(blind?0:3);record(m,0,'mstrategy',0,0x8000000080000000n);},m=>[ptr(m,0),15,15,layout.RLOC_MSG]);
for(const props of [0n,9007199254740997n])run('intrinsic teleport command '+props,'dotele',m=>{field(m,'HTeleportation',props);m._probe_objlevel(3);m._probe_role(layout.PM_WIZARD);},()=>[0]);
// Repeat original public entries with observable C state and exact stack restoration.
for(let i=0;i<40;i++)run('repeated native buffers '+i,'enexto_core',null,m=>[ptr(m,4),40,10,ptr(m,1),layout.GP_CHECKSCARY],0,100+i);
for(const seed of [1,2,3,4,5,6,7,8,9,10]){
 run('eel RNG '+seed,'goodpos',m=>record(m,1,'mlet',0,layout.S_EEL),m=>[15,15,ptr(m,0),0],0,seed);
 run('pet RNG '+seed,'tele_to_rnd_pet',m=>{for(let i=0;i<4;i++)record(m,0,'mtame',i,1);},null,0,seed);
 run('amulet RNG '+seed,'scrolltele',m=>field(m,'u.uhave.amulet',1),m=>[ptr(m,2)],0,seed);
 run('portal RNG '+seed,'mlevel_tele_trap',m=>{m._probe_level(14,5);m._probe_trap(0,layout.MAGIC_PORTAL,20,10,0,0,0);},m=>[ptr(m,0),ptr(m,3),0,1],0,seed);
 run('controlled species RNG '+seed,'u_teleport_mon',m=>record(m,1,'mflags1',0,layout.M1_TPORT_CNTRL),m=>[ptr(m,0),1],0,seed);
 run('confused prompt RNG '+seed,'level_tele',m=>{m._probe_debug(1);field(m,'HConfusion',1);const p=m._malloc(2);m.HEAPU8.set([53,0],Number(p));m._probe_input(BigInt(p));m._free(p);},null,0,seed);
}
run('rloc exhaustive shuffle RNG','rloc',m=>m._probe_option(options.onscary,1n),baseargs.rloc);
for(const n of [1,2,3,10,20])for(let seed=0;seed<30;seed++)run(`depth bounds ${n}/${seed}`,'random_teleport_level',m=>{m._probe_dungeon(0,n,1,n);m._probe_level(0,n);m._probe_option(options.Is_botlevel,1n);},null,0,seed);
for(const name of ['goodpos_onscary','goodpos'])for(const letter of [layout.S_MIMIC,layout.S_VAMPIRE,layout.S_ANGEL])for(const ward of [0,1])run(`scary ${name}/${letter}/${ward}`,name,m=>{record(m,1,'mlet',0,letter);record(m,0,'m_id',0,0);m._probe_option(options.sengr_at,BigInt(ward));},m=>name==='goodpos'?[15,15,ptr(m,0),layout.GP_CHECKSCARY]:[15,15,ptr(m,1)]);
run('vault room snapshots','teleds',m=>{m._probe_option(68,1n);m._probe_option(69,1n);},()=>[15,15,2]);
run('rider corpse revival','rloco',m=>{record(m,2,'otyp',0,layout.CORPSE);record(m,2,'corpsenm',0,layout.PM_DEATH);m._probe_option(options.revive_corpse,1n);},baseargs.rloco);
run('unpaid object shop billing','rloco',m=>{m._probe_option(71,1n);m._probe_option(options.costly_spot,1n);record(m,2,'unpaid',0,1);},baseargs.rloco);
const sourceData=JSON.parse(await readFile(join(root,'nethack-c/wasm/tu-fragments/teleport-source-data.json'),'utf8'));
assert.deepEqual([...observedRngSites].sort((a,b)=>a-b),sourceData.rngSites.map(s=>s[0]).sort((a,b)=>a-b),'Every configured source RNG origin must execute');checks++;
run('debug macro argument ordering','enexto_core',m=>{for(let x=1;x<80;x++)for(let y=0;y<21;y++)m._probe_tile(x,y,layout.STONE,0);m._probe_option(50,1n);m._probe_option(73,1n);m._probe_option(74,1n);},m=>[ptr(m,4),40,10,ptr(m,1),0]);
for(const opt of [75,76])run('first menu callback '+opt,'dotelecmd',m=>{m._probe_debug(1);field(m,'iflags.menu_requested',1);m._probe_menu(119);m._probe_option(opt,1n);},null);
// Fresh Modules must have independent persistent recursion guards and static data.
const isolated=await Promise.all(factories.map(f=>f()));isolated[1].nethackPorted={teleport:bridge};
for(let i=0;i<2;i++){isolated[i]._probe_reset(9);isolated[i]._probe_trap(0,layout.TELEP_TRAP,40,10,15,15,0);call(isolated[i],'tele_trap',[ptr(isolated[i],3)]);}
equal(decode(isolated[0],isolated[0]._probe_trace()),decode(isolated[1],isolated[1]._probe_trace()),'independent Module recursion guards');
// Controlled exception during trap callback retains the source static guard; public ABI stack restoration is checked separately.
const thrown=mods.map(m=>{m._probe_reset(91);m._probe_trap(0,layout.TELEP_TRAP,40,10,15,15,0);m._probe_option(32,1n);assert.throws(()=>call(m,'tele_trap',[ptr(m,3)]),/TELEPORT controlled callback/);m._probe_clear();call(m,'tele_trap',[ptr(m,3)]);return decode(m,m._probe_trace());});
equal(thrown[0],thrown[1],'C recursion guard remains set after nonlocal callback exit');equal(thrown[0],'','guard rejects reentry after callback exit');
const unaffected=isolated.map(m=>{m._probe_clear();call(m,'tele_trap',[ptr(m,3)]);return decode(m,m._probe_trace());});equal(unaffected[0],unaffected[1],'same bridge isolates another Module after thrown guard');assert.notEqual(unaffected[0],'','independent C guard remains clear');checks++;
console.log(`TELEPORT: ${checks} actual Emscripten-C/JS comparisons, ${invoked.size}/${meta.names.length} configured functions invoked.`);
