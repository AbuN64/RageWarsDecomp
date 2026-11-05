#ifndef AI_PLAYERPROFILE_H
#define AI_PLAYERPROFILE_H
#include "types.h"

struct Profile;
extern void Player_InitializeProfile(void *profileStorage);

extern s32 Player_HasProfileUnlockFlag(u8 *profileBytes, s32 unlockIndex);
s32 Player_GetLevelProgress(struct Profile *obj, s32 index);
#include "Common/sharedplayer.h"
#endif
