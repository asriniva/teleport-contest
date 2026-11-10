// Read-only source-data guards for PLINE's configured macros and ABI storage.
import assert from 'node:assert/strict';
import {readFileSync} from 'node:fs';
import {fileURLToPath,pathToFileURL} from 'node:url';
import {resolve,join} from 'node:path';
const root=fileURLToPath(new URL('../../../',import.meta.url));
const sdk=resolve(process.env.EMSDK??join(root,'.cache/emsdk'));
const {parse}=await import(pathToFileURL(join(sdk,'upstream/emscripten/node_modules/acorn/dist/acorn.mjs')));
const original=readFileSync(join(root,'nethack-c/upstream/src/pline.c'),'utf8');
assert.equal(readFileSync(join(root,'.cache/wasm64-build/tree/src/pline.c'),'utf8'),original,'PLINE prepared provenance changed');
const core=readFileSync(join(root,'js/ported/pline.js'),'utf8');
const binding=readFileSync(join(root,'nethack-c/wasm/tu-libraries/pline.js'),'utf8');
const header=readFileSync(join(root,'nethack-c/wasm/tu-fragments/pline-source-data.h'),'utf8');
const runtime=readFileSync(join(root,'js/ported/pline-runtime.js'),'utf8');
assert.match(original,/#define BIGBUFSZ \(5 \* BUFSZ\)/);
assert.match(original,/static int in_pline = 0;/);assert.match(original,/static boolean use_pline_handler = TRUE;/);
assert.match(runtime,/state=\{in_pline:0,use_pline_handler:1\}/);
assert.equal((original.match(/char pbuf\[BIGBUFSZ\]/g)??[]).length,3);
assert.equal((core.match(/C\.stackAlloc\(C\.BIGBUFSZ\)/g)??[]).length,3);
assert.match(original,/char gamelogbuf\[BUFSZ \* 2\]/);assert.match(core,/C\.stackAlloc\(C\.BUFSZ \* 2\)/);
assert.match(original,/const char \*args\[3\]/);assert.match(core,/C\.pointerArrayLocal\(3\)/);
assert.match(original,/#define YouPrefix\(pointer, prefix, text\) \\\n    Strcpy\(\(pointer = You_buf\(\(int\) \(strlen\(text\) \+ sizeof prefix\)\)\), prefix\)/);
assert.match(original,/#define YouMessage\(pointer, prefix, text\) \\\n    strcat\(\(YouPrefix\(pointer, prefix, text\), pointer\), text\)/);
function prefixes(text){return [...text.matchAll(/C\.Strcpy\(\(tmp = You_buf\(C\.int\(C\.strlen\(line\) \+ (\d+)\)\)\), ("(?:\\.|[^"\\])*")\)/g)].map(m=>[JSON.parse(m[2]),Number(m[1])]);}
const expected=[...original.matchAll(/You(?:Prefix|Message)\(tmp, ("(?:\\.|[^"\\])*"), line\)/g)].map(m=>{const value=JSON.parse(m[1]);return[value,Buffer.byteLength(value)+1];});
assert.equal(expected.length,13);assert.deepEqual(prefixes(core),expected,'Original prefix sizeof/macro expansions');
assert.notDeepEqual(prefixes(core.replace('C.strlen(line) + 5','C.strlen(line) + 6')),expected,'Prefix mutation must be detected');
const strings=new Set();
function visit(node,parent){if(node.type==='Literal'&&typeof node.value==='string'&&parent?.type!=='ImportDeclaration')strings.add(node.value);for(const value of Object.values(node)){if(value&&typeof value==='object')Array.isArray(value)?value.forEach(child=>visit(child,node)):visit(value,node);}}
visit(parse(core,{ecmaVersion:'latest',sourceType:'module'}));
const capacity=[...strings].reduce((n,s)=>n+Buffer.byteLength(s)+1,0);
assert.equal(Number(header.match(/TELEPORT_PLINE_LITERAL_CAPACITY (\d+)/)?.[1]),capacity,'Source-derived literal capacity');
assert.deepEqual(JSON.parse(binding.match(/var sourceLiterals=new Set\((\[[^\n]*\])\);/)[1]),[...strings].sort(),'Source literal allowlist');
// No RNG is introduced by this TU's generated statements.
const clean=original.replace(/\/\*[\s\S]*?\*\/|\/\/[^\n]*|"(?:\\.|[^"\\])*"/g,'');
assert.doesNotMatch(clean,/\b(?:rn2|rnd|rnz|d)\(/);
console.log(`PLINE source guards:13prefix expansions;3private big buffers;${strings.size} literals/${capacity} bytes;no original RNG sites;mutation rejected.`);
