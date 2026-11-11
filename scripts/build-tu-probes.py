"""Build Emscripten C/C→JS probes and native differential oracles."""
import argparse
import ast
import json
import os
from pathlib import Path
import subprocess
import sys

from native_tu_oracles import build_oracle
from importlib import util as importlib_util
addon_spec=importlib_util.spec_from_file_location("native_addon_builder", Path(__file__).with_name("build-native-addon.py"))
addon_builder=importlib_util.module_from_spec(addon_spec)
addon_spec.loader.exec_module(addon_builder)

root = Path(__file__).resolve().parents[1]
sdk = Path(os.environ.get('EMSDK', root / '.cache/emsdk'))
work = root / '.cache/tu-probes'
work.mkdir(parents=True, exist_ok=True)
# Check provenance inputs before compiling; metadata generation must not discover
# a misspelled adapter/header path after a completed game link.
for port in json.loads((root / 'nethack-c/wasm/tu-ports.json').read_text()):
    for path in [port['javascript'], port['library'], *port.get('data', []), *port.get('adapterSources', []), *[storage['source'] for storage in port.get('nativeStorageSources', [])]]:
        assert (root / path).is_file(), f"Missing {port['name']} source/provenance input: {path}"
include = root / '.cache/wasm64-build/tree/include'
assert include.exists(), 'Build the Wasm preparation tree first'
subprocess.run([sys.executable, '-B', str(root / 'scripts/write-objects-data.py'), '--check'], check=True)
subprocess.run([sys.executable, '-B', str(root / 'scripts/write-monst-data.py'), '--check'], check=True)
subprocess.run([sys.executable, '-B', str(root / 'scripts/write-tu-source-metadata.py')], check=True)
if (root / 'js/ported/mondata.js').exists():
    node_command = ast.literal_eval(subprocess.check_output(
        [str(sdk / 'upstream/emscripten/em-config'), 'NODE_JS'], text=True))
    assert isinstance(node_command, list) and all(isinstance(part, str) for part in node_command)
    subprocess.run([*node_command, str(root / 'scripts/check-mondata-data.mjs')], check=True)
    for firstpass_name in ['hack','mon','trap','termcap','wintty','options','botl','zap', 'nhlua', 'spell', 'polyself', 'wizcmds', 'restore', 'nhlobj', 'do_name', 'vision', 'dokick', 'dig', 'monmove', 'do', 'timeout', 'potion', 'mhitu', 'artifact', 'decl', 'do_wear', 'insight', 'eat', 'objnam']:
        if any(port['name'] == firstpass_name for port in json.loads((root / 'nethack-c/wasm/tu-ports.json').read_text())):
            subprocess.run([*node_command, str(root / ('scripts/check-' + firstpass_name + '-data.mjs'))], check=True)
    if any(port['name']=='makemon' for port in json.loads((root/'nethack-c/wasm/tu-ports.json').read_text())):
        subprocess.run([sys.executable,'-B',str(root/'nethack-c/wasm/tu-fragments/makemon-metadata.py')],check=True)
    for owned_name in ['windows','cfgfiles']:
        if any(port['name'] == owned_name for port in json.loads((root / 'nethack-c/wasm/tu-ports.json').read_text())):
            subprocess.run([*node_command, str(root / ('nethack-c/wasm/tu-fragments/' + owned_name + '-source-check.mjs'))], check=True)
    if any(port['name'] == 'mkmaze' for port in json.loads((root / 'nethack-c/wasm/tu-ports.json').read_text())):
        subprocess.run([sys.executable, '-B', str(root / 'scripts/check-mkmaze-source.py')], check=True)
    if any(port['name'] == 'detect' for port in json.loads((root / 'nethack-c/wasm/tu-ports.json').read_text())):
        subprocess.run([sys.executable, '-B', str(root / 'nethack-c/wasm/tu-fragments/detect-check-source.py')], check=True)
        subprocess.run([*node_command, str(root / 'nethack-c/wasm/tu-fragments/detect-check-members.mjs')], check=True)
    if any(port['name'] == 'teleport' for port in json.loads((root / 'nethack-c/wasm/tu-ports.json').read_text())):
        subprocess.run([sys.executable, '-B', str(root / 'nethack-c/wasm/tu-fragments/teleport-source-check.py')], check=True)
    if any(port['name'] == 'mklev' for port in json.loads((root / 'nethack-c/wasm/tu-ports.json').read_text())):
        subprocess.run([sys.executable, '-B', str(root / 'scripts/check-mklev-source.py')], check=True)
    if (root / 'js/ported/hacklib.js').exists():
        subprocess.run([*node_command, str(root / 'scripts/check-hacklib-data.mjs')], check=True)
    if (root / 'nethack-c/wasm/tu-fragments/bones-source-check.mjs').exists():
        subprocess.run([*node_command, str(root / 'nethack-c/wasm/tu-fragments/bones-source-check.mjs')], check=True)
    if (root / 'nethack-c/wasm/tu-fragments/explode-metadata.py').exists():
        subprocess.run([sys.executable, '-B', str(root / 'nethack-c/wasm/tu-fragments/explode-metadata.py')], check=True)
    if (root / 'nethack-c/wasm/tu-fragments/save-source-check.mjs').exists():
        subprocess.run([*node_command, str(root / 'nethack-c/wasm/tu-fragments/save-source-check.mjs')], check=True)
    if (root / 'nethack-c/wasm/tu-fragments/topten-metadata.py').exists():
        subprocess.run([sys.executable, '-B', str(root / 'nethack-c/wasm/tu-fragments/topten-metadata.py')], check=True)
    if (root / 'nethack-c/wasm/tu-fragments/dogmove-source-check.mjs').exists():
        subprocess.run([*node_command, str(root / 'nethack-c/wasm/tu-fragments/dogmove-source-check.mjs')], check=True)
    if (root / 'nethack-c/wasm/tu-fragments/glyphs-source-check.mjs').exists():
        subprocess.run([*node_command, str(root / 'nethack-c/wasm/tu-fragments/glyphs-source-check.mjs')], check=True)
    if (root / 'scripts/check-engrave-data.mjs').exists():
        subprocess.run([*node_command, str(root / 'scripts/check-engrave-data.mjs')], check=True)
    if (root / 'scripts/check-role-data.mjs').exists():
        subprocess.run([*node_command, str(root / 'scripts/check-role-data.mjs')], check=True)
    if (root / 'scripts/check-mthrowu-data.mjs').exists():
        subprocess.run([*node_command, str(root / 'scripts/check-mthrowu-data.mjs')], check=True)
    if (root / 'scripts/check-mhitm-data.mjs').exists():
        subprocess.run([*node_command, str(root / 'scripts/check-mhitm-data.mjs')], check=True)
    if (root / 'nethack-c/wasm/tu-fragments/getpos-metadata.py').exists():
        subprocess.run([sys.executable, '-B', str(root / 'nethack-c/wasm/tu-fragments/getpos-metadata.py')], check=True)
    if (root / 'nethack-c/wasm/tu-fragments/allmain-source-check.mjs').exists():
        subprocess.run([*node_command, str(root / 'nethack-c/wasm/tu-fragments/allmain-source-check.mjs')], check=True)
    if (root / 'scripts/check-sounds-data.mjs').exists():
        subprocess.run([*node_command, str(root / 'scripts/check-sounds-data.mjs')], check=True)
    if (root / 'nethack-c/wasm/tu-fragments/vault-metadata.py').exists():
        subprocess.run([sys.executable, '-B', str(root / 'nethack-c/wasm/tu-fragments/vault-metadata.py')], check=True)
    if (root / 'nethack-c/wasm/tu-fragments/u_init-source-check.mjs').exists():
        subprocess.run([*node_command, str(root / 'nethack-c/wasm/tu-fragments/u_init-source-check.mjs')], check=True)
    if (root / 'scripts/check-weapon-data.mjs').exists():
        subprocess.run([*node_command, str(root / 'scripts/check-weapon-data.mjs')], check=True)
    if (root / 'scripts/check-region-data.mjs').exists():
        subprocess.run([*node_command, str(root / 'scripts/check-region-data.mjs')], check=True)
    if (root / 'scripts/check-dog-data.mjs').exists():
        subprocess.run([*node_command, str(root / 'scripts/check-dog-data.mjs')], check=True)
    if (root / 'nethack-c/wasm/tu-fragments/sfbase-source-check.mjs').exists():
        subprocess.run([*node_command, str(root / 'nethack-c/wasm/tu-fragments/sfbase-source-check.mjs')], check=True)
    if (root / 'nethack-c/wasm/tu-fragments/attrib-metadata.py').exists():
        subprocess.run([sys.executable, '-B', str(root / 'nethack-c/wasm/tu-fragments/attrib-metadata.py')], check=True)
    if (root / 'nethack-c/wasm/tu-fragments/pline-source-check.mjs').exists():
        subprocess.run([*node_command, str(root / 'nethack-c/wasm/tu-fragments/pline-source-check.mjs')], check=True)
    if (root / 'scripts/check-questpgr-data.mjs').exists():
        subprocess.run([*node_command, str(root / 'scripts/check-questpgr-data.mjs')], check=True)
    if (root / 'scripts/check-earlyarg-data.mjs').exists():
        subprocess.run([*node_command, str(root / 'scripts/check-earlyarg-data.mjs')], check=True)
    if (root / 'scripts/check-mkroom-data.mjs').exists():
        subprocess.run([*node_command, str(root / 'scripts/check-mkroom-data.mjs')], check=True)
    if (root / 'js/ported/wield.js').exists():
        subprocess.run([*node_command, str(root / 'scripts/check-wield-data.mjs')], check=True)
    if (root / 'js/ported/worn.js').exists():
        subprocess.run([*node_command, str(root / 'scripts/check-worn-data.mjs')], check=True)

if any(port['name']=='end' for port in json.loads((root/'nethack-c/wasm/tu-ports.json').read_text())):
    subprocess.run([sys.executable,'-B',str(root/'nethack-c/wasm/tu-fragments/end-metadata.py')],check=True)

# PRAY/DOTHROW/PAGER/MUSE/DUNGEON checks run on the ordinary normal-build probe route.
owned_new_names={port['name'] for port in json.loads((root/'nethack-c/wasm/tu-ports.json').read_text())}
if owned_new_names & {'pray','dothrow','pager','muse','dungeon'}:
    owned_node_command=ast.literal_eval(subprocess.check_output([str(sdk/'upstream/emscripten/em-config'),'NODE_JS'],text=True))
    assert isinstance(owned_node_command,list) and all(isinstance(x,str)for x in owned_node_command)
if 'pray' in owned_new_names:
    subprocess.run([sys.executable,'-B',str(root/'nethack-c/wasm/tu-fragments/pray-check-source.py')],check=True)
    subprocess.run([*owned_node_command,str(root/'nethack-c/wasm/tu-fragments/pray-check-members.mjs')],check=True)
if 'dothrow' in owned_new_names:
    subprocess.run([sys.executable,'-B',str(root/'scripts/check-dothrow-source.py')],check=True)
if 'muse' in owned_new_names:
    subprocess.run([sys.executable,'-B',str(root/'nethack-c/wasm/tu-fragments/muse-check-source.py')],check=True)
    subprocess.run([*owned_node_command,str(root/'nethack-c/wasm/tu-fragments/muse-check-members.mjs')],check=True)
if 'dungeon' in owned_new_names:
    subprocess.run([sys.executable,'-B',str(root/'scripts/check-dungeon-source.py')],check=True)
if 'pager' in owned_new_names:
    subprocess.run([sys.executable,'-B',str(root/'nethack-c/wasm/tu-fragments/pager-source-check.py')],check=True)

for owned_name in ['read','apply']:
    if any(port['name']==owned_name for port in json.loads((root/'nethack-c/wasm/tu-ports.json').read_text())):
        subprocess.run([sys.executable,'-B',str(root/('nethack-c/wasm/tu-fragments/'+owned_name+'-metadata.py'))],check=True)

if any(port['name']=='mkobj' for port in json.loads((root/'nethack-c/wasm/tu-ports.json').read_text())):
    subprocess.run([sys.executable,'-B',str(root/'nethack-c/wasm/tu-fragments/mkobj-check-source.py')],check=True)
    subprocess.run([*node_command,str(root/'nethack-c/wasm/tu-fragments/mkobj-check-members.mjs')],check=True)
    subprocess.run([*node_command,str(root/'scripts/check-mkobj-dispatch.mjs')],check=True)


# New fifteen owned source checks: no generic source/data check is skipped.
tu137_names={p['name']for p in json.loads((root/'nethack-c/wasm/tu-ports.json').read_text())}
for owned_name,owned_guard in [
 ('uhitm','nethack-c/wasm/tu-fragments/uhitm-metadata.py'),
 ('pickup','scripts/check-pickup-source.py'),
 ('shk','nethack-c/wasm/tu-fragments/shk-source-check.py'),
 ('sp_lev','nethack-c/wasm/tu-fragments/sp_lev-check.py'),
 ('topl','nethack-c/wasm/tu-fragments/topl-metadata.py'),
 ('unixunix','scripts/check-unixunix-source.py'),
 ('unixmain','nethack-c/wasm/tu-fragments/unixmain-source-check.py')]:
    if owned_name in tu137_names:
        subprocess.run([sys.executable,'-B',str(root/owned_guard)],check=True,cwd=root)
if 'shk'in tu137_names:
    subprocess.run([*node_command,str(root/'nethack-c/wasm/tu-fragments/shk-check-metadata.mjs')],check=True,cwd=root)
if 'unixmain'in tu137_names:
    subprocess.run([*node_command,str(root/'nethack-c/wasm/tu-fragments/unixmain-check-metadata.mjs')],check=True,cwd=root,
                   env={**os.environ,'UNIXMAIN_WRITE_GUARD':'0'})

# FILES/DISPLAY/INVENT: owned source checks on the normal build route.
for owned_name,owned_guard in [('files','nethack-c/wasm/tu-fragments/files-source-check.py'),('invent','nethack-c/wasm/tu-fragments/invent-source-check.py'),('display','scripts/check-display-source.py'),('cmd','nethack-c/wasm/tu-fragments/cmd-check-source.py')]:
    if any(port['name']==owned_name for port in json.loads((root/'nethack-c/wasm/tu-ports.json').read_text())):
        subprocess.run([sys.executable,'-B',str(root/owned_guard),*(['--current-profile']if owned_name=='display'else[])],check=True)
        if owned_name=='cmd':
            owned_node=ast.literal_eval(subprocess.check_output([str(sdk/'upstream/emscripten/em-config'),'NODE_JS'],text=True))
            subprocess.run([*owned_node,str(root/'nethack-c/wasm/tu-fragments/cmd-check-members.mjs')],check=True)

defines = ['-D' + name for name in json.loads((root / 'nethack-c/wasm/compile-defines.json').read_text())]
base = [sdk / 'upstream/emscripten/emcc', '-O2', '-sMEMORY64=1', '-sMODULARIZE=1', *defines,
        '-DTELEPORT_ISOLATED_PROBE',
        '-sENVIRONMENT=node,web', '-sALLOW_MEMORY_GROWTH=1', '--no-entry',
        '-sEXPORTED_RUNTIME_METHODS=HEAPU8', '-I' + str(include), '-I' + str(work)]
