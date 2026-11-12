// Ordinary combat, rest and food decisions author keyboard replay only. No state writes.
import {gzipSync} from 'node:zlib';
// Development-only original-C route author; read-only world observations and keyboard input.
import fs from 'node:fs';import {runFullOriginalC} from './full-original-c-run.mjs';
const R=JSON.parse(fs.readFileSync('js/nethack/records.json')).records,L=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json'));const out='.cache/ordinary-progression-author';fs.mkdirSync(out,{recursive:true});
const base={timezone:'UTC',options:'OPTIONS=!news,autopickup\n',argv:['-u','Ada-male-lawful','-p','Samurai','-r','human']};
for(let seed=Number(process.env.FIRST_SEED??3);seed<=Number(process.env.LAST_SEED??3);seed++){
 let g,pending,food,branch=false,lastLevel,stalls=0,lastPos='',resting=false;const events=[];const actions={attack:0,rest:0,eat:0};
 const result=await runFullOriginalC('.cache/full-original-c-v1',{...base,seed,maxInputBoundaries:3200,authorKey({module:m,state,frame,consumed}){
  if(consumed<3)return '  n'.charCodeAt(consumed);
  if(!g){g={};for(let i=0;i<m._full_global_count();i++){let p=Number(m._full_global_name(i)),e=p;while(m.HEAPU8[e])e++;g[Buffer.from(m.HEAPU8.slice(p,e)).toString()]=Number(m._full_global_address(i));}}
  const v=new DataView(m.HEAPU8.buffer),f=(t,n)=>R[t].fields[n].offset,level=g.u+f('you','uz'),dnum=v.getInt16(level,true),dlevel=v.getInt16(level+2,true),input=v.getInt32(g.program_state+f('sinfo','input_state'),true);
  if(input!==L.cmd.commandInp){if(input===3&&pending){const k=pending;pending=undefined;return k.charCodeAt(0);}if(food&&/What do you want to eat/.test(frame?.screen??'')){const k=food;food=undefined;return k;}if(consumed>=3100)return undefined;return 32;}
  if(lastLevel!==dnum+':'+dlevel){events.push({keyIndex:consumed,moves:state.moves,dnum,dlevel,x:state.x,y:state.y,hp:state.hp});lastLevel=dnum+':'+dlevel;}
  if(dnum!==0){branch=true;const levels=v.getInt16(g.svd+f("instance_globals_saved_d","dungeons")+dnum*R.dungeon.size+f("dungeon","num_dunlevs"),true);if(dlevel>=Number(process.env.ORDINARY_MINES_TARGET??levels))return undefined;}if(consumed>=3000||state.hp<1)return undefined;
  const levelBase=g.svl+f('instance_globals_saved_l','level'),hostiles=[],peaceful=[];let mon=Number(v.getBigUint64(levelBase+f('dlevel_t','monlist'),true));
  while(mon){const x=v.getInt16(mon+f('monst','mx'),true),y=v.getInt16(mon+f('monst','my'),true),hp=v.getInt32(mon+f('monst','mhp'),true),tame=v.getInt8(mon+f('monst','mtame')),d=R.monst.fields.mpeaceful,isPeaceful=(m.HEAPU8[mon+d.offset]>>d.shift)&1;if(hp>0&&x>0&&y>=0){if(!isPeaceful&&!tame)hostiles.push({x,y,hp});else if(!tame)peaceful.push([x,y]);}mon=Number(v.getBigUint64(mon+f('monst','nmon'),true));}
  const adjacent=hostiles.find(p=>Math.max(Math.abs(p.x-state.x),Math.abs(p.y-state.y))===1),directions={'-1,-1':'y','0,-1':'k','1,-1':'u','-1,0':'h','1,0':'l','-1,1':'b','0,1':'j','1,1':'n'};
  if(adjacent){actions.attack++;return directions[(adjacent.x-state.x)+','+(adjacent.y-state.y)].charCodeAt(0);}
  const hunger=v.getInt32(g.u+f('you','uhunger'),true),maxhp=v.getInt32(g.u+f('you','uhpmax'),true);
  if(hunger<300){let o=Number(v.getBigUint64(g.gi+f('instance_globals_i','invent'),true));while(o){if(m.HEAPU8[o+f('obj','oclass')]===7){food=m.HEAPU8[o+f('obj','invlet')];break;}o=Number(v.getBigUint64(o+f('obj','nobj'),true));}if(food){actions.eat++;return 101;}}
  if(state.hp<maxhp){actions.rest++;if(!resting){events.push({kind:'rest',keyIndex:consumed,moves:state.moves,hp:state.hp,maxhp,hunger});resting=true;}return 46;}resting=false;
  let stairs=Number(v.getBigUint64(g.gs+f('instance_globals_s','stairs'),true));const targets=[];
  while(stairs){if(!m.HEAPU8[stairs+f('stairway','up')])targets.push({x:v.getInt16(stairs,true),y:v.getInt16(stairs+2,true),dnum:v.getInt16(stairs+4,true),dlevel:v.getInt16(stairs+6,true)});stairs=Number(v.getBigUint64(stairs+f('stairway','next'),true));}
  targets.sort((a,b)=>(a.dnum===dnum)-(b.dnum===dnum));
  const map=g.svl+f('instance_globals_saved_l','level')+f('dlevel_t','locations'),typ=(x,y)=>m.HEAPU8[map+(x*21+y)*R.rm.size+f('rm','typ')],flags=(x,y)=>m.HEAPU8[map+(x*21+y)*R.rm.size+f('rm','flags')]&31;
  const boulders=new Set(),blocked=new Set(peaceful.map(p=>p.join(',')));const grid=g.svl+f("instance_globals_saved_l","level")+f("dlevel_t","objects");for(let x=1;x<80;x++)for(let y=0;y<21;y++){let o=Number(v.getBigUint64(grid+(x*21+y)*8,true));while(o){if(v.getInt16(o+f("obj","otyp"),true)===475){blocked.add(x+","+y);boulders.add(x+","+y);}o=Number(v.getBigUint64(o+f("obj","v"),true));}}
  let route;
  for(const obstacles of [blocked,boulders]){for(const target of targets){const queue=[[state.x,state.y,'']],seen=new Set([state.x+','+state.y]);for(let i=0;i<queue.length;i++){const[x,y,keys]=queue[i];if(x===target.x&&y===target.y){route={target,keys};break;}for(const[dx,dy,key]of[[-1,0,'h'],[1,0,'l'],[0,-1,'k'],[0,1,'j']]){const nx=x+dx,ny=y+dy,id=nx+','+ny;if(nx<1||nx>=80||ny<0||ny>=21||seen.has(id)||obstacles.has(id))continue;const t=typ(nx,ny);if(t<23||t>32)continue;seen.add(id);const door=t===23?flags(nx,ny):0;queue.push([nx,ny,keys+((door&8)?'\x04'+key:(door&4)?'o'+key:'')+key]);}}if(route)break;}if(route)break;}
  if(!route){events.push({kind:'no-route',keyIndex:consumed,targets,peaceful,blocked:[...blocked]});return undefined;}const pos=dnum+':'+dlevel+':'+state.x+','+state.y;if(pos===lastPos)stalls++;else{lastPos=pos;stalls=0;}if(stalls>70)return undefined;
  const move=Object.entries(directions).find(([,key])=>key===route.keys[0]);if(move){const [dx,dy]=move[0].split(',').map(Number);if(peaceful.some(([x,y])=>x===state.x+dx&&y===state.y+dy)){actions.rest++;return 46;}}
  if(!route.keys)return 62;if(route.keys[0]==='o'||route.keys[0]==='\x04')pending=route.keys[1];return route.keys.charCodeAt(0);
 }});
 const report={seed,branch,actions,status:result.status,consumed:result.consumed,events,keys:result.input.keys};console.log(JSON.stringify(report));fs.writeFileSync(out+'/seed'+seed+'-author.json.gz',gzipSync(JSON.stringify({report,result},null,2)+'\n'));if(branch)break;
}
