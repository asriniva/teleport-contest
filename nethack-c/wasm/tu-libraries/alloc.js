// alloc ABI declarations only; all configured allocation policy is JS.
addToLibrary({
  $teleportAllocServices__deps: ['teleport_alloc_malloc', 'teleport_alloc_realloc', 'teleport_alloc_ptrbuf', 'teleport_alloc_format', 'teleport_alloc_panic_alloc', 'teleport_alloc_panic_realloc', 'teleport_alloc_panic_dupstr', 'teleport_alloc_panic_overflow', 'strlen', 'strcpy'],
  $teleportAllocServices: function() {
    return {
      heap: () => HEAPU8,
      malloc: size => Number(_teleport_alloc_malloc(size)),
      realloc: (pointer, size) => Number(_teleport_alloc_realloc(BigInt(pointer), size)),
      buffers: () => Number(_teleport_alloc_ptrbuf()),
      Sprintf: (pointer, format, value) => _teleport_alloc_format(BigInt(pointer), BigInt(value)),
      strlen: pointer => Number(_strlen(BigInt(pointer))),
      strcpy: (to, from) => Number(_strcpy(BigInt(to), BigInt(from))),
      panicAlloc: size => _teleport_alloc_panic_alloc(size),
      panicRealloc: size => _teleport_alloc_panic_realloc(size),
      panicDupstr: () => _teleport_alloc_panic_dupstr(),
      panicOverflow: (file, line) => _teleport_alloc_panic_overflow(BigInt(file), line),
    };
  },
  $teleportAllocCall__deps: ['$teleportAllocServices'],
  $teleportAllocCall: function(name, ...args) { return Module['nethackPorted'].alloc(teleportAllocServices(), name, ...args); },
  alloc__deps: ['$teleportAllocCall'], alloc__sig: 'pi',
  alloc: function(lth) { return teleportAllocCall('alloc', lth >>> 0); },
  re_alloc__deps: ['$teleportAllocCall'], re_alloc__sig: 'ppi',
  re_alloc: function(oldptr, newlth) { return teleportAllocCall('re_alloc', oldptr, newlth >>> 0); },
  fmt_ptr__deps: ['$teleportAllocCall'], fmt_ptr__sig: 'pj',
  fmt_ptr: function(ptr) { return teleportAllocCall('fmt_ptr', ptr); },
  dupstr__deps: ['$teleportAllocCall'], dupstr__sig: 'pp',
  dupstr: function(string) { return teleportAllocCall('dupstr', string); },
  FITSint___deps: ['$teleportAllocCall'], FITSint___sig: 'ijpi',
  FITSint_: function(i, file, line) { return teleportAllocCall('FITSint_', i, file, line); },
  FITSuint___deps: ['$teleportAllocCall'], FITSuint___sig: 'ijpi',
  FITSuint_: function(ull, file, line) { return teleportAllocCall('FITSuint_', BigInt.asUintN(64, ull), file, line); },
});