probes = {
    'files': ([], ['call', 'reset', 'clear', 'option', 'buffer', 'env', 'pointer', 'open', 'record', 'trace', 'stack', 'uid', 'snapshot', 'nhfile', 'global', 'layout', 'address', 'write', 'read', 'close_stream', 'attach', 'observe', 'offset', 'position']),
    'invent': ([], ['call', 'reset', 'clear', 'option', 'buffer', 'record', 'trace', 'stack', 'snapshot', 'global', 'layout', 'address', 'write', 'read', 'chain', 'queue', 'property', 'foreign', 'input', 'callback', 'function', 'class', 'observe', 'offset', 'held', 'invoke']),
    'display': ([], ['action', 'trace', 'clear', 'draws', 'error', 'errno', 'seed', 'option', 'pointer', 'grid', 'map', 'count', 'alloc_pointer', 'alloc_size', 'alloc_live', 'growth', 'startup', 'startup_size', 'startup_calls', 'coord', 'coord_call', 'wallcolor', 'reset', 'global_size', 'region_size', 'alloc', 'public_size', 'private', 'private_size', 'glyph_events']),
    'cmd': ([], ['watch', 'byvalue', 'callback', 'function', 'ctor', 'ctor_text', 'pool', 'block_count', 'block', 'block_size', 'block_live', 'layout_count', 'layout_name', 'layout_value', 'stack', 'trace', 'input', 'option', 'action', 'reset', 'string', 'string_count', 'string_capacity', 'data']),
    'nhlua': ([], ['consumer_callback', 'consumer_allocator', 'consumer_hook', 'consumer_warning', 'consumer_table_int', 'trace', 'clear_trace', 'option', 'stack', 'alloc', 'free', 'lua', 'lua_load', 'lua_run', 'lua_text', 'lua_integer', 'lua_type', 'lua_top', 'lua_settop', 'lua_string', 'lua_integer_push', 'lua_boolean', 'lua_table', 'lua_field', 'lua_global', 'lua_close', 'setup', 'grow', 'core', 'core_state', 'world', 'data', 'function_name', 'chains', 'snapshot', 'mutate', 'callback_pointer', 'loglua', 'userdata', 'nudfield', 'lua_boolean_value', 'lua_number', 'lua_isinteger']),
    'mkobj': ([], ['pool', 'block_count', 'block_bytes', 'block', 'block_size', 'block_live', 'block_kind', 'heap_obj', 'layout_count', 'layout_name', 'layout_value', 'stack', 'trace', 'option', 'action', 'reset', 'pointer_offset', 'string', 'string_count', 'string_capacity', 'constant', 'data']),
    'eat': ([], ['action', 'callback_identity', 'callback_set', 'cells', 'class_known', 'context', 'count', 'eaten', 'equipment', 'free_count', 'hero', 'hunger', 'layout_count', 'layout_name', 'layout_value', 'mimic', 'mimic_text', 'mon', 'mon_bit', 'moncell', 'more_pointer', 'moves', 'new_mon', 'new_obj', 'nomove_text', 'obj', 'obj_bit', 'option', 'pointer', 'property', 'reset', 'result_string', 'return', 'rng_count', 'rng_length', 'rng_pointer', 'rng_state', 'scalar', 'stack', 'table', 'text', 'tile', 'tin', 'tin_row', 'trace', 'trap', 'victual', 'wall', 'weight']),
    'objnam': ([], ['poison', 'pm', 'mon', 'pool', 'catalogue', 'layout_count', 'layout_name', 'layout_value', 'stack', 'buffer', 'obj', 'ints', 'data', 'alt', 'trace', 'result', 'return', 'option', 'seed', 'clear', 'property', 'item', 'bits', 'name', 'class', 'form', 'scalar', 'fruit', 'callback', 'reset', 'snapshot', 'invoke']),
    'read': ([], ['layout_count', 'layout_name', 'layout_value', 'stack', 'trace', 'buffer', 'clear', 'option', 'seed', 'reset', 'object', 'global', 'input', 'scenario', 'action', 'snapshot', 'projection', 'callback_identity', 'pointer', 'projected_pointer', 'projection_write']),
    'apply': ([], ['layout_count', 'layout_name', 'layout_value', 'stack', 'trace', 'buffer', 'clear', 'option', 'seed', 'reset', 'object', 'global', 'input', 'action', 'snapshot', 'pointer', 'property', 'scene', 'callback_identity', 'callback_action', 'record', 'record_pointer', 'record_write']),

    'insight': ([], 'layout_count layout_name layout_value stack trace result option obj mon pm buffer ints clear property vital dependency_count dependency_name table global equipment item monset reset snapshot invoke startup attribute skill class form conduct logs fruits'.split()),
    'makemon': ([], 'layout_count layout_name layout_value stack trace clear option seed reset monster_setup global vital square planes room map_object action snapshot'.split()),
    'mhitu': ([], 'reset option snapshot trace static stack layout_count layout_name layout_value'.split()),
    'artifact': ([], 'option_name reset option pointer canonical trace stack save_rewind test_constant test_trap_glyph pointer_equal layout_count layout_name layout_value'.split()),
    'decl': ([], 'stack trace action dirty_reset retained dirty_program grow links ctor_ran foreign'.split()),
    'pray': ([], ['string', 'string_count', 'string_capacity', 'god', 'mon_next_offset', 'finish', 'setup', 'constant', 'private', 'pool', 'live', 'layout_count', 'layout_name', 'layout_value', 'stack', 'trace', 'clear_trace', 'option', 'function', 'action', 'reset']),
    'dothrow': ([], ['action', 'trace', 'clear', 'draws', 'error', 'errno', 'seed', 'option', 'pointer', 'coord', 'map', 'grid', 'count', 'alloc_pointer', 'alloc_size', 'reset', 'growth', 'global_size', 'identity', 'pointer_offset', 'constant', 'queue_count', 'queue_identity', 'queue_run', 'source_literal']),
    'pager': ([], ['reset', 'clear', 'option', 'input', 'menu', 'buffer', 'pointer', 'record', 'field', 'tile', 'link', 'property', 'level', 'queue', 'engr', 'trace', 'snapshot', 'layout_count', 'layout_name', 'layout_value', 'stack', 'call', 'consumer', 'observe', 'observe_offset', 'glyph']),
    'muse': ([], ['setup', 'constant', 'choice', 'string', 'string_count', 'string_capacity', 'pool', 'live', 'layout_count', 'layout_name', 'layout_value', 'stack', 'trace', 'option', 'function', 'action', 'reset', 'pointer_offset']),
    'dungeon': ([], ['action', 'trace', 'clear', 'draws', 'error', 'errno', 'seed', 'option', 'input', 'pointer', 'grid', 'map', 'count', 'alloc_pointer', 'alloc_size', 'alloc_live', 'growth', 'serial_length', 'serial_rewind', 'luatop', 'lua', 'reset', 'global_size', 'region_size', 'type_size', 'alloc', 'event_count', 'event_type', 'event_at', 'event_size']),
    'potion': ([], 'action cells class_known count equipment hero layout_count layout_name layout_value mon mon_bit moncell new_mon new_obj obj obj_bit option pointer property reset result_string return rng_count rng_length rng_pointer rng_state scalar stack tile trace'.split()),
    'timeout': ([], 'layout_count layout_name layout_value stack trace result option seed clear obj mon buffer int long arg argument timer saved_rewind global property equipment item monset terrain reset snapshot invoke table_count table_text'.split()),
    'spell': ([], 'layout_count layout_name layout_value stack trace result option seed clear obj mon buffer int intvalue spell item monset global skill link equipment property terrain reset snapshot invoke table_count table_text chain zap zapset chain_state occupation'.split()),
    'monmove': ([], 'action candidate candidates cells class_list count equipment grid grid_state hero layout_count layout_name layout_value level mon mon_bit mon_identity new_mon new_obj obj obj_bit obj_link option point pointer property reset return rng_count rng_length rng_pointer rng_state scalar stack tile trace trap'.split()),
    'detect': ([], 'const_reset dummytrap constant marker pool captured layout_count layout_name layout_value stack trace clear_trace option function action reset level_what level_where'.split()),
    'teleport': ([], 'reset clear option input menu pointer record field link trap dest level stair role debug vision objlevel dungeon tile property trace snapshot layout_count layout_name layout_value stack call'.split()),
    'mklev': ([], 'action trace clear draws error seed option pointer coord map grid count alloc_pointer alloc_size reset growth region_size global_size identity pointer_offset constant alloc_kind'.split()),
    'polyself': ([], 'vision reset option snapshot trace stack layout_count layout_name layout_value'.split()),
    'wizcmds': ([], 'option_name reset option pointer canonical trace stack layout_count layout_name layout_value'.split()),
    'end': ([], 'layout_count layout_name layout_value stack trace output clear option input seed reset item inventory equipment monster_setup global property reason disclosure action snapshot'.split()),
    'dig': ([], 'action alive count digging equipment grid grid_state hero layout_count layout_name layout_value level level_flags link message mon_field mon_identity new new_monster object occupation occupation_call option place point pointer property reset return rng_count rng_length rng_pointer rng_state scalar stack tile timeout timer trace trap'.split()),
    'dokick': ([], 'layout_count layout_name layout_value stack trace result option seed clear mon obj buffer coord reset monset item link equipment oname property terrain global invoke snapshot table_count'.split()),
    'mkmaze': ([], 'action trace clear draws error stack seed option pointer text coord map grid serial_length rewind serial_clear plane hero attach count alloc_pointer alloc_size reset nhfile scratch exclusion region quantity pointer_offset special'.split()),
    'vision': ([], ['layout_count', 'layout_name', 'layout_value', 'stack', 'trace', 'foreign_circle', 'startup_circle', 'payload', 'reset', 'option', 'hero', 'property', 'tile', 'set_monster', 'object', 'room', 'action', 'snapshot', 'value']),
    'do': ([], ['layout_count', 'layout_name', 'layout_value', 'stack', 'stack_span', 'trace', 'snapshot', 'dep_count', 'dep_name', 'function_name', 'option', 'roll', 'callback', 'clear', 'reset', 'object', 'objfield', 'hero', 'equipment', 'property', 'tile', 'trap', 'set_monster', 'text', 'panic_code', 'occupation', 'action']),
    'do_wear': ([], ['layout_count', 'layout_name', 'layout_value', 'stack', 'stack_span', 'trace', 'snapshot', 'dep_count', 'dep_name', 'function_name', 'option', 'roll', 'callback', 'clear', 'reset', 'object', 'objfield', 'hero', 'equipment', 'property', 'text', 'occupation', 'after', 'counter', 'mutation', 'pointer', 'poison', 'macro', 'table', 'set_monster', 'action']),
    'restore': ([], ['layout_count', 'layout_name', 'layout_value', 'reset', 'feed', 'record', 'text', 'option', 'callbacks', 'pointer', 'file', 'global', 'set', 'link', 'trace', 'frees', 'stack', 'snapshot', 'action', 'kind_count', 'kind_name', 'field_count', 'field_name', 'world', 'value', 'buffer', 'saved', 'use_result']),
    'nhlobj': ([], ['bit', 'bytes', 'class', 'collect', 'count', 'eval', 'field', 'link', 'name', 'new', 'object', 'oname', 'option', 'output', 'push', 'reg_callback', 'reg_name', 'release', 'reset', 'set', 'stack', 'state', 'timer', 'trace', 'layout_count', 'layout_name', 'layout_value']),
    'do_name': ([], ['layout_count', 'layout_name', 'layout_value', 'string_count', 'string_name', 'string_value', 'stack', 'option', 'seed', 'trace', 'result', 'clear', 'input', 'random', 'rogue', 'mon', 'obj', 'pm', 'buffer', 'name', 'int', 'intvalue', 'reset', 'monset', 'item', 'property', 'global', 'invoke', 'snapshot', 'table_count', 'table_text', 'startup_bogon']),
    'windows': ([], 'initialize clear reset buffer option field queue menucolor storage consumer dump call trace snapshot stack layout_count layout_name layout_value callback_id null_status_format enc_alias'.split()),
    'cfgfiles': ([], 'open close vformat private layout_count layout_name layout_value stack trace clear_trace input scratch contents file option snapshot callback action reset table_name table_value'.split()),
    'topten': ([], 'time_action reset load input file text argument argc option conduct achievement entry entry_text rolls roll_count action trace snapshot stack layout_count layout_name layout_value'.split()),
    'dogmove': ([], 'reset vision pointer map option action snapshot trace stack layout_count layout_name layout_value'.split()),
    'glyphs': ([], 'clear reset input option symset flags request description glyph custom call color trace dump snapshot stack layout_count layout_name layout_value loadsyms_count loadsyms_name loadsyms_range private backing'.split()),
    'engrave': ([], 'layout_count layout_name layout_value string_count string_name string_value stack trace output clear option input reset seed item item_bit equipment hero prop terrain level global context make engr_bit text action snapshot table_count table_width table_value table_text'.split()),
    'role': ([], 'action answer field generic input layout_count layout_name layout_value name newname output pick pointer reset rng_count rng_length rng_pointer rng_state stack trace value'.split()),
    'mthrowu': ([], 'layout_count layout_name layout_value reset dep_count dep_name option roll seed callback pointer object set_monster position hero property terrain vision attach output attack bhit table action trace frees stack snapshot'.split()),
    'mhitm': ([], 'layout_count layout_name layout_value stack trace clear option seed reset mon field item attack hero prop global terrain action snapshot form form_attack catalogue'.split()),
    'getpos': ([], 'private_state cmap reset option cell input queue goal action trace result snapshot stack layout_count layout_name layout_value'.split()),
    'allmain': ([], 'clear reset fields field_name field option roll clock caps poly occupation steed sex lua role prop prop_count prop_id time call trace snapshot stack layout_count layout_name layout_value'.split()),
    'save': ([], ['reset','pointer','option','action','snapshot','trace','stack','layout_count','layout_name','layout_value','disp_freemem']),
    'sounds': ([], ['action','callback','cell','chain','clear_trace','equipment','grid','hero','input','layout_count','layout_name','layout_value','level','level_flag','mon','nomove','object','option','output','pm','pointer','reason','reset','rng_count','rng_length','rng_pointer','rng_state','room','scalar','sound','stack','table_string','trace']),
    'vault': ([], ['reset','option','set_monster','egd','corridor','cell','object','trap','prop','rng_pointer','rng_length','answer','action','trace','snapshot','stack','layout_count','layout_name','layout_value']),
    'u_init': ([], ['clear','reset','role','option','flags','clock','long','money','roll','sequence','skill','object','align','trop','call','trace','snapshot','stack','layout_count','layout_name','layout_value','table_count','table_rows','table_value']),
    'weapon': ([], ['layout_count','layout_name','layout_value','reset','option','item','item_field','next','inventory','mon','position','equipment','hero','skill','record','counts','menu','matrix','role','class','action','trace','output','clear','snapshot','pointer','arw','stack','table_count','table_value','table_text']),
    'region': ([], ['layout_count','layout_name','layout_value','reset','option','roll','rect','pointer','set_monster','hero','property','field','messages','action','trace','io_size','free_count','stack','snapshot']),
    'dog': ([], ['action','chain','clear_trace','count','edog','extension','hero','hero_value','layout_count','layout_name','layout_value','level','mon','mon_value','moves','obj_value','object','objfield','option','pointer','reset','rng_count','rng_length','rng_pointer','rng_state','stack','trace','vital']),
    'sfbase': ([], ['serial_count','serial_name','values_count','values_name','norms_count','norms_name','reset','option','file','pointer','input','close_log','logs','trace','snapshot','table','action','value','norm','log','layout_count','layout_name','layout_value','stack']),
    'attrib': ([], ['reset','option','attr','role_array','advance','prop','object','equip','rng_pointer','rng_length','input','action','attrname','innate','trace','result','snapshot','stack','layout_count','layout_name','layout_value']),
    'pline': ([], ['caps','reset','clear','option','field','input','argument','trace','snapshot','message','direct','stack','layout_count','layout_name','layout_value']),
    'mail': ([], ['layout_count','layout_name','layout_value','string_count','string_name','string_value','reset','option','env','stat','moves','hero','prop','flags','cell','row','stairs','mon','coord','info','action','trace','clear','snapshot','pointer','stack']),
    'questpgr': ([], ['action', 'chain', 'clear_trace', 'dead', 'free_count', 'gender', 'hero', 'input', 'layout_count', 'layout_name', 'layout_value', 'level_message', 'object', 'option', 'pointer', 'reset', 'rng_count', 'rng_length', 'rng_pointer', 'rng_state', 'source', 'stack', 'trace']),
    'symbols': ([], ['layout_count','layout_name','layout_value','reset','option','input','file','symset','global','symbol','action','compatible','pointer','trace','free_count','stack','buffer','table_name','table_field','snapshot']),
    'bones': ([], ['time_bridge', 'pointer', 'reset', 'option', 'link', 'name', 'omonst', 'pm', 'known', 'trap', 'cemetery', 'action', 'trace', 'snapshot', 'stack', 'layout_count', 'layout_name', 'layout_value']),
    'explode': ([], ['layout_count', 'layout_name', 'layout_value', 'reset', 'option', 'prop', 'cell', 'action', 'trace', 'snapshot', 'pointer', 'stack']),
    'earlyarg': ([], ['layout_count', 'layout_name', 'layout_value', 'reset', 'arg', 'directory', 'option_name', 'preset', 'callback', 'action', 'trace', 'snapshot', 'result', 'result_alias', 'pointer', 'mutate', 'stack', 'table_count', 'table_name', 'table_value', 'arg_origin', 'table_set_value', 'table_set_name']),
    'report': ([], ['reset', 'option', 'config', 'message', 'index', 'init', 'bidshow', 'encode', 'submit', 'bug', 'libc', 'gdb', 'saved', 'handler', 'signals', 'trace', 'output', 'clear', 'stack', 'layout_count', 'layout_name', 'layout_value', 'crashreport', 'devteam']),
    'mkroom': ([], ['layout_count', 'layout_name', 'layout_value', 'reset', 'option', 'birth', 'shoptype', 'room', 'subroom', 'cell', 'grid', 'stair', 'vital', 'maze', 'rng_pointer', 'rng_length', 'rng_state', 'rng_count', 'trace', 'clear_trace', 'pointer', 'room_value', 'count', 'item', 'monster_field', 'level_flags', 'io_length', 'io_position', 'rewind', 'poison_rooms', 'table', 'action', 'stack']),
    'sfstruct': ([], ['layout_count', 'layout_name', 'layout_value', 'reset', 'option', 'open', 'seed_file', 'seek', 'fd', 'state', 'buffer', 'capacity', 'fill', 'flags', 'io', 'serial', 'flags_value', 'eof', 'panic_code', 'trace', 'stack', 'restore', 'proc', 'saved_size', 'read_file', 'saved']),
    'wield': ([], ['layout_count', 'layout_name', 'layout_value', 'reset', 'option', 'rng_pointer', 'rng_length', 'rng_count', 'rng_state', 'object', 'set_monster', 'hero', 'prop', 'equip', 'link', 'class', 'split', 'action', 'pointer', 'snapshot', 'trace', 'free_count', 'stack', 'string']),
    'worn': ([], ['layout_count', 'layout_name', 'layout_value', 'reset', 'option', 'rng_pointer', 'rng_length', 'rng_count', 'rng_state', 'object', 'set_monster', 'hero', 'prop', 'class', 'equip', 'link', 'loot', 'action', 'pointer', 'snapshot', 'trace', 'free_count', 'stack', 'worn_table_count', 'worn_mask', 'worn_what', 'worn_cell']),
    'hacklib': ([], ['layout_count', 'layout_name', 'layout_value', 'reset', 'input', 'pointer', 'snapshot', 'action', 'sort_setup', 'sort_action', 'comparator_pointer', 'sort_state', 'alloc_option', 'alloc_count', 'fd_action', 'io_trace', 'stack', 'trace', 'table_count', 'table']),
    'mondata': ([], ['layout_count', 'layout_name', 'layout_value', 'reset', 'trace', 'snapshot', 'option', 'rng_pointer', 'rng_length', 'rng_count', 'rng_state', 'set_monster', 'hero', 'prop', 'object', 'equip', 'attack', 'permonst', 'input', 'action', 'pointer', 'table', 'table_count', 'stack']),
    'dbridge': ([], ['layout_count', 'layout_name', 'layout_value', 'reset', 'trace', 'snapshot', 'option', 'rng_pointer', 'rng_length', 'rng_count', 'rng_state', 'set_monster', 'hero', 'prop', 'terrain', 'add_monster', 'add_object', 'trap', 'entity', 'action', 'pointer', 'stack']),
    'mcastu': ([], ['layout_count', 'layout_name', 'layout_value', 'reset', 'trace', 'snapshot', 'option', 'rng_pointer', 'rng_length', 'rng_count', 'rng_state', 'set_monster', 'hero', 'prop', 'attack', 'action', 'pointer', 'table', 'table_count', 'stack']),
    'ball': ([], ['layout_count', 'layout_name', 'layout_value', 'reset', 'trace', 'snapshot', 'option', 'rng_pointer', 'rng_length', 'rng_count', 'rng_state', 'object', 'hero', 'prop', 'terrain', 'equip', 'add', 'setup_floor', 'action', 'pointer', 'state', 'stack']),
    'o_init': ([], ['compare_count', 'compare_text', 'compare_result', 'compare_again', 'layout_count', 'layout_name', 'layout_value', 'reset', 'trace', 'snapshot', 'option', 'rng_pointer', 'rng_length', 'rng_count', 'rng_state', 'record', 'row_value', 'object', 'hero', 'prop', 'set_uname', 'input', 'sorted', 'pick_input', 'action', 'pointer', 'table_pointer', 'table_count', 'nhfile', 'io_size', 'io_length', 'io_position', 'free_count', 'stack']),
    'worm': ([], ['layout_count', 'layout_name', 'layout_value', 'reset', 'trace', 'snapshot', 'option', 'rng_pointer', 'rng_length', 'rng_count', 'rng_state', 'hero', 'monster_field', 'prop', 'node', 'set_time', 'action', 'pointer', 'node_pointer', 'nhfile', 'io_size', 'io_length', 'io_position', 'free_count', 'stack']),
    'wizard': ([], ['layout_count', 'layout_name', 'layout_value', 'reset', 'trace', 'snapshot', 'option', 'rng_pointer', 'rng_length', 'rng_count', 'rng_state', 'object', 'hero', 'prop', 'monster_field', 'stair', 'vital', 'action', 'pointer', 'table_pointer', 'table_count', 'stack']),
    'steed': ([], ['layout_count', 'layout_name', 'layout_value', 'reset', 'trace', 'snapshot', 'option', 'rng_pointer', 'rng_length', 'rng_count', 'rng_state', 'object', 'hero', 'prop', 'monster_field', 'terrain', 'action', 'pointer', 'stack']),
    'lock': ([], ['layout_count', 'layout_name', 'layout_value', 'reset', 'trace', 'snapshot', 'option', 'rng_pointer', 'rng_length', 'rng_count', 'rng_state', 'object', 'hero', 'prop', 'terrain', 'monster_field', 'xlock', 'occupation', 'action', 'pointer', 'stack']),
    'light': ([], ['layout_count', 'layout_name', 'layout_value', 'reset', 'trace', 'snapshot', 'option', 'object', 'monster_field', 'hero', 'ls', 'action', 'union_pointer', 'pointer', 'node_pointer', 'node_count', 'nhfile', 'io_pointer', 'io_length', 'io_position', 'io_size', 'free_count', 'panic_code', 'stack']),
    'priest': ([], ['layout_count', 'layout_name', 'layout_value', 'reset', 'trace', 'snapshot', 'option', 'rng_pointer', 'rng_length', 'rng_count', 'rng_state', 'add_monster', 'monster_field', 'hero', 'prop', 'epri', 'emin', 'moves', 'candidates_pointer', 'candidates_count', 'room', 'terrain', 'action', 'input', 'pointer', 'free_count', 'stack']),
    'coloratt': ([], ['regex_dependency_compile', 'regex_dependency_error', 'layout_count', 'layout_name', 'layout_value', 'reset', 'trace', 'snapshot', 'option', 'picks_pointer', 'picks_length', 'action', 'output', 'output_size', 'pointer', 'table_count', 'table_name', 'table_value', 'free_count', 'picks_free_count', 'regex_match', 'stack']),
    'version': ([], ['fallback_witness', 'fallback_witness_base', 'fallback_witness_size', 'layout_count', 'layout_name', 'layout_value', 'string_count', 'string_name', 'string_value', 'reset', 'trace', 'snapshot', 'option', 'nomake', 'string', 'version', 'nhfile', 'action', 'output', 'output_size', 'pointer', 'table_count', 'table_size', 'table_name', 'rt_count', 'rt_token', 'rt_value', 'io_pointer', 'io_size', 'io_length', 'io_position', 'stack']),
    'music': ([], ['layout_count', 'layout_name', 'layout_value', 'reset', 'trace', 'snapshot', 'option', 'rng_pointer', 'rng_length', 'rng_count', 'rng_state', 'add_monster', 'monster_field', 'hero', 'prop', 'terrain', 'trap', 'object', 'action', 'input', 'tune', 'pointer', 'stack']),
    'rumors': ([], ['layout_count', 'layout_name', 'layout_value', 'string_count', 'string_name', 'string_value', 'reset', 'trace', 'snapshot', 'option', 'rng_pointer', 'rng_length', 'rng_count', 'rng_state', 'file', 'remove', 'open', 'close', 'position', 'action', 'output', 'output_size', 'cap_count', 'cap_pointer', 'cap_name', 'rng_pointer_id', 'saved_pointer', 'saved_size', 'restore_position', 'hero', 'prop', 'stack', 'free_count', 'open_count']),
    'shknam': ([], ['layout_count', 'layout_name', 'layout_value', 'reset', 'trace', 'snapshot', 'option', 'rng_pointer', 'rng_length', 'rng_count', 'rng_state', 'table_count', 'table_string', 'table_value', 'list_count', 'list_name', 'list_pointer', 'obj', 'obit', 'mon', 'mbit', 'name', 'hero', 'prop', 'room', 'door', 'cell', 'action', 'pointer', 'extra_pointer', 'extra_size', 'extra_poison', 'free_count', 'output', 'stack']),
    'monst': ([], ['layout_count', 'layout_name', 'layout_value', 'init', 'count', 'field_count', 'field_name', 'field_kind', 'value', 'name', 'attack', 'constant_attack', 'constants', 'monsters', 'poison', 'mutate', 'mutate_attack', 'names', 'stack']),
    'objects': ([], ['layout_count', 'layout_name', 'layout_value', 'init', 'count', 'field_count', 'field_name', 'field_kind', 'value', 'string', 'objects', 'descriptors', 'poison', 'mutate', 'strings', 'stack']),
    'fountain': ([], ['layout_count', 'layout_name', 'layout_value', 'reset', 'trace', 'snapshot', 'option', 'rng_pointer', 'rng_length', 'rng_count', 'rng_state', 'obj', 'next', 'inventory', 'obit', 'hero', 'prop', 'terrain', 'trap', 'mon', 'mbit', 'vital', 'area', 'counter', 'action', 'object_pointer', 'hero_pointer', 'stack']),
    'sit': ([], ['layout_count', 'layout_name', 'layout_value', 'reset', 'trace', 'snapshot', 'option', 'rng_pointer', 'rng_length', 'rng_count', 'rng_state', 'obj', 'next', 'inventory', 'obit', 'hero', 'prop', 'terrain', 'trap', 'species', 'input', 'action', 'object_pointer', 'hero_pointer', 'stack']),
    'steal': ([], ['layout_count', 'layout_name', 'layout_value', 'reset', 'trace', 'snapshot', 'option', 'rng_pointer', 'rng_length', 'rng_count', 'rng_state', 'obj', 'next', 'inventory', 'floor', 'minvent', 'equipment', 'obit', 'mbit', 'mon', 'monnext', 'hero', 'prop', 'reason', 'description', 'action', 'afternmv', 'object_pointer', 'mon_pointer', 'output', 'stack']),
    'selvar': ([], ['layout_count', 'layout_name', 'layout_value', 'reset', 'clear_trace', 'trace', 'rng_pointer', 'rng_length', 'rng_count', 'rng_state', 'option', 'new', 'free', 'clear', 'clone', 'get', 'set', 'bounds', 'recalc', 'not', 'filter', 'mapfilter', 'rndcoord', 'grow', 'flood_callback', 'callback_identity', 'callback_pointer', 'flood', 'ellipse', 'distance', 'gradient', 'line', 'randline', 'iterate', 'irregular', 'description', 'room', 'coder', 'fromroom', 'newsyms', 'cell', 'array', 'have', 'pointer', 'map', 'field', 'rect', 'rect_size', 'coord', 'description_pointer', 'description_size', 'stack']),
    'iactions': ([], ['layout_count', 'layout_name', 'layout_value', 'reset', 'clear', 'trace', 'item', 'class', 'known', 'option', 'names', 'contents', 'equipment', 'hero', 'candelabrum', 'select', 'naming', 'reading', 'add', 'push', 'run', 'menu_count', 'menu_action', 'menu_letter', 'menu_text', 'menu_any', 'any_size', 'output', 'output_size', 'freed', 'live', 'name', 'class_of', 'stack']),
    'minion': ([], ['parse_offer', 'parsed_offer', 'layout_count', 'layout_name', 'layout_value', 'unique', 'copy_monster', 'reset', 'clear', 'trace', 'rng_pointer', 'rng_length', 'rng_count', 'rng_state', 'option', 'input', 'cash', 'cash_value', 'hero', 'properties', 'wield', 'vital', 'endgame', 'victim', 'chain', 'priest', 'minion', 'emin_flags', 'equip', 'emin', 'emin_pointer', 'emin_size', 'mon_field', 'strategy', 'parent', 'count', 'pets', 'botl', 'object_pointer', 'object_size', 'elemental', 'action', 'summon', 'bribe', 'stack']),
    'quest': ([], ['layout_count', 'layout_name', 'layout_value', 'reset', 'clear', 'trace', 'rng_pointer', 'rng_length', 'rng_count', 'rng_state', 'option', 'qset', 'qget', 'hset', 'levels', 'alignment', 'deaf', 'ids', 'victim', 'inventory', 'traps', 'branch', 'scalar', 'strategy', 'trap_chain', 'item_bit', 'state_pointer', 'state_size', 'action', 'check', 'stack']),
    'mdlib': ([], ['layout_count', 'layout_name', 'layout_value', 'string_count', 'string_name', 'string_value', 'version_field', 'reset', 'reference_reset', 'clear', 'nested', 'trace', 'output', 'output_size', 'words_pointer', 'words_size', 'word_length', 'words', 'ignored', 'version_string', 'version_id', 'banner', 'make_version', 'build', 'compat', 'validate', 'init', 'release', 'next', 'calls', 'scalar', 'set_scalar', 'buffer', 'opt', 'table_count', 'table_string', 'table_value', 'valid', 'stack']),
    'write': ([], ['layout_count', 'layout_name', 'layout_value', 'reset', 'clear', 'trace', 'rng_pointer', 'rng_length', 'rng_count', 'rng_state', 'option', 'properties', 'property', 'hero', 'literate', 'paper', 'pen', 'object', 'descr_index', 'name', 'descr', 'class', 'known', 'encountered', 'input', 'cost', 'ok', 'write', 'description', 'snapshot_pointer', 'snapshot_size', 'scalar', 'stack']),
    'getline': ([], ['layout_count', 'layout_name', 'layout_value', 'reset', 'clear', 'trace', 'input_pointer', 'input_length', 'option', 'snapshot_pointer', 'snapshot_size', 'scalar', 'default', 'line', 'hooked', 'hook', 'ext', 'wait', 'history', 'stack']),
    'mkmap': ([], ['layout_count', 'layout_name', 'layout_value', 'reset', 'options', 'clear', 'trace', 'rng_pointer', 'rng_length', 'rng_count', 'rng_state', 'snapshot_pointer', 'snapshot_size', 'scalar', 'cell', 'cell_field', 'room', 'counts', 'bounds', 'init', 'fill', 'get', 'pass', 'flood', 'cleanup', 'join', 'finish', 'remove', 'remove_region', 'lit', 'make', 'stack']),
    'exper': ([], ['layout_count', 'layout_name', 'layout_value', 'reset', 'clear', 'trace', 'assertion', 'rng_pointer', 'rng_length', 'rng_count', 'rng_state', 'option', 'snapshot_size', 'snapshot_pointer', 'role', 'hero', 'health', 'increments', 'flags', 'amphibious', 'victim', 'attack', 'threshold', 'energy_modifier', 'power', 'experience', 'more', 'lose', 'killer', 'new_level', 'plus', 'random_experience', 'achievements', 'stack']),
    'mplayer': ([], ['layout_count', 'layout_name', 'layout_value', 'reset', 'clear', 'trace', 'rng_pointer', 'rng_length', 'rng_count', 'rng_state', 'option', 'existing', 'occupied', 'dev', 'name', 'armor', 'make', 'create', 'role', 'talk', 'result', 'name_result', 'monster_count', 'mon_pm', 'mon_female', 'mon_peaceful', 'mon_level', 'mon_hp', 'mon_hpmax', 'mon_malign', 'mon_name', 'object_count', 'object_field', 'object_quantity', 'good_calls', 'fake_copy', 'stack']),
    'extralev': ([], ['layout_count', 'layout_name', 'layout_value', 'reset', 'clear', 'trace', 'rng_pointer', 'rng_length', 'rng_count', 'rng_state', 'options', 'make', 'corr', 'join', 'corridor', 'walk', 'ghost', 'grid_pointer', 'terrain_pointer', 'rooms_pointer', 'smeq_pointer', 'nroom', 'nroom_set', 'cell', 'room', 'typ', 'door', 'typ_set', 'ghost_sleep', 'renamed_sleep', 'object_count', 'object_type', 'object_quantity', 'object_weight', 'object_spe', 'object_cursed', 'object_known', 'object_proof', 'stack']),
    'were': ([], ['layout_count', 'layout_name', 'layout_value', 'reset', 'clear', 'trace', 'rng_pointer', 'rng_length', 'rng_count', 'option', 'properties', 'mon', 'hero', 'counter', 'beastie', 'change', 'new', 'summon', 'you', 'unwere', 'lycanthrope', 'changes', 'set_changes', 'mon_pm', 'mon_hp', 'mon_sleep', 'mon_move', 'mon_frozen', 'mon_flee', 'current', 'lycan', 'timeout', 'visible', 'genbuf', 'summoned_count', 'summoned_pm', 'summoned_tame', 'stack']),
    'unixtty': ([], ['layout_count', 'layout_name', 'layout_value', 'options', 'clear_trace', 'trace', 'input_pointer', 'output_pointer', 'init_pointer', 'cur_pointer', 'ospeed', 'erase', 'intr', 'kill', 'chars', 'echo', 'cbreak', 'window', 'iflags', 'needed', 'set_needed', 'env', 'get', 'set', 'fast', 'on', 'off', 'fixup', 'error', 'exit_status', 'stack']),
    'ioctl': ([], ['window_options', 'dimensions', 'layout_count', 'layout_name', 'layout_value', 'sig_default', 'sig_ignore', 'sig_error', 'options', 'shellers', 'termio_pointer', 'input_pointer', 'output_pointer', 'trace', 'handler', 'get', 'set', 'windows', 'suspend', 'stack']),
    'rnd': ([], ['layout_count', 'layout_name', 'layout_value', 'seed', 'seed_calls', 'seed_value', 'init', 'init_random', 'reseed', 'hero', 'rn2', 'display', 'rnd', 'rnd_display', 'rnl', 'dice', 'rne', 'rnz', 'shuffle', 'log_init', 'enabled', 'count', 'caller', 'env', 'diagnostic', 'panic_message', 'state', 'state_init', 'log_pointer', 'log_disp', 'caller_file', 'caller_line', 'caller_function', 'flush', 'close', 'stack']),
    'posixregex': ([], ['dependency_compile', 'dependency_match', 'dependency_error', 'layout_count', 'layout_name', 'layout_value', 'identifier', 'init', 'compile', 'match', 'error', 'err', 'set_err', 'free', 'stack']),
    'drawing': ([], ['layout_count', 'layout_name', 'layout_value', 'constant_count', 'constant_name', 'constant_value', 'table_count', 'table_pointer', 'table_symbol', 'table_name', 'table_explanation', 'table_color', 'object', 'monclass', 'furniture', 'char_signed', 'stack']),
    'utf8map': ([], ['layout_count', 'layout_name', 'layout_value', 'gbuf_count', 'clear_trace', 'trace', 'unicode', 'set', 'free', 'map_u', 'map_code', 'map_text', 'null_text', 'gbuf', 'fallback', 'mixed', 'custom', 'custom_name', 'custom_count', 'custom_type', 'custom_head', 'custom_end', 'detail_next', 'detail_glyph', 'detail_code', 'detail_text', 'reset', 'cleanup', 'stack']),
    'alloc': ([], ['long_size', 'int_size', 'lua_integer_size', 'ull_size', 'ptrbuf_count', 'ptrbuf_size', 'has_ptr_fmt', 'monitor_heap', 'alloc', 'realloc', 'dup', 'signed', 'unsigned', 'format', 'result', 'signed_result', 'unsigned_result', 'malloc_calls', 'realloc_calls', 'requested', 'panic_message', 'stack']),
    'date': ([], ['field_count', 'field_name', 'field_offset', 'field_size', 'field_kind', 'version_size', 'offset_incarnation', 'offset_feature_set', 'offset_entity_count', 'int_size', 'long_size', 'time_size', 'bufsz', 'build_date_time', 'git_sha', 'git_branch', 'git_prefix', 'pointer', 'env', 'inputs', 'populate', 'release', 'trace', 'stack']),
    'rip': ([], ['bufsz', 'plname_size', 'long_size', 'time_size', 'dumplog', 'dedication', 'inputs', 'run', 'head', 'line_count', 'line_window', 'line_attribute', 'line_dump', 'line_live', 'line_text', 'killer_how', 'killer_format', 'killer_calls', 'killer_size', 'date_calls', 'date_argument', 'stack']),
    'sys': ([], ['field_count', 'field_name', 'field_offset', 'field_size', 'field_kind', 'gc_field_count', 'gc_field_name', 'gc_field_offset', 'gc_field_size', 'config_count', 'config_name', 'config_value', 'string_count', 'string_name', 'string_value', 'll_none', 'int_size', 'sys_pointer', 'gc_pointer', 'init', 'release', 'seduce', 'env', 'populate']),
    'isaac64': (['n', 'r', 'm', 'a', 'b', 'c'], ['init', 'reseed', 'next', 'bounded']),
    'nhmd4': (['lo', 'hi', 'a', 'b', 'c', 'd', 'buffer', 'block'], ['init', 'update', 'final']),
    'strutil': (['len', 'str', 'buf'], ['init', 'append', 'reserve', 'empty', 'crlf', 'match', 'guarded_strlen', 'message', 'buffer_size', 'largest_int']),
    'rect': (['lx', 'ly', 'hx', 'hy'], ['init', 'free', 'index', 'get', 'random', 'bounds', 'remove', 'add', 'split', 'seed', 'rng_count', 'rng_bound', 'rng_caller', 'diagnostic_count', 'diagnostic_message', 'count', 'capacity', 'data', 'coord_size', 'colno', 'rowno']),
    'track': (['utcnt', 'utpnt', 'utrack', 'x', 'y', 'ux', 'uy', 'otyp'], ['init', 'hero', 'set', 'get', 'has', 'save', 'rest', 'corrupt_counts', 'stream', 'stream_size', 'trace', 'panic_message', 'count', 'point', 'data', 'coord_size', 'coordxy_size', 'int_size', 'otyp_size', 'utsz', 'stealth', 'writing', 'freeing', 'counting']),
    'calendar': (['tm_year', 'tm_mon', 'tm_mday', 'tm_hour', 'tm_min', 'tm_sec', 'tm_wday', 'tm_yday'], ['dep_time', 'dep_localtime', 'dep_mktime', 'dep_strlen', 'dep_atoi', 'dep_strtoll', 'dep_getenv', 'dep_format', 'dep_datestr', 'dep_emscripten', 'now', 'year', 'date', 'time', 'format', 'parse', 'moon', 'friday', 'night', 'midnight', 'set_env', 'int_size', 'long_size', 'time_size', 'stack']),
    'stairs': (['sx', 'sy', 'tolev', 'up', 'isladder', 'u_traversed', 'next', 'dnum', 'dlevel', 'uz'], ['coordxy_size', 'bool_size', 'bool_signed', 'level_size', 'level_field_size', 'init', 'hero', 'add', 'head', 'free', 'at', 'find', 'find_from', 'find_dir', 'find_type_dir', 'find_special_dir', 'special', 'up', 'down', 'on', 'ladder', 'on_up', 'on_down', 'known', 'describe', 'description_buffer', 'trace']),
}


