#include "../include/libgultra.h"

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_actor_state_entry_CE060_us_rev1.c */
extern char Turret_Setup_DEATH_Address[];
extern char Turret_Code_DEATH_Address[];
unsigned int g_LibultraEncodedWordsBlock4[3] = {
    0x00000040, (unsigned int)Turret_Setup_DEATH_Address, (unsigned int)Turret_Code_DEATH_Address,
};
#endif
