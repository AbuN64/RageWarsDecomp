#include "COMMON/WORLD.H"
#include "COMMON/LONE/SCREEN_IMAGE_RESOURCES_ENABLED.H"
#include "COMMON/LONE/g_defaultCameraSurfaceType.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/OBJRECAT5F14.H"
#include "COMMON/VERSION_CALLS.H"

/* Spawns the effect of an item variant: resolves the variant's effect id, loads its descriptor and first record, takes the effect count from the record's model and turns the colour vector by the record's angle, then spawns the effect through the inline spawner of Animpool_SpawnDescribedSceneEffect with the given owner, position, scale, direction and counted reference, releasing both resources. Adapted from Animpool_SpawnDescribedSceneEffect with the descriptor loading added. */
#include "TYPES.H"
#include "SCENE/CACHE_REQUESTRESOURCE.H"
#include "SCENE/CACHE_ALLOCATERESOURCEAT.H"
#include "ENGINE/CACHE/LIST.H"
#include "ENGINE/CACHE/LIST.H"
#include "RENDER/SETN64_GETPACKSECTION.H"
extern s32 SetN64_GetDirectoryEntry(s32, s32, s32);
extern s32 SetN64_LocatePackSection(void *, s32, s32, s32 *);
extern s32 Scene_GetActorDefinition(void *, s32);
#include "COMMON.H"
extern void Graphu64_ScaleVector(CVector3 *, CVector3 *, f32);
struct Shared_World;
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
SceneEffect *Animpool_SpawnAnimationObject(struct CAnimPool *scene, s32 variant, s32 owner, CVector3 position, f32 scale, CVector3 direction,
                      CVector3 color, s32 *ref) {
    SceneEffect *effect;
    s32 id;
    s32 key;
    void **descriptor;
    void **resource;
    RecordAnimPoolSpawnAnimationObject *record;
    s32 count;
    s32 size;
    s32 clip;
    effect = 0;
    id = Scene_FindModelIdIndex(&g_world, variant);
    if (id != -1) {
        key = SetN64_GetDirectoryEntry((s32)g_world.indexedDirectory, g_world.indexedBank, id);
        descriptor = Cache_RequestResource(0, key, key, 24, 0, 0, 0, &s_animObjectIndexText, 1);
        if (descriptor != 0) {
            clip = SetN64_LocatePackSection(*descriptor, key, 0, &size);
            resource = Cache_RequestResource(0, clip, clip, size, 0, 0, 0, &s_animObjectInfoText, 1);
            if (resource != 0) {
                record = SetN64_GetPackSection(*resource, 0);
                count = Scene_GetActorDefinition(&g_world, record->count);
                Graphu64_ScaleVector(&color, &color, Menu_ExpandFloatHighWord(record->angle));
                effect = spawn_effect(scene, id, variant, count, owner, position, scale, direction, color, ref);
                Cache_UnlockResource(0, resource);
            }
            Cache_UnlockResource(0, descriptor);
        }
    }
    return effect;
}
