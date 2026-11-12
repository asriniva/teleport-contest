// DEV ONLY: exact native MON ALIGNLIM int observations; no game process/state.
import fs from 'node:fs';import path from 'node:path';import assert from 'node:assert/strict';import crypto from 'node:crypto';import {spawnSync} from 'node:child_process';import {pathToFileURL} from 'node:url';import vm from 'node:vm';
import {projectMonAlignmentLimit} from '../js/standalone/monster-lifecycle.js';
const root=process.cwd(),reference=path.resolve(process.env.STANDALONE_REFERENCE_ROOT??root),sdk=reference+'/.cache/emsdk',tree=reference+'/.cache/wasm64-build/tree',clang=sdk+'/upstream/bin/clang',directory=path.resolve('.cache/mon-alignment-leaf-v1');fs.mkdirSync(directory,{recursive:true});
const sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex'),runtimeFile='js/nethack/bindings/mon.js',sourceFile='js/ported/mon.js',source=fs.readFileSync(sourceFile,'utf8'),runtime=fs.readFileSync(runtimeFile,'utf8'),align=tree+'/include/align.h';
assert.match(fs.readFileSync(align,'utf8'),/^#define ALIGNLIM \(10L \+ \(svm.moves \/ 200L\)\)$/m,'unchanged native macro');
const sourceSites=[...source.matchAll(/^.*\bC\.ALIGNLIM\b.*$/gm)].map(m=>({line:source.slice(0,m.index).split('\n').length,text:m[0]}));assert.equal(sourceSites.length,4,'all original MON macro sites accounted for');
assert.ok(sourceSites[0].text.includes('C.int(C.ALIGNLIM)')&&sourceSites[0].text.includes('/ (2)'));
assert.ok(sourceSites[1].text.includes('(C.ALIGNLIM) / (4)'));assert.ok(sourceSites[2].text.includes('(C.ALIGNLIM) / (8)'));assert.ok(sourceSites[3].text.includes('(C.ALIGNLIM) / (4)'));
const nativeMon=tree+'/src/mon.c',nativeSource=fs.readFileSync(nativeMon,'utf8'),nativeSites=[...nativeSource.matchAll(/^.*\bALIGNLIM\b.*$/gm)].map(m=>({line:nativeSource.slice(0,m.index).split('\n').length,text:m[0]}));assert.equal(nativeSites.length,4);assert.ok(nativeSites[0].text.includes('(int) ALIGNLIM / 2'));assert.ok(nativeSites[1].text.includes('(int) (ALIGNLIM / 4)'));assert.ok(nativeSites[2].text.includes('-(int) (ALIGNLIM / 8)'));assert.ok(nativeSites[3].text.includes('(int) (ALIGNLIM / 4)'));
// Use the actual unchanged MON primitive, mechanically located by AST. This
// self-contained arrow uses only its value parameter and Number/BigInt/Math.
const {parse}=await import(pathToFileURL(sdk+'/upstream/emscripten/node_modules/acorn/dist/acorn.mjs')),ast=parse(runtime,{ecmaVersion:'latest',sourceType:'module'}),factory=ast.body.find(n=>n.type==='ExportNamedDeclaration'&&n.declaration?.id?.name==='createMonEnvironment').declaration;
const declaration=factory.body.body.flatMap(n=>n.type==='VariableDeclaration'?n.declarations:[]).find(n=>n.id.name==='int');assert.equal(declaration.init.type,'ArrowFunctionExpression');const intSource=runtime.slice(declaration.init.start,declaration.init.end),cint=vm.runInNewContext('('+intSource+')',{Number,BigInt,Math},{timeout:1000});
const cSource=`#include "hack.h"
#include "align.h"
_Static_assert(sizeof(long)==8, "native long width");
_Static_assert(sizeof(int)==4, "native int width");
_Static_assert(sizeof(void*)==8, "native memory64 pointer width");
_Static_assert(sizeof(__typeof__(svm.moves))==8, "native move width");
_Static_assert(((__typeof__(svm.moves))-1)<0, "native moves signed");
int abi_long(void){return sizeof(long);}
int abi_int(void){return sizeof(int);}
int abi_pointer(void){return sizeof(void*);}
int mon_alignment(long moves,int site){
    __typeof__(svm) local_frame;
    local_frame.moves=moves;
#define svm local_frame
    switch(site){
    case 0:return (int) ALIGNLIM;
    case 1:return (int) ((int) ALIGNLIM / 2);
    case 2:return (int) (ALIGNLIM / 4);
    case 3:return (int) (ALIGNLIM / 8);
    default:__builtin_trap();
    }
#undef svm
}
`;
const cFile=directory+'/probe.c',wasmFile=directory+'/probe.wasm';fs.writeFileSync(cFile,cSource);
const flags=['--target=wasm64-unknown-emscripten','--sysroot='+sdk+'/upstream/emscripten/cache/sysroot','-include',reference+'/nethack-c/wasm/native-terminal.h','-I'+tree+'/include','-I'+reference+'/.cache/ncurses-wasm64-build/include',...JSON.parse(fs.readFileSync('nethack-c/wasm/compile-defines.json')).map(v=>'-D'+v)];
function run(args){const r=spawnSync(clang,args,{encoding:'utf8',maxBuffer:16*1024*1024});if(r.status!==0)throw Error('Pinned native compiler failed:\n'+r.stderr);return r.stdout;}
const depFile=directory+'/headers.d';run([...flags,'-M','-MF',depFile,cFile]);const dependencies=fs.readFileSync(depFile,'utf8').replace(/\\\n/g,' ').split(':').slice(1).join(':').trim().split(/\s+/).filter(Boolean).map(p=>path.resolve(p));assert.ok(dependencies.includes(path.resolve(align)));
const inputFiles=[path.resolve('scripts/test-standalone-mon-alignment.mjs'),path.resolve(runtimeFile),path.resolve(sourceFile),path.resolve('nethack-c/wasm/compile-defines.json'),path.resolve('js/standalone/mon-abi.json'),path.resolve('js/standalone/monster-lifecycle.js'),nativeMon,clang,sdk+'/upstream/bin/wasm-ld',sdk+'/upstream/emscripten/node_modules/acorn/dist/acorn.mjs',...dependencies],pins=()=>Object.fromEntries([...new Set(inputFiles)].sort().map(p=>[p,sha(p)])),before=pins(),version=run(['--version']);
const command=[...flags,'-O2','-nostdlib','-Wl,--no-entry',...['abi_long','abi_int','abi_pointer','mon_alignment'].map(n=>'-Wl,--export='+n),'-o',wasmFile,cFile];run(command);
const module=new WebAssembly.Module(fs.readFileSync(wasmFile));assert.deepEqual(WebAssembly.Module.imports(module),[],'tiny C leaf has no imported code/globals/memory');const native=new WebAssembly.Instance(module,{}).exports;assert.deepEqual([native.abi_long(),native.abi_int(),native.abi_pointer()],[8,4,8]);
const min=-(1n<<63n),max=(1n<<63n)-1n,moves=new Set([min,max,-1n,0n,1n,1999n,2000n,2001n]),add=v=>{if(v>=min&&v<=max)moves.add(v);};
for(const base of [min,max,0n,200n,-200n,1n<<31n,-(1n<<31n),1n<<53n,-(1n<<53n)])for(let d=-8n;d<=8n;d++)add(base+d);
// Exercise the remainder's sign boundary and every quotient/cast wrap around
// header values 2^31, 2^32, 2^35 and nearby multiples, including negative time.
for(const a of [-(1n<<35n),-(1n<<32n),-(1n<<31n),-1n,0n,1n,1n<<31n,1n<<32n,1n<<35n,(1n<<35n)+1n])for(let d=-16n;d<=16n;d++)add((a-10n)*200n+d);
let seed=1n;for(let i=0;i<10000;i++){seed=BigInt.asUintN(64,seed*6364136223846793005n+1442695040888963407n);add(BigInt.asIntN(64,seed));}
let checks=0;const sampleRows=[];for(const value of moves){const a=10n+value/200n,projected=projectMonAlignmentLimit(a),actual=[cint(projected),cint(cint(projected)/2),cint(cint(projected/4)),cint(cint(projected/8))];for(let i=0;i<4;i++){assert.equal(actual[i],native.mon_alignment(value,i),'native original expression '+i+' moves='+value);checks++;}if(value===min||value===max||value===2000n)sampleRows.push({moves:String(value),macro:String(a),projected,results:actual});}
assert.deepEqual(pins(),before,'compiler/source/all transitive native header inputs remain unchanged');const evidence={complete:true,devOnly:true,productionModifiedByTest:false,productionProjectionUnderTest:true,gameFieldsTouched:false,noImports:true,checks,cases:moves.size,generatedCases:10000,abi:{long:8,int:4,pointer:8},projection:'Number(A % (8n * (1n << 32n))), A=original signedlong ALIGNLIM',intPrimitive:{file:runtimeFile,source:intSource,mechanicallyExtracted:true},sourceSites,nativeSites,sourceSiteSha256:sourceSites.map(r=>crypto.createHash('sha256').update(r.text).digest('hex')),nativeSiteSha256:nativeSites.map(r=>crypto.createHash('sha256').update(r.text).digest('hex')),sourceAndCompilerSha256:before,compilerVersion:version,compileCommand:[clang,...command],artifactSha256:{probeC:sha(cFile),probeWasm:sha(wasmFile)},sampleRows,limits:'Equivalence is only for the four guarded original MON int observations. The projected Number is not the general full long macro value; additional source uses require new review.'};fs.writeFileSync(directory+'/evidence.json',JSON.stringify(evidence,null,2)+'\n');console.log('PASS '+JSON.stringify({checks,cases:moves.size,noImports:true,abi:evidence.abi,sampleRows,evidence:directory+'/evidence.json'}));
