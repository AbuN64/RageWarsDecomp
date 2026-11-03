#include "COMMON/OBJRECAT5F14.H"
#include "COMMON/LONE/SCREEN_IMAGE_RESOURCES_ENABLED.H"
#include "COMMON/LONE/g_defaultCameraSurfaceType.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/WORLD.H"
#include "COMMON/S1.H"
#include "TYPES.H"
#include "ENGINE/CACHE/LIST.H"
#include "ENGINE/CACHE/LIST.H"
#include "ENGINE/SCENE_DRAWOPAQUEACTORS.H"

/* Spawns an effect in a scene when effects are enabled and a count is given: resolves a missing effect id
 * from the variant (Scene_FindModelIdIndex, giving up when unknown) and a default variant from the id
 * (Scene_GetModelIdAtIndex), takes a node from the scene's free list when allowed (always with visibilityEnabled_AnimpoolSpawnsceneeffect, otherwise
 * while fewer than three are active), moves it to the active list and attaches the counted reference, then
 * initialises it through Gobjinst_InitializeActor with the position, scale, direction and colour vectors and starts it
 * with Gobjinst_DispatchActorTypeUpdate. Returns the effect or 0. */










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

/* Culls a scene's active effects against the view box: effects whose bounds overlap the box ending at
 * g_cameraVolumeBoundsMinZ + 4 are passed to Scene_RegisterActorInSceneLists and, when idle, drop their counted reference; the others are
 * reset, release their reference, and are unlinked from the active list (List_RemoveIntrusive) and returned to
 * the free list (List_AppendIntrusive). */



extern f32 g_cameraVolumeBoundsMinZ;

struct SceneActorCategoryListsView; struct ObjectSceneRegisterActorInSceneLists; extern void Scene_RegisterActorInSceneLists(struct SceneActorCategoryListsView *world, struct ObjectSceneRegisterActorInSceneLists *object);

static inline s32 overlaps(EffectAnimPoolUpdateSceneEffects *effect, f32 *max) {
    if (max[0] > effect->min[0] && max[-3] < effect->max[0] && max[2] > effect->min[2] &&
        max[-1] < effect->max[2] && max[1] > effect->min[1] && max[-2] < effect->max[1]) {
        return 1;
    }
    return 0;
}

SceneEffect *Animpool_SpawnSceneEffect(struct CAnimPool *scene, s32 id, s32 variant, s32 count, s32 owner, CVector3 position, f32 scale,
                      CVector3 direction, CVector3 color, s32 *ref) {
    SceneEffect *effect;

    if (g_screenImageResourcesEnabled == 0 || count == 0) {
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

void Animpool_UpdateSceneEffects(struct CAnimPool *scene, s32 world) {
    EffectAnimPoolUpdateSceneEffects *effect;
    EffectAnimPoolUpdateSceneEffects *next;
    f32 *max;

    effect = scene->UsedList.head;
    if (effect == 0) {
        return;
    }
    do {
        max = (&g_cameraVolumeBoundsMinZ + 1);
    next_effect:
        next = effect->next;
        if (overlaps(effect, max)) {
            Scene_RegisterActorInSceneLists(world, effect);
            if (effect->ref != 0 && effect->busy == 0) {
                *effect->ref -= 1;
                effect->ref = 0;
            }
        } else {
            effect->busy = 0;
            effect->flags &= ~0x200;
            if (effect->ref != 0) {
                *effect->ref -= 1;
            }
            List_RemoveIntrusive(&scene->UsedList, effect);
            List_AppendIntrusive(&scene->FreeList, effect);
        }
        effect = next;
    } while (0);
    if (effect != 0) {
        goto next_effect;
    }
}

void *Animpool_AcquireSceneEffect(s32 effectPool, s32 *referenceCount) {
    void *acquiredEffect;

    if ((g_world.visibilityEnabled != 0) || ((u32)((struct CAnimPool *) effectPool)->UsedList.count < 3)) {
        acquiredEffect = ((struct CAnimPool *) effectPool)->FreeList.head;
        if (acquiredEffect != 0) {
            List_RemoveIntrusive((void *)(effectPool + 24320), acquiredEffect);
            List_PrependIntrusive((void *)(effectPool + 24340), acquiredEffect);
            ((SceneEffect *)(acquiredEffect))->ref = referenceCount;
            if (referenceCount != 0) {
                *referenceCount += 1;
            }
        }
        return acquiredEffect;
    }
    return 0;
}
