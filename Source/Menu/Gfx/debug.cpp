#include "include_asm.h"
#include "Common/gfx_initializefrontendservices.h"
#include "Common/format.h"
#include "Common/runtime_declarations.h"
#include "types.h"
#include "stdarg.h"
#include "Menu/Gfx/gfx_formatargumentlist.h"
#include "Data/rest_source_records.h"
#include "Ui/X_files/x_stdio.h"
#include "Menu/Gfx/Debug/debug_symbols.h"

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

#if !(defined(VERSION_US_REV1))
const char s_gfxDebugLocationFormat[13] =
    "[ %s : %d ]\012\000";
#endif

#if defined(VERSION_US_REV1)
const char k_DebugEncodedBytes[13] =
    "[ %s : %d ]\n\000";
#endif

#if !(defined(VERSION_US_REV1))
const char s_gfxDebugUNKNOWNLabel[8] =
    "UNKNOWN\000";
#endif

#if defined(VERSION_EU_X)
unsigned int k_debugFragment[4] = {
    0x0000001E, 0x00000001, 0x496E6600, 0x4E614E00,
};
#endif

#if defined(VERSION_EU)
unsigned int k_debugFragment[4] = {
    0x0800FFD5, 0x0800FFD6, 0x496E6600, 0x4E614E00,
};
#endif

#if defined(VERSION_DE)
unsigned int k_DebugEncodedWords[4] = {
    0x00000000, 0x00000000, 0x496E6600, 0x4E614E00,
};
#endif

#if defined(VERSION_US_REV1)
const char s_gfxDebugUNKNOWNLabelRev1[8] = "UNKNOWN";
#endif

#if defined(VERSION_US)
char g_GfxdataEncodedBytes[16] = "IC_LEVELInf\000NaN";
#endif

#if defined(VERSION_US_REV1)
unsigned int g_debugInfNanTextWords[4] = {
    0x00000020, 0x00000018, 0x496E6600, 0x4E614E00,
};
#endif
