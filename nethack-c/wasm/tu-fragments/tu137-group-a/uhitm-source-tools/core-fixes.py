s=re.sub(r'\benum monnums\s+', 'let ',s)
# Source-specific ABI/storage translations; original policy remains in generated JS.
def codes(text, fn):
 pieces=re.split(r'(/\*UHITM_COMMENT_\d+\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\')',text)
 for j in range(0,len(pieces),2):pieces[j]=fn(pieces[j])
 return ''.join(pieces)
s=s.replace('&C.gy.youmonst','C.gy.youmonst').replace('&C.u.uz','C.u.uz')
s=re.sub(r'&C\.mons\[([^]]+)\]',r'C.mons[\1]',s)
s=re.sub(r'&C\.levl\[([^]]+)\]\[([^]]+)\]',r'C.levl[\1][\2]',s)
s=s.replace('&(ptr.mattk[i])','ptr.mattk[i]')
s=s.replace('&hmd.mdat','C.fieldRef(hmd, "mdat")').replace('&hmd.dmg','C.fieldRef(hmd, "dmg")').replace('&mhm.damage','C.fieldRef(mhm, "damage")')
s=s.replace('&mdef.minvent','C.fieldRef(mdef, "minvent")').replace('&otmp.nobj','C.fieldRef(otmp, "nobj")')
s=s.replace('&C.svr.rooms[*p - C.ROOMOFFSET]','C.svr.rooms[C.byte(p).value - C.ROOMOFFSET]')
s=s.replace('coord save_bhitpos = C.gb.bhitpos;','const save_bhitpos = C.localRecord("struct nhcoord"); C.copyRecord(save_bhitpos, C.gb.bhitpos);')
s=s.replace('save_bhitpos = C.gb.bhitpos;', 'C.copyRecord(save_bhitpos, C.gb.bhitpos);')
s=s.replace('C.gb.bhitpos = save_bhitpos','C.copyRecord(C.gb.bhitpos, save_bhitpos)')
s=s.replace('struct attack alt_attk;', 'const alt_attk = C.localRecord("struct attack");')
s=s.replace('struct attack *mattk, alt_attk;', 'let mattk; const alt_attk = C.localRecord("struct attack");')
s=s.replace('alt_attk = *mattk','C.copyRecord(alt_attk, mattk)')
s=re.sub(r'\b(struct (?:_hitmon_data|mhitm_data|attack|edog|mextra|obj|monst|permonst|rm))\s*\*\s*', 'let ',s)
s=re.sub(r'\bconst struct permonst\s*\*\s*','let ',s)
s=s.replace('let mattk, alt_attk;', 'let mattk; const alt_attk = C.localRecord("struct attack");')
s=s.replace('let weapon, **originalweapon;', 'let weapon, originalweapon;')
s=s.replace('let weapon, *originalweapon;', 'let weapon, originalweapon;')
s=s.replace('let otmp, **minvent_ptr;', 'let otmp, minvent_ptr;').replace('let otmp, *minvent_ptr;', 'let otmp, minvent_ptr;')
s=re.sub(r'\((?:struct (?:_hitmon_data|mhitm_data|attack|obj|monst|permonst)|coord)\s*\*\s*\)\s*','',s)
s=s.replace('const struct permonst','let')
s=re.sub(r'\blet\s+\*','let ',s)
s=s.replace('sizeof from_your_blow','30').replace('sizeof(silverobjbuf)','256').replace('sizeof buf','256').replace('C.sizeof(silverobjbuf)','256')
s=re.sub(r'\bsizeof (?:magrbuf|mdefbuf|fmtbuf)\b','256',s)
s=s.replace('&fmtbuf[i]','(fmtbuf + i)')
for n in ['hmd','mhm','alt_attk']:s=re.sub(r'&'+n+r'\b',n,s)
# Persistent source-owned storage is initialized once per Module in the adapter.
s=s.replace('static boolean clockwise = 0;', '')
s=codes(s,lambda t:re.sub(r'(?<![\w.])clockwise\b','C.cleave_clockwise',t))
s=s.replace('static char msgbuf[C.BUFSZ];','const msgbuf = C.gulpum_msgbuf;')
s=s.replace('static char generic = "a monster";','const generic = C.mimic_generic;')
s=s.replace('static char generic[] = "a monster";','const generic = C.mimic_generic;')
# Dereferenced pointer parameters and byte-pointer contents preserve actual aliases.
for n in ['attk_count','role_roll_penalty','mhit','hitflags','mptr','originalweapon','minvent_ptr']:
 s=re.sub(r'(?<![\w])\*'+n+r'\b',n+'.value',s)
