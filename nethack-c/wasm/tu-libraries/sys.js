// sys ABI declarations only; initialization and cleanup are in js/ported/sys.js.
addToLibrary({
  $teleportSysServices__deps: ['teleport_sys_pointer', 'teleport_sys_gc_pointer', 'teleport_sys_panic', 'getenv', 'dupstr', 'free', '$stringToUTF8OnStack'],
  $teleportSysServices: function() {
    return {
      heap: () => HEAPU8,
      sysPointer: () => Number(_teleport_sys_pointer()),
      gcPointer: () => Number(_teleport_sys_gc_pointer()),
      getenv: name => Number(_getenv(BigInt(stringToUTF8OnStack(name)))),
      dupstr: value => Number(_dupstr(BigInt(typeof value === 'string' ? stringToUTF8OnStack(value) : value))),
      free: pointer => _free(BigInt(pointer)),
      sysPanic: () => _teleport_sys_panic(),
    };
  },
  $teleportSysCall__deps: ['$teleportSysServices', '$stackSave', '$stackRestore'],
  $teleportSysCall: function(name) {
    var stack = stackSave();
    try { return Module['nethackPorted'].sys(teleportSysServices(), name); }
    finally { stackRestore(stack); }
  },
  sys_early_init__deps: ['$teleportSysCall'],
  sys_early_init__sig: 'v',
  sys_early_init: function() { teleportSysCall('sys_early_init'); },
  sysopt_release__deps: ['$teleportSysCall'],
  sysopt_release__sig: 'v',
  sysopt_release: function() { teleportSysCall('sysopt_release'); },
  sysopt_seduce_set__sig: 'vi',
  sysopt_seduce_set: function(val) { Module['nethackPorted'].sys({}, 'sysopt_seduce_set', val); },
});
