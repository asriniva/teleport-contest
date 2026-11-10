// track ABI declarations only; game logic is in js/ported/track.js.
addToLibrary({
  $teleportTrackServices__deps: ['teleport_track_state_pointer', 'teleport_track_u', 'teleport_track_uleft', 'teleport_track_uright', 'teleport_track_update_file', 'teleport_track_release_data', 'teleport_track_panic', 'distmin', 'sfo_int', 'sfo_nhcoord', 'sfi_int', 'sfi_nhcoord', '$stackSave', '$stackRestore', '$stringToUTF8OnStack'],
  $teleportTrackServices: function() {
    var tagged = (fn, fp, pointer, tag) => {
      var stack = stackSave();
      try { fn(BigInt(fp), BigInt(pointer), BigInt(stringToUTF8OnStack(tag))); }
      finally { stackRestore(stack); }
    };
    return {
      heap: () => HEAPU8,
      state: () => Number(_teleport_track_state_pointer()),
      u: () => Number(_teleport_track_u()),
      left: () => Number(_teleport_track_uleft()),
      right: () => Number(_teleport_track_uright()),
      distmin: (x, y, tx, ty) => _distmin(x, y, tx, ty),
      update_file: fp => _teleport_track_update_file(BigInt(fp)),
      release_data: fp => _teleport_track_release_data(BigInt(fp)),
      Sfo_int: (fp, pointer, tag) => tagged(_sfo_int, fp, pointer, tag),
      Sfo_nhcoord: (fp, pointer, tag) => tagged(_sfo_nhcoord, fp, pointer, tag),
      Sfi_int: (fp, pointer, tag) => tagged(_sfi_int, fp, pointer, tag),
      Sfi_nhcoord: (fp, pointer, tag) => tagged(_sfi_nhcoord, fp, pointer, tag),
      trackPanic: () => _teleport_track_panic(),
    };
  },
  initrack__deps: ['$teleportTrackServices'],
  initrack__sig: 'v',
  initrack: function() { Module['nethackPorted'].track(teleportTrackServices(), 'initrack'); },
  settrack__deps: ['$teleportTrackServices'],
  settrack__sig: 'v',
  settrack: function() { Module['nethackPorted'].track(teleportTrackServices(), 'settrack'); },
  gettrack__deps: ['$teleportTrackServices'],
  gettrack__sig: 'pii',
  gettrack: function(x, y) { return Module['nethackPorted'].track(teleportTrackServices(), 'gettrack', x, y); },
  hastrack__deps: ['$teleportTrackServices'],
  hastrack__sig: 'iii',
  hastrack: function(x, y) { return Module['nethackPorted'].track(teleportTrackServices(), 'hastrack', x, y); },
  save_track__deps: ['$teleportTrackServices'],
  save_track__sig: 'vp',
  save_track: function(nhfp) { Module['nethackPorted'].track(teleportTrackServices(), 'save_track', nhfp); },
  rest_track__deps: ['$teleportTrackServices'],
  rest_track__sig: 'vp',
  rest_track: function(nhfp) { Module['nethackPorted'].track(teleportTrackServices(), 'rest_track', nhfp); },
});
