// Actual configured memory64 C/JS differential. Native/game/public pending.
import assert from 'node:assert/strict';
import {resolve} from 'node:path';
import {pathToFileURL} from 'node:url';
import {C} from '../js/ported/c-runtime.js';
if(process.env.TELEPORT_NATIVE_TESTS==='1')throw new Error('WINDOWS has no native fixture backend; this runner supports Emscripten-only comparisons.');
const {callWindows,initializeWindows}=await import(process.env.WINDOWS_RUNTIME?pathToFileURL(resolve(process.env.WINDOWS_RUNTIME)):new URL('../js/ported/windows-runtime.js',import.meta.url));
const dir=resolve(process.env.WINDOWS_PROBE_DIR??'.cache/windows-first-pass');
const ref=(await import(pathToFileURL(resolve(dir,'windows-reference.mjs')))).default;
const hybrid=(await import(pathToFileURL(resolve(dir,'windows-hybrid.mjs')))).default;
const text=(m,p)=>{p=Number(p);let e=p;while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.subarray(p,e)).toString('latin1');};
const layouts=m=>Object.fromEntries(Array.from({length:m._probe_layout_count()},(_,i)=>[text(m,m._probe_layout_name(i)),Number(m._probe_layout_value(i))]));
let modules,L,comparisons=0,scenario='initial',invoked=new Set();
async function pair(){const a=await ref();L=layouts(a);const b=await hybrid({nethackPorted:{windows:(s,n,...args)=>{if(n!=='initialize')invoked.add(n);return callWindows(s,L,n,...args);}}});modules=[a,b];assert.deepEqual(layouts(b),L);comparisons++;assert.equal(a._probe_consumer(1,0),BigInt(L.NO_COLOR));assert.equal(b._probe_consumer(1,0),BigInt(L.NO_COLOR));comparisons+=2;modules.forEach(m=>m._probe_initialize());reset();}
await pair();
function reset(){modules.forEach(m=>m._probe_reset());}
function input(s,slot=0){const data=typeof s==='string'?Buffer.from(s,'latin1'):s;for(const m of modules){const p=Number(m._probe_buffer(slot));m.HEAPU8.set(data,p);m.HEAPU8[p+data.length]=0;}}
function compare(){const states=modules.map(m=>({snapshot:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace()),buffers:[1,3,5].map(i=>text(m,m._probe_buffer(i)))}));if(JSON.stringify(states[0])!==JSON.stringify(states[1]))for(const k of ['snapshot','trace'])if(states[0][k]!==states[1][k]){let i=0;while(states[0][k][i]===states[1][k][i])i++;console.error(scenario,k,i,JSON.stringify(states[0][k].slice(Math.max(0,i-80),i+180)),JSON.stringify(states[1][k].slice(Math.max(0,i-80),i+180)));}assert.deepEqual(states[1],states[0],scenario);assert.equal(C,undefined);comparisons++;}
function call(name,...args){const sp=modules.map(m=>m._probe_stack());const values=modules.map((m,i)=>{try{return m['_probe_'+name](...args);}catch(e){console.error(scenario,name,i,args);throw e;}});assert.deepEqual(values[1],values[0],scenario+' return');comparisons++;modules.forEach((m,i)=>assert.equal(m._probe_stack(),sp[i],scenario+' stack'));compare();return values[0];}
const action=(n,a=0,b=0,v=0n)=>call('call',n,a,b,BigInt(v)),option=(i,v)=>call('option',i,v),field=(i,v)=>call('field',i,BigInt(v));
function choose(){input('tty');action(7);}
function table(){for(let i=5;i<51;i++)call('callback_id',i);}
for(const n of[0,1,2,3,4,5,6,8,9,10,11,...Array.from({length:26},(_,i)=>i+12),42,...Array.from({length:15},(_,i)=>i+43),58,59,60,61,62,63,64,66,67,68,69,70,71,72]){scenario='source body '+n;reset();choose();input('hello');input('query',2);action(n,0,0,0n);}
scenario='window copy/init order';reset();choose();table();choose();input('TTY');action(6);action(7);field(2,1);action(12);table();action(12);table();action(13);action(13);
for(const v of[0n,1n,0x80000000n,9007199254740997n,(1n<<64n)-1n]){scenario='capabilities64 '+v;reset();field(100,v);field(101,v);for(const mask of[0n,1n,0x80000000n,9007199254740997n,(1n<<64n)-1n]){action(4,0,0,mask);action(5,0,0,mask);}choose();field(4,1);for(let c=0;c<L.CLR_MAX;c++)action(55,c);}
for(const s of['','bad','x'.repeat(49),'x'.repeat(50),'x'.repeat(1200)]){scenario='unknown window '+s.length;reset();input(s);modules.forEach(m=>assert.throws(()=>m._probe_call(7,0,0,0n),/WINDOWS fixture exit 10/));assert.equal(C,undefined);compare();reset();choose();input(s);action(7);}
for(const def of[-128,-1,0,1,27,127,255]){scenario='hangup char '+def;action(15,0,0,0n);action(15,def);}
for(const glyph of[-1,0,1,0x1234,0xffff,0x10000,0x7fffffff,-2147483648])for(const seed of[0,1,0xabcd,0xffff]){scenario='glyph encoding '+glyph+'/'+seed;reset();field(15,seed);action(58,glyph);input(text(modules[0],modules[0]._probe_buffer(5)).slice(2));action(59,0,0,113n);action(56,glyph);action(57,glyph);}
for(const seed of[0,1,0xbeef])for(const s of['','00000000','0000000','0000ZZZZ','BEEF0012','beef0012','1','12345zz','zzzz','ffff1234','00001234tail']){scenario='decode '+seed+'/'+s;field(15,seed);input(s);action(59,0,0,123n);}
for(const s of['','abc','\\','\\\\','x\\G00000001y','\\G00000001\\G00000002','\\G0000000Z','\\GFFFF0001','x\\qz','\\G']){scenario='mixed '+s;reset();choose();field(15,0);input(s);action(60,1);action(61,17,3);action(64,1,1);action(64,0,1);action(64,1,0);}
for(const category of[0,1])for(const way of[0,1])for(const n of[-1,0,1,2,4]){scenario='classes '+[category,way,n];reset();choose();input(category===0?'adef':'!?/+=');input('Autopickup what?',2);input(n>0?'a ':'' ,3);option(1,n);action(65,category,way);}
for(const mode of[0,1,2,7])for(const selected of[0,1])for(const flags of[0n,BigInt(L.MENU_ITEMFLAGS_SKIPINVERT),0xffffffffn]){scenario='menu invert';field(0,0);/* raw_printed intentionally independent */field(17,mode);action(63,mode,selected,flags);}
for(const enabled of[0,1])for(const match of[0,1,2,3])for(const flags of[0n,1n,BigInt(L.MENU_ITEMFLAGS_SKIPMENUCOLORS),0xffffffffn]){scenario='menu color '+[enabled,match,flags];reset();choose();field(5,enabled);option(10,match);call('menucolor',0,7,2);call('menucolor',1,14,5);input('matching menu');action(70,-1,-2);action(67,3,4,flags);action(68,17);field(8,1);action(68,17);action(69,17);}
for(const queued of[[],[[L.CMDQ_KEY,65]],[[L.CMDQ_KEY,65],[L.CMDQ_KEY,10],[L.CMDQ_KEY,66]],[[L.CMDQ_KEY,65],[L.CMDQ_KEY+1,0]],[[L.CMDQ_KEY+1,0]],[[L.CMDQ_KEY,65],[L.CMDQ_KEY,66],[L.CMDQ_KEY,67]]]){scenario='getlin queue '+queued;reset();choose();input('interactive answer');input('prompt?',2);for(const[type,key]of queued)call('queue',type,key);action(72);}
for(const missing of[0,1])for(const complain of[0,1])for(const failwrite of[0,1]){scenario='display file';reset();choose();input('test-file');input('alpha\nbeta\nlast',4);option(8,missing);option(9,failwrite);action(62,complain);}
for(const old of[0,1])for(const selected of[-1,0,1,4]){scenario='select return ownership64 '+old+'/'+selected;reset();choose();field(10,old);option(1,selected);action(71,17,2);}
scenario='encglyph static alias';reset();field(15,0x1234);assert.equal(call('enc_alias',1,0x5678),1);comparisons++;
scenario='internal menu callee lifetime';reset();choose();option(12,1);input('a'.repeat(1200));input('large repeated monster class list',2);action(65,0,1);assert.ok(!text(modules[0],modules[0]._probe_trace()).match(/callback-sp:(?!0;)/));comparisons++;
for(const initial of[0,1]){scenario='dump redirection '+initial;reset();choose();call('dump',initial);for(const on of[0,1,1,0]){action(54,on);table();input('dump text');for(const n of[44,45,46,47,48,49,50,51,52,53])action(n,17,L.NO_GLYPH,0n);action(51,17,12,0n);action(52,17,1);action(44,17,3,1n);}action(43);}
for(const format of[0,1,2,3,4])for(const len of[1,5,12]){scenario='status layout '+format+'/'+len;reset();choose();action(38);option(11,format===4?0:format);for(let i=0;i<L.MAXBLSTATS;i++){input('field'+i,2);action(40,i,1);if(format===4)call('null_status_format',i);input((i%3?' ':'')+'x'.repeat(len));action(41,i,0,i===L.BL_CONDITION?0x1fffn:0n);call('consumer',3,i);call('consumer',4,i);call('consumer',5,i);call('consumer',6,i);}action(41,L.BL_FLUSH);action(41,L.BL_RESET);action(39);action(39);}
for(const cond of[0n,1n,0x1fffn,9007199254740997n,-1n,-(1n<<63n)]){scenario='status condition64 '+cond;reset();choose();action(38);action(40,L.BL_CONDITION,1);action(41,L.BL_CONDITION,0,cond);action(41,L.BL_FLUSH);action(39);}
for(const value of[9007199254740997n,-9007199254740997n,(1n<<63n)-1n,-(1n<<63n)]){scenario='foreign copy64 '+value;call('storage',4,0,value);assert.equal(call('consumer',0,0),value);comparisons++;call('initialize');assert.equal(call('consumer',0,0),value);comparisons++;}
for(const opt of[3,4]){scenario='growth/reentry '+opt;reset();choose();option(opt,1);input('window message');const before=modules.map(m=>m.HEAPU8.byteLength);action(8);if(opt===3)modules.forEach((m,i)=>{assert.ok(m.HEAPU8.byteLength>before[i]);comparisons++;});}
scenario='debug macro';reset();choose();option(7,1);action(67,0,0,0n);
for(const n of[8,38,72]){scenario='foreign callback throw '+n;reset();choose();option(5,1);input('throw fixture');input('throw?',2);modules.forEach(m=>assert.throws(()=>m._probe_call(n,0,0,0n),/WINDOWS fixture exit 5/));assert.equal(C,undefined);compare();}
const old=modules;await pair();scenario='second Module startup';choose();action(12);table();modules=old;scenario='original Module reuse';reset();choose();action(12);table();
assert.equal(invoked.size,73,'all original configured WINDOWS bodies invoked');comparisons++;
console.log(`WINDOWS: ${comparisons} configured Emscripten-C/JS comparisons passed; ${invoked.size}/73 bodies invoked; native/game/public pending.`);
