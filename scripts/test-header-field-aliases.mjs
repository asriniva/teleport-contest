// Header member names are alternate views of compiler-measured storage.
import fs from 'node:fs';
import assert from 'node:assert/strict';
import {createStandaloneEnvironment} from '../js/nethack/environment.js';
import {createCTypes,withNetHackEnums} from '../js/nethack/c-types.js';
import {createBitfields} from '../js/c-runtime/bitfields.js';
import {fieldAliases} from '../js/nethack/declarations.js';
import raw from '../js/nethack/records.json' with {type:'json'};
import {createNativeRecordViews} from '../js/nethack/native/record-views.js';
let checks=0,aliases=0;const held=[];
const equal=(a,b,label)=>{assert.deepEqual(a,b,label);checks++;};
const env=createStandaloneEnvironment(),native=createNativeRecordViews(env),metadata=withNetHackEnums(raw);
const direct=createCTypes(env.memory,raw,createBitfields(env.memory,raw));
for(const [header,type]of [['rm.h','rm'],['obj.h','obj'],['objclass.h','objclass'],['trap.h','trap'],['flag.h','instance_flags']]){
 const source=fs.readFileSync('nethack-c/upstream/include/'+header,'utf8');
 const measured={};for(const m of source.matchAll(/^#\s*define\s+(\w+)\s+(\w+(?:\.\w+)*)\s*(?=\/\*|$)/gm))if(Object.hasOwn(raw.records[type].fields,m[2].split('.')[0]))measured[m[1]]=m[2];
 equal(fieldAliases[type],measured,'exhaustive '+header+' member aliases');
}
const globals={'tcap.h:AS':'tc_gbl_data.tc_AS','tcap.h:AE':'tc_gbl_data.tc_AE','tcap.h:LI':'tc_gbl_data.tc_LI','tcap.h:CO':'tc_gbl_data.tc_CO','flag.h:wizard':'flags.debug','flag.h:discover':'flags.explore'};
const allFields=new Set(Object.values(raw.records).flatMap(row=>Object.keys(row.fields)));
let census=0;
for(const file of fs.readdirSync('nethack-c/upstream/include').filter(f=>f.endsWith('.h'))){
 const source=fs.readFileSync('nethack-c/upstream/include/'+file,'utf8');
 for(const [,name,path]of source.matchAll(/^#\s*define\s+(\w+)\s+(\w+(?:\.\w+)*)\s*(?=\/\*|$)/gm)){
  if(!allFields.has(path.split('.')[0]))continue;census++;
  if(Object.hasOwn(globals,file+':'+name))equal(path,globals[file+':'+name],'explicit global alias');
  else assert.ok(Object.values(fieldAliases).some(rows=>rows[name]===path),'Unclassified header member alias '+file+': '+name+' -> '+path);
 }
}
assert.equal(census,53,'all member-like header defines reviewed, including six global aliases');
function target(type,p,path){for(const key of path.split('.')){const f=env.ctypes.locate(type,p,key);p=f.at;type=f.field.record??f.field.ctype.replace(new RegExp('\\b'+key+'$'),'');}return {type,p};}
for(const [type,rows]of Object.entries(fieldAliases))for(const [alias,path]of Object.entries(rows)){
 aliases++;const p=env.memory.calloc(1,raw.records[type].size),view=native.record(type,p),plan=metadata.records[type].fields[alias],ref=target(type,p,path);
 equal(env.ctypes.locate(type,p,alias).at,ref.p,type+'.'+alias+' offset');
 equal(env.ctypes.fieldAddress(type,p,alias),ref.p,type+'.'+alias+' byte address');
 for(const value of [-1,0,1,2,8,16,31,63,255,65539,2147483648,4294967295]){
  env.memory.HEAPU8.fill(0xa5,p,p+raw.records[type].size);
  const before=Buffer.from(env.memory.HEAPU8.slice(p,p+raw.records[type].size));
  const scalar=plan.ctype.replace(new RegExp('\\b'+alias+'$'),'').trim();
  if(plan.record){
   const src=env.memory.calloc(1,env.ctypes.size(plan.record));env.memory.HEAPU8.fill(value&255,src,src+env.ctypes.size(plan.record));
   env.ctypes.setField(type,p,alias,scalar,src);equal(Buffer.from(env.memory.HEAPU8.slice(ref.p,ref.p+env.ctypes.size(plan.record))),Buffer.from(env.memory.HEAPU8.slice(src,src+env.ctypes.size(plan.record))),'aggregate alias copy');env.memory.free(src);continue;
  }
  const input=scalar.includes('*')?(value===0?0:p):value;
  const write=api=>api.setField(type,p,alias,scalar,input),read=api=>api.getField(type,p,alias,scalar);
  write(env.ctypes);const expected=Buffer.from(env.memory.HEAPU8.slice(p,p+raw.records[type].size));
  const result=read(env.ctypes);equal(view[alias]?.address??view[alias],typeof result==='bigint'&&scalar.includes('*')?Number(result):result,'native alias sees generic write '+type+'.'+alias);
  env.memory.HEAPU8.set(before,p);write(direct);equal(Buffer.from(env.memory.HEAPU8.slice(p,p+raw.records[type].size)),expected,'direct raw-driver alias '+type+'.'+alias);
  env.memory.HEAPU8.set(before,p);view[alias]=typeof result==='bigint'?BigInt(input):input;
  equal(Buffer.from(env.memory.HEAPU8.slice(p,p+raw.records[type].size)),expected,'native alias writes same bytes '+type+'.'+alias);
 }
 held.push({type,alias,p,view,plan});
}
const old=env.memory.buffer;assert.ok(env.memory.grow(old.byteLength+8));assert.notEqual(env.memory.buffer,old);checks++;
for(const {type,alias,p,view,plan}of held){
 if(!plan.record){const scalar=plan.ctype.replace(new RegExp('\\b'+alias+'$'),'').trim();env.ctypes.setField(type,p,alias,scalar,scalar.includes('*')?p:1);equal(view[alias]?.address??view[alias],scalar.includes('*')?p:typeof env.ctypes.getField(type,p,alias,scalar)==='bigint'?1n:1,'alias survives growth');}
 env.memory.free(p);
}
assert.equal(aliases,47);
let restoredRecordFields=0;
for(const [type,row]of Object.entries(raw.records))for(const [key,field]of Object.entries(row.fields)){
 const projected=metadata.records[type].fields[key];if(field.record||!projected.record)continue;
 restoredRecordFields++;
 const p=env.memory.calloc(1,row.size),size=env.ctypes.size(projected.record),source=env.memory.calloc(1,size);
 env.memory.HEAPU8.fill(0x5a,source,source+size);
 equal(env.ctypes.getField(type,p,key,'unsigned int'),BigInt(p+field.offset),'aggregate field yields its address '+type+'.'+key);
 equal(direct.getField(type,p,key,'unsigned int'),BigInt(p+field.offset),'direct aggregate field '+type+'.'+key);
 equal(native.record(type,p)[key].address,p+field.offset,'native aggregate identity '+type+'.'+key);
 env.ctypes.setField(type,p,key,'unsigned int',source);
 equal(Buffer.from(env.memory.HEAPU8.slice(p+field.offset,p+field.offset+size)),Buffer.from(env.memory.HEAPU8.slice(source,source+size)),'whole aggregate copy '+type+'.'+key);
 env.memory.free(source);env.memory.free(p);
}
const conflicting={...raw,records:{...raw.records,rm:{...raw.records.rm,fields:{...raw.records.rm.fields,icedpool:{...raw.records.rm.fields.flags,offset:0,ctype:'unsigned int icedpool'}}}}};
assert.throws(()=>withNetHackEnums(conflicting),/Conflicting header alias/);checks++;
assert.throws(()=>env.ctypes.getField('rm',16,'icdepools','unsigned int'),/Unmeasured C field/);checks++;
console.log(JSON.stringify({passed:true,aliases,headerCandidates:census,restoredRecordFields,checks}));
