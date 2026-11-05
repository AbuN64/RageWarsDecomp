#include "Common/runtime_declarations.h"
#include "Common/sessionhandlerrow.h"
#include "Common/contreadformat.h"
#include "types.h"
#include "Common/controller_motor_state.h"
#include "Common/boot_memory_and_thread_boundaries.h"
#include "../../../include/OS/controller.H"
#include <platform_sdk.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "../../../include/os_pif.h"
#include "../../../include/OS/__OSPACKRESETDATA.H"
#include "../../../include/OS/siaccess.H"
#include "../../../include/libultra/os/oscontreset_data.CPP.h"

/* controller.CPP */
s32 osContStartReadData(OSMesgQueue *completionQueue) {
    s32 result;
    u8 *p;

    __osSiGetAccess();
    p = &g_controllerLastCommand;
    if (*p != 1) {
        __osPackReadData();
        __osSiRawStartDma(1, &g_controllerQueryPifBuffer);
        osRecvMesg(completionQueue, 0, 1);
    }
    result = __osSiRawStartDma(0, &g_controllerQueryPifBuffer);
    *p = 1;
    __osSiRelAccess();
    return result;
}





void osContGetReadData(OSContPad *data) {
    u8 *ptr = (u8 *)&g_controllerQueryPifBuffer;
    u8 *count = g_controllerChannelCount;
    ContReadFormat readformat;
    s32 i;

    for (i = 0; i < *count; i++, ptr += sizeof(ContReadFormat), data++) {
        readformat = *(ContReadFormat *)ptr;
        data->errno = (readformat.rxsize & 0xC0) >> 4;
        if (data->errno != 0) {
            continue;
        }
        data->button = readformat.button;
        data->stick_x = readformat.stick_x;
        data->stick_y = readformat.stick_y;
    }
}

void __osPackReadData(void) {
    ContReadFormat readformat;
    u8 *ptr;
    u8 *count;
    s32 i;

    ptr = (u8 *)g_controllerQueryPifBuffer.ramarray;
    for (i = 14; i >= 0; i--) {
        ((s32 *)ptr)[i] = 0;
    }

    g_controllerQueryPifBuffer.pifstatus = 1;
    readformat.dummy = 0xFF;
    readformat.txsize = 1;
    readformat.rxsize = 4;
    readformat.cmd = 1;
    readformat.button = 0xFFFF;
    readformat.stick_x = -1;
    readformat.stick_y = -1;

    count = g_controllerChannelCount;
    for (i = 0; i < *count; i++) {
        *(ContReadFormat *)ptr = readformat;
        ptr += sizeof(ContReadFormat);
    }
    *ptr = 0xFE;
}

s32 osContReset(OSMesgQueue *queue, OSContStatus *controllerStatus) {
    s32 output;
    s32 result;
    u8 *state;
    s32 sentinel;

    __osSiGetAccess();
    state = &g_controllerLastCommand;
    sentinel = 0xFF;
    if (*state != sentinel) {
        char *data;

        __osPackResetData();
        data = &g_controllerQueryPifBuffer;
        __osSiRawStartDma(1, data);
        osRecvMesg(queue, 0, 1);
        __osSiRawStartDma(0, data);
        osRecvMesg(queue, 0, 1);
        __osPackRequestData(sentinel);
        __osSiRawStartDma(1, data);
        osRecvMesg(queue, 0, 1);
        *state = sentinel;
    }
    result = __osSiRawStartDma(0, &g_controllerQueryPifBuffer);
    osRecvMesg(queue, 0, 1);
    __osContGetInitData(&output, controllerStatus);
    __osSiRelAccess();
    return result;
}

void __osPackResetData(void) {
    OSPifRam *ram = (OSPifRam *)&g_controllerQueryPifBuffer;
    s32 channel;
    u8 *commandCursor;
    s32 val;

    commandCursor = &g_controllerQueryPifBuffer;
    ram->pifstatus = 1;
    val = 0xFD;
    channel = 3;
    do {
        *commandCursor = val;
        channel -= 1;
        commandCursor += 1;
    } while (channel >= 0);
    *commandCursor = 0xFE;
}

s32 osContInit(OSMesgQueue *queue, u8 *valid, OSContStatus *connectedPatternOut) {
    s32 node[8];
    s32 timerQueue[6];
    s32 message[2];
    u64 value;
    s32 result;
    s32 *initialized = &g_controllerInitialized;

    if (*initialized != 0) {
        return 0;
    }
    *initialized = 1;
    value = osGetTime();
    if (value <= 0x0165A0BBULL) {
        osCreateMesgQueue(timerQueue, (s32)message, 1);
        osSetTimer(node, 0x0165A0BCULL - value, 0, timerQueue, message);
        osRecvMesg(timerQueue, (s32)message, 1);
    }
    g_controllerChannelCount[0] = 4;
    __osPackRequestData(0);
    __osSiRawStartDma(1, &g_controllerQueryPifBuffer);
    osRecvMesg(queue, (s32)message, 1);
    result = __osSiRawStartDma(0, &g_controllerQueryPifBuffer);
    osRecvMesg(queue, (s32)message, 1);
    __osContGetInitData(valid, connectedPatternOut);
    g_controllerLastCommand = 0;
    __osSiCreateAccessQueue();
    osCreateMesgQueue(&g_controllerInitializationQueue, (s32)&g_controllerInitializationMessage, 1);
    return result;
}

/* G_CONTROLLERINITIALIZED.CPP */
#if defined(VERSION_US_REV1)
int g_controllerInitialized = 0;
#endif

/* OSMOTORINIT_DATA.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800D80A0_unclaimed_D8F40_unclaimed_D8F74 */
#if defined(VERSION_US_REV1)
struct {
    u8 alignmentFill[12];
} g_osmotorinitDataAddressWords __attribute__((aligned(4))) = {
    { 0x80, 0x15, 0x1B, 0xC8, 0x80, 0x15, 0x2B, 0x80, 0x00, 0x00, 0x00, 0x00 }
};
#endif

#if defined(VERSION_US_REV1)
s32 g_osmotorinitDataZeroWords[4] = {
    0, 0, 0, 0
};
#endif
#endif
