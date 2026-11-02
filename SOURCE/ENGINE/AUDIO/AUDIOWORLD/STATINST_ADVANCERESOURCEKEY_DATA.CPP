#include "COMMON/FORMAT.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "DATA_OVERLAY_LAYOUTS.H"
#include "TYPES.H"
#if defined(VERSION_US_REV1)
#if defined(VERSION_US_REV1)

/* 8024E914_21.CPP */
struct {
    s32 g_staticObjectResourceSerial;
    u8 retainedResourceSerialFloatWords[12];
    s32 g_resourceCacheNodeCapacity;
    u8 retainedCacheCapacityFloatWords[12];
    s32 g_resourceHashBucketCount;
    u32 g_resourceHashSlotCount;
    s32 g_resourceHashInitialized;
    u8 retainedHashSizeFloatWord[4];
    u32 g_audioTaskFrameIndex;
    u32 g_audioDmaPendingReadCount;
    s32 g_audioCommandBufferIndex;
    u32 g_audioWorkerEventCount;
    u32 g_audioWorkerElapsedTicks;
    s32 g_audioCacheEntryAllocCount;
    u8 retainedResourceStateFloatWords[8];
    s32 g_audioContextInitialized;
} g_statinstAdvanceResourceKeyWritableWords __attribute__((aligned(4))) = {
    3670016,
    { 0x3f, 0xb1, 0xa8, 0xb6, 0x3f, 0xb1, 0x88, 0x23, 0x3f, 0xb1, 0x67, 0x8d },
    1024,
    { 0x3f, 0xb1, 0x26, 0x5e, 0x3f, 0xb1, 0x5, 0xc4, 0x3f, 0xb0, 0xe5, 0x28 },
    0,
    0x0,
    0,
    { 0x3f, 0xb0, 0x62, 0xaa },
    0x0,
    0x0,
    0,
    0x0,
    0x0,
    0,
    { 0x3f, 0xaf, 0x7e, 0xe, 0x3f, 0xaf, 0x5d, 0x5f },
    0
};
typedef char g_statinstAdvanceResourceKeyWritableWordsSizeCheck[(sizeof(g_statinstAdvanceResourceKeyWritableWords) == 84) ? 1 : -1];
#endif
#endif
