#include "COMMON/FORMAT.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "DATA_OVERLAY_LAYOUTS.H"
#include "TYPES.H"
#include "include_asm.h"


/* 800D0B2C.CPP */
float g_audioPitchRatioCurve[121] = {
    0.0313f, 0.0324f, 0.0335f, 0.0347f, 0.0359f, 0.0372f,
    0.0385f, 0.0398f, 0.0412f, 0.0427f, 0.0442f, 0.0458f,
    0.0474f, 0.049f, 0.0508f, 0.0526f, 0.0544f, 0.0563f,
    0.0583f, 0.0604f, 0.0625f, 0.0647f, 0.067f, 0.0693f,
    0.0718f, 0.0743f, 0.0769f, 0.0797f, 0.0825f, 0.0854f,
    0.0884f, 0.0915f, 0.0947f, 0.0981f, 0.1015f, 0.1051f,
    0.1088f, 0.1127f, 0.1166f, 0.1207f, 0.125f, 0.129f,
    0.134f, 0.139f, 0.144f, 0.149f, 0.154f, 0.159f,
    0.165f, 0.171f, 0.177f, 0.183f, 0.189f, 0.196f,
    0.203f, 0.21f, 0.218f, 0.225f, 0.233f, 0.241f,
    0.25f, 0.259f, 0.268f, 0.277f, 0.287f, 0.297f,
    0.308f, 0.319f, 0.33f, 0.342f, 0.354f, 0.366f,
    0.379f, 0.392f, 0.41f, 0.42f, 0.435f, 0.451f,
    0.467f, 0.483f, 0.5f, 0.518f, 0.536f, 0.555f,
    0.574f, 0.595f, 0.616f, 0.637f, 0.66f, 0.683f,
    0.707f, 0.732f, 0.758f, 0.785f, 0.812f, 0.841f,
    0.871f, 0.901f, 0.933f, 0.966f, 1.0f, 1.04f,
    1.07f, 1.11f, 1.15f, 1.2f, 1.23f, 1.28f,
    1.32f, 1.37f, 1.41f, 1.46f, 1.52f, 1.57f,
    1.63f, 1.68f, 1.74f, 1.8f, 1.87f, 1.93f,
    2.0f,
};
#if defined(VERSION_DE)

/* 800D0D10.CPP */
/* ROM-grounded data: rodata/writable/800D0D10 */
f32 g_GAudiopitchratiocurveWords5 = 26214400.0f;
#endif
#if defined(VERSION_EU)
f32 g_GAudiopitchratiocurveWords5 = 26214400.0f;
#endif
#if defined(VERSION_EU_X)
f32 g_GAudiopitchratiocurveWords5 = 26214400.0f;
#endif
#if defined(VERSION_US)
f32 g_GAudiopitchratiocurveWords5 = 26214400.0f;
#endif
#if defined(VERSION_US_REV1)
f32 g_GAudiopitchratiocurveWords5 = 26214400.0f;
#endif
#if defined(VERSION_DE)

/* 800D0D14.CPP */
s32 g_GAudiopitchratiocurveWords1[10] = {
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1
};
#endif
#if defined(VERSION_EU)
s32 g_GAudiopitchratiocurveWords1[10] = {
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1
};
#endif
#if defined(VERSION_EU_X)
s32 g_GAudiopitchratiocurveWords1[10] = {
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1
};
#endif
#if defined(VERSION_US)
s32 g_GAudiopitchratiocurveWords1[10] = {
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1
};
#endif
#if defined(VERSION_US_REV1)
s32 g_GAudiopitchratiocurveWords1[10] = {
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1
};
#endif
#ifdef VERSION_DE

/* 800D0D14_2.CPP */
/* ROM-grounded data: rodata/writable/800D0D3C */
unsigned int g_GAudiopitchratiocurveWords6[15] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x7F7F0000, 0x007F2929, 0x29000000,
};
#endif
#ifdef VERSION_EU
struct {
    unsigned int words0[2];
    char text1[12];
    unsigned int words2[10];
} g_GAudiopitchratiocurveWords6 = {
    {
        0x00000000, 0x00000000, 0x52204E4F, 0x55532041, 0x564F4952, 0x00000000, 0x00000000, 0x00000000,
    },
    "R NOUS AVOIR",
    {
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x7F7F0000,
        0x007F2929, 0x29000000,
    },
};
#endif
#ifdef VERSION_EU_X
unsigned int g_GAudiopitchratiocurveWords6[15] = {
    0x00000000, 0x00000000, 0x3F8DA520, 0x3F8D814B, 0x3F8D5D71, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x7F7F0000, 0x007F2929, 0x29000000,
};
#endif
#ifdef VERSION_US
unsigned int g_GAudiopitchratiocurveWords6[15] = {
    0x00000000, 0x00000000, 0x71755200, 0x00260700, 0x0010000B, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x7F7F0000, 0x007F2929, 0x29000000,
};
#endif
#ifdef VERSION_US_REV1
unsigned int g_GAudiopitchratiocurveWords6[15] = {
    0x00000000, 0x00000000, 0x3F8E3441, 0x3F8E1080, 0x3F8DECBA, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x7F7F0000, 0x007F2929, 0x29000000,
};
#endif
