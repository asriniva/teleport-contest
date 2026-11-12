// Original-C author only: read-only map/room/object observations, keyboard actions.
import fs from 'node:fs';import {gzipSync} from 'node:zlib';import {runFullOriginalC} from './full-original-c-run.mjs';
const R=JSON.parse(fs.readFileSync('js/nethack/records.json')).records,L=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),out='.cache/shop-author';fs.mkdirSync(out,{recursive:true});const f=(t,n)=>R[t].fields[n].offset;
const profile={timezone:'UTC',options:'OPTIONS=!news,autopickup\n',argv:['-u','Ada-male-neutral','-p','Tourist','-r','human']};
for(let seed=Number(process.env.FIRST_SEED??7);seed<=Number(process.env.LAST_SEED??7);seed++){
 let menuSelected=false;let g,pending,phase='travel',target,previous='',stalls=0,lastLevel,selected;const events=[];
 const result=await runFullOriginalC('.cache/full-original-c-v1',{...profile,seed,maxInputBoundaries:1000,authorKey({module:m,state,frame,consumed}){
  if(consumed<3)return '  n'.charCodeAt(consumed);
  if(!g){g={};for(let i=0;i<m._full_global_count();i++){let p=Number(m._full_global_name(i)),e=p;while(m.HEAPU8[e])e++;g[Buffer.from(m.HEAPU8.slice(p,e)).toString()]=Number(m._full_global_address(i));}}
  const v=new DataView(m.HEAPU8.buffer),ptr=p=>Number(v.getBigUint64(p,true)),level=g.u+f('you','uz'),dnum=v.getInt16(level,true),dlevel=v.getInt16(level+2,true),input=v.getInt32(g.program_state+f('sinfo','input_state'),true),text=(frame?.screen??'').split('\n')[0];
  if(input!==L.cmd.commandInp){if(input===3&&pending){const k=pending;pending=undefined;return k.charCodeAt(0);}if(consumed>=950)return undefined;if(phase==='pay'&&/Pay for which items/.test(text)){if(!menuSelected){menuSelected=true;return 97;}return 10;}if(phase==='pay'&&/itemized/i.test(text))return 121;return 32;}
  if(consumed>=900||state.hp<1||dnum!==0)return undefined;
  if(lastLevel!==dlevel){events.push({kind:'level',keyIndex:consumed,dnum,dlevel,moves:state.moves,hp:state.hp});lastLevel=dlevel;}
  if(phase==='pickup'){events.push({kind:'picked-up',keyIndex:consumed,text,hp:state.hp});phase='pay';return 112;}
  if(phase==='pay'){events.push({kind:'paid',keyIndex:consumed,text,hp:state.hp});return undefined;}
  const grid=g.svl+f('instance_globals_saved_l','level'),objects=grid+f('dlevel_t','objects'),blocked=new Set();for(let x=1;x<80;x++)for(let y=0;y<21;y++){let o=ptr(objects+(x*21+y)*8);while(o){if(v.getInt16(o+f('obj','otyp'),true)===475)blocked.add(x+','+y);o=ptr(o+f('obj','v'));}}
  const targets=[],roomBase=g.svr+f('instance_globals_saved_r','rooms');
  for(let i=0;i<40;i++){const room=roomBase+i*R.mkroom.size,rtype=m.HEAPU8[room+f('mkroom','rtype')];if(rtype<14)continue;const lx=v.getInt16(room,true),hx=v.getInt16(room+2,true),ly=v.getInt16(room+4,true),hy=v.getInt16(room+6,true);if(lx<1||hx>=80||ly<0||hy>=21)continue;
   for(let x=lx;x<=hx;x++)for(let y=ly;y<=hy;y++){const obj=ptr(objects+(x*21+y)*8);if(!obj||ptr(obj+f('obj','v')))continue;const cl=m.HEAPU8[obj+f('obj','oclass')];if(![7,8,9].includes(cl))continue;targets.push({x,y,room:i,rtype,otyp:v.getInt16(obj+f('obj','otyp'),true),class:cl});}}
  if(!targets.length){if(dlevel>=4)return undefined;let stairs=ptr(g.gs+f('instance_globals_s','stairs'));while(stairs){if(!m.HEAPU8[stairs+f('stairway','up')]&&v.getInt16(stairs+4,true)===dnum)targets.push({x:v.getInt16(stairs,true),y:v.getInt16(stairs+2,true),stairs:true});stairs=ptr(stairs+f('stairway','next'));}}
  const typ=(x,y)=>m.HEAPU8[grid+f('dlevel_t','locations')+(x*21+y)*R.rm.size+f('rm','typ')],flags=(x,y)=>m.HEAPU8[grid+f('dlevel_t','locations')+(x*21+y)*R.rm.size+f('rm','flags')]&31;
  let route;for(const t of targets){const queue=[[state.x,state.y,'']],seen=new Set([state.x+','+state.y]);for(let i=0;i<queue.length;i++){const[x,y,keys]=queue[i];if(x===t.x&&y===t.y){route={target:t,keys};break;}for(const[dx,dy,key]of[[-1,0,'h'],[1,0,'l'],[0,-1,'k'],[0,1,'j']]){const nx=x+dx,ny=y+dy,id=nx+','+ny;if(nx<1||nx>=80||ny<0||ny>=21||seen.has(id)||blocked.has(id))continue;const type=typ(nx,ny);if(type<23||type>32)continue;seen.add(id);const d=type===23?flags(nx,ny):0;queue.push([nx,ny,keys+((d&8)?'\x04'+key:(d&4)?'o'+key:'')+key]);}}if(route)break;}
  if(!route)return undefined;const pos=dlevel+':'+state.x+','+state.y;if(pos===previous)stalls++;else{previous=pos;stalls=0;}if(stalls>50)return undefined;
  if(!route.keys){if(route.target.stairs)return 62;selected=route.target;events.push({kind:'shop-item',keyIndex:consumed,dnum,dlevel,moves:state.moves,target:selected});phase='pickup';return 44;}
  if(route.keys[0]==='o'||route.keys[0]==='\x04')pending=route.keys[1];return route.keys.charCodeAt(0);
 }});
 const report={seed,profile,status:result.status,phase,selected,consumed:result.consumed,events,keys:result.input.keys};console.log(JSON.stringify(report));if(selected){fs.writeFileSync(out+'/seed'+seed+'-author.json.gz',gzipSync(JSON.stringify({report,result})));if(phase==='pay')break;}
}
