// Native storage and typed calls only; color tables, parsing and menus are JS.
addToLibrary({
  $teleportColorattServices__deps: ['teleport_coloratt_storage', 'teleport_coloratt_global', 'teleport_coloratt_regex_id', 'teleport_coloratt_hexdd', 'teleport_coloratt_nul_glyphinfo', 'teleport_coloratt_free', 'teleport_coloratt_isspace', 'teleport_coloratt_create_window', 'teleport_coloratt_start_menu', 'teleport_coloratt_end_menu', 'teleport_coloratt_destroy_window', 'teleport_coloratt_format', 'teleport_coloratt_config_error', 'teleport_coloratt_scan', 'teleport_coloratt_snprintf_rgb', 'teleport_coloratt_snprintf_string', 'teleport_coloratt_assert', 'teleport_coloratt_literal_storage', 'teleport_coloratt_literal_capacity', 'alloc', 'dupstr', 'strlen', 'strncmpi', 'strncpy', 'strchr', 'strstri', 'memcpy', 'fuzzymatch', 'atoi', 'mungspaces', 'regex_init', 'regex_compile', 'regex_error_desc', 'regex_free', 'add_menu', 'select_menu', '$lengthBytesUTF8', '$stringToUTF8', '$stackAlloc', '$stackSave', '$stackRestore'],
  $teleportColorattServices: function() {
    var state = Module['teleportColorattCache'] ||= { next: 0, strings: new Map() };
    var pointer = value => BigInt(value ? value.address ?? value : 0);
    var byte = value => Number(BigInt.asIntN(8, BigInt(value)));
    var literal = value => {
      if (state.strings.has(value)) return state.strings.get(value);
      var size = lengthBytesUTF8(value) + 1;
      if (state.next + size > Number(_teleport_coloratt_literal_capacity())) throw new Error('Review changed color/attribute literal corpus');
      var at = Number(_teleport_coloratt_literal_storage()) + state.next;
      stringToUTF8(value, at, size); state.next += size; state.strings.set(value, at); return at;
    };
    var text = value => typeof value === 'string' ? BigInt(literal(value)) : pointer(value);
    return {
      moduleKey: state, heap: () => HEAPU8, literal,
      stackAlloc: size => Number(stackAlloc(size)), stackSave: () => stackSave(), stackRestore: saved => stackRestore(saved),
      storage: index => Number(_teleport_coloratt_storage(index)), global: index => Number(_teleport_coloratt_global(index)),
      regexId: () => Number(_teleport_coloratt_regex_id()), hexdd: () => Number(_teleport_coloratt_hexdd()),
      nulGlyphInfo: () => Number(_teleport_coloratt_nul_glyphinfo()),
      free: value => _teleport_coloratt_free(pointer(value)), isspace: ch => _teleport_coloratt_isspace(ch),
      create_nhwindow: type => _teleport_coloratt_create_window(type),
      start_menu: (win, behavior) => _teleport_coloratt_start_menu(win, BigInt.asUintN(64, BigInt(behavior))),
      end_menu: (win, prompt) => _teleport_coloratt_end_menu(win, text(prompt)),
      destroy_nhwindow: win => _teleport_coloratt_destroy_window(win),
      Sprintf: (out, format, a, b) => _teleport_coloratt_format(pointer(out), text(format), text(a), text(b)),
      config_error_add: (format, a, b) => _teleport_coloratt_config_error(text(format), text(a), text(b)),
      sscanf: (value, format, r, g, b, extra) => _teleport_coloratt_scan(text(value), text(format), pointer(r), pointer(g), pointer(b), pointer(extra)),
      Snprintf: (out, size, format, ...args) => {
        var site = args.pop();
        if (args.length === 3) return _teleport_coloratt_snprintf_rgb(site, pointer(out), BigInt(size), text(format), args[0] >>> 0, args[1] >>> 0, args[2] >>> 0);
        return _teleport_coloratt_snprintf_string(site, pointer(out), BigInt(size), text(format), text(args[0]));
      },
      assert: condition => { if (!condition) _teleport_coloratt_assert(); },
      alloc: size => Number(_alloc(Number(size) >>> 0)),
      dupstr: value => Number(_dupstr(text(value))),
      strlen: value => Number(_strlen(text(value))),
      strcmpi: (a, b) => _strncmpi(text(a), text(b), -1),
      strncmpi: (a, b, n) => _strncmpi(text(a), text(b), Number(n) | 0),
      strncpy: (out, value, n) => Number(_strncpy(pointer(out), text(value), BigInt(n))),
      strchr: (value, ch) => Number(_strchr(text(value), ch)),
      strstri: (value, sub) => Number(_strstri(text(value), text(sub))),
      memcpy: (out, value, n) => Number(_memcpy(pointer(out), text(value), BigInt(n))),
      fuzzymatch: (a, b, skip, insensitive) => _fuzzymatch(text(a), text(b), text(skip), byte(insensitive)),
      atoi: value => _atoi(text(value)),
      mungspaces: value => Number(_mungspaces(pointer(value))),
      regex_init: () => Number(_regex_init()),
      regex_compile: (value, re) => _regex_compile(text(value), pointer(re)),
      regex_error_desc: (re, out) => Number(_regex_error_desc(pointer(re), pointer(out))),
      regex_free: re => _regex_free(pointer(re)),
      add_menu: (win, glyph, any, accelerator, group, attr, color, value, flags) => _add_menu(win, pointer(glyph), pointer(any), byte(accelerator), byte(group), attr, color, text(value), Number(flags) >>> 0),
      select_menu: (win, how, picks) => _select_menu(win, how, pointer(picks)),
    };
  },
  $teleportColorattInit__deps: ['$teleportColorattServices', '$addOnInit'],
  $teleportColorattInit__postset: "addOnInit(() => Module['nethackPorted'].initializeColoratt(teleportColorattServices()));",
  $teleportColorattInit: 0,
  $teleportColorattCall__deps: ['$teleportColorattInit', '$stackSave', '$stackRestore'],
  $teleportColorattCall: function(name, ...args) {
    var saved = stackSave();
    try { return Module['nethackPorted'].coloratt(teleportColorattServices(), name, ...args); }
    finally { stackRestore(saved); }
  },
  colortable_to_int32__deps: ['$teleportColorattCall'], colortable_to_int32__sig: 'ip',
  colortable_to_int32: function(row) { return teleportColorattCall('colortable_to_int32', row); },
  color_attr_to_str__deps: ['$teleportColorattCall'], color_attr_to_str__sig: 'pp',
  color_attr_to_str: function(ca) { return teleportColorattCall('color_attr_to_str', ca); },
  color_attr_parse_str__deps: ['$teleportColorattCall'], color_attr_parse_str__sig: 'ipp',
  color_attr_parse_str: function(ca, str) { return teleportColorattCall('color_attr_parse_str', ca, str); },
  query_color_attr__deps: ['$teleportColorattCall'], query_color_attr__sig: 'ipp',
  query_color_attr: function(ca, prompt) { return teleportColorattCall('query_color_attr', ca, prompt); },
  attr2attrname__deps: ['$teleportColorattCall'], attr2attrname__sig: 'pi',
  attr2attrname: function(attr) { return teleportColorattCall('attr2attrname', attr); },
  clr2colorname__deps: ['$teleportColorattCall'], clr2colorname__sig: 'pi',
  clr2colorname: function(color) { return teleportColorattCall('clr2colorname', color); },
  match_str2clr__deps: ['$teleportColorattCall'], match_str2clr__sig: 'ipi',
  match_str2clr: function(str, suppress) { return teleportColorattCall('match_str2clr', str, suppress << 24 >> 24); },
  match_str2attr__deps: ['$teleportColorattCall'], match_str2attr__sig: 'ipi',
  match_str2attr: function(str, complain) { return teleportColorattCall('match_str2attr', str, complain << 24 >> 24); },
  query_attr__deps: ['$teleportColorattCall'], query_attr__sig: 'ipi',
  query_attr: function(prompt, attr) { return teleportColorattCall('query_attr', prompt, attr); },
  query_color__deps: ['$teleportColorattCall'], query_color__sig: 'ipi',
  query_color: function(prompt, color) { return teleportColorattCall('query_color', prompt, color); },
  basic_menu_colors__deps: ['$teleportColorattCall'], basic_menu_colors__sig: 'vi',
  basic_menu_colors: function(load) { teleportColorattCall('basic_menu_colors', load << 24 >> 24); },
  add_menu_coloring_parsed__deps: ['$teleportColorattCall'], add_menu_coloring_parsed__sig: 'ipii',
  add_menu_coloring_parsed: function(str, color, attr) { return teleportColorattCall('add_menu_coloring_parsed', str, color, attr); },
  add_menu_coloring__deps: ['$teleportColorattCall'], add_menu_coloring__sig: 'ip',
  add_menu_coloring: function(str) { return teleportColorattCall('add_menu_coloring', str); },
  free_menu_coloring__deps: ['$teleportColorattCall'], free_menu_coloring__sig: 'v',
  free_menu_coloring: function() { teleportColorattCall('free_menu_coloring'); },
  free_one_menu_coloring__deps: ['$teleportColorattCall'], free_one_menu_coloring__sig: 'vi',
  free_one_menu_coloring: function(index) { teleportColorattCall('free_one_menu_coloring', index); },
  count_menucolors__deps: ['$teleportColorattCall'], count_menucolors__sig: 'i',
  count_menucolors: function() { return teleportColorattCall('count_menucolors'); },
  check_enhanced_colors__deps: ['$teleportColorattCall'], check_enhanced_colors__sig: 'ip',
  check_enhanced_colors: function(buf) { return teleportColorattCall('check_enhanced_colors', buf); },
  wc_color_name__deps: ['$teleportColorattCall'], wc_color_name__sig: 'pi',
  wc_color_name: function(color) { return teleportColorattCall('wc_color_name', color); },
  onlyhexdigits__deps: ['$teleportColorattCall'], onlyhexdigits__sig: 'ip',
  onlyhexdigits: function(buf) { return teleportColorattCall('onlyhexdigits', buf); },
  rgbstr_to_int32__deps: ['$teleportColorattCall'], rgbstr_to_int32__sig: 'ip',
  rgbstr_to_int32: function(str) { return teleportColorattCall('rgbstr_to_int32', str); },
  set_map_customcolor__deps: ['$teleportColorattCall'], set_map_customcolor__sig: 'ipi',
  set_map_customcolor: function(gmap, color) { return teleportColorattCall('set_map_customcolor', gmap, color >>> 0); },
  color_distance__deps: ['$teleportColorattCall'], color_distance__sig: 'iii',
  color_distance: function(a, b) { return teleportColorattCall('color_distance', a >>> 0, b >>> 0); },
  closest_color__deps: ['$teleportColorattCall'], closest_color__sig: 'iipp',
  closest_color: function(color, close, index) { return teleportColorattCall('closest_color', color >>> 0, close, index); },
  get_nhcolor_from_256_index__deps: ['$teleportColorattCall'], get_nhcolor_from_256_index__sig: 'ii',
  get_nhcolor_from_256_index: function(index) { return teleportColorattCall('get_nhcolor_from_256_index', index); },
});
