#ifndef FRONTEND_FRONTEND_HANDLETABOPTIONSSHORTCUT_H
#define FRONTEND_FRONTEND_HANDLETABOPTIONSSHORTCUT_H
#include "COMMON/MENU_OPTIONS_AND_RESULTS.H"
extern s32 Frontend_DispatchCompactOptionsEvent(void *eventTarget, s32 eventId, s32 eventCode, s32 eventValue, s32 repeatCount);
extern s32 Frontend_DispatchTabOptionsEvent(void *eventTarget, s32 eventId, s32 eventCode, s32 eventValue, s32 repeatCount);
s32 Frontend_ActivateCompactOptionsPage(void);
s32 Frontend_CloseCompactOptionsPage(void);
s32 Frontend_ConsumeTabOptionsEvent(void);
s32 Frontend_DestroyCompactOptionsPage(void);
s32 Frontend_DestroyTabOptionsPage(void);
s32 Frontend_HandleCompactOptionsShortcut(void);
s32 Frontend_HandleTabOptionsShortcut(void);
#endif
