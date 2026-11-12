// Development-only input guard for the exact reviewed JS-helper extraction.
// Original compiled records remain immutable; unrelated inputs use raw hashes.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import crypto from 'node:crypto';
import {execFileSync} from 'node:child_process';
let extractionChecked=false;
const reviewedDependencies=new Map();
export const compiledInputDependencies=()=>[...reviewedDependencies];
const digest=bytes=>crypto.createHash('sha256').update(bytes).digest('hex');
export function assertCompiledInput(file,expected,label='compiled input') {
    const actual=digest(fs.readFileSync(file));
    if(actual===expected)return actual;
    const receipt=JSON.parse(fs.readFileSync('docs/runtime-environment/c-runtime-helper-extraction.json'));
    const relative=path.relative(process.cwd(),path.resolve(file));
    const entry=receipt.files.find(row=>row.file===relative);
    assert.ok(entry&&entry.beforeSha256===expected&&entry.afterSha256===actual,'stale '+label+':'+file);
    if(!extractionChecked){
        execFileSync(process.execPath,['scripts/extract-c-runtime-helpers.mjs'],{env:{...process.env,STANDALONE_REFERENCE_ROOT:process.env.STANDALONE_REFERENCE_ROOT??process.cwd()},stdio:'pipe'});
        assert.equal(digest(fs.readFileSync(receipt.helperFile)),receipt.helperSha256);
        reviewedDependencies.set(receipt.helperFile,receipt.helperSha256);
        reviewedDependencies.set('docs/runtime-environment/c-runtime-helper-extraction.json',digest(fs.readFileSync('docs/runtime-environment/c-runtime-helper-extraction.json')));
        extractionChecked=true;
    }
    const original=execFileSync('git',['show',receipt.baselineCommit+':'+relative]);
    assert.equal(digest(original),expected,'Historical input inverse differs '+file);
    console.log('Reviewed exact JS-helper input inverse: '+relative+'; original compiled pin retained');
    return actual;
}
