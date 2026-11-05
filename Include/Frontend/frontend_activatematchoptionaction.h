#ifndef FRONTEND_FRONTEND_ACTIVATEMATCHOPTIONACTION_H
#define FRONTEND_FRONTEND_ACTIVATEMATCHOPTIONACTION_H
#include "Common/menu_options_and_results.h"
#include "options.h"
extern void Frontend_SyncMatchJoinSlots(s32);
extern void Frontend_LoadMatchOptionWidgets(void);
extern void Frontend_StoreMatchOptionWidgets(void);
extern s32 Frontend_DispatchMatchOptionsEvent(void *element, s32 event, s32 source, s32 parameter, s32 value);
s32 Frontend_ActivateMatchOptionAction(void);
s32 Frontend_DestroyMatchOptions(void);
s32 Frontend_ExitMatchOptions(void);
s32 Frontend_RefreshMatchSlotsOnZeroEvent(void *first, void *second, void *third, s32 fourth);
s32 Frontend_RefreshMatchSlotsOnZeroEventAlt(void *first, void *second, void *third, s32 fourth);
s32 Frontend_ResetMatchOptionOnEvent(s32 element, s32 eventId, u32 eventData, s32 eventValue);
s32 Frontend_ReturnMatchOptionsEventZero(void);
#endif
