// Exercise native game state/execution against the existing independent C
// matrices. The fixture exposes its real production memory environment.
import {nativeStateFor} from '../js/nethack/native/state-bridge.js';
import {createNativeRecordViews} from '../js/nethack/native/record-views.js';
export function nativeFixtureServices(services,schemas){
 const environment=services.moduleKey.environment;
 if(!environment?.memory?.onGrow)throw new Error('Native matrix requires the production fixture memory owner');
 createNativeRecordViews(environment);
 const owner=nativeStateFor(environment),local=Object.create(services);
 local.nativeOwner=owner;
 local.nativeRecordLayouts=Object.fromEntries(Object.values(schemas).map(row=>[row.ctype.replace(/^(struct |union )/,''),environment.ctypes.record(row.ctype)]));
 return {owner,services:local};
}
export function nativeFixtureCall(owner,services,fn,...args){
 const saved=services.stackSave();owner.enter();
 try{return fn(...args);}finally{try{owner.leave();}finally{services.stackRestore(saved);}}
}
