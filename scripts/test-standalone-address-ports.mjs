import assert from 'node:assert/strict';
import fs from 'node:fs';
import {pathToFileURL} from 'node:url';
import path from 'node:path';
import {createStandaloneEnvironment} from '../js/nethack/environment.js';
const root=process.env.STANDALONE_REFERENCE_ROOT;if(!root)throw new Error('Missing STANDALONE_REFERENCE_ROOT');
const metadata=JSON.parse(fs.readFileSync('js/nethack/address-ports.json'));
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json'));
const oracleRoot=path.resolve(process.env.STANDALONE_HELPER_ORACLES??'.cache/standalone-helper-oracles');
let checks=0;
for(const [name,definition]of Object.entries(metadata.ports)) {
    const env=createStandaloneEnvironment({maximumBytes:64*1024*1024});
    env.enableDecl(layouts.decl);env.enableDrawing(layouts.drawing);env.enableObjects(layouts.objects);env.enableMonst(layouts.monst);
    const adapter=env.enableAddressPort(name),{default:factory}=await import(pathToFileURL(oracleRoot+`/${name}-reference.mjs`)),ref=await factory();
    const nativeRead=ref[`_teleport_${name}_read`]??(['shk','invent'].includes(name)?ref._probe_read:null);
    const nativeAddress=ref[`_teleport_${name}_address`]??(['shk','invent'].includes(name)?ref._probe_address:null);
    const nativeWrite=ref[`_teleport_${name}_write`]??(['shk','invent'].includes(name)?ref._probe_write:null);
    if(!nativeRead||!nativeAddress||!nativeWrite)throw new Error('Missing actual field oracle '+name);
    const scratch=ref._malloc?Number(ref._malloc(2n*1024n*1024n)):Number(ref._probe_growth());
    for(const [kind,[key,record]]of Object.entries(definition.schema.schema).entries()) {
        const size=env.ctypes.size(record.ctype),p=env.memory.calloc(1,size),q=scratch;
        assert.ok(size<2*1024*1024,'Native scratch bounds');
        for(let index=0;index<record.fields.length;index++) {
            const field=record.fields[index];
            if(!field.bit){const at=adapter.services.address(kind,p,index),nativeAt=Number(nativeAddress(kind,BigInt(q),index));assert.equal(at-p,nativeAt-q,`${name}:${key}.${field.name} address`);checks++;}
            // Test the read transport on actual byte witnesses, including packed
            // neighbors, signed values and pointer cells, without dereferencing.
            for(const pattern of [0,1,127,128,255]) {
                env.memory.HEAPU8.fill(pattern,p,p+size);ref.HEAPU8.fill(pattern,q,q+size);
                const expected=nativeRead(kind,BigInt(q),index),actual=adapter.services.read(kind,p,index);
                const type=env.ctypes.canonical(field.canonical);
                if(type.includes('[')||(!type.includes('*')&&!/^(enum |char$|signed char$|unsigned char$|short$|unsigned short$|int$|unsigned int$|unsigned$|long$|unsigned long$|long long$|unsigned long long$)/.test(type)))
                    assert.equal(Number(actual)-p,Number(expected)-q,`${name}:${key}.${field.name} aggregate`);
                else assert.equal(BigInt.asUintN(64,BigInt(actual)),BigInt.asUintN(64,BigInt(expected)),`${name}:${key}.${field.name} byte ${pattern}`);
                checks++;
            }
            const type=env.ctypes.canonical(field.canonical),aggregate=type.includes('[')||(!type.includes('*')&&!/^(enum |char$|signed char$|unsigned char$|short$|unsigned short$|int$|unsigned int$|unsigned$|long$|unsigned long$|long long$|unsigned long long$)/.test(type));
            if(!aggregate&&!/\*\s*const\b|^const [^*]*$/.test(field.ctype))for(const value of [0n,1n,0xffffffffffffffffn,0x8123456789abcdefn]) {
                env.memory.HEAPU8.fill(165,p,p+size);ref.HEAPU8.fill(165,q,q+size);
                adapter.services.write(kind,p,index,value);nativeWrite(kind,BigInt(q),index,value);
                assert.deepEqual(Buffer.from(env.memory.readBytes(p,size)),Buffer.from(ref.HEAPU8.slice(q,q+size)),`${name}:${key}.${field.name} write ${value}`);checks++;
            }
        }
        env.memory.free(p);
    }
    assert.ok(adapter.unresolved().length>0,'Unresolved game dependencies must be reported');
}
console.log(`PASS: ${checks} original-C address/scalar/bitfield witnesses across ${Object.keys(metadata.ports).length} existing adapters; unresolved game dependencies remain explicit.`);
