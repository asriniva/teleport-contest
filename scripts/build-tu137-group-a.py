"""Owned isolated Group A branches. Called only by composed shadow builder."""
from pathlib import Path
import hashlib,json,subprocess

def build_group_a(root,sdk,work,name):
    root,sdk,work=Path(root),Path(sdk),Path(work)
    recipes=json.loads((root/'nethack-c/wasm/tu-fragments/tu137-group-a-probes.json').read_text())
    if name not in recipes:return False
    recipe=recipes[name];src=root/'.cache/wasm64-build/tree/src'
    out=work/'uhitm' if name=='uhitm' else work;out.mkdir(parents=True,exist_ok=True)
    defines=['-D'+d for d in json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())]
    includes={'prepared/src':src,'prepared/include':src.parent/'include','ncurses/include':root/'.cache/ncurses-wasm64-build/include','scripts':root/'scripts'}
    flags=[*recipe['flags'],*defines,*['-I'+str(includes[d]) for d in recipe['includeDirs']]]
    if recipe['forceInclude']:flags+=['-include',str(root/recipe['forceInclude'])]
    flags+=['-sEXPORTED_RUNTIME_METHODS='+json.dumps(recipe['runtimeMethods']),'-sEXPORTED_FUNCTIONS='+json.dumps(recipe['exactExports']),recipe['prefixMap'].replace('{ROOT}',str(root))]
    emcc=str(sdk/'upstream/emscripten/emcc')
    dependencies=[]
    if name=='hack':
        pieces=(src/'hacklib.c').read_text().split('/*=');assert len(pieces)==2,'Original deterministic sort prefix boundary'
        target=work/'hack-sort-dependency.c';target.write_text(pieces[0]);dependencies=[target]
    elif name=='shk':
        # Same separate non-LTO true dependency compilation as author build.
        depflags=['-O2','-g','-sMEMORY64=1',*defines,'-I'+str(src.parent/'include'),'-I'+str(root/'.cache/ncurses-wasm64-build/include'),'-include',str(root/'nethack-c/wasm/native-terminal.h')]
        for dependency in recipe['dependenciesBothModes']:
            source=src/Path(dependency).name;target=work/('shk-dependency-'+source.stem+'.o')
            subprocess.run([emcc,*depflags,'-c',str(source),'-o',str(target)],check=True,cwd=root)
            dependencies.append(target)
    else:
        for dependency in recipe['dependenciesBothModes']:
            dependencies.append(src/Path(dependency).name if dependency.startswith('prepared/src/') else root/dependency)
    for mode in ['reference','hybrid']:
        modeflags=[]
        if mode=='reference' and recipe['referenceDefine']:modeflags+=['-D'+recipe['referenceDefine']]
        if mode=='hybrid':
            modeflags+=['-D'+d for d in recipe['hybridDefines']]
            if name=='mon':modeflags += [str(root/'.cache/mon-author/support.c')]
            modeflags+=['--js-library',str(root/('nethack-c/wasm/tu-libraries/'+name+'.js'))]
        command=[emcc,*flags,str(root/recipe['fixture']),*map(str,dependencies),*modeflags,'-o',str(out/recipe['outputNames'][mode])]
        # Preserve author profiles and source spelling; no generic common support,
        # native-libc library, original algorithm source append or addon fallback.
        (out/(name+'-'+mode+'-command.json')).write_text(json.dumps(command,indent=2)+'\n')
        subprocess.run(command,check=True,cwd=src if name=='pickup' else root)
    for mapping in recipe.get('extraOutputCopies',[])+recipe.get('extraOutputMetadata',[]):
        source=root/mapping['from'];target=root/mapping['to'];target.parent.mkdir(parents=True,exist_ok=True)
        data=source.read_bytes();target.write_bytes(data)
        assert hashlib.sha256(target.read_bytes()).digest()==hashlib.sha256(data).digest()
    return True
