#include "COMMON/FORMAT.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "DATA_OVERLAY_LAYOUTS.H"

#include "TYPES.H"

/* 800D06C0.CPP */
#if defined(VERSION_US_REV1)
float g_BlastFalloffWords1[25] = {
    0.8f, 0.9f, 0.914584f, 0.844435f, 0.711762f, 0.538774f,
    0.347679f, 0.160684f, 0.0f, -0.117057f, -0.192729f, -0.23415f,
    -0.248454f, -0.242774f, -0.224245f, -0.2f, -0.17596f, -0.153195f,
    -0.131565f, -0.110927f, -0.09114f, -0.072061f, -0.05355f, -0.035464f,
    -0.017661f,
};
#endif

/* 800D0724.CPP */
#if defined(VERSION_US_REV1)
float g_ModelSwaySamplesWords1[120] = {
    0.5118f, 0.6133f, 0.7257f, 0.8109f, 0.837f, 0.7398f,
    0.6093f, 0.4077f, 0.2169f, 0.0785f, 0.0395f, 0.0f,
    0.0497f, 0.1495f, 0.2897f, 0.408f, 0.5864f, 0.783f,
    0.9406f, 0.9869f, 1.0f, 0.9338f, 0.7957f, 0.6598f,
    0.5745f, 0.5089f, 0.4424f, 0.3485f, 0.2724f, 0.2325f,
    0.2487f, 0.3471f, 0.4945f, 0.6424f, 0.7669f, 0.7895f,
    0.7018f, 0.6105f, 0.4798f, 0.3106f, 0.2198f, 0.2245f,
    0.2409f, 0.3063f, 0.4331f, 0.5551f, 0.6211f, 0.6633f,
    0.6768f, 0.6399f, 0.5756f, 0.4991f, 0.4358f, 0.351f,
    0.3123f, 0.2456f, 0.2394f, 0.235f, 0.3232f, 0.412f,
    0.5516f, 0.6491f, 0.7533f, 0.7432f, 0.7247f, 0.6709f,
    0.6104f, 0.5112f, 0.4538f, 0.3369f, 0.2651f, 0.2296f,
    0.2548f, 0.3407f, 0.4778f, 0.5775f, 0.6626f, 0.7249f,
    0.6948f, 0.6387f, 0.5679f, 0.4792f, 0.3274f, 0.2008f,
    0.1288f, 0.1204f, 0.1287f, 0.2117f, 0.3809f, 0.4986f,
    0.5626f, 0.6308f, 0.7094f, 0.6511f, 0.5879f, 0.525f,
    0.4314f, 0.27f, 0.1672f, 0.1157f, 0.1245f, 0.1771f,
    0.2849f, 0.4542f, 0.5866f, 0.6452f, 0.6868f, 0.7077f,
    0.6341f, 0.5423f, 0.4744f, 0.3887f, 0.2938f, 0.268f,
    0.2965f, 0.3318f, 0.3902f, 0.4721f, 0.5217f, 0.5553f,
};

#if defined(VERSION_US_REV1)
f32 g_StatinstAdvanceresourcekeyWords1[3] = {
    1.39193606f, 1.39094257f, 1.38994896f
};
#endif
#endif

/* 8024E914_21.CPP */
#if defined(VERSION_US_REV1)
#if defined(VERSION_US_REV1)
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
