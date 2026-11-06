#include "Common/screen.h"
#include "include_asm.h"
#include "Common/menu_options_and_results.h"
#include "Common/vector4f.h"
#include "Common/aiprofile.h"
#include "types.h"
#include "Common/menulistscreen.h"
#include "Frontend/menu_commitoptionspage.h"
#include "Frontend/frontend_handletaboptionsshortcut.h"
#include "Scene/cache_freememory.h"
#include "Common/shared_menureply.h"
#include "Common/menu_screen_elements.h"
#include "Common/runtime_declarations.h"
#include "Common/access_s8_10f.h"
#include "Common/selectionscreenstate.h"
#include "Frontend/menuimage.h"
#include "Scenariosetupscreen/scenariosetupscreen.h"
#include "Frontend/frontend_address_symbols.h"
#include "Frontend/node_findwidgetbyresourceid.h"
#include "Frontend/options_list_declarations.h"
#include "Common/shared_gameslot.h"
#include "Common/game_session.h"
#include "System/sound_context_music_and_voice_control.h"
#include "Common/menu_initializeoptionsscene.h"
#include "options.h"
#include "Common/widget_texture_retention.h"
#include "Game/frontend_closeoptionspage.h"
#include "Menu/menu_commitoptionspage.h"
#include "Menu/state.h"
#include "Frontend/frontend_dispatchoptionspageevent.h"
#include "Common/frontend_resource_load_state.h"
#include "Menu/localized_game_option_choices.h"
#include "Common/Lone/g_languageindex.h"
#include "Common/sharedplayer.h"
#include "Ui/Quag/N64_Eng.h"
#include "Node/node_configurescrolledtablecell.h"

/* unit OPTIONS.CPP */
#if defined(VERSION_US) || defined(VERSION_US_REV1)
#include "Menu/scroll.h"
#include "Common/menu_overlay.h"
#include "Common/menu_options_and_results.h"
#include "types.h"
#include "Common/shared_gameslot.h"
#include "types.h"
#include "Common/shared_optionsscreen.h"
#endif
#if defined(VERSION_DE)
#include "System/sound_context_music_and_voice_control.h"
#include "Menu/scroll.h"
#include "types.h"
#include "Common/shared_optionsscreen.h"
#include "Ui/Tsmos/Smp/smp_button.h"
#include "Smp/smp_slider.h"
#include "Widget/widget_findwidgetatpoint.h"
#include "Menuimage/menuimage.h"
#include "Smp/smp_flicker.h"
#include "Defs/defs.h"
/* Localized label pointers for the memory-mode list (rev1 g_optionsResolutionLoRezChoiceLabels..g_optionsResolutionLetterboxChoiceLabels). */
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
    SmpButton_AppendListText(secondListHandle, g_optionsLowResolutionLabels[0]);
    if (Defs_GetMemorySize() != 0x400000) {
        SmpButton_AppendListText(g_optionsShortcutScreen->secondList, g_optionsHighResolutionLabels);
        SmpButton_AppendListText(g_optionsShortcutScreen->secondList, g_optionsLetterboxLabels);
    }
    settings = &g_gameSettings;
    SmpButton_SelectListEntry(g_optionsShortcutScreen->secondList, settings->slots[7].secondListMode);
    slider = SmpSlider_CreateSliderWidget(881, 882, 128);
    g_optionsShortcutScreen->slider = slider;

    SmpSlider_SetSliderItem((struct Scroll *)slider, settings->lightingGamma);
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

/* unit FRONTEND_CLOSESETTINGSPAGE.CPP */
#if defined(VERSION_DE)
#include "Common/menu_options_and_results.h"
#include "types.h"
#include "Scene/cache_freememory.h"
#include "Game/frontend_closesettingspage.h"
/* German Menu_DestroyOptionsPage: releases the object g_optionsPage holds through Cache_FreeMemory, clears
   g_optionsPage, reloads the default language strings and returns zero. */
