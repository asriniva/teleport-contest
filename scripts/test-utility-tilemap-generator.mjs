import {parseArgs} from 'node:util';
import {resolve} from 'node:path';
import {pathToFileURL} from 'node:url';
const cli=parseArgs({options:{out:{type:'string'}}});
if(!cli.values.out)throw Error('--out is required');
const outURL=pathToFileURL(resolve(cli.values.out)+'/');
const rf=(await import(new URL('reference.mjs',outURL))).default;
const hf=(await import(new URL('hybrid.mjs',outURL))).default;
import assert from'node:assert/strict';import{writeFileSync,mkdirSync}from'node:fs';import{createHash}from'node:crypto';;;import{createUtility}from'../js/ported-utilities/tilemap-generator-runtime.mjs';import{C,R,T}from'../js/ported-utilities/tilemap-scope.mjs';
let checks=0;const results=[],digest=b=>createHash('sha256').update(b).digest('hex');
async function run(factory,{src=true,argc=0,direct=false,grow=false}={}){const stdout=[],stderr=[],m=await factory({print:s=>stdout.push(s),printErr:s=>stderr.push(s),quit:(n,e)=>{throw e;}});let u;if(factory===hf){u=createUtility(m);m.utilityInvoke=(...a)=>u.invoke(...a);m.utilityState=i=>u.C[['TILE_corr','TILE_stone','TILE_unexplored','TILE_nothing','lastmontile','lastobjtile','lastothtile','laststatuetile'][i]];}
 m.FS.mkdir('/util');if(src)m.FS.mkdir('/src');m.FS.chdir('/util');let grew=false;
 if(grow&&factory===hf){const old=m._gen_snprintf0;let once=false;m._gen_snprintf0=(...args)=>{if(!once){once=true;const before=m.HEAPU8.buffer,p=m._malloc(BigInt(m.HEAPU8.byteLength*2));assert.notEqual(m.HEAPU8.buffer,before);m._free(BigInt(p));grew=true;}return old(...args);};}
 let code;try{if(direct){m._probe_init_catalogues();m._probe_init_map();code=0;}else code=m._probe_run(argc,0n);}catch(e){if(e.name!=='ExitStatus')throw e;code=e.status;}
 const files={};for(const f of ['/src/tile.c','/util/tilemappings.lst']){try{files[f]=Buffer.from(m.FS.readFile(f));}catch{files[f]=null;}}
 const state=Array.from({length:8},(_,i)=>m._probe_state(i)),map=Number(m._probe_map()),size=Number(m._tm_layout(14)),n=Number(m._tm_layout(3)),mapBytes=Buffer.from(m.HEAPU8.subarray(map,map+size*n));
 const list=[];const text=p=>{let q=p;while(m.HEAPU8[q])q++;return Buffer.from(m.HEAPU8.subarray(p,q)).toString();};for(let i=0;i<2500;i++){const p=Number(m._probe_list(i));if(p){const v=new DataView(m.HEAPU8.buffer);list.push({i,n:v.getInt32(p,true),src:v.getInt32(p+4,true),entry:v.getInt32(p+8,true),name:text(p+Number(m._tm_layout(20))),refs:text(p+Number(m._tm_layout(21)))});}}
 if(direct){m._probe_free();for(let i=0;i<2500;i++)assert.equal(Number(m._probe_list(i)),0);checks+=2500;}
 assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);return{code,stdout,stderr,files,state,mapBytes,list,n,size,grew};}
async function check(name,options={}){const a=await run(rf,options),b=await run(hf,options);for(const k of['code','stdout','stderr','state','mapBytes','list']){assert.deepEqual(b[k],a[k],name+' '+k);checks++;}for(const f of Object.keys(a.files)){assert.deepEqual(b.files[f],a.files[f],name+' '+f);checks++;}if(options.grow)assert.ok(b.grew);const row={name,code:a.code,state:a.state,glyphRows:a.n,listingRecords:a.list.length,files:Object.fromEntries(Object.entries(a.files).map(([k,v])=>[k,v?{bytes:v.length,sha256:digest(v)}:null])),scope:'Actual current-EmC implementation observation; inherited self-overlap snprintf path not portable defined C'};results.push(row);return a;}
// Defined native constant-table observations, independent of init_tilemap's overlap.
{
 const ref=await rf(),hybrid=await hf(),u=createUtility(hybrid);
 for(const[kind,key,n]of[[0,'wall_offsets',5],[1,'expl_offsets',7]])for(let i=0;i<n;i++){assert.equal(u.C[key][i],ref._probe_offset(kind,i),'configured offset table '+key+':'+i);checks++;}
}
const a=await check('complete-generator');assert.equal(a.code,0);checks++;const file=a.files['/src/tile.c'].toString(),listing=a.files['/util/tilemappings.lst'].toString();assert.ok(file.includes('glyph_map glyphmap[MAX_GLYPH]'));assert.equal((file.match(/^    \{ 0U,/gm)||[]).length,a.n);assert.equal((listing.match(/^glyph\[/gm)||[]).length,a.n);assert.ok(file.endsWith('/*tile.c*/\n'));assert.ok(a.state[7]>=a.state[6]);checks+=5;
const out=new URL('./observed-output/',outURL);mkdirSync(out,{recursive:true});writeFileSync(new URL('tile.c',out),a.files['/src/tile.c']);writeFileSync(new URL('tilemappings.lst',out),a.files['/util/tilemappings.lst']);
assert.equal((await check('ignored-source-arguments',{argc:29})).code,0);checks++;
assert.equal((await check('missing-src-directory',{src:false})).code,1);checks++;
await check('direct-init-map-cleanup',{direct:true});await check('growth-native-format-boundary',{grow:true});
writeFileSync(new URL('results.json',outURL),JSON.stringify({status:'PASS CURRENT EMC OBSERVATION',ownedFunctions:8,newFunctions:2,checks,scenarios:results.length,results,inheritedUB:'Source overlapping snprintf destination and %s argument in unexplored name preserved exactly; full generator output parity is measured for actual EmC, not portable C semantics.',limits:'Actual configured plain profile only; source catalogue/data init realC; no host/game/public/timing or other statue/enhanced profiles.'},null,2)+'\n');console.log('PASS plain TILEMAP generator '+results.length+' whole-output observations/'+checks+' checks (inherited snprintf overlap explicitly qualified)');
