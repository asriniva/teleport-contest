// TRAP typed foreign calls and callback dispatch, no game source policy.
addToLibrary({
$teleportTrapServices__deps:["teleport_trap_storage", "teleport_trap_global", "teleport_trap_function_pointer", "teleport_trap_literal_storage", "teleport_trap_literal_capacity", "teleport_trap_layout_count", "teleport_trap_layout_name", "teleport_trap_layout_value", "teleport_trap_api_0", "teleport_trap_api_1", "teleport_trap_api_2", "teleport_trap_api_3", "teleport_trap_api_4", "teleport_trap_api_5", "teleport_trap_api_6", "teleport_trap_api_7", "teleport_trap_api_8", "teleport_trap_api_9", "teleport_trap_api_10", "teleport_trap_api_11", "teleport_trap_api_12", "teleport_trap_api_13", "teleport_trap_api_14", "teleport_trap_api_15", "teleport_trap_api_16", "teleport_trap_api_17", "teleport_trap_api_18", "teleport_trap_api_19", "teleport_trap_api_20", "teleport_trap_api_21", "teleport_trap_api_22", "teleport_trap_api_23", "teleport_trap_api_24", "teleport_trap_api_25", "teleport_trap_api_26", "teleport_trap_api_27", "teleport_trap_api_28", "teleport_trap_api_29", "teleport_trap_api_30", "teleport_trap_api_31", "teleport_trap_api_32", "teleport_trap_api_33", "teleport_trap_api_34", "teleport_trap_api_35", "teleport_trap_api_36", "teleport_trap_api_37", "teleport_trap_api_38", "teleport_trap_api_39", "teleport_trap_api_40", "teleport_trap_api_41", "teleport_trap_api_42", "teleport_trap_api_43", "teleport_trap_api_44", "teleport_trap_api_45", "teleport_trap_api_46", "teleport_trap_api_47", "teleport_trap_api_48", "teleport_trap_api_49", "teleport_trap_api_50", "teleport_trap_api_51", "teleport_trap_api_52", "teleport_trap_api_53", "teleport_trap_api_54", "teleport_trap_api_55", "teleport_trap_api_56", "teleport_trap_api_57", "teleport_trap_api_58", "teleport_trap_api_59", "teleport_trap_api_60", "teleport_trap_api_61", "teleport_trap_api_62", "teleport_trap_api_63", "teleport_trap_api_64", "teleport_trap_api_65", "teleport_trap_api_66", "teleport_trap_api_67", "teleport_trap_api_68", "teleport_trap_api_69", "teleport_trap_api_70", "teleport_trap_api_71", "teleport_trap_api_72", "teleport_trap_api_73", "teleport_trap_api_74", "teleport_trap_api_75", "teleport_trap_api_76", "teleport_trap_api_77", "teleport_trap_api_78", "teleport_trap_api_79", "teleport_trap_api_80", "teleport_trap_api_81", "teleport_trap_api_82", "teleport_trap_api_83", "teleport_trap_api_84", "teleport_trap_api_85", "teleport_trap_api_86", "teleport_trap_api_87", "teleport_trap_api_88", "teleport_trap_api_89", "teleport_trap_api_90", "teleport_trap_api_91", "teleport_trap_api_92", "teleport_trap_api_93", "teleport_trap_api_94", "teleport_trap_api_95", "teleport_trap_api_96", "teleport_trap_api_97", "teleport_trap_api_98", "teleport_trap_api_99", "teleport_trap_api_100", "teleport_trap_api_101", "teleport_trap_api_102", "teleport_trap_api_103", "teleport_trap_api_104", "teleport_trap_api_105", "teleport_trap_api_106", "teleport_trap_api_107", "teleport_trap_api_108", "teleport_trap_api_109", "teleport_trap_api_110", "teleport_trap_api_111", "teleport_trap_api_112", "teleport_trap_api_113", "teleport_trap_api_114", "teleport_trap_api_115", "teleport_trap_api_116", "teleport_trap_api_117", "teleport_trap_api_118", "teleport_trap_api_119", "teleport_trap_api_120", "teleport_trap_api_121", "teleport_trap_api_122", "teleport_trap_api_123", "teleport_trap_api_124", "teleport_trap_api_125", "teleport_trap_api_126", "teleport_trap_api_127", "teleport_trap_api_128", "teleport_trap_api_129", "teleport_trap_api_130", "teleport_trap_api_131", "teleport_trap_api_132", "teleport_trap_api_133", "teleport_trap_api_134", "teleport_trap_api_135", "teleport_trap_api_136", "teleport_trap_api_137", "teleport_trap_api_138", "teleport_trap_api_139", "teleport_trap_api_140", "teleport_trap_api_141", "teleport_trap_api_142", "teleport_trap_api_143", "teleport_trap_api_144", "teleport_trap_api_145", "teleport_trap_api_146", "teleport_trap_api_147", "teleport_trap_api_148", "teleport_trap_api_149", "teleport_trap_api_150", "teleport_trap_api_151", "teleport_trap_api_152", "teleport_trap_api_153", "teleport_trap_api_154", "teleport_trap_api_155", "teleport_trap_api_156", "teleport_trap_api_157", "teleport_trap_api_158", "teleport_trap_api_159", "teleport_trap_api_160", "teleport_trap_api_161", "teleport_trap_api_162", "teleport_trap_api_163", "teleport_trap_api_164", "teleport_trap_api_165", "teleport_trap_api_166", "teleport_trap_api_167", "teleport_trap_api_168", "teleport_trap_api_169", "teleport_trap_api_170", "teleport_trap_api_171", "teleport_trap_api_172", "teleport_trap_api_173", "teleport_trap_api_174", "teleport_trap_api_175", "teleport_trap_api_176", "teleport_trap_api_177", "teleport_trap_api_178", "teleport_trap_api_179", "teleport_trap_api_180", "teleport_trap_api_181", "teleport_trap_api_182", "teleport_trap_api_183", "teleport_trap_api_184", "teleport_trap_api_185", "teleport_trap_api_186", "teleport_trap_api_187", "teleport_trap_api_188", "teleport_trap_api_189", "teleport_trap_api_190", "teleport_trap_api_191", "teleport_trap_api_192", "teleport_trap_api_193", "teleport_trap_api_194", "teleport_trap_api_195", "teleport_trap_api_196", "teleport_trap_api_197", "teleport_trap_api_198", "teleport_trap_api_199", "teleport_trap_api_200", "teleport_trap_api_201", "teleport_trap_api_202", "teleport_trap_api_203", "teleport_trap_api_204", "teleport_trap_api_205", "teleport_trap_api_206", "teleport_trap_api_207", "teleport_trap_api_208", "teleport_trap_api_209", "teleport_trap_api_210", "teleport_trap_api_211", "teleport_trap_api_212", "teleport_trap_api_213", "teleport_trap_api_214", "teleport_trap_api_215", "teleport_trap_api_216", "teleport_trap_api_217", "teleport_trap_api_218", "teleport_trap_api_219", "teleport_trap_api_220", "teleport_trap_api_221", "teleport_trap_api_222", "teleport_trap_api_223", "teleport_trap_api_224", "teleport_trap_api_225", "teleport_trap_api_226", "teleport_trap_api_227", "teleport_trap_api_228", "teleport_trap_api_229", "teleport_trap_api_230", "teleport_trap_api_231", "teleport_trap_api_232", "teleport_trap_api_233", "teleport_trap_api_234", "teleport_trap_api_235", "teleport_trap_api_236", "teleport_trap_api_237", "teleport_trap_api_238", "teleport_trap_api_239", "teleport_trap_api_240", "teleport_trap_api_241", "teleport_trap_api_242", "teleport_trap_api_243", "teleport_trap_api_244", "teleport_trap_api_245", "teleport_trap_api_246", "teleport_trap_api_247", "teleport_trap_api_248", "teleport_trap_api_249", "teleport_trap_api_250", "teleport_trap_api_251", "teleport_trap_api_252", "teleport_trap_api_253", "teleport_trap_api_254", "teleport_trap_api_255", "teleport_trap_api_256", "teleport_trap_api_257", "teleport_trap_api_258", "teleport_trap_api_259", "teleport_trap_api_260", "teleport_trap_api_261", "teleport_trap_api_262", "teleport_trap_api_263", "teleport_trap_api_264", "teleport_trap_api_265", "teleport_trap_api_266", "teleport_trap_api_267", "teleport_trap_api_268", "teleport_trap_api_269", "teleport_trap_api_270", "teleport_trap_api_271", "teleport_trap_api_272", "teleport_trap_api_273", "teleport_trap_api_274", "teleport_trap_api_275", "teleport_trap_api_276", "teleport_trap_api_277", "teleport_trap_api_278", "teleport_trap_api_279", "teleport_trap_api_280", "teleport_trap_api_281", "teleport_trap_api_282", "teleport_trap_api_283", "teleport_trap_api_284", "teleport_trap_api_285", "teleport_trap_api_286", "teleport_trap_api_287", "teleport_trap_api_288", "teleport_trap_api_289", "teleport_trap_api_290", "teleport_trap_api_291", "teleport_trap_api_292", "teleport_trap_api_293", "teleport_trap_api_294", "teleport_trap_api_295", "teleport_trap_api_296", "teleport_trap_api_297", "teleport_trap_api_298", "teleport_trap_api_299", "teleport_trap_api_300", "teleport_trap_api_301", "teleport_trap_api_302", "teleport_trap_api_303", "teleport_trap_api_304", "teleport_trap_api_305", "teleport_trap_api_306", "teleport_trap_api_307", "teleport_trap_api_308", "teleport_trap_api_309", "teleport_trap_api_310", "teleport_trap_api_311", "teleport_trap_api_312", "teleport_trap_api_313", "teleport_trap_api_314", "teleport_trap_api_315", "teleport_trap_api_316", "teleport_trap_api_317", "teleport_trap_api_318", "teleport_trap_api_319", "teleport_trap_api_320", "teleport_trap_api_321", "teleport_trap_api_322", "teleport_trap_api_323", "teleport_trap_api_324", "teleport_trap_api_325", "teleport_trap_api_326", "teleport_trap_api_327", "teleport_trap_api_328", "teleport_trap_api_329", "teleport_trap_api_330", "teleport_trap_api_331", "teleport_trap_api_332", "teleport_trap_api_333", "teleport_trap_api_334", "teleport_trap_api_335", "teleport_trap_api_336", "teleport_trap_api_337", "teleport_trap_api_338", "teleport_trap_api_339", "teleport_trap_api_340", "teleport_trap_api_341", "teleport_trap_api_342", "teleport_trap_api_343", "teleport_trap_api_344", "teleport_trap_api_345", "teleport_trap_api_346", "teleport_trap_api_347", "teleport_trap_api_348", "teleport_trap_api_349", "teleport_trap_api_350", "teleport_trap_api_351", "teleport_trap_api_352", "teleport_trap_api_353", "teleport_trap_api_354", "teleport_trap_api_355", "teleport_trap_api_356", "teleport_trap_api_357", "teleport_trap_api_358", "teleport_trap_api_359", "teleport_trap_api_360", "teleport_trap_api_361", "teleport_trap_api_362", "teleport_trap_api_363", "teleport_trap_api_364", "teleport_trap_api_365", "teleport_trap_api_366", "teleport_trap_api_367", "teleport_trap_api_368", "teleport_trap_api_369", "teleport_trap_api_370", "teleport_trap_api_371", "teleport_trap_api_372", "teleport_trap_api_373", "teleport_trap_api_374", "teleport_trap_api_375", "teleport_trap_api_376", "teleport_trap_api_377", "teleport_trap_api_378", "teleport_trap_api_379", "teleport_trap_api_380", "teleport_trap_api_381", "teleport_trap_api_382", "teleport_trap_api_383", "teleport_trap_api_384", "teleport_trap_api_385", "teleport_trap_api_386", "teleport_trap_api_387", "teleport_trap_api_388", "teleport_trap_api_389", "teleport_trap_api_390", "teleport_trap_api_391", "teleport_trap_api_392", "teleport_trap_api_393", "teleport_trap_api_394", "teleport_trap_api_395", "teleport_trap_api_396", "teleport_trap_api_397", "teleport_trap_api_398", "teleport_trap_api_399", "teleport_trap_api_400", "teleport_trap_api_401", "teleport_trap_api_402", "teleport_trap_api_403", "teleport_trap_api_404", "teleport_trap_api_405", "teleport_trap_api_406", "teleport_trap_api_407", "teleport_trap_api_408", "teleport_trap_api_409", "teleport_trap_api_410", "teleport_trap_api_411", "teleport_trap_api_412", "teleport_trap_api_413", "teleport_trap_api_414", "teleport_trap_api_415", "teleport_trap_api_416", "teleport_trap_api_417", "teleport_trap_api_418", "teleport_trap_api_419", "teleport_trap_api_420", "teleport_trap_api_421", "teleport_trap_api_422", "teleport_trap_api_423", "teleport_trap_api_424", "teleport_trap_api_425", "teleport_trap_api_426", "teleport_trap_api_427", "teleport_trap_api_428", "teleport_trap_api_429", "teleport_trap_api_430", "teleport_trap_api_431", "teleport_trap_api_432", "teleport_trap_api_433", "teleport_trap_api_434", "teleport_trap_api_435", "teleport_trap_api_436", "teleport_trap_api_437", "teleport_trap_api_438", "teleport_trap_api_439", "teleport_trap_api_440", "teleport_trap_api_441", "teleport_trap_api_442", "teleport_trap_api_443", "teleport_trap_api_444", "teleport_trap_api_445", "teleport_trap_api_446", "teleport_trap_api_447", "teleport_trap_api_448", "teleport_trap_api_449", "teleport_trap_api_450", "teleport_trap_api_451", "teleport_trap_api_452", "teleport_trap_api_453", "teleport_trap_api_454", "teleport_trap_api_455", "teleport_trap_api_456", "teleport_trap_api_457", "teleport_trap_api_458", "teleport_trap_api_459", "teleport_trap_api_460", "teleport_trap_api_461", "teleport_trap_api_462", "teleport_trap_api_463", "teleport_trap_api_464", "teleport_trap_api_465", "teleport_trap_api_466", "teleport_trap_api_467", "teleport_trap_api_468", "teleport_trap_api_469", "teleport_trap_api_470", "teleport_trap_api_471", "teleport_trap_api_472", "teleport_trap_api_473", "teleport_trap_api_474", "teleport_trap_api_475", "teleport_trap_api_476", "teleport_trap_api_477", "teleport_trap_api_478", "teleport_trap_api_479", "teleport_trap_api_480", "teleport_trap_api_481", "teleport_trap_api_482", "teleport_trap_api_483", "teleport_trap_api_484", "teleport_trap_api_485", "teleport_trap_api_486", "teleport_trap_api_487", "teleport_trap_api_488", "teleport_trap_api_489", "teleport_trap_api_490", "teleport_trap_api_491", "teleport_trap_api_492", "teleport_trap_api_493", "teleport_trap_api_494", "teleport_trap_api_495", "teleport_trap_api_496", "teleport_trap_api_497", "teleport_trap_api_498", "teleport_trap_api_499", "teleport_trap_api_500", "teleport_trap_api_501", "teleport_trap_api_502", "teleport_trap_api_503", "teleport_trap_api_504", "teleport_trap_api_505", "teleport_trap_api_506", "teleport_trap_api_507", "teleport_trap_api_508", "teleport_trap_api_509", "teleport_trap_api_510", "teleport_trap_api_511", "teleport_trap_api_512", "teleport_trap_api_513", "teleport_trap_api_514", "teleport_trap_api_515", "teleport_trap_api_516", "teleport_trap_api_517", "teleport_trap_api_518", "teleport_trap_api_519", "teleport_trap_api_520", "teleport_trap_api_521", "teleport_trap_api_522", "teleport_trap_api_523", "teleport_trap_api_524", "teleport_trap_api_525", "teleport_trap_api_526", "teleport_trap_api_527", "teleport_trap_api_528", "teleport_trap_api_529", "teleport_trap_api_530", "teleport_trap_api_531", "teleport_trap_api_532", "teleport_trap_api_533", "teleport_trap_api_534", "teleport_trap_api_535", "teleport_trap_api_536", "teleport_trap_api_537", "teleport_trap_api_538", "teleport_trap_api_539", "teleport_trap_api_540", "teleport_trap_api_541", "teleport_trap_api_542", "teleport_trap_api_543", "teleport_trap_api_544", "teleport_trap_api_545", "teleport_trap_api_546", "teleport_trap_api_547", "teleport_trap_api_548", "teleport_trap_api_549", "teleport_trap_api_550", "teleport_trap_api_551", "teleport_trap_api_552", "teleport_trap_api_553", "teleport_trap_api_554", "teleport_trap_api_555", "teleport_trap_api_556", "teleport_trap_api_557", "teleport_trap_api_558", "teleport_trap_api_559", "teleport_trap_api_560", "teleport_trap_api_561", "teleport_trap_api_562", "teleport_trap_api_563", "teleport_trap_api_564", "teleport_trap_api_565", "teleport_trap_api_566", "teleport_trap_api_567", "teleport_trap_api_568", "teleport_trap_api_569", "teleport_trap_api_570", "teleport_trap_api_571", "teleport_trap_api_572", "teleport_trap_api_573", "teleport_trap_api_574", "teleport_trap_api_575", "teleport_trap_api_576", "teleport_trap_api_577", "teleport_trap_api_578", "teleport_trap_api_579", "teleport_trap_api_580", "teleport_trap_api_581", "teleport_trap_api_582", "teleport_trap_api_583", "teleport_trap_api_584", "teleport_trap_api_585", "teleport_trap_api_586", "teleport_trap_api_587", "teleport_trap_api_588", "teleport_trap_api_589", "teleport_trap_api_590", "teleport_trap_api_591", "teleport_trap_api_592", "teleport_trap_api_593", "teleport_trap_api_594", "teleport_trap_api_595", "teleport_trap_api_596", "teleport_trap_api_597", "teleport_trap_api_598", "teleport_trap_api_599", "teleport_trap_api_600", "teleport_trap_api_601", "teleport_trap_api_602", "teleport_trap_api_603", "teleport_trap_api_604", "teleport_trap_api_605", "teleport_trap_api_606", "teleport_trap_api_607", "teleport_trap_api_608", "teleport_trap_api_609", "teleport_trap_api_610", "teleport_trap_api_611", "teleport_trap_api_612", "teleport_trap_api_613", "teleport_trap_api_614", "teleport_trap_api_615", "teleport_trap_api_616", "teleport_trap_api_617", "teleport_trap_api_618", "teleport_trap_api_619", "teleport_trap_api_620", "teleport_trap_api_621", "teleport_trap_api_622", "teleport_trap_api_623", "teleport_trap_api_624", "teleport_trap_api_625", "teleport_trap_api_626", "teleport_trap_api_627", "teleport_trap_api_628", "teleport_trap_api_629", "teleport_trap_api_630", "teleport_trap_api_631", "teleport_trap_api_632", "teleport_trap_api_633", "teleport_trap_api_634", "teleport_trap_api_635", "teleport_trap_api_636", "teleport_trap_api_637", "teleport_trap_api_638", "teleport_trap_api_639", "teleport_trap_api_640", "teleport_trap_api_641", "teleport_trap_api_642", "teleport_trap_api_643", "teleport_trap_api_644", "teleport_trap_api_645", "teleport_trap_api_646", "teleport_trap_api_647", "teleport_trap_api_648", "teleport_trap_api_649", "teleport_trap_api_650", "teleport_trap_api_651", "teleport_trap_api_652", "teleport_trap_api_653", "teleport_trap_api_654", "teleport_trap_api_655", "teleport_trap_api_656", "teleport_trap_api_657", "teleport_trap_api_658", "teleport_trap_api_659", "teleport_trap_api_660", "teleport_trap_api_661", "teleport_trap_api_662", "teleport_trap_api_663", "teleport_trap_api_664", "teleport_trap_api_665", "teleport_trap_api_666", "teleport_trap_api_667", "teleport_trap_api_668", "teleport_trap_api_669", "teleport_trap_api_670", "teleport_trap_api_671", "teleport_trap_api_672", "teleport_trap_api_673", "teleport_trap_api_674", "teleport_trap_api_675", "teleport_trap_api_676", "teleport_trap_api_677", "teleport_trap_api_678", "teleport_trap_api_679", "teleport_trap_api_680", "teleport_trap_api_681", "teleport_trap_api_682", "teleport_trap_api_683", "teleport_trap_api_684", "teleport_trap_api_685", "teleport_trap_api_686", "teleport_trap_api_687", "teleport_trap_api_688", "teleport_trap_api_689", "teleport_trap_api_690", "teleport_trap_api_691", "teleport_trap_api_692", "teleport_trap_api_693", "teleport_trap_api_694", "teleport_trap_api_695", "teleport_trap_api_696", "teleport_trap_api_697", "teleport_trap_api_698", "teleport_trap_api_699", "teleport_trap_api_700", "teleport_trap_api_701", "teleport_trap_api_702", "teleport_trap_api_703", "teleport_trap_api_704", "teleport_trap_api_705", "teleport_trap_api_706", "teleport_trap_api_707", "teleport_trap_api_708", "teleport_trap_api_709", "teleport_trap_api_710", "teleport_trap_api_711", "teleport_trap_api_712", "teleport_trap_api_713", "teleport_trap_api_714", "teleport_trap_api_715", "teleport_trap_api_716", "teleport_trap_api_717", "teleport_trap_api_718", "teleport_trap_api_719", "teleport_trap_api_720", "teleport_trap_api_721", "teleport_trap_api_722", "teleport_trap_api_723", "teleport_trap_api_724", "teleport_trap_api_725", "teleport_trap_api_726", "teleport_trap_api_727", "teleport_trap_api_728", "teleport_trap_api_729", "teleport_trap_api_730", "teleport_trap_api_731", "teleport_trap_api_732", "teleport_trap_api_733", "teleport_trap_api_734", "teleport_trap_api_735", "teleport_trap_api_736", "teleport_trap_api_737", "teleport_trap_api_738", "teleport_trap_api_739", "teleport_trap_api_740", "teleport_trap_api_741", "teleport_trap_api_742", "teleport_trap_api_743", "teleport_trap_api_744", "teleport_trap_api_745", "teleport_trap_api_746", "teleport_trap_api_747", "teleport_trap_api_748", "teleport_trap_api_749", "teleport_trap_api_750", "teleport_trap_api_751", "teleport_trap_api_752", "teleport_trap_api_753", "teleport_trap_api_754", "teleport_trap_api_755", "teleport_trap_api_756", "teleport_trap_api_757", "teleport_trap_api_758", "teleport_trap_api_759", "teleport_trap_api_760", "teleport_trap_api_761", "teleport_trap_api_762", "teleport_trap_api_763", "teleport_trap_api_764", "teleport_trap_api_765", "teleport_trap_api_766", "teleport_trap_api_767", "teleport_trap_api_768", "teleport_trap_api_769", "teleport_trap_api_770", "teleport_trap_api_771", "teleport_trap_api_772", "teleport_trap_api_773", "teleport_trap_api_774", "teleport_trap_api_775", "teleport_trap_api_776", "teleport_trap_api_777", "teleport_trap_api_778", "teleport_trap_api_779", "teleport_trap_api_780", "teleport_trap_api_781", "teleport_trap_api_782", "teleport_trap_api_783", "teleport_trap_api_784", "teleport_trap_api_785", "teleport_trap_api_786", "teleport_trap_api_787", "teleport_trap_api_788", "teleport_trap_api_789", "teleport_trap_api_790", "teleport_trap_api_791", "teleport_trap_api_792", "teleport_trap_api_793", "teleport_trap_api_794", "teleport_trap_api_795", "teleport_trap_api_796", "teleport_trap_api_797", "teleport_trap_api_798", "teleport_trap_api_799", "teleport_trap_api_800", "teleport_trap_api_801", "teleport_trap_api_802", "teleport_trap_api_803", "teleport_trap_api_804", "teleport_trap_api_805", "teleport_trap_api_806", "teleport_trap_api_807", "teleport_trap_api_808", "teleport_trap_api_809", "teleport_trap_api_810", "teleport_trap_api_811", "teleport_trap_api_812", "teleport_trap_api_813", "teleport_trap_api_814", "teleport_trap_api_815", "teleport_trap_api_816", "teleport_trap_api_817", "teleport_trap_api_818", "teleport_trap_api_819", "teleport_trap_api_820", "teleport_trap_api_821", "teleport_trap_api_822", "teleport_trap_api_823", "teleport_trap_api_824", "teleport_trap_api_825", "teleport_trap_api_826", "teleport_trap_api_827", "teleport_trap_api_828", "teleport_trap_api_829", "teleport_trap_api_830", "teleport_trap_api_831", "teleport_trap_api_832", "teleport_trap_api_833", "teleport_trap_api_834", "teleport_trap_api_835", "teleport_trap_api_836", "teleport_trap_api_837", "teleport_trap_api_838", "teleport_trap_api_839", "teleport_trap_api_840", "teleport_trap_api_841", "teleport_trap_api_842", "teleport_trap_api_843", "teleport_trap_api_844", "teleport_trap_api_845", "teleport_trap_api_846", "teleport_trap_api_847", "teleport_trap_api_848", "teleport_trap_api_849", "teleport_trap_api_850", "teleport_trap_api_851", "teleport_trap_api_852", "teleport_trap_api_853", "teleport_trap_api_854", "teleport_trap_api_855", "teleport_trap_api_856", "teleport_trap_api_857", "teleport_trap_api_858", "teleport_trap_api_859", "teleport_trap_api_860", "teleport_trap_api_861", "teleport_trap_api_862", "teleport_trap_api_863", "teleport_trap_api_864", "teleport_trap_api_865", "teleport_trap_api_866", "teleport_trap_api_867", "teleport_trap_api_868", "teleport_trap_api_869", "teleport_trap_api_870", "teleport_trap_api_871", "teleport_trap_api_872", "teleport_trap_api_873", "teleport_trap_api_874", "teleport_trap_api_875", "teleport_trap_api_876", "teleport_trap_api_877", "teleport_trap_api_878", "teleport_trap_api_879", "teleport_trap_api_880", "teleport_trap_api_881", "teleport_trap_api_882", "teleport_trap_api_883", "teleport_trap_api_884", "teleport_trap_api_885", "teleport_trap_api_886", "teleport_trap_api_887", "teleport_trap_api_888", "teleport_trap_api_889", "teleport_trap_api_890", "teleport_trap_api_891", "teleport_trap_api_892", "teleport_trap_api_893", "teleport_trap_api_894", "teleport_trap_api_895", "teleport_trap_api_896", "teleport_trap_api_897", "teleport_trap_api_898", "teleport_trap_api_899", "teleport_trap_api_900", "teleport_trap_api_901", "teleport_trap_api_902", "teleport_trap_api_903", "teleport_trap_api_904", "teleport_trap_api_905", "teleport_trap_api_906", "teleport_trap_api_907", "teleport_trap_api_908", "teleport_trap_api_909", "teleport_trap_api_910", "teleport_trap_api_911", "teleport_trap_api_912", "teleport_trap_api_913", "teleport_trap_api_914", "teleport_trap_api_915", "teleport_trap_api_916", "teleport_trap_api_917", "teleport_trap_api_918", "teleport_trap_api_919", "teleport_trap_api_920", "teleport_trap_api_921", "teleport_trap_api_922", "teleport_trap_api_923", "teleport_trap_api_924", "teleport_trap_api_925", "teleport_trap_api_926", "teleport_trap_api_927", "teleport_trap_api_928", "teleport_trap_api_929", "teleport_trap_api_930", "teleport_trap_api_931", "teleport_trap_api_932", "teleport_trap_api_933", "teleport_trap_api_934", "teleport_trap_api_935", "teleport_trap_api_936", "teleport_trap_api_937", "teleport_trap_api_938", "teleport_trap_api_939", "teleport_trap_api_940", "teleport_trap_api_941", "teleport_trap_api_942", "teleport_trap_api_943", "teleport_trap_api_944", "teleport_trap_api_945", "teleport_trap_api_946", "teleport_trap_api_947", "teleport_trap_api_948", "teleport_trap_api_949", "teleport_trap_api_950", "teleport_trap_api_951", "teleport_trap_api_952", "teleport_trap_api_953", "teleport_trap_api_954", "teleport_trap_api_955", "teleport_trap_api_956", "teleport_trap_api_957", "teleport_trap_api_958", "teleport_trap_api_959", "teleport_trap_api_960", "teleport_trap_api_961", "teleport_trap_api_962", "teleport_trap_api_963", "teleport_trap_api_964", "teleport_trap_api_965", "teleport_trap_api_966", "teleport_trap_api_967", "teleport_trap_api_968", "teleport_trap_api_969", "teleport_trap_api_970", "teleport_trap_api_971", "teleport_trap_api_972", "teleport_trap_api_973", "teleport_trap_api_974", "teleport_trap_api_975", "teleport_trap_api_976", "teleport_trap_api_977", "teleport_trap_api_978", "teleport_trap_api_979", "teleport_trap_api_980", "teleport_trap_api_981", "teleport_trap_api_982", "teleport_trap_api_983", "teleport_trap_api_984", "teleport_trap_api_985", "teleport_trap_api_986", "teleport_trap_api_987", "teleport_trap_api_988", "teleport_trap_api_989", "teleport_trap_api_990", "teleport_trap_api_991", "teleport_trap_api_992", "teleport_trap_api_993", "teleport_trap_api_994", "teleport_trap_api_995", "teleport_trap_api_996", "teleport_trap_api_997", "teleport_trap_api_998", "teleport_trap_api_999", "teleport_trap_api_1000", "teleport_trap_api_1001", "teleport_trap_api_1002", "teleport_trap_api_1003", "teleport_trap_api_1004", "teleport_trap_api_1005", "teleport_trap_api_1006", "teleport_trap_api_1007", "teleport_trap_api_1008", "teleport_trap_api_1009", "teleport_trap_api_1010", "teleport_trap_api_1011", "teleport_trap_api_1012", "teleport_trap_api_1013", "teleport_trap_api_1014", "teleport_trap_api_1015", "teleport_trap_api_1016", "teleport_trap_api_1017", "teleport_trap_api_1018", "teleport_trap_api_1019", "teleport_trap_api_1020", "teleport_trap_api_1021", "teleport_trap_api_1022", "teleport_trap_api_1023", "teleport_trap_api_1024", "teleport_trap_api_1025", "teleport_trap_api_1026", "teleport_trap_api_1027", "teleport_trap_api_1028", "teleport_trap_api_1029", "teleport_trap_api_1030", "teleport_trap_api_1031", "teleport_trap_api_1032", "teleport_trap_api_1033", "teleport_trap_api_1034", "teleport_trap_api_1035", "teleport_trap_api_1036", "teleport_trap_api_1037", "teleport_trap_api_1038", "teleport_trap_api_1039", "teleport_trap_api_1040", "teleport_trap_api_1041", "teleport_trap_api_1042", "teleport_trap_api_1043", "teleport_trap_api_1044", "teleport_trap_api_1045", "teleport_trap_api_1046", "teleport_trap_api_1047", "teleport_trap_api_1048", "teleport_trap_api_1049", "teleport_trap_api_1050", "teleport_trap_api_1051", "teleport_trap_api_1052", "teleport_trap_api_1053", "teleport_trap_api_1054", "teleport_trap_api_1055", "teleport_trap_api_1056", "teleport_trap_api_1057", "teleport_trap_api_1058", "teleport_trap_api_1059", "teleport_trap_api_1060", "teleport_trap_api_1061", "teleport_trap_api_1062", "teleport_trap_api_1063", "teleport_trap_api_1064", "teleport_trap_api_1065", "teleport_trap_api_1066", "teleport_trap_api_1067", "teleport_trap_api_1068", "teleport_trap_api_1069", "teleport_trap_api_1070", "teleport_trap_api_1071", "teleport_trap_api_1072", "teleport_trap_api_1073", "teleport_trap_api_1074", "teleport_trap_api_1075", "teleport_trap_api_1076", "teleport_trap_api_1077", "teleport_trap_api_1078", "teleport_trap_api_1079", "teleport_trap_api_1080", "teleport_trap_api_1081", "teleport_trap_api_1082", "teleport_trap_api_1083", "teleport_trap_api_1084", "teleport_trap_api_1085", "teleport_trap_api_1086", "teleport_trap_api_1087", "teleport_trap_api_1088", "teleport_trap_api_1089", "teleport_trap_api_1090", "teleport_trap_api_1091", "teleport_trap_api_1092", "teleport_trap_api_1093", "teleport_trap_api_1094", "teleport_trap_api_1095", "teleport_trap_api_1096", "teleport_trap_api_1097", "teleport_trap_api_1098", "teleport_trap_api_1099", "teleport_trap_api_1100", "teleport_trap_api_1101", "teleport_trap_api_1102", "teleport_trap_api_1103", "teleport_trap_api_1104", "teleport_trap_api_1105", "teleport_trap_api_1106", "teleport_trap_api_1107", "teleport_trap_api_1108", "teleport_trap_api_1109", "teleport_trap_api_1110", "teleport_trap_api_1111", "teleport_trap_api_1112", "teleport_trap_api_1113", "teleport_trap_api_1114", "teleport_trap_api_1115", "teleport_trap_api_1116", "teleport_trap_api_1117", "teleport_trap_api_1118", "teleport_trap_api_1119", "teleport_trap_api_1120", "teleport_trap_api_1121", "teleport_trap_api_1122", "teleport_trap_api_1123", "teleport_trap_api_1124", "teleport_trap_api_1125", "teleport_trap_api_1126", "teleport_trap_api_1127", "teleport_trap_api_1128", "teleport_trap_api_1129", "teleport_trap_api_1130", "teleport_trap_api_1131", "teleport_trap_api_1132", "teleport_trap_api_1133", "teleport_trap_api_1134", "teleport_trap_api_1135", "teleport_trap_api_1136", "teleport_trap_api_1137", "teleport_trap_api_1138", "teleport_trap_api_1139", "teleport_trap_api_1140", "teleport_trap_api_1141", "teleport_trap_api_1142", "teleport_trap_api_1143", "teleport_trap_api_1144", "teleport_trap_api_1145", "teleport_trap_api_1146", "teleport_trap_api_1147", "teleport_trap_api_1148", "teleport_trap_api_1149", "teleport_trap_api_1150", "teleport_trap_api_1151", "teleport_trap_api_1152", "teleport_trap_api_1153", "teleport_trap_api_1154", "teleport_trap_api_1155", "teleport_trap_api_1156", "teleport_trap_api_1157", "teleport_trap_api_1158", "teleport_trap_api_1159", "teleport_trap_api_1160", "teleport_trap_api_1161", "teleport_trap_api_1162", "teleport_trap_api_1163", "teleport_trap_api_1164", "teleport_trap_api_1165", "teleport_trap_api_1166", "teleport_trap_api_1167", "teleport_trap_api_1168", "teleport_trap_api_1169", "teleport_trap_api_1170", "teleport_trap_api_1171", "teleport_trap_api_1172", "teleport_trap_api_1173", "teleport_trap_api_1174", "teleport_trap_api_1175", "teleport_trap_api_1176", "teleport_trap_api_1177", "teleport_trap_api_1178", "teleport_trap_api_1179", "teleport_trap_api_1180", "teleport_trap_api_1181", "teleport_trap_api_1182", "teleport_trap_api_1183", "teleport_trap_api_1184", "teleport_trap_api_1185", "teleport_trap_api_1186", "teleport_trap_api_1187", "teleport_trap_api_1188", "teleport_trap_api_1189", "teleport_trap_api_1190", "teleport_trap_api_1191", "teleport_trap_api_1192", "teleport_trap_api_1193", "teleport_trap_api_1194", "teleport_trap_api_1195", "teleport_trap_api_1196", "teleport_trap_api_1197", "teleport_trap_api_1198", "teleport_trap_api_1199", "teleport_trap_api_1200", "teleport_trap_api_1201", "teleport_trap_api_1202", "teleport_trap_api_1203", "teleport_trap_api_1204", "teleport_trap_api_1205", "teleport_trap_api_1206", "teleport_trap_api_1207", "teleport_trap_api_1208", "teleport_trap_api_1209", "teleport_trap_api_1210", "teleport_trap_api_1211", "teleport_trap_api_1212", "teleport_trap_api_1213", "teleport_trap_api_1214", "teleport_trap_api_1215", "teleport_trap_api_1216", "teleport_trap_api_1217", "teleport_trap_api_1218", "teleport_trap_api_1219", "teleport_trap_api_1220", "teleport_trap_api_1221", "teleport_trap_api_1222", "teleport_trap_api_1223", "teleport_trap_api_1224", "teleport_trap_api_1225", "teleport_trap_api_1226", "teleport_trap_api_1227", "teleport_trap_api_1228", "teleport_trap_api_1229", "teleport_trap_api_1230", "teleport_trap_api_1231", "teleport_trap_api_1232", "teleport_trap_api_1233", "teleport_trap_api_1234", "teleport_trap_api_1235", "teleport_trap_api_1236", "teleport_trap_api_1237", "teleport_trap_api_1238", "teleport_trap_api_1239", "teleport_trap_api_1240", "teleport_trap_api_1241", "teleport_trap_api_1242", "teleport_trap_api_1243", "teleport_trap_api_1244", "teleport_trap_api_1245", "teleport_trap_api_1246", "teleport_trap_api_1247", "teleport_trap_api_1248", "teleport_trap_api_1249", "teleport_trap_api_1250", "teleport_trap_api_1251", "teleport_trap_api_1252", "teleport_trap_api_1253", "teleport_trap_api_1254", "teleport_trap_api_1255", "teleport_trap_api_1256", "teleport_trap_api_1257", "teleport_trap_api_1258", "teleport_trap_api_1259", "teleport_trap_api_1260", "teleport_trap_api_1261", "teleport_trap_api_1262", "teleport_trap_api_1263", "teleport_trap_api_1264", "teleport_trap_api_1265", "teleport_trap_api_1266", "teleport_trap_api_1267", "teleport_trap_api_1268", "teleport_trap_api_1269", "teleport_trap_api_1270", "teleport_trap_api_1271", "teleport_trap_api_1272", "teleport_trap_api_1273", "teleport_trap_api_1274", "teleport_trap_api_1275", "teleport_trap_api_1276", "teleport_trap_api_1277", "teleport_trap_api_1278", "teleport_trap_api_1279", "teleport_trap_api_1280", "teleport_trap_api_1281", "teleport_trap_api_1282", "teleport_trap_api_1283", "teleport_trap_api_1284", "teleport_trap_api_1285", "teleport_trap_api_1286", "teleport_trap_api_1287", "teleport_trap_api_1288", "teleport_trap_api_1289", "teleport_trap_api_1290", "teleport_trap_api_1291", "teleport_trap_api_1292", "teleport_trap_api_1293", "teleport_trap_api_1294", "teleport_trap_api_1295", "teleport_trap_api_1296", "teleport_trap_api_1297", "teleport_trap_api_1298", "teleport_trap_api_1299", "teleport_trap_api_1300", "teleport_trap_api_1301", "teleport_trap_api_1302", "teleport_trap_api_1303", "teleport_trap_api_1304", "teleport_trap_api_1305", "teleport_trap_api_1306", "teleport_trap_api_1307", "teleport_trap_api_1308", "teleport_trap_api_1309", "teleport_trap_api_1310", "teleport_trap_api_1311", "teleport_trap_api_1312", "teleport_trap_api_1313", "teleport_trap_api_1314", "teleport_trap_api_1315", "teleport_trap_api_1316", "teleport_trap_api_1317", "teleport_trap_api_1318", "teleport_trap_api_1319", "teleport_trap_api_1320", "teleport_trap_api_1321", "teleport_trap_api_1322", "teleport_trap_api_1323", "teleport_trap_api_1324", "teleport_trap_api_1325", "teleport_trap_api_1326", "teleport_trap_api_1327", "teleport_trap_api_1328", "teleport_trap_api_1329", "teleport_trap_api_1330", "teleport_trap_api_1331", "teleport_trap_api_1332", "teleport_trap_api_1333", "teleport_trap_api_1334", "teleport_trap_api_1335", "teleport_trap_api_1336", "teleport_trap_api_1337", "teleport_trap_api_1338", "teleport_trap_api_1339", "teleport_trap_api_1340", "teleport_trap_api_1341", "teleport_trap_api_1342", "teleport_trap_api_1343", "teleport_trap_api_1344", "teleport_trap_api_1345", "teleport_trap_api_1346", "teleport_trap_api_1347", "teleport_trap_api_1348", "teleport_trap_api_1349", "teleport_trap_api_1350", "teleport_trap_api_1351", "teleport_trap_api_1352", "teleport_trap_api_1353", "teleport_trap_api_1354", "teleport_trap_api_1355", "teleport_trap_api_1356", "teleport_trap_api_1357", "teleport_trap_api_1358", "teleport_trap_api_1359", "teleport_trap_api_1360", "teleport_trap_api_1361", "teleport_trap_api_1362", "teleport_trap_api_1363", "teleport_trap_api_1364", "teleport_trap_api_1365", "teleport_trap_api_1366", "teleport_trap_api_1367", "teleport_trap_api_1368", "teleport_trap_api_1369", "teleport_trap_api_1370", "teleport_trap_api_1371", "teleport_trap_api_1372", "teleport_trap_api_1373", "teleport_trap_api_1374", "teleport_trap_api_1375", "teleport_trap_api_1376", "teleport_trap_api_1377", "teleport_trap_api_1378", "teleport_trap_api_1379", "teleport_trap_api_1380", "teleport_trap_api_1381", "teleport_trap_api_1382", "teleport_trap_api_1383", "teleport_trap_api_1384", "teleport_trap_api_1385", "teleport_trap_api_1386", "teleport_trap_api_1387", "teleport_trap_api_1388", "teleport_trap_api_1389", "teleport_trap_api_1390", "teleport_trap_api_1391", "teleport_trap_api_1392", "teleport_trap_api_1393", "teleport_trap_api_1394", "teleport_trap_api_1395", "teleport_trap_api_1396", "teleport_trap_api_1397", "teleport_trap_api_1398", "teleport_trap_api_1399", "teleport_trap_api_1400", "teleport_trap_api_1401", "teleport_trap_api_1402", "teleport_trap_api_1403", "teleport_trap_api_1404", "teleport_trap_api_1405", "teleport_trap_api_1406", "teleport_trap_api_1407", "teleport_trap_api_1408", "teleport_trap_api_1409", "teleport_trap_api_1410", "teleport_trap_api_1411", "teleport_trap_api_1412", "teleport_trap_api_1413", "teleport_trap_api_1414", "teleport_trap_api_1415", "teleport_trap_api_1416", "teleport_trap_api_1417", "teleport_trap_api_1418", "teleport_trap_api_1419", "teleport_trap_api_1420", "teleport_trap_api_1421", "teleport_trap_api_1422", "teleport_trap_api_1423", "teleport_trap_api_1424", "teleport_trap_api_1425", "teleport_trap_api_1426", "teleport_trap_api_1427", "teleport_trap_api_1428", "teleport_trap_api_1429", "teleport_trap_api_1430", "teleport_trap_api_1431", "teleport_trap_api_1432", "teleport_trap_api_1433", "teleport_trap_api_1434", "teleport_trap_api_1435", "teleport_trap_api_1436", "teleport_trap_api_1437", "teleport_trap_api_1438", "teleport_trap_api_1439", "teleport_trap_api_1440", "teleport_trap_api_1441", "teleport_trap_api_1442", "teleport_trap_api_1443", "teleport_trap_api_1444", "teleport_trap_api_1445", "teleport_trap_api_1446", "teleport_trap_api_1447", "teleport_trap_api_1448", "teleport_trap_api_1449", "teleport_trap_api_1450", "teleport_trap_api_1451", "teleport_trap_api_1452", "teleport_trap_api_1453", "teleport_trap_api_1454", "teleport_trap_api_1455", "teleport_trap_api_1456", "teleport_trap_api_1457", "teleport_trap_api_1458", "teleport_trap_api_1459", "teleport_trap_api_1460", "teleport_trap_api_1461", "teleport_trap_api_1462", "teleport_trap_api_1463", "teleport_trap_api_1464", "teleport_trap_api_1465", "teleport_trap_api_1466", "teleport_trap_api_1467", "teleport_trap_api_1468", "teleport_trap_api_1469", "teleport_trap_api_1470", "teleport_trap_api_1471", "teleport_trap_api_1472", "teleport_trap_api_1473", "teleport_trap_api_1474", "teleport_trap_api_1475", "teleport_trap_api_1476", "teleport_trap_api_1477", "teleport_trap_api_1478", "teleport_trap_api_1479", "teleport_trap_api_1480", "teleport_trap_api_1481", "teleport_trap_api_1482", "teleport_trap_api_1483", "teleport_trap_api_1484", "teleport_trap_api_1485", "teleport_trap_api_1486", "teleport_trap_api_1487", "teleport_trap_api_1488", "teleport_trap_api_1489", "teleport_trap_api_1490", "teleport_trap_api_1491", "teleport_trap_api_1492", "teleport_trap_api_1493", "teleport_trap_api_1494", "teleport_trap_api_1495", "teleport_trap_api_1496", "teleport_trap_api_1497", "teleport_trap_api_1498", "teleport_trap_api_1499", "teleport_trap_api_1500", "teleport_trap_api_1501", "teleport_trap_api_1502", "teleport_trap_api_1503", "teleport_trap_api_1504", "teleport_trap_api_1505", "teleport_trap_api_1506", "teleport_trap_api_1507", "teleport_trap_api_1508", "teleport_trap_api_1509", "teleport_trap_api_1510", "teleport_trap_api_1511", "teleport_trap_api_1512", "teleport_trap_api_1513", "teleport_trap_api_1514", "teleport_trap_api_1515", "teleport_trap_api_1516", "teleport_trap_api_1517", "teleport_trap_api_1518", "teleport_trap_api_1519", "teleport_trap_api_1520", "teleport_trap_api_1521", "teleport_trap_api_1522", "teleport_trap_api_1523", "teleport_trap_api_1524", "teleport_trap_api_1525", "teleport_trap_api_1526", "teleport_trap_api_1527", "teleport_trap_api_1528", "teleport_trap_api_1529", "teleport_trap_api_1530", "teleport_trap_api_1531", "teleport_trap_api_1532", "teleport_trap_api_1533", "teleport_trap_api_1534", "teleport_trap_api_1535", "teleport_trap_api_1536", "teleport_trap_api_1537", "teleport_trap_api_1538", "teleport_trap_api_1539", "teleport_trap_api_1540", "teleport_trap_api_1541", "teleport_trap_api_1542", "teleport_trap_api_1543", "teleport_trap_api_1544", "teleport_trap_api_1545", "teleport_trap_api_1546", "teleport_trap_api_1547", "teleport_trap_api_1548", "teleport_trap_api_1549", "teleport_trap_api_1550", "teleport_trap_api_1551", "teleport_trap_api_1552", "teleport_trap_api_1553", "teleport_trap_api_1554", "teleport_trap_api_1555", "teleport_trap_api_1556", "teleport_trap_api_1557", "teleport_trap_api_1558", "teleport_trap_api_1559", "teleport_trap_api_1560", "teleport_trap_api_1561", "teleport_trap_api_1562", "teleport_trap_api_1563", "teleport_trap_api_1564", "teleport_trap_api_1565", "teleport_trap_api_1566", "teleport_trap_api_1567", "teleport_trap_api_1568", "teleport_trap_api_1569", "teleport_trap_api_1570", "teleport_trap_api_1571", "teleport_trap_api_1572", "teleport_trap_api_1573", "teleport_trap_api_1574", "teleport_trap_api_1575", "teleport_trap_api_1576", "teleport_trap_api_1577", "teleport_trap_api_1578", "teleport_trap_api_1579", "teleport_trap_api_1580", "teleport_trap_api_1581", "teleport_trap_api_1582", "teleport_trap_api_1583", "teleport_trap_api_1584", "teleport_trap_api_1585", "teleport_trap_api_1586", "teleport_trap_api_1587", "teleport_trap_api_1588", "teleport_trap_api_1589", "teleport_trap_api_1590", "teleport_trap_api_1591", "teleport_trap_api_1592", "teleport_trap_api_1593", "teleport_trap_api_1594", "teleport_trap_api_1595", "teleport_trap_api_1596", "teleport_trap_api_1597", "teleport_trap_api_1598", "teleport_trap_api_1599", "teleport_trap_api_1600", "teleport_trap_api_1601", "teleport_trap_api_1602", "teleport_trap_api_1603", "teleport_trap_api_1604", "teleport_trap_api_1605", "teleport_trap_api_1606", "teleport_trap_api_1607", "teleport_trap_api_1608", "teleport_trap_api_1609", "teleport_trap_api_1610", "teleport_trap_api_1611", "teleport_trap_api_1612", "teleport_trap_api_1613", "teleport_trap_api_1614", "teleport_trap_api_1615", "teleport_trap_api_1616", "teleport_trap_api_1617", "teleport_trap_api_1618", "teleport_trap_api_1619", "teleport_trap_api_1620", "teleport_trap_api_1621", "teleport_trap_api_1622", "teleport_trap_api_1623", "teleport_trap_api_1624", "teleport_trap_api_1625", "teleport_trap_api_1626", "teleport_trap_api_1627", "teleport_trap_api_1628", "teleport_trap_api_1629", "teleport_trap_api_1630", "teleport_trap_api_1631", "teleport_trap_api_1632", "teleport_trap_api_1633", "teleport_trap_api_1634", "teleport_trap_api_1635", "teleport_trap_api_1636", "teleport_trap_api_1637", "teleport_trap_api_1638", "teleport_trap_api_1639", "teleport_trap_api_1640", "teleport_trap_api_1641", "teleport_trap_api_1642", "teleport_trap_api_1643", "teleport_trap_api_1644", "teleport_trap_api_1645", "teleport_trap_api_1646", "teleport_trap_api_1647", "teleport_trap_api_1648", "teleport_trap_api_1649", "teleport_trap_api_1650", "teleport_trap_api_1651", "teleport_trap_api_1652", "teleport_trap_api_1653", "teleport_trap_api_1654", "teleport_trap_api_1655", "teleport_trap_api_1656", "teleport_trap_api_1657", "teleport_trap_api_1658", "teleport_trap_api_1659", "teleport_trap_api_1660", "teleport_trap_api_1661", "teleport_trap_api_1662", "teleport_trap_api_1663", "teleport_trap_api_1664", "teleport_trap_api_1665", "teleport_trap_api_1666", "teleport_trap_api_1667", "teleport_trap_api_1668", "teleport_trap_api_1669", "teleport_trap_api_1670", "teleport_trap_api_1671", "teleport_trap_api_1672", "teleport_trap_api_1673", "teleport_trap_api_1674", "teleport_trap_api_1675", "teleport_trap_api_1676", "teleport_trap_api_1677", "teleport_trap_api_1678", "teleport_trap_api_1679", "teleport_trap_api_1680", "teleport_trap_api_1681", "teleport_trap_api_1682", "teleport_trap_api_1683", "teleport_trap_api_1684", "teleport_trap_api_1685", "teleport_trap_api_1686", "teleport_trap_api_1687", "teleport_trap_api_1688", "teleport_trap_api_1689", "teleport_trap_api_1690", "teleport_trap_api_1691", "teleport_trap_api_1692", "teleport_trap_api_1693", "teleport_trap_api_1694", "teleport_trap_api_1695", "teleport_trap_api_1696", "teleport_trap_api_1697", "teleport_trap_api_1698", "teleport_trap_api_1699", "teleport_trap_api_1700", "teleport_trap_api_1701", "teleport_trap_api_1702", "teleport_trap_api_1703", "teleport_trap_api_1704", "teleport_trap_api_1705", "teleport_trap_api_1706", "teleport_trap_api_1707", "teleport_trap_api_1708", "teleport_trap_api_1709", "teleport_trap_api_1710", "teleport_trap_api_1711", "teleport_trap_api_1712", "teleport_trap_api_1713", "teleport_trap_api_1714", "teleport_trap_api_1715", "teleport_trap_api_1716", "teleport_trap_api_1717", "teleport_trap_api_1718", "teleport_trap_api_1719", "teleport_trap_api_1720", "teleport_trap_api_1721", "teleport_trap_api_1722", "teleport_trap_api_1723", "teleport_trap_api_1724", "teleport_trap_api_1725", "teleport_trap_api_1726", "teleport_trap_api_1727", "teleport_trap_api_1728", "teleport_trap_api_1729", "teleport_trap_api_1730", "teleport_trap_api_1731", "teleport_trap_api_1732", "teleport_trap_api_1733", "teleport_trap_api_1734", "teleport_trap_api_1735", "teleport_trap_api_1736", "teleport_trap_api_1737", "teleport_trap_api_1738", "teleport_trap_api_1739", "teleport_trap_api_1740", "teleport_trap_api_1741", "teleport_trap_api_1742", "teleport_trap_api_1743", "teleport_trap_api_1744", "teleport_trap_api_1745", "teleport_trap_api_1746", "teleport_trap_api_1747", "teleport_trap_api_1748", "teleport_trap_api_1749", "teleport_trap_api_1750", "teleport_trap_api_1751", "teleport_trap_api_1752", "teleport_trap_api_1753", "teleport_trap_api_1754", "teleport_trap_api_1755", "teleport_trap_api_1756", "teleport_trap_api_1757", "teleport_trap_api_1758", "teleport_trap_api_1759", "teleport_trap_api_1760", "teleport_trap_api_1761", "teleport_trap_api_1762", "teleport_trap_api_1763", "teleport_trap_api_1764", "teleport_trap_api_1765", "teleport_trap_api_1766", "teleport_trap_api_1767", "teleport_trap_api_1768", "teleport_trap_api_1769", "teleport_trap_api_1770", "teleport_trap_api_1771", "teleport_trap_api_1772", "teleport_trap_api_1773", "teleport_trap_api_1774", "teleport_trap_api_1775", "teleport_trap_api_1776", "teleport_trap_api_1777", "teleport_trap_api_1778", "teleport_trap_api_1779", "teleport_trap_api_1780", "teleport_trap_api_1781", "teleport_trap_api_1782", "teleport_trap_api_1783", "teleport_trap_api_1784", "teleport_trap_api_1785", "teleport_trap_api_1786", "teleport_trap_api_1787", "teleport_trap_api_1788", "teleport_trap_api_1789", "teleport_trap_api_1790", "teleport_trap_api_1791", "teleport_trap_api_1792", "teleport_trap_api_1793", "teleport_trap_api_1794", "teleport_trap_api_1795", "teleport_trap_api_1796", "teleport_trap_api_1797", "teleport_trap_api_1798", "teleport_trap_api_1799", "teleport_trap_api_1800", "teleport_trap_api_1801", "teleport_trap_api_1802", "teleport_trap_api_1803", "teleport_trap_api_1804", "teleport_trap_api_1805", "teleport_trap_api_1806", "teleport_trap_api_1807", "teleport_trap_api_1808", "teleport_trap_api_1809", "teleport_trap_api_1810", "teleport_trap_api_1811", "teleport_trap_api_1812", "teleport_trap_api_1813", "teleport_trap_api_1814", "teleport_trap_api_1815", "teleport_trap_api_1816", "teleport_trap_api_1817", "teleport_trap_api_1818", "teleport_trap_api_1819", "teleport_trap_api_1820", "teleport_trap_api_1821", "teleport_trap_api_1822", "teleport_trap_api_1823", "teleport_trap_api_1824", "teleport_trap_api_1825", "teleport_trap_api_1826", "teleport_trap_api_1827", "teleport_trap_api_1828", "teleport_trap_api_1829", "teleport_trap_api_1830", "teleport_trap_api_1831", "teleport_trap_api_1832", "teleport_trap_api_1833", "teleport_trap_api_1834", "teleport_trap_api_1835", "teleport_trap_api_1836", "teleport_trap_api_1837", "teleport_trap_api_1838", "teleport_trap_api_1839", "teleport_trap_api_1840", "teleport_trap_api_1841", "teleport_trap_api_1842", "teleport_trap_api_1843", "teleport_trap_api_1844", "teleport_trap_api_1845", "teleport_trap_api_1846", "teleport_trap_api_1847", "teleport_trap_api_1848", "teleport_trap_api_1849", "teleport_trap_api_1850", "teleport_trap_api_1851", "teleport_trap_api_1852", "teleport_trap_api_1853", "teleport_trap_api_1854", "teleport_trap_api_1855", "teleport_trap_api_1856", "teleport_trap_api_1857", "teleport_trap_api_1858", "teleport_trap_api_1859", "teleport_trap_api_1860", "teleport_trap_api_1861", "teleport_trap_api_1862", "teleport_trap_api_1863", "teleport_trap_api_1864", "teleport_trap_api_1865", "teleport_trap_api_1866", "teleport_trap_api_1867", "teleport_trap_api_1868", "teleport_trap_api_1869", "teleport_trap_api_1870", "teleport_trap_api_1871", "teleport_trap_api_1872", "teleport_trap_api_1873", "teleport_trap_api_1874", "teleport_trap_api_1875", "teleport_trap_api_1876", "teleport_trap_api_1877", "teleport_trap_api_1878", "teleport_trap_api_1879", "teleport_trap_api_1880", "teleport_trap_api_1881", "teleport_trap_api_1882", "teleport_trap_api_1883", "teleport_trap_api_1884", "teleport_trap_api_1885", "teleport_trap_api_1886", "teleport_trap_api_1887", "teleport_trap_api_1888", "teleport_trap_api_1889", "teleport_trap_api_1890", "teleport_trap_api_1891", "teleport_trap_api_1892", "teleport_trap_api_1893", "teleport_trap_api_1894", "teleport_trap_api_1895", "teleport_trap_api_1896", "teleport_trap_api_1897", "teleport_trap_api_1898", "teleport_trap_api_1899", "teleport_trap_api_1900", "teleport_trap_api_1901", "teleport_trap_api_1902", "teleport_trap_api_1903", "teleport_trap_api_1904", "teleport_trap_api_1905", "teleport_trap_api_1906", "teleport_trap_api_1907", "teleport_trap_api_1908", "teleport_trap_api_1909", "teleport_trap_api_1910", "teleport_trap_api_1911", "teleport_trap_api_1912", "teleport_trap_api_1913", "teleport_trap_api_1914", "teleport_trap_api_1915", "teleport_trap_api_1916", "teleport_trap_api_1917", "teleport_trap_api_1918", "teleport_trap_api_1919", "teleport_trap_api_1920", "teleport_trap_api_1921", "teleport_trap_api_1922", "teleport_trap_api_1923", "teleport_trap_api_1924", "teleport_trap_api_1925", "teleport_trap_api_1926", "teleport_trap_api_1927", "teleport_trap_api_1928", "teleport_trap_api_1929", "teleport_trap_api_1930", "teleport_trap_api_1931", "teleport_trap_api_1932", "teleport_trap_api_1933", "teleport_trap_api_1934", "teleport_trap_api_1935", "teleport_trap_api_1936", "teleport_trap_api_1937", "teleport_trap_api_1938", "teleport_trap_api_1939", "teleport_trap_api_1940", "teleport_trap_api_1941", "teleport_trap_api_1942", "teleport_trap_api_1943", "teleport_trap_api_1944", "teleport_trap_api_1945", "teleport_trap_api_1946", "teleport_trap_api_1947", "teleport_trap_api_1948", "teleport_trap_api_1949", "teleport_trap_api_1950", "teleport_trap_api_1951", "teleport_trap_api_1952", "teleport_trap_api_1953", "teleport_trap_api_1954", "teleport_trap_api_1955", "teleport_trap_api_1956", "teleport_trap_api_1957", "teleport_trap_api_1958", "teleport_trap_api_1959", "teleport_trap_api_1960", "teleport_trap_api_1961", "teleport_trap_api_1962", "teleport_trap_api_1963", "teleport_trap_api_1964", "teleport_trap_api_1965", "teleport_trap_api_1966", "teleport_trap_api_1967", "teleport_trap_api_1968", "teleport_trap_api_1969", "teleport_trap_api_1970", "teleport_trap_api_1971", "teleport_trap_api_1972", "teleport_trap_api_1973", "teleport_trap_api_1974", "teleport_trap_api_1975", "teleport_trap_api_1976", "teleport_trap_api_1977", "teleport_trap_api_1978", "teleport_trap_api_1979", "teleport_trap_api_1980", "teleport_trap_api_1981", "teleport_trap_api_1982", "teleport_trap_api_1983", "teleport_trap_api_1984", "teleport_trap_api_1985", "teleport_trap_api_1986", "teleport_trap_api_1987", "teleport_trap_api_1988", "teleport_trap_api_1989", "teleport_trap_api_1990", "teleport_trap_api_1991", "teleport_trap_api_1992", "teleport_trap_api_1993", "teleport_trap_api_1994", "teleport_trap_api_1995", "teleport_trap_api_1996", "$stackAlloc", "$stackSave", "$stackRestore", "$UTF8ToString", "$lengthBytesUTF8", "$stringToUTF8"],
$teleportTrapServices:function(){
var state=Module.teleportTrapTransport||={next:0,strings:new Map()};
var pointer=v=>BigInt(v??0);
var literal=s=>{if(state.strings.has(s))return state.strings.get(s);var n=lengthBytesUTF8(s)+1;if(state.next+n>Number(_teleport_trap_literal_capacity()))throw Error('TRAP literal capacity');var at=Number(_teleport_trap_literal_storage())+state.next;stringToUTF8(s,at,n);state.next+=n;state.strings.set(s,at);return at;};
var layout=state.layout;if(!layout){layout=Object.create(null);for(var i=0;i<Number(_teleport_trap_layout_count());i++){var name=UTF8ToString(Number(_teleport_trap_layout_name(BigInt(i)))),value=Number(_teleport_trap_layout_value(BigInt(i)));if(Object.hasOwn(layout,name)||!Number.isSafeInteger(value)||value<0)throw Error('TRAP layout metadata '+name);layout[name]=value;}}
return {moduleKey:Module,layout,commitLayout:()=>{if(!state.layout)state.layout=Object.freeze(layout);},heap:()=>HEAPU8,literal,stackAlloc:n=>Number(stackAlloc(n)),stackSave:()=>stackSave(),stackRestore:p=>stackRestore(p),
global:i=>Number(_teleport_trap_global(i)),storage:i=>Number(_teleport_trap_storage(i)),
functionPointer:name=>{var i=["ansimpleoname", "doname", "rn2_on_display_rng", "unsqueak_ok", "xname"].indexOf(name);if(i<0)throw Error('TRAP callback '+name);return Number(_teleport_trap_function_pointer(i));},
api:(site,...args)=>{switch(site){
case 0:return Number(_teleport_trap_api_0(Number(args[0])));
case 1:return Number(_teleport_trap_api_1(BigInt(args[0]),Number(args[1])));
case 2:return _teleport_trap_api_2();
case 3:return _teleport_trap_api_3(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 4:return _teleport_trap_api_4(Number(args[0]));
case 5:return _teleport_trap_api_5(Number(args[0]));
case 6:return _teleport_trap_api_6(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 7:return _teleport_trap_api_7();
case 8:return _teleport_trap_api_8(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 9:return _teleport_trap_api_9(Number(args[0]));
case 10:return _teleport_trap_api_10(Number(args[0]));
case 11:return Number(_teleport_trap_api_11(BigInt(args[0]),BigInt(args[1])));
case 12:return Number(_teleport_trap_api_12(BigInt(args[0])));
case 13:return _teleport_trap_api_13(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]));
case 14:return Number(_teleport_trap_api_14(BigInt(args[0]),BigInt(args[1])));
case 15:return Number(_teleport_trap_api_15(BigInt(args[0])));
case 16:return Number(_teleport_trap_api_16(BigInt(args[0]),BigInt(args[1])));
case 17:return Number(_teleport_trap_api_17(BigInt(args[0])));
case 18:return Number(_teleport_trap_api_18(BigInt(args[0]),BigInt(args[1])));
case 19:return Number(_teleport_trap_api_19(BigInt(args[0]),BigInt(args[1])));
case 20:return Number(_teleport_trap_api_20(BigInt(args[0]),BigInt(args[1])));
case 21:return Number(_teleport_trap_api_21(BigInt(args[0]),BigInt(args[1])));
case 22:return _teleport_trap_api_22(BigInt(args[0]));
case 23:return _teleport_trap_api_23(Number(args[0]),Number(args[1]));
case 24:return _teleport_trap_api_24(Number(args[0]),Number(args[1]),Number(args[2]),Number(args[3]));
case 25:return _teleport_trap_api_25(Number(args[0]));
case 26:return _teleport_trap_api_26(BigInt(args[0]));
case 27:return _teleport_trap_api_27(BigInt(args[0]));
case 28:return _teleport_trap_api_28(Number(args[0]));
case 29:return _teleport_trap_api_29(BigInt(args[0]));
case 30:return Number(_teleport_trap_api_30(BigInt(args[0])));
case 31:return _teleport_trap_api_31(BigInt(args[0]),BigInt(args[1]),Number(args[2]));
case 32:return _teleport_trap_api_32(BigInt(args[0]));
case 33:return Number(_teleport_trap_api_33(BigInt(args[0])));
case 34:return Number(_teleport_trap_api_34(BigInt(args[0])));
case 35:return Number(_teleport_trap_api_35(BigInt(args[0]),BigInt(args[1])));
case 36:return _teleport_trap_api_36(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]),BigInt(args[4]));
case 37:return _teleport_trap_api_37();
case 38:return _teleport_trap_api_38(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 39:return _teleport_trap_api_39(Number(args[0]));
case 40:return _teleport_trap_api_40(Number(args[0]));
case 41:return Number(_teleport_trap_api_41(BigInt(args[0])));
case 42:return Number(_teleport_trap_api_42(BigInt(args[0])));
case 43:return Number(_teleport_trap_api_43(BigInt(args[0]),BigInt(args[1])));
case 44:return _teleport_trap_api_44(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]),BigInt(args[4]));
case 45:return _teleport_trap_api_45();
case 46:return Number(_teleport_trap_api_46(BigInt(args[0])));
case 47:return Number(_teleport_trap_api_47(BigInt(args[0])));
case 48:return Number(_teleport_trap_api_48(BigInt(args[0]),BigInt(args[1])));
case 49:return _teleport_trap_api_49(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]),BigInt(args[4]));
case 50:return _teleport_trap_api_50(BigInt(args[0]),Number(args[1]));
case 51:return _teleport_trap_api_51();
case 52:return Number(_teleport_trap_api_52(BigInt(args[0]),BigInt(args[1])));
case 53:return _teleport_trap_api_53(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 54:return _teleport_trap_api_54(BigInt(args[0]),BigInt(args[1]));
case 55:return Number(_teleport_trap_api_55(BigInt(args[0])));
case 56:return Number(_teleport_trap_api_56(BigInt(args[0])));
case 57:return _teleport_trap_api_57(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]));
case 58:return _teleport_trap_api_58(BigInt(args[0]),Number(args[1]));
case 59:return _teleport_trap_api_59(BigInt(args[0]),Number(args[1]));
case 60:return _teleport_trap_api_60(BigInt(args[0]),BigInt(args[1]),Number(args[2]),Number(args[3]));
case 61:return Number(_teleport_trap_api_61(BigInt(args[0])));
case 62:return _teleport_trap_api_62(BigInt(args[0]),Number(args[1]),Number(args[2]),BigInt(args[3]),BigInt(args[4]));
case 63:return _teleport_trap_api_63(BigInt(args[0]));
case 64:return Number(_teleport_trap_api_64(BigInt(args[0]),BigInt(args[1])));
case 65:return _teleport_trap_api_65(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]));
case 66:return Number(_teleport_trap_api_66(BigInt(args[0])));
case 67:return Number(_teleport_trap_api_67(BigInt(args[0])));
case 68:return Number(_teleport_trap_api_68(BigInt(args[0]),BigInt(args[1])));
case 69:return _teleport_trap_api_69(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]),BigInt(args[4]));
case 70:return _teleport_trap_api_70(BigInt(args[0]));
case 71:return Number(_teleport_trap_api_71(BigInt(args[0]),BigInt(args[1])));
case 72:return _teleport_trap_api_72(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]));
case 73:return Number(_teleport_trap_api_73(BigInt(args[0])));
case 74:return Number(_teleport_trap_api_74(BigInt(args[0]),BigInt(args[1])));
case 75:return _teleport_trap_api_75(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]),BigInt(args[4]));
case 76:return Number(_teleport_trap_api_76(BigInt(args[0]),BigInt(args[1])));
case 77:return _teleport_trap_api_77(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 78:return _teleport_trap_api_78();
case 79:return _teleport_trap_api_79(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 80:return _teleport_trap_api_80(Number(args[0]));
case 81:return _teleport_trap_api_81(Number(args[0]));
case 82:return _teleport_trap_api_82(BigInt(args[0]));
case 83:return _teleport_trap_api_83();
case 84:return _teleport_trap_api_84(Number(args[0]),Number(args[1]));
case 85:return _teleport_trap_api_85(Number(args[0]));
case 86:return _teleport_trap_api_86(Number(args[0]));
case 87:return Number(_teleport_trap_api_87(Number(args[0]),BigInt(args[1]),BigInt(args[2]),Number(args[3]),Number(args[4]),Number(args[5])));
case 88:return Number(_teleport_trap_api_88(BigInt(args[0]),Number(args[1]),Number(args[2]),Number(args[3])));
case 89:return _teleport_trap_api_89(BigInt(args[0]));
case 90:return Number(_teleport_trap_api_90(BigInt(args[0]),BigInt(args[1])));
case 91:return _teleport_trap_api_91(BigInt(args[0]));
case 92:return _teleport_trap_api_92(BigInt(args[0]));
case 93:return _teleport_trap_api_93(BigInt(args[0]));
case 94:return _teleport_trap_api_94(BigInt(args[0]));
case 95:return _teleport_trap_api_95(BigInt(args[0]));
case 96:return _teleport_trap_api_96(BigInt(args[0]));
case 97:return _teleport_trap_api_97();
case 98:return _teleport_trap_api_98(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 99:return _teleport_trap_api_99(Number(args[0]));
case 100:return _teleport_trap_api_100(Number(args[0]));
case 101:return _teleport_trap_api_101(Number(args[0]),Number(args[1]));
case 102:return _teleport_trap_api_102(Number(args[0]),Number(args[1]));
case 103:return _teleport_trap_api_103(BigInt(args[0]));
case 104:return Number(_teleport_trap_api_104(Number(args[0])));
case 105:return Number(_teleport_trap_api_105(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 106:return Number(_teleport_trap_api_106(Number(args[0]),Number(args[1]),Number(args[2])));
case 107:return _teleport_trap_api_107(Number(args[0]),Number(args[1]),BigInt(args[2]));
case 108:return _teleport_trap_api_108(Number(args[0]),Number(args[1]),Number(args[2]));
case 109:return _teleport_trap_api_109(Number(args[0]),Number(args[1]),Number(args[2]));
case 110:return _teleport_trap_api_110(Number(args[0]),Number(args[1]),Number(args[2]));
case 111:return _teleport_trap_api_111(Number(args[0]),Number(args[1]),Number(args[2]));
case 112:return _teleport_trap_api_112(Number(args[0]),Number(args[1]),Number(args[2]));
case 113:return _teleport_trap_api_113(Number(args[0]),Number(args[1]));
case 114:return _teleport_trap_api_114(Number(args[0]),Number(args[1]));
case 115:return _teleport_trap_api_115(Number(args[0]),Number(args[1]));
case 116:return _teleport_trap_api_116(BigInt(args[0]));
case 117:return _teleport_trap_api_117(BigInt(args[0]));
case 118:return _teleport_trap_api_118(BigInt(args[0]));
case 119:return _teleport_trap_api_119(BigInt(args[0]));
case 120:return Number(_teleport_trap_api_120(Number(args[0]),Number(args[1])));
case 121:return _teleport_trap_api_121(BigInt(args[0]),BigInt(args[1]));
case 122:return _teleport_trap_api_122(BigInt(args[0]));
case 123:return _teleport_trap_api_123(BigInt(args[0]));
case 124:return _teleport_trap_api_124();
case 125:return _teleport_trap_api_125(BigInt(args[0]),BigInt(args[1]));
case 126:return _teleport_trap_api_126(BigInt(args[0]),Number(args[1]),Number(args[2]),Number(args[3]));
case 128:return _teleport_trap_api_128(BigInt(args[0]));
case 129:return _teleport_trap_api_129(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 130:return _teleport_trap_api_130(Number(args[0]));
case 131:return _teleport_trap_api_131(BigInt(args[0]),BigInt(args[1]));
case 132:return _teleport_trap_api_132(BigInt(args[0]));
case 133:return _teleport_trap_api_133(BigInt(args[0]),BigInt(args[1]));
case 134:return _teleport_trap_api_134(BigInt(args[0]));
case 135:return _teleport_trap_api_135(BigInt(args[0]));
case 136:return _teleport_trap_api_136(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]));
case 137:return Number(_teleport_trap_api_137(Number(args[0]),Number(args[1])));
case 138:return _teleport_trap_api_138(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 139:return _teleport_trap_api_139(BigInt(args[0]),Number(args[1]),BigInt(args[2]),BigInt(args[3]));
case 140:return _teleport_trap_api_140(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 141:return Number(_teleport_trap_api_141(BigInt(args[0]),BigInt(args[1]),Number(args[2])));
case 142:return _teleport_trap_api_142(BigInt(args[0]),Number(args[1]));
case 143:return _teleport_trap_api_143(Number(args[0]));
case 144:return Number(_teleport_trap_api_144(BigInt(args[0]),Number(args[1]),Number(args[2]),Number(args[3])));
case 145:return _teleport_trap_api_145(BigInt(args[0]),BigInt(args[1]),Number(args[2]));
case 146:return Number(_teleport_trap_api_146(BigInt(args[0]),Number(args[1]),Number(args[2]),Number(args[3])));
case 147:return Number(_teleport_trap_api_147(BigInt(args[0]),BigInt(args[1])));
case 148:return _teleport_trap_api_148(BigInt(args[0]));
case 149:return _teleport_trap_api_149(BigInt(args[0]));
case 150:return _teleport_trap_api_150(BigInt(args[0]));
case 151:return _teleport_trap_api_151(BigInt(args[0]));
case 152:return Number(_teleport_trap_api_152(Number(args[0]),Number(args[1]),Number(args[2])));
case 153:return Number(_teleport_trap_api_153(Number(args[0])));
case 154:return Number(_teleport_trap_api_154(BigInt(args[0]),BigInt(args[1])));
case 155:return Number(_teleport_trap_api_155(BigInt(args[0])));
case 156:return _teleport_trap_api_156(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]));
case 157:return Number(_teleport_trap_api_157(BigInt(args[0])));
case 158:return _teleport_trap_api_158(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 159:return Number(_teleport_trap_api_159(BigInt(args[0])));
case 160:return _teleport_trap_api_160(BigInt(args[0]),BigInt(args[1]));
case 161:return Number(_teleport_trap_api_161(BigInt(args[0]),BigInt(args[1])));
case 162:return Number(_teleport_trap_api_162(BigInt(args[0])));
case 163:return _teleport_trap_api_163(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]));
case 164:return Number(_teleport_trap_api_164(BigInt(args[0]),BigInt(args[1])));
case 165:return _teleport_trap_api_165(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 166:return _teleport_trap_api_166(Number(args[0]),Number(args[1]));
case 167:return _teleport_trap_api_167(BigInt(args[0]));
case 168:return _teleport_trap_api_168(BigInt(args[0]));
case 169:return Number(_teleport_trap_api_169(BigInt(args[0])));
case 170:return _teleport_trap_api_170(BigInt(args[0]),BigInt(args[1]));
case 171:return _teleport_trap_api_171(BigInt(args[0]));
case 172:return _teleport_trap_api_172(BigInt(args[0]));
case 173:return _teleport_trap_api_173(Number(args[0]),Number(args[1]));
case 174:return _teleport_trap_api_174();
case 175:return _teleport_trap_api_175(Number(args[0]),Number(args[1]));
case 176:return Number(_teleport_trap_api_176(Number(args[0]),Number(args[1]),Number(args[2])));
case 177:return Number(_teleport_trap_api_177(Number(args[0])));
case 178:return _teleport_trap_api_178(BigInt(args[0]),Number(args[1]),Number(args[2]),Number(args[3]),Number(args[4]));
case 179:return _teleport_trap_api_179(BigInt(args[0]),BigInt(args[1]));
case 180:return _teleport_trap_api_180(Number(args[0]));
case 181:return _teleport_trap_api_181(BigInt(args[0]),BigInt(args[1]));
case 182:return _teleport_trap_api_182(BigInt(args[0]));
case 183:return _teleport_trap_api_183(BigInt(args[0]),BigInt(args[1]));
case 184:return _teleport_trap_api_184(BigInt(args[0]),Number(args[1]));
case 185:return _teleport_trap_api_185(BigInt(args[0]),Number(args[1]));
case 186:return _teleport_trap_api_186(BigInt(args[0]));
case 187:return Number(_teleport_trap_api_187(Number(args[0]),Number(args[1]),Number(args[2])));
case 188:return Number(_teleport_trap_api_188(BigInt(args[0]),Number(args[1]),Number(args[2])));
case 189:return _teleport_trap_api_189(Number(args[0]),Number(args[1]));
case 190:return _teleport_trap_api_190(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),Number(args[3]));
case 191:return _teleport_trap_api_191(BigInt(args[0]));
case 192:return _teleport_trap_api_192(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 193:return _teleport_trap_api_193(BigInt(args[0]));
case 194:return _teleport_trap_api_194(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 195:return Number(_teleport_trap_api_195(BigInt(args[0])));
case 196:return _teleport_trap_api_196(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]),BigInt(args[4]));
case 197:return _teleport_trap_api_197(Number(args[0]),Number(args[1]));
case 198:return _teleport_trap_api_198(BigInt(args[0]),BigInt(args[1]));
case 199:return Number(_teleport_trap_api_199(BigInt(args[0])));
case 200:return _teleport_trap_api_200(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]));
case 201:return Number(_teleport_trap_api_201(Number(args[0]),Number(args[1]),Number(args[2])));
case 202:return _teleport_trap_api_202(BigInt(args[0]));
case 203:return _teleport_trap_api_203();
case 204:return _teleport_trap_api_204(BigInt(args[0]));
case 205:return Number(_teleport_trap_api_205(BigInt(args[0]),BigInt(args[1])));
case 206:return _teleport_trap_api_206(BigInt(args[0]),Number(args[1]));
case 207:return _teleport_trap_api_207(BigInt(args[0]),Number(args[1]));
case 208:return _teleport_trap_api_208(BigInt(args[0]),Number(args[1]));
case 209:return _teleport_trap_api_209(BigInt(args[0]),Number(args[1]));
case 210:return _teleport_trap_api_210(BigInt(args[0]));
case 211:return _teleport_trap_api_211(BigInt(args[0]),Number(args[1]));
case 212:return _teleport_trap_api_212(BigInt(args[0]),Number(args[1]));
case 213:return _teleport_trap_api_213();
case 214:return _teleport_trap_api_214(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 215:return _teleport_trap_api_215(Number(args[0]));
case 216:return _teleport_trap_api_216(Number(args[0]));
case 217:return _teleport_trap_api_217(BigInt(args[0]));
case 218:return _teleport_trap_api_218(Number(args[0]),Number(args[1]));
case 219:return _teleport_trap_api_219(BigInt(args[0]));
case 220:return _teleport_trap_api_220(BigInt(args[0]),BigInt(args[1]));
case 221:return _teleport_trap_api_221();
case 222:return _teleport_trap_api_222(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 223:return _teleport_trap_api_223(Number(args[0]));
case 224:return _teleport_trap_api_224(Number(args[0]));
case 225:return _teleport_trap_api_225(Number(args[0]),Number(args[1]),BigInt(args[2]),BigInt(args[3]));
case 226:return _teleport_trap_api_226(BigInt(args[0]),BigInt(args[1]));
case 227:return _teleport_trap_api_227(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 228:return _teleport_trap_api_228(BigInt(args[0]));
case 229:return _teleport_trap_api_229(BigInt(args[0]));
case 230:return _teleport_trap_api_230(Number(args[0]),Number(args[1]));
case 231:return _teleport_trap_api_231(BigInt(args[0]));
case 232:return _teleport_trap_api_232();
case 233:return _teleport_trap_api_233(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 234:return _teleport_trap_api_234(Number(args[0]));
case 235:return _teleport_trap_api_235(Number(args[0]));
case 236:return Number(_teleport_trap_api_236(BigInt(args[0])));
case 237:return _teleport_trap_api_237(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 238:return _teleport_trap_api_238(Number(args[0]),Number(args[1]));
case 239:return _teleport_trap_api_239();
case 240:return _teleport_trap_api_240(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 241:return _teleport_trap_api_241(Number(args[0]));
case 242:return _teleport_trap_api_242(Number(args[0]));
case 243:return _teleport_trap_api_243(BigInt(args[0]));
case 244:return _teleport_trap_api_244(Number(args[0]),Number(args[1]));
case 245:return _teleport_trap_api_245(BigInt(args[0]));
case 246:return _teleport_trap_api_246();
case 247:return _teleport_trap_api_247(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 248:return _teleport_trap_api_248(Number(args[0]));
case 249:return _teleport_trap_api_249(Number(args[0]));
case 250:return _teleport_trap_api_250(BigInt(args[0]),BigInt(args[1]));
case 251:return _teleport_trap_api_251();
case 252:return _teleport_trap_api_252(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 253:return _teleport_trap_api_253(Number(args[0]));
case 254:return _teleport_trap_api_254(Number(args[0]));
case 255:return _teleport_trap_api_255(Number(args[0]),Number(args[1]),BigInt(args[2]),BigInt(args[3]));
case 256:return _teleport_trap_api_256(BigInt(args[0]),Number(args[1]),BigInt(args[2]),Number(args[3]),Number(args[4]));
case 257:return _teleport_trap_api_257(BigInt(args[0]),BigInt(args[1]));
case 258:return _teleport_trap_api_258(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 259:return _teleport_trap_api_259(BigInt(args[0]));
case 260:return _teleport_trap_api_260(BigInt(args[0]));
case 261:return _teleport_trap_api_261(Number(args[0]),Number(args[1]));
case 262:return _teleport_trap_api_262(BigInt(args[0]));
case 263:return _teleport_trap_api_263();
case 264:return _teleport_trap_api_264(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 265:return _teleport_trap_api_265(Number(args[0]));
case 266:return _teleport_trap_api_266(Number(args[0]));
case 267:return Number(_teleport_trap_api_267(BigInt(args[0])));
case 268:return _teleport_trap_api_268(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 269:return _teleport_trap_api_269(Number(args[0]),Number(args[1]));
case 270:return _teleport_trap_api_270();
case 271:return _teleport_trap_api_271(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 272:return _teleport_trap_api_272(Number(args[0]));
case 273:return _teleport_trap_api_273(Number(args[0]));
case 274:return _teleport_trap_api_274();
case 275:return _teleport_trap_api_275(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 276:return _teleport_trap_api_276(Number(args[0]));
case 277:return _teleport_trap_api_277(Number(args[0]));
case 278:return Number(_teleport_trap_api_278(Number(args[0]),Number(args[1])));
case 279:return Number(_teleport_trap_api_279(BigInt(args[0])));
case 280:return _teleport_trap_api_280(BigInt(args[0]),BigInt(args[1]));
case 281:return _teleport_trap_api_281(Number(args[0]),Number(args[1]));
case 282:return _teleport_trap_api_282();
case 283:return _teleport_trap_api_283(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 284:return _teleport_trap_api_284(Number(args[0]),Number(args[1]));
case 285:return _teleport_trap_api_285(Number(args[0]),Number(args[1]));
case 286:return _teleport_trap_api_286(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 287:return Number(_teleport_trap_api_287(Number(args[0]),Number(args[1])));
case 288:return Number(_teleport_trap_api_288(BigInt(args[0])));
case 289:return Number(_teleport_trap_api_289(BigInt(args[0])));
case 290:return Number(_teleport_trap_api_290(BigInt(args[0])));
case 291:return Number(_teleport_trap_api_291(Number(args[0])));
case 292:return _teleport_trap_api_292(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]));
case 293:return Number(_teleport_trap_api_293(BigInt(args[0])));
case 294:return Number(_teleport_trap_api_294(BigInt(args[0])));
case 295:return _teleport_trap_api_295(BigInt(args[0]),BigInt(args[1]));
case 296:return _teleport_trap_api_296(BigInt(args[0]));
case 297:return _teleport_trap_api_297(BigInt(args[0]));
case 298:return Number(_teleport_trap_api_298(BigInt(args[0])));
case 299:return _teleport_trap_api_299(BigInt(args[0]),BigInt(args[1]));
case 300:return _teleport_trap_api_300(BigInt(args[0]));
case 301:return _teleport_trap_api_301(BigInt(args[0]));
case 302:return _teleport_trap_api_302(BigInt(args[0]));
case 303:return _teleport_trap_api_303(Number(args[0]),Number(args[1]));
case 304:return _teleport_trap_api_304(Number(args[0]),BigInt(args[1]),Number(args[2]));
case 305:return _teleport_trap_api_305(Number(args[0]),Number(args[1]));
case 306:return _teleport_trap_api_306(BigInt(args[0]));
case 307:return _teleport_trap_api_307();
case 308:return _teleport_trap_api_308(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 309:return _teleport_trap_api_309(Number(args[0]));
case 310:return _teleport_trap_api_310(Number(args[0]));
case 311:return Number(_teleport_trap_api_311(BigInt(args[0])));
case 312:return _teleport_trap_api_312(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 313:return _teleport_trap_api_313(Number(args[0]),Number(args[1]));
case 314:return _teleport_trap_api_314();
case 315:return _teleport_trap_api_315(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 316:return _teleport_trap_api_316(Number(args[0]),Number(args[1]));
case 317:return _teleport_trap_api_317(Number(args[0]),Number(args[1]));
case 318:return _teleport_trap_api_318(BigInt(args[0]));
case 319:return _teleport_trap_api_319(BigInt(args[0]));
case 320:return _teleport_trap_api_320(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]));
case 321:return _teleport_trap_api_321(Number(args[0]));
case 322:return _teleport_trap_api_322(BigInt(args[0]));
case 323:return _teleport_trap_api_323(BigInt(args[0]));
case 324:return Number(_teleport_trap_api_324(BigInt(args[0])));
case 325:return _teleport_trap_api_325(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]));
case 326:return Number(_teleport_trap_api_326(BigInt(args[0])));
case 327:return _teleport_trap_api_327(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 328:return _teleport_trap_api_328(Number(args[0]),Number(args[1]),Number(args[2]),Number(args[3]));
case 329:return _teleport_trap_api_329(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 330:return _teleport_trap_api_330(Number(args[0]),Number(args[1]),Number(args[2]));
case 331:return _teleport_trap_api_331();
case 332:return _teleport_trap_api_332(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 333:return _teleport_trap_api_333(Number(args[0]),Number(args[1]));
case 334:return _teleport_trap_api_334(Number(args[0]),Number(args[1]));
case 335:return _teleport_trap_api_335(BigInt(args[0]),BigInt(args[1]));
case 336:return _teleport_trap_api_336(BigInt(args[0]),BigInt(args[1]));
case 337:return _teleport_trap_api_337();
case 338:return _teleport_trap_api_338(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 339:return _teleport_trap_api_339(Number(args[0]));
case 340:return _teleport_trap_api_340(Number(args[0]));
case 341:return Number(_teleport_trap_api_341(BigInt(args[0])));
case 342:return Number(_teleport_trap_api_342(BigInt(args[0])));
case 343:return Number(_teleport_trap_api_343(BigInt(args[0]),Number(args[1])));
case 344:return _teleport_trap_api_344(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]));
case 345:return Number(_teleport_trap_api_345(Number(args[0])));
case 346:return _teleport_trap_api_346(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 347:return _teleport_trap_api_347(BigInt(args[0]));
case 348:return Number(_teleport_trap_api_348(BigInt(args[0])));
case 349:return _teleport_trap_api_349(BigInt(args[0]),BigInt(args[1]));
case 350:return _teleport_trap_api_350();
case 351:return _teleport_trap_api_351(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 352:return _teleport_trap_api_352(Number(args[0]));
case 353:return _teleport_trap_api_353(Number(args[0]));
case 354:return _teleport_trap_api_354();
case 355:return _teleport_trap_api_355(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 356:return _teleport_trap_api_356(Number(args[0]));
case 357:return _teleport_trap_api_357(Number(args[0]));
case 358:return _teleport_trap_api_358(BigInt(args[0]),Number(args[1]));
case 359:return _teleport_trap_api_359(Number(args[0]),BigInt(args[1]),Number(args[2]));
case 360:return _teleport_trap_api_360(Number(args[0]),Number(args[1]));
case 361:return _teleport_trap_api_361(BigInt(args[0]));
case 362:return _teleport_trap_api_362(BigInt(args[0]));
case 363:return Number(_teleport_trap_api_363(BigInt(args[0])));
case 364:return _teleport_trap_api_364(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]));
case 365:return _teleport_trap_api_365(BigInt(args[0]));
case 366:return Number(_teleport_trap_api_366(BigInt(args[0])));
case 367:return _teleport_trap_api_367(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]));
case 368:return _teleport_trap_api_368();
case 369:return _teleport_trap_api_369(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 370:return _teleport_trap_api_370(Number(args[0]),Number(args[1]));
case 371:return _teleport_trap_api_371(Number(args[0]),Number(args[1]));
case 372:return _teleport_trap_api_372(BigInt(args[0]));
case 373:return _teleport_trap_api_373(BigInt(args[0]));
case 374:return _teleport_trap_api_374(BigInt(args[0]));
case 375:return _teleport_trap_api_375();
case 376:return _teleport_trap_api_376(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 377:return _teleport_trap_api_377(Number(args[0]));
case 378:return _teleport_trap_api_378(Number(args[0]));
case 379:return _teleport_trap_api_379(Number(args[0]),Number(args[1]));
case 380:return _teleport_trap_api_380(BigInt(args[0]));
case 381:return _teleport_trap_api_381(BigInt(args[0]));
case 382:return _teleport_trap_api_382(BigInt(args[0]),Number(args[1]));
case 383:return _teleport_trap_api_383();
case 384:return _teleport_trap_api_384(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 385:return _teleport_trap_api_385(Number(args[0]));
case 386:return _teleport_trap_api_386(Number(args[0]));
case 387:return _teleport_trap_api_387(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 388:return Number(_teleport_trap_api_388(BigInt(args[0])));
case 389:return _teleport_trap_api_389(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 390:return _teleport_trap_api_390();
case 391:return _teleport_trap_api_391(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 392:return _teleport_trap_api_392(Number(args[0]));
case 393:return _teleport_trap_api_393(Number(args[0]));
case 394:return Number(_teleport_trap_api_394(Number(args[0])));
case 395:return _teleport_trap_api_395(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 396:return Number(_teleport_trap_api_396(BigInt(args[0])));
case 397:return Number(_teleport_trap_api_397(Number(args[0])));
case 398:return _teleport_trap_api_398(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 399:return Number(_teleport_trap_api_399(BigInt(args[0])));
case 400:return Number(_teleport_trap_api_400(Number(args[0])));
case 401:return _teleport_trap_api_401(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 402:return _teleport_trap_api_402(BigInt(args[0]),BigInt(args[1]));
case 403:return _teleport_trap_api_403(BigInt(args[0]));
case 404:return Number(_teleport_trap_api_404(BigInt(args[0])));
case 405:return Number(_teleport_trap_api_405(BigInt(args[0])));
case 406:return _teleport_trap_api_406();
case 407:return _teleport_trap_api_407(BigInt(args[0]));
case 408:return _teleport_trap_api_408(Number(args[0]),BigInt(args[1]),Number(args[2]));
case 409:return _teleport_trap_api_409();
case 410:return _teleport_trap_api_410(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 411:return _teleport_trap_api_411(Number(args[0]));
case 412:return _teleport_trap_api_412(Number(args[0]));
case 413:return Number(_teleport_trap_api_413(BigInt(args[0]),BigInt(args[1])));
case 414:return _teleport_trap_api_414(BigInt(args[0]));
case 415:return _teleport_trap_api_415();
case 416:return _teleport_trap_api_416(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 417:return _teleport_trap_api_417(Number(args[0]));
case 418:return _teleport_trap_api_418(Number(args[0]));
case 419:return Number(_teleport_trap_api_419(BigInt(args[0])));
case 420:return Number(_teleport_trap_api_420(BigInt(args[0]),Number(args[1])));
case 421:return _teleport_trap_api_421(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]),BigInt(args[4]));
case 422:return Number(_teleport_trap_api_422(BigInt(args[0]),BigInt(args[1])));
case 423:return Number(_teleport_trap_api_423(BigInt(args[0])));
case 424:return Number(_teleport_trap_api_424(BigInt(args[0])));
case 425:return Number(_teleport_trap_api_425(BigInt(args[0]),Number(args[1])));
case 426:return _teleport_trap_api_426(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]),BigInt(args[4]));
case 427:return Number(_teleport_trap_api_427(BigInt(args[0]),BigInt(args[1])));
case 428:return Number(_teleport_trap_api_428(BigInt(args[0]),BigInt(args[1])));
case 429:return Number(_teleport_trap_api_429(BigInt(args[0])));
case 430:return Number(_teleport_trap_api_430(BigInt(args[0])));
case 431:return Number(_teleport_trap_api_431(BigInt(args[0]),Number(args[1])));
case 432:return _teleport_trap_api_432(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]),BigInt(args[4]));
case 433:return Number(_teleport_trap_api_433(BigInt(args[0])));
case 434:return _teleport_trap_api_434(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 435:return _teleport_trap_api_435(BigInt(args[0]));
case 436:return Number(_teleport_trap_api_436(BigInt(args[0]),BigInt(args[1])));
case 437:return Number(_teleport_trap_api_437(BigInt(args[0])));
case 438:return Number(_teleport_trap_api_438(BigInt(args[0]),BigInt(args[1])));
case 439:return Number(_teleport_trap_api_439(BigInt(args[0])));
case 440:return Number(_teleport_trap_api_440(BigInt(args[0]),BigInt(args[1])));
case 441:return Number(_teleport_trap_api_441(BigInt(args[0])));
case 442:return Number(_teleport_trap_api_442(BigInt(args[0])));
case 443:return _teleport_trap_api_443(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]));
case 444:return _teleport_trap_api_444(BigInt(args[0]),BigInt(args[1]),Number(args[2]));
case 445:return _teleport_trap_api_445();
case 446:return _teleport_trap_api_446(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 447:return _teleport_trap_api_447(Number(args[0]));
case 448:return _teleport_trap_api_448(Number(args[0]));
case 449:return Number(_teleport_trap_api_449(BigInt(args[0]),BigInt(args[1])));
case 450:return _teleport_trap_api_450(BigInt(args[0]));
case 451:return _teleport_trap_api_451();
case 452:return _teleport_trap_api_452(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 453:return _teleport_trap_api_453(Number(args[0]),Number(args[1]));
case 454:return _teleport_trap_api_454(Number(args[0]),Number(args[1]));
case 455:return Number(_teleport_trap_api_455(Number(args[0]),Number(args[1])));
case 456:return Number(_teleport_trap_api_456(BigInt(args[0])));
case 457:return _teleport_trap_api_457(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]),BigInt(args[4]));
case 458:return _teleport_trap_api_458(Number(args[0]),Number(args[1]));
case 459:return Number(_teleport_trap_api_459(Number(args[0]),Number(args[1])));
case 460:return _teleport_trap_api_460(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 461:return _teleport_trap_api_461(BigInt(args[0]),Number(args[1]));
case 462:return _teleport_trap_api_462(Number(args[0]),Number(args[1]));
case 463:return Number(_teleport_trap_api_463(BigInt(args[0])));
case 464:return _teleport_trap_api_464(BigInt(args[0]),BigInt(args[1]));
case 465:return _teleport_trap_api_465();
case 466:return _teleport_trap_api_466(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 467:return _teleport_trap_api_467(Number(args[0]));
case 468:return _teleport_trap_api_468(Number(args[0]));
case 469:return _teleport_trap_api_469();
case 470:return _teleport_trap_api_470(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 471:return _teleport_trap_api_471(Number(args[0]));
case 472:return _teleport_trap_api_472(Number(args[0]));
case 473:return _teleport_trap_api_473(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 474:return _teleport_trap_api_474(BigInt(args[0]),BigInt(args[1]),Number(args[2]));
case 475:return _teleport_trap_api_475(Number(args[0]),Number(args[1]),Number(args[2]),Number(args[3]));
case 476:return _teleport_trap_api_476(Number(args[0]),Number(args[1]),Number(args[2]),Number(args[3]));
case 477:return _teleport_trap_api_477(BigInt(args[0]));
case 478:return _teleport_trap_api_478(Number(args[0]),Number(args[1]));
case 479:return _teleport_trap_api_479(Number(args[0]),Number(args[1]),BigInt(args[2]));
case 480:return _teleport_trap_api_480(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 481:return _teleport_trap_api_481(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 482:return _teleport_trap_api_482(BigInt(args[0]));
case 483:return Number(_teleport_trap_api_483(BigInt(args[0]),Number(args[1]),BigInt(args[2]),Number(args[3]),Number(args[4])));
case 484:return _teleport_trap_api_484(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 485:return Number(_teleport_trap_api_485(BigInt(args[0]),Number(args[1]),BigInt(args[2]),Number(args[3]),Number(args[4])));
case 486:return _teleport_trap_api_486(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 487:return Number(_teleport_trap_api_487(BigInt(args[0])));
case 488:return _teleport_trap_api_488(BigInt(args[0]),BigInt(args[1]));
case 489:return _teleport_trap_api_489(BigInt(args[0]));
case 490:return _teleport_trap_api_490();
case 491:return _teleport_trap_api_491(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 492:return _teleport_trap_api_492(Number(args[0]));
case 493:return _teleport_trap_api_493(Number(args[0]));
case 494:return _teleport_trap_api_494(BigInt(args[0]),BigInt(args[1]));
case 495:return Number(_teleport_trap_api_495(BigInt(args[0]),BigInt(args[1])));
case 496:return _teleport_trap_api_496(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 497:return _teleport_trap_api_497(BigInt(args[0]));
case 498:return _teleport_trap_api_498(BigInt(args[0]),BigInt(args[1]));
case 499:return _teleport_trap_api_499(BigInt(args[0]));
case 500:return _teleport_trap_api_500(BigInt(args[0]));
case 501:return Number(_teleport_trap_api_501(BigInt(args[0])));
case 502:return _teleport_trap_api_502(BigInt(args[0]),BigInt(args[1]));
case 503:return Number(_teleport_trap_api_503(BigInt(args[0]),Number(args[1]),BigInt(args[2]),Number(args[3]),Number(args[4])));
case 504:return Number(_teleport_trap_api_504(BigInt(args[0])));
case 505:return _teleport_trap_api_505(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]));
case 506:return _teleport_trap_api_506(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 507:return _teleport_trap_api_507();
case 508:return _teleport_trap_api_508(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 509:return _teleport_trap_api_509(Number(args[0]));
case 510:return _teleport_trap_api_510(Number(args[0]));
case 511:return _teleport_trap_api_511();
case 512:return _teleport_trap_api_512(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 513:return _teleport_trap_api_513(Number(args[0]));
case 514:return _teleport_trap_api_514(Number(args[0]));
case 515:return _teleport_trap_api_515();
case 516:return _teleport_trap_api_516(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 517:return _teleport_trap_api_517(Number(args[0]));
case 518:return _teleport_trap_api_518(Number(args[0]));
case 519:return _teleport_trap_api_519(Number(args[0]),BigInt(args[1]),Number(args[2]));
case 520:return _teleport_trap_api_520();
case 521:return _teleport_trap_api_521(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 522:return _teleport_trap_api_522(Number(args[0]));
case 523:return _teleport_trap_api_523(Number(args[0]));
case 524:return _teleport_trap_api_524(BigInt(args[0]),Number(args[1]),BigInt(args[2]),Number(args[3]),Number(args[4]));
case 525:return _teleport_trap_api_525();
case 526:return _teleport_trap_api_526(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 527:return _teleport_trap_api_527(Number(args[0]));
case 528:return _teleport_trap_api_528(Number(args[0]));
case 529:return _teleport_trap_api_529();
case 530:return _teleport_trap_api_530(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 531:return _teleport_trap_api_531(Number(args[0]));
case 532:return _teleport_trap_api_532(Number(args[0]));
case 533:return _teleport_trap_api_533(Number(args[0]),BigInt(args[1]),Number(args[2]));
case 534:return _teleport_trap_api_534();
case 535:return _teleport_trap_api_535();
case 536:return _teleport_trap_api_536();
case 537:return _teleport_trap_api_537(Number(args[0]),Number(args[1]));
case 538:return _teleport_trap_api_538(Number(args[0]),Number(args[1]));
case 539:return _teleport_trap_api_539(BigInt(args[0]));
case 540:return _teleport_trap_api_540(BigInt(args[0]));
case 541:return _teleport_trap_api_541(BigInt(args[0]));
case 542:return Number(_teleport_trap_api_542(BigInt(args[0])));
case 543:return _teleport_trap_api_543(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 544:return Number(_teleport_trap_api_544(BigInt(args[0])));
case 545:return _teleport_trap_api_545(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]),BigInt(args[4]));
case 546:return _teleport_trap_api_546(BigInt(args[0]));
case 547:return _teleport_trap_api_547();
case 548:return _teleport_trap_api_548(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 549:return _teleport_trap_api_549(Number(args[0]));
case 550:return _teleport_trap_api_550(Number(args[0]));
case 551:return _teleport_trap_api_551(BigInt(args[0]));
case 552:return _teleport_trap_api_552(BigInt(args[0]),BigInt(args[1]));
case 553:return _teleport_trap_api_553(BigInt(args[0]));
case 554:return _teleport_trap_api_554(BigInt(args[0]));
case 555:return _teleport_trap_api_555(BigInt(args[0]),BigInt(args[1]));
case 556:return _teleport_trap_api_556(BigInt(args[0]));
case 557:return _teleport_trap_api_557(BigInt(args[0]));
case 558:return Number(_teleport_trap_api_558(BigInt(args[0])));
case 559:return _teleport_trap_api_559(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 560:return Number(_teleport_trap_api_560(BigInt(args[0])));
case 561:return _teleport_trap_api_561(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 562:return Number(_teleport_trap_api_562(BigInt(args[0])));
case 563:return _teleport_trap_api_563(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 564:return _teleport_trap_api_564(BigInt(args[0]));
case 565:return _teleport_trap_api_565(BigInt(args[0]));
case 566:return _teleport_trap_api_566(BigInt(args[0]),BigInt(args[1]),Number(args[2]));
case 567:return _teleport_trap_api_567(BigInt(args[0]),Number(args[1]));
case 568:return _teleport_trap_api_568(BigInt(args[0]));
case 569:return _teleport_trap_api_569(BigInt(args[0]),BigInt(args[1]),Number(args[2]),Number(args[3]));
case 570:return _teleport_trap_api_570(BigInt(args[0]));
case 571:return Number(_teleport_trap_api_571(BigInt(args[0]),BigInt(args[1])));
case 572:return Number(_teleport_trap_api_572(BigInt(args[0]),Number(args[1]),BigInt(args[2]),Number(args[3]),Number(args[4])));
case 573:return _teleport_trap_api_573(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 574:return Number(_teleport_trap_api_574(BigInt(args[0])));
case 575:return _teleport_trap_api_575(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 576:return _teleport_trap_api_576(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 577:return _teleport_trap_api_577(Number(args[0]));
case 578:return _teleport_trap_api_578();
case 579:return _teleport_trap_api_579(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 580:return _teleport_trap_api_580(Number(args[0]));
case 581:return _teleport_trap_api_581(Number(args[0]));
case 582:return _teleport_trap_api_582();
case 583:return _teleport_trap_api_583(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 584:return _teleport_trap_api_584(Number(args[0]));
case 585:return _teleport_trap_api_585(Number(args[0]));
case 586:return _teleport_trap_api_586();
case 587:return _teleport_trap_api_587(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 588:return _teleport_trap_api_588(Number(args[0]));
case 589:return _teleport_trap_api_589(Number(args[0]));
case 590:return _teleport_trap_api_590();
case 591:return _teleport_trap_api_591(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 592:return _teleport_trap_api_592(Number(args[0]));
case 593:return _teleport_trap_api_593(Number(args[0]));
case 594:return _teleport_trap_api_594();
case 595:return _teleport_trap_api_595(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 596:return _teleport_trap_api_596(Number(args[0]));
case 597:return _teleport_trap_api_597(Number(args[0]));
case 598:return _teleport_trap_api_598();
case 599:return _teleport_trap_api_599(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 600:return _teleport_trap_api_600(Number(args[0]));
case 601:return _teleport_trap_api_601(Number(args[0]));
case 602:return _teleport_trap_api_602(BigInt(args[0]),BigInt(args[1]));
case 603:return _teleport_trap_api_603(Number(args[0]),Number(args[1]));
case 604:return _teleport_trap_api_604(BigInt(args[0]));
case 605:return _teleport_trap_api_605(BigInt(args[0]));
case 606:return _teleport_trap_api_606(BigInt(args[0]));
case 607:return Number(_teleport_trap_api_607(BigInt(args[0])));
case 608:return _teleport_trap_api_608(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]));
case 609:return Number(_teleport_trap_api_609(BigInt(args[0])));
case 610:return _teleport_trap_api_610(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]));
case 611:return _teleport_trap_api_611(Number(args[0]),Number(args[1]));
case 612:return Number(_teleport_trap_api_612(BigInt(args[0])));
case 613:return _teleport_trap_api_613(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]));
case 614:return _teleport_trap_api_614();
case 615:return _teleport_trap_api_615(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 616:return _teleport_trap_api_616(Number(args[0]));
case 617:return _teleport_trap_api_617(Number(args[0]));
case 618:return _teleport_trap_api_618(Number(args[0]),Number(args[1]));
case 619:return _teleport_trap_api_619(BigInt(args[0]));
case 620:return _teleport_trap_api_620();
case 621:return _teleport_trap_api_621(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 622:return _teleport_trap_api_622(Number(args[0]));
case 623:return _teleport_trap_api_623(Number(args[0]));
case 624:return _teleport_trap_api_624(Number(args[0]),BigInt(args[1]),Number(args[2]));
case 625:return _teleport_trap_api_625(BigInt(args[0]));
case 626:return _teleport_trap_api_626();
case 627:return _teleport_trap_api_627(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 628:return _teleport_trap_api_628(Number(args[0]));
case 629:return _teleport_trap_api_629(Number(args[0]));
case 630:return Number(_teleport_trap_api_630(BigInt(args[0]),BigInt(args[1])));
case 631:return Number(_teleport_trap_api_631(BigInt(args[0])));
case 632:return _teleport_trap_api_632(BigInt(args[0]),BigInt(args[1]));
case 633:return _teleport_trap_api_633(BigInt(args[0]),Number(args[1]));
case 634:return _teleport_trap_api_634();
case 635:return _teleport_trap_api_635();
case 636:return _teleport_trap_api_636(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 637:return _teleport_trap_api_637(Number(args[0]));
case 638:return _teleport_trap_api_638(Number(args[0]));
case 639:return _teleport_trap_api_639();
case 640:return _teleport_trap_api_640(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 641:return _teleport_trap_api_641(Number(args[0]));
case 642:return _teleport_trap_api_642(Number(args[0]));
case 643:return _teleport_trap_api_643(BigInt(args[0]),Number(args[1]));
case 644:return _teleport_trap_api_644();
case 645:return _teleport_trap_api_645(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 646:return _teleport_trap_api_646(Number(args[0]));
case 647:return _teleport_trap_api_647(Number(args[0]));
case 648:return _teleport_trap_api_648(BigInt(args[0]));
case 649:return _teleport_trap_api_649(Number(args[0]),BigInt(args[1]));
case 650:return _teleport_trap_api_650();
case 651:return _teleport_trap_api_651(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 652:return _teleport_trap_api_652(Number(args[0]));
case 653:return _teleport_trap_api_653(Number(args[0]));
case 654:return _teleport_trap_api_654(BigInt(args[0]));
case 655:return _teleport_trap_api_655(Number(args[0]),BigInt(args[1]),Number(args[2]));
case 656:return _teleport_trap_api_656();
case 657:return _teleport_trap_api_657(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 658:return _teleport_trap_api_658(Number(args[0]),Number(args[1]));
case 659:return _teleport_trap_api_659(Number(args[0]),Number(args[1]));
case 660:return _teleport_trap_api_660();
case 661:return _teleport_trap_api_661(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 662:return _teleport_trap_api_662(Number(args[0]));
case 663:return _teleport_trap_api_663(Number(args[0]));
case 664:return _teleport_trap_api_664(BigInt(args[0]));
case 665:return _teleport_trap_api_665(BigInt(args[0]));
case 666:return _teleport_trap_api_666(BigInt(args[0]),Number(args[1]));
case 667:return _teleport_trap_api_667(BigInt(args[0]),Number(args[1]));
case 668:return _teleport_trap_api_668();
case 669:return _teleport_trap_api_669(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 670:return _teleport_trap_api_670(Number(args[0]),Number(args[1]));
case 671:return _teleport_trap_api_671(Number(args[0]),Number(args[1]));
case 672:return Number(_teleport_trap_api_672(BigInt(args[0])));
case 673:return _teleport_trap_api_673(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 674:return _teleport_trap_api_674();
case 675:return _teleport_trap_api_675(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 676:return _teleport_trap_api_676(Number(args[0]));
case 677:return _teleport_trap_api_677(Number(args[0]));
case 678:return _teleport_trap_api_678(BigInt(args[0]),Number(args[1]));
case 679:return _teleport_trap_api_679();
case 680:return _teleport_trap_api_680(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 681:return _teleport_trap_api_681(Number(args[0]));
case 682:return _teleport_trap_api_682(Number(args[0]));
case 683:return _teleport_trap_api_683(Number(args[0]),BigInt(args[1]));
case 684:return _teleport_trap_api_684();
case 685:return _teleport_trap_api_685(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 686:return _teleport_trap_api_686(Number(args[0]));
case 687:return _teleport_trap_api_687(Number(args[0]));
case 688:return _teleport_trap_api_688(BigInt(args[0]),BigInt(args[1]),Number(args[2]));
case 689:return _teleport_trap_api_689(Number(args[0]),Number(args[1]));
case 690:return Number(_teleport_trap_api_690(BigInt(args[0]),BigInt(args[1])));
case 691:return Number(_teleport_trap_api_691(BigInt(args[0]),Number(args[1]),BigInt(args[2]),Number(args[3]),Number(args[4])));
case 692:return _teleport_trap_api_692(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 693:return Number(_teleport_trap_api_693(BigInt(args[0])));
case 694:return _teleport_trap_api_694(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 695:return _teleport_trap_api_695(BigInt(args[0]),BigInt(args[1]));
case 696:return Number(_teleport_trap_api_696(BigInt(args[0])));
case 697:return _teleport_trap_api_697(BigInt(args[0]),BigInt(args[1]));
case 698:return Number(_teleport_trap_api_698(BigInt(args[0]),Number(args[1])));
case 699:return _teleport_trap_api_699();
case 700:return _teleport_trap_api_700(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 701:return _teleport_trap_api_701(Number(args[0]),Number(args[1]));
case 702:return _teleport_trap_api_702(BigInt(args[0]));
case 703:return _teleport_trap_api_703(Number(args[0]),Number(args[1]));
case 704:return _teleport_trap_api_704(BigInt(args[0]));
case 705:return _teleport_trap_api_705(Number(args[0]));
case 706:return _teleport_trap_api_706(BigInt(args[0]));
case 707:return Number(_teleport_trap_api_707(BigInt(args[0]),BigInt(args[1])));
case 708:return _teleport_trap_api_708(BigInt(args[0]),BigInt(args[1]),Number(args[2]),Number(args[3]));
case 709:return _teleport_trap_api_709(BigInt(args[0]),BigInt(args[1]));
case 710:return _teleport_trap_api_710(BigInt(args[0]));
case 711:return Number(_teleport_trap_api_711(BigInt(args[0]),Number(args[1])));
case 712:return _teleport_trap_api_712(BigInt(args[0]),BigInt(args[1]),Number(args[2]),Number(args[3]));
case 713:return _teleport_trap_api_713(BigInt(args[0]));
case 714:return _teleport_trap_api_714(BigInt(args[0]));
case 715:return _teleport_trap_api_715(BigInt(args[0]),Number(args[1]),Number(args[2]),Number(args[3]));
case 716:return _teleport_trap_api_716(BigInt(args[0]),BigInt(args[1]),Number(args[2]));
case 717:return _teleport_trap_api_717();
case 718:return _teleport_trap_api_718(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 719:return _teleport_trap_api_719(Number(args[0]));
case 720:return _teleport_trap_api_720(Number(args[0]));
case 721:return _teleport_trap_api_721();
case 722:return _teleport_trap_api_722(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 723:return _teleport_trap_api_723(Number(args[0]));
case 724:return _teleport_trap_api_724(Number(args[0]));
case 725:return _teleport_trap_api_725(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 726:return _teleport_trap_api_726();
case 727:return _teleport_trap_api_727(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 728:return _teleport_trap_api_728(Number(args[0]));
case 729:return _teleport_trap_api_729(Number(args[0]));
case 730:return _teleport_trap_api_730(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]));
case 731:return _teleport_trap_api_731(BigInt(args[0]),BigInt(args[1]));
case 732:return Number(_teleport_trap_api_732(Number(args[0]),Number(args[1]),Number(args[2])));
case 733:return _teleport_trap_api_733();
case 734:return _teleport_trap_api_734(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 735:return _teleport_trap_api_735(Number(args[0]));
case 736:return _teleport_trap_api_736(Number(args[0]));
case 737:return _teleport_trap_api_737(BigInt(args[0]),Number(args[1]));
case 738:return _teleport_trap_api_738();
case 739:return _teleport_trap_api_739(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 740:return _teleport_trap_api_740(Number(args[0]));
case 741:return _teleport_trap_api_741(Number(args[0]));
case 742:return _teleport_trap_api_742(BigInt(args[0]),Number(args[1]));
case 743:return _teleport_trap_api_743(Number(args[0]),Number(args[1]));
case 744:return _teleport_trap_api_744(Number(args[0]),BigInt(args[1]),Number(args[2]));
case 745:return _teleport_trap_api_745(Number(args[0]),Number(args[1]));
case 746:return _teleport_trap_api_746(BigInt(args[0]));
case 747:return _teleport_trap_api_747();
case 748:return _teleport_trap_api_748(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 749:return _teleport_trap_api_749(Number(args[0]));
case 750:return _teleport_trap_api_750(Number(args[0]));
case 751:return _teleport_trap_api_751(BigInt(args[0]));
case 752:return Number(_teleport_trap_api_752(BigInt(args[0])));
case 753:return _teleport_trap_api_753(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 754:return _teleport_trap_api_754();
case 755:return _teleport_trap_api_755(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 756:return _teleport_trap_api_756(Number(args[0]));
case 757:return _teleport_trap_api_757(Number(args[0]));
case 758:return _teleport_trap_api_758(Number(args[0]),Number(args[1]));
case 759:return _teleport_trap_api_759(BigInt(args[0]),BigInt(args[1]));
case 760:return _teleport_trap_api_760(Number(args[0]),Number(args[1]));
case 761:return Number(_teleport_trap_api_761(BigInt(args[0])));
case 762:return _teleport_trap_api_762(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]),BigInt(args[4]));
case 763:return _teleport_trap_api_763(BigInt(args[0]),BigInt(args[1]));
case 764:return _teleport_trap_api_764(BigInt(args[0]),BigInt(args[1]));
case 765:return _teleport_trap_api_765(BigInt(args[0]));
case 766:return _teleport_trap_api_766(BigInt(args[0]));
case 767:return _teleport_trap_api_767(BigInt(args[0]));
case 768:return _teleport_trap_api_768(BigInt(args[0]));
case 769:return _teleport_trap_api_769(BigInt(args[0]));
case 770:return _teleport_trap_api_770(Number(args[0]),Number(args[1]));
case 771:return Number(_teleport_trap_api_771(BigInt(args[0])));
case 772:return _teleport_trap_api_772(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]),BigInt(args[4]));
case 773:return _teleport_trap_api_773(BigInt(args[0]));
case 774:return _teleport_trap_api_774(BigInt(args[0]));
case 775:return Number(_teleport_trap_api_775(BigInt(args[0])));
case 776:return _teleport_trap_api_776(BigInt(args[0]));
case 777:return Number(_teleport_trap_api_777(BigInt(args[0]),BigInt(args[1])));
case 778:return Number(_teleport_trap_api_778(BigInt(args[0])));
case 779:return Number(_teleport_trap_api_779(BigInt(args[0]),BigInt(args[1])));
case 780:return Number(_teleport_trap_api_780(BigInt(args[0]),BigInt(args[1])));
case 781:return Number(_teleport_trap_api_781(BigInt(args[0])));
case 782:return Number(_teleport_trap_api_782(BigInt(args[0]),Number(args[1])));
case 783:return Number(_teleport_trap_api_783(BigInt(args[0])));
case 784:return Number(_teleport_trap_api_784(BigInt(args[0]),BigInt(args[1])));
case 785:return Number(_teleport_trap_api_785(BigInt(args[0]),BigInt(args[1]),BigInt(args[2])));
case 786:return _teleport_trap_api_786(BigInt(args[0]),BigInt(args[1]));
case 787:return _teleport_trap_api_787(Number(args[0]),Number(args[1]),Number(args[2]),Number(args[3]));
case 788:return _teleport_trap_api_788(BigInt(args[0]),BigInt(args[1]));
case 789:return _teleport_trap_api_789(BigInt(args[0]));
case 790:return _teleport_trap_api_790(BigInt(args[0]));
case 791:return _teleport_trap_api_791(BigInt(args[0]),Number(args[1]));
case 792:return _teleport_trap_api_792(BigInt(args[0]));
case 793:return _teleport_trap_api_793(BigInt(args[0]));
case 794:return _teleport_trap_api_794(BigInt(args[0]));
case 795:return _teleport_trap_api_795(BigInt(args[0]),Number(args[1]));
case 796:return _teleport_trap_api_796(BigInt(args[0]),Number(args[1]));
case 797:return _teleport_trap_api_797(BigInt(args[0]),Number(args[1]));
case 798:return _teleport_trap_api_798(BigInt(args[0]));
case 799:return _teleport_trap_api_799(BigInt(args[0]),Number(args[1]));
case 800:return _teleport_trap_api_800(BigInt(args[0]),BigInt(args[1]),Number(args[2]));
case 801:return _teleport_trap_api_801(Number(args[0]));
case 802:return _teleport_trap_api_802(Number(args[0]),Number(args[1]));
case 803:return _teleport_trap_api_803(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 804:return Number(_teleport_trap_api_804(BigInt(args[0])));
case 805:return _teleport_trap_api_805(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]));
case 806:return _teleport_trap_api_806();
case 807:return _teleport_trap_api_807(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 808:return _teleport_trap_api_808(Number(args[0]));
case 809:return _teleport_trap_api_809(Number(args[0]));
case 810:return _teleport_trap_api_810(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 811:return _teleport_trap_api_811(BigInt(args[0]),Number(args[1]));
case 812:return _teleport_trap_api_812(BigInt(args[0]));
case 813:return Number(_teleport_trap_api_813(BigInt(args[0]),BigInt(args[1])));
case 814:return Number(_teleport_trap_api_814(BigInt(args[0]),BigInt(args[1])));
case 815:return _teleport_trap_api_815();
case 816:return _teleport_trap_api_816(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 817:return _teleport_trap_api_817(Number(args[0]));
case 818:return _teleport_trap_api_818(Number(args[0]));
case 819:return _teleport_trap_api_819();
case 820:return _teleport_trap_api_820(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 821:return _teleport_trap_api_821(Number(args[0]));
case 822:return _teleport_trap_api_822(Number(args[0]));
case 823:return _teleport_trap_api_823(BigInt(args[0]));
case 824:return _teleport_trap_api_824(BigInt(args[0]));
case 825:return _teleport_trap_api_825(BigInt(args[0]),Number(args[1]));
case 826:return _teleport_trap_api_826();
case 827:return _teleport_trap_api_827(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 828:return _teleport_trap_api_828(Number(args[0]));
case 829:return _teleport_trap_api_829(Number(args[0]));
case 830:return _teleport_trap_api_830(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 831:return Number(_teleport_trap_api_831(BigInt(args[0])));
case 832:return _teleport_trap_api_832(BigInt(args[0]),BigInt(args[1]));
case 833:return _teleport_trap_api_833();
case 834:return _teleport_trap_api_834(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 835:return _teleport_trap_api_835(Number(args[0]));
case 836:return _teleport_trap_api_836(Number(args[0]));
case 837:return _teleport_trap_api_837();
case 838:return _teleport_trap_api_838(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 839:return _teleport_trap_api_839(Number(args[0]));
case 840:return _teleport_trap_api_840(Number(args[0]));
case 841:return _teleport_trap_api_841(BigInt(args[0]));
case 842:return _teleport_trap_api_842(BigInt(args[0]),Number(args[1]),Number(args[2]),Number(args[3]));
case 843:return _teleport_trap_api_843(BigInt(args[0]),BigInt(args[1]),Number(args[2]));
case 844:return _teleport_trap_api_844(Number(args[0]));
case 845:return _teleport_trap_api_845(Number(args[0]),Number(args[1]),Number(args[2]),Number(args[3]),BigInt(args[4]));
case 846:return _teleport_trap_api_846(Number(args[0]),Number(args[1]));
case 847:return _teleport_trap_api_847(Number(args[0]),Number(args[1]),Number(args[2]));
case 848:return _teleport_trap_api_848(Number(args[0]),Number(args[1]));
case 849:return _teleport_trap_api_849(BigInt(args[0]),BigInt(args[1]));
case 850:return _teleport_trap_api_850(Number(args[0]),Number(args[1]));
case 851:return _teleport_trap_api_851(BigInt(args[0]),BigInt(args[1]));
case 852:return _teleport_trap_api_852(BigInt(args[0]),BigInt(args[1]));
case 853:return _teleport_trap_api_853(Number(args[0]),Number(args[1]),Number(args[2]));
case 854:return _teleport_trap_api_854(Number(args[0]),Number(args[1]),Number(args[2]),BigInt(args[3]),BigInt(args[4]));
case 855:return _teleport_trap_api_855(Number(args[0]),Number(args[1]));
case 856:return _teleport_trap_api_856(Number(args[0]),Number(args[1]));
case 857:return _teleport_trap_api_857(Number(args[0]),Number(args[1]),Number(args[2]));
case 858:return _teleport_trap_api_858(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 859:return Number(_teleport_trap_api_859(Number(args[0]),Number(args[1]),Number(args[2])));
case 860:return Number(_teleport_trap_api_860(Number(args[0]),Number(args[1]),Number(args[2])));
case 861:return _teleport_trap_api_861(BigInt(args[0]));
case 862:return _teleport_trap_api_862(Number(args[0]),Number(args[1]));
case 863:return Number(_teleport_trap_api_863(BigInt(args[0]),BigInt(args[1])));
case 864:return _teleport_trap_api_864(BigInt(args[0]));
case 865:return _teleport_trap_api_865(Number(args[0]),Number(args[1]));
case 866:return Number(_teleport_trap_api_866(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 867:return _teleport_trap_api_867(Number(args[0]),Number(args[1]),Number(args[2]),Number(args[3]));
case 868:return _teleport_trap_api_868(Number(args[0]));
case 869:return _teleport_trap_api_869(Number(args[0]));
case 870:return Number(_teleport_trap_api_870(BigInt(args[0])));
case 871:return Number(_teleport_trap_api_871(BigInt(args[0])));
case 872:return _teleport_trap_api_872(BigInt(args[0]),BigInt(args[1]));
case 873:return _teleport_trap_api_873(BigInt(args[0]));
case 874:return _teleport_trap_api_874(Number(args[0]),Number(args[1]),Number(args[2]),Number(args[3]));
case 875:return _teleport_trap_api_875(BigInt(args[0]),BigInt(args[1]));
case 876:return _teleport_trap_api_876();
case 878:return _teleport_trap_api_878(Number(args[0]));
case 881:return _teleport_trap_api_881(Number(args[0]),Number(args[1]));
case 882:return _teleport_trap_api_882(Number(args[0]),Number(args[1]));
case 883:return _teleport_trap_api_883(Number(args[0]),Number(args[1]));
case 885:return _teleport_trap_api_885(Number(args[0]),Number(args[1]));
case 886:return _teleport_trap_api_886();
case 887:return _teleport_trap_api_887(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 888:return _teleport_trap_api_888(Number(args[0]));
case 889:return _teleport_trap_api_889(Number(args[0]));
case 890:return Number(_teleport_trap_api_890(BigInt(args[0])));
case 891:return _teleport_trap_api_891(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 892:return _teleport_trap_api_892(BigInt(args[0]),BigInt(args[1]));
case 893:return _teleport_trap_api_893(BigInt(args[0]),BigInt(args[1]),Number(args[2]),Number(args[3]));
case 894:return _teleport_trap_api_894(BigInt(args[0]),BigInt(args[1]));
case 895:return _teleport_trap_api_895(Number(args[0]));
case 896:return _teleport_trap_api_896(Number(args[0]),Number(args[1]),BigInt(args[2]),BigInt(args[3]));
case 897:return _teleport_trap_api_897();
case 898:return _teleport_trap_api_898(Number(args[0]),Number(args[1]));
case 899:return _teleport_trap_api_899(BigInt(args[0]),Number(args[1]),Number(args[2]),Number(args[3]));
case 900:return _teleport_trap_api_900();
case 901:return _teleport_trap_api_901(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 902:return _teleport_trap_api_902(Number(args[0]));
case 903:return _teleport_trap_api_903(Number(args[0]));
case 904:return _teleport_trap_api_904(Number(args[0]),Number(args[1]));
case 905:return _teleport_trap_api_905(BigInt(args[0]),BigInt(args[1]));
case 906:return _teleport_trap_api_906(Number(args[0]),Number(args[1]));
case 907:return _teleport_trap_api_907(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 908:return _teleport_trap_api_908(BigInt(args[0]));
case 909:return _teleport_trap_api_909(Number(args[0]),Number(args[1]),Number(args[2]),Number(args[3]),BigInt(args[4]));
case 910:return _teleport_trap_api_910(Number(args[0]),Number(args[1]));
case 911:return _teleport_trap_api_911();
case 912:return _teleport_trap_api_912(BigInt(args[0]));
case 913:return _teleport_trap_api_913(Number(args[0]),Number(args[1]),BigInt(args[2]));
case 914:return _teleport_trap_api_914(BigInt(args[0]));
case 915:return _teleport_trap_api_915(BigInt(args[0]));
case 916:return _teleport_trap_api_916(BigInt(args[0]));
case 917:return _teleport_trap_api_917(BigInt(args[0]),Number(args[1]));
case 918:return _teleport_trap_api_918(BigInt(args[0]),Number(args[1]),Number(args[2]),BigInt(args[3]));
case 919:return _teleport_trap_api_919(BigInt(args[0]),Number(args[1]),Number(args[2]),BigInt(args[3]));
case 920:return Number(_teleport_trap_api_920(Number(args[0]),Number(args[1]),Number(args[2])));
case 921:return _teleport_trap_api_921(Number(args[0]),Number(args[1]));
case 922:return _teleport_trap_api_922(BigInt(args[0]),BigInt(args[1]));
case 923:return _teleport_trap_api_923(BigInt(args[0]));
case 924:return _teleport_trap_api_924(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 925:return _teleport_trap_api_925(Number(args[0]),Number(args[1]),Number(args[2]));
case 926:return _teleport_trap_api_926(Number(args[0]),Number(args[1]));
case 927:return _teleport_trap_api_927(Number(args[0]),Number(args[1]));
case 928:return _teleport_trap_api_928(BigInt(args[0]));
case 929:return _teleport_trap_api_929(Number(args[0]),Number(args[1]));
case 930:return _teleport_trap_api_930(Number(args[0]),Number(args[1]));
case 931:return _teleport_trap_api_931();
case 932:return _teleport_trap_api_932(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 933:return _teleport_trap_api_933(Number(args[0]));
case 934:return _teleport_trap_api_934(Number(args[0]));
case 935:return _teleport_trap_api_935(BigInt(args[0]),Number(args[1]),Number(args[2]),Number(args[3]),Number(args[4]),Number(args[5]),Number(args[6]));
case 936:return _teleport_trap_api_936(BigInt(args[0]));
case 937:return _teleport_trap_api_937(Number(args[0]),Number(args[1]),Number(args[2]));
case 938:return _teleport_trap_api_938(Number(args[0]),Number(args[1]));
case 939:return _teleport_trap_api_939(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 940:return _teleport_trap_api_940(Number(args[0]),Number(args[1]));
case 941:return _teleport_trap_api_941(Number(args[0]),Number(args[1]));
case 942:return _teleport_trap_api_942(BigInt(args[0]),Number(args[1]));
case 943:return _teleport_trap_api_943(Number(args[0]),Number(args[1]));
case 944:return _teleport_trap_api_944(Number(args[0]),Number(args[1]));
case 945:return _teleport_trap_api_945(Number(args[0]),Number(args[1]),Number(args[2]),Number(args[3]),Number(args[4]));
case 946:return _teleport_trap_api_946();
case 947:return _teleport_trap_api_947(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 948:return _teleport_trap_api_948(Number(args[0]));
case 949:return _teleport_trap_api_949(Number(args[0]));
case 950:return _teleport_trap_api_950();
case 951:return _teleport_trap_api_951(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 952:return _teleport_trap_api_952(Number(args[0]));
case 953:return _teleport_trap_api_953(Number(args[0]));
case 954:return _teleport_trap_api_954(Number(args[0]),Number(args[1]));
case 955:return Number(_teleport_trap_api_955(Number(args[0]),Number(args[1]),Number(args[2])));
case 956:return _teleport_trap_api_956(BigInt(args[0]));
case 957:return _teleport_trap_api_957(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 958:return _teleport_trap_api_958(BigInt(args[0]));
case 959:return _teleport_trap_api_959(Number(args[0]),Number(args[1]));
case 960:return _teleport_trap_api_960(Number(args[0]),Number(args[1]));
case 961:return _teleport_trap_api_961(Number(args[0]),Number(args[1]));
case 962:return _teleport_trap_api_962(BigInt(args[0]));
case 963:return _teleport_trap_api_963();
case 964:return _teleport_trap_api_964(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 965:return _teleport_trap_api_965(Number(args[0]));
case 966:return _teleport_trap_api_966(Number(args[0]));
case 967:return Number(_teleport_trap_api_967(Number(args[0]),Number(args[1]),Number(args[2])));
case 968:return _teleport_trap_api_968();
case 969:return _teleport_trap_api_969(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 970:return _teleport_trap_api_970(Number(args[0]));
case 971:return _teleport_trap_api_971(Number(args[0]));
case 972:return _teleport_trap_api_972(BigInt(args[0]));
case 973:return Number(_teleport_trap_api_973(BigInt(args[0])));
case 974:return _teleport_trap_api_974(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 975:return _teleport_trap_api_975(BigInt(args[0]));
case 976:return _teleport_trap_api_976(Number(args[0]),Number(args[1]));
case 977:return Number(_teleport_trap_api_977(BigInt(args[0])));
case 978:return _teleport_trap_api_978(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 979:return Number(_teleport_trap_api_979(BigInt(args[0])));
case 980:return _teleport_trap_api_980(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 981:return _teleport_trap_api_981(BigInt(args[0]));
case 982:return Number(_teleport_trap_api_982(BigInt(args[0])));
case 983:return _teleport_trap_api_983(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 984:return _teleport_trap_api_984(BigInt(args[0]));
case 985:return Number(_teleport_trap_api_985(BigInt(args[0])));
case 986:return _teleport_trap_api_986(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 987:return _teleport_trap_api_987(BigInt(args[0]),Number(args[1]));
case 988:return _teleport_trap_api_988(Number(args[0]),Number(args[1]));
case 989:return _teleport_trap_api_989();
case 990:return _teleport_trap_api_990(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 991:return _teleport_trap_api_991(Number(args[0]));
case 992:return _teleport_trap_api_992(Number(args[0]));
case 993:return _teleport_trap_api_993(BigInt(args[0]),Number(args[1]));
case 994:return _teleport_trap_api_994(BigInt(args[0]));
case 995:return _teleport_trap_api_995();
case 996:return _teleport_trap_api_996(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 997:return _teleport_trap_api_997(Number(args[0]));
case 998:return _teleport_trap_api_998(Number(args[0]));
case 999:return _teleport_trap_api_999(BigInt(args[0]),Number(args[1]));
case 1000:return _teleport_trap_api_1000(BigInt(args[0]));
case 1001:return _teleport_trap_api_1001(BigInt(args[0]));
case 1002:return _teleport_trap_api_1002(Number(args[0]),Number(args[1]));
case 1003:return _teleport_trap_api_1003(BigInt(args[0]));
case 1004:return Number(_teleport_trap_api_1004(BigInt(args[0])));
case 1005:return _teleport_trap_api_1005(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1006:return _teleport_trap_api_1006(BigInt(args[0]));
case 1007:return _teleport_trap_api_1007(Number(args[0]));
case 1008:return _teleport_trap_api_1008(BigInt(args[0]));
case 1009:return Number(_teleport_trap_api_1009(BigInt(args[0]),BigInt(args[1])));
case 1010:return _teleport_trap_api_1010(Number(args[0]));
case 1011:return _teleport_trap_api_1011(BigInt(args[0]),Number(args[1]));
case 1012:return _teleport_trap_api_1012(BigInt(args[0]));
case 1013:return _teleport_trap_api_1013(BigInt(args[0]));
case 1014:return _teleport_trap_api_1014(BigInt(args[0]));
case 1015:return _teleport_trap_api_1015(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1016:return Number(_teleport_trap_api_1016(BigInt(args[0])));
case 1017:return _teleport_trap_api_1017(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1018:return _teleport_trap_api_1018(BigInt(args[0]),Number(args[1]));
case 1019:return _teleport_trap_api_1019(BigInt(args[0]));
case 1020:return Number(_teleport_trap_api_1020(BigInt(args[0])));
case 1021:return _teleport_trap_api_1021(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1022:return Number(_teleport_trap_api_1022(BigInt(args[0])));
case 1023:return _teleport_trap_api_1023(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1024:return _teleport_trap_api_1024();
case 1025:return Number(_teleport_trap_api_1025(BigInt(args[0])));
case 1026:return _teleport_trap_api_1026(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1027:return Number(_teleport_trap_api_1027(BigInt(args[0])));
case 1028:return _teleport_trap_api_1028(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1029:return _teleport_trap_api_1029();
case 1030:return _teleport_trap_api_1030(BigInt(args[0]),Number(args[1]));
case 1031:return Number(_teleport_trap_api_1031(BigInt(args[0])));
case 1032:return Number(_teleport_trap_api_1032(BigInt(args[0])));
case 1033:return Number(_teleport_trap_api_1033(BigInt(args[0]),BigInt(args[1]),Number(args[2])));
case 1034:return _teleport_trap_api_1034(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]),BigInt(args[4]));
case 1035:return Number(_teleport_trap_api_1035(BigInt(args[0]),BigInt(args[1])));
case 1036:return _teleport_trap_api_1036(BigInt(args[0]),Number(args[1]));
case 1037:return _teleport_trap_api_1037(BigInt(args[0]));
case 1038:return _teleport_trap_api_1038(BigInt(args[0]),BigInt(args[1]));
case 1039:return Number(_teleport_trap_api_1039(Number(args[0])));
case 1040:return Number(_teleport_trap_api_1040(BigInt(args[0])));
case 1041:return _teleport_trap_api_1041(BigInt(args[0]),BigInt(args[1]));
case 1042:return Number(_teleport_trap_api_1042(BigInt(args[0])));
case 1043:return Number(_teleport_trap_api_1043(Number(args[0])));
case 1044:return _teleport_trap_api_1044(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1045:return _teleport_trap_api_1045(BigInt(args[0]),BigInt(args[1]));
case 1046:return Number(_teleport_trap_api_1046(Number(args[0])));
case 1047:return _teleport_trap_api_1047(BigInt(args[0]),BigInt(args[1]));
case 1048:return _teleport_trap_api_1048(Number(args[0]));
case 1049:return Number(_teleport_trap_api_1049(Number(args[0]),Number(args[1])));
case 1050:return _teleport_trap_api_1050(BigInt(args[0]),BigInt(args[1]));
case 1051:return Number(_teleport_trap_api_1051(BigInt(args[0])));
case 1052:return _teleport_trap_api_1052(BigInt(args[0]),BigInt(args[1]));
case 1053:return _teleport_trap_api_1053(BigInt(args[0]));
case 1054:return _teleport_trap_api_1054(BigInt(args[0]),BigInt(args[1]));
case 1055:return _teleport_trap_api_1055(BigInt(args[0]));
case 1056:return _teleport_trap_api_1056(BigInt(args[0]));
case 1057:return Number(_teleport_trap_api_1057(BigInt(args[0])));
case 1058:return _teleport_trap_api_1058(BigInt(args[0]),BigInt(args[1]));
case 1059:return Number(_teleport_trap_api_1059(BigInt(args[0])));
case 1060:return _teleport_trap_api_1060(BigInt(args[0]),BigInt(args[1]));
case 1061:return _teleport_trap_api_1061(Number(args[0]));
case 1062:return _teleport_trap_api_1062(BigInt(args[0]));
case 1063:return _teleport_trap_api_1063();
case 1064:return _teleport_trap_api_1064();
case 1065:return Number(_teleport_trap_api_1065(Number(args[0]),Number(args[1]),Number(args[2])));
case 1066:return _teleport_trap_api_1066(BigInt(args[0]));
case 1067:return _teleport_trap_api_1067(BigInt(args[0]),Number(args[1]),Number(args[2]),BigInt(args[3]));
case 1068:return _teleport_trap_api_1068();
case 1069:return _teleport_trap_api_1069(BigInt(args[0]),BigInt(args[1]));
case 1070:return _teleport_trap_api_1070();
case 1071:return _teleport_trap_api_1071(Number(args[0]));
case 1072:return _teleport_trap_api_1072();
case 1073:return _teleport_trap_api_1073(BigInt(args[0]));
case 1074:return _teleport_trap_api_1074();
case 1075:return Number(_teleport_trap_api_1075(BigInt(args[0]),Number(args[1]),Number(args[2])));
case 1076:return _teleport_trap_api_1076(BigInt(args[0]),BigInt(args[1]));
case 1077:return _teleport_trap_api_1077();
case 1078:return _teleport_trap_api_1078(Number(args[0]),Number(args[1]));
case 1079:return _teleport_trap_api_1079(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 1080:return _teleport_trap_api_1080(Number(args[0]),Number(args[1]));
case 1081:return _teleport_trap_api_1081(BigInt(args[0]));
case 1082:return Number(_teleport_trap_api_1082(BigInt(args[0])));
case 1083:return _teleport_trap_api_1083(BigInt(args[0]),BigInt(args[1]));
case 1084:return Number(_teleport_trap_api_1084(BigInt(args[0])));
case 1085:return _teleport_trap_api_1085(BigInt(args[0]),BigInt(args[1]));
case 1086:return _teleport_trap_api_1086(BigInt(args[0]));
case 1087:return _teleport_trap_api_1087(Number(args[0]),Number(args[1]));
case 1088:return _teleport_trap_api_1088(BigInt(args[0]),BigInt(args[1]));
case 1089:return _teleport_trap_api_1089(Number(args[0]),Number(args[1]));
case 1090:return _teleport_trap_api_1090(BigInt(args[0]),BigInt(args[1]));
case 1091:return _teleport_trap_api_1091(BigInt(args[0]));
case 1092:return _teleport_trap_api_1092(BigInt(args[0]),BigInt(args[1]));
case 1093:return _teleport_trap_api_1093(BigInt(args[0]));
case 1094:return _teleport_trap_api_1094(BigInt(args[0]));
case 1095:return _teleport_trap_api_1095(BigInt(args[0]));
case 1096:return _teleport_trap_api_1096();
case 1097:return _teleport_trap_api_1097(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1098:return _teleport_trap_api_1098(Number(args[0]));
case 1099:return _teleport_trap_api_1099(Number(args[0]));
case 1100:return _teleport_trap_api_1100(Number(args[0]),BigInt(args[1]),Number(args[2]));
case 1101:return _teleport_trap_api_1101(Number(args[0]));
case 1102:return _teleport_trap_api_1102(BigInt(args[0]));
case 1103:return _teleport_trap_api_1103(Number(args[0]),Number(args[1]));
case 1104:return _teleport_trap_api_1104(BigInt(args[0]),BigInt(args[1]));
case 1105:return Number(_teleport_trap_api_1105(Number(args[0]),Number(args[1])));
case 1106:return _teleport_trap_api_1106(BigInt(args[0]),BigInt(args[1]));
case 1107:return _teleport_trap_api_1107();
case 1108:return _teleport_trap_api_1108(BigInt(args[0]),BigInt(args[1]));
case 1109:return _teleport_trap_api_1109(BigInt(args[0]));
case 1110:return _teleport_trap_api_1110(BigInt(args[0]),BigInt(args[1]));
case 1111:return _teleport_trap_api_1111(BigInt(args[0]),BigInt(args[1]));
case 1112:return _teleport_trap_api_1112(BigInt(args[0]),BigInt(args[1]));
case 1113:return _teleport_trap_api_1113(Number(args[0]));
case 1114:return _teleport_trap_api_1114(BigInt(args[0]),BigInt(args[1]));
case 1115:return _teleport_trap_api_1115();
case 1116:return _teleport_trap_api_1116(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1117:return _teleport_trap_api_1117(Number(args[0]));
case 1118:return _teleport_trap_api_1118(Number(args[0]));
case 1119:return Number(_teleport_trap_api_1119(Number(args[0]),Number(args[1]),Number(args[2])));
case 1120:return Number(_teleport_trap_api_1120(Number(args[0])));
case 1121:return _teleport_trap_api_1121(BigInt(args[0]),BigInt(args[1]));
case 1124:return Number(_teleport_trap_api_1124(Number(args[0])));
case 1125:return _teleport_trap_api_1125(BigInt(args[0]),BigInt(args[1]));
case 1126:return Number(_teleport_trap_api_1126(BigInt(args[0])));
case 1127:return _teleport_trap_api_1127(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1128:return _teleport_trap_api_1128(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1129:return Number(_teleport_trap_api_1129(BigInt(args[0])));
case 1130:return _teleport_trap_api_1130(BigInt(args[0]),BigInt(args[1]));
case 1131:return _teleport_trap_api_1131();
case 1132:return _teleport_trap_api_1132(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1133:return _teleport_trap_api_1133(Number(args[0]));
case 1134:return _teleport_trap_api_1134(Number(args[0]));
case 1135:return _teleport_trap_api_1135(BigInt(args[0]));
case 1136:return _teleport_trap_api_1136();
case 1137:return _teleport_trap_api_1137(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1138:return _teleport_trap_api_1138(Number(args[0]),Number(args[1]));
case 1139:return _teleport_trap_api_1139(Number(args[0]),Number(args[1]));
case 1140:return _teleport_trap_api_1140(Number(args[0]),Number(args[1]));
case 1141:return Number(_teleport_trap_api_1141(BigInt(args[0])));
case 1142:return Number(_teleport_trap_api_1142(Number(args[0]),Number(args[1])));
case 1143:return Number(_teleport_trap_api_1143(BigInt(args[0])));
case 1144:return _teleport_trap_api_1144(BigInt(args[0]),BigInt(args[1]));
case 1145:return _teleport_trap_api_1145(BigInt(args[0]));
case 1146:return _teleport_trap_api_1146();
case 1147:return _teleport_trap_api_1147(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1148:return _teleport_trap_api_1148(Number(args[0]));
case 1149:return _teleport_trap_api_1149(Number(args[0]));
case 1150:return _teleport_trap_api_1150(Number(args[0]),BigInt(args[1]),Number(args[2]));
case 1151:return Number(_teleport_trap_api_1151(BigInt(args[0])));
case 1152:return Number(_teleport_trap_api_1152(Number(args[0]),Number(args[1])));
case 1153:return Number(_teleport_trap_api_1153(BigInt(args[0])));
case 1154:return _teleport_trap_api_1154(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]));
case 1155:return _teleport_trap_api_1155(Number(args[0]),Number(args[1]));
case 1156:return _teleport_trap_api_1156(BigInt(args[0]));
case 1157:return _teleport_trap_api_1157();
case 1158:return _teleport_trap_api_1158(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1159:return _teleport_trap_api_1159(Number(args[0]));
case 1160:return _teleport_trap_api_1160(Number(args[0]));
case 1161:return _teleport_trap_api_1161();
case 1162:return _teleport_trap_api_1162(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1163:return _teleport_trap_api_1163(Number(args[0]));
case 1164:return _teleport_trap_api_1164(Number(args[0]));
case 1165:return _teleport_trap_api_1165(BigInt(args[0]));
case 1166:return _teleport_trap_api_1166(Number(args[0]));
case 1167:return _teleport_trap_api_1167();
case 1168:return _teleport_trap_api_1168(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1169:return _teleport_trap_api_1169(Number(args[0]),Number(args[1]));
case 1170:return _teleport_trap_api_1170(Number(args[0]),Number(args[1]));
case 1171:return _teleport_trap_api_1171();
case 1172:return _teleport_trap_api_1172(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1173:return _teleport_trap_api_1173(Number(args[0]));
case 1174:return _teleport_trap_api_1174(Number(args[0]));
case 1175:return _teleport_trap_api_1175(Number(args[0]),Number(args[1]));
case 1176:return _teleport_trap_api_1176(BigInt(args[0]));
case 1177:return _teleport_trap_api_1177(BigInt(args[0]));
case 1178:return _teleport_trap_api_1178(BigInt(args[0]));
case 1179:return _teleport_trap_api_1179(Number(args[0]),BigInt(args[1]),Number(args[2]));
case 1180:return _teleport_trap_api_1180();
case 1181:return _teleport_trap_api_1181();
case 1182:return _teleport_trap_api_1182(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1183:return _teleport_trap_api_1183(Number(args[0]));
case 1184:return _teleport_trap_api_1184(Number(args[0]));
case 1185:return _teleport_trap_api_1185(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 1186:return _teleport_trap_api_1186(Number(args[0]),Number(args[1]),Number(args[2]),Number(args[3]));
case 1187:return _teleport_trap_api_1187(BigInt(args[0]));
case 1188:return _teleport_trap_api_1188(Number(args[0]),Number(args[1]));
case 1189:return _teleport_trap_api_1189(Number(args[0]),Number(args[1]),BigInt(args[2]));
case 1190:return _teleport_trap_api_1190();
case 1191:return _teleport_trap_api_1191(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1192:return _teleport_trap_api_1192(Number(args[0]));
case 1193:return _teleport_trap_api_1193(Number(args[0]));
case 1194:return _teleport_trap_api_1194();
case 1195:return _teleport_trap_api_1195(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1196:return _teleport_trap_api_1196(Number(args[0]));
case 1197:return _teleport_trap_api_1197(Number(args[0]));
case 1198:return _teleport_trap_api_1198(BigInt(args[0]));
case 1199:return _teleport_trap_api_1199(BigInt(args[0]));
case 1200:return _teleport_trap_api_1200();
case 1201:return _teleport_trap_api_1201(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1202:return _teleport_trap_api_1202(Number(args[0]));
case 1203:return _teleport_trap_api_1203(Number(args[0]));
case 1204:return _teleport_trap_api_1204(BigInt(args[0]),Number(args[1]));
case 1205:return _teleport_trap_api_1205(BigInt(args[0]),BigInt(args[1]));
case 1206:return _teleport_trap_api_1206(BigInt(args[0]));
case 1207:return _teleport_trap_api_1207(BigInt(args[0]));
case 1208:return _teleport_trap_api_1208();
case 1209:return _teleport_trap_api_1209(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1210:return _teleport_trap_api_1210(Number(args[0]));
case 1211:return _teleport_trap_api_1211(Number(args[0]));
case 1212:return _teleport_trap_api_1212(BigInt(args[0]),Number(args[1]));
case 1213:return _teleport_trap_api_1213(BigInt(args[0]));
case 1214:return _teleport_trap_api_1214();
case 1215:return _teleport_trap_api_1215(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1216:return _teleport_trap_api_1216(Number(args[0]));
case 1217:return _teleport_trap_api_1217(Number(args[0]));
case 1218:return _teleport_trap_api_1218(BigInt(args[0]),Number(args[1]));
case 1219:return Number(_teleport_trap_api_1219(BigInt(args[0]),Number(args[1]),Number(args[2]),Number(args[3])));
case 1220:return _teleport_trap_api_1220(Number(args[0]),Number(args[1]),Number(args[2]));
case 1221:return _teleport_trap_api_1221(BigInt(args[0]));
case 1222:return _teleport_trap_api_1222();
case 1223:return _teleport_trap_api_1223(BigInt(args[0]));
case 1224:return _teleport_trap_api_1224(BigInt(args[0]));
case 1225:return _teleport_trap_api_1225(BigInt(args[0]),BigInt(args[1]));
case 1226:return _teleport_trap_api_1226(Number(args[0]),Number(args[1]));
case 1227:return Number(_teleport_trap_api_1227(Number(args[0])));
case 1228:return _teleport_trap_api_1228(BigInt(args[0]),BigInt(args[1]));
case 1229:return _teleport_trap_api_1229(BigInt(args[0]));
case 1230:return _teleport_trap_api_1230(BigInt(args[0]),BigInt(args[1]));
case 1231:return _teleport_trap_api_1231(BigInt(args[0]),BigInt(args[1]));
case 1232:return _teleport_trap_api_1232(BigInt(args[0]));
case 1233:return _teleport_trap_api_1233(BigInt(args[0]));
case 1234:return _teleport_trap_api_1234(BigInt(args[0]),BigInt(args[1]));
case 1235:return _teleport_trap_api_1235(BigInt(args[0]));
case 1236:return _teleport_trap_api_1236(BigInt(args[0]));
case 1237:return _teleport_trap_api_1237(BigInt(args[0]));
case 1238:return _teleport_trap_api_1238(Number(args[0]),Number(args[1]),Number(args[2]));
case 1239:return _teleport_trap_api_1239(Number(args[0]),Number(args[1]));
case 1240:return _teleport_trap_api_1240(BigInt(args[0]),BigInt(args[1]),Number(args[2]));
case 1241:return _teleport_trap_api_1241(BigInt(args[0]));
case 1242:return _teleport_trap_api_1242(BigInt(args[0]));
case 1243:return _teleport_trap_api_1243();
case 1244:return _teleport_trap_api_1244(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1245:return _teleport_trap_api_1245(Number(args[0]));
case 1246:return _teleport_trap_api_1246(Number(args[0]));
case 1247:return Number(_teleport_trap_api_1247(BigInt(args[0])));
case 1248:return _teleport_trap_api_1248(BigInt(args[0]),BigInt(args[1]));
case 1249:return _teleport_trap_api_1249(BigInt(args[0]));
case 1250:return _teleport_trap_api_1250(BigInt(args[0]));
case 1251:return _teleport_trap_api_1251(BigInt(args[0]),Number(args[1]),Number(args[2]),BigInt(args[3]));
case 1252:return _teleport_trap_api_1252(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 1253:return _teleport_trap_api_1253(BigInt(args[0]));
case 1254:return _teleport_trap_api_1254(BigInt(args[0]));
case 1255:return _teleport_trap_api_1255();
case 1256:return _teleport_trap_api_1256(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1257:return _teleport_trap_api_1257(Number(args[0]));
case 1258:return _teleport_trap_api_1258(Number(args[0]));
case 1259:return Number(_teleport_trap_api_1259(BigInt(args[0])));
case 1260:return Number(_teleport_trap_api_1260(BigInt(args[0])));
case 1261:return _teleport_trap_api_1261(BigInt(args[0]),BigInt(args[1]));
case 1262:return Number(_teleport_trap_api_1262(BigInt(args[0])));
case 1263:return _teleport_trap_api_1263(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1264:return _teleport_trap_api_1264(BigInt(args[0]));
case 1265:return _teleport_trap_api_1265(BigInt(args[0]));
case 1266:return Number(_teleport_trap_api_1266(BigInt(args[0])));
case 1267:return _teleport_trap_api_1267(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1268:return _teleport_trap_api_1268(BigInt(args[0]));
case 1269:return _teleport_trap_api_1269(BigInt(args[0]));
case 1270:return _teleport_trap_api_1270(BigInt(args[0]));
case 1271:return _teleport_trap_api_1271(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 1272:return _teleport_trap_api_1272(Number(args[0]));
case 1273:return Number(_teleport_trap_api_1273(BigInt(args[0]),BigInt(args[1])));
case 1274:return _teleport_trap_api_1274(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1275:return Number(_teleport_trap_api_1275(BigInt(args[0])));
case 1276:return _teleport_trap_api_1276(BigInt(args[0]),BigInt(args[1]));
case 1277:return _teleport_trap_api_1277(BigInt(args[0]),Number(args[1]));
case 1278:return _teleport_trap_api_1278(BigInt(args[0]));
case 1279:return _teleport_trap_api_1279(BigInt(args[0]));
case 1280:return _teleport_trap_api_1280(BigInt(args[0]));
case 1281:return _teleport_trap_api_1281(Number(args[0]));
case 1282:return Number(_teleport_trap_api_1282(BigInt(args[0]),BigInt(args[1])));
case 1283:return _teleport_trap_api_1283(BigInt(args[0]),BigInt(args[1]));
case 1284:return Number(_teleport_trap_api_1284(BigInt(args[0])));
case 1285:return Number(_teleport_trap_api_1285(BigInt(args[0])));
case 1286:return Number(_teleport_trap_api_1286(BigInt(args[0]),BigInt(args[1])));
case 1287:return _teleport_trap_api_1287(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1288:return Number(_teleport_trap_api_1288(BigInt(args[0]),BigInt(args[1])));
case 1289:return _teleport_trap_api_1289(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1290:return Number(_teleport_trap_api_1290(BigInt(args[0])));
case 1291:return Number(_teleport_trap_api_1291(BigInt(args[0]),BigInt(args[1])));
case 1292:return _teleport_trap_api_1292(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]));
case 1293:return _teleport_trap_api_1293(BigInt(args[0]));
case 1294:return _teleport_trap_api_1294(BigInt(args[0]));
case 1295:return _teleport_trap_api_1295();
case 1296:return _teleport_trap_api_1296(BigInt(args[0]));
case 1297:return Number(_teleport_trap_api_1297(BigInt(args[0])));
case 1298:return _teleport_trap_api_1298();
case 1299:return _teleport_trap_api_1299(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1300:return _teleport_trap_api_1300(Number(args[0]));
case 1301:return _teleport_trap_api_1301(Number(args[0]));
case 1302:return _teleport_trap_api_1302(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 1303:return _teleport_trap_api_1303();
case 1304:return _teleport_trap_api_1304(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1305:return _teleport_trap_api_1305(Number(args[0]));
case 1306:return _teleport_trap_api_1306(Number(args[0]));
case 1307:return Number(_teleport_trap_api_1307(BigInt(args[0])));
case 1308:return _teleport_trap_api_1308(BigInt(args[0]),BigInt(args[1]));
case 1309:return _teleport_trap_api_1309();
case 1310:return _teleport_trap_api_1310();
case 1311:return _teleport_trap_api_1311(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1312:return _teleport_trap_api_1312(Number(args[0]));
case 1313:return _teleport_trap_api_1313(Number(args[0]));
case 1314:return Number(_teleport_trap_api_1314(BigInt(args[0])));
case 1315:return _teleport_trap_api_1315(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1316:return Number(_teleport_trap_api_1316(BigInt(args[0])));
case 1317:return _teleport_trap_api_1317(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1318:return _teleport_trap_api_1318(Number(args[0]),Number(args[1]),Number(args[2]),Number(args[3]));
case 1319:return _teleport_trap_api_1319();
case 1320:return _teleport_trap_api_1320(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1321:return _teleport_trap_api_1321(Number(args[0]));
case 1322:return _teleport_trap_api_1322(Number(args[0]));
case 1323:return Number(_teleport_trap_api_1323(BigInt(args[0]),BigInt(args[1])));
case 1324:return _teleport_trap_api_1324(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1325:return _teleport_trap_api_1325();
case 1326:return _teleport_trap_api_1326(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),Number(args[3]));
case 1327:return _teleport_trap_api_1327(Number(args[0]),Number(args[1]));
case 1328:return Number(_teleport_trap_api_1328(BigInt(args[0])));
case 1329:return Number(_teleport_trap_api_1329(BigInt(args[0])));
case 1330:return _teleport_trap_api_1330(BigInt(args[0]),BigInt(args[1]));
case 1331:return Number(_teleport_trap_api_1331(BigInt(args[0]),BigInt(args[1])));
case 1332:return _teleport_trap_api_1332(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1333:return _teleport_trap_api_1333();
case 1334:return _teleport_trap_api_1334(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1335:return _teleport_trap_api_1335(Number(args[0]));
case 1336:return _teleport_trap_api_1336(Number(args[0]));
case 1337:return _teleport_trap_api_1337(BigInt(args[0]));
case 1338:return _teleport_trap_api_1338();
case 1339:return Number(_teleport_trap_api_1339(BigInt(args[0]),BigInt(args[1])));
case 1340:return _teleport_trap_api_1340(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1341:return _teleport_trap_api_1341();
case 1342:return Number(_teleport_trap_api_1342(BigInt(args[0]),BigInt(args[1])));
case 1343:return _teleport_trap_api_1343(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1344:return _teleport_trap_api_1344();
case 1345:return _teleport_trap_api_1345(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),Number(args[3]));
case 1346:return _teleport_trap_api_1346(Number(args[0]));
case 1347:return _teleport_trap_api_1347();
case 1348:return _teleport_trap_api_1348();
case 1349:return _teleport_trap_api_1349(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1350:return _teleport_trap_api_1350(Number(args[0]));
case 1351:return _teleport_trap_api_1351(Number(args[0]));
case 1352:return _teleport_trap_api_1352(BigInt(args[0]));
case 1353:return _teleport_trap_api_1353(BigInt(args[0]),Number(args[1]));
case 1354:return _teleport_trap_api_1354(BigInt(args[0]));
case 1355:return _teleport_trap_api_1355();
case 1356:return _teleport_trap_api_1356(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1357:return _teleport_trap_api_1357(Number(args[0]));
case 1358:return _teleport_trap_api_1358(Number(args[0]));
case 1359:return _teleport_trap_api_1359(Number(args[0]),Number(args[1]));
case 1360:return _teleport_trap_api_1360(Number(args[0]),Number(args[1]),BigInt(args[2]),Number(args[3]));
case 1361:return Number(_teleport_trap_api_1361(Number(args[0]),Number(args[1])));
case 1362:return _teleport_trap_api_1362(Number(args[0]),Number(args[1]));
case 1363:return Number(_teleport_trap_api_1363(Number(args[0]),Number(args[1]),BigInt(args[2])));
case 1364:return _teleport_trap_api_1364(BigInt(args[0]),BigInt(args[1]),Number(args[2]));
case 1365:return _teleport_trap_api_1365(BigInt(args[0]),BigInt(args[1]),Number(args[2]));
case 1366:return _teleport_trap_api_1366(BigInt(args[0]),BigInt(args[1]),Number(args[2]));
case 1367:return _teleport_trap_api_1367(BigInt(args[0]),BigInt(args[1]),Number(args[2]));
case 1368:return _teleport_trap_api_1368(BigInt(args[0]),BigInt(args[1]),Number(args[2]));
case 1369:return Number(_teleport_trap_api_1369(BigInt(args[0])));
case 1370:return _teleport_trap_api_1370(BigInt(args[0]),BigInt(args[1]),Number(args[2]));
case 1371:return _teleport_trap_api_1371(BigInt(args[0]),BigInt(args[1]),Number(args[2]));
case 1372:return _teleport_trap_api_1372(BigInt(args[0]),BigInt(args[1]),Number(args[2]));
case 1373:return Number(_teleport_trap_api_1373(BigInt(args[0])));
case 1374:return _teleport_trap_api_1374(BigInt(args[0]),BigInt(args[1]));
case 1375:return Number(_teleport_trap_api_1375(BigInt(args[0])));
case 1376:return Number(_teleport_trap_api_1376(BigInt(args[0])));
case 1377:return _teleport_trap_api_1377(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]));
case 1378:return _teleport_trap_api_1378(Number(args[0]),Number(args[1]));
case 1379:return _teleport_trap_api_1379(BigInt(args[0]),BigInt(args[1]));
case 1380:return Number(_teleport_trap_api_1380(BigInt(args[0])));
case 1381:return _teleport_trap_api_1381(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]));
case 1382:return _teleport_trap_api_1382(BigInt(args[0]),BigInt(args[1]));
case 1383:return _teleport_trap_api_1383(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1384:return _teleport_trap_api_1384(Number(args[0]),Number(args[1]));
case 1385:return Number(_teleport_trap_api_1385(BigInt(args[0])));
case 1386:return _teleport_trap_api_1386(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]));
case 1387:return _teleport_trap_api_1387(Number(args[0]),Number(args[1]));
case 1388:return Number(_teleport_trap_api_1388(BigInt(args[0])));
case 1389:return _teleport_trap_api_1389(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1390:return _teleport_trap_api_1390(Number(args[0]),Number(args[1]));
case 1391:return _teleport_trap_api_1391(Number(args[0]),Number(args[1]));
case 1392:return _teleport_trap_api_1392(Number(args[0]),Number(args[1]));
case 1393:return _teleport_trap_api_1393(Number(args[0]),Number(args[1]));
case 1394:return _teleport_trap_api_1394();
case 1395:return _teleport_trap_api_1395(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1396:return _teleport_trap_api_1396(Number(args[0]));
case 1397:return _teleport_trap_api_1397(Number(args[0]));
case 1398:return Number(_teleport_trap_api_1398(Number(args[0]),Number(args[1])));
case 1399:return _teleport_trap_api_1399(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),Number(args[3]));
case 1400:return _teleport_trap_api_1400(BigInt(args[0]),BigInt(args[1]));
case 1401:return _teleport_trap_api_1401();
case 1402:return _teleport_trap_api_1402(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1403:return _teleport_trap_api_1403(Number(args[0]));
case 1404:return _teleport_trap_api_1404(Number(args[0]));
case 1405:return Number(_teleport_trap_api_1405(BigInt(args[0]),BigInt(args[1])));
case 1406:return _teleport_trap_api_1406(BigInt(args[0]));
case 1407:return _teleport_trap_api_1407();
case 1408:return _teleport_trap_api_1408(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1409:return _teleport_trap_api_1409(Number(args[0]),Number(args[1]));
case 1410:return _teleport_trap_api_1410(Number(args[0]),Number(args[1]));
case 1411:return _teleport_trap_api_1411();
case 1412:return _teleport_trap_api_1412(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1413:return _teleport_trap_api_1413(Number(args[0]),Number(args[1]));
case 1414:return _teleport_trap_api_1414(Number(args[0]),Number(args[1]));
case 1415:return _teleport_trap_api_1415(Number(args[0]),BigInt(args[1]),Number(args[2]));
case 1416:return _teleport_trap_api_1416();
case 1417:return _teleport_trap_api_1417(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1418:return _teleport_trap_api_1418();
case 1419:return _teleport_trap_api_1419(BigInt(args[0]));
case 1420:return _teleport_trap_api_1420(BigInt(args[0]),BigInt(args[1]));
case 1421:return _teleport_trap_api_1421(BigInt(args[0]));
case 1422:return _teleport_trap_api_1422(BigInt(args[0]));
case 1423:return _teleport_trap_api_1423();
case 1424:return _teleport_trap_api_1424();
case 1425:return _teleport_trap_api_1425(Number(args[0]));
case 1426:return _teleport_trap_api_1426(Number(args[0]));
case 1427:return _teleport_trap_api_1427(Number(args[0]));
case 1428:return _teleport_trap_api_1428();
case 1429:return _teleport_trap_api_1429();
case 1430:return _teleport_trap_api_1430(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1431:return _teleport_trap_api_1431(Number(args[0]));
case 1432:return _teleport_trap_api_1432(Number(args[0]));
case 1433:return _teleport_trap_api_1433(BigInt(args[0]));
case 1434:return _teleport_trap_api_1434(BigInt(args[0]));
case 1435:return _teleport_trap_api_1435(Number(args[0]));
case 1436:return _teleport_trap_api_1436(Number(args[0]),Number(args[1]));
case 1437:return _teleport_trap_api_1437(BigInt(args[0]));
case 1438:return _teleport_trap_api_1438(Number(args[0]));
case 1439:return _teleport_trap_api_1439(Number(args[0]),Number(args[1]));
case 1440:return _teleport_trap_api_1440(BigInt(args[0]));
case 1441:return _teleport_trap_api_1441();
case 1442:return _teleport_trap_api_1442();
case 1443:return _teleport_trap_api_1443(BigInt(args[0]),BigInt(args[1]));
case 1444:return Number(_teleport_trap_api_1444(BigInt(args[0])));
case 1445:return _teleport_trap_api_1445(BigInt(args[0]),BigInt(args[1]));
case 1446:return _teleport_trap_api_1446(BigInt(args[0]));
case 1447:return _teleport_trap_api_1447(BigInt(args[0]));
case 1448:return _teleport_trap_api_1448(Number(args[0]),Number(args[1]),Number(args[2]));
case 1449:return _teleport_trap_api_1449(BigInt(args[0]));
case 1450:return _teleport_trap_api_1450(Number(args[0]));
case 1451:return _teleport_trap_api_1451(BigInt(args[0]));
case 1452:return Number(_teleport_trap_api_1452(Number(args[0]),Number(args[1])));
case 1453:return _teleport_trap_api_1453(BigInt(args[0]),BigInt(args[1]));
case 1454:return _teleport_trap_api_1454(BigInt(args[0]),BigInt(args[1]));
case 1455:return Number(_teleport_trap_api_1455(BigInt(args[0]),BigInt(args[1])));
case 1456:return _teleport_trap_api_1456(Number(args[0]));
case 1457:return _teleport_trap_api_1457(Number(args[0]));
case 1458:return _teleport_trap_api_1458(BigInt(args[0]));
case 1459:return _teleport_trap_api_1459(Number(args[0]));
case 1460:return _teleport_trap_api_1460();
case 1461:return _teleport_trap_api_1461(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1462:return _teleport_trap_api_1462(Number(args[0]));
case 1463:return _teleport_trap_api_1463(Number(args[0]));
case 1464:return _teleport_trap_api_1464();
case 1465:return _teleport_trap_api_1465(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1466:return _teleport_trap_api_1466(Number(args[0]));
case 1467:return _teleport_trap_api_1467(Number(args[0]));
case 1468:return _teleport_trap_api_1468(BigInt(args[0]),BigInt(args[1]),Number(args[2]));
case 1469:return _teleport_trap_api_1469();
case 1470:return Number(_teleport_trap_api_1470(BigInt(args[0]),BigInt(args[1])));
case 1471:return Number(_teleport_trap_api_1471(BigInt(args[0]),BigInt(args[1])));
case 1472:return _teleport_trap_api_1472(BigInt(args[0]));
case 1473:return Number(_teleport_trap_api_1473(BigInt(args[0])));
case 1474:return _teleport_trap_api_1474(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1475:return _teleport_trap_api_1475(BigInt(args[0]));
case 1476:return Number(_teleport_trap_api_1476(Number(args[0])));
case 1477:return Number(_teleport_trap_api_1477(BigInt(args[0])));
case 1478:return _teleport_trap_api_1478(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1479:return _teleport_trap_api_1479(Number(args[0]));
case 1480:return Number(_teleport_trap_api_1480(Number(args[0]),Number(args[1])));
case 1481:return _teleport_trap_api_1481(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1482:return _teleport_trap_api_1482(BigInt(args[0]),BigInt(args[1]));
case 1483:return _teleport_trap_api_1483(BigInt(args[0]),Number(args[1]));
case 1484:return _teleport_trap_api_1484(Number(args[0]),BigInt(args[1]));
case 1485:return _teleport_trap_api_1485();
case 1486:return _teleport_trap_api_1486(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1487:return _teleport_trap_api_1487(Number(args[0]));
case 1488:return _teleport_trap_api_1488(Number(args[0]));
case 1489:return _teleport_trap_api_1489();
case 1490:return _teleport_trap_api_1490(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1491:return _teleport_trap_api_1491(Number(args[0]));
case 1492:return _teleport_trap_api_1492(Number(args[0]));
case 1493:return Number(_teleport_trap_api_1493(Number(args[0]),Number(args[1]),Number(args[2])));
case 1494:return _teleport_trap_api_1494(BigInt(args[0]));
case 1495:return _teleport_trap_api_1495(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 1496:return Number(_teleport_trap_api_1496(BigInt(args[0]),BigInt(args[1])));
case 1497:return _teleport_trap_api_1497(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 1498:return _teleport_trap_api_1498(BigInt(args[0]));
case 1499:return _teleport_trap_api_1499(Number(args[0]),Number(args[1]));
case 1500:return _teleport_trap_api_1500(Number(args[0]));
case 1501:return _teleport_trap_api_1501(Number(args[0]));
case 1502:return _teleport_trap_api_1502(Number(args[0]),Number(args[1]),Number(args[2]),Number(args[3]),Number(args[4]));
case 1503:return _teleport_trap_api_1503(Number(args[0]),Number(args[1]),BigInt(args[2]),BigInt(args[3]),BigInt(args[4]),BigInt(args[5]),BigInt(args[6]),BigInt(args[7]),Number(args[8]));
case 1504:return _teleport_trap_api_1504(Number(args[0]),Number(args[1]));
case 1505:return _teleport_trap_api_1505(Number(args[0]),Number(args[1]));
case 1506:return _teleport_trap_api_1506(Number(args[0]));
case 1507:return _teleport_trap_api_1507(Number(args[0]),Number(args[1]));
case 1508:return _teleport_trap_api_1508(Number(args[0]),Number(args[1]),Number(args[2]),Number(args[3]),Number(args[4]),Number(args[5]));
case 1509:return _teleport_trap_api_1509(Number(args[0]));
case 1510:return _teleport_trap_api_1510(Number(args[0]),Number(args[1]));
case 1511:return _teleport_trap_api_1511(BigInt(args[0]),BigInt(args[1]));
case 1512:return Number(_teleport_trap_api_1512(BigInt(args[0])));
case 1513:return _teleport_trap_api_1513(BigInt(args[0]),BigInt(args[1]));
case 1514:return Number(_teleport_trap_api_1514(Number(args[0]),Number(args[1]),Number(args[2])));
case 1515:return _teleport_trap_api_1515(BigInt(args[0]));
case 1516:return _teleport_trap_api_1516(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 1517:return _teleport_trap_api_1517(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 1518:return _teleport_trap_api_1518();
case 1519:return _teleport_trap_api_1519();
case 1520:return _teleport_trap_api_1520(BigInt(args[0]),BigInt(args[1]));
case 1521:return _teleport_trap_api_1521(Number(args[0]));
case 1522:return _teleport_trap_api_1522();
case 1523:return _teleport_trap_api_1523(BigInt(args[0]),BigInt(args[1]));
case 1524:return _teleport_trap_api_1524();
case 1525:return _teleport_trap_api_1525(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1526:return _teleport_trap_api_1526(Number(args[0]));
case 1527:return _teleport_trap_api_1527(Number(args[0]));
case 1528:return _teleport_trap_api_1528(BigInt(args[0]));
case 1529:return _teleport_trap_api_1529(BigInt(args[0]));
case 1530:return _teleport_trap_api_1530();
case 1531:return _teleport_trap_api_1531(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1532:return _teleport_trap_api_1532(Number(args[0]));
case 1533:return _teleport_trap_api_1533(Number(args[0]));
case 1534:return _teleport_trap_api_1534(BigInt(args[0]));
case 1535:return _teleport_trap_api_1535();
case 1536:return _teleport_trap_api_1536(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1537:return _teleport_trap_api_1537(Number(args[0]));
case 1538:return _teleport_trap_api_1538(Number(args[0]));
case 1539:return _teleport_trap_api_1539(BigInt(args[0]));
case 1540:return _teleport_trap_api_1540(Number(args[0]));
case 1541:return Number(_teleport_trap_api_1541(BigInt(args[0])));
case 1542:return _teleport_trap_api_1542(BigInt(args[0]),BigInt(args[1]));
case 1543:return _teleport_trap_api_1543(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]));
case 1544:return _teleport_trap_api_1544();
case 1545:return _teleport_trap_api_1545(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1546:return _teleport_trap_api_1546(Number(args[0]));
case 1547:return _teleport_trap_api_1547(Number(args[0]));
case 1548:return _teleport_trap_api_1548(BigInt(args[0]));
case 1549:return Number(_teleport_trap_api_1549(BigInt(args[0])));
case 1550:return _teleport_trap_api_1550(BigInt(args[0]),BigInt(args[1]));
case 1551:return _teleport_trap_api_1551();
case 1552:return _teleport_trap_api_1552(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1553:return _teleport_trap_api_1553(Number(args[0]));
case 1554:return _teleport_trap_api_1554(Number(args[0]));
case 1555:return _teleport_trap_api_1555();
case 1556:return _teleport_trap_api_1556(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1557:return _teleport_trap_api_1557(Number(args[0]));
case 1558:return _teleport_trap_api_1558(Number(args[0]));
case 1559:return _teleport_trap_api_1559(Number(args[0]));
case 1560:return _teleport_trap_api_1560(BigInt(args[0]));
case 1561:return Number(_teleport_trap_api_1561(BigInt(args[0])));
case 1562:return _teleport_trap_api_1562(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]));
case 1563:return _teleport_trap_api_1563(BigInt(args[0]),BigInt(args[1]));
case 1564:return _teleport_trap_api_1564(BigInt(args[0]),Number(args[1]));
case 1565:return _teleport_trap_api_1565(Number(args[0]),BigInt(args[1]));
case 1566:return Number(_teleport_trap_api_1566(BigInt(args[0])));
case 1567:return _teleport_trap_api_1567(BigInt(args[0]),Number(args[1]));
case 1568:return _teleport_trap_api_1568(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]));
case 1569:return _teleport_trap_api_1569(BigInt(args[0]),BigInt(args[1]));
case 1570:return _teleport_trap_api_1570(BigInt(args[0]),BigInt(args[1]));
case 1571:return _teleport_trap_api_1571(Number(args[0]),Number(args[1]));
case 1572:return _teleport_trap_api_1572(BigInt(args[0]),BigInt(args[1]));
case 1573:return Number(_teleport_trap_api_1573(BigInt(args[0]),BigInt(args[1]),Number(args[2])));
case 1574:return _teleport_trap_api_1574(BigInt(args[0]),Number(args[1]));
case 1575:return _teleport_trap_api_1575(BigInt(args[0]));
case 1576:return _teleport_trap_api_1576(Number(args[0]),Number(args[1]),Number(args[2]),Number(args[3]));
case 1577:return _teleport_trap_api_1577(BigInt(args[0]));
case 1578:return _teleport_trap_api_1578(Number(args[0]),Number(args[1]));
case 1579:return _teleport_trap_api_1579(Number(args[0]),Number(args[1]));
case 1580:return _teleport_trap_api_1580();
case 1581:return _teleport_trap_api_1581(BigInt(args[0]),BigInt(args[1]));
case 1582:return _teleport_trap_api_1582();
case 1583:return _teleport_trap_api_1583(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1584:return _teleport_trap_api_1584(Number(args[0]));
case 1585:return _teleport_trap_api_1585(Number(args[0]));
case 1586:return _teleport_trap_api_1586(Number(args[0]));
case 1587:return Number(_teleport_trap_api_1587(BigInt(args[0])));
case 1588:return _teleport_trap_api_1588(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1589:return _teleport_trap_api_1589();
case 1590:return _teleport_trap_api_1590(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1591:return _teleport_trap_api_1591(Number(args[0]));
case 1592:return _teleport_trap_api_1592(Number(args[0]));
case 1593:return _teleport_trap_api_1593(BigInt(args[0]));
case 1594:return Number(_teleport_trap_api_1594(BigInt(args[0])));
case 1595:return _teleport_trap_api_1595(BigInt(args[0]),BigInt(args[1]));
case 1596:return Number(_teleport_trap_api_1596(BigInt(args[0])));
case 1597:return _teleport_trap_api_1597(BigInt(args[0]),BigInt(args[1]));
case 1598:return _teleport_trap_api_1598(BigInt(args[0]));
case 1599:return Number(_teleport_trap_api_1599(Number(args[0])));
case 1600:return Number(_teleport_trap_api_1600(BigInt(args[0])));
case 1601:return Number(_teleport_trap_api_1601(BigInt(args[0])));
case 1602:return _teleport_trap_api_1602(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1603:return Number(_teleport_trap_api_1603(BigInt(args[0])));
case 1604:return Number(_teleport_trap_api_1604(Number(args[0])));
case 1605:return Number(_teleport_trap_api_1605(BigInt(args[0])));
case 1606:return _teleport_trap_api_1606(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1607:return _teleport_trap_api_1607(BigInt(args[0]));
case 1608:return _teleport_trap_api_1608(Number(args[0]));
case 1610:return Number(_teleport_trap_api_1610(BigInt(args[0])));
case 1611:return _teleport_trap_api_1611(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1612:return Number(_teleport_trap_api_1612(BigInt(args[0])));
case 1613:return _teleport_trap_api_1613(BigInt(args[0]),BigInt(args[1]));
case 1614:return Number(_teleport_trap_api_1614(BigInt(args[0])));
case 1615:return _teleport_trap_api_1615(BigInt(args[0]),BigInt(args[1]));
case 1616:return Number(_teleport_trap_api_1616(Number(args[0])));
case 1617:return Number(_teleport_trap_api_1617(BigInt(args[0])));
case 1618:return Number(_teleport_trap_api_1618(BigInt(args[0])));
case 1619:return _teleport_trap_api_1619(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1620:return Number(_teleport_trap_api_1620(BigInt(args[0])));
case 1621:return _teleport_trap_api_1621(BigInt(args[0]),BigInt(args[1]));
case 1622:return _teleport_trap_api_1622();
case 1623:return _teleport_trap_api_1623(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1624:return _teleport_trap_api_1624(Number(args[0]));
case 1625:return _teleport_trap_api_1625(Number(args[0]));
case 1626:return Number(_teleport_trap_api_1626(BigInt(args[0])));
case 1627:return _teleport_trap_api_1627(BigInt(args[0]),BigInt(args[1]));
case 1628:return Number(_teleport_trap_api_1628(BigInt(args[0])));
case 1629:return _teleport_trap_api_1629(BigInt(args[0]),BigInt(args[1]));
case 1630:return _teleport_trap_api_1630(Number(args[0]));
case 1631:return _teleport_trap_api_1631();
case 1632:return _teleport_trap_api_1632(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1633:return _teleport_trap_api_1633();
case 1634:return _teleport_trap_api_1634(Number(args[0]));
case 1635:return _teleport_trap_api_1635();
case 1636:return _teleport_trap_api_1636(Number(args[0]));
case 1637:return _teleport_trap_api_1637(BigInt(args[0]));
case 1638:return _teleport_trap_api_1638(Number(args[0]),Number(args[1]));
case 1639:return _teleport_trap_api_1639();
case 1640:return _teleport_trap_api_1640(Number(args[0]),Number(args[1]));
case 1641:return Number(_teleport_trap_api_1641(BigInt(args[0])));
case 1642:return _teleport_trap_api_1642(BigInt(args[0]),BigInt(args[1]));
case 1643:return _teleport_trap_api_1643();
case 1644:return _teleport_trap_api_1644(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1645:return _teleport_trap_api_1645(Number(args[0]));
case 1646:return _teleport_trap_api_1646(Number(args[0]));
case 1647:return _teleport_trap_api_1647();
case 1648:return _teleport_trap_api_1648(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1649:return _teleport_trap_api_1649(Number(args[0]));
case 1650:return _teleport_trap_api_1650(Number(args[0]));
case 1651:return Number(_teleport_trap_api_1651(BigInt(args[0])));
case 1652:return Number(_teleport_trap_api_1652(BigInt(args[0])));
case 1653:return _teleport_trap_api_1653(BigInt(args[0]),BigInt(args[1]));
case 1654:return Number(_teleport_trap_api_1654(BigInt(args[0])));
case 1655:return Number(_teleport_trap_api_1655(BigInt(args[0])));
case 1656:return _teleport_trap_api_1656(BigInt(args[0]),BigInt(args[1]));
case 1657:return _teleport_trap_api_1657(BigInt(args[0]));
case 1658:return _teleport_trap_api_1658(Number(args[0]),Number(args[1]));
case 1659:return _teleport_trap_api_1659(BigInt(args[0]),BigInt(args[1]),Number(args[2]),Number(args[3]));
case 1660:return Number(_teleport_trap_api_1660(BigInt(args[0])));
case 1661:return Number(_teleport_trap_api_1661(BigInt(args[0])));
case 1662:return _teleport_trap_api_1662(BigInt(args[0]),BigInt(args[1]));
case 1663:return Number(_teleport_trap_api_1663(BigInt(args[0])));
case 1664:return _teleport_trap_api_1664(BigInt(args[0]));
case 1665:return _teleport_trap_api_1665(Number(args[0]),Number(args[1]));
case 1666:return _teleport_trap_api_1666(BigInt(args[0]));
case 1667:return _teleport_trap_api_1667(Number(args[0]));
case 1668:return Number(_teleport_trap_api_1668(BigInt(args[0])));
case 1669:return Number(_teleport_trap_api_1669(BigInt(args[0]),BigInt(args[1])));
case 1670:return Number(_teleport_trap_api_1670(BigInt(args[0]),BigInt(args[1])));
case 1671:return Number(_teleport_trap_api_1671(BigInt(args[0]),BigInt(args[1])));
case 1672:return _teleport_trap_api_1672(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]),BigInt(args[4]),BigInt(args[5]));
case 1673:return Number(_teleport_trap_api_1673(BigInt(args[0])));
case 1674:return Number(_teleport_trap_api_1674(BigInt(args[0]),BigInt(args[1])));
case 1675:return _teleport_trap_api_1675(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1676:return Number(_teleport_trap_api_1676(BigInt(args[0])));
case 1677:return _teleport_trap_api_1677(BigInt(args[0]),Number(args[1]),BigInt(args[2]),BigInt(args[3]),BigInt(args[4]),BigInt(args[5]),BigInt(args[6]),BigInt(args[7]),BigInt(args[8]));
case 1678:return _teleport_trap_api_1678(BigInt(args[0]),BigInt(args[1]),Number(args[2]),Number(args[3]));
case 1679:return _teleport_trap_api_1679(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1680:return _teleport_trap_api_1680(BigInt(args[0]));
case 1681:return _teleport_trap_api_1681(BigInt(args[0]));
case 1682:return _teleport_trap_api_1682(BigInt(args[0]));
case 1683:return _teleport_trap_api_1683(BigInt(args[0]),BigInt(args[1]));
case 1684:return Number(_teleport_trap_api_1684(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]),BigInt(args[4]),BigInt(args[5]),BigInt(args[6])));
case 1685:return Number(_teleport_trap_api_1685(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]),BigInt(args[4]),BigInt(args[5]),BigInt(args[6])));
case 1686:return _teleport_trap_api_1686(BigInt(args[0]),BigInt(args[1]),Number(args[2]),Number(args[3]));
case 1687:return _teleport_trap_api_1687(BigInt(args[0]));
case 1688:return _teleport_trap_api_1688(Number(args[0]),Number(args[1]));
case 1689:return _teleport_trap_api_1689(BigInt(args[0]));
case 1690:return _teleport_trap_api_1690(BigInt(args[0]),BigInt(args[1]));
case 1691:return _teleport_trap_api_1691(BigInt(args[0]));
case 1692:return _teleport_trap_api_1692(BigInt(args[0]));
case 1693:return _teleport_trap_api_1693();
case 1694:return _teleport_trap_api_1694(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1695:return _teleport_trap_api_1695(Number(args[0]));
case 1696:return _teleport_trap_api_1696(Number(args[0]));
case 1697:return _teleport_trap_api_1697();
case 1698:return _teleport_trap_api_1698(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1699:return _teleport_trap_api_1699(Number(args[0]));
case 1700:return _teleport_trap_api_1700(Number(args[0]));
case 1701:return _teleport_trap_api_1701(BigInt(args[0]));
case 1702:return _teleport_trap_api_1702(Number(args[0]),Number(args[1]));
case 1703:return _teleport_trap_api_1703(BigInt(args[0]),BigInt(args[1]),Number(args[2]),Number(args[3]));
case 1704:return _teleport_trap_api_1704(Number(args[0]),Number(args[1]));
case 1705:return _teleport_trap_api_1705();
case 1706:return _teleport_trap_api_1706(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1707:return _teleport_trap_api_1707();
case 1708:return _teleport_trap_api_1708(Number(args[0]));
case 1709:return _teleport_trap_api_1709();
case 1710:return _teleport_trap_api_1710(Number(args[0]));
case 1711:return _teleport_trap_api_1711(BigInt(args[0]));
case 1712:return _teleport_trap_api_1712(Number(args[0]),Number(args[1]));
case 1713:return _teleport_trap_api_1713(Number(args[0]),Number(args[1]));
case 1714:return Number(_teleport_trap_api_1714(Number(args[0]),Number(args[1]),Number(args[2])));
case 1715:return _teleport_trap_api_1715(Number(args[0]),Number(args[1]),BigInt(args[2]));
case 1716:return _teleport_trap_api_1716(BigInt(args[0]));
case 1717:return _teleport_trap_api_1717(Number(args[0]),Number(args[1]));
case 1718:return _teleport_trap_api_1718();
case 1719:return _teleport_trap_api_1719(BigInt(args[0]));
case 1720:return _teleport_trap_api_1720(BigInt(args[0]));
case 1721:return Number(_teleport_trap_api_1721(BigInt(args[0]),Number(args[1]),BigInt(args[2])));
case 1722:return _teleport_trap_api_1722(BigInt(args[0]),BigInt(args[1]),Number(args[2]),BigInt(args[3]));
case 1723:return Number(_teleport_trap_api_1723(BigInt(args[0]),Number(args[1])));
case 1724:return _teleport_trap_api_1724(BigInt(args[0]),BigInt(args[1]),Number(args[2]),BigInt(args[3]));
case 1725:return Number(_teleport_trap_api_1725(BigInt(args[0]),BigInt(args[1])));
case 1726:return Number(_teleport_trap_api_1726(BigInt(args[0]),BigInt(args[1])));
case 1727:return Number(_teleport_trap_api_1727(BigInt(args[0]),BigInt(args[1])));
case 1728:return Number(_teleport_trap_api_1728(BigInt(args[0])));
case 1729:return _teleport_trap_api_1729(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1730:return Number(_teleport_trap_api_1730(BigInt(args[0])));
case 1731:return _teleport_trap_api_1731(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1732:return _teleport_trap_api_1732(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]));
case 1733:return _teleport_trap_api_1733(Number(args[0]));
case 1734:return _teleport_trap_api_1734(BigInt(args[0]));
case 1735:return _teleport_trap_api_1735(BigInt(args[0]));
case 1736:return Number(_teleport_trap_api_1736(BigInt(args[0])));
case 1737:return _teleport_trap_api_1737(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]));
case 1738:return _teleport_trap_api_1738(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]));
case 1739:return Number(_teleport_trap_api_1739(BigInt(args[0]),BigInt(args[1])));
case 1740:return Number(_teleport_trap_api_1740(BigInt(args[0])));
case 1741:return _teleport_trap_api_1741(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1742:return _teleport_trap_api_1742();
case 1743:return _teleport_trap_api_1743(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1744:return _teleport_trap_api_1744(Number(args[0]));
case 1745:return _teleport_trap_api_1745(Number(args[0]));
case 1746:return _teleport_trap_api_1746(Number(args[0]),Number(args[1]),Number(args[2]),Number(args[3]));
case 1747:return _teleport_trap_api_1747(BigInt(args[0]));
case 1748:return _teleport_trap_api_1748(BigInt(args[0]));
case 1749:return _teleport_trap_api_1749(BigInt(args[0]));
case 1750:return _teleport_trap_api_1750(BigInt(args[0]));
case 1751:return _teleport_trap_api_1751(BigInt(args[0]),Number(args[1]));
case 1752:return _teleport_trap_api_1752(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),Number(args[3]));
case 1753:return _teleport_trap_api_1753(BigInt(args[0]));
case 1755:return _teleport_trap_api_1755();
case 1756:return _teleport_trap_api_1756(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1757:return _teleport_trap_api_1757(Number(args[0]));
case 1758:return _teleport_trap_api_1758(Number(args[0]));
case 1759:return _teleport_trap_api_1759();
case 1760:return _teleport_trap_api_1760(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1761:return _teleport_trap_api_1761(Number(args[0]));
case 1762:return _teleport_trap_api_1762(Number(args[0]));
case 1763:return _teleport_trap_api_1763(BigInt(args[0]));
case 1764:return _teleport_trap_api_1764(BigInt(args[0]),BigInt(args[1]));
case 1765:return _teleport_trap_api_1765();
case 1766:return _teleport_trap_api_1766(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1767:return _teleport_trap_api_1767(Number(args[0]));
case 1768:return _teleport_trap_api_1768(Number(args[0]));
case 1769:return _teleport_trap_api_1769();
case 1770:return _teleport_trap_api_1770(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1771:return _teleport_trap_api_1771(Number(args[0]));
case 1772:return _teleport_trap_api_1772(Number(args[0]));
case 1773:return _teleport_trap_api_1773();
case 1774:return _teleport_trap_api_1774(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1775:return _teleport_trap_api_1775(Number(args[0]));
case 1776:return _teleport_trap_api_1776(Number(args[0]));
case 1777:return _teleport_trap_api_1777(Number(args[0]),Number(args[1]));
case 1778:return Number(_teleport_trap_api_1778(Number(args[0]),Number(args[1]),Number(args[2])));
case 1779:return Number(_teleport_trap_api_1779(Number(args[0])));
case 1780:return _teleport_trap_api_1780(Number(args[0]),Number(args[1]));
case 1781:return Number(_teleport_trap_api_1781(Number(args[0]),Number(args[1]),Number(args[2])));
case 1782:return Number(_teleport_trap_api_1782(BigInt(args[0]),BigInt(args[1])));
case 1783:return _teleport_trap_api_1783(BigInt(args[0]),BigInt(args[1]));
case 1784:return Number(_teleport_trap_api_1784(BigInt(args[0])));
case 1785:return _teleport_trap_api_1785(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1786:return _teleport_trap_api_1786(BigInt(args[0]),Number(args[1]),Number(args[2]),Number(args[3]),Number(args[4]));
case 1787:return _teleport_trap_api_1787(BigInt(args[0]));
case 1788:return _teleport_trap_api_1788();
case 1789:return _teleport_trap_api_1789(BigInt(args[0]),Number(args[1]),Number(args[2]),Number(args[3]),Number(args[4]));
case 1790:return _teleport_trap_api_1790(BigInt(args[0]));
case 1791:return _teleport_trap_api_1791(Number(args[0]));
case 1792:return _teleport_trap_api_1792();
case 1793:return _teleport_trap_api_1793(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1794:return _teleport_trap_api_1794(Number(args[0]),Number(args[1]));
case 1795:return _teleport_trap_api_1795(Number(args[0]),Number(args[1]));
case 1796:return _teleport_trap_api_1796();
case 1797:return _teleport_trap_api_1797(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1798:return _teleport_trap_api_1798(Number(args[0]),Number(args[1]));
case 1799:return _teleport_trap_api_1799(Number(args[0]),Number(args[1]));
case 1800:return _teleport_trap_api_1800(Number(args[0]),BigInt(args[1]),Number(args[2]));
case 1801:return _teleport_trap_api_1801(Number(args[0]),Number(args[1]));
case 1802:return Number(_teleport_trap_api_1802(BigInt(args[0])));
case 1803:return _teleport_trap_api_1803(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1804:return Number(_teleport_trap_api_1804(BigInt(args[0])));
case 1805:return _teleport_trap_api_1805(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1806:return _teleport_trap_api_1806(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 1807:return Number(_teleport_trap_api_1807(BigInt(args[0])));
case 1808:return Number(_teleport_trap_api_1808(BigInt(args[0])));
case 1809:return _teleport_trap_api_1809(BigInt(args[0]),BigInt(args[1]));
case 1810:return _teleport_trap_api_1810();
case 1811:return _teleport_trap_api_1811(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1812:return _teleport_trap_api_1812(Number(args[0]));
case 1813:return _teleport_trap_api_1813(Number(args[0]));
case 1814:return _teleport_trap_api_1814(BigInt(args[0]),Number(args[1]),BigInt(args[2]),Number(args[3]),Number(args[4]));
case 1815:return Number(_teleport_trap_api_1815(Number(args[0]),Number(args[1]),Number(args[2]),Number(args[3])));
case 1816:return _teleport_trap_api_1816(Number(args[0]),Number(args[1]));
case 1817:return Number(_teleport_trap_api_1817(Number(args[0])));
case 1818:return _teleport_trap_api_1818(BigInt(args[0]),BigInt(args[1]));
case 1819:return _teleport_trap_api_1819(BigInt(args[0]),Number(args[1]),BigInt(args[2]),Number(args[3]),Number(args[4]));
case 1820:return _teleport_trap_api_1820(Number(args[0]),Number(args[1]));
case 1821:return _teleport_trap_api_1821();
case 1822:return _teleport_trap_api_1822(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1823:return _teleport_trap_api_1823(Number(args[0]),Number(args[1]));
case 1824:return _teleport_trap_api_1824(Number(args[0]),Number(args[1]));
case 1825:return _teleport_trap_api_1825(BigInt(args[0]));
case 1826:return _teleport_trap_api_1826(Number(args[0]),Number(args[1]));
case 1827:return _teleport_trap_api_1827(BigInt(args[0]));
case 1828:return _teleport_trap_api_1828(BigInt(args[0]));
case 1829:return _teleport_trap_api_1829(BigInt(args[0]));
case 1830:return _teleport_trap_api_1830(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 1831:return _teleport_trap_api_1831(Number(args[0]),BigInt(args[1]),Number(args[2]));
case 1832:return _teleport_trap_api_1832(BigInt(args[0]));
case 1833:return _teleport_trap_api_1833();
case 1834:return _teleport_trap_api_1834(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1835:return _teleport_trap_api_1835(Number(args[0]),Number(args[1]));
case 1836:return _teleport_trap_api_1836(Number(args[0]),Number(args[1]));
case 1837:return _teleport_trap_api_1837(Number(args[0]));
case 1838:return _teleport_trap_api_1838(Number(args[0]),Number(args[1]));
case 1839:return _teleport_trap_api_1839(BigInt(args[0]));
case 1840:return _teleport_trap_api_1840();
case 1841:return _teleport_trap_api_1841(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1842:return _teleport_trap_api_1842(Number(args[0]));
case 1843:return _teleport_trap_api_1843(Number(args[0]));
case 1844:return Number(_teleport_trap_api_1844());
case 1845:return Number(_teleport_trap_api_1845(BigInt(args[0])));
case 1846:return Number(_teleport_trap_api_1846(BigInt(args[0])));
case 1847:return _teleport_trap_api_1847(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1848:return _teleport_trap_api_1848(BigInt(args[0]));
case 1849:return Number(_teleport_trap_api_1849(BigInt(args[0]),BigInt(args[1])));
case 1850:return _teleport_trap_api_1850(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1851:return _teleport_trap_api_1851();
case 1852:return _teleport_trap_api_1852(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1853:return _teleport_trap_api_1853(Number(args[0]));
case 1854:return _teleport_trap_api_1854(Number(args[0]));
case 1855:return _teleport_trap_api_1855(BigInt(args[0]),Number(args[1]));
case 1856:return _teleport_trap_api_1856();
case 1857:return _teleport_trap_api_1857(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1858:return _teleport_trap_api_1858(Number(args[0]));
case 1859:return _teleport_trap_api_1859(Number(args[0]));
case 1860:return _teleport_trap_api_1860(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1861:return _teleport_trap_api_1861(BigInt(args[0]));
case 1862:return _teleport_trap_api_1862();
case 1863:return _teleport_trap_api_1863(BigInt(args[0]));
case 1864:return _teleport_trap_api_1864(BigInt(args[0]));
case 1865:return _teleport_trap_api_1865(Number(args[0]),Number(args[1]));
case 1866:return _teleport_trap_api_1866(Number(args[0]),Number(args[1]));
case 1867:return _teleport_trap_api_1867(Number(args[0]));
case 1868:return _teleport_trap_api_1868(Number(args[0]));
case 1869:return _teleport_trap_api_1869(Number(args[0]),Number(args[1]));
case 1870:return _teleport_trap_api_1870(Number(args[0]),Number(args[1]));
case 1871:return _teleport_trap_api_1871(Number(args[0]),Number(args[1]));
case 1872:return _teleport_trap_api_1872();
case 1873:return _teleport_trap_api_1873();
case 1874:return _teleport_trap_api_1874(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1875:return _teleport_trap_api_1875(Number(args[0]));
case 1876:return _teleport_trap_api_1876(Number(args[0]));
case 1877:return Number(_teleport_trap_api_1877(BigInt(args[0])));
case 1878:return _teleport_trap_api_1878(BigInt(args[0]),BigInt(args[1]));
case 1879:return _teleport_trap_api_1879(Number(args[0]));
case 1880:return _teleport_trap_api_1880(Number(args[0]),BigInt(args[1]),Number(args[2]));
case 1881:return _teleport_trap_api_1881(Number(args[0]),Number(args[1]));
case 1882:return _teleport_trap_api_1882(Number(args[0]),Number(args[1]));
case 1883:return _teleport_trap_api_1883(BigInt(args[0]),Number(args[1]));
case 1884:return _teleport_trap_api_1884(BigInt(args[0]));
case 1885:return _teleport_trap_api_1885();
case 1886:return _teleport_trap_api_1886(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1887:return _teleport_trap_api_1887(Number(args[0]));
case 1888:return _teleport_trap_api_1888(Number(args[0]));
case 1889:return _teleport_trap_api_1889(BigInt(args[0]));
case 1890:return _teleport_trap_api_1890();
case 1891:return _teleport_trap_api_1891(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1892:return _teleport_trap_api_1892(Number(args[0]));
case 1893:return _teleport_trap_api_1893(Number(args[0]));
case 1894:return Number(_teleport_trap_api_1894(BigInt(args[0])));
case 1895:return Number(_teleport_trap_api_1895(BigInt(args[0])));
case 1896:return _teleport_trap_api_1896(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]));
case 1897:return Number(_teleport_trap_api_1897(BigInt(args[0])));
case 1898:return Number(_teleport_trap_api_1898(BigInt(args[0])));
case 1899:return _teleport_trap_api_1899(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]),BigInt(args[4]));
case 1900:return _teleport_trap_api_1900(BigInt(args[0]),BigInt(args[1]));
case 1901:return _teleport_trap_api_1901(BigInt(args[0]),BigInt(args[1]),Number(args[2]));
case 1902:return _teleport_trap_api_1902(Number(args[0]),Number(args[1]));
case 1903:return _teleport_trap_api_1903(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 1904:return _teleport_trap_api_1904(BigInt(args[0]));
case 1905:return _teleport_trap_api_1905(BigInt(args[0]));
case 1906:return _teleport_trap_api_1906(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1907:return _teleport_trap_api_1907(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1908:return _teleport_trap_api_1908(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1909:return _teleport_trap_api_1909();
case 1910:return _teleport_trap_api_1910(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1911:return _teleport_trap_api_1911(Number(args[0]),Number(args[1]));
case 1912:return _teleport_trap_api_1912(Number(args[0]),Number(args[1]));
case 1913:return _teleport_trap_api_1913(BigInt(args[0]),Number(args[1]));
case 1914:return _teleport_trap_api_1914(BigInt(args[0]));
case 1915:return _teleport_trap_api_1915(Number(args[0]),Number(args[1]));
case 1916:return _teleport_trap_api_1916();
case 1917:return _teleport_trap_api_1917(BigInt(args[0]),BigInt(args[1]));
case 1918:return Number(_teleport_trap_api_1918(BigInt(args[0])));
case 1919:return _teleport_trap_api_1919(BigInt(args[0]),BigInt(args[1]),Number(args[2]),Number(args[3]));
case 1920:return _teleport_trap_api_1920(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 1921:return Number(_teleport_trap_api_1921(BigInt(args[0]),BigInt(args[1])));
case 1922:return _teleport_trap_api_1922(BigInt(args[0]),BigInt(args[1]));
case 1923:return _teleport_trap_api_1923();
case 1924:return _teleport_trap_api_1924(BigInt(args[0]));
case 1925:return _teleport_trap_api_1925(BigInt(args[0]),BigInt(args[1]));
case 1926:return Number(_teleport_trap_api_1926(BigInt(args[0])));
case 1927:return _teleport_trap_api_1927(BigInt(args[0]),BigInt(args[1]));
case 1928:return _teleport_trap_api_1928(Number(args[0]),BigInt(args[1]),Number(args[2]));
case 1929:return Number(_teleport_trap_api_1929(Number(args[0]),Number(args[1])));
case 1930:return _teleport_trap_api_1930(BigInt(args[0]),BigInt(args[1]));
case 1931:return Number(_teleport_trap_api_1931(BigInt(args[0])));
case 1932:return Number(_teleport_trap_api_1932(BigInt(args[0])));
case 1933:return Number(_teleport_trap_api_1933(BigInt(args[0])));
case 1934:return _teleport_trap_api_1934(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1935:return Number(_teleport_trap_api_1935(BigInt(args[0]),BigInt(args[1])));
case 1936:return _teleport_trap_api_1936(BigInt(args[0]),BigInt(args[1]));
case 1937:return _teleport_trap_api_1937(BigInt(args[0]),Number(args[1]));
case 1938:return _teleport_trap_api_1938(BigInt(args[0]));
case 1939:return _teleport_trap_api_1939(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]),BigInt(args[3]));
case 1940:return Number(_teleport_trap_api_1940(BigInt(args[0]),BigInt(args[1])));
case 1941:return _teleport_trap_api_1941(BigInt(args[0]),BigInt(args[1]));
case 1942:return _teleport_trap_api_1942(Number(args[0]));
case 1943:return _teleport_trap_api_1943(Number(args[0]));
case 1944:return _teleport_trap_api_1944(BigInt(args[0]));
case 1945:return _teleport_trap_api_1945(BigInt(args[0]),BigInt(args[1]));
case 1946:return _teleport_trap_api_1946(BigInt(args[0]),BigInt(args[1]));
case 1947:return _teleport_trap_api_1947(BigInt(args[0]),BigInt(args[1]));
case 1948:return _teleport_trap_api_1948(Number(args[0]));
case 1949:return _teleport_trap_api_1949(BigInt(args[0]),BigInt(args[1]));
case 1950:return _teleport_trap_api_1950();
case 1951:return _teleport_trap_api_1951(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1952:return _teleport_trap_api_1952(Number(args[0]));
case 1953:return _teleport_trap_api_1953(Number(args[0]));
case 1954:return _teleport_trap_api_1954();
case 1955:return _teleport_trap_api_1955(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1956:return _teleport_trap_api_1956(Number(args[0]));
case 1957:return _teleport_trap_api_1957(Number(args[0]));
case 1958:return Number(_teleport_trap_api_1958(Number(args[0]),Number(args[1])));
case 1959:return _teleport_trap_api_1959(BigInt(args[0]),BigInt(args[1]),BigInt(args[2]));
case 1960:return _teleport_trap_api_1960(BigInt(args[0]));
case 1961:return _teleport_trap_api_1961(BigInt(args[0]));
case 1962:return _teleport_trap_api_1962(Number(args[0]),BigInt(args[1]),Number(args[2]));
case 1963:return _teleport_trap_api_1963(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 1964:return _teleport_trap_api_1964(Number(args[0]),Number(args[1]));
case 1965:return Number(_teleport_trap_api_1965(BigInt(args[0]),BigInt(args[1])));
case 1966:return _teleport_trap_api_1966(BigInt(args[0]));
case 1967:return _teleport_trap_api_1967();
case 1968:return _teleport_trap_api_1968(Number(args[0]));
case 1969:return _teleport_trap_api_1969(Number(args[0]));
case 1970:return _teleport_trap_api_1970();
case 1971:return _teleport_trap_api_1971(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1972:return _teleport_trap_api_1972(Number(args[0]));
case 1973:return _teleport_trap_api_1973(Number(args[0]));
case 1974:return _teleport_trap_api_1974(BigInt(args[0]));
case 1975:return _teleport_trap_api_1975();
case 1976:return _teleport_trap_api_1976(BigInt(args[0]));
case 1977:return _teleport_trap_api_1977();
case 1978:return _teleport_trap_api_1978(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1979:return _teleport_trap_api_1979(Number(args[0]));
case 1980:return _teleport_trap_api_1980(Number(args[0]));
case 1981:return _teleport_trap_api_1981(Number(args[0]));
case 1982:return Number(_teleport_trap_api_1982(Number(args[0])));
case 1983:return _teleport_trap_api_1983(BigInt(args[0]),BigInt(args[1]),Number(args[2]),BigInt(args[3]));
case 1984:return _teleport_trap_api_1984(Number(args[0]));
case 1985:return _teleport_trap_api_1985();
case 1986:return _teleport_trap_api_1986(BigInt(args[0]),Number(args[1]),BigInt(args[2]));
case 1987:return _teleport_trap_api_1987(Number(args[0]));
case 1988:return _teleport_trap_api_1988(Number(args[0]));
case 1989:return Number(_teleport_trap_api_1989(Number(args[0]),Number(args[1]),Number(args[2])));
case 1990:return _teleport_trap_api_1990(BigInt(args[0]),BigInt(args[1]),Number(args[2]));
case 1991:return Number(_teleport_trap_api_1991(BigInt(args[0]),BigInt(args[1])));
case 1992:return Number(_teleport_trap_api_1992(BigInt(args[0])));
case 1993:return _teleport_trap_api_1993(BigInt(args[0]));
case 1994:return _teleport_trap_api_1994(Number(args[0]),Number(args[1]));
case 1995:return _teleport_trap_api_1995(BigInt(args[0]),Number(args[1]),Number(args[2]));
case 1996:return _teleport_trap_api_1996(BigInt(args[0]),Number(args[1]));
default:throw Error("TRAP API site "+site);}},indirect:(site,target,...args)=>{switch(site){
case 127:return _teleport_trap_api_127(pointer(target) , Number(args[0]),Number(args[1]));
case 877:return _teleport_trap_api_877(pointer(target) , Number(args[0]));
case 879:return _teleport_trap_api_879(pointer(target) , Number(args[0]));
case 880:return _teleport_trap_api_880(pointer(target) , Number(args[0]));
case 884:return _teleport_trap_api_884(pointer(target));
case 1122:return _teleport_trap_api_1122(pointer(target) , Number(args[0]),Number(args[1]));
case 1123:return _teleport_trap_api_1123(pointer(target) , Number(args[0]));
case 1609:return _teleport_trap_api_1609(pointer(target) , Number(args[0]),Number(args[1]));
case 1754:return _teleport_trap_api_1754(pointer(target) , Number(args[0]),Number(args[1]));
default:throw Error("TRAP indirect site "+site);}}};},
$teleportTrapCall__deps:['$teleportTrapServices'],
$teleportTrapCall:function(name,...args){return Module.nethackPorted.trap(teleportTrapServices(),name,...args);},
teleport_trap_js_burnarmor__deps:["$teleportTrapCall"],teleport_trap_js_burnarmor__sig:"ip",
teleport_trap_js_burnarmor:function(a0){return teleportTrapCall("burnarmor",a0);},
teleport_trap_js_erode_obj__deps:["$teleportTrapCall"],teleport_trap_js_erode_obj__sig:"ippii",
teleport_trap_js_erode_obj:function(a0,a1,a2,a3){return teleportTrapCall("erode_obj",a0,a1,a2,a3);},
teleport_trap_js_grease_protect__deps:["$teleportTrapCall"],teleport_trap_js_grease_protect__sig:"ippp",
teleport_trap_js_grease_protect:function(a0,a1,a2){return teleportTrapCall("grease_protect",a0,a1,a2);},
teleport_trap_js_mk_trap_statue__deps:["$teleportTrapCall"],teleport_trap_js_mk_trap_statue__sig:"vii",
teleport_trap_js_mk_trap_statue:function(a0,a1){teleportTrapCall("mk_trap_statue",a0,a1);},
teleport_trap_js_dng_bottom__deps:["$teleportTrapCall"],teleport_trap_js_dng_bottom__sig:"ip",
teleport_trap_js_dng_bottom:function(a0){return teleportTrapCall("dng_bottom",a0);},
teleport_trap_js_hole_destination__deps:["$teleportTrapCall"],teleport_trap_js_hole_destination__sig:"vp",
teleport_trap_js_hole_destination:function(a0){teleportTrapCall("hole_destination",a0);},
teleport_trap_js_maketrap__deps:["$teleportTrapCall"],teleport_trap_js_maketrap__sig:"piii",
teleport_trap_js_maketrap:function(a0,a1,a2){return BigInt(teleportTrapCall("maketrap",a0,a1,a2)??0);},
teleport_trap_js_clamp_hole_destination__deps:["$teleportTrapCall"],teleport_trap_js_clamp_hole_destination__sig:"pp",
teleport_trap_js_clamp_hole_destination:function(a0){return BigInt(teleportTrapCall("clamp_hole_destination",a0)??0);},
teleport_trap_js_fall_through__deps:["$teleportTrapCall"],teleport_trap_js_fall_through__sig:"vii",
teleport_trap_js_fall_through:function(a0,a1){teleportTrapCall("fall_through",a0,a1);},
teleport_trap_js_animate_statue__deps:["$teleportTrapCall"],teleport_trap_js_animate_statue__sig:"ppiiip",
teleport_trap_js_animate_statue:function(a0,a1,a2,a3,a4){return BigInt(teleportTrapCall("animate_statue",a0,a1,a2,a3,a4)??0);},
teleport_trap_js_activate_statue_trap__deps:["$teleportTrapCall"],teleport_trap_js_activate_statue_trap__sig:"ppiii",
teleport_trap_js_activate_statue_trap:function(a0,a1,a2,a3){return BigInt(teleportTrapCall("activate_statue_trap",a0,a1,a2,a3)??0);},
teleport_trap_js_keep_saddle_with_steedcorpse__deps:["$teleportTrapCall"],teleport_trap_js_keep_saddle_with_steedcorpse__sig:"iipp",
teleport_trap_js_keep_saddle_with_steedcorpse:function(a0,a1,a2){return teleportTrapCall("keep_saddle_with_steedcorpse",a0,a1,a2);},
teleport_trap_js_mu_maybe_destroy_web__deps:["$teleportTrapCall"],teleport_trap_js_mu_maybe_destroy_web__sig:"ipip",
teleport_trap_js_mu_maybe_destroy_web:function(a0,a1,a2){return teleportTrapCall("mu_maybe_destroy_web",a0,a1,a2);},
teleport_trap_js_t_missile__deps:["$teleportTrapCall"],teleport_trap_js_t_missile__sig:"pip",
teleport_trap_js_t_missile:function(a0,a1){return BigInt(teleportTrapCall("t_missile",a0,a1)??0);},
teleport_trap_js_set_utrap__deps:["$teleportTrapCall"],teleport_trap_js_set_utrap__sig:"vii",
teleport_trap_js_set_utrap:function(a0,a1){teleportTrapCall("set_utrap",a0,a1);},
teleport_trap_js_reset_utrap__deps:["$teleportTrapCall"],teleport_trap_js_reset_utrap__sig:"vi",
teleport_trap_js_reset_utrap:function(a0){teleportTrapCall("reset_utrap",a0);},
teleport_trap_js_floor_trigger__deps:["$teleportTrapCall"],teleport_trap_js_floor_trigger__sig:"ii",
teleport_trap_js_floor_trigger:function(a0){return teleportTrapCall("floor_trigger",a0);},
teleport_trap_js_check_in_air__deps:["$teleportTrapCall"],teleport_trap_js_check_in_air__sig:"ipi",
teleport_trap_js_check_in_air:function(a0,a1){return teleportTrapCall("check_in_air",a0,a1);},
teleport_trap_js_wearing_iron_shoes__deps:["$teleportTrapCall"],teleport_trap_js_wearing_iron_shoes__sig:"ip",
teleport_trap_js_wearing_iron_shoes:function(a0){return teleportTrapCall("wearing_iron_shoes",a0);},
teleport_trap_js_m_harmless_trap__deps:["$teleportTrapCall"],teleport_trap_js_m_harmless_trap__sig:"ipp",
teleport_trap_js_m_harmless_trap:function(a0,a1){return teleportTrapCall("m_harmless_trap",a0,a1);},
teleport_trap_js_trapeffect_arrow_trap__deps:["$teleportTrapCall"],teleport_trap_js_trapeffect_arrow_trap__sig:"ippi",
teleport_trap_js_trapeffect_arrow_trap:function(a0,a1,a2){return teleportTrapCall("trapeffect_arrow_trap",a0,a1,a2);},
teleport_trap_js_trapeffect_dart_trap__deps:["$teleportTrapCall"],teleport_trap_js_trapeffect_dart_trap__sig:"ippi",
teleport_trap_js_trapeffect_dart_trap:function(a0,a1,a2){return teleportTrapCall("trapeffect_dart_trap",a0,a1,a2);},
teleport_trap_js_trapeffect_rocktrap__deps:["$teleportTrapCall"],teleport_trap_js_trapeffect_rocktrap__sig:"ippi",
teleport_trap_js_trapeffect_rocktrap:function(a0,a1,a2){return teleportTrapCall("trapeffect_rocktrap",a0,a1,a2);},
teleport_trap_js_trapeffect_sqky_board__deps:["$teleportTrapCall"],teleport_trap_js_trapeffect_sqky_board__sig:"ippi",
teleport_trap_js_trapeffect_sqky_board:function(a0,a1,a2){return teleportTrapCall("trapeffect_sqky_board",a0,a1,a2);},
teleport_trap_js_trapeffect_bear_trap__deps:["$teleportTrapCall"],teleport_trap_js_trapeffect_bear_trap__sig:"ippi",
teleport_trap_js_trapeffect_bear_trap:function(a0,a1,a2){return teleportTrapCall("trapeffect_bear_trap",a0,a1,a2);},
teleport_trap_js_trapeffect_slp_gas_trap__deps:["$teleportTrapCall"],teleport_trap_js_trapeffect_slp_gas_trap__sig:"ippi",
teleport_trap_js_trapeffect_slp_gas_trap:function(a0,a1,a2){return teleportTrapCall("trapeffect_slp_gas_trap",a0,a1,a2);},
teleport_trap_js_trapeffect_rust_trap__deps:["$teleportTrapCall"],teleport_trap_js_trapeffect_rust_trap__sig:"ippi",
teleport_trap_js_trapeffect_rust_trap:function(a0,a1,a2){return teleportTrapCall("trapeffect_rust_trap",a0,a1,a2);},
teleport_trap_js_trapeffect_fire_trap__deps:["$teleportTrapCall"],teleport_trap_js_trapeffect_fire_trap__sig:"ippi",
teleport_trap_js_trapeffect_fire_trap:function(a0,a1,a2){return teleportTrapCall("trapeffect_fire_trap",a0,a1,a2);},
teleport_trap_js_trapeffect_pit__deps:["$teleportTrapCall"],teleport_trap_js_trapeffect_pit__sig:"ippi",
teleport_trap_js_trapeffect_pit:function(a0,a1,a2){return teleportTrapCall("trapeffect_pit",a0,a1,a2);},
teleport_trap_js_trapeffect_hole__deps:["$teleportTrapCall"],teleport_trap_js_trapeffect_hole__sig:"ippi",
teleport_trap_js_trapeffect_hole:function(a0,a1,a2){return teleportTrapCall("trapeffect_hole",a0,a1,a2);},
teleport_trap_js_trapeffect_telep_trap__deps:["$teleportTrapCall"],teleport_trap_js_trapeffect_telep_trap__sig:"ippi",
teleport_trap_js_trapeffect_telep_trap:function(a0,a1,a2){return teleportTrapCall("trapeffect_telep_trap",a0,a1,a2);},
teleport_trap_js_trapeffect_level_telep__deps:["$teleportTrapCall"],teleport_trap_js_trapeffect_level_telep__sig:"ippi",
teleport_trap_js_trapeffect_level_telep:function(a0,a1,a2){return teleportTrapCall("trapeffect_level_telep",a0,a1,a2);},
teleport_trap_js_trapeffect_web__deps:["$teleportTrapCall"],teleport_trap_js_trapeffect_web__sig:"ippi",
teleport_trap_js_trapeffect_web:function(a0,a1,a2){return teleportTrapCall("trapeffect_web",a0,a1,a2);},
teleport_trap_js_trapeffect_statue_trap__deps:["$teleportTrapCall"],teleport_trap_js_trapeffect_statue_trap__sig:"ippi",
teleport_trap_js_trapeffect_statue_trap:function(a0,a1,a2){return teleportTrapCall("trapeffect_statue_trap",a0,a1,a2);},
teleport_trap_js_trapeffect_magic_trap__deps:["$teleportTrapCall"],teleport_trap_js_trapeffect_magic_trap__sig:"ippi",
teleport_trap_js_trapeffect_magic_trap:function(a0,a1,a2){return teleportTrapCall("trapeffect_magic_trap",a0,a1,a2);},
teleport_trap_js_trapeffect_anti_magic__deps:["$teleportTrapCall"],teleport_trap_js_trapeffect_anti_magic__sig:"ippi",
teleport_trap_js_trapeffect_anti_magic:function(a0,a1,a2){return teleportTrapCall("trapeffect_anti_magic",a0,a1,a2);},
teleport_trap_js_trapeffect_poly_trap__deps:["$teleportTrapCall"],teleport_trap_js_trapeffect_poly_trap__sig:"ippi",
teleport_trap_js_trapeffect_poly_trap:function(a0,a1,a2){return teleportTrapCall("trapeffect_poly_trap",a0,a1,a2);},
teleport_trap_js_trapeffect_landmine__deps:["$teleportTrapCall"],teleport_trap_js_trapeffect_landmine__sig:"ippi",
teleport_trap_js_trapeffect_landmine:function(a0,a1,a2){return teleportTrapCall("trapeffect_landmine",a0,a1,a2);},
teleport_trap_js_trapeffect_rolling_boulder_trap__deps:["$teleportTrapCall"],teleport_trap_js_trapeffect_rolling_boulder_trap__sig:"ippi",
teleport_trap_js_trapeffect_rolling_boulder_trap:function(a0,a1,a2){return teleportTrapCall("trapeffect_rolling_boulder_trap",a0,a1,a2);},
teleport_trap_js_trapeffect_magic_portal__deps:["$teleportTrapCall"],teleport_trap_js_trapeffect_magic_portal__sig:"ippi",
teleport_trap_js_trapeffect_magic_portal:function(a0,a1,a2){return teleportTrapCall("trapeffect_magic_portal",a0,a1,a2);},
teleport_trap_js_trapeffect_vibrating_square__deps:["$teleportTrapCall"],teleport_trap_js_trapeffect_vibrating_square__sig:"ippi",
teleport_trap_js_trapeffect_vibrating_square:function(a0,a1,a2){return teleportTrapCall("trapeffect_vibrating_square",a0,a1,a2);},
teleport_trap_js_immune_to_trap__deps:["$teleportTrapCall"],teleport_trap_js_immune_to_trap__sig:"ipi",
teleport_trap_js_immune_to_trap:function(a0,a1){return teleportTrapCall("immune_to_trap",a0,a1);},
teleport_trap_js_trapeffect_selector__deps:["$teleportTrapCall"],teleport_trap_js_trapeffect_selector__sig:"ippi",
teleport_trap_js_trapeffect_selector:function(a0,a1,a2){return teleportTrapCall("trapeffect_selector",a0,a1,a2);},
teleport_trap_js_dotrap__deps:["$teleportTrapCall"],teleport_trap_js_dotrap__sig:"vpi",
teleport_trap_js_dotrap:function(a0,a1){teleportTrapCall("dotrap",a0,a1);},
teleport_trap_js_trapnote__deps:["$teleportTrapCall"],teleport_trap_js_trapnote__sig:"ppi",
teleport_trap_js_trapnote:function(a0,a1){return BigInt(teleportTrapCall("trapnote",a0,a1)??0);},
teleport_trap_js_choose_trapnote__deps:["$teleportTrapCall"],teleport_trap_js_choose_trapnote__sig:"ip",
teleport_trap_js_choose_trapnote:function(a0){return teleportTrapCall("choose_trapnote",a0);},
teleport_trap_js_steedintrap__deps:["$teleportTrapCall"],teleport_trap_js_steedintrap__sig:"ipp",
teleport_trap_js_steedintrap:function(a0,a1){return teleportTrapCall("steedintrap",a0,a1);},
teleport_trap_js_blow_up_landmine__deps:["$teleportTrapCall"],teleport_trap_js_blow_up_landmine__sig:"vp",
teleport_trap_js_blow_up_landmine:function(a0){teleportTrapCall("blow_up_landmine",a0);},
teleport_trap_js_launch_drop_spot__deps:["$teleportTrapCall"],teleport_trap_js_launch_drop_spot__sig:"vpii",
teleport_trap_js_launch_drop_spot:function(a0,a1,a2){teleportTrapCall("launch_drop_spot",a0,a1,a2);},
teleport_trap_js_launch_in_progress__deps:["$teleportTrapCall"],teleport_trap_js_launch_in_progress__sig:"i",
teleport_trap_js_launch_in_progress:function(){return teleportTrapCall("launch_in_progress");},
teleport_trap_js_force_launch_placement__deps:["$teleportTrapCall"],teleport_trap_js_force_launch_placement__sig:"v",
teleport_trap_js_force_launch_placement:function(){teleportTrapCall("force_launch_placement");},
teleport_trap_js_launch_obj__deps:["$teleportTrapCall"],teleport_trap_js_launch_obj__sig:"iiiiiii",
teleport_trap_js_launch_obj:function(a0,a1,a2,a3,a4,a5){return teleportTrapCall("launch_obj",a0,a1,a2,a3,a4,a5);},
teleport_trap_js_seetrap__deps:["$teleportTrapCall"],teleport_trap_js_seetrap__sig:"vp",
teleport_trap_js_seetrap:function(a0){teleportTrapCall("seetrap",a0);},
teleport_trap_js_feeltrap__deps:["$teleportTrapCall"],teleport_trap_js_feeltrap__sig:"vp",
teleport_trap_js_feeltrap:function(a0){teleportTrapCall("feeltrap",a0);},
teleport_trap_js_find_random_launch_coord__deps:["$teleportTrapCall"],teleport_trap_js_find_random_launch_coord__sig:"ipp",
teleport_trap_js_find_random_launch_coord:function(a0,a1){return teleportTrapCall("find_random_launch_coord",a0,a1);},
teleport_trap_js_mkroll_launch__deps:["$teleportTrapCall"],teleport_trap_js_mkroll_launch__sig:"ipiiij",
teleport_trap_js_mkroll_launch:function(a0,a1,a2,a3,a4){return teleportTrapCall("mkroll_launch",a0,a1,a2,a3,a4);},
teleport_trap_js_isclearpath__deps:["$teleportTrapCall"],teleport_trap_js_isclearpath__sig:"ipiii",
teleport_trap_js_isclearpath:function(a0,a1,a2,a3){return teleportTrapCall("isclearpath",a0,a1,a2,a3);},
teleport_trap_js_m_easy_escape_pit__deps:["$teleportTrapCall"],teleport_trap_js_m_easy_escape_pit__sig:"ip",
teleport_trap_js_m_easy_escape_pit:function(a0){return teleportTrapCall("m_easy_escape_pit",a0);},
teleport_trap_js_mintrap__deps:["$teleportTrapCall"],teleport_trap_js_mintrap__sig:"ipi",
teleport_trap_js_mintrap:function(a0,a1){return teleportTrapCall("mintrap",a0,a1);},
teleport_trap_js_instapetrify__deps:["$teleportTrapCall"],teleport_trap_js_instapetrify__sig:"vp",
teleport_trap_js_instapetrify:function(a0){teleportTrapCall("instapetrify",a0);},
teleport_trap_js_minstapetrify__deps:["$teleportTrapCall"],teleport_trap_js_minstapetrify__sig:"vpi",
teleport_trap_js_minstapetrify:function(a0,a1){teleportTrapCall("minstapetrify",a0,a1);},
teleport_trap_js_selftouch__deps:["$teleportTrapCall"],teleport_trap_js_selftouch__sig:"vp",
teleport_trap_js_selftouch:function(a0){teleportTrapCall("selftouch",a0);},
teleport_trap_js_mselftouch__deps:["$teleportTrapCall"],teleport_trap_js_mselftouch__sig:"vppi",
teleport_trap_js_mselftouch:function(a0,a1,a2){teleportTrapCall("mselftouch",a0,a1,a2);},
teleport_trap_js_float_up__deps:["$teleportTrapCall"],teleport_trap_js_float_up__sig:"v",
teleport_trap_js_float_up:function(){teleportTrapCall("float_up");},
teleport_trap_js_fill_pit__deps:["$teleportTrapCall"],teleport_trap_js_fill_pit__sig:"vii",
teleport_trap_js_fill_pit:function(a0,a1){teleportTrapCall("fill_pit",a0,a1);},
teleport_trap_js_float_down__deps:["$teleportTrapCall"],teleport_trap_js_float_down__sig:"ijj",
teleport_trap_js_float_down:function(a0,a1){return teleportTrapCall("float_down",a0,a1);},
teleport_trap_js_climb_pit__deps:["$teleportTrapCall"],teleport_trap_js_climb_pit__sig:"v",
teleport_trap_js_climb_pit:function(){teleportTrapCall("climb_pit");},
teleport_trap_js_dofiretrap__deps:["$teleportTrapCall"],teleport_trap_js_dofiretrap__sig:"vp",
teleport_trap_js_dofiretrap:function(a0){teleportTrapCall("dofiretrap",a0);},
teleport_trap_js_domagictrap__deps:["$teleportTrapCall"],teleport_trap_js_domagictrap__sig:"v",
teleport_trap_js_domagictrap:function(){teleportTrapCall("domagictrap");},
teleport_trap_js_fire_damage__deps:["$teleportTrapCall"],teleport_trap_js_fire_damage__sig:"ipiii",
teleport_trap_js_fire_damage:function(a0,a1,a2,a3){return teleportTrapCall("fire_damage",a0,a1,a2,a3);},
teleport_trap_js_fire_damage_chain__deps:["$teleportTrapCall"],teleport_trap_js_fire_damage_chain__sig:"ipiiii",
teleport_trap_js_fire_damage_chain:function(a0,a1,a2,a3,a4){return teleportTrapCall("fire_damage_chain",a0,a1,a2,a3,a4);},
teleport_trap_js_lava_damage__deps:["$teleportTrapCall"],teleport_trap_js_lava_damage__sig:"ipii",
teleport_trap_js_lava_damage:function(a0,a1,a2){return teleportTrapCall("lava_damage",a0,a1,a2);},
teleport_trap_js_acid_damage__deps:["$teleportTrapCall"],teleport_trap_js_acid_damage__sig:"vp",
teleport_trap_js_acid_damage:function(a0){teleportTrapCall("acid_damage",a0);},
teleport_trap_js_pot_acid_damage__deps:["$teleportTrapCall"],teleport_trap_js_pot_acid_damage__sig:"vpii",
teleport_trap_js_pot_acid_damage:function(a0,a1,a2){teleportTrapCall("pot_acid_damage",a0,a1,a2);},
teleport_trap_js_water_damage__deps:["$teleportTrapCall"],teleport_trap_js_water_damage__sig:"ippi",
teleport_trap_js_water_damage:function(a0,a1,a2){return teleportTrapCall("water_damage",a0,a1,a2);},
teleport_trap_js_water_damage_chain__deps:["$teleportTrapCall"],teleport_trap_js_water_damage_chain__sig:"vpi",
teleport_trap_js_water_damage_chain:function(a0,a1){teleportTrapCall("water_damage_chain",a0,a1);},
teleport_trap_js_emergency_disrobe__deps:["$teleportTrapCall"],teleport_trap_js_emergency_disrobe__sig:"ip",
teleport_trap_js_emergency_disrobe:function(a0){return teleportTrapCall("emergency_disrobe",a0);},
teleport_trap_js_rnd_nextto_goodpos__deps:["$teleportTrapCall"],teleport_trap_js_rnd_nextto_goodpos__sig:"ippp",
teleport_trap_js_rnd_nextto_goodpos:function(a0,a1,a2){return teleportTrapCall("rnd_nextto_goodpos",a0,a1,a2);},
teleport_trap_js_back_on_ground__deps:["$teleportTrapCall"],teleport_trap_js_back_on_ground__sig:"vi",
teleport_trap_js_back_on_ground:function(a0){teleportTrapCall("back_on_ground",a0);},
teleport_trap_js_rescued_from_terrain__deps:["$teleportTrapCall"],teleport_trap_js_rescued_from_terrain__sig:"vi",
teleport_trap_js_rescued_from_terrain:function(a0){teleportTrapCall("rescued_from_terrain",a0);},
teleport_trap_js_drown__deps:["$teleportTrapCall"],teleport_trap_js_drown__sig:"i",
teleport_trap_js_drown:function(){return teleportTrapCall("drown");},
teleport_trap_js_drain_en__deps:["$teleportTrapCall"],teleport_trap_js_drain_en__sig:"vii",
teleport_trap_js_drain_en:function(a0,a1){teleportTrapCall("drain_en",a0,a1);},
teleport_trap_js_dountrap__deps:["$teleportTrapCall"],teleport_trap_js_dountrap__sig:"i",
teleport_trap_js_dountrap:function(){return teleportTrapCall("dountrap");},
teleport_trap_js_could_untrap__deps:["$teleportTrapCall"],teleport_trap_js_could_untrap__sig:"iii",
teleport_trap_js_could_untrap:function(a0,a1){return teleportTrapCall("could_untrap",a0,a1);},
teleport_trap_js_untrap_prob__deps:["$teleportTrapCall"],teleport_trap_js_untrap_prob__sig:"ip",
teleport_trap_js_untrap_prob:function(a0){return teleportTrapCall("untrap_prob",a0);},
teleport_trap_js_cnv_trap_obj__deps:["$teleportTrapCall"],teleport_trap_js_cnv_trap_obj__sig:"viipi",
teleport_trap_js_cnv_trap_obj:function(a0,a1,a2,a3){teleportTrapCall("cnv_trap_obj",a0,a1,a2,a3);},
teleport_trap_js_into_vs_onto__deps:["$teleportTrapCall"],teleport_trap_js_into_vs_onto__sig:"ii",
teleport_trap_js_into_vs_onto:function(a0){return teleportTrapCall("into_vs_onto",a0);},
teleport_trap_js_move_into_trap__deps:["$teleportTrapCall"],teleport_trap_js_move_into_trap__sig:"vp",
teleport_trap_js_move_into_trap:function(a0){teleportTrapCall("move_into_trap",a0);},
teleport_trap_js_try_disarm__deps:["$teleportTrapCall"],teleport_trap_js_try_disarm__sig:"ipi",
teleport_trap_js_try_disarm:function(a0,a1){return teleportTrapCall("try_disarm",a0,a1);},
teleport_trap_js_reward_untrap__deps:["$teleportTrapCall"],teleport_trap_js_reward_untrap__sig:"vpp",
teleport_trap_js_reward_untrap:function(a0,a1){teleportTrapCall("reward_untrap",a0,a1);},
teleport_trap_js_disarm_holdingtrap__deps:["$teleportTrapCall"],teleport_trap_js_disarm_holdingtrap__sig:"ip",
teleport_trap_js_disarm_holdingtrap:function(a0){return teleportTrapCall("disarm_holdingtrap",a0);},
teleport_trap_js_disarm_landmine__deps:["$teleportTrapCall"],teleport_trap_js_disarm_landmine__sig:"ip",
teleport_trap_js_disarm_landmine:function(a0){return teleportTrapCall("disarm_landmine",a0);},
teleport_trap_js_unsqueak_ok__deps:["$teleportTrapCall"],teleport_trap_js_unsqueak_ok__sig:"ip",
teleport_trap_js_unsqueak_ok:function(a0){return teleportTrapCall("unsqueak_ok",a0);},
teleport_trap_js_disarm_squeaky_board__deps:["$teleportTrapCall"],teleport_trap_js_disarm_squeaky_board__sig:"ip",
teleport_trap_js_disarm_squeaky_board:function(a0){return teleportTrapCall("disarm_squeaky_board",a0);},
teleport_trap_js_disarm_shooting_trap__deps:["$teleportTrapCall"],teleport_trap_js_disarm_shooting_trap__sig:"ipi",
teleport_trap_js_disarm_shooting_trap:function(a0,a1){return teleportTrapCall("disarm_shooting_trap",a0,a1);},
teleport_trap_js_try_lift__deps:["$teleportTrapCall"],teleport_trap_js_try_lift__sig:"ippii",
teleport_trap_js_try_lift:function(a0,a1,a2,a3){return teleportTrapCall("try_lift",a0,a1,a2,a3);},
teleport_trap_js_help_monster_out__deps:["$teleportTrapCall"],teleport_trap_js_help_monster_out__sig:"ipp",
teleport_trap_js_help_monster_out:function(a0,a1){return teleportTrapCall("help_monster_out",a0,a1);},
teleport_trap_js_disarm_box__deps:["$teleportTrapCall"],teleport_trap_js_disarm_box__sig:"vpii",
teleport_trap_js_disarm_box:function(a0,a1,a2){teleportTrapCall("disarm_box",a0,a1,a2);},
teleport_trap_js_untrap_box__deps:["$teleportTrapCall"],teleport_trap_js_untrap_box__sig:"vpii",
teleport_trap_js_untrap_box:function(a0,a1,a2){teleportTrapCall("untrap_box",a0,a1,a2);},
teleport_trap_js_untrap__deps:["$teleportTrapCall"],teleport_trap_js_untrap__sig:"iiiip",
teleport_trap_js_untrap:function(a0,a1,a2,a3){return teleportTrapCall("untrap",a0,a1,a2,a3);},
teleport_trap_js_openholdingtrap__deps:["$teleportTrapCall"],teleport_trap_js_openholdingtrap__sig:"ipp",
teleport_trap_js_openholdingtrap:function(a0,a1){return teleportTrapCall("openholdingtrap",a0,a1);},
teleport_trap_js_closeholdingtrap__deps:["$teleportTrapCall"],teleport_trap_js_closeholdingtrap__sig:"ipp",
teleport_trap_js_closeholdingtrap:function(a0,a1){return teleportTrapCall("closeholdingtrap",a0,a1);},
teleport_trap_js_openfallingtrap__deps:["$teleportTrapCall"],teleport_trap_js_openfallingtrap__sig:"ipip",
teleport_trap_js_openfallingtrap:function(a0,a1,a2){return teleportTrapCall("openfallingtrap",a0,a1,a2);},
teleport_trap_js_chest_trap__deps:["$teleportTrapCall"],teleport_trap_js_chest_trap__sig:"ipii",
teleport_trap_js_chest_trap:function(a0,a1,a2){return teleportTrapCall("chest_trap",a0,a1,a2);},
teleport_trap_js_t_at__deps:["$teleportTrapCall"],teleport_trap_js_t_at__sig:"pii",
teleport_trap_js_t_at:function(a0,a1){return BigInt(teleportTrapCall("t_at",a0,a1)??0);},
teleport_trap_js_count_traps__deps:["$teleportTrapCall"],teleport_trap_js_count_traps__sig:"ii",
teleport_trap_js_count_traps:function(a0){return teleportTrapCall("count_traps",a0);},
teleport_trap_js_deltrap__deps:["$teleportTrapCall"],teleport_trap_js_deltrap__sig:"vp",
teleport_trap_js_deltrap:function(a0){teleportTrapCall("deltrap",a0);},
teleport_trap_js_conjoined_pits__deps:["$teleportTrapCall"],teleport_trap_js_conjoined_pits__sig:"ippi",
teleport_trap_js_conjoined_pits:function(a0,a1,a2){return teleportTrapCall("conjoined_pits",a0,a1,a2);},
teleport_trap_js_clear_conjoined_pits__deps:["$teleportTrapCall"],teleport_trap_js_clear_conjoined_pits__sig:"vp",
teleport_trap_js_clear_conjoined_pits:function(a0){teleportTrapCall("clear_conjoined_pits",a0);},
teleport_trap_js_adj_nonconjoined_pit__deps:["$teleportTrapCall"],teleport_trap_js_adj_nonconjoined_pit__sig:"ip",
teleport_trap_js_adj_nonconjoined_pit:function(a0){return teleportTrapCall("adj_nonconjoined_pit",a0);},
teleport_trap_js_uteetering_at_seen_pit__deps:["$teleportTrapCall"],teleport_trap_js_uteetering_at_seen_pit__sig:"ip",
teleport_trap_js_uteetering_at_seen_pit:function(a0){return teleportTrapCall("uteetering_at_seen_pit",a0);},
teleport_trap_js_uescaped_shaft__deps:["$teleportTrapCall"],teleport_trap_js_uescaped_shaft__sig:"ip",
teleport_trap_js_uescaped_shaft:function(a0){return teleportTrapCall("uescaped_shaft",a0);},
teleport_trap_js_delfloortrap__deps:["$teleportTrapCall"],teleport_trap_js_delfloortrap__sig:"ip",
teleport_trap_js_delfloortrap:function(a0){return teleportTrapCall("delfloortrap",a0);},
teleport_trap_js_b_trapped__deps:["$teleportTrapCall"],teleport_trap_js_b_trapped__sig:"vpi",
teleport_trap_js_b_trapped:function(a0,a1){teleportTrapCall("b_trapped",a0,a1);},
teleport_trap_js_thitm__deps:["$teleportTrapCall"],teleport_trap_js_thitm__sig:"iippii",
teleport_trap_js_thitm:function(a0,a1,a2,a3,a4){return teleportTrapCall("thitm",a0,a1,a2,a3,a4);},
teleport_trap_js_unconscious__deps:["$teleportTrapCall"],teleport_trap_js_unconscious__sig:"i",
teleport_trap_js_unconscious:function(){return teleportTrapCall("unconscious");},
teleport_trap_js_lava_effects__deps:["$teleportTrapCall"],teleport_trap_js_lava_effects__sig:"i",
teleport_trap_js_lava_effects:function(){return teleportTrapCall("lava_effects");},
teleport_trap_js_sink_into_lava__deps:["$teleportTrapCall"],teleport_trap_js_sink_into_lava__sig:"v",
teleport_trap_js_sink_into_lava:function(){teleportTrapCall("sink_into_lava");},
teleport_trap_js_sokoban_guilt__deps:["$teleportTrapCall"],teleport_trap_js_sokoban_guilt__sig:"v",
teleport_trap_js_sokoban_guilt:function(){teleportTrapCall("sokoban_guilt");},
teleport_trap_js_maybe_finish_sokoban__deps:["$teleportTrapCall"],teleport_trap_js_maybe_finish_sokoban__sig:"v",
teleport_trap_js_maybe_finish_sokoban:function(){teleportTrapCall("maybe_finish_sokoban");},
teleport_trap_js_trapname__deps:["$teleportTrapCall"],teleport_trap_js_trapname__sig:"pii",
teleport_trap_js_trapname:function(a0,a1){return BigInt(teleportTrapCall("trapname",a0,a1)??0);},
teleport_trap_js_ignite_items__deps:["$teleportTrapCall"],teleport_trap_js_ignite_items__sig:"vp",
teleport_trap_js_ignite_items:function(a0){teleportTrapCall("ignite_items",a0);},
teleport_trap_js_trap_ice_effects__deps:["$teleportTrapCall"],teleport_trap_js_trap_ice_effects__sig:"viii",
teleport_trap_js_trap_ice_effects:function(a0,a1,a2){teleportTrapCall("trap_ice_effects",a0,a1,a2);},
teleport_trap_js_trap_sanity_check__deps:["$teleportTrapCall"],teleport_trap_js_trap_sanity_check__sig:"v",
teleport_trap_js_trap_sanity_check:function(){teleportTrapCall("trap_sanity_check");},
});
