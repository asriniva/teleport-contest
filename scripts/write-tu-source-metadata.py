"""Preserve recorder macro source locations while original callers become JS."""
from pathlib import Path
import re
import ast
import json
import os
import subprocess

root = Path(__file__).resolve().parents[1]
source = root / '.cache/wasm64-build/tree/src/rect.c'
lines = source.read_text().splitlines()
calls = [i for i, line in enumerate(lines, 1) if 'rn2(rect_cnt)' in line]
assert len(calls) == 1, 'Review changed rectangle RNG call sites'
out = root / '.cache/tu-probes/tu-source-locations.h'
out.parent.mkdir(parents=True, exist_ok=True)
out.write_text('/* Generated from the actual prepared C source; do not edit. */\n'
               '#define TELEPORT_RECT_RNG_FILE "rect.c"\n'
               f'#define TELEPORT_RECT_RNG_LINE {calls[0]}\n'
               '#define TELEPORT_RECT_RNG_FUNCTION "rnd_rect"\n')
track = (source.parent / 'track.c').read_text()
match = re.search(r'^#define UTSZ (\d+)$', track, flags=re.M)
assert match, 'Review changed track capacity declaration'
with out.open('a') as stream:
    stream.write(f'#define TELEPORT_TRACK_UTSZ {match.group(1)}\n')
    calendar = (source.parent / 'calendar.c').read_text().splitlines()
    calls = [i for i, line in enumerate(calendar, 1) if 'Snprintf(datestr, sizeof datestr,' in line]
    assert len(calls) == 1, 'Review changed calendar format call sites'
    # Clang expands __LINE__ at the closing line of a multiline invocation.
    closing = next(i for i in range(calls[0] - 1, len(calendar)) if ');' in calendar[i]) + 1
    stream.write(f'#define TELEPORT_CALENDAR_FORMAT_LINE {closing}\n')
    stream.write('#define TELEPORT_CALENDAR_FORMAT_FUNCTION "yyyymmddhhmmss"\n')

    date = (source.parent / 'date.c').read_text().splitlines()
    calls = [i for i, line in enumerate(date, 1) if 'Snprintf(tmpbuf1, sizeof tmpbuf1,' in line]
    assert len(calls) == 1, 'Review changed build date format call sites'
    closing = next(i for i in range(calls[0] - 1, len(date)) if ');' in date[i]) + 1
    stream.write(f'#define TELEPORT_DATE_FORMAT_LINE {closing}\n')

# The JS name table is authoritative; C reserves the complete static JS literal corpus capacity.
mplayer_js = root / 'js/ported/mplayer.js'
if mplayer_js.exists():
    match = re.search(r'^(?:export )?const developers\s*=\s*(\[.*?\])\s*;', mplayer_js.read_text(), flags=re.M | re.S)
    assert match, 'Review changed JS developer-name table'
    names = ast.literal_eval(re.sub(r'/\*.*?\*/|//[^\n]*', '', match.group(1), flags=re.S))
    assert all(isinstance(name, str) for name in names)
    tokens = re.finditer(r"/\*.*?\*/|//[^\n]*|\"(?:\\.|[^\"\\])*\"|'(?:\\.|[^'\\])*'", mplayer_js.read_text(), flags=re.S)
    literals = {ast.literal_eval(token.group()) for token in tokens if token.group()[0] in ['\"', "'"]}
    assert set(names) <= literals
    capacity = sum(len(value.encode('utf-8')) + 1 for value in literals)
    with out.open('a') as stream:
        stream.write(f'#define TELEPORT_MPLAYER_LITERAL_CAPACITY {capacity}\n')

exper = (source.parent / 'exper.c').read_text().splitlines()
assertions = [(i, re.search(r'^\s*assert\((.+)\);', line)) for i, line in enumerate(exper, 1) if re.search(r'^\s*assert\(', line)]
assert len(assertions) == 1 and assertions[0][1], 'Review changed experience assertions'
with out.open('a') as stream:
    stream.write(f'#define TELEPORT_EXPER_ASSERT_LINE {assertions[0][0]}\n')
    stream.write('#define TELEPORT_EXPER_ASSERT_CONDITION ' + json.dumps(assertions[0][1].group(1)) + '\n')

# Static getline strings cannot consume new stack space per replay key.
getline_js = root / 'js/ported/getline.js'
if getline_js.exists():
    tokens = re.finditer(r"/\*.*?\*/|//[^\n]*|\"(?:\\.|[^\"\\])*\"|'(?:\\.|[^'\\])*'", getline_js.read_text(), flags=re.S)
    literals = {ast.literal_eval(token.group()) for token in tokens if token.group()[0] in ['\"', "'"]}
    capacity = sum(len(value.encode('utf-8')) + 1 for value in literals)
    with out.open('a') as stream:
        stream.write(f'#define TELEPORT_GETLINE_LITERAL_CAPACITY {capacity}\n')

