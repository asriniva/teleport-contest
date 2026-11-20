// Exercise the historical hash lookup using the actual bytes immediately after
// the move. Today's implementation is free to evolve independently.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import { execFileSync } from 'node:child_process';
import { layoutSourceSha, verifyHistoricalLayout } from './nethack-layout.mjs';

verifyHistoricalLayout();
const moved = '1dab2c64a80d86e2398875c0e3d45017f174abf1';
const receipt = JSON.parse(fs.readFileSync('docs/runtime-environment/nethack-layout.json'));
const row = receipt.files['js/standalone/light.js'];
const file = path.resolve(row.destination);
let fixture = execFileSync('git', ['show', moved + ':' + row.destination]);
const read = fs.readFileSync;
try {
    fs.readFileSync = (name, ...args) => name === file ? fixture : read(name, ...args);
    assert.equal(layoutSourceSha(file, row.beforeSha256), row.beforeSha256);
    fixture = Buffer.concat([fixture, Buffer.from('\n')]);
    assert.throws(() => layoutSourceSha(file, row.beforeSha256), /changed beyond NetHack path relocation/);
} finally {
    fs.readFileSync = read;
}
console.log(`PASS historical relocation at ${moved.slice(0, 12)}: ${Object.keys(receipt.files).length} transitions verified and altered source rejected.`);
