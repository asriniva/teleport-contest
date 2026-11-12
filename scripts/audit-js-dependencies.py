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
SOURCE_MOVES = json.loads((ROOT / 'docs/runtime-environment/services-layout-map.json').read_text())['moves']


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


def source_integrity(hashes):
    result = []
    for path, expected in sorted(hashes.items()):
        current = SOURCE_MOVES.get(path, path)
        artifact(ROOT / current)
        observed = READS.get(current, {}).get('sha256')
        result.append({'path': path, 'current_source_path': current, 'manifest_sha256': expected,
                       'observed_sha256': observed, 'matches': observed == expected})
    return result


def declared_manifest_sources(manifest):
    """Collect the selected artifact provenance scope, including JS-only inputs."""
    hashes = {}

    def add(path, digest):
        value = Path(path)
        if value.is_absolute() or '..' in value.parts:
            raise ValueError('Invalid declared source path: ' + path)
        if path in hashes and hashes[path] != digest:
            raise ValueError('Conflicting declared source hashes: ' + path)
        hashes[path] = digest

    def collect(value):
        if isinstance(value, dict):
            for key, child in value.items():
                if key in ['sourceSha256', 'adapterSourceSha256', 'javascriptDataSha256',
                           'nativeStorageSourceSha256'] and isinstance(child, dict):
                    for path, digest in child.items():
                        add(path, digest)
                else:
                    collect(child)
        elif isinstance(value, list):
            for child in value:
                collect(child)

    collect(manifest)
    for field, path in {
        'nativeAbiSha256': 'nethack-c/wasm/native-terminal.h',
        'ncursesSha256': '.cache/ncurses-6.5.tar.gz',
        'terminfoEntrySha256': 'nethack-c/wasm/terminfo/x/xterm-256color',
        'compressionSourceSha256': 'nethack-c/wasm/vendor/ncompress/compress.c',
    }.items():
        if field in manifest:
            add(path, manifest[field])
    for port in manifest.get('javascriptTranslationUnits', []):
        add(port['javascript'], port['sha256'])
        add(port['library'], port['abiLibrarySha256'])
        add('.cache/wasm64-build/tree/' + port['source'], port['preparedCSourceSha256'])
    if manifest.get('wasmSha256'):
        add('js/wasm/nethack.wasm', manifest['wasmSha256'])
    return hashes


def private_lua_evidence(directory='.cache/js-lua-game-automatic', historical=True):
    """Recorded frozen candidate evidence, never an attestation of current JS."""
    base = ROOT / directory
    manifest_path = base / 'build.json'
    if not manifest_path.is_file():
        return {'available': False, 'path': relative(base)}
    manifest = json.loads(read(manifest_path))
    artifact(base / 'nethack.wasm')
    snapshot = manifest.get('luaSnapshot', '')
    prefix = snapshot.rstrip('/') + '/'
    hashes = {path: value for path, value in manifest.get('inputSha256', {}).items()
              if snapshot and path.startswith(prefix)}
    frozen = source_integrity(hashes)
    current = []
    for entry in frozen:
        path = entry['path'][len(prefix):]
        artifact(ROOT / path)
        observed = READS.get(path, {}).get('sha256')
        current.append({'path': path, 'snapshot_sha256': entry['manifest_sha256'],
                        'current_sha256': observed, 'matches_snapshot': observed == entry['manifest_sha256']})
    summaries, raw_summaries = {}, {}
    for key, name in [('public', 'public-summary.json'), ('all_levels', 'all-level-tests/summary.json'),
                      ('wizard', 'wizard-tests/summary.json')]:
        path = base / name
        if not path.is_file():
            summaries[key] = {'available': False, 'path': relative(path)}
            continue
        data = json.loads(read(path))
        raw_summaries[key] = data
        groups = data.get('groups', [])
        summaries[key] = {'available': True, 'path': relative(path),
                          'sha256': READS[relative(path)]['sha256'],
                          **{k: data[k] for k in ('passed', 'total', 'metrics', 'errors') if k in data}}
        if groups:
            summaries[key].update(group_count=len(groups),
                                  script_loads=sum(len(group.get('files', [])) for group in groups),
                                  unique_script_count=len({f for group in groups for f in group.get('files', [])}),
                                  seeds=sorted({group['seed'] for group in groups}),
                                  screens=sum(group.get('screens', 0) for group in groups),
                                  rng=sum(group.get('rng', 0) for group in groups),
                                  animation_frames=sum(group.get('animationFrames', 0) for group in groups),
                                  groups=groups)
    result = {'available': True, 'path': relative(base), 'status': manifest.get('status'),
            'historical_candidate': historical,
            'manifest_sha256': READS[relative(manifest_path)]['sha256'],
            'manifest_wasm_sha256': manifest.get('wasmSha256'),
            'wasm_matches_manifest': READS.get(relative(base / 'nethack.wasm'), {}).get('sha256') == manifest.get('wasmSha256'),
            'removed_link_inputs': manifest.get('removedLinkInputs', []),
            'snapshot': snapshot, 'frozen_source_integrity': frozen,
            'current_sources_compared_with_frozen_snapshot': current,
            'recorded_validation': summaries,
            'scope_limit': 'Recorded private results, not rerun by this audit and not evidence for a different selected game binary. Adjacent build/summary files are hashed independently. Newer current sources are not covered when their hashes differ from the frozen snapshot.'}
    acceptance_path = base / 'acceptance.json'
    if acceptance_path.is_file():
        acceptance = json.loads(read(acceptance_path))
        freeze_path = ROOT / snapshot / 'manifest.json'
        freeze = json.loads(read(freeze_path)) if freeze_path.is_file() else {}
        production = freeze.get('productionSha256', {})
        overlay = source_integrity({relative(base / 'snapshot' / path): value
                                    for path, value in production.items()})
        dependency_log = ROOT / '.cache/js-dependencies-final.log'
        if not historical and dependency_log.is_file():
            artifact(dependency_log)
        result['acceptance'] = {
            'path': relative(acceptance_path), 'sha256': READS[relative(acceptance_path)]['sha256'],
            'recorded': acceptance,
            'wasm_matches_candidate_manifest': acceptance.get('wasmSha256') == manifest.get('wasmSha256'),
            'wasm_matches_candidate_artifact': acceptance.get('wasmSha256') == READS.get(relative(base / 'nethack.wasm'), {}).get('sha256'),
            'freeze_manifest_matches_acceptance': bool(freeze) and acceptance.get('freezeManifestSha256') == READS.get(relative(freeze_path), {}).get('sha256'),
            'public_metrics_match_summary': acceptance.get('public') == raw_summaries.get('public'),
            'level_totals_match_summary': acceptance.get('levelSweep') == {
                'groups': summaries.get('all_levels', {}).get('group_count'),
                'loads': summaries.get('all_levels', {}).get('script_loads'),
                'seeds': len(summaries.get('all_levels', {}).get('seeds', [])),
                'screens': summaries.get('all_levels', {}).get('screens'),
                'rng': summaries.get('all_levels', {}).get('rng'),
                'animationFrames': summaries.get('all_levels', {}).get('animation_frames')},
            'wizard_groups_match_summary': acceptance.get('wizardGroups') == summaries.get('wizard', {}).get('group_count'),
            'production_overlay_integrity': overlay,
            'all_production_overlay_hashes_match': bool(overlay) and all(entry['matches'] for entry in overlay),
            'dependency_suite_log': ({'path': relative(dependency_log), **READS[relative(dependency_log)]}
                                     if not historical and dependency_log.is_file() else None),
            'scope_limit': 'Acceptance is owner-recorded evidence tied here to the private Wasm, freeze manifest, overlay and recorded summaries. This audit does not rerun the acceptance gates or transfer their result to a newly linked production artifact.'}
    return result


