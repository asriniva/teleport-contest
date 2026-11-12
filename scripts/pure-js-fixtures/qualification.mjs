// Development-only qualification of this migration's exact reviewed changes.
// Historical cleanup pins stay immutable; current execution has its own receipt.
import fs from 'node:fs';
import os from 'node:os';
import path from 'node:path';
import crypto from 'node:crypto';
import {execFileSync} from 'node:child_process';
export const migrationFiles=new Set([
 'js/backends/emscripten/runtime.js','js/c-runtime/adapter-factories.js',
 'js/c-runtime/libc.js','js/c-runtime/scanf.js','js/c-runtime/stdio.js',
 'js/c-runtime/stdlib.js','js/c-runtime/vfs.js','js/c-runtime/environment.js',
 'js/c-runtime/errno.js','js/c-runtime/errno-messages.json','js/lua/abi.js',
 'js/lua/lapi.js','js/lua/bytecode-vm.js','js/lua/io-library.js',
 'js/nethack/runtime.js','js/ported/rumors.js','js/standalone/environment.js',
 'js/standalone/light-abi.json','js/standalone/light.js','js/standalone/lua.js',
 'scripts/test-tu-topl.mjs','scripts/test-js-posix-regex.mjs',
 'scripts/relocate-runtime-layout.py','scripts/extract-binding-infrastructure.mjs','scripts/check-services-layout.mjs',
 'scripts/test-allocation-cli-layered-audits.py','scripts/allocation_cli_source_successors.py','scripts/test-post-default-successors.py','scripts/post_default_successors.py','scripts/services-layout-audit.mjs','scripts/services_layout_audit.py',
 'scripts/check-standalone-scope.mjs','scripts/write-c-runtime-manifest.mjs',
]);
const sha=bytes=>crypto.createHash('sha256').update(bytes).digest('hex');
export function qualifiedHistorical(file,expected){
 if(!migrationFiles.has(file))throw Error('Unqualified migration source: '+file);
 const declaration=JSON.parse(fs.readFileSync('docs/runtime-environment/pure-js-source-changes.json'));
 if(declaration.baselineCommit!=='cc8ef80b7ac93c01feac7e40677aec0d3d63c03a'||Object.keys(declaration.files).some(p=>!migrationFiles.has(p)))throw Error('Unreviewed migration qualification cohort');
 const row=declaration.files[file];if(!row)throw Error('Missing migration qualification: '+file);
 const actual=file==='js/c-runtime/stdio.js'&&fs.existsSync('docs/runtime-environment/stdio-byte-source-successors.json')?execFileSync('python3',['scripts/stdio_byte_source_successors.py','--file',file]):fs.readFileSync(file);if(sha(actual)!==row.afterSha256)throw Error('Migration source changed after validation: '+file);
 const before=row.beforeSha256===null?Buffer.alloc(0):execFileSync('git',['show',declaration.baselineCommit+':'+file]);
 if(row.beforeSha256!==null&&sha(before)!==row.beforeSha256)throw Error('Historical migration source differs: '+file);
 const patch=fs.readFileSync(row.patch);if(sha(patch)!==row.patchSha256)throw Error('Migration patch changed: '+file);
 const canonical=(()=>{const directory=fs.mkdtempSync(path.join(os.tmpdir(),'migration-source-')),input=path.join(directory,'input.json');try{fs.writeFileSync(input,JSON.stringify({file,before:before.toString(),after:actual.toString()}));return execFileSync('python3',['-c',"import sys,json,difflib;d=json.load(open(sys.argv[1]));sys.stdout.write(''.join(difflib.unified_diff(d['before'].splitlines(keepends=True),d['after'].splitlines(keepends=True),fromfile='a/'+d['file'],tofile='b/'+d['file'])))",input],{maxBuffer:16*1024*1024});}finally{fs.rmSync(directory,{recursive:true,force:true});}})();
 if(!canonical.equals(patch))throw Error('Migration patch is not exact: '+file);
 if(expected!==undefined&&sha(before)!==expected){
  // Later committed features retain their own native proof and immutable pins.
  const successor=JSON.parse(fs.readFileSync('docs/runtime-environment/post-default-source-successors.json'));
  if(successor.files[file]?.afterSha256===expected)execFileSync('python3',['scripts/post_default_successors.py','--check'],{stdio:'pipe'});
  else if(JSON.parse(fs.readFileSync('docs/runtime-environment/c-runtime-manifest.json')).sha256[file]!==expected)throw Error('Historical migration source differs: '+file);
  const committed=execFileSync('git',['show','8b834cd2b94a10bc1a96336de0bd91f90d3adf2b:'+file]);
  if(sha(committed)!==expected)throw Error('Historical migration source differs: '+file);
  return committed;
 }
 return before;
}
