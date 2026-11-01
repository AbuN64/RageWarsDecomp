#include "../include/libgultra.h"

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_actor_state_animation_CE014_us_rev1.c */
unsigned int g_ActorStateEntryEncodedWords[3] = {
    0x3F800000, 0x00000005, 0x00000000,
};

extern char Turret_Code_IDLE_Address[];
/* ROM-grounded data: src/rw_actor_state_entry_CE020_us_rev1.c */
unsigned int g_actorState62EntryWords[3] = {
    0x0000003E, 0x00000000, (unsigned int)Turret_Code_IDLE_Address,
};
#endif
