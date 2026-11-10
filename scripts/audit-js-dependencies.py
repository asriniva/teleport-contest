#!/usr/bin/env python3
"""Inventory migration dependencies without building or changing the game.

Only the requested JSON output is written. All paths in the report are relative
to the contest checkout. Counts are physical lines (comments/blank lines count).
Static token observations deliberately do not claim linker/runtime reachability.
"""
import argparse
from collections import Counter, defaultdict
import hashlib
import json
from pathlib import Path
import re


ROOT = Path(__file__).resolve().parents[1]
READS = {}
MISSING = set()


def relative(path):
    return str(path.relative_to(ROOT))


def read(path):
    if not path.is_file():
        MISSING.add(relative(path))
        return ''
    data = path.read_bytes()
    READS[relative(path)] = {'sha256': hashlib.sha256(data).hexdigest(),
                             'bytes': len(data), 'physical_lines': len(data.splitlines())}
    return data.decode('utf-8', errors='replace')


def location(path, text, offset):
    return {'path': relative(path), 'line': text.count('\n', 0, offset) + 1}


def size(paths):
    files = []
    for path in sorted(set(paths)):
        if path.is_file():
            read(path)
            files.append({'path': relative(path), **READS[relative(path)]})
        else:
            MISSING.add(relative(path))
    return {'file_count': len(files),
            'physical_lines': sum(f['physical_lines'] for f in files),
            'bytes': sum(f['bytes'] for f in files), 'files': files}


def evidence(path, marker=None):
    text = read(ROOT / path)
    at = text.find(marker) if marker else 0
    return {'path': path, 'line': text.count('\n', 0, max(at, 0)) + 1,
            **({'marker': marker, 'marker_found': at >= 0} if marker else {})}


def artifact(path):
    """Hash a binary artifact without treating its contents as source text."""
    if not path.is_file():
        MISSING.add(relative(path))
        return None
    data = path.read_bytes()
    result = {'bytes': len(data), 'sha256': hashlib.sha256(data).hexdigest()}
    READS[relative(path)] = result
    return data


def strip_comments(text):
    # Retain newlines and string literals, so line evidence remains accurate.
    pattern = r'/\*[\s\S]*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\''
    return re.sub(pattern, lambda m: re.sub(r'[^\n]', ' ', m[0])
                  if m[0].startswith(('/*', '//')) else m[0], text)


LIBC = {
    'memory_strings_numbers': set('malloc calloc realloc free memcpy memmove memset memcmp memchr strlen strnlen strcpy strncpy strcat strncat strcmp strncmp strcasecmp strncasecmp strchr strrchr strstr strspn strcspn strtok strdup strndup atoi atol atoll strtol strtoul strtoll strtoull strtod abs labs llabs qsort bsearch'.split()),
    'formatting': set('printf fprintf sprintf snprintf vsnprintf vprintf vfprintf vsprintf sscanf fscanf scanf puts fputs putchar perror'.split()),
    'files_posix': set('open close read write lseek stat fstat lstat access unlink rename remove mkdir rmdir chmod chdir getcwd opendir readdir closedir fopen fclose fread fwrite fflush fseek ftell rewind feof ferror clearerr getc fgetc putc fputc fgets ungetc fileno dup dup2 fcntl truncate ftruncate fsync umask mkstemp tmpfile lockf'.split()),
    'time': set('time localtime localtime_r gmtime gmtime_r mktime strftime clock difftime gettimeofday tzset'.split()),
    'regex': set('regcomp regexec regerror regfree'.split()),
    'environment_process_terminal': set('getenv setenv unsetenv getuid geteuid getgid getegid getpid getppid getpwnam getpwuid getlogin isatty ioctl tcgetattr tcsetattr signal raise exit abort system fork wait waitpid sleep usleep setjmp longjmp _setjmp _longjmp'.split()),
    'math': set('floor ceil round trunc sqrt pow log log10 exp sin cos tan atan atan2 fabs fmod ldexp frexp modf'.split()),
    'character_locale': set('tolower toupper isalpha isalnum isdigit isspace isprint iscntrl isupper islower ispunct isxdigit setlocale localeconv'.split()),
}
TERMINFO = set('tgetent tgetflag tgetnum tgetstr tgoto tputs tparm setupterm set_curterm del_curterm tigetstr tigetnum tigetflag'.split())


def classify(symbol, game_tokens):
    if symbol.startswith('$teleport'):
        return 'javascript_bridge_helper', 'high'
    if symbol.startswith('$'):
        return 'emscripten_javascript_service', 'high'
    if symbol.startswith('teleport_'):
        return 'c_abi_helper_or_replay_bridge', 'high'
    if symbol.startswith(('lua_', 'luaL_', 'luaopen_')):
        return 'lua', 'high'
    if symbol in TERMINFO:
        return 'terminfo', 'high'
    for category, members in LIBC.items():
        if symbol in members:
            return 'libc_' + category, 'medium'
    if symbol in game_tokens:
        return 'game_symbol_candidate', 'low'
    return 'unclassified', 'low'


def collect_tu_dependencies(game_tokens, active=None, paths=None):
    libraries = []
    users = defaultdict(list)
    dependency_pattern = re.compile(r'([\w$]+)__deps\s*:\s*\[([^\]]*)\]', re.S)
    for path in sorted(paths if paths is not None else (ROOT / 'nethack-c/wasm/tu-libraries').glob('*.js')):
        text = read(path)
        groups = []
        for match in dependency_pattern.finditer(strip_comments(text)):
            symbols = re.findall(r'''['"]([^'"]+)['"]''', match[2])
            entry = {'owner': match[1], 'dependencies': symbols,
                     'evidence': location(path, text, match.start())}
            groups.append(entry)
            for symbol in set(symbols):
                users[symbol].append({'owner': match[1], **entry['evidence']})
        libraries.append({'path': relative(path), 'dependency_groups': groups})
    symbols = []
    for symbol, uses in sorted(users.items()):
        category, confidence = classify(symbol, game_tokens)
        entry = {'symbol': symbol, 'category': category, 'confidence': confidence, 'uses': uses}
        if active:
            if symbol in LIBC['regex'] and active['built_dependency_backend'] == 'javascript':
                entry['selected_resolution'] = 'C regex_t ABI forwarder to selected JavaScript ERE; not compiled TRE algorithms'
            elif symbol in TERMINFO and active['built_dependency_backend'] == 'javascript':
                entry['selected_resolution'] = 'Selected JavaScript terminfo; tparm/tputs retain C vararg/callback ABI forwarders'
            elif symbol in active['symbol_map']['javascript_import_names']:
                entry['selected_resolution'] = 'Imported JavaScript function name observed in selected Wasm artifact'
            elif symbol in active['symbol_map']['defined_wasm_function_names']:
                entry['selected_resolution'] = 'Defined Wasm function name observed; transitive implementation unresolved'
            else:
                entry['selected_resolution'] = 'Unresolved by literal name; aliases/inlining/link elimination may apply'
        symbols.append(entry)
    return {'method': 'Literal __deps arrays; no preprocessing, linker closure, or call graph.',
            'classification_limitations': [
                'Game candidates are exact token matches in prepared game C/header text, not definitions or calls.',
                'C ABI helpers may themselves call libc or remaining game functions; these transitive calls are not resolved.',
                'A JS bridge dependency may resolve to a ported TU, a remaining C implementation, or a linker service.',
                'Recognized libc names are a curated semantic classification, not an exhaustive libc API list.'],
            'library_count': len(libraries), 'unique_symbol_count': len(symbols),
            'category_counts': dict(sorted(Counter(x['category'] for x in symbols).items())),
            'libraries': libraries, 'symbols': symbols}


