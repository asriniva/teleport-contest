// Adapter descriptors plus actual configured-C private table layouts.
import fs from 'node:fs';
import path from 'node:path';
import crypto from 'node:crypto';
import {pathToFileURL} from 'node:url';
const directory=path.resolve(process.env.STANDALONE_HERO_STARTUP_ORACLE||'.cache/standalone-hero-startup-v4'),sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex');
const receipt=JSON.parse(fs.readFileSync(path.join(directory,'receipt.json')));
for(const [p,h]of Object.entries(receipt.sourceSha256))if(sha(p)!==h)throw new Error('Changed reference input '+p);
for(const [p,h]of Object.entries(receipt.artifactSha256))if(sha(path.join(directory,p))!==h)throw new Error('Changed reference artifact '+p);
const {default:factory}=await import(pathToFileURL(path.join(directory,'reference.mjs'))),ref=await factory();
function declaration(file,name){const line=fs.readFileSync(file,'utf8').split('\n').find(l=>l.startsWith('const '+name+'='));if(!line?.endsWith(';'))throw new Error('Changed descriptor boundary '+file+':'+name);return JSON.parse(line.slice(('const '+name+'=').length,-1));}
const poly='js/ported/polyself-runtime.js',ui='js/ported/u_init-runtime.js';
const data={polyself:{schema:declaration(poly,'schemas'),globals:declaration(poly,'globals')},u_init:{fields:declaration(ui,'fields'),tables:declaration(ui,'tables')},records:{},sourceSha256:Object.fromEntries([poly,ui,'scripts/export-standalone-hero-abi.mjs','scripts/tu-u_init-layout.h','js/ported/attrib-runtime.js'].map(p=>[p,sha(p)])),measurementArtifactSha256:receipt.artifactSha256};
let i=0;for(const [name,fields,types]of [['trobj',['trotyp','trspe','trclass','trquan_min','trquan_max','trbless'],['short','signed char','char','char','char','char']],['inv_sub',['race_pm','item_otyp','subs_otyp'],['short','short','short']]]){const size=Number(ref._probe_hero_layout(i++));data.records[name]={size,fields:Object.fromEntries(fields.map((n,j)=>[n,{offset:Number(ref._probe_hero_layout(i++)),ctype:types[j]+' '+n}]))};}
fs.writeFileSync('js/standalone/hero-abi.json',JSON.stringify(data,null,2)+'\n');
console.log('Exported original adapter descriptors and measured hero table layouts.');
