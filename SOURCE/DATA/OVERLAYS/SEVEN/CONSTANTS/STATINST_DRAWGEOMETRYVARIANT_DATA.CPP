#include "COMMON/FORMAT.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "DATA_OVERLAY_LAYOUTS.H"

#include "TYPES.H"

#if defined(VERSION_EU_X)
#if defined(VERSION_EU_X)
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
} g_statinstDrawGeometryVariantTable_eu_x __attribute__((aligned(4))) = {
    3670016,
    { 0x3f, 0xb1, 0x26, 0x5e, 0x3f, 0xb1, 0x5, 0xc4, 0x3f, 0xb0, 0xe5, 0x28 },
    1024,
    { 0x3f, 0xb0, 0xa3, 0xed, 0x3f, 0xb0, 0x83, 0x4c, 0x3f, 0xb0, 0x62, 0xaa },
    0,
    0x0,
    0,
    { 0x3f, 0xaf, 0xe0, 0x12 },
    0x0,
    0x0,
    0,
    0x0,
    0x0,
    0,
    { 0x3f, 0xae, 0xfb, 0x47, 0x3f, 0xae, 0xda, 0x91 },
    0
};
typedef char g_statinstDrawGeometryVariantTable_eu_xSizeCheck[(sizeof(g_statinstDrawGeometryVariantTable_eu_x) == 84) ? 1 : -1];
#endif
#endif
