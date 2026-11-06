#include "Common/rg.h"
#include "Frontend/node_findwidgetbyresourceid.h"
#include "include_asm.h"
#include "Common/shared_gameslot.h"
#include "Scene/cache_freememory.h"
#include "Common/playerprofiles.h"
#include "Ui/X_files/x_plus.h"
#include "Common/sharedplayer.h"
#include "Common/gameplay_settings.h"
#include "Common/alauxbus_s.h"
#include "Frontend/screen.h"
#include "Menu_choice/frontend_initplaymodemenu.h"
#include "Ui/Tsmos/Smp/smp_fade.h"
#include "World/playerprofile.h"
#include "Common/screen.h"
#include "Frontend/scenario_cup_catalogue.h"
#include "Common/selectionscreenstate.h"
#include "Resmgr/tsmos_setidletimer.h"
#include "Common/shared_menureply.h"
#include "Engine/defs.h"
#include "Common/menu_options_and_results.h"
#include "Ai/playerprofile.h"
#include "Pakinterfacescreen/pakinterface_setscreenphase.h"
#include "Widget/widget_findwidgetatpoint.h"
#include "Smp/smp_button.h"
#include "Focus/focus.h"
#include "Smp/smp_slider.h"
#include "Menu/menu.h"
#include "Smp/smp_flicker.h"
#include "Frontend/frontend_address_symbols.h"
#include "Common/stagepreset.h"
#include "Frontend/playmodemenu_state.h"
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Menu_choice/menu_choice.h"
#include "Playercount/frontend_updateplayercountscreen.h"
#include "Common/aiprofile.h"
#include "Frontend/frontend_dispatchplaymodeevent.h"
#include "Common/packed_callback.h"

/* unit FRONTEND_INITPLAYMODEMENU.CPP */
#if defined(VERSION_EU_X)
#define WID_42 68
#define WID_43 69
#define WID_44 70
#define WID_45 71
#define WID_46 72
#define WID_47 75
#define WID_48 77
#define WID_4A 78
#define WID_4B 73
#define WID_4C 74
#define WID_49 76
#else
#define WID_4A 74
#define WID_4B 75
#define WID_4C 76
#define WID_42 66
#define WID_43 67
#define WID_44 68
#define WID_45 69
#define WID_46 70
#define WID_47 71
#define WID_48 72
#define WID_49 73
#endif
/* Builds the options screen: clears the per-player settings, retires bots that are no longer wanted, allocates
 * the screen record in g_playModeMenuState and picks the button layout. The layout is 3 when any human is on a pad
 * that Defs_TestBit reports in group 0 (or the game flag 0x20000000 is set), 2 for group 1, else the
 * default; it positions the first widget and shows or hides the sibling widgets. */
s32 Frontend_InitPlayModeMenu(void *menu) {
    CGameStatus *counters = &g_gameSettings.counters;
    MenuWidget *title;
    MenuWidget *widget;
    s32 i;
    s32 layout;
    s32 groupA;
    s32 groupB;
    s32 groupC;
    s32 mode;

    ScenarioSetup_SetCupCategory(-1);
    Random_SetSelectedStage(0, 0);
    counters->humanWon = 0;
    Tsmos_SetIdleTimer(0.0f);
    g_gameSettings.local = 1;

    for (i = 0; i < 8; i++) {
        { Shared_PlayerSettingsRecord *entry = &g_gameSettings.playerSettings[i];
        entry->enabled = 0;
        entry->locked = 0; }
    }
    for (i = 0; i < 4; i++) {
        if (g_localPlayerProfiles[i].player >= 0 && g_profileSlotEnabledFlags[i * sizeof(Profile)] == 1) {
            Player_InitializeProfile((char *)&g_localPlayerProfiles[i]);
            g_localPlayerProfiles[i].player = -1;
            g_profileSlotEnabledFlags[i * sizeof(Profile)] = 0;
        }
        XPlus_FillMemory(g_localPlayerProfiles[0].levelFlags[1] + i * sizeof(g_localPlayerProfiles[0]), 0, 5);
    }
    g_playModeMenuState = Cache_AllocateMemory(28);
    Tsmos_ActivateControllerState();
    groupA = 0;
    groupB = 0;
    groupC = 0;
    for (i = 0; i < 4; i++) {
        if (g_localPlayerProfiles[i].player >= 0) {
            groupA = groupA || Defs_TestBit(&g_profileUnlockGroupFlags[i * sizeof(Profile)], 0);
            groupB = groupB || Defs_TestBit(&g_profileUnlockGroupFlags[i * sizeof(Profile)], 1);
            groupC = groupC || Defs_TestBit(&g_profileUnlockGroupFlags[i * sizeof(Profile)], 2);
        }
    }
    if (g_gameSettings.flags & 0x20000000) {
        groupC = 1;
        groupB = 1;
    }
    layout = 0;
    if (groupC == 1) {
        layout = 3;
    } else if (groupB == 1) {
        layout = 2;
    }
    title = Node_FindWidgetByResourceId(menu, WID_42);
    switch (layout) {
    case 2:
        SmpButton_WrapButtonWidget(WID_48);
        widget = Node_FindWidgetByResourceId(menu, WID_4A);
        Widget_SetWidgetFlag100(widget, 1);
        Widget_SetWidgetFlag08(widget, 0);
        title->y = 51;
        title->height = 120;
        break;
    case 3:
        SmpButton_WrapButtonWidget(WID_4A);
        SmpButton_WrapButtonWidget(WID_48);
        title->y = 42;
        title->height = 136;
        break;
    default:
        widget = Node_FindWidgetByResourceId(menu, WID_48);
        Widget_SetWidgetFlag100(widget, 1);
        Widget_SetWidgetFlag08(widget, 0);
        widget = Node_FindWidgetByResourceId(menu, WID_4A);
        Widget_SetWidgetFlag100(widget, 1);
        Widget_SetWidgetFlag08(widget, 0);
        title->y = 60;
        title->height = 104;
        break;
    }
    i = -1;
    Focus_AdvanceActiveSlot(&i);
    if (i < 0) {
        Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(menu, WID_4C), 1);
    }
    mode = Control_IsControllerConnected(0);
    if (mode != 1 || Control_IsControllerConnected(1) != mode) {
        Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(menu, WID_49), 1);
    }
    g_playModeMenuState->music = SmpFade_CreateFadeWidget(WID_42, 36);
    SmpSlider_DisableTransition(g_playModeMenuState->music);
    SmpButton_WrapButtonWidget(WID_45);
    SmpButton_WrapButtonWidget(WID_46);
    SmpButton_WrapButtonWidget(WID_49);
    SmpButton_WrapButtonWidget(WID_4B);
    SmpButton_WrapButtonWidget(WID_4C);
    SmpButton_WrapButtonWidget(WID_47);
    g_playModeMenuState->title = Node_FindWidgetByResourceId(menu, WID_43);
    g_playModeMenuState->title->alpha = 15;
    g_playModeMenuState->prompt = SmpFlicker_CreateFlickerWidget(WID_44, 110);
    if (Menu_GetBlockedScreenOwner() == 2) {
        g_playModeMenuState->opening = 9;
    } else {
        g_playModeMenuState->opening = 1;
    }
    g_playModeMenuState->scrollDelay = 3;
    Frontend_RequestScreenMode(0);
    return 0;
}

/* Applies the play mode picked on the front-end menu: sets the next screen, the controller mode and which players
 * join, then hands the screen record on. */
s32 Frontend_ApplyModeChoice(void) {
    Shared_PlayerSettingsRecord *status;
    Shared_Game *settings;

    s32 i;

    MarkMenuEventHandled();
    switch (Menu_GetFocusedElementId()) {
    #if defined(VERSION_EU_X)
    case 71:
#else
    case 69:
#endif
        g_playModeMenuState->nextScreen = 26;
        g_gameSettings.controllerMode = 0;
        break;
    #if defined(VERSION_EU_X)
    case 76:
#else
    case 73:
#endif
        settings = &g_gameSettings;
        status = settings->playerSettings;
        g_playModeMenuState->nextScreen = 7;
        settings->controllerMode = 2;
        for (i = 0; i < 2; i++) {
            status[i].enabled = 1;
            status[i].slot = i;
            if (g_localPlayerProfiles[i].player < 0) {
                Player_InitializeProfileSlot(i);
            }
        }
        break;
    #if defined(VERSION_EU_X)
    case 72:
#else
    case 70:
#endif
        status = g_gameSettings.playerSettings;
        status->enabled = 1;
        status[0].slot = 0;
        Player_InitializeProfile((char *)g_localPlayerProfiles);
        PAKInterface_SetScreenPhase(7);
        g_playModeMenuState->nextScreen = 19;
        g_gameSettings.controllerMode = 1;
        break;
    #if defined(VERSION_EU_X)
    case 73:
#else
    case 75:
#endif
        g_playModeMenuState->nextScreen = 27;
        break;
    #if defined(VERSION_EU_X)
    case 75:
#else
    case 71:
#endif
        g_playModeMenuState->nextScreen = 4;
        break;
    #if defined(VERSION_EU_X)
    case 74:
#else
    case 76:
#endif
        g_playModeMenuState->nextScreen = 16;
        break;
    #if defined(VERSION_EU_X)
    case 77:
#else
    case 72:
#endif
        status = g_gameSettings.playerSettings;
        g_playModeMenuState->nextScreen = 7;
        status->enabled = 1;
        status[0].slot = 0;
        if (g_localPlayerProfiles[0].player < 0) {
            Player_InitializeProfileSlot(0);
            for (i = 0; i < 20; i++) {
                Player_SetAchievementFlag7((char *)g_localPlayerProfiles, i);
            }
        }
        g_gameSettings.controllerMode = 3;
        break;
    #if defined(VERSION_EU_X)
    case 78:
#else
    case 74:
#endif
        status = g_gameSettings.playerSettings;
        g_playModeMenuState->nextScreen = 10;
        status->enabled = 1;
        status[0].slot = 0;
        if (g_localPlayerProfiles[0].player < 0) {
            Player_InitializeProfileSlot(0);
        }
        g_gameSettings.controllerMode = 4;
        g_currentStagePreset = 0;
        break;
    default:
        return 0;
    }
    SmpSlider_SetTransitionMode(g_playModeMenuState->music, 2);
    return 0;
}

s32 Frontend_DestroyPlayModeMenu(void) {
    Cache_FreeMemory(g_playModeMenuState);
    g_playModeMenuState = 0;
    return 0;
}

/* unit MENU_CHOICE.CPP */
/* Runs the screen g_playModeMenuState each frame: past stage 1 of g_selectionMessageStage it only calls Tsmos_DeactivateControllerState;
   otherwise it calls Tsmos_ActivateControllerState and, while the opening delay at 0xC runs, counts it down and
   calls SmpSlider_EnableTransition on its menu when it expires; after that, while the menu reports 3, it counts
   the scroll delay at 0x14 down and on expiry scrolls the list at 0x8 back one row, wrapping to
   the menu's own row count, and restarts the delay at 3, and when the menu reports 4 it calls
   MarkMenuEventHandled and leaves through SmXlate_SwitchScreen with the target at 0x18. Returns zero. Adapted
   from Frontend_UpdatePlayerCountScreen with the opening delay added, the scroll delay and target moved and the -1
   target test removed. */