def collect_runtime():
    paths = [ROOT / 'js/wasm-adapter.js',
             ROOT / 'js/wasm-replay-support.js', ROOT / 'js/recording-profile.js',
             ROOT / 'nethack-c/wasm/runtime.js']
    paths += sorted((ROOT / 'js/ported').glob('*runtime.js'))
    paths += sorted((ROOT / 'js/services').rglob('*.js'))
    results = []
    patterns = {
        'esm_import': r'''\bimport\s+(?:[\s\S]*?\s+from\s+)?['"]([^'"]+)['"]|\bimport\(\s*['"]([^'"]+)['"]''',
        'service_member': r'\bservices\.([A-Za-z_$][\w$]*)',
        'filesystem_member': r'\b(?:FS|module\.FS)\.([A-Za-z_$][\w$]*)',
        'wasm_api': r'\bWebAssembly\.([A-Za-z_$][\w$]*)',
        'heap_view': r'\b(?:HEAP[A-Z0-9]+|BigUint64Array|BigInt64Array|DataView)\b',
    }
    for path in sorted(set(paths)):
        text = read(path)
        clean = strip_comments(text)
        observations = {}
        for name, pattern in patterns.items():
            values = defaultdict(list)
            for match in re.finditer(pattern, clean):
                key = next((v for v in match.groups() if v is not None), match[0])
                values[key].append(clean.count('\n', 0, match.start()) + 1)
            if values:
                observations[name] = [{'value': key, 'lines': sorted(set(lines))}
                                      for key, lines in sorted(values.items())]
        results.append({'path': relative(path), 'observations': observations})
    return {'method': 'Static imports/member expressions; dynamic properties, aliases and runtime reachability are unresolved.',
            'files': results}


def collect_compiled_service_sites(tree):
    paths = []
    for folder in ['src', 'sys/unix', 'win/tty']:
        paths += [(path, 'game') for path in sorted((tree / folder).glob('*.c'))]
    paths += [(ROOT / 'nethack-c/wasm' / name, 'c_abi_or_replay_support')
              for name in ['tu-support.c', 'bridge.c', 'compress-service.c']]
    # Token sites within concrete .c sources improve on header matching, while
    # remaining deliberately weaker evidence than preprocessing/linking/tracing.
    known = set().union(*LIBC.values(), TERMINFO)
    sites = defaultdict(list)
    pattern = re.compile(r'\b(' + '|'.join(sorted(known, key=lambda n: (-len(n), n))) + r')\s*\(')
    for path, layer in paths:
        text = read(path)
        clean = strip_comments(text)
        for match in pattern.finditer(clean):
            category, confidence = classify(match[1], set())
            sites[(match[1], category)].append({'layer': layer, **location(path, text, match.start())})
    return {'method': 'Known libc/terminfo call-like syntax in game .c files and C support wrappers. Includes inactive branches, declarations and macro-related syntax; transitive library implementations and generated glue are not traced.',
            'symbols': [{'name': name, 'category': category, 'sites': occurrences}
                        for (name, category), occurrences in sorted(sites.items())]}


def wasm_surface(binary):
    """Read declared imports/counts only; never instantiate or execute Wasm."""
    if binary is None:
        return {'available': False, 'imports': [], 'function_import_count': 0, 'defined_function_count': 0}
    if binary[:8] != b'\0asm\x01\0\0\0':
        raise ValueError('Unrecognized selected Wasm artifact')
    at = 8

    def leb():
        nonlocal at
        value, shift = 0, 0
        while True:
            byte = binary[at]; at += 1
            value |= (byte & 127) << shift
            if not byte & 128:
                return value
            shift += 7
            if shift > 70:
                raise ValueError('Invalid Wasm LEB integer')

    def name():
        nonlocal at
        length = leb(); value = binary[at:at + length].decode('utf-8'); at += length
        return value

    def limits():
        flags = leb(); minimum = leb()
        return {'flags': flags, 'minimum': minimum, **({'maximum': leb()} if flags & 1 else {})}

    imports, defined, function_index = [], 0, 0
    while at < len(binary):
        section = binary[at]; at += 1
        length = leb(); end = at + length
        if section == 2:
            for _ in range(leb()):
                entry = {'module': name(), 'field': name()}
                kind = binary[at]; at += 1
                if kind == 0:
                    entry.update(kind='function', function_index=function_index, type_index=leb())
                    function_index += 1
                elif kind == 1:
                    element = binary[at]; at += 1
                    entry.update(kind='table', element_type=element, limits=limits())
                elif kind == 2:
                    entry.update(kind='memory', limits=limits())
                elif kind == 3:
                    entry.update(kind='global', value_type=binary[at], mutable=bool(binary[at + 1])); at += 2
                elif kind == 4:
                    entry.update(kind='tag', attribute=leb(), type_index=leb())
                else:
                    raise ValueError('Unrecognized Wasm import kind')
                imports.append(entry)
        elif section == 3:
            defined = leb()
        at = end
    return {'available': True, 'imports': imports, 'function_import_count': function_index,
            'defined_function_count': defined,
            'limitation': 'Section declarations establish import/definition boundaries, not semantic equivalence or source provenance.'}


