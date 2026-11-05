#ifndef ENGINE_ANIMPOOL_ANIMPOOL_SPAWNSCENEEFFECT_H
#define ENGINE_ANIMPOOL_ANIMPOOL_SPAWNSCENEEFFECT_H
#include "types.h"
#include "Common/results.h"
#include "Common/vector.h"

struct SceneEffect;
extern struct SceneEffect * Animpool_SpawnSceneEffect(struct CAnimPool *scene, s32 id, s32 variant, s32 count, s32 owner, CVector3 position, f32 scale, CVector3 direction, CVector3 color, s32 *ref);

#endif
