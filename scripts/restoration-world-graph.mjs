// Test-only canonical graph: pointer bytes become checked target identities, never presence bits.
// $normalizedBytes preserves named scalar bits; measured padding and already-resolved
// pointer bytes are zero. The adjacent fields/edge list preserve the full pointer graph.
// Immutable permonst literal strings compare by contents (native compiler may merge them).
// Unknown nonempty pointer/union/callback cases fail explicitly; this is not a heap scanner.
import fs from 'node:fs';
import assert from 'node:assert/strict';
const schema=JSON.parse(fs.readFileSync(new URL('../js/standalone/records.json',import.meta.url)));
const records=schema.records;
function resolve(type){type=type.replace(/\b(const|volatile)\b/g,'').trim().replace(/\s+/g,' ');for(let i=0;schema.aliases[type]&&i<20;i++)type=schema.aliases[type];return type;}
const primitive=type=>/\*/.test(type)?8:/\b(char|_Bool)\b/.test(type)?1:/\bshort\b/.test(type)?2:/\b(long|double)\b/.test(type)?8:4;
export function worldGraph({module,environment}){
 const heap=module?.HEAPU8??environment.memory.HEAPU8,view=new DataView(heap.buffer,heap.byteOffset,heap.byteLength),globals=new Map();
 const str=p=>{let e=p;while(e<heap.length&&heap[e])e++;assert.ok(e<heap.length,'terminated string');return Buffer.from(heap.slice(p,e)).toString('base64');};
 if(module)for(let i=0;i<module._full_global_count();i++)globals.set(Buffer.from(str(Number(module._full_global_name(i))),'base64').toString(),Number(module._full_global_address(i)));
 const global=name=>module?(assert.ok(globals.has(name),'C global '+name),globals.get(name)):environment.requireGlobal(name);
 const ptr=p=>Number(view.getBigUint64(p,true));
 const addressIds=new Map(),idAddresses=new Map(),nodes={},counts={},pointerEdges=[];let bytes=0,padding=0,speciesBase;const scalarMasks=new Map();
 function bind(at,id){if(addressIds.has(at))assert.equal(addressIds.get(at),id,'address identity');if(idAddresses.has(id))assert.equal(idAddresses.get(id),at,'unique '+id);addressIds.set(at,id);idAddresses.set(id,at);}
 function field(at,record,name){return at+records[record].fields[name].offset;}
 const roomAt=global('svr')+records.instance_globals_saved_r.fields.rooms.offset;
 for(let i=0;i<82;i++)bind(roomAt+i*records.mkroom.size,'room:'+i);
 const hero=global('gy')+records.instance_globals_y.fields.youmonst.offset;bind(hero,'hero-monster');
 function target(at,type,path){if(!at)return null;assert.ok(at>0&&at<heap.length,'pointer in heap '+path);
  type=resolve(type);const match=type.match(/^(?:struct|union) (\w+)$/);let id;
  if(match){const rec=match[1];assert.ok(records[rec],'measured pointee '+type);
   if(rec==='obj')id='obj:'+view.getUint32(field(at,rec,'o_id'),true);
   else if(rec==='monst')id=at===hero?'hero-monster':'mon:'+view.getUint32(field(at,rec,'m_id'),true);
   else if(rec==='permonst'){const index=view.getInt32(field(at,rec,'pmidx'),true),base=at-index*records.permonst.size;speciesBase??=base;assert.equal(base,speciesBase,'all species references belong to one measured table');id='species:'+index;}
   else id=addressIds.get(at)??path;
   bind(at,id);if(!(id in nodes)){nodes[id]=null;counts[rec]=(counts[rec]??0)+1;nodes[id]=record(at,rec,id);}
  }else if(type==='char'||type==='signed char'||type==='unsigned char'){
   // C may merge immutable species literals; their target contract is content.
   if(path.startsWith('species:'))return {literal:str(at)};
   id=addressIds.get(at)??path;bind(at,id);nodes[id]??={string:str(at)};
  }else throw new Error('Unsupported non-null pointee '+type+' at '+path);
  pointerEdges.push([path,id]);return {$ref:id};
 }
 function typed(at,type,path,owner){
  type=resolve(type);const dims=[...type.matchAll(/\[(\d+)\]/g)].map(x=>+x[1]);if(dims.length){const base=type.replace(/\[\d+\]/g,'').trim(),n=dims.reduce((a,b)=>a*b,1),size=sizeOf(base);return Array.from({length:n},(_,i)=>typed(at+i*size,base,path+'['+i+']',owner));}
  if(type.includes('(*')){assert.equal(ptr(at),0,'non-null callback requires source identity '+path);return null;}
  if(path==='svd.doors'||path==='svo.oracle_loc'){const p=ptr(at);if(!p)return null;const count=path==='svd.doors'?view.getInt32(global('svd')+records.instance_globals_saved_d.fields.doors_alloc.offset,true):view.getUint32(global('svo')+records.instance_globals_saved_o.fields.oracle_cnt.offset,true);assert.ok(count>=0&&count<100000,'bounded source array count');bind(p,path);nodes[path]=Array.from({length:count},(_,i)=>typed(p+i*sizeOf(type.slice(0,-1)),type.slice(0,-1).trim(),path+'['+i+']'));pointerEdges.push([path,path]);return {$ref:path};}
  if(path.endsWith('.bill_p')&&type.endsWith('*')){const base=owner+records.eshk.fields.bill.offset,delta=ptr(at)-base;if(!ptr(at))return null;assert.ok(delta>=0&&delta<200*records.bill_x.size&&delta%records.bill_x.size===0,'bill_p points inside owning shop bill array');const id=path.slice(0,-7)+'.bill['+(delta/records.bill_x.size)+']';pointerEdges.push([path,id]);return {$interior:id};}
  if(type.endsWith('*'))return target(ptr(at),type.slice(0,-1).trim(),path);
  const match=type.match(/^(?:struct|union) (\w+)$/);if(match)return record(at,match[1],path,owner);
  for(let i=0;i<primitive(type);i++)scalarMasks.set(at+i,255);return Buffer.from(heap.slice(at,at+primitive(type))).toString('hex');
 }
 function sizeOf(type){type=resolve(type);if(type.includes('*'))return 8;const m=type.match(/^(?:struct|union) (\w+)$/);return m?records[m[1]].size:primitive(type);}
 function record(at,name,path,owner){const r=records[name];assert.ok(r,'record '+name);assert.ok(at+r.size<=heap.length,'record bounds '+path);
  if(name==='vptrs'){
   const where=view.getInt8(owner+records.obj.fields.where.offset);const pointee=where===1||where===2?'struct obj':where===4?'struct monst':null;
   if(pointee)return {active:where,target:target(ptr(at),pointee,path)};
   assert.equal(ptr(at),0,'inactive object union must be zero '+path);return {inactive:where,raw:'0000000000000000'};
  }
  if(name==='any'){
   let pointee;if(path.endsWith('.id')){const kind=view.getInt16(owner+records.ls_t.fields.type.offset,true);pointee=kind===1?'struct obj':kind===2?'struct monst':null;}
   if(path.endsWith('.arg')){const kind=view.getInt16(owner+records.fe.fields.kind.offset,true);pointee=kind===3?'struct obj':kind===4?'struct monst':null;}
   if(pointee)return target(ptr(at),pointee,path);assert.equal(ptr(at),0,'unsupported nonempty union '+path);return {zero:true};
  }
  // Other measured unions in world records have only scalar alternatives.
  if(name==='vlaunchinfo'){for(let i=0;i<r.size;i++)scalarMasks.set(at+i,255);return {raw:Buffer.from(heap.slice(at,at+r.size)).toString('hex')};}
  const out={},covered=new Uint8Array(r.size);
  for(const [key,f]of Object.entries(r.fields)){
   const p=at+f.offset,ft=f.ctype.replace(new RegExp('\\b'+key+'$'),'').trim(),t=resolve(ft);
   if(f.bits!==undefined){const n=Math.ceil((f.shift+f.bits)/8);let value=0n;for(let i=0;i<n;i++){value|=BigInt(heap[p+i])<<BigInt(i*8);covered[f.offset+i]|=Number(((1n<<BigInt(f.bits))-1n)<<BigInt(f.shift)>>BigInt(i*8))&255;}for(let i=0;i<n;i++)scalarMasks.set(p+i,(scalarMasks.get(p+i)??0)|covered[f.offset+i]);out[key]=String((value>>BigInt(f.shift))&((1n<<BigInt(f.bits))-1n));}
   else {const dims=[...t.matchAll(/\[(\d+)\]/g)].map(x=>+x[1]),n=dims.reduce((a,b)=>a*b,1)*sizeOf(t.replace(/\[\d+\]/g,''));for(let i=0;i<n;i++)covered[f.offset+i]=255;out[key]=typed(p,t,path+'.'+key,at);}
  }
  bytes+=r.size;padding+=covered.reduce((n,v)=>n+(v===0),0);out.$normalizedBytes=Buffer.from(Array.from({length:r.size},(_,i)=>heap[at+i]&(scalarMasks.get(at+i)??0))).toString('hex');return out;
 }
 const roots={};const root=(name,type)=>roots[name]=record(global(name),type,name);
 root('u','you');root('flags','flag');roots.youmonst=target(hero,'struct monst','youmonst');
 for(const type of Object.keys(records).filter(n=>n.startsWith('instance_globals_saved_')))root('sv'+type.slice(-1),type);
 for(const [g,rec,key]of [['gi','instance_globals_i','invent'],['gm','instance_globals_m','migrating_objs'],['gm','instance_globals_m','mydogs'],['gm','instance_globals_m','migrating_mons'],['gl','instance_globals_l','light_base'],['gt','instance_globals_t','timer_base'],['gf','instance_globals_f','ftrap'],['gs','instance_globals_s','stairs']]){
  const f=records[rec].fields[key];roots[g+'.'+key]=typed(global(g)+f.offset,f.ctype.replace(new RegExp('\\b'+key+'$'),'').trim(),g+'.'+key);
 }
 roots.head_engr=target(ptr(global('head_engr')),'struct engr','head_engr');
 for(const name of ['uwep','uswapwep','uquiver','uarm','uarmc','uarmh','uarms','uarmg','uarmf','uarmu','uleft','uright','uamul','ublindf','uball','uchain'])roots[name]=target(ptr(global(name)),'struct obj',name);
 return {roots,nodes:Object.fromEntries(Object.entries(nodes).sort(([a],[b])=>a.localeCompare(b))),coverage:{counts,serializedRecordBytes:bytes,serializedPaddingByteOccurrences:padding,uniqueScalarBytes:scalarMasks.size,pointerEdges:pointerEdges.length},pointerEdges};
}
