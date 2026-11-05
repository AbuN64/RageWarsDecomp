#ifndef COMMON_PLAYERPROFILES_H
#define COMMON_PLAYERPROFILES_H
#include "Common/sharedplayer.h"
struct Profile;
/* The four player profile records (0x190 bytes each): name, achievements, per-level times and flags. */
extern struct Profile g_localPlayerProfiles[4];
#endif
