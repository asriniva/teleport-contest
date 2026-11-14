// Validate finite ABI field selectors even when recordings never take the branch.
import fs from 'node:fs';
import assert from 'node:assert/strict';
import {withNetHackEnums} from '../js/nethack/c-types.js';
import raw from '../js/nethack/records.json' with {type:'json'};
const names={object:'obj',obj:'obj',monster:'monst',mon:'monst',class:'objclass',cls:'objclass',terrain:'rm',rm:'rm',trap:'trap',hero:'you',you:'you',level:'levelflags',levelFlags:'levelflags',levelflags:'levelflags',quest:'q_score',engr:'engr',egd:'egd',edog:'edog',have:'u_have',victual:'victual_info',vital:'mvitals',q_score:'q_score',u_event:'u_event'};
export function checkFieldTable(metadata,type,fields,label){
 for(const path of fields){let current=type.replace(/^(?:struct|union) /,'');
  for(const part of path.split('.')){
   const row=metadata.records[current],field=row?.fields[part];assert.ok(field,label+': unknown measured field '+current+'.'+part);
   current=field.record;
  }
 }
 return fields.length;
}
export function checkAbiFieldTables(){
 const metadata=withNetHackEnums(raw),tables=[];
 for(const file of fs.readdirSync('js/nethack').filter(n=>n.endsWith('-abi.json')).sort()){
  function visit(value,path=[],parent){
   if(Array.isArray(value)){
    if(!value.length||!value.every(x=>typeof x==='string'))return;
    const last=path.at(-1),typed=last==='fields'&&typeof parent?.type==='string';
    if(!typed&&!path.some(k=>/bits$/i.test(k)))return;
    const key=last==='fields'?path.at(-2):last;
    const base=key.replace(/Bits$/,'');
    const type=typed?parent.type:names[base]??(key==='bits'&&['were-abi.json','exper-abi.json','mhitm-abi.json'].includes(file)?'monst':undefined);
    assert.ok(type,'Unclassified ABI field table '+file+':'+path.join('.'));
    checkFieldTable(metadata,type,value,file+':'+path.join('.'));
    tables.push({file,path:path.join('.'),type,fields:value.length});return;
   }
   if(value&&typeof value==='object')for(const [key,child]of Object.entries(value))visit(child,[...path,key],value);
  }
  visit(JSON.parse(fs.readFileSync('js/nethack/'+file,'utf8')));
 }
 return{tables:tables.length,fields:tables.reduce((n,t)=>n+t.fields,0),selectors:tables};
}
if(process.argv[1]===new URL(import.meta.url).pathname){
 const result=checkAbiFieldTables();
 assert.throws(()=>checkFieldTable(withNetHackEnums(raw),'rm',['roomno','icdepools'],'mutated ICE table'),/unknown measured field/);
 assert.throws(()=>checkFieldTable(withNetHackEnums(raw),'you',['uhave.missing'],'mutated nested table'),/unknown measured field/);
 assert.throws(()=>checkFieldTable(raw,'rm',['icedpool'],'prior missing alias'),/unknown measured field/);
 fs.mkdirSync('.cache',{recursive:true});fs.writeFileSync('.cache/abi-field-tables.json',JSON.stringify(result,null,2)+'\n');
 console.log(JSON.stringify({passed:true,tables:result.tables,fields:result.fields,mutationsRejected:3}));
}
