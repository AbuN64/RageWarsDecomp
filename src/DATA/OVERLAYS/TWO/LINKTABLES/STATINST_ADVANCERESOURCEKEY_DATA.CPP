#include "COMMON/FORMAT.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "DATA_OVERLAY_LAYOUTS.H"

#include "TYPES.H"

#if defined(VERSION_US)
#if defined(VERSION_US)
struct {
    s32 g_staticObjectResourceSerial;
    u8 alignmentFill4[12];
    s32 g_resourceCacheNodeCapacity;
    u8 alignmentFill20[12];
    s32 g_resourceHashBucketCount;
    u32 g_resourceHashSlotCount;
    s32 g_resourceHashInitialized;
    u8 alignmentFill44[4];
    u32 g_audioTaskFrameIndex;
    u32 g_audioDmaPendingReadCount;
    s32 g_audioCommandBufferIndex;
    u32 g_audioWorkerEventCount;
    u32 g_audioWorkerElapsedTicks;
    s32 g_audioCacheEntryAllocCount;
    u8 alignmentFill72[8];
    s32 g_audioContextInitialized;
} g_statinstAdvanceResourceKeyDataWords __attribute__((aligned(4))) = {
    3670016,
    { 0xa, 0x0, 0x4, 0x0, 0x0, 0x0, 0x1b, 0x53, 0x46, 0x58, 0x5f, 0x53 },
    1024,
    { 0x55, 0x4e, 0x5f, 0x43, 0x48, 0x41, 0x4d, 0x42, 0x45, 0x52, 0x5f, 0x48 },
    0,
    0x0,
    0,
    { 0x0, 0x10, 0x0, 0xb },
    0x0,
    0x0,
    0,
    0x0,
    0x0,
    0,
    { 0x52, 0x5f, 0x48, 0x49, 0x53, 0x53, 0x54, 0x0 },
    0
};
typedef char g_statinstAdvanceResourceKeyDataWordsSizeCheck[(sizeof(g_statinstAdvanceResourceKeyDataWords) == 84) ? 1 : -1];
#endif
#endif
