import './pure-js-probes/deny-wasm.mjs';
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import {pathToFileURL} from 'node:url';
import {loadFixture} from './pure-js-fixtures/load.mjs';
import {callMhitu,getMhituState} from '../js/nethack/bindings/mhitu.js';
import {C,R,T} from '../js/c-runtime/context.js';

const schema=JSON.parse(fs.readFileSync('nethack-c/wasm/tu-fragments/mhitu-schema.json'));
const kinds=Object.keys(schema.schema),layout={},servicesByModule=new WeakMap();
const factory=async kind=>(await loadFixture('mhitu',pathToFileURL(path.resolve('.cache/mhitu-author/mhitu-'+kind+'.mjs')))).default;
const reference=await (await factory('reference'))();
function text(m,p){let at=Number(p),end=at;while(m.HEAPU8[end])end++;return Buffer.from(m.HEAPU8.slice(at,end)).toString('latin1');}
for(let i=0;i<reference._probe_layout_count();i++)layout[text(reference,reference._probe_layout_name(i))]=Number(BigInt.asIntN(64,reference._probe_layout_value(i)));
const implementation=await (await factory('hybrid'))({nethackPorted:{mhitu(services,name,...args){servicesByModule.set(services.moduleKey,services);return callMhitu(services,layout,name,...args);}}});
const modules=[reference,implementation],ptr=(m,k,i=0)=>m._probe_pointer(k,i);
const read=(m,type,at,name)=>m._teleport_mhitu_read(kinds.indexOf(type),at,schema.schema[type].fields.findIndex(field=>field.name===name));
const monster=m=>ptr(m,0),item=m=>ptr(m,1),hero=m=>ptr(m,6),attack=m=>ptr(m,9),species=m=>ptr(m,2,layout.PM_HUMAN);
const speciesAttack=m=>read(m,'permonst',species(m),'mattk');
const actions=[
 ['hitmsg',monster,speciesAttack],['missmu',monster,0,attack],
 ['mswings_verb',item,0],['mswings',monster,item,0],['mpoisons_subj',monster,attack],
 ['u_slow_down'],['wildmiss',monster,attack],['expels',monster,species,1],
 ['getmattk',monster,hero,0,m=>ptr(m,10),attack],
 ['calc_mattacku_vars',monster,...[0,1,2,3].map(i=>m=>ptr(m,11,i))],
 ['mtrapped_in_pit',monster],['mattacku',monster],['summonmu',monster,1],
 ['diseasemu',species],['u_slip_free',monster,attack],['magic_negation',monster],
 ['hitmu',monster,speciesAttack],['gulp_blnd_check'],['gulpmu',monster,speciesAttack],
 ['explmu',monster,speciesAttack,0],['gazemu',monster,attack],['mdamageu',monster,3],
 ['could_seduce',monster,hero,attack],['doseduce',monster],
 ['mayberem',monster,m=>ptr(m,5),item,m=>ptr(m,5)],['assess_dmg',monster,3],
 ['mon_avoiding_this_attack',monster,0],['ranged_attk_available',monster],
 ['passiveum',species,monster,attack],['cloneu'],
];
const snapshot=m=>({state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace())});
let cases=0;
for(let seed=1;seed<=32;seed++)for(const [name,...args]of actions){
 const label=name+':seed='+seed;
 for(const m of modules){m._probe_reset();m._probe_option(48,seed);m._probe_option(49,1);}
 const services=servicesByModule.get(implementation);if(services)getMhituState(services).mon_currwep=0;
 const stacks=modules.map(m=>m._probe_stack());
 const values=modules.map(m=>m['_probe_call_'+name](...args.map(arg=>typeof arg==='function'?arg(m):arg)));
 if(['mswings_verb','mpoisons_subj'].includes(name))assert.equal(text(implementation,values[1]),text(reference,values[0]),label+' returned text');
 else if(['cloneu','getmattk'].includes(name))assert.equal(implementation._probe_canonical(values[1]),reference._probe_canonical(values[0]),label+' returned pointer identity');
 else assert.equal(values[1],values[0],label+' return');
 assert.deepEqual(snapshot(implementation),snapshot(reference),label+' full state/trace');
 assert.deepEqual(modules.map(m=>m._probe_stack()),stacks,label+' restored stacks');
 const current=servicesByModule.get(implementation);
 if(current)assert.equal(implementation._probe_canonical(BigInt(getMhituState(current).mon_currwep)),reference._probe_static(),label+' module static');
 assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);cases++;
}
console.log('PASS: MHITU '+cases+' original-C/pure-JS state, trace, return/pointer, stack, context and module-static cases across30 routines and32 seeds.');
