import assert from 'node:assert/strict';
import {writeFileSync} from 'node:fs';
import {pathToFileURL} from 'node:url';
import path from 'node:path';
const arg=process.argv.indexOf('--out');if(arg<0)throw Error('--out required');const out=path.resolve(process.argv[arg+1]);
const reference=(await import(pathToFileURL(out+'/reference-full.mjs'))).default;
const hybrid=(await import(pathToFileURL(out+'/hybrid-full.mjs'))).default;
import {createSfctoolHelpers} from '../js/ported-utilities/sfctool-helpers.js';
let checks=0,cases=0;
async function one(factory,op,text,number=0,setup=()=>{}){
    const m=await factory({print(){},printErr(){}}),h=createSfctoolHelpers(m);
    m.utilityInvoke=(name,args)=>h.invoke(name,args);m.utilityVararg=(...args)=>h.vararg(...args);
    m.FS.mkdirTree('/usr/games/lib/nethackdir');m.FS.mkdirTree('/sandbox/sub');
    m._utility_streams();setup(m);
    const n=m.lengthBytesUTF8(text??'')+1,p=Number(m._malloc(BigInt(n)));m.stringToUTF8(text??'',p,n);
    let status=null;
    try{m._utility_extra_call(op,text===null?0n:BigInt(p),number);}catch(e){if(e?.name==='ExitStatus')status=e.status;else throw e;}
    m._utility_flush();
    let signal=null;
    if(op===7){const previous=m._utility_signal(h.env.SIGINT,h.env.SIG_IGN);signal=previous===h.env.done1Pointer?'done1':previous===h.env.SIG_IGN?'SIG_IGN':'other';}
    return{status,text:m.UTF8ToString(p),stdout:m.FS.readFile('/stdout',{encoding:'utf8'}),stderr:m.FS.readFile('/stderr',{encoding:'utf8'}),cwd:m.FS.cwd(),signal};
}
async function pair(op,text,number=0,setup){const a=await one(reference,op,text,number,setup),b=await one(hybrid,op,text,number,setup);assert.deepEqual(b,a);checks++;cases++;return a;}
for(const s of['','normal','a.b/c d','abcdefghijklmnopq','. /..','1234567890.123','two\\path:okay']){const a=await pair(0,s);assert.ok(!/[. /]/.test(a.text));assert.equal(a.text.length,s.length);checks+=2;}
for(const op of[1,2,3,4])for(const s of['','name','%s is literal here','a\nb']){const a=await pair(op,s,-17);assert.equal(a.stdout,`str=${s} int=-17 long=-9007199254740993 double=1.25 %\n`);assert.equal(a.status,op===3||op===4?1:null);checks+=2;}
for(const status of[0,1,17]){const a=await pair(5,'',status);assert.equal(a.status,status);checks++;}
for(const dir of[null,'/sandbox','/sandbox/sub']){const a=await pair(6,dir);assert.equal(a.status,null);checks++;}
const failed=await pair(6,'/missing-dir');assert.equal(failed.status,1);assert.ok(failed.stdout.includes('Cannot chdir to /missing-dir.'));assert.ok(failed.stderr.startsWith('/missing-dir:'));checks+=3;
for(const flag of[0,1]){const a=await pair(7,'',2,m=>m._utility_set_ignintr(flag));assert.equal(a.signal,flag?'done1':'SIG_IGN');checks++;}
for(const name of['sfctool','/some/bin/sfctool','x\\some\\tool.exe','a/b:c/d']){const a=await pair(8,name);assert.ok(a.stderr.includes('To convert a savefile'));assert.ok(a.stderr.includes('To unconvert an exported savefile'));checks+=2;}
writeFileSync(path.join(out,'full-extra-test-results.json'),JSON.stringify({status:'PASS',checks,cases,additionalFunctions:9,verifiedFunctions:44,fullCliComplete:false},null,2)+'\n');console.log(JSON.stringify({checks,cases,verifiedFunctions:44,status:'PASS'}));

process.exitCode=0;
