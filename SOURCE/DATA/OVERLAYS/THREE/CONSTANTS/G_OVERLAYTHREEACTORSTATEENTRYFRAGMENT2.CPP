#include "TYPES.H"

#include "DATA/ACTION_CALLBACKS/BREAKABLE_HIT_CALLBACK_ADDRESSES.H"

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_actor_state_entry_CE210_us_rev1.c */
#if defined(VERSION_US_REV1)
struct {
    s32 id;
    void * enter;
    void * update;
} g_overlayThreeActorStateEntryFragment2 __attribute__((aligned(4))) = {
    1,
    (void *)&addrLow_Action_DeactivateBreakable,
    (void *)&addrLow_Action_ResolveBreakableHit
};
typedef char g_overlayThreeActorStateEntryFragment2SizeCheck[(sizeof(g_overlayThreeActorStateEntryFragment2) == 12) ? 1 : -1];
#endif
#endif
