import './pure-js-probes/deny-wasm.mjs';
import fs from 'node:fs';import assert from 'node:assert/strict';import crypto from 'node:crypto';
import {loadGameAssets} from '../js/nethack/game-assets.js';
import bundle from '../js/nethack/game-assets.json' with {type:'json'};
const manifest=JSON.parse(fs.readFileSync('js/nethack/game-assets-manifest.json')),sha=bytes=>crypto.createHash('sha256').update(bytes).digest('hex');
assert.equal(sha(fs.readFileSync('js/nethack/game-assets.json')),manifest.bundleSha256);
assert.equal(sha(fs.readFileSync('js/nethack/game-assets.js')),manifest.provenance.loaderSha256);
const first=loadGameAssets(),second=loadGameAssets();assert.equal(Object.keys(first).length,157);let bytes=0;
for(const row of manifest.files){
 const key='/nethack/'+row.path,a=first[key],b=second[key];assert.ok(a&&b);assert.equal(a.mode,row.mode);assert.equal(a.bytes.length,row.bytes);assert.equal(sha(a.bytes),row.sha256);
 assert.deepEqual(Buffer.from(a.bytes),fs.readFileSync('.cache/full-original-c-v1/assets/'+row.path),'exact original-C reference asset '+row.path);
 assert.equal(fs.statSync('.cache/full-original-c-v1/assets/'+row.path).mode&0o777,row.mode,'original-C asset mode '+row.path);
 assert.notEqual(a.bytes,b.bytes);assert.deepEqual(a.bytes,b.bytes);bytes+=a.bytes.length;
}
assert.equal(bytes,manifest.totalBytes);first['/nethack/cmdhelp'].bytes[0]^=255;
assert.equal(sha(second['/nethack/cmdhelp'].bytes),manifest.files.find(row=>row.path==='cmdhelp').sha256);
assert.deepEqual(Buffer.from(first['/nethack/license'].bytes),fs.readFileSync('js/nethack/game-assets.LICENSE'));
// Explicit malformed-JS-bundle contracts. The sealed C data remains untouched.
const version=bundle.version,root=bundle.root;
try{bundle.version=-1;assert.throws(()=>loadGameAssets(),/Unknown bundled game asset format/);bundle.version=version;bundle.root='/invalid';assert.throws(()=>loadGameAssets(),/Unknown bundled game asset format/);}
finally{bundle.version=version;bundle.root=root;}
assert.equal(Object.keys(loadGameAssets()).length,157);
console.log('PASS:157 exact original-C asset byte/mode witnesses, independent game buffers and license;2 malformed JS bundle contracts; Wasm/network unavailable.');
