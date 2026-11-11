// Conversions at actual C scalar local assignment/initialization boundaries.
import fs from 'node:fs';import {resolve as resolveSdkPath} from 'node:path';import {pathToFileURL as sdkFileURL,fileURLToPath as sdkURLPath} from 'node:url';
const toplSourceRoot=sdkURLPath(new URL('../../../../../',import.meta.url));
const {parse}=await import(sdkFileURL(resolveSdkPath(process.env.EMSDK??resolveSdkPath(toplSourceRoot,'.cache/emsdk'),'upstream/emscripten/node_modules/acorn/dist/acorn.mjs')));
const F=JSON.parse(fs.readFileSync(resolveSdkPath(toplSourceRoot,'.cache/topl-author/functions.json'))),filename=process.argv[2];let source=fs.readFileSync(filename,'utf8'),tree=parse(source,{ecmaVersion:'latest',sourceType:'module'}),edits=[],count=0;
const kind=t=>({'int':'int','unsigned int':'uint','unsigned':'uint','long':'long','char':'char','signed char':'char','short':'short'}[t]);
function collect(n,locals){if(['VarDecl','ParmVarDecl'].includes(n.kind)){const k=kind(n.type.desugaredQualType??n.type.qualType);if(k)locals.set(n.name,k);}for(const c of n.inner??[])collect(c,locals);}
function visit(n,locals){
 if(n.type==='VariableDeclarator'&&n.id.type==='Identifier'&&locals.has(n.id.name)&&n.init){edits.push([n.init.start,'C.'+locals.get(n.id.name)+'('],[n.init.end,')']);count++;}
 if(n.type==='AssignmentExpression'&&n.left.type==='Identifier'&&locals.has(n.left.name)&&n.operator==='='){edits.push([n.right.start,'C.'+locals.get(n.left.name)+'('],[n.right.end,')']);count++;}
 for(const v of Object.values(n))if(Array.isArray(v)){for(const c of v)if(c?.type)visit(c,locals);}else if(v?.type)visit(v,locals);
}
for(const stmt of tree.body)if(stmt.type==='ExportNamedDeclaration'&&stmt.declaration?.type==='FunctionDeclaration'){const fn=stmt.declaration,locals=new Map();collect(F.find(f=>f.name===fn.id.name),locals);visit(fn.body,locals);}
for(const[at,text]of edits.sort((a,b)=>b[0]-a[0]))source=source.slice(0,at)+text+source.slice(at);parse(source,{ecmaVersion:'latest',sourceType:'module'});fs.writeFileSync(filename,source);console.log('TOPL actual scalar local conversions',count);
