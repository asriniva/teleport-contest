// Real stdio, native dependencies and typed ABI calls; rumor logic is JS.
addToLibrary({
  $teleportRumorsServices__deps: ['teleport_rumors_global', 'teleport_rumors_hero_bit', 'teleport_rumors_set_hero_bit', 'teleport_rumors_monster_bit', 'teleport_rumors_bogon_codes', 'teleport_rumors_open', 'teleport_rumors_close', 'teleport_rumors_seek', 'teleport_rumors_tell', 'teleport_rumors_gets', 'teleport_rumors_free', 'teleport_rumors_rng_pointer', 'teleport_rumors_call_rng', 'teleport_rumors_rn2', 'teleport_rumors_rnd', 'teleport_rumors_assert', 'teleport_rumors_nhassert', 'teleport_rumors_scan_header', 'teleport_rumors_scan_int', 'teleport_rumors_scan_ulong', 'teleport_rumors_format_longs', 'teleport_rumors_format_long_string', 'teleport_rumors_format_int_string', 'teleport_rumors_format_strings', 'teleport_rumors_message', 'teleport_rumors_create_window', 'teleport_rumors_display_window', 'teleport_rumors_destroy_window', 'teleport_rumors_putstr', 'teleport_rumors_win_message', 'teleport_rumors_ynq', 'teleport_rumors_y_n', 'teleport_rumors_explicitdebug', 'teleport_rumors_sfo_unsigned', 'teleport_rumors_sfo_ulong', 'teleport_rumors_sfi_unsigned', 'teleport_rumors_sfi_ulong', 'teleport_rumors_literal_storage', 'teleport_rumors_literal_capacity', 'alloc', 'dupstr', 'strlen', 'strcpy', 'strncmp', 'strcmp', 'strchr', 'eos', 'xcrypt', 'lowc', 'exercise', 'is_fainted', 'money_cnt', 'Monnam', 'currency', 'money2mon', 'record_achievement', 'more_experienced', 'newexplevel', 'the_unique_pm', 'bogon_is_pname', '$lengthBytesUTF8', '$stringToUTF8', '$stackAlloc', '$stackSave', '$stackRestore'],
  $teleportRumorsServices: function() {
    var state = Module['teleportRumorsCache'] ||= { next: 0, strings: new Map() };
    var pointer = value => BigInt(value ? value.address ?? value : 0);
    var byte = value => Number(BigInt.asIntN(8, BigInt(value)));
    var literal = value => {
      if (state.strings.has(value)) return state.strings.get(value);
      var size = lengthBytesUTF8(value) + 1;
      if (state.next + size > Number(_teleport_rumors_literal_capacity())) throw new Error('Review changed rumor literal corpus');
      var at = Number(_teleport_rumors_literal_storage()) + state.next;
      stringToUTF8(value, at, size); state.next += size; state.strings.set(value, at); return at;
    };
    var text = value => typeof value === 'string' ? BigInt(literal(value)) : pointer(value);
    var message = (kind, format, a, b) => _teleport_rumors_message(kind, text(format), text(a), text(b));
    return {
      moduleKey: state, heap: () => HEAPU8, literal,
      stackAlloc: size => Number(stackAlloc(size)), stackSave: () => stackSave(), stackRestore: saved => stackRestore(saved),
      global: index => Number(_teleport_rumors_global(index)),
      heroBit: index => _teleport_rumors_hero_bit(index),
      setHeroBit: (index, value) => _teleport_rumors_set_hero_bit(index, Number(value) >>> 0),
      monsterBit: (mon, index) => _teleport_rumors_monster_bit(pointer(mon), index),
      bogonCodes: () => Number(_teleport_rumors_bogon_codes()),
      dlb_fopen: (name, mode) => Number(_teleport_rumors_open(text(name), text(mode))),
      dlb_fclose: fp => _teleport_rumors_close(pointer(fp)),
      dlb_fseek: (fp, offset, whence) => _teleport_rumors_seek(pointer(fp), BigInt.asIntN(64, BigInt(offset)), whence),
      dlb_ftell: fp => _teleport_rumors_tell(pointer(fp)),
      dlb_fgets: (out, size, fp) => Number(_teleport_rumors_gets(pointer(out), Number(size) | 0, pointer(fp))),
      alloc: size => Number(_alloc(Number(size) >>> 0)), free: ptr => _teleport_rumors_free(pointer(ptr)),
      dupstr: value => Number(_dupstr(text(value))), strlen: value => Number(_strlen(text(value))),
      strcpy: (out, value) => Number(_strcpy(pointer(out), text(value))),
      Strcpy: (out, value) => Number(_strcpy(pointer(out), text(value))),
      strcmp: (a, b) => _strcmp(text(a), text(b)),
      strncmp: (a, b, size) => _strncmp(text(a), text(b), BigInt(size)),
      strchr: (value, ch) => Number(_strchr(text(value), ch)), eos: value => Number(_eos(text(value))),
      xcrypt: (value, out) => Number(_xcrypt(text(value), pointer(out))), lowc: ch => _lowc(byte(ch)),
      exercise: (attr, value) => _exercise(attr, byte(value)), is_fainted: () => _is_fainted(),
      money_cnt: obj => _money_cnt(pointer(obj)), Monnam: mon => Number(_Monnam(pointer(mon))),
      currency: value => Number(_currency(BigInt.asIntN(64, BigInt(value)))),
      money2mon: (mon, value) => _money2mon(pointer(mon), BigInt.asIntN(64, BigInt(value))),
      record_achievement: value => _record_achievement(byte(value)),
      more_experienced: (a, b) => _more_experienced(a, b), newexplevel: () => _newexplevel(),
      the_unique_pm: mon => _the_unique_pm(pointer(mon)), bogon_is_pname: code => _bogon_is_pname(byte(code)),
      rngPointer: () => _teleport_rumors_rng_pointer(),
      callRng: (rng, bound) => _teleport_rumors_call_rng(BigInt(rng), bound),
      rn2: (bound, line, caller) => _teleport_rumors_rn2(bound, line, caller),
      rnd: (bound, line, caller) => _teleport_rumors_rnd(bound, line, caller),
      assert: condition => { if (!condition) _teleport_rumors_assert(); },
      nhassert: condition => { if (!condition) _teleport_rumors_nhassert(); },
      sscanf: (line, format, ...args) => {
        if (args.length === 7) return _teleport_rumors_scan_header(text(line), text(format), ...args.map(pointer));
        if (format.includes('lx')) return _teleport_rumors_scan_ulong(text(line), text(format), pointer(args[0]));
        return _teleport_rumors_scan_int(text(line), text(format), pointer(args[0]));
      },
      Sprintf: (out, format, ...args) => {
        if (args.length === 6) return _teleport_rumors_format_longs(pointer(out), text(format), ...args.map(value => BigInt(value)));
        if (args.length === 2 && typeof args[0] === 'bigint') return _teleport_rumors_format_long_string(pointer(out), text(format), args[0], text(args[1]));
        if (args.length === 2 && format.includes('%d')) return _teleport_rumors_format_int_string(pointer(out), text(format), args[0], text(args[1]));
        return _teleport_rumors_format_strings(pointer(out), text(format), text(args[0]), text(args[1]));
      },
      pline: (format, a, b) => message(0, format, a, b), You: (format, a, b) => message(1, format, a, b),
      There: (format, a, b) => message(2, format, a, b), verbalize: (format, a, b) => message(3, format, a, b),
      impossible: (format, a, b) => message(4, format, a, b),
      create_nhwindow: type => _teleport_rumors_create_window(type),
      display_nhwindow: (win, blocking) => _teleport_rumors_display_window(win, byte(blocking)),
      destroy_nhwindow: win => _teleport_rumors_destroy_window(win),
      putstr: (win, attr, value) => _teleport_rumors_putstr(win, attr, text(value)),
      winMessage: () => _teleport_rumors_win_message(),
      ynq: query => _teleport_rumors_ynq(text(query)), y_n: query => _teleport_rumors_y_n(text(query)),
      explicitdebug: value => _teleport_rumors_explicitdebug(text(value)),
      Sfo_unsigned: (fp, value, tag) => _teleport_rumors_sfo_unsigned(pointer(fp), pointer(value), text(tag)),
      Sfo_ulong: (fp, value, tag) => _teleport_rumors_sfo_ulong(pointer(fp), pointer(value), text(tag)),
      Sfi_unsigned: (fp, value, tag) => _teleport_rumors_sfi_unsigned(pointer(fp), pointer(value), text(tag)),
      Sfi_ulong: (fp, value, tag) => _teleport_rumors_sfi_ulong(pointer(fp), pointer(value), text(tag)),
    };
  },
  $teleportRumorsCall__deps: ['$teleportRumorsServices', '$stackSave', '$stackRestore'],
  $teleportRumorsCall: function(name, ...args) {
    var saved = stackSave();
    try { return Module['nethackPorted'].rumors(teleportRumorsServices(), name, ...args); }
    finally { stackRestore(saved); }
  },
  getrumor__deps: ['$teleportRumorsCall'], getrumor__sig: 'pipi',
  getrumor: function(truth, buf, exclude) { return teleportRumorsCall('getrumor', truth, buf, exclude << 24 >> 24); },
  rumor_check__deps: ['$teleportRumorsCall'], rumor_check__sig: 'v',
  rumor_check: function() { teleportRumorsCall('rumor_check'); },
  get_rnd_text__deps: ['$teleportRumorsCall'], get_rnd_text__sig: 'ppppi',
  get_rnd_text: function(file, buf, rng, pad) { return teleportRumorsCall('get_rnd_text', file, buf, rng, pad >>> 0); },
  outrumor__deps: ['$teleportRumorsCall'], outrumor__sig: 'vii',
  outrumor: function(truth, mechanism) { teleportRumorsCall('outrumor', truth, mechanism); },
  save_oracles__deps: ['$teleportRumorsCall'], save_oracles__sig: 'vp',
  save_oracles: function(fp) { teleportRumorsCall('save_oracles', fp); },
  restore_oracles__deps: ['$teleportRumorsCall'], restore_oracles__sig: 'vp',
  restore_oracles: function(fp) { teleportRumorsCall('restore_oracles', fp); },
  outoracle__deps: ['$teleportRumorsCall'], outoracle__sig: 'vii',
  outoracle: function(special, delphi) { teleportRumorsCall('outoracle', special << 24 >> 24, delphi << 24 >> 24); },
  doconsult__deps: ['$teleportRumorsCall'], doconsult__sig: 'ip',
  doconsult: function(mon) { return teleportRumorsCall('doconsult', mon); },
  CapitalMon__deps: ['$teleportRumorsCall'], CapitalMon__sig: 'ip',
  CapitalMon: function(word) { return teleportRumorsCall('CapitalMon', word); },
  free_CapMons__deps: ['$teleportRumorsCall'], free_CapMons__sig: 'v',
  free_CapMons: function() { teleportRumorsCall('free_CapMons'); },
  teleport_rumors_test_unpad__deps: ['$teleportRumorsCall'], teleport_rumors_test_unpad__sig: 'vp',
  teleport_rumors_test_unpad: function(line) { teleportRumorsCall('unpadline', line); },
  teleport_rumors_test_init__deps: ['$teleportRumorsCall'], teleport_rumors_test_init__sig: 'vp',
  teleport_rumors_test_init: function(fp) { teleportRumorsCall('init_rumors', fp); },
  teleport_rumors_test_line__deps: ['$teleportRumorsCall'], teleport_rumors_test_line__sig: 'pppipjji',
  teleport_rumors_test_line: function(fp, buf, size, rng, start, end, pad) { return teleportRumorsCall('get_rnd_line', fp, buf, size >>> 0, rng, start, end, pad >>> 0); },
  teleport_rumors_test_oracles__deps: ['$teleportRumorsCall'], teleport_rumors_test_oracles__sig: 'vp',
  teleport_rumors_test_oracles: function(fp) { teleportRumorsCall('init_oracles', fp); },
  teleport_rumors_test_others__deps: ['$teleportRumorsCall'], teleport_rumors_test_others__sig: 'vppp',
  teleport_rumors_test_others: function(type, file, win) { teleportRumorsCall('others_check', type, file, win); },
  teleport_rumors_test_couldnt__deps: ['$teleportRumorsCall'], teleport_rumors_test_couldnt__sig: 'vp',
  teleport_rumors_test_couldnt: function(file) { teleportRumorsCall('couldnt_open_file', file); },
  teleport_rumors_test_caps__deps: ['$teleportRumorsCall'], teleport_rumors_test_caps__sig: 'v',
  teleport_rumors_test_caps: function() { teleportRumorsCall('init_CapMons'); },
  // Probe-only observation of the original private state; no cache population.
  teleport_rumors_test_cap_count__deps: ['$teleportRumorsServices'], teleport_rumors_test_cap_count__sig: 'ii',
  teleport_rumors_test_cap_count: function(field) {
    var state = Module['nethackPorted'].rumorsState(teleportRumorsServices());
    return state[['CapMonstCnt', 'CapBogonCnt', 'CapMonSiz'][field]] >>> 0;
  },
  teleport_rumors_test_cap_pointer__deps: ['$teleportRumorsServices'], teleport_rumors_test_cap_pointer__sig: 'p',
  teleport_rumors_test_cap_pointer: function() {
    return Module['nethackPorted'].rumorsState(teleportRumorsServices()).CapMons;
  },
});
