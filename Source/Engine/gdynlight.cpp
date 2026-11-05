#include "Render/rangenode.h"
#include "Common/sharedplayer.h"
#include "Common/world.h"
#include "types.h"
#include "Fx/normalize_vector.h"
#include "Engine/Cache/list.h"
#include "include_asm.h"
#include "Common/objb.h"
#include "Common/lightdata.h"
#include "Ovlgame/ovlgame_initializedynamiclightpool.h"
#include "Common/heap_arena_entry.h"
#include "Engine/gdynlight.h"
#include "Graphu64/graphu64_getangledistance.h"
#include "Common/approachlocation.h"
#include "Engine/scene.h"

/* GDYNLIGHT.CPP */

void Gdynlight_AccumulateLightDirections(struct CGameDynamicLight_t *lightPool, CVector3 position,
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
    CDLight *node;
    u16 *radius_ptr;

    node = lightPool->m_ActiveList.head;
    if (node != 0) {
        do {
            if (node->m_bEnabled != 0) {
                absoluteDeltaX = position.x - (f32)node->x;
                radius_ptr = &node->m_pROMLight->falloff;
                if (absoluteDeltaX < 0.0f) {
                    absoluteDeltaX = -absoluteDeltaX;
                }
                deltaY = position.y - (f32)node->y;
                if (deltaY < 0.0f) {
                    distanceXY = absoluteDeltaX - deltaY;
                } else {
                    distanceXY = absoluteDeltaX + deltaY;
                }
                deltaZ = position.z - (f32)node->z;
                if (deltaZ < 0.0f) {
                    distanceXYZ = distanceXY - deltaZ;
                } else {
                    distanceXYZ = distanceXY + deltaZ;
                }
                lightRadius = (f32)*radius_ptr;
                if (distanceXYZ < lightRadius) {
                    delta.x = (f32)node->x - position.x;
                    delta.y = (f32)node->y - position.y;
                    delta.z = (f32)node->z - position.z;
                    falloffFraction = g_dynamicLightFalloffUnit - (distanceXYZ / lightRadius);
                    Graphu64_NormalizeVec3(&delta);
                    directionWeight = falloffFraction * g_dynamicLightDirectionScale;
                    Graphu64_ScaleVector(&delta, &delta, directionWeight);
                    Graphu64_AddVec3(left, left, &delta);
                    *remainingIntensity -= directionWeight;
                }
            }
            node = node->m_pNext;
        } while (node != 0);
    }
}

void *Gdynlight_AllocateWorldLight(s32 intrusiveList, s32 index) {
    return Gdynlight_AllocateLightNode(intrusiveList, Scene_GetStridedWorldRecord(&g_world, index));
}

void *Gdynlight_AllocateLightNode(void *listStorage, void *radiusDescriptor) {
    IntrusiveList *intrusiveList = listStorage;
    CDLight *lightNode;

    lightNode = (intrusiveList)[1].head;
    if (lightNode != 0) {
        List_RemoveIntrusive(&(intrusiveList)[1], lightNode);
        List_PrependIntrusive(intrusiveList, lightNode);
        ((CDLight *)lightNode)->m_pROMLight = radiusDescriptor;
        ((CDLight *)lightNode)->m_bEnabled = 0;
    }
    return lightNode;
}

void Gdynlight_ReleaseLight(void *a, CDLight *b) {
    b->m_bEnabled = 0;
    List_RemoveIntrusive(a, b);
    List_PrependIntrusive(&((IntrusiveList *)a)[1], b);
}

int Gdynlight_GetFirstLight(IntrusiveList *intrusiveList) {
    return (int)intrusiveList->head;
}

int Gdynlight_GetNextLight(void *lightPool, struct RangeNode *rangeNode) {
    CDLight *node = rangeNode;
    return (int)node->m_pNext;
}

const float g_dynamicLightDirectionConstants[2] = {
    1.0f, 0.4f,
};

#if defined(VERSION_US)
unsigned int g_dynamicLightNextTag[1] = {
    0x4E657874,
};
#endif
#if defined(VERSION_EU_X)
unsigned int g_dynamicLightTrailingWord[1] = {
    0x3F800000,
};
#endif
#if defined(VERSION_EU)
unsigned int g_dynamicLightTrailingWord[1] = {
    0x00031C00,
};
#endif
#if defined(VERSION_DE)
unsigned int g_dynamicLightTrailingWord[1] = {
    0x00268D74,
};
#endif

#if defined(VERSION_US_REV1)
unsigned int g_dynamicLightPoolWord[1] = {
    0x3F800000,
};
#endif
