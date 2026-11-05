#ifndef COMMON_LEVEL_SPAWN_H
#define COMMON_LEVEL_SPAWN_H
#include "Common/level_actor.h"
#include "Common/level_track.h"
#include "Common/level_placement.h"
#include "Common/gameplay_settings.h"
#include "Engine/scene.h"
#include "Common/level_input.h"
struct SharedPlayer;
typedef struct LevelNode {
    s32 size;
    s32 count;
    LevelPlacedActorRecord records[1];
} LevelNode;
extern struct SharedPlayer *g_gamePlayerAndMenuState;
#endif
