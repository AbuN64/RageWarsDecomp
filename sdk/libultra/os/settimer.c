#include "COMMON/NODERECAT1C.H"
#include "TYPES.H"

/* 802C07B0.CPP */
/* 802C07B0.CPP */
int osSetTimer(OSTimer *node, OSTime initialDelay, OSTime repeatInterval, OSMesgQueue *messageQueue, OSMesg message) {
    u64 value;

    node->value = initialDelay;
    node->next = 0;
    node->prev = 0;
    node->interval = repeatInterval;
    if (initialDelay == 0) {
        node->value = repeatInterval;
    }
    node->mq = messageQueue;
    node->msg = message;
    value = __osInsertTimer(node);
    if (*(void **)g_timerListSentinel == node) {
        __osSetTimerIntr(value);
    }
    return 0;
}

/* 802C0840_2.CPP */

/* 802C0840.CPP */

/* 802C0840_12.CPP */

/* 802C0840_5.CPP */