def active_inventory(manifest):
    build_path = 'nethack-c/wasm/build.py'
    build = read(ROOT / build_path)
    selected = manifest.get('dependencyBackend', 'unrecorded')
    binary_path = ROOT / 'js/wasm/nethack.wasm'
    binary = artifact(binary_path)
    surface = wasm_surface(binary)
    symbols_path = ROOT / 'js/wasm/nethack.mjs.symbols'
    symbol_text = read(symbols_path)
    indexed = {int(m[1]): m[2] for m in re.finditer(r'^(\d+):(.+)$', symbol_text, re.M)}
    imported_count = surface['function_import_count']
    imported = {name for index, name in indexed.items() if index < imported_count}
    defined = {name for index, name in indexed.items() if index >= imported_count}
    for entry in surface['imports']:
        if entry['kind'] == 'function':
            entry['symbol_map_name'] = indexed.get(entry['function_index'])
    dependency_hashes = manifest.get('javascriptDependencies', {}).get('sourceSha256', {})
    integrity = []
    for path, expected in sorted(dependency_hashes.items()):
        read(ROOT / path)
        observed = READS.get(path, {}).get('sha256')
        integrity.append({'path': path, 'manifest_sha256': expected, 'observed_sha256': observed, 'matches': observed == expected})
    groups = []
    for category, names in sorted(LIBC.items()):
        entries = sorted(names & defined)
        groups.append({'category': category, 'defined_wasm_names': entries,
                       'interpretation': 'C ABI forwarding to selected JavaScript regex' if category == 'regex' and selected == 'javascript'
                       else 'Names defined in selected Wasm; aliases/inlined and internal support routines are additional.'})
    lua_names = sorted(name for name in defined if re.match(r'^lua(?:_|[A-Z])', name))
    algorithms = {
        'compression': sorted(name for name in defined if name.startswith(('ncompress_', 'compress.', 'decompress.'))),
        'terminfo': sorted(name for name in defined if name.startswith(('_nc_', '_nc_tinfo_'))),
        'regex': sorted(name for name in defined if name.startswith(('tre_', '__tre_'))),
    }
    adapter = read(ROOT / 'js/wasm-adapter.js')
    abi_source = 'nethack-c/wasm/dependency-bridge.c'
    abi = read(ROOT / abi_source)
    abi_names = [m[1] for m in re.finditer(r'\b(tparm|tputs|regcomp|regexec|regerror|regfree)\s*\([^;{}]*\)\s*\{', strip_comments(abi))]
    allocator = sorted(name for name in defined if re.search(r'(?:^dl(?:malloc|calloc|realloc|free)$|^emmalloc|^_?emscripten_builtin_(?:malloc|calloc|realloc|free)|^__libc_(?:malloc|free))', name))
    engine_objects = read(ROOT / 'js/wasm/link-objects.txt').splitlines()
    recording_path = ROOT / '.cache/js-dependencies-active-public-summary.json'
    recording = json.loads(read(recording_path)) if recording_path.is_file() else None
    return {
        'configured_default_dependency_backend': 'javascript' if "DEPENDENCY_BACKEND = 'c' if C_DEPENDENCIES else 'javascript'" in build else 'unresolved',
        'alternate_reference_backend_flag': '--c-dependencies' if "'--c-dependencies' in sys.argv" in build else None,
        'built_dependency_backend': selected,
        'built_implementations': {key: manifest.get(key) for key in ['terminalCapabilities', 'compression', 'regex', 'ncursesRole', 'compressionSourceRole']},
        'manifest_removed_compiled_dependencies': manifest.get('removedCompiledDependencies', []),
        'build_time_and_reference_dependencies': [
            {'name': 'ncurses 6.5', 'role': 'Default builder still builds the reference libtinfo archive and generated headers; selected JS link omits that archive.',
             'evidence': [evidence(build_path, 'terminfo_include, terminfo_library = build_terminfo'),
                          evidence(build_path, 'WINLIB={terminfo_library if C_DEPENDENCIES else')]},
            {'name': 'ncompress 5.0 source', 'role': 'Pinned source hash/reference and optional --c-dependencies codec; selected JS link uses dependency-bridge.o instead.',
             'evidence': [evidence(build_path, 'codec_source_hash = '), evidence(build_path, 'if C_DEPENDENCIES:')]},
            {'name': 'native NetHack generators and host compiler', 'role': 'Generate embedded game assets and reference executables; not production runtime services.',
             'evidence': [evidence(build_path, 'Native data generators'), evidence(build_path, '--embed-file')]},
        ],
        'manifest_dependency_source_integrity': integrity,
        'wasm_artifact_matches_manifest': READS.get(relative(binary_path), {}).get('sha256') == manifest.get('wasmSha256'),
        'recorded_public_validation': {
            'available': recording is not None, 'path': relative(recording_path),
            **({key: recording.get(key) for key in ['sessions', 'passed', 'errors', 'metrics', 'wasmSha256', 'dependencyBackend']} if recording else {}),
            'matches_selected_wasm_artifact': bool(recording and recording.get('wasmSha256') == READS.get(relative(binary_path), {}).get('sha256')),
            'scope_limit': 'Recorded result, not a fresh run. Wasm hash pairs the binary; current adapter/service JS is not cryptographically included in that summary.'},
        'wasm_import_surface': surface,
        'symbol_map': {'path': relative(symbols_path), 'name_count': len(indexed),
                       'declared_function_total': imported_count + surface['defined_function_count'],
                       'index_coverage_matches_artifact': set(indexed) == set(range(imported_count + surface['defined_function_count'])),
                       'javascript_import_names': sorted(imported), 'defined_wasm_function_names': sorted(defined),
                       'freshness_limit': 'Symbol map is not hashed in the build manifest. Count/index agreement is a consistency check, not cryptographic pairing.'},
        'remaining_game_object_count': len(engine_objects), 'remaining_game_objects': engine_objects,
        'defined_wasm_teleport_helper_prefix_count': sum(name.startswith('teleport_') for name in defined),
        'external_c_residuals': [
            {'dependency': 'Lua 5.4.8', 'selected_status': 'compiled C interpreter/runtime retained',
             'compiled_lua_prefix_name_count': len(lua_names), 'compiled_lua_prefix_names': lua_names,
             'compiled_library_openers': sorted(name for name in defined if name.startswith('luaopen_')),
             'evidence': [evidence(build_path, 'wasm_lua = '), evidence(build_path, 'LUALIBS=')]},
            {'dependency': 'C libc/system support', 'selected_status': 'compiled/runtime services retained',
             'curated_defined_function_groups': groups, 'allocator_implementation_names': allocator,
             'capability_limit': 'Defined native-looking names can be Emscripten wrappers or stubs. Their presence does not establish host process/filesystem capabilities or complete POSIX behavior.',
             'evidence': [evidence('nethack-c/wasm/tu-libraries/calendar.js', "'mktime'"),
                          evidence('nethack-c/wasm/dependency-library.js', "'$FS'")]},
            {'dependency': 'ncurses terminfo, ncompress, musl TRE algorithms',
             'selected_status': 'JavaScript selected; C ABI support remains' if selected == 'javascript' else 'Compiled reference backend or unresolved',
             'known_algorithm_prefix_names_still_defined': algorithms,
             'retained_c_forwarder_definitions': sorted(set(abi_names)),
             'retained_c_terminfo_globals': ['ospeed', 'PC', 'BC', 'UP'],
             'retained_services': ['C varargs decoding', 'C output callback dispatch', 'malloc/free/strlen/memcpy and C-backed output buffers', 'opaque regex_t storage and forwarder ABI'],
             'warning': 'Algorithm-prefix absence alone does not prove removal. Manifest selection, source/ABI evidence and binary import boundaries are independent evidence.',
             'evidence': [evidence(build_path, 'if C_DEPENDENCIES:'), evidence(abi_source, 'int tputs('), evidence(abi_source, 'char *tparm(')]},
        ],
        'emscripten_residuals': {
            'status': 'selected game still requires Wasm/Emscripten',
            'services': ['memory64 linear heap/stack and allocator', 'C ABI/global/static storage and callback table',
                         'MEMFS and file/stdio/syscall services', 'ENV/environment construction',
                         'embedded assets/startup constructors/callMain', 'time/timezone Date delegates',
                         'input-exhaustion unwind, exit, signals and longjmp helpers'],
            'import_names': sorted(name for name in imported if name.startswith(('__wasi_', '__syscall_', '_emscripten', 'emscripten_', '_tzset_', '_mktime_', '_localtime_', '_gmtime_', '_abort_'))),
            'evidence': [evidence('js/wasm-adapter.js', "await import('./wasm/nethack.mjs')"),
                         evidence('js/wasm-adapter.js', 'module.callMain'),
                         evidence(build_path, '-sEXPORTED_RUNTIME_METHODS=FS,ENV,callMain')]},
        'ghostty': {'selected': False if 'createTerminalBackend' not in adapter and "import { createTerminalBackend" not in adapter else 'unresolved',
                    'standalone_diagnostic_file_present': (ROOT / 'js/terminal-backend.js').is_file(),
                    'evidence': [evidence('js/wasm-adapter.js', "const terminalDiagnostics = { backend: 'shadow' }")],
                    'limitation': 'This is an adapter source observation; historical standalone diagnostic artifacts are not active runtime dependencies.'},
    }


