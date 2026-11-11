"""Source-faithful UHITM translation, original order/comments kept; no native policy."""
from pathlib import Path
import ast,json,re,subprocess,os
TOOLS=Path(__file__).resolve().parent;W=Path('.cache/uhitm-author');src=Path('.cache/wasm64-build/tree/src/uhitm.c').read_text();F=json.loads((W/'functions.json').read_text());names=[f['name']for f in F]
# Carry caller metadata directly from original token positions before translation;
# nested macro branches duplicate these explicit expressions exactly as native CPP.
masked=re.sub(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'',lambda m:' '*len(m[0]),src,flags=re.S)
insertions=[]
for m in re.finditer(r'\b(rn2|rn1|rnd|d|rnl)\s*\(',masked):
 fn=next((f for f in F if f['range']['begin'].get('expansionLoc',f['range']['begin'])['offset']<=m.start()<=f['range']['end'].get('expansionLoc',f['range']['end'])['offset']),None)
 if not fn:continue
 at=m.end();depth=1
 while depth:depth+=(masked[at]=='(')-(masked[at]==')');at+=1
 insertions.extend([(m.start(),'(rngSource('+str(src[:m.start()].count('\n')+1)+', '+str(names.index(fn['name']))+'), '),(at,')')])
for at,text in sorted(insertions,reverse=True):src=src[:at]+text+src[at:]
comments=[]
def comment(m):comments.append(m[0]);return '/*UHITM_COMMENT_'+str(len(comments)-1)+'*/'
s=re.sub(r'/\*.*?\*/|//[^\n]*',comment,src,flags=re.S)
# Actual configured source has two #if 0 experiments and source-local macros.
lines=s.splitlines(True);out=[];active=True;i=0
while i<len(lines):
 line=lines[i];i+=1
 while line.rstrip().endswith('\\') and i<len(lines):line=line.rstrip()[:-1]+lines[i];i+=1
 if re.match(r'\s*#if 0\b',line):
  active=False;out.extend(c+'\n'for c in re.findall(r'/\*UHITM_COMMENT_\d+\*/',line))
 elif re.match(r'\s*#endif',line):
  active=True;out.extend(c+'\n'for c in re.findall(r'/\*UHITM_COMMENT_\d+\*/',line))
 elif not re.match(r'\s*#',line):out.append(line if active else ''.join(c+'\n'for c in re.findall(r'/\*UHITM_COMMENT_\d+\*/',line)))
 else:out.extend(c+'\n'for c in re.findall(r'/\*UHITM_COMMENT_\d+\*/',line))
s=''.join(out)
s=re.sub(r'(?m)^\s*staticfn[^;{}]+;','',s)
for f in F:
 pars=[p['name']for p in f.get('inner',[])if p.get('kind')=='ParmVarDecl'];name=f['name']
 m=re.search(r'(?m)^(?:staticfn\s+)?(?:const\s+)?(?:boolean|int|void|char\s*\*|struct obj\s*\*)\s*\n?'+name+r'\([^{}]*?\)\s*',s)
 assert m,name
 notes=''.join(re.findall(r'/\*UHITM_COMMENT_\d+\*/',m[0]));s=s[:m.start()]+notes+'\nexport function '+name+'('+', '.join(pars)+')\n'+s[m.end():]
locals_,refs=set(),{}
def scan(n):
 if n.get('kind')in['VarDecl','ParmVarDecl']:locals_.add(n['id'])
 if n.get('kind')=='DeclRefExpr':refs[n['referencedDecl']['name']]=n['referencedDecl']
 for c in n.get('inner',[]):scan(c)
