// Independent development-only projection of original local option data.
import assert from 'node:assert/strict';
import {readFileSync} from 'node:fs';
const c=readFileSync(new URL('../.cache/wasm64-build/tree/src/questpgr.c',import.meta.url),'utf8');
const js=readFileSync(new URL('../js/ported/questpgr.js',import.meta.url),'utf8');
function compare(source){
    const literal=s=>Array.from(s.matchAll(/"(?:\\.|[^"\\])*"|\bNULL\b|\b\d+\b/g),m=>m[0]==='NULL'?0:m[0][0]==='"'?JSON.parse(m[0]):Number(m[0]));
    for(const name of ['howtoput','howtoput2i']){
        const original=c.match(new RegExp('\\b'+name+'\\[\\]\\s*=\\s*\\{([^}]+)\\}'))?.[1];
        const translated=source.match(new RegExp('\\bconst\\s+'+name+'\\s*=\\s*\\[([^\\]]+)\\]'))?.[1];
        assert.ok(original&&translated,name);assert.deepEqual(literal(translated),literal(original),name);
    }
    const original=c.match(/#define QTEXT_FILE ("[^"]+")/)[1];const translated=source.match(/export const QTEXT_FILE = ("[^"]+")/)[1];assert.equal(translated,original);
}
compare(js);
for(const [from,to]of [['"pline", "window"','"window", "pline"'],['[ 1, 2, 2, 3, 0, 0 ]','[ 1, 2, 3, 2, 0, 0 ]'],['"quest.lua"','"wrong.lua"']]){const mutated=js.replace(from,to);assert.notEqual(mutated,js);assert.throws(()=>compare(mutated));}
console.log('QUESTPGR original QTEXT_FILE/local option arrays and three rejection mutations passed.');