def lua_differential_summaries():
    """Record local test outputs without treating them as a source-bound run."""
    summaries = []
    for name, directory, script in [
        ('auxiliary_errors', 'js-lua-aux-memory', 'test-js-lua-aux-memory.mjs'),
        ('format_buffer', 'js-lua-format-memory', 'test-js-lua-format-memory.mjs'),
        ('utf8_buffer', 'js-lua-utf8-memory', 'test-js-lua-utf8-memory.mjs'),
        ('format_utf8_diagnostics', 'js-lua-format-utf8-errors', 'test-js-lua-format-utf8-errors.mjs'),
        ('pack_os_buffer_and_diagnostics', 'js-lua-pack-os-memory', 'test-js-lua-pack-os-memory.mjs'),
        ('retained_string_table_consumers', 'js-dependency-lua/consumer-memory', 'test-js-lua-consumer-memory.mjs'),
        ('retained_string_table_consumer_diagnostics', 'js-dependency-lua/consumer-memory-errors', 'test-js-lua-consumer-memory.mjs'),
        ('reader_callbacks', 'js-lua-debug/reader-runtime', 'test-js-lua-reader-runtime.mjs'),
        ('sort_stack_and_diagnostics', 'js-lua-sort-memory', 'test-js-lua-sort-memory.mjs'),
    ]:
        path = ROOT / '.cache' / directory / 'summary.json'
        entry = {'name': name, 'test': evidence('scripts/' + script),
                 'path': relative(path), 'available': path.is_file()}
        if path.is_file():
            data = json.loads(read(path))
            entry.update(sha256=READS[relative(path)]['sha256'],
                         case_count=len(data.get('cases', [])),
                         allocation_refusal_schedules=data.get('refusals'),
                         cases=data.get('cases', []))
            if 'diagnosticFailures' in data:
                entry['diagnostic_failures'] = data['diagnosticFailures']
        summaries.append(entry)
    return {'summaries': summaries,
            'scope_limit': 'Local recorded summaries are not executed by this audit and do not contain a complete source-hash binding. Case filters and success-only diagnostic runs can replace them. Inspect case/refusal counts and rerun the exact final source snapshot; these files are separate from whole-game candidate evidence.'}


def lua_core_freeze_evidence():
    path = ROOT / '.cache/js-dependency-lua/core-freeze-manifest.json'
    if not path.is_file():
        return {'available': False, 'path': relative(path)}
    data = json.loads(read(path))
    integrity = source_integrity({entry['path']: entry['sha256'] for entry in data.get('files', [])})
    return {'available': True, 'path': relative(path),
            'sha256': READS[relative(path)]['sha256'],
            'milestone': data.get('milestone'), 'scope': data.get('scope'),
            'recorded_verification': data.get('verification'),
            'source_integrity': integrity,
            'all_listed_sources_match': bool(integrity) and all(entry['matches'] for entry in integrity),
            'scope_limit': 'Owner-recorded scoped verification with listed source/test hashes, not a fresh audit test run. This is not the complete final VM/library/ABI source snapshot or whole-game validation.'}


def lua_incremental_freeze_evidence():
    path = ROOT / '.cache/js-lua-debug/incremental-freeze.json'
    if not path.is_file():
        return {'available': False, 'path': relative(path)}
    data = json.loads(read(path))
    files = data.get('ownedFiles', []) + data.get('coordinatedDependencies', [])
    integrity = source_integrity({entry['path']: entry['sha256'] for entry in files})
    return {'available': True, 'path': relative(path), 'sha256': READS[relative(path)]['sha256'],
            'status': data.get('status'), 'recorded_gates': data.get('gates'), 'scope': data.get('scope'),
            'source_integrity': integrity,
            'all_listed_sources_match': bool(integrity) and all(entry['matches'] for entry in integrity),
            'scope_limit': 'Owner-recorded compiler/VM/base/debug verification and listed source/test hashes; not a fresh audit run or whole-game acceptance.'}


def lua_aggregate_freeze_evidence():
    base = ROOT / '.cache/js-lua-final-freeze'
    path = base / 'manifest.json'
    if not path.is_file():
        return {'available': False, 'path': relative(path)}
    data = json.loads(read(path))
    hashes = data.get('sourceSha256', {})
    current = source_integrity(hashes)
    frozen = source_integrity({relative(base / name): value for name, value in hashes.items()})
    return {'available': True, 'path': relative(path), 'sha256': READS[relative(path)]['sha256'],
            'status': data.get('status'), 'base_root': data.get('baseRoot'),
            'production_count': len(data.get('productionSha256', {})),
            'production_paths': sorted(data.get('productionSha256', {})),
            'test_count': len(data.get('testSha256', {})), 'total_count': len(hashes),
            'current_source_integrity': current, 'frozen_source_integrity': frozen,
            'all_current_sources_match': bool(current) and all(entry['matches'] for entry in current),
            'all_frozen_sources_match': bool(frozen) and all(entry['matches'] for entry in frozen),
            'base_known_limitation': data.get('baseKnownLimitation'),
            'base_investigation_history': data.get('baseInvestigationHistory', []),
            'scope_limit': 'Frozen production/test input evidence for the final private candidate. A retained investigation retraction is history, not an active limitation. This manifest does not certify a newly linked selected production artifact.'}


