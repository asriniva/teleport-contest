// Shared data, string lifetime and native-call ABI only; TU algorithms are JS.
addToLibrary({
  $teleportMplayerServices__deps: ['bless', 'christen_monst', 'curse', 'goodpos', 'is_art', 'm_dowear', 'makemon', 'mk_artifact', 'mkmonmoney', 'mkobj', 'mksobj', 'mongets', 'monmightthrowwep', 'mpickobj', 'rank_of', 'rloc', 'rnd_class', 'rnd_defensive_item', 'rnd_misc_item', 'rnd_offensive_item', 'set_malign', 'set_mon_data', 'strcat', 'strcmp', 'strcpy', 'strlen', 'strncmp', 'teleport_mplayer_class_bit', 'teleport_mplayer_dice', 'teleport_mplayer_global', 'teleport_mplayer_impossible', 'teleport_mplayer_monster_bit', 'teleport_mplayer_object_bit', 'teleport_mplayer_rn2', 'teleport_mplayer_rnd', 'teleport_mplayer_set_monster_bit', 'teleport_mplayer_set_object_bit', 'teleport_mplayer_verbalize', 'weight', 'teleport_mplayer_literal_storage', 'teleport_mplayer_literal_capacity', '$lengthBytesUTF8', '$stringToUTF8', '$stackAlloc'],
  $teleportMplayerServices: function() {
    var state = Module['teleportMplayerLiterals'] ||= { next: 0, strings: new Map() };
    var literal = value => {
      if (state.strings.has(value)) return state.strings.get(value);
      var size = lengthBytesUTF8(value) + 1;
      var capacity = Number(_teleport_mplayer_literal_capacity());
      if (state.next + size > capacity) throw new Error('Review changed mplayer literal corpus');
      var at = Number(_teleport_mplayer_literal_storage()) + state.next;
      stringToUTF8(value, at, size);
      state.next += size;
      state.strings.set(value, at);
      return at;
    };
    var text = value => BigInt(typeof value === 'string' ? literal(value) : value || 0);
    var pointer = value => BigInt(value ? value.address ?? value : 0);
    var callers = { dev_name: 0, get_mplname: 1, mk_mplayer_armor: 2, mk_mplayer: 3, create_mplayers: 4, mplayer_talk: 5 };
    return {
      heap: () => HEAPU8,
      stackAlloc: size => stackAlloc(size),
      literal,
      global: index => Number(_teleport_mplayer_global(index)),
      monsterBit: (mon, index) => _teleport_mplayer_monster_bit(BigInt(mon), index),
      setMonsterBit: (mon, index, value) => _teleport_mplayer_set_monster_bit(BigInt(mon), index, value),
      objectBit: (object, index) => _teleport_mplayer_object_bit(BigInt(object), index),
      setObjectBit: (object, index, value) => _teleport_mplayer_set_object_bit(BigInt(object), index, value),
      objectClassBit: type => _teleport_mplayer_class_bit(BigInt(type)),
      rn2: (value, line, caller) => _teleport_mplayer_rn2(value, line, callers[caller]),
      rnd: (value, line, caller) => _teleport_mplayer_rnd(value, line, callers[caller]),
      rn1: (x, y, line, caller) => _teleport_mplayer_rn2(x, line, callers[caller]) + y,
      d: (count, sides, line, caller) => _teleport_mplayer_dice(count, sides, line, callers[caller]),
      impossible: message => _teleport_mplayer_impossible(text(message)),
      verbalize: (format, message) => _teleport_mplayer_verbalize(text(format), text(message)),
      strlen: value => Number(_strlen(text(value))),
      strcmp: (a, b) => _strcmp(text(a), text(b)),
      strncmp: (a, b, length) => _strncmp(text(a), text(b), BigInt(length)),
      Strcpy: (out, value) => Number(_strcpy(BigInt(out), text(value))),
      Strcat: (out, value) => Number(_strcat(BigInt(out), text(value))),
      rank_of: (level, pm, female) => Number(_rank_of(level, pm << 16 >> 16, Number(female))),
      rloc: (mon, flags) => _rloc(pointer(mon), Number(flags) >>> 0),
      makemon: (pm, x, y, flags) => Number(_makemon(pointer(pm), x, y, Number(flags) >>> 0)),
      christen_monst: (mon, name) => Number(_christen_monst(pointer(mon), text(name))),
      mongets: (mon, type) => Number(_mongets(pointer(mon), type)),
      set_malign: mon => _set_malign(pointer(mon)),
      rnd_class: (low, high) => _rnd_class(low, high),
      mksobj: (type, initialize, artifact) => Number(_mksobj(type, Number(initialize), Number(artifact))),
      curse: object => _curse(pointer(object)),
      bless: object => _bless(pointer(object)),
      mpickobj: (mon, object) => _mpickobj(pointer(mon), pointer(object)),
      mk_artifact: (object, align, chance, force) => Number(_mk_artifact(pointer(object), Number(align) << 24 >> 24, Number(chance) & 255, Number(force))),
      monmightthrowwep: object => _monmightthrowwep(pointer(object)),
      weight: object => _weight(pointer(object)),
      is_art: (object, artifact) => _is_art(pointer(object), artifact),
      m_dowear: (mon, creation) => _m_dowear(pointer(mon), Number(creation)),
      mkmonmoney: (mon, amount) => _mkmonmoney(pointer(mon), BigInt(amount)),
      mkobj: (type, artifact) => Number(_mkobj(type, Number(artifact))),
      rnd_offensive_item: mon => _rnd_offensive_item(pointer(mon)),
      rnd_defensive_item: mon => _rnd_defensive_item(pointer(mon)),
      rnd_misc_item: mon => _rnd_misc_item(pointer(mon)),
      set_mon_data: (mon, data) => _set_mon_data(pointer(mon), pointer(data)),
      goodpos: (x, y, mon, flags) => _goodpos(x << 16 >> 16, y << 16 >> 16, pointer(mon), Number(flags) >>> 0),
    };
  },
  $teleportMplayerCall__deps: ['$teleportMplayerServices', '$stackSave', '$stackRestore'],
  $teleportMplayerCall: function(name, ...args) {
    var stack = stackSave();
    try { return Module['nethackPorted'].mplayer(teleportMplayerServices(), name, ...args); }
    finally { stackRestore(stack); }
  },
  mk_mplayer__deps: ['$teleportMplayerCall'], mk_mplayer__sig: 'ppiii',
  mk_mplayer: function(ptr, x, y, special) { return teleportMplayerCall('mk_mplayer', ptr, x, y, special); },
  create_mplayers__deps: ['$teleportMplayerCall'], create_mplayers__sig: 'vii',
  create_mplayers: function(num, special) { teleportMplayerCall('create_mplayers', num, special); },
  mplayer_talk__deps: ['$teleportMplayerCall'], mplayer_talk__sig: 'vp',
  mplayer_talk: function(mtmp) { teleportMplayerCall('mplayer_talk', mtmp); },
  teleport_mplayer_test_dev_name__deps: ['$teleportMplayerCall'], teleport_mplayer_test_dev_name__sig: 'p',
  teleport_mplayer_test_dev_name: function() { return teleportMplayerCall('dev_name'); },
  teleport_mplayer_test_name__deps: ['$teleportMplayerCall'], teleport_mplayer_test_name__sig: 'vpp',
  teleport_mplayer_test_name: function(mtmp, nam) { teleportMplayerCall('get_mplname', mtmp, nam); },
  teleport_mplayer_test_armor__deps: ['$teleportMplayerCall'], teleport_mplayer_test_armor__sig: 'vpi',
  teleport_mplayer_test_armor: function(mon, typ) { teleportMplayerCall('mk_mplayer_armor', mon, typ); },
});
