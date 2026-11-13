import assert from 'node:assert/strict';
import {CMemory,createMemoryServices,createBitfields,createCTypes,createRecordViews,createFunctions,createLinker,CExit,createRuntime} from '../js/c-runtime/index.js';

// Fictional application declarations exercise the runtime without NetHack types.
const memory=new CMemory({initialBytes:256,maximumBytes:1024*1024});
const metadata={aliases:{value_t:'short'},enums:{'enum shade':{size:4,signed:true}},records:{
    payload:{size:8,fields:{bits:{offset:0,ctype:'unsigned long'},low:{offset:0,ctype:'unsigned int'}}},
    point:{size:4,fields:{x:{offset:0,ctype:'short'},y:{offset:2,ctype:'short'}}},
    packet:{size:32,fields:{point:{offset:0,ctype:'struct point',record:'point'},
        flags:{offset:4,ctype:'unsigned int',bits:3,shift:2},
        items:{offset:8,ctype:'short[2]'},next:{offset:16,ctype:'struct packet *'},label:{offset:24,ctype:'char *'}}},
}};
const transport=createMemoryServices(memory),functions=createFunctions();
const ctypes=createCTypes(memory,metadata,createBitfields(memory,metadata));
const environment={ctypes,memory,address:transport.address,services:transport};
const views=createRecordViews(environment,{point:{horizontal:'x'}});
const at=memory.calloc(2,32),first=views.record('packet',at),second=views.record('struct packet',at+32);
assert.equal(views.record('struct packet',at),first);
first.point.x=65535;first.point.horizontal=10;assert.equal(first.point.x,10);
assert.ok(!Object.keys(first.point).includes('horizontal'));
first.point.y=-22;second.point=first.point;first.point.y=5;
assert.equal(second.point.y,-22);
first.next=second;assert.equal(first.next,second);
first.label='shared text';assert.equal(memory.readString(Number(first.label)),'shared text');
const sentinel=transport.read('Uint8',at+4);first.flags=5;
assert.equal(first.flags,5);assert.equal(transport.read('Uint8',at+4)&~28,sentinel&~28);
first.items[0]=32768;assert.equal(first.items[0],-32768);
assert.equal(first.items['01'],first.items[1]);
assert.throws(()=>first.items[2],/bounds/);
const points=views.array('struct point',at,2);
assert.equal(points[2].address,at+8);assert.throws(()=>points[3],/bounds/);
assert.throws(()=>{points[2]=first.point;},/bounds/);
points.length=99;assert.throws(()=>points[3],/bounds/); // Extent is declaration-owned.
assert.equal(views.advance(first,1),second);
assert.throws(()=>views.advance({address:at},1),/Unrecognized/);
ctypes.store('enum shade',at+40,-1);assert.equal(ctypes.load('enum shade',at+40),-1);
assert.equal(ctypes.size('value_t'),2);
const payload=views.record('union payload',memory.calloc(1,8));
payload.bits=0x1122334455667788n;assert.equal(payload.low,0x55667788);
payload.low=0xaabbccdd;assert.equal(payload.bits,0x11223344aabbccddn);
const old=memory.buffer;memory.malloc(4096);assert.notEqual(memory.buffer,old);
assert.equal(first.next,second);assert.equal(first.point.x,10);first.point.x=99;
assert.equal(ctypes.getField('point',at,'x','short'),99);

const core=createRuntime({memory:new CMemory(),metadata,typeAliases:{small_t:'short'},conversionAliases:{small:'short'}});
assert.equal(core.ctypes.size('small_t'),2);assert.equal(core.services.small(65535),-1);
assert.notEqual(core.services.moduleKey,transport.moduleKey);

// Linking tests real scope/ownership semantics independently of game startup.
let current,events=[];
const services={...transport};
const withEnvironment=(env,fn,...args)=>{const previous=current;current=env;try{return fn(...args);}finally{current=previous;}};
const linker=createLinker({memory,transport,functions,services,ctypes,withEnvironment,
    prototypes:{add:'int (int, int)',read:'short (void)',consume:'void (struct point *)',variadic:'int (int, ...)'}});
const global=linker.allocateGlobal('counter',4);
assert.equal(linker.requireGlobal('counter'),global);linker.linkGlobal('counter-alias',global);
assert.equal(linker.requireGlobal('counter-alias'),global);
assert.throws(()=>linker.allocateGlobal('counter',4),/Duplicate/);
assert.throws(()=>linker.requireGlobal('missing'),/Unresolved/);
linker.register('math',{add:(a,b)=>a+b,read:()=>current.name,consume:()=>{},variadic:()=>{}},{name:'math'},
    {initialize:()=>events.push('math')});
linker.register('outer',{run:()=>{assert.equal(current.name,'outer');const result=linker.call('math','read');assert.equal(current.name,'outer');return result;},fail:()=>{transport.stackAlloc(8);throw new Error('failure');}},{name:'outer'},
    {dependencies:['math'],initialize:()=>events.push('outer')});
assert.equal(linker.call('outer','run'),'math');assert.deepEqual(events,['math','outer']);
assert.equal(current,undefined);
assert.equal(functions.indirect(services.add.address,'iii',3,4),7);
assert.equal(services.add.address,services.add.address);
assert.throws(()=>services.variadic.address,/explicit ABI/);
assert.throws(()=>linker.functionPointer('add','ii'),/Conflicting/);
const allocations=memory.live.size;
assert.throws(()=>linker.call('outer','fail'),/failure/);
assert.equal(memory.live.size,allocations);assert.equal(current,undefined);
linker.register('lazy',{});linker.deferFunctions('lazy',{later:()=>12});
assert.equal(linker.resolve('later')(),12);
linker.register('other',{});linker.deferFunctions('other',{conflict:()=>1});linker.deferFunctions('lazy',{conflict:()=>2});
assert.throws(()=>linker.resolve('conflict'),/Ambiguous/);
linker.register('retry',{},services,{initialize:()=>{if(events.at(-1)!=='retry') {events.push('retry');throw new Error('retry');}}});
assert.throws(()=>linker.start('retry'),/retry/);assert.equal(linker.status().retry,'failed');
linker.start('retry');assert.equal(linker.status().retry,'ready');
const result=functions.withJumpScope(scope=>functions.withJumpScope(()=>functions.longjmp(scope,7)));
assert.equal(result,7);
assert.throws(()=>functions.exit(4),error=>error instanceof CExit&&error.status===4);
// A native entry may own normalization inside a mixed legacy/native module.
let prepared=0;
const native=x=>x+1;native.nativeDirect=true;native.nativePrepared=true;
linker.register('mixed-native-preparation',{native,legacy:x=>x+1},services,{prepareArgs:(_name,args)=>{prepared++;return args.map(x=>x+10);}});
assert.equal(linker.call('mixed-native-preparation','native',2),3);
assert.equal(prepared,0,'self-prepared native entry bypasses generic argument preparation');
assert.equal(linker.call('mixed-native-preparation','legacy',2),13);
assert.equal(prepared,1,'sibling legacy entry retains the existing prepareArgs contract');
console.log('PASS: shared typed records/aliases/unions of storage, pointers/arrays/bitfields/growth and linker globals/lazy ownership/callbacks/reentry/unwinding/initialization retry.');
