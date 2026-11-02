#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "include_asm.h"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/MENU_INITIALIZEOPTIONSSCENE.H"
#include "TYPES.H"
#include "MENU/EXTERNS.H"
#include "COMMON/SCREEN.H"

/* 80406A88_12.CPP */
#if defined(VERSION_EU_X)
/* Dispatches event eventId through this file's 12-byte handler table, whose rows hold an event at g_matchMenuEventIds, an actor kind at g_matchMenuEventKinds and a handler at g_matchMenuEventHandlers: the first row whose event equals eventId and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from Menu_DispatchOptionsTransitionEvent. */

s32 Match_DispatchEuxMatchMenuEvent(void *eventObject, s32 eventId, s32 eventPayload, s32 eventValue, s32 eventExtra) {
    char *entry;
    s32 offset;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;

    if (g_matchMenuEventHandlers != 0) {
        wildcard = 30000;
        entry = (char *)&g_matchMenuEventHandlers;
        offset = 0;
        do {
            if (((struct AnimationEventMaskView *) (((char *) (&g_matchMenuEventIds)) + offset))->value == eventId) {
                actor_kind = ((struct MenuActorInputView *) ((char *) eventObject))->input;
                table_kind = ((struct AnimationEventMaskView *) (((char *) (&g_matchMenuEventKinds)) + offset))->value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*(WidgetEventHandler *)entry)(eventObject, eventId, eventPayload, eventValue, eventExtra);
                }
            }
            entry += sizeof(ResidentEventHandlerEntry);
            offset += 12;
        } while (*(WidgetEventHandler *)entry != 0);
    }
    return 0;
}
#endif


/* 80408AC4.CPP */
#if defined(VERSION_DE)
unsigned int g_matchPackedCodeAddresses_de[3] = {
    0x004297A8, 0x00429754, 0x004297A8,
};
#endif

#if defined(VERSION_DE)
#include "COMMON/OWNERRECAT8V1.H"

s32 Match_ClearGermanLoadingHints(void) {
    SmpButton_WrapButtonWidget(469);
    SmpButton_WrapButtonWidget(470);
    return 0;
}
#endif

#if defined(VERSION_DE)
#include "FRONTEND/MATCH_MENU_MESSAGE_IDS.H"
#include "MENU/PAK_LOAD.H"
#include "COMMON/GAME_SESSION.H"
#include "COMMON/MENULISTSCREEN.H"
#include "COMMON/REQUESTRECAT10.H"

/* Handles the menu message Menu_GetFocusedElementId reports after MarkMenuEventHandled. 0x1D5: when
   Menu_GetPreviousScreenOwner(0) reports 0x16 it stops the menu object and the menu data g_playerViewRenderContext, releases
   g_world_AchieveUpdateresultsscreen, restarts Cache_SetResourceActivityState when Cache_GetResourceActivityState reports it idle, sets the menu stage to 8
   and sends Random_SetMenuChoiceResult 20, 10, 15 or 10 by the controller mode (3 for any other mode); otherwise
   it sends 3. 0x1D6 sends 11 when Menu_GetPreviousScreenOwner(0) reports 11 and -1 otherwise. Either then calls
   Menu_ReturnToPreviousScreen. Returns zero. */
extern void Pools_ResetActorPools(struct DraftOwnerA370 *owner, s32 actorCount);
extern void Player_InitializePlayerPool(struct CPlayerPool_t *pool, s32 count, s32 force_active);
extern void Scene_LoadLevelResources(void *, s32, s32);
extern s32 Cache_GetResourceActivityState(void);
extern void Cache_SetResourceActivityState(unsigned int);
extern void Menu_ReturnToPreviousScreen(void);

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
