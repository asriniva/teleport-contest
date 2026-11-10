// Read-only data/config guard; source-order and differential gates are separate.
import assert from 'node:assert/strict';
import {readFile} from 'node:fs/promises';
import {resolve,dirname} from 'node:path';
import {fileURLToPath,pathToFileURL} from 'node:url';
import {execFileSync} from 'node:child_process';
import {createHash} from 'node:crypto';
const root=resolve(dirname(fileURLToPath(import.meta.url)),'../../..');
const read=p=>readFile(resolve(root,p),'utf8');
const [source,prepared,core,runtime,support,library]=await Promise.all(['nethack-c/upstream/src/allmain.c','.cache/wasm64-build/tree/src/allmain.c','js/ported/allmain.js','js/ported/allmain-runtime.js','nethack-c/wasm/tu-fragments/allmain-support.c','nethack-c/wasm/tu-libraries/allmain.js'].map(read));
assert.equal(prepared,source,'ALLMAIN pristine/prepared provenance changed');
assert.ok((await read('scripts/tu-allmain-probe.c')).includes(';flags:%d/%d/%ld/%d;poly:'),'Snapshot u.usleep must retain original signed long64');
const strip=s=>s.replace(/\/\*[\s\S]*?\*\/|\/\/[^\n]*/g,'');
const clean=strip(source),cleanJS=strip(core),sites=[],owners=[...source.matchAll(/\n(\w+)\([^;{}]*\)(?:[^\n]*)\n\{/g)];
for(const match of source.matchAll(/\/\*[\s\S]*?\*\/|\/\/[^\n]*|"(?:\\.|[^"\\])*"|\b(rn2|rnd|rn1)\s*\(/g)){
 if(!match[1])continue;let depth=1,end=match.index+match[0].length;
 for(;end<source.length;end++){if(source[end]==='(')depth++;else if(source[end]===')'&&!--depth)break;}
 const line=source.slice(0,end).split('\n').length,owner=owners.filter(f=>f.index<match.index).at(-1)[1];sites.push({name:match[1],line,owner});
 assert.ok(cleanJS.includes(`, ${line}, "${owner}")`),'RNG original closing-line origin '+line);
}
assert.equal(sites.length,16);assert.equal([...cleanJS.matchAll(/\bC\.(rn2|rnd|rn1)\s*\(/g)].length,16);
assert.equal([...cleanJS.matchAll(/\bC\.(rn2|rnd|rn1)\(\(\)=>/g)].length,16,'Every RNG bound defers until original caller logging');
assert.ok(runtime.includes("rn2(bound,line,fn){services.rngCaller(line,fn);return services.drawRn2(typeof bound==='function'?bound():bound);}"));
const macro=clean.match(/#define U_CAN_REGEN\(\) ([^\n]*)/)[1];assert.equal(macro,'(Regeneration || (Sleepy && u.usleep))');
assert.equal([...clean.matchAll(/U_CAN_REGEN\(\)/g)].length-1,3);
assert.equal([...cleanJS.matchAll(/\(C\.Regeneration \|\| \(C\.Sleepy && C\.u\.usleep\)\)/g)].length,3,'Source-owned macro must stay in original regen_hp');
const data=await import(pathToFileURL(resolve(root,'js/ported/allmain.js')));
for(const name of['mvl_wtcap','mvl_change']){assert.equal(data[name],0);assert.ok(clean.includes(`static int ${name} = 0;`));assert.ok(runtime.includes(`${name}:allmain.${name}`));}
assert.equal(Object.values(data).filter(v=>typeof v==='function').length,16);
const literals=new Set([...clean.matchAll(/"(?:\\.|[^"\\])*"/g)].map(m=>JSON.parse(m[0])));literals.delete('hack.h');sites.forEach(s=>literals.add(s.owner));
const actual=JSON.parse(library.match(/var literals=new Set\((\[[^\n]*\])\)/)[1]);assert.deepEqual(new Set(actual),literals);
const size=actual.reduce((n,s)=>n+Buffer.byteLength(s)+1,0);assert.ok(support.includes(`static char teleport_allmain_literals[${size}];`));assert.equal(size,636);
assert.ok(!support.includes('src/allmain.c'),'No original ALLMAIN fallback');
const longPaths=['gc.command_count','gh.hero_seq','gm.multi','gw.were_changes','iflags.hilite_delta','svc.context.next_attrib_check','svc.context.seer_turn','svc.context.tribute.tributesz','svm.moves','u.usleep','urealtime.realtime','urealtime.start_timing'];
const runtimeLongs=JSON.parse(runtime.match(/const longs=new Set\((\[[^\n]*\])\)/)[1]);assert.deepEqual(new Set(runtimeLongs),new Set(longPaths));
for(const path of longPaths)assert.ok(support.includes(`_Static_assert(sizeof(${path})==8,`),'Compiler long/time guard '+path);
assert.ok(runtime.includes("path==='svc.context.tribute.tributesz'?BigInt.asUintN(64,BigInt(value)):BigInt(value)"));
assert.ok(support.includes('long teleport_allmain_from_double(double n){return(long)n;}'));
assert.ok(support.includes('double teleport_allmain_dep_difftime(time_t a0,time_t a1){return difftime(a0,a1);}'));
assert.ok(library.includes('difftime:(a0=0,a1=0)=>_teleport_allmain_dep_difftime(BigInt(a0),BigInt(a1))'));
assert.ok(cleanJS.includes('C.callLocal(welcome, C.TRUE);'));assert.ok(runtime.includes('callLocal(fn,...values){const frame=services.stackSave();try{return fn(...values);}finally{services.stackRestore(frame);}}'));
assert.ok(cleanJS.includes('return C.longFromDouble(C.difftime(etim, stim));'));
assert.ok(cleanJS.includes('Math.trunc((C.ACURR(C.A_WIS) + C.ACURR(C.A_INT)) / 15) + 1'));
for(const expression of['moveamt / 4','moveamt / 2','(moveamt * 3) / 4','(moveamt * 7) / 8'])assert.ok(cleanJS.includes(`Math.trunc(${expression})`));
const defines=JSON.parse(await read('nethack-c/wasm/compile-defines.json'));
const output=execFileSync(resolve(root,'.cache/emsdk/upstream/emscripten/emcc'),['-E','-dM','-sMEMORY64=1','-I'+resolve(root,'.cache/wasm64-build/tree/include'),'-include',resolve(root,'nethack-c/wasm/native-terminal.h'),...defines.map(d=>'-D'+d),resolve(root,'.cache/wasm64-build/tree/src/allmain.c')],{encoding:'utf8'});
const macros=new Set([...output.matchAll(/^#define (\w+)/gm)].map(m=>m[1]));
for(const key of['CRASHREPORT','SAFERHANGUP','STATUS_HILITES','MAIL','CLIPPING','NEWS','INSURANCE'])assert.ok(macros.has(key),'Configured feature drift '+key);
for(const key of['POSITIONBAR','MICRO','WIN32','WIN32CON','CHANGE_COLOR','TTY_PERM_INVENT','MACOS9','NO_SIGNAL','SOUNDLIB','SOUNDS','USER_SOUNDS'])assert.ok(!macros.has(key),'Configured feature drift '+key);
console.log(`ALLMAIN source guard: pristine/prepared identical;16 RNG closing-line/caller sites,3 owning-function regen macro expansions,2 JS statics,12 compiler64bit fields,${actual.length} literals/${size} bytes; feature guards pass.`);
console.log('Prepared source SHA256 '+createHash('sha256').update(prepared).digest('hex'));
