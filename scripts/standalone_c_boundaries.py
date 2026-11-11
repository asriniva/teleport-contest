"""Development-only abort boundaries for a deliberately incomplete C group.

Never return success/default values for an unconnected function. Every boundary
is named in the build receipt, and any reached boundary fails the comparison.
"""
import json,re,subprocess
from pathlib import Path

def build(cmd,flags,sources,root,reference,out):
    tree=reference/'.cache/wasm64-build/tree'
    probe=out/'boundary-types.c';probe.write_text('#include "hack.h"\n#include <stdio.h>\n#include <stdlib.h>\n')
    compiler=reference/'.cache/emsdk/upstream/bin/clang'
    cpp=[flag for flag in flags if flag.startswith(('-I','-D'))]
    ast=json.loads(subprocess.check_output([str(compiler),'--target=wasm64-unknown-emscripten','--sysroot='+str(reference/'.cache/emsdk/upstream/emscripten/cache/sysroot'),*cpp,'-fsyntax-only','-Xclang','-ast-dump=json',str(probe)]))
    functions={n['name']:n for n in ast['inner'] if n.get('kind')=='FunctionDecl'}
    variables={n['name']:n for n in ast['inner'] if n.get('kind')=='VarDecl'}
    known={row['name'] for row in json.loads((root/'js/standalone/decl-storage.json').read_text())['globals']}
    boundary=out/'boundaries.c';declarations={}
    def parameter(t,i):
        if '(*)' in t:return t.replace('(*)','(*p'+str(i)+')',1)
        if '[' in t:return t.replace('[',' p'+str(i)+'[',1)
        return t+' p'+str(i)
    for attempt in range(8):
        boundary.write_text(probe.read_text()+'\n'+'\n'.join(declarations.values())+'\n')
        current=[*cmd[:-2],str(boundary),*cmd[-2:]]
        result=subprocess.run(current,capture_output=True,text=True)
        (out/f'build-{attempt}.log').write_text(result.stdout+result.stderr)
        if result.returncode==0:
            sources.extend([probe,boundary]);return result,current,[{'name':name,'kind':'function-abort' if name in functions else 'zero-input-global'} for name in sorted(declarations)]
        missing=set(re.findall(r'undefined symbol: ([A-Za-z_]\w*)',result.stderr))-declarations.keys()
        if not missing:raise RuntimeError(result.stderr[-6000:])
        for name in sorted(missing):
            if name in functions:
                node=functions[name];result_type=node['type']['qualType'].split('(',1)[0].strip()
                params=[parameter(n['type']['qualType'],i) for i,n in enumerate(n for n in node.get('inner',[]) if n.get('kind')=='ParmVarDecl')]
                if node.get('variadic'):params.append('...')
                declarations[name]='#undef '+name+'\n'+result_type+' '+name+'('+(','.join(params) or 'void')+'){fputs("Unconnected C boundary: '+name+'\\n",stderr);abort();}'
            elif name in known and name in variables:
                # Explicit zero input globals for this component harness. Full
                # game/default initialization remains a separate acceptance gate.
                declarations[name]='__typeof__('+name+') '+name+';'
            else:raise RuntimeError('Unrecognized external C boundary '+name)
    raise RuntimeError('C boundary resolution did not converge')
