#include "COMMON/OBJRECAT5F14.H"
#include "COMMON/LONE/SCREEN_IMAGE_RESOURCES_ENABLED.H"
#include "COMMON/LONE/g_defaultCameraSurfaceType.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/WORLD.H"
#include "COMMON/S1.H"
#include "TYPES.H"
#include "ENGINE/CACHE/LIST.H"
#include "ENGINE/CACHE/LIST.H"

/* Spawns the effect a description asks for: the spawn of Animpool_SpawnSceneEffect (id resolution, free node, init
 * through Gobjinst_InitializeActor and start) inlined with the id, variant, count, owner, position, scale, direction
 * and colour taken from the description record and no counted reference. Adapted from Animpool_SpawnSceneEffect with
 * the enabled and count tests as separate early returns. */










extern s32 Scene_FindModelIdIndex(struct Shared_World *, s32);

extern s32 Scene_GetModelIdAtIndex(void *, s32);


extern void Gobjinst_InitializeActor(SceneEffect *, s32, s32, s32, s32, s32, s32, f32, CVector3, s32, CVector3, CVector3, s32);

extern void Gobjinst_DispatchActorTypeUpdate(char *actor);

static inline SceneEffect *take_effect(struct CAnimPool *scene, s32 *ref) {
    SceneEffect *effect;

    if (g_world.visibilityEnabled == 0 && (unsigned int)scene->UsedList.count >= 3) {
        return 0;
    }
    effect = scene->FreeList.head;
    if (effect != 0) {
        List_RemoveIntrusive(&scene->FreeList, effect);
        List_PrependIntrusive(&scene->UsedList, effect);
        effect->ref = ref;
        if (ref != 0) {
            *ref += 1;
        }
    }
    return effect;
}

static inline SceneEffect *spawn_effect(struct CAnimPool *scene, s32 id, s32 variant, s32 count, s32 owner, CVector3 position,
                                   f32 scale, CVector3 direction, CVector3 color, s32 *ref) {
    SceneEffect *effect;

    if (g_screenImageResourcesEnabled == 0) {
        return 0;
    }
    if (count == 0) {
        return 0;
    }
    if (id == -1) {
        id = Scene_FindModelIdIndex(&g_world, variant);
        if (id == -1) {
            return 0;
        }
    }
    if ((unsigned int)(variant + 1) < 2) {
        variant = Scene_GetModelIdAtIndex(&g_world, id);
    }
    effect = take_effect(scene, ref);
    if (effect == 0) {
        return 0;
    }
    Gobjinst_InitializeActor(effect, id, variant, g_defaultCameraSurfaceType, count, -1, owner, scale, position, 0x80000, color, direction, 0);
    Gobjinst_DispatchActorTypeUpdate(effect);
    return effect;
}

SceneEffect *Animpool_SpawnDescribedSceneEffect(struct CAnimPool *scene, EffectDesc *desc) {
    return spawn_effect(scene, desc->id, desc->variant, desc->count, desc->owner, desc->position, desc->scale,
                        desc->direction, desc->color, 0);
}

s32 Animpool_ReleaseSceneEffect(struct SceneEffect *node) {
    s32 *counter;

    counter = node->ref;
    node->angle = 0;
    if (counter != 0) {
        *counter -= 1;
    }
    List_RemoveIntrusive(&g_spawnedActorList, node);
    return List_AppendIntrusive(&g_sceneEffectSpawnList, node);
}
