// V8 block execution for the leaderboard entry, independent of C parity.
import {Session} from 'node:inspector';
import {createHash} from 'node:crypto';
import {readFileSync, readdirSync, writeFileSync} from 'node:fs';
import {relative, resolve} from 'node:path';
import {fileURLToPath} from 'node:url';

const [directory, output, baselinePath] = process.argv.slice(2);
if (!directory || !output) {
    throw new Error('Usage: node scripts/measure-recording-coverage.mjs SESSION_DIRECTORY OUTPUT_JSON [PUBLIC_COVERAGE_JSON]');
}

const inspector = new Session();
inspector.connect();
function command(method, params = {}) {
    return new Promise((accept, reject) => {
        inspector.post(method, params, (error, value) => error ? reject(error) : accept(value));
    });
}

await command('Profiler.enable');
await command('Profiler.startPreciseCoverage', {callCount: true, detailed: true});
const {runSegment} = await import('../js/jsmain.js');
const files = readdirSync(directory).filter(name => name.endsWith('.session.json')).sort();
if (!files.length) throw new Error('No .session.json files in ' + directory);
for (const name of files) {
    const data = new Map();
    const storage = {
        getItem: key => data.get(key) ?? null,
        setItem: (key, value) => data.set(key, String(value)),
        removeItem: key => data.delete(key),
        get length() { return data.size; },
        key: index => [...data.keys()][index] ?? null,
    };
    const {segments} = JSON.parse(readFileSync(resolve(directory, name), 'utf8'));
    for (const segment of segments) await runSegment({...segment, storage});
    console.log(name);
}

const {result} = await command('Profiler.takePreciseCoverage');
await command('Profiler.stopPreciseCoverage');
inspector.disconnect();

const root = fileURLToPath(new URL('../', import.meta.url));
const coverage = {};
for (const module of result) {
    if (!module.url.startsWith('file:')) continue;
    const name = relative(root, fileURLToPath(module.url));
    if (name.startsWith('js/')) coverage[name] = module.functions;
}
const digest = file => createHash('sha256').update(readFileSync(resolve(root, file))).digest('hex');
const sourceSha256 = Object.fromEntries(Object.keys(coverage).map(file => [file, digest(file)]));
writeFileSync(output, JSON.stringify({sourceSha256, coverage}));

const baseline = baselinePath ? JSON.parse(readFileSync(baselinePath, 'utf8')) : {sourceSha256, coverage};
for (const [file, hash] of Object.entries(baseline.sourceSha256)) {
    if ((sourceSha256[file] ?? digest(file)) !== hash) throw new Error('Coverage sources differ at ' + file);
}
const publicCoverage = baseline.coverage;
const key = range => range.startOffset + ':' + range.endOffset;
const summary = {
    filesExecuted: Object.keys(coverage).length,
    publicFunctionsReported: 0,
    publicFunctionsUnentered: 0,
    remainingPublicFunctionsUnentered: 0,
    additionalFunctionEntries: 0,
    publicZeroCountBlocks: 0,
    additionalExactBlockRanges: 0,
    filesWithNewCoverage: {},
};

for (const [file, publicFunctions] of Object.entries(publicCoverage)) {
    const functions = new Map((coverage[file] ?? []).map(fn => [key(fn.ranges[0]), fn]));
    const extraEntries = [];
    let extraBlocks = 0;
    for (const original of publicFunctions) {
        const [body, ...blocks] = original.ranges;
        const extra = functions.get(key(body));
        const entered = Boolean(extra?.ranges[0].count);
        summary.publicFunctionsReported++;
        if (!body.count) {
            summary.publicFunctionsUnentered++;
            if (entered) extraEntries.push(original.functionName || '(anonymous)');
            else summary.remainingPublicFunctionsUnentered++;
        }
        const extraRanges = new Set(extra?.ranges.slice(1).filter(range => range.count).map(key));
        for (const block of blocks) {
            if (block.count) continue;
            summary.publicZeroCountBlocks++;
            if (extraRanges.has(key(block))) extraBlocks++;
        }
    }
    if (extraEntries.length || extraBlocks) {
        summary.filesWithNewCoverage[file] = {extraEntries, extraBlocks};
        summary.additionalFunctionEntries += extraEntries.length;
        summary.additionalExactBlockRanges += extraBlocks;
    }
}
writeFileSync(output + '.summary.json', JSON.stringify(summary, null, 2) + '\n');
