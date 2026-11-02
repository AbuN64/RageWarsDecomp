#include "TYPES.H"

#include "DATA/ACTOR_STATE_CALLBACKS/ACTOR_STATE_CALLBACK_LABELS.H"

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_controller_state_dispatch_CED00_us_rev1.c */
#if defined(VERSION_US_REV1)
struct {
    s32 id;
    void * enter;
    void * update;
} g_controllerState5HandlerWords __attribute__((aligned(4))) = {
    5,
    (void *)&addrLow_Nav_InitCloseCombat,
    (void *)&addrLow_Nav_UpdateCloseCombat
};
#endif
#endif
