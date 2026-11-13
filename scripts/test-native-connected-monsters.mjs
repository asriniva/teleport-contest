// Live-main ownership and direct-dispatch checks, beyond isolated provider tests.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import {runStandaloneProgram} from './run-standalone-program.mjs';
import {enableMonsterLifecycle} from '../js/nethack/monster-lifecycle.js';
import {nativeStateFor} from '../js/nethack/native/state-bridge.js';
import {callVision} from '../js/nethack/bindings/vision.js';
import {C,withCEnvironment} from '../js/c-runtime/context.js';
const reference='.cache/full-original-c-v1';
const input=JSON.parse(fs.readFileSync(reference+'/scenarios/death.json'));
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json'));
let runtime;
const result=runStandaloneProgram(reference+'/assets',{...input,keys:input.keys.slice(0,256),observeRuntime:r=>{runtime=r;}});
assert.deepEqual(result.status,{kind:'input-exhausted'});
const {environment}=runtime,owner=nativeStateFor(environment);
const glyphs=environment.enableGlyphs(layouts),glyphContext=glyphs.context;
assert.ok(environment.enableGlyphs(layouts)===glyphs,'glyph initialization has one game owner');assert.ok(glyphs.context===glyphContext,'glyph calls retain one native context');
const glyphAbi=JSON.parse(fs.readFileSync('js/nethack/glyph-abi.json'));for(const g of [-2147483648,-2,-1,0,layouts.glyphs.GLYPH_CMAP_MAIN_OFF,layouts.glyphs.MAX_GLYPH,2147483647])for(const [i,name]of glyphAbi.headers.entries())assert.equal(glyphContext.env[name](g),glyphs.services.header(i,g),'native header wiring '+name);
for(const name of ['glyph_to_cmap','fill_glyphid_cache','glyphid_cache_status'])assert.ok(environment.services[name].nativeEntry===owner.functions.get(name),name+' has direct native dispatch');
const glyphMap=glyphContext.env.glyphmap[0];assert.ok(glyphMap===owner.nativeRecords.record('glyph_map',glyphMap.address),'glyph model and display share a native glyph map record');
assert.ok(glyphContext.env.mons[0]===owner.nativeRecords.record('struct permonst',environment.requireGlobal('mons')),'glyph lookup uses canonical monster species');
const unicodeAt=environment.memory.calloc(1,layouts.glyphs.unicodeSize),unicode=owner.nativeRecords.record('struct unicode_representation',unicodeAt),priorUnicode=glyphMap.u;
try{glyphMap.u=unicode;assert.ok(glyphContext.env.glyphmap[0].u===unicode);unicode.utf32ch=0x2603;assert.equal(glyphMap.u.utf32ch,0x2603);}finally{glyphMap.u=priorUnicode;environment.memory.free(unicodeAt);}
const find=glyphContext.env.glyphsState.to_custom_symbol_find,priorGlyphCallback=find.callback;
try{find.callback=glyphContext.native.to_custom_symset_entry_callback;assert.ok(find.callback===glyphContext.native.to_custom_symset_entry_callback);assert.equal(Number(glyphs.services.get(0,7,glyphs.finds+layouts.glyphs.findSize)),Number(glyphs.services.callbackAddress()));}finally{find.callback=priorGlyphCallback;}
const glyphMarker={nativeGlyphCaller:true},oldHeader=glyphContext.env.glyph_is_cmap_main,liveBeforeGlyph=environment.memory.live.size;
try{glyphContext.env.glyph_is_cmap_main=g=>{assert.equal(C,glyphMarker);return oldHeader(g);};withCEnvironment(glyphMarker,()=>assert.equal(environment.services.glyph_to_cmap(layouts.glyphs.GLYPH_CMAP_MAIN_OFF),layouts.glyphs.S_vwall));
 glyphContext.env.glyph_is_cmap_main=()=>{assert.equal(C,glyphMarker);environment.transport.stackAlloc(24);throw Error('native glyph cleanup');};withCEnvironment(glyphMarker,()=>assert.throws(()=>environment.services.glyph_to_cmap(layouts.glyphs.GLYPH_CMAP_MAIN_OFF),/native glyph cleanup/));
}finally{glyphContext.env.glyph_is_cmap_main=oldHeader;}
assert.equal(environment.memory.live.size,liveBeforeGlyph);assert.equal(owner.depth,0);
withCEnvironment(glyphMarker,()=>glyphContext.env.callFindCallback(()=>{assert.ok(C===glyphContext.env,'foreign glyph callbacks retain their C context');assert.equal(owner.depth,0);},0,find));

