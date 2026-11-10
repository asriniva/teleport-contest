"""Read-only configured END inventory, provenance, data and ABI-source guards."""
from pathlib import Path
import ast,hashlib,json,re,subprocess
r=Path(__file__).resolve().parents[3];prepared=r/'.cache/wasm64-build/tree/src/end.c';pristine=r/'nethack-c/upstream/src/end.c';source=prepared.read_text();core=(r/'js/ported/end.js').read_text();runtime=(r/'js/ported/end-runtime.js').read_text();library=(r/'nethack-c/wasm/tu-libraries/end.js').read_text();support=(r/'nethack-c/wasm/tu-fragments/end-support.inc').read_text();layout=(r/'scripts/tu-end-layout.h').read_text()
assert hashlib.sha256(prepared.read_bytes()).hexdigest()=='9190178742d65ea579645cfa365573a1c3f59cff7a5504856631c42a0c169296','Review changed prepared END source'
assert hashlib.sha256(pristine.read_bytes()).hexdigest()=='86076b732d630a31f1c596548631f1af8d033f2aa8bb5987daa53eb0bc02a424','Review changed pristine END source'
comments=re.findall(r'/\*.*?\*/',source,re.S);assert len(comments)==231
for comment in set(comments):assert source.count(comment)==core.count(comment),('Original END comment multiplicity changed',comment)
functions=['done1','done2','done_intr','done_hangup','done_in_by','fixup_death','panic','should_query_disclose_option','dump_everything','disclose','savelife','get_valuables','sort_valuables','done_object_cleanup','artifact_score','fuzzer_savelife','done','really_done','container_contents','nh_terminate','delayed_killer','find_delayed_killer','dealloc_killer','save_killers','restore_killers','wordcount','bel_copy1','build_english_list','NH_abort'];assert re.findall(r'export function (\w+)\(',core)==functions
# Only the necessary JS reserved-word spelling in_ differs from original parameters.
expected={'done1':['sig_unused'],'done2':[],'done_intr':['sig_unused'],'done_hangup':['sig'],'done_in_by':['mtmp','how'],'fixup_death':['how'],'panic':['str'],'should_query_disclose_option':['category','defquery'],'dump_everything':['how','when'],'disclose':['how','taken'],'savelife':['how'],'get_valuables':['list'],'sort_valuables':['list','size'],'done_object_cleanup':[],'artifact_score':['list','counting','endwin'],'fuzzer_savelife':['how'],'done':['how'],'really_done':['how'],'container_contents':['list','identified','all_containers','reportempty'],'nh_terminate':['status'],'delayed_killer':['id','format','killername'],'find_delayed_killer':['id'],'dealloc_killer':['kptr'],'save_killers':['nhfp'],'restore_killers':['nhfp'],'wordcount':['p'],'bel_copy1':['inp','out'],'build_english_list':['in_'],'NH_abort':['why']}
for name,params in expected.items():assert re.search(r'export function '+name+r'\(([^)]*)\)',core)[1]==', '.join(params),('END parameter names',name)
clean=lambda s:re.sub(r'/\*.*?\*/|//[^\n]*','',s,flags=re.S)
for name in ['deaths','ends']:
 c=re.search(r'\b'+name+r'\[\] = \{(.*?)\};',clean(source),re.S)[1];j=re.search(r'export const '+name+r' = \[(.*?)\];',clean(core),re.S)[1]
 assert re.findall(r'"(?:\\.|[^"\\])*"',c)==re.findall(r'"(?:\\.|[^"\\])*"',j),('END table',name)
assert re.findall(r'why: "(\w+)"',core)==['STONING','STARVING'];assert 'Schroedingers_cat:0,aborting:0' in runtime
literals=sorted(set(['end.c'])|set(ast.literal_eval(s)for s in re.findall(r'"(?:\\.|[^"\\])*"',clean(source))));actual=json.loads(re.search(r'sourceLiterals=new Set\((\[[^\n]*\])\)',library)[1]);assert actual==literals;capacity=sum(len(x.encode())+1 for x in literals);assert f'teleport_end_literals[{capacity}]'in support
assert '!sourceLiterals.has(v)'in library
# Preserve direct original RNG order and physical source origins, excluding #if0 function.
sites=[];fn=''
for line,text in enumerate(source.splitlines(),1):
 m=re.match(r'^(\w+)\(',text)
 if m:fn=m[1]
 if fn=='odds_and_ends':continue
 for m in re.finditer(r'\b(rn2|d)\(',text):sites.append((m[1],line,fn))
actual=[]
for m in re.finditer(r'C\.(rn2|d)\(',core):
 pos=m.end();depth=1
 while depth:depth+=(core[pos]=='(')-(core[pos]==')');pos+=1
 origin=re.search(r',\s*(\d+),\s*"(\w+)"\s*$',core[m.end():pos-1]);assert origin;actual.append((m[1],int(origin[1]),origin[2]))
