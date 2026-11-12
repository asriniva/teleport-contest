// Read-only active REGION observation for the source-created elemental profiles.
// This supplements, and does not change, the shared strict world scanner.
import fs from 'node:fs';import assert from 'node:assert/strict';
const schema=JSON.parse(fs.readFileSync(new URL('../js/standalone/records.json',import.meta.url))),records=schema.records,L=JSON.parse(fs.readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url))).region;
export function elementalRegions({module,environment}){
 const heap=module?.HEAPU8??environment.memory.HEAPU8,view=new DataView(heap.buffer),globals=new Map(),pointer=p=>Number(view.getBigUint64(p,true)),raw=(p,n)=>Buffer.from(heap.slice(p,p+n)).toString('hex');
 const string=p=>{let end=p;while(end<heap.length&&heap[end])end++;assert.ok(end<heap.length,'terminated region message');return Buffer.from(heap.slice(p,end)).toString('base64');};
 if(module)for(let i=0;i<module._full_global_count();i++){const name=Buffer.from(string(Number(module._full_global_name(i))),'base64').toString();globals.set(name,Number(module._full_global_address(i)));}
 const global=n=>module?(assert.ok(globals.has(n)),globals.get(n)):environment.requireGlobal(n),at=(type,p,k)=>p+records[type].fields[k].offset;
 const count=view.getInt32(at('instance_globals_saved_n',global('svn'),'n_regions'),true),capacity=view.getInt32(at('instance_globals_m',global('gm'),'max_regions'),true),array=pointer(at('instance_globals_r',global('gr'),'regions'));assert.ok(count>=0&&count<=capacity&&capacity<100000);if(count)assert.ok(array);
 const allocations=new Map(),identity=(p,id)=>{if(!p)return null;if(!allocations.has(p))allocations.set(p,id);return allocations.get(p);},regions=[];
 function canonical(t){for(let i=0;schema.aliases[t]&&i<20;i++)t=schema.aliases[t];return t.replace(/\b(const|volatile)\b/g,'').trim();}
 for(let i=0;i<count;i++){const p=pointer(array+8*i);assert.ok(p>0&&p+records.NhRegion.size<=heap.length);const row={identity:identity(p,'region:'+i)},nrects=view.getInt16(at('NhRegion',p,'nrects'),true),nmons=view.getInt16(at('NhRegion',p,'n_monst'),true),maxmons=view.getInt16(at('NhRegion',p,'max_monst'),true);assert.ok(nrects>=0&&nrects<100000&&nmons>=0&&nmons<=maxmons&&maxmons<100000);assert.equal(view.getInt16(at('NhRegion',p,'inside_f'),true),L.INSIDE_GAS_CLOUD,'this profile only supports original gas-cloud active argument');
  for(const[k,f]of Object.entries(records.NhRegion.fields)){const q=p+f.offset,t=canonical(f.ctype.replace(new RegExp('\\s+'+k+'$'),''));
   if(k==='rects'){const start=pointer(q);if(nrects)assert.ok(start);row[k]={allocation:identity(start,'region:'+i+'.rects'),values:Array.from({length:nrects},(_,j)=>raw(start+j*records.nhrect.size,records.nhrect.size))};}
   else if(k==='monsters'){const start=pointer(q);if(nmons)assert.ok(start);row[k]={allocation:identity(start,'region:'+i+'.monsters'),values:Array.from({length:nmons},(_,j)=>view.getUint32(start+4*j,true))};}
   else if(k==='enter_msg'||k==='leave_msg'){const value=pointer(q);row[k]=value?{cstring:string(value)}:null;}
   else if(k==='bounding_box')row[k]=raw(q,records.nhrect.size);
   else if(k==='arg'){assert.equal(records.any.size,8);row[k]={active:'gas-cloud damage int; original create_region zeroany initializes remaining bytes',raw:raw(q,records.any.size)};}
   else{assert.ok(!t.includes('*')&&!t.startsWith('struct ')&&!t.startsWith('union '),'unknown live region field '+k+':'+t);const size=/\bchar\b/.test(t)?1:/\bshort\b/.test(t)?2:/\blong\b/.test(t)?8:4;row[k]=raw(q,size);}
  }regions.push(row);
 }
 return{count,allocatedCapacity:capacity,regions};
}
