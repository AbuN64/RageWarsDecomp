#ifndef COMMON_OS_TIMER_INTERRUPT_INTERNALS_H
#define COMMON_OS_TIMER_INTERRUPT_INTERNALS_H
/* __osTimerInterrupt, drafted from ultralib src/os/timerintr.c (_FINALROM: no profiler). */
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"




extern void __osSetTimerIntr(u64 tim);
extern u64 __osInsertTimer(OSTimer *t);
#endif
