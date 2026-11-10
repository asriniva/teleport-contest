// date ABI declarations only; metadata population/parsing/cleanup are JS.
addToLibrary({
  $teleportDateServices__deps: ['teleport_date_pointer', 'teleport_date_format', 'getenv', 'strlen', 'atoi', 'case_insensitive_comp', 'mktime', 'dupstr', 'free', 'md_ignored_features', 'mdlib_version_string', 'version_id_string', 'bannerc_string', 'malloc', '$stackAlloc', '$stringToUTF8OnStack'],
  $teleportDateServices: function() {
    var text = value => typeof value === 'string' ? BigInt(stringToUTF8OnStack(value)) : BigInt(value || 0);
    return {
      heap: () => HEAPU8,
      signedHeap: () => HEAP8,
      stackAlloc: size => stackAlloc(size),
      data: () => Number(_teleport_date_pointer()),
      malloc: size => Number(_malloc(BigInt(size))),
      getenv: name => Number(_getenv(text(name))),
      strlen: pointer => Number(_strlen(BigInt(pointer))),
      atoi: pointer => _atoi(BigInt(pointer)),
      case_insensitive_comp: (a, b) => _case_insensitive_comp(text(a), text(b)),
      mktime: value => _mktime(BigInt(value.address)),
      dupstr: value => Number(_dupstr(text(value))),
      free: pointer => _free(BigInt(pointer)),
      SnprintDate: (pointer, size, value) => _teleport_date_format(BigInt(pointer), BigInt(size), text(value)),
      md_ignored_features: () => BigInt.asUintN(64, _md_ignored_features()),
      mdlib_version_string: (pointer, delim) => Number(_mdlib_version_string(BigInt(pointer), text(delim))),
      version_id_string: (pointer, size, date) => Number(_version_id_string(BigInt(pointer), BigInt(size), text(date))),
      bannerc_string: (pointer, size, date) => Number(_bannerc_string(BigInt(pointer), BigInt(size), text(date))),
    };
  },
  $teleportDateInit__deps: ['$teleportDateServices', '$addOnInit'],
  $teleportDateInit__postset: "addOnInit(() => Module['nethackPorted'].initializeDate(teleportDateServices()));",
  $teleportDateInit: 0,
  $teleportDateCall__deps: ['$teleportDateServices', '$teleportDateInit', '$stackSave', '$stackRestore'],
  $teleportDateCall: function(name, ...args) {
    var stack = stackSave();
    try { return Module['nethackPorted'].date(teleportDateServices(), name, ...args); }
    finally { stackRestore(stack); }
  },
  populate_nomakedefs__deps: ['$teleportDateCall'],
  populate_nomakedefs__sig: 'vp',
  populate_nomakedefs: function(version) { teleportDateCall('populate_nomakedefs', version); },
  free_nomakedefs__deps: ['$teleportDateCall'],
  free_nomakedefs__sig: 'v',
  free_nomakedefs: function() { teleportDateCall('free_nomakedefs'); },
});
