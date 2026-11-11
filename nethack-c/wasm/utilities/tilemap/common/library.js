addToLibrary({
teleport_tm_name__sig:'piii',teleport_tm_name:function(a,b,c){return BigInt(Module.utilityInvoke('tilename',a,b,c));},
teleport_tm_acceptable__sig:'iiipp',teleport_tm_acceptable:function(a,b,c,d){return Module.utilityInvoke('acceptable_tilename',a,b,Number(c),Number(d));},
teleport_tm_precheck__sig:'vip',teleport_tm_precheck:function(a,b){Module.utilityInvoke('precheck',a,Number(b));},
teleport_tm_add__sig:'viiiipp',teleport_tm_add:function(a,b,c,d,e,f){Module.utilityInvoke('add_tileref',a,b,c,d,Number(e),Number(f));},
teleport_tm_dump__sig:'vp',teleport_tm_dump:function(a){Module.utilityInvoke('dump_tilerefs',Number(a));},
teleport_tm_free__sig:'v',teleport_tm_free:function(){Module.utilityInvoke('free_tilerefs');}
});
