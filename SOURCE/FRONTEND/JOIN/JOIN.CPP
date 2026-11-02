#include "include_asm.h"

#if defined(VERSION_EU)
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/MULTIPLAYEROPTIONS.H"
extern ResidentEventHandlerEntry g_joinOptionsEventHandlers[];

s32 Join_DispatchEuJoinOptionsEvent(ActorDefinitionHeader *actor, s32 event, s32 eventData, s32 eventValue, s32 eventContext) {
    s32 index;
    index = 0;
    if (g_joinOptionsEventHandlers[index].handler != 0) {
        do {
            if (g_joinOptionsEventHandlers[index].event == event) {
                if (g_joinOptionsEventHandlers[index].actorKind == actor->character || g_joinOptionsEventHandlers[index].actorKind == 30000) {
                    return g_joinOptionsEventHandlers[index].handler(actor, event, eventData, eventValue, eventContext);
                }
            }
            index++;
        } while (g_joinOptionsEventHandlers[index].handler != 0);
    }
    return 0;
}
#endif
