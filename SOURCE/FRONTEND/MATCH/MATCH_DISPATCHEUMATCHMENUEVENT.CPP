#include "include_asm.h"

#if defined(VERSION_EU)
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/ITEMRECAT20V1.H"
extern ResidentEventHandlerEntry g_matchMenuEventIds[];

s32 Match_DispatchEuMatchMenuEvent(MenuWidget *pThis, s32 event, s32 eventPayload, s32 eventValue, s32 eventExtra) {
    s32 i;
    for (i = 0; g_matchMenuEventIds[i].handler != 0; i++) {
        if (g_matchMenuEventIds[i].event == event &&
            (g_matchMenuEventIds[i].actorKind == pThis->resource || g_matchMenuEventIds[i].actorKind == 30000)) {
            return g_matchMenuEventIds[i].handler(pThis, event, eventPayload, eventValue, eventExtra);
        }
    }
    return 0;
}
#endif

