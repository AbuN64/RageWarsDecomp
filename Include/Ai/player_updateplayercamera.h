#ifndef AI_PLAYER_UPDATEPLAYERCAMERA_H
#define AI_PLAYER_UPDATEPLAYERCAMERA_H
#include "types.h"
#include "Common/small_records.h"

struct Desc;
struct Desc {
    char pad[0x108];
    s32 caps[4];
};

#include "types.h"
extern f32 Menu_MeasureLine(u8 *p, f32 sx, f32 sy);
struct PlayerGroundContactView;
struct SharedPlayer;
struct Player;
struct ViewTuning;
extern void Player_UpdateBodyMovementAndActions(struct SharedPlayer *player);
extern void Player_UpdateViewAngles(struct Player *player, struct Player *body, struct ViewTuning *tuning);
extern s32 Player_TryEnterHitReactionState(void *player, void *bodyActor);
extern s32 Player_TryThrowSelectedActor(void *playerObject, void *positionObject, s32 *stateFlags);
extern void Player_UpdateMovementSpeedFactor(void *actorView, void *bodyActor, struct PlayerGroundContactView *ground);
#endif
