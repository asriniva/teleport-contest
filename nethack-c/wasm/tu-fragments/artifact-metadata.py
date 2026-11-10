"""Extract the actual configured ARTIFACT function/field/callback ABI.

Development-only: the JS port never runs this compiler or reads these files.
All outputs stay under the requested private author directory by default.
"""
import argparse
import hashlib
import json
from pathlib import Path
import subprocess


ROOT = Path(__file__).resolve().parents[3]


def walk(node):
    yield node
    for child in node.get('inner', []):
        yield from walk(child)


def stable(node):
    if isinstance(node, list):
        return [stable(value) for value in node]
    if not isinstance(node, dict):
        return node
    return {key: stable(value) for key, value in node.items()
            if key not in ['id', 'loc', 'range', 'previousDecl', 'typeAliasDeclId']}


def analyze(source, ast):
    text = source.read_text()
    nodes = list(walk(ast))
    declarations = {node['id']: node for node in nodes if 'id' in node}
    record_aliases = {}
    for declaration in nodes:
        if declaration.get('kind') == 'TypedefDecl':
            for child in walk(declaration):
                if child.get('kind') == 'RecordType':
                    record_aliases.setdefault(child['decl']['id'], []).append(declaration['name'])
    functions = []
    for node in ast.get('inner', []):
        name = node.get('name', '')
        offset = node.get('loc', {}).get('offset', -1)
        if (node.get('kind') == 'FunctionDecl' and offset >= 0
                and text[offset:offset + len(name)] == name
                and any(child.get('kind') == 'CompoundStmt' for child in node.get('inner', []))):
            functions.append(node)
    assert len(functions) == 76, 'Review changed configured ARTIFACT inventory'
    function_names = {node['name'] for node in functions}
    fields = {}
    for record in nodes:
        if record.get('kind') == 'RecordDecl' and record.get('completeDefinition'):
            for field in record.get('inner', []):
                if field.get('kind') == 'FieldDecl':
                    fields[field['id']] = (record, field)
    used_fields, globals_, dependencies, calls = {}, {}, {}, []
    local_ids = {node['id'] for fn in functions for node in walk(fn)
                 if node.get('kind') == 'ParmVarDecl'
                 or node.get('kind') == 'VarDecl' and node.get('storageClass') != 'extern'}
    for fn in functions:
        for node in walk(fn):
            if node.get('kind') == 'MemberExpr':
                owner, field = fields[node['referencedMemberDecl']]
                aliases = record_aliases.get(owner['id'], [])
                key = owner.get('name', '') or (aliases[0] if aliases else None)
                assert key, 'Review unnamed, non-typedef ARTIFACT record'
                record = used_fields.setdefault(key, {'name': key,
                    'ctype': owner.get('tagUsed', 'struct') + ' ' + key if owner.get('name') else key,
                    'aliases': aliases, 'tag': owner.get('tagUsed'), 'fields': {}})
                record['fields'][field['name']] = {
                    'name': field['name'], 'type': field['type'],
                    'bitfield': field.get('isBitfield', False)}
            if node.get('kind') == 'DeclRefExpr':
                reference = node.get('referencedDecl', {})
                if reference.get('kind') == 'VarDecl' and reference['id'] not in local_ids:
                    globals_[reference['name']] = reference['type']
                if reference.get('kind') == 'FunctionDecl' and reference['name'] not in function_names:
                    decl = declarations.get(reference['id'], reference)
                    dependencies[reference['name']] = {
                        'type': reference['type'],
                        'parameters': [{'name': p.get('name'), 'type': p['type']}
                            for p in decl.get('inner', []) if p.get('kind') == 'ParmVarDecl'],
                        'variadic': decl.get('variadic', False)}
            if node.get('kind') == 'CallExpr':
                callee = node['inner'][0]
                while callee.get('inner') and callee.get('kind') != 'DeclRefExpr':
                    callee = callee['inner'][0]
                reference = callee.get('referencedDecl', {})
                if reference.get('kind') == 'FunctionDecl':
                    calls.append({'caller': fn['name'], 'callee': reference['name'],
                                  'arguments': [argument.get('type') for argument in node['inner'][1:]],
                                  'range': node.get('range')})
    return {'source': str(source.relative_to(ROOT)),
            'preparedSha256': hashlib.sha256(source.read_bytes()).hexdigest(),
            'functions': [{'name': fn['name'], 'type': fn['type'],
                           'static': fn.get('storageClass') == 'static',
                           'parameters': [{'name': p.get('name'), 'type': p['type']}
                               for p in fn.get('inner', []) if p.get('kind') == 'ParmVarDecl'],
                           'locals': [{'name': local.get('name'), 'type': local['type'],
                                       'static': local.get('storageClass') == 'static'}
                                      for local in walk(fn) if local.get('kind') == 'VarDecl'
                                      and local.get('storageClass') != 'extern'],
                           'astSha256': hashlib.sha256(json.dumps(stable(fn), sort_keys=True).encode()).hexdigest()}
                          for fn in functions],
            'records': list(used_fields.values()), 'globals': globals_,
            'dependencies': dependencies, 'calls': calls}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--work', type=Path, default=ROOT / '.cache/artifact-author')
    parser.add_argument('--ast', type=Path, help='Analyze an existing private compiler AST instead of compiling.')
    args = parser.parse_args()
    args.work.mkdir(parents=True, exist_ok=True)
    source = ROOT / '.cache/wasm64-build/tree/src/artifact.c'
    if args.ast:
        ast = json.loads(args.ast.read_text())
    else:
        defines = json.loads((ROOT / 'nethack-c/wasm/compile-defines.json').read_text())
        command = [str(ROOT / '.cache/emsdk/upstream/emscripten/emcc'),
                   '-O2', '-g', '-sMEMORY64=1', *['-D' + name for name in defines],
                   '-include', str(ROOT / 'nethack-c/wasm/native-terminal.h'),
                   '-I' + str(ROOT / '.cache/wasm64-build/tree/include'),
                   '-I' + str(ROOT / '.cache/ncurses-wasm64-build/include'),
                   '-fsyntax-only', '-Xclang', '-ast-dump=json', source.name]
        ast_path = args.work / 'artifact-ast.json'
        with ast_path.open('w') as output:
            # Match the real production basename/cwd, including __FILE__ and
            # recorder/debug source context. Included probes have separate paths.
            subprocess.run(command, cwd=source.parent, stdout=output, check=True)
        ast = json.loads(ast_path.read_text())
    metadata = analyze(source, ast)
    destination = args.work / 'source-metadata.json'
    temporary = destination.with_suffix('.json.tmp')
    temporary.write_text(json.dumps(metadata, indent=2) + '\n')
    temporary.replace(destination)
    print(f'ARTIFACT: {len(metadata["functions"])} functions, '
          f'{len(metadata["records"])} used records, '
          f'{len(metadata["globals"])} globals, '
          f'{len(metadata["dependencies"])} typed dependencies; wrote {destination}')


if __name__ == '__main__':
    main()
