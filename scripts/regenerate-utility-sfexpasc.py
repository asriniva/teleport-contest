from pathlib import Path
import subprocess,json,re
import argparse
parser=argparse.ArgumentParser();parser.add_argument('--out',required=True,type=Path);parser.add_argument('--source-root',type=Path);args=parser.parse_args();code_root=Path(__file__).resolve().parents[1];w=args.out.resolve();r=(args.source_root or code_root).resolve();subprocess.run(['python3',str(code_root/'scripts/lower-utility-sfexpasc.py'),'--out',str(w),'--source-root',str(r)],check=True);p=w/'candidate/sfexpasc.js';s=p.read_text();c=(r/'nethack-c/upstream/util/sfexpasc.c').read_text();data={}
for name in ['exportascii_sfo_procs','exportascii_sfi_procs']:
 b=re.search(r'struct sf_fieldlevel_procs '+name+r' = \{([\s\S]*?)\n\};',c)[1];b=re.sub(r'/\*[\s\S]*?\*/','',b);data[name]={'ext':re.search(r'"([^"]*)"',b)[1],'fn_x':re.findall(r'\b(?:sfo_x_|sfi_x_|exportascii_sfo_|exportascii_sfi_)\w+',b)}
s=s.replace("import {C} from '../../ported/c-runtime.js';\n", "import {C} from '../../ported/c-runtime.js';\n"+''.join('export const '+k+' = '+json.dumps(v)+';\n'for k,v in data.items()));p.write_text(s)
