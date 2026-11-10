// First-pass memory64 C/JS differential; native/game/public remain separate.
import assert from 'node:assert/strict';
import {resolve} from 'node:path';
import {pathToFileURL} from 'node:url';
const {createGlyphsBridge}=await import(process.env.GLYPHS_RUNTIME?pathToFileURL(resolve(process.env.GLYPHS_RUNTIME)):new URL('../js/ported/glyphs-runtime.js',import.meta.url));
import {C} from '../js/ported/c-runtime.js';
const directory=resolve(process.env.GLYPHS_PROBE_DIR??'.cache/glyphs-first-pass');
const factory=async name=>(await import(pathToFileURL(resolve(directory,'glyphs-'+name+'.mjs')))).default;
const ref=await factory('reference'),hybrid=await factory('hybrid');
const text=(m,p)=>{p=Number(p);let q=p;while(m.HEAPU8[q])q++;return Buffer.from(m.HEAPU8.subarray(p,q)).toString('latin1');};
const layouts=m=>Object.fromEntries(Array.from({length:m._probe_layout_count()},(_,i)=>[text(m,m._probe_layout_name(i)),Number(m._probe_layout_value(i))]));
let modules,L,bridge,comparisons=0,scenario='initial',invoked=new Set();
async function pair(){const a=await ref();L=layouts(a);bridge??=createGlyphsBridge(L);const b=await hybrid({nethackPorted:{glyphs:(s,n,...a)=>{invoked.add(n);return bridge(s,n,...a);}}});assert.deepEqual(layouts(b),L);comparisons++;modules=[a,b];reset();}
await pair();
function reset(){modules.forEach(m=>m._probe_reset());}
function input(s){const data=typeof s==='string'?Buffer.from(s,'latin1'):s;for(const m of modules){const p=Number(m._probe_input());m.HEAPU8.set(data,p);m.HEAPU8[p+data.length]=0;}}
function compare(){const states=modules.map(m=>({snapshot:text(m,m._probe_snapshot()),trace:text(m,m._probe_trace()),dump:text(m,m._probe_dump()),input:text(m,m._probe_input())}));if(JSON.stringify(states[0])!==JSON.stringify(states[1]))for(const k of Object.keys(states[0]))if(states[0][k]!==states[1][k]){let i=0;while(states[0][k][i]===states[1][k][i])i++;console.error(scenario,k,i,JSON.stringify(states[0][k].slice(Math.max(0,i-80),i+160)),JSON.stringify(states[1][k].slice(Math.max(0,i-80),i+160)));}assert.deepEqual(states[1],states[0],scenario);assert.equal(C,undefined);comparisons++;}
function call(n,...a){const stack=modules.map(m=>m._probe_stack());const results=modules.map(m=>m['_probe_'+n](...a));assert.deepEqual(results[1],results[0],scenario+' return');comparisons++;modules.forEach((m,i)=>assert.equal(m._probe_stack(),stack[i],scenario+' stack'));compare();return results[0];}
const action=(a,x=0,y=0)=>call('call',a,x,y);
for(let g=-2;g<=L.MAX_GLYPH+2;g++){scenario='cmap '+g;action(0,g);}
for(const s of['','ABCxyz','G_invisible','g_InVisible','G_something_that_is_long_enough_to_rotate_hash_more_than_32_bits',Buffer.from([255,128,65,90,32,1])]){scenario='hash '+s;input(s);action(1);action(2);}
for(const s of['','bad','G_bad','S_bad','G_invisible','G_nothing','G_unexplored','G_warning0','G_warning5','G_stone_substrate','G_male_giant_ant','G_female_giant_ant','G_dark_expl_tl','G_lawful_altar','G_missile_zap_vbeam']){scenario='parse '+s;reset();input(s);call('request',0,0,0);action(21,1);call('request',0,0,0);action(22);}
for(let i=0;i<modules[0]._probe_loadsyms_count();i++){const s=text(modules[0],modules[0]._probe_loadsyms_name(i));if(!s||!modules[0]._probe_loadsyms_range(i))continue;scenario='symbol '+s;input(s);call('request',0,0,0);action(21,1);}
scenario='full dump';reset();action(19);const ids=text(modules[0],modules[0]._probe_dump()).trim().split('\n').map(line=>{const m=line.match(/^\((\d+)\) (.*)$/);assert.ok(m,line);return[Number(m[1]),m[2]];});assert.ok(ids.length>L.MAX_GLYPH/2 && ids.length<=L.MAX_GLYPH);comparisons++;
scenario='full cache';reset();call('option',0,1);action(6);action(12);call('option',0,0);call('clear');
for(const [g,id]of ids){scenario='cache lookup '+g;input(id);action(8);}
for(const [g,id]of ids.filter((_,i)=>i%53===0)){scenario='cache by glyph '+g;action(9,g);assert.equal(text(modules[0],modules[0]._probe_input()),id);comparisons++;call('request',0,0,0);action(21,1);}
scenario='cache misses';input('G_BAD_UNDEFINED');action(8);action(9,-1);action(7);action(7);action(12);
for(const s of['G_invisible/U+0041/red','G_nothing:U+1F600/#123456','G_unexplored: U+2603/0-0-0','G_warning0/blue','G_warning1/#ffffff','G_warning2/#000000','G_bad:U+0041/red','G_invisible:invalid/invalid','S_vwall:U+0042/red']){
 scenario='custom parse '+s;reset();call('option',0,1);input(s);action(3);action(4);action(5);for(let set=0;set<2;set++)for(const mask of[0,L.do_custom_colors,L.do_custom_symbols,L.do_custom_colors|L.do_custom_symbols])action(13,set,mask);action(24);action(23);action(17);
}
for(const set of[0,1])for(const named of[0,1])for(const utf of[0,1]){scenario='callback '+[set,named,utf];reset();call('symset',set,named,utf);call('request',4,123,0);input('U+1F600');call('color',0xffffffff);action(25,23);action(25,24);action(13,set,3);action(18,set);}
for(const type of[L.custom_nhcolor,L.custom_ureps])for(const set of[0,1]){scenario='entries '+type+'/'+set;reset();input('custom');for(const color of[0,1,0xffffff,0x1000000,0xffffffff]){call('custom',type,set,L.GLYPH_OBJ_OFF+L.POT_GAIN_ABILITY,color);call('custom',type,set,L.GLYPH_OBJ_PILETOP_OFF+L.POT_GAIN_ABILITY,color);}input(set?'rogue':'primary');action(16,type,set);action(13,set,3);call('description',L.POT_GAIN_ABILITY,L.POT_GAIN_ABILITY+1);call('description',L.POT_GAIN_ABILITY+1,L.POT_GAIN_ABILITY);action(15);call('flags',1,1,1,set);action(14);action(24);action(17);}
for(const colors of[0,1])for(const symbols of[0,1])for(const utf of[0,1]){scenario='custom gates '+[colors,symbols,utf];reset();input('G_invisible:U+1F600/#808080');action(3);call('flags',colors,symbols,0,0);call('symset',0,1,utf);action(13,0,3);action(24);action(17);}
scenario='duplicate description ownership';reset();input('U+2603');for(const offset of[L.GLYPH_OBJ_OFF,L.GLYPH_OBJ_PILETOP_OFF]){call('custom',L.custom_ureps,0,offset+L.POT_GAIN_ABILITY,0x2603);call('custom',L.custom_nhcolor,0,offset+L.POT_GAIN_ABILITY,0x123456);}action(13,0,3);call('description',L.POT_GAIN_ABILITY+1,L.POT_GAIN_ABILITY);call('option',0,1);action(15);action(15);action(17);
scenario='wizard listing';reset();action(6);call('option',2,1);call('option',5,1);modules.forEach(m=>assert.throws(()=>m._probe_call(20,7,0),/GLYPHS fixture exit 5/));assert.equal(C,undefined);compare();call('option',5,0);action(7);
scenario='empty explicit cache';action(10);input('G_test_private_cache');action(11,121);action(8);action(7);
for(const option of[3,4]){scenario='growth/reentry '+option;reset();call('option',option,1);input('G_invisible:U+0041/red');const before=modules.map(m=>m.HEAPU8.byteLength);action(3);if(option===3)modules.forEach((m,i)=>{assert.ok(m.HEAPU8.byteLength>before[i]);comparisons++;});}
scenario='optimized source static records';reset();input('G_warning3/#123456');action(3);call('private',1,0);assert.equal(call('private',1,1),0x123456n);comparisons++;assert.equal(call('private',1,2),4n);comparisons++;assert.equal(call('private',1,4),1n);comparisons++;
for(const value of[2147483647,-2147483648,734193]){scenario='mutable backing witness '+value;assert.equal(call('backing',0,1,BigInt(value)),BigInt(value));comparisons++;}call('backing',0,1,0n);
scenario='preserve first Module cache';action(6);const old=modules;await pair();scenario='second Module';assert.equal(action(12),0n);comparisons++;input('G_warning1/red');action(3);action(6);action(7);modules=old;scenario='old Module retains its private cache';assert.equal(action(12),1n);comparisons++;reset();scenario='first Module reused';input('G_warning2/blue');action(3);
assert.equal(invoked.size,27,'all configured original source bodies called');comparisons++;
console.log(`GLYPHS: ${comparisons} configured Emscripten-C/JS comparisons passed; ${invoked.size}/27 bodies invoked; native/game/public pending.`);
