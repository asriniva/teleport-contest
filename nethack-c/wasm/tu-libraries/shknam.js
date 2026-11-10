// Shop data startup, native dependencies and typed ABI access only.
addToLibrary({
  $teleportShknamServices__deps: ['teleport_shknam_storage', 'teleport_shknam_global', 'teleport_shknam_birthday', 'teleport_shknam_object_class_bit', 'teleport_shknam_monster_bit', 'teleport_shknam_set_monster_bit', 'teleport_shknam_terrain_bit', 'teleport_shknam_set_terrain_bit', 'teleport_shknam_level_bit', 'teleport_shknam_set_level_bit', 'teleport_shknam_special_town', 'teleport_shknam_context_bit', 'teleport_shknam_set_context_bit', 'teleport_shknam_free', 'teleport_shknam_rn2', 'teleport_shknam_rnd', 'teleport_shknam_assert', 'teleport_shknam_panic', 'teleport_shknam_panic_ints', 'teleport_shknam_impossible', 'teleport_shknam_pline', 'teleport_shknam_format', 'teleport_shknam_display_window', 'teleport_shknam_win_message', 'teleport_shknam_literal_storage', 'teleport_shknam_literal_capacity', 'alloc', 'memset', 'strcmp', 'strcpy', 'strncpy', 'newmextra', 'mksobj_at', 'set_tin_variety', 'depth', 'mkclass', 'makemon', 'mkobj_at', 'Is_special', 'In_mines', 'highc', 'letter', 'ledger_no', 'isok', 'rloc', 'set_malign', 'mon_learns_traps', 'assign_level', 'mkmonmoney', 'mongets', 'distmin', 'newsym', 'cvt_sdoor_to_door', 'inside_shop', 'make_engr_at', 'in_rooms', 'on_level', 'shop_keeper', 'mongone', 'noit_mon_nam', 'in_town', '$lengthBytesUTF8', '$stringToUTF8', '$stackAlloc', '$stackSave', '$stackRestore'],
  $teleportShknamServices: function() {
    var state = Module['teleportShknamCache'] ||= { next: 0, strings: new Map() };
    var pointer = value => BigInt(value ? value.address ?? value : 0);
    var coord = value => Number(BigInt.asIntN(16, BigInt(value)));
    var byte = value => Number(BigInt.asIntN(8, BigInt(value)));
    var literal = value => {
      if (state.strings.has(value)) return state.strings.get(value);
      var size = lengthBytesUTF8(value) + 1;
      if (state.next + size > Number(_teleport_shknam_literal_capacity())) throw new Error('Review changed shop-name literal corpus');
      var at = Number(_teleport_shknam_literal_storage()) + state.next;
      stringToUTF8(value, at, size);
      state.next += size;
      state.strings.set(value, at);
      return at;
    };
    var text = value => typeof value === 'string' ? BigInt(literal(value)) : pointer(value);
    return {
      moduleKey: state, heap: () => HEAPU8, literal,
      stackAlloc: size => Number(stackAlloc(size)),
      stackSave: () => stackSave(),
      stackRestore: saved => stackRestore(saved),
      storage: index => Number(_teleport_shknam_storage(index)),
      global: index => Number(_teleport_shknam_global(index)),
      birthday: () => _teleport_shknam_birthday(),
      objectClassBit: (obj, index) => _teleport_shknam_object_class_bit(pointer(obj), index),
      monsterBit: (mon, index) => _teleport_shknam_monster_bit(pointer(mon), index),
      setMonsterBit: (mon, index, value) => _teleport_shknam_set_monster_bit(pointer(mon), index, Number(value) >>> 0),
      terrainBit: (x, y, index) => _teleport_shknam_terrain_bit(coord(x), coord(y), index),
      setTerrainBit: (x, y, index, value) => _teleport_shknam_set_terrain_bit(coord(x), coord(y), index, Number(value) >>> 0),
      levelBit: index => _teleport_shknam_level_bit(index),
      setLevelBit: (index, value) => _teleport_shknam_set_level_bit(index, Number(value) >>> 0),
      specialTown: level => _teleport_shknam_special_town(pointer(level)),
      contextBit: index => _teleport_shknam_context_bit(index),
      setContextBit: (index, value) => _teleport_shknam_set_context_bit(index, Number(value) >>> 0),
      alloc: size => Number(_alloc(Number(size) >>> 0)),
      free: ptr => _teleport_shknam_free(pointer(ptr)),
      memset: (out, value, size) => Number(_memset(pointer(out), value, BigInt(size))),
      strcmp: (a, b) => _strcmp(text(a), text(b)),
      Strcpy: (out, value) => Number(_strcpy(pointer(out), text(value))),
      strncpy: (out, value, size) => Number(_strncpy(pointer(out), text(value), BigInt(size))),
      newmextra: () => Number(_newmextra()),
      mksobj_at: (type, x, y, init, artif) => Number(_mksobj_at(type, coord(x), coord(y), byte(init), byte(artif))),
      set_tin_variety: (obj, variety) => _set_tin_variety(pointer(obj), variety),
      depth: level => _depth(pointer(level)),
      mkclass: (sym, flags) => Number(_mkclass(byte(sym), flags)),
      makemon: (mon, x, y, flags) => Number(_makemon(pointer(mon), coord(x), coord(y), Number(BigInt.asUintN(32, BigInt(flags))))),
      mkobj_at: (type, x, y, init) => Number(_mkobj_at(byte(type), coord(x), coord(y), byte(init))),
      Is_special: level => Number(_Is_special(pointer(level))),
      In_mines: level => _In_mines(pointer(level)),
      highc: ch => _highc(byte(ch)),
      letter: ch => _letter(byte(ch)),
      ledger_no: level => _ledger_no(pointer(level)),
      isok: (x, y) => _isok(coord(x), coord(y)),
      rloc: (mon, flags) => _rloc(pointer(mon), flags >>> 0),
      set_malign: mon => _set_malign(pointer(mon)),
      mon_learns_traps: (mon, traps) => _mon_learns_traps(pointer(mon), traps),
      assign_level: (out, source) => _assign_level(pointer(out), pointer(source)),
      mkmonmoney: (mon, money) => _mkmonmoney(pointer(mon), BigInt.asIntN(64, BigInt(money))),
      mongets: (mon, type) => Number(_mongets(pointer(mon), type)),
      distmin: (x, y, xx, yy) => _distmin(coord(x), coord(y), coord(xx), coord(yy)),
      newsym: (x, y) => _newsym(coord(x), coord(y)),
      cvt_sdoor_to_door: rm => _cvt_sdoor_to_door(pointer(rm)),
      inside_shop: (x, y) => _inside_shop(coord(x), coord(y)),
      make_engr_at: (x, y, value, gravetext, time, type) => _make_engr_at(coord(x), coord(y), text(value), text(gravetext), BigInt.asIntN(64, BigInt(time)), type),
      in_rooms: (x, y, type) => Number(_in_rooms(coord(x), coord(y), type)),
      on_level: (a, b) => _on_level(pointer(a), pointer(b)),
      shop_keeper: room => Number(_shop_keeper(byte(room))),
      mongone: mon => _mongone(pointer(mon)),
      noit_mon_nam: mon => Number(_noit_mon_nam(pointer(mon))),
      in_town: (x, y) => _in_town(coord(x), coord(y)),
      rn2: (bound, line, caller) => _teleport_shknam_rn2(bound, line, caller),
      rnd: (bound, line, caller) => _teleport_shknam_rnd(bound, line, caller),
      assert: (condition, index) => { if (!condition) _teleport_shknam_assert(index); },
      panic: (format, ...args) => args.length === 2
        ? _teleport_shknam_panic_ints(text(format), args[0], args[1])
        : _teleport_shknam_panic(text(format), text(args[0]), 0, 0),
      impossible: (format, name) => _teleport_shknam_impossible(text(format), text(name)),
      pline: (format, a, b, c, d) => _teleport_shknam_pline(text(format), a ?? 0, b ?? 0, c ?? 0, d ?? 0),
      Sprintf: (out, format) => _teleport_shknam_format(pointer(out), text(format)),
      display_nhwindow: (win, blocking) => _teleport_shknam_display_window(win, byte(blocking)),
      winMessage: () => _teleport_shknam_win_message(),
    };
  },
  $teleportShknamInit__deps: ['$teleportShknamServices', '$addOnInit'],
  $teleportShknamInit__postset: "addOnInit(() => Module['nethackPorted'].initializeShknam(teleportShknamServices()));",
  $teleportShknamInit: 0,
  $teleportShknamCall__deps: ['$teleportShknamInit', '$stackSave', '$stackRestore'],
  $teleportShknamCall: function(name, ...args) {
    var stack = stackSave();
    try { return Module['nethackPorted'].shknam(teleportShknamServices(), name, ...args); }
    finally { stackRestore(stack); }
  },
  neweshk__deps: ['$teleportShknamCall'], neweshk__sig: 'vp',
  neweshk: function(mon) { teleportShknamCall('neweshk', mon); },
  free_eshk__deps: ['$teleportShknamCall'], free_eshk__sig: 'vp',
  free_eshk: function(mon) { teleportShknamCall('free_eshk', mon); },
  stock_room__deps: ['$teleportShknamCall'], stock_room__sig: 'vip',
  stock_room: function(index, room) { teleportShknamCall('stock_room', index, room); },
  saleable__deps: ['$teleportShknamCall'], saleable__sig: 'ipp',
  saleable: function(mon, obj) { return teleportShknamCall('saleable', mon, obj); },
  get_shop_item__deps: ['$teleportShknamCall'], get_shop_item__sig: 'ii',
  get_shop_item: function(type) { return teleportShknamCall('get_shop_item', type); },
  Shknam__deps: ['$teleportShknamCall'], Shknam__sig: 'pp',
  Shknam: function(mon) { return teleportShknamCall('Shknam', mon); },
  shkname__deps: ['$teleportShknamCall'], shkname__sig: 'pp',
  shkname: function(mon) { return teleportShknamCall('shkname', mon); },
  shkname_is_pname__deps: ['$teleportShknamCall'], shkname_is_pname__sig: 'ip',
  shkname_is_pname: function(mon) { return teleportShknamCall('shkname_is_pname', mon); },
  is_izchak__deps: ['$teleportShknamCall'], is_izchak__sig: 'ipi',
  is_izchak: function(mon, override) { return teleportShknamCall('is_izchak', mon, override << 24 >> 24); },
  teleport_shknam_test_stockpos__deps: ['$teleportShknamCall'], teleport_shknam_test_stockpos__sig: 'ipiiii',
  teleport_shknam_test_stockpos: function(room, rmno, sh, x, y) { return teleportShknamCall('stock_room_goodpos', room, rmno, sh, x, y); },
  teleport_shknam_test_veggy__deps: ['$teleportShknamCall'], teleport_shknam_test_veggy__sig: 'ipi',
  teleport_shknam_test_veggy: function(obj, type) { return teleportShknamCall('veggy_item', obj, type); },
  teleport_shknam_test_veg__deps: ['$teleportShknamCall'], teleport_shknam_test_veg__sig: 'i',
  teleport_shknam_test_veg: function() { return teleportShknamCall('shkveg'); },
  teleport_shknam_test_mkveggy__deps: ['$teleportShknamCall'], teleport_shknam_test_mkveggy__sig: 'vii',
  teleport_shknam_test_mkveggy: function(x, y) { teleportShknamCall('mkveggy_at', x, y); },
  teleport_shknam_test_mkshobj__deps: ['$teleportShknamCall'], teleport_shknam_test_mkshobj__sig: 'vpiii',
  teleport_shknam_test_mkshobj: function(shop, x, y, special) { teleportShknamCall('mkshobj_at', shop, x, y, special << 24 >> 24); },
  teleport_shknam_test_names__deps: ['$teleportShknamCall'], teleport_shknam_test_names__sig: 'vpp',
  teleport_shknam_test_names: function(mon, names) { teleportShknamCall('nameshk', mon, names); },
  teleport_shknam_test_door__deps: ['$teleportShknamCall'], teleport_shknam_test_door__sig: 'ippp',
  teleport_shknam_test_door: function(room, x, y) { return teleportShknamCall('good_shopdoor', room, x, y); },
  teleport_shknam_test_init__deps: ['$teleportShknamCall'], teleport_shknam_test_init__sig: 'ipp',
  teleport_shknam_test_init: function(shop, room) { return teleportShknamCall('shkinit', shop, room); },
});
