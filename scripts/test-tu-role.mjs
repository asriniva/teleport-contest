import {referenceBackend,referenceLabel,assertStackRestored,assertMemoryGrowth} from './native-test-backend.mjs';
import assert from './native-test-assert.mjs';
import {readFileSync} from 'node:fs';
import {resolve} from 'node:path';
import {pathToFileURL} from 'node:url';
import {callRole,initializeRole} from '../js/ported/role-runtime.js';
import * as role from '../js/ported/role.js';
import {C,R,T} from '../js/ported/c-runtime.js';
const author=process.env.TELEPORT_ROLE_PROBES,dir=author?pathToFileURL(resolve(author)+'/'):new URL('../.cache/tu-probes/',import.meta.url);
const referenceFactory=(await import(new URL('role-reference.mjs',dir))).default,hybridFactory=(await import(new URL('role-hybrid.mjs',dir))).default;
const ref=await referenceBackend('role',referenceFactory)();
function text(m,p){if(!p)return null;let e=Number(p);while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.slice(Number(p),e)).toString();}
const L={size:Number(ref._probe_context_size())};for(let i=0;i<ref._probe_layout_count();i++){const k=text(ref,ref._probe_layout_name(i)),v=ref._probe_layout_value(i);L[k]=/^(expr_|M2_)/.test(k)?BigInt.asUintN(64,v).toString():Number(BigInt.asIntN(64,v));}
if(!author)assert.deepEqual(L,JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url))).role);
for(const k of ['roleSize','raceSize','nameSize','genderSize','alignSize','NUM_ROLES','NUM_RACES','BUFSZ','ROLE_NONE','ROLE_RANDOM'])assert.ok(Number.isSafeInteger(L[k]),k);
const runtime={initializeRole:s=>initializeRole(s,L),role:(s,n,...a)=>callRole(s,L,n,...a)};
const modules=[ref,await hybridFactory({nethackPorted:runtime})],stacks=modules.map(m=>m._probe_stack());let comparisons=0;
const bytes=(m,p,n)=>Buffer.from(m.HEAPU8.slice(Number(p),Number(p)+n));
const nameOffsets=[L.name_m,L.name_f],roleOffsets=[...nameOffsets.map(o=>L.role_name+o),...Array.from({length:9},(_,i)=>nameOffsets.map(o=>L.role_rank+i*L.nameSize+o)).flat(),...['lgod','ngod','cgod','filecode','homebase','intermed'].map(k=>L['role_'+k])],raceOffsets=[...['noun','adj','coll','filecode'].map(k=>L['race_'+k]),...nameOffsets.map(o=>L.race_individual+o)],genderOffsets=['adj','he','him','his','filecode'].map(k=>L['gender_'+k]),alignOffsets=['noun','adj','filecode'].map(k=>L['align_'+k]);
function row(m,kind,index){const type=['role','race','gender','align','role','race'][kind-4],b=bytes(m,m._probe_pointer(kind,index),L[type+'Size']),strings=[];for(const o of ({role:roleOffsets,race:raceOffsets,gender:genderOffsets,align:alignOffsets})[type]){strings.push(text(m,b.readBigUInt64LE(o)));b.writeBigUInt64LE(0n,o);}return{bytes:b,strings};}
// Before any original function call: all JS-owned catalogues must equal actual original C.
for(const[k,count]of [[4,L.roleCount],[5,L.raceCount],[6,L.genderCount],[7,L.alignCount]])for(let i=0;i<count;i++){assert.deepEqual(row(modules[1],k,i),row(ref,k,i));comparisons++;}
function species(m){const out=[];for(let i=0;i<L.NUMMONS;i++){const p=Number(m._probe_pointer(10,i));if(!p)break;const v=new DataView(m.HEAPU8.buffer);out.push([v.getUint8(p+L.pm_msound),v.getBigUint64(p+L.pm_mflags2,true),v.getUint16(p+L.pm_mflags3,true),v.getInt8(p+L.pm_maligntyp)]);}return out;}
function snap(m){return{input:bytes(m,m._probe_pointer(0,0),1024),output:bytes(m,m._probe_pointer(1,0),1024),name:text(m,m._probe_pointer(2,0)),character:text(m,m._probe_pointer(3,0)),role:row(m,8,0),race:row(m,9,0),values:Array.from({length:30},(_,i)=>m._probe_value(i)),trace:text(m,m._probe_trace()),rng:[m._probe_rng_count(),m._probe_rng_state()>>>0],species:species(m)};}
function state(){assert.deepEqual(snap(modules[1]),snap(ref));assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);modules.forEach((m,i)=>assertStackRestored(m,stacks[i]));comparisons++;}
function call(n,...args){const r=modules.map(m=>m['_probe_'+n](...args));assert.deepEqual(r[1],r[0],n+'('+args+')');state();comparisons++;return r[0];}
function string(n,s){for(const m of modules){const b=Buffer.from(s),p=m._malloc(BigInt(b.length+1));m.HEAPU8.set(b,Number(p));m.HEAPU8[Number(p)+b.length]=0;m['_probe_'+n](BigInt(p));m._free(BigInt(p));}state();}
const reset=(seed=42)=>call('reset',seed),act=(op,...a)=>call('action',op,...Array.from({length:6},(_,i)=>a[i]??0)),field=(k,v)=>call('field',k,v);
reset();for(let i=0;i<4;i++)act(47,i);act(48,L.BUFSZ,-1,-1,-1,-1);
// Exhaustive valid/compatible selection rules, including original sentinel/negative index cases.
for(let r=-2;r<=L.NUM_ROLES;r++)for(let c=-2;c<=L.NUM_RACES;c++)for(let g=-2;g<=3;g++)for(let a=-2;a<=3;a++){for(const op of [13,15,17,19])act(op,r,c,g,a);}
for(let r=-2;r<=L.NUM_ROLES;r++){act(0,r);act(27,r);}for(let r=0;r<L.NUM_ROLES;r++){for(let c=-2;c<=L.NUM_RACES;c++){act(4,r,c);if(c>=0&&c<L.NUM_RACES)for(let g=-2;g<=3;g++){act(7,r,c,g);act(10,r,c,g);}}}
for(let c=-2;c<L.NUM_RACES;c++)act(28,c);
for(const s of ['', '*','@','random','RANDOM','Arc','Archeologist','Cavewoman','Priestess','Kni','unknown','elf','elven','Dwa','male','Fem','lawful','balance','Cha']){string('input',s);for(const op of [3,6,9,12])act(op);}
for(let r=-2;r<L.NUM_ROLES;r++)for(let c=-2;c<L.NUM_RACES;c++)for(const how of [L.PICK_RANDOM,L.PICK_RIGID]){reset();act(14,c,-1,-1,how);act(16,r,-1,-1,how);act(18,r,c,-1,how);act(20,r,c,-1,how);}
for(let r=0;r<L.NUM_ROLES;r++){reset();act(1,0);act(1,1);act(5,r);act(8,r,0);act(11,r,0);}
// Filter mutation/live native arrays; string suffix pointer and native formatting behavior.
for(const s of ['Arc','Bar','human','elf','female','chaotic','unknown']){reset();string('input',s);act(22);act(23);for(const aspect of [L.RS_ROLE,L.RS_RACE,L.RS_GENDER,L.RS_ALGNMNT])act(24,aspect);act(2);act(25,L.RS_filter);act(23);}
for(const r of [-2,-1,0,2,6,12])for(const c of [-2,-1,0,4])for(const g of [-2,-1,0,1])for(const a of [-2,-1,0,1,2]){reset();for(const size of [0,1,8,L.QBUFSZ,L.BUFSZ]){act(29,size,r,c,g,a);act(30,size,r,c,g,a);}}
for(const s of ['Hero-Arc-human-male-lawful','Hero-Cav-elf-female-chaotic','Unknown-@-random','Com,ma-Bar','Hero']){reset();string('name',s);act(31);}
for(const generic of ['*','Hero other','other Hero','other']){reset();string('generic',generic);act(31);}
// Role initialization/copies and actual native monster catalogue changes.
for(let r=0;r<L.NUM_ROLES;r++)for(const pantheon of [-1,0]){reset();field(0,r);field(4,pantheon);act(34);for(const pm of [L.PM_SHOPKEEPER,L.PM_MAIL_DAEMON,L.PM_HUMAN]){field(10,pm);act(35,1);}act(35,0);act(36);}
for(let pm=-1;pm<400;pm++)act(37,pm);
// All native menu entry functions and full anything/menu pointer ownership.
for(const aspect of [L.RS_NAME,L.RS_ROLE,L.RS_RACE,L.RS_GENDER,L.RS_ALGNMNT,L.RS_filter,L.ROLE_RANDOM,L.ROLE_NONE]){reset();act(32,aspect,7);act(33,aspect,7,1);act(41,24,aspect);act(42,24,aspect);}
for(const filtering of [0,1]){reset();for(const op of [43,44,45,46])act(op,7,filtering,-1,-1,-1);}
for(const answer of ['a','y','n','q','@',' ','\x1b']){reset();call('answer',answer.charCodeAt(0));act(39,24);}
reset();act(38);
for(const id of [-1,L.ROLE_RANDOM,1,2]){reset();call('answer','n'.charCodeAt(0));call('pick',0,1,id,0);act(39,24);}
reset();field(7,1);call('answer','y'.charCodeAt(0));call('pick',0,1,3,0);call('pick',1,1,1,0);act(39,24);
reset();call('answer','y'.charCodeAt(0));call('pick',0,1,2,0);act(39,24);
reset();call('pick',0,0,0,0);act(40);
reset();call('pick',0,2,-1000,-1013);act(40);assert.equal(ref._probe_value(16),1);
for(const aspect of [L.RS_RACE,L.RS_GENDER,L.RS_ALGNMNT,L.RS_filter]){reset();call('answer','n'.charCodeAt(0));call('pick',0,1,L.ROLE_RANDOM-(aspect+1),0);act(39,24);}
// Actual native memory growth occurs inside askname, then native globals are re-read.
reset();string('name','');field(13,1);const before=modules.map(m=>m.HEAPU8.buffer);act(31);modules.forEach((m,i)=>assertMemoryGrowth(m,before[i]));
const other=await hybridFactory({nethackPorted:runtime});other._probe_reset(7);other._probe_field(0,12);other._probe_action(34,0,0,0,0,0,0);assert.equal(other._probe_value(0),12);reset();field(0,0);act(34);assert.equal(other._probe_value(0),12);comparisons+=2;
console.log('ROLE '+comparisons+' comparisons passed ('+referenceLabel+' vs JavaScript).');
