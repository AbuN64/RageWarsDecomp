#include "include_asm.h"
#include "MENU/PAK_LOAD.H"

#if defined(VERSION_DE)
extern char *g_pakThresholdBelow50Text, *g_pakThresholdBelow150Text, *g_pakThresholdBelow300Text, *g_pakThresholdBelow500Text, *g_pakThresholdBelow800Text, *g_pakThresholdBelow1300Text;
extern char *g_pakThresholdBelow2000Text, *g_pakThresholdBelow3000Text, *g_pakThresholdBelow4500Text, *g_pakThresholdBelow6500Text, *g_pakThresholdBelow9999Text, *g_pakThresholdAtLeast9999Text;
typedef struct { char pad0[0x14]; char **text; } PakThresholdLabel;
/* Copies the 12-byte rank label chosen by the value g_pakProfileRankScore (banded 0, 50, 150, 300, 500, 800, 1300, 2000, 3000, 4500, 6500, 9999) into the text 8 bytes in; returns zero. */
s32 Snapshot_UpdateThresholdLabel(PakThresholdLabel *label) {
    u32 v = g_pakLoadedProfile.values[2];
    char *src = 0;
    char *dst;
    s32 i;
    if (v < 50) src = g_pakThresholdBelow50Text;
    else if (v >= 50 && v < 150) src = g_pakThresholdBelow150Text;
    else if (v >= 150 && v < 300) src = g_pakThresholdBelow300Text;
    else if (v >= 300 && v < 500) src = g_pakThresholdBelow500Text;
    else if (v >= 500 && v < 800) src = g_pakThresholdBelow800Text;
    else if (v >= 800 && v < 1300) src = g_pakThresholdBelow1300Text;
    else if (v >= 1300 && v < 2000) src = g_pakThresholdBelow2000Text;
    else if (v >= 2000 && v < 3000) src = g_pakThresholdBelow3000Text;
    else if (v >= 3000 && v < 4500) src = g_pakThresholdBelow4500Text;
    else if (v >= 4500 && v < 6500) src = g_pakThresholdBelow6500Text;
    else if (v >= 6500 && v < 9999) src = g_pakThresholdBelow9999Text;
    else if ((s32)v >= 9999) src = g_pakThresholdAtLeast9999Text;
    dst = *label->text;
    dst += 8;
    if (src != 0) {
        i = 0;
        do { *dst++ = *src++; i++; } while (i < 12);
    }
    return 0;
}
#endif