assert.equal(owner.depth,0,'input exhaustion publishes the entire connected native graph');
assert.equal(owner.dirty.size,0);
for(const name of ['movemon','mcalcdistress','healmon','mfndpos','dochugw','m_move','domove','lookaround','test_move','vision_recalc','clear_path','does_block','moveloop','moveloop_core','moveloop_preamble','stop_occupation','timet_to_seconds','timet_delta','dog_move','dog_eat','mattacku','magic_negation','getmattk']){
 assert.ok(owner.functions.has(name),name+' has native dispatch');
 assert.equal(owner.functions.get(name).nativeState,owner,name+' uses the common native owner');
}
const lifecycle=enableMonsterLifecycle(environment,layouts);
const vision=callVision({moduleKey:environment},layouts.vision,'environment');
const hero=owner.records.get('struct you:'+environment.requireGlobal('u'));assert.ok(hero);
const pets=environment.enableDogmove(layouts),attacks=environment.enableMhitu(layouts);
assert.equal(pets.context.u,hero);assert.equal(attacks.context.u,hero);
const combat=environment.enableMhitm(layouts);assert.equal(combat.context.u,hero);assert.equal(combat.context.levl[hero.ux][hero.uy],pets.context.levl[hero.ux][hero.uy],'combat and pets share canonical map cells across their array interfaces');
assert.ok(combat.services.healmon===owner.functions.get('healmon'),'combat calls native healing directly');
for(const name of ['mattackm','fightm','mdisplacem','sleep_monst'])assert.ok(environment.services[name].nativeEntry===owner.functions.get(name),name+' is published directly');
const combatActor=[...owner.records].find(([key])=>key.startsWith('struct monst:'))?.[1];assert.ok(combatActor);assert.equal(combat.context.monster(combatActor.address),combatActor);
assert.equal(combat.context.permonst(combatActor.data.address),combatActor.data);
const allActors=[...owner.records].filter(([key])=>key.startsWith('struct monst:')).map(([,value])=>value);assert.ok(allActors.length>1);
for(const field of ['mhp','mx','mcan']){const first=Object.getOwnPropertyDescriptor(allActors[0],field).get;assert.ok(allActors.every(actor=>Object.getOwnPropertyDescriptor(actor,field).get===first),'live monsters share '+field+' accessors');}

const priorKilled=owner.functions.get('monkilled'),stringMarker={nativeStringCaller:true};let stringChecks=0;
const killedProbe=(actor,why,how)=>{assert.ok(actor===combatActor);assert.ok(why,'an empty C string remains a non-null pointer');assert.equal(environment.memory.readString(why),'');assert.equal(how,7);assert.equal(C,stringMarker);stringChecks++;};killedProbe.nativeState=owner;
try{owner.functions.set('monkilled',killedProbe);withCEnvironment(stringMarker,()=>combat.services.monkilled(combatActor,'',7));assert.equal(stringChecks,1);}
finally{owner.functions.set('monkilled',priorKilled);}
const combatScopeCount=environment.memory.live.size,priorDistance=combat.context.mdistu;
try{combat.context.mdistu=()=>{environment.transport.stackAlloc(16);throw Error('native combat cleanup');};withCEnvironment(stringMarker,()=>assert.throws(()=>combat.call('noises',combatActor,0),/native combat cleanup/));}
finally{combat.context.mdistu=priorDistance;}
assert.equal(environment.memory.live.size,combatScopeCount);assert.equal(owner.depth,0);
assert.equal(pets.services.mfndpos,owner.functions.get('mfndpos'),'pet movement calls native candidate search directly');
const candidateAt=environment.memory.calloc(1,environment.ctypes.size('struct mfndposdata'));
try{const candidates=pets.context.view('mfndposdata',candidateAt);assert.equal(candidates.info.length,9);assert.equal(candidates.poss.length,9);}
finally{environment.memory.free(candidateAt);}
const petMarker={nativePetCaller:true};
withCEnvironment(petMarker,()=>{
 let distance=0;pets.context.do_clear_area(hero.ux,hero.uy,1,pets.native.wantdoor,{reference:true,type:'int',get:()=>distance,set:v=>{distance=v;}});
 assert.equal(distance,0);assert.equal(C,petMarker,'native search callbacks retain caller context');
 const object=[...owner.records].find(([key])=>key.startsWith('struct obj:'))?.[1];assert.ok(object);
 const previous=attacks.context.mon_currwep;
 try{attacks.context.mon_currwep=object;assert.equal(attacks.context.mon_currwep,object);}
 finally{attacks.context.mon_currwep=previous;}
 assert.equal(C,petMarker);
});
assert.equal(environment.transport.scoped(()=>hero),hero,'canonical records remain synchronous values across legacy scopes');
assert.equal(hero.table,undefined,'legacy table probes observe ordinary missing JS properties on complete records');
assert.equal(hero.then,undefined,'complete records are not promises');
owner.completeRecordTypes.delete('struct you');
try{assert.throws(()=>hero.table,/Unknown HACK record field/,'partial legacy projections retain their unknown-field guard');}
finally{owner.completeRecordTypes.add('struct you');}
const turn=environment.state('game-startup-context');
const savedNativeTurn=turn.nativeTurn,dispatchMarker={nativeLinkerCaller:true};
turn.nativeTurn=fn=>{assert.equal(C,dispatchMarker,'published native calls do not switch the caller environment');return savedNativeTurn(fn);};
try{withCEnvironment(dispatchMarker,()=>{
 assert.equal(environment.services.timet_delta(10n,4n),6n);
 assert.equal(environment.resolve('timet_to_seconds')(10n),10n);
 assert.equal(environment.call('game-startup','timet_delta',10n,4n),6n);
});}finally{turn.nativeTurn=savedNativeTurn;}
assert.equal(environment.services.m_move.nativeEntry,owner.functions.get('m_move'));
for(const name of ['domove','lookaround','test_move','money_cnt'])assert.ok(environment.services[name].nativeEntry===owner.functions.get(name),name+' is published as direct native movement');
const movementMarker={nativeMovementCaller:true},priorStackSave=environment.services.stackSave;let movementStackChecks=0;
try{environment.services.stackSave=()=>{assert.equal(C,movementMarker,'published native movement retains the caller environment');movementStackChecks++;return priorStackSave();};withCEnvironment(movementMarker,()=>assert.equal(environment.services.money_cnt(0),0n));assert.ok(movementStackChecks>0);}
finally{environment.services.stackSave=priorStackSave;}

