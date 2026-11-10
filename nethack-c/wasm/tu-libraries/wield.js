// Typed native ABI only; weapon decisions and selection callbacks remain JS.
addToLibrary({
  $teleportWieldServices__deps:['teleport_wield_global', 'teleport_wield_equipment_cell', 'teleport_wield_hands', 'teleport_wield_hero_bit', 'teleport_wield_object_bit', 'teleport_wield_set_object_bit', 'teleport_wield_class_bit', 'teleport_wield_callback_pointer', 'teleport_wield_getobj', 'teleport_wield_ynq', 'teleport_wield_rnd', 'teleport_wield_rn2', 'teleport_wield_common_string', 'teleport_wield_format_p', 'teleport_wield_format_pp', 'teleport_wield_format_ppp', 'teleport_wield_format_jp', 'teleport_wield_format_jpj', 'teleport_wield_format_pjpj', 'teleport_wield_pline', 'teleport_wield_You', 'teleport_wield_Your', 'teleport_wield_You_cant', 'teleport_wield_literal_storage', 'teleport_wield_literal_capacity', 'setworn', 'artifact_light', 'end_burn', 'begin_burn', 'is_art', 'corpse_xname', 'makeplural', 'body_part', 'killer_xname', 'instapetrify', 'retouch_object', 'xname', 'The', 'strncmp', 'aobjnam', 'set_bknown', 'prinv', 'arti_speak', 'Tobjnam', 'arti_light_description', 'inside_shop', 'shop_keeper', 'shkname', 'clear_splitobjs', 'unsplitobj', 'reset_remarm', 'inv_cnt', 'splittable', 'simpleonames', 'splitobj', 'Shk_Your', 'otense', 'freeinv', 'addinv_nomerge', 'update_inventory', 'strcmp', 'strcpy', 'strstri', 'yname', 'doname', 'Yname2', 'Yobjnam2', 'dropx', 'yobjnam', 'vtense', 'acurr', 'hcolor', 'an', 'uncurse', 'strange_feeling', 'exercise', 'weight', 'alter_cost', 'discover_object', 'encumber_msg', 'costly_alteration', 'restrict_name', 'useupall', 'undiscovered_artifact', '$lengthBytesUTF8', '$stringToUTF8', '$stackAlloc', '$stackSave', '$stackRestore'],
  $teleportWieldServices:function(){
    var state=Module['teleportWieldCache']||={next:0,strings:new Map()};
    var pointer=value=>BigInt(value?value.address??value:0);
    var long=value=>BigInt.asIntN(64,BigInt(value));
    var ulong=value=>BigInt.asUintN(64,BigInt(value));
    var byte=value=>Number(BigInt.asIntN(8,BigInt(value)));
    var coord=value=>Number(BigInt.asIntN(16,BigInt(value)));
    var literal=value=>{
      if(state.strings.has(value))return state.strings.get(value);
      var size=lengthBytesUTF8(value)+1;
      if(state.next+size>Number(_teleport_wield_literal_capacity()))throw new Error('Review changed wield literal corpus');
      var at=Number(_teleport_wield_literal_storage())+state.next;
      stringToUTF8(value,at,size);state.next+=size;state.strings.set(value,at);return at;
    };
    var text=value=>typeof value==='string'?BigInt(literal(value)):pointer(value);
    var services={
      moduleKey:Module,heap:()=>HEAPU8,literal,
      stackAlloc:size=>Number(stackAlloc(size)),stackSave:()=>stackSave(),stackRestore:saved=>stackRestore(saved),
      global:index=>Number(_teleport_wield_global(index)),equipmentCell:index=>Number(_teleport_wield_equipment_cell(index)),
      hands:()=>Number(_teleport_wield_hands()),heroBit:index=>_teleport_wield_hero_bit(index),
      objectBit:(obj,index)=>_teleport_wield_object_bit(pointer(obj),index),
      setObjectBit:(obj,index,value)=>_teleport_wield_set_object_bit(pointer(obj),index,Number(value)>>>0),
      classBit:(obj,index)=>_teleport_wield_class_bit(pointer(obj),index),
      callbackPointer:index=>BigInt.asUintN(64,_teleport_wield_callback_pointer(index)),
      getobj:(prompt,callback,flags)=>Number(_teleport_wield_getobj(text(prompt),ulong(callback),Number(flags)>>>0)),
      ynq:prompt=>_teleport_wield_ynq(text(prompt)),
      rnd:bound=>_teleport_wield_rnd(bound|0),
      rn2:(bound,line)=>{
        var site=line===1000?0:line===1044?1:-1;
        if(site<0)throw new Error('Unexpected original wield RNG site');
        return _teleport_wield_rn2(bound|0,site);
      },
      commonString:index=>Number(_teleport_wield_common_string(index)),
      Sprintf:(out,format,...args)=>{
        if(args.length===4)return _teleport_wield_format_pjpj(pointer(out),text(format),text(args[0]),long(args[1]),text(args[2]),long(args[3]));
        if(args.length===3)return typeof args[0]==='bigint'
          ?_teleport_wield_format_jpj(pointer(out),text(format),long(args[0]),text(args[1]),long(args[2]))
          :_teleport_wield_format_ppp(pointer(out),text(format),...args.map(text));
        if(args.length===2)return typeof args[0]==='bigint'
          ?_teleport_wield_format_jp(pointer(out),text(format),long(args[0]),text(args[1]))
          :_teleport_wield_format_pp(pointer(out),text(format),text(args[0]),text(args[1]));
        if(args.length===1)return _teleport_wield_format_p(pointer(out),text(format),text(args[0]));
        throw new Error('Unexpected original wield Sprintf ABI');
      },
      pline:(format,...args)=>_teleport_wield_pline(text(format),text(args[0]),text(args[1]),text(args[2]),text(args[3]),text(args[4])),
      You:(format,...args)=>_teleport_wield_You(text(format),text(args[0]),text(args[1]),text(args[2])),
      Your:(format,...args)=>_teleport_wield_Your(text(format),text(args[0]),text(args[1]),text(args[2])),
      You_cant:(format,...args)=>_teleport_wield_You_cant(text(format),text(args[0]),text(args[1]),text(args[2])),
      setworn:(a,b)=>_setworn(pointer(a),long(b)),
      artifact_light:(a)=>_artifact_light(pointer(a)),
      end_burn:(a,b)=>_end_burn(pointer(a),byte(b)),
      begin_burn:(a,b)=>_begin_burn(pointer(a),byte(b)),
      is_art:(a,b)=>_is_art(pointer(a),Number(b)|0),
      corpse_xname:(a,b,c)=>Number(_corpse_xname(pointer(a),text(b),Number(c)>>>0)),
      makeplural:(a)=>Number(_makeplural(text(a))),
      body_part:(a)=>Number(_body_part(Number(a)|0)),
      killer_xname:(a)=>Number(_killer_xname(pointer(a))),
      instapetrify:(a)=>_instapetrify(text(a)),
      retouch_object:(a,b)=>_retouch_object(pointer(a),byte(b)),
      xname:(a)=>Number(_xname(pointer(a))),
      The:(a)=>Number(_The(text(a))),
      strncmp:(a,b,c)=>_strncmp(text(a),text(b),ulong(c)),
      aobjnam:(a,b)=>Number(_aobjnam(pointer(a),text(b))),
      set_bknown:(a,b)=>_set_bknown(pointer(a),Number(b)>>>0),
      prinv:(a,b,c)=>_prinv(text(a),pointer(b),long(c)),
      arti_speak:(a)=>_arti_speak(pointer(a)),
      Tobjnam:(a,b)=>Number(_Tobjnam(pointer(a),text(b))),
      arti_light_description:(a)=>Number(_arti_light_description(pointer(a))),
      inside_shop:(a,b)=>byte(_inside_shop(coord(a),coord(b))),
      shop_keeper:(a)=>Number(_shop_keeper(byte(a))),
      shkname:(a)=>Number(_shkname(pointer(a))),
      clear_splitobjs:()=>_clear_splitobjs(),
      unsplitobj:(a)=>Number(_unsplitobj(pointer(a))),
      reset_remarm:()=>_reset_remarm(),
      inv_cnt:(a)=>_inv_cnt(byte(a)),
      splittable:(a)=>_splittable(pointer(a)),
      simpleonames:(a)=>Number(_simpleonames(pointer(a))),
      splitobj:(a,b)=>Number(_splitobj(pointer(a),long(b))),
      Shk_Your:(a,b)=>Number(_Shk_Your(pointer(a),pointer(b))),
      otense:(a,b)=>Number(_otense(pointer(a),text(b))),
      freeinv:(a)=>_freeinv(pointer(a)),
      addinv_nomerge:(a)=>Number(_addinv_nomerge(pointer(a))),
      update_inventory:()=>_update_inventory(),
      strcmp:(a,b)=>_strcmp(text(a),text(b)),
      strcpy:(a,b)=>Number(_strcpy(pointer(a),text(b))),
      strstri:(a,b)=>Number(_strstri(text(a),text(b))),
      yname:(a)=>Number(_yname(pointer(a))),
      doname:(a)=>Number(_doname(pointer(a))),
      Yname2:(a)=>Number(_Yname2(pointer(a))),
      Yobjnam2:(a,b)=>Number(_Yobjnam2(pointer(a),text(b))),
      dropx:(a)=>_dropx(pointer(a)),
      yobjnam:(a,b)=>Number(_yobjnam(pointer(a),text(b))),
      vtense:(a,b)=>Number(_vtense(text(a),text(b))),
      acurr:(a)=>_acurr(Number(a)|0),
      hcolor:(a)=>Number(_hcolor(text(a))),
      an:(a)=>Number(_an(text(a))),
      uncurse:(a)=>_uncurse(pointer(a)),
      strange_feeling:(a,b)=>_strange_feeling(pointer(a),text(b)),
      exercise:(a,b)=>_exercise(Number(a)|0,byte(b)),
      weight:(a)=>_weight(pointer(a)),
      alter_cost:(a,b)=>_alter_cost(pointer(a),long(b)),
      discover_object:(a,b,c,d)=>_discover_object(Number(a)|0,byte(b),byte(c),byte(d)),
      encumber_msg:()=>_encumber_msg(),
      costly_alteration:(a,b)=>_costly_alteration(pointer(a),Number(b)|0),
      restrict_name:(a,b)=>_restrict_name(pointer(a),text(b)),
      useupall:(a)=>_useupall(pointer(a)),
      undiscovered_artifact:(a)=>_undiscovered_artifact(Number(a)|0),
    };
    services.Strcpy=services.strcpy;
    return services;
  },
  $teleportWieldCall__deps:['$teleportWieldServices','$stackSave','$stackRestore'],
  $teleportWieldCall:function(name,...args){var saved=stackSave();try{return Module['nethackPorted'].wield(teleportWieldServices(),name,...args);}finally{stackRestore(saved);}},
  setuwep__deps:['$teleportWieldCall'],setuwep__sig:'vp',
  setuwep:function(a){teleportWieldCall('setuwep' ,a);},
  empty_handed__deps:['$teleportWieldCall'],empty_handed__sig:'p',
  empty_handed:function(){return teleportWieldCall('empty_handed');},
  setuqwep__deps:['$teleportWieldCall'],setuqwep__sig:'vp',
  setuqwep:function(a){teleportWieldCall('setuqwep' ,a);},
  setuswapwep__deps:['$teleportWieldCall'],setuswapwep__sig:'vp',
  setuswapwep:function(a){teleportWieldCall('setuswapwep' ,a);},
  dowield__deps:['$teleportWieldCall'],dowield__sig:'i',
  dowield:function(){return teleportWieldCall('dowield');},
  doswapweapon__deps:['$teleportWieldCall'],doswapweapon__sig:'i',
  doswapweapon:function(){return teleportWieldCall('doswapweapon');},
  dowieldquiver__deps:['$teleportWieldCall'],dowieldquiver__sig:'i',
  dowieldquiver:function(){return teleportWieldCall('dowieldquiver');},
  doquiver_core__deps:['$teleportWieldCall'],doquiver_core__sig:'ip',
  doquiver_core:function(a){return teleportWieldCall('doquiver_core' ,a);},
  wield_tool__deps:['$teleportWieldCall'],wield_tool__sig:'ipp',
  wield_tool:function(a,b){return teleportWieldCall('wield_tool' ,a,b);},
  can_twoweapon__deps:['$teleportWieldCall'],can_twoweapon__sig:'i',
  can_twoweapon:function(){return teleportWieldCall('can_twoweapon');},
  drop_uswapwep__deps:['$teleportWieldCall'],drop_uswapwep__sig:'v',
  drop_uswapwep:function(){teleportWieldCall('drop_uswapwep');},
  set_twoweap__deps:['$teleportWieldCall'],set_twoweap__sig:'vi',
  set_twoweap:function(a){teleportWieldCall('set_twoweap' ,a);},
  dotwoweapon__deps:['$teleportWieldCall'],dotwoweapon__sig:'i',
  dotwoweapon:function(){return teleportWieldCall('dotwoweapon');},
  uwepgone__deps:['$teleportWieldCall'],uwepgone__sig:'v',
  uwepgone:function(){teleportWieldCall('uwepgone');},
  uswapwepgone__deps:['$teleportWieldCall'],uswapwepgone__sig:'v',
  uswapwepgone:function(){teleportWieldCall('uswapwepgone');},
  uqwepgone__deps:['$teleportWieldCall'],uqwepgone__sig:'v',
  uqwepgone:function(){teleportWieldCall('uqwepgone');},
  untwoweapon__deps:['$teleportWieldCall'],untwoweapon__sig:'v',
  untwoweapon:function(){teleportWieldCall('untwoweapon');},
  chwepon__deps:['$teleportWieldCall'],chwepon__sig:'ipi',
  chwepon:function(a,b){return teleportWieldCall('chwepon' ,a,b);},
  welded__deps:['$teleportWieldCall'],welded__sig:'ip',
  welded:function(a){return teleportWieldCall('welded' ,a);},
  weldmsg__deps:['$teleportWieldCall'],weldmsg__sig:'vp',
  weldmsg:function(a){teleportWieldCall('weldmsg' ,a);},
  mwelded__deps:['$teleportWieldCall'],mwelded__sig:'ip',
  mwelded:function(a){return teleportWieldCall('mwelded' ,a);},
  teleport_wield_test_corpse__deps:['$teleportWieldCall'],teleport_wield_test_corpse__sig:'ip',
  teleport_wield_test_corpse:function(a){return teleportWieldCall('cant_wield_corpse' ,a);},
  teleport_wield_test_weapon__deps:['$teleportWieldCall'],teleport_wield_test_weapon__sig:'ip',
  teleport_wield_test_weapon:function(a){return teleportWieldCall('ready_weapon' ,a);},
  teleport_wield_test_ready__deps:['$teleportWieldCall'],teleport_wield_test_ready__sig:'ip',
  teleport_wield_test_ready:function(a){return teleportWieldCall('ready_ok' ,a);},
  teleport_wield_test_ok__deps:['$teleportWieldCall'],teleport_wield_test_ok__sig:'ip',
  teleport_wield_test_ok:function(a){return teleportWieldCall('wield_ok' ,a);},
  teleport_wield_test_split__deps:['$teleportWieldCall'],teleport_wield_test_split__sig:'vp',
  teleport_wield_test_split:function(a){teleportWieldCall('finish_splitting' ,a);},
  teleport_wield_ready_callback__deps:['$teleportWieldCall'],teleport_wield_ready_callback__sig:'ip',
  teleport_wield_ready_callback:function(a){return teleportWieldCall('ready_ok' ,a);},
  teleport_wield_wield_callback__deps:['$teleportWieldCall'],teleport_wield_wield_callback__sig:'ip',
  teleport_wield_wield_callback:function(a){return teleportWieldCall('wield_ok' ,a);},
});
