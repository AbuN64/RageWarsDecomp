#include "types.h"
#include "include_asm.h"

/* ACHIEVE_UPDATEPLAYERPREVIEWSTATS_DATA.CPP */
#if defined(VERSION_DE)
const char k_achieveUpdateplayerpreviewstatsDataTextBytes[5] __attribute__((aligned(1))) = "%d%%\000";
#endif
#if defined(VERSION_EU)
const char k_achieveUpdateplayerpreviewstatsDataTextBytes[5] __attribute__((aligned(1))) = "%d%%\000";
#endif
#if defined(VERSION_EU_X)
const char k_achieveUpdateplayerpreviewstatsDataTextBytes[5] __attribute__((aligned(1))) = "%d%%\000";
#endif
#if defined(VERSION_US)
const char k_achieveUpdateplayerpreviewstatsDataTextBytes[5] __attribute__((aligned(1))) = "%d%%\000";
#endif
#if defined(VERSION_US_REV1)
const char k_achieveUpdateplayerpreviewstatsDataTextBytes[5] __attribute__((aligned(1))) = "%d%%\000";
#endif

/* G_OVERLAYNINECOLORMASKBYTES.CPP */
#if defined(VERSION_US_REV1)
struct {
    u8 retainedRecordWords[12];
} g_portalColorMaskBytes __attribute__((aligned(4))) = {
    { 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00, 0x07, 0xE0 }
};
#endif
