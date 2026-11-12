/* Actual native macOS gmtime/localtime/mktime differential oracle. */
import assert from'node:assert/strict';import fs from'node:fs';import path from'node:path';import{spawnSync}from'node:child_process';import{fileURLToPath}from'node:url';
import{epochToCalendar,makeCalendarTime}from'../js/platform/darwin/calendar.js';import{lookupTimezone}from'../js/platform/timezone/info.js';
const root=fileURLToPath(new URL('../',import.meta.url)),work=path.join(root,'.cache/js-lua-calendar');fs.mkdirSync(work,{recursive:true});
function command(program,args,options={}){const r=spawnSync(program,args,{encoding:'utf8',timeout:120000,maxBuffer:20000000,...options});assert.equal(r.status,0,r.error||r.stderr||r.stdout);return r.stdout;}
const src=path.join(work,'oracle.c'),oracle=path.join(work,'oracle');fs.writeFileSync(src,`#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
static void emit(struct tm*x){if(!x){puts("NULL");return;}printf("%d %d %d %d %d %d %d %d %d\\n",x->tm_year,x->tm_mon,x->tm_mday,x->tm_hour,x->tm_min,x->tm_sec,x->tm_wday,x->tm_yday,x->tm_isdst);}
int main(void){char op,encoded[4096],zone[2048];long long raw,offset;while(scanf(" %c",&op)==1){struct tm fields={.tm_wday=6,.tm_yday=123},*result;
if(op=='G'){scanf("%lld%lld",&raw,&offset);time_t t=raw+offset;emit(gmtime_r(&t,&fields));continue;}
scanf("%4095s",encoded);int n=strlen(encoded)/2;for(int i=0;i<n;i++){unsigned b;sscanf(encoded+2*i,"%2x",&b);zone[i]=b;}zone[n]=0;setenv("TZ",zone,1);tzset();
if(op=='L'){scanf("%lld",&raw);time_t t=raw;emit(localtime_r(&t,&fields));continue;}
scanf("%d%d%d%d%d%d%d",&fields.tm_year,&fields.tm_mon,&fields.tm_mday,&fields.tm_hour,&fields.tm_min,&fields.tm_sec,&fields.tm_isdst);time_t t=mktime(&fields);printf("%lld ",(long long)t);emit(&fields);}return 0;}`);
command(process.env.CC||path.join(root,'.cache/wasm64-build/host-cc'),['-O2',src,'-o',oracle]);
const cases=[],keys=['year','month','day','hour','min','sec','wday','yday','isdst'];
const encodeZone=zone=>Buffer.from(zone).toString('hex')||'0';
function epoch(time,offset=0){cases.push({op:'G',time:BigInt(time),offset,line:'G '+time+' '+offset});}
function local(zone,time){cases.push({op:'L',zone,time:BigInt(time),line:'L '+encodeZone(zone)+' '+time});}
function make(zone,fields){fields={hour:0,min:0,sec:0,isdst:-1,...fields,wday:6,yday:123};cases.push({op:'M',zone,fields,line:'M '+encodeZone(zone)+' '+['year','month','day','hour','min','sec','isdst'].map(k=>fields[k]).join(' ')});}
const zones=['UTC','America/New_York','America/Los_Angeles','Europe/Berlin','Asia/Tokyo','Asia/Kathmandu','Australia/Sydney','Europe/Dublin','Pacific/Apia','America/Nuuk','EST5EDT,M3.2.0,M11.1.0','UTC-5:30'];
for(const time of [0n,-1n,1n,-2208988800n,-62167219200n,951782400n,2147483647n,2147483648n,67768036160140800n,67768036191676799n,-67768040609740800n,-(1n<<63n),(1n<<63n)-1n]){epoch(time);for(const zone of zones)local(zone,time);}
for(const time of [-2208988800n,0n,951782400n,67768036160140800n])for(const offset of [-43200,-19800,1,19800,50400])epoch(time,offset);
for(const zone of zones)for(const year of [-2147483648,-1000,-1,0,1,69,70,100,126,138,200,600,1100,3100,1000000,2147483646,2147483647])for(const isdst of [-1,0,1,2])make(zone,{year,month:0,day:1,isdst});
for(const zone of zones)for(const isdst of [-2147483648,2147483647])make(zone,{year:126,month:6,day:1,isdst});
// Gap and overlap minutes, including missing calendar day in Apia.
for(const [zone,year,month,day,hour]of[['America/New_York',124,2,10,2],['America/New_York',124,10,3,1],['America/Los_Angeles',124,2,10,2],['Europe/Berlin',124,2,31,2],['Europe/Berlin',124,9,27,2],['Australia/Sydney',124,9,6,2],['Australia/Sydney',124,3,7,2],['Pacific/Apia',111,11,30,12]])for(const min of [0,15,30,59])for(const isdst of [-2,-1,0,1,2])make(zone,{year,month,day,hour,min,isdst});
for(const zone of zones)for(const field of ['month','day','hour','min','sec'])for(const value of [-2147483648,-2147483647,-100000,-61,-1,0,60,100000,2147483646,2147483647])make(zone,{year:126,month:0,day:1,[field]:value});
for(const zone of ['UTC','America/New_York','Europe/Dublin'])for(const year of [0,69,126,2147483647])for(const hour of [-2147483648,2147483647])for(const min of [-2147483648,2147483647])for(const sec of [-2147483648,2147483647])make(zone,{year,month:0,day:1,hour,min,sec});
let seed=0x291af7c3;const rnd=()=>{seed^=seed<<13;seed^=seed>>>17;seed^=seed<<5;return seed>>>0;};
for(let i=0;i<5000;i++){const zone=zones[rnd()%zones.length];make(zone,{year:60+rnd()%180,month:(rnd()%60)-24,day:(rnd()%200)-60,hour:(rnd()%200)-80,min:(rnd()%20000)-10000,sec:(rnd()%200000)-100000,isdst:[-2,-1,0,1,2][rnd()%5]});epoch(BigInt(rnd())*40000000n-70000000000000000n);}
// Every sampled local calendar is converted back under all three DST policies.
for(const zone of ['America/New_York','Europe/Berlin','Australia/Sydney','Asia/Kathmandu','Pacific/Apia'])for(const year of [1910,1942,2024,2038,2100,2500])for(const month of [0,2,3,9,10,11]){const time=BigInt(Date.UTC(year,month,1,1,30)/1000),info=lookupTimezone(zone,time),fields=epochToCalendar(time,info.offset);for(const isdst of [-1,0,1])make(zone,{...fields,isdst});}
const lines=command(oracle,[],{input:cases.map(c=>c.line).join('\n')+'\n'}).trimEnd().split('\n');assert.equal(lines.length,cases.length);const differences=[];let count=0;
for(let i=0;i<cases.length;i++){const c=cases[i],line=lines[i],raw=line==='NULL'?null:line.split(' '),wanted=raw?raw.slice(c.op==='M'?1:0).map(Number):null;let result;
if(c.op==='G')result=epochToCalendar(c.time,c.offset);else if(c.op==='L'){const info=lookupTimezone(c.zone,c.time);result=epochToCalendar(c.time,info.offset);if(result)result.isdst=info.isdst;}else result=makeCalendarTime(c.zone,c.fields);
const got=c.op==='M'?[String(result.time),...keys.map(k=>result.fields[k])]:result?keys.map(k=>result[k]):null,want=c.op==='M'?[raw[0],...wanted]:wanted;
if(JSON.stringify(got)!==JSON.stringify(want)){differences.push({case:c.line,native:want,result:got});if(differences.length<5)console.error(JSON.stringify(differences.at(-1)));}count++;}
fs.writeFileSync(path.join(work,'differences.json'),JSON.stringify(differences,null,2)+'\n');assert.deepEqual(differences.slice(0,12),[]);fs.writeFileSync(path.join(work,'validated.json'),JSON.stringify({cases:count,byKind:cases.reduce((o,c)=>(o[c.op]=(o[c.op]??0)+1,o),{}),zones},null,2)+'\n');
console.log(`PASS: ${count} actual macOS Gregorian gmtime/localtime/mktime comparisons; int32 years and int64 epochs, normalization/overflow, pre1900 failure fields, gaps/overlaps, explicit DST, historical offsets and random calendar values.`);
