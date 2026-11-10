/** Standalone JS/native differential tests; production imports no Node modules. */
import assert from 'node:assert/strict';
import { createHash } from 'node:crypto';
import { readFileSync, writeFileSync, mkdirSync, existsSync } from 'node:fs';
import { fileURLToPath } from 'node:url';
import { resolve } from 'node:path';
import { execFileSync } from 'node:child_process';
import { Terminfo, createTerminfo, parseTerminfo } from '../js/services/terminfo.js';
import { pinnedXterm256color, PINNED_ENTRY_SHA256, BOOLEAN_CODES, NUMBER_CODES, STRING_CODES } from '../js/services/terminfo-data.js';

const root = fileURLToPath(new URL('../', import.meta.url));
const scratch = resolve(root, '.cache/js-dependency-terminfo');
mkdirSync(scratch, { recursive: true });
const bytes = pinnedXterm256color();
const entry = readFileSync(resolve(root, 'nethack-c/wasm/terminfo/x/xterm-256color'));
assert.deepEqual(bytes, new Uint8Array(entry));
assert.equal(createHash('sha256').update(bytes).digest('hex'), PINNED_ENTRY_SHA256);
assert.notEqual(bytes, pinnedXterm256color(), 'embedded bytes must be instance-local');
const t = createTerminfo();
assert.equal(t.tgetent(null, 'xterm-256color'), 1);

const hex = value => value === null ? 'NULL' : Array.from(value, c => (c.charCodeAt(0) & 255).toString(16).padStart(2, '0')).join('');
const lines = [];
const emit = (label, value) => lines.push(`${label}=${hex(value)}`);
const strings = ['pc', 'le', 'ho', 'nd', 'ce', 'up', 'xd', 'cm', 'so', 'se', 'us', 'ue', 'ZH', 'ZR', 'ti', 'te', 'eA', 'ks', 'ke', 'mr', 'mb', 'md', 'mh', 'me', 'vi', 've', 'Ic', 'as', 'ae', 'cd', 'cl', 'AF', 'Sf'];
for (const id of strings) emit(id, t.tgetstr(id));
for (const id of ['co', 'li', 'sg', 'Co']) lines.push(`${id}=${t.tgetnum(id)}`);
for (const id of ['os', 'ul']) lines.push(`${id}=${t.tgetflag(id)}`);
for (let color = 0; color < 256; color++) emit(`color-${color}`, t.tparm(t.tgetstr('AF'), color));
for (let row = 0; row < 24; row++) emit(`cursor-${row}`, t.tgoto(t.tgetstr('cm'), row * 3, row));
emit('rgb', t.tparm(t.tgetstr('Ic'), 15, 120, 340, 560));
let collected = '';
t.tputs(t.tgetstr('cl'), 24, byte => { collected += String.fromCharCode(byte); });
emit('tputs', collected);

