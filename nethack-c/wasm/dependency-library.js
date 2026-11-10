// ABI imports only. Dependency algorithms live in js/services/*.js.
addToLibrary({
  $teleportDependencyServices__deps: ['malloc', 'free', '$FS', '$ENV', '$getWasmTableEntry'],
  $teleportDependencyServices: function() {
    return Module['teleportDependencyServices'] || (Module['teleportDependencyServices'] = {
      heap: () => HEAPU8,
      malloc: size => Number(_malloc(BigInt(size))),
      free: pointer => _free(BigInt(pointer)),
      FS: FS,
      ENV: ENV,
      emit: (callback, byte) => getWasmTableEntry(Number(callback))(byte),
      callback: pointer => getWasmTableEntry(Number(pointer)),
      printErr: text => err(text),
    });
  },
  tgetent__deps: ['$teleportDependencyServices'],
  tgetent__sig: 'ipp',
  tgetent: function(buffer, name) {
    return Module['nethackDependencies'].tgetent(teleportDependencyServices(), name);
  },
  tgetflag__deps: ['$teleportDependencyServices'],
  tgetflag__sig: 'ip',
  tgetflag: function(id) {
    return Module['nethackDependencies'].tgetflag(teleportDependencyServices(), id);
  },
  tgetnum__deps: ['$teleportDependencyServices'],
  tgetnum__sig: 'ip',
  tgetnum: function(id) {
    return Module['nethackDependencies'].tgetnum(teleportDependencyServices(), id);
  },
  tgetstr__deps: ['$teleportDependencyServices'],
  tgetstr__sig: 'ppp',
  tgetstr: function(id, area) {
    return Module['nethackDependencies'].tgetstr(teleportDependencyServices(), id, area);
  },
  tgoto__deps: ['$teleportDependencyServices'],
  tgoto__sig: 'ppii',
  tgoto: function(format, column, row) {
    return Module['nethackDependencies'].tgoto(teleportDependencyServices(), format, column, row);
  },
  teleport_js_tparm__deps: ['$teleportDependencyServices'],
  teleport_js_tparm__sig: 'ppp',
  teleport_js_tparm: function(format, parameters) {
    return Module['nethackDependencies'].tparm(teleportDependencyServices(), format, parameters);
  },
  teleport_js_tputs__deps: ['$teleportDependencyServices'],
  teleport_js_tputs__sig: 'ppi',
  teleport_js_tputs: function(value, lines) {
    return Module['nethackDependencies'].tputsPrepare(teleportDependencyServices(), value, lines);
  },
  teleport_compress_file__deps: ['$teleportDependencyServices'],
  teleport_compress_file__sig: 'ippi',
  teleport_compress_file: function(filename, compressed, unpack) {
    return Module['nethackDependencies'].compressFile(teleportDependencyServices(), filename, compressed, unpack);
  },
});

// This gate is evaluated by Emscripten's Node linker, not by the game runtime.
// The builder records it and uses it only for the separate --regex candidate.
if (process.env['TELEPORT_JS_REGEX'] === '1') addToLibrary({
  teleport_js_regcomp__deps: ['$teleportDependencyServices'],
  teleport_js_regcomp__sig: 'ippi',
  teleport_js_regcomp: function(re, pattern, flags) {
    return Module['nethackDependencies'].regcomp(teleportDependencyServices(), re, pattern, flags);
  },
  teleport_js_regexec__deps: ['$teleportDependencyServices'],
  teleport_js_regexec__sig: 'ippppi',
  teleport_js_regexec: function(re, text, count, matches, flags) {
    return Module['nethackDependencies'].regexec(teleportDependencyServices(), re, text, count, matches, flags);
  },
  teleport_js_regerror__deps: ['$teleportDependencyServices'],
  teleport_js_regerror__sig: 'pippp',
  teleport_js_regerror: function(code, re, destination, size) {
    return Module['nethackDependencies'].regerror(teleportDependencyServices(), code, re, destination, size);
  },
  teleport_js_regfree__deps: ['$teleportDependencyServices'],
  teleport_js_regfree__sig: 'vp',
  teleport_js_regfree: function(re) {
    Module['nethackDependencies'].regfree(teleportDependencyServices(), re);
  },
});
