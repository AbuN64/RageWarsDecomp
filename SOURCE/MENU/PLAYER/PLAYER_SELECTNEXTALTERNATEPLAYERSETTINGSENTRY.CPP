#include "include_asm.h"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "COMMON/MENULISTSCREEN.H"
#include "COMMON/MEASUREDRECAT0V1.H"
#include "COMMON/MEASURED.H"
#include "COMMON/MEASUREDRECAT14V4.H"
#include "COMMON/MEASUREDRECAT14V2.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/ARGB_COLOR.H"
#include <ultra64.h>
#include "COMMON/MENU_TEXT.H"
#include "COMMON/SCREEN.H"
#include "COMMON/SHARED_MENUREPLY.H"
#include "COMMON/SHARED_OPTIONSSCREEN.H"
#include "COMMON/MULTIPLAYEROPTIONS.H"
#include "COMMON/LOADOUT.H"
#include "COMMON/OWNERRECAT8V2.H"
#include "COMMON/GROUP.H"
#include "COMMON/OBJECT_INSTANCE_TRANSFORM_AND_RENDER_VIEWS.H"
#include "COMMON/MANAGER.H"
#include "COMMON/CARTRIDGEREADWORKER.H"
#include "COMMON/OBJRECAT4V6.H"
#include "COMMON/SOUNDVOICEPOOL.H"
#include "COMMON/LIGHTDATA.H"
#include "COMMON/GEOMETRY_BLEND_AND_INSTANCE_VIEWS.H"
#include "COMMON/MTX.H"
#include "COMMON/PARTICLE_ATTACHMENT_AND_OWNER_VIEWS.H"
#include "COMMON/COLORENTRY.H"
#include "COMMON/WORLDSORTENTRY.H"
#include "COMMON/RESULTS.H"
#include "COMMON/OBJRECAT26DD8.H"
#include "COMMON/INTEGERSTATE530.H"
#include "COMMON/OBJRECAT18V6.H"
#include "COMMON/ALBANK_S.H"
#include "COMMON/OBJRECAT18V1.H"
#include "COMMON/ALPARAM_S.H"
#include "COMMON/ALDELAY28.H"
#include "COMMON/OSPIHANDLE_S.H"
#include "COMMON/OSVISCALE.H"
#include "COMMON/CTX.H"
#include "COMMON/AUDIO_LOADDECODEDSAMPLES.H"
#include "COMMON/CHEATCODE.H"
#include "COMMON/ENTRYRECAT0V3.H"
#include "COMMON/NODERECAT2A8.H"
#include "COMMON/SLOTRECATCV1.H"
#include "COMMON/TEXTURE.H"
#include "COMMON/LABEL.H"
#include "COMMON/REQUESTRECAT10.H"
#include "COMMON/CHARACTERSELECTIONROOT.H"
#include "COMMON/NUMBERPADSCREEN.H"
#include "COMMON/MENU_INITIALIZEOPTIONSSCENE.H"
#include "COMMON/STATERECAT91.H"
#include "COMMON/RESULTSOPTIONSSCREEN.H"
#include "COMMON/SETTINGSRECAT24.H"
#include "COMMON/OBJECTRECAT28.H"
#include "COMMON/PLAYERRECAT64E.H"
#include "COMMON/OBJB.H"
#include "TYPES.H"
extern StyleNextState *g_alternatePlayerSettingsScreen;
#include "MENU/PLAYER_STOREALTERNATEPLAYERSETTINGSENTRY.H"
#include "MENU/PLAYER_SELECTNEXTALTERNATEPLAYERSETTINGSENTRY.H"
#include "SCENE/CACHE_FREEMEMORY.H"

/* Releases the object g_alternatePlayerSettingsScreen holds through Cache_FreeMemory, clears g_alternatePlayerSettingsScreen and returns zero. */



/* Calls MarkMenuEventHandled; when Menu_GetFocusedElementId reports 0x1C8, passes the word at offset 0x14 of the
   object g_alternatePlayerSettingsScreen points to to Player_StoreAlternatePlayerSettingsEntry, then passes -1 to Random_SetMenuChoiceResult if Menu_GetPreviousScreenOwner
   reports 0x16 for zero and 0xB otherwise, and calls Menu_ReturnToPreviousScreen. Returns zero. */





/* Calls MarkMenuEventHandled, then passes -1 to Random_SetMenuChoiceResult when Menu_GetPreviousScreenOwner reports 0x16 for zero
   and 0xB otherwise, then calls Menu_ReturnToPreviousScreen. Returns zero. */


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

/* Dispatches event eventId through this file's 12-byte handler table, whose rows hold an event at g_alternatePlayerSettingsEventIds, an actor kind at g_alternatePlayerSettingsEventActorKinds and a handler at g_alternatePlayerSettingsEventHandlers: the first row whose event equals eventId and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from N64Eng_DispatchNumericWidgetEvent. */

