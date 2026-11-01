#include "thread_queue.h"
#include "COMMON/CARTRIDGEREADWORKER.H"
#include "TEXTURE/CARTRIDGE_DMA_AND_AUDIO_TIMING_VIEWS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/S1.H"
#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
#include "TYPES.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "UI/X_FILES/X_PLUS.H"
#include "include_asm.h"
#include "ENGINE/CACHE/LIST.H"

/* LOADER.CPP */
extern char g_Cartridge_RunReadWorkerPackedAddress24;

typedef struct Queue Queue;

void Cartridge_StartReadWorker(CartridgeReadWorker *worker, s32 count) {
    OSMesgQueue *completionQueue;
    s32 s0;
    s32 s1;

    osCreateMesgQueue(&worker->requestQueueStorage, &worker->requestMessages, 512);
    completionQueue = &worker->completionQueueStorage;
    osCreateMesgQueue(completionQueue, &worker->completionMessage, 1);
    osSetEventMesg(8, completionQueue, 2001);
    List_InitializeIntrusive(&worker->available, 24, 28);
    List_InitializeIntrusive(&worker->pending, 24, 28);
    s1 = 0;
    s0 = 3688;
    do {
        ((struct LinkedWorldFlagsView *) ((char *)worker + s0))->flags = 0;
        List_AppendIntrusive(&worker->available, (char *)worker + s0);
        s1 += 1;
        s0 += 32;
    } while (s1 < 528);
    XPlus_FillMemory(&worker->stack, count, 0x400);
    osCreateThread(worker, count, &g_Cartridge_RunReadWorkerPackedAddress24, worker, &worker->stack[sizeof(((CartridgeReadWorker *)0)->stack)], g_cartridgeReadWorkerPriority);
    osStartThread(worker);
}

void Cartridge_ReadChunksAndWait(struct CartridgeReadWorker *cartridgeReadWorker, u32 sourceAddress, s32 byteCount, void *extra) {
    char queue[24];
    s32 queue_init;
    s32 completed;
    s32 remaining;
    s32 length;
    Chunk *chunk;

    osCreateMesgQueue(queue, (s32) &queue_init, 1);
    remaining = byteCount;
    do {
        chunk = Cartridge_AcquireReadRequest(cartridgeReadWorker);
        length = 0x2000;
        if (chunk == 0) {
            break;
        }
        chunk->source = sourceAddress + (byteCount - remaining);
        chunk->destination = (char *) extra + (byteCount - remaining);
        if ((u32) remaining < 8193U) {
            length = remaining;
        }
        chunk->length = length;
        chunk->queue = queue;
        osJamMesg(&cartridgeReadWorker->requestQueueStorage, chunk, 1);
        osRecvMesg(queue, &completed, 1);
        remaining -= length;
    } while (remaining != 0);
}

void Cartridge_SubmitReadChunks(struct CartridgeReadWorker *worker, u32 source, s32 length, void *destination,
                   Queue *queue, s32 value, s32 direct) {
    s32 remaining;
    s32 chunk_length;
    Chunk *chunk;

    if (direct != 0) {
        chunk = Cartridge_AcquireReadRequest(worker);
        if (chunk != 0) {
            chunk->source = source;
            chunk->destination = destination;
            chunk->length = length;
            chunk->queue = queue;
            chunk->value = value;
            osJamMesg(&worker->requestQueueStorage, chunk, 1);
        }
    } else {
        remaining = length;
        do {
            chunk = Cartridge_AcquireReadRequest(worker);
            chunk_length = 0x2000;
            if (chunk == 0) {
                break;
            }
            chunk->source = source + (length - remaining);
            chunk->destination = (char *)destination + (length - remaining);
            if ((u32)remaining < 8193U) {
                chunk_length = remaining;
            }
            remaining -= chunk_length;
            chunk->length = chunk_length;
            if (remaining != 0) {
                chunk->queue = 0;
                chunk->value = 0;
            } else {
                chunk->queue = queue;
                chunk->value = value;
            }
            osSendMesg(&worker->requestQueueStorage, (s32)chunk, 1);
        } while ((chunk != 0) && (remaining != 0));
    }
}

