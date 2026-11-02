#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHARED_WORLDFUNC.H"
#include "COMMON/STATERECAT34.H"
#include "COMMON/SOUNDINFO.H"
#include "COMMON/OBJB.H"
#include "MENU/SCENE_RESOURCE_PREVIEW_AND_COLLISION_VIEWS.H"
#include "COMMON/S1.H"
#include "TYPES.H"
#include <ultra64.h>
#include "COMMON/RESULTS.H"
#include "SYSTEM/SOUND_CONTEXT_MUSIC_AND_VOICE_CONTROL.H"
#include "ENGINE/CACHE/LIST.H"
#include "SCENE/CACHE_FREEMEMORY.H"
#include "RENDER/SETN64_GETPACKSECTION.H"
extern void Cache_ReleaseResource(void *cache, void *resource);

/* Loads a scene's light into the global light g_playerModelLighting: copies the ambient and directional colours from the scene's light settings (bytes 0xD and 0xA) into both colour copies and the direction bytes from 0x11, then scales the direction to g_lightDirectionLength_SceneUnpackvisibilitygeometry in length through Gu_Sqrtf_TurretMove and Graphu64_ScaleVector and stores it as shorts at 0x1B2B4 of the scene. */
extern u8 g_playerModelLighting[];
extern u8 g_savedPlayerModelLighting[];
extern u8 g_savedSecondaryMenuByteOptions[];
extern u8 g_sceneLightDirection[];
extern f32 Gu_Sqrtf(f32);
extern void Graphu64_ScaleVector(struct CVector3_t *,struct CVector3_t *,f32);
void Scene_LoadSceneLight(SceneLightLoadView *scene) {
    s32 i;
    u8 c;
    f32 v[3];
    f32 length;
    u8 *light;
    for (i = 0; i < 3; i++) {
        c = scene->light->m_AmbientLight[i];
        light = g_playerModelLighting;
        light[i] = c;
        g_savedPlayerModelLighting[i] = c;
        c = scene->light->m_DirectionalLight[i];
        light[i + 8] = c;
        g_savedSecondaryMenuByteOptions[i] = c;
        g_sceneLightDirection[i] = scene->light->m_Direction[i];
    }
    v[0] = scene->light->m_Direction[0];
    v[1] = scene->light->m_Direction[1];
    v[2] = scene->light->m_Direction[2];
    length = Gu_Sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    if (length != 0.0f) {
        Graphu64_ScaleVector(v, v, g_lightDirectionLength / length);
        scene->dir[0] = v[0];
        scene->dir[1] = v[1];
        scene->dir[2] = v[2];
    }
}
int Playerai_GetFirstPlayer(void *);
void SoundVoicePool_StopAll(void *);
s32 * SoundVoicePool_GetGlobalState(void);
void Scene_ReleaseCachedGeometry(void *);
void Player_ReleaseObjectHandles(void *);
/* Shut down the subsystem, free its owned resources, and unlink its list. */
void Scene_FreeSceneResources(SceneResourceOwnerView *sceneToFree) {
    s32 firstPlayer;
    void *firstOptionalResource;
    void *secondOptionalResource;
    void *thirdOptionalResource;
    void *nextAllocationNode;
    void *allocationBase;
    ResourceHandleLinkView *allocationNode;
    firstPlayer = Playerai_GetFirstPlayer(&g_playerViewRenderContext);
    if (firstPlayer != 0) {
        Player_ReleaseObjectHandles((void *) firstPlayer);
    }
    SoundVoicePool_StopAll(SoundVoicePool_GetGlobalState());
    SoundElement_ClearVoiceFlags();
    SoundElement_StopAudioByMask(0x1000);
    Cache_ReleaseResource(NULL, sceneToFree->sceneResourceHandle11);
    Cache_ReleaseResource(NULL, sceneToFree->sceneResourceHandle1);
    Cache_ReleaseResource(NULL, sceneToFree->sceneResourceHandle2);
    Cache_ReleaseResource(NULL, sceneToFree->sceneResourceHandle3);
    Cache_ReleaseResource(NULL, sceneToFree->sceneResourceHandle4);
    Cache_ReleaseResource(NULL, sceneToFree->sceneResourceHandle5);
    Cache_ReleaseResource(NULL, sceneToFree->sceneResourceHandle7);
    Cache_ReleaseResource(NULL, sceneToFree->sceneResourceHandle8);
    Cache_ReleaseResource(NULL, sceneToFree->sceneResourceHandle10);
    Cache_ReleaseResource(NULL, sceneToFree->sceneResourceHandle6);
    Cache_ReleaseResource(NULL, sceneToFree->sceneResourceHandle9);
    firstOptionalResource = sceneToFree->firstOptionalResource;
    if (firstOptionalResource != NULL) {
        Cache_ReleaseResource(NULL, firstOptionalResource);
    }
    secondOptionalResource = sceneToFree->secondOptionalResource;
    if (secondOptionalResource != NULL) {
        Cache_ReleaseResource(NULL, secondOptionalResource);
    }
    thirdOptionalResource = sceneToFree->thirdOptionalResource;
    if (thirdOptionalResource != NULL) {
        Cache_ReleaseResource(NULL, thirdOptionalResource);
    }
    Scene_ReleaseCachedGeometry(sceneToFree);
    allocationBase = sceneToFree->allocations.head;
    allocationNode = allocationBase;
    if (allocationBase != NULL) {
        do {
            nextAllocationNode = allocationNode->resourceHandle;
            List_RemoveIntrusive(&sceneToFree->allocations, allocationNode);
            allocationNode = nextAllocationNode;
        } while (allocationNode != NULL);
    }
    Cache_FreeMemory(allocationBase);
}
/* Binds a loaded collision mesh to the world: records the vertex, face and edge lists from the
   node's four chunks with their counts, resets the two bucket lists and files the 48 buckets into
   the second, then for every face of both lists clears the solid bit when it is hidden and marks it
   0xF0 when its group bit is set in the current group's bitmap. */
