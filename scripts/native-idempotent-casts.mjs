// Remove only nested identical, pure compiler-width conversions. Keep every
// operand once, in order; the surviving inner cast retains the original error
// and narrowing semantics, including signed/unsigned 64-bit overflow.
import fs from 'node:fs';import {parse} from 'acorn';
const source=fs.readFileSync(0,'utf8'),ast=parse(source,{ecmaVersion:'latest',sourceType:'module'}),casts=new Set(['int','uint','char','uchar','ushort','boolean','coordxy','long','ulong']),counts={};
const cast=n=>n?.type==='CallExpression'&&n.arguments.length===1&&n.callee?.type==='MemberExpression'&&!n.callee.computed&&n.callee.object.name==='C'&&casts.has(n.callee.property.name)?n.callee.property.name:undefined;
function render(n){if(!n||typeof n!=='object'||n.start===undefined)return '';const name=cast(n);if(name&&cast(n.arguments[0])===name){counts[name]=(counts[name]??0)+1;return render(n.arguments[0]);}let children=[];for(const[k,v]of Object.entries(n)){if(['start','end','loc'].includes(k))continue;for(const child of Array.isArray(v)?v:[v])if(child&&typeof child==='object'&&child.start!==undefined)children.push(child);}children.sort((a,b)=>a.start-b.start);let cursor=n.start,out='';for(const child of children){if(child.start<cursor)continue;out+=source.slice(cursor,child.start)+render(child);cursor=child.end;}return out+source.slice(cursor,n.end);}
const result=render(ast);parse(result,{ecmaVersion:'latest',sourceType:'module'});process.stdout.write(result);process.stderr.write(JSON.stringify({removedIdempotentCasts:counts})+'\n');
