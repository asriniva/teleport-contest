// Native dependencies, opaque callbacks and typed formatting ABI only.
addToLibrary({
  $teleportSelvarServices__deps: ['alloc', 'dupstr', 'memset', 'memcpy', 'isok', 'match_maptyps', 'random_wdir', 'newsym_force', 'dist2', 'teleport_selvar_global', 'teleport_selvar_terrain_bit', 'teleport_selvar_flood_check', 'teleport_selvar_iterate', 'teleport_selvar_free', 'teleport_selvar_rn2', 'teleport_selvar_panic', 'teleport_selvar_impossible', 'teleport_selvar_format', 'teleport_selvar_literal_storage', 'teleport_selvar_literal_capacity', '$lengthBytesUTF8', '$stringToUTF8', '$stackAlloc'],
  $teleportSelvarServices: function() {
    if(Module["teleportSelvarServicesObject"])return Module["teleportSelvarServicesObject"];
    var state = Module['teleportSelvarLiterals'] ||= { next: 0, strings: new Map() };
    var literal = value => {
      if (state.strings.has(value)) return state.strings.get(value);
      var size = lengthBytesUTF8(value) + 1;
      if (state.next + size > Number(_teleport_selvar_literal_capacity())) throw new Error('Review changed selvar literal corpus');
      var at = Number(_teleport_selvar_literal_storage()) + state.next;
      stringToUTF8(value, at, size);
      state.next += size;
      state.strings.set(value, at);
      return at;
    };
    var pointer = value => BigInt(value ? value.address ?? value : 0);
    var text = value => typeof value === 'string' ? BigInt(literal(value)) : pointer(value);
    var int = value => typeof value === 'bigint' ? Number(BigInt.asIntN(32, value)) : Number(value) | 0;
    var coord = value => typeof value === 'bigint' ? Number(BigInt.asIntN(16, value)) : Number(value) << 16 >> 16;
    return Module["teleportSelvarServicesObject"]={
      moduleKey: Module,
      heap: () => HEAPU8,
      stackAlloc: size => stackAlloc(size),
      global: index => Number(_teleport_selvar_global(index)),
      terrainBit: (x, y, index) => _teleport_selvar_terrain_bit(coord(x), coord(y), index),
      floodCheck: (callback, x, y) => _teleport_selvar_flood_check(pointer(callback), coord(x), coord(y)),
      iterate: (callback, x, y, arg) => _teleport_selvar_iterate(pointer(callback), coord(x), coord(y), pointer(arg)),
      alloc: size => Number(_alloc(int(size) >>> 0)),
      free: value => _teleport_selvar_free(pointer(value)),
      dupstr: value => Number(_dupstr(text(value))),
      memset: (out, value, size) => Number(_memset(pointer(out), int(value), BigInt.asUintN(64, BigInt(size)))),
      memcpy: (out, source, size) => Number(_memcpy(pointer(out), pointer(source), BigInt.asUintN(64, BigInt(size)))),
      isok: (x, y) => _isok(coord(x), coord(y)),
      match_maptyps: (wanted, actual) => _match_maptyps(coord(wanted), coord(actual)),
      random_wdir: () => _random_wdir(),
      newsym_force: (x, y) => _newsym_force(coord(x), coord(y)),
      dist2: (x1, y1, x2, y2) => _dist2(coord(x1), coord(y1), coord(x2), coord(y2)),
      rn2: (bound, line, caller) => _teleport_selvar_rn2(int(bound), line, caller),
      panic: message => _teleport_selvar_panic(text(message)),
      impossible: message => _teleport_selvar_impossible(text(message)),
      Sprintf: (out, format, shape, dx, dy) => _teleport_selvar_format(pointer(out), text(format), text(shape), int(dx), int(dy)),
    };
  },
  $teleportSelvarCall__deps: ['$teleportSelvarServices', '$stackSave', '$stackRestore'],
  $teleportSelvarCall: function(name, ...args) {
    var stack = stackSave();
    try { return Module['nethackPorted'].selvar(teleportSelvarServices(), name, ...args); }
    finally { stackRestore(stack); }
  },
  selection_new__deps: ['$teleportSelvarCall'], selection_new__sig: 'p',
  selection_new: function() { return teleportSelvarCall('selection_new'); },
  selection_free__deps: ['$teleportSelvarCall'], selection_free__sig: 'vpi',
  selection_free: function(sel, freesel) { teleportSelvarCall('selection_free', sel, freesel); },
  selection_clear__deps: ['$teleportSelvarCall'], selection_clear__sig: 'vpi',
  selection_clear: function(sel, val) { teleportSelvarCall('selection_clear', sel, val); },
  selection_clone__deps: ['$teleportSelvarCall'], selection_clone__sig: 'pp',
  selection_clone: function(sel) { return teleportSelvarCall('selection_clone', sel); },
  selection_getbounds__deps: ['$teleportSelvarCall'], selection_getbounds__sig: 'vpp',
  selection_getbounds: function(sel, bounds) { teleportSelvarCall('selection_getbounds', sel, bounds); },
  selection_recalc_bounds__deps: ['$teleportSelvarCall'], selection_recalc_bounds__sig: 'vp',
  selection_recalc_bounds: function(sel) { teleportSelvarCall('selection_recalc_bounds', sel); },
  selection_getpoint__deps: ['$teleportSelvarCall'], selection_getpoint__sig: 'iiip',
  selection_getpoint: function(x, y, sel) { return teleportSelvarCall('selection_getpoint', x, y, sel); },
  selection_setpoint__deps: ['$teleportSelvarCall'], selection_setpoint__sig: 'viipi',
  selection_setpoint: function(x, y, sel, value) { teleportSelvarCall('selection_setpoint', x, y, sel, value); },
  selection_not__deps: ['$teleportSelvarCall'], selection_not__sig: 'pp',
  selection_not: function(sel) { return teleportSelvarCall('selection_not', sel); },
  selection_filter_percent__deps: ['$teleportSelvarCall'], selection_filter_percent__sig: 'ppi',
  selection_filter_percent: function(sel, percent) { return teleportSelvarCall('selection_filter_percent', sel, percent); },
  selection_filter_mapchar__deps: ['$teleportSelvarCall'], selection_filter_mapchar__sig: 'ppii',
  selection_filter_mapchar: function(sel, typ, lit) { return teleportSelvarCall('selection_filter_mapchar', sel, typ, lit); },
  selection_rndcoord__deps: ['$teleportSelvarCall'], selection_rndcoord__sig: 'ipppi',
  selection_rndcoord: function(sel, x, y, removeit) { return teleportSelvarCall('selection_rndcoord', sel, x, y, removeit); },
  selection_do_grow__deps: ['$teleportSelvarCall'], selection_do_grow__sig: 'vpi',
  selection_do_grow: function(sel, dir) { teleportSelvarCall('selection_do_grow', sel, dir); },
  // Function-pointer and callback payload bits remain opaque memory64 values.
  set_selection_floodfillchk__deps: ['$teleportSelvarCall'], set_selection_floodfillchk__sig: 'vj',
  set_selection_floodfillchk: function(callback) { teleportSelvarCall('set_selection_floodfillchk', callback); },
  selection_floodfill__deps: ['$teleportSelvarCall'], selection_floodfill__sig: 'vpiii',
  selection_floodfill: function(sel, x, y, diagonals) { teleportSelvarCall('selection_floodfill', sel, x, y, diagonals); },
  selection_do_ellipse__deps: ['$teleportSelvarCall'], selection_do_ellipse__sig: 'vpiiiii',
  selection_do_ellipse: function(sel, xc, yc, a, b, filled) { teleportSelvarCall('selection_do_ellipse', sel, xc, yc, a, b, filled); },
  selection_do_gradient__deps: ['$teleportSelvarCall'], selection_do_gradient__sig: 'vpjjjjjjj',
  selection_do_gradient: function(sel, x, y, x2, y2, typ, mind, maxd) { teleportSelvarCall('selection_do_gradient', sel, x, y, x2, y2, typ, mind, maxd); },
  selection_do_line__deps: ['$teleportSelvarCall'], selection_do_line__sig: 'viiiip',
  selection_do_line: function(x1, y1, x2, y2, sel) { teleportSelvarCall('selection_do_line', x1, y1, x2, y2, sel); },
  selection_do_randline__deps: ['$teleportSelvarCall'], selection_do_randline__sig: 'viiiiiip',
  selection_do_randline: function(x1, y1, x2, y2, rough, rec, sel) { teleportSelvarCall('selection_do_randline', x1, y1, x2, y2, rough, rec, sel); },
  selection_iterate__deps: ['$teleportSelvarCall'], selection_iterate__sig: 'vpjj',
  selection_iterate: function(sel, callback, arg) { teleportSelvarCall('selection_iterate', sel, callback, arg); },
  selection_is_irregular__deps: ['$teleportSelvarCall'], selection_is_irregular__sig: 'ip',
  selection_is_irregular: function(sel) { return teleportSelvarCall('selection_is_irregular', sel); },
  selection_size_description__deps: ['$teleportSelvarCall'], selection_size_description__sig: 'ppp',
  selection_size_description: function(sel, out) { return teleportSelvarCall('selection_size_description', sel, out); },
  selection_from_mkroom__deps: ['$teleportSelvarCall'], selection_from_mkroom__sig: 'pp',
  selection_from_mkroom: function(room) { return teleportSelvarCall('selection_from_mkroom', room); },
  selection_force_newsyms__deps: ['$teleportSelvarCall'], selection_force_newsyms__sig: 'vp',
  selection_force_newsyms: function(sel) { teleportSelvarCall('selection_force_newsyms', sel); },
  teleport_selvar_test_havepoint__deps: ['$teleportSelvarCall'], teleport_selvar_test_havepoint__sig: 'iiippi',
  teleport_selvar_test_havepoint: function(x, y, xs, ys, n) { return teleportSelvarCall('sel_flood_havepoint', x, y, xs, ys, n); },
  teleport_selvar_test_line_dist__deps: ['$teleportSelvarCall'], teleport_selvar_test_line_dist__sig: 'jjjjjjj',
  teleport_selvar_test_line_dist: function(x1, y1, x2, y2, x3, y3) { return teleportSelvarCall('line_dist_coord', x1, y1, x2, y2, x3, y3); },
});
