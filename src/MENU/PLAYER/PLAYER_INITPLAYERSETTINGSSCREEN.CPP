#include "COMMON/GAMEPLAY_SETTINGS.H"
#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/MENULISTSCREEN.H"
#include "TYPES.H"
#include "MENU/PLAYER_INITPLAYERSETTINGSSCREEN.H"

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
#if defined(VERSION_DE)
#define PLAYER_SETTINGS_ID(id) ((id) - 2)
#else
#define PLAYER_SETTINGS_ID(id) (id)
#endif
extern struct StateMenuSelectPlayerSettingsEntry *g_playerSettingsScreen;
extern char *g_matchOptionsCursorLabelThird[1];
extern char *g_playerSettingsPrimaryListLabels[1];
extern u8 *g_toggleListClearLabel[];
extern char *g_toggleListSetLabel[1];
extern char *g_playerSettingsSecondaryListLabels[1];
extern char *g_playerSettingsFirstChoiceText[1];
extern char *g_playerSettingsSecondChoiceText[1];
extern struct Record *Cache_AllocateMemory(s32 size);
extern void *SmpFade_CreateFadeWidget(s32, s32);
extern void SmpButton_WrapButtonWidget(s32);
extern void *SmpButton_CreateListWidget(s32, s32);
extern void SmpButton_AppendListText(struct MenuListWidget *menu, u8 *text);
extern struct MenuSliderWidget *SmpSlider_CreateSliderWidget(s32 sliderWidgetId, s32 childWidgetId, s32 initialTransition);
extern struct MenuResourceWidget *SmpFlicker_CreateFlickerWidget(int widgetResourceId, int ownerValue);
extern struct MenuWidget *Node_FindWidgetByResourceId(void *root, s32 identifier);
#define ST ((void **)g_playerSettingsScreen)
/* Builds the five player-settings controls and opens their parent screen. */
s32 Player_InitPlayerSettingsScreen(s32 root) {
    g_playerSettingsScreen = (struct StateMenuSelectPlayerSettingsEntry *)Cache_AllocateMemory(100);
    ST[0] = SmpFade_CreateFadeWidget(PLAYER_SETTINGS_ID(91), PLAYER_SETTINGS_ID(92));
    SmpButton_WrapButtonWidget(PLAYER_SETTINGS_ID(94));
    g_playerSettingsScreen->a = SmpButton_CreateListWidget(PLAYER_SETTINGS_ID(100), PLAYER_SETTINGS_ID(101));
    SmpButton_AppendListText(g_playerSettingsScreen->a, g_matchOptionsCursorLabelThird[0]);
    SmpButton_AppendListText(g_playerSettingsScreen->a, g_playerSettingsPrimaryListLabels[0]);
    g_playerSettingsScreen->b = SmpButton_CreateListWidget(PLAYER_SETTINGS_ID(97), PLAYER_SETTINGS_ID(99));
    SmpButton_AppendListText(g_playerSettingsScreen->b, g_toggleListClearLabel[0]);
    SmpButton_AppendListText(g_playerSettingsScreen->b, g_toggleListSetLabel[0]);
    g_playerSettingsScreen->c = SmpSlider_CreateSliderWidget(PLAYER_SETTINGS_ID(102), PLAYER_SETTINGS_ID(103), 248);
    g_playerSettingsScreen->d = SmpSlider_CreateSliderWidget(PLAYER_SETTINGS_ID(106), PLAYER_SETTINGS_ID(107), 248);
    g_playerSettingsScreen->e = SmpButton_CreateListWidget(PLAYER_SETTINGS_ID(104), PLAYER_SETTINGS_ID(105));
    SmpButton_AppendListText(g_playerSettingsScreen->e, g_playerSettingsSecondaryListLabels[0]);
    SmpButton_AppendListText(g_playerSettingsScreen->e, g_playerSettingsFirstChoiceText[0]);
    SmpButton_AppendListText(g_playerSettingsScreen->e, g_playerSettingsSecondChoiceText[0]);
    SmpButton_WrapButtonWidget(PLAYER_SETTINGS_ID(96));
    ST[1] = SmpFlicker_CreateFlickerWidget(PLAYER_SETTINGS_ID(93), 110);
    ((s32 *)g_playerSettingsScreen)[9] = 3;
    ((s32 *)g_playerSettingsScreen)[8] = -1;
    ST[11] = Node_FindWidgetByResourceId(root, PLAYER_SETTINGS_ID(95));
    ((s32 *)g_playerSettingsScreen)[10] = 0;
    Player_SelectPlayerSettingsEntry(0);
    return 0;
}
#undef ST
#undef PLAYER_SETTINGS_ID
#else
#include "TYPES.H"
#if defined(VERSION_EU_X)
#define EU_ID(eu, eux) (eux)
#else
#define EU_ID(eu, eux) (eu)
#endif
extern struct StateMenuSelectPlayerSettingsEntry *g_playerSettingsScreen;
extern char *g_matchOptionsCursorLabelThirdByLanguage[];
extern char *g_alternateSettingsModeLabels[];
extern u8 *g_optionsFirstChoiceLabels[];
extern char *g_alternateSettingsControlLabels[];
extern char *g_alternateSettingsHandLabels[];
extern char *g_alternateSettingsFinalChoiceLabelsEu[];
extern char *g_alternateSettingsFinalChoiceLabelsEuX[];
extern struct Record *Cache_AllocateMemory(s32 size);
extern void *SmpFade_CreateFadeWidget(s32, s32);
extern void SmpButton_WrapButtonWidget(s32);
extern void *SmpButton_CreateListWidget(s32, s32);
extern void SmpButton_AppendListText(struct MenuListWidget *menu, u8 *text);
extern struct MenuSliderWidget *SmpSlider_CreateSliderWidget(s32 sliderWidgetId, s32 childWidgetId, s32 initialTransition);
extern struct MenuResourceWidget *SmpFlicker_CreateFlickerWidget(int widgetResourceId, int ownerValue);
extern struct MenuWidget *Node_FindWidgetByResourceId(void *root, s32 identifier);
#define ST ((void **)g_playerSettingsScreen)
/* Builds the five player-settings controls (labels picked by the current language) and opens their parent screen. */
s32 Player_InitPlayerSettingsScreen(s32 root) {
    u8 *settings = (u8 *)&g_gameSettings;
    g_playerSettingsScreen = (struct StateMenuSelectPlayerSettingsEntry *)Cache_AllocateMemory(100);
    ST[0] = SmpFade_CreateFadeWidget(EU_ID(91, 95), EU_ID(92, 96));
    SmpButton_WrapButtonWidget(EU_ID(94, 98));
    g_playerSettingsScreen->a = SmpButton_CreateListWidget(EU_ID(100, 104), EU_ID(101, 105));
    SmpButton_AppendListText(g_playerSettingsScreen->a, g_matchOptionsCursorLabelThirdByLanguage[settings[1409]]);
    SmpButton_AppendListText(g_playerSettingsScreen->a, g_alternateSettingsModeLabels[settings[1409]]);
    g_playerSettingsScreen->b = SmpButton_CreateListWidget(EU_ID(97, 101), EU_ID(99, 102));
    SmpButton_AppendListText(g_playerSettingsScreen->b, g_optionsFirstChoiceLabels[settings[1409]]);
    SmpButton_AppendListText(g_playerSettingsScreen->b, g_alternateSettingsControlLabels[settings[1409]]);
    g_playerSettingsScreen->c = SmpSlider_CreateSliderWidget(EU_ID(102, 106), EU_ID(103, 107), 248);
    g_playerSettingsScreen->d = SmpSlider_CreateSliderWidget(EU_ID(106, 110), EU_ID(107, 111), 248);
    g_playerSettingsScreen->e = SmpButton_CreateListWidget(EU_ID(104, 108), EU_ID(105, 109));
    SmpButton_AppendListText(g_playerSettingsScreen->e, g_alternateSettingsHandLabels[settings[1409]]);
    SmpButton_AppendListText(g_playerSettingsScreen->e, g_alternateSettingsFinalChoiceLabelsEu[settings[1409]]);
    SmpButton_AppendListText(g_playerSettingsScreen->e, g_alternateSettingsFinalChoiceLabelsEuX[settings[1409]]);
    SmpButton_WrapButtonWidget(EU_ID(96, 100));
    ST[1] = SmpFlicker_CreateFlickerWidget(EU_ID(93, 97), 110);
    ((s32 *)g_playerSettingsScreen)[9] = 3;
    ((s32 *)g_playerSettingsScreen)[8] = -1;
    ST[11] = Node_FindWidgetByResourceId(root, EU_ID(95, 99));
    ((s32 *)g_playerSettingsScreen)[10] = 0;
    Player_SelectPlayerSettingsEntry(0);
    return 0;
}
#undef ST
#undef EU_ID
#endif

