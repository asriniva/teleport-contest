#!/usr/bin/env python3
"""Isolated complete prepared-C game. Never invoke the shared build/port tools."""
import argparse,concurrent.futures,hashlib,json,os,re,shlex,shutil,subprocess
from pathlib import Path
p=argparse.ArgumentParser();p.add_argument('--reference-root',type=Path,required=True);p.add_argument('--out',type=Path,required=True);p.add_argument('--jobs',type=int,default=1);p.add_argument('--abi-only',action='store_true');a=p.parse_args()
root=Path(__file__).resolve().parents[1];ref=a.reference_root.resolve();private=a.out.resolve();accepted=ref/'.cache/wasm64-build';sdk=ref/'.cache/emsdk/upstream/emscripten';emcc=sdk/'emcc';source_tree=accepted/'tree';pristine=ref/'nethack-c/upstream'
if private.exists():raise SystemExit('Use a fresh private output directory')
if not private.is_relative_to(root/'.cache') or private==root/'.cache' or private.is_relative_to(accepted):raise SystemExit('Output must be a NEW private .cache child outside accepted build')
if a.jobs<1 or a.jobs>4:raise SystemExit('Choose 1..4 compile jobs; coordinate concurrent builds')
pin=subprocess.check_output(['git','-C',str(pristine),'rev-parse','HEAD'],text=True).strip();assert pin=='16ff59115315917b93185d026aeefea06db9b0f4'
private.mkdir(parents=True);out=private/'out';out.mkdir();deps=private/'deps';deps.mkdir();obj=private/'obj';obj.mkdir();tree=private/'tree'
env={**os.environ,'SOURCE_DATE_EPOCH':'1777723200','TZ':'UTC'}
commands=[];inputs=set();artifacts=set();sha=lambda path:hashlib.sha256(path.read_bytes()).hexdigest()
def run(command,log):
 command=list(map(str,command));commands.append(command);result=subprocess.run(command,capture_output=True,text=True,env=env)
 log.write_text(result.stdout+result.stderr)
 if result.returncode:raise RuntimeError(result.stderr[-10000:])
 return result.stdout
def check_sources(paths):
 return {str(path):sha(path)for path in sorted(set(paths))}
abi=json.loads((root/'js/platform/darwin/terminal-abi.json').read_text());n,w=abi['native'],abi['wire'];nc,wc=abi['nativeConstants'],abi['wireConstants'];tables=[]
tables+=['#define ABI_NATIVE_SIZE '+str(n['termioSize']),'#define ABI_WIRE_SIZE '+str(w['termioSize']),'#define ABI_NATIVE_VDISABLE '+str(n['_PC_VDISABLE']),'#define ABI_WIRE_VDISABLE '+str(w['_PC_VDISABLE'])]
tables+=['static const int abi_size[]={'+str(n['termioSize'])+','+str(w['termioSize'])+'};','static const int abi_width[]={8,4};','static const int abi_speed_width[]={8,4};','static const int abi_cc[]={'+str(n['c_cc'])+','+str(w['c_cc'])+'};','static const int abi_offsets[2][4]={'+','.join('{'+','.join(str(row[k])for k in ['c_iflag','c_oflag','c_cflag','c_lflag'])+'}'for row in [n,w])+'};']
groups=['IGNBRK BRKINT IGNPAR PARMRK INPCK ISTRIP INLCR IGNCR ICRNL IXON IXOFF IXANY IMAXBEL IUTF8','OPOST ONLCR OCRNL ONOCR ONLRET OFILL OFDEL','CLOCAL CREAD CSTOPB HUPCL PARENB PARODD CRTSCTS','ECHO ECHOE ECHOK ECHONL ICANON ISIG IEXTEN TOSTOP NOFLSH ECHOKE ECHOCTL PENDIN FLUSHO EXTPROC']
bits=['{'+str(i)+',{'+str(nc[k])+'ULL,'+str(wc[k])+'ULL}}'for i,g in enumerate(groups)for k in g.split()if k in nc and k in wc]
tables+=['static const struct {int field;uint64_t value[2];} abi_bits[]={'+','.join(bits)+'};']
multi=[]
for field,mask,keys in [(2,'CSIZE',['CS5','CS6','CS7','CS8']),(1,'TABDLY',['TAB0','TAB1','TAB2','TAB3'])]:
 if mask in nc and mask in wc:
  keys=[k for k in keys if k in nc and k in wc];multi.append('{'+str(field)+','+str(len(keys))+',{'+str(nc[mask])+','+str(wc[mask])+'},{'+','.join('{'+str(nc[k])+','+str(wc[k])+'}'for k in keys)+'}}')
