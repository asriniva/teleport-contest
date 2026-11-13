import './pure-js-probes/deny-wasm.mjs';
import assert from 'node:assert/strict';
import fs from 'node:fs';
import {createReference} from './pure-js-fixtures/load.mjs';
import {DataView as FixtureDataView} from './native-test-backend.mjs';
import createStairs from './pure-js-probes/stairs.mjs';
import createRect from './pure-js-probes/rect.mjs';
import {withCEnvironment,C,R,T} from '../js/c-runtime/context.js';
import {init_rect} from '../js/ported/rect.js';
import {dupstr} from '../js/ported/alloc.js';
import {regex_match,regex_error_desc} from '../js/ported/posixregex.js';
import * as drawing from '../js/ported/drawing.js';
import {createStandaloneEnvironment} from '../js/nethack/environment.js';
import {CExit} from '../js/c-runtime/functions.js';
import {REG_ESPACE} from '../js/libraries/regex/posix.js';
import {set_map_u} from '../js/ported/utf8map.js';
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json'));
const text=(m,p)=>{let at=Number(p),end=at;while(m.HEAPU8[end])end++;return Buffer.from(m.HEAPU8.slice(at,end)).toString('latin1');};
let comparisons=0,contracts=0;
const stairs=[await createReference('stairs'),await createStairs(layouts)];
for(const dungeon of [1,2,3,4])for(const up of [0,1])for(const ladder of [0,1])for(const singular of [0,1])for(const amulet of [0,1]){
 const values=stairs.map(m=>{
  m._probe_init();m._probe_hero(dungeon,1,amulet);m._probe_add(1,2,up,ladder,0,2);
  const node=m._probe_head();new FixtureDataView(m.HEAPU8.buffer)['setUint'+layouts.stairs.boolSize*8](Number(node)+layouts.stairs.u_traversed,1,true);
  const result=m._probe_describe(node,singular);assert.equal(result,m._probe_description_buffer());
  const value={text:text(m,result),trace:text(m,m._probe_trace())};m._probe_free();return value;
 });
 assert.deepEqual(values[1],values[0],'branch stairs from dungeon '+dungeon);
 assert.equal(values[0].text,'branch '+(ladder?'ladder':singular?'staircase':'stairs')+' '+(up?'up':'down')+' to the Main Dungeon');comparisons++;
}
const rect=[await createReference('rect'),await createRect(layouts)],L=layouts.rect,fields=['lx','ly','hx','hy'];
function box(m,values){const p=m._malloc(BigInt(L.size)),view=new FixtureDataView(m.HEAPU8.buffer);fields.forEach((name,i)=>view['setInt'+L.coordSize*8](Number(p)+L[name],values[i],true));return p;}
for(const cut of [[30,10,25,12],[25,12,30,8]]){
 const values=rect.map(m=>{
  m._probe_seed(1);m._probe_init();
  const whole=box(m,[0,0,L.COLNO-1,L.ROWNO-1]);m._probe_remove(BigInt(whole));m._free(whole);
  for(const value of [[0,0,50,15],[20,5,79,20]]){const p=box(m,value);m._probe_add(BigInt(p));m._free(p);}
  const p=box(m,cut);m._probe_split(BigInt(m._probe_data()),BigInt(p));m._free(p);
  const count=m._probe_count(),base=Number(m._probe_data()),view=new FixtureDataView(m.HEAPU8.buffer);
  const result={count,capacity:m._probe_capacity(),rects:Array.from({length:count},(_,i)=>fields.map(name=>view['getInt'+L.coordSize*8](base+i*L.size+L[name],true))),diagnostic:text(m,m._probe_diagnostic_message()),rng:m._probe_rng_count()};
  m._probe_free();return result;
 });
 assert.deepEqual(values[1],values[0],'inverted rectangle '+cut);comparisons++;
}
// These simulate rejected dependency results; they are explicit JS boundary
// contracts, not claims that original C can allocate multi-gigabyte strings.
const failure=new Error('rejected rectangle allocation'),state={rect:0,n_rects:0,rect_cnt:0},events=[];
assert.throws(()=>withCEnvironment({rectState:state,COLNO:80,ROWNO:21,NhRectSize:8,alloc:n=>{events.push(['alloc',n]);return 0;},rectArray:p=>{assert.equal(p,0);return 0;},rectPanic:()=>{events.push(['panic']);throw failure;}},init_rect),error=>error===failure);
assert.deepEqual(events,[['alloc',448],['panic']]);assert.equal(state.n_rects,56);assert.equal(state.rect_cnt,0);contracts++;
for(const length of [0xffffffff,0x100000000,0xffffffffffffffffn]){
 const events=[],failure=new Error('length overflow');
 assert.throws(()=>withCEnvironment({strlen:()=>{events.push('strlen');return length;},panicDupstr:()=>{events.push('panic');throw failure;},malloc:()=>{throw Error('Unexpected allocation');},strcpy:()=>{throw Error('Unexpected copy');}},()=>dupstr(123)),error=>error===failure);
 assert.deepEqual(events,['strlen','panic']);contracts++;
}
const regex={re:100,err:73};
assert.equal(withCEnvironment({REG_NOMATCH:layouts.posixregex.REG_NOMATCH,regexec:(...args)=>{assert.deepEqual(args,[100,200,0,0,0]);return REG_ESPACE;}},()=>regex_match(200,regex)),0);
assert.equal(regex.err,REG_ESPACE);contracts++;
const heap=new Uint8Array(64),signed=new Int8Array(heap.buffer),diagnostics=[];
const result=withCEnvironment({HEAPU8:heap,HEAP8:signed,BUFSZ:32,regerror:(...args)=>{diagnostics.push(args);return 0;},Strcpy:(p,s)=>{heap.set(Buffer.from(s+'\0'),p);return p;}},()=>regex_error_desc(regex,8));
assert.equal(result,8);assert.deepEqual(diagnostics,[[REG_ESPACE,100,8,32]]);
assert.equal(Buffer.from(heap.slice(8,heap.indexOf(0,8))).toString(),'unspecified regexp error');contracts++;

