#include "Frontend/node_findwidgetbyresourceid.h"
#include "Common/numberpadscreen.h"
#include "Common/sharedplayer.h"
#include "types.h"
#include "Menu/menu_refreshextraoptionlocks.h"
#include "Common/shared_gameslot.h"
#include "Common/selectionscreenstate.h"
#include "Common/screen.h"
#include "Ui/smp_button.h"
#include "Achieve/achieve.h"
#include "Frontend/widget_findwidgetatpoint.h"
#include "Menu/menu_advancetextrows.h"
#include "Menu/Extraoptions/menu_refreshextraoptionlocks_symbols.h"
#include "include_asm.h"
#include "Common/runtime_declarations.h"
#include "Common/Lone/g_languageindex.h"
#include "Common/resident_event_handler.h"
#include "Menu/event.h"
#include "Data/Ovltbl/menu_openoptionskeypad_data.h"
#include "Menu/Extraoptions/menu_openoptionskeypad_data_symbols.h"
#include "Ui/Tsmos/Smp/smp_button.h"
#include "Ui/Tsmos/Smp/smp_fade.h"
#include "Frontend/options_list_declarations.h"
#include "Menu/Extraoptions/menu_openruletogglescreen_symbols.h"
#include "Common/pakqueuestate.h"
#include <platform_sdk.h>
#include "Menu/menu_scrolloptionskeypad.h"
#include "Scene/cache_freememory.h"
#include "Common/shared_menureply.h"
#include "Menu/menu_advancefademeter.h"
#include "Common/cheatcode.h"
#include "Menu/state.h"
#include "Common/aiprofile.h"
#include "Menu/menu_dispatchextraoptionsevent.h"
#include "Frontend/frontend.h"

#if defined(VERSION_DE)
enum { k_extraOptionHighTierLockId = 935, k_extraOptionTopTierLockId = 937, k_extraOptionLowTierLockId = 939, k_extraOptionLowestTierLockId = 942 };
#elif defined(VERSION_EU_X)
enum { k_extraOptionHighTierLockId = 950, k_extraOptionTopTierLockId = 952, k_extraOptionLowTierLockId = 947, k_extraOptionLowestTierLockId = 944 };
#else
enum { k_extraOptionHighTierLockId = 941, k_extraOptionTopTierLockId = 943, k_extraOptionLowTierLockId = 945, k_extraOptionLowestTierLockId = 948 };
#endif

#if defined(VERSION_DE)
enum { k_keypadHiddenWidget = 933, k_keypadDigitWidgetBase = 946 };
#elif defined(VERSION_EU_X)
enum { k_keypadHiddenWidget = 943, k_keypadDigitWidgetBase = 956 };
#else
enum { k_keypadHiddenWidget = 939, k_keypadDigitWidgetBase = 952 };
#endif

void Menu_ApplyExtraOptionFlags(void) {
    if (SmpButton_GetListSelection(g_extraOptionsScreen->buttons[0]) == 0) {
        g_gameSettings.flags &= ~0x08000000;
    } else {
        g_gameSettings.flags |= 0x08000000;
    }
    if (SmpButton_GetListSelection(g_extraOptionsScreen->buttons[1]) == 0) {
        g_gameSettings.flags &= ~0x10000000;
    } else {
        g_gameSettings.flags |= 0x10000000;
    }
    if (SmpButton_GetListSelection(g_extraOptionsScreen->buttons[2]) == 0) {
        g_gameSettings.flags &= ~0x8;
    } else {
        g_gameSettings.flags |= 0x8;
    }
    if (SmpButton_GetListSelection(g_extraOptionsScreen->buttons[3]) == 0) {
        g_gameSettings.flags &= ~0x20000000;
    } else {
        g_gameSettings.flags |= 0x20000000;
    }
}

