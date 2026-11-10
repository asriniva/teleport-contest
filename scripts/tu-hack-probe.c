/* Controlled original-C/JS HACK policy fixture. Original hack.c is included unchanged.
 * Native-host, selected game and public deadline gates are separate.
 * Catalogues are synthetic native tables. Neither objects.c nor monst.c is
 * linked; init_objects/decl_globals_init below are logged foreign controls,
 * not real catalogue initialization. No actual-catalogue parity is claimed.
 */
#include "hack.h"
#include "func_tab.h"
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <emscripten/stack.h>
#include <emscripten/heap.h>
__typeof__(gt) gt;
__typeof__(svl) svl;
__typeof__(u) u;
__typeof__(gy) gy;
__typeof__(gi) gi;
__typeof__(gb) gb;
__typeof__(svm) svm;
__typeof__(flags) flags;
__typeof__(svc) svc;
__typeof__(svd) svd;
__typeof__(gv) gv;
__typeof__(objects) objects;
__typeof__(uarmf) uarmf;
__typeof__(uleft) uleft;
__typeof__(uright) uright;
__typeof__(svi) svi;
__typeof__(uwep) uwep;
__typeof__(iflags) iflags;
__typeof__(windowprocs) windowprocs;
__typeof__(a11y) a11y;
__typeof__(uswapwep) uswapwep;
__typeof__(svq) svq;
__typeof__(gd) gd;
__typeof__(gk) gk;
__typeof__(disp) disp;
__typeof__(uball) uball;
__typeof__(gm) gm;
__typeof__(gn) gn;
__typeof__(uarmh) uarmh;
__typeof__(svr) svr;
__typeof__(svp) svp;
__typeof__(gc) gc;
__typeof__(ga) ga;
__typeof__(gw) gw;
__typeof__(gu) gu;
__typeof__(svk) svk;
__typeof__(obj_descr) obj_descr;
const struct const_globals cg={0};
const struct c_common_strings c_common_strings={.c_Something="Something",.c_something="something",.c_You_can_move_again="You can move again."};
const struct symdef defsyms[MAXPCHARS+1]={[0 ... MAXPCHARS]={.explanation="fixture terrain"}};
const schar xdir[N_DIRS_Z]={-1,-1,0,1,1,1,0,-1,0,0};
const schar ydir[N_DIRS_Z]={0,-1,-1,-1,0,1,1,1,0,0};
const schar dirs_ord[N_DIRS]={DIR_W,DIR_N,DIR_E,DIR_S,DIR_NW,DIR_NE,DIR_SE,DIR_SW};
struct permonst mons[NUMMONS+1]={
{.pmidx=0,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=1,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=2,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=3,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=4,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=5,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=6,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=7,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=8,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=9,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=10,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=11,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=12,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=13,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=14,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=15,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=16,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=17,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=18,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=19,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=20,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=21,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=22,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=23,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=24,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=25,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=26,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=27,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=28,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=29,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=30,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=31,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=32,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=33,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=34,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=35,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=36,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=37,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=38,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=39,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=40,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=41,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=42,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=43,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=44,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=45,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=46,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=47,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=48,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=49,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=50,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=51,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=52,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=53,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=54,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=55,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=56,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=57,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=58,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=59,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=60,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=61,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=62,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=63,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=64,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=65,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=66,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=67,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=68,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=69,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=70,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=71,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=72,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=73,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=74,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=75,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=76,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=77,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=78,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=79,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=80,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=81,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=82,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=83,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=84,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=85,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=86,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=87,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=88,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=89,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=90,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=91,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=92,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=93,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=94,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=95,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=96,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=97,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=98,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=99,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=100,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=101,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=102,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=103,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=104,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=105,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=106,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=107,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=108,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=109,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=110,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=111,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=112,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=113,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=114,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=115,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=116,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=117,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=118,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=119,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=120,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=121,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=122,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=123,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=124,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=125,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=126,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=127,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=128,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=129,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=130,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=131,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=132,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=133,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=134,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=135,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=136,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=137,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=138,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=139,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=140,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=141,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=142,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=143,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=144,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=145,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=146,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=147,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=148,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=149,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=150,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=151,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=152,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=153,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=154,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=155,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=156,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=157,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=158,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=159,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=160,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=161,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=162,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=163,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=164,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=165,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=166,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=167,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=168,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=169,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=170,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=171,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=172,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=173,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=174,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=175,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=176,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=177,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=178,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=179,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=180,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=181,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=182,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=183,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=184,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=185,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=186,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=187,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=188,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=189,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=190,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=191,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=192,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=193,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=194,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=195,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=196,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=197,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=198,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=199,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=200,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=201,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=202,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=203,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=204,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=205,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=206,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=207,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=208,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=209,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=210,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=211,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=212,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=213,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=214,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=215,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=216,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=217,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=218,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=219,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=220,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=221,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=222,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=223,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=224,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=225,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=226,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=227,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=228,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=229,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=230,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=231,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=232,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=233,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=234,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=235,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=236,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=237,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=238,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=239,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=240,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=241,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=242,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=243,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=244,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=245,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=246,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=247,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=248,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=249,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=250,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=251,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=252,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=253,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=254,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=255,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=256,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=257,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=258,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=259,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=260,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=261,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=262,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=263,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=264,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=265,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=266,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=267,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=268,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=269,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=270,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=271,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=272,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=273,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=274,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=275,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=276,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=277,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=278,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=279,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=280,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=281,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=282,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=283,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=284,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=285,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=286,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=287,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=288,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=289,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=290,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=291,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=292,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=293,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=294,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=295,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=296,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=297,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=298,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=299,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=300,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=301,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=302,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=303,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=304,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=305,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=306,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=307,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=308,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=309,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=310,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=311,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=312,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=313,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=314,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=315,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=316,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=317,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=318,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=319,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=320,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=321,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=322,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=323,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=324,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=325,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=326,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=327,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=328,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=329,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=330,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=331,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=332,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=333,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=334,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=335,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=336,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=337,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=338,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=339,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=340,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=341,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=342,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=343,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=344,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=345,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=346,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=347,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=348,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=349,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=350,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=351,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=352,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=353,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=354,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=355,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=356,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=357,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=358,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=359,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=360,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=361,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=362,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=363,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=364,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=365,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=366,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=367,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=368,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=369,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=370,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=371,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=372,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=373,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=374,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=375,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=376,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=377,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=378,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=379,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=380,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=381,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=382,.pmnames={"fixture species","fixture species","fixture species"}},
{.pmidx=383,.pmnames={"fixture species","fixture species","fixture species"}},
};
static struct monst mpool[8];static struct obj opool[16];static struct trap traps[4];static struct engr engrpool[2];static struct attack attackpool[2];static struct _cmd_queue cmdpool[2];static struct ext_func_tab extpool[2];static NhRegion regions[2];static struct selectionvar selection;static unsigned char selected[COLNO][ROWNO];static d_level levelarg;static long counters[8];static short shorts[8];static int ints[8];static struct monst*monrefs[8];static struct obj*objrefs[8];static char input[2048],labels[32][80],tracebuf[8388608],stringbuf[4096];static int tracepos,options[1024],seed,reentered,error_code;static void*growth;
static jmp_buf escapes[16];static int escape_depth;static uintptr_t rooms_base;
static seenV vis[ROWNO][COLNO],*visrows[ROWNO];
static struct {uintptr_t pointer;size_t bytes;} allocations[4096];static int allocated;
static uint64_t canonical(uint64_t);
static void append(const char*fmt,...){if(tracepos>sizeof tracebuf-8192)abort();va_list ap;va_start(ap,fmt);tracepos+=vsnprintf(tracebuf+tracepos,sizeof tracebuf-tracepos,fmt,ap);va_end(ap);}
static void grow(void){if(options[900]&&!growth){growth=malloc(emscripten_get_heap_size()+16*1024*1024);if(!growth)abort();append("growth;");}}
static void message(const char*kind,const char*fmt,va_list ap){char b[4096];vsnprintf(b,sizeof b,fmt,ap);append("%s:%s;",kind,b);grow();}
static int roll(int n){if(n<=0)abort();seed=(unsigned)seed*1664525U+1013904223U;return(unsigned)seed%n;}
static void escape_call(int code){error_code=code;if(!escape_depth)abort();longjmp(escapes[escape_depth-1],1);}
boolean (enexto)(coord * a0,coordxy a1,coordxy a2,struct permonst * a3){a0->x=a1+1;a0->y=a2;append("enexto:%d:%d;",a1,a2);return options[93];}
void (rloc_to)(struct monst * a0,coordxy a1,coordxy a2){append("rloc:%d:%d;",a1,a2);a0->mx=a1;a0->my=a2;}
void (Norep)(const char * a0,...){va_list ap;va_start(ap,a0);message("Norep",a0,ap);va_end(ap);}
boolean (revive_corpse)(struct obj * a0){append("dependency:revive_corpse:%llu;",(unsigned long long)canonical((uintptr_t)a0));return options[202];}
boolean (goodpos)(coordxy a0,coordxy a1,struct monst * a2,mmflags_nht a3){return isok(a0,a1)&&!IS_OBSTRUCTED(levl[a0][a1].typ)&&!closed_door(a0,a1);}
char * (the)(const char * a0){append("dependency:the:%s;",a0?a0:"(null)");return stringbuf;}
char * (xname)(struct obj * a0){return labels[a0>=opool&&a0<opool+16?a0-opool:31];}
void (pline)(const char * a0,...){va_list ap;va_start(ap,a0);message("pline",a0,ap);va_end(ap);}
void (exercise)(int a0,boolean a1){append("dependency:exercise:%d:%d;",(int)a0,(int)a1);}
char * (YMonnam)(struct monst * a0){return a0==&gy.youmonst?labels[30]:labels[a0>=mpool&&a0<mpool+8?16+a0-mpool:31];}
void (unmap_object)(coordxy a0,coordxy a1){append("dependency:unmap_object:%d:%d;",(int)a0,(int)a1);}
void (feel_location)(coordxy a0,coordxy a1){append("dependency:feel_location:%d:%d;",(int)a0,(int)a1);}
void (newsym)(coordxy a0,coordxy a1){append("dependency:newsym:%d:%d;",(int)a0,(int)a1);}
boolean (costly_spot)(coordxy a0,coordxy a1){append("dependency:costly_spot:%d:%d;",(int)a0,(int)a1);return options[65];}
void (addtobill)(struct obj * a0,boolean a1,boolean a2,boolean a3){append("dependency:addtobill:%llu:%d:%d:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1,(int)a2,(int)a3);}
struct monst * (shop_keeper)(char a0){append("dependency:shop_keeper:%d;",(int)a0);return options[225]?&mpool[7]:0;}
boolean (onshopbill)(struct obj * a0,struct monst * a1,boolean a2){append("dependency:onshopbill:%llu:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(unsigned long long)canonical((uintptr_t)a1),(int)a2);return options[178];}
void (subfrombill)(struct obj * a0,struct monst * a1){append("dependency:subfrombill:%llu:%llu;",(unsigned long long)canonical((uintptr_t)a0),(unsigned long long)canonical((uintptr_t)a1));}
struct monst * (find_objowner)(struct obj * a0,coordxy a1,coordxy a2){append("dependency:find_objowner:%llu:%d:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1,(int)a2);return options[104]?&mpool[7]:0;}
long (stolen_value)(struct obj * a0,coordxy a1,coordxy a2,boolean a3,boolean a4){append("dependency:stolen_value:%llu:%d:%d:%d:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1,(int)a2,(int)a3,(int)a4);return options[235];}
void (You)(const char * a0,...){va_list ap;va_start(ap,a0);message("You",a0,ap);va_end(ap);}
struct obj * (carrying)(int a0){append("dependency:carrying:%d;",(int)a0);return options[56]?&opool[14]:0;}
boolean (autopick_testobj)(struct obj * a0,boolean a1){append("dependency:autopick_testobj:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);return options[37];}
char * (y_monnam)(struct monst * a0){return a0==&gy.youmonst?labels[30]:labels[a0>=mpool&&a0<mpool+8?16+a0-mpool:31];}
void (sokoban_guilt)(void){append("dependency:sokoban_guilt;");}
struct obj * (sobj_at)(int a0,coordxy a1,coordxy a2){struct obj*o=svl.level.objects[a1][a2];for(;o;o=o->nexthere)if(o->otyp==a0)return o;return 0;}
int (glyph_at)(coordxy a0,coordxy a1){append("dependency:glyph_at:%d:%d;",(int)a0,(int)a1);return options[114];}
void (map_object)(struct obj * a0,int a1){append("dependency:map_object:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);}
void (There)(const char * a0,...){va_list ap;va_start(ap,a0);message("There",a0,ap);va_end(ap);}
boolean (on_level)(d_level * a0,d_level * a1){return a0->dnum==a1->dnum&&a0->dlevel==a1->dlevel;}
int (isok)(coordxy a0,coordxy a1){return a0>=1&&a0<COLNO&&a1>=0&&a1<ROWNO;}
struct trap * (t_at)(coordxy a0,coordxy a1){append("dependency:t_at:%d:%d;",a0,a1);return options[246]&&traps[0].tx==a0&&traps[0].ty==a1?&traps[0]:0;}
char * (The)(const char * a0){return a0;}
const char * (surface)(coordxy a0,coordxy a1){return "floor";}
int (canseemon)(struct monst * a0){return !a0->minvis;}
int (sensemon)(struct monst * a0){return options[220];}
char * (a_monnam)(struct monst * a0){return a0==&gy.youmonst?labels[30]:labels[a0>=mpool&&a0<mpool+8?16+a0-mpool:31];}
void (You_hear)(const char * a0,...){va_list ap;va_start(ap,a0);message("You_hear",a0,ap);va_end(ap);}
void (map_invisible)(coordxy a0,coordxy a1){append("dependency:map_invisible:%d:%d;",(int)a0,(int)a1);}
char * (upstart)(char * a0){if(*a0>='a'&&*a0<='z')*a0-=32;return a0;}
boolean (closed_door)(coordxy a0,coordxy a1){return IS_DOOR(levl[a0][a1].typ)&&(levl[a0][a1].doormask&(D_CLOSED|D_LOCKED));}
boolean (rng_log_enabled)(void){return options[901];}
void (rng_log_set_caller)(const char * a0,int a1,const char * a2){append("site:%s:%d:%s;",a0,a1,a2);grow();if(options[902]&&!reentered){reentered=1;append("reenter:%d;",near_capacity());}}
int (rn2)(int a0){int v=roll(a0);append("rn2:%d:%d;",a0,v);return v;}
void (obj_extract_self)(struct obj * a0){append("extract:%llu;",(unsigned long long)canonical((uintptr_t)a0));if(a0->where==OBJ_FLOOR&&isok(a0->ox,a0->oy)){struct obj**p=&svl.level.objects[a0->ox][a0->oy];while(*p&&*p!=a0)p=&(*p)->nexthere;if(*p)*p=a0->nexthere;}else if(a0->where==OBJ_INVENT){struct obj**p=&gi.invent;while(*p&&*p!=a0)p=&(*p)->nobj;if(*p)*p=a0->nobj;}a0->nexthere=0;a0->nobj=0;a0->where=OBJ_FREE;}
void (place_object)(struct obj * a0,coordxy a1,coordxy a2){append("place:%llu:%d:%d;",(unsigned long long)canonical((uintptr_t)a0),a1,a2);a0->ox=a1;a0->oy=a2;a0->where=OBJ_FLOOR;a0->nexthere=svl.level.objects[a1][a2];svl.level.objects[a1][a2]=a0;}
char * (Tobjnam)(struct obj * a0,const char * a1){snprintf(stringbuf,sizeof stringbuf,"%s %s",labels[a0>=opool&&a0<opool+16?a0-opool:31],a1);return stringbuf;}
void (blow_up_landmine)(struct trap * a0){append("dependency:blow_up_landmine:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
void (fill_pit)(coordxy a0,coordxy a1){append("dependency:fill_pit:%d:%d;",(int)a0,(int)a1);}
boolean (flooreffects)(struct obj * a0,coordxy a1,coordxy a2,const char * a3){append("dependency:flooreffects:%llu:%d:%d:%s;",(unsigned long long)canonical((uintptr_t)a0),(int)a1,(int)a2,a3?a3:"(null)");return options[108];}
char * (otense)(struct obj * a0,const char * a1){return a1;}
void (deltrap)(struct trap * a0){append("dependency:deltrap:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
void (useupf)(struct obj * a0,long a1){append("dependency:useupf:%llu:%ld;",(unsigned long long)canonical((uintptr_t)a0),(long)a1);}
void (bury_objs)(int a0,int a1){append("dependency:bury_objs:%d:%d;",(int)a0,(int)a1);}
int (random_teleport_level)(void){append("dependency:random_teleport_level;");return options[193];}
schar (depth)(d_level * a0){return a0->dlevel;}
boolean (rloco)(struct obj * a0){append("dependency:rloco:%llu;",(unsigned long long)canonical((uintptr_t)a0));return options[205];}
void (add_to_migration)(struct obj * a0){append("dependency:add_to_migration:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
void (get_level)(d_level * a0,int a1){a0->dnum=1;a0->dlevel=a1;append("getlevel:%d;",a1);}
void (seetrap)(struct trap * a0){append("dependency:seetrap:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
void (feeltrap)(struct trap * a0){append("dependency:feeltrap:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
int (launch_obj)(short a0,coordxy a1,coordxy a2,coordxy a3,coordxy a4,int a5){append("dependency:launch_obj:%d:%d:%d:%d:%d:%d;",(int)a0,(int)a1,(int)a2,(int)a3,(int)a4,(int)a5);return options[144];}
boolean (boulder_hits_pool)(struct obj * a0,coordxy a1,coordxy a2,boolean a3){append("boulder_pool:%llu:%d:%d:%d;",(unsigned long long)canonical((uintptr_t)a0),a1,a2,a3);if(options[47]){obj_extract_self(a0);return 1;}return 0;}
void (remove_object)(struct obj * a0){append("dependency:remove_object:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
void (assign_level)(d_level * a0,d_level * a1){*a0=*a1;}
void (watch_dig)(struct monst * a0,coordxy a1,coordxy a2,boolean a3){append("dependency:watch_dig:%llu:%d:%d:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1,(int)a2,(int)a3);}
void (livelog_printf)(long a0,const char * a1,...){append("livelog:%ld;",a0);va_list ap;va_start(ap,a1);message("livelog",a1,ap);va_end(ap);}
int (rnd)(int a0){int v=1+roll(a0);append("rnd:%d:%d;",a0,v);return v;}
void (delobj)(struct obj * a0){append("delobj:%llu;",(unsigned long long)canonical((uintptr_t)a0));obj_extract_self(a0);}
void (block_point)(int a0,int a1){append("dependency:block_point:%d:%d;",(int)a0,(int)a1);}
void (add_damage)(coordxy a0,coordxy a1,long a2){append("dependency:add_damage:%d:%d:%ld;",(int)a0,(int)a1,(long)a2);}
schar (acurrstr)(void){int value=options[25]?options[25]:10;append("acurrstr:%d;",value);return value;}
void (morehungry)(int a0){append("dependency:morehungry:%d;",(int)a0);}
void (dissolve_bars)(coordxy a0,coordxy a1){append("dependency:dissolve_bars:%d:%d;",(int)a0,(int)a1);}
void (b_trapped)(const char * a0,int a1){append("dependency:b_trapped:%s:%d;",a0?a0:"(null)",(int)a1);}
void (recalc_block_point)(coordxy a0,coordxy a1){append("dependency:recalc_block_point:%d:%d;",(int)a0,(int)a1);}
void (pay_for_damage)(const char * a0,boolean a1){append("dependency:pay_for_damage:%s:%d;",a0?a0:"(null)",(int)a1);}
void (maybe_unhide_at)(coordxy a0,coordxy a1){append("dependency:maybe_unhide_at:%d:%d;",(int)a0,(int)a1);}
schar (acurr)(int a0){int value=options[24]?options[24]:10;append("acurr:%d:%d;",a0,value);return value;}
void (selftouch)(const char * a0){append("dependency:selftouch:%s;",a0?a0:"(null)");}
char * (doname)(struct obj * a0){return labels[a0>=opool&&a0<opool+16?a0-opool:31];}
int (stop_donning)(struct obj * a0){append("dependency:stop_donning:%llu;",(unsigned long long)canonical((uintptr_t)a0));return options[236];}
void (Ring_off)(struct obj * a0){append("dependency:Ring_off:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
void (off_msg)(struct obj * a0){append("dependency:off_msg:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
int (Boots_off)(void){append("dependency:Boots_off;");return options[1];}
void (float_vs_flight)(void){append("dependency:float_vs_flight;");}
boolean (can_fog)(struct monst * a0){append("dependency:can_fog:%llu;",(unsigned long long)canonical((uintptr_t)a0));return options[52];}
int (curr_mon_load)(struct monst * a0){append("dependency:curr_mon_load:%llu;",(unsigned long long)canonical((uintptr_t)a0));return options[66];}
boolean (Invocation_lev)(d_level * a0){append("dependency:Invocation_lev:%llu;",(unsigned long long)canonical((uintptr_t)a0));return options[6];}
boolean (dmgtype)(struct permonst * a0,int a1){append("dependency:dmgtype:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);return options[80];}
boolean (passes_bars)(struct permonst * a0){append("dependency:passes_bars:%llu;",(unsigned long long)canonical((uintptr_t)a0));return options[182];}
int (use_pick_axe2)(struct obj * a0){append("dependency:use_pick_axe2:%llu;",(unsigned long long)canonical((uintptr_t)a0));return options[257];}
boolean (is_db_wall)(coordxy a0,coordxy a1){append("dependency:is_db_wall:%d:%d;",(int)a0,(int)a1);return options[134];}
void (pline_The)(const char * a0,...){va_list ap;va_start(ap,a0);message("pline_The",a0,ap);va_end(ap);}
int (back_to_glyph)(coordxy a0,coordxy a1){append("dependency:back_to_glyph:%d:%d;",(int)a0,(int)a1);return options[40];}
int (glyph_to_cmap)(int a0){append("dependency:glyph_to_cmap:%d;",(int)a0);return options[115];}
char * (an)(const char * a0){return a0;}
void (pline_dir)(int a0,const char * a1,...){append("direction:%d;",a0);va_list ap;va_start(ap,a1);message("pline_dir",a1,ap);va_end(ap);}
int (xytodir)(int a0,int a1){append("dependency:xytodir:%d:%d;",(int)a0,(int)a1);return options[276];}
boolean (can_ooze)(struct monst * a0){append("dependency:can_ooze:%llu;",(unsigned long long)canonical((uintptr_t)a0));return options[53];}
int (doopen_indir)(coordxy a0,coordxy a1){append("dependency:doopen_indir:%d:%d;",(int)a0,(int)a1);return options[88];}
struct _cmd_queue * (cmdq_peek)(int a0){return options[63]?&cmdpool[0]:0;}
const struct ext_func_tab * (ext_func_tab_from_func)(int (*a0)(void)){append("extfunc:%d;",a0==dokick);return a0==dokick?&extpool[0]:0;}
int (dokick)(void){append("dependency:dokick;");return options[85];}
void (You_cant)(const char * a0,...){va_list ap;va_start(ap,a0);message("You_cant",a0,ap);va_end(ap);}
boolean (block_door)(coordxy a0,coordxy a1){append("dependency:block_door:%d:%d;",(int)a0,(int)a1);return options[42];}
void (Your)(const char * a0,...){va_list ap;va_start(ap,a0);message("Your",a0,ap);va_end(ap);}
boolean (worm_cross)(int a0,int a1,int a2,int a3){append("dependency:worm_cross:%d:%d:%d:%d;",(int)a0,(int)a1,(int)a2,(int)a3);return options[273];}
boolean (is_pool_or_lava)(coordxy a0,coordxy a1){return is_pool(a0,a1)||is_lava(a0,a1);}
boolean (is_pool)(coordxy a0,coordxy a1){return IS_POOL(levl[a0][a1].typ);}
boolean (is_lava)(coordxy a0,coordxy a1){return IS_LAVA(levl[a0][a1].typ);}
boolean (block_entry)(coordxy a0,coordxy a1){append("dependency:block_entry:%d:%d;",(int)a0,(int)a1);return options[43];}
struct selectionvar * (selection_new)(void){append("selection_new;");return &selection;}
int (dist2)(coordxy a0,coordxy a1,coordxy a2,coordxy a3){int x=a0-a2,y=a1-a3;return x*x+y*y;}
coordxy (selection_getpoint)(coordxy a0,coordxy a1,struct selectionvar * a2){if(!isok(a0,a1))abort();return selected[a0][a1];}
void (selection_setpoint)(coordxy a0,coordxy a1,struct selectionvar * a2,int a3){if(!isok(a0,a1))abort();selected[a0][a1]=a3;append("selection:%d:%d:%d;",a0,a1,a3);}
void (tmp_at)(coordxy a0,coordxy a1){append("dependency:tmp_at:%d:%d;",(int)a0,(int)a1);}
int (distmin)(coordxy a0,coordxy a1,coordxy a2,coordxy a3){int x=abs(a0-a2),y=abs(a1-a3);return x>y?x:y;}
int (sgn)(int a0){return(a0>0)-(a0<0);}
void (climb_pit)(void){append("dependency:climb_pit;");}
boolean (is_art)(struct obj * a0,int a1){append("dependency:is_art:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);return options[133];}
const char * (hliquid)(const char * a0){return a0;}
struct obj * (buried_ball)(coord * a0){append("buried_ball:%d:%d;",a0->x,a0->y);if(!options[49])return 0;a0->x=u.ux;a0->y=u.uy;return &opool[14];}
void (buried_ball_to_punishment)(void){append("dependency:buried_ball_to_punishment;");}
void (impossible)(const char * a0,...){va_list ap;va_start(ap,a0);message("impossible",a0,ap);va_end(ap);}
void (set_msg_xy)(coordxy a0,coordxy a1){append("dependency:set_msg_xy:%d:%d;",(int)a0,(int)a1);}
char * (x_monnam)(struct monst * a0,int a1,const char * a2,int a3,boolean a4){return a0==&gy.youmonst?labels[30]:labels[a0>=mpool&&a0<mpool+8?16+a0-mpool:31];}
long * (alloc)(unsigned int a0){void*p=malloc(a0?a0:1);if(!p)abort();if(allocated>=4096)abort();allocations[allocated].pointer=(uintptr_t)p;allocations[allocated].bytes=a0;allocated++;append("alloc:%u:%d;",a0,allocated);return p;}
long (peek_timer)(short a0,union any * a1){append("dependency:peek_timer:%d:%llu;",(int)a0,(unsigned long long)canonical((uintptr_t)a1));return options[184];}
long (stop_timer)(short a0,union any * a1){append("dependency:stop_timer:%d:%llu;",(int)a0,(unsigned long long)canonical((uintptr_t)a1));return options[237];}
boolean (start_timer)(long a0,short a1,short a2,union any * a3){append("dependency:start_timer:%ld:%d:%d:%llu;",(long)a0,(int)a1,(int)a2,(unsigned long long)canonical((uintptr_t)a3));return options[233];}
char (highc)(char a0){return a0>='a'&&a0<='z'?a0-32:a0;}
const char * (locomotion)(const struct permonst * a0,const char * a1){return a1;}
boolean (has_ceiling)(d_level * a0){append("dependency:has_ceiling:%llu;",(unsigned long long)canonical((uintptr_t)a0));return options[118];}
boolean (is_waterwall)(coordxy a0,coordxy a1){return levl[a0][a1].typ==WATER;}
char * (visctrl)(char a0){append("dependency:visctrl:%d;",(int)a0);return stringbuf;}
char (cmd_from_func)(int (*a0)(void)){append("cmdfunc:%d;",a0==do_reqmenu);return a0==do_reqmenu?77:0;}
int (do_reqmenu)(void){append("dependency:do_reqmenu;");return options[83];}
void (l_nhcore_call)(int a0){append("dependency:l_nhcore_call:%d;",(int)a0);}
char * (ing_suffix)(const char * a0){append("dependency:ing_suffix:%s;",a0?a0:"(null)");return stringbuf;}
const char * (waterbody_name)(coordxy a0,coordxy a1){return "water";}
void (stumble_onto_mimic)(struct monst * a0){append("dependency:stumble_onto_mimic:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
char * (m_monnam)(struct monst * a0){return a0==&gy.youmonst?labels[30]:labels[a0>=mpool&&a0<mpool+8?16+a0-mpool:31];}
char * (mon_nam)(struct monst * a0){return a0==&gy.youmonst?labels[30]:labels[a0>=mpool&&a0<mpool+8?16+a0-mpool:31];}
int (is_safemon)(struct monst * a0){return a0->mpeaceful||a0->mtame;}
boolean (do_attack)(struct monst * a0){append("dependency:do_attack:%llu;",(unsigned long long)canonical((uintptr_t)a0));return options[82];}
boolean (breaktest)(struct obj * a0){append("dependency:breaktest:%llu;",(unsigned long long)canonical((uintptr_t)a0));return options[48];}
struct obj * (splitobj)(struct obj * a0,long a1){append("dependency:splitobj:%llu:%ld;",(unsigned long long)canonical((uintptr_t)a0),(long)a1);return options[229]?&opool[14]:0;}
void (setuwep)(struct obj * a0){append("dependency:setuwep:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
void (freeinv)(struct obj * a0){append("dependency:freeinv:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
void (hit_bars)(struct obj ** a0,coordxy a1,coordxy a2,coordxy a3,coordxy a4,unsigned int a5){append("dependency:hit_bars:%llu:%d:%d:%d:%d:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1,(int)a2,(int)a3,(int)a4,(int)a5);}
int (uwep_skill_type)(void){append("dependency:uwep_skill_type;");return options[261];}
boolean (attacks)(int a0,struct obj * a1){append("dependency:attacks:%d:%llu;",(int)a0,(unsigned long long)canonical((uintptr_t)a1));return options[34];}
char * (bare_artifactname)(struct obj * a0){return "fixture artifact";}
const char * (weapon_descr)(struct obj * a0){return "fixture weapon";}
int (strncmpi)(const char * a0,const char * a1,int a2){for(int i=0;i<a2;i++){unsigned char x=a0[i],y=a1[i];if(x>=65&&x<=90)x+=32;if(y>=65&&y<=90)y+=32;if(x!=y||!x)return x-y;}return 0;}
char * (makeplural)(const char * a0){return a0;}
void (__assert_fail)(const char * a0,const char * a1,int a2,const char * a3){append("assert:%s:%s:%d:%s;",a0,a1,a2,a3);escape_call(3);__builtin_unreachable();}
void (use_skill)(int a0,int a1){append("dependency:use_skill:%d:%d;",(int)a0,(int)a1);}
void (seemimic)(struct monst * a0){append("dependency:seemimic:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
const char * (trapname)(int a0,boolean a1){append("dependency:trapname:%d:%d;",(int)a0,(int)a1);return stringbuf;}
char * (just_an)(char * a0,const char * a1){strcpy(a0,"fixture article");return a0;}
void (place_monster)(struct monst * a0,coordxy a1,coordxy a2){append("dependency:place_monster:%llu:%d:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1,(int)a2);}
int (minliquid)(struct monst * a0){append("dependency:minliquid:%llu;",(unsigned long long)canonical((uintptr_t)a0));return options[159];}
int (mintrap)(struct monst * a0,unsigned int a1){append("dependency:mintrap:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);return options[160];}
void (abuse_dog)(struct monst * a0){append("dependency:abuse_dog:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
void (adjalign)(int a0){append("dependency:adjalign:%d;",(int)a0);}
int (experience)(struct monst * a0,int a1){append("dependency:experience:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);return options[97];}
void (more_experienced)(int a0,int a1){append("dependency:more_experienced:%d:%d;",(int)a0,(int)a1);}
void (newexplevel)(void){append("dependency:newexplevel;");}
void (You_feel)(const char * a0,...){va_list ap;va_start(ap,a0);message("You_feel",a0,ap);va_end(ap);}
boolean (attacktype)(struct permonst * a0,int a1){append("dependency:attacktype:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);return options[35];}
boolean (accessible)(coordxy a0,coordxy a1){return ACCESSIBLE(levl[a0][a1].typ);}
int (dig_typ)(struct obj * a0,coordxy a1,coordxy a2){append("dependency:dig_typ:%llu:%d:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1,(int)a2);return options[74];}
char * (ansimpleoname)(struct obj * a0){return labels[a0>=opool&&a0<opool+16?a0-opool:31];}
struct attack * (attacktype_fordmg)(struct permonst * a0,int a1,int a2){append("dependency:attacktype_fordmg:%llu:%d:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1,(int)a2);return options[36]?&attackpool[0]:0;}
void (wake_nearto)(coordxy a0,coordxy a1,int a2){append("dependency:wake_nearto:%d:%d:%d;",(int)a0,(int)a1,(int)a2);}
int (explum)(struct monst * a0,struct attack * a1){append("dependency:explum:%llu:%llu;",(unsigned long long)canonical((uintptr_t)a0),(unsigned long long)canonical((uintptr_t)a1));return options[98];}
void (rehumanize)(void){append("dependency:rehumanize;");}
void (water_friction)(void){append("dependency:water_friction;");}
boolean (is_ice)(coordxy a0,coordxy a1){return isok(a0,a1)&&levl[a0][a1].typ==ICE;}
boolean (objdescr_is)(struct obj * a0,const char * a1){return options[174];}
boolean (Resists_Elem)(struct monst * a0,int a1){append("dependency:Resists_Elem:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);return options[9];}
void (confdir)(boolean a0){append("dependency:confdir:%d;",(int)a0);}
NhRegion * (visible_region_at)(coordxy a0,coordxy a1){return options[264]?&regions[a0==u.ux&&a1==u.uy?0:1]:0;}
int (reg_damg)(NhRegion * a0){return a0==&regions[1]?options[903]:0;}
void (nh_snprintf)(const char * a0,int a1,char * a2,size_t a3,const char * a4,...){append("snprintf:%s:%d:%lu;",a0,a1,a3);va_list ap;va_start(ap,a4);vsnprintf(a2,a3,a4,ap);va_end(ap);}
boolean (paranoid_query)(boolean a0,const char * a1){append("query:%d:%s;",a0,a1);return options[181];}
int (immune_to_trap)(struct monst * a0,unsigned int a1){append("dependency:immune_to_trap:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);return options[124];}
boolean (into_vs_onto)(int a0){append("dependency:into_vs_onto:%d;",(int)a0);return options[132];}
const char * (directionname)(int a0){return "direction";}
void (set_ustuck)(struct monst * a0){append("ustuck:%llu;",(unsigned long long)canonical((uintptr_t)a0));u.ustuck=a0;}
boolean (sticks)(struct permonst * a0){append("dependency:sticks:%llu;",(unsigned long long)canonical((uintptr_t)a0));return options[234];}
void (maybe_adjust_hero_bubble)(void){append("dependency:maybe_adjust_hero_bubble;");}
void (u_on_newpos)(coordxy a0,coordxy a1){append("dependency:u_on_newpos:%d:%d;",(int)a0,(int)a1);}
int (mon_visible)(struct monst * a0){return !a0->minvis;}
boolean (unmap_invisible)(coordxy a0,coordxy a1){append("dependency:unmap_invisible:%d:%d;",(int)a0,(int)a1);return options[253];}
boolean (stucksteed)(boolean a0){append("dependency:stucksteed:%d;",(int)a0);return options[242];}
void (reset_utrap)(boolean a0){append("dependency:reset_utrap:%d;",(int)a0);}
boolean (drag_ball)(coordxy a0,coordxy a1,int * a2,coordxy * a3,coordxy * a4,coordxy * a5,coordxy * a6,boolean * a7,boolean a8){*a2=0;*a3=1;*a4=2;*a5=3;*a6=4;*a7=0;append("drag:%d:%d:%d;",a0,a1,a8);return !options[90];}
boolean (in_out_region)(coordxy a0,coordxy a1){append("dependency:in_out_region:%d:%d;",(int)a0,(int)a1);return options[126];}
void (m_postmove_effect)(struct monst * a0){append("dependency:m_postmove_effect:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
void (exercise_steed)(void){append("dependency:exercise_steed;");}
void (reset_occupations)(void){append("dependency:reset_occupations;");}
boolean (hideunder)(struct monst * a0){append("dependency:hideunder:%llu;",(unsigned long long)canonical((uintptr_t)a0));return options[120];}
void (check_leash)(coordxy a0,coordxy a1){append("dependency:check_leash:%d:%d;",(int)a0,(int)a1);}
void (vision_recalc)(int a0){append("dependency:vision_recalc:%d;",(int)a0);}
void (move_bc)(int a0,int a1,coordxy a2,coordxy a3,coordxy a4,coordxy a5){append("dependency:move_bc:%d:%d:%d:%d:%d:%d;",(int)a0,(int)a1,(int)a2,(int)a3,(int)a4,(int)a5);}
void (curs_on_u)(void){append("dependency:curs_on_u;");}
boolean (can_reach_floor)(boolean a0){return !options[54];}
struct engr * (engr_at)(coordxy a0,coordxy a1){append("dependency:engr_at:%d:%d;",(int)a0,(int)a1);return options[94]?&engrpool[0]:0;}
void (wipe_engr_at)(coordxy a0,coordxy a1,xint16 a2,boolean a3){append("dependency:wipe_engr_at:%d:%d:%d:%d;",(int)a0,(int)a1,(int)a2,(int)a3);}
void (fall_asleep)(int a0,boolean a1){append("dependency:fall_asleep:%d:%d;",(int)a0,(int)a1);}
void (gethungry)(void){append("dependency:gethungry;");}
boolean (On_stairs)(coordxy a0,coordxy a1){append("dependency:On_stairs:%d:%d;",(int)a0,(int)a1);return options[8];}
const char * (body_part)(int a0){return "body";}
schar (db_under_typ)(int a0){append("dependency:db_under_typ:%d;",(int)a0);return options[69];}
void (float_up)(void){append("dependency:float_up;");}
void (back_on_ground)(boolean a0){append("dependency:back_on_ground:%d;",(int)a0);}
void (docrt)(void){append("dependency:docrt;");}
void (dismount_steed)(int a0){append("dependency:dismount_steed:%d;",(int)a0);}
boolean (lava_effects)(void){append("dependency:lava_effects;");return options[145];}
boolean (drown)(void){append("dependency:drown;");return options[91];}
void (incr_itimeout)(long * a0,int a1){append("itimeout:%ld:%ld;",*a0,a1);*a0+=a1;}
int (float_down)(long a0,long a1){append("dependency:float_down:%ld:%ld;",(long)a0,(long)a1);return options[105];}
int (pickup)(int a0){append("pickup:%d;",a0);if(options[905]&&!reentered){reentered=1;if(options[906])u.ux++;spoteffects(1);}return options[185];}
void (dotrap)(struct trap * a0,unsigned int a1){append("dependency:dotrap:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);}
long (spot_time_left)(coordxy a0,coordxy a1,short a2){append("dependency:spot_time_left:%d:%d:%d;",(int)a0,(int)a1,(int)a2);return options[231];}
char * (Amonnam)(struct monst * a0){return a0==&gy.youmonst?labels[30]:labels[a0>=mpool&&a0<mpool+8?16+a0-mpool:31];}
const char * (ceiling)(coordxy a0,coordxy a1){return "ceiling";}
boolean (hard_helmet)(struct obj * a0){append("dependency:hard_helmet:%llu;",(unsigned long long)canonical((uintptr_t)a0));return options[117];}
const char * (helm_simple_name)(struct obj * a0){return "fixture helmet";}
int (d)(int a0,int a1){int v=0;for(int i=0;i<a0;i++)v+=1+roll(a1);append("d:%d:%d:%d;",a0,a1,v);return v;}
void (mdamageu)(struct monst * a0,int a1){append("dependency:mdamageu:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);}
void (mnexto)(struct monst * a0,unsigned int a1){append("dependency:mnexto:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);}
boolean (inside_room)(struct mkroom * a0,coordxy a1,coordxy a2){return a1>=a0->lx&&a1<=a0->hx&&a2>=a0->ly&&a2<=a0->hy;}
void (u_left_shop)(char * a0,boolean a1){append("dependency:u_left_shop:%s:%d;",a0?a0:"(null)",(int)a1);}
boolean (In_mines)(d_level * a0){append("dependency:In_mines:%llu;",(unsigned long long)canonical((uintptr_t)a0));return options[5];}
void (record_achievement)(schar a0){append("dependency:record_achievement:%d;",(int)a0);}
void (u_entered_shop)(char * a0){append("dependency:u_entered_shop:%s;",a0?a0:"(null)");}
int (midnight)(void){append("dependency:midnight;");return options[158];}
void (verbalize)(const char * a0,...){va_list ap;va_start(ap,a0);message("verbalize",a0,ap);va_end(ap);}
const char * (Hello)(struct monst * a0){append("dependency:Hello:%llu;",(unsigned long long)canonical((uintptr_t)a0));return stringbuf;}
void (intemple)(int a0){append("dependency:intemple:%d;",(int)a0);}
void (room_discovered)(int a0){append("dependency:room_discovered:%d;",(int)a0);}
struct mkroom * (search_special)(schar a0){for(int i=0;i<MAXNROFROOMS;i++)if(svr.rooms[i].hx>0&&svr.rooms[i].rtype==a0)return &svr.rooms[i];return 0;}
void (wake_msg)(struct monst * a0,boolean a1){append("dependency:wake_msg:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);}
struct attack * (dmgtype_fromattack)(struct permonst * a0,int a1,int a2){append("dependency:dmgtype_fromattack:%llu:%d:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1,(int)a2);return options[81]?&attackpool[0]:0;}
char * (s_suffix)(const char * a0){return a0;}
boolean (uteetering_at_seen_pit)(struct trap * a0){append("dependency:uteetering_at_seen_pit:%llu;",(unsigned long long)canonical((uintptr_t)a0));return options[260];}
void (rider_cant_reach)(void){append("dependency:rider_cant_reach;");}
int (loot_mon)(struct monst * a0,int * a1,boolean * a2){append("dependency:loot_mon:%llu:%llu:%llu;",(unsigned long long)canonical((uintptr_t)a0),(unsigned long long)canonical((uintptr_t)a1),(unsigned long long)canonical((uintptr_t)a2));return options[148];}
void (pline_xy)(coordxy a0,coordxy a1,const char * a2,...){append("xy:%d:%d;",a0,a1);va_list ap;va_start(ap,a2);message("pline_xy",a2,ap);va_end(ap);}
boolean (noattacks)(struct permonst * a0){append("dependency:noattacks:%llu;",(unsigned long long)canonical((uintptr_t)a0));return options[171];}
boolean (onscary)(coordxy a0,coordxy a1,struct monst * a2){append("dependency:onscary:%d:%d:%llu;",(int)a0,(int)a1,(unsigned long long)canonical((uintptr_t)a2));return options[177];}
void (selection_free)(struct selectionvar * a0,boolean a1){append("selection_free:%d;",a1);}
void (cmdq_clear)(int a0){append("dependency:cmdq_clear:%d;",(int)a0);}
const char * (pmname)(struct permonst * a0,int a1){return a0->pmnames[a1];}
void (urgent_pline)(const char * a0,...){va_list ap;va_start(ap,a0);message("urgent_pline",a0,ap);va_end(ap);}
void (done)(int a0){append("done:%d;",a0);escape_call(2);__builtin_unreachable();}
int (Boots_on)(void){append("Boots_on;");grow();if(options[904]&&!reentered){reentered=1;append("Boots_reenter:%d;",near_capacity());}return options[2];}
void (decl_globals_init)(void){append("dependency:decl_globals_init;");}
void (init_objects)(void){append("init_objects;");}
boolean (CapitalMon)(const char * a0){append("dependency:CapitalMon:%s;",a0?a0:"(null)");return options[3];}
char * (dupstr)(const char * a0){size_t n=strlen(a0)+1;char*p=(char*)(alloc)((unsigned)n);memcpy(p,a0,n);append("dup:%s;",a0);return p;}
char * (simple_typename)(int a0){return "fixture object";}
void (raw_printf)(const char * a0,...){append("dependency:raw_printf:%s;",a0?a0:"(null)");}
void (freedynamicdata)(void){append("freedynamicdata;");}
void (spot_stop_timers)(coordxy a0,coordxy a1,short a2){append("dependency:spot_stop_timers:%d:%d:%d;",(int)a0,(int)a1,(int)a2);}
void (obj_ice_effects)(coordxy a0,coordxy a1,boolean a2){append("dependency:obj_ice_effects:%d:%d:%d;",(int)a0,(int)a1,(int)a2);}
void (panic)(const char * a0,...){va_list ap;va_start(ap,a0);message("panic",a0,ap);va_end(ap);escape_call(1);__builtin_unreachable();}
static void delay_output(void){append("delay;");grow();}
static void raw_output(const char*s){append("raw:%s;",s);grow();}
#ifdef HYBRID_HACK
extern anything * uint_to_any(unsigned int ui);
extern anything * long_to_any(long lng);
extern anything * monst_to_any(struct monst * mtmp);
extern anything * obj_to_any(struct obj * obj);
extern boolean revive_nasty(coordxy x,coordxy y,const char * msg);
extern boolean teleport_hack_test_could_move_onto_boulder(coordxy sx,coordxy sy);
#define could_move_onto_boulder teleport_hack_test_could_move_onto_boulder
extern void teleport_hack_test_dopush(coordxy sx,coordxy sy,coordxy rx,coordxy ry,struct obj * otmp,boolean costly);
#define dopush teleport_hack_test_dopush
extern void teleport_hack_test_cannot_push_msg(struct obj * otmp,coordxy sx,coordxy sy);
#define cannot_push_msg teleport_hack_test_cannot_push_msg
extern int teleport_hack_test_cannot_push(struct obj * otmp,coordxy sx,coordxy sy);
#define cannot_push teleport_hack_test_cannot_push
extern void teleport_hack_test_rock_disappear_msg(struct obj * otmp);
#define rock_disappear_msg teleport_hack_test_rock_disappear_msg
extern void teleport_hack_test_moverock_done(coordxy sx,coordxy sy);
#define moverock_done teleport_hack_test_moverock_done
extern int teleport_hack_test_moverock(void);
#define moverock teleport_hack_test_moverock
extern int teleport_hack_test_moverock_core(coordxy sx,coordxy sy);
#define moverock_core teleport_hack_test_moverock_core
extern int still_chewing(coordxy x,coordxy y);
extern void movobj(struct obj * obj,coordxy ox,coordxy oy);
extern void teleport_hack_test_dosinkfall(void);
#define dosinkfall teleport_hack_test_dosinkfall
extern boolean may_dig(coordxy x,coordxy y);
extern boolean may_passwall(coordxy x,coordxy y);
extern boolean bad_rock(struct permonst * mdat,coordxy x,coordxy y);
extern int cant_squeeze_thru(struct monst * mon);
extern boolean invocation_pos(coordxy x,coordxy y);
extern boolean test_move(coordxy ux,coordxy uy,coordxy dx,coordxy dy,int mode);
extern boolean teleport_hack_test_findtravelpath(int mode);
#define findtravelpath teleport_hack_test_findtravelpath
extern boolean is_valid_travelpt(coordxy x,coordxy y);
extern boolean teleport_hack_test_trapmove(coordxy x,coordxy y,struct trap * desttrap);
#define trapmove teleport_hack_test_trapmove
extern boolean u_rooted(void);
extern void notice_mon(struct monst * mtmp);
extern int teleport_hack_test_notice_mons_cmp(const void * ptr1,const void * ptr2);
#define notice_mons_cmp teleport_hack_test_notice_mons_cmp
extern void notice_all_mons(boolean reset);
extern void impact_disturbs_zombies(struct obj * obj,boolean violent);
extern void disturb_buried_zombies(coordxy x,coordxy y);
extern const char * u_locomotion(const char * def);
extern schar teleport_hack_test_u_simple_floortyp(coordxy x,coordxy y);
#define u_simple_floortyp teleport_hack_test_u_simple_floortyp
extern boolean handle_tip(int tip);
extern boolean teleport_hack_test_swim_move_danger(coordxy x,coordxy y);
#define swim_move_danger teleport_hack_test_swim_move_danger
extern boolean teleport_hack_test_domove_bump_mon(struct monst * mtmp,int glyph);
#define domove_bump_mon teleport_hack_test_domove_bump_mon
extern boolean teleport_hack_test_domove_attackmon_at(struct monst * mtmp,coordxy x,coordxy y,boolean * displaceu);
#define domove_attackmon_at teleport_hack_test_domove_attackmon_at
extern boolean teleport_hack_test_domove_fight_ironbars(coordxy x,coordxy y);
#define domove_fight_ironbars teleport_hack_test_domove_fight_ironbars
extern boolean teleport_hack_test_domove_fight_web(coordxy x,coordxy y);
#define domove_fight_web teleport_hack_test_domove_fight_web
extern boolean teleport_hack_test_domove_swap_with_pet(struct monst * mtmp,coordxy x,coordxy y);
#define domove_swap_with_pet teleport_hack_test_domove_swap_with_pet
extern boolean teleport_hack_test_domove_fight_empty(coordxy x,coordxy y);
#define domove_fight_empty teleport_hack_test_domove_fight_empty
extern boolean teleport_hack_test_air_turbulence(void);
#define air_turbulence teleport_hack_test_air_turbulence
extern boolean teleport_hack_test_water_turbulence(coordxy * x,coordxy * y);
#define water_turbulence teleport_hack_test_water_turbulence
extern void teleport_hack_test_slippery_ice_fumbling(void);
#define slippery_ice_fumbling teleport_hack_test_slippery_ice_fumbling
extern boolean u_maybe_impaired(void);
extern boolean teleport_hack_test_impaired_movement(coordxy * x,coordxy * y);
#define impaired_movement teleport_hack_test_impaired_movement
extern boolean teleport_hack_test_avoid_moving_on_trap(coordxy x,coordxy y,boolean msg);
#define avoid_moving_on_trap teleport_hack_test_avoid_moving_on_trap
extern boolean teleport_hack_test_avoid_moving_on_liquid(coordxy x,coordxy y,boolean msg);
#define avoid_moving_on_liquid teleport_hack_test_avoid_moving_on_liquid
extern boolean teleport_hack_test_avoid_running_into_trap_or_liquid(coordxy x,coordxy y);
#define avoid_running_into_trap_or_liquid teleport_hack_test_avoid_running_into_trap_or_liquid
extern boolean teleport_hack_test_avoid_trap_andor_region(coordxy x,coordxy y);
#define avoid_trap_andor_region teleport_hack_test_avoid_trap_andor_region
extern boolean teleport_hack_test_move_out_of_bounds(coordxy x,coordxy y);
#define move_out_of_bounds teleport_hack_test_move_out_of_bounds
extern boolean teleport_hack_test_carrying_too_much(void);
#define carrying_too_much teleport_hack_test_carrying_too_much
extern boolean teleport_hack_test_escape_from_sticky_mon(coordxy x,coordxy y);
#define escape_from_sticky_mon teleport_hack_test_escape_from_sticky_mon
extern void domove(void);
extern void teleport_hack_test_domove_core(void);
#define domove_core teleport_hack_test_domove_core
extern void runmode_delay_output(void);
extern void teleport_hack_test_maybe_smudge_engr(coordxy x1,coordxy y1,coordxy x2,coordxy y2);
#define maybe_smudge_engr teleport_hack_test_maybe_smudge_engr
extern void overexert_hp(void);
extern boolean overexertion(void);
extern void invocation_message(void);
extern void classify_terrain(void);
extern void switch_terrain(void);
extern void set_uinwater(int in_out);
extern boolean pooleffects(boolean newspot);
extern void spoteffects(boolean pick);
extern struct monst * teleport_hack_test_monstinroom(struct permonst * mdat,int roomno);
#define monstinroom teleport_hack_test_monstinroom
extern boolean teleport_hack_test_furniture_present(int furniture,int roomno);
#define furniture_present teleport_hack_test_furniture_present
extern char * in_rooms(coordxy x,coordxy y,int typewanted);
extern boolean in_town(coordxy x,coordxy y);
extern void teleport_hack_test_move_update(boolean newlev);
#define move_update teleport_hack_test_move_update
extern void check_special_room(boolean newlev);
extern int teleport_hack_test_pickup_checks(void);
#define pickup_checks teleport_hack_test_pickup_checks
extern int dopickup(void);
extern void lookaround(void);
extern boolean doorless_door(coordxy x,coordxy y);
extern boolean crawl_destination(coordxy x,coordxy y);
extern int monster_nearby(void);
extern void end_running(boolean and_travel);
extern void nomul(int nval);
extern void unmul(const char * msg_override);
extern void teleport_hack_test_maybe_wail(void);
#define maybe_wail teleport_hack_test_maybe_wail
extern void showdamage(int dmg);
extern void losehp(int n,const char * knam,schar k_format);
extern int weight_cap(void);
extern int inv_weight(void);
extern int calc_capacity(int xtra_wt);
extern int near_capacity(void);
extern int max_capacity(void);
extern boolean check_capacity(const char * str);
extern void dump_weights(void);
extern int teleport_hack_test_cmp_weights(const void * p1,const void * p2);
#define cmp_weights teleport_hack_test_cmp_weights
extern int inv_cnt(boolean incl_gold);
extern long money_cnt(struct obj * otmp);
extern void spot_checks(coordxy x,coordxy y,schar old_typ);
extern int rounddiv(long x,int y);
#else
#define TELEPORT_REFERENCE_TU 1
#include "../.cache/wasm64-build/tree/src/hack.c"
#endif
#include "../nethack-c/wasm/tu-fragments/hack-support.c"
#include "tu-hack-layout.h"
static struct weight_table_entry comparator_weights[2];
static uint64_t canonical(uint64_t value){
#define REGION(v,id) if(value>=(uintptr_t)&(v)&&value<(uintptr_t)&(v)+sizeof(v))return ((uint64_t)(id)<<48)+(value-(uintptr_t)&(v))
REGION(mpool,1);
REGION(opool,2);
REGION(traps,3);
REGION(engrpool,4);
REGION(cmdpool,5);
REGION(extpool,6);
REGION(regions,7);
REGION(selection,8);
REGION(selected,9);
REGION(levelarg,10);
REGION(counters,11);
REGION(shorts,12);
REGION(ints,13);
REGION(monrefs,14);
REGION(objrefs,15);
REGION(input,16);
REGION(labels,17);
REGION(stringbuf,18);
REGION(vis,19);
REGION(visrows,20);
REGION(gt,21);
REGION(cg,22);
REGION(svl,23);
REGION(mons,24);
REGION(u,25);
REGION(gy,26);
REGION(gi,27);
REGION(gb,28);
REGION(svm,29);
REGION(flags,30);
REGION(svc,31);
REGION(svd,32);
REGION(gv,33);
REGION(objects,34);
REGION(uarmf,35);
REGION(uleft,36);
REGION(uright,37);
REGION(svi,38);
REGION(uwep,39);
REGION(defsyms,40);
REGION(iflags,41);
REGION(xdir,42);
REGION(dirs_ord,43);
REGION(ydir,44);
REGION(windowprocs,45);
REGION(a11y,46);
REGION(uswapwep,47);
REGION(svq,48);
REGION(gd,49);
REGION(gk,50);
REGION(disp,51);
REGION(uball,52);
REGION(c_common_strings,53);
REGION(gm,54);
REGION(gn,55);
REGION(uarmh,56);
REGION(svr,57);
REGION(svp,58);
REGION(gc,59);
REGION(ga,60);
REGION(gw,61);
REGION(gu,62);
REGION(svk,63);
REGION(obj_descr,64);
REGION(comparator_weights,65);
REGION(attackpool,66);
#undef REGION
for(int i=allocated-1;i>=0;i--)if(value>=allocations[i].pointer&&value<allocations[i].pointer+allocations[i].bytes)return (0x7000ULL<<48)+((uint64_t)i<<32)+(value-allocations[i].pointer);
#ifdef HYBRID_HACK
if(value>=(uintptr_t)teleport_hack_in_rooms_buf&&value<=(uintptr_t)teleport_hack_in_rooms_buf+4)return (0x7fffULL<<48)+(value-(uintptr_t)teleport_hack_in_rooms_buf);
#else
if(rooms_base&&value>=rooms_base&&value<=rooms_base+4)return(0x7fffULL<<48)+(value-rooms_base);
#endif
return value;}
void probe_reset(void){
memset(&gt,0,sizeof gt);
memset(&svl,0,sizeof svl);
memset(&u,0,sizeof u);
memset(&gy,0,sizeof gy);
memset(&gi,0,sizeof gi);
memset(&gb,0,sizeof gb);
memset(&svm,0,sizeof svm);
memset(&flags,0,sizeof flags);
memset(&svc,0,sizeof svc);
memset(&svd,0,sizeof svd);
memset(&gv,0,sizeof gv);
memset(&objects,0,sizeof objects);
memset(&uarmf,0,sizeof uarmf);
memset(&uleft,0,sizeof uleft);
memset(&uright,0,sizeof uright);
memset(&svi,0,sizeof svi);
memset(&uwep,0,sizeof uwep);
memset(&iflags,0,sizeof iflags);
memset(&windowprocs,0,sizeof windowprocs);
memset(&a11y,0,sizeof a11y);
memset(&uswapwep,0,sizeof uswapwep);
memset(&svq,0,sizeof svq);
memset(&gd,0,sizeof gd);
memset(&gk,0,sizeof gk);
memset(&disp,0,sizeof disp);
memset(&uball,0,sizeof uball);
memset(&gm,0,sizeof gm);
memset(&gn,0,sizeof gn);
memset(&uarmh,0,sizeof uarmh);
memset(&svr,0,sizeof svr);
memset(&svp,0,sizeof svp);
memset(&gc,0,sizeof gc);
memset(&ga,0,sizeof ga);
memset(&gw,0,sizeof gw);
memset(&gu,0,sizeof gu);
memset(&svk,0,sizeof svk);
memset(&obj_descr,0,sizeof obj_descr);
memset(&mpool,0,sizeof mpool);
memset(&opool,0,sizeof opool);
memset(&traps,0,sizeof traps);
memset(&engrpool,0,sizeof engrpool);
memset(&cmdpool,0,sizeof cmdpool);
memset(&extpool,0,sizeof extpool);
memset(&regions,0,sizeof regions);
memset(&selection,0,sizeof selection);
memset(&selected,0,sizeof selected);
memset(&levelarg,0,sizeof levelarg);
memset(&counters,0,sizeof counters);
memset(&shorts,0,sizeof shorts);
memset(&ints,0,sizeof ints);
memset(&monrefs,0,sizeof monrefs);
memset(&objrefs,0,sizeof objrefs);
memset(&input,0,sizeof input);
memset(&labels,0,sizeof labels);
memset(&stringbuf,0,sizeof stringbuf);
memset(&vis,0,sizeof vis);
memset(&visrows,0,sizeof visrows);
memset(options,0,sizeof options);tracepos=0;tracebuf[0]=0;seed=1;reentered=0;error_code=0;allocated=0;if(growth){free(growth);growth=0;}
windowprocs.name="tty";windowprocs.wp_id=wp_tty;windowprocs.win_delay_output=delay_output;windowprocs.win_raw_print=raw_output;
for(int y=0;y<ROWNO;y++){visrows[y]=vis[y];for(int x=0;x<COLNO;x++){levl[x][y].typ=ROOM;levl[x][y].seenv=255;vis[y][x]=IN_SIGHT|COULD_SEE;}}gv.viz_array=visrows;
for(int i=0;i<NUMMONS+1;i++){mons[i].mlet=S_HUMAN;mons[i].mlevel=5;mons[i].mr=0;mons[i].maligntyp=0;mons[i].msound=0;mons[i].msize=MZ_MEDIUM;mons[i].cwt=1450;mons[i].mflags1=mons[i].mflags2=mons[i].mflags3=0;mons[i].mresists=0;}
for(int i=0;i<NUM_OBJECTS;i++){objects[i].oc_name_idx=i;objects[i].oc_class=WEAPON_CLASS;objects[i].oc_subtyp=P_LONG_SWORD;objects[i].oc_material=IRON;objects[i].oc_weight=10;obj_descr[i].oc_name="fixture object";}
for(int i=0;i<32;i++)snprintf(labels[i],sizeof labels[i],"name%d",i);
comparator_weights[0].nm=labels[0];comparator_weights[0].wt=10;comparator_weights[1].nm=labels[1];comparator_weights[1].wt=20;
for(int i=0;i<8;i++){mpool[i].data=&mons[PM_HUMAN];mpool[i].m_id=100+i;mpool[i].mhp=20;mpool[i].mhpmax=30;mpool[i].m_lev=5;mpool[i].mx=30+i;mpool[i].my=10;monrefs[i]=&mpool[i];objrefs[i]=&opool[i];}
for(int i=0;i<16;i++){opool[i].quan=1;opool[i].otyp=LONG_SWORD;opool[i].oclass=WEAPON_CLASS;opool[i].where=OBJ_INVENT;}
u.ux=u.ux0=20;u.uy=u.uy0=10;u.dx=1;u.dy=0;u.tx=21;u.ty=10;u.uz.dnum=1;u.uz.dlevel=3;u.ulevel=10;u.uhp=u.uhpmax=40;u.uen=u.uenmax=30;u.mh=u.mhmax=50;u.umonnum=u.umonster=PM_HUMAN;gu.urole.mnum=PM_ARCHEOLOGIST;gu.urole.name.m="Fixture";gu.urace.mnum=PM_HUMAN;gy.youmonst.data=&mons[PM_HUMAN];
rooms_base=(uintptr_t)in_rooms(0,0,0)-4;
levelarg.dnum=1;levelarg.dlevel=4;strcpy(input,"fixture input");strcpy(stringbuf,"fixture text");options[901]=1;cmdpool[0].ec_entry=&extpool[0];cmdpool[0].typ=CMDQ_EXTCMD;extpool[0].ef_funct=dokick;
}
void probe_option(int i,int v){if(i<0||i>=1024)abort();options[i]=v;}
void*probe_pointer(int k,int i){switch(k){case 0:return &mpool[i];case 1:return &opool[i];case 2:return &mons[i];case 3:return &objects[i];case 4:return &traps[i];case 5:return input;case 6:return &gy.youmonst;case 7:return &levelarg;case 8:return &counters[i];case 9:return &shorts[i];case 10:return &ints[i];case 11:return &objrefs[i];case 12:return &monrefs[i];case 13:return labels[i];case 14:return &engrpool[i];case 15:return &regions[i];case 16:return &cmdpool[i];case 17:return &comparator_weights[i];default:abort();}}
uint64_t probe_canonical(uint64_t p){return canonical(p);}
const char*probe_trace(void){return tracebuf;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
int probe_layout_count(void){return sizeof hack_layout/sizeof hack_layout[0];}
const char*probe_layout_name(int i){return hack_layout[i].name;}
uint64_t probe_layout_value(int i){return hack_layout[i].value;}
int probe_error(void){return error_code;}
int probe_pointer_equal(uint64_t a,uint64_t b){return (void*)(uintptr_t)a==(void*)(uintptr_t)b;}
uintptr_t probe_callback_pointer(int kind){return teleport_hack_function_pointer(kind);}
int probe_invoke_comparator(int kind,const void*a,const void*b){return ((int(*)(const void*,const void*))teleport_hack_function_pointer(kind))(a,b);}
uintptr_t probe_foreign_callback(int kind){return teleport_hack_foreign_function_pointer(kind);}
void probe_set_afternmv(int enabled){ga.afternmv=enabled?Boots_on:0;}
void probe_place_object(int i,coordxy x,coordxy y){place_object(&opool[i],x,y);}
void probe_room(int i,coordxy lx,coordxy hx,coordxy ly,coordxy hy,int subrooms,int type){svr.rooms[i].lx=lx;svr.rooms[i].hx=hx;svr.rooms[i].ly=ly;svr.rooms[i].hy=hy;svr.rooms[i].nsubrooms=subrooms;svr.rooms[i].rtype=type;}
int probe_test_constant(int i){switch(i){case 0:return PM_HUMAN;case 1:return DO_MOVE;case 2:return TEST_MOVE;case 3:return TEST_TRAV;case 4:return TEST_TRAP;case 5:return ALTAR;case 6:return NO_KILLER_PREFIX;case 7:return ROOM;case 8:return ROWNO;case 9:return COLNO;case 10:return OBJ_FLOOR;case 11:return ARROW_TRAP;default:abort();}}
static const char*option_names[]={"Amonnam","Boots_off","Boots_on","CapitalMon","Hello","In_mines","Invocation_lev","Norep","On_stairs","Resists_Elem","Ring_off","The","There","Tobjnam","YMonnam","You","You_cant","You_feel","You_hear","Your","__assert_fail","a_monnam","abuse_dog","accessible","acurr","acurrstr","add_damage","add_to_migration","addtobill","adjalign","alloc","an","ansimpleoname","assign_level","attacks","attacktype","attacktype_fordmg","autopick_testobj","b_trapped","back_on_ground","back_to_glyph","bare_artifactname","block_door","block_entry","block_point","blow_up_landmine","body_part","boulder_hits_pool","breaktest","buried_ball","buried_ball_to_punishment","bury_objs","can_fog","can_ooze","can_reach_floor","canseemon","carrying","ceiling","check_leash","climb_pit","closed_door","cmd_from_func","cmdq_clear","cmdq_peek","confdir","costly_spot","curr_mon_load","curs_on_u","d","db_under_typ","decl_globals_init","delobj","deltrap","depth","dig_typ","directionname","dismount_steed","dissolve_bars","dist2","distmin","dmgtype","dmgtype_fromattack","do_attack","do_reqmenu","docrt","dokick","doname","done","doopen_indir","dotrap","drag_ball","drown","dupstr","enexto","engr_at","exercise","exercise_steed","experience","explum","ext_func_tab_from_func","fall_asleep","feel_location","feeltrap","fill_pit","find_objowner","float_down","float_up","float_vs_flight","flooreffects","free","freedynamicdata","freeinv","get_level","gethungry","glyph_at","glyph_to_cmap","goodpos","hard_helmet","has_ceiling","helm_simple_name","hideunder","highc","hit_bars","hliquid","immune_to_trap","impossible","in_out_region","incr_itimeout","ing_suffix","init_objects","inside_room","intemple","into_vs_onto","is_art","is_db_wall","is_ice","is_lava","is_pool","is_pool_or_lava","is_safemon","is_waterwall","isok","just_an","l_nhcore_call","launch_obj","lava_effects","livelog_printf","locomotion","loot_mon","m_monnam","m_postmove_effect","makeplural","map_invisible","map_object","maybe_adjust_hero_bubble","maybe_unhide_at","mdamageu","memset","midnight","minliquid","mintrap","mnexto","mon_nam","mon_visible","more_experienced","morehungry","move_bc","newexplevel","newsym","nh_deterministic_qsort","nh_snprintf","noattacks","obj_extract_self","obj_ice_effects","objdescr_is","off_msg","on_level","onscary","onshopbill","otense","panic","paranoid_query","passes_bars","pay_for_damage","peek_timer","pickup","place_monster","place_object","pline","pline_The","pline_dir","pline_xy","pmname","random_teleport_level","raw_printf","recalc_block_point","record_achievement","reg_damg","rehumanize","remove_object","reset_occupations","reset_utrap","revive_corpse","rider_cant_reach","rloc_to","rloco","rn2","rnd","rng_log_enabled","rng_log_set_caller","room_discovered","s_suffix","search_special","seemimic","seetrap","selection_free","selection_getpoint","selection_new","selection_setpoint","selftouch","sensemon","set_msg_xy","set_ustuck","setuwep","sgn","shop_keeper","simple_typename","sobj_at","sokoban_guilt","splitobj","spot_stop_timers","spot_time_left","sprintf","start_timer","sticks","stolen_value","stop_donning","stop_timer","strchr","strcmp","strcpy","strncmpi","stucksteed","stumble_onto_mimic","subfrombill","surface","t_at","the","tmp_at","trapname","u_entered_shop","u_left_shop","u_on_newpos","unmap_invisible","unmap_object","upstart","urgent_pline","use_pick_axe2","use_skill","useupf","uteetering_at_seen_pit","uwep_skill_type","verbalize","visctrl","visible_region_at","vision_recalc","wake_msg","wake_nearto","watch_dig","water_friction","waterbody_name","weapon_descr","wipe_engr_at","worm_cross","x_monnam","xname","xytodir","y_monnam"};
const char*probe_option_name(int i){return i<278?option_names[i]:0;}
anything * probe_call_uint_to_any(unsigned int ui){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}anything * result=uint_to_any(ui);escape_depth--;return result;}
anything * probe_call_long_to_any(long lng){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}anything * result=long_to_any(lng);escape_depth--;return result;}
anything * probe_call_monst_to_any(struct monst * mtmp){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}anything * result=monst_to_any(mtmp);escape_depth--;return result;}
anything * probe_call_obj_to_any(struct obj * obj){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}anything * result=obj_to_any(obj);escape_depth--;return result;}
boolean probe_call_revive_nasty(coordxy x,coordxy y,const char * msg){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}boolean result=revive_nasty(x,y,msg);escape_depth--;return result;}
boolean probe_call_could_move_onto_boulder(coordxy sx,coordxy sy){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}boolean result=could_move_onto_boulder(sx,sy);escape_depth--;return result;}
void probe_call_dopush(coordxy sx,coordxy sy,coordxy rx,coordxy ry,struct obj * otmp,boolean costly){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return;}dopush(sx,sy,rx,ry,otmp,costly);escape_depth--;}
void probe_call_cannot_push_msg(struct obj * otmp,coordxy sx,coordxy sy){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return;}cannot_push_msg(otmp,sx,sy);escape_depth--;}
int probe_call_cannot_push(struct obj * otmp,coordxy sx,coordxy sy){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}int result=cannot_push(otmp,sx,sy);escape_depth--;return result;}
void probe_call_rock_disappear_msg(struct obj * otmp){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return;}rock_disappear_msg(otmp);escape_depth--;}
void probe_call_moverock_done(coordxy sx,coordxy sy){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return;}moverock_done(sx,sy);escape_depth--;}
int probe_call_moverock(void){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}int result=moverock();escape_depth--;return result;}
int probe_call_moverock_core(coordxy sx,coordxy sy){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}int result=moverock_core(sx,sy);escape_depth--;return result;}
int probe_call_still_chewing(coordxy x,coordxy y){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}int result=still_chewing(x,y);escape_depth--;return result;}
void probe_call_movobj(struct obj * obj,coordxy ox,coordxy oy){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return;}movobj(obj,ox,oy);escape_depth--;}
void probe_call_dosinkfall(void){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return;}dosinkfall();escape_depth--;}
boolean probe_call_may_dig(coordxy x,coordxy y){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}boolean result=may_dig(x,y);escape_depth--;return result;}
boolean probe_call_may_passwall(coordxy x,coordxy y){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}boolean result=may_passwall(x,y);escape_depth--;return result;}
boolean probe_call_bad_rock(struct permonst * mdat,coordxy x,coordxy y){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}boolean result=bad_rock(mdat,x,y);escape_depth--;return result;}
int probe_call_cant_squeeze_thru(struct monst * mon){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}int result=cant_squeeze_thru(mon);escape_depth--;return result;}
boolean probe_call_invocation_pos(coordxy x,coordxy y){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}boolean result=invocation_pos(x,y);escape_depth--;return result;}
boolean probe_call_test_move(coordxy ux,coordxy uy,coordxy dx,coordxy dy,int mode){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}boolean result=test_move(ux,uy,dx,dy,mode);escape_depth--;return result;}
boolean probe_call_findtravelpath(int mode){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}boolean result=findtravelpath(mode);escape_depth--;return result;}
boolean probe_call_is_valid_travelpt(coordxy x,coordxy y){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}boolean result=is_valid_travelpt(x,y);escape_depth--;return result;}
boolean probe_call_trapmove(coordxy x,coordxy y,struct trap * desttrap){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}boolean result=trapmove(x,y,desttrap);escape_depth--;return result;}
boolean probe_call_u_rooted(void){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}boolean result=u_rooted();escape_depth--;return result;}
void probe_call_notice_mon(struct monst * mtmp){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return;}notice_mon(mtmp);escape_depth--;}
int probe_call_notice_mons_cmp(const void * ptr1,const void * ptr2){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}int result=notice_mons_cmp(ptr1,ptr2);escape_depth--;return result;}
void probe_call_notice_all_mons(boolean reset){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return;}notice_all_mons(reset);escape_depth--;}
void probe_call_impact_disturbs_zombies(struct obj * obj,boolean violent){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return;}impact_disturbs_zombies(obj,violent);escape_depth--;}
void probe_call_disturb_buried_zombies(coordxy x,coordxy y){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return;}disturb_buried_zombies(x,y);escape_depth--;}
const char * probe_call_u_locomotion(const char * def){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}const char * result=u_locomotion(def);escape_depth--;return result;}
schar probe_call_u_simple_floortyp(coordxy x,coordxy y){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}schar result=u_simple_floortyp(x,y);escape_depth--;return result;}
boolean probe_call_handle_tip(int tip){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}boolean result=handle_tip(tip);escape_depth--;return result;}
boolean probe_call_swim_move_danger(coordxy x,coordxy y){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}boolean result=swim_move_danger(x,y);escape_depth--;return result;}
boolean probe_call_domove_bump_mon(struct monst * mtmp,int glyph){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}boolean result=domove_bump_mon(mtmp,glyph);escape_depth--;return result;}
boolean probe_call_domove_attackmon_at(struct monst * mtmp,coordxy x,coordxy y,boolean * displaceu){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}boolean result=domove_attackmon_at(mtmp,x,y,displaceu);escape_depth--;return result;}
boolean probe_call_domove_fight_ironbars(coordxy x,coordxy y){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}boolean result=domove_fight_ironbars(x,y);escape_depth--;return result;}
boolean probe_call_domove_fight_web(coordxy x,coordxy y){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}boolean result=domove_fight_web(x,y);escape_depth--;return result;}
boolean probe_call_domove_swap_with_pet(struct monst * mtmp,coordxy x,coordxy y){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}boolean result=domove_swap_with_pet(mtmp,x,y);escape_depth--;return result;}
boolean probe_call_domove_fight_empty(coordxy x,coordxy y){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}boolean result=domove_fight_empty(x,y);escape_depth--;return result;}
boolean probe_call_air_turbulence(void){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}boolean result=air_turbulence();escape_depth--;return result;}
boolean probe_call_water_turbulence(coordxy * x,coordxy * y){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}boolean result=water_turbulence(x,y);escape_depth--;return result;}
void probe_call_slippery_ice_fumbling(void){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return;}slippery_ice_fumbling();escape_depth--;}
boolean probe_call_u_maybe_impaired(void){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}boolean result=u_maybe_impaired();escape_depth--;return result;}
boolean probe_call_impaired_movement(coordxy * x,coordxy * y){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}boolean result=impaired_movement(x,y);escape_depth--;return result;}
boolean probe_call_avoid_moving_on_trap(coordxy x,coordxy y,boolean msg){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}boolean result=avoid_moving_on_trap(x,y,msg);escape_depth--;return result;}
boolean probe_call_avoid_moving_on_liquid(coordxy x,coordxy y,boolean msg){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}boolean result=avoid_moving_on_liquid(x,y,msg);escape_depth--;return result;}
boolean probe_call_avoid_running_into_trap_or_liquid(coordxy x,coordxy y){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}boolean result=avoid_running_into_trap_or_liquid(x,y);escape_depth--;return result;}
boolean probe_call_avoid_trap_andor_region(coordxy x,coordxy y){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}boolean result=avoid_trap_andor_region(x,y);escape_depth--;return result;}
boolean probe_call_move_out_of_bounds(coordxy x,coordxy y){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}boolean result=move_out_of_bounds(x,y);escape_depth--;return result;}
boolean probe_call_carrying_too_much(void){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}boolean result=carrying_too_much();escape_depth--;return result;}
boolean probe_call_escape_from_sticky_mon(coordxy x,coordxy y){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}boolean result=escape_from_sticky_mon(x,y);escape_depth--;return result;}
void probe_call_domove(void){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return;}domove();escape_depth--;}
void probe_call_domove_core(void){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return;}domove_core();escape_depth--;}
void probe_call_runmode_delay_output(void){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return;}runmode_delay_output();escape_depth--;}
void probe_call_maybe_smudge_engr(coordxy x1,coordxy y1,coordxy x2,coordxy y2){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return;}maybe_smudge_engr(x1,y1,x2,y2);escape_depth--;}
void probe_call_overexert_hp(void){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return;}overexert_hp();escape_depth--;}
boolean probe_call_overexertion(void){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}boolean result=overexertion();escape_depth--;return result;}
void probe_call_invocation_message(void){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return;}invocation_message();escape_depth--;}
void probe_call_classify_terrain(void){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return;}classify_terrain();escape_depth--;}
void probe_call_switch_terrain(void){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return;}switch_terrain();escape_depth--;}
void probe_call_set_uinwater(int in_out){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return;}set_uinwater(in_out);escape_depth--;}
boolean probe_call_pooleffects(boolean newspot){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}boolean result=pooleffects(newspot);escape_depth--;return result;}
void probe_call_spoteffects(boolean pick){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return;}spoteffects(pick);escape_depth--;}
struct monst * probe_call_monstinroom(struct permonst * mdat,int roomno){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}struct monst * result=monstinroom(mdat,roomno);escape_depth--;return result;}
boolean probe_call_furniture_present(int furniture,int roomno){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}boolean result=furniture_present(furniture,roomno);escape_depth--;return result;}
char * probe_call_in_rooms(coordxy x,coordxy y,int typewanted){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}char * result=in_rooms(x,y,typewanted);escape_depth--;return result;}
boolean probe_call_in_town(coordxy x,coordxy y){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}boolean result=in_town(x,y);escape_depth--;return result;}
void probe_call_move_update(boolean newlev){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return;}move_update(newlev);escape_depth--;}
void probe_call_check_special_room(boolean newlev){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return;}check_special_room(newlev);escape_depth--;}
int probe_call_pickup_checks(void){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}int result=pickup_checks();escape_depth--;return result;}
int probe_call_dopickup(void){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}int result=dopickup();escape_depth--;return result;}
void probe_call_lookaround(void){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return;}lookaround();escape_depth--;}
boolean probe_call_doorless_door(coordxy x,coordxy y){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}boolean result=doorless_door(x,y);escape_depth--;return result;}
boolean probe_call_crawl_destination(coordxy x,coordxy y){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}boolean result=crawl_destination(x,y);escape_depth--;return result;}
int probe_call_monster_nearby(void){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}int result=monster_nearby();escape_depth--;return result;}
void probe_call_end_running(boolean and_travel){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return;}end_running(and_travel);escape_depth--;}
void probe_call_nomul(int nval){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return;}nomul(nval);escape_depth--;}
void probe_call_unmul(const char * msg_override){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return;}unmul(msg_override);escape_depth--;}
void probe_call_maybe_wail(void){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return;}maybe_wail();escape_depth--;}
void probe_call_showdamage(int dmg){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return;}showdamage(dmg);escape_depth--;}
void probe_call_losehp(int n,const char * knam,schar k_format){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return;}losehp(n,knam,k_format);escape_depth--;}
int probe_call_weight_cap(void){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}int result=weight_cap();escape_depth--;return result;}
int probe_call_inv_weight(void){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}int result=inv_weight();escape_depth--;return result;}
int probe_call_calc_capacity(int xtra_wt){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}int result=calc_capacity(xtra_wt);escape_depth--;return result;}
int probe_call_near_capacity(void){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}int result=near_capacity();escape_depth--;return result;}
int probe_call_max_capacity(void){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}int result=max_capacity();escape_depth--;return result;}
boolean probe_call_check_capacity(const char * str){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}boolean result=check_capacity(str);escape_depth--;return result;}
void probe_call_dump_weights(void){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return;}dump_weights();escape_depth--;}
int probe_call_cmp_weights(const void * p1,const void * p2){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}int result=cmp_weights(p1,p2);escape_depth--;return result;}
int probe_call_inv_cnt(boolean incl_gold){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}int result=inv_cnt(incl_gold);escape_depth--;return result;}
long probe_call_money_cnt(struct obj * otmp){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}long result=money_cnt(otmp);escape_depth--;return result;}
void probe_call_spot_checks(coordxy x,coordxy y,schar old_typ){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return;}spot_checks(x,y,old_typ);escape_depth--;}
int probe_call_rounddiv(long x,int y){error_code=0;if(escape_depth>=16)abort();int index=escape_depth++;if(setjmp(escapes[index])){escape_depth--;return 0;}int result=rounddiv(x,y);escape_depth--;return result;}
