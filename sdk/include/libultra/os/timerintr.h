#ifndef LIBULTRA_OS_TIMERINTR_H
#define LIBULTRA_OS_TIMERINTR_H
#include "TYPES.H"
struct TimerInterruptNode {
    void *next;
    void *prev;
    u64 interval;
    u64 value;
    s32 messageQueue;
    s32 message;
};
#endif
