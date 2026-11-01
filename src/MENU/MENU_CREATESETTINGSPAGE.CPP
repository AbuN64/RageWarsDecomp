#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/GAME_SESSION.H"
#include "MENU.H"

#if defined(VERSION_DE)
#include "SYSTEM/SOUND_CONTEXT_MUSIC_AND_VOICE_CONTROL.H"
#include "MENU/SCROLL.H"
#include "COMMON/OWNERRECAT8V1.H"
#include "COMMON/MENU_OPTIONS_AND_RESULTS.H"
#include "TYPES.H"
struct MenuFadeWidget;
struct MenuResourceWidget;
extern struct MenuResourceWidget *SmpFlicker_CreateFlickerWidget(s32, s32);
extern OptionsCommitContext *g_optionsPage;
/* Localized label pointers for the two option lists (rev1 g_optionsSecondListPrimaryLabelsUsRev1..B0, g_optionsResolutionFirstChoiceLabels..213C). */
extern u8 *g_optionsSecondListPrimaryLabels[1];
extern u8 *g_optionsSecondListSecondaryLabels;
extern u8 *g_optionsSecondListTertiaryLabels;
extern struct Record *Cache_AllocateMemory(s32 size);
extern struct MenuFadeWidget *SmpFade_CreateFadeWidget(s32, s32);
extern s32 Defs_GetMemorySize(void);
extern MenuListWidget *SmpButton_CreateListWidget(s32, s32);
extern void SmpButton_AppendListText(struct MenuListWidget *, u8 *);
extern void SmpButton_SelectListEntry(struct MenuListWidget *, s32);
extern MenuSliderWidget *SmpSlider_CreateSliderWidget(s32, s32, s32);
extern void SmpSlider_SetSliderItem(Scroll *, s32);
/* German Options_CreateOptionsPage: the same options-commit page without the first (blood) list, so the
   lists 0x51/0x52 and 0x53/0x54 fill twoPlayerScreenList and resolutionList and the slider is 0x55/0x56. */
s32 Menu_CreateSettingsPage(void) {
    Shared_Game *settings;
    void *secondList;
    void *thirdList;
    void *title;
    void *slider;
    g_optionsPage = Cache_AllocateMemory(40);
    g_optionsPage->menu = SmpFade_CreateFadeWidget(77, 78);
    SmpButton_WrapButtonWidget(87);
    SmpButton_WrapButtonWidget(88);
    secondList = SmpButton_CreateListWidget(81, 82);
    g_optionsPage->twoPlayerScreenList = secondList;
    SmpButton_AppendListText(secondList, g_settingsPagePrimaryLocalizedLabels[0]);
    SmpButton_AppendListText(g_optionsPage->twoPlayerScreenList, g_settingsPageSecondaryLocalizedLabels);
    settings = &g_gameSettings;
    SmpButton_SelectListEntry(g_optionsPage->twoPlayerScreenList, settings->twoPlayerScreenPreference);
    thirdList = SmpButton_CreateListWidget(83, 84);
    g_optionsPage->resolutionList = thirdList;
    SmpButton_AppendListText(thirdList, g_optionsSecondListPrimaryLabels[0]);
    if (Defs_GetMemorySize() != 0x400000) {
        SmpButton_AppendListText(g_optionsPage->resolutionList, g_optionsSecondListSecondaryLabels);
        SmpButton_AppendListText(g_optionsPage->resolutionList, g_optionsSecondListTertiaryLabels);
    }
    SmpButton_SelectListEntry(g_optionsPage->resolutionList, settings->resolution);
    slider = SmpSlider_CreateSliderWidget(85, 86, 128);
    g_optionsPage->gammaSlider = slider;
    SmpSlider_SetSliderItem(slider, settings->lightingGamma);
    SmpButton_WrapButtonWidget(80);
    title = SmpFlicker_CreateFlickerWidget(79, 110);
    g_optionsPage->state = 3;
    g_optionsPage->title = title;
    g_optionsPage->value = -1;
    return 0;
}
#endif
