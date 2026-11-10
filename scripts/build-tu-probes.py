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
    if (root / 'js/ported/hacklib.js').exists():
        subprocess.run([*node_command, str(root / 'scripts/check-hacklib-data.mjs')], check=True)
    if (root / 'js/ported/wield.js').exists():
        subprocess.run([*node_command, str(root / 'scripts/check-wield-data.mjs')], check=True)
    if (root / 'js/ported/worn.js').exists():
        subprocess.run([*node_command, str(root / 'scripts/check-worn-data.mjs')], check=True)

defines = ['-D' + name for name in json.loads((root / 'nethack-c/wasm/compile-defines.json').read_text())]
base = [sdk / 'upstream/emscripten/emcc', '-O2', '-sMEMORY64=1', '-sMODULARIZE=1', *defines,
        '-sENVIRONMENT=node,web', '-sALLOW_MEMORY_GROWTH=1', '--no-entry',
        '-sEXPORTED_RUNTIME_METHODS=HEAPU8', '-I' + str(include), '-I' + str(work)]
probes = {
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
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--native-only', action='store_true', help='Build full native APIs for the existing tests')
parser.add_argument('--supplementary-only', action='store_true', help='Historical smaller native scenarios; not the full existing test cases')
parser.add_argument('--only', action='append', choices=probes, help='Rebuild only this TU (repeatable); default rebuilds every registered TU')
options = parser.parse_args()
requested = options.only
for port in json.loads((root / 'nethack-c/wasm/tu-ports.json').read_text()):
    name = port['name']
    if requested and name not in requested:
        continue
    fields, functions = probes[name]
    exports = ['_malloc', '_free', '_probe_context_size']
    exports += ['_probe_' + function for function in functions]
    exports += ['_probe_offset_' + field for field in fields]
    for mode in ['reference', 'hybrid']:
        args = base + ['-sEXPORTED_FUNCTIONS=' + ','.join(exports), root / ('scripts/tu-' + name + '-probe.c')]
        if mode=='hybrid':
            args+=['-include',root/'nethack-c/wasm/native-terminal.h','--js-library',root/'nethack-c/wasm/native-libc-library.js']
        if name == 'hacklib':
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
            if name in ['rect', 'track', 'posixregex', 'rnd', 'unixtty', 'extralev', 'mplayer', 'exper', 'mkmap', 'getline', 'write', 'mdlib', 'quest', 'minion', 'iactions', 'selvar', 'steal', 'sit', 'fountain', 'shknam', 'rumors', 'music', 'version', 'coloratt', 'priest', 'light', 'lock', 'steed', 'wizard', 'worm', 'o_init', 'ball', 'mcastu', 'dbridge', 'mondata', 'hacklib', 'worn', 'wield']:
                args += ['-DTELEPORT_REFERENCE_TU']
            else:
                source_tree = root / ('.cache/wasm64-build/tree' if port.get('reference') == 'prepared' else 'nethack-c/upstream')
                args += [source_tree / port['source']]
        else:
            args += ['--js-library', root / port['library']]
            if name == 'o_init':
                native_sort = work / 'native-sort-hacklib.c'
                native_sort.write_text('#define qsort teleport_native_c_qsort\n#include ' + json.dumps(str(root / '.cache/wasm64-build/tree/src/hacklib.c')) + '\n')
                args = [native_sort if arg == root / '.cache/wasm64-build/tree/src/hacklib.c' else arg for arg in args]
            if port.get('startup'):
                startups=[port['startup']]
                if name == 'coloratt':startups.append('$teleportPosixregexInit')
                args += ['-sDEFAULT_LIBRARY_FUNCS_TO_INCLUDE=' + json.dumps(startups)]
        if not options.native_only and not options.supplementary_only:
            subprocess.run(list(map(str, args + ['-o', work / (name + '-' + mode + '.mjs')])), check=True,
                           env={**os.environ, 'SOURCE_DATE_EPOCH': '1777723200'} if name == 'date' else None)
        if options.supplementary_only:
            build_oracle(root, work, name, mode, args)
        elif mode == 'reference':
            addon_builder.build(name, args)

    print('Built Emscripten C, C→JS and native', name, 'probes.')
