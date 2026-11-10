// Read-only source/data fidelity checks; no native policy or generated tables.
import assert from 'node:assert/strict';
import {readFileSync} from 'node:fs';
import {fileURLToPath} from 'node:url';
import {resolve} from 'node:path';
import {callbacks,inside_gas_cloud,expire_gas_cloud} from '../js/ported/region.js';
const root=fileURLToPath(new URL('..',import.meta.url));
const source=readFileSync(resolve(root,'nethack-c/upstream/src/region.c'),'utf8');
const js=readFileSync(resolve(root,'js/ported/region.js'),'utf8');
const original=source.match(/static const callback_proc callbacks\[\]\s*=\s*\{([\s\S]*?)\};/);assert.ok(original,'original callback array must exist');
assert.deepEqual(original[1].replace(/^#.*$/gm,'').split(',').map(s=>s.trim()).filter(Boolean),['inside_gas_cloud','expire_gas_cloud']);
assert.deepEqual(callbacks,[inside_gas_cloud,expire_gas_cloud]);
const count=text=>{const out=new Map();for(const c of text.match(/\/\*[\s\S]*?\*\//g)||[])out.set(c,(out.get(c)||0)+1);return [...out].sort(([a],[b])=>a.localeCompare(b));};
assert.deepEqual(count(js),count(source),'every original block comment and its multiplicity');
console.log('REGION original callback identities/order and every block comment match.');