# JS owns write.c strings and compositions; C supplies addressable storage only.
write_js = root / 'js/ported/write.js'
if write_js.exists():
    tokens = re.finditer(r"/\*.*?\*/|//[^\n]*|\"(?:\\.|[^\"\\])*\"|'(?:\\.|[^'\\])*'", write_js.read_text(), flags=re.S)
    literals = {ast.literal_eval(token.group()) for token in tokens if token.group()[0] in ['\"', "'"]}
    capacity = sum(len(value.encode('utf-8')) + 1 for value in literals)
    with out.open('a') as stream:
        stream.write(f'#define TELEPORT_WRITE_LITERAL_CAPACITY {capacity}\n')

# Preserve mdlib's native formatting diagnostics, with constants owned by JS.
mdlib = (source.parent / 'mdlib.c').read_text().splitlines()
starts = [i for i, line in enumerate(mdlib) if line.lstrip().startswith('Snprintf(outbuf, bufsz,')]
assert len(starts) == 2, 'Review changed mdlib format call sites'
with out.open('a') as stream:
    for label, start in zip(['VERSION', 'BANNER'], starts):
        closing = next(i for i in range(start, len(mdlib)) if ');' in mdlib[i]) + 1
        stream.write(f'#define TELEPORT_MDLIB_{label}_LINE {closing}\n')
mdlib_js = root / 'js/ported/mdlib.js'
if mdlib_js.exists():
    tokens = re.finditer(r"/\*.*?\*/|//[^\n]*|\"(?:\\.|[^\"\\])*\"|'(?:\\.|[^'\\])*'", mdlib_js.read_text(), flags=re.S)
    literals = {ast.literal_eval(token.group()) for token in tokens if token.group()[0] in ['\"', "'"]}
    capacity = sum(len(value.encode('utf-8')) + 1 for value in literals)
    with out.open('a') as stream:
        stream.write(f'#define TELEPORT_MDLIB_LITERAL_CAPACITY {capacity}\n')

# Quest dialogue messages retain static C-addressable lifetime.
quest_js = root / 'js/ported/quest.js'
if quest_js.exists():
    tokens = re.finditer(r"/\*.*?\*/|//[^\n]*|\"(?:\\.|[^\"\\])*\"|'(?:\\.|[^'\\])*'", quest_js.read_text(), flags=re.S)
    literals = {ast.literal_eval(token.group()) for token in tokens if token.group()[0] in ['\"', "'"]}
    capacity = sum(len(value.encode('utf-8')) + 1 for value in literals)
    with out.open('a') as stream:
        stream.write(f'#define TELEPORT_QUEST_LITERAL_CAPACITY {capacity}\n')

# Minion dialogue and symbolic elemental labels remain JS-owned constants.
minion_js = root / 'js/ported/minion.js'
if minion_js.exists():
    tokens = re.finditer(r"/\*.*?\*/|//[^\n]*|\"(?:\\.|[^\"\\])*\"|'(?:\\.|[^'\\])*'", minion_js.read_text(), flags=re.S)
    literals = {ast.literal_eval(token.group()) for token in tokens if token.group()[0] in ['\"', "'"]}
    capacity = sum(len(value.encode('utf-8')) + 1 for value in literals)
    with out.open('a') as stream:
        stream.write(f'#define TELEPORT_MINION_LITERAL_CAPACITY {capacity}\n')

# Item-action strings remain JS-owned constants with static C addresses.
iactions_js = root / 'js/ported/iactions.js'
if iactions_js.exists():
    tokens = re.finditer(r"/\*.*?\*/|//[^\n]*|\"(?:\\.|[^\"\\])*\"|'(?:\\.|[^'\\])*'", iactions_js.read_text(), flags=re.S)
    literals = {ast.literal_eval(token.group()) for token in tokens if token.group()[0] in ['\"', "'"]}
    capacity = sum(len(value.encode('utf-8')) + 1 for value in literals)
    with out.open('a') as stream:
        # Header plur() adds the static string 's' outside the core TU.
        stream.write(f'#define TELEPORT_IACTIONS_LITERAL_CAPACITY {capacity + 2}\n')

# Preserve the original item-action assertion diagnostics.
iactions = (source.parent / 'iactions.c').read_text().splitlines()
assertions = [(i, re.search(r'^\s*assert\((.+)\);', line)) for i, line in enumerate(iactions, 1) if re.search(r'^\s*assert\(', line)]
assert len(assertions) == 1 and assertions[0][1], 'Review changed item-action assertions'
with out.open('a') as stream:
    stream.write(f'#define TELEPORT_IACTIONS_ASSERT_LINE {assertions[0][0]}\n')
    stream.write('#define TELEPORT_IACTIONS_ASSERT_CONDITION ' + json.dumps(assertions[0][1].group(1)) + '\n')

