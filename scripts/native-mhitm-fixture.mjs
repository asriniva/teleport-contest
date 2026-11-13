// Exercise real native actor storage/execution against the retained C fixtures.
import {createMhitmEnvironment,prepareMhitmArguments} from '../js/nethack/bindings/mhitm.js';
import {createNativeMonsterCombat} from '../js/nethack/native/mhitm.js';
import {nativeFixtureServices,nativeFixtureCall} from './native-pet-combat-fixture.mjs';
export function nativeMhitmFixture(layout){
 const contexts=new WeakMap();
 return (services,name,...args)=>{
  let entry=contexts.get(services.moduleKey);
  if(!entry){const connected=nativeFixtureServices(services,{}),env=createMhitmEnvironment(connected.services,layout);entry={...connected,env,native:createNativeMonsterCombat(env)};contexts.set(services.moduleKey,entry);}
  return nativeFixtureCall(entry.owner,entry.services,entry.native[name],...prepareMhitmArguments(entry.env,name,args));
 };
}
