import { DataView, Int32Array, assertStackRestored, allocationMetric, assertMemoryGrowth, memoryCheckpoint, referenceBackend, referenceLabel } from './native-test-backend.mjs';
const referenceFactory = referenceBackend('priest', emscriptenReferenceFactory);
import assert from './native-test-assert.mjs';
import {readFileSync} from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/priest-reference.mjs';
import hybridFactory from '../.cache/tu-probes/priest-hybrid.mjs';
import {createPortedRuntime} from '../js/backends/emscripten/runtime.js';
import {C,R,T} from '../js/c-runtime/context.js';

const layouts=JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url)));
const L=layouts.priest,runtime=createPortedRuntime(layouts);
const modules=[await referenceFactory(),await hybridFactory({nethackPorted:runtime})];
const stacks=modules.map(m=>m._probe_stack());
let comparisons=0;
function text(m,p){
    if(!p)return null;
    p=Number(p);let end=p;while(m.HEAPU8[end])end++;
    return Buffer.from(m.HEAPU8.slice(p,end)).toString('latin1');
}
function bytes(m,p,n){return Buffer.from(m.HEAPU8.slice(Number(p),Number(p)+n));}
function snapshot(m){return {
    state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace()),
    output:text(m,m._probe_pointer(5,0)),rng:m._probe_rng_state()>>>0,count:m._probe_rng_count()
};}
function check(){
    assert.deepEqual(snapshot(modules[1]),snapshot(modules[0]));
    assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);
    modules.forEach((m,i)=>assertStackRestored(m, stacks[i]));comparisons++;
}
function call(name,...args){
    const longIndex={monster_field:2,hero:1,prop:2,epri:2,moves:0}[name];
    if(longIndex!==undefined)args[longIndex]=BigInt(args[longIndex]);
    const out=modules.map(m=>m['_probe_'+name](...args));
    assert.deepEqual(out[1],out[0],`${name}:${args}`);check();comparisons++;
    return out[0];
}
function reset(seed=1){call('reset',seed);}
function act(op,index=0,a=0,b=0,c=0,d=0,e=0,f=0){return call('action',op,index,a,b,c,d,e,f);}
function hero(k,v){call('hero',k,v);}
function mf(i,k,v){call('monster_field',i,k,v);}
function ep(i,k,v){call('epri',i,k,v);}
function prop(p,k=0,v=1n){call('prop',p,k,v);}
function trace(){return text(modules[0],modules[0]._probe_trace());}
function output(){return text(modules[0],modules[0]._probe_pointer(5,0));}
function fields(prefix='hero'){
    return text(modules[0],modules[0]._probe_snapshot()).split(';').find(s=>s.startsWith(prefix+':')).split(':').slice(1);
}
function rng(values){
    modules.forEach(m=>{new Int32Array(m.HEAPU8.buffer,Number(m._probe_rng_pointer()),values.length).set(values);m._probe_rng_length(values.length);});check();
}
function input(k,s){
    modules.forEach(m=>{const b=Buffer.from(s+'\0','latin1'),p=Number(m._malloc(BigInt(b.length)));
        m.HEAPU8.set(b,p);m._probe_input(k,BigInt(p));m._free(p);});check();
}
function candidates(rows){
    modules.forEach(m=>{
        const base=Number(m._probe_candidates_pointer()),v=new DataView(m.HEAPU8.buffer);
        m.HEAPU8.fill(0,base,base+L.mfndposSize);
        rows.forEach(([x,y,info=0n],i)=>{
            v.setInt16(base+L.mfp_poss+i*L.coordSize+L.coord_x,x,true);
            v.setInt16(base+L.mfp_poss+i*L.coordSize+L.coord_y,y,true);
            v.setBigInt64(base+L.mfp_info+i*L.longSize,BigInt.asIntN(64,BigInt(info)),true);
        });m._probe_candidates_count(rows.length);
    });check();
}
function readEpri(field,index=0,signed=true){
    const m=modules[0],p=Number(m._probe_pointer(2,index))+L['epri_'+field];
    const size=L['epri_'+field+'_size'],v=new DataView(m.HEAPU8.buffer);
    return size===8?v[signed?'getBigInt64':'getBigUint64'](p,true):BigInt(v['get'+(signed?'Int':'Uint')+size*8](p,true));
}
function shrineLevel(index=0){
    const m=modules[0],p=Number(m._probe_pointer(2,index))+L.epri_shrlevel,v=new DataView(m.HEAPU8.buffer);
    return [v.getInt16(p+L.level_dnum,true),v.getInt16(p+L.level_dlevel,true)];
}
function priest(index=0,pm=L.PM_ALIGNED_CLERIC,x=11,y=10){
    call('add_monster',index,pm,x,y);act(0,index);mf(index,2,1);
    ep(index,0,L.A_LAWFUL);ep(index,1,L.ROOMOFFSET);ep(index,2,12);ep(index,3,10);
    ep(index,4,1);ep(index,5,2);
}
reset();
for(const m of modules)for(let i=0;i<m._probe_layout_count();i++){
    const k=text(m,m._probe_layout_name(i)),v=m._probe_layout_value(i);
    assert.equal(typeof L[k]==='string'?BigInt.asUintN(64,v).toString():Number(BigInt.asIntN(64,v)),L[k],k);
}
const required=['PM_HUMAN','PM_ALIGNED_CLERIC','PM_HIGH_CLERIC','PM_ANGEL','PM_GHOST','PM_DEATH',
    'ROOMOFFSET','TEMPLE','ROOM','CORR','DOOR','ALTAR','AM_SHRINE','AM_LAWFUL','AM_CHAOTIC','A_LAWFUL',
    'A_CHAOTIC','A_NEUTRAL','A_NONE','CONFLICT','DISPLACED','INVIS','HALLUC','HALLUC_RES','DEAF',
    'PROTECTION','CLAIRVOYANT','INTRINSIC','FROMOUTSIDE','ARTICLE_NONE','ARTICLE_A','ARTICLE_THE','ARTICLE_YOUR'];
