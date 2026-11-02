#include "DATA/REST_SOURCE_RECORDS.H"
#if defined(VERSION_DE)
extern RestGMenuboxcornersLevelTextWords1Layout487 g_menuBoxLevelStatusText;
#endif
#if defined(VERSION_EU_X)
extern RestGMenuboxcornersLevelTextWords2Layout491 g_GMenuboxcornersLevelTextWords2;
#endif
#if defined(VERSION_EU)
extern RestGMenuboxcornersLevelTextWords3Layout493 g_GMenuboxcornersLevelTextWords3;
#endif
#if defined(VERSION_US)
extern RestGMenuboxcornersOurclevelTextWords1Layout489 g_menuBoxCurrentLevelText;
#endif
#include "include_asm.h"
#include "MENU/MENU_BOX.H"

/* GMenuboxcornersWords1.CPP */
/* ROM-grounded data: rodata/writable/800E5E48 */
#ifdef VERSION_DE
RestGMenuboxcornersWords1Layout481 g_GMenuboxcornersWords1 = {
    5,
    "MiniGames\000\000\000BLANK\000\000\000Trap Sho",
    0x6F7400CC,
    24.0f,
    -1,
};
#endif
#ifdef VERSION_EU
RestGMenuboxcornersWords1Layout482 g_GMenuboxcornersWords1 = {
    5,
    "MiniGames\000\000\000BLANK\000\000\000Trap Sho",
    0x6F7400F8,
    { 4239624, -1 },
};
#endif
#ifdef VERSION_EU_X
RestGMenuboxcornersWords1Layout483 g_GMenuboxcornersWords1 = {
    5,
    "MiniGames\000\000\000BLANK\000\000\000Trap Shoot\000$",
    0x8FB40020,
    -1,
};
#endif
#ifdef VERSION_US
RestGMenuboxcornersWords1Layout484 g_GMenuboxcornersWords1 = {
    5,
    "MiniGames\000\000\000BLANK\000\000\000Trap Shoot\000:\\Pro",
    -1,
};
#endif
#ifdef VERSION_US_REV1
RestGMenuboxcornersWords1Layout485 g_GMenuboxcornersWords1 = {
    5,
    "MiniGames\000\000\000BLANK\000\000\000Trap Shoot\000ANTED",
    -1,
};
#endif

