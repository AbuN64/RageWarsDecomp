#include "TYPES.H"

#include "DATA/ACTION_CALLBACKS/ACTOR_MOTION_CALLBACK_LABELS.H"

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_actor_state_entry_CE124_us_rev1.c */
#if defined(VERSION_US_REV1)
struct {
    s32 id;
    void * enter;
    void * update;
} g_overlayThreeActorStateEntryFragment8 __attribute__((aligned(4))) = {
    2,
    (void *)&addrLow_Actionai_SetDrawHandler,
    (void *)&addrLow_Actionai_ClearMotionFlags
};
typedef char g_overlayThreeActorStateEntryFragment8SizeCheck[(sizeof(g_overlayThreeActorStateEntryFragment8) == 12) ? 1 : -1];
#endif
#endif