typedef s32 (*AlternatePlayerSettingsEventHandler)(void *, s32, s32, s32, s32);



extern AlternatePlayerSettingsEventHandler g_alternatePlayerSettingsEventHandlers;

s32 Player_FreeAlternatePlayerSettingsScreen(void) {
    Cache_FreeMemory(g_alternatePlayerSettingsScreen);
    g_alternatePlayerSettingsScreen = 0;
    return 0;
}

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 Player_EmptyAlternateSettingsEntryHook(void) {
    return 0;
}

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 Player_EmptyAlternateSettingsExitHook(void) {
    return 0;
}

s32 Player_ConfirmAlternatePlayerSettingsEntry(void) {
    MarkMenuEventHandled();
#if defined(VERSION_DE)
    if (Menu_GetFocusedElementId() == 452) {
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    if (Menu_GetFocusedElementId() == 456) {
#elif defined(VERSION_EU_X)
    if (Menu_GetFocusedElementId() == 460) {
#endif
        Player_StoreAlternatePlayerSettingsEntry(g_alternatePlayerSettingsScreen->item);
        Random_SetMenuChoiceResult(Menu_GetPreviousScreenOwner(0) == 22 ? -1 : 11);
        Menu_ReturnToPreviousScreen();
    }
    return 0;
}

s32 Player_CancelAlternatePlayerSettingsEntry(void) {
    MarkMenuEventHandled();
    Random_SetMenuChoiceResult(Menu_GetPreviousScreenOwner(0) == 22 ? -1 : 11);
    Menu_ReturnToPreviousScreen();
    return 0;
}

s32 Player_SelectNextAlternatePlayerSettingsEntry(s32 unused0, s32 unused1, s32 unused2, s32 selectionPressed) {
    s32 selectedEntry;

    MarkMenuEventHandled();
    if (selectionPressed == 1) {
        Player_StoreAlternatePlayerSettingsEntry(g_alternatePlayerSettingsScreen->item);
        selectedEntry = g_alternatePlayerSettingsScreen->item + 1;
        g_alternatePlayerSettingsScreen->item = selectedEntry;
        if (selectedEntry >= 4) {
            g_alternatePlayerSettingsScreen->item = 0;
        }
        Player_SelectAlternatePlayerSettingsEntry(g_alternatePlayerSettingsScreen->item);
        XStdio_FormatBuffer(g_alternatePlayerSettingsScreen->text, RW_LOCALIZED_TEXT(g_playerSettingsSlotNumberFormat, g_playerSettingsSlotNumberTranslations, g_playerSettingsSlotNumberTranslations, g_languageIndex), g_alternatePlayerSettingsScreen->item + 1);
        g_alternatePlayerSettingsScreen->label->text = (void *) (g_alternatePlayerSettingsScreen->text);
        return 0;
    }
    return 0;
}

s32 Player_SelectPreviousAlternatePlayerSettingsEntry(s32 unused0, s32 unused1, s32 unused2, s32 selectionPressed) {
    s32 selectedEntry;

    MarkMenuEventHandled();
    if (selectionPressed == 1) {
        Player_StoreAlternatePlayerSettingsEntry(g_alternatePlayerSettingsScreen->item);
        selectedEntry = g_alternatePlayerSettingsScreen->item - 1;
        g_alternatePlayerSettingsScreen->item = selectedEntry;
        if (selectedEntry < 0) {
            g_alternatePlayerSettingsScreen->item = 3;
        }
        Player_SelectAlternatePlayerSettingsEntry(g_alternatePlayerSettingsScreen->item);
        XStdio_FormatBuffer(g_alternatePlayerSettingsScreen->text, RW_LOCALIZED_TEXT(g_playerSettingsSlotNumberFormat, g_playerSettingsSlotNumberTranslations, g_playerSettingsSlotNumberTranslations, g_languageIndex), g_alternatePlayerSettingsScreen->item + 1);
        g_alternatePlayerSettingsScreen->label->text = (void *) (g_alternatePlayerSettingsScreen->text);
        return 0;
    }
    return 0;
}

s32 Player_DispatchAlternatePlayerSettingsEvent(void *eventObject, s32 eventId, s32 eventPayload, s32 eventValue, s32 eventExtra) {
    AlternatePlayerSettingsEventHandler *entry;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;
    MenuActorInputView *actor;

    if (g_alternatePlayerSettingsEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_alternatePlayerSettingsEventHandlers;
        index = 0;
        do {
            if (g_alternatePlayerSettingsEventIds[index].value == eventId) {
                actor = eventObject;
                actor_kind = actor->input;
                table_kind = g_alternatePlayerSettingsEventActorKinds[index].value;
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

