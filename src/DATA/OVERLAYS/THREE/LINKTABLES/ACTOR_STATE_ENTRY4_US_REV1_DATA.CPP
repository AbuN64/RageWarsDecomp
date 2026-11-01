#include "COMMON/RESIDENT_EVENT_HANDLER.H"

#include "DATA/OVLTBL/ACTOR_STATE_ENTRY4_US_REV1_DATA.H"

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_actor_state_entry_CE590_us_rev1.c */
#if defined(VERSION_US_REV1)
ResidentEventHandlerEntry g_actorStateEntry4_us_rev1[1] = {
    { 4, 0, (ResidentEventHandler)(void *)&g_actorStateEntry5_us_rev1 }
};
#endif
#endif
