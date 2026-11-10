// drawing ABI storage/startup only; tables and lookup functions are JS.
addToLibrary({
  $teleportDrawingServices__deps: ['teleport_drawing_objects', 'teleport_drawing_monsters', 'teleport_drawing_warnings', 'teleport_drawing_symbols', 'teleport_drawing_rogue', 'malloc'],
  $teleportDrawingServices: function() {
    return {
      heap: () => HEAPU8,
      malloc: size => Number(_malloc(BigInt(size))),
      objectSymbols: () => Number(_teleport_drawing_objects()),
      monsterSymbols: () => Number(_teleport_drawing_monsters()),
      warningSymbols: () => Number(_teleport_drawing_warnings()),
      symbols: () => Number(_teleport_drawing_symbols()),
      rogueSymbols: () => Number(_teleport_drawing_rogue()),
    };
  },
  $teleportDrawingInit__deps: ['$teleportDrawingServices', '$addOnInit'],
  $teleportDrawingInit__postset: "addOnInit(() => Module['nethackPorted'].initializeDrawing(teleportDrawingServices()));",
  $teleportDrawingInit: 0,
  def_char_to_objclass__deps: ['$teleportDrawingInit'], def_char_to_objclass__sig: 'ii',
  def_char_to_objclass: function(ch) { return Module['nethackPorted'].drawing('def_char_to_objclass', ch << 24 >> 24); },
  def_char_to_monclass__deps: ['$teleportDrawingInit'], def_char_to_monclass__sig: 'ii',
  def_char_to_monclass: function(ch) { return Module['nethackPorted'].drawing('def_char_to_monclass', ch << 24 >> 24); },
  def_char_is_furniture__deps: ['$teleportDrawingInit'], def_char_is_furniture__sig: 'ii',
  def_char_is_furniture: function(ch) { return Module['nethackPorted'].drawing('def_char_is_furniture', ch << 24 >> 24); },
});
