// Typed native ABI only; original drawbridge/entity algorithms remain JavaScript.
addToLibrary({
  $teleportDbridgeServices__deps: ['teleport_dbridge_global', 'teleport_dbridge_monster_bit', 'teleport_dbridge_hero_bit', 'teleport_dbridge_roleplay_deaf', 'teleport_dbridge_hero_event', 'teleport_dbridge_set_hero_event', 'teleport_dbridge_terrain_bit', 'teleport_dbridge_set_terrain_bit', 'teleport_dbridge_phrase_buffer', 'teleport_dbridge_rn2', 'teleport_dbridge_rnd', 'teleport_dbridge_pline', 'teleport_dbridge_pline_The', 'teleport_dbridge_You', 'teleport_dbridge_You_see', 'teleport_dbridge_You_hear', 'teleport_dbridge_pline_int', 'teleport_dbridge_pline_name_int', 'teleport_dbridge_impossible', 'teleport_dbridge_literal_storage', 'teleport_dbridge_literal_capacity', 'isok', 'on_level', 'mon_nam', 'Monnam', 'canseemon', 'sensemon', 'pronoun_gender', 'debugcore', 'strcpy', 'strcat', 'vtense', 'drown', 'lava_effects', 'done', 'enexto', 'teleds', 'monkilled', 'xkilled', 'spoteffects', 'place_monster', 'update_monster_region', 'hliquid', 'revive_nasty', 'delallobj', 't_at', 'deltrap', 'del_engr_at', 'newsym', 'block_point', 'unblock_point', 'sobj_at', 'obj_extract_self', 'flooreffects', 'wake_nearto', 'mksobj_at', 'scatter', 'does_block', 'vision_recalc', 'minliquid', 'unconscious', 'is_fainted', 'dist2', '$lengthBytesUTF8', '$stringToUTF8', '$stackAlloc', '$stackSave', '$stackRestore'],
  $teleportDbridgeServices:function(){
    var state=Module['teleportDbridgeCache']||={next:0,strings:new Map()};
    var pointer=value=>BigInt(value?value.address??value:0);
    var byte=value=>Number(BigInt.asIntN(8,BigInt(value)));
    var coord=value=>Number(BigInt.asIntN(16,BigInt(value)));
    var literal=value=>{
      if(state.strings.has(value))return state.strings.get(value);
      var size=lengthBytesUTF8(value)+1;
      if(state.next+size>Number(_teleport_dbridge_literal_capacity()))throw new Error('Review changed dbridge literal corpus');
      var at=Number(_teleport_dbridge_literal_storage())+state.next;
      stringToUTF8(value,at,size);state.next+=size;state.strings.set(value,at);return at;
    };
    var text=value=>typeof value==='string'?BigInt(literal(value)):pointer(value);
    var callers=['e_missed','e_jumps','destroy_drawbridge'];
    var callerIndex=value=>{
      var index=typeof value==='string'?callers.indexOf(value):value;
      if(!Number.isInteger(index)||index<0||index>=callers.length)throw new Error('Unexpected original dbridge RNG caller');
      return index;
    };
    var services={
      moduleKey:Module,heap:()=>HEAPU8,literal,
      stackAlloc:size=>Number(stackAlloc(size)),stackSave:()=>stackSave(),stackRestore:saved=>stackRestore(saved),
      global:index=>Number(_teleport_dbridge_global(index)),
      monsterBit:(mon,index)=>_teleport_dbridge_monster_bit(pointer(mon),index),
      heroBit:index=>_teleport_dbridge_hero_bit(index),
      roleplayDeaf:()=>_teleport_dbridge_roleplay_deaf(),
      heroEvent:index=>_teleport_dbridge_hero_event(index),
      setHeroEvent:(index,value)=>_teleport_dbridge_set_hero_event(index,Number(value)>>>0),
      terrainBit:(x,y,index)=>_teleport_dbridge_terrain_bit(coord(x),coord(y),index),
      setTerrainBit:(x,y,index,value)=>_teleport_dbridge_set_terrain_bit(coord(x),coord(y),index,Number(value)>>>0),
      phraseBuffer:()=>Number(_teleport_dbridge_phrase_buffer()),
      rn2:(bound,line,caller)=>_teleport_dbridge_rn2(bound|0,line,callerIndex(caller)),
      rnd:(bound,line,caller)=>_teleport_dbridge_rnd(bound|0,line,callerIndex(caller)),
      impossible:format=>_teleport_dbridge_impossible(text(format)),
      pline:(format,...args)=>{
        // Select only the original printf argument ABI: int, string/int, or strings.
        if(args.length===1&&format.includes('%d'))return _teleport_dbridge_pline_int(text(format),args[0]|0);
        if(args.length===2&&format.includes('%d'))return _teleport_dbridge_pline_name_int(text(format),text(args[0]),args[1]|0);
        return _teleport_dbridge_pline(text(format),text(args[0]),text(args[1]));
      },
      isok:(x,y)=>_isok(coord(x),coord(y)),
      on_level:(a,b)=>_on_level(pointer(a),pointer(b)),
      mon_nam:mon=>Number(_mon_nam(pointer(mon))),
      Monnam:mon=>Number(_Monnam(pointer(mon))),
      canseemon:mon=>_canseemon(pointer(mon)),
      sensemon:mon=>_sensemon(pointer(mon)),
      pronoun_gender:(mon,flags)=>_pronoun_gender(pointer(mon),Number(flags)>>>0),
      debugcore:(file,flag)=>_debugcore(text(file),byte(flag)),
      Strcpy:(out,value)=>Number(_strcpy(pointer(out),text(value))),
      Strcat:(out,value)=>Number(_strcat(pointer(out),text(value))),
      vtense:(name,verb)=>Number(_vtense(text(name),text(verb))),
      drown:()=>_drown(),
      lava_effects:()=>_lava_effects(),
      done:how=>_done(how|0),
      enexto:(out,x,y,pm)=>_enexto(pointer(out),coord(x),coord(y),pointer(pm)),
      teleds:(x,y,flags)=>_teleds(coord(x),coord(y),flags|0),
      monkilled:(mon,reason,how)=>_monkilled(pointer(mon),text(reason),how|0),
      xkilled:(mon,flags)=>_xkilled(pointer(mon),flags|0),
      spoteffects:pickup=>_spoteffects(byte(pickup)),
      place_monster:(mon,x,y)=>_place_monster(pointer(mon),coord(x),coord(y)),
      update_monster_region:mon=>_update_monster_region(pointer(mon)),
      hliquid:name=>Number(_hliquid(text(name))),
      revive_nasty:(x,y,message)=>_revive_nasty(coord(x),coord(y),text(message)),
      delallobj:(x,y)=>_delallobj(coord(x),coord(y)),
      t_at:(x,y)=>Number(_t_at(coord(x),coord(y))),
      deltrap:trap=>_deltrap(pointer(trap)),
      del_engr_at:(x,y)=>_del_engr_at(coord(x),coord(y)),
      newsym:(x,y)=>_newsym(coord(x),coord(y)),
      block_point:(x,y)=>_block_point(x|0,y|0),
      unblock_point:(x,y)=>_unblock_point(x|0,y|0),
      sobj_at:(type,x,y)=>Number(_sobj_at(type|0,coord(x),coord(y))),
      obj_extract_self:obj=>_obj_extract_self(pointer(obj)),
      flooreffects:(obj,x,y,verb)=>_flooreffects(pointer(obj),coord(x),coord(y),text(verb)),
      wake_nearto:(x,y,distance)=>_wake_nearto(coord(x),coord(y),distance|0),
      mksobj_at:(type,x,y,init,art)=>Number(_mksobj_at(type|0,coord(x),coord(y),byte(init),byte(art))),
      scatter:(x,y,force,flags,obj)=>_scatter(coord(x),coord(y),force|0,Number(flags)>>>0,pointer(obj)),
      does_block:(x,y,terrain)=>_does_block(x|0,y|0,pointer(terrain)),
      vision_recalc:mode=>_vision_recalc(mode|0),
      minliquid:mon=>_minliquid(pointer(mon)),
      unconscious:()=>_unconscious(),
      is_fainted:()=>_is_fainted(),
      dist2:(x,y,xx,yy)=>_dist2(coord(x),coord(y),coord(xx),coord(yy)),
      pline_The:(format,...args)=>_teleport_dbridge_pline_The(text(format),text(args[0]),text(args[1])),
      You:(format,...args)=>_teleport_dbridge_You(text(format),text(args[0]),text(args[1])),
      You_see:(format,...args)=>_teleport_dbridge_You_see(text(format),text(args[0]),text(args[1])),
      You_hear:(format,...args)=>_teleport_dbridge_You_hear(text(format),text(args[0]),text(args[1])),
    };
    return services;
  },
  $teleportDbridgeCall__deps:['$teleportDbridgeServices','$stackSave','$stackRestore'],
  $teleportDbridgeCall:function(name,...args){var saved=stackSave();try{return Module['nethackPorted'].dbridge(teleportDbridgeServices(),name,...args);}finally{stackRestore(saved);}},
  is_waterwall__deps:['$teleportDbridgeCall'],is_waterwall__sig:'iii',
  is_waterwall:function(x,y){return teleportDbridgeCall('is_waterwall',x<<16>>16,y<<16>>16);},
  is_pool__deps:['$teleportDbridgeCall'],is_pool__sig:'iii',
  is_pool:function(x,y){return teleportDbridgeCall('is_pool',x<<16>>16,y<<16>>16);},
  is_lava__deps:['$teleportDbridgeCall'],is_lava__sig:'iii',
  is_lava:function(x,y){return teleportDbridgeCall('is_lava',x<<16>>16,y<<16>>16);},
  is_pool_or_lava__deps:['$teleportDbridgeCall'],is_pool_or_lava__sig:'iii',
  is_pool_or_lava:function(x,y){return teleportDbridgeCall('is_pool_or_lava',x<<16>>16,y<<16>>16);},
  is_ice__deps:['$teleportDbridgeCall'],is_ice__sig:'iii',
  is_ice:function(x,y){return teleportDbridgeCall('is_ice',x<<16>>16,y<<16>>16);},
  is_moat__deps:['$teleportDbridgeCall'],is_moat__sig:'iii',
  is_moat:function(x,y){return teleportDbridgeCall('is_moat',x<<16>>16,y<<16>>16);},
  is_drawbridge_wall__deps:['$teleportDbridgeCall'],is_drawbridge_wall__sig:'iii',
  is_drawbridge_wall:function(x,y){return teleportDbridgeCall('is_drawbridge_wall',x<<16>>16,y<<16>>16);},
  is_db_wall__deps:['$teleportDbridgeCall'],is_db_wall__sig:'iii',
  is_db_wall:function(x,y){return teleportDbridgeCall('is_db_wall',x<<16>>16,y<<16>>16);},
  db_under_typ__deps:['$teleportDbridgeCall'],db_under_typ__sig:'ii',
  db_under_typ:function(mask){return teleportDbridgeCall('db_under_typ',mask);},
  find_drawbridge__deps:['$teleportDbridgeCall'],find_drawbridge__sig:'ipp',
  find_drawbridge:function(x,y){return teleportDbridgeCall('find_drawbridge',x,y);},
  create_drawbridge__deps:['$teleportDbridgeCall'],create_drawbridge__sig:'iiiii',
  create_drawbridge:function(x,y,dir,flag){return teleportDbridgeCall('create_drawbridge',x<<16>>16,y<<16>>16,dir,flag<<24>>24);},
  close_drawbridge__deps:['$teleportDbridgeCall'],close_drawbridge__sig:'vii',
  close_drawbridge:function(x,y){teleportDbridgeCall('close_drawbridge',x<<16>>16,y<<16>>16);},
  open_drawbridge__deps:['$teleportDbridgeCall'],open_drawbridge__sig:'vii',
  open_drawbridge:function(x,y){teleportDbridgeCall('open_drawbridge',x<<16>>16,y<<16>>16);},
  destroy_drawbridge__deps:['$teleportDbridgeCall'],destroy_drawbridge__sig:'vii',
  destroy_drawbridge:function(x,y){teleportDbridgeCall('destroy_drawbridge',x<<16>>16,y<<16>>16);},
  teleport_dbridge_test_get_wall_for_db__deps:['$teleportDbridgeCall'],teleport_dbridge_test_get_wall_for_db__sig:'vpp',
  teleport_dbridge_test_get_wall_for_db:function(x,y){teleportDbridgeCall('get_wall_for_db',x,y);},
  teleport_dbridge_test_e_at__deps:['$teleportDbridgeCall'],teleport_dbridge_test_e_at__sig:'pii',
  teleport_dbridge_test_e_at:function(x,y){return teleportDbridgeCall('e_at',x<<16>>16,y<<16>>16);},
  teleport_dbridge_test_m_to_e__deps:['$teleportDbridgeCall'],teleport_dbridge_test_m_to_e__sig:'vpiip',
  teleport_dbridge_test_m_to_e:function(mon,x,y,entity){teleportDbridgeCall('m_to_e',mon,x<<16>>16,y<<16>>16,entity);},
  teleport_dbridge_test_u_to_e__deps:['$teleportDbridgeCall'],teleport_dbridge_test_u_to_e__sig:'vp',
  teleport_dbridge_test_u_to_e:function(entity){teleportDbridgeCall('u_to_e',entity);},
  teleport_dbridge_test_set_entity__deps:['$teleportDbridgeCall'],teleport_dbridge_test_set_entity__sig:'viip',
  teleport_dbridge_test_set_entity:function(x,y,entity){teleportDbridgeCall('set_entity',x<<16>>16,y<<16>>16,entity);},
  teleport_dbridge_test_e_nam__deps:['$teleportDbridgeCall'],teleport_dbridge_test_e_nam__sig:'pp',
  teleport_dbridge_test_e_nam:function(entity){return teleportDbridgeCall('e_nam',entity);},
  teleport_dbridge_test_E_phrase__deps:['$teleportDbridgeCall'],teleport_dbridge_test_E_phrase__sig:'ppp',
  teleport_dbridge_test_E_phrase:function(entity,verb){return teleportDbridgeCall('E_phrase',entity,verb);},
  teleport_dbridge_test_e_survives_at__deps:['$teleportDbridgeCall'],teleport_dbridge_test_e_survives_at__sig:'ipii',
  teleport_dbridge_test_e_survives_at:function(entity,x,y){return teleportDbridgeCall('e_survives_at',entity,x<<16>>16,y<<16>>16);},
  teleport_dbridge_test_e_died__deps:['$teleportDbridgeCall'],teleport_dbridge_test_e_died__sig:'vpii',
  teleport_dbridge_test_e_died:function(entity,flags,how){teleportDbridgeCall('e_died',entity,flags,how);},
  teleport_dbridge_test_automiss__deps:['$teleportDbridgeCall'],teleport_dbridge_test_automiss__sig:'ip',
  teleport_dbridge_test_automiss:function(entity){return teleportDbridgeCall('automiss',entity);},
  teleport_dbridge_test_e_missed__deps:['$teleportDbridgeCall'],teleport_dbridge_test_e_missed__sig:'ipi',
  teleport_dbridge_test_e_missed:function(entity,chunks){return teleportDbridgeCall('e_missed',entity,chunks<<24>>24);},
  teleport_dbridge_test_e_jumps__deps:['$teleportDbridgeCall'],teleport_dbridge_test_e_jumps__sig:'ip',
  teleport_dbridge_test_e_jumps:function(entity){return teleportDbridgeCall('e_jumps',entity);},
  teleport_dbridge_test_do_entity__deps:['$teleportDbridgeCall'],teleport_dbridge_test_do_entity__sig:'vp',
  teleport_dbridge_test_do_entity:function(entity){teleportDbridgeCall('do_entity',entity);},
  teleport_dbridge_test_nokiller__deps:['$teleportDbridgeCall'],teleport_dbridge_test_nokiller__sig:'v',
  teleport_dbridge_test_nokiller:function(){teleportDbridgeCall('nokiller');},
});
