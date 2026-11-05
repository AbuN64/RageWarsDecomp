#ifndef COMMON_OS_TIMER_NODES_H
#define COMMON_OS_TIMER_NODES_H
#include "types.h"
#include "Common/os_timer_interrupt_internals.h"
struct OsTimerNode;
typedef struct OsTimerNode OsTimerNode;

struct TimerInterruptNode;

struct OsTimerNode;
struct OsTimerNode {
    s32 next;
    s32 prev;
    u64 interval;
    u64 value;
    void *mq;
    void *msg;
};

extern void __osTimerServicesInit(void);



struct ThreadNode;
struct ThreadNode {
    struct ThreadNode *next;
    s32 priority;
    struct ThreadNode **queue;
    s32 tlnext;
    u16 state;
};

struct ThreadNode;
typedef struct ThreadNode ThreadNode;

struct TimerInterruptNode;
typedef struct TimerInterruptNode TimerInterruptNode;
#endif
