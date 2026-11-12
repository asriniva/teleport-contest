// Read-only source/data guard. Differential tests remain the behavior gate.
import assert from 'node:assert/strict';
import {readFile} from 'node:fs/promises';
import {fileURLToPath,pathToFileURL} from 'node:url';
import {resolve,dirname} from 'node:path';
import {createHash} from 'node:crypto';
const root=resolve(dirname(fileURLToPath(import.meta.url)),'../../..');
const read=p=>readFile(resolve(root,p),'utf8');
const [prepared,pristine,js,runtime,support,library]=await Promise.all(['.cache/wasm64-build/tree/src/u_init.c','nethack-c/upstream/src/u_init.c','js/ported/u_init.js','js/nethack/bindings/u_init.js','nethack-c/wasm/tu-fragments/u_init-support.c','nethack-c/wasm/tu-libraries/u_init.js'].map(read));
const originalClock='#if defined(BSD) && !defined(POSIX_TYPES)\n    (void) time((long *) &ubirthday);\n#else\n    (void) time(&ubirthday);\n#endif';
const patchedClock='    /* Route through getnow() so fixed datetime also controls ubirthday. */\n    ubirthday = getnow();';
assert.ok(pristine.includes(originalClock));assert.equal(prepared,pristine.replace(originalClock,patchedClock),'Unexpected prepared/pristine adaptation');
const strip=s=>s.replace(/\/\*[\s\S]*?\*\/|\/\/[^\n]*/g,'');
const dataSource=strip(prepared.slice(prepared.indexOf('/*\n *      Initial inventory'),prepared.indexOf('staticfn void\nknows_object')));
const data=await import(pathToFileURL(resolve(root,'js/ported/u_init.js')));
const expectedTables=[];
const pattern=/static const struct (trobj|def_skill) (\w+)\[\] =\s*\{([\s\S]*?)\n?\};|static const struct inv_sub \{[\s\S]*?\} (inv_subs)\[\] = \{([\s\S]*?)\n\};/g;
let cells=0,rows=0;
for(const m of dataSource.matchAll(pattern)){
 const name=m[2]??m[4],body=m[3]??m[5];expectedTables.push(name);
 const expected=[...body.matchAll(/\{([^{}]*)\}/g)].map(row=>row[1].split(',').map(v=>v.trim()).filter(Boolean).map(v=>/^\d+$/.test(v)?Number(v):v));
 assert.deepEqual(data[name],expected,'Source table '+name);rows+=expected.length;cells+=expected.reduce((n,row)=>n+row.length,0);
 assert.ok(support.includes(`_Static_assert(sizeof ${name}==sizeof teleport_u_init_storage_${name},`),'Missing actual source/backing guard '+name);
 const type=m[1]==='trobj'?'struct teleport_u_init_trobj':m[1]==='def_skill'?'struct def_skill':'struct teleport_u_init_invsub';
 assert.ok(support.includes(`static ${type} teleport_u_init_storage_${name}[${expected.length}];`),'Backing must be exact zero-only storage '+name);
}
assert.equal(expectedTables.length,40);assert.equal(Object.values(data).filter(Array.isArray).length,40);
const cleanJS=strip(js),cleanC=strip(prepared);
for(const name of ['M_spell','trotyp']){
 const cm=cleanC.match(new RegExp('(?:const struct trobj \\*|const int )'+name+'\\[\\] =\\s*\\{([\\s\\S]*?)\\};'));
 const jm=cleanJS.match(new RegExp('const '+name+' =\\s*\\[([\\s\\S]*?)\\];'));
 assert.ok(cm&&jm,'Local array '+name);assert.equal(jm[1].replace(/\bC\./g,'').replace(/\s+/g,''),cm[1].replace(/\s+/g,''));
}
assert.ok(cleanJS.includes('const Instrument = C.localTrobj(\n                [ [ trotyp[C.rn2(trotyp.length, 810, "u_init_race")], 0, C.TOOL_CLASS, 1, 1, 0 ],\n                  [ 0, 0, 0, 0, 0, 0 ] ]);'));
const funcs=[...prepared.matchAll(/\n(\w+)\([^;{}]*\)\n\{/g)];
const sites=[];
// Match source lexical tokens while retaining offsets and excluding comments/strings.
for(const match of prepared.matchAll(/\/\*[\s\S]*?\*\/|\/\/[^\n]*|"(?:\\.|[^"\\])*"|\b(rn2|rnd|rn1|rne)\s*\(/g)){
 if(!match[1])continue;const line=prepared.slice(0,match.index).split('\n').length;const owner=funcs.filter(f=>f.index<match.index).at(-1)?.[1];sites.push({name:match[1],line,owner});
 assert.ok(cleanJS.includes(`, ${line}, "${owner}")`),'Missing RNG source origin '+line);
}
assert.equal([...cleanJS.matchAll(/\bC\.(rn2|rnd|rn1|rne)\s*\(/g)].length,sites.length+1,'Extra/missing RNG sites (one original ROLL_FROM expansion)');
const sourceLiterals=[...new Set([...strip(prepared).matchAll(/"(?:\\.|[^"\\])*"/g)].map(m=>JSON.parse(m[0])).filter(s=>s!=='hack.h'))];
const literalSet=new Set([...sourceLiterals,...sites.map(s=>s.owner),'u_init_race']);
const serviceLiterals=JSON.parse(library.match(/var literals=new Set\((\[[^\n]*\])\)/)[1]);
assert.deepEqual(new Set(serviceLiterals),literalSet,'Exact source-derived literal corpus');
const bytes=serviceLiterals.reduce((n,s)=>n+Buffer.byteLength(s)+1,0);
assert.ok(support.includes(`static char teleport_u_init_literals[${bytes}];`),'Exact zero-only source literal capacity');
assert.ok(runtime.includes("states.set(services.moduleKey,state)"));assert.ok(runtime.includes('BigInt(v)'));
assert.ok(support.includes('#ifdef TELEPORT_U_INIT_VALIDATE_SOURCE'));assert.ok(!support.includes('#ifdef TELEPORT_REFERENCE_TU'),'Source-private guards must not leak to unrelated shared reference probes');
assert.ok((await read('scripts/tu-u_init-probe.c')).includes('#include "../.cache/wasm64-build/tree/src/u_init.c"\n#define TELEPORT_U_INIT_VALIDATE_SOURCE 1'));
assert.ok(!/src\/u_init\.c|#include.*u_init\.c/.test(support),'No original TU fallback in support');
console.log(`U_INIT source guard: prepared birthday adaptation only;40 tables/${rows} rows/${cells} cells,3 local arrays,${sites.length+1} RNG sites,${serviceLiterals.length} literals/${bytes} bytes; zero-only typed storage verified.`);
console.log('Prepared source SHA256 '+createHash('sha256').update(prepared).digest('hex'));
