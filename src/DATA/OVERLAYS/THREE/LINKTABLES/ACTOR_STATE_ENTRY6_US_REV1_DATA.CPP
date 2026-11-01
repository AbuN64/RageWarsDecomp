#include "TYPES.H"

#include "DATA/OVLTBL/ACTOR_STATE_ENTRY7_US_REV1.H"

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_actor_state_entry_CE550_us_rev1.c */
#if defined(VERSION_US_REV1)
struct {
    s32 id;
    void * enter;
    void * update;
} g_actorStateEntry6_us_rev1 __attribute__((aligned(4))) = {
    2,
    (void *)&g_actorStateEntry7_us_rev1,
    (void *)&g_actorStateEntry8_us_rev1
};
typedef char g_actorStateEntry6_us_rev1SizeCheck[(sizeof(g_actorStateEntry6_us_rev1) == 12) ? 1 : -1];
#endif
#endif
