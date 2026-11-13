// Exercise production adapter services, rather than fixture callback substitutes.
import './pure-js-probes/deny-wasm.mjs';
import assert from 'node:assert/strict';
import fs from 'node:fs';
import {createStandaloneProgram} from '../js/nethack/program.js';
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json'));
const {environment:env}=createStandaloneProgram({layouts,readKey(){throw Error('Unexpected input');}});
const owners=[
 ['UHITM',env.enableUhitm(layouts),['display_nhwindow','nh_delay_output']],
 ['APPLY',env.enableApply(layouts),['create_nhwindow','start_menu','end_menu','destroy_nhwindow']],
 ['ENGRAVE',env.enableEngrave(layouts),['getlin']],
 ['LIGHT',env.enableLight(layouts),['create_nhwindow','putstr','display_nhwindow','destroy_nhwindow']],
 ['COLORATT',env.enableColorAttributes(layouts),['create_nhwindow','start_menu','end_menu','destroy_nhwindow']],
 ['SHKNAM',env.enableShknam(layouts),['display_nhwindow']],
 ['O_INIT',{services:env.start('object-state').environment},['wait_synch']],
];
const pointer=env.services.literal('production binding probe'),output=env.memory.calloc(128,1);
const contracts={
 create_nhwindow:{field:'win_create_nhwindow',signature:'ii',values:mode=>({args:[mode?4294967299:0],expected:[mode?3:0]})},
 destroy_nhwindow:{field:'win_destroy_nhwindow',signature:'vi',values:mode=>({args:[mode?-1:0],expected:[mode?-1:0]})},
 display_nhwindow:{field:'win_display_nhwindow',signature:'vii',values:mode=>({args:[mode?4294967313:0,mode?257:0],expected:[mode?17:0,mode?1:0]})},
 nh_delay_output:{field:'win_delay_output',signature:'v',values:()=>({args:[],expected:[]})},
 wait_synch:{field:'win_wait_synch',signature:'v',values:()=>({args:[],expected:[]})},
 start_menu:{field:'win_start_menu',signature:'vij',values:mode=>({args:[17,mode?(1n<<63n)|7n:0n],expected:[17,mode?(1n<<63n)|7n:0n]})},
 end_menu:{field:'win_end_menu',signature:'vip',values:mode=>({args:[17,mode?pointer:0],expected:[17,mode?pointer:0]})},
 putstr:{field:'win_putstr',signature:'viip',values:mode=>({args:[17,2,mode?pointer:0],expected:[17,2,mode?pointer:0]})},
 getlin:{field:'win_getlin',signature:'vpp',values:mode=>({args:[mode?pointer:0,output],expected:[mode?pointer:0,output]})},
};
let bindings=0,dispatches=0,rejections=0,growths=0;
for(const [name,owner,methods]of owners)for(const method of methods){
 const contract=contracts[method],at=env.ctypes.locate('struct window_procs',env.requireGlobal('windowprocs'),contract.field).at;
 const original=env.memory.view.getBigUint64(at,true),stack=env.transport.stackSave();
 try{
  for(const mode of [0,1]){
   const {args,expected}=contract.values(mode),seen=[];
   const result=phase=>contract.signature[0]==='v'?undefined:7+phase;
   const second=env.functions.functionPointer((...values)=>{seen.push(['second',values]);return result(1);},contract.signature);
   const first=env.functions.functionPointer((...values)=>{
    seen.push(['first',values]);
    if(!growths&&mode===1){const buffer=env.memory.buffer;assert.equal(env.memory.grow(buffer.byteLength+16),true,'verified callback-time growth');assert.notEqual(env.memory.buffer,buffer);growths++;}
    env.memory.view.setBigUint64(at,second,true);return result(0);
   },contract.signature);
   env.memory.view.setBigUint64(at,first,true);
   assert.equal(owner.services[method](...args),result(0),name+'.'+method+' first return');
   assert.equal(owner.services[method](...args),result(1),name+'.'+method+' replacement return');
   assert.deepEqual(seen,[['first',expected],['second',expected]],name+'.'+method+' measured arguments and live replacement');
   const after=env.transport.stackSave();
   assert.equal(after.index,stack.index,name+'.'+method+' stack depth');env.transport.stackRestore(after);dispatches+=2;
  }
  const {args}=contract.values(1);
  const incompatible=env.functions.functionPointer(()=>0,contract.signature==='v'?'i':'v');
  for(const pointer of [0n,incompatible]){
   env.memory.view.setBigUint64(at,pointer,true);
   assert.throws(()=>owner.services[method](...args),/Unknown or incompatible C callback/,name+'.'+method+' rejects invalid live pointer');rejections++;
  }
 }finally{env.memory.view.setBigUint64(at,original,true);env.transport.stackRestore(stack);}
 bindings++;
}
assert.equal(bindings,17);assert.equal(dispatches,68);assert.equal(rejections,34);assert.equal(growths,1);
console.log('PASS: '+bindings+' production window bindings across7 owners, '+dispatches+' live dispatches, '+rejections+' invalid-pointer/signature rejections, verified callback-time growth, replacement, integer/boolean narrowing, full-width menu flags, pointers and stack preservation.');
