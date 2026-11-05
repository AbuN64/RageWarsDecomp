#ifndef FRONTEND_CTRIALCATALOGUE_SHOWTRIALOPTIONCHILDREN_H
#define FRONTEND_CTRIALCATALOGUE_SHOWTRIALOPTIONCHILDREN_H
#include "Common/resultsoptionsscreen.h"

extern s32 CTrialCatalogue_DispatchCatalogueEvent(void *eventObject, s32 eventId, s32 eventPayload, s32 eventValue, s32 eventExtra);
extern void CTrialCatalogue_ShowTrialOptionChildren(void);
s32 CTrialCatalogue_CloseTrialOptionsScreen(void);
s32 CTrialCatalogue_ConfirmTrialStage(void);
s32 CTrialCatalogue_ExitTrialCatalogue(void);
s32 CTrialCatalogue_HandleTrialOptionRelease(void *first, void *second, u32 event, s32 value);
s32 CTrialCatalogue_SelectNeighborLeft(void *parent, s32 eventId, s32 eventPayload, s32 event);
s32 CTrialCatalogue_SelectNeighborBelow(void *parent, s32 eventId, s32 eventPayload, s32 event);
s32 CTrialCatalogue_SelectNeighborAbove(void *parent, s32 eventId, s32 eventPayload, s32 event);
s32 CTrialCatalogue_SelectNeighborRight(void *parent, s32 eventId, s32 eventPayload, s32 event);
#endif
