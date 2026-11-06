#include "types.h"
#include "Common/Lone/screen_image_resources_enabled.h"
#include "Common/audio_callbacks.h"
#include "Common/runtime_declarations.h"
#include "Menu/scene_resource_preview_and_collision_views.h"
#include "Common/resident_event_handler.h"
#include "Common/cache_releaseresource.h"
#include "Common/scene_frame_and_effect_updates.h"
#include "Common/note_state.h"
#include "Common/player_pool_and_inode_cache_views.h"
#include "Common/objb.h"
#include "Common/world.h"
#include "Ai/Nav/portal_loadcollisiontable.h"
#include "Engine/scene.h"
#include "Menu/Items/Scene/selection_preview_operations.h"
#include "Menu/Pak/menu_istrackrequestitem.h"
#include "Engine/Cache/cache.h"
#include "Engine/session.h"
#include "Menu/Items/Scene/ovlscene_loadsceneresources.h"
#include "Ovlgame/ovlgame_initializeplayerpool.h"
#include "Common/resourcelockstate.h"
#include "Cache/cache.h"
#include "Ovlgame/ovlgame_address_symbols.h"
#include "Common/navigation_graph.h"
#include "Common/shared_worldfunc.h"
#include "Common/music_track_volume.h"
#include "Common/soundinfo.h"
#include "Common/heap_arena_entry.h"
#include <platform_sdk.h>
#include "Common/results.h"
#include "System/sound_context_music_and_voice_control.h"
#include "Engine/Cache/list.h"
#include "Scene/cache_freememory.h"
#include "Render/setn64_getpacksection.h"
#include "Ai/Player/playerai_findtransientplayer.h"
#include "Ai/Player/player_startplayeranimation.h"
#include "Common/ppdecom_unpackresource.h"
#include "Graphu64/graphu64_getangledistance.h"
#include "Scene/scene_unpackvisibilitygeometry.h"
#include "Cache/cache_allocateresourceat.h"
#include "Scene/scene_updateanddrawworld.h"
#include "../../sdk/include/LIBC.H"
#include "Common/effectrender.h"
#include "Common/sharedplayer.h"
#include "Common/selectionscreenstate.h"
#include "Common/level_spawn.h"
#include "Common/game_player_and_menu_state.h"
#include "Common/level_track.h"
#include "Common/propgeometry.h"
#include "Engine/Instance/gobjinst_initializeplacedactor.h"
#include "Engine/Instance/insthdr.h"
#include "Weapons/barrel_geteyedistancesquared.h"
#include "Scene/cache_requestresource.h"
#include "Engine/scene_grid_and_geometry_operations.h"
#include "Engine/Instance/simpinst.h"
#include "Engine/scene_drawtransitioncoloroverlay.h"
#include "Geometry/geometry_drawblendparts.h"
#include "Gobjinst/gobjinst_findnearestbonebounds.h"
#include "Menu/Items/Scene/ovlscene_findplacedobjectsbykey.h"
#include "Menu/Items/Scene/scene_buildplacedactors.h"
#include "Ovlscene/ovlscene.h"
#include "Statinst/statinst_acquiregeometry.h"
#include "Common/frontend_clock_state.h"
#include "Cache/cache_allocresourceblock.h"
#include "Simpinst/barrel_spawnactoreffect_data.h"
#include "Statinst/statinst_drawgeometryvariant.h"
#include "include_asm.h"
#include "Engine/defs.h"
#include "Menu/Items/items.h"
#include "Menu/Items/Scene/scene_updatependingobjects.h"
#include "Common/sessionhandlerrow.h"
#include "Graphu64/graphu64_matrixfromeulerxyz.h"
#include "Render/soundelement_playflatsound.h"
#include "Menu/Items/Scene/scene_loadlevelresources.h"
#include "Common/level.h"
#include "Common/trigger_and_float_value_operations.h"
#include "Common/triple.h"
#include "Ovlgame/scene_dispatchandrecyclequeuedtriggers.h"
#include "Engine/scene_loadlevelresources.h"
#include "Menu/Items/Scene/scene_findactortriggerrange.h"
#include "Menu/Items/Scene/scene_relocateparticleeffectdata.h"
#include "Data/rest_source_records.h"

extern void Cache_DrainAndCompactResources(s32 unusedHeap);






