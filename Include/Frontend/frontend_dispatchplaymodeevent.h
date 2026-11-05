#ifndef FRONTEND_FRONTEND_DISPATCHPLAYMODEEVENT_H
#define FRONTEND_FRONTEND_DISPATCHPLAYMODEEVENT_H
#include "Common/menu_options_and_results.h"
extern s32 Frontend_DispatchPlayModeEvent(void *actor, s32 event, s32 eventValue, s32 eventData, s32 eventContext);
s32 Frontend_ConsumePlayModeEvent(void);
s32 Frontend_HandlePlayModeShortcut(void *first, void *second, u32 event, s32 value);
#endif