# Uses existing globals root/sdk/work/defines and imports json/subprocess/Path.
# Profile mirrors each frozen component recipe. ZAP's absent forced header/-g
# remain a recorded narrow diagnostic profile; production game flags unchanged.
C_SHADOW_EXPORTS = {'unixmain': ['_main', '_malloc', '_free', '_probe_getenv', '_probe_env', '_probe_passwd_uid', '_probe_passwd_gid', '_probe_passwd_string', '_probe_passwd_set', '_probe_sigaction_size', '_probe_sigaction_flags', '_probe_call', '_probe_reset', '_probe_clear', '_probe_option', '_probe_buffer', '_probe_argv', '_probe_arg', '_probe_global', '_probe_layout', '_probe_read', '_probe_write', '_probe_address', '_probe_trace', '_probe_stack', '_probe_action', '_probe_actions', '_probe_handler', '_probe_function', '_probe_errno', '_probe_snapshot', '_probe_finished'], 'options': ['_malloc', '_free', '_probe_context_size', '_probe_layout_count', '_probe_layout_name', '_probe_layout_value', '_probe_function_token', '_probe_table_bytes', '_probe_catalogue', '_probe_stringbuf', '_probe_stringbuf_text', '_probe_function_count', '_probe_function_name', '_probe_call', '_probe_data', '_probe_buffer', '_probe_global', '_probe_layout', '_probe_read', '_probe_write', '_probe_address', '_probe_stack', '_probe_trace', '_probe_clear', '_probe_result', '_probe_option', '_probe_return', '_probe_reply', '_probe_menu', '_probe_input', '_probe_reset', '_probe_sizes', '_probe_snapshot'], 'botl': ['_malloc', '_free', '_probe_object', '_probe_equipment', '_probe_stack_span', '_probe_reply', '_probe_context_size', '_probe_layout_count', '_probe_layout_name', '_probe_layout_value', '_probe_stack', '_probe_trace', '_probe_snapshot', '_probe_dep_count', '_probe_dep_name', '_probe_function_name', '_probe_clear', '_probe_reset', '_probe_option', '_probe_callback', '_probe_menu', '_probe_input', '_probe_text', '_probe_property', '_probe_hero', '_probe_stat', '_probe_any', '_probe_pointer', '_probe_lastptr', '_probe_action', '_probe_startup', '_probe_public_tables', '_probe_result_text', '_probe_private_count', '_probe_private_text', '_probe_private_number', '_probe_global', '_probe_read', '_probe_write'], 'zap': ['_malloc', '_free', '_probe_level', '_probe_type_class', '_probe_option_id', '_probe_consumer', '_probe_history', '_probe_callback', '_probe_destroy', '_probe_pm', '_probe_mon', '_probe_buffer', '_probe_obj', '_probe_ints', '_probe_any', '_probe_trap', '_probe_layout_count', '_probe_layout_name', '_probe_layout_value', '_probe_stack', '_probe_trace', '_probe_result', '_probe_return', '_probe_option', '_probe_seed', '_probe_clear', '_probe_property', '_probe_item', '_probe_map', '_probe_link', '_probe_grid', '_probe_scalar', '_probe_reset', '_probe_snapshot', '_probe_invoke'], 'unixunix': ['_probe_action', '_probe_trace', '_probe_clear', '_probe_outcome', '_probe_errno', '_probe_option', '_probe_option_get', '_probe_now', '_probe_answer', '_probe_char', '_probe_file', '_probe_open', '_probe_file_count', '_probe_fd_count', '_probe_fd_open', '_probe_event_count', '_probe_handler', '_probe_done_id', '_probe_handler_raw', '_probe_signal_run', '_probe_growth', '_probe_reset', '_probe_pointer', '_probe_region_size', '_probe_global_size', '_probe_sourcebuf', '_teleport_unixunix_global', '_teleport_unixunix_read', '_teleport_unixunix_write', '_teleport_unixunix_address', '_teleport_unixunix_layout', '_teleport_unixunix_storage']}
C_SHADOW_NAMES = set(C_SHADOW_EXPORTS)

