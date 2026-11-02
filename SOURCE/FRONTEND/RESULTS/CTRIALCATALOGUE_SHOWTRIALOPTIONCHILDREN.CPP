#include "FRONTEND/NODE_FINDWIDGETBYRESOURCEID.H"
#include "COMMON/MENU_OPTIONS_AND_RESULTS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SCREEN.H"
#include "COMMON/ACCESS_S8_10F.H"
#include "COMMON/RESULTSOPTIONSSCREEN.H"
#include "OPTIONS.H"
#include "COMMON/MENULISTSCREEN.H"
#include "TYPES.H"
#include "FRONTEND/RESULTS_REFRESHTRIALCATALOGUEWIDGETS.H"
#include "FRONTEND/RESULTS_UPDATERESULTSHEADING.H"
#include "FRONTEND/RESULTS_FILLPROFILEWEAPONROWS.H"
#include "FRONTEND/CTRIALCATALOGUE_SHOWTRIALOPTIONCHILDREN.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"
#include "SCENE/CACHE_FREEMEMORY.H"
#include "COMMON/SHARED_GAMESLOT.H"
#define g_gameSettingsView ((u8 *)&g_gameSettings)

extern ResultsOptionsScreen *g_trialCatalogueScreen;

/* Opens the five option windows of screen g_trialCatalogueScreen: for each of options 0 to 4 it picks window
   0x149, 0x14C, 0x14D, 0x14E or 0x14F through k_trialOptionWindowIdJumpTable, opens it under the screen's parent at
   0x970, opens its 0x14B child and shows that through Widget_SetWidgetFlag08_EquipActivateequipmentpanel. The loop walks the table with
   its own pointer, as the cartridge's strength-reduced dispatch does. */


extern void Widget_SetWidgetFlag08(void *object, int enabled);

#if defined(VERSION_DE)
enum { RESULTS_OPTION_329 = 327, RESULTS_OPTION_331 = 329, RESULTS_OPTION_332 = 330, RESULTS_OPTION_333 = 331, RESULTS_OPTION_334 = 332, RESULTS_OPTION_335 = 333 };
#elif defined(VERSION_EU_X)
enum { RESULTS_OPTION_329 = 333, RESULTS_OPTION_331 = 335, RESULTS_OPTION_332 = 336, RESULTS_OPTION_333 = 337, RESULTS_OPTION_334 = 338, RESULTS_OPTION_335 = 339 };
#else
enum { RESULTS_OPTION_329 = 329, RESULTS_OPTION_331 = 331, RESULTS_OPTION_332 = 332, RESULTS_OPTION_333 = 333, RESULTS_OPTION_334 = 334, RESULTS_OPTION_335 = 335 };
#endif

/* Releases the object g_trialCatalogueScreen holds through Cache_FreeMemory, calls Tsmos_ActivateControllerState, clears g_trialCatalogueScreen, calls
   Cinema_ReleaseSequenceContext_FrontendHandletaboptionsshortcut and returns zero. */



extern void Tsmos_ActivateControllerState(void);

/* On event 3 with value 0, calls MarkMenuEventHandled, sets the word at offset 0x988 of the object
   g_trialCatalogueScreen points to to 8 and the byte at 0x10 of its item at 0xA50 to 0x5A, and plays sound
   0xE7C through SoundElement_PlayFlatSound. Returns zero. */








/* Moves the menu cursor on event 1: when the current slot's successor in the 28-byte slot table
   (word at g_trialCatalogueNeighborTwo) exists and Defs_TestBit reports it set in the menu's flags at 0xA74, it
   plays sound 0xE7D, shades the old window 0x46 or 0xAA by whether the old slot is set in the
   flags at 0xA79, opens the successor's window (halfword at g_trialCatalogueStageIdLowHalves) under parent, refreshes
   through Results_RefreshTrialSelectionLabel and, by the mode byte at 0xD of g_gameSettings, through Results_ShowTrialPreviewBanner and
   Results_UpdateResultsHeading unless the mode is 2 and Results_RefreshTrialCharacterPreview when it is 4; returns zero. */









extern s32 Defs_TestBit(void *bitArray, s32 index);

