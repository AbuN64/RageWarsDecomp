#include "FRONTEND/NODE_FINDWIDGETBYRESOURCEID.H"
#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/GAME_SESSION.H"
#include "SYSTEM/SOUND_CONTEXT_MUSIC_AND_VOICE_CONTROL.H"
#include "COMMON/MENU_INITIALIZEOPTIONSSCENE.H"
#include "OPTIONS.H"
#if defined(VERSION_US) || defined(VERSION_US_REV1)
#include "MENU/SCROLL.H"
#include "COMMON/OWNERRECAT8V1.H"
#include "COMMON/MENU_OPTIONS_AND_RESULTS.H"
#include "TYPES.H"
extern struct MenuResourceWidget *SmpFlicker_CreateFlickerWidget(s32, s32);
#include "COMMON/SHARED_GAMESLOT.H"
extern void *Cache_AllocateMemory(s32);
extern s32 Defs_GetMemorySize(void);
extern MenuListWidget *SmpButton_CreateListWidget(s32, s32);
extern void SmpButton_AppendListText(struct MenuListWidget *, u8 *);
extern void SmpButton_SelectListEntry(struct MenuListWidget *, s32);
extern MenuSliderWidget *SmpSlider_CreateSliderWidget(s32, s32, s32);
extern void SmpSlider_SetSliderItem(Scroll *, s32);
#include "TYPES.H"
#include "COMMON/SHARED_OPTIONSSCREEN.H"
extern Shared_OptionsScreen *g_optionsShortcutScreen;
extern Shared_MenuReply g_selectionMessageReply;
extern void Widget_SetWidgetFlag08(void *, s32);
extern void Widget_SetWidgetFlag100(void *, s32);
extern void Tsmos_DeactivateControllerState(void);
extern void Frontend_InitMenuImage(Shared_OptionsScreen *, s32, s32, s32, s32);
extern void Frontend_StartMenuImageTransition(Shared_OptionsScreen *);
#endif
#if defined(VERSION_DE)
#include "SYSTEM/SOUND_CONTEXT_MUSIC_AND_VOICE_CONTROL.H"
#include "MENU/SCROLL.H"
#include "TYPES.H"
#include "COMMON/SHARED_OPTIONSSCREEN.H"
extern struct MenuResourceWidget *SmpFlicker_CreateFlickerWidget(s32, s32);
extern Shared_OptionsScreen *g_optionsShortcutScreen;
extern Shared_MenuReply g_selectionMessageReply;
/* Localized label pointers for the memory-mode list (rev1 g_optionsResolutionFirstChoiceLabels..g_optionsResolutionThirdChoiceLabels). */
extern u8 *g_optionsSecondListPrimaryLabels[1];
extern u8 *g_optionsSecondListSecondaryLabels;
extern u8 *g_optionsSecondListTertiaryLabels;
extern struct Record *Cache_AllocateMemory(s32 size);
extern void Widget_SetWidgetFlag08(void *, s32);
extern void Widget_SetWidgetFlag100(void *, s32);
extern s32 Defs_GetMemorySize(void);
extern MenuListWidget *SmpButton_CreateListWidget(s32, s32);
extern void SmpButton_AppendListText(struct MenuListWidget *, u8 *);
extern void SmpButton_SelectListEntry(struct MenuListWidget *, s32);
extern MenuSliderWidget *SmpSlider_CreateSliderWidget(s32, s32, s32);
extern void SmpSlider_SetSliderItem(Scroll *, s32);
extern s32 ScenarioSetup_IsCupSelected(void);
extern void Tsmos_DeactivateControllerState(void);
extern void Frontend_InitMenuImage(s32 *record, s32 first, s32 second, s32 third, s32 fourth);
extern void Frontend_StartMenuImageTransition(s32 *record);
/* German Options_OpenOptionsScreen: the same options screen without the first (blood) list; the
   widget resource ids are 6..0x14 lower and settings is first taken after the memory-mode labels. */
