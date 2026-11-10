// Runtime scope only: no source SP_LEV algorithm or data.
const spLevStates=new WeakMap();
export function initializeSpLev(services,layout,namespace){
 let state=spLevStates.get(services.moduleKey);
 if(!state){
  state={services};
  const forwarding=new Proxy(Object.create(null),{get:(_,key)=>Reflect.get(state.services,key,state.services)});
  state.env=createSpLevEnvironment(forwarding,layout,namespace);
  spLevStates.set(services.moduleKey,state);
 }
 return state.env;
}
export function callSpLev(services,layout,namespace,name,...args){
 const env=initializeSpLev(services,layout,namespace),state=spLevStates.get(services.moduleKey),previous=state.services;
 if(typeof namespace[name]!=='function')throw Error('Unknown original SP_LEV function '+name);
 state.services=services;
 try{
  const stack=services.stackSave();
  try{
   const typed=args.map((v,i)=>{const t=schema.sourceParameters[name][i].canonical;return t==='long'?env.i64(v):t==='unsigned long'?env.u64(v):env.ptr(v);});
   const result=withCEnvironment(env,namespace[name],...typed);
   return schema.sourceReturns[name].includes('*')?BigInt(result??0):result;
  }finally{services.stackRestore(stack);}
 }finally{state.services=previous;}
}