assert actual==sites,(actual,sites)
assert 'C.Strlen(pbuf, 1317, "really_done")' in core
assert 'Number(Boolean(C.Hallucination && C.canspotmon(mtmp)))'in core
assert 'Number(Boolean((how < C.GENOCIDED) && C.can_make_bones()))'in core
assert "emptygrave',{get:()=>out.flags,set:v=>out.flags=v}"in runtime
assert 'C.copyValuable(ltmp, list[i])' in core and 'C.copyValuable(list[j], list[j - 1])'in core
assert 'C.callLocal(container_contents,'in core and 'C.reference(() => p, value => p = value)'in core
assert not re.search(r'\b(?:done|really_done|get_valuables|disclose|savelife|artifact_score)\([^;]*\)\s*\{',support),'END policy in support'
assert 'fixture_exit'not in support and 'fixture_abort'not in support,'Test process interception leaked into production'
# Actual production command spelling: cwd src and basename end.c. No oracle basename filtering.
defs=json.loads((r/'nethack-c/wasm/compile-defines.json').read_text());base=[str(r/'.cache/emsdk/upstream/emscripten/emcc'),'-sMEMORY64=1',*[f'-D{x}'for x in defs],'-I'+str(r/'.cache/wasm64-build/tree/include'),'-I'+str(r/'.cache/ncurses-wasm64-build/include')]
macros=subprocess.check_output([*base,'-E','-dM','end.c'],cwd=prepared.parent,text=True)
for name,value in {'DUMPLOG':0,'SFCTOOL':0,'NO_SIGNAL':0,'UNIX':1,'HANGUPHANDLING':1,'PANICTRACE':1,'CRASHREPORT':1,'NOMUX_CAPTURE':1,'DEBUG':1}.items():assert bool(re.search(r'^#define '+name+r'\b',macros,re.M))==bool(value),('Review END profile',name)
assert re.search(r'^#define emptygrave flags$',macros,re.M)
macro_defs={m[1]:m[2].strip()for m in re.finditer(r'^#define (\w+(?:\([^\n]*?\))?)[ \t]*(.*)$',macros,re.M)}
for key,value in {'done_stopprint':'program_state.stopprint','Role_if(X)':'(gu.urole.mnum == (X))','Race_if(X)':'(gu.urace.mnum == (X))','SchroedingersBox(o)':'((o)->otyp == LARGE_BOX && (o)->spe == 1)','Has_contents(o)':'( (o)->cobj != (struct obj *) 0)','Is_container(o)':'((o)->otyp >= LARGE_BOX && (o)->otyp <= BAG_OF_TRICKS)','M_AP_TYPE(m)':'((m)->m_ap_type & M_AP_TYPMASK)','update_file(nhfp)':'((nhfp)->mode & (COUNTING | WRITING))','release_data(nhfp)':'((nhfp)->mode & FREEING)'}.items():assert macro_defs.get(key)==value,('END header macro changed',key,macro_defs.get(key))

configured_cpp=subprocess.check_output([*base,'-E','end.c'],cwd=prepared.parent,text=True)
assert re.search(r'debugcore\(\"end\.c\",\s*1\)',configured_cpp),'Production END filename spelling changed'
assert 'snprintf(origin,sizeof origin,\"%s:%d:%s\",f,l,n)'in (r/'scripts/tu-end-probe.c').read_text(),'Raw filename observations must not be basename-normalized'

tree=json.loads(subprocess.check_output([*base,'-fsyntax-only','-Xclang','-ast-dump=json','end.c'],cwd=prepared.parent,text=True));b=prepared.read_bytes();configured=[]
for node in tree['inner']:
 if node.get('kind')!='FunctionDecl' or not any(c.get('kind')=='CompoundStmt'for c in node.get('inner',[])):continue
 name=node['name'];offset=node.get('loc',{}).get('offset',-1)
 if offset<0 or b[offset:offset+len(name)]!=name.encode():continue
 configured.append(name);actual=[c['name']for c in node.get('inner',[])if c.get('kind')=='ParmVarDecl'];actual=['in_'if p=='in'else p for p in actual];assert actual==expected[name],('Changed configured source parameters',name,actual)
assert configured==functions,('Changed actual configured END inventory',configured)

assert 'return i==0?WIZARD_NAME:i==1?plur(1):plur(2)'in support
assert 'Review changed END configured profile'in layout
print(f'END metadata:29 functions/231 original comments,15public+14private,16+16+2 tables,{len(literals)} strings/{capacity} bytes,{len(sites)} RNG origins; prepared patches/profile/aliases/auto storage guarded.')
