#include "Common/resident_event_handler.h"
#include "Common/access_s8_10f.h"
#include "include_asm.h"
#include "Common/runtime_declarations.h"
#include "Common/shared_gameslot.h"
#include "Common/menu_initializeoptionsscene.h"
#include "Common/sharedplayer.h"
#include "Common/aiprofile.h"
#include "types.h"
#include "Menu/menu_dispatchoptionstransitionevent.h"
#include "Scene/cache_freememory.h"
#include "Frontend/menuimage.h"
#include "Common/numberpadscreen.h"
#include "Menu/optiontransition.h"
#include "Data/Ovltbl/menu_drawoptionsimagetransition_data.h"
#include "Frontend/menu_image.h"
#include "Common/shared_menureply.h"
#include "Common/selectionscreenstate.h"
#include "Common/statepair.h"
#include "Engine/control.h"
#include "Common/screen.h"
#include "Menu/event.h"
#include "Common/menu_options_and_results.h"
#include "Ui/pakinterface_handlenextpanelselection.h"
#include "Menu/Optiontransition/optiontransition_symbols.h"
#include "Frontend/frontend.h"

s32 Menu_CreateOptionsImageTransition(void) {
    s32 *record = Cache_AllocateMemory(36);
    g_optionsImageTransition = record;
    record[7] = 0;
    record[8] = 0;
    Frontend_InitMenuImage(record, 103, 0, 0, 0);
    return 0;
}

/* Dispatches event event through this file's 12-byte handler table, whose rows hold an event at g_optionsTransitionEventCodes, an actor kind at g_optionsTransitionActorKinds and a handler at g_optionsTransitionEventCallbacks: the first row whose event equals event and whose kind equals the actor's input kind, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. */
s32 Menu_DestroyOptionsImageTransition(void) {
    Cache_FreeMemory(g_optionsImageTransition);
    g_optionsImageTransition = 0;
    return 0;
}

s32 Menu_DrawOptionsImageTransition(s32 element, s32 eventId, s32 event) {
    if (event == 1) {
        if (Frontend_GetMenuImageState(g_optionsImageTransition) != 1) {
            return 0;
        }
        Frontend_DrawMenuImage(g_optionsImageTransition);
        Frontend_AdvanceMenuImageTransition(g_optionsImageTransition);
        if (Frontend_GetMenuImageState(g_optionsImageTransition) != 2) {
            return 0;
        }
#if defined(VERSION_DE)
        Menu_ReleaseOptionsScene();
#else

#if defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US) || defined(VERSION_US_REV1)
Menu_ReleaseOptionsScene
#else
Menu_ReleaseOptionsScene_Optiontransition
#endif
();
#endif
        Stage_StartConfiguredMatch();
        Control_SetControllerMode(1);
    }
    return 0;
}

s32 Menu_StartOptionsImageTransition(void) {
    s32 one = 1;

    if (Frontend_GetMenuImageState(g_optionsImageTransition) == one) {
        return 0;
    }
    Tsmos_ActivateControllerState();
    if (g_optionsImageTransition[8] != one) {
        return 0;
    }
    Tsmos_DeactivateControllerState();
    if (g_gameSettings.controllerMode == 0) {
        Cinema_ReleaseSequenceContext();
        ScenarioSetup_ResetSelectionIndicators();
    }
    Frontend_StartMenuImageTransition(g_optionsImageTransition);
    return 0;
}

s32 Menu_HandleOptionsTransitionRequest(void *first, void *second, u32 event, s32 value) {
    if ((event >> 16) == 3 && value == 11) {
        MarkMenuEventHandled();
        g_optionsImageTransition[8] = 1;
    }
    return 0;
}

s32 Menu_RequestOptionsImageTransition(void) {
    g_optionsImageTransition[8] = 1;
    return 0;
}

s32 Menu_ConsumeOptionsTransitionEvent(void) {
    MarkMenuEventHandled();
    return 0;
}

