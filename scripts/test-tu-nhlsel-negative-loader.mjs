// Negative control only: a one-unit coordinate error must fail C parity.
import {readFile} from 'node:fs/promises';
export async function load(url,context,next) {
    if(url.endsWith('/js/ported/nhlsel.js')) {
        const original=await readFile(new URL(url),'utf8');
        const source=original.replace('x = C.coordxy(ix);','x = C.coordxy(ix) + 1;');
        if(source===original)throw new Error('NHLSEL negative target missing');
        return {format:'module',source,shortCircuit:true};
    }
    return next(url,context);
}
