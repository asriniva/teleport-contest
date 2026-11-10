// Native ABI only; all lock algorithms remain in the original JS functions.
addToLibrary({
  $teleportLockServices__deps: ['teleport_lock_global', 'teleport_lock_equipment', 'teleport_lock_roleplay_deaf', 'teleport_lock_hero_bit', 'teleport_lock_object_bit', 'teleport_lock_set_object_bit', 'teleport_lock_monster_bit', 'teleport_lock_object_class_bit', 'teleport_lock_terrain_bit', 'teleport_lock_set_terrain_bit', 'teleport_lock_context_bit', 'teleport_lock_set_context_bit', 'teleport_lock_callback_pointer', 'teleport_lock_get_occupation', 'teleport_lock_set_occupation_pointer', 'teleport_lock_set_occupation', 'teleport_lock_command_pointer', 'teleport_lock_cmdq_add_ec', 'teleport_lock_safe_qbuf', 'teleport_lock_singular', 'teleport_lock_common_string', 'teleport_lock_y_n', 'teleport_lock_ynq', 'teleport_lock_rn2', 'teleport_lock_rnl', 'teleport_lock_pline', 'teleport_lock_You', 'teleport_lock_You_cant', 'teleport_lock_You_hear', 'teleport_lock_There', 'teleport_lock_pline_The', 'teleport_lock_verbalize', 'teleport_lock_you_money', 'teleport_lock_impossible', 'teleport_lock_format', 'teleport_lock_literal_storage', 'teleport_lock_literal_capacity', 'is_magic_key', 'is_quest_artifact', 'exercise', 'b_trapped', 'unblock_point', 'block_point', 'recalc_block_point', 'in_rooms', 'add_damage', 'newsym', 'feel_newsym', 'feel_location', 'chest_trap', 'costly_alteration', 'costly_spot', 'shop_keeper', 'xname', 'obj_extract_self', 'stolen_value', 'obfree', 'useup', 'start_corpse_timeout', 'place_object', 'stackobj', 'currency', 'delobj', 'obj_resists', 'wake_nearby', 'can_reach_floor', 'doname', 'mon_nam', 'yname', 'ysimple_name', 'ansimpleoname', 'get_adjacent_loc', 'is_lava', 'is_pool', 'hliquid', 'could_untrap', 'untrap', 'an', 'An', 'the', 'simple_typename', 'touch_artifact', 'canseemon', 'sensemon', 'stumble_onto_mimic', 'maybe_absorb_item', 'update_mapseen_for', 'is_drawbridge_wall', 'cant_reach_floor', 'getdir', 'closed_door', 'container_at', 'doloot', 'is_db_wall', 'set_msg_xy', 'cmdq_add_dir', 'sgn', 'Some_Monnam', 's_suffix', 'strcat', 'map_invisible', 'isok', 't_at', 'mb_trapped', 'vision_recalc', 'wake_nearto', 'stop_occupation', 'bottlename', 'potionbreathe', 'acurr', 'acurrstr', 'unconscious', 'is_fainted', 'on_level', 'dist2', '$lengthBytesUTF8', '$stringToUTF8', '$stackAlloc', '$stackSave', '$stackRestore'],
  $teleportLockServices: function() {
    var state = Module['teleportLockCache'] ||= { next: 0, strings: new Map() };
    var pointer = value => BigInt(value ? value.address ?? value : 0);
    var byte = value => Number(BigInt.asIntN(8, BigInt(value)));
    var coord = value => Number(BigInt.asIntN(16, BigInt(value)));
    var literal = value => {
      if (state.strings.has(value)) return state.strings.get(value);
      var size = lengthBytesUTF8(value) + 1;
      if (state.next + size > Number(_teleport_lock_literal_capacity())) throw new Error('Review changed lock literal corpus');
      var at = Number(_teleport_lock_literal_storage()) + state.next;
      stringToUTF8(value, at, size); state.next += size; state.strings.set(value, at); return at;
    };
    var text = value => typeof value === 'string' ? BigInt(literal(value)) : pointer(value);
    var callers = ['picklock','breakchestlock','forcelock','doopen_indir','doclose'];
    var callerIndex = value => {
      var index = typeof value === 'string' ? callers.indexOf(value) : value;
      if (!Number.isInteger(index) || index < 0 || index >= callers.length) throw new Error('Unexpected original lock RNG caller');
      return index;
    };
    var services = {
      heap: () => HEAPU8, literal,
      stackAlloc: size => Number(stackAlloc(size)), stackSave: () => stackSave(), stackRestore: saved => stackRestore(saved),
      global: index => Number(_teleport_lock_global(index)), equipment: () => Number(_teleport_lock_equipment()),
      roleplayDeaf: () => _teleport_lock_roleplay_deaf(), heroBit: index => _teleport_lock_hero_bit(index),
      objectBit: (obj,index) => _teleport_lock_object_bit(pointer(obj),index),
      setObjectBit: (obj,index,value) => _teleport_lock_set_object_bit(pointer(obj),index,Number(value)>>>0),
      monsterBit: (mon,index) => _teleport_lock_monster_bit(pointer(mon),index),
      objectClassBit: (obj,index) => _teleport_lock_object_class_bit(pointer(obj),index),
      terrainBit: (x,y,index) => _teleport_lock_terrain_bit(coord(x),coord(y),index),
      setTerrainBit: (x,y,index,value) => _teleport_lock_set_terrain_bit(coord(x),coord(y),index,Number(value)>>>0),
      contextBit: index => _teleport_lock_context_bit(index), setContextBit: (index,value) => _teleport_lock_set_context_bit(index,byte(value)),
      callbackPointer: index => _teleport_lock_callback_pointer(index),
      getOccupation: () => _teleport_lock_get_occupation(), setOccupation: value => _teleport_lock_set_occupation_pointer(pointer(value)),
      set_occupation: (callback,action,count) => _teleport_lock_set_occupation(pointer(callback),text(action),BigInt.asIntN(64,BigInt(count))),
      commandPointer: () => _teleport_lock_command_pointer(), cmdq_add_ec: (queue,command) => _teleport_lock_cmdq_add_ec(queue,pointer(command)),
      commonString: index => Number(_teleport_lock_common_string(index)),
      y_n: query => _teleport_lock_y_n(text(query)), ynq: query => _teleport_lock_ynq(text(query)),
      rn2: (bound,line,caller) => _teleport_lock_rn2(bound,line,callerIndex(caller)), rnl: (bound,line,caller) => _teleport_lock_rnl(bound,line,callerIndex(caller)),
      impossible: (format,value) => _teleport_lock_impossible(text(format),value),
      Sprintf: (out,format,...args) => _teleport_lock_format(pointer(out),text(format),text(args[0]),text(args[1]),text(args[2])),
      singular: (obj,callback) => {
        if (callback !== services.xname) throw new Error('Unexpected original lock singular callback');
        return Number(_teleport_lock_singular(pointer(obj)));
      },
      safe_qbuf: (out,prefix,suffix,obj,name,alternate,last) => {
        var pair;
        if (name === services.yname && alternate === services.ysimple_name) pair = 0;
        else if (name === services.doname && alternate === services.ansimpleoname) pair = 1;
        else throw new Error('Unexpected original lock prompt callbacks');
        return Number(_teleport_lock_safe_qbuf(pointer(out),text(prefix),text(suffix),pointer(obj),pair,text(last)));
      },
      is_magic_key: (mon,obj) => _is_magic_key(pointer(mon), pointer(obj)),
      is_quest_artifact: (obj) => _is_quest_artifact(pointer(obj)),
      exercise: (attr,flag) => _exercise(attr, byte(flag)),
      b_trapped: (name,part) => _b_trapped(text(name), part),
      unblock_point: (x,y) => _unblock_point(coord(x), coord(y)),
      block_point: (x,y) => _block_point(coord(x), coord(y)),
      recalc_block_point: (x,y) => _recalc_block_point(coord(x), coord(y)),
      in_rooms: (x,y,type) => Number(_in_rooms(coord(x), coord(y), type)),
      add_damage: (x,y,cost) => _add_damage(coord(x), coord(y), BigInt.asIntN(64,BigInt(cost))),
      newsym: (x,y) => _newsym(coord(x), coord(y)),
      feel_newsym: (x,y) => _feel_newsym(coord(x), coord(y)),
      feel_location: (x,y) => _feel_location(coord(x), coord(y)),
      chest_trap: (obj,part,disarm) => _chest_trap(pointer(obj), part, byte(disarm)),
      costly_alteration: (obj,kind) => _costly_alteration(pointer(obj), kind),
      costly_spot: (x,y) => _costly_spot(coord(x), coord(y)),
      shop_keeper: (room) => Number(_shop_keeper(byte(room))),
      xname: (obj) => Number(_xname(pointer(obj))),
      obj_extract_self: (obj) => _obj_extract_self(pointer(obj)),
      stolen_value: (obj,x,y,peaceful,silent) => _stolen_value(pointer(obj), coord(x), coord(y), byte(peaceful), byte(silent)),
      obfree: (obj,merge) => _obfree(pointer(obj), pointer(merge)),
      useup: (obj) => _useup(pointer(obj)),
      start_corpse_timeout: (obj) => _start_corpse_timeout(pointer(obj)),
      place_object: (obj,x,y) => _place_object(pointer(obj), coord(x), coord(y)),
      stackobj: (obj) => _stackobj(pointer(obj)),
      currency: (amount) => Number(_currency(BigInt.asIntN(64,BigInt(amount)))),
      delobj: (obj) => _delobj(pointer(obj)),
      obj_resists: (obj,usual,artifact) => _obj_resists(pointer(obj), usual, artifact),
      wake_nearby: (viaattack) => _wake_nearby(byte(viaattack)),
      can_reach_floor: (check) => _can_reach_floor(byte(check)),
      doname: (obj) => Number(_doname(pointer(obj))),
      mon_nam: (mon) => Number(_mon_nam(pointer(mon))),
      yname: (obj) => Number(_yname(pointer(obj))),
      ysimple_name: (obj) => Number(_ysimple_name(pointer(obj))),
      ansimpleoname: (obj) => Number(_ansimpleoname(pointer(obj))),
      get_adjacent_loc: (prompt,error,x,y,out) => _get_adjacent_loc(text(prompt), text(error), coord(x), coord(y), pointer(out)),
      is_lava: (x,y) => _is_lava(coord(x), coord(y)),
      is_pool: (x,y) => _is_pool(coord(x), coord(y)),
      hliquid: (name) => Number(_hliquid(text(name))),
      could_untrap: (disarming,container) => _could_untrap(byte(disarming), byte(container)),
      untrap: (force,x,y,obj) => _untrap(byte(force), coord(x), coord(y), pointer(obj)),
      an: (name) => Number(_an(text(name))),
      An: (name) => Number(_An(text(name))),
      the: (name) => Number(_the(text(name))),
      simple_typename: (type) => Number(_simple_typename(type)),
      touch_artifact: (obj,mon) => _touch_artifact(pointer(obj), pointer(mon)),
      canseemon: (mon) => _canseemon(pointer(mon)),
      sensemon: (mon) => _sensemon(pointer(mon)),
      stumble_onto_mimic: (mon) => _stumble_onto_mimic(pointer(mon)),
      maybe_absorb_item: (mon,obj,chance,artifact) => _maybe_absorb_item(pointer(mon), pointer(obj), chance, artifact),
      update_mapseen_for: (x,y) => _update_mapseen_for(coord(x), coord(y)),
      is_drawbridge_wall: (x,y) => _is_drawbridge_wall(coord(x), coord(y)),
      cant_reach_floor: (x,y,check,pit,pool) => _cant_reach_floor(coord(x), coord(y), byte(check), byte(pit), byte(pool)),
      getdir: (prompt) => _getdir(text(prompt)),
      closed_door: (x,y) => _closed_door(coord(x), coord(y)),
      container_at: (x,y,check) => _container_at(coord(x), coord(y), byte(check)),
      doloot: () => _doloot(),
      is_db_wall: (x,y) => _is_db_wall(coord(x), coord(y)),
      set_msg_xy: (x,y) => _set_msg_xy(coord(x), coord(y)),
      cmdq_add_dir: (queue,x,y,z) => _cmdq_add_dir(queue, byte(x), byte(y), byte(z)),
      sgn: (value) => _sgn(value),
      Some_Monnam: (mon) => Number(_Some_Monnam(pointer(mon))),
      s_suffix: (name) => Number(_s_suffix(text(name))),
      strcat: (out,tail) => Number(_strcat(pointer(out), text(tail))),
      map_invisible: (x,y) => _map_invisible(coord(x), coord(y)),
      isok: (x,y) => _isok(coord(x), coord(y)),
      t_at: (x,y) => Number(_t_at(coord(x), coord(y))),
      mb_trapped: (mon,visible) => _mb_trapped(pointer(mon), byte(visible)),
      vision_recalc: (control) => _vision_recalc(control),
      wake_nearto: (x,y,distance) => _wake_nearto(coord(x), coord(y), distance),
      stop_occupation: () => _stop_occupation(),
      bottlename: () => Number(_bottlename()),
      potionbreathe: (obj) => _potionbreathe(pointer(obj)),
      acurr: (attr) => _acurr(attr),
      acurrstr: () => _acurrstr(),
      unconscious: () => _unconscious(),
      is_fainted: () => _is_fainted(),
      on_level: (a,b) => _on_level(pointer(a), pointer(b)),
      dist2: (x,y,xx,yy) => _dist2(coord(x), coord(y), coord(xx), coord(yy)),
      pline: (format,...args) => _teleport_lock_pline(text(format),text(args[0]),text(args[1]),text(args[2])),
      You: (format,...args) => typeof args[0] === 'bigint' ? _teleport_lock_you_money(text(format),BigInt.asIntN(64,args[0]),text(args[1])) : _teleport_lock_You(text(format),text(args[0]),text(args[1]),text(args[2])),
      You_cant: (format,...args) => _teleport_lock_You_cant(text(format),text(args[0]),text(args[1]),text(args[2])),
      You_hear: (format,...args) => _teleport_lock_You_hear(text(format),text(args[0]),text(args[1]),text(args[2])),
      There: (format,...args) => _teleport_lock_There(text(format),text(args[0]),text(args[1]),text(args[2])),
      pline_The: (format,...args) => _teleport_lock_pline_The(text(format),text(args[0]),text(args[1]),text(args[2])),
      verbalize: (format,...args) => _teleport_lock_verbalize(text(format),text(args[0]),text(args[1]),text(args[2])),
    };
    return services;
  },
  $teleportLockCall__deps: ['$teleportLockServices', '$stackSave', '$stackRestore'],
  $teleportLockCall: function(name,...args) {
    var saved = stackSave();
    try { return Module['nethackPorted'].lock(teleportLockServices(),name,...args); }
    finally { stackRestore(saved); }
  },
  picking_lock__deps: ['$teleportLockCall'], picking_lock__sig: 'ipp',
  picking_lock: function(x,y) { return teleportLockCall('picking_lock',x,y); },
  picking_at__deps: ['$teleportLockCall'], picking_at__sig: 'iii',
  picking_at: function(x,y) { return teleportLockCall('picking_at',x<<16>>16,y<<16>>16); },
  breakchestlock__deps: ['$teleportLockCall'], breakchestlock__sig: 'vpi',
  breakchestlock: function(box,destroy) { teleportLockCall('breakchestlock',box,destroy<<24>>24); },
  reset_pick__deps: ['$teleportLockCall'], reset_pick__sig: 'v',
  reset_pick: function() { teleportLockCall('reset_pick'); },
  maybe_reset_pick__deps: ['$teleportLockCall'], maybe_reset_pick__sig: 'vp',
  maybe_reset_pick: function(obj) { teleportLockCall('maybe_reset_pick',obj); },
  autokey__deps: ['$teleportLockCall'], autokey__sig: 'pi',
  autokey: function(opening) { return teleportLockCall('autokey',opening<<24>>24); },
  pick_lock__deps: ['$teleportLockCall'], pick_lock__sig: 'ipiip',
  pick_lock: function(pick,x,y,container) { return teleportLockCall('pick_lock',pick,x<<16>>16,y<<16>>16,container); },
  u_have_forceable_weapon__deps: ['$teleportLockCall'], u_have_forceable_weapon__sig: 'i',
  u_have_forceable_weapon: function() { return teleportLockCall('u_have_forceable_weapon'); },
  doforce__deps: ['$teleportLockCall'], doforce__sig: 'i',
  doforce: function() { return teleportLockCall('doforce'); },
  stumble_on_door_mimic__deps: ['$teleportLockCall'], stumble_on_door_mimic__sig: 'iii',
  stumble_on_door_mimic: function(x,y) { return teleportLockCall('stumble_on_door_mimic',x<<16>>16,y<<16>>16); },
  doopen__deps: ['$teleportLockCall'], doopen__sig: 'i',
  doopen: function() { return teleportLockCall('doopen'); },
  doopen_indir__deps: ['$teleportLockCall'], doopen_indir__sig: 'iii',
  doopen_indir: function(x,y) { return teleportLockCall('doopen_indir',x<<16>>16,y<<16>>16); },
  doclose__deps: ['$teleportLockCall'], doclose__sig: 'i',
  doclose: function() { return teleportLockCall('doclose'); },
  boxlock__deps: ['$teleportLockCall'], boxlock__sig: 'ipp',
  boxlock: function(box,spell) { return teleportLockCall('boxlock',box,spell); },
  doorlock__deps: ['$teleportLockCall'], doorlock__sig: 'ipii',
  doorlock: function(spell,x,y) { return teleportLockCall('doorlock',spell,x<<16>>16,y<<16>>16); },
  teleport_lock_callback_pick__deps: ['$teleportLockCall'], teleport_lock_callback_pick__sig: 'i',
  teleport_lock_callback_pick: function() { return teleportLockCall('picklock'); },
  teleport_lock_callback_force__deps: ['$teleportLockCall'], teleport_lock_callback_force__sig: 'i',
  teleport_lock_callback_force: function() { return teleportLockCall('forcelock'); },
  teleport_lock_test_action__deps: ['$teleportLockCall'], teleport_lock_test_action__sig: 'p',
  teleport_lock_test_action: function() { return teleportLockCall('lock_action'); },
  teleport_lock_test_pick__deps: ['$teleportLockCall'], teleport_lock_test_pick__sig: 'i',
  teleport_lock_test_pick: function() { return teleportLockCall('picklock'); },
  teleport_lock_test_force__deps: ['$teleportLockCall'], teleport_lock_test_force__sig: 'i',
  teleport_lock_test_force: function() { return teleportLockCall('forcelock'); },
  teleport_lock_test_obstructed__deps: ['$teleportLockCall'], teleport_lock_test_obstructed__sig: 'iiii',
  teleport_lock_test_obstructed: function(x,y,quiet) { return teleportLockCall('obstructed',x<<16>>16,y<<16>>16,quiet<<24>>24); },
  teleport_lock_test_shatter__deps: ['$teleportLockCall'], teleport_lock_test_shatter__sig: 'vp',
  teleport_lock_test_shatter: function(obj) { teleportLockCall('chest_shatter_msg',obj); },
});