def accepted_production_98_evidence(active):
    """Bind accepted 98-TU evidence to its exact captured sources and runtime."""
    base = ROOT / '.cache/tu98-fixed-gate-snapshot'
    acceptance_path = base / 'acceptance.json'
    if not acceptance_path.is_file():
        return {'available': False, 'path': relative(base)}
    acceptance = json.loads(read(acceptance_path))
    manifest_path = base / 'js/wasm/build.json'
    manifest = json.loads(read(manifest_path))
    captured_path = base / 'captured-input-hashes.json'
    captured = json.loads(read(captured_path))
    public_captured_path = base / 'public-input-hashes.json'
    public_captured = json.loads(read(public_captured_path))
    supplement_path = base / 'public-capture-supplement.json'
    supplement = json.loads(read(supplement_path))
    declared = declared_manifest_sources(manifest)
    declared_integrity = source_integrity({relative(base / path): value for path, value in declared.items()})
    captured_integrity = source_integrity({relative(base / path): value for path, value in captured.items()})
    public_integrity = source_integrity({relative(base / path): value for path, value in public_captured.items()})
    # The unchanged public runner embeds its JSON after this marker in its log.
    results_path = base / 'public.log'
    public_log = read(results_path)
    results = json.loads(public_log.split('__RESULTS_JSON__\n', 1)[1]).get('results', [])
    totals = {}
    for result in results:
        for name, metric in result.get('metrics', {}).items():
            total = totals.setdefault(name, {'matched': 0, 'total': 0})
            total['matched'] += metric['matched']
            total['total'] += metric['total']
    all_public_exact = bool(results) and all(result.get('passed') and not result.get('error')
        and all(metric['matched'] == metric['total'] for metric in result.get('metrics', {}).values())
        for result in results)
    checks = {
        'accepted_status': acceptance.get('status') == 'accepted',
        'manifest_matches_acceptance': READS[relative(manifest_path)]['sha256'] == acceptance.get('manifestSha256'),
        'captured_manifest_matches_acceptance': captured.get('js/wasm/build.json') == acceptance.get('manifestSha256'),
        'wasm_matches_acceptance': manifest.get('wasmSha256') == acceptance.get('wasmSha256'),
        'runtime_matches_acceptance': captured.get('js/ported/wasm-runtime.js') == acceptance.get('runtimeSha256'),
        'engrave_runtime_matches_acceptance': captured.get('js/ported/engrave-runtime.js') == acceptance.get('engraveRuntimeSha256'),
        'windows_runtime_matches_acceptance': captured.get('js/ported/windows-runtime.js') == acceptance.get('windowsRuntimeSha256'),
        'monmove_runtime_matches_acceptance': captured.get('js/ported/monmove-runtime.js') == acceptance.get('monmoveRuntimeSha256'),
        'mkmaze_source_matches_acceptance': captured.get('js/ported/mkmaze.js') == acceptance.get('mkmazeSourceSha256'),
        'tu_count_matches_acceptance': len(manifest.get('javascriptTranslationUnits', [])) == acceptance.get('translationUnits'),
        'captured_file_count_matches_acceptance': len(captured) == acceptance.get('capturedFiles') == acceptance.get('unchangedCapturedFiles'),
        'all_captured_declared_sources_match': bool(declared_integrity) and all(entry['matches'] for entry in declared_integrity),
        'all_captured_files_match': bool(captured_integrity) and all(entry['matches'] for entry in captured_integrity),
        'all_public_captured_files_match': bool(public_integrity) and all(entry['matches'] for entry in public_integrity),
        'public_file_count_matches_acceptance': len(public_captured) == acceptance.get('publicInputFiles') == acceptance.get('unchangedPublicInputFiles'),
        'public_capture_preserves_base_inputs': all(public_captured.get(path) == value for path, value in captured.items()),
        'only_public_supplement_is_scorer_metadata': set(public_captured) - set(captured) == {'.teleport/repo-metadata.json'},
        'scorer_metadata_matches_acceptance': public_captured.get('.teleport/repo-metadata.json') == acceptance.get('scorerMetadataSha256') == supplement.get('addedFileSha256'),
        'supplement_records_separate_scopes': supplement.get('baseCaptureInputs') == len(captured) and supplement.get('publicInputFiles') == len(public_captured) and supplement.get('addedFile') == '.teleport/repo-metadata.json' and supplement.get('allBaseInputsUnchangedAfterIntegration') is True and supplement.get('frozenHarnessChanged') is False,
        'all_public_results_exact': all_public_exact,
        'all_44_public_recordings_present': len(results) == 44,
        'public_metrics_match_acceptance': {name: metric['total'] for name, metric in totals.items()} == acceptance.get('metrics'),
    }
    integration_path = base / 'integration.log'
    integration_result_path = base / 'integration-result.json'
    integration_result = json.loads(read(integration_result_path))
    provenance_path = base / 'provenance-after.log'
    import_path = base / 'production-import-audit.json'
    integration = read(integration_path)
    # Record the captured provenance log and independently recheck its hashes.
    if provenance_path.is_file():
        read(provenance_path)
        provenance_log = {'path': relative(provenance_path), **READS[relative(provenance_path)]}
    else:
        provenance_log = {'available': False, 'verification': 'all_captured_declared_sources_match'}
    imports = json.loads(read(import_path))
    checks.update(integration_recorded_passed=acceptance.get('integration', '').startswith('passed'),
                  integration_log_pass_marker='passed' in integration.lower(),
                  integration_original_deadlines=integration_result.get('exitCode') == 0 and integration_result.get('originalHarness') is True and integration_result.get('diagnosticLoaders') is False and integration_result.get('workerDeadlineSeconds') == 30 and integration_result.get('allCapturedHashesUnchanged') == len(captured),
                  recorded_c_lua_algorithms_absent=imports.get('cInterpreterSymbolsAbsent') is True)
    matched = (all(checks.values())
               and active['manifest_file_sha256'] == acceptance.get('manifestSha256')
               and active['all_manifest_declared_artifact_and_source_hashes_match'])
    return {'available': True, 'path': relative(base),
            'acceptance_path': relative(acceptance_path),
            'acceptance_sha256': READS[relative(acceptance_path)]['sha256'],
            'recorded_acceptance': acceptance, 'binding_checks': checks,
            'selected_manifest_matches_accepted_manifest': active['manifest_file_sha256'] == acceptance.get('manifestSha256'),
            'selected_artifact_and_runtime_match_accepted_snapshot': matched,
            'accepted_manifest_sha256': READS[relative(manifest_path)]['sha256'],
            'accepted_lua_backend': manifest.get('luaBackend'),
            'accepted_lua_source_count': len((manifest.get('javascriptLua') or {}).get('sourceSha256', {})),
            'declared_provenance_count': len(declared), 'declared_provenance_integrity': declared_integrity,
            'captured_inputs_path': relative(captured_path),
            'captured_inputs_sha256': READS[relative(captured_path)]['sha256'],
            'captured_input_count': len(captured), 'captured_input_integrity': captured_integrity,
            'public_capture': {'path': relative(public_captured_path), 'sha256': READS[relative(public_captured_path)]['sha256'],
                               'count': len(public_captured), 'integrity': public_integrity,
                               'supplement_path': relative(supplement_path), 'supplement_sha256': READS[relative(supplement_path)]['sha256'],
                               'recorded_supplement': supplement},
            'public_results': {'path': relative(results_path), 'sha256': READS[relative(results_path)]['sha256'],
                               'passed': sum(bool(result.get('passed')) for result in results),
                               'total': len(results), 'metrics': totals,
                               'errors': [result.get('error') for result in results if result.get('error')]},
            'integration': {'path': relative(integration_path), 'sha256': READS[relative(integration_path)]['sha256'],
                            'recorded_status': acceptance.get('integration'), 'log_contains_pass': 'passed' in integration.lower()},
            'provenance_log': provenance_log,
            'import_audit': {'path': relative(import_path), 'sha256': READS[relative(import_path)]['sha256'],
                             'recorded': imports},
            'module_capture': {'recorded_literal_closure_verified_in_copy': acceptance.get('literalModuleClosureVerifiedInCopy'),
                               'recorded_resolved_module_files': acceptance.get('resolvedModuleFiles'),
                               'limitation': 'Recorded Acorn AST traversal of literal local imports/exports; the audit rechecks captured hashes, not JavaScript parsing. SDK/tooling and dynamic file access are outside that closure.'},
            'scope_limit': 'Recorded acceptance for this exact captured 98-TU manifest, Wasm and JS/runtime/source set, not a fresh audit replay. Integration covers the original968 inputs; public scoring covers969 including the later identical scorer metadata supplement. Equal Wasm alone is insufficient. Later builds or source changes are not covered when the selected manifest or declared source hashes differ; native parity for the new TUs remains as disclosed in acceptance.'}


