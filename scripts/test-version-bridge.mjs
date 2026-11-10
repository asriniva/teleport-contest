// Exercise the real game's C -> JS version -> native -> EM_JS bridge.
import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import createNethack from '../js/wasm/nethack.mjs';
import { createPortedRuntime } from '../js/ported/wasm-runtime.js';

const layouts = JSON.parse(readFileSync(new URL('../js/wasm/tu-layouts.json', import.meta.url)));
async function run(option) {
    const output = [], errors = [];
    const module = await createNethack({
        nethackPorted: createPortedRuntime(layouts),
        noInitialRun: true,
        print: line => output.push(line),
        printErr: line => errors.push(line),
        preRun: [instance => {
            Object.assign(instance.ENV, {
                HOME: '/root', USER: 'root', LOGNAME: 'root',
                NETHACKDIR: '/nethack', HACKDIR: '/nethack',
                TERM: 'xterm-256color', TZ: 'UTC',
            });
            instance.FS.mkdirTree('/root');
        }],
    });
    module.FS.chdir('/nethack');
    try {
        assert.equal(module.callMain([option]), 0);
    } catch (error) {
        if (error?.name !== 'ExitStatus' || error.status !== 0) throw error;
    }
    assert.deepEqual(errors, []);
    return { output, clipboard: module.teleportClipboard };
}

const copy = await run('--version:copy');
assert.ok(copy.output.length > 0);
assert.match(copy.output.join('\n'), /MacOS NetHack Version/);
assert.equal(copy.clipboard, copy.output.join('\n'));
const show = await run('--version:show');
assert.deepEqual(show.output, copy.output);
assert.equal(show.clipboard, undefined);
console.log('PASS: real version command preserves module clipboard copy/show behavior.');