s32 Frontend_CloseSettingsPage(void) {
    Cache_FreeMemory(g_optionsPage);
    g_optionsPage = 0;
    Node_LoadLanguageStringsIfAny(0);
    return 0;
}
#endif

/* unit FRONTEND_HANDLEOPTIONSPAGESHORTCUT.CPP */
#include <platform_sdk.h>
#include "types.h"
#include "Game/frontend_handleoptionspageshortcut.h"
#include "Smp/smp_slider.h"
#include "Menu/menu_commitoptionspage.h"
#include "Frontend/frontend_address_symbols.h"

/* Acts on the mode of the menu held first in the block g_optionsPage points to: in mode 4 it calls
   MarkMenuEventHandled and then either SmXlate_SwitchScreen with the block's word at 0x20, when that is not -1,
   or Menu_ReturnToPreviousScreen. Returns zero. */

#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
enum { SHORTCUT_RESET = 80, SHORTCUT_SIX = 87, SHORTCUT_FIVE = 88 };
#elif defined(VERSION_EU_X)
enum { SHORTCUT_RESET = 92, SHORTCUT_SIX = 82, SHORTCUT_FIVE = 85 };
#endif

/* Handles the menu shortcut codes by selecting an entry and refreshing the screen. */
s32 Frontend_UpdateOptionsPageExit(void) {
    switch (SmpSlider_GetTransitionMode(g_optionsPage->menu)) {
    case 3:
        break;
    case 4:
        MarkMenuEventHandled();
        if (g_optionsPage->value != -1) {
            SmXlate_SwitchScreen(g_optionsPage->value);
        } else {
            Menu_ReturnToPreviousScreen();
        }
        break;
    }
    return 0;
}

s32 Frontend_HandleOptionsPageShortcut(void) {
    s32 focusedElementIdResult;
    s32 shortcutHandled;
    MarkMenuEventHandled();
    shortcutHandled = 1;
    focusedElementIdResult = Menu_GetFocusedElementId();
    switch(focusedElementIdResult) {
    case SHORTCUT_RESET:g_optionsPage->value=-1;break;
    case SHORTCUT_SIX:g_optionsPage->value=6;break;
    case SHORTCUT_FIVE:g_optionsPage->value=5;break;
    default:shortcutHandled=0;break;
    }
    if (shortcutHandled == 1) {
        Menu_CommitOptionsPage();
        SmpSlider_SetTransitionMode(g_optionsPage->menu, 2);
    }
    return 0;
}

/* unit FRONTEND_CLOSEOPTIONSPAGE.CPP */
/* Calls MarkMenuEventHandled, sets the exit value of the options page g_optionsPage points to to -1,
   calls SmpSlider_SetTransitionMode on the page's menu with 2 and then Menu_CommitOptionsPage, returning zero. */
s32 Frontend_CloseOptionsPage(void) {
    struct StateFrontendUpdateOptionsPageExit *state;

    MarkMenuEventHandled();
    state = g_optionsPage;
    state->value = -1;
    SmpSlider_SetTransitionMode(state->menu, 2);
    Menu_CommitOptionsPage();
    return 0;
}

#if defined(VERSION_US) || defined(VERSION_US_REV1)
/* Returns zero. */
s32 Frontend_ReturnOptionsEventZeroA(void) {
    return 0;
}

/* Returns zero. */
s32 Frontend_ReturnOptionsEventZeroB(void) {
    return 0;
}
#endif

/* unit FRONTEND_RETURNGERMANOPTIONSEVENTZEROA.CPP */
#if defined(VERSION_DE)
/* Event handler placeholder: ignores the event and returns zero. */
s32 Frontend_ReturnGermanOptionsEventZeroA(void) {
    return 0;
}

/* Event handler placeholder: ignores the event and returns zero. */
s32 Frontend_ReturnGermanOptionsEventZeroB(void) {
    return 0;
}
#endif

