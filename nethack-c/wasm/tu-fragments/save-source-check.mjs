// Development source/configuration/typed-shape guard. No C behavior fallback.
import assert from 'node:assert/strict';
import {readFileSync} from 'node:fs';
import {createHash} from 'node:crypto';
import {execFileSync} from 'node:child_process';
import {resolve,join} from 'node:path';
import {fileURLToPath,pathToFileURL} from 'node:url';
const root=fileURLToPath(new URL('../../../',import.meta.url)),sdk=resolve(process.env.EMSDK??join(root,'.cache/emsdk'));
const read=p=>readFileSync(join(root,p),'utf8');
const source=read('.cache/wasm64-build/tree/src/save.c'),pristine=read('nethack-c/upstream/src/save.c'),core=read('js/ported/save.js'),runtime=read('js/ported/save-runtime.js'),binding=read('nethack-c/wasm/tu-libraries/save.js'),support=read('nethack-c/wasm/tu-fragments/save-support.c'),header=read('nethack-c/wasm/tu-fragments/save-source-data.h'),schema=JSON.parse(read('nethack-c/wasm/tu-fragments/save-schema.json'));
assert.equal(source,pristine,'Review original/prepared SAVE changes');
assert.equal(createHash('sha256').update(source).digest('hex'),header.match(/SAVE_SOURCE_SHA256 "([a-f0-9]+)"/)?.[1],'Review SAVE source fingerprint');
const {parse}=await import(pathToFileURL(join(sdk,'upstream/emscripten/node_modules/acorn/dist/acorn.mjs')).href);
const defines=JSON.parse(read('nethack-c/wasm/compile-defines.json')).map(x=>'-D'+x),sourcePath='.cache/wasm64-build/tree/src/save.c';
const args=['-sMEMORY64=1',...defines,'-I.cache/wasm64-build/tree/include',sourcePath];
const cpp=execFileSync(join(sdk,'upstream/emscripten/emcc'),['-E',...args],{cwd:root,encoding:'utf8',maxBuffer:20*1024*1024});
let active=false;const selected=[];for(const line of cpp.split('\n')){const m=line.match(/^# \d+ "([^"]+)"/);if(m)active=m[1]===sourcePath;else if(active)selected.push(line);}
const configured=selected.join('\n'),defs=Array.from(configured.matchAll(/\b(\w+)\s*\(([^;{}]*)\)\s*\{/g)).filter(x=>!['if','for','while','switch'].includes(x[1]));
function inventory(text){const ast=parse(text,{ecmaVersion:'latest',sourceType:'module'}),functions=ast.body.filter(n=>n.type==='ExportNamedDeclaration'&&n.declaration?.type==='FunctionDeclaration').map(n=>n.declaration);assert.deepEqual(functions.map(n=>n.id.name),defs.map(d=>d[1]),'Original SAVE inventory/order');for(let i=0;i<functions.length;i++){const params=defs[i][2].trim();assert.deepEqual(functions[i].params.map(p=>p.name),!params||params==='void'?[]:params.split(',').map(s=>s.match(/(\w+)\s*$/)[1]),'Original SAVE parameters');}return ast;}
const jsast=inventory(core);assert.equal(defs.length,26);assert.throws(()=>inventory(core.replace('function dosave(', 'function missing_dosave(')),/Original SAVE inventory/);
for(const comment of source.match(/\/\*[\s\S]*?\*\//g)??[])assert.ok(core.includes(comment),'Original SAVE comment');
const strings=new Set(['mon_notices_blocked<0']);function visit(n){if(n?.type==='ImportDeclaration')return;if(n?.type==='Literal'&&typeof n.value==='string')strings.add(n.value);for(const value of Object.values(n??{}))if(Array.isArray(value)){for(const c of value)if(c?.type)visit(c);}else if(value?.type)visit(value);}visit(jsast);
// Include-import literals were part of this exact generated corpus. No arbitrary
// excess capacity can hide adding an unreviewed runtime-generated string.
const literalBytes=Array.from(strings).reduce((n,s)=>n+Buffer.byteLength(s)+1,0);assert.equal(Number(header.match(/SAVE_LITERAL_CAPACITY (\d+)/)?.[1]),literalBytes,'Exact SAVE literal corpus capacity');assert.deepEqual([...strings].sort(),schema.literals);
const snprintf=[...configured.matchAll(/nh_snprintf\(__func__,\s*(\d+)/g)];assert.equal(snprintf.length,1);assert.equal(Number(header.match(/SAVE_SNPRINTF_LINE (\d+)/)?.[1]),Number(snprintf[0][1]));
const strlen=[...configured.matchAll(/Strlen_\([^;]*?__func__,\s*(\d+)\)/g)];assert.equal(strlen.length,2);for(let i=0;i<strlen.length;i++)assert.equal(Number(header.match(new RegExp('SAVE_STRLEN_LINE'+i+' (\\d+)'))?.[1]),Number(strlen[i][1]));
assert.ok(core.includes('C.Strlen(tmp.text, 0)')&&core.includes('C.Strlen(msg, 1)'));
const assertion=configured.match(/__assert_fail\("hero[^\n]*?,\s*"([^"]+)",\s*(\d+),\s*__func__/);assert.ok(assertion);assert.equal(JSON.parse(header.match(/SAVE_SOURCE_FILE ("[^"]+")/)[1]),assertion[1]);assert.equal(Number(header.match(/SAVE_ASSERT_LINE (\d+)/)?.[1]),Number(assertion[2]));
assert.ok(support.includes('debugcore(SAVE_SOURCE_FILE,FALSE)'),'Original debug macro source ownership');
assert.ok(!/\b(?:rn2|rnd|rn1)\(/.test(configured),'SAVE has no RNG site');
assert.ok(source.includes('static struct trap zerotrap;')&&source.includes('static struct fruit zerofruit;'));assert.ok(support.includes('static struct trap save_zerotrap;static struct fruit save_zerofruit;'));
const ast=JSON.parse(execFileSync(join(sdk,'upstream/emscripten/emcc'),['-fsyntax-only','-Xclang','-ast-dump=json',...args],{cwd:root,encoding:'utf8',maxBuffer:80*1024*1024}));
const records=new Map(),td=new Map(),fields=new Map();function walk(n){if(n.kind==='TypedefDecl')td.set(n.name,n);if(n.kind==='RecordDecl'&&n.completeDefinition){records.set(n.id,n);for(const f of n.inner??[])if(f.kind==='FieldDecl')fields.set(f.id,f);}for(const c of n.inner??[])walk(c);}walk(ast);
for(const [name,n]of td)for(const c of n.inner??[]){const rec=records.get(c.ownedTagDecl?.id);if(rec&&!rec.name)rec.name=name;}
const byname=new Map([...records.values()].map(n=>[n.name,n]));
for(const [name,s]of Object.entries(schema.schema)){const rec=byname.get(name);assert.ok(rec,'Original SAVE record '+name);for(const f of s.fields){const actual=rec.inner.find(x=>x.kind==='FieldDecl'&&x.name===f.name);assert.ok(actual,'Original SAVE field '+name+'.'+f.name);assert.equal(actual.type.qualType,f.ctype,'Original SAVE field type');assert.equal(Boolean(actual.isBitfield),f.bit,'Original bitfield');if(f.bit)assert.equal(Number(actual.inner.find(x=>x.value!==undefined).value),f.bitWidth,'Original bitfield width');}}
const prototypes=new Map(ast.inner.filter(n=>n.kind==='FunctionDecl').map(n=>[n.name,n]));for(const [name,type]of Object.entries(schema.dependencyTypes))assert.equal(prototypes.get(name)?.type.qualType,type,'Review SAVE dependency prototype '+name);
assert.ok(runtime.includes('const schemas='+JSON.stringify(schema.schema)+';'),'Runtime schema exactly source-derived');assert.ok(runtime.includes('const globals='+JSON.stringify(schema.globals)+';'));
for(const f of defs){const name=f[1];assert.ok(binding.includes('"'+name+'"'),'Imported source body '+name);}
assert.ok(binding.includes('getuid:()=>(Number(_getuid())>>>0)'),'Unsigned32 getuid return transport');assert.ok(binding.includes('_yyyymmddhhmmss(long(a0))'),'Original time_t64 dependency');
const test=read('scripts/test-tu-save.mjs'),probe=read('scripts/tu-save-probe.c');assert.ok(test.includes('Number(BigInt.asIntN(64,BigInt(value)))'),'Signed metadata before Number');assert.ok(test.includes('readLayout(reference,true)')&&test.includes('readLayout(hybrid,true)'),'Unsigned64 carrier metadata regression');assert.ok(probe.includes('int probe_disp_freemem(void){return DISP_FREEMEM;}'),'Actual compiler cleanup constant');assert.ok(probe.includes('append("tmp_at:%d:%d;",(int)a0,(int)a1)'),'Both cleanup coords must remain observable');
console.log(`SAVE source guard:26 original functions/parameters/comments,${Object.keys(schema.schema).length} typed records,170 accessed fields,1 formatter/2 Strlen sites,2 compiler-sized static sentinels,${literalBytes} literal bytes,zero RNG sites; inventory mutation rejected`);