extern char g_sceneCollisionStorage;
void Scene_LoadSceneResources(struct Shared_World *sceneToLoad, s32 cartridgeBankKey) {
    s32 *cartridgeDirectory;
    s32 *bloodlustLevelDirectory;
    void **bloodlustWeaponResource;
    void **warpDestinationsResource;
    void **bloodlustLevelResource;
    s32 levelDirectoryKey;
    s32 textureDirectoryKey;
    s32 objectDirectoryKey;
    s32 binaryDirectoryKey;
    s32 graphicsetDirectoryKey;
    s32 sectionEighteenKey;
    s32 linkGroupTypeData;
    s32 sectionTwelveData;

    Scene_ClearSceneObjectCounts(sceneToLoad);
    sceneToLoad->mode = 0;
    Scene_ResetSelectionState((char *)sceneToLoad);
    sceneToLoad->previewLoaded = 0;
    sceneToLoad->sceneResourceResetState = 0;
    sceneToLoad->level = -1;
    sceneToLoad->eventPhase = 0;
    sceneToLoad->elapsed = 0;
    sceneToLoad->offset.x = 0;
    sceneToLoad->offset.y = 0;
    sceneToLoad->offset.z = 0;
    sceneToLoad->count = 0;
    sceneToLoad->specialActorCount = 0;
    sceneToLoad->sceneLoadResetState = 0;
    /* The global is the holder storage; its canonical scalar declaration is incomplete. */
    ((void (*)(void *))Player_RefreshActivePlayerSceneState)(&g_playerViewRenderContext);
    /* The original resource API passes the null arena argument. */
    Cache_DrainAndCompactResources(0);
    Cache_RequestWordCountedResourcePinned(0, (void **)&cartridgeDirectory, cartridgeBankKey, &g_cartridgeIndex);
    levelDirectoryKey = SetN64_GetDirectoryEntry(cartridgeDirectory, cartridgeBankKey, 5);
    sceneToLoad->resourceBank = levelDirectoryKey;
    Cache_RequestWordCountedResourcePinned(0, &sceneToLoad->resourceDirectory, levelDirectoryKey, &g_sceneDirectoryResourceTag);
    textureDirectoryKey = SetN64_GetDirectoryEntry(cartridgeDirectory, cartridgeBankKey, 3);
    sceneToLoad->textureBank = textureDirectoryKey;
    Cache_RequestWordCountedResourcePinned(0, (void **)&sceneToLoad->textureDirectory, textureDirectoryKey, &g_textureSetsIndex);
    sceneToLoad->modelIds = (s32) *Cache_RequestPackSection(0, (s32)cartridgeDirectory, 2, cartridgeBankKey, (s32)sceneToLoad, (intptr_t)&g_cResource_UnpackRequestEntry, &g_objectTypesText);
    objectDirectoryKey = SetN64_GetDirectoryEntry(cartridgeDirectory, cartridgeBankKey, 0);
    sceneToLoad->indexedBank = objectDirectoryKey;
    Cache_RequestWordCountedResourcePinned(0, &sceneToLoad->indexedDirectory, objectDirectoryKey, &g_objectsIndex);
    sceneToLoad->actorDefinitions = (s32) *Cache_RequestPackSection(0, (s32)cartridgeDirectory, 1, cartridgeBankKey, (s32)sceneToLoad, (intptr_t)&g_sceneGeometrySectionTag, &g_sceneGeometryResourceTag);
    sceneToLoad->slotPoolDefinition = (s32 *)Cache_RequestPackSection(0, (s32)cartridgeDirectory, 4, cartridgeBankKey, (s32)sceneToLoad, (intptr_t)&g_sceneParticleEffectSectionTag, &g_particleEffects);
    sceneToLoad->lookupTable = (s32) *Cache_RequestPackSection(0, (s32)cartridgeDirectory, 10, cartridgeBankKey, (s32)sceneToLoad, (intptr_t)&g_cResource_UnpackRequestEntry, &g_objectTypesText);
    binaryDirectoryKey = SetN64_GetDirectoryEntry(cartridgeDirectory, cartridgeBankKey, 9);
    sceneToLoad->lookupBank = binaryDirectoryKey;
    Cache_RequestWordCountedResourcePinned(0, &sceneToLoad->lookupDirectory, binaryDirectoryKey, &g_binariesIndexText);
    sceneToLoad->objectSections = (s32) *Cache_RequestPackSection(0, (s32)cartridgeDirectory, 11, cartridgeBankKey, (s32)sceneToLoad, (intptr_t)&g_cResource_UnpackRequestEntry, &g_particleSwooshes);
    sectionTwelveData = (s32) *Cache_RequestPackSection(0, (s32)cartridgeDirectory, 12, cartridgeBankKey, (s32)sceneToLoad, (intptr_t)&g_cResource_UnpackRequestEntry, &g_dynamicLightsResourceTag);
    sceneToLoad->bitSections = &g_worldSnapshotNoteData;
    sceneToLoad->records = sectionTwelveData;
    sceneToLoad->previewDirectoryKey = SetN64_LocatePackSection((s32)cartridgeDirectory, cartridgeBankKey, 6, &sceneToLoad->noteCount);
    sceneToLoad->secondaryLevels = &g_sceneCollisionStorage;
    sceneToLoad->previewResourceKey = SetN64_LocatePackSection((s32)cartridgeDirectory, cartridgeBankKey, 7, &sceneToLoad->previewResourceBank);
    warpDestinationsResource = Cache_RequestPackSection(0, (s32)cartridgeDirectory, 8, cartridgeBankKey, (s32)sceneToLoad, (intptr_t)&g_cResource_UnpackRequestEntry, &g_warpDests);
    sceneToLoad->warpDestinationsResourceHandle = warpDestinationsResource;
    sceneToLoad->placedObjectTable = (s32) *warpDestinationsResource;
    sceneToLoad->stridedRecords = (s32) *Cache_RequestPackSection(0, (s32)cartridgeDirectory, 13, cartridgeBankKey, (s32)sceneToLoad, (intptr_t)&g_cResource_UnpackRequestEntry, &g_curves);
    sceneToLoad->eventClipDefinitions = (s32) *Cache_RequestPackSection(0, (s32)cartridgeDirectory, 14, cartridgeBankKey, (s32)sceneToLoad, (intptr_t)&g_cResource_UnpackRequestEntry, &g_rumbleLabels);
    sceneToLoad->eventClipGroups = (s32) *Cache_RequestPackSection(0, (s32)cartridgeDirectory, 15, cartridgeBankKey, (s32)sceneToLoad, (intptr_t)&g_cResource_UnpackRequestEntry, &g_rumbleTypesResourceTag);
    sceneToLoad->resourceKindTable = (s32) *Cache_RequestPackSection(0, (s32)cartridgeDirectory, 17, cartridgeBankKey, (s32)sceneToLoad, (intptr_t)&g_cResource_UnpackRequestEntry, &g_graphicsetType);
    graphicsetDirectoryKey = SetN64_GetDirectoryEntry(cartridgeDirectory, cartridgeBankKey, 16);
    sceneToLoad->resourceKindBank = graphicsetDirectoryKey;
    Cache_RequestWordCountedResourcePinned(0, &sceneToLoad->resourceKindDirectory, graphicsetDirectoryKey, &g_graphicsetIndex);
    sectionEighteenKey = SetN64_GetDirectoryEntry(cartridgeDirectory, cartridgeBankKey, 18);
    sceneToLoad->trackLookup = sectionEighteenKey;
    Cache_RequestWordCountedResourcePinned(0, &sceneToLoad->trackBundle, sectionEighteenKey, &g_cinemasIndexText);
    Menu_RequestTrackBundle();
    linkGroupTypeData = (s32) *Cache_RequestPackSection(0, (s32)cartridgeDirectory, 19, cartridgeBankKey, (s32)sceneToLoad, (intptr_t)&g_cResource_UnpackRequestEntry, &g_linkGroupTypes);
    sceneToLoad->challengeFile = 0;
    sceneToLoad->challengeFileSize = 0;
    sceneToLoad->resourceHandle = 0;
    sceneToLoad->resourceKey = -1;
    sceneToLoad->triggerCounterIds = linkGroupTypeData;
    if (*cartridgeDirectory >= 22) {
        sceneToLoad->challengeFile = SetN64_GetDirectoryEntry(cartridgeDirectory, cartridgeBankKey, 21);
        bloodlustLevelResource = /* This callee returns its allocated resource handle, not an integer ID. */
            ((void **(*)(s32,void **,s32,void *,s32))Cache_RequestWordCountedResource)(0, (void **)&bloodlustLevelDirectory, sceneToLoad->challengeFile, &g_constructBlLevelDataIndex, 1);
        if (bloodlustLevelResource != 0) {
            sceneToLoad->challengeFileSize = (s32) (((*bloodlustLevelDirectory * 4) + 15) & ~7);
            Cache_ReleaseResource(0, bloodlustLevelResource);
        } else {
            sceneToLoad->challengeFile = 0;
        }
    }
    if (*cartridgeDirectory >= 24) {
        bloodlustWeaponResource = Cache_RequestPackSection(0, (s32)cartridgeDirectory, 23, cartridgeBankKey, (s32)sceneToLoad, (intptr_t)g_cResource_UnpackRequestEntry, &g_bloodlustWeaponData);
        Portal_LoadCollisionTable(*bloodlustWeaponResource);
        Cache_ReleaseResource(0, bloodlustWeaponResource);
    }
    Scene_InitPreview((Shared_World *)sceneToLoad, cartridgeBankKey);
    g_screenImageResourcesEnabled = 1;
    Scene_CopySimpleModelHeader(sceneToLoad, &sceneToLoad->simpleModelHeaders[0], 3500);
    Scene_CopySimpleModelHeader(sceneToLoad, &sceneToLoad->simpleModelHeaders[1], 3501);
    Scene_CopySimpleModelHeader(sceneToLoad, &sceneToLoad->simpleModelHeaders[2], 3502);
    Scene_CopySimpleModelHeader(sceneToLoad, &sceneToLoad->simpleModelHeaders[3], 3503);
    Scene_CopySimpleModelHeader(sceneToLoad, &sceneToLoad->simpleModelHeaders[4], 3504);
    sceneToLoad->navPointsResourceHandle = 0;
    sceneToLoad->navLinksResourceHandle = 0;
    sceneToLoad->navVisionResourceHandle = 0;
    sceneToLoad->cachedGeometryHandle = 0;
    sceneToLoad->cachedGeometryPack = 0;
    sceneToLoad->cachedDisplayLists[0] = 0;
    sceneToLoad->cachedDisplayLists[1] = 0;
    Scene_LoadLevelResources(sceneToLoad, 0, 0);
}

