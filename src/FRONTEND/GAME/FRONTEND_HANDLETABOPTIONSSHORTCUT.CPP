#include "COMMON/SCREEN.H"
#include "include_asm.h"
#include "COMMON/MENU_OPTIONS_AND_RESULTS.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "TYPES.H"
#include "COMMON/MENULISTSCREEN.H"
#include "FRONTEND/MENU_COMMITOPTIONSPAGE.H"
#include "FRONTEND/FRONTEND_HANDLETABOPTIONSSHORTCUT.H"
#include "SCENE/CACHE_FREEMEMORY.H"

/* Releases the object g_gameOptionsScreenState holds through Cache_FreeMemory, calls Tsmos_ActivateControllerState, clears
   g_gameOptionsScreenState and returns zero. */



extern void Tsmos_ActivateControllerState(void);

/* Sets the word at offset 0xC of the object g_gameOptionsScreenState points to and calls Tsmos_ActivateControllerState, once:
   nothing happens when the word is already set. Returns zero. */




/* Handles the menu message Menu_GetFocusedElementId reports after MarkMenuEventHandled: 0x1C3, 0x1BD, 0x1C2 and
   0x1C4 send codes -1, 13, 12 and 14 to Random_SetMenuChoiceResult; a handled message then runs Menu_CommitCompactOptionsPage
   and Menu_ReturnToPreviousScreen. Returns zero. */



extern void Menu_ReturnToPreviousScreen(void);

/* Calls MarkMenuEventHandled, Random_SetMenuChoiceResult with -1, Menu_CommitCompactOptionsPage and Menu_ReturnToPreviousScreen, and returns zero. */

extern void Menu_ReturnToPreviousScreen(void);

typedef s32 (*CompactOptionsEventHandler)(void *, s32, s32, s32, s32);

extern FieldRow g_compactOptionsEventKinds[];

extern FieldRow g_compactOptionsActorKinds[];

extern CompactOptionsEventHandler g_compactOptionsEventHandlers;

/* Releases the object g_optionsShortcutScreen holds through Cache_FreeMemory, calls Tsmos_ActivateControllerState, clears g_optionsShortcutScreen, calls
   Cinema_ReleaseSequenceContext_FrontendHandletaboptionsshortcut and returns zero. */


extern void Cinema_ReleaseSequenceContext(void);

/* Handles the menu message Menu_GetFocusedElementId reports after MarkMenuEventHandled, for its MESSAGE_COUNT messages from
   FIRST_MESSAGE (0x377 to 0x380 on us) through k_tabOptionsShortcutMessageJumpTable: one reopens screen g_optionsShortcutScreen (marking it shown with timer -1 and
   refreshing its two windows at 0x44 and 0x4C) and calls Cinema_ReleaseSequenceContext_FrontendHandletaboptionsshortcut; one tries ScenarioSetup_StartRandomCupStage
   and on failure sets the screen's modes 5 and 4 with timer 20, else reopens it with timer 0; the
   others pass codes 0x17, 13, 12 and 14 to Random_SetMenuChoiceResult. Any handled message then runs
   Menu_CommitTabOptionsPage. Returns zero. */
/* The first message this handles and how many it takes: eu-x numbers the messages 4 higher, de 4
   lower and takes only 8, as each cartridge's own bytes show; us, us-rev1 and eu share 0x377 and 10. */


extern void Tsmos_DeactivateControllerState(void);

/* The message screen g_gameOptionsScreenState; its word at 0xC marks the message handled. */
extern struct CompactOptionsCommitContext *g_gameOptionsScreenState;
extern struct MessageScreen *g_optionsShortcutScreen;
extern void Frontend_StartMenuImageTransition(s32 *record);

extern void Widget_SetWidgetFlag08(void *object, int enabled);

extern void Cinema_ReleaseSequenceContext(void);

extern s32 ScenarioSetup_StartRandomCupStage(void);

/* Dispatches event eventKind through this file's 12-byte handler table, whose rows hold an event at g_tabOptionsEventKinds, an actor kind at g_tabOptionsActorKinds and a handler at g_tabOptionsEventHandlers: the first row whose event equals eventKind and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from N64Eng_DispatchNumericWidgetEvent. */

typedef s32 (*TabOptionsEventHandler)(void *, s32, s32, s32, s32);