/* Updates the limit markers of the screen g_extraOptionsScreen: totals Achieve_CountEarnedAchievements over the four 400-byte
   records of g_localPlayerProfiles whose owner is not negative (or takes 40 when the frontend's extra-limit flag is
   1), enables items 0x3B4, 0x3B1, 0x3AD and 0x3AF of the screen's window through Widget_SetWidgetFlag100_MenuRefreshextraoptionlocks, then
   disables 0x3B1 from a total of 10, 0x3B4 from 6, 0x3AD from 12 and 0x3AF from 14. */
void Menu_RefreshExtraOptionLocks(void) {
    s32 total;
    s32 i;

    total = 0;
    for (i = 0; i < 4; i++) {
        if (g_profileSlotIndices[i][0] >= 0) {
            total += Achieve_CountEarnedAchievements(i);
        }
    }
    if (g_extraOptionsScreen->full == 1) {
        total = 40;
    }
    Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(g_extraOptionsScreen->window, k_extraOptionLowestTierLockId), 1);
    Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(g_extraOptionsScreen->window, k_extraOptionLowTierLockId), 1);
    Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(g_extraOptionsScreen->window, k_extraOptionHighTierLockId), 1);
    Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(g_extraOptionsScreen->window, k_extraOptionTopTierLockId), 1);
    if (total >= 10) {
        Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(g_extraOptionsScreen->window, k_extraOptionLowTierLockId), 0);
    }
    if (total >= 6) {
        Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(g_extraOptionsScreen->window, k_extraOptionLowestTierLockId), 0);
    }
    if (total >= 12) {
        Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(g_extraOptionsScreen->window, k_extraOptionHighTierLockId), 0);
    }
    if (total >= 14) {
        Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(g_extraOptionsScreen->window, k_extraOptionTopTierLockId), 0);
    }
}

/* Resets the number pad of the screen g_extraOptionsScreen: shows the screen's number pad item, hides item 0x3AB of its
   window, sets four number pad settings to 1, 8, 0 and 0, then for keys 0 to
   9 takes item 0x3B8 plus the key, sets its alpha to 0x96 and clears its pending flag, and
   finishes through Menu_AdvanceTextRows. */
void Menu_OpenOptionsKeypad(void) {
    MenuWidget *item;
    s32 key;

    Widget_SetWidgetFlag08(g_extraOptionsScreen->pad, 1);
    Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_extraOptionsScreen->window, k_keypadHiddenWidget), 0);
    g_extraOptionsScreen->mode = 1;
    g_extraOptionsScreen->length = 8;
    g_extraOptionsScreen->value = 0;
    g_extraOptionsScreen->cursor = 0;
    for (key = 0; key < 10; key++) {
        switch (key) {
        case 1:
            item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, k_keypadDigitWidgetBase + 1);
            break;
        case 2:
            item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, k_keypadDigitWidgetBase + 2);
            break;
        case 3:
            item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, k_keypadDigitWidgetBase + 3);
            break;
        case 4:
            item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, k_keypadDigitWidgetBase + 4);
            break;
        case 5:
            item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, k_keypadDigitWidgetBase + 5);
            break;
        case 6:
            item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, k_keypadDigitWidgetBase + 6);
            break;
        case 7:
            item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, k_keypadDigitWidgetBase + 7);
            break;
        case 8:
            item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, k_keypadDigitWidgetBase + 8);
            break;
        case 9:
            item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, k_keypadDigitWidgetBase + 9);
            break;
        case 0:
        default:
            item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, k_keypadDigitWidgetBase);
            break;
        }
        item->alpha = 150;
        item->word38 = 0;
    }
    Menu_AdvanceTextRows();
}