def source_sizes(tree, active=None):
    lua = tree / 'lib/lua-5.4.8/src'
    makefile = read(lua / 'Makefile')
    groups = {}
    for group in ('CORE_O', 'LIB_O'):
        match = re.search(r'^' + group + r'=\s*(.*)$', makefile, re.M)
        files = re.findall(r'(\w+)\.o', match[1]) if match else []
        groups[group] = size(lua / (name + '.c') for name in files)
    groups['headers'] = size(lua.glob('*.h'))
    regex = ROOT / '.cache/emsdk/upstream/emscripten/system/lib/libc/musl/src/regex'
    ncurses = ROOT / '.cache/ncurses-6.5'
    ncbuild = ROOT / '.cache/ncurses-wasm64-build/ncurses'
    nc_make = read(ncbuild / 'Makefile')
    match = re.search(r'^NORMAL_T_OBJS\s*=\s*([\s\S]*?)(?=\n\n)', nc_make, re.M)
    objects = re.findall(r'../objects/(\w+)\$o', match[1]) if match else []
    vars_ = {'tinfo': ncurses / 'ncurses/tinfo', 'base': ncurses / 'ncurses/base',
             'serial': ncurses / 'ncurses/tty', 'trace': ncurses / 'ncurses/trace',
             'srcdir': ncurses / 'ncurses'}
    object_sources, unresolved = [], []
    for obj in objects:
        rule = re.search(r'^\.\./objects/' + re.escape(obj) + r'\$o\s*:\s*([^\s\\]+)', nc_make, re.M)
        if not rule:
            unresolved.append(obj)
            continue
        value = rule[1]
        for var, base in vars_.items():
            value = value.replace('$(' + var + ')', str(base)).replace('${' + var + '}', str(base))
        path = Path(value)
        if not path.is_absolute():
            path = ncbuild / path
        path = path.resolve()
        if path.suffix == '.c' and path.is_file():
            object_sources.append(path)
        else:
            unresolved.append({'object': obj, 'source_token': rule[1]})
    central = ['lib_termcap', 'lib_tparm', 'lib_tputs', 'read_entry', 'lib_setup', 'lib_cur_term']
    read(ROOT / 'nethack-c/wasm/terminfo/x/xterm-256color')
    return {
        'measurement': 'Physical source lines, including comments and blanks. Not JS rewrite size or dynamic/linker closure.',
        'lua_5_4_8': {'group_source': relative(lua / 'Makefile'), **groups,
                      'library_c_total': groups['CORE_O']['physical_lines'] + groups['LIB_O']['physical_lines'],
                      'nethack_binding_files_already_in_game_inventory': size(tree / 'src' / name for name in ['nhlua.c', 'nhlobj.c', 'nhlsel.c'])},
        'ncompress_5_0': {'codec': size([ROOT / 'nethack-c/wasm/vendor/ncompress/compress.c']),
                          'wrapper': size([ROOT / 'nethack-c/wasm/compress-service.c'])},
        'musl_posix_regex': {'implementation': size(regex / name for name in ['regcomp.c', 'regexec.c', 'regerror.c', 'tre-mem.c']),
                            'internal_header': size([regex / 'tre.h']),
                            'excluded_siblings': ['fnmatch.c', 'glob.c']},
        'ncurses_6_5': {
            'library_measurement_role': 'Reference/C-backend libtinfo archive; selected JS backend uses its headers/data, not the C library.'
                if active and active['built_dependency_backend'] == 'javascript'
                else 'Configured libtinfo archive; curses UI library is not selected.',
            'configured_archive_object_count': len(objects),
            'configured_archive_source_files': size(object_sources),
            'unresolved_archive_objects': unresolved,
            'central_six_files_incomplete_subset': size(ncurses / 'ncurses/tinfo' / (name + '.c') for name in central),
            'pinned_entry': {'path': 'nethack-c/wasm/terminfo/x/xterm-256color',
                             'bytes': len((ROOT / 'nethack-c/wasm/terminfo/x/xterm-256color').read_bytes())},
            'closure_warning': 'Archive membership includes unused objects. Six central files omit supporting routines. Neither number proves the needed reachable terminfo subset.'}}


