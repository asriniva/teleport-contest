// utf8map ABI declarations only; byte/glyph/customization logic is JS.
addToLibrary({
  $teleportUtf8Services__deps: ['teleport_utf8_glyphmap', 'teleport_utf8_gbuf', 'teleport_utf8_showsyms', 'teleport_utf8_customizations', 'teleport_utf8_currentgraphics', 'teleport_utf8_hexdd', 'teleport_utf8_nul_glyphinfo', 'alloc', 'dupstr', 'free', 'strchr', 'strcpy', 'decode_glyph', 'map_glyphinfo', 'find_matching_customization', 'apply_customizations', '$stackAlloc', '$stringToUTF8OnStack'],
  $teleportUtf8Services: function() {
    var text = value => typeof value === 'string' ? BigInt(stringToUTF8OnStack(value)) : BigInt(value || 0);
    return {
      heap: () => HEAPU8,
      signedHeap: () => HEAP8,
      stackAlloc: size => stackAlloc(size),
      glyphmap: () => Number(_teleport_utf8_glyphmap()),
      gbuf: () => Number(_teleport_utf8_gbuf()),
      showsyms: () => Number(_teleport_utf8_showsyms()),
      customizations: () => Number(_teleport_utf8_customizations()),
      currentgraphics: () => _teleport_utf8_currentgraphics(),
      hexdd: () => Number(_teleport_utf8_hexdd()),
      nulGlyphInfo: () => Number(_teleport_utf8_nul_glyphinfo()),
      alloc: size => Number(_alloc(size >>> 0)),
      dupstr: pointer => Number(_dupstr(text(pointer))),
      free: pointer => _free(BigInt(pointer)),
      strchr: (pointer, value) => Number(_strchr(BigInt(pointer), value)),
      strcpy: (dest, source) => Number(_strcpy(BigInt(dest), text(source))),
      decode_glyph: (pointer, result) => _decode_glyph(BigInt(pointer), BigInt(result)),
      map_glyphinfo: (x, y, glyph, flags, dest) => _map_glyphinfo(x, y, glyph, flags, BigInt(dest)),
      find_matching_customization: (name, type, set) => Number(_find_matching_customization(text(name), type, set)),
      apply_customizations: (set, what) => _apply_customizations(set, what),
    };
  },
  $teleportUtf8Call__deps: ['$teleportUtf8Services', '$stackSave', '$stackRestore'],
  $teleportUtf8Call: function(name, ...args) {
    var stack = stackSave();
    try { return Module['nethackPorted'].utf8map(teleportUtf8Services(), name, ...args); }
    finally { stackRestore(stack); }
  },
  unicode_val__deps: ['$teleportUtf8Call'], unicode_val__sig: 'ip',
  unicode_val: function(cp) { return teleportUtf8Call('unicode_val', cp); },
  set_map_u__deps: ['$teleportUtf8Call'], set_map_u__sig: 'ipip',
  set_map_u: function(gmap, utf32ch, utf8str) { return teleportUtf8Call('set_map_u', gmap, utf32ch >>> 0, utf8str); },
  free_all_glyphmap_u__deps: ['$teleportUtf8Call'], free_all_glyphmap_u__sig: 'v',
  free_all_glyphmap_u: function() { teleportUtf8Call('free_all_glyphmap_u'); },
  mixed_to_utf8__deps: ['$teleportUtf8Call'], mixed_to_utf8__sig: 'ppppp',
  mixed_to_utf8: function(buf, bufsz, str, retflags) { return teleportUtf8Call('mixed_to_utf8', buf, bufsz, str, retflags); },
  add_custom_urep_entry__deps: ['$teleportUtf8Call'], add_custom_urep_entry__sig: 'ipiipi',
  add_custom_urep_entry: function(name, glyphidx, utf32ch, utf8str, set) { return teleportUtf8Call('add_custom_urep_entry', name, glyphidx, utf32ch >>> 0, utf8str, set); },
  reset_customsymbols__deps: ['$teleportUtf8Call'], reset_customsymbols__sig: 'v',
  reset_customsymbols: function() { teleportUtf8Call('reset_customsymbols'); },
});
