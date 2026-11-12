import { DataView, assertStackRestored, allocationMetric, assertMemoryGrowth, memoryCheckpoint, referenceBackend, referenceLabel } from './native-test-backend.mjs';
const referenceFactory = referenceBackend('light', emscriptenReferenceFactory);
import assert from './native-test-assert.mjs';
import {readFileSync} from 'node:fs';
import emscriptenReferenceFactory from '../.cache/tu-probes/light-reference.mjs';
import hybridFactory from '../.cache/tu-probes/light-hybrid.mjs';
import {createPortedRuntime} from '../js/backends/emscripten/runtime.js';
import {C,R,T} from '../js/c-runtime/context.js';
const layouts=JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url)));
const L=layouts.light,runtime=createPortedRuntime(layouts);
const modules=[await referenceFactory(),await hybridFactory({nethackPorted:runtime})];
const stacks=modules.map(m=>m._probe_stack());
const nativeSource=readFileSync(new URL('../.cache/wasm64-build/tree/src/light.c',import.meta.url),'utf8');
const fixtureSource=readFileSync(new URL('./tu-light-probe.c',import.meta.url),'utf8');
const nativeVision=readFileSync(new URL('../.cache/wasm64-build/tree/src/vision.c',import.meta.url),'utf8');
for(const name of ['circle_data','circle_start']){
    const pattern=new RegExp('const coordxy '+name+'\\[\\]\\s*=\\s*\\{[\\s\\S]*?\\};');
    const fixtureMatch=fixtureSource.match(pattern),nativeMatch=nativeVision.match(pattern);
    assert.ok(fixtureMatch,`fixture ${name} initializer`);assert.ok(nativeMatch,`native ${name} initializer`);
    assert.equal(fixtureMatch[0],nativeMatch[0]);
}
const flag=name=>Number(nativeSource.match(new RegExp('#define '+name+' (0x[0-9a-f]+)'))[1]);
const SHOW=flag('LSF_SHOW'),FIXUP=flag('LSF_NEEDS_FIXUP'),PROBLEM=flag('LSF_IS_PROBLEMATIC');
let comparisons=0,ioMode='none',fileMode=L.WRITING;
function text(m,p){if(!p)return null;p=Number(p);let e=p;while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.slice(p,e)).toString('latin1');}
function bytes(m,p,n){return Buffer.from(m.HEAPU8.slice(Number(p),Number(p)+n));}
function ptrLabel(m,p){
    p=BigInt(p);if(!p)return 'null';
    for(let i=0;i<16;i++){
        if(p===m._probe_pointer(0,i))return 'o'+i;
        if(p===m._probe_pointer(1,i))return 'm'+i;
    }
    if(p===m._probe_pointer(1,-1))return 'hero';
    for(let i=0;i<m._probe_node_count();i++)if(p===m._probe_node_pointer(i))return 'ls'+i;
    return null;
}
function normalizeTrace(m,s){
    return s.replace(/0x[0-9a-f]+/gi,token=>ptrLabel(m,BigInt(token))??token);
}
function nodeBytes(m,p){
    const raw=bytes(m,p,L.lightSourceSize),view=new DataView(raw.buffer,raw.byteOffset,raw.byteLength);
    const id=view.getBigUint64(L.ls_id,true),flags=view.getInt16(L.ls_flags,true);
    raw.fill(0,L.ls_next,L.ls_next+L.pointerSize);
    let label=null;
    if(!(flags&FIXUP)||(flags&PROBLEM))label=ptrLabel(m,id);
    if(label!==null)raw.fill(0,L.ls_id,L.ls_id+L.anythingSize);
    return {raw,id:label??id.toString()};
}
function nodes(m){return Array.from({length:m._probe_node_count()},(_,i)=>nodeBytes(m,m._probe_node_pointer(i)));}
function ioBytes(m){
    const raw=bytes(m,m._probe_io_pointer(),m._probe_io_size()),ids=[];
    let offset=ioMode==='count'?L.intSize:0;
    if(ioMode!=='none')for(;offset+L.lightSourceSize<=raw.length;offset+=L.lightSourceSize){
        const part=nodeBytes(m,Number(m._probe_io_pointer())+offset);part.raw.copy(raw,offset);ids.push(part.id);
    }
    return {raw,ids};
}
function snapshot(m){return {
    state:text(m,m._probe_snapshot()),trace:normalizeTrace(m,text(m,m._probe_trace())),nodes:nodes(m),
    vision:bytes(m,m._probe_pointer(3,0),L.COLNO*L.ROWNO*L.seenSize),io:ioBytes(m)
};}
function check(){
    assert.deepEqual(snapshot(modules[1]),snapshot(modules[0]));
    assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);
    modules.forEach((m,i)=>assertStackRestored(m, stacks[i]));comparisons++;
}
function call(name,...args){
    if(['object','monster_field','ls'].includes(name))args[2]=BigInt(args[2]);
    if(name==='nhfile'&&args[0]===0)fileMode=args[1];
    const out=modules.map(m=>m['_probe_'+name](...args));
    assert.deepEqual(out[1],out[0],`${name}:${args}`);check();comparisons++;return out[0];
}
function reset(){ioMode='none';fileMode=L.WRITING;call('reset');}
function act(op,a=0,b=0,c=0,d=0,e=0){
    if(op===10&&(fileMode&(L.WRITING|L.COUNTING)))ioMode='count';
    if((op===14&&b&&b!==256)||op===16)ioMode='bare';
    return call('action',op,a,b,c,d,e);
}
function object(i,k,v){call('object',i,k,v);}
function mon(i,k,v){call('monster_field',i,k,v);}
function ls(i,k,v){call('ls',i,k,v);}
function id(kind,index=0,raw=0n){
    modules.forEach(m=>{
        const p=Number(m._probe_union_pointer()),v=new DataView(m.HEAPU8.buffer);
        const value=kind==='obj'?m._probe_pointer(0,index):kind==='mon'?m._probe_pointer(1,index):BigInt(raw);
        v.setBigUint64(p,BigInt.asUintN(64,value),true);
    });check();
}
function add(kind,index=0,range=2,x=10,y=10){
    id(kind,index);return act(1,x,y,range,kind==='obj'?L.LS_OBJECT:L.LS_MONSTER);
}
function trace(){return normalizeTrace(modules[0],text(modules[0],modules[0]._probe_trace()));}
function fields(){return text(modules[0],modules[0]._probe_snapshot()).split(';')[0].split(':').slice(1);}
function litCount(){return [...snapshot(modules[0]).vision].filter(v=>v&L.TEMP_LIT).length;}
function rowField(i,field){
    const m=modules[0],p=Number(m._probe_node_pointer(i))+L['ls_'+field];
    return new DataView(m.HEAPU8.buffer).getInt16(p,true);
}
function load(data,mode='count'){
    ioMode=mode;modules.forEach(m=>{m.HEAPU8.set(data,Number(m._probe_io_pointer()));m._probe_io_length(data.length);m._probe_io_position(0);});check();
}
reset();
for(const m of modules)for(let i=0;i<m._probe_layout_count();i++){
    const k=text(m,m._probe_layout_name(i)),v=m._probe_layout_value(i);
    assert.equal(typeof L[k]==='string'?BigInt.asUintN(64,v).toString():Number(BigInt.asIntN(64,v)),L[k],k);
}
for(const k of ['LS_OBJECT','LS_MONSTER','LS_NONE','MAX_RADIUS','OBJ_FREE','OBJ_FLOOR','OBJ_BURIED','OBJ_INVENT',
    'FM_YOU','FM_FMON','FM_MIGRATE','FM_MYDOGS','FM_EVERYWHERE','TEMP_LIT','COULD_SEE','TALLOW_CANDLE',
    'WAX_CANDLE','MAGIC_LAMP','OIL_LAMP','GOLD_DRAGON_SCALE_MAIL','CANDELABRUM_OF_INVOCATION'])assert.ok(Number.isSafeInteger(L[k]),k);
