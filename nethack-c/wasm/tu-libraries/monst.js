// Native storage and copies only; the monster and attack catalogues are JS.
addToLibrary({
  $teleportMonstServices__deps: ['memcpy', 'teleport_monst_storage', 'teleport_monst_literal_storage', 'teleport_monst_literal_capacity', '$lengthBytesUTF8', '$stringToUTF8'],
  $teleportMonstServices: function() {
    // The shared JS runtime keys its serialized source tables by this module
    // identity, including when startup precedes monst_globals_init.
    var state = Module['teleportMonstCache'] ||= { next: 0, strings: new Map() };
    var pointer = value => BigInt(value ? value.address ?? value : 0);
    return {
      moduleKey: state,
      heap: () => HEAPU8,
      storage: index => Number(_teleport_monst_storage(index)),
      memcpy: (out, source, size) => Number(_memcpy(pointer(out), pointer(source), BigInt.asUintN(64, BigInt(size)))),
      literal: value => {
        if (state.strings.has(value)) return state.strings.get(value);
        var size = lengthBytesUTF8(value) + 1;
        if (state.next + size > Number(_teleport_monst_literal_capacity())) throw new Error('Review changed monster catalogue literal corpus');
        var at = Number(_teleport_monst_literal_storage()) + state.next;
        stringToUTF8(value, at, size);
        state.next += size;
        state.strings.set(value, at);
        return at;
      },
    };
  },
  $teleportMonstInit__deps: ['$teleportMonstServices', '$addOnInit'],
  $teleportMonstInit__postset: "addOnInit(() => Module['nethackPorted'].initializeMonst(teleportMonstServices()));",
  $teleportMonstInit: 0,
  monst_globals_init__deps: ['$teleportMonstInit'], monst_globals_init__sig: 'v',
  monst_globals_init: function() {
    Module['nethackPorted'].monst(teleportMonstServices(), 'monst_globals_init');
  },
});
