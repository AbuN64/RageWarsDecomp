#include "COMMON/NODERECAT1C.H"
#include "../../include/libultra/os/thread.h"

void __osDequeueThread(void **listHead, void *node) {
    void **link;
    void *current;

    link = listHead;
    current = *link;
    while (current != 0) {
        if (current != node) {
            link = (void **)current;
            current = *link;
        } else {
            *link = *(void **)current;
            return;
        }
    }
}
