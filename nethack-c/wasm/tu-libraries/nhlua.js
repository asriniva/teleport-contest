// NHLUA typed foreign calls and callback dispatch, no game source policy.
addToLibrary({
$teleportNhluaServices__deps:["teleport_nhlua_storage", "teleport_nhlua_global", "teleport_nhlua_function_pointer", "teleport_nhlua_jump_scope", "teleport_nhlua_jump", "teleport_nhlua_literal_storage", "teleport_nhlua_literal_capacity", "teleport_nhlua_layout_count", "teleport_nhlua_layout_name", "teleport_nhlua_layout_value", "teleport_nhlua_api_0", "teleport_nhlua_api_1", "teleport_nhlua_api_2", "teleport_nhlua_api_3", "teleport_nhlua_api_4", "teleport_nhlua_api_5", "teleport_nhlua_api_6", "teleport_nhlua_api_7", "teleport_nhlua_api_8", "teleport_nhlua_api_9", "teleport_nhlua_api_10", "teleport_nhlua_api_11", "teleport_nhlua_api_12", "teleport_nhlua_api_13", "teleport_nhlua_api_14", "teleport_nhlua_api_15", "teleport_nhlua_api_16", "teleport_nhlua_api_17", "teleport_nhlua_api_18", "teleport_nhlua_api_19", "teleport_nhlua_api_20", "teleport_nhlua_api_21", "teleport_nhlua_api_22", "teleport_nhlua_api_23", "teleport_nhlua_api_24", "teleport_nhlua_api_25", "teleport_nhlua_api_26", "teleport_nhlua_api_27", "teleport_nhlua_api_28", "teleport_nhlua_api_29", "teleport_nhlua_api_30", "teleport_nhlua_api_31", "teleport_nhlua_api_32", "teleport_nhlua_api_33", "teleport_nhlua_api_34", "teleport_nhlua_api_35", "teleport_nhlua_api_36", "teleport_nhlua_api_37", "teleport_nhlua_api_38", "teleport_nhlua_api_39", "teleport_nhlua_api_40", "teleport_nhlua_api_41", "teleport_nhlua_api_42", "teleport_nhlua_api_43", "teleport_nhlua_api_44", "teleport_nhlua_api_45", "teleport_nhlua_api_46", "teleport_nhlua_api_47", "teleport_nhlua_api_48", "teleport_nhlua_api_49", "teleport_nhlua_api_50", "teleport_nhlua_api_51", "teleport_nhlua_api_52", "teleport_nhlua_api_53", "teleport_nhlua_api_54", "teleport_nhlua_api_55", "teleport_nhlua_api_56", "teleport_nhlua_api_57", "teleport_nhlua_api_58", "teleport_nhlua_api_59", "teleport_nhlua_api_60", "teleport_nhlua_api_61", "teleport_nhlua_api_62", "teleport_nhlua_api_63", "teleport_nhlua_api_64", "teleport_nhlua_api_65", "teleport_nhlua_api_66", "teleport_nhlua_api_67", "teleport_nhlua_api_68", "teleport_nhlua_api_69", "teleport_nhlua_api_70", "teleport_nhlua_api_71", "teleport_nhlua_api_72", "teleport_nhlua_api_73", "teleport_nhlua_api_74", "teleport_nhlua_api_75", "teleport_nhlua_api_76", "teleport_nhlua_api_77", "teleport_nhlua_api_78", "teleport_nhlua_api_79", "teleport_nhlua_api_80", "teleport_nhlua_api_81", "teleport_nhlua_api_82", "teleport_nhlua_api_83", "teleport_nhlua_api_84", "teleport_nhlua_api_85", "teleport_nhlua_api_86", "teleport_nhlua_api_87", "teleport_nhlua_api_88", "teleport_nhlua_api_89", "teleport_nhlua_api_90", "teleport_nhlua_api_91", "teleport_nhlua_api_92", "teleport_nhlua_api_93", "teleport_nhlua_api_94", "teleport_nhlua_api_95", "teleport_nhlua_api_96", "teleport_nhlua_api_97", "teleport_nhlua_api_98", "teleport_nhlua_api_99", "teleport_nhlua_api_100", "teleport_nhlua_api_101", "teleport_nhlua_api_102", "teleport_nhlua_api_103", "teleport_nhlua_api_104", "teleport_nhlua_api_105", "teleport_nhlua_api_106", "teleport_nhlua_api_107", "teleport_nhlua_api_108", "teleport_nhlua_api_109", "teleport_nhlua_api_110", "teleport_nhlua_api_111", "teleport_nhlua_api_112", "teleport_nhlua_api_113", "teleport_nhlua_api_114", "teleport_nhlua_api_115", "teleport_nhlua_api_116", "teleport_nhlua_api_117", "teleport_nhlua_api_118", "teleport_nhlua_api_119", "teleport_nhlua_api_120", "teleport_nhlua_api_121", "teleport_nhlua_api_122", "teleport_nhlua_api_123", "teleport_nhlua_api_124", "teleport_nhlua_api_125", "teleport_nhlua_api_126", "teleport_nhlua_api_127", "teleport_nhlua_api_128", "teleport_nhlua_api_129", "teleport_nhlua_api_130", "teleport_nhlua_api_131", "teleport_nhlua_api_132", "teleport_nhlua_api_133", "teleport_nhlua_api_134", "teleport_nhlua_api_135", "teleport_nhlua_api_136", "teleport_nhlua_api_137", "teleport_nhlua_api_138", "teleport_nhlua_api_139", "teleport_nhlua_api_140", "teleport_nhlua_api_141", "teleport_nhlua_api_142", "teleport_nhlua_api_143", "teleport_nhlua_api_144", "teleport_nhlua_api_145", "teleport_nhlua_api_146", "teleport_nhlua_api_147", "teleport_nhlua_api_148", "teleport_nhlua_api_149", "teleport_nhlua_api_150", "teleport_nhlua_api_151", "teleport_nhlua_api_152", "teleport_nhlua_api_153", "teleport_nhlua_api_154", "teleport_nhlua_api_155", "teleport_nhlua_api_156", "teleport_nhlua_api_157", "teleport_nhlua_api_158", "teleport_nhlua_api_159", "teleport_nhlua_api_160", "teleport_nhlua_api_161", "teleport_nhlua_api_162", "teleport_nhlua_api_163", "teleport_nhlua_api_164", "teleport_nhlua_api_165", "teleport_nhlua_api_166", "teleport_nhlua_api_167", "teleport_nhlua_api_168", "teleport_nhlua_api_169", "teleport_nhlua_api_170", "teleport_nhlua_api_171", "teleport_nhlua_api_172", "teleport_nhlua_api_173", "teleport_nhlua_api_174", "teleport_nhlua_api_175", "teleport_nhlua_api_176", "teleport_nhlua_api_177", "teleport_nhlua_api_178", "teleport_nhlua_api_179", "teleport_nhlua_api_180", "teleport_nhlua_api_181", "teleport_nhlua_api_182", "teleport_nhlua_api_183", "teleport_nhlua_api_184", "teleport_nhlua_api_185", "teleport_nhlua_api_186", "teleport_nhlua_api_187", "teleport_nhlua_api_188", "teleport_nhlua_api_189", "teleport_nhlua_api_190", "teleport_nhlua_api_191", "teleport_nhlua_api_192", "teleport_nhlua_api_193", "teleport_nhlua_api_194", "teleport_nhlua_api_195", "teleport_nhlua_api_196", "teleport_nhlua_api_197", "teleport_nhlua_api_198", "teleport_nhlua_api_199", "teleport_nhlua_api_200", "teleport_nhlua_api_201", "teleport_nhlua_api_202", "teleport_nhlua_api_203", "teleport_nhlua_api_204", "teleport_nhlua_api_205", "teleport_nhlua_api_206", "teleport_nhlua_api_207", "teleport_nhlua_api_208", "teleport_nhlua_api_209", "teleport_nhlua_api_210", "teleport_nhlua_api_211", "teleport_nhlua_api_212", "teleport_nhlua_api_213", "teleport_nhlua_api_214", "teleport_nhlua_api_215", "teleport_nhlua_api_216", "teleport_nhlua_api_217", "teleport_nhlua_api_218", "teleport_nhlua_api_219", "teleport_nhlua_api_220", "teleport_nhlua_api_221", "teleport_nhlua_api_222", "teleport_nhlua_api_223", "teleport_nhlua_api_224", "teleport_nhlua_api_225", "teleport_nhlua_api_226", "teleport_nhlua_api_227", "teleport_nhlua_api_228", "teleport_nhlua_api_229", "teleport_nhlua_api_230", "teleport_nhlua_api_231", "teleport_nhlua_api_232", "teleport_nhlua_api_233", "teleport_nhlua_api_234", "teleport_nhlua_api_235", "teleport_nhlua_api_236", "teleport_nhlua_api_237", "teleport_nhlua_api_238", "teleport_nhlua_api_239", "teleport_nhlua_api_240", "teleport_nhlua_api_241", "teleport_nhlua_api_242", "teleport_nhlua_api_243", "teleport_nhlua_api_244", "teleport_nhlua_api_245", "teleport_nhlua_api_246", "teleport_nhlua_api_247", "teleport_nhlua_api_248", "teleport_nhlua_api_249", "teleport_nhlua_api_250", "teleport_nhlua_api_251", "teleport_nhlua_api_252", "teleport_nhlua_api_253", "teleport_nhlua_api_254", "teleport_nhlua_api_255", "teleport_nhlua_api_256", "teleport_nhlua_api_257", "teleport_nhlua_api_258", "teleport_nhlua_api_259", "teleport_nhlua_api_260", "teleport_nhlua_api_261", "teleport_nhlua_api_262", "teleport_nhlua_api_263", "teleport_nhlua_api_264", "teleport_nhlua_api_265", "teleport_nhlua_api_266", "teleport_nhlua_api_267", "teleport_nhlua_api_268", "teleport_nhlua_api_269", "teleport_nhlua_api_270", "teleport_nhlua_api_271", "teleport_nhlua_api_272", "teleport_nhlua_api_273", "teleport_nhlua_api_274", "teleport_nhlua_api_275", "teleport_nhlua_api_276", "teleport_nhlua_api_277", "teleport_nhlua_api_278", "teleport_nhlua_api_279", "teleport_nhlua_api_280", "teleport_nhlua_api_281", "teleport_nhlua_api_282", "teleport_nhlua_api_283", "teleport_nhlua_api_284", "teleport_nhlua_api_285", "teleport_nhlua_api_286", "teleport_nhlua_api_287", "teleport_nhlua_api_288", "teleport_nhlua_api_289", "teleport_nhlua_api_290", "teleport_nhlua_api_291", "teleport_nhlua_api_292", "teleport_nhlua_api_293", "teleport_nhlua_api_294", "teleport_nhlua_api_295", "teleport_nhlua_api_296", "teleport_nhlua_api_297", "teleport_nhlua_api_298", "teleport_nhlua_api_299", "teleport_nhlua_api_300", "teleport_nhlua_api_301", "teleport_nhlua_api_302", "teleport_nhlua_api_303", "teleport_nhlua_api_304", "teleport_nhlua_api_305", "teleport_nhlua_api_306", "teleport_nhlua_api_307", "teleport_nhlua_api_308", "teleport_nhlua_api_309", "teleport_nhlua_api_310", "teleport_nhlua_api_311", "teleport_nhlua_api_312", "teleport_nhlua_api_313", "teleport_nhlua_api_314", "teleport_nhlua_api_315", "teleport_nhlua_api_316", "teleport_nhlua_api_317", "teleport_nhlua_api_318", "teleport_nhlua_api_319", "teleport_nhlua_api_320", "teleport_nhlua_api_321", "teleport_nhlua_api_322", "teleport_nhlua_api_323", "teleport_nhlua_api_324", "teleport_nhlua_api_325", "teleport_nhlua_api_326", "teleport_nhlua_api_327", "teleport_nhlua_api_328", "teleport_nhlua_api_329", "teleport_nhlua_api_330", "teleport_nhlua_api_331", "teleport_nhlua_api_332", "teleport_nhlua_api_333", "teleport_nhlua_api_334", "teleport_nhlua_api_335", "teleport_nhlua_api_336", "teleport_nhlua_api_337", "teleport_nhlua_api_338", "teleport_nhlua_api_339", "teleport_nhlua_api_340", "teleport_nhlua_api_341", "teleport_nhlua_api_342", "teleport_nhlua_api_343", "teleport_nhlua_api_344", "teleport_nhlua_api_345", "teleport_nhlua_api_346", "teleport_nhlua_api_347", "teleport_nhlua_api_348", "teleport_nhlua_api_349", "teleport_nhlua_api_350", "teleport_nhlua_api_351", "teleport_nhlua_api_352", "teleport_nhlua_api_353", "teleport_nhlua_api_354", "teleport_nhlua_api_355", "teleport_nhlua_api_356", "teleport_nhlua_api_357", "teleport_nhlua_api_358", "teleport_nhlua_api_359", "teleport_nhlua_api_360", "teleport_nhlua_api_361", "teleport_nhlua_api_362", "teleport_nhlua_api_363", "teleport_nhlua_api_364", "teleport_nhlua_api_365", "teleport_nhlua_api_366", "teleport_nhlua_api_367", "teleport_nhlua_api_368", "teleport_nhlua_api_369", "teleport_nhlua_api_370", "teleport_nhlua_api_371", "teleport_nhlua_api_372", "teleport_nhlua_api_373", "teleport_nhlua_api_374", "teleport_nhlua_api_375", "teleport_nhlua_api_376", "teleport_nhlua_api_377", "teleport_nhlua_api_378", "teleport_nhlua_api_379", "teleport_nhlua_api_380", "teleport_nhlua_api_381", "teleport_nhlua_api_382", "teleport_nhlua_api_383", "teleport_nhlua_api_384", "teleport_nhlua_api_385", "teleport_nhlua_api_386", "teleport_nhlua_api_387", "teleport_nhlua_api_388", "teleport_nhlua_api_389", "teleport_nhlua_api_390", "teleport_nhlua_api_391", "teleport_nhlua_api_392", "teleport_nhlua_api_393", "teleport_nhlua_api_394", "teleport_nhlua_api_395", "teleport_nhlua_api_396", "teleport_nhlua_api_397", "teleport_nhlua_api_398", "teleport_nhlua_api_399", "teleport_nhlua_api_400", "teleport_nhlua_api_401", "teleport_nhlua_api_402", "teleport_nhlua_api_403", "teleport_nhlua_api_404", "teleport_nhlua_api_405", "teleport_nhlua_api_406", "teleport_nhlua_api_407", "teleport_nhlua_api_408", "teleport_nhlua_api_409", "teleport_nhlua_api_410", "teleport_nhlua_api_411", "teleport_nhlua_api_412", "teleport_nhlua_api_413", "teleport_nhlua_api_414", "teleport_nhlua_api_415", "teleport_nhlua_api_416", "teleport_nhlua_api_417", "teleport_nhlua_api_418", "teleport_nhlua_api_419", "teleport_nhlua_api_420", "teleport_nhlua_api_421", "teleport_nhlua_api_422", "teleport_nhlua_api_423", "teleport_nhlua_api_424", "teleport_nhlua_api_425", "teleport_nhlua_api_426", "teleport_nhlua_api_427", "teleport_nhlua_api_428", "teleport_nhlua_api_429", "teleport_nhlua_api_430", "teleport_nhlua_api_431", "teleport_nhlua_api_432", "teleport_nhlua_api_433", "teleport_nhlua_api_434", "teleport_nhlua_api_435", "teleport_nhlua_api_436", "teleport_nhlua_api_437", "teleport_nhlua_api_438", "teleport_nhlua_api_439", "teleport_nhlua_api_440", "teleport_nhlua_api_441", "teleport_nhlua_api_442", "teleport_nhlua_api_443", "teleport_nhlua_api_444", "teleport_nhlua_api_445", "teleport_nhlua_api_446", "teleport_nhlua_api_447", "teleport_nhlua_api_448", "teleport_nhlua_api_449", "teleport_nhlua_api_450", "teleport_nhlua_api_451", "teleport_nhlua_api_452", "teleport_nhlua_api_453", "teleport_nhlua_api_454", "teleport_nhlua_api_455", "teleport_nhlua_api_456", "teleport_nhlua_api_457", "teleport_nhlua_api_458", "teleport_nhlua_api_459", "teleport_nhlua_api_460", "teleport_nhlua_api_461", "teleport_nhlua_api_462", "teleport_nhlua_api_463", "teleport_nhlua_api_464", "teleport_nhlua_api_465", "teleport_nhlua_api_466", "teleport_nhlua_api_467", "teleport_nhlua_api_468", "teleport_nhlua_api_469", "teleport_nhlua_api_470", "teleport_nhlua_api_471", "teleport_nhlua_api_472", "teleport_nhlua_api_473", "teleport_nhlua_api_474", "teleport_nhlua_api_475", "teleport_nhlua_api_476", "teleport_nhlua_api_477", "teleport_nhlua_api_478", "teleport_nhlua_api_479", "teleport_nhlua_api_480", "teleport_nhlua_api_481", "teleport_nhlua_api_482", "teleport_nhlua_api_483", "teleport_nhlua_api_484", "teleport_nhlua_api_485", "teleport_nhlua_api_486", "teleport_nhlua_api_487", "teleport_nhlua_api_488", "teleport_nhlua_api_489", "teleport_nhlua_api_490", "teleport_nhlua_api_491", "teleport_nhlua_api_492", "teleport_nhlua_api_493", "teleport_nhlua_api_494", "teleport_nhlua_api_495", "teleport_nhlua_api_496", "teleport_nhlua_api_497", "teleport_nhlua_api_498", "teleport_nhlua_api_499", "teleport_nhlua_api_500", "teleport_nhlua_api_501", "teleport_nhlua_api_502", "teleport_nhlua_api_503", "teleport_nhlua_api_504", "teleport_nhlua_api_505", "teleport_nhlua_api_506", "teleport_nhlua_api_507", "teleport_nhlua_api_508", "teleport_nhlua_api_509", "teleport_nhlua_api_510", "teleport_nhlua_api_511", "teleport_nhlua_api_512", "teleport_nhlua_api_513", "teleport_nhlua_api_514", "teleport_nhlua_api_515", "teleport_nhlua_api_516", "teleport_nhlua_api_517", "teleport_nhlua_api_518", "teleport_nhlua_api_519", "teleport_nhlua_api_520", "teleport_nhlua_api_521", "teleport_nhlua_api_522", "teleport_nhlua_api_523", "teleport_nhlua_api_524", "teleport_nhlua_api_525", "$stackAlloc", "$stackSave", "$stackRestore", "$UTF8ToString", "$lengthBytesUTF8", "$stringToUTF8"],
$teleportNhluaServices:function(){
var state=Module.teleportNhluaTransport||={next:0,strings:new Map(),continuations:new Map(),token:0};
var pointer=v=>BigInt(v??0);
var literal=s=>{if(state.strings.has(s))return state.strings.get(s);var n=lengthBytesUTF8(s)+1;if(state.next+n>Number(_teleport_nhlua_literal_capacity()))throw Error('NHLUA literal capacity');var at=Number(_teleport_nhlua_literal_storage())+state.next;stringToUTF8(s,at,n);state.next+=n;state.strings.set(s,at);return at;};
var layout=state.layout;if(!layout){layout=Object.create(null);for(var i=0;i<Number(_teleport_nhlua_layout_count());i++){var name=UTF8ToString(Number(_teleport_nhlua_layout_name(BigInt(i)))),value=Number(_teleport_nhlua_layout_value(BigInt(i)));if(Object.hasOwn(layout,name)||!Number.isSafeInteger(value)||value<0)throw Error('NHLUA layout metadata '+name);layout[name]=value;}}
return {moduleKey:Module,layout,commitLayout:()=>{if(!state.layout)state.layout=Object.freeze(layout);},heap:()=>HEAPU8,literal,stackAlloc:n=>Number(stackAlloc(n)),stackSave:()=>stackSave(),stackRestore:p=>stackRestore(p),
global:i=>Number(_teleport_nhlua_global(i)),storage:i=>Number(_teleport_nhlua_storage(i)),
functionPointer:name=>{var i=["l_get_config_errors", "luaopen_base", "luaopen_coroutine", "luaopen_debug", "luaopen_math", "luaopen_os", "luaopen_string", "luaopen_table", "luaopen_utf8", "nhl_abs_coord", "nhl_alloc", "nhl_an", "nhl_callback", "nhl_debug_flags", "nhl_deltrap", "nhl_dnum_name", "nhl_doturn", "nhl_flip_level", "nhl_gamestate", "nhl_get_cmd_key", "nhl_get_config", "nhl_get_debug_themerm_name", "nhl_getlin", "nhl_getmap", "nhl_gettrap", "nhl_hookfn", "nhl_impossible", "nhl_ing_suffix", "nhl_int_to_obj_name", "nhl_int_to_pm_name", "nhl_is_genocided", "nhl_level_difficulty", "nhl_makeplural", "nhl_makesingular", "nhl_menu", "nhl_meta_u_index", "nhl_meta_u_newindex", "nhl_panic", "nhl_parse_config", "nhl_pline", "nhl_pushkey", "nhl_random", "nhl_rn2", "nhl_s_suffix", "nhl_stairways", "nhl_test", "nhl_text", "nhl_timer_has_at", "nhl_timer_peek_at", "nhl_timer_start_at", "nhl_timer_stop_at", "nhl_u_clear_inventory", "nhl_u_giveobj", "nhl_variable", "nhl_verbalize", "nhl_warn", "parse_config_line", "traceback_handler"].indexOf(name);if(i<0)throw Error('NHLUA callback '+name);return Number(_teleport_nhlua_function_pointer(i));},
longjmp:(buffer,status)=>_teleport_nhlua_jump(pointer(buffer),status),
setjmpBooleanScope:(buffer,fn)=>{var token=++state.token;state.continuations.set(token,fn);try{return _teleport_nhlua_jump_scope(pointer(buffer),BigInt(token));}finally{state.continuations.delete(token);}},
api:(site,...args)=>{switch(site){
case 0:return _teleport_nhlua_api_0(BigInt(args[0]));
case 1:return _teleport_nhlua_api_1(BigInt(args[0]),BigInt(args[1]));
case 2:return _teleport_nhlua_api_2(BigInt(args[0]),Number(args[1]));
case 3:return _teleport_nhlua_api_3(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 4:return _teleport_nhlua_api_4(BigInt(args[0]),Number(args[1]));
case 5:return _teleport_nhlua_api_5(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 6:return _teleport_nhlua_api_6(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 7:return _teleport_nhlua_api_7(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),Number(args[3]));
case 8:return Number(_teleport_nhlua_api_8(BigInt(args[0])));
case 9:return _teleport_nhlua_api_9(BigInt(args[0]));
case 10:return _teleport_nhlua_api_10(BigInt(args[0]),BigInt(args[1]),Number(args[2]),BigInt(args[3]));
case 11:return Number(_teleport_nhlua_api_11(BigInt(args[0]),BigInt(args[1])));
case 12:return _teleport_nhlua_api_12(BigInt(args[0]));
case 13:return _teleport_nhlua_api_13(BigInt(args[0]));
case 14:return _teleport_nhlua_api_14(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 15:return _teleport_nhlua_api_15(BigInt(args[0]),Number(args[1]));
case 16:return _teleport_nhlua_api_16(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 17:return _teleport_nhlua_api_17(BigInt(args[0]));
case 18:return _teleport_nhlua_api_18(BigInt(args[0]));
case 19:return _teleport_nhlua_api_19(BigInt(args[0]),Number(args[1]),BigInt(args[2]),BigInt(args[3]));
case 20:return Number(_teleport_nhlua_api_20(BigInt(args[0]),BigInt(args[1])));
case 21:return _teleport_nhlua_api_21(BigInt(args[0]),BigInt(args[1]));
case 22:return _teleport_nhlua_api_22(BigInt(args[0]),Number(args[1]));
case 23:return _teleport_nhlua_api_23(BigInt(args[0]),BigInt(args[1]),Number(args[2]));
case 24:return Number(_teleport_nhlua_api_24(BigInt(args[0]),BigInt(args[1])));
case 25:return Number(_teleport_nhlua_api_25(BigInt(args[0]),BigInt(args[1])));
case 26:return _teleport_nhlua_api_26(BigInt(args[0]),Number(args[1]));
case 27:return Number(_teleport_nhlua_api_27(BigInt(args[0]),BigInt(args[1])));
case 28:return Number(_teleport_nhlua_api_28(BigInt(args[0]),BigInt(args[1])));
case 29:return _teleport_nhlua_api_29(BigInt(args[0]),Number(args[1]));
case 30:return Number(_teleport_nhlua_api_30(BigInt(args[0]),BigInt(args[1])));
case 31:return _teleport_nhlua_api_31(BigInt(args[0]),Number(args[1]));
case 32:return _teleport_nhlua_api_32(BigInt(args[0]),Number(args[1]));
case 33:return Number(_teleport_nhlua_api_33(BigInt(args[0]),BigInt(args[1])));
case 34:return _teleport_nhlua_api_34(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 35:return _teleport_nhlua_api_35(BigInt(args[0]),Number(args[1]));
case 36:return _teleport_nhlua_api_36(BigInt(args[0]));
case 37:return _teleport_nhlua_api_37(BigInt(args[0]),BigInt(args[1]));
case 38:return _teleport_nhlua_api_38(Number(args[0]),Number(args[1]));
case 39:return Number(_teleport_nhlua_api_39(Number(args[0]),Number(args[1])));
case 40:return _teleport_nhlua_api_40(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 41:return Number(_teleport_nhlua_api_41(Number(args[0])));
case 42:return _teleport_nhlua_api_42(BigInt(args[0]),BigInt(args[1]));
case 43:return _teleport_nhlua_api_43(Number(args[0]),Number(args[1]));
case 44:return Number(_teleport_nhlua_api_44(Number(args[0]),Number(args[1])));
case 45:return _teleport_nhlua_api_45(BigInt(args[0]));
case 46:return _teleport_nhlua_api_46(BigInt(args[0]));
case 47:return _teleport_nhlua_api_47(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 48:return _teleport_nhlua_api_48(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 49:return _teleport_nhlua_api_49(BigInt(args[0]),Number(args[1]));
case 50:return _teleport_nhlua_api_50(BigInt(args[0]),Number(args[1]),BigInt(args[2]),BigInt(args[3]));
case 51:return _teleport_nhlua_api_51(BigInt(args[0]),BigInt(args[1]));
case 52:return _teleport_nhlua_api_52(Number(args[0]),Number(args[1]));
case 53:return _teleport_nhlua_api_53(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 54:return Number(_teleport_nhlua_api_54(Number(args[0])));
case 55:return _teleport_nhlua_api_55(BigInt(args[0]),BigInt(args[1]),Number(args[2]));
case 56:return Number(_teleport_nhlua_api_56(Number(args[0]),Number(args[1])));
case 57:return Number(_teleport_nhlua_api_57(BigInt(args[0]),BigInt(args[1])));
case 58:return _teleport_nhlua_api_58(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 59:return _teleport_nhlua_api_59(BigInt(args[0]),Number(args[1]));
case 60:return _teleport_nhlua_api_60(BigInt(args[0]));
case 61:return Number(_teleport_nhlua_api_61(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 62:return _teleport_nhlua_api_62(BigInt(args[0]),BigInt(args[1]));
case 63:return _teleport_nhlua_api_63(BigInt(args[0]));
case 64:return Number(_teleport_nhlua_api_64(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 65:return _teleport_nhlua_api_65(BigInt(args[0]),BigInt(args[1]));
case 66:return _teleport_nhlua_api_66(BigInt(args[0]),Number(args[1]));
case 68:return _teleport_nhlua_api_68(BigInt(args[0]));
case 69:return Number(_teleport_nhlua_api_69(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 70:return _teleport_nhlua_api_70(BigInt(args[0]),BigInt(args[1]));
case 71:return _teleport_nhlua_api_71(BigInt(args[0]));
case 72:return Number(_teleport_nhlua_api_72(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 73:return _teleport_nhlua_api_73(BigInt(args[0]),BigInt(args[1]));
case 74:return _teleport_nhlua_api_74(BigInt(args[0]));
case 75:return Number(_teleport_nhlua_api_75(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 76:return Number(_teleport_nhlua_api_76(BigInt(args[0]),Number(args[1])));
case 77:return Number(_teleport_nhlua_api_77(BigInt(args[0]),BigInt(args[1])));
case 78:return _teleport_nhlua_api_78(BigInt(args[0]));
case 79:return Number(_teleport_nhlua_api_79(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 80:return _teleport_nhlua_api_80(BigInt(args[0]),BigInt(args[1]));
case 81:return Number(_teleport_nhlua_api_81(BigInt(args[0]),BigInt(args[1])));
case 82:return _teleport_nhlua_api_82(BigInt(args[0]));
case 83:return Number(_teleport_nhlua_api_83(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 84:return _teleport_nhlua_api_84(BigInt(args[0]),Number(args[1]));
case 85:return Number(_teleport_nhlua_api_85(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 86:return _teleport_nhlua_api_86(BigInt(args[0]),Number(args[1]));
case 87:return _teleport_nhlua_api_87(BigInt(args[0]),Number(args[1]),BigInt(args[2]),BigInt(args[3]));
case 88:return _teleport_nhlua_api_88(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 91:return _teleport_nhlua_api_91(BigInt(args[0]));
case 92:return _teleport_nhlua_api_92(BigInt(args[0]),Number(args[1]));
case 93:return _teleport_nhlua_api_93(BigInt(args[0]),Number(args[1]));
case 94:return Number(_teleport_nhlua_api_94(BigInt(args[0]),BigInt(args[1])));
case 95:return _teleport_nhlua_api_95(BigInt(args[0]),Number(args[1]));
case 96:return Number(_teleport_nhlua_api_96(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 97:return _teleport_nhlua_api_97(BigInt(args[0]),Number(args[1]));
case 98:return Number(_teleport_nhlua_api_98(BigInt(args[0]),BigInt(args[1])));
case 99:return _teleport_nhlua_api_99(BigInt(args[0]),Number(args[1]));
case 100:return Number(_teleport_nhlua_api_100(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 101:return _teleport_nhlua_api_101(BigInt(args[0]),Number(args[1]));
case 102:return _teleport_nhlua_api_102(BigInt(args[0]),Number(args[1]));
case 103:return Number(_teleport_nhlua_api_103(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 104:return Number(_teleport_nhlua_api_104(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 105:return _teleport_nhlua_api_105(Number(args[0]),BigInt(args[1]),BigInt(args[2]),Number(args[3]),Number(args[4]),Number(args[5]),Number(args[6]),BigInt(args[7]),Number(args[8]));
case 106:return _teleport_nhlua_api_106(BigInt(args[0]),Number(args[1]));
case 108:return _teleport_nhlua_api_108(Number(args[0]),Number(args[1]),BigInt(args[2]));
case 110:return Number(_teleport_nhlua_api_110(BigInt(args[0]),BigInt(args[1])));
case 111:return Number(_teleport_nhlua_api_111(BigInt(args[0]),BigInt(args[1])));
case 112:return _teleport_nhlua_api_112(BigInt(args[0]));
case 115:return _teleport_nhlua_api_115(BigInt(args[0]));
case 116:return Number(_teleport_nhlua_api_116(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 117:return Number(_teleport_nhlua_api_117(BigInt(args[0])));
case 118:return _teleport_nhlua_api_118(BigInt(args[0]));
case 119:return Number(_teleport_nhlua_api_119(BigInt(args[0]),Number(args[1])));
case 120:return _teleport_nhlua_api_120(Number(args[0]),BigInt(args[1]));
case 121:return _teleport_nhlua_api_121(BigInt(args[0]),Number(args[1]));
case 122:return _teleport_nhlua_api_122(BigInt(args[0]));
case 124:return _teleport_nhlua_api_124(Number(args[0]),Number(args[1]),BigInt(args[2]));
case 126:return _teleport_nhlua_api_126(BigInt(args[0]));
case 127:return Number(_teleport_nhlua_api_127(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 128:return Number(_teleport_nhlua_api_128(BigInt(args[0])));
case 129:return Number(_teleport_nhlua_api_129(BigInt(args[0]),BigInt(args[1])));
case 130:return _teleport_nhlua_api_130(BigInt(args[0]));
case 131:return Number(_teleport_nhlua_api_131(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 132:return Number(_teleport_nhlua_api_132(BigInt(args[0])));
case 133:return Number(_teleport_nhlua_api_133(BigInt(args[0]),BigInt(args[1])));
case 134:return _teleport_nhlua_api_134(BigInt(args[0]));
case 135:return Number(_teleport_nhlua_api_135(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 136:return Number(_teleport_nhlua_api_136(BigInt(args[0])));
case 137:return Number(_teleport_nhlua_api_137(BigInt(args[0]),BigInt(args[1])));
case 138:return _teleport_nhlua_api_138(BigInt(args[0]));
case 139:return Number(_teleport_nhlua_api_139(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 140:return Number(_teleport_nhlua_api_140(BigInt(args[0])));
case 141:return Number(_teleport_nhlua_api_141(BigInt(args[0]),BigInt(args[1])));
case 142:return _teleport_nhlua_api_142(BigInt(args[0]));
case 143:return Number(_teleport_nhlua_api_143(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 144:return Number(_teleport_nhlua_api_144(BigInt(args[0])));
case 145:return Number(_teleport_nhlua_api_145(BigInt(args[0]),BigInt(args[1])));
case 146:return Number(_teleport_nhlua_api_146(BigInt(args[0])));
case 147:return _teleport_nhlua_api_147(BigInt(args[0]),BigInt(args[1]));
case 148:return Number(_teleport_nhlua_api_148(BigInt(args[0])));
case 149:return _teleport_nhlua_api_149(BigInt(args[0]),Number(args[1]),BigInt(args[2]),BigInt(args[3]),BigInt(args[4]),BigInt(args[5]));
case 150:return _teleport_nhlua_api_150(BigInt(args[0]),Number(args[1]),BigInt(args[2]),BigInt(args[3]),BigInt(args[4]),BigInt(args[5]));
case 151:return _teleport_nhlua_api_151(BigInt(args[0]),Number(args[1]),BigInt(args[2]),BigInt(args[3]),BigInt(args[4]),BigInt(args[5]));
case 152:return _teleport_nhlua_api_152(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 153:return _teleport_nhlua_api_153(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 154:return _teleport_nhlua_api_154(BigInt(args[0]));
case 155:return _teleport_nhlua_api_155(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 156:return _teleport_nhlua_api_156(BigInt(args[0]),Number(args[1]),BigInt(args[2]),BigInt(args[3]),BigInt(args[4]),Number(args[5]),BigInt(args[6]));
case 157:return _teleport_nhlua_api_157(BigInt(args[0]),Number(args[1]),BigInt(args[2]),BigInt(args[3]),BigInt(args[4]),BigInt(args[5]));
case 158:return _teleport_nhlua_api_158(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 159:return _teleport_nhlua_api_159(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 160:return _teleport_nhlua_api_160(BigInt(args[0]));
case 161:return _teleport_nhlua_api_161(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 162:return _teleport_nhlua_api_162(BigInt(args[0]),Number(args[1]),BigInt(args[2]),BigInt(args[3]),BigInt(args[4]),Number(args[5]),BigInt(args[6]));
case 163:return _teleport_nhlua_api_163(BigInt(args[0]),Number(args[1]),BigInt(args[2]),BigInt(args[3]),BigInt(args[4]),BigInt(args[5]));
case 164:return _teleport_nhlua_api_164(BigInt(args[0]),Number(args[1]),BigInt(args[2]),BigInt(args[3]),BigInt(args[4]),BigInt(args[5]),BigInt(args[6]),Number(args[7]),BigInt(args[8]));
case 165:return _teleport_nhlua_api_165(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 166:return _teleport_nhlua_api_166(BigInt(args[0]));
case 167:return _teleport_nhlua_api_167(BigInt(args[0]),Number(args[1]));
case 168:return _teleport_nhlua_api_168(Number(args[0]));
case 169:return _teleport_nhlua_api_169(BigInt(args[0]),BigInt(args[1]));
case 170:return _teleport_nhlua_api_170(BigInt(args[0]));
case 171:return _teleport_nhlua_api_171(BigInt(args[0]),Number(args[1]));
case 172:return _teleport_nhlua_api_172(Number(args[0]));
case 173:return _teleport_nhlua_api_173(BigInt(args[0]),BigInt(args[1]));
case 174:return _teleport_nhlua_api_174(BigInt(args[0]),Number(args[1]));
case 175:return _teleport_nhlua_api_175(BigInt(args[0]),Number(args[1]));
case 176:return _teleport_nhlua_api_176(Number(args[0]));
case 177:return _teleport_nhlua_api_177(BigInt(args[0]),BigInt(args[1]));
case 178:return _teleport_nhlua_api_178(BigInt(args[0]));
case 179:return _teleport_nhlua_api_179();
case 180:return _teleport_nhlua_api_180(BigInt(args[0]),BigInt(args[1]));
case 181:return _teleport_nhlua_api_181(BigInt(args[0]));
case 182:return Number(_teleport_nhlua_api_182(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 183:return _teleport_nhlua_api_183(BigInt(args[0]),BigInt(args[1]));
case 184:return _teleport_nhlua_api_184(BigInt(args[0]),Number(args[1]));
case 185:return _teleport_nhlua_api_185(BigInt(args[0]));
case 186:return _teleport_nhlua_api_186(BigInt(args[0]),Number(args[1]));
case 187:return _teleport_nhlua_api_187(BigInt(args[0]),Number(args[1]));
case 188:return Number(_teleport_nhlua_api_188(BigInt(args[0])));
case 189:return _teleport_nhlua_api_189(BigInt(args[0]));
case 190:return Number(_teleport_nhlua_api_190(BigInt(args[0]),BigInt(args[1])));
case 191:return _teleport_nhlua_api_191(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 192:return _teleport_nhlua_api_192(BigInt(args[0]),Number(args[1]));
case 193:return _teleport_nhlua_api_193(BigInt(args[0]),Number(args[1]));
case 194:return _teleport_nhlua_api_194(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 195:return _teleport_nhlua_api_195(BigInt(args[0]),Number(args[1]));
case 196:return _teleport_nhlua_api_196(BigInt(args[0]),Number(args[1]));
case 197:return _teleport_nhlua_api_197(BigInt(args[0]),Number(args[1]));
case 198:return _teleport_nhlua_api_198(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 199:return Number(_teleport_nhlua_api_199(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 200:return Number(_teleport_nhlua_api_200(BigInt(args[0])));
case 201:return _teleport_nhlua_api_201(BigInt(args[0]),Number(args[1]));
case 202:return _teleport_nhlua_api_202(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 203:return _teleport_nhlua_api_203(BigInt(args[0]),Number(args[1]));
case 204:return Number(_teleport_nhlua_api_204(BigInt(args[0]),Number(args[1]),BigInt(args[2]),BigInt(args[3])));
case 205:return Number(_teleport_nhlua_api_205(BigInt(args[0]),Number(args[1]),BigInt(args[2]),BigInt(args[3])));
case 206:return _teleport_nhlua_api_206(BigInt(args[0]),Number(args[1]));
case 207:return Number(_teleport_nhlua_api_207(BigInt(args[0])));
case 208:return _teleport_nhlua_api_208(BigInt(args[0]),Number(args[1]));
case 209:return _teleport_nhlua_api_209(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 210:return _teleport_nhlua_api_210(BigInt(args[0]),Number(args[1]));
case 211:return _teleport_nhlua_api_211(BigInt(args[0]),Number(args[1]),BigInt(args[2]),BigInt(args[3]));
case 212:return _teleport_nhlua_api_212(BigInt(args[0]),Number(args[1]));
case 213:return _teleport_nhlua_api_213(BigInt(args[0]),Number(args[1]));
case 214:return _teleport_nhlua_api_214(BigInt(args[0]),Number(args[1]));
case 215:return _teleport_nhlua_api_215(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 216:return _teleport_nhlua_api_216(BigInt(args[0]),Number(args[1]));
case 217:return _teleport_nhlua_api_217(BigInt(args[0]),Number(args[1]));
case 218:return _teleport_nhlua_api_218(BigInt(args[0]),Number(args[1]));
case 219:return _teleport_nhlua_api_219(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 220:return _teleport_nhlua_api_220(BigInt(args[0]),Number(args[1]),BigInt(args[2]),BigInt(args[3]));
case 221:return _teleport_nhlua_api_221(BigInt(args[0]),Number(args[1]));
case 222:return _teleport_nhlua_api_222(BigInt(args[0]));
case 223:return _teleport_nhlua_api_223(BigInt(args[0]),Number(args[1]));
case 224:return Number(_teleport_nhlua_api_224(BigInt(args[0]),BigInt(args[1])));
case 225:return Number(_teleport_nhlua_api_225(BigInt(args[0]),BigInt(args[1])));
case 226:return _teleport_nhlua_api_226(BigInt(args[0]));
case 227:return _teleport_nhlua_api_227(BigInt(args[0]),Number(args[1]));
case 228:return Number(_teleport_nhlua_api_228(BigInt(args[0]),BigInt(args[1])));
case 229:return Number(_teleport_nhlua_api_229(BigInt(args[0]),BigInt(args[1])));
case 230:return _teleport_nhlua_api_230(BigInt(args[0]));
case 231:return _teleport_nhlua_api_231(BigInt(args[0]),Number(args[1]));
case 232:return Number(_teleport_nhlua_api_232(BigInt(args[0]),BigInt(args[1])));
case 233:return Number(_teleport_nhlua_api_233(BigInt(args[0]),BigInt(args[1])));
case 234:return Number(_teleport_nhlua_api_234(BigInt(args[0]),BigInt(args[1])));
case 235:return Number(_teleport_nhlua_api_235(BigInt(args[0]),BigInt(args[1])));
case 236:return _teleport_nhlua_api_236(BigInt(args[0]));
case 237:return _teleport_nhlua_api_237(BigInt(args[0]));
case 238:return _teleport_nhlua_api_238(BigInt(args[0]),BigInt(args[1]));
case 239:return _teleport_nhlua_api_239(BigInt(args[0]),Number(args[1]));
case 240:return _teleport_nhlua_api_240(BigInt(args[0]));
case 241:return Number(_teleport_nhlua_api_241(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 242:return _teleport_nhlua_api_242(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 243:return _teleport_nhlua_api_243(BigInt(args[0]),Number(args[1]));
case 244:return Number(_teleport_nhlua_api_244(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 245:return Number(_teleport_nhlua_api_245(BigInt(args[0]),BigInt(args[1])));
case 246:return _teleport_nhlua_api_246(BigInt(args[0]));
case 247:return _teleport_nhlua_api_247(BigInt(args[0]),Number(args[1]));
case 248:return _teleport_nhlua_api_248(BigInt(args[0]),Number(args[1]));
case 249:return _teleport_nhlua_api_249(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 250:return _teleport_nhlua_api_250(BigInt(args[0]),BigInt(args[1]));
case 251:return _teleport_nhlua_api_251(BigInt(args[0]),BigInt(args[1]));
case 252:return _teleport_nhlua_api_252(BigInt(args[0]),Number(args[1]));
case 253:return Number(_teleport_nhlua_api_253(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 254:return _teleport_nhlua_api_254(BigInt(args[0]),BigInt(args[1]));
case 255:return Number(_teleport_nhlua_api_255(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 256:return _teleport_nhlua_api_256(BigInt(args[0]),Number(args[1]));
case 257:return Number(_teleport_nhlua_api_257(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 258:return Number(_teleport_nhlua_api_258(BigInt(args[0]),BigInt(args[1])));
case 259:return _teleport_nhlua_api_259(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 260:return _teleport_nhlua_api_260(BigInt(args[0]));
case 261:return _teleport_nhlua_api_261(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 262:return _teleport_nhlua_api_262(BigInt(args[0]),Number(args[1]));
case 263:return _teleport_nhlua_api_263(BigInt(args[0]),Number(args[1]));
case 264:return _teleport_nhlua_api_264(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 265:return _teleport_nhlua_api_265(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 266:return _teleport_nhlua_api_266(BigInt(args[0]),BigInt(args[1]));
case 267:return _teleport_nhlua_api_267(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 268:return _teleport_nhlua_api_268(BigInt(args[0]),BigInt(args[1]));
case 269:return Number(_teleport_nhlua_api_269(BigInt(args[0]),BigInt(args[1])));
case 270:return _teleport_nhlua_api_270(BigInt(args[0]),Number(args[1]));
case 271:return Number(_teleport_nhlua_api_271(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 272:return _teleport_nhlua_api_272(BigInt(args[0]),BigInt(args[1]));
case 273:return _teleport_nhlua_api_273(BigInt(args[0]));
case 274:return _teleport_nhlua_api_274(BigInt(args[0]),BigInt(args[1]));
case 275:return _teleport_nhlua_api_275(BigInt(args[0]),Number(args[1]));
case 276:return Number(_teleport_nhlua_api_276(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 277:return Number(_teleport_nhlua_api_277(BigInt(args[0])));
case 278:return _teleport_nhlua_api_278(BigInt(args[0]),Number(args[1]));
case 279:return Number(_teleport_nhlua_api_279(BigInt(args[0])));
case 280:return _teleport_nhlua_api_280(BigInt(args[0]),BigInt(args[1]),Number(args[2]));
case 281:return _teleport_nhlua_api_281(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 282:return _teleport_nhlua_api_282(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),Number(args[3]));
case 283:return _teleport_nhlua_api_283(BigInt(args[0]));
case 284:return _teleport_nhlua_api_284(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 285:return Number(_teleport_nhlua_api_285(Number(args[0])));
case 286:return _teleport_nhlua_api_286(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),Number(args[3]));
case 287:return _teleport_nhlua_api_287(BigInt(args[0]),BigInt(args[1]));
case 288:return _teleport_nhlua_api_288(BigInt(args[0]));
case 289:return _teleport_nhlua_api_289(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 290:return _teleport_nhlua_api_290(BigInt(args[0]),BigInt(args[1]));
case 291:return _teleport_nhlua_api_291(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 292:return _teleport_nhlua_api_292(BigInt(args[0]),Number(args[1]));
case 293:return _teleport_nhlua_api_293(BigInt(args[0]),Number(args[1]));
case 294:return _teleport_nhlua_api_294(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 295:return _teleport_nhlua_api_295(BigInt(args[0]),Number(args[1]),Number(args[2]),BigInt(args[3]));
case 296:return _teleport_nhlua_api_296(BigInt(args[0]));
case 297:return _teleport_nhlua_api_297(BigInt(args[0]));
case 298:return Number(_teleport_nhlua_api_298(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 299:return _teleport_nhlua_api_299(Number(args[0]),Number(args[1]));
case 300:return _teleport_nhlua_api_300(BigInt(args[0]));
case 301:return _teleport_nhlua_api_301(BigInt(args[0]),Number(args[1]));
case 302:return _teleport_nhlua_api_302();
case 303:return _teleport_nhlua_api_303(BigInt(args[0]));
case 304:return _teleport_nhlua_api_304(BigInt(args[0]));
case 305:return _teleport_nhlua_api_305(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 306:return _teleport_nhlua_api_306(Number(args[0]),Number(args[1]));
case 307:return _teleport_nhlua_api_307(BigInt(args[0]),Number(args[1]));
case 308:return _teleport_nhlua_api_308(BigInt(args[0]),BigInt(args[1]));
case 309:return _teleport_nhlua_api_309(Number(args[0]),Number(args[1]));
case 310:return _teleport_nhlua_api_310(Number(args[0]),Number(args[1]),Number(args[2]));
case 311:return _teleport_nhlua_api_311(BigInt(args[0]),Number(args[1]));
case 312:return _teleport_nhlua_api_312(BigInt(args[0]),Number(args[1]));
case 313:return _teleport_nhlua_api_313(BigInt(args[0]),BigInt(args[1]));
case 314:return _teleport_nhlua_api_314(Number(args[0]),Number(args[1]));
case 315:return _teleport_nhlua_api_315(Number(args[0]),Number(args[1]),Number(args[2]));
case 316:return _teleport_nhlua_api_316(BigInt(args[0]),BigInt(args[1]));
case 317:return _teleport_nhlua_api_317(BigInt(args[0]),Number(args[1]));
case 318:return _teleport_nhlua_api_318(BigInt(args[0]),BigInt(args[1]));
case 319:return _teleport_nhlua_api_319(Number(args[0]),Number(args[1]));
case 320:return _teleport_nhlua_api_320(Number(args[0]),Number(args[1]),Number(args[2]));
case 321:return _teleport_nhlua_api_321(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 322:return _teleport_nhlua_api_322(BigInt(args[0]),Number(args[1]));
case 323:return _teleport_nhlua_api_323(BigInt(args[0]),BigInt(args[1]));
case 324:return _teleport_nhlua_api_324(Number(args[0]),Number(args[1]));
case 325:return _teleport_nhlua_api_325(Number(args[0]),Number(args[1]),Number(args[2]));
case 326:return Number(_teleport_nhlua_api_326(BigInt(args[0])));
case 327:return _teleport_nhlua_api_327(BigInt(args[0]),Number(args[1]),Number(args[2]),BigInt(args[3]));
case 328:return _teleport_nhlua_api_328(BigInt(args[0]));
case 329:return Number(_teleport_nhlua_api_329(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 330:return Number(_teleport_nhlua_api_330(BigInt(args[0])));
case 331:return Number(_teleport_nhlua_api_331(BigInt(args[0]),BigInt(args[1])));
case 332:return _teleport_nhlua_api_332(BigInt(args[0]));
case 333:return _teleport_nhlua_api_333(BigInt(args[0]));
case 334:return Number(_teleport_nhlua_api_334(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 335:return Number(_teleport_nhlua_api_335(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 336:return _teleport_nhlua_api_336(BigInt(args[0]),Number(args[1]));
case 337:return Number(_teleport_nhlua_api_337(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 338:return Number(_teleport_nhlua_api_338(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 339:return _teleport_nhlua_api_339(BigInt(args[0]),BigInt(args[1]));
case 340:return _teleport_nhlua_api_340(BigInt(args[0]));
case 341:return _teleport_nhlua_api_341(BigInt(args[0]),BigInt(args[1]));
case 342:return Number(_teleport_nhlua_api_342(BigInt(args[0]),BigInt(args[1])));
case 343:return Number(_teleport_nhlua_api_343(BigInt(args[0]),BigInt(args[1])));
case 344:return _teleport_nhlua_api_344(BigInt(args[0]));
case 345:return _teleport_nhlua_api_345(BigInt(args[0]),Number(args[1]));
case 346:return _teleport_nhlua_api_346(BigInt(args[0]),Number(args[1]));
case 347:return _teleport_nhlua_api_347(BigInt(args[0]),Number(args[1]),Number(args[2]),Number(args[3]),Number(args[4]));
case 348:return _teleport_nhlua_api_348(BigInt(args[0]),BigInt(args[1]));
case 349:return _teleport_nhlua_api_349(BigInt(args[0]));
case 350:return _teleport_nhlua_api_350(BigInt(args[0]),BigInt(args[1]));
case 351:return Number(_teleport_nhlua_api_351(BigInt(args[0])));
case 352:return _teleport_nhlua_api_352(BigInt(args[0]),BigInt(args[1]));
case 353:return _teleport_nhlua_api_353(BigInt(args[0]),BigInt(args[1]),Number(args[2]),BigInt(args[3]));
case 354:return Number(_teleport_nhlua_api_354(BigInt(args[0]),BigInt(args[1]),BigInt(args[2])));
case 355:return _teleport_nhlua_api_355(BigInt(args[0]),BigInt(args[1]),Number(args[2]),BigInt(args[3]));
case 356:return Number(_teleport_nhlua_api_356(BigInt(args[0]),BigInt(args[1]),BigInt(args[2])));
case 357:return _teleport_nhlua_api_357(BigInt(args[0]),BigInt(args[1]),Number(args[2]),BigInt(args[3]));
case 358:return Number(_teleport_nhlua_api_358(BigInt(args[0]),BigInt(args[1]),BigInt(args[2])));
case 359:return _teleport_nhlua_api_359(BigInt(args[0]));
case 360:return _teleport_nhlua_api_360();
case 361:return Number(_teleport_nhlua_api_361(BigInt(args[0]),BigInt(args[1]),BigInt(args[2])));
case 362:return _teleport_nhlua_api_362(BigInt(args[0]));
case 363:return _teleport_nhlua_api_363(BigInt(args[0]));
case 364:return Number(_teleport_nhlua_api_364(Number(args[0])));
case 365:return Number(_teleport_nhlua_api_365(BigInt(args[0]),BigInt(args[1]),BigInt(args[2])));
case 366:return Number(_teleport_nhlua_api_366(Number(args[0])));
case 367:return Number(_teleport_nhlua_api_367(BigInt(args[0]),BigInt(args[1]),BigInt(args[2])));
case 368:return Number(_teleport_nhlua_api_368(Number(args[0])));
case 369:return Number(_teleport_nhlua_api_369(BigInt(args[0]),BigInt(args[1]),BigInt(args[2])));
case 370:return Number(_teleport_nhlua_api_370(BigInt(args[0]),BigInt(args[1]),BigInt(args[2])));
case 371:return Number(_teleport_nhlua_api_371(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 372:return _teleport_nhlua_api_372(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 373:return _teleport_nhlua_api_373();
case 374:return _teleport_nhlua_api_374(BigInt(args[0]),BigInt(args[1]));
case 375:return _teleport_nhlua_api_375(BigInt(args[0]),BigInt(args[1]));
case 376:return _teleport_nhlua_api_376(BigInt(args[0]));
case 377:return _teleport_nhlua_api_377(BigInt(args[0]));
case 378:return _teleport_nhlua_api_378(BigInt(args[0]));
case 379:return _teleport_nhlua_api_379(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 380:return Number(_teleport_nhlua_api_380(BigInt(args[0]),BigInt(args[1])));
case 381:return _teleport_nhlua_api_381(BigInt(args[0]),BigInt(args[1]));
case 382:return _teleport_nhlua_api_382(BigInt(args[0]),Number(args[1]));
case 383:return _teleport_nhlua_api_383(BigInt(args[0]),BigInt(args[1]));
case 384:return _teleport_nhlua_api_384(BigInt(args[0]),BigInt(args[1]));
case 385:return _teleport_nhlua_api_385(BigInt(args[0]),BigInt(args[1]));
case 386:return _teleport_nhlua_api_386(BigInt(args[0]),BigInt(args[1]));
case 387:return Number(_teleport_nhlua_api_387(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 388:return _teleport_nhlua_api_388(BigInt(args[0]),BigInt(args[1]));
case 389:return _teleport_nhlua_api_389(BigInt(args[0]),BigInt(args[1]));
case 390:return _teleport_nhlua_api_390(BigInt(args[0]),BigInt(args[1]));
case 391:return _teleport_nhlua_api_391(BigInt(args[0]),BigInt(args[1]));
case 392:return Number(_teleport_nhlua_api_392(BigInt(args[0]),BigInt(args[1])));
case 393:return _teleport_nhlua_api_393(BigInt(args[0]),BigInt(args[1]));
case 394:return _teleport_nhlua_api_394(BigInt(args[0]),BigInt(args[1]));
case 395:return _teleport_nhlua_api_395(BigInt(args[0]),BigInt(args[1]));
case 396:return _teleport_nhlua_api_396(BigInt(args[0]),BigInt(args[1]));
case 397:return _teleport_nhlua_api_397(BigInt(args[0]),BigInt(args[1]));
case 398:return _teleport_nhlua_api_398(BigInt(args[0]));
case 399:return _teleport_nhlua_api_399(BigInt(args[0]),BigInt(args[1]));
case 400:return _teleport_nhlua_api_400(BigInt(args[0]),BigInt(args[1]));
case 401:return _teleport_nhlua_api_401(BigInt(args[0]));
case 402:return _teleport_nhlua_api_402(BigInt(args[0]),Number(args[1]));
case 403:return _teleport_nhlua_api_403(BigInt(args[0]));
case 404:return _teleport_nhlua_api_404(BigInt(args[0]));
case 405:return _teleport_nhlua_api_405(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 406:return _teleport_nhlua_api_406(BigInt(args[0]),BigInt(args[1]),Number(args[2]));
case 407:return _teleport_nhlua_api_407(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 408:return _teleport_nhlua_api_408(BigInt(args[0]),BigInt(args[1]),Number(args[2]));
case 409:return _teleport_nhlua_api_409(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 410:return _teleport_nhlua_api_410(BigInt(args[0]),BigInt(args[1]),Number(args[2]));
case 411:return _teleport_nhlua_api_411(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 412:return _teleport_nhlua_api_412(BigInt(args[0]),Number(args[1]));
case 413:return _teleport_nhlua_api_413(BigInt(args[0]),BigInt(args[1]));
case 414:return Number(_teleport_nhlua_api_414(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 415:return _teleport_nhlua_api_415(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),Number(args[3]));
case 416:return _teleport_nhlua_api_416(BigInt(args[0]),Number(args[1]));
case 417:return _teleport_nhlua_api_417(BigInt(args[0]),Number(args[1]));
case 418:return _teleport_nhlua_api_418(BigInt(args[0]),BigInt(args[1]),Number(args[2]));
case 419:return _teleport_nhlua_api_419(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 420:return Number(_teleport_nhlua_api_420(BigInt(args[0]),BigInt(args[1])));
case 421:return _teleport_nhlua_api_421(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 422:return _teleport_nhlua_api_422(BigInt(args[0]),Number(args[1]),Number(args[2]),Number(args[3]),BigInt(args[4]),BigInt(args[5]));
case 423:return _teleport_nhlua_api_423(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 424:return _teleport_nhlua_api_424(BigInt(args[0]),Number(args[1]));
case 425:return _teleport_nhlua_api_425(BigInt(args[0]),BigInt(args[1]),Number(args[2]),BigInt(args[3]),BigInt(args[4]));
case 426:return _teleport_nhlua_api_426(BigInt(args[0]),BigInt(args[1]),Number(args[2]),BigInt(args[3]),BigInt(args[4]));
case 427:return Number(_teleport_nhlua_api_427(BigInt(args[0]),BigInt(args[1])));
case 428:return Number(_teleport_nhlua_api_428(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 429:return _teleport_nhlua_api_429(BigInt(args[0]),Number(args[1]),BigInt(args[2]),BigInt(args[3]));
case 430:return Number(_teleport_nhlua_api_430(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 431:return _teleport_nhlua_api_431(BigInt(args[0]),Number(args[1]),BigInt(args[2]),BigInt(args[3]));
case 432:return _teleport_nhlua_api_432(BigInt(args[0]),Number(args[1]));
case 433:return _teleport_nhlua_api_433(BigInt(args[0]),BigInt(args[1]),Number(args[2]));
case 434:return Number(_teleport_nhlua_api_434(Number(args[0])));
case 435:return _teleport_nhlua_api_435(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 436:return Number(_teleport_nhlua_api_436(BigInt(args[0]),BigInt(args[1])));
case 437:return _teleport_nhlua_api_437(BigInt(args[0]),BigInt(args[1]));
case 438:return _teleport_nhlua_api_438(BigInt(args[0]),BigInt(args[1]),Number(args[2]));
case 439:return _teleport_nhlua_api_439(BigInt(args[0]));
case 440:return _teleport_nhlua_api_440(BigInt(args[0]),BigInt(args[1]),Number(args[2]));
case 441:return _teleport_nhlua_api_441(BigInt(args[0]),BigInt(args[1]),Number(args[2]));
case 442:return Number(_teleport_nhlua_api_442(Number(args[0])));
case 443:return _teleport_nhlua_api_443(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]));
case 444:return Number(_teleport_nhlua_api_444(BigInt(args[0]),Number(args[1])));
case 445:return _teleport_nhlua_api_445(BigInt(args[0]));
case 446:return Number(_teleport_nhlua_api_446(BigInt(args[0])));
case 447:return _teleport_nhlua_api_447(BigInt(args[0]),BigInt(args[1]));
case 448:return _teleport_nhlua_api_448(BigInt(args[0]));
case 449:return _teleport_nhlua_api_449(BigInt(args[0]));
case 450:return _teleport_nhlua_api_450(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]),BigInt(args[4]));
case 451:return Number(_teleport_nhlua_api_451(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 452:return _teleport_nhlua_api_452(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 453:return _teleport_nhlua_api_453(BigInt(args[0]));
case 454:return _teleport_nhlua_api_454(BigInt(args[0]));
case 455:return _teleport_nhlua_api_455(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 456:return _teleport_nhlua_api_456(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 457:return _teleport_nhlua_api_457(BigInt(args[0]),BigInt(args[1]),Number(args[2]));
case 458:return _teleport_nhlua_api_458(BigInt(args[0]),BigInt(args[1]));
case 459:return _teleport_nhlua_api_459(BigInt(args[0]));
case 460:return _teleport_nhlua_api_460(BigInt(args[0]));
case 461:return _teleport_nhlua_api_461(BigInt(args[0]));
case 462:return _teleport_nhlua_api_462(BigInt(args[0]),BigInt(args[1]));
case 463:return _teleport_nhlua_api_463(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 464:return _teleport_nhlua_api_464(BigInt(args[0]),BigInt(args[1]));
case 465:return Number(_teleport_nhlua_api_465(BigInt(args[0]),BigInt(args[1])));
case 466:return _teleport_nhlua_api_466(BigInt(args[0]),BigInt(args[1]),Number(args[2]),BigInt(args[3]),BigInt(args[4]));
case 467:return _teleport_nhlua_api_467(BigInt(args[0]),BigInt(args[1]),Number(args[2]),BigInt(args[3]),BigInt(args[4]));
case 468:return _teleport_nhlua_api_468(BigInt(args[0]));
case 469:return _teleport_nhlua_api_469(BigInt(args[0]),BigInt(args[1]));
case 470:return _teleport_nhlua_api_470(BigInt(args[0]),Number(args[1]));
case 471:return Number(_teleport_nhlua_api_471(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 472:return _teleport_nhlua_api_472(BigInt(args[0]));
case 473:return _teleport_nhlua_api_473(BigInt(args[0]),BigInt(args[1]));
case 474:return _teleport_nhlua_api_474(BigInt(args[0]),Number(args[1]));
case 475:return Number(_teleport_nhlua_api_475(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 476:return _teleport_nhlua_api_476(BigInt(args[0]));
case 477:return _teleport_nhlua_api_477(BigInt(args[0]),BigInt(args[1]),Number(args[2]));
case 478:return Number(_teleport_nhlua_api_478(BigInt(args[0]),BigInt(args[1])));
case 479:return Number(_teleport_nhlua_api_479(BigInt(args[0]),BigInt(args[1])));
case 480:return _teleport_nhlua_api_480(BigInt(args[0]));
case 481:return _teleport_nhlua_api_481(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 482:return _teleport_nhlua_api_482(BigInt(args[0]));
case 483:return _teleport_nhlua_api_483(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 484:return _teleport_nhlua_api_484(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 485:return _teleport_nhlua_api_485(BigInt(args[0]),Number(args[1]));
case 486:return _teleport_nhlua_api_486(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 487:return _teleport_nhlua_api_487(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),Number(args[3]));
case 488:return _teleport_nhlua_api_488(BigInt(args[0]));
case 489:return _teleport_nhlua_api_489(BigInt(args[0]),Number(args[1]));
case 490:return _teleport_nhlua_api_490(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),Number(args[3]));
case 491:return _teleport_nhlua_api_491(BigInt(args[0]),Number(args[1]));
case 492:return _teleport_nhlua_api_492(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),Number(args[3]));
case 493:return _teleport_nhlua_api_493(BigInt(args[0]),Number(args[1]));
case 494:return _teleport_nhlua_api_494(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),Number(args[3]));
case 495:return _teleport_nhlua_api_495(BigInt(args[0]));
case 496:return _teleport_nhlua_api_496(BigInt(args[0]),Number(args[1]));
case 497:return _teleport_nhlua_api_497(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),Number(args[3]));
case 498:return _teleport_nhlua_api_498(BigInt(args[0]),Number(args[1]));
case 499:return _teleport_nhlua_api_499(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),Number(args[3]));
case 500:return Number(_teleport_nhlua_api_500(BigInt(args[0])));
case 501:return _teleport_nhlua_api_501(BigInt(args[0]),BigInt(args[1]),Number(args[2]));
case 502:return _teleport_nhlua_api_502(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 503:return _teleport_nhlua_api_503(BigInt(args[0]),BigInt(args[1]));
case 504:return _teleport_nhlua_api_504(BigInt(args[0]),Number(args[1]),Number(args[2]),BigInt(args[3]),BigInt(args[4]));
case 505:return _teleport_nhlua_api_505(BigInt(args[0]),Number(args[1]));
case 506:return _teleport_nhlua_api_506(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),Number(args[3]));
case 507:return _teleport_nhlua_api_507(BigInt(args[0]),Number(args[1]));
case 508:return _teleport_nhlua_api_508(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),Number(args[3]));
case 509:return _teleport_nhlua_api_509(BigInt(args[0]));
case 510:return _teleport_nhlua_api_510(BigInt(args[0]),Number(args[1]));
case 511:return _teleport_nhlua_api_511(BigInt(args[0]));
case 512:return Number(_teleport_nhlua_api_512(BigInt(args[0]),Number(args[1])));
case 513:return Number(_teleport_nhlua_api_513(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 514:return _teleport_nhlua_api_514(BigInt(args[0]),BigInt(args[1]));
case 515:return _teleport_nhlua_api_515(BigInt(args[0]));
case 516:return _teleport_nhlua_api_516(BigInt(args[0]));
case 517:return Number(_teleport_nhlua_api_517(BigInt(args[0]),BigInt(args[1]),BigInt(args[2])));
case 518:return _teleport_nhlua_api_518(BigInt(args[0]),BigInt(args[1]));
case 519:return Number(_teleport_nhlua_api_519(BigInt(args[0]),BigInt(args[1])));
case 520:return Number(_teleport_nhlua_api_520(BigInt(args[0]),BigInt(args[1])));
case 521:return _teleport_nhlua_api_521(BigInt(args[0]));
case 522:return Number(_teleport_nhlua_api_522(BigInt(args[0]),BigInt(args[1])));
case 523:return _teleport_nhlua_api_523(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 524:return _teleport_nhlua_api_524(BigInt(args[0]));
case 525:return _teleport_nhlua_api_525(BigInt(args[0]),BigInt(args[1]),Number(args[2]),Number(args[3]));
default:throw Error("NHLUA API site "+site);}},indirect:(site,target,...args)=>{switch(site){
case 67:return _teleport_nhlua_api_67(pointer(target) , Number(args[0]),Number(args[1]));
case 89:return _teleport_nhlua_api_89(pointer(target) , Number(args[0]));
case 90:return _teleport_nhlua_api_90(pointer(target) , Number(args[0]),BigInt(args[1]));
case 107:return _teleport_nhlua_api_107(pointer(target) , Number(args[0]),BigInt(args[1]));
case 109:return _teleport_nhlua_api_109(pointer(target) , Number(args[0]));
case 113:return _teleport_nhlua_api_113(pointer(target) , Number(args[0]));
case 114:return _teleport_nhlua_api_114(pointer(target) , Number(args[0]),BigInt(args[1]));
case 123:return _teleport_nhlua_api_123(pointer(target) , Number(args[0]),BigInt(args[1]));
case 125:return _teleport_nhlua_api_125(pointer(target) , Number(args[0]));
default:throw Error("NHLUA indirect site "+site);}}};},
$teleportNhluaCall__deps:['$teleportNhluaServices'],
$teleportNhluaCall:function(name,...args){return Module.nethackPorted.nhlua(teleportNhluaServices(),name,...args);},
teleport_nhlua_resume__sig:'iji',teleport_nhlua_resume:function(token,resumed){return Module.teleportNhluaTransport.continuations.get(Number(token))(resumed);},
teleport_nhlua_js_l_nhcore_init__deps:["$teleportNhluaCall"],teleport_nhlua_js_l_nhcore_init__sig:"v",
teleport_nhlua_js_l_nhcore_init:function(){teleportNhluaCall("l_nhcore_init");},
teleport_nhlua_js_l_nhcore_done__deps:["$teleportNhluaCall"],teleport_nhlua_js_l_nhcore_done__sig:"v",
teleport_nhlua_js_l_nhcore_done:function(){teleportNhluaCall("l_nhcore_done");},
teleport_nhlua_js_l_nhcore_call__deps:["$teleportNhluaCall"],teleport_nhlua_js_l_nhcore_call__sig:"vi",
teleport_nhlua_js_l_nhcore_call:function(a0){teleportNhluaCall("l_nhcore_call",a0);},
teleport_nhlua_js_nhl_error__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_error__sig:"vpp",
teleport_nhlua_js_nhl_error:function(a0,a1){teleportNhluaCall("nhl_error",a0,a1);},
teleport_nhlua_js_lcheck_param_table__deps:["$teleportNhluaCall"],teleport_nhlua_js_lcheck_param_table__sig:"vp",
teleport_nhlua_js_lcheck_param_table:function(a0){teleportNhluaCall("lcheck_param_table",a0);},
teleport_nhlua_js_get_table_mapchr__deps:["$teleportNhluaCall"],teleport_nhlua_js_get_table_mapchr__sig:"ipp",
teleport_nhlua_js_get_table_mapchr:function(a0,a1){return teleportNhluaCall("get_table_mapchr",a0,a1);},
teleport_nhlua_js_get_table_mapchr_opt__deps:["$teleportNhluaCall"],teleport_nhlua_js_get_table_mapchr_opt__sig:"ippi",
teleport_nhlua_js_get_table_mapchr_opt:function(a0,a1,a2){return teleportNhluaCall("get_table_mapchr_opt",a0,a1,a2);},
teleport_nhlua_js_nhl_get_timertype__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_get_timertype__sig:"ipi",
teleport_nhlua_js_nhl_get_timertype:function(a0,a1){return teleportNhluaCall("nhl_get_timertype",a0,a1);},
teleport_nhlua_js_nhl_add_table_entry_int__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_add_table_entry_int__sig:"vppj",
teleport_nhlua_js_nhl_add_table_entry_int:function(a0,a1,a2){teleportNhluaCall("nhl_add_table_entry_int",a0,a1,a2);},
teleport_nhlua_js_nhl_add_table_entry_char__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_add_table_entry_char__sig:"vppi",
teleport_nhlua_js_nhl_add_table_entry_char:function(a0,a1,a2){teleportNhluaCall("nhl_add_table_entry_char",a0,a1,a2);},
teleport_nhlua_js_nhl_add_table_entry_str__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_add_table_entry_str__sig:"vppp",
teleport_nhlua_js_nhl_add_table_entry_str:function(a0,a1,a2){teleportNhluaCall("nhl_add_table_entry_str",a0,a1,a2);},
teleport_nhlua_js_nhl_add_table_entry_bool__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_add_table_entry_bool__sig:"vppi",
teleport_nhlua_js_nhl_add_table_entry_bool:function(a0,a1,a2){teleportNhluaCall("nhl_add_table_entry_bool",a0,a1,a2);},
teleport_nhlua_js_nhl_add_table_entry_region__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_add_table_entry_region__sig:"vppiiii",
teleport_nhlua_js_nhl_add_table_entry_region:function(a0,a1,a2,a3,a4,a5){teleportNhluaCall("nhl_add_table_entry_region",a0,a1,a2,a3,a4,a5);},
teleport_nhlua_js_splev_chr2typ__deps:["$teleportNhluaCall"],teleport_nhlua_js_splev_chr2typ__sig:"ii",
teleport_nhlua_js_splev_chr2typ:function(a0){return teleportNhluaCall("splev_chr2typ",a0);},
teleport_nhlua_js_check_mapchr__deps:["$teleportNhluaCall"],teleport_nhlua_js_check_mapchr__sig:"ip",
teleport_nhlua_js_check_mapchr:function(a0){return teleportNhluaCall("check_mapchr",a0);},
teleport_nhlua_js_splev_typ2chr__deps:["$teleportNhluaCall"],teleport_nhlua_js_splev_typ2chr__sig:"ii",
teleport_nhlua_js_splev_typ2chr:function(a0){return teleportNhluaCall("splev_typ2chr",a0);},
teleport_nhlua_js_nhl_gettrap__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_gettrap__sig:"ip",
teleport_nhlua_js_nhl_gettrap:function(a0){return teleportNhluaCall("nhl_gettrap",a0);},
teleport_nhlua_js_nhl_deltrap__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_deltrap__sig:"ip",
teleport_nhlua_js_nhl_deltrap:function(a0){return teleportNhluaCall("nhl_deltrap",a0);},
teleport_nhlua_js_nhl_get_xy_params__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_get_xy_params__sig:"ippp",
teleport_nhlua_js_nhl_get_xy_params:function(a0,a1,a2){return teleportNhluaCall("nhl_get_xy_params",a0,a1,a2);},
teleport_nhlua_js_nhl_getmap__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_getmap__sig:"ip",
teleport_nhlua_js_nhl_getmap:function(a0){return teleportNhluaCall("nhl_getmap",a0);},
teleport_nhlua_js_nhl_impossible__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_impossible__sig:"ip",
teleport_nhlua_js_nhl_impossible:function(a0){return teleportNhluaCall("nhl_impossible",a0);},
teleport_nhlua_js_nhl_pline__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_pline__sig:"ip",
teleport_nhlua_js_nhl_pline:function(a0){return teleportNhluaCall("nhl_pline",a0);},
teleport_nhlua_js_nhl_verbalize__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_verbalize__sig:"ip",
teleport_nhlua_js_nhl_verbalize:function(a0){return teleportNhluaCall("nhl_verbalize",a0);},
teleport_nhlua_js_nhl_parse_config__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_parse_config__sig:"ip",
teleport_nhlua_js_nhl_parse_config:function(a0){return teleportNhluaCall("nhl_parse_config",a0);},
teleport_nhlua_js_nhl_get_config__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_get_config__sig:"ip",
teleport_nhlua_js_nhl_get_config:function(a0){return teleportNhluaCall("nhl_get_config",a0);},
teleport_nhlua_js_nhl_getlin__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_getlin__sig:"ip",
teleport_nhlua_js_nhl_getlin:function(a0){return teleportNhluaCall("nhl_getlin",a0);},
teleport_nhlua_js_nhl_menu__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_menu__sig:"ip",
teleport_nhlua_js_nhl_menu:function(a0){return teleportNhluaCall("nhl_menu",a0);},
teleport_nhlua_js_nhl_text__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_text__sig:"ip",
teleport_nhlua_js_nhl_text:function(a0){return teleportNhluaCall("nhl_text",a0);},
teleport_nhlua_js_nhl_makeplural__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_makeplural__sig:"ip",
teleport_nhlua_js_nhl_makeplural:function(a0){return teleportNhluaCall("nhl_makeplural",a0);},
teleport_nhlua_js_nhl_makesingular__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_makesingular__sig:"ip",
teleport_nhlua_js_nhl_makesingular:function(a0){return teleportNhluaCall("nhl_makesingular",a0);},
teleport_nhlua_js_nhl_s_suffix__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_s_suffix__sig:"ip",
teleport_nhlua_js_nhl_s_suffix:function(a0){return teleportNhluaCall("nhl_s_suffix",a0);},
teleport_nhlua_js_nhl_ing_suffix__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_ing_suffix__sig:"ip",
teleport_nhlua_js_nhl_ing_suffix:function(a0){return teleportNhluaCall("nhl_ing_suffix",a0);},
teleport_nhlua_js_nhl_an__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_an__sig:"ip",
teleport_nhlua_js_nhl_an:function(a0){return teleportNhluaCall("nhl_an",a0);},
teleport_nhlua_js_nhl_lua_rnglog_ctx_enabled__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_lua_rnglog_ctx_enabled__sig:"i",
teleport_nhlua_js_nhl_lua_rnglog_ctx_enabled:function(){return teleportNhluaCall("nhl_lua_rnglog_ctx_enabled");},
teleport_nhlua_js_nhl_rnglog_set_lua_caller__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_rnglog_set_lua_caller__sig:"vpp",
teleport_nhlua_js_nhl_rnglog_set_lua_caller:function(a0,a1){teleportNhluaCall("nhl_rnglog_set_lua_caller",a0,a1);},
teleport_nhlua_js_nhl_rn2__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_rn2__sig:"ip",
teleport_nhlua_js_nhl_rn2:function(a0){return teleportNhluaCall("nhl_rn2",a0);},
teleport_nhlua_js_nhl_random__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_random__sig:"ip",
teleport_nhlua_js_nhl_random:function(a0){return teleportNhluaCall("nhl_random",a0);},
teleport_nhlua_js_nhl_level_difficulty__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_level_difficulty__sig:"ip",
teleport_nhlua_js_nhl_level_difficulty:function(a0){return teleportNhluaCall("nhl_level_difficulty",a0);},
teleport_nhlua_js_nhl_is_genocided__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_is_genocided__sig:"ip",
teleport_nhlua_js_nhl_is_genocided:function(a0){return teleportNhluaCall("nhl_is_genocided",a0);},
teleport_nhlua_js_nhl_get_debug_themerm_name__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_get_debug_themerm_name__sig:"ip",
teleport_nhlua_js_nhl_get_debug_themerm_name:function(a0){return teleportNhluaCall("nhl_get_debug_themerm_name",a0);},
teleport_nhlua_js_get_table_int__deps:["$teleportNhluaCall"],teleport_nhlua_js_get_table_int__sig:"ipp",
teleport_nhlua_js_get_table_int:function(a0,a1){return teleportNhluaCall("get_table_int",a0,a1);},
teleport_nhlua_js_get_table_int_opt__deps:["$teleportNhluaCall"],teleport_nhlua_js_get_table_int_opt__sig:"ippi",
teleport_nhlua_js_get_table_int_opt:function(a0,a1,a2){return teleportNhluaCall("get_table_int_opt",a0,a1,a2);},
teleport_nhlua_js_get_table_str__deps:["$teleportNhluaCall"],teleport_nhlua_js_get_table_str__sig:"ppp",
teleport_nhlua_js_get_table_str:function(a0,a1){return BigInt(teleportNhluaCall("get_table_str",a0,a1)??0);},
teleport_nhlua_js_get_table_str_opt__deps:["$teleportNhluaCall"],teleport_nhlua_js_get_table_str_opt__sig:"pppp",
teleport_nhlua_js_get_table_str_opt:function(a0,a1,a2){return BigInt(teleportNhluaCall("get_table_str_opt",a0,a1,a2)??0);},
teleport_nhlua_js_get_table_boolean__deps:["$teleportNhluaCall"],teleport_nhlua_js_get_table_boolean__sig:"ipp",
teleport_nhlua_js_get_table_boolean:function(a0,a1){return teleportNhluaCall("get_table_boolean",a0,a1);},
teleport_nhlua_js_get_table_boolean_opt__deps:["$teleportNhluaCall"],teleport_nhlua_js_get_table_boolean_opt__sig:"ippi",
teleport_nhlua_js_get_table_boolean_opt:function(a0,a1,a2){return teleportNhluaCall("get_table_boolean_opt",a0,a1,a2);},
teleport_nhlua_js_get_table_option__deps:["$teleportNhluaCall"],teleport_nhlua_js_get_table_option__sig:"ipppp",
teleport_nhlua_js_get_table_option:function(a0,a1,a2,a3){return teleportNhluaCall("get_table_option",a0,a1,a2,a3);},
teleport_nhlua_js_nhl_dnum_name__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_dnum_name__sig:"ip",
teleport_nhlua_js_nhl_dnum_name:function(a0){return teleportNhluaCall("nhl_dnum_name",a0);},
teleport_nhlua_js_nhl_int_to_pm_name__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_int_to_pm_name__sig:"ip",
teleport_nhlua_js_nhl_int_to_pm_name:function(a0){return teleportNhluaCall("nhl_int_to_pm_name",a0);},
teleport_nhlua_js_nhl_int_to_obj_name__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_int_to_obj_name__sig:"ip",
teleport_nhlua_js_nhl_int_to_obj_name:function(a0){return teleportNhluaCall("nhl_int_to_obj_name",a0);},
teleport_nhlua_js_nhl_variable__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_variable__sig:"ip",
teleport_nhlua_js_nhl_variable:function(a0){return teleportNhluaCall("nhl_variable",a0);},
teleport_nhlua_js_get_nh_lua_variables__deps:["$teleportNhluaCall"],teleport_nhlua_js_get_nh_lua_variables__sig:"p",
teleport_nhlua_js_get_nh_lua_variables:function(){return BigInt(teleportNhluaCall("get_nh_lua_variables")??0);},
teleport_nhlua_js_save_luadata__deps:["$teleportNhluaCall"],teleport_nhlua_js_save_luadata__sig:"vp",
teleport_nhlua_js_save_luadata:function(a0){teleportNhluaCall("save_luadata",a0);},
teleport_nhlua_js_restore_luadata__deps:["$teleportNhluaCall"],teleport_nhlua_js_restore_luadata__sig:"vp",
teleport_nhlua_js_restore_luadata:function(a0){teleportNhluaCall("restore_luadata",a0);},
teleport_nhlua_js_nhl_stairways__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_stairways__sig:"ip",
teleport_nhlua_js_nhl_stairways:function(a0){return teleportNhluaCall("nhl_stairways",a0);},
teleport_nhlua_js_nhl_test__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_test__sig:"ip",
teleport_nhlua_js_nhl_test:function(a0){return teleportNhluaCall("nhl_test",a0);},
teleport_nhlua_js_nhl_pushkey__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_pushkey__sig:"ip",
teleport_nhlua_js_nhl_pushkey:function(a0){return teleportNhluaCall("nhl_pushkey",a0);},
teleport_nhlua_js_nhl_doturn__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_doturn__sig:"ip",
teleport_nhlua_js_nhl_doturn:function(a0){return teleportNhluaCall("nhl_doturn",a0);},
teleport_nhlua_js_nhl_debug_flags__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_debug_flags__sig:"ip",
teleport_nhlua_js_nhl_debug_flags:function(a0){return teleportNhluaCall("nhl_debug_flags",a0);},
teleport_nhlua_js_nhl_flip_level__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_flip_level__sig:"ip",
teleport_nhlua_js_nhl_flip_level:function(a0){return teleportNhluaCall("nhl_flip_level",a0);},
teleport_nhlua_js_nhl_timer_has_at__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_timer_has_at__sig:"ip",
teleport_nhlua_js_nhl_timer_has_at:function(a0){return teleportNhluaCall("nhl_timer_has_at",a0);},
teleport_nhlua_js_nhl_timer_peek_at__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_timer_peek_at__sig:"ip",
teleport_nhlua_js_nhl_timer_peek_at:function(a0){return teleportNhluaCall("nhl_timer_peek_at",a0);},
teleport_nhlua_js_nhl_timer_stop_at__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_timer_stop_at__sig:"ip",
teleport_nhlua_js_nhl_timer_stop_at:function(a0){return teleportNhluaCall("nhl_timer_stop_at",a0);},
teleport_nhlua_js_nhl_timer_start_at__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_timer_start_at__sig:"ip",
teleport_nhlua_js_nhl_timer_start_at:function(a0){return teleportNhluaCall("nhl_timer_start_at",a0);},
teleport_nhlua_js_nhl_get_cmd_key__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_get_cmd_key__sig:"ip",
teleport_nhlua_js_nhl_get_cmd_key:function(a0){return teleportNhluaCall("nhl_get_cmd_key",a0);},
teleport_nhlua_js_nhl_callback__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_callback__sig:"ip",
teleport_nhlua_js_nhl_callback:function(a0){return teleportNhluaCall("nhl_callback",a0);},
teleport_nhlua_js_nhl_gamestate__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_gamestate__sig:"ip",
teleport_nhlua_js_nhl_gamestate:function(a0){return teleportNhluaCall("nhl_gamestate",a0);},
teleport_nhlua_js_free_tutorial__deps:["$teleportNhluaCall"],teleport_nhlua_js_free_tutorial__sig:"v",
teleport_nhlua_js_free_tutorial:function(){teleportNhluaCall("free_tutorial");},
teleport_nhlua_js_tutorial__deps:["$teleportNhluaCall"],teleport_nhlua_js_tutorial__sig:"vi",
teleport_nhlua_js_tutorial:function(a0){teleportNhluaCall("tutorial",a0);},
teleport_nhlua_js_init_nhc_data__deps:["$teleportNhluaCall"],teleport_nhlua_js_init_nhc_data__sig:"vp",
teleport_nhlua_js_init_nhc_data:function(a0){teleportNhluaCall("init_nhc_data",a0);},
teleport_nhlua_js_nhl_push_anything__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_push_anything__sig:"ipip",
teleport_nhlua_js_nhl_push_anything:function(a0,a1,a2){return teleportNhluaCall("nhl_push_anything",a0,a1,a2);},
teleport_nhlua_js_nhl_meta_u_index__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_meta_u_index__sig:"ip",
teleport_nhlua_js_nhl_meta_u_index:function(a0){return teleportNhluaCall("nhl_meta_u_index",a0);},
teleport_nhlua_js_nhl_meta_u_newindex__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_meta_u_newindex__sig:"ip",
teleport_nhlua_js_nhl_meta_u_newindex:function(a0){return teleportNhluaCall("nhl_meta_u_newindex",a0);},
teleport_nhlua_js_nhl_u_clear_inventory__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_u_clear_inventory__sig:"ip",
teleport_nhlua_js_nhl_u_clear_inventory:function(a0){return teleportNhluaCall("nhl_u_clear_inventory",a0);},
teleport_nhlua_js_nhl_u_giveobj__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_u_giveobj__sig:"ip",
teleport_nhlua_js_nhl_u_giveobj:function(a0){return teleportNhluaCall("nhl_u_giveobj",a0);},
teleport_nhlua_js_init_u_data__deps:["$teleportNhluaCall"],teleport_nhlua_js_init_u_data__sig:"vp",
teleport_nhlua_js_init_u_data:function(a0){teleportNhluaCall("init_u_data",a0);},
teleport_nhlua_js_traceback_handler__deps:["$teleportNhluaCall"],teleport_nhlua_js_traceback_handler__sig:"ip",
teleport_nhlua_js_traceback_handler:function(a0){return teleportNhluaCall("traceback_handler",a0);},
teleport_nhlua_js_nhl_getmeminuse__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_getmeminuse__sig:"ip",
teleport_nhlua_js_nhl_getmeminuse:function(a0){return teleportNhluaCall("nhl_getmeminuse",a0);},
teleport_nhlua_js_nhl_pcall__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_pcall__sig:"ipiip",
teleport_nhlua_js_nhl_pcall:function(a0,a1,a2,a3){return teleportNhluaCall("nhl_pcall",a0,a1,a2,a3);},
teleport_nhlua_js_nhl_pcall_handle__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_pcall_handle__sig:"ipiipi",
teleport_nhlua_js_nhl_pcall_handle:function(a0,a1,a2,a3,a4){return teleportNhluaCall("nhl_pcall_handle",a0,a1,a2,a3,a4);},
teleport_nhlua_js_nhl_loadlua__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_loadlua__sig:"ipp",
teleport_nhlua_js_nhl_loadlua:function(a0,a1){return teleportNhluaCall("nhl_loadlua",a0,a1);},
teleport_nhlua_js_nhl_init__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_init__sig:"pp",
teleport_nhlua_js_nhl_init:function(a0){return BigInt(teleportNhluaCall("nhl_init",a0)??0);},
teleport_nhlua_js_nhl_done__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_done__sig:"vp",
teleport_nhlua_js_nhl_done:function(a0){teleportNhluaCall("nhl_done",a0);},
teleport_nhlua_js_load_lua__deps:["$teleportNhluaCall"],teleport_nhlua_js_load_lua__sig:"ipp",
teleport_nhlua_js_load_lua:function(a0,a1){return teleportNhluaCall("load_lua",a0,a1);},
teleport_nhlua_js_get_lua_version__deps:["$teleportNhluaCall"],teleport_nhlua_js_get_lua_version__sig:"p",
teleport_nhlua_js_get_lua_version:function(){return BigInt(teleportNhluaCall("get_lua_version")??0);},
teleport_nhlua_js_nhl_clearfromtable__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_clearfromtable__sig:"vpiip",
teleport_nhlua_js_nhl_clearfromtable:function(a0,a1,a2,a3){teleportNhluaCall("nhl_clearfromtable",a0,a1,a2,a3);},
teleport_nhlua_js_end_luapat__deps:["$teleportNhluaCall"],teleport_nhlua_js_end_luapat__sig:"v",
teleport_nhlua_js_end_luapat:function(){teleportNhluaCall("end_luapat");},
teleport_nhlua_js_nhl_pushhooked_open_table__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_pushhooked_open_table__sig:"vp",
teleport_nhlua_js_nhl_pushhooked_open_table:function(a0){teleportNhluaCall("nhl_pushhooked_open_table",a0);},
teleport_nhlua_js_nhlL_openlibs__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhlL_openlibs__sig:"vpi",
teleport_nhlua_js_nhlL_openlibs:function(a0,a1){teleportNhluaCall("nhlL_openlibs",a0,a1);},
teleport_nhlua_js_nhl_alloc__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_alloc__sig:"pppjj",
teleport_nhlua_js_nhl_alloc:function(a0,a1,a2,a3){return BigInt(teleportNhluaCall("nhl_alloc",a0,a1,a2,a3)??0);},
teleport_nhlua_js_nhl_panic__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_panic__sig:"ip",
teleport_nhlua_js_nhl_panic:function(a0){return teleportNhluaCall("nhl_panic",a0);},
teleport_nhlua_js_nhl_warn__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_warn__sig:"vppi",
teleport_nhlua_js_nhl_warn:function(a0,a1,a2){teleportNhluaCall("nhl_warn",a0,a1,a2);},
teleport_nhlua_js_nhl_hookfn__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhl_hookfn__sig:"vpp",
teleport_nhlua_js_nhl_hookfn:function(a0,a1){teleportNhluaCall("nhl_hookfn",a0,a1);},
teleport_nhlua_js_nhlL_newstate__deps:["$teleportNhluaCall"],teleport_nhlua_js_nhlL_newstate__sig:"ppp",
teleport_nhlua_js_nhlL_newstate:function(a0,a1){return BigInt(teleportNhluaCall("nhlL_newstate",a0,a1)??0);},
});
