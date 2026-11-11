mergeInto(LibraryManager.library,{
 $teleportStripbsServices__deps:['teleport_stripbs_fread','teleport_stripbs_fputc','teleport_stripbs_fflush','teleport_stripbs_fclose','teleport_stripbs_stdin','teleport_stripbs_stdout','teleport_stripbs_errno','teleport_stripbs_metadata','$stackSave','$stackRestore','$stackAlloc'],
 $teleportStripbsServices:function(){return{
  moduleKey:Module,heap:()=>HEAPU8,stackSave:()=>stackSave(),stackRestore:p=>stackRestore(p),stackAlloc:n=>Number(stackAlloc(n)),
  fread:(out,size,count,fp)=>_teleport_stripbs_fread(BigInt(out),BigInt(size),BigInt(count),BigInt(fp)),
  fputc:(ch,fp)=>_teleport_stripbs_fputc(Number(ch)|0,BigInt(fp)),fflush:fp=>_teleport_stripbs_fflush(BigInt(fp)),fclose:fp=>_teleport_stripbs_fclose(BigInt(fp)),
  stdin:()=>_teleport_stripbs_stdin(),stdout:()=>_teleport_stripbs_stdout(),errno:()=>_teleport_stripbs_errno(),
  EOF:_teleport_stripbs_metadata(0),EXIT_FAILURE:_teleport_stripbs_metadata(1),EXIT_SUCCESS:_teleport_stripbs_metadata(2),charSigned:_teleport_stripbs_metadata(3),charSize:_teleport_stripbs_metadata(4),pointerSize:_teleport_stripbs_metadata(5),sizeSize:_teleport_stripbs_metadata(6)
 };},
 teleport_stripbs_main__deps:['$teleportStripbsServices'],teleport_stripbs_main__sig:'iip',
 teleport_stripbs_main:function(argc,argv){return Module['stripbsPort'].main(teleportStripbsServices(),argc,argv);}
});
