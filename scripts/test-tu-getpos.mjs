// Configured Emscripten-C first pass. This cannot silently count as native C.
import assert from 'node:assert/strict';
import {resolve} from 'node:path';
import {pathToFileURL} from 'node:url';
import * as getpos from '../js/ported/getpos.js';
import {createGetposEnvironment} from '../js/ported/getpos-runtime.js';
import {withCEnvironment,C} from '../js/ported/c-runtime.js';
if(process.env.TELEPORT_NATIVE_TESTS==='1')throw new Error('GETPOS native oracle pending; this staged suite compares configured Emscripten C only.');
const dir=resolve(process.env.TELEPORT_GETPOS_PROBE_DIR??'.cache/tu-probes');
const refFactory=(await import(pathToFileURL(resolve(dir,'getpos-reference.mjs')))).default,hybridFactory=(await import(pathToFileURL(resolve(dir,'getpos-hybrid.mjs')))).default;
const text=(m,p)=>{p=Number(p);let e=p;while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.subarray(p,e)).toString('latin1');};
const layout=m=>Object.fromEntries(Array.from({length:m._probe_layout_count()},(_,i)=>[text(m,m._probe_layout_name(i)),Number(m._probe_layout_value(i))]));
const reference=await refFactory(),L=layout(reference),envs=new WeakMap();
const getEnv=s=>{let e=envs.get(s.moduleKey);if(!e){e=createGetposEnvironment(s,L,getpos);envs.set(s.moduleKey,e);}return e;};
const runtime={getpos(s,name,...a){const e=getEnv(s);if(['getpos','getpos_menu'].includes(name))a[0]=e.coord(a[0]);if(name==='getpos_getvalids_selection')a[0]=e.selection(a[0]);if(name==='gather_locs'){a[0]=e.coordArrayPointer(a[0]);a[1]=e.intPointer(a[1]);}if(name==='truncate_to_map'){a[0]=e.coordPointer(a[0]);a[1]=e.coordPointer(a[1]);}const r=withCEnvironment(e,getpos[name],...a);return r?.address??r??0;}};
const hybrid=await hybridFactory({nethackPorted:runtime}),modules=[reference,hybrid],stacks=modules.map(m=>m._probe_stack());assert.deepEqual(layout(hybrid),L);let comparisons=1,scenario='initial';
const snap=m=>({state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace())});
function check(){const actual=snap(hybrid),expected=snap(reference);for(const field of["state","trace"]){if(actual[field]!==expected[field]){let at=0;while(actual[field][at]===expected[field][at])at++;throw new Error(`${scenario} ${field} differs at${at}: JS=${actual[field].slice(Math.max(0,at-80),at+150)} C=${expected[field].slice(Math.max(0,at-80),at+150)}`);}}const e=envs.get(hybrid);if(e)for(const[i,value]of[e.getpos_hilite_state,e.defaultHiliteState,Number(Boolean(e.getpos_hilitefunc)),Number(Boolean(e.getpos_getvalid))].entries())assert.equal(value,reference._probe_private_state(i),scenario+" private state");assert.equal(C,undefined);modules.forEach((m,i)=>assert.equal(m._probe_stack(),stacks[i]));comparisons++;}
function call(name,...a){const r=modules.map(m=>{try{return m['_probe_'+name](...a);}catch(error){throw new Error(scenario+':'+name+':'+a,{cause:error});}});assert.deepEqual(r[1],r[0],scenario+':'+name+':'+a);comparisons++;check();return r[0];}
const reset=()=>call('reset'),opt=(k,v)=>call('option',k,v),cell=(x,y,k,v)=>call('cell',x,y,k,v),act=(op,a=0,b=0,c=0)=>call('action',op,a,b,c),key=(c,x=0,y=0,b=0)=>call('input',typeof c==='string'?c.charCodeAt(0):c,x,y,b),cmap=s=>reference._probe_cmap(s);
const trace=()=>text(reference,reference._probe_trace());
function goal(s){modules.forEach(m=>m.HEAPU8.set(Buffer.from(s+'\0'),Number(m._probe_goal())));check();}
for(const bg of[0,1])for(const cb of[0,1,2]){scenario='retained callback states';reset();opt(100,bg);opt(121,0xffffffff);act(0,1,cb);for(let i=0;i<5;i++)act(1);act(2,3,4);act(20);act(0,0,0);}
for(const valid of[0,1,2]){scenario='selection callback';reset();act(3,valid);}
for(const force of[0,1])for(const terrain of[0,L.TER_MON,L.TER_MAP,L.TER_DETECT])for(const target of[0,1,2]){scenario='help target modes';reset();opt(108,terrain);opt(109,1);opt(100,1);act(0,1,1);act(5,force,target);}
for(let gloc=0;gloc<L.NUM_GLOCS;gloc++)for(const menu of[0,1])for(const filter of[0,1,2]){scenario='help target descriptions';reset();opt(104,menu);opt(101,filter);act(4,gloc);}
for(const [a,b,c]of[[10,10,12],[9,10,11],[0,0,0],[32767,-32768,32767]]){scenario='coordinate comparator';reset();act(6,a,b,c);}
const symbols=[L.S_room,L.S_corr,L.S_hwall,L.S_tree,L.S_ndoor,L.S_upstair,L.S_pool,L.S_lava,L.S_arrow_trap,L.S_altar,L.S_air];
for(const glyph of[...symbols.map(cmap),L.GLYPH_UNEXPLORED,L.GLYPH_NOTHING,L.GLYPH_MON_MALE_OFF,L.GLYPH_OBJ_OFF]){scenario='glyph classification';reset();act(7,glyph);}
for(const type of[0,1,2]){scenario='area selection and doorway';reset();opt(101,L.GFILTER_AREA);if(type){cell(10,10,4,L.DOOR);opt(115,type===1?1:0);opt(116,0);}for(const x of[8,9,10,11,12])for(const y of[9,10,11])cell(x,y,1,cmap(x<10?L.S_hwall:L.S_room));act(10);act(8,10,10);act(13,9,10,L.GLOC_INTERESTING);act(11);}
for(const seen of[0,1])for(const glyph of[cmap(L.S_room),cmap(L.S_hwall),cmap(L.S_corr)]){scenario='flood match';reset();cell(10,10,1,glyph);cell(10,10,3,seen);act(9,10,10);act(8,10,10);act(11);}
for(const trap of[0,1]){scenario='genuine vibrating square';reset();opt(120,trap);act(12,5,5);act(12,6,5);act(13,5,5,L.GLOC_INTERESTING);}
for(const glyph of[...symbols.map(cmap),L.GLYPH_MON_MALE_OFF+1,L.GLYPH_MON_MALE_OFF+L.PM_LONG_WORM_TAIL,L.GLYPH_MON_FEM_OFF+L.PM_LONG_WORM_TAIL,L.GLYPH_OBJ_OFF+L.ROCK,L.GLYPH_OBJ_OFF+L.BOULDER,L.GLYPH_OBJ_OFF+1,L.GLYPH_UNEXPLORED,L.GLYPH_NOTHING])for(let gloc=0;gloc<L.NUM_GLOCS;gloc++){scenario='interesting location predicates';reset();cell(15,10,0,glyph);cell(16,10,2,L.GLYPH_UNEXPLORED);cell(16,10,3,0);act(13,15,10,gloc);}
for(const filter of[0,1,2])for(let gloc=0;gloc<L.NUM_GLOCS;gloc++){scenario='gather sorted locations';reset();opt(101,filter);act(0,1,2);for(const [x,y,g]of[[12,10,L.GLYPH_MON_MALE_OFF],[8,9,L.GLYPH_OBJ_OFF+1],[20,10,cmap(L.S_ndoor)],[12,12,cmap(L.S_upstair)]])cell(x,y,0,g);cell(9,8,5,0);act(14,gloc);act(14,gloc);}
for(const full of[0,1])for(const dx of[0,-1,1,-9,99,32767,-32768])for(const dy of[0,-1,1,-8,88,32767,-32768]){scenario='distance descriptions';reset();act(15,dx,dy,full);}
for(const mode of[L.GPCOORDS_NONE,L.GPCOORDS_MAP,L.GPCOORDS_SCREEN,L.GPCOORDS_COMPASS,L.GPCOORDS_COMFULL])for(const x of[0,1,79,32767,-32768]){scenario='coordinate modes and static buffer reuse';reset();act(16,x,20,mode);act(16,1,0,mode);}
for(const invalid of[0,1])for(const travel of[0,1])for(const mode of[L.GPCOORDS_NONE,L.GPCOORDS_MAP]){scenario='auto description';reset();opt(106,invalid);opt(103,travel);opt(105,mode);act(0,1,2);act(17,10,10);act(17,3,4);}
for(let gloc=0;gloc<L.NUM_GLOCS;gloc++)for(const selected of[-1,0,2]){scenario='menu allocation and choice';reset();opt(1,selected);act(0,1,2);cell(15,10,0,L.GLYPH_MON_MALE_OFF+1);cell(8,10,0,L.GLYPH_OBJ_OFF+1);cell(15,11,0,cmap(L.S_ndoor));act(18,gloc);}
for(const x of[1,2,40,78,79])for(const y of[0,1,10,19,20])for(const [dx,dy]of[[-8,-8],[-8,8],[8,-8],[8,8],[127,-128],[-128,127]]){scenario='truncate signed schar movement';reset();opt(118,x);opt(119,y);act(19,dx,dy);}
for(const sequence of['. ', ',',';',':','hljkyubn.','L.','Gl.','gk.','sL.','? .','vva.','ff.','!m.','mMm.','oO.','dD.','iI.','zZ.','@.','<.','^.','~.',' .']){scenario='interactive input '+sequence;reset();act(0,1,2);cell(15,10,0,L.GLYPH_MON_MALE_OFF+1);cell(8,10,0,L.GLYPH_OBJ_OFF+1);cell(15,11,0,cmap(L.S_ndoor));cell(18,10,0,cmap(L.S_upstair));for(const c of sequence)key(c);act(21,0);}
for(const force of[0,1])for(const c of[27,0,255,18]){scenario='escape mouse invalid help';reset();key(c,3,4,1);if(c!==27&&c!==0)key('.');act(21,force);}
for(const kind of[L.CMDQ_DIR,L.CMDQ_KEY,L.CMDQ_USER_INPUT]){scenario='queued initial command';reset();call('queue',kind,'.'.charCodeAt(0),1,-1,0);act(21);}
scenario='queued repeat and remember';reset();opt(112,1);opt(107,1);call('queue',L.CMDQ_KEY,'l'.charCodeAt(0),0,0,0);key('.');act(21);
scenario='growth and callback reentry';reset();act(0,1,1);opt(30,1);opt(31,1);const old=modules.map(m=>m.HEAPU8.buffer);act(5,0,1);assert.ok(trace().includes('growth;'));assert.ok(trace().includes('reentry:'));modules.forEach((m,i)=>assert.notEqual(m.HEAPU8.buffer,old[i]));
// A legitimate full monster display forces1,658 menu iterations. Automatic
// fullbuf/tmpcc/firstmatch storage must be released each iteration, unlike the
// two original static buffers which retain their addresses/content across calls.
scenario='large menu automatic lifetime';reset();opt(123,L.GLYPH_MON_MALE_OFF+1);opt(1,2);act(18,L.GLOC_MONS);assert.ok(trace().includes('sort:1659:4;'));assert.ok(trace().includes('cmp:'));
scenario='long input automatic lifetime';reset();for(let i=0;i<2000;i++)key(255);key('.');act(21,1);
scenario='static buffer retained alias';reset();act(15,99,-8,0);act(15,-6,11,1);assert.ok(snap(reference).state.includes('retained:11south,6west;'));
scenario='default null goal help identity';reset();key('?');key('.');act(21,0,2);
scenario='growth during pointer outputs';reset();act(0,1,2);opt(30,1);opt(31,1);key(0,7,8,1);act(21);assert.ok(trace().includes('growth;'));assert.ok(trace().includes('reentry:'));
scenario='separate Module state and static buffers';const other=await hybridFactory({nethackPorted:runtime});other._probe_reset();other._probe_action(0,1,2,0);other._probe_action(15,44,33,1);const otherSnapshot=snap(other),otherEnv=envs.get(other),otherState=[otherEnv.getpos_hilitefunc,otherEnv.getpos_getvalid,otherEnv.getpos_hilite_state];reset();act(0,1,1);act(1);act(15,9,8,0);assert.deepEqual(snap(other),otherSnapshot);assert.deepEqual([otherEnv.getpos_hilitefunc,otherEnv.getpos_getvalid,otherEnv.getpos_hilite_state],otherState);comparisons++;
scenario='dependency throw binding cleanup';let failedServices,entryStack;const throwingRuntime={getpos(services,name,...a){failedServices=services;entryStack=services.stackSave();const e=getEnv(services),saved=e.putstr;e.putstr=()=>{throw new Error('controlled GETPOS dependency throw');};try{return runtime.getpos(services,name,...a);}finally{e.putstr=saved;}}};const throwing=await hybridFactory({nethackPorted:throwingRuntime});throwing._probe_reset();const outerStack=throwing._probe_stack();assert.throws(()=>throwing._probe_action(5,0,0,0),/controlled GETPOS dependency throw/);assert.equal(C,undefined);assert.equal(throwing._probe_stack(),BigInt(entryStack));failedServices.stackRestore(Number(outerStack));assert.equal(throwing._probe_stack(),outerStack);comparisons++;
console.log(`GETPOS: ${comparisons} configured Emscripten-C/JS comparisons passed; native and production promotion pending.`);
