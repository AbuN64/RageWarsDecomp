#include "FRONTEND/NODE_FINDWIDGETBYRESOURCEID.H"
#include "COMMON/NUMBERPADSCREEN.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "TYPES.H"
#include "MENU/MENU_REFRESHEXTRAOPTIONLOCKS.H"
#include "COMMON/SHARED_GAMESLOT.H"
#define g_gameSettingsView (*(struct MemoryUsageStats *)&g_gameSettings)
extern NumberPadScreen *g_extraOptionsScreen;

/* Copies the four checkboxes at 0xC to 0x18 of the screen g_extraOptionsScreen into the game flags word
   g_gameSettings, setting or clearing bits 0x08000000, 0x10000000, 0x8 and 0x20000000 as
   SmpButton_GetListSelection reports each box checked. */






extern s32 SmpButton_GetListSelection(s32 *record);

/* Updates the limit markers of the screen g_extraOptionsScreen: totals Achieve_CountEarnedAchievements over the four 400-byte
   records of g_localPlayerProfiles whose owner byte 0xD is not negative (or takes 40 when the word at 0x38 is
   1), enables items 0x3B4, 0x3B1, 0x3AD and 0x3AF of the window at 0x8 through Widget_SetWidgetFlag100_MenuRefreshextraoptionlocks, then
   disables 0x3B1 from a total of 10, 0x3B4 from 6, 0x3AD from 12 and 0x3AF from 14. Written from
   the assembly. */



extern s8 g_profileSlotIndices[];

extern s32 Achieve_CountEarnedAchievements(s32);

extern void Widget_SetWidgetFlag100(MenuWidget *record, int enable);

#if defined(VERSION_DE)
enum { k_extraOptionLockAtTotal12 = 935, k_extraOptionLockAtTotal14 = 937, k_extraOptionLockAtTotal10 = 939, k_extraOptionLockAtTotal6 = 942 };
#elif defined(VERSION_EU_X)
enum { k_extraOptionLockAtTotal12 = 950, k_extraOptionLockAtTotal14 = 952, k_extraOptionLockAtTotal10 = 947, k_extraOptionLockAtTotal6 = 944 };
#else
enum { k_extraOptionLockAtTotal12 = 941, k_extraOptionLockAtTotal14 = 943, k_extraOptionLockAtTotal10 = 945, k_extraOptionLockAtTotal6 = 948 };
#endif

/* Resets the number pad of the screen g_extraOptionsScreen: shows the item at 0x20, hides item 0x3AB of the
   window at 0x8, sets the words at 0x2C, 0x28, 0x30 and 0x34 to 1, 8, 0 and 0, then for keys 0 to
   9 takes item 0x3B8 plus the key, sets its alpha to 0x96 and clears its word at 0x38, and
   finishes through Menu_AdvanceTextRows. */



extern void Widget_SetWidgetFlag08(void *object, int enabled);

extern void Menu_AdvanceTextRows();

#if defined(VERSION_DE)
enum { k_keypadHiddenWidget = 933, k_keypadKeyWidgetDigit0 = 946, k_keypadKeyWidgetDigit1 = 947, k_keypadKeyWidgetDigit2 = 948, k_keypadKeyWidgetDigit3 = 949, k_keypadKeyWidgetDigit4 = 950, k_keypadKeyWidgetDigit5 = 951, k_keypadKeyWidgetDigit6 = 952, k_keypadKeyWidgetDigit7 = 953, k_keypadKeyWidgetDigit8 = 954, k_keypadKeyWidgetDigit9 = 955 };
#elif defined(VERSION_EU_X)
enum { k_keypadHiddenWidget = 943, k_keypadKeyWidgetDigit0 = 956, k_keypadKeyWidgetDigit1 = 957, k_keypadKeyWidgetDigit2 = 958, k_keypadKeyWidgetDigit3 = 959, k_keypadKeyWidgetDigit4 = 960, k_keypadKeyWidgetDigit5 = 961, k_keypadKeyWidgetDigit6 = 962, k_keypadKeyWidgetDigit7 = 963, k_keypadKeyWidgetDigit8 = 964, k_keypadKeyWidgetDigit9 = 965 };
#else
enum { k_keypadHiddenWidget = 939, k_keypadKeyWidgetDigit0 = 952, k_keypadKeyWidgetDigit1 = 953, k_keypadKeyWidgetDigit2 = 954, k_keypadKeyWidgetDigit3 = 955, k_keypadKeyWidgetDigit4 = 956, k_keypadKeyWidgetDigit5 = 957, k_keypadKeyWidgetDigit6 = 958, k_keypadKeyWidgetDigit7 = 959, k_keypadKeyWidgetDigit8 = 960, k_keypadKeyWidgetDigit9 = 961 };
#endif

