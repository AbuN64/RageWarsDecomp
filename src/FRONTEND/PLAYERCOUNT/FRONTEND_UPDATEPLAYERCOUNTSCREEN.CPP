#include "COMMON/MENU_OPTIONS_AND_RESULTS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/SETTINGSRECAT24.H"
#include "TYPES.H"
#include "COMMON/SELECTIONSCREENSTATE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/PAKQUEUESTATE.H"
#include "COMMON/INTEGERSTATE530.H"
#include "FRONTEND/FRONTEND_DISPATCHPLAYERCOUNTEVENT.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"
#include "SCENE/CACHE_FREEMEMORY.H"
extern SettingsScreenState *g_playerCountScreen;
extern void SmpSlider_SetTransitionMode(struct SliderTransitionView *object, s32 mode);

/* Releases the object g_playerCountScreen holds through Cache_FreeMemory, clears g_playerCountScreen and returns zero. */



/* Runs the screen g_playerCountScreen each frame: past stage 1 of g_selectionMessageStage it only calls Tsmos_DeactivateControllerState;
   otherwise it calls Tsmos_ActivateControllerState and, while its menu reports 3, counts the delay at 0xC down and
   on expiry scrolls the list at 0x8 back one row, wrapping to the menu's own row count, and
   restarts the delay at 3; when the menu reports 4 it calls MarkMenuEventHandled and leaves through
   SmXlate_SwitchScreen with the stored target or Menu_ReturnToPreviousScreen when that is -1. Returns zero. Written
   from the assembly as a switch on the menu result, matching on the first trial. */








extern void Tsmos_DeactivateControllerState(void);

extern void Tsmos_ActivateControllerState(void);

extern s32 SmpSlider_GetTransitionMode(s32 *record);

extern void MarkMenuEventHandled();

extern void SmXlate_SwitchScreen(s32);


/* Activates the requested player slots and creates any missing players when entering the screen. */







extern SlotSelectionPlayerConfig g_playerSettings[];

extern s8 g_profileSlotIndices[];

extern void MarkMenuEventHandled(void);

/* Calls MarkMenuEventHandled, then sets the word at offset 0x10 of the object g_playerCountScreen points to to -1 and
   calls SmpSlider_SetTransitionMode on the object's first word with 2, returning zero. */




/* When the fourth argument is one, calls MarkMenuEventHandled, advances the word at 0x20 of the object g_playerCountScreen holds while Control_IsControllerConnected reports one for it and it is below Control_CountConnectedControllers_FrontendUpdateplayercountscreen's limit, formats that word into the object's text at 0x14 through XStdio_FormatBuffer with s_playerCountFormat, and plays sound 0xE81 through SoundElement_PlayFlatSound; returns zero.
   Adapted from Menu_StartOptionsImageTransition with the object chain changed to a guarded counter increment, text format and sound call. */








extern s32 XStdio_FormatBuffer(void *goal, s32 fmt0, ...);


/* Slider-down handler: when the fourth argument is one, calls MarkMenuEventHandled, lowers the value at
   offset 0x20 of the object g_playerCountScreen points to by one while it is at least 2, formats it into the
   text at offset 0x14 with s_playerCountFormat through XStdio_FormatBuffer and plays sound 0xE81. Returns zero. */




/* Dispatches event eventId through this file's 12-byte handler table, whose rows hold an event at g_playerCountEventIds, an actor kind at g_playerCountEventActorKinds and a handler at g_playerCountEventHandlers: the first row whose event equals eventId and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from N64Eng_DispatchNumericWidgetEvent. */

typedef s32 (*PlayerCountEventHandler)(void *, s32, s32, s32, s32);



extern PlayerCountEventHandler g_playerCountEventHandlers;

s32 Frontend_DestroyPlayerCountScreen(void) {
    Cache_FreeMemory(g_playerCountScreen);
    g_playerCountScreen = 0;
    return 0;
}

