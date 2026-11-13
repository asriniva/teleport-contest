import assert from 'node:assert/strict';
import {discoverProductionWorldSuites,expandProductionWorldSuites} from './branch-coverage/production-world-suites.mjs';
const marker='/* runStandaloneProgram full-original-c-v1 */\n';
const files={
 'scripts/test-standalone-clean.mjs':marker+"import './safe.mjs';",
 'scripts/test-standalone-prefix.mjs':marker+"const input='sessions/seed4500.session.json';",
 'scripts/test-standalone-hidden.mjs':marker+"import('./helper.mjs');",
 'scripts/helper.mjs':"export {input} from './session-reader.mjs';",
 'scripts/session-reader.mjs':"export const input='sessions/seed1.session.json';",
 'scripts/safe.mjs':"export const input='  n';",
 'scripts/test-standalone-recorder.mjs':marker,
 'scripts/test-standalone-cycle.mjs':marker+"import './a.mjs';",
 'scripts/a.mjs':"import './b.mjs'; export * from './safe.mjs';",
 'scripts/b.mjs':"import './a.mjs'; export * from './session-reader.mjs';",
 'scripts/test-standalone-property.mjs':marker+"export * from './a.mjs';",
 'scripts/test-standalone-frozen.mjs':marker+'const accepted={literalNativeReplayAccepted:true};',
 'scripts/test-standalone-fresh-observations.mjs':marker+'// Complete recordings are compared from newly generated literal input.\n',
 'scripts/test-standalone-recording-dir.mjs':marker+"const root='recordings';",
 'scripts/test-standalone-recording-path.mjs':marker+"const input='../recordings/example.json';",
};
const result=discoverProductionWorldSuites('/unused',{read:file=>{assert.ok(file in files,file);return files[file];},names:Object.keys(files).map(p=>p.slice(8))});
assert.deepEqual(result.suites,['test-standalone-clean.mjs','test-standalone-fresh-observations.mjs']);assert.equal(result.excluded.length,7);
assert.equal(result.excluded.find(r=>r.name.includes('hidden')).reason,'scripts/session-reader.mjs');
assert.deepEqual(expandProductionWorldSuites(['test-standalone-obscure-interactions.mjs']).map(row=>row.args),[['riding'],['menus'],['music'],['rogue']]);
assert.deepEqual(expandProductionWorldSuites(['test-standalone-quest-completion.mjs'])[0].environment,{STANDALONE_QUEST_COMPLETION_SAFETY_SWEEP:'1'});
console.log('PASS: direct session prefixes, dynamic imports, reexports and cyclic/transitive session readers excluded; independent literal API input retained.');
