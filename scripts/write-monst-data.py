#!/usr/bin/env python3
"""Generate readable monster rows and seduction attacks from configured C source.

The compiler is used only as a source preprocessor. No runtime oracle, memory
image, or native initializer result supplies catalogue values.
"""
from pathlib import Path
import argparse
import json
import os
import re
import subprocess
import tempfile
import runpy

ROOT = Path(__file__).resolve().parents[1]
PARSERS = runpy.run_path(str(ROOT / 'scripts/write-objects-data.py'))
split_args, c_string = PARSERS['split_args'], PARSERS['string']


def call(text, name):
    prefix = name + '('
    if not text.startswith(prefix) or not text.endswith(')'): raise ValueError(text)
    return split_args(text[len(prefix):-1])


def expression(text, wide=False):
    text = re.sub(r'\b(0[xX][0-9a-fA-F]+|\d+)[uUlL]+\b', r'\1', text).strip()
    if '/' in text: raise ValueError('Review new C integer division: ' + text)
    if wide: text = re.sub(r'\b(0[xX][0-9a-fA-F]+|\d+)\b', r'\1n', text)
    return re.sub(r'\s+', ' ', text)


def generate():
    source = (ROOT / 'nethack-c/upstream/src/monst.c').read_text()
    catalogue = (ROOT / 'nethack-c/upstream/include/monsters.h').read_text()
    tokens = set(re.findall(r'\b[A-Z][A-Z_0-9]+\b', re.sub(r'/\*[\s\S]*?\*/|"(?:\\.|[^"\\])*"', '', catalogue)))
    # Keep object-like game constants symbolic instead of replacing flags and
    # attack types with opaque numbers. Structural macros still expand normally.
    preserve = set()
    for header in ['monflag.h', 'monattk.h', 'color.h', 'weight.h', 'align.h']:
        contents = (ROOT / 'nethack-c/upstream/include' / header).read_text()
        preserve.update(tokens & set(re.findall(r'^#define\s+(\w+)(?:\s|$)', contents, flags=re.M)))
    prefix = source[source.index('#define NO_ATTK'):source.index('static struct permonst')]
    prefix = re.sub(r'#define MON\([\s\S]*?\n    \}', '#define MON(nam,sym,lvl,gen,atk,siz,mr1,mr2,flg1,flg2,flg3,d,col,bn) \\\nTELEPORT_MON_ROW(PM_##bn,nam,sym,lvl,gen,atk,siz,mr1,mr2,flg1,flg2,flg3,d,col)', prefix, count=1)
    prefix = prefix.replace('#define NAM(name) { (const char *) 0, (const char *) 0, name }', '#define NAM(name) TELEPORT_NAMES((const char *)0,(const char *)0,name)')
    prefix = prefix.replace('#define NAMS(namm, namf, namn) { namm, namf, namn }', '#define NAMS(namm,namf,namn) TELEPORT_NAMES(namm,namf,namn)')
    prefix = prefix.replace('#define ATTK(at, ad, n, d) { at, ad, n, d }', '#define ATTK(at,ad,n,d) TELEPORT_ATTACK(at,ad,n,d)')
    prefix = prefix.replace('#define NO_ATTK { 0, 0, 0, 0 }', '#define NO_ATTK TELEPORT_ATTACK(0,0,0,0)')
    prefix = prefix.replace('#define A(a1, a2, a3, a4, a5, a6) { a1, a2, a3, a4, a5, a6 }', '#define A(a1,a2,a3,a4,a5,a6) TELEPORT_ATTACKS(a1,a2,a3,a4,a5,a6)')
    terminator = source[source.index('    MON(NAM("")'):source.index('\n};', source.index('    MON(NAM("")'))]
    unit = '#include "hack.h"\n' + ''.join(f'#undef {n}\n#define {n} {n}\n' for n in sorted(preserve)) + prefix
    unit += '\nTELEPORT_BEGIN\n#include "monsters.h"\n#undef MON\n#define MON(nam,sym,lvl,gen,atk,siz,mr1,mr2,flg1,flg2,flg3,d,col,bn) \\\nTELEPORT_MON_ROW(NON_PM,nam,sym,lvl,gen,atk,siz,mr1,mr2,flg1,flg2,flg3,d,col)\n' + terminator
    unit += '\nTELEPORT_END\nTELEPORT_YES(SEDUCTION_ATTACKS_YES)\nTELEPORT_NO(SEDUCTION_ATTACKS_NO)\n'
    defines = json.loads((ROOT / 'nethack-c/wasm/compile-defines.json').read_text())
    with tempfile.TemporaryDirectory(prefix='teleport-monst-') as directory:
        path = Path(directory) / 'projection.c'; path.write_text(unit)
        sdk = Path(os.environ.get('EMSDK', ROOT / '.cache/emsdk'))
        command = [str(sdk / 'upstream/emscripten/emcc'), '-E', '-P', '-CC', '-sMEMORY64=1',
                   *['-D'+d for d in defines], '-I'+str(ROOT / '.cache/wasm64-build/tree/include'), str(path)]
        output = subprocess.check_output(command, text=True)
    section = output.split('TELEPORT_BEGIN',1)[1].split('TELEPORT_END',1)[0]
    rows, constants, cursor = [], set(), 0
    def expr(value, wide=False):
        value = expression(value, wide)
        constants.update(re.findall(r'\b[A-Z][A-Z_0-9]*\b', value))
        return value
    def attacks(text):
        return '[' + ', '.join('[' + ', '.join(expr(x) for x in call(a,'TELEPORT_ATTACK')) + ']' for a in call(text,'TELEPORT_ATTACKS')) + ']'
    while True:
        match = re.search(r'TELEPORT_MON_ROW\(',section[cursor:])
        if not match: break
        begin,start = cursor+match.start(),cursor+match.end()
        comments = re.findall(r'/\*[\s\S]*?\*/',section[cursor:begin])
        i,depth,quote,escape=start,1,False,False
        while depth:
            ch=section[i]
            if quote:
                if escape: escape=False
                elif ch=='\\': escape=True
                elif ch=='"': quote=False
            elif section.startswith('/*',i): i=section.index('*/',i)+1
            elif ch=='"': quote=True
            elif ch=='(': depth+=1
            elif ch==')': depth-=1
            i+=1
        raw=section[start:i-1]
        comments+=re.findall(r'/\*[\s\S]*?\*/',raw)
        args=split_args(re.sub(r'/\*[\s\S]*?\*/','',raw))
        if len(args)!=21: raise ValueError((len(args),args))
        # MON expands LVL and SIZ into their ordinary fields.
        # index,names,symbol, five LVL fields, geno,attacks, four SIZ
        # fields, two resistance masks, three flag masks,difficulty,color.
        index,names,sym,level,move,ac,mr,align,geno,atk,weight,nut,sound,size,resists,conveys,flags1,flags2,flags3,difficulty,color = args
        constants.add(index)
        namevalues=call(names,'TELEPORT_NAMES')
        row='\n'.join(comments)+ ('\n' if comments else '')
        row+='    { id: '+json.dumps(index)+', pmidx: '+index+',\n'
        row+='      pmnames: ['+', '.join(c_string(x.replace("const char", "char")) for x in namevalues)+'],\n'
        fields=[('mlet',sym),('mlevel',level),('mmove',move),('ac',ac),('mr',mr),('maligntyp',align),('geno',geno)]
        row+='      '+', '.join(k+': '+expr(v) for k,v in fields)+',\n'
        row+='      mattk: '+attacks(atk)+',\n'
        row+='      '+', '.join(k+': '+expr(v) for k,v in [('cwt',weight),('cnutrit',nut),('msound',sound),('msize',size),('mresists',resists),('mconveys',conveys)])+',\n'
        row+='      mflags1: '+expr(flags1,True)+', mflags2: '+expr(flags2,True)+', mflags3: '+expr(flags3)+',\n'
        row+='      difficulty: '+expr(difficulty)+', mcolor: '+expr(color)+',\n    },'
        rows.append(row);cursor=i
    # The attack tables are separate static objects in the original TU.
    attacktables={}
    for name,marker in [('c_sa_yes','TELEPORT_YES'),('c_sa_no','TELEPORT_NO')]:
        text=output.split(marker+'(',1)[1].strip()
        # Its outer parenthesis encloses one TELEPORT_ATTACKS expression.
        end=text.index(')\n') if ')\n' in text else -1
        attacktables[name]=attacks(text[:end])
    wide=sorted(c for c in constants if c.startswith(('M1_','M2_')))
    ordinary=sorted(constants-set(wide))
    result='// Generated from configured upstream monsters.h and monst.c by scripts/write-monst-data.py.\n'
    result+="import layouts from '../wasm/tu-layouts.json' with { type: 'json' };\n"
    result+='const {\n' + ''.join('    ' + ', '.join(ordinary[i:i+8]) + ',\n' for i in range(0,len(ordinary),8)) + '} = layouts.monst;\n'
    result+=''.join('const '+c+' = BigInt(layouts.monst.'+c+');\n' for c in wide)+'\n'
    result+='export const mons_init = [\n'+'\n'.join(rows)+'\n];\n\n'
    result+=''.join('export const '+name+' = '+value+';\n' for name,value in attacktables.items())
    return result

if __name__=='__main__':
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--check',action='store_true');args=parser.parse_args()
    content=generate();path=ROOT/'js/ported/monst-data.js'
    if args.check:
        if path.read_text()!=content: raise SystemExit('monst-data.js is not current; regenerate it')
        print('Monster catalogue source projection is reproducible')
    else:path.write_text(content);print('Wrote monst-data.js')
