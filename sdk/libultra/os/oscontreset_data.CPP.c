#include "include_asm.h"
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/CONTREADFORMAT.H"
#include "../../include/os_pif.h"

/* oscontreset_data.CPP */
/* Clears the controller PIF RAM block, sets its status word to execute, and packs one request-status command with the given command byte per controller followed by the end marker (libultra __osPackRequestData). Adapted from __osPackReadData with the request format and command argument changed, the clearing loop counting up and the status word written through a local pointer to the PIF RAM block. */

void __osPackRequestData(u8 cmd) {
    u8 *ptr;
    __OSContRequesFormat requestformat;
    s32 i;
    u8 *count;
    OSPifRam *pifram;

    for (i = 0; i < 15; i++) {
        ((u32 *)&g_controllerQueryPifBuffer)[i] = 0;
    }
    pifram = &g_controllerQueryPifBuffer;
    pifram->pifstatus = 1;
    ptr = (u8 *)pifram->ramarray;
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

void __osContGetInitData(u8 *valid, ControllerInitStatusBytes *data) {
    u8 *ptr;
    __OSContRequesFormat readformat;
    s32 i;
    u8 mask = 0;

    ptr = (u8 *)&g_controllerQueryPifBuffer;
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