# Selection geometry keeps the recorder's original native RNG attribution.
selvar = (source.parent / 'selvar.c').read_text().splitlines()
selvar_sites = [i for i, line in enumerate(selvar, 1) if re.search(r'\brn2\(', line)]
assert len(selvar_sites) == 7, 'Review changed selection RNG sites'
with out.open('a') as stream:
    stream.write('#define TELEPORT_SELVAR_RNG_LINES { ' + ', '.join(map(str, selvar_sites)) + ' }\n')
selvar_js = root / 'js/ported/selvar.js'
if selvar_js.exists():
    tokens = re.finditer(r"/\*.*?\*/|//[^\n]*|\"(?:\\.|[^\"\\])*\"|'(?:\\.|[^'\\])*'", selvar_js.read_text(), flags=re.S)
    literals = {ast.literal_eval(token.group()) for token in tokens if token.group()[0] in ['\"', "'"]}
    capacity = sum(len(value.encode('utf-8')) + 1 for value in literals)
    with out.open('a') as stream:
        stream.write(f'#define TELEPORT_SELVAR_LITERAL_CAPACITY {capacity}\n')

# Theft diagnostics preserve the prepared source assertion verbatim.
steal = (source.parent / 'steal.c').read_text().splitlines()
assertions = [(i, re.search(r'^\s*assert\((.+)\);', line)) for i, line in enumerate(steal, 1) if re.search(r'^\s*assert\(', line)]
assert len(assertions) == 1 and assertions[0][1], 'Review changed theft assertions'
with out.open('a') as stream:
    stream.write(f'#define TELEPORT_STEAL_ASSERT_LINE {assertions[0][0]}\n')
    stream.write('#define TELEPORT_STEAL_ASSERT_CONDITION ' + json.dumps(assertions[0][1].group(1)) + '\n')
steal_js = root / 'js/ported/steal.js'
if steal_js.exists():
    tokens = re.finditer(r"/\*.*?\*/|//[^\n]*|\"(?:\\.|[^\"\\])*\"|'(?:\\.|[^'\\])*'", steal_js.read_text(), flags=re.S)
    literals = {ast.literal_eval(token.group()) for token in tokens if token.group()[0] in ['\"', "'"]}
    capacity = sum(len(value.encode('utf-8')) + 1 for value in literals)
    with out.open('a') as stream:
        stream.write(f'#define TELEPORT_STEAL_LITERAL_CAPACITY {capacity}\n')

# Sitting, throne and curse literals retain static native-pointer lifetimes.
sit_js = root / 'js/ported/sit.js'
if sit_js.exists():
    tokens = re.finditer(r"/\*.*?\*/|//[^\n]*|\"(?:\\.|[^\"\\])*\"|'(?:\\.|[^'\\])*'", sit_js.read_text(), flags=re.S)
    literals = {ast.literal_eval(token.group()) for token in tokens if token.group()[0] in ['\"', "'"]}
    capacity = sum(len(value.encode('utf-8')) + 1 for value in literals)
    with out.open('a') as stream:
        stream.write(f'#define TELEPORT_SIT_LITERAL_CAPACITY {capacity}\n')

# Fountain and sink literals retain static native-pointer lifetimes.
fountain_js = root / 'js/ported/fountain.js'
if fountain_js.exists():
    tokens = re.finditer(r"/\*.*?\*/|//[^\n]*|\"(?:\\.|[^\"\\])*\"|'(?:\\.|[^'\\])*'", fountain_js.read_text(), flags=re.S)
    literals = {ast.literal_eval(token.group()) for token in tokens if token.group()[0] in ['\"', "'"]}
    literals.add('%s')  # pline1 macro expands in the runtime adapter.
    capacity = sum(len(value.encode('utf-8')) + 1 for value in literals)
    with out.open('a') as stream:
        stream.write(f'#define TELEPORT_FOUNTAIN_LITERAL_CAPACITY {capacity}\n')

# The object catalogue's stable descriptor strings are authoritative JS data.
objects_data = root / 'js/ported/objects-data.js'
if objects_data.exists():
    tokens = re.finditer(r"/\*.*?\*/|//[^\n]*|\"(?:\\.|[^\"\\])*\"|'(?:\\.|[^'\\])*'", objects_data.read_text(), flags=re.S)
    literals = {ast.literal_eval(token.group()) for token in tokens if token.group()[0] in ['\"', "'"]}
    capacity = sum(len(value.encode('utf-8')) + 1 for value in literals)
    with out.open('a') as stream:
        stream.write(f'#define TELEPORT_OBJECTS_LITERAL_CAPACITY {capacity}\n')

