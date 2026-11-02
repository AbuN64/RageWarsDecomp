#include "include_asm.h"

#if defined(VERSION_US)
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/MULTIPLAYEROPTIONS.H"
extern ResidentEventHandlerEntry g_residentEventEntries[];

s32 Frontend_DispatchResidentActorTableEvent(ActorDefinitionHeader *actor, s32 event, s32 eventArg2, s32 eventArg3, s32 eventArg4) {
    s32 index;
    index = 0;
    if (g_residentEventEntries[index].handler != 0) {
        do {
            if (g_residentEventEntries[index].event == event) {
                if (g_residentEventEntries[index].actorKind == actor->character || g_residentEventEntries[index].actorKind == 30000) {
                    return g_residentEventEntries[index].handler(actor, event, eventArg2, eventArg3, eventArg4);
                }
            }
            index++;
        } while (g_residentEventEntries[index].handler != 0);
    }
    return 0;
}
#endif

