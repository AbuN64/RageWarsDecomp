#include "FRONTEND/JOIN_RANDOMIZEJOINREQUESTENTRIES.H"
#include "COMMON/MENULISTSCREEN.H"
#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/REQUESTRECAT10.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "TYPES.H"
#include "COMMON/SELECTIONSCREENSTATE.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"
#include "SCENE/CACHE_FREEMEMORY.H"
/* Resets the three 28-byte entries of g_joinRequestEntries: -1 in the first word and zero in the next
   three. */
/* Counts the four player records whose byte 0x78 is one and returns 3, 2 or 1 for one, two or three such players, otherwise zero. */
extern SlotSelectionPlayerConfig g_playerSettings[];
/* Counts how many of the three 28-byte entries of g_joinRequestEntries hold a non-negative first word. */
/* Returns entry column - 1 of row r in the five-word table g_rewardScoreBudgets, or zero when the column is
   not positive. */
/* Returns the score of the three entries: 5, 10 or 20 points by kind for each active one, repeating the previous award for other kinds. */
/* Returns the column of the first of the seventeen eight-byte entries in row r of g_rewardItemTiers whose
   identifier matches, or zero when none does. */
/* Releases the object g_courseOptionsScreen holds through Cache_FreeMemory, clears g_courseOptionsScreen and returns zero. */
/* Advances the join screen's pulse timer by delta and sets byte 0x10 of node 0x392 under the edited request's root to 150 plus 100 times the sine of the timer over 300; returns zero. */
/* Calls MarkMenuEventHandled, then passes -1 to Random_SetMenuChoiceResult when Menu_GetPreviousScreenOwner reports 0x16 for zero
   and 0x15 otherwise, then calls Menu_ReturnToPreviousScreen. Returns zero. */