# The monster catalogue's stable gender names are authoritative JS data.
monst_data = root / 'js/ported/monst-data.js'
if monst_data.exists():
    tokens = re.finditer(r"/\*.*?\*/|//[^\n]*|\"(?:\\.|[^\"\\])*\"|'(?:\\.|[^'\\])*'", monst_data.read_text(), flags=re.S)
    literals = {ast.literal_eval(token.group()) for token in tokens if token.group()[0] in ['\"', "'"]}
    capacity = sum(len(value.encode('utf-8')) + 1 for value in literals)
    with out.open('a') as stream:
        stream.write(f'#define TELEPORT_MONST_LITERAL_CAPACITY {capacity}\n')

# Shop diagnostics preserve original conditions and physical source lines.
shknam = (source.parent / 'shknam.c').read_text().splitlines()
assertions = [(i, re.search(r'^\s*assert\((.+)\);', line)) for i, line in enumerate(shknam, 1) if re.search(r'^\s*assert\(', line)]
assert len(assertions) == 2 and all(match for _, match in assertions), 'Review changed shop assertions'
with out.open('a') as stream:
    for index, (line, match) in enumerate(assertions):
        stream.write(f'#define TELEPORT_SHKNAM_ASSERT_LINE_{index} {line}\n')
        stream.write(f'#define TELEPORT_SHKNAM_ASSERT_CONDITION_{index} ' + json.dumps(match.group(1)) + '\n')

shknam_js = root / 'js/ported/shknam.js'
if shknam_js.exists():
    text = shknam_js.read_text()
    lists = re.findall(r'^(?:export )?const (shk\w+)\s*=\s*(\[.*?\])\s*;', text, flags=re.M | re.S)
    assert len(lists) == 11, 'Review changed shopkeeper name lists'
    count = 0
    for name, values in lists:
        values = re.sub(r'/\*.*?\*/|//[^\n]*', '', values, flags=re.S)
        values = ast.literal_eval(re.sub(r'\bnull\b', 'None', values))
        assert values[-1] in [0, None] and all(isinstance(value, str) for value in values[:-1]), name
        count += len(values)
    tokens = re.finditer(r"/\*.*?\*/|//[^\n]*|\"(?:\\.|[^\"\\])*\"|'(?:\\.|[^'\\])*'", text, flags=re.S)
    literals = {ast.literal_eval(token.group()) for token in tokens if token.group()[0] in ['\"', "'"]}
    capacity = sum(len(value.encode('utf-8')) + 1 for value in literals)
    with out.open('a') as stream:
        stream.write('#define TELEPORT_SHKNAM_ROW_COUNT (MAXRTYPE - SHOPBASE + 2)\n')
        stream.write(f'#define TELEPORT_SHKNAM_NAME_POINTER_COUNT {count}\n')
        stream.write(f'#define TELEPORT_SHKNAM_LITERAL_CAPACITY {capacity}\n')

# Original rumor assertions have distinct native assert/nhassert behavior.
rumors = (source.parent / 'rumors.c').read_text().splitlines()
for kind, macro in [('assert', 'ASSERT'), ('nhassert', 'NHASSERT')]:
    assertions = [(i, re.search(r'^\s*' + kind + r'\((.+)\);', line)) for i, line in enumerate(rumors, 1) if re.search(r'^\s*' + kind + r'\(', line)]
    assert len(assertions) == 1 and assertions[0][1], 'Review changed rumor ' + kind
    with out.open('a') as stream:
        stream.write(f'#define TELEPORT_RUMORS_{macro}_LINE {assertions[0][0]}\n')
        stream.write(f'#define TELEPORT_RUMORS_{macro}_CONDITION ' + json.dumps(assertions[0][1].group(1)) + '\n')
rumors_js = root / 'js/ported/rumors.js'
if rumors_js.exists():
    tokens = re.finditer(r"/\*.*?\*/|//[^\n]*|\"(?:\\.|[^\"\\])*\"|'(?:\\.|[^'\\])*'", rumors_js.read_text(), flags=re.S)
    literals = {ast.literal_eval(token.group()) for token in tokens if token.group()[0] in ['\"', "'"]}
    capacity = sum(len(value.encode('utf-8')) + 1 for value in literals)
    with out.open('a') as stream:
        stream.write(f'#define TELEPORT_RUMORS_LITERAL_CAPACITY {capacity}\n')