def accepted_production_evidence(active):
    """Verify the accepted 110-TU capture; retain the separate 98-TU history."""
    base = ROOT / '.cache/tu110-warn-fixed-gate-snapshot'
    acceptance_path = base / 'acceptance.json'
    if not acceptance_path.is_file():
        return accepted_production_98_evidence(active)
    acceptance = json.loads(read(acceptance_path))
    identity = acceptance['identity']
    manifest_path = base / 'js/wasm/build.json'
    manifest = json.loads(read(manifest_path))
    captured_path = base / 'captured-input-hashes.json'
    captured = json.loads(read(captured_path))
    declared = declared_manifest_sources(manifest)
    declared_integrity = source_integrity({relative(base / p): h for p, h in declared.items()})
    captured_integrity = source_integrity({relative(base / p): h for p, h in captured.items()})
    integration_path = base / 'integration.log'
    integration_log = read(integration_path)
    integration_result_path = base / 'integration-result.json'
    integration_result = json.loads(read(integration_result_path))
    command_path = base / 'original-command-contract.json'
    command_record = json.loads(read(command_path))
    command = acceptance['commandContract']
    # The immutable pre-terminal command record says pending. The final receipt
    # records the actual exit; all other command/environment fields must agree.
    recorded_public_exit = command_record['public']['exitCode']
    command_record['public']['exitCode'] = command['public']['exitCode']
    public_path = base / 'public.log'
    public_log = read(public_path)
    public_data = json.loads(public_log.split('__RESULTS_JSON__\n', 1)[1])
    parsed_path = base / 'public-results.json'
    parsed_public = json.loads(read(parsed_path))
    results = public_data.get('results', [])
    required_metrics = {'rngCalls', 'screens', 'cellsOnly', 'cursors', 'animFrames'}
    totals = {key: {'matched': 0, 'total': 0} for key in required_metrics}
    all_exact = bool(results)
    for result in results:
        metrics = result.get('metrics', {})
        all_exact &= (result.get('passed') is True and not result.get('error')
                      and set(metrics) == required_metrics)
        for key, metric in metrics.items():
            if key not in totals:
                all_exact = False
                continue
            matched, total = metric.get('matched'), metric.get('total')
            valid = (type(matched) is int and type(total) is int
                     and matched == total and total >= 0)
            all_exact &= valid
            if valid:
                totals[key]['matched'] += matched
                totals[key]['total'] += total
    import_path = base / '.cache/tu110-warn-fixed-production-import-audit.json'
    imports = json.loads(read(import_path))
    closure_path = base / '.cache/next-game-import-closure.json'
    closure = json.loads(read(closure_path))
    critical = ['js/wasm/build.json', 'js/wasm/nethack.wasm',
                'js/wasm/nethack.mjs.symbols', 'js/wasm/link-objects.txt',
                '.teleport/repo-metadata.json', 'scripts/test-wasm.mjs',
                'scripts/score-wasm.sh', '.cache/tu110-warn-fixed-production-import-audit.json',
                '.cache/next-game-import-closure.json']
    integration_command, public_command = command['integration'], command['public']
    checks = {
        'accepted_110_receipt': acceptance.get('acceptedTranslationUnits') == identity.get('translationUnits') == 110,
        'manifest_matches_acceptance': READS[relative(manifest_path)]['sha256'] == identity.get('manifestSha256'),
        'captured_manifest_matches_acceptance': captured.get('js/wasm/build.json') == identity.get('manifestSha256'),
        'wasm_matches_acceptance': manifest.get('wasmSha256') == captured.get('js/wasm/nethack.wasm') == identity.get('wasmSha256'),
        'runtime_matches_acceptance': captured.get('js/ported/wasm-runtime.js') == identity.get('runtimeSha256'),
        'engrave_runtime_matches_acceptance': captured.get('js/ported/engrave-runtime.js') == identity.get('engraveRuntimeSha256'),
        'tu_count_matches_acceptance': len(manifest.get('javascriptTranslationUnits', [])) == 110,
        'declared_count_matches_acceptance': len(declared) == acceptance.get('declaredProvenanceHashes') == 683,
        'captured_file_count_matches_acceptance': len(captured) == identity.get('capturedFiles') == acceptance.get('allCapturedInputsUnchanged') == 1322,
        'critical_inputs_in_base_capture': all(p in captured for p in critical),
        'all_captured_declared_sources_match': bool(declared_integrity) and all(e['matches'] for e in declared_integrity),
        'all_captured_files_match': bool(captured_integrity) and all(e['matches'] for e in captured_integrity),
        'no_changed_inputs_recorded': acceptance.get('changedInputs') == [],
        'integration_receipt_matches_acceptance': integration_result == acceptance.get('integration'),
        'integration_log_matches_receipt': READS[relative(integration_path)]['sha256'] == integration_result.get('logSha256'),
        'integration_log_pass_marker': 'passed' in integration_log.lower(),
        'integration_covers_base_capture': integration_result.get('exitCode') == 0 and integration_result.get('allCapturedInputsUnchanged') == len(captured),
        'command_record_matches_final_receipt': command_record == command and recorded_public_exit in ['pending', 0],
        'integration_original_deadlines': (integration_command.get('originalHarness') is True
            and integration_command.get('workerDeadlineSeconds') == 30
            and integration_command.get('diagnosticLoaders') is False
            and integration_command.get('timeoutOverride') is None
            and integration_command.get('exitCode') == 0
            and integration_command.get('session') == integration_result.get('session')
            and integration_command.get('command', [])[1:] == ['scripts/test-wasm.mjs']),
        'public_original_deadlines': (public_command.get('originalHarness') is True
            and public_command.get('sessionDeadlineSeconds') == 45
            and public_command.get('diagnosticLoaders') is False
            and public_command.get('timeoutOverride') is None
            and public_command.get('exitCode') == acceptance.get('publicExitCode') == 0
            and public_command.get('command') == ['bash', 'scripts/score-wasm.sh']
            and public_command.get('environment', {}).get('TZ') == 'America/New_York'),
        'ambient_diagnostic_options_absent': set(command.get('ambientDiagnosticOptionsAbsent', [])) == {'SESSION_REPLAY_TIMEOUT_MS', 'NODE_OPTIONS'},
        'public_log_matches_acceptance': READS[relative(public_path)]['sha256'] == acceptance.get('publicLogSha256'),
        'parsed_public_matches_original_log': parsed_public == public_data,
        'all_public_results_exact': bool(all_exact),
        'all_44_distinct_recordings_present': len(results) == len({r.get('session') for r in results}) == acceptance.get('publicPassed') == acceptance.get('publicTotal') == 44,
        'public_metrics_match_acceptance': {k: v['total'] for k, v in totals.items()} == acceptance.get('exactMetricTotals'),
        'no_public_failures_recorded': acceptance.get('failures') == [],
        'recorded_import_audit_passed': (imports.get('translationUnits') == 110 and imports.get('allOriginalObjectsAbsent') is True
            and len(imports.get('ports', [])) == 23
            and all(p.get('originalObjectAbsent') is True and p.get('privateAliasesAbsent') is True for p in imports['ports'])),
        'recorded_c_lua_algorithms_absent': imports.get('luaBackend') == manifest.get('luaBackend') == 'javascript' and imports.get('cInterpreterSymbolsAbsent') is True,
        'literal_module_closure_matches_acceptance': (len(closure.get('files', [])) == acceptance.get('literalModuleClosure', {}).get('files') == 298
            and closure.get('nonliteralImports') == [] and acceptance.get('literalModuleClosure', {}).get('nonliteralExpressions') == 0
            and all(p in captured for p in closure['files'])),
    }
    selected_matches = active['manifest_file_sha256'] == identity.get('manifestSha256')
    matched = bool(all(checks.values()) and selected_matches
                   and active['all_manifest_declared_artifact_and_source_hashes_match'])
    historical_path = ROOT / '.cache/tu98-fixed-gate-snapshot/acceptance.json'
    read(historical_path)
    return {
        'available': True, 'path': relative(base),
        'acceptance_path': relative(acceptance_path), 'acceptance_sha256': READS[relative(acceptance_path)]['sha256'],
        'recorded_acceptance': acceptance, 'binding_checks': checks,
        'selected_manifest_matches_accepted_manifest': selected_matches,
        'selected_artifact_and_runtime_match_accepted_snapshot': matched,
        'accepted_manifest_sha256': READS[relative(manifest_path)]['sha256'],
        'accepted_lua_backend': manifest.get('luaBackend'),
        'accepted_lua_source_count': len((manifest.get('javascriptLua') or {}).get('sourceSha256', {})),
        'declared_provenance_count': len(declared), 'declared_provenance_integrity': declared_integrity,
        'captured_inputs_path': relative(captured_path), 'captured_inputs_sha256': READS[relative(captured_path)]['sha256'],
        'captured_input_count': len(captured), 'captured_input_integrity': captured_integrity,
        'public_capture': {'path': relative(captured_path), 'sha256': READS[relative(captured_path)]['sha256'],
                           'count': len(captured), 'integrity': captured_integrity,
                           'same_as_integration_capture': True, 'scorer_metadata_present_before_both_gates': True,
                           'supplement_path': None},
        'public_results': {'path': relative(public_path), 'sha256': READS[relative(public_path)]['sha256'],
                           'passed': sum(r.get('passed') is True for r in results), 'total': len(results), 'metrics': totals,
                           'errors': [r.get('error') for r in results if r.get('error')]},
        'integration': {'path': relative(integration_path), 'sha256': READS[relative(integration_path)]['sha256'],
                        'recorded': integration_result, 'command_contract': command, 'command_contract_path': relative(command_path),
                        'command_contract_sha256': READS[relative(command_path)]['sha256']},
        'import_audit': {'path': relative(import_path), 'sha256': READS[relative(import_path)]['sha256'], 'recorded': imports},
        'module_capture': {'path': relative(closure_path), 'sha256': READS[relative(closure_path)]['sha256'],
                           'recorded_literal_closure_verified_in_copy': checks['literal_module_closure_matches_acceptance'],
                           'recorded_resolved_module_files': len(closure.get('files', [])),
                           'limitation': 'Recorded Acorn literal local import/export traversal, not rerun by this audit; SDK/tooling and dynamic file access remain outside it.'},
        'historical_acceptance': {'path': relative(historical_path), 'sha256': READS[relative(historical_path)]['sha256'],
                                  'scope': 'Separate 98-TU history with 968 integration inputs and later 969-input public supplement; not the 110-TU capture scope.'},
        'scope_limit': 'Recorded acceptance for the exact captured 110-TU manifest, Wasm and JS/runtime/source set, not a fresh replay. Both original timed gates cover the same1322 inputs, including scorer metadata. Equal Wasm alone is insufficient. Current source changes invalidate selected matching; 57 new native checks remain pending and53 historical native suites are not a fresh110 aggregate proof.',
    }


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
            elif category == 'lua' and active['built_lua_backend'] == 'javascript':
                entry['selected_resolution'] = 'Selected JavaScript Lua algorithms through C API/callback/storage ABI; literal name does not establish individual semantic coverage'
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
    paths += sorted((ROOT / 'js/nethack/bindings').glob('*.js'))
    paths += sorted((ROOT / 'js/backends').rglob('*.js'))
    paths += [p for directory in ['js/c-runtime', 'js/lua', 'js/libraries', 'js/platform', 'js/nethack'] for p in sorted((ROOT / directory).rglob('*.js'))]
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
    integrity = source_integrity((manifest.get('javascriptDependencies') or {}).get('sourceSha256', {}))
    lua_integrity = source_integrity((manifest.get('javascriptLua') or {}).get('sourceSha256', {}))
    declared_integrity = source_integrity(declared_manifest_sources(manifest))
    groups = []
    for category, names in sorted(LIBC.items()):
        entries = sorted(names & defined)
        groups.append({'category': category, 'defined_wasm_names': entries,
                       'interpretation': 'C ABI forwarding to selected JavaScript regex' if category == 'regex' and selected == 'javascript'
                       else 'Names defined in selected Wasm; aliases/inlined and internal support routines are additional.'})
    lua_names = sorted(name for name in defined if re.match(r'^lua(?:_|[A-Z])', name))
    lua_internals = sorted(name for name in lua_names if re.match(r'^lua[BCDEFGHMOSTUVXYZ]_', name))
    lua_backend = manifest.get('luaBackend')
    lua_basis = 'explicit build.json luaBackend'
    if lua_backend is None:
        lua_backend = ('javascript' if manifest.get('javascriptLua') else 'c' if lua_internals else 'unresolved')
        lua_basis = ('legacy manifest: javascriptLua metadata' if manifest.get('javascriptLua') else
                     'legacy manifest: defined internal Lua algorithm symbols' if lua_internals else
                     'legacy manifest has no explicit Lua backend; no conclusive symbol evidence')
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
        'built_lua_backend': lua_backend,
        'configured_default_lua_backend': ('javascript' if "JS_LUA = '--c-lua' not in sys.argv and (not C_DEPENDENCIES or '--js-lua' in sys.argv)" in build else 'unresolved'),
        'alternate_c_lua_backend_flag': '--c-lua' if "'--c-lua' in sys.argv" in build else None,
        'lua_build_default_is_not_selected_artifact_evidence': True,
        'lua_backend_selection': {'manifest_luaBackend': manifest.get('luaBackend'),
                                  'manifest_lua': manifest.get('lua'),
                                  'manifest_javascriptLua': manifest.get('javascriptLua'),
                                  'resolved_backend': lua_backend, 'basis': lua_basis,
                                  'javascript_provenance_recorded': bool((manifest.get('javascriptLua') or {}).get('sourceSha256')),
                                  'defined_internal_algorithm_count': len(lua_internals),
                                  'backend_matches_internal_symbol_observation': (not bool(lua_internals) if lua_backend == 'javascript' else bool(lua_internals) if lua_backend == 'c' else None),
                                  'symbol_observation_limit': 'Symbol names are consistency evidence; API forwarders can remain compiled and symbol-map pairing is limited as described below.',
                                  'adapter_selection_evidence': evidence('js/wasm-adapter.js', "buildMetadata.luaBackend === 'javascript'")},
        'built_implementations': {key: manifest.get(key) for key in ['terminalCapabilities', 'compression', 'regex', 'ncursesRole', 'compressionSourceRole', 'lua', 'luaBackend']},
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
        'manifest_lua_source_integrity': lua_integrity,
        'manifest_file_sha256': READS.get('js/wasm/build.json', {}).get('sha256'),
        'manifest_declared_artifact_and_source_integrity': declared_integrity,
        'manifest_declared_artifact_and_source_count': len(declared_integrity),
        'all_manifest_declared_artifact_and_source_hashes_match': bool(declared_integrity) and all(entry['matches'] for entry in declared_integrity),
        'provenance_binding_requirement': 'A final validation summary must bind this exact build manifest and its declared JS/runtime/source hashes as well as the Wasm artifact. JS-only corrections can preserve the Wasm SHA, so matching Wasm alone does not pair a recording result with the selected runtime.',
        'wasm_artifact_matches_manifest': READS.get(relative(binary_path), {}).get('sha256') == manifest.get('wasmSha256'),
        'recorded_public_validation': {
            'available': recording is not None, 'path': relative(recording_path),
            **({key: recording.get(key) for key in ['sessions', 'passed', 'errors', 'metrics', 'wasmSha256', 'dependencyBackend']} if recording else {}),
            'matches_selected_wasm_artifact': bool(recording and recording.get('wasmSha256') == READS.get(relative(binary_path), {}).get('sha256')),
            'binding_strength': 'Historical Wasm-only pairing; insufficient to validate changed JavaScript/runtime sources.',
            'final_selected_validation_entry': 'accepted_production_validation',
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
            {'dependency': 'Lua 5.4.8', 'selected_status': ('JavaScript Lua algorithms selected; C ABI/callback/storage bridge retained' if lua_backend == 'javascript' else 'compiled C interpreter/runtime retained' if lua_backend == 'c' else 'unresolved'),
             'compiled_lua_prefix_name_count': len(lua_names), 'compiled_lua_prefix_names': lua_names,
             'defined_internal_algorithm_names': lua_internals,
             'symbol_limit': 'Lua API names can be C ABI forwarders in a JS Lua build; API prefix counts alone do not identify the algorithm backend.',
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
    standalone_graph = reachable('js/nethack/runtime.js')
    selected_sources = {ROOT / path for path in active_source_paths(active)}
    services = []
    for path in [p for directory in ['js/c-runtime', 'js/lua', 'js/libraries', 'js/platform', 'js/nethack'] for p in sorted((ROOT / directory).rglob('*.js'))]:
        text = texts[path] if path in texts else read(path)
        selected_algorithm = path in selected_sources
        if selected_algorithm:
            status = 'selected_game_javascript_dependency_or_abi_adapter'
        elif path.name == 'game-files.js' and path in adapter_graph:
            status = 'selected_game_transport_with_injected_emscripten_filesystem'
        elif path in standalone_graph:
            status = 'standalone_provider_only_not_selected_game_runtime'
        elif path.parent.name == 'lua' or path.name.startswith(('lua-', 'wasm-lua-')):
            status = 'javascript_lua_implementation_or_provider_not_recorded_as_selected_source'
        else:
            status = 'present_but_selected_runtime_use_unresolved'
        services.append({'path': relative(path), 'physical_lines': len(text.splitlines()),
                         'status': status, 'reachable_from_adapter_by_literal_import_graph': path in adapter_graph,
                         'reachable_from_standalone_provider_by_literal_import_graph': path in standalone_graph,
                         'selected_build_manifest_source': path in selected_sources,
                         'exports_observed': sorted(set(re.findall(r'\bexport\s+(?:async\s+)?(?:function|class|const|let)\s+(\w+)', strip_comments(text)))),
                         'static_js_import_sites': importers[path]})
    lapi_path = ROOT / 'js/lua/lapi.js'
    lapi = texts.get(lapi_path, '')
    methods = sorted(set(re.findall(r'^\s{2}((?:lua|luaL)_\w+)\s*\(', strip_comments(lapi), re.M)))
    unsupported = sorted(set(re.findall(r'^\s{2}((?:lua|luaL)_\w+)\([^\n]*?\)\s*\{\s*return this\.unsupported\(', strip_comments(lapi), re.M)))
    provider = texts.get(ROOT / 'js/lua/abi.js', '')
    provider_cases = sorted(set(re.findall(r"\bcase\s+'((?:lua|luaL)_\w+)'|\boperation\s*===\s*'((?:lua|luaL)_\w+)'", strip_comments(provider))))
    provider_names = {name for pair in provider_cases for name in pair if name}
    lua_limits = []
    for path in sorted(path for path in texts if path.parent.name == 'lua' or path.name.startswith(('lua-', 'wasm-lua-'))):
        text = texts.get(path, '')
        for line, value in enumerate(text.splitlines(), 1):
            if re.search(r'cadence|heap parity|parity is|arbitrary source|transport budget|host-work|resource limit|not native', value, re.I):
                lua_limits.append({'path': relative(path), 'line': line, 'excerpt': value.strip()[:260]})
    tests = ['scripts/test-js-compress.mjs', 'scripts/test-js-terminfo.mjs', 'scripts/test-js-posix-regex.mjs',
             'scripts/test-js-runtime.mjs', 'scripts/test-js-runtime-regex.mjs', 'scripts/test-js-time.mjs', 'scripts/test-js-vfs.mjs',
             'scripts/test-js-lua.mjs', 'scripts/test-js-lua-api.mjs', 'scripts/test-js-dependency-isolation.mjs']
    tests = sorted(set(tests + [relative(path) for path in (ROOT / 'scripts').glob('test-js-lua*.mjs')]))
    for path in tests:
        read(ROOT / path)
    final_candidate = private_lua_evidence('.cache/js-lua-game-final', historical=False)
    aggregate_freeze = lua_aggregate_freeze_evidence()
    acceptance = final_candidate.get('acceptance', {})
    private_gates = final_candidate.get('recorded_validation', {})
    final_binding_checks = ['wasm_matches_candidate_manifest', 'wasm_matches_candidate_artifact',
                            'freeze_manifest_matches_acceptance', 'public_metrics_match_summary',
                            'level_totals_match_summary', 'wizard_groups_match_summary',
                            'all_production_overlay_hashes_match']
    final_acceptance_matches = bool(acceptance) and all(acceptance.get(key) for key in final_binding_checks)
    final_recorded_passes = (private_gates.get('public', {}).get('passed', 0) > 0
                             and private_gates['public'].get('passed') == private_gates['public'].get('total')
                             and not private_gates['public'].get('errors')
                             and all(private_gates.get(key, {}).get('group_count', 0) > 0
                                     and private_gates[key].get('passed') == private_gates[key].get('group_count')
                                     for key in ['all_levels', 'wizard']))
    final_private_verified = final_acceptance_matches and final_recorded_passes
    frozen_production_hashes = {entry['path']: entry['manifest_sha256']
                               for entry in aggregate_freeze.get('current_source_integrity', [])
                               if entry['path'] in aggregate_freeze.get('production_paths', [])}
    selected_lua_hashes = {entry['path']: entry['manifest_sha256']
                          for entry in active['manifest_lua_source_integrity']}
    selected_lua_matches_final = bool(frozen_production_hashes) and selected_lua_hashes == frozen_production_hashes
    return {
        'method': 'Literal static imports plus selected manifest source hashes and inspected provider wiring. Imports may be conditional and do not establish executed call closure.',
        'modules': services,
        'standalone_provider': {
            'path': 'js/nethack/runtime.js', 'selected_by_active_adapter': ROOT / 'js/nethack/runtime.js' in adapter_graph,
            'translated_subsystems': [name + '.c' for name in sorted(set(re.findall(r'''\bimport\s+\*\s+as\s+\w+\s+from\s+['"]\./([^'"]+)\.js['"]''', strip_comments(texts[ROOT / 'js/nethack/runtime.js']))))],
            'services': ['JavaScript-owned ArrayBuffer memory', 'bounded LP64 strings/integer formatting/parsing',
                         'Date-based calendar/time compatibility', 'regular-file/directory VFS and stream facade',
                         'per-instance environment and scoped C bindings', 'opaque-handle configured ERE through unchanged posixregex translation'],
            'limitations': ['Not the complete game state/global layout/runtime', 'No C stdio layer or full libc',
                            'No full IANA/POSIX per-instance timezone database or strftime',
                            'VFS excludes device/socket/symlink/mount/lock/ownership/ACL/chmod services'],
            'evidence': [evidence('js/nethack/runtime.js', 'new CMemory'), evidence('js/nethack/runtime.js', 'new CVFS'),
                         evidence('js/nethack/runtime.js', 'calendar:'), evidence('js/nethack/runtime.js', 'posixregex:')]},
        'lua': {
            'selected_game_interpreter_replaced': active['built_lua_backend'] == 'javascript',
            'selected_backend': active['built_lua_backend'],
            'entrypoint': 'js/lua/bytecode-vm.js', 'api_entrypoint': 'js/lua/lapi.js',
            'source_compiler': 'js/lua/incremental-parser.js',
            'source_compiler_components': ['js/lua/incremental-lexer.js',
                                           'js/lua/incremental-parser.js',
                                           'js/lua/incremental-codegen.js',
                                           'js/lua/parser-errors.js',
                                           'js/lua/compiler-allocations.js'],
            'source_compiler_compatibility_entrypoint': 'js/lua/source-compiler.js',
            'binary_chunk_codec': 'js/lua/codegen.js',
            'abi_provider': 'js/lua/abi.js',
            'abi_bridge': ['nethack-c/wasm/lua-bridge.c', 'nethack-c/wasm/lua-library.js'],
            'implementation_form': 'Lua 5.4.8 register VM implementing all 83 opcodes, direct demand-reader lexer/parser/expression-descriptor code generation with native allocation operations interleaved during parsing, binary chunk codec, C API facade and real memory64 C ABI/callback provider. The AST interpreter remains a separate execution path, not the game candidate VM.',
            'compiler_limit': 'Native compiler parity is differentially tested for the compared corpus; this is a JavaScript compiler, not a runtime native compiler subprocess. Arbitrary source equivalence is not proven by inventory.',
            'opcode_names': re.search(r"LUA_OPCODES = Object.freeze\('([^']+)'", texts.get(ROOT / 'js/lua/codegen.js', ''))[1].split(),
            'private_automatic_candidate': private_lua_evidence(),
            'private_final_candidate': final_candidate,
            'recorded_aggregate_freeze': aggregate_freeze,
            'final_current_source_candidate': {'status': ('selected_javascript_artifact_and_runtime_match_accepted_production_snapshot'
                                                         if active['built_lua_backend'] == 'javascript'
                                                         and active['accepted_production_validation'].get('selected_artifact_and_runtime_match_accepted_snapshot')
                                                         else 'selected_javascript_has_live_source_changes_after_accepted_production_snapshot'
                                                         if active['built_lua_backend'] == 'javascript'
                                                         and active['accepted_production_validation'].get('selected_manifest_matches_accepted_manifest')
                                                         and not active['all_manifest_declared_artifact_and_source_hashes_match']
                                                         else 'selected_javascript_final_private_candidate_verified_production_artifact_gates_separate'
                                                         if active['built_lua_backend'] == 'javascript' and final_private_verified
                                                         else 'final_private_candidate_verified_selected_backend_' + active['built_lua_backend']
                                                         if final_private_verified else 'pending_final_snapshot_game_validation'),
                                               'selected_backend': active['built_lua_backend'],
                                               'recorded_private_gates_passed_and_acceptance_bindings_match': final_private_verified,
                                               'current_sources_match_final_freeze': aggregate_freeze.get('all_current_sources_match', False),
                                               'selected_lua_manifest_matches_final_production_freeze': selected_lua_matches_final,
                                               'selected_artifact_and_runtime_match_accepted_production_snapshot': active['accepted_production_validation'].get('selected_artifact_and_runtime_match_accepted_snapshot', False),
                                               'selected_wasm_is_private_candidate': READS.get('js/wasm/nethack.wasm', {}).get('sha256') == final_candidate.get('manifest_wasm_sha256'),
                                               'selected_public_summary_matches_selected_wasm': active['recorded_public_validation']['matches_selected_wasm_artifact'],
                                               'historical_candidate_is_final_evidence': False,
                                               'requirement': 'Read the actual selected build manifest and validate its final Lua source hashes plus binary-specific public/integration gates. The accepted private candidate is a separately linked frozen game; historical automatic results and private candidate results do not by themselves validate a new production artifact.'},
            'recorded_local_differential_summaries': lua_differential_summaries(),
            'recorded_core_freeze': lua_core_freeze_evidence(),
            'recorded_incremental_freeze': lua_incremental_freeze_evidence(),
            'method_names_observed_in_lapi_class': methods,
            'direct_explicit_unsupported_methods': unsupported,
            'facade_unsupported_methods_with_explicit_abi_provider_dispatch': sorted(set(unsupported) & provider_names),
            'unsupported_interpretation': 'Facade methods can deliberately require host ABI facilities supplied by lua/abi.js. Their standalone exception is not evidence that the game ABI lacks them; dispatch-name presence is also not semantic certification.',
            'direct_explicit_unsupported_method_count': len(unsupported),
            'additional_complete_library_opener_unsupported': 'luaL_openlibs' if "luaL_openlibs() { throw" in lapi else None,
            'explicit_unsupported_count_including_complete_library_opener': len(unsupported) + int("luaL_openlibs() { throw" in lapi),
            'configured_call_limit': 'lua_resetthread occurs under notyet/#if0 and luaL_openlibs is in the inactive non-sandbox branch. The standalone luaL_openlibs exception is not a configured-game blocker; configured libraries are opened individually through the ABI provider.',
            'source_declared_limitations': lua_limits,
            'allocation_verification_scope': {
                'completed_differential_gates': ['Original C-compiled binary chunk loading/close for all 131 original scripts',
                                                 'Bytecode VM: 119 native execution/478-value cases and 119 exact opcode traces covering 334264 instruction boundaries, plus all 131 original native-compiled chunks',
                                                 'Bare bytecode runtime full allocator callback transcripts in INC and GEN, constructor/load/runtime refusal and COUNT threshold probes',
                                                 'Complete eight retained library opener and ordered requiref-chain allocation/free transcripts',
                                                 'Direct incremental source parser/codegen: 296 source cases with whole-string and one-byte readers; 1490 native prototypes and 113502 instructions including constants/register/upvalue/debug/local fields',
                                                 'Original 131 source scripts and 168 additional language/lexer/control-flow sources with complete source-load/close allocator transcripts; 250 refusal schedules and 2177 COUNT thresholds',
                                                 'Chunked source reader: 393 valid traces covering 736017 callbacks and 55 invalid traces plus 504 refusal schedules; binary reader: 9 native traces plus 99 refusal schedules and 96 malformed-input traces',
                                                 'Retained Lua load(reader): 18 full allocator/result traces and 337 refusal schedules, including source consumption order, reader errors, forced collection, COUNT observations and nesting boundaries',
                                                 'Native dump: 262 writer transcripts, 84061 block writes and 64 writer-refusal positions; retained debug/base: 62 cases and 201 values; debug hooks: 1482 events across 35 mask/count combinations',
                                                 'Real LuaL_Buffer/UBox formatting, UTF8 char and retained pack/OS consumers, with exact result/free/allocation transcripts and permanent refusal schedules',
                                                 'Actual string.format/UTF8 auxiliary error strings, type/source/alias/method/C-caller naming, native check ordering and allocator/refusal sequences',
                                                 'Sort actual C temporary stack slots/reused bytecode storage: 300 native comparator/table/GC/entropy traces plus 10 full allocator/result/error transcripts and 150 refusal schedules'],
                'not_blanket_certified': ['Arbitrary source/reader inputs and failure schedules outside the differential corpora',
                                          'All retained-library input combinations, temporary buffers and resource quotas outside their directed corpora',
                                          'Arbitrary weak/finalizer/userdata/thread graphs and whole-game native heap/cadence parity'],
                'evidence': [evidence('scripts/test-js-lua-memory.mjs', 'complete allocation/free callback transcript'),
                             evidence('scripts/test-js-lua-memory.mjs', 'eight original standard-library opener'),
                             evidence('scripts/test-js-lua-incremental.mjs'),
                             evidence('scripts/test-js-lua-bytecode.mjs'),
                             evidence('scripts/test-js-lua-source-memory.mjs'),
                             evidence('scripts/test-js-lua-reader.mjs'),
                             evidence('scripts/test-js-lua-reader-runtime.mjs'),
                             evidence('scripts/test-js-lua-format-utf8-errors.mjs'),
                             evidence('scripts/test-js-lua-sort.mjs'),
                             evidence('scripts/test-js-lua-sort-memory.mjs'),
                             evidence('js/lua/aux-error.js'),
                             evidence('js/lua/buffer.js'),
                             evidence('js/lua/compiler-allocations.js')],
                'scope_limit': 'Gates reported by the implementing owner and encoded in differential assertions; this inventory does not execute them. Their existence is not a blanket equivalence claim.'},
            'remaining_gates': ['Retain explicit limits beyond the completed source/reader/library/GC differential corpora; these comparisons do not prove arbitrary native heap parity',
                                'C library work does not fetch Lua opcodes; optional host-work guards are not native instruction hooks',
                                'The accepted production snapshot and final private candidate have separate evidence; any later link or runtime/source change needs its own final source-hash, recording and integration checks',
                                'Treat actual selected luaBackend/javascriptLua metadata and matching source hashes as selection evidence; a changed builder default or a private acceptance alone is insufficient',
                                'Remaining C game, memory64 ABI, allocator, host services and MEMFS still prevent whole-game JavaScript independence'],
            'provider_evidence': [evidence('js/lua/abi.js', 'createLuaAbi'),
                                  evidence('js/lua/bytecode-vm.js', 'compileLuaIncremental'),
                                  evidence('nethack-c/wasm/lua-bridge.c'),
                                  evidence('js/lua/lmem.js', 'cadence/heap parity')],
        },
        'game_file_transport': {'selected_in_adapter': ROOT / 'js/nethack/game-files.js' in adapter_graph,
                                'filesystem_currently_supplied': 'Emscripten module.FS/MEMFS',
                                'standalone_vfs_replaces_active_memfs': False,
                                'payload': 'Existing {files,deleted} transport; binary base64; persistence filter injected by adapter',
                                'evidence': [evidence('js/wasm-adapter.js', "from './services/game-files.js'"),
                                             evidence('js/wasm-adapter.js', 'captureGameFiles(module.FS')]},
        'test_entrypoints': tests,
        'verification_limit': 'The inventory records test entrypoints, not a fresh test run or coverage/equivalence certification.'}


def active_source_paths(active):
    return [entry.get('current_source_path', entry['path']) for entry in active['manifest_dependency_source_integrity'] + active['manifest_lua_source_integrity']]


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
    debug_source = tree / 'lib/lua-5.4.8/src/ldblib.c'
    debug_text = read(debug_source)
    debug_table = re.search(r'\bdblib\[\]\s*=\s*\{([\s\S]*?)\n\};', debug_text)
    debug_exports = re.findall(r'\{\s*"([^"]+)"\s*,', debug_table[1]) if debug_table else []
    never = {entry['name']: [item['function'] for item in entry['entries'] if item['condition'] == 'NEVER']
             for entry in filters}
    retained_debug = sorted(set(debug_exports) - set(never.get('ct_debug_debug', [])))
    wizard_libraries = {
        'os': sorted(item['function'] for group in filters if group['name'].startswith('ct_os_')
                     for item in group['entries'] if item['condition'] == 'IFFLAG'),
        'debug': retained_debug,
        'base_file_and_dynamic_loading': ['dofile', 'load', 'loadfile'],
        'never_removed_even_with_ALL': never,
        'io_library': 'not opened: luaopen_io is inside #ifdef notyet; retained base loadfile/dofile are separate',
        'package_library': 'not opened by nhlL_openlibs',
    }
    return {'api_observations': [{'name': name, 'sites': sites} for name, sites in sorted(calls.items())],
            'unique_api_name_count': len(calls), 'sandbox_initializers': initializers,
            'sandbox_filters': filters,
            'script_member_tokens': [{'name': name, 'sites': sites} for name, sites in sorted(script_members.items())],
            'scope_assessment': {
                'confidence': 'medium: source/configuration review; not preprocessed or dynamically instrumented',
                'normal_states': ['restricted base', 'coroutine', 'table', 'string', 'math', 'utf8'],
                'additional_states': ['wizard SAFE|DEBUGGING expands to ALL before library filtering', 'version information state'],
                'wizard_flag_expansion': {
                    'input': 'NHL_SB_SAFE | NHL_SB_DEBUGGING',
                    'steps': ['DEBUGGING adds NHL_SB_DB_SAFE (0x00002000)',
                              'DB_SAFE intersects NHL_SB_ALL (0x0000ffff)',
                              'if (NHL_SB_ALL & lflags) sets lflags to uint32_t(-1)',
                              'IFFLAG entries survive; NEVER entries are still removed'],
                    'retained_libraries': wizard_libraries,
                    'retained_debug_function_count': len(retained_debug),
                    'evidence': [evidence(relative(nhlua), 'if (NHL_SB_DEBUGGING & lflags)'),
                                 evidence(relative(nhlua), 'if (NHL_SB_ALL & lflags)'),
                                 evidence(relative(tree / 'src/wizcmds.c'), 'NHL_SB_SAFE | NHL_SB_DEBUGGING'),
                                 evidence(relative(debug_source), 'dblib[]')]},
                'inactive_observed_states_and_calls': [
                    {'name': 'string-only pattern matching state', 'condition': '#ifdef notyet',
                     'evidence': evidence(relative(nhlua), 'start_luapat(void)')},
                    {'name': 'lua_resetthread', 'condition': '#ifdef notyet and nested #if0',
                     'configured_game_blocker': False, 'evidence': evidence(relative(nhlua), 'lua_resetthread(luapat)')},
                    {'name': 'luaL_openlibs', 'condition': 'non-sandbox #else branch; prepared config enables NHL_SANDBOX',
                     'configured_game_blocker': False, 'evidence': evidence(relative(nhlua), 'luaL_openlibs(L);')},
                ],
                'not_opened_in_configured_sandbox': ['io library (#ifdef notyet)', 'package/module loader'],
                'os_scope': 'Absent from ordinary SAFE initialization, but all six retained OS functions are reachable through actual configured wizard SAFE|DEBUGGING expansion.',
                'preserve': ['Lua 5.4.8 integer/float semantics and strings', 'parser/compiler and VM',
                             'core garbage collector and userdata lifecycle/finalization; these are not removable standard-library features',
                             'tables, iteration, metamethods, userdata and object identity',
                             'C API stack and callbacks used by NetHack', 'registry/upvalues/metatables',
                             'errors/protected calls/tracebacks',
                             'instruction hooks and memory limits for configured sandbox states',
                             'Lua patterns, coroutine/table/string/math/UTF-8 behavior',
                             'seeded math.random and NetHack RNG call ordering',
                             'original level/quest scripts and NetHack nh/des/selection/object bindings'],
                'unresolved': ['Reachability beyond public, level-script and wizard differential corpora',
                               'Inactive/alternate compiled branches are not proven by lexical API matches',
                               'Native allocation sequence, GC cadence and C-library quota boundaries beyond the completed directed differential corpora',
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
    active['accepted_production_validation'] = accepted_production_evidence(active)
    service_sets = []
    for category, names in sorted(LIBC.items()):
        observations = []
        for name in sorted(names):
            if name in game_tokens:
                observations.append(name)
        service_sets.append({'category': category, 'game_text_tokens': observations})
    report = {
        'schema_version': 3,
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
        'lua_abi_library': collect_tu_dependencies(game_tokens, active, [ROOT / 'nethack-c/wasm/lua-library.js']),
        'runtime_observations': collect_runtime(),
        'compiled_service_candidates': {'method': 'Known libc/terminfo names matched as tokens in prepared C/headers; not calls or reachable closure.',
                                        'libc_groups': service_sets, 'terminfo_game_tokens': sorted(TERMINFO & game_tokens)},
        'compiled_service_sites': collect_compiled_service_sites(tree),
        'lua': lua_inventory(tree),
        'runtime_layers': [
            {'name': 'remaining_game_code', 'disposition': 'port incrementally; coordinate with active TU work', 'evidence': ['js/wasm/link-objects.txt', 'nethack-c/wasm/tu-ports.json']},
            {'name': 'c_abi_and_linear_memory', 'disposition': 'preserve addresses/layout/integer semantics initially; replace C helpers and Wasm memory ownership', 'evidence': ['nethack-c/wasm/tu-support.c', 'js/backends/emscripten/runtime.js']},
            {'name': 'libc_regex_time_files', 'disposition': 'JS regex selected through C ABI forwarders; compiled libc/time/MEMFS remain selected. Standalone bounded JS services do not replace the active game runtime.', 'evidence': ['nethack-c/wasm/tu-libraries/posixregex.js', 'nethack-c/wasm/tu-libraries/calendar.js', 'js/nethack/runtime.js']},
            {'name': 'lua_algorithms_and_abi', 'disposition': 'Selected Lua backend: ' + active['built_lua_backend'] + '. Complete 83-opcode JavaScript VM/compiler and ABI provider exist; final frozen private candidate acceptance is recorded separately from both historical automatic results and selected production artifact validation. C memory/callback transport remains even when Lua algorithms are JavaScript.', 'evidence': ['js/lua/bytecode-vm.js', 'js/lua/incremental-parser.js', 'js/lua/abi.js', 'nethack-c/wasm/lua-bridge.c']},
            {'name': 'assets', 'disposition': 'embed generated game data and pinned terminal entry as JS-accessible assets; native generators remain development-only', 'evidence': ['nethack-c/wasm/build.py']},
            {'name': 'replay_adapter_environment_startup', 'disposition': 'Game-file transport extracted and selected; active adapter still supplies Emscripten FS/ENV/startup/callMain/unwind. Standalone VFS/time/memory provider is separate.', 'evidence': ['js/wasm-adapter.js', 'js/nethack/game-files.js', 'js/nethack/runtime.js']},
            {'name': 'terminfo_capabilities', 'disposition': 'Pinned-entry JS terminfo selected; ncurses headers/data/reference build retained, C libtinfo excluded from selected runtime. C vararg/callback ABI support remains.', 'evidence': ['nethack-c/wasm/build.py', 'nethack-c/wasm/dependency-bridge.c', 'js/libraries/terminfo/index.js']},
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
            'JavaScript Lua implementation and frozen private validation are distinct from selected build.json luaBackend/javascriptLua provenance. Backend read from selected artifacts: ' + active['built_lua_backend'] + '.',
            'JavaScript Lua algorithm replacement does not remove the remaining game Wasm/Emscripten runtime, native-backed ABI storage or host file/time services.',
        ],
    }
    report['javascript_service_inventory'] = service_inventory(active)
    changed_inputs = [entry['path'] for entry in active['manifest_declared_artifact_and_source_integrity']
                      if not entry['matches']]
    if changed_inputs:
        report['unresolved'].append('Selected manifest has live artifact/source hash mismatches: '
                                    + ', '.join(changed_inputs)
                                    + '. Accepted production snapshot remains separately bound; its score is not transferred to these changed live inputs.')
    lua_candidate = report['javascript_service_inventory']['lua']
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
        'lua': ('selected_javascript_vm_compiler_abi_final_private_and_production_evidence_separate' if active['built_lua_backend'] == 'javascript'
                else 'final_private_javascript_candidate_accepted_production_selection_pending'
                if lua_candidate['final_current_source_candidate']['recorded_private_gates_passed_and_acceptance_bindings_match']
                else 'private_javascript_candidate_selected_backend_' + active['built_lua_backend']),
        'startup_capture_persistence': 'game_file_transport_extracted_active_memfs_retained',
        'independence': 'not_achieved_wasm_emscripten_remain_selected_lua_' + active['built_lua_backend'],
    }
    for entry in report['migration_backlog']:
        entry['current_status'] = backlog_status[entry['id']]
    report['migration_backlog'][3]['action'] = 'Retain selected JS codec and differential gates; replace remaining MEMFS/C ABI dependence during standalone runtime integration.'
    report['migration_backlog'][4]['action'] = 'Retain pinned-entry JS terminfo; remove remaining tparm/tputs C ABI support when game callers and callback state are JS-owned.'
    report['migration_backlog'][5]['action'] = 'Keep configured JS ERE selected; wire the separately implemented JS calendar/time provider into the active game through controlled integration.'
    report['migration_backlog'][6]['action'] = 'Retain accepted final private Lua snapshot and completed compiler/reader/runtime/library regression gates. Read actual selected build metadata and source hashes, then validate the newly linked production artifact before claiming promotion complete. Preserve actual wizard ALL expansion and NEVER filters.'
    report['migration_backlog'][6]['gate'] += ['Final private frozen candidate: 44 public recordings, all 126 level scripts at three seeds, three wizard seed groups and immutable full dependency runner accepted; selected production build has separate artifact and integration gates', 'Completed native source allocation/refusal, reader, automatic GC and C-library buffer/error differential corpora remain required regression gates; broader inputs are not blanket certified']
    if active['accepted_production_validation'].get('selected_artifact_and_runtime_match_accepted_snapshot'):
        report['migration_backlog'][6]['current_status'] = 'selected_javascript_lua_artifact_and_runtime_match_accepted_production_snapshot'
        report['migration_backlog'][6]['selected_acceptance_snapshot'] = active['accepted_production_validation']['path']
        report['migration_backlog'][6]['action'] = 'Retain selected JavaScript Lua with accepted production manifest/runtime/source bindings and completed regression gates. Revalidate later links or changed JavaScript/runtime sources; equal Wasm alone is insufficient. Preserve actual wizard ALL expansion and NEVER filters.'
    runtime_markers = {
        'nethack-c/wasm/build.py': 'link_flags = ',
        'nethack-c/wasm/build_terminfo.py': "'--with-termlib'",
        'nethack-c/wasm/tu-support.c': 'teleport_',
        'nethack-c/wasm/bridge.c': 'teleport_getch',
        'js/backends/emscripten/runtime.js': 'createPortedRuntime',
        'js/wasm-adapter.js': 'runWasmSegment',
        'js/wasm-replay-support.js': 'encodeRecorderScreen',
        'js/recording-profile.js': 'recordingProfile',
        'js/nethack/runtime.js': 'createJsRuntime',
        'js/nethack/game-files.js': 'captureGameFiles',
        'js/libraries/terminfo/index.js': 'createTerminfo',
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
    parser.add_argument('--output', type=Path, default=ROOT / 'docs/runtime-environment/dependency-inventory-current.json')
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
