// Native dependencies, shared fields and typed scanning/formatting ABI only.
addToLibrary({
  $teleportMinionServices__deps: ['Amonnam', 'Hear_again', 'In_hell', 'Monnam', 'acurr', 'align_gname', 'alloc', 'bless', 'canseemon', 'currency', 'enexto', 'free', 'getlin', 'is_art', 'is_fainted', 'm_dowear', 'makemon', 'memset', 'mk_roamer', 'mkclass', 'mkclass_aligned', 'mksobj', 'mon_aligntyp', 'mon_has_amulet', 'mon_nam', 'money2mon', 'money_cnt', 'mongone', 'mongets', 'mpickobj', 'msummon_environ', 'newmextra', 'newsym', 'nomul', 'reset_faint', 'rloc', 's_suffix', 'select_hwep', 'sensemon', 'set_malign', 'sgn', 'show_transient_light', 'stop_occupation', 'tele_restrict', 'transient_light_cleanup', 'unmul', 'which_armor', 'x_monnam', 'teleport_minion_global', 'teleport_minion_uwep', 'teleport_minion_roleplay_deaf', 'teleport_minion_monster_bit', 'teleport_minion_set_monster_bit', 'teleport_minion_sscanf', 'teleport_minion_message', 'teleport_minion_money_message', 'teleport_minion_livelog', 'teleport_minion_rn2', 'teleport_minion_rnd', 'teleport_minion_d', 'teleport_minion_literal_storage', 'teleport_minion_literal_capacity', '$lengthBytesUTF8', '$stringToUTF8', '$stackAlloc'],
  $teleportMinionServices: function() {
    var state = Module['teleportMinionLiterals'] ||= { next: 0, strings: new Map() };
    var literal = value => {
      if (state.strings.has(value)) return state.strings.get(value);
      var size = lengthBytesUTF8(value) + 1;
      if (state.next + size > Number(_teleport_minion_literal_capacity())) throw new Error('Review changed minion literal corpus');
      var at = Number(_teleport_minion_literal_storage()) + state.next;
      stringToUTF8(value, at, size);
      state.next += size;
      state.strings.set(value, at);
      return at;
    };
    var pointer = value => BigInt(value ? value.address ?? value : 0);
    var text = value => typeof value === 'string' ? BigInt(literal(value)) : pointer(value);
    var byte = value => Number(value) << 24 >> 24;
    var coord = value => Number(value) << 16 >> 16;
    var message = (kind, format, a = 0, b = 0, c = 0) => _teleport_minion_message(kind, text(format), text(a), text(b), text(c));
    var money = (kind, format, name, value, units) => _teleport_minion_money_message(kind, text(format), text(name), BigInt(value), text(units));
    return {
      heap: () => HEAPU8,
      stackAlloc: size => stackAlloc(size),
      global: index => Number(_teleport_minion_global(index)),
      uwep: () => Number(_teleport_minion_uwep()),
      roleplayDeaf: () => _teleport_minion_roleplay_deaf(),
      monsterBit: (mon, index) => _teleport_minion_monster_bit(pointer(mon), index),
      setMonsterBit: (mon, index, value) => _teleport_minion_set_monster_bit(pointer(mon), index, Number(value)),
      newmextra: () => Number(_newmextra()),
      alloc: size => Number(_alloc(size >>> 0)),
      free: value => _free(pointer(value)),
      memset: (out, value, size) => Number(_memset(pointer(out), value, BigInt(size))),
      canseemon: mon => _canseemon(pointer(mon)),
      sensemon: mon => _sensemon(pointer(mon)),
      is_art: (obj, art) => _is_art(pointer(obj), art),
      mon_aligntyp: mon => _mon_aligntyp(pointer(mon)),
      In_hell: level => _In_hell(pointer(level)),
      sgn: value => _sgn(value),
      makemon: (data, x, y, flags) => Number(_makemon(pointer(data), coord(x), coord(y), flags >>> 0)),
      show_transient_light: (obj, x, y) => _show_transient_light(pointer(obj), coord(x), coord(y)),
      transient_light_cleanup: () => _transient_light_cleanup(),
      msummon_environ: (data, cloud) => Number(_msummon_environ(pointer(data), pointer(cloud))),
      align_gname: alignment => Number(_align_gname(byte(alignment))),
      s_suffix: value => Number(_s_suffix(text(value))),
      Amonnam: mon => Number(_Amonnam(pointer(mon))),
      Monnam: mon => Number(_Monnam(pointer(mon))),
      mon_nam: mon => Number(_mon_nam(pointer(mon))),
      is_fainted: () => _is_fainted(),
      reset_faint: () => _reset_faint(),
      stop_occupation: () => _stop_occupation(),
      nomul: value => _nomul(value),
      unmul: value => _unmul(text(value)),
      set_malign: mon => _set_malign(pointer(mon)),
      newsym: (x, y) => _newsym(coord(x), coord(y)),
      tele_restrict: mon => _tele_restrict(pointer(mon)),
      rloc: (mon, flags) => _rloc(pointer(mon), flags >>> 0),
      money_cnt: obj => _money_cnt(pointer(obj)),
      mon_has_amulet: mon => _mon_has_amulet(pointer(mon)),
      currency: value => Number(_currency(BigInt(value))),
      acurr: attribute => _acurr(attribute),
      x_monnam: (mon, article, adjective, flags, called) => Number(_x_monnam(pointer(mon), article, text(adjective), flags, byte(called))),
      mongone: mon => _mongone(pointer(mon)),
      getlin: (prompt, out) => _getlin(text(prompt), pointer(out)),
      sscanf: (buffer, format, value) => _teleport_minion_sscanf(pointer(buffer), text(format), pointer(value)),
      money2mon: (mon, value) => _money2mon(pointer(mon), BigInt(value)),
      mkclass: (letter, flags) => Number(_mkclass(byte(letter), flags)),
      mkclass_aligned: (letter, flags, alignment) => Number(_mkclass_aligned(byte(letter), flags, byte(alignment))),
      enexto: (out, x, y, data) => _enexto(pointer(out), coord(x), coord(y), pointer(data)),
      mk_roamer: (data, alignment, x, y, peaceful) => Number(_mk_roamer(pointer(data), byte(alignment), coord(x), coord(y), byte(peaceful))),
      Hear_again: () => _Hear_again(),
      select_hwep: mon => Number(_select_hwep(pointer(mon))),
      mksobj: (type, init, artif) => Number(_mksobj(type, byte(init), byte(artif))),
      mpickobj: (mon, obj) => _mpickobj(pointer(mon), pointer(obj)),
      bless: obj => _bless(pointer(obj)),
      which_armor: (mon, mask) => Number(_which_armor(pointer(mon), BigInt(mask))),
      mongets: (mon, type) => Number(_mongets(pointer(mon), type)),
      m_dowear: (mon, creation) => _m_dowear(pointer(mon), byte(creation)),
      rn2: (bound, line, caller) => _teleport_minion_rn2(bound, line, caller),
      rnd: (bound, line, caller) => _teleport_minion_rnd(bound, line, caller),
      d: (number, sides, line, caller) => _teleport_minion_d(number, sides, line, caller),
      livelog_printf: (category, format, name, value, units) => _teleport_minion_livelog(BigInt(category), text(format), text(name), BigInt(value), text(units)),
      pline: (format, a, b, c) => format === '%s demands %ld %s for safe passage.' ? money(0, format, a, b, c) : message(0, format, a, b, c),
      pline_The: (format, a, b, c) => message(1, format, a, b, c),
      You: (format, a, b, c) => format === 'give %s %ld %s.' ? money(1, format, a, b, c) : message(2, format, a, b, c),
      You_feel: (format, a, b, c) => message(3, format, a, b, c),
      verbalize: (format, a, b, c) => message(4, format, a, b, c),
      impossible: (format, a, b, c) => message(5, format, a, b, c),
      panic: (format, a, b, c) => message(6, format, a, b, c),
    };
  },
  $teleportMinionCall__deps: ['$teleportMinionServices', '$stackSave', '$stackRestore'],
  $teleportMinionCall: function(name, ...args) {
    var stack = stackSave();
    try { return Module['nethackPorted'].minion(teleportMinionServices(), name, ...args); }
    finally { stackRestore(stack); }
  },
  newemin__deps: ['$teleportMinionCall'], newemin__sig: 'vp', newemin: function(mon) { teleportMinionCall('newemin', mon); },
  free_emin__deps: ['$teleportMinionCall'], free_emin__sig: 'vp', free_emin: function(mon) { teleportMinionCall('free_emin', mon); },
  monster_census__deps: ['$teleportMinionCall'], monster_census__sig: 'ii', monster_census: function(spotted) { return teleportMinionCall('monster_census', spotted); },
  msummon__deps: ['$teleportMinionCall'], msummon__sig: 'ip', msummon: function(mon) { return teleportMinionCall('msummon', mon); },
  summon_minion__deps: ['$teleportMinionCall'], summon_minion__sig: 'vii', summon_minion: function(alignment, talk) { teleportMinionCall('summon_minion', alignment, talk); },
  demon_talk__deps: ['$teleportMinionCall'], demon_talk__sig: 'ip', demon_talk: function(mon) { return teleportMinionCall('demon_talk', mon); },
  bribe__deps: ['$teleportMinionCall'], bribe__sig: 'jpp', bribe: function(mon, prompt) { return teleportMinionCall('bribe', mon, prompt); },
  dprince__deps: ['$teleportMinionCall'], dprince__sig: 'ii', dprince: function(alignment) { return teleportMinionCall('dprince', alignment); },
  dlord__deps: ['$teleportMinionCall'], dlord__sig: 'ii', dlord: function(alignment) { return teleportMinionCall('dlord', alignment); },
  llord__deps: ['$teleportMinionCall'], llord__sig: 'i', llord: function() { return teleportMinionCall('llord'); },
  lminion__deps: ['$teleportMinionCall'], lminion__sig: 'i', lminion: function() { return teleportMinionCall('lminion'); },
  ndemon__deps: ['$teleportMinionCall'], ndemon__sig: 'ii', ndemon: function(alignment) { return teleportMinionCall('ndemon', alignment); },
  lose_guardian_angel__deps: ['$teleportMinionCall'], lose_guardian_angel__sig: 'vp', lose_guardian_angel: function(mon) { teleportMinionCall('lose_guardian_angel', mon); },
  gain_guardian_angel__deps: ['$teleportMinionCall'], gain_guardian_angel__sig: 'v', gain_guardian_angel: function() { teleportMinionCall('gain_guardian_angel'); },
});