s32 Menu_DispatchOptionsTransitionEvent(void *object, s32 event, s32 eventData, s32 eventValue, s32 eventContext) {
    ResidentEventHandlerEntry *handlers = (ResidentEventHandlerEntry *)g_optionsTransitionEventCodes;
    s32 row;
    for (row = 0; handlers[row].handler != 0; row++) {
        if (handlers[row].event == event &&
            (handlers[row].actorKind == ((struct MenuWidget *)object)->resource ||
             handlers[row].actorKind == ANY_ACTOR_KIND)) {
            return handlers[row].handler(object, event, eventData, eventValue, eventContext);
        }
    }
    return 0;
}

#if defined(VERSION_DE)
struct {
    void * g_optionsImageTransition;
} k_MenuDrawoptionsimagetransitionZeroWords __attribute__((aligned(4))) = {
    0
};
typedef char k_MenuDrawoptionsimagetransitionZeroWordsSizeCheck[(sizeof(k_MenuDrawoptionsimagetransitionZeroWords) == 4) ? 1 : -1];
#endif
#if defined(VERSION_EU)
struct {
    void * g_optionsImageTransition;
} k_MenuDrawoptionsimagetransitionZeroWords __attribute__((aligned(4))) = {
    0
};
typedef char k_MenuDrawoptionsimagetransitionZeroWordsSizeCheck[(sizeof(k_MenuDrawoptionsimagetransitionZeroWords) == 4) ? 1 : -1];
#endif
#if defined(VERSION_EU_X)
struct {
    void * g_optionsImageTransition;
} k_MenuDrawoptionsimagetransitionZeroWords __attribute__((aligned(4))) = {
    0
};
typedef char k_MenuDrawoptionsimagetransitionZeroWordsSizeCheck[(sizeof(k_MenuDrawoptionsimagetransitionZeroWords) == 4) ? 1 : -1];
#endif
#if defined(VERSION_US)
struct {
    void * g_optionsImageTransition;
} k_MenuDrawoptionsimagetransitionZeroWords __attribute__((aligned(4))) = {
    0
};
typedef char k_MenuDrawoptionsimagetransitionZeroWordsSizeCheck[(sizeof(k_MenuDrawoptionsimagetransitionZeroWords) == 4) ? 1 : -1];
#endif
#if defined(VERSION_US_REV1)
struct {
    void * g_optionsImageTransition;
} k_MenuDrawoptionsimagetransitionZeroWords __attribute__((aligned(4))) = {
    0
};
typedef char k_MenuDrawoptionsimagetransitionZeroWordsSizeCheck[(sizeof(k_MenuDrawoptionsimagetransitionZeroWords) == 4) ? 1 : -1];
#endif

#if !(defined(VERSION_US) || defined(VERSION_US_REV1))
#if defined(VERSION_DE)
struct {
    ResidentEventHandlerEntry handlers[8];
    u32 retainedEventWords[3];
} g_optiontransitionRecord __attribute__((aligned(4))) = {
    { { 3590, 25, (ResidentEventHandler)(void *)(addrLow_Menu_DispatchPakActionEvent + 1120) }, { 3587, 25, (ResidentEventHandler)(void *)(addrLow_Menu_DispatchPakActionEvent + 1192) }, { 2, 25, (ResidentEventHandler)(void *)(addrLow_Menu_DispatchPakActionEvent + 1628) }, { 1, 25, (ResidentEventHandler)(void *)(addrLow_Menu_DispatchPakActionEvent + 1604) }, { 3594, 25, (ResidentEventHandler)(void *)(addrLow_Menu_DispatchPakActionEvent + 1240) }, { 3592, 25, (ResidentEventHandler)(void *)(addrLow_Menu_DispatchPakActionEvent + 1392) }, { 10, 25, (ResidentEventHandler)(void *)(addrLow_Menu_DispatchPakActionEvent + 1532) }, { 0, 0, (ResidentEventHandler)0 } },
    { 0x00000000, 0x00000000, 0x00000E08 }
};
#endif
#if defined(VERSION_EU)
struct {
    ResidentEventHandlerEntry handlers[8];
    u32 retainedInstructionWords[3];
} g_optiontransitionRecord __attribute__((aligned(4))) = {
    { { 3590, 25, (ResidentEventHandler)(void *)&addrLow_Menu_CreateOptionsImageTransition }, { 3587, 25, (ResidentEventHandler)(void *)&addrLow_Menu_DestroyOptionsImageTransition }, { 2, 25, (ResidentEventHandler)(void *)&addrLow_Menu_ConsumeOptionsTransitionEvent }, { 1, 25, (ResidentEventHandler)(void *)&addrLow_Menu_RequestOptionsImageTransition }, { 3594, 25, (ResidentEventHandler)(void *)&addrLow_Menu_DrawOptionsImageTransition }, { 3592, 25, (ResidentEventHandler)(void *)&addrLow_Menu_StartOptionsImageTransition }, { 10, 25, (ResidentEventHandler)(void *)&addrLow_Menu_HandleOptionsTransitionRequest }, { 0, 0, (ResidentEventHandler)0 } },
    { 0xA702000C, 0x001A1402, 0x30410008 }
};
#endif
#if defined(VERSION_EU_X)
ResidentEventHandlerEntry g_optiontransitionRecord[9] = {
    { 3590, 25, ResidentCodeOffset(Menu_CreateOptionsImageTransition) }, { 3587, 25, ResidentCodeOffset(Menu_DestroyOptionsImageTransition) }, { 2, 25, ResidentCodeOffset(Menu_ConsumeOptionsTransitionEvent) }, { 1, 25, ResidentCodeOffset(Menu_RequestOptionsImageTransition) }, { 3594, 25, ResidentCodeOffset(Menu_DrawOptionsImageTransition) }, { 3592, 25, ResidentCodeOffset(Menu_StartOptionsImageTransition) }, { 10, 25, ResidentCodeOffset(Menu_HandleOptionsTransitionRequest) }, { 0, 0, (ResidentEventHandler)0 },
    { 2, 19, ResidentCodeOffset(PAKInterface_HandlePlayerPanelBack) }
};
#endif
#endif

