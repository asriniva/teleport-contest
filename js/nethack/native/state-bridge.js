// One per-game native field owner. Legacy byte-level services are explicit
// synchronization boundaries; native-to-native field access stays in JS.
export class NativeStateBridge {
 constructor() { this.sharedTypes=new Set(['struct you','struct prop','struct d_level','struct u_roleplay','struct u_conduct','struct monst','struct permonst','struct obj','struct rm','struct nhcoord','struct attack','struct mfndposdata','struct mextra','struct edog','struct eshk','struct epri','struct emin','struct egd','struct ebones','struct trap']);this.providers=[];this.schemaVersion=0;this.enriched=new WeakMap();this.depth=0; this.epoch=0; this.dirty=new Set(); this.fields=0; this.hits=0; this.boundaries=0; }
 registerSchemas(provider) {this.providers.push(provider);this.schemaVersion++;}
 enrich(record,type,address) {
  if(this.enriched.get(record)===this.schemaVersion)return;
  this.enriched.set(record,this.schemaVersion);
  for(const provider of this.providers)provider.get(type)?.(address);
 }
 field(read,write,normalize=v=>v) {
  const owner=this;
  const cell={epoch:-1,value:undefined,read,write};this.fields++;
  return {enumerable:true,get(){
   if(!owner.depth)return read();
   if(cell.epoch!==owner.epoch){cell.value=read();cell.epoch=owner.epoch;}else owner.hits++;
   return cell.value;
  },set(value){if(!owner.depth){write(normalize(value));owner.invalidate();return;}cell.value=normalize(value);cell.epoch=owner.epoch;owner.dirty.add(cell);}};
 }
 flush() {for(const cell of this.dirty)cell.write(cell.value);this.dirty.clear();}
 invalidate() {this.epoch++;}
 boundary(fn,...args) {
  this.flush();this.boundaries++;const depth=this.depth;this.depth=0;
  try {return fn(...args);}finally {this.depth=depth;this.invalidate();}
 }
 enter() {if(!this.depth){this.flush();this.invalidate();}this.depth++;}
 leave() {this.depth--;if(!this.depth){this.flush();this.invalidate();}}
}

// Native providers in one game share identities and their synchronization owner.
const games=new WeakMap();
export function nativeStateFor(moduleKey) {
 let state=games.get(moduleKey);
 if(!state){state=new NativeStateBridge();state.records=new Map();state.functions=new Map();games.set(moduleKey,state);}
 return state;
}
