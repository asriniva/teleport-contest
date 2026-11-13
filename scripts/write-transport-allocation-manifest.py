#!/usr/bin/env python3
"""Current-source receipt, separate from immutable historical cleanup manifests."""
from pathlib import Path
import subprocess,json,hashlib,sys
root=Path(__file__).resolve().parents[1];source=set(subprocess.check_output(['git','ls-tree','-r','--name-only','HEAD','--','js','frozen','scripts'],cwd=root,text=True).splitlines());source={p for p in source if Path(p).suffix in {'.js','.mjs','.json','.py','.sh','.c','.h','.inc'}}
source.update(['scripts/test-uhitm-delay-callback.mjs','scripts/transport_allocation_source_successors.py','scripts/test-transport-allocation-source-successors.py','scripts/test-c-runtime-live-views.mjs','scripts/test-recorder-bootstrap.mjs','scripts/write-transport-allocation-manifest.py','scripts/check-current-transport-allocation.mjs','docs/runtime-environment/nethack-layout.json','docs/runtime-environment/transport-allocation-source-successors.json','docs/runtime-environment/transport-allocation-native-evidence.json'])
source.update(['scripts/analyze-recorder-profile-recovery.py','scripts/author-standalone-engulf.mjs','scripts/test-standalone-engulf-main.mjs','scripts/fixtures/standalone-engulf-main.json','.github/workflows/score.yml','docs/runtime-environment/transport-allocation-public-validation.json','docs/runtime-environment/engulf-main-validation.json'])
for name in ['transport-allocation-public-validation.json','engulf-main-validation.json']:source.update(json.loads((root/'docs/runtime-environment'/name).read_text())['rawProofs'])
source.update(['scripts/benchmark-c-runtime-type-metadata.mjs','scripts/test-c-runtime-type-metadata.mjs','scripts/type_metadata_source_successor.py','scripts/test-type-metadata-source-successor.py','scripts/compare-recorder-profiles.py','.github/workflows/profile-runtime.yml','docs/runtime-environment/type-metadata-validation.json','docs/runtime-environment/type-metadata-source-review.json'])
source.update(json.loads((root/'docs/runtime-environment/type-metadata-validation.json').read_text())['rawProofs'])
source.update(r['patch']for r in json.loads((root/'docs/runtime-environment/type-metadata-source-review.json').read_text())['files'].values())
source.update(['scripts/free_list_source_successor.py','scripts/test-free-list-source-successor.py','scripts/test-c-runtime-free-lists.mjs','scripts/benchmark-c-runtime-free-lists.mjs','scripts/verify-public-recorder.py','docs/runtime-environment/free-list-source-review.json','docs/runtime-environment/free-list-source-successor.patch','docs/runtime-environment/free-list-validation.json','docs/runtime-environment/type-metadata-paired-ci-validation.json'])
for name in ['free-list-validation.json','type-metadata-paired-ci-validation.json']:source.update(json.loads((root/'docs/runtime-environment'/name).read_text())['rawProofs'])
source.update(['scripts/numeric_guards_source_successor.py','scripts/test-numeric-guards-source-successor.py','scripts/test-c-runtime-numeric-guards.mjs','scripts/test-c-runtime-numeric-coercions.mjs','docs/runtime-environment/numeric-guards-source-successor.patch'])
source.add('docs/runtime-environment/numeric-guards-validation.json')
source.update(json.loads((root/'docs/runtime-environment/numeric-guards-validation.json').read_text())['rawProofs'])
source.update(['scripts/scalar_load_source_successor.py','scripts/test-scalar-load-source-successor.py','scripts/test-c-runtime-scalar-loads.mjs','scripts/benchmark-c-runtime-scalar-loads.mjs','docs/runtime-environment/scalar-load-source-successors/types.js.patch'])
source.add('docs/runtime-environment/scalar-load-validation.json')
source.update(json.loads((root/'docs/runtime-environment/scalar-load-validation.json').read_text())['rawProofs'])
source.add('docs/runtime-environment/free-list-paired-ci-validation.json')
source.update(json.loads((root/'docs/runtime-environment/free-list-paired-ci-validation.json').read_text())['rawProofs'])
source.update(['scripts/load_plan_source_successor.py','scripts/test-load-plan-source-successor.py','scripts/test-c-runtime-load-plans.mjs','scripts/test-c-runtime-load-plan-mutations.mjs','scripts/benchmark-c-runtime-load-plans.mjs','docs/runtime-environment/load-plan-source-successor.patch'])
source.add('docs/runtime-environment/numeric-guards-paired-ci-validation.json')
source.update(json.loads((root/'docs/runtime-environment/numeric-guards-paired-ci-validation.json').read_text())['rawProofs'])
for name in ['load-plan-validation.json','scalar-load-paired-ci-validation.json']:
 source.add('docs/runtime-environment/'+name)
 source.update(json.loads((root/'docs/runtime-environment'/name).read_text())['rawProofs'])
