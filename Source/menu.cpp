#include "Menu/state.h"
#include "Ui/Quag/N64_Eng.h"
#include "Frontend/frontend_openresourcearchive.h"
#include "Frontend/widget_drawtextwidget.h"
#include "include_asm.h"
#include "Menu/localized_game_option_choices.h"
#include "Common/frontend_resource_load_state.h"
#include "Frontend/node_findwidgetbyresourceid.h"
#include "Common/shared_gameslot.h"
#include "Menu/widget_records.h"
#if ((defined(VERSION_EU_X))) || ((defined(VERSION_EU) || defined(VERSION_EU_X))) || ((defined(VERSION_DE)))
#include "Menu/scroll.h"
#endif
#if ((defined(VERSION_EU_X))) || ((defined(VERSION_EU) || defined(VERSION_EU_X))) || ((defined(VERSION_DE)))
#include "Common/menu_overlay.h"
#endif
#include "Common/menu_options_and_results.h"
#include "types.h"
#include "Common/selectionscreenstate.h"
#include "Common/runtime_declarations.h"
#include "Common/shared_menureply.h"
#if ((defined(VERSION_EU)))
#include "Common/player_join_requests.h"
#endif
#if ((defined(VERSION_EU)))
#include "Frontend/smp_overlay.h"
#endif
#if ((defined(VERSION_EU)))
#include "Join/join_cyclejoinrequestrank.h"
#endif
#include "Common/audio_voice_slots.h"
#include "Common/menu_initializeoptionsscene.h"
#include "Render/soundelement_playflatsound.h"
#include "Menu/menu_animatetaboptionsmenu.h"
#include "Common/game_session.h"
#include "Common/Lone/g_languageindex.h"
#include "System/sound_context_music_and_voice_control.h"
#include "Frontend/options_list_declarations.h"
#include "Frontend/menuimage.h"
#include "Common/resident_event_handler.h"
#if ((defined(VERSION_DE)))
#include "Frontend/game_options_labels.h"
#endif
#if ((defined(VERSION_DE)))
#include "Engine/defs.h"
#endif
#if ((defined(VERSION_DE)))
#include "Common/animation.h"
#endif
#include "Ui/smp_slider.h"
#include "Frontend/widget_findwidgetatpoint.h"
#if ((defined(VERSION_DE)))
#include "Menu/menu_openlocalizedgameoptions_symbols.h"
#endif
#if ((defined(VERSION_EU) || defined(VERSION_EU_X)))
#include "Game/frontend_creategameoptionsscreen.h"
#endif
#if ((defined(VERSION_EU) || defined(VERSION_EU_X)))
#include "Menu/menu_openlocalizedgameoptions.h"
#endif
#if ((defined(VERSION_EU) || defined(VERSION_EU_X))) || ((defined(VERSION_DE)))
#include "Ui/Tsmos/Smp/smp_button.h"
#endif
#if ((defined(VERSION_EU) || defined(VERSION_EU_X))) || ((defined(VERSION_DE)))
#include "Ui/Tsmos/Smp/smp_fade.h"
#endif
#include "Common/shared_optionsscreen.h"
#include "Common/screen.h"
#include "Common/characterselectionroot.h"
#include "Scene/cache_freememory.h"
#include "Common/sharedplayer.h"
#include "Common/aiprofile.h"
#include "Menu/selection_dispatchcharacterselectionevent.h"
#include "Menu/character_unlocks.h"
#include "Menu/selection.h"
#include "Frontend/frontend_drawmodelpreview.h"
#include "Common/ballisticparams.h"
#include "Common/gameplay_camera.h"
#include "Rsp/random_direction_and_affine_math.h"
#include "Common/menu_ui_providers.h"
#include "Common/world.h"
#include "Frontend/screen.h"
#include "Frontend/menu_image.h"
#include "Menu/menu_finishtaboptionstransition.h"
#include "Common/track_requesttrackbykey.h"
#include "Ui/Tsmos/TSMOS.h"
#include "Common/statepair.h"
#include "Menu/menu_switchtooptionsscreen.h"
#include "Frontend/menu_commitoptionspage.h"
#include "Ui/smp_button.h"
#include "Menu/menu_commitoptionspage_symbols.h"
#include "menu.h"
#if ((defined(VERSION_DE)))
#include "Menu/menu_createsettingspage.h"
#endif
#if ((defined(VERSION_DE)))
#include "Menu/menu_createsettingspage_symbols.h"
#endif
#include "Menu/menu_destroyoptionspage_symbols.h"
#include "Frontend/frontend.h"