tables+=['static const struct {int field,count;uint64_t mask[2],value[5][2];} abi_multi[]={'+','.join(multi)+'};']
controls='VEOF VEOL VEOL2 VERASE VWERASE VKILL VREPRINT VINTR VQUIT VSUSP VDSUSP VSTART VSTOP VLNEXT VDISCARD VMIN VTIME VSTATUS'.split()
tables+=['static const int abi_control[][2]={'+','.join('{'+str(nc[k])+','+str(wc[k])+'}'for k in controls if k in nc and k in wc)+'};','static const uint64_t abi_baud[][2]={'+','.join('{'+str(n[k])+','+str(w[k])+'}'for k in n if re.fullmatch(r'B\d+',k)and k in w)+'};']
table=deps/'full-original-c-native-tables.h';table.write_text('\n'.join(tables)+'\n');inputs.update([table,root/'js/platform/darwin/terminal-abi.json',root/'js/platform/darwin/terminal.js',root/'nethack-c/wasm/native-terminal.h',root/'nethack-c/wasm/full-original-c-native.c',root/'scripts/full-original-c-abi-probe.c',Path(__file__).resolve()])
common=['-O2','-g','-sMEMORY64=1','-I'+str(deps)];native_header=root/'nethack-c/wasm/native-terminal.h';native_obj=obj/'native.o';probe_obj=obj/'abi-probe.o'
run([emcc,*common,'-c',root/'nethack-c/wasm/full-original-c-native.c','-o',native_obj],private/'native-compile.log')
run([emcc,*common,'-include',native_header,'-c',root/'scripts/full-original-c-abi-probe.c','-o',probe_obj],private/'abi-probe-compile.log')
exports=['full_abi_buffer','full_abi_errno','full_abi_op','full_abi_regex','full_abi_native_size','full_abi_signal','full_sdk_regex','full_sdk_signal','malloc','free']
runtime=['-sMODULARIZE=1','-sEXPORT_ES6=1','-sENVIRONMENT=node','-sALLOW_MEMORY_GROWTH=1','-sFORCE_FILESYSTEM=1','-sEXPORTED_RUNTIME_METHODS=FS,ENV,callMain,HEAPU8']
abi_runtime=[x.replace('FS,ENV,callMain,HEAPU8','FS,ENV,HEAPU8')for x in runtime]
run([emcc,*common,*abi_runtime,'--no-entry','-sEXPORTED_FUNCTIONS='+json.dumps(['_'+s for s in exports]),native_obj,probe_obj,'-o',out/'abi.mjs'],private/'abi-link.log')
artifacts.update([out/'abi.mjs',out/'abi.wasm'])
node=ref/'.cache/emsdk/node/24.19.0_64bit/bin/node';test=root/'scripts/full-original-c-test-abi.mjs';inputs.add(test)
run([node,test,'--reference',out/'abi.mjs'],private/'abi-test.log')
if not a.abi_only:
 # Copy only source/generated inputs; no accepted objects/stamps/host tools.
 def ignore(directory,names):return [name for name in names if name in ['.git','wasm','Sysunix','nethack','makedefs','dgn_comp','lev_comp','recover']or name.endswith(('.o','.a','.d','.dylib'))]
 shutil.copytree(source_tree,tree,ignore=ignore)
 text=(tree/'src/Makefile').read_text();start='# BEGIN JAVASCRIPT TUS';end='# END JAVASCRIPT TUS'
 assert text.count(start)==1 and text.count(end)==1
 before,tail=text.split(start,1);_,after=tail.split(end,1);(tree/'src/Makefile').write_text(before+after)
 original=(pristine/'sys/unix/Makefile.src').read_text().replace('\\\n',' ')
 configured=before.replace('\\\n',' ')
 def var(text,key):
  m=re.search(r'^'+key+r'\s*(?:\?=|=)\s*(.*)$',text,re.M);return m[1]if m else ''
 assert var(original,'HOBJ')==var(configured,'HOBJ'),'Configured HOBJ differs from pristine source list'
 values={'TARGETPFX':'obj/','REGEXOBJ':'$(TARGETPFX)posixregex.o','RANDOBJ':'','SYSOBJ':var(original,'SYSOBJ'),'WINOBJ':var(original,'WINTTYOBJ'),'HINTOBJ':'','SNDLIBOBJ':'','UUIDOBJ':''}
 def expand(value):
  for i in range(10):
   if '$('not in value:return value.split()
   value=re.sub(r'\$\((\w+)\)',lambda m:values[m[1]],value)
  raise RuntimeError('Unexpanded original Makefile source selection')
 selected=expand(var(original,'HOBJ'))+expand(var(original,'DATE_O'))+expand(var(original,'TARGET_HACKLIB'))
 assert len(selected)==140 and len(set(selected))==140
 source_list=[]
 for target in selected:
  stem=Path(target).stem;candidates=[tree/f'{directory}/{stem}.c'for directory in ['src','sys/share','sys/unix','win/tty']];found=[q for q in candidates if q.exists()]
  assert len(found)==1,(target,found);source_list.append((target,found[0]))
 (private/'original-link-selection.json').write_text(json.dumps([{'target':t,'source':str(s.relative_to(tree))}for t,s in source_list],indent=2)+'\n')
 # Explicit prepared/pristine source inventory, including generated inputs.
 differences=[]
 for q in sorted(tree.rglob('*')):
  if not q.is_file():continue
  rel=q.relative_to(tree);old=pristine/rel
  if not old.exists()or sha(q)!=sha(old):differences.append({'path':str(rel),'pristineSha256':sha(old)if old.is_file()else None,'preparedSha256':sha(q)})
 (private/'prepared-pristine-differences.json').write_text(json.dumps(differences,indent=2)+'\n')
 inputs.update([pristine/'sys/unix/Makefile.src',source_tree/'src/Makefile',root/'nethack-c/wasm/build.py',root/'nethack-c/wasm/compile-defines.json',*sorted((root/'nethack-c/patches').glob('*.patch'))])
 # All generated backing refers to REAL original definitions, never fixtures.
 rows=json.loads((root/'js/nethack/decl-storage.json').read_text())['globals'];inputs.add(root/'js/nethack/decl-storage.json')
 for suffix,expression in [('names',lambda r:json.dumps(r['name'])),('addresses',lambda r:'&'+r['name']),('sizes',lambda r:'sizeof('+r['name']+')')]:
  q=deps/('full-global-'+suffix+'.inc');q.write_text(''.join('case '+str(i)+':return '+expression(r)+';\n'for i,r in enumerate(rows)));inputs.add(q)
 observer=root/'scripts/full-original-c-observers.c';inputs.add(observer)
 flags=[*common,'-D'+str('FULL_GLOBAL_COUNT='+str(len(rows))),'-include',str(native_header),'-I'+str(tree/'include'),'-I'+str(tree/'src'),'-I'+str(tree/'win/tty'),'-I'+str(tree/'lib/lua-5.4.8/src'),'-I'+str(ref/'.cache/ncurses-wasm64-build/include'),*['-D'+x for x in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())],'-fmacro-prefix-map='+str(tree/'src')+'/=']
 cfiles=[(s,obj/(Path(t).stem+'.o'))for t,s in source_list if s.name!='decl.c']
 # Same original RNG owner, with read-only private-state access appended.
 rnd=deps/'rnd-observed.c';rnd.write_text('#include '+json.dumps(str(tree/'src/rnd.c'))+'\nconst void *full_rng_state(int i){if(i<0||i>1)abort();return &rnglist[i].rng_state;}\nsize_t full_rng_size(void){return sizeof(isaac64_ctx);}\nuintptr_t full_rng_function(int display){return (uintptr_t)(display?(rn2_on_display_rng):(rn2));}\n')
 cfiles=[(rnd if s.name=='rnd.c'else s,o)for s,o in cfiles];cfiles.append((observer,obj/'observers.o'))
 lua=tree/'lib/lua-5.4.8/src';luafiles=sorted(q for q in lua.glob('*.c')if q.stem not in ['lua','luac','onelua']);assert len(luafiles)==32
 def compile_one(row):
  source,target=row;localflags=flags if source not in luafiles else [*common,'-DLUA_USE_POSIX','-I'+str(lua)]
  run([emcc,*localflags,'-c',source,'-o',target],private/('compile-'+target.stem+'.log'))
  return source,target
 cfiles += [(q,obj/('lua-'+q.stem+'.o'))for q in luafiles]
 with concurrent.futures.ThreadPoolExecutor(max_workers=a.jobs)as pool:list(pool.map(compile_one,cfiles))
 for src,dest in [('bridge',root/'nethack-c/wasm/bridge.c'),('compress',root/'nethack-c/wasm/compress-service.c')]:
  target=obj/(src+'.o');run([emcc,*common,'-c',dest,'-o',target],private/(src+'-compile.log'));cfiles.append((dest,target))
 tinfo=deps/'libtinfo.a';shutil.copy2(ref/'.cache/ncurses-wasm64-build/lib/libtinfo.a',tinfo);inputs.update([tinfo,ref/'.cache/ncurses-wasm64-build/teleport-config.txt',root/'nethack-c/wasm/build_terminfo.py',ref/'.cache/ncurses-6.5.tar.gz'])
 assets=private/'assets';shutil.copytree(accepted/'assets',assets)
 # Keep actual process exit status in this reference worker, not host exit.
 post=deps/'exit-transport.js';post.write_text('quit_ = (status, exception) => { throw exception; };\n')
 nm=ref/'.cache/emsdk/upstream/bin/llvm-nm';objects=[o for s,o in cfiles]
 symbols=run([nm,'--defined-only','--extern-only','--format=posix',*objects,native_obj],private/'defined-symbols.log')
 names=sorted(set(re.findall(r'^([A-Za-z_]\w*) T ',symbols,re.M))-{'main','__main_argc_argv'})
 game_exports=['_main',*['_'+n for n in names],'_malloc','_free']
 link=[emcc,*common,*runtime,'-sINVOKE_RUN=0','-sEXIT_RUNTIME=1','-sSTACK_SIZE=4194304','-sEXPORTED_FUNCTIONS='+json.dumps(game_exports),'--emit-symbol-map','--post-js',post,'--embed-file',str(assets)+'@/nethack',*objects,native_obj,tinfo,'-lm','-o',out/'game.mjs']
 run(link,private/'game-link.log');artifacts.update([out/'game.mjs',out/'game.wasm',out/'game.mjs.symbols'])
 # Source dependency closure comes from compiler dependency output, not a TU registry.
 for source,target in cfiles:
  localflags=flags if source not in luafiles else [*common,'-DLUA_USE_POSIX','-I'+str(lua)]
  deptext=run([emcc,*localflags,'-M',source],private/('deps-'+target.stem+'.log'))
  inputs.update(Path(x).resolve()for x in shlex.split(deptext.split(':',1)[1].replace('\\\n','')))
 inputs.update(q for q in assets.rglob('*')if q.is_file());inputs.update(q for q in deps.rglob('*')if q.is_file());inputs.update([private/'original-link-selection.json',private/'prepared-pristine-differences.json'])
 # Copy-based staging: accepted source hashes are also bound independently.
 inputs.update(source_tree/s.relative_to(tree)for t,s in source_list)
 inputs.update([root/'nethack-c/wasm/vendor/ncompress/compress.c',root/'nethack-c/wasm/vendor/ncompress/patchlevel.h'])
 # No port modules/JS algorithm dispatch: only built-in SDK + explicit EM_JS I/O.
 run([node,root/'scripts/full-original-c-check-imports.mjs',out/'game.wasm'],private/'imports-check.log')
inputs.update([sdk/'emcc',ref/'.cache/emsdk/upstream/bin/clang',*sorted((sdk/'src/lib').glob('lib*.js'))])
(private/'commands.json').write_text(json.dumps(commands,indent=2)+'\n');inputs.add(private/'commands.json')
(private/'receipt.json').write_text(json.dumps({'profile':'complete prepared original C, SDK musl/TRE, C Lua5.4.8, C ncurses/ncompress; native ABI transport in C','upstream':pin,'gameTranslationUnits':0 if a.abi_only else 140,'luaTranslationUnits':0 if a.abi_only else 32,'syntheticGameGlobals':[],'abortBoundaries':[],'portedTranslationUnits':[],'buildEnvironment':{k:env[k]for k in ['SOURCE_DATE_EPOCH','TZ']},'sourceSha256':check_sources(inputs),'artifactSha256':{str(q.relative_to(private)):sha(q)for q in sorted(artifacts)}},indent=2)+'\n')
print('Prepared full original-C reference:',private,flush=True)
