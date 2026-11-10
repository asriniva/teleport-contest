#!/usr/bin/env python3
"""Project the configured objects.h catalogue into readable JavaScript source.

Only source tokens and the compiler preprocessor are used; no executable oracle
or serialized memory image is read.  Enum values stay symbolic and are queried
separately by the normal ABI metadata probe.
"""
from pathlib import Path
import argparse
import json
import os
import re
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
FIELDS = 'oc_name_known oc_merge oc_uses_known oc_encountered oc_magic oc_charged oc_unique oc_nowish oc_big oc_tough oc_spare1 oc_dir oc_material oc_subtyp oc_oprop oc_class oc_delay oc_color oc_prob oc_weight oc_cost oc_wsdam oc_wldam oc_oc1 oc_oc2 oc_nutrition'.split()

def split_args(text):
    out, start, depth, quote, escape = [], 0, 0, False, False
    for i, ch in enumerate(text):
        if quote:
            if escape: escape = False
            elif ch == '\\': escape = True
            elif ch == '"': quote = False
        elif ch == '"': quote = True
        elif ch == '(': depth += 1
        elif ch == ')': depth -= 1
        elif ch == ',' and depth == 0:
            out.append(text[start:i].strip()); start = i + 1
    out.append(text[start:].strip())
    return out

def expression(text):
    text = re.sub(r'/\*[\s\S]*?\*/', '', text).strip()
    text = re.sub(r'\b(\d+)[uUlL]+\b', r'\1', text)
    # Current source divisions are integer literal quotients in FOOD costs.
    # Truncate the quotient before its following addition, as C requires.
    pattern = r'(?<![\w.])(\d+)\s*/\s*(\d+)(?![\w.])'
    covered = re.sub(pattern, '', text)
    if '/' in covered:
        raise ValueError('Review new C integer division expression: ' + text)
    text = re.sub(pattern, lambda m: 'Math.trunc(' + m[1] + ' / ' + m[2] + ')', text)
    return re.sub(r'\s+', ' ', text)

def string(text):
    if re.fullmatch(r'\(char\s*\*\)\s*0', text.strip()): return 'null'
    pieces = re.findall(r'"(?:\\.|[^"\\])*"', text)
    if not pieces: raise ValueError('Unexpected descriptor: ' + text)
    return json.dumps(''.join(json.loads(p) for p in pieces), ensure_ascii=False)

