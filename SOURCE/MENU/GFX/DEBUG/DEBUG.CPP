#include "include_asm.h"
#include "COMMON/GFX_INITIALIZEFRONTENDSERVICES.H"
#include "COMMON/FORMAT.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "TYPES.H"
#include "stdarg.h"
#include "MENU/GFX/GFX_FORMATARGUMENTLIST.H"
#include "DATA/REST_SOURCE_RECORDS.H"

/* DEBUG.CPP */
/* 80414330.CPP */
extern char g_debugNameNumberFormat[];
extern char g_debugUnnamedLabelText[];
extern s32 XStdio_FormatBuffer(void *goal, s32 fmt0, ...);

s32 Gfx_FormatDiagnosticMessage(char *name, s32 number, char *format, ...) {
    va_list arguments;
    s32 length;

    if (format != 0) {
        va_start(arguments, format);
        if (name != 0) {
            length = XStdio_FormatBuffer(g_uiFormattedMessage, g_debugNameNumberFormat, name, number);
        } else {
            length = XStdio_FormatBuffer(g_uiFormattedMessage, g_debugNameNumberFormat, g_debugUnnamedLabelText, number);
        }
        Gfx_FormatArgumentList(g_uiFormattedMessage + length, format, arguments);
        va_end(arguments);
    }
    return 1;
}

/* Returns the address of the table g_uiFormattedMessage. */

char *Gfx_GetDiagnosticMessage(void) {
    return g_uiFormattedMessage;
}

/* 800E10F0.CPP */
#if !(defined(VERSION_US_REV1))
const char s_gfxDebugLocationFormat[13] =
    "[ %s : %d ]\012\000";
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/s_gfxDebugLocationFormatRev1.c */
const char k_DebugEncodedBytes[13] =
    "[ %s : %d ]\n\000";
#endif

/* 800E1100.CPP */
#if !(defined(VERSION_US_REV1))
const char s_gfxDebugUNKNOWNLabel[8] =
    "UNKNOWN\000";
#endif

#if defined(VERSION_EU_X)
unsigned int k_DebugEncodedWordsBlock1[4] = {
    0x0000001E, 0x00000001, 0x496E6600, 0x4E614E00,
};
#endif

#if defined(VERSION_EU)
unsigned int k_DebugEncodedWordsBlock2[4] = {
    0x0800FFD5, 0x0800FFD6, 0x496E6600, 0x4E614E00,
};
#endif

#if defined(VERSION_DE)
unsigned int k_DebugEncodedWords[4] = {
    0x00000000, 0x00000000, 0x496E6600, 0x4E614E00,
};
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/s_gfxDebugUNKNOWNLabelRev1.c */
const char s_gfxDebugUNKNOWNLabelRev1[8] = "UNKNOWN";
#endif

/* G_GFXDATAENCODEDWORDS.CPP */
#if defined(VERSION_US)
/* g_GfxdataEncodedBytes_Gfxdata2.CPP */
char g_GfxdataEncodedBytes[16] = "IC_LEVELInf\000NaN";
#endif

/* G_OVERLAYSNINECONSTANTSCONSTANTWORDSBLOCK1.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800E1108 */
unsigned int g_overlaysNineConstantsConstantWordsBlock1[4] = {
    0x00000020, 0x00000018, 0x496E6600, 0x4E614E00,
};
#endif
