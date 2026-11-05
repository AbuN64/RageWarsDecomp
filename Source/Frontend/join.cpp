#include "Frontend/join_randomizejoinrequestentries.h"
#include "Frontend/join_player_names.h"
#include "Common/menulistscreen.h"
#include "include_asm.h"
#include "Common/shared_gameslot.h"
#include "Common/player_join_requests.h"
#include "Common/sharedplayer.h"
#include "types.h"
#include "Common/selectionscreenstate.h"
#include "Render/soundelement_playflatsound.h"
#include "Scene/cache_freememory.h"
#include "Common/screen.h"
#include "Common/menu_screen_elements.h"
#include "Data/rest_source_records.h"
#include "Common/effectrender.h"
#include "Frontend/frontend_address_symbols.h"
#include "data_overlay_layouts.h"
#include "Common/Lone/g_languageindex.h"
#include "Ui/X_files/x_plus.h"
#include "Common/resultsoptionsscreen.h"
#include "Common/runtime_declarations.h"
#include "X_files/x_plus.h"
#include "Rsp/random_direction_and_affine_math.h"

/* unit JOIN_CYCLEJOINREQUESTRANK.CPP */
#if defined(VERSION_DE)
enum { MENU_RESOURCE = 908 };
#elif defined(VERSION_EU_X)
enum { MENU_RESOURCE = 918 };
#else
enum { MENU_RESOURCE = 914 };
#endif

