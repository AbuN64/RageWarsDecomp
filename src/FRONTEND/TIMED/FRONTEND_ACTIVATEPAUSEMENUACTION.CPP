#include "COMMON/SCREEN.H"
#include "COMMON/MENU_INITIALIZEOPTIONSSCENE.H"
#include "COMMON/GAME_SESSION.H"
#include "COMMON/RESERVED_SHARED_DECLARATIONS.H"
#include "TYPES.H"
#include "MENU/MENU_REQUESTOPTIONSSCREEN22.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "FRONTEND/FRONTEND_DISPATCHPAUSEMENUEVENT.H"

/* 8042E080_78.CPP */
#if defined(VERSION_EU_X)
enum { START_MATCH = 67, RETURN_MENU = 62, WAIT_SHORT = 66, WAIT_LONG = 64 };
#else
enum { START_MATCH = 64, RETURN_MENU = 60, WAIT_SHORT = 65, WAIT_LONG = 62 };
#endif

/* Handles the menu message Menu_GetFocusedElementId reports after MarkMenuEventHandled: 0x40 clears g_simpleObjectPauseState and
   calls Tsmos_RequestFrontendShutdown and SoundElement_DisableMusicGainOverride; 0x3C clears g_simpleObjectPauseState and calls Menu_RequestOptionsScreen22; 0x41 and
   0x3E wait 0x1F and 0x20 through SmXlate_SwitchScreen. Returns zero. */
extern void Tsmos_RequestFrontendShutdown(void);
extern void SoundElement_DisableMusicGainOverride(void);

extern void SmXlate_SwitchScreen(s32);

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
        Menu_RequestOptionsScreen22();
        return 0;
    case WAIT_SHORT:
        time = 31;
        goto wait;
    case WAIT_LONG:
        time = 32;
    wait:
        SmXlate_SwitchScreen(time);
        return 0;
    }
    return 0;
}

/* 8042E080_79.CPP */
/* Dispatches event eventId through this file's 12-byte handler table, whose rows hold an event at g_pauseMenuEventIds, an actor kind at g_pauseMenuEventActorKinds and a handler at g_pauseMenuEventHandlers: the first row whose event equals eventId and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from N64Eng_DispatchNumericWidgetEvent. */

typedef s32 (*PauseMenuEventHandler)(void *, s32, s32, s32, s32);

extern FieldRow g_pauseMenuEventIds[];
extern FieldRow g_pauseMenuEventActorKinds[];
extern PauseMenuEventHandler g_pauseMenuEventHandlers;

s32 Frontend_DispatchPauseMenuEvent(void *eventTarget, s32 eventId, s32 eventCode, s32 eventValue, s32 repeatCount) {
    PauseMenuEventHandler *entry;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;
    MenuActorInputView *actor;

    if (g_pauseMenuEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_pauseMenuEventHandlers;
        index = 0;
        do {
            if (g_pauseMenuEventIds[index].value == eventId) {
                actor = eventTarget;
                actor_kind = actor->input;
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

/* 8042E080_80.CPP */
/* Builds screen state g_pauseTimedMenu as Frontend_CreateTimedMenu builds g_residentChoiceScreen: allocates its 0x20 bytes,
   resets through Tsmos_ActivateControllerState, sets its selection at 0x1C to -1 and opens it as page 0x67 through
   Frontend_InitMenuImage; then places the given window at 0x62, 0x45 in mode 1 of Frontend_GetCurrentVideoModeIndex_de, or at x
   0x69 in mode 2. Returns zero. */

extern struct MenuRules *g_pauseTimedMenu;
extern struct Record *Cache_AllocateMemory(s32 size);
extern void Tsmos_ActivateControllerState(void);
extern void Frontend_InitMenuImage(s32 *record, s32 first, s32 second, s32 third, s32 fourth);
extern s32 Frontend_GetScreenMode(void);

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
