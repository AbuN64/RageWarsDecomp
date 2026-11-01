#include "COMMON/MENULISTSCREEN.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/CHEATCODE.H"
#include "TYPES.H"
#include "MENU/MENU_DISPATCHSETTINGSCOLUMNEVENT.H"

#if defined(VERSION_DE)
/* Dispatches event eventId through this file's 12-byte handler table, whose rows hold an event at g_settingsColumnEventIds, an actor kind at g_settingsColumnEventKinds and a handler at g_settingsColumnEventHandlers: the first row whose event equals eventId and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from N64Eng_DispatchNumericWidgetEvent. */

extern FieldRow g_settingsColumnEventIds[];
extern FieldRow g_settingsColumnEventKinds[];
extern MenuChoiceEventHandler g_settingsColumnEventHandlers;

s32 Menu_DispatchSettingsColumnEvent(void *eventObject, s32 eventId, s32 eventPayload, s32 eventValue, s32 eventExtra) {
    MenuChoiceEventHandler *entry;
    MenuActorInputView *actor;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;

    if (g_settingsColumnEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_settingsColumnEventHandlers;
        index = 0;
        do {
            if (g_settingsColumnEventIds[index].value == eventId) {
                actor = eventObject;
                actor_kind = actor->input;
                table_kind = g_settingsColumnEventKinds[index].value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*entry)(eventObject, eventId, eventPayload, eventValue, eventExtra);
                }
            }
            entry += 3;
            index++;
        } while (*entry != 0);
    }
    return 0;
}
#endif
