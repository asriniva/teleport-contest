import {parseCPrototype} from '../js/c-runtime/prototypes.js';
// All generated entry signatures/plans plus observed actual MAIN execution.
import fs from 'node:fs';import assert from 'node:assert/strict';import {parse} from 'acorn';
import {bindNativeAddressEntry,prepareNativeAddressText} from '../js/nethack/native/address-entries.js';
import {createServiceForwarder,serviceScopeFor} from '../js/c-runtime/service-scope.js';
import {runStandaloneProgram} from './run-standalone-program.mjs';
import {nativeStateFor} from '../js/nethack/native/state-bridge.js';
const ports=JSON.parse(fs.readFileSync('js/nethack/address-ports.json')).ports;ports.cmd={schema:JSON.parse(fs.readFileSync('js/nethack/command-abi.json')).schema};
let runtime,checks=0,entries=0,textArguments=0,addressGetters=0;const eq=(a,b,label)=>{assert.deepEqual(a,b,label);checks++;};
const result=runStandaloneProgram(process.env.STANDALONE_ORIGINAL_ASSETS??'.cache/full-original-c-v1/assets',{seed:1,timezone:'UTC',options:'OPTIONS=!news\n',keys:'  nl.Fyy ',observeRuntime:r=>runtime=r});eq(result.status.kind,'input-exhausted','actual complete turns');
const env=runtime.environment,owner=nativeStateFor(env),byPort={};
const publicEntry=env.start('cmd').namespace.rhack;
eq(publicEntry.nativeValuesEntry.nativeExecutionState.ready,true,'actual command owner prepared');
eq(env.start('cmd').environment.nativeFixedProvider,true,'actual command uses its permanent services');
eq(publicEntry.nativeValuesEntry.nativeExecutionState.scope,undefined,'permanent command services need no forwarding scope');
let readyOwners=0;
for(const [port,{schema}]of Object.entries(ports)){
 const sourceTypes=JSON.parse(fs.readFileSync('nethack-c/wasm/tu-fragments/'+port+'-schema.json')).functionTypes;
 const source=fs.readFileSync('js/ported/'+port+'.js','utf8'),ast=parse(source,{ecmaVersion:'latest',sourceType:'module'}),functions=ast.body.filter(n=>n.type==='ExportNamedDeclaration'&&n.declaration?.type==='FunctionDeclaration'&&!/StaticInitializers$/.test(n.declaration.id.name)).map(n=>n.declaration);
 let actual;for(const fn of Object.values(env.start(port).namespace)){if(fn?.nativeValuesEntry?.nativeExecutionState?.ready){actual=fn.nativeValuesEntry.nativeExecutionState;break;}}if(actual)readyOwners++;
 const primary=env.start(port).environment,scope={services:primary},localOwner={depth:1};
 for(const fn of functions){
  const name=fn.id.name;if(fn.params.some(p=>p.type!=='Identifier')||schema.functionTypes?.[name]?.includes('...'))continue;
  const argumentsIn=fn.params.map((_,i)=>i%2?{address:i+17}:i+17),expected=argumentsIn.map(v=>v?.address??v),events=[];
  const context=actual?.context??{ptr:v=>Number(v),i64:v=>BigInt.asIntN(64,BigInt(v)),u64:v=>BigInt.asUintN(64,BigInt(v))};
  if(port==='cmd'||port==='sp_lev')for(let i=0;i<expected.length;i++){const t=schema.sourceParameters[name][i].canonical;expected[i]=context[t==='long'?'i64':t==='unsigned long'?'u64':'ptr'](expected[i]);}
  const state={ready:true,scope,context,namespace:{[name]:(...values)=>{events.push(['native',values]);return 0;}}},legacy=(...values)=>{events.push(['legacy',values]);return 'legacy';};
  const entry=bindNativeAddressEntry(port,name,state,localOwner,primary,legacy,(_n,_i,v)=>v);
  eq(typeof entry,'function','all source functions have a plan '+port+'.'+name);eq(entry.length,fn.params.length,'fixed arity '+port+'.'+name);
  eq(entry(...argumentsIn),0,'native result '+port+'.'+name);eq(events.pop(),['native',expected],'ordered native arguments '+port+'.'+name);
  for(let i=0;i<argumentsIn.length;i++){let gets=0;const args=[...argumentsIn];args[i]={get address(){gets++;return i+17;}};eq(entry(...args),0);eq(gets,1,'one address read '+port+'.'+name+':'+i);eq(events.pop(),['native',expected]);addressGetters++;}
  const parameters=parseCPrototype(schema.functionTypes?.[name]??sourceTypes[name]).parameters;
  const textIndices=parameters.flatMap((type,i)=>/^(?:signed|unsigned)?char\*$/.test(env.ctypes.canonical(type).replace(/\s/g,''))?[i]:[]);
  for(const i of textIndices){const text='native text '+port+'.'+name+':'+i,literalEvents=[],pointer=9000+i,textServices=Object.create(primary);let lookups=0;
   Object.defineProperty(textServices,'literal',{get(){lookups++;return function(value){eq(this,textServices,'text helper receiver');literalEvents.push(value);return pointer;};}});
   const textState={ready:true,scope:{services:textServices},context,namespace:{[name]:(...values)=>{events.push(['native',values]);return 0;}}};
   const textEntry=bindNativeAddressEntry(port,name,textState,localOwner,textServices,legacy,(_n,index,value)=>textIndices.includes(index)&&typeof value==='string'?textServices.literal(value):value);
   const args=[...argumentsIn],values=[...expected];args[i]=text;values[i]=pointer;
   if(port==='cmd'||port==='sp_lev'){const t=schema.sourceParameters[name][i].canonical;values[i]=context[t==='long'?'i64':t==='unsigned long'?'u64':'ptr'](values[i]);}
   eq(textEntry(...args),0);eq(events.pop(),['native',values],'text pointer conversion '+port+'.'+name+':'+i);eq(literalEvents,[text]);eq(lookups,1,'one literal provider lookup');textArguments++;
   for(const textValue of [text,'']){
    const coldArgs=[...argumentsIn];coldArgs[i]=textValue;literalEvents.length=0;lookups=0;
    prepareNativeAddressText(port,name,coldArgs,textServices);
    eq(coldArgs[i],pointer,'cold text pointer conversion '+port+'.'+name+':'+i);eq(literalEvents,[textValue]);eq(lookups,1,'one cold literal provider lookup');
    for(let j=0;j<coldArgs.length;j++)if(j!==i)eq(coldArgs[j],argumentsIn[j],'unrelated cold argument retained');
   }
   const literalArgs=[...argumentsIn];literalArgs[i]=pointer;literalEvents.length=0;lookups=0;
   prepareNativeAddressText(port,name,literalArgs,textServices);eq(literalArgs[i],pointer,'cold pointer retained');eq(literalEvents,[]);eq(lookups,0);

  }

  state.ready=false;eq(entry(...argumentsIn),'legacy','cold path');eq(events.pop(),['legacy',argumentsIn],'cold args retained');state.ready=true;
  scope.services={foreign:true};eq(entry(...argumentsIn),'legacy','foreign scope path');eq(events.pop(),['legacy',argumentsIn],'foreign args retained');scope.services=primary;
  localOwner.depth=0;eq(entry(...argumentsIn),'legacy','outside native scope');eq(events.pop(),['legacy',argumentsIn],'outside args retained');localOwner.depth=1;
  eq(entry(...argumentsIn,99),'legacy','extra arguments stay compatible');eq(events.pop(),['legacy',[...argumentsIn,99]],'extra args retained');
  state.namespace[name]=()=>{throw Error('native entry failure');};assert.throws(()=>entry(...argumentsIn),/native entry failure/);checks++;eq(localOwner.depth,1,'throw preserves owner');eq(scope.services,primary,'throw preserves provider');entries++;
 }
 byPort[port]=functions.length;
}
// Exercise the real ABI wrapper's hot dispatch and recursion guards without
// performing another game command: substitute only this component's core body.
const execution=publicEntry.nativeValuesEntry.nativeExecutionState,originalNamespace=execution.namespace,originalContextNamespace=execution.context.nativeNamespace;
const calls=[];const fake={rhack:(...values)=>{calls.push(values);return 23;}};
const position=env.transport.stackPosition();owner.enter();
try{
 execution.namespace=fake;execution.context.nativeNamespace=fake;
 const args=Array(publicEntry.nativeValuesEntry.length).fill(0);
 eq(publicEntry(...args),23,'actual registered ABI wrapper reaches direct core');
 eq(calls.pop(),args,'actual direct core arguments');
 assert.throws(()=>publicEntry(...args,99),TypeError,'mismatched arity reaches checked legacy path without recursion');checks++;
 eq(owner.depth,1,'ABI wrapper and errors preserve owner');
}finally{execution.namespace=originalNamespace;execution.context.nativeNamespace=originalContextNamespace;owner.leave();}
eq(env.transport.stackPosition(),position,'actual wrapper restores stack position');
const state={services:{value:1}},forwarding=createServiceForwarder(state);eq(serviceScopeFor(forwarding),state,'explicit provider identity');eq(forwarding.value,1,'primary forwarding');const first=state.services;try{state.services={value:2};eq(forwarding.value,2,'nested provider live');}finally{state.services=first;}eq(forwarding.value,1,'nested provider restored');
const evidence={passed:true,entries,checks,textArguments,addressGetters,readyOwners,byPort,scope:'All original fixed entry arities and ordered plans, cold/foreign/outside/extra-argument fallbacks, exception/provider preservation, explicit forwarding identities, actual MAIN command owner and ordinary walk/wait/attack assembly. Plans are controlled component probes; C gameplay and public recording comparisons are separate.'};fs.mkdirSync('.cache/native-address-entries',{recursive:true});fs.writeFileSync('.cache/native-address-entries/evidence.json',JSON.stringify(evidence,null,2));console.log(JSON.stringify(evidence));
