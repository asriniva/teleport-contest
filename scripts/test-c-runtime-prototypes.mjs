import {createSignals} from '../js/nethack/signals.js';
import assert from 'node:assert/strict';import fs from 'node:fs';
import {parseCPrototype,splitCParameters} from '../js/c-runtime/prototypes.js';
import {createStandaloneEnvironment} from '../js/nethack/environment.js';
import {createFunctions} from '../js/c-runtime/functions.js';import {createLinker} from '../js/c-runtime/linker.js';
import catalog from '../js/nethack/public-functions.json' with {type:'json'};
let checks=0;
for(const name of ['signal','sigset']){
 assert.deepEqual(parseCPrototype(catalog.functions[name]),{result:'void (*)(int)',parameters:['int','void (*)(int)']});checks++;
}
assert.deepEqual(parseCPrototype('int (void (*)(void))'),{result:'int',parameters:['void (*)(void)']});checks++;
assert.deepEqual(parseCPrototype('void (int (*)[3], int (*)(int, void (*)(int)))'),{result:'void',parameters:['int (*)[3]','int (*)(int, void (*)(int))']});checks++;
assert.deepEqual(splitCParameters('void'),[]);checks++;
assert.deepEqual(parseCPrototype('void (* (int) ) (int)'),{result:'void (*)(int)',parameters:['int']});checks++;
for(const type of ['void (int','void (int))','void (int,,char *)','void (*(int))(int','void (int[3)']){assert.throws(()=>parseCPrototype(type));checks++;}
const env=createStandaloneEnvironment(),functions=createFunctions(),services={},seen=[];
const prototypes={signal:catalog.functions.signal,sigset:catalog.functions.sigset,qsort:catalog.functions.qsort,divide:'div_t (int, int)',extended:'long double (void)',variadic:'int (const char *, ...)'};
const linker=createLinker({memory:env.memory,transport:env.transport,functions,services,ctypes:env.ctypes,prototypes,withEnvironment:(_env,fn,...args)=>fn(...args)});
let handler=0n;
linker.register('test-signals',{signal:(number,next)=>{seen.push(number);const previous=handler;handler=next;return previous;},sigset:(number,next)=>{seen.push(number);const previous=handler;handler=next;return previous;},qsort:(base,count,size,compare)=>{seen.push(functions.indirect(compare,'ipp',base,base+Number(size)));},divide:()=>0,extended:()=>0,variadic:()=>0});
const callback=functions.functionPointer(number=>{seen.push(number);},'vi');
assert.equal(functions.indirect(services.signal.address,'pip',2,callback),0n);checks++;
const previous=functions.indirect(services.sigset.address,'pip',3,0n);assert.equal(previous,callback);checks++;
functions.indirect(previous,'vi',4);assert.deepEqual(seen,[2,3,4]);checks++;
const compare=functions.functionPointer((a,b)=>a-b,'ipp');functions.indirect(services.qsort.address,'vpjjp',32,2n,8n,compare);assert.equal(seen.at(-1),-8);checks++;
assert.throws(()=>functions.indirect(services.signal.address,'vp',0),/incompatible/);checks++;
assert.throws(()=>services.divide.address,/aggregate callback/);checks++;
assert.throws(()=>services.extended.address,/extended scalar callback/);checks++;
assert.throws(()=>services.variadic.address,/Variadic C callback/);checks++;
const signals=createSignals(env);env.register('production-signals',signals.api);let delivered=0;
const productionHandler=env.functions.functionPointer(number=>{delivered+=number;},'vi');
assert.equal(env.functions.indirect(env.services.signal.address,'pip',2,productionHandler),0n);checks++;
signals.raise(2);assert.equal(delivered,2);checks++;
const returned=env.functions.indirect(env.services.signal.address,'pip',2,0n);assert.equal(returned,productionHandler);checks++;
env.functions.indirect(returned,'vi',3);assert.equal(delivered,5);checks++;
let parsed=0;for(const type of Object.values(catalog.functions)){const row=parseCPrototype(type);assert.ok(row.result);parsed++;}
console.log(JSON.stringify({passed:true,checks,publicDeclarations:parsed,returnedCallbackDispatch:true}));
