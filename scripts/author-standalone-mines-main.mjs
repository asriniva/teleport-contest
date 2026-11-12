import {gzipSync} from 'node:zlib';
// Development-only original-C route author; read-only world observations and keyboard input.
import fs from 'node:fs';import {runFullOriginalC} from './full-original-c-run.mjs';
const R=JSON.parse(fs.readFileSync('js/standalone/records.json')).records,L=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json'));const out='.cache/mines-author';fs.mkdirSync(out,{recursive:true});
const base={timezone:'UTC',options:'OPTIONS=!news,autopickup\n',argv:['-u','Ada-male-lawful','-p','Samurai','-r','human']};
for(let seed=Number(process.env.FIRST_SEED??3);seed<=Number(process.env.LAST_SEED??3);seed++){
 let g,pending,branch=false,lastLevel,stalls=0,lastPos='';const events=[];
 const result=await runFullOriginalC('.cache/full-original-c-v1',{...base,seed,maxInputBoundaries:1200,authorKey({module:m,state,frame,consumed}){
  if(consumed<3)return '  n'.charCodeAt(consumed);
  if(!g){g={};for(let i=0;i<m._full_global_count();i++){let p=Number(m._full_global_name(i)),e=p;while(m.HEAPU8[e])e++;g[Buffer.from(m.HEAPU8.slice(p,e)).toString()]=Number(m._full_global_address(i));}}
  const v=new DataView(m.HEAPU8.buffer),f=(t,n)=>R[t].fields[n].offset,level=g.u+f('you','uz'),dnum=v.getInt16(level,true),dlevel=v.getInt16(level+2,true),input=v.getInt32(g.program_state+f('sinfo','input_state'),true);
  if(input!==L.cmd.commandInp){if(input===3&&pending){const k=pending;pending=undefined;return k.charCodeAt(0);}if(consumed>=1150)return undefined;return 32;}
  if(lastLevel!==dnum+':'+dlevel){events.push({keyIndex:consumed,moves:state.moves,dnum,dlevel,x:state.x,y:state.y,hp:state.hp});lastLevel=dnum+':'+dlevel;}
  if(dnum!==0){branch=true;if(dlevel>=3)return undefined;}if(consumed>=1100||state.hp<1)return undefined;
  let stairs=Number(v.getBigUint64(g.gs+f('instance_globals_s','stairs'),true));const targets=[];
  while(stairs){if(!m.HEAPU8[stairs+f('stairway','up')])targets.push({x:v.getInt16(stairs,true),y:v.getInt16(stairs+2,true),dnum:v.getInt16(stairs+4,true),dlevel:v.getInt16(stairs+6,true)});stairs=Number(v.getBigUint64(stairs+f('stairway','next'),true));}
  targets.sort((a,b)=>(a.dnum===dnum)-(b.dnum===dnum));
  const map=g.svl+f('instance_globals_saved_l','level')+f('dlevel_t','locations'),typ=(x,y)=>m.HEAPU8[map+(x*21+y)*R.rm.size+f('rm','typ')],flags=(x,y)=>m.HEAPU8[map+(x*21+y)*R.rm.size+f('rm','flags')]&31;
  const blocked=new Set();const grid=g.svl+f("instance_globals_saved_l","level")+f("dlevel_t","objects");for(let x=1;x<80;x++)for(let y=0;y<21;y++){let o=Number(v.getBigUint64(grid+(x*21+y)*8,true));while(o){if(v.getInt16(o+f("obj","otyp"),true)===475)blocked.add(x+","+y);o=Number(v.getBigUint64(o+f("obj","v"),true));}}
  let route;
  for(const target of targets){const queue=[[state.x,state.y,'']],seen=new Set([state.x+','+state.y]);for(let i=0;i<queue.length;i++){const[x,y,keys]=queue[i];if(x===target.x&&y===target.y){route={target,keys};break;}for(const[dx,dy,key]of[[-1,0,'h'],[1,0,'l'],[0,-1,'k'],[0,1,'j']]){const nx=x+dx,ny=y+dy,id=nx+','+ny;if(nx<1||nx>=80||ny<0||ny>=21||seen.has(id)||blocked.has(id))continue;const t=typ(nx,ny);if(t<23||t>32)continue;seen.add(id);const door=t===23?flags(nx,ny):0;queue.push([nx,ny,keys+((door&8)?'\x04'+key:(door&4)?'o'+key:'')+key]);}}if(route)break;}
  if(!route)return undefined;const pos=dnum+':'+dlevel+':'+state.x+','+state.y;if(pos===lastPos)stalls++;else{lastPos=pos;stalls=0;}if(stalls>70)return undefined;
  if(!route.keys)return 62;if(route.keys[0]==='o'||route.keys[0]==='\x04')pending=route.keys[1];return route.keys.charCodeAt(0);
 }});
 const report={seed,branch,status:result.status,consumed:result.consumed,events,keys:result.input.keys};console.log(JSON.stringify(report));fs.writeFileSync(out+'/seed'+seed+'-author.json.gz',gzipSync(JSON.stringify({report,result},null,2)+'\n'));if(branch)break;
}