for n in ['p','whom','buf']:s=re.sub(r'(?<![\w])\*'+n+r'\b','C.byte('+n+').value',s)
s=s.replace('++p','++p') # actual char-pointer stride is one byte
# Real native addressable cells for locals passed by address.
for index,f in reversed(list(enumerate(F))):
 start=s.index('export function '+f['name']+'(');end=s.index('export function '+F[index+1]['name']+'(')if index+1<len(F)else len(s);body=s[start:end]
 addr=[]
 def visit(n):
  if n.get('kind')=='UnaryOperator'and n.get('opcode')=='&':
   c=n.get('inner',[{}])[0]
   if c.get('kind')=='DeclRefExpr'and c.get('referencedDecl',{}).get('kind')in['VarDecl','ParmVarDecl']:
    d=c['referencedDecl'];typ=d['type'].get('desugaredQualType',d['type']['qualType'])
    if not typ.startswith(('struct ','union '))or'*'in typ:addr.append((d['name'],typ))
  for c in n.get('inner',[]):visit(c)
 visit(f)
 for name,typ in sorted(set(addr)):
  if '['in typ:continue
  if name in ['uwep','uswapwep','uarmg']:
   body=body.replace('&C.'+name,'C.globalRef("'+name+'")');continue
  placeholder='UHITMREF_'+name
  body=body.replace('&'+name,placeholder)
  body=codes(body,lambda t:re.sub(r'(?<![\w.])'+name+r'\b',name+'.value',t))
  body=body.replace(placeholder,name)
  pars={p['name']for p in f.get('inner',[])if p.get('kind')=='ParmVarDecl'}
  if name in pars:
   body=body.replace('{\n','{\n    '+name+' = C.localScalar('+json.dumps(typ)+', '+name+');\n',1)
 # Split native comma-declaration groups without changing initializer order.
 typed=dict(addr)
 def declaration(m):
  text=m[1];chunks=[];last=0;depth=0
  for z,c in enumerate(text):
   depth+=(c in '([{')-(c in ')]}')
   if c==',' and depth==0:chunks.append(text[last:z]);last=z+1
  chunks.append(text[last:]);out=[]
  for chunk in chunks:
   chunk=chunk.strip();notes=''.join(re.findall(r'/\*UHITM_COMMENT_\d+\*/',chunk));clean=re.sub(r'/\*UHITM_COMMENT_\d+\*/','',chunk).strip();clean=re.sub(r'^\*+','',clean)
   v=re.match(r'(\w+)\.value(?:\s*=\s*(.*))?$',clean,re.S)
   if v and v[1]in typed:out.append(notes+' const '+v[1]+' = C.localScalar('+json.dumps(typed[v[1]])+', '+(v[2]or'0')+');')
   else:out.append(notes+' let '+re.sub(r'^(\w+)\.value(?=\s*(?:=|$))',r'\1',clean)+';')
  return ''.join(out)
 body=re.sub(r'\blet\s+([^;]+);',declaration,body)
 s=s[:start]+body+s[end:]
# Array storage remains native and supports pointer projection.
for item in automatic:
 typ=item['type'].get('desugaredQualType',item['type']['qualType'])
 if typ.startswith('char['):
  name=item['name'];s=codes(s,lambda t:re.sub(r'(?<![\w.])'+name+r'\[([^]\n]+)\]',lambda m:'C.byte('+name+' + ('+m[1]+')).value',t))
