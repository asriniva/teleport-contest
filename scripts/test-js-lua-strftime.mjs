/* Independent actual macOS C-locale strftime oracle; no C formatter in JS. */
import assert from'node:assert/strict';import fs from'node:fs';import path from'node:path';import{spawnSync}from'node:child_process';import{fileURLToPath}from'node:url';
import{formatDarwinTime}from'../js/platform/darwin/strftime.js';import{epochToCalendar}from'../js/platform/darwin/calendar.js';import{lookupTimezone}from'../js/platform/timezone/info.js';import{NATIVE_TIMEZONE_NAMES}from'../js/platform/timezone/tzdb.js';
const root=fileURLToPath(new URL('../',import.meta.url)),work=path.join(root,'.cache/js-lua-strftime');fs.mkdirSync(work,{recursive:true});
function command(program,args,options={}){const r=spawnSync(program,args,{encoding:'utf8',timeout:120000,maxBuffer:40000000,...options});assert.equal(r.status,0,r.error||r.stderr||r.stdout);return r.stdout;}
const source=path.join(work,'oracle.c'),oracle=path.join(work,'oracle');
fs.writeFileSync(source,`#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
static void decode(char*out,char*in){int n=strlen(in)/2;for(int i=0;i<n;i++){unsigned x;sscanf(in+2*i,"%2x",&x);out[i]=x;}out[n]=0;}
int main(void){setlocale(LC_ALL,"C");char fhex[8192],zhex[4096],ahex[4096],format[4096],zone[2048],abbr[2048],output[8192];int cap;struct tm t;
while(scanf("%8191s%4095s%4095s%d%d%d%d%d%d%d%d%d%d",fhex,zhex,ahex,&cap,&t.tm_year,&t.tm_mon,&t.tm_mday,&t.tm_hour,&t.tm_min,&t.tm_sec,&t.tm_wday,&t.tm_yday,&t.tm_isdst)==13){
decode(format,fhex);decode(zone,zhex);decode(abbr,ahex);setenv("TZ","GMT0",1);tzset();setenv("TZ",zone,1);tzset();t.tm_zone=!strcmp(ahex,"N")?NULL:abbr;t.tm_gmtoff=12345;memset(output,0xa5,sizeof output);size_t n=strftime(output,cap,format,&t);printf("%zu:",n);for(size_t i=0;i<n;i++)printf("%02x",(unsigned char)output[i]);puts("");}return 0;}`);
command(process.env.CC||path.join(root,'.cache/wasm64-build/host-cc'),['-O2',source,'-o',oracle]);
const cases=[],keys=['year','month','day','hour','min','sec','wday','yday','isdst'],base={year:126,month:10,day:9,hour:13,min:7,sec:8,wday:1,yday:312,isdst:0};
const add=(format,fields=base,options={})=>cases.push({format,fields:{...fields},options:{zone:'America/New_York',abbreviation:'MANUAL',capacity:250,...options}});
const codes='aAbBcCdDeFgGhHIjmMnprRStTuUVwWxXyYzZ%klv+';
const years=[-2147483648,-2147483647,-10000,-2001,-2000,-1999,-1901,-1900,-1899,-1,0,69,70,99,100,124,126,8100,2147483646,2147483647];
for(const year of years)for(const code of codes)for(const flag of ['','-','_','0','E','O','E-','-O'])add('%'+flag+code,{...base,year});
for(const code of codes)for(const flag of ['EE','EO','OE','OO','--','00','_0','-_','_E','O_','E0','0E','OE-'])add('%'+flag+code);
for(const format of ['','%','tail%','%E','%O','%_','%-','%0','%EE','%EO','%%','%?','%q','%Q','%P','%N','%9Y','%#c','%:z','a\0b%Y','%Y\0%m','%s','%s %Z','%Z %s %Z'])add(format,base,{abbreviation:undefined});
for(const format of ['%Y','%c','%F','%z','%Z','a%Yb','literal','%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c'])for(const capacity of [0,1,2,3,4,5,6,10,20,249,250,251,500])add(format,base,{capacity});
for(const zone of ['UTC','','America/New_York','America/Los_Angeles','Europe/Berlin','Asia/Tokyo','Asia/Kathmandu','Europe/Dublin','Australia/Sydney','America/Nuuk','UTC-5:30','AAA0'])for(const isdst of [-2147483648,-1,0,1,2,2147483647])for(const abbreviation of [undefined,null,'','UTC','MANUAL','with\0suffix','x'.repeat(249),'x'.repeat(250)])for(const format of ['%Z','%z','%Z %z','%c %Z %z'])add(format,{...base,isdst},{zone,abbreviation});
for(const year of [-10000,-1,0,1,4,99,100,399,400,1582,1900,1969,1970,1999,2000,2004,2015,2016,2019,2020,2021,2026,2038,2100,2400,9999,10000])for(const month of [0,11])for(let day=1;day<=7;day++){
const date=new Date(0);date.setUTCFullYear(year,month,day);const fields=epochToCalendar(BigInt(date.getTime()/1000));add('%Y %C %y %G %g %V %U %W %u %w %j %F %c %x',fields);}
for(const field of ['month','day','hour','min','sec','wday','yday'])for(const value of [-2147483648,-1,0,7,12,23,59,60,61,365,366,2147483647])for(const format of ['%A|%a|%B|%b|%C|%d|%e|%H|%I|%j|%k|%l|%M|%m|%p|%S|%U|%u|%V|%W|%w|%X|%x|%y|%Y','%G %g %V'])add(format,{...base,[field]:value});
for(const zone of Object.keys(NATIVE_TIMEZONE_NAMES))for(const isdst of [-1,0,1])for(const format of ['%Z','%c|%Z|%z'])add(format,{...base,isdst},{zone,abbreviation:undefined});
let seed=0x72ba81c5;const random=()=>{seed^=seed<<13;seed^=seed>>>17;seed^=seed<<5;return seed>>>0;};
for(let i=0;i<10000;i++){const time=BigInt(random())*40000000n-70000000000000000n,fields=epochToCalendar(time);if(!fields)continue;fields.sec=[0,59,60,61][random()%4];const code=codes[random()%codes.length],flag=['','_','-','0','E','O'][random()%6];add('%'+flag+code,fields);}
for(let i=0;i<3000;i++){let format='';const alphabet='ab %EO_-0YmdzZG%HMSvr?';for(let n=0;n<1+random()%30;n++)format+=alphabet[random()%alphabet.length];add(format,base,{capacity:[0,1,2,4,8,20,250][random()%7]});}
for(const byte of [0,1,31,127,128,255])add('a'+String.fromCharCode(byte)+'b%Y');
const hex=value=>Buffer.from(value,'latin1').toString('hex')||'0';
const input=cases.map(c=>[hex(c.format),hex(c.options.zone),c.options.abbreviation===undefined||c.options.abbreviation===null?'N':hex(c.options.abbreviation),c.options.capacity,...keys.map(k=>c.fields[k])].join(' ')).join('\n')+'\n';
const lines=command(oracle,[],{input}).trimEnd().split('\n');assert.equal(lines.length,cases.length);const differences=[];
for(let i=0;i<cases.length;i++){const c=cases[i],want=Buffer.from(lines[i].split(':')[1]??'','hex').toString('latin1');let result;try{result=formatDarwinTime(c.format,c.fields,c.options);}catch(error){result='THROW:'+error.stack;}if(result!==want){differences.push({case:c,native:want,result});if(differences.length<6)console.error(JSON.stringify(differences.at(-1)));}}
fs.writeFileSync(path.join(work,'differences.json'),JSON.stringify(differences,null,2)+'\n');assert.deepEqual(differences.slice(0,12),[]);fs.writeFileSync(path.join(work,'validated.json'),JSON.stringify({cases:cases.length,yearCases:years,cLocale:true,capacity:250},null,2)+'\n');
console.log(`PASS: ${cases.length} actual macOS C-locale strftime comparisons; every Lua C99 specifier/E/O, padding/unknown sequences, BC..INT_MAX years, ISO boundaries, raw int32 fields, leap seconds, timezone pointers/process offsets, NUL and capacity limits.`);
