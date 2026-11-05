#include "Frontend/frontend.h"
#include "Frontend/match_menu_message_ids.h"
#include "Common/gameplay_camera.h"
#include "Common/resident_event_handler.h"
#include "include_asm.h"
#include "Common/sharedplayer.h"
#include "Common/aiprofile.h"
#include "Common/menu_initializeoptionsscene.h"
#include "types.h"
#include "Menu/externs.h"
#include "Frontend/frontend_address_symbols.h"
#include "Common/screen.h"
#include "Common/shared_menureply.h"
#include "Common/menu_screen_elements.h"
#include "Common/world.h"
#include "options.h"
#include "Common/player_join_requests.h"
#include "Common/menulistscreen.h"
#include "Common/cheatcode.h"
#include "Menu/menu_dispatchgermanmatchmenuevent.h"
#include "Common/runtime_declarations.h"

/* unit MATCH_SPLIT.CPP */
#if defined(VERSION_EU_X)
/* Calls the handler of the first row of g_matchMenuEventIds whose event equals eventId and whose kind equals the actor's kind or is the any-kind wildcard 30000. Returns the handler's result, or zero when no row matches. */
s32 Match_DispatchEuxMatchMenuEvent(void *eventObject, s32 eventId, s32 eventPayload, s32 eventValue, s32 eventExtra) {
    ResidentEventHandlerEntry *row = g_matchMenuEventIds;
    MenuWidget *actor = eventObject;
    for (; row->handler != 0; ++row) {
        if (row->event == eventId &&
            (row->actorKind == actor->resource || row->actorKind == ANY_ACTOR_KIND)) {
            return row->handler(eventObject, eventId, eventPayload, eventValue, eventExtra);
        }
    }
    return 0;
}
#endif

#if defined(VERSION_DE)
unsigned int g_matchPackedCodeAddresses_de[3] = {
    0x004297A8, 0x00429754, 0x004297A8,
};
#endif

#if defined(VERSION_DE)
#include "Common/menu_overlay.h"

s32 Match_ClearGermanLoadingHints(void) {
    SmpButton_WrapButtonWidget(469);
    SmpButton_WrapButtonWidget(470);
    return 0;
}
#endif

#if defined(VERSION_DE)
#include "Menu/pak_load.h"
#include "Common/game_session.h"
#include "Common/menulistscreen.h"
#include "Common/player_join_requests.h"
#include "Match/match_split.h"
#include "Cache/cache_allocresourceblock.h"

/* Handles the menu message Menu_GetFocusedElementId reports after MarkMenuEventHandled. 0x1D5: when
   Menu_GetPreviousScreenOwner(0) reports 0x16 it stops the menu object and the menu data g_playerViewRenderContext, releases
   g_world_AchieveUpdateresultsscreen, restarts Cache_SetResourceActivityState when Cache_GetResourceActivityState reports it idle, sets the menu stage to 8
   and sends Random_SetMenuChoiceResult 20, 10, 15 or 10 by the controller mode (3 for any other mode); otherwise
   it sends 3. 0x1D6 sends 11 when Menu_GetPreviousScreenOwner(0) reports 11 and -1 otherwise. Either then calls
   Menu_ReturnToPreviousScreen. Returns zero. */
s32 Match_HandleMatchMessage(void) {
    MarkMenuEventHandled();
    switch (Menu_GetFocusedElementId()) {
    default:
        return 0;
    case MATCH_MENU_ELEMENT_LOAD_LEVEL_RESOURCES:
        if (Menu_GetPreviousScreenOwner(0) == 22) {
            Pools_ResetActorPools(&g_playerViewRenderContext.object, 0);
            Player_InitializePlayerPool(&g_playerViewRenderContext, 0, 0);
            Scene_LoadLevelResources(&g_world, 0, 0);
            if (Cache_GetResourceActivityState() == 0) {
                Cache_SetResourceActivityState(1);
            }
            g_playerViewRenderContext.stage = 8;
            switch (g_playerViewRenderContext.game.controllerMode) {
            case 0:
                Random_SetMenuChoiceResult(20);
                break;
            case 1:
                Random_SetMenuChoiceResult(10);
                break;
            case 2:
                Random_SetMenuChoiceResult(15);
                break;
            case 3:
            case 4:
                Random_SetMenuChoiceResult(10);
                break;
            default:
                Random_SetMenuChoiceResult(3);
                break;
            }
        } else {
            Random_SetMenuChoiceResult(3);
        }
        break;
    case MATCH_MENU_ELEMENT_RETURN_PREVIOUS_OWNER:
        if (Menu_GetPreviousScreenOwner(0) == 11) {
            Random_SetMenuChoiceResult(11);
        } else {
            Random_SetMenuChoiceResult(-1);
        }
        break;
    }
    Menu_ReturnToPreviousScreen();
    return 0;
}
#endif

/* unit FRONTEND_HANDLEMATCHMENUMESSAGE.CPP */
#if !defined(VERSION_DE)
#include "types.h"

/* Handles the menu message Menu_GetFocusedElementId reports after MarkMenuEventHandled. 0x1D9: when
   Menu_GetPreviousScreenOwner(0) reports 0x16 it stops the menu object and the menu data g_playerViewRenderContext, releases
   g_world_AchieveUpdateresultsscreen, restarts Cache_SetResourceActivityState when Cache_GetResourceActivityState reports it idle, sets the menu stage to 8
   and sends Random_SetMenuChoiceResult 20, 10, 15 or 10 by the controller mode (3 for any other mode); otherwise
   it sends 3. 0x1DA sends 11 when Menu_GetPreviousScreenOwner(0) reports 11 and -1 otherwise. Either then calls
   Menu_ReturnToPreviousScreen. Returns zero. */
