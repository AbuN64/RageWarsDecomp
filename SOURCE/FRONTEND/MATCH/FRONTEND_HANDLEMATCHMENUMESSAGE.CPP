#include "COMMON/SCREEN.H"
#include "COMMON/WORLD.H"
#include "include_asm.h"
#include "OPTIONS.H"
#include "TYPES.H"
#include "COMMON/INTEGERSTATE530.H"
#include "COMMON/REQUESTRECAT10.H"
#include "COMMON/MENULISTSCREEN.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/ITEMRECAT20V1.H"

/* 80423280_45.CPP */
#if !defined(VERSION_DE)
#include "FRONTEND/MATCH_MENU_MESSAGE_IDS.H"
#include "TYPES.H"

/* Handles the menu message Menu_GetFocusedElementId reports after MarkMenuEventHandled. 0x1D9: when
   Menu_GetPreviousScreenOwner(0) reports 0x16 it stops the menu object and the menu data g_playerViewRenderContext, releases
   g_world_AchieveUpdateresultsscreen, restarts Cache_SetResourceActivityState when Cache_GetResourceActivityState reports it idle, sets the menu stage to 8
   and sends Random_SetMenuChoiceResult 20, 10, 15 or 10 by the controller mode (3 for any other mode); otherwise
   it sends 3. 0x1DA sends 11 when Menu_GetPreviousScreenOwner(0) reports 11 and -1 otherwise. Either then calls
   Menu_ReturnToPreviousScreen. Returns zero. */
#include "MENU/PAK_LOAD.H"

extern void Pools_ResetActorPools(struct DraftOwnerA370 *owner, s32 actorCount);
extern void Player_InitializePlayerPool(struct CPlayerPool_t *pool, s32 count, s32 force_active);
extern void Scene_LoadLevelResources(void *, s32, s32);
extern s32 Cache_GetResourceActivityState(void);
extern void Cache_SetResourceActivityState(unsigned int);

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

/* 80423280_46.CPP */
#if defined(VERSION_US) || defined(VERSION_US_REV1)
/* Dispatches event eventId through this file's 12-byte handler table, whose rows hold an event at g_matchMenuEventIds, an actor kind at g_matchMenuEventKinds and a handler at g_matchMenuEventHandlers: the first row whose event equals eventId and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from N64Eng_DispatchNumericWidgetEvent. */

typedef s32 (*MatchMenuEventHandler)(void *, s32, s32, s32, s32);

extern FieldRow g_matchMenuEventIds[];
extern FieldRow g_matchMenuEventKinds[];
extern MatchMenuEventHandler g_matchMenuEventHandlers;

struct MenuActorInputView;

s32 Frontend_DispatchMatchMenuEvent(void *eventObject, s32 eventId, s32 eventPayload, s32 eventValue, s32 eventExtra) {
    MatchMenuEventHandler *entry;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;
    MenuActorInputView *actor;

    if (g_matchMenuEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_matchMenuEventHandlers;
        index = 0;
        do {
            if (g_matchMenuEventIds[index].value == eventId) {
                actor = eventObject;
                actor_kind = actor->input;
                table_kind = g_matchMenuEventKinds[index].value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*entry)(eventObject, eventId, eventPayload, eventValue, eventExtra);
                }
            }
            entry += 3;
            index++;
        } while (*entry != 0);
    }
    return 0;
}
#endif
