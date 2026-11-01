#ifndef ENGINE_SCENE_DRAWTRANSITIONCOLOROVERLAY_H
#define ENGINE_SCENE_DRAWTRANSITIONCOLOROVERLAY_H
#include "COMMON/COLORENTRY.H"
#include "ENGINE/SCENE.H"
#include "COMMON/WORLD.H"
extern void *Scene_GetEffectCurveRecord(Shared_World *world, s32 index);
extern s32 Scene_CollectMatchingLevelActors(Container *container, s32 key0, s32 key1, s32 key2, SceneActorMatchRecord **out, s32 max);
#endif
