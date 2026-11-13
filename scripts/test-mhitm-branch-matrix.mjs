// Additional valid fixture inputs; original C remains the behavior oracle.
import './pure-js-probes/deny-wasm.mjs';
import assert from 'node:assert/strict';
import path from 'node:path';
import {pathToFileURL} from 'node:url';
import {loadFixture} from './pure-js-fixtures/load.mjs';
import {callMhitm} from '../js/nethack/bindings/mhitm.js';
import {C,R,T} from '../js/c-runtime/context.js';

const url=kind=>pathToFileURL(path.resolve('.cache/tu-probes/mhitm-'+kind+'.mjs'));
const refFactory=(await loadFixture('mhitm',url('reference'))).default;
const jsFactory=(await loadFixture('mhitm',url('hybrid'))).default;
const reference=await refFactory(),layout={};
function text(m,p){let at=Number(p),end=at;while(m.HEAPU8[end])end++;return Buffer.from(m.HEAPU8.slice(at,end)).toString('latin1');}
for(let i=0;i<reference._probe_layout_count();i++)layout[text(reference,reference._probe_layout_name(i))]=Number(reference._probe_layout_value(i));
const implementation=await jsFactory({nethackPorted:{mhitm:(services,name,...args)=>callMhitm(services,layout,name,...args)}});
const modules=[reference,implementation],snapshot=m=>({state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace())});
let cases=0;
function compare(label,seed,op,type,damage){
 for(const m of modules){
  m._probe_reset();m._probe_seed(seed);m._probe_attack(0,type,damage,2,4);
  if(op===19)m._probe_form(1,layout.PM_HUMAN,layout.AT_NONE,damage,2,4);
 }
 const c=op===15?3:op===19?1:[17,18].includes(op)?0:-1;
 const e=[7,12,14,15,20].includes(op)?7:0;
 const stacks=modules.map(m=>m._probe_stack()),results=modules.map(m=>m._probe_action(op,0,1,c,e));
 assert.equal(results[1],results[0],label+' return');
 assert.deepEqual(snapshot(implementation),snapshot(reference),label+' full state/trace');
 assert.deepEqual(modules.map(m=>m._probe_stack()),stacks,label+' restored stacks');
 assert.equal(C,undefined,label+' C context restored');assert.equal(R,undefined);assert.equal(T,undefined);cases++;
}
for(let seed=1;seed<=32;seed++)for(let op=0;op<22;op++)compare('routine='+op+',seed='+seed,seed,op,layout.AT_CLAW,layout.AD_PHYS);
const configurations=[
 ['AT_CLAW','AD_PHYS'],['AT_BITE','AD_PHYS'],['AT_HUGS','AD_WRAP'],
 ['AT_TUCH','AD_ACID'],['AT_STNG','AD_STUN'],['AT_GAZE','AD_STON'],
 ['AT_GAZE','AD_BLND'],['AT_ENGL','AD_DGST'],['AT_ENGL','AD_PHYS'],
 ['AT_EXPL','AD_FIRE'],['AT_EXPL','AD_COLD'],['AT_EXPL','AD_ELEC'],
];
for(const [attack,damage]of configurations){
 assert.ok(attack in layout,attack);assert.ok(damage in layout,damage);
 const ops=attack==='AT_EXPL'?[11,12]:attack==='AT_GAZE'?[8,12]:attack==='AT_ENGL'?[9,10,12]:[6,7,12,19];
 for(let seed=1;seed<=8;seed++)for(const op of ops)compare(attack+'/'+damage+',routine='+op+',seed='+seed,seed,op,layout[attack],layout[damage]);
}
console.log('PASS: MHITM '+cases+' original-C/pure-JS return, state, trace, stack and context cases across22 routines,32 routine seeds and12 attack configurations.');
