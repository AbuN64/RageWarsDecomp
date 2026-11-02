#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "include_asm.h"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SELECTIONSCREENSTATE.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "TYPES.H"
#include "COMMON/NUMBERPADSCREEN.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/ENTRYRECAT6C.H"
#include "FRONTEND/PAKINTERFACE_SETSCREENPHASE.H"
#include "MENU/MENU_ADVANCEFADEMETER.H"
#include "SCENE/CACHE_FREEMEMORY.H"

/* 80420E90_14.CPP */
#if defined(VERSION_DE)
#define ID_SCREEN 920
#define ID_SCREEN_B 921
#define ID_ROW0 927
#define ID_ROW1 926
#define ID_ROW2 929
#define ID_ROW3 925
#define ID_ROW4 924
#define ID_ROW5 928
#define ID_WINDOW 922
#define ID_LABEL 923
#elif defined(VERSION_EU_X)
#define ID_SCREEN 930
#define ID_SCREEN_B 931
#define ID_ROW0 939
#define ID_ROW1 935
#define ID_ROW2 938
#define ID_ROW3 936
#define ID_ROW4 937
#define ID_ROW5 934
#define ID_WINDOW 932
#define ID_LABEL 933
#else
#define ID_SCREEN 926
#define ID_SCREEN_B 927
#define ID_ROW0 933
#define ID_ROW1 932
#define ID_ROW2 935
#define ID_ROW3 931
#define ID_ROW4 930
#define ID_ROW5 934
#define ID_WINDOW 928
#define ID_LABEL 929
#endif

extern void Tsmos_ActivateControllerState(void);
extern struct MenuResourceWidget *SmpFlicker_CreateFlickerWidget(int widgetResourceId, int ownerValue);
extern s32 SmpFade_CreateFadeWidget(s32, s32);
extern void SmpSlider_EnableTransition(struct Access_s32_5C *object);
extern ChoiceMenuState *g_sixChoiceMenuState;

/* Builds the screen state g_sixChoiceMenuState: allocates it, opens screen 0x39E, registers six resources, opens window 0x3A0 and stores the 0x3A1 label. */
s32 Menu_CreateSixChoiceMenu(s32 root) {
    s32 screen;
    MenuWidget *window;

    g_sixChoiceMenuState = (ChoiceMenuState *) Cache_AllocateMemory(20);
    Tsmos_ActivateControllerState();
    screen = SmpFade_CreateFadeWidget(ID_SCREEN, ID_SCREEN_B);
    g_sixChoiceMenuState->slider = (struct ObjMenuUpdateSixChoiceMenu *) screen;
    SmpSlider_EnableTransition(screen);
    SmpButton_WrapButtonWidget(ID_ROW0);
    SmpButton_WrapButtonWidget(ID_ROW1);
    SmpButton_WrapButtonWidget(ID_ROW2);
    SmpButton_WrapButtonWidget(ID_ROW3);
    SmpButton_WrapButtonWidget(ID_ROW4);
    SmpButton_WrapButtonWidget(ID_ROW5);
    window = Node_FindWidgetByResourceId(root, ID_WINDOW);
    g_sixChoiceMenuState->transitionCell = (struct ChoiceMenuCellView *) window;
    window->alpha = 15;
    g_sixChoiceMenuState->labelFlicker = SmpFlicker_CreateFlickerWidget(ID_LABEL, 110);
    g_sixChoiceMenuState->transitionTimer = 3;
    return 0;
}

/* 80420E90_3.CPP */
extern void SmpSlider_SetTransitionMode(struct SliderTransitionView *object, s32 mode);

/* Releases the object g_sixChoiceMenuState holds through Cache_FreeMemory, clears g_sixChoiceMenuState and returns zero. */

/* Advances menu selection timing and dispatches the selected action. */

void SmXlate_SwitchScreen(s32);

                               /* extern */
void MarkMenuEventHandled();

                                  /* extern */

                                  /* extern */

                                  /* extern */
s32 SmpSlider_GetTransitionMode(s32 *record);

                          /* extern */



/* Handles the menu message Menu_GetFocusedElementId reports after MarkMenuEventHandled, for messages 0x3A2 to 0x3A7
   through k_menuChooseSixChoiceOptionJumpTable: five pick option 0, 1, 3, 4 or 2, pass it to PAKInterface_SetScreenPhase and set the
   result word at offset 0x10 of the screen g_sixChoiceMenuState to 0x13; the sixth sets it to -1. Both then
   close the screen's first word through SmpSlider_SetTransitionMode with 2. Returns zero. */

