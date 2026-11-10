// ABI imports only. Dependency algorithms live in js/services/*.js.
addToLibrary({
  $teleportDependencyServices__deps: ['malloc', 'free', '$FS', '$ENV', '$getWasmTableEntry'],
  $teleportDependencyServices: function() {
    return {
      heap: () => HEAPU8,
      malloc: size => Number(_malloc(BigInt(size))),
      free: pointer => _free(BigInt(pointer)),
      FS: FS,
      ENV: ENV,
      emit: (callback, byte) => getWasmTableEntry(Number(callback))(byte),
      printErr: text => err(text),
    };
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
  tputs__deps: ['$teleportDependencyServices'],
  tputs__sig: 'ipip',
  tputs: function(value, lines, callback) {
    return Module['nethackDependencies'].tputs(teleportDependencyServices(), value, lines, callback);
  },
  teleport_compress_file__deps: ['$teleportDependencyServices'],
  teleport_compress_file__sig: 'ippi',
  teleport_compress_file: function(filename, compressed, unpack) {
    return Module['nethackDependencies'].compressFile(teleportDependencyServices(), filename, compressed, unpack);
  },
});
