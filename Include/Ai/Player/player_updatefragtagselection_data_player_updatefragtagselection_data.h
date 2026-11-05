#ifndef AI_PLAYER_PLAYER_UPDATEFRAGTAGSELECTION_DATA_PLAYER_UPDATEFRAGTAGSELECTION_DATA_H
#define AI_PLAYER_PLAYER_UPDATEFRAGTAGSELECTION_DATA_PLAYER_UPDATEFRAGTAGSELECTION_DATA_H
#include "types.h"
#include "Common/small_records.h"

struct Shared_HudView;
struct Shared_HudView {
    char pad0[0x24];
    s32 flags;
    char pad28[0x274];
    f32 width;
    f32 height;
    f32 x;
    f32 y;
};
typedef struct Shared_HudView Shared_HudView;

#include "types.h"

extern void Playerai_ApplyPeriodicHazardDamage(s32 player, s32 damageSource);
extern s32 Playerai_IsRoundEndState(void *actorObject);
extern s32 Playerai_CountActivePlayers(char *object);

#endif