void Scene_LoadSceneLight(Shared_World *scene) {
    s32 i;
    u8 c;
    f32 v[3];
    f32 length;
    u8 *light;
    for (i = 0; i < 3; i++) {
        c = scene->levelInfo->m_AmbientLight[i];
        light = g_playerModelLighting[0].ambient;
        light[i] = c;
        g_savedPlayerModelLighting[i] = c;
        c = scene->levelInfo->m_DirectionalLight[i];
        light[i + 8] = c;
        g_savedSecondaryMenuByteOptions[i] = c;
        g_sceneLightDirection[i] = scene->levelInfo->m_Direction[i];
    }
    v[0] = scene->levelInfo->m_Direction[0];
    v[1] = scene->levelInfo->m_Direction[1];
    v[2] = scene->levelInfo->m_Direction[2];
    length = Gu_Sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    if (length != 0.0f) {
        Graphu64_ScaleVector(v, v, g_lightDirectionLength / length);
        scene->lightDirection[0] = v[0];
        scene->lightDirection[1] = v[1];
        scene->lightDirection[2] = v[2];
    }
}

void SoundVoicePool_StopAll(void *);
s32 * SoundVoicePool_GetGlobalState(void);
void Scene_ReleaseCachedGeometry(struct Shared_World *);

/* Shut down the subsystem, free its owned resources, and unlink its list. */
void Scene_FreeSceneResources(Shared_World *sceneToFree) {
    s32 firstPlayer;
    void *firstOptionalResource;
    void *secondOptionalResource;
    void *thirdOptionalResource;
    void *nextAllocationNode;
    void *allocationBase;
    NavigationSearchNode *allocationNode;
    firstPlayer = Playerai_GetFirstPlayer(&g_playerViewRenderContext);
    if (firstPlayer != 0) {
        Player_ReleaseObjectHandles((void *) firstPlayer);
    }
    SoundVoicePool_StopAll(SoundVoicePool_GetGlobalState());
    SoundElement_ClearVoiceFlags();
    SoundElement_StopAudioByMask(0x1000);
    Cache_ReleaseResource(NULL, sceneToFree->visibilityResourceHandle);
    Cache_ReleaseResource(NULL, sceneToFree->levelIndexResourceHandle);
    Cache_ReleaseResource(NULL, sceneToFree->collisionResourceHandle);
    Cache_ReleaseResource(NULL, sceneToFree->gridBoundsResourceHandle);
    Cache_ReleaseResource(NULL, sceneToFree->sceneIndexResourceHandle);
    Cache_ReleaseResource(NULL, sceneToFree->levelInfoResourceHandle);
    Cache_ReleaseResource(NULL, sceneToFree->animatedInstancesResourceHandle);
    Cache_ReleaseResource(NULL, sceneToFree->actorLinksResourceHandle);
    Cache_ReleaseResource(NULL, sceneToFree->levelPathsResourceHandle);
    Cache_ReleaseResource(NULL, sceneToFree->skyLayersResourceHandle);
    Cache_ReleaseResource(NULL, sceneToFree->resource);
    firstOptionalResource = sceneToFree->navPointsResourceHandle;
    if (firstOptionalResource != NULL) {
        Cache_ReleaseResource(NULL, firstOptionalResource);
    }
    secondOptionalResource = sceneToFree->navLinksResourceHandle;
    if (secondOptionalResource != NULL) {
        Cache_ReleaseResource(NULL, secondOptionalResource);
    }
    thirdOptionalResource = sceneToFree->navVisionResourceHandle;
    if (thirdOptionalResource != NULL) {
        Cache_ReleaseResource(NULL, thirdOptionalResource);
    }
    Scene_ReleaseCachedGeometry(sceneToFree);
    allocationBase = sceneToFree->navigation.searchNodes.head;
    allocationNode = allocationBase;
    if (allocationBase != NULL) {
        do {
            nextAllocationNode = allocationNode->next;
            List_RemoveIntrusive(&sceneToFree->navigation.searchNodes, allocationNode);
            allocationNode = nextAllocationNode;
        } while (allocationNode != NULL);
    }
    Cache_FreeMemory(allocationBase);
}
/* Binds a loaded collision mesh to the world: records the vertex, face and edge lists from the
   node's four chunks with their counts, resets the two bucket lists and files the 48 buckets into
   the second, then for every record of both lists clears the solid bit when its kind is nonzero (a trigger) and marks it
   0xF0 when its visibilityGroup bit is set in the current group's bitmap. */