/* FloatRecordWords.CPP */
#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE)
RestD_src_afbf569bLayout486 D_src_afbf569b = {
    0,
    { 21.599998f, 24.0f, 0.9f, 1.0f },
    0x02FFFFC8,
    "VG/\000",
    1,
    { 9.9f, 1e+01f, 0.80999994f, 1.0f },
    0x02FFFFC8,
    "VG/\000\000\000\000\000AO\\)",
    { 16.8f, 0.54f, 0.6f },
    0x02FFFFC8,
    "VG/\000",
    1,
    { 8.099999f, 7.5f, 0.67499995f, 0.75f },
    0x02FFFFC8,
    "VG/\000\000\000\000\000AO\\)",
    { 16.8f, 0.54f, 0.6f },
    16777160,
    "VG/\000",
    1,
    { 8.099999f, 7.0f, 0.71999997f, 0.7f },
    0x02FFFFC8,
    "VG/\000\000\000\000\000",
    { 15.119999f, 24.0f, 0.63f, 1.0f },
    0x02FFFFC8,
    "VG/\000",
    2,
    { 7.2f, 8.0f, 0.9f, 1.0f },
    0x01FFFFC8,
    { -14336, 1 },
    { 8.099999f, 1e+01f, 0.67499995f, 1.0f },
    0x02FFFFC8,
    "VG/\000",
};
MenuBoxCorner g_menuBoxCorners[8] = {
    { -1, -1, 0, 0, 0, 0 },
    { 1, -1, 0, 0, 0, 0 },
    { 1, 1, 0, 0, 0, 0 },
    { -1, 1, 0, 0, 0, 0 },
    { -1, -1, -2, 0, 0, 0 },
    { 1, -1, -2, 0, 0, 0 },
    { 1, 1, -2, 0, 0, 0 },
    { -1, 1, -2, 0, 0, 0 },
};
RestGMenuboxcornersLevelTextWords1Layout487 g_menuBoxLevelStatusText = {
    { 0, 0 },
    -5.5e+02f,
    "  : level         :      \000\000\000",
    (void *)((char *)&g_menuBoxLevelStatusText + 0x10),
    "lod chg dist  :      \000\000\000",
    (void *)((char *)&g_menuBoxLevelStatusText + 0x2C),
    "global scaler :      \000\000\000",
    (void *)((char *)&g_menuBoxLevelStatusText + 0x48),
    "music         :  none\000\000\000",
    (void *)((char *)&g_menuBoxLevelStatusText + 0x64),
    0x20202020,
    0x20202020,
    0x20202020,
    0x20202020,
    0x20202020,
    0x20202020,
    0x20202020,
    0x20202020,
    0x20202020,
    0x20202020,
    0x20202020,
    0x20000000,
    (void *)((char *)&g_menuBoxLevelStatusText + 0x80),
};
#endif
#if defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US)
RestD_src_afbf569bLayout488 D_src_afbf569b = {
    0,
    { 24.0f, 24.0f, 1.0f, 1.0f },
    0x02FFFFC8,
    "VG/\000",
    1,
    "A0\000\000A \000\000?fff",
    1.0f,
    0x02FFFFC8,
    "VG/\000\000\000\000\000Affg",
    { 16.8f, 0.6f, 0.6f },
    0x02FFFFC8,
    "VG/\000",
    1,
    { 9.0f, 7.5f, 0.75f, 0.75f },
    0x02FFFFC8,
    "VG/\000\000\000\000\000Affg",
    { 16.8f, 0.6f, 0.6f },
    16777160,
    "VG/\000\000\000\000\000",
    { 6.0f, 8.4f, 0.25f, 0.25f },
    0x02FFFFC8,
    "VG/\000\000\000\000\000",
    { 19.2f, 24.0f, 0.8f, 1.0f },
    0x02FFFFC8,
    "VG/\000",
    2,
    { 8.0f, 8.0f, 1.0f, 1.0f },
    0x01FFFFC8,
    { -14336, 1 },
    { 9.0f, 1e+01f, 0.75f, 1.0f },
    0x02FFFFC8,
    "VG/\000",
};
#endif
#endif

#if defined(VERSION_US)
#if defined(VERSION_US)
MenuBoxCorner g_menuBoxCorners[8] = {
    { -1, -1, 0, 0, 0, 0 },
    { 1, -1, 0, 0, 0, 0 },
    { 1, 1, 0, 0, 0, 0 },
    { -1, 1, 0, 0, 0, 0 },
    { -1, -1, -2, 0, 0, 0 },
    { 1, -1, -2, 0, 0, 0 },
    { 1, 1, -2, 0, 0, 0 },
    { -1, 1, -2, 0, 0, 0 },
};
RestGMenuboxcornersOurclevelTextWords1Layout489 g_menuBoxCurrentLevelText = {
    { 0, 0 },
    -5.5e+02f,
    "ourclevel         :      \000\000\000",
    (void *)((char *)&g_menuBoxCurrentLevelText + 0x10),
    "lod chg dist  :      \000\000\000",
    (void *)((char *)&g_menuBoxCurrentLevelText + 0x2C),
    "global scaler :      \000\000\000",
    (void *)((char *)&g_menuBoxCurrentLevelText + 0x48),
    "music         :  none\000\000\000",
    (void *)((char *)&g_menuBoxCurrentLevelText + 0x64),
    0x20202020,
    0x20202020,
    0x20202020,
    0x20202020,
    0x20202020,
    0x20202020,
    0x20202020,
    0x20202020,
    0x20202020,
    0x20202020,
    0x20202020,
    0x20000000,
    (void *)((char *)&g_menuBoxCurrentLevelText + 0x80),
};
#endif
#endif