/* Moves the menu cursor on event 1: when the current slot's successor in the 28-byte slot table
   (word at g_trialCatalogueNeighborThree) exists and Defs_TestBit reports it set in the menu's flags at 0xA74, it
   plays sound 0xE7D, shades the old window 0x46 or 0xAA by whether the old slot is set in the
   flags at 0xA79, opens the successor's window (halfword at g_trialCatalogueStageIdLowHalves) under parent, refreshes
   through Results_RefreshTrialSelectionLabel and, by the mode byte at 0xD of g_gameSettings, through Results_ShowTrialPreviewBanner and
   Results_UpdateResultsHeading unless the mode is 2 and Results_RefreshTrialCharacterPreview when it is 4; returns zero. Adapted from CTrialCatalogue_SelectNeighborTwo with the successor word changed. */







/* Moves the menu cursor on event 1: when the current slot's successor in the 28-byte slot table
   (word at g_trialCatalogueNeighborOne) exists and Defs_TestBit reports it set in the menu's flags at 0xA74, it
   plays sound 0xE7D, shades the old window 0x46 or 0xAA by whether the old slot is set in the
   flags at 0xA79, opens the successor's window (halfword at g_trialCatalogueStageIdLowHalves) under parent, refreshes
   through Results_RefreshTrialSelectionLabel and, by the mode byte at 0xD of g_gameSettings, through Results_ShowTrialPreviewBanner and
   Results_UpdateResultsHeading unless the mode is 2 and Results_RefreshTrialCharacterPreview when it is 4; returns zero. Adapted from CTrialCatalogue_SelectNeighborTwo with the successor word changed. */







/* Moves the menu cursor on event 1: when the current slot's successor in the 28-byte slot table
   (word at g_trialCatalogueNeighborZero) exists and Defs_TestBit reports it set in the menu's flags at 0xA74, it
   plays sound 0xE7D, shades the old window 0x46 or 0xAA by whether the old slot is set in the
   flags at 0xA79, opens the successor's window (halfword at g_trialCatalogueStageIdLowHalves) under parent, refreshes
   through Results_RefreshTrialSelectionLabel and, by the mode byte at 0xD of g_gameSettings, through Results_ShowTrialPreviewBanner and
   Results_UpdateResultsHeading unless the mode is 2 and Results_RefreshTrialCharacterPreview when it is 4; returns zero. Adapted from CTrialCatalogue_SelectNeighborTwo with the successor word changed. */








/* Calls MarkMenuEventHandled and Results_HideTrialCatalogueWidgets, passes the two words after the identifier in the
   28-byte entry g_trialCatalogueScreen's selection at 0xA44 picks from g_trialCatalogueStages to Random_SetSelectedStage, then
   calls Random_SetMenuChoiceResult with 0x19. Returns zero. */






extern struct ResultsOptionEntry g_trialCatalogueStages[];
/* The window table stores word-valued resource identifiers: the key is the word cast to 16 bits. The halfword at
   word+2 (the table symbol g_trialCatalogueStageIdLowHalves) is only its low half on big-endian MIPS. */
#define entryWindowKey(index) ((u16)g_trialCatalogueStages[index].id)

extern void Random_SetSelectedStage(s32, s32);

/* Dispatches event event through this file's 12-byte handler table, whose rows hold an event at g_trialCatalogueEventIds, an actor kind at g_trialCatalogueEventKinds and a handler at g_trialCatalogueEventHandlers: the first row whose event equals event and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from N64Eng_DispatchNumericWidgetEvent. */

typedef s32 (*TrialCatalogueEventHandlerFn)(void *, s32, s32, s32, s32);

extern TrialCatalogueEventHandlerFn g_trialCatalogueEventHandlers;

/* Dispatches event event through this file's 12-byte handler table, whose rows hold an event at g_trialOptionsEventIds, an actor kind at g_trialOptionsEventKinds and a handler at g_trialOptionsEventHandlers: the first row whose event equals event and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from N64Eng_DispatchNumericWidgetEvent. */

typedef s32 (*TrialOptionsEventHandlerFn)(void *, s32, s32, s32, s32);

extern TrialOptionsEventHandlerFn g_trialOptionsEventHandlers;

