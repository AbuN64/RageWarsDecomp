#include "TYPES.H"

#include "DATA/OVLTBL/MOTION_OPEN_ROM_ENTRIES.H"

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_actor_state_entry_CE530_us_rev1.c */
#if defined(VERSION_US_REV1)
struct {
    s32 id;
    void * enter;
    void * update;
} g_actorStateEntry1_us_rev1 __attribute__((aligned(4))) = {
    1,
    (void *)&g_actorStateEntry2_us_rev1,
    (void *)&g_actorStateEntry3_us_rev1
};
typedef char g_actorStateEntry1_us_rev1SizeCheck[(sizeof(g_actorStateEntry1_us_rev1) == 12) ? 1 : -1];
#endif
#endif