for f in F:scan(f)
staticnames={n['name']for n in json.loads((W/'boundary-inventory.json').read_text())['staticVariables']}
external={name for name,d in refs.items()if d['id']not in locals_}-set(names)-staticnames
# Header object-like aliases remain explicit typed JS properties in the adapter.
external|=set('Blinded Invis See_invisible Something HJumping EJumping Jumping Conflict Protection_from_shape_changers ParanoidBreakwand levl fmon Blind Confusion Stunned Hallucination Deaf Underwater Glib Fumbling Sick HBlinded HStun HConfusion HHallucination HDeaf Vomiting BlindedTimeout Half_physical_damage Stoned Slimed Strangled Wounded_legs Punished Upolyd Ugender Luck Invisible Fire_resistance Passes_walls Unchanging Levitation Flying Swimming Wwalking Blindfolded Disint_resistance Free_action Antimagic Sleep_resistance Stone_resistance Breathless Amphibious see_invisible something nothing_happens nothing_seems_to_happen Never_mind'.split())
external |= {m[1] for m in re.finditer(r'^#define (\w+)', (W/'macros.txt').read_text(),re.M)} - staticnames - set(names)
def group(text,at,op='(',cl=')'):
 depth=1;at+=1
 while depth:depth+=(text[at]==op)-(text[at]==cl);at+=1
 return at
automatic=json.loads((W/'automatic-storage.json').read_text())
prefix=re.compile(r'(?<![\w.])(?:'+'|'.join(sorted(external,key=len,reverse=True))+r'|[A-Z][A-Z_0-9]+)\b')
parts=re.split(r'(/\*UHITM_COMMENT_\d+\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\')',s)
for i in range(0,len(parts),2):
 t=parts[i].replace('->','.')
 # All actual static data is readonly and source-owned, with native strings retained verbatim.
 t=re.sub(r'(?m)^(\s*)(?:static )?const char\s*\*const (\w+)\[\]\s*=\s*\{',r'\1const \2 = [',t)
 t=re.sub(r'(?m)^(\s*)(?:static )?const char\s+(\w+)\[\]\s*=',r'\1const \2 =',t)
 t=re.sub(r'(?m)^(\s*)(?:static )?const char\s*\n',r'\1const ',t)
 for name in staticnames|{'thump'}:t=t.replace(name+'[]',name)
 # Automatic arrays/records are real addressable ABI storage.
 for n in automatic:
  name=n['name'];typ=n['type'].get('desugaredQualType',n['type']['qualType'])
  if n['type']['qualType'].startswith('const '):continue
  if '['in typ:
   elem=typ.split('[')[0];count=int(typ.split('[')[1].split(']')[0]);t=re.sub(r'\b'+name+r'\[(?:BUFSZ|QBUFSZ|PROP_COUNT|NATTK|'+str(count)+r')\](?=\s*[,;])',name+' = '+('C.stackAlloc('+str(count)+')'if elem=='char'else'C.localArray('+json.dumps(elem)+', '+str(count)+')'),t)
  elif typ.startswith(('struct ','union '))and'*'not in typ:
   t=re.sub(r'(?m)^(\s*)'+re.escape(n['type']['qualType'])+r'\s+'+name+r'\s*;',r'\1const '+name+' = C.localRecord('+json.dumps(typ)+');',t)
 t=re.sub(r'(?m)^(\s*)(?:struct (?:obj|monst|permonst|trap|rm)\s*\*\s*|const char\s*\*\s*(?:const\s+)?|char\s*\*\s*|stairway\s*\*\s*|menu_item\s*\*\s*|coordxy\s+|coord\s+|xint16\s+|winid\s+|schar\s+|unsigned int\s+|unsigned\s+|boolean\s+|int\s+|long\s+|char\s+|enum digcheck_result\s+)',r'\1let ',t)
 t=re.sub(r'(\blet [^;]*?),\s*\*',r'\1, ',t)
 t=re.sub(r'(?m)^(\s*)anything any;',r'\1const any = C.localRecord("union any");',t)
 t=re.sub(r'\((?:struct (?:obj|monst|permonst|trap|rm) \*\s*\*?|const char \*|char \*|genericptr_t|genericptr|void)\)\s*','',t)
 t=re.sub(r'\(int \(\*\) \([^)]*\)\)\s*0','0',t)
 t=re.sub(r'\(struct obj \*\(\*\) \(struct obj \*\)\)','',t)
 kinds={'int':'int','unsigned':'uint','unsigned int':'uint','long':'long','char':'char','boolean':'boolean','schar':'char','coordxy':'short','uchar':'uchar'}
 while(m:=re.search(r'\((int|unsigned int|unsigned|long|char|boolean|schar|coordxy|uchar)\)\s*',t)):
  start=at=m.end()
  while t[at]in'!~+-* ':at+=1
  if t[at]=='(':at=group(t,at)
  else:
   n=re.match(r'[A-Za-z_]\w*|\d+',t[at:]);assert n,t[at:at+80];at+=len(n[0])
  while at<len(t):
   if t[at]=='.':at+=len(re.match(r'\.\w+',t[at:])[0])
   elif t[at]in'[(':at=group(t,at,t[at],']'if t[at]=='['else')')
   else:break
  t=t[:m.start()]+'C.'+kinds[m[1]]+'('+t[start:at]+')'+t[at:]
 t=t.replace('FALLTHROUGH;','').replace('UNUSED','').replace('VOICEONLY','')
 t=re.sub(r'\b(\d+)L\b',r'\1n',t)
 for a,b in[('TRUE','1'),('FALSE','0'),('NULL','0')]:t=re.sub(r'\b'+a+r'\b',b,t)
 t=re.sub(r'(?<![\w.])([A-Za-z_]\w*)(?=\()',lambda m:m[0]if m[0]in set(names)|{'if','for','while','switch','function','BigInt','Number','Boolean'}else'C.'+m[0],t)
 t=prefix.sub(lambda m:m[0]if m[0]=='C'else'C.'+m[0],t)
 t=t.replace('C.C.','C.')
 parts[i]=t
