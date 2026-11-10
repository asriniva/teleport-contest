// Native calls, shared storage, variadic formatting and assertion ABI only.
addToLibrary({
  $teleportExperServices__deps: ['Goodbye', 'achieve_rank', 'acurr', 'adjabil', 'count_achievements', 'done', 'exp_percent_changing', 'find_mac', 'minuhpmax', 'monhp_per_lvl', 'newhp', 'record_achievement', 'rehumanize', 'resists_drli', 'setuhpmax', 'strcmp', 'strcpy', 'teleport_exper_assert_fail', 'teleport_exper_feel', 'teleport_exper_global', 'teleport_exper_log_int', 'teleport_exper_log_plain', 'teleport_exper_log_prefix', 'teleport_exper_monster_bit', 'teleport_exper_pline', 'teleport_exper_rn2', 'teleport_exper_rnd', 'teleport_exper_set_monster_bit', 'xlev_to_rank', '$stringToUTF8OnStack'],
  $teleportExperServices: function() {
    var text = value => typeof value === 'string' ? BigInt(stringToUTF8OnStack(value)) : BigInt(value || 0);
    var pointer = value => BigInt(value ? value.address ?? value : 0);
    var callers = { newpw: 0, rndexp: 1 };
    return {
      heap: () => HEAPU8,
      global: index => Number(_teleport_exper_global(index)),
      monsterBit: (mon, index) => _teleport_exper_monster_bit(BigInt(mon), index),
      setMonsterBit: (mon, index, value) => _teleport_exper_set_monster_bit(BigInt(mon), index, value),
      rn2: (value, line, caller) => _teleport_exper_rn2(value, line, callers[caller]),
      rnd: (value, line, caller) => _teleport_exper_rnd(value, line, callers[caller]),
      rn1: (x, y, line, caller) => _teleport_exper_rn2(x, line, callers[caller]) + y,
      acurr: attribute => _acurr(attribute),
      find_mac: mon => _find_mac(pointer(mon)),
      exp_percent_changing: () => _exp_percent_changing(),
      resists_drli: mon => _resists_drli(pointer(mon)),
      Goodbye: () => Number(_Goodbye()),
      adjabil: (oldlevel, newlevel) => _adjabil(oldlevel, newlevel),
      done: reason => _done(reason),
      minuhpmax: value => _minuhpmax(value),
      setuhpmax: (value, normal) => _setuhpmax(value, Number(normal)),
      monhp_per_lvl: mon => _monhp_per_lvl(pointer(mon)),
      rehumanize: () => _rehumanize(),
      newhp: () => _newhp(),
      xlev_to_rank: level => _xlev_to_rank(level),
      count_achievements: () => _count_achievements(),
      achieve_rank: rank => _achieve_rank(rank),
      record_achievement: achievement => _record_achievement(achievement << 24 >> 24),
      strcmp: (a, b) => _strcmp(text(a), text(b)),
      Strcpy: (out, value) => Number(_strcpy(BigInt(out), text(value))),
      pline: (format, prefix, level) => _teleport_exper_pline(text(format), text(prefix), level),
      You_feel: message => _teleport_exper_feel(text(message)),
      assert: condition => { if (!condition) _teleport_exper_assert_fail(); },
      livelog_printf: (category, format, ...args) => {
        if (args.length === 0) _teleport_exper_log_plain(BigInt(category), text(format));
        else if (args.length === 1) _teleport_exper_log_int(BigInt(category), text(format), args[0]);
        else _teleport_exper_log_prefix(BigInt(category), text(format), text(args[0]), args[1]);
      },
    };
  },
  $teleportExperCall__deps: ['$teleportExperServices', '$stackSave', '$stackRestore'],
  $teleportExperCall: function(name, ...args) {
    var stack = stackSave();
    try { return Module['nethackPorted'].exper(teleportExperServices(), name, ...args); }
    finally { stackRestore(stack); }
  },
  newuexp__deps: ['$teleportExperCall'], newuexp__sig: 'ji',
  newuexp: function(lev) { return teleportExperCall('newuexp', lev); },
  teleport_exper_test_enermod__deps: ['$teleportExperCall'], teleport_exper_test_enermod__sig: 'ii',
  teleport_exper_test_enermod: function(en) { return teleportExperCall('enermod', en); },
  newpw__deps: ['$teleportExperCall'], newpw__sig: 'i',
  newpw: function() { return teleportExperCall('newpw'); },
  experience__deps: ['$teleportExperCall'], experience__sig: 'ipi',
  experience: function(mtmp, nk) { return teleportExperCall('experience', mtmp, nk); },
  more_experienced__deps: ['$teleportExperCall'], more_experienced__sig: 'vii',
  more_experienced: function(exper, rexp) { teleportExperCall('more_experienced', exper, rexp); },
  losexp__deps: ['$teleportExperCall'], losexp__sig: 'vp',
  losexp: function(drainer) { teleportExperCall('losexp', drainer); },
  newexplevel__deps: ['$teleportExperCall'], newexplevel__sig: 'v',
  newexplevel: function() { teleportExperCall('newexplevel'); },
  pluslvl__deps: ['$teleportExperCall'], pluslvl__sig: 'vi',
  pluslvl: function(incr) { teleportExperCall('pluslvl', incr); },
  rndexp__deps: ['$teleportExperCall'], rndexp__sig: 'ji',
  rndexp: function(gaining) { return teleportExperCall('rndexp', gaining); },
});
