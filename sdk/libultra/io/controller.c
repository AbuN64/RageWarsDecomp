#include "include_asm.h"
#include "COMMON/CONTROLLER_MOTOR_STATE.H"
#include "COMMON/PLAYER_POOL_AND_INODE_CACHE_VIEWS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "../../include/os_pif.h"

#if !(defined(VERSION_EU_X) || defined(VERSION_US_REV1))
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/CONTROLLER_MOTOR_STATE.H"
#include "TYPES.H"
#include "COMMON/PLAYER_POOL_AND_INODE_CACHE_VIEWS.H"
#include "../../include/os_pif.h"
void __osPfsRequestData(u8 cmd);

s32 osContInit_pfs(OSMesgQueue *queue, u8 *pattern) {
    ControllerInitStatusBytes data[4];
    void *dummy;
    u8 bitpattern;
    s32 i;
    u8 *count;
    s32 ret;
    s32 patternmask = 0;
    s32 retry = 3;
    __osSiGetAccess();
    do {
        __osPfsRequestData(0);
        __osSiRawStartDma(1, &g_controllerStatusPifBuffer);
        osRecvMesg(queue, &dummy, 1);
        ret = __osSiRawStartDma(0, &g_controllerStatusPifBuffer);
        osRecvMesg(queue, &dummy, 1);
        __osContGetInitData_pfs(&bitpattern, data);
        for (i = 0; i < g_controllerChannelCount[0]; i++) {
            if (!(data[i].team & 4)) {
                retry--;
                break;
            }
        }
        if (i == g_controllerChannelCount[0]) retry = 0;
    } while (retry > 0);
    count = g_controllerChannelCount;
    for (i = 0; i < *count; i++) {
        if (data[i].slot == 0 && (data[i].team & 1)) patternmask |= 1 << i;
    }
    __osSiRelAccess();
    *pattern = patternmask;
    return ret;
}
#endif

#if defined(VERSION_EU_X) || defined(VERSION_US_REV1)
extern void __osPfsRequestData(u8);

s32 osContInit_pfs(OSMesgQueue *queue, u8 *pattern) {
    ControllerInitStatusBytes data[4];
    void *dummy;
    u8 bitpattern;
    s32 i;
    u8 *count;
    s32 ret;
    s32 patternmask = 0;
    s32 retry = 3;
    __osSiGetAccess();
    do {
        __osPfsRequestData(0);
        __osSiRawStartDma(1, &g_controllerStatusPifBuffer);
        osRecvMesg(queue, &dummy, 1);
        ret = __osSiRawStartDma(0, &g_controllerStatusPifBuffer);
        osRecvMesg(queue, &dummy, 1);
        __osContGetInitData_pfs(&bitpattern, data);
        for (i = 0; i < g_controllerChannelCount[0]; i++) {
            if (!(data[i].team & 4)) {
                retry--;
                break;
            }
        }
        if (i == g_controllerChannelCount[0]) retry = 0;
    } while (retry > 0);
    count = g_controllerChannelCount;
    for (i = 0; i < *count; i++) {
        if (data[i].slot == 0 && (data[i].team & 1)) patternmask |= 1 << i;
    }
    __osSiRelAccess();
    *pattern = patternmask;
    return ret;
}
#endif

/* Sets the last controller command to the given byte, marks the pak PIF RAM block for execution and packs one request-status command per controller followed by the end marker (libultra __osPfsRequestData). Adapted from __osPackRequestData with the RAM clearing loop dropped, the command byte also stored to g_controllerLastCommand, and the pak PIF RAM block g_controllerStatusPifBuffer used in place of g_controllerQueryPifBuffer, with the pointer taken before the status word is written. */


/* Decodes the controller status replies in g_controllerStatusPifBuffer for each of g_controllerChannelCount channels, recording the error bits from each reply's receive size and, for a channel without error, its type and status, and stores the mask of answering channels through cmd. Adapted from __osContGetInitData_pfs. */


void __osPfsRequestData(u8 cmd) {
    u8 *ptr;
    __OSContRequesFormat requestformat;
    s32 i;
    u8 *count;

    g_controllerLastCommand = cmd;
    ptr = (u8 *)&g_controllerStatusPifBuffer;
    g_controllerStatusPifBuffer.pifstatus = 1;
    requestformat.dummy = 0xFF;
    requestformat.txsize = 1;
    requestformat.rxsize = 3;
    requestformat.cmd = cmd;
    requestformat.typeh = 0xFF;
    requestformat.typel = 0xFF;
    requestformat.status = 0xFF;
    requestformat.dummy1 = 0xFF;

    count = g_controllerChannelCount;
    for (i = 0; i < *count; i++) {
        *(__OSContRequesFormat *)ptr = requestformat;
        ptr += sizeof(requestformat);
    }
    *ptr = 0xFE;
}

void __osContGetInitData_pfs(u8 *valid, ControllerInitStatusBytes *data) {
    u8 *ptr;
    __OSContRequesFormat readformat;
    s32 i;
    u8 mask = 0;

    ptr = (u8 *)&g_controllerStatusPifBuffer;
    for (i = 0; i < g_controllerChannelCount[0]; i++, ptr += sizeof(readformat), data++) {
        readformat = *(__OSContRequesFormat *)ptr;
        data->slot = (readformat.rxsize & 0xC0) >> 4;
        if (data->slot != 0) {
            continue;
        }
        data->id = (readformat.typel << 8) | readformat.typeh;
        data->team = readformat.status;
        mask |= 1 << i;
    }
    *valid = mask;
}

