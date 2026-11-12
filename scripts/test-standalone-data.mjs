import assert from 'node:assert/strict';
import fs from 'node:fs';
import {pathToFileURL} from 'node:url';
import {createStandaloneEnvironment} from '../js/nethack/environment.js';
const root=process.env.STANDALONE_REFERENCE_ROOT;if(!root)throw new Error('Missing STANDALONE_REFERENCE_ROOT');
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json'));
const runtime=createStandaloneEnvironment({maximumBytes:64*1024*1024});
const {default:declFactory}=await import(pathToFileURL(root+'/.cache/tu-probes/decl-reference.mjs'));
const native=await declFactory(),env=runtime.enableDecl(layouts.decl);
const {globals,schema}=JSON.parse(fs.readFileSync('nethack-c/wasm/tu-fragments/decl-schema.json'));
function width(d){return d.p!==undefined?8:d.t?Number(d.t.slice(1))/8:d.s?schema[d.s].size:d.a.reduce((a,b)=>a*b,1)*width(d.e);}
function slots(d,at=0,out=[]) {
    if(d.p!==undefined)out.push([at,d.p]);
    else if(d.s)for(const f of schema[d.s].fields){if(f.bits===null)slots(f.d,at+f.offset,out);}
    else if(d.a){const child=d.a.length===1?d.e:{a:d.a.slice(1),e:d.e};for(let i=0;i<d.a[0];i++)slots(child,at+i*width(child),out);}
    return out;
}
function snapshot(heap,base) {
    const regions=globals.map((g,i)=>({start:base(i,g),end:base(i,g)+g.bytes,name:g.name})),aliases=new Map();
    const string=p=>{let end=p;while(heap[end])end++;return Buffer.from(heap.slice(p,end)).toString('hex');};
    return globals.map((g,i)=>{
        const bytes=Buffer.from(heap.slice(regions[i].start,regions[i].end)),pointers=[];
        for(const [offset,kind] of slots(g.d)) {
            const p=Number(bytes.readBigUInt64LE(offset));bytes.writeBigUInt64LE(0n,offset);let value=null;
            if(p){const target=regions.find(r=>p>=r.start&&p<r.end);if(target)value=[target.name,p-target.start];
                else if(kind==='char'){if(!aliases.has(p))aliases.set(p,aliases.size);value=[string(p),aliases.get(p)];}
                else throw new Error('Unresolved non-character initializer pointer '+g.name);}
            pointers.push([offset,kind,value]);
        }
        return {name:g.name,bytes,pointers};
    });
}
const original=snapshot(native.HEAPU8,i=>Number(native._teleport_decl_storage(i)));
assert.deepEqual(snapshot(runtime.memory.HEAPU8,(_,g)=>runtime.requireGlobal(g.name)),original);
env.nhcb_counts[0]=19;assert.equal(runtime.services.nhcb_counts[0],19);
const old=env.flags;runtime.memory.malloc(2*1024*1024);assert.equal(old.address,env.flags.address);
const other=createStandaloneEnvironment();other.enableDecl(layouts.decl);assert.equal(other.services.nhcb_counts[0],0);
const sysopt=runtime.enableSys(layouts.sys),{default:sysFactory}=await import(pathToFileURL(root+'/.cache/tu-probes/sys-reference.mjs'));
const system=await sysFactory();runtime.call('sys','sys_early_init');system._probe_init();
for(const [key,field]of Object.entries(layouts.sys.fields)) {
    const at=Number(system._probe_sys_pointer())+field.offset,view=new DataView(system.HEAPU8.buffer);
    if(field.kind==='pointer'){const p=Number(view.getBigUint64(at,true));let end=p;while(system.HEAPU8[end])end++;assert.equal(sysopt[key]?runtime.memory.readString(sysopt[key]):null,p?Buffer.from(system.HEAPU8.slice(p,end)).toString('latin1'):null,key);}
    else if(field.kind==='array')assert.deepEqual(Array.from({length:field.size/4},(_,i)=>sysopt[key][i]),Array.from({length:field.size/4},(_,i)=>view.getInt32(at+i*4,true)),key);
    else assert.equal(sysopt[key],view[field.kind==='long'?'getBigInt64':'getInt'+field.size*8](at,true),key);
}
runtime.call('sys','sysopt_release');system._probe_release();
const {default:drawingFactory}=await import(pathToFileURL(root+'/.cache/tu-probes/drawing-reference.mjs'));
const drawing=await drawingFactory(),tables=runtime.enableDrawing(layouts.drawing);
const counts=[layouts.drawing.MAXOCLASSES,layouts.drawing.MAXMCLASSES,layouts.drawing.WARNCOUNT,layouts.drawing.MAXPCHARS+1,layouts.drawing.MAXOCLASSES];
const bases=[tables.objectSymbols,tables.monsterSymbols,tables.warningSymbols,tables.symbols,tables.rogueSymbols];
for(let table=0;table<5;table++)for(let i=0;i<counts[table];i++) {
    const classTable=table<2,at=bases[table]+i*(table===4?1:classTable?layouts.drawing.classSize:layouts.drawing.symdefSize);
    assert.equal(runtime.memory.HEAP8[at],drawing._probe_table_symbol(table,i));
    if(table===4)continue;
    const field=at+(classTable?layouts.drawing.classExplain:layouts.drawing.symdefExplanation),ptr=Number(runtime.memory.view.getBigUint64(field,true));
    let p=Number(drawing._probe_table_explanation(table,i)),end=p;while(drawing.HEAPU8[end])end++;
    assert.equal(ptr?runtime.memory.readString(ptr):null,p?Buffer.from(drawing.HEAPU8.slice(p,end)).toString('latin1'):null);
}
const names={object:'def_char_to_objclass',monclass:'def_char_to_monclass',furniture:'def_char_is_furniture'};
for(let byte=-256;byte<512;byte++)for(const [probe,name]of Object.entries(names))assert.equal(runtime.call('drawing',name,byte),drawing['_probe_'+probe](byte));
for(const name of ['objects','monst']) {
    const {default:factory}=await import(pathToFileURL(root+`/.cache/tu-probes/${name}-reference.mjs`));
    const ref=await factory(),L=layouts[name],pointers=name==='objects'?runtime.enableObjects(L):runtime.enableMonst(L);
    const destination=pointers[name==='objects'?1:0],size=name==='objects'?L.sizeof_objects:L.sizeof_mons;
    assert.ok(runtime.memory.readBytes(destination,size).every(v=>v===0),'Catalogue destination stays zero before public initializer');
    runtime.call(name,name==='objects'?'objects_globals_init':'monst_globals_init');ref._probe_init();
    const nativeBase=Number(name==='objects'?ref._probe_objects():ref._probe_monsters());
    const actual=Buffer.from(runtime.memory.readBytes(destination,size)),expected=Buffer.from(ref.HEAPU8.slice(nativeBase,nativeBase+size));
    for(let row=0;row<L.rowCount;row++) {
        const base=row*(name==='objects'?L.objectSize:L.monsterSize);
        const slots=name==='objects'?[L.oc_uname]:[L.pmnames,L.pmnames+8,L.pmnames+16];
        for(const slot of slots) {
            const p=Number(actual.readBigUInt64LE(base+slot)),q=Number(expected.readBigUInt64LE(base+slot));
            let end=q;while(ref.HEAPU8[end])end++;
            assert.equal(p?runtime.memory.readString(p):null,q?Buffer.from(ref.HEAPU8.slice(q,end)).toString('latin1'):null);
            actual.writeBigUInt64LE(0n,base+slot);expected.writeBigUInt64LE(0n,base+slot);
        }
    }
    assert.deepEqual(actual,expected,`${name} complete native bytes except relocated strings`);
    const pristine=runtime.memory.readBytes(destination,size);
    runtime.memory.HEAPU8.fill(255,destination,destination+size);
    runtime.call(name,name==='objects'?'objects_globals_init':'monst_globals_init');
    assert.deepEqual(runtime.memory.readBytes(destination,size),pristine);
}
console.log(`PASS: ${globals.length} original-C global images/pointer aliases, shared/isolation/growth state, full object/monster catalogue bytes, drawing tables and 2304 drawing lookups.`);
