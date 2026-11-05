#include "Common/screen.h"
#include "Frontend/frontend_address_symbols.h"
#include "include_asm.h"
#include "Common/shared_gameslot.h"
#include "Common/reserved_shared_declarations.h"
#include "types.h"
#include "System/sound_context_music_and_voice_control.h"
#include "Common/shared_menureply.h"
#include "Common/selectionscreenstate.h"
#include "Frontend/menuimage.h"
#include "Common/game_session.h"
#include "Ui/Tsmos/TSMOS.h"
#include "Common/menu_initializeoptionsscene.h"
#include "Menu/menu_switchtooptionsscreen.h"
#include "Common/aiprofile.h"
#include "Frontend/frontend_dispatchpausemenuevent.h"
#include "Common/runtime_declarations.h"
#include "Common/multiplayeroptions.h"
#include "Scene/cache_freememory.h"
#include "Common/gameplay_camera.h"
#include "Common/shared_optionsscreen.h"
#include "Common/menu_match_globals.h"
#include "Common/world.h"
#include "Frontend/screen.h"
#include "Frontend/menu_image.h"
#include "Cache/cache_allocresourceblock.h"
#include "Frontend/frontend_dispatchconfirmationevent.h"
#include "Common/Lone/resident_choice_screen.h"
#include "Frontend/frontend.h"

/* unit TIMED.CPP */
/* Handles the menu message Menu_GetFocusedElementId reports after MarkMenuEventHandled: 0x3D5 waits 1 through
   SmXlate_SwitchScreen; 0x3D3 plays cue 0x34 through SoundElement_SetMusicPlaybackEnabled when SoundElement_GetMusicPlaybackEnabled reports sound on,
   resets through Tsmos_DeactivateControllerState, sets the timer at 0x1C of screen g_pauseTimedMenu by setting
   g_gameControllerMode through k_timedControllerModeLockedJumpTable (10, 15 or 10, and 20 for any other setting) and shows the
   screen through Frontend_StartMenuImageTransition. Returns zero. */

#if defined(VERSION_DE)
enum { TIMED_MENU_ELEMENT_START_TRANSITION = 973, TIMED_MENU_ELEMENT_SWITCH_SCREEN = 975 };
#elif defined(VERSION_EU_X)
enum { TIMED_MENU_ELEMENT_START_TRANSITION = 983, TIMED_MENU_ELEMENT_SWITCH_SCREEN = 985 };
#else
enum { TIMED_MENU_ELEMENT_START_TRANSITION = 979, TIMED_MENU_ELEMENT_SWITCH_SCREEN = 981 };
#endif

s32 Timed_UpdateTimedScreen(void) {
    MarkMenuEventHandled();
    switch (Menu_GetFocusedElementId()) {
    case TIMED_MENU_ELEMENT_SWITCH_SCREEN:
        SmXlate_SwitchScreen(1);
        return 0;
    case TIMED_MENU_ELEMENT_START_TRANSITION:
        if (SoundElement_GetMusicPlaybackEnabled() != 0) {
            SoundElement_SetMusicPlaybackEnabled(52);
        }
        Tsmos_DeactivateControllerState();
        switch (g_gameSettings.controllerMode) {
        case 1:
            g_pauseTimedMenu->locked = 10;
            break;
        case 2:
            g_pauseTimedMenu->locked = 15;
            break;
        case 3:
        case 4:
            g_pauseTimedMenu->locked = 10;
            break;
        case 0:
        default:
            g_pauseTimedMenu->locked = 20;
            break;
        }
        Frontend_StartMenuImageTransition(g_pauseTimedMenu);
        return 0;
    }
    return 0;
}

#if defined(VERSION_EU_X)
unsigned int k_TimedEncodedWords[3] = {
    0x00000015, 0x00000001, 0x00000004,
};
#endif

#if defined(VERSION_EU)
unsigned int k_timedSubtractInstructionWords[3] = {
    0x01785822, 0x19600002, 0x01735822,
};
#endif

/* unit FRONTEND_RESUMEMATCHONINPUT.CPP */
/* On event 3 with value 0xD, clears g_simpleObjectPauseState and calls Tsmos_RequestFrontendShutdown and SoundElement_DisableMusicGainOverride. Returns
   zero. */
s32 Frontend_ResumeMatchOnInput(void *first, void *second, u32 event, s32 value) {
    if ((event >> 16) == 3) {
        if (value != 13) {
            return 0;
        }
        g_gameSession.clockPaused = 0;
        Tsmos_RequestFrontendShutdown();
        SoundElement_DisableMusicGainOverride();
    }
    return 0;
}

