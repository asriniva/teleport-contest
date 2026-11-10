import assert from './native-test-assert.mjs';
import {DataView,assertStackRestored,memoryCheckpoint,assertMemoryGrowth,referenceBackend,referenceLabel} from './native-test-backend.mjs';
import {readFileSync} from 'node:fs';
import {callSymbols} from '../js/ported/symbols-runtime.js';
import * as symbols from '../js/ported/symbols.js';
import {C,R,T} from '../js/ported/c-runtime.js';
const own=process.env.TELEPORT_SYMBOLS_AUTHOR==='1';
const referenceFactory=(await import(own?'../.cache/symbols-author/reference.mjs':'../.cache/tu-probes/symbols-reference.mjs')).default,hybridFactory=(await import(own?'../.cache/symbols-author/hybrid.mjs':'../.cache/tu-probes/symbols-hybrid.mjs')).default;
const L=own?JSON.parse(readFileSync(new URL('../.cache/symbols-author/layout.json',import.meta.url))):JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url))).symbols;
const ported={callSymbols:(services,name,...args)=>callSymbols(services,L,name,...args)},modules=[await referenceBackend('symbols',referenceFactory)(),await hybridFactory({nethackPorted:ported})],stacks=modules.map(m=>m._probe_stack());let comparisons=0;
function text(m,p){if(!p)return null;p=Number(p);let end=p;while(m.HEAPU8[end])end++;return Buffer.from(m.HEAPU8.slice(p,end)).toString('latin1');}
function snapshot(m){return {state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace()),frees:m._probe_free_count()};}
function check(){assert.deepEqual(snapshot(modules[1]),snapshot(modules[0]));assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);modules.forEach((m,i)=>assertStackRestored(m,stacks[i]));comparisons++;}
function call(name,...args){const values=modules.map(m=>m['_probe_'+name](...args));assert.deepEqual(values[1],values[0],name+':'+args);comparisons++;check();return values[0];}
function stringCall(name,value,...args){const results=[];for(const m of modules){const bytes=Buffer.from(value+'\0','latin1'),p=Number(m._malloc(bytes.length));m.HEAPU8.set(bytes,p);results.push(m['_probe_'+name](BigInt(p),...args));m._free(BigInt(p));}assert.deepEqual(results[1],results[0]);comparisons++;check();return results[0];}
const reset=()=>call('reset'),opt=(k,v)=>call('option',k,v),input=s=>stringCall('input',s),file=s=>stringCall('file',s),global=(k,v)=>call('global',k,v),symbol=(a,i,v)=>call('symbol',a,i,v),act=(op,a=0,b=0)=>call('action',op,a,b),trace=()=>text(modules[0],modules[0]._probe_trace());
function set(set,field,s=null,value=0){for(const m of modules){let p=0;if(s!==null){const bytes=Buffer.from(s+'\0','latin1');p=Number(m._malloc(bytes.length));m.HEAPU8.set(bytes,p);}m._probe_symset(set,field,BigInt(p),value);if(p)m._free(BigInt(p));}check();}
function parse(s,set=0,op=16){input(s);return act(op,set);}
function fields(prefix){return text(modules[0],modules[0]._probe_snapshot()).split(';').find(x=>x.startsWith(prefix+':')).split(':').slice(1);}
function array(a){return fields('a'+a)[0];}
const resolve=expr=>expr.split('+').map(s=>s.trim()).reduce((a,k)=>a+(/^\d+$/.test(k)?Number(k):L[k]),0);
reset();for(const m of modules)for(let i=0;i<m._probe_layout_count();i++){const k=text(m,m._probe_layout_name(i));assert.equal(Number(BigInt.asIntN(64,m._probe_layout_value(i))),L[k],k);}
assert.equal(L.loadsymsCount,197);assert.equal(L.pointerSize,8);assert.equal(L.nhsymSize,1);
// Every externally visible row, including terminators, matches original C.
for(const [table,rows]of [[0,symbols.known_handling],[1,symbols.known_restrictions]])for(let i=0;i<rows.length;i++){assert.equal(text(modules[0],modules[0]._probe_table_name(table,i)),rows[i]||null);assert.equal(text(modules[1],modules[1]._probe_table_name(table,i)),rows[i]||null);comparisons++;}
for(const[i,row]of symbols.loadsyms.entries()){for(const m of modules){assert.equal(text(m,m._probe_table_name(2,i)),row.name);assert.equal(m._probe_table_field(i,0),resolve(row.range));assert.equal(m._probe_table_field(i,1),resolve(row.idx));}comparisons++;}
// The duplicate S_invisible spelling shares its native name pointer and the
// matcher returns the first (monster-class) row, exactly as original C does.
const invisibleRows=symbols.loadsyms.map((r,i)=>r.name==='S_invisible'?i:-1).filter(i=>i>=0);assert.equal(invisibleRows.length,2);for(const m of modules)assert.equal(m._probe_table_name(2,invisibleRows[0]),m._probe_table_name(2,invisibleRows[1]));
// All names, aliases and boundary matches return original table-interior IDs.
for(const row of symbols.loadsyms){if(!row.name)continue;for(const suffix of ['',':x','=x',' = x']){input(row.name+suffix);const index=act(25);assert.equal(index,symbols.loadsyms.findIndex(candidate=>candidate.name?.toLowerCase()===row.name.toLowerCase()));}}
for(const s of ['S_armour','S_explode1','S_explode2','S_explode3','S_explode4','S_explode5','S_explode6','S_explode7','S_explode8','S_explode9','s_ArMoUr:x','S_explode10','S_st','G_foo','g_foo','unknown','finishmore']){input(s);act(25);}
reset();act(0);assert.equal(array(0),array(1));assert.notEqual(array(1),array(2));assert.equal(fields('set1')[3],'1');
for(const which of [L.PRIMARYSET,L.ROGUESET,2,-1])for(let i=0;i<L.MAXOTHER;i++)act(4,i,which);
for(const arrayIndex of [1,2,3,4])for(const value of [0,1,127,128,255,256,-1,-128,2147483647]){reset();const fallback=act(4,L.SYM_BOULDER,L.PRIMARYSET);symbol(arrayIndex,L.SYM_OFF_X+L.SYM_BOULDER,value);const which=arrayIndex===2||arrayIndex===4?L.ROGUESET:L.PRIMARYSET;assert.equal(act(4,L.SYM_BOULDER,which),(value&255)||fallback);act(7,which);}
for(let i=0;i<L.SYM_MAX;i++){symbol(1,i,i);symbol(2,i,255-i);symbol(3,i,i%3===0?99:0);symbol(4,i,i%3===1?77:0);}act(7,0);act(7,1);act(7,123);
for(const op of [2,3,5,6,1])act(op);
for(const op of [9,10,11,12])for(const value of [-2147483648,-1,0,255,256,2147483647]){reset();const row=symbols.loadsyms.findIndex(r=>r.name==='S_vwall'),idx=resolve(symbols.loadsyms[row].idx),target={9:3,10:4,11:1,12:2}[op];act(op,row,value);assert.equal(Number.parseInt(array(target).slice(idx*2,idx*2+2),16),value&255);}
reset();for(const setIndex of [0,1]){set(setIndex,0,'Name');set(setIndex,1,'Description');}act(19);assert.equal(modules[0]._probe_free_count(),4);for(const setIndex of [0,1])assert.deepEqual(fields('set'+setIndex).slice(0,2),['<NULL>','<NULL>']);
for(const which of [0,1])for(const handling of [L.H_UNK,L.H_DEC,L.H_UTF8])for(const callback of [0,1]){reset();act(0);set(which,2,null,handling);global(0,which);global(7,callback);global(8,callback);act(8,1);assert.equal(trace().includes('dec-callback'),handling===L.H_DEC&&!!callback);assert.equal(trace().includes('utf-callback'),handling===L.H_UTF8&&!!callback);}
for(const caps of [0n,BigInt(L.WC2_U_UTF8STR),1n<<63n,(1n<<64n)-1n])for(const h of [L.H_UNK,L.H_UTF8,999]){const result=call('compatible',h,caps);assert.equal(result,h!==L.H_UTF8||(caps&BigInt(L.WC2_U_UTF8STR))===BigInt(L.WC2_U_UTF8STR)?1n:0n);}
// Clearing preserves explicitly, optionally frees name and coordinates UTF8 cleanup.
for(const which of [0,1])for(const nameToo of [0,1,256,-1])for(const otherUtf of [0,1]){reset();set(which,0,'Alpha');set(which,1,'desc');set(which,2,null,L.H_UTF8);set(which,6,null,1);set(1-which,2,null,otherUtf?L.H_UTF8:L.H_DEC);act(13,which,nameToo);assert.equal(fields('set'+which)[0],(nameToo<<24>>24)?'<NULL>':'Alpha');assert.equal(fields('set'+which)[6],'1');assert.equal(trace().includes('free-unicode;'),!otherUtf);}
// Build a native linked list by driving only the original parser.
reset();for(const line of ['start:Alpha','description:one','description:ignored','handling:dec','restrictions:primary','color:off','start:Beta','handling:utf8','restrictions:rogue','finish'])assert.equal(parse(line),1);assert.ok(text(modules[0],modules[0]._probe_snapshot()).includes('list:0:Alpha:one:2:0:1:0:'));assert.ok(text(modules[0],modules[0]._probe_snapshot()).includes('list:1:Beta:<NULL>:5:0:0:1:'));
for(const which of [0,1]){reset();set(which,0,'Alpha');for(const line of ['start:Other','S_vwall:x','start:alpha','handling:UTF8','S_vwall:U+1234','G_demo:U+1234','color:on','colour:false','restrictions:primary','restrictions:rogue','description:ignored','finish'])parse(line,which);assert.equal(fields('set'+which)[2],String(L.H_UTF8));assert.ok(trace().includes('glyphrep:'));assert.equal(fields('set'+which)[3],'1');}
for(const line of ['junk','finish','finishmore','S_bad:x','G_bad:x','start=Alpha','start:Alpha','  handling = dec # comment','color:yes','color:NO','color:maybe','restrictions:unknown','S_vwall:x # comment','S_vwall:x#comment','x'.repeat(L.BUFSZ+30)]){reset();set(0,0,'Alpha');parse('start:Alpha');parse(line);}
reset();global(4,1);input('unknown');assert.equal(act(15),1);input('finish');assert.equal(act(15),0);
for(const which of [0,1])for(const handling of [L.H_UNK,L.H_UTF8])for(const value of [-2147483648,-1,0,255,256,2147483647]){reset();set(which,0,'Alpha');parse('start:Alpha',which);set(which,2,null,handling);opt(2,value);parse('S_vwall:x',which);const idx=resolve(symbols.loadsyms.find(r=>r.name==='S_vwall').idx);if(handling!==L.H_UTF8)assert.equal(Number.parseInt(array(which?2:1).slice(idx*2,idx*2+2),16),value&255);}
// Quoting, recursive right-to-left overrides, glyph paths and real saved ownership.
for(const line of ["S_vwall:'|'","S_vwall:','","S_vwall:':'",'S_vwall:\\,','S_vwall=x','S_vwall:U+1234','S_vwall:u+abcd','G_demo:U+1','start:x','unknown:x','S_vwall:x,S_hwall:y','S_vwall:x,S_vwall:y','S_vwall:x,unknown:y','S_vwall','S_vwall:','S_vwall:x,']){reset();act(0);parse(line,0,24);act(23);const out=modules.map(m=>text(m,m._probe_buffer()));assert.equal(out[1],out[0]);}
reset();parse('S_vwall:x,S_hwall:y',0,24);act(23);assert.equal(text(modules[0],modules[0]._probe_buffer()),'SYMBOLS=S_vwall:x\nSYMBOLS=S_hwall:y\n');input('S_vwall');act(22,0);assert.equal(act(21,0),1);assert.equal(act(21,1),0);const heads=modules.map(m=>new DataView(m.HEAPU8.buffer).getBigUint64(Number(m._probe_pointer(3,0)),true));act(20);modules.forEach((m,i)=>assert.equal(new DataView(m.HEAPU8.buffer).getBigUint64(Number(m._probe_pointer(3,0)),true),heads[i]));assert.ok(text(modules[0],modules[0]._probe_snapshot()).includes('saved:<freed>'));
// Real native file reader calls the original parser back through the C ABI.
const script='start:Alpha\ndescription:first\nhandling:DEC\nS_vwall:x\nfinish\nstart:Beta\ndescription:second\nhandling:UTF8\nS_hwall:U+1234\nfinish\n';
for(const name of ['Alpha','Beta'])for(const fail of [0,1]){reset();file(script);opt(0,fail?0:1);input(name);assert.equal(act(18,0),fail?0:1);if(!fail){assert.equal(fields('set0')[0],name);assert.ok(trace().includes('apply:'));}else assert.equal(fields('set0')[0],'<NULL>');}
for(const rogue of [0,1])for(const count of [-1,0,1,2])for(const chosen of [1,2,3,99]){reset();file(script);opt(5,count);opt(6,chosen);opt(7,3);act(26,rogue);assert.ok(trace().includes('menu:'));if(count>0)assert.ok(trace().includes('free:'));assert.ok(trace().includes('bytes01000000a5a5a5a5'));}
for(const which of [0,1]){reset();file(script);set(which,0,'Alpha');opt(5,2);opt(6,2);opt(7,3);act(26,which);assert.equal(fields('set'+which)[0],'Beta');}
for(const rogue of [0,1]){reset();file(script);global(5,3);global(6,4);opt(5,1);opt(6,1);act(26,rogue);assert.ok(trace().includes('on-level:3:4:3:4;'));assert.equal(fields('state')[0],String(rogue?L.ROGUESET:L.PRIMARYSET));}
for(const setup of ['missing','empty','restricted','second-failure']){reset();file(setup==='empty'?'':setup==='restricted'?'start:Alpha\nrestrictions:rogue\nfinish\n':script);if(setup==='missing')opt(0,0);if(setup==='second-failure'){opt(5,1);opt(6,2);opt(8,2);}act(26,0);}
// Scoped native callbacks force actual memory growth and real C→JS reentry.
for(const stage of [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]){reset();file(script);opt(20,stage);opt(21,stage);const before=modules.map(memoryCheckpoint);
 if(stage===1)act(7,0);else if(stage===2){set(0,2,null,L.H_UTF8);act(13,0,1);}else if(stage===3||stage===4)act(13,0,0);else if(stage===5)parse('G_demo:x',0,24);else if(stage===6)parse('S_vwall:x',0,24);else if(stage===7)parse('S_vwall:U+1234',0,24);else if(stage===8){input('Alpha');act(18);}else if(stage===9){set(0,0,'Alpha');act(13,0,1);}else if(stage===10||stage===11){set(0,2,null,stage===10?L.H_DEC:L.H_UTF8);act(8,1);}else if(stage===12||stage===13||stage===14){opt(5,1);opt(6,2);act(26,0);}else{input('Alpha');act(18);}
 assert.ok(trace().includes(`grow:${stage};`),`stage ${stage}`);assert.ok(trace().includes('nested:'));modules.forEach((m,i)=>assertMemoryGrowth(m,before[i]));}
reset();act(0);const old=modules.map(snapshot),other=await hybridFactory({nethackPorted:ported});other._probe_reset();other._probe_symbol(1,0,77);other._probe_action(7,0,0);assert.ok(text(other,other._probe_snapshot()).includes('a0:4d'));modules.forEach((m,i)=>assert.deepEqual(snapshot(m),old[i]));check();
console.log(`SYMBOLS: ${comparisons} ${referenceLabel}/hybrid complete tables, parser, menus, aliases, ownership and callbacks checked.`);
