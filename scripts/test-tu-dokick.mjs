// Original configured EmC versus actual imported JS, controlled foreign world.
import assert from './native-test-assert.mjs';import{resolve}from'node:path';import{pathToFileURL}from'node:url';import{callDokick}from'../js/ported/dokick-runtime.js';import{C,R,T}from'../js/ported/c-runtime.js';
const dir=resolve(process.env.TELEPORT_DOKICK_PROBE_DIR??'.cache/tu-probes'),path=k=>pathToFileURL(resolve(dir,(process.env.TELEPORT_DOKICK_PROBE_DIR?'':'dokick-')+k+'.mjs'));
const{default:rf}=await import(path('reference')),{default:hf}=await import(path('hybrid'));const reference=await rf();
function text(m,p){p=Number(p);if(!p)return null;let e=p;while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.slice(p,e)).toString('latin1');}
const L={};for(let i=0;i<reference._probe_layout_count();i++)L[text(reference,reference._probe_layout_name(i))]=Number(reference._probe_layout_value(i));
const runtime={dokick:(services,name,...args)=>callDokick(new Proxy(services,{get(o,k,r){if(['rectState','trackState'].includes(k))return o[k];if(!Reflect.has(o,k))throw Error('Missing DOKICK service '+String(k));return Reflect.get(o,k,r);}}),L,name,...args)};
const modules=[reference,await hf({nethackPorted:runtime})],stacks=modules.map(m=>m._probe_stack());let comparisons=0,context='';
const names=['kickdmg','maybe_kick_monster','kick_monster','ghitm','container_impact_dmg','kick_object','really_kick_object','kickstr','watchman_thief_arrest','watchman_door_damage','kick_dumb','kick_ouch','kick_door','kick_nondoor','dokick','drop_to','impact_drop','ship_object','obj_delivery','deliver_obj_to_mon','otransit_msg','down_gate'],reached=new Set();
function snapshot(m){return{state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace()),result:text(m,m._probe_result())};}function check(){assert.deepEqual(snapshot(modules[1]),snapshot(reference),context);modules.forEach((m,i)=>assert.equal(m._probe_stack(),stacks[i]));assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);comparisons++;}
function call(name,...args){const out=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(out[1],out[0],context+':'+name);check();return out[0];}
const mon=i=>m=>m._probe_mon(i),obj=i=>m=>m._probe_obj(i),buf=i=>m=>m._probe_buffer(i),coord=m=>m._probe_coord();
const strings=new WeakMap();function str(value){return m=>{if(value===null)return 0n;let cache=strings.get(m);if(!cache)strings.set(m,cache=new Map());const b=Buffer.from(value,'latin1');let p=cache.get(value);if(!p){p=m._malloc(BigInt(Math.max(b.length+1,8192)));cache.set(value,p);}m.HEAPU8.set(b,Number(p));m.HEAPU8[Number(p)+b.length]=0;return BigInt(p);};}
function invoke(name,...args){context=name+' '+args.map(x=>typeof x==='function'?'pointer':String(x)).join(',');reached.add(name);const values=modules.map(m=>m._probe_invoke(names.indexOf(name),...Array.from({length:4},(_,i)=>typeof args[i]==='function'?BigInt(args[i](m)):BigInt.asUintN(64,BigInt(args[i]??0)))));check();return values;}
const reset=()=>call('reset'),opt=(i,v)=>call('option',i,v),field=(i,f,v,pm=-1)=>call('monset',i,pm,f,BigInt(v)),item=(i,typ,quan=1n,f=0,v=0n)=>call('item',i,typ,BigInt(quan),f,BigInt(v)),prop=(i,a=0n,b=0n,c=0n)=>call('property',i,BigInt(a),BigInt(b),BigInt(c)),global=(f,v)=>call('global',f,BigInt(v)),terrain=(typ,mask=0)=>call('terrain',11,10,typ,0,mask),trace=()=>snapshot(reference).trace,result=()=>snapshot(reference).result;
for(const m of modules)for(let i=0;i<m._probe_layout_count();i++)assert.equal(Number(m._probe_layout_value(i)),L[text(m,m._probe_layout_name(i))]);
for(const pm of [L.PM_HUMAN,L.PM_SHADE,L.PM_RED_DRAGON,L.PM_SASQUATCH])for(const attr of [9,17,18,25])for(const clumsy of [0,1,256,257]){reset();opt(0,1);opt(30,attr);field(0,0,0,pm);invoke('kickdmg',mon(0),clumsy);}
for(const peaceful of [0,1])for(const invisible of [0,1])for(const checkFail of [0,1]){reset();field(0,1,peaceful);opt(1,!invisible);opt(35,checkFail);invoke('maybe_kick_monster',mon(0),11,10);assert.match(snapshot(reference).state,/ff:0;/);}
reset();invoke('maybe_kick_monster',mon(-1),11,10);
for(const pm of [L.PM_HUMAN,L.PM_SHADE,L.PM_GRID_BUG,L.PM_RED_DRAGON,L.PM_FLOATING_EYE])for(const seed of [1,2,7,42])for(const weight of [-100,-50,-1]){reset();call('seed',seed);opt(0,1);opt(31,weight);field(0,0,0,pm);invoke('kick_monster',mon(0),11,10);}
for(const role of [L.PM_WIZARD,L.PM_MONK])for(const fumble of [0,1])for(const lev of [0,1]){reset();global(0,role);prop(L.FUMBLING,BigInt(fumble));prop(L.LEVITATION,BigInt(lev));invoke('kick_monster',mon(0),11,10);}
for(const pm of [L.PM_HORSE,L.PM_WARHORSE]){reset();global(1,pm);field(3,0,0,pm);invoke('kick_monster',mon(0),11,10);}
for(const pm of [L.PM_HUMAN,L.PM_LEPRECHAUN,L.PM_SOLDIER,L.PM_SERGEANT,L.PM_LIEUTENANT,L.PM_CAPTAIN])for(const qty of [1n,100n,10000n,9007199254740993n]){reset();field(0,1,1,pm);item(0,L.GOLD_PIECE,qty);invoke('ghitm',mon(0),obj(0));}
for(const who of [9,10,11])for(const peaceful of [0,1])for(const robbed of [0n,2000n,9007199254740993n]){reset();field(0,who,1);field(0,1,peaceful);field(0,13,robbed);item(0,L.GOLD_PIECE,500n);invoke('ghitm',mon(0),obj(0));}
for(const brokenType of [L.MIRROR,L.POT_HEALING,L.EGG])for(const qty of [1n,3n])for(const costly of [0,1]){reset();item(0,L.CHEST);item(1,brokenType,qty,7,1n);call('link',2,0,1);opt(4,costly);opt(5,costly);opt(50,50);invoke('container_impact_dmg',obj(0),10,10);}
for(const ty of [L.ROCK,L.GOLD_PIECE,L.BOULDER,L.CORPSE,L.CHEST,L.EXPENSIVE_CAMERA,L.HEAVY_IRON_BALL,L.POT_HEALING])for(const weight of [1n,39n,40n,80n]){reset();item(0,ty,2n,10,weight);invoke('kick_object',11,10,buf(0));}
for(const trap of [L.PIT,L.SPIKED_PIT,L.WEB,L.STATUE_TRAP]){reset();opt(22,1);global(11,trap);invoke('really_kick_object',11,10);}
for(const typ of [L.ROOM,L.DOOR,L.SDOOR,L.ICE,L.POOL])for(const seed of [1,2,7]){reset();terrain(typ,typ===L.DOOR?L.D_CLOSED:0);call('seed',seed);invoke('really_kick_object',11,10);}
for(const typ of [L.ROOM,L.STONE,L.DOOR,L.SDOOR,L.CORR,L.THRONE,L.FOUNTAIN,L.SINK,L.ALTAR,L.GRAVE,L.TREE,L.IRONBARS,L.STAIRS,L.LADDER])for(const seed of [1,2,7,42,7134]){reset();terrain(typ,L.D_CLOSED);call('seed',seed);invoke('kickstr',buf(0),str('item'));invoke('kick_nondoor',11,10,18);}
for(const typ of [L.DOOR,L.SDOOR])for(const mask of [L.D_CLOSED,L.D_LOCKED,L.D_TRAPPED|L.D_CLOSED,L.D_BROKEN,L.D_ISOPEN])for(const seed of [1,2,7]){reset();terrain(typ,mask);call('seed',seed);invoke('kick_door',11,10,18);}
for(const pm of [L.PM_HUMAN,L.PM_WATCHMAN,L.PM_WATCH_CAPTAIN])for(const peaceful of [0,1])for(const deaf of [0,1]){reset();field(0,1,peaceful,pm);global(13,deaf);invoke('watchman_thief_arrest',mon(0));invoke('watchman_door_damage',mon(0),11,10);}
for(const martial of [0,1]){reset();global(0,martial?L.PM_MONK:L.PM_WIZARD);invoke('kick_dumb',11,10);invoke('kick_ouch',11,10,str('item'));}
for(const pm of [L.PM_HUMAN,L.PM_GRID_BUG,L.PM_SNAKE,L.PM_HORSE]){reset();field(3,0,0,pm);invoke('dokick');}
for(const status of [L.FUMBLING,L.LEVITATION,L.BLINDED,L.WOUNDED_LEGS]){reset();prop(status,1n);invoke('dokick');}
for(const loc of [L.MIGR_NOWHERE,L.MIGR_RANDOM,L.MIGR_STAIRS_UP,L.MIGR_LADDER_UP,L.MIGR_SSTAIRS]){reset();invoke('drop_to',coord,loc,10,10);}
for(const ladder of [0,1])for(const seen of [0,1])for(const ty of [L.PIT,L.TRAPDOOR,L.HOLE]){reset();opt(20,ladder);global(9,ladder);opt(22,1);global(11,ty);global(12,seen);invoke('down_gate',10,10);}
for(const near of [0,1])for(const qty of [1n,3n]){reset();opt(20,1);item(0,L.ROCK,qty);item(1,L.ROCK,2n);call('link',1,0,1);invoke('impact_drop',obj(-1),10,10,0);invoke('obj_delivery',near);}
for(const ty of [L.ROCK,L.BOULDER,L.CHEST,L.MIRROR])for(const seed of [1,2,7]){reset();opt(20,1);call('seed',seed);item(0,ty);invoke('ship_object',obj(0),10,10,0);}
for(const where of [L.MIGR_STAIRS_UP,L.MIGR_LADDER_UP,L.MIGR_RANDOM,L.MIGR_WITH_HERO])for(const near of [0,1]){reset();item(0,L.ROCK,1n,11,BigInt(where));item(0,L.ROCK,1n,13,0n);item(0,L.ROCK,1n,14,1n);call('link',3,0,0);opt(21,1);invoke('obj_delivery',near);}
for(const flags of [0,BigInt(L.DF_ALL),BigInt(L.DF_RANDOM)]){reset();item(0,L.ROCK,1n,11,BigInt(L.MIGR_TO_SPECIES));item(0,L.ROCK,1n,12,BigInt(L.M2_HUMAN));call('link',3,0,0);invoke('deliver_obj_to_mon',mon(0),2,flags);}
for(const count of [0n,1n,2n,9007199254740993n])for(const nodrop of [0,1])for(const chain of [0,1]){reset();invoke('down_gate',10,10);invoke('otransit_msg',obj(0),nodrop,chain,count);}
// Full original native-pointer callbacks exercise their actual private JS bodies.
for(const which of [0,1]){reset();field(0,1,1,L.PM_WATCHMAN);opt(7,1);opt(0,1);terrain(L.DOOR,L.D_LOCKED);call('seed',which?2:1);invoke('kick_door',11,10,which?-100:100);assert.match(trace(),which?/iterxy:0:1;/:/iter:0:1;/,'actual native iterator invokes private JS callback');}
// A native bhit call writes the actual shared kicked-object pointer, not a mirror.
for(const clear of [0,1]){reset();opt(62,clear);invoke('really_kick_object',11,10);assert.match(trace(),/bhit:1:0:\d+:\d+:0:0:1;/);if(clear)assert.match(snapshot(reference).state,/kick:-1;/);}
// Preserve next-pointer traversal when native ownership callbacks rewrite links.
reset();field(0,0,0,L.PM_ORC);opt(16,1);for(const i of [0,1]){item(i,L.ROCK,1n,11,BigInt(L.MIGR_TO_SPECIES));item(i,L.ROCK,1n,12,BigInt(L.M2_ORC));for(const m of modules)m._probe_oname(i,str('Orc Gang')(m));}call('link',0,0,1);call('link',3,0,0);invoke('deliver_obj_to_mon',mon(0),2,BigInt(L.DF_ALL));assert.equal((trace().match(/christen_orc:/g)||[]).length,2);
// Every declared callback stage must actually reenter and grow both real Modules.
for(let stage=1;stage<=16;stage++){
 reset();opt(80,stage);opt(81,stage);const before=modules.map(m=>m.HEAPU8.byteLength);
 if(stage===1)invoke('kick_ouch',11,10,str('item'));
 else if(stage===2){field(0,1,1,L.PM_WATCHMAN);invoke('watchman_thief_arrest',mon(0));}
 else if(stage===3)invoke('maybe_kick_monster',mon(0),11,10);
 else if(stage===4||stage===14)invoke('kickdmg',mon(0),0);
 else if(stage===5){global(1,L.PM_HORSE);field(3,0,0,L.PM_HORSE);invoke('kick_monster',mon(0),11,10);}
 else if(stage===6){item(0,L.ROCK,2n);invoke('really_kick_object',11,10);}
 else if(stage===7){item(0,L.CHEST);item(1,L.MIRROR);call('link',2,0,1);opt(4,1);opt(5,1);invoke('container_impact_dmg',obj(0),10,10);}
 else if(stage===8||stage===9||stage===15){if(stage===15)opt(62,1);invoke('really_kick_object',11,10);}
 else if(stage===10){opt(15,1);terrain(L.DOOR,L.D_CLOSED);call('terrain',12,10,L.STONE,0,0);invoke('kick_ouch',12,10,str('item'));}
 else if(stage===11)invoke('dokick');
 else if(stage===12){call('seed',7134);terrain(L.SINK);opt(26,1);invoke('kick_nondoor',11,10,18);assert.match(trace(),/makemon:/,'native makemon path reached');}
 else if(stage===13){item(0,L.GOLD_PIECE,2n);invoke('really_kick_object',11,10);assert.match(trace(),/scatter:/,'original coins path reached');}
 else if(stage===16){opt(33,L.SLT_ENCUMBER+1);invoke('dokick');}
 assert.match(trace(),/nested:/,'callback stage '+stage);assert.match(trace(),new RegExp('grow:'+stage+';'),'callback stage '+stage);modules.forEach((m,i)=>assert.ok(m.HEAPU8.byteLength>before[i],'actual growth '+stage));
}
const other=await hf({nethackPorted:runtime});other._probe_reset();other._probe_invoke(names.indexOf('down_gate'),10n,10n,0n,0n);assert.equal(text(other,other._probe_result()),String(L.MIGR_NOWHERE));assert.equal(C,undefined);
assert.deepEqual([...reached].sort(),names.slice().sort());
console.log(`DOKICK first-pass EmC: ${comparisons} exact comparisons passed; all 22 functions; native/shared/public pending.`);