#if defined(VERSION_EU) || defined(VERSION_EU_X)
#define CREDITS_LINES g_creditsLocalizedLines[g_languageIndex]
#else
#define CREDITS_LINES g_creditsLocalizedLines[0]
#endif
#if defined(VERSION_DE)
#define ID_ROW0 946
#define ID_CLOSE 933
#elif defined(VERSION_EU_X)
#define ID_ROW0 956
#define ID_CLOSE 943
#else
#define ID_ROW0 952
#define ID_CLOSE 939
#endif
void Menu_AdvanceTextRows(void) {
    MenuWidget *item;
    char *text;
    s32 line;
    s32 index;

    line = g_extraOptionsScreen->length;
    index = g_extraOptionsScreen->value;
    do {
        text = CREDITS_LINES[index];

        if (text != 0) {
            index++;
        }
        item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, ID_ROW0);
        switch (line) {
        case 0:
            item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, ID_ROW0);
            break;
        case 1:
            item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, ID_ROW0 + 1);
            break;
        case 2:
            item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, ID_ROW0 + 2);
            break;
        case 3:
            item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, ID_ROW0 + 3);
            break;
        case 4:
            item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, ID_ROW0 + 4);
            break;
        case 5:
            item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, ID_ROW0 + 5);
            break;
        case 6:
            item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, ID_ROW0 + 6);
            break;
        case 7:
            item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, ID_ROW0 + 7);
            break;
        case 8:
            item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, ID_ROW0 + 8);
            break;
        case 9:
            item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, ID_ROW0 + 9);
            break;
        }
        item->text = text;
        line++;
    } while (line < 10);
        if (CREDITS_LINES[g_extraOptionsScreen->value] != 0)

    {
        if (g_extraOptionsScreen->length == 0) {
            g_extraOptionsScreen->value++;
        }
    } else {
        Widget_SetWidgetFlag08(g_extraOptionsScreen->pad, 0);
        Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_extraOptionsScreen->window, ID_CLOSE), 1);
        g_extraOptionsScreen->cursor = 1;
    }
    if (g_extraOptionsScreen->length > 0) {
        g_extraOptionsScreen->length--;
    }
}
#undef CREDITS_LINES
#undef ID_ROW0
#undef ID_CLOSE

