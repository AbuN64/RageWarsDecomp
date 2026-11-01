#include "TYPES.H"

#include "DATA/ACTION_CALLBACKS/ACTION_SETBREAKABLESTATE_ADDRESS.H"

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_actor_state_entry_CE104_us_rev1.c */
#if defined(VERSION_US_REV1)
struct {
    s32 id;
    void * enter;
} g_overlayThreeActorStateEntryFragment7 __attribute__((aligned(4))) = {
    1,
    (void *)&addrLow_Action_SetBreakableState
};
typedef char g_overlayThreeActorStateEntryFragment7SizeCheck[(sizeof(g_overlayThreeActorStateEntryFragment7) == 8) ? 1 : -1];
#endif
#endif
