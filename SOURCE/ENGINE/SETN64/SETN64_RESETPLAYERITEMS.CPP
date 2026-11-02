#include "COMMON/WORLD.H"
#include "COMMON/SESSIONHANDLERROW.H"
#include "ENGINE/SETN64.H"
#include "TYPES.H"

extern void Pools_ResetActorPools(struct DraftOwnerA370 *owner, s32 actorCount);
extern void Player_InitializePlayerPool(struct CPlayerPool_t *pool, s32 count, s32 force_active);
extern s32 Track_RequestTrackByKey(s32);
extern void Scene_SetSelection(void *state, s32 selection, s32 mode);
extern void Scene_LoadPreviewBufferA(void *previewToLoad);
extern void Scene_LoadPreviewBufferB(void *state);





void SetN64_ResetPlayerItems(s32 sessionAddress, s32 selectionKey) {
    SessionPlayerItemResetView *object = (void *)sessionAddress;
    Pools_ResetActorPools(&object->actorPools, 1);
    Player_InitializePlayerPool(&object->playerPool, (void *)1, 0);
    Scene_SetSelection(&g_world, ~Track_RequestTrackByKey(selectionKey), 0);
    Scene_LoadPreviewBufferA(&g_world);
    Scene_LoadPreviewBufferB(&g_world);
}