# The instrument TU keeps authoritative literal data in readable JavaScript.
music_js = root / 'js/ported/music.js'
if music_js.exists():
    tokens = re.finditer(r"/\*.*?\*/|//[^\n]*|\"(?:\\.|[^\"\\])*\"|'(?:\\.|[^'\\])*'", music_js.read_text(), flags=re.S)
    literals = {ast.literal_eval(token.group()) for token in tokens if token.group()[0] in ['\"', "'"]}
    capacity = sum(len(value.encode('utf-8')) + 1 for value in literals)
    with out.open('a') as stream:
        stream.write(f'#define TELEPORT_MUSIC_LITERAL_CAPACITY {capacity}\n')

# Preserve the macro's actual closing line and caller for each version format.
# Match strings/comments before parentheses, so format text cannot end a call.
version_source = source.parent / 'version.c'
version_text = version_source.read_text()
version_functions = list(re.finditer(r'^(\w+)\([^;{}]*\)\s*\{', version_text, re.M))
version_sites = []
for match in re.finditer(r'\bSnprintf\s*\(', version_text):
    depth = 1
    end = None
    for token in re.finditer(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|[()]',
                             version_text[match.end():], re.S):
        if token.group() == '(':
            depth += 1
        elif token.group() == ')':
            depth -= 1
            if depth == 0:
                end = match.end() + token.start()
                break
    assert end is not None, 'Unclosed version formatting macro'
    function = next(item.group(1) for item in reversed(version_functions) if item.start() < match.start())
    version_sites.append((version_text.count('\n', 0, end) + 1, function))
assert len(version_sites) == 13, 'Review changed version formatting sites'

# Counts describe only configured storage sizes; authoritative rows stay JS.
sdk = Path(os.environ.get('EMSDK', root / '.cache/emsdk'))
version_defines = ['-D' + name for name in json.loads((root / 'nethack-c/wasm/compile-defines.json').read_text())]
version_cpp = subprocess.check_output([str(sdk / 'upstream/emscripten/emcc'), '-E', '-P',
    '-sMEMORY64=1', *version_defines, '-I' + str(source.parent.parent / 'include'), str(version_source)], text=True)
version_counts = {}
for name, expected in [('critical_sizes', 80), ('rt_opts', 3)]:
    table = re.search(r'\b' + name + r'\[\]\s*=\s*\{(.*?)\n\};', version_cpp, re.S)
    assert table, 'Review changed version table ' + name
    count = len(re.findall(r'^\s*\{', table.group(1), re.M))
    assert count == expected, ('Review changed configured version table', name, count)
    version_counts[name] = count
with out.open('a') as stream:
    stream.write('#define TELEPORT_VERSION_SNPRINTF_LINES {' + ', '.join(str(line) for line, _ in version_sites) + '}\n')
    stream.write('#define TELEPORT_VERSION_SNPRINTF_FUNCTIONS {' + ', '.join(json.dumps(fn) for _, fn in version_sites) + '}\n')
    stream.write(f'#define TELEPORT_VERSION_CRITICAL_COUNT {version_counts["critical_sizes"]}\n')
    stream.write(f'#define TELEPORT_VERSION_RTOPTS_COUNT {version_counts["rt_opts"]}\n')
version_js = root / 'js/ported/version.js'
if version_js.exists():
    tokens = re.finditer(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'', version_js.read_text(), re.S)
    literals = {ast.literal_eval(token.group()) for token in tokens if token.group()[0] in ['"', "'"]}
    capacity = sum(len(value.encode('utf-8')) + 1 for value in literals)
    with out.open('a') as stream:
        stream.write(f'#define TELEPORT_VERSION_LITERAL_CAPACITY {capacity}\n')

coloratt_source = source.parent / 'coloratt.c'
coloratt_text = coloratt_source.read_text()
coloratt_functions = list(re.finditer(r'^(\w+)\([^;{}]*\)\s*\{', coloratt_text, re.M))
coloratt_sites = []
for match in re.finditer(r'\bSnprintf\s*\(', coloratt_text):
    depth, end = 1, None
    for token in re.finditer(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|[()]',
                             coloratt_text[match.end():], re.S):
        if token.group() == '(':
            depth += 1
        elif token.group() == ')':
            depth -= 1
            if depth == 0:
                end = match.end() + token.start()
                break
    assert end is not None, 'Unclosed color formatting macro'
    function = next(item.group(1) for item in reversed(coloratt_functions) if item.start() < match.start())
    coloratt_sites.append((coloratt_text.count('\n', 0, end) + 1, function))
assert len(coloratt_sites) == 3, 'Review changed color formatting sites'
coloratt_asserts = [(i, re.search(r'^\s*assert\((.+)\);', line))
    for i, line in enumerate(coloratt_text.splitlines(), 1) if re.search(r'^\s*assert\(', line)]
