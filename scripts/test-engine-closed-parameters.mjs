import assert from 'node:assert/strict';
import fs from 'node:fs';
import {parse} from '../.cache/emsdk/upstream/emscripten/node_modules/acorn/dist/acorn.mjs';
import {closedParameterProofs} from './branch-coverage/closed-parameters.mjs';
import {instrument} from './branch-coverage/instrument.mjs';
const proofs=source=>closedParameterProofs(parse(source,{ecmaVersion:'latest',sourceType:'module'}));
const source='function helper(sk){if(!sk)return 1;else{do{}while(sk);}}export function run(){return helper(0);}';
assert.equal(proofs(source).length,1);
let checks=1;
for(const changed of [
 source.replace('helper(0)','helper(1)')+'helper(0);',
 source+'const alias=helper;',
 source+'export {helper};',
 source.replace('function helper','export function helper'),
 source.replace('if(!sk)','sk=1;if(!sk)'),
 source.replace('if(!sk)','sk++;if(!sk)'),
 source.replace('if(!sk)','let sk2=0;({x:sk}={x:1});if(!sk)'),
 source.replace('if(!sk)','for(sk of [1]){}if(!sk)'),
 source.replace('if(!sk)','function nested(sk){return sk;}if(!sk)'),
 source.replace('if(!sk)','{let sk=1;if(!sk)return 2;}if(!sk)'),
 source.replace('if(!sk)','try{}catch(sk){}if(!sk)'),
 source.replace('if(!sk)','eval("sk=1");if(!sk)'),
 source.replace('return 1','return helper(1)'),
 source.replace('helper(0)','helper(...[1])'),
 'function helper(x,sk){if(!sk)return 1;return 2;}export function run(){return helper(...[0,1],0);}',
]){assert.equal(proofs(changed).length,0,changed);checks++;}
const recursive='function helper(n,sk){if(!sk)return n?helper(n-1,sk):1;return 2;}export function run(){return helper(3,0);}';
assert.equal(proofs(recursive).length,1);checks++;
const file='js/ported/strutil.js',actual=fs.readFileSync(file,'utf8'),found=proofs(actual);
assert.equal(found.length,1);assert.equal(found[0].function,'pmatch_internal');assert.equal(found[0].parameter,'sk');checks++;
const sites=instrument(actual,file).sites;
const excluded=sites.reduce((n,s)=>n+(s.unreachableProof?s.arms.length:s.constantProofKind==='closed-parameter'?s.arms.length-1:0),0);
assert.equal(excluded,5);checks++;
console.log('PASS: '+checks+' closed-parameter proof controls; aliases, exports, writes, shadowing, eval, changing arguments and spread reject exclusion; exactly5 unreachable STRUTIL outcomes proved.');
