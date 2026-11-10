// calendar ABI declarations only; game logic is in js/ported/calendar.js.
addToLibrary({
  $teleportCalendarServices__deps: ['teleport_calendar_time', 'teleport_calendar_localtime', 'teleport_calendar_datestr', 'teleport_calendar_format', 'mktime', 'nh_getenv', 'strlen', 'atoi', 'strtoll', '$stackAlloc', '$stringToUTF8OnStack'],
  $teleportCalendarServices: function() {
    return {
      heap: () => HEAPU8,
      signedHeap: () => HEAP8,
      stackAlloc: size => stackAlloc(size),
      nh_getenv: name => Number(_nh_getenv(BigInt(stringToUTF8OnStack(name)))),
      // Replay supplies its process clock; ordinary callers retain native time.
      time: () => typeof Module['nethackCalendarTime'] === 'function'
        ? Module['nethackCalendarTime']() : _teleport_calendar_time(),
      localtimePointer: date => Number(_teleport_calendar_localtime(date)),
      mktimePointer: pointer => _mktime(BigInt(pointer)),
      strlen: pointer => Number(_strlen(BigInt(pointer))),
      atoi: pointer => _atoi(BigInt(pointer)),
      strtoll: (pointer, end, base) => _strtoll(BigInt(pointer), BigInt(end), base),
      datestr: () => Number(_teleport_calendar_datestr()),
      Snprintf: (pointer, size, format, year, month, day, hour, minute, second) =>
        _teleport_calendar_format(BigInt(pointer), BigInt(size), year, month, day, hour, minute, second),
    };
  },
  $teleportCalendarCall__deps: ['$teleportCalendarServices', '$stackSave', '$stackRestore'],
  $teleportCalendarCall: function(name, ...args) {
    var stack = stackSave();
    try { return Module['nethackPorted'].calendar(teleportCalendarServices(), name, ...args); }
    finally { stackRestore(stack); }
  },
  getnow__deps: ['$teleportCalendarCall'],
  getnow__sig: 'j',
  getnow: function() { return teleportCalendarCall('getnow'); },
  getyear__deps: ['$teleportCalendarCall'],
  getyear__sig: 'i',
  getyear: function() { return teleportCalendarCall('getyear'); },
  yyyymmdd__deps: ['$teleportCalendarCall'],
  yyyymmdd__sig: 'jj',
  yyyymmdd: function(date) { return teleportCalendarCall('yyyymmdd', date); },
  hhmmss__deps: ['$teleportCalendarCall'],
  hhmmss__sig: 'jj',
  hhmmss: function(date) { return teleportCalendarCall('hhmmss', date); },
  yyyymmddhhmmss__deps: ['$teleportCalendarCall'],
  yyyymmddhhmmss__sig: 'pj',
  yyyymmddhhmmss: function(date) { return teleportCalendarCall('yyyymmddhhmmss', date); },
  time_from_yyyymmddhhmmss__deps: ['$teleportCalendarCall'],
  time_from_yyyymmddhhmmss__sig: 'jp',
  time_from_yyyymmddhhmmss: function(buf) { return teleportCalendarCall('time_from_yyyymmddhhmmss', buf); },
  phase_of_the_moon__deps: ['$teleportCalendarCall'],
  phase_of_the_moon__sig: 'i',
  phase_of_the_moon: function() { return teleportCalendarCall('phase_of_the_moon'); },
  friday_13th__deps: ['$teleportCalendarCall'],
  friday_13th__sig: 'i',
  friday_13th: function() { return teleportCalendarCall('friday_13th'); },
  night__deps: ['$teleportCalendarCall'],
  night__sig: 'i',
  night: function() { return teleportCalendarCall('night'); },
  midnight__deps: ['$teleportCalendarCall'],
  midnight__sig: 'i',
  midnight: function() { return teleportCalendarCall('midnight'); },
});
