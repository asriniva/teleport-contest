// Read-only original data and comment fidelity; no fixture algorithms.
import assert from 'node:assert/strict';
import {readFileSync} from 'node:fs';
import * as core from '../js/ported/mthrowu.js';
const source=readFileSync(new URL('../nethack-c/upstream/src/mthrowu.c',import.meta.url),'utf8');
const js=readFileSync(new URL('../js/ported/mthrowu.js',import.meta.url),'utf8');
function initializer(text,name){const match=text.match(new RegExp('\\b'+name+'(?:\\[\\])?\\s*=\\s*[\\{\\[]([\\s\\S]*?)[\\}\\]]'));assert.ok(match,'original initializer '+name);return match[1].replace(/\/\*[\s\S]*?\*\//g,'');}
const strings=s=>[...s.matchAll(/"(?:\\.|[^"\\])*"/g)].map(m=>JSON.parse(m[0]));
for(const name of ['breathwep','hallublasts'])assert.deepEqual(core[name],strings(initializer(source,name)),name+' complete original order');
assert.deepEqual(strings(initializer(js,'barsounds')),strings(initializer(source,'barsounds')),'function-local barsounds');
const enums=s=>s.split(',').map(x=>x.trim()).filter(Boolean).map(x=>x.replace(/^C\./,''));
assert.deepEqual(enums(initializer(js,'se')),enums(initializer(source,'se')),'function-local sound selectors');
const comments=s=>{const out=new Map();for(const c of s.match(/\/\*[\s\S]*?\*\//g)||[])out.set(c,(out.get(c)||0)+1);return [...out].sort(([a],[b])=>a.localeCompare(b));};
assert.deepEqual(comments(js),comments(source),'every original block comment and multiplicity');
console.log('MTHROWU two complete file tables, two scoped local tables and all original block comments match.');
