// Shared map/room data and native-call ABI only; generation logic is JS.
addToLibrary({
  $teleportMkmapServices__deps: ['add_room', 'alloc', 'depth', 'dig_corridor', 'free', 'isok', 'somexy', 'teleport_mkmap_global', 'teleport_mkmap_impossible', 'teleport_mkmap_level_bit', 'teleport_mkmap_rn2', 'teleport_mkmap_rnd', 'teleport_mkmap_set_level_bit', 'teleport_mkmap_set_terrain_bit', 'teleport_mkmap_terrain_bit', 'wallify_map', '$stringToUTF8OnStack', '$stackAlloc'],
  $teleportMkmapServices: function() {
    var pointer = value => BigInt(value ? value.address ?? value : 0);
    var callers = { init_fill: 0, join_map: 1, litstate_rnd: 2 };
    return {
      heap: () => HEAPU8,
      stackAlloc: size => stackAlloc(size),
      global: index => Number(_teleport_mkmap_global(index)),
      terrainBit: (location, index) => _teleport_mkmap_terrain_bit(BigInt(location), index),
      setTerrainBit: (location, index, value) => _teleport_mkmap_set_terrain_bit(BigInt(location), index, value),
      levelBit: index => _teleport_mkmap_level_bit(index),
      setLevelBit: (index, value) => _teleport_mkmap_set_level_bit(index, value),
      rn2: (value, line, caller) => _teleport_mkmap_rn2(value, line, callers[caller]),
      rnd: (value, line, caller) => _teleport_mkmap_rnd(value, line, callers[caller]),
      rn1: (x, y, line, caller) => _teleport_mkmap_rn2(x, line, callers[caller]) + y,
      alloc: size => Number(_alloc(size >>> 0)),
      free: value => _free(pointer(value)),
      impossible: message => _teleport_mkmap_impossible(BigInt(stringToUTF8OnStack(message))),
      isok: (x, y) => _isok(x << 16 >> 16, y << 16 >> 16),
      depth: level => _depth(pointer(level)),
      abs: value => Math.abs(value) | 0,
      add_room: (lx, ly, hx, hy, lit, type, special) => _add_room(lx, ly, hx, hy, Number(lit), type, Number(special)),
      somexy: (room, coord) => _somexy(pointer(room), pointer(coord)),
      dig_corridor: (start, end, costs, exact, foreground, background) => _dig_corridor(pointer(start), pointer(end), pointer(costs), Number(exact), foreground, background),
      wallify_map: (lx, ly, hx, hy) => _wallify_map(lx, ly, hx, hy),
    };
  },
  $teleportMkmapCall__deps: ['$teleportMkmapServices', '$stackSave', '$stackRestore'],
  $teleportMkmapCall: function(name, ...args) {
    var stack = stackSave();
    try { return Module['nethackPorted'].mkmap(teleportMkmapServices(), name, ...args); }
    finally { stackRestore(stack); }
  },
  flood_fill_rm__deps: ['$teleportMkmapCall'], flood_fill_rm__sig: 'viiiii',
  flood_fill_rm: function(sx, sy, rmno, lit, anyroom) { teleportMkmapCall('flood_fill_rm', sx, sy, rmno, lit, anyroom); },
  remove_rooms__deps: ['$teleportMkmapCall'], remove_rooms__sig: 'viiii',
  remove_rooms: function(lx, ly, hx, hy) { teleportMkmapCall('remove_rooms', lx, ly, hx, hy); },
  litstate_rnd__deps: ['$teleportMkmapCall'], litstate_rnd__sig: 'ii',
  litstate_rnd: function(litstate) { return teleportMkmapCall('litstate_rnd', litstate); },
  mkmap__deps: ['$teleportMkmapCall'], mkmap__sig: 'vp',
  mkmap: function(init_lev) { teleportMkmapCall('mkmap', init_lev); },
  teleport_mkmap_test_init_map__deps: ['$teleportMkmapCall'], teleport_mkmap_test_init_map__sig: 'vi',
  teleport_mkmap_test_init_map: function(bg) { teleportMkmapCall('init_map', bg); },
  teleport_mkmap_test_init_fill__deps: ['$teleportMkmapCall'], teleport_mkmap_test_init_fill__sig: 'vii',
  teleport_mkmap_test_init_fill: function(bg, fg) { teleportMkmapCall('init_fill', bg, fg); },
  teleport_mkmap_test_get_map__deps: ['$teleportMkmapCall'], teleport_mkmap_test_get_map__sig: 'iiii',
  teleport_mkmap_test_get_map: function(col, row, bg) { return teleportMkmapCall('get_map', col, row, bg); },
  teleport_mkmap_test_pass_one__deps: ['$teleportMkmapCall'], teleport_mkmap_test_pass_one__sig: 'vii',
  teleport_mkmap_test_pass_one: function(bg, fg) { teleportMkmapCall('pass_one', bg, fg); },
  teleport_mkmap_test_pass_two__deps: ['$teleportMkmapCall'], teleport_mkmap_test_pass_two__sig: 'vii',
  teleport_mkmap_test_pass_two: function(bg, fg) { teleportMkmapCall('pass_two', bg, fg); },
  teleport_mkmap_test_pass_three__deps: ['$teleportMkmapCall'], teleport_mkmap_test_pass_three__sig: 'vii',
  teleport_mkmap_test_pass_three: function(bg, fg) { teleportMkmapCall('pass_three', bg, fg); },
  teleport_mkmap_test_join_map_cleanup__deps: ['$teleportMkmapCall'], teleport_mkmap_test_join_map_cleanup__sig: 'v',
  teleport_mkmap_test_join_map_cleanup: function() { teleportMkmapCall('join_map_cleanup'); },
  teleport_mkmap_test_join_map__deps: ['$teleportMkmapCall'], teleport_mkmap_test_join_map__sig: 'vii',
  teleport_mkmap_test_join_map: function(bg, fg) { teleportMkmapCall('join_map', bg, fg); },
  teleport_mkmap_test_finish_map__deps: ['$teleportMkmapCall'], teleport_mkmap_test_finish_map__sig: 'viiiii',
  teleport_mkmap_test_finish_map: function(fg, bg, lit, walled, icedpools) { teleportMkmapCall('finish_map', fg, bg, lit, walled, icedpools); },
  teleport_mkmap_test_remove_room__deps: ['$teleportMkmapCall'], teleport_mkmap_test_remove_room__sig: 'vi',
  teleport_mkmap_test_remove_room: function(roomno) { teleportMkmapCall('remove_room', roomno); },
});
