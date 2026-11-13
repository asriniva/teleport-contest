import assert from 'node:assert/strict';import vm from 'node:vm';
import {createCollector} from './branch-coverage/collector.mjs';
import {instrument} from './branch-coverage/instrument.mjs';
const cases=[
 ['if-and-or',`function run(v){if(v&&v.x)return v.x||7;return 9;}`,[[null],[{x:0}],[{x:3}]]],
 ['nullish-and-optional',`function run(v){return v?.x??13;}`,[[null],[{}],[{x:0}],[{x:8}]]],
 ['ternary-loop',`function run(n){let x=0;for(let i=0;i<n;i++)x+=i%2?3:5;while(n-->0)x++;do{x--;}while(x>10);return x;}`,[[0],[2],[8]]],
 ['switch-fallthrough',`function run(n){let x=0;switch(n){case 0:case 1:x++;case 2:x+=2;break;default:x=8;}return x;}`,[[0],[1],[2],[9]]],
 ['throw-and-catch',`function run(n){try{if(n)throw new Error('expected');return 1;}catch(e){return e.message;}finally{n++;}}`,[[0],[1]]],
 ['arrow-and-default',`const f=(a=3)=>({value:a?4:5});function run(a){return f(a).value;}`,[[undefined],[0],[1]]],
 ['getter-and-this',`function run(v){let n=0;const o={get x(){n++;return v;},f(){return this.x;}};return [o?.f(),n];}`,[[0],[8]]],
 ['labels-and-generator',`function* g(n){outer:for(let i=0;i<n;i++){if(i%2)continue outer;yield i;}}function run(n){return [...g(n)];}`,[[0],[5]]],
 ['optional-method-receiver',`function run(mode){const o=Object.freeze({x:3,f:mode?function(a){return [this.x,a===this.f];}:null});return o.f?.(o.f);}`,[[0],[1]]],
 ['optional-primitive',`function run(v){return v.toUpperCase?.();}`,[['abc'],['xyz']]],
 ['iterator-protocol',`function run(stop){const trace=[];let n=0;const result={get done(){trace.push('done');return n>2;},get value(){trace.push('value');return n;}};const iterator={get next(){trace.push('next');return function(){trace.push(this===iterator);n++;return result;};},get return(){trace.push('get-return');return function(){trace.push(this===iterator);return {};};}};const iterable={get [Symbol.iterator](){trace.push('iterator');return function(){trace.push(this===iterable);return iterator;};}};let sum=0;for(const x of iterable){sum+=x;if(stop)break;}return [sum,trace];}`,[[0],[1]]],
 ['switch-no-default',`function run(v){let x=0;switch(v){case 1:x=3;case 2:x++;break;}return x;}`,[[1],[2],[9]]],
 ['switch-expression-error',`function run(v){try{switch(v){case (()=>{throw Error('case');})():return 3;}}catch(e){return e.message;}}`,[[1]]],
 ['logical-side-effects',`function run(v){let n=0;const get=()=>{n++;return v;};return [get()&&get(),get()||get(),get()??get(),n];}`,[[null],[0],[2]]],
 ['default-names',`function run(a=()=>0,b=function(){},c=class{static seen=this.name}){return [a.name,b.name,c.name,c.seen];}`,[[]]],
 ['destructuring-defaults',`function run(v){const {a=()=>0,b=class{static seen=this.name}}=v;let [c=function(){}]=[];return [a.name,b.name,b.seen,c.name];}`,[[{}]]],
 ['parameter-default-throws',`function fail(){throw Error('parameter');}function f(a=2,b=fail()){return a+b;}function run(v){try{return f(v);}catch(e){return e.message;}}`,[[undefined],[7]]],
 ['generator-defaults',`function* f(a=3){yield a;}function run(v){const unused=f();return [...f(v)];}`,[[undefined],[7]]],
 ['logical-assignments',`function run(v){let x=v,y=v,z=v,n=0;x&&=(n++,2);y||=(n++,3);z??=(n++,4);return [x,y,z,n];}`,[[undefined],[null],[0],[1]]],
 ['logical-assignment-names',`function run(){let a,b,c=1;a||=function(){};b??=()=>0;c&&=class{static seen=this.name};return [a.name,b.name,c.name,c.seen];}`,[[]]],
 ['logical-assignment-yield',`function* f(v){v||=yield 3;return v;}function run(v){const g=f(v);return [g.next(),g.next(7)];}`,[[0],[1]]],
 ['directive-automatic-semicolon',`function run(){'use strict'\nreturn this===undefined;}`,[[]]],
 ['nested-default-names',`function run({a=()=>0}={},[b=class{static seen=this.name}]=[]){return [a.name,b.name,b.seen];}`,[[]]],
 ['iterator-next-error',`function run(){try{for(const x of {[Symbol.iterator](){return {get next(){throw Error('next');}};}}){return x;}}catch(e){return e.message;}}`,[[]]],
 ['optional-private-receiver',`class A{#value=9;f(){return this.#value;}run(){return this.f?.();}}function run(){return new A().run();}`,[[]]],
 ['member-logical-assignment',`function run(v){let n=0;const o={a:v,b:v,c:v};o.a&&=(n++,2);o.b||=(n++,3);o.c??=(n++,4);return [o.a,o.b,o.c,n];}`,[[null],[0],[1]]],
 ['computed-logical-receiver',`function run(v){const trace=[];let value=v;const o={get x(){trace.push(this===o);return value;},set x(v){trace.push(this===o);value=v;}};const key={[Symbol.toPrimitive](){trace.push('key');return 'x';}};const result=o[key]??=(trace.push('rhs'),7);return [result,value,trace];}`,[[null],[3]]],
 ['readonly-logical-retained',`function run(v){'use strict';const o=Object.freeze({x:v});try{return o.x??=7;}catch(e){return e.name;}}`,[[null],[3]]],
 ['logical-private-setter',`class A{#x;get x(){return this.#x;}set x(v){this.#x=v;}}function run(v){const o=new A();o.x=v;o.x??=3;return o.x;}`,[[null],[7]]],
 ['for-in-empty-inherited',`function run(v){const o=Object.assign(Object.create({p:3}),v?{x:2}:{});let x='';for(const k in v===null?null:v===0?{}:o)x+=k;return x;}`,[[null],[0],[1]]],
 ['for-in-labels',`function run(v){let n=0;outer:inner:for(const k in {x:1,y:2}){n++;if(v)continue outer;break inner;}return n;}`,[[0],[1]]],
 ['for-in-enumeration-error',`function run(){try{for(const k in new Proxy({},{ownKeys(){throw Error('enumeration');}}))return k;}catch(e){return e.message;}}`,[[]]],
 ['iterator-close-error',`function run(){try{for(const x of {[Symbol.iterator](){return {next(){return {done:false,value:1};},get return(){throw Error('close-get');}};}}){throw Error('body');}}catch(e){return e.message;}}`,[[]]],
 ['logical-proxy-receiver',`function run(v){const trace=[];const target={x:v};const o=new Proxy(target,{get(t,k,r){trace.push(['get',r===o]);return Reflect.get(t,k,r);},set(t,k,v,r){trace.push(['set',r===o]);return Reflect.set(t,k,v,r);},defineProperty(t,k,d){trace.push(['define',k]);return Reflect.defineProperty(t,k,d);}});o.x??=7;return [target.x,trace];}`,[[null],[3]]],
];
let runs=0;
for(const[name,source,inputs]of cases){const runtime=createCollector();const code=instrument(source,name+'.js').code;
 const original=vm.runInNewContext(source+';run'),actual=vm.runInNewContext(code+';run',{__nethackBranchCoverage:runtime});
 for(const args of inputs){assert.deepEqual(structuredClone(actual(...args)),structuredClone(original(...args)),name);runs++;}assert.ok(runtime.files.size,name);
}
console.log('PASS: '+runs+' instrumentation equivalence cases preserve results, evaluation counts, getters, receivers, loops, exceptions and generators.');
