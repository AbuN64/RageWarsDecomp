#include "COMMON/FORMAT.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "DATA_OVERLAY_LAYOUTS.H"
#include "TYPES.H"
#include "include_asm.h"
#if !(defined(VERSION_US))
#ifdef VERSION_DE
#if defined(VERSION_DE)
/* 800D9355_3.CPP */
/* ROM-grounded data: rodata/writable/800D9360 */
struct {
    s32 g_audioTransformInputStream;
    u8 alignmentFill4[12];
} g_audioLoaddecodedsamplesDataAddressWords __attribute__((aligned(4))) = {
    0,
    { 0x80, 0x14, 0xb9, 0x38, 0x80, 0x14, 0xc8, 0xf0, 0x0, 0x0, 0x0, 0x0 }
};
typedef char g_audioLoaddecodedsamplesDataAddressWordsSizeCheck[(sizeof(g_audioLoaddecodedsamplesDataAddressWords) == 16) ? 1 : -1];
#endif
#endif
#ifdef VERSION_EU
#if defined(VERSION_EU)
struct {
    s32 g_audioTransformInputStream;
    u8 alignmentFill4[12];
} g_audioLoaddecodedsamplesDataAddressWords __attribute__((aligned(4))) = {
    0,
    { 0x80, 0xc, 0x6a, 0x70, 0x80, 0xc, 0x6a, 0x60, 0x80, 0xc, 0x6a, 0x50 }
};
typedef char g_audioLoaddecodedsamplesDataAddressWordsSizeCheck[(sizeof(g_audioLoaddecodedsamplesDataAddressWords) == 16) ? 1 : -1];
#endif
#endif
#ifdef VERSION_EU_X
#if defined(VERSION_EU_X)
struct {
    s32 g_audioTransformInputStream;
    u8 alignmentFill4[12];
} g_audioLoaddecodedsamplesDataAddressWords __attribute__((aligned(4))) = {
    0,
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 }
};
typedef char g_audioLoaddecodedsamplesDataAddressWordsSizeCheck[(sizeof(g_audioLoaddecodedsamplesDataAddressWords) == 16) ? 1 : -1];
#endif
#endif
#ifdef VERSION_US_REV1
#if defined(VERSION_US_REV1)
struct {
    s32 g_audioTransformInputStream;
    u8 alignmentFill4[12];
} g_audioLoaddecodedsamplesDataAddressWords __attribute__((aligned(4))) = {
    0,
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 }
};
typedef char g_audioLoaddecodedsamplesDataAddressWordsSizeCheck[(sizeof(g_audioLoaddecodedsamplesDataAddressWords) == 16) ? 1 : -1];
#endif
#endif
#endif
