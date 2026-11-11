// Audit actual component imports; do not impose a Wasm call shape on the game.
import assert from 'node:assert/strict';
import {readFileSync,writeFileSync,mkdirSync} from 'node:fs';
import path from 'node:path';
import {fileURLToPath} from 'node:url';
import {callbackNames} from '../js/ported/nhlsel.js';
const root=fileURLToPath(new URL('../',import.meta.url));
const directory=path.resolve(process.env.TELEPORT_NHLSEL_PROBE_DIR||path.join(root,'.cache/tu-probes'));
const imports=mode=>WebAssembly.Module.imports(new WebAssembly.Module(readFileSync(path.join(directory,'nhlsel-'+mode+'.wasm')))).map(x=>x.name);
const selection=name=>name.startsWith('l_selection_')||name.startsWith('teleport_nhlsel_');
const expected=[...callbackNames.map(name=>'teleport_nhlsel_'+name),'l_selection_check','l_selection_push_copy','l_selection_register','teleport_nhlsel_test_l_selection_push_new','teleport_nhlsel_test_params_sel_2coords'];
assert.equal(callbackNames.length,28);
assert.deepEqual(imports('reference').filter(selection),[],'original reference functions execute in C');
const hybrid=imports('hybrid').filter(selection);
assert.deepEqual([...hybrid].sort(),[...expected].sort(),'all 33 component entry routes really import JS');
const out=path.join(root,'.cache/nhlsel-current-run');mkdirSync(out,{recursive:true});writeFileSync(path.join(out,'imports.json'),JSON.stringify({status:'PASS',scope:'isolated C-consumer component pair',referenceSelectionImports:[],hybridSelectionImports:hybrid,gameImportShapeRequired:false},null,2)+'\n');
console.log('NHLSEL component imports: original reference stays C; all 33 hybrid entry routes import JS.');
