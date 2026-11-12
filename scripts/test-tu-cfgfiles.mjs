import './pure-js-probes/deny-wasm.mjs';
import {referenceLabelFor as fixtureReferenceLabelFor} from './native-test-backend.mjs';
const fixtureReferenceLabel=fixtureReferenceLabelFor("cfgfiles");
import {createProbe,createReference,loadFixture,fixtureImports} from './pure-js-fixtures/load.mjs';
import assert from './native-test-assert.mjs';
import {readFile} from 'node:fs/promises';
import {resolve} from 'node:path';
import {pathToFileURL} from 'node:url';
import {referenceBackend,memoryCheckpoint,assertMemoryGrowth,assertStackRestored} from './native-test-backend.mjs';
import {withCEnvironment,C} from '../js/c-runtime/context.js';
import * as core from '../js/ported/cfgfiles.js';
import {createCfgfilesEnvironment} from '../js/nethack/bindings/cfgfiles.js';
const dir=resolve(process.env.CFGFILES_PROBE_DIR??'.cache/tu-probes'),schema=JSON.parse(await readFile(new URL('../nethack-c/wasm/tu-fragments/cfgfiles-schema.json',import.meta.url),'utf8'));
const factory=async mode=>(await loadFixture("cfgfiles",pathToFileURL(resolve(dir,'cfgfiles-'+mode+'.mjs')).href)).default;
const rf=await factory('reference'),hf=await factory('hybrid'),reference=await referenceBackend('cfgfiles',rf)();
function text(m,p){p=Number(p);if(!p)return null;let e=p;while(m.HEAPU8[e])e++;return Buffer.from(m.HEAPU8.slice(p,e)).toString('utf8');}
function layout(m){const out={};for(let i=0;i<m._probe_layout_count();i++)out[text(m,m._probe_layout_name(i))]=Number(BigInt.asIntN(64,m._probe_layout_value(i)));return out;}
const L=layout(reference),envs=new WeakMap(),ops=Object.keys(schema.functionTypes),index=name=>{const i=ops.indexOf(name);if(i<0)throw Error(name);return i;};
const runtime={cfgfiles(services,name,...args){let env=envs.get(services.moduleKey);if(!env){env=createCfgfilesEnvironment(services,L,core);envs.set(services.moduleKey,env);}const stack=services.stackSave(),va=env.vaList;try{if(name==='config_error_add')env.vaList=env.ptr(args[1]);const result=withCEnvironment(env,core[name],...args.map(env.ptr));return schema.functionTypes[name].split('(')[0].includes('*')?BigInt(result??0):result;}finally{env.vaList=va;services.stackRestore(stack);}},cfgfilesPrivate(module,index){const e=envs.get(module);if(!e)throw Error('CFGFILES observation before initialization');return index>=100?e.disregarded_config_lines[index-100]:[e.ignore_errors_on_unmatched,e.ignore_statement_errors,e.configfile,e.default_configfile,e.config_error_data,e.config_error_msg][index];}};
const hybrid=await hf({nethackPorted:runtime}),modules=[reference,hybrid],stacks=modules.map(m=>m._probe_stack());assert.deepEqual(layout(hybrid),L);let comparisons=1,active='',called=new Set();
const both=(method,...args)=>modules.map(m=>m['_probe_'+method](...args));
function str(m,s,slot=0){const at=Number(m._probe_scratch())+slot*1024;m.stringToUTF8(s,at,slot===0?4096:1024);return BigInt(at);}
function input(m,s){return m._probe_input(str(m,s));}
function compare(){const v=modules.map(m=>({state:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace())}));for(const key of ['state','trace'])if(v[0][key]!==v[1][key]){const at=[...v[0][key]].findIndex((c,i)=>c!==v[1][key][i]);throw Error('CFGFILES '+key+' differs in '+active+' after '+comparisons+' checks at '+at+'\nactual '+v[1][key].slice(Math.max(0,at-80),at+240)+'\nexpected '+v[0][key].slice(Math.max(0,at-80),at+240));}comparisons+=2;for(const [get,size]of [[m=>m._probe_private(2),256],[m=>m._probe_input(0n),8192]]){const values=modules.map(m=>{const at=Number(get(m));return Buffer.from(m.HEAPU8.slice(at,at+size)).toString('hex');});assert.equal(values[1],values[0],active+' complete source buffer bytes');comparisons++;}modules.forEach((m,i)=>{assertStackRestored(m,stacks[i]);comparisons++;});assert.equal(C,undefined);}
function reset(){active='reset';both('reset');compare();}
const chars=new Set(['get_configfile','get_default_configfile','choose_random_part','is_config_section','find_optparam']);
function action(name,args=()=>[]){active=name;called.add(name);const values=modules.map(m=>{const a=typeof args==='function'?args(m):args;return m._probe_action(index(name),...a.map(BigInt),...Array(5-a.length).fill(0n));});if(chars.has(name)){assert.equal(text(hybrid,values[1]),text(reference,values[0]));if(['choose_random_part','is_config_section','find_optparam'].includes(name))assert.equal(values[1]?values[1]-hybrid._probe_input(0n):0n,values[0]?values[0]-reference._probe_input(0n):0n);}else if(name==='fopen_config_file')assert.equal(Boolean(values[1]),Boolean(values[0]));else assert.equal(values[1],values[0],name);comparisons++;compare();return values;}
function option(k,v){both('option',k,v);}
reset();action('get_configfile');action('get_default_configfile');action('set_configfile_name',m=>[str(m,'config-fixture')]);
// The complete original const table retains names, lengths, flags and aliases.
const e=envs.get(hybrid);for(let i=0;i<59;i++){const row=e.config_line_stmt[i];assert.equal(text(hybrid,row.name),text(reference,reference._probe_table_name(i)));for(const[c,key]of ['len','syscnf_only','origbuf'].entries())assert.equal(row[key],reference._probe_table_value(i,c));assert.equal(row.fn,core[ops[reference._probe_table_value(i,3)]]);comparisons+=5;}
for(const value of [' 1 2 255 256 0 8','3 0 9','7\\error','a','42949672960 9'])for(const mod of [0,1]){reset();action('get_uchars',m=>[input(m,value),m._probe_scratch()+4096n,mod,6,str(m,'WARN',6)]);const b=modules.map(m=>Buffer.from(m.HEAPU8.slice(Number(m._probe_scratch())+4096,Number(m._probe_scratch())+4102)).toString('hex'));assert.equal(b[1],b[0]);comparisons++;}
for(const value of ['',',a','a,b,c','one,,three','abc,','a'])for(const rng of [0,1,2]){reset();option(1,rng);action('choose_random_part',m=>[input(m,value),44]);}
for(const value of ['[ choice ] # comment','[x]junk','[]','[ x ]',' x ','[x','[x] #ok','[ ]']){reset();action('is_config_section',m=>[input(m,value)]);action('handle_config_section',m=>[input(m,value)]);action('free_config_sections');}
for(const value of ['NAME=value','NAME:value','a:b=c','noequal','']){reset();action('find_optparam',m=>[input(m,value)]);}
// Every configured directive body runs through the actual imported ABI.
for(const name of ops.filter(n=>n.startsWith('cnf_line_')))for(const value of ['5','0','-2','abc']){reset();option(5,L.set_in_sysconf);action(name,m=>[input(m,name==='cnf_line_WARNINGS'?'1 2 3 4 5 6':name==='cnf_line_OPTIONS'?'OPTIONS='+value:value)]);}
for(const value of ['OPTIONS= a, b','NAME=  Test\t Name  ','CHARACTER=wizard','LEVELS=/tmp/fixture','SOUND=ignored','SOUNDDIR=ignored','unknown=3','missing','  dogname : Fido ','BOULDER=42','WARNINGS=1 2 3 4 5 6','LIVELOG=0xffff','LIVELOG=0x10000'])for(const src of [L.set_in_config,L.set_in_sysconf]){reset();option(5,src);action('parse_config_line',m=>[input(m,value)]);}
reset();action('disregard_all_config_statements');action('parse_config_line',m=>[input(m,'NAME=ignored')]);for(const id of [-1,0,10,58,59,99]){action('heed_this_config_statement',[id]);action('disregard_this_config_statement',[id]);}action('heed_all_config_statements');action('set_ignore_errors_on_unmatched');action('config_unmatched_ignored');action('clear_ignore_errors_on_unmatched');action('config_unmatched_ignored');
// Nested frames, secure early stop, Lua error list ownership and actual varargs.
for(const secure of [0,1]){reset();action('config_error_init',m=>[1,str(m,'outer'),secure]);action('config_error_nextline',m=>[input(m,'actual line')]);action('config_erradd',m=>[str(m,'problem')]);action('config_error_nextline',m=>[input(m,'second line')]);action('config_error_init',m=>[0,str(m,'inner'),0]);action('config_error_add',m=>[str(m,'%s:%d:%ld:%zu:%x'),str(m,'value',1),-17]);action('config_error_done');action('config_error_done');action('config_error_done');}
reset();action('config_error_init',m=>[0,str(m,'Lua'),0]);option(6,1);action('config_erradd',m=>[str(m,'first')]);action('config_erradd',m=>[str(m,'second!')]);action('l_get_config_errors',[1]);option(6,0);action('config_error_done');
for(const content of ['ONE=1\nTWO=2\n','# comment\n\nA=first\\\n second\n','CHOOSE=red,blue\n[red]\nONE=1\n[blue]\nTWO=2\n[]\nTHREE=3\n','X=last','\n','MISSING\n','X='+('a'.repeat(1100))+'\nNEXT=ok\n']){reset();action('parse_conf_str',m=>[input(m,content),m._probe_callback()]);}
// True libc stdio paths, file contents and access/errno/default selection.
for(const m of modules){m.FS.mkdirTree('/fixture');m.FS.writeFile('/fixture/config','NAME=Real File\nOPTIONS=foo\n');m.FS.writeFile('/fixture/raw','RAW=one\nRAW=two\n');m.FS.writeFile('/fixture/sysconf','NAME=System File\n');}
reset();const files=action('fopen_config_file',m=>[str(m,'/fixture/config'),L.set_in_config]);modules.forEach((m,i)=>m._probe_close(files[i]));action('read_config_file',m=>[str(m,'/fixture/config'),L.set_in_config]);
reset();action('set_configfile_name',m=>[str(m,'/fixture/written')]);action('do_write_config_file');assert.equal(text(hybrid,hybrid._probe_contents(str(hybrid,'/fixture/written'))),text(reference,reference._probe_contents(str(reference,'/fixture/written'))));comparisons++;
reset();option(2,0);action('set_configfile_name',m=>[str(m,'/fixture/not-written')]);action('do_write_config_file');reset();action('do_write_config_file');
reset();option(3,1);option(4,1);const checkpoints=modules.map(memoryCheckpoint);action('parse_conf_str',m=>[input(m,'OPTIONS=foo\nOPTIONS=bar\n'),m._probe_callback()]);modules.forEach((m,i)=>assertMemoryGrowth(m,checkpoints[i]));comparisons+=2;
// Remaining private format/file entry points exercised with genuine ABI values.
reset();action('cnf_parser_init',m=>[m._probe_scratch()+4096n]);action('parse_conf_buf',m=>[m._probe_scratch()+4096n,m._probe_callback()]);action('cnf_parser_done',m=>[m._probe_scratch()+4096n]);
reset();action('rcfile');action('rcfile_interface_options');
// Lua callbacks may grow memory and prepend another message after the source
// has already saved its local old-list head. Keep native ownership/control flow.
reset();action('config_error_init',m=>[0,str(m,'Lua reentry'),0]);option(6,1);action('config_erradd',m=>[str(m,'old one')]);action('config_erradd',m=>[str(m,'old two')]);option(3,1);option(4,1);action('l_get_config_errors',[1]);assert.equal(hybrid._probe_private(5),0n);option(6,0);action('config_error_done');comparisons++;
// Replacing owned strings and Lua error-list teardown expose actual frees.
reset();for(const name of ['cnf_line_WIZARDS','cnf_line_SHELLERS','cnf_line_MSGHANDLER','cnf_line_EXPLORERS','cnf_line_GENERICUSERS','cnf_line_SUPPORT','cnf_line_RECOVER','cnf_line_CRASHREPORTURL']){action(name,m=>[input(m,'first')]);action(name,m=>[input(m,'second')]);}assert.ok(text(hybrid,hybrid._probe_trace()).includes('free:'));comparisons++;
// Direct actual FILE* and va_list routes preserve source boundaries.
reset();const readers=modules.map(m=>m._probe_open(str(m,'/fixture/raw')));action('parse_conf_file',m=>[readers[modules.indexOf(m)],m._probe_callback()]);modules.forEach((m,i)=>m._probe_close(readers[i]));
reset();active='vconfig_error_add native va_list';called.add('vconfig_error_add');modules.forEach(m=>m._probe_vformat(str(m,'%s:%d:%ld:%zu:%x'),str(m,'wide',1),-19,9007199254741001n,9007199254741003n,0xfedcba98));compare();assert.ok(text(hybrid,hybrid._probe_trace()).includes('wide:-19:9007199254741001:9007199254741003:fedcba98'));comparisons++;
reset();modules.forEach(m=>m.FS.writeFile('/sysconf','valid'));action('assure_syscf_file');
// Actual stdio consumes an intentionally short-writing virtual device.
reset();option(9,1);const delivered=[];for(const m of modules){let n=0;m.FS.createDevice('/fixture','partial',null,b=>{if(n>=31)throw new m.FS.ErrnoError(L.EIO);n++;});delivered.push(()=>n);}action('set_configfile_name',m=>[str(m,'/fixture/partial')]);action('do_write_config_file');assert.equal(delivered[1](),delivered[0]());assert.ok(text(hybrid,hybrid._probe_trace()).includes('partial data'));comparisons+=2;
// Throwing from a true dependency still restores JS adapter context/stack.
const he=envs.get(hybrid),savedStack=hybrid._probe_stack(),savedFopen=he.fopen;he.fopen=()=>{throw Error('fixture fopen throw');};try{assert.throws(()=>withCEnvironment(he,core.fopen_config_file,Number(str(hybrid,'/fixture/config')),L.set_in_config),/fixture fopen throw/);}finally{delete he.fopen;}assert.equal(C,undefined);assertStackRestored(hybrid,savedStack);comparisons+=2;
// Separate Modules retain original independent static buffers, tables and roots.
const hybrid2=await hf({nethackPorted:runtime});hybrid2._probe_reset();const he2=envs.get(hybrid2);assert.notEqual(he,he2);assert.notEqual(he.config_line_stmt,he2.config_line_stmt);assert.notEqual(he.disregarded_config_lines,he2.disregarded_config_lines);withCEnvironment(he2,core.set_ignore_errors_on_unmatched);assert.equal(he2.ignore_errors_on_unmatched,1);assert.equal(he.ignore_errors_on_unmatched,0);comparisons+=5;
assert.equal(called.size,92);assert.equal(C,undefined);

console.log(`cfgfiles: ${comparisons} ${fixtureReferenceLabel}/JS state/trace/stdio/heap/varargs/callback/stack comparisons; all ${called.size} configured bodies directly exercised; controlled dependencies`);
