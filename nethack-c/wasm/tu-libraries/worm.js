// Native ABI only; all worm algorithms and private arrays remain JavaScript.
addToLibrary({
  $teleportWormServices__deps: ['teleport_worm_global', 'teleport_worm_monster_bit', 'teleport_worm_set_monster_bit', 'teleport_worm_free', 'teleport_worm_sfo_int', 'teleport_worm_sfi_int', 'teleport_worm_sfo_coordxy', 'teleport_worm_sfi_coordxy', 'teleport_worm_sfo_long', 'teleport_worm_sfi_long', 'teleport_worm_rn2', 'teleport_worm_rnd', 'teleport_worm_d', 'teleport_worm_impossible_ints', 'teleport_worm_impossible_strings', 'teleport_worm_pline', 'teleport_worm_you', 'teleport_worm_literal_storage', 'teleport_worm_literal_capacity', 'alloc', 'newsym', 'mcalcmove', 'mattacku', 'clone_mon', 'canseemon', 'sensemon', 's_suffix', 'mon_nam', 'Monnam', 'rn2_on_display_rng', 'show_glyph', 'fmt_ptr', 'isok', 'rnd_nextto_goodpos', 'dist2', 'distmin', '$lengthBytesUTF8', '$stringToUTF8', '$stackAlloc', '$stackSave', '$stackRestore'],
  $teleportWormServices: function() {
    var state = Module['teleportWormCache'] ||= { next: 0, strings: new Map() };
    var pointer = value => BigInt(value ? value.address ?? value : 0);
    var byte = value => Number(BigInt.asIntN(8,BigInt(value)));
    var coord = value => Number(BigInt.asIntN(16,BigInt(value)));
    var literal = value => {
      if (state.strings.has(value)) return state.strings.get(value);
      var size = lengthBytesUTF8(value) + 1;
      if (state.next + size > Number(_teleport_worm_literal_capacity())) throw new Error('Review changed worm literal corpus');
      var at = Number(_teleport_worm_literal_storage()) + state.next;
      stringToUTF8(value,at,size); state.next += size; state.strings.set(value,at); return at;
    };
    var text = value => typeof value === 'string' ? BigInt(literal(value)) : pointer(value);
    var callers = ['worm_move','worm_nomove','cutworm'];
    var callerIndex = value => {
      var index = typeof value === 'string' ? callers.indexOf(value) : value;
      if (!Number.isInteger(index) || index < 0 || index >= callers.length) throw new Error('Unexpected original worm RNG caller');
      return index;
    };
    var services = {
      moduleKey: Module, heap: () => HEAPU8, literal,
      stackAlloc: size => Number(stackAlloc(size)), stackSave: () => stackSave(), stackRestore: saved => stackRestore(saved),
      global: index => Number(_teleport_worm_global(index)),
      monsterBit: (mon,index) => _teleport_worm_monster_bit(pointer(mon),index),
      setMonsterBit: (mon,index,value) => _teleport_worm_set_monster_bit(pointer(mon),index,Number(value)>>>0),
      free: value => _teleport_worm_free(pointer(value)),
      rn2: (bound,line,caller) => _teleport_worm_rn2(bound,line,callerIndex(caller)),
      rnd: (bound,line,caller) => _teleport_worm_rnd(bound,line,callerIndex(caller)),
      d: (dice,sides,line,caller) => _teleport_worm_d(dice,sides,line,callerIndex(caller)),
      impossible: (format,...args) => format.includes('%s')
        ? _teleport_worm_impossible_strings(text(format),text(args[0]),text(args[1]))
        : _teleport_worm_impossible_ints(text(format),args[0]??0,args[1]??0,args[2]??0,args[3]??0),
      pline: (format,value) => _teleport_worm_pline(text(format),text(value)),
      You: (format,value) => _teleport_worm_you(text(format),text(value)),
      Sfo_int: (fp,value,tag) => _teleport_worm_sfo_int(pointer(fp),pointer(value),text(tag)),
      Sfo_coordxy: (fp,value,tag) => _teleport_worm_sfo_coordxy(pointer(fp),pointer(value),text(tag)),
      Sfo_long: (fp,value,tag) => _teleport_worm_sfo_long(pointer(fp),pointer(value),text(tag)),
      Sfi_int: (fp,value,tag) => _teleport_worm_sfi_int(pointer(fp),pointer(value),text(tag)),
      Sfi_coordxy: (fp,value,tag) => _teleport_worm_sfi_coordxy(pointer(fp),pointer(value),text(tag)),
      Sfi_long: (fp,value,tag) => _teleport_worm_sfi_long(pointer(fp),pointer(value),text(tag)),
      alloc: (size) => Number(_alloc(Number(size)>>>0)),
      newsym: (x,y) => _newsym(coord(x),coord(y)),
      mcalcmove: (mon,slow) => _mcalcmove(pointer(mon),byte(slow)),
      mattacku: (mon) => _mattacku(pointer(mon)),
      clone_mon: (mon,x,y) => Number(_clone_mon(pointer(mon),coord(x),coord(y))),
      canseemon: (mon) => _canseemon(pointer(mon)),
      sensemon: (mon) => _sensemon(pointer(mon)),
      s_suffix: (name) => Number(_s_suffix(text(name))),
      mon_nam: (mon) => Number(_mon_nam(pointer(mon))),
      Monnam: (mon) => Number(_Monnam(pointer(mon))),
      rn2_on_display_rng: (bound) => _rn2_on_display_rng(bound),
      show_glyph: (x,y,glyph) => _show_glyph(coord(x),coord(y),glyph),
      fmt_ptr: (value) => Number(_fmt_ptr(pointer(value))),
      isok: (x,y) => _isok(coord(x),coord(y)),
      rnd_nextto_goodpos: (x,y,mon) => _rnd_nextto_goodpos(pointer(x),pointer(y),pointer(mon)),
      dist2: (x,y,xx,yy) => _dist2(coord(x),coord(y),coord(xx),coord(yy)),
      distmin: (x,y,xx,yy) => _distmin(coord(x),coord(y),coord(xx),coord(yy)),
    };
    return services;
  },
  $teleportWormCall__deps: ['$teleportWormServices','$stackSave','$stackRestore'],
  $teleportWormCall: function(name,...args) {
    var saved = stackSave();
    try { return Module['nethackPorted'].worm(teleportWormServices(),name,...args); }
    finally { stackRestore(saved); }
  },
  get_wormno__deps: ['$teleportWormCall'], get_wormno__sig: 'i',
  get_wormno: function() { return teleportWormCall('get_wormno'); },
  initworm__deps: ['$teleportWormCall'], initworm__sig: 'vpi',
  initworm: function(mon,count) { teleportWormCall('initworm',mon,count); },
  worm_move__deps: ['$teleportWormCall'], worm_move__sig: 'vp',
  worm_move: function(mon) { teleportWormCall('worm_move',mon); },
  worm_nomove__deps: ['$teleportWormCall'], worm_nomove__sig: 'vp',
  worm_nomove: function(mon) { teleportWormCall('worm_nomove',mon); },
  wormgone__deps: ['$teleportWormCall'], wormgone__sig: 'vp',
  wormgone: function(mon) { teleportWormCall('wormgone',mon); },
  wormhitu__deps: ['$teleportWormCall'], wormhitu__sig: 'ip',
  wormhitu: function(mon) { return teleportWormCall('wormhitu',mon); },
  cutworm__deps: ['$teleportWormCall'], cutworm__sig: 'vpiii',
  cutworm: function(mon,x,y,cut) { teleportWormCall('cutworm',mon,x<<16>>16,y<<16>>16,cut<<24>>24); },
  see_wsegs__deps: ['$teleportWormCall'], see_wsegs__sig: 'vp',
  see_wsegs: function(mon) { teleportWormCall('see_wsegs',mon); },
  detect_wsegs__deps: ['$teleportWormCall'], detect_wsegs__sig: 'vpi',
  detect_wsegs: function(mon,detect) { teleportWormCall('detect_wsegs',mon,detect<<24>>24); },
  save_worm__deps: ['$teleportWormCall'], save_worm__sig: 'vp',
  save_worm: function(fp) { teleportWormCall('save_worm',fp); },
  rest_worm__deps: ['$teleportWormCall'], rest_worm__sig: 'vp',
  rest_worm: function(fp) { teleportWormCall('rest_worm',fp); },
  place_wsegs__deps: ['$teleportWormCall'], place_wsegs__sig: 'vpp',
  place_wsegs: function(mon,old) { teleportWormCall('place_wsegs',mon,old); },
  sanity_check_worm__deps: ['$teleportWormCall'], sanity_check_worm__sig: 'vp',
  sanity_check_worm: function(mon) { teleportWormCall('sanity_check_worm',mon); },
  wormno_sanity_check__deps: ['$teleportWormCall'], wormno_sanity_check__sig: 'v',
  wormno_sanity_check: function() { teleportWormCall('wormno_sanity_check'); },
  remove_worm__deps: ['$teleportWormCall'], remove_worm__sig: 'vp',
  remove_worm: function(mon) { teleportWormCall('remove_worm',mon); },
  place_worm_tail_randomly__deps: ['$teleportWormCall'], place_worm_tail_randomly__sig: 'vpii',
  place_worm_tail_randomly: function(mon,x,y) { teleportWormCall('place_worm_tail_randomly',mon,x<<16>>16,y<<16>>16); },
  size_wseg__deps: ['$teleportWormCall'], size_wseg__sig: 'ip',
  size_wseg: function(mon) { return teleportWormCall('size_wseg',mon); },
  count_wsegs__deps: ['$teleportWormCall'], count_wsegs__sig: 'ip',
  count_wsegs: function(mon) { return teleportWormCall('count_wsegs',mon); },
  worm_known__deps: ['$teleportWormCall'], worm_known__sig: 'ip',
  worm_known: function(mon) { return teleportWormCall('worm_known',mon); },
  worm_cross__deps: ['$teleportWormCall'], worm_cross__sig: 'iiiii',
  worm_cross: function(x,y,xx,yy) { return teleportWormCall('worm_cross',x,y,xx,yy); },
  wseg_at__deps: ['$teleportWormCall'], wseg_at__sig: 'ipii',
  wseg_at: function(mon,x,y) { return teleportWormCall('wseg_at',mon,x,y); },
  flip_worm_segs_vertical__deps: ['$teleportWormCall'], flip_worm_segs_vertical__sig: 'vpii',
  flip_worm_segs_vertical: function(mon,low,high) { teleportWormCall('flip_worm_segs_vertical',mon,low,high); },
  flip_worm_segs_horizontal__deps: ['$teleportWormCall'], flip_worm_segs_horizontal__sig: 'vpii',
  flip_worm_segs_horizontal: function(mon,low,high) { teleportWormCall('flip_worm_segs_horizontal',mon,low,high); },
  redraw_worm__deps: ['$teleportWormCall'], redraw_worm__sig: 'vp',
  redraw_worm: function(mon) { teleportWormCall('redraw_worm',mon); },
  teleport_worm_test_toss__deps: ['$teleportWormCall'], teleport_worm_test_toss__sig: 'vpi',
  teleport_worm_test_toss: function(seg,display) { teleportWormCall('toss_wsegs',seg,display<<24>>24); },
  teleport_worm_test_shrink__deps: ['$teleportWormCall'], teleport_worm_test_shrink__sig: 'vi',
  teleport_worm_test_shrink: function(number) { teleportWormCall('shrink_worm',number); },
  teleport_worm_test_create__deps: ['$teleportWormCall'], teleport_worm_test_create__sig: 'pi',
  teleport_worm_test_create: function(count) { return teleportWormCall('create_worm_tail',count); },
  teleport_worm_test_segment__deps: ['$teleportWormServices'], teleport_worm_test_segment__sig: 'pii',
  teleport_worm_test_segment: function(kind,index) {
    var state = Module['nethackPorted'].wormState(teleportWormServices());
    return (kind === 0 ? state.wheads : state.wtails)[index];
  },
  teleport_worm_test_time__deps: ['$teleportWormServices'], teleport_worm_test_time__sig: 'ji',
  teleport_worm_test_time: function(index) { return Module['nethackPorted'].wormState(teleportWormServices()).wgrowtime[index]; },
  teleport_worm_test_set_time__deps: ['$teleportWormServices'], teleport_worm_test_set_time__sig: 'vij',
  teleport_worm_test_set_time: function(index,value) { Module['nethackPorted'].wormState(teleportWormServices()).wgrowtime[index] = BigInt.asIntN(64,value); },
});