source.add('docs/runtime-environment/load-plan-paired-ci-validation.json')
source.update(json.loads((root/'docs/runtime-environment/load-plan-paired-ci-validation.json').read_text())['rawProofs'])
source.update(['scripts/immutable_selectors_source_successor.py','scripts/test-immutable-selectors-source-successor.py','scripts/test-c-runtime-immutable-selectors.mjs','docs/runtime-environment/immutable-selectors-source-successors/adapter-factories.js.patch','docs/runtime-environment/immutable-selectors-source-successors/display.js.patch','docs/runtime-environment/immutable-selectors-source-successors/invent.js.patch'])
source.add('docs/runtime-environment/immutable-selectors-validation.json')
source.update(json.loads((root/'docs/runtime-environment/immutable-selectors-validation.json').read_text())['rawProofs'])
for name in ['pointer-limit-validation.json','immutable-selectors-deadline-ci-validation.json']:
 source.add('docs/runtime-environment/'+name)
 source.update(json.loads((root/'docs/runtime-environment'/name).read_text())['rawProofs'])
source.update(['scripts/pointer_limit_source_successor.py','scripts/test-pointer-limit-source-successor.py','docs/runtime-environment/pointer-limit-source-successors/hack.js.patch','docs/runtime-environment/pointer-limit-source-successors/mon.js.patch','docs/runtime-environment/pointer-limit-source-successors/wintty.js.patch'])
source.add('docs/runtime-environment/immutable-selectors-paired-ci-validation.json')
source.update(json.loads((root/'docs/runtime-environment/immutable-selectors-paired-ci-validation.json').read_text())['rawProofs'])
# Explicit additions bind branch tests and service fixes before their first commit.
# Historical native evidence and the historical 391-file receipt stay immutable.
source.update('scripts/'+name+'.mjs' for name in [
 'check-engine-callbacks','run-engine-branch-coverage',
 'test-engine-branch-gate','test-engine-branch-instrumentation','test-engine-branch-syntax',
 'test-engine-closed-parameters','test-engine-abi-rejections','test-display-branch-matrix','test-zap-branch-matrix','test-shop-pricing-branches',
 'test-engulf-branch-matrix','test-mhitm-branch-matrix','test-mhitu-branch-matrix',
 'test-production-window-bindings','test-trap-branch-matrix','test-uhitm-branch-matrix',
 'test-small-engine-branches',
 'test-policy-branch-gaps','test-calendar-branch-gaps','test-quest-inventory-branches','test-game-assets-branches','test-engine-reference-observers','test-engine-world-suite-selection','test-engine-reference-runtime-successor','run-production-world-branches','test-standalone-engulf-branches','test-standalone-keyboard-branches',
])
source.update('scripts/branch-coverage/'+name+'.mjs' for name in ['closed-parameters','collector','instrument','loader','production-world-suites','reference-runtime-successor','reference-setup','register','report','rumors-source-successor','runtime'])
source.add('docs/engine-branch-tests.md')
source.update(['scripts/engine_test_source_successors.py','scripts/test-engine-test-source-successors.py','docs/engine-test-source-successors.json'])
source.update(['scripts/engine_service_source_successors.py','scripts/test-engine-service-source-successors.py','docs/engine-service-source-successors.json','scripts/test-production-service-resolution.mjs','scripts/test-standalone-teleport-branches.mjs'])
source.update('scripts/'+name+'.mjs'for name in ['test-mon-header-constants','test-mon-position-branches','test-display-darkroom-branches','test-engine-mon-position-production','test-engine-fatal-zap-branches'])
source.update(['scripts/profile-runtime-pair.sh','scripts/test-profile-runtime-pair.py','docs/runtime-environment/pointer-limit-paired-ci-validation.json'])
source.update(json.loads((root/'docs/runtime-environment/pointer-limit-paired-ci-validation.json').read_text())['rawProofs'])
proof=json.loads((root/'docs/runtime-environment/transport-allocation-native-evidence.json').read_text());source.update(proof['rawProofs']);decl=json.loads((root/'docs/runtime-environment/transport-allocation-source-successors.json').read_text());source.update(r['patch']for r in decl['files'].values());sha=lambda p:hashlib.sha256((root/p).read_bytes()).hexdigest();data={'version':1,'baseCommit':'1dab2c64a80d86e2398875c0e3d45017f174abf1','scope':'Current implementation/tool/evidence source closure; historical391-hash receipt remains unchanged. Not runtime/game acceptance.','sha256':{p:sha(p)for p in sorted(source)}};target=root/'docs/runtime-environment/transport-allocation-current-source.json'
if '--check'in sys.argv:assert json.loads(target.read_text())==data,'Current transport source manifest changed';print('PASS',len(source),'current source/evidence hashes')
else:target.write_text(json.dumps(data,indent=2)+'\n');print('Bound',len(source),'current source/evidence hashes')
