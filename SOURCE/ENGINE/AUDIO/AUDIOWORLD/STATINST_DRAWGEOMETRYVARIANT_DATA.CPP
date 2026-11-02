#include "COMMON/FORMAT.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "DATA_OVERLAY_LAYOUTS.H"
#include "TYPES.H"
#if defined(VERSION_DE)
#if defined(VERSION_DE)

/* 8024E914_18.CPP */
struct {
    s32 g_staticObjectResourceSerial;
    u8 retainedResourceSerialInstructions[12];
    s32 g_resourceCacheNodeCapacity;
    u8 retainedCacheCapacityWords[12];
    s32 g_resourceHashBucketCount;
    u32 g_resourceHashSlotCount;
    s32 g_resourceHashInitialized;
    u8 zeroHashTail[4];
    u32 g_audioTaskFrameIndex;
    u32 g_audioDmaPendingReadCount;
    s32 g_audioCommandBufferIndex;
    u32 g_audioWorkerEventCount;
    u32 g_audioWorkerElapsedTicks;
    s32 g_audioCacheEntryAllocCount;
    u8 retainedResourceStateWords[8];
    s32 g_audioContextInitialized;
} g_statinstDrawGeometryVariantWords __attribute__((aligned(4))) = {
    3670016,
    { 0x3c, 0x1, 0x80, 0xd, 0x0, 0x22, 0x8, 0x21, 0xac, 0x30, 0x43, 0x70 },
    1024,
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x43, 0x10, 0x25 },
    0,
    0x0,
    0,
    { 0x0, 0x0, 0x0, 0x0 },
    0x0,
    0x0,
    0,
    0x0,
    0x0,
    0,
    { 0x0, 0x0, 0x12, 0xc0, 0x0, 0x0, 0x0, 0xa0 },
    0
};
typedef char g_statinstDrawGeometryVariantWordsSizeCheck[(sizeof(g_statinstDrawGeometryVariantWords) == 84) ? 1 : -1];
#endif
#endif