def service_inventory(active):
    sources = [path for path in sorted((ROOT / 'js').rglob('*.js'))
               if '/wasm/' not in relative(path) and '/vendor/' not in relative(path)]
    texts = {path: read(path) for path in sources}
    edges, importers = defaultdict(list), defaultdict(list)
    for importer, text in texts.items():
        for match in re.finditer(r'''\b(?:from\s*|import\(\s*)['"]([^'"]+)['"]''', strip_comments(text)):
            if not match[1].startswith('.'):
                continue
            target = (importer.parent / match[1]).resolve()
            edges[importer].append(target)
            importers[target].append(location(importer, text, match.start()))

    def reachable(start):
        seen, pending = set(), [ROOT / start]
        while pending:
            path = pending.pop()
            if path in seen:
                continue
            seen.add(path); pending.extend(edges[path])
        return seen

    adapter_graph = reachable('js/wasm-adapter.js')
    standalone_graph = reachable('js/ported/js-runtime.js')
    selected_sources = {ROOT / path for path in active_source_paths(active)}
    services = []
    for path in sorted((ROOT / 'js/services').rglob('*.js')):
        text = texts[path] if path in texts else read(path)
        selected_algorithm = path in selected_sources and active['built_dependency_backend'] == 'javascript'
        if selected_algorithm:
            status = 'selected_game_javascript_dependency_or_abi_adapter'
        elif path.name == 'game-files.js' and path in adapter_graph:
            status = 'selected_game_transport_with_injected_emscripten_filesystem'
        elif path in standalone_graph:
            status = 'standalone_provider_only_not_selected_game_runtime'
        elif path.parent.name == 'lua':
            status = 'partial_standalone_lua_only_not_selected_game_interpreter'
        else:
            status = 'present_but_selected_runtime_use_unresolved'
        services.append({'path': relative(path), 'physical_lines': len(text.splitlines()),
                         'status': status, 'reachable_from_adapter_by_literal_import_graph': path in adapter_graph,
                         'reachable_from_standalone_provider_by_literal_import_graph': path in standalone_graph,
                         'selected_build_manifest_source': path in selected_sources,
                         'exports_observed': sorted(set(re.findall(r'\bexport\s+(?:async\s+)?(?:function|class|const|let)\s+(\w+)', strip_comments(text)))),
                         'static_js_import_sites': importers[path]})
    lapi_path = ROOT / 'js/services/lua/lapi.js'
    lapi = texts.get(lapi_path, '')
    methods = sorted(set(re.findall(r'^\s{2}((?:lua|luaL)_\w+)\s*\(', strip_comments(lapi), re.M)))
    unsupported = sorted(set(re.findall(r'^\s{2}((?:lua|luaL)_\w+)\([^\n]*?\)\s*\{\s*return this\.unsupported\(', strip_comments(lapi), re.M)))
    lua_limits = []
    for path in sorted((ROOT / 'js/services/lua').glob('*.js')):
        text = texts.get(path, '')
        for line, value in enumerate(text.splitlines(), 1):
            if re.search(r'NOT a complete|Missing:|full C stack|GC/finaliz|table hashing|tail calls|goto/<close>|unfinished|not simulated|await deterministic', value):
                lua_limits.append({'path': relative(path), 'line': line, 'excerpt': value.strip()[:260]})
    tests = ['scripts/test-js-compress.mjs', 'scripts/test-js-terminfo.mjs', 'scripts/test-js-posix-regex.mjs',
             'scripts/test-js-runtime.mjs', 'scripts/test-js-runtime-regex.mjs', 'scripts/test-js-time.mjs', 'scripts/test-js-vfs.mjs',
             'scripts/test-js-lua.mjs', 'scripts/test-js-lua-api.mjs', 'scripts/test-js-dependency-isolation.mjs']
    for path in tests:
        read(ROOT / path)
    return {
        'method': 'Literal static imports plus selected manifest source hashes and inspected provider wiring. Imports may be conditional and do not establish executed call closure.',
        'modules': services,
        'standalone_provider': {
            'path': 'js/ported/js-runtime.js', 'selected_by_active_adapter': ROOT / 'js/ported/js-runtime.js' in adapter_graph,
            'translated_subsystems': [name + '.c' for name in sorted(set(re.findall(r'''\bimport\s+\*\s+as\s+\w+\s+from\s+['"]\./([^'"]+)\.js['"]''', strip_comments(texts[ROOT / 'js/ported/js-runtime.js']))))],
            'services': ['JavaScript-owned ArrayBuffer memory', 'bounded LP64 strings/integer formatting/parsing',
                         'Date-based calendar/time compatibility', 'regular-file/directory VFS and stream facade',
                         'per-instance environment and scoped C bindings', 'opaque-handle configured ERE through unchanged posixregex translation'],
            'limitations': ['Not the complete game state/global layout/runtime', 'No C stdio layer or full libc',
                            'No full IANA/POSIX per-instance timezone database or strftime',
                            'VFS excludes device/socket/symlink/mount/lock/ownership/ACL/chmod services'],
            'evidence': [evidence('js/ported/js-runtime.js', 'new CMemory'), evidence('js/ported/js-runtime.js', 'new CVFS'),
                         evidence('js/ported/js-runtime.js', 'calendar:'), evidence('js/ported/js-runtime.js', 'posixregex:')]},
        'partial_lua': {
            'selected_game_interpreter_replaced': False,
            'entrypoint': 'js/services/lua/lua.js', 'api_entrypoint': 'js/services/lua/lapi.js',
            'implementation_form': 'Bounded Lua 5.4 AST interpreter and partial C API, not a complete opcode VM or drop-in C ABI replacement.',
            'method_names_observed_in_lapi_class': methods,
            'direct_explicit_unsupported_methods': unsupported,
            'direct_explicit_unsupported_method_count': len(unsupported),
            'additional_complete_library_opener_unsupported': 'luaL_openlibs' if "luaL_openlibs() { throw" in lapi else None,
            'explicit_unsupported_count_including_complete_library_opener': len(unsupported) + int("luaL_openlibs() { throw" in lapi),
            'configured_call_limit': 'lua_resetthread occurs under notyet/#if0 and luaL_openlibs is in the inactive non-sandbox branch. Their explicit unsupported methods are not configured-game blockers.',
            'source_declared_limitations': lua_limits,
            'remaining_gates': ['Complete NetHack-used API semantics and bind game nh/des/selection/object callbacks',
                                'Preserve table hashing/iteration/holed-length behavior', 'GC/finalizers/memory accounting and configured limits',
                                'Exact instruction hooks, continuation/finalization, diagnostics and remaining syntax/library behavior',
                                'Differentially execute original scripts and level/quest generation before selecting this interpreter'],
        },
        'game_file_transport': {'selected_in_adapter': ROOT / 'js/services/game-files.js' in adapter_graph,
                                'filesystem_currently_supplied': 'Emscripten module.FS/MEMFS',
                                'standalone_vfs_replaces_active_memfs': False,
                                'payload': 'Existing {files,deleted} transport; binary base64; persistence filter injected by adapter',
                                'evidence': [evidence('js/wasm-adapter.js', "from './services/game-files.js'"),
                                             evidence('js/wasm-adapter.js', 'captureGameFiles(module.FS')]},
        'test_entrypoints': tests,
        'verification_limit': 'The inventory records test entrypoints, not a fresh test run or coverage/equivalence certification.'}


