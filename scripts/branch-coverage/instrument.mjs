// Test-only instrumentation: preserve operand values, evaluation order and source files.
import crypto from 'node:crypto';
import {parse} from 'acorn';
import {closedParameterProofs} from './closed-parameters.mjs';
export const version=1;
export function instrument(source,file){
 const tokens=[],ast=parse(source,{ecmaVersion:'latest',sourceType:'module',locations:true,onToken:tokens}),sites=[],wraps=[],inserts=[],replacements=[],parameterEntries=new WeakMap(),localCompletions=new WeakMap(),parents=new WeakMap();
 const fallback={optionalReceiver:'((_f,_i,v)=>v)',optionalValue:'((_f,_i,v)=>v)',iterable:'((_f,_i,v)=>v)',switchValue:'((_t,v)=>v)',caseValue:'((_t,v)=>v)'};
 const call=(method,args)=>'globalThis.__nethackBranchCoverage.'+method+'('+JSON.stringify(file)+','+args+')';
 function site(node,kind,arms,owner){const id=sites.length;sites.push({id,key:kind+':'+node.start+':'+node.end,kind,arms,line:node.loc.start.line,column:node.loc.start.column,start:node.start,end:node.end,function:owner});return id;}
 function optionalWrap(node,method,id){wrap(node,'(globalThis.__nethackBranchCoverage.'+method+'??'+fallback[method]+')('+JSON.stringify(file)+','+id+',(', '))');}
 function wrap(node,open,close){wraps.push({start:node.start,end:node.end,open,close,order:wraps.length});}
 function bindingDefaults(pattern,callback){
  if(!pattern)return;
  if(pattern.type==='AssignmentPattern'){callback(pattern);bindingDefaults(pattern.left,callback);}
  else if(pattern.type==='ObjectPattern')for(const property of pattern.properties)bindingDefaults(property.value??property.argument,callback);
  else if(pattern.type==='ArrayPattern')for(const item of pattern.elements)bindingDefaults(item,callback);
  else if(pattern.type==='RestElement')bindingDefaults(pattern.argument,callback);
 }
 function decision(node,kind,owner,operator){const id=site(node,kind,['taken','not-taken'],owner);if(node.type==='Literal'&&!node.regex){let taken;if(operator==='??')taken=node.value===null;else if(operator==='||')taken=!node.value;else if(operator==='nonnull')taken=node.value!==null;else taken=Boolean(node.value);sites[id].constantArm=taken?0:1;sites[id].constantProof='literal '+source.slice(node.start,node.end);}wrap(node,call('decision',id+','+JSON.stringify(operator??'truthy')+',(').slice(0,-1),'))');}
 function visit(node,owner='<module>',parent){
  if(!node||typeof node!=='object')return;
  if(Array.isArray(node)){for(const child of node)visit(child,owner,parent);return;}
  if(!node.type)return;
  parents.set(node,parent);
  let completedDefaults;
  if(node.type==='VariableDeclaration'&&['Program','BlockStatement','ExportNamedDeclaration'].includes(parent?.type)){
   completedDefaults=[];
   for(const declaration of node.declarations)bindingDefaults(declaration.id,pattern=>localCompletions.set(pattern,completedDefaults));
  }
  if(/^(?:FunctionDeclaration|FunctionExpression|ArrowFunctionExpression)$/.test(node.type)){
   owner=node.id?.name??owner+'::<anonymous@'+node.loc.start.line+':'+node.loc.start.column+'>';
   const id=site(node,'function-entry',['entered'],owner),hit=call('hit',id+',0')+';';
   for(const param of node.params)bindingDefaults(param,pattern=>parameterEntries.set(pattern,sites[id].key));
   if(node.body.type==='BlockStatement'){
    let at=node.body.start+1;for(const statement of node.body.body){if(statement.directive)at=statement.end;else break;}
    inserts.push({at,text:';'+hit});
   }else wrap(node.body,'('+call('hit',id+',0')+',(', '))');
  }
  if(node.type==='IfStatement'||node.type==='ConditionalExpression')decision(node.test,node.type==='IfStatement'?'if':'conditional',owner);
  if(['WhileStatement','DoWhileStatement','ForStatement'].includes(node.type)&&node.test)decision(node.test,'loop',owner);
  if(node.type==='LogicalExpression')decision(node.left,'logical-'+node.operator,owner,node.operator);
  if(node.type==='MemberExpression'&&node.optional)decision(node.object,'optional-member',owner,'nonnull');
  if(node.type==='CallExpression'&&node.optional){
   const id=site(node,'optional-call',['callee-present','callee-nullish'],owner),callee=node.callee;
   if(callee.type==='MemberExpression'&&callee.object.type!=='Super'&&callee.property.type!=='PrivateIdentifier'){sites[id].supported=true;optionalWrap(callee.object,'optionalReceiver',id);}
   else if(!['MemberExpression','ChainExpression','Super'].includes(callee.type)){sites[id].supported=true;optionalWrap(callee,'optionalValue',id);}
  }
  if(node.type==='AssignmentPattern'){
   const id=site(node,'default-value',['default','provided'],owner),entry=parameterEntries.get(node);
   const completions=localCompletions.get(node);
   sites[id].supported=true;sites[id].measuredArms=[true,Boolean(entry)||Boolean(completions)];if(entry)sites[id].parameterEntryKey=entry;
   if(completions){sites[id].localCompletion=true;completions.push(id);}
   // A comma wrapper would erase inferred function/class names. An object
   // property performs the same NamedEvaluation for identifier defaults.
   const rhs=node.right,named=node.left.type==='Identifier'&&['FunctionExpression','ArrowFunctionExpression','ClassExpression'].includes(rhs.type)&&!rhs.id;
   const prefix='('+call('hit',id+',0')+',';
   if(named){const key=JSON.stringify(node.left.name);wrap(rhs,prefix+'({['+key+']:', '})['+key+'])');}
   else wrap(rhs,prefix+'(', '))');
  }
  if(['ForOfStatement','ForInStatement'].includes(node.type)){
   const id=site(node,'iterator-loop',node.type==='ForOfStatement'?['has-next','done']:['nonempty','empty'],owner);
   if(node.type==='ForOfStatement'&&!node.await){sites[id].supported=true;optionalWrap(node.right,'iterable',id);}
   if(node.type==='ForInStatement'){
    sites[id].supported=true;let token='__nhbc_forin_'+id;while(source.includes(token))token+='_';
    let statement=node;while(parents.get(statement)?.type==='LabeledStatement')statement=parents.get(statement);
    wrap(statement,'{const '+token+'={seen:false};',';globalThis.__nethackBranchCoverage.iterationEnd?.('+JSON.stringify(file)+','+id+','+token+');}');
    wrap(node.body,'{globalThis.__nethackBranchCoverage.iterationBody?.('+JSON.stringify(file)+','+id+','+token+');','}');
   }
  }
  if(node.type==='AssignmentExpression'&&['&&=','||=','??='].includes(node.operator)){
   const id=site(node,'logical-assignment',['assigned','retained'],owner);
   if(node.left.type==='Identifier'){
    sites[id].supported=true;const operator=node.operator.slice(0,-1);
    const token=tokens.find(t=>t.start>=node.left.end&&t.end<=node.right.start&&source.slice(t.start,t.end)===node.operator);
    if(!token)throw Error('Missing logical assignment operator '+file+':'+node.loc.start.line);
    replacements.push({at:token.start,end:token.end,text:operator+' ('+node.left.name+' = '});
    wrap(node,'(', '))');wrap(node.left,call('decision',id+','+JSON.stringify(operator)+',(').slice(0,-1),'))');
   }else if(node.left.type==='MemberExpression'&&node.left.object.type!=='Super'&&node.left.property.type!=='PrivateIdentifier'){
    sites[id].supported=true;
    wrap(node.left.object,'(globalThis.__nethackBranchCoverage.logicalReceiver??((_f,_i,_op,v)=>v))('+JSON.stringify(file)+','+id+','+JSON.stringify(node.operator.slice(0,-1))+',(', '))');
   }
  }
  if(node.type==='SwitchStatement'&&!node.cases.some(c=>c.test===null)){
   const id=site(node,'switch-no-match',['no-match'],owner);sites[id].supported=true;
   let token='__nhbc_switch_'+id;while(source.includes(token))token+='_';
   wrap(node,'{const '+token+'=globalThis.__nethackBranchCoverage.beginSwitch?.('+JSON.stringify(file)+','+id+','+node.cases.length+');try{','}finally{globalThis.__nethackBranchCoverage.endSwitch?.('+token+');}}');
   const value=(expr,method)=>wrap(expr,'(globalThis.__nethackBranchCoverage.'+method+'??'+fallback[method]+')('+token+',(', '))');
   value(node.discriminant,'switchValue');for(const c of node.cases)if(c.test)value(c.test,'caseValue');
  }
  if(node.type==='ThrowStatement')wrap(node.argument,'('+call('hit',site(node,'throw',['entered'],owner)+',0')+',(', '))');
  if(node.type==='SwitchCase'){
   const id=site(node,node.test?'switch-case':'switch-default',['body-entered'],owner),end=node.test?.end??node.start;
   const colon=tokens.find(token=>token.start>=end&&token.type.label===':');if(!colon)throw Error('Missing switch colon '+file+':'+node.loc.start.line);
   inserts.push({at:colon.end,text:call('hit',id+',0')+';'});
  }
  if(node.type==='CatchClause')inserts.push({at:node.body.start+1,text:call('hit',site(node,'catch',['entered'],owner)+',0')+';'});
  for(const[key,child]of Object.entries(node))if(!['loc','start','end','type'].includes(key))visit(child,owner,node);
  if(completedDefaults?.length)inserts.push({at:node.end,text:';globalThis.__nethackBranchCoverage.complete?.('+JSON.stringify(file)+','+JSON.stringify(completedDefaults)+');'});
 }
 visit(ast);
 for(const proof of closedParameterProofs(ast))for(const s of sites){
  if(s.start===proof.test.start&&s.end===proof.test.end&&s.kind==='if'){
   s.constantArm=proof.arm;s.constantProof=proof.reason;s.constantProofKind='closed-parameter';
  }
  if(proof.dead&&s.start>=proof.dead.start&&s.end<=proof.dead.end){s.unreachableProof=proof.reason;s.unreachableProofKind='closed-parameter';}
 }
 const events=new Map();const event=(at,row)=>{if(!events.has(at))events.set(at,[]);events.get(at).push(row);};
 for(const w of wraps){event(w.start,{kind:'open',text:w.open,...w});event(w.end,{kind:'close',text:w.close,...w});}
 for(const i of inserts)event(i.at,{kind:'insert',text:i.text});
 for(const r of replacements)event(r.at,{kind:'replace',...r});
 let code='',last=0;
 for(const[at,items]of [...events].sort((a,b)=>a[0]-b[0])){
  code+=source.slice(last,at);last=at;
  items.sort((a,b)=>{if(a.kind!==b.kind)return ['close','insert','open','replace'].indexOf(a.kind)-['close','insert','open','replace'].indexOf(b.kind);if(a.kind==='open')return b.end-a.end||a.order-b.order;if(a.kind==='close')return b.start-a.start||b.order-a.order;return 0;});
  for(const i of items){code+=i.text;if(i.kind==='replace')last=i.end;}
 }
 code+=source.slice(last);
 const register=call('register',JSON.stringify(sites.map(s=>s.key))+','+JSON.stringify(crypto.createHash('sha256').update(source).digest('hex'))+',{defaultTracking:true}')+';\n';
 if(code.startsWith('#!')){const at=code.indexOf('\n')+1;code=code.slice(0,at)+register+code.slice(at);}else code=register+code;
 // An unsupported semantic construct is retained in the inventory as uncovered.
 for(const s of sites)s.measured=s.supported===true||!['optional-call','default-value','iterator-loop','logical-assignment','switch-no-match'].includes(s.kind);
 return {code,sites};
}
