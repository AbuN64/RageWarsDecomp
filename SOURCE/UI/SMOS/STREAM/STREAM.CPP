#include "COMMON/CALLBACK.H"
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "RESMGR/STREAM.H"
#include "RESMGR/resmgr_string_memory.H"
#include "COMMON/OBJRECAT3CV2.H"
#include "COMMON/LONE/RESOURCE_REQUEST_QUEUE.H"
#include "SCENE/CACHE_FREEMEMORY.H"
#include "include_asm.h"

/* STREAM.CPP */
/** Copy the same global float to two destinations. */
void Stream_SetFloatPairToNegativeOne(float *first, float *second) {
    float value = g_streamFloatPairInitialValue;
    *first = value;
    *second = value;
}

struct Record;
extern struct Record *Cache_AllocateMemory(s32 byteCount);

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

/* STREAM_SETFLOATPAIRTONEGATIVEONE_DATA.CPP */
#if !(defined(VERSION_US_REV1))
const float g_Stream_SetFloatPairToNegativeOneConstantWords_de_eu_eu_x_us[1] = {
    -1.0f,
};
#endif

#if defined(VERSION_EU_X)
char k_MenuDrawscreenstackEncodedWordsBlock1[4] =
    " EXT";
#endif

#if defined(VERSION_DE)
unsigned int k_MenuDrawscreenstackEncodedWords[1] = {
    0x0029A164,
};
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/g_Stream_SetFloatPairToNegativeOneConstantWords_us_rev1_MenuDrawscreenstackData.c */
const float g_Stream_SetFloatPairToNegativeOneConstantWords_us_rev1[1] = {
    -1.0f,
};
#endif

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