def c_shadow_flags(name):
    flags = ['-O2', '-sMEMORY64=1', *defines,
             '-I'+str(root/'.cache/wasm64-build/tree/include'),
             '-I'+str(root/'.cache/ncurses-wasm64-build/include'),
             '-I'+str(root/'nethack-c/wasm'), '-I'+str(root/'scripts'),
             '-I'+str(work)]
    if name in ['unixunix','unixmain']:
        flags += ['-g']
    if name != 'zap':
        flags += ['-include', str(root/'nethack-c/wasm/native-terminal.h')]
    if name in ['options','botl']:
        flags += ['-Dfree=teleport_probe_free',
                  '-ffile-prefix-map='+str(root/'.cache/wasm64-build/tree/src')+'/=',
                  '-ffile-prefix-map='+str(root/'scripts/../.cache/wasm64-build/tree/src')+'/=']
    elif name == 'unixunix':
        # Parent binds the fixture's one absolute original-source include to root.
        flags += ['-fmacro-prefix-map='+str(root/'.cache/wasm64-build/tree/sys/unix')+'/=../sys/unix/']
    elif name == 'unixmain':
        flags += ['-fmacro-prefix-map='+str(root/'scripts/../.cache/wasm64-build/tree/sys/unix/unixmain.c')+'=../sys/unix/unixmain.c']
    elif name == 'zap':
        flags += ['-ffile-prefix-map='+str(root/'scripts/../nethack-c/upstream/src')+'/=']
    return flags

def c_shadow_compile(source, output, flags):
    # Separate objects/no LTO; all paths are shadow-rooted inputs or fresh work.
    assert not any(str(x).startswith('-flto') for x in flags)
    subprocess.run(list(map(str,[sdk/'upstream/emscripten/emcc', *flags,
                                '-c',source,'-o',output])),check=True)
    return output

def build_c_shadow_probes(name):
    flags=c_shadow_flags(name)
    fixture=root/('scripts/tu-'+name+'-probe.c')
    if name=='unixunix':
        # A missing/unbound include must fail before compiling any live source.
        include='#include "'+str(root/'.cache/wasm64-build/tree/sys/unix/unixunix.c')+'"'
        assert include in fixture.read_text(), 'Bind UNIXUNIX fixture to exact absolute shadowRoot first'
        assert '@SHADOW_ROOT@' not in fixture.read_text()
    dependencies={
        'unixunix':[], 'unixmain':['hacklib','strutil'],
        'options':['alloc','hacklib','strutil','objects','monst','role','drawing','posixregex'],
        'botl':['alloc','hacklib','strutil','monst','objects','role'],
        'zap':['alloc','hacklib','strutil','objects','monst','drawing'],
    }[name]
    objects=[]
    for dependency in dependencies:
        relative='sys/share/posixregex.c' if dependency=='posixregex' else 'src/'+dependency+'.c'
        objects.append(c_shadow_compile(root/'.cache/wasm64-build/tree'/relative,
            work/(name+'-dependency-'+dependency+'.o'),flags))
    if name=='unixmain':
        objects.append(c_shadow_compile(root/'nethack-c/wasm/tu-fragments/unixmain-consumer.c',
                                       work/'unixmain-probe-consumer.o',flags))
    if name=='zap':
        objects.append(c_shadow_compile(root/'scripts/tu-zap-consumer.c',
                                       work/'zap-probe-consumer.o',flags))
    if name in ['botl','zap']:
        support=work/(name+'-owned-support.c')
        prefix='#include "tu-source-locations.h"\n' if name=='zap' else ''
        support.write_text(prefix+'#include '+json.dumps(str(root/('nethack-c/wasm/tu-'+name+'-support.inc')))+'\n')
        objects.append(c_shadow_compile(support,work/(name+'-owned-support.o'),flags))
    # OPTIONS and UNIXMAIN fixtures include their own support exactly once.
    # UNIXUNIX support is separate once; none use generic tu-support.c.
    if name=='unixunix':
        objects.append(c_shadow_compile(root/'nethack-c/wasm/tu-fragments/unixunix-support.c',
                                       work/'unixunix-owned-support.o',flags))
    for mode in ['reference','hybrid']:
        args=[sdk/'upstream/emscripten/emcc',*flags,fixture,*objects,
              '-sMODULARIZE=1','-sEXPORT_ES6=1','-sENVIRONMENT=node',
              '-sALLOW_MEMORY_GROWTH=1',
              '-sEXPORTED_FUNCTIONS='+json.dumps(C_SHADOW_EXPORTS[name])]
        runtime=['HEAPU8']
        if name=='unixunix':
            args += ['-sTABLE_BASE=2','-sSTACK_SIZE=4194304','--no-entry']
            runtime += ['stringToUTF8','lengthBytesUTF8','stackSave','stackRestore','stackAlloc','UTF8ToString']
            args += ['-DREFERENCE_UNIXUNIX=1' if mode=='reference' else '-DHYBRID_UNIXUNIX=1']
        elif name=='unixmain':
            args += ['-sTABLE_BASE=2','-sINVOKE_RUN=0','-sEXIT_RUNTIME=1',
                     '-sINITIAL_MEMORY=4194304','-sSTACK_SIZE=1048576',
                     '--post-js',root/'nethack-c/wasm/runtime.js']
            runtime += ['FS','ENV','callMain','stackSave','stackRestore']
            if mode=='reference':args += ['-DTELEPORT_REFERENCE_TU']
            else:args += [root/'nethack-c/wasm/tu-fragments/unixmain-entry.c']
        else:
            args += ['--no-entry']
            if mode=='reference':
                args += ['-DTELEPORT_REFERENCE_TU']
                if name=='options':args += ['-DTELEPORT_REFERENCE_OPTIONS']
                if name=='zap':args += ['-DTELEPORT_REFERENCE_ZAP']
            if name=='options':
                args += ['--js-library',root/'nethack-c/wasm/native-libc-library.js',
                         '-sSTACK_SIZE=1048576','-Wl,--error-limit=0']
                runtime += ['FS','stackSave','stackRestore']
            if name=='botl' and mode=='hybrid':
                storage=c_shadow_compile(root/'nethack-c/wasm/tu-botl-storage.c',
                                          work/'botl-probe-storage.o',flags)
                args += [storage]
            if name=='zap':
                storage_flags=flags+(['-DTELEPORT_REFERENCE_ZAP']if mode=='reference'else[])
                args += [c_shadow_compile(root/'nethack-c/wasm/tu-zap-storage.c',
                                          work/('zap-probe-storage-'+mode+'.o'),storage_flags)]
        if mode=='hybrid':
            args += ['--js-library',root/('nethack-c/wasm/tu-libraries/'+name+'.js')]
            startup={'botl':'$teleportBotlInit','zap':'$teleportZapInit'}.get(name)
            if startup:args += ['-sDEFAULT_LIBRARY_FUNCS_TO_INCLUDE='+json.dumps([startup])]
        args += ['-sEXPORTED_RUNTIME_METHODS='+json.dumps(runtime),
                 '-o',work/(name+'-'+mode+'.mjs')]
        subprocess.run(list(map(str,args)),check=True)

