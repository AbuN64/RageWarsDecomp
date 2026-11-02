#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/ACCESS_S8_10F.H"
#include "include_asm.h"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/MENU_INITIALIZEOPTIONSSCENE.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "TYPES.H"
#include "MENU/MENU_DISPATCHOPTIONSTRANSITIONEVENT.H"
#include "SCENE/CACHE_FREEMEMORY.H"
#include "FRONTEND/MENUIMAGE.H"
#include "COMMON/NUMBERPADSCREEN.H"
#include "MENU/OPTIONTRANSITION.H"
#include "DATA/OVLTBL/MENU_DRAWOPTIONSIMAGETRANSITION_DATA.H"

/* OPTIONTRANSITION.CPP */
extern s32 Frontend_GetMenuImageState(s32 *record);
extern struct Record *Cache_AllocateMemory(s32 size);
extern void Frontend_InitMenuImage(s32 *, s32, s32, s32, s32);

s32 Menu_CreateOptionsImageTransition(void) {
    s32 *record = Cache_AllocateMemory(36);
    g_optionsImageTransition = record;
    record[7] = 0;
    record[8] = 0;
    Frontend_InitMenuImage(record, 103, 0, 0, 0);
    return 0;
}

/* Releases the object g_optionsImageTransition_Optiontransition holds through Cache_FreeMemory, clears g_optionsImageTransition_Optiontransition and returns zero. */

/* Event callback for screen g_optionsImageTransition_Optiontransition: on event 1 while Frontend_GetMenuImageState reports the screen in state
   1 it advances the screen through Frontend_DrawMenuImage and Frontend_AdvanceMenuImageTransition, and when that leaves it in
   state 2 it tears the match display down through Menu_ReleaseOptionsScene and Stage_StartConfiguredMatch and calls
   Control_SetControllerMode_Optiontransition(1). Returns zero. */

extern void Frontend_DrawMenuImage(struct MenuImage *menu);

#if defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US) || defined(VERSION_US_REV1)
#else
extern void Menu_ReleaseOptionsScene_Optiontransition(void);
#endif

extern void Stage_StartConfiguredMatch(void);

/* Unless Frontend_GetMenuImageState reports one for the object g_optionsImageTransition_Optiontransition holds, calls Tsmos_ActivateControllerState and, when
   the object's word at 0x20 is one, calls Tsmos_DeactivateControllerState, then Cinema_ReleaseSequenceContext_FrontendHandletaboptionsshortcut and ScenarioSetup_ResetSelectionIndicators unless
   the option byte g_gameControllerMode is set, and finally resets the object through Frontend_StartMenuImageTransition. Returns
   zero. */

extern void Tsmos_ActivateControllerState(void);

extern void Tsmos_DeactivateControllerState(void);

extern void ScenarioSetup_ResetSelectionIndicators(void);

extern void Frontend_StartMenuImageTransition(s32 *record);

/* On event 3 with value 0xB, calls MarkMenuEventHandled and sets the word at offset 0x20 of the object
   g_optionsImageTransition_Optiontransition points to. Returns zero. */

extern void MarkMenuEventHandled();

/* Sets the word at offset 0x20 of the object g_optionsImageTransition_Optiontransition points to and returns zero. */

/* Dispatches event event through this file's 12-byte handler table, whose rows hold an event at g_optionsTransitionEventCodes, an actor kind at g_optionsTransitionActorKinds and a handler at g_optionsTransitionEventCallbacks: the first row whose event equals event and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from N64Eng_DispatchNumericWidgetEvent. */

s32 Menu_DestroyOptionsImageTransition(void) {
    Cache_FreeMemory(g_optionsImageTransition);
    g_optionsImageTransition = 0;
    return 0;
}

s32 Menu_DrawOptionsImageTransition(s32 unused0, s32 unused1, s32 event) {
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
    char *entry;
    s32 offset;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;

    if (g_optionsTransitionEventCallbacks != 0) {
        wildcard = 30000;
        entry = (char *)&g_optionsTransitionEventCallbacks;
        offset = 0;
        do {
            if (((struct AnimationEventMaskView *) (((char *) (&g_optionsTransitionEventCodes)) + offset))->value == event) {
                actor_kind = ((struct MenuActorInputView *) ((char *) object))->input;
                table_kind = ((struct AnimationEventMaskView *) (((char *) (&g_optionsTransitionActorKinds)) + offset))->value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*(WidgetEventHandler *)entry)(object, event, eventData, eventValue, eventContext);
                }
            }
            entry += sizeof(ResidentEventHandlerEntry);
            offset += 12;
        } while (*(WidgetEventHandler *)entry != 0);
    }
    return 0;
}

/* MENU_DRAWOPTIONSIMAGETRANSITION_DATA.CPP */
extern s32 PAKInterface_HandlePlayerPanelBack(void *unused0, void *unused1, u16 player);
extern char g_Menu_ConsumeOptionsTransitionEventPackedAddress24[];
extern char g_Menu_CreateOptionsImageTransitionPackedAddress24[];
extern char g_Menu_DestroyOptionsImageTransitionPackedAddress24[];
extern char g_Menu_DrawOptionsImageTransitionPackedAddress24[];
extern char g_Menu_HandleOptionsTransitionRequestPackedAddress24[];
extern char g_Menu_RequestOptionsImageTransitionPackedAddress24[];
extern char g_Menu_StartOptionsImageTransitionPackedAddress24[];

