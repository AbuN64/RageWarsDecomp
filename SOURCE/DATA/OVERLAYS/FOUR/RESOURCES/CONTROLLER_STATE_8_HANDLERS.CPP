#include "TYPES.H"

#include "DATA/ACTOR_STATE_CALLBACKS/ACTOR_STATE_CALLBACK_LABELS.H"

#if defined(VERSION_US_REV1)
#if defined(VERSION_US_REV1)
struct {
    s32 id;
    void * enter;
    void * update;
} g_controllerState8HandlerWords __attribute__((aligned(4))) = {
    8,
    (void *)&addrLow_Nav_ResetObjectArrivalChase,
    (void *)&addrLow_Nav_UpdateObjectArrivalChase
};
#endif
#endif
