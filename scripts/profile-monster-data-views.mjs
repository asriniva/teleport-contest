import fs from 'node:fs';
import inspector from 'node:inspector';
import {setupMonsterData} from './monster-data-view-harness.mjs';
const [mode='optimized',out='.cache/monster-mixed-profile/optimized.cpuprofile']=process.argv.slice(2);
const x=setupMonsterData(),{env,entry,mon,species}=x,pm=species[0],L=entry.environment;
if(mode==='baseline')entry.prepareArgs=x.baseline;
else if(mode!=='optimized')throw Error('Expected baseline or optimized');
function mixed(i){switch(i%4){case 0:return env.services.set_mon_data(mon,pm);case 1:return env.services.mon_learns_traps(mon,L.PIT);case 2:return env.services.attacktype(pm,L.AT_BITE);default:return env.services.attacktype_fordmg(pm,L.AT_BITE,L.AD_ANY);}}
let sink=0;function run(count){for(let i=0;i<count;i++){const v=mixed(i);sink=(sink+Number(v?.address??v??0))|0;}}
run(10000);
const session=new inspector.Session();session.connect();
const post=(name,args={})=>new Promise((resolve,reject)=>session.post(name,args,(err,result)=>err?reject(err):resolve(result)));
await post('Profiler.enable');await post('Profiler.setSamplingInterval',{interval:1000});await post('Profiler.start');
run(Number(process.env.PROFILE_ITERATIONS??100000));
const {profile}=await post('Profiler.stop');session.disconnect();fs.writeFileSync(out,JSON.stringify(profile));
const byId=new Map(profile.nodes.map(n=>[n.id,n])),self=new Map(),inclusive=new Map(),parent=new Map();
for(const n of profile.nodes)for(const child of n.children??[])parent.set(child,n.id);
function key(n){const f=n.callFrame;return `${f.functionName||'(anonymous)'} ${f.url.split('/').slice(-2).join('/')}:${f.lineNumber+1}`;}
let total=0;
for(let i=0;i<profile.samples.length;i++){
 const id=profile.samples[i],weight=profile.timeDeltas[i];total+=weight;const k=key(byId.get(id));self.set(k,(self.get(k)??0)+weight);
 let cursor=id;const seen=new Set();while(cursor){const k=key(byId.get(cursor));if(!seen.has(k)){inclusive.set(k,(inclusive.get(k)??0)+weight);seen.add(k);}cursor=parent.get(cursor);}
}
const top=map=>[...map].sort((a,b)=>b[1]-a[1]).slice(0,25).map(([functionLocation,us])=>({functionLocation,percent:100*us/total}));
console.log(JSON.stringify({mode,sink,samples:profile.samples.length,profileMs:total/1000,self:top(self),inclusive:top(inclusive)},null,2));
