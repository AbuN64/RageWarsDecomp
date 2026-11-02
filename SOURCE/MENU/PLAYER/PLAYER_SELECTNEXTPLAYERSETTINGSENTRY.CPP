#include "COMMON/MENULISTSCREEN.H"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/MENU_TEXT.H"
#include "TYPES.H"
extern struct MenuStepState *g_playerSettingsScreen;
#include "MENU/PLAYER_INITPLAYERSETTINGSSCREEN.H"
#include "MENU/PLAYER_SELECTNEXTPLAYERSETTINGSENTRY.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"

/* Calls MarkMenuEventHandled, then sets the word at offset 0x20 of the object g_playerSettingsScreen points to to -1 and
   calls SmpSlider_SetTransitionMode on the object's first word with 2, returning zero. */




extern void MarkMenuEventHandled();

extern void SmpSlider_SetTransitionMode(struct SliderTransitionView *object, s32 mode);


                                 /* extern */
void MarkMenuEventHandled();

                                  /* extern */
s32 XStdio_FormatBuffer(void *, s32, ...);

                  /* extern */

                               /* extern */

                               /* extern */
#if defined(VERSION_EU) || defined(VERSION_EU_X)
extern s32 g_playerSettingsSlotNumberTranslations[];
#else
#endif

/* Native resident constant storage; absolute access symbols retain their addresses. */
#if defined(VERSION_US)

#elif defined(VERSION_US_REV1)

#elif defined(VERSION_DE)

#endif

/* Dispatches event eventId through this file's 12-byte handler table, whose rows hold an event at g_playerSettingsEventIds, an actor kind at g_playerSettingsEventActorKinds and a handler at g_playerSettingsEventHandlers: the first row whose event equals eventId and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from N64Eng_DispatchNumericWidgetEvent. */

typedef s32 (*PlayerSettingsEventHandler)(void *, s32, s32, s32, s32);



extern PlayerSettingsEventHandler g_playerSettingsEventHandlers;

s32 Player_CancelPlayerSettingsEntry(void) {
    struct MenuStepState *state;

    MarkMenuEventHandled();
    state = g_playerSettingsScreen;
    state->value = -1;
    SmpSlider_SetTransitionMode(state->menu, 2);
    return 0;
}

s32 Player_SelectNextPlayerSettingsEntry(s32 unused0, s32 unused1, s32 unused2, s32 buttonState) {
    s32 nextItem;

    MarkMenuEventHandled();
    if (buttonState == 1) {
        Player_StorePlayerSettingsEntry(g_playerSettingsScreen->item);
        nextItem = g_playerSettingsScreen->item + 1;
        g_playerSettingsScreen->item = nextItem;
        if (nextItem >= 4) {
            g_playerSettingsScreen->item = 0;
        }
        Player_SelectPlayerSettingsEntry(g_playerSettingsScreen->item);
        XStdio_FormatBuffer(g_playerSettingsScreen->text, RW_LOCALIZED_TEXT(g_playerSettingsSlotNumberFormat, g_playerSettingsSlotNumberTranslations, g_playerSettingsSlotNumberTranslations, g_languageIndex), g_playerSettingsScreen->item + 1);
        g_playerSettingsScreen->label->text = (void *) (g_playerSettingsScreen->text);
        SoundElement_PlayFlatSound(3713);
        return 0;
    }
    return 0;
}

s32 Player_SelectPreviousPlayerSettingsEntry(s32 unused0, s32 unused1, s32 unused2, s32 buttonState) {
    s32 previousItem;

    MarkMenuEventHandled();
    if (buttonState == 1) {
        Player_StorePlayerSettingsEntry(g_playerSettingsScreen->item);
        previousItem = g_playerSettingsScreen->item - 1;
        g_playerSettingsScreen->item = previousItem;
        if (previousItem < 0) {
            g_playerSettingsScreen->item = 3;
        }
        Player_SelectPlayerSettingsEntry(g_playerSettingsScreen->item);
        XStdio_FormatBuffer(g_playerSettingsScreen->text, RW_LOCALIZED_TEXT(g_playerSettingsSlotNumberFormat, g_playerSettingsSlotNumberTranslations, g_playerSettingsSlotNumberTranslations, g_languageIndex), g_playerSettingsScreen->item + 1);
        g_playerSettingsScreen->label->text = (void *) (g_playerSettingsScreen->text);
        SoundElement_PlayFlatSound(3713);
        return 0;
    }
    return 0;
}

s32 Player_DispatchPlayerSettingsEvent(void *eventTarget, s32 eventId, s32 eventCode, s32 eventValue, s32 repeatCount) {
    PlayerSettingsEventHandler *entry;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;
    MenuActorInputView *actor;

    if (g_playerSettingsEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_playerSettingsEventHandlers;
        index = 0;
        do {
            if (g_playerSettingsEventIds[index].value == eventId) {
                actor = eventTarget;
                actor_kind = actor->input;
                table_kind = g_playerSettingsEventActorKinds[index].value;
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