static inline s32 groupHas(Shared_World *world, s32 n) {
    s32 index;
    void *g;
    u8 *bits;
    s32 mask;
    index = world->level;
    g = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(world->bitSections, 0), index), 2);
    SetN64_GetPackSection(g, 0);
    SetN64_GetPackSectionSize(g, 1);
    bits = SetN64_GetPackSection(g, 1);
    mask = 1 << (n & 7);
    return bits[n / 8] & mask;
}
void Scene_UnpackVisibilityGeometry(Shared_World *world, void ***handle) {
    void *node;
    struct IntPair *l0;
    struct IntPair *l1;
    struct IntPair *l2;
    struct IntPair *l3;
    s32 k;
    s32 i;
    s32 n;
    s32 count;
    WorldTrigger *face;
    if (Ppdecom_UnpackResource(handle, 0) != 0) {
        node = **handle;
        l0 = SetN64_GetPackSection(node, 0);
        l1 = SetN64_GetPackSection(node, 1);
        l2 = SetN64_GetPackSection(node, 2);
        l3 = SetN64_GetPackSection(node, 3);
        count = l0->second;
        world->recordIndex = (s32 *)&((ResidentDataChunk *)(l0))->data[0];
        world->recordArray = (WorldTrigger *)&((ResidentDataChunk *)(l1))->data[0];
        world->recordCount = count;
        count = l2->second;
        world->alternateRecordIndex = (s32 *)&((ResidentDataChunk *)(l2))->data[0];
        world->alternateRecordArray = (WorldTrigger *)&((ResidentDataChunk *)(l3))->data[0];
        world->alternateRecordCount = count;
        List_InitializeIntrusive(&world->activeTriggerTimers, 0, 4);
        List_InitializeIntrusive(&world->freeTriggerTimers, 0, 4);
        for (k = 0; k < 48; k++) {
            List_AppendIntrusive(&world->freeTriggerTimers, &world->triggerTimers[k]);
        }
        n = world->recordCount;
        for (i = 0; i < n; i++) {
            face = &world->recordArray[i];
            if (face->kind != 0) {
                face->flags &= 0xFE;
            }
            if (groupHas(world, face->visibilityGroup)) {
                face->flags |= 0xF0;
            }
        }
        n = world->alternateRecordCount;
        for (i = 0; i < n; i++) {
            face = &world->alternateRecordArray[i];
            if (face->kind != 0) {
                face->flags &= 0xFE;
            }
            if (groupHas(world, face->visibilityGroup)) {
                face->flags |= 0xF0;
            }
        }
    }
}

/* Packs a collision mesh into one allocated block: copies the node's vertex list, the triangle source
   and the trailing chunk behind a five-offset header, builds a 0x20-byte triangle record per source
   face, lowers the world's minimum height to every triangle vertex, and flags triangles whose group
   bit, callback or neighbours mark them with the default surface mask. */
#include "types.h"
#include "Common/Lone/g_defaultcamerasurfacetype.h"
#include "Common/packed.h"
#include "Common/resourcelockstate.h"
#include "Common/ppdecom_unpackresource.h"
#include "Common/resident_event_handler.h"
#include "Common/shared_menureply.h"
#include "Common/objb.h"
#include "Common/world.h"
#include "Menu/scene_resource_preview_and_collision_views.h"
#include "Render/setn64_getpacksection.h"
#include "Engine/Cache/cache.h"
#include "Engine/session.h"
#include "Cache/cache_allocresourceblock.h"
struct CacheResourceNode;

static inline s32 testBit(s32 n, u8 *bits) {
    s32 mask = 1 << (n & 7);

    return bits[n / 8] & mask;
}

void Scene_BuildCollisionGeometry(Shared_World *world, CollisionBuildMeshHandle **handle) {
    s32 size0;
    s32 size1;
    s32 size3;
    void *chunk;
    s32 tableSize;
    char *base;
    CollisionBuildVertex *verts;
    CollisionBuildTriangle *tris;
    CollisionBuildMeshHandle *block;
    int *node;
    void *first;
    CollisionBuildVertexList *vlist;
    CollisionBuildList *flist;
    s32 ntris;
    CollisionBuildHeader *hdr;
    s32 offset;
    char *dst;
    char *vdst;
    CollisionBuildVertexList *copiedVertices;
    CollisionBuildTriangleList *copiedTriangles;
    s32 nverts;
    s32 i;
    s32 j;
    s32 k;
    CollisionBuildTriangle *tri;
    CollisionBuildFace *face;
    f32 y;
    int *group;
    s32 index;
    u8 *bits;

    if (Ppdecom_UnpackResource((void*)handle, 1) != 0) {
        node = (*handle)->payload.data;
        first = ((void *(*)(int *,s32,s32 *))SetN64_GetSizedPackSection)(node, 0, &size0);
        vlist = ((void *(*)(int *,s32,s32 *))SetN64_GetSizedPackSection)(node, 1, &size1);
        flist = (void*)SetN64_GetPackSection(node, 2);
        ntris = flist->count;
        chunk = ((void *(*)(int *,s32,s32 *))SetN64_GetSizedPackSection)(node, 3, &size3);
        tableSize = (ntris << 5) | 8;
        block = (void*)Cache_AllocResourceBlock(0, handle, size0 + 24 + size1 + tableSize + size3);
        if (block != 0) {
            offset = 24;
            hdr = block->payload.data;
            i = 0;
            hdr->count = 0;
            hdr->offsets[0] = offset;
            SetN64_TransposeRecords(first, (char *) hdr + offset, 0);
            hdr->count = 1;
            offset += size0;
            vdst = (char *) hdr + offset;
            hdr->offsets[1] = offset;
            SetN64_TransposeRecords(vlist, vdst, 0);
            hdr->count = 2;
            offset += size1;
            dst = (char *) hdr + offset;
            hdr->offsets[2] = offset;
            SetN64_TransposeRecords(flist, dst, 1);
            face = flist->items;
            copiedTriangles=(void*)dst;
            copiedTriangles->kind = 32;
            copiedTriangles->count = ntris;
            base = (char *) hdr;
            tris = copiedTriangles->items;
            nverts = vlist->count;
            copiedVertices=(void*)vdst;
            verts = copiedVertices->items;
            for (i = 0; i < nverts; i++) {
                Region_ScaleWordsToFloats(&verts[i]);
            }
            for (j = 0; j < ntris; j++) {
                tri = &tris[j];
                /* The caller supplies a sixth bounds value; the decoder uses the first five. */
                ((void (*)(CGameRegion *,Packed *,char *,int,char *,int))Region_DecodePackedRegion)(&tri->canonical, &face[j], (char*)verts, nverts, (char*)tris, ntris);
                for (i = 0; i < 3; i++) {
                    y = tri->fields.v[i]->y;
                    if (!(y <= world->minimumCollisionY)) {
                        y = world->minimumCollisionY;
                    }
                    world->minimumCollisionY = y;
                }
                index = world->level;
                group = (void*)SetN64_GetPackSection((void*)SetN64_GetPackSection((void*)SetN64_GetPackSection(world->secondaryLevels, 0), index), 0);
                SetN64_GetPackSection(group, 0);
                SetN64_GetPackSectionSize(group, 1);
                bits = (void*)SetN64_GetPackSection(group, 1);
                if (testBit(j, bits)) {
                    tri->fields.flags |= 0x400;
                }
                if (!(tri->fields.mask & g_defaultCameraSurfaceType)) {
                    tri->fields.mask = g_defaultCameraSurfaceType;
                }
                if (Cinema_IsSequenceInWindow() != 0) {
                    tri->fields.mask = g_defaultCameraSurfaceType;
                }
                if (tri->fields.flags & 0x2000) {
                    tri->fields.mask = g_defaultCameraSurfaceType;
                }
            }
            for (j = 0; j < ntris; j++) {
                tri = &tris[j];
                for (k = 0; k < 3; k++) {
                    if (tri->fields.adj[k] != 0 && (tri->fields.adj[k]->fields.flags & 0x2000)) {
                        { s32 *surface = &tri->fields.mask; *surface = g_defaultCameraSurfaceType; }
                    }
                }
            }
            offset += tableSize;
            hdr->count = 3;
            hdr->offsets[3] = offset;
            SetN64_TransposeRecords(chunk, base + offset, 0);
            hdr->count = 4;
            offset += size3;
            hdr->offsets[4] = offset;
        }
        Cache_ReplaceResourceBlock(0, (void*)handle, (void*)block);
    }
}

