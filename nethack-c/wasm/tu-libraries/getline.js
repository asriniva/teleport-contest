// Input/output calls, static strings and C storage ABI only; getline logic is JS.
addToLibrary({
  $teleportGetlineServices__deps: ['addtopl', 'dumplogmsg', 'eos', 'extcmd_initiator', 'extcmd_via_menu', 'extcmds_getentry', 'extcmds_match', 'more', 'mungspaces', 'pgetchar', 'putsyms', 'strcat', 'strchr', 'strcpy', 'teleport_getline_clear_window', 'teleport_getline_custompline', 'teleport_getline_fflush', 'teleport_getline_global', 'teleport_getline_pline', 'teleport_getline_scalar', 'teleport_getline_set_scalar', 'teleport_getline_stdout', 'teleport_getline_window_message', 'term_curs_set', 'tty_clear_nhwindow', 'tty_doprev_message', 'tty_nhbell', 'tty_nhgetch', 'visctrl', 'teleport_getline_literal_storage', 'teleport_getline_literal_capacity', '$lengthBytesUTF8', '$stringToUTF8', '$stackAlloc', '$stackSave', '$stackRestore'],
  $teleportGetlineServices: function() {
    var state = Module['teleportGetlineLiterals'] ||= { next: 0, strings: new Map() };
    var literal = value => {
      if (state.strings.has(value)) return state.strings.get(value);
      var size = lengthBytesUTF8(value) + 1;
      if (state.next + size > Number(_teleport_getline_literal_capacity())) throw new Error('Review changed getline literal corpus');
      var at = Number(_teleport_getline_literal_storage()) + state.next;
      stringToUTF8(value, at, size);
      state.next += size;
      state.strings.set(value, at);
      return at;
    };
    var pointer = value => BigInt(value ? value.address ?? value : 0);
    var text = value => BigInt(typeof value === 'string' ? literal(value) : value || 0);
    return {
      heap: () => HEAPU8,
      stackAlloc: size => stackAlloc(size),
      stackSave: () => stackSave(),
      stackRestore: value => stackRestore(value),
      global: index => Number(_teleport_getline_global(index)),
      windowMessage: () => _teleport_getline_window_message(),
      scalar: index => _teleport_getline_scalar(index),
      setScalar: (index, value) => _teleport_getline_set_scalar(index, value),
      stdout: () => Number(_teleport_getline_stdout()),
      fflush: stream => _teleport_getline_fflush(pointer(stream)),
      more: () => _more(),
      custompline: (flags, format, query) => _teleport_getline_custompline(flags >>> 0, text(format), text(query)),
      strcpy: (destination, source) => Number(_strcpy(pointer(destination), text(source))),
      Strcpy: (destination, source) => Number(_strcpy(pointer(destination), text(source))),
      strcat: (destination, source) => Number(_strcat(pointer(destination), text(source))),
      Strcat: (destination, source) => Number(_strcat(pointer(destination), text(source))),
      eos: value => Number(_eos(pointer(value))),
      pgetchar: () => _pgetchar(),
      term_curs_set: value => _term_curs_set(value),
      tty_clear_nhwindow: window => _tty_clear_nhwindow(window),
      clear_nhwindow: window => _teleport_getline_clear_window(window),
      addtopl: value => _addtopl(text(value)),
      putsyms: value => _putsyms(text(value)),
      tty_doprev_message: () => _tty_doprev_message(),
      tty_nhbell: () => _tty_nhbell(),
      dumplogmsg: value => _dumplogmsg(text(value)),
      tty_nhgetch: () => _tty_nhgetch(),
      strchr: (value, character) => Number(_strchr(text(value), character)),
      extcmds_match: (base, flags, matches) => _extcmds_match(text(base), flags, pointer(matches)),
      extcmds_getentry: index => Number(_extcmds_getentry(index)),
      extcmd_via_menu: () => _extcmd_via_menu(),
      extcmd_initiator: () => _extcmd_initiator(),
      mungspaces: value => Number(_mungspaces(pointer(value))),
      pline: (format, prefix, command) => _teleport_getline_pline(text(format), text(prefix), text(command)),
      visctrl: value => Number(_visctrl(value << 24 >> 24)),
    };
  },
  $teleportGetlineCall__deps: ['$teleportGetlineServices', '$stackSave', '$stackRestore'],
  $teleportGetlineCall: function(name, ...args) {
    var stack = stackSave();
    try { return Module['nethackPorted'].getline(teleportGetlineServices(), name, ...args); }
    finally { stackRestore(stack); }
  },
  tty_getlin__deps: ['$teleportGetlineCall'], tty_getlin__sig: 'vpp',
  tty_getlin: function(query, bufp) { teleportGetlineCall('tty_getlin', query, bufp); },
  xwaitforspace__deps: ['$teleportGetlineCall'], xwaitforspace__sig: 'vp',
  xwaitforspace: function(s) { teleportGetlineCall('xwaitforspace', s); },
  tty_get_ext_cmd__deps: ['$teleportGetlineCall'], tty_get_ext_cmd__sig: 'i',
  tty_get_ext_cmd: function() { return teleportGetlineCall('tty_get_ext_cmd'); },
  teleport_getline_test_hooked__deps: ['$teleportGetlineCall'], teleport_getline_test_hooked__sig: 'vppi',
  teleport_getline_test_hooked: function(query, bufp, hook) { teleportGetlineCall('hooked_tty_getlin', query, bufp, hook); },
  teleport_getline_test_ext_hook__deps: ['$teleportGetlineCall'], teleport_getline_test_ext_hook__sig: 'ip',
  teleport_getline_test_ext_hook: function(base) { return teleportGetlineCall('ext_cmd_getlin_hook', base); },
});
