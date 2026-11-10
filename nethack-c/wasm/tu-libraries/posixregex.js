// POSIX libc ABI only; NetHack wrapper logic and identifier are JS.
addToLibrary({
  $teleportPosixregexServices__deps: ['teleport_posixregex_identifier', 'alloc', 'free', 'strcpy', 'regcomp', 'regexec', 'regerror', 'regfree', '$stringToUTF8OnStack'],
  $teleportPosixregexServices: function() {
    return {
      heap: () => HEAPU8,
      signedHeap: () => HEAP8,
      identifier: () => Number(_teleport_posixregex_identifier()),
      alloc: size => Number(_alloc(size >>> 0)),
      free: pointer => _free(BigInt(pointer)),
      Strcpy: (dest, source) => Number(_strcpy(BigInt(dest), BigInt(typeof source === 'string' ? stringToUTF8OnStack(source) : source))),
      regcomp: (re, source, flags) => _regcomp(BigInt(re), BigInt(source), flags),
      regexec: (re, source, count, matches, flags) => _regexec(BigInt(re), BigInt(source), BigInt(count), BigInt(matches), flags),
      regerror: (error, re, dest, size) => _regerror(error, BigInt(re), BigInt(dest), BigInt(size)),
      regfree: re => _regfree(BigInt(re)),
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
