// Native ABI only; all light-source algorithms are in light.js.
addToLibrary({
  $teleportLightServices__deps: ['teleport_light_global', 'teleport_light_uskin', 'teleport_light_object_bit', 'teleport_light_set_object_bit', 'teleport_light_monster_bit', 'teleport_light_set_monster_bit', 'teleport_light_terrain_bit', 'teleport_light_free', 'teleport_light_delay', 'teleport_light_create_window', 'teleport_light_putstr', 'teleport_light_display_window', 'teleport_light_destroy_window', 'teleport_light_sfo_int', 'teleport_light_sfi_int', 'teleport_light_sfo_ls', 'teleport_light_sfi_ls', 'teleport_light_assert', 'teleport_light_panic_ints', 'teleport_light_panic_uint', 'teleport_light_panic_char_uint', 'teleport_light_impossible_ints', 'teleport_light_impossible_int_string', 'teleport_light_impossible_strings', 'teleport_light_impossible_uint', 'teleport_light_impossible_string_uint', 'teleport_light_format_long', 'teleport_light_format_xy', 'teleport_light_format_source', 'teleport_light_literal_storage', 'teleport_light_literal_capacity', 'alloc', 'memset', 'get_obj_location', 'get_mon_location', 'clear_path', 'simpleonames', 'otense', 'place_object', 'vision_recalc', 'flush_screen', 'dist2', 'canseemon', 'sensemon', 'remove_object', 'map_invisible', 'obj_is_local', 'find_oid', 'lookup_id_mapping', 'fmt_ptr', 'artifact_light', 'end_burn', 'xname', '$lengthBytesUTF8', '$stringToUTF8', '$stackAlloc', '$stackSave', '$stackRestore'],
  $teleportLightServices: function() {
    var state = Module['teleportLightCache'] ||= { next: 0, strings: new Map() };
    var pointer = value => BigInt(value ? value.address ?? value : 0);
    var byte = value => Number(BigInt.asIntN(8, BigInt(value)));
    var coord = value => Number(BigInt.asIntN(16, BigInt(value)));
    var literal = value => {
      if (state.strings.has(value)) return state.strings.get(value);
      var size = lengthBytesUTF8(value) + 1;
      if (state.next + size > Number(_teleport_light_literal_capacity())) throw new Error('Review changed light-source literal corpus');
      var at = Number(_teleport_light_literal_storage()) + state.next;
      stringToUTF8(value, at, size); state.next += size; state.strings.set(value, at); return at;
    };
    var text = value => typeof value === 'string' ? BigInt(literal(value)) : pointer(value);
    return {
      moduleKey: Module,
      heap: () => HEAPU8, literal,
      stackAlloc: size => Number(stackAlloc(size)), stackSave: () => stackSave(), stackRestore: saved => stackRestore(saved),
      global: index => Number(_teleport_light_global(index)), uskin: () => Number(_teleport_light_uskin()),
      objectBit: (obj, index) => _teleport_light_object_bit(pointer(obj), index),
      setObjectBit: (obj, index, value) => _teleport_light_set_object_bit(pointer(obj), index, Number(value) >>> 0),
      monsterBit: (mon, index) => _teleport_light_monster_bit(pointer(mon), index),
      setMonsterBit: (mon, index, value) => _teleport_light_set_monster_bit(pointer(mon), index, Number(value) >>> 0),
      terrainBit: (x, y, index) => _teleport_light_terrain_bit(coord(x), coord(y), index),
      free: value => _teleport_light_free(pointer(value)), nh_delay_output: () => _teleport_light_delay(),
      create_nhwindow: type => _teleport_light_create_window(type),
      putstr: (win, attr, value) => _teleport_light_putstr(win, attr, text(value)),
      display_nhwindow: (win, blocking) => _teleport_light_display_window(win, byte(blocking)),
      destroy_nhwindow: win => _teleport_light_destroy_window(win),
      Sfo_int: (fp, value, tag) => _teleport_light_sfo_int(pointer(fp), pointer(value), text(tag)),
      Sfi_int: (fp, value, tag) => _teleport_light_sfi_int(pointer(fp), pointer(value), text(tag)),
      Sfo_ls_t: (fp, value, tag) => _teleport_light_sfo_ls(pointer(fp), pointer(value), text(tag)),
      Sfi_ls_t: (fp, value, tag) => _teleport_light_sfi_ls(pointer(fp), pointer(value), text(tag)),
      assert: (condition, index) => { if (!condition) _teleport_light_assert(index); },
      panic: (format, ...args) => {
        if (format.includes('%u')) return args.length === 2
          ? _teleport_light_panic_char_uint(text(format), args[0], args[1] >>> 0)
          : _teleport_light_panic_uint(text(format), args[0] >>> 0);
        return _teleport_light_panic_ints(text(format), args[0] ?? 0, args[1] ?? 0, args[2] ?? 0);
      },
      impossible: (format, ...args) => {
        if (format.includes('%u')) return args.length === 2
          ? _teleport_light_impossible_string_uint(text(format), text(args[0]), args[1] >>> 0)
          : _teleport_light_impossible_uint(text(format), args[0] >>> 0);
        if (format.includes('%d')) return format.includes('%s')
          ? _teleport_light_impossible_int_string(text(format), args[0], text(args[1]))
          : _teleport_light_impossible_ints(text(format), args[0], args[1] ?? 0);
        return _teleport_light_impossible_strings(text(format), text(args[0]), text(args[1]), text(args[2]), text(args[3]));
      },
      Sprintf: (out, format, ...args) => {
        if (args.length === 1) return _teleport_light_format_long(pointer(out), text(format), BigInt.asIntN(64, BigInt(args[0])));
        if (args.length === 2) return _teleport_light_format_xy(pointer(out), text(format), args[0], args[1]);
        return _teleport_light_format_source(pointer(out), text(format), args[0], args[1], args[2], args[3], text(args[4]), text(args[5]));
      },
      alloc: size => Number(_alloc(Number(size) >>> 0)),
      memset: (out, value, size) => Number(_memset(pointer(out), value, BigInt(size))),
      get_obj_location: (obj, x, y, flags) => _get_obj_location(pointer(obj), pointer(x), pointer(y), flags),
      get_mon_location: (mon, x, y, flags) => _get_mon_location(pointer(mon), pointer(x), pointer(y), flags),
      clear_path: (x, y, xx, yy) => _clear_path(x, y, xx, yy),
      simpleonames: obj => Number(_simpleonames(pointer(obj))),
      otense: (obj, verb) => Number(_otense(pointer(obj), text(verb))),
      place_object: (obj, x, y) => _place_object(pointer(obj), coord(x), coord(y)),
      vision_recalc: mode => _vision_recalc(mode),
      flush_screen: mode => _flush_screen(mode),
      dist2: (x, y, xx, yy) => _dist2(coord(x), coord(y), coord(xx), coord(yy)),
      canseemon: mon => _canseemon(pointer(mon)),
      sensemon: mon => _sensemon(pointer(mon)),
      remove_object: obj => _remove_object(pointer(obj)),
      map_invisible: (x, y) => _map_invisible(coord(x), coord(y)),
      obj_is_local: obj => _obj_is_local(pointer(obj)),
      find_oid: id => Number(_find_oid(id >>> 0)),
      lookup_id_mapping: (id, out) => _lookup_id_mapping(id >>> 0, pointer(out)),
      fmt_ptr: value => Number(_fmt_ptr(pointer(value))),
      artifact_light: obj => _artifact_light(pointer(obj)),
      end_burn: (obj, flag) => _end_burn(pointer(obj), byte(flag)),
      xname: obj => Number(_xname(pointer(obj))),
    };
  },
  $teleportLightCall__deps: ['$teleportLightServices', '$stackSave', '$stackRestore'],
  $teleportLightCall: function(name, ...args) {
    var saved = stackSave();
    try { return Module['nethackPorted'].light(teleportLightServices(), name, ...args); }
    finally { stackRestore(saved); }
  },
  new_light_source__deps: ['$teleportLightCall'], new_light_source__sig: 'viiiip',
  new_light_source: function(x, y, range, type, id) { teleportLightCall('new_light_source', x << 16 >> 16, y << 16 >> 16, range, type, id); },
  del_light_source__deps: ['$teleportLightCall'], del_light_source__sig: 'vip',
  del_light_source: function(type, id) { teleportLightCall('del_light_source', type, id); },
  do_light_sources__deps: ['$teleportLightCall'], do_light_sources__sig: 'vp',
  do_light_sources: function(rows) { teleportLightCall('do_light_sources', rows); },
  show_transient_light__deps: ['$teleportLightCall'], show_transient_light__sig: 'vpii',
  show_transient_light: function(obj, x, y) { teleportLightCall('show_transient_light', obj, x << 16 >> 16, y << 16 >> 16); },
  transient_light_cleanup__deps: ['$teleportLightCall'], transient_light_cleanup__sig: 'v',
  transient_light_cleanup: function() { teleportLightCall('transient_light_cleanup'); },
  find_mid__deps: ['$teleportLightCall'], find_mid__sig: 'pii',
  find_mid: function(id, flags) { return teleportLightCall('find_mid', id >>> 0, flags >>> 0); },
  save_light_sources__deps: ['$teleportLightCall'], save_light_sources__sig: 'vpi',
  save_light_sources: function(fp, range) { teleportLightCall('save_light_sources', fp, range); },
  restore_light_sources__deps: ['$teleportLightCall'], restore_light_sources__sig: 'vp',
  restore_light_sources: function(fp) { teleportLightCall('restore_light_sources', fp); },
  light_stats__deps: ['$teleportLightCall'], light_stats__sig: 'vpppp',
  light_stats: function(format, buf, count, size) { teleportLightCall('light_stats', format, buf, count, size); },
  relink_light_sources__deps: ['$teleportLightCall'], relink_light_sources__sig: 'vi',
  relink_light_sources: function(ghostly) { teleportLightCall('relink_light_sources', ghostly << 24 >> 24); },
  light_sources_sanity_check__deps: ['$teleportLightCall'], light_sources_sanity_check__sig: 'v',
  light_sources_sanity_check: function() { teleportLightCall('light_sources_sanity_check'); },
  obj_move_light_source__deps: ['$teleportLightCall'], obj_move_light_source__sig: 'vpp',
  obj_move_light_source: function(src, dest) { teleportLightCall('obj_move_light_source', src, dest); },
  any_light_source__deps: ['$teleportLightCall'], any_light_source__sig: 'i',
  any_light_source: function() { return teleportLightCall('any_light_source'); },
  snuff_light_source__deps: ['$teleportLightCall'], snuff_light_source__sig: 'vii',
  snuff_light_source: function(x, y) { teleportLightCall('snuff_light_source', x << 16 >> 16, y << 16 >> 16); },
  obj_sheds_light__deps: ['$teleportLightCall'], obj_sheds_light__sig: 'ip',
  obj_sheds_light: function(obj) { return teleportLightCall('obj_sheds_light', obj); },
  obj_is_burning__deps: ['$teleportLightCall'], obj_is_burning__sig: 'ip',
  obj_is_burning: function(obj) { return teleportLightCall('obj_is_burning', obj); },
  obj_split_light_source__deps: ['$teleportLightCall'], obj_split_light_source__sig: 'vpp',
  obj_split_light_source: function(src, dest) { teleportLightCall('obj_split_light_source', src, dest); },
  obj_merge_light_sources__deps: ['$teleportLightCall'], obj_merge_light_sources__sig: 'vpp',
  obj_merge_light_sources: function(src, dest) { teleportLightCall('obj_merge_light_sources', src, dest); },
  obj_adjust_light_radius__deps: ['$teleportLightCall'], obj_adjust_light_radius__sig: 'vpi',
  obj_adjust_light_radius: function(obj, radius) { teleportLightCall('obj_adjust_light_radius', obj, radius); },
  candle_light_range__deps: ['$teleportLightCall'], candle_light_range__sig: 'ip',
  candle_light_range: function(obj) { return teleportLightCall('candle_light_range', obj); },
  arti_light_radius__deps: ['$teleportLightCall'], arti_light_radius__sig: 'ip',
  arti_light_radius: function(obj) { return teleportLightCall('arti_light_radius', obj); },
  arti_light_description__deps: ['$teleportLightCall'], arti_light_description__sig: 'pp',
  arti_light_description: function(obj) { return teleportLightCall('arti_light_description', obj); },
  wiz_light_sources__deps: ['$teleportLightCall'], wiz_light_sources__sig: 'i',
  wiz_light_sources: function() { return teleportLightCall('wiz_light_sources'); },
  teleport_light_test_new__deps: ['$teleportLightCall'], teleport_light_test_new__sig: 'piiiip',
  teleport_light_test_new: function(x, y, range, type, id) { return teleportLightCall('new_light_core', x << 16 >> 16, y << 16 >> 16, range, type, id); },
  teleport_light_test_delete__deps: ['$teleportLightCall'], teleport_light_test_delete__sig: 'vp',
  teleport_light_test_delete: function(ls) { teleportLightCall('delete_ls', ls); },
  teleport_light_test_discard__deps: ['$teleportLightCall'], teleport_light_test_discard__sig: 'v',
  teleport_light_test_discard: function() { teleportLightCall('discard_flashes'); },
  teleport_light_test_write__deps: ['$teleportLightCall'], teleport_light_test_write__sig: 'vpp',
  teleport_light_test_write: function(fp, ls) { teleportLightCall('write_ls', fp, ls); },
  teleport_light_test_maybe__deps: ['$teleportLightCall'], teleport_light_test_maybe__sig: 'ipii',
  teleport_light_test_maybe: function(fp, range, write) { return teleportLightCall('maybe_write_ls', fp, range, write << 24 >> 24); },
  teleport_light_test_where__deps: ['$teleportLightCall'], teleport_light_test_where__sig: 'ipi',
  teleport_light_test_where: function(mon, flags) { return teleportLightCall('whereis_mon', mon, flags >>> 0); },
});
