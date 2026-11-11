addToLibrary({
recover_js_main__sig:'iip',recover_js_main:function(argc,argv){return Module.recoverPort('main',argc,argv);},
recover_js_set_levelfile_name__sig:'vi',recover_js_set_levelfile_name:function(lev){Module.recoverPort('set_levelfile_name',lev);},
recover_js_open_levelfile__sig:'ii',recover_js_open_levelfile:function(lev){return Module.recoverPort('open_levelfile',lev);},
recover_js_create_savefile__sig:'i',recover_js_create_savefile:function(){return Module.recoverPort('create_savefile');},
recover_js_restore_savefile__sig:'ip',recover_js_restore_savefile:function(basename){return Module.recoverPort('restore_savefile',basename);},
});