#if defined(VERSION_EU)
struct {
    void * g_extraOptionsScreen;
} k_MenuOpenoptionskeypadZeroWords __attribute__((aligned(4))) = {
    0
};
typedef char k_MenuOpenoptionskeypadZeroWordsSizeCheck[(sizeof(k_MenuOpenoptionskeypadZeroWords) == 4) ? 1 : -1];
#endif
#if defined(VERSION_EU_X)
struct {
    void * g_extraOptionsScreen;
} k_MenuOpenoptionskeypadZeroWords __attribute__((aligned(4))) = {
    0
};
typedef char k_MenuOpenoptionskeypadZeroWordsSizeCheck[(sizeof(k_MenuOpenoptionskeypadZeroWords) == 4) ? 1 : -1];
#endif
#if defined(VERSION_US)
struct {
    void * g_extraOptionsScreen;
} k_MenuOpenoptionskeypadZeroWords __attribute__((aligned(4))) = {
    0
};
typedef char k_MenuOpenoptionskeypadZeroWordsSizeCheck[(sizeof(k_MenuOpenoptionskeypadZeroWords) == 4) ? 1 : -1];
#endif
#if defined(VERSION_US_REV1)
struct {
    void * g_extraOptionsScreen;
} k_MenuOpenoptionskeypadZeroWords __attribute__((aligned(4))) = {
    0
};
typedef char k_MenuOpenoptionskeypadZeroWordsSizeCheck[(sizeof(k_MenuOpenoptionskeypadZeroWords) == 4) ? 1 : -1];
#endif
#if !(defined(VERSION_US) || defined(VERSION_US_REV1))
#if defined(VERSION_EU)
struct {
    ResidentEventHandlerEntry handlers[6];
    u32 retainedInstructionWord[1];
} g_menuOpenOptionsKeypadRecord __attribute__((aligned(4))) = {
    { { 3592, 28, (ResidentEventHandler)(void *)&addrLow_Menu_UpdateExtraOptionsMenu }, { 3590, 28, (ResidentEventHandler)(void *)&addrLow_Menu_OpenRuleToggleScreen }, { 3587, 28, (ResidentEventHandler)(void *)&addrLow_Menu_DestroyExtraOptionsMenu }, { 2, 28, (ResidentEventHandler)(void *)&addrLow_Menu_ConfirmExtraOptions }, { 1, 28, (ResidentEventHandler)(void *)&addrLow_Menu_HandleExtraOptionsChoice }, { 0, 0, (ResidentEventHandler)0 } },
    { 0x8C850320 }
};
#endif
#if defined(VERSION_EU_X)
struct {
    ResidentEventHandlerEntry handlers[6];
    u32 zeroTail[1];
} g_menuOpenOptionsKeypadRecord __attribute__((aligned(4))) = {
    { { 3592, 28, (ResidentEventHandler)(void *)(g_Selection_DispatchCharacterSelectionEventAddress + 2956) }, { 3590, 28, (ResidentEventHandler)(void *)(g_Selection_DispatchCharacterSelectionEventAddress + 144) }, { 3587, 28, (ResidentEventHandler)(void *)(g_Selection_DispatchCharacterSelectionEventAddress + 2908) }, { 2, 28, (ResidentEventHandler)(void *)(g_Selection_DispatchCharacterSelectionEventAddress + 3264) }, { 1, 28, (ResidentEventHandler)(void *)(g_Selection_DispatchCharacterSelectionEventAddress + 3120) }, { 0, 0, (ResidentEventHandler)0 } },
    { 0x00000000 }
};
#endif
#endif
#if defined(VERSION_US) || defined(VERSION_US_REV1)
#if defined(VERSION_US)
ResidentEventHandlerEntry g_MenuOpenoptionskeypadEncodedWords[6] = {
    { 3592, 28, (ResidentEventHandler)(void *)&g_menu_UpdateExtraOptionsMenuEntry }, { 3590, 28, (ResidentEventHandler)(void *)&g_menu_OpenRuleToggleScreenEntry }, { 3587, 28, (ResidentEventHandler)(void *)&g_menu_DestroyExtraOptionsMenuEntry }, { 2, 28, (ResidentEventHandler)(void *)&g_menu_ConfirmExtraOptionsEntry }, { 1, 28, (ResidentEventHandler)(void *)&g_menu_HandleExtraOptionsChoiceEntry }, { 0, 0, (ResidentEventHandler)0 }
};
#endif
#if defined(VERSION_US_REV1)
ResidentEventHandlerEntry g_MenuOpenoptionskeypadEncodedWords[6] = {
    { 3592, 28, (ResidentEventHandler)(void *)&g_menu_UpdateExtraOptionsMenuEntry }, { 3590, 28, (ResidentEventHandler)(void *)&g_menu_OpenRuleToggleScreenEntry }, { 3587, 28, (ResidentEventHandler)(void *)&g_menu_DestroyExtraOptionsMenuEntry }, { 2, 28, (ResidentEventHandler)(void *)&g_menu_ConfirmExtraOptionsEntry }, { 1, 28, (ResidentEventHandler)(void *)&g_menu_HandleExtraOptionsChoiceEntry }, { 0, 0, (ResidentEventHandler)0 }
};
#endif
#endif
#if defined(VERSION_US)
struct {
    u8 retainedEosTagWords[4];
} g_MenuOpenoptionskeypadTrailingWord __attribute__((aligned(4))) = {
    { 0x75, 0x04, 0x2E, 0x65 }
};
#endif

/* Opens the options screen: allocates its screen state into g_extraOptionsScreen for window window, builds
   its title, heading and the four toggle buttons 0x3B4, 0x3B1, 0x3AD and 0x3AF set from bits of
   g_gameSettings, creates the item list and refreshes the limit markers through Menu_RefreshExtraOptionLocks. */
