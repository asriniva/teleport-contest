// Shared storage/typed transport for unchanged artifact and hero-startup policy.
import abi from './hero-abi.json' with {type:'json'};
import * as uInit from '../ported/u_init.js';
import {createUInitBridge} from '../ported/u_init-runtime.js';
import {callPolyself} from '../ported/polyself-runtime.js';
import * as attrib from '../ported/attrib.js';
import {createAttribEnvironment} from '../ported/attrib-runtime.js';
import {valid_vampshiftform} from '../ported/mon.js';
import {resists_drli,dmgtype,dmgtype_fromattack} from '../ported/mondata.js';
import {newpw} from '../ported/exper.js';
import {init_uhunger} from '../ported/eat.js';
import {max_rank_sz} from '../ported/botl.js';
import {init_artifacts,hack_artifacts} from '../ported/artifact.js';
export function enableHeroStartup(environment,layouts,creation,inventory){
 const {services,ctypes,memory,transport}=environment,{views,context}=creation;
 const address=environment.address,record=(type,p)=>views.record(type,p),scalar=f=>f.ctype.slice(0,-f.ctype.match(/\s+\w+$/)[0].length);
 function location(type,at,path){for(const key of path.split('.')){const entry=ctypes.locate(type,at,key);at=entry.at;type=entry.field.record??scalar(entry.field);}return {at,type};}
 const named=(name,path='')=>path?location(ctypes.record('struct '+globalTypes[name]).type,environment.requireGlobal(name),path):{at:environment.requireGlobal(name),type:globalTypes[name]};
 const globalTypes={u:'you',gu:'instance_globals_u',gy:'instance_globals_y',svb:'instance_globals_saved_b',svs:'instance_globals_saved_s',svm:'instance_globals_saved_m',svc:'instance_globals_saved_c',svk:'instance_globals_saved_k',gl:'instance_globals_l',gn:'instance_globals_n',gm:'instance_globals_m',gw:'instance_globals_w',flags:'flag',disp:'display_hints',program_state:'sinfo',gi:'instance_globals_i',cg:'const_globals',gx:'instance_globals_x'};
 const foreign=()=>new Proxy(Object.create(services),{get:(o,k,r)=>Reflect.has(o,k)?Reflect.get(o,k,r):typeof k==='string'?(...args)=>environment.resolve(k)(...args):undefined});
 const shadow=(local,names)=>{for(const n of names)Object.defineProperty(local,n,{value:undefined,writable:true,configurable:true});return local;};
 const legacy=inventory.legacy;legacy.aligns=views.array('struct Align',environment.requireGlobal('aligns'),4);Object.defineProperty(legacy,'Role_switch',{get:()=>legacy.gu.urole.mnum});
 legacy.artidisco=views.array('short',environment.allocateGlobal('artidisco',layouts.artifact.NROFARTIFACTS*ctypes.size('short')),layouts.artifact.NROFARTIFACTS);
 Object.assign(legacy.sizes,{artidisco:layouts.artifact.NROFARTIFACTS*ctypes.size('short'),artiexist:(layouts.artifact.NROFARTIFACTS+1)*ctypes.size('struct arti_info')});
 environment.extend('artifact-properties',{init_artifacts,hack_artifacts});
 const ui=shadow(foreign(),['objects','svb','svs','aligns','cg','flags','gn','gl','svm','gu','gi','u']);
 const groupNames=Object.keys(abi.u_init.fields),groupTypes={obj:'obj',objclass:'objclass',you:'you',roleplay:'u_roleplay',level:'d_level',align:'align',weaponskill:'skills',skill:'def_skill',trobj:'trobj',invsub:'inv_sub'};
 const aliases={obj:{opoisoned:'otrapped'},objclass:{oc_skill:'oc_subtyp',oc_level:'oc_oc2'}};
 function field(group,index,p){const name=groupNames[group],key=abi.u_init.fields[name]?.[index];if(!key)throw new Error('Unknown U_INIT field '+group+':'+index);const type=groupTypes[name];if(type){const f=aliases[name]?.[key]??key;if(abi.records[type])return{at:address(p)+abi.records[type].fields[f].offset,type:scalar(abi.records[type].fields[f])};const entry=ctypes.locate(type,address(p),f);return{...entry,type:scalar(entry.field),record:type,key:f};}if(name==='globals')return key==='discover'?named('flags','explore'):{at:environment.requireGlobal(key),type:'long'};return named(name,key);}
 const tables=abi.u_init.tables.map(row=>environment.allocateGlobal('u_init.'+row.name,uInit[row.name].length*(row.typ==='trobj'?layouts.u_init.trobjSize:row.typ==='inv_sub'?layouts.u_init.invsubSize:layouts.u_init.skillSize)));
 const globalNames=['u','u.uroleplay','u.uz','u.uz0','u.utolev','u.ualign','ubirthday','urealtime','cg.zeroobj','flags','gn','gl','svm'];
 function member(kind,i){switch(kind){case 0:return{at:named('svb','bases').at+i*4,type:'int'};case 1:return location('spell',named('svs','spl_book').at+i*ctypes.size('struct spell'),'sp_id');case 2:return{at:named('u','ualignbase').at+i,type:'signed char'};case 3:return{at:named('u','ueninc').at+i*2,type:'short'};case 4:return location('Align',environment.requireGlobal('aligns')+i*ctypes.size('struct Align'),'value');default:throw new Error('Unknown U_INIT array '+kind);}}
 Object.assign(ui,{
  get:(g,f,p)=>{const e=field(g,f,p);return BigInt(e.record?ctypes.getField(e.record,address(p),e.key,e.type):ctypes.load(e.type,e.at));},
  set:(g,f,p,v)=>{const e=field(g,f,p);return e.record?ctypes.setField(e.record,address(p),e.key,e.type,v):ctypes.store(e.type,e.at,v);},
  address:i=>{const path=globalNames[i];if(!path)throw new Error('Unknown U_INIT global '+i);const [name,...keys]=path.split('.');return keys.length?named(name,keys.join('.')).at:environment.requireGlobal(name);},
  arrayGet:(k,i)=>{const e=member(k,i);return BigInt(ctypes.load(e.type,e.at));},arraySet:(k,i,v)=>{const e=member(k,i);ctypes.store(e.type,e.at,v);},
  element:(k,i)=>k===0?environment.requireGlobal('objects')+i*ctypes.size('struct objclass'):named('u','weapon_skills').at+i*ctypes.size('struct skills'),
  invent:()=>ctypes.load('struct obj *',named('gi','invent').at),table:i=>tables[i],
  equipment:i=>ctypes.load('struct obj *',environment.requireGlobal(['uarms','uwep','uarmh','uarmg','uarmu','uarmc','uarmf','uarm','uquiver','uswapwep'][i])),
  intrinsic:i=>views.record('struct you',environment.requireGlobal('u')).uprops[layouts.polyself[i?'BLINDED':'JUMPING']].intrinsic,
  setIntrinsic:(i,v)=>{views.record('struct you',environment.requireGlobal('u')).uprops[layouts.polyself[i?'BLINDED':'JUMPING']].intrinsic=v;},
  rn2:(n,line,caller)=>{if(services.rng_log_enabled())services.rng_log_set_caller(services.literal('u_init.c'),line,services.literal(caller));return services.rn2(n);},
 });
 const bridge=createUInitBridge(layouts.u_init);environment.register('hero-init',Object.fromEntries(['u_init_misc','skills_for_role','u_init_inventory_attrs'].map(name=>[name,(...args)=>bridge(ui,name,...args)])));
 const poly=foreign(),polyNames=Object.keys(abi.polyself.schema);
 function polyField(kind,p,index){const type=polyNames[kind],f=abi.polyself.schema[type]?.fields[index];if(!f)throw new Error('Unknown POLYSELF field');return{type,f,p:address(p)};}
 Object.assign(poly,{
  global:i=>environment.requireGlobal(abi.polyself.globals[i].name),
  read:(k,p,i)=>{const e=polyField(k,p,i);return ctypes.getField(e.type,e.p,e.f.name,e.f.ctype);},
  write:(k,p,i,v)=>{const e=polyField(k,p,i);return ctypes.setField(e.type,e.p,e.f.name,e.f.ctype,v);},
  address:(k,p,i)=>{const e=polyField(k,p,i);return ctypes.locate(e.type,e.p,e.f.name).at;},
 });
 const mon=context(layouts.mon);mon.is_vampire=p=>Number(p.mlet===mon.S_VAMPIRE);environment.register('hero-vampire-form',{valid_vampshiftform},mon);
 const biology=context(layouts.mondata);Object.defineProperty(biology,'gy',{value:record('struct instance_globals_y',environment.requireGlobal('gy'))});
 Object.assign(biology,{is_undead:p=>Number(Boolean(p.mflags2&BigInt(layouts.mondata.M2_UNDEAD))),is_were:p=>Number(Boolean(p.mflags2&BigInt(layouts.mondata.M2_WERE))),is_vampshifter:m=>Number([mon.PM_VAMPIRE,mon.PM_VAMPIRE_LEADER,mon.PM_VLAD_THE_IMPALER].includes(m.cham)),
  objectLocal:()=>record('struct obj',transport.stackAlloc(ctypes.size('struct obj'))),copyObject:(a,b)=>memory.memmove(address(a),address(b),ctypes.size('struct obj')),
  attackBefore:(a,b)=>address(a)<address(b),attackNext:a=>views.advance(a,1),
 });
 for(const key of ['uarm'])Object.defineProperty(biology,key,{get:()=>record('struct obj',ctypes.load('struct obj *',environment.requireGlobal(key)))});
 environment.register('hero-monster-resistance',{resists_drli,dmgtype,dmgtype_fromattack},biology,{prepareArgs:(fn,args)=>{args[0]=record(fn==='resists_drli'?'struct monst':'struct permonst',args[0]);return args;}});
 environment.register('hero-form',{set_uasmon:(...args)=>callPolyself(poly,layouts.polyself,'set_uasmon',...args)});
 const a=shadow(foreign(),['u','gu','gy','gi','svm','gm','svc','svk','flags','program_state','disp','mons','aligns','objects']);
 const ag=['u','gu.urole','gu.urace','gy.youmonst','gi.invent','svm.moves','gm.multi','svc.context.next_attrib_check','svk.killer.format','svk.killer.name','flags.initalign','flags.verbose','program_state.in_moveloop',null,'mons','aligns'];
 const count=Object.keys(attrib).filter(k=>Array.isArray(attrib[k])&&/_abil$/.test(k)).reduce((n,k)=>n+attrib[k].length,0),at=environment.allocateGlobal('attrib.innates',count*layouts.attrib.innateSize),names=environment.allocateGlobal('attrname',attrib.attrname.length*8),from=environment.allocateGlobal('attrib.fromWhat',256);
 Object.assign(a,{global:i=>{const path=ag[i];if(!path)throw new Error('Unknown ATTRIB global '+i);const [name,...fields]=path.split('.');return fields.length?named(name,fields.join('.')).at:environment.requireGlobal(name);},tableStorage:()=>at,tableCount:()=>count,attrnameStorage:()=>names,fromWhatBuffer:()=>from,heroData:()=>record('struct instance_globals_y',environment.requireGlobal('gy')).youmonst.data.address,
  botl:()=>record('struct display_hints',environment.requireGlobal('disp')).botl,setBotl:v=>{record('struct display_hints',environment.requireGlobal('disp')).botl=v;},
  roleplayBit:i=>record('struct you',environment.requireGlobal('u')).uroleplay[i?'deaf':'blind'],
 });
 for(const kind of ['rn2','rnd','rn1','d'])a[kind]=(...args)=>{const caller=args.pop(),line=args.pop();if(services.rng_log_enabled())services.rng_log_set_caller(services.literal('attrib.c'),line,services.literal(caller));return services[kind](...args);};
 a.assert=ok=>{if(!ok)environment.resolve('__assert_fail')(services.literal('chridx >= 0 && chridx < A_MAX'),services.literal('attrib.c'),1204,services.literal('acurr'));};
 const attr=createAttribEnvironment(a,layouts.attrib,attrib);environment.register('hero-attributes',{newhp:attrib.newhp,adjabil:attrib.adjabil,acurr:attrib.acurr,exercise:attrib.exercise},attr);
 const power=context(layouts.exper);Object.assign(power,{xint16:transport.short,rnd:(n,line,caller)=>{if(services.rng_log_enabled())services.rng_log_set_caller(services.literal('exper.c'),line,services.literal(caller));return services.rnd(n);}});environment.register('hero-energy',{newpw},power);
 const hunger=context(layouts.eat);Object.defineProperty(hunger,'disp',{value:record('struct display_hints',environment.requireGlobal('disp'))});environment.register('hero-hunger',{init_uhunger},hunger);
 const rank=context(layouts.botl);rank.strlen=p=>Number(services.strlen(p));environment.register('hero-rank-size',{max_rank_sz},rank);
 environment.exposeAddressPort('display',['reset_glyphmap']);
 environment.register('hero-clock',{getnow:()=>environment.calendar('getnow')});
 return {ui,tables,poly,limitation:'Hero initialization dependency integration in progress; source callbacks/UI and inventory/skills require their actual owners.'};
}