for(const k of required)assert.ok(Number.isSafeInteger(L[k]),k);

// Allocation retains mextra, preserves an existing extension, and frees only EPRI.
for(const id of [0,1,0x7fffffff,0xffffffff]){
    reset();call('add_monster',0,L.PM_ALIGNED_CLERIC,11,10);mf(0,0,id);act(0);
    assert.equal(readEpri('parentmid',0,false),BigInt(id));
    const initial=modules.map(m=>bytes(m,m._probe_pointer(2,0),L.epriSize));
    const expected=Buffer.alloc(L.epriSize);expected.writeUInt32LE(id,L.epri_parentmid);
    assert.deepEqual(initial[0],expected);
    const pointers=modules.map(m=>m._probe_pointer(2,0));
    modules.forEach(m=>m.HEAPU8.fill(0xa5,Number(m._probe_pointer(2,0)),Number(m._probe_pointer(2,0))+L.epriSize));
    act(0);modules.forEach((m,i)=>{
        assert.equal(m._probe_pointer(2,0),pointers[i]);
        assert.ok(bytes(m,m._probe_pointer(2,0),L.epriSize).every(b=>b===0xa5));
    });
    mf(0,2,1);act(1);assert.equal(call('free_count'),1);
    modules.forEach(m=>{assert.notEqual(m._probe_pointer(1,0),0n);assert.equal(m._probe_pointer(2,0),0n);});
    assert.equal(fields('m0')[4],'0');act(1);assert.equal(call('free_count'),1);act(0);
    assert.equal(readEpri('parentmid',0,false),BigInt(id));
}
reset();call('add_monster',0,L.PM_HUMAN,11,10);act(1);assert.equal(call('free_count'),0);