#if defined(VERSION_EU_X)
#if defined(VERSION_EU_X)
RestfloatRecordWordsEuXLayout490 g_floatRecordWordsEuX = {
    0,
    { 18.0f, 24.0f, 0.75f, 1.0f },
    0x02FFFFC8,
    "VG/\000",
    1,
    { 8.25f, 1e+01f, 0.67499995f, 1.0f },
    0x02FFFFC8,
    "VG/\000\000\000\000\000",
    { 10.8f, 16.8f, 0.45000002f, 0.6f },
    0x02FFFFC8,
    "VG/\000",
    1,
    { 6.75f, 7.5f, 0.5625f, 0.75f },
    0x02FFFFC8,
    "VG/\000\000\000\000\000",
    { 10.8f, 16.8f, 0.45000002f, 0.6f },
    16777160,
    "VG/\000",
    1,
    { 6.75f, 7.0f, 0.6f, 0.7f },
    0x02FFFFC8,
    "VG/\000\000\000\000\000",
    { 12.599999f, 24.0f, 0.525f, 1.0f },
    0x02FFFFC8,
    "VG/\000",
    2,
    { 6.0f, 8.0f, 0.75f, 1.0f },
    0x01FFFFC8,
    { -14336, 1 },
    { 6.75f, 1e+01f, 0.5625f, 1.0f },
    0x02FFFFC8,
    "VG/\000\000\000\000\000",
    { 18.0f, 24.0f, 0.75f, 1.0f },
    0x02FFFFC8,
    "VG/\000",
    1,
    { 8.25f, 1e+01f, 0.67499995f, 1.0f },
    0x02FFFFC8,
    "VG/\000\000\000\000\000",
    { 10.8f, 16.8f, 0.45000002f, 0.6f },
    0x02FFFFC8,
    "VG/\000",
    1,
    { 6.75f, 7.5f, 0.5625f, 0.75f },
    0x02FFFFC8,
    "VG/\000\000\000\000\000",
    { 10.8f, 16.8f, 0.45000002f, 0.6f },
    16777160,
    "VG/\000",
    1,
    { 6.75f, 7.0f, 0.6f, 0.7f },
    0x02FFFFC8,
    "VG/\000\000\000\000\000",
    { 12.599999f, 24.0f, 0.525f, 1.0f },
    0x02FFFFC8,
    "VG/\000",
    2,
    { 6.0f, 8.0f, 0.75f, 1.0f },
    0x01FFFFC8,
    { -14336, 1 },
    { 6.75f, 1e+01f, 0.5625f, 1.0f },
    0x02FFFFC8,
    "VG/\000\000\000\000\000",
    { 18.0f, 24.0f, 0.75f, 1.0f },
    0x02FFFFC8,
    "VG/\000",
    1,
    { 8.25f, 1e+01f, 0.67499995f, 1.0f },
    0x02FFFFC8,
    "VG/\000\000\000\000\000",
    { 10.8f, 16.8f, 0.45000002f, 0.6f },
    0x02FFFFC8,
    "VG/\000",
    1,
    { 6.75f, 7.5f, 0.5625f, 0.75f },
    0x02FFFFC8,
    "VG/\000\000\000\000\000",
    { 10.8f, 16.8f, 0.45000002f, 0.6f },
    16777160,
    "VG/\000",
    1,
    { 6.75f, 7.0f, 0.6f, 0.7f },
    0x02FFFFC8,
    "VG/\000\000\000\000\000",
    { 12.599999f, 24.0f, 0.525f, 1.0f },
    0x02FFFFC8,
    "VG/\000",
    2,
    { 6.0f, 8.0f, 0.75f, 1.0f },
    0x01FFFFC8,
    { -14336, 1 },
    { 6.75f, 1e+01f, 0.5625f, 1.0f },
    0x02FFFFC8,
    "VG/\000",
};
MenuBoxCorner g_menuBoxCorners[8] = {
    { -1, -1, 0, 0, 0, 0 },
    { 1, -1, 0, 0, 0, 0 },
    { 1, 1, 0, 0, 0, 0 },
    { -1, 1, 0, 0, 0, 0 },
    { -1, -1, -2, 0, 0, 0 },
    { 1, -1, -2, 0, 0, 0 },
    { 1, 1, -2, 0, 0, 0 },
    { -1, 1, -2, 0, 0, 0 },
};
RestGMenuboxcornersLevelTextWords2Layout491 g_GMenuboxcornersLevelTextWords2 = {
    { 0, 0 },
    -5.5e+02f,
    "level         :      \000\000\000",
    { (void *)((char *)&g_GMenuboxcornersLevelTextWords2 + 0xC), (void *)((char *)&g_GMenuboxcornersLevelTextWords2 + 0xC), (void *)((char *)&g_GMenuboxcornersLevelTextWords2 + 0xC), (void *)((char *)&g_GMenuboxcornersLevelTextWords2 + 0xC) },
    "lod chg dist  :      \000\000\000",
    { (void *)((char *)&g_GMenuboxcornersLevelTextWords2 + 0x34), (void *)((char *)&g_GMenuboxcornersLevelTextWords2 + 0x34), (void *)((char *)&g_GMenuboxcornersLevelTextWords2 + 0x34), (void *)((char *)&g_GMenuboxcornersLevelTextWords2 + 0x34) },
    "global scaler :      \000\000\000",
    { (void *)((char *)&g_GMenuboxcornersLevelTextWords2 + 0x5C), (void *)((char *)&g_GMenuboxcornersLevelTextWords2 + 0x5C), (void *)((char *)&g_GMenuboxcornersLevelTextWords2 + 0x5C), (void *)((char *)&g_GMenuboxcornersLevelTextWords2 + 0x5C) },
    "music         :  none\000\000\000",
    { (void *)((char *)&g_GMenuboxcornersLevelTextWords2 + 0x84), (void *)((char *)&g_GMenuboxcornersLevelTextWords2 + 0x84), (void *)((char *)&g_GMenuboxcornersLevelTextWords2 + 0x84), (void *)((char *)&g_GMenuboxcornersLevelTextWords2 + 0x84) },
    0x20202020,
    0x20202020,
    0x20202020,
    0x20202020,
    0x20202020,
    0x20202020,
    0x20202020,
    0x20202020,
    0x20202020,
    0x20202020,
    0x20202020,
    0x20000000,
    { (void *)((char *)&g_GMenuboxcornersLevelTextWords2 + 0xAC), (void *)((char *)&g_GMenuboxcornersLevelTextWords2 + 0xAC), (void *)((char *)&g_GMenuboxcornersLevelTextWords2 + 0xAC), (void *)((char *)&g_GMenuboxcornersLevelTextWords2 + 0xAC) },
};
#endif
#endif

