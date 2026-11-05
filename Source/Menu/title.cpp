#include "Menu/menu_advancefademeter.h"
#include "Common/menuselectionmessage.h"
#include <platform_sdk.h>
#include "types.h"
#include "Ui/X_files/x_plus.h"
#include "include_asm.h"
#include "Common/screen.h"
#include "Data/g_titlebuttonscreen.h"
#include "Menu/externs.h"
#include "Menu/Title/menu_updatetitlebuttonscreen_symbols.h"
#include "Common/resident_event_handler.h"
#if ((defined(VERSION_EU)))
#include "Common/multiplayeroptions.h"
#endif
#if ((defined(VERSION_EU)))
#include "Common/shared_menureply.h"
#endif
#if ((defined(VERSION_EU)))
#include "Common/menu_screen_elements.h"
#endif
#if ((defined(VERSION_EU)))
#include "Menu/menu_advancefademeter.h"
#endif
#include "Common/sharedplayer.h"
#include "Common/aiprofile.h"
#include "Common/menu_initializeoptionsscene.h"
#include "Common/cheatcode.h"
#include "Menu/menu_dispatchtitlebuttoncolumnevent.h"
#include "Common/runtime_declarations.h"
#include "Menu/Title/menu_dispatchtitlebuttoncolumnevent_symbols.h"
#include "Common/frontend_clock_state.h"
#include "Common/menulistscreen.h"
#include "Frontend/frontend.h"

/* Advances a menu selection on its countdown and dispatches the exit action. */




#if defined(VERSION_DE)
enum { TITLE_BUTTON_CHOICE_RESET_PLAYED_LEVELS = 970, TITLE_BUTTON_CHOICE_CLEAR_PENDING_SCREEN = 971 };
#elif defined(VERSION_EU_X)
enum { TITLE_BUTTON_CHOICE_RESET_PLAYED_LEVELS = 980, TITLE_BUTTON_CHOICE_CLEAR_PENDING_SCREEN = 981 };
#else
enum { TITLE_BUTTON_CHOICE_RESET_PLAYED_LEVELS = 976, TITLE_BUTTON_CHOICE_CLEAR_PENDING_SCREEN = 977 };
#endif

/* Calls MarkMenuEventHandled; when Menu_GetFocusedElementId reports 0x3D0 it sets a field of the menu block
   g_titleButtonScreen points to to 7 and clears five bytes at g_profileModePlayedLevels[0] through XPlus_FillMemory, for 0x3D1 it
   sets that word to -1; then it calls SmpSlider_SetTransitionMode on the block's first word with 2. Returns
   zero. */
 /* const */
s32 Menu_UpdateTitleButtonScreen(void) {
    s32 nextScreen;
    s32 transitionModeResult;
    s32 transitionCountdown;
    MenuWidget *listSelection;
    MenuWidget *listCursor;
    transitionModeResult = SmpSlider_GetTransitionMode(g_titleButtonScreen->slider);
    switch (transitionModeResult) {
    case 3:
        transitionCountdown = g_titleButtonScreen->transitionTimer - 1;
        g_titleButtonScreen->transitionTimer = transitionCountdown;
        if (transitionCountdown <= 0) {
            listCursor = g_titleButtonScreen->transitionCell;
            listCursor->y = (u16) (listCursor->y - 1);
            listSelection = g_titleButtonScreen->transitionCell;
            if (((s16) listSelection->y + listSelection->height) < 0) {
                listSelection->y = (u16) g_titleButtonScreen->slider->transitionCell->height;
            }
            g_titleButtonScreen->transitionTimer = transitionModeResult;
        }
        return 0;
    case 4:
        MarkMenuEventHandled();
        nextScreen = g_titleButtonScreen->nextScreen;
        if (nextScreen == -1) {
            Menu_ReturnToPreviousScreen();
            return 0;
        }
        SmXlate_SwitchScreen(nextScreen);
        return 0;
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
        XPlus_FillMemory(g_profileModePlayedLevels[0], 0, 5);
        break;
    }
    SmpSlider_SetTransitionMode(g_titleButtonScreen->slider, 2);
    return 0;
}

#if defined(VERSION_EU)

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

#if defined(VERSION_EU_X)
/* Dispatches event eventId through this file's 12-byte handler table, whose rows hold an event at g_titleButtonEventTable, an actor kind at g_titleButtonEventActorKinds and a handler at g_titleButtonEventHandlers: the first row whose event equals eventId and whose kind equals the actor's input kind, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. */
s32 Menu_DispatchTitleButtonOffsetEvent(void *widget, s32 eventId, s32 eventData0, s32 eventData1, s32 eventData2) {
    ResidentEventHandlerEntry *row;
    s32 kind;

    if (g_titleButtonEventHandlers != 0) {
        row = g_titleButtonEventTable;
        do {
            if (row->event == eventId) {
                kind = row->actorKind;
                if (kind == ((struct MenuWidget *)widget)->resource || kind == ANY_ACTOR_KIND) {
                    return row->handler(widget, eventId, eventData0, eventData1, eventData2);
                }
            }
            row++;
        } while (row->handler != 0);
    }
    return 0;
}
#endif

#if defined(VERSION_DE)
/* Dispatches event eventId through this file's 12-byte handler table, whose rows hold an event at g_titleButtonEventTable, an actor kind at g_titleButtonEventActorKinds and a handler at g_titleButtonEventHandlers: the first row whose event equals eventId and whose kind equals the actor's input kind, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. */


s32 Menu_DispatchTitleButtonColumnEvent(void *widget, s32 eventId, s32 eventData0, s32 eventData1, s32 eventData2) {
    TitleButtonColumnEventHandler *entry;
    MenuWidget *actor;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;
    s32 actorKind;
    s32 tableKind;

    if (g_titleButtonColumnEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_titleButtonColumnEventHandlers;
        index = 0;
        do {
            if (g_titleButtonColumnEventIds[index].value == eventId) {
                actor = widget;
                actor_kind = actor->resource;
                table_kind = g_titleButtonColumnEventActorKinds[index].value;
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

#endif

#if defined(VERSION_US) || defined(VERSION_US_REV1)
/* Dispatches event eventId through this file's 12-byte handler table, whose rows hold an event at g_titleButtonEventTable, an actor kind at g_titleButtonEventActorKinds and a handler at g_titleButtonEventHandlers: the first row whose event equals eventId and whose kind equals the actor's input kind, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. */
typedef s32 (*TitleButtonColumnEventHandler)(void *, s32, s32, s32, s32);


extern FieldRow g_titleButtonEventActorKinds[];

extern TitleButtonColumnEventHandler g_titleButtonEventHandlers;


s32 Menu_DispatchTitleButtonEvent(void *widget, s32 eventId, s32 eventData0, s32 eventData1, s32 eventData2) {
    TitleButtonColumnEventHandler *entry;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;
    MenuWidget *actor;

    if (g_titleButtonEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_titleButtonEventHandlers;
        index = 0;
        do {
            if (g_titleButtonEventTable[index].event == eventId) {
                actor = widget;
                actor_kind = actor->resource;
                table_kind = g_titleButtonEventActorKinds[index].value;
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
#endif