/* unit FRONTEND_RETURNEUOPTIONSEVENTZEROA.CPP */
#if defined(VERSION_EU)
s32 Frontend_ReturnEuOptionsEventZeroA(void) {
    return 0;
}

/* Event handler placeholder: ignores the event and returns zero. */
s32 Frontend_ReturnEuOptionsEventZeroB(void) {
    return 0;
}
#endif

/* unit FRONTEND_CREATEGAMEOPTIONSSCREEN.CPP */
/* Calls the handler registered for eventKind (tables g_gameOptionsEventKinds, g_gameOptionsActorKinds, g_gameOptionsEventHandlers). A row matches when its event equals eventKind and its kind equals the actor's kind or is the any-kind wildcard 0x7530. Returns the handler's result, or zero when no row matches. */


s32 Frontend_DispatchOptionsPageEvent(void *menuActor, s32 eventKind, s32 eventDataOne, s32 eventDataTwo, s32 eventDataThree) {
    GameOptionsEventHandler *entry;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;
    MenuWidget *actor;

    if (g_gameOptionsEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_gameOptionsEventHandlers;
        index = 0;
        do {
            if (g_gameOptionsEventKinds[index].value == eventKind) {
                actor = menuActor;
                actor_kind = actor->resource;
                table_kind = g_gameOptionsActorKinds[index].value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*entry)(menuActor, eventKind, eventDataOne, eventDataTwo, eventDataThree);
                }
            }
            entry += 3;
            index++;
        } while (*entry != 0);
    }
    return 0;
}

#if !(defined(VERSION_EU) || defined(VERSION_EU_X))
#include "Frontend/game_options_labels.h"
#include "Frontend/options_list_declarations.h"
#include "types.h"
#include "Common/shared_gameslot.h"
#include "Game/frontend_creategameoptionsscreen.h"
#include "Ui/Tsmos/Smp/smp_button.h"
#include "Smp/smp_button.h"
#include "Smp/smp_slider.h"
#include "Defs/defs.h"
#include "Frontend/frontend_address_symbols.h"

/* Builds screen state g_gameOptionsScreenState: allocates its 0x10 bytes, registers resources (0x1BD - OPTIONS_RESOURCE_SHIFT) and (0x1C2 - OPTIONS_RESOURCE_SHIFT),
   creates list 0x1BB/0x1BC at 0x4 with the three texts gameOptionsLabel(0), gameOptionsLabel(1) and gameOptionsLabel(2) and
   selects byte 0x1B of the settings g_gameSettings, creates list (0x1BE - OPTIONS_RESOURCE_SHIFT)/(0x1BF - OPTIONS_RESOURCE_SHIFT) at 0x8 with gameOptionsLabel(3),
   plus gameOptionsLabel(4) and gameOptionsLabel(5) unless Defs_GetMemorySize reports 0x400000, and selects settings byte
   0x580, creates the 0x80-step slider (0x1C0 - OPTIONS_RESOURCE_SHIFT)/(0x1C1 - OPTIONS_RESOURCE_SHIFT) at 0x0 set to the settings word at 0x10,
   registers (0x1C3 - OPTIONS_RESOURCE_SHIFT) and (0x1C4 - OPTIONS_RESOURCE_SHIFT), clears the word at 0xC, resets through Tsmos_DeactivateControllerState and returns
   zero. */