/* Loads every still-empty cell of the level's tile grid: for each row and column whose cell
   record has no resource, fetches the cell's block through SetN64_LocatePackSection and Cache_RequestResource,
   binds and spawns each object of its two object lists (0xE8- and 0x1C8-byte records) and
   releases the spawned handles and the block. */





/* Runs Scene_LoadPreviewBufferA_SceneBuildplacedactors and Scene_LoadPreviewBufferB_SceneBuildplacedactors on a large state block, then clears its word at offset
   0x1B444, sets the word at 0x1B448 to 0x15 and copies g_menuOptionAvailabilityFlags into the word at 0x1B44C. */



void Scene_BuildPlacedActors(Shared_World *world, struct CacheResourceNode **handle) {
    Shared_Placed spawns[8];
    Shared_Placed extra;
    s32 n;
    LevelActor *objects;
    s32 mode;
    struct CacheResourceNode *block;
    s32 nspawns;
    LevelNode *node;
    LevelPlacedActorRecord *records;
    LevelBlock *hdr;
    s32 i;
    s32 peerIndex;
    s32 playerIndex;
    s32 spawnIndex;
    s32 specialSet;
    s32 *definition;
    LevelPlacedActorRecord *rec;
    LevelPlacedActorRecord *recWalk;
    LevelActor *objWalk;
    SlotSelectionPlayerConfig *slot;
    s16 value;
    LevelActor *obj;
    LevelActor *other;
    SharedPlayer *player;
    Shared_Placed *spawn;
    f32 angle;
    f32 best;
    f32 dist;

    if (Ppdecom_UnpackResource(handle, 1) != 0) {
        mode = Scene_GetModelSectionTwoRecord(world, 0);
        node = (*handle)->data;
        n = node->count;
        block = Cache_AllocResourceBlock(0, handle, n * (sizeof(LevelActor)) + 8);
        if (block != 0) {
            SetN64_TransposeRecords(node, block->data, 1);
            hdr = block->data;
            hdr->size = sizeof(LevelActor);
            hdr->count = n;
            records = node->records;
            objects = hdr->objects;
            if (world->selectionFlags == 0) {
                world->selectionValues[0] = Scene_FindNearestPlacedObject(world, node->records[0].vec4, world->level, &world->selectionSpawn);
                if (world->selectionValues[0] != 0) {
                    world->selectionFlags = 1;
                }
            }
            spawnIndex = 0;
            nspawns = 0;
            if (world->selectionFlags != 0) {
                nspawns = Scene_FindPlacedObjectsByKey(world, world->level, world->selectionValues[0], spawns, 8);
            }
            world->actors = objects;
            world->actorCapacity = n;
            i = 0;
            if (i < n) {
                objWalk = objects;
                recWalk = records;
                while (i < n) {
                    rec = recWalk;
                    obj = objWalk;
                    i++;
                    obj->definition = Scene_GetActorDefinition(world, rec->resource22);
                    objWalk = obj + 1;
                    recWalk = rec + 1;
                }
            }
            world->createdActorCount = 0;
            for (i = 0; i < n; i++) {
                rec = &records[i];
                obj = &objects[i];
                specialSet = 3101;
                Gobjinst_InitializePlacedActor(obj, rec, mode, i);
                definition = Scene_GetActorDefinition(world, rec->resource22);
                if (*definition != 11 && i != 0) {
                    continue;
                }
                world->createdActorCount++;
                memcpy(&g_spawnReferencePosition, rec->vec4, sizeof(CVector3));
                g_spawnReferencePosition.y += 204.79998779296875f;
                g_spawnReferenceFloorPolygon = Scene_FindFloorPolygon(world, rec->vec4);
                playerIndex = 0;
                if (playerIndex < g_playerCount) {
                    slot = g_playerSettings;
                    do {
                        player = &g_gamePlayerAndMenuState.entries[playerIndex];
                        if (nspawns != 0) {
                            if (slot->kind == 12 && player->views1450.view1450_1.computer != 0 && world->level == 9) {
                                Scene_FindPlacedObjectsByKey(world, 9, specialSet, &extra, 1);
                                spawn = &extra;
                            } else {
                                spawn = &spawns[spawnIndex];
                            }
                            rec->resource20 = (u16)spawn->modelSectionIndex;
                            Graphu64_WrapPeriodicValue(&spawn->heading);
                            angle = spawn->heading;
                            if (!(angle > 3.1415927f)) {
                                if (!(angle < -3.1415927f)) {
                                    if (!(angle > 3.1415927f)) {
                                        value = angle * 10430.06f;
                                    } else {
                                        value = 0x7FFF;
                                    }
                                } else {
                                    value = -0x7FFF;
                                }
                            } else {
                                value = 0x7FFF;
                            }
                            rec->amount24 = value;
                            memcpy(rec->vec4, &spawn->pos, sizeof(CVector3));
                            world->offset.x = 0;
                            world->offset.y = 0;
                            world->offset.z = 0;
                            spawnIndex++;
                            if (spawnIndex >= nspawns) {
                                spawnIndex = 0;
                            }
                        }
                        Player_InitActorParts(player, rec, mode, i);
                        slot++;
                        playerIndex++;
                    } while (playerIndex < g_playerCount);
                }
            }
            for (i = world->createdActorCount; i < n; i++) {
                obj = &objects[i];
                best = 3.4028235e38f;
                obj->controller = 0;
                if (Insthdr_GetModelPropertyFlag2(obj) == 0) {
                    continue;
                }
                for (peerIndex = world->createdActorCount; peerIndex < n; peerIndex++) {
                    other = &objects[peerIndex];
                    if (obj->definition->kind == other->definition->kind && Insthdr_GetModelPropertyFlag1(other) != 0 && obj != other) {
                        if (obj->controller != 0) {
                            dist = Barrel_GetEyeDistanceSquared(obj, other->position0);
                            if (dist < best) {
                                obj->controller = other;
                                best = dist;
                            }
                        } else {
                            obj->controller = other;
                            best = Barrel_GetEyeDistanceSquared(obj, other->position0);
                        }
                    }
                }
            }
        }
        Cache_ReplaceResourceBlock(0, handle, block);
        world->kind1Cursor = 0;
    }
}
void Scene_LoadGridCells(Shared_World *level) {
    s32 size;
    s32 width;
    s32 row;
    s32 lastCol;
    s32 lastRow;
    s32 rows;
    WorldSectorExtent *cells;
    WorldSectorExtent *cell;
    s32 col;
    s32 firstCol;
    s32 key;
    void **block;
    void *node;
    ResourceManagerState *list;
    s32 i;
    s32 n;
    s32 m;
    ObjA *a;
    ObjA *objsA;
    ObjB *objsB;
    ObjB *b;
    void *handle;

    width = ((ResourceManagerState *) SetN64_GetPackSection(level->gridBoundsAndSections, 0))->count;
    row = 0;
    rows = ((ResourceManagerState *) SetN64_GetPackSection(level->gridBoundsAndSections, 2))->count;
    cells = ((WorldSectorExtentTable *)SetN64_GetPackSection(level->gridBoundsAndSections, 4))->cells;
    lastRow = rows - 1;
    lastCol = width - 1;
    /* scan every cell: columns firstCol..lastCol of each row */
    firstCol = 0;
    for (; row <= lastRow; row++) {
        for (col = firstCol; col <= lastCol; col++) {
            cell = &cells[col + row * width];
            if (cell->occupied != 0) {
                continue;
            }
            key = SetN64_LocatePackSection((s32)level->sceneIndexData, level->sceneDirectoryKey, col + row * width, &size);
            block = Cache_RequestResource(0, key, key, size, 4, level, g_scene_BuildPlacedInstancesEntry, s_gridSectionText, 1);
            if (block == 0) {
                continue;
            }
            node = *block;
            if (*(s32 *) node != 0) {
                list = SetN64_GetPackSection(node, 0);
                n = list->count;
                objsA = (ObjA *) (list + 1);
                for (i = 0; i < n; i++) {
                    a = &objsA[i];
                    a->block = block;
                    Statinst_RegisterGeometryResources(a, 0);
                    handle = Statinst_AcquireGeometry(a, a->type);
                    if (handle != 0) {
                        Geometry_UnlockMaterialResources(handle);
                        Cache_UnlockResource(0, handle);
                    }
                }
                list = SetN64_GetPackSection(node, 1);
                m = list->count;
                objsB = (ObjB *) (list + 1);
                for (i = 0; i < m; i++) {
                    b = &objsB[i];
                    b->block = block;
                    Simpinst_RegisterModelVariantResources(b, 0);
                    handle = Simpinst_RequestModelVariant(b, b->type);
                    if (handle != 0) {
                        Geometry_UnlockMaterialResources(handle);
                        Cache_UnlockResource(0, handle);
                    }
                }
            }
            Cache_UnlockResource(0, block);
        }
    }
}
void Scene_InitPreview(Shared_World *world, s32 level) {
    Scene_LoadPreviewBufferA((Shared_World *)world);
    Scene_LoadPreviewBufferB((char *)world);
    world->previewState = 0;
    world->previewTimer = 21;
    world->previewStart = ((struct MemoryUsageStats *)&g_menuOptionAvailabilityFlags)->value;
}
/* Loads a selected resource into the shared buffer and releases the temporary allocation. */
struct Shared_World;
/* extern */
extern s32 Control_IsSnapshotActive(void); /* extern */


