#ifndef ENGINE_SCENE_FINDTRACKEDACTORS_H
#define ENGINE_SCENE_FINDTRACKEDACTORS_H
#include "TYPES.H"
struct Shared_World;
extern void Scene_CopyLevelName(struct Shared_World *world, s32 type, void *levelName, s32 maximumBytes);
extern void *Scene_GetBlLevelData(void *world, s32 record);
#endif
