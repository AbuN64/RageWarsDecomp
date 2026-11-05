#include "Frontend/node_findwidgetbyresourceid.h"
#include "Common/shared_menureply.h"
#include "include_asm.h"
#include "Common/shared_gameslot.h"
#include "Common/game_session.h"
#include "System/sound_context_music_and_voice_control.h"
#include "Common/menu_initializeoptionsscene.h"
#include "options.h"

#if defined(VERSION_US) || defined(VERSION_US_REV1)
#include "Menu/scroll.h"
#include "Common/menu_overlay.h"
#include "Common/menu_options_and_results.h"
#include "types.h"
#include "Common/shared_gameslot.h"
#include "Data/Gfxdata/audio_decodeframe_data.h"
#include "Ui/Tsmos/Smp/smp_button.h"
#include "Ui/Tsmos/Smp/smp_fade.h"
#include "Common/animation.h"
#include "Common/runtime_declarations.h"
#include "Frontend/game_options_labels.h"
#include "Common/selectionscreenstate.h"
#include "Engine/defs.h"
#include "Frontend/options_list_declarations.h"
#include "Ui/smp_slider.h"
#include "Common/shared_menureply.h"
#include "Frontend/widget_findwidgetatpoint.h"
#include "Frontend/menuimage.h"
#include "options_symbols.h"
/* Localized label pointers supplied to each option list. */
s32 Options_CreateOptionsPage(void) {
    Shared_Game *settings;
    void *firstList;
    void *secondList;
    void *thirdList;
    void *title;
    void *slider;

    g_optionsPage = Cache_AllocateMemory(40);
    g_optionsPage->menu = SmpFade_CreateFadeWidget(77, 78);
    SmpButton_WrapButtonWidget(87);
    SmpButton_WrapButtonWidget(88);
    firstList = SmpButton_CreateListWidget(89, 90);
    g_optionsPage->bloodModeList = firstList;
    SmpButton_AppendListText(firstList, g_toggleListClearLabel[0]);
    SmpButton_AppendListText(g_optionsPage->bloodModeList, g_optionsRedLabel);
    SmpButton_AppendListText(g_optionsPage->bloodModeList, g_optionsGreenLabel);
    settings = &g_gameSettings;
    SmpButton_SelectListEntry(g_optionsPage->bloodModeList, settings->bloodMode);
    secondList = SmpButton_CreateListWidget(85, 86);
    g_optionsPage->twoPlayerScreenList = secondList;
    SmpButton_AppendListText(secondList, g_optionsPrimaryLocalizedLabels[0]);
    SmpButton_AppendListText(g_optionsPage->twoPlayerScreenList, g_optionsSecondaryLocalizedLabels);
    SmpButton_SelectListEntry(g_optionsPage->twoPlayerScreenList, settings->twoPlayerScreenPreference);
    thirdList = SmpButton_CreateListWidget(81, 82);
    g_optionsPage->resolutionList = thirdList;
    SmpButton_AppendListText(thirdList, g_optionsResolutionLoRezChoiceLabels[0]);
    if (Defs_GetMemorySize() != 0x400000) {
        SmpButton_AppendListText(g_optionsPage->resolutionList, g_optionsResolutionHiRezChoiceLabels);
        SmpButton_AppendListText(g_optionsPage->resolutionList, g_optionsResolutionLetterboxChoiceLabels);
    }
    SmpButton_SelectListEntry(g_optionsPage->resolutionList, settings->resolution);
    slider = SmpSlider_CreateSliderWidget(83, 84, 128);
    g_optionsPage->gammaSlider = slider;
    SmpSlider_SetSliderItem(slider, settings->lightingGamma);
    SmpButton_WrapButtonWidget(80);
    title = SmpFlicker_CreateFlickerWidget(79, 110);
    g_optionsPage->state = 3;
    g_optionsPage->title = title;
    g_optionsPage->value = -1;
    return 0;
}
#include "types.h"
#include "Common/shared_optionsscreen.h"
s32 Options_OpenOptionsScreen(void *node) {
    Shared_Game *settings;
    MenuWidget *handle;
    MenuWidget *marker;
    MenuWidget *header;
    MenuWidget *rumble;
    MenuWidget *pak;
    MenuWidget *prompt;
    MenuListWidget *firstListHandle;
    MenuListWidget *secondListHandle;
    void *slider;
    s32 i;
    s32 rem;

    g_optionsShortcutScreen = Cache_AllocateMemory(108);
    g_optionsShortcutScreen->sound = SoundElement_GetMusicPlaybackEnabled();
    SoundElement_SetMusicPlaybackEnabled(52);
    SoundElement_DisableMusicGainOverride();
    SoundElement_StopAudioExceptKey(-1);
    g_optionsShortcutScreen->page = 1;
    g_optionsShortcutScreen->pages = 4;
    g_optionsShortcutScreen->leftTab = Node_FindWidgetByResourceId(node, 897);
    g_optionsShortcutScreen->leftTab->x -= g_optionsShortcutScreen->leftTab->width;
    g_optionsShortcutScreen->leftStep = g_optionsShortcutScreen->leftTab->width / 4;
    rem = g_optionsShortcutScreen->leftTab->width - g_optionsShortcutScreen->leftStep * 4;
    g_optionsShortcutScreen->leftTab->x += rem;
    g_optionsShortcutScreen->rightTab = Node_FindWidgetByResourceId(node, 904);
    g_optionsShortcutScreen->rightTab->x += g_optionsShortcutScreen->rightTab->width;
    g_optionsShortcutScreen->rightStep = g_optionsShortcutScreen->rightTab->width / 4;
    rem = g_optionsShortcutScreen->rightTab->width - g_optionsShortcutScreen->rightStep * 4;
    g_optionsShortcutScreen->rightTab->x -= rem;
    g_optionsShortcutScreen->title = SmpFlicker_CreateFlickerWidget(883, 110);
    marker = Node_FindWidgetByResourceId(node, 882);
    g_optionsShortcutScreen->marker = marker;
    Widget_SetWidgetFlag08(marker, 0);
    (Node_FindWidgetByResourceId(node, 902))->alpha = 110;
    header = Node_FindWidgetByResourceId(node, 903);
    g_optionsShortcutScreen->header = header;
    header->alpha = 140;
    g_optionsShortcutScreen->footer = Node_FindWidgetByResourceId(node, 880);
    rumble = Node_FindWidgetByResourceId(node, 900);
    g_optionsShortcutScreen->rumbleIcon = rumble;
    Widget_SetWidgetFlag08(rumble, 1);
    (Node_FindWidgetByResourceId(node, 901))->alpha = 110;
    pak = Node_FindWidgetByResourceId(node, 884);
    g_optionsShortcutScreen->pakIcon = pak;
    Widget_SetWidgetFlag08(pak, 0);
    SmpButton_WrapButtonWidget(887);
    SmpButton_WrapButtonWidget(892);
    firstListHandle = SmpButton_CreateListWidget(885, 886);
    g_optionsShortcutScreen->firstList = firstListHandle;
    SmpButton_AppendListText(firstListHandle, g_toggleListClearLabel[0]);
    SmpButton_AppendListText(g_optionsShortcutScreen->firstList, g_optionsRedLabel);
    SmpButton_AppendListText(g_optionsShortcutScreen->firstList, g_optionsGreenLabel);
    settings = &g_gameSettings;
    SmpButton_SelectListEntry(g_optionsShortcutScreen->firstList, settings->bloodMode);
    secondListHandle = SmpButton_CreateListWidget(888, 889);
    g_optionsShortcutScreen->secondList = secondListHandle;
    SmpButton_AppendListText(secondListHandle, g_optionsResolutionLoRezChoiceLabels[0]);
    if (Defs_GetMemorySize() != 0x400000) {
        SmpButton_AppendListText(g_optionsShortcutScreen->secondList, g_optionsResolutionHiRezChoiceLabels);
        SmpButton_AppendListText(g_optionsShortcutScreen->secondList, g_optionsResolutionLetterboxChoiceLabels);
    }
    SmpButton_SelectListEntry(g_optionsShortcutScreen->secondList, settings->slots[7].secondListMode);
    slider = SmpSlider_CreateSliderWidget(890, 891, 128);
    g_optionsShortcutScreen->slider = slider;

    SmpSlider_SetSliderItem(slider, settings->lightingGamma);
    switch (settings->controllerMode) {
    case 0:
        if (ScenarioSetup_IsCupSelected() == 0) {
            Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(node, 894), 1);
        }
        handle = Node_FindWidgetByResourceId(node, 896);
        Widget_SetWidgetFlag100(handle, 1);
        for (i = 0; i < 8; i++) {
            if (settings->slots[i].enabled == 1 && settings->slots[i].controller == 1) {
                Widget_SetWidgetFlag100(handle, 0);
                break;
            }
        }
        break;
    case 1:
    case 2:
    case 3:
    case 4:
        Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(node, 896), 1);
        Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(node, 894), 1);
        break;
    }
    SmpButton_WrapButtonWidget(896);
    SmpButton_WrapButtonWidget(893);
    SmpButton_WrapButtonWidget(894);
    SmpButton_WrapButtonWidget(895);
    g_optionsShortcutScreen->state = 0;
    Tsmos_DeactivateControllerState();
    Frontend_InitMenuImage(g_optionsShortcutScreen, 103, 0, 0, 0);
    Frontend_StartMenuImageTransition(g_optionsShortcutScreen);
    g_optionsShortcutScreen->cursor = 0;
    g_optionsShortcutScreen->selection = -1;
    Widget_SetWidgetFlag08(node, 0);
    g_gameSession.clockPaused = 1;
    g_selectionMessageReply.ready = 0;
    g_selectionMessageReply.value = -1;
    Menu_ConfigureOptionsCamera();
    prompt = Node_FindWidgetByResourceId(node, 881);
    g_optionsShortcutScreen->prompt = prompt;
    Widget_SetWidgetFlag08(prompt, 1);
    return 0;
}
#endif
#if defined(VERSION_DE)
#include "System/sound_context_music_and_voice_control.h"
#include "Menu/scroll.h"
#include "types.h"
#include "Common/shared_optionsscreen.h"
#include "Frontend/frontend.h"
#endif
