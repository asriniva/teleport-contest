// Historical ABI provenance only. This does not establish behavior equivalence
// between the old forced-native pointer formatting and the new caller profile.
import crypto from 'node:crypto';
export const priorRuntimeSha='5322fc2cb40783ef7c475861cecb9eaa68ddf26eb12f8618f1bd3e480d3e4371';
export const currentRuntimeSha='6b83a93aa7768916cb34c2461de2f477c96eae51894e0980d38e5113bf2ae026';
export const priorJsRuntimeSha='8d36f8c8e16edbaf216d0938205ffaef0f1644c7f4836cd4a740b16bd7a0aff3';
const sha=value=>crypto.createHash('sha256').update(value).digest('hex');
export function priorReferenceRuntime(bytes){
 if(sha(bytes)!==currentRuntimeSha)throw Error('Unreviewed reference runtime successor');
 let source=bytes.toString();
 source=source.replace("export function createPortedRuntime(layouts, {pointerFormat='caller'}={}) {\n    if (!['caller','native'].includes(pointerFormat)) throw new TypeError('Unknown pointer formatting profile '+pointerFormat);",'export function createPortedRuntime(layouts) {');
 source=source.replace("            // Preserve the configured caller profile unless the embedding\n            // explicitly requests native formatting for a native-C comparison.\n            if (pointerFormat === 'native') environment.fmt_ptr = value => {",'            environment.fmt_ptr = value => {');
 if(sha(source)!==priorRuntimeSha)throw Error('Reference runtime inverse mismatch');
 return Buffer.from(source);
}
export function priorJsRuntimeSource(bytes){
 if(sha(bytes)!=='305102b64ae5f0e5db379b0d245529c3ae2c765af9294d100053ff49dfceee2d')throw Error('Unreviewed JS runtime source successor');
 const prior=bytes.toString().replace('const libc = createCStdlib(memory,options.libc);','const libc = createCStdlib(memory);');
 if(sha(prior)!==priorJsRuntimeSha)throw Error('JS runtime inverse mismatch');
 return Buffer.from(prior);
}
