#include "COMMON/SHARED_OPTIONSSCREEN.H"
#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/INTEGERSTATEB0.H"
#include "COMMON/MENULISTSCREEN.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SHARED_MENUREPLY.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "COMMON/MENU_MATCH_GLOBALS.H"
#include "COMMON/WORLD.H"
#include "COMMON/RESULTSOPTIONSSCREEN.H"
#include "COMMON/MENUSELECTIONMESSAGE.H"
#include "TYPES.H"
#include "ACHIEVE/ACHIEVE_ADVANCERESULTMODELPREVIEW.H"
#include "ACHIEVE/CPLAYERPREVIEW_RESETSELECTIONMESSAGESTATE.H"
#include "SCENE/CACHE_FREEMEMORY.H"
#include "FRONTEND/MENUIMAGE.H"

/* Resets three words of the object g_resultsModelPreviewScreen points to: the words at 0x9C and 0xB0 to -1 and
   the word at 0x188 to zero. */




/* Releases the object g_resultsModelPreviewScreen holds through Cache_FreeMemory, clears g_resultsModelPreviewScreen and returns zero. */



/* Handles event 1 on the screen g_resultsModelPreviewScreen: unless Frontend_GetMenuImageState reports its menu in state 1 it
   calls Achieve_AdvanceResultModelPreview; otherwise it advances the menu with Frontend_DrawMenuImage and Frontend_AdvanceMenuImageTransition and,
   once Frontend_GetMenuImageState reports 2, acts on the choice at 0x1C: choice 0 calls MarkMenuEventHandled, clears
   g_resultReplayPending and g_resultExitPending and leaves through SmXlate_SwitchScreen for screen 0xA unless g_campaignCompletionMenuEnabled is 1
   and g_selectedLevelId is at least 35, in which case it leaves for screen 7 when option g_gameControllerMode is 1
   and screen 3 otherwise; choice 1 calls Frontend_RequestScreenMode_AchieveUpdateresultsscreen(0), shows the window argument, stops the
   objects at g_frontendScreenStatus and 0x48 before it, releases g_world_AchieveUpdateresultsscreen through Scene_LoadLevelResources and sets the
   word at 0x17F0 of g_frontendScreenStatus to 8. Returns zero. Adapted from Frontend_UpdateMatchResultsTransition with the option cases written in the order that reproduces the
   cartridge's decision tree. */










extern struct SelectionMessageScreen *g_resultsModelPreviewScreen;

extern void Frontend_DrawMenuImage(struct MenuImage *menu);




extern void Widget_SetWidgetFlag08(void *object, int enabled);






/* Runs the screen g_resultsModelPreviewScreen each frame until stage 1 of g_selectionMessageStage: on its first frame it marks
   the word at 0x90, passes 0x272 to Menu_SetFocusedElement, or 0x273 when Widget_ListHasFlag100_AchieveUpdateresultsscreen
   reports zero for item 0x273 of the window argument, also 0x272 when g_campaignCompletionMenuEnabled is clear, and calls Tsmos_ActivateControllerState; then, once the
   reply pair ending at g_selectionMessageReply.ready is marked, it clears the mark and either hides the item at 0x24,
   clears the word at 0x1C0, calls MarkMenuEventHandled and leaves through SmXlate_SwitchScreen with the reply,
   or for a reply of -1 shows the item again and sets 0x1C0 to one. Returns zero. Written from the
   assembly; the conditional tests the zero case first. */


extern struct MenuWidget *Node_FindWidgetByResourceId(void *root, s32 identifier);

extern s32 Widget_ListHasFlag100(struct WidgetNode *node);



void CPlayerPreview_ResetSelectionMessageState(void) {
    struct SelectionMessageScreen *state = g_resultsModelPreviewScreen;

    state->first = -1;
    state->second = -1;
    state->third = 0;
}

s32 CPlayerPreview_CloseSelectionMessageScreen(void) {
    Cache_FreeMemory(g_resultsModelPreviewScreen);
    g_resultsModelPreviewScreen = 0;
    return 0;
}

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 Achieve_ResultScreenReturnZero(void) {
    return 0;
}