def active_source_paths(active):
    return [entry['path'] for entry in active['manifest_dependency_source_integrity']]


def lua_inventory(tree):
    calls, initializers, script_members = defaultdict(list), [], defaultdict(list)
    for path in sorted((tree / 'src').glob('*.c')):
        text = read(path)
        clean = strip_comments(text)
        for match in re.finditer(r'\b(lua(?:L)?_[A-Za-z0-9_]+|luaopen_[A-Za-z0-9_]+)\s*\(', clean):
            calls[match[1]].append(location(path, text, match.start()))
        for match in re.finditer(r'nhl_sandbox_info\s+\w+\s*=\s*\{([^}]+)\}', clean, re.S):
            initializers.append({'initializer': re.sub(r'\s+', ' ', match[1]).strip(),
                                 'evidence': location(path, text, match.start())})
    for path in sorted((tree / 'dat').glob('*.lua')):
        text = read(path)
        # Lua comments/strings are not parsed; label results as tokens only.
        for match in re.finditer(r'\b(math|table|string|utf8|coroutine|debug|os|io|package)\s*\.\s*([A-Za-z_]\w*)', text):
            script_members[match[1] + '.' + match[2]].append(location(path, text, match.start()))
    nhlua = tree / 'src/nhlua.c'
    text = read(nhlua)
    filters = []
    for match in re.finditer(r'static struct e\s+(ct_\w+)\[\]\s*=\s*\{([\s\S]*?)\n\};', text):
        filters.append({'name': match[1], 'entries': [
            {'condition': item[0], 'function': item[1]}
            for item in re.findall(r'\{\s*(IFFLAG|NEVER)\s*,\s*"([^"]+)"', match[2])],
            'evidence': location(nhlua, text, match.start())})
    read(tree / 'include/config.h')
    read(tree / 'include/global.h')
    return {'api_observations': [{'name': name, 'sites': sites} for name, sites in sorted(calls.items())],
            'unique_api_name_count': len(calls), 'sandbox_initializers': initializers,
            'sandbox_filters': filters,
            'script_member_tokens': [{'name': name, 'sites': sites} for name, sites in sorted(script_members.items())],
            'scope_assessment': {
                'confidence': 'medium: source/configuration review; not preprocessed or dynamically instrumented',
                'normal_states': ['restricted base', 'coroutine', 'table', 'string', 'math', 'utf8'],
                'additional_states': ['wizard debugging enables debug.traceback', 'version information state'],
                'inactive_observed_states_and_calls': [
                    {'name': 'string-only pattern matching state', 'condition': '#ifdef notyet',
                     'evidence': evidence(relative(nhlua), 'start_luapat(void)')},
                    {'name': 'lua_resetthread', 'condition': '#ifdef notyet and nested #if0',
                     'configured_game_blocker': False, 'evidence': evidence(relative(nhlua), 'lua_resetthread(luapat)')},
                    {'name': 'luaL_openlibs', 'condition': 'non-sandbox #else branch; prepared config enables NHL_SANDBOX',
                     'configured_game_blocker': False, 'evidence': evidence(relative(nhlua), 'luaL_openlibs(L);')},
                ],
                'not_normally_requested': ['io', 'os', 'package/module loader'],
                'preserve': ['Lua 5.4.8 integer/float semantics and strings', 'parser/compiler and VM',
                             'core garbage collector and userdata lifecycle/finalization; these are not removable standard-library features',
                             'tables, iteration, metamethods, userdata and object identity',
                             'C API stack and callbacks used by NetHack', 'registry/upvalues/metatables',
                             'errors/protected calls/tracebacks',
                             'instruction hooks and memory limits for configured sandbox states',
                             'Lua patterns, coroutine/table/string/math/UTF-8 behavior',
                             'seeded math.random and NetHack RNG call ordering',
                             'original level/quest scripts and NetHack nh/des/selection/object bindings'],
                'unresolved': ['Actual reachable opcode/API/library subset',
                               'Effects of compiled conditionals and alternate sandbox flags',
                               'Exact heap accounting/GC effects of an alternative interpreter',
                               'Ordering and numeric corner cases beyond the public recordings'],
                'evidence': [evidence(relative(nhlua), 'nhlL_openlibs(L, sbi->flags)'),
                             evidence(relative(tree / 'include/config.h'), '#define NHL_SANDBOX'),
                             evidence(relative(tree / 'include/global.h'), '#define NHL_SB_SAFE')]},
            'observation_limits': 'C call-name matches retain inactive branches/macros. Lua member tokens can include strings/comments, miss aliases and computed access; they are not an API allowlist.'}


