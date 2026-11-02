#include "COMMON/SCREEN.H"
#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESERVED_SHARED_DECLARATIONS.H"
#include "TYPES.H"
#include "SYSTEM/SOUND_CONTEXT_MUSIC_AND_VOICE_CONTROL.H"

/* Handles the menu message Menu_GetFocusedElementId reports after MarkMenuEventHandled: 0x3D5 waits 1 through
   SmXlate_SwitchScreen; 0x3D3 plays cue 0x34 through SoundElement_SetMusicPlaybackEnabled when SoundElement_GetMusicPlaybackEnabled reports sound on,
   resets through Tsmos_DeactivateControllerState, sets the timer at 0x1C of screen g_pauseTimedMenu by setting
   g_gameControllerMode through k_timedControllerModeLockedJumpTable (10, 15 or 10, and 20 for any other setting) and shows the
   screen through Frontend_StartMenuImageTransition. Returns zero. */
extern MenuRules *g_pauseTimedMenu;
extern void SmXlate_SwitchScreen(s32);

extern void Tsmos_DeactivateControllerState(void);
extern void Frontend_StartMenuImageTransition(s32 *record);

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
unsigned int k_TimedEncodedWordsBlock1[3] = {
    0x01785822, 0x19600002, 0x01735822,
};
#endif