// Corrupt only test-instance data; restore every table/template afterwards.
const original=drawing.defsyms.map(row=>({...row})),fountains=drawing.defsyms.filter(row=>row.explanation==='fountain');
assert.equal(fountains.length,1);assert.ok(drawing.defsyms.every(row=>row.sym!==255));
try{fountains[0].explanation='test missing end marker';assert.equal(drawing.def_char_is_furniture(255),-1);contracts++;}
finally{fountains[0].explanation='fountain';assert.deepEqual(drawing.defsyms,original);}
const env=createStandaloneEnvironment(),messages=[];
const decl=env.enableDecl(layouts.decl,{raw_printf:(...args)=>messages.push(args)});
const marker=env.ctypes.locate('struct instance_globals_a',decl.g_init_a.address,'havestate').at;
const valid=env.memory.HEAPU8[marker];assert.equal(valid,1);
try{
 env.memory.HEAPU8[marker]=0;
 assert.throws(()=>env.call('decl','decl_globals_init'),error=>error instanceof CExit&&error.status===1);
 assert.deepEqual(messages,[['decl_globals_init: %s.havestate not True.','g_init_a']]);contracts++;
}finally{env.memory.HEAPU8[marker]=valid;env.call('decl','decl_globals_init');}
// Native set_map_u declares this pointer nonnull; test JS's defensive null
// rejection separately without invoking undefined native behavior.
assert.equal(withCEnvironment({},()=>set_map_u(0,0x41,0)),0);contracts++;
assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);
assert.equal(comparisons,66);assert.equal(contracts,9);
console.log('PASS: '+comparisons+' original-C/pure-JS STAIRS/RECT gap cases and '+contracts+' explicit JS allocation/regex/template/table fault contracts; contexts and instance data restored.');
