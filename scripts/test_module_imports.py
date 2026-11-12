"""Rebase imports for private wrong-code candidates; never alter the oracle."""
from pathlib import Path
import re

def rebase_test_module(source, owner, redirects=None):
    redirects=redirects or {}
    def replace(match):
        target=(Path(owner).parent/match[3]).resolve()
        destination=redirects.get(target,target.as_uri())
        return match[1]+match[2]+str(destination)+match[2]
    return re.sub(r'''(\bfrom\s*|\bimport\s*)(['"])(\.[^'"\n]+)\2''',replace,source)
