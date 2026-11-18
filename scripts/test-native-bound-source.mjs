import fs from 'node:fs';
import assert from 'node:assert/strict';
import {parse} from 'acorn';
function clean(v){if(Array.isArray(v))return v.map(clean);if(!v||typeof v!=='object')return v;return Object.fromEntries(Object.entries(v).filter(([k])=>!['start','end','raw'].includes(k)).map(([k,x])=>[k,clean(x)]));}
for(const [name,factory]of [['mondata','createNativeMondata'],['stairs','createNativeStairs'],['artifact','createNativeArtifact'],['uhitm','createNativeUhitm'],['makemon','createNativeMakemon'],['hacklib','createNativeHacklib'],['wintty','createNativeWintty'],['getpos','createNativeGetpos'],['pline','createNativePline'],['do','createNativeDo'],['weapon','createNativeWeapon'],['do_wear','createNativeDoWear'],['objnam','createNativeObjnam'],['do_name','createNativeDoName']]){
 const before=parse(fs.readFileSync('js/ported/'+name+'.js','utf8'),{ecmaVersion:'latest',sourceType:'module'}),after=parse(fs.readFileSync('js/nethack/native/'+name+'.js','utf8'),{ecmaVersion:'latest',sourceType:'module'});
 const fn=after.body.find(node=>node.type==='ExportNamedDeclaration').declaration;assert.equal(fn.id.name,factory);assert.deepEqual(fn.params.map(x=>x.name),['C']);
 if(name==='pline'){
  // Undo only the reviewed native history storage operations before checking
  // every original policy statement and its call/RNG order.
  let historyReads=0,historyWrites=0,copies=0;
  function invert(n){if(!n||typeof n!=='object')return n;if(Array.isArray(n))return n.map(invert);
   const member=(object,property)=>({type:'MemberExpression',object,property:{type:'Identifier',name:property},computed:false,optional:false});
   const saved=()=>member(member({type:'Identifier',name:'C'},'gs'),'saved_plines');
   if(n.type==='CallExpression'&&n.callee?.object?.name==='C'){
    const method=n.callee.property.name;
    if(method==='savedMessages'){historyReads++;return saved();}
    if(method==='setSavedMessage'){historyWrites++;return {type:'AssignmentExpression',operator:'=',left:{type:'MemberExpression',object:saved(),property:invert(n.arguments[0]),computed:true,optional:false},right:invert(n.arguments[1])};}
    if(method==='copySavedMessage'){copies++;return {...n,callee:member({type:'Identifier',name:'C'},'dupstr'),arguments:[invert(n.arguments[1])]};}
   }
   return Object.fromEntries(Object.entries(n).map(([k,v])=>[k,invert(v)]));
  }
  fn.body=invert(fn.body);assert.deepEqual([historyReads,historyWrites,copies],[3,2,1]);
 }
 const expected=before.body.filter(n=>n.type!=='ImportDeclaration').map(n=>n.type==='ExportNamedDeclaration'?n.declaration:n);
 assert.deepEqual(clean(fn.body.body.slice(0,-1)),clean(expected),'complete source policy '+name);
 const names=before.body.filter(n=>n.type==='ExportNamedDeclaration').flatMap(n=>n.declaration.id?[n.declaration.id.name]:n.declaration.declarations.map(d=>d.id.name));
 assert.deepEqual(fn.body.body.at(-1).argument.properties.map(p=>p.key.name),names,'all source exports stay connected');
 console.log(JSON.stringify({passed:true,module:name,functions:expected.filter(n=>n.type==='FunctionDeclaration').length,sourcePolicyAstEqual:true}));
}