assert len(coloratt_asserts) == 1 and coloratt_asserts[0][1], 'Review changed color assertion'
coloratt_cpp = subprocess.check_output([str(sdk / 'upstream/emscripten/emcc'), '-E', '-P',
    '-sMEMORY64=1', *version_defines, '-I' + str(source.parent.parent / 'include'), str(coloratt_source)], text=True)
coloratt_counts = {}
for name, macro, expected in [('colortable', 'TABLE', 155), ('colornames', 'COLORNAME', 27),
        ('attrnames', 'ATTRNAME', 11), ('color_256_definitions', 'PALETTE', 240)]:
    table = re.search(r'\b' + name + r'\[\]\s*=\s*\{(.*?)\n\};', coloratt_cpp, re.S)
    assert table, 'Review changed color table ' + name
    # These four flat struct arrays can contain several rows on one line.
    body = re.sub(r'"(?:\\.|[^"\\])*"', '""', table.group(1))
    count = body.count('{')
    assert count == expected, ('Review changed configured color table', name, count)
    coloratt_counts[macro] = count
with out.open('a') as stream:
    stream.write('#define TELEPORT_COLORATT_SNPRINTF_LINES {' + ', '.join(str(line) for line, _ in coloratt_sites) + '}\n')
    stream.write('#define TELEPORT_COLORATT_SNPRINTF_FUNCTIONS {' + ', '.join(json.dumps(fn) for _, fn in coloratt_sites) + '}\n')
    stream.write(f'#define TELEPORT_COLORATT_ASSERT_LINE {coloratt_asserts[0][0]}\n')
    stream.write('#define TELEPORT_COLORATT_ASSERT_CONDITION ' + json.dumps(coloratt_asserts[0][1].group(1)) + '\n')
    for macro, count in coloratt_counts.items():
        stream.write(f'#define TELEPORT_COLORATT_{macro}_COUNT {count}\n')
coloratt_js = root / 'js/ported/coloratt.js'
if coloratt_js.exists():
    tokens = re.finditer(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'', coloratt_js.read_text(), re.S)
    literals = {ast.literal_eval(token.group()) for token in tokens if token.group()[0] in ['"', "'"]}
    capacity = sum(len(value.encode('utf-8')) + 1 for value in literals)
    with out.open('a') as stream:
        stream.write(f'#define TELEPORT_COLORATT_LITERAL_CAPACITY {capacity}\n')

# Preserve the original priest assertion and addressable JS string lifetimes.
priest_text = (source.parent / 'priest.c').read_text()
priest_asserts = [(i, re.search(r'^\s*assert\((.+)\);', line))
    for i, line in enumerate(priest_text.splitlines(), 1) if re.search(r'^\s*assert\(', line)]
assert len(priest_asserts) == 1 and priest_asserts[0][1], 'Review changed priest assertion'
with out.open('a') as stream:
    stream.write(f'#define TELEPORT_PRIEST_ASSERT_LINE {priest_asserts[0][0]}\n')
    stream.write('#define TELEPORT_PRIEST_ASSERT_CONDITION ' + json.dumps(priest_asserts[0][1].group(1)) + '\n')
priest_js = root / 'js/ported/priest.js'
if priest_js.exists():
    tokens = re.finditer(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'', priest_js.read_text(), re.S)
    literals = {ast.literal_eval(token.group()) for token in tokens if token.group()[0] in ['"', "'"]}
    capacity = sum(len(value.encode('utf-8')) + 1 for value in literals)
    with out.open('a') as stream:
        stream.write(f'#define TELEPORT_PRIEST_LITERAL_CAPACITY {capacity}\n')

light_text = (source.parent / 'light.c').read_text()
light_functions = list(re.finditer(r'^(\w+)\([^;{}]*\)\s*\{', light_text, re.M))
light_asserts = list(re.finditer(r'^\s*assert\((.+)\);', light_text, re.M))
assert len(light_asserts) == 3, 'Review changed light assertions'
light_assert_lines = [light_text.count('\n', 0, match.start()) + 1 + match.group().count('\n')
    for match in light_asserts]
light_assert_functions = [next(item.group(1) for item in reversed(light_functions)
    if item.start() < match.start()) for match in light_asserts]
with out.open('a') as stream:
    stream.write('#define TELEPORT_LIGHT_ASSERT_LINES {' + ', '.join(map(str, light_assert_lines)) + '}\n')
    stream.write('#define TELEPORT_LIGHT_ASSERT_CONDITIONS {' + ', '.join(json.dumps(match.group(1)) for match in light_asserts) + '}\n')
    stream.write('#define TELEPORT_LIGHT_ASSERT_FUNCTIONS {' + ', '.join(map(json.dumps, light_assert_functions)) + '}\n')
