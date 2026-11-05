#include "Common/callback.h"
#include "types.h"
#include "Common/sharedplayer.h"
#include "Resmgr/stream.h"
#include "Resmgr/resmgr_string_memory.h"
#include "Common/rotation_extraction.h"
#include "Common/Lone/resource_request_queue.h"
#include "Scene/cache_freememory.h"
#include "include_asm.h"
#include "Common/selectionscreenstate.h"

/** Copy the same global float to two destinations. */
void Stream_SetFloatPairToNegativeOne(float *first, float *second) {
    float value = -1.0f;
    *first = value;
    *second = value;
}

struct Record;

void StreamBufferAppend(StreamBuffer *streamBuffer, const void *sourceData, s32 byteCount) {
    if ((streamBuffer->data) == 0) {
        void *allocation = Cache_AllocateMemory(byteCount);
        streamBuffer->data = allocation;
        streamBuffer->writePosition = 0;
        streamBuffer->capacity = byteCount;
    }
    {
        s32 t_c = streamBuffer->writePosition;
        u8 *t_0 = streamBuffer->data;
        XPlus_CopyBytes(t_0 + t_c, sourceData, byteCount);
    }
    streamBuffer->writePosition = (streamBuffer->writePosition) + byteCount;
}

void Cache_DrainAndCompactResources(s32);

s32 Cache_WaitForResourceLoads(struct ResourceLoadWorker *resourceLoadWorker);

void StreamBufferRead(StreamBuffer *readStream, void *destination, s32 byteCount)
{
  const u8 *sourceBytes;
  const u8 *readCursor;
  readCursor = readStream->data;
  readCursor = readCursor + readStream->readPosition;
  sourceBytes = readCursor;
  XPlus_CopyBytes(destination, sourceBytes, byteCount);
  readStream->readPosition = readStream->readPosition + byteCount;
}

void StreamBufferAllocate(StreamBuffer *streamBuffer, s32 capacityBytes) {
    if (streamBuffer->data == 0) {
        void *allocation = Cache_AllocateMemory(capacityBytes);
        streamBuffer->data = allocation;
        streamBuffer->writePosition = 0;
        streamBuffer->capacity = capacityBytes;
    }
}

void StreamBufferFree(StreamBuffer *streamBuffer) {
    void *bufferData;
    bufferData = streamBuffer->data;
    if (bufferData != 0) {
        Cache_FreeMemory(bufferData);
        streamBuffer->data = 0;
    }
    streamBuffer->writePosition = 0;
    streamBuffer->readPosition = 0;
    streamBuffer->capacity = 0;
}

void Stream_DrainResourceWork(void) {
    Cache_WaitForResourceLoads(&g_resourceCacheWorker);
    Cache_DrainAndCompactResources(0);
}

#if !(defined(VERSION_US_REV1))

#endif

#if defined(VERSION_EU_X)
char s_extSuffixText[4] =
    " EXT";
#endif

#if defined(VERSION_DE)
unsigned int k_MenuDrawscreenstackData[1] = {
    0x0029A164,
};
#endif

#if defined(VERSION_US_REV1)

#endif

#if defined(VERSION_EU)

#endif

#if defined(VERSION_US)

#endif

/* Retained data for this translation unit. */
#if defined(VERSION_EU)
const unsigned int g_controllerButtonDispatchTableEu[1] = {
    0x14C00009,
};
#endif
#if defined(VERSION_US)
const float g_controllerButtonDispatchTableUs[1] = {
    2.0f,
};
#endif
