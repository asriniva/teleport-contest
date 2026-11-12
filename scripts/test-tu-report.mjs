import './pure-js-probes/deny-wasm.mjs';
import {createProbe,createReference,loadFixture,fixtureImports} from './pure-js-fixtures/load.mjs';
import {DataView as FixtureDataView} from './native-test-backend.mjs';
// REPORT first-pass differential: actual prepared C and JS through memory64 ABI.
// Both modules use the production native ABI header. Native libc stacktrace
// branches require a separate oracle pass; this suite makes no native claim.
import assert from './native-test-assert.mjs';
import { pathToFileURL } from 'node:url';
import { resolve } from 'node:path';
import { createReportBridge } from '../js/nethack/bindings/report.js';
import { C } from '../js/c-runtime/context.js';
const probeDir = resolve(process.env.TELEPORT_REPORT_PROBE_DIR ?? '.cache/tu-probes');
const { default: referenceFactory } = await loadFixture("report",pathToFileURL(resolve(probeDir, 'report-reference.mjs')));
const { default: hybridFactory } = await loadFixture("report",pathToFileURL(resolve(probeDir, 'report-hybrid.mjs')));
let comparisons = 0;
function text(m, at) {
    if (!at) return null;
    at = Number(at); let end = at;
    while (m.HEAPU8[end]) end++;
    return Buffer.from(m.HEAPU8.subarray(at, end)).toString();
}
function put(m, value) {
    if (value === null) return 0n;
    const bytes = typeof value === 'string' ? Buffer.from(value) : value;
    const at = BigInt(m._malloc(BigInt(bytes.length + 1)));
    m.HEAPU8.set(bytes, Number(at));m.HEAPU8[Number(at) + bytes.length] = 0;
    return at;
}
function layout(m) {
    const result = {};
    for (let i = 0; i < m._probe_layout_count(); i++)
        result[text(m, m._probe_layout_name(i))] = Number(m._probe_layout_value(i));
    result.strings = { CRASHREPORT: text(m, m._probe_crashreport()), DEVTEAM_URL: text(m, m._probe_devteam()) };
    return result;
}
const firstReference = await referenceFactory();
const reportLayout = layout(firstReference);
async function pair() {
    const r = await referenceFactory();
    const h = await hybridFactory({ nethackPorted: { report: createReportBridge(reportLayout) } });
    assert.deepEqual(layout(h), reportLayout);comparisons++;
    r._probe_reset();h._probe_reset();return [r,h];
}
function check(modules, name, ...args) {
    const stacks = modules.map(m => m._probe_stack());
    const values = modules.map(m => m['_probe_' + name](...args));
    assert.equal(values[1], values[0], name);
    assert.equal(text(modules[1], modules[1]._probe_trace()), text(modules[0], modules[0]._probe_trace()), name+' trace');
    modules.forEach((m,i) => assert.equal(m._probe_stack(), stacks[i], name+' stack'));
    assert.equal(C, undefined);comparisons++;
    return values[0];
}
const modules = await pair();
check(modules,'libc');check(modules,'gdb');check(modules,'bidshow');
check(modules,'handler');
for (const set of [0,1,2,255,256,-1]) check(modules,'signals',set);
// Direct buffers and the pointer/int out-parameters are compared as bytes,
// retaining guards and overflow rollback rather than only decoded strings.
for (const input of ['', 'abcXYZ019_-~.', 'a b c', '?&=#\n\t%', 'a?b', Buffer.from([0x80,0xff,0xc3,0xa9]), 'A'.repeat(100)])
for (const remaining of [0,1,2,3,4,5,8,16,64,128])
for (const mark of [false,true]) {
    const results = modules.map(m => {
        const source = put(m,input), buffer = BigInt(m._malloc(512n)), out = BigInt(m._malloc(8n)), left = BigInt(m._malloc(4n));
        m.HEAPU8.fill(0xa5,Number(buffer),Number(buffer)+512);
        new FixtureDataView(m.HEAPU8.buffer).setBigUint64(Number(out), buffer+32n,true);
        new FixtureDataView(m.HEAPU8.buffer).setInt32(Number(left),remaining,true);
        const stack = m._probe_stack();
        const rv = m._probe_encode(source,out,left,mark?buffer+16n:0n);
        assert.equal(m._probe_stack(),stack);
        const result = {rv, offset:new FixtureDataView(m.HEAPU8.buffer).getBigUint64(Number(out),true)-buffer,
            left:new FixtureDataView(m.HEAPU8.buffer).getInt32(Number(left),true),
            bytes:Buffer.from(m.HEAPU8.slice(Number(buffer),Number(buffer)+512))};
        [source,buffer,out,left].forEach(p=>m._free(p));return result;
    });
    assert.deepEqual(results[1],results[0],`encode ${input}/${remaining}/${mark}`);comparisons++;
}
for (const index of [0,1,3,49,50,51,0xffffffff]) {
    modules.forEach(m=>{
        m._probe_reset();m._probe_index(index);
        for (const slot of [0,2,4,45,48,49]) m._probe_message(slot,put(m,'line'+slot));
    });
    for (const lineno of [0,1,2,3,4,5,49,50,100]) {
        const result=modules.map(m=>text(m,m._probe_saved(lineno)));
        assert.equal(result[1],result[0],`saved ${index}/${lineno}`);comparisons++;
    }
}
// Initialization fixtures exercise failure, chunk boundaries, full MD4 hex,
// and the static once guard with the original C hash provider in both modules.
for (const [readlink,open,read,size] of [[-1,0,0,0],[0,-1,0,0],[0,0,-1,0],...[0,1,63,64,65,4095,4096,4097,9000].map(n=>[0,0,0,n])]) {
    const mods=await pair();
    mods.forEach(m=>{[readlink,open,read,size].forEach((value,i)=>m._probe_option(i,value));});
    check(mods,'init');check(mods,'bidshow');check(mods,'init');check(mods,'bidshow');
}
for (const maximum of [-1,0,1,20,60,120,250,8192,9000])
for (const cos of [1,2]) {
    const mods=await pair();
    mods.forEach(m=>{
        m._probe_config(put(m,'https://fixture.invalid/report'),put(m,'Name & Me'),put(m,'a+b@example.invalid'),maximum);
        m._probe_message(0,put(m,'most recent'));m._probe_index(1);
    });
    for (const status of [0,1,256]) {
        mods.forEach(m=>m._probe_option(5,status));
        // The original URL cursor persists across submissions. Test that
        // behavior without entering a real browser or operating-system fork.
        check(mods,'submit',cos,0n,0n);
    }
}
for (const haveURL of [false,true]) {
    const mods=await pair();
    mods.forEach(m=>m._probe_config(haveURL?put(m,''):0n,0n,0n,-1));
    check(mods,'bug');
}
// Child branch uses a controlled JS exception at exit(1); all preceding URL,
// execve argv, errno diagnostic, and trace bytes must match the real C path.
for (const maximum of [-1,0,1,10,30,31,60,100,200,8192])
for (const [cos,msg,why] of [[1,'panic','bad #thing\nnext'],[2,null,'#bugreport command'],[2,'x'.repeat(80),null]]) {
    const mods=await pair();
    const values=mods.map(m=>{
        m._probe_config(put(m,'https://fixture.invalid/report'),put(m,'Néthack'),put(m,'a+b@example.invalid'),maximum);
        m._probe_option(4,0);m._probe_message(0,put(m,'saved + message'));m._probe_index(1);
        assert.throws(()=>m._probe_submit(cos,put(m,msg),put(m,why)),/REPORT fixture exit 1/);
        return {trace:text(m,m._probe_trace()),url:text(m,m._probe_output())};
    });
    assert.deepEqual(values[1],values[0]);assert.equal(C,undefined);comparisons++;
}
console.log(`REPORT: ${comparisons} prepared original-C/pure-JS comparisons passed; native platform branches pending.`);
