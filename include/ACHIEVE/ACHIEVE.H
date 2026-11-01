#ifndef ACHIEVE_ACHIEVE_H
#define ACHIEVE_ACHIEVE_H
#include "COMMON/STATERECAT91.H"
#include "TYPES.H"

extern void Achieve_UpdateUnlockTiers(s32 index);
extern s32 Achieve_AwardMilestoneCompletion(s32);
extern void Achieve_AwardAllMilestoneAchievement(s32, s32 *);
extern Preset *Achieve_CopyPreset(s32 key, s32 row, s32 column);
extern void Achieve_ApplyProfileWeaponUnlocks(WeaponUnlockPlayerView*player);
#endif
