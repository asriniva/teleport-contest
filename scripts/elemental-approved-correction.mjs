// Test-only authorization/provenance guard; never changes source or game memory.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import crypto from 'node:crypto';
import {readBeforeLayout} from './services-layout-audit.mjs';
export function elementalApprovedCorrection(directory){
 const manifest='docs/runtime-environment/authorized-port-corrections.json',baseline='docs/runtime-environment/scope-baseline.json',hash=b=>crypto.createHash('sha256').update(b).digest('hex'),read=p=>fs.readFileSync(p),data=JSON.parse(read(manifest)),rows=data.corrections;
 assert.deepEqual(rows.map(r=>r.file),['js/ported/vision.js'],'Only the user-approved VISION correction');
 const row=rows[0],original=JSON.parse(read(baseline)).sha256[row.file],corrected=readBeforeLayout(row.file,'utf8');
 assert.equal(row.baselineSha256,original,'Original VISION baseline retained');
 assert.equal(hash(Buffer.from(corrected)),row.correctedSha256,'Approved corrected VISION hash');
 assert.equal(corrected.split(row.change.after).length,2,'Exactly one approved correction');
 assert.equal(hash(Buffer.from(corrected.replace(row.change.after,row.change.before))),original,'Reversing only the approved line restores original VISION');
 const native=path.resolve(directory,'tree/src/vision.c');
 assert.equal(hash(read(native)),row.reference.sha256,'Original C VISION is unchanged');
 const receipt=JSON.parse(read(path.resolve(directory,'receipt.json')));
 assert.ok(Object.entries(receipt.sourceSha256).some(([p,h])=>p.endsWith('/tree/src/vision.c')&&h===row.reference.sha256),'Original C VISION bound by sealed receipt');
 return{manifestSha256:hash(read(manifest)),baselineSha256:hash(read(baseline)),file:row.file,originalSha256:original,correctedSha256:row.correctedSha256,nativeSha256:row.reference.sha256,scope:'Exactly one user-approved logical-OR normalization; no other translated policy correction accepted by this guard.'};
}
