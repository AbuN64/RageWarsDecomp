#include "Common/resident_event_handler.h"
#include "include_asm.h"
#include "Common/runtime_declarations.h"
#include "Common/selectionscreenstate.h"
#include "types.h"
#include "Common/numberpadscreen.h"
#include "Common/sharedplayer.h"
#include "Common/aiprofile.h"
#include "Common/pak_player_panel.h"
#include "Frontend/pakinterface_setscreenphase.h"
#include "Menu/menu_advancefademeter.h"
#include "Scene/cache_freememory.h"
#include "Ui/Tsmos/Smp/smp_fade.h"
#include "Common/shared_menureply.h"
#include "Common/screen.h"
#include "Common/animation.h"
#include "Ui/smp_slider.h"
#include "Menu/Choice/menu_advancefademeter_symbols.h"
#include "Frontend/frontend.h"

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

/* Builds the screen state g_pakActionMenuState: allocates it, opens screen 0x39E, registers six resources, opens window 0x3A0 and stores the 0x3A1 label. */
s32 Menu_CreatePakActionMenu(s32 root) {
    s32 screen;
    MenuWidget *window;

    g_pakActionMenuState = (ChoiceMenuState *) Cache_AllocateMemory(20);
    Tsmos_ActivateControllerState();
    screen = SmpFade_CreateFadeWidget(ID_SCREEN, ID_SCREEN_B);
    g_pakActionMenuState->slider = (struct ObjMenuUpdatePakActionMenu *) screen;
    SmpSlider_EnableTransition(screen);
    SmpButton_WrapButtonWidget(ID_ROW0);
    SmpButton_WrapButtonWidget(ID_ROW1);
    SmpButton_WrapButtonWidget(ID_ROW2);
    SmpButton_WrapButtonWidget(ID_ROW3);
    SmpButton_WrapButtonWidget(ID_ROW4);
    SmpButton_WrapButtonWidget(ID_ROW5);
    window = Node_FindWidgetByResourceId(root, ID_WINDOW);
    g_pakActionMenuState->transitionCell = (struct MenuWidget *) window;
    window->alpha = 15;
    g_pakActionMenuState->labelFlicker = SmpFlicker_CreateFlickerWidget(ID_LABEL, 110);
    g_pakActionMenuState->transitionTimer = 3;
    return 0;
}

/* Advances menu selection timing and dispatches the selected action. */



/* Resets a five-word record: clears the first three words, stores a value in the fourth and one
   in the fifth, then calls Tsmos_DeactivateControllerState. */
s32 Menu_DestroyPakActionMenu(void) {
    Cache_FreeMemory(g_pakActionMenuState);
    g_pakActionMenuState = 0;
    return 0;
}

s32 Menu_UpdatePakActionMenu(void) {
    s32 transitionModeResult;
    s32 remainingFrames;
    s32 nextScreen;
    MenuWidget *choiceCell;
    MenuWidget *decrementedChoiceCell;

    if (g_selectionMessageStage >= 2) {
        Tsmos_DeactivateControllerState();
        return 0;
    }
    Tsmos_ActivateControllerState();
    transitionModeResult = SmpSlider_GetTransitionMode(g_pakActionMenuState->slider);
    switch (transitionModeResult) {
    case 3:
        remainingFrames = g_pakActionMenuState->transitionTimer - 1;
        g_pakActionMenuState->transitionTimer = remainingFrames;
        if (remainingFrames <= 0) {
            decrementedChoiceCell = g_pakActionMenuState->transitionCell;
            decrementedChoiceCell->y = (u16) (decrementedChoiceCell->y - 1);
            choiceCell = g_pakActionMenuState->transitionCell;
            if (((s16) choiceCell->y + choiceCell->height) < 0) {
                choiceCell->y = (u16) g_pakActionMenuState->slider->transitionCell->height;
            }
            g_pakActionMenuState->transitionTimer = transitionModeResult;
        }
        return 0;
    case 4:
        MarkMenuEventHandled();
        nextScreen = g_pakActionMenuState->nextScreen;
        if (nextScreen == -1) {
            nextScreen = 3;
        }
        SmXlate_SwitchScreen(nextScreen);
        return 0;
    default:
        return 0;
    }
}

/* Screen phases the PAK action menu requests through PAKInterface_SetScreenPhase (the panel modes of the PAK
   interface screen). */
enum PakScreenPhase {
    PAK_PHASE_DEFAULT = 0,
    PAK_PHASE_PROFILE_SELECT = 1,
    PAK_PHASE_PAK_EVENT = 2,
    PAK_PHASE_TIMED_RESET = 3,
    PAK_PHASE_PAK_DIALOG = 4
};

/* Rows of the PAK action menu, in the order of their focused element ids; eu-x orders them differently. */
enum PakActionRow {
#if defined(VERSION_EU_X)
    PAK_ACTION_ROW_CANCEL,
    PAK_ACTION_ROW_DEFAULT,
    PAK_ACTION_ROW_TIMED_RESET,
    PAK_ACTION_ROW_PAK_DIALOG,
    PAK_ACTION_ROW_PAK_EVENT,
    PAK_ACTION_ROW_PROFILE_SELECT,
#else
    PAK_ACTION_ROW_PAK_DIALOG,
    PAK_ACTION_ROW_TIMED_RESET,
    PAK_ACTION_ROW_DEFAULT,
    PAK_ACTION_ROW_PROFILE_SELECT,
    PAK_ACTION_ROW_CANCEL,
    PAK_ACTION_ROW_PAK_EVENT,
#endif
    PAK_ACTION_ROW_COUNT
};

