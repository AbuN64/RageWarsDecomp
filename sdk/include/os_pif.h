#ifndef OS_PIF_H
#define OS_PIF_H
#include <platform_sdk.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
/* The controller and pak PIF RAM blocks and the SI access queue that the libultra os/pfs code shares. */
typedef struct OSPifRam {
    u32 ramarray[15];
    u32 pifstatus;
} OSPifRam;

typedef struct __OSContRequesFormat {
    u8 dummy, txsize, rxsize, cmd, typeh, typel, status, dummy1;
} __OSContRequesFormat;
extern struct OSPifRam g_controllerStatusPifBuffer;
extern struct OSPifRam g_controllerQueryPifBuffer;
extern u8 g_controllerChannelCount[];
extern OSMesgQueue g_peripheralDmaAccessQueue;
extern OSMesg g_peripheralDmaAccessMessage;
extern s32 g_peripheralAccessQueueInitialized[];
#endif
