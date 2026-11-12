// Rebase private wrong-code candidates while retaining their intended bad core.
import path from 'node:path';
import {pathToFileURL,fileURLToPath} from 'node:url';
import {parse} from '../.cache/emsdk/upstream/emscripten/node_modules/acorn/dist/acorn.mjs';
export function rebaseTestModule(source,owner,redirects=new Map()){
 const filename=owner instanceof URL?fileURLToPath(owner):owner;
 const ast=parse(source,{ecmaVersion:'latest',sourceType:'module'});
 const nodes=ast.body.filter(n=>n.type==='ImportDeclaration'||n.source&&n.type.startsWith('Export')).map(n=>n.source);
 for(const n of nodes.reverse())if(n.value.startsWith('.')){
  const target=path.resolve(path.dirname(filename),n.value),url=redirects.get(target)??pathToFileURL(target).href;
  source=source.slice(0,n.start)+JSON.stringify(url)+source.slice(n.end);
 }
 return source;
}
