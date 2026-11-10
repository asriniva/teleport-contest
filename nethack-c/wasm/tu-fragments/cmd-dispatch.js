// Runtime scope only: no source CMD algorithm or data.
const cmdStates=new WeakMap();
export function initializeCmd(services,layout,namespace){
 let state=cmdStates.get(services.moduleKey);
 if(!state){
  state={services};
  const forwarding=new Proxy(Object.create(null),{get:(_,key)=>Reflect.get(state.services,key,state.services)});
  state.env=createCmdEnvironment(forwarding,layout,namespace);
  cmdStates.set(services.moduleKey,state);
 }
 return state.env;
}
export function callCmd(services,layout,namespace,name,...args){
 const env=initializeCmd(services,layout,namespace),state=cmdStates.get(services.moduleKey),previous=state.services;
 if(typeof namespace[name]!=='function')throw Error('Unknown original CMD function '+name);
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