void Scene_LoadPreviewBufferA(Shared_World *previewToLoad) {
    s32 *persistentDataResource;
    s32 bufferSize;

    if (Control_IsSnapshotActive() == 0) {
        persistentDataResource = Cache_RequestResource(0, previewToLoad->previewDirectoryKey, previewToLoad->previewDirectoryKey, previewToLoad->noteCount, 0, 0, &g_cResource_UnpackRequestEntry, &g_loadSavePersistentData, 1);
        Libc_CopyBytes(&g_worldSnapshotNoteData, (const void *)*persistentDataResource, 22528);
        Cache_ReleaseResource(0, persistentDataResource);
        previewToLoad->previewLoaded = 1;
    }
}

/* Loads the preview resource into the sound buffer when idle, while the adjacent helper resets a changed selection. */


void Scene_LoadPreviewBufferB(Shared_World *state) {
 int *resource;
 int id;
 if(Control_IsSnapshotActive()==0) {
  resource=Cache_RequestResource(0,state->previewResourceKey,state->previewResourceKey,state->previewResourceBank,0,0,g_cResource_UnpackRequestEntry,g_gamePersistentData,1);
  Libc_CopyBytes(&g_sceneCollisionStorage,(const void *)*resource,0x5000);
  Cache_ReleaseResource(0,resource);
 }
}
/* Loads the preview resource into the sound buffer when idle, while the adjacent helper resets a changed selection. */

void Scene_ChangePreviewSelection(Shared_World *state,int selection) {
 if(selection!=state->level) {
  state->selectionFlags=0;
  Scene_SetSelection(state,~selection,0);
 }
}
/* Resets part of a large state block: sets its word at offset 0x1B410 to 2 and clears the words
   at 0x1B414 to 0x1B41C and 0x1B434 to 0x1B440. */