s=s.replace('&sum[i]','C.arrayRef(sum, i)')
# rn1's first RNG must occur before its offset expression.
at=0
while(m:=re.search(r'C\.rn1\(',s[at:])):
 start=at+m.start();op=start+len('C.rn1');end=group(s,op);args=s[op+1:end-1];depth=0;comma=None
 for i,c in enumerate(args):
  depth+=(c in'([')-(c in')]')
  if c==','and depth==0:comma=i;break
 assert comma is not None,args
 expr='(C.rn2('+args[:comma]+') + ('+args[comma+1:].strip()+'))';s=s[:start]+expr+s[end:];at=start+len(expr)
at=0
while(m:=re.search(r'C\.Maybe_Half_Phys\(',s[at:])):
 start=at+m.start();op=start+len('C.Maybe_Half_Phys');end=group(s,op);expr=s[op+1:end-1]
 replacement='(C.Half_physical_damage ? Math.trunc(('+expr+' + 1) / 2) : '+expr+')';s=s[:start]+replacement+s[end:];at=start+len(replacement)
# Source-local macro consumes the exact original branch, including object clearing.
s=s.replace('C.useup_eggs(obj)', 'do { if (hmd.thrown) C.obfree(obj, 0); else C.useupall(obj); obj = 0; } while (0)')
# Shared forward tail retains the original single body.
a=s.index('export function do_attack(');b=s.index(' atk_done:',a);i=s.index('    if (C.Upolyd && C.noattacks',a)
s=s[:i]+'    atk_done: {\n'+s[i:b].replace('goto atk_done;','break atk_done;')+'    }\n'+s[b+len(' atk_done:'):]
# Cross-branch joins use one explicit dispatcher flag, retaining original branch order.
for fname,label in [('mhitm_ad_famn','mhitm_famn'),('mhitm_ad_pest','mhitm_pest'),('mhitm_ad_deth','mhitm_deth'),('mhitm_ad_dise','mhitm_dise')]:
 a=s.index('export function '+fname+'(');end=s.find('export function ',a+1);end=len(s)if end<0 else end;body=s[a:end]
 target=body.index(' '+label+':');el=body.rfind('    } else {',0,target);op=body.index('{',el);close=group(body,op,'{','}')
 tail=body[target+len(' '+label+':'):close-1];body=body[:el]+'    } else {\n        '+label+'_target = 1;\n    }\n    if ('+label+'_target) {'+tail+'    }'+body[close:]
 body=body.replace('goto '+label+';',label+'_target = 1;').replace('{\n','{\n    let '+label+'_target = 0;\n',1)
 s=s[:a]+body+s[end:]
# post_stone may be entered after munstone OR monstone, before the final default damage.
a=s.index('export function do_stone_mon(');end=s.index('export function mhitm_ad_phys(',a);body=s[a:end]
i=body.index('    if (C.munstone');target=body.index(' post_stone:');el=body.rfind('    if (!C.resists_ston',0,target);op=body.index('{',el);close=group(body,op,'{','}')
pre=body[i:target].replace('goto post_stone;', 'break post_stone_dispatch;')
tail=body[target+len(' post_stone:'):close-1]
body=body[:i]+'    let post_stone_target = 1;\n    post_stone_dispatch: {\n'+pre+'    } else { post_stone_target = 0; }\n    }\n    if (post_stone_target) {'+tail+'    }'+body[close:]
s=s[:a]+body+s[end:]
# hmonas switch re-entry: one original weapon arm and one original passive tail.
a=s.index('export function hmonas(');end=s.index('export function passive(',a);body=s[a:end]
i=body.index('    for (i = 0;',body.index('    for (i = 0;')+1);body=body[:i]+'    attack_loop: '+body[i+4:]
i=body.index('        switch (mattk.aatyp)');op=body.index('{',i);close=group(body,op,'{','}')
dispatch=body[i:close].replace('switch (mattk.aatyp)','switch (attack_case)')
dispatch=dispatch.replace(' use_weapon:','').replace('goto use_weapon;','{ attack_case = C.AT_WEAP; continue attack_dispatch; }').replace('goto passivedone;','break passivedone;').replace('continue;','continue attack_loop;')
# Preserve newly introduced dispatch continue after transforming original continues.
dispatch=dispatch.replace('continue attack_dispatch;', 'continue attack_dispatch;')
body=body[:i]+'        passivedone: {\n        let attack_case = mattk.aatyp;\n        attack_dispatch: while (1) {\n'+dispatch+'\n        break;\n        }\n'+body[close:]
body=body.replace(' passivedone:','        }',1)if False else body
# Only source label has one leading blank; introduced wrapper has eight.
body=body.replace('\n passivedone:', '\n        }')
s=s[:a]+body+s[end:]
s=s.replace('C.256','256')
s=re.sub(r'\bconst (?:int|boolean|long|unsigned|uchar|coordxy)\s+', 'const ',s)
s=s.replace('(int *) 0','0')