const PANIC=call('panic_code');

// Original zeroing, complete anything copies, list order and true zero-before-free.
for(const range of [-1,0,1,L.MAX_RADIUS,L.MAX_RADIUS+1])for(const type of [L.LS_OBJECT,L.LS_MONSTER,L.LS_NONE]){
    reset();id(type===L.LS_MONSTER?'mon':'obj',0);act(0,10,10,range,type);
    assert.equal(call('node_count'),range>0&&range<=L.MAX_RADIUS?1:0);
}
reset();id('raw',0,0n);assert.equal(act(1,11,10,0,L.LS_OBJECT),0n);assert.equal(call('node_count'),1);
reset();const opaque=(1n<<62n)+(1n<<38n)+1n;id('raw',0,opaque);act(1,2,3,2,999);
assert.equal(new DataView(modules[0].HEAPU8.buffer).getBigUint64(Number(modules[0]._probe_node_pointer(0))+L.ls_id,true),opaque);
act(28);assert.match(trace(),new RegExp('0x'+opaque.toString(16)));act(2,999);assert.equal(call('node_count'),0);
reset();add('obj',0);add('obj',1);add('mon',0);act(12);assert.equal(fields()[3],'3');
id('obj',0);act(2,L.LS_OBJECT);assert.equal(call('node_count'),2);assert.equal(call('free_count'),1);assert.equal(fields()[2],'0');
act(3,0);assert.equal(call('node_count'),1);act(18);assert.equal(act(18),1n);
id('obj',15);act(2,L.LS_OBJECT);assert.match(trace(),/not found/);
reset();id('raw',0,0n);act(2,L.LS_NONE);assert.match(trace(),/type=none/);

