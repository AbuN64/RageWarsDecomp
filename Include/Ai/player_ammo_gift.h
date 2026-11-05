#ifndef AI_PLAYER_AMMO_GIFT_H
#define AI_PLAYER_AMMO_GIFT_H
struct SharedPlayer;
void Player_GiveAmmoWithMessage(struct SharedPlayer *player, s32 type, s32 amount);
#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern const float g_forceMarkerDurationEuropean;
#endif
#endif
