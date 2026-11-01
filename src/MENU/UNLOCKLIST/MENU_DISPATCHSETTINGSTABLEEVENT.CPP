#include "include_asm.h"

#if defined(VERSION_EU_X)
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/ITEMRECAT20V1.H"
extern ResidentEventHandlerEntry g_scrollingChoiceEventIds[];

s32 Menu_DispatchSettingsTableEvent(MenuWidget *pThis, s32 event, s32 eventPayload, s32 eventValue, s32 eventExtra) {
    s32 i;
    for (i = 0; g_scrollingChoiceEventIds[i].handler != 0; i++) {
        if (g_scrollingChoiceEventIds[i].event == event &&
            (g_scrollingChoiceEventIds[i].actorKind == pThis->resource || g_scrollingChoiceEventIds[i].actorKind == 30000)) {
            return g_scrollingChoiceEventIds[i].handler(pThis, event, eventPayload, eventValue, eventExtra);
        }
    }
    return 0;
}
#endif