/* 800E449C_2.CPP */
/* ROM-grounded data: rodata/writable/800E44A0 */
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

/* 800E44A4.CPP */
#if !(defined(VERSION_US) || defined(VERSION_US_REV1))
#if defined(VERSION_DE)
extern char g_Menu_DispatchSixChoiceEventAddress[];
#if defined(VERSION_DE)
struct {
    ResidentEventHandlerEntry handlers[8];
    u32 alignmentFill[3];
} g_optiontransitionRecord __attribute__((aligned(4))) = {
    { { 3590, 25, (ResidentEventHandler)(void *)(g_Menu_DispatchSixChoiceEventAddress + 1120) }, { 3587, 25, (ResidentEventHandler)(void *)(g_Menu_DispatchSixChoiceEventAddress + 1192) }, { 2, 25, (ResidentEventHandler)(void *)(g_Menu_DispatchSixChoiceEventAddress + 1628) }, { 1, 25, (ResidentEventHandler)(void *)(g_Menu_DispatchSixChoiceEventAddress + 1604) }, { 3594, 25, (ResidentEventHandler)(void *)(g_Menu_DispatchSixChoiceEventAddress + 1240) }, { 3592, 25, (ResidentEventHandler)(void *)(g_Menu_DispatchSixChoiceEventAddress + 1392) }, { 10, 25, (ResidentEventHandler)(void *)(g_Menu_DispatchSixChoiceEventAddress + 1532) }, { 0, 0, (ResidentEventHandler)0 } },
    { 0x00000000, 0x00000000, 0x00000E08 }
};
#endif
#endif
#if defined(VERSION_EU)
#if defined(VERSION_EU)
struct {
    ResidentEventHandlerEntry handlers[8];
    u32 alignmentFill[3];
} g_optiontransitionRecord __attribute__((aligned(4))) = {
    { { 3590, 25, (ResidentEventHandler)(void *)&g_Menu_CreateOptionsImageTransitionPackedAddress24 }, { 3587, 25, (ResidentEventHandler)(void *)&g_Menu_DestroyOptionsImageTransitionPackedAddress24 }, { 2, 25, (ResidentEventHandler)(void *)&g_Menu_ConsumeOptionsTransitionEventPackedAddress24 }, { 1, 25, (ResidentEventHandler)(void *)&g_Menu_RequestOptionsImageTransitionPackedAddress24 }, { 3594, 25, (ResidentEventHandler)(void *)&g_Menu_DrawOptionsImageTransitionPackedAddress24 }, { 3592, 25, (ResidentEventHandler)(void *)&g_Menu_StartOptionsImageTransitionPackedAddress24 }, { 10, 25, (ResidentEventHandler)(void *)&g_Menu_HandleOptionsTransitionRequestPackedAddress24 }, { 0, 0, (ResidentEventHandler)0 } },
    { 0xA702000C, 0x001A1402, 0x30410008 }
};
#endif
#endif
#if defined(VERSION_EU_X)
#if defined(VERSION_EU_X)
ResidentEventHandlerEntry g_optiontransitionRecord[9] = {
    { 3590, 25, (ResidentEventHandler)(void *)((char *)&Menu_CreateOptionsImageTransition - 0x80000000U) }, { 3587, 25, (ResidentEventHandler)(void *)((char *)&Menu_DestroyOptionsImageTransition - 0x80000000U) }, { 2, 25, (ResidentEventHandler)(void *)((char *)&Menu_ConsumeOptionsTransitionEvent - 0x80000000U) }, { 1, 25, (ResidentEventHandler)(void *)((char *)&Menu_RequestOptionsImageTransition - 0x80000000U) }, { 3594, 25, (ResidentEventHandler)(void *)((char *)&Menu_DrawOptionsImageTransition - 0x80000000U) }, { 3592, 25, (ResidentEventHandler)(void *)((char *)&Menu_StartOptionsImageTransition - 0x80000000U) }, { 10, 25, (ResidentEventHandler)(void *)((char *)&Menu_HandleOptionsTransitionRequest - 0x80000000U) }, { 0, 0, (ResidentEventHandler)0 },
    { 2, 19, (ResidentEventHandler)(void *)((char *)&PAKInterface_HandlePlayerPanelBack - 0x80000000U) }
};
#endif
#endif
#endif

#if defined(VERSION_US) || defined(VERSION_US_REV1)
/* ROM-grounded us-rev1 data; explicit withholding in other holders. */
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

/* G_LINKTABLESENCODEDWORDSBLOCK15.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800E44A4_unclaimed_E5104 */
extern char g_frontend_HandlePakProfileInputEntry[];
#if defined(VERSION_US_REV1)
struct {
    void * previousHandler;
    s32 event;
    s32 actorKind;
} g_LinktablesEncodedWordsBlock15 __attribute__((aligned(4))) = {
    (void *)&g_frontend_HandlePakProfileInputEntry,
    11,
    19
};
typedef char g_LinktablesEncodedWordsBlock15SizeCheck[(sizeof(g_LinktablesEncodedWordsBlock15) == 12) ? 1 : -1];
#endif
#endif
