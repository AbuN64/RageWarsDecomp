#include "DATA/REST_SOURCE_RECORDS.H"
extern char g_actorStateEnd_us_rev1[];
extern char g_actorStateTableEndWords[];
#if defined(VERSION_US_REV1)
extern RestminigunTextLayout331 g_minigunText;
#endif
extern char g_overlayThreeActorStateEndFragment1[];
extern char g_overlayThreeActorStateEndFragment2[];
extern char g_overlayThreeActorStateEndFragment3[];
extern char g_overlayThreeActorStateEndFragment4[];
extern char g_overlayThreeActorStateEndFragment5[];
#include "include_asm.h"

/* g_ConeAttenuationWords1_GMiniguntext.CPP */
#if defined(VERSION_US_REV1)
float g_ConeAttenuationWords1[65] = {
    0.0f, 0.125f, 0.176777f, 0.216506f, 0.25f, 0.279509f,
    0.306186f, 0.330719f, 0.353553f, 0.375f, 0.395285f, 0.414578f,
    0.433013f, 0.450694f, 0.467707f, 0.484123f, 0.5f, 0.515388f,
    0.53033f, 0.544862f, 0.559017f, 0.572822f, 0.586302f, 0.599479f,
    0.612372f, 0.625f, 0.637377f, 0.649519f, 0.661438f, 0.673146f,
    0.684653f, 0.695971f, 0.707107f, 0.71807f, 0.728869f, 0.73951f,
    0.75f, 0.760345f, 0.770552f, 0.780625f, 0.790569f, 0.800391f,
    0.810093f, 0.81968f, 0.829156f, 0.838525f, 0.847791f, 0.856957f,
    0.866025f, 0.875f, 0.883883f, 0.892679f, 0.901388f, 0.910014f,
    0.918559f, 0.927025f, 0.935414f, 0.943729f, 0.951972f, 0.960143f,
    0.968246f, 0.976281f, 0.984251f, 0.992157f, 1.0f,
};
#endif

/* g_GMiniguntextWords1_GMiniguntext.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800D2648_unclaimed_D3450 */
s32 g_GMiniguntextWords1[1] = {
    1,
};

u16 g_ColorJitterHalfwords1[46] = {
    63481, 63733, 2062, 6412, 4631, 6670,
    64750, 62179, 55266, 58855, 58845, 58090,
    57829, 61426, 2, 65267, 62455, 1282,
    65033, 6175, 8733, 5400, 2573, 65018,
    275, 7975, 7454, 5140, 65521, 59116,
    59617, 58344, 59121, 61698, 4360, 1809,
    3593, 3084, 1036, 1290, 3333, 65022,
    63223, 63723, 60392, 22272,
};
#endif

#if defined(VERSION_US_REV1)
/* bytes live in the preceding array */
#endif

/* g_minigunText_GMiniguntext.CPP */
#if defined(VERSION_US_REV1)
RestminigunTextLayout331 g_minigunText = {
    { 0, 0 },
    { (void *)&g_minigunText, (void *)&g_minigunText, (void *)((char *)&g_actorStateEnd_us_rev1 + 40), (void *)((char *)&g_overlayThreeActorStateEndFragment3 + 40), (void *)((char *)&g_actorStateTableEndWords + 40), (void *)&g_minigunText, (void *)((char *)&g_overlayThreeActorStateEndFragment1 + 40), (void *)((char *)&g_overlayThreeActorStateEndFragment2 + 40), (void *)&g_minigunText, (void *)((char *)&g_overlayThreeActorStateEndFragment4 + 40), (void *)((char *)&g_overlayThreeActorStateEndFragment5 + 40), (void *)&g_minigunText, (void *)&g_minigunText, (void *)&g_minigunText, (void *)&g_minigunText },
    "E\000\000\000MINIGUN\000",
    1.0f,
};
#endif