# Actual configured assert expansion retains original file/line/expression/function.
for line in [1873,1888]:
 s=s.replace('C.assert(obj != 0);','if (!(obj != 0)) C.__assert_fail("obj != NULL", "uhitm.c", '+str(line)+', "hmon_hitmon");',1)
s=s.replace('C.assert(mndx >= C.LOW_PM && mndx <= C.HIGH_PM);','if (!(mndx >= C.LOW_PM && mndx <= C.HIGH_PM)) C.__assert_fail("mndx >= LOW_PM && mndx <= HIGH_PM", "uhitm.c", 6247, "that_is_a_mimic");')
# Native field character arrays are address-valued, with byte lvalues at indexing sites.
s=codes(s,lambda t:re.sub(r'(?<![\w.])([A-Za-z_]\w*(?:\.\w+)*\.(?:saved_oname|name))\[([^]\n]+)\]',lambda m:'C.byte('+m[1]+' + ('+m[2]+')).value',t))
# C min/max macros evaluate the selected operand again; never eager helper arguments.
for macro,comparison in [('min','<'),('max','>')]:
 at=0
 while(m:=re.search(r'C\.'+macro+r'\(',s[at:])):
  start=at+m.start();op=start+len('C.'+macro);end=group(s,op);args=s[op+1:end-1];depth=0;comma=None
  for i,c in enumerate(args):
   depth+=(c in'([')-(c in')]')
   if c==','and depth==0:comma=i;break
  assert comma is not None,args
  x,y=args[:comma],args[comma+1:];expr='(('+x+') '+comparison+' ('+y+') ? ('+x+') : ('+y+'))';s=s[:start]+expr+s[end:];at=start+len(expr)

def callee(n):
 while n.get("inner"):n=n["inner"][0]
 return n.get("referencedDecl",{}).get("name")
# Hidden Snprintf source metadata comes from its actual compiler macro calls.
def snprintf_origins(n, out):
    if n.get('kind') == 'CallExpr' and callee(n['inner'][0]) == 'nh_snprintf':
        values = []
        for arg in n['inner'][1:3]:
            while arg.get('inner'):
                arg = arg['inner'][0]
            values.append(arg['value'])
        out.append((values[0].strip('"'), int(values[1])))
    for child in n.get('inner', []):
        snprintf_origins(child, out)
origin_list = []
for f in F:
    snprintf_origins(f, origin_list)
matches = list(re.finditer(r'C.Snprintf\(', s))
assert len(matches) == len(origin_list), (len(matches), origin_list)
for match, (fn, line) in reversed(list(zip(matches, origin_list))):
    s = s[:match.end()]+json.dumps(fn)+', '+str(line)+', '+s[match.end():]

s=s.replace('C.DISABLE_WARNING_FORMAT_NONLITERAL','').replace('C.RESTORE_WARNING_FORMAT_NONLITERAL','')

# Clang actual unsigned-int arithmetic: wrap before divide; then narrow signed local.
s=s.replace('hmd.dmg = (obj.owt + 99) / 100;', 'hmd.dmg = C.uint(obj.owt + 99) / 100;')
s=s.replace('let nopoison = (10 - (obj.owt / 10));', 'let nopoison = C.int(C.uint(10 - (obj.owt / 10)));')
s=s.replace('pd.cwt >> 8', 'pd.cwt >>> 8')
