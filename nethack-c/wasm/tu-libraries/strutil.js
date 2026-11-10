// strutil ABI declarations only; game logic is in js/ported/strutil.js.
addToLibrary({
  $teleportStrutilServices__deps: ['alloc', 'free', 'strlen', 'strcat', 'strcpy', 'strchr', 'lowc', 'teleport_strutil_panic'],
  $teleportStrutilServices: function() {
    return {
      heap: () => HEAPU8,
      signedHeap: () => HEAP8,
      alloc: size => Number(_alloc(size >>> 0)),
      free: pointer => _free(BigInt(pointer)),
      strlen: pointer => Number(_strlen(BigInt(pointer))),
      Strcat: (dest, source) => _strcat(BigInt(dest), BigInt(source)),
      Strcpy: (dest, source) => _strcpy(BigInt(dest), BigInt(source)),
      strchr: (string, c) => Number(_strchr(BigInt(string), c)),
      lowc: c => _lowc(c),
      panic: (format, file, line) => _teleport_strutil_panic(BigInt(file), line),
    };
  },
  strbuf_init__deps: ['$teleportStrutilServices'],
  strbuf_init__sig: 'vp',
  strbuf_init: function(strbuf) {
    Module['nethackPorted'].strutil(teleportStrutilServices(), 'strbuf_init', strbuf);
  },
  strbuf_append__deps: ['$teleportStrutilServices'],
  strbuf_append__sig: 'vpp',
  strbuf_append: function(strbuf, str) {
    Module['nethackPorted'].strutil(teleportStrutilServices(), 'strbuf_append', strbuf, str);
  },
  strbuf_reserve__deps: ['$teleportStrutilServices'],
  strbuf_reserve__sig: 'vpi',
  strbuf_reserve: function(strbuf, len) {
    Module['nethackPorted'].strutil(teleportStrutilServices(), 'strbuf_reserve', strbuf, len);
  },
  strbuf_empty__deps: ['$teleportStrutilServices'],
  strbuf_empty__sig: 'vp',
  strbuf_empty: function(strbuf) {
    Module['nethackPorted'].strutil(teleportStrutilServices(), 'strbuf_empty', strbuf);
  },
  strbuf_nl_to_crlf__deps: ['$teleportStrutilServices'],
  strbuf_nl_to_crlf__sig: 'vp',
  strbuf_nl_to_crlf: function(strbuf) {
    Module['nethackPorted'].strutil(teleportStrutilServices(), 'strbuf_nl_to_crlf', strbuf);
  },
  Strlen___deps: ['$teleportStrutilServices'],
  Strlen___sig: 'ippi',
  Strlen_: function(str, file, line) {
    return Module['nethackPorted'].strutil(teleportStrutilServices(), 'Strlen_', str, file, line);
  },
  pmatch__deps: ['$teleportStrutilServices'],
  pmatch__sig: 'ipp',
  pmatch: function(patrn, strng) {
    return Module['nethackPorted'].strutil(teleportStrutilServices(), 'pmatch', patrn, strng);
  },
  pmatchi__deps: ['$teleportStrutilServices'],
  pmatchi__sig: 'ipp',
  pmatchi: function(patrn, strng) {
    return Module['nethackPorted'].strutil(teleportStrutilServices(), 'pmatchi', patrn, strng);
  },
});