#if defined(VERSION_EU) || defined(VERSION_EU_X)
/* Per-language label pointer tables, indexed by the settings language. */
#define SETTINGS_DECL Shared_Game *settings;
#define SETTINGS_INIT settings = &g_gameSettings;
#define SETTINGS_FLAGS (settings->flags)
#define LABEL0 g_optionsOffLabels[settings->language]
#define LABEL1 g_alternateSettingsControlLabels[settings->language]
#else
#define SETTINGS_DECL
#define SETTINGS_INIT
#define SETTINGS_FLAGS (g_gameSettings.flags)
#define LABEL0 g_toggleListClearLabel[0]
#define LABEL1 g_toggleListSetLabel[0]
#endif

/* The hub spells the allocator, the window item lookup and the list builder; these helpers stay. */
#if defined(VERSION_DE)
#define ID(n) ((n) - 6)
#define COLOR 134
#elif defined(VERSION_EU_X)
/* EU-X numbers the same widgets in a different order. */
#define ID(n) ((n) == 936 ? 940 : (n) == 937 ? 941 : (n) == 938 ? 942 : (n) == 940 ? 954 : \
               (n) == 941 ? 950 : (n) == 942 ? 951 : (n) == 943 ? 952 : (n) == 944 ? 953 : \
               (n) == 945 ? 947 : (n) == 946 ? 948 : (n) == 948 ? 944 : (n) == 949 ? 945 : \
               (n) == 950 ? 946 : 955)
#define COLOR 134
#else
#define ID(n) (n)
#define COLOR 136
#endif
s32 Menu_OpenRuleToggleScreen(void *window) {
    struct OptionsOpenScreen *screen;
    void *button;
    SETTINGS_DECL

    screen = (struct OptionsOpenScreen *) Cache_AllocateMemory(60);
    g_extraOptionsScreen = screen;
    screen->window = window;
    screen->full = 0;
    /* The shared widget type has no color member; the options view of the item names it. */
    ((OptionsOpenItem *) Node_FindWidgetByResourceId(window, ID(936)))->color = COLOR;
    g_extraOptionsScreen->title = SmpFade_CreateFadeWidget(ID(936), ID(937));
    SmpButton_WrapButtonWidget(ID(950));

    SETTINGS_INIT
    SmpButton_AppendListText(g_extraOptionsScreen->buttons[0] = SmpButton_CreateListWidget(ID(948), ID(949)), LABEL0);
    SmpButton_AppendListText(g_extraOptionsScreen->buttons[0], LABEL1);
    if (SETTINGS_FLAGS & 0x8000000) {
        SmpButton_SelectListEntry(g_extraOptionsScreen->buttons[0], 1);
    } else {
        SmpButton_SelectListEntry(g_extraOptionsScreen->buttons[0], 0);
    }

    SETTINGS_INIT
    SmpButton_AppendListText(g_extraOptionsScreen->buttons[1] = SmpButton_CreateListWidget(ID(945), ID(946)), LABEL0);
    SmpButton_AppendListText(g_extraOptionsScreen->buttons[1], LABEL1);
    if (SETTINGS_FLAGS & 0x10000000) {
        SmpButton_SelectListEntry(g_extraOptionsScreen->buttons[1], 1);
    } else {
        SmpButton_SelectListEntry(g_extraOptionsScreen->buttons[1], 0);
    }

    SETTINGS_INIT
    SmpButton_AppendListText(g_extraOptionsScreen->buttons[2] = SmpButton_CreateListWidget(ID(941), ID(942)), LABEL0);
    SmpButton_AppendListText(g_extraOptionsScreen->buttons[2], LABEL1);
    if (SETTINGS_FLAGS & 0x8) {
        SmpButton_SelectListEntry(g_extraOptionsScreen->buttons[2], 1);
    } else {
        SmpButton_SelectListEntry(g_extraOptionsScreen->buttons[2], 0);
    }

    SETTINGS_INIT
    SmpButton_AppendListText(g_extraOptionsScreen->buttons[3] = SmpButton_CreateListWidget(ID(943), ID(944)), LABEL0);
    SmpButton_AppendListText(g_extraOptionsScreen->buttons[3], LABEL1);
    if (SETTINGS_FLAGS & 0x20000000) {
        SmpButton_SelectListEntry(g_extraOptionsScreen->buttons[3], 1);
    } else {
        SmpButton_SelectListEntry(g_extraOptionsScreen->buttons[3], 0);
    }

    SmpButton_WrapButtonWidget(ID(940));
    g_extraOptionsScreen->cursor = (OptionsOpenItem *) Node_FindWidgetByResourceId(window, ID(951));
    g_extraOptionsScreen->length = 0;
    g_extraOptionsScreen->mode = 0;
    g_extraOptionsScreen->open = 1;
    /* the hub publishes the list builder as returning the word naming the list; the member stores it */
    g_extraOptionsScreen->list = (void *) SmpFlicker_CreateFlickerWidget(ID(938), 110);
    Menu_RefreshExtraOptionLocks();
    return 0;
}
#undef SETTINGS_DECL
#undef SETTINGS_INIT
#undef SETTINGS_FLAGS
#undef LABEL0
#undef LABEL1
#undef ID
#undef COLOR