#if defined(VERSION_EU)
#if defined(VERSION_EU)
RestfloatRecordWordsEuLayout492 g_floatRecordWordsEu = {
    0,
    { 18.0f, 24.0f, 0.75f, 1.0f },
    0x02FFFFC8,
    "VG/\000",
    1,
    { 8.25f, 1e+01f, 0.67499995f, 1.0f },
    0x02FFFFC8,
    "VG/\000\000\000\000\000",
    { 10.8f, 16.8f, 0.45000002f, 0.6f },
    0x02FFFFC8,
    "VG/\000",
    1,
    { 6.75f, 7.5f, 0.5625f, 0.75f },
    0x02FFFFC8,
    "VG/\000\000\000\000\000",
    { 10.8f, 16.8f, 0.45000002f, 0.6f },
    16777160,
    "VG/\000",
    1,
    { 6.75f, 7.0f, 0.6f, 0.7f },
    0x02FFFFC8,
    "VG/\000\000\000\000\000",
    { 12.599999f, 24.0f, 0.525f, 1.0f },
    0x02FFFFC8,
    "VG/\000",
    2,
    { 6.0f, 8.0f, 0.75f, 1.0f },
    0x01FFFFC8,
    { -14336, 1 },
    { 6.75f, 1e+01f, 0.5625f, 1.0f },
    0x02FFFFC8,
    "VG/\000\000\000\000\000",
    { 18.0f, 24.0f, 0.75f, 1.0f },
    0x02FFFFC8,
    "VG/\000",
    1,
    { 8.25f, 1e+01f, 0.67499995f, 1.0f },
    0x02FFFFC8,
    "VG/\000\000\000\000\000",
    { 10.8f, 16.8f, 0.45000002f, 0.6f },
    0x02FFFFC8,
    "VG/\000",
    1,
    { 6.75f, 7.5f, 0.5625f, 0.75f },
    0x02FFFFC8,
    "VG/\000\000\000\000\000",
    { 10.8f, 16.8f, 0.45000002f, 0.6f },
    16777160,
    "VG/\000",
    1,
    { 6.75f, 7.0f, 0.6f, 0.7f },
    0x02FFFFC8,
    "VG/\000\000\000\000\000",
    { 12.599999f, 24.0f, 0.525f, 1.0f },
    0x02FFFFC8,
    "VG/\000",
    2,
    { 6.0f, 8.0f, 0.75f, 1.0f },
    0x01FFFFC8,
    { -14336, 1 },
    { 6.75f, 1e+01f, 0.5625f, 1.0f },
    0x02FFFFC8,
    "VG/\000\000\000\000\000",
    { 18.0f, 24.0f, 0.75f, 1.0f },
    0x02FFFFC8,
    "VG/\000",
    1,
    { 8.25f, 1e+01f, 0.67499995f, 1.0f },
    0x02FFFFC8,
    "VG/\000\000\000\000\000",
    { 10.8f, 16.8f, 0.45000002f, 0.6f },
    0x02FFFFC8,
    "VG/\000",
    1,
    { 6.75f, 7.5f, 0.5625f, 0.75f },
    0x02FFFFC8,
    "VG/\000\000\000\000\000",
    { 10.8f, 16.8f, 0.45000002f, 0.6f },
    16777160,
    "VG/\000",
    1,
    { 6.75f, 7.0f, 0.6f, 0.7f },
    0x02FFFFC8,
    "VG/\000\000\000\000\000",
    { 12.599999f, 24.0f, 0.525f, 1.0f },
    0x02FFFFC8,
    "VG/\000",
    2,
    { 6.0f, 8.0f, 0.75f, 1.0f },
    0x01FFFFC8,
    { -14336, 1 },
    { 6.75f, 1e+01f, 0.5625f, 1.0f },
    0x02FFFFC8,
    "VG/\000",
};
MenuBoxCorner g_menuBoxCorners[8] = {
    { -1, -1, 0, 0, 0, 0 },
    { 1, -1, 0, 0, 0, 0 },
    { 1, 1, 0, 0, 0, 0 },
    { -1, 1, 0, 0, 0, 0 },
    { -1, -1, -2, 0, 0, 0 },
    { 1, -1, -2, 0, 0, 0 },
    { 1, 1, -2, 0, 0, 0 },
    { -1, 1, -2, 0, 0, 0 },
};
RestGMenuboxcornersLevelTextWords3Layout493 g_GMenuboxcornersLevelTextWords3 = {
    { 0, 0 },
    -5.5e+02f,
    "level         :      \000\000\000",
    { (void *)((char *)&g_GMenuboxcornersLevelTextWords3 + 0xC), (void *)((char *)&g_GMenuboxcornersLevelTextWords3 + 0xC), (void *)((char *)&g_GMenuboxcornersLevelTextWords3 + 0xC), (void *)((char *)&g_GMenuboxcornersLevelTextWords3 + 0xC) },
    "lod chg dist  :      \000\000\000",
    { (void *)((char *)&g_GMenuboxcornersLevelTextWords3 + 0x34), (void *)((char *)&g_GMenuboxcornersLevelTextWords3 + 0x34), (void *)((char *)&g_GMenuboxcornersLevelTextWords3 + 0x34), (void *)((char *)&g_GMenuboxcornersLevelTextWords3 + 0x34) },
    "global scaler :      \000\000\000",
    { (void *)((char *)&g_GMenuboxcornersLevelTextWords3 + 0x5C), (void *)((char *)&g_GMenuboxcornersLevelTextWords3 + 0x5C), (void *)((char *)&g_GMenuboxcornersLevelTextWords3 + 0x5C), (void *)((char *)&g_GMenuboxcornersLevelTextWords3 + 0x5C) },
    "music         :  none\000\000\000",
    { (void *)((char *)&g_GMenuboxcornersLevelTextWords3 + 0x84), (void *)((char *)&g_GMenuboxcornersLevelTextWords3 + 0x84), (void *)((char *)&g_GMenuboxcornersLevelTextWords3 + 0x84), (void *)((char *)&g_GMenuboxcornersLevelTextWords3 + 0x84) },
    0x20202020,
    0x20202020,
    0x20202020,
    0x20202020,
    0x20202020,
    0x20202020,
    0x20202020,
    0x20202020,
    0x20202020,
    0x20202020,
    0x20202020,
    0x20000000,
    { (void *)((char *)&g_GMenuboxcornersLevelTextWords3 + 0xAC), (void *)((char *)&g_GMenuboxcornersLevelTextWords3 + 0xAC), (void *)((char *)&g_GMenuboxcornersLevelTextWords3 + 0xAC), (void *)((char *)&g_GMenuboxcornersLevelTextWords3 + 0xAC) },
};
#endif
#endif