const additionalC = [];
function compareExpansion(label, format, args = []) {
  emit(label, t.tparm(format, ...args));
  const cArgs = args.map(value => typeof value === 'string' ? JSON.stringify(value) : `${value}L`);
  additionalC.push(`emit(${JSON.stringify(label)}, tparm(${JSON.stringify(format)}${cArgs.length ? ', ' + cArgs.join(', ') : ''}));`);
}
function compareCapability(label, id, args = []) {
  emit(label, t.tparm(t.tgetstr(id), ...args));
  additionalC.push(`emit(${JSON.stringify(label)}, tparm(tgetstr(${JSON.stringify(id)}, NULL)${args.length ? ', ' + args.map(x => `${x}L`).join(', ') : ''}));`);
}
for (const id of ['bc', 'zz', '', 'c', 'cm-extra']) {
  emit(`lookup-${id}`, t.tgetstr(id));
  additionalC.push(`emit(${JSON.stringify(`lookup-${id}`)}, tgetstr(${JSON.stringify(id)}, NULL));`);
}
lines.push(`bs=${t.tgetflag('bs')}`);
additionalC.push('printf("bs=%d\\n", tgetflag("bs"));');
// General parameter-language operations, in addition to the real entry programs.
const expressions = [
  ['arithmetic', '%p1%p2%+%d/%p1%p2%-%d/%p1%p2%*%d/%p1%p2%/%d/%p1%p2%m%d', [37, 5]],
  ['negative-division', '%p1%p2%/%d/%p1%p2%m%d', [-37, 5]],
  ['zero-division', '%p1%p2%/%d/%p1%p2%m%d', [17, 0]],
  ['bitwise', '%p1%p2%&%d/%p1%p2%|%d/%p1%p2%^%d/%p1%~%d', [85, 51]],
  ['boolean', '%p1%p2%A%d/%p1%p2%O%d/%p1%!%d/%p2%!%d', [0, 7]],
  ['compare', '%p1%p2%=%d/%p1%p2%<%d/%p1%p2%>%d', [4, 9]],
  ['formatting', '%p1%04d/%p2%:6d/%p3%:-6d/%p4%#x/%p4%#o/%p4%2.2X', [7, -7, 7, 30]],
  ['precision', '%p1%.0d/%p1%3.0d/%p2%08.4d', [0, 7]],
  ['character', "%{0}%c/%{65}%c/%'Z'%c/%%", []],
  ['vars', '%p1%Pa%ga%d/%p2%PA%gA%d', [17, 29]],
  ['static-persists', '%gA%d', []],
  ['strings', '%p1%l%d/%p1%:8.3s', ['hello']],
  ['increment-once', '%i%i%p1%d;%p2%d', [2, 3]],
  ['nested-true', '%?%p1%tA%?%p2%tB%eC%;%eD%;', [1, 1]],
  ['nested-else', '%?%p1%tA%?%p2%tB%eC%;%eD%;', [1, 0]],
  ['nested-outer-else', '%?%p1%tA%?%p2%tB%eC%;%eD%;', [0, 1]],
  ['implicit-args', '%d;%d', [12, 34]],
  ['escaped-param-implicit', '%%p1%d', [12]],
  ['escaped-param-formatted', '%%p1%02d', [12]],
];
for (const [label, format, args] of expressions) compareExpansion(`expression-${label}`, format, args);
// tparm's stack is int-sized even though the API accepts long arguments.
compareExpansion('int-truncation', '%p1%d', [4294967297]);
for (let color = 0; color < 256; color++) compareCapability(`background-${color}`, 'AB', [color]);
for (let row = 0; row < 24; row++) for (let col = 0; col < 80; col++) {
  const label = `position-${row}-${col}`;
  emit(label, t.tgoto(t.tgetstr('cm'), col, row));
  additionalC.push(`emit("${label}", tgoto(tgetstr("cm", NULL), ${col}, ${row}));`);
}
for (const component of [0, 1, 100, 500, 999, 1000])
  compareCapability(`rgb-${component}`, 'Ic', [255, component, 1000 - component, component]);
// Exhaust the nine boolean sgr arguments; covers all conditionals in that entry.
for (let mask = 0; mask < 512; mask++)
  compareCapability(`attributes-${mask}`, 'sa', Array.from({ length: 9 }, (_, bit) => (mask >>> bit) & 1));

for (const [i, text] of [null, '', '50', 'A$<5>B', 'A$<2.5*>B', '$x$<bad>z', '$<1.2.3>', '$$<1>'].entries()) {
  let output = '';
  const rc = t.tputs(text, 3, byte => { output += String.fromCharCode(byte); });
  emit(`output-${i}`, output);
  lines.push(`output-return-${i}=${rc}`);
  additionalC.push(`printf("output-${i}="); { int rc = tputs(${text === null ? 'NULL' : JSON.stringify(text)}, 3, emit_hex); printf("\\noutput-return-${i}=%d\\n", rc); }`);
}
lines.push(`unknown=${t.tgetent(null, 'teleport-no-such-terminal')}`);

