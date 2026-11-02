#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/GAME_SESSION.H"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "SYSTEM/SOUND_CONTEXT_MUSIC_AND_VOICE_CONTROL.H"
#include "COMMON/MENU_INITIALIZEOPTIONSSCENE.H"
#include "MENU/LOCALIZED_GAME_OPTION_CHOICES.H"

/* 80408AC4_21.CPP */
#if defined(VERSION_DE)
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/ITEMRECAT20V1.H"
extern ResidentEventHandlerEntry g_joinOptionsEventHandlers[];

s32 Menu_DispatchGermanJoinOptionsEvent(MenuWidget *pThis, s32 event, s32 eventData, s32 eventValue, s32 eventContext) {
    s32 i;
    for (i = 0; g_joinOptionsEventHandlers[i].handler != 0; i++) {
        if (g_joinOptionsEventHandlers[i].event == event &&
            (g_joinOptionsEventHandlers[i].actorKind == pThis->resource || g_joinOptionsEventHandlers[i].actorKind == 30000)) {
            return g_joinOptionsEventHandlers[i].handler(pThis, event, eventData, eventValue, eventContext);
        }
    }
    return 0;
}
#endif


/* 80408CB0_28.CPP */
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "MENU/SCROLL.H"
#include "COMMON/OWNERRECAT8V1.H"
#include "COMMON/MENU_OPTIONS_AND_RESULTS.H"
#include "TYPES.H"
struct MenuFadeWidget;
struct MenuResourceWidget;
/* Per-language label pointer tables, indexed by the settings language byte (0x581). */
extern u8 *g_optionsFirstChoiceLabels[];
extern u8 *g_optionsResolutionFirstChoiceLabels[];
extern u8 *g_optionsResolutionSecondChoiceLabels[];
extern u8 *g_optionsResolutionThirdChoiceLabels[];
extern struct Record *Cache_AllocateMemory(s32 size);
extern s32 Defs_GetMemorySize(void);
extern struct MenuFadeWidget *SmpFade_CreateFadeWidget(s32, s32);
extern struct MenuResourceWidget *SmpFlicker_CreateFlickerWidget(s32, s32);
extern MenuListWidget *SmpButton_CreateListWidget(s32, s32);
extern void SmpButton_AppendListText(struct MenuListWidget *, u8 *);
extern void SmpButton_SelectListEntry(struct MenuListWidget *, s32);
extern MenuSliderWidget *SmpSlider_CreateSliderWidget(s32, s32, s32);
extern void SmpSlider_SetSliderItem(Scroll *, s32);
extern void Tsmos_DeactivateControllerState(void);
#endif

#if defined(VERSION_EU)
extern OptionsCommitContext *g_optionsPage;
/* PAL Options_CreateOptionsPage: the three option lists take their labels from the per-language tables
   indexed by settings->language. */