// Candidate fields are real coord16 arrays and signedlong64 information masks.
for(const approach of [-1,0,1,256])for(const avoid of [0,1]){
    reset();priest();candidates([[12,10,1n<<60n],[13,10,0n],[11,11,1n<<63n]]);rng(Array(20).fill(0));
    act(2,0,0,approach,0,avoid,13,10);
}
reset();priest();assert.equal(act(2,0,0,1,0,0,11,10),0n);assert.ok(!trace().includes('mfndpos:'));
reset();priest();mf(0,6,1);candidates([[12,10,0n],[13,10,0n]]);rng([1,0]);act(2,0,0,1,0,1,13,10);
for(const shop of [0,1])for(const following of [0,1])for(const inShop of [0,1]){
    reset();priest();if(shop){mf(0,4,1);mf(0,15,following);}
    call('terrain',12,10,L.CORR,0);candidates([[12,10,0n]]);
    act(2,0,inShop,1,0,0,13,10);
}
for(const uondoor of [0,1])for(const flags of [BigInt(L.NOTONL),0n]){
    reset();priest();mf(0,4,1);candidates([[12,10,flags]]);act(2,0,1,1,uondoor,1,13,10);
}
reset();priest();candidates([[12,10,BigInt(L.NOTONL)]]);
assert.equal(act(2,0,0,1,0,1,13,10),1n);assert.match(trace(),/place:0:12:10/);
reset();priest();candidates([[12,10,BigInt(L.ALLOW_ROCK)|(1n<<63n)]]);
assert.equal(act(2,0,0,1,0,0,13,10),1n);assert.match(trace(),/boulder:0:12:10/);assert.ok(!trace().includes('place:'));
for(const status of [0,1,2,3])for(const occupied of [0,1]){
    reset();priest();if(occupied)call('add_monster',1,L.PM_HUMAN,12,10);
    call('option',1,status);candidates([[12,10,BigInt(L.ALLOW_M)|(1n<<55n)]]);
    const result=act(2,0,0,1,0,0,13,10);
    assert.equal(result,status===2?-2n:status===3?1n:occupied?0n:1n);
}
reset();priest();candidates([[10,10,0n]]);assert.equal(act(2,0,0,1,0,0,9,10),0n);
reset();priest();mf(0,4,1);call('option',2,1);candidates([[12,10,0n]]);act(2,0,0,1,0,0,13,10);assert.match(trace(),/special-room:0/);
reset();priest();candidates(Array.from({length:9},(_,i)=>[12+(i%3),9+Math.trunc(i/3),(1n<<60n)|BigInt(i)]));act(2,0,0,0,0,0,15,10);

// Temple identity and shrine tests use real room bytes, alignments and levels.
for(const roomString of ['',String.fromCharCode(L.ROOMOFFSET),String.fromCharCode(L.ROOMOFFSET+1,L.ROOMOFFSET)]){
    reset();input(0,roomString);act(3);
}
reset();call('room',1,L.TEMPLE,20,25,5,10);input(0,String.fromCharCode(L.ROOMOFFSET+1,L.ROOMOFFSET));assert.equal(act(3),BigInt(L.ROOMOFFSET+1));
reset();assert.equal(act(4,-1,11,10),0n);assert.equal(act(5,-1),0n);assert.equal(act(11,-1),0n);
for(const aligned of [0,1])for(const altar of [0,1])for(const shrine of [0,1]){
    reset();priest();call('terrain',12,10,altar?L.ALTAR:L.ROOM,(shrine?L.AM_SHRINE:0)|(aligned?L.AM_LAWFUL:L.AM_CHAOTIC));
    assert.equal(act(5),BigInt(aligned&&altar&&shrine?1:0));act(11);
}
reset();priest();ep(0,5,3);assert.equal(act(4,0,11,10),0n);assert.equal(act(5),0n);
reset();priest();call('option',3,L.ROOMOFFSET+1);assert.equal(act(5),0n);
reset();priest();call('add_monster',1,L.PM_HUMAN,13,10);assert.equal(act(12,0,L.ROOMOFFSET),0n);mf(0,1,0);assert.equal(act(12,0,L.ROOMOFFSET),-1n);
for(const hostile of [0,1])for(const near of [0,1])for(const conflict of [0,1]){
    reset();priest();mf(0,5,!hostile);call('option',5,near);if(conflict)prop(L.CONFLICT);
    prop(L.DISPLACED);candidates([[12,9,0n],[11,9,0n]]);rng(Array(20).fill(0));act(6);
    assert.equal(trace().includes('attacku:'),(!!hostile||!!conflict)&&!!near);
}
reset();priest();prop(L.INVIS);candidates([[12,9,0n]]);rng([0,0]);act(6);
reset();priest();ep(0,5,3);assert.equal(act(6),-1n);

// Shrine creation invokes actual native allocation callbacks and source ownership.
for(const sanctum of [0,1])for(const alignment of [L.A_LAWFUL,L.A_NONE])for(const fail of [0,1]){
    reset();hero(8,4);hero(9,5);call('terrain',12,10,L.ALTAR,L.AM_SHRINE|(alignment===L.A_NONE?0:L.AM_LAWFUL));
    call('option',7,fail);rng([0,0,1]);act(7,0,0,12,10,sanctum);
    if(!fail){assert.equal(fields('m0')[4],'1');assert.equal(fields('m0')[5],'0');assert.match(trace(),/learn:0:/);assert.equal(trace().includes('mongets:'),!!sanctum&&alignment===L.A_NONE);}
}
reset();call('option',6,8);rng([0,0,0]);act(7,0,0,12,10,0);assert.match(trace(),/makemon:.*:12:10:/);
reset();call('add_monster',0,L.PM_HUMAN,11,10);rng([0,0,0]);act(7,0,0,12,10,0);assert.match(trace(),/rloc:0:/);

