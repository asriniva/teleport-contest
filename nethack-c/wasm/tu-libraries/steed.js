// Native ABI only; all steed decisions remain in the original JS functions.
addToLibrary({
  $teleportSteedServices__deps: ['teleport_steed_global', 'teleport_steed_equipment', 'teleport_steed_hero_bit', 'teleport_steed_roleplay_deaf', 'teleport_steed_monster_bit', 'teleport_steed_set_monster_bit', 'teleport_steed_object_bit', 'teleport_steed_set_object_bit', 'teleport_steed_class_bit', 'teleport_steed_trap_bit', 'teleport_steed_has_mgivenname', 'teleport_steed_storage', 'teleport_steed_common_string', 'teleport_steed_y_n', 'teleport_steed_rn2', 'teleport_steed_rnd', 'teleport_steed_pline', 'teleport_steed_You', 'teleport_steed_You_cant', 'teleport_steed_Your', 'teleport_steed_impossible0', 'teleport_steed_impossible_position', 'teleport_steed_impossible_state', 'teleport_steed_impossible_overlap', 'teleport_steed_panic', 'teleport_steed_format', 'teleport_steed_literal_storage', 'teleport_steed_literal_capacity', 'y_monnam', 'mon_nam', 'Monnam', 'YMonnam', 'a_monnam', 'strchr', 'u_handsy', 'getdir', 'isok', 'canseemon', 'sensemon', 'which_armor', 'polymon', 'pmname', 'Mgender', 'pronoun_gender', 'an', 'instapetrify', 'exercise', 'objdescr_is', 'remove_worn_item', 'freeinv', 'mksobj', 'fully_identify_obj', 'mpickobj', 'update_mon_extrinsics', 'legs_in_no_shape', 'heal_legs', 'near_capacity', 'poly_when_stoned', 'test_move', 'body_part', 't_at', 'trapname', 'm_unleash', 'hliquid', 'x_monnam', 'losehp', 'steed_vs_stealth', 'teleds', 'use_skill', 'strcpy', 'highc', 'monverbself', 'memset', 'xytodir', 'dirtocoord', 'directionname', 'debugcore', 'accessible', 'dist2', 'sobj_at', 'enexto', 'u_locomotion', 'set_wounded_legs', 'rloc_to', 'rloc', 'has_ceiling', 'is_pool', 'surface', 'killed', 'adjalign', 'is_lava', 'sokoban_guilt', 'mintrap', 'monkilled', 'float_down', 'encumber_msg', 'finish_meating', 'strsubst', 'describe_level', 'minimal_monnam', 'acurr', 'newsym', 'is_art', '$lengthBytesUTF8', '$stringToUTF8', '$stackAlloc', '$stackSave', '$stackRestore'],
  $teleportSteedServices: function() {
    var state = Module['teleportSteedCache'] ||= { next: 0, strings: new Map() };
    var pointer = value => BigInt(value ? value.address ?? value : 0);
    var long = value => BigInt.asIntN(64,BigInt(value));
    var ulong = value => BigInt.asUintN(64,BigInt(value));
    var byte = value => Number(BigInt.asIntN(8,BigInt(value)));
    var coord = value => Number(BigInt.asIntN(16,BigInt(value)));
    var literal = value => {
      if (state.strings.has(value)) return state.strings.get(value);
      var size = lengthBytesUTF8(value) + 1;
      if (state.next + size > Number(_teleport_steed_literal_capacity())) throw new Error('Review changed steed literal corpus');
      var at = Number(_teleport_steed_literal_storage()) + state.next;
      stringToUTF8(value,at,size); state.next += size; state.strings.set(value,at); return at;
    };
    var text = value => typeof value === 'string' ? BigInt(literal(value)) : pointer(value);
    var callers = ['use_saddle','mount_steed','kick_steed','landing_spot','dismount_steed','maybewakesteed'];
    var callerIndex = value => {
      var index = typeof value === 'string' ? callers.indexOf(value) : value;
      if (!Number.isInteger(index) || index < 0 || index >= callers.length) throw new Error('Unexpected original steed RNG caller');
      return index;
    };
    var services = {
      moduleKey: Module, heap: () => HEAPU8, literal,
      stackAlloc: size => Number(stackAlloc(size)), stackSave: () => stackSave(), stackRestore: saved => stackRestore(saved),
      global: index => Number(_teleport_steed_global(index)), equipment: index => Number(_teleport_steed_equipment(index)),
      storage: () => Number(_teleport_steed_storage()),
      heroBit: index => _teleport_steed_hero_bit(index), roleplayDeaf: () => _teleport_steed_roleplay_deaf(),
      monsterBit: (mon,index) => _teleport_steed_monster_bit(pointer(mon),index),
      setMonsterBit: (mon,index,value) => _teleport_steed_set_monster_bit(pointer(mon),index,Number(value)>>>0),
      objectBit: (obj,index) => _teleport_steed_object_bit(pointer(obj),index),
      setObjectBit: (obj,index,value) => _teleport_steed_set_object_bit(pointer(obj),index,Number(value)>>>0),
      objectClassBit: (obj,index) => _teleport_steed_class_bit(pointer(obj),index),
      trapBit: (trap,index) => _teleport_steed_trap_bit(pointer(trap),index),
      hasMgivenname: mon => _teleport_steed_has_mgivenname(pointer(mon)),
      commonString: index => Number(_teleport_steed_common_string(index)), y_n: query => _teleport_steed_y_n(text(query)),
      rn2: (bound,line,caller) => _teleport_steed_rn2(bound,line,callerIndex(caller)),
      rnd: (bound,line,caller) => _teleport_steed_rnd(bound,line,callerIndex(caller)),
      panic: format => _teleport_steed_panic(text(format)),
      Sprintf: (out,format,value) => _teleport_steed_format(pointer(out),text(format),text(value)),
      impossible: (format,...args) => {
        if (!args.length) return _teleport_steed_impossible0(text(format));
        if (args.length === 3) return _teleport_steed_impossible_state(text(format),text(args[0]),ulong(args[1]),text(args[2]));
        if (args.length === 5) return _teleport_steed_impossible_position(text(format),text(args[0]),args[1],args[2],ulong(args[3]),text(args[4]));
        return _teleport_steed_impossible_overlap(text(format),text(args[0]),text(args[1]),args[2],args[3],ulong(args[4]),ulong(args[5]),text(args[6]));
      },
      y_monnam: (mon) => Number(_y_monnam(pointer(mon))),
      mon_nam: (mon) => Number(_mon_nam(pointer(mon))),
      Monnam: (mon) => Number(_Monnam(pointer(mon))),
      YMonnam: (mon) => Number(_YMonnam(pointer(mon))),
      a_monnam: (mon) => Number(_a_monnam(pointer(mon))),
      strchr: (string,ch) => Number(_strchr(text(string), ch)),
      u_handsy: () => _u_handsy(),
      getdir: (prompt) => _getdir(text(prompt)),
      isok: (x,y) => _isok(coord(x),coord(y)),
      canseemon: (mon) => _canseemon(pointer(mon)),
      sensemon: (mon) => _sensemon(pointer(mon)),
      which_armor: (mon,mask) => Number(_which_armor(pointer(mon),long(mask))),
      polymon: (index) => _polymon(index),
      pmname: (pm,gender) => Number(_pmname(pointer(pm),gender)),
      Mgender: (mon) => _Mgender(pointer(mon)),
      pronoun_gender: (mon,flags) => _pronoun_gender(pointer(mon),flags>>>0),
      an: (name) => Number(_an(text(name))),
      instapetrify: (reason) => _instapetrify(text(reason)),
      exercise: (attr,flag) => _exercise(attr,byte(flag)),
      objdescr_is: (obj,name) => _objdescr_is(pointer(obj),text(name)),
      remove_worn_item: (obj,unchain) => _remove_worn_item(pointer(obj),byte(unchain)),
      freeinv: (obj) => _freeinv(pointer(obj)),
      mksobj: (type,init,artifact) => Number(_mksobj(type,byte(init),byte(artifact))),
      fully_identify_obj: (obj) => _fully_identify_obj(pointer(obj)),
      mpickobj: (mon,obj) => _mpickobj(pointer(mon),pointer(obj)),
      update_mon_extrinsics: (mon,obj,on,silently) => _update_mon_extrinsics(pointer(mon),pointer(obj),byte(on),byte(silently)),
      legs_in_no_shape: (activity,ancient) => _legs_in_no_shape(text(activity),byte(ancient)),
      heal_legs: (how) => _heal_legs(how),
      near_capacity: () => _near_capacity(),
      poly_when_stoned: (pm) => _poly_when_stoned(pointer(pm)),
      test_move: (x,y,dx,dy,mode) => _test_move(coord(x),coord(y),coord(dx),coord(dy),mode),
      body_part: (part) => Number(_body_part(part)),
      t_at: (x,y) => Number(_t_at(coord(x),coord(y))),
      trapname: (type,article) => Number(_trapname(type,byte(article))),
      m_unleash: (mon,feedback) => _m_unleash(pointer(mon),byte(feedback)),
      hliquid: (name) => Number(_hliquid(text(name))),
      x_monnam: (mon,article,adjective,suppress,called) => Number(_x_monnam(pointer(mon),article,text(adjective),suppress,byte(called))),
      losehp: (amount,reason,format) => _losehp(amount,text(reason),byte(format)),
      steed_vs_stealth: () => _steed_vs_stealth(),
      teleds: (x,y,flags) => _teleds(coord(x),coord(y),flags),
      use_skill: (skill,count) => _use_skill(skill,count),
      strcpy: (out,src) => Number(_strcpy(pointer(out),text(src))),
      highc: (ch) => _highc(byte(ch)),
      monverbself: (mon,out,verb,other) => Number(_monverbself(pointer(mon),pointer(out),text(verb),text(other))),
      memset: (out,value,size) => Number(_memset(pointer(out),value,BigInt(size))),
      xytodir: (x,y) => _xytodir(x,y),
      dirtocoord: (out,dir) => _dirtocoord(pointer(out),dir),
      directionname: (dir) => Number(_directionname(dir)),
      debugcore: (file,flag) => _debugcore(text(file),byte(flag)),
      accessible: (x,y) => _accessible(coord(x),coord(y)),
      dist2: (x,y,xx,yy) => _dist2(coord(x),coord(y),coord(xx),coord(yy)),
      sobj_at: (type,x,y) => Number(_sobj_at(type,coord(x),coord(y))),
      enexto: (out,x,y,pm) => _enexto(pointer(out),coord(x),coord(y),pointer(pm)),
      u_locomotion: (verb) => Number(_u_locomotion(text(verb))),
      set_wounded_legs: (side,turns) => _set_wounded_legs(long(side),Number(BigInt.asIntN(32,BigInt(turns)))),
      rloc_to: (mon,x,y) => _rloc_to(pointer(mon),coord(x),coord(y)),
      rloc: (mon,flags) => _rloc(pointer(mon),flags>>>0),
      has_ceiling: (level) => _has_ceiling(pointer(level)),
      is_pool: (x,y) => _is_pool(coord(x),coord(y)),
      surface: (x,y) => Number(_surface(coord(x),coord(y))),
      killed: (mon) => _killed(pointer(mon)),
      adjalign: (delta) => _adjalign(delta),
      is_lava: (x,y) => _is_lava(coord(x),coord(y)),
      sokoban_guilt: () => _sokoban_guilt(),
      mintrap: (mon,flags) => _mintrap(pointer(mon),flags>>>0),
      monkilled: (mon,reason,type) => _monkilled(pointer(mon),text(reason),type),
      float_down: (intrinsic,extrinsic) => _float_down(long(intrinsic),long(extrinsic)),
      encumber_msg: () => _encumber_msg(),
      finish_meating: (mon) => _finish_meating(pointer(mon)),
      strsubst: (out,old,replacement) => _strsubst(pointer(out),text(old),text(replacement)),
      describe_level: (out,flags) => _describe_level(pointer(out),flags),
      minimal_monnam: (mon,accurate) => Number(_minimal_monnam(pointer(mon),byte(accurate))),
      is_art: (obj,artifact) => _is_art(pointer(obj),artifact),
      acurr: (attr) => _acurr(attr),
      newsym: (x,y) => _newsym(coord(x),coord(y)),
      pline: (format,...args) => _teleport_steed_pline(text(format),text(args[0]),text(args[1]),text(args[2])),
      You: (format,...args) => _teleport_steed_You(text(format),text(args[0]),text(args[1]),text(args[2])),
      You_cant: (format,...args) => _teleport_steed_You_cant(text(format),text(args[0]),text(args[1]),text(args[2])),
      Your: (format,...args) => _teleport_steed_Your(text(format),text(args[0]),text(args[1]),text(args[2])),
    };
    services.Strcpy = services.strcpy;
    return services;
  },
  $teleportSteedCall__deps: ['$teleportSteedServices','$stackSave','$stackRestore'],
  $teleportSteedCall: function(name,...args) {
    var saved = stackSave();
    try { return Module['nethackPorted'].steed(teleportSteedServices(),name,...args); }
    finally { stackRestore(saved); }
  },
  rider_cant_reach__deps: ['$teleportSteedCall'], rider_cant_reach__sig: 'v',
  rider_cant_reach: function() { teleportSteedCall('rider_cant_reach'); },
  can_saddle__deps: ['$teleportSteedCall'], can_saddle__sig: 'ip',
  can_saddle: function(mon) { return teleportSteedCall('can_saddle',mon); },
  use_saddle__deps: ['$teleportSteedCall'], use_saddle__sig: 'ip',
  use_saddle: function(obj) { return teleportSteedCall('use_saddle',obj); },
  put_saddle_on_mon__deps: ['$teleportSteedCall'], put_saddle_on_mon__sig: 'vpp',
  put_saddle_on_mon: function(obj,mon) { teleportSteedCall('put_saddle_on_mon',obj,mon); },
  can_ride__deps: ['$teleportSteedCall'], can_ride__sig: 'ip',
  can_ride: function(mon) { return teleportSteedCall('can_ride',mon); },
  doride__deps: ['$teleportSteedCall'], doride__sig: 'i',
  doride: function() { return teleportSteedCall('doride'); },
  mount_steed__deps: ['$teleportSteedCall'], mount_steed__sig: 'ipi',
  mount_steed: function(mon,force) { return teleportSteedCall('mount_steed',mon,force<<24>>24); },
  exercise_steed__deps: ['$teleportSteedCall'], exercise_steed__sig: 'v',
  exercise_steed: function() { teleportSteedCall('exercise_steed'); },
  kick_steed__deps: ['$teleportSteedCall'], kick_steed__sig: 'v',
  kick_steed: function() { teleportSteedCall('kick_steed'); },
  dismount_steed__deps: ['$teleportSteedCall'], dismount_steed__sig: 'vi',
  dismount_steed: function(reason) { teleportSteedCall('dismount_steed',reason); },
  poly_steed__deps: ['$teleportSteedCall'], poly_steed__sig: 'vpp',
  poly_steed: function(mon,old) { teleportSteedCall('poly_steed',mon,old); },
  stucksteed__deps: ['$teleportSteedCall'], stucksteed__sig: 'ii',
  stucksteed: function(feeding) { return teleportSteedCall('stucksteed',feeding<<24>>24); },
  place_monster__deps: ['$teleportSteedCall'], place_monster__sig: 'vpii',
  place_monster: function(mon,x,y) { teleportSteedCall('place_monster',mon,x<<16>>16,y<<16>>16); },
  teleport_steed_test_landing__deps: ['$teleportSteedCall'], teleport_steed_test_landing__sig: 'ipii',
  teleport_steed_test_landing: function(spot,reason,force) { return teleportSteedCall('landing_spot',spot,reason,force); },
  teleport_steed_test_wake__deps: ['$teleportSteedCall'], teleport_steed_test_wake__sig: 'vp',
  teleport_steed_test_wake: function(mon) { teleportSteedCall('maybewakesteed',mon); },
});
