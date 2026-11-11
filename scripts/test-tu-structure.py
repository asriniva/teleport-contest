"""Source-preservation checks for the current simple, sequential TU ports.

This is a conservative check for these TUs, not a general C parser or proof of
equivalent control flow. Differential tests and source review remain required.
"""
import json
from pathlib import Path
import re
import subprocess
import os


# Scoped complex TU rules: owned guards still run independently on normal builds.
tu137_data=json.loads((Path(__file__).resolve().parents[1]/'nethack-c/wasm/tu-fragments/tu137-source-check-order.json').read_text())
tu137_names=set(tu137_data['counts'])
tu137_a={'hack','uhitm','mon','pickup','shk'}
tu137_columns=tu137_a|set(tu137_data['cOrderedNames'])|{'sp_lev','wintty'}
tu137_tokens=re.compile(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|/\*[\s\S]*?\*/|//[^\n]*')
def tu137_executable(value):
    return tu137_tokens.sub(lambda match:re.sub(r'[^\n]',' ',match[0]),value)
def tu137_comments(value,include_line=False):
    return [match[0]for match in tu137_tokens.finditer(value)
            if match[0].startswith('/*')or(include_line and match[0].startswith('//'))]
def tu137_cpp(root,port,defines):
    source=(root/'.cache/wasm64-build/tree'/port['source']).resolve()
    cwd=(root/'.cache/wasm64-build/tree/src').resolve()
    sdk=Path(os.environ.get('EMSDK',root/'.cache/emsdk'))
    assert not port.get('configuredFunctionHeaders'),(port['name'],'Unreviewed header body owner')
    command=[str(sdk/'upstream/emscripten/emcc'),'-O2','-g','-E','-I../include',
             *defines,'-sMEMORY64=1','-I'+str(root/'.cache/ncurses-wasm64-build/include'),
             '-include',str(root/'nethack-c/wasm/native-terminal.h'),os.path.relpath(source,cwd)]
    output=subprocess.check_output(command,cwd=cwd,text=True)
    selected=[];active=False;encountered=False
    for line in output.splitlines():
        marker=re.match(r'^# \d+ "([^"\n]+)"',line)
        if marker:
            name=marker[1]
            owner=None if name.startswith('<')else(Path(name)if Path(name).is_absolute()else cwd/name).resolve()
            active=owner==source;encountered|=active
        elif active:selected.append(line)
    assert encountered,(port['name'],'CPP never entered exact prepared source')
    return '\n'.join(selected)

root = Path(__file__).resolve().parents[1]
defines = ['-D' + name for name in json.loads((root / 'nethack-c/wasm/compile-defines.json').read_text())]
for port in json.loads((root / 'nethack-c/wasm/tu-ports.json').read_text()):
    pristine = (root / 'nethack-c/upstream' / port['source']).read_text()
    source_tree = root / ('.cache/wasm64-build/tree' if port.get('reference') == 'prepared' else 'nethack-c/upstream')
    c = (source_tree / port['source']).read_text()
    js = (root / port['javascript']).read_text()
    if port['name'] in tu137_names:
        configured_c=tu137_cpp(root,port,defines)
    else:
        if port.get('configuredFunctions'):
            sdk = Path(os.environ.get('EMSDK', root / '.cache/emsdk'))
            source = (source_tree / port['source']).resolve()
            output = subprocess.check_output([str(sdk / 'upstream/emscripten/emcc'), '-E',
                *defines, '-sMEMORY64=1',
                '-I' + str(root / '.cache/wasm64-build/tree/include'),
                '-I' + str(root / '.cache/ncurses-wasm64-build/include'), str(source)], text=True)
            definition_owners = {str(source)}
            for header in port.get('configuredFunctionHeaders', []):
                for tree in [source_tree, root / '.cache/wasm64-build/tree']:
                    definition_owners.add(str((tree / header).resolve()))
            active, selected = False, []
            for line in output.splitlines():
                marker = re.match(r'^# \d+ "([^"\n]+)"', line)
                if marker:
                    active = marker.group(1) in definition_owners
                elif active:
                    selected.append(line)
            configured_c = '\n'.join(selected)
        else:
            configured_c = c
    clean_c = tu137_executable(configured_c) if port['name'] in tu137_names else re.sub(r'/\*.*?\*/|//[^\n]*', '', configured_c, flags=re.S)
    clean_c = re.sub(r'^\s*#(?:[^\n]*\\\n)*[^\n]*', '', clean_c, flags=re.M)
    clean_js = tu137_executable(js) if port['name'] in tu137_names else re.sub(r'/\*.*?\*/|//[^\n]*', '', js, flags=re.S)
    definition_pattern = r'(?m)^(\w+)\s*\(([^;{}]*)\)\s*\{' if port['name']=='display' or port['name'] in tu137_columns else r'\b(\w+)\s*\(([^;{}]*)\)\s*\{'
    definitions = [match for match in re.finditer(definition_pattern, clean_c)
                   if match.group(1) not in ['for', 'while', 'if', 'switch']]
    if port['name']=='artifact':
        # A continuation of a for-update nxtobj call is not a C definition.
        definitions=[m for m in definitions if m.start()==0 or clean_c[m.start()-1]=='\n']
        assert len(definitions)==76
    c_functions = [match.group(1) for match in definitions]
    js_functions = re.findall(r'^export function\s+(\w+)\s*\(' if port['name']=='display' or port['name'] in tu137_names else r'\bfunction\s+(\w+)\s*\(', clean_js, re.M)
    if port['name'] in tu137_names:
        # Account for every named declaration/expression, including generators.
        # The source goto translation has exactly one nested PICKUP helper.
        all_named=re.findall(r'\bfunction(?:\s+|\s*\*\s*)([A-Za-z_$][\w$]*)\s*\(',clean_js)
        extras=['menu_pickup']if port['name']=='pickup'else[]
        assert sorted(all_named)==sorted(js_functions+extras),(port['name'],'Unexpected named JS function',all_named,js_functions,extras)
    if port['name']=='display':
        expected=[f['name'] for f in json.loads((root/'nethack-c/wasm/tu-fragments/display-source-metadata.json').read_text())['functions']]
        assert c_functions==expected and js_functions==expected
        nested=re.findall(r'(?m)^\s+function (\w+)\(',clean_js)
        assert nested==['show_mem','do_twall','horiz','do_crwall'],nested
    if port['name']=='artifact':
        # The separately checked data initializer is not a source C function.
        assert js_functions.count('initializeArtifactData')==1
        assert re.search(r'export function initializeArtifactData\(C\)',js)
        js_functions=[name for name in js_functions if name!='initializeArtifactData']
    if port['name']=='decl':
        # These retain original C macros, not additional source functions.
        assert c_functions==['program_state_init','decl_globals_init','sa_victual']
        assert js_functions.count('ZERO')==js_functions.count('MAGICCHECK')==1
        assert re.search(r'^function ZERO\(value\)',js,re.M)
        assert re.search(r'^function MAGICCHECK\(xx, name\)',js,re.M)
        js_functions=[name for name in js_functions if name not in ['ZERO','MAGICCHECK']]

    if port['name'] in tu137_names:
        initializer={'hack':'initializeHackData','termcap':'initializeTermcapData'}.get(port['name'])
        if initializer:
            assert js_functions.count(initializer)==1
            assert re.search(r'^export function '+initializer+r'\(C\)',js,re.M)
            js_functions=[name for name in js_functions if name!=initializer]
        assert len(c_functions)==tu137_data['counts'][port['name']],(port['name'],'configured body count',c_functions)
        if port['name'] in tu137_data['cOrderedNames']:
            assert c_functions==js_functions==tu137_data['cOrderedNames'][port['name']]
        if port['name']=='hack':
            records=json.loads((root/'nethack-c/wasm/tu-fragments/hack-schema.json').read_text())['functions']
        elif port['name']=='uhitm':
            records=json.loads((root/'.cache/uhitm-author/functions.json').read_text())
        elif port['name']=='mon':
            records=None
            assert c_functions==js_functions==json.loads((root/'.cache/mon-author/functions.json').read_text())
        elif port['name'] in ['pickup','shk']:
            metadata='pickup-source-metadata.json'if port['name']=='pickup'else'shk-source-inventory.json'
            records=json.loads((root/'nethack-c/wasm/tu-fragments'/metadata).read_text())['functions']
        else:records=None
        if records is not None:
            assert c_functions==js_functions==[record['name']for record in records]
        if port['name']=='pickup':assert js.count('function menu_pickup(){')==1

    assert c_functions == js_functions, (port['name'], c_functions, js_functions)
    js_parameters = {name: [word.strip() for word in parameters.split(',')] if parameters.strip() else []
                     for name, parameters in re.findall(r'\bfunction\s+(\w+)\s*\(([^)]*)\)', clean_js)}
    for definition_index, definition in enumerate(definitions):
        parameters, start, depth = [], 0, 0
        raw = definition.group(2)
        variadic = False
        for i, character in enumerate(raw + ','):
            if character == '(':
                depth += 1
            elif character == ')':
                depth -= 1
            elif character == ',' and depth == 0:
                parameter = raw[start:i].strip()
                start = i + 1
                if not parameter or parameter == 'void':
                    continue
                if parameter == '...':
                    assert raw[i:].strip() == '', (port['name'], 'Non-final C ellipsis')
                    variadic = True
                    continue
                function_pointer = re.search(r'\(\s*\*\s*(\w+)\s*\)', parameter)
                # Configured SOUNDLIBONLY expands UNUSED to this annotation.
                # Strip the exact inert form, retaining the source binding.
                parameter = re.sub(r'\b__attribute__\s*\(\(\s*unused\s*\)\)', '', parameter)
                words = re.findall(r'\b\w+\b', re.sub(r'\[[^]]*\]|\bUNUSED\b', '', parameter))
                parameters.append(function_pointer.group(1) if function_pointer else words[-1])
        if variadic:
            # The sole added JS parameter carries the original C va_list.
            # Fixed names/order remain exact, and no generic rest name can
            # silently replace the source's named variadic local.
            end = definitions[definition_index + 1].start() if definition_index + 1 < len(definitions) else len(clean_c)
            body = clean_c[definition.end():end]
            locals_ = re.findall(r'\bva_list\s+(\w+)\s*;', body)
            assert len(locals_) == 1, (port['name'], definition.group(1), 'Expected one C va_list local', locals_)
            parameters.append('...' + locals_[0])
        # END retains its original fixed str parameter and transports the
        # actual C va_list through the second arguments slot, not JS rest args.
        if port['name'] == 'end' and definition.group(1) == 'panic':
            assert parameters == ['str', '...the_args']
            assert 'C.vsnprintf(buf, C.BUFSZ, str, arguments[1])' in js
            parameters = ['str']
        if port['name'] == 'end' and definition.group(1) == 'build_english_list':
            assert parameters == ['in']
            parameters[0] = 'in_'
        # `let` is a reserved binding in strict JavaScript modules.
        if port['name'] == 'iactions' and definition.group(1) == 'ia_addmenu':
            assert parameters == ['win', 'act', 'let', 'txt']
            parameters[2] = 'let_'
        # Exact original WINDOWS parameter collides with a strict-JS keyword.
        if port['name'] == 'windows' and definition.group(1) == 'genl_message_menu':
            assert parameters == ['let', 'how', 'mesg']
            parameters[0] = 'let_'
        # Exact DETECT fixed int parameter is a strict JavaScript reserved name.
        if port['name'] == 'detect' and definition.group(1) == 'object_detect':
            assert parameters == ['detector', 'class']
            parameters[1] = 'class_'
        # The C binding `in` is a reserved JavaScript keyword.
        if port['name'] == 'report' and definition.group(1) == 'swr_add_uricoded':
            assert parameters == ['in', 'out', 'remaining', 'markp']
            parameters[0] = 'in_'
        # Exact C parameters that are reserved bindings in strict JS modules.
        if port['name']=='makemon' and definition.group(1) in ['mkclass','mkclass_aligned','mkclass_poly']:
            expected={'mkclass':['class','spc'],'mkclass_aligned':['class','spc','atyp'],'mkclass_poly':['class']}[definition.group(1)]
            assert parameters==expected
            parameters[0]='class_'
        if port['name']=='mkobj' and definition.group(1)=='mkobj_at':
            assert parameters==['let','x','y','artif']
            parameters[0]='let_'
        # Only these two INVENT source formals collide with strict-JS let.
        if port['name']=='invent' and definition.group(1) in ['xprname','let_to_name']:
            index=2 if definition.group(1)=='xprname' else 0
            assert parameters[index]=='let'
            parameters[index]='let_'
        if port['name']=='wintty' and definition.group(1)=='tty_message_menu':
            assert parameters==['let','how','mesg']
            parameters[0]='let_'
        assert parameters == js_parameters[definition.group(1)], (port['name'], definition.group(1), parameters, js_parameters[definition.group(1)])
    if port['name'] in tu137_names:
        original_a=tu137_comments(pristine);original_b=tu137_comments(c)
        translated=tu137_comments(js)
        for comment in set(original_a+original_b):
            assert translated.count(comment)>=max(original_a.count(comment),original_b.count(comment)),(port['name'],'Missing original comment occurrence',comment)
        if port['name']=='hack':
            original=tu137_comments(pristine,True);assert len(original)==488
            remaining=tu137_comments(js,True)
            for comment in original:
                assert comment in remaining,('hack','Missing source comment occurrence',comment)
                remaining.remove(comment)
        elif port['name']=='uhitm':
            assert len(original_a)==783 and original_a==translated
        elif port['name'] in ['mon','pickup']:
            assert len(original_a)==(717 if port['name']=='mon' else 478)
        elif port['name']=='shk':
            original=tu137_comments(pristine,True);translated_all=tu137_comments(js,True)
            for comment in set(original):assert translated_all.count(comment)>=original.count(comment)
    else:
        for comment in set(re.findall(r'/\*.*?\*/', pristine + '\n' + c, flags=re.S)):
            assert comment in js, (port['name'], 'Missing original comment', comment)
    print(port['name'] + ': original function inventory/order/parameters and all block comments preserved')
