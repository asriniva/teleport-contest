#!/usr/bin/env python3
"""Bind unchanged equipment formatter packets and configured diagnostic sites."""
import hashlib
import json
import os
import re
from pathlib import Path

root = Path(__file__).resolve().parents[1]
reference = Path(os.environ['STANDALONE_REFERENCE_ROOT']).resolve()
tree = reference / '.cache/wasm64-build/tree'
library_paths = {name: root / f'nethack-c/wasm/tu-libraries/{name}.js'
                 for name in ['weapon', 'worn', 'wield', 'do_wear']}
libraries = {name: path.read_text() for name, path in library_paths.items()}
weapon_support = root / 'nethack-c/wasm/tu-weapon-support.inc'
common_support = root / 'nethack-c/wasm/tu-support.c'
weapon_source = (tree / 'src/weapon.c').read_text()
worn_source = (tree / 'src/worn.c').read_text()

# Use the exact diagnostic-line rules of write-tu-source-metadata.py, whose
# native transport consumes these same configured source sites.
weapon_calls = list(re.finditer(r'\bSnprintf\s*\(', weapon_source))
weapon_strlen = list(re.finditer(r'\bStrlen\s*\(', weapon_source))
assert len(weapon_calls) == 4 and len(weapon_strlen) == 1
weapon_lines = [weapon_source.count('\n', 0, weapon_source.index(');', call.end()) + 2) + 1
                for call in weapon_calls]
weapon_formats = []
for index, line in enumerate(weapon_lines):
    match = re.search(r'void teleport_weapon_snprintf' + str(index)
                      + r'\((.*?)\)\s*\{nh_snprintf\("([^"]+)",teleport_weapon_snprintf_lines\['
                      + str(index) + r'\]', weapon_support.read_text(), re.S)
    assert match, f'Changed WEAPON formatter {index}'
    types = [re.sub(r'\b\w+$', '', parameter.strip()).strip().replace('size_t', 'unsigned long')
             for parameter in match[1].split(',')]
    weapon_formats.append({'id': index, 'name': 'Snprintf', 'actual': 'nh_snprintf',
                           'fn': match[2], 'line': line, 'types': types})

worn_active = re.sub(r'/\*.*?\*/|//[^\n]*',
                     lambda match: '\n' * match.group().count('\n'), worn_source, flags=re.S)
worn_calls = list(re.finditer(r'\bSnprintf\(buf, sizeof buf, " removes %s and", oldarm\)', worn_active))
assert len(worn_calls) == 1
worn_format = {'name': 'Snprintf', 'actual': 'nh_snprintf', 'fn': 'm_dowear_type',
               'line': worn_active.count('\n', 0, worn_calls[0].end()) + 1,
               'types': ['char *', 'unsigned long', 'const char *', 'const char *']}
assert 'nh_snprintf(TELEPORT_WORN_SNPRINTF_FUNCTION,TELEPORT_WORN_SNPRINTF_LINE,out,size,format,value)' in common_support.read_text()

armor_sites = json.JSONDecoder().raw_decode(libraries['do_wear'].split('var sites=', 1)[1])[0]
assert [row['id'] for row in armor_sites] == list(range(len(armor_sites)))
assert {row['prefix'] for row in armor_sites} == {0, 2}
for row in armor_sites:
    assert row['prefix'] == (2 if row['actual'] == 'nh_snprintf' else 0)
    assert len(row['types']) >= row['prefix']

messages = {
    'weapon': ['pline', 'You', 'Your', 'You_feel', 'pline_mon', 'impossible', 'panic'],
    'worn': ['impossible', 'pline', 'pline_mon', 'You', 'You_hear'],
    'wield': ['pline', 'You', 'Your', 'You_cant'],
}
for owner, names in messages.items():
    for name in names:
        assert re.search(r'\b' + name + r'\s*:', libraries[owner]), (owner, name)

inputs = [Path(__file__).resolve(), *library_paths.values(), weapon_support, common_support,
          root / 'nethack-c/wasm/tu-do_wear-varargs.inc', root / 'scripts/write-tu-source-metadata.py',
          root / 'nethack-c/wasm/compile-defines.json',
          *[root / f'js/ported/{name}.js' for name in ['weapon', 'worn', 'wield', 'do_wear', 'hacklib', 'strutil']]]
assert '#define pline1(cstr) pline("%s", cstr)' in (tree / 'include/hack.h').read_text()
reference_inputs = [tree / 'include/hack.h', *[tree / f'src/{name}.c' for name in ['weapon', 'worn', 'wield', 'do_wear', 'hacklib', 'strutil']]]
sha = lambda path: hashlib.sha256(path.read_bytes()).hexdigest()
data = {
    'weapon': {'snprintf': weapon_formats,
               'strlen': {'fn': 'add_skills_to_menu',
                          'line': weapon_source.count('\n', 0, weapon_strlen[0].start()) + 1}},
    'worn': {'snprintf': worn_format},
    'armorSites': armor_sites,
    'messages': messages,
    'armorPlain': {'name': 'pline1', 'actual': 'pline', 'format': '%s'},
    'sourceSha256': {str(path.relative_to(root)): sha(path) for path in inputs},
    'referenceHeaderSha256': {str(path.relative_to(reference)): sha(path) for path in reference_inputs},
}
(root / 'js/nethack/equipment-format-abi.json').write_text(json.dumps(data, indent=2) + '\n')
print(f'Bound equipment formatting sites: {len(weapon_formats)} WEAPON, 1 WORN, {len(armor_sites)} DO_WEAR.')
