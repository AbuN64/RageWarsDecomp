#ifndef COMMON_LEVEL_SPAWN_H
#define COMMON_LEVEL_SPAWN_H
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/LEVEL_TRACK.H"
#include "COMMON/LEVEL_PLACEMENT.H"
#include "COMMON/GAMEPLAY_SETTINGS.H"
#include "ENGINE/SCENE.H"
#include "COMMON/LEVEL_INPUT.H"
typedef struct LevelNode {
    s32 size;
    s32 count;
    LevelPlacedActorRecord records[1];
} LevelNode;
extern SharedPlayer *g_gamePlayerAndMenuState;
#endif
