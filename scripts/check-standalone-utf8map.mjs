import {runHistoricalCli as runPriorLayoutAudit} from './nethack-layout.mjs';
if(runPriorLayoutAudit(import.meta.url))process.exit(0);
// Preserve the existing targeted closure check and add UTF8MAP provenance.
import './check-standalone-special-interactions.mjs';
import assert from 'node:assert/strict';import fs from 'node:fs';import path from 'node:path';import crypto from 'node:crypto';
const abi=JSON.parse(fs.readFileSync('js/nethack/utf8map-abi.json')),sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex');
for(const[p,h]of Object.entries(abi.sourceSha256))assert.equal(sha(p),h,p);
for(const[p,h]of Object.entries(abi.referenceHeaderSha256))assert.equal(sha(path.resolve(process.env.STANDALONE_REFERENCE_ROOT,p)),h,p);
console.log('PASS '+JSON.stringify({utf8mapExports:Object.keys(abi.public),sourcePins:Object.keys(abi.sourceSha256).length,configuredHeaderPins:Object.keys(abi.referenceHeaderSha256).length}));