probes.update({'hack': ([], ['option_name', 'reset', 'option', 'pointer', 'canonical', 'trace', 'stack', 'error', 'layout_count', 'layout_name', 'layout_value', 'pointer_equal', 'test_constant', 'callback_pointer', 'invoke_comparator', 'foreign_callback', 'set_afternmv', 'place_object', 'room']), 'uhitm': ([], ['layout_count', 'layout_name', 'layout_value', 'stack', 'trace', 'buffer', 'clear', 'option', 'seed', 'reset', 'object', 'global', 'input', 'action', 'snapshot', 'pointer', 'property', 'scene', 'callback_identity', 'callback_action', 'retained', 'record_prepare', 'record', 'record_pointer', 'record_write']), 'mon': ([], ['aux', 'bit', 'callback', 'clear_trace', 'count', 'extra', 'extra_pointer', 'format_pointer', 'frees', 'gas_glyph', 'grid_mon', 'grid_obj', 'iterator', 'layout_count', 'layout_name', 'layout_value', 'native_return', 'new_mon', 'object', 'option', 'pointer', 'pointer_equal', 'put_object', 'reset', 'return', 'roll', 'run', 'stack', 'tile', 'trace', 'unsigned64']), 'pickup': ([], ['action', 'trace', 'clear', 'draws', 'error', 'errno', 'seed', 'option', 'input', 'answer', 'choice', 'pointer', 'grid', 'region_size', 'count', 'alloc_pointer', 'alloc_size', 'alloc_kind', 'alloc_live', 'growth', 'event_count', 'event_kind', 'newobj', 'floor', 'inventory', 'reset', 'global_size', 'constant', 'identity', 'queue_count', 'queue_identity', 'queue_run', 'literal', 'prefix', 'extra_offset', 'borrow_count', 'borrow_pointer', 'borrow_kind', 'choice2', 'choicewide']), 'shk': ([], ['call', 'reset', 'clear', 'option', 'buffer', 'record', 'trace', 'stack', 'snapshot', 'global', 'layout', 'address', 'write', 'read', 'chain', 'bill', 'shops', 'property', 'function', 'valid', 'invoke']), 'sp_lev': ([], ['lua_prepare', 'sret_sequence', 'invoke_lua', 'selection', 'lua_text', 'lua_int', 'lua_top', 'lua_type', 'lua', 'pool', 'block_count', 'block', 'block_size', 'block_live', 'block_kind', 'selection_map_offset', 'layout_count', 'layout_name', 'layout_value', 'stack', 'trace', 'option', 'action', 'reset', 'string', 'string_count', 'string_capacity', 'data', 'function']), 'trap': ([], ['trace', 'clear', 'option', 'stack', 'buffer', 'object', 'mon_pointer', 'trap', 'trap_live', 'hero', 'level', 'coord', 'global', 'seed', 'catalogue', 'copy_monster', 'setup', 'catalogue_witness', 'layout_count', 'layout_name', 'layout_value', 'data', 'callback', 'trap_consumer', 'trap_obj_consumer', 'enum', 'unsigned_product', 'compound_narrow', 'typed_field', 'typed_get', 'stride', 'native_constant']), 'termcap': ([], ['canonical', 'reset', 'clear_trace', 'option', 'override', 'pointer', 'trace', 'error', 'stack', 'last_output_pointer', 'layout_count', 'layout_name', 'layout_value', 'callback_pointer', 'invoke_callback', 'expected_callback', 'constant']), 'topl': ([], ['layout_count', 'layout_name', 'layout_value', 'stack', 'trace', 'result', 'reset', 'clear', 'input', 'option', 'scene', 'topline', 'history', 'pointer', 'window_identity', 'snapshot', 'action', 'view_write', 'mutate_retained', 'callback_identity', 'callback_action']), 'wintty': ([], ['name', 'menu_item', 'window_set', 'data', 'status_value', 'glyph', 'graphics', 'release', 'startup_catalogue', 'live_catalogue', 'mutate_catalogue', 'more', 'callback_kind', 'layout_count', 'layout_name', 'layout_value', 'stack', 'trace', 'error', 'return', 'buffer', 'ints', 'window', 'display', 'storage', 'shadow', 'input', 'option', 'clear', 'signal', 'pointer_kind', 'snapshot', 'set', 'reset', 'invoke', 'alloc_count', 'alloc_base', 'alloc_size', 'alloc_live'])})


probes.update({name:([],[symbol[len('_probe_'):] for symbol in symbols
                       if symbol.startswith('_probe_') and symbol!='_probe_context_size'])
               for name,symbols in C_SHADOW_EXPORTS.items()})

b_spec=importlib_util.spec_from_file_location('tu137_group_b',root/'nethack-c/wasm/tu-fragments/tu137-group-b/b_probe_support.py')
b_support=importlib_util.module_from_spec(b_spec);b_spec.loader.exec_module(b_support)

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--native-only', action='store_true', help='Build full native APIs for the existing tests')
parser.add_argument('--emscripten-only', action='store_true', help='First-pass C/JS probes; defer native oracle builds')
parser.add_argument('--supplementary-only', action='store_true', help='Historical smaller native scenarios; not the full existing test cases')
parser.add_argument('--only', action='append', choices=probes, help='Rebuild only this TU (repeatable); default rebuilds every registered TU')
options = parser.parse_args()
if options.emscripten_only and (options.native_only or options.supplementary_only):
    parser.error('--emscripten-only cannot be combined with native build modes')