/* Calls MarkMenuEventHandled with the arguments it was given and returns zero. */
s32 Frontend_ConsumePauseMenuEvent(void) {
    MarkMenuEventHandled();
    return 0;
}

/* unit FRONTEND_ACTIVATEPAUSEMENUACTION.CPP */
#if defined(VERSION_EU_X)
enum { START_MATCH = 67, RETURN_MENU = 62, WAIT_SHORT = 66, WAIT_LONG = 64 };
#else
enum { START_MATCH = 64, RETURN_MENU = 60, WAIT_SHORT = 65, WAIT_LONG = 62 };
#endif

/* Handles the menu message Menu_GetFocusedElementId reports after MarkMenuEventHandled: 0x40 clears g_simpleObjectPauseState and
   calls Tsmos_RequestFrontendShutdown and SoundElement_DisableMusicGainOverride; 0x3C clears g_simpleObjectPauseState and calls Menu_SwitchToOptionsScreen; 0x41 and
   0x3E wait 0x1F and 0x20 through SmXlate_SwitchScreen. Returns zero. */
s32 Frontend_ActivatePauseMenuAction(void) {
    s32 time;

    MarkMenuEventHandled();
    switch (Menu_GetFocusedElementId()) {
    case START_MATCH:
        g_gameSession.clockPaused = 0;
        Tsmos_RequestFrontendShutdown();
        SoundElement_DisableMusicGainOverride();
        return 0;
    case RETURN_MENU:
        g_gameSession.clockPaused = 0;
        Menu_SwitchToOptionsScreen();
        return 0;
    case WAIT_SHORT:
        time = 31;
        SmXlate_SwitchScreen(time);
        return 0;
    case WAIT_LONG:
        time = 32;
        SmXlate_SwitchScreen(time);
        return 0;
    }
    return 0;
}

/* Calls the handler registered for eventId (tables g_pauseMenuEventIds, g_pauseMenuEventActorKinds, g_pauseMenuEventHandlers). A row matches when its event equals eventId and its kind equals the actor's kind or is the any-kind wildcard 0x7530. Returns the handler's result, or zero when no row matches. */


s32 Frontend_DispatchPauseMenuEvent(void *eventTarget, s32 eventId, s32 eventCode, s32 eventValue, s32 repeatCount) {
    PauseMenuEventHandler *entry;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;
    MenuWidget *actor;

    if (g_pauseMenuEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_pauseMenuEventHandlers;
        index = 0;
        do {
            if (g_pauseMenuEventIds[index].value == eventId) {
                actor = eventTarget;
                actor_kind = actor->resource;
                table_kind = g_pauseMenuEventActorKinds[index].value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*entry)(eventTarget, eventId, eventCode, eventValue, repeatCount);
                }
            }
            entry += 3;
            index++;
        } while (*entry != 0);
    }
    return 0;
}

/* Builds screen state g_pauseTimedMenu as Frontend_CreateTimedMenu builds g_residentChoiceScreen: allocates its 0x20 bytes,
   resets through Tsmos_ActivateControllerState, sets its selection at 0x1C to -1 and opens it as page 0x67 through
   Frontend_InitMenuImage; then places the given window at 0x62, 0x45 in mode 1 of Frontend_GetCurrentVideoModeIndex_de, or at x
   0x69 in mode 2. Returns zero. */
s32 Frontend_CreatePauseConfirmation(struct Pair14 *window) {
    g_pauseTimedMenu = Cache_AllocateMemory(32);
    Tsmos_ActivateControllerState();
    g_pauseTimedMenu->locked = -1;
    Frontend_InitMenuImage(g_pauseTimedMenu, 103, 0, 0, 0);
    if (Frontend_GetScreenMode() == 1) {
        window->first = 98;
        window->second = 69;
    } else if (Frontend_GetScreenMode() == 2) {
        window->first = 105;
    }
    return 0;
}

/* unit TIMED_DESTROYPAUSECONFIRMATION.CPP */
/* Releases the object g_pauseTimedMenu holds through Cache_FreeMemory, clears g_pauseTimedMenu, calls Tsmos_SetMenuModelFlag with 2
   and returns zero. */
s32 Timed_DestroyPauseConfirmation(void) {
    Cache_FreeMemory(g_pauseTimedMenu);
    g_pauseTimedMenu = 0;
    Tsmos_SetMenuModelFlag(2);
    return 0;
}

/* unit TIMED_SETCONFIRMATIONINPUTMODE.CPP */
/* Calls Tsmos_SetMenuModelFlag with 2 and returns zero. */
s32 Timed_SetConfirmationInputMode(void) {
    Tsmos_SetMenuModelFlag(2);
    return 0;
}

