// Native ABI only; original wizard policy and private catalogues are JavaScript.
addToLibrary({
  $teleportWizardServices__deps: ['teleport_wizard_global', 'teleport_wizard_equipment', 'teleport_wizard_roleplay_deaf', 'teleport_wizard_hero_bit', 'teleport_wizard_set_hero_bit', 'teleport_wizard_monster_bit', 'teleport_wizard_set_monster_bit', 'teleport_wizard_trap_type', 'teleport_wizard_distant_name', 'teleport_wizard_common_string', 'teleport_wizard_rn2', 'teleport_wizard_rnd', 'teleport_wizard_pline', 'teleport_wizard_You', 'teleport_wizard_You_feel', 'teleport_wizard_verbalize', 'teleport_wizard_literal_storage', 'teleport_wizard_literal_capacity', 'Tobjnam', 'builds_up', 'stairway_find_type_dir', 'inhistemple', 'inhishop', 'expels', 'In_W_tower', 'noteleport_level', 'rloc', 'mnearto', 'rloc_to', 'healmon', 'mnexto', 'monnear', 'isok', 'Monnam', 'doname', 'obj_extract_self', 'mpickobj', 'makemon', 'add_to_minv', 'mksobj', 'newsym', 'big_to_little', 'strrchr', 'strncmp', 'strcmp', 'monster_census', 'msummon', 'sgn', 'enexto', 'attacktype', 'set_malign', 'unmakemon', 'mon_catchup_elapsed_time', 'mon_arrive', 'hcolor', 'rndcurse', 'mon_aligntyp', 'com_pager', 'wake_nearto', 'In_hell', 'on_level', 'dist2', '$lengthBytesUTF8', '$stringToUTF8', '$stackAlloc', '$stackSave', '$stackRestore'],
  $teleportWizardServices: function() {
    var state = Module['teleportWizardCache'] ||= { next: 0, strings: new Map() };
    var pointer = value => BigInt(value ? value.address ?? value : 0);
    var byte = value => Number(BigInt.asIntN(8,BigInt(value)));
    var coord = value => Number(BigInt.asIntN(16,BigInt(value)));
    var long = value => BigInt.asIntN(64,BigInt(value));
    var literal = value => {
      if (state.strings.has(value)) return state.strings.get(value);
      var size = lengthBytesUTF8(value) + 1;
      if (state.next + size > Number(_teleport_wizard_literal_capacity())) throw new Error('Review changed wizard literal corpus');
      var at = Number(_teleport_wizard_literal_storage()) + state.next;
      stringToUTF8(value,at,size); state.next += size; state.strings.set(value,at); return at;
    };
    var text = value => typeof value === 'string' ? BigInt(literal(value)) : pointer(value);
    var callers = ['amulet','tactics','aggravate','clonewiz','pick_nasty','nasty','resurrect','intervene','wizdeadorgone','cuss'];
    var callerIndex = value => {
      var index = typeof value === 'string' ? callers.indexOf(value) : value;
      if (!Number.isInteger(index) || index < 0 || index >= callers.length) throw new Error('Unexpected original wizard RNG caller');
      return index;
    };
    var services = {
      moduleKey: Module, heap: () => HEAPU8, literal,
      stackAlloc: size => Number(stackAlloc(size)), stackSave: () => stackSave(), stackRestore: saved => stackRestore(saved),
      global: index => Number(_teleport_wizard_global(index)), equipment: index => Number(_teleport_wizard_equipment(index)),
      heroBit: index => _teleport_wizard_hero_bit(index), setHeroBit: (index,value) => _teleport_wizard_set_hero_bit(index,Number(value)>>>0),
      monsterBit: (mon,index) => _teleport_wizard_monster_bit(pointer(mon),index),
      setMonsterBit: (mon,index,value) => _teleport_wizard_set_monster_bit(pointer(mon),index,Number(value)>>>0),
      trapType: trap => _teleport_wizard_trap_type(pointer(trap)),
      roleplayDeaf: () => _teleport_wizard_roleplay_deaf(), commonString: index => Number(_teleport_wizard_common_string(index)),
      rn2: (bound,line,caller) => _teleport_wizard_rn2(bound,line,callerIndex(caller)),
      rnd: (bound,line,caller) => _teleport_wizard_rnd(bound,line,callerIndex(caller)),
      distant_name: (obj,callback) => {
        if (callback !== services.doname) throw new Error('Unexpected original wizard naming callback');
        return Number(_teleport_wizard_distant_name(pointer(obj)));
      },
      Tobjnam: (obj,verb) => Number(_Tobjnam(pointer(obj),text(verb))),
      builds_up: (level) => _builds_up(pointer(level)),
      stairway_find_type_dir: (ladder,up) => Number(_stairway_find_type_dir(byte(ladder),byte(up))),
      inhistemple: (mon) => _inhistemple(pointer(mon)),
      inhishop: (mon) => _inhishop(pointer(mon)),
      expels: (mon,pm,message) => _expels(pointer(mon),pointer(pm),byte(message)),
      In_W_tower: (x,y,level) => _In_W_tower(coord(x),coord(y),pointer(level)),
      noteleport_level: (mon) => _noteleport_level(pointer(mon)),
      rloc: (mon,flags) => _rloc(pointer(mon),flags>>>0),
      mnearto: (mon,x,y,moveother,flags) => _mnearto(pointer(mon),coord(x),coord(y),byte(moveother),flags>>>0),
      rloc_to: (mon,x,y) => _rloc_to(pointer(mon),coord(x),coord(y)),
      healmon: (mon,hp,extra) => _healmon(pointer(mon),hp,extra),
      mnexto: (mon,flags) => _mnexto(pointer(mon),flags>>>0),
      monnear: (mon,x,y) => _monnear(pointer(mon),coord(x),coord(y)),
      isok: (x,y) => _isok(coord(x),coord(y)),
      Monnam: (mon) => Number(_Monnam(pointer(mon))),
      doname: (obj) => Number(_doname(pointer(obj))),
      obj_extract_self: (obj) => _obj_extract_self(pointer(obj)),
      mpickobj: (mon,obj) => _mpickobj(pointer(mon),pointer(obj)),
      makemon: (pm,x,y,flags) => Number(_makemon(pointer(pm),coord(x),coord(y),flags>>>0)),
      add_to_minv: (mon,obj) => _add_to_minv(pointer(mon),pointer(obj)),
      mksobj: (type,init,artifact) => Number(_mksobj(type,byte(init),byte(artifact))),
      newsym: (x,y) => _newsym(coord(x),coord(y)),
      big_to_little: (index) => _big_to_little(index),
      strrchr: (string,ch) => Number(_strrchr(text(string),ch)),
      strncmp: (a,b,size) => _strncmp(text(a),text(b),BigInt.asUintN(64,BigInt(size))),
      strcmp: (a,b) => _strcmp(text(a),text(b)),
      monster_census: (spotted) => _monster_census(byte(spotted)),
      msummon: (mon) => _msummon(pointer(mon)),
      sgn: (value) => _sgn(value),
      enexto: (out,x,y,pm) => _enexto(pointer(out),coord(x),coord(y),pointer(pm)),
      attacktype: (pm,type) => _attacktype(pointer(pm),type),
      set_malign: (mon) => _set_malign(pointer(mon)),
      unmakemon: (mon,flags) => Number(_unmakemon(pointer(mon),flags>>>0)),
      mon_catchup_elapsed_time: (mon,elapsed) => _mon_catchup_elapsed_time(pointer(mon),long(elapsed)),
      mon_arrive: (mon,code) => _mon_arrive(pointer(mon),code),
      hcolor: (color) => Number(_hcolor(text(color))),
      rndcurse: () => _rndcurse(),
      mon_aligntyp: (mon) => _mon_aligntyp(pointer(mon)),
      com_pager: (section) => _com_pager(text(section)),
      wake_nearto: (x,y,distance) => _wake_nearto(coord(x),coord(y),distance),
      In_hell: (level) => _In_hell(pointer(level)),
      on_level: (a,b) => _on_level(pointer(a),pointer(b)),
      dist2: (x,y,xx,yy) => _dist2(coord(x),coord(y),coord(xx),coord(yy)),
      pline: (format,...args) => _teleport_wizard_pline(text(format),text(args[0]),text(args[1])),
      You: (format,...args) => _teleport_wizard_You(text(format),text(args[0]),text(args[1])),
      You_feel: (format,...args) => _teleport_wizard_You_feel(text(format),text(args[0]),text(args[1])),
      verbalize: (format,...args) => _teleport_wizard_verbalize(text(format),text(args[0]),text(args[1])),
    };
    return services;
  },
  $teleportWizardCall__deps: ['$teleportWizardServices','$stackSave','$stackRestore'],
  $teleportWizardCall: function(name,...args) {
    var saved = stackSave();
    try { return Module['nethackPorted'].wizard(teleportWizardServices(),name,...args); }
    finally { stackRestore(saved); }
  },
  amulet__deps: ['$teleportWizardCall'], amulet__sig: 'v',
  amulet: function() { teleportWizardCall('amulet'); },
  mon_has_amulet__deps: ['$teleportWizardCall'], mon_has_amulet__sig: 'ip',
  mon_has_amulet: function(mon) { return teleportWizardCall('mon_has_amulet',mon); },
  mon_has_special__deps: ['$teleportWizardCall'], mon_has_special__sig: 'ip',
  mon_has_special: function(mon) { return teleportWizardCall('mon_has_special',mon); },
  choose_stairs__deps: ['$teleportWizardCall'], choose_stairs__sig: 'vppi',
  choose_stairs: function(x,y,dir) { teleportWizardCall('choose_stairs',x,y,dir<<24>>24); },
  tactics__deps: ['$teleportWizardCall'], tactics__sig: 'ip',
  tactics: function(mon) { return teleportWizardCall('tactics',mon); },
  has_aggravatables__deps: ['$teleportWizardCall'], has_aggravatables__sig: 'ip',
  has_aggravatables: function(mon) { return teleportWizardCall('has_aggravatables',mon); },
  aggravate__deps: ['$teleportWizardCall'], aggravate__sig: 'v',
  aggravate: function() { teleportWizardCall('aggravate'); },
  clonewiz__deps: ['$teleportWizardCall'], clonewiz__sig: 'v',
  clonewiz: function() { teleportWizardCall('clonewiz'); },
  pick_nasty__deps: ['$teleportWizardCall'], pick_nasty__sig: 'ii',
  pick_nasty: function(difficulty) { return teleportWizardCall('pick_nasty',difficulty); },
  nasty__deps: ['$teleportWizardCall'], nasty__sig: 'ip',
  nasty: function(summoner) { return teleportWizardCall('nasty',summoner); },
  resurrect__deps: ['$teleportWizardCall'], resurrect__sig: 'v',
  resurrect: function() { teleportWizardCall('resurrect'); },
  intervene__deps: ['$teleportWizardCall'], intervene__sig: 'v',
  intervene: function() { teleportWizardCall('intervene'); },
  wizdeadorgone__deps: ['$teleportWizardCall'], wizdeadorgone__sig: 'v',
  wizdeadorgone: function() { teleportWizardCall('wizdeadorgone'); },
  cuss__deps: ['$teleportWizardCall'], cuss__sig: 'vp',
  cuss: function(mon) { teleportWizardCall('cuss',mon); },
  teleport_wizard_test_which__deps: ['$teleportWizardCall'], teleport_wizard_test_which__sig: 'ii',
  teleport_wizard_test_which: function(mask) { return teleportWizardCall('which_arti',mask); },
  teleport_wizard_test_has__deps: ['$teleportWizardCall'], teleport_wizard_test_has__sig: 'ipi',
  teleport_wizard_test_has: function(mon,type) { return teleportWizardCall('mon_has_arti',mon,type<<16>>16); },
  teleport_wizard_test_other__deps: ['$teleportWizardCall'], teleport_wizard_test_other__sig: 'ppi',
  teleport_wizard_test_other: function(mon,type) { return teleportWizardCall('other_mon_has_arti',mon,type<<16>>16); },
  teleport_wizard_test_ground__deps: ['$teleportWizardCall'], teleport_wizard_test_ground__sig: 'pi',
  teleport_wizard_test_ground: function(type) { return teleportWizardCall('on_ground',type<<16>>16); },
  teleport_wizard_test_you__deps: ['$teleportWizardCall'], teleport_wizard_test_you__sig: 'ii',
  teleport_wizard_test_you: function(mask) { return teleportWizardCall('you_have',mask); },
  teleport_wizard_test_target__deps: ['$teleportWizardCall'], teleport_wizard_test_target__sig: 'jip',
  teleport_wizard_test_target: function(mask,mon) { return BigInt.asUintN(64,BigInt(teleportWizardCall('target_on',mask,mon))); },
  teleport_wizard_test_strategy__deps: ['$teleportWizardCall'], teleport_wizard_test_strategy__sig: 'jp',
  teleport_wizard_test_strategy: function(mon) { return BigInt.asUintN(64,BigInt(teleportWizardCall('strategy',mon))); },
});
