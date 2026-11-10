// Native dependencies, static storage and typed variadic ABI only.
addToLibrary({
  $teleportMdlibServices__deps: ['datamodel', 'dupstr', 'eos', 'free', 'free_nomakedefs', 'populate_nomakedefs', 'strcat', 'strchr', 'strcmp', 'strcpy', 'strlen', 'strncmp', 'teleport_mdlib_storage', 'teleport_mdlib_literal_storage', 'teleport_mdlib_literal_capacity', 'teleport_mdlib_format_string', 'teleport_mdlib_format_int', 'teleport_mdlib_format_three', 'teleport_mdlib_format_version', 'teleport_mdlib_format_heading', 'teleport_mdlib_snprintf', '$lengthBytesUTF8', '$stringToUTF8', '$stackAlloc'],
  $teleportMdlibServices: function() {
    var state = Module['teleportMdlibLiterals'] ||= { next: 0, strings: new Map() };
    var literal = value => {
      if (state.strings.has(value)) return state.strings.get(value);
      var size = lengthBytesUTF8(value) + 1;
      if (state.next + size > Number(_teleport_mdlib_literal_capacity())) throw new Error('Review changed mdlib literal corpus');
      var at = Number(_teleport_mdlib_literal_storage()) + state.next;
      stringToUTF8(value, at, size);
      state.next += size;
      state.strings.set(value, at);
      return at;
    };
    var pointer = value => BigInt(value ? value.address ?? value : 0);
    var text = value => typeof value === 'string' ? BigInt(literal(value)) : pointer(value);
    return {
      heap: () => HEAPU8,
      stackAlloc: size => stackAlloc(size),
      storage: index => Number(_teleport_mdlib_storage(index)),
      literal: value => literal(value),
      dupstr: value => Number(_dupstr(text(value))),
      free: value => _free(pointer(value)),
      datamodel: value => Number(_datamodel(value)),
      populate_nomakedefs: value => _populate_nomakedefs(pointer(value)),
      free_nomakedefs: () => _free_nomakedefs(),
      eos: value => Number(_eos(pointer(value))),
      strlen: value => Number(_strlen(text(value))),
      strcmp: (a, b) => _strcmp(text(a), text(b)),
      strncmp: (a, b, size) => _strncmp(text(a), text(b), BigInt(size)),
      strchr: (value, character) => Number(_strchr(text(value), typeof character === 'string' ? character.charCodeAt(0) : character)),
      strcpy: (out, value) => Number(_strcpy(pointer(out), text(value))),
      Strcpy: (out, value) => Number(_strcpy(pointer(out), text(value))),
      Strcat: (out, value) => Number(_strcat(pointer(out), text(value))),
      Sprintf: (out, format, ...args) => {
        if (format === '%d%s%d%s%d')
          _teleport_mdlib_format_version(pointer(out), text(format), args[0], text(args[1]), args[2], text(args[3]), args[4]);
        else if (format === ' %d.%d.%d only')
          _teleport_mdlib_format_three(pointer(out), text(format), args[0], args[1], args[2]);
        else if (format === '%sNetHack version %d.%d.%d%s\n')
          _teleport_mdlib_format_heading(pointer(out), text(format), text(args[0]), args[1], args[2], args[3], text(args[4]));
        else if (format === '-%d')
          _teleport_mdlib_format_int(pointer(out), text(format), args[0]);
        else {
          if (args.length > 1) throw new Error('Review changed mdlib formatting ABI');
          _teleport_mdlib_format_string(pointer(out), text(format), text(args[0]));
        }
      },
      Snprintf: (out, size, format, ...args) => {
        var kind;
        if (format === '%s NetHack%s Version %s%s - last %s %s.') kind = 0;
        else if (format === '         Version %s %s%s, %s %s.') kind = 1;
        else throw new Error('Review changed mdlib diagnostic formatting');
        _teleport_mdlib_snprintf(kind, pointer(out), BigInt(size), text(format), text(args[0]), text(args[1]), text(args[2]), text(args[3]), text(args[4]), text(args[5]));
      },
    };
  },
  $teleportMdlibCall__deps: ['$teleportMdlibServices', '$stackSave', '$stackRestore'],
  $teleportMdlibCall: function(name, ...args) {
    var stack = stackSave();
    try { return Module['nethackPorted'].mdlib(teleportMdlibServices(), name, ...args); }
    finally { stackRestore(stack); }
  },
  md_ignored_features__deps: ['$teleportMdlibCall'], md_ignored_features__sig: 'j',
  md_ignored_features: function() { return teleportMdlibCall('md_ignored_features'); },
  mdlib_version_string__deps: ['$teleportMdlibCall'], mdlib_version_string__sig: 'ppp',
  mdlib_version_string: function(outbuf, delim) { return teleportMdlibCall('mdlib_version_string', outbuf, delim); },
  version_id_string__deps: ['$teleportMdlibCall'], version_id_string__sig: 'ppjp',
  version_id_string: function(outbuf, bufsz, build_date) { return teleportMdlibCall('version_id_string', outbuf, bufsz, build_date); },
  bannerc_string__deps: ['$teleportMdlibCall'], bannerc_string__sig: 'ppjp',
  bannerc_string: function(outbuf, bufsz, build_date) { return teleportMdlibCall('bannerc_string', outbuf, bufsz, build_date); },
  runtime_info_init__deps: ['$teleportMdlibCall'], runtime_info_init__sig: 'v',
  runtime_info_init: function() { teleportMdlibCall('runtime_info_init'); },
  do_runtime_info__deps: ['$teleportMdlibCall'], do_runtime_info__sig: 'pp',
  do_runtime_info: function(rtcontext) { return teleportMdlibCall('do_runtime_info', rtcontext); },
  release_runtime_info__deps: ['$teleportMdlibCall'], release_runtime_info__sig: 'v',
  release_runtime_info: function() { teleportMdlibCall('release_runtime_info'); },
  teleport_mdlib_test_make_version__deps: ['$teleportMdlibCall'], teleport_mdlib_test_make_version__sig: 'v',
  teleport_mdlib_test_make_version: function() { teleportMdlibCall('make_version'); },
  teleport_mdlib_test_build_options__deps: ['$teleportMdlibCall'], teleport_mdlib_test_build_options__sig: 'v',
  teleport_mdlib_test_build_options: function() { teleportMdlibCall('build_options'); },
  teleport_mdlib_test_build_savebones_compat_string__deps: ['$teleportMdlibCall'], teleport_mdlib_test_build_savebones_compat_string__sig: 'v',
  teleport_mdlib_test_build_savebones_compat_string: function() { teleportMdlibCall('build_savebones_compat_string'); },
  teleport_mdlib_test_count_and_validate_winopts__deps: ['$teleportMdlibCall'], teleport_mdlib_test_count_and_validate_winopts__sig: 'i',
  teleport_mdlib_test_count_and_validate_winopts: function() { return teleportMdlibCall('count_and_validate_winopts'); },
  teleport_mdlib_test_count_and_validate_soundlibopts__deps: ['$teleportMdlibCall'], teleport_mdlib_test_count_and_validate_soundlibopts__sig: 'i',
  teleport_mdlib_test_count_and_validate_soundlibopts: function() { return teleportMdlibCall('count_and_validate_soundlibopts'); },
  teleport_mdlib_test_opt_out_words__deps: ['$teleportMdlibCall'], teleport_mdlib_test_opt_out_words__sig: 'vpp',
  teleport_mdlib_test_opt_out_words: function(str, length_p) { teleportMdlibCall('opt_out_words', str, length_p); },
});
