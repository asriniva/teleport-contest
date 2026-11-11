// POSIX libc ABI only; NetHack wrapper logic and identifier are JS.
addToLibrary({
  $teleportPosixregexServices__deps: ['regcomp', 'regexec', 'regerror', 'regfree', 'teleport_posixregex_identifier', 'teleport_posixregex_free', 'alloc', 'strcpy', '$stringToUTF8OnStack'],
  $teleportPosixregexServices: function() {
    return {
      moduleKey: Module,
      regcomp: (re, text, flags) => _regcomp(BigInt(re), BigInt(text), flags),
      regexec: (re, text, count, matches, flags) => _regexec(BigInt(re), BigInt(text), BigInt(count), BigInt(matches), flags),
      regerror: (error, re, out, size) => Number(_regerror(error, BigInt(re), BigInt(out), BigInt(size))),
      regfree: re => _regfree(BigInt(re)),
      heap: () => HEAPU8,
      signedHeap: () => HEAP8,
      identifier: () => Number(_teleport_posixregex_identifier()),
      alloc: size => Number(_alloc(size >>> 0)),
      free: pointer => _teleport_posixregex_free(BigInt(pointer)),
      Strcpy: (dest, source) => Number(_strcpy(BigInt(dest), BigInt(typeof source === 'string' ? stringToUTF8OnStack(source) : source))),
    };
  },
  $teleportPosixregexInit__deps: ['$teleportPosixregexServices', '$addOnInit'],
  $teleportPosixregexInit__postset: "addOnInit(() => Module['nethackPorted'].initializePosixregex(teleportPosixregexServices()));",
  $teleportPosixregexInit: 0,
  $teleportPosixregexCall__deps: ['$teleportPosixregexServices', '$teleportPosixregexInit', '$stackSave', '$stackRestore'],
  $teleportPosixregexCall: function(name, ...args) {
    var stack = stackSave();
    try { return Module['nethackPorted'].posixregex(teleportPosixregexServices(), name, ...args); }
    finally { stackRestore(stack); }
  },
  regex_init__deps: ['$teleportPosixregexCall'], regex_init__sig: 'p',
  regex_init: function() { return teleportPosixregexCall('regex_init'); },
  regex_compile__deps: ['$teleportPosixregexCall'], regex_compile__sig: 'ipp',
  regex_compile: function(s, re) { return teleportPosixregexCall('regex_compile', s, re); },
  regex_error_desc__deps: ['$teleportPosixregexCall'], regex_error_desc__sig: 'ppp',
  regex_error_desc: function(re, errbuf) { return teleportPosixregexCall('regex_error_desc', re, errbuf); },
  regex_match__deps: ['$teleportPosixregexCall'], regex_match__sig: 'ipp',
  regex_match: function(s, re) { return teleportPosixregexCall('regex_match', s, re); },
  regex_free__deps: ['$teleportPosixregexCall'], regex_free__sig: 'vp',
  regex_free: function(re) { teleportPosixregexCall('regex_free', re); },
});
