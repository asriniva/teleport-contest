// Native memory64 integer promotions from the captured configured AST types.
import fs from 'node:fs';
import {resolve} from 'node:path';import {pathToFileURL} from 'node:url';
const {parse}=await import(pathToFileURL(resolve(process.env.EMSDK??'.cache/emsdk','upstream/emscripten/node_modules/acorn/dist/acorn.mjs')));
const dir=new URL('../../../../../.cache/uhitm-author/',import.meta.url), A=JSON.parse(fs.readFileSync(new URL('ast.json',dir))),F=JSON.parse(fs.readFileSync(new URL('functions.json',dir))),S=JSON.parse(fs.readFileSync(new URL('schema.json',dir)));
const aliases=new Map(A.inner.filter(n=>n.kind==='TypedefDecl').map(n=>[n.name,n.type.desugaredQualType??n.type.qualType]));
function canon(t){for(let i=0;i<16&&aliases.has(t)&&aliases.get(t)!==t;i++)t=aliases.get(t);return t;}
const long=t=>/^(?:unsigned )?(?:long|long long)$/.test(canon(t));
const longFields=new Set(Object.values(S.records).flatMap(fs=>Object.entries(fs).filter(([k,f])=>long(f.type)).map(([k])=>k)));
const returns=new Map(A.inner.filter(n=>n.kind==='FunctionDecl').map(n=>[n.name,long(n.type.qualType.split('(')[0].trim())]));
const macros=new Map([...fs.readFileSync(new URL('macros.txt',dir),'utf8').matchAll(/^#define (\w+)[ \t]+(.*)$/gm)].map(m=>[m[1],m[2]]));
function longMacro(name,seen=new Set()){if(seen.has(name))return false;seen.add(name);let t=macros.get(name)??'';return /\b(?:0x[\da-f]+|\d+)[uU]?[lL]+\b/i.test(t)||[...t.matchAll(/\b[A-Za-z_]\w*\b/g)].some(m=>longMacro(m[0],seen));}
const longNames=new Set(S.constants.filter(n=>longMacro(n)));
for(const[n,t]of macros)if(/^\(?u\.uprops\[\w+\]\.intrinsic\)?$/.test(t.trim()))longNames.add(n);
const filename=process.argv[2];let source=fs.readFileSync(filename,'utf8'),tree=parse(source,{ecmaVersion:'latest',sourceType:'module'}),edits=[],count=0;
function collect(n,locals){if((n.kind==='VarDecl'||n.kind==='ParmVarDecl')&&long(n.type.desugaredQualType??n.type.qualType))locals.add(n.name);for(const c of n.inner??[])collect(c,locals);}
function named(n){return n.type==='MemberExpression'&&!n.computed&&n.property.type==='Identifier'?n.property.name:null;}
function visit(n,locals){
 if(!n)return false;
 for(const[k,v]of Object.entries(n))if(k!=='start'&&k!=='end'){if(Array.isArray(v)){for(const x of v)if(x?.type)visit(x,locals);}else if(v?.type)visit(v,locals);}
 const typeOf=x=>!!x?.isNativeLong;
 const wrap=x=>{edits.push([x.start,'C.long('],[x.end,')']);count++;};
 let is=false;
 if(n.type==='Literal')is=typeof n.value==='bigint';
 else if(n.type==='Identifier')is=locals.has(n.name);
 else if(n.type==='MemberExpression')is=longFields.has(named(n))||(n.object.name==='C'&&longNames.has(named(n)))||(named(n)==='value'&&n.object.type==='Identifier'&&locals.has(n.object.name));
 else if(n.type==='CallExpression'){
  const name=named(n.callee);is=name==='long'||name==='div'&&n.arguments.some(typeOf)||returns.get(name)===true;
 }
 else if(n.type==='UnaryExpression')is=typeOf(n.argument)&&['+','-','~'].includes(n.operator);
 else if(n.type==='BinaryExpression'&&['+','-','*','/','%','&','|','^','<<','>>','>>>'].includes(n.operator)){
  is=typeOf(n.left)||typeOf(n.right);if(is){if(!typeOf(n.left))wrap(n.left);if(!typeOf(n.right))wrap(n.right);}
 }else if(n.type==='ConditionalExpression'){
  is=typeOf(n.consequent)||typeOf(n.alternate);if(is){if(!typeOf(n.consequent))wrap(n.consequent);if(!typeOf(n.alternate))wrap(n.alternate);}
 }else if(n.type==='SequenceExpression')is=typeOf(n.expressions.at(-1));
 else if(n.type==='AssignmentExpression'){
  is=typeOf(n.left);if(is&&n.operator!=='='&&!typeOf(n.right))wrap(n.right);
 }else if(n.type==='UpdateExpression')is=typeOf(n.argument);
 if(n.type==='VariableDeclarator'&&n.id.type==='Identifier'&&locals.has(n.id.name)&&n.init&&!typeOf(n.init)&&n.init.type!=='CallExpression')wrap(n.init);
 n.isNativeLong=is;return is;
}
for(const stmt of tree.body)if(stmt.type==='ExportNamedDeclaration'&&stmt.declaration?.type==='FunctionDeclaration'){
 const fn=stmt.declaration,original=F.find(f=>f.name===fn.id.name),locals=new Set();collect(original,locals);visit(fn.body,locals);
}
// Descending insertions retain exactly one evaluation and original comments.
for(const[at,text]of edits.sort((a,b)=>b[0]-a[0]))source=source.slice(0,at)+text+source.slice(at);
parse(source,{ecmaVersion:'latest',sourceType:'module'});fs.writeFileSync(filename,source);console.log('UHITM captured native integer promotions',count);