// Native circle tables, full row matrix and direct line-of-sight boundaries.
reset();add('obj',0,2);act(4);assert.equal(litCount(),21);assert.ok(rowField(0,'flags')&SHOW);
for(const range of [0,1,2,3,L.MAX_RADIUS])for(const center of [[1,0],[79,20],[10,10],[11,10]]){
    reset();if(range===0){id('raw',0,0n);act(1,center[0],center[1],0,L.LS_OBJECT);}
    else{object(0,9,center[0]);object(0,10,center[1]);add('obj',0,range);}
    act(4);
}
reset();object(0,9,11);object(0,10,10);add('obj');call('option',2,0);act(4);assert.equal(litCount(),1);
reset();add('obj',0,3);add('obj',1,1);act(4);assert.equal(rowField(0,'flags')&SHOW,SHOW);assert.equal(rowField(1,'flags')&SHOW,SHOW);
reset();add('obj',0,1);add('obj',1,3);act(4);assert.equal(rowField(1,'flags')&SHOW,0);
for(const located of [0,1]){reset();add('obj');call('option',0,located);act(4);assert.equal(rowField(0,'flags')&SHOW,located?SHOW:0);}
reset();mon(0,2,13);mon(0,3,10);add('mon');act(4);assert.equal(rowField(0,'x'),13);

// Transient objects/camera flashes, seen-monster cleanup and output order.
reset();act(5,-1,11,10);assert.equal(litCount(),1);assert.equal(call('node_count'),1);act(7);assert.equal(call('node_count'),0);
reset();call('hero',5,1);act(5,-1,11,10);assert.equal(call('node_count'),0);
for(const visible of [0,1])for(const sensed of [0,1]){
    reset();add('obj');object(0,4,1);mon(0,2,11);mon(0,3,10);mon(0,7,0);
    mon(1,2,12);mon(1,3,10);mon(1,1,0);mon(0,6,1);
    call('option',3,1);act(5,0,11,10);assert.match(trace(),/place:0:11:10;recalc:0;/);
    assert.match(trace(),/delay;remove:0;/);call('option',3,visible);call('option',4,sensed);act(6);
    assert.equal(trace().includes('invisible:11:10'),!visible&&!sensed);
}
reset();object(0,4,1);act(5,0,11,10);assert.match(trace(),/not a light source/);
reset();add('obj');object(0,8,L.OBJ_FLOOR);act(5,0,11,10);assert.match(trace(),/not free/);

// Monster identities: dead fmon exclusion, all chains and hero priority.
for(const chain of [L.FM_FMON,L.FM_MIGRATE,L.FM_MYDOGS])for(const dead of [0,1]){
    reset();mon(0,7,chain===L.FM_FMON?0:chain===L.FM_MIGRATE?1:2);mon(0,1,dead?0:20);
    assert.equal(act(8,200,chain),chain===L.FM_FMON&&dead?-1n:0n);
    assert.equal(act(9,0,chain),BigInt(chain));
}
reset();assert.equal(act(8,1,L.FM_YOU),-2n);assert.equal(act(9,-2,L.FM_YOU),BigInt(L.FM_YOU));
reset();mon(0,7,0);mon(0,7,1);mon(0,7,2);assert.equal(act(9,0,L.FM_EVERYWHERE),BigInt(L.FM_FMON));