requested = options.only
for port in json.loads((root / 'nethack-c/wasm/tu-ports.json').read_text()):
    name = port['name']
    if requested and name not in requested:
        continue
    if name == 'nhlua' and not options.emscripten_only:
        raise SystemExit('NHLUA native-host oracle is pending; use --emscripten-only for its configured first pass')



    if name in ['hack','uhitm','mon','pickup','shk']:
        if not options.emscripten_only:
            raise SystemExit(name.upper()+' native-host fixture is pending; use --emscripten-only only for configured-C diagnostics')
        group_a_spec=importlib_util.spec_from_file_location('tu137_group_a_builder',root/'scripts/build-tu137-group-a.py')
        group_a=importlib_util.module_from_spec(group_a_spec)
        group_a_spec.loader.exec_module(group_a)
        assert group_a.build_group_a(root,sdk,work,name)
        continue







    if name in ['sp_lev','trap','termcap','topl','wintty']:
        if not options.emscripten_only:
            raise SystemExit(name+' native-host oracle is absent; use --emscripten-only for diagnostic first pass')
        b_support.materialize_fixture_inputs(root,name)
        records=b_support.commands_for(root,name,sdk=sdk)
        for record in records.get('dependencyCommands',[]):
            subprocess.run(record['command'],cwd=record['cwd'],check=True)
        for mode in ['reference','hybrid']:
            record=records[mode];command=record['command']
            expected=b_support.export_arg(name,mode)
            assert [arg for arg in command if arg.startswith('-sEXPORTED_FUNCTIONS=')]==[expected]
            if name=='wintty':b_support.validate_wintty_choice(root,command)
            before=b_support.capture_topl_inputs_before(root,command,mode) if name=='topl' else None
            subprocess.run(command,cwd=record['cwd'],check=True)
            if before is not None:b_support.finish_topl_inputs(root,before)
        if name in ['trap','topl','wintty']:b_support.write_runner_aliases(root,[name])
        continue

    # These full command overrides already contain EXACT mode-specific fixture/support/
    # storage/library/startup/export requirements. Do not append common tu-support.c,
    # original algorithm source, generic native-libc, guessed context/malloc/free or
    # another JS library after this branch. Parent captures fresh command/binary/input/
    # import/storage/startup provenance around the coordinated build.
    # Default TERMCAP only here; explicit variants are commands_for(...,variant=...)
    # with matching export_arg(...,variant=...). Their variant flags/runner switches
    # MUST match. Optional TOPL production record is retained but not built by this loop.



    if name in C_SHADOW_NAMES:
        if not options.emscripten_only or options.native_only or options.supplementary_only:
            raise SystemExit(name+': authoritative native reference fixture is absent; use explicit --emscripten-only diagnostic')
        build_c_shadow_probes(name)
        if name=='unixunix':
            subprocess.run([*node_command,str(root/'scripts/check-unixunix-imports.mjs')],check=True,cwd=root,
                           env={**os.environ,'UNIXUNIX_PROBE_DIR':str(work)})
        continue
    # This explicit route owns both complete modes: generic support/auto source
    # append/automatic malloc/context exports must not also run for these five.

    fields, functions = probes[name]
    # CFGFILES observes actual frees through --wrap=free and its own probe API;
    # its tested fixture does not expose direct malloc/free entrypoints.
    exports = (['_malloc'] if name == 'mkmaze' else [] if name in ['mkobj', 'cfgfiles', 'detect', 'mklev', 'pray', 'dothrow', 'muse', 'dungeon', 'display', 'cmd'] else ['_malloc', '_free']) + ([] if port.get('probeContext') is False else ['_probe_context_size'])
    exports += port.get('probeExtraExports', [])
    exports += ['_probe_' + function for function in functions]
    exports += ['_probe_offset_' + field for field in fields]
    for mode in ['reference', 'hybrid']:
        mode_exports = [entry for entry in exports if not (name == 'mhitu' and mode == 'hybrid' and entry == '_probe_static') and not (name == 'nhlua' and mode == 'reference' and entry.startswith('_teleport_nhlua_'))]
        args = base + ['-sEXPORTED_FUNCTIONS=' + ','.join(mode_exports), root / ('scripts/tu-' + name + '-probe.c')]
        if name in ['files','invent','display']:
            owned_flags=['-O2','-g','-sMEMORY64=1',*defines,'-I'+str(include),
                         '-I'+str(root/'.cache/ncurses-wasm64-build/include'),'-include',root/'nethack-c/wasm/native-terminal.h']
            args += ['-g','-include',root/'nethack-c/wasm/native-terminal.h','-I'+str(root/'.cache/ncurses-wasm64-build/include')]
            if name in ['files','invent']:
                dependencies=['hacklib','strutil']+(['objects','monst','drawing']if name=='invent'else[])
                for dependency in dependencies:
                    obj=work/(name+'-dependency-'+dependency+'.o')
                    subprocess.run(list(map(str,[sdk/'upstream/emscripten/emcc',*owned_flags,'-c',root/('.cache/wasm64-build/tree/src/'+dependency+'.c'),'-o',obj])),check=True)
                    args += [obj]
                args += ['-sSTACK_SIZE=1048576','-sEXPORTED_RUNTIME_METHODS=HEAPU8,FS,stackSave,stackRestore',
                         '-fmacro-prefix-map='+str(root/('scripts/../.cache/wasm64-build/tree/src/'+name+'.c'))+'='+name+'.c']
                if name=='files':args += ['-Wl,--wrap=fcntl','-Wl,--wrap=sscanf']
                else:
                    obj=work/'invent-probe-consumer.o'
                    subprocess.run(list(map(str,[sdk/'upstream/emscripten/emcc',*owned_flags,'-c',root/'nethack-c/wasm/tu-fragments/invent-probe-consumer.c','-o',obj])),check=True)
                    args += [obj]
            else:
                # Separate non-LTO storage and optimized extern-only consumer.
                args += ['-Wl,--wrap=malloc','-Wl,--wrap=free','-sSTACK_SIZE=4194304',
                         '-fmacro-prefix-map='+str(root/'.cache/wasm64-build/tree/src')+'/=',
                         '-sEXPORTED_RUNTIME_METHODS=HEAPU8,stringToUTF8,lengthBytesUTF8,stackSave,stackRestore,stackAlloc,UTF8ToString']
                for part,source in [('support','nethack-c/wasm/tu-fragments/display-support.c'),('consumer','scripts/tu-display-early-reader.c')]+([('storage','nethack-c/wasm/tu-fragments/display-storage.c')]if mode=='hybrid'else[]):
                    obj=work/('display-'+mode+'-'+part+'.o')
                    subprocess.run(list(map(str,[sdk/'upstream/emscripten/emcc',*owned_flags,'-c',root/source,'-o',obj])),check=True)
                    args += [obj]
                args += ['-DHYBRID_DISPLAY=1']if mode=='hybrid'else['-DREFERENCE_DISPLAY=1']
        if name=='cmd':
            cmd_flags=['-O2','-g','-sMEMORY64=1',*defines,'-I'+str(include),'-I'+str(root/'scripts'),'-I'+str(root/'.cache/ncurses-wasm64-build/include'),'-include',root/'nethack-c/wasm/native-terminal.h']
            args += ['-g','-I'+str(root/'scripts'),'-I'+str(root/'.cache/ncurses-wasm64-build/include'),'-include',root/'nethack-c/wasm/native-terminal.h',
                     '-fmacro-prefix-map='+str(root/'scripts')+'/../.cache/wasm64-build/tree/src/=','-Wl,--wrap=free',
                     '-sEXPORTED_RUNTIME_METHODS=HEAPU8,stringToUTF8,lengthBytesUTF8,stackAlloc,stackSave,stackRestore']
            for part,source in [('foreign','nethack-c/wasm/tu-fragments/cmd-fixture-foreign.c')]+([('storage','nethack-c/wasm/tu-fragments/cmd-public-storage.c')]if mode=='hybrid'else[]):
                obj=work/('cmd-'+mode+'-'+part+'.o')
                subprocess.run(list(map(str,[sdk/'upstream/emscripten/emcc',*cmd_flags,'-c',root/source,'-o',obj])),check=True)
                args += [obj]
            if mode=='hybrid':
                args += ['-DHYBRID_CMD=1']
                cmd_fixture_library=work/'cmd-fixture-library.js'
                cmd_lib=(root/port['library']).read_text()
                assert cmd_lib.count('free:(a0)=>_free(pointer(a0))')==1
                cmd_lib=cmd_lib.replace('free:(a0)=>_free(pointer(a0))','free:(a0)=>___wrap_free(pointer(a0))').replace('"alloc", "free"','"alloc", "free", "__wrap_free"')
                cmd_fixture_library.write_text(cmd_lib)
        if name in ['glyphs', 'allmain', 'report', 'pline', 'u_init']:
            args += ['-include', root / 'nethack-c/wasm/native-terminal.h']
        # SDK parity pairs must share the reference terminal/regex ABI.
        sdk_platform_pair = options.emscripten_only and name in ['posixregex', 'ioctl', 'unixtty', 'coloratt']
        if options.emscripten_only and name == 'ioctl':
            # The fixture exercises USE_WIN_IOCTL: expose its SDK header to
            # the original TU as well as the fixture/metadata translation units.
            args += ['-include', 'sys/ioctl.h']
        if mode=='hybrid' and not sdk_platform_pair and name not in ['nhlua', 'do_wear', 'do', 'spell', 'detect', 'teleport', 'mklev', 'polyself', 'wizcmds', 'end', 'dig', 'dokick', 'mkmaze', 'vision', 'restore', 'nhlobj', 'do_name', 'windows', 'cfgfiles', 'topten', 'dogmove', 'glyphs', 'engrave', 'role', 'mthrowu', 'mhitm', 'getpos', 'save', 'allmain', 'report', 'pline', 'u_init', 'monmove', 'timeout', 'potion', 'pray', 'dothrow', 'pager', 'muse', 'dungeon', 'makemon', 'mhitu', 'artifact', 'decl', 'insight', 'read', 'apply', 'eat', 'objnam', 'mkobj', 'files', 'display', 'invent', 'cmd']:
            args+=['-include',root/'nethack-c/wasm/native-terminal.h','--js-library',root/'nethack-c/wasm/native-libc-library.js']
        if name in ['weapon', 'questpgr', 'symbols']:
            args += ['-I' + str(root / '.cache/ncurses-wasm64-build/include')]
        if name in ['windows','cfgfiles']:
            args += ['-include', root / 'nethack-c/wasm/native-terminal.h',
                     '-I' + str(root / '.cache/ncurses-wasm64-build/include')]
        if name in ['restore','nhlobj','do_name','vision']:
            args += ['-I' + str(root / 'nethack-c/wasm'), '-include', 'hack.h',
                     '-include', work / 'tu-source-locations.h']
        if name in ['detect','teleport','mklev']:
            args += ['-g', '-include', root / 'nethack-c/wasm/native-terminal.h',
                     '-I' + str(root / '.cache/ncurses-wasm64-build/include')]
        if name in ['pray','dothrow','pager','muse','dungeon']:
            args += ['-g','-include',root/'nethack-c/wasm/native-terminal.h','-I'+str(root/'.cache/ncurses-wasm64-build/include')]
        if name in ['pray','muse']:
            args += ['-I'+str(root/'scripts'),'-fmacro-prefix-map='+str(root/'scripts')+'/../.cache/wasm64-build/tree/src/=',
                     '-sEXPORTED_RUNTIME_METHODS=HEAPU8,stringToUTF8,lengthBytesUTF8,stackAlloc,stackSave,stackRestore']
            if mode == 'hybrid': args += ['-DHYBRID_'+name.upper()+'=1']
        elif name in ['dothrow','dungeon']:
            args += ['-Wl,--wrap=malloc','-Wl,--wrap=free','-sSTACK_SIZE=4194304',
                     '-fmacro-prefix-map='+str(root/'.cache/wasm64-build/tree/src')+'/=',
                     '-sEXPORTED_RUNTIME_METHODS=HEAPU8,stringToUTF8,lengthBytesUTF8,stackSave,stackRestore,stackAlloc,UTF8ToString',
                     root/('nethack-c/wasm/tu-fragments/'+name+'-support.c')]
            if mode == 'hybrid': args += ['-DHYBRID_'+name.upper()+'=1']
        elif name == 'pager':
            # Compile foreign dependencies and extern-only consumer independently;
            # public JS-initialized storage is hybrid-only and never uses LTO.
            pager_flags=['-O2','-g','-sMEMORY64=1',*defines,'-I'+str(include),
                         '-I'+str(root/'.cache/ncurses-wasm64-build/include'),'-include',root/'nethack-c/wasm/native-terminal.h']
            pager_objects=[]
            for dependency in ['hacklib','drawing','glyphs','strutil']:
                obj=work/('pager-dependency-'+dependency+'.o')
                rename=['-Dmap_glyphinfo=teleport_pager_unused_map_glyphinfo'] if dependency=='glyphs' else []
                subprocess.run(list(map(str,[sdk/'upstream/emscripten/emcc',*pager_flags,*rename,'-c',root/('.cache/wasm64-build/tree/src/'+dependency+'.c'),'-o',obj])),check=True)
                pager_objects.append(obj)
            consumer=work/'pager-probe-consumer.o'
            subprocess.run(list(map(str,[sdk/'upstream/emscripten/emcc',*pager_flags,'-c',root/'nethack-c/wasm/tu-fragments/pager-probe-consumer.c','-o',consumer])),check=True)
            args += [*pager_objects,consumer,'-sSTACK_SIZE=1048576','-sEXPORTED_RUNTIME_METHODS=HEAPU8,FS',
                     '-fmacro-prefix-map='+str(root/'scripts/../.cache/wasm64-build/tree/src/pager.c')+'=pager.c']
            if mode == 'hybrid':
                storage=work/'pager-storage.o'
                subprocess.run(list(map(str,[sdk/'upstream/emscripten/emcc',*pager_flags,'-DTELEPORT_PORT_PAGER_STORAGE','-c',root/'nethack-c/wasm/tu-fragments/pager-storage.c','-o',storage])),check=True)
                args += [storage]
        elif name == 'makemon':
            # Original frozen fixture and original prepared sort algorithm only.
            source_sort = (root/'.cache/wasm64-build/tree/src/hacklib.c').read_text()
            assert source_sort.count('/*=') == 1, 'Review prepared deterministic sort boundary'
            sort_dependency = work/'makemon-sort-dependency.c'
            sort_dependency.write_text(source_sort[:source_sort.index('/*=')])
            args += ['-sSUPPORT_LONGJMP=emscripten', '-I'+str(root/'scripts'),
                     '-ffile-prefix-map='+str(root/'.cache/wasm64-build/tree/src')+'/=',
                     root/'.cache/wasm64-build/tree/src/objects.c',
                     root/'.cache/wasm64-build/tree/src/monst.c', sort_dependency]
        elif name == 'nhlua':
            # Frozen original-C / JS-source fixture and separate no-LTO callback consumer.
            args += ['-g', '-fno-lto', '-sSUPPORT_LONGJMP=emscripten',
                     '-sEXPORTED_RUNTIME_METHODS=HEAPU8,FS',
                     '-include', root/'nethack-c/wasm/native-terminal.h',
                     '-I'+str(root/'scripts'),
                     '-I'+str(root/'nethack-c/wasm/tu-fragments'),
                     '-I'+str(root/'.cache/ncurses-wasm64-build/include'),
                     '-I'+str(root/'.cache/wasm64-build/tree/lib/lua-5.4.8/src'),
                     '-fmacro-prefix-map='+str(root/'scripts')+'/../.cache/wasm64-build/tree/src/=',
                     root/'scripts/tu-nhlua-probe-consumer.c',
                     root/'.cache/wasm64-build/liblua-wasm64.a',
                     '--js-library', root/'nethack-c/wasm/tu-fragments/nhlua-probe-library.js']
            if mode == 'hybrid': args += ['-DHYBRID_NHLUA=1']
        elif name == 'mhitu':
            args += ['-I'+str(root/'scripts'), '-I'+str(root/'.cache/ncurses-wasm64-build/include'),
                     '-fmacro-prefix-map='+str(root/'scripts')+'/../.cache/wasm64-build/tree/src/=',
                     root/'nethack-c/wasm/tu-fragments/mhitu-support.c']
            if mode == 'hybrid': args += ['-DHYBRID_MHITU=1']
        elif name == 'artifact':
            args += ['-include',root/'nethack-c/wasm/native-terminal.h',
                     '-I'+str(root/'scripts'), '-I'+str(root/'.cache/ncurses-wasm64-build/include'),
                     '-fmacro-prefix-map='+str(root/'scripts')+'/../.cache/wasm64-build/tree/src/=']
            if mode == 'hybrid': args += ['-DHYBRID_ARTIFACT=1']
        elif name == 'decl':
            # Separate no-LTO consumer/storage objects are part of the contract.
            decl_defines = json.loads((root/'nethack-c/wasm/compile-defines.json').read_text())
            compile_flags = ['-O2','-fno-lto','-sMEMORY64=1', *['-D'+x for x in decl_defines],
                '-I'+str(root/'.cache/wasm64-build/tree/include'),
                '-I'+str(root/'.cache/ncurses-wasm64-build/include'), '-I'+str(root/'scripts'),
                '-include',str(root/'nethack-c/wasm/native-terminal.h'),
                '-fmacro-prefix-map='+str((root/'scripts/../.cache/wasm64-build/tree/src').resolve())+'/=']
            sources = ['scripts/tu-decl-probe.c','scripts/tu-decl-probe-consumer.c','nethack-c/wasm/tu-fragments/decl-support.c']
            if mode == 'hybrid': sources += ['nethack-c/wasm/tu-fragments/decl-storage.c']
            objects = []
            for i,source in enumerate(sources):
                output = work/('decl-'+mode+'-'+str(i)+'.o')
                command = [str(sdk/'upstream/emscripten/emcc'),*compile_flags,
                    *(['-DHYBRID_DECL=1'] if mode=='hybrid' else []),'-c',str(root/source),'-o',str(output)]
                subprocess.run(command,check=True)
                objects.append(output)
            args = [x for x in args if str(x) != str(root/'scripts/tu-decl-probe.c')]
            args += ['-fno-lto',*objects]
        elif name == 'detect':
            args += ['-I' + str(root / 'scripts'),
                     '-fmacro-prefix-map=' + str(root / 'scripts') + '/../.cache/wasm64-build/tree/src/=',
                     '-sEXPORTED_RUNTIME_METHODS=HEAPU8,stringToUTF8,lengthBytesUTF8,stackAlloc,stackSave,stackRestore']
            if mode == 'hybrid': args += ['-DHYBRID_DETECT=1']
        elif name == 'teleport':
            args += ['-sSTACK_SIZE=1048576', '-fmacro-prefix-map=' + str(root / 'scripts') + '/../.cache/wasm64-build/tree/src/teleport.c=teleport.c']
        elif name == 'mklev':
            sort_dependency = work / 'mklev-deterministic-sort-dependency.c'
            hacklib_text = (root / '.cache/wasm64-build/tree/src/hacklib.c').read_text()
            assert '/*=' in hacklib_text, 'Review genuine deterministic-sort dependency boundary'
            sort_dependency.write_text(hacklib_text[:hacklib_text.index('/*=')])
            args += ['-Wl,--wrap=malloc','-Wl,--wrap=free','-sSTACK_SIZE=4194304',
                     '-fmacro-prefix-map=' + str(root / '.cache/wasm64-build/tree/src') + '/=',
                     '-sEXPORTED_RUNTIME_METHODS=HEAPU8,stringToUTF8,lengthBytesUTF8,stackSave,stackRestore,stackAlloc,UTF8ToString',
                     root / 'nethack-c/wasm/tu-fragments/mklev-support.c', sort_dependency]
            if mode == 'hybrid': args += ['-DHYBRID_MKLEV=1']
        elif name in ['polyself','wizcmds']:
            # Reproduce each frozen original-source fixture and source basename.
            args += ['-I'+str(root/'scripts'), '-I'+str(root/'.cache/ncurses-wasm64-build/include'),
                     '-fmacro-prefix-map='+str(root/'scripts')+'/../.cache/wasm64-build/tree/src/=']
            if name == 'polyself': args += [root/'nethack-c/wasm/tu-fragments/polyself-support.c']
            if mode == 'hybrid': args += ['-DHYBRID_'+name.upper()+'=1']
        elif name == 'end':
            # Match the frozen private fixture; it includes its support once.
            args += ['-I'+str(root/'scripts'), '-I'+str(root/'.cache/ncurses-wasm64-build/include'),
                     '-ffile-prefix-map='+str(root/'.cache/wasm64-build/tree/src')+'/=',
                     '-sSUPPORT_LONGJMP=emscripten']
            args += [root/'.cache/wasm64-build/tree/src'/ (part+'.c') for part in ['objects','monst']]
        elif name == 'potion':
            args += ['-include', root / 'nethack-c/wasm/native-terminal.h',
                     '-I' + str(root / '.cache/ncurses-wasm64-build/include'),
                     '-I' + str(root / '.cache/wasm64-build/tree/src'), '-I' + str(root / 'scripts'),
                     '-ffile-prefix-map=' + str(root / '.cache/wasm64-build/tree/src') + '/=',
                     '-sSTACK_SIZE=1048576', '-sINITIAL_MEMORY=16777216', '-sASSERTIONS=1']
            args += [root / '.cache/wasm64-build/tree/src' / (part + '.c') for part in ['objects','monst','alloc','hacklib']]
            args += [root / 'scripts/tu-potion-command.c']
            if mode == 'hybrid':
                potion_support = work / 'potion-support.c'
                potion_support.write_text('#include "hack.h"\n#include "display.h"\n#include "tu-source-locations.h"\n#include ' + json.dumps(str(root / 'nethack-c/wasm/tu-potion-support.inc')) + '\n')
                args += [potion_support]
        elif name == 'monmove':
            args += ['-include', root / 'nethack-c/wasm/native-terminal.h',
                     '-I' + str(root / '.cache/ncurses-wasm64-build/include'),
                     '-I' + str(root / '.cache/wasm64-build/tree/src'), '-I' + str(root / 'scripts'),
                     '-ffile-prefix-map=' + str(root / '.cache/wasm64-build/tree/src') + '/=',
                     '-sSTACK_SIZE=1048576', '-sINITIAL_MEMORY=16777216', '-sASSERTIONS=1']
            args += [root / '.cache/wasm64-build/tree/src' / (part + '.c') for part in ['objects','monst','alloc','hacklib']]
            args += [root / 'scripts/tu-monmove-command.c']
            if mode == 'hybrid':
                monmove_support = work / 'monmove-support.c'
                monmove_support.write_text('#include "hack.h"\n#include "tu-source-locations.h"\n#include ' + json.dumps(str(root / 'nethack-c/wasm/tu-monmove-support.inc')) + '\n')
                args += [monmove_support]
        elif name == 'dig':
            args += ['-include', root / 'nethack-c/wasm/native-terminal.h', '-I' + str(root / '.cache/ncurses-wasm64-build/include'),
                     '-I' + str(root / '.cache/wasm64-build/tree/src'), '-I' + str(root / 'scripts'),
                     '-ffile-prefix-map=' + str(root / '.cache/wasm64-build/tree/src') + '/=',
                     '-sSTACK_SIZE=1048576', '-sINITIAL_MEMORY=16777216', '-sASSERTIONS=1']
            args += [root / '.cache/wasm64-build/tree/src' / (part + '.c') for part in ['objects','monst','alloc','hacklib','strutil','mondata']]
            args += [root / 'scripts/tu-dig-command.c', root / 'scripts/tu-dig-hack.c']
            if mode == 'hybrid':
                dig_support = work / 'dig-support.c'
                dig_support.write_text('#include "hack.h"\n#include "tu-source-locations.h"\n#include ' + json.dumps(str(root / 'nethack-c/wasm/tu-dig-support.inc')) + '\n')
                args += [dig_support]
        elif name == 'dokick':
            args += ['-include', root / 'nethack-c/wasm/native-terminal.h', '-I' + str(root / '.cache/ncurses-wasm64-build/include'),
                     '-ffile-prefix-map=' + str(root / 'scripts') + '/../nethack-c/upstream/src/=', root / 'nethack-c/wasm/tu-support.c',
                     '-include', work / 'tu-source-locations.h', '-x', 'c', root / 'nethack-c/wasm/tu-dokick-support.inc']
            args += [root / '.cache/wasm64-build/tree/src' / (part + '.c') for part in ['alloc','hacklib','strutil','objects','monst']]
        elif name in ['read','apply']:
            args += ['-ffile-prefix-map='+str(root/'.cache/wasm64-build/tree/src')+'/=',
                     '-sSUPPORT_LONGJMP=emscripten','-I'+str(root/'scripts')]
            args += [root/'.cache/wasm64-build/tree/src'/part for part in ['objects.c','monst.c']]
        elif name == 'eat':
            args += ['-g','-sINITIAL_MEMORY=16777216','-sSTACK_SIZE=1048576','-sASSERTIONS=1',
                     '-ffile-prefix-map='+str(root/'.cache/wasm64-build/tree/src')+'/=',
                     '-I'+str(root/'.cache/wasm64-build/tree/src'),'-I'+str(root/'scripts'),
                     '-I'+str(root/'.cache/ncurses-wasm64-build/include')]
            args += [root/'.cache/wasm64-build/tree/src'/part for part in ['objects.c','monst.c','alloc.c','hacklib.c','strutil.c']]
            args += [root/'scripts/tu-eat-command.c']
            if mode == 'hybrid':
                support=work/'eat-probe-support.c'
                support.write_text('#include "hack.h"\n#include "display.h"\n#include "tu-source-locations.h"\nextern void teleport_eat_fixture_free(void*);\n#define free teleport_eat_fixture_free\n#include '+json.dumps(str(root/'nethack-c/wasm/tu-eat-support.inc'))+'\n')
                args += [support,root/'nethack-c/wasm/tu-eat-storage.c','-DTELEPORT_PORT_EAT_STORAGE']
        elif name == 'objnam':
            args += ['-ffile-prefix-map='+str(root/'scripts/../nethack-c/upstream/src')+'/=',
                     '-I'+str(root/'scripts'),'-I'+str(root/'nethack-c/wasm'),
                     '-I'+str(root/'.cache/ncurses-wasm64-build/include'),
                     '-include',work/'tu-source-locations.h','-x','c',root/'nethack-c/wasm/tu-objnam-support.inc']
            args += [root/'.cache/wasm64-build/tree/src'/part for part in ['alloc.c','hacklib.c','strutil.c','objects.c','monst.c','drawing.c']]
        elif name == 'mkobj':
            args += ['-g','-fmacro-prefix-map='+str(root/'scripts/../.cache/wasm64-build/tree/src')+'/=',
                     '-Wl,--wrap=free','-I'+str(root/'scripts'),
                     '-I'+str(root/'.cache/ncurses-wasm64-build/include'),
                     '-include',root/'nethack-c/wasm/native-terminal.h',
                     '-sEXPORTED_RUNTIME_METHODS=HEAPU8,stringToUTF8,lengthBytesUTF8,stackAlloc,stackSave,stackRestore']
            if mode == 'hybrid':
                fixture_library=work/'mkobj-fixture-library.js'
                library=(root/port['library']).read_text()
                assert library.count('free:(a0)=>_free(pointer(a0))')==1
                assert library.count('"alloc", "free"')==1
                library=library.replace('free:(a0)=>_free(pointer(a0))','free:(a0)=>___wrap_free(pointer(a0))').replace('"alloc", "free"','"alloc", "free", "__wrap_free"')
                fixture_library.write_text(library)
                args += ['-DHYBRID_MKOBJ=1']
        elif name == 'insight':
            args += ['-include', root / 'nethack-c/wasm/native-terminal.h', '-I' + str(root / '.cache/ncurses-wasm64-build/include'),
                     '-ffile-prefix-map=' + str(root / 'scripts') + '/../nethack-c/upstream/src/=',
                     '-include', work / 'tu-source-locations.h', '-x', 'c', root / 'nethack-c/wasm/tu-insight-support.inc']
            args += [root / '.cache/wasm64-build/tree/src' / (part + '.c') for part in ['alloc','hacklib','strutil','objects','monst','drawing']]
            args += ['-DTELEPORT_REFERENCE_OBJECTS','-DTELEPORT_REFERENCE_MONST','-DTELEPORT_REFERENCE_DRAWING']
            if mode == 'reference': args += ['-DTELEPORT_REFERENCE_INSIGHT']

        elif name == 'timeout':
            args += ['-include', root / 'nethack-c/wasm/native-terminal.h', '-I' + str(root / '.cache/ncurses-wasm64-build/include'),
                     '-ffile-prefix-map=' + str(root / 'scripts') + '/../nethack-c/upstream/src/=', root / 'nethack-c/wasm/tu-support.c',
                     '-include', work / 'tu-source-locations.h', '-x', 'c', root / 'nethack-c/wasm/tu-timeout-support.inc']
            args += [root / '.cache/wasm64-build/tree/src' / (part + '.c') for part in ['alloc','hacklib','strutil','objects','monst']]
        elif name == 'spell':
            args += ['-include', root / 'nethack-c/wasm/native-terminal.h', '-I' + str(root / '.cache/ncurses-wasm64-build/include'),
                     '-ffile-prefix-map=' + str(root / 'scripts') + '/../nethack-c/upstream/src/=', root / 'nethack-c/wasm/tu-support.c',
                     '-include', work / 'tu-source-locations.h', '-x', 'c', root / 'nethack-c/wasm/tu-spell-support.inc']
            args += [root / '.cache/wasm64-build/tree/src' / (part + '.c') for part in ['alloc','hacklib','strutil','objects','monst']]
        elif name == 'mkmaze':
            args += ['-include', root / 'nethack-c/wasm/native-terminal.h', '-I' + str(root / '.cache/ncurses-wasm64-build/include'),
                     '-Wl,--wrap=free', '-sSTACK_SIZE=4194304',
                     '-fmacro-prefix-map=' + str(root / '.cache/wasm64-build/tree/src') + '/=',
                     '-sEXPORTED_RUNTIME_METHODS=HEAPU8,stringToUTF8,lengthBytesUTF8,stackSave,stackRestore,stackAlloc,UTF8ToString',
                     root / 'nethack-c/wasm/tu-fragments/mkmaze-support.c']
            if mode == 'hybrid': args += ['-DHYBRID_MKMAZE=1']
        elif name == 'do':
            args += ['-ffile-prefix-map=' + str(root / 'scripts/../.cache/wasm64-build/tree/src') + '/=',
                     '-ffile-prefix-map=' + str(root / '.cache/wasm64-build/tree/src') + '/=',
                     '-x', 'c', root / 'nethack-c/wasm/tu-do-support.inc']
            args += [root / '.cache/wasm64-build/tree/src' / (part + '.c') for part in ['alloc','hacklib','monst','objects','drawing']]
        elif name == 'do_wear':
            args += ['-ffile-prefix-map=' + str(root / 'scripts/../.cache/wasm64-build/tree/src') + '/=',
                     '-ffile-prefix-map=' + str(root / '.cache/wasm64-build/tree/src') + '/=',
                     '-x', 'c', root / 'nethack-c/wasm/tu-do_wear-support.inc', '-Dfree=teleport_probe_free']
            args += [root / '.cache/wasm64-build/tree/src' / (part + '.c') for part in ['alloc','hacklib','monst','objects','drawing']]
        elif name == 'vision':
            args += ['-x', 'c', root / 'nethack-c/wasm/tu-vision-support.inc']
            args += [root / '.cache/wasm64-build/tree/src' / (part + '.c') for part in ['hacklib','monst']]
            if mode == 'hybrid': args += ['-DTELEPORT_PORT_VISION_STORAGE', root / 'nethack-c/wasm/tu-vision-storage.c']
        elif name == 'restore':
            args += ['-Dfree=teleport_probe_free', '-x', 'c',
                     root / 'nethack-c/wasm/tu-restore-support.inc']
            args += [root / '.cache/wasm64-build/tree/src' / (part + '.c') for part in ['hacklib','monst','objects']]
        elif name == 'nhlobj':
            args += ['-I' + str(root / '.cache/ncurses-wasm64-build/include'), '-sSTACK_SIZE=1048576']
            args += [root / '.cache/wasm64-build/tree/src' / (part + '.c') for part in ['objects','monst','alloc','hacklib','strutil','hack','cmd','nhlua','sp_lev','drawing']]
            args += [root / '.cache/wasm64-build/liblua-wasm64.a']
            if mode == 'hybrid': args += ['-x', 'c', root / 'nethack-c/wasm/tu-nhlobj-support.inc']
        elif name == 'do_name':
            args += ['-I' + str(root / '.cache/ncurses-wasm64-build/include'), '-x', 'c',
                     root / 'nethack-c/wasm/tu-do_name-support.inc']
            args += [root / '.cache/wasm64-build/tree/src' / (part + '.c') for part in ['alloc','hacklib','strutil','objects','monst']]
            if mode == 'reference': args += ['-DTELEPORT_REFERENCE_DO_NAME']
        elif name == 'windows':
            args += ['-sSTACK_SIZE=1048576',
                     '-fmacro-prefix-map=' + str(root / 'scripts') + '/../.cache/wasm64-build/tree/src/windows.c=windows.c']
            args += ['-D' + call + '=teleport_probe_' + call for call in ['free','puts','fopen','fgets','fclose','fputs','fprintf']]
            args += [root / '.cache/wasm64-build/tree/src' / (part + '.c') for part in ['drawing','hacklib']]
            args += [root / 'nethack-c/wasm/tu-fragments/windows-probe-consumer.c']
        elif name == 'cfgfiles':
            args += ['-Wl,--wrap=free',
                     '-fmacro-prefix-map=' + str(root / 'scripts') + '/../.cache/wasm64-build/tree/src/=',
                     '-I' + str(root / 'scripts'),
                     '-sEXPORTED_RUNTIME_METHODS=HEAPU8,FS,stringToUTF8,lengthBytesUTF8,stackAlloc,stackSave,stackRestore',
                     root / 'nethack-c/wasm/tu-fragments/cfgfiles-support.c']
            if mode == 'hybrid': args += ['-DHYBRID_CFGFILES=1']
        elif name == 'topten':
            args += ['-Dfree=teleport_probe_free', '-Wl,--wrap=fclose', root / '.cache/wasm64-build/tree/src/hacklib.c', root / 'nethack-c/upstream/src/role.c', root / 'nethack-c/upstream/src/strutil.c']
            if mode == 'hybrid': args += ['-x', 'c', root / 'nethack-c/wasm/tu-fragments/topten-support.inc']
        elif name == 'dogmove':
            args += [root / 'nethack-c/wasm/tu-fragments/dogmove-support.c']
            if mode == 'hybrid': args += ['-DHYBRID_DOGMOVE=1']
        elif name == 'glyphs':
            args += ['-Dfree=teleport_probe_free', '-Dfprintf=teleport_probe_fprintf', '-sSTACK_SIZE=1048576']
            args += [root / '.cache/wasm64-build/tree/src' / (part + '.c') for part in ['utf8map','coloratt','hacklib']]
        elif name == 'engrave':
            args += ['-Dfree=teleport_probe_free', '-I' + str(root / 'nethack-c/wasm'), '-include', work / 'tu-source-locations.h', '-x', 'c', root / 'nethack-c/wasm/tu-engrave-support.inc']
            args += [root / '.cache/wasm64-build/tree/src' / (part + '.c') for part in ['objects','monst','alloc','hacklib','strutil']]
        elif name == 'role':
            args += ['-Dfree=teleport_probe_free', '-I' + str(root / '.cache/ncurses-wasm64-build/include')]
            args += [root / '.cache/wasm64-build/tree/src' / (part + '.c') for part in ['objects','monst','alloc','hacklib','strutil']]
            if mode == 'hybrid':
                args += ['-DTELEPORT_PORT_ROLE_STORAGE', '-include', 'hack.h', '-include', work / 'tu-source-locations.h', '-x', 'c', root / 'nethack-c/wasm/tu-role-support.inc', root / 'nethack-c/wasm/tu-role-storage.c']
        elif name == 'mthrowu':
            args += ['-DNEED_VARARGS', '-x', 'c', root / 'nethack-c/wasm/tu-mthrowu-support.inc']
            args += [root / '.cache/wasm64-build/tree/src' / (part + '.c') for part in ['objects','monst','alloc','hacklib']]
        elif name == 'mhitm':
            args += ['-include', work / 'tu-source-locations.h', '-x', 'c', root / 'nethack-c/wasm/tu-mhitm-support.inc']
            args += [root / '.cache/wasm64-build/tree/src' / (part + '.c') for part in ['objects','monst','alloc','hacklib']]
        elif name == 'getpos':
            args += ['-Dfree=teleport_probe_free', '-Wl,--wrap=nh_deterministic_qsort', root / 'nethack-c/wasm/tu-fragments/getpos-probe-dependencies.c', root / 'nethack-c/upstream/src/glyphs.c']
            if mode == 'hybrid': args += ['-x', 'c', root / 'nethack-c/wasm/tu-fragments/getpos-support.inc']
        elif name == 'allmain':
            pass  # The fixture includes its typed support exactly once.
        elif name == 'save':
            args += [root / 'nethack-c/wasm/tu-fragments/save-support.c']
            if mode == 'hybrid': args += ['-DHYBRID_SAVE=1']
        elif name == 'sounds':
            args += ['-DTELEPORT_REFERENCE_OBJECTS', '-DTELEPORT_REFERENCE_MONST']
            args += [root / '.cache/wasm64-build/tree/src' / (part + '.c') for part in ['objects','monst','alloc','hacklib']]
            args += [root / 'nethack-c/wasm/tu-support.c']
            if mode == 'reference': args += ['-DTELEPORT_REFERENCE_SOUNDS']
        elif name == 'vault':
            args += ['-Dfree=teleport_probe_free']
            if mode == 'hybrid': args += ['-x', 'c', root / 'nethack-c/wasm/tu-fragments/vault-support.inc']
        elif name == 'u_init':
            pass  # Fixture includes its actual object catalogue and ABI support.
        elif name == 'weapon':
            args += ['-DTELEPORT_WEAPON_PROBE', '-DTELEPORT_REFERENCE_OBJECTS', '-DTELEPORT_REFERENCE_MONST', '-DTELEPORT_REFERENCE_DRAWING', '-Dfree=teleport_probe_free']
            args += [root / '.cache/wasm64-build/tree/src' / (part + '.c') for part in ['alloc','hacklib','strutil','objects','monst','drawing']]
            args += [root / 'nethack-c/wasm/tu-support.c']
        elif name == 'region':
            args += ['-DTELEPORT_REFERENCE_MONST', '-Dfree=teleport_probe_free']
            args += [root / '.cache/wasm64-build/tree/src' / (part + '.c') for part in ['alloc','hacklib','monst']]
            args += [root / 'nethack-c/wasm/tu-support.c']
        elif name == 'dog':
            args += ['-DTELEPORT_REFERENCE_OBJECTS', '-DTELEPORT_REFERENCE_MONST', '-Dfree=teleport_probe_free']
            args += [root / '.cache/wasm64-build/tree/src' / (part + '.c') for part in ['objects','monst','alloc','hacklib']]
            args += [root / 'nethack-c/wasm/tu-support.c']
        elif name == 'sfbase':
            args += [root / 'nethack-c/wasm/tu-fragments/sfbase-support.c', root / '.cache/wasm64-build/tree/src/hacklib.c']
            if mode == 'reference': args += ['-DSFBASE_REFERENCE=1']
        elif name == 'attrib':
            if mode == 'hybrid': args += ['-x', 'c', root / 'nethack-c/wasm/tu-fragments/attrib-support.inc']
        elif name == 'pline':
            args += ['-D' + call + '=teleport_probe_' + call for call in ['fork','waitpid','getgid','getuid','setgid','setuid','execv','perror','fprintf','free']]
        elif name == 'mail':
            args += ['-DTELEPORT_MAIL_PROBE', '-DTELEPORT_REFERENCE_MONST', '-Dfree=teleport_probe_free', root / 'nethack-c/wasm/tu-support.c']
            args += [root / '.cache/wasm64-build/tree/src' / (part + '.c') for part in ['alloc','hacklib']]
        elif name == 'questpgr':
            args += ['-DTELEPORT_REFERENCE_MONST', '-Dfree=teleport_probe_free']
            args += [root / '.cache/wasm64-build/tree/src' / (part + '.c') for part in ['monst','alloc','hacklib']]
            args += [root / 'scripts/tu-questpgr-lua.c', root / '.cache/wasm64-build/liblua-wasm64.a', root / 'nethack-c/wasm/tu-support.c']
        elif name == 'symbols':
            args += ['-DTELEPORT_REFERENCE_DRAWING', '-Dmalloc=teleport_probe_malloc', '-Dfree=teleport_probe_free']
            args += [root / '.cache/wasm64-build/tree/src' / (part + '.c') for part in ['alloc','hacklib','strutil','drawing']]
            args += [root / 'nethack-c/wasm/tu-support.c']
            if mode == 'reference': args += ['-DTELEPORT_REFERENCE_SYMBOLS']
        elif name == 'bones':
            args += [root / 'nethack-c/wasm/tu-fragments/bones-support.c']
            if mode == 'hybrid': args += ['-DHYBRID_BONES=1']
        elif name == 'explode':
            if mode == 'hybrid':
                args += ['-x', 'c', root / 'nethack-c/wasm/tu-fragments/explode-support.inc']
        elif name == 'report':
            args += [root / '.cache/wasm64-build/tree/src/nhmd4.c']
            args += ['-D' + call + '=teleport_probe_' + call for call in ['readlink','open','read','write','close','fork','execve','waitpid','signal','exit']]
        elif name == 'earlyarg':
            args += [root / 'nethack-c/upstream/src' / (part + '.c') for part in ['alloc','hacklib']]
            args += [root / 'nethack-c/wasm/tu-support.c', '-Dfree=teleport_probe_free']
            if mode == 'reference':
                args += ['-DTELEPORT_REFERENCE_EARLYARG']
        elif name == 'sfstruct':
            args += [root / 'nethack-c/wasm/tu-support.c']
            args += ['-D' + call + '=teleport_probe_' + call for call in ['read','write','fdopen','fwrite','fflush','fclose','close']]
            if mode == 'reference':
                args += ['-DTELEPORT_REFERENCE_SFSTRUCT']
        elif name == 'mkroom':
            args += ['-DTELEPORT_REFERENCE_DRAWING', '-DTELEPORT_REFERENCE_SHKNAM']
            args += [root / 'nethack-c/upstream/src' / (part + '.c') for part in ['objects','monst','alloc']]
            args += [root / '.cache/wasm64-build/tree/src/hacklib.c', root / 'nethack-c/wasm/tu-support.c']
        elif name == 'hacklib':
            args += [root / 'nethack-c/wasm/tu-support.c', '-sEXPORTED_RUNTIME_METHODS=HEAPU8,FS']
            args += ['-D' + call + '=teleport_probe_' + call for call in ['malloc', 'free', 'read', 'write']]
        elif name in ['objects', 'monst']:
            args += [root / 'nethack-c/wasm/tu-support.c']
        elif name == 'sit':
            args += [root / 'nethack-c/upstream/src/objects.c', root / 'nethack-c/upstream/src/monst.c', root / 'nethack-c/upstream/src/alloc.c', root / 'nethack-c/upstream/src/hacklib.c', root / 'nethack-c/upstream/src/drawing.c', root / 'nethack-c/wasm/tu-support.c', '-DTELEPORT_REFERENCE_DRAWING']
        elif name == 'coloratt':
            args += [root / 'nethack-c/upstream/sys/share/posixregex.c', root / 'nethack-c/upstream/src/alloc.c', root / 'nethack-c/upstream/src/hacklib.c', root / 'nethack-c/wasm/tu-support.c', '-DTELEPORT_REFERENCE_POSIXREGEX', '-Dfree=teleport_probe_free']
            if mode == 'hybrid':
                args = [arg for arg in args if arg != root / 'nethack-c/upstream/sys/share/posixregex.c' and arg != '-DTELEPORT_REFERENCE_POSIXREGEX']
                args += ['--js-library', root / 'nethack-c/wasm/tu-libraries/posixregex.js',
                         '-sDEFAULT_LIBRARY_FUNCS_TO_INCLUDE=$teleportPosixregexInit']
            if mode == 'reference':
                args += ['-DTELEPORT_REFERENCE_COLORATT']
        elif name == 'version':
            args += [root / 'nethack-c/upstream/src/alloc.c', root / 'nethack-c/upstream/src/hacklib.c', root / 'nethack-c/wasm/tu-support.c', '-Wl,--wrap=datamodel']
            if mode == 'reference':
                args += ['-DTELEPORT_REFERENCE_VERSION']
        elif name in ['steal', 'fountain', 'shknam', 'rumors', 'music', 'priest', 'light', 'lock', 'steed', 'worm', 'ball', 'mcastu', 'dbridge']:
            args += [root / 'nethack-c/upstream/src/objects.c', root / 'nethack-c/upstream/src/monst.c', root / 'nethack-c/upstream/src/alloc.c', root / 'nethack-c/upstream/src/hacklib.c', root / 'nethack-c/wasm/tu-support.c']
        elif name in ['worn', 'wield']:
            # Retain actual original shape predicates without replacing the
            # fixture's controlled world callbacks with other mondata bodies.
            shape_dependencies = work / 'worn-mondata-deps.c'
            shape_dependencies.write_text(''.join('#define ' + name + ' teleport_unused_worn_' + name + '\n'
                for name in ['cvt_prop_to_mseenres', 'monstunseesu', 'pronoun_gender', 'raceptr'])
                + '#include ' + json.dumps(str(root / 'nethack-c/upstream/src/mondata.c')) + '\n')
            args += [root / 'nethack-c/upstream/src' / (part + '.c') for part in ['objects', 'monst', 'alloc']]
            args += [shape_dependencies, root / '.cache/wasm64-build/tree/src/hacklib.c', root / 'nethack-c/wasm/tu-support.c', '-DTELEPORT_REFERENCE_MONDATA']
            if name == 'wield':
                args += [root / 'nethack-c/upstream/src/worn.c']
        elif name == 'o_init':
            args += [root / 'nethack-c/upstream/src' / (part + '.c') for part in ['objects', 'monst', 'alloc', 'strutil', 'drawing']]
            args += [root / '.cache/wasm64-build/tree/src/hacklib.c', root / 'nethack-c/wasm/tu-support.c', '-DTELEPORT_REFERENCE_DRAWING', '-Wl,--wrap=nh_deterministic_qsort']
        elif name == 'mondata':
            args += [root / 'nethack-c/upstream/src' / (part + '.c') for part in ['objects', 'monst', 'alloc', 'hacklib', 'drawing']]
            args += [root / 'nethack-c/wasm/tu-support.c', '-DTELEPORT_REFERENCE_DRAWING']
        elif name == 'wizard':
            args += [root / 'nethack-c/upstream/src' / (part + '.c') for part in ['objects', 'monst', 'alloc', 'hacklib', 'drawing', 'stairs']]
            args += [root / 'nethack-c/wasm/tu-support.c', '-DTELEPORT_REFERENCE_DRAWING']
        elif name == 'selvar':
            args += [root / 'nethack-c/upstream/src/alloc.c', root / 'nethack-c/upstream/src/hacklib.c', root / 'nethack-c/wasm/tu-support.c']
        elif name == 'iactions':
            args += [root / 'nethack-c/upstream/src/monst.c', root / 'nethack-c/upstream/src/objects.c', root / 'nethack-c/upstream/src/alloc.c', root / 'nethack-c/upstream/src/hacklib.c', root / 'nethack-c/wasm/tu-support.c', '-Dfree=teleport_probe_free', '-D__assert_fail=teleport_probe_assert_fail']
        elif name == 'minion':
            args += [root / 'nethack-c/upstream/src/monst.c', root / 'nethack-c/upstream/src/objects.c', root / 'nethack-c/upstream/src/alloc.c', root / 'nethack-c/upstream/src/hacklib.c', root / 'nethack-c/wasm/tu-support.c']
        elif name == 'quest':
            args += [root / 'nethack-c/upstream/src/monst.c', root / 'nethack-c/upstream/src/alloc.c', root / 'nethack-c/upstream/src/hacklib.c', root / 'nethack-c/wasm/tu-support.c']
        elif name == 'mdlib':
            native_strings = work / 'mdlib-native-strings.c'
            native_strings.write_text('#define nh_snprintf teleport_unused_nh_snprintf\n#include ' + json.dumps(str(root / 'nethack-c/upstream/src/hacklib.c')) + '\n')
            args += [root / 'nethack-c/upstream/src/alloc.c', native_strings, root / 'nethack-c/wasm/tu-support.c']
        elif name == 'write':
            args += [root / 'nethack-c/upstream/src/monst.c', root / 'nethack-c/upstream/src/objects.c', root / 'nethack-c/upstream/src/alloc.c', root / 'nethack-c/upstream/src/hacklib.c', root / 'nethack-c/wasm/tu-support.c']
        elif name == 'getline':
            args += [root / 'nethack-c/upstream/src/alloc.c', root / 'nethack-c/upstream/src/hacklib.c', root / 'nethack-c/wasm/tu-support.c', '-I' + str(root / '.cache/ncurses-wasm64-build/include'), '-Dfflush=teleport_probe_fflush']
        elif name == 'mkmap':
            args += [root / 'nethack-c/upstream/src/alloc.c', root / 'nethack-c/upstream/src/hacklib.c', root / 'nethack-c/wasm/tu-support.c']
        elif name == 'exper':
            args += [root / 'nethack-c/upstream/src/monst.c', root / 'nethack-c/wasm/tu-support.c', '-D__assert_fail=teleport_probe_assert_fail']
        elif name == 'mplayer':
            args += [root / 'nethack-c/upstream/src/monst.c', root / 'nethack-c/upstream/src/objects.c', root / 'nethack-c/wasm/tu-support.c']
        elif name == 'extralev':
            args += [root / 'nethack-c/upstream/src/monst.c', root / 'nethack-c/wasm/tu-support.c']
        elif name == 'were':
            native_names = work / 'were-native-names.c'
            native_names.write_text('#define Monnam teleport_unused_full_Monnam\n#include ' + json.dumps(str(root / 'nethack-c/upstream/src/do_name.c')) + '\n')
            args += [native_names, root / 'nethack-c/upstream/src/monst.c', root / 'nethack-c/upstream/src/alloc.c', root / 'nethack-c/upstream/src/hacklib.c', root / 'nethack-c/wasm/tu-support.c']
        elif name == 'unixtty':
            args += [root / 'nethack-c/wasm/tu-support.c', '-I' + str(root / '.cache/ncurses-wasm64-build/include')]
            args += ['-D' + call + '=teleport_probe_' + call for call in ['tcgetattr', 'tcsetattr', 'cfgetospeed', 'fpathconf', 'perror', 'vprintf', 'putchar', 'exit']]
        elif name == 'ioctl':
            args += [root / 'nethack-c/wasm/tu-support.c', '-Dtcgetattr=teleport_probe_tcgetattr', '-Dtcsetattr=teleport_probe_tcsetattr', '-Dsignal=teleport_probe_signal', '-Dkill=teleport_probe_kill','-Dioctl=teleport_probe_ioctl']
        elif name == 'rnd':
            args += [root / 'nethack-c/upstream/src/hacklib.c', root / 'nethack-c/wasm/tu-support.c', '-sEXPORTED_RUNTIME_METHODS=HEAPU8,FS']
            if mode == 'reference':
                args += [root / 'nethack-c/upstream/src/isaac64.c']
        elif name == 'drawing':
            args += [root / 'nethack-c/wasm/tu-support.c']
        elif name == 'alloc':
            args += [root / 'nethack-c/wasm/tu-support.c', '-Dmalloc=teleport_probe_malloc', '-Drealloc=teleport_probe_realloc']
        elif name == 'strutil':
            args += [root / 'nethack-c/upstream/src/alloc.c', root / 'nethack-c/upstream/src/hacklib.c',
                     root / 'nethack-c/wasm/tu-support.c']
        elif name == 'rect':
            args += [root / 'nethack-c/upstream/src/alloc.c', root / 'nethack-c/wasm/tu-support.c']
        elif name == 'track':
            args += [root / 'nethack-c/upstream/src/hacklib.c', root / 'nethack-c/wasm/tu-support.c']
        elif name in ['calendar', 'date']:
            args += [root / 'nethack-c/upstream/src/options.c', root / 'nethack-c/upstream/src/hacklib.c', root / 'nethack-c/upstream/src/alloc.c', root / 'nethack-c/wasm/tu-support.c']
        elif name in ['stairs', 'sys', 'rip', 'utf8map', 'posixregex']:
            args += [root / 'nethack-c/upstream/src/alloc.c', root / 'nethack-c/upstream/src/hacklib.c', root / 'nethack-c/wasm/tu-support.c']
        if any(isinstance(arg, Path) and arg.name == 'objects.c' for arg in args) or (name == 'objects' and mode == 'reference'):
            args += ['-DTELEPORT_REFERENCE_OBJECTS']
        if any(isinstance(arg, Path) and arg.name == 'monst.c' for arg in args) or (name == 'monst' and mode == 'reference'):
            args += ['-DTELEPORT_REFERENCE_MONST']
        if name == 'sounds':
            # The fixture supplies sysopt in both modes; suppress common backing.
            args += ['-DTELEPORT_REFERENCE_SYS']
        if name in ['priest', 'light', 'worm', 'o_init']:
            args += ['-Dfree=teleport_probe_free']
        if name == 'shknam':
            args += ['-Dfree=teleport_probe_free']
            if mode == 'reference':
                args += ['-DTELEPORT_REFERENCE_SHKNAM']
        if name == 'rumors':
            args += ['-D' + call + '=teleport_probe_' + call for call in ['fopen', 'fclose', 'fseek', 'fgets', 'ftell', 'free']]
        if mode == 'reference':
            if name == 'sys':
                args += ['-DTELEPORT_REFERENCE_SYS']
            if name == 'getline':
                args += ['-DTELEPORT_REFERENCE_GETLINE']
            if name == 'unixtty':
                args += ['-DTELEPORT_REFERENCE_UNIXTTY']
            if name == 'ioctl':
                args += ['-DTELEPORT_REFERENCE_IOCTL']
            if name == 'date':
                args += ['-DTELEPORT_REFERENCE_DATE']
            if name == 'drawing':
                args += ['-DTELEPORT_REFERENCE_DRAWING']
            if name == 'posixregex':
                args += ['-DTELEPORT_REFERENCE_POSIXREGEX']
            if name in ['nhlua', 'do_wear', 'do', 'spell', 'detect', 'teleport', 'mklev', 'polyself', 'wizcmds', 'end', 'dig', 'dokick', 'mkmaze', 'vision', 'restore', 'nhlobj', 'do_name', 'windows', 'cfgfiles', 'topten', 'dogmove', 'glyphs', 'engrave', 'role', 'mthrowu', 'mhitm', 'getpos', 'allmain', 'save', 'sounds', 'vault', 'u_init', 'weapon', 'region', 'dog', 'attrib', 'pline', 'mail', 'questpgr', 'symbols', 'bones', 'explode', 'report', 'earlyarg', 'mkroom', 'sfstruct', 'rect', 'track', 'posixregex', 'rnd', 'unixtty', 'extralev', 'mplayer', 'exper', 'mkmap', 'getline', 'write', 'mdlib', 'quest', 'minion', 'iactions', 'selvar', 'steal', 'sit', 'fountain', 'shknam', 'rumors', 'music', 'version', 'coloratt', 'priest', 'light', 'lock', 'steed', 'wizard', 'worm', 'o_init', 'ball', 'mcastu', 'dbridge', 'mondata', 'hacklib', 'worn', 'wield', 'monmove', 'timeout', 'potion', 'pray', 'dothrow', 'pager', 'muse', 'dungeon', 'makemon', 'mhitu', 'artifact', 'decl', 'insight', 'read', 'apply', 'eat', 'objnam', 'mkobj', 'files', 'display', 'invent', 'cmd']:
                args += ['-DTELEPORT_REFERENCE_TU']
            else:
                source_tree = root / ('.cache/wasm64-build/tree' if port.get('reference') == 'prepared' else 'nethack-c/upstream')
                args += [source_tree / port['source']]
        else:
            args += ['--js-library', cmd_fixture_library if name=='cmd' else (fixture_library if name=='mkobj' else root / port['library'])]
            if port.get('startup'):
                startups=[port['startup']]
                if name == 'coloratt':startups.append('$teleportPosixregexInit')
                args += ['-sDEFAULT_LIBRARY_FUNCS_TO_INCLUDE=' + json.dumps(startups)]
        if not options.native_only and not options.supplementary_only:
            subprocess.run(list(map(str, args + ['-o', work / (name + '-' + mode + '.mjs')])), check=True,
                           env={**os.environ, 'SOURCE_DATE_EPOCH': '1777723200'} if name == 'date' else None)
        if options.supplementary_only:
            build_oracle(root, work, name, mode, args)
        elif mode == 'reference' and not options.emscripten_only:
            addon_builder.build(name, args)

    if name in ['end','makemon','read','apply'] and not options.native_only and not options.supplementary_only:
        # Frozen END runner accepts a directory containing reference/hybrid.mjs.
        wrappers=work/name;wrappers.mkdir(exist_ok=True)
        for mode in ['reference','hybrid']:
            (wrappers/(mode+'.mjs')).write_text("export {default} from '../"+name+"-"+mode+".mjs';\n")

        if name in ['read','apply']:
            inputs=['inventory.json'] if name=='read' else ['functions.json','callback-witnesses.json','record-projections.json']
            for filename in inputs:
                (wrappers/filename).write_bytes((root/'.cache'/(name+'-author')/filename).read_bytes())

    print('Built Emscripten C and C→JS' if options.emscripten_only else
          'Built Emscripten C, C→JS and native', name, 'probes.')