// Names retain callerbuffer identity and source priest/minion/article rules.
for(const pm of [L.PM_ALIGNED_CLERIC,L.PM_HIGH_CLERIC,L.PM_ANGEL,L.PM_HUMAN])for(const kind of [0,1,2])for(const article of [L.ARTICLE_NONE,L.ARTICLE_A,L.ARTICLE_THE,L.ARTICLE_YOUR]){
    reset();priest(0,pm,30,10);if(kind===0)mf(0,2,0);if(kind===2){mf(0,2,0);call('emin',0,L.A_CHAOTIC,1);mf(0,3,1);mf(0,14,3);}
    mf(0,13,1);mf(0,12,1);hero(8,6);hero(9,7);act(9,0,article,0);assert.match(trace(),/returned:1/);
}
for(const hallucinating of [0,1])for(const resisted of [0,1])for(const personal of [0,1])for(const reveal of [0,1]){
    reset();priest(0,L.PM_HIGH_CLERIC,30,10);hero(8,6);hero(9,7);if(hallucinating)prop(L.HALLUC);if(resisted)prop(L.HALLUC_RES);call('option',9,personal?'='.charCodeAt(0):0);act(9,0,L.ARTICLE_A,reveal);
}
for(const alignment of [L.A_CHAOTIC,L.A_NEUTRAL,L.A_LAWFUL,L.A_NONE])for(const minion of [0,1]){
    reset();priest();if(minion){mf(0,2,0);call('emin',0,alignment,0);mf(0,3,1);}else ep(0,0,alignment);
    assert.equal(act(8),BigInt(alignment));hero(2,alignment);assert.equal(act(10),1n);
}
reset();call('add_monster',0,L.PM_HUMAN,11,10);act(8);act(9,0,L.ARTICLE_A);

// Temple feedback timers remain exact beyond Number's integer precision.
for(const moves of [100n,(1n<<53n)+17n,(1n<<63n)-100000n])for(const deaf of [0,1])for(const frozen of [0,1]){
    reset();priest();call('moves',moves);hero(10,deaf);mf(0,10,frozen?15:0);rng(Array(100).fill(0));act(13,0,L.ROOMOFFSET);
    assert.match(trace(),/achievement:/);assert.match(trace(),/mapseen:0/);assert.equal(trace().includes('intones:'),!deaf);
    if(!deaf)assert.equal(readEpri('intone_time'),moves+10n);
    act(13,0,L.ROOMOFFSET);act(14);for(const f of ['intone_time','enter_time','hostile_time','peaceful_time'])assert.equal(readEpri(f),0n);
}
for(const record of [-4,0,14])for(const aligned of [0,1]){
    reset();priest();hero(3,record);if(!aligned)ep(0,0,L.A_CHAOTIC);ep(0,9,(1n<<53n)+70n);ep(0,10,(1n<<53n)+100n);call('moves',(1n<<53n)+20n);rng(Array(60).fill(0));act(13,0,L.ROOMOFFSET);
}
reset();priest();input(1,String.fromCharCode(L.ROOMOFFSET));act(13,0,L.ROOMOFFSET);assert.ok(!trace().includes('achievement:'));
for(const peaceful of [0,1]){reset();priest(0,L.PM_HIGH_CLERIC);hero(8,4);hero(9,5);ep(0,4,4);ep(0,5,5);mf(0,5,peaceful);rng(Array(100).fill(0));act(13,0,L.ROOMOFFSET);assert.match(trace(),/Moloch|desecrate/);}
for(const message of [0,1,2,3])for(const ghost of [0,1])for(const visible of [0,1]){
    reset();call('option',11,visible);call('option',12,0);hero(12,1);rng([message,ghost?0:1]);act(13,0,L.ROOMOFFSET);
    assert.equal(trace().includes('nomul:-3'),!!ghost);if(ghost)assert.equal(fields()[8],'-3');
}
reset();priest();mf(0,2,0);act(14);assert.match(trace(),/impossible:/);

