// Reproduce the shared-helper migration and enforce the complete owned manifest.
import {execFileSync} from 'node:child_process';
for(const script of ['extract-c-runtime-helpers','prune-c-runtime-shims'])
    process.stdout.write(execFileSync(process.execPath,['scripts/'+script+'.mjs'],{encoding:'utf8'}));
for(const script of ['update-c-runtime-provenance','test-c-runtime-makefile-provenance'])
    process.stdout.write(execFileSync('python3',['-B','scripts/'+script+'.py'],{encoding:'utf8'}));
process.stdout.write(execFileSync(process.execPath,['scripts/write-c-runtime-manifest.mjs','--check'],{encoding:'utf8'}));