s32 Frontend_CreateGameOptionsScreen(void) {

    Shared_Game *settings;
    struct MenuListWidget *list;
    s32 slider;

    g_gameOptionsScreenState = Cache_AllocateMemory(16);
    SmpButton_WrapButtonWidget((445 - OPTIONS_RESOURCE_SHIFT));
    SmpButton_WrapButtonWidget((450 - OPTIONS_RESOURCE_SHIFT));
    if (OPTIONS_HAS_FIRST_LIST) {
    list = SmpButton_CreateListWidget(443, 444);
    g_gameOptionsScreenState->bloodModeList = list;
    SmpButton_AppendListText(g_gameOptionsScreenState->bloodModeList, gameOptionsLabel(0));
    SmpButton_AppendListText(g_gameOptionsScreenState->bloodModeList, gameOptionsLabel(1));
    SmpButton_AppendListText(g_gameOptionsScreenState->bloodModeList, gameOptionsLabel(2));
    settings = &g_gameSettings;
    SmpButton_SelectListEntry(g_gameOptionsScreenState->bloodModeList, settings->bloodMode);
    }
    list = SmpButton_CreateListWidget((446 - OPTIONS_RESOURCE_SHIFT), (447 - OPTIONS_RESOURCE_SHIFT));
    g_gameOptionsScreenState->resolutionList = list;
    SmpButton_AppendListText(g_gameOptionsScreenState->resolutionList, gameOptionsLabel(3));
    if (Defs_GetMemorySize() != 0x400000) {
        SmpButton_AppendListText(g_gameOptionsScreenState->resolutionList, gameOptionsLabel(4));
        SmpButton_AppendListText(g_gameOptionsScreenState->resolutionList, gameOptionsLabel(5));
    }
    if (!OPTIONS_HAS_FIRST_LIST) settings = &g_gameSettings;
    SmpButton_SelectListEntry(g_gameOptionsScreenState->resolutionList, settings->resolution);
    slider = SmpSlider_CreateSliderWidget((448 - OPTIONS_RESOURCE_SHIFT), (449 - OPTIONS_RESOURCE_SHIFT), 128);
    g_gameOptionsScreenState->gammaSlider = slider;

    SmpSlider_SetSliderItem((struct Scroll *)slider, settings->lightingGamma);
    SmpButton_WrapButtonWidget((451 - OPTIONS_RESOURCE_SHIFT));
    SmpButton_WrapButtonWidget((452 - OPTIONS_RESOURCE_SHIFT));
    g_gameOptionsScreenState->state = 0;
    Tsmos_DeactivateControllerState();
    return 0;
}
#endif



/* unit FRONTEND_HANDLETABOPTIONSSHORTCUT.CPP */
/* The first message this handles and how many it takes: eu-x numbers the messages 4 higher, de 4
   lower and takes only 8, as each cartridge's own bytes show; us, us-rev1 and eu share 0x377 and 10. */

/* The message screen g_gameOptionsScreenState; its handled flag marks the message handled. */


/* Releases the object g_gameOptionsScreenState holds through Cache_FreeMemory, calls Tsmos_ActivateControllerState, clears
   g_gameOptionsScreenState and returns zero. */
s32 Frontend_DestroyCompactOptionsPage(void) {
    Cache_FreeMemory(g_gameOptionsScreenState);
    Tsmos_ActivateControllerState();
    g_gameOptionsScreenState = 0;
    return 0;
}

/* Marks the compact options page as activated and calls Tsmos_ActivateControllerState, once:
   nothing happens when it is already activated. Returns zero. */
s32 Frontend_ActivateCompactOptionsPage(void) {
    struct CompactOptionsPageView *state = g_gameOptionsScreenState;

    if (state->flagWord == 0) {
        state->flagWord = 1;
        Tsmos_ActivateControllerState();
    }
    return 0;
}

/* Handles the menu message Menu_GetFocusedElementId reports after MarkMenuEventHandled: 0x1C3, 0x1BD, 0x1C2 and
   0x1C4 send codes -1, 13, 12 and 14 to Random_SetMenuChoiceResult; a handled message then runs Menu_CommitCompactOptionsPage
   and Menu_ReturnToPreviousScreen. Returns zero. */
