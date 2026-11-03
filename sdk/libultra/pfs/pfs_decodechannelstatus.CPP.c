#include "../../include/OSCONTREQUESFORMATSHORT.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "../../include/PFS/pfs_decodechannelstatus.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "../../include/os_pif.h"
#include "../../include/libultra/os/oscontreset_data.CPP.h"
#include "../../include/libultra/pfs/pfs_decodechannelstatus.CPP.h"

/* pfs_decodechannelstatus.CPP */
/* __osPfsGetStatus, drafted from ultralib src/io/pfsgetstatus.c (2.0I branch): send a status request
   to one controller through the pak PIF RAM block and turn its reply into a pack-present, new-pack
   or failure code. */

/* __osPfsRequestOneChannel, drafted from the ultralib io pfsgetstatus source (2.0I branch): fill the pak
   PIF RAM block with one skip byte per preceding channel, a status request for the given channel and
   the end marker. */

/* Decodes the six-byte short controller status reply found one byte per preceding channel into g_controllerStatusPifBuffer for the given channel, recording its error bits and, without error, its type and status.
   Adapted from __osContGetInitData with the per-channel loop over eight-byte replies changed to a single six-byte reply reached by skipping one byte per preceding channel. */

s32 __osPfsGetStatus(void *queue, int channel)
{
    s32 ret = 0;
    void *dummy;
    ControllerInitStatusBytes data;

    __osPfsRequestOneChannel(channel);

    ret = __osSiRawStartDma(1, &g_controllerStatusPifBuffer);
    osRecvMesg(queue, &dummy, 1);

    ret = __osSiRawStartDma(0, &g_controllerStatusPifBuffer);
    osRecvMesg(queue, &dummy, 1);

    Pfs_DecodeChannelStatus(channel, &data);

    if (((data.team & 1) != 0) && ((data.team & 2) != 0)) {
        return 2;
    } else if ((data.slot != 0) || ((data.team & 1) == 0)) {
        return 1;
    } else if ((data.team & 4) != 0) {
        return 4;
    }

    return ret;
}

void __osPfsRequestOneChannel(int channel)
{
    u8 *base;
    u8 *ptr;
    __OSContRequesFormatShort requestformat;
    int i;

    g_controllerLastCommand = 0;
    base = (u8 *)&g_controllerStatusPifBuffer;
    g_controllerStatusPifBuffer.pifstatus = 1;
    ptr = base;

    requestformat.txsize = 1;
    requestformat.rxsize = 3;
    requestformat.cmd = 0;
    requestformat.typeh = 0xFF;
    requestformat.typel = 0xFF;
    requestformat.status = 0xFF;

    for (i = 0; i < channel; i++) {
        *ptr++ = 0;
    }

    *(__OSContRequesFormatShort *)ptr = requestformat;
    ptr += sizeof(__OSContRequesFormatShort);
    *ptr = 0xFE;
}

void Pfs_DecodeChannelStatus(s32 channel, ControllerInitStatusBytes *data) {
    u8 *ptr;
    __OSContRequesFormatShort requestformat;
    s32 i;

    ptr = (u8 *)&g_controllerStatusPifBuffer;
    for (i = 0; i < channel; i++) {
        ptr++;
    }
    requestformat = *(__OSContRequesFormatShort *)ptr;
    data->slot = (requestformat.rxsize & 0xC0) >> 4;
    if (data->slot == 0) {
        data->id = (requestformat.typel << 8) | requestformat.typeh;
        data->team = requestformat.status;
    }
}