extern s32 Menu_GetFocusedElementId(void);

/* Calls MarkMenuEventHandled, then sets the word at offset 0x10 of the object g_sixChoiceMenuState points to to -1 and
   calls SmpSlider_SetTransitionMode on the object's first word with 2, returning zero. */

/* Dispatches event eventKind through this file's 12-byte handler table, whose rows hold an event at g_sixChoiceMenuEventKinds, an actor kind at g_sixChoiceMenuActorKinds and a handler at g_sixChoiceMenuEventHandlers: the first row whose event equals eventKind and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from N64Eng_DispatchNumericWidgetEvent. */

/* Advances a filling or draining bar by the step and writes its level byte at 0x10 of the bar at
   0xC: while rising it scales the amount for the display and, at or above the wrap point, stores
   the remainder with the high bit set, and it finishes at 1000 by storing 0xFF, marking 0x4 and
   calling Tsmos_ActivateControllerState; while falling it does the same from the other pair of constants and
   finishes at zero. Returns the finished flag. */

/* Resets a five-word record: clears the first three words, stores a value in the fourth and one
   in the fifth, then calls Tsmos_DeactivateControllerState. */

s32 Menu_DestroySixChoiceMenu(void) {
    Cache_FreeMemory(g_sixChoiceMenuState);
    g_sixChoiceMenuState = 0;
    return 0;
}



s32 Menu_UpdateSixChoiceMenu(void) {
    s32 transitionModeResult;
    s32 remainingFrames;
    s32 nextScreen;
    ChoiceMenuCellView *choiceCell;
    ChoiceMenuCellView *decrementedChoiceCell;

    if (g_selectionMessageStage >= 2) {
        Tsmos_DeactivateControllerState();
        return 0;
    }
    Tsmos_ActivateControllerState();
    transitionModeResult = SmpSlider_GetTransitionMode(g_sixChoiceMenuState->slider);
    switch (transitionModeResult) {                              /* irregular */
    case 3:
        remainingFrames = g_sixChoiceMenuState->transitionTimer - 1;
        g_sixChoiceMenuState->transitionTimer = remainingFrames;
        if (remainingFrames <= 0) {
            decrementedChoiceCell = g_sixChoiceMenuState->transitionCell;
            decrementedChoiceCell->transitionTimer = (u16) (decrementedChoiceCell->transitionTimer - 1);
            choiceCell = g_sixChoiceMenuState->transitionCell;
            if (((s16) choiceCell->transitionTimer + choiceCell->transitionDuration) < 0) {
                choiceCell->transitionTimer = (u16) g_sixChoiceMenuState->slider->transitionCell->transitionDuration;
            }
            g_sixChoiceMenuState->transitionTimer = transitionModeResult;
        }
block_12:
        return 0;
    case 4:
        MarkMenuEventHandled();
        nextScreen = g_sixChoiceMenuState->nextScreen;
        if (nextScreen == -1) {
            nextScreen = 3;
        }
        SmXlate_SwitchScreen(nextScreen);
        goto block_12;
    default:
        return 0;
    }
}

s32 Menu_ChooseSixChoiceOption(void) {
    s32 option;
    u32 message;
    MarkMenuEventHandled();
#if defined(VERSION_DE)
    message = Menu_GetFocusedElementId() - 924;
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    message = Menu_GetFocusedElementId() - 930;
#elif defined(VERSION_EU_X)
    message = Menu_GetFocusedElementId() - 934;
#endif
    if (message >= 6) {
        return 0;
    }
    switch (message) {
#if defined(VERSION_EU_X)
        case 0: goto cancel;
        case 1: goto option_0;
        case 2: goto option_3;
        case 3: goto option_4;
        case 4: goto option_2;
        case 5: goto option_1;
#else
        case 0: goto option_4;
        case 1: goto option_3;
        case 2: goto option_0;
        case 3: goto option_1;
        case 4: goto cancel;
        case 5: goto option_2;
#endif
        }
option_0:
    option = 0;
    goto choose;
option_1:
    option = 1;
    goto choose;
option_3:
    option = 3;
    goto choose;
option_4:
    option = 4;
    goto choose;
option_2:
    option = 2;
choose:
    PAKInterface_SetScreenPhase(option);
    g_sixChoiceMenuState->nextScreen = 19;
    goto close;
cancel:
    g_sixChoiceMenuState->nextScreen = -1;
close:
    SmpSlider_SetTransitionMode(g_sixChoiceMenuState->slider, 2);
done:
    return 0;
}

