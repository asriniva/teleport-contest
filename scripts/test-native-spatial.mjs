// Independent original-C spatial policies plus live typed-state alias checks.
import fs from 'node:fs';
import assert from 'node:assert/strict';
import {runFullOriginalC} from './full-original-c-run.mjs';
import {runStandaloneProgram} from './run-standalone-program.mjs';
import {nativeSpatialFor} from '../js/nethack/native/spatial-state.js';
import {C,withCEnvironment} from '../js/c-runtime/context.js';
const reference='.cache/full-original-c-v1',layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),records=JSON.parse(fs.readFileSync('js/nethack/records.json')).records,input={seed:1,timezone:'UTC',options:'OPTIONS=!news\n',keys:'  n'};
let module,runtime;const expected=await runFullOriginalC(reference,{...input,observeRuntime:r=>{module=r.module;}}),actual=runStandaloneProgram(reference+'/assets',{...input,observeRuntime:r=>{runtime=r;}});
for(const key of ['status','state','stdout','stderr','rngLog','displayRngLog'])assert.deepEqual(actual[key],expected[key],key+' initialized actual main');
const env=runtime.environment,space=nativeSpatialFor(env,layouts),ctypes=env.ctypes,arena=env.memory,cv=new DataView(module.HEAPU8.buffer),jv=arena.view,off=(t,n)=>records[t].fields[n].offset;
const globals=new Map();for(let i=0;i<module._full_global_count();i++){const p=Number(module._full_global_name(i));let e=p;while(module.HEAPU8[e])e++;globals.set(Buffer.from(module.HEAPU8.slice(p,e)).toString(),Number(module._full_global_address(i)));}
let checks=0;const eq=(a,b,label)=>{assert.deepEqual(a,b,label);checks++;},values=[-65537,-32769,-32768,-1,0,1,20,21,79,80,32767,32768,65535,65536];
for(const x of values)for(const y of values)eq(space.geometry.isok(x,y),module._isok(x,y),'C coordinate validity');
let state=0x12345678;const next=()=>{state=(Math.imul(state,1664525)+1013904223)>>>0;return state<<16>>16;};
for(let i=0;i<6000;i++){const a=[next(),next(),next(),next()];for(const name of ['dist2','distmin','online2'])eq(Number(space.geometry[name](...a)),module['_'+name](...a),'C '+name);}
for(const n of [-2147483648,-1,0,1,2,15,16,17,2147483647])for(const name of ['sgn','isqrt'])eq(Number(space.geometry[name](n)),module['_'+name](n),'C '+name);
const cLevel=globals.get('svl')+off('instance_globals_saved_l','level'),jLevel=env.requireGlobal('svl')+off('instance_globals_saved_l','level'),x=10,y=10,cCell=cLevel+off('dlevel_t','locations')+(x*21+y)*records.rm.size,jCell=jLevel+off('dlevel_t','locations')+(x*21+y)*records.rm.size;
const cb=module.HEAPU8.slice(cCell,cCell+records.rm.size),jb=arena.HEAPU8.slice(jCell,jCell+records.rm.size);
const cu=globals.get('u'),ju=env.requireGlobal('u'),cUz=cu+off('you','uz'),jUz=ju+off('you','uz'),cTopo=globals.get('svd')+off('instance_globals_saved_d','dungeon_topology')+off('dgn_topology','d_juiblex_level'),jTopo=env.requireGlobal('svd')+off('instance_globals_saved_d','dungeon_topology')+off('dgn_topology','d_juiblex_level');
const saved=[module.HEAPU8.slice(cTopo,cTopo+records.d_level.size),arena.HEAPU8.slice(jTopo,jTopo+records.d_level.size)];
try{
 for(const juiblex of [false,true]){
  for(const [v,p,u]of [[cv,cTopo,cUz],[jv,jTopo,jUz]])for(const key of ['dnum','dlevel'])v.setInt8(p+off('d_level',key),v.getInt8(u+off('d_level',key))+(juiblex?0:1));
  for(let typ=0;typ<=36;typ++)for(let mask=0;mask<32;mask++){
   module.HEAPU8.set(cb,cCell);arena.HEAPU8.set(jb,jCell);cv.setInt8(cCell+off('rm','typ'),typ);space.cells[x][y].typ=typ;
   const f=records.rm.fields.flags,packed=((1<<f.bits)-1)<<f.shift;module.HEAPU8[cCell+f.offset]=(module.HEAPU8[cCell+f.offset]&~packed)|(mask<<f.shift);space.cells[x][y].drawbridgemask=mask;
   for(const name of ['is_pool','is_lava','is_waterwall','is_moat','is_ice','is_pool_or_lava'])eq(space.terrain[name](x,y),module['_'+name](x,y),'C terrain '+name);
   eq(space.terrain.db_under_typ(mask),module._db_under_typ(mask),'C drawbridge under');
  }
 }
}finally{module.HEAPU8.set(cb,cCell);arena.HEAPU8.set(jb,jCell);module.HEAPU8.set(saved[0],cTopo);arena.HEAPU8.set(saved[1],jTopo);}
const allocate=(type)=>{const n=records[type].size,c=Number(module._malloc(BigInt(n))),j=arena.calloc(1,n);module.HEAPU8.fill(0,c,c+n);return{c,j};};
const allocations=[],make=t=>{const r=allocate(t);allocations.push(r);return r;},pointer=(view,at,v)=>view.setBigUint64(at,BigInt(v),true);
const cTrap=globals.get('gf')+off('instance_globals_f','ftrap'),jTrap=env.requireGlobal('gf')+off('instance_globals_f','ftrap'),oldTrap=[cv.getBigUint64(cTrap,true),jv.getBigUint64(jTrap,true)],traps=[make('trap'),make('trap')];
try{
 for(const [v,k]of [[cv,'c'],[jv,'j']]){pointer(v,k==='c'?cTrap:jTrap,traps[0][k]);for(let i=0;i<2;i++){const p=traps[i][k];v.setInt16(p+off('trap','tx'),x,true);v.setInt16(p+off('trap','ty'),y,true);pointer(v,p+off('trap','ntrap'),i?0:traps[1][k]);}}
 for(const [dx,dy]of [[0,0],[1,0],[0,1],[65536,0]]){const c=Number(module._t_at(x+dx,y+dy)),j=env.services.t_at(x+dx,y+dy);eq(c?traps.findIndex(t=>t.c===c):-1,j?traps.findIndex(t=>t.j===j):-1,'C trap linked-list first match');}
}finally{pointer(cv,cTrap,oldTrap[0]);pointer(jv,jTrap,oldTrap[1]);}
const cEngr=globals.get('head_engr'),jEngr=env.requireGlobal('head_engr'),oldEngr=[cv.getBigUint64(cEngr,true),jv.getBigUint64(jEngr,true)],engr=[make('engr'),make('engr')];
const string=text=>{const b=Buffer.from(text+'\0'),c=Number(module._malloc(BigInt(b.length))),j=arena.cstring(text);module.HEAPU8.set(b,c);allocations.push({c,j});return{c,j};};
const text=string('The Elbereth ward'),queries=[string('elbereth'),string('the elbereth ward'),string('absent')];
try{
 for(const [v,k,head,moves]of [[cv,'c',cEngr,globals.get('svm')],[jv,'j',jEngr,env.requireGlobal('svm')]]){pointer(v,head,engr[0][k]);for(let i=0;i<2;i++){const p=engr[i][k];pointer(v,p+off('engr','nxt_engr'),i?0:engr[1][k]);pointer(v,p+off('engr','engr_txt'),text[k]);v.setInt16(p+off('engr','engr_x'),x,true);v.setInt16(p+off('engr','engr_y'),y,true);v.setInt8(p+off('engr','engr_type'),layouts.engrave.DUST);v.setBigInt64(p+off('engr','engr_time'),v.getBigInt64(moves+off('instance_globals_saved_m','moves'),true)-1n,true);}}
 const match=(c,j,label)=>eq(c?engr.findIndex(e=>e.c===Number(c)):-1,j?engr.findIndex(e=>e.j===(j.address??j)):-1,label);
 for(const [dx,dy]of [[0,0],[1,0],[65536,0]])match(module._engr_at(x+dx,y+dy),env.services.engr_at(x+dx,y+dy),'C engraving head order and coordinate width');
 for(const type of [layouts.engrave.DUST,layouts.engrave.HEADSTONE])for(const future of [false,true]){
  for(const [v,k,moves]of [[cv,'c',globals.get('svm')],[jv,'j',env.requireGlobal('svm')]]){v.setInt8(engr[0][k]+off('engr','engr_type'),type);v.setBigInt64(engr[0][k]+off('engr','engr_time'),v.getBigInt64(moves+off('instance_globals_saved_m','moves'),true)+(future?1n:-1n),true);}
  for(const strict of [0,1])for(const query of queries)match(module._sengr_at(BigInt(query.c),x,y,strict),env.services.sengr_at(query.j,x,y,strict),'C engraving text, headstone and time');
 }
}finally{pointer(cv,cEngr,oldEngr[0]);pointer(jv,jEngr,oldEngr[1]);}
// Region lookup order and replacement of the pointer table are exercised using
// the same measured records as the original C functions.
const regions=[make('NhRegion'),make('NhRegion')],rects=[make('nhrect'),make('nhrect')],cRegion=globals.get('gr')+off('instance_globals_r','regions'),jRegion=env.requireGlobal('gr')+off('instance_globals_r','regions'),cCount=globals.get('svn')+off('instance_globals_saved_n','n_regions'),jCount=env.requireGlobal('svn')+off('instance_globals_saved_n','n_regions'),oldRegions=[cv.getBigUint64(cRegion,true),jv.getBigUint64(jRegion,true),cv.getInt32(cCount,true),jv.getInt32(jCount,true)],cTable=Number(module._malloc(16n)),jTable=arena.calloc(2,8);allocations.push({c:cTable,j:jTable});
try{
 for(const [v,k,table,root,count]of [[cv,'c',cTable,cRegion,cCount],[jv,'j',jTable,jRegion,jCount]]){
  pointer(v,root,table);v.setInt32(count,2,true);
  for(let i=0;i<2;i++){const p=regions[i][k],rect=rects[i][k];pointer(v,table+i*8,p);pointer(v,p+off('NhRegion','rects'),rect);v.setInt16(p+off('NhRegion','nrects'),1,true);v.setInt8(p+off('NhRegion','visible'),1);v.setBigInt64(p+off('NhRegion','ttl'),5n,true);for(const [name,value]of [['lx',9],['ly',9],['hx',11],['hy',11]]){v.setInt16(rect+off('nhrect',name),value,true);v.setInt16(p+off('NhRegion','bounding_box')+off('nhrect',name),value,true);}}
 }
 for(const inactive of [false,true]){
  cv.setBigInt64(regions[0].c+off('NhRegion','ttl'),inactive?-2n:5n,true);jv.setBigInt64(regions[0].j+off('NhRegion','ttl'),inactive?-2n:5n,true);
  for(const [rx,ry]of [[10,10],[9,9],[11,11],[12,10]]){const c=Number(module._visible_region_at(rx,ry)),j=env.services.visible_region_at(rx,ry)?.address??0;eq(c?regions.findIndex(r=>r.c===c):-1,j?regions.findIndex(r=>r.j===j):-1,'C visible-region traversal order');}
  eq(space.regions.any_visible_region(),module._any_visible_region(),'C visible region flag');
 }
}finally{pointer(cv,cRegion,oldRegions[0]);pointer(jv,jRegion,oldRegions[1]);cv.setInt32(cCount,oldRegions[2],true);jv.setInt32(jCount,oldRegions[3],true);}
for(const r of allocations){module._free(BigInt(r.c));arena.free(r.j);}
const marker={nativeSpatialCaller:true};withCEnvironment(marker,()=>{for(const name of ['isok','dist2','is_pool','t_at','engr_at','visible_region_at']){const fn=env.services[name].nativeEntry;assert.ok(fn,'live native publication '+name);fn(1,1,2,2);assert.equal(C,marker,'native helper preserves caller scope');}});
const original=space.cells[x][y];arena.grow(arena.buffer.byteLength+1);eq(space.cells[x][y],original,'growth preserves map identity');original.typ=layouts.hack.ROOM;eq(jv.buffer===arena.buffer,false,'old DataView detached from new storage');eq(arena.view.getInt8(jCell+off('rm','typ')),layouts.hack.ROOM,'native map survives growth');arena.HEAPU8.set(jb,jCell);
fs.mkdirSync('.cache/native-spatial',{recursive:true});fs.writeFileSync('.cache/native-spatial/evidence.json',JSON.stringify({passed:true,checks,originalC:true,geometry:true,terrain:true,trapOrder:true,regionOrder:true,engravingOrderAndText:true,callerScope:true,growth:true},null,2)+'\n');console.log(JSON.stringify({passed:true,checks}));
