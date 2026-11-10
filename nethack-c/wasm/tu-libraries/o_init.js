// Native ABI only; original object initialization/discovery algorithms are JS.
addToLibrary({
  $teleportOInitServices__deps: ['teleport_o_init_global', 'teleport_o_init_class_bit', 'teleport_o_init_set_class_bit', 'teleport_o_init_object_bit', 'teleport_o_init_set_object_bit', 'teleport_o_init_comparator_pointer', 'teleport_o_init_qsort', 'teleport_o_init_free', 'teleport_o_init_wait', 'teleport_o_init_create_window', 'teleport_o_init_clear_window', 'teleport_o_init_start_menu', 'teleport_o_init_end_menu', 'teleport_o_init_display_window', 'teleport_o_init_destroy_window', 'teleport_o_init_putstr', 'teleport_o_init_win_message', 'teleport_o_init_nul_glyph', 'teleport_o_init_y_n', 'teleport_o_init_rn2', 'teleport_o_init_raw_printf', 'teleport_o_init_panic', 'teleport_o_init_impossible0', 'teleport_o_init_impossible_string', 'teleport_o_init_impossible_name', 'teleport_o_init_impossible_probability', 'teleport_o_init_you', 'teleport_o_init_pline', 'teleport_o_init_format_ints', 'teleport_o_init_format_strings', 'teleport_o_init_format_string_chars', 'teleport_o_init_assert', 'teleport_o_init_strlen', 'teleport_o_init_literal_storage', 'teleport_o_init_literal_capacity', 'teleport_o_init_sfo_int', 'teleport_o_init_sfo_short', 'teleport_o_init_sfo_objclass', 'teleport_o_init_sfo_unsigned', 'teleport_o_init_sfo_char', 'teleport_o_init_sfi_int', 'teleport_o_init_sfi_short', 'teleport_o_init_sfi_objclass', 'teleport_o_init_sfi_unsigned', 'teleport_o_init_sfi_char', 'ledger_no', 'maxledgerno', 'strcmp', 'strcpy', 'strcat', 'strlen', 'strncat', 'strchr', 'strrchr', 'strstri', 'strsubst', 'eos', 'alloc', 'dupstr', 'memset', 'Japanese_item_name', 'exercise', 'gem_learned', 'update_inventory', 'loot_classify', 'obj_typename', 'append_price_quote', 'add_menu', 'add_menu_heading', 'add_menu_str', 'select_menu', 'let_to_name', 'disp_artifact_discoveries', 'dump_artifact_info', 'def_char_to_objclass', 'strkitten', 'yn_function', 'visctrl', 'objtyp_is_callable', 'docall', 'lowc', 'upstart', 'strncmpi', '$lengthBytesUTF8', '$stringToUTF8', '$stackAlloc', '$stackSave', '$stackRestore'],
  $teleportOInitServices: function() {
    var state = Module['teleportOInitCache'] ||= { next: 0, strings: new Map() };
    var pointer = value => BigInt(value ? value.address ?? value : 0);
    var byte = value => Number(BigInt.asIntN(8,BigInt(value)));
    var literal = value => {
      if (state.strings.has(value)) return state.strings.get(value);
      var size = lengthBytesUTF8(value) + 1;
      if (state.next + size > Number(_teleport_o_init_literal_capacity())) throw new Error('Review changed o_init literal corpus');
      var at = Number(_teleport_o_init_literal_storage()) + state.next;
      stringToUTF8(value,at,size); state.next += size; state.strings.set(value,at); return at;
    };
    var text = value => typeof value === 'string' ? BigInt(literal(value)) : pointer(value);
    var callers = ['randomize_gem_colors','shuffle','init_objects'];
    var callerIndex = value => {
      var index = typeof value === 'string' ? callers.indexOf(value) : value;
      if (!Number.isInteger(index) || index < 0 || index >= callers.length) throw new Error('Unexpected original o_init RNG caller');
      return index;
    };
    var services = {
      moduleKey: Module, heap: () => HEAPU8, literal,
      stackAlloc: size => Number(stackAlloc(size)), stackSave: () => stackSave(), stackRestore: saved => stackRestore(saved),
      global: index => Number(_teleport_o_init_global(index)),
      classBit: (obj,index) => _teleport_o_init_class_bit(pointer(obj),index),
      setClassBit: (obj,index,value) => _teleport_o_init_set_class_bit(pointer(obj),index,Number(value)>>>0),
      objectBit: (obj,index) => _teleport_o_init_object_bit(pointer(obj),index),
      setObjectBit: (obj,index,value) => _teleport_o_init_set_object_bit(pointer(obj),index,Number(value)>>>0),
      comparatorPointer: () => _teleport_o_init_comparator_pointer(),
      qsort: (base,count,size) => _teleport_o_init_qsort(pointer(base),BigInt.asUintN(64,BigInt(count)),BigInt.asUintN(64,BigInt(size))),
      free: value => _teleport_o_init_free(pointer(value)), wait_synch: () => _teleport_o_init_wait(),
      create_nhwindow: type => _teleport_o_init_create_window(type), clear_nhwindow: win => _teleport_o_init_clear_window(win),
      start_menu: (win,flags) => _teleport_o_init_start_menu(win,BigInt.asUintN(64,BigInt(flags))),
      end_menu: (win,prompt) => _teleport_o_init_end_menu(win,text(prompt)),
      display_nhwindow: (win,blocking) => _teleport_o_init_display_window(win,byte(blocking)),
      destroy_nhwindow: win => _teleport_o_init_destroy_window(win),
      putstr: (win,attr,value) => _teleport_o_init_putstr(win,attr,text(value)),
      winMessage: () => _teleport_o_init_win_message(), nulGlyphInfo: () => Number(_teleport_o_init_nul_glyph()),
      y_n: query => _teleport_o_init_y_n(text(query)),
      rn2: (bound,line,caller) => _teleport_o_init_rn2(bound,line,callerIndex(caller)),
      assert: condition => { if (!condition) _teleport_o_init_assert(); },
      Strlen: value => _teleport_o_init_strlen(text(value))>>>0,
      strcmpi: (a,b) => _strncmpi(text(a),text(b),-1),
      raw_printf: (format,a,b,c) => _teleport_o_init_raw_printf(text(format),a,b,c),
      panic: (format,a,b) => _teleport_o_init_panic(text(format),a,b),
      impossible: (format,...args) => {
        if (!args.length) return _teleport_o_init_impossible0(text(format));
        if (args.length === 1) return _teleport_o_init_impossible_string(text(format),text(args[0]));
        if (args.length === 3) return _teleport_o_init_impossible_probability(text(format),text(args[0]),args[1],args[2]);
        return _teleport_o_init_impossible_name(text(format),args[0],text(args[1]),text(args[2]),text(args[3]));
      },
      You: (format,value) => _teleport_o_init_you(text(format),text(value)), pline: format => _teleport_o_init_pline(text(format)),
      Sprintf: (out,format,...args) => {
        if (args.length === 4) return _teleport_o_init_format_string_chars(pointer(out),text(format),text(args[0]),args[1],args[2],args[3]);
        if (args.length === 3 || format === '%c') return _teleport_o_init_format_ints(pointer(out),text(format),args[0],args[1]??0,args[2]??0);
        return _teleport_o_init_format_strings(pointer(out),text(format),text(args[0]),text(args[1]));
      },
      Sfo_int: (fp,value,tag) => _teleport_o_init_sfo_int(pointer(fp),pointer(value),text(tag)),
      Sfo_short: (fp,value,tag) => _teleport_o_init_sfo_short(pointer(fp),pointer(value),text(tag)),
      Sfo_objclass: (fp,value,tag) => _teleport_o_init_sfo_objclass(pointer(fp),pointer(value),text(tag)),
      Sfo_unsigned: (fp,value,tag) => _teleport_o_init_sfo_unsigned(pointer(fp),pointer(value),text(tag)),
      Sfo_char: (fp,value,tag,count) => _teleport_o_init_sfo_char(pointer(fp),pointer(value),text(tag),Number(BigInt.asIntN(32,BigInt(count)))),
      Sfi_int: (fp,value,tag) => _teleport_o_init_sfi_int(pointer(fp),pointer(value),text(tag)),
      Sfi_short: (fp,value,tag) => _teleport_o_init_sfi_short(pointer(fp),pointer(value),text(tag)),
      Sfi_objclass: (fp,value,tag) => _teleport_o_init_sfi_objclass(pointer(fp),pointer(value),text(tag)),
      Sfi_unsigned: (fp,value,tag) => _teleport_o_init_sfi_unsigned(pointer(fp),pointer(value),text(tag)),
      Sfi_char: (fp,value,tag,count) => _teleport_o_init_sfi_char(pointer(fp),pointer(value),text(tag),Number(BigInt.asIntN(32,BigInt(count)))),
      ledger_no: (level) => _ledger_no(pointer(level)),
      maxledgerno: () => _maxledgerno(),
      strcmp: (a,b) => _strcmp(text(a),text(b)),
      strcpy: (out,value) => Number(_strcpy(pointer(out),text(value))),
      strcat: (out,value) => Number(_strcat(pointer(out),text(value))),
      strlen: (value) => _strlen(text(value)),
      strncat: (out,value,size) => Number(_strncat(pointer(out),text(value),BigInt.asUintN(64,BigInt(size)))),
      strchr: (value,ch) => Number(_strchr(text(value),ch)),
      strrchr: (value,ch) => Number(_strrchr(text(value),ch)),
      strstri: (value,part) => Number(_strstri(text(value),text(part))),
      strsubst: (out,old,replacement) => _strsubst(pointer(out),text(old),text(replacement)),
      eos: (value) => Number(_eos(pointer(value))),
      alloc: (size) => Number(_alloc(Number(size)>>>0)),
      dupstr: (value) => Number(_dupstr(text(value))),
      memset: (out,value,size) => Number(_memset(pointer(out),value,BigInt(size))),
      Japanese_item_name: (type,name) => Number(_Japanese_item_name(type,text(name))),
      exercise: (attr,flag) => _exercise(attr,byte(flag)),
      gem_learned: (type) => _gem_learned(type),
      update_inventory: () => _update_inventory(),
      loot_classify: (cookie,obj) => _loot_classify(pointer(cookie),pointer(obj)),
      obj_typename: (type) => Number(_obj_typename(type)),
      append_price_quote: (out,end,type) => _append_price_quote(pointer(out),pointer(end),type),
      add_menu: (win,glyph,any,accelerator,group,attr,color,label,flags) => _add_menu(win,pointer(glyph),pointer(any),byte(accelerator),byte(group),attr,color,text(label),flags>>>0),
      add_menu_heading: (win,label) => _add_menu_heading(win,text(label)),
      add_menu_str: (win,label) => _add_menu_str(win,text(label)),
      select_menu: (win,how,selected) => _select_menu(win,how,pointer(selected)),
      let_to_name: (oclass,unpaid,unidentified) => Number(_let_to_name(byte(oclass),byte(unpaid),byte(unidentified))),
      disp_artifact_discoveries: (win) => _disp_artifact_discoveries(win),
      dump_artifact_info: (win) => _dump_artifact_info(win),
      def_char_to_objclass: (ch) => _def_char_to_objclass(byte(ch)),
      strkitten: (out,ch) => Number(_strkitten(pointer(out),byte(ch))),
      yn_function: (query,choices,default_,record) => _yn_function(text(query),text(choices),byte(default_),byte(record)),
      visctrl: (ch) => Number(_visctrl(byte(ch))),
      objtyp_is_callable: (type) => _objtyp_is_callable(type),
      docall: (obj) => _docall(pointer(obj)),
      lowc: (ch) => _lowc(byte(ch)),
      upstart: (out) => Number(_upstart(pointer(out))),
    };
    services.Strcpy = services.strcpy; services.Strcat = services.strcat;
    return services;
  },
  $teleportOInitCall__deps: ['$teleportOInitServices','$stackSave','$stackRestore'],
  $teleportOInitCall: function(name,...args) {
    var saved = stackSave();
    try { return Module['nethackPorted'].o_init(teleportOInitServices(),name,...args); }
    finally { stackRestore(saved); }
  },
  init_objects__deps: ['$teleportOInitCall'], init_objects__sig: 'v',
  init_objects: function() { teleportOInitCall('init_objects'); },
  init_oclass_probs__deps: ['$teleportOInitCall'], init_oclass_probs__sig: 'v',
  init_oclass_probs: function() { teleportOInitCall('init_oclass_probs'); },
  obj_shuffle_range__deps: ['$teleportOInitCall'], obj_shuffle_range__sig: 'vipp',
  obj_shuffle_range: function(type,low,high) { teleportOInitCall('obj_shuffle_range',type,low,high); },
  objdescr_is__deps: ['$teleportOInitCall'], objdescr_is__sig: 'ipp',
  objdescr_is: function(obj,description) { return teleportOInitCall('objdescr_is',obj,description); },
  oinit__deps: ['$teleportOInitCall'], oinit__sig: 'v',
  oinit: function() { teleportOInitCall('oinit'); },
  savenames__deps: ['$teleportOInitCall'], savenames__sig: 'vp',
  savenames: function(fp) { teleportOInitCall('savenames',fp); },
  restnames__deps: ['$teleportOInitCall'], restnames__sig: 'vp',
  restnames: function(fp) { teleportOInitCall('restnames',fp); },
  observe_object__deps: ['$teleportOInitCall'], observe_object__sig: 'vp',
  observe_object: function(obj) { teleportOInitCall('observe_object',obj); },
  discover_object__deps: ['$teleportOInitCall'], discover_object__sig: 'viiii',
  discover_object: function(type,known,encountered,credit) { teleportOInitCall('discover_object',type,known<<24>>24,encountered<<24>>24,credit<<24>>24); },
  undiscover_object__deps: ['$teleportOInitCall'], undiscover_object__sig: 'vi',
  undiscover_object: function(type) { teleportOInitCall('undiscover_object',type); },
  interesting_to_discover__deps: ['$teleportOInitCall'], interesting_to_discover__sig: 'ii',
  interesting_to_discover: function(type) { return teleportOInitCall('interesting_to_discover',type); },
  choose_disco_sort__deps: ['$teleportOInitCall'], choose_disco_sort__sig: 'ii',
  choose_disco_sort: function(mode) { return teleportOInitCall('choose_disco_sort',mode); },
  dodiscovered__deps: ['$teleportOInitCall'], dodiscovered__sig: 'i',
  dodiscovered: function() { return teleportOInitCall('dodiscovered'); },
  doclassdisco__deps: ['$teleportOInitCall'], doclassdisco__sig: 'i',
  doclassdisco: function() { return teleportOInitCall('doclassdisco'); },
  rename_disco__deps: ['$teleportOInitCall'], rename_disco__sig: 'v',
  rename_disco: function() { teleportOInitCall('rename_disco'); },
  get_sortdisco__deps: ['$teleportOInitCall'], get_sortdisco__sig: 'vpi',
  get_sortdisco: function(out,config) { teleportOInitCall('get_sortdisco',out,config<<24>>24); },
  teleport_o_init_compare__deps: ['$teleportOInitCall'], teleport_o_init_compare__sig: 'ipp',
  teleport_o_init_compare: function(a,b) { return teleportOInitCall('discovered_cmp',a,b); },
  teleport_o_init_test_gems__deps: ['$teleportOInitCall'], teleport_o_init_test_gems__sig: 'vp',
  teleport_o_init_test_gems: function(level) { teleportOInitCall('setgemprobs',level); },
  teleport_o_init_test_colors__deps: ['$teleportOInitCall'], teleport_o_init_test_colors__sig: 'v',
  teleport_o_init_test_colors: function() { teleportOInitCall('randomize_gem_colors'); },
  teleport_o_init_test_shuffle__deps: ['$teleportOInitCall'], teleport_o_init_test_shuffle__sig: 'viii',
  teleport_o_init_test_shuffle: function(low,high,material) { teleportOInitCall('shuffle',low,high,material<<24>>24); },
  teleport_o_init_test_all__deps: ['$teleportOInitCall'], teleport_o_init_test_all__sig: 'v',
  teleport_o_init_test_all: function() { teleportOInitCall('shuffle_all'); },
  teleport_o_init_test_cmp__deps: ['$teleportOInitCall'], teleport_o_init_test_cmp__sig: 'ipp',
  teleport_o_init_test_cmp: function(a,b) { return teleportOInitCall('discovered_cmp',a,b); },
  teleport_o_init_test_sortloot__deps: ['$teleportOInitCall'], teleport_o_init_test_sortloot__sig: 'pip',
  teleport_o_init_test_sortloot: function(type,out) { return teleportOInitCall('sortloot_descr',type,out); },
  teleport_o_init_test_typename__deps: ['$teleportOInitCall'], teleport_o_init_test_typename__sig: 'pi',
  teleport_o_init_test_typename: function(type) { return teleportOInitCall('disco_typename',type); },
  teleport_o_init_test_append__deps: ['$teleportOInitCall'], teleport_o_init_test_append__sig: 'vpi',
  teleport_o_init_test_append: function(out,type) { teleportOInitCall('disco_append_typename',out,type); },
  teleport_o_init_test_uniq__deps: ['$teleportOInitCall'], teleport_o_init_test_uniq__sig: 'vip',
  teleport_o_init_test_uniq: function(type,out) { teleportOInitCall('disco_fmt_uniq',type,out); },
  teleport_o_init_test_output__deps: ['$teleportOInitCall'], teleport_o_init_test_output__sig: 'vipii',
  teleport_o_init_test_output: function(win,lines,count,loot) { teleportOInitCall('disco_output_sorted',win,lines,count,loot<<24>>24); },
  teleport_o_init_test_class__deps: ['$teleportOInitCall'], teleport_o_init_test_class__sig: 'pip',
  teleport_o_init_test_class: function(oclass,out) { return teleportOInitCall('oclass_to_name',oclass<<24>>24,out); },
});
