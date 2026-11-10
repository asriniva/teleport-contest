// Zero native storage, typed bitfield access and copies; catalogue rows are JS.
addToLibrary({
  $teleportObjectsServices__deps: ['memcpy', 'teleport_objects_storage', 'teleport_objects_set_bit', 'teleport_objects_literal_storage', 'teleport_objects_literal_capacity', '$lengthBytesUTF8', '$stringToUTF8'],
  $teleportObjectsServices: function() {
    // A shared JS runtime may serve several Wasm modules. Each module owns
    // its literal addresses and provides a stable identity for its TU state.
    var state = Module['teleportObjectsCache'] ||= { next: 0, strings: new Map() };
    var pointer = value => BigInt(value ? value.address ?? value : 0);
    return {
      moduleKey: state,
      heap: () => HEAPU8,
      storage: index => Number(_teleport_objects_storage(index)),
      setBit: (row, index, value) => _teleport_objects_set_bit(pointer(row), index, Number(value) >>> 0),
      memcpy: (out, source, size) => Number(_memcpy(pointer(out), pointer(source), BigInt.asUintN(64, BigInt(size)))),
      literal: value => {
        if (state.strings.has(value)) return state.strings.get(value);
        var size = lengthBytesUTF8(value) + 1;
        if (state.next + size > Number(_teleport_objects_literal_capacity())) throw new Error('Review changed object catalogue literal corpus');
        var at = Number(_teleport_objects_literal_storage()) + state.next;
        stringToUTF8(value, at, size);
        state.next += size;
        state.strings.set(value, at);
        return at;
      },
    };
  },
  objects_globals_init__deps: ['$teleportObjectsServices'], objects_globals_init__sig: 'v',
  objects_globals_init: function() {
    Module['nethackPorted'].objects(teleportObjectsServices(), 'objects_globals_init');
  },
});