/* Stores entryIndex into its own g_playerSettingsSlotByteBase entry and pushes the five settings of slot entryIndex of the g_profileSlotSettingsByte7B table into the objects g_playerSettingsScreen holds through SmpButton_SelectListEntry_PlayerInitplayersettingsscreen and SmpSlider_SetSliderItem. */


extern struct StateMenuSelectPlayerSettingsEntry *g_playerSettingsScreen;
extern s8 g_profileSlotSettingsByte7B[];
extern void SmpButton_SelectListEntry(void *, s32);
extern void SmpSlider_SetSliderItem(struct Scroll *scroll, s32 item);

void Player_SelectPlayerSettingsEntry(s32 entryIndex) {
    u8 *slot = &g_gameSettings.playerSettings[entryIndex].slot;

    *slot = entryIndex;
    SmpButton_SelectListEntry(g_playerSettingsScreen->a, g_profileSlotSettingsByte7B[entryIndex * 400]);
    SmpButton_SelectListEntry(g_playerSettingsScreen->b, g_profileSlotSettingsByte7D[entryIndex * 400]);
    SmpSlider_SetSliderItem(g_playerSettingsScreen->c, g_profileSlotSettingsByte79[entryIndex * 400]);
    SmpSlider_SetSliderItem(g_playerSettingsScreen->d, g_profileSlotSettingsByte7A[entryIndex * 400]);
    SmpButton_SelectListEntry(g_playerSettingsScreen->e, g_profileSlotSettingsByte82[entryIndex * 400]);
}

