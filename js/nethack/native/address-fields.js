// Native field operations used by the generated address-engine kernels.
// Public byte-level transports remain available for lvalue carriers/ABI callbacks.
export function createNativeAddressFields(env,services,schema,decode,convert=env.ptr) {
 const readers=[],writers=[],addresses=[],nativeScalars=new Set(['char','signed char','unsigned char','short','unsigned short','int','unsigned int','unsigned','long','unsigned long','long long','unsigned long long']);
 Object.values(schema.schema).forEach((row,kind)=>row.fields.forEach((field,index)=>{
  const id=readers.length,plan=services.nativeFieldPlans?.[kind]?.[index];
  const readRaw=plan?plan.read:(at=>services.read(kind,at,index));
  const writeRaw=plan?plan.write:((at,value)=>services.write(kind,at,index,value));
  const addressRaw=plan?plan.address:(at=>services.address(kind,at,index));
  readers[id]=plan&&!field.bit&&nativeScalars.has(field.canonical)?(at=>readRaw(convert(at?.address??at))):(at=>decode(field.canonical,readRaw(convert(at?.address??at))));
  writers[id]=(at,value)=>{writeRaw(convert(at?.address??at),BigInt.asUintN(64,BigInt(value)));return value;};
  addresses[id]=at=>convert(addressRaw(convert(at?.address??at)));
 }));
 const compound=(get,set,at,op,rhs)=>{
  const before=get(at);let after;
  switch(op){
   case '+=':after=before+rhs();break;case '-=':after=before-rhs();break;
   case '*=':after=before*rhs();break;case '/=':after=before/rhs();break;
   case '%=':after=before%rhs();break;case '**=':after=before**rhs();break;
   case '<<=':after=before<<rhs();break;case '>>=':after=before>>rhs();break;
   case '>>>=':after=before>>>rhs();break;case '&=':after=before&rhs();break;
   case '|=':after=before|rhs();break;case '^=':after=before^rhs();break;
   case '&&=':if(!before)return before;after=rhs();break;
   case '||=':if(before)return before;after=rhs();break;
   case '??=':if(before!==null&&before!==undefined)return before;after=rhs();break;
   default:throw Error('Unknown native field assignment '+op);
  }
  set(at,after);return after;
 };
 const update=(get,set,at,op,prefix)=>{
  const before=get(at),one=typeof before==='bigint'?1n:1;
  const after=op==='++'?before+one:before-one;set(at,after);return prefix?after:before;
 };
 return {readers,writers,addresses,compound,update};
}

// Resolve immutable field declarations once, rather than on every engine read.
export function compileNativeFieldPlans(environment,schema,ctypes=environment.ctypes) {
 const {memory}=environment,scalarMethods={char:'Int8','signed char':'Int8','unsigned char':'Uint8',short:'Int16','unsigned short':'Uint16',int:'Int32','unsigned int':'Uint32',unsigned:'Uint32',long:'BigInt64','unsigned long':'BigUint64','long long':'BigInt64','unsigned long long':'BigUint64',float:'Float32',double:'Float64'};
 const at=value=>environment.address(value);
 const readBytes=(p,n)=>{if(n===1)return memory.view.getUint8(p);if(n===2)return memory.view.getUint16(p,true);if(n===4)return memory.view.getUint32(p,true);let v=0;for(let i=0;i<n;i++)v+=memory.HEAPU8[p+i]*2**(8*i);return v;};
 const writeBytes=(p,n,v)=>{for(let i=0;i<n;i++)memory.HEAPU8[p+i]=v/2**(8*i)&255;};
 return Object.values(schema.schema).map(row=>{
  const definition=ctypes.record(row.ctype);
  return row.fields.map(declaration=>{
   const field=definition.fields[declaration.name];if(!field)throw Error('Unmeasured native field '+row.ctype+'.'+declaration.name);
   const address=base=>{if(field.bits!==undefined)throw Error('C bitfields have no address');return at(base)+field.offset;};
   if(field.bits!==undefined){
    const bytes=Math.ceil((field.shift+field.bits)/8),mask=2**field.bits-1;
    if(field.shift+field.bits>32){
     return {address,read:base=>ctypes.getField(row.ctype,base,declaration.name,declaration.canonical),write:(base,v)=>ctypes.setField(row.ctype,base,declaration.name,declaration.canonical,v)};
    }
    return {address,
     read:base=>{const p=at(base)+field.offset;memory.bounds(p,bytes);return ((readBytes(p,bytes)>>>field.shift)&mask)>>>0;},
     write:(base,v)=>{const p=at(base)+field.offset;memory.bounds(p,bytes);const packed=mask<<field.shift,old=readBytes(p,bytes),value=Number(BigInt.asUintN(field.bits,BigInt(v)));writeBytes(p,bytes,((old&~packed)|((value&mask)<<field.shift))>>>0);},
    };
   }
   const type=ctypes.canonical(declaration.canonical),pointer=type.includes('*'),aggregate=field.record||type.includes('[')||(!scalarMethods[type]&&!pointer&&!type.startsWith('enum '));
   if(aggregate){let bytes;const size=()=>bytes??=(field.record?ctypes.record(field.record).size:ctypes.size(type));return {address,read:base=>{const p=at(base)+field.offset;if(!field.record)memory.bounds(p,size());return BigInt(p);},write:(base,v)=>memory.memmove(at(base)+field.offset,at(v),size())};}
   if(type.startsWith('enum '))return {address,read:base=>ctypes.load(type,at(base)+field.offset),write:(base,v)=>ctypes.store(type,at(base)+field.offset,v)};
   const method=pointer?'BigUint64':scalarMethods[type],bytes=Number(method.match(/\d+/)[0])/8;
   return {address,
    read:base=>{const p=at(base)+field.offset;memory.bounds(p,bytes);return memory.view['get'+method](p,true);},
    write:(base,v)=>{const p=at(base)+field.offset;memory.bounds(p,bytes);const value=method.startsWith('Big')?BigInt.asUintN(64,BigInt(v)):method.startsWith('Float')?Number(v):Number(BigInt[method.startsWith('Uint')?'asUintN':'asIntN'](bytes*8,BigInt(v)));memory.view['set'+method](p,value,true);},
   };
  });
 });
}