extern FieldRow g_tabOptionsEventKinds[];

extern FieldRow g_tabOptionsActorKinds[];

extern TabOptionsEventHandler g_tabOptionsEventHandlers;

s32 Frontend_DestroyCompactOptionsPage(void) {
    Cache_FreeMemory(g_gameOptionsScreenState);
    Tsmos_ActivateControllerState();
    g_gameOptionsScreenState = 0;
    return 0;
}

s32 Frontend_ActivateCompactOptionsPage(void) {
    struct CompactOptionsPageView *state = g_gameOptionsScreenState;

    if (state->flagWord == 0) {
        state->flagWord = 1;
        Tsmos_ActivateControllerState();
    }
    return 0;
}

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

s32 Frontend_CloseCompactOptionsPage(void) {
    MarkMenuEventHandled();
    Random_SetMenuChoiceResult(-1);
    Menu_CommitCompactOptionsPage();
    Menu_ReturnToPreviousScreen();
    return 0;
}

s32 Frontend_DispatchCompactOptionsEvent(void *menuActor, s32 eventKind, s32 eventDataOne, s32 eventDataTwo, s32 eventDataThree) {
    CompactOptionsEventHandler *entry;
    MenuActorInputView *actor;
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
                actor_kind = actor->input;
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

s32 Frontend_DestroyTabOptionsPage(void) {
    Cache_FreeMemory(g_optionsShortcutScreen);
    Tsmos_ActivateControllerState();
    g_optionsShortcutScreen = 0;
    Cinema_ReleaseSequenceContext();
    return 0;
}

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
    if (message >=
#if defined(VERSION_DE)
        8
#else
        10
#endif
    ) {
        goto other;
    }
    switch (message) {
#if defined(VERSION_DE)
        case 0: goto reopen;
        case 1: goto retry;
        case 2: goto code_14;
        case 3: goto code_17;
        case 4: goto other;
        case 5: goto other;
        case 6: goto code_13;
        case 7: goto code_12;
#else
        case 0: goto code_13;
        case 1: goto other;
        case 2: goto other;
        case 3: goto other;
        case 4: goto other;
        case 5: goto code_12;
        case 6: goto reopen;
        case 7: goto retry;
        case 8: goto code_14;
        case 9: goto code_17;
#endif
        }
reopen:
    Tsmos_DeactivateControllerState();
    Frontend_StartMenuImageTransition(g_optionsShortcutScreen);
    g_optionsShortcutScreen->shown = 1;
    g_optionsShortcutScreen->timer = -1;
    Widget_SetWidgetFlag08(g_optionsShortcutScreen->window, 1);
    Widget_SetWidgetFlag08(g_optionsShortcutScreen->second_window, 1);
    Cinema_ReleaseSequenceContext();
    goto done;
code_17:
    Random_SetMenuChoiceResult(23);
    goto done;
retry:
    Tsmos_DeactivateControllerState();
    if (ScenarioSetup_StartRandomCupStage() == 0) {
        g_optionsShortcutScreen->mode = 5;
        g_optionsShortcutScreen->next_mode = 4;
        g_optionsShortcutScreen->timer = 20;
    } else {
        Frontend_StartMenuImageTransition(g_optionsShortcutScreen);
        g_optionsShortcutScreen->shown = 1;
        g_optionsShortcutScreen->timer = 0;
    }
    goto done;
code_13:
    Random_SetMenuChoiceResult(13);
    goto done;
code_12:
    Random_SetMenuChoiceResult(12);
    goto done;
code_14:
    Random_SetMenuChoiceResult(14);
    goto done;
other:
    handled = 0;
done:
    if (handled == 1) {
        Menu_CommitTabOptionsPage();
    }
    return 0;
}

s32 Frontend_ConsumeTabOptionsEvent(void) {
    MarkMenuEventHandled();
    return 0;
}

s32 Frontend_DispatchTabOptionsEvent(void *menuActor, s32 eventKind, s32 eventDataOne, s32 eventDataTwo, s32 eventDataThree) {
    TabOptionsEventHandler *entry;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;
    MenuActorInputView *actor;

    if (g_tabOptionsEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_tabOptionsEventHandlers;
        index = 0;
        do {
            if (g_tabOptionsEventKinds[index].value == eventKind) {
                actor = menuActor;
                actor_kind = actor->input;
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
