// Native dependencies, packed fields and typed message ABI only.
addToLibrary({
  $teleportQuestServices__deps: ['Is_special', 'Monnam', 'adjalign', 'align_str', 'angry_guards', 'canseemon', 'carrying', 'com_pager', 'create_gas_cloud', 'deltrap', 'dungeon_branch', 'exercise', 'find_quest_artifact', 'fully_identify_obj', 'is_quest_artifact', 'mon_nam', 'monnear', 'noit_mon_nam', 'nomul', 'observe_object', 'on_level', 'qt_pager', 'remdun_mapseen', 'schedule_goto', 'setmangry', 'the', 'update_inventory', 'xname', 'yn_function', 'teleport_quest_global', 'teleport_quest_bit', 'teleport_quest_set_bit', 'teleport_quest_hero_bit', 'teleport_quest_set_hero_bit', 'teleport_quest_monster_bit', 'teleport_quest_set_monster_bit', 'teleport_quest_trap_type', 'teleport_quest_message', 'teleport_quest_you_ints', 'teleport_quest_livelog', 'teleport_quest_rn2', 'teleport_quest_literal_storage', 'teleport_quest_literal_capacity', '$lengthBytesUTF8', '$stringToUTF8'],
  $teleportQuestServices: function() {
    var state = Module['teleportQuestLiterals'] ||= { next: 0, strings: new Map() };
    var literal = value => {
      if (state.strings.has(value)) return state.strings.get(value);
      var size = lengthBytesUTF8(value) + 1;
      if (state.next + size > Number(_teleport_quest_literal_capacity())) throw new Error('Review changed quest literal corpus');
      var at = Number(_teleport_quest_literal_storage()) + state.next;
      stringToUTF8(value, at, size);
      state.next += size;
      state.strings.set(value, at);
      return at;
    };
    var pointer = value => BigInt(value ? value.address ?? value : 0);
    var text = value => typeof value === 'string' ? BigInt(literal(value)) : pointer(value);
    var message = (kind, format, a = 0, b = 0) => _teleport_quest_message(kind, text(format), text(a), text(b));
    return {
      heap: () => HEAPU8,
      global: index => Number(_teleport_quest_global(index)),
      questBit: index => _teleport_quest_bit(index),
      setQuestBit: (index, value) => _teleport_quest_set_bit(index, Number(value)),
      heroBit: index => _teleport_quest_hero_bit(index),
      setHeroBit: (index, value) => _teleport_quest_set_hero_bit(index, Number(value)),
      monsterBit: (mon, index) => _teleport_quest_monster_bit(pointer(mon), index),
      setMonsterBit: (mon, index, value) => _teleport_quest_set_monster_bit(pointer(mon), index, Number(value)),
      trapType: trap => _teleport_quest_trap_type(pointer(trap)),
      qt_pager: value => _qt_pager(text(value)),
      com_pager: value => _com_pager(text(value)),
      find_quest_artifact: flags => Number(_find_quest_artifact(flags >>> 0)),
      Is_special: level => Number(_Is_special(pointer(level))),
      on_level: (a, b) => _on_level(pointer(a), pointer(b)),
      observe_object: obj => _observe_object(pointer(obj)),
      exercise: (attribute, positive) => _exercise(attribute, Number(positive) << 24 >> 24),
      align_str: alignment => Number(_align_str(alignment << 24 >> 24)),
      yn_function: (query, choices, initial, history) => _yn_function(text(query), text(choices), (typeof initial === 'string' ? initial.charCodeAt(0) : initial) << 24 >> 24, Number(history) << 24 >> 24),
      dungeon_branch: name => Number(_dungeon_branch(text(name))),
      nomul: value => _nomul(value),
      schedule_goto: (dest, flags, pre, post) => _schedule_goto(pointer(dest), flags, text(pre), text(post)),
      remdun_mapseen: dungeon => _remdun_mapseen(dungeon),
      deltrap: trap => _deltrap(pointer(trap)),
      is_quest_artifact: obj => _is_quest_artifact(pointer(obj)),
      fully_identify_obj: obj => _fully_identify_obj(pointer(obj)),
      xname: obj => Number(_xname(pointer(obj))),
      the: value => Number(_the(text(value))),
      carrying: type => Number(_carrying(type)),
      update_inventory: () => _update_inventory(),
      livelog_printf: (category, format, name) => _teleport_quest_livelog(BigInt(category), text(format), text(name)),
      noit_mon_nam: mon => Number(_noit_mon_nam(pointer(mon))),
      rn2: (bound, line) => _teleport_quest_rn2(bound, line),
      create_gas_cloud: (x, y, radius, damage) => Number(_create_gas_cloud(x << 16 >> 16, y << 16 >> 16, radius, damage)),
      canseemon: mon => _canseemon(pointer(mon)),
      Monnam: mon => Number(_Monnam(pointer(mon))),
      adjalign: value => _adjalign(value),
      angry_guards: silent => _angry_guards(Number(silent) << 24 >> 24),
      setmangry: (mon, silent) => _setmangry(pointer(mon), Number(silent) << 24 >> 24),
      mon_nam: mon => Number(_mon_nam(pointer(mon))),
      monnear: (mon, x, y) => _monnear(pointer(mon), x << 16 >> 16, y << 16 >> 16),
      You: (format, a, b) => {
        if (format === 'are currently %d and require %d.') _teleport_quest_you_ints(text(format), a, b);
        else message(1, format, a, b);
      },
      pline: (format, a, b) => message(0, format, a, b),
      verbalize: (format, a, b) => message(2, format, a, b),
      impossible: (format, a, b) => message(3, format, a, b),
    };
  },
  $teleportQuestCall__deps: ['$teleportQuestServices', '$stackSave', '$stackRestore'],
  $teleportQuestCall: function(name, ...args) {
    var stack = stackSave();
    try { return Module['nethackPorted'].quest(teleportQuestServices(), name, ...args); }
    finally { stackRestore(stack); }
  },
  onquest__deps: ['$teleportQuestCall'], onquest__sig: 'v', onquest: function() { teleportQuestCall('onquest'); },
  nemdead__deps: ['$teleportQuestCall'], nemdead__sig: 'v', nemdead: function() { teleportQuestCall('nemdead'); },
  leaddead__deps: ['$teleportQuestCall'], leaddead__sig: 'v', leaddead: function() { teleportQuestCall('leaddead'); },
  artitouch__deps: ['$teleportQuestCall'], artitouch__sig: 'vp', artitouch: function(obj) { teleportQuestCall('artitouch', obj); },
  ok_to_quest__deps: ['$teleportQuestCall'], ok_to_quest__sig: 'i', ok_to_quest: function() { return teleportQuestCall('ok_to_quest'); },
  finish_quest__deps: ['$teleportQuestCall'], finish_quest__sig: 'vp', finish_quest: function(obj) { teleportQuestCall('finish_quest', obj); },
  leader_speaks__deps: ['$teleportQuestCall'], leader_speaks__sig: 'vp', leader_speaks: function(mon) { teleportQuestCall('leader_speaks', mon); },
  nemesis_speaks__deps: ['$teleportQuestCall'], nemesis_speaks__sig: 'v', nemesis_speaks: function() { teleportQuestCall('nemesis_speaks'); },
  nemesis_stinks__deps: ['$teleportQuestCall'], nemesis_stinks__sig: 'vii', nemesis_stinks: function(mx, my) { teleportQuestCall('nemesis_stinks', mx, my); },
  quest_chat__deps: ['$teleportQuestCall'], quest_chat__sig: 'vp', quest_chat: function(mon) { teleportQuestCall('quest_chat', mon); },
  quest_talk__deps: ['$teleportQuestCall'], quest_talk__sig: 'vp', quest_talk: function(mon) { teleportQuestCall('quest_talk', mon); },
  quest_stat_check__deps: ['$teleportQuestCall'], quest_stat_check__sig: 'vp', quest_stat_check: function(mon) { teleportQuestCall('quest_stat_check', mon); },
  teleport_quest_test_on_start__deps: ['$teleportQuestCall'], teleport_quest_test_on_start__sig: 'v', teleport_quest_test_on_start: function() { teleportQuestCall('on_start'); },
  teleport_quest_test_on_locate__deps: ['$teleportQuestCall'], teleport_quest_test_on_locate__sig: 'v', teleport_quest_test_on_locate: function() { teleportQuestCall('on_locate'); },
  teleport_quest_test_on_goal__deps: ['$teleportQuestCall'], teleport_quest_test_on_goal__sig: 'v', teleport_quest_test_on_goal: function() { teleportQuestCall('on_goal'); },
  teleport_quest_test_not_capable__deps: ['$teleportQuestCall'], teleport_quest_test_not_capable__sig: 'i', teleport_quest_test_not_capable: function() { return teleportQuestCall('not_capable'); },
  teleport_quest_test_is_pure__deps: ['$teleportQuestCall'], teleport_quest_test_is_pure__sig: 'ii', teleport_quest_test_is_pure: function(talk) { return teleportQuestCall('is_pure', talk); },
  teleport_quest_test_expulsion__deps: ['$teleportQuestCall'], teleport_quest_test_expulsion__sig: 'vi', teleport_quest_test_expulsion: function(seal) { teleportQuestCall('expulsion', seal); },
  teleport_quest_test_chat_with_leader__deps: ['$teleportQuestCall'], teleport_quest_test_chat_with_leader__sig: 'vp', teleport_quest_test_chat_with_leader: function(mon) { teleportQuestCall('chat_with_leader', mon); },
  teleport_quest_test_chat_with_nemesis__deps: ['$teleportQuestCall'], teleport_quest_test_chat_with_nemesis__sig: 'v', teleport_quest_test_chat_with_nemesis: function() { teleportQuestCall('chat_with_nemesis'); },
  teleport_quest_test_chat_with_guardian__deps: ['$teleportQuestCall'], teleport_quest_test_chat_with_guardian__sig: 'v', teleport_quest_test_chat_with_guardian: function() { teleportQuestCall('chat_with_guardian'); },
  teleport_quest_test_prisoner_speaks__deps: ['$teleportQuestCall'], teleport_quest_test_prisoner_speaks__sig: 'vp', teleport_quest_test_prisoner_speaks: function(mon) { teleportQuestCall('prisoner_speaks', mon); },
});