s32 Frontend_HandleCompactOptionsShortcut(void) {
    s32 handled;
    MarkMenuEventHandled();
    handled = 1;
    switch (Menu_GetFocusedElementId()) {
#if defined(VERSION_DE)
    case 447:
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    case 451:
#elif defined(VERSION_EU_X)
    case 455:
#endif
        Random_SetMenuChoiceResult(-1);
        break;
#if defined(VERSION_DE)
    case 441:
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    case 445:
#elif defined(VERSION_EU_X)
    case 449:
#endif
        Random_SetMenuChoiceResult(13);
        break;
#if defined(VERSION_DE)
    case 446:
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    case 450:
#elif defined(VERSION_EU_X)
    case 454:
#endif
        Random_SetMenuChoiceResult(12);
        break;
#if defined(VERSION_DE)
    case 448:
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    case 452:
#elif defined(VERSION_EU_X)
    case 456:
#endif
        Random_SetMenuChoiceResult(14);
        break;
    default:
        handled = 0;
        break;
    }
    if (handled == 1) {
        Menu_CommitCompactOptionsPage();
        Menu_ReturnToPreviousScreen();
    }
    return 0;
}

/* Calls MarkMenuEventHandled, Random_SetMenuChoiceResult with -1, Menu_CommitCompactOptionsPage and Menu_ReturnToPreviousScreen, and returns zero. */
s32 Frontend_CloseCompactOptionsPage(void) {
    MarkMenuEventHandled();
    Random_SetMenuChoiceResult(-1);
    Menu_CommitCompactOptionsPage();
    Menu_ReturnToPreviousScreen();
    return 0;
}

s32 Frontend_DispatchCompactOptionsEvent(void *menuActor, s32 eventKind, s32 eventDataOne, s32 eventDataTwo, s32 eventDataThree) {
    CompactOptionsEventHandler *entry;
    MenuWidget *actor;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;

    if (g_compactOptionsEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_compactOptionsEventHandlers;
        index = 0;
        do {
            if (g_compactOptionsEventKinds[index].value == eventKind) {
                actor = menuActor;
                actor_kind = actor->resource;
                table_kind = g_compactOptionsActorKinds[index].value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*entry)(menuActor, eventKind, eventDataOne, eventDataTwo, eventDataThree);
                }
            }
            entry += 3;
            index++;
        } while (*entry != 0);
    }
    return 0;
}

/* Releases the object g_optionsShortcutScreen holds through Cache_FreeMemory, calls Tsmos_ActivateControllerState, clears g_optionsShortcutScreen, calls
   Cinema_ReleaseSequenceContext_FrontendHandletaboptionsshortcut and returns zero. */
s32 Frontend_DestroyTabOptionsPage(void) {
    Cache_FreeMemory(g_optionsShortcutScreen);
    Tsmos_ActivateControllerState();
    g_optionsShortcutScreen = 0;
    Cinema_ReleaseSequenceContext();
    return 0;
}

/* Deactivates the controller state and brings the shortcut menu image back on screen. */
static inline void Frontend_ReopenTabOptionsShortcut(void) {
    Tsmos_DeactivateControllerState();
    Frontend_StartMenuImageTransition(g_optionsShortcutScreen);
    g_optionsShortcutScreen->shown = 1;
    g_optionsShortcutScreen->timer = -1;
    Widget_SetWidgetFlag08(g_optionsShortcutScreen->window, 1);
    Widget_SetWidgetFlag08(g_optionsShortcutScreen->second_window, 1);
    Cinema_ReleaseSequenceContext();
}

/* Starts a random cup stage; when none can start, shows a message for 20 ticks instead of leaving the menu. */
static inline void Frontend_RetryTabOptionsShortcut(void) {
    Tsmos_DeactivateControllerState();
    if (ScenarioSetup_StartRandomCupStage() == 0) {
        g_optionsShortcutScreen->messageMode = 5;
        g_optionsShortcutScreen->messageNextMode = 4;
        g_optionsShortcutScreen->timer = 20;
    } else {
        Frontend_StartMenuImageTransition(g_optionsShortcutScreen);
        g_optionsShortcutScreen->shown = 1;
        g_optionsShortcutScreen->timer = 0;
    }
}

