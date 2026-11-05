#include "include_asm.h"
#include "types.h"
#include <platform_sdk.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "Common/runtime_declarations.h"
#include "Ui/Tsmos/Screens/pakinterfacescreen.h"
#include "Common/cartridgereadworker.h"
#include "Engine/Cache/mutex.h"

/* MUTEX.CPP */

/* Steps an object's nesting count up and back down while it is nonzero, each step bracketed by __osDisableInt_Mutex and __osRestoreInt: going up past one calls osRecvMesg_Mutex, and coming down to anything but zero calls osSendMesg_Mutex. */
typedef struct Object {
    char pad0[0x1C];
    s32 depth;
} Object;

void Mutex_WaitUntilReleased(Object *obj) {
    s32 mask;
    s32 mask2;

    if (obj->depth == 0) {
        return;
    }
    mask = __osDisableInt();
    if (++obj->depth != 1) {
        __osRestoreInt(mask);
        osRecvMesg(obj, 0, 1);
    } else {
        __osRestoreInt(mask);
    }
    mask2 = __osDisableInt();
    if (--obj->depth != 0) {
        __osRestoreInt(mask2);
        osSendMesg(obj, 0, 1);
        return;
    }
    __osRestoreInt(mask2);
}

void Mutex_InitializeQueueLock(MenuRules *menuRules) {
    menuRules->locked = 0;
    osCreateMesgQueue(menuRules, &menuRules->message, 1);
}
