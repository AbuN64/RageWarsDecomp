#include "TYPES.H"
#include "COMMON/LONE/SCREEN_IMAGE_RESOURCES_ENABLED.H"
#include "COMMON/AUDIO_CALLBACKS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "MENU/SCENE_RESOURCE_PREVIEW_AND_COLLISION_VIEWS.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/CACHE_RELEASERESOURCE.H"
#include "COMMON/SCENE_FRAME_AND_EFFECT_UPDATES.H"
#include "COMMON/ENTRYRECAT0V3.H"
#include "COMMON/PLAYER_POOL_AND_INODE_CACHE_VIEWS.H"
#include "COMMON/OBJB.H"
#include "AI/NAV/PORTAL_LOADCOLLISIONTABLE.H"
#include "ENGINE/SCENE.H"
#include "MENU/ITEMS/SCENE/SELECTION_PREVIEW_OPERATIONS.H"
#include "MENU/PAK/MENU_ISTRACKREQUESTITEM.H"

extern void Player_RefreshActivePlayerSceneState(CPlayerPool *);
extern void Cache_DrainAndCompactResources(s32 unusedHeap);
extern s32 Cache_RequestWordCountedResourcePinned(s32,void **,s32,void *);
extern void **Cache_RequestPackSection(s32,s32,s32,s32,s32,s32,void *);
extern int SetN64_GetDirectoryEntry(int *,int,int);
extern s32 SetN64_LocatePackSection(s32,s32,s32,s32 *);
extern s32 g_cResource_UnpackRequestEntry;
extern char g_sceneCollisionStorage;
void Scene_LoadSceneResources(SceneLoadResourcesView *sceneToLoad, s32 cartridgeBankKey) {
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
    sceneToLoad->reservedWord = 0;
    Scene_ResetSelectionState((char *)sceneToLoad);
    sceneToLoad->reservedWord1 = 0;
    sceneToLoad->reservedWord2 = 0;
    sceneToLoad->visibilityGroup = -1;
    sceneToLoad->reservedWord13 = 0;
    sceneToLoad->reservedWord12 = 0;
    sceneToLoad->spawnOffsetX = 0;
    sceneToLoad->spawnOffsetY = 0;
    sceneToLoad->spawnOffsetZ = 0;
    sceneToLoad->reservedWord14 = 0;
    sceneToLoad->selectedActorCount = 0;
    sceneToLoad->sceneLoadResetState = 0;
    /* The global is the holder storage; its canonical scalar declaration is incomplete. */
    ((void (*)(void *))Player_RefreshActivePlayerSceneState)(&g_playerViewRenderContext);
    /* The original resource API passes the unused arena argument. */
    Cache_DrainAndCompactResources(0);
    Cache_RequestWordCountedResourcePinned(0, (void **)&cartridgeDirectory, cartridgeBankKey, &g_cartridgeIndex);
    levelDirectoryKey = SetN64_GetDirectoryEntry(cartridgeDirectory, cartridgeBankKey, 5);
    sceneToLoad->levelDirectoryKey = levelDirectoryKey;
    Cache_RequestWordCountedResourcePinned(0, &sceneToLoad->levelDirectoryHandle, levelDirectoryKey, &g_sceneDirectoryResourceTag);
    textureDirectoryKey = SetN64_GetDirectoryEntry(cartridgeDirectory, cartridgeBankKey, 3);
    sceneToLoad->textureDirectoryKey = textureDirectoryKey;
    Cache_RequestWordCountedResourcePinned(0, &sceneToLoad->textureDirectoryHandle, textureDirectoryKey, &g_textureSetsIndex);
    sceneToLoad->objectTypes = (s32) *Cache_RequestPackSection(0, (s32)cartridgeDirectory, 2, cartridgeBankKey, (s32)sceneToLoad, (s32)&g_cResource_UnpackRequestEntry, &g_objectTypesText);
    objectDirectoryKey = SetN64_GetDirectoryEntry(cartridgeDirectory, cartridgeBankKey, 0);
    sceneToLoad->objectDirectoryKey = objectDirectoryKey;
    Cache_RequestWordCountedResourcePinned(0, &sceneToLoad->objectDirectoryHandle, objectDirectoryKey, &g_objectsIndex);
    sceneToLoad->geometry = (s32) *Cache_RequestPackSection(0, (s32)cartridgeDirectory, 1, cartridgeBankKey, (s32)sceneToLoad, (s32)&g_sceneGeometrySectionTag, &g_sceneGeometryResourceTag);
    sceneToLoad->particleEffectHandle = Cache_RequestPackSection(0, (s32)cartridgeDirectory, 4, cartridgeBankKey, (s32)sceneToLoad, (s32)&g_sceneParticleEffectSectionTag, &g_particleEffects);
    sceneToLoad->sectionTenObjectTypes = (s32) *Cache_RequestPackSection(0, (s32)cartridgeDirectory, 10, cartridgeBankKey, (s32)sceneToLoad, (s32)&g_cResource_UnpackRequestEntry, &g_objectTypesText);
    binaryDirectoryKey = SetN64_GetDirectoryEntry(cartridgeDirectory, cartridgeBankKey, 9);
    sceneToLoad->binaryDirectoryKey = binaryDirectoryKey;
    Cache_RequestWordCountedResourcePinned(0, &sceneToLoad->binaryDirectoryHandle, binaryDirectoryKey, &g_binariesIndexText);
    sceneToLoad->particleSwooshes = (s32) *Cache_RequestPackSection(0, (s32)cartridgeDirectory, 11, cartridgeBankKey, (s32)sceneToLoad, (s32)&g_cResource_UnpackRequestEntry, &g_particleSwooshes);
    sectionTwelveData = (s32) *Cache_RequestPackSection(0, (s32)cartridgeDirectory, 12, cartridgeBankKey, (s32)sceneToLoad, (s32)&g_cResource_UnpackRequestEntry, &g_sceneSectionTwelveResourceTag);
    sceneToLoad->placedActorStorage = &g_worldSnapshotNoteData;
    sceneToLoad->sectionTwelveData = sectionTwelveData;
    sceneToLoad->sectionSixAddress = SetN64_LocatePackSection((s32)cartridgeDirectory, cartridgeBankKey, 6, &sceneToLoad->sectionSixSize);
    sceneToLoad->collisionStorage = &g_sceneCollisionStorage;
    sceneToLoad->sectionSevenAddress = SetN64_LocatePackSection((s32)cartridgeDirectory, cartridgeBankKey, 7, &sceneToLoad->sectionSevenSize);
    warpDestinationsResource = Cache_RequestPackSection(0, (s32)cartridgeDirectory, 8, cartridgeBankKey, (s32)sceneToLoad, (s32)&g_cResource_UnpackRequestEntry, &g_warpDests);
    sceneToLoad->warpDestinationsHandle = warpDestinationsResource;
    sceneToLoad->warpDestinations = (s32) *warpDestinationsResource;
    sceneToLoad->curves = (s32) *Cache_RequestPackSection(0, (s32)cartridgeDirectory, 13, cartridgeBankKey, (s32)sceneToLoad, (s32)&g_cResource_UnpackRequestEntry, &g_curves);
    sceneToLoad->rumbleLabels = (s32) *Cache_RequestPackSection(0, (s32)cartridgeDirectory, 14, cartridgeBankKey, (s32)sceneToLoad, (s32)&g_cResource_UnpackRequestEntry, &g_rumbleLabels);
    sceneToLoad->sectionFifteenData = (s32) *Cache_RequestPackSection(0, (s32)cartridgeDirectory, 15, cartridgeBankKey, (s32)sceneToLoad, (s32)&g_cResource_UnpackRequestEntry, &g_sceneSectionFifteenResourceTag);
    sceneToLoad->graphicsetTypes = (s32) *Cache_RequestPackSection(0, (s32)cartridgeDirectory, 17, cartridgeBankKey, (s32)sceneToLoad, (s32)&g_cResource_UnpackRequestEntry, &g_graphicsetType);
    graphicsetDirectoryKey = SetN64_GetDirectoryEntry(cartridgeDirectory, cartridgeBankKey, 16);
    sceneToLoad->graphicsetDirectoryKey = graphicsetDirectoryKey;
    Cache_RequestWordCountedResourcePinned(0, &sceneToLoad->graphicsetDirectoryHandle, graphicsetDirectoryKey, &g_graphicsetIndex);
    sectionEighteenKey = SetN64_GetDirectoryEntry(cartridgeDirectory, cartridgeBankKey, 18);
    sceneToLoad->sectionEighteenKey = sectionEighteenKey;
    Cache_RequestWordCountedResourcePinned(0, &sceneToLoad->cinemaDirectoryHandle, sectionEighteenKey, &g_cinemasIndexText);
    Menu_RequestTrackBundle();
    linkGroupTypeData = (s32) *Cache_RequestPackSection(0, (s32)cartridgeDirectory, 19, cartridgeBankKey, (s32)sceneToLoad, (s32)&g_cResource_UnpackRequestEntry, &g_linkGroupTypes);
    sceneToLoad->bloodlustDirectoryKey = 0;
    sceneToLoad->bloodlustDirectorySize = 0;
    sceneToLoad->reservedWord3 = 0;
    sceneToLoad->reservedWord4 = -1;
    sceneToLoad->linkGroupTypes = linkGroupTypeData;
    if (*cartridgeDirectory >= 22) {
        sceneToLoad->bloodlustDirectoryKey = SetN64_GetDirectoryEntry(cartridgeDirectory, cartridgeBankKey, 21);
        bloodlustLevelResource = /* This callee returns its allocated resource handle, not an integer ID. */
            ((void **(*)(s32,void **,s32,void *,s32))Cache_RequestWordCountedResource)(0, (void **)&bloodlustLevelDirectory, sceneToLoad->bloodlustDirectoryKey, &g_constructBlLevelDataIndex, 1);
        if (bloodlustLevelResource != 0) {
            sceneToLoad->bloodlustDirectorySize = (s32) (((*bloodlustLevelDirectory * 4) + 15) & ~7);
            Cache_ReleaseResource(0, bloodlustLevelResource);
        } else {
            sceneToLoad->bloodlustDirectoryKey = 0;
        }
    }
    if (*cartridgeDirectory >= 24) {
        bloodlustWeaponResource = Cache_RequestPackSection(0, (s32)cartridgeDirectory, 23, cartridgeBankKey, (s32)sceneToLoad, (s32)&g_cResource_UnpackRequestEntry, &g_bloodlustWeaponData);
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
    sceneToLoad->reservedWord6 = 0;
    sceneToLoad->reservedWord7 = 0;
    sceneToLoad->reservedWord9 = 0;
    sceneToLoad->reservedWord8 = 0;
    sceneToLoad->reservedWord5 = 0;
    sceneToLoad->reservedWord10 = 0;
    sceneToLoad->reservedWord11 = 0;
    Scene_LoadLevelResources(sceneToLoad, 0, 0);
}