void Menu_ApplyExtraOptionFlags(void) {
    if (SmpButton_GetListSelection(g_extraOptionsScreen->buttons[0]) == 0) {
        g_gameSettingsView.value &= ~0x08000000;
    } else {
        g_gameSettingsView.value |= 0x08000000;
    }
    if (SmpButton_GetListSelection(g_extraOptionsScreen->buttons[1]) == 0) {
        g_gameSettingsView.value &= ~0x10000000;
    } else {
        g_gameSettingsView.value |= 0x10000000;
    }
    if (SmpButton_GetListSelection(g_extraOptionsScreen->buttons[2]) == 0) {
        g_gameSettingsView.value &= ~0x8;
    } else {
        g_gameSettingsView.value |= 0x8;
    }
    if (SmpButton_GetListSelection(g_extraOptionsScreen->buttons[3]) == 0) {
        g_gameSettingsView.value &= ~0x20000000;
    } else {
        g_gameSettingsView.value |= 0x20000000;
    }
}

void Menu_RefreshExtraOptionLocks(void) {
    s32 total;
    s32 i;

    total = 0;
    for (i = 0; i < 4; i++) {
        if (g_profileSlotIndices[i * 400] >= 0) {
            total += Achieve_CountEarnedAchievements(i);
        }
    }
    if (g_extraOptionsScreen->full == 1) {
        total = 40;
    }
    Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(g_extraOptionsScreen->window, k_extraOptionLockAtTotal6), 1);
    Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(g_extraOptionsScreen->window, k_extraOptionLockAtTotal10), 1);
    Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(g_extraOptionsScreen->window, k_extraOptionLockAtTotal12), 1);
    Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(g_extraOptionsScreen->window, k_extraOptionLockAtTotal14), 1);
    if (total >= 10) {
        Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(g_extraOptionsScreen->window, k_extraOptionLockAtTotal10), 0);
    }
    if (total >= 6) {
        Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(g_extraOptionsScreen->window, k_extraOptionLockAtTotal6), 0);
    }
    if (total >= 12) {
        Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(g_extraOptionsScreen->window, k_extraOptionLockAtTotal12), 0);
    }
    if (total >= 14) {
        Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(g_extraOptionsScreen->window, k_extraOptionLockAtTotal14), 0);
    }
}

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
            item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, k_keypadKeyWidgetDigit1);
            break;
        case 2:
            item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, k_keypadKeyWidgetDigit2);
            break;
        case 3:
            item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, k_keypadKeyWidgetDigit3);
            break;
        case 4:
            item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, k_keypadKeyWidgetDigit4);
            break;
        case 5:
            item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, k_keypadKeyWidgetDigit5);
            break;
        case 6:
            item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, k_keypadKeyWidgetDigit6);
            break;
        case 7:
            item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, k_keypadKeyWidgetDigit7);
            break;
        case 8:
            item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, k_keypadKeyWidgetDigit8);
            break;
        case 9:
            item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, k_keypadKeyWidgetDigit9);
            break;
        case 0:
        default:
            item = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, k_keypadKeyWidgetDigit0);
            break;
        }
        item->alpha = 150;
        item->word38 = 0;
    }
    Menu_AdvanceTextRows();
}
