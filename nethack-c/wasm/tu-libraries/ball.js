// Native ABI only; ball-and-chain policy and private state stay JavaScript.
addToLibrary({
  $teleportBallServices__deps: ['teleport_ball_global', 'teleport_ball_equipment', 'teleport_ball_hero_bit', 'teleport_ball_terrain_bit', 'teleport_ball_trap_bit', 'teleport_ball_set_trap_bit', 'teleport_ball_rn2', 'teleport_ball_rnd', 'teleport_ball_pline', 'teleport_ball_pline_The', 'teleport_ball_You', 'teleport_ball_You_feel', 'teleport_ball_Your', 'teleport_ball_impossible0', 'teleport_ball_impossible_strings', 'teleport_ball_impossible_worn', 'teleport_ball_impossible_coords', 'teleport_ball_format', 'teleport_ball_literal_storage', 'teleport_ball_literal_capacity', 'welded', 'setuwep', 'setuswapwep', 'setuqwep', 'freeinv', 'encumber_msg', 'body_part', 'hard_helmet', 'Yname2', 'losehp', 'flooreffects', 'place_object', 'newsym', 'obj_extract_self', 'maybe_unhide_at', 'remove_object', 'movobj', 'map_object', 'dist2', 'distmin', 'near_capacity', 'nomul', 'is_pool', 't_at', 'find_mac', 'omon_adj', 'hmon', 'miss', 'xname', 'spoteffects', 'deltrap', 'hliquid', 'set_wounded_legs', 'reset_utrap', 'fill_pit', 'weight_cap', 'canletgo', 'yname', 'otense', 'setnotworn', 'hitfloor', 'cls', 'exercise', 'safe_typename', 'on_level', 'paniclog', '$lengthBytesUTF8', '$stringToUTF8', '$stackAlloc', '$stackSave', '$stackRestore'],
  $teleportBallServices: function() {
    var state = Module['teleportBallCache'] ||= { next: 0, strings: new Map() };
    var pointer = value => BigInt(value ? value.address ?? value : 0);
    var byte = value => Number(BigInt.asIntN(8,BigInt(value)));
    var coord = value => Number(BigInt.asIntN(16,BigInt(value)));
    var literal = value => {
      if (state.strings.has(value)) return state.strings.get(value);
      var size = lengthBytesUTF8(value) + 1;
      if (state.next + size > Number(_teleport_ball_literal_capacity())) throw new Error('Review changed ball literal corpus');
      var at = Number(_teleport_ball_literal_storage()) + state.next;
      stringToUTF8(value,at,size); state.next += size; state.strings.set(value,at); return at;
    };
    var text = value => typeof value === 'string' ? BigInt(literal(value)) : pointer(value);
    var callers = ['ballfall','unplacebc_and_covet_placebc','drag_ball','drop_ball','litter','drag_down'];
    var callerIndex = value => {
      var index = typeof value === 'string' ? callers.indexOf(value) : value;
      if (!Number.isInteger(index) || index < 0 || index >= callers.length) throw new Error('Unexpected original ball RNG caller');
      return index;
    };
    var services = {
      moduleKey: Module, heap: () => HEAPU8, literal,
      stackAlloc: size => Number(stackAlloc(size)), stackSave: () => stackSave(), stackRestore: saved => stackRestore(saved),
      global: index => Number(_teleport_ball_global(index)), equipment: index => Number(_teleport_ball_equipment(index)),
      heroBit: index => _teleport_ball_hero_bit(index),
      terrainBit: (x,y,index) => _teleport_ball_terrain_bit(coord(x),coord(y),index),
      trapBit: (trap,index) => _teleport_ball_trap_bit(pointer(trap),index),
      setTrapBit: (trap,index,value) => _teleport_ball_set_trap_bit(pointer(trap),index,Number(value)>>>0),
      rn2: (bound,line,caller) => _teleport_ball_rn2(bound,line,callerIndex(caller)),
      rnd: (bound,line,caller) => _teleport_ball_rnd(bound,line,callerIndex(caller)),
      impossible: (format,...args) => {
        if (!args.length) return _teleport_ball_impossible0(text(format));
        if (args.length === 3) return _teleport_ball_impossible_strings(text(format),text(args[0]),text(args[1]),text(args[2]));
        if (args.length === 4) return _teleport_ball_impossible_worn(text(format),args[0],text(args[1]),args[2],BigInt.asUintN(64,BigInt(args[3])));
        return _teleport_ball_impossible_coords(text(format),args[0],args[1],args[2],args[3],args[4],args[5]);
      },
      Sprintf: (out,format,value) => _teleport_ball_format(pointer(out),text(format),text(value)),
      welded: (obj) => _welded(pointer(obj)),
      setuwep: (obj) => _setuwep(pointer(obj)),
      setuswapwep: (obj) => _setuswapwep(pointer(obj)),
      setuqwep: (obj) => _setuqwep(pointer(obj)),
      freeinv: (obj) => _freeinv(pointer(obj)),
      encumber_msg: () => _encumber_msg(),
      body_part: (part) => Number(_body_part(part)),
      hard_helmet: (obj) => _hard_helmet(pointer(obj)),
      Yname2: (obj) => Number(_Yname2(pointer(obj))),
      losehp: (damage,reason,format) => _losehp(Number(BigInt.asIntN(32,BigInt(damage))),text(reason),byte(format)),
      flooreffects: (obj,x,y,verb) => _flooreffects(pointer(obj),coord(x),coord(y),text(verb)),
      place_object: (obj,x,y) => _place_object(pointer(obj),coord(x),coord(y)),
      newsym: (x,y) => _newsym(coord(x),coord(y)),
      obj_extract_self: (obj) => _obj_extract_self(pointer(obj)),
      maybe_unhide_at: (x,y) => _maybe_unhide_at(coord(x),coord(y)),
      remove_object: (obj) => _remove_object(pointer(obj)),
      movobj: (obj,x,y) => _movobj(pointer(obj),coord(x),coord(y)),
      map_object: (obj,flags) => _map_object(pointer(obj),flags),
      dist2: (x,y,xx,yy) => _dist2(coord(x),coord(y),coord(xx),coord(yy)),
      distmin: (x,y,xx,yy) => _distmin(coord(x),coord(y),coord(xx),coord(yy)),
      near_capacity: () => _near_capacity(),
      nomul: (turns) => _nomul(turns),
      is_pool: (x,y) => _is_pool(coord(x),coord(y)),
      t_at: (x,y) => Number(_t_at(coord(x),coord(y))),
      find_mac: (mon) => _find_mac(pointer(mon)),
      omon_adj: (mon,obj,check) => _omon_adj(pointer(mon),pointer(obj),byte(check)),
      hmon: (mon,obj,how,roll) => _hmon(pointer(mon),pointer(obj),how,roll),
      miss: (name,mon) => _miss(text(name),pointer(mon)),
      xname: (obj) => Number(_xname(pointer(obj))),
      spoteffects: (pick) => _spoteffects(byte(pick)),
      deltrap: (trap) => _deltrap(pointer(trap)),
      hliquid: (name) => Number(_hliquid(text(name))),
      set_wounded_legs: (side,turns) => _set_wounded_legs(BigInt.asIntN(64,BigInt(side)),Number(BigInt.asIntN(32,BigInt(turns)))),
      reset_utrap: (message) => _reset_utrap(byte(message)),
      fill_pit: (x,y) => _fill_pit(coord(x),coord(y)),
      weight_cap: () => _weight_cap(),
      canletgo: (obj,message) => _canletgo(pointer(obj),text(message)),
      yname: (obj) => Number(_yname(pointer(obj))),
      otense: (obj,verb) => Number(_otense(pointer(obj),text(verb))),
      setnotworn: (obj) => _setnotworn(pointer(obj)),
      hitfloor: (obj,verbose) => _hitfloor(pointer(obj),byte(verbose)),
      cls: () => _cls(),
      exercise: (attr,positive) => _exercise(attr,byte(positive)),
      safe_typename: (type) => Number(_safe_typename(type)),
      on_level: (a,b) => _on_level(pointer(a),pointer(b)),
      paniclog: (type,reason) => _paniclog(text(type),text(reason)),
      pline: (format,...args) => _teleport_ball_pline(text(format),text(args[0]),text(args[1]),text(args[2])),
      pline_The: (format,...args) => _teleport_ball_pline_The(text(format),text(args[0]),text(args[1]),text(args[2])),
      You: (format,...args) => _teleport_ball_You(text(format),text(args[0]),text(args[1]),text(args[2])),
      You_feel: (format,...args) => _teleport_ball_You_feel(text(format),text(args[0]),text(args[1]),text(args[2])),
      Your: (format,...args) => _teleport_ball_Your(text(format),text(args[0]),text(args[1]),text(args[2])),
    };
    return services;
  },
  $teleportBallCall__deps: ['$teleportBallServices','$stackSave','$stackRestore'],
  $teleportBallCall: function(name,...args) {
    var saved = stackSave();
    try { return Module['nethackPorted'].ball(teleportBallServices(),name,...args); }
    finally { stackRestore(saved); }
  },
  ballrelease__deps: ['$teleportBallCall'], ballrelease__sig: 'vi',
  ballrelease: function(show) { teleportBallCall('ballrelease',show<<24>>24); },
  ballfall__deps: ['$teleportBallCall'], ballfall__sig: 'v',
  ballfall: function() { teleportBallCall('ballfall'); },
  placebc__deps: ['$teleportBallCall'], placebc__sig: 'v',
  placebc: function() { teleportBallCall('placebc'); },
  unplacebc__deps: ['$teleportBallCall'], unplacebc__sig: 'v',
  unplacebc: function() { teleportBallCall('unplacebc'); },
  unplacebc_and_covet_placebc__deps: ['$teleportBallCall'], unplacebc_and_covet_placebc__sig: 'i',
  unplacebc_and_covet_placebc: function() { return teleportBallCall('unplacebc_and_covet_placebc'); },
  lift_covet_and_placebc__deps: ['$teleportBallCall'], lift_covet_and_placebc__sig: 'vi',
  lift_covet_and_placebc: function(pin) { teleportBallCall('lift_covet_and_placebc',pin); },
  set_bc__deps: ['$teleportBallCall'], set_bc__sig: 'vi',
  set_bc: function(blind) { teleportBallCall('set_bc',blind); },
  move_bc__deps: ['$teleportBallCall'], move_bc__sig: 'viiiiii',
  move_bc: function(before,control,bx,by,cx,cy) { teleportBallCall('move_bc',before,control,bx<<16>>16,by<<16>>16,cx<<16>>16,cy<<16>>16); },
  drag_ball__deps: ['$teleportBallCall'], drag_ball__sig: 'iiippppppi',
  drag_ball: function(x,y,control,bx,by,cx,cy,delay,allow) { return teleportBallCall('drag_ball',x<<16>>16,y<<16>>16,control,bx,by,cx,cy,delay,allow<<24>>24); },
  drop_ball__deps: ['$teleportBallCall'], drop_ball__sig: 'vii',
  drop_ball: function(x,y) { teleportBallCall('drop_ball',x<<16>>16,y<<16>>16); },
  drag_down__deps: ['$teleportBallCall'], drag_down__sig: 'v',
  drag_down: function() { teleportBallCall('drag_down'); },
  bc_sanity_check__deps: ['$teleportBallCall'], bc_sanity_check__sig: 'v',
  bc_sanity_check: function() { teleportBallCall('bc_sanity_check'); },
  teleport_ball_test_order__deps: ['$teleportBallCall'], teleport_ball_test_order__sig: 'i',
  teleport_ball_test_order: function() { return teleportBallCall('bc_order'); },
  teleport_ball_test_litter__deps: ['$teleportBallCall'], teleport_ball_test_litter__sig: 'v',
  teleport_ball_test_litter: function() { teleportBallCall('litter'); },
  teleport_ball_test_place__deps: ['$teleportBallCall'], teleport_ball_test_place__sig: 'v',
  teleport_ball_test_place: function() { teleportBallCall('placebc_core'); },
  teleport_ball_test_unplace__deps: ['$teleportBallCall'], teleport_ball_test_unplace__sig: 'v',
  teleport_ball_test_unplace: function() { teleportBallCall('unplacebc_core'); },
  teleport_ball_test_restriction__deps: ['$teleportBallCall'], teleport_ball_test_restriction__sig: 'ii',
  teleport_ball_test_restriction: function(restriction) { return teleportBallCall('check_restriction',restriction); },
  teleport_ball_test_state__deps: ['$teleportBallServices'], teleport_ball_test_state__sig: 'iii',
  teleport_ball_test_state: function(write,value) {
    var state = Module['nethackPorted'].ballState(teleportBallServices());
    if (write) state.bcrestriction = value|0;
    return state.bcrestriction;
  },
});
