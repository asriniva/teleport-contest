import fs from 'node:fs';
import {createStandaloneEnvironment} from '../js/nethack/environment.js';
export const layouts=JSON.parse(fs.readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url)));
export function setupMonsterData(){
 const env=createStandaloneEnvironment({initialBytes:1024,maximumBytes:64*1024*1024});
 env.enableStdio();env.enableDecl(layouts.decl);env.enableDrawing(layouts.drawing);
 env.enableObjects(layouts.objects);env.call('objects','objects_globals_init');
 env.enableMonst(layouts.monst);env.call('monst','monst_globals_init');
 env.enableSerialization(layouts);env.enableRnd(layouts.rnd,{seed:1n});
 env.enableAddressPort('dungeon',{only:['ledger_no','maxledgerno']});
 env.enableObjectState(layouts);env.call('object-state','init_objects');
 env.enableObjectRecords(layouts);env.enableItemInventory(layouts);env.enableTimers(layouts);env.enableItemNaming(layouts);
 const selection=env.enableMonsterSelection(layouts),creation=env.enableMonsterCreation(layouts);
 const entry=env.start('monster-data'),{views}=selection;
 const baseline=(fn,args)=>{
  args[0]=views.record(['attacktype','attacktype_fordmg'].includes(fn)?'struct permonst':'struct monst',args[0]);
  if(fn==='set_mon_data')args[1]=views.record('struct permonst',args[1]);
  return args;
 };
 const p=env.memory.calloc(1,env.ctypes.size('struct monst'));
 const mon=views.record('struct monst',p),species=creation.environment.mons;
 mon.data=species[0];mon.movement=12;
 return {env,entry,baseline,optimized:entry.prepareArgs,views,creation,mon,species};
}