void Scene_ResetSelectionState(char *state) {
    ((Shared_World *)state)->selectionState = 2;
    ((Shared_World *)state)->frozen = 0;
    ((Shared_World *)state)->selectionTimer = 0;
    ((Shared_World *)state)->selectionFlags = 0;
    ((Shared_World *)state)->selectionValues[0] = 0;
    ((Shared_World *)state)->selectionValues[1] = 0;
    ((Shared_World *)state)->selectionValues[2] = 0;
    ((Shared_World *)state)->selectionValues[3] = 0;
}
/* Copies up to max of a track's placed objects whose key matches into out: finds the key's index range in the track's sorted key table through Defs_FindSortedGroupRange, queues each object in that range of the given kind (any kind for -1) on a local list through List_InitializeIntrusive and List_PrependIntrusive, then takes them back off through List_CountIntrusiveNodes and List_RemoveIntrusive, copying each 20-byte object, and returns how many were copied. */
s32 Scene_FindPlacedObjectsByKey(void *world, s32 kind, s32 key, Shared_Placed *out, s32 max) {
    Shared_World *track = world;
    ListRec list;
    Node_Items_FindPlacedObjectsByKey nodes[64];
    s32 first;
    s32 last;
    s32 found;
    s32 *keys;
    s32 *objectTable;
    Shared_Placed *objects;
    Node_Items_FindPlacedObjectsByKey *node;
    s32 i;
    s32 match;
    s32 count;

    found = 0;
    count = (keys = SetN64_GetPackSection(track->placedObjectTable, 0))[1];
    keys += 2;
    objectTable = SetN64_GetPackSection(track->placedObjectTable, 1);
    objects = (Shared_Placed *)(objectTable + 2);
    if (Defs_FindSortedGroupRange(keys, count, key, &first, &last) != 0) {
        List_InitializeIntrusive(&list, 4, 8);
        node = nodes;
        for (i = first; i <= last; i++) {
            match = 1;
            if (kind != -1) {
                match = objects[i].kind == kind;
            }
            if (match) {
                node->index = i;
                List_PrependIntrusive(&list, node);
                node++;
            }
        }
        for (max--; max != -1; max--) {
            if (list.count == 0) {
                return found;
            }
            node = List_CountIntrusiveNodes(&list);
            out[found++] = objects[node->index];
            List_RemoveIntrusive(&list, node);
        }
    }
    return found;
}
/* SetN64_GetPackSection sections of Shared_World.placedObjectTable: 0 holds one key per placed object,
   1 the placed objects in the same order. */
typedef struct PlacedObjectKeys {
    s32 tag;
    s32 count;
    s32 keys[1];
} PlacedObjectKeys;
typedef struct PlacedObjectList {
    s32 tag;
    s32 count;
    Shared_Placed objects[1];
} PlacedObjectList;
/* Finds the placed object of the given kind nearest to position, copies it to out and returns its key; returns 0
   when none is found or the nearest is object 0 (index 0 doubles as "none"). */
s32 Scene_FindNearestPlacedObject(Shared_World *world, f32 *position, s32 kind, Shared_Placed *out) {
    s32 i;
    s32 nearest;
    PlacedObjectKeys *keys;
    PlacedObjectList *list;
    s32 *key;
    Shared_Placed *objects;
    s32 count;
    f32 distance;
    f32 nearestDistance;
    keys = SetN64_GetPackSection(world->placedObjectTable, 0);
    count = keys->count;
    key = keys->keys;
    list = SetN64_GetPackSection(world->placedObjectTable, 1);
    nearestDistance = 3.4028235e+38f;
    objects = list->objects;
    nearest = 0;
    for (i = 0; i < count; i++) {
        if (objects[i].kind == kind) {
            distance = Graphu64_GetPointDistance(&objects[i].pos.x, position);
            if (distance < nearestDistance) {
                nearestDistance = distance;
                nearest = i;
            }
        }
    }
    if (nearest != 0) {
        *out = objects[nearest];
    }
    if (nearest != 0) {
        return key[nearest];
    }
    return 0;
}

/* Sets the resource transition state and sound, while its adjacent helper refreshes the controller-option bit. */



void Scene_SetSelection(Shared_World *state,int selection,int mode) {
 state->frozen=1;
 state->selectionState=mode;
 state->selectionValues[1]=selection;
 if(mode==2 && selection!=999)SoundElement_PlayFlatSound(540);
}
void Scene_LoadSelectionLighting(Shared_World *state) {
 Scene_LoadSceneLight(state);
 g_geometryFogEffectEnabled=(state->levelInfo->lightingFlags>>2)&1;
}

/* Processes both pending object lists between update barriers. */

void Cinema_SetPlaybackFlag(void);
void Cinema_ClearPlaybackFlag(void);

void Scene_UpdatePendingObjects(Shared_World *pendingWorld) {
 s32 i,n;
 Cinema_ClearPlaybackFlag();
 n=pendingWorld->recordCount;
 for(i=0;i<n;i++) Scene_DispatchEnabledEntityTrigger(pendingWorld,(s32)pendingWorld->recordArray+i*20);
 n=pendingWorld->alternateRecordCount;
 for(i=0;i<n;i++) Scene_DispatchEnabledEntityTrigger(pendingWorld,(s32)pendingWorld->alternateRecordArray+i*20);
 Cinema_SetPlaybackFlag();
}

