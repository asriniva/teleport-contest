import assert from 'node:assert/strict';
import fs from 'node:fs';
import { fileURLToPath, pathToFileURL } from 'node:url';
const root = fileURLToPath(new URL('../', import.meta.url));
const fields = {
    mkobj: [],
    eat: [],
    objnam: [],
    read: [],
    apply: [],
    insight: [],
    makemon: [],
    mhitu: [],
    artifact: [],
    decl: [],
    pray: [],
    dothrow: [],
    pager: [],
    muse: [],
    dungeon: [],
    potion: [],
    timeout: [],
    spell: [],
    monmove: [],
    detect: [],
    teleport: [],
    mklev: [],
    polyself: [],
    wizcmds: [],
    end: [],
    dig: [],
    dokick: [],
    mkmaze: [],
    vision: [],
    do: [],
    do_wear: [],
    restore: [],
    nhlobj: [],
    do_name: [],
    windows: [],
    cfgfiles: [],
    topten: [],
    dogmove: [],
    glyphs: [],
    engrave: [],
    role: [],
    mthrowu: [],
    mhitm: [],
    getpos: [],
    allmain: [],
    save: [],
    sounds: [],
    vault: [],
    u_init: [],
    weapon: [],
    region: [],
    dog: [],
    sfbase: [],
    attrib: [],
    pline: [],
    mail: [],
    questpgr: [],
    symbols: [],
    bones: [],
    explode: [],
    earlyarg: [],
    report: [],
    mkroom: [],
    sfstruct: [],
    wield: [],
    worn: [],
    hacklib: [],
    mondata: [],
    dbridge: [],
    mcastu: [],
    ball: [],
    o_init: [],
    worm: [],
    wizard: [],
    steed: [],
    lock: [],
    light: [],
    priest: [],
    coloratt: [],
    version: [],
    music: [],
    rumors: [],
    shknam: [],
    monst: [],
    objects: [],
    fountain: [],
    sit: [],
    steal: [],
    selvar: [],
    iactions: [],
    minion: [],
    quest: [],
    mdlib: [],
    write: [],
    getline: [],
    mkmap: [],
    exper: [],
    mplayer: [],
    extralev: [],
    were: [],
    unixtty: [],
    ioctl: [],
    rnd: [],
    posixregex: [],
    drawing: [],
    utf8map: [],
    alloc: [],
    date: [],
    rip: [],
    sys: [],
    isaac64: ['n', 'r', 'm', 'a', 'b', 'c'],
    nhmd4: ['lo', 'hi', 'a', 'b', 'c', 'd', 'buffer', 'block'],
    strutil: ['len', 'str', 'buf'],
    rect: ['lx', 'ly', 'hx', 'hy'],
    track: ['utcnt', 'utpnt', 'utrack', 'x', 'y', 'ux', 'uy', 'otyp'],
    calendar: ['tm_year', 'tm_mon', 'tm_mday', 'tm_hour', 'tm_min', 'tm_sec', 'tm_wday', 'tm_yday'],
    stairs: ['sx', 'sy', 'tolev', 'up', 'isladder', 'u_traversed', 'next', 'dnum', 'dlevel', 'uz'],
};
const layouts = {};
// Bootstrap data imports from actual C probes before importing the JS runtime.
// Native terminal/regex ABI layouts then come from their configured hybrids.
const ports = JSON.parse(fs.readFileSync(root + 'nethack-c/wasm/tu-ports.json'));
for (const pass of ['reference', 'hybrid']) {
const createPortedRuntime = pass === 'hybrid'
    ? (await import('../js/ported/wasm-runtime.js')).createPortedRuntime : null;
for (const port of ports) {
    const {name} = port;
    if (pass === 'hybrid' && !['ioctl','unixtty','posixregex'].includes(name)) continue;
    const variant = pass;
    const createProbe = (await import(pathToFileURL(root + `.cache/tu-probes/${name}-${variant}.mjs`))).default;
    const probe = await createProbe(variant==='hybrid'?{nethackPorted:createPortedRuntime(
        JSON.parse(fs.readFileSync(root+'js/wasm/tu-layouts.json')))}:{});
    const layout = port.probeContext === false ? {} : { size: Number(probe._probe_context_size()) };
    for (const field of fields[name]) layout[field] = Number(probe['_probe_offset_' + field]());
    if (name === 'strutil') {
        layout.bufSize = Number(probe._probe_buffer_size());
        layout.largestInt = probe._probe_largest_int();
    }
    if (name === 'rect') {
        layout.coordSize = probe._probe_coord_size();
        layout.COLNO = probe._probe_colno();
        layout.ROWNO = probe._probe_rowno();
    }
    if (name === 'track') {
        for (const [field, query] of Object.entries({ coordSize: 'coord_size', coordxySize: 'coordxy_size', intSize: 'int_size', otypSize: 'otyp_size', UTSZ: 'utsz', RIN_STEALTH: 'stealth', WRITING: 'writing', FREEING: 'freeing', COUNTING: 'counting' })) {
            layout[field] = probe['_probe_' + query]();
        }
    }
    if (name === 'calendar') {
        layout.fields = {};
        for (const field of fields[name]) { layout.fields[field] = layout[field]; delete layout[field]; }
        layout.intSize = probe._probe_int_size();
        layout.longSize = probe._probe_long_size();
        layout.timeSize = probe._probe_time_size();
    }
    if (name === 'stairs') {
        for (const [field, query] of Object.entries({ coordxySize: 'coordxy_size', boolSize: 'bool_size', boolSigned: 'bool_signed', levelSize: 'level_size', levelFieldSize: 'level_field_size' })) {
            layout[field] = probe['_probe_' + query]();
        }
    }
    if (name === 'sys') {
        const text = pointer => {
            if (!pointer) return null;
            let end = Number(pointer);
            while (probe.HEAPU8[end]) end++;
            return new TextDecoder().decode(probe.HEAPU8.subarray(Number(pointer), end));
        };
        layout.intSize = probe._probe_int_size();
        for (const prefix of ['', 'gc_']) {
            const table = {};
            for (let i = 0; i < probe['_probe_' + prefix + 'field_count'](); i++) {
                table[text(probe['_probe_' + prefix + 'field_name'](i))] = {
                    offset: Number(probe['_probe_' + prefix + 'field_offset'](i)),
                    size: Number(probe['_probe_' + prefix + 'field_size'](i)),
                    kind: prefix ? 'pointer' : ['pointer', 'int', 'long', 'array'][probe._probe_field_kind(i)],
                };
            }
            layout[prefix ? 'gcFields' : 'fields'] = table;
        }
        layout.constants = {};
        for (let i = 0; i < probe._probe_config_count(); i++)
            layout.constants[text(probe._probe_config_name(i))] = probe._probe_config_value(i);
        layout.constants.LL_NONE = String(probe._probe_ll_none());
        layout.strings = {};
        for (let i = 0; i < probe._probe_string_count(); i++)
            layout.strings[text(probe._probe_string_name(i))] = text(probe._probe_string_value(i));
    }
    if (name === 'rip') {
        layout.pointerSize = layout.size;
        layout.BUFSZ = probe._probe_bufsz();
        layout.DUMPLOG = probe._probe_dumplog();
        layout.NH320_DEDICATION = probe._probe_dedication();
    }
    if (name === 'date') {
        const text = pointer => {
            if (!pointer) return null;
            let end = Number(pointer);
            while (probe.HEAPU8[end]) end++;
            return new TextDecoder().decode(probe.HEAPU8.subarray(Number(pointer), end));
        };
        layout.fields = {};
        for (let i = 0; i < probe._probe_field_count(); i++) {
            layout.fields[text(probe._probe_field_name(i))] = {
                offset: Number(probe._probe_field_offset(i)),
                size: Number(probe._probe_field_size(i)),
                kind: ['pointer', 'ulong'][probe._probe_field_kind(i)],
            };
        }
        layout.versionFields = {};
        for (const field of ['incarnation', 'feature_set', 'entity_count'])
            layout.versionFields[field] = { offset: Number(probe['_probe_offset_' + field]()), size: probe._probe_long_size(), kind: 'ulong' };
        layout.BUFSZ = probe._probe_bufsz();
        layout.strings = { BUILD_DATE_TIME: text(probe._probe_build_date_time()) };
        for (const field of ['sha', 'branch', 'prefix'])
            layout.strings['NETHACK_GIT_' + field.toUpperCase()] = text(probe['_probe_git_' + field]());
    }
    if (name === 'alloc') {
        layout.LONG_SIZE = probe._probe_long_size();
        layout.PTRBUFCNT = probe._probe_ptrbuf_count();
        layout.PTRBUFSIZ = probe._probe_ptrbuf_size();
        layout.PTR_FMT = probe._probe_has_ptr_fmt() ? '%p' : '%06lx';
        if (probe._probe_monitor_heap()) throw new Error('MONITOR_HEAP alloc port is not implemented');
        if (probe._probe_int_size() !== 4 || probe._probe_lua_integer_size() !== 8 || probe._probe_ull_size() !== 8)
            throw new Error('Review changed allocation integer widths');
    }
    if (name === 'insight') {
        for (let i=0;i<probe._probe_layout_count();i++) {
            let at=Number(probe._probe_layout_name(i)),end=at;while(probe.HEAPU8[end])end++;
            const key=new TextDecoder().decode(probe.HEAPU8.subarray(at,end));
            const value=probe._probe_layout_value(i);
            layout[key]=/^(M1_|M2_|W_|LL_|STRAT_|I_SPECIAL$|TIMEOUT$|INTRINSIC$|FROMOUTSIDE$|FROMFORM$)/.test(key)
                ? String(BigInt.asUintN(64,value)) : Number(BigInt.asIntN(64,value));
        }
    }
    if (['read','apply'].includes(name)) {
        for(let i=0;i<probe._probe_layout_count();i++) {
            let at=Number(probe._probe_layout_name(i)),end=at;while(probe.HEAPU8[end])end++;
            const key=new TextDecoder().decode(probe.HEAPU8.subarray(at,end));
            const value=BigInt.asIntN(64,probe._probe_layout_value(i));
            if(BigInt(Number(value))!==value)throw new Error(name+': inexact layout '+key);
            layout[key]=Number(value);
        }
    }
    if (['eat','objnam'].includes(name)) {
        const raw={};
        for(let i=0;i<probe._probe_layout_count();i++) {
            let at=Number(probe._probe_layout_name(i)),end=at;while(probe.HEAPU8[end])end++;
            raw[new TextDecoder().decode(probe.HEAPU8.subarray(at,end))]=probe._probe_layout_value(i);
        }
        for(const [key,value] of Object.entries(raw)) {
            const wide=name==='eat'?/^(M1_|M2_|W_)/.test(key):raw['constwidth_'+key]===8n;
            layout[key]=wide?String(name==='eat'||!raw['constsigned_'+key]?BigInt.asUintN(64,value):BigInt.asIntN(64,value)):Number(BigInt.asIntN(64,value));
        }
    }
    if (name==='mkobj') {
        for(let i=0;i<probe._probe_layout_count();i++) {
            let at=Number(probe._probe_layout_name(i)),end=at;while(probe.HEAPU8[end])end++;
            const key=new TextDecoder().decode(probe.HEAPU8.subarray(at,end));
            const value=BigInt.asIntN(64,probe._probe_layout_value(i));
            if(BigInt(Number(value))!==value)throw new Error('mkobj: inexact metadata '+key);
            layout[key]=Number(value);
        }
    }
    // DECL exposes the exact production metadata names, not probe aliases.
    if (name === 'decl') {
        for(let i=0;i<probe._teleport_decl_layout_count();i++) {
            let at=Number(probe._teleport_decl_layout_name(i)),end=at;while(probe.HEAPU8[end])end++;
            layout[new TextDecoder().decode(probe.HEAPU8.subarray(at,end))]=String(probe._teleport_decl_layout_value(i));
        }
    }
    // Native long-long MAKEMON rows; avoid rounding any future wide constant.
    if (name === 'makemon') {
        for (let i=0;i<probe._probe_layout_count();i++) {
            let at=Number(probe._probe_layout_name(i)),end=at;while(probe.HEAPU8[end])end++;
            const key=new TextDecoder().decode(probe.HEAPU8.subarray(at,end));
            const value=probe._probe_layout_value(i);
            layout[key]=value>=-BigInt(Number.MAX_SAFE_INTEGER)&&value<=BigInt(Number.MAX_SAFE_INTEGER)?Number(value):String(value);
        }
    }
    // Keep exact raw64 bits. ARTIFACT decodes signedness; frozen MHITU
    // width8 constants are separately verified nonnegative/Numberexact.
    if (['mhitu','artifact'].includes(name)) {
        const raw={};
        for(let i=0;i<probe._probe_layout_count();i++) {
            let at=Number(probe._probe_layout_name(i)),end=at;while(probe.HEAPU8[end])end++;
            raw[new TextDecoder().decode(probe.HEAPU8.subarray(at,end))]=probe._probe_layout_value(i);
        }
        for(const [key,value]of Object.entries(raw))
            layout[key]=raw['constwidth_'+key]===8n?String(value):Number(BigInt.asIntN(64,value));
    }
    if (['polyself','wizcmds'].includes(name)) {
        const raw = {};
        for (let i=0;i<probe._probe_layout_count();i++) {
            let at=Number(probe._probe_layout_name(i)),end=at;while(probe.HEAPU8[end])end++;
            raw[new TextDecoder().decode(probe.HEAPU8.subarray(at,end))]=probe._probe_layout_value(i);
        }
        for (const [key,value] of Object.entries(raw))
            layout[key]=raw['constwidth_'+key]===8n ? String(BigInt.asIntN(64,value)) : Number(BigInt.asIntN(64,value));
    }
    if (["do", "spell", "detect", "teleport", "end", "dig", "dokick", "vision", "restore", "nhlobj", "do_name", "windows", "cfgfiles", "topten", "dogmove", "glyphs", "engrave", "role", "mthrowu", "mhitm", "getpos", "allmain", "save", "sounds", "vault", "u_init", "weapon", "region", "dog", "sfbase", "attrib", "pline", "mail", "questpgr", "symbols", "bones", "explode", "earlyarg", "report", "mkroom", "sfstruct", "utf8map", "drawing", "posixregex", "rnd", "ioctl", "unixtty", "were", "extralev", "mplayer", "exper", "mkmap", "getline", "write", "mdlib", "quest", "minion", "iactions", "selvar", "steal", "sit", "fountain", "objects", "monst", "shknam", "rumors", "music", "version", "coloratt", "priest", "light", "lock", "steed", "wizard", "worm", "o_init", "ball", "mcastu", "dbridge", "mondata", "hacklib", "worn", "wield", "monmove", "timeout", "potion", "pray", "pager", "muse", "do_wear"].includes(name)) {
        for (let i = 0; i < probe._probe_layout_count(); i++) {
            let pointer = Number(probe._probe_layout_name(i)), end = pointer;
            while (probe.HEAPU8[end]) end++;
            const key = new TextDecoder().decode(probe.HEAPU8.subarray(pointer, end));
            layout[key] = (name === 'potion' && !/^(M1_|M2_|W_)/.test(key)) || (name === 'timeout' && !/^(M1_|M2_|W_|TIMEOUT$|I_SPECIAL$|FROMOUTSIDE$|INTRINSIC$)/.test(key)) || (name === 'spell' && !/^(M1_|M2_|TIMEOUT$|LL_)/.test(key)) || (name === 'monmove' && !(/^(M1_|M2_|STRAT_|ALLOW_)/.test(key) || key === 'NOTONL')) || ["detect", "teleport", "pray", "pager", "muse"].includes(name) || (name === 'dig' && !(/^(W_|M1_|M2_)/.test(key) || ['LEFT_SIDE','RIGHT_SIDE'].includes(key))) || (name === 'dokick' && !/^(W_|M1_|M2_|DF_)/.test(key)) || ['do_wear','do','end','restore','vision'].includes(name) || (name === 'nhlobj' && ['NON_PM','LUA_REGISTRYINDEX'].includes(key)) || (name === 'do_name' && ['NON_PM','GETOBJ_EXCLUDE'].includes(key)) || ['windows','cfgfiles'].includes(name) || name === 'dogmove' || (name === 'save' && key !== 'SIG_IGN') || (name === 'role' && ['ROLE_NONE','ROLE_RANDOM','NON_PM','WIN_ERR','A_NONE','A_CHAOTIC'].includes(key)) || name === 'mthrowu' || (name === 'mhitm' && key === 'NON_PM') || (name === 'minion' && ['NON_PM', 'A_CHAOTIC', 'A_NONE'].includes(key)) || (name === 'iactions' && key === 'GETOBJ_EXCLUDE') || (name === 'selvar' && key === 'W_RANDOM') || (name === 'fountain' && key === 'A_CHAOTIC') || (name === 'monst' && ['NON_PM', 'A_NONE'].includes(key)) || (name === 'shknam' && ['NON_PM', 'HEALTHY_TIN', 'ALL_TRAPS'].includes(key)) || (name === 'rumors' && key === 'WIN_ERR') || (name === 'music' && key === 'A_NONE') || (name === 'version' && key === 'WIN_ERR') || (name === 'priest' && ['A_CHAOTIC', 'A_NONE', 'ALL_TRAPS', 'SPBOOK_no_NOVEL'].includes(key)) || (name === 'light' && key === 'WIN_ERR') || (name === 'steed' && ['DIR_ERR', 'P_ISRESTRICTED'].includes(key)) || (name === 'worm' && key === 'NON_PM') || (name === 'o_init' && ['WIN_ERR', 'NON_PM'].includes(key)) || (name === 'ball' && key === 'override_restriction') || (name === 'mondata' && ['AD_ANY', 'AT_ANY', 'NON_PM', 'ALL_TRAPS'].includes(key)) || (name === 'worn' && key === 'NON_PM') || (name === 'wield' && (key === 'NON_PM' || /^GETOBJ_/.test(key))) || (name === 'mkroom' && ['A_NONE','NON_PM','ANY_TYPE','ANY_SHOP'].includes(key)) || (name === 'questpgr' && ['NON_PM','A_CHAOTIC'].includes(key)) || (name === 'symbols' && key === 'NO_COLOR') || (name === 'dog' && key === 'NON_PM') || (name === 'region' && key === 'NO_CALLBACK')
                ? Number(BigInt.asIntN(64, probe._probe_layout_value(i)))
                : (name === 'potion' && /^(M1_|M2_|W_)/.test(key)) || (name === 'monmove' && (/^(M1_|M2_|STRAT_|ALLOW_)/.test(key) || key === 'NOTONL')) || (name === 'spell' && /^(M1_|M2_|TIMEOUT$|LL_)/.test(key)) || (name === 'timeout' && /^(M1_|M2_|W_|TIMEOUT$|I_SPECIAL$|FROMOUTSIDE$|INTRINSIC$)/.test(key)) || (name === 'engrave' && /^(M1_|M2_|LL_)/.test(key)) || (name === 'role' && /^(expr_|M2_)/.test(key)) || (name === 'mhitm' && /^(M1_|M2_|W_)/.test(key)) || (name === 'save' && key === 'SIG_IGN') || (name === 'sounds' && /^(M1_|M2_|STRAT_|W_)/.test(key)) || (name === 'dog' && /^(M1_|M2_|MON_|STRAT_|MIGR_LEFTOVERS$)/.test(key)) || (name === 'questpgr' && key === 'M2_PNAME') || (name === 'exper' && key === 'LONG_MAX') || (name === 'monst' && /^(M1_|M2_)/.test(key)) || (name === 'music' && (/^(M1_|M2_)/.test(key) || key === 'STRAT_WAITMASK')) || (name === 'priest' && /^(M1_|M2_)/.test(key)) || (name === 'lock' && /^M1_/.test(key)) || (name === 'steed' && /^(M1_|M2_)/.test(key)) || (name === 'wizard' && /^(M1_|M2_|M3_|STRAT_)/.test(key)) || (name === 'ball' && (/^W_/.test(key) || ['LEFT_SIDE', 'RIGHT_SIDE'].includes(key))) || (name === 'mcastu' && /^(M1_|M2_)/.test(key)) || (name === 'dbridge' && /^M1_/.test(key)) || (name === 'mondata' && (/^(M1_|M2_|W_)/.test(key) || key === 'INTRINSIC')) || (name === 'worn' && (/^(M1_|W_)/.test(key) || key === 'I_SPECIAL')) || (name === 'wield' && (/^(M1_|M2_|W_)/.test(key) || ['INTRINSIC', 'I_SPECIAL'].includes(key)))
                || (name === 'do_name' && /^(M1_|M2_|W_|LL_)/.test(key)) || (name === 'dokick' && /^(W_|M1_|M2_|DF_)/.test(key)) || (name === 'dig' && (/^(W_|M1_|M2_)/.test(key) || ['LEFT_SIDE','RIGHT_SIDE'].includes(key)))
                ? String(BigInt.asUintN(64, probe._probe_layout_value(i))) : Number(probe._probe_layout_value(i));
        }
    }
    if (name === 'do_name') {
        const text = pointer => {let at=Number(pointer),end=at;while(probe.HEAPU8[end])end++;return new TextDecoder().decode(probe.HEAPU8.subarray(at,end));};
        layout.strings = {};
        for(let i=0;i<probe._probe_string_count();i++)layout.strings[text(probe._probe_string_name(i))]=text(probe._probe_string_value(i));
    }
    if (name === 'engrave') {
        const text = pointer => {
            let at = Number(pointer), end = at;
            while (probe.HEAPU8[end]) end++;
            return new TextDecoder().decode(probe.HEAPU8.subarray(at, end));
        };
        for (let i = 0; i < probe._probe_string_count(); i++)
            layout[text(probe._probe_string_name(i))] = text(probe._probe_string_value(i));
    }
    if (name === 'mail') {
        const text = pointer => {
            if (!pointer) return null;
            let end = Number(pointer); while (probe.HEAPU8[end]) end++;
            return new TextDecoder().decode(probe.HEAPU8.subarray(Number(pointer), end));
        };
        layout.strings = {};
        for (let i=0; i<probe._probe_string_count(); i++)
            layout.strings[text(probe._probe_string_name(i))] = text(probe._probe_string_value(i));
    }
    if (name === 'report') {
        const text = pointer => {
            let at=Number(pointer),end=at;
            while(probe.HEAPU8[end]) end++;
            return new TextDecoder().decode(probe.HEAPU8.subarray(at,end));
        };
        layout.strings={CRASHREPORT:text(probe._probe_crashreport()),DEVTEAM_URL:text(probe._probe_devteam())};
    }
    if (['mdlib', 'rumors', 'version'].includes(name)) {
        const text = pointer => {
            if (!pointer) return null;
            let end = Number(pointer);
            while (probe.HEAPU8[end]) end++;
            return new TextDecoder().decode(probe.HEAPU8.subarray(Number(pointer), end));
        };
        layout.strings = {};
        for (let i = 0; i < probe._probe_string_count(); i++)
            layout.strings[text(probe._probe_string_name(i))] = text(probe._probe_string_value(i));
    }
    if (name === 'drawing') {
        const constants = {};
        for (let i = 0; i < probe._probe_constant_count(); i++) {
            let pointer = Number(probe._probe_constant_name(i)), end = pointer;
            while (probe.HEAPU8[end]) end++;
            const key = new TextDecoder().decode(probe.HEAPU8.subarray(pointer, end));
            constants[key] = Number(probe._probe_constant_value(i));
        }
        fs.writeFileSync(root + 'js/wasm/drawing-constants.json', JSON.stringify(constants, null, 2) + '\n');
    }
    if (name === 'ioctl') {
        for (const [field, query] of Object.entries({ SIG_DFL: 'default', SIG_IGN: 'ignore', SIG_ERR: 'error' }))
            layout[field] = String(BigInt.asUintN(64, probe['_probe_sig_' + query]()));
    }
    if (['windows','cfgfiles'].includes(name)) {
        for (const [key,value] of Object.entries(layout))
            assert(Number.isSafeInteger(value), `${name}: metadata ${key} needs lossless representation`);
    }
    if (["detect", "teleport", "dig", "dokick", "pray", "pager", "muse"].includes(name)) for (const [key,value] of Object.entries(layout))
        assert(typeof value === 'string' || Number.isSafeInteger(value), `${name}: metadata ${key} needs lossless representation`);
    layouts[name] = layout;
}
fs.writeFileSync(root + 'js/wasm/tu-layouts.json', JSON.stringify(layouts, null, 2) + '\n');
}
console.log('Clang-derived TU layouts:', JSON.stringify(layouts));

// Isolated TU fixtures can supply their own dispatchers; check the real central
// API against every static binding call before accepting a shared build.
function assertBindingMethods(source, runtime, name) {
    const calls = /Module(?:\.nethackPorted|\[['"]nethackPorted['"]\])(?:\.(\w+)|\[['"](\w+)['"]\])\s*\(/g;
    for (const call of source.matchAll(calls)) {
        const method = call[1] || call[2];
        assert.equal(typeof runtime[method], 'function', `${name}: missing nethackPorted.${method}`);
    }
}
assert.doesNotThrow(() => assertBindingMethods("Module['nethackPorted'].callRegion()", {callRegion() {}}, 'fixture'));
assert.throws(() => assertBindingMethods("Module['nethackPorted'].callRegion()", {region() {}}, 'fixture'), /missing nethackPorted.callRegion/);
const centralRuntime = (await import('../js/ported/wasm-runtime.js')).createPortedRuntime(layouts);
for (const port of ports) assertBindingMethods(fs.readFileSync(root + port.library, 'utf8'), centralRuntime, port.name);
console.log(`ABI dispatcher methods verified: ${ports.length} registered bindings.`);

// Validate required helper inputs in addition to the binding method names.
await import('./check-tu-dispatch.mjs');
