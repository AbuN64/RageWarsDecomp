#include "COMMON/OWNERRECAT8V1.H"
#include "COMMON/MENULISTSCREEN.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "MENU/PLAYER_STOREALTERNATEPLAYERSETTINGSENTRY.H"
#include "UI/TSMOS/SMP/SMP_BUTTON.H"

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
/* Builds screen state g_alternatePlayerSettingsScreen under a parent window: allocates its 0x50 bytes, opens lists 0x1C9, 0x1D1 and 0x1CB filled with the entries in D_800D74xx at 0x0C, 0x08 and 0x10, opens panels 0x1CF and 0x1CD at 0x0 and 0x4, opens window 0x1C7 at 0x18, clears the word at 0x14, resets through Player_SelectAlternatePlayerSettingsEntry(0) and returns zero.
   Adapted from SmpOverlay_CreatePakDialog with the window openings changed to the list, panel and window calls of this screen and the list entry words declared as arrays. */

extern MenuListScreen *g_alternatePlayerSettingsScreen;
extern struct Record *Cache_AllocateMemory(s32 size);


extern void SmpButton_AppendListText(struct MenuListWidget *menu, u8 *text);
extern struct MenuSliderWidget *SmpSlider_CreateSliderWidget(s32 sliderWidgetId, s32 childWidgetId, s32 initialTransition);
extern struct MenuWidget *Node_FindWidgetByResourceId(void *root, s32 identifier);

#if defined(VERSION_DE)
enum { k_altPlayerSettingsButtonFirstWrapId = 450, k_altPlayerSettingsWindowWidgetId = 451, k_altPlayerSettingsButtonSecondWrapId = 452, k_altPlayerSettingsListAFirstId = 453, k_altPlayerSettingsListASecondId = 454, k_altPlayerSettingsListCFirstId = 455, k_altPlayerSettingsListCSecondId = 456, k_altPlayerSettingsSliderBFirstId = 457, k_altPlayerSettingsSliderBSecondId = 458, k_altPlayerSettingsSliderAFirstId = 459, k_altPlayerSettingsSliderASecondId = 460, k_altPlayerSettingsListBFirstId = 461, k_altPlayerSettingsListBSecondId = 462 };
#else
enum { k_altPlayerSettingsButtonFirstWrapId = 454, k_altPlayerSettingsWindowWidgetId = 455, k_altPlayerSettingsButtonSecondWrapId = 456, k_altPlayerSettingsListAFirstId = 457, k_altPlayerSettingsListASecondId = 458, k_altPlayerSettingsListCFirstId = 459, k_altPlayerSettingsListCSecondId = 460, k_altPlayerSettingsSliderBFirstId = 461, k_altPlayerSettingsSliderBSecondId = 462, k_altPlayerSettingsSliderAFirstId = 463, k_altPlayerSettingsSliderASecondId = 464, k_altPlayerSettingsListBFirstId = 465, k_altPlayerSettingsListBSecondId = 466 };
#endif

s32 Player_BuildItemLabelList(void *parent) {
    void *list;

    g_alternatePlayerSettingsScreen = Cache_AllocateMemory(80);
    SmpButton_WrapButtonWidget(k_altPlayerSettingsButtonFirstWrapId);
    list = SmpButton_CreateListWidget(k_altPlayerSettingsListAFirstId, k_altPlayerSettingsListASecondId);
    g_alternatePlayerSettingsScreen->listA = list;
    SmpButton_AppendListText(list, g_matchOptionsCursorLabelThird[0]);
    SmpButton_AppendListText(g_alternatePlayerSettingsScreen->listA, g_playerSettingsPrimaryListLabels[0]);
    list = SmpButton_CreateListWidget(k_altPlayerSettingsListBFirstId, k_altPlayerSettingsListBSecondId);
    g_alternatePlayerSettingsScreen->listB = list;
    SmpButton_AppendListText(list, g_toggleListClearLabel[0]);
    SmpButton_AppendListText(g_alternatePlayerSettingsScreen->listB, g_toggleListSetLabel[0]);
    g_alternatePlayerSettingsScreen->panels[0] = SmpSlider_CreateSliderWidget(k_altPlayerSettingsSliderAFirstId, k_altPlayerSettingsSliderASecondId, 0xFF);
    g_alternatePlayerSettingsScreen->panels[1] = SmpSlider_CreateSliderWidget(k_altPlayerSettingsSliderBFirstId, k_altPlayerSettingsSliderBSecondId, 0xFF);
    list = SmpButton_CreateListWidget(k_altPlayerSettingsListCFirstId, k_altPlayerSettingsListCSecondId);
    g_alternatePlayerSettingsScreen->listC = list;
    SmpButton_AppendListText(list, g_playerSettingsSecondaryListLabels[0]);
    SmpButton_AppendListText(g_alternatePlayerSettingsScreen->listC, g_playerSettingsFirstChoiceText[0]);
    SmpButton_AppendListText(g_alternatePlayerSettingsScreen->listC, g_playerSettingsSecondChoiceText[0]);
    SmpButton_WrapButtonWidget(k_altPlayerSettingsButtonSecondWrapId);
    g_alternatePlayerSettingsScreen->window = Node_FindWidgetByResourceId(parent, k_altPlayerSettingsWindowWidgetId);
    g_alternatePlayerSettingsScreen->selection = 0;
    Player_SelectAlternatePlayerSettingsEntry(0);
    return 0;
}
#endif