/* Resets the three join request entries of g_joinRequestEntries: -1 in the id and zero in the other fields. */
void Join_ResetJoinRequestEntries(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        g_joinRequestEntries[i].id = -1;
        g_joinRequestEntries[i].variant = 0;
        g_joinRequestEntries[i].word8 = 0;
        g_joinRequestEntries[i].variantC = 0;
    }
}
/* Counts the four player records that are active and returns 3, 2 or 1 for one, two or three such players, otherwise zero. */
s32 Join_CountOpenPlayerSlots(void) {
    s32 count;
    s32 i;
    s32 result;
    struct Shared_PlayerSettingsRecord *player;

    count = 0;
    player = g_playerSettings;
    for (i = 0; i < 4; i++, player++) {
        if (player->enabled == 1) {
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
/* Counts how many of the three join request entries of g_joinRequestEntries hold a non-negative id. */
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
/* Returns entry column - 1 of row r in the five-word table g_rewardScoreBudgets, or zero when the column is
   not positive. */
s32 Join_GetJoinRankThreshold(s32 column, s32 row) {
    s32 previous = column - 1;

    if (column <= 0) {
        return 0;
    }
    return g_rewardScoreBudgets[row * 5 + previous];
}
/* Returns the score of the three entries: 5, 10 or 20 points by kind for each active one, repeating the previous award for other kinds. */
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
/* Returns the column of the first of the seventeen entries in row r of g_rewardItemTiers whose
   identifier matches, or zero when none does. */
s32 Join_FindJoinModelIndex(s32 row, s32 id) {
    s32 i;

    for (i = 0; i < 17; i++) {
        if (g_rewardItemTiers[row][i].id == id) {
            return i;
        }
    }
    return 0;
}
/* Releases the object g_courseOptionsScreen holds through Cache_FreeMemory, clears g_courseOptionsScreen and returns zero. */
s32 Join_DestroyJoinOptionsMenu(void) {
    Cache_FreeMemory(g_courseOptionsScreen);
    g_courseOptionsScreen = 0;
    return 0;
}
/* Advances the join screen's pulse timer by delta and sets the alpha of the selected row's highlight widget to 150 plus 100 times the cosine of the timer over 300; returns zero. */
s32 Join_PulseJoinSelectionHighlight(void *element, void *eventId, s32 delta) {
    MenuWidget *node;
    g_courseOptionsScreen->timer += delta;
    node = Node_FindWidgetByResourceId(g_courseOptionsScreen->rows[g_courseOptionsScreen->selection], MENU_RESOURCE);
    node->alpha = (u32)(Math_Cosf(g_courseOptionsScreen->timer * 0.0033333334f) * 100.0f + 150.0f);
    return 0;
}
/* Calls MarkMenuEventHandled, then passes -1 to Random_SetMenuChoiceResult when Menu_GetPreviousScreenOwner reports 22 for zero
   and 21 otherwise, then calls Menu_ReturnToPreviousScreen. Returns zero. */
s32 Join_RequestJoinOptionsExit(void) {
    MarkMenuEventHandled();
    Random_SetMenuChoiceResult(Menu_GetPreviousScreenOwner(0) == 22 ? -1 : 21);
    Menu_ReturnToPreviousScreen();
    return 0;
}
/* Same exit as Join_RequestJoinOptionsExit, reached through the alternate event binding. */
s32 Join_RequestJoinOptionsExitAlternate(void) {
    MarkMenuEventHandled();
    Random_SetMenuChoiceResult(Menu_GetPreviousScreenOwner(0) == 22 ? -1 : 21);
    Menu_ReturnToPreviousScreen();
    return 0;
}
/* Steps the selected menu item backwards and updates its display state. */
s32 Join_SelectPreviousJoinRow(s32 element, s32 eventId, s32 eventPayload, s32 eventValue) {
    s32 prevSelection;
    s32 idx;
    MenuWidget *oldItem;
    MenuWidget *newItem;
    if (eventValue == 1) {
        MarkMenuEventHandled();
        idx = g_courseOptionsScreen->selection;
        oldItem = Node_FindWidgetByResourceId(g_courseOptionsScreen->rows[idx], MENU_RESOURCE);
        oldItem->alpha = 0xFF;
        Widget_SetWidgetFlag08(oldItem, 0);
        prevSelection = g_courseOptionsScreen->selection - 1;
        g_courseOptionsScreen->selection = prevSelection;
        if (prevSelection < 0) {
            g_courseOptionsScreen->selection = g_courseOptionsScreen->step - 1;
        }
        idx = g_courseOptionsScreen->selection;
        newItem = Node_FindWidgetByResourceId(g_courseOptionsScreen->rows[idx], MENU_RESOURCE);
        newItem->alpha = 0xFF;
        Widget_SetWidgetFlag08(newItem, 1);
        g_courseOptionsScreen->timer = 0;
        SoundElement_PlayFlatSound(3712);
        return 0;
    }
    return 0;
}
/* Advances the selected menu item and updates its display state. */
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
/* Cycles a menu selection and updates the associated character setting. */
s32 Join_CycleJoinRequestRank(s32 element, s32 eventId, u32 eventData, s32 eventValue) {
    struct PlayerJoinRequestEntry *selectedEntry;
    s32 selectedRow;
    u32 eventKind;

    eventKind = eventData >> 16;
    if ((eventKind == 3) && (eventValue == 0)) {
        MarkMenuEventHandled();
        selectedEntry = &g_joinRequestRanks[g_courseOptionsScreen->selection];
        selectedEntry->id = (selectedEntry->id + 1) % 5;
        Join_UpdateJoinRequestDisplay(g_courseOptionsScreen->selection);
        if (Menu_GetPreviousScreenOwner(0) == 22) {
            selectedRow = g_courseOptionsScreen->selection;
            g_gameSettings.playerSettings[7 - selectedRow].rank = g_joinRequestRankBytes[selectedRow * sizeof(struct PlayerJoinRequestEntry)];
        }
    }
    return 0;
}
#if defined(VERSION_EU_X) || defined(VERSION_US_REV1)
#include "Common/resident_event_handler.h"
#include "Join/join_cyclejoinrequestrank.h"
#include "Frontend/frontend_address_symbols.h"
#include "Common/gameplay_settings.h"
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

/* unit CHARACTER_PREVIEW_VERTICAL_OFFSET.CPP */
#if !(defined(VERSION_US_REV1))
#if defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US)
extern const unsigned char g_characterPreviewVerticalOffset[3];
#endif
#endif
#if defined(VERSION_US_REV1)
extern const float g_characterPreviewVerticalOffset;
#endif

/* unit CHARACTER_PREVIEW_DEFINITIONS.CPP */
#if !(defined(VERSION_DE))
#if defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US)
float g_characterPreviewPositionTail[11] = {
    -60.0f, -100.0f, -40.0f, -60.0f,
    -100.0f, 29.0f, -95.0f, -70.0f,
    -29.0f, -95.0f, -70.0f,
};
#endif
#endif
#if defined(VERSION_EU_X)
CharacterPreviewDefinitionsEuXLayout g_characterPreviewDefinitionsEuX = {
    { 0, 0, -20, -20 },
    {
        { (void *)&g_characterNamesLocalized[3], 138, 1, 22,
            { 0.11f, 0.11f, 0.11f, 0.11f, 1.6e+02f, 2e+02f, 1.6e+02f, 2.1e+02f },
            { 41.0f, -37.0f, -1e+02f, -38.0f, -37.0f, -1e+02f, 34.0f, -74.0f, -8e+01f, -3e+01f, -74.0f, -8e+01f },
            { 0, 0, -15, -15 } },
        { (void *)&g_characterNamesLocalized[6], 149, 2, 29,
            { 0.14f, 0.14f, 0.14f, 0.14f, 1.6e+02f, 195.0f, 1.6e+02f, 195.0f },
            { 4e+01f, -53.0f, -1e+02f, -4e+01f, -53.0f, -1e+02f, 32.0f, -91.0f, -8e+01f, -35.0f, -91.0f, -8e+01f },
            { 0, 0, -15, -15 } },
        { (void *)&g_joinCharacterPreviewLabelText[0x4], 136, 3, 26,
            { 0.065f, 0.065f, 0.065f, 0.065f, 1.6e+02f, 2e+02f, 1.6e+02f, 2e+02f },
            { 39.0f, -35.0f, -1e+02f, -39.0f, -35.0f, -1e+02f, 32.0f, -72.0f, -8e+01f, -32.0f, -72.0f, -8e+01f },
            { 20, 20, 0, 0 } },
        { (void *)&g_joinCharacterPreviewLabelText[0x10], 139, 4, 20,
            { 0.055f, 0.055f, 0.055f, 0.055f, 155.0f, 2e+02f, 1.6e+02f, 2e+02f },
            { 4e+01f, -35.0f, -1e+02f, -4e+01f, -35.0f, -1e+02f, 3e+01f, -72.0f, -8e+01f, -33.0f, -72.0f, -8e+01f },
            { 0, 0, -15, -15 } },
        { (void *)&g_joinCharacterPreviewLabelText[0x1C], 144, 5, 32,
            { 0.17f, 0.17f, 0.17f, 0.17f, 1.8e+02f, 2.2e+02f, 1.8e+02f, 2.2e+02f },
            { 41.0f, -79.0f, -1e+02f, -39.0f, -79.0f, -1e+02f, 4e+01f, -115.0f, -7e+01f, -17.0f, -115.0f, -7e+01f },
            { 0, 0, -15, -15 } },
        { (void *)&g_joinCharacterPreviewLabelText[0x28], 146, 6, 23,
            { 0.08f, 0.08f, 0.08f, 0.08f, 1.6e+02f, 2e+02f, 1.6e+02f, 2e+02f },
            { 42.0f, -45.0f, -1e+02f, -38.0f, -45.0f, -1e+02f, 38.0f, -81.0f, -88.0f, -33.0f, -81.0f, -88.0f },
            { 0, 0, -15, -15 } },
        { (void *)&g_joinCharacterPreviewLabelText[0x34], 145, 7, 27,
            { 0.065f, 0.065f, 0.065f, 0.065f, 1.6e+02f, 2e+02f, 1.6e+02f, 2e+02f },
            { 4e+01f, -36.0f, -1e+02f, -4e+01f, -36.0f, -1e+02f, 33.0f, -71.0f, -8e+01f, -33.0f, -71.0f, -8e+01f },
            { 0, 0, -15, -15 } },
        { (void *)&g_joinCharacterPreviewLabelText[0x40], 141, 8, 25,
            { 0.13f, 0.13f, 0.13f, 0.13f, 1.6e+02f, 2e+02f, 1.6e+02f, 2e+02f },
            { 39.0f, -58.0f, -1e+02f, -41.0f, -58.0f, -1e+02f, 32.0f, -95.0f, -8e+01f, -34.0f, -95.0f, -8e+01f },
            { 0, 0, -15, -15 } },
        { (void *)&g_joinCharacterPreviewLabelText[0x4C], 134, 9, 24,
            { 0.06f, 0.06f, 0.06f, 0.06f, 1.6e+02f, 205.0f, 1.6e+02f, 205.0f },
            { 39.0f, -2e+01f, -1e+02f, -41.0f, -2e+01f, -1e+02f, 31.0f, -55.0f, -8e+01f, -33.0f, -55.0f, -8e+01f },
            { 0, 0, -15, -15 } },
        { (void *)&g_joinCharacterPreviewLabelText[0x58], 148, 10, 28,
            { 0.13f, 0.13f, 0.13f, 0.13f, 2e+02f, 245.0f, 2e+02f, 245.0f },
            { 4e+01f, -6e+01f, -1e+02f, -4e+01f, -6e+01f, -1e+02f, 43.0f, -95.0f, -8e+01f, -21.0f, -95.0f, -8e+01f },
            { 0, 0, -10, -10 } },
        { (void *)&g_joinCharacterPreviewLabelText[0x64], 140, 11, 33,
            { 0.21f, 0.21f, 0.21f, 0.21f, 1.6e+02f, 2e+02f, 1.6e+02f, 2e+02f },
            { 42.0f, -62.0f, -1e+02f, -41.0f, -62.0f, -1e+02f, 36.0f, -103.0f, -8e+01f, -36.0f, -103.0f, -8e+01f },
            { 0, 0, -15, -15 } },
        { (void *)&g_bastilleNameLocalized, 142, 12, 34,
            { 0.19f, 0.19f, 0.19f, 0.19f, 2.2e+02f, 2.6e+02f, 2.2e+02f, 2.6e+02f },
            { 45.0f, -58.0f, -1e+02f, -34.0f, -6e+01f, -1e+02f, 53.0f, -97.0f, -8e+01f, -13.0f, -97.0f, -8e+01f },
            { 0, 0, -10, -10 } },
        { (void *)&g_syraNameLocalized, 147, 13, 31,
            { 0.14f, 0.14f, 0.14f, 0.14f, 2.2e+02f, 2.7e+02f, 2.2e+02f, 275.0f },
            { 48.0f, -55.0f, -1e+02f, -33.0f, -58.0f, -1e+02f, 54.0f, -92.0f, -8e+01f, -11.0f, -91.0f, -8e+01f },
            { 0, 0, -10, -10 } },
        { (void *)&g_symbiontNameLocalized, 132, 14, 21,
            { 0.14f, 0.14f, 0.14f, 0.14f, 1.6e+02f, 2e+02f, 1.6e+02f, 2e+02f },
            { 4e+01f, -58.0f, -1e+02f, -41.0f, -58.0f, -1e+02f, 32.0f, -96.0f, -8e+01f, -33.0f, -96.0f, -8e+01f },
            { 0, 0, -15, -15 } },
        { (void *)&g_talSetRaptorMantidMitesNamesLocalized, 143, 17, 30,
            { 0.085f, 0.085f, 0.085f, 0.085f, 143.0f, 215.0f, 143.0f, 215.0f },
            { 45.0f, -36.0f, -1e+02f, -56.0f, -34.0f, -1e+02f, 37.0f, -71.0f, -9e+01f, -48.0f, -71.0f, -9e+01f },
            { 0, 0, -15, -15 } },
        { (void *)&g_joinCharacterPreviewLabelText[0xA0], 137, 18, 36,
            { 0.09f, 0.09f, 0.09f, 0.09f, 1.7e+02f, 2.1e+02f, 1.7e+02f, 2.1e+02f },
            { 4e+01f, 2.0f, -1e+02f, -4e+01f, 2.0f, -1e+02f, 32.0f, -33.0f, -8e+01f, -31.0f, -33.0f, -8e+01f },
            { 0, 0, -15, -15 } },
    },
    (void *)&g_joinCharacterPreviewLabelText[0xAC],
    { 18, 15, 52, 94, 232, 15, 267, 94, 18, 128, 52, 206, 232, 128, 267, 206, 107, 108, 109, 110, 102, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 111, 146, 147, 148, 106, 104, 105, 103, 150, 151, 149, 145, 3590, 20 },
};
#endif
#if defined(VERSION_EU)
CharacterPreviewDefinitionsEuLayout g_characterPreviewDefinitionsEu = {
    { 0, 0, -20, -20 },
    {
        { (void *)&g_characterNamesLocalized[4], 134, 1, 22,
            { 0.11f, 0.11f, 0.11f, 0.11f, 1.6e+02f, 2e+02f, 1.6e+02f, 2.1e+02f },
            { 41.0f, -37.0f, -1e+02f, -38.0f, -37.0f, -1e+02f, 34.0f, -74.0f, -8e+01f, -3e+01f, -74.0f, -8e+01f },
            { 0, 0, -15, -15 } },
        { (void *)&g_characterNamesLocalized[8], 145, 2, 29,
            { 0.14f, 0.14f, 0.14f, 0.14f, 1.6e+02f, 195.0f, 1.6e+02f, 195.0f },
            { 4e+01f, -53.0f, -1e+02f, -4e+01f, -53.0f, -1e+02f, 32.0f, -91.0f, -8e+01f, -35.0f, -91.0f, -8e+01f },
            { 0, 0, -15, -15 } },
        { (void *)&g_characterNamesLocalized[12], 132, 3, 26,
            { 0.065f, 0.065f, 0.065f, 0.065f, 1.6e+02f, 2e+02f, 1.6e+02f, 2e+02f },
            { 39.0f, -35.0f, -1e+02f, -39.0f, -35.0f, -1e+02f, 32.0f, -72.0f, -8e+01f, -32.0f, -72.0f, -8e+01f },
            { 20, 20, 0, 0 } },
        { (void *)&g_characterNamesLocalized[16], 135, 4, 20,
            { 0.055f, 0.055f, 0.055f, 0.055f, 155.0f, 2e+02f, 1.6e+02f, 2e+02f },
            { 4e+01f, -35.0f, -1e+02f, -4e+01f, -35.0f, -1e+02f, 3e+01f, -72.0f, -8e+01f, -33.0f, -72.0f, -8e+01f },
            { 0, 0, -15, -15 } },
        { (void *)&g_setupNameCursorLabelText[0x4], 140, 5, 32,
            { 0.17f, 0.17f, 0.17f, 0.17f, 1.8e+02f, 2.2e+02f, 1.8e+02f, 2.2e+02f },
            { 41.0f, -79.0f, -1e+02f, -39.0f, -79.0f, -1e+02f, 4e+01f, -115.0f, -7e+01f, -17.0f, -115.0f, -7e+01f },
            { 0, 0, -15, -15 } },
        { (void *)&g_setupNameCursorLabelText[0x14], 142, 6, 23,
            { 0.08f, 0.08f, 0.08f, 0.08f, 1.6e+02f, 2e+02f, 1.6e+02f, 2e+02f },
            { 42.0f, -45.0f, -1e+02f, -38.0f, -45.0f, -1e+02f, 38.0f, -81.0f, -88.0f, -33.0f, -81.0f, -88.0f },
            { 0, 0, -15, -15 } },
        { (void *)&g_setupNameCursorLabelText[0x24], 141, 7, 27,
            { 0.065f, 0.065f, 0.065f, 0.065f, 1.6e+02f, 2e+02f, 1.6e+02f, 2e+02f },
            { 4e+01f, -36.0f, -1e+02f, -4e+01f, -36.0f, -1e+02f, 33.0f, -71.0f, -8e+01f, -33.0f, -71.0f, -8e+01f },
            { 0, 0, -15, -15 } },
        { (void *)&g_setupNameCursorLabelText[0x34], 137, 8, 25,
            { 0.13f, 0.13f, 0.13f, 0.13f, 1.6e+02f, 2e+02f, 1.6e+02f, 2e+02f },
            { 39.0f, -58.0f, -1e+02f, -41.0f, -58.0f, -1e+02f, 32.0f, -95.0f, -8e+01f, -34.0f, -95.0f, -8e+01f },
            { 0, 0, -15, -15 } },
        { (void *)&g_setupNameCursorLabelText[0x44], 130, 9, 24,
            { 0.06f, 0.06f, 0.06f, 0.06f, 1.6e+02f, 205.0f, 1.6e+02f, 205.0f },
            { 39.0f, -2e+01f, -1e+02f, -41.0f, -2e+01f, -1e+02f, 31.0f, -55.0f, -8e+01f, -33.0f, -55.0f, -8e+01f },
            { 0, 0, -15, -15 } },
        { (void *)&g_setupNameCursorLabelText[0x54], 144, 10, 28,
            { 0.13f, 0.13f, 0.13f, 0.13f, 2e+02f, 245.0f, 2e+02f, 245.0f },
            { 4e+01f, -6e+01f, -1e+02f, -4e+01f, -6e+01f, -1e+02f, 43.0f, -95.0f, -8e+01f, -21.0f, -95.0f, -8e+01f },
            { 0, 0, -10, -10 } },
        { (void *)&g_setupNameCursorLabelText[0x64], 136, 11, 33,
            { 0.21f, 0.21f, 0.21f, 0.21f, 1.6e+02f, 2e+02f, 1.6e+02f, 2e+02f },
            { 42.0f, -62.0f, -1e+02f, -41.0f, -62.0f, -1e+02f, 36.0f, -103.0f, -8e+01f, -36.0f, -103.0f, -8e+01f },
            { 0, 0, -15, -15 } },
        { (void *)&g_bastilleNameLocalized, 138, 12, 34,
            { 0.19f, 0.19f, 0.19f, 0.19f, 2.2e+02f, 2.6e+02f, 2.2e+02f, 2.6e+02f },
            { 45.0f, -58.0f, -1e+02f, -34.0f, -6e+01f, -1e+02f, 53.0f, -97.0f, -8e+01f, -13.0f, -97.0f, -8e+01f },
            { 0, 0, -10, -10 } },
        { (void *)&g_syraNameLocalized, 143, 13, 31,
            { 0.14f, 0.14f, 0.14f, 0.14f, 2.2e+02f, 2.7e+02f, 2.2e+02f, 275.0f },
            { 48.0f, -55.0f, -1e+02f, -33.0f, -58.0f, -1e+02f, 54.0f, -92.0f, -8e+01f, -11.0f, -91.0f, -8e+01f },
            { 0, 0, -10, -10 } },
        { (void *)&g_symbiontNameLocalized, 128, 14, 21,
            { 0.14f, 0.14f, 0.14f, 0.14f, 1.6e+02f, 2e+02f, 1.6e+02f, 2e+02f },
            { 4e+01f, -58.0f, -1e+02f, -41.0f, -58.0f, -1e+02f, 32.0f, -96.0f, -8e+01f, -33.0f, -96.0f, -8e+01f },
            { 0, 0, -15, -15 } },
        { (void *)&g_talSetRaptorMantidMitesNamesLocalized, 139, 17, 30,
            { 0.085f, 0.085f, 0.085f, 0.085f, 143.0f, 215.0f, 143.0f, 215.0f },
            { 45.0f, -36.0f, -1e+02f, -56.0f, -34.0f, -1e+02f, 37.0f, -71.0f, -9e+01f, -48.0f, -71.0f, -9e+01f },
            { 0, 0, -15, -15 } },
        { (void *)&g_talSetRaptorMantidMitesNamesLocalized[4], 133, 18, 36,
            { 0.09f, 0.09f, 0.09f, 0.09f, 1.7e+02f, 2.1e+02f, 1.7e+02f, 2.1e+02f },
            { 4e+01f, 2.0f, -1e+02f, -4e+01f, 2.0f, -1e+02f, 32.0f, -33.0f, -8e+01f, -31.0f, -33.0f, -8e+01f },
            { 0, 0, -15, -15 } },
    },
    (void *)&g_talSetRaptorMantidMitesNamesLocalized[8],
    { 18, 15, 52, 94, 232, 15, 267, 94, 18, 128, 52, 206, 232, 128, 267, 206, 107, 108, 109, 110, 102, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 111, 146, 147, 148, 106, 104, 105, 103, 150, 151, 149, 145 },
    0x8FB90004,
    1707458,
};
#endif

/* unit G_SELECTIONSTATEANDFIRSTKIND.CPP */
#if defined(VERSION_EU)
struct {
    void * screen;
    s32 firstKind;
} g_selectionScreenAndInitialKind __attribute__((aligned(4))) = {
    0,
    146
};
typedef char g_selectionScreenAndInitialKindSizeCheck[(sizeof(g_selectionScreenAndInitialKind) == 8) ? 1 : -1];
#endif
#if defined(VERSION_EU_X)
struct {
    void * screen;
    s32 firstKind;
} g_selectionScreenAndInitialKind __attribute__((aligned(4))) = {
    0,
    150
};
typedef char g_selectionScreenAndInitialKindSizeCheck[(sizeof(g_selectionScreenAndInitialKind) == 8) ? 1 : -1];
#endif
#if defined(VERSION_US)
struct {
    void * screen;
    s32 firstKind;
} g_selectionScreenAndInitialKind __attribute__((aligned(4))) = {
    0,
    146
};
typedef char g_selectionScreenAndInitialKindSizeCheck[(sizeof(g_selectionScreenAndInitialKind) == 8) ? 1 : -1];
#endif

/* unit OVL1_I.CPP */
#if defined(VERSION_US) || defined(VERSION_US_REV1)
#if defined(VERSION_US)
CharacterUnlocksPreviewConstantWordsRecord g_characterUnlocksPreviewConstantWords = {
    { 0, 0, -20, -20 },
};
#endif
#endif
#if defined(VERSION_US)
CharacterPreviewRecordWordsUsLayout g_characterPreviewRecordWordsUs = {
    {
        { (void *)&g_characterNames[0x4], 134, 1, 22,
            { 0.11f, 0.11f, 0.11f, 0.11f, 1.6e+02f, 2e+02f, 1.6e+02f, 2.1e+02f },
            { 41.0f, -37.0f, -1e+02f, -38.0f, -37.0f, -1e+02f, 34.0f, -74.0f, -8e+01f, -3e+01f, -74.0f, -8e+01f },
            { 0.0f, 0.0f, -15, -15 } },
        { (void *)&g_characterNames[0x8], 145, 2, 29,
            { 0.14f, 0.14f, 0.14f, 0.14f, 1.6e+02f, 195.0f, 1.6e+02f, 195.0f },
            { 4e+01f, -53.0f, -1e+02f, -4e+01f, -53.0f, -1e+02f, 32.0f, -91.0f, -8e+01f, -35.0f, -91.0f, -8e+01f },
            { 0.0f, 0.0f, -15, -15 } },
        { (void *)&g_characterNames[0xC], 132, 3, 26,
            { 0.065f, 0.065f, 0.065f, 0.065f, 1.6e+02f, 2e+02f, 1.6e+02f, 2e+02f },
            { 39.0f, -35.0f, -1e+02f, -39.0f, -35.0f, -1e+02f, 32.0f, -72.0f, -8e+01f, -32.0f, -72.0f, -8e+01f },
            { 20, 20, 0, 0 } },
        { (void *)&g_characterNames[0x10], 135, 4, 20,
            { 0.055f, 0.055f, 0.055f, 0.055f, 155.0f, 2e+02f, 1.6e+02f, 2e+02f },
            { 4e+01f, -35.0f, -1e+02f, -4e+01f, -35.0f, -1e+02f, 3e+01f, -72.0f, -8e+01f, -33.0f, -72.0f, -8e+01f },
            { 0.0f, 0.0f, -15, -15 } },
        { (void *)&g_characterNames[0x14], 140, 5, 32,
            { 0.17f, 0.17f, 0.17f, 0.17f, 1.8e+02f, 2.2e+02f, 1.8e+02f, 2.2e+02f },
            { 41.0f, -79.0f, -1e+02f, -39.0f, -79.0f, -1e+02f, 4e+01f, -115.0f, -7e+01f, -17.0f, -115.0f, -7e+01f },
            { 0.0f, 0.0f, -15, -15 } },
        { (void *)&g_characterNames[0x18], 142, 6, 23,
            { 0.08f, 0.08f, 0.08f, 0.08f, 1.6e+02f, 2e+02f, 1.6e+02f, 2e+02f },
            { 42.0f, -45.0f, -1e+02f, -38.0f, -45.0f, -1e+02f, 38.0f, -81.0f, -88.0f, -33.0f, -81.0f, -88.0f },
            { 0.0f, 0.0f, -15, -15 } },
        { (void *)&g_characterNames[0x1C], 141, 7, 27,
            { 0.065f, 0.065f, 0.065f, 0.065f, 1.6e+02f, 2e+02f, 1.6e+02f, 2e+02f },
            { 4e+01f, -36.0f, -1e+02f, -4e+01f, -36.0f, -1e+02f, 33.0f, -71.0f, -8e+01f, -33.0f, -71.0f, -8e+01f },
            { 0.0f, 0.0f, -15, -15 } },
        { (void *)&g_characterNames[0x20], 137, 8, 25,
            { 0.13f, 0.13f, 0.13f, 0.13f, 1.6e+02f, 2e+02f, 1.6e+02f, 2e+02f },
            { 39.0f, -58.0f, -1e+02f, -41.0f, -58.0f, -1e+02f, 32.0f, -95.0f, -8e+01f, -34.0f, -95.0f, -8e+01f },
            { 0.0f, 0.0f, -15, -15 } },
        { (void *)&g_characterNames[0x24], 130, 9, 24,
            { 0.06f, 0.06f, 0.06f, 0.06f, 1.6e+02f, 205.0f, 1.6e+02f, 205.0f },
            { 39.0f, -2e+01f, -1e+02f, -41.0f, -2e+01f, -1e+02f, 31.0f, -55.0f, -8e+01f, -33.0f, -55.0f, -8e+01f },
            { 0.0f, 0.0f, -15, -15 } },
        { (void *)&g_characterNames[0x28], 144, 10, 28,
            { 0.13f, 0.13f, 0.13f, 0.13f, 2e+02f, 245.0f, 2e+02f, 245.0f },
            { 4e+01f, -6e+01f, -1e+02f, -4e+01f, -6e+01f, -1e+02f, 43.0f, -95.0f, -8e+01f, -21.0f, -95.0f, -8e+01f },
            { 0.0f, 0.0f, -10, -10 } },
        { (void *)&g_characterNames[0x2C], 136, 11, 33,
            { 0.21f, 0.21f, 0.21f, 0.21f, 1.6e+02f, 2e+02f, 1.6e+02f, 2e+02f },
            { 42.0f, -62.0f, -1e+02f, -41.0f, -62.0f, -1e+02f, 36.0f, -103.0f, -8e+01f, -36.0f, -103.0f, -8e+01f },
            { 0.0f, 0.0f, -15, -15 } },
        { (void *)&g_characterNames[0x30], 138, 12, 34,
            { 0.19f, 0.19f, 0.19f, 0.19f, 2.2e+02f, 2.6e+02f, 2.2e+02f, 2.6e+02f },
            { 45.0f, -58.0f, -1e+02f, -34.0f, -6e+01f, -1e+02f, 53.0f, -97.0f, -8e+01f, -13.0f, -97.0f, -8e+01f },
            { 0.0f, 0.0f, -10, -10 } },
        { (void *)&g_characterNames[0x34], 143, 13, 31,
            { 0.14f, 0.14f, 0.14f, 0.14f, 2.2e+02f, 2.7e+02f, 2.2e+02f, 275.0f },
            { 48.0f, -55.0f, -1e+02f, -33.0f, -58.0f, -1e+02f, 54.0f, -92.0f, -8e+01f, -11.0f, -91.0f, -8e+01f },
            { 0.0f, 0.0f, -10, -10 } },
        { (void *)&g_characterNames[0x38], 128, 14, 21,
            { 0.14f, 0.14f, 0.14f, 0.14f, 1.6e+02f, 2e+02f, 1.6e+02f, 2e+02f },
            { 4e+01f, -58.0f, -1e+02f, -41.0f, -58.0f, -1e+02f, 32.0f, -96.0f, -8e+01f, -33.0f, -96.0f, -8e+01f },
            { 0.0f, 0.0f, -15, -15 } },
        { (void *)&g_characterNames[0x3C], 139, 17, 30,
            { 0.085f, 0.085f, 0.085f, 0.085f, 143.0f, 215.0f, 143.0f, 215.0f },
            { 45.0f, -36.0f, -1e+02f, -56.0f, -34.0f, -1e+02f, 37.0f, -71.0f, -9e+01f, -48.0f, -71.0f, -9e+01f },
            { 0.0f, 0.0f, -15, -15 } },
        { (void *)&g_characterNames[0x4C], 133, 18, 36,
            { 0.09f, 0.09f, 0.09f, 0.09f, 1.7e+02f, 2.1e+02f, 1.7e+02f, 2.1e+02f },
            { 4e+01f, 2.0f, -1e+02f, -4e+01f, 2.0f, -1e+02f, 32.0f, -33.0f, -8e+01f, -31.0f, -33.0f, -8e+01f },
            { 0.0f, 0.0f, -15, -15 } },
    },
    (void *)&g_characterNames[0x5C],
    { 18, 15, 52, 94, 232, 15, 267, 94, 18, 128, 52, 206, 232, 128, 267, 206, 107, 108, 109, 110, 102, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 111, 146, 147, 148, 106, 104, 105, 103, 150, 151, 149, 145 },
    "ON_MPLAY"
};
#endif

/* unit G_MENUPLAYERSCISSORRECTS.CPP */
#if defined(VERSION_US_REV1)
void *g_GMenuplayerscissorrectsEncodedWords[1] = {
    (void *)&g_characterNames[0x5C],
};
#endif

/* unit FRONTEND_SELECTNEXTJOINMODEL.CPP */
#if defined(VERSION_US)
#include "Common/resident_event_handler.h"
#include "Common/multiplayeroptions.h"
#include "Frontend/frontend_address_symbols.h"

s32 Frontend_DispatchUsJoinOptionsEvent(ActorDefinitionHeader *actor, s32 event, s32 eventData, s32 eventValue, s32 eventContext) {
    s32 index;
    index = 0;
    if (g_joinOptionsEventHandlers[index].handler != 0) {
        do {
            if (g_joinOptionsEventHandlers[index].event == event) {
                if (g_joinOptionsEventHandlers[index].actorKind == actor->character || g_joinOptionsEventHandlers[index].actorKind == 30000) {
                    return g_joinOptionsEventHandlers[index].handler(actor, event, eventData, eventValue, eventContext);
                }
            }
            index++;
        } while (g_joinOptionsEventHandlers[index].handler != 0);
    }
    return 0;
}
#endif

#if !(defined(VERSION_US))

/* Steps the model of the join request the screen g_courseOptionsScreen edits (by its selection index) back on event 1
   unless Menu_GetPreviousScreenOwner reports 0x16: calls MarkMenuEventHandled, finds the request's place in the 3 by 17
   model table g_rewardItemTiers through Join_FindJoinModelIndex, walks back through its variants and, before the
   first, to the last variant of the previous model (wrapping to the last), skipping entries whose
   id is -1, then stores the variant and the id in the request in
   g_joinRequestEntries, copies the name of the entry the found id selects in that variant row into the request, redraws through Join_UpdateJoinRequestDisplay and plays sound
   0xE81. Returns zero. */
s32 Frontend_SelectPreviousJoinModel(void *element, void *eventId, void *eventPayload, s32 event) {
    s32 variant;
    s32 model;
    s32 id;

    if (event != 1) {
        return 0;
    }
    MarkMenuEventHandled();
    if (Menu_GetPreviousScreenOwner(0) == 22) {
        return 0;
    }
    variant = g_joinRequestEntries[g_courseOptionsScreen->selection].variant;
    model = Join_FindJoinModelIndex(variant, g_joinRequestEntries[g_courseOptionsScreen->selection].id);
    do {
        variant--;
        if (variant < 0) {
            variant = 2;
            model--;
            if (model < 0) {
                model = 16;
            }
        }
        id = g_rewardItemTiers[variant][model].id;
    } while (id == -1);
    g_joinRequestEntries[g_courseOptionsScreen->selection].variant = variant;
    g_joinRequestEntries[g_courseOptionsScreen->selection].id = id;
    XPlus_CopyString(g_joinRequestEntries[g_courseOptionsScreen->selection].name,
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        g_rewardItemTiers[variant][id].text[g_languageIndex]
#else
        *g_rewardItemTiers[variant][id].text
#endif
    );
    g_joinRequestEntries[g_courseOptionsScreen->selection].variantC = variant;
    Join_UpdateJoinRequestDisplay(g_courseOptionsScreen->selection);
    SoundElement_PlayFlatSound(3713);
    return 0;
}

/* Steps the model of the join request the screen g_courseOptionsScreen edits (by its selection index) forward on event 1
   unless Menu_GetPreviousScreenOwner reports 0x16: calls MarkMenuEventHandled, finds the request's place in the 3 by 17
   model table g_rewardItemTiers through Join_FindJoinModelIndex, walks forward through its variants and, past the
   last, to the first variant of the next model (wrapping to the first), skipping entries whose
   id is -1, then stores the variant and the id in the request in
   g_joinRequestEntries, copies the name of the entry the found id selects in that variant row into the request, redraws through Join_UpdateJoinRequestDisplay and plays sound
   0xE81. Returns zero. */
s32 Frontend_SelectNextJoinModel(void *element, void *eventId, void *eventPayload, s32 event) {
    s32 variant;
    s32 model;
    s32 id;

    if (event != 1) {
        return 0;
    }
    MarkMenuEventHandled();
    if (Menu_GetPreviousScreenOwner(0) == 22) {
        return 0;
    }
    variant = g_joinRequestEntries[g_courseOptionsScreen->selection].variant;
    model = Join_FindJoinModelIndex(variant, g_joinRequestEntries[g_courseOptionsScreen->selection].id);
    do {
        variant++;
        if (variant >= 3) {
            variant = 0;
            model++;
            if (model >= 17) {
                model = 0;
            }
        }
        id = g_rewardItemTiers[variant][model].id;
    } while (id == -1);
    g_joinRequestEntries[g_courseOptionsScreen->selection].variant = variant;
    g_joinRequestEntries[g_courseOptionsScreen->selection].id = id;
    XPlus_CopyString(g_joinRequestEntries[g_courseOptionsScreen->selection].name,
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        g_rewardItemTiers[variant][id].text[g_languageIndex]
#else
        *g_rewardItemTiers[variant][id].text
#endif
    );
    g_joinRequestEntries[g_courseOptionsScreen->selection].variantC = variant;
    id = g_courseOptionsScreen->selection;
    Join_UpdateJoinRequestDisplay(id);
    SoundElement_PlayFlatSound(3713);
    return 0;
}
#endif

/* unit JOIN_UPDATEJOINREQUESTDISPLAY.CPP */
#if defined(VERSION_EU_X)
enum { DRAW_ICON=913, DRAW_NAME=915, DRAW_VARIANT=914, DRAW_FIRST=916, DRAW_SECOND=917 };
#elif defined(VERSION_DE)
enum { DRAW_ICON=903, DRAW_NAME=905, DRAW_VARIANT=904, DRAW_FIRST=906, DRAW_SECOND=907 };
#else
enum { DRAW_ICON=909, DRAW_NAME=911, DRAW_VARIANT=910, DRAW_FIRST=912, DRAW_SECOND=913 };
#endif
void Join_UpdateJoinRequestDisplay(s32 index) {
    void *window;
    RequestDrawScreen *screen;
    MenuWidget *widget;
    s32 model;
    char *name;
    Shared_Game *game;
    void *widgetObject;
    void *variantObject;
    char ***variantSlot;
    screen = (RequestDrawScreen *)g_courseOptionsScreen;
    window = screen->roots[index];
    if (screen->count < index || g_joinRequestEntries[index].id < 0) {
        Widget_SetWidgetFlag08(window, 0);
    } else {
        widgetObject = Node_FindWidgetByResourceId(window, DRAW_ICON);
        widget = widgetObject;
        widget->alpha = 125;
        model = Key_FindKeyIndex(g_joinRequestEntries[index].id);
        widget->value = g_characterPortraitRecords[model].portrait;
        widgetObject = Node_FindWidgetByResourceId(window, DRAW_NAME);
        widget = widgetObject;
        widget->alpha = 125;
        model = Join_FindJoinModelIndex(g_joinRequestEntries[index].variant, g_joinRequestEntries[index].id);
    name = g_joinRequestEntries[index].name;
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        game = &g_gameSettings;
        XPlus_CopyString((u8 *)name, g_joinPlayerNamesLocalized[g_joinRequestEntries[index].variant * 17 + model].names[game->language]);
#else
        XPlus_CopyString((u8 *)name,
          (u8 *)*g_rewardItemTiers[g_joinRequestEntries[index].variant][model].text
        );
#endif
        widget->text = name;
        widgetObject = Node_FindWidgetByResourceId(window, DRAW_VARIANT);
        widget = widgetObject;
        widget->alpha = 125;
#if defined(VERSION_EU) || defined(VERSION_EU_X)
        widget->text = g_resultsRankTexts[g_joinRequestEntries[index].variant][game->language];
#else
        variantObject = &g_resultsRankTexts[g_joinRequestEntries[index].variant];
        variantSlot = variantObject;
        widget->text = **variantSlot;
#endif
        widgetObject = Node_FindWidgetByResourceId(window, DRAW_FIRST);
        widget = widgetObject;
        widget->alpha = 125;
        widget->value = g_joinRequestDrawPairs[g_joinRequestEntries[index].word8].first;
        widgetObject = Node_FindWidgetByResourceId(window, DRAW_SECOND);
        widget = widgetObject;
        widget->alpha = 125;
        widget->value = g_joinRequestDrawPairs[g_joinRequestEntries[index].word8].second;
    }
}

/* Seats the three join requests in free player settings slots, searching down from slot 7. */
void Join_SeatJoinRequests(void) {
    Shared_PlayerSettingsRecord *player;
    s32 slot = 7;
    s32 i = 0;
    Shared_Game *g = &g_gameSettings;
    Shared_PlayerSettingsRecord *settings = g->playerSettings;
    do {
        if (slot <= 0) return;
        if (g_joinRequestEntries[i].id >= 0) {
            while (slot > 0 && g->playerSettings[slot].enabled == 1) {
                slot--;
            }
            if (slot >= 0) {
                player = &settings[slot];
                player->locked = 1;
                player->enabled = 1;
                player->slot = slot;
                player->character = g_joinRequestEntries[i].id;
                player->team = g_joinRequestEntries[i].variant;
                player->rank = g_joinRequestEntries[i].word8;
                player->variant = g_joinRequestEntries[i].variantC;
                XPlus_CopyString(player->name, (u8 *)g_joinRequestEntries[i].name);
                slot--;
            }
        }
        i++;
    } while (i < 3);
}

/* unit JOIN_GETJOINREQUESTRANK.CPP */
/* Scores the three entries (5, 10 or 20 points by kind for each active one, repeating the previous award for other kinds) and returns the first of five ranks whose threshold for the active-entry count reaches the score, 4 when none does, or zero with no active entry. */
static inline s32 entryScore(void) {
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


s32 Join_GetJoinRequestRank(void) {
    s32 score;
    s32 i;
    s32 count;
    s32 rank;

    score = entryScore();
    count = 0;
    for (i = 0; i < 3; i++) {
        if (g_joinRequestEntries[i].id >= 0) {
            count++;
        }
    }
    rank = 4;
    if (count <= 0) {
        return 0;
    }
    for (i = 0; i < 5; i++, count += 5) {
        if (g_rewardScoreBudgets[count - 1] >= score) {
            rank = i;
            break;
        }
    }
    return rank;
}

/* unit JOIN_RANDOMIZEJOINREQUESTENTRIES.CPP */
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "Frontend/join_randomizejoinrequestentries.h"
#include "Common/shared_gameslot.h"

void Join_RandomizeJoinRequestEntries(s32 count, s32 level) {
    Shared_Game *game;
    char *name;
    s32 points[3];
    s32 *p;
    s32 budget;
    s32 i;
    s32 *entry;
    s32 tier;
    s32 value;
    s32 pick;
    s32 last;

    if (count <= 0) {
        return;
    }
    for (i = 2, p = points + i; i >= 0; i--) {
        *p-- = 0;
    }
    last = count - 1;
    if (count <= 0) {
        budget = 0;
    } else {
        budget = g_rewardScoreBudgets[level * 5 + last];
    }
    for (i = 0; i < count; i++) {
        points[i] = 5;
        budget -= 5;
    }
    i = 0;
    while (budget > 0) {
        entry = &points[Graphu64_NextRandom() % count];
        value = *entry;
        if (value < 20 && budget >= value) {
            *entry = value * 2;
            budget -= value;
        }
        if (++i >= 10001) {
            break;
        }
    }
    for (i = 0; i < count; i++) {
        tier = points[i] / 10;
        g_joinRequestEntries[i].word8 = 4;
        g_joinRequestEntries[i].variant = tier;
        g_joinRequestEntries[i].variantC = tier;
        do {
            pick = Graphu64_NextRandom() % 17;
            g_joinRequestEntries[i].id = g_rewardItemTiers[tier][pick].id;
#if defined(VERSION_EU) || defined(VERSION_EU_X)
            name = g_joinRequestEntries[i].name;
            game = &g_gameSettings;
            XPlus_CopyString(name, g_rewardItemTiers[tier][pick].text[game->language]);
#else
            XPlus_CopyString(g_joinRequestEntries[i].name, *g_rewardItemTiers[tier][pick].text);
#endif
        } while (g_joinRequestEntries[i].id == -1);
    }
}
#endif

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
/* Deals out random rewards for count entries at difficulty level: starts every entry at 5 points
   from the level's budget in g_rewardScoreBudgets, then for up to 10001 random picks doubles an entry below
   20 points while the budget covers it; each entry then records mode 4 and its tier (points / 10)
   in g_joinRequestEntries's 0x1C-byte records and draws random tier items from the seventeen per tier in
   g_rewardItemTiers, copying the item's name, until it gets one that exists. */
#include "types.h"
#include "Common/player_join_requests.h"
#include "Constants/g_rewarditemtiers.h"
#include "X_files/x_plus.h"
#include "Frontend/frontend_address_symbols.h"

void Join_RandomizeJoinRequestEntries(s32 count, s32 level) {
    s32 points[3];
    s32 *p;
    s32 budget;
    s32 i;
    s32 *entry;
    s32 tier;
    s32 value;
    s32 pick;
    s32 last;

    if (count <= 0) {
        return;
    }
    for (i = 2, p = points + i; i >= 0; i--) {
        *p-- = 0;
    }
    last = count - 1;
    if (count <= 0) {
        budget = 0;
    } else {
        budget = g_rewardScoreBudgets[level * 5 + last];
    }
    for (i = 0; i < count; i++) {
        points[i] = 5;
        budget -= 5;
    }
    i = 0;
    while (budget > 0) {
        entry = &points[Graphu64_NextRandom() % count];
        value = *entry;
        if (value < 20 && budget >= value) {
            *entry = value * 2;
            budget -= value;
        }
        if (++i >= 10001) {
            break;
        }
    }
    for (i = 0; i < count; i++) {
        tier = points[i] / 10;
        g_joinRequestEntries[i].word8 = 4;
        g_joinRequestEntries[i].variant = tier;
        g_joinRequestEntries[i].variantC = tier;
        do {
            pick = Graphu64_NextRandom() % 17;
            g_joinRequestEntries[i].id = g_rewardItemTiers[tier][pick].id;
            XPlus_CopyString(g_joinRequestEntries[i].name, *g_rewardItemTiers[tier][pick].text);
        } while (g_joinRequestEntries[i].id == -1);
    }
}
#endif

/* unit JOIN.CPP */
#if defined(VERSION_EU)
#include "Common/resident_event_handler.h"
#include "Common/multiplayeroptions.h"
#include "Frontend/frontend_address_symbols.h"

s32 Join_DispatchEuJoinOptionsEvent(ActorDefinitionHeader *actor, s32 event, s32 eventData, s32 eventValue, s32 eventContext) {
    s32 index;
    index = 0;
    if (g_joinOptionsEventHandlers[index].handler != 0) {
        do {
            if (g_joinOptionsEventHandlers[index].event == event) {
                if (g_joinOptionsEventHandlers[index].actorKind == actor->character || g_joinOptionsEventHandlers[index].actorKind == 30000) {
                    return g_joinOptionsEventHandlers[index].handler(actor, event, eventData, eventValue, eventContext);
                }
            }
            index++;
        } while (g_joinOptionsEventHandlers[index].handler != 0);
    }
    return 0;
}
#endif

/* unit JOIN_CREATEUSJOINOPTIONSMENU.CPP */
#if defined(VERSION_US)
#include "Common/selectionscreenstate.h"
#include "Common/player_join_requests.h"
#include "types.h"
#include "Common/shared_menureply.h"
#include "Common/selectionscreenstate.h"
#include "Common/player_join_requests.h"
#include "types.h"
#include "Common/shared_menureply.h"
#include "Render/soundelement_playflatsound.h"

s32 Join_CreateUsJoinOptionsMenu(void *root) {
    MenuWidget *item;
    s32 row;

    { void *memory = Cache_AllocateMemory(32); g_courseOptionsScreen = memory; }
    g_courseOptionsScreen->handle = root;
    g_courseOptionsScreen->mode = SmpOverlay_CreateOverlayNode((s32) root, 4);
    SmpOverlay_ShowSlotById((s32) root, 0, 905);
    SmpOverlay_ShowSlotById((s32) root, 1, 905);
    SmpOverlay_ShowSlotById((s32) root, 2, 905);
    SmpOverlay_ShowSlotById((s32) root, 3, 905);

    item = Node_FindWidgetByResourceId(root, 907);
    item->alpha = 140;
    if (Menu_GetPreviousScreenOwner(0) == 22) {
        Widget_SetWidgetFlag08(item, 0);
    }

    g_courseOptionsScreen->timer = 0;
    g_courseOptionsScreen->selection = 0;
    item = Node_FindWidgetByResourceId(root, 908);
    g_courseOptionsScreen->rows[0] = item;
    item = Node_FindWidgetByResourceId(root, 917);
    g_courseOptionsScreen->rows[1] = item;
    item = Node_FindWidgetByResourceId(root, 918);
    g_courseOptionsScreen->rows[2] = item;
    g_courseOptionsScreen->step = Join_CountUsedSlots();

    for (row = 0; row < 3; row++) {
        Join_UpdateJoinRequestDisplay(row);
        item = Node_FindWidgetByResourceId(g_courseOptionsScreen->rows[row], 914);
        Widget_SetWidgetFlag08(item, 0);
    }

    Tsmos_ActivateControllerState();

    item = Node_FindWidgetByResourceId(g_courseOptionsScreen->rows[g_courseOptionsScreen->selection], 914);
    Widget_SetWidgetFlag08(item, 1);
    return 0;
}
#endif

#if defined(VERSION_US)
#include "Frontend/smp_overlay.h"
#include "Join/join_cyclejoinrequestrank.h"

s32 Join_SelectPreviousUsJoinModel(void *sender, void *context, void *argument, s32 event) {
    s32 variant;
    s32 model;
    s32 id;

    if (event != 1) return 0;
    MarkMenuEventHandled();
    if (Menu_GetPreviousScreenOwner(0) == 22) return 0;
    variant = g_joinRequestEntries[g_courseOptionsScreen->selection].variant;
    model = Join_FindJoinModelIndex(variant, g_joinRequestEntries[g_courseOptionsScreen->selection].id);
    do {
        variant--;
        if (variant < 0) {
            variant = 2;
            model--;
            if (model < 0) model = 16;
        }
        id = g_rewardItemTiers[variant][model].id;
    } while (id == -1);
    g_joinRequestEntries[g_courseOptionsScreen->selection].variant = variant;
    g_joinRequestEntries[g_courseOptionsScreen->selection].id = id;
    XPlus_CopyString(g_joinRequestEntries[g_courseOptionsScreen->selection].name,
                    *g_rewardItemTiers[variant][id].text);
    g_joinRequestEntries[g_courseOptionsScreen->selection].variantC = variant;
    Join_UpdateJoinRequestDisplay(g_courseOptionsScreen->selection);
    SoundElement_PlayFlatSound(3713);
    return 0;
}
#endif

#if defined(VERSION_US)

s32 CJoinCharacter_CycleModelSelection(void *element, void *eventId, void *eventPayload, s32 event) {
    s32 variant;
    s32 model;
    s32 id;

    if (event != 1) {
        return 0;
    }
    MarkMenuEventHandled();
    if (Menu_GetPreviousScreenOwner(0) == 22) {
        return 0;
    }
    variant = g_joinRequestEntries[g_courseOptionsScreen->selection].variant;
    model = Join_FindJoinModelIndex(variant, g_joinRequestEntries[g_courseOptionsScreen->selection].id);
    do {
        variant++;
        if (variant >= 3) {
            variant = 0;
            model++;
            if (model >= 17) {
                model = 0;
            }
        }
        id = g_rewardItemTiers[variant][model].id;
    } while (id == -1);
    g_joinRequestEntries[g_courseOptionsScreen->selection].variant = variant;
    g_joinRequestEntries[g_courseOptionsScreen->selection].id = id;
    XPlus_CopyString(g_joinRequestEntries[g_courseOptionsScreen->selection].name, *g_rewardItemTiers[variant][id].text);
    g_joinRequestEntries[g_courseOptionsScreen->selection].variantC = variant;
    id = g_courseOptionsScreen->selection;
    Join_UpdateJoinRequestDisplay(id);
    SoundElement_PlayFlatSound(3713);
    return 0;
}
#endif

/* unit FRONTEND_CREATECOURSEOPTIONSMENU.CPP */
#if defined(VERSION_US_REV1)
#include "Common/selectionscreenstate.h"
#include "Common/player_join_requests.h"
#include "types.h"
#include "Common/shared_menureply.h"
/* Creates the three-row request screen and shows its selected row. */
s32 Frontend_CreateCourseOptionsMenu(void *root) {
    SlotSelectionWidget *item;
    s32 row;

    { void *memory = Cache_AllocateMemory(32); g_courseOptionsScreen = memory; }
    g_courseOptionsScreen->handle = root;
    g_courseOptionsScreen->mode = SmpOverlay_CreateOverlayNode((s32) root, 4);
    SmpOverlay_ShowSlotById((s32) root, 0, 905);
    SmpOverlay_ShowSlotById((s32) root, 1, 905);
    SmpOverlay_ShowSlotById((s32) root, 2, 905);
    SmpOverlay_ShowSlotById((s32) root, 3, 905);

    item = Node_FindWidgetByResourceId(root, 907);
    item->alpha = 140;
    if (Menu_GetPreviousScreenOwner(0) == 22) {
        Widget_SetWidgetFlag08(item, 0);
    }

    g_courseOptionsScreen->timer = 0;
    g_courseOptionsScreen->selection = 0;
    item = Node_FindWidgetByResourceId(root, 908);
    g_courseOptionsScreen->rows[0] = item;
    item = Node_FindWidgetByResourceId(root, 917);
    g_courseOptionsScreen->rows[1] = item;
    item = Node_FindWidgetByResourceId(root, 918);
    g_courseOptionsScreen->rows[2] = item;
    g_courseOptionsScreen->step = Join_CountUsedSlots();

    for (row = 0; row < 3; row++) {
        Join_UpdateJoinRequestDisplay(row);
        item = Node_FindWidgetByResourceId(g_courseOptionsScreen->rows[row], 914);
        Widget_SetWidgetFlag08(item, 0);
    }

    Tsmos_ActivateControllerState();

    item = Node_FindWidgetByResourceId(g_courseOptionsScreen->rows[g_courseOptionsScreen->selection], 914);
    Widget_SetWidgetFlag08(item, 1);
    return 0;
}
#endif
#if defined(VERSION_EU_X)
#include "types.h"
#include "Frontend/smp_overlay.h"
#include "Join/join_cyclejoinrequestrank.h"
#include "Node/node_replacewidgetlinks.h"
#include "Frontend/frontend.h"
#endif

/* Retained data for this translation unit. */
#if !(defined(VERSION_US_REV1))
#if defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US)
const unsigned char g_characterPreviewVerticalOffset[3] = {
    0x42, 0x20, 0x00,
};
#endif
#endif
#if defined(VERSION_US_REV1)
const float g_characterPreviewVerticalOffset = 40.0f;
#endif