// Compile a private probe, without touching the existing shared probe or build.
const baseline = readFileSync(resolve(root, 'scripts/terminfo-probe.c'), 'utf8');
const source = baseline.replace('    /* Unknown terminals', () => `    ${additionalC.join('\n    ')}\n    /* Unknown terminals`);
const probeC = resolve(scratch, 'probe-js-terminfo.c');
const probe = resolve(scratch, 'probe-js-terminfo');
writeFileSync(probeC, source);
const cachedCompiler = resolve(root, '.cache/wasm64-build/host-cc');
execFileSync(existsSync(cachedCompiler) ? cachedCompiler : 'cc', [probeC, '-lncurses', '-o', probe]);
const expected = execFileSync(probe, [], {
  encoding: 'utf8', maxBuffer: 4 * 1024 * 1024,
  env: { ...process.env, TERMINFO: resolve(root, 'nethack-c/wasm/terminfo'), TERM: 'xterm-256color', LINES: '24', COLUMNS: '80' },
});
const actual = lines.join('\n') + '\n';
writeFileSync(resolve(scratch, 'native-output.txt'), expected);
writeFileSync(resolve(scratch, 'js-output.txt'), actual);
const expectedLines = expected.trimEnd().split('\n');
assert.equal(lines.length, expectedLines.length, 'probe line count');
for (let i = 0; i < lines.length; i++) assert.equal(lines[i], expectedLines[i], `native parity at line ${i + 1}`);

// Independently verify area copying, raw bytes and argument-order semantics.
assert.equal(t.tgetent('xterm-256color'), 1);
const area = { bytes: new Uint8Array(40), offset: 3 };
const cm = t.tgetstr('cm', area);
assert.equal(area.offset, 3 + cm.length + 1);
assert.deepEqual(Array.from(area.bytes.slice(3, area.offset)), [...Array.from(cm, c => c.charCodeAt(0)), 0]);
assert.throws(() => t.tgetstr('cm', { bytes: new Uint8Array(2), offset: 0 }), RangeError);
assert.equal(t.tgetstr('unknown'), null);
assert.equal(t.tgetnum('zz'), -1);
assert.equal(t.tgetflag('zz'), 0);
assert.equal(t.tparm(null), null);
assert.equal(t.tparm('%ga%d'), '0', 'uninitialized dynamic variables use ncurses 6.5 zero initialization');
assert.equal(t.tgoto(cm, 3, 2), '\x1b[3;4H');
assert.equal(t.tgetstr('me'), '\x1b[0m', 'termcap sgr0 must exclude alternate charset reset');
const dimensions = createTerminfo({ lines: 50, columns: 132 });
dimensions.tgetent('xterm-256color');
assert.equal(dimensions.tgetnum('li'), 50);
assert.equal(dimensions.tgetnum('co'), 132);
assert.equal(new Terminfo({ entries: [] }).tgetent('xterm-256color'), -1);
const events = [];
const timed = createTerminfo({ delay: (...event) => events.push(event) });
const output = [];
timed.tputs('A$<1.2*>B$<5/>C', 3, byte => output.push(byte));
assert.deepEqual(output, [65, 66, 67]);
assert.deepEqual(events, [[3, false], [5, true]]);

// Parsed entries own their values rather than retaining the caller's byte view.
const padded = new Uint8Array(bytes.length + 8);
padded.set(bytes, 5);
assert.deepEqual(parseTerminfo(padded.subarray(5, bytes.length + 5)), parseTerminfo(bytes));
const parsed = parseTerminfo(bytes);
assert.equal(parsed.numberWidth, 2);
assert.ok(parsed.extended.strings.size > 0, 'pinned extended database section is decoded');
assert.deepEqual([BOOLEAN_CODES.length, NUMBER_CODES.length, STRING_CODES.length], [44, 39, 414]);

