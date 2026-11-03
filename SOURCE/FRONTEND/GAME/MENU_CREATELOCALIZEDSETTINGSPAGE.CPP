#include "include_asm.h"
#include "MENU/LOCALIZED_GAME_OPTION_CHOICES.H"
#include "COMMON/FRONTEND_RESOURCE_LOAD_STATE.H"
#include "FRONTEND/NODE_FINDWIDGETBYRESOURCEID.H"
#if defined(VERSION_EU_X)
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "MENU/SCROLL.H"
#include "COMMON/OWNERRECAT8V1.H"
#include "COMMON/MENU_OPTIONS_AND_RESULTS.H"
#include "TYPES.H"
#include "GAME/MENU_CREATELOCALIZEDSETTINGSPAGE.H"
#include "UI/TSMOS/SMP/SMP_BUTTON.H"
#include "UI/TSMOS/SMP/SMP_FADE.H"
extern OptionsCommitContext *g_optionsPage;
/* Per-language label pointer tables, indexed by the settings language byte (0x581). */
extern u8 *g_optionsFirstChoiceLabels[];
extern u8 *g_optionsResolutionFirstChoiceLabels[];
extern u8 *g_optionsResolutionSecondChoiceLabels[];
extern u8 *g_optionsResolutionThirdChoiceLabels[];
extern u8 *g_optionsLocalizedShortcutText[];
extern struct Record *Cache_AllocateMemory(s32 size);
extern s32 Defs_GetMemorySize(void);

extern struct MenuResourceWidget *SmpFlicker_CreateFlickerWidget(s32, s32);

extern void SmpButton_AppendListText(struct MenuListWidget *, u8 *);

extern MenuSliderWidget *SmpSlider_CreateSliderWidget(s32, s32, s32);
extern void SmpSlider_SetSliderItem(Scroll *, s32);
extern MenuWidget *Node_FindWidgetByResourceId(void *, s32);
/* eu-x Options_CreateOptionsPage: the PAL options page with its own resource ids, plus the caption widget
   0x5E whose text is set from the per-language table g_optionsLocalizedShortcutText. */
s32 Menu_CreateLocalizedSettingsPage(void *node) {
    Shared_Game *settings;
    void *firstList;
    void *secondList;
    void *thirdList;
    void *title;
    void *slider;
    g_optionsPage = Cache_AllocateMemory(40);
    g_optionsPage->menu = SmpFade_CreateFadeWidget(79, 80);
    SmpButton_WrapButtonWidget(82);
    SmpButton_WrapButtonWidget(85);
    firstList = SmpButton_CreateListWidget(83, 84);
    settings = &g_gameSettings;
    g_optionsPage->bloodModeList = firstList;
    SmpButton_AppendListText(firstList, g_optionsFirstChoiceLabels[settings->language]);
    SmpButton_AppendListText(g_optionsPage->bloodModeList, g_optionsFirstListChoiceZeroLabels[settings->language]);
    SmpButton_AppendListText(g_optionsPage->bloodModeList, g_optionsFirstListChoiceOneLabels[settings->language]);
    SmpButton_SelectListEntry(g_optionsPage->bloodModeList, settings->bloodMode);
    secondList = SmpButton_CreateListWidget(86, 87);
    g_optionsPage->twoPlayerScreenList = secondList;
    SmpButton_AppendListText(secondList, g_optionsSecondListChoiceZeroLabels[settings->language]);
    SmpButton_AppendListText(g_optionsPage->twoPlayerScreenList, g_optionsSecondListChoiceOneLabels[settings->language]);
    SmpButton_SelectListEntry(g_optionsPage->twoPlayerScreenList, settings->twoPlayerScreenPreference);
    thirdList = SmpButton_CreateListWidget(88, 89);
    g_optionsPage->resolutionList = thirdList;
    SmpButton_AppendListText(thirdList, g_optionsResolutionFirstChoiceLabels[settings->language]);
    if (Defs_GetMemorySize() != 0x400000) {
        SmpButton_AppendListText(g_optionsPage->resolutionList, g_optionsResolutionSecondChoiceLabels[settings->language]);
        SmpButton_AppendListText(g_optionsPage->resolutionList, g_optionsResolutionThirdChoiceLabels[settings->language]);
    }
    SmpButton_SelectListEntry(g_optionsPage->resolutionList, settings->resolution);
    slider = SmpSlider_CreateSliderWidget(90, 91, 128);
    g_optionsPage->gammaSlider = slider;
    SmpSlider_SetSliderItem(slider, settings->lightingGamma);
    SmpButton_WrapButtonWidget(93);
    Node_FindWidgetByResourceId(node, 94)->text = g_optionsLocalizedShortcutText[settings->language];
    SmpButton_WrapButtonWidget(92);
    title = SmpFlicker_CreateFlickerWidget(81, 110);
    g_optionsPage->state = 3;
    g_optionsPage->title = title;
    g_optionsPage->value = -1;
    return 0;
}
#endif
#if defined(VERSION_EU)
#include "COMMON/REQUESTRECAT10.H"
extern struct Record *Cache_AllocateMemory(s32 size);
#endif
