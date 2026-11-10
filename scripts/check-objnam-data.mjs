// Development-only source/configuration/data guard; never imported by the game.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import * as data from '../js/ported/objnam.js';
const source=fs.readFileSync('nethack-c/upstream/src/objnam.c','utf8');
const prepared=fs.readFileSync('.cache/wasm64-build/tree/src/objnam.c','utf8');
const js=fs.readFileSync('js/ported/objnam.js','utf8');
assert.equal(source,prepared,'OBJNAM configured source retains original bytes');
const mask=s=>s.replace(/\/\*[\s\S]*?\*\/|\/\/[^\n]*|"(?:\\.|[^"\\])*"|'(?:\\.|[^'\\])*'/g,x=>x.replace(/[^\n]/g,' '));
const comments=s=>s.match(/\/\*[\s\S]*?\*\//g)??[];
const originalComments=comments(source),portedComments=comments(js);let pos=0;
for(const comment of originalComments){const next=portedComments.indexOf(comment,pos);assert.notEqual(next,-1,'Original ordered comment '+comment.slice(0,80));pos=next+1;}
const c=mask(source),clean=mask(js);
const functions=[...c.matchAll(/^(\w+)\(([^;{}]*)\)\s*\{/gm)].map(m=>({name:m[1],params:m[2]}));
assert.equal(functions.length,87);assert.deepEqual([...clean.matchAll(/export function (\w+)\(/g)].map(m=>m[1]),functions.map(f=>f.name));
function split(s){let depth=0,start=0;const result=[];for(let i=0;i<=s.length;i++){const ch=s[i]??',';if('([{'.includes(ch))depth++;if(')]}'.includes(ch))depth--;if(ch===','&&!depth){result.push(s.slice(start,i).trim());start=i+1;}}return result.filter(Boolean);}
for(const fn of functions){const original=split(fn.params).filter(p=>p!=='void').map(p=>p.match(/\(\*(\w+)\)/)?.[1]??p.replace(/\bUNUSED\b/g,'').trim().match(/\w+$/)[0]);const translated=js.match(new RegExp('export function '+fn.name+'\\(([^)]*)\\)'))[1].split(',').map(p=>p.trim()).filter(Boolean);assert.deepEqual(translated,original,fn.name+' original parameters');}
function initializer(name){const match=source.match(new RegExp('\\b'+name+'\\[[^\\]]*\\]\\s*=\\s*\\{'));assert.ok(match,name);const at=match.index+match[0].lastIndexOf('{');let depth=1,end=at+1;while(depth){if(c[end]==='{')depth++;if(c[end]==='}')depth--;end++;}return source.slice(at+1,end-1);}
function value(s){s=s.replace(/\(const char \*\)\s*/g,'').trim();if(s==='0')return 0;if(s.startsWith('"'))return JSON.parse(s);return s;}
for(const[name,fields]of Object.entries({Japanese_items:['item','name'],one_off:['sing','plur'],o_ranges:['name','oclass','f_o_range','l_o_range'],spellings:['sp','ob']})){
 const body=initializer(name).replace(/\/\*[\s\S]*?\*\//g,'');const rows=[...body.matchAll(/\{([^{}]*)\}/g)].map(m=>Object.fromEntries(split(m[1]).map((v,i)=>[fields[i],value(v)])));assert.deepEqual(data[name],rows,name+' authoritative rows');
}
for(const name of ['wrp','wrpsym','special_subjs','as_is']){const body=initializer(name).replace(/\/\*[\s\S]*?\*\//g,'');assert.deepEqual(data[name],split(body).map(value),name+' authoritative values/sentinel');}
assert.equal(data.Japanese_items.length,14);assert.equal(data.one_off.length,23);assert.equal(data.o_ranges.length,19);assert.equal(data.wrpsym.length,13);
assert.equal((c.match(/\bgoto\s+\w+;/g)??[]).length,49);assert.ok(!/\bgoto\s+\w+;/.test(clean),'No untranslated C goto');
assert.equal((clean.match(/C\.Strlen_\(/g)??[]).length,14);
assert.equal((clean.match(/C\.__assert_fail\(/g)??[]).length,2);
assert.ok(!/\b(?:xname|doname|readobjnam)\s*:\s*[^\n]*services\./.test(fs.readFileSync('js/ported/objnam-runtime.js','utf8')),'No original policy delegated to native services');
const support=fs.readFileSync('nethack-c/wasm/tu-objnam-support.inc','utf8');assert.ok(!/\b(?:for|while)\s*\(/.test(mask(support)),'Typed native ABI has no policy loop');
for(const name of functions.map(f=>f.name))assert.ok(!new RegExp('\\b'+name+'\\s*\\([^;{}]*\\)\\s*\\{').test(mask(support)),name+' algorithm absent native support');
assert.match(support,/static char objnam_buffers\[12\]\[BUFSZ\];/);
assert.match(support,/objnam_and_contents\[18\].*objnam_compound_start\[3\].*objnam_detect\[8\].*objnam_detection\[11\].*objnam_gauntlets\[10\].*objnam_shoes\[6\]/);
console.log(`OBJNAM: 87 original boundaries/parameters, ${originalComments.length} ordered comments, all 8 private catalogues/sentinels, 49 structured jumps, 14 Strlen/2 assertion sites and zero-only native storage pass.`);