// A small generated modern entry proves 32-bit numbers and absent/cancelled values.
function syntheticEntry(cancelled = false) {
  const result = [];
  const word = n => { result.push(n & 255, (n >> 8) & 255); };
  const dword = n => { word(n); word(n >> 16); };
  const text = s => result.push(...Array.from(s, c => c.charCodeAt(0)));
  const names = 'synthetic|alias|test terminal\0';
  for (const value of [0x21e, names.length, 2, 3, 3, 4]) word(value);
  text(names); result.push(1, 0); if (result.length % 2) result.push(0);
  dword(100000); dword(-1); dword(-2);
  word(0); word(-1); word(-2); text('abc\0');
  // One extended boolean, number, and string; values first, then named offsets.
  for (const value of [1, 1, 1, cancelled ? 3 : 4, cancelled ? 9 : 12]) word(value);
  result.push(1, 0); dword(100001);
  for (const value of [cancelled ? -2 : 0, 0, 3, 6]) word(value);
  text(cancelled ? 'XB\0XN\0XS\0' : 'ok\0XB\0XN\0XS\0');
  return Uint8Array.from(result);
}
const synthetic = parseTerminfo(syntheticEntry());
assert.equal(synthetic.numberWidth, 4);
assert.deepEqual(synthetic.names, ['synthetic', 'alias']);
assert.deepEqual(synthetic.numbers, [100000, -1, -2]);
assert.deepEqual(synthetic.strings, ['abc', null, null]);
assert.equal(synthetic.extended.booleans.get('XB'), 1);
assert.equal(synthetic.extended.numbers.get('XN'), 100001);
assert.equal(synthetic.extended.strings.get('XS'), 'ok');
const custom = new Terminfo({ entries: [syntheticEntry()], columns: null, lines: null });
assert.equal(custom.tgetent('alias'), 1);
assert.equal(custom.tgetflag('XB'), 1);
assert.equal(custom.tgetnum('XN'), 100001);
assert.equal(custom.tgetstr('XS'), 'ok');
const cancelled = new Terminfo({ entries: [syntheticEntry(true)] });
assert.equal(cancelled.tgetent('synthetic'), 1);
assert.equal(cancelled.tgetstr('XS'), null, 'cancelled extended strings retain their offset slot but no value bytes');
assert.equal(cancelled.tgetflag('XB'), 1);
assert.equal(cancelled.tgetnum('XN'), 100001);

let malformedCases = 0;
const reject = data => { assert.throws(() => parseTerminfo(data), RangeError); malformedCases++; };
for (let length = 0; length < 12; length++) reject(bytes.slice(0, length));
for (const offset of [0, 2, 4, 6, 8, 10]) {
  const invalid = bytes.slice(); invalid[offset] = 255; invalid[offset + 1] = 255; reject(invalid);
}
const namesUnterminated = bytes.slice(); namesUnterminated[12 + new DataView(bytes.buffer).getInt16(2, true) - 1] = 65; reject(namesUnterminated);
reject(bytes.slice(0, 100));
reject(bytes.slice(0, -1));
const offsetStart = 12 + 37 + 38 + 1 + 15 * 2;
const badOffset = bytes.slice(); new DataView(badOffset.buffer).setInt16(offsetStart, 32767, true); reject(badOffset);
assert.throws(() => parseTerminfo('not bytes'), TypeError);
for (const format of ['%p0%d', '%pA%d', '%{x}%d', "%'x", '%q', '%p1%tmissing', '%p1%10001d'])
  assert.throws(() => t.tparm(format), RangeError);

console.log(`PASS: ${lines.length} native-ncurses comparisons using the identical pinned entry; all NetHack queries, 256 foreground/background colors, 1920 cursors, RGB, 512 attributes, expression operators, tputs and unknown terminal.`);
console.log(`PASS: raw-entry provenance, 16/32-bit and extended parsing, area-copy/state isolation, explicit dimensions/delay callbacks, ${malformedCases} malformed-entry cases and invalid expression rejection.`);
console.log('Scope: standalone service only; no game integration or public-recording equivalence claim. General setupterm fixups, legacy termcap coordinate syntax, baud-rate pad bytes and TTY timing are outside this implementation.');