/* Reads five settings from the objects g_playerSettingsScreen holds through SmpButton_GetListSelection and SmpSlider_GetSliderItem into slot entryIndex of the g_profileSlotSettingsByte7B table and copies them into the matching bytes of the entryIndex entry of g_playerSettings_Achieve. */


extern u8 g_playerSettings[];
extern s32 SmpButton_GetListSelection(s32 *record);
extern s32 SmpSlider_GetSliderItem(s32 *record);

void Player_StorePlayerSettingsEntry(s32 entryIndex) {
    u8 *config;

    config = g_playerSettings + entryIndex * sizeof(Shared_PlayerSettingsRecord);
    g_profileSlotSettingsByte7B[entryIndex * 400] = SmpButton_GetListSelection(g_playerSettingsScreen->a);
    do {
        g_profileSlotSettingsByte7D[entryIndex * 400] = SmpButton_GetListSelection(g_playerSettingsScreen->b);
        g_profileSlotSettingsByte79[entryIndex * 400] = SmpSlider_GetSliderItem(g_playerSettingsScreen->c);
        g_profileSlotSettingsByte7A[entryIndex * 400] = SmpSlider_GetSliderItem(g_playerSettingsScreen->d);
        g_profileSlotSettingsByte82[entryIndex * 400] = SmpButton_GetListSelection(g_playerSettingsScreen->e);
    } while (0);
    config[123] = g_profileSlotSettingsByte7B[entryIndex * 400];
    config[125] = g_profileSlotSettingsByte7D[entryIndex * 400];
    config[121] = g_profileSlotSettingsByte79[entryIndex * 400];
    config[122] = g_profileSlotSettingsByte7A[entryIndex * 400];
    config[130] = g_profileSlotSettingsByte82[entryIndex * 400];
}
