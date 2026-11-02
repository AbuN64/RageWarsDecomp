#include "COMMON/FORMAT.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "DATA_OVERLAY_LAYOUTS.H"
#include "TYPES.H"

#include "include_asm.h"

/* 800D064C_2.CPP */
/* ROM-grounded data: rodata/writable/800D0650 */
#ifdef VERSION_DE
#if defined(VERSION_DE)
struct {
    s32 g_collisionMovementCount;
    s32 g_collisionPeakMovementCount;
    s32 g_collisionSweepCount;
    s32 g_collisionPeakSweepCount;
    s32 g_cinemaLastUpdatedFrame;
    u8 alignmentFill20[12];
} g_GameobjectMovetoxzkeepheightWords2 __attribute__((aligned(4))) = {
    0,
    0,
    0,
    0,
    -1,
    { 0x40, 0x40, 0x0, 0x0, 0x10, 0x62, 0x0, 0x3, 0x3c, 0x3, 0xa4, 0x60 }
};
typedef char g_GameobjectMovetoxzkeepheightWords2SizeCheck[(sizeof(g_GameobjectMovetoxzkeepheightWords2) == 32) ? 1 : -1];
#endif
#endif
#ifdef VERSION_EU
#if defined(VERSION_EU)
struct {
    s32 g_collisionMovementCount;
    s32 g_collisionPeakMovementCount;
    s32 g_collisionSweepCount;
    s32 g_collisionPeakSweepCount;
    s32 g_cinemaLastUpdatedFrame;
    u8 alignmentFill20[12];
} g_GameobjectMovetoxzkeepheightWords2 __attribute__((aligned(4))) = {
    0,
    0,
    0,
    0,
    -1,
    { 0x2f, 0x20, 0x44, 0x49, 0x4e, 0x4f, 0x53, 0x4f, 0x49, 0x44, 0x53, 0x0 }
};
typedef char g_GameobjectMovetoxzkeepheightWords2SizeCheck[(sizeof(g_GameobjectMovetoxzkeepheightWords2) == 32) ? 1 : -1];
#endif
#endif
#ifdef VERSION_EU_X
#if defined(VERSION_EU_X)
struct {
    s32 g_collisionMovementCount;
    s32 g_collisionPeakMovementCount;
    s32 g_collisionSweepCount;
    s32 g_collisionPeakSweepCount;
    s32 g_cinemaLastUpdatedFrame;
    u8 alignmentFill20[12];
} g_GameobjectMovetoxzkeepheightWords2 __attribute__((aligned(4))) = {
    0,
    0,
    0,
    0,
    -1,
    { 0x3f, 0xc6, 0xcf, 0x43, 0x3f, 0xc6, 0xaf, 0x3a, 0x3f, 0xc6, 0x8f, 0x30 }
};
typedef char g_GameobjectMovetoxzkeepheightWords2SizeCheck[(sizeof(g_GameobjectMovetoxzkeepheightWords2) == 32) ? 1 : -1];
#endif
#endif
#ifdef VERSION_US
#if defined(VERSION_US)
struct {
    s32 g_collisionMovementCount;
    s32 g_collisionPeakMovementCount;
    s32 g_collisionSweepCount;
    s32 g_collisionPeakSweepCount;
    s32 g_cinemaLastUpdatedFrame;
    u8 alignmentFill20[12];
} g_GameobjectMovetoxzkeepheightWords2 __attribute__((aligned(4))) = {
    0,
    0,
    0,
    0,
    -1,
    { 0x50, 0x41, 0x52, 0x54, 0x49, 0x43, 0x4c, 0x45, 0x5f, 0x49, 0x4d, 0x50 }
};
typedef char g_GameobjectMovetoxzkeepheightWords2SizeCheck[(sizeof(g_GameobjectMovetoxzkeepheightWords2) == 32) ? 1 : -1];
#endif
#endif
#ifdef VERSION_US_REV1
#if defined(VERSION_US_REV1)
struct {
    s32 g_collisionMovementCount;
    s32 g_collisionPeakMovementCount;
    s32 g_collisionSweepCount;
    s32 g_collisionPeakSweepCount;
    s32 g_cinemaLastUpdatedFrame;
    u8 alignmentFill20[12];
} g_GameobjectMovetoxzkeepheightWords2 __attribute__((aligned(4))) = {
    0,
    0,
    0,
    0,
    -1,
    { 0x3f, 0xc7, 0x4f, 0x67, 0x3f, 0xc7, 0x2f, 0x5e, 0x3f, 0xc7, 0xf, 0x55 }
};
typedef char g_GameobjectMovetoxzkeepheightWords2SizeCheck[(sizeof(g_GameobjectMovetoxzkeepheightWords2) == 32) ? 1 : -1];
#endif
#endif

/* 800D0670.CPP */
/* ROM-grounded data: src/k_moveToXzKeepHeightPoolPair_us_rev1.c */
const float g_GameobjectMovetoxzkeepheightWords1[2] = {
    0.3f, 3.0f,
};
