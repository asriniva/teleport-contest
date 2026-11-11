// Replay literal ordinary inputs through the unchanged sealed original-C runner.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import crypto from 'node:crypto';
import {runFullOriginalC} from './full-original-c-run.mjs';
const directory=path.resolve(process.env.STANDALONE_FULL_C_REFERENCE??'.cache/full-original-c-v1');
const fixture=path.resolve(process.env.NATIVE_BONES_FIXTURE??'.cache/native-deeper-bones-sam3');
const sha=file=>crypto.createHash('sha256').update(fs.readFileSync(file)).digest('hex');
const input=JSON.parse(fs.readFileSync(fixture+'/input.json')),generated=JSON.parse(fs.readFileSync(fixture+'/result.json')),generation=JSON.parse(fs.readFileSync(fixture+'/evidence.json'));
assert.ok(generation.complete&&generation.nativeOnly&&generation.deepest>=4&&generation.bones.length,'native generator reached a real deeper bones-producing death');
assert.equal(sha(fixture+'/input.json'),generation.literalInputSha256,'immutable literal inputs');
assert.equal(sha(fixture+'/controller.mjs'),generation.controllerSha256,'retained controller source');
assert.equal(sha(directory+'/receipt.json'),generation.referenceReceiptSha256,'identical sealed reference');
const replay=await runFullOriginalC(directory,input);
fs.writeFileSync(fixture+'/replay-result.json',JSON.stringify(replay,null,2)+'\n');
assert.deepEqual(replay,generated,'whole original-C result: observations, full RNG states/logs, TTY/frames, file paths/metadata/bytes including compressed bones');
const bones=Object.keys(replay.files).filter(name=>/\/bon[^/]*$/.test(name));
assert.deepEqual(bones,generation.bones.map(row=>row.path),'exact real bones paths');
for(const row of generation.bones){const bytes=Buffer.from(replay.files[row.path].bytes,'base64');assert.equal(bytes.length,row.bytes);assert.equal(crypto.createHash('sha256').update(bytes).digest('hex'),row.sha256);assert.equal(bytes.subarray(0,2).toString('hex'),'1f9d','actual original ncompress .Z stream');}
const evidence={nativeProducerFixtureAccepted:true,literalReplayAccepted:true,jsBonesAccepted:false,bonesGraphAccepted:false,referenceReceiptSha256:sha(directory+'/receipt.json'),fixtureSha256:sha(fixture+'/input.json'),generatedResultSha256:sha(fixture+'/result.json'),replayResultSha256:sha(fixture+'/replay-result.json'),generatorSha256:generation.controllerSha256,verifierSha256:sha('scripts/verify-native-bones-fixture.mjs'),unmodifiedRunnerSha256:sha('scripts/full-original-c-run.mjs'),profile:generation.profile,deepest:generation.deepest,moves:replay.state.moves,consumed:replay.consumed,inputBoundaries:replay.snapshots.length,frames:replay.frames.length,bones:generation.bones,limitation:'One genuine native Samurai seed3 ordinary descent/death producer, exactly replayed without the controller. JS production, four producer/consumer combinations and relocated restored bones graphs remain unverified.'};
fs.writeFileSync(fixture+'/replay-evidence.json',JSON.stringify(evidence,null,2)+'\n');console.log('PASS '+JSON.stringify(evidence));
