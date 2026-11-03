#ifndef WORLD_PLAYERPROFILE_H
#define WORLD_PLAYERPROFILE_H
#include "COMMON/RESOURCELOADSTATE.H"
#include "WORLD/PLAYERAI_RESPAWNFRAGTAGPLAYER.H"
extern unsigned char Player_GetProfileValue16(struct Profile *object);
extern unsigned char Player_GetProfileValue14(struct Profile *player);
extern unsigned int Player_GetProfileProgress(struct Profile *object);
extern unsigned char Player_GetProfileValue15(struct Profile *player);
int Player_AddFiftyToProfileValue16(void *player);
void Player_AddTenToProfileValue14(void *object);
void Player_AdvanceProfileProgress(void *object);
struct Profile;
s32 Player_GetProfileAchievementFlag(struct Profile *profile, s32 achievementIndex);
void Player_IncrementLevelProgress(struct Profile *obj, int index);
void Player_SetAchievementFlag7(struct Profile *record, s32 achievementIndex);
int Player_AddFiftyToProfileValue15(void *player);
s32 Player_GetLevelProgress(struct Profile *obj, s32 index);
s32 Player_HasProfileUnlockFlag(u8 *profileBytes, s32 unlockIndex);
void Player_SetAchievementFlag2F(struct Profile *player, s32 achievementIndex);
void Player_SetAchievementFlagByIndex(struct Profile *player, s32 achievementIndex);
s32 Player_TestAchievementFlag7(struct Profile *record, s32 index);
#endif
