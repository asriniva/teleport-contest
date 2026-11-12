/* Test-only forwarding exports in the unchanged original MONMOVE translation unit. */
#include MONMOVE_SOURCE
const char *full_monmove_common(void) { return something; }
winid full_monmove_message_window(void) { return WIN_MESSAGE; }
int full_monmove_cansee(int x, int y) { return cansee(x, y); }
int full_monmove_canspotmon(struct monst *mon) { return canspotmon(mon); }
const struct permonst *full_monmove_species(int index) { return &mons[index]; }
void full_monmove_spin_web(struct monst *mon) { maybe_spin_web(mon); }
int full_monmove_vamp_shift(struct monst *mon, struct permonst *form, boolean msg)
{
    return vamp_shift(mon, form, msg);
}