#if defined(VERSION_EU_X)
#endif
#if defined(VERSION_DE)
typedef struct { char pad0[0x14]; char *text; } PakOperationLabelItem;
s32 Menu_SelectPakOperationActionLabel(PakOperationLabelItem *labelItem) {
    switch (g_frontendResourceLoadStage) {
    case 0:
    default:
        labelItem->text = s_nodeDefaultFieldText;
        break;
    case 3:
        labelItem->text = s_nodeDefaultFieldText;
        break;
    case 4:
        labelItem->text = s_nodeDefaultFieldText;
        break;
    case 1:
    case 2:
        labelItem->text = s_nodeAlternateFieldText;
        break;
    }
    return 0;
}
#endif
#if defined(VERSION_EU)

s32 Menu_CreateEuJoinOptions(void *handle) {
    MenuWidget *widget;
    s32 i;
    g_courseOptionsScreen = Cache_AllocateMemory(32);
    g_courseOptionsScreen->handle = handle;
    g_courseOptionsScreen->mode = SmpOverlay_CreateOverlayNode(handle, 4);
    SmpOverlay_ShowSlotById(handle, 0, 905);
    SmpOverlay_ShowSlotById(handle, 1, 905);
    SmpOverlay_ShowSlotById(handle, 2, 905);
    SmpOverlay_ShowSlotById(handle, 3, 905);
    widget = Node_FindWidgetByResourceId(handle, 907);
    widget->alpha = 140;
    if (Menu_GetPreviousScreenOwner(0) == 22) {
        Widget_SetWidgetFlag08(widget, 0);
    }
    g_courseOptionsScreen->timer = 0;
    g_courseOptionsScreen->selection = 0;
    g_courseOptionsScreen->rows[0] = Node_FindWidgetByResourceId(handle, 908);
    g_courseOptionsScreen->rows[1] = Node_FindWidgetByResourceId(handle, 917);
    g_courseOptionsScreen->rows[2] = Node_FindWidgetByResourceId(handle, 918);
    g_courseOptionsScreen->step = Join_CountUsedSlots();
    for (i = 0; i < 3; i++) {
        Join_UpdateJoinRequestDisplay(i);
        Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_courseOptionsScreen->rows[i], 914), 0);
    }
    Tsmos_ActivateControllerState();
    Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_courseOptionsScreen->rows[g_courseOptionsScreen->selection], 914), 1);
    return 0;
}
#endif

#if defined(VERSION_DE)
const unsigned int k_widgetOffsetWord[1] = {
    0x0040DBA0,
};
#endif

/* Resource ids of this screen are numbered per version: de -10, eu-x 4 relative to us. */
static inline s32 tabRes_menuAnimatetaboptionsmenu(s32 id) {
#if defined(VERSION_DE)
    return id - 10;
#elif defined(VERSION_EU_X)
    return id + 4;
#else
    return id;
#endif
}

