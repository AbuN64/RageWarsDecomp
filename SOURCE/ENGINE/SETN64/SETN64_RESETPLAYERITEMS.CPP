#include "COMMON/GAMEPLAY_CAMERA.H"
#include "COMMON/WORLD.H"
#include "COMMON/SESSIONHANDLERROW.H"
#include "ENGINE/SETN64.H"
#include "TYPES.H"
#include "MENU/ITEMS/SCENE/OVLSCENE_FINDPLACEDOBJECTSBYKEY.H"
#include "MENU/ITEMS/SCENE/SCENE_BUILDPLACEDACTORS.H"
#include "MENU/ITEMS/SCENE/SCENE_UPDATEPENDINGOBJECTS.H"

extern void Pools_ResetActorPools(struct ScreenMessageOwner *owner, s32 actorCount);
extern void Player_InitializePlayerPool(struct CPlayerPool_t *pool, s32 count, s32 force_active);
extern s32 Track_RequestTrackByKey(s32);








void SetN64_ResetPlayerItems(s32 sessionAddress, s32 selectionKey) {
    SessionPlayerItemResetView *object = (void *)sessionAddress;
    Pools_ResetActorPools(&object->actorPools, 1);
    Player_InitializePlayerPool(&object->playerPool, (void *)1, 0);
    Scene_SetSelection(&g_world, ~Track_RequestTrackByKey(selectionKey), 0);
    Scene_LoadPreviewBufferA(&g_world);
    Scene_LoadPreviewBufferB(&g_world);
}