#include "Menu/pak_load.h"
#include "Match/frontend_handlematchmenumessage.h"
#include "Cache/cache_allocresourceblock.h"
#include "Frontend/frontend_address_symbols.h"

s32 Frontend_HandleMatchMenuMessage(void) {
    MarkMenuEventHandled();
    switch (Menu_GetFocusedElementId()) {
    default:
        return 0;
    case MATCH_MENU_ELEMENT_LOAD_LEVEL_RESOURCES:
        if (Menu_GetPreviousScreenOwner(0) == 22) {
            Pools_ResetActorPools(&g_playerViewRenderContext.object, 0);
            Player_InitializePlayerPool(&g_playerViewRenderContext, 0, 0);
            Scene_LoadLevelResources(&g_world, 0, 0);
            if (Cache_GetResourceActivityState() == 0) {
                Cache_SetResourceActivityState(1);
            }
            g_playerViewRenderContext.stage = 8;
            switch (g_playerViewRenderContext.game.controllerMode) {
            case 0:
                Random_SetMenuChoiceResult(20);
                break;
            case 1:
                Random_SetMenuChoiceResult(10);
                break;
            case 2:
                Random_SetMenuChoiceResult(15);
                break;
            case 3:
            case 4:
                Random_SetMenuChoiceResult(10);
                break;
            default:
                Random_SetMenuChoiceResult(3);
                break;
            }
        } else {
            Random_SetMenuChoiceResult(3);
        }
        break;
    case MATCH_MENU_ELEMENT_RETURN_PREVIOUS_OWNER:
        if (Menu_GetPreviousScreenOwner(0) == 11) {
            Random_SetMenuChoiceResult(11);
        } else {
            Random_SetMenuChoiceResult(-1);
        }
        break;
    }
    Menu_ReturnToPreviousScreen();
    return 0;
}
#endif

/* Calls MarkMenuEventHandled, then passes 0xB to Random_SetMenuChoiceResult when Menu_GetPreviousScreenOwner reports 0xB for zero
   and -1 otherwise, then calls Menu_ReturnToPreviousScreen. Returns zero. */
s32 Frontend_CloseMatchMenu(void) {
    MarkMenuEventHandled();
    Random_SetMenuChoiceResult(Menu_GetPreviousScreenOwner(0) == 11 ? 11 : -1);
    Menu_ReturnToPreviousScreen();
    return 0;
}

#if defined(VERSION_US) || defined(VERSION_US_REV1)
/* Dispatches event eventId through this file's 12-byte handler table, whose rows hold an event at g_matchMenuEventIds, an actor kind at g_matchMenuEventKinds and a handler at g_matchMenuEventHandlers: the first row whose event equals eventId and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from N64Eng_DispatchNumericWidgetEvent. */

typedef s32 (*MatchMenuEventHandler)(void *, s32, s32, s32, s32);



/* Calls the handler of the first row of g_matchMenuEventIds whose event equals eventId and whose kind equals the actor's kind or is the any-kind wildcard 30000. Returns the handler's result, or zero when no row matches. */
s32 Frontend_DispatchMatchMenuEvent(void *eventObject, s32 eventId, s32 eventPayload, s32 eventValue, s32 eventExtra) {
    ResidentEventHandlerEntry *row = g_matchMenuEventIds;
    MenuWidget *actor = eventObject;
    for (; row->handler != 0; ++row) {
        if (row->event == eventId &&
            (row->actorKind == actor->resource || row->actorKind == ANY_ACTOR_KIND)) {
            return row->handler(eventObject, eventId, eventPayload, eventValue, eventExtra);
        }
    }
    return 0;
}
#endif

/* unit MATCH.CPP */
#if defined(VERSION_DE)
/* Calls the handler of the first row of g_germanMatchMenuEventIds whose event equals eventId and whose kind equals the actor's kind or is the any-kind wildcard 30000. Returns the handler's result, or zero when no row matches. */
s32 Menu_DispatchGermanMatchMenuEvent(void *eventObject, s32 eventId, s32 eventPayload, s32 eventValue, s32 eventExtra) {
    s32 index;
    struct MenuWidget *actor = eventObject;
    for (index = 0; g_germanMatchMenuEventIds[index].handler != 0; index++) {
        ResidentEventHandlerEntry *entry = &g_germanMatchMenuEventIds[index];
        if (entry->event == eventId &&
            (entry->actorKind == actor->resource || entry->actorKind == ANY_ACTOR_KIND)) {
            return entry->handler(eventObject, eventId, eventPayload, eventValue, eventExtra);
        }
    }
    return 0;
}
#endif

/* unit MATCH_DISPATCHEUMATCHMENUEVENT.CPP */
#if defined(VERSION_EU)
#include "Common/resident_event_handler.h"
#include "Frontend/frontend_address_symbols.h"
#include "Frontend/frontend.h"

s32 Match_DispatchEuMatchMenuEvent(MenuWidget *pThis, s32 event, s32 eventPayload, s32 eventValue, s32 eventExtra) {
    s32 i;
    for (i = 0; g_matchMenuEventIds[i].handler != 0; i++) {
        if (g_matchMenuEventIds[i].event == event &&
            (g_matchMenuEventIds[i].actorKind == pThis->resource || g_matchMenuEventIds[i].actorKind == 30000)) {
            return g_matchMenuEventIds[i].handler(pThis, event, eventPayload, eventValue, eventExtra);
        }
    }
    return 0;
}
#endif
