// Read-only test observations; no source policy calls or game-memory writes.
import assert from 'node:assert/strict';
import {worldGraph} from './restoration-world-graph.mjs';
export function attachWizardVictoryObserver(runtime,layouts,records){
 const{module,environment}=runtime,heap=()=>module?.HEAPU8??environment.memory.HEAPU8,view=()=>new DataView(heap().buffer),roots={};
 if(module)for(let i=0;i<module._full_global_count();i++){let p=Number(module._full_global_name(i)),end=p;while(heap()[end])end++;roots[Buffer.from(heap().slice(p,end)).toString()]=Number(module._full_global_address(i));}
 const global=n=>module?roots[n]:environment.requireGlobal(n),at=(t,p,k)=>p+records[t].fields[k].offset,bit=(t,p,k)=>{const f=records[t].fields[k];return(view().getUint32(p+f.offset,true)>>>f.shift)&((1<<f.bits)-1);};
 function state(){const v=view(),u=global('u'),uz=at('you',u,'uz');return{termGone:v.getInt8(at('instance_flags',global('iflags'),'term_gone')),readDepth:v.getInt32(at('sinfo',global('program_state'),'getting_char'),true),gameover:v.getInt32(at('sinfo',global('program_state'),'gameover'),true),wizard:v.getInt8(at('flag',global('flags'),'debug')),inputState:v.getInt32(at('sinfo',global('program_state'),'input_state'),true),moves:String(v.getBigInt64(at('instance_globals_saved_m',global('svm'),'moves'),true)),position:[v.getInt16(at('you',u,'ux'),true),v.getInt16(at('you',u,'uy'),true)],level:[v.getInt16(at('d_level',uz,'dnum'),true),v.getInt16(at('d_level',uz,'dlevel'),true)],amulet:bit('u_have',at('you',u,'uhave'),'amulet'),ascended:bit('u_event',at('you',u,'uevent'),'ascended')};}
 const hostReads=[],rawReads=[],waypoints=[],seen=new Set();let victoryLive;
 function beforeKey(){
  const row=state();assert.equal(row.termGone,0,'actual MAIN terminal remains connected');assert.equal(row.readDepth,1,'natural MAIN keyboard depth one');assert.equal(row.wizard,1,'source argv-D wizard flag');hostReads.push(row);
  if(row.ascended&&!row.gameover&&!victoryLive){const v=view(),inventory=[];for(let p=Number(v.getBigUint64(at('instance_globals_i',global('gi'),'invent'),true));p;p=Number(v.getBigUint64(at('obj',p,'nobj'),true)))inventory.push({id:v.getUint32(at('obj',p,'o_id'),true),type:v.getInt16(at('obj',p,'otyp'),true)});victoryLive={...row,inventory};}
  if(row.inputState===layouts.cmd.commandInp&&!row.gameover){const id=row.level.join(':')+':'+row.amulet;if(!seen.has(id)){seen.add(id);waypoints.push({state:row,world:worldGraph(runtime)});}}
 }
 if(module){
  const read=module.teleportReadKey;module.teleportReadKey=()=>{beforeKey();return read();};const tty=module.FS.getStream(0).tty,get=tty.ops.get_char;tty.ops={...tty.ops,get_char(t){const value=get(t);rawReads.push({value:value??null,state:state()});return value;}};
 }else{
  const boundary=environment.start('terminal-key-input'),read=boundary.namespace.teleport_getch;boundary.namespace.teleport_getch=()=>{beforeKey();return read();};const readFd=environment.services.read;environment.services.read=(fd,p,n)=>{const count=readFd(fd,p,n);if(Number(fd)===0)rawReads.push({requested:Number(n),count:Number(count),bytes:[...heap().slice(Number(p),Number(p)+Math.max(0,Number(count)))],state:state()});return count;};
 }
 return{observations:()=>({hostReads,rawReads,waypoints,victoryLive}),final:()=>{const row=state(),u=global('u');return{...row,score:String(view().getBigInt64(at('you',u,'urexp'),true)),achievements:[...heap().slice(at('you',u,'uachieved'),at('you',u,'uachieved')+32)]};}};
}
