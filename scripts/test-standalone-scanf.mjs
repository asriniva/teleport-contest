import assert from'node:assert/strict';import fs from'node:fs';import path from'node:path';import crypto from'node:crypto';import{pathToFileURL}from'node:url';
import{createStandaloneEnvironment}from'../js/standalone/environment.js';
const directory=path.resolve(process.env.STANDALONE_SCANF_ORACLE??'.cache/standalone-scanf-v3'),receipt=JSON.parse(fs.readFileSync(directory+'/receipt.json')),sha=p=>crypto.createHash('sha256').update(fs.readFileSync(p)).digest('hex');let hashes=0,checks=0;
for(const[p,h]of Object.entries(receipt.sourceSha256)){assert.equal(sha(p),h,p);hashes++;}for(const[p,h]of Object.entries(receipt.artifactSha256)){assert.equal(sha(directory+'/'+p),h,p);hashes++;}
const{default:factory}=await import(pathToFileURL(directory+'/reference.mjs')),reference=await factory(),equal=(a,b,label)=>{assert.deepEqual(a,b,label);checks++;};
const binding=JSON.parse(fs.readFileSync('js/standalone/scanf-abi.json'));for(const[p,h]of Object.entries(binding.sourceSha256)){assert.equal(sha(p),h,p);hashes++;}assert.equal(binding.referenceReceiptSha256,sha(directory+'/receipt.json'));
equal(Array.from({length:6},(_,i)=>Number(reference._scanf_constant(i))),[28,68,8,8,-1,128],'actual configured SDK scanner constants/widths');
const cases=[['','%d'],[' ','%d'],['a','%d'],['+','%d'],['-X','%d'],['0x','%i'],['0xZ','%i'],['0xZ','%x'],['09X','%i'],['-0x20Z','%i'],['-17Z','%u'],['18446744073709551615!','%llu'],['18446744073709551616!','%llu'],['-18446744073709551616!','%lld'],['42','%d'],['42!','%d'],['42 9','%d%d'],['42x9','%d%d'],['  42 \nQ','%n%d%n'],['','%n%d'],['a','a%d'],['a','a'],['  %X','%%%c'],['%','%%'],['Q',' %c'],['ab','%3c'],['abc','%3c'],['abC!','%2c%c'],['a b','%s%s'],['abc!','%3s'],[' abc \n','%*s%d'],['123','%*d%d'],['123','%*d%n'],['abc,rest\nZ','%[^,],%[^\n]%*c'],[']-za!','%[]a-z-]'],['za-!','%[z-a]'],['123X','%[a-z]'],['abX','%2[a-z]'],['abc','%[^x]'],['12 34XYZ','%d %2d%hn'],['\xa0Z Q','%s'],['x\0yZ','%3c'],['123Q','%c%d',{preUnget:33}],['42Z','%d',{postUnget:88}],['','%d',{postUnget:88}],['123','%d',{mode:1}],['123','%d',{broken:true}]];
for(const width of[1,2,3,4])for(const fmt of['d','i','x'])cases.push(['+0x9Z','%'+width+fmt]);
cases.push(['',''],['','%n'],['abc','%n'],['abc','%*n'],['','',{mode:1}],['','%n',{mode:1}],['','%n',{broken:true}]);
cases.push(['X123Q','%d',{preRead:true,broken:true}],['X123','%d',{preRead:true,broken:true}]);
for(const length of['hh','h','','l','ll','j','z','t'])cases.push(['-123Z','%'+length+'d'],['123Z','%'+length+'n%d']);
cases.push(['5.0.0 123456789123456789 0 3 4 -2 18 1 20260102 20251231 42 Arc Hum Mal Law Ada,killed by a jackal\n','%d.%d.%d %ld %d %d %d %d %d %d %ld %ld %d ']);
async function run([input,format,options={}],stdin=false){
 const bytes=Uint8Array.from(input,c=>c.charCodeAt(0)),queue=[...bytes],ref=stdin?await factory({stdin:()=>queue.length?queue.shift():null}):reference;
 const env=createStandaloneEnvironment(),io=env.enableStdio({stdin:bytes}),{memory}=env;env.filesystem.writeFile('/scanf-input',bytes);if(!stdin)ref.FS.writeFile('/scanf-input',bytes);
 const jf=stdin?io.stdin:io.fopen('/scanf-input',options.mode===1?'w':'r'),cf=BigInt(ref._scanf_open(stdin?2:options.mode??0));assert.ok(jf&&cf);
 if(options.preRead)equal(io.fgetc(jf),ref._scanf_getc(cf),'real pre-read buffer activation');
 if(options.broken){io.close(io.fileno(jf));ref._scanf_break_fd(cf);}
 if(options.preUnget!==undefined)equal(io.ungetc(options.preUnget,jf),ref._scanf_unget(cf,options.preUnget),'pre-pushback');
 const outputs=memory.malloc(16*128),p=BigInt(ref._malloc(BigInt(format.length+1)));memory.memset(outputs,0xa5,16*128);ref.HEAPU8.set(Buffer.from(format+'\0'),Number(p));
 env.libc.errno=137;const result=io.fscanf(jf,format,...Array.from({length:16},(_,i)=>outputs+i*128)),native=ref._scanf_run(cf,p,137),label=JSON.stringify({input,format,options,stdin});
 equal(result,native,label+' return');equal(env.libc.errno,ref._scanf_errno(),label+' errno');equal(memory.readBytes(outputs,16*128),ref.HEAPU8.slice(Number(ref._scanf_outputs()),Number(ref._scanf_outputs())+16*128),label+' every output byte/sentinel');equal(io.feof(jf)|(io.ferror(jf)<<1),ref._scanf_flags(cf),label+' EOF/error');
 if(!stdin&&!options.broken&&options.mode!==1)equal(io.ftell(jf),ref._scanf_position(cf),label+' logical unread position');
 if(options.postUnget!==undefined)equal(io.ungetc(options.postUnget,jf),ref._scanf_unget(cf,options.postUnget),label+' post-pushback');
 equal(io.fgetc(jf),ref._scanf_getc(cf),label+' next byte');equal(io.feof(jf)|(io.ferror(jf)<<1),ref._scanf_flags(cf),label+' next-byte EOF/error');
 const line=memory.malloc(128);memory.memset(line,0xa5,128);equal(Boolean(io.fgets(line,32,jf)),Boolean(ref._scanf_getline(cf,32)),label+' following fgets');equal(memory.readBytes(line,128),ref.HEAPU8.slice(Number(ref._scanf_line()),Number(ref._scanf_line())+128),label+' fgets bytes/sentinels');equal(io.feof(jf)|(io.ferror(jf)<<1),ref._scanf_flags(cf),label+' final flags');
 io.fclose(jf);ref._scanf_close(cf);
 // The exact same engine must preserve sscanf assignment/partial-output rules.
 if(!stdin&&!options.broken&&!options.mode&&!options.preUnget){const j=createStandaloneEnvironment(),out=j.memory.malloc(16*128),q=BigInt(ref._malloc(BigInt(bytes.length+1)));ref.HEAPU8.set(bytes,Number(q));ref.HEAPU8[Number(q)+bytes.length]=0;j.memory.memset(out,0xa5,16*128);j.libc.errno=137;equal(j.services.sscanf(input,format,...Array.from({length:16},(_,i)=>out+i*128)),ref._scanf_string(q,p,137),label+' actual SDK sscanf result');equal(j.libc.errno,ref._scanf_errno(),label+' actual sscanf errno');equal(j.memory.readBytes(out,16*128),ref.HEAPU8.slice(Number(ref._scanf_outputs()),Number(ref._scanf_outputs())+16*128),label+' actual sscanf every output byte');ref._free(q);}
 ref._free(p);
}
for(const c of cases)await run(c);for(const i of[0,3,5,8,16,24,25,29,30,31,32,42])await run(cases[i],true);
console.log(`PASS scanf: ${checks} comparisons / ${cases.length+12} real SDK stream cases; ${hashes} pinned native inputs/artifacts.`);
fs.writeFileSync(directory+'/test-evidence.json',JSON.stringify({checks,cases:cases.length+12,hashes,referenceSha256:sha(directory+'/receipt.json'),sourceSha256:Object.fromEntries(['scripts/test-standalone-scanf.mjs','js/c-runtime/scanf.js','js/standalone/libc.js','js/c-runtime/stdio.js'].map(p=>[p,sha(p)])),scope:'Pinned SDK narrow integer/byte/string/scanset scanf, actual TOPTEN 13-field prefix, partial/mismatch/EOF/error, suppression/%n/width, unread getc/fgets and nonseekable stdin. Floating/wide/allocation/positional conversions remain explicit unsupported.'},null,2)+'\n');
