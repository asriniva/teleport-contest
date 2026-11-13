import assert from 'node:assert/strict';
import fs from 'node:fs';
import crypto from 'node:crypto';
import metadata from '../js/nethack/weapon-native-layout.json' with {type:'json'};
import layouts from '../js/wasm/tu-layouts.json' with {type:'json'};
import {createStandaloneEnvironment} from '../js/nethack/environment.js';
import {validateNativeWeaponLayouts} from '../js/nethack/native/weapon-layout.js';
assert.equal(crypto.createHash('sha256').update(fs.readFileSync(metadata.referenceHeader)).digest('hex'),metadata.headerSha256,'independent compiler layout declarations are unchanged');
const {ctypes}=createStandaloneEnvironment();
assert.equal(validateNativeWeaponLayouts(ctypes,layouts.weapon),147);
for(const [key]of metadata.checks){const changed={...layouts.weapon,[key]:Number(layouts.weapon[key])+1};assert.throws(()=>validateNativeWeaponLayouts(ctypes,changed),new RegExp('Review native WEAPON layout '+key+'$'));}
console.log(JSON.stringify({passed:true,independentCompilerLayouts:147,rejectedMutations:147}));
