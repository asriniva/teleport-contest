// Development-only original private arrival enum/source-location guards.
import assert from 'node:assert/strict';
import {readFileSync} from 'node:fs';
const c=readFileSync(new URL('../.cache/wasm64-build/tree/src/dog.c',import.meta.url),'utf8');
const js=readFileSync(new URL('../js/ported/dog.js',import.meta.url),'utf8');
const support=readFileSync(new URL('../nethack-c/wasm/tu-dog-support.inc',import.meta.url),'utf8');
function check(source){const original=c.match(/enum arrival\s*\{([\s\S]*?)\};/)[1].replace(/\/\*[\s\S]*?\*\//g,'');const translated=source.match(/export const ([^;]+);/)[1];const rows=s=>Array.from(s.matchAll(/\b(\w+)\s*=\s*(-?\d+)/g),m=>[m[1],Number(m[2]),m[3]]);assert.deepEqual(rows(translated),rows(original));}
check(js);assert.throws(()=>check(js.replace('With_you=1','With_you=2')));assert.throws(()=>check(js.replace('Wiz_arrive=-1','Wiz_arrive=0')));
const assertion=c.match(/assert\(([^;]+)\);/);assert.ok(assertion);const line=c.slice(0,assertion.index).split('\n').length;assert.ok(support.includes(`__assert_fail("${assertion[1]}","dog.c",${line},"pick_familiar_pm")`));
const original=Array.from(c.matchAll(/\b(rn1|rn2|rnd)\(/g),m=>[m[1],c.slice(0,m.index).split('\n').length,Array.from(c.slice(0,m.index).matchAll(/^([A-Za-z_]\w*)\(/gm)).at(-1)[1]]);
const translated=Array.from(js.matchAll(/\bC\.(rn1|rn2|rnd)\([^;]+?, (\d+), '(\w+)'\)/g),m=>[m[1],Number(m[2]),m[3]]);assert.deepEqual(translated,original);
console.log('DOG arrival enum, exact RNG physical sites and assertion metadata passed (two rejected enum mutations).');
