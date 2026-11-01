#ifndef FRONTEND_FRONTEND_ACTIVATEMATCHOPTIONACTION_H
#define FRONTEND_FRONTEND_ACTIVATEMATCHOPTIONACTION_H
#include "COMMON/MENU_OPTIONS_AND_RESULTS.H"
#include "OPTIONS.H"
extern void Frontend_SyncMatchJoinSlots(s32);
extern void Frontend_LoadMatchOptionWidgets(void);
extern void Frontend_StoreMatchOptionWidgets(void);
extern s32 Frontend_DispatchMatchOptionsEvent(void *element, s32 event, s32 source, s32 parameter, s32 value);
#endif
