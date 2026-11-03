#ifndef RENDER_PLAYERAI_TOGGLEFORCEMARKER_H
#define RENDER_PLAYERAI_TOGGLEFORCEMARKER_H
#include "WEAPONS/PLAYERRECAT1450V1.H"
extern void Player_ReleasePlayerParticleEmitters(s32);

void Player_GetPlayerViewTranslation(void *player, f32 *origin);
struct CVector3_t;
void Player_TransformPointByViewOrOwnerMatrix(void *player, struct CVector3_t *point);
void Playerai_AddCappedEventCounter(void *player, s32 increment);
struct SharedPlayer;
int Playerai_IsAlternateFireHeld(struct SharedPlayer *object);
int Playerai_IsPlayerInactive(struct SharedPlayer *player);
struct Shared_ActorView;
void Playerai_ToggleForceMarker(struct Shared_ActorView *player, s32 attract);
#endif
