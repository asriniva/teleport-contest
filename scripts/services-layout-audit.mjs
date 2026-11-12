// Current paths plus a checked inverse for immutable historical source receipts.
import fs from 'node:fs';
import path from 'node:path';
import {historicalCall,currentLayoutPath} from './nethack-layout.mjs';
export function currentSourcePath(file){const p=path.relative(process.cwd(),path.resolve(file)),d=JSON.parse(fs.readFileSync('docs/runtime-environment/services-layout.json'));return currentLayoutPath(d.moves[p]??p);}
export function readBeforeLayout(file,encoding){return historicalCall('scripts/services-layout-audit.mjs','readBeforeLayout',[file,encoding]);}
export function existsBeforeLayout(file){return historicalCall('scripts/services-layout-audit.mjs','existsBeforeLayout',[file]);}
export function writeBeforeLayout(file,bytes){return historicalCall('scripts/services-layout-audit.mjs','writeBeforeLayout',[file,bytes]);}
