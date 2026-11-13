import './pure-js-probes/deny-wasm.mjs';
import assert from 'node:assert/strict';import fs from 'node:fs';
import {DataView as FixtureDataView} from './native-test-backend.mjs';
// Existing harness's supported one-case mode prepares its full native/JS
// worlds without rerunning its unrelated cases before this additional matrix.
const prior=process.env.SHK_ONE;process.env.SHK_ONE='get_cost';let harness;
try{harness=await import('./test-tu-shk.mjs');}finally{prior===undefined?delete process.env.SHK_ONE:process.env.SHK_ONE=prior;}
const {schema,mods,run,record,ptr,global,write64,option,constant,field,get}=harness;
const records=JSON.parse(fs.readFileSync('js/nethack/records.json')).records,size=constant('size:struct objclass');assert.equal(size,records.objclass.size);
const count=Number(schema.globals.find(row=>row.name==='objects').canonical.match(/\[(\d+)\]/)[1]),classAt=records.objclass.fields.oc_class.offset;
const classes=Array.from({length:count},(_,i)=>new FixtureDataView(mods[0].HEAPU8.buffer).getInt8(Number(global(mods[0],'objects'))+i*size+classAt));
function item(m,type,known){record(m,ptr(m,0),'obj','otyp',type);record(m,ptr(m,0),'obj','oclass',classes[type]);record(m,ptr(m,0),'obj','dknown',known&1);record(m,global(m,'objects')+BigInt(type*size),'objclass','oc_name_known',(known>>1)&1);}
let cases=0;
for(let type=1;type<count;type++)if(classes[type])for(const fn of ['getprice','get_cost']){
 run('catalogue '+type,fn,m=>{item(m,type,3);option(m,66,12);});cases++;
}
const types=[...new Set(['DIAMOND','OPAL','SAPPHIRE','POT_WATER','MAGIC_LAMP','OIL_LAMP','WAX_CANDLE','TALLOW_CANDLE','CORPSE','ROCK','DUNCE_CAP'].map(constant).concat(Array.from({length:9},(_,i)=>constant('FIRST_GLASS_GEM')+i)))];
for(const type of types)for(const charisma of [3,5,6,7,8,10,11,15,16,17,18,19,25])for(const known of [0,1,2,3])for(const surcharge of [0,1]){
 run('pricing '+[type,charisma,known,surcharge].join(':'),'get_cost',m=>{item(m,type,known);option(m,66,charisma);record(m,ptr(m,2),'eshk','surcharge',surcharge);record(m,ptr(m,1),'monst','mpeaceful',1-surcharge);});cases++;
}
for(const clothing of ['none','dunce','shirt','armored-shirt','cloaked-shirt'])for(const tourist of [0,1])for(const level of [14,15])for(const charisma of [5,12,18,19]){
 run('visible clothing '+[clothing,tourist,level,charisma].join(':'),'get_cost',m=>{
  option(m,66,charisma);field(m,'u.ulevel',level);if(tourist)field(m,'gu.urole.mnum',constant('PM_TOURIST'));
  if(clothing==='dunce'){record(m,ptr(m,0,1),'obj','otyp',constant('DUNCE_CAP'));write64(m,global(m,'uarmh'),ptr(m,0,1));}
  if(clothing.includes('shirt'))write64(m,global(m,'uarmu'),ptr(m,0,1));
  if(clothing==='armored-shirt')write64(m,global(m,'uarm'),ptr(m,0,2));
  if(clothing==='cloaked-shirt')write64(m,global(m,'uarmc'),ptr(m,0,2));
 });cases++;
}
for(let color=0;color<9;color++)for(const birthday of [-9223372036854775808n,-2147483649n,0n,2147483648n,9007199254740993n,9223372036854775807n])for(const known of [0,1,2,3]){
 run('glass colour/birthday '+[color,birthday,known].join(':'),'get_cost',m=>{item(m,constant('FIRST_GLASS_GEM')+color,known);write64(m,global(m,'ubirthday'),birthday);option(m,66,12);});cases++;
}
assert.ok(cases>3000);console.log('PASS:'+cases+' original-C/pure-JS catalogue/price/knowledge/charisma/surcharge/clothing/glass-birthday cases; full existing fixture state/trace/result checks, with actual C catalogue classes. Controlled shop dependencies.');
