#include "COMMON/MENUSELECTIONMESSAGE.H"
#include "COMMON/ITEMRECAT20V1.H"
#include <ultra64.h>
#include "TYPES.H"
#include "UI/X_FILES/X_PLUS.H"
#include "include_asm.h"

/* 804379C8_2.CPP */
extern ChoiceMenuState *g_titleButtonScreen;

/* Advances a menu selection on its countdown and dispatches the exit action. */
void SmXlate_SwitchScreen(s32);

 /* extern */
void MarkMenuEventHandled();

 /* extern */
void Menu_ReturnToPreviousScreen(void);

 /* extern */
s32 SmpSlider_GetTransitionMode(s32 *record);

 /* extern */

/* Calls MarkMenuEventHandled, then sets the word at offset 0x10 of the object g_titleButtonScreen points to to -1 and
   calls SmpSlider_SetTransitionMode on the object's first word with 2, returning zero. */

extern void SmpSlider_SetTransitionMode(struct SliderTransitionView *object, s32 mode);

/* Calls MarkMenuEventHandled; when Menu_GetFocusedElementId reports 0x3D0 it sets the word at 0x10 of the menu block
   g_titleButtonScreen points to to 7 and clears five bytes at g_profileModeOnePlayedLevels through XPlus_FillMemory, for 0x3D1 it
   sets that word to -1; then it calls SmpSlider_SetTransitionMode on the block's first word with 2. Returns
   zero. */

extern char g_profileModeOnePlayedLevels[];

extern s32 Menu_GetFocusedElementId();

#if defined(VERSION_DE)
enum { TITLE_BUTTON_CHOICE_RESET_PLAYED_LEVELS = 970, TITLE_BUTTON_CHOICE_CLEAR_PENDING_SCREEN = 971 };
#elif defined(VERSION_EU_X)
enum { TITLE_BUTTON_CHOICE_RESET_PLAYED_LEVELS = 980, TITLE_BUTTON_CHOICE_CLEAR_PENDING_SCREEN = 981 };
#else
enum { TITLE_BUTTON_CHOICE_RESET_PLAYED_LEVELS = 976, TITLE_BUTTON_CHOICE_CLEAR_PENDING_SCREEN = 977 };
#endif

 /* const */
s32 Menu_UpdateTitleButtonScreen(void) {
    s32 nextScreen;
    s32 transitionModeResult;
    s32 transitionCountdown;
    ChoiceMenuCellView *listSelection;
    ChoiceMenuCellView *listCursor;
    transitionModeResult = SmpSlider_GetTransitionMode(g_titleButtonScreen->slider);
    switch (transitionModeResult) { /* irregular */
    case 3:
        transitionCountdown = g_titleButtonScreen->transitionTimer - 1;
        g_titleButtonScreen->transitionTimer = transitionCountdown;
        if (transitionCountdown <= 0) {
            listCursor = g_titleButtonScreen->transitionCell;
            listCursor->transitionTimer = (u16) (listCursor->transitionTimer - 1);
            listSelection = g_titleButtonScreen->transitionCell;
            if (((s16) listSelection->transitionTimer + listSelection->transitionDuration) < 0) {
                listSelection->transitionTimer = (u16) g_titleButtonScreen->slider->transitionCell->transitionDuration;
            }
            g_titleButtonScreen->transitionTimer = transitionModeResult;
        }
block_10:
        return 0;
    case 4:
        MarkMenuEventHandled();
        nextScreen = g_titleButtonScreen->nextScreen;
        if (nextScreen == -1) {
            Menu_ReturnToPreviousScreen();
            return 0;
        }
        SmXlate_SwitchScreen(nextScreen);
        goto block_10;
    default:
        return 0;
    }
}

s32 Menu_CancelTitleButtonScreen(void) {
    ChoiceMenuState *state;

    MarkMenuEventHandled();
    state = g_titleButtonScreen;
    state->nextScreen = -1;
    SmpSlider_SetTransitionMode(state->slider, 2);
    return 0;
}

s32 Menu_HandleTitleButtonChoice(void) {
    s32 choice;

    MarkMenuEventHandled();
    choice = Menu_GetFocusedElementId();
    switch (choice) {
    case TITLE_BUTTON_CHOICE_CLEAR_PENDING_SCREEN:
        g_titleButtonScreen->nextScreen = -1;
        break;
    case TITLE_BUTTON_CHOICE_RESET_PLAYED_LEVELS:
        g_titleButtonScreen->nextScreen = 7;
        XPlus_FillMemory(g_profileModeOnePlayedLevels, 0, 5);
        break;
    }
    SmpSlider_SetTransitionMode(g_titleButtonScreen->slider, 2);
    return 0;
}

/* 804389B0_2.CPP */
#if defined(VERSION_EU)
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/MULTIPLAYEROPTIONS.H"
extern ResidentEventHandlerEntry g_titleButtonEventTable[];

s32 Menu_DispatchTitleButtonTableEvent(ActorDefinitionHeader *actor, s32 event, s32 eventData0, s32 eventData1, s32 eventData2) {
    s32 index;
    index = 0;
    if (g_titleButtonEventTable[index].handler != 0) {
        do {
            if (g_titleButtonEventTable[index].event == event) {
                if (g_titleButtonEventTable[index].actorKind == actor->character || g_titleButtonEventTable[index].actorKind == 30000) {
                    return g_titleButtonEventTable[index].handler(actor, event, eventData0, eventData1, eventData2);
                }
            }
            index++;
        } while (g_titleButtonEventTable[index].handler != 0);
    }
    return 0;
}
#endif
