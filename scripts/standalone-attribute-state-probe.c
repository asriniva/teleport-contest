/* Explicit independent test inputs for original ATTRIB's object/inventory ABI. */
#include "hack.h"
#include <string.h>
void probe_attribute_object(struct obj *obj, int otyp, long quan,
                            unsigned bits, struct obj *next)
{
    memset(obj, 0, sizeof *obj);
    obj->otyp = otyp;
    obj->oclass = objects[otyp].oc_class;
    obj->quan = quan;
    obj->cursed = !!(bits & 1);
    obj->blessed = !!(bits & 2);
    obj->dknown = !!(bits & 4);
    obj->where = OBJ_INVENT;
    obj->nobj = next;
}
void probe_attribute_inventory(struct obj *first) { gi.invent = first; }