#if defined(VERSION_US) || defined(VERSION_US_REV1)
#if defined(VERSION_US)
ResidentEventHandlerEntry g_MenuDrawoptionsimagetransitionEncodedWords[8] = {
    { 3590, 25, (ResidentEventHandler)(void *)&g_menu_CreateOptionsImageTransitionEntry }, { 3587, 25, (ResidentEventHandler)(void *)&g_menu_DestroyOptionsImageTransitionEntry }, { 2, 25, (ResidentEventHandler)(void *)&g_menu_ConsumeOptionsTransitionEventEntry }, { 1, 25, (ResidentEventHandler)(void *)&g_menu_RequestOptionsImageTransitionEntry }, { 3594, 25, (ResidentEventHandler)(void *)&g_menu_DrawOptionsImageTransitionEntry }, { 3592, 25, (ResidentEventHandler)(void *)&g_menu_StartOptionsImageTransitionEntry }, { 10, 25, (ResidentEventHandler)(void *)&g_menu_HandleOptionsTransitionRequestEntry }, { 0, 0, (ResidentEventHandler)0 }
};
#endif
#if defined(VERSION_US_REV1)
ResidentEventHandlerEntry g_MenuDrawoptionsimagetransitionEncodedWords[8] = {
    { 3590, 25, (ResidentEventHandler)(void *)&g_menu_CreateOptionsImageTransitionEntry }, { 3587, 25, (ResidentEventHandler)(void *)&g_menu_DestroyOptionsImageTransitionEntry }, { 2, 25, (ResidentEventHandler)(void *)&g_menu_ConsumeOptionsTransitionEventEntry }, { 1, 25, (ResidentEventHandler)(void *)&g_menu_RequestOptionsImageTransitionEntry }, { 3594, 25, (ResidentEventHandler)(void *)&g_menu_DrawOptionsImageTransitionEntry }, { 3592, 25, (ResidentEventHandler)(void *)&g_menu_StartOptionsImageTransitionEntry }, { 10, 25, (ResidentEventHandler)(void *)&g_menu_HandleOptionsTransitionRequestEntry }, { 0, 0, (ResidentEventHandler)0 }
};
#endif
#endif

#if defined(VERSION_US_REV1)
struct {
    void * previousHandler;
    s32 event;
    s32 actorKind;
} g_pakProfileInputHandlerLink __attribute__((aligned(4))) = {
    (void *)&g_frontend_HandlePakProfileInputEntry,
    11,
    19
};
typedef char g_pakProfileInputHandlerLinkSizeCheck[(sizeof(g_pakProfileInputHandlerLink) == 12) ? 1 : -1];
#endif
