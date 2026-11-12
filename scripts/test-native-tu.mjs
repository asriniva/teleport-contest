// Same C scenarios, three builds. Native output is generated afresh; no expected
// values are derived from an Emscripten run. See nethack-c/wasm/README.md for scope.
import assert from 'node:assert/strict';
import { readFileSync, writeFileSync } from 'node:fs';
import { spawnSync } from 'node:child_process';
import { fileURLToPath } from 'node:url';
import { createHash } from 'node:crypto';
import { createPortedRuntime } from '../js/backends/emscripten/runtime.js';
process.env.TZ = 'UTC';
const root = new URL('../', import.meta.url);
const ports = JSON.parse(readFileSync(new URL('nethack-c/wasm/tu-ports.json', root)));
const layouts = JSON.parse(readFileSync(new URL('js/wasm/tu-layouts.json', root)));
const selected = process.argv.slice(2);
assert.ok(selected.every(name => ports.some(port => port.name === name)), 'Unknown native TU selection');
const casesHash = createHash('sha256').update(readFileSync(new URL('scripts/native-tu-cases.h', root))).digest('hex');
let failures = 0;
let observations = 0;
const results = [];
for (const { name } of ports) {
    if (selected.length && !selected.includes(name)) continue;
    try {
        const base = new URL(`.cache/tu-probes/native-oracles/${name}`, root);
        const provenance = JSON.parse(readFileSync(new URL(`${base}-build.json`)));
        assert.equal(provenance.casesSHA256, casesHash, `${name}: stale native cases; rebuild probes`);
        for (const [tree, key] of [['nethack-c/upstream', 'upstreamSHA256'], ['.cache/wasm64-build/tree', 'preparedSHA256']]) {
            const hash = createHash('sha256').update(readFileSync(new URL(`${tree}/${provenance.source}`, root))).digest('hex');
            assert.equal(hash, provenance[key], `${name}: source changed since native build`);
        }
        const native = spawnSync(fileURLToPath(new URL(`${base}-native`)), [], {
            encoding: 'utf8', env: { ...process.env, TZ: 'UTC' }, timeout: 30000, maxBuffer: 32 * 1024 * 1024,
        });
        assert.equal(native.status, 0, `${name} native oracle failed: ${native.error || native.stderr || native.signal}`);
        assert.ok(native.stdout.length > 0, `${name} must exercise observable behavior`);
        if (['calendar', 'date', 'rnd', 'unixtty'].includes(name)) {
            const pristine = spawnSync(fileURLToPath(new URL(`${base}-pristine`)), [], {
                encoding: 'utf8', env: { ...process.env, TZ: 'UTC' }, timeout: 30000, maxBuffer: 32 * 1024 * 1024,
            });
            assert.equal(pristine.status, 0, `${name} pristine native oracle failed: ${pristine.error || pristine.stderr || pristine.signal}`);
            if (name === 'calendar') {
                // The inherited recorder patch deliberately adds an environment
                // override. All explicit-date algorithms must still match.
                const marker = 'recording-specific\n';
                const originalParts = pristine.stdout.split(marker), recorderParts = native.stdout.split(marker);
                assert.equal(originalParts.length, 2); assert.equal(recorderParts.length, 2);
                assert.equal(originalParts[0], recorderParts[0], 'Pristine native calendar algorithms');
                assert.equal(originalParts[1], 'n:1768478400\nn:2026\nn:7\nn:0\nn:0\nn:0\n', 'Pristine ignores recorder-only fixed datetime');
                assert.equal(recorderParts[1], 'n:1794528000\nn:2026\nn:1\nn:1\nn:1\nn:1\n', 'Recorder fixed datetime semantics');
            } else {
                assert.equal(pristine.stdout, native.stdout, `${name}: pristine and prepared native behavior`);
            }
        }
        for (const mode of ['reference', 'hybrid']) {
            const lines = [];
            const factory = (await import(`${base}-${mode}.mjs`)).default;
            const module = await factory({ print: line => lines.push(line), nethackPorted: createPortedRuntime(layouts) });
            module._probe_native_oracle();
            const actual = lines.join('\n') + '\n';
            if (actual !== native.stdout) {
                writeFileSync(new URL(`${base}-native.txt`), native.stdout);
                writeFileSync(new URL(`${base}-${mode}.txt`), actual);
                let offset = 0;
                while (offset < actual.length && actual[offset] === native.stdout[offset]) offset++;
                throw new Error(`${name}: ${mode} differs from native at byte ${offset}:\n` +
                    `native: ${JSON.stringify(native.stdout.slice(offset, offset + 140))}\n` +
                    `${mode}: ${JSON.stringify(actual.slice(offset, offset + 140))}\nFull outputs: ${fileURLToPath(base)}-*.txt`);
            }
        }
        if (name === 'isaac64') {
            // A wrong JS result must be observable against the independent
            // native executable, even if module creation still succeeds.
            const broken = createPortedRuntime(layouts);
            const next = broken.isaac64_next_uint64.bind(broken);
            broken.isaac64_next_uint64 = (...args) => next(...args) ^ 1n;
            const lines = [];
            const factory = (await import(`${base}-hybrid.mjs`)).default;
            const module = await factory({ print: line => lines.push(line), nethackPorted: broken });
            module._probe_native_oracle();
            assert.notEqual(lines.join('\n') + '\n', native.stdout, 'Native oracle must detect a mutated JS RNG');
        }
        const count = native.stdout.split('\n').length - 1;
        observations += count;
        results.push({ name, passed: true, observations: count, pristineNative: provenance.pristineNative });
        console.log(`PASS ${name}: native C = Emscripten C = JavaScript (${native.stdout.split('\n').length - 1} observations)`);
    } catch (error) {
        failures++;
        results.push({ name, passed: false, error: error.message });
        console.error(`FAIL ${name}: ${error.message}`);
    }
}
writeFileSync(new URL('.cache/native-tu-results.json', root), JSON.stringify({ passed: results.length - failures, failed: failures, observations, results }, null, 2) + '\n');
console.log(`Native TU coverage: ${results.length - failures}/${results.length} passed, ${observations} observations.`);
if (failures) process.exitCode = 1;
