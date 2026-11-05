#include "types.h"
#include "Common/osthread_s.h"
#include "Common/runtime_declarations.h"
#include "../../include/libultra/os/getthreadid.h"

/** Return the global word at __osFaultedThread. */

int __osGetCurrFaultedThread(void) {
    return __osFaultedThread;
}

extern void *__osRunningThread;




/** Return offset 0x14 from the supplied object or the default global object. */
OSId osGetThreadId(OSThread *object) {
    OSThread *object_record;
    if (object == 0) {
        object = __osRunningThread;
    }
    object_record = object;
    return object_record->id;
}
