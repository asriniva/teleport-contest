import assert from 'node:assert/strict';
import fs from 'node:fs';
import {pathToFileURL} from 'node:url';
import {createStandaloneEnvironment} from '../js/nethack/environment.js';
import * as sfstruct from '../js/ported/sfstruct.js';
const root=process.env.STANDALONE_REFERENCE_ROOT;if(!root)throw new Error('Missing STANDALONE_REFERENCE_ROOT');
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),S=layouts.sfstruct,L=layouts.sfbase;
const env=createStandaloneEnvironment({maximumBytes:64*1024*1024});env.enableStdio();env.enableDecl(layouts.decl);
const serialization=env.enableSerialization(layouts),{memory,services}=env;
const {default:factory}=await import(pathToFileURL(root+'/.cache/tu-probes/sfstruct-reference.mjs')),ref=await factory();
const frame=memory.calloc(1,S.nhfileSize),data=memory.malloc(65536);
const names=Object.keys(sfstruct.historical_sfo_procs.fn).map(k=>k.slice(3));let comparisons=0;
assert.equal(names.length,68);
for(const [index,name]of names.entries())for(const input of [0,1]) {
    ref._probe_reset();ref._probe_open(0,0);ref._probe_option(8,0);ref._probe_fill(17+index);
    const size=name==='char'?19:S['type_'+(name==='genericptr'?'genericptr_t':name)+'_size'];
    assert.ok(size>0&&size<65536);
    const original=Uint8Array.from({length:size},(_,i)=>(17+index+i*29)&255);
    const fd=services.open('/serialized',578,0o600);
    memory.memset(frame,0,S.nhfileSize);memory.view.setInt32(frame+S.nhf_fd,fd,true);
    memory.view.setInt32(frame+L.nhf_fnidx,L.historical,true);memory.view.setInt8(frame+L.nhf_structlevel,1);
    memory.view.setInt32(frame+L.nhf_mode,input?0:L.WRITING,true);
    memory.HEAPU8.set(original,data);
    if(input) {
        assert.equal(services.write(fd,data,size),size);services.lseek(fd,0,0);memory.memset(data,165,size);
        ref._probe_seed_file(0,size);ref._probe_fill(165);
    }
    const symbol=(input?'sfi_':'sfo_')+name;
    env.call('sfbase',symbol,frame,data,'test',name==='char'?19:77);
    assert.equal(ref._probe_serial(input,index,0,name==='char'?19:77,1),0n);
    if(input)assert.deepEqual(memory.readBytes(data,size),ref.HEAPU8.slice(Number(ref._probe_buffer()),Number(ref._probe_buffer())+size));
    else {
        assert.equal(ref._probe_read_file(0),size);
        assert.deepEqual(env.filesystem.readFile('/serialized'),ref.HEAPU8.slice(Number(ref._probe_saved()),Number(ref._probe_saved())+size));
    }
    if(input)services.close(fd);else env.call('sfstruct','bclose',fd);
    comparisons++;
}
// Real source normalizers remain the original configured no-op bodies; no
// replacement normalizers or fixture-specific expected values are installed.
assert.equal(serialization.base.historical,1);
console.log(`PASS: ${comparisons} SFBASE → callback table → SFSTRUCT → standalone file comparisons against original C, covering all 68 historical serializer kinds in both directions.`);
