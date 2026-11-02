#include "LIBC.H"
#include "include_asm.h"
#include "COMMON/WORLDRECAT1B6A4.H"
#include "COMMON/MEASUREDRECAT14V4.H"
#include "COMMON/MEASUREDRECAT14V2.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/WORLD.H"
#include "COMMON/MANAGER.H"
#include "COMMON/LIGHT_VOLUME_AND_TRIGGER_VIEWS.H"
#include "COMMON/SCENERECAT10C0.H"
#include "COMMON/COLORENTRY.H"
#include "ENGINE/SCENE.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "SCENE/SCENE_FINDTRACKEDACTORS.H"
#include "SCENE/CACHE_REQUESTRESOURCE.H"
#include "ENGINE/DEFS.H"
#include "RENDER/SETN64_GETPACKSECTION.H"
#include "COMMON/CACHE_RELEASERESOURCE.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/WORLDSORTENTRY.H"

/* SCENE_14.CPP */

extern s32 SetN64_GetDirectoryEntry(s32 *directory, s32 bankOffset, s32 level);

extern s32 Cache_RequestWordCountedResourcePinned(s32 cacheAddress, s32 *handle, s32 resourceKey, void *loadTag);

extern void **Cache_RequestPackSection(s32 cacheAddress, s32 handle, s32 sectionSelector, s32 resourceKey, s32 world, s32 resourceTag, void *loadTag);



extern void Scene_ReleaseCachedLevelData(Shared_World *world);

extern s32 SetN64_LocatePackSection(s32, s32, s32, s32 *);

extern s32 g_cResource_UnpackRequestEntry;

extern void Cache_UnlockResource(s32 cacheContext, s32 resource);

struct VisibleEffectPoolView; struct Results; void SetN64_CollectVisibleEffectNodes(struct VisibleEffectPoolView *effectPool, struct Results *results);

/* Advances the fractional animation clock and updates every active object with the resulting tick flag. */

extern void Statinst_DispatchAttachmentEvents(void *object, s32 all);
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US)
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X)

float k_SceneFindtrackedactorsEncodedWords[3] = {
    1.0f, 1.0f, 1.0f,
};
#endif
#endif

/* 8028B64C_9.CPP */
extern void SetN64_GetPackSectionSize(s32 table, s32 index);

extern LevelActor *g_sceneTrackedActors[4];
extern LevelActor *g_fragTagObjectiveActor;
extern int Scene_GetModelIdAtIndex(void *world, int modelIndex);
