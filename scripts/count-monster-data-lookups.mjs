import {setupMonsterData} from './monster-data-view-harness.mjs';
const x=setupMonsterData(),{env,entry,mon,species}=x,pm=species[0],L=entry.environment;
const original=env.ctypes.record,counts=new Map();
env.ctypes.record=function(type){const row=counts.get(type)??{calls:0,throws:0};counts.set(type,row);row.calls++;try{return original(type);}catch(error){row.throws++;throw error;}};
for(let i=0;i<1000;i++)switch(i%4){case 0:env.services.set_mon_data(mon,pm);break;case 1:env.services.mon_learns_traps(mon,L.PIT);break;case 2:env.services.attacktype(pm,L.AT_BITE);break;default:env.services.attacktype_fordmg(pm,L.AT_BITE,L.AD_ANY);}
env.ctypes.record=original;
console.log(JSON.stringify({calls:1000,lookups:[...counts].map(([type,count])=>({type,...count})),totalThrows:[...counts.values()].reduce((n,r)=>n+r.throws,0)},null,2));