void CTrialCatalogue_ShowTrialOptionChildren(void) {
    s32 id = 0;
    s32 option;

    for (option = 0; option < 5; option++) {
        switch (option) {
        case 0:
            id = RESULTS_OPTION_329;
            break;
        case 1:
            id = RESULTS_OPTION_332;
            break;
        case 2:
            id = RESULTS_OPTION_333;
            break;
        case 3:
            id = RESULTS_OPTION_334;
            break;
        case 4:
            id = RESULTS_OPTION_335;
            break;
        }
        Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(Node_FindWidgetByResourceId(g_trialCatalogueScreen->parent, id), RESULTS_OPTION_331), 1);
    }
}

s32 CTrialCatalogue_CloseTrialOptionsScreen(void) {
    Cache_FreeMemory(g_trialCatalogueScreen);
    Tsmos_ActivateControllerState();
    g_trialCatalogueScreen = 0;
    Cinema_ReleaseSequenceContext();
    return 0;
}

s32 CTrialCatalogue_HandleTrialOptionRelease(void *first, void *second, u32 event, s32 value) {
    ResultsOptionsScreen *state;

    if ((event >> 16) == 3 && value == 0) {
        MarkMenuEventHandled();
        state = g_trialCatalogueScreen;
        state->state = 8;
        state->item->alpha = 90;
        SoundElement_PlayFlatSound(3708);
    }
    return 0;
}

s32 CTrialCatalogue_SelectNeighborTwo(void *parent, s32 unused1, s32 unused2, s32 event) {
    s32 next;
    s32 set;
    u8 *options;

    MarkMenuEventHandled();
    if (event != 1) {
        return 0;
    }
    next = g_trialCatalogueNeighborTwo[g_trialCatalogueScreen->selection * 7];
    if (next == -1) {
        return 0;
    }
    set = Defs_TestBit(g_trialCatalogueScreen->owned, next);
    if (set != 1) {
        return 0;
    }
    SoundElement_PlayFlatSound(3709);
    if (Defs_TestBit(g_trialCatalogueScreen->pending, g_trialCatalogueScreen->selection) == set) {
        g_trialCatalogueScreen->window->alpha = 70;
    } else {
        g_trialCatalogueScreen->window->alpha = 170;
    }
    g_trialCatalogueScreen->selection = next;
    g_trialCatalogueScreen->window = Node_FindWidgetByResourceId(parent, entryWindowKey(next));
    Results_RefreshTrialSelectionLabel();
    options = g_gameSettingsView;
    if (options[13] != 2) {
        Results_ShowTrialPreviewBanner();
        g_trialCatalogueScreen->frames = 0;
        Results_UpdateResultsHeading();
    }
    if (options[13] == 4) {
        Results_RefreshTrialCharacterPreview();
    }
    return 0;
}

s32 CTrialCatalogue_SelectNeighborThree(void *parent, s32 unused1, s32 unused2, s32 event) {
    s32 next;
    s32 set;
    u8 *options;

    MarkMenuEventHandled();
    if (event != 1) {
        return 0;
    }
    next = g_trialCatalogueNeighborThree[g_trialCatalogueScreen->selection * 7];
    if (next == -1) {
        return 0;
    }
    set = Defs_TestBit(g_trialCatalogueScreen->owned, next);
    if (set != 1) {
        return 0;
    }
    SoundElement_PlayFlatSound(3709);
    if (Defs_TestBit(g_trialCatalogueScreen->pending, g_trialCatalogueScreen->selection) == set) {
        g_trialCatalogueScreen->window->alpha = 70;
    } else {
        g_trialCatalogueScreen->window->alpha = 170;
    }
    g_trialCatalogueScreen->selection = next;
    g_trialCatalogueScreen->window = Node_FindWidgetByResourceId(parent, entryWindowKey(next));
    Results_RefreshTrialSelectionLabel();
    options = g_gameSettingsView;
    if (options[13] != 2) {
        Results_ShowTrialPreviewBanner();
        g_trialCatalogueScreen->frames = 0;
        Results_UpdateResultsHeading();
    }
    if (options[13] == 4) {
        Results_RefreshTrialCharacterPreview();
    }
    return 0;
}