s32 Frontend_UpdatePlayerCountScreen(void) {
    s32 result;

    if (g_selectionMessageStage >= 2) {
        Tsmos_DeactivateControllerState();
        return 0;
    }
    Tsmos_ActivateControllerState();
    switch (result = SmpSlider_GetTransitionMode(g_playerCountScreen->head.menu)) {
    case 3:
        if (--g_playerCountScreen->head.delay <= 0) {
            g_playerCountScreen->head.list->transitionTimer--;
            if (g_playerCountScreen->head.list->transitionTimer + g_playerCountScreen->head.list->transitionDuration < 0) {
                g_playerCountScreen->head.list->transitionTimer = g_playerCountScreen->head.menu->list->transitionDuration;
            }
            g_playerCountScreen->head.delay = result;
        }
        break;
    case 4:
        MarkMenuEventHandled();
        if (g_playerCountScreen->head.target != -1) {
            SmXlate_SwitchScreen(g_playerCountScreen->head.target);
            return 0;
        }
        Menu_ReturnToPreviousScreen();
        break;
    default:
        return 0;
    }
    return 0;
}

int Frontend_ConfirmPlayerCount(void) {
    int i;
    PlayerCountSettingsSlotView *slot;

    MarkMenuEventHandled();
    g_playerCountScreen->head.target = 7;
    SmpSlider_SetTransitionMode(g_playerCountScreen->head.menu, 2);
    for (i = 0; i < g_playerCountScreen->count; i++) {
        slot = (PlayerCountSettingsSlotView *)&g_playerSettings[i];
        slot->active = 1;
        slot->index = i;
        if (g_profileSlotIndices[i * 400] < 0) {
            Player_InitializeProfileSlot(i);
        }
    }
    return 0;
}

s32 Frontend_CancelPlayerCount(void) {
    SettingsScreenState *state;

    MarkMenuEventHandled();
    state = g_playerCountScreen;
    state->head.target = -1;
    SmpSlider_SetTransitionMode(state->head.menu, 2);
    return 0;
}

s32 Frontend_IncreasePlayerCount(void *a0, void *a1, void *a2, s32 press) {
    SettingsScreenState *object;

    if (press != 1) {
        return 0;
    }
    MarkMenuEventHandled();
    if (Control_IsControllerConnected(g_playerCountScreen->count) == press) {
        object = g_playerCountScreen;
        if (object->count < Control_CountConnectedControllers()) {
            g_playerCountScreen->count++;
        }
    }
    XStdio_FormatBuffer(g_playerCountScreen->text, s_playerCountFormat, g_playerCountScreen->count);
    SoundElement_PlayFlatSound(3713);
    return 0;
}

s32 Frontend_DecreasePlayerCount(void *first, void *second, void *third, s32 fourth) {
    s32 value;

    if (fourth != 1) {
        return 0;
    }
    MarkMenuEventHandled();
    value = g_playerCountScreen->count;
    if (value >= 2) {
        g_playerCountScreen->count = value - 1;
    }
    XStdio_FormatBuffer(g_playerCountScreen->text, s_playerCountFormat, g_playerCountScreen->count);
    SoundElement_PlayFlatSound(3713);
    return 0;
}

s32 Frontend_DispatchPlayerCountEvent(void *widget, s32 eventId, s32 eventData0, s32 eventData1, s32 eventData2) {
    PlayerCountEventHandler *entry;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;
    MenuActorInputView *actor;

    if (g_playerCountEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_playerCountEventHandlers;
        index = 0;
        do {
            if (g_playerCountEventIds[index].value == eventId) {
                actor = widget;
                actor_kind = actor->input;
                table_kind = g_playerCountEventActorKinds[index].value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*entry)(widget, eventId, eventData0, eventData1, eventData2);
                }
            }
            entry += 3;
            index++;
        } while (*entry != 0);
    }
    return 0;
}