assert.equal(environment.services.movemon.nativeEntry,owner.functions.get('movemon'));
assert.equal(turn.u,hero,'turn loop consumes the canonical hero');
assert.equal(turn.movemon,owner.functions.get('movemon'),'turn dependencies call the native engine directly');
assert.equal(environment.services.moveloop_core.nativeEntry,owner.functions.get('moveloop_core'));
assert.equal(turn.u.uprops[1],owner.records.get('struct prop:'+turn.u.uprops[1].address));
const temporaryCount=environment.memory.live.size,scopeMarker={nativeTurnCaller:true};
withCEnvironment(scopeMarker,()=>{
 assert.throws(()=>turn.nativeTurn(()=>{assert.equal(C,scopeMarker,'native turn scopes do not switch the C environment');assert.equal(owner.depth,1);environment.transport.stackAlloc(32);throw Error('native turn cleanup');}),/native turn cleanup/);
 assert.equal(C,scopeMarker);
});
assert.equal(owner.depth,0);assert.equal(environment.memory.live.size,temporaryCount,'a completed or throwing turn frees its temporaries');
assert.equal(lifecycle.context.u,hero,'hero has one identity across native providers');
assert.equal(vision.u,hero,'visibility consumes the canonical hero');
assert.equal(vision.levl[hero.ux][hero.uy],lifecycle.context.levl[hero.ux][hero.uy],'visibility and movement use the same map cell');
const marker={nativeVisibilityCaller:true};
withCEnvironment(marker,()=>{owner.functions.get('get_viz_clear')(1,1);assert.equal(C,marker,'native visibility retains caller context');});
for(const provider of owner.providers){const read=provider.get('struct you');if(read)assert.equal(read(hero.address),hero);}
const recalc=vision.gv.vision_full_recalc;
owner.enter();
assert.equal(lifecycle.context.gv.vision_full_recalc,recalc);
vision.gv.vision_full_recalc=recalc?0:1;
assert.equal(lifecycle.context.gv.vision_full_recalc,recalc?0:1,'different global projections observe a native visibility write immediately');
lifecycle.context.gv.vision_full_recalc=recalc;
assert.equal(vision.gv.vision_full_recalc,recalc,'visibility sees a pending write through another native projection');
owner.leave();
let monsters=0;
for(const[key,monster]of owner.records){
 if(!key.startsWith('struct monst:'))continue;
 assert.equal(lifecycle.context.monster(monster.address),monster,'lifecycle keeps the shared identity');
 assert.equal(vision.view('monst',monster.address),monster,'visibility keeps the canonical monster');
 for(const provider of owner.providers){const read=provider.get('struct monst');if(read)assert.equal(read(monster.address),monster,'movement and lifecycle retain the same object');}
 // Includes retained dead/freed records: live fields must still read their byte
 // backing outside native execution, matching the established view contract.
 const hp=environment.memory.view.getInt32(Number(monster.address)+layouts.mon.mon_mhp,true);
 assert.equal(monster.mhp,hp);monsters++;
}
assert.ok(monsters>0);assert.ok(owner.nativeArena||owner.hits>0);
console.log(JSON.stringify({passed:true,monsters,nativeFunctions:owner.functions.size,nativeFields:owner.fields,nativeStorage:owner.nativeArena?'typed-arrays':'cached-fields',cachedReads:owner.hits,legacyBoundaries:owner.boundaries,moves:result.state.moves}));
