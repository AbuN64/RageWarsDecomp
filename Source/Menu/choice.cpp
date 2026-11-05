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

/* The option each row selects; the row that cancels holds PAK_ACTION_CANCEL. */
#define PAK_ACTION_CANCEL (-1)
#if defined(VERSION_EU_X)
static const s32 pakActionOptionByRow_menuAdvancefademeter[6] = { PAK_ACTION_CANCEL, 0, 3, 4, 2, 1 };
#else
static const s32 pakActionOptionByRow_menuAdvancefademeter[6] = { 4, 3, 0, 1, PAK_ACTION_CANCEL, 2 };
#endif

s32 Menu_ChoosePakActionOption(void) {
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
    option = pakActionOptionByRow_menuAdvancefademeter[message];
    if (option == PAK_ACTION_CANCEL) {
        g_pakActionMenuState->nextScreen = -1;
    } else {
        PAKInterface_SetScreenPhase(option);
        g_pakActionMenuState->nextScreen = 19;
    }
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
    ResidentEventHandlerEntry *handlers = (ResidentEventHandlerEntry *)g_pakActionMenuEventKinds;
    s32 row;
    for (row = 0; handlers[row].handler != 0; row++) {
        if (handlers[row].event == eventKind &&
            (handlers[row].actorKind == ((struct MenuWidget *)menuActor)->resource ||
             handlers[row].actorKind == ANY_ACTOR_KIND)) {
            return handlers[row].handler(menuActor, eventKind, eventDataOne, eventDataTwo, eventDataThree);
        }
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
