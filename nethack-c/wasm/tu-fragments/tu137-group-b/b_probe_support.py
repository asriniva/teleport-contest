"""Parent-consumed isolated probe helpers. Not executed by group B.

Copy beside b-probe-commands.json in the shadow clone. Parent imports functions
from its composed builder; no top-level build/import of game or probe modules.
"""
from pathlib import Path
import ast,hashlib,json,os,re,shlex,subprocess

AUTHOR_ROOT=Path('/Users/arj/Desktop/nethack_comp/teleport-contest')
DATA=Path(__file__).with_name('b-probe-commands.json')

def _root(value):
    root=Path(value).resolve()
    allowed=AUTHOR_ROOT/'.cache/tu137-shadow-integration'
    if root!=AUTHOR_ROOT and not root.is_relative_to(allowed):
        raise ValueError('B helpers require exact live root or a parent private shadow root')
    return root

def _write(root,path,data):
    path=Path(path)
    if not path.resolve().is_relative_to(root):raise ValueError('Output escapes shadow root')
    path.parent.mkdir(parents=True,exist_ok=True)
    if isinstance(data,str):path.write_text(data)
    else:path.write_bytes(data)

def _sdk(root,value=None):
    return Path(value or os.environ.get('EMSDK',str(AUTHOR_ROOT/'.cache/emsdk'))).resolve()

def _path_word(word,root,sdk):
    old=str(AUTHOR_ROOT);old_sdk=str(AUTHOR_ROOT/'.cache/emsdk')
    if word==old_sdk or word.startswith(old_sdk+'/'):return str(sdk)+word[len(old_sdk):]
    if word==old or word.startswith(old+'/'):return str(root)+word[len(old):]
    return word

def rebase_command(command,root,sdk=None):
    root=_root(root);sdk=_sdk(root,sdk);out=[]
    for word in command:
        transformed=_path_word(word,root,sdk)
        if transformed==word:
            for prefix in ['-I','-L','-isystem=','-fmacro-prefix-map=','-ffile-prefix-map=']:
                if word.startswith(prefix):
                    value=word[len(prefix):]
                    if prefix.endswith('prefix-map='):
                        left,sep,right=value.partition('=')
                        transformed=prefix+_path_word(left,root,sdk)+sep+right
                    else:transformed=prefix+_path_word(value,root,sdk)
                    break
        # SDK is the one explicit same-pinned external path exception.
        residual=transformed.replace(str(root),'').replace(str(sdk),'')
        if str(AUTHOR_ROOT) in residual:
            raise ValueError('Unhandled original-root command word: '+word)
        out.append(transformed)
    return out

def commands_for(root,name,variant='default',sdk=None):
    data=json.loads(DATA.read_text())
    if name not in data['commands']:raise ValueError(name)
    modes=data['commands'][name]
    if name=='termcap':modes=modes[variant]
    elif variant!='default':raise ValueError('Variant only supported for TERMCAP')
    result={}
    for mode,record in modes.items():
        if mode=='dependencyCommands':
            result[mode]=[{'cwd':_path_word(row['cwd'],_root(root),_sdk(root,sdk)),
                           'command':rebase_command(row['command'],root,sdk)} for row in record]
        else:result[mode]={'cwd':str(_root(root)),'command':rebase_command(record['command'],root,sdk)}
    return result

def export_arg(name,mode='reference',variant='default'):
    data=json.loads(DATA.read_text())
    if name=='termcap':
        values=data['exports'][name][variant][mode]
        command=data['commands'][name][variant][mode]['command']
    else:
        values=data['exports'][name][mode]
        command=data['commands'][name][mode]['command']
    if len(values)!=len(set(values)):raise ValueError('Duplicate native export')
    tokens=[arg for arg in command if arg.startswith('-sEXPORTED_FUNCTIONS=')]
    if len(tokens)!=1 or json.loads(tokens[0].split('=',1)[1])!=values:
        raise ValueError('Exact command/export map mismatch')
    return tokens[0]

def validate_wintty_choice(root,command):
    root=_root(root);data=json.loads(DATA.read_text())['winttyChoice']
    for path,pin in data['files'].items():
        if hashlib.sha256((root/path).read_bytes()).hexdigest()!=pin:
            raise ValueError('WINTTY observer fixture/test choice mismatch: '+path)
    args=[arg for arg in command if arg.startswith('-sEXPORTED_FUNCTIONS=')]
    if len(args)!=1:raise ValueError('WINTTY export argument missing/duplicated')
    exports=json.loads(args[0].split('=',1)[1])
    if len(exports)!=40 or exports[-4:]!=data['fourGetterExports']:
        raise ValueError('WINTTY must use coherent reviewed40-export observer choice')

