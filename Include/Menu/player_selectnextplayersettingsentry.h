#ifndef MENU_PLAYER_SELECTNEXTPLAYERSETTINGSENTRY_H
#define MENU_PLAYER_SELECTNEXTPLAYERSETTINGSENTRY_H
#include "Common/menulistscreen.h"
extern s32 Player_DispatchPlayerSettingsEvent(void *eventObject, s32 eventId, s32 eventPayload, s32 eventValue, s32 eventExtra);
extern s32 Player_SelectNextPlayerSettingsEntry(s32 element, s32 eventId, s32 eventPayload, s32 buttonState);
extern s32 Player_SelectPreviousPlayerSettingsEntry(s32 element, s32 eventId, s32 eventPayload, s32 buttonState);
#endif