s32 Menu_CreateEuropeanSettingsPage(void) {
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
    settings = &g_gameSettings;
    g_optionsPage->bloodModeList = firstList;
    SmpButton_AppendListText(firstList, g_optionsFirstChoiceLabels[settings->language]);
    SmpButton_AppendListText(g_optionsPage->bloodModeList, g_optionsFirstListChoiceZeroLabels[settings->language]);
    SmpButton_AppendListText(g_optionsPage->bloodModeList, g_optionsFirstListChoiceOneLabels[settings->language]);
    SmpButton_SelectListEntry(g_optionsPage->bloodModeList, settings->bloodMode);
    secondList = SmpButton_CreateListWidget(85, 86);
    g_optionsPage->twoPlayerScreenList = secondList;
    SmpButton_AppendListText(secondList, g_optionsSecondListChoiceZeroLabels[settings->language]);
    SmpButton_AppendListText(g_optionsPage->twoPlayerScreenList, g_optionsSecondListChoiceOneLabels[settings->language]);
    SmpButton_SelectListEntry(g_optionsPage->twoPlayerScreenList, settings->twoPlayerScreenPreference);
    thirdList = SmpButton_CreateListWidget(81, 82);
    g_optionsPage->resolutionList = thirdList;
    SmpButton_AppendListText(thirdList, g_optionsResolutionFirstChoiceLabels[settings->language]);
    if (Defs_GetMemorySize() != 0x400000) {
        SmpButton_AppendListText(g_optionsPage->resolutionList, g_optionsResolutionSecondChoiceLabels[settings->language]);
        SmpButton_AppendListText(g_optionsPage->resolutionList, g_optionsResolutionThirdChoiceLabels[settings->language]);
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
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)
#if defined(VERSION_EU_X)
#define MENU_RESOURCE_ID(id) ((id) + 4)
#else
#define MENU_RESOURCE_ID(id) (id)
#endif
/* Game-options screen state (0x10 bytes, rev1 SliderScreen in FRONTEND/80423280_30.CPP). */
typedef struct GameOptionsScreen {
    void *slider;
    void *firstList;
    void *secondList;
    s32 state;
} GameOptionsScreen;
extern struct CompactOptionsCommitContext *g_gameOptionsScreenState;
/* PAL Frontend_CreateGameOptionsScreen: the list labels come from the per-language tables. */
s32 Menu_CreateSessionSettingsControls(void) {
    Shared_Game *settings;
    void *firstList;
    void *secondList;
    void *slider;

    g_gameOptionsScreenState = Cache_AllocateMemory(16);
    SmpButton_WrapButtonWidget(MENU_RESOURCE_ID(445));
    SmpButton_WrapButtonWidget(MENU_RESOURCE_ID(450));
    firstList = SmpButton_CreateListWidget(MENU_RESOURCE_ID(443), MENU_RESOURCE_ID(444));
    settings = &g_gameSettings;
    g_gameOptionsScreenState->firstList = firstList;
    SmpButton_AppendListText(firstList, g_optionsFirstChoiceLabels[settings->language]);
    SmpButton_AppendListText(g_gameOptionsScreenState->firstList, g_optionsFirstListChoiceZeroLabels[settings->language]);
    SmpButton_AppendListText(g_gameOptionsScreenState->firstList, g_optionsFirstListChoiceOneLabels[settings->language]);
    SmpButton_SelectListEntry(g_gameOptionsScreenState->firstList, settings->bloodMode);
    secondList = SmpButton_CreateListWidget(MENU_RESOURCE_ID(446), MENU_RESOURCE_ID(447));
    g_gameOptionsScreenState->secondList = secondList;
    SmpButton_AppendListText(secondList, g_optionsResolutionFirstChoiceLabels[settings->language]);
    if (Defs_GetMemorySize() != 0x400000) {
        SmpButton_AppendListText(g_gameOptionsScreenState->secondList, g_optionsResolutionSecondChoiceLabels[settings->language]);
        SmpButton_AppendListText(g_gameOptionsScreenState->secondList, g_optionsResolutionThirdChoiceLabels[settings->language]);
    }
    SmpButton_SelectListEntry(g_gameOptionsScreenState->secondList, settings->resolution);
    slider = SmpSlider_CreateSliderWidget(MENU_RESOURCE_ID(448), MENU_RESOURCE_ID(449), 128);
    g_gameOptionsScreenState->slider = slider;
    SmpSlider_SetSliderItem(slider, settings->lightingGamma);
    SmpButton_WrapButtonWidget(MENU_RESOURCE_ID(451));
    SmpButton_WrapButtonWidget(MENU_RESOURCE_ID(452));
    g_gameOptionsScreenState->state = 0;
    Tsmos_DeactivateControllerState();
    return 0;
}
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)
#include "COMMON/SHARED_OPTIONSSCREEN.H"
extern Shared_OptionsScreen *g_optionsShortcutScreen;
extern Shared_MenuReply g_selectionMessageReply;
extern MenuWidget *Node_FindWidgetByResourceId(void *, s32);
extern void Widget_SetWidgetFlag08(void *, s32);
extern void Widget_SetWidgetFlag100(void *, s32);
extern void Frontend_InitMenuImage(s32 *record, s32 first, s32 second, s32 third, s32 fourth);
extern void Frontend_StartMenuImageTransition(s32 *record);
/* PAL Options_OpenOptionsScreen: the list labels come from the per-language tables. */
s32 Menu_OpenLocalizedGameOptions(void *node) {
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
    g_optionsShortcutScreen->leftTab = Node_FindWidgetByResourceId(node, MENU_RESOURCE_ID(897));
    g_optionsShortcutScreen->leftTab->x -= g_optionsShortcutScreen->leftTab->width;
    g_optionsShortcutScreen->leftStep = g_optionsShortcutScreen->leftTab->width / 4;
    rem = g_optionsShortcutScreen->leftTab->width - g_optionsShortcutScreen->leftStep * 4;
    g_optionsShortcutScreen->leftTab->x += rem;
    g_optionsShortcutScreen->rightTab = Node_FindWidgetByResourceId(node, MENU_RESOURCE_ID(904));
    g_optionsShortcutScreen->rightTab->x += g_optionsShortcutScreen->rightTab->width;
    g_optionsShortcutScreen->rightStep = g_optionsShortcutScreen->rightTab->width / 4;
    rem = g_optionsShortcutScreen->rightTab->width - g_optionsShortcutScreen->rightStep * 4;
    g_optionsShortcutScreen->rightTab->x -= rem;
    g_optionsShortcutScreen->title = SmpFlicker_CreateFlickerWidget(MENU_RESOURCE_ID(883), 110);
    marker = Node_FindWidgetByResourceId(node, MENU_RESOURCE_ID(882));
    g_optionsShortcutScreen->marker = marker;
    Widget_SetWidgetFlag08(marker, 0);
    (Node_FindWidgetByResourceId(node, MENU_RESOURCE_ID(902)))->alpha = 110;
    header = Node_FindWidgetByResourceId(node, MENU_RESOURCE_ID(903));
    g_optionsShortcutScreen->header = header;
    header->alpha = 140;
    g_optionsShortcutScreen->footer = Node_FindWidgetByResourceId(node, MENU_RESOURCE_ID(880));
    rumble = Node_FindWidgetByResourceId(node, MENU_RESOURCE_ID(900));
    g_optionsShortcutScreen->rumbleIcon = rumble;
    Widget_SetWidgetFlag08(rumble, 1);
    (Node_FindWidgetByResourceId(node, MENU_RESOURCE_ID(901)))->alpha = 110;
    pak = Node_FindWidgetByResourceId(node, MENU_RESOURCE_ID(884));
    g_optionsShortcutScreen->pakIcon = pak;
    Widget_SetWidgetFlag08(pak, 0);
    SmpButton_WrapButtonWidget(MENU_RESOURCE_ID(887));
    SmpButton_WrapButtonWidget(MENU_RESOURCE_ID(892));
    firstListHandle = SmpButton_CreateListWidget(MENU_RESOURCE_ID(885), MENU_RESOURCE_ID(886));
    g_optionsShortcutScreen->firstList = firstListHandle;
    settings = &g_gameSettings;
    SmpButton_AppendListText(firstListHandle, g_optionsFirstChoiceLabels[settings->language]);
    SmpButton_AppendListText(g_optionsShortcutScreen->firstList, g_optionsFirstListChoiceZeroLabels[settings->language]);
    SmpButton_AppendListText(g_optionsShortcutScreen->firstList, g_optionsFirstListChoiceOneLabels[settings->language]);
    SmpButton_SelectListEntry(g_optionsShortcutScreen->firstList, settings->bloodMode);
    secondListHandle = SmpButton_CreateListWidget(MENU_RESOURCE_ID(888), MENU_RESOURCE_ID(889));
    g_optionsShortcutScreen->secondList = secondListHandle;
    SmpButton_AppendListText(secondListHandle, g_optionsResolutionFirstChoiceLabels[settings->language]);
    if (Defs_GetMemorySize() != 0x400000) {
        SmpButton_AppendListText(g_optionsShortcutScreen->secondList, g_optionsResolutionSecondChoiceLabels[settings->language]);
        SmpButton_AppendListText(g_optionsShortcutScreen->secondList, g_optionsResolutionThirdChoiceLabels[settings->language]);
    }
    SmpButton_SelectListEntry(g_optionsShortcutScreen->secondList, settings->slots[7].secondListMode);
    slider = SmpSlider_CreateSliderWidget(MENU_RESOURCE_ID(890), MENU_RESOURCE_ID(891), 128);
    g_optionsShortcutScreen->slider = slider;

    SmpSlider_SetSliderItem(slider, settings->lightingGamma);
    switch (settings->controllerMode) {
    case 0:
        if (ScenarioSetup_IsCupSelected() == 0) {
            Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(node, MENU_RESOURCE_ID(894)), 1);
        }
        handle = Node_FindWidgetByResourceId(node, MENU_RESOURCE_ID(896));
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
        handle = Node_FindWidgetByResourceId(node, MENU_RESOURCE_ID(896));
        Widget_SetWidgetFlag100(handle, 1);
        Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(node, MENU_RESOURCE_ID(894)), 1);
        break;
    }
    SmpButton_WrapButtonWidget(MENU_RESOURCE_ID(896));
    SmpButton_WrapButtonWidget(MENU_RESOURCE_ID(893));
    SmpButton_WrapButtonWidget(MENU_RESOURCE_ID(894));
    SmpButton_WrapButtonWidget(MENU_RESOURCE_ID(895));
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
    prompt = Node_FindWidgetByResourceId(node, MENU_RESOURCE_ID(881));
    g_optionsShortcutScreen->prompt = prompt;
    Widget_SetWidgetFlag08(prompt, 1);
    return 0;
}
#endif
