// Build/test guard for the configured original WIZCMDS translation unit.
import { readFileSync } from 'node:fs';
import { resolve } from 'node:path';
import { createHash } from 'node:crypto';
import { spawnSync } from 'node:child_process';
const sha=bytes=>createHash('sha256').update(bytes).digest('hex');
export function checkWizcmdsSource(root=process.cwd(),{preprocess=true}={}) {
    const read=path=>readFileSync(resolve(root,path),'utf8');
    const expected='4611d620caedc59dc270f5d6b6f9a2497831dc88325edc90f3770e75afd9b71f';
    const original=read('nethack-c/upstream/src/wizcmds.c');
    for(const [name,source] of [['upstream',original],['prepared',read('.cache/wasm64-build/tree/src/wizcmds.c')]])
        if(sha(source)!==expected)throw Error('Review changed WIZCMDS '+name+' source');
    const core=read('js/ported/wizcmds.js');
    const schema=JSON.parse(read('nethack-c/wasm/tu-fragments/wizcmds-schema.json'));
    if(schema.preparedSha256!==expected)throw Error('Review changed WIZCMDS ABI source binding');
    const names=[...original.matchAll(/^(\w+)\([^;]*?\)\s*(?:\/\*[\s\S]*?\*\/\s*)?\{/gm)].map(m=>m[1]);
    const functions=[...core.matchAll(/^export function (\w+)\(([^)]*)\)/gm)];
    if(names.length!==48||functions.map(m=>m[1]).join(',')!==names.join(','))
        throw Error('Review changed WIZCMDS function set/order');
    for(const m of functions) {
        const signature=new RegExp('^'+m[1]+'\\(([^)]*)\\)','m').exec(original)[1].replace(/\/\*[\s\S]*?\*\//g,'');
        const params=signature.trim()==='void'?[]:signature.split(',').map(s=>/\b(\w+)\s*$/.exec(s.trim())[1]);
        if(m[2].replaceAll(' ','')!==params.join(','))throw Error('Review changed WIZCMDS formal bindings '+m[1]);
    }
    const comments=original.match(/\/\*[\s\S]*?\*\//g)??[];
    for(const comment of comments)if(!core.includes(comment))throw Error('Missing original WIZCMDS comment '+comment.slice(0,80));
    if(preprocess) {
        const defines=JSON.parse(read('nethack-c/wasm/compile-defines.json'));
        const base=['-sMEMORY64=1',...defines.map(x=>'-D'+x),'-I'+resolve(root,'.cache/wasm64-build/tree/include'),'-I'+resolve(root,'.cache/ncurses-wasm64-build/include')];
        const run=args=>{const result=spawnSync(resolve(root,'.cache/emsdk/upstream/emscripten/emcc'),[...base,...args,'wizcmds.c'],{cwd:resolve(root,'.cache/wasm64-build/tree/src'),encoding:'utf8',maxBuffer:32*1024*1024});if(result.status!==0)throw Error('WIZCMDS configured preprocessing failed: '+result.stderr);return result.stdout;};
        const macros=new Map([...run(['-E','-dM']).matchAll(/^#define (\w+)(\([^\n ]*\))? ?(.*)$/gm)].map(m=>[m[1],{params:m[2]??null,body:m[3]}]));
        if(!macros.has('DEBUG')||!macros.has('ENHANCED_SYMBOLS')||!macros.has('DEBUG_MIGRATING_MONS'))throw Error('Review changed WIZCMDS configured branches');
        if(!schema.headerMacros)throw Error('WIZCMDS ABI lacks configured macro provenance');
        const manualMacros={"FEATURE_NOTICE_VER":{"params":"(major,minor,patch)","body":"(((unsigned long) major << 24) | ((unsigned long) minor << 16) | ((unsigned long) patch << 8) | ((unsigned long) 0))"},"SIZE":{"params":"(x)","body":"(int)(sizeof(x) / sizeof(x[0]))"},"Snprintf":{"params":"(str,size,...)","body":"nh_snprintf(__func__, __LINE__, str, size, __VA_ARGS__)"},"Sprintf":{"params":null,"body":"(void) sprintf"},"Strcat":{"params":null,"body":"(void) strcat"},"Strcpy":{"params":null,"body":"(void) strcpy"},"WINDOWPORT":{"params":"(wn)","body":"(windowprocs.wp_id == wp_##wn)"},"distu":{"params":"(xx,yy)","body":"dist2((coordxy) (xx), (coordxy) (yy), u.ux, u.uy)"},"notice_mon_off":{"params":"()","body":"do { a11y.mon_notices_blocked++; } while(0)"},"notice_mon_on":{"params":"()","body":"do { if (--a11y.mon_notices_blocked < 0) { impossible(\"mon_notices_blocked<0\"); a11y.mon_notices_blocked = 0; } } while(0)"},"rn2":{"params":"(x)","body":"(rng_log_enabled() ? (rng_log_set_caller(__FILE__, __LINE__, __func__), rn2(x)) : rn2(x))"}};
        for(const [name,expected]of Object.entries(manualMacros)) {
            const actual=macros.get(name);
            if(actual?.body!==expected.body||actual.params!==expected.params)throw Error('Review changed WIZCMDS ABI/header macro '+name);
        }
        for(const [name,m] of Object.entries(schema.headerMacros)) {
            const actual=macros.get(name);
            if(actual?.body!==m.original||actual.params!==(m.params===null?null:'('+m.params.join(',')+')'))throw Error('Review changed WIZCMDS header macro '+name);
        }
        const cpp=run(['-E']);
        if(!cpp.includes('rng_log_set_caller("wizcmds.c", 1036, __func__)'))throw Error('Review changed WIZCMDS production RNG filename/line');
        for(const [fn,line]of [['wiz_mon_diff',1819],['wiz_objprobs',1861],['wizcustom_callback',2021]])
            if(!core.includes("C.nh_snprintf('"+fn+"', "+line+',')||!cpp.includes('nh_snprintf(__func__, '+line+','))throw Error('Review changed WIZCMDS diagnostic source context '+fn);
    }
    return {functions:48,staticFunctions:schema.functions.filter(f=>f.static).length,originalComments:comments.length,records:Object.keys(schema.schema).length,fields:Object.values(schema.schema).reduce((n,s)=>n+s.fields.length,0),globals:schema.globals.length,variadicShapes:Object.keys(schema.variadicABI).length,headerMacros:Object.keys(schema.headerMacros??{}).length,manualHeaderMacros:11,sourceSha256:expected};
}
