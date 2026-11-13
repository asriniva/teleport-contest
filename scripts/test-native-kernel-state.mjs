// Exercise canonical fields through the same live-game providers as gameplay.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import {runStandaloneProgram} from './run-standalone-program.mjs';
import {nativeStateFor} from '../js/nethack/native/state-bridge.js';
import {createNativeAddressFields,compileNativeFieldPlans} from '../js/nethack/native/address-fields.js';
import {createScalarAdapter,createImmutableFieldMetadata} from '../js/c-runtime/adapter-factories.js';
import {createAddressBindings} from '../js/c-runtime/address-bindings.js';
import {installDirectDisplayFields} from '../js/nethack/bindings/display-direct.js';
const reference='.cache/full-original-c-v1',input=JSON.parse(fs.readFileSync(reference+'/scenarios/death.json'));
let runtime;
const result=runStandaloneProgram(reference+'/assets',{...input,keys:input.keys.slice(0,256),observeRuntime:r=>{runtime=r;}});
assert.deepEqual(result.status,{kind:'input-exhausted'});
const game=runtime.environment,owner=nativeStateFor(game),memory=game.memory;
assert.ok(owner.nativeArena);assert.ok(owner.nativeKernels.has('display'));assert.ok(owner.nativeKernels.has('mklev'));
const gameKernels=[...owner.nativeKernels].sort();
const hero=owner.records.get('struct you:'+game.requireGlobal('u'));
const monster=owner.records.get('struct monst:'+game.address(game.ctypes.getField('dlevel_t',game.requireGlobal('svl')+game.ctypes.fieldAddress('struct instance_globals_saved_l',0,'level'),'monlist','struct monst *')));
assert.ok(hero&&monster);
const mapCell=[...owner.records.entries()].find(([key])=>key.startsWith('struct rm:'))[1];
const schema={schema:{monst:{ctype:'struct monst',fields:[{name:'mhp',canonical:'int'},{name:'mx',canonical:'short'}]},you:{ctype:'struct you',fields:[{name:'ux',canonical:'short'},{name:'ustuck',canonical:'struct monst *'}]},gv:{ctype:'struct instance_globals_v',fields:[{name:'vision_full_recalc',canonical:'signed char'}]},rm:{ctype:'struct rm',fields:[{name:'lit',canonical:'unsigned int',bit:true}]}},globals:[]};
const plans=compileNativeFieldPlans(game,schema),services={nativeOwner:owner,nativeModuleName:'_unit',nativeFieldPlans:plans,heap:()=>memory.HEAPU8,read:(k,p,i)=>plans[k][i].read(p),write:(k,p,i,v)=>plans[k][i].write(p,v),address:(k,p,i)=>plans[k][i].address(p)};
const {env,decode}=createScalarAdapter(services,{},schema,game.address,{profile:'cached-fields',errors:['scalar ','cell ','field '],fieldMetadata:createImmutableFieldMetadata(schema)});
const hpAt=game.ctypes.fieldAddress('struct monst',monster.address,'mhp'),uxAt=game.ctypes.fieldAddress('struct you',hero.address,'ux');
env.foreignRead=function(){assert.equal(this,env);assert.equal(owner.depth,0);return memory.view.getInt32(hpAt,true);};
env.foreignFailure=function(){assert.equal(owner.depth,0);memory.view.setInt32(hpAt,19,true);throw Error('foreign failure');};
installDirectDisplayFields(env,()=>memory.view,game.address);
const fields=createNativeAddressFields(env,services,schema,decode,game.address);
const old={hp:monster.mhp,mx:monster.mx,ux:hero.ux,stuck:hero.ustuck,lit:mapCell.lit};
const nextHP=old.hp===17?16:17,nextUX=old.ux===1?2:1;
owner.enter();
try {
 fields.writers[0](monster.address,nextHP);
 assert.equal(monster.mhp,nextHP);assert.equal(fields.readers[0](monster.address),nextHP);
 assert.equal(owner.nativeArena.Int32[hpAt/4],nextHP,'canonical health is a native typed-array element');
 owner.nativeArena.Int32[hpAt/4]=nextHP+1;assert.equal(monster.mhp,nextHP+1);fields.writers[0](monster.address,nextHP);
 assert.equal(fields.writers[1](monster.address,65537),65537,'assignment preserves the original RHS');
 assert.equal(monster.mx,1);assert.equal(fields.readers[1](monster.address),1);monster.mx=old.mx;
 fields.writers[2](hero.address,nextUX);assert.equal(env.display_read_you_ux(hero.address),nextUX);
 assert.equal(owner.nativeArena.Int16[uxAt/2],nextUX,'direct display reads consume the same typed coordinates');
 fields.writers[3](hero.address,monster.address);assert.equal(hero.ustuck,monster);assert.equal(fields.readers[3](hero.address),monster.address);
 const packed=(1n<<60n)|BigInt(old.lit?0:1);fields.writers[5](mapCell.address,packed);assert.equal(mapCell.lit,old.lit?0:1);assert.equal(game.ctypes.getField('struct rm',mapCell.address,'lit','unsigned int'),old.lit?0:1,'wide packed writes preserve low bits in shared storage');mapCell.lit=old.lit;
 assert.equal(env.foreignRead(),nextHP,'foreign helpers publish before reading bytes');assert.equal(owner.depth,1);
 fields.writers[0](monster.address,18);assert.equal(env.cell(hpAt,'int').value,18,'addressable cell reads publish');
 env.cell(hpAt,'int').value=20;assert.equal(monster.mhp,20,'cell writes invalidate native fields');
 assert.throws(()=>env.foreignFailure(),/foreign failure/);assert.equal(owner.depth,1);assert.equal(monster.mhp,19);
 assert.throws(()=>env.display_read_you_ux(0),RangeError,'direct display bounds guards survive native lowering');
 // Logger-only capability retains dirty actor state; replacing a service with
 // ordinary byte-consuming code restores the foreign boundary automatically.
 const dependency={ret:'int',params:[]};
 const binding=createAddressBindings({environment:game,name:'_unit',schema:{schema:{},globals:[],dependencies:{_native_kernel_probe:dependency}},layout:[],namespace:{},backings:[],publicFunctions:{functions:{}},nativeOwner:owner});
 game.services._native_kernel_probe=()=>{assert.equal(owner.depth,1);return 7;};
 Object.defineProperty(game.services._native_kernel_probe,'nativeStateIndependent',{value:true});
 monster.mhp=21;assert.equal(binding.services._native_kernel_probe(),7);assert.equal(memory.view.getInt32(hpAt,true),21);
 game.services._native_kernel_probe=()=>{assert.equal(owner.depth,0);return memory.view.getInt32(hpAt,true);};
 assert.equal(binding.services._native_kernel_probe(),21);assert.equal(owner.depth,1);
 const legacy=createAddressBindings({environment:game,name:'_unit_legacy',schema:{schema:{},globals:[],dependencies:{_native_kernel_probe:dependency}},layout:[],namespace:{},backings:[],publicFunctions:{functions:{}}});
 game.services._native_kernel_probe=()=>1;dependency.ret='unsigned long';assert.equal(legacy.services._native_kernel_probe(),1n,'legacy mutable return metadata remains live');
 const wide=0x1000000000000001n;
 assert.equal(fields.writers[0](monster.address,wide),wide);assert.equal(monster.mhp,1,'wide integer writes retain low bits before native normalization');
 assert.equal(fields.writers[0](monster.address,'17'),'17');assert.equal(monster.mhp,17,'numeric string coercion occurs before a native setter');
 for(const invalid of [undefined,NaN,Infinity,1.5])assert.throws(()=>fields.writers[0](monster.address,invalid));
 assert.equal(monster.mhp,17,'failed coercions retain the prior native mutation');
 const stuckAt=game.ctypes.fieldAddress('struct you',hero.address,'ustuck');
 const opaque=0xa5abcdef12345678n;
 assert.equal(fields.writers[3](hero.address,opaque),opaque);assert.equal(memory.view.getBigUint64(stuckAt,true),opaque,'opaque pointer bits use the exact byte boundary');
 hero.ustuck=old.stuck;
 binding.services._native_kernel_probe=()=>11;assert.equal(binding.services._native_kernel_probe(),11,'local dependency replacement remains writable');
 delete game.services._native_kernel_probe;
} finally {monster.mhp=old.hp;monster.mx=old.mx;hero.ux=old.ux;hero.ustuck=old.stuck;mapCell.lit=old.lit;owner.leave();}
assert.equal(owner.depth,0);assert.equal(owner.dirty.size,0);
// Native reads consume typed state directly, even before a projection exists.
const freshMon=memory.calloc(1,game.ctypes.size('struct monst')+1)+1,freshHero=memory.calloc(1,game.ctypes.size('struct you'));
game.ctypes.setField('struct monst',freshMon,'mhp','int',31);game.ctypes.setField('struct monst',freshMon,'mx','short',5);
game.ctypes.setField('struct you',freshHero,'ux','short',7);game.ctypes.setField('struct you',freshHero,'ustuck','struct monst *',BigInt(freshMon));
const recordsBefore=owner.records.size;assert.ok(!Object.hasOwn(owner.records,'get'));
owner.records.get=()=>{throw Error('native field read rebuilt a record');};
try{
 assert.equal(fields.readers[0](freshMon),31);assert.equal(fields.readers[1](freshMon),5);assert.equal(fields.readers[2](freshHero),7);assert.equal(fields.readers[3](freshHero),freshMon);
 memory.grow(memory.buffer.byteLength+1);assert.equal(fields.readers[0](freshMon),31);assert.equal(fields.readers[3](freshHero),freshMon);
 assert.equal(owner.records.size,recordsBefore,'typed reads retain handles without materializing record wrappers');
}finally{delete owner.records.get;}
console.log(JSON.stringify({passed:true,gameKernels,canonicalFields:true,displayNativeReads:true,byteAliases:true,foreignReentry:true,exceptions:true,serviceReplacement:true,legacyMutableMetadata:true,directTypedReads:true,unalignedReads:true,growth:true,noReadProjection:true}));
