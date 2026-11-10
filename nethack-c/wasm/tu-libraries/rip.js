// rip ABI declarations only; tombstone algorithms are in js/ported/rip.js.
addToLibrary({
  $teleportRipServices__deps: ['teleport_rip_head_pointer', 'teleport_rip_name', 'teleport_rip_money', 'teleport_rip_putstr', 'teleport_rip_format_name', 'teleport_rip_format_cash', 'teleport_rip_format_year', 'alloc', 'dupstr', 'free', 'strlen', 'formatkiller', 'yyyymmdd', '$stackAlloc', '$stringToUTF8OnStack', 'teleport_rip_dump'
  ],
  $teleportRipServices: function() {
    var text = value => typeof value === 'string' ? BigInt(stringToUTF8OnStack(value)) : BigInt(value || 0);
    return {
      heap: () => HEAPU8,
      signedHeap: () => HEAP8,
      stackAlloc: size => stackAlloc(size),
      head: () => Number(_teleport_rip_head_pointer()),
      name: () => Number(_teleport_rip_name()),
      money: () => _teleport_rip_money(),
      alloc: size => Number(_alloc(size >>> 0)),
      dupstr: value => Number(_dupstr(text(value))),
      free: pointer => _free(BigInt(pointer)),
      strlen: pointer => Number(_strlen(BigInt(pointer))),
      Sprintf: (pointer, format, ...args) => {
        if (format === '%.*s') _teleport_rip_format_name(BigInt(pointer), args[0], text(args[1]));
        else if (format === '%ld Au') _teleport_rip_format_cash(BigInt(pointer), args[0]);
        else _teleport_rip_format_year(BigInt(pointer), args[0]);
      },
      formatkiller: (pointer, size, how, flag) => _formatkiller(BigInt(pointer), size >>> 0, how, flag),
      yyyymmdd: when => _yyyymmdd(when),
      putstr: (window, attr, value) => _teleport_rip_putstr(window, attr, text(value)),
      dump_forward_putstr: (window, attr, value, forward) => _teleport_rip_dump(window, attr, text(value), forward),
    };
  },
  $teleportRipCall__deps: ['$teleportRipServices', '$stackSave', '$stackRestore'],
  $teleportRipCall: function(tmpwin, how, when) {
    var stack = stackSave();
    try { return Module['nethackPorted'].rip(teleportRipServices(), 'genl_outrip', tmpwin, how, when); }
    finally { stackRestore(stack); }
  },
  genl_outrip__deps: ['$teleportRipCall'],
  genl_outrip__sig: 'viij',
  genl_outrip: function(tmpwin, how, when) { teleportRipCall(tmpwin, how, when); },
});
