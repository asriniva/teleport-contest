import assert from 'node:assert/strict';
import {moveloop_core, moveloop, u_calc_moveamt} from '../js/ported/allmain.js';

assert.equal(moveloop_core.length, 0);
assert.equal(moveloop.length, 1);
assert.equal(u_calc_moveamt.length, 1);
const hero = {ux: 4, uy: 5, umovement: -2, usteed: 0};
const game = {
    u: hero, gy: {youmonst: {data: {mmove: 8}}},
    NORMAL_SPEED: 12, UNENCUMBERED: 0,
};
u_calc_moveamt(0, game);
assert.equal(hero.umovement, 6);
console.log('PASS: ALLMAIN accepts an explicit game context with the original entry arities');
