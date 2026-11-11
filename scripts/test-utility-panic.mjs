import{resolve,isAbsolute}from'node:path';import{pathToFileURL}from'node:url';
const output=process.env.UTILITY_PANIC_OUT;if(!output)throw Error('Explicit fresh UTILITY_PANIC_OUT build directory required');if(!isAbsolute(output))throw Error('Build directory must be absolute');
import assert from 'node:assert/strict';
import { writeFileSync } from 'node:fs';
const reference=(await import(pathToFileURL(output+'/reference.mjs'))).default;
const hybrid=(await import(pathToFileURL(output+'/hybrid.mjs'))).default;
import { install } from '../js/ported-utilities/panic/runtime.mjs';
import { C } from '../js/ported-utilities/panic/scope.mjs';
let comparisons = 0, cases = 0;
const eq = (a,b,label) => { assert.deepEqual(a,b,label); comparisons++; };
const string = (m,text) => { const length=m.lengthBytesUTF8(text)+1, pointer=m._malloc(BigInt(length)); m.stringToUTF8(text,Number(pointer),length); return BigInt(pointer); };
async function run(factory,{mode=0,text='message',wide=9007199254740993n,value=1.25,initial=0,reentry=false,growth=false}={}) {
    const sourceBytes=[],runtimeMessages=[],abortNotifications=[];
    let m, entered=false, nestedPointer, grew=false;
    const instance=await factory({stdout:byte=>sourceBytes.push(byte),stderr:byte=>{
        sourceBytes.push(byte);
        if(m&&growth&&!grew&&sourceBytes.length===new TextEncoder().encode(' ERROR:  '+text).length){grew=true;const before=m.HEAPU8.buffer;m._malloc(50000000n);assert.notEqual(m.HEAPU8.buffer,before);}
        if(m&&reentry&&!entered){entered=true;m._utility_panic_fixture(0,nestedPointer,0n,0);}
    },printErr:text=>runtimeMessages.push(text),onAbort:reason=>abortNotifications.push(reason)});
    m=instance;
    const state=factory===hybrid?install(m):null;
    const address=Number(m._utility_panic_state_address());
    if(state)state.panicking=initial;else new DataView(m.HEAPU8.buffer).setInt8(address,initial);
    const p=string(m,text);nestedPointer=string(m,'nested should not be printed');
    let caught=null;
    try { m._utility_panic_fixture(mode,p,wide,value); } catch(error) { caught={name:error.name,message:error.message,stack:error.stack}; }
    assert(caught,'actual native abort must not return');comparisons++;
    eq(caught.name,'RuntimeError','actual SDK abort outcome');
    eq(abortNotifications,reentry?['','']:[''],'actual SDK native abort notifications (device catches nested error)');
    const count=state?state.panicking:new DataView(m.HEAPU8.buffer).getInt8(address);
    if(state)eq(C,undefined,'scope restored after native abort');
    return { sourceBytes,sourceText:new TextDecoder().decode(Uint8Array.from(sourceBytes)),count,entered,grew,caught,runtimeMessages,abortNotifications };
}
const configs=[{}, {mode:1,text:'formatted\ntext',wide:9223372036854775807n,value:3.125}, {mode:1,text:'negative',wide:-9007199254740993n,value:-0.5}, {mode:2}, {mode:3,text:'abcdef',wide:-9223372036854775808n}, {text:''}, {text:'first\nsecond\n'}, {initial:1}, {initial:-128}, {initial:127}, {reentry:true,text:'outer complete bytes'}, {growth:true,text:'growing native stream'}];
const records=[];
for(const config of configs){const a=await run(reference,config),b=await run(hybrid,config);eq(b.sourceBytes,a.sourceBytes,'actual libc source stderr bytes');eq(b.count,a.count,'source signedboolean recursion state');eq(b.entered,a.entered,'native callback reentry');eq(b.grew,a.grew,'actual memory growth');eq(b.abortNotifications,a.abortNotifications,'native abort notifications');eq(b.runtimeMessages,a.runtimeMessages,'runtime-generated stderr messages preserved, not normalized');eq(b.caught.message,a.caught.message,'actual native abort messages unchanged');if(config.initial){eq(a.sourceBytes,[],'recursive/nonzero source guard emits no prefix');}else if(!config.reentry){assert(a.sourceText.startsWith(' ERROR:  '));comparisons++;}if(config.reentry)eq(a.count,2,'nested guard postincrements before abort');if(config.mode===1)eq(a.sourceText,' ERROR:  number=-17 long='+config.wide.toString()+' double='+config.value.toFixed(3)+' char=A string='+config.text+'\n','actual promoted varargs exact output');if(config.mode===3)eq(a.sourceText,' ERROR:           abc:-9223372036854775808','actual native width/precision and long64');if(config.initial===127)eq(a.count,-128,'configured signed boolean narrowing');records.push({config:{...config,wide:config.wide?.toString()},reference:a,hybrid:b});cases++;}
// Two actual Modules have independent original private recursion state.
const first=await run(hybrid,{text:'moduleA'}),second=await run(hybrid,{text:'moduleB'});eq(first.count,1,'moduleA first call');eq(second.count,1,'moduleB first call');eq(first.sourceText,' ERROR:  moduleA','source exact message A');eq(second.sourceText,' ERROR:  moduleB','source exact message B');
const result={status:'PASS',comparisons,cases,ownedFunctions:1,actualNativeAbort:true,actualVaList:true,nativeMac:false,stackTraceQualification:'Full actual reference/hybrid generated stacks retained separately; differing frames/addresses are not source-output parity or host core-dump claims.'};
writeFileSync(resolve(output,'test-result.json'),JSON.stringify(result,null,2)+'\n');writeFileSync(resolve(output,'actual-abort-records.json'),JSON.stringify(records,null,2)+'\n');console.log(JSON.stringify(result));
