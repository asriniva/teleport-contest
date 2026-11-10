/* Independent configured original-C/JS ARTIFACT policy fixture.
 * EmC memory64 first pass; native macOS and integrated recordings are separate.
 */
#include "hack.h"
#include "artifact.h"
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <emscripten/stack.h>
#include <emscripten/heap.h>
#include "tu-artifact-layout.h"
__typeof__(flags) flags;
__typeof__(gu) gu;
__typeof__(objects) objects;
__typeof__(u) u;
__typeof__(obj_descr) obj_descr;
__typeof__(svb) svb;
__typeof__(gi) gi;
__typeof__(program_state) program_state;
__typeof__(svc) svc;
__typeof__(gv) gv;
__typeof__(gy) gy;
__typeof__(gs) gs;
__typeof__(windowprocs) windowprocs;
__typeof__(iflags) iflags;
__typeof__(disp) disp;
__typeof__(gm) gm;
__typeof__(gn) gn;
__typeof__(svn) svn;
__typeof__(svd) svd;
__typeof__(svl) svl;
__typeof__(svq) svq;
__typeof__(svm) svm;
__typeof__(uwep) uwep;
__typeof__(gw) gw;
__typeof__(uarmg) uarmg;
__typeof__(uleft) uleft;
__typeof__(uright) uright;
__typeof__(uswapwep) uswapwep;
const struct Align aligns[3]={{.value=A_LAWFUL},{.value=A_NEUTRAL},{.value=A_CHAOTIC}};
const struct c_common_strings c_common_strings={.c_Never_mind="Never mind.",.c_nothing_happens="Nothing happens.",.c_nothing_seems_to_happen="Nothing seems to happen.",.c_fakename={"it","you"}};
const struct c_color_names c_color_names={.c_black="black"};
const struct const_globals cg={0};
const glyph_info nul_glyphinfo={0};
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
static struct monst mpool[8];static struct obj opool[16];static struct trap traps[4];static d_level levelarg;static long counters[8];static short shorts[8];static int ints[8];static struct obj*objrefs[8];static menu_item selections[8];static char input[2048],labels[32][80],tracebuf[4194304],stringbuf[256],savebuf[32768];static int tracepos,options[256],seed,reentered,savepos;static void*growth;
static seenV vis[ROWNO][COLNO],*visrows[ROWNO];
static uint64_t canonical(uint64_t);
static void append(const char*fmt,...){if(tracepos>sizeof tracebuf-4096)abort();va_list ap;va_start(ap,fmt);tracepos+=vsnprintf(tracebuf+tracepos,sizeof tracebuf-tracepos,fmt,ap);va_end(ap);}
static void grow(void){if(options[240]&&!growth){growth=malloc(emscripten_get_heap_size()+16*1024*1024);if(!growth)abort();append("growth;");}}
static void message(const char*kind,const char*fmt,va_list ap){char b[4096];vsnprintf(b,sizeof b,fmt,ap);append("%s:%s;",kind,b);grow();}
static int roll(int n){if(n<=0)abort();seed=(unsigned)seed*1664525U+1013904223U;return(unsigned)seed%n;}
void (sfo_arti_info)(NHFILE * a0,struct arti_info * a1,const char * a2){append("sfo_arti_info:%s;",a2);memcpy(savebuf+savepos,a1,sizeof *a1);savepos+=sizeof *a1;}
void (sfo_xint16)(NHFILE * a0,xint16 * a1,const char * a2){append("sfo_xint16:%s;",a2);memcpy(savebuf+savepos,a1,sizeof *a1);savepos+=sizeof *a1;}
void (sfi_arti_info)(NHFILE * a0,struct arti_info * a1,const char * a2){append("sfi_arti_info:%s;",a2);memcpy(a1,savebuf+savepos,sizeof *a1);savepos+=sizeof *a1;}
void (sfi_short)(NHFILE * a0,short * a1,const char * a2){append("sfi_short:%s;",a2);memcpy(a1,savebuf+savepos,sizeof *a1);savepos+=sizeof *a1;}
boolean (rng_log_enabled)(void){return options[241];}
void (rng_log_set_caller)(const char * a0,int a1,const char * a2){append("site:%s:%d:%s;",a0,a1,a2);grow();if(options[242]&&!reentered){reentered=1;append("reentered:%s;",artiname(1));}}
int (rn2)(int a0){int v=roll(a0);append("rn2:%d:%d;",a0,v);return v;}
struct obj * (mksobj)(int a0,boolean a1,boolean a2){append("mksobj:%d:%d:%d;",a0,a1,a2);if(options[243])return 0;opool[15].otyp=a0;return &opool[15];}
struct obj * (oname)(struct obj * a0,const char * a1,unsigned int a2){append("oname:%llu:%s:%u;",(unsigned long long)canonical((uintptr_t)a0),a1,a2);return a0;}
void (obj_extract_self)(struct obj * a0){append("dependency:obj_extract_self:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
void (obfree)(struct obj * a0,struct obj * a1){append("dependency:obfree:%llu:%llu;",(unsigned long long)canonical((uintptr_t)a0),(unsigned long long)canonical((uintptr_t)a1));}
int (strncmpi)(const char * a0,const char * a1,int a2){for(int i=0;a2<0||i<a2;i++){unsigned char x=a0[i],y=a1[i];if(x>=65&&x<=90)x+=32;if(y>=65&&y<=90)y+=32;if(x!=y||!x)return x-y;}return 0;}
boolean (fuzzymatch)(const char * a0,const char * a1,const char * a2,boolean a3){while(1){while(*a0&&strchr(a2,*a0))a0++;while(*a1&&strchr(a2,*a1))a1++;unsigned char x=*a0++,y=*a1++;if(a3){if(x>=65&&x<=90)x+=32;if(y>=65&&y<=90)y+=32;}if(x!=y)return FALSE;if(!x)return TRUE;}}
void (impossible)(const char * a0,...){va_list ap;va_start(ap,a0);message("impossible",a0,ap);va_end(ap);}
char (inside_shop)(coordxy a0,coordxy a1){append("dependency:inside_shop:%d:%d;",(int)a0,(int)a1);return options[59];}
void (livelog_printf)(long a0,const char * a1,...){append("livelog:%ld;",a0);va_list ap;va_start(ap,a1);message("event",a1,ap);va_end(ap);}
char * (bare_artifactname)(struct obj * a0){return labels[a0>=opool&&a0<opool+16?a0-opool:31];}
void (obj_shuffle_range)(int a0,int * a1,int * a2){*a1=a0-1;*a2=a0+1;append("shuffle:%d:%d:%d;",a0,*a1,*a2);}
boolean (make_hallucinated)(long a0,boolean a1,long a2){append("dependency:make_hallucinated:%ld:%d:%ld;",(long)a0,(int)a1,(long)a2);return options[72];}
void (recalc_telepat_range)(void){append("dependency:recalc_telepat_range;");}
void (see_monsters)(void){append("dependency:see_monsters;");}
aligntyp (mon_aligntyp)(struct monst * a0){return a0->data->maligntyp;}
void (You)(const char * a0,...){va_list ap;va_start(ap,a0);message("You",a0,ap);va_end(ap);}
char * (s_suffix)(const char * a0){return (char*)a0;}
char * (the)(const char * a0){return (char*)a0;}
char * (xname)(struct obj * a0){return labels[a0>=opool&&a0<opool+16?a0-opool:31];}
int (d)(int a0,int a1){int v=0;for(int i=0;i<a0;i++)v+=1+roll(a1);append("d:%d:%d:%d;",a0,a1,v);return v;}
boolean (hates_silver)(struct permonst * a0){append("dependency:hates_silver:%llu;",(unsigned long long)canonical((uintptr_t)a0));return options[51];}
int (rnd)(int a0){int v=1+roll(a0);append("rnd:%d:%d;",a0,v);return v;}
void (losehp)(int a0,const char * a1,schar a2){append("losehp:%d:%s:%d;",a0,a1,a2);u.uhp-=a0;}
void (exercise)(int a0,boolean a1){append("dependency:exercise:%d:%d;",(int)a0,(int)a1);}
void (pline)(const char * a0,...){va_list ap;va_start(ap,a0);message("pline",a0,ap);va_end(ap);}
char * (Tobjnam)(struct obj * a0,const char * a1){snprintf(stringbuf,sizeof stringbuf,"%s %s",labels[a0>=opool&&a0<opool+16?a0-opool:31],a1);return stringbuf;}
int (sgn)(int a0){return(a0>0)-(a0<0);}
boolean (defended)(struct monst * a0,int a1){append("dependency:defended:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);return options[28];}
boolean (Resists_Elem)(struct monst * a0,int a1){append("dependency:Resists_Elem:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);return options[4];}
boolean (resists_drli)(struct monst * a0){append("dependency:resists_drli:%llu;",(unsigned long long)canonical((uintptr_t)a0));return options[105];}
const char * (align_str)(aligntyp a0){return a0==A_LAWFUL?"lawful":a0==A_CHAOTIC?"chaotic":"neutral";}
char * (simple_typename)(int a0){return "fixture object";}
void (nh_snprintf)(const char * a0,int a1,char * a2,size_t a3,const char * a4,...){append("snprintf:%s:%d:%lu;",a0,a1,a3);va_list ap;va_start(ap,a4);vsnprintf(a2,a3,a4,ap);va_end(ap);}
void (pline_The)(const char * a0,...){va_list ap;va_start(ap,a0);message("pline_The",a0,ap);va_end(ap);}
char * (vtense)(const char * a0,const char * a1){return (char*)a1;}
int (canseemon)(struct monst * a0){append("dependency:canseemon:%llu;",(unsigned long long)canonical((uintptr_t)a0));return options[23];}
int (sensemon)(struct monst * a0){append("dependency:sensemon:%llu;",(unsigned long long)canonical((uintptr_t)a0));return options[116];}
void (map_invisible)(coordxy a0,coordxy a1){append("dependency:map_invisible:%d:%d;",(int)a0,(int)a1);}
boolean (cancel_monst)(struct monst * a0,struct obj * a1,boolean a2,boolean a3,boolean a4){append("dependency:cancel_monst:%llu:%llu:%d:%d:%d;",(unsigned long long)canonical((uintptr_t)a0),(unsigned long long)canonical((uintptr_t)a1),(int)a2,(int)a3,(int)a4);return options[22];}
char * (mon_nam)(struct monst * a0){return a0==&gy.youmonst?"you":labels[a0>=mpool&&a0<mpool+8?16+a0-mpool:31];}
boolean (attacktype)(struct permonst * a0,int a1){append("dependency:attacktype:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);return options[16];}
void (nomul)(int a0){append("dependency:nomul:%d;",(int)a0);}
boolean (sticks)(struct permonst * a0){append("dependency:sticks:%llu;",(unsigned long long)canonical((uintptr_t)a0));return options[129];}
void (set_ustuck)(struct monst * a0){append("dependency:set_ustuck:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
int (resist)(struct monst * a0,char a1,int a2,int a3){append("dependency:resist:%llu:%d:%d:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1,(int)a2,(int)a3);return options[104];}
void (monflee)(struct monst * a0,int a1,boolean a2,boolean a3){append("dependency:monflee:%llu:%d:%d:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1,(int)a2,(int)a3);}
void (probe_monster)(struct monst * a0){append("dependency:probe_monster:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
void (make_stunned)(long a0,boolean a1){append("dependency:make_stunned:%ld:%d;",(long)a0,(int)a1);}
void (make_confused)(long a0,boolean a1){append("dependency:make_confused:%ld:%d;",(long)a0,(int)a1);}
char * (upstart)(char * a0){if(*a0>='a'&&*a0<='z')*a0-=32;return a0;}
void (shieldeff)(coordxy a0,coordxy a1){append("dependency:shieldeff:%d:%d;",(int)a0,(int)a1);}
int (destroy_items)(struct monst * a0,int a1,int a2){append("dependency:destroy_items:%llu:%d:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1,(int)a2);return options[30];}
void (ignite_items)(struct obj * a0){append("dependency:ignite_items:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
void (burn_away_slime)(void){append("dependency:burn_away_slime;");}
void (wake_nearto)(coordxy a0,coordxy a1,int a2){append("dependency:wake_nearto:%d:%d:%d;",(int)a0,(int)a1,(int)a2);}
char * (Monnam)(struct monst * a0){return a0==&gy.youmonst?"You":labels[a0>=mpool&&a0<mpool+8?16+a0-mpool:31];}
void (observe_object)(struct obj * a0){append("dependency:observe_object:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
const char * (mbodypart)(struct monst * a0,int a1){return "neck";}
const char * (body_part)(int a0){return "neck";}
int (monhp_per_lvl)(struct monst * a0){append("dependency:monhp_per_lvl:%llu;",(unsigned long long)canonical((uintptr_t)a0));return options[85];}
char * (distant_name)(struct obj * a0,char *(*a1)(struct obj *)){append("distant:%llu;",(unsigned long long)canonical((uintptr_t)a0));return a1(a0);}
const char * (hcolor)(const char * a0){return a0;}
char * (The)(const char * a0){return (char*)a0;}
void (healup)(int a0,int a1,boolean a2,boolean a3){append("dependency:healup:%d:%d:%d:%d;",(int)a0,(int)a1,(int)a2,(int)a3);}
int (healmon)(struct monst * a0,int a1,int a2){append("healmon:%llu:%d:%d;",(unsigned long long)canonical((uintptr_t)a0),a1,a2);a0->mhp+=a1;return a1;}
void (You_feel)(const char * a0,...){va_list ap;va_start(ap,a0);message("You_feel",a0,ap);va_end(ap);}
void (losexp)(const char * a0){append("dependency:losexp:%s;",a0?a0:"(null)");}
struct obj * (getobj)(const char * a0,int (*a1)(struct obj *),unsigned int a2){append("getobj:%s:%u;",a0,a2);struct obj*o=options[244]?&opool[options[244]-1]:0;append("callback:%d;",a1(o));return o;}
int (seffects)(struct obj * a0){append("seffects:%d:%d:%d:%d;",a0->otyp,a0->blessed,a0->cursed,a0->oextra!=0);return 0;}
void (make_sick)(long a0,const char * a1,boolean a2,int a3){append("dependency:make_sick:%ld:%s:%d:%d;",(long)a0,a1?a1:"(null)",(int)a2,(int)a3);}
void (make_slimed)(long a0,const char * a1){append("dependency:make_slimed:%ld:%s;",(long)a0,a1?a1:"(null)");}
void (make_blinded)(long a0,boolean a1){append("dependency:make_blinded:%ld:%d;",(long)a0,(int)a1);}
int (untrap)(boolean a0,coordxy a1,coordxy a2,struct obj * a3){append("dependency:untrap:%d:%d:%d:%llu;",(int)a0,(int)a1,(int)a2,(unsigned long long)canonical((uintptr_t)a3));return options[140];}
int (charge_ok)(struct obj * a0){return a0?GETOBJ_SUGGEST:GETOBJ_EXCLUDE;}
void (recharge)(struct obj * a0,int a1){append("dependency:recharge:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);}
void (update_inventory)(void){append("dependency:update_inventory;");}
void (add_menu)(winid a0,const glyph_info * a1,const union any * a2,char a3,char a4,int a5,int a6,const char * a7,unsigned int a8){append("menu:%d:%d:%d:%d:%d:%d:%s:%u;",a0,a2->a_int,a3,a4,a5,a6,a7,a8);grow();}
int (select_menu)(winid a0,int a1,menu_item ** a2){append("select:%d:%d;",a0,a1);if(options[246]>0){*a2=malloc(options[246]*sizeof **a2);memcpy(*a2,selections,options[246]*sizeof **a2);}else *a2=0;return options[246];}
schar (depth)(d_level * a0){append("depth:%d:%d;",a0->dnum,a0->dlevel);return a0->dlevel;}
boolean (next_to_u)(void){append("dependency:next_to_u;");return options[87];}
void (goto_level)(d_level * a0,boolean a1,boolean a2,boolean a3){append("goto:%d:%d:%d:%d:%d;",a0->dnum,a0->dlevel,a1,a2,a3);u.uz=*a0;}
int (weight)(struct obj * a0){append("dependency:weight:%llu;",(unsigned long long)canonical((uintptr_t)a0));return options[147];}
struct obj * (hold_another_object)(struct obj * a0,const char * a1,const char * a2,const char * a3){append("hold:%llu:%s:%s:%s;",(unsigned long long)canonical((uintptr_t)a0),a1,a2,a3?a3:"(null)");return a0;}
char * (aobjnam)(struct obj * a0,const char * a1){snprintf(stringbuf,sizeof stringbuf,"%s %s",labels[a0>=opool&&a0<opool+16?a0-opool:31],a1);return stringbuf;}
void (find_hell)(d_level * a0){a0->dnum=3;a0->dlevel=2;append("findhell; ");}
int (isok)(coordxy a0,coordxy a1){return a0>=1&&a0<COLNO&&a1>=0&&a1<ROWNO;}
boolean (In_quest)(d_level * a0){append("dependency:In_quest:%llu;",(unsigned long long)canonical((uintptr_t)a0));return options[1];}
boolean (In_hell)(d_level * a0){append("dependency:In_hell:%llu;",(unsigned long long)canonical((uintptr_t)a0));return options[0];}
xint16 (dunlevs_in_dungeon)(d_level * a0){append("dunlevs:%d:%d;",a0->dnum,a0->dlevel);return 12;}
void (migrate_mon)(struct monst * a0,xint16 a1,xint16 a2){append("dependency:migrate_mon:%llu:%d:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1,(int)a2);}
xint16 (ledger_no)(d_level * a0){append("ledger:%d:%d;",a0->dnum,a0->dlevel);return a0->dnum*20+a0->dlevel;}
boolean (u_teleport_mon)(struct monst * a0,boolean a1){append("dependency:u_teleport_mon:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);return options[138];}
char * (eos)(char * a0){return a0+strlen(a0);}
int (getdir)(const char * a0){append("dependency:getdir:%s;",a0?a0:"(null)");return options[46];}
void (throwit)(struct obj * a0,long a1,boolean a2,struct obj * a3){append("dependency:throwit:%llu:%ld:%d:%llu;",(unsigned long long)canonical((uintptr_t)a0),(long)a1,(int)a2,(unsigned long long)canonical((uintptr_t)a3));}
int (spell_skilltype)(int a0){append("dependency:spell_skilltype:%d;",(int)a0);return options[125];}
int (spelleffects)(int a0,boolean a1,boolean a2){append("dependency:spelleffects:%d:%d:%d;",(int)a0,(int)a1,(int)a2);return options[126];}
void (do_blinding_ray)(struct obj * a0){append("dependency:do_blinding_ray:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
void (litroom)(boolean a0,struct obj * a1){append("dependency:litroom:%d:%llu;",(int)a0,(unsigned long long)canonical((uintptr_t)a1));}
int (lightdamage)(struct obj * a0,boolean a1,int a2){append("dependency:lightdamage:%llu:%d:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1,(int)a2);return options[65];}
boolean (flashburn)(long a0,boolean a1){append("dependency:flashburn:%ld:%d;",(long)a0,(int)a1);return options[40];}
char * (otense)(struct obj * a0,const char * a1){return (char*)a1;}
int (rnz)(int a0){int v=a0+roll(31);append("rnz:%d:%d;",a0,v);return v;}
void (use_crystal_ball)(struct obj ** a0){append("crystal:%llu;",(unsigned long long)canonical((uintptr_t)*a0));if(options[247])*a0=0;}
void (level_tele)(void){append("dependency:level_tele;");}
void (enlightenment)(int a0,int a1){append("dependency:enlightenment:%d:%d;",(int)a0,(int)a1);}
void (float_up)(void){append("dependency:float_up;");}
void (spoteffects)(boolean a0){append("dependency:spoteffects:%d;",(int)a0);}
int (float_down)(long a0,long a1){append("dependency:float_down:%ld:%ld;",(long)a0,(long)a1);return options[41];}
void (newsym)(coordxy a0,coordxy a1){append("dependency:newsym:%d:%d;",(int)a0,(int)a1);}
void (Your)(const char * a0,...){va_list ap;va_start(ap,a0);message("Your",a0,ap);va_end(ap);}
char * (getrumor)(int a0,char * a1,boolean a2){strcpy(a1,options[245]?"":"fixture rumor");return a1;}
int (bcsign)(struct obj * a0){return a0->blessed?1:a0->cursed?-1:0;}
void (verbalize)(const char * a0,...){va_list ap;va_start(ap,a0);message("verbalize",a0,ap);va_end(ap);}
const char * (clr2colorname)(int a0){return a0==CLR_RED?"red":"fixture color";}
void (maybe_lvltport_feedback)(void){append("dependency:maybe_lvltport_feedback;");}
boolean (invocation_pos)(coordxy a0,coordxy a1){append("dependency:invocation_pos:%d:%d;",(int)a0,(int)a1);return options[60];}
boolean (On_stairs)(coordxy a0,coordxy a1){append("dependency:On_stairs:%d:%d;",(int)a0,(int)a1);return options[3];}
void (You_cant)(const char * a0,...){va_list ap;va_start(ap,a0);message("You_cant",a0,ap);va_end(ap);}
char * (yname)(struct obj * a0){return labels[a0>=opool&&a0<opool+16?a0-opool:31];}
char * (killer_xname)(struct obj * a0){return labels[a0>=opool&&a0<opool+16?a0-opool:31];}
void (remove_worn_item)(struct obj * a0,boolean a1){append("remove_worn:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),a1);a0->owornmask=0;if(options[249]){if(uarmg==a0)uarmg=0;if(uleft==a0)uleft=0;if(uright==a0)uright=0;}if(options[250]&&!reentered){reentered=1;retouch_equipment(0);append("equipment-reentered;");}}
void (freeinv)(struct obj * a0){append("freeinv:%llu;",(unsigned long long)canonical((uintptr_t)a0));struct obj**p=&gi.invent;while(*p){if(*p==a0){*p=a0->nobj;break;}p=&(*p)->nobj;}a0->nobj=0;}
void (hitfloor)(struct obj * a0,boolean a1){append("dependency:hitfloor:%llu:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1);}
const char * (surface)(coordxy a0,coordxy a1){return "floor";}
void (dropx)(struct obj * a0){append("dependency:dropx:%llu;",(unsigned long long)canonical((uintptr_t)a0));}
void (clear_bypasses)(void){append("clear_bypasses; ");for(int i=0;i<16;i++)opool[i].bypass=0;}
void (bypass_obj)(struct obj * a0){append("bypass:%llu;",(unsigned long long)canonical((uintptr_t)a0));if(a0)a0->bypass=1;}
struct obj * (which_armor)(struct monst * a0,long a1){append("dependency:which_armor:%llu:%ld;",(unsigned long long)canonical((uintptr_t)a0),(long)a1);return options[148]?&opool[14]:0;}
void (dismount_steed)(int a0){append("dependency:dismount_steed:%d;",(int)a0);}
struct obj * (nxt_unbypassed_obj)(struct obj * a0){for(;a0;a0=a0->nobj)if(!a0->bypass){a0->bypass=1;return a0;}return 0;}
void (uncurse)(struct obj * a0){append("uncurse:%llu;",(unsigned long long)canonical((uintptr_t)a0));a0->cursed=0;}
void (selftouch)(const char * a0){append("dependency:selftouch:%s;",a0?a0:"(null)");}
int (glyph_at)(coordxy a0,coordxy a1){append("dependency:glyph_at:%d:%d;",(int)a0,(int)a1);return options[49];}
struct trap * (t_at)(coordxy a0,coordxy a1){append("dependency:t_at:%d:%d;",(int)a0,(int)a1);return options[135]?&traps[0]:0;}
struct obj * (nxtobj)(struct obj * a0,int a1,boolean a2){append("dependency:nxtobj:%llu:%d:%d;",(unsigned long long)canonical((uintptr_t)a0),(int)a1,(int)a2);return options[91]?&opool[14]:0;}
static winid cw(int kind){append("create:%d;",kind);grow();return 7;}
static void dw(winid w){append("destroy:%d;",w);}
static void pw(winid w,int attr,const char*s){append("put:%d:%d:%s;",w,attr,s);grow();}
static void display(winid w,boolean block){append("display:%d:%d;",w,block);}
static void sm(winid w,unsigned long behavior){append("start:%d:%lu;",w,behavior);}
static void em(winid w,const char*s){append("end:%d:%s;",w,s?s:"(null)");}
#ifdef HYBRID_ARTIFACT
extern void teleport_artifact_test_hack_artifacts(void);
#define hack_artifacts teleport_artifact_test_hack_artifacts
extern void init_artifacts(void);
extern void save_artifacts(NHFILE * nhfp);
extern void restore_artifacts(NHFILE * nhfp);
extern const char * artiname(int artinum);
extern struct obj * mk_artifact(struct obj * otmp,aligntyp alignment,uchar max_giftvalue,boolean adjust_spe);
extern void teleport_artifact_test_dispose_of_orig_obj(struct obj * obj);
#define dispose_of_orig_obj teleport_artifact_test_dispose_of_orig_obj
extern const char * artifact_name(const char * name,short * otyp_p,boolean fuzzy);
extern boolean exist_artifact(int otyp,const char * name);
extern void artifact_exists(struct obj * otmp,const char * name,boolean mod,unsigned int flgs);
extern void found_artifact(int a);
extern void find_artifact(struct obj * otmp);
extern int nartifact_exist(void);
extern void artifact_origin(struct obj * arti,unsigned int aflags);
extern boolean spec_ability(struct obj * otmp,unsigned long abil);
extern boolean confers_luck(struct obj * obj);
extern boolean arti_reflects(struct obj * obj);
extern boolean shade_glare(struct obj * obj);
extern boolean restrict_name(struct obj * otmp,const char * name);
extern boolean attacks(int adtyp,struct obj * otmp);
extern boolean defends(int adtyp,struct obj * otmp);
extern boolean defends_when_carried(int adtyp,struct obj * otmp);
extern boolean protects(struct obj * otmp,boolean being_worn);
extern void set_artifact_intrinsic(struct obj * otmp,boolean on,long wp_mask);
extern int touch_artifact(struct obj * obj,struct monst * mon);
extern boolean arti_immune(struct obj * obj,int dtyp);
extern boolean teleport_artifact_test_bane_applies(const struct artifact * oart,struct monst * mon);
#define bane_applies teleport_artifact_test_bane_applies
extern int teleport_artifact_test_spec_applies(const struct artifact * weap,struct monst * mtmp);
#define spec_applies teleport_artifact_test_spec_applies
extern long spec_m2(struct obj * otmp);
extern int spec_abon(struct obj * otmp,struct monst * mon);
extern int spec_dbon(struct obj * otmp,struct monst * mon,int tmp);
extern void discover_artifact(xint16 m);
extern boolean undiscovered_artifact(xint16 m);
extern int disp_artifact_discoveries(winid tmpwin);
extern void dump_artifact_info(winid tmpwin);
extern boolean teleport_artifact_test_Mb_hit(struct monst * magr,struct monst * mdef,struct obj * mb,int * dmgptr,int dieroll,boolean vis,char * hittee);
#define Mb_hit teleport_artifact_test_Mb_hit
extern boolean artifact_hit(struct monst * magr,struct monst * mdef,struct obj * otmp,int * dmgptr,int dieroll);
extern int teleport_artifact_test_invoke_ok(struct obj * obj);
#define invoke_ok teleport_artifact_test_invoke_ok
extern int doinvoke(void);
extern void teleport_artifact_test_nothing_special(struct obj * obj);
#define nothing_special teleport_artifact_test_nothing_special
extern int teleport_artifact_test_invoke_taming(struct obj * obj);
#define invoke_taming teleport_artifact_test_invoke_taming
extern int teleport_artifact_test_invoke_healing(struct obj * obj);
#define invoke_healing teleport_artifact_test_invoke_healing
extern int teleport_artifact_test_invoke_energy_boost(struct obj * obj);
#define invoke_energy_boost teleport_artifact_test_invoke_energy_boost
extern int teleport_artifact_test_invoke_untrap(struct obj * obj);
#define invoke_untrap teleport_artifact_test_invoke_untrap
extern int teleport_artifact_test_invoke_charge_obj(struct obj * obj);
#define invoke_charge_obj teleport_artifact_test_invoke_charge_obj
extern int teleport_artifact_test_invoke_create_portal(struct obj * obj);
#define invoke_create_portal teleport_artifact_test_invoke_create_portal
extern int teleport_artifact_test_invoke_create_ammo(struct obj * obj);
#define invoke_create_ammo teleport_artifact_test_invoke_create_ammo
extern int teleport_artifact_test_invoke_banish(struct obj * obj);
#define invoke_banish teleport_artifact_test_invoke_banish
extern int teleport_artifact_test_invoke_fling_poison(struct obj * obj);
#define invoke_fling_poison teleport_artifact_test_invoke_fling_poison
extern int teleport_artifact_test_invoke_storm_spell(struct obj * obj);
#define invoke_storm_spell teleport_artifact_test_invoke_storm_spell
extern int teleport_artifact_test_invoke_blinding_ray(struct obj * obj);
#define invoke_blinding_ray teleport_artifact_test_invoke_blinding_ray
extern int teleport_artifact_test_arti_invoke_cost_pw(struct obj * obj);
#define arti_invoke_cost_pw teleport_artifact_test_arti_invoke_cost_pw
extern boolean teleport_artifact_test_arti_invoke_cost(struct obj * obj);
#define arti_invoke_cost teleport_artifact_test_arti_invoke_cost
extern int teleport_artifact_test_arti_invoke(struct obj * obj);
#define arti_invoke teleport_artifact_test_arti_invoke
extern boolean finesse_ahriman(struct obj * obj);
extern boolean artifact_light(struct obj * obj);
extern int arti_speak(struct obj * obj);
extern boolean artifact_has_invprop(struct obj * otmp,uchar inv_prop);
extern long arti_cost(struct obj * otmp);
extern uchar teleport_artifact_test_abil_to_adtyp(long * abil);
#define abil_to_adtyp teleport_artifact_test_abil_to_adtyp
extern unsigned long teleport_artifact_test_abil_to_spfx(long * abil);
#define abil_to_spfx teleport_artifact_test_abil_to_spfx
extern struct obj * what_gives(long * abil);
extern const char * glow_color(int arti_indx);
extern int teleport_artifact_test_glow_strength(int count);
#define glow_strength teleport_artifact_test_glow_strength
extern const char * glow_verb(int count,boolean ingsfx);
extern void Sting_effects(int orc_count);
extern int retouch_object(struct obj ** objp,boolean loseit);
extern boolean teleport_artifact_test_untouchable(struct obj * obj,boolean drop_untouchable);
#define untouchable teleport_artifact_test_untouchable
extern void retouch_equipment(int dropflag);
extern int teleport_artifact_test_count_surround_traps(coordxy x,coordxy y);
#define count_surround_traps teleport_artifact_test_count_surround_traps
extern void mkot_trap_warn(void);
extern boolean is_magic_key(struct monst * mon,struct obj * obj);
extern struct obj * has_magic_key(struct monst * mon);
extern boolean is_art(struct obj * obj,int art);
extern struct artifact * teleport_artifact_test_get_artifact(struct obj * obj);
#define get_artifact teleport_artifact_test_get_artifact
extern boolean permapoisoned(struct obj * obj);
#else
#include "../.cache/wasm64-build/tree/src/artifact.c"
#define TELEPORT_ARTIFACT_REFERENCE 1
#endif
#include "../nethack-c/wasm/tu-fragments/artifact-support.c"
#ifdef HYBRID_ARTIFACT
#define artilist teleport_artifact_artilist
#define artiexist teleport_artifact_artiexist
#define artidisco teleport_artifact_artidisco
#define zero_artiexist teleport_artifact_zero_artiexist
#endif
static uint64_t canonical(uint64_t value){
#define REGION(v,id) if(value>=(uintptr_t)&(v)&&value<(uintptr_t)&(v)+sizeof(v))return ((uint64_t)(id)<<48)+(value-(uintptr_t)&(v))
REGION(mpool,1);
REGION(opool,2);
REGION(traps,3);
REGION(levelarg,4);
REGION(counters,5);
REGION(shorts,6);
REGION(ints,7);
REGION(objrefs,8);
REGION(selections,9);
REGION(input,10);
REGION(labels,11);
REGION(vis,12);
REGION(visrows,13);
REGION(aligns,14);
REGION(flags,15);
REGION(artilist,16);
REGION(gu,17);
REGION(artiexist,18);
REGION(artidisco,19);
REGION(objects,20);
REGION(mons,21);
REGION(u,22);
REGION(zero_artiexist,23);
REGION(obj_descr,24);
REGION(svb,25);
REGION(gi,26);
REGION(program_state,27);
REGION(svc,28);
REGION(gv,29);
REGION(gy,30);
REGION(gs,31);
REGION(windowprocs,32);
REGION(iflags,33);
REGION(disp,34);
REGION(gm,35);
REGION(gn,36);
REGION(c_common_strings,37);
REGION(c_color_names,38);
REGION(cg,39);
REGION(svn,40);
REGION(svd,41);
REGION(nul_glyphinfo,42);
REGION(svl,43);
REGION(svq,44);
REGION(svm,45);
REGION(uwep,46);
REGION(gw,47);
REGION(uarmg,48);
REGION(uleft,49);
REGION(uright,50);
REGION(uswapwep,51);
#undef REGION
return value;}
void probe_reset(void){static struct artifact initial[35];static int ready;if(!ready){memcpy(initial,artilist,sizeof initial);ready=1;}memcpy(artilist,initial,sizeof initial);memset(artiexist,0,sizeof artiexist);memset(artidisco,0,sizeof artidisco);
memset(&flags,0,sizeof flags);
memset(&gu,0,sizeof gu);
memset(&objects,0,sizeof objects);
memset(&u,0,sizeof u);
memset(&obj_descr,0,sizeof obj_descr);
memset(&svb,0,sizeof svb);
memset(&gi,0,sizeof gi);
memset(&program_state,0,sizeof program_state);
memset(&svc,0,sizeof svc);
memset(&gv,0,sizeof gv);
memset(&gy,0,sizeof gy);
memset(&gs,0,sizeof gs);
memset(&windowprocs,0,sizeof windowprocs);
memset(&iflags,0,sizeof iflags);
memset(&disp,0,sizeof disp);
memset(&gm,0,sizeof gm);
memset(&gn,0,sizeof gn);
memset(&svn,0,sizeof svn);
memset(&svd,0,sizeof svd);
memset(&svl,0,sizeof svl);
memset(&svq,0,sizeof svq);
memset(&svm,0,sizeof svm);
memset(&uwep,0,sizeof uwep);
memset(&gw,0,sizeof gw);
memset(&uarmg,0,sizeof uarmg);
memset(&uleft,0,sizeof uleft);
memset(&uright,0,sizeof uright);
memset(&uswapwep,0,sizeof uswapwep);
memset(&mpool,0,sizeof mpool);
memset(&opool,0,sizeof opool);
memset(&traps,0,sizeof traps);
memset(&levelarg,0,sizeof levelarg);
memset(&counters,0,sizeof counters);
memset(&shorts,0,sizeof shorts);
memset(&ints,0,sizeof ints);
memset(&objrefs,0,sizeof objrefs);
memset(&selections,0,sizeof selections);
memset(&input,0,sizeof input);
memset(&labels,0,sizeof labels);
memset(options,0,sizeof options);tracepos=0;tracebuf[0]=0;seed=1;reentered=0;savepos=0;if(growth){free(growth);growth=0;}
windowprocs.name="tty";windowprocs.wp_id=wp_tty;windowprocs.win_create_nhwindow=cw;windowprocs.win_destroy_nhwindow=dw;windowprocs.win_putstr=pw;windowprocs.win_display_nhwindow=display;windowprocs.win_start_menu=sm;windowprocs.win_end_menu=em;
for(int y=0;y<ROWNO;y++){visrows[y]=vis[y];for(int x=0;x<COLNO;x++){levl[x][y].typ=ROOM;vis[y][x]=IN_SIGHT;}}gv.viz_array=visrows;
/* pmidx is const: its actual native declaration initialization is never reset. */
for(int i=0;i<NUMMONS+1;i++){mons[i].mlet=S_HUMAN;mons[i].mlevel=5;mons[i].mr=0;mons[i].maligntyp=0;mons[i].msound=0;mons[i].msize=MZ_MEDIUM;mons[i].mflags1=mons[i].mflags2=0;mons[i].mflags3=0;mons[i].mresists=0;}
for(int i=0;i<NUM_OBJECTS;i++){objects[i].oc_name_idx=i;objects[i].oc_class=WEAPON_CLASS;objects[i].oc_subtyp=P_LONG_SWORD;objects[i].oc_material=IRON;objects[i].oc_cost=10;obj_descr[i].oc_name="fixture object";}
for(int i=0;i<32;i++)snprintf(labels[i],sizeof labels[i],"name%d",i);
for(int i=0;i<8;i++){mpool[i].data=&mons[PM_HUMAN];mpool[i].m_id=100+i;mpool[i].mhp=20;mpool[i].mhpmax=30;mpool[i].m_lev=5;mpool[i].mx=20+i;mpool[i].my=10;selections[i].item.a_int=i+1;selections[i].count=-1;objrefs[i]=&opool[i];}
for(int i=0;i<16;i++){opool[i].quan=1;opool[i].otyp=LONG_SWORD;opool[i].oclass=WEAPON_CLASS;opool[i].where=OBJ_INVENT;}
u.ux=20;u.uy=10;u.uz.dnum=1;u.uz.dlevel=3;u.ulevel=10;u.uhp=u.uhpmax=40;u.uen=u.uenmax=30;u.mh=u.mhmax=50;u.umonnum=u.umonster=PM_HUMAN;gu.urole.mnum=PM_ARCHEOLOGIST;gu.urole.questarti=ART_ORB_OF_DETECTION;gu.urace.mnum=PM_HUMAN;gy.youmonst.data=&mons[PM_HUMAN];
levelarg.dnum=1;levelarg.dlevel=4;strcpy(input,"Excalibur");strcpy(labels[31],"fixture label");options[241]=1;
}
void probe_option(int i,int v){if(i<0||i>=256)abort();options[i]=v;}
void*probe_pointer(int k,int i){switch(k){case 0:return &mpool[i];case 1:return &opool[i];case 2:return &mons[i];case 3:return &objects[i];case 4:return &traps[i];case 5:return input;case 6:return &gy.youmonst;case 7:return &levelarg;case 8:return &counters[i];case 9:return &shorts[i];case 10:return &ints[i];case 11:return &objrefs[i];case 12:return &selections[i];case 13:return labels[i];default:abort();}}
uint64_t probe_canonical(uint64_t p){return canonical(p);}
const char*probe_trace(void){return tracebuf;}
uintptr_t probe_stack(void){return emscripten_stack_get_current();}
int probe_layout_count(void){return sizeof artifact_layout/sizeof artifact_layout[0];}
const char*probe_layout_name(int i){return artifact_layout[i].name;}
uint64_t probe_layout_value(int i){return artifact_layout[i].value;}
int probe_test_trap_glyph(void){return GLYPH_TRAP_OFF;}
int probe_pointer_equal(uint64_t a,uint64_t b){return (void*)(uintptr_t)a==(void*)(uintptr_t)b;}
void probe_save_rewind(void){savepos=0;}
int probe_test_constant(int i){static const int values[]={ART_FIRE_BRAND,ART_FROST_BRAND,ART_MJOLLNIR,ART_MAGICBANE,CHEST,PM_HUMAN};return values[i];}
static const char*option_names[]={"In_hell","In_quest","Monnam","On_stairs","Resists_Elem","The","Tobjnam","You","You_cant","You_feel","Your","__assert_fail","abs","add_menu","align_str","aobjnam","attacktype","bare_artifactname","bcsign","body_part","burn_away_slime","bypass_obj","cancel_monst","canseemon","charge_ok","clear_bypasses","clr2colorname","d","defended","depth","destroy_items","dismount_steed","distant_name","do_blinding_ray","dropx","dunlevs_in_dungeon","enlightenment","eos","exercise","find_hell","flashburn","float_down","float_up","free","freeinv","fuzzymatch","getdir","getobj","getrumor","glyph_at","goto_level","hates_silver","hcolor","healmon","healup","hitfloor","hold_another_object","ignite_items","impossible","inside_shop","invocation_pos","isok","killer_xname","ledger_no","level_tele","lightdamage","litroom","livelog_printf","losehp","losexp","make_blinded","make_confused","make_hallucinated","make_sick","make_slimed","make_stunned","map_invisible","maybe_lvltport_feedback","mbodypart","memset","migrate_mon","mksobj","mon_aligntyp","mon_nam","monflee","monhp_per_lvl","newsym","next_to_u","nh_snprintf","nomul","nxt_unbypassed_obj","nxtobj","obfree","obj_extract_self","obj_shuffle_range","observe_object","oname","otense","pline","pline_The","probe_monster","recalc_telepat_range","recharge","remove_worn_item","resist","resists_drli","rn2","rnd","rng_log_enabled","rng_log_set_caller","rnz","s_suffix","see_monsters","seffects","select_menu","selftouch","sensemon","set_ustuck","sfi_arti_info","sfi_short","sfo_arti_info","sfo_xint16","sgn","shieldeff","simple_typename","spell_skilltype","spelleffects","spoteffects","sprintf","sticks","strcat","strcmp","strcpy","strncmpi","surface","t_at","the","throwit","u_teleport_mon","uncurse","untrap","update_inventory","upstart","use_crystal_ball","verbalize","vtense","wake_nearto","weight","which_armor","xname","yname"};
const char*probe_option_name(int i){return i<151?option_names[i]:0;}
void probe_call_hack_artifacts(void){hack_artifacts();}
void probe_call_init_artifacts(void){init_artifacts();}
void probe_call_save_artifacts(NHFILE * nhfp){save_artifacts(nhfp);}
void probe_call_restore_artifacts(NHFILE * nhfp){restore_artifacts(nhfp);}
const char * probe_call_artiname(int artinum){return artiname(artinum);}
struct obj * probe_call_mk_artifact(struct obj * otmp,aligntyp alignment,uchar max_giftvalue,boolean adjust_spe){return mk_artifact(otmp,alignment,max_giftvalue,adjust_spe);}
void probe_call_dispose_of_orig_obj(struct obj * obj){dispose_of_orig_obj(obj);}
const char * probe_call_artifact_name(const char * name,short * otyp_p,boolean fuzzy){return artifact_name(name,otyp_p,fuzzy);}
boolean probe_call_exist_artifact(int otyp,const char * name){return exist_artifact(otyp,name);}
void probe_call_artifact_exists(struct obj * otmp,const char * name,boolean mod,unsigned int flgs){artifact_exists(otmp,name,mod,flgs);}
void probe_call_found_artifact(int a){found_artifact(a);}
void probe_call_find_artifact(struct obj * otmp){find_artifact(otmp);}
int probe_call_nartifact_exist(void){return nartifact_exist();}
void probe_call_artifact_origin(struct obj * arti,unsigned int aflags){artifact_origin(arti,aflags);}
boolean probe_call_spec_ability(struct obj * otmp,unsigned long abil){return spec_ability(otmp,abil);}
boolean probe_call_confers_luck(struct obj * obj){return confers_luck(obj);}
boolean probe_call_arti_reflects(struct obj * obj){return arti_reflects(obj);}
boolean probe_call_shade_glare(struct obj * obj){return shade_glare(obj);}
boolean probe_call_restrict_name(struct obj * otmp,const char * name){return restrict_name(otmp,name);}
boolean probe_call_attacks(int adtyp,struct obj * otmp){return attacks(adtyp,otmp);}
boolean probe_call_defends(int adtyp,struct obj * otmp){return defends(adtyp,otmp);}
boolean probe_call_defends_when_carried(int adtyp,struct obj * otmp){return defends_when_carried(adtyp,otmp);}
boolean probe_call_protects(struct obj * otmp,boolean being_worn){return protects(otmp,being_worn);}
void probe_call_set_artifact_intrinsic(struct obj * otmp,boolean on,long wp_mask){set_artifact_intrinsic(otmp,on,wp_mask);}
int probe_call_touch_artifact(struct obj * obj,struct monst * mon){return touch_artifact(obj,mon);}
boolean probe_call_arti_immune(struct obj * obj,int dtyp){return arti_immune(obj,dtyp);}
boolean probe_call_bane_applies(const struct artifact * oart,struct monst * mon){return bane_applies(oart,mon);}
int probe_call_spec_applies(const struct artifact * weap,struct monst * mtmp){return spec_applies(weap,mtmp);}
long probe_call_spec_m2(struct obj * otmp){return spec_m2(otmp);}
int probe_call_spec_abon(struct obj * otmp,struct monst * mon){return spec_abon(otmp,mon);}
int probe_call_spec_dbon(struct obj * otmp,struct monst * mon,int tmp){return spec_dbon(otmp,mon,tmp);}
void probe_call_discover_artifact(xint16 m){discover_artifact(m);}
boolean probe_call_undiscovered_artifact(xint16 m){return undiscovered_artifact(m);}
int probe_call_disp_artifact_discoveries(winid tmpwin){return disp_artifact_discoveries(tmpwin);}
void probe_call_dump_artifact_info(winid tmpwin){dump_artifact_info(tmpwin);}
boolean probe_call_Mb_hit(struct monst * magr,struct monst * mdef,struct obj * mb,int * dmgptr,int dieroll,boolean vis,char * hittee){return Mb_hit(magr,mdef,mb,dmgptr,dieroll,vis,hittee);}
boolean probe_call_artifact_hit(struct monst * magr,struct monst * mdef,struct obj * otmp,int * dmgptr,int dieroll){return artifact_hit(magr,mdef,otmp,dmgptr,dieroll);}
int probe_call_invoke_ok(struct obj * obj){return invoke_ok(obj);}
int probe_call_doinvoke(void){return doinvoke();}
void probe_call_nothing_special(struct obj * obj){nothing_special(obj);}
int probe_call_invoke_taming(struct obj * obj){return invoke_taming(obj);}
int probe_call_invoke_healing(struct obj * obj){return invoke_healing(obj);}
int probe_call_invoke_energy_boost(struct obj * obj){return invoke_energy_boost(obj);}
int probe_call_invoke_untrap(struct obj * obj){return invoke_untrap(obj);}
int probe_call_invoke_charge_obj(struct obj * obj){return invoke_charge_obj(obj);}
int probe_call_invoke_create_portal(struct obj * obj){return invoke_create_portal(obj);}
int probe_call_invoke_create_ammo(struct obj * obj){return invoke_create_ammo(obj);}
int probe_call_invoke_banish(struct obj * obj){return invoke_banish(obj);}
int probe_call_invoke_fling_poison(struct obj * obj){return invoke_fling_poison(obj);}
int probe_call_invoke_storm_spell(struct obj * obj){return invoke_storm_spell(obj);}
int probe_call_invoke_blinding_ray(struct obj * obj){return invoke_blinding_ray(obj);}
int probe_call_arti_invoke_cost_pw(struct obj * obj){return arti_invoke_cost_pw(obj);}
boolean probe_call_arti_invoke_cost(struct obj * obj){return arti_invoke_cost(obj);}
int probe_call_arti_invoke(struct obj * obj){return arti_invoke(obj);}
boolean probe_call_finesse_ahriman(struct obj * obj){return finesse_ahriman(obj);}
boolean probe_call_artifact_light(struct obj * obj){return artifact_light(obj);}
int probe_call_arti_speak(struct obj * obj){return arti_speak(obj);}
boolean probe_call_artifact_has_invprop(struct obj * otmp,uchar inv_prop){return artifact_has_invprop(otmp,inv_prop);}
long probe_call_arti_cost(struct obj * otmp){return arti_cost(otmp);}
uchar probe_call_abil_to_adtyp(long * abil){return abil_to_adtyp(abil);}
unsigned long probe_call_abil_to_spfx(long * abil){return abil_to_spfx(abil);}
struct obj * probe_call_what_gives(long * abil){return what_gives(abil);}
const char * probe_call_glow_color(int arti_indx){return glow_color(arti_indx);}
int probe_call_glow_strength(int count){return glow_strength(count);}
const char * probe_call_glow_verb(int count,boolean ingsfx){return glow_verb(count,ingsfx);}
void probe_call_Sting_effects(int orc_count){Sting_effects(orc_count);}
int probe_call_retouch_object(struct obj ** objp,boolean loseit){return retouch_object(objp,loseit);}
boolean probe_call_untouchable(struct obj * obj,boolean drop_untouchable){return untouchable(obj,drop_untouchable);}
void probe_call_retouch_equipment(int dropflag){retouch_equipment(dropflag);}
int probe_call_count_surround_traps(coordxy x,coordxy y){return count_surround_traps(x,y);}
void probe_call_mkot_trap_warn(void){mkot_trap_warn();}
boolean probe_call_is_magic_key(struct monst * mon,struct obj * obj){return is_magic_key(mon,obj);}
struct obj * probe_call_has_magic_key(struct monst * mon){return has_magic_key(mon);}
boolean probe_call_is_art(struct obj * obj,int art){return is_art(obj,art);}
struct artifact * probe_call_get_artifact(struct obj * obj){return get_artifact(obj);}
boolean probe_call_permapoisoned(struct obj * obj){return permapoisoned(obj);}
