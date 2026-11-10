// Read-only source/ABI fidelity guard. No DO policy or save data.
import assert from 'node:assert/strict';
import {readFileSync} from 'node:fs';
const read=p=>readFileSync(new URL('../'+p,import.meta.url),'utf8');
const source=read('nethack-c/upstream/src/do.c'),js=read('js/ported/do.js');
const comments=text=>{const out=new Map();for(const c of text.match(/\/\*[\s\S]*?\*\//g)||[])out.set(c,(out.get(c)||0)+1);return [...out].sort(([a],[b])=>a.localeCompare(b));};
assert.deepEqual(comments(js),comments(source),'all original block comments and multiplicities');
const clean=text=>text.replace(/\/\*[\s\S]*?\*\//g,'');
const original=[...clean(source).matchAll(/^(?:staticfn\s+)?(?:struct\s+\w+\s*\*|NHFILE\s*\*|void|int|boolean)\s*\n?(\w+)\(([^{};]*?)\)\s*\{/gm)].map(m=>({name:m[1],params:m[2].split(',').map(s=>s.replace(/\bUNUSED\b/g,'').trim()).filter(s=>s&&s!=='void').map(s=>s.match(/\w+$/)?.[0])}));
const translated=[...clean(js).matchAll(/^export function (\w+)\(([^)]*)\)/gm)].map(m=>({name:m[1],params:m[2].split(',').map(s=>s.replace(/\bUNUSED\b/g,'').trim()).filter(Boolean)}));
assert.equal(original.length,44,'configured original source inventory');assert.deepEqual(translated,original,'original function order, boundaries and parameter names');
assert.match(js,/const buf = C\.staticBuffer\(39\)/,'original persistent wipe occupation text');
for(const name of ['fam_msgs','halu_fam_msgs']){const a=source.match(new RegExp('static const char \\*const '+name+'\\[4\\] = \\{([\\s\\S]*?)\\};'));const b=js.match(new RegExp('const '+name+' = \\[([\\s\\S]*?)\\];'));assert.ok(a);assert.ok(b);const strings=x=>[...x.matchAll(/"(?:\\.|[^"\\])*"/g)].map(m=>m[0]);assert.deepEqual(strings(a[1]),strings(b[1]),name+' original local string order');}
assert.doesNotMatch(clean(js),/\bgoto\s/);assert.match(js,/new_ = 0/,'C new local uses necessary JS reserved-word spelling');
console.log('DO all44 original boundaries/order/parameters/comments, local readonly message tables, persistent occupation buffer and forward exits match.');