// Dialogue covers conduct, charity, unsignedcheapskate arithmetic and donations.
for(const gnostic of [0n,1n,(1n<<53n)+1n,-1n]){
    reset();priest();hero(5,gnostic);hero(15,0);act(15);assert.equal(BigInt(fields()[2]),gnostic+1n);assert.equal(trace().includes('livelog:'),gnostic===0n);
}
for(const aligned of [0,1])for(const record of [-1,10])for(const money of [0,1,2,7]){
    reset();priest();if(!aligned){ep(0,0,L.A_CHAOTIC);call('terrain',12,10,L.ALTAR,L.AM_SHRINE|L.AM_CHAOTIC);}
    hero(3,record);hero(15,money);act(15);
    assert.equal(trace().includes('money2u:'),!!aligned&&record>=0&&money>0);
    if(!aligned||record<0)assert.match(trace(),/not interested/);
}
for(const helpless of [0,1]){reset();priest();mf(0,8,helpless);mf(0,5,0);rng([1]);act(15);assert.match(trace(),/verbalize:/);}
reset();priest();mf(0,8,1);call('option',10,1);act(15);assert.match(trace(),/their reverie/);
reset();priest();mf(0,11,1);act(15);assert.match(trace(),/doesn't want/);
for(const count of [0,1,0x80000000,0xffffffff])for(const peak of [0,1,30,0x7fffffff]){
    reset();priest();ep(0,6,count);hero(4,peak);hero(14,10000);hero(16,0);rng([0]);act(15);assert.match(trace(),/bribe:/);assert.equal(readEpri('cheapskate_count',0,false),BigInt((count+1)>>>0));
}
for(const wallet of [100,500,1500,5000])for(const donation of [0,1,100,149,150,200,299,300,449,450,900]){
    if(donation>wallet)continue;
    reset();priest();hero(4,1);hero(14,wallet);hero(16,donation);rng(Array(100).fill(0));act(15);
    assert.equal(BigInt(fields()[3]),BigInt(wallet-donation));assert.match(trace(),/bribe:/);
}
for(const protection of [0,1])for(const magnitude of [0,8,9,19,20]){
    reset();priest();hero(4,1);hero(14,400);hero(16,300);hero(6,magnitude);if(protection)prop(L.PROTECTION,0,L.FROMOUTSIDE);rng(Array(20).fill(0));act(15);assert.match(trace(),/devotion|generosity/);
}
for(const old of [4999n,5000n,5001n]){
    reset();priest();hero(3,-3);hero(4,1);hero(14,500);hero(16,450);call('moves',(1n<<53n)+10000n);hero(7,(1n<<53n)+10000n-old);rng([0]);act(15);assert.equal(fields()[1],old>5000n?'0':'-1');
}
for(const donation of [0n,1n,(1n<<53n)+1n]){
    reset();priest();hero(14,(1n<<53n)+101n);hero(16,donation);rng([0]);act(15);
    assert.equal(BigInt(fields()[3]),(1n<<53n)+101n-donation);
}

// Paid noncoaligned priests still have a valid shrine; alignment affects rewards.
for(const aligned of [0,1])for(const record of [-4,10])for(const donation of [0,200,450]){
    reset();priest();
    if(!aligned){
        ep(0,0,L.A_CHAOTIC);
        call('terrain',12,10,L.ALTAR,L.AM_SHRINE|L.AM_CHAOTIC);
    }
    hero(3,record);hero(4,1);hero(14,500);hero(16,donation);rng(Array(20).fill(0));
    act(15);assert.match(trace(),/bribe:/);
    const adjustment=aligned?(donation===0?-1:donation===200&&record===-4?1:donation===450?2:0):0;
    assert.equal(trace().includes('adjalign:'),adjustment!==0);
    assert.equal(Number(fields()[1]),record+adjustment);
    if(donation===200)assert.match(trace(),/blessing/);
}
// A valid co-aligned roaming minion refuses a strayed hero before the cranky path.
reset();priest();mf(0,2,0);call('emin',0,L.A_LAWFUL,0);mf(0,3,1);hero(3,-1);
act(15);assert.match(trace(),/doesn't want anything to do with you/);
assert.equal(fields('m0')[7],'0');assert.ok(!trace().includes('bribe:'));
assert.ok(!trace().includes('rn2:'));

// Roamers, sanctuary, divine attacks and shrine restoration ownership.
for(const alignment of [L.A_LAWFUL,L.A_CHAOTIC,L.A_NONE])for(const peaceful of [0,1])for(const fail of [0,1]){
    reset();call('option',7,fail);const id=act(16,0,L.PM_ANGEL,alignment,11,10,peaceful);
    assert.equal(id,fail?-1n:0n);if(!fail){assert.equal(fields('m0')[5],'1');assert.equal(fields('m0')[4],'0');act(17);}
}
for(const pm of [L.PM_HUMAN,L.PM_ANGEL,L.PM_DEATH])for(const record of [-4,-3,10]){
    reset();priest();call('add_monster',1,pm,12,11);hero(3,record);act(18,1,12,11);act(18,-1,12,11);
}
reset();priest();assert.equal(act(18,-1,12,11),1n);mf(0,5,0);assert.equal(act(18,-1,12,11),0n);
for(const line of [0,1])for(const side of [0,1,2,3])for(const doorway of [0,1]){
    reset();priest();call('option',13,line);if(doorway){hero(0,[4,16,10,10][side]);hero(1,[10,10,4,16][side]);call('terrain',[4,16,10,10][side],[10,10,4,16][side],L.DOOR,0);}rng([side,side%3]);act(19);
    assert.equal(trace().includes('buzz:'),!!line);assert.equal(fields()[10],'1');assert.equal(fields()[11],'1');
}
for(const altar of [L.ALTAR,L.ROOM])for(const aligned of [0,1]){
    reset();priest();call('terrain',12,10,altar,L.AM_SHRINE|(aligned?L.AM_LAWFUL:L.AM_CHAOTIC));act(20);
    assert.equal(fields('m0')[4],altar===L.ALTAR&&aligned?'1':'0');
    if(altar!==L.ALTAR||!aligned){assert.equal(fields('m0')[5],'1');assert.equal(call('free_count'),1);}
}
reset();priest();priest(1,L.PM_ALIGNED_CLERIC,13,10);ep(1,5,3);call('add_monster',2,L.PM_HUMAN,14,10);act(21);assert.match(trace(),/gone:1/);assert.equal(fields('m0')[3],'20');
for(const ghostly of [0,1,256])for(const loaded of [0,1]){
    reset();priest();ep(0,5,7);hero(9,loaded?2:0);act(22,0,ghostly);assert.deepEqual(shrineLevel(),[1,ghostly===1&&loaded?2:7]);
    assert.equal(trace().includes('assign:'),ghostly===1&&!!loaded);
}
// Native callbacks can reenter source or grow memory during real C ABI calls.
for(const stage of [1,2,3,4,5,6,7,8]){
    reset();if(stage!==1&&stage!==3)priest();
    call('option',30,stage);call('option',31,stage);const sizes=modules.map(m=>allocationMetric(m));
    if(stage===1){call('add_monster',0,L.PM_HUMAN,11,10);act(0);}
    if(stage===2){candidates([[12,10,1n<<60n]]);act(2,0,0,1,0,0,13,10);}
    if(stage===3){rng([0,0,0]);act(7,0,0,12,10,0);}
    if(stage===4){hero(14,100);hero(16,1);act(15);}
    if(stage===5)act(19);
    if(stage===6)act(1);
    if(stage===7){rng(Array(100).fill(0));act(13,0,L.ROOMOFFSET);}
    if(stage===8)act(5);
    assert.match(trace(),/nested-temple:/);assert.match(trace(),new RegExp('grew:'+stage));
    modules.forEach((m,i)=>assert.ok(allocationMetric(m)>sizes[i]));
}
reset();priest();call('option',0,0);candidates([[12,10,0n]]);act(2,0,0,0,0,0,13,10);assert.match(trace(),/@;/);
// Shared runtime caches must not share native monster extensions or hero state.
reset();priest();const before=snapshot(modules[1]),other=await hybridFactory({nethackPorted:runtime});other._probe_reset(1);
assert.equal(other._probe_pointer(2,0),0n);other._probe_add_monster(0,L.PM_HUMAN,11,10);
other._probe_action(0,0,0,0,0,0,0,0);assert.notEqual(other._probe_pointer(2,0),0n);
assert.deepEqual(snapshot(modules[1]),before);other._probe_action(1,0,0,0,0,0,0,0);
assert.deepEqual(snapshot(modules[1]),before);check();reset();
console.log(`PRIEST: ${comparisons} ${referenceLabel}/hybrid extension, movement, temple, donation, ownership and RNG-site comparisons checked.`);
