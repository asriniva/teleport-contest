// Only typed imports. All six original policy bodies live in private core.mjs.
addToLibrary({
 xpmgetline__sig:'p',xpmgetline:function(){return BigInt(Module.xpm2iff('xpmgetline',[]));},
 fopen_xpm_file__sig:'ip',fopen_xpm_file:function(fn){return Module.xpm2iff('fopen_xpm_file',[fn]);},
 conv_image__sig:'vi',conv_image:function(nplanes){Module.xpm2iff('conv_image',[nplanes]);},
 wr32__sig:'vi',wr32:function(v){Module.xpm2iff('wr32',[v>>>0]);},
 write_chunk__sig:'vppi',write_chunk:function(id,data,size){Module.xpm2iff('write_chunk',[id,data,size>>>0]);},
 utility_main__sig:'iip',utility_main:function(argc,argv){return Module.xpm2iff('main',[argc,argv]);}
});
