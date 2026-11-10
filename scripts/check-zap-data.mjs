// Development-only original-source/data/ABI guard. Never bundled in game.
import assert from 'node:assert/strict';
import fs from 'node:fs';
import * as core from '../js/ported/zap.js';
const source=fs.readFileSync('nethack-c/upstream/src/zap.c','utf8');
const prepared=fs.readFileSync('.cache/wasm64-build/tree/src/zap.c','utf8');
const js=fs.readFileSync('js/ported/zap.js','utf8');
const expected=["zaptype", "learnwand", "bhitm", "release_hold", "probe_objchain", "probe_monster", "get_obj_location", "get_mon_location", "montraits", "get_container_location", "zombie_can_dig", "revive", "revive_egg", "unturn_dead", "unturn_you", "cancel_item", "blank_novel", "drain_item", "obj_resists", "obj_shudders", "polyuse", "create_polymon", "do_osshock", "obj_unpolyable", "poly_obj", "stone_to_flesh_obj", "bhito", "bhitpile", "zappable", "do_enlightenment_effect", "zapnodir", "backfire", "zap_ok", "dozap", "boxlock_invent", "zapyourself", "ubreatheu", "lightdamage", "flashburn", "zap_steed", "cancel_monst", "zap_updown", "zapsetup", "zapwrapup", "weffects", "spell_damage_bonus", "spell_hit_bonus", "exclam", "hit", "miss", "skiprange", "maybe_explode_trap", "zap_map", "bhit", "boomhit", "zhitm", "zhitu", "burn_floor_objects", "bounce_dir", "zap_hit", "disintegrate_mon", "ubuzz", "buzz", "dobuzz", "melt_ice", "start_melt_ice_timeout", "melt_ice_away", "zap_over_floor", "mon_spell_hits_spot", "fracture_rock", "break_statue", "destroyable", "adtyp_to_prop", "u_adtyp_resistance_obj", "inventory_resistance_check", "item_what", "maybe_destroy_item", "destroy_items", "resist", "wishcmdassist", "wish_history_add", "wish_history_flush", "wish_history_menu", "makewish", "flash_str"];
assert.equal(source,prepared,'Original ZAP source remains byte-identical');
const mask=s=>s.replace(/\/\*[\s\S]*?\*\/|\/\/[^\n]*|"(?:\\.|[^"\\])*"|'(?:\\.|[^'\\])*'/g,v=>v.replace(/[^\n]/g,' '));
const comments=s=>s.match(/\/\*[\s\S]*?\*\//g)??[];
const original=comments(source),translated=comments(js);assert.equal(original.length,782);let cursor=0;
for(const c of original){const next=translated.indexOf(c,cursor);assert.notEqual(next,-1,'Original ordered comment '+c.slice(0,70));cursor=next+1;}
const c=mask(source),j=mask(js);
// Anchored real source declarations avoid the conservative shared parser's
// twelve `case (AD_x-1): if (...) {` false definitions after preprocessing.
assert.deepEqual([...c.matchAll(/^(\w+)\([^;{}]*\)\s*\{/gm)].map(m=>m[1]),expected);
assert.deepEqual([...j.matchAll(/export function (\w+)\(/g)].map(m=>m[1]),expected);
function params(s){let depth=0,at=0;const out=[];for(let i=0;i<=s.length;i++){const ch=s[i]??',';depth+=(ch==='(')-(ch===')');if(ch===','&&!depth){const p=s.slice(at,i).trim();if(p&&p!=='void')out.push(p.match(/\(\*(\w+)\)/)?.[1]??p.replace(/\bUNUSED\b/g,'').trim().match(/\w+$/)[0]);at=i+1;}}return out;}
for(const name of expected){const a=c.match(new RegExp('^'+name+'\\(([^;{}]*)\\)\\s*\\{','m'));assert.ok(a,name);const b=js.match(new RegExp('export function '+name+'\\(([^)]*)\\)'));assert.deepEqual(b[1].split(',').map(x=>x.trim()).filter(Boolean),params(a[1]),name+' original parameters');}
function data(name){const m=source.match(new RegExp('\\b'+name+'(?:\\[[^\\]]*\\])+\\s*=\\s*\\{'));assert.ok(m,name);const a=source.indexOf('{',m.index);let d=1,i=a+1;while(d){d+=(c[i]==='{')-(c[i]==='}');i++;}return source.slice(a+1,i-1);}
const strings=s=>[...s.matchAll(/"(?:\\.|[^"\\])*"/g)].map(m=>JSON.parse(m[0]));
assert.deepEqual(core.flash_types,strings(data('flash_types')));assert.equal(core.flash_types.length,30);
assert.deepEqual(core.destroy_strings.flat(),strings(data('destroy_strings')));assert.equal(core.destroy_strings.length,7);assert.ok(core.destroy_strings.every(row=>row.length===3));
assert.deepEqual(core.charged_objs,['WAND_CLASS','WEAPON_CLASS','ARMOR_CLASS',0]);
assert.equal((c.match(/\bgoto\s+\w+;/g)??[]).length,11);assert.ok(!/\bgoto\s+\w+;/.test(j));
assert.equal((j.match(/C\.__assert_fail\(/g)??[]).length,1);assert.equal((j.match(/C\.nh_snprintf\(/g)??[]).length,1);
const support=fs.readFileSync('nethack-c/wasm/tu-zap-support.inc','utf8');
assert.ok(!/\b(?:for|while)\s*\(/.test(mask(support)),'Native support contains only typed ABI, no policy loops');
for(const name of expected)assert.ok(!new RegExp('\\b'+name+'\\s*\\([^;{}]*\\)\\s*\\{').test(mask(support)),name+' body absent native support');
const storage=fs.readFileSync('nethack-c/wasm/tu-zap-storage.c','utf8');assert.match(storage,/const char \*const destroy_strings\[7\]\[3\];/);assert.ok(!/destroy_strings[^;]*=/.test(storage),'External table native storage zero-only');
assert.match(js,/const items_to_destroy = C\.localRecordArray\(/,'Unobserved local descriptor rows remain JS');
// The few foreign helper bodies retained in this isolated fixture are copied
// from their actual prepared sources, not substitute gameplay algorithms.
const fixture=fs.readFileSync('scripts/tu-zap-probe.c','utf8');
function body(text,name){const masked=mask(text),m=masked.match(new RegExp('^'+name+'\\([^;{}]*\\)\\s*\\{','m'));assert.ok(m,name);const start=masked.indexOf('{',m.index);let i=start+1,depth=1;while(depth){depth+=(masked[i]==='{')-(masked[i]==='}');i++;}return mask(text.slice(start,i)).replace(/\s/g,'');}
for(const [file,names]of [['cmd',['isok']],['worn',['bypass_obj','bypass_objlist','nxt_unbypassed_obj']]]){
 const native=fs.readFileSync('.cache/wasm64-build/tree/src/'+file+'.c','utf8');for(const name of names)assert.equal(body(fixture,name),body(native,name),name+' actual original dependency body');
}
const library=fs.readFileSync('nethack-c/wasm/tu-libraries/zap.js','utf8');
assert.match(library,/\$teleportZapInit__deps:\['\$teleportZapServices','\$addOnInit'\]/);
assert.match(library,/teleport_zap_callback_zap_ok:function/);
assert.match(fs.readFileSync('scripts/tu-zap-consumer.c','utf8'),/return destroy_strings\[dindx\]\[\(obj->quan > 1L\)\];/);
console.log('ZAP: 85 original boundaries/parameters, 782 ordered comments, 30 flash/7x3 destruction/4 classifier data,11 inline jumps and typed-only zero storage pass.');