/* unit TIMED_FINISHPAUSECONFIRMATIONTRANSITION.CPP */
/* Event callback for screen g_pauseTimedMenu: on event 1 while Frontend_GetMenuImageState reports the screen in state 1 it advances the screen through Frontend_DrawMenuImage and Frontend_AdvanceMenuImageTransition, and when that leaves it in state 2 it calls Frontend_RequestScreenMode_AchieveUpdateresultsscreen(0) and MarkMenuEventHandled, clears the pause word g_simpleObjectPauseState (0x180C past the match objects at g_frontendScreenStatus), stops those objects and the ones 0x48 bytes before them, releases resource 0x24 of g_world_AchieveUpdateresultsscreen, restarts Cache_SetResourceActivityState when Cache_GetResourceActivityState reports it idle, stores 8 at 0x17F0 past the match objects, passes the screen's word at 0x1C to SmXlate_SwitchScreen and calls SoundElement_DisableMusicGainOverride, returning zero. */
s32 Timed_FinishPauseConfirmationTransition(s32 element, s32 eventId, s32 event) {
    s32 *pause;
    Shared_MenuData *menuData;
    if (event == 1) {
        if (Frontend_GetMenuImageState(g_pauseTimedMenu) != 1) {
            return 0;
        }
        Frontend_DrawMenuImage(g_pauseTimedMenu);
        Frontend_AdvanceMenuImageTransition(g_pauseTimedMenu);
        if (Frontend_GetMenuImageState(g_pauseTimedMenu) != 2) {
            return 0;
        }
        Frontend_RequestScreenMode(0);
        MarkMenuEventHandled();
        pause = &g_frontendScreenStatus.status[7];
        *pause = 0;
        menuData = (Shared_MenuData *)&g_frontendScreenStatus;
        Pools_ResetActorPools(&menuData->object, 0);
        Player_InitializePlayerPool(menuData, 0, 0);
        Scene_LoadLevelResources(&g_world, 36, 0);
        if (Cache_GetResourceActivityState() == 0) {
            Cache_SetResourceActivityState(1);
        }
        g_frontendScreenStatus.status[0] = 8;
        SmXlate_SwitchScreen((void *)g_pauseTimedMenu->locked);
        SoundElement_DisableMusicGainOverride();
    }
    return 0;
}

/* unit FRONTEND_CONSUMECONFIRMATIONEVENT.CPP */
/* Event handler placeholder: ignores the event and returns zero. */
s32 Frontend_ReturnConfirmationEventZero(void) {
    return 0;
}

/* Calls MarkMenuEventHandled with the arguments it was given and returns zero. */
s32 Frontend_ConsumeConfirmationEvent(void) {
    MarkMenuEventHandled();
    return 0;
}

/* unit FRONTEND_CREATETIMEDMENU.CPP */
/* Calls the handler registered for eventId (tables g_confirmationMenuEventIds, g_confirmationMenuEventActorKinds, g_confirmationMenuEventHandlers). A row matches when its event equals eventId and its kind equals the actor's kind or is the any-kind wildcard 0x7530. Returns the handler's result, or zero when no row matches. */


s32 Frontend_DispatchConfirmationEvent(void *eventTarget, s32 eventId, s32 eventCode, s32 eventValue, s32 repeatCount) {
    ConfirmationMenuEventHandler *entry;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;
    MenuWidget *actor;

    if (g_confirmationMenuEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_confirmationMenuEventHandlers;
        index = 0;
        do {
            if (g_confirmationMenuEventIds[index].value == eventId) {
                actor = eventTarget;
                actor_kind = actor->resource;
                table_kind = g_confirmationMenuEventActorKinds[index].value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*entry)(eventTarget, eventId, eventCode, eventValue, repeatCount);
                }
            }
            entry += 3;
            index++;
        } while (*entry != 0);
    }
    return 0;
}

/* Builds screen state g_residentChoiceScreen: allocates its 0x1C bytes, resets through Tsmos_ActivateControllerState and opens
   it as page 0x67 through Frontend_InitMenuImage; then places the given window at 0x62, 0x45 in mode 1 of
   Frontend_GetCurrentVideoModeIndex_de, or at x 0x69 in mode 2. Returns zero. */
s32 Frontend_CreateTimedMenu(struct Pair14 *window) {
    g_residentChoiceScreen = Cache_AllocateMemory(28);
    Tsmos_ActivateControllerState();
    Frontend_InitMenuImage(g_residentChoiceScreen, 103, 0, 0, 0);
    if (Frontend_GetScreenMode() == 1) {
        window->first = 98;
        window->second = 69;
    } else if (Frontend_GetScreenMode() == 2) {
        window->first = 105;
    }
    return 0;
}