/* Advances the animation frame countdown and wraps exhausted frames. */


/* Polls the dialog of screen g_extraOptionsScreen through SmpSlider_GetTransitionMode: state 3 opens the screen through
   Menu_ScrollOptionsKeypad while its word at 0x34 is zero, and otherwise, when g_combinedControllerProfile.buttons is 0x433, marks the
   screen confirmed at 0x38 and calls Menu_RefreshExtraOptionLocks; state 4 calls MarkMenuEventHandled and waits 3
   through SmXlate_SwitchScreen. Returns zero. */
void Menu_ShowExtraOptionsPanel(void) {
    Widget_SetWidgetFlag08(g_extraOptionsScreen->pad, 0);
#if defined(VERSION_DE)
    Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_extraOptionsScreen->window, 933), 1);
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_extraOptionsScreen->window, 939), 1);
#elif defined(VERSION_EU_X)
    Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_extraOptionsScreen->window, 943), 1);
#endif
    g_extraOptionsScreen->open = 1;
}

void Menu_ScrollOptionsKeypad(void) {
    s32 currentMode;
    MenuWidget *scrollingPad;
    MenuWidget *wrappedPad;
    MenuWidget *textRow;
    currentMode = g_extraOptionsScreen->mode - 1;
    g_extraOptionsScreen->mode = currentMode;
    if (currentMode <= 0) {
#if defined(VERSION_DE)
        textRow = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, 946);
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
        textRow = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, 952);
#elif defined(VERSION_EU_X)
        textRow = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, 956);
#endif
        scrollingPad = g_extraOptionsScreen->pad;
        scrollingPad->y = (u16) (scrollingPad->y - 1);
        wrappedPad = g_extraOptionsScreen->pad;
        if (((s16) wrappedPad->y + textRow->height) < 0) {
            wrappedPad->y = 2U;
            Menu_AdvanceTextRows();
        }
        g_extraOptionsScreen->mode = 1;
    }
}

s32 Menu_DestroyExtraOptionsMenu(void) {
    Cache_FreeMemory(g_extraOptionsScreen);
    g_extraOptionsScreen = 0;
    return 0;
}

s32 Menu_UpdateExtraOptionsMenu(void) {
    switch (SmpSlider_GetTransitionMode(g_extraOptionsScreen->dialog)) {
    case 3:
        if (g_extraOptionsScreen->open == 0) {
            Menu_ScrollOptionsKeypad();
            return 0;
        }
        if (g_combinedControllerProfile.buttons != 0x433) {
            return 0;
        }
        g_extraOptionsScreen->confirmed = 1;
        Menu_RefreshExtraOptionLocks();
        return 0;
    case 4:
        MarkMenuEventHandled();
        SmXlate_SwitchScreen(3);
        return 0;
    }
    return 0;
}