s32 Menu_CancelSixChoiceMenu(void) {
    ChoiceMenuState *state;

    MarkMenuEventHandled();
    state = g_sixChoiceMenuState;
    state->nextScreen = -1;
    SmpSlider_SetTransitionMode(state->slider, 2);
    return 0;
}

s32 Menu_DispatchSixChoiceEvent(void *menuActor, s32 eventKind, s32 eventDataOne, s32 eventDataTwo, s32 eventDataThree) {
    char *entry;
    s32 offset;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;

    if (g_sixChoiceMenuEventHandlers != 0) {
        wildcard = 30000;
        entry = (char *)&g_sixChoiceMenuEventHandlers;
        offset = 0;
        do {
            if (((struct AnimationEventMaskView *) (((char *) (&g_sixChoiceMenuEventKinds)) + offset))->value == eventKind) {
                actor_kind = ((struct MenuActorInputView *) ((char *) menuActor))->input;
                table_kind = ((struct AnimationEventMaskView *) (((char *) (&g_sixChoiceMenuActorKinds)) + offset))->value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*(WidgetEventHandler *)entry)(menuActor, eventKind, eventDataOne, eventDataTwo, eventDataThree);
                }
            }
            entry += sizeof(ResidentEventHandlerEntry);
            offset += 12;
        } while (*(WidgetEventHandler *)entry != 0);
    }
    return 0;
}

/* Returns the word at offset 0x4 of a record. */
s32 Menu_GetFadeMeterDone(s32 *record) {
    return ((struct Triple *)record)->y;
}

/* Switches a timer record to a new mode: when the mode at offset 8 changes it stores the mode,
   loads the countdown at offset 0 with 1000 for a non-zero mode or zero otherwise, and clears the
   word at offset 4. */

void Menu_SetFadeMeterDirection(struct Triple *timer, s32 mode) {
    if (timer->z != mode) {
        timer->z = mode;
        if (mode == 0) {
            timer->x = 0;
        } else {
            timer->x = 1000;
        }
        timer->y = 0;
    }
}

s32 Menu_AdvanceFadeMeter(struct Meter *meter, s32 step) {
    struct ResourceSmpFlickerCreateFlickerWidget *bar;
    s32 level;
    f32 value;

    if (meter->done == 0) {
        if (meter->falling == 0) {
            if (meter->amount < 1000) {
                value = (f32)meter->amount * k_menuFadeInConstants;
                bar = meter->bar;
                if (!(value >= *(&k_menuFadeInConstants + 1))) {
                    level = (s32)value;
                } else {
                    level = (s32)(value - *(&k_menuFadeInConstants + 1)) | 0x80000000;
                }
                bar->value = level;
            } else {
                meter->bar->value = 0xFF;
                meter->done = 1;
                Tsmos_ActivateControllerState();
            }
            meter->amount = meter->amount + step;
        } else {
            if (meter->amount > 0) {
                value = (f32)meter->amount * k_menuFadeOutConstants;
                bar = meter->bar;
                if (!(value >= *(&k_menuFadeOutConstants + 1))) {
                    level = (s32)value;
                } else {
                    level = (s32)(value - *(&k_menuFadeOutConstants + 1)) | 0x80000000;
                }
                bar->value = level;
            } else {
                meter->bar->value = 0;
                meter->done = 1;
                Tsmos_ActivateControllerState();
            }
            meter->amount = meter->amount - step;
        }
    }
    return meter->done;
}

void Menu_InitializeFadeMeter(struct RecGobjinstSampleBoneTranslation *record, s32 value) {
    record->y = 0;
    record->x = 0;
    record->z = 0;
    record->pad0 = value;
    record->pad1 = 1;
    Tsmos_DeactivateControllerState();
}

#if defined(VERSION_US)
unsigned int k_MenuAdvancefademeterEncodedWords[2] = {
    0x000F000A, 0x00040000,
};
#endif

#if defined(VERSION_EU_X)
unsigned int k_MenuAdvancefademeterEncodedWordsBlock2[2] = {
    0x0044333C, 0x0044333C,
};
#endif

#if defined(VERSION_EU)
unsigned int k_MenuAdvancefademeterEncodedWordsBlock3[2] = {
    0x0800FFB6, 0x0800FFB7,
};
#endif

#if defined(VERSION_DE)
unsigned int k_MenuAdvancefademeterEncodedWordsBlock1[2] = {
    0x3E828F5D, 0x4F000000,
};
#endif
