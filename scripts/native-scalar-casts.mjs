// Specialize only proven finite primitive values; unknown values keep the ABI.
import fs from 'node:fs';import {parse} from 'acorn';import {pathToFileURL} from 'node:url';
const options={ecmaVersion:'latest',sourceType:'module'},widths={int:32,uint:32,char:8,uchar:8,short:16,ushort:16,boolean:8,coordxy:16},unsigned=new Set(['uint','uchar','ushort']);
export function compileNativeScalarCasts(source,{measured,roots={},parameters={}}={}){
 const ast=parse(source,options),counts={numeric:0,wideConstants:0,byCast:{},measuredFields:0};
 let currentFunction,opaqueC=false;const parameterTypes=new Map();function collect(n){if(!n||typeof n!=='object')return;if(n.type==='FunctionDeclaration'&&parameters[n.id.name])parameterTypes.set(n.id.name,Object.fromEntries(n.params.map((p,i)=>[p.name,parameters[n.id.name][i]])));for(const v of Object.values(n))if(Array.isArray(v))v.forEach(collect);else if(v&&typeof v==='object')collect(v);}collect(ast);
 const canonical=t=>{for(let i=0;i<32;i++){const value=t.replace(/\bconst\s+/g,'').replace(/\s+/g,' ').trim(),next=measured?.aliases?.[value];if(!next)return value;t=next;}throw Error('C alias cycle');};
 function typeOf(n){if(opaqueC)return;if(n?.type==='Identifier')return parameterTypes.get(currentFunction)?.[n.name];if(n?.type!=='MemberExpression')return;if(n.object?.name==='C'&&!n.computed)return roots[n.property.name];const parent=typeOf(n.object);if(!parent)return;const type=canonical(parent);if(n.computed){const a=type.match(/^(.*?)\[\d*\](.*)$/);return a?a[1]+a[2]:undefined;}const key=type.replace(/\s*\*$/,'').replace(/^(struct |union )/,'');const field=measured?.records?.[key]?.fields[n.property.name];if(!field)return;if(field.bits!==undefined)return field.bits<=32?'unsigned int':undefined;return field.ctype.replace(new RegExp('\\s+'+n.property.name+'$'),'');}
 const primitiveRanges={'char':[-128,127],'signed char':[-128,127],'unsigned char':[0,255],short:[-32768,32767],'unsigned short':[0,65535],int:[-2147483648,2147483647],'unsigned int':[0,4294967295],_Bool:[0,1],bool:[0,1]};
 const cast=n=>!opaqueC&&n?.type==='CallExpression'&&n.arguments.length===1&&n.callee?.type==='MemberExpression'&&!n.callee.computed&&n.callee.object?.name==='C'?n.callee.property.name:undefined;
 const bounded=(lo,hi)=>Number.isFinite(lo)&&Number.isFinite(hi)?[lo,hi]:undefined;
 function range(n){if(!n)return;
  const fieldType=typeOf(n);if(fieldType){const known=primitiveRanges[canonical(fieldType)];if(known){counts.measuredFields++;return known;}}
  if(n.type==='Literal'){if(typeof n.value==='number'&&Number.isInteger(n.value))return[n.value,n.value];if(typeof n.value==='boolean')return[0,1];return;}
  const name=cast(n);if(widths[name]){const bits=widths[name];return unsigned.has(name)?[0,2**bits-1]:[-(2**(bits-1)),2**(bits-1)-1];}
  if(n.type==='UnaryExpression'){if(n.operator==='!')return[0,1];const a=range(n.argument);if(!a)return;if(n.operator==='-')return[-a[1],-a[0]];if(n.operator==='+')return a;if(n.operator==='~')return[-2147483648,2147483647];return;}
  if(n.type==='BinaryExpression'){
   if(['===','!==','==','!=','<','<=','>','>=','in','instanceof'].includes(n.operator))return[0,1];
   if(n.operator==='>>>')return[0,4294967295];const a=range(n.left),b=range(n.right);if(!a||!b)return;
   if(['&','|','^','<<','>>'].includes(n.operator))return[-2147483648,2147483647];
   if(n.operator==='+')return bounded(a[0]+b[0],a[1]+b[1]);if(n.operator==='-')return bounded(a[0]-b[1],a[1]-b[0]);
   if(n.operator==='*'){const values=[a[0]*b[0],a[0]*b[1],a[1]*b[0],a[1]*b[1]];return bounded(Math.min(...values),Math.max(...values));}
   if(n.operator==='/'&&b[0]===b[1]&&Math.abs(b[0])===1){const values=[a[0]/b[0],a[0]/b[1],a[1]/b[0],a[1]/b[1]];return bounded(Math.min(...values),Math.max(...values));}
   return;
  }
  if(n.type==='ConditionalExpression'||n.type==='LogicalExpression'){const a=range(n.type==='ConditionalExpression'?n.consequent:n.left),b=range(n.type==='ConditionalExpression'?n.alternate:n.right);return a&&b?bounded(Math.min(a[0],b[0]),Math.max(a[1],b[1])):undefined;}
  if(n.type==='SequenceExpression')return range(n.expressions.at(-1));if(n.type==='AssignmentExpression'&&n.operator==='=')return range(n.right);
 }
 function constant(n){if(n.type==='Literal'&&(typeof n.value==='bigint'||typeof n.value==='number'&&Number.isSafeInteger(n.value)))return n.value;if(n.type==='UnaryExpression'&&n.operator==='-'){const v=constant(n.argument);if(v!==undefined)return -v;}}
 function render(n){if(!n||typeof n!=='object'||n.start===undefined)return '';
  const before=currentFunction,previousOpaque=opaqueC;if(['FunctionDeclaration','FunctionExpression','ArrowFunctionExpression'].includes(n.type)){if(currentFunction&&n.params.some(p=>p.name==='C'))opaqueC=true;currentFunction=n.id?.name;}const name=cast(n);
  if(widths[name]&&range(n.arguments[0])){counts.numeric++;counts.byCast[name]=(counts.byCast[name]??0)+1;const v='('+render(n.arguments[0])+')';return name==='uint'?'('+v+'>>>0)':name==='uchar'?'('+v+'&255)':name==='ushort'?'('+v+'&65535)':widths[name]===8?'('+v+'<<24>>24)':widths[name]===16?'('+v+'<<16>>16)':'('+v+'|0)';}
  if(name==='long'||name==='ulong'){const value=constant(n.arguments[0]);if(value!==undefined){counts.wideConstants++;return '('+BigInt[name==='long'?'asIntN':'asUintN'](64,BigInt(value))+'n)';}}
  const children=[];for(const[k,v]of Object.entries(n)){if(['start','end','loc'].includes(k))continue;for(const child of Array.isArray(v)?v:[v])if(child&&typeof child==='object'&&child.start!==undefined)children.push(child);}children.sort((a,b)=>a.start-b.start);let cursor=n.start,out='';for(const child of children){if(child.start<cursor)continue;out+=source.slice(cursor,child.start)+render(child);cursor=child.end;}const result=out+source.slice(cursor,n.end);currentFunction=before;opaqueC=previousOpaque;return result;
 }
 const code=render(ast);parse(code,options);return{code,counts};
}
export function nativeScalarMetadata(unit){
 const measured=JSON.parse(fs.readFileSync('js/nethack/records.json','utf8')),roots={u:'struct you',flags:'struct flag',iflags:'struct instance_flags',svm:'struct instance_globals_saved_m',svl:'struct instance_globals_saved_l',gy:'struct instance_globals_y',mons:'struct permonst[]',objects:'struct objclass[]',levl:'struct rm[][]'},parameters={};
 if(unit==='mon'){const abi=JSON.parse(fs.readFileSync('js/nethack/mon-abi.json'));for(const [name,kinds]of Object.entries(abi.argumentKinds))parameters[name]=kinds.map(kind=>abi.schema[kind]?.[0]);}
 if(unit==='monmove'){const abi=JSON.parse(fs.readFileSync('js/nethack/monmove-abi.json')),binding=fs.readFileSync('js/nethack/bindings/monmove.js','utf8'),d=parse(binding,options).body.flatMap(n=>n.type==='VariableDeclaration'?n.declarations:[]).find(n=>n.id.name==='argumentTypes');if(!d)throw Error('Missing MONMOVE argument plans');const args=JSON.parse(binding.slice(d.init.start,d.init.end)),kinds={monster:'mon',object:'obj',permonst:'pm',candidateData:'mfp',coord:'coord',attack:'attack'};for(const[name,types]of Object.entries(args))parameters[name]=Object.fromEntries(Object.entries(types).map(([index,kind])=>[index,abi.schema[kinds[kind]]?.[0]]));}
 return{measured,roots,parameters};
}
if(process.argv[1]&&import.meta.url===pathToFileURL(process.argv[1]).href){const unit=process.argv[process.argv.indexOf('--unit')+1],{code,counts}=compileNativeScalarCasts(fs.readFileSync(0,'utf8'),process.argv.includes('--measured-roots')?nativeScalarMetadata(process.argv.includes('--unit')?unit:undefined):undefined);process.stdout.write(code);process.stderr.write(JSON.stringify({nativeScalarCasts:counts})+'\n');}