s32 Menu_AnimateTabOptionsMenu(void) {
    s32 cinemaState;
    s32 transitionState;
    s32 openingFrames;
    s32 closingFrames;
    s32 lastPage;
    s32 pages;
    s32 remainingPages;
    MenuWidget *openingLeftTab;
    MenuWidget *openingRightTab;
    MenuWidget *closingLeftTab;
    MenuWidget *closingRightTab;
    Shared_OptionsScreen *timer;
    Shared_OptionsScreen *finish;
    s32 *ready;

    if (g_selectionMessageStage <= 0) {
        if ((Frontend_GetMenuImageState(g_optionsShortcutScreen) != 1) && ((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->state) == 0)) {
            (((Shared_OptionsScreen *)(g_optionsShortcutScreen))->state) = 1;
            Tsmos_ActivateControllerState();
            return 0;
        }
        cinemaState = g_cinemaSequenceState->state3C;
        if ((cinemaState == 1) && (Cinema_IsSequenceInWindow() == cinemaState)) {
            Widget_SetWidgetFlag08((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->prompt), 0);
            Widget_SetWidgetFlag08((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->footer), 0);
            Widget_SetWidgetFlag08((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->rumbleIcon), 0);
            g_cinemaSequenceState->state3C = 0;
        }
        ready = &g_selectionMessageReply.ready;
        if (*ready == 1) {
            *ready = 0;
            if (g_selectionMessageReply.value != -1) {
                Widget_SetWidgetFlag08((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->pakIcon), 0);
                Widget_SetWidgetFlag08((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->header), 0);
                MarkMenuEventHandled();
                SmXlate_SwitchScreen(g_selectionMessageReply.value);
                return 0;
            }
            Widget_SetWidgetFlag08((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->pakIcon), 1);
            Widget_SetWidgetFlag08((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->header), 1);
            Menu_SetFocusedElement(tabRes_menuAnimatetaboptionsmenu(893));
        }
        transitionState = (((Shared_OptionsScreen *)(g_optionsShortcutScreen))->page);
        switch (transitionState) {
        case 1:
            openingLeftTab = (((Shared_OptionsScreen *)(g_optionsShortcutScreen))->leftTab);
            openingLeftTab->x = (u16) (openingLeftTab->x + (u16)(((Shared_OptionsScreen *)(g_optionsShortcutScreen))->leftStep));
            openingRightTab = (((Shared_OptionsScreen *)(g_optionsShortcutScreen))->rightTab);
            openingRightTab->x = (u16) (openingRightTab->x - (u16)(((Shared_OptionsScreen *)(g_optionsShortcutScreen))->rightStep));
            openingFrames = (((Shared_OptionsScreen *)(g_optionsShortcutScreen))->pages) - 1;
            (((Shared_OptionsScreen *)(g_optionsShortcutScreen))->pages) = openingFrames;
            if (openingFrames <= 0) {
                Widget_SetWidgetFlag08((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->marker), 1);
                Widget_SetWidgetFlag08((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->pakIcon), 1);
                SmpFlicker_StartFlicker((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->title), 4);
                finish = (Shared_OptionsScreen *)g_optionsShortcutScreen;
                finish->page = 4;
                finish->pages = 4;
            }
        case 3:
        default:
            break;
        case 2:
            closingLeftTab = (((Shared_OptionsScreen *)(g_optionsShortcutScreen))->leftTab);
            closingLeftTab->x = (u16) (closingLeftTab->x - (u16)(((Shared_OptionsScreen *)(g_optionsShortcutScreen))->leftStep));
            closingRightTab = (((Shared_OptionsScreen *)(g_optionsShortcutScreen))->rightTab);
            closingRightTab->x = (u16) (closingRightTab->x + (u16)(((Shared_OptionsScreen *)(g_optionsShortcutScreen))->rightStep));
            closingFrames = (((Shared_OptionsScreen *)(g_optionsShortcutScreen))->pages) - 1;
            (((Shared_OptionsScreen *)(g_optionsShortcutScreen))->pages) = closingFrames;
            if (closingFrames <= 0) {
                g_playerViewRenderContext.pause = 0;
                (((Shared_OptionsScreen *)(g_optionsShortcutScreen))->page) = 3;
                Pools_ResetActorPools(&g_playerViewRenderContext.object, 0);
                Player_InitializePlayerPool(&g_playerViewRenderContext, 0, 0);
                Scene_LoadLevelResources(&g_world, 0, 0);
                if (Cache_GetResourceActivityState() == 0) {
                    Cache_SetResourceActivityState(1U);
                }
                g_playerViewRenderContext.stage = 8;
                MarkMenuEventHandled();
                SmXlate_SwitchScreen((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->selection));
                return 0;
            }
            break;
        case 4:
            timer = (Shared_OptionsScreen *)g_optionsShortcutScreen;
            pages = timer->pages;
            lastPage = pages - 1;
            if (lastPage >= 0) {
                remainingPages = pages - (pages >= lastPage);
            } else {
                remainingPages = 0;
            }
            timer->pages = remainingPages;
            if (((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->pages) <= 0) && (SmpFlicker_IsFlickerIdle((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->title)) != 0)) {
                SmpFlicker_RestoreFlickerValue((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->title));
                (((Shared_OptionsScreen *)(g_optionsShortcutScreen))->page) = 3;
            }
            break;
        case 5:
            SoundElement_PlayFlatSound(3704);
            Widget_SetWidgetFlag08((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->marker), 0);
            Widget_SetWidgetFlag08((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->pakIcon), 0);
            Widget_SetWidgetFlag08((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->footer), 1);
            Widget_SetWidgetFlag08((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->rumbleIcon), 1);
            Widget_SetWidgetFlag08((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->prompt), 1);
            finish = (Shared_OptionsScreen *)g_optionsShortcutScreen;
            finish->page = 2;
            finish->pages = 4;
            break;
        }
        if ((((Shared_OptionsScreen *)(g_optionsShortcutScreen))->page) != 3) {
            return 0;
        }
    }
    return 0;
}

