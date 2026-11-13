// Conservative ESM call-graph proof. No exported/aliased functions, eval,
// mutable or shadowed parameters, or unknown call arguments are accepted.
const children=node=>Object.entries(node).filter(([key])=>!['loc','start','end','type'].includes(key)).map(([,value])=>value);
function walk(node,visit,parent){
 if(!node||typeof node!=='object')return;
 if(Array.isArray(node)){for(const child of node)walk(child,visit,parent);return;}
 if(!node.type)return;visit(node,parent);for(const child of children(node))walk(child,visit,node);
}
const contains=(node,name)=>{let found=false;walk(node,n=>{if(n.type==='Identifier'&&n.name===name)found=true;});return found;};
export function closedParameterProofs(ast){
 const functions=ast.body.filter(node=>node.type==='FunctionDeclaration'&&node.id&&node.params.every(p=>p.type==='Identifier'));
 const references=new Map(functions.map(fn=>[fn.id.name,[]]));
 let evalPresent=false;walk(ast,(node,parent)=>{
  if(node.type==='CallExpression'&&node.callee.type==='Identifier'&&node.callee.name==='eval')evalPresent=true;
  if(node.type==='Identifier'&&references.has(node.name))references.get(node.name).push({node,parent});
 });
 if(evalPresent)return[];
 const proofs=[];
 for(const fn of functions){
  for(const [index,param]of fn.params.entries()){
   let valid=true,anchor=false,value,known=false;
   walk(fn.body,node=>{
    const binding=node.type==='VariableDeclarator'?node.id:node.type==='CatchClause'?node.param:['FunctionDeclaration','ClassDeclaration','FunctionExpression','ClassExpression'].includes(node.type)?node.id:undefined;
    if(binding&&contains(binding,param.name))valid=false;
    if(/^(?:FunctionDeclaration|FunctionExpression|ArrowFunctionExpression)$/.test(node.type)&&node.params.some(p=>contains(p,param.name)))valid=false;
    if(node.type==='AssignmentExpression'&&contains(node.left,param.name))valid=false;
    if(node.type==='UpdateExpression'&&contains(node.argument,param.name))valid=false;
    if(['ForInStatement','ForOfStatement'].includes(node.type)&&contains(node.left,param.name))valid=false;
   });
   for(const {node,parent}of references.get(fn.id.name)){
    if(node===fn.id)continue;
    if(parent?.type!=='CallExpression'||parent.callee!==node||parent.optional){valid=false;continue;}
    if(parent.arguments.slice(0,index+1).some(argument=>argument.type==='SpreadElement')){valid=false;continue;}
    const argument=parent.arguments[index],inside=parent.start>=fn.body.start&&parent.end<=fn.body.end;
    if(inside&&argument?.type==='Identifier'&&argument.name===param.name)continue;
    if(argument?.type!=='Literal'||argument.regex){valid=false;continue;}
    if(known&&!Object.is(value,argument.value)){valid=false;continue;}
    known=true;value=argument.value;if(!inside)anchor=true;
   }
   if(!valid||!known||!anchor)continue;
   const reason='Closed ESM function '+fn.id.name+' parameter '+param.name+' has one literal entry value ('+typeof value+':'+String(value)+'); recursive calls preserve it; no escape, eval, writes or shadowing.';
   walk(fn.body,node=>{
    if(node.type!=='IfStatement')return;
    const direct=node.test.type==='Identifier'&&node.test.name===param.name;
    const negated=node.test.type==='UnaryExpression'&&node.test.operator==='!'&&node.test.argument.type==='Identifier'&&node.test.argument.name===param.name;
    if(!direct&&!negated)return;
    const taken=negated?!value:Boolean(value),dead=taken?node.alternate:node.consequent;
    proofs.push({test:node.test,arm:taken?0:1,dead,reason,parameter:param.name,function:fn.id.name});
   });
  }
 }
 return proofs;
}
