#include "include_asm.h"

#if defined(VERSION_US)
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/MULTIPLAYEROPTIONS.H"
extern ResidentEventHandlerEntry g_pakProfileHandlerEvents[];

s32 Frontend_DispatchPakProfileEventUs(ActorDefinitionHeader *actor, s32 event, s32 eventPayload, s32 eventValue, s32 eventExtra) {
    s32 index;
    index = 0;
    if (g_pakProfileHandlerEvents[index].handler != 0) {
        do {
            if (g_pakProfileHandlerEvents[index].event == event) {
                if (g_pakProfileHandlerEvents[index].actorKind == actor->character || g_pakProfileHandlerEvents[index].actorKind == 30000) {
                    return g_pakProfileHandlerEvents[index].handler(actor, event, eventPayload, eventValue, eventExtra);
                }
            }
            index++;
        } while (g_pakProfileHandlerEvents[index].handler != 0);
    }
    return 0;
}
#endif

#if defined(VERSION_US)
char g_FrontendTrailingBytesBlock7[8] =
    "gHdrR\000\000";
#endif