s32 Achieve_UpdateResultsScreen(void *window, void *unused1, s32 event) {
    s32 state;
    char *object;
    s32 next;

    if (event != 1) {
        return 0;
    }
    state = Frontend_GetMenuImageState((Shared_OptionsScreen *)&g_resultsModelPreviewScreen->rules);
    if (state == event) {
        Frontend_DrawMenuImage(&g_resultsModelPreviewScreen->rules);
        Frontend_AdvanceMenuImageTransition(&g_resultsModelPreviewScreen->rules);
        if (Frontend_GetMenuImageState((Shared_OptionsScreen *)&g_resultsModelPreviewScreen->rules) != 2) {
            return 0;
        }
        if (g_resultsModelPreviewScreen->rules.locked != 0) {
            if (g_resultsModelPreviewScreen->rules.locked != state) {
                return 0;
            }
            Frontend_RequestScreenMode(0);
            Widget_SetWidgetFlag08(window, 1);
            object = &g_frontendScreenStatus;
            Pools_ResetActorPools(object, 0);
            Player_InitializePlayerPool(object - ((char *)&((Shared_MenuData *)0)->object - (char *)0), 0, 0);
            Scene_LoadLevelResources(&g_world, 0, 0);
            ((MatchMenuObjects *)(object))->transition = 8;
        } else {
            MarkMenuEventHandled();
            g_resultReplayPending = 0;
            g_resultExitPending = 0;
            if (g_campaignCompletionMenuEnabled == state && g_selectedLevelId >= 35) {
                switch (g_gameSettings.controllerMode) {
                case 4:
                    next = 3;
                    break;
                default:
                    next = 3;
                    break;
                case 1:
                    next = 7;
                    break;
                case 3:
                    next = 3;
                    break;
                }
            } else {
                next = 10;
            }
            SmXlate_SwitchScreen(next);
            return 0;
        }
    } else {
        Achieve_AdvanceResultModelPreview();
    }
    return 0;
}

s32 Achieve_UpdateResultSelectionMessage(void *window) {
    s32 *pair;
    s32 marked;
    if (g_selectionMessageStage > 0) {
        return 0;
    }
    if (g_resultsModelPreviewScreen->started == 0) {
        g_resultsModelPreviewScreen->started = 1;
#if defined(VERSION_DE)
        Menu_SetFocusedElement(Widget_ListHasFlag100(Node_FindWidgetByResourceId(window, 623)) == 0 ? 623 : 622);
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
        Menu_SetFocusedElement(Widget_ListHasFlag100(Node_FindWidgetByResourceId(window, 627)) == 0 ? 627 : 626);
#elif defined(VERSION_EU_X)
        Menu_SetFocusedElement(Widget_ListHasFlag100(Node_FindWidgetByResourceId(window, 632)) == 0 ? 632 : 631);
#endif
        if (g_gameSettings.counters.humanWon == 0) {
#if defined(VERSION_DE)
            Menu_SetFocusedElement(622);
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
            Menu_SetFocusedElement(626);
#elif defined(VERSION_EU_X)
            Menu_SetFocusedElement(631);
#endif
        }
        Tsmos_ActivateControllerState();
    }
    pair = &g_selectionMessageReply.ready;
    marked = pair[0];
    if (marked == 1) {
        pair[0] = 0;
        if (pair[-1] != -1) {
            Widget_SetWidgetFlag08(g_resultsModelPreviewScreen->item, 0);
            g_resultsModelPreviewScreen->busy = 0;
            MarkMenuEventHandled();
            SmXlate_SwitchScreen(pair[-1]);
            return 0;
        }
        Widget_SetWidgetFlag08(g_resultsModelPreviewScreen->item, 1);
        g_resultsModelPreviewScreen->busy = marked;
    }
    return 0;
}

#if defined(VERSION_DE)
enum { MSG_BACK = 623, MSG_HIDE = 622, MSG_LEAVE = 627 };
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
enum { MSG_BACK = 627, MSG_HIDE = 626, MSG_LEAVE = 631 };
#else
enum { MSG_BACK = 632, MSG_HIDE = 631, MSG_LEAVE = 636 };
#endif
extern void PAKInterface_SetScreenPhase(s32);
extern void Frontend_StartMenuImageTransition(s32 *record);

s32 Achieve_HandleResultsMenuChoice(void) {
    MarkMenuEventHandled();
    if (Frontend_GetMenuImageState((Shared_OptionsScreen *)&g_resultsModelPreviewScreen->rules) != 1) {
        g_frontendScreenStatus.status[7] = 0;
        switch (Menu_GetFocusedElementId()) {
        case MSG_HIDE:
            Frontend_StartMenuImageTransition(g_resultsModelPreviewScreen);
            g_resultsModelPreviewScreen->rules.locked = 0;
            break;
        case MSG_BACK:
            PAKInterface_SetScreenPhase(5);
            SmXlate_SwitchScreen(19);
            return 0;
        case MSG_LEAVE:
            Random_SetMenuChoiceResult(33);
            break;
        default:
            return 0;
        }
        return 0;
    }
    return 0;
}

