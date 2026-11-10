import fs from 'node:fs';
import { fileURLToPath, pathToFileURL } from 'node:url';
const root = fileURLToPath(new URL('../', import.meta.url));
const fields = {
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
for (const { name } of JSON.parse(fs.readFileSync(root + 'nethack-c/wasm/tu-ports.json'))) {
    const createProbe = (await import(pathToFileURL(root + `.cache/tu-probes/${name}-reference.mjs`))).default;
    const probe = await createProbe();
    const layout = { size: Number(probe._probe_context_size()) };
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
    if (['utf8map', 'drawing', 'posixregex', 'rnd', 'ioctl', 'unixtty', 'were', 'extralev', 'mplayer', 'exper', 'mkmap', 'getline', 'write', 'mdlib', 'quest', 'minion', 'iactions', 'selvar', 'steal', 'sit', 'fountain', 'objects', 'monst', 'shknam', 'rumors', 'music', 'version', 'coloratt', 'priest', 'light', 'lock', 'steed', 'wizard', 'worm', 'o_init', 'ball', 'mcastu', 'dbridge', 'mondata', 'hacklib'].includes(name)) {
        for (let i = 0; i < probe._probe_layout_count(); i++) {
            let pointer = Number(probe._probe_layout_name(i)), end = pointer;
            while (probe.HEAPU8[end]) end++;
            const key = new TextDecoder().decode(probe.HEAPU8.subarray(pointer, end));
            layout[key] = (name === 'minion' && ['NON_PM', 'A_CHAOTIC', 'A_NONE'].includes(key)) || (name === 'iactions' && key === 'GETOBJ_EXCLUDE') || (name === 'selvar' && key === 'W_RANDOM') || (name === 'fountain' && key === 'A_CHAOTIC') || (name === 'monst' && ['NON_PM', 'A_NONE'].includes(key)) || (name === 'shknam' && ['NON_PM', 'HEALTHY_TIN', 'ALL_TRAPS'].includes(key)) || (name === 'rumors' && key === 'WIN_ERR') || (name === 'music' && key === 'A_NONE') || (name === 'version' && key === 'WIN_ERR') || (name === 'priest' && ['A_CHAOTIC', 'A_NONE', 'ALL_TRAPS', 'SPBOOK_no_NOVEL'].includes(key)) || (name === 'light' && key === 'WIN_ERR') || (name === 'steed' && ['DIR_ERR', 'P_ISRESTRICTED'].includes(key)) || (name === 'worm' && key === 'NON_PM') || (name === 'o_init' && ['WIN_ERR', 'NON_PM'].includes(key)) || (name === 'ball' && key === 'override_restriction') || (name === 'mondata' && ['AD_ANY', 'AT_ANY', 'NON_PM', 'ALL_TRAPS'].includes(key))
                ? Number(BigInt.asIntN(64, probe._probe_layout_value(i)))
                : (name === 'exper' && key === 'LONG_MAX') || (name === 'monst' && /^(M1_|M2_)/.test(key)) || (name === 'music' && (/^(M1_|M2_)/.test(key) || key === 'STRAT_WAITMASK')) || (name === 'priest' && /^(M1_|M2_)/.test(key)) || (name === 'lock' && /^M1_/.test(key)) || (name === 'steed' && /^(M1_|M2_)/.test(key)) || (name === 'wizard' && /^(M1_|M2_|M3_|STRAT_)/.test(key)) || (name === 'ball' && (/^W_/.test(key) || ['LEFT_SIDE', 'RIGHT_SIDE'].includes(key))) || (name === 'mcastu' && /^(M1_|M2_)/.test(key)) || (name === 'dbridge' && /^M1_/.test(key)) || (name === 'mondata' && (/^(M1_|M2_|W_)/.test(key) || key === 'INTRINSIC'))
                ? String(BigInt.asUintN(64, probe._probe_layout_value(i))) : Number(probe._probe_layout_value(i));
        }
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
    layouts[name] = layout;
}
fs.writeFileSync(root + 'js/wasm/tu-layouts.json', JSON.stringify(layouts, null, 2) + '\n');
console.log('Clang-derived TU layouts:', JSON.stringify(layouts));