#if defined(VERSION_EU)
int Menu_ReturnZeroEuropean(void) {
    return 0;
}
#endif
#if defined(VERSION_DE)
int Menu_ReturnZeroGerman(void) {
    return 0;
}
#endif
#if defined(VERSION_DE) || defined(VERSION_EU)
/* Processes a widget with clipping and drawing operations. */
void Menu_DrawClippedWidgetSiblings(void *widget, sm_dldc args) {
    NumericWidgetChildView *record = widget;
    struct WidgetRect first;
    struct WidgetRect basis;
    struct WidgetRect value;
    struct WidgetRect transformed;
    s32 changed;

    changed = 0;
    if (Widget_ComputeWidgetBounds(&first, &basis, widget, &args) != 0) {
        if ((record->flags & 0x200) != 0) {
            N64Eng_GetClipBounds(&value.left, &value.top, &value.right, &value.bottom);
            transformed = value;
            Node_ClampRectToClip(&transformed, &basis);
            N64Eng_SetClipBounds(transformed.left, transformed.top, transformed.right, transformed.bottom);
            changed = 1;
        }
        Widget_DrawVisibleSiblings(record->firstChild, args);
        if (changed != 0) {
            N64Eng_SetClipBounds(value.left, value.top, value.right, value.bottom);
        }
    }
}
#endif

#if defined(VERSION_DE)

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

#if defined(VERSION_EU) || defined(VERSION_EU_X)
struct MenuFadeWidget;
struct MenuResourceWidget;
/* Per-language label pointer tables, indexed by the settings language byte (0x581). */
#endif

