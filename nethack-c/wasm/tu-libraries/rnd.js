// RNG and recorder algorithms are JS; these are native/global/stdio bindings.
addToLibrary({
  $teleportRndServices__deps: ['teleport_rnd_core_function', 'teleport_rnd_display_function', 'teleport_rnd_luck', 'teleport_rnd_level', 'teleport_rnd_strong_seed', 'teleport_rnd_panic', 'teleport_rnd_impossible_one', 'teleport_rnd_impossible_two', 'teleport_rnd_snprintf_one', 'teleport_rnd_snprintf_two', 'teleport_rnd_print_full', 'teleport_rnd_print_file', 'teleport_rnd_print_plain', 'teleport_rnd_print_display', 'teleport_rnd_print_caller', 'teleport_rnd_print_source', 'getenv', 'fopen', 'setvbuf', 'fputc', 'sys_random_seed', 'sgn', '$stackSave', '$stackRestore', '$stackAlloc', '$stringToUTF8OnStack'],
  $teleportRndServices: function() {
    if (Module['teleportRndServices']) return Module['teleportRndServices'];
    var scoped = callback => {
      var stack = stackSave();
      try { return callback(); } finally { stackRestore(stack); }
    };
    var text = value => {
      if (typeof value === 'string') return BigInt(stringToUTF8OnStack(value));
      if (value instanceof Uint8Array) {
        var pointer = stackAlloc(value.length);
        HEAPU8.set(value, pointer);
        return BigInt(pointer);
      }
      return BigInt(value || 0);
    };
    return Module['teleportRndServices'] = {
      heap: () => HEAPU8,
      signedHeap: () => HEAP8,
      coreFunction: () => Number(_teleport_rnd_core_function()),
      displayFunction: () => Number(_teleport_rnd_display_function()),
      luck: () => _teleport_rnd_luck(),
      level: () => _teleport_rnd_level(),
      strongSeed: () => _teleport_rnd_strong_seed(),
      sys_random_seed: () => BigInt.asUintN(64, _sys_random_seed()),
      sgn: value => _sgn(value),
      getenv: name => scoped(() => Number(_getenv(text(name)))),
      fopen: (path, mode) => scoped(() => Number(_fopen(text(path), text(mode)))),
      setvbuf: (file, buffer, mode, size) => _setvbuf(BigInt(file), BigInt(buffer), mode, BigInt(size)),
      fputc: (value, file) => _fputc(value, BigInt(file)),
      panicBadRng: () => _teleport_rnd_panic(),
      impossible: (format, ...args) => scoped(() => args.length === 2
        ? _teleport_rnd_impossible_two(text(format), args[0], args[1])
        : _teleport_rnd_impossible_one(text(format), args[0])),
      snprintf: (buffer, size, format, ...args) => scoped(() => {
        var pointer = stackAlloc(buffer.length);
        HEAPU8.set(buffer, pointer);
        if (args.length === 2) _teleport_rnd_snprintf_two(BigInt(pointer), BigInt(size), text(format), args[0], args[1]);
        else _teleport_rnd_snprintf_one(BigInt(pointer), BigInt(size), text(format), args[0]);
        buffer.set(HEAPU8.subarray(pointer, pointer + buffer.length));
      }),
      fprintf: (file, format, ...args) => scoped(() => {
        var stream = BigInt(file), fmt = text(format);
        switch (format) {
          case '%d %s(%s) = %d @ %s(%s:%d)\n':
            return _teleport_rnd_print_full(stream, fmt, args[0], text(args[1]), text(args[2]), args[3], text(args[4]), text(args[5]), args[6]);
          case '%d %s(%s) = %d @ %s:%d\n':
            return _teleport_rnd_print_file(stream, fmt, args[0], text(args[1]), text(args[2]), args[3], text(args[4]), args[5]);
          case '%d %s(%s) = %d\n':
            return _teleport_rnd_print_plain(stream, fmt, args[0], text(args[1]), text(args[2]), args[3]);
          case '%d ~drn2(%d) = %d':
            return _teleport_rnd_print_display(stream, fmt, args[0], args[1], args[2]);
          case ' @ %s(%s:%d)':
            return _teleport_rnd_print_caller(stream, fmt, text(args[0]), text(args[1]), args[2]);
          case ' @ %s:%d':
            return _teleport_rnd_print_source(stream, fmt, text(args[0]), args[1]);
          default: throw new Error('Review changed RNG stdio ABI: ' + format);
        }
      }),
    };
  },
  $teleportRndCall__deps: ['$teleportRndServices'],
  $teleportRndCall: function(name, ...args) { return Module['nethackPorted'].rnd(teleportRndServices(), name, ...args); },
  rng_log_init__deps: ['$teleportRndCall'], rng_log_init__sig: 'v',
  rng_log_init: function() { teleportRndCall('rng_log_init'); },
  rng_log_enabled__deps: ['$teleportRndCall'], rng_log_enabled__sig: 'i',
  rng_log_enabled: function() { return teleportRndCall('rng_log_enabled'); },
  rng_log_set_caller__deps: ['$teleportRndCall'], rng_log_set_caller__sig: 'vpip',
  rng_log_set_caller: function(file, line, func) { teleportRndCall('rng_log_set_caller', file, line, func); },
  rng_log_get_call_count__deps: ['$teleportRndCall'], rng_log_get_call_count__sig: 'i',
  rng_log_get_call_count: function() { return teleportRndCall('rng_log_get_call_count'); },
  init_isaac64__deps: ['$teleportRndCall'], init_isaac64__sig: 'vjp',
  init_isaac64: function(seed, fn) { teleportRndCall('init_isaac64', BigInt.asUintN(64, seed), fn); },
  rn2_on_display_rng__deps: ['$teleportRndCall'], rn2_on_display_rng__sig: 'ii',
  rn2_on_display_rng: function(x) { return teleportRndCall('rn2_on_display_rng', x); },
  rn2__deps: ['$teleportRndCall'], rn2__sig: 'ii',
  rn2: function(x) { return teleportRndCall('rn2', x); },
  rnl__deps: ['$teleportRndCall'], rnl__sig: 'ii',
  rnl: function(x) { return teleportRndCall('rnl', x); },
  rnd__deps: ['$teleportRndCall'], rnd__sig: 'ii',
  rnd: function(x) { return teleportRndCall('rnd', x); },
  rnd_on_display_rng__deps: ['$teleportRndCall'], rnd_on_display_rng__sig: 'ii',
  rnd_on_display_rng: function(x) { return teleportRndCall('rnd_on_display_rng', x); },
  d__deps: ['$teleportRndCall'], d__sig: 'iii',
  d: function(n, x) { return teleportRndCall('d', n, x); },
  rne__deps: ['$teleportRndCall'], rne__sig: 'ii',
  rne: function(x) { return teleportRndCall('rne', x); },
  rnz__deps: ['$teleportRndCall'], rnz__sig: 'ii',
  rnz: function(i) { return teleportRndCall('rnz', i); },
  init_random__deps: ['$teleportRndCall'], init_random__sig: 'vp',
  init_random: function(fn) { teleportRndCall('init_random', fn); },
  reseed_random__deps: ['$teleportRndCall'], reseed_random__sig: 'vp',
  reseed_random: function(fn) { teleportRndCall('reseed_random', fn); },
  shuffle_int_array__deps: ['$teleportRndCall'], shuffle_int_array__sig: 'vpi',
  shuffle_int_array: function(indices, count) { teleportRndCall('shuffle_int_array', indices, count); },
});
