#include "COMMON/GAMEPLAY_CAMERA.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "FRONTEND/NODE_FINDWIDGETBYRESOURCEID.H"
#include "include_asm.h"
#include "COMMON/PLAYERPROFILES.H"
#include "COMMON/OBJECTRECAT28.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "TYPES.H"
#include "FRONTEND/FRONTEND_DISPATCHPROFILERESETEVENT.H"
#include "SCENE/CACHE_FREEMEMORY.H"

/* 80408AC4_37.CPP */
#if defined(VERSION_DE)
#include "COMMON/OBJECTRECAT28.H"
#include "COMMON/SHARED_WORLDFUNC.H"
#include "COMMON/WORLD.H"
extern struct Record *Cache_AllocateMemory(s32 size);
extern void Player_InitializeProfile(void *profileStorage);
extern Pulse *g_profileResetScreen;
extern void Pools_ResetActorPools(struct ScreenMessageOwner *owner, s32 actorCount);
extern void Player_InitializePlayerPool(struct CPlayerPool_t *pool, s32 count, s32 force_active);
extern void Scene_LoadLevelResources(void *, s32, s32);
extern s32 Cache_GetResourceActivityState(void);
extern void Cache_SetResourceActivityState(u32);
extern void Frontend_RequestScreenMode(s32);
extern void Tsmos_DeactivateControllerState(void);
extern void Tsmos_SetIdleTimer(f32);

s32 Frontend_CreateProfileResetScreenGerman(MenuWidget *tree) {
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
    g_profileResetScreen->widget = Node_FindWidgetByResourceId(tree, 913);
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

/* 8043962C_2.CPP */
/* Releases the object g_profileResetScreen holds through Cache_FreeMemory, clears g_profileResetScreen and returns zero. */

extern void Tsmos_ActivateControllerState(void);

/* On event 3 with value 0xD, calls MarkMenuEventHandled and SmXlate_SwitchScreen with 3. Returns zero. */
extern void MarkMenuEventHandled();

extern void SmXlate_SwitchScreen(s32);

s32 Frontend_FreeProfileResetScreen(void) {
    extern Pulse *g_profileResetScreen;
    Cache_FreeMemory(g_profileResetScreen);
    g_profileResetScreen = 0;
    return 0;
}

/* Advances a sine-driven pulse phase and writes the resulting display intensity byte. */
s32 Frontend_PulseProfileResetWidget(s32 unused0, s32 unused1, s32 phaseStep) {
    extern Pulse *g_profileResetScreen;
    if (g_selectionMessageStage >= 2) {
        return 0;
    }
    Tsmos_ActivateControllerState();
    g_profileResetScreen->phase += phaseStep;
    g_profileResetScreen->light->alpha = (u32)(Math_Cosf(g_profileResetScreen->phase * 0.005f) * 100.0f + 150.0f);
    return 0;
}

s32 Frontend_HandleProfileResetConfirm(void *first, void *second, u32 event, s32 value) {
    if ((event >> 16) == 3) {
        if (value != 13) {
            return 0;
        }
        MarkMenuEventHandled();
        SmXlate_SwitchScreen(3);
    }
    return 0;
}

s32 Frontend_AcknowledgeProfileResetEvent(void) {
    MarkMenuEventHandled();
    return 0;
}

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 ProfileReset_ReturnUnhandledEvent(void) {
    return 0;
}

/* Dispatches event eventId through this file's 12-byte handler table, whose rows hold an event at g_profileResetEventIds, an actor kind at g_profileResetEventActorKinds and a handler at g_profileResetEventHandlers: the first row whose event equals eventId and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from N64Eng_DispatchNumericWidgetEvent. */

s32 Frontend_DispatchProfileResetEvent(Shared_Body *widget, s32 eventId, s32 eventData0, s32 eventData1, s32 eventData2) {
    char *entry;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;

    if (g_profileResetEventHandlers != 0) {
        wildcard = 30000;
        entry = (char *)&g_profileResetEventHandlers;
        index = 0;
        do {
#if defined(VERSION_EU)
            if (g_profileResetEventIdsEu[index].value == eventId) {
#else
            if (g_profileResetEventIds[index].value == eventId) {
#endif
                actor_kind = widget->kind;
                table_kind = g_profileResetEventActorKinds[index].value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*(MenuEventHandler *)entry)(widget, eventId, eventData0, eventData1, eventData2);
                }
            }
            entry += sizeof(ResidentEventHandlerEntry);
            index++;
        } while (*(MenuEventHandler *)entry != 0);
    }
    return 0;
}
