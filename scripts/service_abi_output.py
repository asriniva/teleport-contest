"""Write service ABI inventories without dropping symlinked compiler inputs."""
import hashlib,json,shlex,tempfile
from pathlib import Path

def write_service_abi(root,output,data,dependencies=None,reference_root=None,extra=()):
    root=Path(root).resolve()
    sha=lambda p:hashlib.sha256(Path(p).read_bytes()).hexdigest()
    if dependencies is not None:
        aliases=[(root,Path('.'))]
        for name in ['.cache/emsdk','.cache/wasm64-build','.cache/wasm64-build/tree','.cache/ncurses-wasm64-build','.cache/ncurses-wasm64-build/include']:
            p=root/name
            if p.exists():aliases.append((p.resolve(),Path(name)))
        if reference_root is not None:aliases.append((Path(reference_root).resolve(),Path('.')))
        aliases.sort(key=lambda row:len(str(row[0])),reverse=True)
        paths=list(extra)
        for text in dependencies if isinstance(dependencies,list) else [dependencies]:
            paths.extend(shlex.split(text.split(':',1)[1].replace('\\\n','')))
        headers={}
        for value in paths:
            p=Path(value).resolve()
            # The temporary preprocessing probe is not a compiler/header input.
            if p.name in {'probe.c','room.c'} and not p.exists() and p.parent.name.startswith('standalone-') and p.parent.parent==Path(tempfile.gettempdir()).resolve():continue
            logical=None
            for physical,prefix in aliases:
                if p.is_relative_to(physical):
                    candidate=prefix/p.relative_to(physical)
                    if (root/candidate).is_file() and sha(root/candidate)==sha(p):logical=candidate;break
            if logical is None:raise RuntimeError('Unmapped service ABI dependency: '+str(p))
            headers[str(logical)]=sha(p)
        data['referenceHeaderSha256']=dict(sorted(headers.items()))
    for path in ['scripts/service_abi_output.py','js/nethack/service-coercions.js']:
        data['sourceSha256'][path]=sha(root/path)
    Path(output).write_text(json.dumps(data,indent=2)+'\n')
