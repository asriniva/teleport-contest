import {DataView,referenceBackend,referenceLabel,assertStackRestored,assertMemoryGrowth} from './native-test-backend.mjs';
import assert from './native-test-assert.mjs';
import {readFileSync} from 'node:fs';
import {resolve} from 'node:path';
import {pathToFileURL} from 'node:url';
import {callNhlobj} from '../js/nethack/bindings/nhlobj.js';
import * as core from '../js/ported/nhlobj.js';
import {C,R,T} from '../js/c-runtime/context.js';
const author=process.env.TELEPORT_NHLOBJ_PROBES,dir=author?pathToFileURL(resolve(author)+'/'):new URL('../.cache/tu-probes/',import.meta.url);
const referenceFactory=(await import(new URL('nhlobj-reference.mjs',dir))).default,hybridFactory=(await import(new URL('nhlobj-hybrid.mjs',dir))).default;
const ref=await referenceBackend('nhlobj',referenceFactory)();
function text(m,p){if(!p)return null;let end=Number(p);while(m.HEAPU8[end])end++;return Buffer.from(m.HEAPU8.slice(Number(p),end)).toString();}
const L={size:Number(ref._probe_context_size())};for(let i=0;i<ref._probe_layout_count();i++){const k=text(ref,ref._probe_layout_name(i)),v=ref._probe_layout_value(i);L[k]=['NON_PM','LUA_REGISTRYINDEX'].includes(k)?Number(BigInt.asIntN(64,v)):Number(v);}
if(!author)assert.deepEqual(L,JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json',import.meta.url))).nhlobj);
for(const k of ['objSize','regSize','NUM_OBJECTS','NUM_TIME_FUNCS','LUA_OK','ROCK','CHEST','DAGGER','ARROW','POT_HEALING','CORPSE','EGG','STATUE','TIN','FIGURINE','PM_HUMAN','PM_GHOST'])assert.ok(Number.isSafeInteger(L[k]),k);
const runtime={nhlobj:(services,name,...args)=>callNhlobj(services,L,name,...args)},modules=[ref,await hybridFactory({nethackPorted:runtime})],stacks=modules.map(m=>m._probe_stack());let comparisons=0;
const fields=["o_id", "ox", "oy", "otyp", "owt", "quan", "spe", "oclass", "invlet", "where", "corpsenm", "usecount", "oeaten", "age", "owornmask", "lua_ref_cnt"];
function snapshot(m){const objects=[];for(let i=0;i<m._probe_count(0);i++){const at=Number(m._probe_bytes(i)),raw=Buffer.from(m.HEAPU8.slice(at,at+L.objSize));for(const k of ['nobj','nexthere','cobj','ocontainer','oextra'])raw.fill(0,L['obj_'+k],L['obj_'+k]+8);objects.push({alive:!!m._probe_object(i),raw,fields:fields.map((k,j)=>m._probe_field(i,j)),links:[0,1,2,3].map(j=>m._probe_link(i,j)),name:text(m,m._probe_oname(i)),timers:Array.from({length:L.NUM_TIME_FUNCS},(_,j)=>m._probe_timer(i,j))});}return{made:m._probe_count(0),free:m._probe_count(1),top:m._probe_count(2),objects,trace:text(m,m._probe_trace()),output:text(m,m._probe_output())};}
function state(label='state'){assert.deepEqual(snapshot(modules[1]),snapshot(modules[0]),label);assert.equal(C,undefined);assert.equal(R,undefined);assert.equal(T,undefined);modules.forEach((m,i)=>assertStackRestored(m,stacks[i]));comparisons++;}
function call(fn,...args){const out=modules.map(m=>m['_probe_'+fn](...args));assert.deepEqual(out[1],out[0],fn);state(fn);comparisons++;return out[0];}
function stringCall(fn,s,...prefix){if(process.env.TELEPORT_NHLOBJ_DEBUG)console.error(fn,s);const out=modules.map(m=>{const b=Buffer.from(s+'\0'),p=m._malloc(BigInt(b.length));m.HEAPU8.set(b,Number(p));try{return m['_probe_'+fn](...prefix,BigInt(p));}finally{m._free(BigInt(p));}});assert.deepEqual(out[1],out[0],fn+' '+s);state(s);comparisons++;return out[0];}
const evalLua=s=>stringCall('eval',s),reset=()=>call('reset'),option=(k,v)=>call('option',k,v),set=(slot,key,v)=>call('set',slot,fields.indexOf(key),BigInt(v));
const serialize="local function serialize(t) local k={} for key in pairs(t) do k[#k+1]=key end table.sort(k) local o={} for _,key in ipairs(k) do o[#o+1]=key..'='..tostring(t[key]) end return table.concat(o,';') end ";
function check(s,expected){assert.equal(evalLua(s),L.LUA_OK,s);if(expected!==undefined)assert.equal(text(ref,ref._probe_output()),expected,s);}
reset();check("return type(obj),type(getmetatable(obj))",'nil');
for(const [table,name]of [[0,'l_obj_methods'],[1,'l_obj_meta']])for(let i=0;i<core[name].length;i++){const row=core[name][i],expected=row.name||null;for(const m of modules)assert.equal(text(m,m._probe_reg_name(table,i)),expected);assert.equal(modules[0]._probe_reg_callback(table,i),modules[1]._probe_reg_callback(table,i));comparisons+=3;}
// Real C Lua userdata/methods, native null-object behavior and protected metatable.
for(const wish of ['rock','chest','corpse','arrow','hands','missing','']){reset();check("o=obj.new("+JSON.stringify(wish)+"); return tostring(o:isnull())",String(wish==='hands'||wish==='missing'));check(serialize+"return serialize(o:totable())");check("return type(getmetatable(o).__gc)..':'..tostring(getmetatable(o).__index)",'function:nil');check("o=nil;collectgarbage('collect');return 'collected'",'collected');}
for(const value of ["{}","{id='rock'}","{id='chest'}","{class='!'}","{class='?'}","{class='x'}","{class='xx'}","{id=function() return 'arrow' end}","{id=function() local x=obj.new('arrow');return x:totable().otyp_name end}"]){reset();check('o=obj.new('+value+');return o:totable().otyp_name');}
// Every actual catalogue class projects live flags, signed fields and descriptor indices.
reset();for(let i=0;i<L.NUM_OBJECTS;i++)check(serialize+'return serialize(obj.class('+i+'))');
for(const typ of [L.ROCK,L.CHEST,L.DAGGER,L.ARROW,L.POT_HEALING,L.CORPSE,L.EGG,L.STATUE,L.TIN,L.FIGURINE]){reset();call('new',typ);stringCall('push','o',0);for(const [k,v]of [['o_id',0xffffffffn],['ox',-123],['oy',32767],['owt',0xffffffffn],['quan',9007199254740993n],['spe',-128],['invlet',122],['corpsenm',L.PM_GHOST],['usecount',-2147483648],['oeaten',0xffffffffn],['age',-9007199254740993n],['owornmask',-9223372036854775808n]])set(0,k,v);for(let bit=0;bit<27;bit++)call('bit',0,bit,bit%4+1);stringCall('name','Named object',0);option(1,1);check(serialize+'return serialize(o:totable())');check(serialize+'return serialize(o:class())');}
// Actual floor lists/contained lists, pointer identity, geometry conversion, fresh memory views.
reset();check("a=obj.new('rock');b=obj.new('arrow');a:placeobj(5,6);b:placeobj(5,6);return obj.at(5,6):totable().o_id..':'..obj.at(5,6):next(true):totable().o_id",'101:100');check("return obj.next():totable().o_id..':'..obj.next():next():totable().o_id",'101:100');check("return tostring(a:container():isnull())",'true');check("box=obj.new('chest');box:addcontent(a);box:addcontent(b);return box:contents():totable().o_id..':'..a:container():totable().o_id",'101:102');check("a=nil;b=nil;box=nil;collectgarbage('collect');return 'done'",'done');
for(const room of [false,true]){reset();option(room?6:4,7);if(!room)option(5,8);check("o=obj.new('rock');o:placeobj(2,3);return o:totable().ox..':'..o:totable().oy",room?'9:11':'9:11');check("return obj.at(2,3):totable().o_id",'100');}
reset();option(3,1);const oldBuffers=modules.map(m=>m.HEAPU8.buffer);check("o=obj.new('rock');o:placeobj(5,6);return o:totable().otyp_name",'rock');modules.forEach((m,i)=>assertMemoryGrowth(m,oldBuffers[i]));
// Unsigned reference counters wrap independently of signed temporary refs.
reset();call('new',L.ROCK);set(0,'where',L.OBJ_INVENT);stringCall('push','o',0);set(0,'lua_ref_cnt',0xffffffffn);stringCall('push','alias',0);assert.equal(ref._probe_field(0,15),0n);check("getmetatable(o).__gc(o);getmetatable(alias).__gc(alias);return tostring(o:isnull())",'true');
// Native timer API has signed64 amounts and independent object-only type predicates.
for(const timer of ['rot-organic','rot-corpse','revive-mon','zombify-mon','burn-obj','hatch-egg','fig-transform','shrink-glob','melt-ice'])for(const when of [0n,-1n,1n,9007199254740993n,9223372036854775807n]){reset();check("o=obj.new('rock');o:start_timer("+JSON.stringify(timer)+','+when+");return tostring(o:has_timer("+JSON.stringify(timer)+"))");check("return tostring(o:peek_timer("+JSON.stringify(timer)+"))");check("o:start_timer("+JSON.stringify(timer)+",12);return tostring(o:stop_timer("+JSON.stringify(timer)+"))");check("o:stop_timer();return 'stopped'",'stopped');}
// Public inventory handoff retains the source's distinct old-object reference-count update.
for(const merge of [-1,0]){reset();check("target=obj.new('rock');giveobj(target);o=obj.new('rock');alias=o;return 'ready'",'ready');option(0,merge);check("giveobj(o);return o:totable().o_id");check("giveobj(o);return o:totable().where");}
for(const merge of [-1,1]){reset();check("box=obj.new('chest');target=obj.new('rock');box:addcontent(target);o=obj.new('rock');return 'ready'",'ready');option(0,merge);check("box:addcontent(o);return o:totable().o_id");}
// Bury typed boolean output, existing coords, coordinate conversion and consumed objects.
for(const gone of [0,1])for(const xy of ['',',5,6',',0,0',',32768,65537']){reset();option(2,gone);check("o=obj.new('rock');return tostring(o:bury("+xy.replace(/^,/, '')+"))");check(serialize+'return serialize(o:totable())');}
// Native Lua errors/argument checks are exact; actual protected calls resume after callbacks.
for(const s of ["return obj.new({id='not an object',class='!'})","return obj.new()","return obj.new(3)","return obj.new(true)","return obj.at()","return obj.at('x',2)","return obj.class()","return obj.class('bad')","return obj.class(obj.new('missing'))","local o=obj.new('rock');return o:placeobj(1)","return obj.isnull({})","return obj.isnull(io.stdout)","local o=obj.new('missing');return o:contents()","local o=obj.new('rock');return o:start_timer('not-a-timer',1)","local o=obj.new('rock');return o:has_timer()","local o=obj.new('rock');return o:peek_timer()","local o=obj.new('rock');return o:stop_timer(1,2)","local o=obj.new('rock');return o:start_timer()","local o=obj.new('rock');return o:bury(1)"]){reset();assert.notEqual(evalLua(s),L.LUA_OK,s);check("return 17",'17');}
reset();check("o=obj.new('missing');return tostring(o:next(true))",'true');check("getmetatable(o).__gc(o);getmetatable(o).__gc(o);return tostring(o:isnull())",'true');
// GC retains objects in native world lists; source LUA_FREE object remains accessible but null.
reset();call('new',L.ROCK);stringCall('push','o',0);call('release',0);check("return tostring(o:isnull())",'true');check(serialize+'return serialize(o:totable())','NO_OBJ=1');check("o=nil;collectgarbage('collect');return 'free'",'free');
// Repeated real native-to-JS callbacks release each original automatic buffer frame.
reset();check("for i=1,96 do local x=obj.new('rock');getmetatable(x).__gc(x) end return '96'",'96');assert.equal(ref._probe_count(1),96);
// Two actual Module instances share one JS runtime without sharing registration/native addresses.
const other=await hybridFactory({nethackPorted:runtime});other._probe_reset();const before=modules[1]._probe_count(0);other._probe_new(L.CHEST);assert.equal(modules[1]._probe_count(0),before);comparisons++;
console.log('NHLOBJ '+comparisons+' comparisons passed ('+referenceLabel+' vs JavaScript; actual C Lua5.4.8 + controlled object/timer world).');