#include "Frontend/playmodemenu_state.h"
#include "Frontend/frontend.h"

s32 Frontend_UpdatePlayModeMenu(void) {
    s32 result;

    if (g_selectionMessageStage >= 2) {
        Tsmos_DeactivateControllerState();
        return 0;
    }
    Tsmos_ActivateControllerState();
    if (g_playModeMenuState->opening > 0) {
        if (--g_playModeMenuState->opening == 0) {
            SmpSlider_EnableTransition(g_playModeMenuState->music);
            return 0;
        }
        return 0;
    }
    switch (result = SmpSlider_GetTransitionMode(g_playModeMenuState->music)) {
    case 3:
        if (--g_playModeMenuState->scrollDelay <= 0) {
            g_playModeMenuState->title->y--;
            if (g_playModeMenuState->title->y + g_playModeMenuState->title->height < 0) {
                g_playModeMenuState->title->y = g_playModeMenuState->music->list->height;
            }
            g_playModeMenuState->scrollDelay = result;
        }
        break;
    case 4:
        MarkMenuEventHandled();
        SmXlate_SwitchScreen(g_playModeMenuState->nextScreen);
        break;
    default:
        return 0;
    }
    return 0;
}

/* unit FRONTEND_DISPATCHPLAYMODEEVENT.CPP */
/* On event 3 with value 0xA, marks the menu event handled, sets the play-mode menu state value to 0x1C and starts the menu's exit transition. Returns zero. */
s32 Frontend_HandlePlayModeShortcut(void *first, void *second, u32 event, s32 value) {
    PlayModeMenuState *state;

    if ((event >> 16) == 3 && value == 10) {
        MarkMenuEventHandled();
        state = g_playModeMenuState;
        state->nextScreen = 28;
        SmpSlider_SetTransitionMode(state->music, 2);
    }
    return 0;
}

/* Marks the menu event handled and does nothing else. Returns zero. */
s32 Frontend_ConsumePlayModeEvent(void) {
    MarkMenuEventHandled();
    return 0;
}

/* Calls the handler registered for event (tables g_playModeEventIds, g_playModeEventKinds, g_playModeEventHandlers). A row matches when its event equals event and its kind equals the actor's kind or is the any-kind wildcard 0x7530. Returns the handler's result, or zero when no row matches. */
s32 Frontend_DispatchPlayModeEvent(void *eventTarget, s32 event, s32 itemId, s32 value, s32 context) {
    PlayModeEventHandler *entry;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;
    struct MenuWidget *actor;

    if (g_playModeEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_playModeEventHandlers;
        index = 0;
        do {
            if (g_playModeEventIds[index].value == event) {
                actor = eventTarget;
                actor_kind = actor->resource;
                table_kind = g_playModeEventKinds[index].value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*entry)(eventTarget, event, itemId, value, context);
                }
            }
            entry += 3;
            index++;
        } while (*entry != 0);
    }
    return 0;
}

