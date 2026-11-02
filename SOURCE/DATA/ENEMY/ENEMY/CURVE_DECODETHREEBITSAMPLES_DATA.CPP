#include "DATA/REST_SOURCE_RECORDS.H"
extern char g_threadLabelWordsEuropean[];
extern char g_threadLabelWordsEuropeanX[];
extern char g_threadLabelWordsGerman[];
extern char g_threadLabelWordsUs[];
extern char g_threadLabelWordsUsRev1[];
#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE)
extern char g_threadLabelWordsGerman[];
RestCurveDecodethreebitsamplesEncodedWordsLayout313 k_CurveDecodethreebitsamplesEncodedWords = {
    { 0, 61440, 124928, 117760, 0, 0, -61440, -53248 },
    { (void *)((char *)&g_threadLabelWordsGerman + 0x5C), (void *)((char *)&g_threadLabelWordsGerman + 0x54), (void *)((char *)&g_threadLabelWordsGerman + 0x4C), (void *)((char *)&g_threadLabelWordsGerman + 0x3C), (void *)((char *)&g_threadLabelWordsGerman + 0x34), (void *)((char *)&g_threadLabelWordsGerman + 0x2C), (void *)((char *)&g_threadLabelWordsGerman + 0x20), (void *)((char *)&g_threadLabelWordsGerman + 0x14), (void *)((char *)&g_threadLabelWordsGerman + 0xC), 0 },
    { -1, 10273 },
};
#endif
#if defined(VERSION_EU)
extern char g_threadLabelWordsEuropean[];
RestCurveDecodethreebitsamplesEncodedWordsLayout314 k_CurveDecodethreebitsamplesEncodedWords = {
    { 0, 61440, 124928, 117760, 0, 0, -61440, -53248 },
    { (void *)((char *)&g_threadLabelWordsEuropean + 0x5C), (void *)((char *)&g_threadLabelWordsEuropean + 0x54), (void *)((char *)&g_threadLabelWordsEuropean + 0x4C), (void *)((char *)&g_threadLabelWordsEuropean + 0x3C), (void *)((char *)&g_threadLabelWordsEuropean + 0x34), (void *)((char *)&g_threadLabelWordsEuropean + 0x2C), (void *)((char *)&g_threadLabelWordsEuropean + 0x20), (void *)((char *)&g_threadLabelWordsEuropean + 0x14), (void *)((char *)&g_threadLabelWordsEuropean + 0xC), 0 },
    -1,
    "FAMI",
};
#endif
#if defined(VERSION_EU_X)
extern char g_threadLabelWordsEuropeanX[];
RestCurveDecodethreebitsamplesEncodedWordsLayout315 k_CurveDecodethreebitsamplesEncodedWords = {
    { 0, 61440, 124928, 117760, 0, 0, -61440, -53248 },
    { (void *)((char *)&g_threadLabelWordsEuropeanX + 0x5C), (void *)((char *)&g_threadLabelWordsEuropeanX + 0x54), (void *)((char *)&g_threadLabelWordsEuropeanX + 0x4C), (void *)((char *)&g_threadLabelWordsEuropeanX + 0x3C), (void *)((char *)&g_threadLabelWordsEuropeanX + 0x34), (void *)((char *)&g_threadLabelWordsEuropeanX + 0x2C), (void *)((char *)&g_threadLabelWordsEuropeanX + 0x20), (void *)((char *)&g_threadLabelWordsEuropeanX + 0x14), (void *)((char *)&g_threadLabelWordsEuropeanX + 0xC), 0 },
    -1,
    1.000847f,
};
#endif
#if defined(VERSION_US)
extern char g_threadLabelWordsUs[];
RestCurveDecodethreebitsamplesEncodedWordsLayout316 k_CurveDecodethreebitsamplesEncodedWords = {
    { 0, 61440, 124928, 117760, 0, 0, -61440, -53248 },
    { (void *)((char *)&g_threadLabelWordsUs + 0x5C), (void *)((char *)&g_threadLabelWordsUs + 0x54), (void *)((char *)&g_threadLabelWordsUs + 0x4C), (void *)((char *)&g_threadLabelWordsUs + 0x3C), (void *)((char *)&g_threadLabelWordsUs + 0x34), (void *)((char *)&g_threadLabelWordsUs + 0x2C), (void *)((char *)&g_threadLabelWordsUs + 0x20), (void *)((char *)&g_threadLabelWordsUs + 0x14), (void *)((char *)&g_threadLabelWordsUs + 0xC), 0 },
    -1,
    "INI_",
};
#endif
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded exact candidate, normalized from prior lane proof. */
RestCurveDecodethreebitsamplesEncodedWordsLayout317 g_CurveDecodethreebitsamplesEncodedWords = {
    { 0, 61440, 124928, 117760, 0, 0, -61440, -53248 },
    { (void *)((char *)&g_threadLabelWordsUsRev1 + 92), (void *)((char *)&g_threadLabelWordsUsRev1 + 84), (void *)((char *)&g_threadLabelWordsUsRev1 + 76), (void *)((char *)&g_threadLabelWordsUsRev1 + 60), (void *)((char *)&g_threadLabelWordsUsRev1 + 52), (void *)((char *)&g_threadLabelWordsUsRev1 + 44), (void *)((char *)&g_threadLabelWordsUsRev1 + 32), (void *)((char *)&g_threadLabelWordsUsRev1 + 20), (void *)((char *)&g_threadLabelWordsUsRev1 + 12), 0 },
    -1,
};
#endif