light_js = root / 'js/ported/light.js'
if light_js.exists():
    tokens = re.finditer(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'', light_js.read_text(), re.S)
    literals = {ast.literal_eval(token.group()) for token in tokens if token.group()[0] in ['"', "'"]}
    capacity = sum(len(value.encode('utf-8')) + 1 for value in literals)
    with out.open('a') as stream:
        stream.write(f'#define TELEPORT_LIGHT_LITERAL_CAPACITY {capacity}\n')

lock_text = (source.parent / 'lock.c').read_text()
assert not re.search(r'\b(?:assert|Snprintf)\s*\(', lock_text), 'Review changed lock diagnostics'
lock_js = root / 'js/ported/lock.js'
if lock_js.exists():
    tokens = re.finditer(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'', lock_js.read_text(), re.S)
    literals = {ast.literal_eval(token.group()) for token in tokens if token.group()[0] in ['"', "'"]}
    capacity = sum(len(value.encode('utf-8')) + 1 for value in literals)
    with out.open('a') as stream:
        stream.write(f'#define TELEPORT_LOCK_LITERAL_CAPACITY {capacity}\n')

steed_text = (source.parent / 'steed.c').read_text()
assert not re.search(r'\b(?:assert|Snprintf)\s*\(', steed_text), 'Review changed steed diagnostics'
steed_js = root / 'js/ported/steed.js'
if steed_js.exists():
    tokens = re.finditer(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'', steed_js.read_text(), re.S)
    literals = {ast.literal_eval(token.group()) for token in tokens if token.group()[0] in ['"', "'"]}
    capacity = sum(len(value.encode('utf-8')) + 1 for value in literals)
    with out.open('a') as stream:
        stream.write(f'#define TELEPORT_STEED_LITERAL_CAPACITY {capacity}\n')

wizard_text = (source.parent / 'wizard.c').read_text()
assert not re.search(r'\b(?:assert|Snprintf)\s*\(', wizard_text), 'Review changed wizard diagnostics'
wizard_js = root / 'js/ported/wizard.js'
if wizard_js.exists():
    tokens = re.finditer(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'', wizard_js.read_text(), re.S)
    literals = {ast.literal_eval(token.group()) for token in tokens if token.group()[0] in ['"', "'"]}
    capacity = sum(len(value.encode('utf-8')) + 1 for value in literals)
    with out.open('a') as stream:
        stream.write(f'#define TELEPORT_WIZARD_LITERAL_CAPACITY {capacity}\n')

worm_text = (source.parent / 'worm.c').read_text()
assert not re.search(r'\b(?:assert|Snprintf)\s*\(', worm_text), 'Review changed worm diagnostics'
worm_js = root / 'js/ported/worm.js'
if worm_js.exists():
    tokens = re.finditer(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'', worm_js.read_text(), re.S)
    literals = {ast.literal_eval(token.group()) for token in tokens if token.group()[0] in ['"', "'"]}
    capacity = sum(len(value.encode('utf-8')) + 1 for value in literals)
    with out.open('a') as stream:
        stream.write(f'#define TELEPORT_WORM_LITERAL_CAPACITY {capacity}\n')

o_init_text = (source.parent / 'o_init.c').read_text()
assert not re.search(r'\bSnprintf\s*\(', o_init_text), 'Review changed o_init formatting diagnostics'
o_init_asserts = [(n, line.strip()) for n, line in enumerate(o_init_text.splitlines(), 1) if re.search(r'\bassert\s*\(', line)]
assert o_init_asserts == [(752, 'assert(p != NULL); /* pacify static analyzer */')], o_init_asserts
o_init_strlen = [(n, line.strip()) for n, line in enumerate(o_init_text.splitlines(), 1) if re.search(r'\bStrlen\s*\(', line)]
assert o_init_strlen == [(397, 'len = Strlen(objects[i].oc_uname) + 1;')], o_init_strlen
with out.open('a') as stream:
    stream.write('#define TELEPORT_O_INIT_ASSERT_LINE 752\n')
    stream.write('#define TELEPORT_O_INIT_ASSERT_CONDITION "p != NULL"\n')
    stream.write('#define TELEPORT_O_INIT_ASSERT_FUNCTION "disco_output_sorted"\n')
    stream.write('#define TELEPORT_O_INIT_STRLEN_LINE 397\n')
    stream.write('#define TELEPORT_O_INIT_STRLEN_FUNCTION "savenames"\n')
o_init_js = root / 'js/ported/o_init.js'
if o_init_js.exists():
    tokens = re.finditer(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'', o_init_js.read_text(), re.S)
    literals = {ast.literal_eval(token.group()) for token in tokens if token.group()[0] in ['"', "'"]}
    capacity = sum(len(value.encode('utf-8')) + 1 for value in literals)
    with out.open('a') as stream:
        stream.write(f'#define TELEPORT_O_INIT_LITERAL_CAPACITY {capacity}\n')