s32 Menu_OpenGameOptionsScreen(void *node) {
    Shared_Game *settings;
    MenuWidget *handle;
    MenuWidget *marker;
    MenuWidget *header;
    MenuWidget *rumble;
    MenuWidget *pak;
    MenuWidget *prompt;
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
    g_optionsShortcutScreen->leftTab = Node_FindWidgetByResourceId(node, 891);
    g_optionsShortcutScreen->leftTab->x -= g_optionsShortcutScreen->leftTab->width;
    g_optionsShortcutScreen->leftStep = g_optionsShortcutScreen->leftTab->width / 4;
    rem = g_optionsShortcutScreen->leftTab->width - g_optionsShortcutScreen->leftStep * 4;
    g_optionsShortcutScreen->leftTab->x += rem;
    g_optionsShortcutScreen->rightTab = Node_FindWidgetByResourceId(node, 898);
    g_optionsShortcutScreen->rightTab->x += g_optionsShortcutScreen->rightTab->width;
    g_optionsShortcutScreen->rightStep = g_optionsShortcutScreen->rightTab->width / 4;
    rem = g_optionsShortcutScreen->rightTab->width - g_optionsShortcutScreen->rightStep * 4;
    g_optionsShortcutScreen->rightTab->x -= rem;
    g_optionsShortcutScreen->title = SmpFlicker_CreateFlickerWidget(879, 110);
    marker = Node_FindWidgetByResourceId(node, 878);
    g_optionsShortcutScreen->marker = marker;
    Widget_SetWidgetFlag08(marker, 0);
    (Node_FindWidgetByResourceId(node, 896))->alpha = 110;
    header = Node_FindWidgetByResourceId(node, 897);
    g_optionsShortcutScreen->header = header;
    header->alpha = 140;
    g_optionsShortcutScreen->footer = Node_FindWidgetByResourceId(node, 876);
    rumble = Node_FindWidgetByResourceId(node, 894);
    g_optionsShortcutScreen->rumbleIcon = rumble;
    Widget_SetWidgetFlag08(rumble, 1);
    (Node_FindWidgetByResourceId(node, 895))->alpha = 110;
    pak = Node_FindWidgetByResourceId(node, 880);
    g_optionsShortcutScreen->pakIcon = pak;
    Widget_SetWidgetFlag08(pak, 0);
    SmpButton_WrapButtonWidget(889);
    SmpButton_WrapButtonWidget(890);
    secondListHandle = SmpButton_CreateListWidget(887, 888);
    g_optionsShortcutScreen->secondList = secondListHandle;
    SmpButton_AppendListText(secondListHandle, g_optionsSecondListPrimaryLabels[0]);
    if (Defs_GetMemorySize() != 0x400000) {
        SmpButton_AppendListText(g_optionsShortcutScreen->secondList, g_optionsSecondListSecondaryLabels);
        SmpButton_AppendListText(g_optionsShortcutScreen->secondList, g_optionsSecondListTertiaryLabels);
    }
    settings = &g_gameSettings;
    SmpButton_SelectListEntry(g_optionsShortcutScreen->secondList, settings->slots[7].secondListMode);
    slider = SmpSlider_CreateSliderWidget(881, 882, 128);
    g_optionsShortcutScreen->slider = slider;

    SmpSlider_SetSliderItem(slider, settings->lightingGamma);
    switch (settings->controllerMode) {
    case 0:
        if (ScenarioSetup_IsCupSelected() == 0) {
            Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(node, 884), 1);
        }
        handle = Node_FindWidgetByResourceId(node, 886);
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
        Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(node, 886), 1);
        Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(node, 884), 1);
        break;
    }
    SmpButton_WrapButtonWidget(886);
    SmpButton_WrapButtonWidget(883);
    SmpButton_WrapButtonWidget(884);
    SmpButton_WrapButtonWidget(885);
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
    prompt = Node_FindWidgetByResourceId(node, 877);
    g_optionsShortcutScreen->prompt = prompt;
    Widget_SetWidgetFlag08(prompt, 1);
    return 0;
}
#endif
