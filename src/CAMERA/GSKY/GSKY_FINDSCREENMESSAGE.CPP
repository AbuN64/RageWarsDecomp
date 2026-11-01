#include "COMMON/VIEWFLAGS.H"
#include "COMMON/GAMEPLAY_TRANSITION.H"

extern void *g_transientPlayerList;




void *Gsky_FindScreenMessage(int messageId) {
    Shared_ActorView *node = g_transientPlayerList;
    if (node != 0) {
        do {
            if ((s32)node->message == messageId) {
                return node;
            }
            node = node->next;
        } while (node != 0);
    }
    return 0;
}
