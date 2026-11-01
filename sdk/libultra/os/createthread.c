#include "include_asm.h"
#include "COMMON/OSTHREAD_S.H"
#include "TYPES.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>

/* 802BFD80_5.CPP */

/* createthread.c */
/* osCreateThread, drafted from ultralib src/os/createthread.c (2.0I-J, no thread profile). */

extern OSThread *__osActiveQueue;
extern void System_CleanupThreadEntry(void);

void osCreateThread(OSThread *t, s32 id, void (*entry)(void *), void *arg, void *sp, s32 p)
{
    register u32 saveMask;
    u32 mask;
    OSThread **active;

    t->id = id;
    t->priority = p;
    t->next = 0;
    t->queue = 0;
    t->context.pc = (u32)entry;
    t->context.a0 = (s64)(s32)arg;
    t->context.sp = (s64)(s32)sp - 16;
    t->context.ra = (s64)(s32)System_CleanupThreadEntry;
    mask = 0x3FFF01;
    t->context.sr = (mask & 0xFF01) | 0x04000002;
    t->context.rcp = (mask & 0x3F0000) >> 16;
    t->context.fpcsr = 0x01000800;
    t->fp = 0;
    t->state = 1;
    t->flags = 0;

    saveMask = __osDisableInt();
    active = &__osActiveQueue;
    t->tlnext = *active;
    *active = t;
    __osRestoreInt(saveMask);
}