s32 CTrialCatalogue_SelectNeighborOne(void *parent, s32 unused1, s32 unused2, s32 event) {
    s32 next;
    s32 set;
    u8 *options;

    MarkMenuEventHandled();
    if (event != 1) {
        return 0;
    }
    next = g_trialCatalogueNeighborOne[g_trialCatalogueScreen->selection * 7];
    if (next == -1) {
        return 0;
    }
    set = Defs_TestBit(g_trialCatalogueScreen->owned, next);
    if (set != 1) {
        return 0;
    }
    SoundElement_PlayFlatSound(3709);
    if (Defs_TestBit(g_trialCatalogueScreen->pending, g_trialCatalogueScreen->selection) == set) {
        g_trialCatalogueScreen->window->alpha = 70;
    } else {
        g_trialCatalogueScreen->window->alpha = 170;
    }
    g_trialCatalogueScreen->selection = next;
    g_trialCatalogueScreen->window = Node_FindWidgetByResourceId(parent, entryWindowKey(next));
    Results_RefreshTrialSelectionLabel();
    options = g_gameSettingsView;
    if (options[13] != 2) {
        Results_ShowTrialPreviewBanner();
        g_trialCatalogueScreen->frames = 0;
        Results_UpdateResultsHeading();
    }
    if (options[13] == 4) {
        Results_RefreshTrialCharacterPreview();
    }
    return 0;
}

s32 CTrialCatalogue_SelectNeighborZero(void *parent, s32 unused1, s32 unused2, s32 event) {
    s32 next;
    s32 set;
    u8 *options;

    MarkMenuEventHandled();
    if (event != 1) {
        return 0;
    }
    next = g_trialCatalogueNeighborZero[g_trialCatalogueScreen->selection * 7];
    if (next == -1) {
        return 0;
    }
    set = Defs_TestBit(g_trialCatalogueScreen->owned, next);
    if (set != 1) {
        return 0;
    }
    SoundElement_PlayFlatSound(3709);
    if (Defs_TestBit(g_trialCatalogueScreen->pending, g_trialCatalogueScreen->selection) == set) {
        g_trialCatalogueScreen->window->alpha = 70;
    } else {
        g_trialCatalogueScreen->window->alpha = 170;
    }
    g_trialCatalogueScreen->selection = next;
    g_trialCatalogueScreen->window = Node_FindWidgetByResourceId(parent, entryWindowKey(next));
    Results_RefreshTrialSelectionLabel();
    options = g_gameSettingsView;
    if (options[13] != 2) {
        Results_ShowTrialPreviewBanner();
        g_trialCatalogueScreen->frames = 0;
        Results_UpdateResultsHeading();
    }
    if (options[13] == 4) {
        Results_RefreshTrialCharacterPreview();
    }
    return 0;
}

s32 CTrialCatalogue_ExitTrialCatalogue(void) {
    MarkMenuEventHandled();
    Results_HideTrialCatalogueWidgets();
    Random_SetMenuChoiceResult(14);
    return 0;
}

s32 CTrialCatalogue_ConfirmTrialStage(void) {
    s32 selection;

    MarkMenuEventHandled();
    Results_HideTrialCatalogueWidgets();
    selection = g_trialCatalogueScreen->selection;
    Random_SetSelectedStage(g_trialCatalogueStages[selection].first, g_trialCatalogueStages[selection].second);
    Random_SetMenuChoiceResult(25);
    return 0;
}

s32 CTrialCatalogue_DispatchCatalogueEvent(void *eventObject, s32 eventId, s32 eventPayload, s32 eventValue, s32 eventExtra) {
    TrialCatalogueEventHandlerFn *entry;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;
    MenuActorInputView *actor;

    if (g_trialCatalogueEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_trialCatalogueEventHandlers;
        index = 0;
        do {
            if (g_trialCatalogueEventIds[index].value == eventId) {
                actor = eventObject;
                actor_kind = actor->input;
                table_kind = g_trialCatalogueEventKinds[index].value;
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

s32 CTrialCatalogue_DispatchOptionsEvent(void *eventObject, s32 eventId, s32 eventPayload, s32 eventValue, s32 eventExtra) {
    TrialOptionsEventHandlerFn *entry;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;
    MenuActorInputView *actor;

    if (g_trialOptionsEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_trialOptionsEventHandlers;
        index = 0;
        do {
            if (g_trialOptionsEventIds[index].value == eventId) {
                actor = eventObject;
                actor_kind = actor->input;
                table_kind = g_trialOptionsEventKinds[index].value;
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