extern void MarkMenuEventHandled();
extern void Menu_ReturnToPreviousScreen(void);
/* Steps the selected menu item backwards and updates its display state. */
extern void MarkMenuEventHandled();
extern void Widget_SetWidgetFlag08(void *object, int enabled);
#if defined(VERSION_DE)
enum { MENU_RESOURCE = 908 };
#elif defined(VERSION_EU)
enum { MENU_RESOURCE = 914 };
#elif defined(VERSION_EU_X)
enum { MENU_RESOURCE = 918 };
#elif defined(VERSION_US)
enum { MENU_RESOURCE = 914 };
#elif defined(VERSION_US_REV1)
enum { MENU_RESOURCE = 914 };
#endif
/* Advances the selected menu item and updates its display state. */
/* Cycles a menu selection and updates the associated character setting. */
extern struct PlayerJoinRequestEntry g_joinRequestRanks[];
extern unsigned char g_joinRequestRankBytes[];
extern void MarkMenuEventHandled();
extern struct CourseOptionsScreen *g_courseOptionsScreen;
extern MenuWidget *Node_FindWidgetByResourceId(void *, s32);
void Join_ResetJoinRequestEntries(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        g_joinRequestEntries[i].id = -1;
        g_joinRequestEntries[i].variant = 0;
        g_joinRequestEntries[i].word8 = 0;
        g_joinRequestEntries[i].variantC = 0;
    }
}
s32 Join_CountOpenPlayerSlots(void) {
    s32 count;
    s32 i;
    s32 result;
    PlayerFrontendCountOpenPlayerSlots *player;

    count = 0;
    player = (PlayerFrontendCountOpenPlayerSlots *)g_playerSettings;
    for (i = 0; i < 4; i++) {
        if (player[i].active == 1) {
            count++;
        }
    }
    result = 0;
    switch (count) {
    case 1:
        result = 3;
        break;
    case 2:
        result = 2;
        break;
    case 3:
        result = 1;
        break;
    }
    return result;
}
s32 Join_CountUsedSlots(void) {
    s32 count = 0;
    s32 i;

    for (i = 0; i < 3; i++) {
        if (g_joinRequestEntries[i].id >= 0) {
            count++;
        }
    }
    return count;
}
s32 Join_GetJoinRankThreshold(s32 column, s32 row) {
    s32 previous = column - 1;

    if (column <= 0) {
        return 0;
    }
    return g_rewardScoreBudgets[row * 5 + previous];
}
s32 Join_ScoreJoinRequestEntries(void) {
    s32 score;
    s32 points;
    s32 i;

    score = 0;
    points = 0;
    for (i = 0; i < 3; i++) {
        if (g_joinRequestEntries[i].id >= 0) {
            switch (g_joinRequestEntries[i].variant) {
            case 0:
                points = 5;
                break;
            case 1:
                points = 10;
                break;
            case 2:
                points = 20;
                break;
            }
            score += points;
        }
    }
    return score;
}
s32 Join_FindJoinModelIndex(s32 row, s32 id) {
    s32 i;

    for (i = 0; i < 17; i++) {
        if (g_rewardItemTiers[row][i].id == id) {
            return i;
        }
    }
    return 0;
}
s32 Join_DestroyJoinOptionsMenu(void) {
    Cache_FreeMemory(g_courseOptionsScreen);
    g_courseOptionsScreen = 0;
    return 0;
}
s32 Join_PulseJoinSelectionHighlight(void *unused0, void *unused1, s32 delta) {
    MenuWidget *node;
    g_courseOptionsScreen->timer += delta;
#if defined(VERSION_DE)
    node = Node_FindWidgetByResourceId(g_courseOptionsScreen->rows[g_courseOptionsScreen->selection], 908);
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    node = Node_FindWidgetByResourceId(g_courseOptionsScreen->rows[g_courseOptionsScreen->selection], 914);
#elif defined(VERSION_EU_X)
    node = Node_FindWidgetByResourceId(g_courseOptionsScreen->rows[g_courseOptionsScreen->selection], 918);
#endif
    node->alpha = (u32)(Math_Cosf(g_courseOptionsScreen->timer * 0.0033333334f) * 100.0f + 150.0f);
    return 0;
}
s32 Join_RequestJoinOptionsExit(void) {
    MarkMenuEventHandled();
    Random_SetMenuChoiceResult(Menu_GetPreviousScreenOwner(0) == 22 ? -1 : 21);
    Menu_ReturnToPreviousScreen();
    return 0;
}
s32 Join_RequestJoinOptionsExitAlternate(void) {
    MarkMenuEventHandled();
    Random_SetMenuChoiceResult(Menu_GetPreviousScreenOwner(0) == 22 ? -1 : 21);
    Menu_ReturnToPreviousScreen();
    return 0;
}
s32 Join_SelectPreviousJoinRow(s32 unused0, s32 unused1, s32 unused2, s32 eventValue) {
    s32 prevSelection;
    s32 idx;
    MenuWidget *oldItem;
    MenuWidget *newItem;
    if (eventValue == 1) {
        MarkMenuEventHandled();
        idx = g_courseOptionsScreen->selection;
#if defined(VERSION_DE)
        oldItem = Node_FindWidgetByResourceId(g_courseOptionsScreen->rows[idx], 908);
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
        oldItem = Node_FindWidgetByResourceId(g_courseOptionsScreen->rows[idx], 914);
#elif defined(VERSION_EU_X)
        oldItem = Node_FindWidgetByResourceId(g_courseOptionsScreen->rows[idx], 918);
#endif
        oldItem->alpha = 0xFF;
        Widget_SetWidgetFlag08(oldItem, 0);
        prevSelection = g_courseOptionsScreen->selection - 1;
        g_courseOptionsScreen->selection = prevSelection;
        if (prevSelection < 0) {
            g_courseOptionsScreen->selection = g_courseOptionsScreen->step - 1;
        }
        idx = g_courseOptionsScreen->selection;
#if defined(VERSION_DE)
        newItem = Node_FindWidgetByResourceId(g_courseOptionsScreen->rows[idx], 908);
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
        newItem = Node_FindWidgetByResourceId(g_courseOptionsScreen->rows[idx], 914);
#elif defined(VERSION_EU_X)
        newItem = Node_FindWidgetByResourceId(g_courseOptionsScreen->rows[idx], 918);
#endif
        newItem->alpha = 0xFF;
        Widget_SetWidgetFlag08(newItem, 1);
        g_courseOptionsScreen->timer = 0;
        SoundElement_PlayFlatSound(3712);
        return 0;
    }
    return 0;
}
s32 Join_SelectNextJoinRow(s32 unusedObject, s32 unusedEvent, s32 unusedEventData, s32 eventValue) {
    s32 nextSelection;
    s32 followingRow;
    s32 rowCount;
    MenuWidget *oldItem;
    MenuWidget *newItem;

    if (eventValue == 1) {
        MarkMenuEventHandled();
        oldItem = Node_FindWidgetByResourceId(g_courseOptionsScreen->rows[g_courseOptionsScreen->selection], MENU_RESOURCE);
        oldItem->alpha = 0xFF;
        Widget_SetWidgetFlag08(oldItem, 0);
        rowCount = g_courseOptionsScreen->step;
        followingRow = g_courseOptionsScreen->selection + 1;
        nextSelection = followingRow % rowCount;
        g_courseOptionsScreen->selection = nextSelection;
        newItem = Node_FindWidgetByResourceId(g_courseOptionsScreen->rows[nextSelection], MENU_RESOURCE);
        newItem->alpha = 0xFF;
        Widget_SetWidgetFlag08(newItem, 1);
        g_courseOptionsScreen->timer = 0;
        SoundElement_PlayFlatSound(3712);
        return 0;
    }
    return 0;
}
s32 Join_CycleJoinRequestRank(s32 unused0, s32 unused1, u32 eventData, s32 eventValue) {
    s32 rowByteOffset;
    s32 selectedRow;
    u32 eventKind;

    eventKind = eventData >> 16;
    if ((eventKind == 3) && (eventValue == 0)) {
        MarkMenuEventHandled();
        rowByteOffset = g_courseOptionsScreen->selection * 28;
        ((struct PlayerJoinRequestEntry *)((char *)g_joinRequestRanks + rowByteOffset))->id = (((struct PlayerJoinRequestEntry *)((char *)g_joinRequestRanks + rowByteOffset))->id + 1) % 5;
        Join_UpdateJoinRequestDisplay(g_courseOptionsScreen->selection);
        if (Menu_GetPreviousScreenOwner(0) == 22) {
            selectedRow = g_courseOptionsScreen->selection;
            g_gameSettings.playerSettings[7 - selectedRow].rank = *(g_joinRequestRankBytes + (selectedRow * sizeof(struct PlayerJoinRequestEntry)));
        }
    }
    return 0;
}
#if defined(VERSION_EU_X) || defined(VERSION_US_REV1)
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
extern ResidentEventHandlerEntry g_joinOptionsEventHandlers[];
s32 Join_DispatchJoinOptionsEvent(MenuWidget *object, s32 event, s32 eventData, s32 eventValue, s32 eventContext) {
    s32 i = 0;
    while (g_joinOptionsEventHandlers[i].handler != 0) {
        if (g_joinOptionsEventHandlers[i].event == event &&
            (g_joinOptionsEventHandlers[i].actorKind == object->resource || g_joinOptionsEventHandlers[i].actorKind == 30000)) {
            return g_joinOptionsEventHandlers[i].handler(object, event, eventData, eventValue, eventContext);
        }
        i++;
    }
    return 0;
}
#endif
