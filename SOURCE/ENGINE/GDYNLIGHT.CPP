#include "RENDER/RANGENODE.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/WORLD.H"
#include "TYPES.H"
#include "FX/GRAPHU64_NORMALIZEVEC3.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "ENGINE/CACHE/LIST.H"
#include "include_asm.h"
#include "COMMON/OBJB.H"
#include "OVLGAME/OVLGAME_INITIALIZEDYNAMICLIGHTPOOL.H"
#include "COMMON/S1.H"

/* GDYNLIGHT.CPP */
extern void Graphu64_ScaleVector(void *, void *, f32);

extern void Graphu64_AddVec3(CVector3 *, CVector3 *, CVector3 *);

extern void *Scene_GetStridedWorldRecord(struct Shared_World *object, int index);

void Gdynlight_AccumulateLightDirections(RangeNode **lightList, u32 positionXBits, u32 positionYBits, u32 positionZBits,
                   CVector3 *left, f32 *remainingIntensity) {
    CVector3 delta;
    f32 deltaZ;
    f32 deltaY;
    f32 falloffFraction;
    f32 directionWeight;
    f32 lightRadius;
    f32 absoluteDeltaX;
    f32 distanceXY;
    f32 distanceXYZ;
    RangeNode *node;
    u16 *radius_ptr;

    node = *lightList;
    if (node != 0) {
        do {
            if (node->active != 0) {
                absoluteDeltaX = *(f32 *)&positionXBits - (f32)node->x;
                radius_ptr = node->radius;
                if (absoluteDeltaX < 0.0f) {
                    absoluteDeltaX = -absoluteDeltaX;
                }
                deltaY = *(f32 *)&positionYBits - (f32)node->y;
                if (deltaY < 0.0f) {
                    distanceXY = absoluteDeltaX - deltaY;
                } else {
                    distanceXY = absoluteDeltaX + deltaY;
                }
                deltaZ = *(f32 *)&positionZBits - (f32)node->z;
                if (deltaZ < 0.0f) {
                    distanceXYZ = distanceXY - deltaZ;
                } else {
                    distanceXYZ = distanceXY + deltaZ;
                }
                lightRadius = (f32)*radius_ptr;
                if (distanceXYZ < lightRadius) {
                    delta.x = (f32)node->x - *(f32 *)&positionXBits;
                    delta.y = (f32)node->y - *(f32 *)&positionYBits;
                    delta.z = (f32)node->z - *(f32 *)&positionZBits;
                    falloffFraction = g_dynamicLightFalloffUnit - (distanceXYZ / lightRadius);
                    Graphu64_NormalizeVec3(&delta);
                    directionWeight = falloffFraction * g_dynamicLightDirectionScale;
                    Graphu64_ScaleVector(&delta, &delta, directionWeight);
                    Graphu64_AddVec3(left, left, &delta);
                    *remainingIntensity -= directionWeight;
                }
            }
            node = node->next;
        } while (node != 0);
    }
}

void *Gdynlight_AllocateWorldLight(s32 intrusiveList, s32 index) {
    return Gdynlight_AllocateLightNode(intrusiveList, Scene_GetStridedWorldRecord(&g_world, index));
}

void *Gdynlight_AllocateLightNode(void *intrusiveList, void *radiusDescriptor) {
    void *lightNode;

    lightNode = ((IntrusiveList *)intrusiveList)[1].head;
    if (lightNode != 0) {
        List_RemoveIntrusive(&((IntrusiveList *)intrusiveList)[1], lightNode);
        List_PrependIntrusive(intrusiveList, lightNode);
        ((RangeNode *)lightNode)->radius = radiusDescriptor;
        ((RangeNode *)lightNode)->active = 0;
    }
    return lightNode;
}

void Gdynlight_ReleaseLight(IntrusiveList *a, RangeNode *b) {
    b->active = 0;
    List_RemoveIntrusive(a, b);
    List_PrependIntrusive(&a[1], b);
}

int Gdynlight_GetFirstLight(void *intrusiveList) {
    IntrusiveList *list = intrusiveList;
    return (int)list->head;
}

int Gdynlight_GetNextLight(void *unused0, void *rangeNode) {
    RangeNode *node = rangeNode;
    return (int)node->next;
}

/* ROM-grounded data: src/g_dynamicLightDirectionConstants.c */
const float g_dynamicLightDirectionConstants[2] = {
    1.0f, 0.4f,
};

/* DYNLIGHT.CPP */
#if defined(VERSION_US)
unsigned int k_DynlightEncodedWords[1] = {
    0x4E657874,
};
#endif
#if defined(VERSION_EU_X)
unsigned int k_DynlightOneWords[1] = {
    0x3F800000,
};
#endif
#if defined(VERSION_EU)
unsigned int k_DynlightEncodedWordsBlock2[1] = {
    0x00031C00,
};
#endif
#if defined(VERSION_DE)
unsigned int k_DynlightEncodedWordsBlock1[1] = {
    0x00268D74,
};
#endif

/* K_OVLGAMEINITIALIZEDYNAMICLIGHTPOOLONEWORDS.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800C958C */
unsigned int k_OvlgameInitializedynamiclightpoolOneWords[1] = {
    0x3F800000,
};
#endif
