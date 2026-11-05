#ifndef ACHIEVE_ACHIEVE_H
#define ACHIEVE_ACHIEVE_H
#include "Common/weapon_unlock_presets.h"
#include "types.h"

struct Preset;
struct WeaponUnlockPlayerView;
extern void Achieve_UpdateUnlockTiers(s32 index);
extern s32 Achieve_AwardMilestoneCompletion(s32);
extern void Achieve_AwardAllMilestoneAchievement(s32, s32 *);
extern struct Preset *Achieve_CopyPreset(s32 key, s32 row, s32 column);
extern void Achieve_ApplyProfileWeaponUnlocks(struct WeaponUnlockPlayerView*player);
extern s32 Achieve_AwardCharacterCompletionUnlock(s32 p);
extern void Achieve_MarkLevelPlayed(s32 slot);
extern s32 Achieve_CountEarnedAchievements(s32);
typedef struct MatchMenuObjects {
    char pad0[0x17F0];
    s32 transition;
} MatchMenuObjects;

#endif
