// stairs ABI declarations only; game logic is in js/ported/stairs.js.
addToLibrary({
  $teleportStairsServices__deps: ['teleport_stairs_head_pointer', 'teleport_stairs_amulet', 'teleport_stairs_quest', 'teleport_stairs_special_level', 'teleport_stairs_dname', 'teleport_stairs_format_strings', 'teleport_stairs_format_int', 'teleport_track_u', 'alloc', 'free', 'assign_level', 'on_level', 'single_level_branch', 'depth', 'dunlev', 'u_on_newpos', 'u_on_rndspot', 'eos', 'strsubst', '$stringToUTF8OnStack', '$stackAlloc'],
  $teleportStairsServices: function() {
    var text = value => typeof value === 'string' ? BigInt(stringToUTF8OnStack(value)) : BigInt(value || 0);
    return {
      heap: () => HEAPU8,
      stackAlloc: size => stackAlloc(size),
      alloc: size => Number(_alloc(size >>> 0)),
      free: pointer => _free(BigInt(pointer)),
      head: () => Number(_teleport_stairs_head_pointer()),
      u: () => Number(_teleport_track_u()),
      amulet: () => _teleport_stairs_amulet(),
      quest: () => _teleport_stairs_quest(),
      specialLevel: which => Number(_teleport_stairs_special_level(which)),
      dname: index => Number(_teleport_stairs_dname(index)),
      assign_level: (dest, source) => _assign_level(BigInt(dest.address), BigInt(source.address)),
      on_level: (a, b) => _on_level(BigInt(a.address), BigInt(b.address)),
      single_level_branch: value => _single_level_branch(BigInt(value.address)),
      dunlev: value => _dunlev(BigInt(value.address)),
      depth: value => _depth(BigInt(value.address)),
      u_on_newpos: (x, y) => _u_on_newpos(x, y),
      u_on_rndspot: flag => _u_on_rndspot(flag),
      eos: pointer => Number(_eos(BigInt(pointer))),
      strsubst: (pointer, a, b) => _strsubst(BigInt(pointer), text(a), text(b)),
      Sprintf: (pointer, format, ...args) => {
        if (format.includes('%d')) _teleport_stairs_format_int(BigInt(pointer), text(format), args[0]);
        else _teleport_stairs_format_strings(BigInt(pointer), text(format), text(args[0]), text(args[1]), text(args[2]), text(args[3]));
      },
    };
  },
  $teleportStairsCall__deps: ['$teleportStairsServices', '$stackSave', '$stackRestore'],
  $teleportStairsCall: function(name, ...args) {
    var stack = stackSave();
    try { return Module['nethackPorted'].stairs(teleportStairsServices(), name, ...args); }
    finally { stackRestore(stack); }
  },
  stairway_add__deps: ['$teleportStairsCall'], stairway_add__sig: 'viiiip',
  stairway_add: function(x, y, up, ladder, dest) { teleportStairsCall('stairway_add', x, y, up, ladder, dest); },
  stairway_free_all__deps: ['$teleportStairsCall'], stairway_free_all__sig: 'v',
  stairway_free_all: function() { teleportStairsCall('stairway_free_all'); },
  stairway_at__deps: ['$teleportStairsCall'], stairway_at__sig: 'pii',
  stairway_at: function(x, y) { return teleportStairsCall('stairway_at', x, y); },
  stairway_find__deps: ['$teleportStairsCall'], stairway_find__sig: 'pp',
  stairway_find: function(dest) { return teleportStairsCall('stairway_find', dest); },
  stairway_find_from__deps: ['$teleportStairsCall'], stairway_find_from__sig: 'ppi',
  stairway_find_from: function(dest, ladder) { return teleportStairsCall('stairway_find_from', dest, ladder); },
  stairway_find_dir__deps: ['$teleportStairsCall'], stairway_find_dir__sig: 'pi',
  stairway_find_dir: function(up) { return teleportStairsCall('stairway_find_dir', up); },
  stairway_find_type_dir__deps: ['$teleportStairsCall'], stairway_find_type_dir__sig: 'pii',
  stairway_find_type_dir: function(ladder, up) { return teleportStairsCall('stairway_find_type_dir', ladder, up); },
  stairway_find_special_dir__deps: ['$teleportStairsCall'], stairway_find_special_dir__sig: 'pi',
  stairway_find_special_dir: function(up) { return teleportStairsCall('stairway_find_special_dir', up); },
  u_on_sstairs__deps: ['$teleportStairsCall'], u_on_sstairs__sig: 'vi',
  u_on_sstairs: function(up) { teleportStairsCall('u_on_sstairs', up); },
  u_on_upstairs__deps: ['$teleportStairsCall'], u_on_upstairs__sig: 'v',
  u_on_upstairs: function() { teleportStairsCall('u_on_upstairs'); },
  u_on_dnstairs__deps: ['$teleportStairsCall'], u_on_dnstairs__sig: 'v',
  u_on_dnstairs: function() { teleportStairsCall('u_on_dnstairs'); },
  On_stairs__deps: ['$teleportStairsCall'], On_stairs__sig: 'iii',
  On_stairs: function(x, y) { return teleportStairsCall('On_stairs', x, y); },
  On_ladder__deps: ['$teleportStairsCall'], On_ladder__sig: 'iii',
  On_ladder: function(x, y) { return teleportStairsCall('On_ladder', x, y); },
  On_stairs_up__deps: ['$teleportStairsCall'], On_stairs_up__sig: 'iii',
  On_stairs_up: function(x, y) { return teleportStairsCall('On_stairs_up', x, y); },
  On_stairs_dn__deps: ['$teleportStairsCall'], On_stairs_dn__sig: 'iii',
  On_stairs_dn: function(x, y) { return teleportStairsCall('On_stairs_dn', x, y); },
  known_branch_stairs__deps: ['$teleportStairsCall'], known_branch_stairs__sig: 'ip',
  known_branch_stairs: function(stair) { return teleportStairsCall('known_branch_stairs', stair); },
  stairs_description__deps: ['$teleportStairsCall'], stairs_description__sig: 'pppi',
  stairs_description: function(stair, out, stcase) { return teleportStairsCall('stairs_description', stair, out, stcase); },
});