/* Handles the focused menu element of the tab options shortcut screen: one element reopens the screen, one retries
   with a random cup stage, and the others pick menu choice results 12, 13, 14 or 23. A handled element then commits
   the options page. Returns zero. */
s32 Frontend_HandleTabOptionsShortcut(void) {
    s32 handled;
    u32 message;
    MarkMenuEventHandled();
    handled = 1;
    message = Menu_GetFocusedElementId() -
#if defined(VERSION_DE)
        883;
#elif defined(VERSION_EU_X)
        891;
#else
        887;
#endif
    switch (message) {
#if defined(VERSION_DE)
    case 0:
#else
    case 6:
#endif
        Frontend_ReopenTabOptionsShortcut();
        break;
#if defined(VERSION_DE)
    case 3:
#else
    case 9:
#endif
        Random_SetMenuChoiceResult(23);
        break;
#if defined(VERSION_DE)
    case 1:
#else
    case 7:
#endif
        Frontend_RetryTabOptionsShortcut();
        break;
#if defined(VERSION_DE)
    case 6:
#else
    case 0:
#endif
        Random_SetMenuChoiceResult(13);
        break;
#if defined(VERSION_DE)
    case 7:
#else
    case 5:
#endif
        Random_SetMenuChoiceResult(12);
        break;
#if defined(VERSION_DE)
    case 2:
#else
    case 8:
#endif
        Random_SetMenuChoiceResult(14);
        break;
    default:
        handled = 0;
        break;
    }
    if (handled == 1) {
        Menu_CommitTabOptionsPage();
    }
    return 0;
}

s32 Frontend_ConsumeTabOptionsEvent(void) {
    MarkMenuEventHandled();
    return 0;
}

/* Calls the handler registered for eventKind (tables g_tabOptionsEventKinds, g_tabOptionsActorKinds, g_tabOptionsEventHandlers). A row matches when its event equals eventKind and its kind equals the actor's kind or is the any-kind wildcard 0x7530. Returns the handler's result, or zero when no row matches. */
s32 Frontend_DispatchTabOptionsEvent(void *menuActor, s32 eventKind, s32 eventDataOne, s32 eventDataTwo, s32 eventDataThree) {
    TabOptionsEventHandler *entry;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;
    struct MenuWidget *actor;

    if (g_tabOptionsEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_tabOptionsEventHandlers;
        index = 0;
        do {
            if (g_tabOptionsEventKinds[index].value == eventKind) {
                actor = menuActor;
                actor_kind = actor->resource;
                table_kind = g_tabOptionsActorKinds[index].value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*entry)(menuActor, eventKind, eventDataOne, eventDataTwo, eventDataThree);
                }
            }
            entry += 3;
            index++;
        } while (*entry != 0);
    }
    return 0;
}

#if defined(VERSION_DE)
unsigned int k_FrontendHandletaboptionsshortcutEncodedWords[2] = {
    0x00424034, 0x0042405C,
};
#endif