#if defined(VERSION_US_REV1)
/* Phase1 source candidate; contract holds and immutable inputs in per-function JSON. */
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "TYPES.H"
#include "COMMON/CARTRIDGEREADWORKER.H"
/* Cartridge read thread loop: waits on the manager's request queue; a 0xBEEFDEAD message arms a
 * periodic timer that posts 0xDEADBEEF, a 0xDEADBEEF tick runs Libultra_RunDebugLinkCommands when TextLoad_IsArtsendTexturePreviewEnabled
 * reports work, and any other message is a read request whose buffer is invalidated, read from the
 * device through __osPiRawStartDma, awaited on the completion queue, flushed, acknowledged to its reply
 * queue when one is given and finally retired through Cartridge_ReleaseReadRequest. */

extern int TextLoad_IsArtsendTexturePreviewEnabled(void);
extern void Libultra_RunDebugLinkCommands(void);
extern void osWritebackDCache(void *, s32);
extern s32 __osPiRawStartDma(s32, u32, void *, u32);
extern void osInvalDCache(void *, s32);
extern void Cartridge_ReleaseReadRequest(s32, CartridgeReadRequest *);

void Cartridge_RunReadWorkerRev1(s32 cartridgeReadWorker) {
    struct OSTimer_s timer;
    struct CartridgeReadRequest *request;
    void *done;

    for (;;) {
        osRecvMesg(&((struct CartridgeReadWorker *)(cartridgeReadWorker))->requestQueueStorage, &request, 1);
        if (request == (struct CartridgeReadRequest *)0xBEEFDEAD) {
            osSetTimer(&timer, 0, 3750000, &((struct CartridgeReadWorker *)(cartridgeReadWorker))->requestQueueStorage, (void *)0xDEADBEEF);
        } else if (request == (struct CartridgeReadRequest *)0xDEADBEEF) {
            if (TextLoad_IsArtsendTexturePreviewEnabled() != 0) {
                Libultra_RunDebugLinkCommands();
            }
        } else {
            osWritebackDCache(request->buffer, request->size);
            __osPiRawStartDma(0, request->devAddr, request->buffer, request->size);
            osRecvMesg(&((struct CartridgeReadWorker *)(cartridgeReadWorker))->completionQueueStorage, &done, 1);
            osInvalDCache(request->buffer, request->size);
            if (request->replyQueue != 0) {
                osSendMesg(request->replyQueue, request->replyMsg, 1);
            }
            Cartridge_ReleaseReadRequest(cartridgeReadWorker, request);
        }
    }
}
#endif

#if !(defined(VERSION_US_REV1))
/* Receives read requests, transfers and acknowledges each one. The timer-message
 * handling belongs to the separate US-rev1 routine, which this item does not contain. */

extern void osWritebackDCache(void *, s32);
extern s32 __osPiRawStartDma(s32, u32, void *, u32);
extern void osInvalDCache(void *, s32);
extern void Cartridge_ReleaseReadRequest(s32, CartridgeReadRequest *);

void Cartridge_RunReadWorker(CartridgeReadWorker *worker) {
    CartridgeReadRequest *request;
    void *done;

    for (;;) {
        osRecvMesg(&worker->requestQueueStorage, &request, 1);
        osWritebackDCache(request->buffer, request->size);
        __osPiRawStartDma(0, request->devAddr, request->buffer, request->size);
        osRecvMesg(&worker->completionQueueStorage, &done, 1);
        osInvalDCache(request->buffer, request->size);
        if (request->replyQueue != 0) {
            osSendMesg(request->replyQueue, request->replyMsg, 1);
        }
        Cartridge_ReleaseReadRequest(worker, request);
    }
}
#endif

void *Cartridge_AcquireReadRequest(CartridgeReadWorker *cartridgeReadWorker) {
    u32 mask;
    void *head;

    mask = __osDisableInt();
    head = cartridgeReadWorker->available.head;
    if (head != 0) {
        List_RemoveIntrusive(&cartridgeReadWorker->available, head);
        ((CartridgeReadRequest *)head)->active = 1;
        List_PrependIntrusive(&cartridgeReadWorker->pending, head);
    }
    __osRestoreInt(mask);
    return head;
}

void Cartridge_ReleaseReadRequest(s32 worker, CartridgeReadRequest *request) {
    u32 mask;

    mask = __osDisableInt();
    List_RemoveIntrusive(&((CartridgeReadWorker *)worker)->pending, request);
    request->active = 0;
    List_PrependIntrusive(&((CartridgeReadWorker *)worker)->available, request);
    __osRestoreInt(mask);
}