def materialize_fixture_inputs(root,name):
    root=_root(root);work=root/'.cache/tu-probes';data=json.loads(DATA.read_text())
    if name=='trap':_write(root,work/'trap-fixture-library.js',data['trapFixtureLibrary'])
    elif name=='wintty':
        text=(root/'js/ported/wintty.js').read_text()
        tokens=re.finditer(r'/\*[\s\S]*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'',text)
        literals={ast.literal_eval(m[0])for m in tokens if m[0].startswith(('"',"'"))}
        capacity=sum(len(x.encode())+1 for x in literals)
        _write(root,work/'wintty-support.c','#define TELEPORT_WINTTY_LITERAL_CAPACITY '+str(capacity)+'\n#include "'+str(root/'nethack-c/wasm/tu-wintty-support.inc')+'"\n')
    elif name=='sp_lev':
        library=(root/'nethack-c/wasm/tu-libraries/sp_lev.js').read_text()
        for old,new in data['spLevFixtureReplacements']:
            if library.count(old)!=1:raise ValueError('SP_LEV exact fixture-library anchor: '+old)
            library=library.replace(old,new)
        _write(root,work/'sp_lev-fixture-library.js',library)

def write_runner_aliases(root,names=None):
    root=_root(root);work=root/'.cache/tu-probes'
    selected=set(names if names is not None else ['trap','topl','wintty'])
    if not selected.issubset({'trap','topl','wintty'}):raise ValueError('Unknown alias unit')
    for name,prefix in [('trap','probe-'),('topl',''),('wintty','')]:
        if name not in selected:continue
        for mode in ['reference','hybrid']:
            for suffix in ['mjs','wasm']:
                if not (work/f'{name}-{mode}.{suffix}').is_file():
                    raise FileNotFoundError('No private selected pair: '+str(work/f'{name}-{mode}.{suffix}'))
            _write(root,work/name/f'{prefix}{mode}.mjs',"export {default} from '../"+name+'-'+mode+".mjs';\n")
    if 'trap'in selected:_write(root,work/'trap/foreign-option-indices.json',(root/'.cache/trap-author/foreign-option-indices.json').read_bytes())
    if 'topl'in selected:_write(root,work/'topl/functions.json',(root/'.cache/topl-author/functions.json').read_bytes())

def topl_dependency_command(command,source):
    """Exact known compile-relevant flags, explicit projection receipt required."""
    result=[command[0]];i=1
    while i<len(command):
        arg=command[i]
        if arg in ['-include','-isystem','-I','-D','-U']:
            result.extend(command[i:i+2]);i+=2;continue
        if arg.startswith(('-O','-g','-D','-U','-I','-isystem=','-std=','-ffile-prefix-map=','-fmacro-prefix-map=')) or arg.startswith(('-sMEMORY64=','-sSUPPORT_LONGJMP=')):
            result.append(arg);i+=1;continue
        if arg in ['--js-library','-o']:
            i+=2;continue
        if arg in ['--no-entry'] or arg.startswith(('-Wl,','-sMODULARIZE=','-sEXPORT_ES6=','-sENVIRONMENT=','-sALLOW_MEMORY_GROWTH=','-sEXPORTED_RUNTIME_METHODS=','-sEXPORTED_FUNCTIONS=')):
            i+=1;continue
        if arg==str(source):i+=1;continue
        raise ValueError('Unhandled TOPL dependency-command flag/input: '+arg)
    return [*result,'-M','-MT','topl-shadow',str(source)]

def capture_topl_inputs_before(root,command,mode):
    """Called ONLY during parent-coordinated compile phase, never by group B now."""
    root=_root(root);source=root/'scripts/tu-topl-probe.c'
    depcmd=topl_dependency_command(command,source)
    result=subprocess.run(depcmd,cwd=root,check=True,capture_output=True,text=True)
    words=shlex.split(result.stdout.replace('\\\n',' '))
    if not words or words[0]!='topl-shadow:':raise ValueError('Invalid actual compiler dependency output')
    sdk=_sdk(root);paths=set()
    for value in words[1:]:
        path=(root/value).resolve()
        if not (path.is_relative_to(root) or path.is_relative_to(sdk)):
            raise ValueError('TOPL input escaped clone/pinned SDK: '+str(path))
        if not path.is_file():raise FileNotFoundError(path)
        paths.add(path)
    paths.update(p for p in (root/'.cache/wasm64-build/tree/include').rglob('*')if p.is_file())
    paths.update(root/p for p in json.loads(DATA.read_text())['toplAdditionalInputs'])
    hashes={str(p):hashlib.sha256(p.read_bytes()).hexdigest() for p in sorted(paths)}
    return {'mode':mode,'command':command,'dependencyCommand':depcmd,'cwd':str(root),'inputHashes':hashes}

def finish_topl_inputs(root,capture):
    root=_root(root)
    for path,pin in capture['inputHashes'].items():
        if hashlib.sha256(Path(path).read_bytes()).hexdigest()!=pin:
            raise ValueError('Compiled TOPL input changed across actual shared link: '+path)
    work=root/'.cache/tu-probes';mode=capture['mode']
    _write(root,work/'topl'/f'{mode}-input-hashes.json',json.dumps(capture['inputHashes'],indent=2)+'\n')
    _write(root,work/'topl'/f'{mode}-compile-input-receipt.json',json.dumps(capture,indent=2)+'\n')