s32 Menu_ChoosePakActionOption(void) {
    s32 phase;
    u32 row;
    MarkMenuEventHandled();
#if defined(VERSION_DE)
    row = Menu_GetFocusedElementId() - 924;
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    row = Menu_GetFocusedElementId() - 930;
#elif defined(VERSION_EU_X)
    row = Menu_GetFocusedElementId() - 934;
#endif
    if (row >= PAK_ACTION_ROW_COUNT) {
        return 0;
    }
    switch (row) {
    case PAK_ACTION_ROW_PAK_DIALOG: goto choose_pak_dialog;
    case PAK_ACTION_ROW_TIMED_RESET: goto choose_timed_reset;
    case PAK_ACTION_ROW_DEFAULT: goto choose_default;
    case PAK_ACTION_ROW_PROFILE_SELECT: goto choose_profile_select;
    case PAK_ACTION_ROW_CANCEL: goto cancel;
    case PAK_ACTION_ROW_PAK_EVENT: goto choose_pak_event;
    }
choose_default:
    phase = PAK_PHASE_DEFAULT;
    goto choose;
choose_profile_select:
    phase = PAK_PHASE_PROFILE_SELECT;
    goto choose;
choose_timed_reset:
    phase = PAK_PHASE_TIMED_RESET;
    goto choose;
choose_pak_dialog:
    phase = PAK_PHASE_PAK_DIALOG;
    goto choose;
choose_pak_event:
    phase = PAK_PHASE_PAK_EVENT;
    goto choose;
choose:
    PAKInterface_SetScreenPhase(phase);
    g_pakActionMenuState->nextScreen = 19;
    goto close;
cancel:
    g_pakActionMenuState->nextScreen = -1;
close:
    SmpSlider_SetTransitionMode(g_pakActionMenuState->slider, 2);
    return 0;
}

s32 Menu_CancelPakActionMenu(void) {
    ChoiceMenuState *state;

    MarkMenuEventHandled();
    state = g_pakActionMenuState;
    state->nextScreen = -1;
    SmpSlider_SetTransitionMode(state->slider, 2);
    return 0;
}

s32 Menu_DispatchPakActionEvent(void *menuActor, s32 eventKind, s32 eventDataOne, s32 eventDataTwo, s32 eventDataThree) {
    char *entry;
    s32 offset;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;

    if (g_pakActionMenuEventHandlers != 0) {
        wildcard = 30000;
        entry = (char *)&g_pakActionMenuEventHandlers;
        offset = 0;
        do {
            if (((s32 *) (((char *) (&g_pakActionMenuEventKinds)) + offset))[0] == eventKind) {
                actor_kind = ((struct MenuWidget *) ((char *) menuActor))->resource;
                table_kind = ((s32 *) (((char *) (&g_pakActionMenuActorKinds)) + offset))[0];
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

/* Returns a field of a record. */
s32 Menu_GetFadeMeterDone(struct Meter *record) {
    return record->done;
}

/* Sets the fade meter's direction: when the falling flag changes it stores the new direction, resets
   the amount to 1000 for a falling meter or zero otherwise, and clears the done flag. */
void Menu_SetFadeMeterDirection(struct Meter *timer, s32 mode) {
    if (timer->falling != mode) {
        timer->falling = mode;
        if (mode == 0) {
            timer->amount = 0;
        } else {
            timer->amount = 1000;
        }
        timer->done = 0;
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
                    level = (s32)(value - *(&k_menuFadeInConstants + 1)) | 0x80000000U;
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
                    level = (s32)(value - *(&k_menuFadeOutConstants + 1)) | 0x80000000U;
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

void Menu_InitializeFadeMeter(struct FadeMeterRecord *record, s32 value) {
    record->resetState[1] = 0;
    record->resetState[0] = 0;
    record->resetState[2] = 0;
    record->value = value;
    record->initialized = 1;
    Tsmos_DeactivateControllerState();
}

#if defined(VERSION_US)
unsigned int k_MenuAdvancefademeterEncodedWords[2] = {
    0x000F000A, 0x00040000,
};
#endif

#if defined(VERSION_EU_X)
unsigned int k_menuAdvancefademeterFragment[2] = {
    0x0044333C, 0x0044333C,
};
#endif

#if defined(VERSION_EU)
unsigned int k_menuAdvancefademeterFragment[2] = {
    0x0800FFB6, 0x0800FFB7,
};
#endif

#if defined(VERSION_DE)
unsigned int k_menuAdvancefademeterFragment[2] = {
    0x3E828F5D, 0x4F000000,
};
#endif
#undef ID_SCREEN
#undef ID_SCREEN_B
#undef ID_ROW0
#undef ID_ROW1
#undef ID_ROW2
#undef ID_ROW3
#undef ID_ROW4
#undef ID_ROW5
#undef ID_WINDOW
#undef ID_LABEL
#undef PAK_ACTION_CANCEL

const unsigned int k_menuAdvancefademeterDataFloatConstantWords[4] = {
    0x3E828F5D, 0x4F000000, 0x3E828F5D, 0x4F000000,
};

#if defined(VERSION_US_REV1)
unsigned int g_choiceConstantWords[2] = {
    0x00442454, 0x00442454,
};
#endif