extern s32 Ppdecom_UnpackResource(void ***handle, s32 retainUncompressed);
extern void SetN64_GetPackSectionSize(void *node, s32 index);
static inline s32 groupHas(SceneVisibilityGeometryView *world, s32 n) {
    s32 index;
    void *g;
    u8 *bits;
    s32 mask;
    index = world->group;
    g = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(world->tree, 0), index), 2);
    SetN64_GetPackSection(g, 0);
    SetN64_GetPackSectionSize(g, 1);
    bits = SetN64_GetPackSection(g, 1);
    mask = 1 << (n & 7);
    return bits[n / 8] & mask;
}
void Scene_UnpackVisibilityGeometry(SceneVisibilityGeometryView *world, void ***handle) {
    void *node;
    struct IntPair *l0;
    struct IntPair *l1;
    struct IntPair *l2;
    struct IntPair *l3;
    s32 k;
    s32 i;
    s32 n;
    s32 count;
    Face *face;
    if (Ppdecom_UnpackResource(handle, 0) != 0) {
        node = **handle;
        l0 = SetN64_GetPackSection(node, 0);
        l1 = SetN64_GetPackSection(node, 1);
        l2 = SetN64_GetPackSection(node, 2);
        l3 = SetN64_GetPackSection(node, 3);
        count = l0->second;
        world->verts = &((ResidentDataChunk *)(l0))->data[0];
        world->faces = (Face *)&((ResidentDataChunk *)(l1))->data[0];
        world->nfaces = count;
        count = l2->second;
        world->edgeData = &((ResidentDataChunk *)(l2))->data[0];
        world->edges = (Face *)&((ResidentDataChunk *)(l3))->data[0];
        world->nedges = count;
        List_InitializeIntrusive(&world->listA, 0, 4);
        List_InitializeIntrusive(&world->listB, 0, 4);
        for (k = 0; k < 48; k++) {
            List_AppendIntrusive(&world->listB, &world->buckets[k]);
        }
        n = world->nfaces;
        for (i = 0; i < n; i++) {
            face = &world->faces[i];
            if (face->hidden != 0) {
                face->flags &= 0xFE;
            }
            if (groupHas(world, face->group)) {
                face->flags |= 0xF0;
            }
        }
        n = world->nedges;
        for (i = 0; i < n; i++) {
            face = &world->edges[i];
            if (face->hidden != 0) {
                face->flags &= 0xFE;
            }
            if (groupHas(world, face->group)) {
                face->flags |= 0xF0;
            }
        }
    }
}