#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE)
s32 g_minusOneSentinelWords[3] = {
    -1, 0, 16,
};
#endif
#if defined(VERSION_EU)
RestminusOneSentinelWordsLayout495 g_minusOneSentinelWords = {
    { -1, 0, 16 },
    1024.0f,
};
#endif
#if defined(VERSION_EU_X)
RestminusOneSentinelWordsLayout496 g_minusOneSentinelWords = {
    { -1, 0, 16 },
    0x02202021,
};
#endif
#if defined(VERSION_US)
s32 g_minusOneSentinelWords[2] = {
    -1, 0,
};
#endif
#endif

#if defined(VERSION_US_REV1)
struct {
    unsigned int w0[5];
    unsigned char b1[8];
} g_debugMenuMixedRows[9] = {
    { { 0x00000000, 0x41C00000, 0x41C00000, 0x3F800000, 0x3F800000 }, { 0x02, 0xFF, 0xFF, 0xC8, 0x56, 0x47, 0x2F, 0x00 } },
    { { 0x00000001, 0x41300000, 0x41200000, 0x3F666666, 0x3F800000 }, { 0x02, 0xFF, 0xFF, 0xC8, 0x56, 0x47, 0x2F, 0x00 } },
    { { 0x00000000, 0x41666667, 0x41866666, 0x3F19999A, 0x3F19999A }, { 0x02, 0xFF, 0xFF, 0xC8, 0x56, 0x47, 0x2F, 0x00 } },
    { { 0x00000001, 0x41100000, 0x40F00000, 0x3F400000, 0x3F400000 }, { 0x02, 0xFF, 0xFF, 0xC8, 0x56, 0x47, 0x2F, 0x00 } },
    { { 0x00000000, 0x41666667, 0x41866666, 0x3F19999A, 0x3F19999A }, { 0x00, 0xFF, 0xFF, 0xC8, 0x56, 0x47, 0x2F, 0x00 } },
    { { 0x00000000, 0x40C00000, 0x41066666, 0x3E800000, 0x3E800000 }, { 0x02, 0xFF, 0xFF, 0xC8, 0x56, 0x47, 0x2F, 0x00 } },
    { { 0x00000000, 0x4199999A, 0x41C00000, 0x3F4CCCCD, 0x3F800000 }, { 0x02, 0xFF, 0xFF, 0xC8, 0x56, 0x47, 0x2F, 0x00 } },
    { { 0x00000002, 0x41000000, 0x41000000, 0x3F800000, 0x3F800000 }, { 0x01, 0xFF, 0xFF, 0xC8, 0xFF, 0xFF, 0xC8, 0x00 } },
    { { 0x00000001, 0x41100000, 0x41200000, 0x3F400000, 0x3F800000 }, { 0x02, 0xFF, 0xFF, 0xC8, 0x56, 0x47, 0x2F, 0x00 } },
};
#endif
