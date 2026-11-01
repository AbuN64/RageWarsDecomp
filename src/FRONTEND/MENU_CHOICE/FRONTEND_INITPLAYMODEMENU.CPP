#include "FRONTEND/NODE_FINDWIDGETBYRESOURCEID.H"
#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"
#include "SCENE/CACHE_FREEMEMORY.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/PLAYERPROFILES.H"
#include "UI/X_FILES/X_PLUS.H"


#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/GAMEPLAY_SETTINGS.H"
#include "COMMON/ALAUXBUS_S.H"
#include "FRONTEND/SCREEN.H"

extern s32 g_currentStagePreset;

/* g_playerSettings_Achieve is the hub's SlotSelectionPlayerConfig array: eight 0x96-byte records at Game+0xD0.
   This unit reaches them only as settings->playerSettings and declares nothing here. */

extern void MarkMenuEventHandled(void);

extern s32 Menu_GetFocusedElementId(void);

extern void Player_InitializeProfile(void *profileStorage);

extern void PAKInterface_SetScreenPhase(s32);

extern void Player_SetAchievementFlag7(char *, s32);

extern void SmpSlider_SetTransitionMode(struct SliderTransitionView *object, s32 mode);

/* Applies the play mode picked on the front-end menu: sets the next screen, the controller mode and which players
 * join, then hands the screen record on. */
/* The options screen record g_playModeMenuState (Frontend_InitPlayModeMenu allocates its 0x1C bytes): the menu music handle, the
 * prompt and title widgets, the controller mode, the screen state and the screen Frontend_ApplyModeChoice goes to. */
typedef struct OptionsScreen {
    void *music;
    void *prompt;
    MenuWidget *title;
    s32 mode;
    s32 pad10;
    s32 state;
    s32 nextScreen;
} OptionsScreen;
extern OptionsScreen *g_playModeMenuState;

extern s8 g_profileSlotEnabledFlags[];
extern u8 g_profileUnlockGroupFlags[];
extern void ScenarioSetup_SetCupCategory(int);
extern void Random_SetSelectedStage(s32, s32);
extern void Tsmos_SetIdleTimer(f32);
extern void Tsmos_ActivateControllerState(void);
extern struct Record *Cache_AllocateMemory(s32 size);
extern s32 Defs_TestBit(void *bitArray, s32 index);
extern void Widget_SetWidgetFlag100(void *, s32);
extern void Widget_SetWidgetFlag08(void *, s32);
extern void SmpButton_WrapButtonWidget(s32);
extern void Focus_AdvanceActiveSlot(int *);
extern s32 Control_IsControllerConnected(s32);
extern void *SmpFade_CreateFadeWidget(s32, s32);
extern void SmpSlider_DisableTransition(struct Access_s32_5C *object);
extern struct MenuResourceWidget *SmpFlicker_CreateFlickerWidget(int widgetResourceId, int ownerValue);
extern u32 Menu_GetBlockedScreenOwner(void);
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
        XPlus_FillMemory((char *)&g_localPlayerProfiles[i] + ((char *)&((Profile *)0)->levelFlags[1] - (char *)0), 0, 5);
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
        g_playModeMenuState->mode = 9;
    } else {
        g_playModeMenuState->mode = 1;
    }
    g_playModeMenuState->state = 3;
    Frontend_RequestScreenMode(0);
    return 0;
}

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