// Save subsets, pointer-to-ID replacement, raw unions/padding and restoration.
for(const mode of [0,L.COUNTING,L.WRITING,L.FREEING,L.WRITING|L.FREEING])for(const range of [L.RANGE_LEVEL,L.RANGE_GLOBAL]){
    reset();object(0,8,L.OBJ_FLOOR);add('obj',0);object(1,8,L.OBJ_INVENT);add('obj',1);
    mon(0,7,0);add('mon',0);mon(1,2,0);mon(1,7,1);add('mon',1);
    call('nhfile',0,mode);act(10,range);
    assert.equal(fields()[0],'0');if(mode&L.FREEING){assert.equal(call('node_count'),2);assert.equal(call('free_count'),2);}
}
reset();object(0,1,0xffffffff);object(0,8,L.OBJ_FLOOR);add('obj');
const beforeIDs=modules.map(m=>bytes(m,Number(m._probe_node_pointer(0))+L.ls_id,L.anythingSize));
act(16,0);modules.forEach((m,i)=>assert.deepEqual(bytes(m,Number(m._probe_node_pointer(0))+L.ls_id,L.anythingSize),beforeIDs[i]));
assert.ok(!(rowField(0,'flags')&FIXUP));assert.equal(new DataView(modules[0].HEAPU8.buffer).getUint32(Number(modules[0]._probe_io_pointer())+L.ls_id,true),0xffffffff);
reset();id('obj',0);act(1,10,10,2,L.LS_OBJECT);modules.forEach(m=>{
    m._probe_ls(0,3,BigInt(FIXUP));const v=new DataView(m.HEAPU8.buffer),p=Number(m._probe_node_pointer(0))+L.ls_id;
    v.setBigUint64(p,0xa5a5a5a500000064n,true);
});check();act(16,0);assert.equal(new DataView(modules[0].HEAPU8.buffer).getBigUint64(Number(modules[0]._probe_io_pointer())+L.ls_id,true),0xa5a5a5a500000064n);
reset();mon(0,7,0);mon(0,1,0);add('mon');act(16,0);assert.match(trace(),/because it's dead/);assert.equal(rowField(0,'flags')&(FIXUP|PROBLEM),0);
reset();add('mon');act(16,0);assert.match(trace(),/not in any chain/);
reset();call('option',7,1);add('obj');act(16,0);assert.match(trace(),/can't find obj/);
reset();id('raw',0,0n);act(1,11,10,0,L.LS_OBJECT);act(10,L.RANGE_LEVEL);assert.equal(call('node_count'),0);assert.equal(call('free_count'),1);
reset();add('obj',0);add('obj',1);act(12,1);assert.equal(fields()[3],String(2*(L.lightSourceSize+1)));assert.equal(fields()[4],'0');
reset();id('obj',0);act(1,10,10,2,999);act(14,L.RANGE_LEVEL,1);act(16,0);assert.match(trace(),/bad type/);
reset();object(0,8,L.OBJ_FLOOR);add('obj');mon(0,7,0);add('mon');call('nhfile',0,L.WRITING|L.FREEING);
act(10,L.RANGE_LEVEL);assert.equal(call('node_count'),0);call('io_position',0);act(11);assert.equal(call('node_count'),2);
assert.ok(rowField(0,'flags')&FIXUP);act(13,0);assert.ok(!(rowField(0,'flags')&FIXUP));act(15);
reset();add('mon',-1);act(4);assert.equal(rowField(0,'x'),10);act(16,0);assert.ok(!trace().includes('impossible:'));
reset();object(0,8,L.OBJ_FLOOR);add('obj');call('option',9,1);assert.equal(act(10,L.RANGE_LEVEL),PANIC);assert.match(trace(),/counted 2 light sources, wrote 1/);
// Ghost-ID mapping and controlled original panic paths.
reset();id('raw',0,90n);act(1,10,10,2,L.LS_OBJECT);ls(0,3,FIXUP);call('option',5,10);act(13,1);assert.equal(nodes(modules[0])[0].id,'o0');
for(const failure of ['mapping','object','monster','type']){
    reset();id('raw',0,failure==='monster'?999n:100n);act(1,10,10,2,failure==='monster'?L.LS_MONSTER:failure==='type'?999:L.LS_OBJECT);ls(0,3,FIXUP);
    if(failure==='mapping')call('option',6,0);if(failure==='object')call('option',7,1);
    assert.equal(act(13,failure==='mapping'?1:0),PANIC);assert.match(trace(),/panic:/);
}
reset();add('obj');act(15);call('option',7,1);assert.equal(act(15),PANIC);
reset();id('raw',0,0n);act(1,11,10,0,L.LS_OBJECT);assert.equal(act(15),PANIC);

// Split/merge copy entire native structs including padding, with real ownership.
reset();add('obj');const fieldsUsed=new Set();
for(const f of ['next','x','y','range','flags','type','id'])for(let j=0;j<L['ls_'+f+'_size'];j++)fieldsUsed.add(L['ls_'+f]+j);
const padding=Array.from({length:L.lightSourceSize},(_,i)=>i).filter(i=>!fieldsUsed.has(i));
modules.forEach(m=>{const p=Number(m._probe_node_pointer(0));padding.forEach((off,i)=>m.HEAPU8[p+off]=0xa0+i);});
object(0,2,9);object(1,2,4);act(22,0,1);assert.equal(call('node_count'),2);assert.equal(rowField(0,'range'),3);assert.equal(rowField(1,'range'),4);
modules.forEach(m=>padding.forEach((off,i)=>assert.equal(m.HEAPU8[Number(m._probe_node_pointer(0))+off],0xa0+i)));
act(17,1,2);object(2,2,16);act(23,0,2);assert.equal(call('node_count'),1);assert.equal(rowField(0,'range'),5);
act(23,2,2);act(24,2,7);assert.equal(rowField(0,'range'),7);act(24,15,2);assert.match(trace(),/can't find fixture object/);
for(const typ of [L.TALLOW_CANDLE,L.WAX_CANDLE,L.CANDELABRUM_OF_INVOCATION,L.OIL_LAMP])for(const quantity of [0n,1n,3n,4n,8n,9n,15n,16n,224n,225n,(1n<<53n)+1n,(1n<<63n)-1n]){
    reset();object(0,0,typ);object(0,2,quantity);object(0,3,Number(quantity%9n));act(25,0);
}
for(const typ of [L.TALLOW_CANDLE,L.MAGIC_LAMP,L.OIL_LAMP,L.GOLD_DRAGON_SCALE_MAIL])for(const lit of [0,1])for(const artifact of [0,1])for(const spe of [0,1]){
    reset();object(0,0,typ);object(0,4,lit);object(0,7,artifact);object(0,3,spe);act(20,0);act(21,0);
    if(lit){add('obj');act(19,10,10);}
}
for(const blessed of [0,1])for(const cursed of [0,1])for(const skin of [0,1])for(const typ of [L.OIL_LAMP,L.GOLD_DRAGON_SCALE_MAIL]){
    reset();object(0,0,typ);object(0,7,1);object(0,4,1);object(0,5,blessed);object(0,6,cursed);object(0,11,skin);
    const radius=act(26,0);act(27,0);assert.equal(radius,BigInt(skin?1:(blessed?3:!cursed?2:1)+(typ===L.GOLD_DRAGON_SCALE_MAIL?1:0)));
}
reset();object(0,7,1);act(26);act(27);assert.equal(text(modules[0],modules[0]._probe_pointer(5,0)),'strangely');
reset();act(28);assert.match(trace(),/<none>/);call('option',8,1);assert.equal(act(28),BigInt(L.ECMD_OK));

// Actual native boundaries grow memory/reenter while native field pointers live.
for(const stage of [1,2,3,4,5,6]){
    reset();add('obj');call('option',30,stage);call('option',31,stage);
    const sizes=modules.map(m=>allocationMetric(m));
    if(stage===1)act(4);
    if(stage===2){object(0,9,11);act(4);}
    if(stage===3)act(5,0,11,10);
    if(stage===4)act(16,0);
    if(stage===5){object(0,8,L.OBJ_FLOOR);act(10,L.RANGE_LEVEL);}
    if(stage===6){id('obj');act(2,L.LS_OBJECT);}
    assert.match(trace(),/nested-any:/);assert.match(trace(),new RegExp('grew:'+stage));
    modules.forEach((m,i)=>assert.ok(allocationMetric(m)>sizes[i]));
}
reset();add('obj');const before=snapshot(modules[1]),other=await hybridFactory({nethackPorted:runtime});other._probe_reset();
assert.equal(other._probe_node_count(),0);new DataView(other.HEAPU8.buffer).setBigUint64(Number(other._probe_union_pointer()),other._probe_pointer(0,1),true);
other._probe_action(1,11,10,3,L.LS_OBJECT,0);assert.equal(other._probe_node_count(),1);
assert.deepEqual(snapshot(modules[1]),before);check();reset();
console.log(`LIGHT: ${comparisons} ${referenceLabel}/hybrid native-list, vision, union, serialization, ownership and callback comparisons checked.`);