def generate():
    source = (ROOT / 'nethack-c/upstream/include/objects.h').read_text()
    # Replace only the final projection macro. All original convenience macros,
    # conditional rows, source expressions and comments still pass through CPP.
    marker = '#define OBJECT(obj,bits,prp,sym,prob,dly,wt,        \\\n               cost,sdam,ldam,oc1,oc2,nut,color,sn) \\\n  { 0, 0, (char *) 0, bits, prp, sym, dly, color, prob, wt, \\\n    cost, sdam, ldam, oc1, oc2, nut, (0UL-1UL), 0, (0UL-1UL), 0 }'
    replacement = '#define OBJECT(obj,bits,prp,sym,prob,dly,wt,cost,sdam,ldam,oc1,oc2,nut,color,sn) \\\nTELEPORT_ROW(sn,obj,bits,prp,sym,dly,color,prob,wt,cost,sdam,ldam,oc1,oc2,nut)'
    if source.count(marker) != 1: raise ValueError('Review changed OBJECT projection macro')
    source = source.replace(marker, replacement)
    defines = json.loads((ROOT / 'nethack-c/wasm/compile-defines.json').read_text())
    if isinstance(defines, dict): defines = defines['defines']
    with tempfile.TemporaryDirectory(prefix='teleport-objects-') as directory:
        header = Path(directory) / 'objects-projection.h'; header.write_text(source)
        unit = Path(directory) / 'projection.c'
        unit.write_text('#include "hack.h"\nTELEPORT_BEGIN\n#define OBJECTS_INIT\n#define OBJ(name,desc) TELEPORT_DESCR(name,desc)\n#include "objects-projection.h"\nTELEPORT_END\n')
        sdk = Path(os.environ.get('EMSDK', ROOT / '.cache/emsdk'))
        command = [str(sdk / 'upstream/emscripten/emcc'), '-E', '-P', '-CC', '-sMEMORY64=1',
                   *['-D' + d for d in defines], '-I' + str(ROOT / '.cache/wasm64-build/tree/include'), str(unit)]
        output = subprocess.check_output(command, text=True)
    output = output.split('TELEPORT_BEGIN', 1)[1].split('TELEPORT_END', 1)[0]
    rows, constants, comments, cursor = [], set(), [], 0
    # Keep source section/row comments, excluding the repeatedly expanded macro
    # annotation which would otherwise occur in every single catalogue row.
    while True:
        match = re.search(r'TELEPORT_ROW\(', output[cursor:])
        if not match:
            comments.extend(re.findall(r'/\*[\s\S]*?\*/', output[cursor:])); break
        begin = cursor + match.start(); start = cursor + match.end()
        comments.extend(re.findall(r'/\*[\s\S]*?\*/', output[cursor:begin]))
        i, depth, quote, escape = start, 1, False, False
        while depth:
            ch = output[i]
            if quote:
                if escape: escape = False
                elif ch == '\\': escape = True
                elif ch == '"': quote = False
            elif output.startswith('/*', i): i = output.index('*/', i) + 1
            elif ch == '"': quote = True
            elif ch == '(': depth += 1
            elif ch == ')': depth -= 1
            i += 1
        raw = output[start:i-1]
        inline = re.findall(r'/\*[\s\S]*?\*/', raw)
        comments += [c for c in inline if c != '/*cpp fodder*/']
        args = split_args(re.sub(r'/\*[\s\S]*?\*/', '', raw))
        if len(args) != 28: raise ValueError((len(args), args))
        name = args[0] if args[0] != '0' else 'ARRAY_TERMINATOR'
        descriptor = args[1]
        if not descriptor.startswith('TELEPORT_DESCR('): raise ValueError(descriptor)
        description = split_args(descriptor[len('TELEPORT_DESCR('):-1])
        values = [expression(x) for x in args[2:]]
        for value in values: constants.update(re.findall(r'\b[A-Z][A-Z_0-9]*\b', value))
        row = '\n'.join(comments) + ('\n' if comments else '')
        row += '    { id: ' + json.dumps(name) + ', oc_name: ' + string(description[0]) + ', oc_descr: ' + string(description[1]) + ',\n'
        for offset in range(0, len(FIELDS), 4):
            row += '      ' + ', '.join(f'{key}: {value}' for key,value in zip(FIELDS[offset:offset+4],values[offset:offset+4])) + ',\n'
        row += '    },'
        rows.append(row); comments = []; cursor = i
    constants.discard('n')
    text = '// Generated from configured upstream include/objects.h by scripts/write-objects-data.py.\n'
    text += '// Source expressions stay symbolic; ABI metadata supplies their compiled enum values.\n'
    text += "import layouts from '../wasm/tu-layouts.json' with { type: 'json' };\n"
    text += 'const { ' + ', '.join(sorted(constants)) + ' } = layouts.objects;\n\n'
    text += 'export const catalogue = [\n' + '\n'.join(rows) + '\n];\n\n'
    text += '\n'.join(comments) + '\n'
    text += '''// These are the two original objects.h projections, without native memory aliases.
export const obj_descr_init = catalogue.map(({ oc_name, oc_descr }) => ({ oc_name, oc_descr }));
export const obj_init = catalogue.map(({ id, oc_name, oc_descr, ...fields }) => ({
    oc_name_idx: 0, oc_descr_idx: 0, oc_uname: null, ...fields,
    oc_sell_minseen: 0xffffffffffffffffn, oc_sell_maxseen: 0n,
    oc_buy_minseen: 0xffffffffffffffffn, oc_buy_maxseen: 0n,
}));
'''
    return text, constants

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()
    text, constants = generate()
    destination = ROOT / 'js/ported/objects-data.js'
    if args.check:
        if destination.read_text() != text: raise SystemExit('objects-data.js is not current; regenerate it')
        print('Objects catalogue source projection is reproducible')
    else:
        destination.write_text(text)
        print('Wrote objects-data.js; metadata constants: ' + ', '.join(sorted(constants)))
