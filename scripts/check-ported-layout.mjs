// Compare the complete port with a commit before a layout-only change.
import assert from 'node:assert/strict';
import { execFileSync } from 'node:child_process';
import { readdirSync, readFileSync } from 'node:fs';
import { parse } from 'acorn';
import { sourceLayoutSignature } from './source-layout-signature.mjs';

const [ref] = process.argv.slice(2);
if (!ref) throw new Error('Usage: node scripts/check-ported-layout.mjs <reference-commit>');
const revision = execFileSync('git', ['rev-parse', '--verify', '--end-of-options', ref + '^{commit}'], { encoding: 'utf8' }).trim();
const dir = 'js/ported';
const names = readdirSync(dir).filter(name => name.endsWith('.js')).sort();
const referenceNames = execFileSync('git', ['ls-tree', '--name-only', revision + ':' + dir], { encoding: 'utf8' })
    .trim().split('\n').filter(name => name.endsWith('.js')).sort();
assert.deepEqual(names, referenceNames, 'ported modules');
for (const name of names) {
    const path = dir + '/' + name;
    const original = execFileSync('git', ['show', revision + ':' + path], { encoding: 'utf8', maxBuffer: 32 * 1024 * 1024 });
    const current = readFileSync(path, 'utf8');
    assert.equal(sourceLayoutSignature(parse, current), sourceLayoutSignature(parse, original), path);
}
console.log('Matched JavaScript syntax, token order, literals and comments in ' + names.length + ' ported modules against ' + revision);
