/* Type-only SHK source-private ABI. Initializers/algorithms are JS. */
#ifndef TELEPORT_SHK_TYPES_H
#define TELEPORT_SHK_TYPES_H
#ifndef TELEPORT_SHK_ORIGINAL_INCLUDED
enum billitem_status {FullyUsedUp=1,PartlyUsedUp=2,PartlyIntact=3,FullyIntact=4,KnownContainer=5,UndisclosedContainer=6};
struct sortbill_item {struct obj*obj;long cost;long quan;int bidx;int8 usedup;boolean queuedpay;};
typedef struct sortbill_item Bill;
#endif
struct shk_icost {int trinsic;int cost;};
_Static_assert(sizeof(struct sortbill_item)==32&&sizeof(struct bill_x)==24&&sizeof(struct eshk)==4960,"Review actual SHK record extents");
_Static_assert(sizeof(struct shk_icost)==8&&offsetof(struct shk_icost,cost)==4,"Review actual anonymous icost row");
#endif
