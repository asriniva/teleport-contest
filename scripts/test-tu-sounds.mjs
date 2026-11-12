import './pure-js-probes/deny-wasm.mjs';
import {referenceLabelFor as fixtureReferenceLabelFor} from './native-test-backend.mjs';
const fixtureReferenceLabel=fixtureReferenceLabelFor("sounds");
import {createProbe,createReference,loadFixture,fixtureImports} from './pure-js-fixtures/load.mjs';
import {Int32Array as FixtureInt32Array} from './native-test-backend.mjs';
import {Int32Array,referenceBackend,assertStackRestored,assertMemoryGrowth} from './native-test-backend.mjs';
import assert from './native-test-assert.mjs';
import {readFileSync} from 'node:fs';
import {resolve} from 'node:path';
import {pathToFileURL} from 'node:url';
import * as sounds from '../js/ported/sounds.js';
import {callSounds} from '../js/nethack/bindings/sounds.js';
import {C,R,T} from '../js/c-runtime/context.js';
const author=process.env.TELEPORT_SOUNDS_PROBES,dir=author?pathToFileURL(resolve(author)+'/'):new URL('../.cache/tu-probes/',import.meta.url);
const referenceFactory=(await loadFixture("sounds",new URL('sounds-reference.mjs',dir))).default,hybridFactory=(await loadFixture("sounds",new URL('sounds-hybrid.mjs',dir))).default;
const ref=await referenceBackend('sounds',referenceFactory)();
function text(m,p){if(!p)return null;let end=Number(p);while(m.HEAPU8[end])end++;return Buffer.from(m.HEAPU8.slice(Number(p),end)).toString();}
const L={size:Number(ref._probe_context_size())};for(let i=0;i<ref._probe_layout_count();i++){const k=text(ref,ref._probe_layout_name(i)),v=ref._probe_layout_value(i);L[k]=/^(M1_|M2_|STRAT_|W_)/.test(k)?BigInt.asUintN(64,v).toString():Number(v);}
if(!author)assert.deepEqual(L,JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url))).sounds);
for(const k of ['soundSize','monSize','objSize','NUMMONS','BUFSZ','MS_HUMANOID','PM_HUMAN','HELMET','GLYPH_MON_MALE_OFF'])assert.ok(Number.isSafeInteger(L[k]),k);
const runtime={sounds:(s,n,...args)=>callSounds(s,L,n,...args)};
const modules=[ref,await hybridFactory({nethackPorted:runtime})],stacks=modules.map(m=>m._probe_stack());let comparisons=0;
function bytes(m,p,n){return Buffer.from(m.HEAPU8.slice(Number(p),Number(p)+n));}
// Original exported soundprocs must remain native-zero before any source function call.
for(const m of modules)assert.deepEqual(bytes(m,m._probe_pointer(4,0),L.soundSize),Buffer.alloc(L.soundSize));comparisons+=2;
function soundBytes(m,kind){const p=m._probe_pointer(kind?5:4,0),b=bytes(m,p,L.soundSize),name=text(m,b.readBigUInt64LE(L.sound_soundname));b.writeBigUInt64LE(0n,L.sound_soundname);const callbacks=[m._probe_callback(0),m._probe_callback(1)];for(const key of ['sound_init_nhsound','sound_exit_nhsound','sound_achievement','sound_soundeffect','sound_hero_playnotes','sound_play_usersound','sound_ambience','sound_verbal']){const at=L['sound_'+key],raw=b.readBigUInt64LE(at),index=callbacks.indexOf(raw);if(index>=0)b.writeBigUInt64LE(BigInt(index+1),at);}return {name,bytes:b};}
function snapshot(m){return {output:bytes(m,m._probe_pointer(1,0),1024),values:Array.from({length:20},(_,k)=>m._probe_scalar(k)),reason:text(m,m._probe_reason()),nomove:text(m,m._probe_nomove()),sound:soundBytes(m,0),source:soundBytes(m,1),trace:text(m,m._probe_trace()),rng:[m._probe_rng_count(),m._probe_rng_state()>>>0]};}
function state(){assert.deepEqual(snapshot(modules[1]),snapshot(modules[0]));assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);modules.forEach((m,i)=>assertStackRestored(m,stacks[i]));comparisons++;}
function call(n,...args){const results=modules.map(m=>m['_probe_'+n](...args));assert.deepEqual(results[1],results[0],n+'('+args+')');state();comparisons++;return results[0];}
function string(n,s){modules.forEach(m=>{const b=Buffer.from(s),p=m._malloc(BigInt(b.length+1));m.HEAPU8.set(b,Number(p));m.HEAPU8[Number(p)+b.length]=0;m['_probe_'+n](BigInt(p));m._free(BigInt(p));});state();}
const reset=(seed=42)=>call('reset',seed),act=(op,a=0,b=0,size=0n)=>call('action',op,a,b,BigInt(size)),mon=(i,k,v)=>call('mon',i,k,BigInt(v)),hero=(k,v)=>call('hero',k,BigInt(v));
function rolls(vals){modules.forEach(m=>{new FixtureInt32Array(m.HEAPU8.buffer,Number(m._probe_rng_pointer()),vals.length).set(vals);m._probe_rng_length(vals.length);});state();}
reset();for(let i=0;i<sounds.h_sounds.length;i++){assert.equal(text(ref,ref._probe_table_string(i)),sounds.h_sounds[i]);comparisons++;}assert.equal(sounds.soundlib_choices.length,1);assert.equal(sounds.soundlib_choices[0].sndprocs,sounds.nosound_procs);
// All28 source entries, all actual monster catalogue sound codes and exact text/RNG.
for(let pm=0;pm<L.NUMMONS;pm++){reset();mon(0,0,pm);for(const op of [8,9,10,11,12,13,14,15,16])act(op);}
for(const pm of [L.PM_DOG,L.PM_GHOST,L.PM_HUMAN,L.PM_GECKO])for(const asleep of [0,1])for(const deaf of [0,1])for(const hallu of [0,1]){reset();mon(0,0,pm);mon(0,1,asleep);hero(0,deaf);hero(5,hallu);for(const op of [8,9,10,11,12,13,14,15,16])act(op);}
for(const props of [[0,0,0],[1,0,0],[1,1,0],[0,1,0],[1,0,1]]){reset();hero(0,props[0]);hero(1,props[1]);hero(2,props[2]);act(9);act(18);}
// Specific ambient room predicates, callback identity/traversal and room flags.
for(const [op,type,pm]of [[1,L.COURT,L.PM_HUMAN],[2,L.BEEHIVE,L.PM_KILLER_BEE],[3,L.MORGUE,L.PM_GHOST],[4,L.ZOO,L.PM_DOG],[5,L.TEMPLE,L.PM_ALIGNED_CLERIC],[6,L.OROOM,L.PM_ORACLE]])for(const hallu of [0,1]){reset();call('room',type);mon(0,0,pm);mon(0,1,1);mon(0,12,op===5?1:0);hero(5,hallu);for(const r of [0,1,2,3]){rolls([r]);act(op);}act(0,0,type);}
for(let flag=0;flag<11;flag++)for(const hallu of [0,1]){reset();call('level_flag',flag,1);call('chain',0,-1);call('option',17,1);call('option',6,1);call('room',[L.OROOM,L.OROOM,L.COURT,L.SWAMP,L.VAULT,L.BEEHIVE,L.MORGUE,L.BARRACKS,L.ZOO,L.SHOPBASE,L.TEMPLE][flag]);mon(0,12,1);mon(0,1,1);hero(5,hallu);rolls(Array(64).fill(0));act(7);}
reset();call('level',1,7);call('chain',0,-1);mon(0,0,L.PM_ORACLE);rolls([0,1]);act(7);
// Dialogue conditional choices, integer HP division boundaries and Death's native int*.
const codes=Array.from(new Set(Object.entries(L).filter(([k,v])=>k.startsWith('MS_')&&typeof v==='number').map(([,v])=>v)));
for(const code of codes)for(const peaceful of [0,1]){reset();call('pm',L.PM_HUMAN,code,L.S_HUMAN);mon(0,4,peaceful);call('option',2,1);call('option',19,1);rolls(Array(64).fill(1));act(16);}
for(const maxhp of [3,5,7,9])for(const hp of [1,2,3]){reset();mon(0,4,1);mon(0,16,hp);mon(0,17,maxhp);act(16);}
for(const novel of [0,1])for(const title of [0,1]){reset();mon(0,0,L.PM_DEATH);call('option',23,novel);call('option',13,title);call('option',1,1);rolls([1,0]);act(16);act(16);}
for(const seduce of [0,1])for(const gender of [0,1])for(const possible of [0,1]){reset();call('pm',L.PM_HUMAN,L.MS_SEDUCE,L.S_HUMAN);hero(24,seduce);call('option',15,gender);call('option',4,possible);rolls([0,1,2]);act(16);}
for(const strategy of [0x8000000000000000n,0xffffffffffffffffn]){reset();mon(0,19,BigInt.asIntN(64,strategy));call('grid',0,11,8,0);act(17);}
// #chat/#tip direction and map behavior, including both original nada routes.
for(const direction of [[0,0,0],[0,0,1],[0,0,-1],[1,0,0],[-1,0,0]])for(const present of [0,1]){reset();hero(18,direction[0]);hero(19,direction[1]);hero(20,direction[2]);if(present)call('grid',0,11,8,0);act(18);act(17);act(19,11,8);call('equipment',3,0);act(20);}
for(const seen of [0,1])for(const peaceful of [0,1])for(const deaf of [0,1]){reset();call('equipment',3,0);call('grid',0,11,8,0);call('option',2,seen);mon(0,4,peaceful);hero(0,deaf);rolls([0,1,2,1]);act(20);}
for(const glyph of [L.GLYPH_INVISIBLE,L.GLYPH_STATUE_MALE_OFF+L.PM_HUMAN,L.GLYPH_MON_MALE_OFF+L.PM_GECKO]){reset();call('equipment',3,0);call('cell',11,8,L.ROOM,L.ROOMOFFSET,glyph,L.IN_SIGHT|L.COULD_SEE);hero(5,1);act(20);}
reset();call('equipment',3,0);call('object',0,L.HELMET,1,0);act(20);reset();hero(9,1);act(18);reset();hero(11,1);act(18);reset();call('option',18,1);act(18);
// Native sound_procs zero state, source fields, all bytes/padding and raw callbacks.
reset();act(22,0);for(const n of [0,1,2,4,8,100])act(23,n);for(const name of ['nosound','NOsound','unknown','']){string('input',name);act(24);}act(21);
reset();call('sound',0,2);hero(25,1);act(21);reset();call('sound',1,2);act(21);reset();call('sound',0,1);call('sound',1,1);hero(25,1);act(21);
reset();call('sound',1,3);act(23,100);
// Exact unsigned size_t filename construction, source truncation quirk and stale bytes.
for(const basename of ['', 'x','ding','longer-file-name'])for(const prefix of ['', '/tmp','/tmp/','C:\\dir\\'])for(const approach of [L.sff_base_only,L.sff_havedir_append_rest,L.sff_baseknown_add_rest,99])for(const size of [0n,1n,4n,5n,8n,16n,64n,0xffffffffffffffffn]){reset();string('input',basename);string('output',prefix);act(25,approach,0,size);}
reset();string('input','ding');act(25,L.sff_base_only,1,100n);act(26);act(27);
// Native world callback grows memory before the next read of equipment/global state.
reset();call('equipment',3,0);call('option',30,1);const before=modules.map(m=>m.HEAPU8.buffer);act(20);modules.forEach((m,i)=>assertMemoryGrowth(m,before[i]));
// Separate actual Modules share JS functions but not private sound source addresses/data.
const other=await hybridFactory({nethackPorted:runtime});other._probe_reset(42);other._probe_sound(1,3);other._probe_action(23,100,0,0n);assert.equal(text(other,other._probe_pointer(1,0)),'nosound');assert.equal(soundBytes(other,1).name,'nosound,aliases');reset();act(23,100);assert.equal(text(modules[1],modules[1]._probe_pointer(1,0)),'nosound');assert.equal(soundBytes(modules[1],1).name,'nosound');assert.equal(soundBytes(other,1).name,'nosound,aliases');comparisons+=5;
console.log('SOUNDS '+comparisons+' comparisons passed ('+fixtureReferenceLabel+' vs JavaScript).');
