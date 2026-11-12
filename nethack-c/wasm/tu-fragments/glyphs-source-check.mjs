// Read-only source/data/ABI/configuration guard, separate from behavior tests.
import assert from 'node:assert/strict';
import {readFile} from 'node:fs/promises';
import {resolve,dirname} from 'node:path';
import {fileURLToPath} from 'node:url';
import {execFileSync} from 'node:child_process';
const root=resolve(dirname(fileURLToPath(import.meta.url)),'../../..');
const read=p=>readFile(resolve(root,p),'utf8');
const [source,prepared,core,runtime,support,library]=await Promise.all(['nethack-c/upstream/src/glyphs.c','.cache/wasm64-build/tree/src/glyphs.c','js/ported/glyphs.js','js/nethack/bindings/glyphs.js','nethack-c/wasm/tu-fragments/glyphs-support.c','nethack-c/wasm/tu-libraries/glyphs.js'].map(read));
assert.equal(prepared,source,'GLYPHS prepared/pristine provenance');
const defs=JSON.parse(await read('nethack-c/wasm/compile-defines.json'));
const args=['-E','-sMEMORY64=1','-I'+resolve(root,'.cache/wasm64-build/tree/include'),'-include',resolve(root,'nethack-c/wasm/native-terminal.h'),...defs.map(d=>'-D'+d),resolve(root,'.cache/wasm64-build/tree/src/glyphs.c')];
const emcc=resolve(root,'.cache/emsdk/upstream/emscripten/emcc');
const pre=execFileSync(emcc,args,{encoding:'utf8',maxBuffer:8*1024*1024});
let active=false,lines=[];for(const line of pre.split('\n')){const m=line.match(/^# \d+ "([^"]+)"/);if(m)active=m[1]===resolve(root,'.cache/wasm64-build/tree/src/glyphs.c');else if(active)lines.push(line);}
const configured=lines.join('\n'),strip=s=>s.replace(/\/\*[\s\S]*?\*\/|\/\/[^\n]*/g,'');
const names=[...configured.matchAll(/\b(\w+)\s*\([^;{}]*\)\s*\{/g)].map(m=>m[1]).filter(n=>!['if','for','while','switch'].includes(n));
assert.deepEqual([...core.matchAll(/export function (\w+)\(/g)].map(m=>m[1]),names);assert.equal(names.length,27);
const c=strip(source),js=strip(core);
const fixtureData=await read('nethack-c/wasm/tu-fragments/glyphs-fixture-data.h');
for(const [file,declaration]of[['symbols','const struct symparse loadsyms'],['earlyarg','struct enum_dump monsdump'],['earlyarg','struct enum_dump objdump']]){
 const upstream=await read('.cache/wasm64-build/tree/src/'+file+'.c');
 const block=upstream.match(new RegExp(declaration.replaceAll('[','\\[')+'\\[\\] = \\{[\\s\\S]*?\\n\\};'))[0];assert.ok(fixtureData.includes(block),'actual external catalogue '+declaration);
}

for(const name of['altar_text','zap_texts','swallow_texts','expl_type_texts','expl_texts']){
 const original=c.match(new RegExp('static const char \\*const '+name+'\\[\\] = \\{([\\s\\S]*?)\\};'))[1];
 const actual=js.match(new RegExp('const '+name+' = \\[([\\s\\S]*?)\\];'))[1];
 const strings=s=>[...s.matchAll(/"(?:\\.|[^"\\])*"/g)].map(m=>JSON.parse(m[0]));assert.deepEqual(strings(actual),strings(original),name+' exact source table');
}
assert.ok(c.includes('static const int offsets[2] = { GLYPH_OBJ_OFF, GLYPH_OBJ_PILETOP_OFF };'));
assert.ok(js.includes('const offsets = [ C.GLYPH_OBJ_OFF, C.GLYPH_OBJ_PILETOP_OFF ];'));
assert.ok(c.includes('uint8 utf8str[6] = { 0, 0, 0, 0, 0, 0 };'));assert.ok(js.includes('C.byteArray([0,0,0,0,0,0])'));
assert.ok(c.includes('static const struct find_struct zero_find = { 0 };'));assert.ok(c.includes('static const long nonzero_black = CLR_BLACK | NH_BASIC_COLOR;'));
assert.ok(support.includes('static teleport_glyphs_actual_find teleport_glyphs_find_storage[3];'));assert.ok(!support.includes('const teleport_glyphs_actual_find'));
assert.ok(runtime.includes('for(const [key,value]of Object.entries(glyphs.zero_find))state.zero_find[key]=value;'));
assert.ok(support.includes('#ifdef TELEPORT_GLYPHS_VALIDATE_SOURCE'));assert.ok(!support.includes('TELEPORT_REFERENCE_TU'));
const tokens=[...core.matchAll(/\/\*[\s\S]*?\*\/|\/\/[^\n]*|"(?:\\.|[^"\\])*"/g)];
const literals=new Set(tokens.filter(m=>m[0][0]==='"').map(m=>JSON.parse(m[0])));
for(const name of ['CLR_BLACK','NH_BASIC_COLOR','to_custom_symset_entry_callback.glyphnag','to_custom_symset_entry_callback.colornag'])literals.delete(name);
literals.delete('Unimplemented customization feature,');literals.delete(' ignoring for now');literals.add('Unimplemented customization feature, ignoring for now');
const actual=JSON.parse(library.match(/var literals=new Set\((\[[^\n]*\])\)/)[1]);assert.deepEqual(new Set(actual),literals);
const capacity=actual.reduce((n,s)=>n+Buffer.byteLength(s)+1,0);assert.equal(capacity,909);assert.ok(support.includes(`teleport_glyphs_literals[${capacity}]`));
const expected=[[126,'glyphrep_to_custom_map_entries'],[465,'match_glyph'],[1025,'parse_id'],[1042,'parse_id'],[1044,'parse_id'],[1082,'parse_id'],[1085,'parse_id'],[1106,'parse_id']];
const owners=[...configured.matchAll(/\b(\w+)\s*\([^;{}]*\)\s*\{/g)].filter(m=>names.includes(m[1]));
const macroSites=[];for(const m of configured.matchAll(/nh_snprintf\(__func__,\s*(\d+),/g))macroSites.push([Number(m[1]),owners.filter(f=>f.index<m.index).at(-1)[1]]);assert.deepEqual(macroSites,expected);
for(const[line,fn]of expected)assert.ok(js.includes(`C.Snprintf("${fn}", ${line},`));assert.equal([...js.matchAll(/C\.Snprintf\(/g)].length,8);
assert.equal([...js.matchAll(/\bC\.(rn2|rnd|rn1)\(/g)].length,0);
assert.ok(js.includes('C.Strcat(buf[3], " ");'),'source swallow separator');
assert.ok(js.includes('hash = ((hash << 1) | (hash >>> 31)) >>> 0;'));assert.ok(js.includes('hash = (hash ^ ch) >>> 0;'));
assert.ok(runtime.includes('getInt8(address(p)+Number(i))'));assert.ok(runtime.includes('BigInt.asUintN(64,BigInt(v))'));
for(const fn of['glyphrep_to_custom_map_entries','match_glyph','glyphrep','parse_id']){const calls=[...js.matchAll(new RegExp('(?<!function )\\b'+fn+'\\(', 'g'))];assert.equal(calls.length,0,'internal automatic storage call scope '+fn);}
const macros=execFileSync(emcc,[args[0],'-dM',...args.slice(1)],{encoding:'utf8'});assert.match(macros,/^#define ENHANCED_SYMBOLS\b/m);assert.doesNotMatch(macros,/^#define TEST_GLYPHNAMES\b/m);
assert.ok(!support.includes('src/glyphs.c'));assert.ok(!support.includes('glyphid_cache full'));
console.log('GLYPHS source guard: identical provenance;27 configured functions;5 exact text tables+2 offsets+6 bytes;8 actual CPP format origins;91 literals/909bytes;unsigned hash/signedchar/size_t64/static backing/lifetime guards pass.');