#if defined(VERSION_EU)
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
    SmpButton_AppendListText(firstList, g_optionsOffLabels[settings->language]);
    SmpButton_AppendListText(g_optionsPage->bloodModeList, g_optionsRedLabels[settings->language]);
    SmpButton_AppendListText(g_optionsPage->bloodModeList, g_optionsGreenLabels[settings->language]);
    SmpButton_SelectListEntry(g_optionsPage->bloodModeList, settings->bloodMode);
    secondList = SmpButton_CreateListWidget(85, 86);
    g_optionsPage->twoPlayerScreenList = secondList;
    SmpButton_AppendListText(secondList, g_optionsHorizontalLabels[settings->language]);
    SmpButton_AppendListText(g_optionsPage->twoPlayerScreenList, g_optionsVerticalLabels[settings->language]);
    SmpButton_SelectListEntry(g_optionsPage->twoPlayerScreenList, settings->twoPlayerScreenPreference);
    thirdList = SmpButton_CreateListWidget(81, 82);
    g_optionsPage->resolutionList = thirdList;
    SmpButton_AppendListText(thirdList, g_optionsResolutionLoRezChoiceLabels[settings->language]);
    if (Defs_GetMemorySize() != 0x400000) {
        SmpButton_AppendListText(g_optionsPage->resolutionList, g_optionsResolutionHiRezChoiceLabels[settings->language]);
        SmpButton_AppendListText(g_optionsPage->resolutionList, g_optionsResolutionLetterboxChoiceLabels[settings->language]);
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
    g_gameOptionsScreenState->bloodModeList = firstList;
    SmpButton_AppendListText(firstList, g_optionsOffLabels[settings->language]);
    SmpButton_AppendListText(g_gameOptionsScreenState->bloodModeList, g_optionsRedLabels[settings->language]);
    SmpButton_AppendListText(g_gameOptionsScreenState->bloodModeList, g_optionsGreenLabels[settings->language]);
    SmpButton_SelectListEntry(g_gameOptionsScreenState->bloodModeList, settings->bloodMode);
    secondList = SmpButton_CreateListWidget(MENU_RESOURCE_ID(446), MENU_RESOURCE_ID(447));
    g_gameOptionsScreenState->resolutionList = secondList;
    SmpButton_AppendListText(secondList, g_optionsResolutionLoRezChoiceLabels[settings->language]);
    if (Defs_GetMemorySize() != 0x400000) {
        SmpButton_AppendListText(g_gameOptionsScreenState->resolutionList, g_optionsResolutionHiRezChoiceLabels[settings->language]);
        SmpButton_AppendListText(g_gameOptionsScreenState->resolutionList, g_optionsResolutionLetterboxChoiceLabels[settings->language]);
    }
    SmpButton_SelectListEntry(g_gameOptionsScreenState->resolutionList, settings->resolution);
    slider = SmpSlider_CreateSliderWidget(MENU_RESOURCE_ID(448), MENU_RESOURCE_ID(449), 128);
    g_gameOptionsScreenState->gammaSlider = slider;
    SmpSlider_SetSliderItem(slider, settings->lightingGamma);
    SmpButton_WrapButtonWidget(MENU_RESOURCE_ID(451));
    SmpButton_WrapButtonWidget(MENU_RESOURCE_ID(452));
    g_gameOptionsScreenState->state = 0;
    Tsmos_DeactivateControllerState();
    return 0;
}
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)
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
    SmpButton_AppendListText(firstListHandle, g_optionsOffLabels[settings->language]);
    SmpButton_AppendListText(g_optionsShortcutScreen->firstList, g_optionsRedLabels[settings->language]);
    SmpButton_AppendListText(g_optionsShortcutScreen->firstList, g_optionsGreenLabels[settings->language]);
    SmpButton_SelectListEntry(g_optionsShortcutScreen->firstList, settings->bloodMode);
    secondListHandle = SmpButton_CreateListWidget(MENU_RESOURCE_ID(888), MENU_RESOURCE_ID(889));
    g_optionsShortcutScreen->secondList = secondListHandle;
    SmpButton_AppendListText(secondListHandle, g_optionsResolutionLoRezChoiceLabels[settings->language]);
    if (Defs_GetMemorySize() != 0x400000) {
        SmpButton_AppendListText(g_optionsShortcutScreen->secondList, g_optionsResolutionHiRezChoiceLabels[settings->language]);
        SmpButton_AppendListText(g_optionsShortcutScreen->secondList, g_optionsResolutionLetterboxChoiceLabels[settings->language]);
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
#undef MENU_RESOURCE_ID

#if defined(VERSION_US)
/* Releases the object g_characterSelectionMenu holds through Cache_FreeMemory, clears g_characterSelectionMenu, calls
   Tsmos_ActivateControllerState and Tsmos_SetMenuModelFlag with 2, and returns zero. */
s32 Selection_DestroyUsCharacterSelectionMenu(void) {
    Cache_FreeMemory(g_characterSelectionMenu);
    g_characterSelectionMenu = 0;
    Tsmos_ActivateControllerState();
    Tsmos_SetMenuModelFlag(2);
    return 0;
}

/* Calls Tsmos_SetMenuModelFlag with 1 and SoundElement_PlayFlatSound with 0xE78, and returns zero. */
s32 Selection_ActivateCharacterSelectionMode(void) {
    Tsmos_SetMenuModelFlag(1);
    SoundElement_PlayFlatSound(3704);
    return 0;
}
#endif
#if !(defined(VERSION_US))
/* Releases the object g_characterSelectionMenu holds through Cache_FreeMemory, clears g_characterSelectionMenu, calls
   Tsmos_ActivateControllerState and Tsmos_SetMenuModelFlag with 2, and returns zero. */
s32 Selection_DestroyCharacterSelectionMenu(void) {
    Cache_FreeMemory(g_characterSelectionMenu);
    g_characterSelectionMenu = 0;
    Tsmos_ActivateControllerState();
    Tsmos_SetMenuModelFlag(2);
    return 0;
}

/* Calls Tsmos_SetMenuModelFlag with 1 and SoundElement_PlayFlatSound with 0xE78, and returns zero. */
s32 Selection_ActivateCharacterSelectionMode(void) {
    Tsmos_SetMenuModelFlag(1);
    SoundElement_PlayFlatSound(3704);
    return 0;
}
#endif

/* Advances a player panel from its ready state and starts its selection. */



/* Applies the chosen character when the active player panel is ready. */






                          #if defined(VERSION_DE)
enum { SPECIAL_CHAR = 127 };
#elif defined(VERSION_EU_X)
enum { SPECIAL_CHAR = 133 };
#else
enum { SPECIAL_CHAR = 129 };
#endif

/* Dispatches event eventId through this file's 12-byte handler table, whose rows hold an event at g_characterSelectionEventIds, an actor kind at g_characterSelectionEventActorKinds and a handler at g_characterSelectionEventHandlers: the first row whose event equals eventId and whose kind equals the actor's input kind, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. */
int Selection_HandleCharacterVariantCycle(int element, int eventId, unsigned int message, int extra) {
    int index = message & 0xFFFF;
    CharacterVariantSelectionEntry *e;

    if ((message >> 16) == 3 && extra == 0) {
        e = &((CharacterVariantSelectionEntry *)g_characterSelectionMenu)[index];
        if (e->active == 1 && e->target != -1) {
            Menu_CyclePlayerCharacterVariant(index, e);
            SoundElement_PlayFlatSound(3708);
        }
    }
    return 0;
}

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 Selection_ReturnCharacterEventZeroA(void) {
    return 0;
}

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 Selection_ReturnCharacterEventZeroB(void) {
    return 0;
}

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 Selection_ReturnCharacterEventZeroC(void) {
    return 0;
}

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 Selection_ReturnCharacterEventZeroD(void) {
    return 0;
}

s32 Selection_CancelCharacterConfirmation(s32 element, s32 eventId, s32 entryId) {
    s32 confirmationState;
    s32 entryIndex;
    s32 entryOffset;
    StateMenuCancelCharacterConfirmation *selectionEntry;

    MarkMenuEventHandled();
    entryIndex = entryId & 0xFFFF;
    entryOffset = entryIndex * 1224;
    selectionEntry = (StateMenuCancelCharacterConfirmation *)&((PanelRecord *)g_characterSelectionMenu)[entryIndex];
    confirmationState = selectionEntry->confirmationState;
    switch (confirmationState) {
    case 1:
        if (g_gameSettings.controllerMode != 1) {
            g_characterSelectionMenu->phase = 5;
            g_characterSelectionMenu->timer = 4;
            g_characterSelectionMenu->result = 3;
        }
        break;
    case 3:
        selectionEntry->confirmationState = 1;
        SmpOverlay_SetSlotValue(g_characterSelectionMenu->slotOverlay, entryIndex, 0);
        Preview_SetPreviewTransformUpdate(&((PanelRecord *)(entryOffset + (s32)g_characterSelectionMenu))->target, 1);
        Menu_RefreshPlayerCharacterVariants(entryIndex);
        break;
    }
    return 0;
}

s32 Selection_ReadSelectionSlot(s32 unusedFirst, s32 unusedSecond, s32 packedPlayer) {
    s32 entryIndex;
    s32 choice;
    s32 unusedValue;
    CharacterSelectionRoot *characterSelectionRoot;

    entryIndex = packedPlayer & 0xFFFF;
    choice = SmpOverlay_GetSlotNodeId(g_characterSelectionMenu->slotOverlay, entryIndex);
    MarkMenuEventHandled();
    characterSelectionRoot = (CharacterSelectionRoot *)((char *)g_characterSelectionMenu + (entryIndex * sizeof(SelectionScreenPlayer)));
    if (characterSelectionRoot->phase == 1) {
        if (choice == SPECIAL_CHAR) Menu_ApplySlotValueGfx(entryIndex, characterSelectionRoot->choice);
        else if (Widget_ListHasFlag100(SmpOverlay_GetSlotValue(g_characterSelectionMenu->slotOverlay, entryIndex)) == 0) Menu_ApplySlotValueGfx(entryIndex, choice);
    }
    return 0;
}

s32 Selection_DispatchCharacterSelectionEvent(void *widget, s32 eventId, s32 eventData0, s32 eventData1, s32 eventData2) {
    ResidentEventHandlerEntry *handlers = (ResidentEventHandlerEntry *)g_characterSelectionEventIds;
    s32 row;
    for (row = 0; handlers[row].handler != 0; row++) {
        if (handlers[row].event == eventId &&
            (handlers[row].actorKind == ((struct MenuWidget *)widget)->resource ||
             handlers[row].actorKind == ANY_ACTOR_KIND)) {
            return handlers[row].handler(widget, eventId, eventData0, eventData1, eventData2);
        }
    }
    return 0;
}

/* Event callback for the match setup screen g_optionsShortcutScreen: on event 1 with the screen in state 1 it
   advances it, and once it reaches state 2 either goes back (choice 0: resets the mode, shows the
   item and queues sound 0x259 past g_selectedLevelId) or starts the match (choice 1: picks the arena,
   clears the pause word, then either sets the mode from the settings and active human players or
   stops the match objects and calls Stage_StartConfiguredMatch). Returns zero. */
s32 Menu_FinishTabOptionsTransition(void *item, s32 eventId, s32 event) {
    s32 state;
    s32 humans;
    s32 i;
    Shared_Game *settings;
    Shared_MenuData *menuData;

    if (event == 1) {
        state = Frontend_GetMenuImageState(g_optionsShortcutScreen);
        if (state != event) {
            return 0;
        }
        Frontend_DrawMenuImage(g_optionsShortcutScreen);
        Frontend_AdvanceMenuImageTransition(g_optionsShortcutScreen);
        if (Frontend_GetMenuImageState(g_optionsShortcutScreen) != 2) {
            return 0;
        }
        if (g_optionsShortcutScreen->choice != 0 && g_optionsShortcutScreen->choice != state) {
            return 0;
        }
        if (g_optionsShortcutScreen->choice == 0) {
            Frontend_RequestScreenMode(0);
            Widget_SetWidgetFlag08(item, 1);
            Track_RequestTrackByKey(g_selectedLevelId + 601);
            g_cinemaSequenceState->targetD8 = -1;
            g_cinemaSequenceState->state3C = state;
        } else {
            MarkMenuEventHandled();
            if (g_optionsShortcutScreen->arena == 0 && SoundElement_GetMusicPlaybackEnabled() != 0) {
                SoundElement_SetMusicPlaybackEnabled(Graphu64_NextRandom() % 4 + 56);
            } else {
                SoundElement_SetMusicPlaybackEnabled(g_optionsShortcutScreen->arena);
            }
            menuData = &g_playerViewRenderContext;
            menuData->pause = 0;
            if (g_optionsShortcutScreen->mode == -1) {
                humans = 0;
                i = 0;
                do {
                    if (menuData->game.playerSettings[i].locked == 0 && menuData->game.playerSettings[i].enabled == 1) {
                        humans++;
                    }
                    i++;
                } while (i < 4);
                settings = &g_gameSettings;
                if (settings->resolution == 2 && humans >= 2) {
                    Frontend_RequestScreenMode(1);
                } else {
                    Frontend_RequestScreenMode(settings->resolution);
                }
                Tsmos_RequestFrontendShutdown();
                return 0;
            }
            Pools_ResetActorPools(&menuData->object, 0);
            Player_InitializePlayerPool(menuData, 0, 0);
            Scene_LoadLevelResources(&g_world, 0, 0);
            Stage_StartConfiguredMatch();
        }
    }
    return 0;
}

/* Calls Tsmos_DeactivateControllerState and then SmXlate_SwitchScreen with 0x16. */
void Menu_SwitchToOptionsScreen(void) {
    Tsmos_DeactivateControllerState();
    SmXlate_SwitchScreen(22);
}

/* Writes the options page back into g_gameSettings: the two-player screen preference and, outside the DE version, the
   blood mode from their button lists (SmpButton_GetListSelection), the resolution from its list, and the
   lighting gamma from the gamma slider (SmpSlider_GetSliderItem). */
void Menu_CommitOptionsPage(void) {
    Shared_Game *options;
    s32 value;

#if defined(VERSION_DE)
    value = SmpButton_GetListSelection(g_optionsPage->twoPlayerScreenList);
    options = &g_gameSettings;
    options->twoPlayerScreenPreference = value;
#else
    value = SmpButton_GetListSelection(g_optionsPage->bloodModeList);
    options = &g_gameSettings;
    options->bloodMode = value;
    options->twoPlayerScreenPreference = SmpButton_GetListSelection(g_optionsPage->twoPlayerScreenList);
#endif
    options->resolution = SmpButton_GetListSelection(g_optionsPage->resolutionList);
    options->lightingGamma = SmpSlider_GetSliderItem(g_optionsPage->gammaSlider);
}

void Menu_CommitCompactOptionsPage(void) {
    Shared_Game *options;
    s32 value;

#if defined(VERSION_DE)
    value = SmpButton_GetListSelection(g_gameOptionsScreenState->resolutionList);
    options = &g_gameSettings;
    options->resolution = value;
#else
    value = SmpButton_GetListSelection(g_gameOptionsScreenState->bloodModeList);
    options = &g_gameSettings;
    options->bloodMode = value;
    options->resolution = SmpButton_GetListSelection(g_gameOptionsScreenState->resolutionList);
#endif
    options->lightingGamma = SmpSlider_GetSliderItem(g_gameOptionsScreenState->gammaSlider);
}

void Menu_CommitTabOptionsPage(void) {
    Shared_Game *options;
    s32 value;

#if defined(VERSION_DE)
    value = SmpButton_GetListSelection(g_optionsShortcutScreen->resolutionList);
    options = &g_gameSettings;
    options->resolution = value;
#else
    value = SmpButton_GetListSelection(g_optionsShortcutScreen->bloodModeList);
    options = &g_gameSettings;
    options->bloodMode = value;
    options->resolution = SmpButton_GetListSelection(g_optionsShortcutScreen->resolutionList);
#endif
    options->lightingGamma = SmpSlider_GetSliderItem(g_optionsShortcutScreen->gammaSlider);
}

#if defined(VERSION_DE)
struct MenuFadeWidget;
struct MenuResourceWidget;
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
    SmpButton_AppendListText(thirdList, g_optionsLowResolutionLabels[0]);
    if (Defs_GetMemorySize() != 0x400000) {
        SmpButton_AppendListText(g_optionsPage->resolutionList, g_optionsHighResolutionLabels);
        SmpButton_AppendListText(g_optionsPage->resolutionList, g_optionsLetterboxLabels);
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

#if !(defined(VERSION_DE) || defined(VERSION_EU_X))
/* Releases the object g_optionsPage holds through Cache_FreeMemory, clears g_optionsPage and returns zero. */
s32 Menu_DestroyOptionsPage(void) {
    Cache_FreeMemory(g_optionsPage);
    g_optionsPage = 0;
    return 0;
}
#endif

#if defined(VERSION_EU)
/* Older build's code pointer: offsets of its code, relocated at load. */
void *g_menuCodePointer[1] = { (void *)0x00442F6C };
#endif