ball_text = (source.parent / 'ball.c').read_text()
assert not re.search(r'\b(?:assert|Snprintf)\s*\(', ball_text), 'Review changed ball diagnostics'
ball_js = root / 'js/ported/ball.js'
if ball_js.exists():
    tokens = re.finditer(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'', ball_js.read_text(), re.S)
    literals = {ast.literal_eval(token.group()) for token in tokens if token.group()[0] in ['"', "'"]}
    capacity = sum(len(value.encode('utf-8')) + 1 for value in literals)
    with out.open('a') as stream:
        stream.write(f'#define TELEPORT_BALL_LITERAL_CAPACITY {capacity}\n')


mcastu_text = (source.parent / 'mcastu.c').read_text()
assert not re.search(r'\b(?:assert|Snprintf)\s*\(', mcastu_text), 'Review changed mcastu diagnostics'
mcastu_js = root / 'js/ported/mcastu.js'
if mcastu_js.exists():
    tokens = re.finditer(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'', mcastu_js.read_text(), re.S)
    literals = {ast.literal_eval(token.group()) for token in tokens if token.group()[0] in ['"', "'"]}
    capacity = sum(len(value.encode('utf-8')) + 1 for value in literals)
    with out.open('a') as stream:
        stream.write(f'#define TELEPORT_MCASTU_LITERAL_CAPACITY {capacity}\n')


dbridge_text = (source.parent / 'dbridge.c').read_text()
assert re.findall(r'static\s+char\s+wholebuf\[(\d+)\];', dbridge_text) == ['80'], 'Review changed dbridge static phrase backing'
assert not re.search(r'\b(?:assert|Snprintf)\s*\(', dbridge_text), 'Review changed dbridge diagnostics'
dbridge_js = root / 'js/ported/dbridge.js'
if dbridge_js.exists():
    tokens = re.finditer(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'', dbridge_js.read_text(), re.S)
    literals = {ast.literal_eval(token.group()) for token in tokens if token.group()[0] in ['"', "'"]}
    capacity = sum(len(value.encode('utf-8')) + 1 for value in literals)
    with out.open('a') as stream:
        stream.write(f'#define TELEPORT_DBRIDGE_LITERAL_CAPACITY {capacity}\n')


mondata_text = (source.parent / 'mondata.c').read_text()
assert not re.search(r'\b(?:assert|Snprintf)\s*\(', mondata_text), 'Review changed mondata diagnostics'
mondata_js = root / 'js/ported/mondata.js'
if mondata_js.exists():
    tokens = re.finditer(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'', mondata_js.read_text(), re.S)
    literals = {ast.literal_eval(token.group()) for token in tokens if token.group()[0] in ['"', "'"]}
    capacity = sum(len(value.encode('utf-8')) + 1 for value in literals)
    with out.open('a') as stream:
        stream.write(f'#define TELEPORT_MONDATA_LITERAL_CAPACITY {capacity}\n')


hacklib_text = (source.parent / 'hacklib.c').read_text()
assert re.search(r'struct\s+nh_qsort_index\s*\{\s*size_t\s+idx;\s*\};', hacklib_text), 'Review inherited qsort index fields'
assert re.findall(r'^#define VISCTRL_NBUF (\d+)$', hacklib_text, re.M) == ['5'], 'Review visctrl dimensions'
assert re.findall(r'^#define TABSIZ (0x[0-9A-Fa-f]+)', hacklib_text, re.M) == ['0x20'], 'Review signed nibble table dimensions'
assert re.findall(r'^#define MAX_D (\d+)$', hacklib_text, re.M) == ['5'], 'Review datamodel dimensions'
assert len(re.findall(r'static\s+char\s+buf\[BUFSZ\];', hacklib_text)) == 2, 'Review hacklib suffix buffers'
assert re.findall(r'static\s+char\s+visctrl_bufs\[VISCTRL_NBUF\]\[(\d+)\];', hacklib_text) == ['5'], 'Review hacklib visctrl backing'
assert re.findall(r'static\s+char\s+buf\[(\d+)\];', hacklib_text) == ['13'], 'Review hacklib sitoa backing'
hacklib_js = root / 'js/ported/hacklib.js'
if hacklib_js.exists():
    tokens = re.finditer(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'', hacklib_js.read_text(), re.S)
    literals = {ast.literal_eval(token.group()) for token in tokens if token.group()[0] in ['"', "'"]}
    capacity = sum(len(value.encode('utf-8')) + 1 for value in literals)
    with out.open('a') as stream:
        stream.write(f'#define TELEPORT_HACKLIB_LITERAL_CAPACITY {capacity}\n')
