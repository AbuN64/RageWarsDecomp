#include "../include/libgultra.h"

#if defined(VERSION_US_REV1)
extern char Turret_Code_FIRE_Address[];
/* ROM-grounded data: src/rw_actor_state_entry_CE040_us_rev1.c */
unsigned int g_actorState63EntryWords[3] = {
    0x0000003F, 0x00000000, (unsigned int)Turret_Code_FIRE_Address,
};
#endif