/* Spawns the pickups of a level: between Cinema_ClearPlaybackFlag and Cinema_SetPlaybackFlag it passes every item of both item tables whose kind is 1, 2, 4 or 10 to Scene_DispatchEnabledEntityTrigger. */
void Scene_DispatchSelectedEntityKinds(Level *level) {
    s32 i;
    s32 n;
    ItemOvlSceneDispatchSelectedEntityKinds *item;

    Cinema_ClearPlaybackFlag();
    n = level->counts[0];
    for (i = 0; i < n; i++) {
        item = &level->items[0][i];
        if (item->kind == 1 || item->kind == 4 || item->kind == 2 || item->kind == 10) {
            Scene_DispatchEnabledEntityTrigger(level, item);
        }
    }
    n = level->counts[1];
    for (i = 0; i < n; i++) {
        item = &level->items[1][i];
        if (item->kind == 1 || item->kind == 4 || item->kind == 2 || item->kind == 10) {
            Scene_DispatchEnabledEntityTrigger(level, item);
        }
    }
    Cinema_SetPlaybackFlag();
}
void Scene_DispatchAndRecycleQueuedTriggers(SceneTriggerQueueOwner *scene) {
    EntryOvlSceneDispatchAndRecycleQueuedTriggers *entry;
    EntryOvlSceneDispatchAndRecycleQueuedTriggers *next;

    entry = scene->active;
    while (entry != 0) {
        next = entry->next;
        Link_DispatchTrigger(entry->handle);
        List_RemoveIntrusive(&scene->active, entry);
        List_PrependIntrusive(&scene->spare, entry);
        entry = next;
    }
}
void Scene_RelocateParticleEffectData(s32 world, void ***handle) {
    void *obj;
    PieceGroup *group;
    Piece *piece;
    s32 base;
    s32 count;
    s32 i;

    if (Ppdecom_UnpackResource(handle, 0) != 0) {
        obj = **handle;
        group = SetN64_GetPackSection(obj, 2);
        count = group->count;
        piece = group->pieces;
        i = 0;
        base = (s32) SetN64_GetPackSection(obj, i);
        if (count > 0) {
            do {
                if (piece[i].tag == -1) {
                    piece[i].tag = 0;
                } else {
                    piece[i].tag = Scene_GetIndexedModelResource(world, piece[i].tag);
                }
                piece[i].relocatedOffset18 = base + piece[i].relocatedOffset18;
                piece[i].relocatedOffset1C = base + piece[i].relocatedOffset1C;
                piece[i].relocatedOffset20 = base + piece[i].relocatedOffset20;
                piece[i].relocatedOffset24 = base + piece[i].relocatedOffset24;
                piece[i].relocatedOffset28 = base + piece[i].relocatedOffset28;
                piece[i].relocatedOffset2C = base + piece[i].relocatedOffset2C;
                piece[i].relocatedOffset30 = base + piece[i].relocatedOffset30;
                piece[i].relocatedOffset34 = base + piece[i].relocatedOffset34;
                piece[i].relocatedOffset38 = base + piece[i].relocatedOffset38;
                i++;
            } while (i < count);
        }
    }
}
void Scene_ScaleDefinitionFields(s32 requestOwner, void ***handle) {
    f32 scale;
    void *obj;
    Ent *ent;
    s32 count;
    s32 i;

    scale = k_sceneDefinitionFieldScale_de;
    if (Ppdecom_UnpackResource(handle, 0) != 0) {
        obj = **handle;
        count = *(s32 *) obj;
        for (i = 0; i < count; i++) {
            ent = SetN64_GetPackSection(obj, i);
            switch (ent->kind) {
            case 1:
                ent->scaledValueA = ent->scaledValueA * scale;
                ent->scaledValueB = ent->scaledValueB * scale;
                ent->scaledValueC = ent->scaledValueC * scale;
                ent->scaledValueD = ent->scaledValueD * scale;
                ent->scaledValueE = ent->scaledValueE * scale;
                ent->scaledValueF = ent->scaledValueF * scale;
                break;
            case 11:
                ent->scaledKind11ValueA = ent->scaledKind11ValueA * scale;
                ent->scaledKind11ValueB = ent->scaledKind11ValueB * scale;
                break;
            case 0:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
                break;
            }
        }
    }
}
void Scene_ResolveFrameItemReferences(SceneTriggerQueueOwner *scene, void ***handle) {
    void *obj;
    ParticleEffectRelocationFrame *frame;
    SceneFrameItemBank *bank;
    struct SceneFrameItemReference *items;
    struct SceneFrameItemReference *item;
    ParticleEffectRelocationSlot *slot;
    s32 count;
    s32 inner;
    s32 i;
    s32 j;
    s32 index;

    if (Ppdecom_UnpackResource(handle, 0) != 0) {
        obj = **handle;
        count = *(s32 *) obj;
        for (i = 0; i < count; i++) {
            frame = SetN64_GetPackSection(SetN64_GetPackSection(obj, i), 1);
            inner = frame->count;
            j = 0;
            if (j < inner) {
                slot = frame->slots;
                do {
                    index = slot->item;
                    if (index != -1) {
                        bank = SetN64_GetPackSection(scene->modelBankData, 2);
                        items = bank->items;
                        if ((index < 0) || (index >= bank->count)) {
                            item = 0;
                        } else {
                            item = &items[index];
                        }
                        slot->item = (s32) item;
                    } else {
                        slot->item = 0;
                    }
                    slot++;
                    j++;
                } while (j < inner);
            }
        }
        scene->frameResourceData = obj;
    }
}

#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_US)
const char g_sceneConstructMapObjectIndexText[35] =
    "CScene__ConstructMap: object index\000";
#endif
#if defined(VERSION_EU_X)
const char g_sceneConstructMapObjectIndexText[36] =
    "CScene__ConstructMap: object index\000\000";
#endif
#endif

#if defined(VERSION_US_REV1)

#endif

#if defined(VERSION_US_REV1)

#endif

#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X)

#endif

#if defined(VERSION_EU) || defined(VERSION_US)

#endif

#if defined(VERSION_EU_X)

#endif

#if defined(VERSION_US_REV1)

#endif

#if defined(VERSION_US)

#endif

#if defined(VERSION_US_REV1)
const char g_cartridgeIndex[16] = "cartridge index";

#endif

/* Retained data for this translation unit. */
#if defined(VERSION_US_REV1)
const u8 g_constructMapObjectIndex[35] =
    "CScene__ConstructMap: object index";
#endif
#if defined(VERSION_US_REV1)
const u8 g_constructMapSimpleModel[35] =
    "CScene__ConstructMap: simple model";
#endif
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X)
const char k_constructMapSimpleModelStrings[75] =
    "CScene__ConstructMap: simp models index\0"
    "CScene__ConstructMap: simple model\0";
#endif
#if defined(VERSION_EU) || defined(VERSION_US)
const char k_ovlsceneLoadsceneresourcesDataTextBytes[29] =
    "cartridge index\000levels index";
#endif
#if defined(VERSION_EU_X)
const unsigned char s_sceneResourceIndexTagsEuX[29] = {
    0x63, 0x61, 0x72, 0x74, 0x72, 0x69, 0x64, 0x67, 0x65, 0x20, 0x69, 0x6E, 0x64, 0x65, 0x78, 0x00,
    0x6C, 0x65, 0x76, 0x65, 0x6C, 0x73, 0x20, 0x69, 0x6E, 0x64, 0x65, 0x78, 0x00,
};
#endif
#if defined(VERSION_US_REV1)
const char g_constructMapSimpModelsIndex[40] = "CScene__ConstructMap: simp models index";
#endif
#if defined(VERSION_US)
const char g_sceneConstructMapModelTextPool[75] =
    "CScene__ConstructMap: simp models index\0"
    "CScene__ConstructMap: simple model\0";
#endif
#if defined(VERSION_US_REV1)
const char k_levelsIndexText[13] = "levels index";
#endif