/* unit FRONTEND.CPP */
#if defined(VERSION_US)
struct {
    unsigned int words0[1724];
    float floats1[1];
    unsigned int words2[1];
    char text3[4];
    unsigned int words4[307];
    char text5[4];
    unsigned int words6[507];
    char text7[4];
    unsigned int words8[370];
    char text9[8];
    unsigned int words10[226];
    char text11[8];
    unsigned int words12[414];
    char text13[8];
} g_FrontendMenuChoiceRetainedPointerWords = {
    {
        0x00000004, 0x00000000, 0x00235041, 0x00010000, 0x90000000, 0x00000000, 0x0000FF01, 0x00000385,
        (unsigned int)addrLow_Menu_DrawMenuOptionSprite2, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x08000041, 0x0000000A, 0x0000FF01,
        (unsigned int)g_pakOwnerChannelLabelFixed, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, PACKED_CALLBACK_LOW(Timer_UpdateOwnerChannelLabel), 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x0000FFF8,
        0x0000FF01, (unsigned int)g_pakProfileLoadProfileChoiceLabels, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, PACKED_CALLBACK_LOW(Timer_UpdateOperationChoiceLabel), 0x00000000, 0x00000000, 0x00000000, 0x00011001,
        0x00000006, 0x0000FF01, (unsigned int)g_pakOwnerChannelLabelFixed + 0x4, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, PACKED_CALLBACK_LOW(Snapshot_UpdateNoteLabel), PACKED_CALLBACK_LOW(Snapshot_SelectNote), 0x00000000, 0x00000000,
        0x00011001, 0x00000000, 0x0000FF01, (unsigned int)g_pakOwnerChannelLabelFixed + 0x8, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, PACKED_CALLBACK_LOW(Snapshot_UpdateNoteLabel), PACKED_CALLBACK_LOW(Snapshot_SelectNote), 0x00000000,
        0x00000000, 0x00011001, 0x00000000, 0x0000FF01, (unsigned int)g_pakOwnerChannelLabelFixed + 0xC, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, PACKED_CALLBACK_LOW(Snapshot_UpdateNoteLabel), PACKED_CALLBACK_LOW(Snapshot_SelectNote),
        0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x0000FF01, (unsigned int)g_pakOwnerChannelLabelFixed + 0x10, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, PACKED_CALLBACK_LOW(Snapshot_UpdateNoteLabel),
        PACKED_CALLBACK_LOW(Snapshot_SelectNote), 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x0000FF01, (unsigned int)g_pakOwnerChannelLabelFixed + 0x14, (unsigned int)addrLow_Menu_DrawMenuItemLabel2,
        PACKED_CALLBACK_LOW(Snapshot_UpdateNoteLabel), PACKED_CALLBACK_LOW(Snapshot_SelectNote), 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x0000FF01, (unsigned int)g_pakOwnerChannelLabelFixed + 0x18,
        (unsigned int)addrLow_Menu_DrawMenuItemLabel2, PACKED_CALLBACK_LOW(Snapshot_UpdateNoteLabel), PACKED_CALLBACK_LOW(Snapshot_SelectNote), 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x0000FF01,
        (unsigned int)g_pakOwnerChannelLabelFixed + 0x1C, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, PACKED_CALLBACK_LOW(Snapshot_UpdateNoteLabel), PACKED_CALLBACK_LOW(Snapshot_SelectNote), 0x00000000, 0x00000000, 0x00011001, 0x00000000,
        0x0000FF01, (unsigned int)g_pakOwnerChannelLabelFixed + 0x20, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, PACKED_CALLBACK_LOW(Snapshot_UpdateNoteLabel), PACKED_CALLBACK_LOW(Snapshot_SelectNote), 0x00000000, 0x00000000, 0x00011001,
        0x00000000, 0x0000FF01, (unsigned int)g_pakOwnerChannelLabelFixed + 0x24, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, PACKED_CALLBACK_LOW(Snapshot_UpdateNoteLabel), PACKED_CALLBACK_LOW(Snapshot_SelectNote), 0x00000000, 0x00000000,
        0x00011001, 0x00000000, 0x0000FF01, (unsigned int)g_pakOwnerChannelLabelFixed + 0x28, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, PACKED_CALLBACK_LOW(Snapshot_UpdateNoteLabel), PACKED_CALLBACK_LOW(Snapshot_SelectNote), 0x00000000,
        0x00000000, 0x00011001, 0x00000000, 0x0000FF01, (unsigned int)g_pakOwnerChannelLabelFixed + 0x2C, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, PACKED_CALLBACK_LOW(Snapshot_UpdateNoteLabel), PACKED_CALLBACK_LOW(Snapshot_SelectNote),
        0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x0000FF01, (unsigned int)g_pakOwnerChannelLabelFixed + 0x30, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, PACKED_CALLBACK_LOW(Snapshot_UpdateNoteLabel),
        PACKED_CALLBACK_LOW(Snapshot_SelectNote), 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x0000FF01, (unsigned int)g_pakOwnerChannelLabelFixed + 0x34, (unsigned int)addrLow_Menu_DrawMenuItemLabel2,
        PACKED_CALLBACK_LOW(Snapshot_UpdateNoteLabel), PACKED_CALLBACK_LOW(Snapshot_SelectNote), 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x0000FF01, (unsigned int)g_pakOwnerChannelLabelFixed + 0x38,
        (unsigned int)addrLow_Menu_DrawMenuItemLabel2, PACKED_CALLBACK_LOW(Snapshot_UpdateNoteLabel), PACKED_CALLBACK_LOW(Snapshot_SelectNote), 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x0000FF01,
        (unsigned int)g_pakOwnerChannelLabelFixed + 0x3C, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, PACKED_CALLBACK_LOW(Snapshot_UpdateNoteLabel), PACKED_CALLBACK_LOW(Snapshot_SelectNote), 0x00000000, 0x00000000, 0x00011001, 0x00000000,
        0x0000FF01, (unsigned int)g_pakOwnerChannelLabelFixed + 0x40, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, PACKED_CALLBACK_LOW(Snapshot_UpdateNoteLabel), PACKED_CALLBACK_LOW(Snapshot_SelectNote), 0x00000000, 0x00000000, 0x00011001,
        0x00000003, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, PACKED_CALLBACK_LOW(Snapshot_UpdateSpaceLabel), 0x00000000, 0x00000000, 0x00000000,
        0x00010041, 0x0000000A, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Timer_UpdateManagerChannelLabel, PACKED_CALLBACK_LOW(Snapshot_HandleMenuAction), 0x00000000,
        0x00000000, 0x00010041, 0x00000004, 0x0000FF01, (unsigned int)g_pakSaveMenuSnapshotChoiceLabels + 0x4, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Timer_SetManagerHeading, PACKED_CALLBACK_LOW(Snapshot_CloseNoteBrowser),
        0x00000000, 0x0044E2C0, 0x00160000, PACKED_CALLBACK_LOW(Snapshot_BeginProfileLoad), 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, (unsigned int)addrLow_Timer_CheckMenuPakChange, 0x00150000,
        0x00000000, 0x00000000, 0x0044E2C0, 0x00160000, PACKED_CALLBACK_LOW(Snapshot_BeginProfileSave), 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, (unsigned int)addrLow_Timer_CheckMenuPakChange,
        0x00140000, 0x00000000, 0x00000000, 0x0044E2C0, 0x00160000, PACKED_CALLBACK_LOW(Snapshot_BeginBlockLoad), 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2,
        (unsigned int)addrLow_Timer_CheckChangedMenuChannel, 0x00150000, 0x00000000, 0x00000000, 0x0044E2C0, 0x00160000, PACKED_CALLBACK_LOW(Snapshot_BeginSnapshotSave), 0x00000000,
        (unsigned int)addrLow_Menu_DrawMenuEntries2, (unsigned int)addrLow_Timer_CheckChangedMenuChannel, 0x00140000, 0x00000000, 0x00000000, 0x0044E2C0, 0x00160000, PACKED_CALLBACK_LOW(Snapshot_CheckControllerPak),
        0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, (unsigned int)addrLow_Timer_UpdateManagerStatus, 0x00140000, 0x00000000, 0x00000000, 0x00010000, 0x90000000,
        0x00000000, 0x0000FF01, 0x00000385, (unsigned int)addrLow_Menu_DrawMenuOptionSprite2, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x08000801, 0x00000008, 0x0000FF01, (unsigned int)g_pakNoteLabelSlots, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Timer_UpdateAlternatePromptLabel, 0x00000000, 0x00000000,
        0x00000000, 0x00010041, 0x00000014, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, PACKED_CALLBACK_LOW(Timer_FormatPreviewDottedTriple), 0x00000000,
        0x00000000, 0x00000000, 0x00010041, 0x00000005, 0x0000FF01, (unsigned int)g_difficultyHardText + 0xC, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Timer_FormatPreviewDottedTriple,
        0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x0000000A, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)addrLow_Menu_DrawMenuItemLabel2,
        (unsigned int)addrLow_Timer_UpdatePreviewDepthLabel, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000000, 0x0000FF01, (unsigned int)g_difficultyHardText + 0x4,
        (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Timer_FormatPreviewPageCount, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000000, 0x0000FF01,
        (unsigned int)g_difficultyHardText + 0x8, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Timer_FormatPreviewValue, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000014,
        0x0000FF01, (unsigned int)g_pakAlternateActionLabel, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Timer_UpdateAlternateActionLabel, 0x00000000, 0x00000000, 0x00000000, 0x00010040,
        0x007D000A, 0x00010000, (unsigned int)g_captureFlagVictimFollowupMessage + 0xC, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, 0x00408870, 0x00000000, 0x00000000,
        0x00024040, 0x000A0000, 0xFF000000, (unsigned int)g_captureFlagVictimFollowupMessage + 0x10, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, (unsigned int)addrLow_Timer_OpenSelectedPrompt, 0x00000000,
        0x0044E68C, 0x000A0000, (unsigned int)addrLow_Timer_EnableAlternatePrompt, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00000000, 0x00080000, 0x00000000,
        0x00000000, 0x0044E68C, 0x000A0000, (unsigned int)addrLow_Timer_DisableAlternatePrompt, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00000000, 0x00090000,
        0x00000000, 0x00000000, 0x00010000, 0x90000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)addrLow_Menu_DrawMenuOptionSprite2,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x08000021, 0x00000008, 0x0000FF01, (unsigned int)g_pakPreviewKindLabelProfile,
        (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Timer_UpdatePreviewKindLabel, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000032, 0x0000FF01,
        (unsigned int)g_unlockedLevelResultLabel, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Status_FormatRightAlignedPreviewName, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000002,
        0x0000FF01, (unsigned int)g_pakStatusLabelTemplate, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Status_UpdateStatusText, 0x00000000, 0x00000000, 0x00000000, 0x00010041,
        0x00000002, 0x0000FF01, (unsigned int)&g_pakStatusLabelTemplate[0x4], (unsigned int)addrLow_Menu_DrawMenuItemLabel2, PACKED_CALLBACK_LOW(Pak_FormatPreviewFourDigitValue), 0x00000000, 0x00000000, 0x00000000,
        0x00010041, 0x00000002, 0x0000FF01, (unsigned int)&g_pakStatusLabelTemplate[0x8], (unsigned int)addrLow_Menu_DrawMenuItemLabel2, PACKED_CALLBACK_LOW(Snapshot_UpdateThresholdLabel), 0x00000000, 0x00000000,
        0x00000000, 0x00010041, 0x00000010, 0x0000FF01, (unsigned int)g_pakAlternateActionLabel, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Pak_UpdateProfileActionLabel, 0x00000000,
        0x00000000, 0x00000000, 0x00010040, 0x007D000A, 0x00010000, (unsigned int)g_captureFlagVictimFollowupMessage + 0xC, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000,
        (unsigned int)addrLow_Pak_ConfirmProfileOrDeleteNote, 0x00000000, 0x00000000, 0x00024040, 0x000A0000, 0xFF000000, (unsigned int)g_captureFlagVictimFollowupMessage + 0x10, (unsigned int)addrLow_Menu_DrawMenuItemLabel2,
        0x00000000, (unsigned int)addrLow_Pak_OpenProfileActionPrompt, 0x00000000, 0x0044E83C, 0x00090000, (unsigned int)addrLow_Timer_EnableProfilePreview, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2,
        0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044E83C, 0x00090000, (unsigned int)addrLow_Timer_ClearProfilePreview, 0x00000000,
        (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00000000, 0x00080000, 0x00000000, 0x00000000, 0x0044E83C, 0x00090000, (unsigned int)addrLow_Timer_EnableAlternatePrompt_Objectdata,
        0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00000000, 0x00080000, 0x00000000, 0x00000000, 0x00010000, 0x90000000,
        0x00000000, 0x0000FF01, 0x00000385, (unsigned int)addrLow_Menu_DrawMenuOptionSprite2, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x08000021, 0x00000008, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Pak_SelectPromptActionHeading, 0x00000000, 0x00000000,
        0x00000000, 0x00010041, 0x0000001E, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, PACKED_CALLBACK_LOW(Pak_SelectPromptTextGroupOne), 0x00000000,
        0x00000000, 0x00000000, 0x00010041, 0x00000005, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, PACKED_CALLBACK_LOW(Pak_SelectPromptTextGroupTwo),
        0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000005, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)addrLow_Menu_DrawMenuItemLabel2,
        PACKED_CALLBACK_LOW(Pak_SelectPromptTextGroupThree), 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000005, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel,
        (unsigned int)addrLow_Menu_DrawMenuItemLabel2, PACKED_CALLBACK_LOW(Pak_SelectPromptTextGroupFour), 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000005, 0x0000FF01,
        (unsigned int)g_unlockedLevelResultLabel, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, PACKED_CALLBACK_LOW(Pak_SelectPromptTextGroupFive), 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000019,
        0x0000FF01, (unsigned int)g_SelectModalPromptLabelStateOtherText, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Pak_SelectModalPromptLabel, (unsigned int)addrLow_Pak_ClosePromptByKind, 0x00000000, 0x0044E9EC, 0x00080000,
        (unsigned int)addrLow_Pak_SelectPromptKindZero, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044E9EC,
        0x00080000, PACKED_CALLBACK_LOW(Pak_SelectPromptKindOne), 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00000000, 0x00070000, 0x00000000, 0x00000000,
        0x0044E9EC, 0x00080000, PACKED_CALLBACK_LOW(Pak_SelectPromptKindTwo), 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00000000, 0x00070000, 0x00000000,
        0x00000000, 0x0044E9EC, 0x00080000, PACKED_CALLBACK_LOW(Pak_SelectPromptKindThree), 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00000000, 0x00070000,
        0x00000000, 0x00000000, 0x0044E9EC, 0x00080000, PACKED_CALLBACK_LOW(Pak_SelectPromptKindFour), 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00000000,
        0x00070000, 0x00000000, 0x00000000, 0x0044E9EC, 0x00080000, PACKED_CALLBACK_LOW(Pak_SelectPromptKindFive), 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2,
        0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044E9EC, 0x00080000, PACKED_CALLBACK_LOW(Pak_SelectPromptKindSix), 0x00000000,
        (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044E9EC, 0x00080000, PACKED_CALLBACK_LOW(Pak_SelectPromptKindSeven),
        0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044E9EC, 0x00080000,
        PACKED_CALLBACK_LOW(Pak_SelectPromptKindEight), 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044E9EC,
        0x00080000, PACKED_CALLBACK_LOW(Pak_SelectPromptKindNine), 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00000000, 0x00070000, 0x00000000, 0x00000000,
        0x0044E9EC, 0x00080000, PACKED_CALLBACK_LOW(Pak_SelectPromptKindNinePending), 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00000000, 0x00070000, 0x00000000,
        0x00000000, 0x0044E9EC, 0x00080000, PACKED_CALLBACK_LOW(Pak_SelectPromptKindTen), 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00000000, 0x00070000,
        0x00000000, 0x00000000, 0x0044E9EC, 0x00080000, PACKED_CALLBACK_LOW(Pak_SelectPromptKindEleven), 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00000000,
        0x00070000, 0x00000000, 0x00000000, 0x0044E9EC, 0x00080000, PACKED_CALLBACK_LOW(Pak_SelectPromptKindTwelve), 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2,
        0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044E9EC, 0x00080000, PACKED_CALLBACK_LOW(Pak_SelectPromptKindFifteen), 0x00000000,
        (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044E9EC, 0x00080000, PACKED_CALLBACK_LOW(Pak_SelectPromptKindThirteen),
        0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x0044E9EC, 0x00080000,
        PACKED_CALLBACK_LOW(Pak_SelectPromptKindFourteen), 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00000000, 0x00070000, 0x00000000, 0x00000000, 0x00010000,
        0x90000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)addrLow_Menu_DrawMenuOptionSprite2, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x08000021, 0x00000008, 0x0000FF01, (unsigned int)&g_pakPromptLineCells[PAK_PROMPT_ROW_KIND15][4][0x4], (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00010041, 0x00000028, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Pak_SelectOperationHeading,
        0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000000, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)addrLow_Menu_DrawMenuItemLabel2,
        (unsigned int)addrLow_Pak_SelectOperationDescription, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000000, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel,
        (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Pak_FormatOperationChannelLabel, 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000014, 0x0000FF01,
        (unsigned int)&g_pakChannelLabelTexts + 0x4, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, (unsigned int)addrLow_Pak_OpenPakChannel, 0x00000000, 0x00000000, 0x00010041, 0x00000005,
        0x0000FF01, (unsigned int)&g_pakChannelLabelTexts + 0x8, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, (unsigned int)addrLow_Pak_OpenPakStatusPrompt, 0x00000000, 0x00000000, 0x00010041,
        0x00000005, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Pak_SelectPakLoadHeading, (unsigned int)addrLow_Pak_CancelPakAction, 0x00000000, 0x0044ED70,
        0x00080000, (unsigned int)addrLow_Pak_EnableOperationHeading, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, (unsigned int)addrLow_Pak_CheckOperationPakChange, 0x00070000, 0x00000000, 0x00000000,
        0x0044ED70, 0x00080000, PACKED_CALLBACK_LOW(Pak_FormatOperationChannelLabel), 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, (unsigned int)addrLow_Pak_CheckOperationPakChange, 0x00050000, 0x00000000,
        0x00000000, 0x00010000, 0x90000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)addrLow_Menu_DrawMenuOptionSprite2, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x08000801, 0x00000008, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)addrLow_Menu_DrawMenuItemLabel2,
        PACKED_CALLBACK_LOW(Pak_SelectPakOperationTextOne), 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000023, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel,
        (unsigned int)addrLow_Menu_DrawMenuItemLabel2, PACKED_CALLBACK_LOW(Frontend_SelectPakOperationTextTwo), 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000004, 0x0000FF01,
        (unsigned int)g_unlockedLevelResultLabel, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, PACKED_CALLBACK_LOW(Frontend_SelectPakOperationTextThree), 0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000004,
        0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, PACKED_CALLBACK_LOW(Frontend_SelectPakOperationTextFour), 0x00000000, 0x00000000, 0x00000000, 0x00010041,
        0x00000004, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, PACKED_CALLBACK_LOW(Frontend_SelectPakOperationTextFive), 0x00000000, 0x00000000, 0x00000000,
        0x00012001, 0x00000023, 0x0000FF01, (unsigned int)g_pakConfirmationDefaultLabel, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Frontend_SelectPakConfirmationLabel, (unsigned int)addrLow_Pak_ConfirmPendingOperation, 0x00000000,
        0x00000000, 0x00012001, 0x00000005, 0x0000FF01, (unsigned int)s_nodeDefaultFieldText, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Frontend_SelectPakActionLabel, (unsigned int)addrLow_Timer_CancelPendingOperation,
        0x00000000, 0x0044EED8, 0x00080000, (unsigned int)addrLow_Pak_SelectPakOperationZero, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, (unsigned int)addrLow_Pak_CheckPakActionChange, 0x00070000,
        0x00000000, 0x00000000, 0x0044EED8, 0x00080000, PACKED_CALLBACK_LOW(Pak_SelectPakOperationOne), 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, (unsigned int)addrLow_Pak_CheckPakActionChange,
        0x00070000, 0x00000000, 0x00000000, 0x0044EED8, 0x00080000, PACKED_CALLBACK_LOW(Pak_SelectPakOperationTwo), 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2,
        (unsigned int)addrLow_Pak_CheckPakActionChange, 0x00070000, 0x00000000, 0x00000000, 0x0044EED8, 0x00080000, PACKED_CALLBACK_LOW(Pak_SelectPakOperationThree), 0x00000000,
        (unsigned int)addrLow_Menu_DrawMenuEntries2, (unsigned int)addrLow_Pak_CheckPakActionChange, 0x00070000, 0x00000000, 0x00000000, 0x0044EED8, 0x00080000, PACKED_CALLBACK_LOW(Pak_SelectPakOperationFour),
        0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, (unsigned int)addrLow_Pak_CheckPakActionChange, 0x00070000, 0x00000000, 0x00000000, 0x1643524F, (unsigned int)&g_encodedCheatTextAndHeaderUs.text[156],
        (unsigned int)&g_optionFlagsChangedMessageText + 0x18, 0x00000020, 0x00000001, (unsigned int)&g_encodedCheatTextAndHeaderUs.text[140], (unsigned int)&g_optionFlagsChangedMessageText + 0x20, 0x00000080, 0x00000001, (unsigned int)&g_encodedCheatTextAndHeaderUs.text[132],
        (unsigned int)&g_optionFlagsChangedMessageText + 0x24, 0x00000100, 0x00000001, (unsigned int)&g_encodedCheatTextAndHeaderUs.text[120], (unsigned int)&g_optionFlagsChangedMessageText + 0x1C, 0x00000040, 0x00000001, (unsigned int)&g_encodedCheatTextAndHeaderUs.text[108],
        (unsigned int)&g_optionFlagsChangedMessageText + 0x28, 0x00000200, 0x00000001, (unsigned int)&g_encodedCheatTextAndHeaderUs.text[88], (unsigned int)&g_optionFlagsChangedMessageText + 0x2C, 0x00000400, 0x00000001, (unsigned int)&g_encodedCheatTextAndHeaderUs.text[76],
        (unsigned int)&g_optionFlagsChangedMessageText + 0x30, 0x00000800, 0x00000001, (unsigned int)&g_encodedCheatTextAndHeaderUs.text[68], (unsigned int)&g_optionFlagsChangedMessageText + 0x34, 0x00001000, 0x00000001, (unsigned int)&g_encodedCheatTextAndHeaderUs.text[56],
        (unsigned int)&g_optionFlagsChangedMessageText + 0x3C, 0x00004000, 0x00000001, (unsigned int)&g_encodedCheatTextAndHeaderUs.text[44], (unsigned int)&g_optionFlagsChangedMessageText + 0x40, 0x00008000, 0x00000001, (unsigned int)&g_encodedCheatTextAndHeaderUs.text[20],
        (unsigned int)&g_encodedCheatCode[0x30], 0xFFFFFFFF, 0x00000001, (unsigned int)&g_encodedCheatTextAndHeaderUs.text[0], (unsigned int)&g_encodedCheatCode[0x4C], 0x0400C7E0, 0x00000001, 0x00010000,
        0x50000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)addrLow_Menu_DrawMenuOptionSprite2, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x08000021, 0x00000008, 0x0000FF01, (unsigned int)g_captureFlagVictimFollowupMessage + 0x20, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00210041, 0x00000014, 0x0000FF01, (unsigned int)&g_encodedCheatCode[0x18], (unsigned int)addrLow_Encoded_DrawTextEntryCursor, (unsigned int)addrLow_Encoded_UpdateTextEntryCursor,
        (unsigned int)addrLow_Encoded_TextEntryReturnZero_PlaymodeRegionalStorage3, 0x00000000, 0x00000000, 0x00010050, 0x00500014, 0x0601FF07, (unsigned int)g_creditsLocalizedLines + 0x8, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText,
        0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01FE07, (unsigned int)g_creditsLocalizedLines + 0x10,
        (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01FD07,
        (unsigned int)g_creditsLocalizedLines + 0x18, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000, 0x00000000, 0x00024050, 0x00080000,
        0xFF01FC07, (unsigned int)g_creditsLocalizedLines + 0x20, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000, 0x00000000, 0x00024050,
        0x00080000, 0xFF01FB07, (unsigned int)g_creditsLocalizedLines + 0x28, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000, 0x00000000,
        0x00024050, 0x00080000, 0xFF01FA07, (unsigned int)g_creditsLocalizedLines + 0x30, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000,
        0x00000000, 0x00024050, 0x00080000, 0xFFFAF907, (unsigned int)g_creditsLocalizedLines + 0x38, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter,
        0x00000000, 0x00000000, 0x00010050, 0x00500008, 0x0601F907, (unsigned int)g_creditsLocalizedLines + 0x40, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F907, (unsigned int)g_creditsLocalizedLines + 0x48, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText,
        0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F907, (unsigned int)g_creditsLocalizedLines + 0x50,
        (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F907,
        (unsigned int)g_creditsLocalizedLines + 0x58, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000, 0x00000000, 0x00024050, 0x00080000,
        0xFF01F907, (unsigned int)g_creditsLocalizedLines + 0x60, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000, 0x00000000, 0x00024050,
        0x00080000, 0xFF01F907, (unsigned int)g_creditsLocalizedLines + 0x68, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000, 0x00000000,
        0x00024050, 0x00080000, 0xFFFAF907, (unsigned int)g_creditsLocalizedLines + 0x70, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000,
        0x00000000, 0x00010050, 0x00500008, 0x0601F907, (unsigned int)g_creditsLocalizedLines + 0x78, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter,
        0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F907, (unsigned int)g_creditsLocalizedLines + 0x80, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F907, (unsigned int)g_creditsLocalizedLines + 0x88, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText,
        0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F907, (unsigned int)g_creditsLocalizedLines + 0x90,
        (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F907,
        (unsigned int)g_creditsLocalizedLines + 0x98, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000, 0x00000000, 0x00024050, 0x00080000,
        0xFF01F907, (unsigned int)g_creditsLocalizedLines + 0xA0, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000, 0x00000000, 0x00024050,
        0x00080000, 0xFFFAF907, (unsigned int)g_creditsLocalizedLines + 0xA8, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000, 0x00000000,
        0x00010050, 0x00500008, 0x0601F908, (unsigned int)g_creditsLocalizedLines + 0xB0, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000,
        0x00000000, 0x00024050, 0x00080000, 0xFF01F907, (unsigned int)g_creditsLocalizedLines + 0xB8, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter,
        0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F906, (unsigned int)g_creditsLocalizedLines + 0xC0, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000,
        (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F905, (unsigned int)g_creditsLocalizedLines + 0xC8, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText,
        0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F904, (unsigned int)g_creditsLocalizedLines + 0xD0,
        (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Encoded_InsertTextEntryCharacter, 0x00000000, 0x00000000, 0x00024050, 0x00080000, 0xFF01F903,
        (unsigned int)g_creditsLocalizedLines + 0x130, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Encoded_DeletePreviousTextEntryCharacter, 0x00000000, 0x00000000, 0x00024050, 0x00080000,
        0xFFFAF902, (unsigned int)g_creditsLocalizedLines + 0x138, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, (unsigned int)addrLow_Encoded_ApplyCheatCode, 0x00000000, 0x00000000, 0x00011001,
        0x00000014, 0x00000000, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Encoded_SetTextEntryResultLabel, 0x00000000, 0x00000000, 0x00000000,
        0x00310201, 0x00000018, 0x0000FEE2, (unsigned int)g_captureFlagVictimFollowupMessage + 0x30, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, (unsigned int)addrLow_Menu_TryCreateMenu, 0x00000000,
        0x0044F170, 0x00210000, (unsigned int)addrLow_Encoded_ResetTextEntryResult, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00000000, 0x00020000, 0x00000000,
        0x00000000, 0x00010000, 0x50000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)addrLow_Menu_DrawMenuOptionSprite2, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x08000021, 0x00000008, 0x0000FF01, (unsigned int)g_captureFlagVictimFollowupMessage + 0x14, (unsigned int)addrLow_Menu_DrawMenuItemLabel2,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00411001, 0x0000000C, 0x0000FF01, (unsigned int)g_menuOptionInvincibilityDisabledText,
        (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Option_UpdateOptionInvincibilityItem, (unsigned int)addrLow_Pak_ToggleTextChoice, 0x00000000, 0x00000000, 0x00411001, 0x00000000, 0x0000FF01,
        (unsigned int)g_menuOptionInfiniteLivesDisabledText, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Option_UpdateOptionInfiniteLivesItem, (unsigned int)addrLow_Option_ToggleOptionInfiniteLives, 0x00000000, 0x00000000, 0x00411001, 0x00000000,
        0x0000FF01, (unsigned int)g_menuOptionAllWeaponsDisabledText, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Encoded_HandleUnlockedLevelSelection_Objectdata, (unsigned int)addrLow_Option_ToggleOptionAllWeapons, 0x00000000, 0x00000000, 0x00411001,
        0x00000000, 0x0000FF01, (unsigned int)g_menuOptionUnlimitedAmmoDisabledText, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Option_UpdateOptionUnlimitedAmmoItem, (unsigned int)addrLow_Option_ToggleOptionUnlimitedAmmo, 0x00000000, 0x00000000,
        0x00411001, 0x00000000, 0x0000FF01, (unsigned int)g_menuOptionAllSpecialObjectsDisabledText, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Option_UpdateOptionAllSpecialObjectsItem, (unsigned int)addrLow_Option_ToggleOptionAllSpecialObjects, 0x00000000,
        0x00000000, 0x00411001, 0x00000000, 0x0000FF01, (unsigned int)g_menuOptionBigHeadModeDisabledText, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Option_UpdateOptionBigHeadModeItem, (unsigned int)addrLow_Option_ToggleOptionBigHeadMode,
        0x00000000, 0x00000000, 0x00411001, 0x00000000, 0x0000FF01, (unsigned int)g_menuOptionTinyModeDisabledText, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Option_UpdateOptionTinyModeItem,
        (unsigned int)addrLow_Option_ToggleOptionTinyMode, 0x00000000, 0x00000000, 0x00411001, 0x00000000, 0x0000FF01, (unsigned int)g_menuOptionBigHandsFeetModeDisabledText, (unsigned int)addrLow_Menu_DrawMenuItemLabel2,
        (unsigned int)addrLow_Option_UpdateOptionBigHandsFeetModeItem, (unsigned int)addrLow_Option_ToggleOptionBigHandsFeetMode, 0x00000000, 0x00000000, 0x00411001, 0x00000000, 0x0000FF01, (unsigned int)g_menuOptionStickModeDisabledText,
        (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Option_UpdateOptionStickModeItem, (unsigned int)addrLow_Option_ToggleOptionStickMode, 0x00000000, 0x00000000, 0x00411001, 0x00000000, 0x0000FF01,
        (unsigned int)g_menuOptionPenAndInkModeDisabledText, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Option_UpdateOptionPenAndInkModeItem, (unsigned int)addrLow_Option_ToggleOptionPenAndInkMode, 0x00000000, 0x00000000, 0x00411001, 0x00000000,
        0x0000FF01, (unsigned int)g_menuOptionGouraudModeDisabledText, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Option_UpdateOptionBit10Item_PlaymodeRegionalStorage3, (unsigned int)addrLow_Option_ToggleOptionGouraudMode, 0x00000000, 0x00000000, 0x00411001,
        0x00000000, 0x0000FF01, (unsigned int)g_menuOptionJuansCheatDisabledText, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Option_UpdateOptionJuansCheatItem, (unsigned int)addrLow_Option_ToggleOptionJuansCheat, 0x00000000, 0x00000000,
        0x00411001, 0x00000000, 0x0000FF01, (unsigned int)g_menuOptionZachAttackCheatDisabledText, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Option_UpdateOptionZachAttackCheatItem, (unsigned int)addrLow_Option_ToggleOptionZachAttackCheat, 0x00000000,
        0x00000000, 0x00411001, 0x00000000, 0x0000FF01, (unsigned int)g_menuOptionAllMapDisabledText, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Option_UpdateOptionBit13Item_PlaymodeRegionalStorage3, (unsigned int)addrLow_Option_ToggleOptionAllMap,
        0x00000000, 0x00000000, 0x00411001, 0x00000000, 0x0000FF01, (unsigned int)g_menuOptionBlackoutDisabledText, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Option_UpdateOptionBlackoutItem,
        (unsigned int)addrLow_Option_ToggleOptionBlackout, 0x00000000, 0x00000000, 0x00411001, 0x00000000, 0x0000FF01, (unsigned int)g_menuOptionFrootyStripesDisabledText, (unsigned int)addrLow_Menu_DrawMenuItemLabel2,
        (unsigned int)addrLow_Option_UpdateOptionFrootyStripesItem, (unsigned int)addrLow_Option_ToggleOptionFrootyStripes, 0x00000000, 0x00000000, 0x00411001, 0x00000000, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel,
        (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Menu_SetSelectedLevelLabel, (unsigned int)addrLow_Encoded_HandleUnlockedLevelSelection, 0x00000000, 0x00000000, 0x00000201, 0x000000C0, 0x0000FF01,
        (unsigned int)g_captureFlagVictimFollowupMessage + 0x30, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, (unsigned int)addrLow_Menu_TryCreateMenu, 0x00000000, 0x0044F638, 0x00140000, 0x0043C730,
        0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00000000, 0x00130000, 0x00000000, 0x00000000, 0x00000100, 0x00000000,
        0x00000021, 0x00000000, 0x0000FF01, (unsigned int)g_captureFlagVictimFollowupMessage + 0x34, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00010081, 0x00000028, 0x0000FF01, (unsigned int)g_captureFlagVictimFollowupMessage + 0xC, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, (unsigned int)addrLow_Menu_ForwardRulesLock,
        0x00000000, 0x00000000, 0x00010081, 0x00000000, 0x0000FF01, (unsigned int)g_captureFlagVictimFollowupMessage + 0x10, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000,
        (unsigned int)addrLow_Menu_HandleSessionOptionPage, 0x00000000, 0x0044F930, 0x00030000, 0x00000000, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00000000,
        0x00010000, 0x00000000, 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x00000000, (unsigned int)&g_profileMenuLabelWords[0xC],
        (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x00000000,
        (unsigned int)&g_profileMenuLabelWords[0x10], (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00011001, 0x00000000,
        0x00000000, (unsigned int)&g_profileMenuLabelWords[0x14], (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00011001,
        0x00000000, 0x00000000, (unsigned int)&g_profileMenuLabelWords[0x18], (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00011001, 0x00000000, 0x00000000, (unsigned int)&g_profileMenuLabelWords[0x1C], (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00011001, 0x00000000, 0x00000000, (unsigned int)&g_profileMenuLabelWords[0x20], (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00011001, 0x00000000, 0x00000000, (unsigned int)&g_profileMenuLabelWords[0x24], (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00010041, 0x00000005, 0x00000000, (unsigned int)&g_profileMenuLabelWords[0x8], (unsigned int)addrLow_Menu_DrawMenuItemLabel2,
        0x00000000, (unsigned int)addrLow_CMenuProfile_ResetPlayerControllerProfile, 0x00000000, 0x0044F9C0, 0x00080000, 0x00000000, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2,
        (unsigned int)addrLow_CMenuProfile_HasRoundProgress, 0x00070000, 0x00000000, 0x0044FBB8, 0x00000000, 0x00011001, 0x00000000, 0x0000FF02,
        (unsigned int)&g_packedButtonOptionStepText[0x14], (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, (unsigned int)addrLow_CMenuProfile_OpenPrimaryProfileMenu_PlaymodeRegionalStorage3, 0x00000000, 0x00000000, 0x00010101, 0x00000008,
        0x00000000, (unsigned int)&g_packedButtonOptionStepText[0x18], (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_CMenuProfile_BindSelectedDebugField, 0x00000000, 0x00000000, 0x00000000, 0x00411001,
        0x00000008, 0x0000FE01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_CMenuProfile_FormatProfileQuantityLabel, (unsigned int)addrLow_CMenuProfile_AdjustControllerSelection, 0x00000000, 0x00000000,
        0x00411001, 0x00000002, 0x0000FF01, (unsigned int)g_profileModeZeroLabel, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Option_UpdateOptionBit7Item_Objectdata, (unsigned int)addrLow_CMenuProfile_ToggleProfileMode, 0x00000000,
        0x00000000, 0x00010041, 0x00000005, 0x0000FF01, (unsigned int)&g_profileMenuLabelWords[0x8], (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, (unsigned int)addrLow_CMenuProfile_OpenSecondaryProfileMenu_PlaymodeRegionalStorage3,
        0x00000000, 0x0044FB04, 0x00050000, 0x00000000, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, (unsigned int)addrLow_CMenuProfile_HasSavedRoundProgress, 0x00040000,
        0x00000000, 0x0044FC78, 0x00000460, 0x0000000B, 0x00000000, 0x00000000, 0xC2480000, 0xC4610000,
        0x40000000, 0x40000000, 0x40000000, 0x00000032, 0x00000050, 0x3DB2B8C4, 0x00010000, 0x30000000,
        0x00000000, 0x0000FF01, 0x00000387, (unsigned int)addrLow_Menu_DrawMenuOptionSprite2, 0x00000000, 0x00000000, 0x00000000, 0x00030000,
        0x00410021, 0x00000000, 0x0000FF01, 0x0044FBDC, (unsigned int)addrLow_Menu_DrawMenuModel, (unsigned int)addrLow_CMenuProfile_GameSpeedReturnZero_PlaymodeRegionalStorage3, (unsigned int)addrLow_CMenuProfile_UpdatePlayerAnimationChoice, 0x00000000,
        0x00000000, 0x00010081, 0x00000019, 0x0000FF01, (unsigned int)&g_packedButtonOptionStepText[0x10], (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_CMenuProfile_ProfileModeReturnZero_PlaymodeRegionalStorage3, (unsigned int)addrLow_CMenuProfile_OpenTimedPlayerDialog,
        0x00000000, 0x0044FC0C, 0x00030000, (unsigned int)addrLow_CMenuProfile_EnableOwnerControllerPak, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, (unsigned int)addrLow_CMenuProfile_HasProfileRoundProgress, 0x00010000,
        0x00000000, 0x00000000, 0x0044FC0C, 0x00030000, (unsigned int)addrLow_CMenuProfile_EnableControllerPakAndClearState, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, (unsigned int)addrLow_CMenuProfile_HasProfileRoundProgress,
        0x00010000, 0x00000000, 0x00000000, 0x00010000, 0x30000000, 0x00000000, 0x0000FF01, 0x00000387,
        (unsigned int)addrLow_Menu_DrawMenuOptionSprite2, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00010081, 0x00000000, 0x0000FF01,
        (unsigned int)&g_profileMenuLabelWords[0x2C], (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00010101, 0x0000000C,
        0x0000FF01, (unsigned int)&g_profileMenuLabelWords[0x30], (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, (unsigned int)addrLow_CMenuProfile_OpenPrimaryPlayerDialog, 0x00000000, 0x00000000, 0x00010101,
        0x00000000, 0x0000FF01, (unsigned int)&g_profileMenuLabelWords[0x34], (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, (unsigned int)addrLow_CMenuProfile_OpenAlternatePlayerDialog, 0x00000000, 0x0044FCC0,
        0x00040000, 0x00000000, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, (unsigned int)addrLow_CMenuProfile_HasDialogRoundProgress, 0x00020000, 0x00000000, 0x00000000,
        0xBF000000, 0xBECCCCCD, 0xBE99999A, 0xBE4CCCCD, 0xBDCCCCCD, 0x00000000, 0x3DCCCCCD, 0x3E4CCCCD,
        0x3E99999A, 0x3ECCCCCD, 0x3F000000, 0x3F19999A, 0x3F333333, 0x3F4CCCCD, 0x3F666666, 0x3F800000,
    },
    { 0.7f },
    {
        0x3F4CCCCD, 0x3F666666, 0x3F800000, 0x00010000, 0x10000000, 0x00000000, 0x0000FF01, 0x00000385,
    },
    "\?fff",
    {
        0x3F800000, 0x00010000, 0x10000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)addrLow_Menu_DrawMenuOptionSprite2, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x08000201, 0x0000000C, 0x0000FF01, (unsigned int)&g_defaultPlayerNames[3] + 0xC0, (unsigned int)addrLow_Menu_DrawMenuItemLabel2,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00410041, 0x0000001E, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel,
        (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Items_SelectToggleRowTextGerman, PACKED_CALLBACK_LOW(Initial_OpenDialogWithControllerPak), 0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01,
        (unsigned int)g_unlockedLevelResultLabel, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Items_SelectToggleRowTextGerman, PACKED_CALLBACK_LOW(Initial_OpenDialogWithControllerPak), 0x00000000, 0x00000000, 0x00410041, 0x00000000,
        0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Items_SelectToggleRowTextGerman, PACKED_CALLBACK_LOW(Initial_OpenDialogWithControllerPak), 0x00000000, 0x00000000, 0x00410041,
        0x00000000, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Items_SelectToggleRowTextGerman, PACKED_CALLBACK_LOW(Initial_OpenDialogWithControllerPak), 0x00000000, 0x00000000,
        0x00410041, 0x00000000, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Items_SelectToggleRowTextGerman, PACKED_CALLBACK_LOW(Initial_OpenDialogWithControllerPak), 0x00000000,
        0x00000000, 0x00410041, 0x00000000, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Items_SelectToggleRowTextGerman, PACKED_CALLBACK_LOW(Initial_OpenDialogWithControllerPak),
        0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Items_SelectToggleRowTextGerman,
        PACKED_CALLBACK_LOW(Initial_OpenDialogWithControllerPak), 0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)addrLow_Menu_DrawMenuItemLabel2,
        (unsigned int)addrLow_Items_SelectToggleRowTextGerman, PACKED_CALLBACK_LOW(Initial_OpenDialogWithControllerPak), 0x00000000, 0x00000000, 0x00010201, 0x0000002D, 0x0000FF01, (unsigned int)g_captureFlagVictimFollowupMessage + 0x30,
        (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, (unsigned int)addrLow_Menu_TryCreateMenu, 0x00000000, 0x0044FDB4, 0x000B0000, 0x00000000, 0x00000000,
        (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00000000, 0x000A0000, 0x00000000, 0x0044FFF4, 0x00010000, 0x10000000, 0x00000000,
        0x0000FF01, 0x00000385, (unsigned int)addrLow_Menu_DrawMenuOptionSprite2, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x08000021,
        0x00000008, 0x0000FF01, (unsigned int)&g_defaultPlayerNames[3] + 0x14, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00010081, 0x00000000, 0x0000FF01, (unsigned int)&g_defaultPlayerNames[3] + 0xC0, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, (unsigned int)addrLow_Initial_OpenMatchSetupMenu_PlaymodeRegionalStorage3, 0x00000000,
        0x00000000, 0x00010201, 0x00000038, 0x0000FF01, (unsigned int)g_captureFlagVictimFollowupMessage + 0x30, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, (unsigned int)addrLow_Menu_TryCreateMenu,
        0x00000000, 0x0044FF64, 0x00040000, 0x00000000, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00000000, 0x00020000,
        0x00000000, 0x00450258, 0x00010000, 0x10000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)addrLow_Menu_DrawMenuOptionSprite2,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x08000021, 0x00000008, 0x0000FF01, (unsigned int)&g_defaultPlayerNames[3] + 0x4,
        (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00010081, 0x00000036, 0x0000FF01,
        (unsigned int)&g_defaultPlayerNames[3] + 0x8, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, (unsigned int)addrLow_Initial_OpenDialogWithControllerPak, 0x00000000, 0x00000000, 0x00010081, 0x00000004,
        0x0000FF01, (unsigned int)&g_defaultPlayerNames[3] + 0xC, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, (unsigned int)addrLow_Initial_OpenDialogAfterTimerReset, 0x00000000, 0x00000000, 0x00010201,
        0x00000049, 0x0000FF01, (unsigned int)&g_packedButtonOptionStepText[0x8], (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, (unsigned int)addrLow_Initial_RequestTransitionWithPakDisabled, 0x00000000, 0x00450018,
        0x00050000, (unsigned int)addrLow_Initial_ProbeMenuControllerPak, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00000000, 0x00020000, 0x00000000, 0x00000000,
        0x00450018, 0x00050000, (unsigned int)addrLow_Initial_EnableMenuControllerPak, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00000000, 0x00020000, 0x00000000,
        0x00000000, 0x00010000, 0x10000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)addrLow_Menu_DrawMenuOptionSprite2, 0x00000000,
        0x00000000, 0x00000000, 0x00450114, 0x00010000, 0x00000000, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00000000,
        0x00020000, 0x00000000, 0x00450258, 0x00010000, 0x10000000, 0x00000000, 0x0000FF01, 0x00000384,
        (unsigned int)addrLow_Menu_DrawMenuOptionSprite2, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000081, 0x0000001E, 0x0000FF01,
        (unsigned int)&g_defaultPlayerNames[3] + 0x4, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, (unsigned int)addrLow_Initial_SelectInitialController, 0x00000000, 0x00000000, 0x00010081, 0x0000000C,
        0x0000FF01, (unsigned int)&g_defaultPlayerNames[3] + 0x10, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Initial_UpdateMultiplayerAvailability, (unsigned int)addrLow_Initial_OpenLocalPlayerSetup, 0x00000000, 0x00000000, 0x00010081,
        0x0000000C, 0x0000FF01, (unsigned int)g_captureFlagVictimFollowupMessage + 0x20, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, (unsigned int)addrLow_Initial_OpenDialogTopRow_PlaymodeRegionalStorage3, 0x00000000, 0x00000000,
        0x00010081, 0x0000000C, 0x0000FF01, (unsigned int)&g_menuToggleTorpedoLauncherDisabledText + 0x2C, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, (unsigned int)addrLow_Initial_OpenDialogMiddleRow_PlaymodeRegionalStorage3, 0x00000000,
        0x00000000, 0x00010081, 0x0000000C, 0x0000FF01, (unsigned int)&g_menuToggleTorpedoLauncherDisabledText + 0x28, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, (unsigned int)addrLow_Initial_OpenDialogBottomRow_PlaymodeRegionalStorage3,
        0x00000000, 0x00000000, 0x00010081, 0x0000000C, 0x0000FF01, (unsigned int)&g_menuToggleTorpedoLauncherDisabledText + 0x38, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000,
        (unsigned int)addrLow_Initial_OpenTrackPreviewMenu, 0x00000000, 0x0045015C, 0x00070000, 0x00000000, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00000000,
        0x00010000, 0x00000000, 0x00000000, 0x4C697374, 0x00010000, 0x00000000, 0x00000000, 0x00000000,
    },
    "List",
    {
        0x00010000, 0x00000000, 0x00000000, 0x00000000, 0x00000064, (unsigned int)addrLow_Menu_DrawMenuOptionSprite2, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000089, 0x00000028, 0x00000000, (unsigned int)g_creditsLocalizedLines + 0x140, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_CMenuProfile_ResetPlayerControllerProfile_Objectdata,
        0x00000000, 0x00000000, 0x00450280, 0x00020000, 0x0043EF20, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, (unsigned int)addrLow_Multi_CompleteGameOverDelay,
        0x00010000, 0x00000000, 0x00000000, 0x00000000, 0x00010000, 0x50000000, 0x00000000, 0x0000FF01,
        0x00000385, (unsigned int)addrLow_Menu_DrawMenuOptionSprite2, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x08000801, 0x00000008,
        0x0000FF01, (unsigned int)&g_redBloodScoreText[0x2C], (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00010080,
        0x00230016, 0x00000000, (unsigned int)&g_unlockedLevelResultLabel[0x8], (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, 0x00000000, 0x00000000, 0x00010000,
        0x00024010, 0x00030000, 0x00000000, 0x000007D0, 0x0043EFD0, 0x00000000, 0x00000000, 0x10D60000,
        0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007D0, 0x0043EFD0, 0x00000000, 0x00000000,
        0x10D60001, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007D0, 0x0043EFD0, 0x00000000,
        0x00000000, 0x10D60002, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007D1, 0x0043EFD0,
        0x00000000, 0x00000000, 0x10E00000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007D1,
        0x0043EFD0, 0x00000000, 0x00000000, 0x10E00001, 0x00010000, 0x00024010, 0x00030000, 0x00000000,
        0x000007D1, 0x0043EFD0, 0x00000000, 0x00000000, 0x10E00002, 0x00010000, 0x00024010, 0x00290000,
        0x00000000, 0x000007E4, 0x0043EFD0, 0x00000000, 0x00000000, 0x11080000, 0x00010000, 0x00024010,
        0x00030000, 0x00000000, 0x00000820, 0x0043EFD0, 0x00000000, 0x00000000, 0x11940000, 0x00000000,
        0x00010080, 0x00230003, 0x00000000, (unsigned int)&g_unlockedLevelResultLabel[0xC], (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, 0x00000000, 0x00000000,
        0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007D2, 0x0043EFD0, 0x00000000, 0x00000000,
        0x10EA0000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007D2, 0x0043EFD0, 0x00000000,
        0x00000000, 0x10EA0001, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007D2, 0x0043EFD0,
        0x00000000, 0x00000000, 0x10EA0002, 0x00010000, 0x00024010, 0x003C0000, 0x00000000, 0x0000080D,
        0x0043EFD0, 0x00000000, 0x00000000, 0x11320000, 0x00010000, 0x00024010, 0x00030000, 0x00000000,
        0x000007F9, 0x0043EFD0, 0x00000000, 0x00000000, 0x111E0000, 0x00010000, 0x00024010, 0x00030000,
        0x00000000, 0x000007E5, 0x0043EFD0, 0x00000000, 0x00000000, 0x11090000, 0x00010000, 0x00024010,
        0x00030000, 0x00000000, 0x00000820, 0x0043EFD0, 0x00000000, 0x00000000, 0x11940001, 0x00000000,
        0x00010080, 0x00230003, 0x00000000, (unsigned int)&g_unlockedLevelResultLabel[0x10], (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, 0x00000000, 0x00000000,
        0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007D3, 0x0043EFD0, 0x00000000, 0x00000000,
        0x10F40000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007D3, 0x0043EFD0, 0x00000000,
        0x00000000, 0x10F40001, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007D3, 0x0043EFD0,
        0x00000000, 0x00000000, 0x10F40002, 0x00010000, 0x00024010, 0x003C0000, 0x00000000, 0x0000080F,
        0x0043EFD0, 0x00000000, 0x00000000, 0x11300000, 0x00010000, 0x00024010, 0x00030000, 0x00000000,
        0x000007F8, 0x0043EFD0, 0x00000000, 0x00000000, 0x111C0000, 0x00010000, 0x00024010, 0x00030000,
        0x00000000, 0x000007E6, 0x0043EFD0, 0x00000000, 0x00000000, 0x110A0000, 0x00010000, 0x00024010,
        0x00030000, 0x00000000, 0x00000820, 0x0043EFD0, 0x00000000, 0x00000000, 0x11940002, 0x00000000,
        0x00010080, 0x00230003, 0x00000000, (unsigned int)&g_unlockedLevelResultLabel[0x14], (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, 0x00000000, 0x00000000,
        0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007D4, 0x0043EFD0, 0x00000000, 0x00000000,
        0x10FE0000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007D4, 0x0043EFD0, 0x00000000,
        0x00000000, 0x10FE0001, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007D4, 0x0043EFD0,
        0x00000000, 0x00000000, 0x10FE0002, 0x00010000, 0x00024010, 0x003C0000, 0x00000000, 0x0000080E,
        0x0043EFD0, 0x00000000, 0x00000000, 0x11340000, 0x00010000, 0x00024010, 0x00030000, 0x00000000,
        0x000007FC, 0x0043EFD0, 0x00000000, 0x00000000, 0x11200000, 0x00010000, 0x00024010, 0x00030000,
        0x00000000, 0x000007E7, 0x0043EFD0, 0x00000000, 0x00000000, 0x110B0000, 0x00010000, 0x00024010,
        0x00030000, 0x00000000, 0x00000820, 0x0043EFD0, 0x00000000, 0x00000000, 0x11940003, 0x00000000,
        0x00010080, 0x00230003, 0x00000000, (unsigned int)&g_unlockedLevelResultLabel[0x18], (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, 0x00000000, 0x00000000,
        0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007D4, 0x0043EFD0, 0x00000000, 0x00000000,
        0x10FE0003, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007D4, 0x0043EFD0, 0x00000000,
        0x00000000, 0x10FE0004, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007D4, 0x0043EFD0,
        0x00000000, 0x00000000, 0x10FE0005, 0x00010000, 0x00024010, 0x003C0000, 0x00000000, 0x0000080C,
        0x0043EFD0, 0x00000000, 0x00000000, 0x11330000, 0x00010000, 0x00024010, 0x00030000, 0x00000000,
        0x000007FB, 0x0043EFD0, 0x00000000, 0x00000000, 0x111F0000, 0x00010000, 0x00024010, 0x00030000,
        0x00000000, 0x000007E8, 0x0043EFD0, 0x00000000, 0x00000000, 0x110C0000, 0x00010000, 0x00024010,
        0x00030000, 0x00000000, 0x00000820, 0x0043EFD0, 0x00000000, 0x00000000, 0x11940004, 0x00000000,
        0x00010080, 0x00230003, 0x00000000, (unsigned int)&g_unlockedLevelResultLabel[0x1C], (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, 0x00000000, 0x00000000,
        0x00010000, 0x00024010, 0x00750000, 0x00000000, 0x00000810, 0x0043EFD0, 0x00000000, 0x00000000,
        0x11310000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007FA, 0x0043EFD0, 0x00000000,
        0x00000000, 0x111D0000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x000007E9, 0x0043EFD0,
        0x00000000, 0x00000000, 0x110D0000, 0x00010000, 0x00024010, 0x00030000, 0x00000000, 0x00000820,
        0x0043EFD0, 0x00000000, 0x00000000, 0x11940005, 0x00000000, 0x00010081, 0x0000001E, 0x00000000,
        (unsigned int)&g_redBloodScoreText[0x30], (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, (unsigned int)addrLow_Multi_CreateMenuWithDefaultMusicGain, 0x00000000, 0x004502F0, 0x00310000, (unsigned int)addrLow_Multi_EmptyItemHook_PlaymodeRegionalStorage3,
        0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00000000, 0x00300000, 0x00000000, 0x004513A0, 0x27000000, 0x08000C00,
        0x00010000, 0x50000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)addrLow_Menu_DrawMenuOptionSprite2, 0x00000000, 0x00000000,
        0x00000000, 0x00450A00, 0x00010000, (unsigned int)addrLow_Items_PrepareMenuReturnUs, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00000000, 0x00090000,
        0x00000000, 0x00451010, 0x00450A00, 0x00010000, (unsigned int)addrLow_Items_PrepareControllerReturn, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00000000,
        0x00090000, 0x00000000, 0x00000000, 0x616E6365, 0x00010000, 0x50000000, 0x00000000, 0x0000FF01,
    },
    "ance",
    {
        0x00010000, 0x50000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)addrLow_Menu_DrawMenuOptionSprite2, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000401, 0x00000028, 0x0000FF01, (unsigned int)&g_fragTagOnLabelText[0x8], (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Player_FormatPlayerPartnerStatus,
        0x00000000, 0x00000000, 0x00010000, 0x20010001, 0x00000000, 0x00000001, 0x0000012D, (unsigned int)addrLow_Player_DrawPulsingMenuSprite,
        0x00000000, (unsigned int)addrLow_Player_RespawnItemPlayer, 0x00000000, 0x00010000, 0x50000000, 0x00000000, 0x0000FF01, 0x00000385,
        (unsigned int)addrLow_Menu_DrawMenuOptionSprite2, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000401, 0x00000028, 0x0000FF01,
        (unsigned int)&g_fragTagOnLabelText[0x28], (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Player_FormatPlayerPartnerStatus, 0x00000000, 0x00000000, 0x00010000, 0x20010001, 0xFFEC0000,
        0xEC000001, 0x0000012D, (unsigned int)addrLow_Player_DrawPulsingMenuSprite, 0x00000000, (unsigned int)addrLow_Player_RespawnItemPlayer, 0x00000000, 0x00010000, 0x50000000,
        0x00000000, 0x0000FF01, 0x00000385, (unsigned int)addrLow_Menu_DrawMenuOptionSprite2, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000401, 0x00000028, 0x0000FF01, (unsigned int)&g_fragTagOnLabelText[0x48], (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Player_FormatPlayerPartnerStatus, 0x00000000, 0x00000000,
        0x00010000, 0x20010001, 0x00000000, 0x00000001, 0x0000012D, (unsigned int)addrLow_Player_DrawPulsingMenuSprite, 0x00000000, (unsigned int)addrLow_Player_RespawnItemPlayer,
        0x00000000, 0x00010000, 0x50000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)addrLow_Menu_DrawMenuOptionSprite2, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000401, 0x00000028, 0x0000FF01, (unsigned int)&g_fragTagOnLabelText[0x68], (unsigned int)addrLow_Menu_DrawMenuItemLabel2,
        (unsigned int)addrLow_Player_FormatPlayerPartnerStatus, 0x00000000, 0x00000000, 0x00010000, 0x20010001, 0x00000000, 0x00000001, 0x0000012D,
        (unsigned int)addrLow_Player_DrawPulsingMenuSprite, 0x00000000, (unsigned int)addrLow_Player_RespawnItemPlayer, 0x00000000, 0x00450A70, 0x00030000, (unsigned int)addrLow_Player_ConfigurePlayerMenuFlags, 0x00000000,
        (unsigned int)addrLow_Menu_DrawMenuEntries2, (unsigned int)addrLow_Player_UpdatePlayerRespawnDelay, 0x00020000, 0x00000000, 0x00000000, 0x00450ADC, 0x00030000, (unsigned int)addrLow_Player_ConfigurePlayerMenuFlags,
        0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, (unsigned int)addrLow_Player_UpdatePlayerRespawnDelay, 0x00020000, 0x00000000, 0x00000000, 0x00450B48, 0x00030000,
        (unsigned int)addrLow_Player_ConfigurePlayerMenuFlags, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, (unsigned int)addrLow_Player_UpdatePlayerRespawnDelay, 0x00020000, 0x00000000, 0x00000000, 0x00450BB4,
        0x00030000, (unsigned int)addrLow_Player_ConfigurePlayerMenuFlags, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, (unsigned int)addrLow_Player_UpdatePlayerRespawnDelay, 0x00020000, 0x00000000, 0x00000000,
        0x00450A70, 0x00030000, (unsigned int)addrLow_Player_ConfigureAndProbeControllerPak, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00000000, 0x000E0000, 0x00000000,
        0x00000000, 0x00450ADC, 0x00030000, (unsigned int)addrLow_Player_ConfigureAndProbeControllerPak, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00000000, 0x000E0000,
        0x00000000, 0x00000000, 0x00450B48, 0x00030000, (unsigned int)addrLow_Player_ConfigureAndProbeControllerPak, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00000000,
        0x000E0000, 0x00000000, 0x00000000, 0x00450BB4, 0x00030000, (unsigned int)addrLow_Player_ConfigureAndProbeControllerPak, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2,
        0x00000000, 0x000E0000, 0x00000000, 0x00000000, 0x00450A70, 0x00030000, (unsigned int)addrLow_Player_ConfigureControllerPakMenu, 0x00000000,
        (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00000000, 0x000E0000, 0x00000000, 0x00000000, 0x00450ADC, 0x00030000, (unsigned int)addrLow_Player_ConfigureControllerPakMenu,
        0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00000000, 0x000E0000, 0x00000000, 0x00000000, 0x00450B48, 0x00030000,
        (unsigned int)addrLow_Player_ConfigureControllerPakMenu, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00000000, 0x000E0000, 0x00000000, 0x00000000, 0x00450BB4,
        0x00030000, (unsigned int)addrLow_Player_ConfigureControllerPakMenu, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00000000, 0x000E0000, 0x00000000, 0x00000000,
        0x00010000, 0x50000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)addrLow_Menu_DrawMenuOptionSprite2, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x08000021, 0x00000008, 0x0000FF01, (unsigned int)&g_menuToggleTorpedoLauncherDisabledText + 0x28, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00400041, 0x0000002F, 0x0000FF01, (unsigned int)g_sceneMaskLabelTables[0], (unsigned int)addrLow_Menu_DrawMenuItemLabel2,
        (unsigned int)addrLow_Items_SelectSceneMaskText, (unsigned int)addrLow_Items_CycleSceneMask, 0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01, (unsigned int)g_playerOptionControlTypeExpertText,
        (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Items_SelectPlayerOptionControlTypeText, (unsigned int)addrLow_Items_AdjustPlayerOptionControlType, 0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01,
        (unsigned int)g_playerOptionControlSideLeftText, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Items_SelectPlayerOptionControlSideText, (unsigned int)addrLow_Items_AdjustPlayerOptionControlSide, 0x00000000, 0x00000000, 0x00410041, 0x00000000,
        0x0000FF01, (unsigned int)g_playerOptionLookSpringOnText, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Items_SelectPlayerOptionLookSpringText, (unsigned int)addrLow_Items_AdjustPlayerOptionLookSpring, 0x00000000, 0x00000000, 0x00410041,
        0x00000000, 0x0000FF01, (unsigned int)g_playerOptionAutoAimOffText, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Items_SelectPlayerOptionAutoAimText, (unsigned int)addrLow_Items_AdjustPlayerOptionAutoAim, 0x00000000, 0x00000000,
        0x00410041, 0x00000000, 0x0000FF01, (unsigned int)g_bloodColorOffText, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, PACKED_CALLBACK_LOW(Items_SelectBloodColorText), PACKED_CALLBACK_LOW(Items_AdjustBloodColor), 0x00000000,
        0x00000000, 0x00410041, 0x00000000, 0x0000FF01, (unsigned int)g_gameOptionSplitScreenLayoutHorizontalText, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Items_SelectSplitScreenPreferenceText, (unsigned int)addrLow_Items_AdjustSplitScreenPreference,
        0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01, (unsigned int)g_packedGameOptionValueText, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Items_FormatPackedGameOption,
        (unsigned int)addrLow_Items_AdjustPackedGameOption, 0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01, (unsigned int)g_playerOptionStickHorizontalStepText, (unsigned int)addrLow_Menu_DrawMenuItemLabel2,
        (unsigned int)addrLow_Items_FormatPlayerOptionStickHorizontalStep, (unsigned int)addrLow_Items_AdjustPlayerOptionStickHorizontal, 0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01, (unsigned int)g_playerOptionStickVerticalStepText,
        (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Items_FormatPlayerOptionStickVerticalStep, (unsigned int)addrLow_Items_AdjustPlayerOptionStickVertical, 0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01,
        (unsigned int)g_weaponSelectNormalText, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Items_SelectQuickWeaponSelectText, (unsigned int)addrLow_Items_ToggleQuickWeaponSelect, 0x00000000, 0x00000000, 0x00410041, 0x00000000,
        0x0000FF01, (unsigned int)g_frontendScreenModePaletteDefault, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Items_UpdateScreenModeMenuItem, (unsigned int)addrLow_Items_RequestScreenModeFade, 0x00000000, 0x00000000, 0x00410041,
        0x00000000, 0x0000FF01, (unsigned int)g_packedButtonOptionStepText, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, (unsigned int)addrLow_Pak_FormatPackedButtonOption, (unsigned int)addrLow_Pak_AdjustPackedButtonOption, 0x00000000, 0x00000000,
        0x00010201, 0x00000013, 0x0000FF01, (unsigned int)&g_packedButtonOptionStepText[0x8], (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, (unsigned int)addrLow_Menu_TryCreateMenu, 0x00000000,
        0x00450DD0, 0x00100000, (unsigned int)addrLow_Items_ResetScreenModeFadeCooldown, 0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00000000, 0x000F0000, 0x00000000,
        0x00000000, 0x0B434D65, 0x6D456E74, 0x72795F74, 0x00010000, 0x50000000, 0x00000000, 0x0000FF01,
    },
    "mEntry_t",
    {
        0x00010000, 0x50000000, 0x00000000, 0x0000FF01, 0x00000385, (unsigned int)addrLow_Menu_DrawMenuOptionSprite2, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x08000041, 0x00000008, 0x0000FF01, (unsigned int)&g_redBloodScoreText[0x28], (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000101, 0x0000005D, 0x0000FF01, (unsigned int)g_captureFlagVictimFollowupMessage + 0x4, (unsigned int)addrLow_Menu_DrawMenuItemLabel2,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00010101, 0x0000000A, 0x0000FF01, (unsigned int)g_captureFlagVictimFollowupMessage + 0xC,
        (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, 0x00444FA0, 0x00000000, 0x00000000, 0x00010101, 0x00000000, 0x0000FF01,
        (unsigned int)g_captureFlagVictimFollowupMessage + 0x10, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, (unsigned int)addrLow_Menu_TryCreateMenu, 0x00000000, 0x00451040, 0x00050000, 0x00444FE0,
        0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00000000, 0x00040000, 0x00000000, 0x004513A0, 0x00010000, 0x50000000,
        0x00000000, 0x0000FF01, 0x00000385, (unsigned int)addrLow_Menu_DrawMenuOptionSprite2, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x08002001, 0x00000008, 0x0000FF01, (unsigned int)&g_menuToggleTorpedoLauncherDisabledText + 0x38, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00410041, 0x00000032, 0x0000FF01, (unsigned int)g_volumeZeroValueLabelFixed, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00445340, 0x004452D0,
        0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01, (unsigned int)g_sfxVolumeText, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00445480,
        0x00445420, 0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01, (unsigned int)g_speechVolumeText, (unsigned int)addrLow_Menu_DrawMenuItemLabel2,
        0x004451F0, 0x00445190, 0x00000000, 0x00000000, 0x00410041, 0x00000000, 0x0000FF01, (unsigned int)g_musicPreviewFixedValueText,
        (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00445604, 0x00445560, 0x00000000, 0x00000000, 0x00410401, 0x00000044, 0x0000FF01,
        (unsigned int)&g_packedButtonOptionStepText[0x8], (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, 0x00445108, 0x00000000, 0x00451118, 0x00070000, 0x00000000,
        0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00000000, 0x00020000, 0x00000000, 0x00000000, 0x00010000, 0x50000000,
        0x00000000, 0x0000FF01, 0x00000385, (unsigned int)addrLow_Menu_DrawMenuOptionSprite2, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x08000041, 0x00000008, 0x0000FF01, (unsigned int)&g_redBloodScoreText[0x8], (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00010041, 0x00000028, 0x0000FF01, (unsigned int)&g_redBloodScoreText[0xC], (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, 0x00444FEC,
        0x00000000, 0x00000000, 0x00010041, 0x00000000, 0x0000FF01, (unsigned int)&g_redBloodScoreText[0x10], (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000,
        0x00445024, 0x00000000, 0x00000000, 0x00010041, 0x00000000, 0x0000FF01, (unsigned int)&g_redBloodScoreText[0x18], (unsigned int)addrLow_Menu_DrawMenuItemLabel2,
        0x00000000, 0x0044502C, 0x00000000, 0x00000000, 0x00010041, 0x00000000, 0x0000FF01, (unsigned int)&g_redBloodScoreText[0x20],
        (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, 0x00445058, 0x00000000, 0x00000000, 0x00010041, 0x00000000, 0x0000FF01,
        (unsigned int)&g_menuToggleTorpedoLauncherDisabledText + 0x38, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, 0x00445674, 0x00000000, 0x00000000, 0x00010041, 0x00000000,
        0x0000FF01, (unsigned int)g_captureFlagVictimFollowupMessage + 0x20, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, 0x00445084, 0x00000000, 0x00000000, 0x00010041,
        0x00000000, 0x0000FF01, (unsigned int)&g_redBloodScoreText[0x24], (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, 0x004450B0, 0x00000000, 0x00000000,
        0x00010041, 0x00000000, 0x0000FF01, (unsigned int)&g_redBloodScoreText[0x28], (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, 0x004450DC, 0x00000000,
        0x00451238, 0x000A0000, 0x0044577C, 0x0044580C, 0x00445828, 0x00000000, 0x00020000, 0x00000000,
        0x00000000, 0x00000010, 0x454E454D, 0x595F494E, 0x00000000, 0x00000041, 0x00000000, 0x0000FF01,
    },
    "ENEMY_IN",
    {
        0x00000000, 0x00000041, 0x00000000, 0x0000FF01, (unsigned int)&g_pakStatusTelsetText + 0x14, (unsigned int)addrLow_Menu_DrawMenuItemLabel2, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00210101, 0x00000008, 0x0000FF01, (unsigned int)&g_multiplayerSavedPlayerNames[0xB4], 0x00445D30, 0x00445AD4,
        0x00000000, 0x00000000, 0x00000000, 0x00210101, 0x00000008, 0x0000FF01, (unsigned int)&g_multiplayerSavedPlayerNames[0xB8], 0x00445D30,
        0x00445AD4, 0x00000000, 0x00000000, 0x00000000, 0x00210101, 0x00000008, 0x0000FF01, (unsigned int)&g_multiplayerSavedPlayerNames[0xBC],
        0x00445D30, 0x00445AD4, 0x00000000, 0x00000000, 0x00000000, 0x00210101, 0x00000008, 0x0000FF01,
        (unsigned int)&g_multiplayerSavedPlayerNames[0xC0], 0x00445D30, 0x00445AD4, 0x00000000, 0x00000000, 0x00000000, 0x00010110, 0x0000000A,
        0x07012008, (unsigned int)g_creditsLocalizedLines + 0x8, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, 0x00445C24, 0x00000000, 0x00000000, 0x00024110,
        0x00060000, 0xFF012008, (unsigned int)g_creditsLocalizedLines + 0x10, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, 0x00445C24, 0x00000000, 0x00000000,
        0x00024110, 0x00060000, 0xFF012008, (unsigned int)g_creditsLocalizedLines + 0x18, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, 0x00445C24, 0x00000000,
        0x00000000, 0x00024110, 0x00060000, 0xFF012008, (unsigned int)g_creditsLocalizedLines + 0x20, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, 0x00445C24,
        0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF012008, (unsigned int)g_creditsLocalizedLines + 0x28, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000,
        0x00445C24, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF012008, (unsigned int)g_creditsLocalizedLines + 0x30, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText,
        0x00000000, 0x00445C24, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF012008, (unsigned int)g_creditsLocalizedLines + 0x38,
        (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, 0x00445C24, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFFF92008,
        (unsigned int)g_creditsLocalizedLines + 0x40, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, 0x00445C24, 0x00000000, 0x00000000, 0x00010110, 0x00000004,
        0x0701F808, (unsigned int)g_creditsLocalizedLines + 0x48, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, 0x00445C24, 0x00000000, 0x00000000, 0x00024110,
        0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0x50, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, 0x00445C24, 0x00000000, 0x00000000,
        0x00024110, 0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0x58, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, 0x00445C24, 0x00000000,
        0x00000000, 0x00024110, 0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0x60, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, 0x00445C24,
        0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0x68, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000,
        0x00445C24, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0x70, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText,
        0x00000000, 0x00445C24, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0x78,
        (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, 0x00445C24, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFFF9F808,
        (unsigned int)g_creditsLocalizedLines + 0x80, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, 0x00445C24, 0x00000000, 0x00000000, 0x00010110, 0x00000004,
        0x0701F808, (unsigned int)g_creditsLocalizedLines + 0x88, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, 0x00445C24, 0x00000000, 0x00000000, 0x00024110,
        0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0x90, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, 0x00445C24, 0x00000000, 0x00000000,
        0x00024110, 0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0x98, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, 0x00445C24, 0x00000000,
        0x00000000, 0x00024110, 0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0xA0, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, 0x00445C24,
        0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0xA8, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000,
        0x00445C24, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0xB0, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText,
        0x00000000, 0x00445C24, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0xB8,
        (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, 0x00445C24, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFFF9F808,
        (unsigned int)g_creditsLocalizedLines + 0xC0, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, 0x00445C24, 0x00000000, 0x00000000, 0x00010110, 0x00000004,
        0x0701F808, (unsigned int)g_creditsLocalizedLines + 0xC8, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, 0x00445C24, 0x00000000, 0x00000000, 0x00024110,
        0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0xD0, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, 0x00445C24, 0x00000000, 0x00000000,
        0x00024110, 0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0xD8, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, 0x00445C24, 0x00000000,
        0x00000000, 0x00024110, 0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0xE0, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, 0x00445C24,
        0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0xE8, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000,
        0x00445C24, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0xF0, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText,
        0x00000000, 0x00445C24, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F808, (unsigned int)g_creditsLocalizedLines + 0xF8,
        (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, 0x00445C24, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFFF9F808,
        (unsigned int)g_creditsLocalizedLines + 0x100, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, 0x00445C24, 0x00000000, 0x00000000, 0x00010110, 0x00000004,
        0x0701F8E0, (unsigned int)g_creditsLocalizedLines + 0x108, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, 0x00445C24, 0x00000000, 0x00000000, 0x00024110,
        0x00060000, 0xFF01F8E0, (unsigned int)g_creditsLocalizedLines + 0x110, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, 0x00445C24, 0x00000000, 0x00000000,
        0x00024110, 0x00060000, 0xFF01F8E0, (unsigned int)g_creditsLocalizedLines + 0x118, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, 0x00445C24, 0x00000000,
        0x00000000, 0x00024110, 0x00060000, 0xFF01F8E0, (unsigned int)g_creditsLocalizedLines + 0x120, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, 0x00445C24,
        0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F8E0, (unsigned int)g_unlockedLevelResultLabel, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000,
        0x00445C24, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F8E0, (unsigned int)g_creditsLocalizedLines + 0x128, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText,
        0x00000000, 0x00445C24, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFF01F8E0, (unsigned int)g_creditsLocalizedLines + 0x130,
        (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, 0x00445EDC, 0x00000000, 0x00000000, 0x00024110, 0x00060000, 0xFFF9F8E0,
        (unsigned int)g_creditsLocalizedLines + 0x138, (unsigned int)addrLow_Menu_DrawLocalizedMenuItemText, 0x00000000, 0x00445F74, 0x00000000, 0x004513D0, 0x002D0000, 0x00445850,
        0x00000000, (unsigned int)addrLow_Menu_DrawMenuEntries2, 0x00446064, 0x00050000, 0x00000000, 0x00000000, 0x2E656F73, 0x52000000,
    },
    ".eosR\000\000\000",
};
#endif
