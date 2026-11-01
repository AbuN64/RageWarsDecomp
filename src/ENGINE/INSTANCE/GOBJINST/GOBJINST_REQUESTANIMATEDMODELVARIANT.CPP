#include "include_asm.h"
#include "COMMON/ACTORRESOURCEHEADER.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/ACCESS_S8_10F.H"
#include "COMMON/TRIPLE.H"
#include "TYPES.H"
#include "SCENE/CACHE_REQUESTRESOURCE.H"
#include "SCENE/CACHE_ALLOCATERESOURCEAT.H"
#include "RENDER/SETN64_GETPACKSECTION.H"



extern s32 SetN64_LocatePackSection(s32, s32, s32, s32 *);




f32 Gobjinst_GetRootMeanSquareScale(void *target) {
    float scaleX = ((LevelActor *)target)->scale.x;
    float scaleY = ((LevelActor *)target)->scale.y;
    float scaleZ = ((LevelActor *)target)->scale.z;
    return Gu_Sqrtf(((scaleX * scaleX) + (scaleY * scaleY) + (scaleZ * scaleZ)) * (0.3333333432674408f));
}

f32 Gobjinst_GetModelParticleScale(void *actor) {
    f32 result;
    void **modelResource;

    result = g_defaultModelParticleScale;
    if (((LevelActor *)actor)->flags & 0x40000) {
        modelResource = Cache_RequestResource(0, ((LevelActor *)actor)->resource, ((LevelActor *)actor)->resource, ((LevelActor *)actor)->resourceFlags, 4, 0, 0, &g_unitScaleMultiplierAnimObjectInfoRev1Text, 1);
        if (modelResource != 0) {
            result = RW_BITS_TO_FLOAT((s32) ((ActorResourceHeader *)SetN64_GetPackSection(*modelResource, 0))->particleScale);
            Cache_UnlockResource(0, modelResource);
        }
    }
    return result;
}

void **Gobjinst_RequestAnimatedModelVariant(MenuPanelRoot *actor, s32 variantIndex) {
    void **resource;

    if (variantIndex < 0) {
        return 0;
    }
    if (variantIndex != actor->selected) {
        resource = Cache_RequestResource(0, actor->resource,
                                 actor->resource, actor->resourceSize,
                                 0, 0, 0, &s_animModelIndexText, 1);
        if (resource != 0) {
            actor->selectedResource = SetN64_LocatePackSection((s32)*resource,
                                                actor->resource,
                                                variantIndex % *(s32 *)*resource,
                                                &actor->window);
            actor->selected = variantIndex;
            Cache_UnlockResource(0, resource);
        }
    }
    if (actor->selectedResource != 0) {
        return Cache_RequestResource(0, actor->selectedResource,
                             actor->selectedResource, actor->window,
                             0, 0, &g_Geometry_ExpandExtendedModelAddress, &s_animatedModelText, 0);
    }
    return 0;
}

#if defined(VERSION_EU_X)
void Gobjinst_EuropeExtendedNoOperation(void) {
}
#endif

#if defined(VERSION_EU_X)
void Gobjinst_EuropeExtendedAlternateNoOperation(void) {
}
#endif

#if defined(VERSION_EU)
void Gobjinst_EuropeNoOperation(void) {
}
#endif

#if defined(VERSION_EU)
void Gobjinst_EuropeAlternateNoOperation(void) {
}
#endif
