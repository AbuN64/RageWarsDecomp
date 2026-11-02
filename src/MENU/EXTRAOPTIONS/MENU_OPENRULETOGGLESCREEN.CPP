#include "include_asm.h"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SELECTIONSCREENSTATE.H"
#include "TYPES.H"
#include "MENU/MENU_REFRESHEXTRAOPTIONLOCKS.H"
#include "COMMON/SHARED_GAMESLOT.H"
#define g_gameSettingsView (*(s32 *)&g_gameSettings)

/* Opens the options screen: allocates its 0x3C-byte state into g_extraOptionsScreen for window window, builds
   its title, heading and the four toggle buttons 0x3B4, 0x3B1, 0x3AD and 0x3AF set from bits of
   g_gameSettings, creates the item list and refreshes the limit markers through Menu_RefreshExtraOptionLocks. */

extern struct OptionsOpenScreen *g_extraOptionsScreen;
#if defined(VERSION_EU) || defined(VERSION_EU_X)
/* Per-language label pointer tables, indexed by the settings language byte (0x581). */
extern u8 *g_optionsFirstChoiceLabels[];
extern char *g_alternateSettingsControlLabels[];
#define SETTINGS_DECL Shared_Game *settings;
#define SETTINGS_INIT settings = &g_gameSettingsView;
#define SETTINGS_FLAGS (*(s32 *) settings)
#define LABEL0 g_optionsFirstChoiceLabels[settings->language]
#define LABEL1 g_alternateSettingsControlLabels[settings->language]
#else
#define SETTINGS_DECL
#define SETTINGS_INIT
#define SETTINGS_FLAGS g_gameSettingsView
#define LABEL0 g_toggleListClearLabel[0]
#define LABEL1 g_toggleListSetLabel[0]
#endif

/* The hub spells the allocator, the window item lookup and the list builder; these helpers stay. */
extern void *SmpFade_CreateFadeWidget(s32, s32);
extern void *SmpButton_CreateListWidget(s32, s32);
extern void SmpButton_AppendListText(struct MenuListWidget *menu, u8 *text);
extern void SmpButton_SelectListEntry(void *, s32);

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
    /* the hub's item type carries no color; this unit's options view names the byte at +0x1A */
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
