#include "Common/boot_memory_and_thread_boundaries.h"
#include "Common/runtime_declarations.h"
#include "Common/small_records.h"
#include "types.h"
#include <platform_sdk.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>

/* 802C0390_9.CPP */

/* seteventmesg.c */
extern struct IntPair g_osEventMessageBindings[];

void osSetEventMesg(OSEvent eventId, OSMesgQueue *messageQueue, OSMesg message) {
    u32 mask;
    struct IntPair *e;

    mask = __osDisableInt();
    ;
    (&g_osEventMessageBindings[eventId])->first = messageQueue;
    (*(&g_osEventMessageBindings[eventId])).second = message;
    __osRestoreInt(mask);
}
