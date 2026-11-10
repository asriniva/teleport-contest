import assert from 'node:assert/strict';
import { createTerminalBackend } from '../js/terminal-backend.js';
import { decodeScreen } from '../frozen/screen-decode.mjs';
const encoder = new TextEncoder();
async function test(name, run) {
    const terminal = await createTerminalBackend();
    try { await run(terminal); console.log(`PASS: ${name}`); }
    finally { terminal.dispose(); }
}
const write = (t, s) => t.write(encoder.encode(s));
const grid = t => decodeScreen(t.snapshot().screen);
await test('fragmented escape sequences and 16-color attributes', t => {
    write(t, '\x1b['); write(t, '2;4H\x1b[31;1;4;7m@');
    const { screen, cursor } = t.snapshot(), cell = decodeScreen(screen)[1][3];
    assert.equal(cell.ch, '@'); assert.equal(cell.color, 1); assert.equal(cell.attr, 7);
    assert.deepEqual(cursor, [4, 1, 1]);
});
await test('cursor addressing, erase to end of screen, and reset', t => {
    write(t, 'old\x1b[3;1Hstale\x1b[H\x1b[Jnew');
    const g = grid(t);
    assert.equal(g[0].slice(0,3).map(c=>c.ch).join(''), 'new');
    assert.equal(g[2].map(c=>c.ch).join('').trim(), '');
});
await test('DEC graphics and cursor visibility', t => {
    write(t, '\x1b(0lqk\x1b(B\x1b[?25l');
    const { screen, cursor } = t.snapshot();
    assert.equal(decodeScreen(screen)[0].slice(0,3).map(c=>c.ch).join(''), '┌─┐');
    assert.equal(cursor[2], 0);
    write(t, '\x1b[?25h'); assert.equal(t.snapshot().cursor[2], 1);
});
await test('primary and alternate screen buffers', t => {
    write(t, 'main\x1b[?1049h\x1b[Halt');
    assert.match(t.snapshot().screen, /^alt/);
    write(t, '\x1b[?1049l'); assert.match(t.snapshot().screen, /^main/);
});
await test('Unix tty LF conversion and scrolling', t => {
    for (const byte of encoder.encode(Array.from({length:25},(_,i)=>String(i)).join('\n'))) t.writeByte(byte);
    const g = grid(t);
    assert.equal(g[0].slice(0,2).map(c=>c.ch).join('').trim(), '1');
    assert.equal(g[23].slice(0,2).map(c=>c.ch).join(''), '24');
});
await test('RGB foregrounds and explicit backgrounds survive serialization', t => {
    write(t, '\x1b[38;2;123;45;67;44m@');
    const { screen } = t.snapshot();
    assert.match(screen, /38;2;123;45;67/);
    assert.match(screen, /44m/);
    assert.match(screen, /@/);
});
await test('ANSI tty secondary DEC character set', t => {
    write(t, '\x0elqk\x0f');
    assert.equal(grid(t)[0].slice(0,3).map(c=>c.ch).join(''), '┌─┐');
});
