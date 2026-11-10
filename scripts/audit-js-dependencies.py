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


def collect_tu_dependencies(game_tokens):
    libraries = []
    users = defaultdict(list)
    dependency_pattern = re.compile(r'([\w$]+)__deps\s*:\s*\[([^\]]*)\]', re.S)
    for path in sorted((ROOT / 'nethack-c/wasm/tu-libraries').glob('*.js')):
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
        symbols.append({'symbol': symbol, 'category': category, 'confidence': confidence,
                        'uses': uses})
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
    paths = [ROOT / 'js/wasm-adapter.js', ROOT / 'js/terminal-backend.js',
             ROOT / 'js/wasm-replay-support.js', ROOT / 'js/recording-profile.js',
             ROOT / 'nethack-c/wasm/runtime.js']
    paths += sorted((ROOT / 'js/ported').glob('*runtime.js'))
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


def source_sizes(tree):
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
            'linked_library': 'libtinfo.a only; curses UI library is not linked by build.py',
            'configured_archive_object_count': len(objects),
            'configured_archive_source_files': size(object_sources),
            'unresolved_archive_objects': unresolved,
            'central_six_files_incomplete_subset': size(ncurses / 'ncurses/tinfo' / (name + '.c') for name in central),
            'pinned_entry': {'path': 'nethack-c/wasm/terminfo/x/xterm-256color',
                             'bytes': len((ROOT / 'nethack-c/wasm/terminfo/x/xterm-256color').read_bytes())},
            'closure_warning': 'Archive membership includes unused objects. Six central files omit supporting routines. Neither number proves the needed reachable terminfo subset.'}}


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
                'additional_states': ['wizard debugging enables debug.traceback', 'string-only pattern matching state', 'version information state'],
                'not_normally_requested': ['io', 'os', 'package/module loader'],
                'preserve': ['Lua 5.4.8 integer/float semantics and strings', 'parser/compiler and VM',
                             'core garbage collector and userdata lifecycle/finalization; these are not removable standard-library features',
                             'tables, iteration, metamethods, userdata and object identity',
                             'C API stack and callbacks used by NetHack', 'registry/upvalues/metatables',
                             'errors/protected calls/tracebacks and thread reset',
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
    service_sets = []
    for category, names in sorted(LIBC.items()):
        observations = []
        for name in sorted(names):
            if name in game_tokens:
                observations.append(name)
        service_sets.append({'category': category, 'game_text_tokens': observations})
    report = {
        'schema_version': 1,
        'generator': 'scripts/audit-js-dependencies.py',
        'purpose': 'Read-only migration inventory; no production implementation or defaults changed.',
        'snapshot': {'configured_js_tu_count': len(ports),
                     'built_js_tu_count': len(manifest.get('javascriptTranslationUnits', [])),
                     'built_emscripten': manifest.get('emscripten'), 'built_upstream': manifest.get('upstream'),
                     'configured_port_names': [p['name'] for p in ports],
                     'build_and_config_can_differ': True},
        'source_provenance': {
            'pristine_reference': 'nethack-c/upstream',
            'measured_game_and_lua': '.cache/wasm64-build/tree',
            'prepared_tree_contains': 'Pinned pristine reference plus inherited patches, build.py source adaptations, generated configuration/data, and extracted Lua source.',
            'identity_limit': 'Prepared tree may predate or differ from current build script/configuration. Hashes are file content evidence, not a fresh-build attestation.',
            'evidence': [evidence('nethack-c/wasm/build.py', "PIN = "),
                         evidence('nethack-c/wasm/build.py', "for patch in sorted"),
                         evidence('nethack-c/wasm/build.py', "replace('include/unixconf.h'")]},
        'source_sizes': source_sizes(tree),
        'tu_dependencies': collect_tu_dependencies(game_tokens),
        'runtime_observations': collect_runtime(),
        'compiled_service_candidates': {'method': 'Known libc/terminfo names matched as tokens in prepared C/headers; not calls or reachable closure.',
                                        'libc_groups': service_sets, 'terminfo_game_tokens': sorted(TERMINFO & game_tokens)},
        'compiled_service_sites': collect_compiled_service_sites(tree),
        'lua': lua_inventory(tree),
        'runtime_layers': [
            {'name': 'remaining_game_code', 'disposition': 'port incrementally; coordinate with active TU work', 'evidence': ['js/wasm/link-objects.txt', 'nethack-c/wasm/tu-ports.json']},
            {'name': 'c_abi_and_linear_memory', 'disposition': 'preserve addresses/layout/integer semantics initially; replace C helpers and Wasm memory ownership', 'evidence': ['nethack-c/wasm/tu-support.c', 'js/ported/wasm-runtime.js']},
            {'name': 'libc_regex_time_files', 'disposition': 'replace required behavior through explicit JS services and differential tests', 'evidence': ['nethack-c/wasm/tu-libraries/posixregex.js', 'nethack-c/wasm/tu-libraries/calendar.js']},
            {'name': 'assets', 'disposition': 'embed generated game data and pinned terminal entry as JS-accessible assets; native generators remain development-only', 'evidence': ['nethack-c/wasm/build.py']},
            {'name': 'replay_adapter_environment_startup', 'disposition': 'retain runSegment boundary, deterministic inputs, per-instance isolation, capture, persistence; replace Emscripten loader/FS/ENV/callMain/unwind', 'evidence': ['js/wasm-adapter.js', 'js/wasm-replay-support.js', 'js/recording-profile.js']},
            {'name': 'terminfo_capabilities', 'disposition': 'replace libtinfo behavior required by current game; no curses UI rewrite', 'evidence': ['nethack-c/wasm/build_terminfo.py']},
            {'name': 'input_output_transport', 'disposition': 'preserve keyboard byte mapping and input-exhaustion boundary', 'evidence': ['nethack-c/wasm/bridge.c', 'js/wasm-adapter.js']},
            {'name': 'shadow_screen_capture', 'disposition': 'preserve inherited default capture and frame timing separately from transport/terminfo', 'evidence': ['nethack-c/wasm/build.py', 'js/wasm-adapter.js']},
            {'name': 'optional_ghostty_emulation', 'disposition': 'diagnostic path selected by TELEPORT_TERMINAL=ghostty currently executes separate Wasm; remove from final runtime or implement JS equivalent if retained', 'evidence': ['js/terminal-backend.js', 'js/wasm-adapter.js']},
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
            'Terminfo source/archive membership is not a linker-reachable subset; linker map/call graph work remains.',
            'Full libc/formatting/time/filesystem/transitive-helper inventory remains open beyond curated token categories.',
            'Lua inactive branches, scripts loaded through generated data, runtime aliases and alternate flags need dynamic/preprocessed evidence.',
            'No JS library candidate has been validated or selected by this inventory.',
        ],
    }
    runtime_markers = {
        'nethack-c/wasm/build.py': 'link_flags = ',
        'nethack-c/wasm/build_terminfo.py': "'--with-termlib'",
        'nethack-c/wasm/tu-support.c': 'teleport_',
        'nethack-c/wasm/bridge.c': 'teleport_getch',
        'js/ported/wasm-runtime.js': 'createPortedRuntime',
        'js/wasm-adapter.js': 'runWasmSegment',
        'js/wasm-replay-support.js': 'encodeRecorderScreen',
        'js/recording-profile.js': 'recordingProfile',
        'js/terminal-backend.js': 'WebAssembly.compile',
        'nethack-c/wasm/tu-libraries/posixregex.js': "'regcomp'",
        'nethack-c/wasm/tu-libraries/calendar.js': "'mktime'",
    }
    for layer in report['runtime_layers']:
        layer['evidence'] = [evidence(path, runtime_markers.get(path)) for path in layer['evidence']]
    # Presence is not integration or compatibility proof. Observe exact static
    # import strings only; do not assume dynamic strings or aliases are absent.
    js_sources = [p for p in sorted((ROOT / 'js').rglob('*.js'))
                  if '/wasm/' not in relative(p) and '/vendor/' not in relative(p)]
    source_texts = {p: read(p) for p in js_sources}
    candidates = []
    for path in sorted((ROOT / 'js/services').glob('*.js')):
        text = read(path)
        importers = []
        for importer, imported_text in source_texts.items():
            if importer == path:
                continue
            for match in re.finditer(r'''\b(?:from\s*|import\(\s*)['"]([^'"]+)['"]''', strip_comments(imported_text)):
                if match[1].startswith('.') and (importer.parent / match[1]).resolve() == path.resolve():
                    importers.append(location(importer, imported_text, match.start()))
        candidates.append({'path': relative(path), 'physical_lines': len(text.splitlines()),
                           'exports_observed': sorted(set(re.findall(r'\bexport\s+(?:async\s+)?(?:function|class|const|let)\s+(\w+)', strip_comments(text)))),
                           'static_js_import_sites': importers,
                           'status': 'candidate present; inventory does not establish runtime integration, equivalence or completion'})
    report['standalone_service_candidates'] = candidates
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
