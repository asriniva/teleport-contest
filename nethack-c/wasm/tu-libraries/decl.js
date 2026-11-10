// DECL typed storage/startup transport. Original initializer values and reset policy are JavaScript.
addToLibrary({
 $teleportDeclServices__deps:['teleport_decl_storage','teleport_decl_public_address','teleport_decl_literal_storage','teleport_decl_literal_capacity','teleport_decl_raw_printf','teleport_decl_exit','$lengthBytesUTF8','$stringToUTF8'],
 $teleportDeclServices:function(){
  var cache=Module.teleportDeclLiterals||={next:0,strings:new Map()};
  var literal=s=>{if(cache.strings.has(s))return cache.strings.get(s);var size=lengthBytesUTF8(s)+1;if(cache.next+size>Number(_teleport_decl_literal_capacity()))throw Error('Review changed DECL literal capacity');var at=Number(_teleport_decl_literal_storage())+cache.next;stringToUTF8(s,at,size);cache.next+=size;cache.strings.set(s,at);return at;};
  var text=v=>BigInt(typeof v==='string'?literal(v):v?.address??v??0);
  return {moduleKey:Module,heap:()=>HEAPU8,literal,storage:i=>Number(_teleport_decl_storage(i)),publicAddress:i=>Number(_teleport_decl_public_address(i)),raw_printf:(fmt,name)=>_teleport_decl_raw_printf(text(fmt),text(name)),exit:code=>_teleport_decl_exit(Number(code)|0)};
 },
 $teleportDeclCall__deps:['$teleportDeclServices'],
 $teleportDeclCall:function(name,...args){return Module.nethackPorted.decl(teleportDeclServices(),name,...args);},
 $teleportDeclInit__deps:['$teleportDeclServices','$addOnInit'],
 $teleportDeclInit__postset:'addOnInit(() => Module.nethackPorted.initializeDecl(teleportDeclServices()));',
 $teleportDeclInit:function(){},
 program_state_init__deps:['$teleportDeclCall','$teleportDeclInit'],program_state_init__sig:'v',
 program_state_init:function(){teleportDeclCall('program_state_init');},
 decl_globals_init__deps:['$teleportDeclCall','$teleportDeclInit'],decl_globals_init__sig:'v',
 decl_globals_init:function(){teleportDeclCall('decl_globals_init');},
 sa_victual__deps:['$teleportDeclCall','$teleportDeclInit'],sa_victual__sig:'vp',
 sa_victual:function(value){teleportDeclCall('sa_victual',value);},
});
