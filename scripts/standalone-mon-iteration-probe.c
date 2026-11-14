/* Test observer only: include the original MON TU without changing its policy. */
#include MON_SOURCE
static int iter_rows[4096][4], iter_count, iter_behavior, iter_answer, iter_stop, iter_depth;
static void record_iteration(struct monst *mon, int x, int y)
{
    if (iter_count >= 4096) panic("finite MON iteration observer overflow");
    iter_rows[iter_count][0] = iter_depth;
    iter_rows[iter_count][1] = (int) mon->m_id;
    iter_rows[iter_count][2] = x;
    iter_rows[iter_count++][3] = y;
}
staticfn boolean iteration_callback(struct monst *mon)
{
    int ordinal = iter_count;
    record_iteration(mon, 0, 0);
    if (ordinal == 0) {
        if (iter_behavior == 1)
            (void) makemon(&mons[PM_HUMAN], 0, 0, MM_NOMSG | NO_MINVENT);
        else if (iter_behavior == 2)
            mongone(mon);
        else if (iter_behavior == 3 && mon->nmon)
            mongone(mon->nmon);
        else if (iter_behavior == 4) {
            iter_depth = 1;
            iter_mons_safe(iteration_callback);
            iter_depth = 0;
        }
    }
    return (boolean) ((iter_stop && ordinal + 1 >= iter_stop) ? iter_answer : 0);
}
staticfn void iteration_void(struct monst *mon) { (void) iteration_callback(mon); }
staticfn boolean iteration_xy(struct monst *mon, coordxy x, coordxy y)
{
    int ordinal = iter_count;
    record_iteration(mon, x, y);
    return (boolean) ((iter_stop && ordinal + 1 >= iter_stop) ? iter_answer : 0);
}
unsigned full_mon_iteration(int operation, int behavior, int stop, int answer,
                            int x, int y)
{
    struct monst *mon = 0;
    iter_count = iter_depth = 0;
    iter_behavior = behavior; iter_stop = stop; iter_answer = answer;
    switch (operation) {
    case 0: iter_mons_safe(iteration_callback); break;
    case 1: iter_mons(iteration_void); break;
    case 2: mon = get_iter_mons(iteration_callback); break;
    case 3: mon = get_iter_mons_xy(iteration_xy, x, y); break;
    default: panic("unknown MON observer operation");
    }
    return mon ? mon->m_id : 0;
}
int full_mon_iteration_count(void) { return iter_count; }
int full_mon_iteration_value(int row, int col) { return iter_rows[row][col]; }
void full_mon_iteration_alloc(unsigned n) { alloc_itermonarr(n); }
unsigned full_mon_iteration_capacity(void) { return itermonsiz; }
boolean full_mon_iteration_storage(void) { return itermonarr != 0; }

void full_mon_visibility(int operation, struct monst *mon)
{
    if (operation == 0) hide_monst(mon);
    else if (operation == 1) flash_mon(mon);
    else panic("unknown MON visibility observer operation");
}
int full_mon_visibility_byte(struct monst *mon)
{ return gv.viz_array[mon->my][mon->mx]; }

void full_mon_animal_init(int construct) { mon_animal_list(construct); }
int full_mon_animal_count(void) { return ga.animal_list_count; }
int full_mon_animal_value(int i) { return ga.animal_list[i]; }
int full_mon_animal_pick(void) { return pick_animal(); }
