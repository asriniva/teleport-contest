import assert from 'node:assert/strict';
import fs from 'node:fs';
import {pathToFileURL} from 'node:url';
import {createStandaloneEnvironment} from '../js/nethack/environment.js';
const root=process.env.STANDALONE_REFERENCE_ROOT;if(!root)throw new Error('Missing STANDALONE_REFERENCE_ROOT');
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json')),L=layouts.track,S=layouts.sfbase;
const env=createStandaloneEnvironment();env.enableStdio();env.enableDecl(layouts.decl);env.enableHacklib(layouts.hacklib);env.enableSerialization(layouts);
const state=env.enableTrack(layouts),{memory,services}=env;
const {default:factory}=await import(pathToFileURL(root+'/.cache/tu-probes/track-reference.mjs')),ref=await factory();
const frame=memory.calloc(1,S.nhfileSize),rings=[memory.calloc(1,env.ctypes.size('struct obj')),memory.calloc(1,env.ctypes.size('struct obj'))];
let comparisons=0;
function compare(){assert.equal(state.utcnt,ref._probe_count());assert.equal(state.utpnt,ref._probe_point());assert.deepEqual(memory.readBytes(state.utrack.address,L.UTSZ*L.coordSize),ref.HEAPU8.slice(Number(ref._probe_data()),Number(ref._probe_data())+L.UTSZ*L.coordSize));comparisons++;}
function init(){env.call('track','initrack');ref._probe_init();compare();}
function hero(x,y,left=-1,right=-1){services.u.ux=x;services.u.uy=y;for(const [i,key]of ['uleft','uright'].entries()){const type=i?right:left;services[key]=type<0?0:rings[i];if(type>=0)env.ctypes.setField('struct obj',rings[i],'otyp','short',type);}ref._probe_hero(x,y,left,right);env.call('track','settrack');ref._probe_set();compare();}
function query(x,y){const result=env.call('track','gettrack',x,y),pointer=ref._probe_get(x,y);assert.equal(result?(result.address-state.utrack.address)/L.coordSize:-1,pointer?(Number(pointer)-Number(ref._probe_data()))/L.coordSize:-1);assert.equal(env.call('track','hastrack',x,y),ref._probe_has(x,y));comparisons++;}
init();query(0,0);
for(let i=0;i<453;i++){hero(i%80,i*7%21,i%17===0?L.RIN_STEALTH:-1,-1);query(i%80,(i*7+1)%21);}
for(const count of [0,1,99,100,101])for(let mode=0;mode<8;mode++){
    init();for(let i=0;i<count;i++)hero(i-150,i*3-100);
    const fd=services.open('/track-save',578,0o600);memory.memset(frame,0,S.nhfileSize);
    memory.view.setInt32(frame+layouts.sfstruct.nhf_fd,fd,true);memory.view.setInt32(frame+S.nhf_mode,mode,true);memory.view.setInt32(frame+S.nhf_fnidx,S.historical,true);memory.view.setInt8(frame+S.nhf_structlevel,1);
    env.call('track','save_track',frame);ref._probe_save(mode);compare();
    const saved=env.filesystem.readFile('/track-save'),size=Number(ref._probe_stream_size());assert.deepEqual(saved,ref.HEAPU8.slice(Number(ref._probe_stream()),Number(ref._probe_stream())+size));comparisons++;
    if(mode&(L.COUNTING|L.WRITING)){
        init();services.lseek(fd,0,0);memory.view.setInt32(frame+S.nhf_mode,0,true);env.call('track','rest_track',frame);assert.equal(ref._probe_rest(),0);compare();
    }
    if(mode&(L.COUNTING|L.WRITING))env.call('sfstruct','bclose',fd);else services.close(fd);
}
console.log(`PASS: ${comparisons} original-C track ring-buffer/equipment/query/state and historical save/restore comparisons through real SFBASE/SFSTRUCT and standalone files.`);
