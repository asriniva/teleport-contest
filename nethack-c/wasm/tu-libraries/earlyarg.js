// Typed EARLYARG ABI only; original options and dump algorithms remain JS.
addToLibrary({
  $teleportEarlyargServices__deps: ['teleport_earlyarg_storage', 'teleport_earlyarg_global', 'teleport_earlyarg_usagehelp', 'teleport_earlyarg_stdout', 'teleport_earlyarg_config_error', 'teleport_earlyarg_error', 'teleport_earlyarg_free', 'teleport_earlyarg_raw_print', 'teleport_earlyarg_raw_p', 'teleport_earlyarg_raw_pp', 'teleport_earlyarg_raw_pipip', 'teleport_earlyarg_snprintf', 'teleport_earlyarg_literal_storage', 'teleport_earlyarg_literal_capacity', 'strchr', 'strlen', 'strncmp', 'strcmp', 'eos', 'dupstr', 'config_error_init', 'config_error_done', 'nh_terminate', 'chdirx', 'genl_display_file', 'initoptions', 'panictrace_setsignals', 'whoami', 'prscore', 'match_optname', 'dump_version_info', 'early_version_info', 'dump_mongen', 'dump_weights', 'crashreport_bidshow', 'strncmpi', 'isspace', 'dump_all_glyphids', '$lengthBytesUTF8', '$stringToUTF8', '$stackAlloc', '$stackSave', '$stackRestore'],
  $teleportEarlyargServices:function(){
    var state=Module['teleportEarlyargLiterals']||={next:0,strings:new Map()};
    var pointer=value=>BigInt(value?.address??value??0);
    var literal=value=>{
      if(state.strings.has(value))return state.strings.get(value);
      var size=lengthBytesUTF8(value)+1;
      if(state.next+size>Number(_teleport_earlyarg_literal_capacity()))throw new Error('Review changed EARLYARG literal corpus');
      var at=Number(_teleport_earlyarg_literal_storage())+state.next;
      stringToUTF8(value,at,size);state.next+=size;state.strings.set(value,at);return at;
    };
    var text=value=>typeof value==='string'?BigInt(literal(value)):pointer(value);
    return {
      moduleKey:Module,heap:()=>HEAPU8,literal,
      stackAlloc:size=>Number(stackAlloc(size)),
      storage:index=>Number(_teleport_earlyarg_storage(index)),global:index=>Number(_teleport_earlyarg_global(index)),
      usageHelp:()=>Number(_teleport_earlyarg_usagehelp()),stdout:()=>Number(_teleport_earlyarg_stdout()),
      config_error_add:(format,arg)=>_teleport_earlyarg_config_error(text(format),text(arg)),
      error:format=>_teleport_earlyarg_error(text(format)),
      free:value=>_teleport_earlyarg_free(pointer(value)),
      raw_print:value=>_teleport_earlyarg_raw_print(text(value)),
      raw_printf:(format,...args)=>{
        if(args.length===1)return _teleport_earlyarg_raw_p(text(format),text(args[0]));
        if(args.length===2)return _teleport_earlyarg_raw_pp(text(format),text(args[0]),text(args[1]));
        if(args.length===5)return _teleport_earlyarg_raw_pipip(text(format),text(args[0]),Number(args[1])|0,text(args[2]),Number(args[3])|0,text(args[4]));
        throw new Error('Unexpected original EARLYARG raw_printf shape');
      },
      Snprintf:(out,size,format,value)=>_teleport_earlyarg_snprintf(pointer(out),BigInt(size),text(format),Number(value)|0),
      strchr:(a,b)=>Number(_strchr(text(a),Number(b)|0)),
      strlen:(a)=>Number(_strlen(text(a))),
      strncmp:(a,b,c)=>_strncmp(text(a),text(b),BigInt.asUintN(64,BigInt(c))),
      strcmp:(a,b)=>_strcmp(text(a),text(b)),
      eos:(a)=>Number(_eos(text(a))),
      dupstr:(a)=>Number(_dupstr(text(a))),
      config_error_init:(a,b,c)=>_config_error_init(Number(a)<<24>>24,text(b),Number(c)<<24>>24),
      config_error_done:()=>_config_error_done(),
      nh_terminate:(a)=>_nh_terminate(Number(a)|0),
      chdirx:(a,b)=>_chdirx(text(a),Number(b)<<24>>24),
      genl_display_file:(a,b)=>_genl_display_file(text(a),Number(b)<<24>>24),
      initoptions:()=>_initoptions(),
      panictrace_setsignals:(a)=>_panictrace_setsignals(Number(a)<<24>>24),
      whoami:()=>_whoami(),
      prscore:(a,b)=>_prscore(Number(a)|0,text(b)),
      match_optname:(a,b,c,d)=>_match_optname(text(a),text(b),Number(c)|0,Number(d)<<24>>24),
      dump_version_info:()=>_dump_version_info(),
      early_version_info:(a)=>_early_version_info(Number(a)<<24>>24),
      dump_mongen:()=>_dump_mongen(),
      dump_weights:()=>_dump_weights(),
      crashreport_bidshow:()=>_crashreport_bidshow(),
      strncmpi:(a,b,c)=>_strncmpi(text(a),text(b),Number(c)|0),
      isspace:(a)=>_isspace(Number(a)|0),
      dump_all_glyphids:(a)=>_dump_all_glyphids(text(a)),
    };
  },
  $teleportEarlyargInit__deps:['$teleportEarlyargServices','$addOnInit'],
  $teleportEarlyargInit__postset:"addOnInit(() => Module['nethackPorted'].initializeEarlyarg(teleportEarlyargServices()));",
  $teleportEarlyargInit:0,
  $teleportEarlyargCall__deps:['$teleportEarlyargServices','$teleportEarlyargInit','$stackSave','$stackRestore'],
  $teleportEarlyargCall:function(name,...args){var saved=stackSave();try{return Module['nethackPorted'].earlyarg(teleportEarlyargServices(),name,...args);}finally{stackRestore(saved);}},
  early_options__deps:['$teleportEarlyargCall'],early_options__sig:'vppp',
  early_options:function(a,b,c){teleportEarlyargCall('early_options' ,a,b,c);},
  after_opt_showpaths__deps:['$teleportEarlyargCall'],after_opt_showpaths__sig:'vp',
  after_opt_showpaths:function(a){teleportEarlyargCall('after_opt_showpaths' ,a);},
  argcheck__deps:['$teleportEarlyargCall'],argcheck__sig:'iipi',
  argcheck:function(a,b,c){return teleportEarlyargCall('argcheck' ,a,b,c);},
  dump_glyphids__deps:['$teleportEarlyargCall'],dump_glyphids__sig:'v',
  dump_glyphids:function(){teleportEarlyargCall('dump_glyphids');},
  teleport_earlyarg_test_lopt__deps:['$teleportEarlyargCall'],teleport_earlyarg_test_lopt__sig:'ppipppp',
  teleport_earlyarg_test_lopt:function(a,b,c,d,e,f){return teleportEarlyargCall('lopt' ,a,b,c,d,e,f);},
  teleport_earlyarg_test_consume__deps:['$teleportEarlyargCall'],teleport_earlyarg_test_consume__sig:'vipp',
  teleport_earlyarg_test_consume:function(a,b,c){teleportEarlyargCall('consume_arg' ,a,b,c);},
  teleport_earlyarg_test_consume_two__deps:['$teleportEarlyargCall'],teleport_earlyarg_test_consume_two__sig:'vipp',
  teleport_earlyarg_test_consume_two:function(a,b,c){teleportEarlyargCall('consume_two_args' ,a,b,c);},
  teleport_earlyarg_test_terminate__deps:['$teleportEarlyargCall'],teleport_earlyarg_test_terminate__sig:'v',
  teleport_earlyarg_test_terminate:function(){teleportEarlyargCall('opt_terminate');},
  teleport_earlyarg_test_usage__deps:['$teleportEarlyargCall'],teleport_earlyarg_test_usage__sig:'vp',
  teleport_earlyarg_test_usage:function(a){teleportEarlyargCall('opt_usage' ,a);},
  teleport_earlyarg_test_scores__deps:['$teleportEarlyargCall'],teleport_earlyarg_test_scores__sig:'vipp',
  teleport_earlyarg_test_scores:function(a,b,c){teleportEarlyargCall('scores_only' ,a,b,c);},
  teleport_earlyarg_test_debug__deps:['$teleportEarlyargCall'],teleport_earlyarg_test_debug__sig:'vp',
  teleport_earlyarg_test_debug:function(a){teleportEarlyargCall('debug_fields' ,a);},
  teleport_earlyarg_test_enums__deps:['$teleportEarlyargCall'],teleport_earlyarg_test_enums__sig:'v',
  teleport_earlyarg_test_enums:function(){teleportEarlyargCall('dump_enums');},
});
