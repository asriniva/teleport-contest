// Provenance for the pre5031c28 ABI, not behavior equivalence on malformed files.
import crypto from 'node:crypto';
export const priorRumorsSha='ed65d74e21b44cc3d384224c2c17b8e8dcf963fbb523c61c24c5f04cfc9cd72a';
const sha=bytes=>crypto.createHash('sha256').update(bytes).digest('hex');
export function priorRumorsSource(bytes){
 if(sha(bytes)!=='b343317f260f82f12fd835b619ffd9f0292f7d6409329c094d0db710bc141791')throw Error('Unreviewed RUMORS source successor');
 const prior=bytes.toString().replace('    C.storeChar(line, 0); // Empty/truncated input must not scan a reused stack buffer.\n','');
 if(sha(prior)!==priorRumorsSha)throw Error('RUMORS source inverse mismatch');
 return Buffer.from(prior);
}
