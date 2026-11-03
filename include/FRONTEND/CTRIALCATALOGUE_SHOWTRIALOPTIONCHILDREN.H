#ifndef FRONTEND_CTRIALCATALOGUE_SHOWTRIALOPTIONCHILDREN_H
#define FRONTEND_CTRIALCATALOGUE_SHOWTRIALOPTIONCHILDREN_H
#include "COMMON/RESULTSOPTIONSSCREEN.H"

extern s32 CTrialCatalogue_DispatchCatalogueEvent(void *eventObject, s32 eventId, s32 eventPayload, s32 eventValue, s32 eventExtra);
extern void CTrialCatalogue_ShowTrialOptionChildren(void);
s32 CTrialCatalogue_CloseTrialOptionsScreen(void);
s32 CTrialCatalogue_ConfirmTrialStage(void);
s32 CTrialCatalogue_ExitTrialCatalogue(void);
s32 CTrialCatalogue_HandleTrialOptionRelease(void *first, void *second, u32 event, s32 value);
s32 CTrialCatalogue_SelectNeighborOne(void *parent, s32 unused1, s32 unused2, s32 event);
s32 CTrialCatalogue_SelectNeighborThree(void *parent, s32 unused1, s32 unused2, s32 event);
s32 CTrialCatalogue_SelectNeighborTwo(void *parent, s32 unused1, s32 unused2, s32 event);
s32 CTrialCatalogue_SelectNeighborZero(void *parent, s32 unused1, s32 unused2, s32 event);
#endif
