// Pure test collector; imported separately so instrumentation semantics are testable.
export function createCollector({enabled=true}={}){
 let referenceDepth=0;
 const files=new Map(),bucket=file=>{if(!files.has(file))files.set(file,{siteKeys:[],sourceSha256:null,counts:[],capabilities:['optional-call','sync-iterator','switch-no-match','parameter-default-bounds','local-default-bounds','logical-assignment','for-in']});return files.get(file);};
 const hit=(file,id,arm)=>{if(enabled&&!referenceDepth){const b=bucket(file);b.counts[id]??=[];b.counts[id][arm]=(b.counts[id][arm]??0)+1;}};
 const methods={files,
  reference(fn){referenceDepth++;try{return fn();}finally{referenceDepth--;}},
  complete(file,ids){if(enabled&&!referenceDepth){const row=bucket(file);row.completions??=[];for(const id of ids)row.completions[id]=(row.completions[id]??0)+1;}},
  register(file,siteKeys,sourceSha256,options){if(enabled){const b=bucket(file);b.siteKeys=siteKeys;b.sourceSha256=sourceSha256;b.defaultTracking=options?.defaultTracking===true;}},hit,
  decision(file,id,operator,value){let taken;if(operator==='??')taken=value===null||value===undefined;else if(operator==='||')taken=!value;else if(operator==='nonnull')taken=value!==null&&value!==undefined;else taken=Boolean(value);hit(file,id,taken?0:1);return value;},
  logicalReceiver(file,id,operator,value){
   if(!enabled||value==null)return value;
   return new Proxy(Object.create(null),{
    get(_target,key){return methods.decision(file,id,operator,Reflect.get(Object(value),key,value));},
    set(_target,key,item){return Reflect.set(Object(value),key,item,value);},
   });
  },
  iterationBody(file,id,token){token.seen=true;hit(file,id,0);},
  iterationEnd(file,id,token){if(!token.seen)hit(file,id,1);},
  optionalValue(file,id,value){hit(file,id,value==null?1:0);return value;},
  optionalReceiver(file,id,value){
   if(!enabled||value==null)return value;
   return new Proxy(Object.create(null),{get(_target,key){const member=Reflect.get(Object(value),key,value);hit(file,id,member==null?1:0);return typeof member==='function'?new Proxy(member,{apply(fn,_this,args){return Reflect.apply(fn,value,args);}}):member;}});
  },
  iterable(file,id,value){
   if(!enabled||value==null)return value;
   const method=value[Symbol.iterator];if(typeof method!=='function')return{[Symbol.iterator]:method};
   return{[Symbol.iterator](){
    const iterator=Reflect.apply(method,value,[]);if(iterator===null||!['object','function'].includes(typeof iterator))return iterator;
    const next=iterator.next;
    return{
     next(...args){const result=Reflect.apply(next,iterator,args);if(result===null||!['object','function'].includes(typeof result))return result;return new Proxy(Object.create(null),{get(_target,key){const item=Reflect.get(result,key,result);if(key==='done')hit(file,id,item?1:0);return item;}});},
     return(...args){const close=iterator.return;if(close==null)return{done:true};return Reflect.apply(close,iterator,args);},
    };
   }};
  },
  beginSwitch(file,id,total){return{file,id,total,visited:0,active:false,matched:false};},
  switchValue(token,value){if(token){token.value=value;token.active=true;}return value;},
  caseValue(token,value){if(token){token.visited++;if(value===token.value)token.matched=true;}return value;},
  endSwitch(token){if(token?.active&&!token.matched&&token.visited===token.total)hit(token.file,token.id,0);},
 };
 return methods;
}
