// Differential transport contracts against the pinned preceding implementation.
// This synthetic check complements, and never replaces, original-C comparisons.
import assert from 'node:assert/strict';
import {execFileSync} from 'node:child_process';
import {CMemory,createBitfields,createCTypes} from '../js/c-runtime/index.js';
import {createAddressBindings} from '../js/c-runtime/address-bindings.js';
const BASE='a2adb49';
const old=execFileSync('git',['show',BASE+':js/c-runtime/types.js'],{encoding:'utf8'})
    .replace("'./memory.js'",JSON.stringify(new URL('../js/c-runtime/memory.js',import.meta.url).href));
const {createCTypes:baseline}=await import('data:text/javascript;base64,'+Buffer.from(old).toString('base64'));
const bindingSource=execFileSync('git',['show',BASE+':js/c-runtime/address-bindings.js'],{encoding:'utf8'});
const {createAddressBindings:baselineBindings}=await import('data:text/javascript;base64,'+Buffer.from(bindingSource).toString('base64'));
const scalars=['char','signed char','unsigned char','short','unsigned short','int','unsigned int','long','unsigned long','float','double','enum status','char *'];
function fixture(create,bindings=create===baseline?baselineBindings:createAddressBindings) {
    const fields=Object.fromEntries(scalars.map((type,i)=>['f'+i,{offset:i*8,ctype:type}]));
    fields.child={offset:112,ctype:'struct child',record:'child'};
    fields.flags={offset:120,ctype:'unsigned int',bits:7,shift:5};
    const metadata={aliases:{packet_t:'const struct packet'},enums:{'enum status':{size:4,signed:true}},records:{
        packet:{size:128,fields},child:{size:8,fields:{x:{offset:0,ctype:'int'}}},
    }};
    const memory=new CMemory({initialBytes:256,maximumBytes:1024*1024});
    const at=memory.calloc(2,128),types=create(memory,metadata,createBitfields(memory,metadata));
    const bindingSchema={globals:[],schema:{packet:{ctype:'struct packet',fields:[{name:'f5',canonical:'int'},{name:'flags',canonical:'unsigned int',bit:true}]}}};
    const environment={ctypes:types,memory,services:{},transport:{},address:Number};
    const binding=bindings({environment,name:'metadata-test',schema:bindingSchema,layout:[],namespace:{},backings:[],publicFunctions:{functions:{}}}).services;
    return {memory,metadata,types,at,bindingSchema,binding};
}
const a=fixture(baseline),b=fixture(createCTypes);let checks=0;
function compare(label,fn) {
    const run=f=>{try{return{value:fn(f)};}catch(e){return{error:{name:e.name,message:e.message}};}};
    assert.deepEqual(run(b),run(a),label);checks++;
    assert.deepEqual(b.memory.HEAPU8,a.memory.HEAPU8,label+' memory');checks++;
}
for(const type of ['packet','struct packet','const struct packet','packet_t','union packet']) {
    compare('record '+type,f=>f.types.record(type));
    compare('record predicate '+type,f=>f.types.isRecord(type));
    compare('locate '+type,f=>f.types.locate(type,f.at,'f0'));
}
for(let i=0;i<scalars.length;i++)for(const value of [0,-1,255,32768,4294967295,2**53,0x123456789abcdefn]) {
    if(scalars[i].includes('*')&&typeof value==='number'&&value<0)continue;
    compare('write '+scalars[i]+' '+value,f=>f.types.setField('packet_t',f.at,'f'+i,scalars[i],value));
    compare('read '+scalars[i],f=>f.types.getField('packet_t',f.at,'f'+i,scalars[i]));
}
for(const value of [-1,0,1,127,128,255,2n**63n]) {
    compare('packed write '+value,f=>f.types.setField('struct packet',f.at,'flags','unsigned int',value));
    compare('packed read',f=>f.types.getField('struct packet',f.at,'flags','unsigned int'));
}
for(const f of [a,b]) {
    const first=f.types.record('packet');first.type='local-only';first.size=999;
    assert.notEqual(first,f.types.record('packet'));
    assert.equal(f.types.record('packet').size,128);
    assert.notEqual(f.types.locate('packet',f.at,'f0').definition,f.types.locate('packet',f.at,'f0').definition);
    f.metadata.records.packet.fields.f0.offset=1;
}
compare('live changed field offset',f=>f.types.getField('packet',f.at,'f0','char'));
for(const f of [a,b])f.metadata.records.packet={size:128,fields:{...f.metadata.records.packet.fields,f0:{offset:2,ctype:'char'}}};
compare('live replaced declaration',f=>f.types.getField('packet',f.at,'f0','char'));
compare('embedded record address',f=>f.types.getField('packet',f.at,'child','struct child'));
compare('embedded record copy',f=>f.types.setField('packet',f.at,'child','struct child',f.at));
compare('heap growth',f=>{f.memory.malloc(4096);return f.types.getField('packet',f.at,'f5','int');});
for(const [type,key,at]of [['missing','x',0],['packet','missing',NaN],['packet','f0',NaN],['packet','f0',1]]) {
    compare('invalid read '+type+'.'+key,f=>f.types.getField(type,at,key,'int'));
    compare('invalid write '+type+'.'+key,f=>f.types.setField(type,at,key,'int',1));
}
for(const value of [1.5,NaN,Infinity,'invalid',undefined])
    compare('invalid scalar conversion '+String(value),f=>f.types.setField('packet',f.at,'f5','int',value));
for(const index of [0,1,99]) {
    compare('address binding '+index,f=>f.binding.address(0,f.at,index));
    compare('read binding '+index,f=>f.binding.read(0,f.at,index));
    compare('write binding '+index,f=>f.binding.write(0,f.at,index,5n));
}
for(const f of [a,b]) {
    f.bindingSchema.schema.packet.fields[0].name='f0';
    f.bindingSchema.schema.packet.fields[0].canonical='char';
}
compare('binding follows mutated field row',f=>f.binding.read(0,f.at,0));
for(const f of [a,b])f.bindingSchema.schema.packet.fields[0]={name:'f5',canonical:'int'};
compare('binding follows replaced field row',f=>f.binding.read(0,f.at,0));
for(const f of [a,b])f.bindingSchema.schema.packet.ctype='packet_t';
compare('binding follows changed record type',f=>f.binding.address(0,f.at,0));
const legacy=fixture(baseline,createAddressBindings);assert.equal(legacy.binding.address(0,legacy.at,0),legacy.at+40);
console.log(`PASS ${checks} differential metadata/field contracts: widths, aliases, fresh descriptions, live offsets/declarations, packed bits, records, growth, errors and conversion boundaries; synthetic only.`);
