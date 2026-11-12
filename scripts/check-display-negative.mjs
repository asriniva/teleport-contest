import{rebaseTestModule}from'./test-module-imports.mjs';
// Leave original C/Wasm and comparison assertions untouched. Only the private
// JS candidate or eager initialization hook is deliberately wrong.
import assert from'node:assert/strict';
import{readFileSync,writeFileSync,mkdirSync}from'node:fs';
import{spawnSync}from'node:child_process';
import{fileURLToPath,pathToFileURL}from'node:url';
import{createHash}from'node:crypto';
const root=fileURLToPath(new URL('../',import.meta.url)),work=root+'.cache/display-first-pass/negative/';mkdirSync(work,{recursive:true});
const hash=p=>createHash('sha256').update(readFileSync(p)).digest('hex');
const pinned=['.cache/wasm64-build/tree/src/display.c','.cache/display-first-pass/display-reference.wasm','.cache/display-first-pass/display-hybrid.wasm','scripts/test-tu-display.mjs'].map(p=>[p,hash(root+p)]);
const core=readFileSync(root+'js/ported/display.js','utf8'),runtime=readFileSync(root+'js/nethack/bindings/display.js','utf8');
const start=core.indexOf('export function fn_cmap_to_glyph('),end=core.indexOf('\n}',start);assert.ok(start>=0&&end>start);
const wrong=core.slice(0,start)+core.slice(start,end).replace('return ', 'return 1 + ')+core.slice(end);assert.notEqual(wrong,core);
writeFileSync(work+'display.mjs',rebaseTestModule(wrong,root+'js/ported/display.js'));
writeFileSync(work+'display-runtime.mjs',rebaseTestModule(runtime,root+'js/nethack/bindings/display.js',new Map([[root+'js/ported/display.js',pathToFileURL(work+'display.mjs').href]])));
for(const[mode,env]of[['wrong-source',{DISPLAY_RUNTIME:pathToFileURL(work+'display-runtime.mjs').href}],['missing-eager-init',{DISPLAY_STARTUP_NEGATIVE:'1'}]]){
 const p=spawnSync(process.execPath,[root+'scripts/test-tu-display.mjs'],{cwd:root,env:{...process.env,...env},encoding:'utf8',maxBuffer:8*1024*1024});
 writeFileSync(work+mode+'.log',p.stdout+p.stderr);assert.notEqual(p.status,0,mode+' must fail');assert.match(p.stdout+p.stderr,/AssertionError/,mode+' actual comparison assertion');
 for(const[path,sha]of pinned)assert.equal(hash(root+path),sha,mode+' unchanged oracle/input '+path);
 console.log('PASS DISPLAY actual AssertionError negative:',mode,'original C/Wasm/test unchanged');
}
