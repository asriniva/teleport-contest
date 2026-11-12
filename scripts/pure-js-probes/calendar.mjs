import {environment,probeModule} from './common.mjs';
export default async function createCalendarProbe(_layouts,{now}={}){
 const env=await environment(now?{now}:{}),methods={_probe_set_env(name,value){env.setEnvironment(env.memory.readString(Number(name)),Number(value)?env.memory.readString(Number(value)):null);return 0;}};
 for(const[op,fn]of Object.entries({now:'getnow',year:'getyear',date:'yyyymmdd',time:'hhmmss',format:'yyyymmddhhmmss',parse:'time_from_yyyymmddhhmmss',moon:'phase_of_the_moon',friday:'friday_13th',night:'night',midnight:'midnight'}))methods['_probe_'+op]=(...args)=>{const result=env.calendar(fn,...args.map(a=>op==='parse'?Number(a):a));return ['format','date','time'].includes(op)?BigInt(result):result;};
 return probeModule(env,methods);
}
