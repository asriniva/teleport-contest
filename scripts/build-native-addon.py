"""Generate typed Node-API bindings for the existing C probe exports."""
import argparse
import json
import hashlib
import os
import re
from pathlib import Path
import subprocess
import sys

root=Path(__file__).resolve().parents[1]
work=root/'.cache/tu-probes/native-oracles'
node_headers=root/'.cache/emsdk/node/24.19.0_64bit/include/node'

def decode_stream(text):
    decoder=json.JSONDecoder(); position=0
    while position<len(text):
        while position<len(text) and text[position].isspace():position+=1
        if position==len(text):break
        value,position=decoder.raw_decode(text,position);yield value

def build(name, reference_args=None):
    work.mkdir(parents=True,exist_ok=True)
    old=work/(name+'.c')
    if reference_args is None:
        metadata=json.loads((work/(name+'-build.json')).read_text())
        args=metadata['nativeCommand']
    else:
        compat=work/'include/emscripten';compat.mkdir(parents=True,exist_ok=True)
        (compat/'stack.h').write_text('#pragma once\n#include <stdint.h>\nstatic inline uintptr_t emscripten_stack_get_current(void){return (uintptr_t)__builtin_frame_address(0);}\n')
        (compat/'heap.h').write_text('#pragma once\n#include <stddef.h>\nstatic inline size_t emscripten_get_heap_size(void){return 16UL*1024*1024;}\n')
        probe=root/('scripts/tu-'+name+'-probe.c')
        args=[str(root/'.cache/wasm64-build/host-cc'),'-O2','-ffunction-sections','-fdata-sections','-I'+str(compat.parent),'-DTELEPORT_NATIVE_ORACLE']
        wraps=[]
        for arg in map(str,reference_args[1:]):
            if arg.startswith('-s') or arg=='--no-entry' or arg.endswith('/tu-support.c'):continue
            if arg.startswith('-Wl,--wrap=') and sys.platform=='darwin':wraps.append(arg.split('=',1)[1]);continue
            args.append(str(old) if arg==str(probe) else arg)
        if wraps:
            for symbol in wraps:args.append('-D'+symbol+'=__wrap_'+symbol)
            for i,arg in enumerate(args):
                if Path(arg).name=='hacklib.c':
                    shim=work/(name+'-native-hacklib.c')
                    shim.write_text(''.join('#undef '+symbol+'\n#define '+symbol+' __real_'+symbol+'\n' for symbol in wraps)+'#include '+json.dumps(arg)+'\n')
                    args[i]=str(shim)

    driver=work/(name+'-addon.c')
    probe=root/('scripts/tu-'+name+'-probe.c')
    prelude='#define ORACLE_'+name.upper()+' 1\n'
    prelude+='#include '+json.dumps(str(probe))+'\n' 
    # The real native globals supplied by the previous scenario driver are
    # also needed when all of the existing probe methods are exported.
    storage=''
    if name=='ioctl':storage='__typeof__(gt) gt;struct sysopt_s sysopt;\n'
    if name=='getline':storage='char erase_char,kill_char;\n'
    if name=='version':
        symbol='_regex_id' if sys.platform=='darwin' else 'regex_id'
        storage='struct nomakedefs_s nomakedefs;char native_regex_identifier[11] __asm__('+json.dumps(symbol)+')={0};\n'
    if name == 'exper':storage+='void teleport_native_assert_rtn(const char *function,const char *file,int line,const char *condition){teleport_probe_assert_fail(condition,file,line,function);__builtin_unreachable();}\n'
    driver.write_text(prelude+'\n'+storage)
    compiler=[str(driver) if a==str(old) else a for a in args if a not in ['-Wl,-dead_strip','-Wl,--gc-sections','-Dtime=teleport_oracle_time']]
    if name == 'hacklib':compiler+=['-DTELEPORT_NATIVE_HACKLIB_IO']
    # Query only probe function declarations instead of dumping every header.
    astargs=[a for a in compiler if not a.endswith('.c') or a==str(driver)]
    dump=subprocess.check_output(astargs+['-Xclang','-ast-dump=json','-Xclang','-ast-dump-filter=probe_','-fsyntax-only'],text=True)
    funcs={}
    for node in decode_stream(dump):
        if node.get('kind')=='FunctionDecl' and node.get('name','').startswith('probe_') and any(c.get('kind')=='CompoundStmt' for c in node.get('inner',[])):
            funcs[node['name']]=node
    assert funcs,name
    code='\n#include '+json.dumps(str(root/'scripts/native-addon.h'))+'\n'
    if name == 'hacklib':code+='#include '+json.dumps(str(root/'scripts/native-hacklib-io.h'))+'\n'
    code+='static napi_value native_dispatch(napi_env env,napi_callback_info info){\n napi_value a[32],undefined;napi_get_undefined(env,&undefined);for(int i=0;i<32;i++)a[i]=undefined;size_t argc=32;void *data;napi_get_cb_info(env,info,&argc,a,NULL,&data);\n switch((uintptr_t)data){\n'
    signatures={}
    for index,(fn,node) in enumerate(funcs.items()):
        parameters=[c for c in node.get('inner',[]) if c.get('kind')=='ParmVarDecl']
        types=[p['type'].get('desugaredQualType',p['type']['qualType']) for p in parameters]
        ret=node['type']['qualType'].split('(')[0].strip()
        # Probe APIs contain scalars and pointers only, never structs by value.
        cast=[f'({t})(uintptr_t)native_integer(env,a[{i}])' for i,t in enumerate(types)]
        call=fn+'('+','.join(cast)+')'
        if ret=='void':statement=call+';native_check_stack(stack_before);return native_void(env);'
        elif '*' in ret:statement='uintptr_t result=(uintptr_t)'+call+';native_check_stack(stack_before);return native_unsigned(env,result);'
        elif ret in ['size_t','uintptr_t','uint64_t','unsigned long','unsigned long long']:statement='uint64_t result='+call+';native_check_stack(stack_before);return native_unsigned(env,result);'
        elif ret in ['long','time_t','int64_t','long long']:statement='int64_t result='+call+';native_check_stack(stack_before);return native_signed(env,result);'
        else:statement='double result='+call+';native_check_stack(stack_before);return native_number(env,result);'
        code+=f'case {index}:{{uintptr_t stack_before=native_stack_pointer();{statement}}}\n'
        signatures['_'+fn]={'return':ret,'arguments':types}
    code+='case 100000:return native_number(env,(uintptr_t)teleport_native_malloc(native_integer(env,a[0])));\ncase 100001:free((void*)(uintptr_t)native_integer(env,a[0]));return native_void(env);\n}return native_void(env);}\n'
    code+='NAPI_MODULE_INIT(){napi_value fn;\n'
    exports=[('_'+fn,'native_dispatch',i) for i,fn in enumerate(funcs)]
    exports += [('_malloc','native_dispatch',100000),('_free','native_dispatch',100001),('_read','native_read',0),('_write','native_write',0),('_cstring','native_cstring',0),('_allocated','native_metrics',0),('_stack_status','native_stack_status',0),('_set_clock','native_set_clock',0),('_set_root','native_set_root',0)]
    if name == 'hacklib':exports+=[('_hacklib_set_io','native_hacklib_io_set',0)]
    for label,callback,index in exports:
        code+=f'napi_create_function(env,{json.dumps(label)},NAPI_AUTO_LENGTH,{callback},(void*){index},&fn);napi_set_named_property(env,exports,{json.dumps(label)},fn);\n'
    code+='return exports;}\n'
    driver.write_text(driver.read_text()+code)
    # Track native allocation requests without replacing their libc behavior.
    for function in ['malloc','realloc','calloc']:
        if not any(a.startswith('-D'+function+'=') for a in compiler):compiler+=['-D'+function+'=teleport_native_'+function]
    if name == 'calendar':compiler+=['-Dtime=teleport_native_time']
    if name == 'rnd':compiler+=['-Dfopen=teleport_native_fopen']
    if name == 'exper':compiler+=['-D__assert_rtn=teleport_native_assert_rtn']
    compiler+=['-I'+str(node_headers),'-fvisibility=hidden','-shared']
    if sys.platform=='darwin':compiler+=['-Wl,-dead_strip','-Wl,-undefined,dynamic_lookup']
    subprocess.run(compiler+['-o',str(work/(name+'-native.node'))],check=True,env={**os.environ,'SOURCE_DATE_EPOCH':'1777723200'})
    (work/(name+'-signatures.json')).write_text(json.dumps(signatures,indent=2)+'\n')
    port=next(p for p in json.loads((root/'nethack-c/wasm/tu-ports.json').read_text()) if p['name']==name)
    tracked=[root/('scripts/tu-'+name+'-probe.c'),root/'scripts/native-addon.h',root/'.cache/wasm64-build/tree'/port['source'],root/'nethack-c/upstream'/port['source']]
    tracked+=sorted((root/'.cache/wasm64-build/tree/include').glob('*.h'))
    if name=='hacklib':tracked+=[root/'scripts/native-hacklib-io.h']
    hashes={str(path):hashlib.sha256(path.read_bytes()).hexdigest() for path in tracked}
    body=(root/'.cache/wasm64-build/tree'/port['source']).read_bytes()
    pristine=(root/'nethack-c/upstream'/port['source']).read_bytes()
    manifest={'name':name,'command':compiler,'sourceKind':'upstream-identical' if body==pristine else 'prepared-recorder','hashes':hashes}
    (work/(name+'-full-native-build.json')).write_text(json.dumps(manifest,indent=2)+'\n')
    print('Built full native API',name,flush=True)

if __name__=='__main__':
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('names',nargs='*');options=parser.parse_args()
    command=[sys.executable,'-B',str(root/'scripts/build-tu-probes.py'),'--native-only']
    for name in options.names:command+=['--only',name]
    subprocess.run(command,check=True)
