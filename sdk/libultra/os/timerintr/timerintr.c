
/* __osInsertTimer, drafted from ultralib src/os/timerintr.c. */
#include "TYPES.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>




extern OSTimer *g_timerListSentinel;

u64 __osInsertTimer(OSTimer *t)
{
    OSTimer *timep;
    u64 tim;
    u32 savedMask = __osDisableInt();

    timep = g_timerListSentinel->next;
    tim = t->value;
    for (; timep != g_timerListSentinel && tim > timep->value; timep = timep->next) {
        tim -= timep->value;
    }

    t->value = tim;

    if (timep != g_timerListSentinel) {
        timep->value -= tim;
    }

    t->next = timep;
    t->prev = timep->prev;
    timep->prev->next = t;
    timep->prev = t;
    __osRestoreInt(savedMask);
    return tim;
}
