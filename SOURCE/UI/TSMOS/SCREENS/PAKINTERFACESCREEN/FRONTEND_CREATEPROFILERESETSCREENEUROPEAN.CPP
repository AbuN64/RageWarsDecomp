#include "include_asm.h"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/FRONTEND_RESOURCE_LOAD_STATE.H"
#include "COMMON/NODERECAT2A8.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "TYPES.H"
#include "FRONTEND/NODE_FINDWIDGETBYRESOURCEID.H"
#include "COMMON/PLAYERPROFILES.H"
#if defined(VERSION_EU)
#include "COMMON/OBJECTRECAT28.H"
#include "COMMON/SHARED_WORLDFUNC.H"
#include "COMMON/WORLD.H"
/* 8042FBEC_9.CPP */
extern struct Record *Cache_AllocateMemory(s32 size);
extern void Player_InitializeProfile(void *profileStorage);
extern Pulse *g_profileResetScreen;
extern void Pools_ResetActorPools(struct DraftOwnerA370 *owner, s32 actorCount);
extern void Player_InitializePlayerPool(struct CPlayerPool_t *pool, s32 count, s32 force_active);
extern void Scene_LoadLevelResources(void *, s32, s32);
extern s32 Cache_GetResourceActivityState(void);
extern void Cache_SetResourceActivityState(u32);
extern void Frontend_RequestScreenMode(s32);
extern void Tsmos_DeactivateControllerState(void);
extern void Tsmos_SetIdleTimer(f32);
s32 Frontend_CreateProfileResetScreenEuropean(MenuWidget *tree) {
    s32 i;
    Shared_Game *settings;
    Shared_PlayerSettingsRecord *record;
    Shared_MenuObject *object;

    g_profileResetScreen = Cache_AllocateMemory(sizeof(*g_profileResetScreen));
    object = &g_playerViewRenderContext.object;
    Pools_ResetActorPools(object, 0);
    Player_InitializePlayerPool(&g_playerViewRenderContext, 0, 0);
    Scene_LoadLevelResources(&g_world, 0, 0);
    if (Cache_GetResourceActivityState() == 0) {
        Cache_SetResourceActivityState(1);
    }
    Frontend_RequestScreenMode(0);
    i = 7;
    Tsmos_DeactivateControllerState();
    record = &object->playerSettings[7];
    do {
        record->enabled = 0;
        i--;
        record--;
    } while (i >= 0);
    g_profileResetScreen->widget = Node_FindWidgetByResourceId(tree, 919);
    g_profileResetScreen->phase = 0;
    settings = &g_gameSettings;
    settings->laps = 10;
    settings->players = 10;
    for (i = 0; i < 4; i++) {
        Player_InitializeProfile(&g_localPlayerProfiles[i]);
    }
    Tsmos_SetIdleTimer(0.0f);
    return 0;
}
#endif
