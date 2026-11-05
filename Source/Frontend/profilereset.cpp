#include "Menu/widget_records.h"
#include "Common/gameplay_camera.h"
#include "Common/resident_event_handler.h"
#include "Frontend/node_findwidgetbyresourceid.h"
#include "include_asm.h"
#include "Common/playerprofiles.h"
#include "Common/menu_model_preview.h"
#include "Common/sharedplayer.h"
#include "Common/runtime_declarations.h"
#include "types.h"
#include "Frontend/frontend_dispatchprofileresetevent.h"
#include "Scene/cache_freememory.h"
#include "Common/selectionscreenstate.h"
#include "Common/shared_menureply.h"
#include "Resmgr/tsmos_setidletimer.h"
#include "Common/screen.h"

/* unit FRONTEND_CREATEPROFILERESETSCREENGERMAN.CPP */
#if defined(VERSION_DE)
#include "Common/menu_model_preview.h"
#include "Common/shared_worldfunc.h"
#include "Common/world.h"
#include "Ai/playerprofile.h"
#include "Cache/cache_allocresourceblock.h"
#include "Frontend/screen.h"
#include "Frontend/frontend_address_symbols.h"

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

/* Releases the object g_profileResetScreen holds through Cache_FreeMemory, clears g_profileResetScreen and returns zero. */

/* On event 3 with value 0xD, calls MarkMenuEventHandled and SmXlate_SwitchScreen with 3. Returns zero. */
s32 Frontend_FreeProfileResetScreen(void) {
    Cache_FreeMemory(g_profileResetScreen);
    g_profileResetScreen = 0;
    return 0;
}

/* Advances a sine-driven pulse phase and writes the resulting display intensity byte. */
s32 Frontend_PulseProfileResetWidget(s32 element, s32 eventId, s32 phaseStep) {
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

/* Event handler placeholder: ignores the event and returns zero. */
s32 ProfileReset_ReturnUnhandledEvent(void) {
    return 0;
}

/* Calls the handler registered for eventId (tables g_profileResetEventIds, g_profileResetEventActorKinds, g_profileResetEventHandlers). A row matches when its event equals eventId and its kind equals the actor's kind or is the any-kind wildcard 0x7530. Returns the handler's result, or zero when no row matches. */
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

/* unit FRONTEND_CREATEPROFILERESETSCREENEXTENDED.CPP */
#if defined(VERSION_EU_X)
#include "Common/menu_model_preview.h"
#include "Common/shared_worldfunc.h"
#include "Common/world.h"
#include "Ai/playerprofile.h"
#include "Cache/cache_allocresourceblock.h"
#include "Frontend/screen.h"
#include "Frontend/frontend_address_symbols.h"

s32 Frontend_CreateProfileResetScreenExtended(MenuWidget *tree) {
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
    g_profileResetScreen->widget = Node_FindWidgetByResourceId(tree, 923);
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

/* unit FRONTEND_CREATEPROFILERESETSCREENUS.CPP */
#if defined(VERSION_US)
#include "Common/menu_model_preview.h"
#include "Common/shared_worldfunc.h"
#include "Common/world.h"
#include "Ai/playerprofile.h"
#include "Cache/cache_allocresourceblock.h"
#include "Frontend/screen.h"
#include "Frontend/frontend_address_symbols.h"
#include "Frontend/frontend.h"

s32 Frontend_CreateProfileResetScreenUs(MenuWidget *tree) {
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
