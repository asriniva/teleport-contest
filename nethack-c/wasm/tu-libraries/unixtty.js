// Native terminal/variadic ABI only; unixtty control flow lives in JavaScript.
addToLibrary({
  $teleportUnixttyServices__deps: ['teleport_unixtty_initial', 'teleport_unixtty_current', 'teleport_unixtty_scalar', 'teleport_unixtty_set_scalar', 'teleport_unixtty_iflag', 'teleport_unixtty_set_iflag', 'teleport_unixtty_window', 'teleport_unixtty_speed', 'teleport_unixtty_fpathconf', 'teleport_unixtty_perror', 'teleport_unixtty_vprintf', 'teleport_unixtty_putchar', 'teleport_unixtty_exit', 'teleport_unixtty_raw_print', 'teleport_unixtty_exit_windows', 'teleport_ioctl_getattr', 'teleport_ioctl_setattr', 'getenv', 'getioctls', 'setioctls', 'term_start_screen', 'term_end_screen', '$stringToUTF8OnStack'],
  $teleportUnixttyServices: function() {
    return {
      heap: () => HEAPU8,
      signedHeap: () => HEAP8,
      initial: () => Number(_teleport_unixtty_initial()),
      current: () => Number(_teleport_unixtty_current()),
      scalar: index => _teleport_unixtty_scalar(index),
      setScalar: (index, value) => _teleport_unixtty_set_scalar(index, value),
      iflag: index => _teleport_unixtty_iflag(index),
      setIflag: (index, value) => _teleport_unixtty_set_iflag(index, value),
      wpId: () => _teleport_unixtty_window(),
      tcgetattr: (fd, pointer) => _teleport_ioctl_getattr(fd, BigInt(pointer)),
      tcsetattr: (fd, action, pointer) => _teleport_ioctl_setattr(fd, action, BigInt(pointer)),
      cfgetospeed: pointer => _teleport_unixtty_speed(BigInt(pointer)) >>> 0,
      fpathconf: (fd, name) => _teleport_unixtty_fpathconf(fd, name),
      getenv: name => Number(_getenv(BigInt(stringToUTF8OnStack(name)))),
      perror: message => _teleport_unixtty_perror(BigInt(stringToUTF8OnStack(message))),
      getioctls: () => _getioctls(),
      setioctls: () => _setioctls(),
      term_start_screen: () => _term_start_screen(),
      term_end_screen: () => _term_end_screen(),
      raw_print: message => _teleport_unixtty_raw_print(BigInt(message)),
      exit_nhwindows: message => _teleport_unixtty_exit_windows(BigInt(message)),
      vprintf: (format, args) => _teleport_unixtty_vprintf(BigInt(format), BigInt(args)),
      putchar: value => _teleport_unixtty_putchar(value),
      exit: value => _teleport_unixtty_exit(value),
    };
  },
  $teleportUnixttyCall__deps: ['$teleportUnixttyServices', '$stackSave', '$stackRestore'],
  $teleportUnixttyCall: function(name) {
    var args = Array.prototype.slice.call(arguments, 1);
    var stack = stackSave();
    try { return Module['nethackPorted'].unixtty(teleportUnixttyServices(), name, ...args); }
    finally { stackRestore(stack); }
  },
  gettty__deps: ['$teleportUnixttyCall'], gettty__sig: 'v',
  gettty: function() { teleportUnixttyCall('gettty'); },
  settty__deps: ['$teleportUnixttyCall'], settty__sig: 'vp',
  settty: function(s) { teleportUnixttyCall('settty', s); },
  setftty__deps: ['$teleportUnixttyCall'], setftty__sig: 'v',
  setftty: function() { teleportUnixttyCall('setftty'); },
  intron__deps: ['$teleportUnixttyCall'], intron__sig: 'v',
  intron: function() { teleportUnixttyCall('intron'); },
  introff__deps: ['$teleportUnixttyCall'], introff__sig: 'v',
  introff: function() { teleportUnixttyCall('introff'); },
  error__deps: ['$teleportUnixttyCall'], error__sig: 'vpp',
  error: function(s, args) { teleportUnixttyCall('error', s, args); },
  tty_utf8graphics_fixup__deps: ['$teleportUnixttyCall'], tty_utf8graphics_fixup__sig: 'v',
  tty_utf8graphics_fixup: function() { teleportUnixttyCall('tty_utf8graphics_fixup'); },
});