/* unit MENU_CREATELOCALIZEDSETTINGSPAGE.CPP */
#if defined(VERSION_EU_X)
#include "Common/shared_gameslot.h"
#include "Menu/scroll.h"
#include "Common/menu_overlay.h"
#include "Common/menu_options_and_results.h"
#include "types.h"
#include "Game/menu_createlocalizedsettingspage.h"
#include "Ui/Tsmos/Smp/smp_button.h"
#include "Ui/Tsmos/Smp/smp_fade.h"
/* Per-language label pointer tables, indexed by the settings language byte (0x581). */

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
    SmpButton_AppendListText(firstList, g_optionsOffLabels[settings->language]);
    SmpButton_AppendListText(g_optionsPage->bloodModeList, g_optionsRedLabels[settings->language]);
    SmpButton_AppendListText(g_optionsPage->bloodModeList, g_optionsGreenLabels[settings->language]);
    SmpButton_SelectListEntry(g_optionsPage->bloodModeList, settings->bloodMode);
    secondList = SmpButton_CreateListWidget(86, 87);
    g_optionsPage->twoPlayerScreenList = secondList;
    SmpButton_AppendListText(secondList, g_optionsHorizontalLabels[settings->language]);
    SmpButton_AppendListText(g_optionsPage->twoPlayerScreenList, g_optionsVerticalLabels[settings->language]);
    SmpButton_SelectListEntry(g_optionsPage->twoPlayerScreenList, settings->twoPlayerScreenPreference);
    thirdList = SmpButton_CreateListWidget(88, 89);
    g_optionsPage->resolutionList = thirdList;
    SmpButton_AppendListText(thirdList, g_optionsResolutionLoRezChoiceLabels[settings->language]);
    if (Defs_GetMemorySize() != 0x400000) {
        SmpButton_AppendListText(g_optionsPage->resolutionList, g_optionsResolutionHiRezChoiceLabels[settings->language]);
        SmpButton_AppendListText(g_optionsPage->resolutionList, g_optionsResolutionLetterboxChoiceLabels[settings->language]);
    }
    SmpButton_SelectListEntry(g_optionsPage->resolutionList, settings->resolution);
    slider = SmpSlider_CreateSliderWidget(90, 91, 128);
    g_optionsPage->gammaSlider = (struct Scroll *)slider;
    SmpSlider_SetSliderItem((struct Scroll *)slider, settings->lightingGamma);
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
#include "Common/player_join_requests.h"
#include "Smp/smp_slider.h"
#include "Defs/defs.h"
#include "Smp/smp_flicker.h"
#include "Frontend/frontend_address_symbols.h"
#endif

/* unit MENU_DRAWCLIPPEDWIDGETSIBLINGS.CPP */
#if defined(VERSION_EU_X)
int Menu_DestroyEuxOptionsAndReloadLanguage(void) {
    Cache_FreeMemory(g_optionsPage);
    g_optionsPage = 0;
    Node_LoadLanguageStringsIfAny(g_languageIndex);
    return 0;
}
#endif

/* unit GAME.CPP */
#if defined(VERSION_EU_X)
#include "types.h"
#include "Common/shared_gameslot.h"
#include "Game/game.h"
#include "T2soundelement/T2SoundElement.h"
#include "Frontend/frontend_address_symbols.h"
#include "Frontend/frontend.h"
/* Language selector, previous entry: on the confirm press (press == 1) steps the language byte down (0 wraps to 2), shows the
   new language's label in item 0x5E and plays sound 0xE81. */
s32 Frontend_SelectPreviousLanguage(void *window, s32 b, s32 c, s32 press) {
    MarkMenuEventHandled();
    if (press != 1) {
        return 0;
    }
    {
        Shared_Game *g = &g_gameSettings;
        if (g->language == 0) g->language = 2; else g->language--;
    }
    ((MenuWidget *)Node_FindWidgetByResourceId(window, 94))->text = g_optionsLocalizedShortcutText[g_languageIndex];
    SoundElement_PlayFlatSound(3713);
    return 0;
}
#endif

#if defined(VERSION_EU_X)
/* Language selector, next entry: as Frontend_SelectPreviousLanguage but steps the language byte up (2 wraps to 0). */
s32 Frontend_SelectNextLanguage(void *window, s32 b, s32 c, s32 press) {
    MarkMenuEventHandled();
    if (press != 1) {
        return 0;
    }
    {
        Shared_Game *g = &g_gameSettings;
        if (g->language == 2) g->language = 0; else g->language++;
    }
    ((MenuWidget *)Node_FindWidgetByResourceId(window, 94))->text = g_optionsLocalizedShortcutText[g_languageIndex];
    SoundElement_PlayFlatSound(3713);
    return 0;
}
#endif
