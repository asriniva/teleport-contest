import './pure-js-probes/deny-wasm.mjs';
import fs from 'node:fs';import assert from 'node:assert/strict';import path from 'node:path';import {pathToFileURL} from 'node:url';
import {createStandaloneEnvironment} from '../js/nethack/environment.js';
import {C,R,T} from '../js/c-runtime/context.js';
const layouts=JSON.parse(fs.readFileSync('js/wasm/tu-layouts.json'));
let owners=0,contracts=0;const inventory=[];
for(const name of fs.readdirSync('js/nethack').filter(name=>name.endsWith('.js')).sort()){
 const file='js/nethack/'+name,source=fs.readFileSync(file,'utf8');
 // Select only the simple, early, named-field ABI guard. Unsupported factory
 // shapes are reported by the coverage inventory, never silently called tested.
 const abiImport=source.match(/import\s+abi\s+from\s*['"]([^'"]+)['"]/),factory=source.match(/export function (enable\w+)\(environment,layouts\)/),layout=source.match(/\bL=layouts\.(\w+)/),guard=source.match(/for\s*\(\s*const\s*\[k,v\]\s*of\s*Object\.entries\(abi\.layout\)\s*\)\s*if\s*\(L\[k\]!==v\)\s*throw new Error\((['"])(.*?)\1\s*\+\s*k\)/);
 if(!abiImport||!factory||!layout||!guard)continue;
 const abi=JSON.parse(fs.readFileSync(path.resolve(path.dirname(file),abiImport[1]))),profile=layout[1],enable=(await import(pathToFileURL(path.resolve(file))))[factory[1]],env=createStandaloneEnvironment();
 if(profile==='dbridge'){
  // DBRIDGE extends an existing terrain owner. Assemble that real prerequisite
  // in production order, stopping before installing DBRIDGE itself.
  env.enableStdio();env.enableSdkBoundary();env.enableDecl(layouts.decl);env.enableDrawing(layouts.drawing);env.enableObjects(layouts.objects);env.enableMonst(layouts.monst);
  env.enableSerialization(layouts);env.enableRnd(layouts.rnd,{initialize:false});env.enableAddressPort('dungeon',{only:['ledger_no','maxledgerno']});
  env.enableObjectState(layouts);env.enableObjectRecords(layouts);env.enableItemInventory(layouts);env.enableTimers(layouts);env.enableItemNaming(layouts);env.enableMonsterSelection(layouts);env.enableMonsterCreation(layouts);
  env.enableGameStartup(layouts);env.enableHeroStartup(layouts);env.enableWorldPosition(layouts);
 }
 assert.ok(Object.keys(abi.layout).length);owners++;
 function stack(){const mark=env.transport.stackSave();try{return mark.index;}finally{env.transport.stackRestore(mark);}}
 const before=stack(),buffer=env.memory.HEAPU8.buffer;
 for(const [field,value]of Object.entries(abi.layout)){
  assert.deepEqual(layouts[profile][field],value,'configured C ABI baseline '+file+':'+field);
  const corrupt=typeof value==='number'?value+1:typeof value==='boolean'?!value:String(value)+' invalid';
  const invalid={...layouts,[profile]:{...layouts[profile],[field]:corrupt}};
  assert.throws(()=>enable(env,invalid),error=>error instanceof Error&&error.message===guard[2]+field,file+':'+field+' exact rejected field');
  assert.equal(stack(),before,'ABI rejection restores stack');assert.equal(env.memory.HEAPU8.buffer,buffer,'no heap growth before validation');
  assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);contracts++;
 }
 inventory.push({file,profile,factory:factory[1],fields:Object.keys(abi.layout).length});
}
assert.equal(owners,17,'review discovery changes explicitly');assert.ok(contracts>1000);
fs.mkdirSync('.cache/engine-abi-rejections',{recursive:true});fs.writeFileSync('.cache/engine-abi-rejections/evidence.json',JSON.stringify({owners,contracts,inventory,scope:'Malformed measured-ABI JS boundary contracts, not original-C game-policy cases.'},null,2)+'\n');
console.log('PASS:'+contracts+' single-field ABI rejection contracts across'+owners+' production owners; exact diagnostics, stack/context restoration and no heap growth; Wasm/network unavailable.');
