import assert from 'node:assert/strict';
import {readFileSync,writeFileSync} from 'node:fs';
import path from 'node:path';
import {pathToFileURL} from 'node:url';
const arg=process.argv.indexOf('--out'),sr=process.argv.indexOf('--source-root');if(arg<0||sr<0)throw Error('--out and --source-root required');
const out=path.resolve(process.argv[arg+1]),r=path.resolve(process.argv[sr+1]);
const acorn=await import(pathToFileURL(r+'/.cache/emsdk/upstream/emscripten/node_modules/acorn/dist/acorn.mjs'));
const w=pathToFileURL(out+'/'),read=f=>readFileSync(new URL(f,w),'utf8');
const source=readFileSync(new URL('../js/ported-utilities/sfctool.js',import.meta.url),'utf8'),original=readFileSync(r+'/nethack-c/upstream/util/sfctool.c','utf8');
const inventory=JSON.parse(read('inventory.json')),native=JSON.parse(read('compiler-ast.json'));
function check(text){
 const tree=acorn.parse(text,{ecmaVersion:'latest',sourceType:'module'}),functions=tree.body.filter(n=>n.type==='ExportNamedDeclaration'&&n.declaration?.type==='FunctionDeclaration').map(n=>n.declaration);
 assert.deepEqual(functions.map(n=>[n.id.name,n.params.map(p=>p.name)]),inventory.map(n=>[n.name,n.parameters]));
 const counts=(node,kind)=>{let n=Number(node?.kind===kind||node?.type===kind);for(const x of Object.values(node??{})){if(Array.isArray(x)){for(const y of x)if(y&&typeof y==='object')n+=counts(y,kind);}else if(x&&typeof x==='object')n+=counts(x,kind);}return n;};
 for(const f of functions){const c=native.inner.find(n=>n.kind==='FunctionDecl'&&n.name===f.id.name&&n.inner?.some(v=>v.kind==='CompoundStmt'));assert.ok(c,f.id.name);for(const kind of ['If','While','For','Switch','Return','Break','Continue'])assert.equal(counts(f,kind+'Statement'),counts(c,kind+'Stmt'),f.id.name+' '+kind);}
 const comments=original.match(/\/\*[\s\S]*?\*\//g)||[];
 for(const c of comments)assert.ok(text.includes(c),'missing original comment '+c);
 const table=tree.body.find(n=>n.declaration?.declarations?.[0].id.name==='rensuffixes').declaration.declarations[0].init.elements.map(n=>n.value);
 const expected=original.match(/const char \*const rensuffixes\[\] = \{([\s\S]*?)\};/)[1].match(/"[^"]*"/g).map(s=>JSON.parse(s));assert.deepEqual(table,expected);
 assert.ok(!/\bsizeof\s*\(/.test(text.replace(/\/\*[\s\S]*?\*\//g,'')));
 return{functions:functions.length,originalBlockComments:comments.length,originalNamesFormalsOrder:true,configuredControlCounts:true,rensuffixes:table.length};
}
const result=check(source);let negatives=0;
for(const bad of[source.replace('export function main(argc, argv)','export function main(argv, argc)'),source.replace('while (sz-- !== 0n)','if (sz-- !== 0n)'),source.replace('"IL32LLP64"','"WRONG"')]){assert.throws(()=>check(bad));negatives++;}
writeFileSync(new URL('source-guard.json',w),JSON.stringify({status:'PASS',...result,negativeControls:negatives,commentQualification:'Outside-body annotations stay near original function regions; inactive-only annotations may be archived separately.'},null,2)+'\n');
console.log(JSON.stringify({status:'PASS',...result,negativeControls:negatives}));
