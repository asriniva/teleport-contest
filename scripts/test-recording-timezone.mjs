import assert from 'node:assert/strict';
import {createCTime} from '../js/c-runtime/time.js';
import {createJsRuntime} from '../js/nethack/runtime.js';
import {PUBLIC_RECORDING_PROFILE} from '../js/recording-profile.js';

const timeZone = PUBLIC_RECORDING_PROFILE.timeZone;
const clock = createCTime({native: true, timeZone});
const epoch = text => BigInt(Date.parse(text) / 1000);

for (const [timestamp, localHour, dst, utcOffset] of [
    ['2026-01-15T14:00:00Z', 9, 0, -18000n],
    ['2026-07-15T13:00:00Z', 9, 1, -14400n],
]) {
    const value = epoch(timestamp);
    const local = clock.localtime(value);
    assert.equal(local.tm_hour, localHour);
    assert.equal(local.tm_isdst, dst);
    assert.equal(local.tm_gmtoff, utcOffset);
    assert.equal(clock.mktime({...local}), value);
    assert.equal(clock.gmtime(value).tm_gmtoff, 0n);
}

const wall = (month, day, hour, isdst) => ({
    tm_year: 126, tm_mon: month, tm_mday: day, tm_hour: hour,
    tm_min: 30, tm_sec: 0, tm_isdst: isdst,
});
assert.equal(clock.mktime(wall(2, 8, 2, -1)), epoch('2026-03-08T07:30:00Z'), 'spring gap');
assert.equal(clock.mktime(wall(10, 1, 1, -1)), epoch('2026-11-01T05:30:00Z'), 'earlier repeated hour');
assert.equal(clock.mktime(wall(10, 1, 1, 0)), epoch('2026-11-01T06:30:00Z'), 'explicit standard time');

const recordingClock = epoch('2026-05-02T12:00:00Z');
const runtime = createJsRuntime({timeZone, now: () => recordingClock});
runtime.setEnvironment('NETHACK_RECORDING_EPOCH', String(recordingClock));
runtime.setEnvironment('NETHACK_FIXED_DATETIME', '20260115090000');
const start = runtime.calendar('getnow');
assert.equal(start, epoch('2026-01-15T13:00:00Z'), 'explicit DST from the capture clock');
assert.equal(runtime.calendar('hhmmss', start), 80000n);
console.log('PASS: recording timezone offsets, DST overlap and gap, and engine replay date');
