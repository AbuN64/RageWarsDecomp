extern char g_viDataZeroWords[];
#include "COMMON/FORMAT.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "DATA_OVERLAY_LAYOUTS.H"
#include "TYPES.H"

#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE)
#if defined(VERSION_DE)
void * D_src_c0f3ff2a[4] = {
    (void *)&g_viDataZeroWords, (void *)g_viDataZeroWords + 0x30, 0, 0
};
#endif
#endif
#if defined(VERSION_EU)
#if defined(VERSION_EU)
struct {
    void * __osViCurr;
    void * __osViNext;
    u8 alignmentFill8[8];
} D_src_c0f3ff2a __attribute__((aligned(4))) = {
    (void *)&g_viDataZeroWords,
    (void *)g_viDataZeroWords + 0x30,
    { 0x20, 0x20, 0x70, 0x72, 0x69, 0x6d, 0x61, 0x67 }
};
typedef char D_src_c0f3ff2aSizeCheck[(sizeof(D_src_c0f3ff2a) == 16) ? 1 : -1];
#endif
#endif
#if defined(VERSION_EU_X)
#if defined(VERSION_EU_X)
struct {
    void * __osViCurr;
    void * __osViNext;
    u8 alignmentFill8[8];
} D_src_c0f3ff2a __attribute__((aligned(4))) = {
    (void *)&g_viDataZeroWords,
    (void *)g_viDataZeroWords + 0x30,
    { 0x3a, 0x98, 0x37, 0xf1, 0x3a, 0xb5, 0x4, 0xf3 }
};
typedef char D_src_c0f3ff2aSizeCheck[(sizeof(D_src_c0f3ff2a) == 16) ? 1 : -1];
#endif
#endif
#if defined(VERSION_US)
#if defined(VERSION_US)
struct {
    void * __osViCurr;
    void * __osViNext;
    u8 alignmentFill8[8];
} D_src_c0f3ff2a __attribute__((aligned(4))) = {
    (void *)&g_viDataZeroWords,
    (void *)g_viDataZeroWords + 0x30,
    { 0x58, 0x5f, 0x46, 0x49, 0x52, 0x45, 0x42, 0x4f }
};
typedef char D_src_c0f3ff2aSizeCheck[(sizeof(D_src_c0f3ff2a) == 16) ? 1 : -1];
#endif
#endif
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded us-rev1 data; explicit withholding in other holders. */
#if defined(VERSION_US_REV1)
struct {
    void * __osViCurr;
    void * __osViNext;
} g_osvigetcurrentframebufferDataAddressWords __attribute__((aligned(4))) = {
    (void *)&g_viDataZeroWords,
    (void *)((char *)&g_viDataZeroWords + 48)
};
typedef char g_osvigetcurrentframebufferDataAddressWordsSizeCheck[(sizeof(g_osvigetcurrentframebufferDataAddressWords) == 8) ? 1 : -1];
#endif
#endif
