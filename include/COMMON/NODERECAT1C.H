#ifndef COMMON_NODERECAT1C_H
#define COMMON_NODERECAT1C_H
#include "TYPES.H"
#include "COMMON/OS_TIMER_INTERRUPT_INTERNALS.H"
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
