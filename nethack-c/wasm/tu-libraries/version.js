// Native storage, dependency calls and typed ABI only; version logic is JS.
addToLibrary({
  $teleportVersionServices__deps: ['teleport_version_storage', 'teleport_version_global', 'teleport_version_regex_id', 'teleport_version_win_message', 'teleport_version_create_window', 'teleport_version_putstr', 'teleport_version_display_window', 'teleport_version_destroy_window', 'teleport_version_wait_synch', 'teleport_version_raw_print', 'teleport_version_pline', 'teleport_version_format', 'teleport_version_raw_string', 'teleport_version_raw_int_string', 'teleport_version_raw_counts', 'teleport_version_snprintf_strings', 'teleport_version_snprintf_longs', 'teleport_version_sfo_char', 'teleport_version_sfi_char', 'teleport_version_sfo_uchar', 'teleport_version_sfi_uchar', 'teleport_version_sfo_info', 'teleport_version_sfi_info', 'teleport_version_literal_storage', 'teleport_version_literal_capacity', 'atoi', 'bufoff', 'bufon', 'teleport_version_datamodel', 'do_runtime_info', 'eos', 'fclose', 'fgets', 'fopen', 'get_lua_version', 'mdlib_version_string', 'nh_basename', 'teleport_version_pastebuf', 'release_runtime_info', 'runtime_info_init', 'strchr', 'strcmp', 'strcpy', 'strip_newline', 'strlen', 'strncmpi', 'strncpy', 'strrchr', 'strstri', 'strsubst', 'tabexpand', 'what_datamodel_is_this', '$lengthBytesUTF8', '$stringToUTF8', '$stackAlloc', '$stackSave', '$stackRestore'],
  $teleportVersionServices: function() {
    var state = Module['teleportVersionCache'] ||= { next: 0, strings: new Map() };
    var pointer = value => BigInt(value ? value.address ?? value : 0);
    var byte = value => Number(BigInt.asIntN(8, BigInt(value)));
    var literal = value => {
      if (state.strings.has(value)) return state.strings.get(value);
      var size = lengthBytesUTF8(value) + 1;
      if (state.next + size > Number(_teleport_version_literal_capacity())) throw new Error('Review changed version literal corpus');
      var at = Number(_teleport_version_literal_storage()) + state.next;
      stringToUTF8(value, at, size); state.next += size; state.strings.set(value, at); return at;
    };
    var text = value => typeof value === 'string' ? BigInt(literal(value)) : pointer(value);
    return {
      moduleKey: state, heap: () => HEAPU8, literal,
      stackAlloc: size => Number(stackAlloc(size)), stackSave: () => stackSave(), stackRestore: saved => stackRestore(saved),
      storage: index => Number(_teleport_version_storage(index)), global: index => Number(_teleport_version_global(index)),
      regexId: () => Number(_teleport_version_regex_id()), winMessage: () => _teleport_version_win_message(),
      create_nhwindow: type => _teleport_version_create_window(type),
      putstr: (win, attr, value) => _teleport_version_putstr(win, attr, text(value)),
      display_nhwindow: (win, blocking) => _teleport_version_display_window(win, byte(blocking)),
      destroy_nhwindow: win => _teleport_version_destroy_window(win), wait_synch: () => _teleport_version_wait_synch(),
      raw_print: value => _teleport_version_raw_print(text(value)),
      pline: (format, value) => _teleport_version_pline(text(format), text(value)),
      Sprintf: (out, format, value) => _teleport_version_format(pointer(out), text(format), text(value)),
      Snprintf: (out, size, format, ...args) => {
        var site = args.pop();
        if (args.length === 4) return _teleport_version_snprintf_longs(site, pointer(out), BigInt.asUintN(64, BigInt(size)), text(format), text(args[0]), BigInt(args[1]), BigInt(args[2]), BigInt(args[3]));
        return _teleport_version_snprintf_strings(site, pointer(out), BigInt.asUintN(64, BigInt(size)), text(format), text(args[0]), text(args[1]));
      },
      raw_printf: (format, ...args) => {
        if (args.length === 1) return _teleport_version_raw_string(text(format), text(args[0]));
        if (format.includes('file:%d')) return _teleport_version_raw_counts(text(format), args[0], Number(args[1]) | 0);
        return _teleport_version_raw_int_string(text(format), args[0], text(args[1]));
      },
      Sfo_char: (fp, value, tag, count) => _teleport_version_sfo_char(pointer(fp), pointer(value), text(tag), count),
      Sfi_char: (fp, value, tag, count) => _teleport_version_sfi_char(pointer(fp), pointer(value), text(tag), count),
      Sfo_uchar: (fp, value, tag) => _teleport_version_sfo_uchar(pointer(fp), pointer(value), text(tag)),
      Sfi_uchar: (fp, value, tag) => _teleport_version_sfi_uchar(pointer(fp), pointer(value), text(tag)),
      Sfo_version_info: (fp, value, tag) => _teleport_version_sfo_info(pointer(fp), pointer(value), text(tag)),
      Sfi_version_info: (fp, value, tag) => _teleport_version_sfi_info(pointer(fp), pointer(value), text(tag)),
      get_lua_version: () => Number(_get_lua_version()),
      mdlib_version_string: (out, sep) => Number(_mdlib_version_string(pointer(out), text(sep))),
      nh_basename: (name, keep) => Number(_nh_basename(text(name), byte(keep))),
      strlen: value => Number(_strlen(text(value))),
      eos: value => Number(_eos(pointer(value))),
      Strcpy: (out, value) => Number(_strcpy(pointer(out), text(value))),
      strcpy: (out, value) => Number(_strcpy(pointer(out), text(value))),
      strncpy: (out, value, size) => Number(_strncpy(pointer(out), text(value), BigInt(size))),
      strncmpi: (a, b, size) => _strncmpi(text(a), text(b), Number(size) | 0),
      strcmp: (a, b) => _strcmp(text(a), text(b)),
      strchr: (value, ch) => Number(_strchr(text(value), ch)),
      strrchr: (value, ch) => Number(_strrchr(text(value), ch)),
      strstri: (value, sub) => Number(_strstri(text(value), text(sub))),
      strsubst: (value, orig, replacement) => _strsubst(pointer(value), text(orig), text(replacement)),
      strip_newline: value => Number(_strip_newline(pointer(value))),
      tabexpand: value => Number(_tabexpand(pointer(value))),
      atoi: value => _atoi(text(value)),
      dlb_fopen: (name, mode) => Number(_fopen(text(name), text(mode))),
      dlb_fgets: (out, size, fp) => Number(_fgets(pointer(out), size, pointer(fp))),
      dlb_fclose: fp => _fclose(pointer(fp)),
      do_runtime_info: context => Number(_do_runtime_info(pointer(context))),
      runtime_info_init: () => _runtime_info_init(),
      release_runtime_info: () => _release_runtime_info(),
      port_insert_pastebuf: value => _teleport_version_pastebuf(pointer(value)),
      bufon: fd => _bufon(fd),
      bufoff: fd => _bufoff(fd),
      datamodel: format => Number(_teleport_version_datamodel(format)),
      what_datamodel_is_this: (format, a, b, c, d, e) => Number(_what_datamodel_is_this(format, a, b, c, d, e)),
    };
  },
  $teleportVersionInit__deps: ['$teleportVersionServices', '$addOnInit'],
  $teleportVersionInit__postset: "addOnInit(() => Module['nethackPorted'].initializeVersion(teleportVersionServices()));",
  $teleportVersionInit: 0,
  $teleportVersionCall__deps: ['$teleportVersionInit', '$stackSave', '$stackRestore'],
  $teleportVersionCall: function(name, ...args) {
    var saved = stackSave();
    try { return Module['nethackPorted'].version(teleportVersionServices(), name, ...args); }
    finally { stackRestore(saved); }
  },
  version_string__deps: ['$teleportVersionCall'], version_string__sig: 'ppj',
  version_string: function(buf, size) { return teleportVersionCall('version_string', buf, size); },
  getversionstring__deps: ['$teleportVersionCall'], getversionstring__sig: 'ppj',
  getversionstring: function(buf, size) { return teleportVersionCall('getversionstring', buf, size); },
  status_version__deps: ['$teleportVersionCall'], status_version__sig: 'ppji',
  status_version: function(buf, size, indent) { return teleportVersionCall('status_version', buf, size, indent << 24 >> 24); },
  doversion__deps: ['$teleportVersionCall'], doversion__sig: 'i',
  doversion: function() { return teleportVersionCall('doversion'); },
  doextversion__deps: ['$teleportVersionCall'], doextversion__sig: 'i',
  doextversion: function() { return teleportVersionCall('doextversion'); },
  early_version_info__deps: ['$teleportVersionCall'], early_version_info__sig: 'vi',
  early_version_info: function(paste) { teleportVersionCall('early_version_info', paste << 24 >> 24); },
  check_version__deps: ['$teleportVersionCall'], check_version__sig: 'ippij',
  check_version: function(data, file, complain, flags) { return teleportVersionCall('check_version', data, file, complain << 24 >> 24, flags); },
  get_feature_notice_ver__deps: ['$teleportVersionCall'], get_feature_notice_ver__sig: 'jp',
  get_feature_notice_ver: function(str) { return teleportVersionCall('get_feature_notice_ver', str); },
  get_current_feature_ver__deps: ['$teleportVersionCall'], get_current_feature_ver__sig: 'j',
  get_current_feature_ver: function() { return teleportVersionCall('get_current_feature_ver'); },
  copyright_banner_line__deps: ['$teleportVersionCall'], copyright_banner_line__sig: 'pi',
  copyright_banner_line: function(index) { return teleportVersionCall('copyright_banner_line', index); },
  dump_version_info__deps: ['$teleportVersionCall'], dump_version_info__sig: 'v',
  dump_version_info: function() { teleportVersionCall('dump_version_info'); },
  store_version__deps: ['$teleportVersionCall'], store_version__sig: 'vp',
  store_version: function(fp) { teleportVersionCall('store_version', fp); },
  get_critical_size_count__deps: ['$teleportVersionCall'], get_critical_size_count__sig: 'i',
  get_critical_size_count: function() { return teleportVersionCall('get_critical_size_count'); },
  store_critical_bytes__deps: ['$teleportVersionCall'], store_critical_bytes__sig: 'vp',
  store_critical_bytes: function(fp) { teleportVersionCall('store_critical_bytes', fp); },
  uptodate__deps: ['$teleportVersionCall'], uptodate__sig: 'ippj',
  uptodate: function(fp, name, flags) { return teleportVersionCall('uptodate', fp, name, flags); },
  compare_critical_bytes__deps: ['$teleportVersionCall'], compare_critical_bytes__sig: 'ippj',
  compare_critical_bytes: function(fp, mismatch, flags) { return teleportVersionCall('compare_critical_bytes', fp, mismatch, flags); },
  validate__deps: ['$teleportVersionCall'], validate__sig: 'ippi',
  validate: function(fp, name, noWait) { return teleportVersionCall('validate', fp, name, noWait << 24 >> 24); },
  teleport_version_test_insert__deps: ['$teleportVersionCall'], teleport_version_test_insert__sig: 'vp',
  teleport_version_test_insert: function(buf) { teleportVersionCall('insert_rtoption', buf); },
});