def build_report():
    READS.clear()
    MISSING.clear()
    tree = ROOT / '.cache/wasm64-build/tree'
    game_tokens = set()
    for base in ['src', 'include', 'sys/unix', 'win/tty']:
        for path in sorted((tree / base).glob('*')):
            if path.suffix in ('.c', '.h'):
                game_tokens.update(re.findall(r'\b[A-Za-z_]\w*\b', strip_comments(read(path))))
    read(ROOT / 'nethack-c/wasm/build.py')
    read(ROOT / 'nethack-c/wasm/build_terminfo.py')
    read(ROOT / 'nethack-c/wasm/bridge.c')
    read(ROOT / 'nethack-c/wasm/tu-support.c')
    ports = json.loads(read(ROOT / 'nethack-c/wasm/tu-ports.json') or '[]')
    manifest = json.loads(read(ROOT / 'js/wasm/build.json') or '{}')
    active = active_inventory(manifest)
    service_sets = []
    for category, names in sorted(LIBC.items()):
        observations = []
        for name in sorted(names):
            if name in game_tokens:
                observations.append(name)
        service_sets.append({'category': category, 'game_text_tokens': observations})
    report = {
        'schema_version': 2,
        'generator': 'scripts/audit-js-dependencies.py',
        'purpose': 'Read-only migration inventory; no production implementation or defaults changed.',
        'snapshot': {'configured_js_tu_count': len(ports),
                     'built_js_tu_count': len(manifest.get('javascriptTranslationUnits', [])),
                     'built_emscripten': manifest.get('emscripten'), 'built_upstream': manifest.get('upstream'),
                     'configured_port_names': [p['name'] for p in ports],
                     'configured_only_port_names': sorted(set(p['name'] for p in ports) - set(p['name'] for p in manifest.get('javascriptTranslationUnits', []))),
                     'built_only_port_names': sorted(set(p['name'] for p in manifest.get('javascriptTranslationUnits', [])) - set(p['name'] for p in ports)),
                     'build_and_config_can_differ': True},
        'selected_runtime': active,
        'source_provenance': {
            'pristine_reference': 'nethack-c/upstream',
            'measured_game_and_lua': '.cache/wasm64-build/tree',
            'prepared_tree_contains': 'Pinned pristine reference plus inherited patches, build.py source adaptations, generated configuration/data, and extracted Lua source.',
            'identity_limit': 'Prepared tree may predate or differ from current build script/configuration. Hashes are file content evidence, not a fresh-build attestation.',
            'evidence': [evidence('nethack-c/wasm/build.py', "PIN = "),
                         evidence('nethack-c/wasm/build.py', "for patch in sorted"),
                         evidence('nethack-c/wasm/build.py', "replace('include/unixconf.h'")]},
        'source_sizes': source_sizes(tree, active),
        'tu_dependencies': collect_tu_dependencies(game_tokens, active),
        'dependency_abi_library': collect_tu_dependencies(game_tokens, active, [ROOT / 'nethack-c/wasm/dependency-library.js']),
        'runtime_observations': collect_runtime(),
        'compiled_service_candidates': {'method': 'Known libc/terminfo names matched as tokens in prepared C/headers; not calls or reachable closure.',
                                        'libc_groups': service_sets, 'terminfo_game_tokens': sorted(TERMINFO & game_tokens)},
        'compiled_service_sites': collect_compiled_service_sites(tree),
        'lua': lua_inventory(tree),
        'runtime_layers': [
            {'name': 'remaining_game_code', 'disposition': 'port incrementally; coordinate with active TU work', 'evidence': ['js/wasm/link-objects.txt', 'nethack-c/wasm/tu-ports.json']},
            {'name': 'c_abi_and_linear_memory', 'disposition': 'preserve addresses/layout/integer semantics initially; replace C helpers and Wasm memory ownership', 'evidence': ['nethack-c/wasm/tu-support.c', 'js/ported/wasm-runtime.js']},
            {'name': 'libc_regex_time_files', 'disposition': 'JS regex selected through C ABI forwarders; compiled libc/time/MEMFS remain selected. Standalone bounded JS services do not replace the active game runtime.', 'evidence': ['nethack-c/wasm/tu-libraries/posixregex.js', 'nethack-c/wasm/tu-libraries/calendar.js', 'js/ported/js-runtime.js']},
            {'name': 'assets', 'disposition': 'embed generated game data and pinned terminal entry as JS-accessible assets; native generators remain development-only', 'evidence': ['nethack-c/wasm/build.py']},
            {'name': 'replay_adapter_environment_startup', 'disposition': 'Game-file transport extracted and selected; active adapter still supplies Emscripten FS/ENV/startup/callMain/unwind. Standalone VFS/time/memory provider is separate.', 'evidence': ['js/wasm-adapter.js', 'js/services/game-files.js', 'js/ported/js-runtime.js']},
            {'name': 'terminfo_capabilities', 'disposition': 'Pinned-entry JS terminfo selected; ncurses headers/data/reference build retained, C libtinfo excluded from selected runtime. C vararg/callback ABI support remains.', 'evidence': ['nethack-c/wasm/build.py', 'nethack-c/wasm/dependency-bridge.c', 'js/services/terminfo.js']},
            {'name': 'input_output_transport', 'disposition': 'preserve keyboard byte mapping and input-exhaustion boundary', 'evidence': ['nethack-c/wasm/bridge.c', 'js/wasm-adapter.js']},
            {'name': 'shadow_screen_capture', 'disposition': 'preserve inherited default capture and frame timing separately from transport/terminfo', 'evidence': ['nethack-c/wasm/build.py', 'js/wasm-adapter.js']},
            {'name': 'historical_ghostty_emulation', 'disposition': 'Removed from active adapter selection/import path. Historical standalone diagnostic file remains outside selected game runtime.', 'evidence': ['js/wasm-adapter.js']},
            {'name': 'snapshot_serialization', 'disposition': 'preserve recorder encoding/cursor/animation/RNG log conventions independently of terminal emulation', 'evidence': ['js/wasm-replay-support.js', 'js/wasm-adapter.js']},
        ],
        'migration_backlog': [
            {'order': 1, 'id': 'boundary_inventory', 'depends_on': [], 'action': 'Validate and refine static inventory with link maps and instrumented boundary traces.', 'gate': ['Every used compiled service has an owner and differential fixture', 'Unresolved static symbols are explicitly reviewed; no claim that public traces prove closure']},
            {'order': 2, 'id': 'js_memory_state', 'depends_on': ['boundary_inventory'], 'action': 'Run one translated subsystem on JS-owned memory/state through a second service provider.', 'gate': ['No C/Module/WebAssembly service accessed by that subsystem', 'Addresses, aliasing, widths, callbacks, initialization and instance isolation compare with reference']},
            {'order': 3, 'id': 'bounded_services', 'depends_on': ['boundary_inventory'], 'action': 'Replace allocation/strings/formatting/files/environment services needed by the selected subsystem.', 'gate': ['C byte strings, integer formatting, errno/errors, file modes/positions and buffer lifetimes have reference comparisons', 'Node and browser fixtures execute the same JS provider']},
            {'order': 4, 'id': 'compression', 'depends_on': ['boundary_inventory'], 'action': 'Use or implement JS Unix .Z codec and preserve file operation status/cleanup.', 'gate': ['Native-to-JS and JS-to-native round trips', 'Dictionary growth/reset, empty/truncated/malformed inputs, failures and save/bones lifecycle checked']},
            {'order': 5, 'id': 'terminfo', 'depends_on': ['boundary_inventory'], 'action': 'Implement required capability lookup/database/parameter/output semantics against the pinned entry.', 'gate': ['All game-used capability APIs compared with ncurses', 'Parameter stack/arithmetic, missing capabilities, padding/callbacks and terminal setup tested', 'Capture, emulation, transport and serialization remain independently verified']},
            {'order': 6, 'id': 'regex_time', 'depends_on': ['boundary_inventory'], 'action': 'Replace POSIX regex and recording date/time services with compatible JS implementations.', 'gate': ['POSIX flags, matching semantics, errors and resource lifecycle compared with libc', 'Fixed datetime, recording epoch, timezone/DST and integer/date boundaries checked']},
            {'order': 7, 'id': 'lua', 'depends_on': ['boundary_inventory'], 'parallel_start': 'Start compatibility investigation at order 1; do not defer until final TU.', 'action': 'Evaluate pure-JS interpreters or implement Lua 5.4.8 required VM/C API/library semantics and NetHack bindings.', 'gate': ['Original scripts execute; no precomputed replacement for dynamic behavior', 'Lua integers/floats, iteration, callbacks, protected calls, sandbox hooks/limits and seeded random compare', 'Level/quest generation and object/selection bindings match across seeds beyond public recordings']},
            {'order': 8, 'id': 'startup_capture_persistence', 'depends_on': ['js_memory_state', 'bounded_services', 'compression', 'terminfo', 'regex_time', 'lua'], 'action': 'Move initialization/assets/input/capture/save restoration onto per-instance JS runtime.', 'gate': ['Fresh instance and deterministic segment restart behavior', 'Save/bones and deletion semantics match frozen storage API', 'Screen/cursor/animation/RNG sequence equality against public recordings and targeted cases']},
            {'order': 9, 'id': 'independence', 'depends_on': ['startup_capture_persistence'], 'action': 'Cut over only when remaining game TUs and external services are JS-owned.', 'gate': ['Frozen harness passes in Node 22 and Chrome', 'Run with WebAssembly disabled and native subprocess/filesystem/network fallbacks unavailable', 'No runtime fetches or hidden compiled fallbacks', 'Inspect package dependency closure, licenses/assets and dynamic imports', 'Public recordings exact and additional differential cases pass; hidden-case equivalence remains unproven']},
        ],
        'unresolved': [
            'Static analysis does not establish reachable function closure, external dependency completeness, or standalone JavaScript independence.',
            'Prepared source, configuration, generated build manifest and active files may change concurrently; hashes record the inputs actually read.',
            'Reference terminfo archive sizes are historical/C-backend scope, not active JS implementation size or runtime closure.',
            'Full libc/formatting/time/filesystem/transitive-helper inventory remains open beyond curated token categories.',
            'Lua inactive branches, scripts loaded through generated data, runtime aliases and alternate flags need dynamic/preprocessed evidence.',
            'Compression/terminfo/ERE are selected in the active build manifest; the audit does not rerun their validation suites.',
            'Standalone memory/time/VFS and partial Lua presence does not replace the selected game Emscripten runtime or compiled Lua.',
        ],
    }
    report['javascript_service_inventory'] = service_inventory(active)
    lua_candidate = report['javascript_service_inventory']['partial_lua']
    required_lua_names = [entry['name'] for entry in report['lua']['api_observations']]
    observed_lua_names = set(lua_candidate['method_names_observed_in_lapi_class'])
    lua_candidate['c_call_names_observed_including_inactive_branches'] = required_lua_names
    lua_candidate['name_matches_only_not_semantic_coverage'] = sorted(set(required_lua_names) & observed_lua_names)
    lua_candidate['observed_names_not_matching_lapi_class_methods'] = sorted(set(required_lua_names) - observed_lua_names)
    backlog_status = {
        'boundary_inventory': 'inventory_updated_remaining_closure_work',
        'js_memory_state': 'bounded_subsystems_on_standalone_provider_not_selected_game',
        'bounded_services': 'implemented_bounded_standalone_services_not_full_libc',
        'compression': 'selected_javascript_configured_scope',
        'terminfo': 'selected_javascript_pinned_entry_scope',
        'regex_time': 'regex_selected_javascript_time_standalone_only',
        'lua': 'partial_standalone_interpreter_compiled_lua_still_selected',
        'startup_capture_persistence': 'game_file_transport_extracted_active_memfs_retained',
        'independence': 'not_achieved_wasm_emscripten_and_compiled_lua_remain',
    }
    for entry in report['migration_backlog']:
        entry['current_status'] = backlog_status[entry['id']]
    report['migration_backlog'][3]['action'] = 'Retain selected JS codec and differential gates; replace remaining MEMFS/C ABI dependence during standalone runtime integration.'
    report['migration_backlog'][4]['action'] = 'Retain pinned-entry JS terminfo; remove remaining tparm/tputs C ABI support when game callers and callback state are JS-owned.'
    report['migration_backlog'][5]['action'] = 'Keep configured JS ERE selected; wire the separately implemented JS calendar/time provider into the active game through controlled integration.'
    runtime_markers = {
        'nethack-c/wasm/build.py': 'link_flags = ',
        'nethack-c/wasm/build_terminfo.py': "'--with-termlib'",
        'nethack-c/wasm/tu-support.c': 'teleport_',
        'nethack-c/wasm/bridge.c': 'teleport_getch',
        'js/ported/wasm-runtime.js': 'createPortedRuntime',
        'js/wasm-adapter.js': 'runWasmSegment',
        'js/wasm-replay-support.js': 'encodeRecorderScreen',
        'js/recording-profile.js': 'recordingProfile',
        'js/ported/js-runtime.js': 'createJsRuntime',
        'js/services/game-files.js': 'captureGameFiles',
        'js/services/terminfo.js': 'createTerminfo',
        'nethack-c/wasm/dependency-bridge.c': 'int tputs(',
        'nethack-c/wasm/tu-libraries/posixregex.js': "'regcomp'",
        'nethack-c/wasm/tu-libraries/calendar.js': "'mktime'",
    }
    for layer in report['runtime_layers']:
        layer['evidence'] = [evidence(path, runtime_markers.get(path)) for path in layer['evidence']]
    # Evidence exists separately from layer descriptions, including optional files.
    for path in ['js/wasm/link-objects.txt', 'nethack-c/wasm/compile-defines.json']:
        read(ROOT / path)
    report['missing_inputs'] = sorted(MISSING)
    report['evidence_files'] = dict(sorted(READS.items()))
    return report


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', type=Path, default=ROOT / 'dependency-inventory.json')
    parser.add_argument('--check', action='store_true', help='Compare generated content to output without writing.')
    args = parser.parse_args()
    report = build_report()
    content = json.dumps(report, indent=2, sort_keys=True) + '\n'
    if args.check:
        if not args.output.is_file() or args.output.read_text() != content:
            raise SystemExit('Dependency inventory differs; regenerate after reviewing active source changes.')
        print('Dependency inventory is current.')
    else:
        args.output.write_text(content)
        print(f'Wrote {args.output}: {report["tu_dependencies"]["unique_symbol_count"]} unique TU dependency symbols; {len(report["missing_inputs"])} missing inputs.')


if __name__ == '__main__':
    main()
