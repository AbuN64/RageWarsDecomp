#include "include_asm.h"
#include "TYPES.H"
#include "COMMON/OSPIHANDLE_S.H"
#include "COMMON/ALFXPARAM.H"
#include "../../include/libultra/io/pirawread.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "UI/X_FILES/X_PLUS.H"

extern OSPiHandle *g_peripheralHandleList;

OSPiHandle *osCartRomInit(void)
{
    u32 domain = 0;
    u32 saveMask;
    OSPiHandle *h = &g_diskPiHandle;
    OSPiHandle **table;

    if (h->baseAddress == 0xB0000000)
        return h;

    h->type = 0;
    h->baseAddress = 0xB0000000;
    osPiRawReadIo(0, &domain);
    h->latency = domain & 0xff;
    h->pulse = (domain >> 8) & 0xff;
    h->pageSize = (domain >> 0x10) & 0xf;
    h->relDuration = (domain >> 0x14) & 0xf;
    h->domain = 0;
    h->speed = 0;

    XPlus_FillMemory(&h->transferInfo, 0, sizeof(h->transferInfo));

    saveMask = __osDisableInt();
    table = &g_peripheralHandleList;
    h->next = *table;
    *table = h;
    __osRestoreInt(saveMask);

    return h;
}

#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US_REV1) || defined(VERSION_US)
typedef struct PiRequest {
    u16 type;
    u8 priority, status;
    OSMesgQueue *replyQueue;
    void *dramAddr;
    u32 deviceAddress, size;
    OSPiHandle *handle;
} PiRequest;
typedef struct PiManager {
    s32 active;
    void *thread;
    OSMesgQueue *commandQueue, *eventQueue, *accessQueue;
    s32 (*dma)(s32, u32, void *, u32);
    s32 (*extendedDma)(OSPiHandle *, s32, u32, void *, u32);
} PiManager;
extern s32 osEPiRawWriteIo(OSPiHandle *, u32, u32);
extern s32 osEPiRawReadIo(OSPiHandle *, u32, u32 *);

/* The PI manager thread: serves DMA and 64DD disk requests from the command queue for ever. */
void __osDevMgrMain(void *argument) {
    PiManager *manager = argument;
    PiRequest *request = 0;
    OSMesg access, event;
    OSPiHandle *handle;
    __OSBlockInfo *block;
    __OSTranxInfo *transfer;
    u32 status;
    s32 twoBlocks, result;

    for (;;) {
        osRecvMesg(manager->commandQueue, (OSMesg *)&request, 1);
        handle = (OSPiHandle *)request->handle;
        if (handle != 0 && handle->type == 2 &&
            (transfer = &handle->transferInfo)->cmdType <= 1) {
            block = &transfer->block[handle->transferInfo.blockNum];
            handle->transferInfo.sectorNum = -1;
            if (handle->transferInfo.transferMode != 3) {
                block->dramAddr -= block->sectorSize;
            }
            twoBlocks = 0;
            if (handle->transferInfo.transferMode == 2) {
                twoBlocks = (&request->handle->transferInfo)->cmdType == 0;
            }
            osRecvMesg(manager->accessQueue, &access, 1);
            __osResetGlobalIntMask(0x100401);
            osEPiRawWriteIo(request->handle, 0x05000510, handle->transferInfo.bmCtlShadow | 0x80000000);
            diskEvent:
            {
                osRecvMesg(manager->eventQueue, &event, 1);
                handle = (OSPiHandle *)request->handle;
                transfer = &handle->transferInfo;
                block = &transfer->block[handle->transferInfo.blockNum];
                if (block->errStatus == 29) {
                    osEPiRawWriteIo((OSPiHandle *)handle, 0x05000510, handle->transferInfo.bmCtlShadow | 0x10000000);
                    osEPiRawWriteIo(request->handle, 0x05000510, handle->transferInfo.bmCtlShadow);
                    osEPiRawReadIo(request->handle, 0x05000508, &status);
                    if (status & 0x02000000) {
                        osEPiRawWriteIo(request->handle, 0x05000510, handle->transferInfo.bmCtlShadow | 0x01000000);
                    }
                    block->errStatus = 4;
                    *(volatile u32 *)0xA4600010 = 2;
                    __osSetGlobalIntMask(0x100C01);
                }
                osSendMesg(request->replyQueue, request, 0);
                if (twoBlocks == 1 &&
                    (&request->handle->transferInfo)->block[0].errStatus == 0) {
                    twoBlocks = 0;
                    goto diskEvent;
                }
            }
            osSendMesg(manager->accessQueue, 0, 0);
            if ((&request->handle->transferInfo)->blockNum == 1) {
                osYieldThread();
            }
            continue;
        }
        switch (request->type) {
        case 11:
            osRecvMesg(manager->accessQueue, &access, 1);
            result = manager->dma(0, request->deviceAddress, request->dramAddr, request->size);
            break;
        case 12:
            osRecvMesg(manager->accessQueue, &access, 1);
            result = manager->dma(1, request->deviceAddress, request->dramAddr, request->size);
            break;
        case 15:
            osRecvMesg(manager->accessQueue, &access, 1);
            result = manager->extendedDma(request->handle, 0, request->deviceAddress, request->dramAddr, request->size);
            break;
        case 16:
            osRecvMesg(manager->accessQueue, &access, 1);
            result = manager->extendedDma(request->handle, 1, request->deviceAddress, request->dramAddr, request->size);
            break;
        case 10:
            osSendMesg(request->replyQueue, request, 0);
            /* A loopback message has no DMA completion to wait for. */
        default:
            result = -1;
            break;
        }
        if (result == 0) {
            osRecvMesg(manager->eventQueue, &event, 1);
            osSendMesg(request->replyQueue, request, 0);
            osSendMesg(manager->accessQueue, 0, 0);
        }
    }
}

#endif
