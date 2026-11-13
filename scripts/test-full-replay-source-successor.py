#!/usr/bin/env python3
"""Reject unrelated source/patch changes in the development-only inverse."""
import pathlib
import subprocess
import tempfile
from full_replay_source_successor import FILES, BASE_COMMIT, validate_cohort, qualified_before

root = pathlib.Path(__file__).resolve().parents[1]
images = validate_cohort(root)
checks = 0
with tempfile.TemporaryDirectory(prefix='full-replay-inverse-') as directory:
    private = pathlib.Path(directory)
    git = subprocess.check_output(['git', 'rev-parse', '--absolute-git-dir'], cwd=root, text=True).strip()
    (private / '.git').write_text('gitdir: ' + git + '\n')
    for file, row in FILES.items():
        for path in [file, row['patch']]:
            dest = private / path
            dest.parent.mkdir(parents=True, exist_ok=True)
            dest.write_bytes((root / path).read_bytes())
    assert validate_cohort(private) == images
    checks += 1
    for file, row in FILES.items():
        expected = subprocess.check_output(['git', 'show', BASE_COMMIT + ':' + file], cwd=root)
        assert qualified_before(private, file) == expected
        checks += 1
        for path in [file, row['patch']]:
            target = private / path
            original = target.read_bytes()
            target.write_bytes(original + b'\n// unrelated mutation\n')
            try:
                validate_cohort(private)
            except AssertionError:
                checks += 1
            else:
                raise AssertionError('Accepted unrelated modification: ' + path)
            finally:
                target.write_bytes(original)
    try:
        qualified_before(private, 'js/ported/hack.js')
    except AssertionError:
        checks += 1
    else:
        raise AssertionError('Accepted an undeclared policy source')
print(f'PASS {checks} full-replay predecessor/patch/cohort and rejection controls; not game acceptance')
