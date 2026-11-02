#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "TYPES.H"
#include "COMMON/SHARED_GAMESLOT.H"
#if defined(VERSION_EU_X)
#define ID(id) ((id) + 4)
#else
#define ID(id) (id)
#endif
typedef struct { void *a0, *a4, *a8, *aC, *a10; s32 a14; void *a18; } MenuBlockEu;
extern MenuBlockEu *g_alternatePlayerSettingsScreen;
extern char *g_matchOptionsCursorLabelThirdByLanguage[];
extern char *g_alternateSettingsModeLabels[];
extern u8 *g_optionsFirstChoiceLabels[];
extern char *g_alternateSettingsControlLabels[];
extern char *g_alternateSettingsHandLabels[];
extern char *g_alternateSettingsFinalChoiceLabelsEu[];
extern char *g_alternateSettingsFinalChoiceLabelsEuX[];
extern struct Record *Cache_AllocateMemory(s32 size);
extern void SmpButton_WrapButtonWidget(s32);
extern void SmpButton_AppendListText(struct MenuListWidget *menu, u8 *text);
extern void *SmpButton_CreateListWidget(s32, s32);
extern struct MenuSliderWidget *SmpSlider_CreateSliderWidget(s32 sliderWidgetId, s32 childWidgetId, s32 initialTransition);
extern struct MenuWidget *Node_FindWidgetByResourceId(void *root, s32 identifier);
extern void Player_SelectAlternatePlayerSettingsEntry(s32);
/* Builds the 0x50-byte confirm popup: its three button rows (ids 0x1C9, 0x1D1, 0x1CB) get the labels of the current language,
   the two fade windows ID(0x1CF)/ID(0x1CD) are created, and item ID(0x1C7) is kept as the cursor. Returns 0. */
s32 Player_OpenAlternatePlayerSettingsScreen(void *window) {
    u8 *settings = (u8 *)&g_gameSettings;
    g_alternatePlayerSettingsScreen = Cache_AllocateMemory(80);
    SmpButton_WrapButtonWidget(ID(454));
    g_alternatePlayerSettingsScreen->aC = SmpButton_CreateListWidget(ID(457), ID(458));
    SmpButton_AppendListText(g_alternatePlayerSettingsScreen->aC, g_matchOptionsCursorLabelThirdByLanguage[settings[1409]]);
    SmpButton_AppendListText(g_alternatePlayerSettingsScreen->aC, g_alternateSettingsModeLabels[settings[1409]]);
    g_alternatePlayerSettingsScreen->a8 = SmpButton_CreateListWidget(ID(465), ID(466));
    SmpButton_AppendListText(g_alternatePlayerSettingsScreen->a8, g_optionsFirstChoiceLabels[settings[1409]]);
    SmpButton_AppendListText(g_alternatePlayerSettingsScreen->a8, g_alternateSettingsControlLabels[settings[1409]]);
    g_alternatePlayerSettingsScreen->a0 = SmpSlider_CreateSliderWidget(ID(463), ID(464), 0xFF);
    g_alternatePlayerSettingsScreen->a4 = SmpSlider_CreateSliderWidget(ID(461), ID(462), 0xFF);
    g_alternatePlayerSettingsScreen->a10 = SmpButton_CreateListWidget(ID(459), ID(460));
    SmpButton_AppendListText(g_alternatePlayerSettingsScreen->a10, g_alternateSettingsHandLabels[settings[1409]]);
    SmpButton_AppendListText(g_alternatePlayerSettingsScreen->a10, g_alternateSettingsFinalChoiceLabelsEu[settings[1409]]);
    SmpButton_AppendListText(g_alternatePlayerSettingsScreen->a10, g_alternateSettingsFinalChoiceLabelsEuX[settings[1409]]);
    SmpButton_WrapButtonWidget(ID(456));
    g_alternatePlayerSettingsScreen->a18 = Node_FindWidgetByResourceId(window, ID(455));
    g_alternatePlayerSettingsScreen->a14 = 0;
    Player_SelectAlternatePlayerSettingsEntry(0);
    return 0;
}
#undef ID
#endif
