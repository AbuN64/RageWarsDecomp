#ifndef RENDER_PLAYERAI_TOGGLEFORCEMARKER_H
#define RENDER_PLAYERAI_TOGGLEFORCEMARKER_H
#include "Weapons/weapon_switch_actions.h"
extern void Player_ReleasePlayerParticleEmitters(s32);

void Player_GetPlayerViewTranslation(void *player, f32 *origin);
struct CVector3_t;
void Player_TransformPointByViewOrOwnerMatrix(void *player, struct CVector3_t *point);
void Playerai_AddCappedEventCounter(void *player, s32 increment);
struct SharedPlayer;
int Playerai_IsAlternateFireHeld(struct SharedPlayer *object);
int Playerai_IsPlayerInactive(struct SharedPlayer *player);
struct Player;
void Playerai_ToggleForceMarker(struct Player *player, s32 attract);
#endif
