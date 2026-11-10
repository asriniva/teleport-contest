// Native storage/call ABI only; Rogue level algorithms live in JavaScript.
addToLibrary({
  $teleportExtralevServices__deps: ['add_room', 'christen_monst', 'curse', 'dodoor', 'makemon', 'mksobj_at', 'roguename', 'somex', 'somey', 'teleport_extralev_door_mask', 'teleport_extralev_global', 'teleport_extralev_impossible_one', 'teleport_extralev_impossible_two', 'teleport_extralev_object_bit', 'teleport_extralev_rn2', 'teleport_extralev_rnd', 'teleport_extralev_set_door_mask', 'teleport_extralev_set_object_bit', 'teleport_were_monster_bit', 'teleport_were_set_monster_bit', 'weight', '$stringToUTF8OnStack'],
  $teleportExtralevServices: function() {
    var text = value => typeof value === 'string' ? BigInt(stringToUTF8OnStack(value)) : BigInt(value || 0);
    var pointer = value => BigInt(value ? value.address ?? value : 0);
    var callers = { roguejoin: 0, roguecorr: 1, miniwalk: 2, makeroguerooms: 3, corr: 4, makerogueghost: 5 };
    return {
      heap: () => HEAPU8,
      global: index => Number(_teleport_extralev_global(index)),
      monsterBit: (mon, index) => _teleport_were_monster_bit(BigInt(mon), index),
      setMonsterBit: (mon, index, value) => _teleport_were_set_monster_bit(BigInt(mon), index, value),
      objectBit: (object, index) => _teleport_extralev_object_bit(BigInt(object), index),
      setObjectBit: (object, index, value) => _teleport_extralev_set_object_bit(BigInt(object), index, value),
      doorMask: location => _teleport_extralev_door_mask(BigInt(location)),
      setDoorMask: (location, value) => _teleport_extralev_set_door_mask(BigInt(location), value),
      rn2: (value, line, caller) => _teleport_extralev_rn2(value, line, callers[caller]),
      rnd: (value, line, caller) => _teleport_extralev_rnd(value, line, callers[caller]),
      rn1: (x, y, line, caller) => _teleport_extralev_rn2(x, line, callers[caller]) + y,
      impossible: (format, ...args) => {
        if (args.length === 1) _teleport_extralev_impossible_one(text(format), args[0]);
        else _teleport_extralev_impossible_two(text(format), args[0], args[1]);
      },
      dodoor: (x, y, room) => _dodoor(x, y, pointer(room)),
      add_room: (lx, ly, hx, hy, lit, type, special) => _add_room(lx, ly, hx, hy, Number(lit), type, Number(special)),
      somex: room => _somex(pointer(room)),
      somey: room => _somey(pointer(room)),
      roguename: () => Number(_roguename()),
      christen_monst: (mon, name) => Number(_christen_monst(pointer(mon), text(name))),
      mksobj_at: (type, x, y, initialize, artifact) => Number(_mksobj_at(type, x, y, Number(initialize), Number(artifact))),
      weight: object => _weight(pointer(object)),
      curse: object => _curse(pointer(object)),
      makemon: (pm, x, y, flags) => Number(_makemon(pointer(pm), x, y, Number(flags) >>> 0)),
    };
  },
  $teleportExtralevCall__deps: ['$teleportExtralevServices', '$stackSave', '$stackRestore'],
  $teleportExtralevCall: function(name, ...args) {
    var stack = stackSave();
    try { return Module['nethackPorted'].extralev(teleportExtralevServices(), name, ...args); }
    finally { stackRestore(stack); }
  },
  makeroguerooms__deps: ['$teleportExtralevCall'], makeroguerooms__sig: 'v',
  makeroguerooms: function() { teleportExtralevCall('makeroguerooms'); },
  corr__deps: ['$teleportExtralevCall'], corr__sig: 'vii',
  corr: function(x, y) { teleportExtralevCall('corr', x, y); },
  makerogueghost__deps: ['$teleportExtralevCall'], makerogueghost__sig: 'v',
  makerogueghost: function() { teleportExtralevCall('makerogueghost'); },
  teleport_extralev_test_join__deps: ['$teleportExtralevCall'], teleport_extralev_test_join__sig: 'viiiii',
  teleport_extralev_test_join: function(x1, y1, x2, y2, horiz) { teleportExtralevCall('roguejoin', x1, y1, x2, y2, horiz); },
  teleport_extralev_test_corridor__deps: ['$teleportExtralevCall'], teleport_extralev_test_corridor__sig: 'viii',
  teleport_extralev_test_corridor: function(x, y, dir) { teleportExtralevCall('roguecorr', x, y, dir); },
  teleport_extralev_test_walk__deps: ['$teleportExtralevCall'], teleport_extralev_test_walk__sig: 'vii',
  teleport_extralev_test_walk: function(x, y) { teleportExtralevCall('miniwalk', x, y); },
});
