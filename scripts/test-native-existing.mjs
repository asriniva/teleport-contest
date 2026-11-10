// Original test files/cases with native C selected as their reference. Results
// distinguish an assertion mismatch from a suite that did not finish its cases.
import { spawn } from 'node:child_process';
import { readFileSync, writeFileSync, readdirSync, existsSync, mkdirSync } from 'node:fs';
import { fileURLToPath } from 'node:url';
const root = new URL('../', import.meta.url), cache = new URL('.cache/', root);
const ports = JSON.parse(readFileSync(new URL('nethack-c/wasm/tu-ports.json', root)));
const selected = process.argv.slice(2);
if (!selected.every(name => ports.some(port => port.name === name))) throw new Error('Unknown native test suite');
const names = ports.map(p => p.name).filter(name => (!selected.length || selected.includes(name)) && existsSync(new URL(`test-tu-${name}.mjs`, import.meta.url)));
for (const name of names) {
    if (!readFileSync(new URL(`test-tu-${name}.mjs`, import.meta.url), 'utf8').includes('referenceBackend(')) throw new Error(`${name}: existing suite has no native reference selection`);
}
const runId = `${process.pid}-${Date.now()}`;
const directory = new URL(`native-existing-runs/${runId}/`, cache);
mkdirSync(directory, { recursive: true });
console.log(`Full native run ${runId}: ${names.length} existing suites.`);
let next = 0;
const results = [];
async function run(name) {
    const script = fileURLToPath(new URL(`test-tu-${name}.mjs`, import.meta.url));
    const result = await new Promise(resolve => {
        const child = spawn(process.execPath, [script], { env: { ...process.env, TELEPORT_NATIVE_TESTS: '1', TELEPORT_NATIVE_RUN_ID: runId } });
        let stdout = '', stderr = '', error;
        const timer = setTimeout(() => { error = 'Native suite timed out after 600 seconds'; child.kill('SIGTERM'); }, 600000);
        child.stdout.on('data', data => { stdout += data; });
        child.stderr.on('data', data => { stderr += data; });
        child.on('error', problem => { error = problem.message; });
        child.on('close', (status, signal) => { clearTimeout(timer); resolve({ stdout, stderr, error, status, signal }); });
    });
    writeFileSync(new URL(`${name}.log`, directory), result.stdout + result.stderr);
    const passed = result.status === 0;
    const detail = result.error || result.stderr || result.stdout;
    console.log(`${passed ? 'PASS' : 'FAIL'} ${name}: ${passed ? result.stdout.trim().split('\n').at(-1) : detail.slice(0, 350).replaceAll('\n', ' ')}`);
    results.push({ name, passed, exitStatus: result.status, signal: result.signal, detail, log: fileURLToPath(new URL(`${name}.log`, directory)) });
}
async function worker() { while (next < names.length) await run(names[next++]); }
const workers = await Promise.allSettled(Array.from({ length: Math.min(3, names.length) }, worker));
for (const worker of workers) if (worker.status === 'rejected') throw worker.reason;
const reports = readdirSync(cache).filter(file => /^native-assertions-.*\.json$/.test(file)).flatMap(file => {
    try { const report = JSON.parse(readFileSync(new URL(file, cache)));return report.runId === runId ? [report] : []; } catch { return []; }
});
for (const result of results) {
    const matching = reports.filter(report => report.test === fileURLToPath(new URL(`test-tu-${result.name}.mjs`, import.meta.url)));
    result.expectedReports = ['calendar', 'date'].includes(result.name) ? 6 : 1;
    result.completed = matching.length === result.expectedReports && matching.every(r => r.completed) && matching.some(r => r.nativeInstances > 0);
    result.assertions = matching.reduce((n, r) => n + r.assertions, 0);
    result.assertionFailures = matching.reduce((n, r) => n + r.failures, 0);
    result.reports = matching.map(r => r.pid);
    result.passed &&= result.completed;
}
results.sort((a, b) => names.indexOf(a.name) - names.indexOf(b.name));
const passed = results.filter(r => r.passed).length, completed = results.filter(r => r.completed).length;
const summary = { runId, selection: selected.length ? selected : null, passed, failed: results.length - passed, completed, assertions: results.reduce((n, r) => n + r.assertions, 0), assertionFailures: results.reduce((n, r) => n + r.assertionFailures, 0), results };
writeFileSync(new URL('results.json', directory), JSON.stringify(summary, null, 2) + '\n');
writeFileSync(new URL(selected.length ? 'native-existing-selected-results.json' : 'native-existing-results.json', cache), JSON.stringify(summary, null, 2) + '\n');
console.log(`Existing native suites: ${completed}/${results.length} completed; ${passed} passed, ${results.length - passed} failed. ${summary.assertions} assertions, ${summary.assertionFailures} assertion failures.`);
console.log(`Report: ${fileURLToPath(new URL('results.json', directory))}`);
if (passed !== results.length) process.exitCode = 1;
