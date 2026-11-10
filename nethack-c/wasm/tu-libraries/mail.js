// MAIL typed dependency transport; original algorithms remain in JS.
addToLibrary({
 $teleportMailServices__deps:['$lengthBytesUTF8', '$stackAlloc', '$stackRestore', '$stackSave', '$stringToUTF8', 'Hello', 'accessible', 'alloc', 'child', 'debugcore', 'dist2', 'dupstr', 'enexto', 'flush_screen', 'hold_another_object', 'isok', 'makemon', 'mksobj', 'mongone', 'new_omailcmd', 'newsym', 'nh_getenv', 'nh_terminate', 'oname', 'place_monster', 'strcat', 'strcpy', 'strlen', 'teleport_mail_config_string', 'teleport_mail_delay', 'teleport_mail_display', 'teleport_mail_execl', 'teleport_mail_free', 'teleport_mail_getpwuid', 'teleport_mail_getuid', 'teleport_mail_global', 'teleport_mail_hero_bit', 'teleport_mail_literal_capacity', 'teleport_mail_literal_storage', 'teleport_mail_never_mind', 'teleport_mail_pline0', 'teleport_mail_pline1', 'teleport_mail_pline_ipi', 'teleport_mail_rn2', 'teleport_mail_stat', 'teleport_mail_storage', 'teleport_mail_verbalize', 'teleport_mail_win_message'],
 $teleportMailServices:function(){
  var state=Module['teleportMailLiterals']||={next:0,strings:new Map()};
  var pointer=value=>BigInt.asUintN(64,BigInt(value?.address??value??0));
  var coord=value=>Number(BigInt.asIntN(16,BigInt(value)));
  var byte=value=>Number(BigInt.asIntN(8,BigInt(value)));
  var literal=value=>{
   if(state.strings.has(value))return state.strings.get(value);
   var size=lengthBytesUTF8(value)+1;
   if(state.next+size>Number(_teleport_mail_literal_capacity()))throw new Error('Review changed MAIL literal corpus');
   var at=Number(_teleport_mail_literal_storage())+state.next;
   stringToUTF8(value,at,size);state.next+=size;state.strings.set(value,at);return at;
  };
  var text=value=>typeof value==='string'?BigInt(literal(value)):pointer(value);
  return {moduleKey:Module,heap:()=>HEAPU8,literal,
   stackSave:()=>stackSave(),stackRestore:saved=>stackRestore(saved),stackAlloc:size=>Number(stackAlloc(size)),
   global:index=>Number(_teleport_mail_global(index)),storage:index=>Number(_teleport_mail_storage(index)),
   heroBit:index=>_teleport_mail_hero_bit(index),winMessage:()=>_teleport_mail_win_message(),neverMind:()=>Number(_teleport_mail_never_mind()),
   configString:index=>Number(_teleport_mail_config_string(index)),
   pline:(format,...args)=>{
    if(args.length===0)return _teleport_mail_pline0(text(format));
    if(args.length===1)return _teleport_mail_pline1(text(format),text(args[0]));
    if(args.length===3)return _teleport_mail_pline_ipi(text(format),Number(args[0])|0,text(args[1]),Number(args[2])|0);
    throw new Error('Unexpected original MAIL pline shape');
   },
   verbalize:(format,...args)=>_teleport_mail_verbalize(text(format),text(args[0]),text(args[1]),text(args[2])),
   rn2:(bound,line,caller)=>{var site=caller==='md_stop'?0:caller==='md_rush'?1:-1;
    if(site<0||line!==[261,340][site])throw new Error('Unexpected MAIL RNG site');return _teleport_mail_rn2(Number(bound)|0,site);},
   nh_getenv:(a)=>Number(_nh_getenv(text(a))),
   dupstr:(a)=>Number(_dupstr(text(a))),
   alloc:(a)=>Number(_alloc(Number(a)>>>0)),
   strlen:(a)=>Number(_strlen(text(a))),
   Strcpy:(a,b)=>Number(_strcpy(text(a),text(b))),
   Strcat:(a,b)=>Number(_strcat(text(a),text(b))),
   stat:(a,b)=>_teleport_mail_stat(text(a),pointer(b)),
   getuid:()=>_teleport_mail_getuid(),
   getpwuid:(a)=>Number(_teleport_mail_getpwuid(Number(a)>>>0)),
   execl:(a,b,c)=>_teleport_mail_execl(text(a),text(b),pointer(c)),
   free:(a)=>_teleport_mail_free(pointer(a)),
   enexto:(a,b,c,d)=>_enexto(pointer(a),coord(b),coord(c),pointer(d)),
   dist2:(a,b,c,d)=>_dist2(coord(a),coord(b),coord(c),coord(d)),
   isok:(a,b)=>_isok(coord(a),coord(b)),
   accessible:(a,b)=>_accessible(coord(a),coord(b)),
   newsym:(a,b)=>_newsym(coord(a),coord(b)),
   place_monster:(a,b,c)=>_place_monster(pointer(a),coord(b),coord(c)),
   flush_screen:(a)=>_flush_screen(Number(a)|0),
   nh_delay_output:()=>_teleport_mail_delay(),
   display_nhwindow:(a,b)=>_teleport_mail_display(Number(a)|0,byte(b)),
   makemon:(a,b,c,d)=>Number(_makemon(pointer(a),coord(b),coord(c),Number(d)>>>0)),
   Hello:(a)=>Number(_Hello(pointer(a))),
   mksobj:(a,b,c)=>Number(_mksobj(Number(a)|0,byte(b),byte(c))),
   oname:(a,b,c)=>Number(_oname(pointer(a),text(b),Number(c)>>>0)),
   new_omailcmd:(a,b)=>_new_omailcmd(pointer(a),text(b)),
   hold_another_object:(a,b,c,d)=>Number(_hold_another_object(pointer(a),text(b),text(c),text(d))),
   mongone:(a)=>_mongone(pointer(a)),
   child:(a)=>_child(Number(a)|0),
   nh_terminate:(a)=>_nh_terminate(Number(a)|0),
   debugcore:(a,b)=>_debugcore(text(a),byte(b)),
  };
 },
 $teleportMailCall__deps:['$teleportMailServices','$stackSave','$stackRestore'],
 $teleportMailCall:function(name,...args){var saved=stackSave();try{return Module['nethackPorted'].mail(teleportMailServices(),name,...args);}finally{stackRestore(saved);}},
 free_maildata__deps:['$teleportMailCall'],free_maildata__sig:'v',
 free_maildata:function(){return teleportMailCall('free_maildata');},
 getmailstatus__deps:['$teleportMailCall'],getmailstatus__sig:'v',
 getmailstatus:function(){return teleportMailCall('getmailstatus');},
 ckmailstatus__deps:['$teleportMailCall'],ckmailstatus__sig:'v',
 ckmailstatus:function(){return teleportMailCall('ckmailstatus');},
 ck_server_admin_msg__deps:['$teleportMailCall'],ck_server_admin_msg__sig:'v',
 ck_server_admin_msg:function(){return teleportMailCall('ck_server_admin_msg');},
 readmail__deps:['$teleportMailCall'],readmail__sig:'vp',
 readmail:function(a){return teleportMailCall('readmail',a);},
 teleport_mail_test_start__deps:['$teleportMailCall'],teleport_mail_test_start__sig:'ip',
 teleport_mail_test_start:function(a){return teleportMailCall('md_start',a);},
 teleport_mail_test_stop__deps:['$teleportMailCall'],teleport_mail_test_stop__sig:'ipp',
 teleport_mail_test_stop:function(a,b){return teleportMailCall('md_stop',a,b);},
 teleport_mail_test_rush__deps:['$teleportMailCall'],teleport_mail_test_rush__sig:'ipii',
 teleport_mail_test_rush:function(a,b,c){return teleportMailCall('md_rush',a,b,c);},
 teleport_mail_test_new__deps:['$teleportMailCall'],teleport_mail_test_new__sig:'vp',
 teleport_mail_test_new:function(a){return teleportMailCall('newmail',a);},
 teleport_mail_test_state__deps:['$teleportMailCall'],teleport_mail_test_state__sig:'ji',
 teleport_mail_test_state:function(a){return teleportMailCall('$state',a);},
 teleport_mail_test_reset__deps:['$teleportMailCall'],teleport_mail_test_reset__sig:'v',
 teleport_mail_test_reset:function(){teleportMailCall('$reset');},
});
