// Development-only author: original C, ordinary keys and read-only map observations.
// No setup policy calls, game-state/RNG writes, or translated production modules.
import fs from 'node:fs';
import path from 'node:path';
import {runFullOriginalC} from './full-original-c-run.mjs';
const reference=path.resolve(process.env.STANDALONE_FULL_C_REFERENCE??'.cache/full-original-c-v1');
const out='.cache/sink-discovery';fs.mkdirSync(out,{recursive:true});
const records=JSON.parse(fs.readFileSync('js/standalone/records.json')).records;
const commandInput=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')).cmd.commandInp;
const base={timezone:'UTC',options:'OPTIONS=!news\n',argv:['-u','Ada-male-lawful','-p','Archeologist','-r','human']};
function globals(m){const result={};for(let i=0;i<m._full_global_count();i++){let p=Number(m._full_global_name(i)),e=p;while(m.HEAPU8[e])e++;result[Buffer.from(m.HEAPU8.slice(p,e)).toString()]=Number(m._full_global_address(i));}return result;}
function route(module,state){
 const g=globals(module),start=g.svl+records.instance_globals_saved_l.fields.level.offset+records.dlevel_t.fields.locations.offset;
 const typ=(x,y)=>module.HEAPU8[start+(x*21+y)*records.rm.size+records.rm.fields.typ.offset];
 const initial=[state.x,state.y],queue=[[...initial,'']],seen=new Set([initial.join(',')]);
 for(let i=0;i<queue.length;i++){
  const [x,y,keys]=queue[i];if(typ(x,y)===30)return{position:[x,y],keys};
  for(const [dx,dy,key]of [[-1,0,'h'],[1,0,'l'],[0,-1,'k'],[0,1,'j']]){
   const nx=x+dx,ny=y+dy,id=nx+','+ny;if(nx<1||nx>=80||ny<0||ny>=21||seen.has(id))continue;
   const terrain=typ(nx,ny),flags=module.HEAPU8[start+(nx*21+ny)*records.rm.size+records.rm.fields.flags.offset]&31;
   if(![23,24,25,26,27,28,29,30].includes(terrain)||(terrain===23&&(flags&8)))continue;
   seen.add(id);queue.push([nx,ny,keys+(terrain===23&&(flags&4)?'o'+key:'')+key]);
  }
 }
 return null;
}
for(let seed=Number(process.env.SINK_FIRST_SEED??1);seed<=Number(process.env.SINK_LAST_SEED??100);seed++){
 let sink,g,pendingDirection,metamorphosis=false,toxic=false;const events=[];
 const result=await runFullOriginalC(reference,{...base,seed,maxInputBoundaries:512,authorKey({module,state,frame,consumed}){
  if(consumed<3)return '  n'.charCodeAt(consumed);
  g??=globals(module);const inputState=new DataView(module.HEAPU8.buffer).getInt32(g.program_state+records.sinfo.fields.input_state.offset,true);
  const screen=(frame?.screen??'').replace(/\x1b\[[0-9;?]*[A-Za-z]/g,'');
  metamorphosis ||=screen.includes('freakish metamorphosis');toxic ||=screen.includes('toxic wastes');
  events.push({consumed,position:[state.x,state.y],inputState,screen:screen.split('\n')[0]});
  if(consumed>=480)return undefined;
  if(inputState!==commandInput){if(inputState===3&&pendingDirection){const key=pendingDirection;pendingDirection=undefined;return key.charCodeAt(0);}return /drink.*sink/i.test(screen)?121:32;}
  if(metamorphosis)return undefined;
  const next=route(module,state);if(!next)return undefined;sink??=next;
  if(next.keys==='')return 113;
  if(next.keys[0]==='o')pendingDirection=next.keys[1];
  return next.keys.charCodeAt(0);
 }});
 if(!sink)continue;const keys=result.input.keys;
 const u=Buffer.from(result.globals.u,'base64');
 const row={seed,sink,status:result.status,consumed:result.consumed,metamorphosis,toxic,form:u.readInt32LE(records.you.fields.umonnum.offset),human:u.readInt32LE(records.you.fields.umonster.offset),keys};console.log(JSON.stringify(row));
 fs.writeFileSync(out+'/last-candidate.json',JSON.stringify(row,null,2));fs.writeFileSync(out+'/last-native-result.json',JSON.stringify(result));
 fs.writeFileSync(out+'/last-input-events.json',JSON.stringify(events,null,2));
 if(row.metamorphosis&&result.status.kind==='input-exhausted'){const tag=row.form===row.human?'newman':'monster';fs.writeFileSync(out+'/'+tag+'-input.json',JSON.stringify({...base,seed,keys},null,2));fs.writeFileSync(out+'/'+tag+'-native-result.json',JSON.stringify(result));fs.writeFileSync(out+'/'+tag+'-discovery.json',JSON.stringify(row,null,2));if(process.env.SINK_REQUIRE_MONSTER!=='1'||tag==='monster')break;}
}