s=''.join(parts)
# Native preprocessing erases these calls and their arguments.
for macro in['Soundeffect','SetVoice','Hero_playnotes']:s=re.sub(r'C\.'+macro+r'\([^;]*\)','',s)
# Reconstitute adjacent source strings without damaging whitespace strings.
previous=None;inserts=[]
for token in re.finditer(r'/\*UHITM_COMMENT_\d+\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'',s):
 if token[0].startswith('/*'):continue
 if token[0].startswith('"')and previous is not None and re.fullmatch(r'(?:\s|/\*UHITM_COMMENT_\d+\*/)+',s[previous.end():token.start()]):inserts.append(previous.end())
 previous=token if token[0].startswith('"')else None
for at in reversed(inserts):s=s[:at]+' +'+s[at:]

# Additional type/lifetime/source-control fixes are maintained in one owned pass.
exec((TOOLS/'core-fixes.py').read_text())
# Every internal original call owns a native automatic-storage frame.
parts=re.split(r'(/\*UHITM_COMMENT_\d+\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\')',s)
for i in range(0,len(parts),2):
 for name in names:
  parts[i]=re.sub(r'(?<!function )(?<![\w.])'+name+r'\(','C.callLocal('+name+', ',parts[i]);parts[i]=parts[i].replace('C.callLocal('+name+', )','C.callLocal('+name+')')
s=''.join(parts)
s=re.sub(r'/\*UHITM_COMMENT_(\d+)\*/',lambda m:comments[int(m[1])],s)
parts=re.split(r'(/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\')',s,flags=re.S)
for i in range(1,len(parts),2):
 if parts[i].startswith('"'):
  parts[i]=re.sub(r'\\([0-7]{1,3})',lambda m:'\\x'+format(int(m[1],8),'02x'),parts[i])
 if parts[i].startswith("'"):
  v=ast.literal_eval(parts[i]);assert len(v)==1;parts[i]=str(ord(v))
s=''.join(parts)
output=Path(os.environ.get('UHITM_OUTPUT','js/ported/uhitm.js'))
output.write_text("import {C} from './c-runtime.js';\n"+s)
print('UHITM bodies',len(re.findall(r'export function ',s)),'comments',len(comments))
subprocess.check_call([str(Path(os.environ.get('EMSDK','.cache/emsdk'))/'node/24.19.0_64bit/bin/node'),str(TOOLS/'canonical-logicals.mjs'),str(output)])
subprocess.check_call([str(Path(os.environ.get('EMSDK','.cache/emsdk'))/'node/24.19.0_64bit/bin/node'),str(TOOLS/'integer-divisions.mjs'),str(output)])

subprocess.check_call([str(Path(os.environ.get('EMSDK','.cache/emsdk'))/'node/24.19.0_64bit/bin/node'),str(TOOLS/'integer-promotions.mjs'),str(output)])
