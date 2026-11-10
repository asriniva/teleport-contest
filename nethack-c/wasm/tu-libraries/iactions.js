// Native dependencies, shared fields, function identities and typed varargs.
addToLibrary({
  $teleportIactionsServices__deps: ['add_menu', 'select_menu', 'name_ok', 'call_ok', 'the_unique_obj', 'simpleonames', 'the', 'makeplural', 'strcpy', 'eos', 'is_edible', 'carrying', 'surface', 'check_invent_gold', 'in_rooms', 'shop_keeper', 'inhishop', 'body_part', 'armor_simple_name', 'an', 'armcat_to_wornmask', 'wearmask_to_obj', 'ia_checkfile', 'cxname', 'undiscovered_artifact', 'cmdq_add_key', 'teleport_iactions_global', 'teleport_iactions_equipment', 'teleport_iactions_object_bit', 'teleport_iactions_class_bit', 'teleport_iactions_hero_bit', 'teleport_iactions_nul_glyphinfo', 'teleport_iactions_command', 'teleport_iactions_cmdq_add_ec', 'teleport_iactions_free', 'teleport_iactions_create_window', 'teleport_iactions_start_menu', 'teleport_iactions_end_menu', 'teleport_iactions_destroy_window', 'teleport_iactions_format_strings', 'teleport_iactions_format_unwield', 'teleport_iactions_impossible', 'teleport_iactions_assert_fail', 'teleport_iactions_literal_storage', 'teleport_iactions_literal_capacity', '$lengthBytesUTF8', '$stringToUTF8', '$stackAlloc'],
  $teleportIactionsServices: function() {
    var state = Module['teleportIactionsLiterals'] ||= { next: 0, strings: new Map() };
    var literal = value => {
      if (state.strings.has(value)) return state.strings.get(value);
      var size = lengthBytesUTF8(value) + 1;
      if (state.next + size > Number(_teleport_iactions_literal_capacity())) throw new Error('Review changed iactions literal corpus');
      var at = Number(_teleport_iactions_literal_storage()) + state.next;
      stringToUTF8(value, at, size);
      state.next += size;
      state.strings.set(value, at);
      return at;
    };
    var pointer = value => BigInt(value ? value.address ?? value : 0);
    var text = value => typeof value === 'string' ? BigInt(literal(value)) : pointer(value);
    var byte = value => Number(value) << 24 >> 24;
    var coord = value => Number(value) << 16 >> 16;
    return {
      heap: () => HEAPU8,
      stackAlloc: size => stackAlloc(size),
      global: index => Number(_teleport_iactions_global(index)),
      equipment: index => Number(_teleport_iactions_equipment(index)),
      objectBit: (obj, index) => _teleport_iactions_object_bit(pointer(obj), index),
      objectClassBit: (obj, index) => _teleport_iactions_class_bit(pointer(obj), index),
      heroBit: index => _teleport_iactions_hero_bit(index),
      nulGlyphInfo: () => Number(_teleport_iactions_nul_glyphinfo()),
      command: index => _teleport_iactions_command(index),
      cmdq_add_ec: (queue, command) => _teleport_iactions_cmdq_add_ec(queue, pointer(command)),
      cmdq_add_key: (queue, key) => _cmdq_add_key(queue, byte(key)),
      free: ptr => _teleport_iactions_free(pointer(ptr)),
      create_nhwindow: type => _teleport_iactions_create_window(type),
      start_menu: (win, behavior) => _teleport_iactions_start_menu(win, BigInt(behavior)),
      end_menu: (win, prompt) => _teleport_iactions_end_menu(win, text(prompt)),
      destroy_nhwindow: win => _teleport_iactions_destroy_window(win),
      add_menu: (win, glyph, any, letter, group, attr, color, label, flags) => _add_menu(win, pointer(glyph), pointer(any), byte(letter), byte(group), attr, color, text(label), flags >>> 0),
      select_menu: (win, how, out) => _select_menu(win, how, pointer(out)),
      name_ok: obj => _name_ok(pointer(obj)),
      call_ok: obj => _call_ok(pointer(obj)),
      the_unique_obj: obj => _the_unique_obj(pointer(obj)),
      simpleonames: obj => Number(_simpleonames(pointer(obj))),
      the: value => Number(_the(text(value))),
      makeplural: value => Number(_makeplural(text(value))),
      Strcpy: (out, value) => Number(_strcpy(pointer(out), text(value))),
      eos: ptr => Number(_eos(pointer(ptr))),
      is_edible: obj => _is_edible(pointer(obj)),
      carrying: type => Number(_carrying(type)),
      surface: (x, y) => Number(_surface(coord(x), coord(y))),
      check_invent_gold: message => _check_invent_gold(text(message)),
      in_rooms: (x, y, type) => Number(_in_rooms(coord(x), coord(y), type)),
      shop_keeper: room => Number(_shop_keeper(byte(room))),
      inhishop: mon => _inhishop(pointer(mon)),
      body_part: part => Number(_body_part(part)),
      armor_simple_name: obj => Number(_armor_simple_name(pointer(obj))),
      an: value => Number(_an(text(value))),
      armcat_to_wornmask: category => _armcat_to_wornmask(category),
      wearmask_to_obj: mask => Number(_wearmask_to_obj(BigInt(mask))),
      ia_checkfile: obj => _ia_checkfile(pointer(obj)),
      cxname: obj => Number(_cxname(pointer(obj))),
      undiscovered_artifact: artifact => _undiscovered_artifact(artifact),
      Sprintf: (out, format, ...args) => {
        if (format === "%s '%c' to %s %s %s")
          _teleport_iactions_format_unwield(pointer(out), text(format), text(args[0]), args[1], text(args[2]), text(args[3]), text(args[4]));
        else {
          if (args.length > 3) throw new Error('Review changed iactions formatting ABI');
          _teleport_iactions_format_strings(pointer(out), text(format), text(args[0]), text(args[1]), text(args[2]));
        }
      },
      impossible: (format, act) => _teleport_iactions_impossible(text(format), act),
      assert: condition => { if (!condition) _teleport_iactions_assert_fail(); },
    };
  },
  $teleportIactionsCall__deps: ['$teleportIactionsServices', '$stackSave', '$stackRestore'],
  $teleportIactionsCall: function(name, ...args) {
    var stack = stackSave();
    try { return Module['nethackPorted'].iactions(teleportIactionsServices(), name, ...args); }
    finally { stackRestore(stack); }
  },
  itemactions__deps: ['$teleportIactionsCall'], itemactions__sig: 'ip',
  itemactions: function(obj) { return teleportIactionsCall('itemactions', obj); },
  teleport_iactions_test_naming__deps: ['$teleportIactionsCall'], teleport_iactions_test_naming__sig: 'ippp',
  teleport_iactions_test_naming: function(obj, onamebuf, ocallbuf) { return teleportIactionsCall('item_naming_classification', obj, onamebuf, ocallbuf); },
  teleport_iactions_test_reading__deps: ['$teleportIactionsCall'], teleport_iactions_test_reading__sig: 'ipp',
  teleport_iactions_test_reading: function(obj, outbuf) { return teleportIactionsCall('item_reading_classification', obj, outbuf); },
  teleport_iactions_test_addmenu__deps: ['$teleportIactionsCall'], teleport_iactions_test_addmenu__sig: 'viiip',
  teleport_iactions_test_addmenu: function(win, act, letter, txt) { teleportIactionsCall('ia_addmenu', win, act, letter, txt); },
  teleport_iactions_test_pushkeys__deps: ['$teleportIactionsCall'], teleport_iactions_test_pushkeys__sig: 'vpi',
  teleport_iactions_test_pushkeys: function(obj, act) { teleportIactionsCall('itemactions_pushkeys', obj, act); },
});