#if defined(VERSION_EU_X)
s32 Menu_HandleEuxExtraOptionsChoice(void) {
    s32 message;
    MarkMenuEventHandled();
    if (g_extraOptionsScreen->open == 0) {
        Menu_ShowExtraOptionsPanel();
    } else {
        message = Menu_GetFocusedElementId();
        switch (message) {
        case 954:
            SmpSlider_SetTransitionMode(g_extraOptionsScreen->dialog, 2);
            Menu_ApplyExtraOptionFlags();
            break;
        case 946:
            Menu_OpenOptionsKeypad();
            break;
        }
    }
    return 0;
}
#endif
#if defined(VERSION_DE)
enum { menuId3ac = 934, menuId3b6 = 944 };
/* Calls MarkMenuEventHandled, then Menu_ShowExtraOptionsPanel when a field of the object g_extraOptionsScreen
   points to is clear, or SmpSlider_SetTransitionMode on its first word with 2 and Menu_ApplyExtraOptionFlags otherwise.
   Returns zero. */
s32 Menu_HandleGermanExtraOptionsChoice(void) {
    if (SmpSlider_GetTransitionMode(g_extraOptionsScreen->dialog) != 3) {
        return 0;
    }
    MarkMenuEventHandled();
    if (g_extraOptionsScreen->open == 0) {
        Menu_ShowExtraOptionsPanel();
    } else {
        switch (Menu_GetFocusedElementId()) {
        case menuId3ac:
            SmpSlider_SetTransitionMode(g_extraOptionsScreen->dialog, 2);
            Menu_ApplyExtraOptionFlags();
            break;
        case menuId3b6:
            Menu_OpenOptionsKeypad();
            break;
        }
    }
    return 0;
}
#endif

#if !(defined(VERSION_DE) || defined(VERSION_EU_X))
s32 Menu_HandleExtraOptionsChoice(void) {
    MarkMenuEventHandled();
    if (g_extraOptionsScreen->open == 0) {
        Menu_ShowExtraOptionsPanel();
    } else {
        switch (Menu_GetFocusedElementId()) {
        case 940:
            SmpSlider_SetTransitionMode(g_extraOptionsScreen->dialog, 2);
            Menu_ApplyExtraOptionFlags();
            break;
        case 950:
            Menu_OpenOptionsKeypad();
            break;
        }
    }
    return 0;
}
#endif

#if !(defined(VERSION_DE))
/* Calls MarkMenuEventHandled, then Menu_ShowExtraOptionsPanel when a field of the object g_extraOptionsScreen
   points to is clear, or SmpSlider_SetTransitionMode on its first word with 2 and Menu_ApplyExtraOptionFlags otherwise.
   Returns zero. */
struct StateMenuConfirmGermanExtraOptions;

s32 Menu_ConfirmExtraOptions(void) {
    struct StateMenuConfirmGermanExtraOptions *state;

    MarkMenuEventHandled();
    state = g_extraOptionsScreen;
    if (state->ready == 0) {
        Menu_ShowExtraOptionsPanel();
    } else {
        SmpSlider_SetTransitionMode(state->first, 2);
        Menu_ApplyExtraOptionFlags();
    }
    return 0;
}
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US) || defined(VERSION_US_REV1)
/* Dispatches event event through this file's 12-byte handler table, whose rows hold an event at g_extraOptionsEventCodes, an actor kind at g_extraOptionsActorKinds and a handler at g_extraOptionsEventCallbacks: the first row whose event equals event and whose kind equals the actor's input kind, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. */
s32 Menu_DispatchExtraOptionsEvent(void *object, s32 event, s32 eventData, s32 eventValue, s32 eventContext) {
    ResidentEventHandlerEntry *row = (ResidentEventHandlerEntry *)&g_extraOptionsEventCodes;
    MenuWidget *actor = object;
    for (; row->handler != 0; ++row) {
        if (row->event == event &&
            (row->actorKind == actor->resource || row->actorKind == ANY_ACTOR_KIND)) {
            return row->handler(object, event, eventData, eventValue, eventContext);
        }
    }
    return 0;
}
#endif
