#ifndef ENGINE_SCENE_DRAWTRANSITIONCOLOROVERLAY_H
#define ENGINE_SCENE_DRAWTRANSITIONCOLOROVERLAY_H
#include "Scene/scene_drawtransitioncoloroverlay.h"
#include "Common/colorentry.h"
#include "Engine/scene.h"
#include "Common/world.h"
struct Shared_World;
struct LevelActor;
extern void *Scene_GetEffectCurveRecord(struct Shared_World *world, s32 index);
extern s32 Scene_CollectMatchingLevelActors(struct Shared_World *container, s32 key0, s32 key1, s32 key2, struct LevelActor **out, s32 max);
void *Scene_GetActorDefinition(void *world, s32 index);
#endif
