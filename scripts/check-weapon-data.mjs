// Source projection guard for WEAPON's nine private tables. Not a C parser;
// the deliberately bounded initializer grammar must be reviewed if it changes.
import { readFileSync } from 'node:fs';
import assert from 'node:assert/strict';
import * as core from '../js/ported/weapon.js';
const source=readFileSync(new URL('../nethack-c/upstream/src/weapon.c',import.meta.url),'utf8');
const clean=source.replace(/\/\*[\s\S]*?\*\//g,'');
const pn=Object.fromEntries([...clean.matchAll(/^#define (PN_\w+) \((-?\d+)\)/gm)].map(m=>[m[1],Number(m[2])]));
assert.match(clean,/^#define AKLYS_LIM \(BOLT_LIM \/ 2\)$/m);
const names=['skill_names_indices','odd_skill_names','barehands_or_martial','kebabable','rwep','pwep','arwep','hwep','skill_ranges'];
let rows=0;
for(const name of names){
 const start=new RegExp('\\b'+name+'\\s*\\[[^\\]]*\\]\\s*=\\s*\\{').exec(clean);assert.ok(start,name);
 let index=start.index+start[0].length,depth=1,end=index,quote=null;
 while(depth){const ch=clean[end];assert.notEqual(ch,undefined,name);if(quote){if(ch==='\\')end++;else if(ch===quote)quote=null;}else if(ch==='"'||ch==="'")quote=ch;else if(ch==='{')depth++;else if(ch==='}')depth--;end++;}
 const body=clean.slice(index,end-1),tokens=body.match(/"(?:\\.|[^"\\])*"|'(?:\\.|[^'\\])*'|\b\w+\b|[{},*]/g)??[];
 let pos=0;
 const value=()=>{const t=tokens[pos++];if(t?.startsWith('"'))return JSON.parse(t);if(t==="'\\0'")return 0;if(/^\d+$/.test(t))return Number(t);assert.match(t,/^[A-Z][A-Z_0-9]*$/,name);return t in pn?pn[t]:t;};
 const result=[];
 while(pos<tokens.length){if(tokens[pos]===','){pos++;continue;}
  if(name==='arwep'||name==='skill_ranges'){
   assert.equal(tokens[pos++],'{');const first=value();assert.equal(tokens[pos++],',');let second=value();
   if(name==='arwep'){assert.equal(second,'AKLYS_LIM');assert.equal(tokens[pos++],'*');assert.equal(value(),'AKLYS_LIM');second='AKLYS_RANGE';}
   assert.equal(tokens[pos++],',');const third=value();assert.equal(tokens[pos++],'}');result.push(name==='arwep'?{otyp:first,range:second,tethered:third}:{first,last:second,name:third});
  }else result.push(value());
 }
 assert.deepEqual(core[name],result,name);rows+=result.length;
}
console.log(`WEAPON data: ${names.length} original private tables / ${rows} rows preserved.`);

// Original double-quoted messages/table names must remain byte-for-byte.
// Generated selector names and diagnostic metadata may add literals.
const js=readFileSync(new URL('../js/ported/weapon.js',import.meta.url),'utf8').replace(/\/\*[\s\S]*?\*\//g,'').replace(/\/\/[^\n]*/g,'');
const literalCounts=text=>{const counts=new Map();for(const token of text.match(/"(?:\\.|[^"\\])*"/g)??[])counts.set(token,(counts.get(token)??0)+1);return counts;};
const original=literalCounts(clean),translated=literalCounts(js);original.delete('"hack.h"');
for(const[token,count]of original)assert.ok((translated.get(token)??0)>=count,'Missing original literal '+token);
