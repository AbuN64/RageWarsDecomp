#ifndef MENU_PLAYER_SELECTNEXTPLAYERSETTINGSENTRY_H
#define MENU_PLAYER_SELECTNEXTPLAYERSETTINGSENTRY_H
#include "COMMON/MENULISTSCREEN.H"
extern s32 Player_DispatchPlayerSettingsEvent(void *eventObject, s32 eventId, s32 eventPayload, s32 eventValue, s32 eventExtra);
extern s32 Player_SelectNextPlayerSettingsEntry(s32 unused0, s32 unused1, s32 unused2, s32 buttonState);
extern s32 Player_SelectPreviousPlayerSettingsEntry(s32 unused0, s32 unused1, s32 unused2, s32 buttonState);
#endif
