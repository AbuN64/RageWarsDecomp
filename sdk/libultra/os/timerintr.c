#include "COMMON/NODERECAT1C.H"
#include "../../include/libultra/os/timerintr.h"
#include "COMMON/OS_TIMER_INTERRUPT_INTERNALS.H"
#include "TYPES.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>

void __osTimerInterrupt(void)
{
    OSTimer *t;
    u32 count;
    u32 elapsed_cycles;
    u32 *counter;

    if (((OSTimer *)g_timerListSentinel)->next == g_timerListSentinel) {
        return;
    }
    counter = &g_timerLastProcessorCount;
    for (;;) {
        t = ((OSTimer *)g_timerListSentinel)->next;

        if (t == g_timerListSentinel) {
            __osSetCompare(0);
            g_timerLastProcessorCount = 0;
            break;
        }

        count = osGetCount();
        elapsed_cycles = count - *counter;
        *counter = count;

        if (elapsed_cycles < t->value) {
            t->value -= elapsed_cycles;
            __osSetTimerIntr(t->value);
            break;
        }

        t->prev->next = t->next;
        t->next->prev = t->prev;
        t->next = 0;
        t->prev = 0;

        if (t->mq != 0) {
            osSendMesg(t->mq, t->msg, 0);
        }

        if (t->interval != 0) {
            t->value = t->interval;
            __osInsertTimer(t);
        }
    }
}




void __osTimerServicesInit(void) {
    TimerInterruptNode *node = (TimerInterruptNode *)g_timerListSentinel;

    __osCurrentTime = 0;
    __osBaseCounter = 0;
    g_timerServiceCounter = 0;
    node->value = 0;
    node->interval = 0;
    node->prev = node;
    node->next = node;
    node->messageQueue = 0;
    node->message = 0;
}

/* Arms the CP0 timer interrupt: with interrupts disabled through __osDisableInt_Mutex, reads the Count
   register through osGetCount into g_timerLastProcessorCount, sets the Compare register through
   __osSetCompare to that count plus the requested interval, then restores interrupts. */

void __osSetTimerIntr(u64 interval) {
    u64 compare;
    u32 saved = __osDisableInt();

    g_timerLastProcessorCount = osGetCount();
    compare = g_timerLastProcessorCount + interval;
    __osSetCompare(compare);
    __osRestoreInt(saved);
}
