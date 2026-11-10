// Native dependencies, stable strings and fixed callback/formatting ABI only.
addToLibrary({
  $teleportWriteServices__deps: ['Tobjnam', 'The', 'an', 'aobjnam', 'bcsign', 'check_unpaid', 'discover_object', 'dropx', 'exercise', 'fingers_or_gloves', 'hold_another_object', 'known_spell', 'memcpy', 'mksobj', 'mungspaces', 'obfree', 'observe_object', 'strcpy', 'strncmpi', 'strstri', 'update_inventory', 'upstart', 'useup', 'wipeout_text', 'ysimple_name', 'teleport_write_global', 'teleport_write_object_bit', 'teleport_write_set_object_bit', 'teleport_write_class_bit', 'teleport_write_getobj', 'teleport_write_getlin', 'teleport_write_message', 'teleport_write_sprintf', 'teleport_write_livelog', 'teleport_write_rn2', 'teleport_write_rnl', 'teleport_write_literal_storage', 'teleport_write_literal_capacity', '$lengthBytesUTF8', '$stringToUTF8', '$stackAlloc'],
  $teleportWriteServices: function() {
    var state = Module['teleportWriteLiterals'] ||= { next: 0, strings: new Map() };
    var literal = value => {
      if (state.strings.has(value)) return state.strings.get(value);
      var size = lengthBytesUTF8(value) + 1;
      if (state.next + size > Number(_teleport_write_literal_capacity())) throw new Error('Review changed write literal corpus');
      var at = Number(_teleport_write_literal_storage()) + state.next;
      stringToUTF8(value, at, size);
      state.next += size;
      state.strings.set(value, at);
      return at;
    };
    var pointer = value => BigInt(value ? value.address ?? value : 0);
    var text = value => typeof value === 'string' ? BigInt(literal(value)) : pointer(value);
    var message = (kind, format, a = 0, b = 0) => _teleport_write_message(kind, text(format), text(a), text(b));
    return {
      heap: () => HEAPU8,
      stackAlloc: size => stackAlloc(size),
      literal: value => literal(value),
      global: index => Number(_teleport_write_global(index)),
      objectBit: (obj, index) => _teleport_write_object_bit(pointer(obj), index),
      setObjectBit: (obj, index, value) => _teleport_write_set_object_bit(pointer(obj), index, Number(value)),
      objectClassBit: (obj, index) => _teleport_write_class_bit(pointer(obj), index),
      getobj: (verb, callback, flags) => Number(_teleport_write_getobj(text(verb), flags >>> 0)),
      getlin: (query, out) => _teleport_write_getlin(text(query), pointer(out)),
      Tobjnam: (obj, verb) => Number(_Tobjnam(pointer(obj), text(verb))),
      fingers_or_gloves: value => Number(_fingers_or_gloves(Number(value))),
      ysimple_name: obj => Number(_ysimple_name(pointer(obj))),
      upstart: value => Number(_upstart(text(value))),
      dropx: obj => _dropx(pointer(obj)),
      observe_object: obj => _observe_object(pointer(obj)),
      exercise: (attribute, positive) => _exercise(attribute, Number(positive)),
      makeknown: type => _discover_object(type, 1, 1, 1),
      Sprintf: (out, format, a = 0, b = 0) => _teleport_write_sprintf(pointer(out), text(format), text(a), text(b)),
      Strcpy: (out, value) => Number(_strcpy(pointer(out), text(value))),
      mungspaces: value => Number(_mungspaces(pointer(value))),
      strncmpi: (a, b, length) => _strncmpi(text(a), text(b), length),
      strcmpi: (a, b) => _strncmpi(text(a), text(b), -1),
      strstri: (a, b) => Number(_strstri(text(a), text(b))),
      memcpy: (out, source, size) => Number(_memcpy(pointer(out), text(source), BigInt(size))),
      rn2: (bound, line) => _teleport_write_rn2(bound, line),
      rn1: (bound, offset, line) => _teleport_write_rn2(bound, line) + offset,
      rnl: (bound, line) => _teleport_write_rnl(bound, line),
      livelog_printf: (category, format, value) => _teleport_write_livelog(BigInt(category), text(format), text(value)),
      an: value => Number(_an(text(value))),
      mksobj: (type, init, artif) => Number(_mksobj(type, Number(init), Number(artif))),
      check_unpaid: obj => _check_unpaid(pointer(obj)),
      obfree: (obj, merge) => _obfree(pointer(obj), pointer(merge)),
      bcsign: obj => _bcsign(pointer(obj)),
      update_inventory: () => _update_inventory(),
      useup: obj => _useup(pointer(obj)),
      known_spell: type => _known_spell(type << 16 >> 16),
      wipeout_text: (out, count, seed) => _wipeout_text(pointer(out), count, seed >>> 0),
      aobjnam: (obj, verb) => Number(_aobjnam(pointer(obj), text(verb))),
      The: value => Number(_The(text(value))),
      hold_another_object: (obj, format, name, other) => Number(_hold_another_object(pointer(obj), text(format), text(name), text(other))),
      pline: (format, a, b) => message(0, format, a, b),
      You: (format, a, b) => message(1, format, a, b),
      Your: (format, a, b) => message(2, format, a, b),
      You_cant: (format, a, b) => message(3, format, a, b),
      There: (format, a, b) => message(4, format, a, b),
      pline_The: (format, a, b) => message(5, format, a, b),
      impossible: (format, a, b) => message(6, format, a, b),
    };
  },
  $teleportWriteCall__deps: ['$teleportWriteServices', '$stackSave', '$stackRestore'],
  $teleportWriteCall: function(name, ...args) {
    var stack = stackSave();
    try { return Module['nethackPorted'].write(teleportWriteServices(), name, ...args); }
    finally { stackRestore(stack); }
  },
  dowrite__deps: ['$teleportWriteCall'], dowrite__sig: 'ip',
  dowrite: function(pen) { return teleportWriteCall('dowrite', pen); },
  teleport_write_callback__deps: ['$teleportWriteCall'], teleport_write_callback__sig: 'ip',
  teleport_write_callback: function(obj) { return teleportWriteCall('write_ok', obj); },
  teleport_write_test_cost__deps: ['$teleportWriteCall'], teleport_write_test_cost__sig: 'ip',
  teleport_write_test_cost: function(otmp) { return teleportWriteCall('cost', otmp); },
  teleport_write_test_write_ok__deps: ['$teleportWriteCall'], teleport_write_test_write_ok__sig: 'ip',
  teleport_write_test_write_ok: function(obj) { return teleportWriteCall('write_ok', obj); },
  teleport_write_test_new_book_description__deps: ['$teleportWriteCall'], teleport_write_test_new_book_description__sig: 'pip',
  teleport_write_test_new_book_description: function(booktype, outbuf) { return teleportWriteCall('new_book_description', booktype, outbuf); },
});
