#include "TYPES.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/OSTHREAD_S.H"

extern void *__osRunningThread;




/** Return field 0x4 of thread, falling back to a global record when thread is null. */
OSPri osGetThreadPri(OSThread *thread) {
    OSThread *p = thread;
    if (p == 0) {
        p = __osRunningThread;
    }
    return p->priority;
}
