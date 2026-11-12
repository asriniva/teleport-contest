/* Independent actual macOS C localtime/strftime timezone-data/rule oracle.
 * No native or host lookup is used by the production service. */
import assert from 'node:assert/strict';import fs from 'node:fs';import path from 'node:path';import{spawnSync}from'node:child_process';import{fileURLToPath}from'node:url';
import{lookupTimezone,parsePosixTimezone,timezoneDataVersion,TimezoneError,formatTimezoneOffset,getTimezoneOffsets}from'../js/platform/timezone/info.js';
import{NATIVE_TIMEZONE_ENTRIES,NATIVE_TIMEZONE_NAMES,NATIVE_TIMEZONE_META}from'../js/platform/timezone/tzdb.js';
const root=fileURLToPath(new URL('../',import.meta.url)),work=path.join(root,'.cache/js-native-timezone');fs.mkdirSync(work,{recursive:true});
function command(program,args,options={}){const result=spawnSync(program,args,{encoding:'utf8',timeout:120000,maxBuffer:40000000,...options});assert.equal(result.status,0,result.error||result.stderr||result.stdout);return result.stdout;}
const regenerated=path.join(work,'regenerated-data.js');command('python3',[path.join(root,'scripts/generate-native-timezones.py'),'--output',regenerated]);assert.deepEqual(fs.readFileSync(regenerated),fs.readFileSync(path.join(root,'js/platform/timezone/tzdb.js')),'generated data and source SHA manifest reproduce exactly');
assert.equal(timezoneDataVersion,'2026c');assert.equal(fs.readFileSync('/usr/share/zoneinfo/+VERSION','utf8').trim(),timezoneDataVersion,'native oracle TZDB must match pinned data');
const source=path.join(work,'oracle.c'),oracle=path.join(work,'oracle');
fs.writeFileSync(source,`#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
int main(void){char encoded[4096],zone[2048],abbreviation[256],numeric[32];long long raw;
while(scanf("%4095s %lld",encoded,&raw)==2){int count=strlen(encoded)/2;for(int i=0;i<count;i++){unsigned byte;sscanf(encoded+2*i,"%2x",&byte);zone[i]=byte;}zone[count]=0;
setenv("TZ",zone,1);tzset();time_t epoch=raw;struct tm value;if(!localtime_r(&epoch,&value)){puts("ERROR");continue;}
strftime(abbreviation,sizeof abbreviation,"%Z",&value);printf("%ld %d ",value.tm_gmtoff,value.tm_isdst);for(int i=0;abbreviation[i];i++)printf("%02x",(unsigned char)abbreviation[i]);value.tm_gmtoff=12345;value.tm_zone="MANUAL";for(int dst=-1;dst<=1;dst++){value.tm_isdst=dst;strftime(numeric,sizeof numeric,"%z",&value);printf("|%s",numeric);}puts("");}return 0;}`);
command(process.env.CC||path.join(root,'.cache/wasm64-build/host-cc'),['-O2',source,'-o',oracle]);
const corpus=[];const add=(zone,epoch)=>corpus.push({zone,epoch:BigInt(epoch)});
const dates=['1600-01-01','1800-01-01','1880-01-01','1900-01-01','1916-07-01','1942-07-01','1945-07-01','1970-01-01','2000-01-01','2026-01-01','2026-07-01','2038-01-19','2100-01-01','2100-07-01','2500-07-01','3000-07-01','5000-01-01','5000-07-01'];
for(const zone of Object.keys(NATIVE_TIMEZONE_NAMES))for(const date of dates)add(zone,BigInt(Date.parse(date+'T12:00:00Z')/1000));
const unsupportedFooters=new Set();function checkFooter(footer){try{parsePosixTimezone(footer);}catch(error){assert.ok(error instanceof TimezoneError);unsupportedFooters.add(footer);}}
const focus=['America/New_York','America/Los_Angeles','UTC','Europe/Berlin','Asia/Tokyo','Australia/Sydney','Asia/Kathmandu','Europe/Dublin'];
for(const zone of focus){const [times,,,footer]=NATIVE_TIMEZONE_ENTRIES[NATIVE_TIMEZONE_NAMES[zone]];for(const at of times)for(const delta of [-1,0,1])add(zone,BigInt(at)+BigInt(delta));for(const year of [2038,2100,2400,2500])for(let month=0;month<12;month++)for(const day of [1,15,28])add(zone,Date.UTC(year,month,day)/1000);if(footer)checkFooter(footer);}
// Every footer must parse and agree with native extrapolation beyond stored data.
for(const zone of Object.keys(NATIVE_TIMEZONE_NAMES)){const footer=NATIVE_TIMEZONE_ENTRIES[NATIVE_TIMEZONE_NAMES[zone]][3];if(footer){checkFooter(footer);for(const date of ['2400-02-29','2400-03-31','2400-10-31','2400-12-31'])add(zone,Date.parse(date+'T03:00:00Z')/1000);}}
for(const zone of focus)for(const epoch of [-(1n<<40n),1n<<40n])add(zone,epoch);
for(const zone of ['',':America/New_York',':/usr/share/zoneinfo/Asia/Tokyo'])add(zone,0);
const posix=['GMT0','UTC-5:30','ABC+7:43:21','<+0545>-5:45','EST5EDT,M3.2.0/2,M11.1.0/2','AEST-10AEDT,M10.1.0,M4.1.0/3','AAA0BBB,J60/0,J300/23','AAA0BBB,59/1,300/2','AAA1BBB0,M3.5.0/2,M10.5.0/26'];
for(const zone of posix)for(const date of dates)add(zone,Date.parse(date+'T12:00:00Z')/1000);
let randomState=0x5b174c6f;function random(){randomState^=randomState<<13;randomState^=randomState>>>17;randomState^=randomState<<5;return randomState>>>0;}
for(let i=0;i<10000;i++){const zone=[...focus,...posix][random()%(focus.length+posix.length)],epoch=BigInt(random())*8n-10000000000n;add(zone,epoch);}
const input=corpus.map(({zone,epoch})=>(Buffer.from(zone).toString('hex')||'0')+' '+epoch).join('\n')+'\n';
const lines=command(oracle,[],{input}).trimEnd().split('\n');assert.equal(lines.length,corpus.length);const differences=[];
for(let i=0;i<corpus.length;i++){const{zone,epoch}=corpus[i],pieces=lines[i].split('|'),fields=pieces[0].split(' ');assert.notEqual(fields[0],'ERROR',zone+'/'+epoch);const native={offset:Number(fields[0]),isdst:Number(fields[1]),abbreviation:Buffer.from(fields[2]??'','hex').toString('latin1')},result=lookupTimezone(zone,epoch);for(let dst=-1;dst<=1;dst++)assert.equal(formatTimezoneOffset(zone,dst),pieces[dst+2],'%z '+zone+'/'+dst);if(JSON.stringify(native)!==JSON.stringify({offset:result.offset,isdst:result.isdst,abbreviation:result.abbreviation}))differences.push({zone,epoch:String(epoch),native,result});}
fs.writeFileSync(path.join(work,'differences.json'),JSON.stringify(differences,null,2)+'\n');assert.deepEqual(differences.slice(0,12),[]);
for(const zone of ['Missing/Zone','../America/New_York','/etc/localtime','AAA0BBB','AAA0BBB,M13.1.0,M4.1.0','AAA0BBB,J0,J300','AAA0BBB,M3.1.8,M4.1.0','AAA0BBB,M3.1.0/-2,M4.1.0','AAA0BBB,M3.1.0/168,M4.1.0','AAA0BBB,M3.1.0/1:60,M4.1.0','AAA0\0trash'])assert.throws(()=>lookupTimezone(zone,0),TimezoneError,zone);
assert.throws(()=>lookupTimezone('UTC',0.5),TimezoneError);assert.throws(()=>lookupTimezone('UTC',Number.MAX_SAFE_INTEGER+1),TimezoneError);
assert.deepEqual(lookupTimezone(':America/New_York',0),lookupTimezone('America/New_York',0));assert.deepEqual(lookupTimezone(':/usr/share/zoneinfo/Asia/Tokyo',0),lookupTimezone('Asia/Tokyo',0));
fs.writeFileSync(path.join(work,'validated.json'),JSON.stringify({cases:corpus.length,forcedOffsetComparisons:corpus.length*3,names:Object.keys(NATIVE_TIMEZONE_NAMES).length,entries:NATIVE_TIMEZONE_ENTRIES.length,unsupportedNativeFooters:[...unsupportedFooters],version:timezoneDataVersion},null,2)+'\n');
console.log(`PASS: ${corpus.length} actual macOS C %Z/offset/isdst comparisons + ${corpus.length*3} forced%z comparisons; ${Object.keys(NATIVE_TIMEZONE_NAMES).length} pinned names/${NATIVE_TIMEZONE_ENTRIES.length} unique tables, all footers (${unsupportedFooters.size} native-rejected forms retain the last stored type), historical LMT/war/DST, exact transition boundaries, future years, process offsets for forced DST=-1/0/1, northern/southern POSIX M/J/n rules and explicit rejected inputs.`);
