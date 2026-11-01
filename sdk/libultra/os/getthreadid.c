#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/OSTHREAD_S.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "../../include/libultra/os/getthreadid.h"

/** Return the global word at __osFaultedThread. */

int __osGetCurrFaultedThread(void) {
    return __osFaultedThread;
}

extern void *__osRunningThread;




/** Return offset 0x14 from the supplied object or the default global object. */
OSId osGetThreadId(OSThread *object) {
    ThreadIdentifierView *object_record;
    if (object == 0) {
        object = __osRunningThread;
    }
    object_record = object;
    return object_record->threadId;
}
