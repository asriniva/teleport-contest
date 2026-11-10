// WORN typed ABI only; original equipment decisions remain in worn.js.
addToLibrary({
  $teleportWornServices__deps:['teleport_worn_global', 'teleport_worn_equipment_cell', 'teleport_worn_object_bit', 'teleport_worn_set_object_bit', 'teleport_worn_class_bit', 'teleport_worn_monster_bit', 'teleport_worn_set_monster_bit', 'teleport_worn_rnl', 'teleport_worn_distant_name', 'teleport_worn_common_string', 'teleport_worn_snprintf', 'teleport_worn_format_p', 'teleport_worn_format_pp', 'teleport_worn_format_ppp', 'teleport_worn_format_pj', 'teleport_worn_format_pjpj', 'teleport_worn_impossible0', 'teleport_worn_impossible_p', 'teleport_worn_impossible_j', 'teleport_worn_pline', 'teleport_worn_pline_mon', 'teleport_worn_You', 'teleport_worn_You_hear', 'teleport_worn_literal_storage', 'teleport_worn_literal_capacity', 'set_twoweap', 'cvt_prop_to_mseenres', 'monstunseesu', 'set_artifact_intrinsic', 'cancel_doff', 'update_inventory', 'newsym', 'see_wsegs', 'canseemon', 'learnwand', 'dismount_steed', 'artifact_light', 'end_burn', 'begin_burn', 'vision_recalc', 'curse', 'arti_light_description', 'Yname2', 'Monnam', 'mon_nam', 'doname', 'otense', 'simpleonames', 'hcolor', 's_suffix', 'sgn', 'breakarm', 'sliparm', 'num_horns', 'is_art', 'strcpy', 'strncmpi', 'strsubst', 'place_object', 'm_useup', 'can_saddle', 'can_ride', 'surface', 'instapetrify', 'an', 'pmname', 'Mgender', 'raceptr', 'obj_extract_self', 'check_gear_next_turn', 'obj_no_longer_held', 'mwepgone', 'fmt_ptr', 'discover_object', 'pronoun_gender', 'cloak_simple_name', '$lengthBytesUTF8', '$stringToUTF8', '$stackAlloc', '$stackSave', '$stackRestore'],
  $teleportWornServices:function(){
    var state=Module['teleportWornCache']||={next:0,strings:new Map()};
    var pointer=value=>BigInt(value?value.address??value:0);
    var long=value=>BigInt.asIntN(64,BigInt(value));
    var ulong=value=>BigInt.asUintN(64,BigInt(value));
    var byte=value=>Number(BigInt.asIntN(8,BigInt(value)));
    var coord=value=>Number(BigInt.asIntN(16,BigInt(value)));
    var literal=value=>{
      if(state.strings.has(value))return state.strings.get(value);
      var size=lengthBytesUTF8(value)+1;
      if(state.next+size>Number(_teleport_worn_literal_capacity()))throw new Error('Review changed worn literal corpus');
      var at=Number(_teleport_worn_literal_storage())+state.next;
      stringToUTF8(value,at,size);state.next+=size;state.strings.set(value,at);return at;
    };
    var text=value=>typeof value==='string'?BigInt(literal(value)):pointer(value);
    var services={
      moduleKey:Module,heap:()=>HEAPU8,literal,
      stackAlloc:size=>Number(stackAlloc(size)),stackSave:()=>stackSave(),stackRestore:saved=>stackRestore(saved),
      global:index=>Number(_teleport_worn_global(index)),equipmentCell:index=>Number(_teleport_worn_equipment_cell(index)),
      objectBit:(obj,index)=>_teleport_worn_object_bit(pointer(obj),index),
      setObjectBit:(obj,index,value)=>_teleport_worn_set_object_bit(pointer(obj),index,Number(value)>>>0),
      classBit:(obj,index)=>_teleport_worn_class_bit(pointer(obj),index),
      monsterBit:(mon,index)=>_teleport_worn_monster_bit(pointer(mon),index),
      setMonsterBit:(mon,index,value)=>_teleport_worn_set_monster_bit(pointer(mon),index,Number(value)>>>0),
      rnl:bound=>_teleport_worn_rnl(bound|0),
      commonString:index=>Number(_teleport_worn_common_string(index)),
      Snprintf:(out,size,format,value)=>_teleport_worn_snprintf(pointer(out),ulong(size),text(format),text(value)),
      Sprintf:(out,format,...args)=>{
        if(args.length===4)return _teleport_worn_format_pjpj(pointer(out),text(format),text(args[0]),long(args[1]),text(args[2]),long(args[3]));
        if(args.length===3)return _teleport_worn_format_ppp(pointer(out),text(format),...args.map(text));
        if(args.length===2)return typeof args[1]==='bigint'
          ?_teleport_worn_format_pj(pointer(out),text(format),text(args[0]),long(args[1]))
          :_teleport_worn_format_pp(pointer(out),text(format),text(args[0]),text(args[1]));
        if(args.length===1)return _teleport_worn_format_p(pointer(out),text(format),text(args[0]));
        throw new Error('Unexpected original worn Sprintf ABI');
      },
      impossible:(format,...args)=>args.length===0?_teleport_worn_impossible0(text(format)):
        typeof args[0]==='bigint'?_teleport_worn_impossible_j(text(format),long(args[0])):
          _teleport_worn_impossible_p(text(format),text(args[0])),
      pline:(format,...args)=>_teleport_worn_pline(text(format),text(args[0]),text(args[1]),text(args[2]),text(args[3])),
      pline_mon:(mon,format,...args)=>_teleport_worn_pline_mon(pointer(mon),text(format),text(args[0]),text(args[1]),text(args[2])),
      You:(format,value)=>_teleport_worn_You(text(format),text(value)),You_hear:format=>_teleport_worn_You_hear(text(format)),
      set_twoweap:(a)=>_set_twoweap(byte(a)),
      cvt_prop_to_mseenres:(a)=>BigInt.asUintN(64,_cvt_prop_to_mseenres(Number(a)&255)),
      monstunseesu:(a)=>_monstunseesu(ulong(a)),
      set_artifact_intrinsic:(a,b,c)=>_set_artifact_intrinsic(pointer(a),byte(b),long(c)),
      cancel_doff:(a,b)=>_cancel_doff(pointer(a),long(b)),
      update_inventory:()=>_update_inventory(),
      newsym:(a,b)=>_newsym(coord(a),coord(b)),
      see_wsegs:(a)=>_see_wsegs(pointer(a)),
      canseemon:(a)=>_canseemon(pointer(a)),
      learnwand:(a)=>_learnwand(pointer(a)),
      dismount_steed:(a)=>_dismount_steed(Number(a)|0),
      artifact_light:(a)=>_artifact_light(pointer(a)),
      end_burn:(a,b)=>_end_burn(pointer(a),byte(b)),
      begin_burn:(a,b)=>_begin_burn(pointer(a),byte(b)),
      vision_recalc:(a)=>_vision_recalc(Number(a)|0),
      curse:(a)=>_curse(pointer(a)),
      arti_light_description:(a)=>Number(_arti_light_description(pointer(a))),
      Yname2:(a)=>Number(_Yname2(pointer(a))),
      Monnam:(a)=>Number(_Monnam(pointer(a))),
      mon_nam:(a)=>Number(_mon_nam(pointer(a))),
      doname:(a)=>Number(_doname(pointer(a))),
      otense:(a,b)=>Number(_otense(pointer(a),text(b))),
      simpleonames:(a)=>Number(_simpleonames(pointer(a))),
      hcolor:(a)=>Number(_hcolor(text(a))),
      s_suffix:(a)=>Number(_s_suffix(text(a))),
      sgn:(a)=>_sgn(Number(a)|0),
      breakarm:(a)=>_breakarm(pointer(a)),
      sliparm:(a)=>_sliparm(pointer(a)),
      num_horns:(a)=>_num_horns(pointer(a)),
      is_art:(a,b)=>_is_art(pointer(a),Number(b)|0),
      strcpy:(a,b)=>Number(_strcpy(pointer(a),text(b))),
      strncmpi:(a,b,c)=>_strncmpi(text(a),text(b),Number(c)|0),
      strsubst:(a,b,c)=>Number(_strsubst(pointer(a),text(b),text(c))),
      place_object:(a,b,c)=>_place_object(pointer(a),coord(b),coord(c)),
      m_useup:(a,b)=>_m_useup(pointer(a),pointer(b)),
      can_saddle:(a)=>_can_saddle(pointer(a)),
      can_ride:(a)=>_can_ride(pointer(a)),
      surface:(a,b)=>Number(_surface(coord(a),coord(b))),
      instapetrify:(a)=>_instapetrify(text(a)),
      an:(a)=>Number(_an(text(a))),
      pmname:(a,b)=>Number(_pmname(pointer(a),Number(b)|0)),
      Mgender:(a)=>_Mgender(pointer(a)),
      raceptr:(a)=>Number(_raceptr(pointer(a))),
      obj_extract_self:(a)=>_obj_extract_self(pointer(a)),
      check_gear_next_turn:(a)=>_check_gear_next_turn(pointer(a)),
      obj_no_longer_held:(a)=>_obj_no_longer_held(pointer(a)),
      mwepgone:(a)=>_mwepgone(pointer(a)),
      fmt_ptr:(a)=>Number(_fmt_ptr(pointer(a))),
      discover_object:(a,b,c,d)=>_discover_object(Number(a)|0,byte(b),byte(c),byte(d)),
      pronoun_gender:(a,b)=>_pronoun_gender(pointer(a),Number(b)>>>0),
      cloak_simple_name:obj=>Number(_cloak_simple_name(pointer(obj))),
    };
    services.Strcpy=services.strcpy;
    services.strcmpi=(a,b)=>services.strncmpi(a,b,-1);
    services.distant_name=(obj,callback)=>{
      if(callback!==services.doname)throw new Error('Unexpected original worn naming callback');
      return Number(_teleport_worn_distant_name(pointer(obj)));
    };
    return services;
  },
  $teleportWornCall__deps:['$teleportWornServices','$stackSave','$stackRestore'],
  $teleportWornCall:function(name,...args){var saved=stackSave();try{return Module['nethackPorted'].worn(teleportWornServices(),name,...args);}finally{stackRestore(saved);}},
  recalc_telepat_range__deps:['$teleportWornCall'],recalc_telepat_range__sig:'v',
  recalc_telepat_range:function(){teleportWornCall('recalc_telepat_range');},
  setworn__deps:['$teleportWornCall'],setworn__sig:'vpj',
  setworn:function(a,b){teleportWornCall('setworn' ,a,b);},
  setnotworn__deps:['$teleportWornCall'],setnotworn__sig:'vp',
  setnotworn:function(a){teleportWornCall('setnotworn' ,a);},
  allunworn__deps:['$teleportWornCall'],allunworn__sig:'v',
  allunworn:function(){teleportWornCall('allunworn');},
  wearmask_to_obj__deps:['$teleportWornCall'],wearmask_to_obj__sig:'pj',
  wearmask_to_obj:function(a){return teleportWornCall('wearmask_to_obj' ,a);},
  wornmask_to_armcat__deps:['$teleportWornCall'],wornmask_to_armcat__sig:'ij',
  wornmask_to_armcat:function(a){return teleportWornCall('wornmask_to_armcat' ,a);},
  armcat_to_wornmask__deps:['$teleportWornCall'],armcat_to_wornmask__sig:'ji',
  armcat_to_wornmask:function(a){return BigInt.asIntN(64,teleportWornCall('armcat_to_wornmask' ,a));},
  wearslot__deps:['$teleportWornCall'],wearslot__sig:'jp',
  wearslot:function(a){return BigInt.asIntN(64,teleportWornCall('wearslot' ,a));},
  check_wornmask_slots__deps:['$teleportWornCall'],check_wornmask_slots__sig:'v',
  check_wornmask_slots:function(){teleportWornCall('check_wornmask_slots');},
  mon_set_minvis__deps:['$teleportWornCall'],mon_set_minvis__sig:'vpi',
  mon_set_minvis:function(a,b){teleportWornCall('mon_set_minvis' ,a,b);},
  mon_adjust_speed__deps:['$teleportWornCall'],mon_adjust_speed__sig:'vpip',
  mon_adjust_speed:function(a,b,c){teleportWornCall('mon_adjust_speed' ,a,b,c);},
  update_mon_extrinsics__deps:['$teleportWornCall'],update_mon_extrinsics__sig:'vppii',
  update_mon_extrinsics:function(a,b,c,d){teleportWornCall('update_mon_extrinsics' ,a,b,c,d);},
  find_mac__deps:['$teleportWornCall'],find_mac__sig:'ip',
  find_mac:function(a){return teleportWornCall('find_mac' ,a);},
  m_dowear__deps:['$teleportWornCall'],m_dowear__sig:'vpi',
  m_dowear:function(a,b){teleportWornCall('m_dowear' ,a,b);},
  which_armor__deps:['$teleportWornCall'],which_armor__sig:'ppj',
  which_armor:function(a,b){return teleportWornCall('which_armor' ,a,b);},
  clear_bypasses__deps:['$teleportWornCall'],clear_bypasses__sig:'v',
  clear_bypasses:function(){teleportWornCall('clear_bypasses');},
  bypass_obj__deps:['$teleportWornCall'],bypass_obj__sig:'vp',
  bypass_obj:function(a){teleportWornCall('bypass_obj' ,a);},
  bypass_objlist__deps:['$teleportWornCall'],bypass_objlist__sig:'vpi',
  bypass_objlist:function(a,b){teleportWornCall('bypass_objlist' ,a,b);},
  nxt_unbypassed_obj__deps:['$teleportWornCall'],nxt_unbypassed_obj__sig:'pp',
  nxt_unbypassed_obj:function(a){return teleportWornCall('nxt_unbypassed_obj' ,a);},
  nxt_unbypassed_loot__deps:['$teleportWornCall'],nxt_unbypassed_loot__sig:'ppp',
  nxt_unbypassed_loot:function(a,b){return teleportWornCall('nxt_unbypassed_loot' ,a,b);},
  mon_break_armor__deps:['$teleportWornCall'],mon_break_armor__sig:'vpi',
  mon_break_armor:function(a,b){teleportWornCall('mon_break_armor' ,a,b);},
  racial_exception__deps:['$teleportWornCall'],racial_exception__sig:'ipp',
  racial_exception:function(a,b){return teleportWornCall('racial_exception' ,a,b);},
  extract_from_minvent__deps:['$teleportWornCall'],extract_from_minvent__sig:'vppii',
  extract_from_minvent:function(a,b,c,d){teleportWornCall('extract_from_minvent' ,a,b,c,d);},
  teleport_worn_test_lose__deps:['$teleportWornCall'],teleport_worn_test_lose__sig:'vppi',
  teleport_worn_test_lose:function(a,b,c){teleportWornCall('m_lose_armor' ,a,b,c);},
  teleport_worn_test_clear__deps:['$teleportWornCall'],teleport_worn_test_clear__sig:'vp',
  teleport_worn_test_clear:function(a){teleportWornCall('clear_bypass' ,a);},
  teleport_worn_test_type__deps:['$teleportWornCall'],teleport_worn_test_type__sig:'vpjii',
  teleport_worn_test_type:function(a,b,c,d){teleportWornCall('m_dowear_type' ,a,b,c,d);},
  teleport_worn_test_pref__deps:['$teleportWornCall'],teleport_worn_test_pref__sig:'ipp',
  teleport_worn_test_pref:function(a,b){return teleportWornCall('extra_pref' ,a,b);},
});
