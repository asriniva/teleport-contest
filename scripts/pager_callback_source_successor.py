"""Exact pager callback inverse; current tests execute production source."""
from pathlib import Path
import argparse,subprocess,sys
from monster_view_source_successor import validate_bytes
FILE='js/nethack/pager-lookup.js'
BASE='3b6db96'
ROW={'beforeSha256': '4cf2851f6403a8932e5262be18476d5b6b015dc2c9a88f640abaa003f2733732', 'afterSha256': 'b9394076a4b1534f1fc731f3ccf2b2d6cab2f94bac90224d1f369fee80e95c58', 'patch': 'docs/runtime-environment/pager-callback-source.patch', 'patchSha256': 'dddc8e127e61b6038fbd60052ec89adba55b4b2bd463d0e5d07518cfbe918535'}
def qualified_before(root,file):
 assert file==FILE,'Unowned pager source'
 root=Path(root);before=subprocess.check_output(['git','show',BASE+':'+FILE],cwd=root)
 return validate_bytes(before,(root/file).read_bytes(),(root/ROW['patch']).read_bytes(),ROW,file)
if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('--file',required=True);a=p.parse_args()
 sys.stdout.buffer.write(qualified_before(Path(__file__).resolve().parents[1],a.file))
