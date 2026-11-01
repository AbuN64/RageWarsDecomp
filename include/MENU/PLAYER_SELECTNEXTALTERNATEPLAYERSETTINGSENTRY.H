#ifndef MENU_PLAYER_SELECTNEXTALTERNATEPLAYERSETTINGSENTRY_H
#define MENU_PLAYER_SELECTNEXTALTERNATEPLAYERSETTINGSENTRY_H
#include "COMMON/MENULISTSCREEN.H"
extern s32 Player_DispatchAlternatePlayerSettingsEvent(void *actor, s32 event, s32 eventValue, s32 eventData, s32 eventContext);
/* Exact localized menu callbacks, bound to current native/consumer receipts. */
extern s32 Player_SelectNextAlternatePlayerSettingsEntry(s32 unusedActor, s32 unusedEvent, s32 unusedValue, s32 playerIndex);
extern s32 Player_SelectPreviousAlternatePlayerSettingsEntry(s32 unusedActor, s32 unusedEvent, s32 unusedValue, s32 playerIndex);
#endif
